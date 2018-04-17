//
//  TapToSpeakView.m
//  Telegraph
//
//  Created by Alexander Dubikov on 21/02/2018.
//

#import "TapToSpeakView.h"
#import "TGInterfaceManager.h"
#import "TGDatabase.h"

#import <LegacyComponents/LegacyComponents.h>

#import "FMDatabase.h"

#import "ATQueue.h"

#import "TGTimer.h"

#import "TGTelegraph.h"
#import "TGAppDelegate.h"

#import <LegacyComponents/ActionStage.h>
#import <LegacyComponents/SGraphObjectNode.h>

#import <LegacyComponents/TGCache.h>
#import <LegacyComponents/TGRemoteImageView.h>

#import <SSignalKit/SSignalKit.h>

#import "TGPreparedLocalDocumentMessage.h"

#import "TGGlobalMessageSearchSignals.h"

#import "TGSpotlightIndexData.h"

#import <MobileCoreServices/MobileCoreServices.h>

#import "TGModernSendSecretMessageActor.h"

#import "TGTelegramNetworking.h"
#import "TGConversationAddMessagesActor.h"

#import "TGChannelList.h"

#import "TGMediaCacheIndexData.h"


#import "TGRemoteRecentPeer.h"
#import "TGRemoteRecentPeerSet.h"
#import "TGRemoteRecentPeerCategories.h"

#import "TGMessageViewedContentProperty.h"

#import "TGInterfaceManager.h"
#import "TGRecentGifsSignal.h"
#import "TGRecentStickersSignal.h"

#import "TGGroupManagementSignals.h"

#import "TGCdnData.h"

#import "TGAudioMediaAttachment+Telegraph.h"
#import "TGUser+Telegraph.h"

#import "TGUnseenPeerMentionsState.h"
#import "TGUnseenPeerMentionsMessageIdsState.h"

@implementation TapToSpeakView 

- (instancetype)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame];
	if (self != nil)
	{
		[self configure];
	}
	return self;
}

-(void)configure
{
    _speechRecognizer = [[SFSpeechRecognizer alloc] initWithLocale:[NSLocale localeWithLocaleIdentifier:@"en-US"]];
    
    _speechRecognizer.delegate = self;
    
    _audioEngine = [AVAudioEngine new];
    
    _recordButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 90, 90)];
    [_recordButton setImage:[UIImage imageNamed:@"microphone"] forState:UIControlStateNormal];
    [_recordButton addTarget:self action:@selector(startRecording) forControlEvents:UIControlEventTouchUpInside];
    
    _textView = [UITextView new];
    _textView.frame = CGRectMake(0, 100, self.bounds.size.width, 200);
    _textView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    _textView.backgroundColor = [UIColor clearColor];
    
    [self addSubview:_recordButton];
    [self addSubview:_textView];
    
    if (self.bounds.size.width > self.frame.origin.y) {
        _vertical = NO;
    } else {
        _vertical = YES;
    }
    
    [SFSpeechRecognizer requestAuthorization:^(SFSpeechRecognizerAuthorizationStatus status) {
    }];
}

-(void)layoutSubviews {
    [super layoutSubviews];
    
    _recordButton.frame = CGRectMake(0, 0, 90, 90);
    
    if (_vertical == NO) {
        
        if ([[UIDevice currentDevice] orientation] == UIDeviceOrientationPortrait) {
            _recordButton.center = CGPointMake(self.center.x, 370);
            
        } else {
            _recordButton.center = CGPointMake(self.center.x, 55);
        }
        
    } else {
        if ([[UIDevice currentDevice] orientation] == UIDeviceOrientationPortrait) {
            _recordButton.center = CGPointMake(self.center.x, 55);
            
        } else {
            _recordButton.frame = CGRectMake(self.frame.size.width / 2 - 45, - self.frame.origin.y / 2, 90, 90);
        }
    }
    _textView.frame = CGRectMake(0, 100, self.bounds.size.width, 200);
}

-(void) startTimer
{
    if (_done == NO) {
        double delayInSeconds = 3.0;
        dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, delayInSeconds * NSEC_PER_SEC);
        dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
            _done = YES;
            [self startTimer];
        });
    } else {
        [self stopRecording];
    }
//    if (_timer != nil) {
//        [_timer invalidate];
//        _timer = nil;
//    }
//
//    self.timer = [NSTimer scheduledTimerWithTimeInterval:5.0
//                                                  target:self
//                                                selector:@selector(stopRecording:)
//                                                userInfo:nil
//                                                 repeats:NO];
//    [[NSRunLoop currentRunLoop] addTimer:self.timer forMode:NSRunLoopCommonModes];
//    [self.timer fire];
}

-(void)startRecording {
    if (_recognitionTask != nil) {
        [_recognitionTask cancel];
        _recognitionTask = nil;
    }
    
    AVAudioSession *audioSession = [AVAudioSession sharedInstance];
    NSError *error = nil;
    
    [audioSession setCategory:AVAudioSessionCategoryRecord error:&error];
    [audioSession setMode:AVAudioSessionModeMeasurement error:&error];
    [audioSession setActive:YES withOptions:AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation error:&error];
    
    if (error != nil) { return; }
    _recognitionRequest = [SFSpeechAudioBufferRecognitionRequest new];
    
    AVAudioInputNode *inputNode = _audioEngine.inputNode;
    
    _recognitionRequest.shouldReportPartialResults = YES;
    
    if (inputNode == nil || _recognitionRequest == nil) {
        return;
    }
    
    _timer = [NSTimer timerWithTimeInterval:5 target:self selector:@selector(stopRecording) userInfo:nil repeats:NO];
    
    _recognitionTask = [_speechRecognizer recognitionTaskWithRequest:_recognitionRequest resultHandler:^(SFSpeechRecognitionResult * _Nullable result, NSError * _Nullable error) {
        
        BOOL isFinal = NO;
        
        if (result != nil) {
            _textView.text = result.bestTranscription.formattedString;
            _done == NO;
            [self startTimer];
            isFinal = result.isFinal;
        }
        
        if (error != nil || isFinal) {
            [_audioEngine stop];
            [inputNode removeTapOnBus:0];
            
            self.recognitionRequest = nil;
            self.recognitionTask = nil;
            self.recordButton.enabled = YES;
        }
        
    }];
    
    AVAudioFormat *recordingFormat = [inputNode outputFormatForBus:0];
    [inputNode installTapOnBus:0 bufferSize:1024 format:recordingFormat block:^(AVAudioPCMBuffer * _Nonnull buffer, AVAudioTime * _Nonnull when) {
        [_recognitionRequest appendAudioPCMBuffer:buffer];
    }];
    
    [_audioEngine prepare];
    [_audioEngine startAndReturnError:nil];
    _textView.text = @"Please speak";
    

}

-(void)speechRecognizer:(SFSpeechRecognizer *)speechRecognizer availabilityDidChange:(BOOL)available {
    _recordButton.enabled = available;
    
}

- (void)tryToStop {
    if (_done == YES) {
        [self stopRecording];
    }
}

- (void)stopRecording {
    
    if (_sent == NO ) {
        _sent = YES;
    
        TGMessage *message = [[TGMessage alloc] init];
        message.text = _textView.text;
        
        if ([_textView.text.lowercaseString containsString:@"yellow"]) {
            [[TGInterfaceManager instance] navigateToConversationWithId:4679961 conversation:nil performActions:@{@"sendMessages": @[message]}];
        } else {
           [[TGInterfaceManager instance] navigateToConversationWithId:294106979 conversation:nil performActions:@{@"sendMessages": @[message]}];
        }
        
        NSLog(_textView.text);
        
        [_audioEngine stop];
        
        self.recognitionRequest = nil;
        self.recognitionTask = nil;
        self.recordButton.enabled = YES;
    }
}

- (void)recordButtonTapped {
    _sent = NO;
    _done == NO;
    
    if (_audioEngine.isRunning) {
        [_audioEngine stop];
        [_recognitionRequest endAudio];
        _recordButton.enabled = NO;
    } else {
        @try {
            [self startRecording];
        }
        @catch (NSException *exception) {
            NSLog(@"%@", exception.reason);
        }
        @finally {
            _recognitionRequest = nil;
            _recognitionTask = nil;
            NSLog(@"OPS");
        }
    }
}

@end

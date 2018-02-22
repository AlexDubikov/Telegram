//
//  TapToSpeakView.m
//  Telegraph
//
//  Created by Alexander Dubikov on 21/02/2018.
//

#import "TapToSpeakView.h"

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
    _recordButton.center = CGPointMake(self.center.x, 55);
    [_recordButton setImage:[UIImage imageNamed:@"microphone"] forState:UIControlStateNormal];
    [_recordButton addTarget:self action:@selector(startRecording) forControlEvents:UIControlEventTouchUpInside];
    
    _textView = [UITextView new];
    _textView.frame = CGRectMake(0, 100, self.bounds.size.width, 200);
    _textView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    _textView.backgroundColor = [UIColor clearColor];
    
    [self addSubview:_recordButton];
    [self addSubview:_textView];

    [SFSpeechRecognizer requestAuthorization:^(SFSpeechRecognizerAuthorizationStatus status) {
    }];
}

-(void) startTimer
{
    if (_timer != nil) {
        [_timer invalidate];
        _timer = nil;
    }
    
    self.timer = [NSTimer scheduledTimerWithTimeInterval:2.0
                                                  target:self
                                                selector:@selector(stopRecording)
                                                userInfo:nil
                                                 repeats:NO];
    [[NSRunLoop currentRunLoop] addTimer:self.timer forMode:NSDefaultRunLoopMode];
    [self.timer fire];
}

-(void)startRecording {
    if (_recognitionTask != nil) {
        [_recognitionTask cancel];
        _recognitionTask = nil;
    }
    
    AVAudioSession *audioSession = [AVAudioSession sharedInstance];
    [audioSession setCategory:AVAudioSessionCategoryRecord error:nil];
    [audioSession setMode:AVAudioSessionModeMeasurement error:nil];
    [audioSession setActive:YES withOptions:AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation error:nil];
    _recognitionRequest = [SFSpeechAudioBufferRecognitionRequest new];
    
    AVAudioInputNode *inputNode = _audioEngine.inputNode;
    
    _recognitionRequest.shouldReportPartialResults = YES;
    _timer = [NSTimer timerWithTimeInterval:2 target:self selector:@selector(stopRecording) userInfo:nil repeats:NO];
    
    _recognitionTask = [_speechRecognizer recognitionTaskWithRequest:_recognitionRequest resultHandler:^(SFSpeechRecognitionResult * _Nullable result, NSError * _Nullable error) {
        
        BOOL isFinal = false;
        
        if (result != nil) {
            _textView.text = result.bestTranscription.formattedString;
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

- (void)stopRecording {
    NSLog(_textView.text);
    [_timer invalidate];
    _timer = nil;
    [_audioEngine stop];
    
    self.recognitionRequest = nil;
    self.recognitionTask = nil;
    self.recordButton.enabled = YES;
    _textView.text = @"done";
}

- (void)recordButtonTapped {
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
            NSLog(@"OPS");
        }
    }
}

@end

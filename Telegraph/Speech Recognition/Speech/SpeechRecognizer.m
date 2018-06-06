//
//  SpeechRecognizer.m
//  SpeechRecognition
//
//  Created by Ilya Tsarev on 18.04.2018.
//  Copyright © 2018 Ilya Tsarev. All rights reserved.
//

#import "SpeechRecognizer.h"
@import Speech;

@interface SpeechRecognizer()  <SFSpeechRecognizerDelegate>

@property(strong, nonatomic) SFSpeechRecognizer *speechRecognizer;
@property(strong, nonatomic) SFSpeechAudioBufferRecognitionRequest *recognitionRequest;
@property(strong, nonatomic) SFSpeechRecognitionTask *recognitionTask;
@property(strong, nonatomic) AVAudioEngine *audioEngine;
@property(strong, nonatomic) AVAudioInputNode *inputNode;

@property(strong, nonatomic) NSTimer *speechSilenceTimer;

@end

@implementation SpeechRecognizer

- (instancetype)initWithLocale:(NSLocale *)locale {
    self = [super init];
    
    if (self) {
        _speechRecognizer = [[SFSpeechRecognizer alloc] initWithLocale:locale];
        self.speechRecognizer.delegate = self;
        
        _audioEngine = [[AVAudioEngine alloc] init];
    }
    
    return self;
}

- (void)startRecognition:(void (^) (NSString *recognizedString, BOOL isFinal))partialCompletion {
    // Make sure there's not a recognition task already running
    if (self.recognitionTask) {
        [self.recognitionTask cancel];
        _recognitionTask = nil;
    }
    
    // Starts an AVAudio Session
    NSError *error;
    AVAudioSession *audioSession = [AVAudioSession sharedInstance];
    [audioSession setCategory:AVAudioSessionCategoryRecord error:&error];
    [audioSession setActive:YES withOptions:AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation error:&error];
    
    // Starts a recognition process, in the block it logs the input or stops the audio
    // process if there's an error.
    self.recognitionRequest = [[SFSpeechAudioBufferRecognitionRequest alloc] init];
    self.recognitionRequest.shouldReportPartialResults = YES;

    self.inputNode = self.audioEngine.inputNode;
    
    __weak SpeechRecognizer* weakSelf = self;    
    self.recognitionTask = [self.speechRecognizer recognitionTaskWithRequest:self.recognitionRequest resultHandler:^(SFSpeechRecognitionResult * _Nullable result, NSError * _Nullable error) {
        
        if (result.isFinal == NO) {
            [weakSelf rescheduleSilenceTimer];
        } else {
            [weakSelf stopSilenceTimer];
        }
        
        if (result) {
            partialCompletion(result.bestTranscription.formattedString, result.isFinal);
            NSLog(@"RESULT: %@\nFinal: %d", result.bestTranscription.formattedString, result.isFinal);
        }
        if (error) {
            [weakSelf.audioEngine stop];
            [weakSelf.inputNode removeTapOnBus:0];
            weakSelf.recognitionRequest = nil;
            weakSelf.recognitionTask = nil;
            partialCompletion([NSString stringWithFormat:@"ERROR: %@", error.localizedDescription], YES);
        }
    }];
    
    // Sets the recording format
    AVAudioFormat *recordingFormat = [self.inputNode outputFormatForBus:0];
    [self.inputNode installTapOnBus:0 bufferSize:1024 format:recordingFormat block:^(AVAudioPCMBuffer * _Nonnull buffer, AVAudioTime * _Nonnull when) {
        [weakSelf.recognitionRequest appendAudioPCMBuffer:buffer];
    }];
    
    // Starts the audio engine, i.e. it starts listening.
    [self.audioEngine prepare];
    [self.audioEngine startAndReturnError:&error];
    NSLog(@"Say Something");
}

- (void)scheduleSilenceTimer {
    NSTimeInterval silenceTime = 2.0;
    
    _speechSilenceTimer = [NSTimer scheduledTimerWithTimeInterval:silenceTime
                                                          target:self
                                                        selector:@selector(stopRecognition)
                                                        userInfo:nil
                                                         repeats:NO];
}

- (void)stopSilenceTimer {
    NSLog(@"Timer stopped");
    [self.speechSilenceTimer invalidate];
    _speechSilenceTimer = nil;
}

- (void)rescheduleSilenceTimer {
    [self stopSilenceTimer];
    [self scheduleSilenceTimer];
    NSLog(@"Reschedule timer");
}

- (void)stopRecognition {
    NSLog(@"Recognition stopped");
    if (self.audioEngine.isRunning) {
        [self.audioEngine stop];
        [self.recognitionRequest endAudio];
        [self.inputNode removeTapOnBus:0];
        _recognitionRequest = nil;
        _recognitionTask = nil;
    }
}

- (void)requestAuthorization:(void (^) (BOOL isAuthorized))completion {
    [SFSpeechRecognizer requestAuthorization:^(SFSpeechRecognizerAuthorizationStatus status) {
        
        BOOL isAuthorized = NO;
        
        switch (status) {
            case SFSpeechRecognizerAuthorizationStatusAuthorized:
                isAuthorized = YES;
                NSLog(@"SFSpeechRecognizerAuthorizationStatusAuthorized");
                break;
            case SFSpeechRecognizerAuthorizationStatusDenied:
                isAuthorized = NO;
                NSLog(@"SFSpeechRecognizerAuthorizationStatusDenied");
                break;
            case SFSpeechRecognizerAuthorizationStatusRestricted:
                isAuthorized = NO;
                NSLog(@"SFSpeechRecognizerAuthorizationStatusRestricted");
                break;
            case SFSpeechRecognizerAuthorizationStatusNotDetermined:
                isAuthorized = NO;
                NSLog(@"SFSpeechRecognizerAuthorizationStatusNotDetermined");
                break;
            default:
                break;
        }
        
        completion(isAuthorized);
    }];
}

#pragma mark - SFSpeechRecognizerDelegate Delegate Methods

- (void)speechRecognizer:(SFSpeechRecognizer *)speechRecognizer availabilityDidChange:(BOOL)available {
    NSLog(@"Availability: %d",available);
}

@end

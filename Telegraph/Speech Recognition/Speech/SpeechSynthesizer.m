//
//  SpeechSynthesizer.m
//  SpeechRecognition
//
//  Created by Ilya Tsarev on 22.04.2018.
//  Copyright © 2018 Ilya Tsarev. All rights reserved.
//

#import "SpeechSynthesizer.h"
#import <AVFoundation/AVFoundation.h>
#import <QuartzCore/QuartzCore.h>

@interface SpeechSynthesizer()

@property (strong, nonatomic) AVSpeechSynthesizer *speechSynthesizer;
@property (strong, nonatomic) NSString *locale;
@property (nonatomic) float speechRate;

@end

@implementation SpeechSynthesizer

- (instancetype)initWithLocale:(NSString *)locale {
    return [self initWithLocale:locale speechRate:0.5f];
}

- (instancetype)initWithLocale:(NSString *)locale speechRate:(float)speechRate {
    self = [super init];
    
    if (self) {
        _speechSynthesizer = [[AVSpeechSynthesizer alloc] init];
        _locale = locale;
        _speechRate = speechRate;
    }
    
    return self;
}

- (void)synthesizeText:(NSString *)text {
    AVSpeechUtterance *speechUtt = [AVSpeechUtterance speechUtteranceWithString:text];
    [speechUtt setRate:self.speechRate];
    speechUtt.voice = [AVSpeechSynthesisVoice voiceWithLanguage:self.locale];
    
    [self.speechSynthesizer speakUtterance:speechUtt];
}


@end

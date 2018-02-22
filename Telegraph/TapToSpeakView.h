//
//  TapToSpeakView.h
//  Telegraph
//
//  Created by Alexander Dubikov on 21/02/2018.
//

#import <UIKit/UIKit.h>
#import <Speech/Speech.h>

@interface TapToSpeakView : UIView <SFSpeechRecognizerDelegate>

@property (nonatomic, strong) SFSpeechRecognizer *speechRecognizer;
@property (nonatomic, strong) SFSpeechAudioBufferRecognitionRequest *recognitionRequest;
@property (nonatomic, strong) SFSpeechRecognitionTask *recognitionTask;
@property (nonatomic, strong) AVAudioEngine *audioEngine;
@property (nonatomic, strong) UITextView *textView;
@property (nonatomic, strong) UIButton *recordButton;
@property (nonatomic, strong) NSTimer *timer;
@property (nonatomic) BOOL sent;
@property (nonatomic) BOOL done;

@end

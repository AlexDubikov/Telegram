//
//  SpeechRecognitionController.m
//  SpeechRecognition
//
//  Created by Ilya Tsarev on 22.04.2018.
//  Copyright © 2018 Ilya Tsarev. All rights reserved.
//

#import "SpeechRecognitionController.h"
#import "SpeechRecognizer.h"
#import "SpeechSynthesizer.h"

@interface SpeechRecognitionController ()

@property (strong, nonatomic) SpeechRecognizer *speechRecognizer;
@property (strong, nonatomic) SpeechSynthesizer *speechSynthesizer;
@property (strong, nonatomic) CALayer *animatedLayer;

@end

@implementation SpeechRecognitionController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self prepareUI];
    [self prepareSpeechRecognizer];
    [self prepareSpeechSynthesizer];
}

- (void)prepareUI {
    self.recognizeButton.layer.cornerRadius = self.recognizeButton.frame.size.width / 2.0;
    [self showRecognitionAnimation:NO];
    
    [self.speechTextView addObserver:self
                          forKeyPath:@"contentSize"
                             options:(NSKeyValueObservingOptionNew)
                             context:NULL];
    
    self.speechTextView.text = @"Tap «+» and say\nsomething to a\nnearby driver";
}

- (void)prepareSpeechRecognizer {
    self.speechRecognizer = [[SpeechRecognizer alloc] initWithLocale:[NSLocale localeWithLocaleIdentifier:@"en-US"]];
    
    [self.speechRecognizer requestAuthorization:^(BOOL isAuthorized) {
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            if (isAuthorized) {
                [self enableRecognizeButton];
            } else {
                [self disableRecognizeButton];
            }
        }];
    }];
}

- (IBAction)sendLike:(id)sender {
    [self.delegate didSendLike];
}

- (IBAction)sendDislike:(id)sender {
    [self.delegate didSendDislike];
}

- (void)prepareSpeechSynthesizer {
    self.speechSynthesizer = [[SpeechSynthesizer alloc] initWithLocale:@"en-US"];
}


- (void)showText:(NSString *)text withPronunciation:(BOOL)usePronunciation {
    self.speechTextView.text = [NSString stringWithFormat:@"«%@»", text];
    
    if (usePronunciation == YES) {
        [self.speechSynthesizer synthesizeText:text];
    }
}

- (IBAction)recogniseSpeech:(id)sender {
    [self.delegate didBeginRecognition];

    self.speechTextView.text = @"";
    [self showRecognitionAnimation:YES];
    
    __weak SpeechRecognitionController* weakSelf = self;
    [self.speechRecognizer startRecognition:^(NSString *recognizedString, BOOL isFinal) {
        weakSelf.speechTextView.text = [NSString stringWithFormat:@"«%@...»", recognizedString];
        if (isFinal) {
            weakSelf.speechTextView.text = [NSString stringWithFormat:@"«%@»", recognizedString];
            [weakSelf showRecognitionAnimation:NO];
            [weakSelf.delegate didRecognize:recognizedString];
        }
    }];
}

- (void)showRecognitionAnimation:(BOOL)animate {
    if (animate) {
        [self disableRecognizeButton];
        [self.statusLabel setHidden:NO];
        [self startRecognizeButtonAnimation];
    } else {
        [self.statusLabel setHidden:YES];
        [self enableRecognizeButton];
        [self stopRecognizeButtonAnimation];
    }
}

- (void)startRecognizeButtonAnimation {
    
    float animationTime = 1.5f;
    
    CABasicAnimation *opacityAnimation = ({
        CABasicAnimation *animation = [CABasicAnimation animationWithKeyPath:@"opacity"];
        animation.duration = animationTime;
        animation.repeatCount = HUGE_VALF;
        [animation setTimingFunction:[CAMediaTimingFunction functionWithName: kCAMediaTimingFunctionEaseInEaseOut]];
        animation.fromValue = [NSNumber numberWithFloat:1.0];
        animation.toValue = [NSNumber numberWithFloat:0.0];
        animation;
    });

    CABasicAnimation *scaleAnimation = ({
        CABasicAnimation *animation = [CABasicAnimation animationWithKeyPath:@"transform.scale"];
        animation.duration = animationTime;
        animation.repeatCount = HUGE_VALF;
        [animation setTimingFunction:[CAMediaTimingFunction functionWithName: kCAMediaTimingFunctionEaseInEaseOut]];
        animation.fromValue = [NSNumber numberWithFloat:1.0];
        animation.toValue = [NSNumber numberWithFloat:3.0];
        animation;
    });

    
    CGFloat layerRadius = self.recognizeButton.bounds.size.height;
    self.animatedLayer = [CALayer layer];
    //TODO: Не работает с авторотейтом
    self.animatedLayer.frame = self.recognizeButton.frame;
    self.animatedLayer.cornerRadius = layerRadius / 2.0;
    self.animatedLayer.backgroundColor = [UIColor whiteColor].CGColor;
    
    [self.animatedLayer addAnimation:opacityAnimation forKey:@"animateOpacity"];
    [self.animatedLayer addAnimation:scaleAnimation forKey:@"animateScale"];
    
    [self.view.layer insertSublayer:self.animatedLayer below:self.recognizeButton.layer];
}

- (void)stopRecognizeButtonAnimation {
    [self.animatedLayer removeAllAnimations];
    [self.animatedLayer removeFromSuperlayer];
    _animatedLayer = nil;
}

- (void)enableRecognizeButton {
    self.recognizeButton.enabled = YES;
}

- (void)disableRecognizeButton {
    self.recognizeButton.enabled = NO;
}

-(void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    
    // Should work
    UITextView *tv = object;
    CGFloat topCorrect = ([tv bounds].size.height - [tv contentSize].height * [tv zoomScale])/2.0;
    topCorrect = ( topCorrect < 0.0 ? 0.0 : topCorrect );
    tv.contentOffset = (CGPoint){.x = 0, .y = -topCorrect};
}

@end

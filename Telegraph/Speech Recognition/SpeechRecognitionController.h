//
//  SpeechRecognitionController.h
//  SpeechRecognition
//
//  Created by Ilya Tsarev on 22.04.2018.
//  Copyright © 2018 Ilya Tsarev. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol SpeechRecognitionControllerDelegate
@optional
- (void)didRecognize:(NSString *)text;
- (void)didSendLike;
- (void)didSendDislike;
- (void)didBeginRecognition;
@end



@interface SpeechRecognitionController : UIViewController <SpeechRecognitionControllerDelegate>

@property(weak, nonatomic) id <SpeechRecognitionControllerDelegate> delegate;
@property (weak, nonatomic) IBOutlet UIButton *recognizeButton;
@property (weak, nonatomic) IBOutlet UIButton *likeButton;
@property (weak, nonatomic) IBOutlet UIButton *dislikeButton;
@property (weak, nonatomic) IBOutlet UILabel *statusLabel;
@property (weak, nonatomic) IBOutlet UITextView *speechTextView;

- (void)showText:(NSString *)text withPronunciation:(BOOL)usePronunciation;

@end

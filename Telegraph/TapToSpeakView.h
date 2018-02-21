//
//  TapToSpeakView.h
//  Telegraph
//
//  Created by Alexander Dubikov on 21/02/2018.
//

#import <UIKit/UIKit.h>
#import <YSKRecognizerViewController.h>

@interface TapToSpeakView : UIView

@property (nonatomic, strong) YSKRecognizerViewController *controller;

@end

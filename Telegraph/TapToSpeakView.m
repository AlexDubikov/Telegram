//
//  TapToSpeakView.m
//  Telegraph
//
//  Created by Alexander Dubikov on 21/02/2018.
//

#import "TapToSpeakView.h"
#import <YandexSpeechKit/SpeechKit.h>

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
    _controller = [[YSKRecognizerViewController alloc] initWithLanguage:YSKRecognitionLanguageEnglish model:YSKRecognitionModelGeneral];
    _controller.view.frame = self.bounds;
    _controller.view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;

    [self addSubview:_controller.view];
}

@end

//
//  ProgressView.h
//  SpeechRecognition
//
//  Created by Ilya Tsarev on 27.05.2018.
//  Copyright © 2018 Ilya Tsarev. All rights reserved.
//

#import <UIKit/UIKit.h>

IB_DESIGNABLE
@interface ProgressView : UIView

@property (nonatomic) IBInspectable CGFloat lineWidth;
@property (nonatomic) IBInspectable UIColor *progressColor;
@property (nonatomic) IBInspectable UIColor *circleColor;
@property (nonatomic) IBInspectable CGFloat progress;

@end

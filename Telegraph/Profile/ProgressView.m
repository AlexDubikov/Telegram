//
//  ProgressView.m
//  SpeechRecognition
//
//  Created by Ilya Tsarev on 27.05.2018.
//  Copyright © 2018 Ilya Tsarev. All rights reserved.
//

#import "ProgressView.h"

@implementation ProgressView

-(void)setProgress:(CGFloat)progress {
    _progress = progress;
    [self setNeedsDisplay];
}

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
    
    CGFloat radius = rect.size.width / 2.0 - self.lineWidth / 2.0;
    CGFloat startAngle = -M_PI_2;
    
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    CGContextFillPath(ctx);
    
    const CGFloat *circleColorComponents = CGColorGetComponents(self.circleColor.CGColor);
    CGContextSetStrokeColor(ctx, circleColorComponents);
    CGContextAddArc(ctx,
                    self.bounds.size.width / 2.0,
                    self.bounds.size.height / 2.0,
                    radius,
                    startAngle,
                    startAngle + 2*M_PI,
                    NO);
    
    CGContextSetLineWidth(ctx, self.lineWidth);
    CGContextDrawPath(ctx, kCGPathStroke);
    
    const CGFloat *progressColorComponents = CGColorGetComponents(self.progressColor.CGColor);
    CGContextSetStrokeColor(ctx, progressColorComponents);
    CGContextAddArc(ctx,
                    self.bounds.size.width / 2.0,
                    self.bounds.size.height / 2.0,
                    radius,
                    startAngle,
                    startAngle + self.progress*2*M_PI,
                    NO);
    
    CGContextSetLineWidth(ctx, self.lineWidth);
    CGContextDrawPath(ctx, kCGPathStroke);
}

CGFloat ToRadians(CGFloat degrees) {
    return degrees * M_PI / 180;
};

@end

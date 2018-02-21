//
//  MySpinTouchInjection.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Henning Thöle on 11.04.13.
//  Copyright (c) 2013 Bosch SoftTec GmbH. All rights reserved.
//

#ifndef __MYSPINSERVERSDK_TOUCHINJECTION_H__
#define __MYSPINSERVERSDK_TOUCHINJECTION_H__

#import "MySpinTouch.h"

#pragma mark- MySpinTouchDelegate

/**
 Implement this protocol to receive touches injected from mySPIN TouchInjection.
*/
@protocol MySpinTouchDelegate <NSObject>

@optional
/**
 Implement this message to handle touch events on custom controls.
 @param touches array of MySpinTouch objects
 @return YES if the touch events were handled on this control. NO if the touch events should be propagated to child controls.
 @deprecated This method is deprecated. Use `[touchesBegan:withTouchEvents:]`, `[touchesMoved:withTouchEvents:]`, `[touchesEnded:withTouchEvents:]` and `[touchesCancelled:withTouchEvents:]` instead.
 @see MySpinTouch class
*/
- (BOOL)handleTouchEvents:(nonnull NSArray<MySpinTouch*>*)touches __attribute((deprecated("mySPIN Platform")));

/**
 Method to tell the receiver when new multi-touch events down arrived
 @param touches is an array of all new touch down events
 @param touchEvents is an array of all ongoing touch events
 @see MySpinTouch class
*/
- (void)touchesBegan:(nonnull NSArray<MySpinTouch*>*)touches withTouchEvents:(nonnull NSArray<MySpinTouch*>*)touchEvents;

/**
 Method to tell the receiver when multi-touch events moved
 @param touches is an array of all new touch move events
 @param touchEvents is an array of all ongoing touch events
 @see MySpinTouch class
*/
- (void)touchesMoved:(nonnull NSArray<MySpinTouch*>*)touches withTouchEvents:(nonnull NSArray<MySpinTouch*>*)touchEvents;

/**
 Method to tell the receiver when multi-touch events ended
 @param touches is an array of all new touch up events
 @param touchEvents is an array of all ongoing touch events
 @see MySpinTouch class
*/
- (void)touchesEnded:(nonnull NSArray<MySpinTouch*>*)touches withTouchEvents:(nonnull NSArray<MySpinTouch*>*)touchEvents;

/**
 Method to tell the receiver when multi-touch events cancelled
 @param touches is an array of all new touches which have been cancelled
 @param touchEvents is an array of all ongoing touch events
 @see MySpinTouch class
*/
- (void)touchesCancelled:(nonnull NSArray<MySpinTouch*>*)touches withTouchEvents:(nonnull NSArray<MySpinTouch*>*)touchEvents;

@end

#endif

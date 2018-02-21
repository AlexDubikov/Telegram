//
//  MySpinGestureRecognizer.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Ebrahim Ameen on 06.06.13.
//  Copyright (c) 2013 Bosch SoftTec GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

#ifndef __MYSPINSERVERSDK_INTERNAL_H__
#define __MYSPINSERVERSDK_INTERNAL_H__

/**
 MySpin specific subclass of UIGestureRecognizer. The standard UIGestureRecognizer subclasses do not work in connected MySpin mode. Use our custom subclasses of MySpinGestureRecognizer instead.
 */
@interface MySpinGestureRecognizer : UIGestureRecognizer

@end

/**
MySpinTapGestureRecognizer Interface
*/
@interface MySpinTapGestureRecognizer : MySpinGestureRecognizer

/**
The number of taps for the gesture to be recognized.
@return numberOfTapsRequired. Default is 1. The number of taps required to match
*/
@property (nonatomic) NSUInteger numberOfTapsRequired;

/**
The number of fingers required to tap for the gesture to be recognized.
@return numberOfTouchesRequired. Default is 1. The number of fingers required to match
*/
@property (nonatomic) NSUInteger numberOfTouchesRequired;

@end

/**
MySpinLongPressGestureRecognizer Interface
*/
@interface MySpinLongPressGestureRecognizer : MySpinGestureRecognizer

/**
The number of full taps required before the press for gesture to be recognized.
@return numberOfTapsRequired. Default is 0.
*/
@property (nonatomic) NSUInteger numberOfTapsRequired;

/**
The number of fingers required to tap for the gesture to be recognized.
@return numberOfTouchesRequired. The default number of fingers is 1.
*/
@property (nonatomic) NSUInteger numberOfTouchesRequired;

/**
Time in seconds the fingers must be held down for the gesture to be recognized
@return minimumPressDuration. Default is 0.5.
*/
@property (nonatomic) CFTimeInterval minimumPressDuration;

/**
Maximum movement in pixels allowed before the gesture fails. Once recognized (after minimumPressDuration) there is no limit on finger movement for the remainder of the touch tracking
@return allowableMovement. Default is 10 points.
*/
@property (nonatomic) CGFloat allowableMovement;

@end

/**
Interface MySpinSwipeGestureRecognizer
*/
@interface MySpinSwipeGestureRecognizer : MySpinGestureRecognizer

/**
The number of fingers that must swipe
@return numberOfTouchesRequired. default is 1.
*/
@property (nonatomic) NSUInteger numberOfTouchesRequired;

/**
The desired direction of the swipe. multiple directions may be specified if they will result in the same behavior
(for example, UITableView swipe delete)
@return direction. Default is UISwipeGestureRecognizerDirectionRight.
*/
@property (nonatomic) UISwipeGestureRecognizerDirection direction;

@end


/**
MySpinPanGestureRecognizer is a concrete subclass of MySpinGestureRecognizer that looks for panning/dragging gestures. The user has to press one or several fingers on the view while they pan it. Lifting the last finger ends the gesture.
*/
@interface MySpinPanGestureRecognizer : MySpinGestureRecognizer

/**
The maximum number of fingers that can be touching the view for this gesture to be recognized.
 
@discussion The default value is NSUIntegerMax.
*/
@property (nonatomic) NSUInteger maximumNumberOfTouches;


/**
The minimum number of fingers that need to be touching the view for this gesture to be recognized.
 
@discussion The default value is 1.
*/
@property (nonatomic) NSUInteger minimumNumberOfTouches;

/**
Sets the translation value in the coordinate system of the specified view.
Changing the translation value resets the velocity of the pan.
 @param translation A point that identifies the new translation value
 @param view The translation is set to occur relative to this views coordinate system.
*/
- (void)setTranslation:(CGPoint)translation inView:(nullable UIView*)view;

/**
The translation of the pan gesture in the coordinate system of the specified view. 
Apply the translation value to the state of the view when the gesture is first
recognized—do not concatenate the value each time the handler is called.
@param view The view in whose coordinate system the translation of the pan gesture should be computed.
If you want to adjust a view's location to keep it under the user's finger,
request the translation in that view's superview's coordinate system.
@discussion The translation point reports the total panning translation in the reference view over time. It is not offset value from the last time.
*/
- (CGPoint)translationInView:(nullable UIView*)view;

/**
The velocity of the pan gesture in the coordinate system of the specified view,
which is expressed in points per second.
@param view The view in whose coordinate system the translation of the pan gesture should be computed.
@discussion any updates on the translation value leads to update in the velocity of the pan gesture.
*/
- (CGPoint)velocityInView:(nullable UIView*)view;

@end


/**
Interface MySpinRotationGestureRecognizer

When the user moves the fingers opposite each other in a circular motion,
the underlying view should rotate in a corresponding direction and speed.

Rotation is a continuous gesture. It begins when two touches have moved
enough to be considered a rotation. The gesture changes when a finger
moves while the two fingers are down. It ends when both fingers have lifted.

If more than two fingers touched, only the moves of the first two touched down
fingers will be used to determine a rotation.
*/
@interface MySpinRotationGestureRecognizer : MySpinGestureRecognizer

/**
The rotation of the gesture in radians.
setting the rotation resets the velocity.
The rotation value is a single value that varies over time.
It is not the delta value from the last time that the rotation was reported.
*/
@property (nonatomic) CGFloat rotation;

/** The velocity of the rotation gesture in radians per second. The velocity is read only. */
@property (nonatomic, readonly) CGFloat velocity;

@end

/**
 MySpinPinchGestureRecognizer is a gesture recognizer implementation that dedicated for mySPIN platform which looks for pinching gestures involving two touches.
 The Pinch generates change in the scale and velocity of finger movements. The Pinch state begins when two touches have moved enough to be considered as a pinch, 
 while state changes repeated as long as the fingers move remain down. The End state triggerd when both fingers have lifted the view.
 */
@interface MySpinPinchGestureRecognizer : MySpinGestureRecognizer

/** 
 The scale value is the value that generated relatively from the touch points in the screen coordinates.
 @discussion The scale value is an absolute value that varies over time. It is not the delta value from the last time that the scale was reported.
 */
@property (nonatomic) CGFloat scale;

/** The velocity of the pinch touches in scale/second. */
@property (nonatomic,readonly) CGFloat velocity;

@end

#endif

//
//  MySpinTouch.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Jan Rose on 29.09.15.
//  Copyright © 2015 Bosch SoftTec GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

@class MSAPersistentTouchInfo;

/** Different touch-event types */
typedef NS_ENUM(NSInteger, ETouchEventType)
{
   /** constant for finger down state */
   TouchEvent_Down,
   /** constant for finger released state */
   TouchEvent_Up,
   /** constant for finger moving state */
   TouchEvent_Moved,
   /** constant for touch is cancel state. Touch has moved out of the view or window. */
   TouchEvent_Cancel,
   /** constant for finger is still down but no change in the location */
   TouchEvent_Stationary,
};

/**
 Encapsulates a MySPIN.ServerSDK touchevent.
 */
@interface MySpinTouch : NSObject
/**
 Touch Position
 */
@property CGPoint Position;

/**
 Touch Inection Type
 */
@property ETouchEventType Type;

/**
 Touch Unique ID
 */
@property int UniqueID;

/**
 Touch Timestamp
 */
@property NSTimeInterval Timestamp;

/**
 Count of Taps on the View
 */
@property int TapCount;

@end


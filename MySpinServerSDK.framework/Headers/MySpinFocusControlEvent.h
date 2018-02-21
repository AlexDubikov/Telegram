//
//  MySpinFocusControlEvent.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Kai Gräper on 27.04.16.
//  Copyright © 2016 Bosch SoftTec GmbH. All rights reserved.
//
#import <Foundation/Foundation.h>

/**
 A key received from the IVI. Up/Down/Left/Right are only received on a 4-way D-Pad and previous/next only on a vehicle which supports 2-way.
 */
typedef NS_ENUM(UInt8, MySpinFocusKeyCode)
{
   MySpinFocusKeyCodeUp          = 0,
   MySpinFocusKeyCodeDown        = 1,
   MySpinFocusKeyCodeLeft        = 2,
   MySpinFocusKeyCodeRight       = 3,
   MySpinFocusKeyCodeOk          = 4,
   MySpinFocusKeyCodeBack        = 5,
   MySpinFocusKeyCodePrevious    = 6,
   MySpinFocusKeyCodeNext        = 7,
   MySpinFocusKeyCodeKnobTickCW  = 100,
   MySpinFocusKeyCodeKnobTickCCW = 101,
};

/**
 The action of a corresponding key. The IVI might send Press/Release (and Longpress) or a simple Click depending on the available hardware. Both scenarios should be handled by your UI.
 @discussion 
 The IVI usually would send sequences of events in the form of MySpinFocusKeyActionPress followed by a MySpinFocusKeyActionRelease. If the time between Press and Release exceeds a certain threshold the sequence will be extended by MySpinFocusKeyActionLongPress into MySpinFocusKeyActionPress -> MySpinFocusKeyActionLongPress -> MySpinFocusKeyActionRelease. The time-interval between Press and Longpress may differ between IVI manufacturers but will be consistent across all apps on that platform.
 Other types of IVIs do not support Press/Release due to hardware limitations. These IVIs will just send a MySpinFocusKeyActionClick which can be treated as an immediate sequence of Press/Release.
 */
typedef NS_ENUM(UInt16, MySpinFocusKeyAction)
{
   MySpinFocusKeyActionPress        = 1,
   MySpinFocusKeyActionRelease      = 2,
   MySpinFocusKeyActionLongPress    = 3,
   MySpinFocusKeyActionClick        = 4,
   MySpinFocusKeyActionAbort        = 6,
};

/**
 The combined information for a focus control event.
 */
@interface MySpinFocusControlEvent : NSObject

/** A timestamp only for comparison between other focus control events within the same connection. */
@property (nonatomic, readonly) NSTimeInterval timestamp;

/** The key received from the IVI. */
@property (nonatomic, readonly) MySpinFocusKeyCode keyCode;

/** The action event corresponding to the key, which caused the event. */
@property (nonatomic, readonly) MySpinFocusKeyAction keyAction;

@end

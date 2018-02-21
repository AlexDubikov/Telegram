//
//  MySpinInputManager.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Jan Rose on 28.04.16.
//  Copyright © 2016 Bosch SoftTec GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MySpinFocusControlEvent.h"

/**
 Every IVI that supports focus control contains a Back and a OK button. In addition they have one of the following options:
 - a knob which can rotate (counter-) clockwise
 - two buttons which correspond to previous/next
 - 4 way D-Pad with up/down/left/right
 It may be reasonable to show different layouts depending on this capability. E.g. on a collection view a singe line/row should be used when only 2 directions can be entered. And multiple lines/rows can be used if the connected system can send 4 directions in order to reduce the necessary clicks.
 */
typedef NS_OPTIONS(NSUInteger, MySpinFocusControlCapability)
{
   MySpinFocusControlCapabilityNone     = 0,
   MySpinFocusControlCapabilityKnob2Way = 1,
   MySpinFocusControlCapabilityKey2Way  = 2,
   MySpinFocusControlCapabilityKey4Way  = 4,
};

/**
 Key events for focus controlled interfaces will be delivered through this protocol.
 Set the [MySpinInputManager sharedInstance].focusControlDelegate to receive events.
 */
@protocol MySpinFocusControlDelegate<NSObject>

@required

/**
 The given delegate received an FocusControlEvent of the given type
 @param event MySpinFocusControlEvent
 */
- (void)handleFocusEvent:(nonnull MySpinFocusControlEvent*)event;

@end

@interface MySpinInputManager : NSObject

/**
 @return The singleton instance
 */
+ (nonnull MySpinInputManager*)sharedInstance;

/**
 The delegate for the focus control events.
 Every time a new control event is received the delegate method handleFocusEvent: will be called.
 @discussion Events will not be delivered to the focusControlDelegate while modal mySPIN views such as keyboard and alertviews are displayed.
 */
@property (weak, atomic, nullable) id<MySpinFocusControlDelegate> focusControlDelegate;

#pragma mark input capabilities

/**
 @return The input capabilities provided by the connected IVI.
 */
- (MySpinFocusControlCapability)keyInputCapabilities;

@end

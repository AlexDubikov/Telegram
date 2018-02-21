//
//  MySpinKeyboardProtocol.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Jan Rose on 09.01.15.
//  Copyright (c) 2015 Bosch SoftTec GmbH. All rights reserved.
//

#ifndef MySpinServerSDK_MySpinKeyboardProtocol_h
#define MySpinServerSDK_MySpinKeyboardProtocol_h

#import <UIKit/UIKit.h>

#import "MySpinKeyboardDelegate.h"

typedef NS_ENUM(NSUInteger, MySpinKeyboardType)
{
   MySpinKeyboardTypeCharacterSet = 0,
   MySpinKeyboardTypeNumberSet = 1,
   MySpinKeyboardTypeAlternativeSet = 2,
};

typedef NS_ENUM(NSUInteger, MySpinKeyboardShiftType)
{
   MySpinKeyboardShiftTypeOff = 0,
   MySpinKeyboardShiftTypeOn = 1,
   MySpinKeyboardShiftTypeCapsLock = 2,
};


/** Type definition for the mySPIN.Keyboard representation of the return key type. */
typedef NS_ENUM(NSUInteger, MySpinKeyboardReturnKeyType)
{
   MySpinKeyboardReturnKeyTypeGo = 0,
   MySpinKeyboardReturnKeyTypeDone = 1,
   MySpinKeyboardReturnKeyTypeNext = 2,
   MySpinKeyboardReturnKeyTypePrevious = 3,
   MySpinKeyboardReturnKeyTypeSearch = 4,
   MySpinKeyboardReturnKeyTypeOk = 5,
};

/**
 Common protocol for all MySPIN keyboards, either internal or external keyboards provided by external libraries.
 */
@protocol MySpinKeyboardProtocol <NSObject>

@required

/** UIView with all buttons of the keyboard. Needs to include all required keyboard views (i.e. input suggestions and other additional UI elements) as subviews. */
@property (strong, readonly, nonnull) UIView* keyboardView;

/** Unique ID of the keyboard. External keyboards delivered as libraries should use reverse-DNS notation. */
@property (readonly, strong, nonnull) NSString* keyboardID;

/** The write direction of the Keyboard, the default is UITextWritingDirectionLeftToRight. */
@property (readonly) UITextWritingDirection writingDirection;

/** Reference to the UI element with text-content that is currently edited by the keyboard view. */
@property (weak, nullable) id<UITextInput> textWidget;

/** Handles submit (enter-key), switch to different keyboard layout, and other actions triggered by a keyboard. */
@property (weak, nullable) id<MySpinKeyboardDelegate> delegate;

/** The type of keyboard layout (CharacterSet, Numberset, ...) */
@property MySpinKeyboardType keyboardType;

/** The current state of the shift-button (On, Off, CapsLock).*/
@property MySpinKeyboardShiftType shiftType;

/**
 Returns the suitable translated text for the return button on the keyboard and should match the UITextField's return
 key type.

 @param type The keyboard's return key type which should match the UITextField's return key type
 @return Returns the text which should be presented to the user on the return button
 */
- (nullable NSString*)returnKeyStringForType:(MySpinKeyboardReturnKeyType)type;

@optional

/**
 Invoked by ServerSDK when the keyboard is about to be displayed.
 */
- (void)keyboardWillShow;

/**
 Invoked by ServerSDK when the keyboard is displayed.
 */
- (void)keyboardDidShow;

/**
 Invoked by ServerSDK when the keyboard is about to be hidden.
 */
- (void)keyboardWillHide;

/**
 Invoked by ServerSDK when the keyboard was hidden.
 */
- (void)keyboardDidHide;

- (void)selectionDidChange;

- (void)textDidChange;

/**
 Retrieve an information dictionary from the previous keyboard e.g focus control highlight
 @param info Information from the previous keyboard
 */
- (void)handleInformationFromPreviousKeyboard:(nullable NSDictionary*)info;

@end


#endif

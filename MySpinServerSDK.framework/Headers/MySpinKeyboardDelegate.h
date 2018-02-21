//
//  MySpinKeyboardDelegate.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Jan Rose on 09.01.15.
//  Copyright (c) 2015 Bosch SoftTec GmbH. All rights reserved.
//

#ifndef MySpinServerSDK_MySpinKeyboardDelegate_h
#define MySpinServerSDK_MySpinKeyboardDelegate_h

/**
 Interface for keyboard implementations to switch between layouts and access additional SDK states required by the keyboard.
 */
@protocol MySpinKeyboardDelegate <NSObject>

/**
 Screenspace available for keyboard layout.
 */
@property (readonly) CGSize availableSize;

/**
 Are there any additional keyboard layouts to switch to. This should be used to enable/disable the button to switch between keyboard layouts.
 */
@property (readonly) BOOL hasAdditionalKeyboardLayouts;

/**
 Tells the SDK to hide the keyboard. Should be called when the 'hide'-Button of the keyboard was clicked.
 */
- (void)hideKeyboard;

/**
 Tells the SDK to switch to the next keyboard layout available.
 @param info An info dictionary with additional information for the next keyboard. The information depend on the keyboard.
 @discussion Calling this method will do nothing if no additional keyboard layouts are available.
 */
- (void)changeToNextKeyboardWithInfo:(nullable NSDictionary*)info;

/**
 Tells the SDK to switch to the next keyboard layout available.
 @deprecated First deprecated in SDK 2.2. Please use changeToNextKeyboardWithInfo:, now.
 @discussion Calling this method will do nothing if no additional keyboard layouts are available.
 */
- (void)changeToNextKeyboard __deprecated;

/**
 Tells the SDK that the submit/enter/search/... button was clicked.
 */
- (void)keyboardDidSubmit;

/**
 Asks the different delegate-methods that need to be called to make sure the keyboard is allowed to replace the text in the given text-range
 @param widget the UITextInput object that is edited
 @param range the UITextRange that should be replaced with new text
 @param text the text that should replace the current content of the range
 @return YES if the replacement should be done, NO if the delegates said we should not replace
 */
- (BOOL)textWidget:(nonnull id<UITextInput>)widget shouldChangeTextInRange:(nonnull UITextRange*)range replacementText:(nullable NSString*)text;

@end

#endif

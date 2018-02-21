//
//  MySpinActionSheet.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Roland Adler on 19.09.13.
//  Copyright (c) 2013 Bosch SoftTec GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#ifndef __MYSPINACTIONSHEET_H__
#define __MYSPINACTIONSHEET_H__

@class MySpinActionSheet;

/** @name MySpinActionSheet Delegate */

/**
MySpinActionSheet Delegate.
*/
@protocol MySpinActionSheetDelegate <UIActionSheetDelegate>
@optional

/**
Sent to the delegate when the user clicks a button on an action sheet.
@param mySpinActionSheet The shown MySpinActionSheet
@param buttonIndex The index of the clicked button
*/
- (void)mySpinActionSheet:(nonnull MySpinActionSheet*)mySpinActionSheet clickedButtonAtIndex:(NSInteger)buttonIndex;

/**
Sent to the delegate before an action sheet is canceled.
An action sheet can be canceled at any time by the system—for example, when the user taps the Home button.
@param mySpinActionSheet The shown MySpinActionSheet
*/
- (void)mySpinActionSheetCancel:(nonnull MySpinActionSheet*)mySpinActionSheet;

/**
Sent to the delegate before an action sheet is presented to the user.
@param mySpinActionSheet The shown MySpinActionSheet
*/
- (void)willPresentMySpinActionSheet:(nonnull MySpinActionSheet*)mySpinActionSheet;

/**
Sent to the delegate after an action sheet is presented to the user.
@param mySpinActionSheet The shown MySpinActionSheet
*/
- (void)didPresentMySpinActionSheet:(nonnull MySpinActionSheet*)mySpinActionSheet;  // after animation

/**
Sent to the delegate before an action sheet is dismissed.
@param mySpinActionSheet The shown MySpinActionSheet
@param buttonIndex The index of button which causes the dismissing of the MySpinActionSheet
*/
- (void)mySpinActionSheet:(nonnull MySpinActionSheet*)mySpinActionSheet willDismissWithButtonIndex:(NSInteger)buttonIndex;

/**
Sent to the delegate after an action sheet is dismissed from the screen.
@param mySpinActionSheet The shown MySpinActionSheet
@param buttonIndex The index of button which causes the dismissing of the MySpinActionSheet
*/
- (void)mySpinActionSheet:(nonnull MySpinActionSheet*)mySpinActionSheet didDismissWithButtonIndex:(NSInteger)buttonIndex;  // after animation

@end

/** @name MySpinActionSheet interface */

#pragma mark Button info dictionary keys

NS_ASSUME_NONNULL_BEGIN
/** Title key for OtherButtonsInfo dictionary */
FOUNDATION_EXPORT NSString* const kMySpinActionSheetButtonTitleKey;

/** Subtitle key for OtherButtonsInfo dictionary */
FOUNDATION_EXPORT NSString* const kMySpinActionSheetButtonSubtitleKey;

/** Alignment key for OtherButtonsInfo dictionary */
FOUNDATION_EXPORT NSString* const kMySpinActionSheetButtonTextAlignmentKey;

/** Possible values for kMySpinActionSheetButtonTextAlignmentKey */
FOUNDATION_EXPORT NSString* const kMySpinActionSheetButtonTextAlignmentLeft;
FOUNDATION_EXPORT NSString* const kMySpinActionSheetButtonTextAlignmentRight;
FOUNDATION_EXPORT NSString* const kMySpinActionSheetButtonTextAlignmentCenter;
NS_ASSUME_NONNULL_END

#pragma mark MySpinActionSheet interface

/** MySpinActionSheet interface */
@interface MySpinActionSheet : UIWindow <MySpinActionSheetDelegate>

/** @name MySpinActionSheet properties */

/** Weak reference to MySpinActionSheet delegate */
@property (nonatomic, weak) id<MySpinActionSheetDelegate> _Nullable mySpinActionSheetDelegate;

/** Title of MySpinActionSheet */
@property (nonatomic, copy) NSString* _Nullable title;

/** Number of buttons on MySpinActionSheet */
@property (nonatomic, readonly) NSInteger numberOfButtons;

/**
Index of cancel-button
@return  index if there is cancele button, otherwise, -1.
*/
@property (nonatomic) NSInteger cancelButtonIndex;

/**
Index of destructive-button
@return  index if there is destructive button, otherwise, -1.
*/
@property (nonatomic) NSInteger destructiveButtonIndex;

/**
Index of first-other-button (e.g. OK-Button)
@return  index if there are other buttons, otherwise, -1.
*/
@property (nonatomic, readonly) NSInteger firstOtherButtonIndex;

/** is the MySpinActionSheet visible? */
@property (nonatomic, readonly, getter=isVisible) BOOL visible;

/** @name MySpinActionSheet methods */

/**
Initializing the MySpinActionSheet, parameters equal to UIActionSheet-initialization
@param title the title of MySpinActionSheet
@param delegate the delegate of MySpinActionSheet
@param cancelButtonTitle the title of the cancel-button
@param destructiveButtonTitle the title of the destructive-button
@param otherButtonTitles the title of the other buttons
@param ... additional button titles
@return The initialized MySpinActionSheet instance
*/
- (nonnull instancetype)initWithTitle:(nullable NSString*)title delegate:(nullable id<MySpinActionSheetDelegate>)delegate cancelButtonTitle:(nullable NSString*)cancelButtonTitle destructiveButtonTitle:(nullable NSString*)destructiveButtonTitle otherButtonTitles:(nullable NSString*)otherButtonTitles, ... NS_REQUIRES_NIL_TERMINATION;

/**
Initializing the MySpinActionSheet, parameters equal to UIActionSheet-initialization
@param title the title of MySpinActionSheet
@param delegate the delegate of MySpinActionSheet
@param cancelButtonTitle the title of the cancel-button
@param destructiveButtonTitle the title of the destructive-button
@param otherButtonsInfoDictionaries NSArray of NSDictionaries describing all other buttons through key-value-pairs. Valid keys are kMySpinActionSheetButtonTitleKey, kMySpinActionSheetButtonSubtitleKey, kMySpinActionSheetButtonTextAlignmentKey
@return The initialized MySpinActionSheet instance
*/
- (nonnull instancetype)initWithTitle:(nullable NSString*)title delegate:(nullable id<MySpinActionSheetDelegate>)delegate cancelButtonTitle:(nullable NSString*)cancelButtonTitle destructiveButtonTitle:(nullable NSString*)destructiveButtonTitle otherButtonsInfoDictionaries:(nullable NSArray*)otherButtonsInfoDictionaries;

/**
Adds a button with the title. returns the index (0 based) of where it was added.
Buttons are displayed in the order added.
@param title The title of the button to add
@return Returns the index of the added button
*/
- (NSInteger)addButtonWithTitle:(nonnull NSString*)title;

/**
Adds a button with the title. Returns the index (0 based) of where it was added.
Buttons are displayed in the order added.
@param buttonInfoDictionary NSDictionary with key-value-pairs describing the button to add. Valid keys are kMySpinActionSheetButtonTitleKey, kMySpinActionSheetButtonSubtitleKey, kMySpinActionSheetButtonTextAlignmentKey
@return Returns the index of the added button
*/
- (NSInteger)addButtonWithInfoDictionary:(nullable NSDictionary*)buttonInfoDictionary;

/**
Returns the title of the button at the specified index.
@param buttonIndex The index of the button
@return Returns the title of the button
*/
- (nullable NSString*)buttonTitleAtIndex:(NSInteger)buttonIndex;

/**
Returns a dictionary containing information about the button at the specified index. Possible keys are kMySpinActionSheetButtonTitleKey, kMySpinActionSheetButtonSubtitleKey, kMySpinActionSheetButtonTextAlignmentKey
@param buttonIndex The index of the button
@return Returns the Info dictionary of the button. Valid keys are kMySpinActionSheetButtonTitleKey, kMySpinActionSheetButtonSubtitleKey, kMySpinActionSheetButtonTextAlignmentKey
*/
- (nullable NSDictionary*)buttonInfoDictionaryAtIndex:(NSInteger)buttonIndex;


/** Shows the MySpinActionSheet on the IVI screen*/
- (void)show;

/**
Hides the MySpinActionSheet. Use this method when you need to explicitly dismiss the ActionSheet without user-interaction (it does not need to be called if the user presses on a button)
@param buttonIndex The index of the clicked button
@param animated Not implemented yet, always hides without animation.
*/
- (void)dismissWithClickedButtonIndex:(NSInteger)buttonIndex animated:(BOOL)animated;

@end

#endif

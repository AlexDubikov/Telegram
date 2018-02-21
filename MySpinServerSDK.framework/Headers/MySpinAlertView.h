//
//  MySpinAlertView.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Roland Adler on 06.09.13.
//  Copyright (c) 2013 Bosch SoftTec GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#ifndef __MYSPINALERTVIEW_H__
#define __MYSPINALERTVIEW_H__

@class MySpinAlertView;

/** @name MySpinAlertView Delegate */

/**
MySpinAlertView Delegate
*/
@protocol MySpinAlertViewDelegate <UIAlertViewDelegate>
@optional

/** Called when a button is clicked. The view will be automatically dismissed after this call returns
@param mySpinAlertView the shown MySpinAlertView
@param buttonIndex the index of the clicked button
*/
- (void)mySpinAlertView:(MySpinAlertView* _Nonnull)mySpinAlertView clickedButtonAtIndex:(NSInteger)buttonIndex;

/** Called when we cancel a view programatically. This is not called when the user clicks the cancel button.
@param mySpinAlertView the shown MySpinAlertView
*/
- (void)mySpinAlertViewCancel:(MySpinAlertView* _Nonnull)mySpinAlertView;

/** before showing view
@param mySpinAlertView the shown MySpinAlertView
*/
- (void)willPresentMySpinAlertView:(MySpinAlertView* _Nonnull)mySpinAlertView;

/** after showing view
@param mySpinAlertView the shown MySpinAlertView
*/
- (void)didPresentMySpinAlertView:(MySpinAlertView* _Nonnull)mySpinAlertView;

/** before hiding view
@param mySpinAlertView the shown MySpinAlertView
@param buttonIndex the index of button which causes the dismissing of the MySpinAlertView
*/
- (void)mySpinAlertView:(MySpinAlertView* _Nonnull)mySpinAlertView willDismissWithButtonIndex:(NSInteger)buttonIndex;

/** after hiding view
@param mySpinAlertView the shown MySpinAlertView
@param buttonIndex the index of button which causes the dismissing of the MySpinAlertView
*/
- (void)mySpinAlertView:(MySpinAlertView* _Nonnull)mySpinAlertView didDismissWithButtonIndex:(NSInteger)buttonIndex;

/** Called after edits in any of the default fields added by the style
@param mySpinAlertView the shown MySpinAlertView
@return is first other button enabled
*/
- (BOOL)mySpinAlertViewShouldEnableFirstOtherButton:(MySpinAlertView* _Nonnull)mySpinAlertView;

@end

/** @name MySpinAlertView inteface */

/** MySpinAlertView interface */
@interface MySpinAlertView : UIWindow

/** @name methods and properties */

/**
Initializing the MySpinAlertView with parameters equal to UIAlertView-initialization
@param title the title of MySpinAlertView
@param message the message of MySpinAlertView
@param delegate the delegate of MySpinAlertView
@param cancelButtonTitle the title of the cancel-button
@param otherButtonTitles the title of the other buttons. MySpinAlertView is currently limited to a maximum of 5 items including title, message, cancelButton and other buttons.
@return id the id of the initialized MySpinAlertView

 @discussion This is the Objective-C variant of the initializer. Additional other buttons will be ignored.
*/
- (instancetype _Null_unspecified)initWithTitle:(NSString* _Nullable)title message:(NSString* _Nullable)message delegate:(id<MySpinAlertViewDelegate> _Nullable)delegate cancelButtonTitle:(NSString* _Nullable)cancelButtonTitle otherButtonTitles:(NSString* _Nullable)otherButtonTitles, ... NS_REQUIRES_NIL_TERMINATION;

/**
 Initializing the MySpinAlertView parameters equal to UIALertView-initialization
 @param title the title of MySpinAlertView
 @param message the message of MySpinAlertView
 @param delegate the delegate of MySpinAlertView
 @param cancelButtonTitle the title of the cancel-button
 @param otherButtonTitles the title of the other buttons. MySpinAlertView is currently limited to a maximum of 5 items including title, message, cancelButton and other buttons.
 @return id the id of the initialized MySpinAlertView
 
 @discussion This is the Swift-compatible version of the initializer. To use this initializer with Swift you still need to define the following extension of MySpinAlertView in your app, especially if you want to pass an empty list to parameter otherButtonTitles.
 
     extension MySpinAlertView
     {
          convenience init(title: String?, message: String?, delegate: MySpinAlertViewDelegate?, cancelButtonTitle: String?, otherButtonTitles moreButtonTitles: CVarArgType...)
          {
               let btnsArgs = getVaList(moreButtonTitles)
               self.init(title: title, message: message, delegate: delegate, cancelButtonTitle: cancelButtonTitle, otherButtonTitleArgs: btnsArgs)
          }
     }
 
 However you can not create a MySpinAlertView without otherButtonTitles with that extension. Please use the default init and set all properties afterwards in that case.
 */
- (instancetype _Null_unspecified)initWithTitle:(NSString* _Nullable)title message:(NSString* _Nullable)message delegate:(id<MySpinAlertViewDelegate> _Nullable)delegate cancelButtonTitle:(NSString* _Nullable)cancelButtonTitle otherButtonTitleArgs:(va_list)otherButtonTitles;

/** weak reference on delegate */
@property (nonatomic, weak) id<MySpinAlertViewDelegate> _Nullable mySpinAlertViewDelegate;

/** title of MySpinAlertView */
@property (nonatomic, strong) NSString* _Nonnull title;

/** message(secondary explanation text) of MySpinAlertView */
@property (nonatomic, strong) NSString* _Nonnull message;

/** adds a button with the title. returns the index (0 based) of where it was added. buttons are displayed in the order added.
@param title the title of the button to add
@return returns the index of the addedd button
 @discussion MySpinAlertView is currently limited to a maximum of 5 items including title, message, cancelButton and other buttons. Additional other buttons will be ignored.
*/
- (NSInteger)addButtonWithTitle:(NSString* _Nonnull)title;

/** returns button title at index
@param buttonIndex the index of the button
@return returns the title of the button
*/
- (NSString* _Nullable)buttonTitleAtIndex:(NSInteger)buttonIndex;

/**
 Set the color of an 'other' button at the given index.
 @param otherButtonIndex the index of the button
 @param newOtherButtonColor the new color of a button at a given index
 @return returns YES if button-color was set.
 
 @warning Colors need to be set before the MySpinAlertView is shown
*/
- (BOOL)setOtherButtonColorAtIndex:(NSInteger)otherButtonIndex withColor:(UIColor* _Nonnull)newOtherButtonColor;

/**
 Set the color of the cancel button
 @param newCancelButtonColor the new color of the cancel-button
 @return returns if button-color was set.
 @warning Colors need to be set before the MySpinAlertView is shown
*/
- (BOOL)setCancelButtonColor:(UIColor* _Nonnull)newCancelButtonColor;

/** number of MySpinAlertView-buttons */
@property (nonatomic, readonly, getter=numberOfButtons) NSInteger numberOfButtons;

/** index of cancel-button */
@property (nonatomic, readonly, getter=cancelButtonIndex) NSInteger cancelButtonIndex;

/** index of first-other-button (e.g. OK-Button), if there's no other button it's -1 */
@property (nonatomic, readonly, getter=firstOtherButtonIndex) NSInteger firstOtherButtonIndex;

/** indicator view -> shows a progress indicator view */
@property (nonatomic) BOOL indicatorViewIsVisible;

/** is the MySpinAlertView visible? */
@property (nonatomic, readonly, getter=isVisible) BOOL visible;

/** shows the MySpinAlertView */
- (void)show;

/** hides alert sheet or popup. use this method when you need to explicitly dismiss the alert. it does not need to be called if the user presses on a button.
@param buttonIndex the index of the clicked button
@param animated not implemented now, always not animated
*/
- (void)dismissWithClickedButtonIndex:(NSInteger)buttonIndex animated:(BOOL)animated;


@end

#endif

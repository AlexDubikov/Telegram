//
//  MySpinServerSDK_Class.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Henning Thöle on 26.02.13.
//  Copyright (c) 2013 Bosch SoftTec GmbH. All rights reserved.
//

#ifndef __MYSPINSERVERSDK_CLASS_H__
#define __MYSPINSERVERSDK_CLASS_H__

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import "MySpinLogger.h"
#import "MySpinNavigateToDestination.h"
#import <OpenGLES/EAGL.h>

#pragma mark Constants
#pragma mark -

#pragma mark Keyboard

NS_ASSUME_NONNULL_BEGIN

/**
 Posted immediately before the MySpinKeyboard will be shown.

 The notification object is always nil. Additional information about the keyboard is contained in the userInfo dictionary of the notification.
 Use the following keys to get the location and size of the keyboard from the userInfo dictionary.
 - MySpinKeyboardFrameBeginUserInfoKey
 - MySpinKeyboardFrameEndUserInfoKey
 - MySpinKeyboardAnimationDurationUserInfoKey
 - MySpinKeyboardAnimationCurveUserInfoKey

 @discussion
 The MySpinKeyboard will only show up in connected mode. Therefore you won't receive the notification if mySPIN is not connected.
 */
FOUNDATION_EXPORT NSString* const MySpinKeyboardWillShowNotification;
/**
 Posted after the animation to show the MySpinKeyboard has completed.

 The notification object is always nil. Additional information about the keyboard is contained in the userInfo dictionary of the notification.
 Use the following keys to get the location and size of the keyboard from the userInfo dictionary.
 - MySpinKeyboardFrameBeginUserInfoKey
 - MySpinKeyboardFrameEndUserInfoKey
 - MySpinKeyboardAnimationDurationUserInfoKey
 - MySpinKeyboardAnimationCurveUserInfoKey

 @discussion
 The MySpinKeyboard will only show up in connected mode. Therefore you usually should not receive this method if mySPIN is not connected. In some cases you might still receive this notification if the connection was closed while the keyboard animation was running.
 */
FOUNDATION_EXPORT NSString* const MySpinKeyboardDidShowNotification;
/**
 Posted immediately before the keyboard will change it's frame.

 The notification object is always nil. Additional information about the keyboard is contained in the userInfo dictionary of the notification.
 Use the following keys to get the location and size of the keyboard from the userInfo dictionary.
 - MySpinKeyboardFrameBeginUserInfoKey
 - MySpinKeyboardFrameEndUserInfoKey
 - MySpinKeyboardAnimationDurationUserInfoKey
 - MySpinKeyboardAnimationCurveUserInfoKey

 @discussion
 The MySpinKeyboard will only show up in connected mode. Therefore you usually should not receive this method if mySPIN is not connected.
 */
FOUNDATION_EXPORT NSString* const MySpinKeyboardWillChangeFrameNotification;
/**
 Posted after the keyboard changed it's frame.

 The notification object is always nil. Additional information about the keyboard is contained in the userInfo dictionary of the notification.
 Use the following keys to get the location and size of the keyboard from the userInfo dictionary.
 - MySpinKeyboardFrameBeginUserInfoKey
 - MySpinKeyboardFrameEndUserInfoKey
 - MySpinKeyboardAnimationDurationUserInfoKey
 - MySpinKeyboardAnimationCurveUserInfoKey

 @discussion
 The MySpinKeyboard will only show up in connected mode. Therefore you usually should not receive this method if mySPIN is not connected. In some cases you might still receive this notification if the connection was closed while the keyboard animation was running.
 */
FOUNDATION_EXPORT NSString* const MySpinKeyboardDidChangeFrameNotification;
/**
 Posted immediately before the MySpinKeyboard will be hidden.

 The notification object is always nil. Additional information about the keyboard is contained in the userInfo dictionary of the notification.
 Use the following keys to get the location and size of the keyboard from the userInfo dictionary.
 - MySpinKeyboardFrameBeginUserInfoKey
 - MySpinKeyboardFrameEndUserInfoKey
 - MySpinKeyboardAnimationDurationUserInfoKey
 - MySpinKeyboardAnimationCurveUserInfoKey

 @discussion
 The MySpinKeyboard will only show up in connected mode. Therefore you won't receive the notification if mySPIN is not connected.
 */
FOUNDATION_EXPORT NSString* const MySpinKeyboardWillHideNotification;
/**
 Posted after the animation to hide the MySpinKeyboard has completed.

 The notification object is always nil. Additional information about the keyboard is contained in the userInfo dictionary of the notification.
 Use the following keys to get the location and size of the keyboard from the userInfo dictionary.
 - MySpinKeyboardFrameBeginUserInfoKey
 - MySpinKeyboardFrameEndUserInfoKey
 - MySpinKeyboardAnimationDurationUserInfoKey
 - MySpinKeyboardAnimationCurveUserInfoKey

 @discussion
 The MySpinKeyboard will only show up in connected mode. Therefore you usually should not receive this method if mySPIN is not connected. In some cases you might still receive this notification if the connection was closed while the keyboard animation was running.
 */
FOUNDATION_EXPORT NSString* const MySpinKeyboardDidHideNotification;
/**
 The key for an NSValue object containing a CGRect that identifies the start frame of the keyboard in screen coordinates.
 */
FOUNDATION_EXPORT NSString* const MySpinKeyboardFrameBeginUserInfoKey;
/**
 The key for an NSValue object containing a CGRect that identifies the end frame of the keyboard in screen coordinates.
*/
FOUNDATION_EXPORT NSString* const MySpinKeyboardFrameEndUserInfoKey;
/**
 The key for an NSNumber object containing a double that identifies the duration of the animation in seconds.
 */
FOUNDATION_EXPORT NSString* const MySpinKeyboardAnimationDurationUserInfoKey;
/**
 The key for an NSNumber object containing a UIViewAnimationCurve constant that defines how the keyboard will be animated onto or off the screen.
 */
FOUNDATION_EXPORT NSString* const MySpinKeyboardAnimationCurveUserInfoKey;

#pragma mark VoiceControl

/**
 Invoked when the SDK receives voice control status change notifications. This may be called at any time, even without a previous request.

 Contains a dictionary with two NSNumbers with ints containing the same parameters as voiceControlStatusDidChange:withStatusCode:
 */
FOUNDATION_EXPORT NSString* const kMySpinVoiceControlStatusDidChangeNotification;
FOUNDATION_EXPORT NSString* const kMySpinVoiceControlStatusKey;
FOUNDATION_EXPORT NSString* const kMySpinVoiceControlStatusCodeKey;

/**
 Invoked when the voice support state changes. This may be called at any time. You can query "hasVoiceControlCapability" after receiving this notification to see the current state of the voice control feature.
 */
FOUNDATION_EXPORT NSString* const kMySpinVoiceSupportInfoDidChangeNotification;

/**
 Invoked when the voice support state changes. This may be called at any time. You can query "hasVoiceControlCapability" after receiving this notification to see the current state of the voice control feature.
 */
FOUNDATION_EXPORT NSString* const kMySpinVoiceSupportInfoDidChangeNotification;

#pragma mark iviVersions keys
extern NSString* const kMySpinIVIMainMicroVersionKey;
extern NSString* const kMySpinIVISubMicroVersionKey;
extern NSString* const kMySpinIVICANSignalVersionKey;
extern NSString* const kMySpinIVINameKey;
extern NSString* const kMySpinIVIFirmwareVersionEKey;
extern NSString* const kMySpinIVIFirmwareVersionFKey;

NS_ASSUME_NONNULL_END

@class MySpinCapability;

#pragma mark - Enums

#pragma mark NavigateTo
/**
NavigateTo availability status
*/
typedef NS_ENUM(NSInteger, ENavigateToStatus)
{
   /** The NavigateTo feature can be used. The request will be either handled by another third-party app or by the embedded navigation of the IVI (depends on user preferences selected in the launcher app). */
   NavigateToStatusAvailable,
   /** The NavigateTo feature is not available because the launcher is not compatible. */
   NavigateToStatusIncompatibleLauncher,
   /** The NavigateTo feature can not be used because neither a 3rd-party-app is installed that supports this feature nor embedded navi support is present on the connected IVI. */
   NavigateToStatusNoAppsAvailable,
   /** The NavigateTo feature can not be used right now because mySPIN is currently not connected to an IVI. This value will be returned as well if the SDK has not been started. */
   NavigateToStatusIVINotConnected
};

#pragma mark PhoneCall
/**
PhoneCall status values received as a response to [initiatePhoneCall:withDisplayName:]([MySpinServerSDK initiatePhoneCall:withDisplayName:]) through the [phoneCallStateDidChange:]([MySpinServerSDKDelegate phoneCallStateDidChange:]) delegate method. Please be aware that these values only describe the status of outgoing calls initiated with the MySPIN.ServerSDK.
*/
typedef NS_ENUM(NSInteger, EMySpinPhoneCallStatus)
{
   /** The request to initiate a phone call was received and accepted by IVI */
   MySpinPhoneCallStatusReceived = 1,
   /** The IVI is initiating phone call. */
   MySpinPhoneCallStatusStarted = 2,
   /** The phone call is fully established (ready to talk).*/
   MySpinPhoneCallStatusActive = 3,
   /** The phone call has ended. */
   MySpinPhoneCallStatusEnded = 4,
   /** The phone call is waiting to be accepted by the person being called. */
   MySpinPhoneCallStatusWaiting = 5,
   /** The request to initiate a phone call was rejected by the IVI. Possible reasons (no cell phone coverage, phone is busy, hardware-problems, ...). */
   MySpinPhoneCallStatusRejected = 6
};

#pragma mark VoiceControl
/**
EMySpinVoiceIOConfig configuration options for the VoiceControl feature. For some IVI systems it is possible to only request access to the microphone if you don't need audio input and output. Other IVIs can only grant combined access to audio-in and -out. You might receive MySpinVoiceControlStatusUnavailable together with MySpinVoiceControlStatusCodeVoiceSessionSupportMicAndSpeakersTogetherOnly if you set MySpinVoiceIOConfigMicOnly
*/
typedef NS_ENUM(NSInteger, EMySpinVoiceIOConfig)
{
   /** Request both recording access to the microphone and audio-output. */
   MySpinVoiceIOConfigMicAndSpeaker = 0,
   /** Request recording access to the microphone without audio-output. */
   MySpinVoiceIOConfigMicOnly = 1,
};

/**
 VoiceControlStatus values
 */
typedef NS_ENUM(NSInteger, EMySpinVoiceControlStatus)
{
   /** Voice control is not currently available or not available at all. Check the EMySpinVoiceControlStatusCode-enum for details. */
   MySpinVoiceControlStatusUnavailable = 0,
   /** The microphone is ready and waits for new requests. This does not mean that you can record now, it only means you can request microphone now. Call [MySpinServerSDK requestVoiceControl:] to invoke a request. */
   MySpinVoiceControlStatusIdle = 1,
   /** Sent as a confirmation after starting a request from the app side. Recording can not be started yet. */
   MySpinVoiceControlStatusStartRequested = 2,
   /** Confirmation from the IVI that the microphone is now open and recording can be started. Call [MySpinServerSDK resignVoiceControl] to request the microphone to be closed. */
   MySpinVoiceControlStatusStartRecording = 3,
   /** Stop recording when this status change is received. You must call [MySpinServerSDK closeVoiceControl] after receiving the end request. You will receive this on two occasions: when you manually call [MySpinServerSDK resignVoiceControl], when the IVI requests you to stop recording. In both cases [MySpinServerSDK closeVoiceControl] must be called as a response to this event. In the latter case you will also immediately receive MySpinVoiceControlStatusIdle-status. */
   MySpinVoiceControlStatusEndRequested = 4,
};

/**
 Status codes for voice control status messages
 */
typedef NS_ENUM(NSInteger, EMySpinVoiceControlStatusCode)
{
   /** No constraints on the status. This is the usual ”No error” code. */
   MySpinVoiceControlStatusCodeNoConstraint = 0,
   /** The session cannot be opened, because the phone is currently not connected via Bluetooth Hands-Free-Profile. */
   MySpinVoiceControlStatusCodeHFPUnavailable = 1,
   /** The session cannot be opened, because there is already another session running. */
   MySpinVoiceControlStatusCodeVoiceAlreadyActive = 2,
   /** Opening the audio session failed on the device due to a timeout of the Bluetooth stack. This is usually not recoverable on the smartphone. */
   MySpinVoiceControlStatusCodeTimeout = 3,
   /** The connected IVI does not support voice control. This may not be permanent, but depends entirely on the implementation of the vehicle. */
   MySpinVoiceControlStatusCodeVoiceNotSupported = 101,
   /** Opening the audio session on the smartphone failed. This is usually unrecoverable. */
   MySpinVoiceControlStatusCodeVoiceSessionOpenFailed = 102,
   /** Opening the audio session failed, because the connected device only supports microphone and speaker access at the same time, but the voice request was to open the microphone only. */
   MySpinVoiceControlStatusCodeVoiceSessionSupportMicAndSpeakersTogetherOnly = 103,
   /** Returned when the voice control session was closed on user request, i.e. by calling [MySpinServerSDK resignVoiceControl] */
   MySpinVoiceControlStatusCodeEndUserEvent = 104,
   /** Returned when the voice control session was automatically ended, i.e. through a phone call event. */
   MySpinVoiceControlStatusCodeEndSystemEvent = 105,
};

#pragma mark ConnectionState

/**
 The status of the connection between app and vehicle. The state changes can appear in the following sequence NotConnected <-> ConnectedToVehicle <-> ConnectedWithUI. No other state transitions (shortcuts) possible.
 */
typedef NS_ENUM(NSUInteger, MySpinConnectionState)
{
   /** SDK is currently stopped. No information available about the connection state. */
   MySpinConnectionStateUnknown,
   /** No mySPIN connection to the vehicle*/
   MySpinConnectionStateNotConnected,
   /** mySPIN connection to the vehicle is established but the app is currently not visible */
   MySpinConnectionStateConnectedToVehicle,
   /** mySPIN connection to the vehicle is established and the app is currently visible to the user */
   MySpinConnectionStateConnectedWithUI
};

NS_ASSUME_NONNULL_BEGIN

/**
 Invoked when the SDK enters or leaves the connected state with Boolean Object YES/NO
 @deprecated Deprecated in mySPIN.SDK 2.2 Please use MySpinWillShowConnectedUINotification, MySpinDidShowConnectedUINotification, MySpinWillHideConnectedUINotification, MySpinDidHideConnectedUINotification, MySpinDidConnectToVehicleNotification, MySpinDidDisconnectFromVehicleNotification instead. This notification will be continued to be invoked when the SDK switched to and from the connected UI of your application. It will not be sent if a background connection is established.
 @warning This is only invoked on the transition to and from  ConnectedWithUI state although the name suggests it's invoked on ANY state change.
 */
FOUNDATION_EXPORT NSString* const kMySPINConnectionStateDidChangeNotification __deprecated;

/** Invoked when a connection to the vehicle was established. Transition from NotConnected to ConnectedToVehicle. */
FOUNDATION_EXPORT NSString* const MySpinDidConnectToVehicleNotification;
/** Invoked when the connection to the vehicle was lost. Transition from ConnectedToVehicle to NotConnected. */
FOUNDATION_EXPORT NSString* const MySpinDidDisconnectFromVehicleNotification;
/** Invoked before the connected UI of your application will be shown. Transition from ConnectedToVehicle to ConnectedWithUI. */
FOUNDATION_EXPORT NSString* const MySpinWillShowConnectedUINotification;
/** Invoked after the connected UI of your application was presented to the user. Transition from ConnectedToVehicle to ConnectedWithUI. */
FOUNDATION_EXPORT NSString* const MySpinDidShowConnectedUINotification;
/** Invoked before the connected UI will disappear. Transition from ConnectedWithUI to ConnectedToVehicle. */
FOUNDATION_EXPORT NSString* const MySpinWillHideConnectedUINotification;
/** Invoked after the connected UI did disappear. Transition from ConnectedWithUI to ConnectedToVehicle.*/
FOUNDATION_EXPORT NSString* const MySpinDidHideConnectedUINotification;

NS_ASSUME_NONNULL_END

#pragma mark - Protocol definitions

/** @name mySPIN ServerSDK Delegate */

/** A protocol for delegates of MySpinServerSDK. */
@protocol MySpinServerSDKDelegate <NSObject>

/**
Requests the main UIViewController that will be displayed in disconnect mode.

This method will be called only once on start. To change the viewcontroller later on you can use the [MySpinServerSDK.disconnectedModeViewController]([MySpinServerSDK disconnectedModeViewController]) property.

@see [MySpinServerSDK.disconnectedModeViewController]([MySpinServerSDK disconnectedModeViewController])

@return Your application's rootViewController for disconnected mode.
*/
- (nonnull UIViewController*)viewControllerForDisconnectedMode;

/**
Requests the main view controller of the external/remote screen.

This method will be called only once on first connect. To change the viewcontroller later on you can use the [MySpinServerSDK.connectedModeViewController]([MySpinServerSDK connectedModeViewController]) property.

@see [MySpinServerSDK.connectedModeViewController]([MySpinServerSDK connectedModeViewController])

@param remoteScreenSize dimensions of the remote screen that was connected
@return Your application's rootViewController for the connected IVI Screen.
*/
- (nonnull UIViewController*)viewControllerForConnectedModeOnRemoteScreen:(CGSize)remoteScreenSize;

@optional
/**
Invoked when the SDK enters or leaves the connected state.
@param isConnected YES if the app has connected to an IVI, NO if it has disconnected
 @deprecated Deprecated in mySPIN.SDK 2.2 Please use connectionStateDidChangeFrom:to: instead.
*/
- (void)connectionStateDidChange:(BOOL)isConnected __deprecated;

/**
 Invoked when the mySPIN.SDK changes it's connection state.
 @param oldState The previous connection state that was valid up until now.
 @param newState The new connection state
 */
- (void)connectionStateDidChangeFrom:(MySpinConnectionState)oldState to:(MySpinConnectionState)newState;

/**
Invoked when the SDK receives a phone call state update from the connected IVI. There is currently no
indication to which phone call request this response applies.
@param newPhoneCallState Value of the EMySpinPhoneCallStatus enum indicating which state has been received
*/
- (void)phoneCallStateDidChange:(EMySpinPhoneCallStatus)newPhoneCallState;

/**
Called when the mySPIN ServerSDK detects disconnection from the IVI. Usually this would mean
that the display auto-lock feature of iOS would automatically be enabled again. Implement this
message to override this behaviour.

Implementing this method is only necessary if your application overrides display auto-lock behaviour in disconnected mode.

@return YES, if autolock should be enabled by the SDK (default if you do not implement this method), otherwise return NO.
*/
- (BOOL)shouldEnableAutoLock;

@end

/** MySpinCarStatusDelegate interface object delegate */
@protocol MySpinCarStatusDelegate <NSObject>

@optional
/** Method that is called when a new geo-coordinate data was received from the IVI

@deprecated First deprecated in SDK 1.1. Please use MySpinVehicleDataManager, now.
@param location is the geographic coordinate represented as an NMEA string
*/
- (void)geolocationDidUpdate:(nonnull NSString*)location __deprecated;

/** Method that is called when the daytime has changed or detected.

@deprecated First deprecated in SDK 1.1. Please use MySpinVehicleDataManager, now.
@param isNight YES if the daytime is night, NO if day
*/
- (void)receiveIsNight:(BOOL)isNight __deprecated;

/** Method that is called if the moving state of the car has been changed.

@deprecated First deprecated in SDK 1.1. Please use MySpinVehicleDataManager, now.
@param isMoving YES if the car is moving, NO if it is stationary
*/
- (void)receiveCarIsMoving:(BOOL)isMoving __deprecated;

@end

/** MySpinServicesDelegate interface object delegate */
@protocol MySpinServicesDelegate <NSObject>

@optional

/**
Method that is called if your app was launched by a another mySpin-enabled application to handle a navigation request.
@param destination The destination-object describing the destination of the navigation request. The destination may be described as a geocoordinate or an address with several attributes.
*/
- (void)shouldNavigateToDestination:(nonnull MySpinNavigateToDestination*)destination;

/**
Method will be called by the SDK when the connected device sends voice control status changes. This may be called at any time, even without a previous request.

@param status New Voice control status.
@param statusCode Additional information regarding the new voice control status. Usually limited to EMySpinVoiceControlStatusCode, future versions may pass unexpected values in addition to the defined ones.
*/
- (void)voiceControlStatusDidChange:(EMySpinVoiceControlStatus)status withStatusCode:(EMySpinVoiceControlStatusCode)statusCode;

@end

/** @name mySPIN ServerSDK API */

#pragma mark - MySpinServerSDK class

/**  MySpinServerSDK interface object */
@interface MySpinServerSDK : NSObject

/**
@return the singleton instance
*/
+ (nonnull MySpinServerSDK*)sharedInstance;

/** @name SDK Lifecycle */

/** MySpinServerSDKDelegate */
@property (weak, nullable) id <MySpinServerSDKDelegate> delegate;

/** Car status delegate */
@property (weak, nullable) id <MySpinCarStatusDelegate> carStatusDelegate;

/** Services delegate */
@property (weak, nullable) id <MySpinServicesDelegate> servicesDelegate;

/**
 The connected state of your application. YES if your app is connected to the vehicle.
 @deprecated Deprecated in mySPIN.SDK 2.2. Please use connectionState instead.
 */
@property (readonly) BOOL isConnected __deprecated;

/**
 The state of your applications connection to the vehicle.
 */
@property (readonly) MySpinConnectionState connectionState;

/** @return the externalScreenSize or (0,0) if the screen size is unknown or mySPIN is in disconnected state */
@property (readonly) CGSize externalScreenSize;

/** @return the physical size in mm of the external screen or (0,0) if the physical size is unknown or mySPIN is in disconnected state */
@property (readonly) CGSize physicalExternalScreenSize;

/** Sets/Gets the UIViewController for disconnected mode */
@property (strong, nullable) UIViewController* disconnectedModeViewController;

/** Sets/Gets the UIViewController for connected mode */
@property (strong, nullable) UIViewController* connectedModeViewController;

/** @return the SDK version as a string */
- (nonnull NSString*)sdkVersion;

/** @return the IVI protocol version as a string */
- (nonnull NSString*)protocolVersion;

/** @return the SDK version with protocol number as a string */
- (nonnull NSString*)versionString;

/**
IVI Name, Processor version, CAN Bus version, etc
@deprecated First deprecated in SDK 2.0. Please use iviVersions, now.
@return technical info of the IVI
*/
- (nonnull NSString*)iviInfo __deprecated;

/**
 IVI Name, Processor version, CAN Bus version, etc describing the connected IVI.
 @return versions info of the IVI
 @discussion Not all keys might be available immediately after the connection was established. You can use KVO to observe this dict for any changes in the available values.
 */
- (null_unspecified NSDictionary*)iviVersions;

/**
Starts the activities of the mySPIN ServerSDK
mySPIN will not do anything before this method is called.
*/
- (void)start;

/** Stop mySPIN */
- (void)stop;

/**
Must be set before the SDK can be fully used
@param launchURL is the launch url
*/
- (void)setLaunchURL:(nullable NSURL*)launchURL;

/**
 Activate/deactivate metrics screen which gathers and displays performance statistics of the mySPIN SDK.
 Besides enabling the metrics screen through this property it can also be enabled with a 3-finger triple-tap on the mySPIN connected mode screen on the iPhone.
 */
@property (nonatomic) BOOL metricsEnabled;

/**
 Set logging level

 @param level value @see EMySpinLogLevel enum
 @param component which should be logged. @see EMySpinLogComponent for possible parameter options.
 */
- (void)setLogLevel:(EMySpinLogLevel)level andLogComponents:(EMySpinLogComponent)component;

/**
 Logging

 @param text string to be logged
 @param level is the logging level
 */
- (void)log:(nonnull NSString*)text withLevel:(EMySpinLogLevel)level;

/**
 Performs an app switch back to the mySPIN launcher application that previously launched opened the currently
 running app.

 @note: Only works if this app is connected to a mySPIN IVI and was indeed previously opened from a launcher app.
 If not, this method will do nothing.
 */
- (void)openLauncher;

#pragma mark Phone Call handling

/** @name Phone Call handling */

/**
This method requests the IVI to initiate a phone call to the specified number. This method will first check if
the IVI is capable of initiating a phone call. The actual device used for placing the phone call is undetermined.
If the handset is connected via Hands-Free-Profile, then the handset will be used. If the IVI has its own phone
module or any other network connection, then this may be used.
This method will NOT use the iOS integrated phone call services under any circumstances.

@warning *Important:* initiatePhoneCall dispatches the request to the IVI and returns immediately. If you receive YES as the result of the invocation, do not flood the IVI with requests, doing so will cause a loss of connection.

@param phoneNumber The phone number to call. Must not be nil nor empty.
@param displayName The name or description to be shown on the vehicle IVI screen. Must not be nil nor empty.
@return TRUE if the IVI is capable of placing the phone call, FALSE if otherwise. If there is no connected device or if
the mySPIN Server SDK has not been initiated yet, this function will return FALSE. It will also return FALSE if the display name is empty.
*/
- (BOOL)initiatePhoneCall:(nonnull NSString*)phoneNumber withDisplayName:(nonnull NSString*)displayName;

/**
Checks if any of the connected devices has the capability to initiate phone calls.

@return TRUE if at least one connected device has phone call capabilities. If there is no connected device or if
the mySPIN Server SDK has not been initiated yet, this function will return FALSE.
*/
- (BOOL)hasPhoneCallCapability;

#pragma mark Initiate Navigation

/** @name Initiate Navigation */

/**
* Test the availability of the navigateTo feature. Should be called for appropriate user-feedback before calling the initiateNavigation... methods.
* @return Current availability of the navigateTo feature. See eNavigateToStatus for possible return values
*/
- (ENavigateToStatus)navigateToCapabilityStatus;

/**
Starts a navigation to the specified coordinate. Checks availability of the navigation feature. The return value indicates if the feature is available and the navigation request was initiated or not.

@warning *Important:* initiateNavigation dispatches the request to the IVI and returns immediately. If you receive YES as the result of the invocation, do not flood the IVI with requests, doing so will cause a loss of connection. Instead wait for a response before sending a new request.

@param location The destination location to navigate to.
@param description Short human-readable description of the location (e.g. POI name)
@return YES if an navigation target is available that can handle the navigation request. NO otherwise (no target available or mySPIN not connected)
*/
- (BOOL)initiateNavigationByLocation:(CLLocationCoordinate2D)location andDescription:(null_unspecified NSString*)description;

/**
Starts a navigation request with the provided query params. Checks availability of the navigation feature. The return value indicates if the feature is available and the navigation request was initiated or not.
Not all of the provided parameters need to be set but the navigation app should be able to resolve the query params to a valid navigation target.
Therefore passing only a country or region or just a houseNumber is not a valid use case for this method because it can't be resolved to a proper navigation destination. The language of the query params is not specified.

@warning *Important:* initiateNavigation dispatches the request to the IVI and returns immediately. If you receive YES as the result of the invocation, do not flood the IVI with requests, doing so will cause a loss of connection. Instead wait for a response before sending a new request.

@param country The country (i.e. "uk", "germany", "de", "Canada"...)
@param region The federal state, province or administrative unit below the country
@param city The city (i.e. "Berlin", "London", ...)
@param zip The postcode (zip code) of the address
@param street Name of the street - without the house number
@param crossStreet name of the crossing street if an intersection is the navigation target
@param houseNumber number of the house on the street (i.e. "10", "10 a", "10a", ...)
@param description Short human-readable description of the location (e.g. POI name)

@return YES if an navigation target is available that can handle the navigation request. NO otherwise (no target available or mySPIN not connected)
*/
- (BOOL)initiateNavigationByCountry:(nullable NSString*)country
                             region:(nullable NSString*)region
                               city:(nullable NSString*)city
                            zipCode:(nullable NSString*)zip
                             street:(nullable NSString*)street
                        crossStreet:(nullable NSString*)crossStreet
                        houseNumber:(nullable NSString*)houseNumber
                        description:(nullable NSString*)description;

#pragma mark Vehicle Data

/** @name Vehicle Data */

/**
 This function checks if the connected client is able to send location information (e.g. GPS). The functions returns NO if the client is not connected.

 @return Returns YES if the target sends location information (usually through CoreLocation, but also through mySPIN vehicle data). Returns NO if the target does not send location updates. If this is the case, the phones own location data is your only source for positioning information.
 */
- (BOOL)hasPositionInformationCapability;

#pragma mark Voice Control

/** @name Voice Control */

/**
This function checks if voice control is generally supported by the target. It does NOT mean that voice control is currently accessible. To find out if voice control currently available listen for status change notifications (kMySpinVoiceControlStatusDidChangeNotification) or simply request voice control by calling "requestVoiceControl".
*/
- (BOOL)hasVoiceControlCapability;

/**
This method requests voice control from the connected device. The response is sent via the MySpinServicesDelegate delegate as well as through notifications. The current state of AVAudioSession.category and AVAudioSession.categoryOptions is remembered in case of a successful open of the voice control link, which sets them to CategoryPlayAndRecord and AllowBluetooth. The previous values are restored when closeVoiceControl is called.
 @warning *Important:* requestVoiceControl: dispatches the request to the IVI and returns immediately. Do not flood the IVI with requests, doing so will cause a loss of connection. Instead wait for a response before sending a new request.
 @param voiceIOConfig Can be either MySpinVoiceIOConfigMicOnly if only recording is desired or MySpinVoiceIOConfigMicAndSpeaker if playback is requested as well.
*/
- (void)requestVoiceControl:(EMySpinVoiceIOConfig)voiceIOConfig;

/**
This method sends a hint to the connected device that the app no longer requires voice control. The response is sent via the MySpinServicesDelegate delegate as well as through notifications. The caller should NOT wait for such a response, but instead immediately stop recording and call "closeVoiceControl".
 @warning *Important:* resignVoiceControl dispatches the command to the IVI and returns immediately. Do not flood the IVI with commands, doing so will cause a loss of connection.
 */
- (void)resignVoiceControl;

/**
This method closes the audio session with the IVI. The app must stop recording prior to calling this. The previous values for AVAudioSession.category and AVAudioSession.categoryOptions are restored after this function completes. This function call is equivalent to calling [closeVoiceControlWithNotification:YES], which means the system will notify other apps in the background that the audiosession has ended.
*/
- (void)closeVoiceControl;

/**
 This method closes the audio session with the IVI. The app must stop recording prior to calling this. The previous values for AVAudioSession.category and AVAudioSession.categoryOptions are restored after this function completes. You can configure whether the system should automatically notify other apps that the audio session has ended. If you want to resume audio on your own, you should pass "NO".

 @param notifyOthersOnDeactivation YES will call [AVAudioSession setActive:NO withOptions:AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation], NO will pass 0 as the parameter.
 */
- (void)closeVoiceControlWithNotification:(BOOL)notifyOthersOnDeactivation;

#pragma mark Focus Control

/**
 This function checks if Focus Control is required by the target. This means, the target is ONLY controllable through
 hardware keys or a knob.

 @return Returns true if the current connected target requires Focus Control.
 */
- (BOOL)requiresFocusControl;

/**
 This function checks if the connected target is a TwoWheeler. This means the target is a vehicle with limited
 displaying and controlling capabilities. To guarantee a good user experience, the HMI should be able to be displayed on
 smaller screens and it should be able to be controlled by hardware keys.

 @return Returns true if there is a target connected and the target is a two wheeler vehicle.
 */
- (BOOL)isTwoWheeler;

/**
 This function checks if the connected target is a "Other". This flag is reserved for future use.

 @return Returns true if there is a target connected and the target is an "other" vehicle.
 */
- (BOOL)isOtherVehicle;

#pragma mark - Background connections

/**
 To enable background connections to the IVI this property needs to be set to YES (Default is NO). This property needs to be set before the SDK is started.

 @discussion Activating background connectivity changes the behaviour of the mySPIN.SDK. If you set this property to YES you'll have to manage the start and stop of mySPIN yourself by calling the start and stop methods whenever you want to connect or disconnect to the IVI. Being connected to the IVI will be different from showing the connected UI if you enable this setting. Therefore kMySPINConnectionStateDidChangeNotification is deprecated and the new notifications MySpinDidConnectToVehicleNotification, MySpinDidDisconnectFromVehicleNotification, MySpinWillShowConnectedUINotification and MySpinWillHideConnectedUINotification have been introduced to reflect the new behavior.
 */
@property (nonatomic) BOOL enableBackgroundConnection;

@end

#endif // __MYSPINSERVERSDK_CLASS_H__

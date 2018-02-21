//
//  MySpinLogger.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Henning Thöle on 28.02.13.
//  Copyright (c) 2013 Bosch SoftTec GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
The loglevel specifies the verbositiy of the logging.
*/
typedef NS_ENUM(NSInteger, EMySpinLogLevel)
{
   /** Fatal errors in the SDK. Those errors are usually not recoverable. */
   MySpinLogLevelFatal = 0,
   /** Used to log errors in the SDK. These are usually recoverable by SDK itself. */
   MySpinLogLevelError = 1,
   /** Used to log conditions which may be causing errors later on. */
   MySpinLogLevelWarning = 2,
   /** Logging of protocol states, state-changes and other 'runtime events'. */
   MySpinLogLevelInfo = 3,
   /** detailed information including important property values etc. */
   MySpinLogLevelDebug = 4
};

/**
Logging can be filtered by components of the SDK. The different logging components can be combined to logging groups.
*/
typedef NS_OPTIONS(NSUInteger, EMySpinLogComponent)
{
   /// Main SDK functionality
   MySpinLogComponentSdkMain = 1 << 0,
   /// Capturing of the connected screen contents
   MySpinLogComponentScreenCapturing = 1 << 1,
   /// TouchInjection for UIViews
   MySpinLogComponentTouchInjection = 1 << 2,
   /// mySPIN communication protocol
   MySpinLogComponentMySpinProtocol = 1 << 3,
   /// mySPIN keyboard
   MySpinLogComponentKeyboard = 1 << 4,
   /// Attached IVI-Devices and transport layer
   MySpinLogComponentExternalDevice = 1 << 5,
   /// NavigateTo feature
   MySpinLogComponentNavigateTo = 1 << 6,
   /// PhoneCall functionality
   MySpinLogComponentPhoneCall = 1 << 7,
   /// VoiceControl feature
   MySpinLogComponentVoiceControl = 1 << 8,
   /// ScreenManager
   MySpinLogComponentScreenManager = 1 << 9,
   /// Service for inter app communication
   MySpinLogComponentService = 1 << 10,
   /// ServiceClient in the AppSDK
   MySpinLogComponentServiceClient = 1 << 11,
   /// ServiceCore sitting between the apps and the service
   MySpinLogComponentServiceCore = 1 << 12,
   /// VehicleData functionality
   MySpinLogComponentVehicleData = 1 << 13,
   /// AudioManagement feature
   MySpinLogComponentAudioManagement = 1 << 14,
   /// Analytics Event handling
   MySpinLogComponentAnalytics = 1 << 15,
   /// FocusControl feature
   MySpinLogComponentFocusControl = 1 << 16,


   // component groups

   /// This flag will log no component
   MySpinLogComponentNone = 0,
   /// This flag will log all components
   MySpinLogComponentAll = MySpinLogComponentSdkMain | MySpinLogComponentScreenCapturing | MySpinLogComponentTouchInjection |
                           MySpinLogComponentMySpinProtocol | MySpinLogComponentKeyboard | MySpinLogComponentExternalDevice |
                           MySpinLogComponentNavigateTo | MySpinLogComponentPhoneCall | MySpinLogComponentVoiceControl  |
                           MySpinLogComponentScreenManager | MySpinLogComponentService | MySpinLogComponentServiceClient |
                           MySpinLogComponentServiceCore | MySpinLogComponentVehicleData | MySpinLogComponentAudioManagement |
                           MySpinLogComponentAnalytics | MySpinLogComponentFocusControl ,
   /// This flag will log all mySPIN protocol, devices and transport layer events
   MySpinLogComponentCommunication = MySpinLogComponentMySpinProtocol | MySpinLogComponentExternalDevice | MySpinLogComponentServiceCore,
   /// This flag will log all keyboard and touch input related events
   MySpinLogComponentInput = MySpinLogComponentKeyboard | MySpinLogComponentTouchInjection | MySpinLogComponentFocusControl,
   /// This flag will log all core components of mySPIN
   MySpinLogComponentSystem = MySpinLogComponentSdkMain | MySpinLogComponentScreenCapturing | MySpinLogComponentTouchInjection |
                              MySpinLogComponentMySpinProtocol | MySpinLogComponentScreenManager | MySpinLogComponentService | MySpinLogComponentServiceCore | MySpinLogComponentServiceClient,
   /// This flag will log all mySPIN features (NavigateTo, PhoneCall, ...)
   MySpinLogComponentServices = MySpinLogComponentNavigateTo | MySpinLogComponentPhoneCall | MySpinLogComponentVoiceControl | MySpinLogComponentVehicleData | MySpinLogComponentAudioManagement
};


@interface MySpinLogger : NSObject

// Returns the singleton instance
+ (nonnull MySpinLogger*)sharedInstance;


#pragma mark - Logging

/** @name SDK Logging */

/**
Set logging level ELogLevel. This call is ignored if mySPINConf.conf is present in the documents folder

@param level value of ELogLevel enum
@param components which should be logged. @see EMySpinLogComponent for possible parameter options.
*/
- (void)setLogLevel:(EMySpinLogLevel)level andLogComponents:(NSUInteger)components;

/**
Logging
@param text string to be logged
@param level is the logging level
*/
- (void)log:(nonnull NSString*)text withLevel:(EMySpinLogLevel)level;

/**
 If we're logging to the logfile and this is set to YES, the log will be flushed to the file after every single log statement. Default value is NO
 
 @discussion
 This will be slower and leads to really bad performance if logginglevel is high for all components.
 */
@property (nonatomic) BOOL alwaysFlushToFile;

@end

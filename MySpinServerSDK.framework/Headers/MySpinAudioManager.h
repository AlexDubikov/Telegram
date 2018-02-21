//
//  MySpinAudioManager.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Jan Rose on 22.01.16.
//  Copyright © 2016 Bosch SoftTec GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Audio category for mySPIN audio management.
 */
typedef NS_ENUM(NSUInteger, MySpinAudioType)
{
   /** AudioFocus type is currently unknown (possible reasons: not connected, no audiomanagement capability, ...) */
   MySpinAudioTypeUnknown,
   /** Type does not matter (release) */
   MySpinAudioTypeIgnore,
   /** App never needs audio output (always silent) */
   MySpinAudioTypeSilent,
   /** App generates audio usable as main audio source (music, podcasts, ...) with continous playback */
   MySpinAudioTypeMain,
   /** Short chimes (signals) and announcements (mixable into main source) */
   MySpinAudioTypeChime,
   /** Announcement (with limited duration) that should mute main source but with lower priority than a phonecall. */
   MySpinAudioTypeAnnouncement,
   /** Important announcement that mutes main audio source and has higher priority than a phonecall (e.g. important navigation announcement "leave highway at next exit", not "follow street for 30 kilometers") */
   MySpinAudioTypeCriticalAnnouncement
};

/**
 Status for a given audiomanagement audiofocus request.
 */
typedef NS_ENUM(NSUInteger, MySpinAudioStatus)
{
   /** AudioManagement not available right now. We can not assert that your app is audible but you should be able to start playing nonetheless */
   MySpinAudioStatusUnknown = 0,
   /** The request to get the audiofocus for a given AudioType was rejected */
   MySpinAudioStatusRejected = 2,
   /** The request to get audiofocus for a given AudioType was granted. Audio with the given category can now be played. */
   MySpinAudioStatusOpen = 3,
   /** Audiofocus for a given AudioType was temporarily lost. Focus may resume again with another change to MySpinAudioStatusOpen. You should probably pause playback. */
   MySpinAudioStatusSuspended = 4,
   /** Audiofocus for a given AudioType was lost permanently. You have to call requestAudioFocusWithType:duration: again to gain focus. */
   MySpinAudioStatusClosed = 6
};

/**
 Implement this delegate and set as the MySpinServerSDK audioFocusDelegate to receive changes in your applications audiofocus initiated by the mySPIN audio management.
 */
@protocol MySpinAudioFocusDelegate <NSObject>

@required

/**
 This method will be called to announce changes in your applications mySPIN audio focus state. You can request the audiofocus for a specifiy MySpinAudioType through the MySpinServerSDK requestAudioFocusWithType:duration: method. The result will be delivered through this interface asynchronously.
 @param audioType The audioType that has a changed state.
 @param state The new state for the audio focus type.
 */
- (void)audioFocusStateChangedForType:(MySpinAudioType)audioType toState:(MySpinAudioStatus)state;

@end

/**
 The MySpinAudioManager is a sigleton that you use to request the mySPIN audio focus for your app and later release it.
 
 You should use this class to request the mySPIN audio focus if you're connected to the car. Without using the MySpinAudioManager for audio management your audio might not be audible through the car audio system. Requesting the audio focus through the MySpinAudioManager allows the IVI to mix your audio with other audio sources such as the embedded navigation, radio etc.
 */
@interface MySpinAudioManager : NSObject

/**
 All the audio focus requests should be done through the MySpinAudioManager sharedInstance singleton.
 @return Singleton instance of the MySpinAudioManager
 */
+ (nonnull MySpinAudioManager*)sharedInstance;

/**
 Checks if the connected device has the capability audio managment.
 
 @return TRUE if the connected device has the capability audio management. If there is no connected device or the car does not support the audio management feature this function will return FALSE.
 
 @discussion In general you should not need to use this property. You can just request and release audio focus even without AudioManagement support from the IVI. If the IVI does not support it or is not connected you'll receive MySpinAudioStatusUnknown and can start playing.
 */
- (BOOL)hasAudioManagmentCapability;

/** Delegate for asynchronous updates in the mySPIN audiofocus. */
@property (weak, nullable) id<MySpinAudioFocusDelegate> audioFocusDelegate;

/**
 If you want to play audio while the smartphone is connected to the IVI, you have to request the mySPIN audio focus before starting your playback. The request is executed asynchronously and the result will be announced through the audioFocusDelegate callback.
 
 @param audioType Define the type of audio you want to play (music, a short announcement, alert sound, ...)
 @param duration 0 if you don't know how long you'll need the audio focus for the given type. If you already know the duration of your announcement please announce it here (add some leeway to make sure your audio is not cut off)
 
 @discussion Make sure you've requested the iOS system audiofocus before requesting the mySPIN audiofocus. Wait for the audioFocusDelegate callback before starting your audio playback.
 */
- (void)requestAudioFocusWithType:(MySpinAudioType)audioType duration:(UInt16)duration;

/**
 Announce that you don't need the audiofocus for the given audioType anymore. Will result in a MySpinAudioStatusClosed callback through the audioFocusDelegate.
 
 @param audioType The type of audio you no longer want to play.
 */
- (void)releaseAudioFocusWithType:(MySpinAudioType)audioType;

@end

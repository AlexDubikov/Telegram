//
//  MySpinVehicleDataManager.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Ingo Dellwig on 15.10.14.
//  Copyright (c) 2014 Bosch SoftTec GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MySpinVehicleData.h"

#ifndef __MYSPINVEHICLEDATAMANAGER_H__
#define __MYSPINVEHICLEDATAMANAGER_H__

/**
 Implement this interface if you want to observe VehicleData values by registering with addObserver: of MySpinVehicleDataManager
 */
@protocol MySpinVehicleDataObserverProtocol <NSObject>

@required

/**
This method will be called on the observer by the MySpinVehicleDataManager,
whenever a vehicle data entry changes. The observer can read the new value
via vehicleDataWithKey:

@param key The vehicle data type key.
*/
- (void)vehicleDataDidChangeForKey:(uint32_t)key;

@end

/**
 Access to VehicleData through the MySpinVehicleDataManager singleton. It allows to access the last transmitted values for the different VehicleData types. If continuous updates of values are required they can be observed through the MySpinVehicleDataManager.
 */
@interface MySpinVehicleDataManager : NSObject

/**
@return The singleton instance
*/
+ (nonnull MySpinVehicleDataManager*)sharedInstance;

/**
Check, if vehicle data can be read for a key.

@param key The vehicle data key.
@return NO if access is forbidden or key is unknown
*/
- (BOOL)canAccessVehicleDataWithKey:(uint32_t)key;

/**
Read the last transmitted vehicle data for a key converted to a dictionary. This dictionary may also contain cached data like maximum, minimum and resolution values.

@param key The vehicle data type key.
@return The latest vehicle data available for the given key. This will always return a MySpinVehicleData object even if the key is invalid. If no data is available yet, the status will equal kMySpinVehicleDataStatusUnknown, if the key is invalid the status equals kMySpinVehicleDataStatusAccessDenied
*/
- (nonnull MySpinVehicleData*)vehicleDataWithKey:(uint32_t)key;

/**
Add observer that conforms to MySpinVehicleDataObserverProtocol.
The MySpinVehicleDataManager will call vehicleDataDidChangeForKey: in the
observer every time the value for any key changes. The observer can then read
the value via vehicleDataWithKey:

@param observer The observer that has to be added.
@return success
*/
- (BOOL)addObserver:(nonnull id<MySpinVehicleDataObserverProtocol>)observer;

/**
Add observer for a specific key.
(It doesn't have to conform to MySpinVehicleDataObserverProtocol necessarily.)
The MySpinVehicleDataManager will call the observer's selector every time the
value for the observed key changes. It will pass the vehicle data as parameter
of type MySpinVehicleData.

@param observer The observer that has to be added.
@param selector The selector that will be called. It has to have one argument, which will receive a MySpinVehicleData object.
@param key The key that should be observed.
@return success
*/
- (BOOL)addObserver:(nonnull NSObject*)observer withSelector:(nonnull SEL)selector forVehicleDataKey:(int)key;

/**
Remove the observer for a specific observed key.

@param observer The observer that should be affected.
@param key The key that no longer should be observe.
*/
- (void)removeObserver:(nonnull NSObject*)observer forVehicleDataKey:(uint32_t)key;

/**
Removes the observer for all observed keys.

@param observer The observer that has to be removed.
*/
- (void)removeObserver:(nonnull NSObject*)observer;

/**
Removes *all* observers (observers for specific keys *as well as* observers conforming to the MySpinVehicleDataObserverProtocol, which observe all keys).
*/
- (void)removeAllObservers;

@end

#endif

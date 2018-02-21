//
//  MySpinVehicleData.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Ingo Dellwig on 20.10.14.
//  Copyright (c) 2014 Bosch SoftTec GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef __MYSPINVEHICLEDATA_H__
#define __MYSPINVEHICLEDATA_H__

/// Constant representing the vehicle data status "unknown".
extern NSString* const _Nonnull kMySpinVehicleDataStatusUnknown;

/// Constant representing the vehicle data status "access denied".
extern NSString* const _Nonnull kMySpinVehicleDataStatusAccessDenied;

/**
 A single VehicleData value. The different types are differentiated through the typeKey.
 
 To avoid confusion, here are some terms and notations, we'll use:
 
 Vehicle data comes in different flavors:
 - *vehicle data:* Means vehicle data in general. Any data that is sent via mySPIN vehicle data functionality from the IVI to the app.
 - *MySpinVehicleData:* A single instance of the MySpinVehicleData class.
 - *vehicle data type:* The type of some vehicle data (i.e. the vehicle-is-moving flag or the geolocation)
 
 There are different keys to mention:
 - *type key:* The key, representing the vehicle data type (i.e. VEHICLE DATA KEY GEOLOCATION NMEA or its integer representation 1)
 - *internal key:* The internal key in a MySpinVehicleData object, which is needed to access the value or meta data (i.e. value, status, maximum, ...)
 */
@interface MySpinVehicleData : NSObject <NSCoding>

/**
 ID of the MySpinVehicleData type. 
 A list of all valid type keys can be obtained as a header file which will be updated seperately in future.
 */
@property (nonatomic, readonly) uint32_t typeKey;

/**
 The internal keys of all availiable vehicle data properties.
 @return An array of all internal keys for a specific car data
 */
- (nonnull NSArray<NSString*>*)keys;

/**
 The object for a specific key.
 @return The object for a specific key.
 */
- (nullable id)objectForKey:(nonnull NSString*)key;

@end

#endif // __MYSPINVEHICLEDATA_H__

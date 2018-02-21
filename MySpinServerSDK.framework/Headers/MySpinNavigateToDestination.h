//
//  MySpinNavigateToDestination.h
//  AppSDK
//
//  mySPIN.SDK Version: 2.3.3.110
//
//  Created by Arne Tempelhof on 02/05/14.
//  Copyright (c) 2014 Bosch SoftTec GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

#ifndef __MYSPINNAVIGATETODESTINATION_H__
#define __MYSPINNAVIGATETODESTINATION_H__

/**
 Describes a navigation request through different properties. Not all of the properties are guaranteed to be filled if a MySpinNavigateToDestination is received. Usually the request may either be expressed as a coordinate or a search-query.
 */
@interface MySpinNavigateToDestination : NSObject <NSCoding>



/**
 A 'title' for the navigation request. May contain the name of a person from the contacts app. This can be displayed in the application handling the navigate-to request.
 */
@property (nonatomic, strong, nullable) NSString* destinationDescription;

/**
 Geocoordinate to navigate to.
 */
@property (nonatomic) CLLocationCoordinate2D coordinate;

/**
@name search-query
 
 The following attributes are used to describe an address to navigate to. Not all of the properties are guaranteed to be filled. The language of the fields is not specified either.
 */

/**
 Country of the destination, if known.
 */
@property (nonatomic, strong, nullable) NSString* country;
/**
 Region (i.e 'state' in the United States, 'bundesland' in germany, ...)
 */
@property (nonatomic, strong, nullable) NSString* region;
/**
 Postal-/ZIP-Code, if known.
 */
@property (nonatomic, strong, nullable) NSString* zip;
/**
 City
 */
@property (nonatomic, strong, nullable) NSString* city;
/**
 Street
 */
@property (nonatomic, strong, nullable) NSString* street;
/**
 If the destination is at an intersection this describes the seconds street.
 */
@property (nonatomic, strong, nullable) NSString* crossStreetName;
/**
 Housenumber on the street
 */
@property (nonatomic, strong, nullable) NSString* houseNumber;

@end

#endif

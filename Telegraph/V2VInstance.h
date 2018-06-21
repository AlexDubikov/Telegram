//
//  V2VInstance.h
//  Telegraph
//
//  Created by Alexander Dubikov on 19/04/2018.
//

#import <Foundation/Foundation.h>
#import "V2VController.h"
#import <MapKit/MapKit.h>

@interface V2VInstance : NSObject

+ (instancetype)shared;
- (void)setEnabled;
- (void)activate;
- (void)addIncomingMessage:(NSString*)message fromId:(int)senderId;
@property (nonatomic) int opponentId;
@property (nonatomic) int selfId;

@property (nonatomic) BOOL configured;
@property (nonatomic, strong) UIWindow *window;
@property (nonatomic, strong) V2VController *controller;
@property (nonatomic, strong) CLLocationManager *locationManager;
@property (nonatomic, strong) CLLocation* currentLocation;
@property (nonatomic, strong) CLLocation* lastDistantLocation;

@end

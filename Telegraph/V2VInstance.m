//
//  V2VInstance.m
//  Telegraph
//
//  Created by Alexander Dubikov on 19/04/2018.
//

#import "V2VInstance.h"
#import "V2VController.h"
#import <LegacyComponents/TGLocationUtils.h>
#import "V2VService.h"

@interface V2VInstance() <CLLocationManagerDelegate>
@end

@implementation V2VInstance

+ (instancetype)shared
{
    static V2VInstance* _animator = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _animator = [[V2VInstance alloc] init];
    });
    return _animator;
}

- (void)setEnabled {
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"V2VLoginEnabled"];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (BOOL)enabled {
    return [[NSUserDefaults standardUserDefaults] boolForKey:@"V2VLoginEnabled"];
}

- (void)activate {
    if ([self enabled]) {
        [self configure];
    }
}

- (void)configure {
    if (!_configured) {
        _configured = YES;

        if ([NSThread isMainThread]) {
            [self makeInterface];
        } else {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self makeInterface];
            });
        }
    }
}

- (void)addIncomingMessage:(NSString*)message fromId:(int)senderId toId:(int)receiverId {
    if (senderId != _opponentId && senderId != _selfId) { // smb sent me a message
        _opponentId = senderId;
        _controller.dataSource.messages = [NSMutableArray new];
    } else if (senderId == _selfId && _opponentId != receiverId) { // I'm sending a message to smb
        _opponentId = receiverId;
        _controller.dataSource.messages = [NSMutableArray new];
    }

    if ([NSThread isMainThread]) {
        [_controller addMessage:message from:senderId];
    } else {
        dispatch_async(dispatch_get_main_queue(), ^{
            [_controller addMessage:message from:senderId];
        });
    }
    NSLog(@"%@",message);
}

#define V2V 1

- (void)makeInterface{
    if (V2V) {
        _opponentId = 0;

        self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        _controller = [V2VController new];
        self.window.rootViewController = _controller;
        self.window.alpha = 0.0;
        self.window.windowLevel = UIWindowLevelNormal + 0.5;
        [self.window makeKeyAndVisible];
        self.window.alpha = 1.0;
        [[UIApplication sharedApplication] setIdleTimerDisabled: YES];
        [self requestLocation];
    }
}

- (void)requestLocation {
    _locationManager = [[CLLocationManager alloc] init];
    _locationManager.delegate = self;

    [TGLocationUtils requestAlwaysUserLocationAuthorizationWithLocationManager:_locationManager];
    [_locationManager setDesiredAccuracy:kCLLocationAccuracyHundredMeters];
    [_locationManager startUpdatingLocation];
}

-(void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations {

    CLLocationDistance distance = [locations.lastObject distanceFromLocation:_lastDistantLocation];
    _currentLocation = locations.lastObject;

    if (distance > 100 || distance == -1 || [self timeIntervalFromLastSentLocation] > 120) {
        _lastDistantLocation = _currentLocation;
        [[V2VService shared] sendCurrentCoordinates];
    }
}

- (NSTimeInterval)timeIntervalFromLastSentLocation {
    NSTimeInterval interval = [[NSDate date] timeIntervalSinceDate:_lastDistantLocation.timestamp];
    return interval;
}

@end

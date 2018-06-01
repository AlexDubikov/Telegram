//
//  V2VInstance.m
//  Telegraph
//
//  Created by Alexander Dubikov on 19/04/2018.
//

#import "V2VInstance.h"
#import "V2VController.h"

@implementation V2VInstance

+ (id)shared
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

- (void)addIncomingMessage:(NSString*)message fromId:(uint32_t)senderId {
    if (senderId !=_opponentId) {
        _controller.dataSource.messages = [NSMutableArray new];
        _opponentId = senderId;
    }
    if ([NSThread isMainThread]) {
        [_controller addMessage:message];
    } else {
        dispatch_async(dispatch_get_main_queue(), ^{
            [_controller addMessage:message];
        });
    }
    NSLog(@"%@",message);
}

- (void)addOutgoingMessage:(NSString *)message {

}

#define V2V 1

- (void)makeInterface{
    if (V2V) {
        self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        _controller = [V2VController new];
        self.window.rootViewController = _controller;
        self.window.alpha = 0.0;
        self.window.windowLevel = UIWindowLevelNormal + 0.5;
        [self.window makeKeyAndVisible];
        self.window.alpha = 1.0;
    }
}

@end

//
//  V2VInstance.h
//  Telegraph
//
//  Created by Alexander Dubikov on 19/04/2018.
//

#import <Foundation/Foundation.h>
#import "V2VController.h"

@interface V2VInstance : NSObject
+ (id)shared;
- (void)setEnabled;
- (void)activate;
- (void)addIncomingMessage:(NSString*)message fromId:(uint32_t)senderId;
@property (nonatomic) uint32_t opponentId;
@property (nonatomic) BOOL configured;
@property (nonatomic, strong) UIWindow *window;
@property (nonatomic, strong) V2VController *controller;
@end

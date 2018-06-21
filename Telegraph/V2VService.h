//
//  V2VService.h
//  Telegraph
//
//  Created by Alexander Dubikov on 16/06/2018.
//

#import <Foundation/Foundation.h>
#import <thirdparty/AFNetworking/AFHTTPClient.h>

@interface V2VService: NSObject

@property (nonatomic, strong) AFHTTPClient * client;

-(void)getTelegramIdUsingText:(NSString *)text telegramId:(int)tgId withCompletion:(void (^)(int opponentId))block;

- (void)sendCurrentCoordinates;
- (void)sendRate:(BOOL)good;

+ (instancetype)shared;

@end

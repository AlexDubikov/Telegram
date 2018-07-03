//
//  V2VService.m
//  Telegraph
//
//  Created by Alexander Dubikov on 16/06/2018.
//

#import "V2VService.h"
#import <thirdparty/AFNetworking/AFHTTPRequestOperation.h>
#import "V2VInstance.h"

@implementation V2VService


+ (instancetype)shared
{
    static V2VService* instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [V2VService new];
        [instance configure];
    });
    return instance;
}

- (void)configure {
    self.client = [[AFHTTPClient alloc] initWithBaseURL:[NSURL URLWithString:@"https://v2vmessenger.azurewebsites.net/"]];
}

-(void)getTelegramIdUsingText:(NSString *)text telegramId:(int)tgId withCompletion:(void (^)(int opponentId))block {

    NSMutableDictionary * parameters = [@{
                                  @"message": text,
                                  @"lat": @([[V2VInstance shared] currentLocation].coordinate.latitude),
                                  @"lon": @([[V2VInstance shared] currentLocation].coordinate.longitude)
                                  } mutableCopy];

    if (tgId != 0) {
        parameters[@"telegramId"] = @(tgId);
    }

    [_client getPath:@"api/destinationForMessage"
          parameters:parameters
             success:^(AFHTTPRequestOperation *operation, id responseObject) {
                 NSLog(@"%@",responseObject);
                 NSDictionary *jsonResponse = [NSJSONSerialization JSONObjectWithData:responseObject
                                                                              options:kNilOptions
                                                                                error:nil];
                 NSLog(@"%@ %@",jsonResponse[@"telegramId"], jsonResponse[@"userId"]);
                 block([jsonResponse[@"telegramId"] intValue]);
             }
             failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                 NSLog(@"oops, %@",error);
                 block(0);
             }
     ];
}

- (void)sendCurrentCoordinates {
    NSString * tgID = [NSString stringWithFormat:@"%d",[[V2VInstance shared] selfId]];
    NSDictionary * parameters = @{
                                  @"telegramId": tgID,
                                  @"lat": @([[V2VInstance shared] currentLocation].coordinate.latitude),
                                  @"lon": @([[V2VInstance shared] currentLocation].coordinate.longitude)
                                  };

    [_client postPath:@"api/coordinates"
          parameters:parameters
             success:^(AFHTTPRequestOperation *operation, id responseObject) {
                 NSLog(@"%@",responseObject);
                 NSDictionary *jsonResponse = [NSJSONSerialization JSONObjectWithData:responseObject
                                                                              options:kNilOptions
                                                                                error:nil];
                 NSLog(@"%@",jsonResponse);
             }
             failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                 NSLog(@"oops, %@",error);
             }
     ];
}
- (void)sendRate:(BOOL)good {
    if ([[V2VInstance shared] opponentId] == 0) {
        return;
    }

    NSString * tgID = [NSString stringWithFormat:@"%d",[[V2VInstance shared] opponentId]];

    NSDictionary * parameters = @{
                                  @"telegramId": tgID,
                                  @"rate": @(good ? 1 : -1),
                                  };

    [_client postPath:@"api/rate"
          parameters:parameters
             success:^(AFHTTPRequestOperation *operation, id responseObject) {
                 NSLog(@"%@",responseObject);
                 NSDictionary *jsonResponse = [NSJSONSerialization JSONObjectWithData:responseObject
                                                                              options:kNilOptions
                                                                                error:nil];
                 NSLog(@"%@",jsonResponse);
             }
             failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                 NSLog(@"oops, %@",error);
             }
     ];
}


@end

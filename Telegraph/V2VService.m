//
//  V2VService.m
//  Telegraph
//
//  Created by Alexander Dubikov on 16/06/2018.
//

#import "V2VService.h"
#import "V2VInstance.h"
#import <thirdparty/AFNetworking/AFNetworking.h>
#import <thirdparty/AFNetworking/AFNetworking.h>

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
    [self.client setDefaultHeader:@"Content-Type" value:@"application/json"];
    [self.client setDefaultHeader:@"Accept" value:@"application/json"];

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

    if ([tgID isEqualToString:@"0"]) {
        return;
    }

    NSDictionary * parameters = @{
                                  @"telegramId": tgID,
                                  @"lat": @([[V2VInstance shared] currentLocation].coordinate.latitude),
                                  @"lon": @([[V2VInstance shared] currentLocation].coordinate.longitude)
                                  };

    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:@"https://v2vmessenger.azurewebsites.net/api/coordinates"]];
    [request setHTTPMethod:@"POST"];
    NSDictionary *headers = @{@"Content-Type":@"application/json"};
    [request setAllHTTPHeaderFields:headers];
    [request setHTTPBody:[NSJSONSerialization dataWithJSONObject:parameters
                                                         options:NSJSONWritingPrettyPrinted
                                                           error:nil]];

    AFHTTPRequestOperation * operation = [[AFHTTPRequestOperation alloc] initWithRequest:request];

    [operation setCompletionBlockWithSuccess:^(AFHTTPRequestOperation *operation, __unused id responseObject)
     {
         NSLog(@"%@",responseObject);
         NSDictionary *jsonResponse = [NSJSONSerialization JSONObjectWithData:responseObject
                                                                      options:kNilOptions
                                                                        error:nil];
         NSLog(@"%@",jsonResponse);
     } failure:^(__unused AFHTTPRequestOperation *operation, NSError *error)
     {
         NSLog(@"oops, %@",error);
     }];


    [[NSOperationQueue mainQueue] addOperation:operation];

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

    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:@"https://v2vmessenger.azurewebsites.net/api/rate"]];
    [request setHTTPMethod:@"POST"];
    NSDictionary *headers = @{@"Content-Type":@"application/json"};
    [request setAllHTTPHeaderFields:headers];
    [request setHTTPBody:[NSJSONSerialization dataWithJSONObject:parameters
                                                         options:NSJSONWritingPrettyPrinted
                                                           error:nil]];

    AFHTTPRequestOperation * operation = [[AFHTTPRequestOperation alloc] initWithRequest:request];

    [operation setCompletionBlockWithSuccess:^(AFHTTPRequestOperation *operation, __unused id responseObject)
     {
         NSLog(@"%@",responseObject);
         NSDictionary *jsonResponse = [NSJSONSerialization JSONObjectWithData:responseObject
                                                                      options:kNilOptions
                                                                        error:nil];
         NSLog(@"%@",jsonResponse);
     } failure:^(__unused AFHTTPRequestOperation *operation, NSError *error)
     {
         NSLog(@"oops, %@",error);
     }];


    [[NSOperationQueue mainQueue] addOperation:operation];
}


@end

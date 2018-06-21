//
//  V2VModels.h
//  Telegraph
//
//  Created by Alexander Dubikov on 18/06/2018.
//

#import <Foundation/Foundation.h>

@interface DestinationResponse : NSObject
/**
Идентификатор пользователя в Telegram
 */
@property (nonatomic, strong) NSString * telegramId;

/// Идентификатор пользователя в V2V
@property (nonatomic, strong) NSString * userId;

@end

@interface V2VUser : NSObject
@property (nonatomic, strong) NSString * userId;
@property (nonatomic, strong) NSString * telegramId;
@property (nonatomic, strong) NSString * telegramAlias;
@property (nonatomic, strong) NSString * make;
@property (nonatomic, strong) NSString * model;
@property (nonatomic) double lat;
@property (nonatomic) double lon;
@property (nonatomic, strong) NSString * last_update;
@property (nonatomic) int bad;
@property (nonatomic) int good;


@end


@interface Message : NSObject
/**
Текст
 */
@property (nonatomic, strong) NSString * messageText;

/// от кого
@property (nonatomic, strong) NSString * messageFrom;

/// кому
@property (nonatomic, strong) NSString * messageTo;

@end


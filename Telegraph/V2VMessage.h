//
//  V2VMessage.h
//  Telegraph
//
//  Created by Alexander Dubikov on 01/06/2018.
//

#import <Foundation/Foundation.h>

@interface V2VMessage : NSObject

@property (nonatomic, strong) NSString * text;
@property (nonatomic) BOOL outgoing;
@property (nonatomic, strong) NSString * avatarUrl;

-(instancetype)init:(NSString *)text outgoing:(BOOL)outgoing avatarUrl:(NSString *)avatarUrl;

@end

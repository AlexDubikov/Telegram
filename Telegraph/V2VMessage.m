//
//  V2VMessage.m
//  Telegraph
//
//  Created by Alexander Dubikov on 01/06/2018.
//

#import "V2VMessage.h"

@implementation V2VMessage

-(instancetype)init:(NSString *)text outgoing:(BOOL)outgoing avatarUrl:(NSString *)avatarUrl {
    self = [super init];
    if (self != nil)
    {
        _text = text;
        _outgoing = outgoing;
        _avatarUrl = avatarUrl;
    }
    return self;
}


@end

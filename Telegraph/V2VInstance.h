//
//  V2VInstance.h
//  Telegraph
//
//  Created by Alexander Dubikov on 19/04/2018.
//

#import <Foundation/Foundation.h>

@interface V2VInstance : NSObject
+ (id)shared;
- (void)setEnabled;
- (void)activate;
- (void)addIncomingMessage:(NSString*)message;
@property (nonatomic) BOOL configured;
@property (nonatomic, strong) UIWindow *window;
@end

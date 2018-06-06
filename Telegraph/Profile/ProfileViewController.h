//
//  ProfileViewController.h
//  SpeechRecognition
//
//  Created by Ilya Tsarev on 26.05.2018.
//  Copyright © 2018 Ilya Tsarev. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ProfileViewController : UIViewController

- (void)setName:(NSString *)name car:(NSString *)car plateNumber:(NSString *)plateNumber;
- (void)setAvatarImage:(UIImage *)avatarImage;
- (void)setHappy:(NSUInteger)happy distance:(NSUInteger)distance angry:(NSUInteger)angry;

@end

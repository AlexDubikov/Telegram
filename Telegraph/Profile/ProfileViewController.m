//
//  ProfileViewController.m
//  SpeechRecognition
//
//  Created by Ilya Tsarev on 26.05.2018.
//  Copyright © 2018 Ilya Tsarev. All rights reserved.
//

#import "ProfileViewController.h"
#import "ProgressView.h"

@interface ProfileViewController ()

@property (weak, nonatomic) IBOutlet UIImageView *avatarImageView;
@property (weak, nonatomic) IBOutlet UILabel *nameLabel;
@property (weak, nonatomic) IBOutlet UILabel *carLabel;
@property (weak, nonatomic) IBOutlet UILabel *carPlateLabel;
@property (weak, nonatomic) IBOutlet UILabel *happyLabel;
@property (weak, nonatomic) IBOutlet UILabel *distanceLabel;
@property (weak, nonatomic) IBOutlet UILabel *angryLabel;
@property (weak, nonatomic) IBOutlet ProgressView *progressView;
@property (weak, nonatomic) IBOutlet UILabel *progressLabel;

@end

@implementation ProfileViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)setName:(NSString *)name car:(NSString *)car plateNumber:(NSString *)plateNumber {
    self.nameLabel.text = name;
    self.carLabel.text = car;
    self.carPlateLabel.text = plateNumber;
}

- (void)setAvatarImage:(UIImage *)avatarImage {
    self.avatarImageView.image = avatarImage;
}

- (void)setHappy:(NSUInteger)happy distance:(NSUInteger)distance angry:(NSUInteger)angry {
    self.happyLabel.text = [NSString stringWithFormat:@"%lu", (unsigned long)happy];
    self.distanceLabel.text = [NSString stringWithFormat:@"%lu km", (unsigned long)distance];
    self.angryLabel.text = [NSString stringWithFormat:@"%lu", (unsigned long)angry];
    
    CGFloat currentProgress = (CGFloat)happy / (CGFloat)(happy + angry);
    self.progressLabel.text = [NSString stringWithFormat:@"%.0f%%", currentProgress * 100];
    self.progressView.progress = currentProgress;
}

- (IBAction)dismiss:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)logout:(id)sender {
    NSLog(@"logout called");
}

@end

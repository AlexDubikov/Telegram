//
//  V2VController.m
//  Telegraph
//
//  Created by Alexander Dubikov on 18/04/2018.
//

#import "V2VController.h"

@interface V2VController ()

@end

@implementation V2VController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self configure];
    // Do any additional setup after loading the view.
}

-(void)configure {
    self.view.backgroundColor = [UIColor colorWithRed:22.0/255.0 green:22.0/255.0 blue:28.0/255.0 alpha:1];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(UIStatusBarStyle)preferredStatusBarStyle {
    return UIStatusBarStyleLightContent;
}


@end

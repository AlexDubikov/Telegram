//
//  V2VController.m
//  Telegraph
//
//  Created by Alexander Dubikov on 18/04/2018.
//

#import "V2VController.h"
#import "V2VTableDatasource.h"

static const CGFloat topBarHeight = 64;
static const CGFloat bottomOffset = 100;
static const CGFloat tapToSpeakButtonSize = 50;

@interface V2VController ()

@property (nonatomic, strong) UIView * navBar;
@property (nonatomic, strong) UITableView * table;
@property (nonatomic, strong) UIButton * tapToSpeakButton;
@property (nonatomic, strong) UIButton * leftButton;
@property (nonatomic, strong) UIButton * rightButton;
@property (nonatomic, strong) V2VTableDatasource * dataSource;

@end

@implementation V2VController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self configure];
    // Do any additional setup after loading the view.
}

- (void)configureDataSource {

}

- (UIView*)makeNavigationBar {
    UIView* view = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, topBarHeight)];
    view.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    view.backgroundColor = [UIColor colorWithRed:170/255.0 green:89/255.0 blue:254/255.0 alpha:1];
    return view;
}

- (UITableView*)makeTable {
    UITableView* view = [[UITableView alloc] initWithFrame:CGRectMake(0, topBarHeight, self.view.frame.size.width, self.view.frame.size.height - topBarHeight)];
    view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    view.backgroundColor = [UIColor redColor];
    view.dataSource = _dataSource;
    view.delegate = _dataSource;
    return view;
}

- (UIButton*)makeTapToSpeakButton {
    UIButton* button = [[UIButton alloc] initWithFrame:CGRectMake(self.view.bounds.size.width / 2 - tapToSpeakButtonSize/2, self.view.bounds.size.height - bottomOffset, tapToSpeakButtonSize, tapToSpeakButtonSize)];
    button.backgroundColor = [UIColor blackColor];
    return button;
}

- (UIButton*)makeLeftButton {
    UIButton* button = [[UIButton alloc] initWithFrame:CGRectMake(self.view.bounds.size.width / 5 - tapToSpeakButtonSize/2, self.view.bounds.size.height - bottomOffset, tapToSpeakButtonSize, tapToSpeakButtonSize)];
    button.backgroundColor = [UIColor blackColor];
    return button;
}

- (UIButton*)makeRightButton {
    UIButton* button = [[UIButton alloc] initWithFrame:CGRectMake(4 * self.view.bounds.size.width / 5 - tapToSpeakButtonSize/2, self.view.bounds.size.height - bottomOffset, tapToSpeakButtonSize, tapToSpeakButtonSize)];
    button.backgroundColor = [UIColor blackColor];
    return button;
}

- (void)viewDidLayoutSubviews {
//    self.navBar.frame = CGRectMake(0, 0, self.view.frame.size.width, topBarHeight);
    self.tapToSpeakButton.frame = CGRectMake(self.view.bounds.size.width / 2 - tapToSpeakButtonSize/2, self.view.bounds.size.height - bottomOffset, tapToSpeakButtonSize, tapToSpeakButtonSize);
    self.leftButton.frame = CGRectMake(self.view.bounds.size.width / 5 - tapToSpeakButtonSize/2, self.view.bounds.size.height - bottomOffset, tapToSpeakButtonSize, tapToSpeakButtonSize);
    self.rightButton.frame = CGRectMake(4 * self.view.bounds.size.width / 5 - tapToSpeakButtonSize/2, self.view.bounds.size.height - bottomOffset, tapToSpeakButtonSize, tapToSpeakButtonSize);
}

-(void)configure {
    self.navBar = [self makeNavigationBar];
    self.table = [self makeTable];
    self.tapToSpeakButton = [self makeTapToSpeakButton];
    self.leftButton = [self makeLeftButton];
    self.rightButton = [self makeRightButton];

    [self.view addSubview:_navBar];
    [self.view addSubview:_table];
    [self.view addSubview:_tapToSpeakButton];
    [self.view addSubview:_leftButton];
    [self.view addSubview:_rightButton];

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

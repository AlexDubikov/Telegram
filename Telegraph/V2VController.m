//
//  V2VController.m
//  Telegraph
//
//  Created by Alexander Dubikov on 18/04/2018.
//

#import "V2VController.h"
#import "V2VDialogCell.h"
#import "V2VMessage.h"
#import "V2VInstance.h"

#import "TGInterfaceManager.h"
#import "TGDatabase.h"

#import <LegacyComponents/LegacyComponents.h>

#import "FMDatabase.h"

#import "ATQueue.h"

#import "TGTimer.h"

#import "TGTelegraph.h"
#import "TGAppDelegate.h"

#import <LegacyComponents/ActionStage.h>
#import <LegacyComponents/SGraphObjectNode.h>

#import <LegacyComponents/TGCache.h>
#import <LegacyComponents/TGRemoteImageView.h>

#import <SSignalKit/SSignalKit.h>

#import "TGPreparedLocalDocumentMessage.h"

#import "TGGlobalMessageSearchSignals.h"

#import "TGSpotlightIndexData.h"

#import <MobileCoreServices/MobileCoreServices.h>

#import "TGModernSendSecretMessageActor.h"

#import "TGTelegramNetworking.h"
#import "TGConversationAddMessagesActor.h"

#import "TGChannelList.h"

#import "TGMediaCacheIndexData.h"


#import "TGRemoteRecentPeer.h"
#import "TGRemoteRecentPeerSet.h"
#import "TGRemoteRecentPeerCategories.h"

#import "TGMessageViewedContentProperty.h"

#import "TGInterfaceManager.h"
#import "TGRecentGifsSignal.h"
#import "TGRecentStickersSignal.h"

#import "TGGroupManagementSignals.h"

#import "TGCdnData.h"

#import "TGAudioMediaAttachment+Telegraph.h"
#import "TGUser+Telegraph.h"

#import "TGUnseenPeerMentionsState.h"
#import "TGUnseenPeerMentionsMessageIdsState.h"

#import "V2VService.h"

static const CGFloat bottomOffset = 100;
static const CGFloat tapToSpeakButtonSize = 60;

@interface V2VController ()

@property (nonatomic, strong) UIView * navBar;
@property (nonatomic, strong) UIButton * tapToSpeakButton;
@property (nonatomic, strong) UIButton * leftButton;
@property (nonatomic, strong) UIButton * rightButton;
@property (nonatomic, strong) SpeechRecognitionController * controller;
@end

@implementation V2VController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self configure];
    // Do any additional setup after loading the view.
}

- (CGFloat)topBarHeight {
    if (UIDeviceOrientationIsPortrait([[UIDevice currentDevice] orientation])) {
        if (@available(iOS 11.0, *)) {
            return UIApplication.sharedApplication.keyWindow.safeAreaInsets.top + 64;
        }
    }
    return 64;
}

- (void)configureDataSource {
    _dataSource = [V2VTableDatasource new];
    _dataSource.messages = [NSMutableArray new];
}

- (void)addMessage:(NSString *)message from:(int)sender {

    BOOL senderIsMe = sender == [[V2VInstance shared] selfId];
    
    [_controller showText:message withPronunciation:!senderIsMe];

    V2VMessage* messageObj = [[V2VMessage alloc] init:message outgoing:sender == [[V2VInstance shared] selfId] avatarUrl:nil];
    [_dataSource.messages addObject:messageObj];
    [_table reloadData];
    [_table scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:_dataSource.messages.count - 1 inSection:0]  atScrollPosition:UITableViewScrollPositionBottom animated:YES];
}

- (UIView*)makeNavigationBar {
    UIView* view = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, [self topBarHeight])];
    view.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    view.backgroundColor = [UIColor colorWithRed:170/255.0 green:89/255.0 blue:254/255.0 alpha:1];
    return view;
}

- (UITableView*)makeTable {
    UITableView* table = [[UITableView alloc] initWithFrame:CGRectMake(0, [self topBarHeight], self.view.frame.size.width, self.view.frame.size.height - [self topBarHeight] - bottomOffset * 2)];
    table.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    table.backgroundColor = [UIColor clearColor];
    table.dataSource = _dataSource;
    table.delegate = _dataSource;
    table.separatorStyle = UITableViewCellSeparatorStyleNone;
    [table registerClass:[V2VDialogCell class] forCellReuseIdentifier:@"reuseID"];
    return table;
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
    _navBar.frame = CGRectMake(0, 0, self.view.frame.size.width, [self topBarHeight]);
    _table.frame = CGRectMake(0, [self topBarHeight], self.view.frame.size.width, self.view.frame.size.height - bottomOffset * 2);
    self.tapToSpeakButton.frame = CGRectMake(self.view.bounds.size.width / 2 - tapToSpeakButtonSize/2, self.view.bounds.size.height - bottomOffset, tapToSpeakButtonSize, tapToSpeakButtonSize);
    self.leftButton.frame = CGRectMake(self.view.bounds.size.width / 5 - tapToSpeakButtonSize/2, self.view.bounds.size.height - bottomOffset, tapToSpeakButtonSize, tapToSpeakButtonSize);
    self.rightButton.frame = CGRectMake(4 * self.view.bounds.size.width / 5 - tapToSpeakButtonSize/2, self.view.bounds.size.height - bottomOffset, tapToSpeakButtonSize, tapToSpeakButtonSize);
    CGRect frame = self.view.frame;
    self.controller.view.frame = CGRectMake(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
}

-(void)configure {
    [self configureDataSource];

    self.navBar = [self makeNavigationBar];
//    self.view.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"car_bg"]];
    self.view.layer.contents = (id)[UIImage imageNamed:@"car_bg"].CGImage;

    self.table = [self makeTable];
    self.controller = [SpeechRecognitionController new];
    self.controller.delegate = self;

    [self.view addSubview:_controller.view];
    [self.view addSubview:_table];
    [self addChildViewController:_controller];

    self.tapToSpeakButton = _controller.recognizeButton;
    self.leftButton = _controller.likeButton;
    self.rightButton = _controller.dislikeButton;

    [self.view addSubview:_navBar];
    [self.view addSubview:_tapToSpeakButton];
    [self.view addSubview:_leftButton];
    [self.view addSubview:_rightButton];

    [self hideRecognition];

    [_controller.closeButton addTarget:self action:@selector(stopAndHideRecognition) forControlEvents:UIControlEventTouchUpInside];
}

- (void)recognitionToFront {
    [self.view bringSubviewToFront:_controller.view];
    [UIView animateWithDuration:0.3 animations:^{
        _controller.view.hidden = NO;
    }];
}

- (void)recognitionButtonToFront {
    [self.view bringSubviewToFront:_tapToSpeakButton];
}

- (void)stopAndHideRecognition {
    [_controller.speechRecognizer stopRecognition];
    [self hideRecognition];
}

- (void)hideRecognition {
    _controller.view.hidden = YES;
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(UIStatusBarStyle)preferredStatusBarStyle {
    return UIStatusBarStyleLightContent;
}

-(void)didBeginRecognition {
    [self recognitionToFront];
}


- (void)didRecognize:(NSString *)text {

    TGMessage *message = [[TGMessage alloc] init];
    message.text = [NSString stringWithFormat:@"݆%@",text];

    [[V2VService shared] getTelegramIdUsingText:text telegramId:[[V2VInstance shared] opponentId] withCompletion:^(int opponentId) {

        if (opponentId != 0) {
            [[TGInterfaceManager instance] navigateToConversationWithId:opponentId conversation:nil performActions:@{@"sendMessages": @[message]}];
            [[V2VInstance shared] addIncomingMessage:text fromId:[[V2VInstance shared] selfId] toId:[[V2VInstance shared] opponentId]];
            [self hideRecognition];
        } else {
            _controller.speechTextView.text = @"Couldn't find the car. Probably, it's not registered yet. Invite your friends to get +5 rating for each of them.";
            [self recognitionButtonToFront];
        }
    }];


}


- (void)didSendLike {
    TGMessage *message = [[TGMessage alloc] init];
    message.text = @"☺️";
    [[V2VService shared] sendRate:YES];
    [[V2VInstance shared] addIncomingMessage:@"☺️" fromId:[[V2VInstance shared] selfId] toId:[[V2VInstance shared] opponentId]];
}

- (void)didSendDislike {
    TGMessage *message = [[TGMessage alloc] init];
    message.text = @"😡";
    [[V2VService shared] sendRate:NO];
    [[V2VInstance shared] addIncomingMessage:@"😡" fromId:[[V2VInstance shared] selfId] toId:[[V2VInstance shared] opponentId]];
}


@end

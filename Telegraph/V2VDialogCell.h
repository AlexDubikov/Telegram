//
//  V2VDialogCell.h
//  Telegraph
//
//  Created by Alexander Dubikov on 22/04/2018.
//

#import <UIKit/UIKit.h>
#import "TGModernLetteredAvatarView.h"

@interface V2VDialogCell : UITableViewCell

@property (nonatomic, strong) NSString* message;
@property (nonatomic) TGModernLetteredAvatarView* avatarView;
@property (nonatomic, strong) UILabel* messageView;
@property (nonatomic) BOOL incoming;

@end

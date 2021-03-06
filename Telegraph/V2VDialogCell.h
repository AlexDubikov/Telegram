//
//  V2VDialogCell.h
//  Telegraph
//
//  Created by Alexander Dubikov on 22/04/2018.
//

#import <UIKit/UIKit.h>
#import "TGModernLetteredAvatarView.h"

@interface V2VDialogCell : UITableViewCell
+ (CGSize)textSize:(NSString *)text;

@property (nonatomic, strong) NSString* message;
@property (nonatomic) TGModernLetteredAvatarView* avatarView;
@property (nonatomic, strong) UITextView* messageView;
@property (nonatomic) BOOL incoming;

@end

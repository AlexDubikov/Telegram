//
//  V2VDialogCell.m
//  Telegraph
//
//  Created by Alexander Dubikov on 22/04/2018.
//

#import "V2VDialogCell.h"
#import "TGModernLetteredAvatarView.h"

@implementation V2VDialogCell

static const CGFloat marginTextField = 12;
static const CGFloat smallOffset = 3;
static const CGFloat bottomMarginTextField = 30;
static const CGFloat avatarSize = 45;
static const CGFloat avatarMargin = 12;

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        [self createViews];
    }
    return self;
}

- (void)layoutSubviews {
    [super layoutSubviews];

    if (_incoming) {
        [self layoutAsIncoming];
    } else {
        [self layoutAsOutgoing];
    }
}

- (void)createViews {
    _avatarView = [[TGModernLetteredAvatarView alloc] init];
    static UIImage *placeholder = nil;
    static dispatch_once_t onceToken2;
    dispatch_once(&onceToken2, ^
                  {
                      UIGraphicsBeginImageContextWithOptions(CGSizeMake(40.0f, 40.0f), false, 0.0f);
                      CGContextRef context = UIGraphicsGetCurrentContext();

                      //!placeholder
                      CGContextSetFillColorWithColor(context, [UIColor whiteColor].CGColor);
                      CGContextFillEllipseInRect(context, CGRectMake(0.0f, 0.0f, 40.0f, 40.0f));
                      CGContextSetStrokeColorWithColor(context, UIColorRGB(0xd9d9d9).CGColor);
                      CGContextSetLineWidth(context, 1.0f);
                      CGContextStrokeEllipseInRect(context, CGRectMake(0.5f, 0.5f, 39.0f, 39.0f));

                      placeholder = UIGraphicsGetImageFromCurrentImageContext();
                      UIGraphicsEndImageContext();
                  });

    [_avatarView setFirstName:@"first" lastName:@"last" uid:828882 placeholder:placeholder];

    [self addSubview:_avatarView];
    [self addSubview:_messageView];
    _incoming = true;
}

- (void)layoutAsIncoming {
    _avatarView.frame = CGRectMake(0, 0, 50, 50);
}

- (void)layoutAsOutgoing {

}

+ (CGSize)textSize:(NSString *)text {
    NSMutableParagraphStyle *style = [[NSParagraphStyle defaultParagraphStyle] mutableCopy];
    [style setLineBreakMode:NSLineBreakByWordWrapping];

    CGFloat maxWidth = [UIScreen mainScreen].bounds.size.width - avatarMargin * 2 - avatarSize - marginTextField * 3 - smallOffset * 2;


    NSDictionary *sizeAttributes = @{NSFontAttributeName:[UIFont systemFontOfSize:15], NSParagraphStyleAttributeName: style};
    CGSize adjustedSize = CGSizeMake(maxWidth, CGFLOAT_MAX);

    CGRect rect = [text boundingRectWithSize:adjustedSize
                                     options:NSStringDrawingUsesLineFragmentOrigin
                                  attributes:sizeAttributes
                                     context:nil];
    CGFloat minimumWidth = 27;
    if (rect.size.width < minimumWidth) {
        rect.size.width = minimumWidth;
    }

    rect.size.width = ceil(rect.size.width) + 1 + marginTextField * 2;
    rect.size.height = ceil(rect.size.height) + bottomMarginTextField  + marginTextField;

    return rect.size;
}

@end

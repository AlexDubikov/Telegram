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
static const CGFloat smallOffset = 12;
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

-(instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
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
    self.selectionStyle = UITableViewCellSelectionStyleNone;
    _avatarView = [[TGModernLetteredAvatarView alloc] init];
    static UIImage *placeholder = nil;
    static dispatch_once_t onceToken2;
    dispatch_once(&onceToken2, ^
                  {
                      UIGraphicsBeginImageContextWithOptions(CGSizeMake(avatarSize, avatarSize), false, 0.0f);
                      CGContextRef context = UIGraphicsGetCurrentContext();

                      //!placeholder
                      CGContextSetFillColorWithColor(context, [UIColor whiteColor].CGColor);
                      CGContextFillEllipseInRect(context, CGRectMake(0.0f, 0.0f, avatarSize, avatarSize));
                      CGContextSetStrokeColorWithColor(context, UIColorRGB(0xd9d9d9).CGColor);
                      CGContextSetLineWidth(context, 1.0f);
                      CGContextStrokeEllipseInRect(context, CGRectMake(0.5f, 0.5f, avatarSize - 1.0f, avatarSize - 1.0f));

                      placeholder = UIGraphicsGetImageFromCurrentImageContext();
                      UIGraphicsEndImageContext();
                  });

    [_avatarView setFirstName:@"first" lastName:@"last" uid:828882 placeholder:placeholder];

    [self addSubview:_avatarView];

    _messageView = [UITextView new];
    _messageView.scrollEnabled = NO;//нужно чтобы не сворачивалось
    _messageView.textColor = [UIColor blackColor];//дефолтный цвет черный

    _messageView.textContainerInset = UIEdgeInsetsMake(marginTextField, marginTextField, marginTextField, marginTextField);

    _messageView.editable = NO; // Обязательно для работы dataDetectorTypes
    _messageView.dataDetectorTypes = UIDataDetectorTypePhoneNumber | UIDataDetectorTypeLink;

    _messageView.textAlignment = NSTextAlignmentLeft;

    _messageView.linkTextAttributes = @{NSForegroundColorAttributeName: [UIColor whiteColor], NSUnderlineStyleAttributeName: [NSNumber numberWithInt:NSUnderlineStyleSingle]};
    _messageView.font = [UIFont systemFontOfSize:15];
    _messageView.layer.cornerRadius = 8;

    [self addSubview:_messageView];

    self.backgroundColor = [UIColor clearColor];
}

- (void)layoutAsIncoming {
    _avatarView.frame = CGRectMake(marginTextField, marginTextField, avatarSize, avatarSize);
    CGSize rectForSelf = [V2VDialogCell rectForText:self.messageView.text];

    CGFloat bubbleOrigin = avatarMargin * 2 + avatarSize;
    _messageView.backgroundColor = [UIColor colorWithRed:197.0/255 green:255/255.0 blue:179.0/255 alpha:1];

    self.messageView.frame = (CGRect) { bubbleOrigin, smallOffset, rectForSelf.width, rectForSelf.height - smallOffset };

}

- (void)layoutAsOutgoing {

    _avatarView.frame = CGRectMake(self.bounds.size.width - avatarSize - marginTextField, marginTextField, avatarSize, avatarSize);
    CGSize rectForSelf = [V2VDialogCell rectForText:self.messageView.text];

    CGFloat bubbleOrigin = self.bounds.size.width - rectForSelf.width - avatarSize - marginTextField * 2;
    _messageView.backgroundColor = [UIColor whiteColor];

    self.messageView.frame = (CGRect){bubbleOrigin, smallOffset, rectForSelf.width, rectForSelf.height - smallOffset};
}

+ (CGSize)textSize:(NSString *)text {

    CGSize size = [V2VDialogCell rectForText:text];

    if (size.height < marginTextField * 2 + avatarSize) {
        size.height = marginTextField * 2 + avatarSize;
    }

    return size;
}

+ (CGSize)rectForText:(NSString *)text {
    NSMutableParagraphStyle *style = [[NSParagraphStyle defaultParagraphStyle] mutableCopy];
    [style setLineBreakMode:NSLineBreakByWordWrapping];

    CGFloat maxWidth = [UIScreen mainScreen].bounds.size.width - avatarMargin * 2 - avatarSize - marginTextField * 3 - smallOffset * 2 - marginTextField * 2;


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

    rect.size.width = ceil(rect.size.width) + 1 + marginTextField * 4;
    rect.size.height = ceil(rect.size.height) + marginTextField * 2 + smallOffset;

    return rect.size;
}

@end

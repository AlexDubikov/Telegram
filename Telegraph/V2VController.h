//
//  V2VController.h
//  Telegraph
//
//  Created by Alexander Dubikov on 18/04/2018.
//

#import <UIKit/UIKit.h>
#import "V2VTableDatasource.h"
#import "SpeechRecognitionController.h"

@interface V2VController : UIViewController <SpeechRecognitionControllerDelegate>
@property (nonatomic, strong) V2VTableDatasource * dataSource;
@property (nonatomic, strong) UITableView * table;
- (void)addMessage:(NSString *)message;

@end

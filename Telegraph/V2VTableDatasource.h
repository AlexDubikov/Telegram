//
//  V2VTableDatasource.h
//  Telegraph
//
//  Created by Alexander Dubikov on 22/04/2018.
//

#import <Foundation/Foundation.h>
#import "V2VMessage.h"

@interface V2VTableDatasource : NSObject <UITableViewDataSource, UITableViewDelegate>
@property (nonatomic, strong) NSMutableArray<V2VMessage *> * messages;

@end

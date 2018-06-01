//
//  V2VTableDatasource.h
//  Telegraph
//
//  Created by Alexander Dubikov on 22/04/2018.
//

#import <Foundation/Foundation.h>

@interface V2VTableDatasource : NSObject <UITableViewDataSource, UITableViewDelegate>
@property (nonatomic, strong) NSMutableArray * messages;

@end

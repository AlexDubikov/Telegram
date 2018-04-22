//
//  V2VTableDatasource.m
//  Telegraph
//
//  Created by Alexander Dubikov on 22/04/2018.
//

#import "V2VTableDatasource.h"

@interface V2VTableDatasource ()

@end

@implementation V2VTableDatasource

- (nonnull UITableViewCell *)tableView:(nonnull UITableView *)tableView cellForRowAtIndexPath:(nonnull NSIndexPath *)indexPath {
    return [UITableViewCell new];
}

- (NSInteger)tableView:(nonnull UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 2;
}

@end

//
//  V2VTableDatasource.m
//  Telegraph
//
//  Created by Alexander Dubikov on 22/04/2018.
//

#import "V2VTableDatasource.h"
#import "V2VDialogCell.h"

@interface V2VTableDatasource ()

@end

@implementation V2VTableDatasource

- (nonnull UITableViewCell *)tableView:(nonnull UITableView *)tableView cellForRowAtIndexPath:(nonnull NSIndexPath *)indexPath {
    V2VDialogCell *cell = (V2VDialogCell *)[tableView dequeueReusableCellWithIdentifier:@"reuseID"];
    if (cell == nil) {
        cell = [[V2VDialogCell alloc] init];
    }
    cell.messageView.text = [_messages objectAtIndex:indexPath.row].text;
    cell.incoming = ![_messages objectAtIndex:indexPath.row].outgoing;
    return cell;
}

- (NSInteger)tableView:(nonnull UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _messages.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return [V2VDialogCell textSize:_messages[indexPath.row].text].height;
}

@end

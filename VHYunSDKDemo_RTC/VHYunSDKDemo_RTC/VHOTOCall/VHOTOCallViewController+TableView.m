//
//  VHOTOCallViewController+TableView.m
//  VHYunSDKDemo_RTC
//
//  Created by vhall on 2019/12/4.
//  Copyright © 2019 vhall. All rights reserved.
//

#import "VHOTOCallViewController+TableView.h"
#import "VHOTOCallViewController+Call.h"
#import "VHInteractiveTableViewCell.h"

@implementation VHOTOCallViewController (TableView)

- (void)updateUserListData
{
    //只有用户列表显示的情况下才刷新数据
    if (self.tableView.hidden) {
        return;
    }
    __weak typeof(self) wf = self;
    [self getUserList:^(NSArray *userList,NSError* error) {
        if(userList)
        {
            wf.userList = userList;
            [wf.tableView reloadData];
        }
    }];
}


-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.userList.count;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    VHInteractiveTableViewCell *cell =[VHInteractiveTableViewCell  cellWithTableView:tableView];
    cell.isOTOCall = YES;
    cell.item = self.userList[indexPath.row];
    
    __weak typeof(self) wf = self;
    cell.action = ^(NSInteger type, NSDictionary *item) {
        [wf action:type item:item];
    };
    return cell;
}

- (void)action:(NSInteger)type item:(NSDictionary*)item
{
    NSString* third_user_id = item[@"third_party_user_id"];
    int status              = [item[@"status"] intValue]; // 用户状态 1 推流中 2 观看中 3 受邀中 4 申请上麦中
    [self callYou:third_user_id];
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 40;
}

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if ([cell respondsToSelector:@selector(setSeparatorInset:)]) {
        [cell setSeparatorInset:UIEdgeInsetsZero];
    }
    
    if ([cell respondsToSelector:@selector(setLayoutMargins:)]) {
        [cell setLayoutMargins:UIEdgeInsetsZero];
    }
}

@end

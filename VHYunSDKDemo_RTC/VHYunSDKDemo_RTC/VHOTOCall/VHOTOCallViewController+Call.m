//
//  VHOTOCallViewController+call.m
//  VHYunSDKDemo_RTC
//
//  Created by vhall on 2019/12/4.
//  Copyright © 2019 vhall. All rights reserved.
//

#import "VHOTOCallViewController+Call.h"
#import "VHOTOCallViewController+Layout.h"
#import "VHOTOCallViewController+TableView.h"
#import <VHCore/VHMessage.h>

@implementation VHOTOCallViewController (Call)
- (NSDictionary*)renderViewsById
{
    return self.otoCall.renderViewsById;
}

- (void)createRoom
{
    if(!self.otoCall)
    {
        self.otoCall = [[VHOTOCall alloc] init];
        self.otoCall.callDelegate = self;
        self.otoCall.isOnlyAudioSubscribe = YES;
    }
}

- (void)enterRoom
{
    [self createRoom];
    [self.otoCall enterRoomWithRoomId:self.ilssRoomID accessToken:self.accessToken userData:nil];
}

- (BOOL)OTOCall:(const NSString *)third_user_id
{
    return [self.otoCall OTOCall:third_user_id];
}

- (BOOL)OTOAnswer:(BOOL)answer
{
    return [self.otoCall OTOAnswer:answer];
}

- (BOOL)OTOStart
{
    return [self.otoCall OTOStartWithCameraView:self.cameraView];
}

- (BOOL)OTOHangUp
{
    if(self.otoCall.isPublishing)
    {
        return [self.otoCall OTOHangUp];
    }
    return NO;
}

- (void)leaveRoom
{
    [self.otoCall leaveRoom];
}

- (BOOL)getUserList:(void(^)(NSArray* userList,NSError* error)) block
{
    return [self.otoCall inviteUserList:block];
}
#pragma mark - VHOTOCallDelegate

/*
 * 收到呼叫消息
 */
- (void)room:(VHInteractiveRoom *)room receiveCall:(id)msg
{
    VHMessage * msg1 = (VHMessage *)msg;
    [self callMe:msg1.third_party_user_id];
}
 
/*
 * 收到呼叫应答消息
 * answer 0 人员变化 1 上麦 2 下麦 3拒绝上麦
 */
- (void)room:(VHInteractiveRoom *)room receiveAnswer:(int)status msg:(id)msg isMySelf:(BOOL)isMySelf
{
    [self updateUserListData];
    
    if(isMySelf)
        return;
    
    VHMessage * msg1 = (VHMessage *)msg;
    if(status == 1 && self.otoCall.isMainCall)
    {
        [self callAccepted];
    }
    
    if(status == 2 || status == 3)
        [self callStop];
}

/*
 * 他人上麦消息
 */
- (void)room:(VHInteractiveRoom *)room didAddAttendView:(VHRenderView *)attendView
{
    [self addView:attendView attributes:attendView.userId];
    NSLog(@"--- userID: %@; userData %@",attendView.userId,attendView.userData);
}
/*
 * 他人下麦消息
 */
- (void)room:(VHInteractiveRoom *)room didRemovedAttendView:(VHRenderView *)attendView
{
    if( [self.otoCall.cur_third_user_id isEqualToString:attendView.userId])
    {
        [self removeView:attendView];
        [self callStop];
    }
}

#pragma mark - 以下回调可不实现
/*
 * 房间错误回调
 */
- (void)room:(VHInteractiveRoom *)room error:(NSError*)error
{
    
}
/*
 * 房间状态变化
 */
- (void)room:(VHInteractiveRoom *)room didChangeStatus:(VHInteractiveRoomStatus)status
{
    
}

/*
 * 进入互动房间
 */
- (void)room:(VHInteractiveRoom *)room didEnterRoom:(NSString *)third_user_id
{
    [self updateUserListData];
}
/*
 * 离开互动房间
 */
- (void)room:(VHInteractiveRoom *)room didLeaveRoom:(NSString *)third_user_id isKickOutRoom:(BOOL)isKickOut
{
    [self updateUserListData];
}
@end

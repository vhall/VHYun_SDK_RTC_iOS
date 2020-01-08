//
//  VHOTOCallViewController.h
//  VHYunSDKDemo_RTC
//
//  Created by vhall on 2019/12/4.
//  Copyright © 2019 vhall. All rights reserved.
//

#import "VHBaseViewController.h"
#import <VHRTC/VHOTOCall.h>
#import "VHLayoutView_1vN_Pip_Left.h"

NS_ASSUME_NONNULL_BEGIN

@interface VHOTOCallViewController : VHBaseViewController
@property(nonatomic,copy) NSString * ilssRoomID;        //互动房间id
@property(nonatomic,copy) NSString * accessToken;


@property(nonatomic,strong) VHOTOCall *otoCall;
@property (nonatomic,strong) VHRenderView *cameraView;//本地摄像头画面view
@property (nonatomic,strong) NSArray* userList;//在线用户列表

//第一层用户列表
@property (weak, nonatomic) IBOutlet UITableView *tableView;
//第二层呼叫应答view
@property (weak, nonatomic) IBOutlet UIView   *callView;//接收到呼入view
@property (weak, nonatomic) IBOutlet UIButton *acceptBtn;
@property (weak, nonatomic) IBOutlet UIButton *refuseBtn;
@property (weak, nonatomic) IBOutlet UILabel  *callingLabel;
//第三层呼叫层view
@property (weak, nonatomic) IBOutlet UIView *containerView;//画面布局容器
@property (nonatomic,strong) VHLayoutView   *layoutView;//画面布局


- (void)callYou:(NSString*)userid;//主叫别人
- (void)callMe:(NSString*)userid;//电话呼入
- (void)callAccept;//接受呼叫
- (void)callAccepted;//对方已接受呼叫
- (void)callRefuse;//拒绝呼叫
- (void)callStop;//挂断

@end

NS_ASSUME_NONNULL_END

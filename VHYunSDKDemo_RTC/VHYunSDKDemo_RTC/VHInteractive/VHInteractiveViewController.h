//
//  VHInteractiveViewController.h
//  VHInteractive
//
//  Created by vhall on 2018/4/18.
//  Copyright © 2018年 vhall. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <VHRTC/VHInteractiveRoom.h>
#import "VHLayoutView_1vN_Pip_Left.h"
#import "VHBaseViewController.h"

@interface VHInteractiveViewController : VHBaseViewController
@property(nonatomic,copy) NSString * ilssRoomID;        //互动房间id
@property(nonatomic,assign)VHPushType  ilssType;        //摄像头及推流参数设置
@property(nonatomic,copy)NSDictionary* ilssOptions;     //摄像头及推流参数设置

@property(nonatomic,copy) NSString * anotherLiveRoomId; //旁路直播间ID
@property(nonatomic,copy) NSString * accessToken;
@property(nonatomic,copy) NSString * userData;//用户数据 进入房间自定义数据
@property(nonatomic,copy) NSString * streamData;//流数据 推流前放入本地流的自定义数据

@property(nonatomic,assign) VHInteractiveRoomMode mode;//应用场景模式，选填，可选值参考 VHInteractiveRoomMode。支持版本：2.3.2及以上
@property(nonatomic,assign) VHInteractiveRoomRole role;//用户角色，选填，可选值参考下文VHInteractiveRoomRole。当mode为rtc模式时，不需要配置role。支持版本：2.3.2及以上


@property (weak, nonatomic) IBOutlet UIView *containerView;//画面布局容器
@property (nonatomic,strong) VHLayoutView   *layoutView;//画面布局

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (weak, nonatomic) IBOutlet UILabel *onlineNumLabel;
@property (weak, nonatomic) IBOutlet UITextView *infoTextView;


@property (nonatomic,strong) VHRenderView *cameraView;//本地摄像头画面view
@property (nonatomic,strong) NSArray* userList;

@property(nonatomic,strong) VHInteractiveRoom *room;

@property(nonatomic,assign)BOOL isResignActive;//是否进入后台


@property(nonatomic,strong) NSMutableDictionary *infoDict;//线路消息
//房间连接状态并更新UI
- (void)showCallConnectViews:(BOOL)show updateStatusMessage:(NSString *)statusMessage;
//房间视频流状态更新
- (void)updateInfoTextView:(NSString*)text;
//断开与房间的连接弹窗
- (void)showDisConectAlertWithStatusMessage:(NSString *)msg;
//推流成功
- (void)didPublish:(NSString*)streamId;
//结束推流成功
- (void)didUnPublish;
@end

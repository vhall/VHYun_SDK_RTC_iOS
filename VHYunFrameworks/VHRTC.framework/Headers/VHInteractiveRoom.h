//
//  VHInteractiveRoom.h
//  VHInteractive
//
//  Created by vhall on 2018/4/17.
//  Copyright © 2018年 www.vhall.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VHRenderView.h"

#import "VHBroadCastDef.h"

typedef enum : NSUInteger {
    RoomBGCropTypeAspectFit  = 0,       // 等比缩放至画布
    RoomBGCropTypeAspectFill = 1,       // 裁剪图片和画布宽高比一致，再缩放至画布
    RoomBGCropTypeFill       = 2,       // 直接拉伸填满画布 [默认]
} RoomBGCropType;

/// 互动房间状态
typedef NS_ENUM(NSInteger, VHInteractiveRoomStatus) {
    VHInteractiveRoomStatusReady,
    VHInteractiveRoomStatusConnected,
    VHInteractiveRoomStatusDisconnected,
    VHInteractiveRoomStatusError
};

typedef NS_ENUM(NSInteger, VHInteractiveRoomMode) {
    VHInteractiveRoomModeRTC,       // 默认为互动房间 实时通信场景，例如互动连麦
    VHInteractiveRoomModeLive       // 无延迟直播房间 直播场景，例如无延迟直播
};

typedef NS_ENUM(NSInteger, VHInteractiveRoomRole) {
    VHInteractiveRoomRoleHost,      // 可以发布和订阅互动流
    VHInteractiveRoomRoleAudience   // 只能订阅互动流，无法发布
};

// param code 200 success ,otherwise fail;
typedef void(^VhallFinishBlock)(int code, NSString * _Nonnull message);

NS_ASSUME_NONNULL_BEGIN

@class VHInteractiveRoom;
@protocol VHInteractiveRoomDelegate <NSObject>
#pragma mark - 房间信息回调

/// 房间错误回调
- (void)room:(VHInteractiveRoom *)room error:(NSError*)error;

/// 房间状态变化
- (void)room:(VHInteractiveRoom *)room didChangeStatus:(VHInteractiveRoomStatus)status;

/// 进入互动房间
- (void)room:(VHInteractiveRoom *)room didEnterRoom:(NSString *)third_user_id;

/// 离开互动房间
- (void)room:(VHInteractiveRoom *)room didLeaveRoom:(NSString *)third_user_id isKickOutRoom:(BOOL)isKickOut;

/// 他人上麦消息
- (void)room:(VHInteractiveRoom *)room didAddAttendView:(VHRenderView *)attendView;

/// 他人下麦消息
- (void)room:(VHInteractiveRoom *)room didRemovedAttendView:(VHRenderView *)attendView;

/// 文档融屏流上线(订阅)
- (void)room:(VHInteractiveRoom *)room didAddDocmentAttendView:(VHRenderView *)attendView;

/// 文档融屏流下线(订阅)
- (void)room:(VHInteractiveRoom *)room didRemovedDocmentAttendView:(VHRenderView *)attendView;

#pragma mark - 上下麦推流信息回调

/// 收到别人上麦申请 调用审核申请上麦接口回复
- (void)room:(VHInteractiveRoom *)room requestPublish:(NSString *)third_user_id;

/// 上下麦
/// @param room 房间信息
/// @param canPublish 是否可以上麦推流
/// @param type 1、进入房间后有无上麦推流权限 2、申请上麦 审核后有无上麦推流权限 3、收到邀请上麦消息 获得上麦推流权限
- (void)room:(VHInteractiveRoom *)room canPublish:(BOOL)canPublish type:(int) type;

/// 房间人员信息变化
/// @param info 数据结构
/// @link
///   info {...}
///     status 0 人员变化 1 上麦 2 下麦 3拒绝上麦
///     third_party_user_id 操作人id
///     online 在线人数
///     nick_name 昵称
///     avatar 头像
- (void)room:(VHInteractiveRoom *)room  userChangeInfo:(NSDictionary*)info;

/// 推流成功
- (void)room:(VHInteractiveRoom *)room didPublish:(VHRenderView *)cameraView;

/// 停止推流成功
/// @param reason  "主动下麦" "被动下麦"
- (void)room:(VHInteractiveRoom *)room didUnpublish:(NSString *)reason;

/// 强制用户下线的消息
- (void)room:(VHInteractiveRoom *)room force_leave_inav:(NSString *)third_user_id;

/// 流音视频开启情况
/// @param streamId 流id
/// @param muteStream 流音视频开启情况
- (void)room:(VHInteractiveRoom *)room didUpdateOfStream:(NSString *)streamId muteStream:(NSDictionary *)muteStream;

/// 服务器已准备好混流可以调用混流接口
/// @param msg 详细消息
- (void)room:(VHInteractiveRoom *)room onStreamMixed:(NSDictionary *)msg;

/// 染推流成功
/// @param room VHInteractiveRoom
/// @param msg 详细消息
- (void)room:(VHInteractiveRoom *)room docMixStreamStart:(NSDictionary *)msg;

/// 停止渲染推流
/// @param room VHInteractiveRoom
/// @param msg 详细消息
- (void)room:(VHInteractiveRoom *)room docMixStreamStop:(NSDictionary *)msg;

/// 染推流失败(推流成功后出现异常)
/// @param room VHInteractiveRoom
/// @param msg 详细消息
- (void)room:(VHInteractiveRoom *)room docMixStreamFailed:(NSDictionary *)msg;
@end

@interface VHInteractiveRoom : NSObject

@property (nonatomic, weak) id <VHInteractiveRoomDelegate> delegate;
@property (nonatomic, readonly) VHInteractiveRoomStatus status; ///< 当前房间状态
@property (nonatomic, readonly, weak) VHRenderView *cameraView; ///< 当前推流的cameraView (只在推流过程中存在)
@property (nonatomic, readonly) NSDictionary *renderViewsById;  ///< 所有其他进入本房间的视频view
@property (nonatomic, readonly) NSArray *streams;               ///< 房间中所有可以观看的流id列表
@property (nonatomic, readonly) NSString *roomId;               ///< 房间id
@property (nonatomic, readonly) NSString *broadCastId;          ///< 旁路房间ID
@property (nonatomic, readonly) BOOL isPublishing;          ///< 当前推流状态 (是否正在推流)
@property (nonatomic, readonly) VHInteractiveRoomMode mode; ///< 房间类型
@property (nonatomic, readonly) VHInteractiveRoomRole role; ///< 房间权限
@property (nonatomic, assign) int reconnectTimes;           ///< 房间重连次数 (默认 5次)
@property (nonatomic, assign) BOOL isOnlyAudioSubscribe;    ///< 是否只订阅音频流 (默认为NO 订阅音视频流 enterRoomWithToken 前有效， YES只订阅音频流，可以 unmuteVideo 打开视频)
@property (nonatomic) BOOL isAdaptResolution;   ///< 自适应分辨率 (默认开启, 根据网速来降低分辨率)
@property (nonatomic) BOOL isSubscribeDocStream; ///< 是否开启文档融屏流的订阅
/*
 * 进入互动房间后可用权限
 * 注: didEnterRoom 后调用有效 具体权限如下：
 kick_inav              踢出互动房间 / 取消踢出互动房间
 kick_inav_stream       踢出路流 / 取消踢出流
 publish_inav_another   推旁路直播 / 结束推旁路直播
 apply_inav_publish     申请上麦
 publish_inav_stream    推流
 askfor_inav_publish    邀请用户上麦推流
 audit_inav_publish     审核申请上麦
 force_leave_inav       强制用户下线
 */
@property (nonatomic, readonly) NSArray *permission;

- (instancetype)initWithLogParam:( NSDictionary* _Nullable )logParam;

#pragma mark - 房间操作
/// 加入房间
/// @param inav_id 互动房间id
/// @param accessToken accessToken
/// @discussion 调用完成等待代理回调确认接下来操作
- (void)enterRoomWithRoomId:(NSString *)inav_id accessToken:(NSString *)accessToken;

/// 加入房间
/// @param inav_id 互动房间id
/// @param accessToken accessToken
/// @param userData 用户数据可以携带不超过255字符的字符串 可在VHRenderView中获取此值
/// @discussion 调用完成等待代理回调确认接下来操作
- (void)enterRoomWithRoomId:(NSString *)inav_id accessToken:(NSString *)accessToken userData:(NSString*)userData;

/// 加入房间
/// @param inav_id 互动房间id
/// @param broadCastId 旁路房间id
/// @param accessToken accessToken
/// @param userData 用户数据可以携带不超过255字符的字符串 可在VHRenderView中获取此值
/// @discussion 调用完成等待代理回调确认接下来操作
- (void)enterRoomWithRoomId:(NSString *)inav_id broadCastId:(NSString *)broadCastId accessToken:(NSString *)accessToken userData:(NSString*)userData;

/// 加入房间
/// @param inav_id 互动房间id
/// @param broadCastId 旁路房间id
/// @param accessToken accessToken
/// @param userData 用户数据可以携带不超过255字符的字符串 可在VHRenderView中获取此值
/// @param mode 应用场景模式，选填，可选值参考 VHInteractiveRoomMode。支持版本：2.3.2及以上
/// @param role 用户角色，选填，可选值参考下文VHInteractiveRoomRole。当mode为rtc模式时，不需要配置role。支持版本：2.3.2及以上
/// @discussion 调用完成等待代理回调确认接下来操作
- (void)enterRoomWithRoomId:(NSString *)inav_id broadCastId:(NSString *)broadCastId accessToken:(NSString *)accessToken userData:(NSString*)userData mode:(VHInteractiveRoomMode)mode role:(VHInteractiveRoomRole)role;

/// 加入房间
/// @param inav_id 互动房间id
/// @param broadCastId 旁路房间id
/// @param accessToken  accessToken
/// @param userData  用户数据可以携带不超过255字符的字符串 可在VHRenderView中获取此值
/// @param isScreenShare  是否录屏互动
/// 调用完成等待代理回调确认接下来操作
- (void)enterRoomWithRoomId:(NSString *)inav_id broadCastId:(NSString *)broadCastId accessToken:(NSString *)accessToken userData:(NSString*)userData screenShare:(BOOL )isScreenShare;

/// 离开房间
- (void)leaveRoom;

/// 踢出互动房间并加入黑名单 或 从黑名单解禁
/// @param isKickout Yes 踢出房间 并加入黑名单 NO 从黑名单解禁
/// @param third_user_id 第三方id
- (BOOL)kickoutRoom:(BOOL)isKickout thirdUserId:(NSString *)third_user_id;

#pragma mark - 上下麦操作

/// 上麦推流
/// @param cameraView 本地摄像头view 也可以是录屏view 尝试推录屏流 需要同步启动 系统录屏界面触发正式推流
/// @return 如果False:请检查cameraView 是否创建， 进入房间角色是否是观众
- (BOOL)publishWithCameraView:(VHRenderView*)cameraView error:(NSError **)error;
- (BOOL)publishWithCameraView:(VHRenderView*) cameraView __deprecated_msg("use -[publishWithCamerView: error:]");

/// 下麦停止推流
- (BOOL)unpublish;

/// 帮别人下麦
/// @param third_user_id 被下麦人的第三方id
- (BOOL)kickoutStreamWithThirdUserId:(NSString *)third_user_id;

#pragma mark - 他人视频处理

/// 接收他人视频数据
/// @param streamId 他人视频 streamId
- (BOOL)addVideo:(NSString*)streamId;

/// 不接收他人视频数据
/// @param streamId 他人视频 streamId
- (BOOL)removeVideo:(NSString*)streamId;

#pragma mark - 上下麦许可操作

/// 邀请 上麦推流
/// @param third_user_id 被邀请/取消邀请人的第三方id
- (BOOL)invitePublishWithThirdUserId:(NSString *)third_user_id;

/// 是否接受 上麦推流申请
/// @param third_user_id 互动观众的第三方id
- (BOOL)acceptPublishRequest:(BOOL)isAccept thirdUserId:(NSString *)third_user_id;

/// 拒绝被邀请上麦推流
- (BOOL)refusePublish;

/// 申请上麦推流
- (BOOL)requestPublish;

/// 互动房间用户列表
/// @param block 结果回调
/// @link
///     userList 结构: [{third_party_user_id:"", status:""}]
///     third_party_user_id 第三方用户ID
///     status 用户状态 1:推流中 2:观看中 3:受邀中 4:申请上麦中
- (BOOL)inviteUserList:(void(^)(NSArray *userList, NSError *error))block;

/// 互动房间被踢出用户列表
/// @param block 结果回调
/// @link
///     userList 结构: [{third_party_user_id:"", status:""}]
///     third_party_user_id 第三方用户ID
///     status 用户状态 1:推流中 2:观看中 3:受邀中 4:申请上麦中
- (BOOL)kickoutUserList:(void(^)(NSArray *userList,NSError *error)) block;

#pragma mark - 旁路操作
/// 设置是否加入混流
- (void)setRoomBroadCastMixOption:(NSDictionary *)dict mode:(NSString *)modeStr finish:(void(^)(int code, NSString * _Nonnull message))handle;

/// 开启/关闭旁路直播 (使用该方法前提:加入房间初始化方法使用enterRoomWithRoomId:broadCastId:accessToken:userData:)
/// @param isOpen Yes开启旁路直播   NO关闭旁路直播
/// @param param [self baseConfigRoomBroadCast:4 layout:4]; 调用此函数配置视频质量参数和旁路布局
/// @discussion 设置成功后会自动推旁路
- (BOOL)publishAnotherLive:(BOOL)isOpen param:(NSDictionary*)param completeBlock:(void(^)(NSError *error))block;

/// 基础配置旁路混流参数
/// @param definition 视频质量参数，推荐使用。即（分辨率+帧率+码率）
/// @param layout 旁路布局模板（非自定义布局）
- (NSDictionary*)baseConfigRoomBroadCast:(BroadcastDefinition)definition layout:(BroadcastLayout)layout;

/// 修改旁路混流布局
/// @param layoutMode VHBroadCastDef.h ==> BroadcastLayout
/// @param mode mode 默认nil
/// @param finish 完成的回调
- (void)setMixLayoutMode:(int)layoutMode mode:(NSString*_Nullable)mode finish:(VhallFinishBlock _Nullable)finish;

/// 设置当前画面为主屏
/// @param handle 完成的回调
- (void)settingRoomBroadCastMainScreenFromCamera:(VhallFinishBlock _Nullable)handle;

/// 设置当前文档融屏为主屏
/// @param handle 完成的回调
- (void)settingRoomBroadCastMainScreenFromDocMix:(VhallFinishBlock _Nullable)handle;

/// 设置旁路背景图
/// @param url 背景图URL,如果为空，则为取消背景图
/// @param cropType 填充类型:RoomBGCropType
/// @param finish 设置后的回调,成功:200
- (void)settingRoomBroadCastBackgroundImageURL:(NSURL *_Nullable)url cropType:(RoomBGCropType)cropType finishHandle:(VhallFinishBlock _Nullable)finish;

/// 设置旁路头像占位图
/// @param url 头像占位图URL,如果为空，则为取消占位图
/// @param finish 设置后的回调,成功:200
- (void)settingRoomBroadCastPlaceholderImageURL:(NSURL *_Nullable)url finishHandle:(VhallFinishBlock _Nullable)finish;

/// 是否开启文档融屏旁路
/// @param enable 开启/关闭
/// @param channelID 文档channelID
/// @param finish 设置后的回调,成功:20041
- (void)settingRoomBroadCastDocMixEnable:(BOOL)enable channelID:(NSString *_Nonnull)channelID finishHandle:(VhallFinishBlock _Nullable)finish;

/// 获得当前SDK版本号
+ (NSString *)getSDKVersion;

/// 是否开启扬声器输出音频
- (void)setSpeakerphoneOn:(BOOL)on;

/// 切换大小流
/// @param streamId 他人视频 streamId
/// @param type 0 是小流 1是大流
/// @param finish code 200 成功 message具体信息
- (void)switchDualStream:(NSString *)streamId type:(int)type finish:(void(^)(int code, NSString * _Nullable message))finish;

/// 强制用户离开(下线)互动房间
- (BOOL)forceLeaveRoomWithInavId:(NSString *)inavId kickUserId:(NSString *)kick_user_id accessToken:(NSString *)accessToken onRequestFinished:(void(^)(id data))success onRequestFailed:(void(^)(NSError *error))failed;
@end

NS_ASSUME_NONNULL_END

/// error
/// 284000 未知错误 VHRoomErrorUnknown
/// 284001 VHRoomErrorClient
/// 284002 VHRoomErrorClientFailedSDP
/// 284003 VHRoomErrorSignaling

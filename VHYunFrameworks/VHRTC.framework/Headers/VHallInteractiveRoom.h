//
//  VHallInteractiveRoom.h
//  VHInteractive
//
//  Created by vhall on 2018/4/18.
//  Copyright © 2018年 www.vhall.com. All rights reserved.
//  1、
//  进入房间-->进入房间结果回调
//  |
//  推流-->推流结果回调
//  2、
//  进入房间-->进入房间结果回调
//  |
//  遍历房间当前流列表，并订阅-->订阅结果回调
//  |
//  返回所订阅流的renderview
//

#import <Foundation/Foundation.h>

@protocol   VHallInteractiveRoomDelegate;
@class      VHRenderView;

// 用户与互动直播间的连接状态
typedef NS_ENUM(NSInteger, VhallInteractiveRoomStatus) {
    VhallInteractiveRoomStatusReady,
    VhallInteractiveRoomStatusConnected,
    VhallInteractiveRoomStatusDisconnected,
    VhallInteractiveRoomStatusError
};

NS_ASSUME_NONNULL_BEGIN
// param code 200 success ,otherwise fail;
typedef void(^VhallFinishBlock)(int code, NSString * _Nonnull message);

///微吼课堂互动直播间实体类，此类定义了进入互动、离开互动、推流等Api，实现用户在线互动功能。
@interface VHallInteractiveRoom : NSObject

@property (nonatomic, weak) id <VHallInteractiveRoomDelegate> delegate;

// 互动直播间房间id
@property (nonatomic, copy, readonly) NSString        *roomId;

// 用户与互动直播间当前的连接状态
@property (nonatomic, assign, readonly) VhallInteractiveRoomStatus status;

// 当前推流 cameraView 只在推流过程中存在
@property (nonatomic, weak, readonly) VHRenderView    *cameraView;

// 所有订阅的视频view key为streamId
@property (nonatomic, strong, readonly) NSDictionary    *renderViewsById;

// 房间中所有流id列表
 @property (nonatomic, strong, readonly) NSArray         *streams;

// 是否自动订阅收到的流 默认为YES 自动订阅收到的流 如果双流默认订阅小分辨率流 enterRoomWithToken 前有效
@property (nonatomic, assign) BOOL isAutoSubscribe;

// 是否只订阅音频流 默认为NO 订阅音视频流 enterRoomWithToken 前有效
@property (nonatomic, assign) BOOL isOnlyAudioSubscribe;

// 重连次数 默认 5次
@property (nonatomic, assign) int reconnectTimes;

- (instancetype)init NS_UNAVAILABLE;
//see wiki:http://wiki.vhall.com/index.php?id=rd:vhall2.0:vhallsdk_uplog
/*
 "host":"例：https://t-dc.e.vhall.com/login"
 "s":"" //sessionId 不传内部会生成一个随机字符串
 "uid":"用户id"
 "aid":"房间id"
 "pf":"平台类型"
 "vtype":"视频类别(0:纯音频, 1:单视频, 2:音视频, 3:桌面共享)"
 "biz_role":"教育版用户角色"
 "biz_id":"教育版业务ID"
 "biz_des01":"教育版业务属性"
 "biz_des02":"角色状态"
 "bu":"业务类型"
 "app_id":"app_id"
 "vid":""  开发者账号id
 "vfid":"" 开发者账号id
 "vfid":"" 开发者账号id
 "isPrintLog":0
 */
- (instancetype)initWithLogParam:(NSDictionary*)param;

/**
 @brief 进入互动直播间
 @param token   进入房间token。
 @param userData 用户数据userData 订阅端需从 stream userAttributes 读取
 @discussion 结果会在- (void)roomdidEnteredWithRoomMetaDataerror:中回调，如果进入成功，可以开始推流上麦。
 */
- (void)enterRoomWithToken:(NSString *)token userData:(NSString*)userData;

/**
 @brief 推流上麦
 @param cameraView 推流的摄像机view，不可为空。
 @discussion 回调推流是否成功：- (void)room:didPublishWithCameraView:error:
 */
- (BOOL)publishWithCameraView:(nonnull VHRenderView *)cameraView;

/**
 @brief 推流上麦
 @param cameraView 推流的摄像机view，不可为空。
 @param streamAttributes 推流数据 订阅端需从 stream streamAttributes 读取
 @discussion 回调推流是否成功：- (void)room:didPublishWithCameraView:error:
 */
- (BOOL)publishWithCameraView:(nonnull VHRenderView *)cameraView streamAttributes:(NSString*)streamAttributes;

/**
 @brief 停止推流
 @discussion 下麦的时候需要停止推流。
 */
- (void)unpublish;

/**
 @brief 离开互动直播间，即下麦
 @discussion 停止推流后离开互动直播间需调用此方法。
 */
- (void)leaveRoom;

/**
 @brief 订阅他人视频数据 即拉取某个连麦人的流 isAutoSubscribe为YES 时收到流会自动订阅
 @param streamId 他人视频 streamId
 @discussion 结果会在- (void)room:didAddAttendView:中回调
 */
- (void)subscribe:(NSString *)streamId;

/**
 @brief 取消订阅他人视频数据 不再拉取某个连麦人的流
 @param streamId 他人视频 streamId
 @discussion 结果会在- (void)room:didRemovedAttendView:中回调
 */
- (void)unsubscribe:(NSString *)streamId;

/**
 @brief 使用streamId 查询VHRenderView，包括未订阅的流
 @param streamId 他人视频 streamId
 @discussion 一般用于查询未订阅流的属性，订阅流可以直接- (void)room:didAddAttendView:中读取
 */
- (VHRenderView*)queryViewWithStreamId:(NSString *)streamId;

/**
 @brief 是否开启扬声器输出音频
 */
- (void)setSpeakerphoneOn:(BOOL)on;

/**
 @brief 切换大小流
 @param streamId 他人视频 streamId
 @param type 0 是小流 1是大流
 @param finish code 200 成功 message具体信息
 */
- (void)switchDualStream:(NSString *)streamId type:(int)type finish:(void(^)(int code, NSString * _Nullable message))finish;

#pragma mark - 旁路接口
/*
 * 配置旁路混流参数 VHConstantDef.h
 NSDictionary *config = [VHBroadCastDef baseConfigRoomBroadCast:BROADCAST_VIDEO_PROFILE_720P_1// 视频质量参数，推荐使用。即（分辨率+帧率+码率）
                                                   broadCastUrl:@"rtmp://domainname/vhall/xxxxxx",// 推流地址
                                                         layout:CANVAS_LAYOUT_PATTERN_GRID_4_M]; // 旁路布局模板（非自定义布局）
 * 设置成功后会自动推旁路
 */
- (void)configRoomBroadCast:(NSDictionary*_Nonnull)configDic mode:(NSString*_Nullable)mode finish:(VhallFinishBlock _Nullable)finish;

/*
 * 配置旁路混流布局 VHConstantDef.h CANVAS_LAYOUT
 * layoutMode CANVAS_LAYOUT_PATTERN_GRID_4_M
 */
- (void)setMixLayoutMode:(int)layoutMode mode:(NSString*_Nullable)mode finish:(VhallFinishBlock _Nullable)finish;

/*
 * 开始旁路混流推流
 */
- (void)startRoomBroadCast:(NSString*_Nullable)mode finish:(VhallFinishBlock _Nullable)finish;
/*
 * 停止旁路混流推流
 */
- (void)stopRoomBroadCast:(NSString*_Nullable)mode finish:(VhallFinishBlock _Nullable)finish;
@end


/// 互动房间代理，此代理定义了进入互动房间结构回调、推流结果回调、上麦结果回调等与互动房间有关的回调方法。在回调中可以处理您关于互动的相关操作。
@protocol VHallInteractiveRoomDelegate <NSObject>

@optional

///----------------------------
/// @name 互动直播间生命周期相关回调
///----------------------------
/**
 @brief 错误回调
 @param error   error
 */
- (void)room:(VHallInteractiveRoom *)room error:(NSError *)error;

/**
 @brief 互动状态回调
 @param status 互动房间状态
 */
- (void)room:(VHallInteractiveRoom *)room statusChanged:(VhallInteractiveRoomStatus)status;


/**
 @brief 进入互动直播间结果回调
 @param data   互动直播间数据
 @discussion   当error为nil时候，表示已进入互动直播间；error不为空时，表示进入失败，失败原因描述：error.errorDescription。成功进入互动直播间成功就可以开始推流上麦了。
 */
- (void)room:(VHallInteractiveRoom *)room didEnteredRoom:(NSDictionary *)data;

/**
 @brief 推流结果回调
 @param cameraView 推流的cameraView
 @discussion 推流成功之后，会收到上麦结果的回调。
 */
- (void)room:(VHallInteractiveRoom *)room didPublish:(VHRenderView *)cameraView;

/**
 @brief 停止推流回调
 @param cameraView 推流的cameraView
 @discussion 自己调用- unpublish停止推流，会回调此方法;被讲师下麦，会停止推流，回调此方法；推流出错,停止推流，会回调此方法。
 */
- (void)room:(VHallInteractiveRoom *)room didUnpublish:(VHRenderView *)cameraView;

/**
 @brief 新加入一路流（有成员进入互动房间，即有人上麦)
 @discussion 流id：attendView.streamId；上麦用户参会id：attendView.userId。
 */
- (void)room:(VHallInteractiveRoom *)room didAddAttendView:(VHRenderView *)attendView;

/**
 @brief 减少一路流（有成员离开房间，即有人下麦）
 @discussion 流id：attendView.streamId；上麦用户参会id：attendView.userId。
 */
- (void)room:(VHallInteractiveRoom *)room didRemovedAttendView:(VHRenderView *)attendView;

/**
 @brief 有新流进入房间
 @param streamId 流id
 @discussion 此时可以订阅此流 订阅后会回调 room: didAddAttendView: 返回具体画面view
 */
- (void)room:(VHallInteractiveRoom *)room didAddedStream:(NSString *)streamId;

/**
 @brief 有端停止推流
 @param streamId 流id
 @discussion 此时会回调room:didRemovedAttendView:方法
 */
- (void)room:(VHallInteractiveRoom *)room didRemovedStream:(NSString *)streamId;

/**
 @brief 流音视频开启情况
 @param streamId 流id
 @param remoteMuteStream remoteMuteStream发起端音视频状态
 */
- (void)room:(VHallInteractiveRoom *)room didUpdateOfStream:(NSString *)streamId remoteMuteStream:(NSDictionary *)remoteMuteStream;

/**
 @brief 服务器已准备好混流可以调用混流接口
 @param msg msg
 @discussion onStreamMixed
 */
- (void)room:(VHallInteractiveRoom * _Nonnull)room onStreamMixed:(NSDictionary * _Nonnull)msg;
@end

NS_ASSUME_NONNULL_END

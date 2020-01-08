//
//  VHOTOCall.h
//  VHInteractive
//
//  Created by vhall on 2019/12/4.
//  Copyright © 2019 vhall. All rights reserved.
//

#import "VHInteractiveRoom.h"

NS_ASSUME_NONNULL_BEGIN

@protocol  VHOTOCallDelegate;

@interface VHOTOCall : VHInteractiveRoom

@property (nonatomic, weak) id <VHOTOCallDelegate> callDelegate;

@property (nonatomic, copy) NSString *cur_third_user_id;//当前对话人ID

@property (nonatomic, assign) BOOL isMainCall;//是否主叫

/*
 * 加入房间
 * @param roomId 互动房间id
 * @param accessToken  accessToken
 * @param userData  用户数据可以携带不超过255字符的字符串 可在VHRenderView中获取此值
 * 调用完成等待代理回调确认接下来操作
 */
- (void)enterRoomWithRoomId:(const NSString *)roomId accessToken:(const NSString *)accessToken userData:(nullable NSString*)userData;

/*
 * 呼叫接口
 * @param third_user_id 被呼叫人d
 */
- (BOOL)OTOCall:(const NSString *)third_user_id;

/*
 * 呼叫应答接口
 * @param answer 是否接受呼叫
 */
- (BOOL)OTOAnswer:(BOOL)answer;

/*
 * 接受呼叫/呼叫成功后推流
 * @param camera 本地摄像头view
 */
- (BOOL)OTOStartWithCameraView:(VHRenderView*) cameraView;

/*
 * 挂断
 */
- (BOOL)OTOHangUp;

/*
 * 离开房间
 */
- (void)leaveRoom;

/*
 * 互动房间用户列表
 * userList数据结构 {third_party_user_id:xxx,status:1}
 * third_party_user_id  第三方用户ID
 * status               用户状态 1 推流中 2 观看中 3 受邀中  4 申请上麦中
 */
- (BOOL)getUserList:(void(^)(NSArray* userList,NSError* error)) block;
@end

/*
 * 呼叫回调
 */
@protocol VHOTOCallDelegate <VHInteractiveRoomDelegate>

/*
 * 收到呼叫消息
 */
- (void)room:(VHInteractiveRoom *)room receiveCall:(id)msg;
 
/*
 * 收到呼叫应答消息
 * answer 0 人员变化 1 上麦 2 下麦 3拒绝上麦
 */
- (void)room:(VHInteractiveRoom *)room receiveAnswer:(int)status msg:(id)msg isMySelf:(BOOL)isMySelf;

@end
NS_ASSUME_NONNULL_END

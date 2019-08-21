//
//  VHStystemSetting.h
//  VHYunSDKDemo
//
//  Created by vhall on 2017/12/19.
//  Copyright © 2017年 www.vhall.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "CONSTS.h"

#define DEMO_Setting [VHStystemSetting sharedSetting]

@interface VHStystemSetting : NSObject
+ (VHStystemSetting *)sharedSetting;

//基础设置
@property(nonatomic, strong)NSString* appID;  
@property(nonatomic, strong)NSString* third_party_user_id;  //第三方ID
@property(nonatomic, strong)NSString* accessToken;          //AccessToken 根据开通的服务生成对应的 AccessToken

@property(nonatomic, strong)NSString* nickName;  //昵称
@property(nonatomic, strong)NSString* avatar;    //头像

//直播播放
@property(nonatomic, strong)NSString* playerRoomID;         //看直播房间ID
@property(nonatomic, assign)NSInteger bufferTime;           //RTMP观看缓冲时间

//推流
@property(nonatomic, strong)NSString* publishRoomID;        //发直播房间ID
@property(nonatomic, strong)NSString* videoResolution;      //发起直播分辨率 VideoResolution [0,3] 默认1
@property(nonatomic, assign)NSInteger videoBitRate;         //发直播视频码率
@property(nonatomic, assign)NSInteger audioBitRate;         //发直播视频码率
@property(nonatomic, assign)NSInteger videoCaptureFPS;      //发直播视频帧率 ［1～30］ 默认10
@property(nonatomic, assign)BOOL      isOpenNoiseSuppresion;//开启降噪 默认YES
@property(nonatomic, assign)float     volumeAmplificateSize;//开启降噪 默认1.0
@property(nonatomic, assign)BOOL      isOnlyAudio;          //是否纯音频推流
@property(nonatomic, assign)BOOL      isBeautifyFilterEnable;//是否开启美颜

//点播
@property(nonatomic, strong)NSString* recordID;             //点播房间ID
@property(nonatomic, assign)BOOL      seekMode;             //seek 播放器是否只支持在播放过的时段seek

//文档直播
@property(nonatomic, strong)NSString* docChannelID;         //文档ChannelID
@property(nonatomic, strong)NSString* docRoomID;            //文档绑定roomID

//IM
@property(nonatomic, strong)NSString* imChannelID;          //im ChannelID

//互动
@property(nonatomic, strong)NSString*   ilssRoomID;           //互动房间ID
@property(nonatomic, strong)NSString*   ilssLiveRoomID;       //旁路直播间ID
@property(nonatomic, assign)NSInteger   ilssType;              //摄像头及推流参数设置
@property(nonatomic, copy)NSDictionary* ilssOptions;            //摄像头及推流参数设置

@property(nonatomic, assign)BOOL isDouble;            //是否开启双流
@property(nonatomic, strong)NSString*   userData;           //互动房间userData
@end

//
//  ScreenShareViewController.h
//  VhallRTCTest
//
//  Created by vhall on 2021/1/24.
//  Copyright © 2021 ilong. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <VHRTC/VHInteractiveRoom.h>
#import <VHCore/VHLiveBase.h>
NS_ASSUME_NONNULL_BEGIN

@interface ScreenShareViewController : UIViewController<VHInteractiveRoomDelegate>
@property(nonatomic,copy) NSString * ilssRoomID;        //互动房间id
@property(nonatomic,copy) NSString * anotherLiveRoomId; //旁路直播间ID
@property(nonatomic,copy) NSString * accessToken;
@property(nonatomic,copy) NSString * extensionBundleID;        //
@end

NS_ASSUME_NONNULL_END

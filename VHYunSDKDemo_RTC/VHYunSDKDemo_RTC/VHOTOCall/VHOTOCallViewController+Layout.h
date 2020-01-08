//
//  VHOTOCallViewController+Layout.h
//  VHYunSDKDemo_RTC
//
//  Created by vhall on 2019/12/4.
//  Copyright © 2019 vhall. All rights reserved.
//

#import "VHOTOCallViewController.h"

NS_ASSUME_NONNULL_BEGIN

@interface VHOTOCallViewController (Layout)
//创建并展示本地摄像头画面
- (void)showLocalCamera;
- (void)closeLocalCamera;

- (void)muteMyVideo:(BOOL)isMute;
- (void)muteMyAudio:(BOOL)isMute;
- (void)switchCamera;


- (void)addView:(UIView*)view attributes:(id) attributes;
- (void)removeView:(UIView*)view;
- (void)removeAllViews;

//更新布局
- (void)updateUI;
@end

NS_ASSUME_NONNULL_END

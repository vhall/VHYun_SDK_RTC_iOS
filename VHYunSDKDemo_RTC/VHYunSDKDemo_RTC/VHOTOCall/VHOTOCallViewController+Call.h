//
//  VHOTOCallViewController+call.h
//  VHYunSDKDemo_RTC
//
//  Created by vhall on 2019/12/4.
//  Copyright © 2019 vhall. All rights reserved.
//


#import "VHOTOCallViewController.h"

NS_ASSUME_NONNULL_BEGIN

@interface VHOTOCallViewController (Call)<VHOTOCallDelegate>
- (NSDictionary*)renderViewsById;
- (void)enterRoom;

- (BOOL)OTOCall:(const NSString *)third_user_id;

- (BOOL)OTOAnswer:(BOOL)answer;

- (BOOL)OTOStart;

- (BOOL)OTOHangUp;

- (void)leaveRoom;

- (BOOL)getUserList:(void(^)(NSArray* userList,NSError* error)) block;
@end

NS_ASSUME_NONNULL_END

//
//  VHScreenShare.h
//  VHScreenShare
//
//  Created by vhall on 2019/7/18.
//  Copyright © 2019 vhall. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for VHScreenShare.
FOUNDATION_EXPORT double VHScreenShareVersionNumber;

//! Project version string for VHScreenShare.
FOUNDATION_EXPORT const unsigned char VHScreenShareVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <VHScreenShare/PublicHeader.h>

#import <Foundation/Foundation.h>
#import <ReplayKit/ReplayKit.h>

@protocol VHScreenShareDelegate;

@interface VHScreenShare : NSObject

@property (nonatomic,weak)id <VHScreenShareDelegate> delegate;

- (instancetype)initWithPort:(uint16_t)port;

- (void)broadcastStartedWithSetupInfo:(NSDictionary<NSString *,NSObject *> *)setupInfo;

- (void)broadcastPaused;

- (void)broadcastResumed;

- (void)broadcastFinished;

- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType API_AVAILABLE(ios(10.0));

+ (NSString *) getSDKVersion;
@end
@protocol VHScreenShareDelegate <NSObject>

@optional
- (void)VHScreenShareFinishBroadcastWithError:(NSError*)error;

@end

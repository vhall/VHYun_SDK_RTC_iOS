//
//  VHOTOCallViewController+Layout.m
//  VHYunSDKDemo_RTC
//
//  Created by vhall on 2019/12/4.
//  Copyright © 2019 vhall. All rights reserved.
//

#import "VHOTOCallViewController+Layout.h"
#import "VHOTOCallViewController+Call.h"

#define MakeColor(r,g,b,a)      ([UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:a])
@interface VHOTOCallButton:UIButton
@property(nonatomic,copy) NSString* streamId;
@end
@implementation VHOTOCallButton
@end

@implementation VHOTOCallViewController (Layout)

#pragma mark - Public
- (void)showLocalCamera
{
    if(!self.cameraView)
    {
        NSDictionary* ilssOptions = @{VHFrameResolutionTypeKey:@(VHFrameResolution640x480),
                                      VHStreamOptionStreamType:@(VHInteractiveStreamTypeAudioAndVideo)};
        self.cameraView = [[VHRenderView alloc]initCameraViewWithFrame:self.containerView.bounds options:ilssOptions];
        
        self.cameraView.layer.borderWidth = 1;
        self.cameraView.layer.borderColor = MakeColor(200, 200, 200, 0.5).CGColor;
        self.cameraView.scalingMode = VHRenderViewScalingModeAspectFill;
        
        __weak typeof(self) wf =self;
        [self.layoutView addRenderView:self.cameraView attributes:@"cameraView" clickedBlock:^(VHLayoutItem * _Nonnull item) {
            [wf.layoutView changePosWithItem:item room:wf.otoCall];
        }];
        
        [self.cameraView setDeviceOrientation:[UIDevice currentDevice].orientation];
    }
}
- (void)closeLocalCamera
{
    [self.cameraView stopStats];
    self.cameraView = nil;
}

- (void)muteMyVideo:(BOOL)isMute
{
    if (isMute) {
        [self.cameraView muteVideo];
    }
    else
    {
        [self.cameraView unmuteVideo];
    }
}
- (void)muteMyAudio:(BOOL)isMute
{
    if (isMute) {
        [self.cameraView muteAudio];
    }
    else
    {
        [self.cameraView unmuteAudio];
    }
}
- (void)switchCamera
{
    [self.cameraView switchCamera];
}

- (void)muteVideo:(BOOL)isMute attendId:(NSString*)attendId
{
    VHRenderView *view = self.renderViewsById[attendId];
    [self.layoutView muteVideo:isMute view:view];
}

- (void)muteAudio:(BOOL)isMute attendId:(NSString*)attendId
{
    VHRenderView *view = self.renderViewsById[attendId];
    if (isMute) {
        [view muteAudio];
    }
    else
    {
        [view unmuteAudio];
    }
}

- (void)addView:(UIView*)view attributes:(id) attributes
{
    VHRenderView* attendView  = (VHRenderView* )view;
    
    if(!attendView.isLocal)
    {
        UILabel *label = [attendView viewWithTag:1001];
        if(!label)
        {
            label  = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, 80, 20)];
            label.textColor = [UIColor redColor];
            label.font = [UIFont systemFontOfSize:9];
            label.adjustsFontSizeToFitWidth = YES;
            label.minimumScaleFactor = 0.5;
            label.tag = 1001;
            [attendView addSubview:label];
        }
        label.text = attendView.userId;
    
//        VHOTOCallButton * muteBtn = [attendView viewWithTag:1002];
//        if(!muteBtn)
//        {
//            muteBtn = [[VHOTOCallButton alloc] initWithFrame:CGRectMake(25, 0,25, 25)];
//            [muteBtn setImage:[UIImage imageNamed:@"video_on"] forState:UIControlStateNormal];
//            [muteBtn setImage:[UIImage imageNamed:@"video_off"] forState:UIControlStateSelected];
//            [muteBtn addTarget:self action:@selector(muteRemoteVideo:) forControlEvents:UIControlEventTouchUpInside];
//            muteBtn.tag = 1002;
//            [attendView addSubview:muteBtn];
//            muteBtn.right  = attendView.width-25;
//            muteBtn.bottom = attendView.height;
//        }
//        muteBtn.streamId = attendView.streamId;
//    
//        VHOTOCallButton * muteBtn1 = [attendView viewWithTag:1003];
//        if(!muteBtn1)
//        {
//            muteBtn1 = [[VHOTOCallButton alloc] initWithFrame:CGRectMake(0, 0,25, 25)];
//            [muteBtn1 setImage:[UIImage imageNamed:@"speaker_on"] forState:UIControlStateNormal];
//            [muteBtn1 setImage:[UIImage imageNamed:@"speaker_off"] forState:UIControlStateSelected];
//            [muteBtn1 addTarget:self action:@selector(muteRemoteAudio:) forControlEvents:UIControlEventTouchUpInside];
//            muteBtn1.tag = 1003;
//            [attendView addSubview:muteBtn1];
//            muteBtn1.right  = attendView.width;
//            muteBtn1.bottom = attendView.height;
//            attendView.layer.borderWidth = 1;
//            attendView.layer.borderColor = MakeColor(200, 200, 200, 0.5).CGColor;
//        }
//        muteBtn1.streamId = attendView.streamId;
    }

    __weak typeof(self) wf = self;
    [self.layoutView addRenderView:view attributes:attributes clickedBlock:^(VHLayoutItem * _Nonnull item) {
        [wf.layoutView changePosWithItem:item room:wf.otoCall];
    } frameChangeBlock:^(VHLayoutItem * _Nonnull item) {
        [item.view viewWithTag:1002].right = item.view.width-25;
        [item.view viewWithTag:1002].bottom = item.view.height;
        [item.view viewWithTag:1003].right = item.view.width;
        [item.view viewWithTag:1003].bottom = item.view.height;
    }];
}
- (void)removeView:(UIView*)view
{
    [self.layoutView removeRenderView:view];
}
- (void)removeAllViews
{
    [self.layoutView removeAllViews];
    if(self.cameraView)
    {
        __weak typeof(self) wf = self;
        [self.layoutView addRenderView:self.cameraView attributes:@"cameraView" clickedBlock:^(VHLayoutItem * _Nonnull item) {
            [wf.layoutView changePosWithItem:item room:wf.otoCall];
        }];
    }
}

- (void)updateUI
{
    self.layoutView.frame = self.containerView.bounds;
}

@end

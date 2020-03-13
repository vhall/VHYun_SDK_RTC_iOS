//
//  VHOTOCallViewController.m
//  VHYunSDKDemo_RTC
//
//  Created by vhall on 2019/12/4.
//  Copyright © 2019 vhall. All rights reserved.
//

#import "VHOTOCallViewController.h"
#import "VHOTOCallViewController+Call.h"
#import "VHOTOCallViewController+Layout.h"

@interface VHOTOCallViewController ()

@property (weak, nonatomic) IBOutlet UIButton *videoBtn;
@property (weak, nonatomic) IBOutlet UIButton *audioBtn;

@end

@implementation VHOTOCallViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    [self enterRoom];
}
- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
}

- (void)viewWillDisappear:(BOOL)animated{
   [super viewWillDisappear:animated];
   [[UIApplication sharedApplication] setIdleTimerDisabled:NO];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (void)callYou:(NSString*)userid//主叫别人
{
    self.callView.hidden = NO;
    self.acceptBtn.hidden = YES;
    self.refuseBtn.hidden = YES;
    self.callingLabel.hidden = NO;
    
    [self OTOCall:userid];
}
- (void)callMe:(NSString*)userid//电话呼入
{
    self.callView.hidden = NO;
    self.acceptBtn.hidden = NO;
    self.refuseBtn.hidden = NO;
    self.callingLabel.hidden = YES;
}
- (void)callAccept//接受呼叫
{
    if(self.containerView.hidden)
    {
        self.callView.hidden = YES;
        self.containerView.hidden = NO;
        [self showLocalCamera];
        [self OTOAnswer:YES];
        [self OTOStart];
    }
}
- (void)callAccepted;//对方已接受呼叫
{
    if(self.containerView.hidden)
    {
        self.callView.hidden = YES;
        self.containerView.hidden = NO;
        [self showLocalCamera];
        [self OTOStart];
    }
}
- (void)callRefuse//拒绝呼叫
{
    self.callView.hidden = YES;
    [self OTOAnswer:NO];
}
- (void)callStop//挂断
{
    self.callView.hidden = YES;
    self.containerView.hidden = YES;
    [self OTOHangUp];
    [self closeLocalCamera];
    [self removeAllViews];
    
    _videoBtn.selected = NO;
    _audioBtn.selected = NO;
}

#pragma mark - btnclicked
- (IBAction)closeBtnClicked:(id)sender {
    [self callStop];
    //离开房间
    [self leaveRoom];
    
    [self dismissViewControllerAnimated:YES completion:^{}];
    [self.navigationController popViewControllerAnimated:NO];
}

- (IBAction)acceptBtnClicked:(id)sender {
    [self callAccept];
}

- (IBAction)refuseBtnClicked:(id)sender {
    [self callRefuse];
}

- (IBAction)stopBtnClicked:(id)sender {
    [self callStop];
}

- (IBAction)videoBtnClicked:(UIButton*)sender {
    if(sender.selected)
    {
        [self.cameraView unmuteVideoWithFinish:^(int code, NSString * _Nullable message) {
        }];
    }
    else
    {
        [self.cameraView muteVideoWithFinish:^(int code, NSString * _Nullable message) {
        }];
    }
    sender.selected = !sender.selected;
}

- (IBAction)audioBtnClicked:(UIButton*)sender {
    if(sender.selected)
    {
        [self.cameraView unmuteAudioWithFinish:^(int code, NSString * _Nullable message) {
        }];
    }
    else
    {
        [self.cameraView muteAudioWithFinish:^(int code, NSString * _Nullable message) {
        }];
    }
    sender.selected = !sender.selected;
}

- (IBAction)swapCameraBtnClicked:(id)sender {
    [self.cameraView switchCamera];
}


#pragma mark - get
- (VHLayoutView*)layoutView
{
    if(!_layoutView)
    {
        _layoutView = [[VHLayoutView_1vN_Pip_Left alloc]initWithFrame:self.containerView.bounds];
        _layoutView.backgroundColor = [UIColor blackColor];
        [self.containerView insertSubview:_layoutView atIndex:0];
    }
    return _layoutView;
}
@end
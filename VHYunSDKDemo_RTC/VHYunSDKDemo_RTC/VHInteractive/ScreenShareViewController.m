//
//  ScreenShareViewController.m
//  VhallRTCTest
//
//  Created by vhall on 2021/1/24.
//  Copyright © 2021 vhall. All rights reserved.
//

#import "ScreenShareViewController.h"

#import <ReplayKit/ReplayKit.h>


@interface ScreenShareViewController ()
@property (weak, nonatomic) IBOutlet UILabel *statusLabel;
@property (weak, nonatomic) IBOutlet UIView *conentView;
@property (strong, nonatomic) VHInteractiveRoom *room;
@property (strong, nonatomic) VHRenderView *screenView;
@end

@implementation ScreenShareViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(deviceOrientationDidChange:)
                                                 name:UIDeviceOrientationDidChangeNotification
                                               object:nil];
    
    self.room = [[VHInteractiveRoom alloc] init];
    self.room.delegate = self;
    self.room.isOnlyAudioSubscribe = NO;
    self.screenView = [[VHRenderView alloc] initScreenViewWithFrame:CGRectZero attributes:@"{}" isShowVideo:NO post:19999];
    [self enterRoom:nil];
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter]  removeObserver:self];
}
- (void)deviceOrientationDidChange:(NSNotification *)notification {
#if TARGET_OS_IPHONE
    UIInterfaceOrientation orientation = [UIApplication sharedApplication].statusBarOrientation;
   [self.room.cameraView setDeviceOrientation:(UIDeviceOrientation)orientation];
#endif
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (void)enterRoom:(id)sender{
    [self showCallConnectViews:NO
         updateStatusMessage:@"Connecting with the room..."];
    // Initialize room (without token!)
        [self.room enterRoomWithRoomId:_ilssRoomID
                           broadCastId:_anotherLiveRoomId
                           accessToken:_accessToken
                              userData:@"userData"
                           screenShare:YES];
}

- (void)showCallConnectViews:(BOOL)show updateStatusMessage:(NSString *)statusMessage {
   __weak typeof(self) weakSelf = self;
   dispatch_async(dispatch_get_main_queue(), ^{
      weakSelf.statusLabel.text = statusMessage;
   });
}
- (IBAction)backBtnClicked:(id)sender {
    [self.room leaveRoom];
    self.room = nil;
    [self dismissViewControllerAnimated:YES completion:^{
        
    }];
}

#pragma mark - VHRoomDelegate
- (void)room:(VHInteractiveRoom *)room error:(NSError*)error{
   __weak typeof(self) weakSelf = self;
   dispatch_async(dispatch_get_main_queue(), ^{
      [weakSelf showCallConnectViews:YES
             updateStatusMessage:[NSString stringWithFormat:@"Room error: %@", error.description]];
   });
}
- (void)room:(VHInteractiveRoom *)room didEnterRoom:(NSString *)third_user_id {
    if(![third_user_id isEqualToString:[VHLiveBase getThirdPartyUserId]])
        return;
    
    [self showCallConnectViews:NO updateStatusMessage:@"Room connected!"];
    [self.room publishWithCameraView:self.screenView];
    
#if TARGET_IPHONE_SIMULATOR  //模拟器
        return;
#elif TARGET_OS_IPHONE      //真机
    __weak typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if (@available(iOS 12.0, *)) {
            RPSystemBroadcastPickerView *_broadPickerView = [[RPSystemBroadcastPickerView alloc] initWithFrame:CGRectMake(-140, 0, 40, 40)];
            _broadPickerView.backgroundColor = [UIColor redColor];
            _broadPickerView.showsMicrophoneButton = NO;
            _broadPickerView.preferredExtension = weakSelf.extensionBundleID;
            
            for (UIButton* btn in _broadPickerView.subviews) {
                if([btn isKindOfClass:[UIButton class]])
                {
                    [btn sendActionsForControlEvents:UIControlEventTouchDown];//代码点击
                    [btn sendActionsForControlEvents:UIControlEventTouchUpInside];//代码点击
                }
            }
        } else {
            // Fallback on earlier versions
        }
    });
#endif
    
}
- (void)room:(VHInteractiveRoom *)room didPublish:(VHRenderView *)cameraView {
   __weak typeof(self) weakSelf = self;
   dispatch_async(dispatch_get_main_queue(), ^{
      [weakSelf showCallConnectViews:NO
             updateStatusMessage:[NSString stringWithFormat:@"Published with Id: %@", cameraView.streamId]];
   });
    [self.room baseConfigRoomBroadCast:BROADCAST_VIDEO_PROFILE_1080P_1 layout:CANVAS_LAYOUT_PATTERN_FLOAT_6_5D];
}
- (void)room:(VHInteractiveRoom *)room didUnpublish:(NSString *)reason{
   __weak typeof(self) weakSelf = self;
   dispatch_async(dispatch_get_main_queue(), ^{
       [weakSelf showCallConnectViews:NO updateStatusMessage:@"didUnpublishStream"];
   });
    
}
- (void)room:(VHInteractiveRoom *)room didChangeStatus:(VHInteractiveRoomStatus)status{
   __weak typeof(self) weakSelf = self;
   dispatch_async(dispatch_get_main_queue(), ^{
      switch (status) {
         case VHInteractiveRoomStatusConnected:
            [weakSelf showCallConnectViews:YES updateStatusMessage:@"Room Disconnected"];
            break;
         default:
            break;
      }
   });
}

//- (void)room:(VhallRoom *)room didSubscribeStream:(VhallStream *)stream {}
//- (void)room:(VhallRoom *)room didUnSubscribeStream:(VhallStream *)stream {}
//- (void)room:(VhallRoom *)room didAddedStream:(VhallStream *)stream {}
//- (void)room:(VhallRoom *)room didRemovedStream:(VhallStream *)stream {}
//- (void)room:(VhallRoom *)room didUpdateOfStream:(VhallStream *)stream muteDict:(NSDictionary *)mute {}
//- (void)room:(VhallRoom *_Nonnull)room  onStreamMixed:(NSDictionary *_Nonnull)msg{}
//- (void)room:(VhallRoom *)room didReconnectTimes:(int)times at:(int)index{
//   [self showCallConnectViews:NO
//          updateStatusMessage:[NSString stringWithFormat:@"reconnectTimes:%d index:%d",times,index]];
//}

@end

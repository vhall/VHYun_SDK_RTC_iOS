//
//  ViewController.m
//  VHYunSDKDemo_RTC
//
//  Created by vhall on 2019/7/23.
//  Copyright © 2019 vhall. All rights reserved.
//

#import "ViewController.h"
#import "ViewController+vhall.h"
#import <VHRTC/VHInteractiveRoom.h>
#import "VHInteractiveViewController.h"
#import "VHOTOCallViewController.h"
#import "ScreenShareViewController.h"

#import <AVFoundation/AVFoundation.h>

#define VHScreenHeight          ([UIScreen mainScreen].bounds.size.height)
#define VHScreenWidth           ([UIScreen mainScreen].bounds.size.width)
#define VH_SH                   ((VHScreenWidth<VHScreenHeight) ? VHScreenHeight : VHScreenWidth)
#define VH_SW                   ((VHScreenWidth<VHScreenHeight) ? VHScreenWidth  : VHScreenHeight)


@interface ViewController ()
{
    UITextField *_businessIDTextField;
    UITextField *_accessTokenTextField;
    UITextField *_roomIDTextField;
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initSDKView];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self showInitSDKVC];
}

- (void)inavBtnClicked:(UIButton*)btn
{
    if(![self isCaptureDeviceOK])
        return;
    
    if(_businessIDTextField.text.length == 0 || _accessTokenTextField.text.length == 0)
    {
        [self showMsg:@"参数不能为空" afterDelay:1.5];
        return;
    }

    DEMO_Setting.ilssRoomID     = _businessIDTextField.text;
    DEMO_Setting.ilssLiveRoomID = _roomIDTextField.text;
    DEMO_Setting.accessToken    = _accessTokenTextField.text;

    VHInteractiveViewController * vc = [[VHInteractiveViewController alloc] init];
    vc.ilssRoomID       = DEMO_Setting.ilssRoomID;
    vc.ilssType         = DEMO_Setting.ilssType;        //摄像头及推流参数设置
    vc.ilssOptions      = DEMO_Setting.ilssOptions;     //摄像头及推流参数设置
    vc.accessToken      = DEMO_Setting.accessToken;
    vc.anotherLiveRoomId= DEMO_Setting.ilssLiveRoomID;
    //    vc.anotherLiveRoomID= DEMO_Setting.anotherLiveRoomID;
    vc.userData         =  [DEMO_Setting.nickName stringByAppendingString:@"进入房间自定义数据"] ;
    vc.streamData       =  [DEMO_Setting.nickName stringByAppendingString:@"推流前放入本地流的自定义数据"] ;
    vc.modalPresentationStyle = UIModalPresentationFullScreen;
    [self presentViewController:vc animated:YES completion:nil];
}
- (void)screenShareBtnClicked:(UIButton*)btn
{
    if(![self isCaptureDeviceOK])
        return;
    
    if(_businessIDTextField.text.length == 0 || _accessTokenTextField.text.length == 0)
    {
        [self showMsg:@"参数不能为空" afterDelay:1.5];
        return;
    }

    DEMO_Setting.ilssRoomID     = _businessIDTextField.text;
    DEMO_Setting.ilssLiveRoomID = _roomIDTextField.text;
    DEMO_Setting.accessToken    = _accessTokenTextField.text;

    ScreenShareViewController * vc = [[ScreenShareViewController alloc] init];
    vc.ilssRoomID       = DEMO_Setting.ilssRoomID;
    vc.accessToken      = DEMO_Setting.accessToken;
    vc.anotherLiveRoomId= DEMO_Setting.ilssLiveRoomID;
    vc.extensionBundleID=@"com.vhallyun.rtc.VHScreenShare";
    //    vc.anotherLiveRoomID= DEMO_Setting.anotherLiveRoomID;
    vc.modalPresentationStyle = UIModalPresentationFullScreen;
    [self presentViewController:vc animated:YES completion:nil];
}

- (void)callBtnClicked:(UIButton*)btn
{
    if(![self isCaptureDeviceOK])
        return;
    
    if(_businessIDTextField.text.length == 0 || _accessTokenTextField.text.length == 0)
    {
        [self showMsg:@"参数不能为空" afterDelay:1.5];
        return;
    }

    DEMO_Setting.ilssRoomID     = _businessIDTextField.text;
    DEMO_Setting.ilssLiveRoomID = _roomIDTextField.text;
    DEMO_Setting.accessToken    = _accessTokenTextField.text;

    VHOTOCallViewController * vc = [[VHOTOCallViewController alloc] init];
    vc.ilssRoomID       = DEMO_Setting.ilssRoomID;
    vc.anotherLiveRoomId= DEMO_Setting.ilssLiveRoomID;
    vc.accessToken      = DEMO_Setting.accessToken;
    vc.modalPresentationStyle = UIModalPresentationFullScreen;
    [self presentViewController:vc animated:YES completion:nil];
}

- (void)initSDKView
{
    
    UITextField *businessIDTextField = [[UITextField alloc] initWithFrame:CGRectMake(20, 60, VHScreenWidth-40, 30)];
    businessIDTextField.placeholder = @"请输入互动房间ID inav_xxxx";
    businessIDTextField.text = DEMO_Setting.ilssRoomID;
    businessIDTextField.borderStyle = UITextBorderStyleRoundedRect;
    businessIDTextField.clearButtonMode=UITextFieldViewModeWhileEditing;
    businessIDTextField.delegate  = self;
    _businessIDTextField = businessIDTextField;
    
    [self.view addSubview:businessIDTextField];
    
    UITextField *accessTokenTextField = [[UITextField alloc] initWithFrame:CGRectMake(businessIDTextField.left, businessIDTextField.bottom+10, businessIDTextField.width, businessIDTextField.height)];
    accessTokenTextField.placeholder = @"请输入 accessToken";
    accessTokenTextField.text = DEMO_Setting.accessToken;
    accessTokenTextField.borderStyle = UITextBorderStyleRoundedRect;
    accessTokenTextField.clearButtonMode=UITextFieldViewModeWhileEditing;
    accessTokenTextField.delegate  = self;
    _accessTokenTextField = accessTokenTextField;
    [self.view addSubview:accessTokenTextField];
    
    UITextField *roomIDTextField = [[UITextField alloc] initWithFrame:CGRectMake(businessIDTextField.left, accessTokenTextField.bottom+10, businessIDTextField.width, businessIDTextField.height)];
    roomIDTextField.placeholder = @"请输入旁路roomID lss_xxxx（可选）";
    roomIDTextField.text = DEMO_Setting.ilssLiveRoomID;
    roomIDTextField.borderStyle = UITextBorderStyleRoundedRect;
    roomIDTextField.clearButtonMode=UITextFieldViewModeWhileEditing;
    roomIDTextField.delegate  = self;
    _roomIDTextField = roomIDTextField;
    [self.view addSubview:roomIDTextField];
    
    UIButton *nextBtn = [[UIButton alloc] initWithFrame:CGRectMake(accessTokenTextField.left, roomIDTextField.bottom+10, accessTokenTextField.width, accessTokenTextField.height)];
    [nextBtn setTitle:@"互动直播" forState:UIControlStateNormal];
    [nextBtn addTarget:self action:@selector(inavBtnClicked:) forControlEvents:UIControlEventTouchUpInside];
    nextBtn.backgroundColor = [UIColor lightGrayColor];
    [self.view addSubview:nextBtn];
    
    UIButton *callBtn = [[UIButton alloc] initWithFrame:CGRectMake(accessTokenTextField.left, nextBtn.bottom+10, accessTokenTextField.width, accessTokenTextField.height)];
    [callBtn setTitle:@"一对一呼叫" forState:UIControlStateNormal];
    [callBtn addTarget:self action:@selector(callBtnClicked:) forControlEvents:UIControlEventTouchUpInside];
    callBtn.backgroundColor = [UIColor lightGrayColor];
    [self.view addSubview:callBtn];
    
    UIButton *screenShareBtn = [[UIButton alloc] initWithFrame:CGRectMake(accessTokenTextField.left, callBtn.bottom+10, accessTokenTextField.width, accessTokenTextField.height)];
    [screenShareBtn setTitle:@"录屏互动" forState:UIControlStateNormal];
    [screenShareBtn addTarget:self action:@selector(screenShareBtnClicked:) forControlEvents:UIControlEventTouchUpInside];
    screenShareBtn.backgroundColor = [UIColor lightGrayColor];
    [self.view addSubview:screenShareBtn];
    
    UILabel * label= [[UILabel alloc] initWithFrame:CGRectMake(0, VHScreenHeight - 100, VHScreenWidth, 20)];
    label.font = [UIFont systemFontOfSize:12];
    label.textAlignment = NSTextAlignmentCenter;
    label.textColor = [UIColor grayColor];
    label.text = [NSString stringWithFormat:@"微吼云 VRTC SDK v%@",[VHInteractiveRoom getSDKVersion]];
    [self.view addSubview:label];
}
#pragma mark - 权限检查
//    iOS 判断应用是否有使用相机的权限
- (BOOL)isCaptureDeviceOK
{
    NSString *mediaType = AVMediaTypeVideo;//读取媒体类型
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:mediaType];//读取设备授权状态
    if(authStatus == AVAuthorizationStatusRestricted || authStatus == AVAuthorizationStatusDenied){
        NSString *errorStr = @"相机权限受限,请在设置中启用";
        [self showMsg:errorStr afterDelay:2];
        return NO;
    }
    
    mediaType = AVMediaTypeAudio;//读取媒体类型
    authStatus = [AVCaptureDevice authorizationStatusForMediaType:mediaType];//读取设备授权状态
    if(authStatus == AVAuthorizationStatusRestricted || authStatus == AVAuthorizationStatusDenied){
        NSString *errorStr = @"麦克风权限受限,请在设置中启用";
        [self showMsg:errorStr afterDelay:2];
        return NO;
    }
    
    return YES;
}

@end

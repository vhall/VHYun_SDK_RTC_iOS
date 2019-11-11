//
//  InitSDKViewController.m
//  VHYunSDKDemo_LSS
//
//  Created by vhall on 2019/7/19.
//  Copyright © 2019 vhall. All rights reserved.
//

#import "InitSDKViewController.h"
#import <objc/message.h>
#import "UIView+ITTAdditions.h"
#import "VHStystemSetting.h"

@interface InitSDKViewController ()
@property (weak, nonatomic) IBOutlet UITextField *appIDTextField;
@property (weak, nonatomic) IBOutlet UITextField *userIDTextField;
@property (weak, nonatomic) IBOutlet UILabel *bundleIDLabel;
@property (weak, nonatomic) IBOutlet UITextField *nicknameTextField;
@property (weak, nonatomic) IBOutlet UITextField *avatarTextField;
@end

@implementation InitSDKViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    [self initView];
    
}

- (void)viewDidLayoutSubviews
{
    [self.view viewWithTag:10099].top = _userIDTextField.bottom-2;
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/


- (void)initView
{
    NSLog(@"微吼云 Foundation Version: %@",[VHLiveBase getSDKVersion]);
    
    [VHLiveBase setAppGroup:DEMO_GroupID];

    _appIDTextField.text = DEMO_Setting.appID;
    _userIDTextField.text = DEMO_Setting.third_party_user_id;
    _nicknameTextField.text = DEMO_Setting.nickName;
    _avatarTextField.text = DEMO_Setting.avatar;
    _bundleIDLabel.text = [NSBundle mainBundle].bundleIdentifier;

    if([self respondsToSelector:@selector(initTestSwitch)])
        [self initTestSwitch];
}

- (IBAction)nextBtnClicked:(id)sender {
    [self hideKeyBoard];

    DEMO_Setting.appID = _appIDTextField.text;
    DEMO_Setting.third_party_user_id =_userIDTextField.text;
    
    if(DEMO_Setting.appID.length<=0)
    {
        [self showMsg:@"appID 不能为空" afterDelay:1];
        return;
    }
    if(DEMO_Setting.third_party_user_id.length<=0)
    {
        [self showMsg:@"用户ID 不能为空" afterDelay:1];
        return;
    }
    DEMO_Setting.nickName = _nicknameTextField.text;
    DEMO_Setting.avatar   = _avatarTextField.text;

    __weak typeof(self)wf = self;
    [VHLiveBase registerApp:DEMO_Setting.appID completeBlock:^(NSError *error) {
        if(error)
        {
            [wf showMsg:error.domain afterDelay:2];
        }
        else
        {
            [wf dismissViewControllerAnimated:YES completion:nil];
        }
    }];
    
    [VHLiveBase setThirdPartyUserId:DEMO_Setting.third_party_user_id context:@{@"nick_name":DEMO_Setting.nickName,@"avatar":DEMO_Setting.avatar}];
}

- (void)hideKeyBoard
{
    [self.view endEditing:YES];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

#pragma mark - 测试正式环境开关不可以暴露给客户
- (void)initTestSwitch
{
    [VHLiveBase setLogLevel:(VHLogLevel)5];
    [VHLiveBase printLogToConsole:YES];
    
    UISwitch *testSwitch = [[UISwitch alloc]initWithFrame:CGRectMake(25,0, 10, 10)];
    testSwitch.tag = 10099;
    [testSwitch addTarget:self action:@selector(testSwitchValueChanged:) forControlEvents:UIControlEventValueChanged];
    UILabel *l = [[UILabel alloc]initWithFrame:CGRectMake(testSwitch.width, 0, 80, testSwitch.height)];
    l.text = @"Release";
    l.textColor = [UIColor redColor];
    [testSwitch addSubview:l];
    [self.view addSubview:testSwitch];
    
    testSwitch.top = _userIDTextField.bottom-2;
#if (VHALL_HOST_INDEX == 0)// 测试环境
    testSwitch.on = NO;
#elif (VHALL_HOST_INDEX == 1)// 生产环境
    testSwitch.on = YES;
#endif
    
    [self testSwitchValueChanged:testSwitch];
}

- (void)testSwitchValueChanged:(UISwitch *)uiSwitch
{
    ((BOOL(*)(id,SEL,BOOL))objc_msgSend)([VHLiveBase class],@selector(setTestServerUrl:),!uiSwitch.on);
}

@end

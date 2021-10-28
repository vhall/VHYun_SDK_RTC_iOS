# VHYun_SDK_RTC_iOS
微吼云 音视频互动 SDK 及 Demo <br>

集成和调用方式，参见官方文档：http://www.vhallyun.com/docs/show/310.html <br>

### SDK 两种引入方式
1、pod 'VHYun_RTC'<br>
  请检查Frameworks路径是否正确配置 <br>
2、手动下载拖入工程设置路径、Embed&Sign<br>
注意依赖 https://github.com/vhall/VHYun_SDK_Core_iOS.git VHCore库<br>

### APP工程集成SDK基本设置
1、关闭bitcode 设置<br>
2、plist 中 App Transport Security Settings -> Allow Arbitrary Loads 设置为YES<br>
3、注册`AppKey`  [VHLiveBase registerApp:`AppKey`]; <br>
4、检查工程 `Bundle ID` 是否与`AppKey`对应 <br>
5、plist中添加相机、麦克风权限 <br>
6、互动功能暂不支持模拟器 <br>


### 版本更新信息

#### 版本 v2.4.0 更新时间：2021.10.27
更新内容：<br>
1、无延迟直播<br>
2、支持base重构版本<br>

#### 版本 v2.3.1 更新时间：2021.05.31
更新内容：<br>
1、日志上报优化<br>

#### 版本 v2.3.0 更新时间：2021.03.26
更新内容：<br>
1、支持竖屏旁路<br>
2、Render可以直接切换大小流<br>


#### 版本 v2.2.0 更新时间：2020.07.27
更新内容：<br>
1、优化开启旁路流程<br>
2、Render可以直接切换大小流<br>
3、修复推流状态不正确的bug<br>
4、修复收不到离开直播间消息的bug<br>
5、新增强制离开直播间回调以及消息<br>

#### 版本 v2.1.3 更新时间：2020.06.22
更新内容：<br>
1、修复数据统计bug<br>

#### 版本 v2.1.2 更新时间：2020.04.30
更新内容：<br>
1、偶尔播放声音小<br>
2、新增强制离开房间的接口<br>

#### 版本 v2.1.1 更新时间：2020.03.13
更新内容：<br>
1、支持Pods集成<br>

#### 版本 v2.1 更新时间：2020.01.08
更新内容：<br>
1、新增一对一呼叫功能<br>

#### 版本 v2.0.1 更新时间：2019.11.11
更新内容：<br>
1、互动优化<br>
2、互动增加美颜<br>

#### 版本 v2.0.0 更新时间：2019.08.21
更新内容：<br>
1、互动优化<br>
2、demo优化<br>



//
//  IVHBeautifyModule.h
//  VHLSS
//
//  Created by LiGuoliang on 2021/12/8.
//  Copyright © 2021 vhall. All rights reserved.
//
#ifndef IVHBeautifyModule_h
#define IVHBeautifyModule_h

#import <CoreMedia/CoreMedia.h>
#import <UIKit/UIKit.h>

@protocol IVHBeautifyModule <NSObject>

#pragma mark- 初始化
@required
/// ⚠️ 需要鉴权，但各自都不一样，所以暂不定义通用方法，仅定义方法前半段
/// ⚠️ + (Class)licenseWith....


#pragma mark- 数据处理
@required

/// 对SampleBuffer数据处理
/// @param sampleBuffer SampleBuffer数据
/// @param ts 时间戳
/// @param handle 加工完成回调
- (void)processedSampleBuffer:(CMSampleBufferRef)sampleBuffer pts:(uint64_t)ts handle:(void(^)(CMSampleBufferRef ref, uint64_t ts))handle;


/// 画面回显
- (UIView *)preView;

#pragma mark- 美颜设置
@optional

/// 是否让美颜生效
/// @param enable 生效?
- (void)enableBeautify:(BOOL)enable;


/// 调整美颜效果
/// @param key 具体查看 VHBeautifyEffectList
/// @param value 值 | NSNumber 0.0 ~ 1.0 || NSNumber true/false || NSString |
- (void)setEffectKey:(NSString *)key toValue:(id)value;

@end

#endif /* IVHBeautifyModule_h */

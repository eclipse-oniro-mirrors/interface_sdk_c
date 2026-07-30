/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup Vibrator
 * @{
 *
 * @brief Provides the enums, structs, and error codes used in the vibrator APIs.
 * @since 11
 */

/**
 * @file vibrator_type.h
 * @brief 提供标准的开放API，用于控制马达振动。该API支持多种振动场景（如报警、铃声、通知、通信、触摸、媒体、物理反馈、模拟现实等），通过设置振动优先级，能够满足不同场景下的振动需求，提升用户交互体验和设备使用体验。
 *
 * @kit SensorServiceKit
 * @library libohvibrator.z.so
 * @syscap SystemCapability.Sensors.MiscDevice
 * @since 11
 */


#ifndef VIBRATOR_TYPE_H
#define VIBRATOR_TYPE_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief 定义错误码，在使用振动相关API时，若发生异常情况会返回相应的错误码。
*
* @since 11
*/
typedef enum Vibrator_ErrorCode : int32_t {
    /**权限校验失败，请检查是否已申请所需权限（如ohos.permission.VIBRATE）。*/
    PERMISSION_DENIED = 201,
    /**参数检查失败，包括必选参数未传入、参数类型错误等。*/
    PARAMETER_ERROR = 401,
    /**设备不支持此API。通常在设备已支持该SysCap时，用于处理少量不支持的情况。*/
    UNSUPPORTED = 801,
    /**设备操作失败，请检查设备状态和参数配置。*/
    DEVICE_OPERATION_FAILED = 14600101,
} Vibrator_ErrorCode;

/**
 * @brief 振动优先级，用于定义不同场景下振动的优先级，高优先级的振动会打断低优先级的振动。使用时建议：根据应用场景选择合适的优先级；在需要连续振动的场景中保持一致优先级，避免频繁切换导致性能损耗；
 * 物理反馈和触摸类振动建议使用较高优先级以确保及时响应。
 *
 * @since 11
 */
typedef enum Vibrator_Usage {
    /**
     * 未知场景，最低优先级。用于无法确定具体使用场景时，系统按默认策略处理。
     */
    VIBRATOR_USAGE_UNKNOWN = 0,
    /**
     * 报警。用于闹钟、倒计时等提醒场景，振动强度较高，持续时间长。
     */
    VIBRATOR_USAGE_ALARM = 1,
    /**
     * 铃声。用于电话呼入场景，振动模式为循环振动，便于用户及时接听。
     */
    VIBRATOR_USAGE_RING = 2,
    /**
     * 通知。用于系统通知、应用消息等提醒场景，振动较短，提醒用户查看。
     */
    VIBRATOR_USAGE_NOTIFICATION = 3,
    /**
     * 通信。用于通话、即时通讯消息、短信等通信场景的振动反馈，振动模式为短促单次振动。
     */
    VIBRATOR_USAGE_COMMUNICATION = 4,
    /**
     * 触摸。用于屏幕触摸、按键操作等反馈场景，振动极短，提供操作确认感。
     */
    VIBRATOR_USAGE_TOUCH = 5,
    /**
     * 媒体。用于音乐、视频等媒体应用场景，振动与媒体内容同步，增强沉浸体验。
     */
    VIBRATOR_USAGE_MEDIA = 6,
    /**
     * 物理反馈。用于游戏、模拟等需要物理反馈的场景，提供物理按键反馈、触觉力反馈等物理交互体验，振动模式可自定义，模拟真实触感。
     */
    VIBRATOR_USAGE_PHYSICAL_FEEDBACK = 7,
    /**
     * 模拟现实。用于VR/AR等沉浸式场景的触觉反馈，振动强度和模式精确可控，提供逼真的环境反馈。
     */
    VIBRATOR_USAGE_SIMULATED_REALITY = 8,
    VIBRATOR_USAGE_MAX
} Vibrator_Usage;

/**
 * @brief Vibrator_Attribute结构体用于描述马达的属性信息。开发者使用该结构体可以指定马达ID和振动场景。具体使用场景和实现机制请参见{@link Vibrator}模块文档。
 *
 * @since 11
 */
typedef struct Vibrator_Attribute {
    /**马达ID，取值原则：通过系统接口获取有效值。指定要操作的马达设备标识，不同ID对应设备上不同的马达。取值范围为[0, 最大支持的马达数-1]。*/
    int32_t vibratorId;
    /**振动场景。指定振动的应用场景，不同场景对应不同的振动模式（如通知、按键、闹钟等各有相应的振动效果），可选值见Vibrator_Usage枚举定义。*/
    Vibrator_Usage usage;
} Vibrator_Attribute;

/**
 * @brief 振动文件描述。用于描述自定义振动序列的文件信息，支持使用自定义振动文件实现精确振动控制。
 *
 * @since 11
 */
typedef struct Vibrator_FileDescription {
    /**自定义振动序列的文件句柄，需指向包含振动序列数据的有效文件。使用前应通过文件操作API（如open）打开文件并获取句柄。fd必须为有效且可读的文件句柄，不能为负值或无效句柄。*/
    int32_t fd;
    /**
     * 自定义振动序列的偏移地址，单位为字节。用于指定从文件中读取振动序列的起始位置，offset≥0且小于文件大小。offset=0表示从文件开头读取，offset>0表示跳过前offset个字节。
     * offset超出文件大小时行为未定义。
     */
    int64_t offset;
    /**自定义振动序列的总长度，单位为字节。表示从offset位置开始读取的字节数。length必须>0，且offset+length不能超过文件大小。length超出文件剩余大小时可能读取失败或产生未定义行为。*/
    int64_t length;
} Vibrator_FileDescription;
#ifdef __cplusplus
}
#endif
/** @} */
#endif  // endif VIBRATOR_TYPE_H

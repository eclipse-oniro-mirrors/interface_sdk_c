/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Defines a set of Progress enum and interface.
 *
 * @since 12
 */

/**
 * @file progress.h
 *
 * @brief Defines a set of Progress enum and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_PROGRESS_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_PROGRESS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the linear progress indicator style.
 *
 * @since 15
 */
typedef struct ArkUI_ProgressLinearStyleOption ArkUI_ProgressLinearStyleOption;
/**
 * @brief 定义进度条类型枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 线性样式。*/
    ARKUI_PROGRESS_TYPE_LINEAR = 0,
    /** 环形无刻度样式。*/
    ARKUI_PROGRESS_TYPE_RING,
    /** 圆形样式。*/
    ARKUI_PROGRESS_TYPE_ECLIPSE,
    /** 环形有刻度样式。*/
    ARKUI_PROGRESS_TYPE_SCALE_RING,
    /** 胶囊样式。*/
    ARKUI_PROGRESS_TYPE_CAPSULE
} ArkUI_ProgressType;
/**
 * @brief 销毁线性进度条样式信息。
 *
 * @param option 线性进度条样式信息。
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_Destroy(ArkUI_ProgressLinearStyleOption* option);
/**
 * @brief 设置扫光效果的开关。
 *
 * @param option 线性进度条样式信息。
 * @param enabled 扫光效果的开关。true：表示开启扫光效果。false：表示关闭扫光效果。默认值：false。
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetScanEffectEnabled(ArkUI_ProgressLinearStyleOption* option, bool enabled);
/**
 * @brief 设置进度平滑动效的开关。
 *
 * @param option 线性进度条样式信息。
 * @param enabled 进度平滑动效的开关。开启平滑动效后设置进度，进度会从当前值渐变至设定值，否则进度从当前值突变至设定值。
 * true：表示开启进度平滑动效。false：表示关闭进度平滑动效。默认值：true。
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetSmoothEffectEnabled(ArkUI_ProgressLinearStyleOption* option, bool enabled);
/**
 * @brief 设置进度条宽度。
 *
 * @param option 线性进度条样式信息。
 * @param strokeWidth 进度条宽度值（不支持百分比设置），单位为vp，默认值：4.0vp。
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetStrokeWidth(ArkUI_ProgressLinearStyleOption* option, float strokeWidth);
/**
 * @brief 设置进度条圆角半径。
 *
 * @param option 线性进度条样式信息。
 * @param strokeRadius 进度条圆角半径值，单位为vp，取值范围[0, strokeWidth/2]。默认值：strokeWidth/2。
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetStrokeRadius(ArkUI_ProgressLinearStyleOption* option, float strokeRadius);
/**
 * @brief 获取扫光效果的开关信息。
 *
 * @param option 线性进度条样式信息。
 * @return 是否开启扫光效果。true：表示开启扫光效果。false：表示关闭扫光效果。默认值：false。
 * @since 15
 */
bool OH_ArkUI_ProgressLinearStyleOption_GetScanEffectEnabled(ArkUI_ProgressLinearStyleOption* option);
/**
 * @brief 获取进度平滑动效的开关信息。
 *
 * @param option 线性进度条样式信息。
 * @return 是否开启平滑动效。true：表示开启进度平滑动效。false：表示关闭进度平滑动效。默认值：true。
 * @since 15
 */
bool OH_ArkUI_ProgressLinearStyleOption_GetSmoothEffectEnabled(ArkUI_ProgressLinearStyleOption* option);
/**
 * @brief 获取进度条宽度。
 *
 * @param option 线性进度条样式信息。
 * @return 进度条宽度值，单位为vp。
 * @since 15
 */
float OH_ArkUI_ProgressLinearStyleOption_GetStrokeWidth(ArkUI_ProgressLinearStyleOption* option);
/**
 * @brief 获取进度条圆角半径值。
 *
 * @param option 线性进度条样式信息。
 * @return 进度条圆角半径值，单位为vp。
 * @since 15
 */
float OH_ArkUI_ProgressLinearStyleOption_GetStrokeRadius(ArkUI_ProgressLinearStyleOption* option);

/**
 * @brief 创建线性进度条样式信息。
 *
 * @return ProgressLinearStyleOption实例。
 * 如果返回空指针，可能是因为内存不足。
 * @since 15
 */
ArkUI_ProgressLinearStyleOption* OH_ArkUI_ProgressLinearStyleOption_Create(void);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_PROGRESS_H
/** @} */
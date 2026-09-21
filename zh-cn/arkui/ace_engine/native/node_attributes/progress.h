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
 * @brief 定义Progress相关的枚举和接口，支持线性、环形、圆形、胶囊等多种进度条类型，并提供线性进度条样式选项的自定义能力（平滑动效、扫光效果、宽度、圆角），适用于需要展示任务进度、加载状态等场景，
 *        帮助开发者快速实现多样化的进度展示和交互反馈。
 *
 * @since 12
 */

/**
 * @file progress.h
 *
 * @brief 定义Progress相关的枚举和接口，支持线性、环形、圆形、胶囊等多种进度条类型，并提供线性进度条样式选项的自定义能力（平滑动效、扫光效果、宽度、圆角），适用于需要展示任务进度、加载状态等场景，
 * 帮助开发者快速实现多样化的进度展示和交互反馈。
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
 * @brief 定义线性进度条的样式选项，适用于需要自定义线性进度条显示样式的场景。
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
    /**
     * 线性样式。
     */
    ARKUI_PROGRESS_TYPE_LINEAR = 0,
    /**
     * 环形无刻度样式，环形圆环逐渐显示直至完全填充。
     */
    ARKUI_PROGRESS_TYPE_RING,
    /**
     * 圆形样式，显示类似月圆月缺的进度展示效果，从月牙逐渐变化至满月。
     */
    ARKUI_PROGRESS_TYPE_ECLIPSE,
    /**
     * 环形有刻度样式，显示类似时钟刻度形式的进度展示效果。
     */
    ARKUI_PROGRESS_TYPE_SCALE_RING,
    /**
     * 胶囊样式，头尾两端圆弧处的进度展示效果与ARKUI_PROGRESS_TYPE_ECLIPSE相同，中段的进度展示效果与ARKUI_PROGRESS_TYPE_LINEAR相同。
     */
    ARKUI_PROGRESS_TYPE_CAPSULE
} ArkUI_ProgressType;

/**
 * @brief 创建线性进度条样式信息。使用完毕后必须调用{@link OH_ArkUI_ProgressLinearStyleOption_Destroy}释放资源，避免内存泄漏。
 *
 * @return ArkUI_ProgressLinearStyleOption实例，可用于配置线性进度条的平滑动效、扫光效果、宽度和圆角等显示样式。
 *     <br>如果返回空指针，可能是因为内存不足。
 * @since 15
 */
ArkUI_ProgressLinearStyleOption* OH_ArkUI_ProgressLinearStyleOption_Create(void);

/**
 * @brief 销毁线性进度条样式信息。必须与{@link OH_ArkUI_ProgressLinearStyleOption_Create}配对使用，
 * 参数option应通过OH_ArkUI_ProgressLinearStyleOption_Create()获取，调用OH_ArkUI_ProgressLinearStyleOption_Destroy()后不应再使用该对象。
 *
 * @param option 线性进度条样式信息。应通过OH_ArkUI_ProgressLinearStyleOption_Create()获取。
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_Destroy(ArkUI_ProgressLinearStyleOption* option);

/**
 * @brief 设置扫光效果的开关。适用于需要增强进度条视觉反馈效果的加载场景，如数据加载、文件上传等。扫光效果指进度条上有光线扫描移动的动态视觉效果。
 *
 * @param option 线性进度条样式信息。应通过OH_ArkUI_ProgressLinearStyleOption_Create()创建。
 * @param enabled 扫光效果的开关。
 *     <br>true：表示开启扫光效果。
 *     <br>false：表示关闭扫光效果。
 *     <br>默认值：false。
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetScanEffectEnabled(ArkUI_ProgressLinearStyleOption* option, bool enabled);

/**
 * @brief 设置进度平滑动效的开关。
 *
 * @param option 线性进度条样式信息。应通过OH_ArkUI_ProgressLinearStyleOption_Create()创建。
 * @param enabled 进度平滑动效的开关。开启平滑动效后设置进度，进度会从当前值渐变至设定值，否则进度从当前值突变至设定值。
 *     <br>true：表示开启进度平滑动效。
 *     <br>false：表示关闭进度平滑动效。
 *     <br>默认值：true。
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetSmoothEffectEnabled(ArkUI_ProgressLinearStyleOption* option, bool enabled);

/**
 * @brief 设置进度条宽度。
 *
 * @param option 线性进度条样式信息。应通过OH_ArkUI_ProgressLinearStyleOption_Create()创建。
 * @param strokeWidth 进度条宽度值（不支持百分比设置），单位为vp，取值需大于0，传入不合法值时使用默认值。默认值：4.0vp。设置strokeWidth会影响strokeRadius的取值范围，
 *     strokeRadius取值范围为[0, strokeWidth/2]。
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetStrokeWidth(ArkUI_ProgressLinearStyleOption* option, float strokeWidth);

/**
 * @brief 设置进度条圆角半径。
 *
 * @param option 线性进度条样式信息。应通过OH_ArkUI_ProgressLinearStyleOption_Create()创建。
 * @param strokeRadius 进度条圆角半径值，单位为vp，取值范围[0, strokeWidth/2]。值为0时进度条显示直角，值越大圆角越明显，最大值时显示为完全圆角。超出范围时自动修正为边界值。默认值：
 *     strokeWidth/2。
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetStrokeRadius(ArkUI_ProgressLinearStyleOption* option, float strokeRadius);

/**
 * @brief 获取扫光效果的开关信息。
 *
 * @param option 线性进度条样式信息。应通过OH_ArkUI_ProgressLinearStyleOption_Create()创建。
 * @return 是否开启扫光效果。true：表示开启扫光效果。false：表示关闭扫光效果。默认值：false。
 * @since 15
 */
bool OH_ArkUI_ProgressLinearStyleOption_GetScanEffectEnabled(ArkUI_ProgressLinearStyleOption* option);

/**
 * @brief 获取进度平滑动效的开关信息。
 *
 * @param option 线性进度条样式信息。应通过OH_ArkUI_ProgressLinearStyleOption_Create()创建。
 * @return 是否开启平滑动效。true：表示开启进度平滑动效。false：表示关闭进度平滑动效。默认值：true。
 * @since 15
 */
bool OH_ArkUI_ProgressLinearStyleOption_GetSmoothEffectEnabled(ArkUI_ProgressLinearStyleOption* option);

/**
 * @brief 获取进度条宽度。
 *
 * @param option 线性进度条样式信息。应通过OH_ArkUI_ProgressLinearStyleOption_Create()创建。
 * @return 进度条宽度值，单位为vp。
 * @since 15
 */
float OH_ArkUI_ProgressLinearStyleOption_GetStrokeWidth(ArkUI_ProgressLinearStyleOption* option);

/**
 * @brief 获取进度条圆角半径值。
 *
 * @param option 线性进度条样式信息。应通过OH_ArkUI_ProgressLinearStyleOption_Create()创建。
 * @return 进度条圆角半径值，单位为vp。
 * @since 15
 */
float OH_ArkUI_ProgressLinearStyleOption_GetStrokeRadius(ArkUI_ProgressLinearStyleOption* option);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_PROGRESS_H
/** @} */
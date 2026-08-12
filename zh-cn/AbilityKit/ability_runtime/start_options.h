/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup AbilityRuntime
 * @{
 *
 * @brief 提供应用启动参数数据结构AbilityRuntime_StartOptions以及设置和获取相关函数。
 *
 * @since 17
 */
/**
 * @file start_options.h
 *
 * @brief 提供应用启动参数数据结构{@link AbilityRuntime_StartOptions}以及设置和获取相关函数，用于启动Ability时配置窗口参数，支持设置窗口模式、位置、大小、显示效果和样式，支持不同窗口模式、
 * 多屏显示、动画效果和自定义窗口图标等场景。
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 17
 */

#ifndef ABILITY_RUNTIME_START_OPTIONS_H
#define ABILITY_RUNTIME_START_OPTIONS_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "ability_runtime_common.h"
#include "context_constant.h"
#include "multimedia/image_framework/image/pixelmap_native.h"

#ifdef __cplusplus
extern "C" {
#endif

struct AbilityRuntime_StartOptions;
typedef struct AbilityRuntime_StartOptions AbilityRuntime_StartOptions;

/**
 * @brief 创建{@link AbilityRuntime_StartOptions}对象。
 *
 * @return 返回指针类型AbilityRuntime_StartOptions对象。
 * @since 17
 */
AbilityRuntime_StartOptions* OH_AbilityRuntime_CreateStartOptions(void);

/**
 * @brief 销毁{@link AbilityRuntime_StartOptions}对象。
 *
 * @param startOptions 需要销毁的AbilityRuntime_StartOptions对象。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_DestroyStartOptions(AbilityRuntime_StartOptions **startOptions);

/**
 * @brief 设置启动Ability时的窗口模式。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowMode 启动Ability时的窗口模式。取值范围参见AbilityRuntime_WindowMode。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空或者WindowMode无效。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsWindowMode(AbilityRuntime_StartOptions *startOptions,
    AbilityRuntime_WindowMode windowMode);

/**
 * @brief 获取启动Ability时的窗口模式。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowMode 用于获取已设置的窗口模式。取值范围参见AbilityRuntime_WindowMode。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsWindowMode(AbilityRuntime_StartOptions *startOptions,
    AbilityRuntime_WindowMode &windowMode);
#endif

/**
 * @brief 设置启动Ability时窗口所在的屏幕ID。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param displayId 启动Ability时窗口所在的屏幕ID。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsDisplayId(AbilityRuntime_StartOptions *startOptions,
    int32_t displayId);

/**
 * @brief 获取启动Ability时窗口所在的屏幕ID。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param displayId 用于获取已设置的屏幕ID。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsDisplayId(AbilityRuntime_StartOptions *startOptions,
    int32_t &displayId);
#endif

/**
 * @brief 设置启动Ability时是否具有动画效果。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param withAnimation 启动Ability时是否具有动画效果。
 *     <br>true表示启动Ability时具有动画效果；false表示启动Ability时不具有动画效果。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsWithAnimation(AbilityRuntime_StartOptions *startOptions,
    bool withAnimation);

/**
 * @brief 获取启动Ability时是否具有动画效果。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param withAnimation 启动Ability时是否具有动画效果。
 *     true表示启动Ability时具有动画效果；false表示启动Ability时不具有动画效果。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsWithAnimation(AbilityRuntime_StartOptions *startOptions,
    bool &withAnimation);
#endif

/**
 * @brief 设置启动Ability时的窗口左侧位置，单位为px。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowLeft 启动Ability时的窗口左侧位置，单位为px。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsWindowLeft(AbilityRuntime_StartOptions *startOptions,
    int32_t windowLeft);

/**
 * @brief 获取启动Ability时的窗口左侧位置，单位为px。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowLeft 用于获取已设置的窗口左侧位置，单位为px。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsWindowLeft(AbilityRuntime_StartOptions *startOptions,
    int32_t &windowLeft);
#endif

/**
 * @brief 设置启动Ability时的窗口顶部位置，单位为px。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowTop 启动Ability时的窗口顶部位置，单位为px。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsWindowTop(AbilityRuntime_StartOptions *startOptions,
    int32_t windowTop);

/**
 * @brief 获取启动Ability时的窗口顶部位置，单位为px。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowTop 用于获取已设置的窗口顶部位置，单位为px。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsWindowTop(AbilityRuntime_StartOptions *startOptions,
    int32_t &windowTop);
#endif

/**
 * @brief 设置启动Ability时的窗口高度，单位为px。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowHeight 启动Ability时的窗口高度，单位为px。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsWindowHeight(AbilityRuntime_StartOptions *startOptions,
    int32_t windowHeight);

/**
 * @brief 获取启动Ability时的窗口高度，单位为px。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowHeight 用于获取已设置的窗口高度，单位为px。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsWindowHeight(AbilityRuntime_StartOptions *startOptions,
    int32_t &windowHeight);
#endif

/**
 * @brief 设置启动Ability时的窗口宽度，单位为px。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowWidth 启动Ability时的窗口宽度，单位为px。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsWindowWidth(AbilityRuntime_StartOptions *startOptions,
    int32_t windowWidth);

/**
 * @brief 获取启动Ability时的窗口宽度，单位为px。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowWidth 用于获取已设置的窗口宽度，单位为px。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsWindowWidth(AbilityRuntime_StartOptions *startOptions,
    int32_t &windowWidth);
#endif

/**
 * @brief 设置启动Ability时窗口和dock栏图标的显示模式。
 *
 * @param startOptions AbilityRuntime_StartOptions对象，包含启动Ability时的显示模式配置信息。
 * @param startVisibility 需要设置的显示模式。取值范围参见AbilityRuntime_StartVisibility。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示设置成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，
 *     或startVisibility取值不在枚举类AbilityRuntime_StartVisibility中。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsStartVisibility(AbilityRuntime_StartOptions *startOptions,
    AbilityRuntime_StartVisibility startVisibility);

/**
 * @brief 获取启动Ability时窗口和dock栏图标的显示模式。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param startVisibility 用于获取已设置的窗口和dock栏图标的显示模式。取值范围参见AbilityRuntime_StartVisibility。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示获取成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或startVisibility未被设置。
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsStartVisibility(AbilityRuntime_StartOptions *startOptions,
    AbilityRuntime_StartVisibility &startVisibility);
#endif

/**
 * @brief 设置启动Ability时的窗口启动图标。图片数据大小限制为600MB。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param startWindowIcon 启动Ability时的窗口启动图标。图片数据大小限制为600MB。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者startWindowIcon为空指针。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsStartWindowIcon(AbilityRuntime_StartOptions *startOptions,
    OH_PixelmapNative *startWindowIcon);

/**
 * @brief 获取启动Ability时的窗口启动图标。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param startWindowIcon 用于获取启动Ability时的窗口启动图标。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者startWindowIcon没有设置为空指针。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsStartWindowIcon(AbilityRuntime_StartOptions *startOptions,
    OH_PixelmapNative **startWindowIcon);

/**
 * @brief 设置启动Ability时的窗口背景颜色。如果未设置，则默认采用{@link module.json5配置文件}中{@link abilities标签}的startWindowBackground字段的配置。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param startWindowBackgroundColor 启动Ability时的窗口背景颜色。固定为ARGB格式，如：`#E5FFFFFF`。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者startWindowBackgroundColor为空指针。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsStartWindowBackgroundColor(
    AbilityRuntime_StartOptions *startOptions, const char *startWindowBackgroundColor);

/**
 * @brief 获取启动Ability时的窗口背景颜色。启动UIAbility时，启动页所显示的背景颜色如果未设置该字段，
 *     则默认采用module.json5配置文件中abilities标签的startWindowBackground字段的配置。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param startWindowBackgroundColor 用于获取启动Ability时的窗口背景颜色。固定为ARGB格式，如：`#E5FFFFFF`。
 * @param size 获取到的窗口背景颜色的大小。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示startOptions为空，
 *     或者startWindowBackgroundColor没有置为空指针。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_INTERNAL时，表示开发者无法恢复的内部错误，比如内部调用malloc错误，
 *     或者字符串拷贝函数出错。
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsStartWindowBackgroundColor(
    AbilityRuntime_StartOptions *startOptions, char **startWindowBackgroundColor, size_t &size);
#endif

/**
 * @brief 设置启动Ability时的组件所支持的窗口模式。如果未配置该字段，则默认采用该UIAbility对应的module.json5配置文件中，abilities标签的supportWindowMode字段的取值。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param supportedWindowModes 启动Ability时的组件所支持的窗口模式。取值范围参见AbilityRuntime_SupportedWindowMode。
 * @param size 组件所支持的窗口模式大小。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions或者SupportedWindowModes为空，或者size为0。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsSupportedWindowModes(
    AbilityRuntime_StartOptions *startOptions, AbilityRuntime_SupportedWindowMode *supportedWindowModes,
    size_t size);

/**
 * @brief 获取启动Ability时的组件所支持的窗口模式。如果未配置该字段，
 *     则默认采用该UIAbility对应的module.json5配置文件中abilities标签的supportWindowMode字段取值。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param supportedWindowModes 启动Ability时的组件所支持的窗口模式。取值范围参见AbilityRuntime_SupportedWindowMode。
 * @param size 组件所支持的窗口模式大小。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，
 *     或者supportedWindowModes参数为非空指针。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_INTERNAL时，表示开发者无法恢复的内部错误，比如内部调用malloc错误。
 * @release free {supportedWindowModes}
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsSupportedWindowModes(
    AbilityRuntime_StartOptions *startOptions, AbilityRuntime_SupportedWindowMode **supportedWindowModes,
    size_t &size);
#endif

/**
 * @brief 设置启动Ability时的窗口最小宽度，单位为vp。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param minWindowWidth 启动Ability时的窗口最小宽度，单位为vp。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsMinWindowWidth(
    AbilityRuntime_StartOptions *startOptions, int32_t minWindowWidth);

/**
 * @brief 获取启动Ability时的窗口最小宽度，单位为vp。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param minWindowWidth 启动Ability时的窗口最小宽度，单位为vp。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsMinWindowWidth(
    AbilityRuntime_StartOptions *startOptions, int32_t &minWindowWidth);
#endif

/**
 * @brief 设置启动Ability时的窗口最大宽度，单位为vp。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param maxWindowWidth 启动Ability时的窗口最大宽度，单位为vp。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsMaxWindowWidth(
    AbilityRuntime_StartOptions *startOptions, int32_t maxWindowWidth);

/**
 * @brief 获取启动Ability时的窗口最大宽度，单位为vp。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param maxWindowWidth 启动Ability时的窗口最大宽度，单位为vp。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsMaxWindowWidth(
    AbilityRuntime_StartOptions *startOptions, int32_t &maxWindowWidth);
#endif

/**
 * @brief 设置启动Ability时的窗口最小高度，单位为vp。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param minWindowHeight 启动Ability时的窗口最小高度，单位为vp。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsMinWindowHeight(
    AbilityRuntime_StartOptions *startOptions, int32_t minWindowHeight);

/**
 * @brief 获取启动Ability时的窗口最小高度，单位为vp。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param minWindowHeight 启动Ability时的窗口最小高度，单位为vp。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsMinWindowHeight(
    AbilityRuntime_StartOptions *startOptions, int32_t &minWindowHeight);
#endif

/**
 * @brief 设置启动Ability时的窗口最大高度，单位为vp。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param maxWindowHeight 启动Ability时的窗口最大高度，单位为vp。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_SetStartOptionsMaxWindowHeight(
    AbilityRuntime_StartOptions *startOptions, int32_t maxWindowHeight);

/**
 * @brief 获取启动Ability时的窗口最大高度，单位为vp。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param maxWindowHeight 启动Ability时的窗口最大高度，单位为vp。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空。
 * @since 17
 */
#ifdef __cplusplus
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsMaxWindowHeight(
    AbilityRuntime_StartOptions *startOptions, int32_t &maxWindowHeight);
#endif

/**
 * @brief 获取启动Ability时的窗口模式。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowMode 指向启动Ability时窗口模式的指针。取值范围参见AbilityRuntime_WindowMode。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者windowMode为空指针。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsWindowModeValue(AbilityRuntime_StartOptions *startOptions,
    AbilityRuntime_WindowMode *windowMode);

/**
 * @brief 获取启动Ability时窗口所在的屏幕ID。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param displayId 指向启动Ability时窗口所在屏幕ID的指针。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者displayId为空指针。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsDisplayIdValue(AbilityRuntime_StartOptions *startOptions,
    int32_t *displayId);

/**
 * @brief 获取启动Ability时是否具有动画效果。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param withAnimation 指向启动Ability时是否具有动画效果的指针。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者withAnimation为空指针。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsWithAnimationValue(AbilityRuntime_StartOptions *startOptions,
    bool *withAnimation);

/**
 * @brief 获取启动Ability时的窗口左侧位置，单位为px。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowLeft 指向启动Ability时窗口左侧位置的指针，单位为px。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者windowLeft为空指针。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsWindowLeftValue(AbilityRuntime_StartOptions *startOptions,
    int32_t *windowLeft);

/**
 * @brief 获取启动Ability时的窗口顶部位置，单位为px。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowTop 指向启动Ability时窗口顶部位置的指针，单位为px。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者windowTop为空指针。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsWindowTopValue(AbilityRuntime_StartOptions *startOptions,
    int32_t *windowTop);

/**
 * @brief 获取启动Ability时的窗口高度，单位为px。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowHeight 指向启动Ability时窗口高度的指针，单位为px。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者windowHeight为空指针。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsWindowHeightValue(AbilityRuntime_StartOptions *startOptions,
    int32_t *windowHeight);

/**
 * @brief 获取启动Ability时的窗口宽度，单位为px。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param windowWidth 指向启动Ability时窗口宽度的指针，单位为px。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者windowWidth为空指针。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsWindowWidthValue(AbilityRuntime_StartOptions *startOptions,
    int32_t *windowWidth);

/**
 * @brief 获取启动Ability时窗口和dock栏图标的显示模式。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param startVisibility 指向启动Ability时窗口和dock栏图标显示模式的指针。取值范围参见AbilityRuntime_StartVisibility。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者startVisibility为空指针。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsStartVisibilityValue(
    AbilityRuntime_StartOptions *startOptions, AbilityRuntime_StartVisibility *startVisibility);

/**
 * @brief 获取启动Ability时的窗口背景颜色。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param startWindowBackgroundColor 指向获取到的窗口背景颜色UTF-8字符串指针的二级指针，不能为空，且调用前必须指向空指针。固定为ARGB格式，如：`#E5FFFFFF`。使用完毕后，
 *     需要调用free释放。
 * @param size 指向获取到的窗口背景颜色字符串长度的指针，不能为空，不包含字符串结尾的空字符。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示任意参数无效。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_INTERNAL时，表示开发者无法恢复的内部错误，比如内部调用malloc错误。
 * @note If the background color is not set, {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned,
 *     *startWindowBackgroundColor remains NULL, and *size is set to 0.
 * @release free {startWindowBackgroundColor}
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsStartWindowBackgroundColorValue(
    AbilityRuntime_StartOptions *startOptions, char **startWindowBackgroundColor, size_t *size);

/**
 * @brief 获取启动Ability时的组件所支持的窗口模式。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param supportedWindowModes 指向获取到的组件所支持窗口模式数组指针的二级指针，不能为空，且调用前必须指向空指针。取值范围参见AbilityRuntime_SupportedWindowMode。使用完毕后，
 *     需要调用free释放。
 * @param size 指向获取到的组件所支持窗口模式数量的指针，不能为空。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示任意参数无效。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_INTERNAL时，表示开发者无法恢复的内部错误，比如内部调用malloc错误。
 * @note If no supported window modes are set, {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned,
 *     *supportedWindowModes remains NULL, and *size is set to 0.
 * @release free {supportedWindowModes}
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsSupportedWindowModesValue(
    AbilityRuntime_StartOptions *startOptions, AbilityRuntime_SupportedWindowMode **supportedWindowModes,
    size_t *size);

/**
 * @brief 获取启动Ability时的窗口最小宽度，单位为vp。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param minWindowWidth 指向启动Ability时窗口最小宽度的指针，单位为vp。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者minWindowWidth为空指针。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsMinWindowWidthValue(
    AbilityRuntime_StartOptions *startOptions, int32_t *minWindowWidth);

/**
 * @brief 获取启动Ability时的窗口最大宽度，单位为vp。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param maxWindowWidth 指向启动Ability时窗口最大宽度的指针，单位为vp。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者maxWindowWidth为空指针。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsMaxWindowWidthValue(
    AbilityRuntime_StartOptions *startOptions, int32_t *maxWindowWidth);

/**
 * @brief 获取启动Ability时的窗口最小高度，单位为vp。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param minWindowHeight 指向启动Ability时窗口最小高度的指针，单位为vp。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者minWindowHeight为空指针。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsMinWindowHeightValue(
    AbilityRuntime_StartOptions *startOptions, int32_t *minWindowHeight);

/**
 * @brief 获取启动Ability时的窗口最大高度，单位为vp。
 *
 * @param startOptions AbilityRuntime_StartOptions对象。
 * @param maxWindowHeight 指向启动Ability时窗口最大高度的指针，单位为vp。
 * @return 在返回ABILITY_RUNTIME_ERROR_CODE_NO_ERROR时，表示接口调用成功。
 *     <br>在返回ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID时，表示StartOptions为空，或者maxWindowHeight为空指针。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetStartOptionsMaxWindowHeightValue(
    AbilityRuntime_StartOptions *startOptions, int32_t *maxWindowHeight);

#ifdef __cplusplus
} // extern "C"
#endif

/** @} */
#endif // ABILITY_RUNTIME_START_OPTIONS_H
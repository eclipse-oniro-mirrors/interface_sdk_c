/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @brief Provides animation callbacks of ArkUI on the native side.
 *
 * @since 12
 */

/**
 * @file native_animate.h
 *
 * @brief 提供ArkUI在Native侧的动画接口定义集合。native_animate.h中的接口需要在主线程上调用。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_ANIMATE_H
#define ARKUI_NATIVE_ANIMATE_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 设置动画的期望帧率。
 *
 * @since 12
 */
typedef struct {
    /**
     * 期望的最小帧率，单位为帧/秒（fps）。
     */
    uint32_t min;
    /**
     * 期望的最大帧率，单位为帧/秒（fps）。
     */
    uint32_t max;
    /**
     * 期望的最优帧率，单位为帧/秒（fps）。
     */
    uint32_t expected;
} ArkUI_ExpectedFrameRateRange;

/**
 * @brief 动画播放结束回调类型。
 *
 * @since 12
 */
typedef struct {
    /**
     * 在动画中定义结束回调的类型。
     */
    ArkUI_FinishCallbackType type;
    /**
     * 动画播放结束回调。
     */
    void (*callback)(void* userData);
    /**
     * 用于动画结束回调，传递用户自定义数据。
     */
    void* userData;
} ArkUI_AnimateCompleteCallback;

/**
 * @brief 设置动画效果相关参数。
 *
 * @since 12
 */
typedef struct ArkUI_AnimateOption ArkUI_AnimateOption;

/**
 * @brief 提供曲线的插值对象定义。
 *
 * @since 12
 */
typedef struct ArkUI_Curve ArkUI_Curve;

/**
 * @brief 定义曲线的插值对象指针定义。
 *
 * @since 12
 */
typedef struct ArkUI_Curve* ArkUI_CurveHandle;

/**
 * @brief 定义关键帧动画参数对象。
 *
 * @since 12
 */
typedef struct ArkUI_KeyframeAnimateOption ArkUI_KeyframeAnimateOption;

/**
 * @brief 定义animator动画参数对象。
 *
 * @since 12
 */
typedef struct ArkUI_AnimatorOption ArkUI_AnimatorOption;

/**
 * @brief 定义animator动画对象指针。
 *
 * @since 12
 */
typedef struct ArkUI_Animator* ArkUI_AnimatorHandle;

/**
 * @brief 定义animator回调事件对象。
 *
 * @since 12
 */
typedef struct ArkUI_AnimatorEvent ArkUI_AnimatorEvent;

/**
 * @brief 定义animator接收到帧时回调对象。
 *
 * @since 12
 */
typedef struct ArkUI_AnimatorOnFrameEvent ArkUI_AnimatorOnFrameEvent;

/**
 * @brief 定义transition属性配置转场参数对象。
 *
 * @since 12
 */
typedef struct ArkUI_TransitionEffect ArkUI_TransitionEffect;

/**
 * @brief ArkUI提供的Native侧动画接口集合。
 *
 * @version 1
 * @since 12
 */
typedef struct {
    /**
     * @brief 显式动画接口。
     *
     * @note Make sure the component attributes to be set in the event closure have been set before.
     *
     * @param context UIContext实例。
     * @param option 设置动画效果相关参数。
     * @param update 指定动效的闭包函数，在闭包函数中导致的状态变化系统会自动插入过渡动画。
     *     <br>**说明**：在闭包函数中要设置的组件属性，必须在其之前设置过。
     * @param complete 设置动画播放完成回调参数。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     */
    int32_t (*animateTo)(ArkUI_ContextHandle context, ArkUI_AnimateOption* option, ArkUI_ContextCallback* update,
        ArkUI_AnimateCompleteCallback* complete);

    /**
     * @brief 关键帧动画接口。
     *
     * @param context UIContext实例。
     * @param option 关键帧动画参数。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     */
    int32_t (*keyframeAnimateTo)(ArkUI_ContextHandle context, ArkUI_KeyframeAnimateOption* option);

    /**
     * @brief 创建animator动画对象。
     *
     * @param context UIContext实例。
     * @param option animator动画参数。
     * @return animator动画对象指针。函数参数异常时返回NULL。
     */
    ArkUI_AnimatorHandle (*createAnimator)(ArkUI_ContextHandle context, ArkUI_AnimatorOption* option);

    /**
     * @brief 销毁animator动画对象。
     *
     * @param animatorHandle animator动画对象。
     */
    void (*disposeAnimator)(ArkUI_AnimatorHandle animatorHandle);
} ArkUI_NativeAnimateAPI_1;

/**
 * @brief 创建动画效果参数。
 *
 * @return 新的动画效果参数指针。
 * @since 12
 */
ArkUI_AnimateOption* OH_ArkUI_AnimateOption_Create();

/**
 * @brief 销毁动画效果参数指针。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，操作无效。
 * @since 12
 */
void OH_ArkUI_AnimateOption_Dispose(ArkUI_AnimateOption* option);

/**
 * @brief 获取动画持续时间，单位为ms（毫秒）。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，返回0。
 * @return 动画持续时间，单位为ms（毫秒）。option异常时返回0。
 * @since 12
 */
uint32_t OH_ArkUI_AnimateOption_GetDuration(ArkUI_AnimateOption* option);

/**
 * @brief 获取动画播放速度。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，返回0.0。
 * @return 动画播放速度。取值范围：[0, +∞)。option异常时返回0.0。
 * @since 12
 */
float OH_ArkUI_AnimateOption_GetTempo(ArkUI_AnimateOption* option);

/**
 * @brief 获取动画曲线。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，返回-1。
 * @return 动画曲线。option异常时返回-1。
 * @since 12
 */
ArkUI_AnimationCurve OH_ArkUI_AnimateOption_GetCurve(ArkUI_AnimateOption* option);

/**
 * @brief 获取动画延迟播放时间，单位为ms（毫秒）。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，返回0。
 * @return 动画延迟播放时间。option异常时返回0。
 * @since 12
 */
int32_t OH_ArkUI_AnimateOption_GetDelay(ArkUI_AnimateOption* option);

/**
 * @brief 获取动画播放次数。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，返回0。
 * @return 动画播放次数。option异常时返回0。
 * @since 12
 */
int32_t OH_ArkUI_AnimateOption_GetIterations(ArkUI_AnimateOption* option);

/**
 * @brief 获取动画播放模式。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，返回-1。
 * @return 动画播放模式。option异常时返回-1。
 * @since 12
 */
ArkUI_AnimationPlayMode OH_ArkUI_AnimateOption_GetPlayMode(ArkUI_AnimateOption* option);

/**
 * @brief 获取动画的期望帧率。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，返回NULL。
 * @return 动画的期望帧率，单位为帧/秒（fps）。option异常时返回NULL。
 * @since 12
 */
ArkUI_ExpectedFrameRateRange* OH_ArkUI_AnimateOption_GetExpectedFrameRateRange(ArkUI_AnimateOption* option);

/**
 * @brief 设置动画持续时间，单位为ms（毫秒）。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，操作无效。
 * @param value 动画持续时间，单位为ms（毫秒）。取值范围：[0, +∞)。
 *     <br>value小于0时，按0处理。
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetDuration(ArkUI_AnimateOption* option, int32_t value);

/**
 * @brief 设置动画播放速度。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，操作无效。
 * @param value 动画播放速度。取值范围：[0, +∞)。
 *     **说明：**
 *     传入小于0的数值，会默认设置为1。
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetTempo(ArkUI_AnimateOption* option, float value);

/**
 * @brief 设置动画曲线。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，操作无效。
 * @param value 动画曲线。默认值：{@link ARKUI_CURVE_LINEAR}，建议使用{@link ARKUI_CURVE_EASE_IN_OUT}获得更平滑的动画效果。
 *     <br>value值异常时，设置无效。
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetCurve(ArkUI_AnimateOption* option, ArkUI_AnimationCurve value);

/**
 * @brief 设置动画延迟播放时间，单位为ms（毫秒）。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，操作无效。
 * @param value 动画延迟播放时间，单位为ms（毫秒）。取值范围：(-∞, +∞)。默认值：0，表示不延迟。value大于0时表示延迟播放，小于0表示提前播放。value小于0时，如果value的绝对值小于实际动画时长，
 *     动画将在开始后第一帧直接运动到value绝对值的时刻的状态；如果value的绝对值大于等于实际动画时长，动画将在开始后第一帧直接运动到终点状态。其中实际动画时长等于单次动画时长乘以动画播放次数。
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetDelay(ArkUI_AnimateOption* option, int32_t value);

/**
 * @brief 设置动画播放次数。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，操作无效。
 * @param value 动画播放次数。取值范围：[-1, +∞)，其中设置为0时不播放，-1表示无限次播放。默认值：1（播放一次）。
 *     <br>value小于-1时，操作无效。
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetIterations(ArkUI_AnimateOption* option, int32_t value);

/**
 * @brief 设置动画播放模式。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，操作无效。
 * @param value 动画播放模式。默认值：{@link ARKUI_ANIMATION_PLAY_MODE_NORMAL}。
 *     <br>value值异常时，操作无效。
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetPlayMode(ArkUI_AnimateOption* option, ArkUI_AnimationPlayMode value);

/**
 * @brief 设置动画的期望帧率。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，操作无效。
 * @param value 动画的期望帧率，单位为帧/秒（fps）。
 *     <br>value为NULL时，操作无效。
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(ArkUI_AnimateOption* option, ArkUI_ExpectedFrameRateRange* value);

/**
 * @brief 设置动画的动画曲线。
 *
 * @note This method is better than the value set by OH_ArkUI_AnimateOption_SetCurve.
 * @param option 设置动画效果相关参数。
 *     <br>option为NULL时，操作无效。
 * @param value 动画曲线参数。
 *     <br>value为NULL时，操作无效。
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetICurve(ArkUI_AnimateOption* option, ArkUI_CurveHandle value);

/**
 * @brief 获取动画的动画曲线。
 *
 * @param option 设置动画效果相关参数。
 *     <br>option为NULL时，返回NULL。
 * @return 动画的动画曲线。参数option异常时返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_AnimateOption_GetICurve(ArkUI_AnimateOption* option);

/**
 * @brief 创建关键帧动画参数。
 *
 * @param size 关键帧动画状态数。
 *     <br>size小于0时返回NULL。
 * @return 关键帧动画参数对象。size小于0时返回NULL，option异常时返回NULL。
 * @since 12
 */
ArkUI_KeyframeAnimateOption* OH_ArkUI_KeyframeAnimateOption_Create(int32_t size);

/**
 * @brief 销毁关键帧动画参数。
 *
 * @param option 关键帧动画参数对象。
 *     <br>option为NULL时，操作无效。
 * @since 12
 */
void OH_ArkUI_KeyframeAnimateOption_Dispose(ArkUI_KeyframeAnimateOption* option);

/**
 * @brief 设置关键帧动画的整体延时时间，单位为ms（毫秒），默认不延时播放。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画延迟播放时间，单位为ms（毫秒）。取值范围：(-∞, +∞)。默认值：0，表示不延迟。value大于0为延迟播放，value小于0表示提前播放。对于value小于0的情况：
 *     当value的绝对值小于实际动画时长，动画将在开始后第一帧直接运动到value绝对值的时刻的状态；当value的绝对值大于等于实际动画时长，动画将在开始后第一帧直接运动到终点状态。
 *     其中实际动画时长等于单次动画时长乘以动画播放次数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetDelay(ArkUI_KeyframeAnimateOption* option, int32_t value);

/**
 * @brief 设置关键帧动画的动画播放次数。默认播放一次，设置为-1时表示无限次播放，设置为0时表示无动画效果。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画播放次数。取值范围：[-1, +∞)，其中设置为0时不播放，-1表示无限次播放。默认值：1，表示播放一次。
 *     <br>value小于-1时，操作无效，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetIterations(ArkUI_KeyframeAnimateOption* option, int32_t value);

/**
 * @brief 设置关键帧动画播放完成回调。当关键帧动画{@link ArkUI_KeyframeAnimateOption}所有次数播放完成后调用。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param userData 用户自定义对象指针。
 *     <br>不涉及异常值处理。
 * @param onFinish Indicates the callback.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_RegisterOnFinishCallback(
    ArkUI_KeyframeAnimateOption* option, void* userData, void (*onFinish)(void* userData));

/**
 * @brief 设置关键帧动画期望帧率。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param frameRate 关键帧动画的期望帧率。
 *     <br>frameRate为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetExpectedFrameRate(
    ArkUI_KeyframeAnimateOption* option, ArkUI_ExpectedFrameRateRange* frameRate);

/**
 * @brief 设置关键帧动画某段关键帧动画的持续时间，单位为ms（毫秒）。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 关键帧动画的持续时间，单位为ms（毫秒），默认值1000ms。取值范围：[0, +∞)。
 *     <br>value小于0时，按0处理。
 * @param index 状态索引值。
 *     <br>index小于0时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetDuration(ArkUI_KeyframeAnimateOption* option, int32_t value, int32_t index);

/**
 * @brief 设置关键帧动画某段关键帧使用的动画曲线。
 *
 * @note Because the <b>springMotion</b>, <b>responsiveSpringMotion</b>, and <b>interpolatingSpring</b> curves do not
 *     have effective duration settings, they are not supported.
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 该关键帧使用的动画曲线。默认值：{@link ARKUI_CURVE_EASE_IN_OUT}。
 * @param index 状态索引值。取值范围：[0, size-1]，其中size为关键帧动画状态数。
 *     <br>index小于0或index超出范围时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetCurve(
    ArkUI_KeyframeAnimateOption* option, ArkUI_CurveHandle value, int32_t index);

/**
 * @brief 设置关键帧时刻状态的闭包函数，即在该关键帧时刻要达到的状态。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param event Indicates a closure function.
 * @param userData 用户定义对象指针。
 *     <br>不涉及异常值处理。
 * @param index 状态索引值。取值范围：[0, size-1]，其中size为关键帧动画状态数。
 *     <br>index小于0或index超出范围时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_RegisterOnEventCallback(
    ArkUI_KeyframeAnimateOption* option, void* userData, void (*event)(void* userData), int32_t index);

/**
 * @brief 获取关键帧整体延时时间，单位为ms（毫秒）。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回0。
 * @return 整体延时时间，单位为ms（毫秒）。option异常时返回0。
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_GetDelay(ArkUI_KeyframeAnimateOption* option);

/**
 * @brief 获取关键帧动画播放次数。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回0。
 * @return 动画播放次数。option异常时返回0。
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_GetIterations(ArkUI_KeyframeAnimateOption* option);

/**
 * @brief 获取关键帧动画参数的期望帧率。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回NULL。
 * @return 关键帧动画参数的期望帧率。option异常时返回NULL。
 * @since 19
 */
ArkUI_ExpectedFrameRateRange* OH_ArkUI_KeyframeAnimateOption_GetExpectedFrameRate(ArkUI_KeyframeAnimateOption* option);

/**
 * @brief 获取关键帧动画某段状态持续时间，单位为ms（毫秒）。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回0。
 * @param index 状态索引值。
 *     <br>index小于0时，返回0。
 * @return 持续时间，单位为ms（毫秒）。option异常时返回0。
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_GetDuration(ArkUI_KeyframeAnimateOption* option, int32_t index);

/**
 * @brief 获取关键帧动画某段状态动画曲线。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回NULL。
 * @param index 状态索引值。
 *     <br>index小于0时，返回NULL。
 * @return 动画曲线。参数异常时返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_KeyframeAnimateOption_GetCurve(ArkUI_KeyframeAnimateOption* option, int32_t index);

/**
 * @brief 创建animator动画对象参数。
 *
 * @note When <b>keyframeSize</b> is greater than 0, the animation interpolation start point is 0, and the animation
 *     interpolation end point is 1; no setting is allowed.
 * @param keyframeSize 关键帧个数。
 *     <br>keyframeSize小于0时返回NULL。
 * @return animator动画对象参数指针。size小于0时返回NULL，option异常时返回NULL。
 * @since 12
 */
ArkUI_AnimatorOption* OH_ArkUI_AnimatorOption_Create(int32_t keyframeSize);

/**
 * @brief 销毁animator动画对象参数。
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，操作无效。
 * @since 12
 */
void OH_ArkUI_AnimatorOption_Dispose(ArkUI_AnimatorOption* option);

/**
 * @brief 设置animator动画播放的时长，单位毫秒。
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 播放的时长，单位为ms（毫秒），默认值0ms。取值范围：[0, +∞)。
 *     <br>value小于0时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetDuration(ArkUI_AnimatorOption* option, int32_t value);

/**
 * @brief 设置animator动画延时播放的时间，单位为ms（毫秒）。
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画延迟播放时间，单位为ms（毫秒）。取值范围：(-∞, +∞)。默认值：0，表示不延迟。value大于0为延迟播放，value小于0表示提前播放。对于value小于0的情况：
 *     当value的绝对值小于实际动画时长，动画将在开始后第一帧直接运动到value绝对值的时刻的状态；当value的绝对值大于等于实际动画时长，动画将在开始后第一帧直接运动到终点状态。
 *     其中实际动画时长等于单次动画时长乘以动画播放次数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetDelay(ArkUI_AnimatorOption* option, int32_t value);

/**
 * @brief 设置animator动画播放次数。默认播放一次，设置为-1时表示无限次播放，设置为0时表示无动画效果。
 *
 * @note If this parameter is set to a negative value other than <b>-1</b>, the value is invalid. In this case, the
 *     animation is played once.
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 取值范围：[-1, +∞)，其中设置为0时不播放，-1表示无限次播放。默认值：1（播放一次）。
 *     <br>value小于-1时，操作无效。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetIterations(ArkUI_AnimatorOption* option, int32_t value);

/**
 * @brief 设置animator动画执行时组件在动画开始前和结束后的状态。
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画执行时组件在动画开始前和结束后的状态。默认值：{@link ARKUI_ANIMATION_FILL_MODE_FORWARDS}。
 *     <br>value小于0时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetFill(ArkUI_AnimatorOption* option, ArkUI_AnimationFillMode value);

/**
 * @brief 设置animator动画播放方向。
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画播放方向。
 *     <br>value小于0时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetDirection(ArkUI_AnimatorOption* option, ArkUI_AnimationDirection value);

/**
 * @brief 设置animator动画插值曲线。
 *
 * @note <b>springCurve</b>, <b>springMotion</b>, <b>responsiveSpringMotion</b>, <b>interpolatingSpring</b>,
 *     and <b>customCurve</b> curves are not supported.
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画插值曲线。默认值：{@link ARKUI_CURVE_LINEAR}，建议使用{@link ARKUI_CURVE_EASE_IN_OUT}获得更平滑的动画效果。
 *     <br>value为NULL时，使用默认曲线{@link ARKUI_CURVE_LINEAR}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetCurve(ArkUI_AnimatorOption* option, ArkUI_CurveHandle value);

/**
 * @brief 设置animator动画插值起点。
 *
 * @note This API does not take effect when the animation is a keyframe animation.
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画插值起点。取值范围：(-∞, +∞)。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetBegin(ArkUI_AnimatorOption* option, float value);

/**
 * @brief 设置animator动画插值终点。
 *
 * @note This API does not take effect when the animation is a keyframe animation.
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画插值终点。取值范围：(-∞, +∞)。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetEnd(ArkUI_AnimatorOption* option, float value);

/**
 * @brief 设置animator动画期望的帧率范围。
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 期望的帧率范围对象。
 *     <br>value为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetExpectedFrameRateRange(
    ArkUI_AnimatorOption* option, ArkUI_ExpectedFrameRateRange* value);

/**
 * @brief 设置animator动画关键帧参数。
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param time 关键帧时间。取值范围：[0, 1], 必须是递增。默认值：按索引均匀分布（如第1帧为0.0，第2帧为0.5，第3帧为1.0）。
 *     <br>time小于0或time大于1时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 关键帧数值。取值范围：(-∞, +∞)。
 * @param index 关键帧的索引值。
 *     <br>index小于0时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetKeyframe(
    ArkUI_AnimatorOption* option, float time, float value, int32_t index);

/**
 * @brief 设置animator动画关键帧曲线类型。
 *
 * @note <b>springCurve</b>, <b>springMotion</b>, <b>responsiveSpringMotion</b>, <b>interpolatingSpring</b>,
 *     and <b>customCurve</b> curves are not supported.
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画插值曲线。默认值：NULL，表示线性插值。
 * @param index 关键帧的索引值。
 *     <br>index小于0时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetKeyframeCurve(ArkUI_AnimatorOption* option, ArkUI_CurveHandle value, int32_t index);

/**
 * @brief 获取animator动画播放的时长。
 *
 * @param option animator动画参数。
 *     <br>option为NULL时，返回0。
 * @return 动画播放的时长，单位毫秒。option异常时返回0。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_GetDuration(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画延时播放时长。
 *
 * @param option animator动画参数。option为NULL时，返回0。
 * @return 动画延时播放时长，单位毫秒。option异常时返回0。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_GetDelay(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画播放次数。
 *
 * @param option animator动画动画参数。option为NULL时，返回0。
 * @return 动画播放次数。option异常时返回0。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_GetIterations(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画执行时组件在动画开始前和结束后的状态。
 *
 * @param option animator动画参数。
 * @return 动画执行时组件在动画开始前和结束后的状态。option异常时返回-1。
 * @since 12
 */
ArkUI_AnimationFillMode OH_ArkUI_AnimatorOption_GetFill(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画播放方向。
 *
 * @param option animator动画参数。
 * @return 动画播放方向。option异常时返回-1。
 * @since 12
 */
ArkUI_AnimationDirection OH_ArkUI_AnimatorOption_GetDirection(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画插值曲线。
 *
 * @param option animator动画参数。
 * @return 动画插值曲线。option异常时返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_AnimatorOption_GetCurve(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画插值起点。
 *
 * @param option animator动画参数。
 * @return 动画插值起点。option异常时返回0.0。
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetBegin(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画插值终点。
 *
 * @param option animator动画参数。
 * @return 动画插值终点。option异常时返回0.0。
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetEnd(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画期望的帧率范围。
 *
 * @param option animator动画参数。
 * @return 期望的帧率范围对象指针。函数参数异常时返回NULL。
 * @since 12
 */
ArkUI_ExpectedFrameRateRange* OH_ArkUI_AnimatorOption_GetExpectedFrameRateRange(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画关键帧时间，单位为ms（毫秒）。
 *
 * @param option animator动画对象参数。
 * @param index 关键帧的索引值。
 * @return 关键帧时间，单位为ms（毫秒）。
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetKeyframeTime(ArkUI_AnimatorOption* option, int32_t index);

/**
 * @brief 获取animator动画关键帧数值。
 *
 * @param option animator动画对象参数。
 * @param index 关键帧的索引值。
 * @return 关键帧数值。
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetKeyframeValue(ArkUI_AnimatorOption* option, int32_t index);

/**
 * @brief 获取animator动画关键帧动画插值曲线。
 *
 * @param option animator动画对象参数。
 * @param index 关键帧的索引值。
 * @return 动画插值曲线。函数参数异常时返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_AnimatorOption_GetKeyframeCurve(ArkUI_AnimatorOption* option, int32_t index);

/**
 * @brief 获取动画事件对象中的用户自定义对象。
 *
 * @param event 动画事件对象。
 * @return 用户自定义对象。
 * @since 12
 */
void* OH_ArkUI_AnimatorEvent_GetUserData(ArkUI_AnimatorEvent* event);

/**
 * @brief 获取动画的帧事件中的用户自定义对象。
 *
 * @param event 动画事件对象。
 * @return 用户自定义对象。
 * @since 12
 */
void* OH_ArkUI_AnimatorOnFrameEvent_GetUserData(ArkUI_AnimatorOnFrameEvent* event);

/**
 * @brief 获取动画帧回调事件对象中的插值结果。
 *
 * @param event 动画事件对象。
 * @return 动画插值结果。
 *     **说明：**
 *     在动画过程中，插值结果根据动画参数在插值起点{@link OH_ArkUI_AnimatorOption_SetBegin}和插值终点{@link OH_ArkUI_AnimatorOption_SetEnd}间变化。
 * @since 12
 */
float OH_ArkUI_AnimatorOnFrameEvent_GetValue(ArkUI_AnimatorOnFrameEvent* event);

/**
 * @brief 设置animator动画接收到帧时回调。
 *
 * @param option animator动画参数。
 * @param userData 用户自定义参数。
 * @param callback Indicates the callback to set.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_RegisterOnFrameCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorOnFrameEvent* event));

/**
 * @brief 设置animator动画完成时回调。
 *
 * @param option animator动画参数。
 * @param userData 用户自定义参数。
 * @param callback Indicates the callback to set.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_RegisterOnFinishCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event));

/**
 * @brief 设置animator动画被取消时回调。
 *
 * @param option animator动画参数。
 * @param userData 用户自定义参数。
 * @param callback Indicates the callback to set.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_RegisterOnCancelCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event));

/**
 * @brief 设置animator动画重复时回调。
 *
 * @param option animator动画参数。
 * @param userData 用户自定义参数。
 * @param callback Indicates the callback to set.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_RegisterOnRepeatCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event));

/**
 * @brief 重置animator动画。
 *
 * @param animatorHandle animator动画对象。
 * @param option animator动画参数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_Animator_ResetAnimatorOption(
    ArkUI_AnimatorHandle animatorHandle, ArkUI_AnimatorOption* option);

/**
 * @brief 启动animator动画。
 *
 * @param animatorHandle animator动画对象。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_Animator_Play(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief 结束animator动画。
 *
 * @param animatorHandle animator动画对象。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_Animator_Finish(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief 暂停animator动画。
 *
 * @param animatorHandle animator动画对象。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_Animator_Pause(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief 取消animator动画。
 *
 * @param animatorHandle animator动画对象。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_Animator_Cancel(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief 以相反的顺序播放animator动画。
 *
 * @param animatorHandle animator动画对象。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_Animator_Reverse(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief 插值曲线的初始化函数，可以根据入参创建一个插值曲线对象。
 *
 * @param curve 曲线类型。
 * @return 曲线的插值对象指针。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCurveByType(ArkUI_AnimationCurve curve);

/**
 * @brief 构造阶梯曲线对象。
 *
 * @param count 阶梯的数量，需要为正整数，取值范围：[1, +∞)。
 *     <br>count值异常时，操作无效。
 * @param end 在每个间隔的起点或是终点发生阶跃变化。true：在终点发生阶跃变化。false：在起点发生阶跃变化。
 * @return 曲线的插值对象指针。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateStepsCurve(int32_t count, bool end);

/**
 * @brief 构造三阶贝塞尔曲线对象。
 *
 * @param x1 确定贝塞尔曲线第一点横坐标，取值范围：[0, 1]。设置的值小于0时，按0处理；设置的值大于1时，按1处理。
 * @param y1 确定贝塞尔曲线第一点纵坐标。
 * @param x2 确定贝塞尔曲线第二点横坐标，取值范围：[0, 1]。设置的值小于0时，按0处理；设置的值大于1时，按1处理。
 * @param y2 确定贝塞尔曲线第二点纵坐标。
 * @return 曲线的插值对象指针。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCubicBezierCurve(float x1, float y1, float x2, float y2);

/**
 * @brief 构造弹簧曲线对象，曲线形状由弹簧参数决定，动画时长受{@link animation}、{@link animateTo}中的duration参数控制。
 *
 * @param velocity 初始速度。是由外部因素对弹性动效产生的影响参数，其目的是保证对象从之前的运动状态平滑的过渡到弹性动效。该速度是归一化速度，其值等于动画开始时的实际速度除以动画属性改变值。
 * @param mass 质量。弹性系统的受力对象，会对弹性系统产生惯性影响。质量越大，震荡的幅度越大，恢复到平衡位置的速度越慢。取值范围：[0, +∞)。
 *     <br>value小于等于0时，按1处理。
 * @param stiffness 刚度。是物体抵抗施加的力而形变的程度。在弹性系统中，刚度越大，抵抗变形的能力越强，恢复到平衡位置的速度就越快。取值范围：[0, +∞)。
 *     <br>value小于等于0时，按1处理。
 * @param damping 阻尼。用于描述系统在受到扰动后震荡及衰减的情形。阻尼越大，弹性运动的震荡次数越少、震荡幅度越小。取值范围：[0, +∞)。
 *     <br>value小于等于0时，按1处理。
 * @return 曲线的插值对象指针。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateSpringCurve(float velocity, float mass, float stiffness, float damping);

/**
 * @brief 构造弹性动画曲线对象。如果对同一对象的同一属性进行多个弹性动画，每个动画会替换掉前一个动画，并继承之前的速度。
 *
 * @note The animation duration is subject to the curve parameters, rather than the <b>duration</b> parameter in
 *     <b>animation</b> or <b>animateTo</b>.
 *
 * @param response 弹簧自然振动周期，决定弹簧复位的速度。取值范围：(0, +∞)。
 *     <br>参数小于等于0时，按0.55处理。
 * @param dampingFraction 阻尼系数。大于0小于1的值为欠阻尼，运动过程中会超出目标值；等于1为临界阻尼；大于1为过阻尼，运动过程中逐渐趋于目标值。取值范围：(0, +∞)。
 *     <br>参数小于等于0时，按0.825处理。
 * @param overlapDuration 弹性动画衔接时长。发生动画继承时，如果前后两个弹性动画response不一致，response参数会在overlapDuration时间内平滑过渡。取值范围：[0, +∞)。
 *     <br>参数小于0时，按0处理。
 * @return 曲线的插值对象指针。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateSpringMotion(float response, float dampingFraction, float overlapDuration);

/**
 * @brief 构造弹性跟手动画曲线对象，是springMotion的一种特例，仅默认参数不同，可与springMotion混合使用。
 *
 * @note The animation duration is subject to the curve parameters, rather than the <b>duration</b> parameter in
 *     <b>animation</b> or <b>animateTo</b>.
 *
 * @param response 弹簧自然振动周期，决定弹簧复位的速度。取值范围：(0, +∞)。
 *     <br>参数小于等于0时，按0.15处理。
 * @param dampingFraction 阻尼系数。大于0小于1的值为欠阻尼，运动过程中会超出目标值；等于1为临界阻尼；大于1为过阻尼，运动过程中逐渐趋于目标值。取值范围：[0, +∞)。
 *     <br>参数小于0时，按0.86处理。
 * @param overlapDuration 弹性动画衔接时长。发生动画继承时，如果前后两个弹性动画response不一致，response参数会在overlapDuration时间内平滑过渡。取值范围：[0, +∞)。
 *     <br>参数小于0时，按0.25处理。
 * @return 曲线的插值对象指针。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateResponsiveSpringMotion(
    float response, float dampingFraction, float overlapDuration);

/**
 * @brief 构造插值器弹簧曲线对象，生成一条从0到1的动画曲线，实际动画值根据曲线进行插值计算。
 *
 * @note The animation duration is subject to the curve parameters, rather than the <b>duration</b> parameter in
 *     <b>animation</b> or <b>animateTo</b>.
 *
 *
 * @param velocity 初始速度。外部因素对弹性动效产生的影响参数，目的是保证对象从之前的运动状态平滑地过渡到弹性动效。该速度是归一化速度，其值等于动画开始时的实际速度除以动画属性改变值。
 * @param mass 质量。弹性系统的受力对象，会对弹性系统产生惯性影响。质量越大，震荡的幅度越大，恢复到平衡位置的速度越慢。取值范围：[0, +∞)。
 *     <br>value小于等于0时，按1处理。
 * @param stiffness 刚度。表示物体抵抗施加的力而形变的程度。刚度越大，抵抗变形的能力越强，恢复到平衡位置的速度越快。取值范围：[0, +∞)。
 *     <br>value小于等于0时，按1处理。
 * @param damping 阻尼。用于描述系统在受到扰动后震荡及衰减的情形。阻尼越大，弹性运动的震荡次数越少、震荡幅度越小。取值范围：[0, +∞)。
 *     <br>value小于等于0时，按1处理。
 * @return 曲线的插值对象指针。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateInterpolatingSpring(float velocity, float mass, float stiffness, float damping);

/**
 * @brief 构造自定义曲线对象。
 *
 * @param userData 用户自定义数据。
 * @param interpolate Indicates the custom interpolation callback. <b>fraction</b> indicates the input x value for
 *     interpolation when the animation starts; value range: [0,1].
 *     The return value is the y value of the curve; value range: [0,1].
 *     If <b>fraction</b> is <b>0</b>, the return value <b>0</b> corresponds to the animation start point; any other
 *     return
 *     value means that the animation jumps at the start point.
 *     If <b>fraction</b> is <b>1</b>, the return value <b>1</b> corresponds to the animation end point; any other
 *     return
 *     value means that the end value of the animation is not the value of the state variable,
 *     which will result in an effect of transition from that end value to the value of the state variable.
 * @return 曲线的插值对象指针。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCustomCurve(
    void* userData, float (*interpolate)(float fraction, void* userdata));

/**
 * @brief 销毁自定义曲线对象。
 *
 * @param curveHandle 曲线的插值对象指针。
 * @since 12
 */
void OH_ArkUI_Curve_DisposeCurve(ArkUI_CurveHandle curveHandle);

/**
 * @brief 创建组件转场时的透明度效果对象。
 *
 * @note If the value specified is less than 0, the value <b>0</b> is used. If the value specified is greater than 1,
 *     the value <b>1</b> is used.
 * @param opacity 透明度，取值范围为[0, 1]。默认值为1。设置小于0的非法值按0处理，大于1的非法值按1处理，1表示不透明，0表示完全透明。
 * @return 组件转场时的透明度效果对象。
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateOpacityTransitionEffect(float opacity);

/**
 * @brief 创建组件转场时的平移效果对象。
 *
 * @param translate 组件转场时的平移参数对象。
 * @return 组件转场时的平移效果对象。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateTranslationTransitionEffect(ArkUI_TranslationOptions* translate);

/**
 * @brief 创建组件转场时的缩放效果对象。
 *
 * @param scale 组件转场时的缩放参数对象。
 * @return 组件转场时的缩放效果对象。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateScaleTransitionEffect(ArkUI_ScaleOptions* scale);

/**
 * @brief 创建组件转场时的旋转效果对象。
 *
 * @param rotate 组件转场时的旋转参数对象。
 * @return 组件转场时的旋转效果对象。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateRotationTransitionEffect(ArkUI_RotationOptions* rotate);

/**
 * @brief 创建组件平移效果对象。
 *
 * @param edge 平移类型。
 * @return 组件转场时的平移效果对象。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateMovementTransitionEffect(ArkUI_TransitionEdge edge);

/**
 * @brief 创建非对称的转场效果对象。
 *
 * @note If the <b>asymmetric</b> function is not used for <b>TransitionEffect</b>, the transition effect takes effect
 *     for both appearance and disappearance of the component.
 * @param appear 出现的转场效果。
 * @param disappear 消失的转场效果。
 * @return 非对称的转场效果对象。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateAsymmetricTransitionEffect(
    ArkUI_TransitionEffect* appear, ArkUI_TransitionEffect* disappear);

/**
 * @brief 销毁转场效果对象。
 *
 * @param effect 转场效果对象。
 * @since 12
 */
void OH_ArkUI_TransitionEffect_Dispose(ArkUI_TransitionEffect* effect);

/**
 * @brief 设置转场效果链式组合，以形成包含多种转场效果的TransitionEffect。
 *
 * @param firstEffect 转场效果。
 * @param secondEffect 需要链式转场效果。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_TransitionEffect_Combine(
    ArkUI_TransitionEffect* firstEffect, ArkUI_TransitionEffect* secondEffect);

/**
 * @brief 设置转场效果动画参数。
 *
 * @note If <b>combine</b> is used for combining transition effects, the animation settings of a transition effect are
 *     applicable to the one following it.
 * @param effect 转场效果。
 * @param animation 属性显示动画效果相关参数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_TransitionEffect_SetAnimation(
    ArkUI_TransitionEffect* effect, ArkUI_AnimateOption* animation);
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_ANIMATE_H
/** @} */
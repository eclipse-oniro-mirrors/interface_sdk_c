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
 * @brief 提供ArkUI（方舟UI框架）在Native侧的动画接口定义集合。native_animate.h中的接口需要在主线程上调用。
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
 * @brief 设置动画的期望帧率。该结构体通过min、max和expected三个字段定义帧率范围，系统尽可能满足期望帧率。
 *
 * @since 12
 */
typedef struct {
    /**
     * 期望的最小帧率，单位为帧/秒（fps）。取值原则：min需小于等于max，且min需小于等于expected。取值需满足min &lt;= expected &lt;= max，不满足时该期望帧率范围设置不生效。
     */
    uint32_t min;
    /**
     * 期望的最大帧率，单位为帧/秒（fps）。取值原则：max需大于等于min，且max需大于等于expected。三者取值需满足min &lt;= expected &lt;= max。
     */
    uint32_t max;
    /**
     * 期望的最优帧率，单位为帧/秒（fps）。取值原则：expected需在[min, max]范围内取值。
     */
    uint32_t expected;
} ArkUI_ExpectedFrameRateRange;

/**
 * @brief 动画播放结束回调类型，用于在动画播放完成时通知开发者动画已结束。开发者可通过type字段指定回调触发方式，通过callback字段设置自定义回调函数，并通过userData字段传递自定义数据至回调函数中。
 *
 * @since 12
 */
typedef struct {
    /**
     * 在动画中定义结束回调的回调类型，用于指定回调的触发方式。取值原则：ARKUI_FINISH_CALLBACK_REMOVED(0)表示动画结束并立即删除时触发回调，
     * ARKUI_FINISH_CALLBACK_LOGICALLY(1)表示动画逻辑上完成（可能仍处于长尾状态）时触发回调。不同回调类型的触发时机不同，请根据业务场景选择合适的类型。未显式设置type时，
     * 按ARKUI_FINISH_CALLBACK_REMOVED处理。
     */
    ArkUI_FinishCallbackType type;
    /**
     * 动画播放结束回调，与type和userData配合使用。type参数决定回调触发的时机类型，回调函数接收userData作为入参。设置该回调后，当动画播放结束时将自动调用该函数，
     * 开发者可在回调中通过userData参数执行自定义逻辑，如更新UI状态或处理动画完成后的后续操作。
     */
    void (*callback)(void* userData);
    /**
     * 用于动画播放结束回调，传递用户自定义数据。需确保userData在动画播放结束回调触发时仍有效，避免悬空指针导致未定义行为。设置该成员为NULL时，回调函数将不会接收到userData参数。
     */
    void* userData;
} ArkUI_AnimateCompleteCallback;

/**
 * @brief 定义动画效果的配置参数，用于配置动画的相关属性。
 *
 * @since 12
 */
typedef struct ArkUI_AnimateOption ArkUI_AnimateOption;

/**
 * @brief 提供动画曲线的插值对象定义，用于动画属性值的插值计算。
 *
 * @since 12
 */
typedef struct ArkUI_Curve ArkUI_Curve;

/**
 * @brief 曲线插值对象的指针类型定义。曲线插值用于控制动画属性值随时间的变化规律，不同类型的插值曲线可实现不同的动画过渡效果。
 *
 * @since 12
 */
typedef struct ArkUI_Curve* ArkUI_CurveHandle;

/**
 * @brief 定义关键帧动画参数对象，作为关键帧动画接口的输入参数使用。相关接口需要在主线程上调用。
 *
 * @since 12
 */
typedef struct ArkUI_KeyframeAnimateOption ArkUI_KeyframeAnimateOption;

/**
 * @brief 定义animator动画参数对象，用于创建animator动画时配置动画属性参数。
 *
 * @since 12
 */
typedef struct ArkUI_AnimatorOption ArkUI_AnimatorOption;

/**
 * @brief 定义animator动画对象指针，用于对ArkUI（方舟UI框架）动画对象进行操作和控制。
 *
 * @since 12
 */
typedef struct ArkUI_Animator* ArkUI_AnimatorHandle;

/**
 * @brief 定义animator回调事件对象，用于在动画状态变化回调中接收事件。
 *
 * @since 12
 */
typedef struct ArkUI_AnimatorEvent ArkUI_AnimatorEvent;

/**
 * @brief 定义animator动画播放过程中逐帧回调的事件数据对象。
 *
 * @since 12
 */
typedef struct ArkUI_AnimatorOnFrameEvent ArkUI_AnimatorOnFrameEvent;

/**
 * @brief 定义transition属性的转场效果参数对象，用于配置组件出现或消失时的过渡动画效果。
 *
 * @since 12
 */
typedef struct ArkUI_TransitionEffect ArkUI_TransitionEffect;

/**
 * @brief ArkUI（方舟UI框架）提供的Native侧动画接口集合。
 *
 * @version 1
 * @since 12
 */
typedef struct {
    /**
     * @brief 执行显式动画过渡效果。
     *
     * @note 在闭包函数中要设置的组件属性，必须在调用animateTo之前已在组件上设置过。
     *
     * @param context UI上下文实例，用于指定动画所在的UI上下文环境，不可为NULL。
     * @param option 动画效果配置参数，不可为NULL。
     * @param update 指定动效的闭包函数。在闭包函数中产生的状态变化，系统会自动插入过渡动画。传参不可为NULL。
     *     <br>**说明**：在闭包函数中要设置的组件属性，必须在调用animateTo之前已在组件上设置过。
     * @param complete 动画播放完成回调函数。传参为NULL时不设置完成回调通知。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常，请检查传入参数的类型和有效性。可能原因：context无效、option为NULL或配置不合理。解决措施：
     *     确保context有效、option配置正确且非NULL。
     */
    int32_t (*animateTo)(ArkUI_ContextHandle context, ArkUI_AnimateOption* option, ArkUI_ContextCallback* update,
        ArkUI_AnimateCompleteCallback* complete);

    /**
     * @brief 关键帧动画接口，通过指定关键帧定义属性在不同时间节点的值，系统根据插值算法自动计算中间帧的属性值实现平滑过渡。关键帧参数配置详见{@link ArkUI_KeyframeAnimateOption}。
     * 与animateTo的显式过渡动画不同，keyframeAnimateTo适用于需要在多个时间节点定义不同动画状态的场景。选取原则：仅需起始到结束状态的过渡动画时使用animateTo，
     * 需多关键帧精细控制动画过程时使用keyframeAnimateTo。
     *
     * @param context UI上下文实例，用于指定关键帧动画所在的UI上下文环境，不可为NULL。
     * @param option 关键帧动画参数，设置关键帧动画的配置参数，包括关键帧的时间节点、动画属性值及过渡效果等，不可为NULL。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常，请检查传入参数的类型和有效性。可能原因：context无效、option为NULL或配置不合理。解决措施：
     *     确保context有效、option配置正确且非NULL。
     */
    int32_t (*keyframeAnimateTo)(ArkUI_ContextHandle context, ArkUI_KeyframeAnimateOption* option);

    /**
     * @brief 创建animator动画对象并返回其指针。与animateTo/keyframeAnimateTo的触发式动画不同，createAnimator创建可持久控制的动画对象，适用于需要反复启动、停止、
     * 监听状态等精细控制的动画场景。选取原则：一次性过渡动画使用animateTo或keyframeAnimateTo，需持久控制动画生命周期时使用createAnimator。
     *
     * @param context UI上下文实例，用于指定动画所在的UI上下文环境，不可为NULL。
     * @param option animator动画参数，不可为NULL。
     * @return animator动画对象指针，用于后续对动画对象进行控制。函数参数异常时返回NULL。
     */
    ArkUI_AnimatorHandle (*createAnimator)(ArkUI_ContextHandle context, ArkUI_AnimatorOption* option);

    /**
     * @brief 销毁animator动画对象并释放其内存，销毁后不可再使用该handle。传入NULL或已销毁的句柄时，函数不执行销毁操作。
     *
     * @param animatorHandle animator动画对象，必须为由createAnimator创建的有效handle，不可传入已销毁的对象。
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
 * @return 动画曲线。返回值包括：ARKUI_CURVE_LINEAR（0，线性曲线）、ARKUI_CURVE_EASE（1，缓动曲线）、ARKUI_CURVE_EASE_IN（2，加速曲线）、
 *     ARKUI_CURVE_EASE_OUT（3，减速曲线）、ARKUI_CURVE_EASE_IN_OUT（4，先加速后减速曲线）、ARKUI_CURVE_FAST_OUT_SLOW_IN（5，标准曲线）、
 *     ARKUI_CURVE_LINEAR_OUT_SLOW_IN（6，减速曲线）、ARKUI_CURVE_FAST_OUT_LINEAR_IN（7，加速曲线）、ARKUI_CURVE_EXTREME_DECELERATION（8，
 *     急减速曲线）、ARKUI_CURVE_SHARP（9，锐利曲线）、ARKUI_CURVE_RHYTHM（10，节奏曲线）、ARKUI_CURVE_SMOOTH（11，平滑曲线）、ARKUI_CURVE_FRICTION（12，
 *     阻尼曲线）。option异常时返回-1。
 * @since 12
 */
ArkUI_AnimationCurve OH_ArkUI_AnimateOption_GetCurve(ArkUI_AnimateOption* option);

/**
 * @brief 获取动画延迟播放时间，单位为ms（毫秒）。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，返回0。
 * @return 动画延迟播放时间，单位为ms（毫秒）。option异常时返回0。
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
 * @return 动画播放模式。返回值包括：ARKUI_ANIMATION_PLAY_MODE_NORMAL（0，正向播放）、ARKUI_ANIMATION_PLAY_MODE_REVERSE（1，反向播放）、
 *     ARKUI_ANIMATION_PLAY_MODE_ALTERNATE（2，交替播放）、ARKUI_ANIMATION_PLAY_MODE_ALTERNATE_REVERSE（3，反向交替播放）。option异常时返回-1。
 * @since 12
 */
ArkUI_AnimationPlayMode OH_ArkUI_AnimateOption_GetPlayMode(ArkUI_AnimateOption* option);

/**
 * @brief 获取动画的期望帧率，单位为帧/秒（fps）。
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
 * @param value 动画持续时间，单位为ms（毫秒），默认值1000ms。取值范围：[0, +∞)。
 *     <br>value小于0时，按0处理。
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetDuration(ArkUI_AnimateOption* option, int32_t value);

/**
 * @brief 设置动画播放速度。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，操作无效。
 * @param value 动画播放速度，默认值1.0。取值范围：[0, +∞)。
 *     <br>**说明：**
 *     <br>传入小于0的数值，会默认设置为1。
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetTempo(ArkUI_AnimateOption* option, float value);

/**
 * @brief 设置动画自定义曲线。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，操作无效。
 * @param value 动画曲线。默认值：{@link ARKUI_CURVE_EASE_IN_OUT}，建议使用ARKUI_CURVE_EASE_IN_OUT获得更平滑的动画效果。
 *     <br>value值异常时，设置无效。
 *     <br>**说明：**若同时设置了{@link OH_ArkUI_AnimateOption_SetICurve}，则SetICurve优先生效，本设置不生效。
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
 * @param value 动画播放模式。默认值：{@link ARKUI_ANIMATION_PLAY_MODE_NORMAL}。ARKUI_ANIMATION_PLAY_MODE_NORMAL表示正向播放，
 *     ARKUI_ANIMATION_PLAY_MODE_REVERSE表示反向播放，ARKUI_ANIMATION_PLAY_MODE_ALTERNATE表示交替正反向播放，
 *     ARKUI_ANIMATION_PLAY_MODE_ALTERNATE_REVERSE表示交替反向和正向播放，奇数次反向，偶数次正向。
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
 * @brief 设置动画的插值曲线。
 *
 * @note 此方法优先于{@link OH_ArkUI_AnimateOption_SetCurve}生效。
 * @param option 动画效果参数。
 *     <br>option为NULL时，操作无效。
 * @param value 动画曲线参数。
 *     <br>value为NULL时，操作无效。
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetICurve(ArkUI_AnimateOption* option, ArkUI_CurveHandle value);

/**
 * @brief 获取动画的插值曲线。
 *
 * @param option 动画效果参数。
 *     <br>option为NULL时，返回NULL。
 * @return 动画的插值曲线。参数option异常时返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_AnimateOption_GetICurve(ArkUI_AnimateOption* option);

/**
 * @brief 创建关键帧动画参数。
 *
 * @param size 关键帧动画状态数。取值范围：[0, +∞)，需要为正整数才能产生动画效果。
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
 * @brief 设置关键帧动画的整体延迟时间，单位为ms（毫秒），默认不延迟播放。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画延迟播放时间，单位为ms（毫秒）。取值范围：(-∞, +∞)。默认值：0，表示不延迟。value大于0为延迟播放，value小于0表示提前播放。对于value小于0的情况：
 *     当value的绝对值小于实际动画时长，动画将在开始后第一帧直接运动到value绝对值的时刻的状态；当value的绝对值大于等于实际动画时长，动画将在开始后第一帧直接运动到终点状态。
 *     其中实际动画时长等于单次动画时长乘以动画播放次数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。可能原因：option为NULL。解决措施：请确保option为有效的动画参数对象指针。
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetDelay(ArkUI_KeyframeAnimateOption* option, int32_t value);

/**
 * @brief 设置关键帧动画播放次数。默认播放一次，设置为-1时表示无限次播放，设置为0时表示无动画效果。
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
 * @param 回调函数。
 *     <br>userData：回调函数的入参，用户自定义对象指针。
 *     <br>onFinish为NULL时，操作无效。
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
 * @param index 状态索引值。取值范围：[0, size-1]，其中size为关键帧动画状态数。
 *     <br>index超出范围时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetDuration(ArkUI_KeyframeAnimateOption* option, int32_t value, int32_t index);

/**
 * @brief 设置关键帧动画某段关键帧使用的动画曲线。
 *
 * @note 由于{@link springMotion}、{@link responsiveSpringMotion}、{@link interpolatingSpring}曲线时长不生效，故不支持这三种曲线。关键帧动画支持
 *     {@link springCurve}和{@link customCurve}曲线。
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
 * @param event 闭包函数。
 *     <br>userData：回调函数的入参，用户自定义对象指针。
 *     <br>event为NULL时，操作无效。
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
 * @brief 获取关键帧整体延迟时间，单位为ms（毫秒）。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回0。
 * @return 整体延迟时间，单位为ms（毫秒）。option异常时返回0。
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
 * @param index 状态索引值。取值范围：[0, size-1]，其中size为关键帧动画状态数。
 *     <br>index不在取值范围内时，返回0。
 * @return 持续时间，单位为ms（毫秒）。option异常时返回0。
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_GetDuration(ArkUI_KeyframeAnimateOption* option, int32_t index);

/**
 * @brief 获取关键帧动画某段状态动画曲线。
 *
 * @param option 关键帧动画参数。
 *     <br>option为NULL时，返回NULL。
 * @param index 状态索引值。取值范围：[0, size-1]，其中size为关键帧动画状态数。
 *     <br>index不在取值范围内时，返回NULL。
 * @return 动画曲线。参数异常时返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_KeyframeAnimateOption_GetCurve(ArkUI_KeyframeAnimateOption* option, int32_t index);

/**
 * @brief 创建animator动画对象参数。
 *
 * @note keyframeSize大于0时，动画插值起点默认是0，动画插值终点默认值是1。不支持设置。
 * @param keyframeSize 需要创建的关键帧个数。
 *     <br>keyframeSize小于0时返回NULL。
 * @return animator动画对象参数指针。keyframeSize小于0时返回NULL，option异常时返回NULL。
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
 * @brief 设置animator动画播放的时长，单位为ms（毫秒）。
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
 * @brief 设置animator动画延迟播放的时间，单位为ms（毫秒）。
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
 * @note 设置为除-1外其他负数视为无效取值，无效取值动画默认播放1次。
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
 * @brief 设置组件在动画开始前和结束后保持的状态。
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画执行时组件在动画开始前和结束后的状态。默认值：{@link ARKUI_ANIMATION_FILL_MODE_FORWARDS}。
 *     <br>ARKUI_ANIMATION_FILL_MODE_NONE（0）表示动画前后均恢复初始状态，ARKUI_ANIMATION_FILL_MODE_FORWARDS（1）表示动画结束后保持终点状态，
 *     ARKUI_ANIMATION_FILL_MODE_BACKWARDS（2）表示动画开始前保持起点状态，ARKUI_ANIMATION_FILL_MODE_BOTH（3）表示动画前后均保持对应状态。
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
 * @param value 动画播放方向。默认值：{@link ARKUI_ANIMATION_DIRECTION_NORMAL}。
 *     <br>ARKUI_ANIMATION_DIRECTION_NORMAL（0）表示正向播放，ARKUI_ANIMATION_DIRECTION_REVERSE（1）表示反向播放，
 *     ARKUI_ANIMATION_DIRECTION_ALTERNATE（2）表示交替正向和反向播放，奇数次正向，偶数次反向，ARKUI_ANIMATION_DIRECTION_ALTERNATE_REVERSE（3）
 *     表示交替反向和正向播放，奇数次反向，偶数次正向。
 *     <br>value超出取值范围时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetDirection(ArkUI_AnimatorOption* option, ArkUI_AnimationDirection value);

/**
 * @brief 设置animator动画插值曲线。
 *
 * @note 不支持{@link springCurve}、{@link springMotion}、{@link responsiveSpringMotion}、{@link interpolatingSpring}、
 *     {@link customCurve}动画曲线。
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
 * @note 当animator动画为关键帧动画时，此方法返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画插值起点，默认值0.0。取值范围：(-∞, +∞)。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetBegin(ArkUI_AnimatorOption* option, float value);

/**
 * @brief 设置animator动画插值终点。
 *
 * @note 当animator动画为关键帧动画时，此方法返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画插值终点。取值范围：(-∞, +∞)。默认值：1。
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
 * @param time 关键帧时间。取值范围：[0, 1], 各关键帧时间必须依次递增，即后一关键帧的time值大于前一关键帧的time值。默认值：按索引均匀分布（如第1帧为0.0，第2帧为0.5，第3帧为1.0）。
 *     <br>time小于0或time大于1时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 关键帧对应的插值目标值，表示动画在该关键帧时刻要达到的属性值。取值范围：(-∞, +∞)。
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
 * @note 不支持{@link springCurve}、{@link springMotion}、{@link responsiveSpringMotion}、{@link interpolatingSpring}、
 *     {@link customCurve}动画曲线。
 *
 * @param option animator动画对象参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param value 动画插值曲线。默认值：NULL，表示线性插值。
 * @param index 关键帧的索引值。取值范围：[0, keyframeSize-1]，其中keyframeSize为关键帧个数。
 *     <br>index超出取值范围时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetKeyframeCurve(ArkUI_AnimatorOption* option, ArkUI_CurveHandle value, int32_t index);
/**
 * @brief 获取animator动画播放的时长，单位为ms（毫秒）。
 *
 * @param option animator动画参数。
 *     <br>option为NULL时，返回-1。
 * @return 动画播放的时长，单位为ms（毫秒）。option异常时返回0。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_GetDuration(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画延迟播放时长，单位为ms（毫秒）。
 *
 * @param option animator动画参数。option为NULL时，返回0。
 * @return 动画延迟播放时长，单位为ms（毫秒）。option异常时返回0。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_GetDelay(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画播放次数。
 *
 * @param option animator动画对象参数。option为NULL时，返回0。
 * @return 动画播放次数。option异常时返回0。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_GetIterations(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画执行时组件在动画开始前和结束后的状态。
 *
 * @param option animator动画参数。option为NULL时，返回-1。
 * @return 动画执行时组件在动画开始前和结束后的状态。返回值包括：ARKUI_ANIMATION_FILL_MODE_NONE（0，播放完成后恢复初始状态）、ARKUI_ANIMATION_FILL_MODE_FORWARDS（
 *     1，播放完成后保持终点状态）、ARKUI_ANIMATION_FILL_MODE_BACKWARDS（2，延时播放时保持起点状态）、ARKUI_ANIMATION_FILL_MODE_BOTH（3，
 *     同时应用FORWARDS和BACKWARDS效果）。option异常时返回-1。
 * @since 12
 */
ArkUI_AnimationFillMode OH_ArkUI_AnimatorOption_GetFill(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画播放方向。
 *
 * @param option animator动画参数。
 * @return 动画播放方向。返回值包括：ARKUI_ANIMATION_DIRECTION_NORMAL（0，正向播放）、ARKUI_ANIMATION_DIRECTION_REVERSE（1，反向播放）、
 *     ARKUI_ANIMATION_DIRECTION_ALTERNATE（2，交替正向和反向播放，奇数次正向，偶数次反向）、ARKUI_ANIMATION_DIRECTION_ALTERNATE_REVERSE（3，
 *     交替反向和正向播放，奇数次反向，偶数次正向）。option异常时返回-1。
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
 * @param option animator动画对象参数。option为NULL时，返回NULL。
 * @return 期望的帧率范围对象指针。函数参数异常时返回NULL。
 * @since 12
 */
ArkUI_ExpectedFrameRateRange* OH_ArkUI_AnimatorOption_GetExpectedFrameRateRange(ArkUI_AnimatorOption* option);

/**
 * @brief 获取animator动画关键帧时间，取值范围[0, 1]，为归一化时间比例。
 *
 * @param option animator动画对象参数。
 * @param index 关键帧的索引值。取值范围：[0, keyframeSize-1]，其中keyframeSize为关键帧个数。
 *     <br>index超出范围时，返回NULL。
 * @return 关键帧时间，取值范围[0, 1]，为归一化时间比例。
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetKeyframeTime(ArkUI_AnimatorOption* option, int32_t index);

/**
 * @brief 获取animator动画关键帧数值。
 *
 * @param option animator动画对象参数。option为NULL时，返回0.0。
 * @param index 关键帧的索引值。取值范围：[0, keyframeSize-1]，其中keyframeSize为关键帧个数。
 *     <br>index超出范围时，返回0.0。
 * @return 关键帧数值。
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetKeyframeValue(ArkUI_AnimatorOption* option, int32_t index);

/**
 * @brief 获取animator动画关键帧动画插值曲线。
 *
 * @param option animator动画对象参数。option为NULL时，返回空指针。
 * @param index 关键帧的索引值。取值范围：[0, keyframeSize-1]，其中keyframeSize为关键帧个数。
 *     <br>index超出范围时，返回空指针。
 * @return 动画插值曲线。函数参数异常时返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_AnimatorOption_GetKeyframeCurve(ArkUI_AnimatorOption* option, int32_t index);

/**
 * @brief 获取动画事件对象中的用户自定义对象。
 *
 * @param event 动画事件对象。event为NULL时，返回NULL。
 * @return 用户自定义对象。
 * @since 12
 */
void* OH_ArkUI_AnimatorEvent_GetUserData(ArkUI_AnimatorEvent* event);

/**
 * @brief 获取动画的帧事件中的用户自定义对象。
 *
 * @param event 动画事件对象。event为NULL时，返回NULL。
 * @return 用户自定义对象。
 * @since 12
 */
void* OH_ArkUI_AnimatorOnFrameEvent_GetUserData(ArkUI_AnimatorOnFrameEvent* event);

/**
 * @brief 获取动画帧回调事件对象中的插值结果。
 *
 * @param event 动画事件对象。event为NULL时，返回0.0。
 * @return 动画插值结果。
 *     <br>**说明：**
 *     <br>在动画过程中，插值结果根据动画参数在插值起点{@link OH_ArkUI_AnimatorOption_SetBegin}和插值终点{@link OH_ArkUI_AnimatorOption_SetEnd}间变化。
 * @since 12
 */
float OH_ArkUI_AnimatorOnFrameEvent_GetValue(ArkUI_AnimatorOnFrameEvent* event);

/**
 * @brief 设置animator动画接收到帧时回调。
 *
 * @param option animator动画对象参数。option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param userData 用户自定义参数。
 * @param 回调函数。
 *     <br>- event：回调函数的入参，动画事件对象。
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
 * @param option animator动画对象参数。option为NULL时，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param userData 用户自定义参数。
 * @param 回调函数。
 *     <br>- event：回调函数的入参，动画事件对象。
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
 * @param option animator动画对象参数。option为NULL时，返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param userData 用户自定义参数。
 * @param 回调函数。
 *     <br>- event：回调函数的入参，动画事件对象。
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
 * @param option animator动画对象参数。option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param userData 用户自定义参数。
 * @param 回调函数。
 *     <br>- event：回调函数的入参，动画事件对象。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_RegisterOnRepeatCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event));

/**
 * @brief 重置animator动画的配置参数。
 *
 * @param animatorHandle animator动画对象。
 *     <br>animatorHandle为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param option animator动画参数。
 *     <br>option为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_Animator_ResetAnimatorOption(
    ArkUI_AnimatorHandle animatorHandle, ArkUI_AnimatorOption* option);

/**
 * @brief 启动animator动画。需要在主线程上调用。
 *
 * @param animatorHandle animator动画对象。animatorHandle为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_Animator_Play(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief 结束animator动画，动画将跳到终点状态后停止。与{@link OH_ArkUI_Animator_Cancel}的区别：Cancel会立即中断动画并回到初始状态，Finish会让动画直接跳到终点状态后停止。
 * 需要在主线程上调用。
 *
 * @param animatorHandle animator动画对象。animatorHandle为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_Animator_Finish(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief 暂停animator动画。
 *
 * @param animatorHandle animator动画对象。animatorHandle为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_Animator_Pause(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief 取消animator动画。
 *
 * @param animatorHandle animator动画对象。animatorHandle为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_Animator_Cancel(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief 以相反的顺序播放animator动画。
 *
 * @param animatorHandle animator动画对象。animatorHandle为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_Animator_Reverse(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief 插值曲线的初始化函数，可以根据入参创建一个插值曲线对象。
 *
 * @param curve 曲线类型。curve值异常时，返回NULL。
 * @return 插值曲线对象指针，用于动画属性值的插值计算。curve值异常时返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCurveByType(ArkUI_AnimationCurve curve);

/**
 * @brief 构造阶梯曲线对象。
 *
 * @param count 阶梯的数量，需要为正整数，取值范围：[1, +∞)。
 *     <br>count值异常时，操作无效。
 * @param end 在每个间隔的起点或是终点发生阶跃变化。true：在终点发生阶跃变化。false：在起点发生阶跃变化。
 * @return 阶梯曲线对象指针。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateStepsCurve(int32_t count, bool end);

/**
 * @brief 构造三阶贝塞尔曲线对象。
 *
 * @param x1 确定贝塞尔曲线第一点横坐标，取值范围：[0, 1]。设置的值小于0时，按0处理；设置的值大于1时，按1处理。
 * @param y1 确定贝塞尔曲线第一点纵坐标。取值范围：(-∞, +∞)。
 * @param x2 确定贝塞尔曲线第二点横坐标，取值范围：[0, 1]。设置的值小于0时，按0处理；设置的值大于1时，按1处理。
 * @param y2 确定贝塞尔曲线第二点纵坐标。
 * @return 三阶贝塞尔曲线对象指针。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCubicBezierCurve(float x1, float y1, float x2, float y2);

/**
 * @brief 构造弹簧曲线对象，曲线形状由弹簧参数决定，动画时长受动画参数中的时长参数控制。
 *
 * @param velocity 初始速度。是由外部因素对弹性动效产生的影响参数，其目的是保证对象从之前的运动状态平滑地过渡到弹性动效。该速度是归一化速度，其值等于动画开始时的实际速度除以动画属性改变值。
 * @param mass 质量。弹性系统的受力对象，会对弹性系统产生惯性影响。质量越大，震荡的幅度越大，恢复到平衡位置的速度越慢。取值范围：[0, +∞)。
 *     <br>value小于等于0时，按1处理。
 * @param stiffness 刚度。是物体抵抗施加的力而形变的程度。在弹性系统中，刚度越大，抵抗变形的能力越强，恢复到平衡位置的速度就越快。取值范围：[0, +∞)。
 *     <br>value小于等于0时，按1处理。
 * @param damping 阻尼。用于描述系统在受到扰动后震荡及衰减的情形。阻尼越大，弹性运动的震荡次数越少、震荡幅度越小。取值范围：[0, +∞)。
 *     <br>value小于等于0时，按1处理。
 * @return 插值器弹簧曲线的插值对象指针，用于基于弹簧物理模型进行插值计算，生成从0到1的动画曲线。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateSpringCurve(float velocity, float mass, float stiffness, float damping);

/**
 * @brief 构造弹性动画曲线对象。如果对同一对象的同一属性进行多个弹性动画，每个动画会替换掉前一个动画，并继承之前的速度。
 *
 * @note 动画时间由曲线参数决定，不受{@link animation}、{@link animateTo}中的duration参数控制。
 *
 * @param response 弹簧自然振动周期，决定弹簧复位的速度，单位为s（秒）。取值范围：(0, +∞)。
 *     <br>参数小于等于0时，按0.55处理。
 * @param dampingFraction 阻尼系数。大于0小于1的值为欠阻尼，运动过程中会超出目标值；等于1为临界阻尼；大于1为过阻尼，运动过程中逐渐趋于目标值。取值范围：(0, +∞)。
 *     <br>参数小于等于0时，按0.825处理。
 * @param overlapDuration 弹性动画衔接时长，单位为s（秒）。发生动画继承时，如果前后两个弹性动画response不一致，response参数会在overlapDuration时间内平滑过渡。取值范围：[0, +∞)
 *     。
 *     <br>参数小于0时，按0处理。
 * @return 弹性动画曲线的插值对象指针，使用响应式参数构造曲线，支持动画间的速度继承。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateSpringMotion(float response, float dampingFraction, float overlapDuration);

/**
 * @brief 构造弹性跟手动画曲线对象，是springMotion的一种特例，仅默认参数不同，可与springMotion混合使用。
 *
 * @note 动画时间由曲线参数决定，不受{@link animation}、{@link animateTo}中的duration参数控制。
 *
 * @param response 弹簧自然振动周期，决定弹簧复位的速度，单位为s（秒）。取值范围：(0, +∞)。
 *     <br>参数小于等于0时，按0.15处理。
 * @param dampingFraction 阻尼系数。大于0小于1的值为欠阻尼，运动过程中会超出目标值；等于1为临界阻尼；大于1为过阻尼，运动过程中逐渐趋于目标值。取值范围：[0, +∞)。
 *     <br>参数小于0时，按0.86处理。
 * @param overlapDuration 弹性动画衔接时长，单位为s（秒）。发生动画继承时，如果前后两个弹性动画response不一致，response参数会在overlapDuration时间内平滑过渡。取值范围：[0, +∞)
 *     。
 *     <br>参数小于0时，按0.25处理。
 * @return 响应式弹簧动画曲线的插值对象指针，是springMotion的一种特例，仅默认参数不同。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateResponsiveSpringMotion(
    float response, float dampingFraction, float overlapDuration);

/**
 * @brief 构造插值器弹簧曲线对象，生成一条从0到1的动画曲线，实际动画值根据曲线进行插值计算。
 *
 * @note 动画时间由曲线参数决定，不受{@link animation}、{@link animateTo}中的duration参数控制。
 *
 *
 * @param velocity 初始速度。外部因素对弹性动效产生的影响参数，目的是保证对象从之前的运动状态平滑地过渡到弹性动效。该速度是归一化速度，其值等于动画开始时的实际速度除以动画属性改变值。取值范围：(-∞, +∞)。
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
 * @param interpolate 用户自定义的插值回调函数。fraction为动画开始时的插值输入x值。取值范围：[0,1]。返回值为曲线的y值。取值范围：[0,1]。fraction等于0时，
 *     返回值为0对应动画起点，返回不为0，动画在起点处有跳变效果。fraction等于1时，返回值为1对应动画终点，返回值不为1将导致动画的终值不是状态变量的值，出现
 *     大于或者小于状态变量值，再跳变到状态变量值的效果。
 * @return 曲线的插值对象指针。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCustomCurve(
    void* userData, float (*interpolate)(float fraction, void* userdata));

/**
 * @brief 销毁自定义曲线对象。
 *
 * @param curveHandle 曲线的插值对象指针。
 *     <br>curveHandle为NULL时，操作无效。
 * @since 12
 */
void OH_ArkUI_Curve_DisposeCurve(ArkUI_CurveHandle curveHandle);

/**
 * @brief 创建组件转场时的透明度效果对象。
 *
 * @note 设置小于0的非法值按0处理，大于1的非法值按1处理。
 * @param opacity 透明度，取值范围为[0, 1]。默认值为1。设置小于0的非法值按0处理，大于1的非法值按1处理，1表示不透明，0表示完全透明。
 * @return 组件转场时的透明度效果对象。
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateOpacityTransitionEffect(float opacity);

/**
 * @brief 创建组件转场时的平移效果对象。
 *
 * @param translate 组件转场时的平移参数对象。
 *     <br>translate为NULL时，返回NULL。
 * @return 组件转场时的平移效果对象。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateTranslationTransitionEffect(ArkUI_TranslationOptions* translate);

/**
 * @brief 创建组件转场时的缩放效果对象。
 *
 * @param scale 组件转场时的缩放参数对象。scale为NULL时，返回NULL。
 * @return 组件转场时的缩放效果对象。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateScaleTransitionEffect(ArkUI_ScaleOptions* scale);

/**
 * @brief 创建组件转场时的旋转效果对象。
 *
 * @param rotate 组件转场时的旋转参数对象。rotate为NULL时，返回NULL。
 * @return 组件转场时的旋转效果对象。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateRotationTransitionEffect(ArkUI_RotationOptions* rotate);

/**
 * @brief 创建组件平移效果对象，通过指定边缘方向（上、下、左、右）控制组件的滑入滑出方向，适用于仅需指定滑动方向的简单场景。与OH_ArkUI_CreateTranslationTransitionEffect不同：
 * 后者支持自定义x/y/z方向的精确平移参数，适用于需要指定具体位移距离的场景。
 *
 * @param edge 组件平移的方向类型，决定组件出现和消失时的平移方向。edge值异常时，按{@link ARKUI_TRANSITION_EDGE_START}处理。
 *     <br>ARKUI_TRANSITION_EDGE_TOP（0）表示从上方滑入/滑出，ARKUI_TRANSITION_EDGE_BOTTOM（1）表示从下方滑入/滑出，ARKUI_TRANSITION_EDGE_START（
 *     2）表示从左侧滑入/滑出，ARKUI_TRANSITION_EDGE_END（3）表示从右侧滑入/滑出。
 * @return 组件转场时的平移效果对象。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateMovementTransitionEffect(ArkUI_TransitionEdge edge);

/**
 * @brief 创建非对称的转场效果对象。
 *
 * @note 如果不通过该函数构造{@link ArkUI_TransitionEffect}，则表明该效果在组件出现和消失时均生效。
 * @param appear 组件出现时的转场效果。appear为NULL时，返回NULL。
 * @param disappear 组件消失时的转场效果。disappear为NULL时，返回NULL。
 * @return 非对称的转场效果对象。如果参数异常返回NULL。
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateAsymmetricTransitionEffect(
    ArkUI_TransitionEffect* appear, ArkUI_TransitionEffect* disappear);

/**
 * @brief 创建无转场效果对象。
 *
 * @return 创建的无转场效果对象指针。调用者需要调用{@link OH_ArkUI_TransitionEffect_Dispose}释放该对象。
 * @release native_animate/OH_ArkUI_TransitionEffect_Dispose {return}
 * @since 26.0.0
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateIdentityTransitionEffect(void);

/**
 * @brief 销毁转场效果对象。
 *
 * @param effect 转场效果对象。
 *     <br>effect为NULL时，操作无效。
 * @since 12
 */
void OH_ArkUI_TransitionEffect_Dispose(ArkUI_TransitionEffect* effect);

/**
 * @brief 设置转场效果链式组合，以形成包含多种转场效果的TransitionEffect。
 *
 * @param firstEffect 链式组合的前一个转场效果，将与secondEffect组合形成包含多种转场效果的TransitionEffect。
 *     <br>firstEffect为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param secondEffect 需要组合的后一个转场效果，将与firstEffect链式组合形成包含多种转场效果的TransitionEffect。
 *     <br>secondEffect为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
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
 * @note 如果通过{@link OH_ArkUI_TransitionEffect_Combine}进行转场效果的组合，前一转场效果的动画参数也可用于后一转场效果。
 * @param effect 要设置动画参数的转场效果对象。
 *     <br>effect为NULL时，返回错误码{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param animation 属性显示动画效果相关参数。
 *     <br>animation为NULL时，设置动画参数为空。
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

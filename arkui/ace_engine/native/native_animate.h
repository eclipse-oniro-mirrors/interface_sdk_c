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
 * @brief Defines a set of animation APIs of ArkUI on the native side. The APIs in **native_animate.h** must be called
 * in the main thread.
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
 * @brief Defines the expected frame rate range of the animation.
 *
 * @since 12
 */
typedef struct {
    /**
     * Expected minimum frame rate, in fps.
     */
    uint32_t min;
    /**
     * Expected maximum frame rate, in fps.
     */
    uint32_t max;
    /**
     * Expected optimal frame rate, in fps.
     */
    uint32_t expected;
} ArkUI_ExpectedFrameRateRange;

/**
 * @brief Defines the callback type for when the animation playback is complete.
 *
 * @since 12
 */
typedef struct {
    /**
     * Callback type for when the animation playback is complete.
     */
    ArkUI_FinishCallbackType type;
    /**
     * Invoked when the animation playback is complete.
     */
    void (*callback)(void* userData);
    /**
     * Custom data passed upon animation end callback.
     */
    void* userData;
} ArkUI_AnimateCompleteCallback;

/**
 * @brief Defines the animation configuration.
 *
 * @since 12
 */
typedef struct ArkUI_AnimateOption ArkUI_AnimateOption;

/**
 * @brief Defines an interpolation curve.
 *
 * @since 12
 */
typedef struct ArkUI_Curve ArkUI_Curve;

/**
 * @brief Defines the pointer to an interpolation curve.
 *
 * @since 12
 */
typedef struct ArkUI_Curve* ArkUI_CurveHandle;

/**
 * @brief Defines the keyframe animation parameter object.
 *
 * @since 12
 */
typedef struct ArkUI_KeyframeAnimateOption ArkUI_KeyframeAnimateOption;

/**
 * @brief Defines the animator parameter object.
 *
 * @since 12
 */
typedef struct ArkUI_AnimatorOption ArkUI_AnimatorOption;

/**
 * @brief Defines the pointer to an animator object.
 *
 * @since 12
 */
typedef struct ArkUI_Animator* ArkUI_AnimatorHandle;

/**
 * @brief Defines the animator callback event object.
 *
 * @since 12
 */
typedef struct ArkUI_AnimatorEvent ArkUI_AnimatorEvent;

/**
 * @brief Defines the callback object when the animator receives a frame.
 *
 * @since 12
 */
typedef struct ArkUI_AnimatorOnFrameEvent ArkUI_AnimatorOnFrameEvent;

/**
 * @brief Defines the transition parameter object for transition property configuration.
 *
 * @since 12
 */
typedef struct ArkUI_TransitionEffect ArkUI_TransitionEffect;

/**
 * @brief Declares the native animation APIs provided by ArkUI.
 *
 * @version 1
 * @since 12
 */
typedef struct {
    /**
     * @brief Defines an explicit animation.
     *
     * @note Make sure the component attributes to be set in the event closure have been set before.
     *
     * @param context **UIContext** instance.
     * @param option Defines the animation configuration.
     * @param update Closure function for the animation. The system automatically inserts the transition animation if
     *     the state changes in the closure function.
     *     <br>Note: Make sure the component attributes to be set in the closure function have been set before.
     * @param complete Callback invoked when the animation playback is complete.
     * @return <ul> 
     *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
     *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
     *         </ul>
     */
    int32_t (*animateTo)(ArkUI_ContextHandle context, ArkUI_AnimateOption* option, ArkUI_ContextCallback* update,
        ArkUI_AnimateCompleteCallback* complete);

    /**
     * @brief Defines a keyframe animation.
     *
     * @param context **UIContext** instance.
     * @param option Keyframe animation parameter.
     * @return <ul> 
     *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
     *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
     *         </ul>
     */
    int32_t (*keyframeAnimateTo)(ArkUI_ContextHandle context, ArkUI_KeyframeAnimateOption* option);

    /**
     * @brief Creates an animator object.
     *
     * @param context **UIContext** instance.
     * @param option Animator parameter.
     * @return Returns the pointer to the animator object; returns **NULL** if a parameter error occurs.
     */
    ArkUI_AnimatorHandle (*createAnimator)(ArkUI_ContextHandle context, ArkUI_AnimatorOption* option);

    /**
     * @brief Disposes of an animator object.
     *
     * @param animatorHandle Animator object.
     */
    void (*disposeAnimator)(ArkUI_AnimatorHandle animatorHandle);
} ArkUI_NativeAnimateAPI_1;

/**
 * @brief Creates an animation configuration.
 *
 * @return Pointer to the created animation configuration.
 * @since 12
 */
ArkUI_AnimateOption* OH_ArkUI_AnimateOption_Create();

/**
 * @brief Disposes of an animation configuration.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_AnimateOption_Dispose(ArkUI_AnimateOption* option);

/**
 * @brief Obtains the animation duration, in milliseconds.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @return Animation duration, in milliseconds. If **option** is invalid, **0** is returned.
 * @since 12
 */
uint32_t OH_ArkUI_AnimateOption_GetDuration(ArkUI_AnimateOption* option);

/**
 * @brief Obtains the playback speed of an animation.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **0.0** is returned.
 * @return Animation playback speed. Value range: [0, +∞). If **option** is invalid, **0.0** is returned.
 * @since 12
 */
float OH_ArkUI_AnimateOption_GetTempo(ArkUI_AnimateOption* option);

/**
 * @brief Obtains an animation curve.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **-1** is returned.
 * @return Animation curve. If **option** is invalid,**-1** is returned.
 * @since 12
 */
ArkUI_AnimationCurve OH_ArkUI_AnimateOption_GetCurve(ArkUI_AnimateOption* option);

/**
 * @brief Obtains the animation delay, in milliseconds.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @return Delay of animation playback. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_AnimateOption_GetDelay(ArkUI_AnimateOption* option);

/**
 * @brief Obtains the number of times that an animation is played.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @return Number of times that the animation is played. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_AnimateOption_GetIterations(ArkUI_AnimateOption* option);

/**
 * @brief Obtains the playback mode of an animation.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **-1** is returned.
 * @return Animation playback mode. If **option** is invalid,**-1** is returned.
 * @since 12
 */
ArkUI_AnimationPlayMode OH_ArkUI_AnimateOption_GetPlayMode(ArkUI_AnimateOption* option);

/**
 * @brief Obtains the expected frame rate range of an animation.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **NULL** is returned.
 * @return Expected frame rate range of the animation, in fps. If **option** is invalid, **NULL** is returned.
 * @since 12
 */
ArkUI_ExpectedFrameRateRange* OH_ArkUI_AnimateOption_GetExpectedFrameRateRange(ArkUI_AnimateOption* option);

/**
 * @brief Sets the animation duration, in milliseconds.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Animation duration, in milliseconds. Value range: [0, +∞).
 *     <br>If the value is less than 0, **0** is used.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetDuration(ArkUI_AnimateOption* option, int32_t value);

/**
 * @brief Sets the playback speed of an animation.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Animation playback speed. Value range: [0, +∞).
 *     <br>**NOTE**
 *     <br>If the value is less than 0, the default value **1** is used.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetTempo(ArkUI_AnimateOption* option, float value);

/**
 * @brief Animation curve.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Animation curve. Default value: {@link ARKUI_CURVE_LINEAR}. You are advised to use
 *     {@link ARKUI_CURVE_EASE_IN_OUT} to obtain a smoother animation effect.
 *     <br>If the value is abnormal, the setting is invalid.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetCurve(ArkUI_AnimateOption* option, ArkUI_AnimationCurve value);

/**
 * @brief Sets the animation delay, in milliseconds.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Animation delay, in milliseconds. Value range: (-∞, +∞). Default value: **0**, indicating no animation
 *     delay. A value greater than 0 means to begin the animation after the specified amount of time has elapsed. A
 *     value less than 0 means to begin the animation in advance. If **value** is less than **0** and the absolute value
 *     of **value** is less than the actual animation duration, the animation starts its first frame from the state at
 *     the absolute value. If the absolute value of **value** is greater than or equal to the actual animation duration,
 *     the animation starts its first frame from the end state. The actual animation duration is equal to the duration
 *     of a single animation multiplied by the number of animation playback times.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetDelay(ArkUI_AnimateOption* option, int32_t value);

/**
 * @brief Sets the number of times that an animation is played.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Number of times that the animation is played. Value range: [-1, +∞). If this parameter is set to **0**,
 *     the animation is not played. If this parameter is set to **-1**, the animation is played for an infinite number
 *     of times. Default value: **1** (played once).
 *     <br>If the value is less than -1, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetIterations(ArkUI_AnimateOption* option, int32_t value);

/**
 * @brief Sets the playback mode for an animation.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Animation playback mode. Default value: {@link ARKUI_ANIMATION_PLAY_MODE_NORMAL}.
 *     <br>If the value is abnormal, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetPlayMode(ArkUI_AnimateOption* option, ArkUI_AnimationPlayMode value);

/**
 * @brief Defines a struct for the expected frame rate range of the animation.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Expected frame rate range of the animation, in fps.
 *     <br>If **value** is set to **NULL**, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(ArkUI_AnimateOption* option, ArkUI_ExpectedFrameRateRange* value);

/**
 * @brief Sets the animation curve for an animation.
 *
 * @note This method is better than the value set by OH_ArkUI_AnimateOption_SetCurve.
 * @param option Animator animation parameters.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Animation curve parameters.
 *     <br>If **value** is set to **NULL**, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetICurve(ArkUI_AnimateOption* option, ArkUI_CurveHandle value);

/**
 * @brief Obtains the animation curve of an animation.
 *
 * @param option Animator animation parameters.
 *     <br>If **option** is set to **NULL**, **NULL** is returned.
 * @return Animation curve parameters. Returns **NULL** if the option parameter is invalid.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_AnimateOption_GetICurve(ArkUI_AnimateOption* option);

/**
 * @brief Creates a keyframe animation parameter object.
 *
 * @param size Number of keyframe animation states.
 *     <br>Returns **NULL** if the value of **size** is less than 0.
 * @return Keyframe animation parameter object. If the value of **size** is less than 0 or if **option** is abnormal, **
 *     NULL** is returned.
 * @since 12
 */
ArkUI_KeyframeAnimateOption* OH_ArkUI_KeyframeAnimateOption_Create(int32_t size);

/**
 * @brief Disposes of a keyframe animation parameter object.
 *
 * @param option Keyframe animation parameter object.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_KeyframeAnimateOption_Dispose(ArkUI_KeyframeAnimateOption* option);

/**
 * @brief Sets the overall delay of a keyframe animation, in milliseconds. By default, the keyframe animation starts
 * without any delay.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Animation delay, in milliseconds. Value range: (-∞, +∞). Default value: **0**, indicating no animation
 *     delay. A value greater than 0 means to begin the animation after the specified amount of time has elapsed. A
 *     value less than 0 means to begin the animation in advance. If **value** is less than **0** and the absolute
 *     value of **value** is less than the actual animation duration, the animation starts its first frame from the
 *     state at the absolute value. If the absolute value of **value** is greater than or equal to the actual animation
 *     duration, the animation starts its first frame from the end state. The actual animation duration is equal to the
 *     duration of a single animation multiplied by the number of animation playback times.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetDelay(ArkUI_KeyframeAnimateOption* option, int32_t value);

/**
 * @brief Sets the number of times that the keyframe animation is played. By default, the animation is played once. The
 * value **-1** indicates that the animation is played for an unlimited number of times. The value **0** indicates that
 * no animation is played.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Number of times that the animation is played. Value range: [-1, +∞). If this parameter is set to **0**,
 *     the animation is not played. If this parameter is set to **-1**, the animation is played for an infinite number
 *     of times. Default value: **1**, indicating that the animation is played once.
 *     <br>If the value is less than **-1**, the operation is invalid, and the error code
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetIterations(ArkUI_KeyframeAnimateOption* option, int32_t value);

/**
 * @brief Sets the callback invoked when the keyframe animation playback is complete. This function is called after the
 * {@link keyframe animation} has played for the specified number of times.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param userData Pointer to a custom object.
 *     <br>Abnormal value processing is not involved.
 * @param onFinish Indicates the callback.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_RegisterOnFinishCallback(
    ArkUI_KeyframeAnimateOption* option, void* userData, void (*onFinish)(void* userData));

/**
 * @brief Sets the expected frame rate for a keyframe animation.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param frameRate Expected frame rate for the keyframe animation.
 *     <br>If **frameRate** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 19
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetExpectedFrameRate(
    ArkUI_KeyframeAnimateOption* option, ArkUI_ExpectedFrameRateRange* frameRate);

/**
 * @brief Sets the duration of a keyframe animation, in milliseconds.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
   * @param value Keyframe animation duration, in ms. The default value is 1000 ms. Value range: [0, +∞).
 *     <br>If the value is less than 0, **0** is used.
 * @param index Index of the keyframe state segment.
 *     <br>If the value of **index** is less than 0, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetDuration(ArkUI_KeyframeAnimateOption* option, int32_t value, int32_t index);

/**
 * @brief Sets the animation curve for a specific keyframe animation segment.
 *
 * @note Because the <b>springMotion</b>, <b>responsiveSpringMotion</b>, and <b>interpolatingSpring</b> curves do not
 *     have effective duration settings, they are not supported.
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Animation curve to set. Default value: {@link ARKUI_CURVE_EASE_IN_OUT}.
 * @param index Index of the keyframe state segment. Value range: [0, size – 1], where **size** indicates the number of
 *     keyframe animation states.
 *     <br>If the value of **index** is less than 0 or out of range, the error code
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetCurve(
    ArkUI_KeyframeAnimateOption* option, ArkUI_CurveHandle value, int32_t index);

/**
 * @brief Sets the closure function of the state at the time of the keyframe, that is, the state to be reached at the
 * time of the keyframe.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param event Indicates a closure function.
 * @param userData Pointer to a user-defined object.
 *     <br>Abnormal value processing is not involved.
 * @param index Index of the keyframe state segment. Value range: [0, size – 1], where **size** indicates the number of
 *     keyframe animation states.
 *     <br>If the value of **index** is less than 0 or out of range, the error code
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_RegisterOnEventCallback(
    ArkUI_KeyframeAnimateOption* option, void* userData, void (*event)(void* userData), int32_t index);

/**
 * @brief Obtains the overall delay of a keyframe animation, in milliseconds.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @return Overall delay, in milliseconds. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_GetDelay(ArkUI_KeyframeAnimateOption* option);

/**
 * @brief Obtains the number of times that a keyframe animation is played.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @return Number of times that the animation is played. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_GetIterations(ArkUI_KeyframeAnimateOption* option);

/**
 * @brief Obtains the expected frame rate from keyframe animation parameters.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, **NULL** is returned.
 * @return Returns the expected frame rate obtained. If **option** is invalid, **NULL** is returned.
 * @since 19
 */
ArkUI_ExpectedFrameRateRange* OH_ArkUI_KeyframeAnimateOption_GetExpectedFrameRate(ArkUI_KeyframeAnimateOption* option);

/**
 * @brief Obtains the duration of a specific state in a keyframe animation, in milliseconds.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @param index Index of the keyframe state segment.
 *     <br>If the value of **index** is less than 0, **0** is returned.
 * @return Duration, in milliseconds. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_GetDuration(ArkUI_KeyframeAnimateOption* option, int32_t index);

/**
 * @brief Obtains the animation curve of a specific state in a keyframe animation.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, **NULL** is returned.
 * @param index Index of the keyframe state segment.
 *     <br>If the value of **index** is less than 0, **NULL** is returned.
 * @return Animation curve. If the parameter is abnormal, **NULL** is returned.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_KeyframeAnimateOption_GetCurve(ArkUI_KeyframeAnimateOption* option, int32_t index);

/**
 * @brief Creates an **AnimatorOption** object.
 *
 * @note When <b>keyframeSize</b> is greater than 0, the animation interpolation start point is 0, and the animation
 *     interpolation end point is 1; no setting is allowed.
 * @param keyframeSize Number of keyframes.
 *     <br>If the value of **keyframeSize** is less than 0, **NULL** is returned.
 * @return Pointer to the animator parameter object. If the value of **size** is less than 0 or if **option** is
 *     abnormal, **NULL** is returned.
 * @since 12
 */
ArkUI_AnimatorOption* OH_ArkUI_AnimatorOption_Create(int32_t keyframeSize);

/**
 * @brief Disposes of an **AnimatorOption** object.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_AnimatorOption_Dispose(ArkUI_AnimatorOption* option);

/**
 * @brief Sets the duration of an animator animation, in milliseconds.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Playback duration, in ms. The default value is 0 ms. Value range: [0, +∞).
 *     <br>If the value is less than 0, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetDuration(ArkUI_AnimatorOption* option, int32_t value);

/**
 * @brief Sets the delay time of the animator playback, in milliseconds.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Animation delay, in milliseconds. Value range: (-∞, +∞). Default value: **0**, indicating no animation
 *     delay. A value greater than 0 means to begin the animation after the specified amount of time has elapsed. A
 *     value less than 0 means to begin the animation in advance. If **value** is less than **0** and the absolute
 *     value of **value** is less than the actual animation duration, the animation starts its first frame from the
 *     state at the absolute value. If the absolute value of **value** is greater than or equal to the actual animation
 *     duration, the animation starts its first frame from the end state. The actual animation duration is equal to the
 *     duration of a single animation multiplied by the number of animation playback times.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetDelay(ArkUI_AnimatorOption* option, int32_t value);

/**
 * @brief Sets the number of times that an animator animation is played. By default, the animation is played once. The
 * value **-1** indicates that the animation is played for an unlimited number of times. The value **0** indicates that
 * no animation is played.
 *
 * @note If this parameter is set to a negative value other than <b>-1</b>, the value is invalid. In this case, the
 *     animation is played once.
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Value range: [-1, +∞). If this parameter is set to **0**, the animation is not played. If this
 *     parameter is set to **-1**, the animation is played for an infinite number of times. Default value: **1** (
 *     played once).
 *     <br>If the value is less than -1, the operation is invalid.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetIterations(ArkUI_AnimatorOption* option, int32_t value);

/**
 * @brief Sets the status of the component before and after the animator animation execution.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Status of the component before and after the animator animation execution. Default value:
 *     {@link ARKUI_ANIMATION_FILL_MODE_FORWARDS}.
 *     <br>If the value is less than 0, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetFill(ArkUI_AnimatorOption* option, ArkUI_AnimationFillMode value);

/**
 * @brief Set the playback direction.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Animation playback direction.
 *     <br>If the value is less than 0, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetDirection(ArkUI_AnimatorOption* option, ArkUI_AnimationDirection value);

/**
 * @brief Sets the interpolation curve for the animation of an animator.
 *
 * @note <b>springCurve</b>, <b>springMotion</b>, <b>responsiveSpringMotion</b>, <b>interpolatingSpring</b>,
 *     and <b>customCurve</b> curves are not supported.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Interpolation curve. Default value: {@link ARKUI_CURVE_LINEAR}. You are advised to use
 *     {@link ARKUI_CURVE_EASE_IN_OUT} to obtain a smoother animation effect.
 *     <br>If **value** is set to **NULL**, the default curve {@link ARKUI_CURVE_LINEAR} is used.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetCurve(ArkUI_AnimatorOption* option, ArkUI_CurveHandle value);

/**
 * @brief Sets the interpolation start point of an animation.
 *
 * @note This API does not take effect when the animation is a keyframe animation.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Interpolation start point of the animation. Value range: (-∞, +∞).
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetBegin(ArkUI_AnimatorOption* option, float value);

/**
 * @brief Sets the interpolation end point for the animation of an animator.
 *
 * @note This API does not take effect when the animation is a keyframe animation.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Interpolation end point of the animation. Value range: (-∞, +∞).
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetEnd(ArkUI_AnimatorOption* option, float value);

/**
 * @brief Sets the expected frame rate range of an animation.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Expected frame rate range.
 *     <br>If **value** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetExpectedFrameRateRange(
    ArkUI_AnimatorOption* option, ArkUI_ExpectedFrameRateRange* value);

/**
 * @brief Sets the keyframe parameters of an animator animation.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param time Keyframe time. Value range: [0, 1]. The value must be in ascending order. Default value: evenly
 *     distributed by index (for example, **0.0** for the first frame, **0.5** for the second frame, and **1.0** for
 *     the third frame).
 *     <br>If the value of **time** is less than 0 or greater than 1, the error code
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Keyframe value. Value range: (-∞, +∞).
 * @param index Keyframe index.
 *     <br>If the value of **index** is less than 0, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetKeyframe(
    ArkUI_AnimatorOption* option, float time, float value, int32_t index);

/**
 * @brief Sets the keyframe curve type for the animation of an animator.
 *
 * @note <b>springCurve</b>, <b>springMotion</b>, <b>responsiveSpringMotion</b>, <b>interpolatingSpring</b>,
 *     and <b>customCurve</b> curves are not supported.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Interpolation curve. Default value: **NULL**, indicating linear interpolation.
 * @param index Keyframe index.
 *     <br>If the value of **index** is less than 0, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetKeyframeCurve(ArkUI_AnimatorOption* option, ArkUI_CurveHandle value, int32_t index);
/**
 * @brief Obtains the duration for playing an animation.
 *
 * @param option Animator animation parameters.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @return Duration for playing the animation, in milliseconds. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_GetDuration(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the delay for playing an animation.
 *
 * @param option Animator animation parameters. If **option** is set to **NULL**, **0** is returned.
 * @return Delay for playing the animation, in milliseconds. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_GetDelay(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the number of times that an animator animation is played.
 *
 * @param option Animator parameters. If **option** is set to **NULL**, **0** is returned.
 * @return Number of times that the animation is played. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_GetIterations(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the status of the component before and after the animator animation execution.
 *
 * @param option Animator animation parameters.
 * @return Status of the component before and after the animator animation execution. If **option** is invalid,**-1**
 *     is returned.
 * @since 12
 */
ArkUI_AnimationFillMode OH_ArkUI_AnimatorOption_GetFill(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the playback direction of an animator animation.
 *
 * @param option Animator animation parameters.
 * @return Animation playback direction. If **option** is invalid,**-1** is returned.
 * @since 12
 */
ArkUI_AnimationDirection OH_ArkUI_AnimatorOption_GetDirection(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the interpolation curve of the animation of an animator.
 *
 * @param option Animator animation parameters.
 * @return Interpolation curve. If **option** is invalid, **NULL** is returned.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_AnimatorOption_GetCurve(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the interpolation start point of an animation.
 *
 * @param option Animator animation parameters.
 * @return Interpolation start point of the animation. If **option** is invalid, **0.0** is returned.
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetBegin(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the interpolation end point of an animation.
 *
 * @param option Animator animation parameters.
 * @return Interpolation end point of the animation. If **option** is invalid, **0.0** is returned.
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetEnd(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the expected frame rate range of an animator animation.
 *
 * @param option Animator animation parameters.
 * @return Pointer to the expected frame rate range object. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_ExpectedFrameRateRange* OH_ArkUI_AnimatorOption_GetExpectedFrameRateRange(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the keyframe time of the animator playback, in milliseconds.
 *
 * @param option Animator parameters.
 * @param index Keyframe index.
 * @return Keyframe time, in milliseconds.
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetKeyframeTime(ArkUI_AnimatorOption* option, int32_t index);

/**
 * @brief Obtains the keyframe value of an animation.
 *
 * @param option Animator parameters.
 * @param index Keyframe index.
 * @return Keyframe value.
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetKeyframeValue(ArkUI_AnimatorOption* option, int32_t index);

/**
 * @brief Obtains the interpolation curve for a keyframe in the animation of an animator.
 *
 * @param option Animator parameters.
 * @param index Keyframe index.
 * @return Interpolation curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_AnimatorOption_GetKeyframeCurve(ArkUI_AnimatorOption* option, int32_t index);

/**
 * @brief Obtains the user-defined object in an animation event object.
 *
 * @param event Animation event object.
 * @return User-defined object.
 * @since 12
 */
void* OH_ArkUI_AnimatorEvent_GetUserData(ArkUI_AnimatorEvent* event);

/**
 * @brief Obtains the user-defined object in the frame event of an animation.
 *
 * @param event Animation event object.
 * @return User-defined object.
 * @since 12
 */
void* OH_ArkUI_AnimatorOnFrameEvent_GetUserData(ArkUI_AnimatorOnFrameEvent* event);

/**
 * @brief Obtains the interpolation result in the animation frame callback event object.
 *
 * @param event Animation event object.
 * @return Animation interpolation result.
 *     <br>**NOTE**
 *     <br>During the animation, the interpolation result changes between the interpolation start point
 *     {@link OH_ArkUI_AnimatorOption_SetBegin} and the interpolation end point {@link OH_ArkUI_AnimatorOption_SetEnd}
 *     based on the animation parameters.
 * @since 12
 */
float OH_ArkUI_AnimatorOnFrameEvent_GetValue(ArkUI_AnimatorOnFrameEvent* event);

/**
 * @brief Sets the callback invoked when the animator receives a frame.
 *
 * @param option Animator animation parameters.
 * @param userData User-defined parameter.
 * @param callback Indicates the callback to set.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_RegisterOnFrameCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorOnFrameEvent* event));

/**
 * @brief Sets the callback invoked when the animation playback is complete.
 *
 * @param option Animator animation parameters.
 * @param userData User-defined parameter.
 * @param callback Indicates the callback to set.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_RegisterOnFinishCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event));

/**
 * @brief Sets the callback invoked when the animation playback is canceled.
 *
 * @param option Animator animation parameters.
 * @param userData User-defined parameter.
 * @param callback Indicates the callback to set.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_RegisterOnCancelCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event));

/**
 * @brief Sets the callback invoked when the animation playback is repeated.
 *
 * @param option Animator animation parameters.
 * @param userData User-defined parameter.
 * @param callback Indicates the callback to set.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_RegisterOnRepeatCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event));

/**
 * @brief Resets the animation of an animator.
 *
 * @param animatorHandle Animator object.
 * @param option Animator animation parameters.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_Animator_ResetAnimatorOption(
    ArkUI_AnimatorHandle animatorHandle, ArkUI_AnimatorOption* option);

/**
 * @brief Starts the animation of an animator.
 *
 * @param animatorHandle Animator object.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_Animator_Play(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief Ends the animation of an animator.
 *
 * @param animatorHandle Animator object.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_Animator_Finish(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief Pauses the animation of an animator.
 *
 * @param animatorHandle Animator object.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_Animator_Pause(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief Cancels the animation of an animator.
 *
 * @param animatorHandle Animator object.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_Animator_Cancel(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief Plays this animation in reverse order.
 *
 * @param animatorHandle Animator object.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_Animator_Reverse(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief Implements initialization for the interpolation curve, which is used to create an interpolation curve based
 * on the input parameter.
 *
 * @param curve Curve type.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCurveByType(ArkUI_AnimationCurve curve);

/**
 * @brief Creates a step curve.
 *
 * @param count Number of steps. The value must be a positive integer. Value range: [1, +∞).
 *     <br>If the value of **count** is abnormal, the operation is invalid.
 * @param end Whether the step change occurs at the start or end of each interval. **true**: The step change occurs at
 *     the end of each interval. **false**: The step change occurs at the start of each interval.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateStepsCurve(int32_t count, bool end);

/**
 * @brief Creates a cubic Bezier curve.
 *
 * @param x1 X-coordinate of the first point on the Bezier curve. Value range: [0, 1]. A value less than 0 is treated
 *     as **0**. A value greater than 1 is treated as **1**.
 * @param y1 Y-coordinate of the first point on the Bezier curve.
 * @param x2 X-coordinate of the second point on the Bezier curve. Value range: [0, 1]. A value less than 0 is treated
 *     as **0**. A value greater than 1 is treated as **1**.
 * @param y2 Y-coordinate of the second point on the Bezier curve.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCubicBezierCurve(float x1, float y1, float x2, float y2);

/**
 * @brief Creates a spring curve. The curve shape is determined by the spring parameters, and the animation duration is
 * controlled by the **duration** parameter in {@link animation} and {@link animateTo}.
 *
   * @param velocity Initial velocity. It is applied by external factors to the spring animation, designed to help
 *     ensure the smooth transition from the previous motion state. The velocity is the normalized velocity, and its
 *     value is equal to the actual velocity at the beginning of the animation divided by the animation attribute
 *     change value.
 * @param mass Mass. It describes the inertia of the object in the elastic system, affecting the amplitude of
 *     oscillation and the speed of return to equilibrium. The greater the mass, the greater the amplitude of the
 *     oscillation, and the slower the speed of restoring to the equilibrium position. Value range: [0, +∞).
 *     <br>If the value is less than or equal to 0, **1** is used.
 * @param stiffness Stiffness. It is the degree to which an object deforms by resisting the force applied. In an
 *     elastic system, the greater the stiffness, the stronger the ability to resist deformation, and the faster the
 *     speed of restoring to the equilibrium position. Value range: [0, +∞).
 *     <br>If the value is less than or equal to 0, **1** is used.
 * @param damping Damping. It is used to describe the oscillation and attenuation of the system after being disturbed.
 *     The larger the damping, the smaller the number of oscillations of elastic motion, and the smaller the
 *     oscillation amplitude. Value range: [0, +∞).
 *     <br>If the value is less than or equal to 0, **1** is used.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateSpringCurve(float velocity, float mass, float stiffness, float damping);

/**
 * @brief Creates a spring animation curve. If multiple spring animations are applied to the same attribute of an
 * object, each animation replaces their predecessor and inherits the velocity.
 *
 * @note The animation duration is subject to the curve parameters, rather than the <b>duration</b> parameter in
 *     <b>animation</b> or <b>animateTo</b>.
 *
 * @param response Duration of one complete oscillation. Value range: (0, +∞).
 *     <br>If the value is less than or equal to 0, **0.55** is used.
 * @param dampingFraction Damping coefficient. > 0 and < 1: underdamped. In this case, the spring overshoots the
 *     equilibrium position. **1**: critically damped. > 1: overdamped. In this case, the spring approaches equilibrium
 *     gradually. Value range: (0, +∞).
 *     <br>If the value is less than or equal to 0, **0.825** is used.
 * @param overlapDuration Duration for animations to overlap, in seconds. When animations overlap, the **response**
 *     values of these animations will transit smoothly over this duration if they are different. Value range: [0, +∞).
 *     <br>If the value is less than 0, **0** is used.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateSpringMotion(float response, float dampingFraction, float overlapDuration);

/**
 * @brief Creates a responsive spring animation curve. It is a special case of **springMotion**, with the only
 * difference in the default values. It can be used together with **springMotion**.
 *
 * @note The animation duration is subject to the curve parameters, rather than the <b>duration</b> parameter in
 *     <b>animation</b> or <b>animateTo</b>.
 *
 * @param response Duration of one complete oscillation. Value range: (0, +∞).
 *     <br>If the value is less than or equal to 0, **0.15** is used.
 * @param dampingFraction Damping coefficient. > 0 and < 1: underdamped. In this case, the spring overshoots the
 *     equilibrium position. **1**: critically damped. > 1: overdamped. In this case, the spring approaches equilibrium
 *     gradually. Value range: [0, +∞).
 *     <br>If the value is less than 0, **0.86** is used.
 * @param overlapDuration Duration for animations to overlap, in seconds. When animations overlap, the **response**
 *     values of these animations will transit smoothly over this duration if they are different. Value range: [0, +∞).
 *     <br>If the value is less than 0, **0.25** is used.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateResponsiveSpringMotion(
    float response, float dampingFraction, float overlapDuration);

/**
 * @brief Creates an interpolating spring curve animated from 0 to 1. The actual animation value is calculated based on
 * the curve.
 *
 * @note The animation duration is subject to the curve parameters, rather than the <b>duration</b> parameter in
 *     <b>animation</b> or <b>animateTo</b>.
 *
 *
   * @param velocity Initial velocity. It is applied by external factors to the spring animation, designed to help
 *     ensure the smooth transition from the previous motion state. The velocity is the normalized velocity, and its
 *     value is equal to the actual velocity at the beginning of the animation divided by the animation attribute
 *     change value.
 * @param mass Mass. It describes the inertia of the object in the elastic system, affecting the amplitude of
 *     oscillation and the speed of return to equilibrium. The greater the mass, the greater the amplitude of the
 *     oscillation, and the slower the speed of restoring to the equilibrium position. Value range: [0, +∞).
 *     <br>If the value is less than or equal to 0, **1** is used.
 * @param stiffness Stiffness. It is the degree to which an object deforms by resisting the force applied. The greater
 *     the stiffness, the stronger the ability to resist deformation, and the faster the speed of restoring to the
 *     equilibrium position. Value range: [0, +∞).
 *     <br>If the value is less than or equal to 0, **1** is used.
 * @param damping Damping. It is used to describe the oscillation and attenuation of the system after being disturbed.
 *     The larger the damping, the smaller the number of oscillations of elastic motion, and the smaller the
 *     oscillation amplitude. Value range: [0, +∞).
 *     <br>If the value is less than or equal to 0, **1** is used.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateInterpolatingSpring(float velocity, float mass, float stiffness, float damping);

/**
 * @brief Creates a custom curve.
 *
 * @param userData Pointer to user-defined data.
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
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCustomCurve(
    void* userData, float (*interpolate)(float fraction, void* userdata));

/**
 * @brief Disposes of a custom curve.
 *
 * @param curveHandle Pointer to the interpolation object of the curve.
 * @since 12
 */
void OH_ArkUI_Curve_DisposeCurve(ArkUI_CurveHandle curveHandle);

/**
 * @brief Creates an opacity effect object for component transitions.
 *
 * @note If the value specified is less than 0, the value <b>0</b> is used. If the value specified is greater than 1,
 *     the value <b>1</b> is used.
 * @param opacity Opacity. Value range: [0, 1]. The default value is **1**. A value less than 0 is treated as 0. A
 *     value greater than 1 is treated as 1. The value **1** means fully opaque, and **0** means fully transparent.
 * @return Opacity effect object for component transitions.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateOpacityTransitionEffect(float opacity);

/**
 * @brief Creates a translation effect object for component transitions.
 *
 * @param translate Translation parameter object for component transitions.
 * @return Translation effect object for component transitions. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateTranslationTransitionEffect(ArkUI_TranslationOptions* translate);

/**
 * @brief Creates a scaling effect object for component transitions.
 *
 * @param scale Scaling parameter object for component transitions.
 * @return Scaling effect object for component transitions. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateScaleTransitionEffect(ArkUI_ScaleOptions* scale);

/**
 * @brief Creates a rotation effect object for component transition.
 *
 * @param rotate Rotation parameter object for component transitions.
 * @return Rotation effect object for component transitions. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateRotationTransitionEffect(ArkUI_RotationOptions* rotate);

/**
 * @brief Creates a movement transition effect object for the component.
 *
 * @param edge Movement transition type.
 * @return Translation effect object for component transitions. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateMovementTransitionEffect(ArkUI_TransitionEdge edge);

/**
 * @brief Creates an asymmetric transition effect.
 *
 * @note If the <b>asymmetric</b> function is not used for <b>TransitionEffect</b>, the transition effect takes effect
 *     for both appearance and disappearance of the component.
 * @param appear Transition effect for appearance.
 * @param disappear Transition effect for disappearance.
 * @return Asymmetric transition effect. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateAsymmetricTransitionEffect(
    ArkUI_TransitionEffect* appear, ArkUI_TransitionEffect* disappear);

/**
 * @brief Create an identity transition effect.
 * Identity transition effect performs no visual transition animation. It can alse be used as the appear or disappear
 * parameter of OH_ArkUI_CreateAsymmetricTransitionEffect to indicate no animation on one side.
 *
 * @return Returns a pointer to the created transition effect object.
 * @release native_animate/OH_ArkUI_TransitionEffect_Dispose {return}
 * @since 26.0.0
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateIdentityTransitionEffect(void);

/**
 * @brief Disposes of a transition effect.
 *
 * @param effect Pointer to the transition effect to be disposed.
 * @since 12
 */
void OH_ArkUI_TransitionEffect_Dispose(ArkUI_TransitionEffect* effect);

/**
 * @brief Sets a combination of transition effects.
 *
 * @param firstEffect Transition effect.
 * @param secondEffect Combination of transition effects.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_TransitionEffect_Combine(
    ArkUI_TransitionEffect* firstEffect, ArkUI_TransitionEffect* secondEffect);

/**
 * @brief Sets transition effect animation settings.
 *
 * @note If <b>combine</b> is used for combining transition effects, the animation settings of a transition effect are
 *     applicable to the one following it.
 * @param effect Transition effect.
 * @param animation Animation settings.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_TransitionEffect_SetAnimation(
    ArkUI_TransitionEffect* effect, ArkUI_AnimateOption* animation);
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_ANIMATE_H
/** @} */

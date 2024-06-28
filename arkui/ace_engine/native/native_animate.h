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

#ifndef ARKUI_NATIVE_ANIMATE_H
#define ARKUI_NATIVE_ANIMATE_H

#include <cstdint>

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
    /** Expected minimum frame rate. */
    uint32_t min;
    /** Expected maximum frame rate. */
    uint32_t max;
    /** Expected optimal frame rate. */
    uint32_t expected;
} ArkUI_ExpectedFrameRateRange;

/**
* @brief Defines the callback type for when the animation playback is complete.
*
* @since 12
*/
typedef struct {
    /** Type of the <b>onFinish</b> callback. */
    ArkUI_FinishCallbackType type;
    /** Callback invoked when the animation playback is complete. */
    void (*callback)(void* userData);
    /** Custom type. */
    void* userData;
} ArkUI_AnimateCompleteCallback;

/**
* @brief Defines the animation configuration.
*
* @since 12
*/
typedef struct ArkUI_AnimateOption ArkUI_AnimateOption;

/**
 * @brief Defines the transition effect.
 *
 * @since 12
 */
typedef struct ArkUI_TransitionEffect ArkUI_TransitionEffect;

/**
 * @brief Implements the native animation APIs provided by ArkUI.
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
    * @param context UIContext。
    * @param option Indicates the pointer to an animation configuration.
    * @param update Indicates the animation closure. The system automatically inserts a transition animation
    * for the state change caused by the closure.
    * @param complete Indicates the callback to be invoked when the animation playback is complete.
    * @return Returns the error code.
    *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
    *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
    */
    int32_t (*animateTo)(ArkUI_ContextHandle context, ArkUI_AnimateOption* option, ArkUI_ContextCallback* update,
        ArkUI_AnimateCompleteCallback* complete);
} ArkUI_NativeAnimateAPI_1;

/**
* @brief Creates an animation configuration.
*
* @return Returns the pointer to the created animation configuration.
* @since 12
*/
ArkUI_AnimateOption* OH_ArkUI_AnimateOption_Create();

/**
* @brief Destroys an animation configuration.
*
* @since 12
*/
void OH_ArkUI_AnimateOption_Dispose(ArkUI_AnimateOption* option);

/**
* @brief Obtains the animation duration, in milliseconds.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the duration.
* @since 12
*/
uint32_t OH_ArkUI_AnimateOption_GetDuration(ArkUI_AnimateOption* option);

/**
* @brief Obtains the animation playback speed.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the animation playback speed.
* @since 12
*/
float OH_ArkUI_AnimateOption_GetTempo(ArkUI_AnimateOption* option);

/**
* @brief Obtains the animation curve.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the animated curve.
* @since 12
*/
ArkUI_AnimationCurve OH_ArkUI_AnimateOption_GetCurve(ArkUI_AnimateOption* option);

/**
* @brief Obtains the animation delay, in milliseconds.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the animation delay.
* @since 12
*/
int32_t OH_ArkUI_AnimateOption_GetDelay(ArkUI_AnimateOption* option);

/**
* @brief Obtains the number of times that an animation is played.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the number of times that the animation is played.
* @since 12
*/
int32_t OH_ArkUI_AnimateOption_GetIterations(ArkUI_AnimateOption* option);

/**
* @brief Obtains the animation playback mode.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the animation playback mode.
* @since 12
*/
ArkUI_AnimationPlayMode OH_ArkUI_AnimateOption_GetPlayMode(ArkUI_AnimateOption* option);

/**
* @brief Obtains the expected frame rate range of an animation.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the expected frame rate range.
* @since 12
*/
ArkUI_ExpectedFrameRateRange* OH_ArkUI_AnimateOption_GetExpectedFrameRateRange(ArkUI_AnimateOption* option);

/**
* @brief Sets the animation duration.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the duration, in milliseconds.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetDuration(ArkUI_AnimateOption* option, int32_t value);

/**
* @brief Sets the animation playback speed.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the animation playback speed.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetTempo(ArkUI_AnimateOption* option, float value);

/**
* @brief Sets the animation curve.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the animated curve.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetCurve(ArkUI_AnimateOption* option, ArkUI_AnimationCurve value);

/**
* @brief Sets the animation delay.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the animation delay.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetDelay(ArkUI_AnimateOption* option, int32_t value);

/**
* @brief Sets the number of times that an animation is played.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the number of times that the animation is played.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetIterations(ArkUI_AnimateOption* option, int32_t value);

/**
* @brief Sets the animation playback mode.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the animation playback mode.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetPlayMode(ArkUI_AnimateOption* option, ArkUI_AnimationPlayMode value);

/**
* @brief Sets the expected frame rate range of an animation.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the expected frame rate range.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(ArkUI_AnimateOption* option, ArkUI_ExpectedFrameRateRange* value);

/**
 * @brief Creates an opacity object for component transition.
 *
 * @note If the value specified is less than 0, the value <b>0</b> is used. If the value specified is greater than 1,
 * the value <b>1</b> is used.
 * @param opacity Indicates the opacity. Value range: [0, 1].
 * @return Returns the created opacity object for component transition.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateOpacityTransitionEffect(float opacity);

/**
 * @brief Creates a translation object for component transition.
 *
 * @param translate Indicates the translation settings for component transition.
 * @return Returns the translation object created for component transition.
 *         Returns <b>NULL</b> if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateTranslationTransitionEffect(ArkUI_TranslationOptions* translate);

/**
 * @brief Creates a scaling object for component transition.
 *
 * @param scale Indicates the scaling settings for component transition.
 * @return Returns the scaling object created for component transition.
 *         Returns <b>NULL</b> if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateScaleTransitionEffect(ArkUI_ScaleOptions* scale);

/**
 * @brief Creates a rotation object for component transition.
 *
 * @param rotate Indicates the rotation settings for component transition.
 * @return Returns the rotation object created for component transition.
 *         Returns <b>NULL</b> if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateRotationTransitionEffect(ArkUI_RotationOptions* rotate);

/**
 * @brief Creates a movement object for component transition.
 *
 * @param edge Indicates the movement type.
 * @return Returns the movement object created for component transition.
 *         Returns <b>NULL</b> if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateMovementTransitionEffect(ArkUI_TransitionEdge edge);

/**
 * @brief Creates an asymmetric transition effect.
 *
 * @note If the <b>asymmetric</b> function is not used for <b>TransitionEffect</b>, the transition effect takes effect
 * for both appearance and disappearance of the component.
 * @param appear Indicates the transition effect for appearance.
 * @param disappear Indicates the transition effect for disappearance.
 * @return Returns the asymmetric transition effect.
 *         Returns <b>NULL</b> if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateAsymmetricTransitionEffect(
    ArkUI_TransitionEffect* appear, ArkUI_TransitionEffect* disappear);

/**
 * @brief Disposes of a transition effect.
 *
 * @param effect Indicates the transition effect to dispose of.
 * @since 12
 */
void OH_ArkUI_TransitionEffect_Dispose(ArkUI_TransitionEffect* effect);

/**
 * @brief Sets a combination of transition effects.
 *
 * @param firstEffect Indicates the transition effect options.
 * @param secondEffect Indicates the combination of transition effects.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_TransitionEffect_Combine(
    ArkUI_TransitionEffect* firstEffect, ArkUI_TransitionEffect* secondEffect);

/**
 * @brief Sets transition effect animation settings.
 *
 * @note If <b>combine</b> is used for combining transition effects, the animation settings of a transition effect are
 * applicable to the one following it.
 * @param effect Indicates the transition effect options.
 * @param animation Indicates the animation settings.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_TransitionEffect_SetAnimation(
    ArkUI_TransitionEffect* effect, ArkUI_AnimateOption* animation);
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_ANIMATE_H
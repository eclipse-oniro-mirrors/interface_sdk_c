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
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 12
 */

/**
 * @file drawable_descriptor.h
 *
 * @brief Declares the APIs of **NativeDrawableDescriptor**.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_DRAWABLE_DESCRIPTOR_H
#define ARKUI_NATIVE_DRAWABLE_DESCRIPTOR_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines a struct for the **DrawableDescriptor** object.
 *
 * @since 12
 */
typedef struct ArkUI_DrawableDescriptor ArkUI_DrawableDescriptor;

/**
 * @brief The OH_PixelmapNative struct describes an uncompressed PixelMap format, which is encapsulated at the native
 * layer after images are decoded.<br>To create an OH_PixelmapNative object, call
 * {@link OH_PixelmapNative_CreatePixelmap}. By default, BGRA_8888 is used for data processing.<br>To release an
 * OH_PixelmapNative object, call {@link OH_PixelmapNative_Release}.<br>The table below describes the content and
 * operation mode of the OH_PixelmapNative struct.
 *
 * @since 12
 */
struct OH_PixelmapNative;

/**
 * @brief Defines a struct for the pointer to an **OH_PixelmapNative** object.
 *
 * @since 12
 */
typedef struct OH_PixelmapNative* OH_PixelmapNativeHandle;

/**
 * @brief Defines the ArkUI native component object.
 *
 * @since 22
 */
struct ArkUI_Node;

/**
 * @brief Defines the pointer to an ArkUI native component object.
 *
 * @since 22
 */
typedef struct ArkUI_Node* ArkUI_NodeHandle;

/**
 * @brief Enumerates the playback states of DrawableDescriptor animations.
 *
 * @since 22
 */
typedef enum {
    /**
     * The animation is in the initial state.
     *
     * @since 22
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_INITIAL = 0,
    /**
     * The animation is being played.
     *
     * @since 22
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_RUNNING = 1,
    /**
     * The animation is paused.
     *
     * @since 22
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_PAUSED = 2,
    /**
     * The animation is stopped.
     *
     * @since 22
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_STOPPED = 3
} DrawableDescriptor_AnimationStatus;

/**
 * @brief Enumerates the stop modes of {@link DrawableDescriptor} animations.
 *
 * @since 24
 */
typedef enum {
    /**
     * The animation returns to the first frame when it stops.
     *
     * @since 24
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_FIRST_FRAME = 0,
    /**
     * The animation stays at the last frame when it stops.
     *
     * @since 24
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_LAST_FRAME = 1
} DrawableDescriptor_AnimationStopMode;

/**
 * @brief Defines the DrawableDescriptor animation controller object.
 *
 * @since 22
 */
typedef struct ArkUI_DrawableDescriptor_AnimationController ArkUI_DrawableDescriptor_AnimationController;

/**
 * @brief Creates a **DrawableDescriptor** object from a **PixelMap** object.
 *
 * @param pixelMap Pointer to the {@link OH_PixelmapNative} object.
 * @return Pointer to the **DrawableDescriptor** object.
 * @since 12
 */
ArkUI_DrawableDescriptor* OH_ArkUI_DrawableDescriptor_CreateFromPixelMap(OH_PixelmapNativeHandle pixelMap);

/**
 * @brief Creates a **DrawableDescriptor** object from an array of **PixelMap** objects.
 *
 * @param array Pointer to the array of **PixelMap** objects.
 * @param size Size of the **PixelMap** object array.
 * @return Pointer to the **DrawableDescriptor** object.
 * @since 12
 */
ArkUI_DrawableDescriptor* OH_ArkUI_DrawableDescriptor_CreateFromAnimatedPixelMap(
    OH_PixelmapNativeHandle* array, int32_t size);

/**
 * @brief Disposes of the pointer to a **DrawableDescriptor** object.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @since 12
 */
void OH_ArkUI_DrawableDescriptor_Dispose(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief Obtains the pointer to a **PixelMap** object.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @return Pointer to the {@link OH_PixelmapNative} object.
 * @since 12
 */
OH_PixelmapNativeHandle OH_ArkUI_DrawableDescriptor_GetStaticPixelMap(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief Obtains an array of **PixelMap** objects for playing an animation.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @return Pointer to the array of **PixelMap** objects.
 * @since 12
 */
OH_PixelmapNativeHandle* OH_ArkUI_DrawableDescriptor_GetAnimatedPixelMapArray(
    ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief Obtains the size of the **PixelMap** object array for playing an animation.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @return Size of the **PixelMap** object array.
 * @since 12
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimatedPixelMapArraySize(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief Sets the total playback duration for an array of **PixelMap** objects.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @param duration Total playback duration, in ms. Value range: [0, +∞). If a negative value is passed in, **0** is
 *     used.
 * @since 12
 */
void OH_ArkUI_DrawableDescriptor_SetAnimationDuration(ArkUI_DrawableDescriptor* drawableDescriptor, int32_t duration);

/**
 * @brief Obtains the total playback duration for an array of **PixelMap** objects.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @return Total playback duration, in ms.
 * @since 12
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationDuration(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief Sets the number of times that an array of **PixelMap** objects is played.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @param iteration Indicates the number of playback times.
 * @since 12
 */
void OH_ArkUI_DrawableDescriptor_SetAnimationIteration(
    ArkUI_DrawableDescriptor* drawableDescriptor, int32_t iteration);

/**
 * @brief Obtains the number of times that an array of **PixelMap** objects is played.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @return Number of playback times.
 * @since 12
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationIteration(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief Sets the duration for each frame in a DrawableDescriptor animation.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @param durations Array of the playback durations for each frame in the animation, in ms.
 *     <br>If this parameter is not set, the playback follows the total duration. This parameter takes precedence over
 *     {@link OH_ArkUI_DrawableDescriptor_SetAnimationDuration}. That is, if both **
 *     OH_ArkUI_DrawableDescriptor_SetAnimationDuration** and **OH_ArkUI_DrawableDescriptor_SetAnimationFrameDurations**
 *     are set, **OH_ArkUI_DrawableDescriptor_SetAnimationDuration** does not take effect.
 *     <br>The array size must match the number of frames in the PixelMap image array.
 *     <br>Valid range for each frame's playback duration: [0, +∞). Default value: evenly distributed total duration.
 * @param size Array size.
 * @return Result code.
 *     <ul>
 *     <li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_SetAnimationFrameDurations(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t* durations, size_t size);

/**
 * @brief Obtains the duration of each frame in a DrawableDescriptor animation.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @param durations Array of the playback durations for each frame in the animation, in ms.
 * @param size Array size.
 * @return Result code.
 *     <ul>
 *     <li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationFrameDurations(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t* durations, size_t* size);

/**
 * @brief Specifies whether to enable autoplay for a DrawableDescriptor animation.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @param autoPlay Whether to enable autoplay.
 *     <br>**1** to enable, **0** otherwise.
 *     <br>The default value is **1**.
 * @return Result code.
 *     <ul>
 *     <li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_SetAnimationAutoPlay(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t autoPlay);

/**
 * @brief Checks whether autoplay is enabled for a DrawableDescriptor animation.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @param autoPlay Whether autoplay is enabled.
 * @return Result code.
 *     <ul>
 *     <li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationAutoPlay(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t* autoPlay);

/**
 * @brief Sets the stop mode for an animation.
 *
 * @param drawableDescriptor Pointer to the {@link DrawableDescriptor} object.
 * @param mode Stop mode of an animation.
 *     <br>The value is an enumerated value of {@link DrawableDescriptor_AnimationStopMode}. The default value is
 *     {@link DRAWABLE_DESCRIPTOR_ANIMATION_FIRST_FRAME}.
 * @return Result code.
 *     <ul>
 *     <li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *     </ul>
 * @since 24
 */
int32_t OH_ArkUI_DrawableDescriptor_SetAnimationStopMode(
    ArkUI_DrawableDescriptor* drawableDescriptor, DrawableDescriptor_AnimationStopMode mode);

/**
 * @brief Obtains the stop mode of an animation.
 *
 * @param drawableDescriptor Pointer to the {@link DrawableDescriptor} object.
 * @param mode Stop mode of an animation.
 *     <br>For details about the values, see {@link DrawableDescriptor_AnimationStopMode}.
 * @return Result code.
 *     <ul>
 *     <li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *     </ul>
 * @since 24
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationStopMode(
    const ArkUI_DrawableDescriptor* drawableDescriptor, DrawableDescriptor_AnimationStopMode* mode);

/**
 * @brief Creates an animation controller for the DrawableDescriptor.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @param node Pointer to the component node.
 * @param controller Pointer to a **DrawableDescriptor** animation controller.
 * @return Result code.
 *     <ul>
 *     <li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_CreateAnimationController(ArkUI_DrawableDescriptor *drawableDescriptor,
    ArkUI_NodeHandle node, ArkUI_DrawableDescriptor_AnimationController** controller);

/**
 * @brief Disposes of the DrawableDescriptor animation controller.
 *
 * @param controller Pointer to a **DrawableDescriptor** animation controller.
 * @since 22
 */
void OH_ArkUI_DrawableDescriptor_DisposeAnimationController(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Starts playback from the first frame.
 *
 * @param controller Pointer to a **DrawableDescriptor** animation controller.
 * @return Result code.
 *     <ul>
 *     <li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_StartAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Stops the DrawableDescriptor animation and returns to the first frame.
 *
 * @param controller Pointer to a **DrawableDescriptor** animation controller.
 * @return Result code.
 *     <ul>
 *     <li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_StopAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Resumes the DrawableDescriptor animation from the current frame.
 *
 * @param controller Pointer to a **DrawableDescriptor** animation controller.
 * @return Result code.
 *     <ul>
 *     <li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_ResumeAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Pauses playback on the current frame.
 *
 * @param controller Pointer to a **DrawableDescriptor** animation controller.
 * @return Result code.
 *     <ul>
 *     <li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_PauseAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Obtains the playback status of the DrawableDescriptor animation.
 *
 * @param controller Pointer to a **DrawableDescriptor** animation controller.
 * @param status Playback state of the DrawableDescriptor animation.
 * @return Result code.
 *     <ul>
 *     <li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationStatus(
    ArkUI_DrawableDescriptor_AnimationController* controller, DrawableDescriptor_AnimationStatus* status);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_DRAWABLE_DESCRIPTOR_H
/** @} */
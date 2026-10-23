/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 * @brief Defines the APIs of **DrawableDescriptor**.
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

#include "common_type.h"

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
 * @brief OH_PixelmapNative is an uncompressed pixel map format struct encapsulated at the native layer after image
 * decoding. It supports operations such as pixel data read/write, opacity setting, scaling, translation, rotation,
 * flipping, and cropping. It is suitable for scenarios where pixel-level processing and transformation of PixelMaps
 * are required at the native layer.<br>To create an OH_PixelmapNative object, you need to use the
 * {@link OH_PixelmapNative_CreatePixelmap} series of functions. If the source pixel format is not specified, these
 * functions parse the source pixel data in the BGRA_8888 format by default. After use, you must call the
 * {@link OH_PixelmapNative_Release} function to release the resources. These two operations must be paired; otherwise,
 * memory leaks may occur.<br>The table below describes some functions and operation modes of the OH_PixelmapNative
 * struct.
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
 * @brief Enumerates the playback states of DrawableDescriptor animations.
 *
 * @since 22
 */
typedef enum {
    /**
     * The animation is in the initial state.
     * @since 22
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_INITIAL = 0,
    /**
     * The animation is being played.
     * @since 22
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_RUNNING = 1,
    /**
     * The animation is paused.
     * @since 22
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_PAUSED = 2,
    /**
     * The animation is stopped.
     * @since 22
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_STOPPED = 3
} DrawableDescriptor_AnimationStatus;

/**
 * @brief Enumerates the stop modes of {@link ArkUI_DrawableDescriptor} animations.
 *
 * @since 24
 */
typedef enum {
    /**
     * The animation returns to the first frame when it stops.
     * @since 24
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_FIRST_FRAME = 0,
    /**
     * The animation stays at the last frame when it stops.
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
 * @param size Size of the PixelMap image array, in number of elements. It must be a positive integer. **nullptr** is
 *     returned if a NULL array is passed or the value of **size** is less than or equal to **0**.
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
 * @return Total playback duration, in ms. If this parameter is not set, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationDuration(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief Sets the number of times that an array of **PixelMap** objects is played.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @param iteration Number of playback times. Value range: [0, +∞). The value **0** indicates infinite playback. If a
 *     negative value is passed in, **0** is used.
 * @since 12
 */
void OH_ArkUI_DrawableDescriptor_SetAnimationIteration(
    ArkUI_DrawableDescriptor* drawableDescriptor, int32_t iteration);

/**
 * @brief Obtains the number of times that an array of **PixelMap** objects is played.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @return Number of playback times. The value **0** indicates infinite playback.
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
 * @param durations Array of the playback durations for each frame in the animation.
 * @param size Array size.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the input parameter is incorrect.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationFrameDurations(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t* durations, size_t* size);

/**
 * @brief Specifies whether to enable autoplay for a DrawableDescriptor animation.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @param autoPlay Whether to enable autoplay for the animation.
 *     The value **1** means to enable, and **0** means the opposite.
 *     The default value is **1**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the input parameter is incorrect.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_SetAnimationAutoPlay(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t autoPlay);

/**
 * @brief Checks whether autoplay is enabled for a DrawableDescriptor animation.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object.
 * @param autoPlay Whether to enable autoplay. **1** to enable, **0** otherwise.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the input parameter is incorrect.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationAutoPlay(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t* autoPlay);

/**
 * @brief Sets the stop mode for an animation.
 *
 * @param drawableDescriptor Pointer to the {@link ArkUI_DrawableDescriptor} object.
 * @param mode Stop mode of an animation.
 *     <br>The value is an enumerated value of {@link DrawableDescriptor_AnimationStopMode}. The default value is
 *     {@link DRAWABLE_DESCRIPTOR_ANIMATION_FIRST_FRAME}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the input parameter is incorrect.
 * @since 24
 */
int32_t OH_ArkUI_DrawableDescriptor_SetAnimationStopMode(
    ArkUI_DrawableDescriptor* drawableDescriptor, DrawableDescriptor_AnimationStopMode mode);

/**
 * @brief Obtains the stop mode of an animation.
 *
 * @param drawableDescriptor Pointer to the {@link ArkUI_DrawableDescriptor} object.
 * @param mode Stop mode of an animation.
 *     <br>For details about the values, see {@link DrawableDescriptor_AnimationStopMode}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the input parameter is incorrect.
 * @since 24
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationStopMode(
    const ArkUI_DrawableDescriptor* drawableDescriptor, DrawableDescriptor_AnimationStopMode* mode);

/**
 * @brief Creates an animation controller. When you need to manually control the playback of an animation (for example,
 * frame-by-frame playback, pausing, seeking to a specified frame, or setting the duration of a single frame) instead
 * of using automatic playback, call this API to obtain the controller, and then call control APIs such as **
 * StartAnimation** and **Pause**.
 *
 * @param drawableDescriptor Pointer to a **DrawableDescriptor** object. The value must be an animation object created
 *     using {@link OH_ArkUI_DrawableDescriptor_CreateFromAnimatedPixelMap}.
 * @param node Pointer to the component node. The value must be a valid ArkUI component node.
 * @param controller Pointer to the **DrawableDescriptor** animation controller object. This is an output parameter,
 *     which returns the controller pointer when the call is successful.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the input parameter is incorrect.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the input parameter is incorrect.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_StartAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Stops the playback of an animation. The position after the playback is stopped is determined by the stop mode
 * set by {@link OH_ArkUI_DrawableDescriptor_SetAnimationStopMode}. If the stop mode is set to **
 * DRAWABLE_DESCRIPTOR_ANIMATION_FIRST_FRAME**, the playback returns to the first frame. If the stop mode is set to **
 * DRAWABLE_DESCRIPTOR_ANIMATION_LAST_FRAME**, the playback stays at the last frame.
 *
 * @param controller Pointer to a **DrawableDescriptor** animation controller.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the input parameter is incorrect.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_StopAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Resumes the DrawableDescriptor animation from the current frame.
 *
 * @param controller Pointer to a **DrawableDescriptor** animation controller.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the input parameter is incorrect.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_ResumeAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Pauses playback on the current frame.
 *
 * @param controller Pointer to a **DrawableDescriptor** animation controller.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the input parameter is incorrect.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_PauseAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Obtains the playback status of the DrawableDescriptor animation.
 *
 * @param controller Pointer to a **DrawableDescriptor** animation controller.
 * @param status Playback state of the DrawableDescriptor animation.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the input parameter is incorrect.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationStatus(
    ArkUI_DrawableDescriptor_AnimationController* controller, DrawableDescriptor_AnimationStatus* status);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_DRAWABLE_DESCRIPTOR_H
/** @} */
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
 * @brief Provides ImageAnimator type definitions of ArkUI on the native side.
 *
 * @since 12
 */

/**
 * @file image_animator.h
 *
 * @brief Defines **ImageAnimator** node types for **NativeNode** APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_ANIMATOR_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_ANIMATOR_H

#include <stdint.h>

#include "../drawable_descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the playback states of the frame-by-frame animation.
 *
 * @since 12
 */
typedef enum {
    /**
     * The animation is in the initial state.
     *
     * @since 12
     */
    ARKUI_ANIMATION_STATUS_INITIAL = 0,
    /**
     * The animation is being played.
     *
     * @since 12
     */
    ARKUI_ANIMATION_STATUS_RUNNING = 1,
    /**
     * The animation is paused.
     *
     * @since 12
     */
    ARKUI_ANIMATION_STATUS_PAUSED = 2,
    /**
     * The animation is stopped.
     *
     * @since 12
     */
    ARKUI_ANIMATION_STATUS_STOPPED = 3
} ArkUI_AnimationStatus;

/**
 * @brief Defines the image animation frame information.
 *
 * @since 12
 */
typedef struct ArkUI_ImageAnimatorFrameInfo ArkUI_ImageAnimatorFrameInfo;

/**
 * @brief Creates an image frame information object based on an image path, with the image format being SVG, PNG, or
 * JPG. Both relative and absolute paths in the application sandbox are supported.
 *
 * @param src Pointer to the image path, which can be a relative or absolute path in the application sandbox.
 * @return Pointer to the image frame information object.
 * @since 12
 */
ArkUI_ImageAnimatorFrameInfo* OH_ArkUI_ImageAnimatorFrameInfo_CreateFromString(char* src);

/**
 * @brief Creates an image frame information object based on an [{@link ArkUI_DrawableDescriptor} object, with the
 * image format being Resource or PixelMap.
 *
 * @param drawable Pointer to an **ArkUI_DrawableDescriptor** object created using Resource or PixelMap.
 * @return Pointer to the image frame information object.
 * @since 12
 */
ArkUI_ImageAnimatorFrameInfo* OH_ArkUI_ImageAnimatorFrameInfo_CreateFromDrawableDescriptor(
    ArkUI_DrawableDescriptor* drawable);

/**
 * @brief Disposes of the pointer to an image frame information object.
 *
 * @param imageInfo Pointer to the image frame information object.
 * @since 12
 */
void OH_ArkUI_ImageAnimatorFrameInfo_Dispose(ArkUI_ImageAnimatorFrameInfo* imageInfo);

/**
 * @brief Sets the image width.
 *
 * @param imageInfo Pointer to the image frame information object.
 * @param width Image width, in px.
 * @since 12
 */
void OH_ArkUI_ImageAnimatorFrameInfo_SetWidth(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t width);

/**
 * @brief Obtains the image width.
 *
 * @param imageInfo Pointer to the image frame information object.
 * @return Image width, in px. If **imageInfo** is a null pointer, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetWidth(ArkUI_ImageAnimatorFrameInfo* imageInfo);

/**
 * @brief Sets the image height.
 *
 * @param imageInfo Pointer to the image frame information object.
 * @param height Image height, in px.
 * @since 12
 */
void OH_ArkUI_ImageAnimatorFrameInfo_SetHeight(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t height);

/**
 * @brief Obtains the image height.
 *
 * @param imageInfo Pointer to the image frame information object.
 * @return Image height, in px. If **imageInfo** is a null pointer, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetHeight(ArkUI_ImageAnimatorFrameInfo* imageInfo);
/**
 * @brief Sets the vertical coordinate of an image relative to the upper left corner of the component.
 *
 * @param imageInfo Pointer to the image frame information object.
 * @param top Vertical coordinate of the image relative to the upper left corner of the component, in px.
 * @since 12
 */
void OH_ArkUI_ImageAnimatorFrameInfo_SetTop(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t top);

/**
 * @brief Obtains the vertical coordinate of an image relative to the upper left corner of the component.
 *
 * @param imageInfo Pointer to the image frame information object.
 * @return Vertical coordinate of the image relative to the upper left corner of the component, in px. If **imageInfo**
 *     is a null pointer, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetTop(ArkUI_ImageAnimatorFrameInfo* imageInfo);
/**
 * @brief Sets the horizontal coordinate of an image relative to the upper left corner of the component.
 *
 * @param imageInfo Pointer to the image frame information object.
 * @param left Horizontal coordinate of the image relative to the upper left corner of the component, in px.
 * @since 12
 */
void OH_ArkUI_ImageAnimatorFrameInfo_SetLeft(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t left);

/**
 * @brief Obtains the horizontal coordinate of an image relative to the upper left corner of the component.
 *
 * @param imageInfo Pointer to the image frame information object.
 * @return Horizontal coordinate of the image relative to the upper left corner of the component, in px. If **imageInfo*
 *     * is a null pointer, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetLeft(ArkUI_ImageAnimatorFrameInfo* imageInfo);

/**
 * @brief Sets the playback duration of an image.
 *
 * @param imageInfo Pointer to the image frame information object.
 * @param duration Playback duration of an image, in ms.
 * @since 12
 */
void OH_ArkUI_ImageAnimatorFrameInfo_SetDuration(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t duration);
/**
 * @brief Obtains the playback duration of an image.
 *
 * @param imageInfo Pointer to the image frame information object.
 * @return Playback duration of the image, in milliseconds. If **imageInfo** is a null pointer, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetDuration(ArkUI_ImageAnimatorFrameInfo* imageInfo);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_ANIMATOR_H
/** @} */
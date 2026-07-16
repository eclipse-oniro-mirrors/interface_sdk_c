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
 * @brief 为NativeNode API提供ImageAnimator节点类型定义。
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
 * @brief 定义帧动画的播放状态。
 *
 * @since 12
 */
typedef enum {
    /**
     * 动画初始状态。
     * @since 12
     */
    ARKUI_ANIMATION_STATUS_INITIAL = 0,
    /**
     * 动画处于播放状态。
     * @since 12
     */
    ARKUI_ANIMATION_STATUS_RUNNING = 1,
    /**
     * 动画处于暂停状态。
     * @since 12
     */
    ARKUI_ANIMATION_STATUS_PAUSED = 2,
    /**
     * 动画处于停止状态。
     * @since 12
     */
    ARKUI_ANIMATION_STATUS_STOPPED = 3
} ArkUI_AnimationStatus;

/**
 * @brief 定义图片动画帧信息。
 *
 * @since 12
 */
typedef struct ArkUI_ImageAnimatorFrameInfo ArkUI_ImageAnimatorFrameInfo;

/**
 * @brief 使用图片路径创建帧图片信息，图片格式为svg、png和jpg。支持应用沙箱内的相对路径和绝对路径。
 *
 * @param src 图片路径，支持应用沙箱内的相对路径或绝对路径。
 * @return 帧图片对象指针。
 * @since 12
 */
ArkUI_ImageAnimatorFrameInfo* OH_ArkUI_ImageAnimatorFrameInfo_CreateFromString(char* src);

/**
 * @brief 使用{@link ArkUI_DrawableDescriptor}对象创建帧图片信息，图片格式为Resource和PixelMap。
 *
 * @param drawable 使用Resource或PixelMap创建的ArkUI_DrawableDescriptor对象指针。
 * @return 帧图片对象指针。
 * @since 12
 */
ArkUI_ImageAnimatorFrameInfo* OH_ArkUI_ImageAnimatorFrameInfo_CreateFromDrawableDescriptor(
    ArkUI_DrawableDescriptor* drawable);

/**
 * @brief 销毁帧图片对象指针。
 *
 * @param imageInfo 帧图片对象指针。
 * @since 12
 */
void OH_ArkUI_ImageAnimatorFrameInfo_Dispose(ArkUI_ImageAnimatorFrameInfo* imageInfo);

/**
 * @brief 设置图片宽度。
 *
 * @param imageInfo 帧图片对象指针。
 * @param width 图片宽度，单位为px。
 * @since 12
 */
void OH_ArkUI_ImageAnimatorFrameInfo_SetWidth(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t width);

/**
 * @brief 获取图片宽度。
 *
 * @param imageInfo 帧图片对象指针。
 * @return 图片宽度，单位为px，imageInfo为空指针时返回0。
 * @since 12
 */
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetWidth(ArkUI_ImageAnimatorFrameInfo* imageInfo);

/**
 * @brief 设置图片高度。
 *
 * @param imageInfo 帧图片对象指针。
 * @param height 图片高度，单位为px。
 * @since 12
 */
void OH_ArkUI_ImageAnimatorFrameInfo_SetHeight(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t height);

/**
 * @brief 获取图片高度。
 *
 * @param imageInfo 帧图片对象指针。
 * @return 图片高度，单位为px，imageInfo为空指针时返回0。
 * @since 12
 */
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetHeight(ArkUI_ImageAnimatorFrameInfo* imageInfo);
/**
 * @brief 设置图片相对于组件左上角的纵向坐标。
 *
 * @param imageInfo 帧图片对象指针。
 * @param top 图片相对于组件左上角的纵向坐标，单位为px。
 * @since 12
 */
void OH_ArkUI_ImageAnimatorFrameInfo_SetTop(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t top);

/**
 * @brief 获取图片相对于组件左上角的纵向坐标。
 *
 * @param imageInfo 帧图片对象指针。
 * @return 图片相对于组件左上角的纵向坐标，单位为px，imageInfo为空指针时返回0。
 * @since 12
 */
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetTop(ArkUI_ImageAnimatorFrameInfo* imageInfo);
/**
 * @brief 设置图片相对于组件左上角的横向坐标。
 *
 * @param imageInfo 帧图片对象指针。
 * @param left 图片相对于组件左上角的横向坐标，单位为px。
 * @since 12
 */
void OH_ArkUI_ImageAnimatorFrameInfo_SetLeft(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t left);

/**
 * @brief 获取图片相对于组件左上角的横向坐标。
 *
 * @param imageInfo 帧图片对象指针。
 * @return 图片相对于组件左上角的横向坐标，单位为px，imageInfo为空指针时返回0。
 * @since 12
 */
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetLeft(ArkUI_ImageAnimatorFrameInfo* imageInfo);

/**
 * @brief 设置图片的播放时长。
 *
 * @param imageInfo 帧图片对象指针。
 * @param duration 图片的播放时长，单位为ms。
 * @since 12
 */
void OH_ArkUI_ImageAnimatorFrameInfo_SetDuration(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t duration);
/**
 * @brief 获取图片的播放时长。
 *
 * @param imageInfo 帧图片对象指针。
 * @return 图片的播放时长，单位为毫秒，imageInfo为空指针时返回0。
 * @since 12
 */
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetDuration(ArkUI_ImageAnimatorFrameInfo* imageInfo);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_ANIMATOR_H
/** @} */
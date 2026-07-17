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
 * @brief 提供NativeDrawableDescriptor接口的类型定义。
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
 * @brief 定义 DrawableDescriptor 对象。
 *
 * @since 12
 */
typedef struct ArkUI_DrawableDescriptor ArkUI_DrawableDescriptor;

/**
 * @brief OH_PixelmapNative结构体是Native层封装的图像解码后无压缩的位图格式结构体，支持像素数据读写、透明度设置、缩放、平移、旋转、翻转、裁剪等操作，
 * 适用于需要在Native层对Pixelmap进行像素级处理与变换的场景。<br>创建OH_PixelmapNative使用{@link OH_PixelmapNative_CreatePixelmap}函数，当未指定源像素格式时，
 * 默认采用BGRA_8888格式处理数据。使用完毕后，必须调用{@link OH_PixelmapNative_Release}函数释放资源，两者需配对使用，否则会导致内存泄漏。<br>
 * OH_PixelmapNative结构体内容和操作方式如下：
 *
 * @since 12
 */
struct OH_PixelmapNative;

/**
 * @brief 定义OH_PixelmapNative对象指针类型。
 *
 * @since 12
 */
typedef struct OH_PixelmapNative* OH_PixelmapNativeHandle;

/**
 * @brief 定义ArkUI native组件实例对象。
 *
 * @since 22
 */
struct ArkUI_Node;

/**
 * @brief 定义ArkUI native组件实例对象指针。
 *
 * @since 22
 */
typedef struct ArkUI_Node* ArkUI_NodeHandle;

/**
 * @brief 定义DrawableDescriptor动图的播放状态。
 *
 * @since 22
 */
typedef enum {
    /**
     * 动画初始状态。
     *
     * @since 22
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_INITIAL = 0,
    /**
     * 动画处于播放状态。
     *
     * @since 22
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_RUNNING = 1,
    /**
     * 动画处于暂停状态。
     *
     * @since 22
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_PAUSED = 2,
    /**
     * 动画处于停止状态。
     *
     * @since 22
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_STOPPED = 3
} DrawableDescriptor_AnimationStatus;

/**
 * @brief 定义{@link DrawableDescriptor}动图的停止模式。
 *
 * @since 24
 */
typedef enum {
    /**
     * 动图停止时回到首帧。
     *
     * @since 24
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_FIRST_FRAME = 0,
    /**
     * 动图停止时停留在最后一帧。
     *
     * @since 24
     */
    DRAWABLE_DESCRIPTOR_ANIMATION_LAST_FRAME = 1
} DrawableDescriptor_AnimationStopMode;

/**
 * @brief 定义DrawableDescriptor动图控制器对象。
 *
 * @since 22
 */
typedef struct ArkUI_DrawableDescriptor_AnimationController ArkUI_DrawableDescriptor_AnimationController;

/**
 * @brief 使用PixelMap创建DrawableDescriptor对象。
 *
 * @param pixelMap {@link OH_PixelmapNative}对象指针。
 * @return 返回DrawableDescriptor对象指针。
 * @since 12
 */
ArkUI_DrawableDescriptor* OH_ArkUI_DrawableDescriptor_CreateFromPixelMap(OH_PixelmapNativeHandle pixelMap);

/**
 * @brief 使用PixelMap图片数组创建DrawableDescriptor对象。
 *
 * @param array PixelMap图片数组对象指针。
 * @param size PixelMap图片数组大小。
 * @return 返回DrawableDescriptor对象指针。
 * @since 12
 */
ArkUI_DrawableDescriptor* OH_ArkUI_DrawableDescriptor_CreateFromAnimatedPixelMap(
    OH_PixelmapNativeHandle* array, int32_t size);

/**
 * @brief 销毁DrawableDescriptor对象指针。
 *
 * @param drawableDescriptor DrawableDescriptor对象指针。
 * @since 12
 */
void OH_ArkUI_DrawableDescriptor_Dispose(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief 获取PixelMap图片对象指针。
 *
 * @param drawableDescriptor DrawableDescriptor对象指针。
 * @return {@link OH_PixelmapNative}对象指针。
 * @since 12
 */
OH_PixelmapNativeHandle OH_ArkUI_DrawableDescriptor_GetStaticPixelMap(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief 获取用于播放动画的PixelMap图片数组数据。
 *
 * @param drawableDescriptor DrawableDescriptor对象指针。
 * @return PixelMap图片数组指针。
 * @since 12
 */
OH_PixelmapNativeHandle* OH_ArkUI_DrawableDescriptor_GetAnimatedPixelMapArray(
    ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief 获取用于播放动画的PixelMap图片数组的大小。
 *
 * @param drawableDescriptor DrawableDescriptor对象指针。
 * @return PixelMap图片数组大小。
 * @since 12
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimatedPixelMapArraySize(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief 设置PixelMap图片数组播放总时长。
 *
 * @param drawableDescriptor DrawableDescriptor对象指针。
 * @param duration 播放总时长，单位ms。取值范围：[0, +∞)。传入负数时按0处理。
 * @since 12
 */
void OH_ArkUI_DrawableDescriptor_SetAnimationDuration(ArkUI_DrawableDescriptor* drawableDescriptor, int32_t duration);

/**
 * @brief 获取PixelMap图片数组播放总时长。
 *
 * @param drawableDescriptor DrawableDescriptor对象指针。
 * @return 播放总时长，单位ms。
 * @since 12
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationDuration(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief 设置PixelMap图片数组播放次数。
 *
 * @param drawableDescriptor DrawableDescriptor对象指针。
 * @param iteration Indicates the number of playback times.
 * @since 12
 */
void OH_ArkUI_DrawableDescriptor_SetAnimationIteration(
    ArkUI_DrawableDescriptor* drawableDescriptor, int32_t iteration);

/**
 * @brief 获取PixelMap图片数组播放次数。
 *
 * @param drawableDescriptor DrawableDescriptor对象指针。
 * @return 播放次数。
 * @since 12
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationIteration(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief 设置动图中的单帧播放时间。
 *
 * @param drawableDescriptor DrawableDescriptor对象指针。
 * @param durations 动图中的单帧播放时间数组，单位ms。
 *     不设置则按照总时间播放。设置的优先级高于{@link OH_ArkUI_DrawableDescriptor_SetAnimationDuration}，
 *     即同时设置了OH_ArkUI_DrawableDescriptor_SetAnimationDuration和OH_ArkUI_DrawableDescriptor_SetAnimationFrameDurations时，
 *     OH_ArkUI_DrawableDescriptor_SetAnimationDuration不生效。
 *     数组大小必须与PixelMap图片数组大小相同。
 *     每帧播放时间取值范围：[0, +∞)。默认值：均匀分配总时长。
 * @param size 数组大小。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 输入参数错误。</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_SetAnimationFrameDurations(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t* durations, size_t size);

/**
 * @brief 获取动图中的单帧播放时间。
 *
 * @param drawableDescriptor DrawableDescriptor对象指针。
 * @param durations 动图中的单帧播放时间数组。
 * @param size 数组大小。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 输入参数错误。</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationFrameDurations(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t* durations, size_t* size);

/**
 * @brief 设置动图是否自动播放。
 *
 * @param drawableDescriptor DrawableDescriptor对象指针。
 * @param autoPlay 是否自动播放。
 *     1表示自动播放，0表示不自动播放。
 *     默认值为1。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 输入参数错误。</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_SetAnimationAutoPlay(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t autoPlay);

/**
 * @brief 获取动图是否自动播放。
 *
 * @param drawableDescriptor DrawableDescriptor对象指针。
 * @param autoPlay 是否自动播放。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 输入参数错误。</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationAutoPlay(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t* autoPlay);

/**
 * @brief 设置动图的停止模式。
 *
 * @param drawableDescriptor {@link DrawableDescriptor}对象指针。
 * @param mode 动图停止模式。
 *     取值为{@link DrawableDescriptor_AnimationStopMode}枚举值，默认值为{@link DRAWABLE_DESCRIPTOR_ANIMATION_FIRST_FRAME}。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 输入参数错误。</li>
 *     </ul>
 * @since 24
 */
int32_t OH_ArkUI_DrawableDescriptor_SetAnimationStopMode(
    ArkUI_DrawableDescriptor* drawableDescriptor, DrawableDescriptor_AnimationStopMode mode);

/**
 * @brief 获取动图的停止模式。
 *
 * @param drawableDescriptor {@link DrawableDescriptor}对象指针。
 * @param mode 动图停止模式。
 *     取值含义请参考{@link DrawableDescriptor_AnimationStopMode}。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 输入参数错误。</li>
 *     </ul>
 * @since 24
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationStopMode(
    const ArkUI_DrawableDescriptor* drawableDescriptor, DrawableDescriptor_AnimationStopMode* mode);

/**
 * @brief 创建动图控制器。
 *
 * @param drawableDescriptor DrawableDescriptor对象指针。
 * @param node 组件节点指针。
 * @param controller DrawableDescriptor动图控制器对象指针。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 输入参数错误。</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_CreateAnimationController(ArkUI_DrawableDescriptor *drawableDescriptor,
    ArkUI_NodeHandle node, ArkUI_DrawableDescriptor_AnimationController** controller);

/**
 * @brief 销毁动图控制器。
 *
 * @param controller DrawableDescriptor动图控制器对象指针。
 * @since 22
 */
void OH_ArkUI_DrawableDescriptor_DisposeAnimationController(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief 从首帧开始播放。
 *
 * @param controller DrawableDescriptor动图控制器对象指针。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 输入参数错误。</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_StartAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief 停止动图播放并回到首帧。
 *
 * @param controller DrawableDescriptor动图控制器对象指针。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 输入参数错误。</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_StopAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief 从当前帧恢复动图播放。
 *
 * @param controller DrawableDescriptor动图控制器对象指针。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 输入参数错误。</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_ResumeAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief 暂停动图的播放，保持在当前帧。
 *
 * @param controller DrawableDescriptor动图控制器对象指针。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 输入参数错误。</li>
 *     </ul>
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_PauseAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief 获取动图的播放状态。
 *
 * @param controller DrawableDescriptor动图控制器对象指针。
 * @param status DrawableDescriptor动图的播放状态。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 输入参数错误。</li>
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
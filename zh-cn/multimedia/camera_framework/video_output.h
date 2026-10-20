/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup OH_Camera
 * @{
 *
 * @brief Provide the definition of the C interface for the camera module.
 *
 * @since 11
 * @version 1.0
 */

/**
 * @file video_output.h
 *
 * @brief 声明录像输出概念。
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 11
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_CAMERA_VIDEOOUTPUT_H
#define NATIVE_INCLUDE_CAMERA_VIDEOOUTPUT_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 录像输出对象。<br> 可以使用{@link OH_CameraManager_CreateVideoOutput}方法创建指针。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_VideoOutput Camera_VideoOutput;

/**
 * @brief 在{@link VideoOutput_Callbacks}中被调用的录像输出帧开始回调。
 * 
 * @param videoOutput 传递回调的录像输出实例。
 * @since 11
 */
typedef void (*OH_VideoOutput_OnFrameStart)(Camera_VideoOutput* videoOutput);

/**
 * @brief 在{@link VideoOutput_Callbacks}中被调用的录像输出帧结束回调。
 * 
 * @param videoOutput 传递回调的录像输出实例。
 * @param frameCount 回调传递的帧计数。
 * @since 11
 */
typedef void (*OH_VideoOutput_OnFrameEnd)(Camera_VideoOutput* videoOutput, int32_t frameCount);

/**
 * @brief 在{@link VideoOutput_Callbacks}中被调用的录像输出错误回调。
 * 
 * @param videoOutput 传递回调的录像输出实例。
 * @param errorCode 录像输出的错误码。
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 11
 */
typedef void (*OH_VideoOutput_OnError)(Camera_VideoOutput* videoOutput, Camera_ErrorCode errorCode);

/**
 * @brief 用于录像输出的回调。
 * 
 * @see OH_VideoOutput_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct VideoOutput_Callbacks {
    /**
     * 录像输出帧启动事件。
     */
    OH_VideoOutput_OnFrameStart onFrameStart;

    /**
     * 录像输出帧结束事件。
     */
    OH_VideoOutput_OnFrameEnd onFrameEnd;

    /**
     * 录像输出错误事件。
     */
    OH_VideoOutput_OnError onError;
} VideoOutput_Callbacks;

/**
 * @brief 注册录像输出更改事件回调。
 * 
 * @param videoOutput 录像输出实例。
 * @param callback 要注册的录像输出更改事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_VideoOutput_RegisterCallback(Camera_VideoOutput* videoOutput, VideoOutput_Callbacks* callback);

/**
 * @brief 注销录像输出更改事件回调。
 * 
 * @param videoOutput 录像输出实例。
 * @param callback 要注销的录像输出更改事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_VideoOutput_UnregisterCallback(Camera_VideoOutput* videoOutput, VideoOutput_Callbacks* callback);

/**
 * @brief 开始录像输出。
 * 
 * @param videoOutput 要启动的录像输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_VideoOutput_Start(Camera_VideoOutput* videoOutput);

/**
 * @brief 停止录像输出。
 * 
 * @param videoOutput 要停止的录像输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_VideoOutput_Stop(Camera_VideoOutput* videoOutput);

/**
 * @brief 释放录像输出实例。
 * 
 * @param videoOutput 要释放的录像输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_VideoOutput_Release(Camera_VideoOutput* videoOutput);

/**
 * @brief 获取当前视频输出配置文件。
 * 
 * @param videoOutput 传递当前视频输出配置文件的录像输出实例。
 * @param profile 如果方法调用成功，将记录当前的视频输出配置文件。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_VideoOutput_GetActiveProfile(Camera_VideoOutput* videoOutput, Camera_VideoProfile** profile);

/**
 * @brief 删除视频配置文件实例。
 * 
 * @param profile 要删除的视频配置文件实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_VideoOutput_DeleteProfile(Camera_VideoProfile* profile);

/**
 * @brief 判断当前视频输出是否支持镜像。
 *
 * @param videoOutput 传递当前视频输出的录像输出实例。
 * @param isSupported 当前视频输出是否支持镜像。true表示当前视频输出支持镜像，false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 15
 */
Camera_ErrorCode OH_VideoOutput_IsMirrorSupported(Camera_VideoOutput* videoOutput, bool* isSupported);

/**
 * @brief 打开/关闭当前视频输出镜像功能。
 *
 * @param videoOutput 传递当前视频输出的录像输出实例。
 * @param mirrorMode 设备是否开启镜像功能。true表示打开镜像功能，false表示关闭镜像功能。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 15
 */
Camera_ErrorCode OH_VideoOutput_EnableMirror(Camera_VideoOutput* videoOutput, bool mirrorMode);

/**
 * @brief 获取录像旋转角度。
 * 
 * @param videoOutput 传递当前视频输出的录像输出实例。
 * @param deviceDegree 设备目前相对于自然方向（充电口朝下）顺时针的旋转角度。
 * @param imageRotation 录像旋转角度的结果。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode  OH_VideoOutput_GetVideoRotation(Camera_VideoOutput* videoOutput, int deviceDegree,
    Camera_ImageRotation* imageRotation);

/**
 * @brief 获取录像旋转角度。
 * 
 * @param videoOutput 传递当前视频输出的录像输出实例。
 * @param imageRotation 录像旋转角度的结果。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 23
 */
Camera_ErrorCode  OH_VideoOutput_GetVideoRotationWithoutDeviceDegree(Camera_VideoOutput* videoOutput,
    Camera_ImageRotation* imageRotation);

/**
 * @brief 获取支持的视频输出帧率列表。
 * 
 * @param videoOutput 传递支持的视频输出帧率列表的录像输出实例。
 * @param frameRateRange 如果方法调用成功，将记录支持的视频输出帧率列表。
 * @param size 如果方法调用成功，将记录支持的视频输出帧率列表大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_VideoOutput_GetSupportedFrameRates(Camera_VideoOutput* videoOutput,
    Camera_FrameRateRange** frameRateRange, uint32_t* size);

/**
 * @brief 删除帧率列表。
 * 
 * @param videoOutput 录像输出实例。
 * @param frameRateRange 要删除的帧率列表。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_VideoOutput_DeleteFrameRates(Camera_VideoOutput* videoOutput,
    Camera_FrameRateRange* frameRateRange);

/**
 * @brief 设置视频输出帧率。
 * 
 * @param videoOutput 要设置帧率的录像输出实例。
 * @param minFps 设置的最小帧率。
 * @param maxFps 设置的最大帧率。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_VideoOutput_SetFrameRate(Camera_VideoOutput* videoOutput,
    int32_t minFps, int32_t maxFps);

/**
 * @brief 获取当前视频输出帧率。
 * 
 * @param videoOutput 传递当前视频输出帧率的录像输出实例。
 * @param frameRateRange 如果方法调用成功，将记录当前的视频输出帧率。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_VideoOutput_GetActiveFrameRate(Camera_VideoOutput* videoOutput,
    Camera_FrameRateRange* frameRateRange);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_VIDEOOUTPUT_H
/** @} */

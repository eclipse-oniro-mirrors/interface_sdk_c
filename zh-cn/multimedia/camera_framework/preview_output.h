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
 * @file preview_output.h
 *
 * @brief 声明预览输出概念。
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 11
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_CAMERA_PREVIEWOUTPUT_H
#define NATIVE_INCLUDE_CAMERA_PREVIEWOUTPUT_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 预览输出对象。<br> 可以使用{@link OH_CameraManager_CreatePreviewOutput}方法创建指针。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_PreviewOutput Camera_PreviewOutput;

/**
 * @brief 在{@link PreviewOutput_Callbacks}中被调用的预览输出帧开始回调。
 * 
 * @param previewOutput 传递回调的预览输出实例。
 * @since 11
 */
typedef void (*OH_PreviewOutput_OnFrameStart)(Camera_PreviewOutput* previewOutput);

/**
 * @brief 在{@link PreviewOutput_Callbacks}中被调用的预览输出帧结束回调。
 * 
 * @param previewOutput 传递回调的预览输出实例。
 * @param frameCount 回调传递的帧计数。
 * @since 11
 */
typedef void (*OH_PreviewOutput_OnFrameEnd)(Camera_PreviewOutput* previewOutput, int32_t frameCount);

/**
 * @brief 在{@link PreviewOutput_Callbacks}中被调用的预览输出帧错误回调。
 * 
 * @param previewOutput 传递回调的预览输出实例。
 * @param errorCode 预览输出的错误码。
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 11
 */
typedef void (*OH_PreviewOutput_OnError)(Camera_PreviewOutput* previewOutput, Camera_ErrorCode errorCode);

/**
 * @brief 用于预览输出的回调。
 * 
 * @see OH_PreviewOutput_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct PreviewOutput_Callbacks {
    /**
     * 预览输出帧开始事件。
     */
    OH_PreviewOutput_OnFrameStart onFrameStart;

    /**
     * 预览输出帧结束事件。
     */
    OH_PreviewOutput_OnFrameEnd onFrameEnd;

    /**
     * 预览输出错误事件。
     */
    OH_PreviewOutput_OnError onError;
} PreviewOutput_Callbacks;

/**
 * @brief 注册预览输出更改事件回调。
 * 
 * @param previewOutput 预览输出实例。
 * @param callback 要注册的预览输出更改事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_PreviewOutput_RegisterCallback(Camera_PreviewOutput* previewOutput,
    PreviewOutput_Callbacks* callback);

/**
 * @brief 注销预览输出更改事件回调。
 * 
 * @param previewOutput 预览输出实例。
 * @param callback 要注销的预览输出更改事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_PreviewOutput_UnregisterCallback(Camera_PreviewOutput* previewOutput,
    PreviewOutput_Callbacks* callback);

/**
 * @brief 开始预览输出。
 * 
 * @param previewOutput 要启动的预览输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_PreviewOutput_Start(Camera_PreviewOutput* previewOutput);

/**
 * @brief 停止预览输出。
 * 
 * @param previewOutput 要停止的预览输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_PreviewOutput_Stop(Camera_PreviewOutput* previewOutput);

/**
 * @brief 释放预览输出实例。
 * 
 * @param previewOutput 要释放的预览输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_PreviewOutput_Release(Camera_PreviewOutput* previewOutput);

/**
 * @brief 获取当前预览输出配置文件。
 * 
 * @param previewOutput 提供当前预览输出配置文件的预览输出实例。
 * @param profile 如果方法调用成功，将记录当前的预览输出配置文件。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_GetActiveProfile(Camera_PreviewOutput* previewOutput, Camera_Profile** profile);

/**
 * @brief 删除预览配置文件实例。
 * 
 * @param profile 要被删除的预览配置文件实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_DeleteProfile(Camera_Profile* profile);

/**
 * @brief 获取相机预览旋转角度。
 * 
 * @param previewOutput 用于获取预览旋转角度的预览输出实例。
 * @param displayRotation 当前显示的旋转角度。
 * @param imageRotation 预览旋转角度结果。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_GetPreviewRotation(Camera_PreviewOutput* previewOutput, int displayRotation,
    Camera_ImageRotation* imageRotation);

/**
 * @brief 获取相机预览旋转角度。
 * 
 * @param previewOutput 用于获取预览旋转角度的预览输出实例。
 * @param imageRotation 预览旋转角度结果。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 23
 */
Camera_ErrorCode OH_PreviewOutput_GetPreviewRotationWithoutDisplayRotation(Camera_PreviewOutput* previewOutput,
    Camera_ImageRotation* imageRotation);

/**
 * @brief 设置相机预览旋转角度。
 * 
 * @param previewOutput 用于设置预览旋转角度的预览输出实例。
 * @param previewRotation 预览的显示旋转角度。
 * @param isDisplayLocked Surface在屏幕旋转时是否锁定方向，未设置时默认取值为false，即不锁定方向。true表示锁定方向，false表示不锁定方向。详情请参考
 *     {@link SurfaceRotationOptions}。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_SetPreviewRotation(Camera_PreviewOutput* previewOutput,
    Camera_ImageRotation previewRotation, bool isDisplayLocked);

/**
 * @brief 获取支持的预览输出帧率列表。
 * 
 * @param previewOutput 传递支持的帧率列表的预览输出实例。
 * @param frameRateRange 如果方法调用成功，将记录支持的预览输出帧率列表。
 * @param size 如果方法调用成功，将记录支持的预览输出帧率列表大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_GetSupportedFrameRates(Camera_PreviewOutput* previewOutput,
    Camera_FrameRateRange** frameRateRange, uint32_t* size);

/**
 * @brief 删除帧率列表。
 * 
 * @param previewOutput 预览输出实例。
 * @param frameRateRange 要删除的帧率列表。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_DeleteFrameRates(Camera_PreviewOutput* previewOutput,
    Camera_FrameRateRange* frameRateRange);

/**
 * @brief 设置预览输出帧率。
 * 
 * @param previewOutput 要设置帧率的预览输出实例。
 * @param minFps 要设置的最小值。
 * @param maxFps 要设置的最大值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_SetFrameRate(Camera_PreviewOutput* previewOutput,
    int32_t minFps, int32_t maxFps);

/**
 * @brief 获取当前预览输出帧率。
 * 
 * @param previewOutput 传递当前预览输出帧率的预览输出实例。
 * @param frameRateRange 如果方法调用成功，则将记录当前的{@link Camera_FrameRateRange}。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_GetActiveFrameRate(Camera_PreviewOutput* previewOutput,
    Camera_FrameRateRange* frameRateRange);

/**
 * @brief 检查是否支持预览带宽压缩（指通过编码减少数据量，降低其在传输链路中的带宽占用）。
 * 
 * @param previewOutput 预览输出实例。
 * @param isSupported 是否支持带宽压缩的结果。true表示支持，false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 23
 */
Camera_ErrorCode OH_PreviewOutput_IsBandwidthCompressionSupported(Camera_PreviewOutput* previewOutput,
    bool* isSupported);
	
/**
 * @brief 使能预览带宽压缩。
 * <br>该接口只能在使用{@link OH_CaptureSession_CommitConfig()}接口之前调用，否则会影响预览流出流格式。
 * 
 * @param previewOutput 传递当前要预览带宽压缩使能的预览输出实例。
 * @param enabled 是否使能预览带宽压缩。true表示使能，false表示不使能。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED: 操作不允许。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：相机会话未配置。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 23
 */
Camera_ErrorCode OH_PreviewOutput_EnableBandwidthCompression(Camera_PreviewOutput* previewOutput, bool enabled);

/**
 * @brief 检查是否支持辅助监看功能。
 *
 * @param previewOutput 预览输出实例。
 * @return 是否支持辅助监看的结果。true表示支持，false表示不支持。
 * @since 26.0.0
 */
bool OH_PreviewOutput_IsLogViewAssistSupported(const Camera_PreviewOutput* previewOutput);

/**
 * @brief 使能辅助监看功能。
 * <br>该接口只能在使用{@link OH_CaptureSession_CommitConfig()}接口之后调用。
 *
 * @param previewOutput 指向当前要使能辅助监看的预览输出实例的指针。
 * @param enable 是否使能预览辅助监看。true表示使能，false表示不使能。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_ERROR_CAPABILITY_NOT_SUPPORTED：表示设备当前不支持该能力。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：相机会话未配置。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 26.0.0
 */
Camera_ErrorCode OH_PreviewOutput_SetLogViewAssistEnable(Camera_PreviewOutput* previewOutput, bool enable);

/**
 * @brief 配置延迟预览的Surface。
 *
 * @param previewOutput 添加surfaceId的预览输出实例。
 * @param surfaceId 用于创建Camera_PreviewOutput实例的surfaceId。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 24
 */
Camera_ErrorCode OH_PreviewOutput_AddDeferredSurface(const Camera_PreviewOutput* previewOutput, const char* surfaceId);
#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_PREVIEWOUTPUT_H
/** @} */

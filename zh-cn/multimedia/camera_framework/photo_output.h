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
 * @file photo_output.h
 *
 * @brief 声明拍照输出概念。
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 11
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_CAMERA_PHOTOOUTPUT_H
#define NATIVE_INCLUDE_CAMERA_PHOTOOUTPUT_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "camera.h"
#include "photo_native.h"
#include "multimedia/media_library/media_asset_base_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 拍照输出对象。<br> 可以使用{@link OH_CameraManager_CreatePhotoOutput}方法创建指针。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_PhotoOutput Camera_PhotoOutput;

/**
 * @brief 在{@link PhotoOutput_Callbacks}中被调用的拍照输出帧启动回调。
 * 
 * @param photoOutput 传递回调的拍照输出实例。
 * @since 11
 */
typedef void (*OH_PhotoOutput_OnFrameStart)(Camera_PhotoOutput* photoOutput);

/**
 * @brief 在{@link PhotoOutput_Callbacks}中被调用的拍照输出帧快门回调。
 * 
 * @param photoOutput 传递回调的拍照输出实例。
 * @param info 回调传递的帧快门回调信息。
 * @since 11
 */
typedef void (*OH_PhotoOutput_OnFrameShutter)(Camera_PhotoOutput* photoOutput, Camera_FrameShutterInfo* info);

/**
 * @brief 在{@link PhotoOutput_Callbacks}中被调用的拍照输出帧结束回调。
 * 
 * @param photoOutput 传递回调的拍照输出实例。
 * @param frameCount 回调传递的帧计数。
 * @since 11
 */
typedef void (*OH_PhotoOutput_OnFrameEnd)(Camera_PhotoOutput* photoOutput, int32_t frameCount);

/**
 * @brief 在{@link PhotoOutput_Callbacks}中被调用的拍照输出错误回调。
 * 
 * @param photoOutput 传递回调的拍照输出实例。
 * @param errorCode 拍照输出的错误码。
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 11
 */
typedef void (*OH_PhotoOutput_OnError)(Camera_PhotoOutput* photoOutput, Camera_ErrorCode errorCode);

/**
 * @brief 拍照结束回调。
 * 
 * @param photoOutput 传递回调的拍照输出实例。
 * @param frameCount 回调传递的帧数。
 * @since 12
 */
typedef void (*OH_PhotoOutput_CaptureEnd) (Camera_PhotoOutput* photoOutput, int32_t frameCount);

/**
 * @brief 拍照开始回调。
 * 
 * @param photoOutput 传递回调的拍照输出实例。
 * @param info the {@link Camera_CaptureStartInfo} which is delivered by the callback.
 * @since 12
 */
typedef void (*OH_PhotoOutput_CaptureStartWithInfo) (Camera_PhotoOutput* photoOutput, Camera_CaptureStartInfo* Info);

/**
 * @brief 拍照曝光结束回调。
 * 
 * @param photoOutput 传递回调的拍照输出实例。
 * @param info the {@link Camera_CaptureStartInfo} which is delivered by the callback.
 * @since 12
 */
typedef void (*OH_PhotoOutput_OnFrameShutterEnd) (Camera_PhotoOutput* photoOutput, Camera_FrameShutterInfo* Info);

/**
 * @brief 拍照准备就绪回调。收到回调后，可以继续进行下一次拍照。
 * 
 * @param photoOutput 传递回调的拍照输出实例。
 * @since 12
 */
typedef void (*OH_PhotoOutput_CaptureReady) (Camera_PhotoOutput* photoOutput);

/**
 * @brief 预计拍照时间回调。
 * 
 * @param photoOutput 传递回调的拍照输出实例。
 * @param duration 回调传递的预计拍照时间，单位毫秒。
 * @since 12
 */
typedef void (*OH_PhotoOutput_EstimatedCaptureDuration) (Camera_PhotoOutput* photoOutput, int64_t duration);

/**
 * @brief 照片输出可用高分辨率图像回调。
 * 
 * @param photoOutput 传递回调的拍照输出实例。
 * @param photo 回调传递的OH_PhotoNative。
 * @since 12
 */
typedef void (*OH_PhotoOutput_PhotoAvailable)(Camera_PhotoOutput* photoOutput, OH_PhotoNative* photo);

/**
 * @brief 输出照片资源可用回调。
 * 
 * @param photoOutput 传递回调的拍照输出实例。
 * @param photoAsset 回调传递的媒体资源。
 * @since 12
 */
typedef void (*OH_PhotoOutput_PhotoAssetAvailable)(Camera_PhotoOutput* photoOutput, OH_MediaAsset* photoAsset);

/**
 * @brief 拍照输出的回调。
 * 
 * @see OH_PhotoOutput_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct PhotoOutput_Callbacks {
    /**
     * 拍照输出帧启动事件。
     */
    OH_PhotoOutput_OnFrameStart onFrameStart;

    /**
     * 拍照输出帧快门事件。
     */
    OH_PhotoOutput_OnFrameShutter onFrameShutter;

    /**
     * 拍照输出帧结束事件。
     */
    OH_PhotoOutput_OnFrameEnd onFrameEnd;

    /**
     * 拍照输出错误事件。
     */
    OH_PhotoOutput_OnError onError;
} PhotoOutput_Callbacks;

/**
 * @brief 注册拍照输出更改事件回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注册的拍照输出更改事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_PhotoOutput_RegisterCallback(Camera_PhotoOutput* photoOutput, PhotoOutput_Callbacks* callback);

/**
 * @brief 注销拍照输出更改事件回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注销的拍照输出更改事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterCallback(Camera_PhotoOutput* photoOutput, PhotoOutput_Callbacks* callback);

/**
 * @brief 注册拍照开始事件回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注册的拍照开始事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterCaptureStartWithInfoCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_CaptureStartWithInfo callback);

/**
 * @brief 获取照片旋转角度。
 * 
 * @param photoOutput 用于获取照片旋转角度的拍照输出实例。
 * @param deviceDegree 当前设备旋转角度。
 * @param imageRotation 照片旋转角度的结果。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_GetPhotoRotation(Camera_PhotoOutput* photoOutput, int deviceDegree,
    Camera_ImageRotation* imageRotation);

/**
 * @brief 获取照片旋转角度。
 * 
 * @param photoOutput 用于获取照片旋转角度的拍照输出实例。
 * @param imageRotation 照片旋转角度的结果。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 23
 */
Camera_ErrorCode OH_PhotoOutput_GetPhotoRotationWithoutDeviceDegree(Camera_PhotoOutput* photoOutput,
    Camera_ImageRotation* imageRotation);

/**
 * @brief 注销拍照开始事件回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注销的拍照开始事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterCaptureStartWithInfoCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_CaptureStartWithInfo callback);

/**
 * @brief 注册拍照结束事件回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注册的拍照结束事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterCaptureEndCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_CaptureEnd callback);

/**
 * @brief 注销拍照结束事件回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注销的拍照结束事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterCaptureEndCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_CaptureEnd callback);

/**
 * @brief 注册拍照曝光结束事件回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注册的拍照曝光结束事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterFrameShutterEndCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_OnFrameShutterEnd callback);

/**
 * @brief 注销拍照曝光结束事件回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注销的拍照曝光结束事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterFrameShutterEndCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_OnFrameShutterEnd callback);

/**
 * @brief 注册拍照就绪事件回调。收到回调后，可以继续进行下一次拍照。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注册的拍照就绪事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterCaptureReadyCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_CaptureReady callback);

/**
 * @brief 注销拍照就绪事件回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注销的拍照就绪事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterCaptureReadyCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_CaptureReady callback);

/**
 * @brief 注册预计拍照时间事件回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注册的预计拍照时间事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterEstimatedCaptureDurationCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_EstimatedCaptureDuration callback);

/**
 * @brief 注销预计拍照时间事件回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注销的预计拍照时间事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterEstimatedCaptureDurationCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_EstimatedCaptureDuration callback);

/**
 * @brief 注册输出照片可用回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注册的输出照片可用回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterPhotoAvailableCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_PhotoAvailable callback);

/**
 * @brief 注销输出照片可用回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注销的输出照片可用回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterPhotoAvailableCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_PhotoAvailable callback);

/**
 * @brief 注册输出照片资源可用回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注册的输出照片资源可用回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterPhotoAssetAvailableCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_PhotoAssetAvailable callback);

/**
 * @brief 注销输出照片资源可用回调。
 * 
 * @param photoOutput 拍照输出实例。
 * @param callback 要注销的输出照片资源可用回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterPhotoAssetAvailableCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_PhotoAssetAvailable callback);

/**
 * @brief 拍摄照片。
 * <br>必须在{@link OH_PreviewOutput_Release}之前调用，否则会导致无法拍照。
 * 
 * @param photoOutput 用于捕获拍照的拍照输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_RUNNING：捕获会话未运行。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_PhotoOutput_Capture(Camera_PhotoOutput* photoOutput);

/**
 * @brief 使用捕获设置捕获拍照。
 * 
 * @param photoOutput 用于捕获拍照的拍照输出实例。
 * @param setting 用于捕获拍照的{@link Camera_PhotoCaptureSetting}。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_RUNNING：捕获会话未运行。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_PhotoOutput_Capture_WithCaptureSetting(Camera_PhotoOutput* photoOutput,
    Camera_PhotoCaptureSetting setting);

/**
 * @brief 释放拍照输出。
 * 
 * @param photoOutput 要释放的拍照输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_PhotoOutput_Release(Camera_PhotoOutput* photoOutput);

/**
 * @brief 检查是否支持镜像拍照。
 * 
 * @param photoOutput 拍照输出实例，用于检查是否支持镜像。
 * @param isSupported 是否支持镜像的结果。true表示支持镜像，false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_PhotoOutput_IsMirrorSupported(Camera_PhotoOutput* photoOutput, bool* isSupported);

/**
 * @brief 是否启用动态照片镜像拍照。
 * 
 * @param photoOutput 拍照输出实例，用于确认是否启用镜像拍照。
 * @param enabled 是否启用动态照片镜像拍照的结果，true为开启动态照片镜像拍照，false为关闭动态照片镜像拍照。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 13
 */
Camera_ErrorCode OH_PhotoOutput_EnableMirror(Camera_PhotoOutput* photoOutput, bool enabled);

/**
 * @brief 获取当前照片输出配置文件。
 * 
 * @param photoOutput 传递当前配置文件的拍照输出实例。
 * @param profile 如果方法调用成功，将记录照片输出配置文件。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_GetActiveProfile(Camera_PhotoOutput* photoOutput, Camera_Profile** profile);

/**
 * @brief 删除照片配置文件实例。
 * 
 * @param profile 要被删除的照片配置文件实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_DeleteProfile(Camera_Profile* profile);

/**
 * @brief 检查是否支持动态照片。
 * 
 * @param photoOutput 用于检查是否支持动态照片的拍照输出实例。
 * @param isSupported 是否支持动态照片的结果。true表示支持动态照片，false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_IsMovingPhotoSupported(Camera_PhotoOutput* photoOutput, bool* isSupported);

/**
 * @brief 是否启用动态照片。
 * 
 * @param photoOutput 用于启用或禁用动态照片的拍照输出实例。
 * @param enabled 是否启用动态照片。true表示启用动态照片，false表示不启用。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_EnableMovingPhoto(Camera_PhotoOutput* photoOutput, bool enabled);

/**
 * @brief 检查是否支持指定的拍照画质优先策略。
 * 
 * @param photoOutput 用于获取是否支持拍照画质优先策略的拍照输出实例。
 * @param qualityPrioritization 要检查的拍照画质优先策略。
 * @param isSupported 是否支持指定的拍照画质优先策略。true表示支持，false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 21
 */
Camera_ErrorCode OH_PhotoOutput_IsPhotoQualityPrioritizationSupported(Camera_PhotoOutput* photoOutput, 
    Camera_PhotoQualityPrioritization qualityPrioritization, bool* isSupported);

/**
 * @brief 设置拍照画质优先策略。
 * 
 * @param photoOutput 用于设置拍照画质优先策略的拍照输出实例。
 * @param qualityPrioritization 要设置的拍照画质优先策略。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 21
 */
Camera_ErrorCode OH_PhotoOutput_SetPhotoQualityPrioritization(Camera_PhotoOutput* photoOutput,
    Camera_PhotoQualityPrioritization qualityPrioritization);

/**
 * @brief 扩展拍照设置对象（提供镜像、旋转等基础拍照配置，支持连续调节图片压缩质量）。
 *
 * @since 26.0.0
 * @version 1.0
 */
typedef struct OH_Camera_PhotoCaptureSettingExt OH_Camera_PhotoCaptureSettingExt;
 
/**
 * @brief 使用扩展拍照设置执行拍照操作。
 *
 * @param photoOutput 拍照输出实例。
 * @param setting 指向扩展拍照设置实例的指针。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_RUNNING：捕获会话未运行。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 26.0.0
 */
Camera_ErrorCode OH_PhotoOutput_Capture_WithCaptureSettingExt(Camera_PhotoOutput* photoOutput,
    OH_Camera_PhotoCaptureSettingExt* setting);
 
/**
 * @brief 创建拍照扩展设置实例。
 *
 * @param photoOutput photoOutput 拍照输出实例。
 * @param setting 如果方法调用成功，setting指向创建的OH_Camera_PhotoCaptureSettingExt实例指针的指针。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 26.0.0
 */
Camera_ErrorCode OH_PhotoOutput_CreatePhotoCaptureSettingExt(Camera_PhotoOutput* photoOutput,
    OH_Camera_PhotoCaptureSettingExt** setting);
 
/**
 * @brief 拍照扩展设置中的图片压缩质量。
 *
 * @param photoCaptureSettingExt 指向扩展拍照设置实例的指针。
 * @param compressionQuality 图片压缩质量，取值范围（1, 100），取值越大生成的图片质量越高，1 为最低质量，100 为最高质量。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 26.0.0
 */
Camera_ErrorCode OH_PhotoCaptureSettingExt_SetCompressionQuality(
    OH_Camera_PhotoCaptureSettingExt* photoCaptureSettingExt, uint8_t compressionQuality);
 
/**
 * @brief 拍照扩展设置中的图像旋转角度。
 *
 * @param photoCaptureSettingExt 指向扩展拍照设置实例的指针。
 * @param rotation 图像旋转角度，定义在{@link Camera_ImageRotation}枚举中。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 26.0.0
 */
Camera_ErrorCode OH_PhotoCaptureSettingExt_SetImageRotation(OH_Camera_PhotoCaptureSettingExt* photoCaptureSettingExt,
    Camera_ImageRotation rotation);
 
/**
 * @brief 拍照扩展设置中的镜像效果。
 *
 * @param photoCaptureSettingExt 指向扩展拍照设置实例的指针。
 * @param mirror 镜像效果开关。true表示启用，false表示禁用。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 26.0.0
 */
Camera_ErrorCode OH_PhotoCaptureSettingExt_SetMirror(OH_Camera_PhotoCaptureSettingExt* photoCaptureSettingExt,
    bool mirror);
 
/**
 * @brief 销毁拍照扩展设置对象的实例。
 *
 * @param setting 指向扩展拍照设置实例的指针。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 26.0.0
 */
Camera_ErrorCode OH_PhotoOutput_DestroyPhotoCaptureSettingExt(OH_Camera_PhotoCaptureSettingExt* setting);
 
 /**
 * @brief 拍照扩展设置中的图片位置信息。
 *
 * @param photoCaptureSettingExt 指向扩展拍照设置实例的指针。
 * @param location 图片位置，定义在{@link Camera_Location}。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 26.0.0
 */
Camera_ErrorCode OH_PhotoCaptureSettingExt_SetLocation(OH_Camera_PhotoCaptureSettingExt* photoCaptureSettingExt,
    Camera_Location location);
 
/**
* @brief 是否启用自动扩展增益图（Gainmap）的输出。
*
* @param photoOutput 用于启用或禁用自动扩展增益图（Gainmap）的输出的拍照输出实例。
* @param enabled 是否启用自动扩展增益图（Gainmap）的输出的结果。true表示启用，false表示不启用。
* @return <ul>
*     <br><li>CAMERA_OK：方法调用成功。</li>
*     <br><li>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。</li>
*     <br><li>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。</li>
*     <br><li>CAMERA_SESSION_NOT_CONFIG：会话未配置。</li>
*     <br><li>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。</li>
*     <br></ul>
* @since 26.0.0
*/
Camera_ErrorCode OH_PhotoOutput_EnableAutoExtendedGainmapDelivery(Camera_PhotoOutput* photoOutput,
    bool enabled);
 
/**
 * @brief 检查是否支持自动扩展增益图（Gainmap）的输出。
 *
 * @param photoOutput 用于检查是否支持自动扩展增益图（Gainmap）的输出的拍照输出实例。
 * @return 是否支持自动扩展增益图（Gainmap）的输出的结果。true表示支持，false表示不支持。
 * @since 26.0.0
 */
bool OH_PhotoOutput_IsAutoExtendedGainmapDeliverySupported(const Camera_PhotoOutput* photoOutput);
#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_PHOTOOUTPUT_H
/** @} */

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
 * @file capture_session.h
 *
 * @brief 声明捕获会话概念。
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 11
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_CAMERA_CAMERA_SESSION_H
#define NATIVE_INCLUDE_CAMERA_CAMERA_SESSION_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "camera.h"
#include "camera_input.h"
#include "preview_output.h"
#include "photo_output.h"
#include "video_output.h"
#include "metadata_output.h"
#include "native_buffer/native_buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 捕获会话对象。<br> 可以使用{@link OH_CameraManager_CreateCaptureSession}方法创建指针。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_CaptureSession Camera_CaptureSession;

/**
 * @brief 在{@link CaptureSession_Callbacks}中被调用的捕获会话焦点状态回调。
 * 
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param focusState 回调传递的会话焦点状态。
 * @since 11
 */
typedef void (*OH_CaptureSession_OnFocusStateChange)(Camera_CaptureSession* session, Camera_FocusState focusState);

/**
 * @brief 在{@link CaptureSession_Callbacks}中被调用的捕获会话错误回调。
 * 
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param errorCode 捕获会话的错误码。
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 11
 */
typedef void (*OH_CaptureSession_OnError)(Camera_CaptureSession* session, Camera_ErrorCode errorCode);

/**
 * @brief 拍照会话平滑变焦信息回调，触发平滑变焦后该回调会返回。
 * 
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param smoothZoomInfo 回调传递的平滑变焦参数信息。
 * @since 12
 */
typedef void (*OH_CaptureSession_OnSmoothZoomInfo)(Camera_CaptureSession* session,
    Camera_SmoothZoomInfo* smoothZoomInfo);

/**
 * @brief 捕获会话设备切换状态回调。
 *
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param autoDeviceSwitchStatusInfo 回调传递的设备切换状态信息。
 * @since 13
 */
typedef void (*OH_CaptureSession_OnAutoDeviceSwitchStatusChange)(Camera_CaptureSession* session,
    Camera_AutoDeviceSwitchStatusInfo* autoDeviceSwitchStatusInfo);

/**
 * @brief 捕获系统压力状态变化回调。
 * 
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param systemPressureLevel 回调传递的系统压力等级。
 * @since 20
 */
typedef void (*OH_CaptureSession_OnSystemPressureLevelChange)(Camera_CaptureSession* session,
    Camera_SystemPressureLevel systemPressureLevel);

/**
 * @brief 捕获会话的回调。
 * 
 * @see OH_CaptureSession_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct CaptureSession_Callbacks {
    /**
     * 捕获会话焦点状态更改事件。
     */
    OH_CaptureSession_OnFocusStateChange onFocusStateChange;

    /**
     * 捕获会话错误事件。
     */
    OH_CaptureSession_OnError onError;
} CaptureSession_Callbacks;

/**
 * @brief 注册捕获会话事件回调。
 * 
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param callback 要注册的捕获会话事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_RegisterCallback(Camera_CaptureSession* session,
    CaptureSession_Callbacks* callback);

/**
 * @brief 注销捕获会话事件回调。
 * 
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param callback 要注销的捕获会话事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_UnregisterCallback(Camera_CaptureSession* session,
    CaptureSession_Callbacks* callback);

/**
 * @brief 注册平滑变焦信息事件回调。
 * 
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param smoothZoomInfoCallback 要注册的平滑变焦信息事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_RegisterSmoothZoomInfoCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnSmoothZoomInfo smoothZoomInfoCallback);

/**
 * @brief 注销平滑变焦信息事件回调。
 * 
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param smoothZoomInfoCallback 要注销的平滑变焦信息事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_UnregisterSmoothZoomInfoCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnSmoothZoomInfo smoothZoomInfoCallback);

/**
 * @brief 设置会话模式。
 * <br>此接口不能在{@link OH_CaptureSession_BeginConfig}之后使用。
 * <br>建议在使用{@link OH_CameraManager_CreateCaptureSession}后立即使用此接口。
 * 
 * @param session Camera_CaptureSession实例。
 * @param sceneMode 相机模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 *     <br>CAMERA_SESSION_CONFIG_LOCKED：会话配置已锁定。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_SetSessionMode(Camera_CaptureSession* session, Camera_SceneMode sceneMode);

/**
 * @brief 把其中一条PreviewOutput标记成安全输出。
 * 
 * @param session Camera_CaptureSession实例。
 * @param previewOutput 要标记为安全输出的Camera_PreviewOutput。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 *     <br>CAMERA_SESSION_CONFIG_LOCKED：会话配置已锁定。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_AddSecureOutput(Camera_CaptureSession* session, Camera_PreviewOutput* previewOutput);

/**
 * @brief 开始捕获会话配置。
 * 
 * @param session Camera_CaptureSession实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_CONFIG_LOCKED：会话配置已锁定。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_BeginConfig(Camera_CaptureSession* session);

/**
 * @brief 提交捕获会话配置。
 * 
 * @param session Camera_CaptureSession实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_CommitConfig(Camera_CaptureSession* session);

/**
 * @brief 添加相机输入。
 * 
 * @param session Camera_CaptureSession实例。
 * @param cameraInput 要添加的相机输入实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_AddInput(Camera_CaptureSession* session, Camera_Input* cameraInput);

/**
 * @brief 删除相机输入。
 * 
 * @param session Camera_CaptureSession实例。
 * @param cameraInput 要删除的相机输入实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_RemoveInput(Camera_CaptureSession* session, Camera_Input* cameraInput);

/**
 * @brief 添加预览输出。
 * 
 * @param session Camera_CaptureSession实例。
 * @param previewOutput 要添加的预览输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_AddPreviewOutput(Camera_CaptureSession* session,
    Camera_PreviewOutput* previewOutput);

/**
 * @brief 删除预览输出。
 * 
 * @param session Camera_CaptureSession实例。
 * @param previewOutput 要删除的预览输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_RemovePreviewOutput(Camera_CaptureSession* session,
    Camera_PreviewOutput* previewOutput);

/**
 * @brief 添加拍照输出。
 * 
 * @param session Camera_CaptureSession实例。
 * @param photoOutput 要添加的拍照输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_AddPhotoOutput(Camera_CaptureSession* session, Camera_PhotoOutput* photoOutput);

/**
 * @brief 删除拍照输出。
 * 
 * @param session Camera_CaptureSession实例。
 * @param photoOutput 要删除的拍照输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_RemovePhotoOutput(Camera_CaptureSession* session, Camera_PhotoOutput* photoOutput);

/**
 * @brief 添加录像输出。
 * 
 * @param session Camera_CaptureSession实例。
 * @param videoOutput 要添加的录像输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_AddVideoOutput(Camera_CaptureSession* session, Camera_VideoOutput* videoOutput);

/**
 * @brief 删除录像输出。
 * 
 * @param session Camera_CaptureSession实例。
 * @param videoOutput 要删除的录像输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_RemoveVideoOutput(Camera_CaptureSession* session, Camera_VideoOutput* videoOutput);

/**
 * @brief 添加元数据输出。
 * 
 * @param session Camera_CaptureSession实例。
 * @param metadataOutput 要添加的元数据输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_AddMetadataOutput(Camera_CaptureSession* session,
    Camera_MetadataOutput* metadataOutput);

/**
 * @brief 删除元数据输出。
 * 
 * @param session Camera_CaptureSession实例。
 * @param metadataOutput 要删除的元数据输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_RemoveMetadataOutput(Camera_CaptureSession* session,
    Camera_MetadataOutput* metadataOutput);

/**
 * @brief 启动捕获会话。
 * 
 * @param session 要启动的Camera_CaptureSession实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_Start(Camera_CaptureSession* session);

/**
 * @brief 停止捕获会话。
 * 
 * @param session 要停止的Camera_CaptureSession实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_Stop(Camera_CaptureSession* session);

/**
 * @brief 释放捕获会话。
 * 
 * @param session 要释放的Camera_CaptureSession实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_Release(Camera_CaptureSession* session);

/**
 * @brief 检查设备是否有闪光灯。
 * 
 * @param session Camera_CaptureSession实例。
 * @param hasFlash 是否支持闪光灯的结果。返回true表示支持闪光灯，返回false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_HasFlash(Camera_CaptureSession* session, bool* hasFlash);

/**
 * @brief 检查是否支持指定的闪光灯模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param flashMode 要检查的闪光灯模式。
 * @param isSupported 是否支持闪光灯模式的结果。返回true表示支持闪光灯模式，返回false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_IsFlashModeSupported(Camera_CaptureSession* session,
    Camera_FlashMode flashMode, bool* isSupported);

/**
 * @brief 获取当前闪光灯模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param flashMode 当前闪光灯模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetFlashMode(Camera_CaptureSession* session, Camera_FlashMode* flashMode);

/**
 * @brief 设置闪光灯模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param flashMode 要设置的闪光灯模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetFlashMode(Camera_CaptureSession* session, Camera_FlashMode flashMode);

/**
 * @brief 捕获会话闪光灯状态变更回调。
 *
 * @param session 传递回调的Camera_CaptureSession指针。
 * @param flashState 回调传递的闪光灯状态。
 * @since 24
 */
typedef void (*OH_CaptureSession_OnFlashStateChange)(const Camera_CaptureSession* session, OH_Camera_FlashState flashState);

/**
 * @brief 注册闪光灯状态变更事件回调。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param flashStateChange 待注册的闪光灯状态变更回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_RegisterFlashStateChangeCallback(const Camera_CaptureSession* session,
    OH_CaptureSession_OnFlashStateChange flashStateChange);

/**
 * @brief 注销闪光灯状态变更回调。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param flashStateChange 待注销的闪光灯状态变更回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_UnregisterFlashStateChangeCallback(const Camera_CaptureSession* session,
    OH_CaptureSession_OnFlashStateChange flashStateChange);

/**
 * @brief 定义曝光状态变更时的回调函数。
 *
 * @param context 指向自定义上下文的指针。
 * @param exposureState 当前曝光状态。
 * @since 26.0.0
 */
typedef void (*OH_CaptureSession_OnExposureStateChange)(void* context, OH_Camera_ExposureState exposureState);

/**
 * @brief 注册曝光状态变化的回调。注册此回调后，当捕获会话中的曝光状态发生变化时，将调用该回调。
 *
 * @param session Camera_CaptureSession实例。
 * @param context 指向自定义上下文的指针。
 * @param callback 表示曝光状态改变的回调函数。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型不正确。
 * @since 26.0.0
 */
Camera_ErrorCode OH_CaptureSession_RegisterExposureStateChangeCallback(
    const Camera_CaptureSession* session, void* context, OH_CaptureSession_OnExposureStateChange callback);

/**
 * @brief 注销曝光状态变更时的回调函数。
 *
 * @param session Camera_CaptureSession实例。
 * @param context 指向注册回调时指定的自定义上下文的指针。
 * @param callback 表示曝光状态改变的回调函数。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型不正确。
 * @since 26.0.0
 */
Camera_ErrorCode OH_CaptureSession_UnregisterExposureStateChangeCallback(
    const Camera_CaptureSession* session, void* context, OH_CaptureSession_OnExposureStateChange callback);

/**
 * @brief 检查是否支持指定的曝光模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param exposureMode 要检查的曝光模式。
 * @param isSupported 是否支持曝光模式的结果。返回true表示支持曝光模式，返回false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_IsExposureModeSupported(Camera_CaptureSession* session,
    Camera_ExposureMode exposureMode, bool* isSupported);

/**
 * @brief 获取当前曝光模式。如果未通过{@link OH_CaptureSession_SetExposureMode}接口进行设置，则直接调用该接口查询当前曝光模式，会返回无效值。
 * 
 * @param session Camera_CaptureSession实例。
 * @param exposureMode 当前的曝光模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetExposureMode(Camera_CaptureSession* session, Camera_ExposureMode* exposureMode);

/**
 * @brief 检查是否支持指定的白平衡模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param whiteBalanceMode 指定的白平衡模式。
 * @param isSupported 用于返回是否支持指定的白平衡模式，支持返回true，否则返回false。
 * @return CAMERA_OK：函数调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或者参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：相机会话未配置。
 * @since 20
 */

Camera_ErrorCode OH_CaptureSession_IsWhiteBalanceModeSupported(Camera_CaptureSession* session,
    Camera_WhiteBalanceMode whiteBalanceMode, bool* isSupported);

/**
 * @brief 获取当前的白平衡模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param whiteBalanceMode 白平衡模式。
 * @return CAMERA_OK：函数调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或者参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：相机会话未配置。
 * @since 20
 */


Camera_ErrorCode OH_CaptureSession_GetWhiteBalanceMode(Camera_CaptureSession* session, Camera_WhiteBalanceMode* whiteBalanceMode);

/**
 * @brief 设置白平衡模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param whiteBalanceMode 白平衡模式。
 * @return CAMERA_OK：设置成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或者参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：相机会话未配置。
 * @since 20
 */


Camera_ErrorCode OH_CaptureSession_SetWhiteBalanceMode(Camera_CaptureSession* session, Camera_WhiteBalanceMode whiteBalanceMode);

/**
 * @brief 获取支持配置的白平衡色温范围。
 * 
 * @param session Camera_CaptureSession实例。
 * @param minColorTemperature 支持的最小色温值，单位为K。
 * @param maxColorTemperature 支持的最大色温值，单位为K。
 * @return CAMERA_OK：函数调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或者参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：相机会话未配置。
 * @since 20
 */


Camera_ErrorCode OH_CaptureSession_GetWhiteBalanceRange(Camera_CaptureSession* session, int32_t *minColorTemperature, int32_t *maxColorTemperature);

/**
 * @brief 获取当前白平衡色温值。
 * 
 * @param session Camera_CaptureSession实例。
 * @param colorTemperature 色温值，单位为K。
 * @return CAMERA_OK：函数调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或者参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：相机会话未配置。
 * @since 20
 */


Camera_ErrorCode OH_CaptureSession_GetWhiteBalance(Camera_CaptureSession* session, int32_t *colorTemperature);


/**
 * @brief 设置白平衡的色温。
 * <br>设置前，建议通过{@link OH_CaptureSession_GetWhiteBalanceRange}获取支持配置的白平衡色温范围。
 * 
 * @param session Camera_CaptureSession实例。
 * @param colorTemperature 色温值，单位为K。
 * @return CAMERA_OK：设置成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或者参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：相机会话未配置。
 * @since 20
 */


Camera_ErrorCode OH_CaptureSession_SetWhiteBalance(Camera_CaptureSession* session, int32_t colorTemperature);

/**
 * @brief 获取支持配置的白平衡色调调节范围。
 *
 * @param session Camera_CaptureSession实例。
 * @param minColorTint 指向最小色调值的指针。
 * @param maxColorTint 指向最大色调值的指针。
 *     @return
 *     <br>CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：当调用该方法时，捕获会话未配置。
 * @since 26.0.0
 */
Camera_ErrorCode OH_CaptureSession_GetColorTintRange(const Camera_CaptureSession* session,
    int32_t *minColorTint, int32_t *maxColorTint);

/**
 * @brief 获取当前白平衡的色调调节值。
 *
 * @param session Camera_CaptureSession实例。
 * @param colorTint 指向色调值的指针。
 *     @return
 *     <br>CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：当调用该方法时，捕获会话未配置。
 * @since 26.0.0
 */
Camera_ErrorCode OH_CaptureSession_GetColorTint(const Camera_CaptureSession* session, int32_t *colorTint);

/**
 * @brief 设置白平衡的色调调节值。设置前，建议通过{@link OH_CaptureSession_GetColorTintRange}获取支持配置的白平衡色调调节范围。
 *
 * @param session Camera_CaptureSession实例。
 * @param colorTint 色调调节值。
 *     @return
 *     <br>CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：当调用该方法时，捕获会话未配置。
 * @since 26.0.0
 */
Camera_ErrorCode OH_CaptureSession_SetColorTint(Camera_CaptureSession* session, int32_t colorTint);

/**
 * @brief 设置曝光模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param exposureMode 要设置的曝光模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetExposureMode(Camera_CaptureSession* session, Camera_ExposureMode exposureMode);

/**
 * @brief 获取当前测量点。
 * 
 * @param session Camera_CaptureSession实例。
 * @param point 当前测量点。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetMeteringPoint(Camera_CaptureSession* session, Camera_Point* point);

/**
 * @brief 设置计量区域的中心点。
 * 
 * @param session Camera_CaptureSession实例。
 * @param point 要设置的测量点。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetMeteringPoint(Camera_CaptureSession* session, Camera_Point point);

/**
 * @brief 查询指定曝光测光模式是否支持。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param exposureMeteringMode 待检查的曝光测光模式。
 * @param isSupported 输出参数，返回曝光模式是否支持的结果。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_IsExposureMeteringModeSupported(const Camera_CaptureSession* session,
    OH_Camera_ExposureMeteringMode exposureMeteringMode, bool* isSupported);

/**
 * @brief 获取当前曝光测光模式。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param exposureMeteringMode 输出参数，返回当前曝光测光模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许，会话或相机状态异常。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetExposureMeteringMode(const Camera_CaptureSession* session, OH_Camera_ExposureMeteringMode* exposureMeteringMode);

/**
 * @brief 设置曝光测光模式。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param exposureMeteringMode 待设置的目标曝光测光模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许，会话或相机状态异常。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetExposureMeteringMode(const Camera_CaptureSession* session, OH_Camera_ExposureMeteringMode exposureMeteringMode);

/**
 * @brief 查询ISO感光度范围。
 *
 * @param session Camera_CaptureSession实例。
 * @param minIsoValue 输出参数，返回ISO最小值。
 * @param maxIsoValue 输出参数，返回ISO最大值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许，会话或相机状态异常。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetSupportedISORange(const Camera_CaptureSession* session,
    int32_t *minIsoValue, int32_t *maxIsoValue);

/**
 * @brief 获取当前ISO感光度值（遵循ISO 12232:2006标准）。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param isoValue 输出参数，返回当前ISO感光度值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许，会话或相机状态异常。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetIso(const Camera_CaptureSession* session, int32_t* isoValue);

/**
 * @brief 设置ISO感光度值。设置的值需在{@link OH_CaptureSession_GetSupportedISORange}范围内。当曝光锁定模式{@link ExposureMode}
 * 为EXPOSURE_MODE_LOCKED时，不支持设置ISO感光度值。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param isoValue 待设置的目标ISO值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许，会话或相机状态异常。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetIso(const Camera_CaptureSession* session, int32_t isoValue);

/**
 * @brief 用于在相机会话中监听感光度（ISO）变化的回调函数。
 * 
 * @param session 指向Camera_CaptureSession的指针。
 * @param isoValue 回调中获取的感光度（ISO）的值。
 * @since 22
 */
typedef void (*OH_CaptureSession_OnIsoChange)(Camera_CaptureSession* session, int32_t isoValue);

/**
 * @brief 注册监听感光度（ISO）改变的事件回调。
 * 
 * @param session 指向Camera_CaptureSession实例的指针。
 * @param isoChange OH_CaptureSession_OnIsoChange类型的回调函数，用于监听ISO改变。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或者参数类型不正确。
 * @since 22
 */
Camera_ErrorCode OH_CaptureSession_RegisterIsoChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnIsoChange isoChange);

/**
 * @brief 取消注册监听感光度（ISO）改变的事件回调。
 * 
 * @param session 指向Camera_CaptureSession实例的指针。
 * @param isoChange OH_CaptureSession_OnIsoChange类型的回调函数，用于监听ISO改变。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或者参数类型不正确。
 * @since 22
 */
Camera_ErrorCode OH_CaptureSession_UnregisterIsoChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnIsoChange isoChange);

/**
 * @brief 获取支持的物理光圈列表。调用{@link OH_CaptureSession_DeletePhysicalApertures}删除支持的物理光圈列表。
 *
 * @param session Camera_CaptureSession实例。
 * @param apertures 用于存储物理光圈值的数组指针。
 * @param size 输出物理光圈数组大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许，会话或相机状态异常。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetSupportedPhysicalApertures(const Camera_CaptureSession* session,
    OH_Camera_PhysicalAperture** apertures, uint32_t* size);

/**
 * @brief 获取当前物理光圈值。
 *
 * @param session Camera_CaptureSession实例。
 * @param aperture 输出参数，返回当前光圈值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许，会话或相机状态异常。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetPhysicalAperture(const Camera_CaptureSession* session, double* aperture);

/**
 * @brief 删除支持的物理光圈列表。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param apertures 待删除的物理光圈数组指针。
 * @param size 物理光圈数组大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_DeletePhysicalApertures(const Camera_CaptureSession* session,
    OH_Camera_PhysicalAperture* apertures, uint32_t size);

/**
 * @brief 设置物理光圈值。
 *
 * @param session Camera_CaptureSession实例。
 * @param aperture 待设置的光圈值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许，会话或相机状态异常。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetPhysicalAperture(const Camera_CaptureSession* session, double aperture);

/**
 * @brief 查询曝光补偿范围。
 * 
 * @param session Camera_CaptureSession实例。
 * @param minExposureBias 曝光补偿的最小值。
 * @param maxExposureBias 曝光补偿的最大值。
 * @param step 每个级别之间的曝光补偿阶梯。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetExposureBiasRange(Camera_CaptureSession* session, float* minExposureBias,
    float* maxExposureBias, float* step);

/**
 * @brief 设置曝光补偿。
 * 
 * @param session Camera_CaptureSession实例。
 * @param exposureBias 要设置的曝光补偿。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetExposureBias(Camera_CaptureSession* session, float exposureBias);

/**
 * @brief 获取当前曝光补偿。
 * 
 * @param session Camera_CaptureSession实例。
 * @param exposureBias 当前的曝光补偿。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetExposureBias(Camera_CaptureSession* session, float* exposureBias);

/**
 * @brief 获取支持的曝光时间范围。单位：微秒。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param minExposureDuration 输出参数，返回曝光时间最小值。
 * @param maxExposureDuration 输出参数，返回曝光时间最大值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetSupportedExposureDurationRange(const Camera_CaptureSession* session, int32_t* minExposureDuration,
    int32_t* maxExposureDuration);

/**
 * @brief 设置曝光时间。单位：微秒。若传感器无法精确使用该曝光时间，系统会自动调整为最近的支持值，并通过{@link OH_CaptureSession_OnExposureDurationChange}回调通知。仅在
 * {@link ExposureMode}.EXPOSURE_MODE_MANUAL手动曝光模式下设置生效。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param exposureDuration 待设置的目标曝光时间。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许，会话或相机状态异常。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetExposureDuration(const Camera_CaptureSession* session, int32_t exposureDuration);

/**
 * @brief 获取当前曝光时间。单位：微秒。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param exposureDuration 输出参数，返回当前曝光时间。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许，会话或相机状态异常。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetExposureDuration(const Camera_CaptureSession* session, int32_t* exposureDuration);

/**
 * @brief 捕获会话曝光时间变更回调。
 *
 * @param session 传递回调的Camera_CaptureSession指针。
 * @param exposureDuration 回调传递的曝光时间。
 * @since 24
 */
typedef void (*OH_CaptureSession_OnExposureDurationChange)(const Camera_CaptureSession* session, int32_t exposureDuration);

/**
 * @brief 注册曝光信息变更事件回调，曝光参数变更后系统会返回更新后的曝光信息。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param exposureDurationChange 待注册的曝光时间变更回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_RegisterExposureInfoChangeCallback(
    const Camera_CaptureSession* session, OH_CaptureSession_OnExposureDurationChange exposureDurationChange);

/**
 * @brief 注销曝光信息变更回调，相机操作完成后调用该方法。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param exposureDurationChange 待注销的曝光时间变更回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_UnregisterExposureInfoChangeCallback(
    const Camera_CaptureSession* session, OH_CaptureSession_OnExposureDurationChange exposureDurationChange); 

/**
 * @brief 检查是否支持指定的聚焦模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param focusMode 要检查的聚焦模式。
 * @param isSupported 是否支持聚焦模式的结果。返回true表示支持聚焦模式，返回false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_IsFocusModeSupported(Camera_CaptureSession* session,
    Camera_FocusMode focusMode, bool* isSupported);

/**
 * @brief 获取当前聚焦模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param focusMode 当前聚焦模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetFocusMode(Camera_CaptureSession* session, Camera_FocusMode* focusMode);

/**
 * @brief 设置聚焦模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param focusMode 要设置的聚焦模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetFocusMode(Camera_CaptureSession* session, Camera_FocusMode focusMode);

/**
 * @brief 获取当前焦点。
 * 
 * @param session Camera_CaptureSession实例。
 * @param focusPoint 当前焦点。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetFocusPoint(Camera_CaptureSession* session, Camera_Point* focusPoint);

/**
 * @brief 设置焦点。
 * 
 * @param session Camera_CaptureSession实例。
 * @param focusPoint 要设置的目标点。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetFocusPoint(Camera_CaptureSession* session, Camera_Point focusPoint);

/**
 * @brief 获取所有支持的缩放比例范围。
 * 
 * @param session Camera_CaptureSession实例。
 * @param minZoom 缩放比范围的最小值。
 * @param maxZoom 缩放比例范围的最大值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetZoomRatioRange(Camera_CaptureSession* session, float* minZoom, float* maxZoom);

/**
 * @brief 获取当前缩放比例。
 * 
 * @param session Camera_CaptureSession实例。
 * @param zoom 当前缩放比例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetZoomRatio(Camera_CaptureSession* session, float* zoom);

/**
 * @brief 设置缩放比例。
 * 
 * @param session Camera_CaptureSession实例。
 * @param zoom 要设置的目标缩放比。
 *     <br>设置可变焦距比到底层生效需要一定时间，获取正确设置的可变焦距比需要等待1~2帧的时间。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetZoomRatio(Camera_CaptureSession* session, float zoom);

/**
 * @brief 检查是否支持指定的录像防抖模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param mode 要检查的录像防抖模式。
 * @param isSupported 是否支持录像防抖模式的结果。返回true表示支持录像防抖模式，返回false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_IsVideoStabilizationModeSupported(Camera_CaptureSession* session,
    Camera_VideoStabilizationMode mode, bool* isSupported);

/**
 * @brief 获取当前录像防抖模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param mode 当前录像防抖模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetVideoStabilizationMode(Camera_CaptureSession* session,
    Camera_VideoStabilizationMode* mode);

/**
 * @brief 设置录像防抖模式。
 * 
 * @param session Camera_CaptureSession实例。
 * @param mode 要设置的录像防抖模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetVideoStabilizationMode(Camera_CaptureSession* session,
    Camera_VideoStabilizationMode mode);

/**
 * @brief 确定是否可以将相机输入添加到会话中。
 * 
 * @param session Camera_CaptureSession实例。
 * @param cameraInput 要设置的相机输入实例。
 * @param isSuccessful 是否可以将相机输入添加到会话中的结果。返回true表示可以将相机输入添加到会话中，返回false表示不可以。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_CanAddInput(Camera_CaptureSession* session,
    Camera_Input* cameraInput, bool* isSuccessful);

/**
 * @brief 确定是否可以将相机预览输出添加到会话中。
 * 
 * @param session Camera_CaptureSession实例。
 * @param cameraOutput 要设置的预览输出实例。
 * @param isSuccessful 是否可以将相机预览输出添加到会话中的结果。返回true表示可以将相机预览输出添加到会话中，返回false表示不可以。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_CanAddPreviewOutput(Camera_CaptureSession* session,
    Camera_PreviewOutput* cameraOutput, bool* isSuccessful);

/**
 * @brief 确定是否可以将拍照输出添加到会话中。
 * 
 * @param session Camera_CaptureSession实例。
 * @param cameraOutput 要设置的拍照输出实例。
 * @param isSuccessful 拍照输出是否可以添加到会话中的结果。返回true表示拍照输出可以添加到会话中，返回false表示不可以。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_CanAddPhotoOutput(Camera_CaptureSession* session,
    Camera_PhotoOutput* cameraOutput, bool* isSuccessful);

/**
 * @brief 确定是否可以将录像输出添加到会话中。
 * 
 * @param session Camera_CaptureSession实例。
 * @param cameraOutput 要添加的录像输出实例。
 * @param isSuccessful 录像输出是否可以添加到会话中的结果。返回true表示录像输出可以添加到会话中，返回false表示不可以。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_CanAddVideoOutput(Camera_CaptureSession* session,
    Camera_VideoOutput* cameraOutput, bool* isSuccessful);

/**
 * @brief 检查是否支持指定的预配置类型。
 * 
 * @param session Camera_CaptureSession实例。
 * @param preconfigType 要检查的预配置类型。
 * @param canPreconfig 是否支持预配置的结果。返回true表示支持预配置，返回false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_CanPreconfig(Camera_CaptureSession* session,
    Camera_PreconfigType preconfigType, bool* canPreconfig);

/**
 * @brief 检查是否支持带比例的预配置类型。
 * 
 * @param session Camera_CaptureSession实例。
 * @param preconfigType 要检查的预配置类型。
 * @param preconfigRatio 要检查的预配置比例。
 * @param canPreconfig 是否支持预配置的结果。返回true表示支持预配置，返回false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_CanPreconfigWithRatio(Camera_CaptureSession* session,
    Camera_PreconfigType preconfigType, Camera_PreconfigRatio preconfigRatio, bool* canPreconfig);

/**
 * @brief 设置预配置类型。
 * 
 * @param session Camera_CaptureSession实例。
 * @param preconfigType 指定的预配置类型。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_Preconfig(Camera_CaptureSession* session,
    Camera_PreconfigType preconfigType);

/**
 * @brief 设置带有比例的预配置类型。
 * 
 * @param session Camera_CaptureSession实例。
 * @param preconfigType 指定的预配置类型。
 * @param preconfigRatio 指定的预配置比例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_PreconfigWithRatio(Camera_CaptureSession* session,
    Camera_PreconfigType preconfigType, Camera_PreconfigRatio preconfigRatio);

/**
 * @brief 查询曝光值。
 * 
 * @param session Camera_CaptureSession实例。
 * @param exposureValue 当前的曝光值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_GetExposureValue(Camera_CaptureSession* session, float* exposureValue);

/**
 * @brief 获取当前焦距值。
 * 
 * @param session Camera_CaptureSession实例。
 * @param focalLength 当前焦距值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_GetFocalLength(Camera_CaptureSession* session, float* focalLength);

/**
 * @brief 查询是否支持对焦距离设置。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param isSupported 输出参数，返回是否支持对焦距离的结果。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_IsFocusDistanceSupported(const Camera_CaptureSession* session, bool* isSupported);

/**
 * @brief 获取当前对焦距离。取值范围为[0.0, 1.0]。0.0表示镜头可对焦的最近距离；1.0表示最远距离。默认值为1.0。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param focusDistance 输出参数，返回当前对焦距离。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许，会话或输入设备可能异常。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetFocusDistance(const Camera_CaptureSession* session, float* focusDistance);

/**
 * @brief 设置对焦距离。取值范围为[0.0, 1.0]。0.0表示镜头可对焦的最近距离；1.0表示最远距离。默认值为1.0。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param focusDistance 待设置的对焦距离。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许，会话或输入设备可能异常。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetFocusDistance(const Camera_CaptureSession* session, float focusDistance);

/**
 * @brief 触发平滑变焦。
 * 
 * @param session Camera_CaptureSession实例。
 * @param targetZoom 要设置的目标变焦比。
 * @param smoothZoomMode 平滑变焦模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_SetSmoothZoom(Camera_CaptureSession* session,
    float targetZoom, Camera_SmoothZoomMode smoothZoomMode);

/**
 * @brief 获取支持的色彩空间列表。
 * 
 * @param session Camera_CaptureSession实例。
 * @param colorSpace 如果方法调用成功，将记录支持的OH_NativeBuffer_ColorSpace列表。
 * @param size 如果方法调用成功，将记录支持的OH_NativeBuffer_ColorSpace列表的大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_GetSupportedColorSpaces(Camera_CaptureSession* session,
    OH_NativeBuffer_ColorSpace** colorSpace, uint32_t* size);

/**
 * @brief 删除色彩空间列表。
 * 
 * @param session Camera_CaptureSession实例。
 * @param colorSpace 如果方法调用成功，将删除的OH_NativeBuffer_ColorSpace列表。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_DeleteColorSpaces(Camera_CaptureSession* session,
    OH_NativeBuffer_ColorSpace* colorSpace);

/**
 * @brief 获取当前色彩空间。
 * 
 * @param session Camera_CaptureSession实例。
 * @param colorSpace 当前的OH_NativeBuffer_ColorSpace。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_GetActiveColorSpace(Camera_CaptureSession* session,
    OH_NativeBuffer_ColorSpace* colorSpace);

/**
 * @brief 设置当前色彩空间。
 * 
 * @param session Camera_CaptureSession实例。
 * @param colorSpace 要设置的目标OH_NativeBuffer_ColorSpace。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_SetActiveColorSpace(Camera_CaptureSession* session,
    OH_NativeBuffer_ColorSpace colorSpace);

/**
 * @brief 注册设备切换事件回调。
 *
 * @param session Camera_CaptureSession实例。
 * @param autoDeviceSwitchStatusChange 要注册的设备切换事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 13
 */
Camera_ErrorCode OH_CaptureSession_RegisterAutoDeviceSwitchStatusCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnAutoDeviceSwitchStatusChange autoDeviceSwitchStatusChange);

/**
 * @brief 注销设备切换事件回调。
 *
 * @param session Camera_CaptureSession实例。
 * @param autoDeviceSwitchStatusChange 要注销的设备切换事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 13
 */
Camera_ErrorCode OH_CaptureSession_UnregisterAutoDeviceSwitchStatusCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnAutoDeviceSwitchStatusChange autoDeviceSwitchStatusChange);

/**
 * @brief 检查是否支持自动设备切换。
 *
 * @param session Camera_CaptureSession实例。
 * @param isSupported 是否支持自动设备切换的结果。返回true表示支持自动设备切换，返回false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 13
 */
Camera_ErrorCode OH_CaptureSession_IsAutoDeviceSwitchSupported(Camera_CaptureSession* session, bool* isSupported);

/**
 * @brief 是否启用相机设备的自动切换。
 *
 * @param session Camera_CaptureSession实例。
 * @param enabled 是否启用自动切换的标志。返回true表示启用自动切换，返回false表示不启用。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 13
 */
Camera_ErrorCode OH_CaptureSession_EnableAutoDeviceSwitch(Camera_CaptureSession* session, bool enabled);

/**
 * @brief 设置录像质量优先级。
 * <br>默认为高录像质量，设置为功耗平衡将降低录像质量以减少功耗。实际功耗收益因平台而异。建议该接口在{@link OH_CaptureSession_CommitConfig}和
 * {@link OH_CaptureSession_Start}之间调用。
 *
 * @param session Camera_CaptureSession实例。
 * @param qualityPrioritization 要设置的录像质量优先级，默认为高录像质量。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 14
 */
Camera_ErrorCode OH_CaptureSession_SetQualityPrioritization(
    Camera_CaptureSession* session, Camera_QualityPrioritization qualityPrioritization);

/**
 * @brief 检查是否支持微距能力。
 * 
 * @param session Camera_CaptureSession实例。
 * @param isSupported 是否支持微距能力的结果。返回true表示支持微距能力，返回false表示不支持。
 *     @return
 *     <br>CAMERA_OK = 0：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 19
 */
Camera_ErrorCode OH_CaptureSession_IsMacroSupported(Camera_CaptureSession* session, bool* isSupported);

/**
 * @brief 是否启用相机设备的微距能力。
 * 
 * @param session Camera_CaptureSession实例。
 * @param enabled 是否启用微距能力的标志。返回true表示启用微距能力，返回false表示不启用。
 *     @return
 *     <br>CAMERA_OK = 0：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：不允许操作。
 * @since 19
 */
Camera_ErrorCode OH_CaptureSession_EnableMacro(Camera_CaptureSession* session, bool enabled);

/**
 * @brief 相机会话微距状态改变回调。
 * 
 * @param session 指向Camera_CaptureSession实例的指针。
 * @param isMacroDetected 是否进入超级微距，true表示进入超级微距，false表示未进入超级微距。
 * @since 20
 */
typedef void (*OH_CaptureSession_OnMacroStatusChange)(Camera_CaptureSession* session, bool isMacroDetected);

/**
 * @brief 注册相机会话微距状态改变回调函数。
 * 
 * @param session 指向Camera_CaptureSession实例的指针。
 * @param macroStatusChange 微距状态改变回调函数。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_RegisterMacroStatusChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnMacroStatusChange macroStatusChange);

/**
 * @brief 取消注册相机会话微距状态改变回调函数。
 * 
 * @param session 指向Camera_CaptureSession实例的指针。
 * @param macroStatusChange 微距状态改变回调函数。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_UnregisterMacroStatusChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnMacroStatusChange macroStatusChange);

/**
 * @brief 注册系统压力状态变化回调。
 *
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param systemPressureLevelChange 要注册的系统压力状态变化OH_CaptureSession_OnSystemPressureLevelChange回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_RegisterSystemPressureLevelChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnSystemPressureLevelChange systemPressureLevelChange);

/**
 * @brief 注销系统压力状态变化回调。
 * 
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param systemPressureLevelChange 要注销的系统压力状态变化OH_CaptureSession_OnSystemPressureLevelChange回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_UnregisterSystemPressureLevelChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnSystemPressureLevelChange systemPressureLevelChange);

/**
 * @brief 检查是否支持相机控制器。
 * 
 * @param session Camera_CaptureSession实例。
 * @param isSupported 是否支持相机控制器的结果。true表示支持，false表示不支持。
 * @return CAMERA_OK = 0：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_IsControlCenterSupported(Camera_CaptureSession* session, bool* isSupported);

/**
 * @brief 获取相机控制器支持的效果类型。
 * 
 * @param session Camera_CaptureSession实例。
 * @param types 如果方法调用成功，将记录支持的Camera_ControlCenterEffectType列表。
 * @param size 如果方法调用成功，将记录支持的Camera_ControlCenterEffectType列表的大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_GetSupportedEffectTypes(
    Camera_CaptureSession* session, Camera_ControlCenterEffectType** types, uint32_t* size);

/**
 * @brief 删除相机控制器效果类型列表。
 * 
 * @param session Camera_CaptureSession实例。
 * @param types 如果方法调用成功，要删除的Camera_ControlCenterEffectType列表。
 * @param size 要删除的Camera_ControlCenterEffectType列表的大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_DeleteSupportedEffectTypes(Camera_CaptureSession* session,
    Camera_ControlCenterEffectType* types, uint32_t size);

/**
 * @brief 是否启用相机控制器。
 * 
 * @param session Camera_CaptureSession实例。
 * @param enabled 是否启用相机控制器的标志。true表示启用，false表示禁用。
 * @return CAMERA_OK = 0：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_EnableControlCenter(Camera_CaptureSession* session, bool enabled);

/**
 * @brief 相机控制器效果激活状态变化回调。
 * 
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param controlCenterStatusInfo 回调传递的相机控制器效果激活状态。
 * @since 20
 */
typedef void (*OH_CaptureSession_OnControlCenterEffectStatusChange)(Camera_CaptureSession* session,
    Camera_ControlCenterStatusInfo* controlCenterStatusInfo);

/**
 * @brief 注册相机控制器效果激活状态变化回调。
 * 
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param controlCenterEffectStatusChange 要注册的相机控制器效果激活状态变化OH_CaptureSession_OnControlCenterEffectStatusChange回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_RegisterControlCenterEffectStatusChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnControlCenterEffectStatusChange controlCenterEffectStatusChange);

/**
 * @brief 注销相机控制器效果激活状态变化回调。
 * 
 * @param session 传递回调的Camera_CaptureSession实例。
 * @param controlCenterEffectStatusChange 要注销的相机控制器效果激活状态变化OH_CaptureSession_OnControlCenterEffectStatusChange回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_UnregisterControlCenterEffectStatusChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnControlCenterEffectStatusChange controlCenterEffectStatusChange);

/**
 * @brief 查询物理镜头RAW图拍照支持的变焦范围。
 *
 * @param session Camera_CaptureSession实例。
 * @param minZoom 输出参数，返回变焦最小值。
 * @param maxZoom 输出参数，返回变焦最大值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许,会话或相机状态异常。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetRAWCaptureZoomRatioRange(const Camera_CaptureSession* session, float* minZoom, float* maxZoom);

/**
 * @brief 检查指定的光学防抖（OIS）模式是否支持。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param oisMode 待检查的光学防抖模式。
 * @param isSupported 输出参数，返回当前设备是否支持该模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_IsOISModeSupported(const Camera_CaptureSession* session,
    OH_Camera_OISMode oisMode, bool* isSupported);

/**
 * @brief 获取指定光学防抖轴支持的偏移范围。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param oisAxis 光学防抖轴。
 * @param minBias 输出参数，返回最小偏移值。
 * @param maxBias 输出参数，返回最大偏移值。
 * @param step 输出参数，返回偏移步长值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetSupportedOISBiasRange(const Camera_CaptureSession* session,
    OH_Camera_OISAxes oisAxis, float* minBias, float* maxBias, float* step);

/**
 * @brief 获取当前光学防抖（OIS）模式。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param oisMode 输出参数，返回当前光学防抖模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetCurrentOISMode(const Camera_CaptureSession* session,
    OH_Camera_OISMode* oisMode);

/**
 * @brief 获取所有光学防抖轴当前的自定义偏移值。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param pitchBias 输出参数，返回俯仰轴偏移值。
 * @param yawBias 输出参数，返回偏航轴偏移值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetCurrentCustomOISBias(const Camera_CaptureSession* session,
    float* pitchBias, float* yawBias);

/**
 * @brief 设置光学防抖（OIS）模式。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param oisMode 待设置的光学防抖模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetOISMode(const Camera_CaptureSession* session,
    OH_Camera_OISMode oisMode);

/**
 * @brief 为对应轴设置自定义光学防抖偏移值。
 *
 * @param session Camera_CaptureSession实例指针。
 * @param pitchBias 俯仰轴偏移值。
 * @param yawBias 偏航轴偏移值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetOISModeCustom(const Camera_CaptureSession* session,
    float pitchBias, float yawBias);

/**
 * @brief 获取变焦点信息。
 * <br>需要通过调用{@link OH_CaptureSession_DeleteZoomPointInfos}来释放变焦点信息的内存。
 *
 * @param session 捕获会话对象的实例指针。
 * @param size 输出参数，返回查询到的变焦点信息数量。
 * @param zoomPointInfo 输出参数，返回查询到的变焦点信息数组。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 * @since 26.0.0
 */
Camera_ErrorCode OH_CaptureSession_GetZoomPointInfos(const Camera_CaptureSession* session, uint32_t* size,
    OH_Camera_ZoomPointInfo** zoomPointInfo);

/**
 * @brief 删除变焦点信息。
 *
 * @param session 捕获会话对象的实例指针。
 * @param zoomPointInfo 待删除的变焦点信息数组，方法调用成功后该内存将被释放。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 * @since 26.0.0
 */
Camera_ErrorCode OH_CaptureSession_DeleteZoomPointInfos(const Camera_CaptureSession* session,
    OH_Camera_ZoomPointInfo* zoomPointInfo);

/**
 * @brief 查询是否支持锁定焦点跟踪。
 *
 * @param session 指向Camera_CaptureSession实例的指针。
 * @return 是否支持追焦跟踪功能，返回true表示支持，返回false表示不支持。
 * @since 26.0.0
 */
bool OH_CaptureSession_IsLockFocusTrackingSupported(const Camera_CaptureSession* session);
 
/**
 * @brief 锁定焦点跟踪，可通过{@link OH_CaptureSession_UnlockFocusTracking}解锁。
 * 
 * @param session 指向Camera_CaptureSession实例的指针。
 * @param focusPoint 锁定焦点跟踪的追踪点。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 26.0.0
 */
Camera_ErrorCode OH_CaptureSession_LockFocusTracking(Camera_CaptureSession* session, Camera_Point focusPoint);
 
/**
 * @brief 解锁焦点跟踪。
 *
 * @param session 指向Camera_CaptureSession实例的指针。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 26.0.0
 */
Camera_ErrorCode OH_CaptureSession_UnlockFocusTracking(Camera_CaptureSession* session);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_CAMERA_SESSION_H
/** @} */
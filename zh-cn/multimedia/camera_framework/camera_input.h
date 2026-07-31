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
 * @file camera_input.h
 *
 * @brief 声明相机输入概念。
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 11
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_CAMERA_CAMERA_INPUT_H
#define NATIVE_INCLUDE_CAMERA_CAMERA_INPUT_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 相机输入对象。可以使用{@link OH_CameraManager_CreateCameraInput}方法创建指针。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Input Camera_Input;

/**
 * @brief 在{@link CameraInput_Callbacks}中被调用的相机输入错误回调。
 * 
 * @param cameraInput 传递回调的Camera_Input。
 * @param errorCode 相机输入的Camera_ErrorCode。
 * @see CAMERA_CONFLICT_CAMERA
 * @see CAMERA_DEVICE_DISABLED
 * @see CAMERA_DEVICE_PREEMPTED
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 11
 */
typedef void (*OH_CameraInput_OnError)(const Camera_Input* cameraInput, Camera_ErrorCode errorCode);

/**
 * @brief 相机输入错误事件的回调。
 * 
 * @see OH_CameraInput_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct CameraInput_Callbacks {
    /**
     * 相机输入错误事件。
     */
    OH_CameraInput_OnError onError;
} CameraInput_Callbacks;

/**
 * @brief 注册相机输入更改事件回调。
 * 
 * @param cameraInput Camera_Input实例。
 * @param callback 要注册的相机输入更改事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_CameraInput_RegisterCallback(Camera_Input* cameraInput, CameraInput_Callbacks* callback);

/**
 * @brief 注销相机输入更改事件回调。
 * 
 * @param cameraInput Camera_Input实例。
 * @param callback 要注销的相机输入更改事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_CameraInput_UnregisterCallback(Camera_Input* cameraInput, CameraInput_Callbacks* callback);

/**
 * @brief 打开相机。
 * 
 * @param cameraInput 要打开的Camera_Input实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_CONFLICT_CAMERA：因冲突而无法使用相机。
 *     <br>CAMERA_DEVICE_DISABLED：由于安全原因禁用了相机。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_CameraInput_Open(Camera_Input* cameraInput);

/**
 * @brief 打开安全相机。
 * 
 * @param cameraInput 要打开的Camera_Input实例。
 * @param secureSeqId 表示安全摄像头的序列值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_CONFLICT_CAMERA：因冲突而无法使用相机。
 *     <br>CAMERA_DEVICE_DISABLED：由于安全原因禁用了相机。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_CameraInput_OpenSecureCamera(Camera_Input* cameraInput, uint64_t* secureSeqId);

/**
 * @brief 关闭相机。
 * 
 * @param cameraInput 要关闭的Camera_Input实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_CameraInput_Close(Camera_Input* cameraInput);

/**
 * @brief 释放相机输入实例。
 * <br>和{@link OH_CameraInput_Close}只需要调用其中一个，调用之后无须再调用{@link OH_CameraInput_Close}。
 * 
 * @param cameraInput 要释放的Camera_Input实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_CameraInput_Release(Camera_Input* cameraInput);

/**
 * @brief 查询设备不同折叠状态下，相机物理镜头角度是否可变。
 * 
 * @param {CameraInput} cameraInput the {@link Camera_Input} instance.
 * @param {bool} isVariable the result of whether physical camera orientation is variable.
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 22
 */
Camera_ErrorCode OH_CameraInput_IsPhysicalCameraOrientationVariable(Camera_Input* cameraInput, bool* isVariable);

/**
 * @brief 获取设备当前折叠状态下的物理镜头角度。
 * 
 * @param cameraInput Camera_Input实例。
 * @param orientation 如果方法调用成功，将返回设备当前折叠状态下的物理镜头角度。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 22
 */
Camera_ErrorCode OH_CameraInput_GetPhysicalCameraOrientation(Camera_Input* cameraInput, uint32_t* orientation);

/**
 * @brief 选择是否使用物理镜头角度。
 * 
 * @param cameraInput Camera_Input实例。
 * @param isUsed 选择是否使用物理镜头角度。true表示使用，false表示不使用。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_OPERATION_NOT_ALLOWED：操作不允许。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 22
 */
Camera_ErrorCode OH_CameraInput_UsePhysicalCameraOrientation(Camera_Input* cameraInput, bool isUsed);

/**
 * @brief 相机镜头遮挡、脏污检测结果回调。
 * 
 * @param cameraInput 传递回调的Camera_Input。
 * @param occlusionDetectionResult 相机镜头遮挡、脏污检测结果。
 * @since 23
 */
typedef void (*OH_CameraInput_OnOcclusionDetectionCallback)(const Camera_Input* cameraInput,
    Camera_OcclusionDetectionResult occlusionDetectionResult);

/**
 * @brief 注册相机镜头遮挡、脏污检测事件回调。
 * 
 * @param cameraInput Camera_Input实例。
 * @param occlusionDetectionCallback 要注册的相机镜头遮挡、脏污检测事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 23
 */
Camera_ErrorCode OH_CameraInput_RegisterOcclusionDetectionCallback(Camera_Input* cameraInput,
    OH_CameraInput_OnOcclusionDetectionCallback occlusionDetectionCallback);

/**
 * @brief 注销相机镜头遮挡、脏污检测事件回调。
 * 
 * @param cameraInput Camera_Input实例。
 * @param occlusionDetectionCallback 要注销的相机镜头遮挡、脏污检测事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 23
 */
Camera_ErrorCode OH_CameraInput_UnregisterOcclusionDetectionCallback(Camera_Input* cameraInput,
    OH_CameraInput_OnOcclusionDetectionCallback occlusionDetectionCallback);

/**
 * @brief 根据指定并发类型打开相机。
 * 
 * @param cameraInput 要打开的Camera_Input实例。
 * @param type 指定并发类型。
 * @return CAMERA_OK: 方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_CONFLICT_CAMERA：因冲突而无法使用相机。
 *     <br>CAMERA_DEVICE_DISABLED：由于安全原因禁用了相机。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 18
 */
Camera_ErrorCode OH_CameraInput_OpenConcurrentCameras(Camera_Input* cameraInput, Camera_ConcurrentType type);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_CAMERA_INPUT_H
/** @} */

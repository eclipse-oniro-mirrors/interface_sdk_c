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
 * @file metadata_output.h
 *
 * @brief 声明元数据输出概念。
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 11
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_CAMERA_METADATAOUTPUT_H
#define NATIVE_INCLUDE_CAMERA_METADATAOUTPUT_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "camera.h"
#include "metadata_object_ext.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 元数据输出对象。<br> 可以使用{@link OH_CameraManager_CreateMetadataOutput}
 * 方法与OH_CameraManager_CreateMetadataOutputWithObjectTypes方法（从API version 23开始支持）创建指针。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_MetadataOutput Camera_MetadataOutput;

/**
 * @brief 在{@link MetadataOutput_Callbacks}中被调用的元数据输出元数据对象可用回调。
 * 
 * @param metadataOutput 传递回调的元数据输出实例。
 * @param metadataObject 回调传递的元数据实例信息。
 * @param size 元数据对象的大小。
 * @since 11
 */
typedef void (*OH_MetadataOutput_OnMetadataObjectAvailable)(Camera_MetadataOutput* metadataOutput,
    Camera_MetadataObject* metadataObject, uint32_t size);

/**
 * @brief 用于监听元数据对象上报事件的回调。使用{@link OH_MetadataOutput_RegisterMetadataObjectExtAvailableCallback}进行注册。
 *
 * @param context 用户提供的上下文指针。
 * @param metadataObjectExt 指向元数据对象的二级指针。
 * @param size 元数据对象的数量。
 * @since 26.0.0
 */
typedef void (*OH_MetadataOutput_OnMetadataObjectExtAvailable)(void* context,
    OH_Camera_MetadataObjectExt** metadataObjectExt, uint32_t size);

/**
 * @brief 在{@link MetadataOutput_Callbacks}中被调用的元数据输出错误回调。
 * 
 * @param metadataOutput 传递回调的元数据输出实例。
 * @param errorCode 元数据输出的错误码。
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 11
 */
typedef void (*OH_MetadataOutput_OnError)(Camera_MetadataOutput* metadataOutput, Camera_ErrorCode errorCode);

/**
 * @brief 在元数据输出期间，用于监听错误事件的回调。
 *
 * @param context 用户提供的上下文指针。
 * @param errorCode 元数据输出期间报告的错误码。
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 26.0.0
 */
typedef void (*OH_MetadataOutput_OnErrorExt)(void* context, Camera_ErrorCode errorCode);

/**
 * @brief 元数据输出的回调。
 * 
 * @see OH_MetadataOutput_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct MetadataOutput_Callbacks {
    /**
     * 此回调将调用元数据输出结果数据。
     */
    OH_MetadataOutput_OnMetadataObjectAvailable onMetadataObjectAvailable;

    /**
     * 元数据输出错误事件。
     */
    OH_MetadataOutput_OnError onError;
} MetadataOutput_Callbacks;

/**
 * @brief 注册元数据输出更改事件回调。
 * 
 * @param metadataOutput 元数据输出实例。
 * @param callback 要注册的元数据输出回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_MetadataOutput_RegisterCallback(Camera_MetadataOutput* metadataOutput,
    MetadataOutput_Callbacks* callback);

/**
 * @brief 注销元数据输出更改事件回调。
 * 
 * @param metadataOutput 元数据输出实例。
 * @param callback 要注销的元数据输出回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_MetadataOutput_UnregisterCallback(Camera_MetadataOutput* metadataOutput,
    MetadataOutput_Callbacks* callback);

/**
 * @brief 注册监听元数据对象上报事件的回调。该回调可通过{@link OH_MetadataOutput_UnregisterMetadataObjectExtAvailableCallback}注销。
 *
 * @param metadataOutput 元数据输出实例的指针。
 * @param context 用户提供的上下文指针。
 * @param callback 监听元数据对象上报事件的回调的指针。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataOutput_RegisterMetadataObjectExtAvailableCallback(Camera_MetadataOutput* metadataOutput,
    void* context, OH_MetadataOutput_OnMetadataObjectExtAvailable callback);

/**
 * @brief 注销监听元数据对象上报事件的回调。
 *
 * @param metadataOutput 元数据输出实例的指针。
 * @param context 用户提供的上下文指针。
 * @param callback 监听元数据对象上报事件的回调的指针。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataOutput_UnregisterMetadataObjectExtAvailableCallback(Camera_MetadataOutput* metadataOutput,
    void* context, OH_MetadataOutput_OnMetadataObjectExtAvailable callback);

/**
 * @brief 注册监听错误事件的回调。该回调可通过{@link OH_MetadataOutput_UnregisterErrorExtCallback}注销。
 *
 * @param metadataOutput 元数据输出实例的指针。
 * @param context 用户提供的上下文指针。
 * @param callback 监听错误事件的回调的指针。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataOutput_RegisterErrorExtCallback(Camera_MetadataOutput* metadataOutput, void* context,
    OH_MetadataOutput_OnErrorExt callback);

/**
 * @brief 注销监听错误事件的回调。
 *
 * @param metadataOutput 元数据输出实例的指针。
 * @param context 用户提供的上下文指针。
 * @param callback 监听错误事件的回调的指针。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataOutput_UnregisterErrorExtCallback(Camera_MetadataOutput* metadataOutput, void* context,
    OH_MetadataOutput_OnErrorExt callback);

/**
 * @brief 启动元数据输出。
 * 
 * @param metadataOutput 要启动的元数据输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_MetadataOutput_Start(Camera_MetadataOutput* metadataOutput);

/**
 * @brief 停止元数据输出。
 * 
 * @param metadataOutput 要停止的元数据输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_MetadataOutput_Stop(Camera_MetadataOutput* metadataOutput);

/**
 * @brief 释放元数据输出实例。
 * 
 * @param metadataOutput 要释放的元数据输出实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_MetadataOutput_Release(Camera_MetadataOutput* metadataOutput);

/**
 * @brief 添加元数据对象类型。
 * 
 * @param metadataOutput 元数据输出实例。
 * @param types 用于添加到Camera_MetadataOutput实例的元数据对象类型数组。
 * @param size 元数据对象类型数组长度。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 23
 */
Camera_ErrorCode OH_MetadataOutput_AddMetadataObjectTypes (Camera_MetadataOutput* metadataOutput, Camera_MetadataObjectType* types, uint32_t size);

/**
 * @brief 移除元数据对象类型。
 * 
 * @param metadataOutput 元数据输出实例。
 * @param types 从Camera_MetadataOutput实例移除的元数据对象类型数组。
 * @param size 元数据对象类型数组长度。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 23
 */
Camera_ErrorCode OH_MetadataOutput_RemoveMetadataObjectTypes (Camera_MetadataOutput* metadataOutput, Camera_MetadataObjectType* types, uint32_t size);

/**
 * @brief 检查设备是否支持锁定元数据对象（如猫脸、狗脸）追踪功能。
 *
 * @param metadataOutput MetadataOutput实例的指针。
 * @return true表示支持该功能。
 *     <br>false表示不支持该功能。
 * @since 26.0.0
 */
bool OH_MetadataOutput_IsLockMetadataObjectTrackingSupported(const Camera_MetadataOutput* metadataOutput);

/**
 * @brief 锁定对特定元数据对象（如猫脸、狗脸）的追踪。
 * <br>该功能以pointOfInterest所指向的点所在的对象为追踪对象，如果该点不存在追踪对象，则功能不生效。
 * <br>被锁定追踪的对象离开取景范围超过三秒或调用解锁追踪后，锁定追踪自动取消。
 *
 * @param metadataOutput 元数据输出实例的指针。
 * @param pointOfInterest 期望追踪对应位置对象的点的指针。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataOutput_LockMetadataObjectTracking(Camera_MetadataOutput* metadataOutput,
    Camera_Point* pointOfInterest);

/**
 * @brief 解锁元数据对象（如猫脸、狗脸）的追踪。
 *
 * @param metadataOutput 元数据输出实例的指针。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 *     <br>CAMERA_SESSION_NOT_CONFIG：捕获会话未配置。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataOutput_UnlockMetadataObjectTracking(Camera_MetadataOutput* metadataOutput);
#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_METADATAOUTPUT_H
/** @} */

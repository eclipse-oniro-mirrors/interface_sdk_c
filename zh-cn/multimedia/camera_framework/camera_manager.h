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
 * @file camera_manager.h
 *
 * @brief 声明相机管理器的概念。
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 11
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_CAMERA_CAMERA_MANAGER_H
#define NATIVE_INCLUDE_CAMERA_CAMERA_MANAGER_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "camera.h"
#include "camera_input.h"
#include "capture_session.h"
#include "preview_output.h"
#include "video_output.h"
#include "photo_output.h"
#include "metadata_output.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 在{@link CameraManager_Callbacks}中被调用的相机管理器状态回调。
 * 
 * @param cameraManager 传递回调的Camera_Manager。
 * @param status 每个相机设备的状态信息。
 * @since 11
 */
typedef void (*OH_CameraManager_StatusCallback)(Camera_Manager* cameraManager, Camera_StatusInfo* status);

/**
 * @brief 手电筒状态变化回调。
 * 
 * @param cameraManager 传递回调的Camera_Manager。
 * @param status 手电筒的状态信息。
 * @since 12
 */
typedef void (*OH_CameraManager_TorchStatusCallback)(Camera_Manager* cameraManager, Camera_TorchStatusInfo* status);

/**
 * @brief 相机管理器折叠状态信息回调。
 * 
 * @param cameraManager 传递回调的Camera_Manager。
 * @param foldStatusInfo 设备的折叠状态信息。
 * @since 13
 */
typedef void (*OH_CameraManager_OnFoldStatusInfoChange)(Camera_Manager* cameraManager,
    Camera_FoldStatusInfo* foldStatusInfo);

/**
 * @brief 相机设备状态的回调。
 * 
 * @see OH_CameraManager_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct CameraManager_Callbacks {
    /**
     * 相机状态更改事件。
     */
    OH_CameraManager_StatusCallback onCameraStatus;
} CameraManager_Callbacks;

/**
 * @brief 注册相机状态更改事件回调。
 * 
 * @param cameraManager 相机管理器实例。
 * @param callback 要注册的相机设备状态回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_RegisterCallback(Camera_Manager* cameraManager, CameraManager_Callbacks* callback);

/**
 * @brief 注销相机状态更改事件回调。
 * 
 * @param cameraManager 相机管理器实例。
 * @param callback 要注销的相机设备状态回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_UnregisterCallback(Camera_Manager* cameraManager, CameraManager_Callbacks* callback);

/**
 * @brief 注册手电筒状态变更事件回调。
 * 
 * @param cameraManager 相机管理器实例。
 * @param torchStatusCallback 要注册的手电筒状态变化回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_RegisterTorchStatusCallback(Camera_Manager* cameraManager,
    OH_CameraManager_TorchStatusCallback torchStatusCallback);

/**
 * @brief 注销手电筒状态变更事件回调。
 * 
 * @param cameraManager 相机管理器实例。
 * @param torchStatusCallback 要注销的手电筒状态变化回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_UnregisterTorchStatusCallback(Camera_Manager* cameraManager,
    OH_CameraManager_TorchStatusCallback torchStatusCallback);

/**
 * @brief 注册折叠状态信息变更事件回调。
 * 
 * @param cameraManager 相机管理器实例。
 * @param foldStatusInfoCallback 要注册的折叠状态信息变更事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 13
 */
Camera_ErrorCode OH_CameraManager_RegisterFoldStatusInfoCallback(Camera_Manager* cameraManager,
    OH_CameraManager_OnFoldStatusInfoChange foldStatusInfoCallback);

/**
 * @brief 注销折叠状态信息变更事件回调。
 * 
 * @param cameraManager 相机管理器实例。
 * @param foldStatusInfoCallback 要注销的折叠状态信息变更事件回调。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 13
 */
Camera_ErrorCode OH_CameraManager_UnregisterFoldStatusInfoCallback(Camera_Manager* cameraManager,
    OH_CameraManager_OnFoldStatusInfoChange foldStatusInfoCallback);

/**
 * @brief 获取支持指定的相机设备实例。
 * 
 * @param cameraManager 相机管理器实例。
 * @param cameras 如果方法调用成功，将记录支持的Camera_Device列表。
 * @param size 如果方法调用成功，将记录支持的Camera_Device列表的大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_GetSupportedCameras(Camera_Manager* cameraManager,
    Camera_Device** cameras, uint32_t* size);

/**
 * @brief 删除支持的相机。
 * 
 * @param cameraManager 相机管理器实例。
 * @param cameras 要删除的Camera_Device列表。
 * @param size 要删除的相机设备数量。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_DeleteSupportedCameras(Camera_Manager* cameraManager,
    Camera_Device* cameras, uint32_t size);

/**
 * @brief 查询指定相机支持的输出能力。
 * 
 * @param cameraManager 相机管理器实例。
 * @param cameras the {@link Camera_Device} to be queried.
 * @param cameraOutputCapability 如果方法调用成功，将记录支持的Camera_OutputCapability。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_GetSupportedCameraOutputCapability(Camera_Manager* cameraManager,
    const Camera_Device* camera, Camera_OutputCapability** cameraOutputCapability);

/**
 * @brief 查询指定相机在指定模式下支持的输出能力。
 * 
 * @param cameraManager 相机管理器实例。
 * @param camera 要查询的Camera_Device。
 * @param sceneMode 指定相机模式。
 * @param cameraOutputCapability 如果方法调用成功，将记录支持的Camera_OutputCapability列表。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_GetSupportedCameraOutputCapabilityWithSceneMode(Camera_Manager* cameraManager,
    const Camera_Device* camera, Camera_SceneMode sceneMode, Camera_OutputCapability** cameraOutputCapability);

/**
 * @brief 查询指定相机在指定模式下支持的完整输出能力，包括未压缩图（YUV）、HEIF和HDR等能力。使用YUV，HEIF或HDR等能力前，需要先显式调用此方法确保获取完整输出能力。
 * 
 * @param cameraManager 相机管理器实例。
 * @param camera 要查询的Camera_Device。
 * @param sceneMode 指定相机模式。
 * @param cameraOutputCapability 如果方法调用成功，将记录支持的Camera_OutputCapability列表。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 23
 */
Camera_ErrorCode OH_CameraManager_GetSupportedFullCameraOutputCapabilityWithSceneMode(Camera_Manager* cameraManager,
    const Camera_Device* camera, Camera_SceneMode sceneMode, Camera_OutputCapability** cameraOutputCapability);

/**
 * @brief 删除支持的输出能力。
 * 
 * @param cameraManager 相机管理器实例。
 * @param cameraOutputCapability 要删除的Camera_OutputCapability。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_DeleteSupportedCameraOutputCapability(Camera_Manager* cameraManager,
    Camera_OutputCapability* cameraOutputCapability);

/**
 * @brief 确定相机是否静音。
 * 
 * @param cameraManager 相机管理器实例。
 * @param isCameraMuted 如果方法调用成功，将返回相机是否静音的结果。返回true表示相机已静音，返回false表示未静音。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_IsCameraMuted(Camera_Manager* cameraManager, bool* isCameraMuted);

/**
 * @brief 创建捕获会话实例。
 * 
 * @param cameraManager 相机管理器实例。
 * @param captureSession 如果方法调用成功，将创建Camera_CaptureSession。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreateCaptureSession(Camera_Manager* cameraManager,
    Camera_CaptureSession** captureSession);

/**
 * @brief 创建相机输入实例。
 * 
 * @param cameraManager 相机管理器实例。
 * @param camera 用于创建Camera_Input实例的Camera_Device。
 * @param cameraInput 如果方法调用成功，将创建Camera_Input实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @permission ohos.permission.CAMERA
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreateCameraInput(Camera_Manager* cameraManager,
    const Camera_Device* camera, Camera_Input** cameraInput);

/**
 * @brief 创建具有位置和类型的相机输入实例。
 * 
 * @param cameraManager 相机管理器实例。
 * @param position 用于创建Camera_Input实例的相机位置。
 * @param type 用于创建Camera_Input实例的相机类型。
 * @param cameraInput 如果方法调用成功，将创建Camera_Input实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @permission ohos.permission.CAMERA
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreateCameraInput_WithPositionAndType(Camera_Manager* cameraManager,
    Camera_Position position, Camera_Type type, Camera_Input** cameraInput);

/**
 * @brief 创建预览输出实例。
 * 
 * @param cameraManager 相机管理器实例。
 * @param profile 用于创建Camera_PreviewOutput实例的相机流配置文件。
 * @param surfaceId 用于创建Camera_PreviewOutput实例的surfaceId。
 * @param previewOutput 如果方法调用成功，将创建Camera_PreviewOutput实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreatePreviewOutput(Camera_Manager* cameraManager, const Camera_Profile* profile,
    const char* surfaceId, Camera_PreviewOutput** previewOutput);

/**
 * @brief 创建在预配置流中使用的预览输出实例。
 * 
 * @param cameraManager 相机管理器实例。
 * @param surfaceId 用于创建Camera_PreviewOutput实例的surfaceId。
 * @param previewOutput 如果方法调用成功，将创建Camera_PreviewOutput实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_CreatePreviewOutputUsedInPreconfig(Camera_Manager* cameraManager,
    const char* surfaceId, Camera_PreviewOutput** previewOutput);

/**
 * @brief 创建延迟预览输出实例。使用结束后，必须调用{@link OH_PreviewOutput_Release}释放预览输出实例。
 *
 * @param cameraManager 相机管理器实例。
 * @param profile 用于创建Camera_PreviewOutput实例的相机流配置文件。
 * @param previewOutput 如果方法调用成功，将创建Camera_PreviewOutput实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 24
 */
Camera_ErrorCode OH_CameraManager_CreateDeferredPreviewOutput(const Camera_Manager* cameraManager,
    const Camera_Profile* profile, Camera_PreviewOutput** previewOutput);

/**
 * @brief 创建一个拍照输出实例。该接口只支持创建JPEG格式的拍照输出对象。
 * 
 * @param cameraManager 相机管理器实例。
 * @param profile 用于创建Camera_PhotoOutput实例的相机流配置文件。
 * @param surfaceId 用于创建Camera_PhotoOutput实例的surfaceId。
 * @param photoOutput 如果方法调用成功，将创建Camera_PhotoOutput实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreatePhotoOutput(Camera_Manager* cameraManager, const Camera_Profile* profile,
    const char* surfaceId, Camera_PhotoOutput** photoOutput);

/**
 * @brief 创建在预配置流中使用的照片输出实例。
 * 
 * @param cameraManager 相机管理器实例。
 * @param surfaceId 用于创建Camera_PhotoOutput实例的surfaceId。
 * @param photoOutput 如果方法调用成功，将创建Camera_PhotoOutput实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_CreatePhotoOutputUsedInPreconfig(Camera_Manager* cameraManager,
    const char* surfaceId, Camera_PhotoOutput** photoOutput);

/**
 * @brief 创建照片输出实例，调用此函数不需要surfaceId。
 * 
 * @param cameraManager 相机管理器实例。
 * @param profile 用于创建Camera_PhotoOutput实例的相机流配置文件。
 * @param photoOutput 如果方法调用成功，将创建Camera_PhotoOutput实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_CreatePhotoOutputWithoutSurface(Camera_Manager *cameraManager,
    const Camera_Profile *profile, Camera_PhotoOutput **photoOutput);

/**
 * @brief 创建一个录像输出实例。
 * 
 * @param cameraManager 相机管理器实例。
 * @param profile 用于创建Camera_VideoOutput实例的录像配置文件。
 * @param surfaceId 用于创建Camera_VideoOutput实例的surfaceId。
 * @param videoOutput 如果方法调用成功，将创建Camera_VideoOutput实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreateVideoOutput(Camera_Manager* cameraManager, const Camera_VideoProfile* profile,
    const char* surfaceId, Camera_VideoOutput** videoOutput);

/**
 * @brief 创建在预配置流中使用的视频输出实例。
 * 
 * @param cameraManager 相机管理器实例。
 * @param surfaceId 用于创建Camera_VideoOutput实例的surfaceId。
 * @param videoOutput 如果方法调用成功，将创建Camera_VideoOutput实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_CreateVideoOutputUsedInPreconfig(Camera_Manager* cameraManager,
    const char* surfaceId, Camera_VideoOutput** videoOutput);

/**
 * @brief 创建元数据输出实例。
 * 
 * @param cameraManager 相机管理器实例。
 * @param profile 用于创建Camera_MetadataOutput实例的元数据对象类型。
 * @param metadataOutput 如果方法调用成功，将创建Camera_MetadataOutput实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreateMetadataOutput(Camera_Manager* cameraManager,
    const Camera_MetadataObjectType* profile, Camera_MetadataOutput** metadataOutput);

/**
 * @brief 使用元数据对象类型数组创建元数据输出实例。
 * 
 * @param cameraManager 相机管理器实例。
 * @param metadataObjectTypes 用于创建Camera_MetadataOutput实例的元数据对象类型数组。
 * @param size 元数据对象类型数组长度。
 * @param metadataOutput 如果方法调用成功，将创建Camera_MetadataOutput实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 23
 */
Camera_ErrorCode OH_CameraManager_CreateMetadataOutputWithObjectTypes(Camera_Manager* cameraManager,
    const Camera_MetadataObjectType* metadataObjectTypes, uint32_t size, Camera_MetadataOutput** metadataOutput);

/**
 * @brief 获取特定相机支持的场景模式。
 * 
 * @param camera 要查询的Camera_Device。
 * @param sceneModes 如果方法调用成功，将记录支持的场景模式列表。
 * @param size 如果方法调用成功，将记录支持的场景模式列表大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_GetSupportedSceneModes(Camera_Device* camera,
    Camera_SceneMode** sceneModes, uint32_t* size);

/**
 * @brief 删除场景模式。
 * 
 * @param cameraManager 相机管理器实例。
 * @param sceneModes 要删除的场景模式列表。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_DeleteSceneModes(Camera_Manager* cameraManager, Camera_SceneMode* sceneModes);

/**
 * @brief 检查设备是否支持手电筒。
 * 
 * @param cameraManager 相机管理器实例。
 * @param isTorchSupported 设备是否支持手电筒。返回true表示设备支持手电筒，返回false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_IsTorchSupported(Camera_Manager* cameraManager,
    bool* isTorchSupported);

/**
 * @brief 检查设备是否支持指定的手电筒模式。
 * 
 * @param cameraManager 相机管理器实例。
 * @param torchMode 要检查的相机手电筒模式。
 * @param isTorchSupported 设备是否支持指定的手电筒模式。返回true表示设备支持该模式，返回false表示不支持。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_IsTorchSupportedByTorchMode(Camera_Manager* cameraManager,
    Camera_TorchMode torchMode, bool* isTorchSupported);

/**
 * @brief 设置相机手电筒模式。
 * 
 * @param cameraManager 相机管理器实例。
 * @param torchMode 要设置的相机手电筒模式。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_SetTorchMode(Camera_Manager* cameraManager,
    Camera_TorchMode torchMode);

/**
 * @brief 检查设备是否支持手电筒亮度控制。
 * 
 * @param cameraManager 相机管理器实例。
 * @param isTorchLevelControlSupported 设备是否支持手电筒亮度控制。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 26.0.0
 */
Camera_ErrorCode OH_CameraManager_IsTorchLevelControlSupported(const Camera_Manager* cameraManager,
    bool* isTorchLevelControlSupported);

/**
 * @brief 将手电筒模式设置为打开，并设置亮度值。
 * 
 * @param cameraManager 相机管理器实例。
 * @param torchLevel 目标亮度水平。取值范围为[0.0, 1.0]。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 26.0.0
 */
Camera_ErrorCode OH_CameraManager_SetTorchModeOnWithLevel(Camera_Manager* cameraManager,
    double torchLevel);

/**
 * @brief 根据相机位置和相机类型查询指定的相机。
 * <br>获取指定{@link Camera_Position}和{@link Camera_Type}的相机镜头，如果该接口返回值为CAMERA_SERVICE_FATAL_ERROR，表示当前设备未查询到该镜头。
 *
 * @param cameraManager 相机管理器实例。
 * @param position 要查询的相机位置。
 * @param type 要查询的相机类型。
 * @param camera 要查询的Camera_Device。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 18
 */
Camera_ErrorCode OH_CameraManager_GetCameraDevice(Camera_Manager* cameraManager, Camera_Position position,
    Camera_Type type, Camera_Device* camera);

/**
 * @brief 根据相机位置、相机类型数组和连接类型查询符合条件的相机列表。
 * 
 * @param cameraManager 相机管理器实例。
 * @param deviceQueryInfo 相机设备的查询信息实例。
 * @param cameraSize 查询的所支持的Camera_Device列表大小。
 * @param cameras 查询的所支持的Camera_Device列表。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 23
 */
Camera_ErrorCode OH_CameraManager_GetCameraDevices(Camera_Manager* cameraManager,
    Camera_DeviceQueryInfo* deviceQueryInfo, uint32_t* cameraSize, Camera_Device** cameras);

/**
 * @brief 删除指定相机设备。
 * 
 * @param cameraManager 相机管理器实例。
 * @param cameras 待删除的Camera_Device列表。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 23
 */
Camera_ErrorCode OH_CameraManager_DeleteCameraDevices(Camera_Manager* cameraManager, Camera_Device* cameras);

/**
 * @brief 获取指定相机的并发信息。
 *
 * @param cameraManager 相机管理器实例。
 * @param camera 用于查询的Camera_Device相机设备列表，推荐设置为包含{@link OH_CameraManager_GetCameraDevice}获取的前置与后置两个相机设备的相机设备列表。
 * @param deviceSize 用于查询的相机设备列表长度, 必须设置为2（表示前置与后置两个用于并发的相机设备）。
 * @param cameraConcurrentInfo 查询到的相机并发能力数组Camera_ConcurrentInfo，作为入参应当默认设置为空。
 *     <br>如果相机支持并发，cameraConcurrentInfo会被赋值为查询到的相机并发能力数组Camera_ConcurrentInfo。
 *     <br>如果相机不支持并发，不会对cameraConcurrentInfo进行更改，并且返回错误码{@link Camera_ErrorCode}.CAMERA_SERVICE_FATAL_ERROR。
 * @param infoSize 查询到的相机并发能力数组长度，作为入参应当默认设置为0。
 *     <br>如果相机支持并发，infoSize会被赋值为查询到的相机并发能力数组长度。
 *     <br>如果相机不支持并发，不会对infoSize进行更改，并且返回错误码{@link Camera_ErrorCode}.CAMERA_SERVICE_FATAL_ERROR。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常，或者相机不支持并发。
 * @since 18
 */
Camera_ErrorCode OH_CameraManager_GetCameraConcurrentInfos(Camera_Manager* cameraManager, const Camera_Device* camera,
    uint32_t deviceSize,
    Camera_ConcurrentInfo** cameraConcurrentInfo,
    uint32_t* infoSize);
#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_CAMERA_MANAGER_H
/** @} */

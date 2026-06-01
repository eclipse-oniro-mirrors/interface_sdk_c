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
 * @brief The file declares the camera manager concepts.
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
 * @brief Defines the callback defined in the {@link CameraManager_Callbacks} struct and used to report the camera
 * manager status.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance that transfers the callback.
 * @param status Pointer to the status information of each camera.
 * @since 11
 */
typedef void (*OH_CameraManager_StatusCallback)(Camera_Manager* cameraManager, Camera_StatusInfo* status);

/**
 * @brief Defines the callback to listen for flashlight status changes.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance that transfers the callback.
 * @param status Pointer to the flashlight status information.
 * @since 12
 */
typedef void (*OH_CameraManager_TorchStatusCallback)(Camera_Manager* cameraManager, Camera_TorchStatusInfo* status);

/**
 * @brief Defines the callback to listen for fold status changes of the camera manager.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance that transfers the callback.
 * @param foldStatusInfo Pointer to the fold status information of the device.
 * @since 13
 */
typedef void (*OH_CameraManager_OnFoldStatusInfoChange)(Camera_Manager* cameraManager,
    Camera_FoldStatusInfo* foldStatusInfo);

/**
 * @brief The struct describes the callbacks used to listen for camera status changes.
 * 
 * @see OH_CameraManager_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct CameraManager_Callbacks {
    /**
     * Camera status change event.
     */
    OH_CameraManager_StatusCallback onCameraStatus;
} CameraManager_Callbacks;

/**
 * @brief Registers a callback to listen for camera status changes.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_RegisterCallback(Camera_Manager* cameraManager, CameraManager_Callbacks* callback);

/**
 * @brief Unregisters the callback used to listen for camera status changes.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_UnregisterCallback(Camera_Manager* cameraManager, CameraManager_Callbacks* callback);

/**
 * @brief Registers a callback to listen for flashlight status changes.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param torchStatusCallback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_RegisterTorchStatusCallback(Camera_Manager* cameraManager,
    OH_CameraManager_TorchStatusCallback torchStatusCallback);

/**
 * @brief Unregisters the callback used to listen for flashlight status changes.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param torchStatusCallback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_UnregisterTorchStatusCallback(Camera_Manager* cameraManager,
    OH_CameraManager_TorchStatusCallback torchStatusCallback);

/**
 * @brief Registers a callback to listen for fold status changes.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param foldStatusInfoCallback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 13
 */
Camera_ErrorCode OH_CameraManager_RegisterFoldStatusInfoCallback(Camera_Manager* cameraManager,
    OH_CameraManager_OnFoldStatusInfoChange foldStatusInfoCallback);

/**
 * @brief Unregisters the callback used to listen for fold status changes.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param foldStatusInfoCallback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 13
 */
Camera_ErrorCode OH_CameraManager_UnregisterFoldStatusInfoCallback(Camera_Manager* cameraManager,
    OH_CameraManager_OnFoldStatusInfoChange foldStatusInfoCallback);

/**
 * @brief Obtains the supported cameras.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param cameras Double pointer to the list of cameras, which are defined in the Camera_Device struct, if the function
 * is successfully called.
 * @param size Pointer to the size of the list of cameras.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_GetSupportedCameras(Camera_Manager* cameraManager,
    Camera_Device** cameras, uint32_t* size);

/**
 * @brief Deletes supported cameras.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param cameras Pointer to a list of cameras, which are defined in the Camera_Device struct.
 * @param size The size of the list of cameras.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_DeleteSupportedCameras(Camera_Manager* cameraManager,
    Camera_Device* cameras, uint32_t size);

/**
 * @brief Obtains the output capability supported by a camera.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param cameras the {@link Camera_Device} to be queried.
 * @param cameraOutputCapability Double pointer to the output capability, which is defined in the
 * Camera_OutputCapability struct, if the function is successfully called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_GetSupportedCameraOutputCapability(Camera_Manager* cameraManager,
    const Camera_Device* camera, Camera_OutputCapability** cameraOutputCapability);

/**
 * @brief Obtains the output capability supported by a camera in the specified mode.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param camera Pointer to the **Camera_Device** instance.
 * @param sceneMode Scene mode.
 * @param cameraOutputCapability Double pointer to output capability, which is defined in the **Camera_OutputCapability*
 * * struct, if the function is successfully called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_GetSupportedCameraOutputCapabilityWithSceneMode(Camera_Manager* cameraManager,
    const Camera_Device* camera, Camera_SceneMode sceneMode, Camera_OutputCapability** cameraOutputCapability);

/**
 * @brief Obtains the complete output capabilities supported by a specified camera in a specified mode, including YUV,
 * HEIF, and HDR. Before using YUV, HEIF, or HDR, you need to explicitly call this method to ensure that the complete
 * output capabilities are obtained.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param camera Pointer to the **Camera_Device** instance.
 * @param sceneMode Scene mode.
 * @param cameraOutputCapability Double pointer to output capability, which is defined in the **Camera_OutputCapability*
 * * struct, if the function is successfully called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 23
 */
Camera_ErrorCode OH_CameraManager_GetSupportedFullCameraOutputCapabilityWithSceneMode(Camera_Manager* cameraManager,
    const Camera_Device* camera, Camera_SceneMode sceneMode, Camera_OutputCapability** cameraOutputCapability);

/**
 * @brief Deletes the output capability supported by a camera.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param cameraOutputCapability Pointer to the output capability, which is defined in the **Camera_OutputCapability**
 * struct.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_DeleteSupportedCameraOutputCapability(Camera_Manager* cameraManager,
    Camera_OutputCapability* cameraOutputCapability);

/**
 * @brief Checks whether a camera is muted.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param isCameraMuted Pointer to the check result for whether the camera is muted, if the function is successfully
 * called. **true** if muted, **false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_IsCameraMuted(Camera_Manager* cameraManager, bool* isCameraMuted);

/**
 * @brief Creates a **CaptureSession** instance.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param captureSession Double pointer to the **Camera_CaptureSession** instance created, if the function is
 * successfully called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreateCaptureSession(Camera_Manager* cameraManager,
    Camera_CaptureSession** captureSession);

/**
 * @brief Creates a **Camera_Input** instance.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param camera Pointer to the **Camera_Device** instance.
 * @param cameraInput Double pointer to the **Camera_Input** instance created, if the function is successfully called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @permission ohos.permission.CAMERA
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreateCameraInput(Camera_Manager* cameraManager,
    const Camera_Device* camera, Camera_Input** cameraInput);

/**
 * @brief Creates a **Camera_Input** instance with the specified camera position and type.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param position Camera position.
 * @param type Camera type.
 * @param cameraInput Double pointer to the **Camera_Input** instance created, if the function is successfully called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @permission ohos.permission.CAMERA
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreateCameraInput_WithPositionAndType(Camera_Manager* cameraManager,
    Camera_Position position, Camera_Type type, Camera_Input** cameraInput);

/**
 * @brief Creates a **PreviewOutput** instance.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param profile Pointer to the profile used for creating the **Camera_PreviewOutput** instance.
 * @param surfaceId Pointer to the surface ID used for creating the **Camera_PreviewOutput** instance.
 * @param previewOutput Double pointer to the **Camera_PreviewOutput** instance created, if the function is
 * successfully called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreatePreviewOutput(Camera_Manager* cameraManager, const Camera_Profile* profile,
    const char* surfaceId, Camera_PreviewOutput** previewOutput);

/**
 * @brief Creates a **PreviewOutput** instance to be used in a preconfiguration stream.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param surfaceId Pointer to the surface ID used for creating the **Camera_PreviewOutput** instance.
 * @param previewOutput Double pointer to the **Camera_PreviewOutput** instance created, if the function is
 * successfully called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_CreatePreviewOutputUsedInPreconfig(Camera_Manager* cameraManager,
    const char* surfaceId, Camera_PreviewOutput** previewOutput);

/**
 * @brief Create a defer preview output instance.The caller must call {@link OH_PreviewOutput_Release}
 *     to free the memory of the output.
 *
 * @param cameraManager the {@link Camera_Manager} instance.
 * @param profile the {@link Camera_Profile} to create {@link Camera_PreviewOutput}.
 * @param previewOutput the {@link Camera_PreviewOutput} will be created if the method call succeeds.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_SERVICE_FATAL_ERROR} if camera service fatal error.
 * @since 24
 */
Camera_ErrorCode OH_CameraManager_CreateDeferredPreviewOutput(const Camera_Manager* cameraManager,
    const Camera_Profile* profile, Camera_PreviewOutput** previewOutput);

/**
 * @brief Creates a **PhotoOutput** instance. This API can only be used to create a **PhotoOutput** object in JPEG
 * format.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param profile Pointer to the profile used for creating the **Camera_PhotoOutput** instance.
 * @param surfaceId Pointer to the surface ID used for creating the **Camera_PhotoOutput** instance.
 * @param photoOutput Double pointer to the **Camera_PhotoOutput** instance created, if the function is successfully
 * called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreatePhotoOutput(Camera_Manager* cameraManager, const Camera_Profile* profile,
    const char* surfaceId, Camera_PhotoOutput** photoOutput);

/**
 * @brief Creates a **PhotoOutput** instance to be used in a preconfiguration stream.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param surfaceId Pointer to the surface ID used for creating the **Camera_PhotoOutput** instance.
 * @param photoOutput Double pointer to the **Camera_PhotoOutput** instance created, if the function is successfully
 * called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_CreatePhotoOutputUsedInPreconfig(Camera_Manager* cameraManager,
    const char* surfaceId, Camera_PhotoOutput** photoOutput);

/**
 * @brief Creates a **PhotoOutput** instance. **surfaceId** is not required in this function.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param profile Pointer to the profile used for creating the **Camera_PhotoOutput** instance.
 * @param photoOutput Double pointer to the **Camera_PhotoOutput** instance created, if the function is successfully
 * called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_CreatePhotoOutputWithoutSurface(Camera_Manager *cameraManager,
    const Camera_Profile *profile, Camera_PhotoOutput **photoOutput);

/**
 * @brief Creates a **VideoOutput** instance.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param profile Pointer to the profile for creating the **Camera_VideoOutput** instance.
 * @param surfaceId Pointer to the surface ID used for creating the **Camera_VideoOutput** instance.
 * @param videoOutput Double pointer to the **Camera_VideoOutput** instance created, if the function is successfully
 * called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreateVideoOutput(Camera_Manager* cameraManager, const Camera_VideoProfile* profile,
    const char* surfaceId, Camera_VideoOutput** videoOutput);

/**
 * @brief Creates a **VideoOutput** instance to be used in a preconfiguration stream.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param surfaceId Pointer to the surface ID used for creating the **Camera_VideoOutput** instance.
 * @param videoOutput Double pointer to the **Camera_VideoOutput** instance created, if the function is successfully
 * called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_CreateVideoOutputUsedInPreconfig(Camera_Manager* cameraManager,
    const char* surfaceId, Camera_VideoOutput** videoOutput);

/**
 * @brief Creates a **MetadataOutput** instance.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param profile Pointer to the metadata object type used for creating the **Camera_MetadataOutput** instance.
 * @param metadataOutput Double pointer to the **Camera_MetadataOutput** instance created, if the function is
 * successfully called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_CameraManager_CreateMetadataOutput(Camera_Manager* cameraManager,
    const Camera_MetadataObjectType* profile, Camera_MetadataOutput** metadataOutput);

/**
 * @brief Creates a **metadataOutput** instance using an array of metadata object types.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param metadataObjectTypes Pointer to the metadata object types used for creating the **Camera_MetadataOutput**
 * instance.
 * @param size Length of the metadata object type array.
 * @param metadataOutput Double pointer to the **Camera_MetadataOutput** instance created, if the function is
 * successfully called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 23
 */
Camera_ErrorCode OH_CameraManager_CreateMetadataOutputWithObjectTypes(Camera_Manager* cameraManager,
    const Camera_MetadataObjectType* metadataObjectTypes, uint32_t size, Camera_MetadataOutput** metadataOutput);

/**
 * @brief Obtains the scene modes supported by a camera.
 * 
 * @param camera Pointer to the **Camera_Device** instance.
 * @param sceneModes Double pointer to the list of scene modes, which are defined in the Camera_SceneMode struct, if
 * the function is successfully called.
 * @param size Pointer to the size of the list of scene modes.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_GetSupportedSceneModes(Camera_Device* camera,
    Camera_SceneMode** sceneModes, uint32_t* size);

/**
 * @brief Deletes scene modes.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param sceneModes Pointer to the list of scene modes to delete.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_DeleteSceneModes(Camera_Manager* cameraManager, Camera_SceneMode* sceneModes);

/**
 * @brief Checks whether the device supports the flashlight.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param isTorchSupported Pointer to the check result for the support of the flashlight. **true** if supported, **
 * false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_IsTorchSupported(Camera_Manager* cameraManager,
    bool* isTorchSupported);

/**
 * @brief Checks whether the device supports the specified flashlight mode.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param torchMode Flashlight mode to check.
 * @param isTorchSupported Pointer to the check result for the support of the flashlight mode. **true** if supported, **
 * false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_IsTorchSupportedByTorchMode(Camera_Manager* cameraManager,
    Camera_TorchMode torchMode, bool* isTorchSupported);

/**
 * @brief Sets a flashlight mode.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param torchMode Flashlight mode to set.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_CameraManager_SetTorchMode(Camera_Manager* cameraManager,
    Camera_TorchMode torchMode);

/**
 * @brief Checks whether the device supports flashlight brightness control.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param isTorchLevelControlSupported Whether the device supports flashlight brightness control.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 26.0.0
 */
Camera_ErrorCode OH_CameraManager_IsTorchLevelControlSupported(const Camera_Manager* cameraManager,
    bool* isTorchLevelControlSupported);

/**
 * @brief Turns on the flashlight and sets the brightness level.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param torchLevel Target brightness level. The value range is [0.0, 1.0].
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 26.0.0
 */
Camera_ErrorCode OH_CameraManager_SetTorchModeOnWithLevel(const Camera_Manager* cameraManager,
    double torchLevel);

/**
 * @brief Queries a specified device based on position and type.
 *
 * @param cameraManager the {@link Camera_Manager} instance.
 * @param position the {@link Camera_Position} instance.
 * @param type the {@link Camera_Type} instance.
 * @param camera the {@link Camera_Device} to be set.
 * @return {@link #CAMERA_OK} if the method call succeeds.
 *         {@link #CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link #CAMERA_SERVICE_FATAL_ERROR} if camera service fatal error.
 * @since 18
 */
Camera_ErrorCode OH_CameraManager_GetCameraDevice(Camera_Manager* cameraManager, Camera_Position position,
    Camera_Type type, Camera_Device* camera);

/**
 * @brief Obtains the list of cameras that meet the search criteria based on the camera position, camera types, and
 * connection type.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param deviceQueryInfo Camera device query information instance.
 * @param cameraSize Size of the list of supported cameras.
 * @param cameras List of supported cameras.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 23
 */
Camera_ErrorCode OH_CameraManager_GetCameraDevices(Camera_Manager* cameraManager,
    Camera_DeviceQueryInfo* deviceQueryInfo, uint32_t* cameraSize, Camera_Device** cameras);

/**
 * @brief Deletes the specified camera.
 * 
 * @param cameraManager Pointer to the **Camera_Manager** instance.
 * @param cameras List of cameras to be deleted.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 23
 */
Camera_ErrorCode OH_CameraManager_DeleteCameraDevices(Camera_Manager* cameraManager, Camera_Device* cameras);

/**
 * @brief Obtains the concurrent information of specified cameras, the empty return means concurrency is not supported.
 *
 * @param cameraManager the {@link Camera_Manager} instance.
 * @param camera the {@link Camera_Device} instance.
 * @param deviceSize length of the input device array.
 * @param cameraConcurrentInfo the {@link Camera_ConcurrentInfo} to be set.
 * @param infoSize length of the returned concurrency information array.
 * @return {@link #CAMERA_OK} if the method call succeeds.
 *         {@link #CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link #CAMERA_SERVICE_FATAL_ERROR} if camera service fatal error.
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

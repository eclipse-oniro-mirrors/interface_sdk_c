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
 * @brief The file declares the metadata output concepts.
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
#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines a struct for the metadata output object.<br>You can use the {@link OH_CameraManager_CreateMetadataOutput}
 *  method and **OH_CameraManager_CreateMetadataOutputWithObjectTypes** method (supported since API version 23) to
 * create a pointer.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_MetadataOutput Camera_MetadataOutput;

/**
 * @brief Defines the callback defined in the {@link MetadataOutput_Callbacks} struct and used to report metadata
 * output data.
 * 
 * @param metadataOutput Pointer to the MetadataOutput instance that transfers the callback.
 * @param metadataObject Pointer to the metadata output data.
 * @param size Size of the metadata object.
 * @since 11
 */
typedef void (*OH_MetadataOutput_OnMetadataObjectAvailable)(Camera_MetadataOutput* metadataOutput,
    Camera_MetadataObject* metadataObject, uint32_t size);

/**
 * @brief Defines the callback defined in the {@link MetadataOutput_Callbacks} struct and used to report metadata
 * output errors.
 * 
 * @param metadataOutput Pointer to the MetadataOutput instance that transfers the callback.
 * @param errorCode Error code reported during metadata output.
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 11
 */
typedef void (*OH_MetadataOutput_OnError)(Camera_MetadataOutput* metadataOutput, Camera_ErrorCode errorCode);

/**
 * @brief The struct describes the callbacks related to metadata output.
 * 
 * @see OH_MetadataOutput_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct MetadataOutput_Callbacks {
    /**
     * Callback to report the metadata output result.
     */
    OH_MetadataOutput_OnMetadataObjectAvailable onMetadataObjectAvailable;

    /**
     * Callback to report a metadata output error.
     */
    OH_MetadataOutput_OnError onError;
} MetadataOutput_Callbacks;

/**
 * @brief Registers a callback to listen for metadata output events.
 * 
 * @param metadataOutput Pointer to a MetadataOutput instance.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_MetadataOutput_RegisterCallback(Camera_MetadataOutput* metadataOutput,
    MetadataOutput_Callbacks* callback);

/**
 * @brief Unregisters the callback used to listen for metadata output events.
 * 
 * @param metadataOutput Pointer to a MetadataOutput instance.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_MetadataOutput_UnregisterCallback(Camera_MetadataOutput* metadataOutput,
    MetadataOutput_Callbacks* callback);

/**
 * @brief Starts metadata output.
 * 
 * @param metadataOutput Pointer to the MetadataOutput instance to start.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_MetadataOutput_Start(Camera_MetadataOutput* metadataOutput);

/**
 * @brief Stops metadata output.
 * 
 * @param metadataOutput Pointer to the MetadataOutput instance to stop.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_MetadataOutput_Stop(Camera_MetadataOutput* metadataOutput);

/**
 * @brief Releases a MetadataOutput instance.
 * 
 * @param metadataOutput Pointer to the MetadataOutput instance to release.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_MetadataOutput_Release(Camera_MetadataOutput* metadataOutput);

/**
 * @brief Adds the metadata object types.
 * 
 * @param metadataOutput Pointer to a MetadataOutput instance.
 * @param types Array of metadata object types to be added to the **Camera_MetadataOutput** instance.
 * @param size Length of the metadata object type array.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 23
 */
Camera_ErrorCode OH_MetadataOutput_AddMetadataObjectTypes (Camera_MetadataOutput* metadataOutput, Camera_MetadataObjectType* types, uint32_t size);

/**
 * @brief Removes the metadata object types.
 * 
 * @param metadataOutput Pointer to a MetadataOutput instance.
 * @param types Array of metadata object types removed from the **Camera_MetadataOutput** instance.
 * @param size Length of the metadata object type array.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 23
 */
Camera_ErrorCode OH_MetadataOutput_RemoveMetadataObjectTypes (Camera_MetadataOutput* metadataOutput, Camera_MetadataObjectType* types, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_METADATAOUTPUT_H
/** @} */

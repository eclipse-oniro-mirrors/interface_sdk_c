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
#include "metadata_object_ext.h"

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
 * @brief Defines the callback used to listen for metadata object ext available.
 *
 * @param context Pointer to the context provided by user.
 * @param metadataObjectExt Pointer to the metadata output data.
 * @param size Size of the metadata object ext.
 * @since 26.0.0
 */
typedef void (*OH_MetadataOutput_OnMetadataObjectExtAvailable)(void* context,
    OH_Camera_MetadataObjectExt** metadataObjectExt, uint32_t size);

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
 * @brief Defines the callback used to listen for error ext event.
 *
 * @param context Pointer to the context provided by user.
 * @param errorCode Error code reported during metadata output.
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 26.0.0
 */
typedef void (*OH_MetadataOutput_OnErrorExt)(void* context, Camera_ErrorCode errorCode);

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
 * @brief Registers a callback to listen for {@link OH_Camera_MetadataObjectExt} events.
 * The callback can be unregistered by {@link OH_MetadataOutput_UnregisterMetadataObjectExtAvailableCallback}.
 *
 * @param metadataOutput Pointer to the {@link Camera_MetadataOutput} instance.
 * @param context Pointer to the context provided by user.
 * @param callback Pointer to the {@link OH_MetadataOutput_OnMetadataObjectExtAvailable} callback function.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataOutput_RegisterMetadataObjectExtAvailableCallback(Camera_MetadataOutput* metadataOutput,
    void* context, OH_MetadataOutput_OnMetadataObjectExtAvailable callback);

/**
 * @brief Unregisters the callback used to listen for metadata object ext events.
 *
 * @param metadataOutput Pointer to a MetadataOutput instance.
 * @param context Pointer to the context provided by user.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataOutput_UnregisterMetadataObjectExtAvailableCallback(Camera_MetadataOutput* metadataOutput,
    void* context, OH_MetadataOutput_OnMetadataObjectExtAvailable callback);

/**
 * @brief Registers a callback to listen for error ext events.
 * The callback can be unregistered by {@link OH_MetadataOutput_UnregisterErrorExtCallback}.
 *
 * @param metadataOutput Pointer to the {@link Camera_MetadataOutput} instance.
 * @param context Pointer to the context provided by user.
 * @param callback Pointer to the {@link OH_MetadataOutput_OnErrorExt} callback function.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataOutput_RegisterErrorExtCallback(Camera_MetadataOutput* metadataOutput, void* context,
    OH_MetadataOutput_OnErrorExt callback);

/**
 * @brief Unregisters the callback used to listen for error ext events.
 *
 * @param metadataOutput Pointer to a MetadataOutput instance.
 * @param context Pointer to the context provided by user.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataOutput_UnregisterErrorExtCallback(Camera_MetadataOutput* metadataOutput, void* context,
    OH_MetadataOutput_OnErrorExt callback);

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

/**
 * @brief Checks whether the lock metadata object tracking is supported.
 *
 * @param metadataOutput Pointer to a MetadataOutput instance.
 * @return **true** if supported, **false** otherwise.
 * @since 26.0.0
 */
bool OH_MetadataOutput_IsLockMetadataObjectTrackingSupported(const Camera_MetadataOutput* metadataOutput);

/**
 * @brief Lock metadata object tracking, can be unlocked by {@link OH_MetadataOutput_UnlockMetadataObjectTracking}.
 *
 * @param metadataOutput Pointer to a MetadataOutput instance.
 * @param pointOfInterest Pointer to the point of interest.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataOutput_LockMetadataObjectTracking(Camera_MetadataOutput* metadataOutput,
    Camera_Point* pointOfInterest);

/**
 * @brief Unlock metadata object tracking.
 *
 * @param metadataOutput Pointer to a MetadataOutput instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataOutput_UnlockMetadataObjectTracking(Camera_MetadataOutput* metadataOutput);
#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_METADATAOUTPUT_H
/** @} */

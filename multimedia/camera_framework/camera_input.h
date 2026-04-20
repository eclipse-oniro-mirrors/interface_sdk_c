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
 * @brief The file declares the camera input concepts.
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
#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct describes the camera input object.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Input Camera_Input;

/**
 * @brief Defines the callback defined in the {@link CameraInput_Callbacks} struct and used to report camera input
 * errors.
 * 
 * @param cameraInput Pointer to the target Camera_Input instance.
 * @param errorCode Error code reported during camera input and defined in the Camera_ErrorCode struct.
 * @see CAMERA_CONFLICT_CAMERA
 * @see CAMERA_DEVICE_DISABLED
 * @see CAMERA_DEVICE_PREEMPTED
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 11
 */
typedef void (*OH_CameraInput_OnError)(const Camera_Input* cameraInput, Camera_ErrorCode errorCode);

/**
 * @brief The struct describes the callbacks used to listen for camera input errors.
 * 
 * @see OH_CameraInput_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct CameraInput_Callbacks {
    /**
     * Camera input error event.
     */
    OH_CameraInput_OnError onError;
} CameraInput_Callbacks;

/**
 * @brief Registers a callback to listen for camera input events.
 * 
 * @param cameraInput Pointer to the target Camera_Input instance.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_CameraInput_RegisterCallback(Camera_Input* cameraInput, CameraInput_Callbacks* callback);

/**
 * @brief Unregisters the callback used to listen for camera input events.
 * 
 * @param cameraInput Pointer to the target Camera_Input instance.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_CameraInput_UnregisterCallback(Camera_Input* cameraInput, CameraInput_Callbacks* callback);

/**
 * @brief Opens a camera.
 * 
 * @param cameraInput Pointer to the target Camera_Input instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_CONFLICT_CAMERA**: The camera cannot be used due to a conflict.
 *     <br>**CAMERA_DEVICE_DISABLED**: The camera is disabled due to security reasons.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_CameraInput_Open(Camera_Input* cameraInput);

/**
 * @brief Opens a camera in secure mode.
 * 
 * @param cameraInput Pointer to the target Camera_Input instance.
 * @param secureSeqId Pointer to the sequence ID of the camera.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_CONFLICT_CAMERA**: The camera cannot be used due to a conflict.
 *     <br>**CAMERA_DEVICE_DISABLED**: The camera is disabled due to security reasons.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_CameraInput_OpenSecureCamera(Camera_Input* cameraInput, uint64_t* secureSeqId);

/**
 * @brief Closes a camera.
 * 
 * @param cameraInput Pointer to the target Camera_Input instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_CameraInput_Close(Camera_Input* cameraInput);

/**
 * @brief Releases a Camera_Input instance.
 * Either this function or {@link OH_CameraInput_Close} needs to be called.
 * 
 * @param cameraInput Pointer to the target Camera_Input instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_CameraInput_Release(Camera_Input* cameraInput);

/**
 * @brief Checks whether the physical camera orientation is adjustable in different fold states of the device.
 * 
 * @param {CameraInput} cameraInput the {@link Camera_Input} instance.
 * @param {bool} isVariable the result of whether physical camera orientation is variable.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 22
 */
Camera_ErrorCode OH_CameraInput_IsPhysicalCameraOrientationVariable(Camera_Input* cameraInput, bool* isVariable);

/**
 * @brief Obtains the physical camera orientation in the current fold state of the device.
 * 
 * @param cameraInput Pointer to the target Camera_Input instance.
 * @param orientation Pointer to the physical camera orientation if the operation is successful.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 22
 */
Camera_ErrorCode OH_CameraInput_GetPhysicalCameraOrientation(Camera_Input* cameraInput, uint32_t* orientation);

/**
 * @brief Enables or disables the use of the physical camera orientation.
 * 
 * @param cameraInput Pointer to the target Camera_Input instance.
 * @param isUsed Whether to enable the use of the physical camera orientation. **true** to enable, **false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 22
 */
Camera_ErrorCode OH_CameraInput_UsePhysicalCameraOrientation(Camera_Input* cameraInput, bool isUsed);

/**
 * @brief Defines a callback used to return the check result for whether a camera lens is blocked or dirty.
 * 
 * @param cameraInput Pointer to the target Camera_Input instance.
 * @param occlusionDetectionResult Check result for whether a camera lens is blocked or dirty.
 * @since 23
 */
typedef void (*OH_CameraInput_OnOcclusionDetectionCallback)(const Camera_Input* cameraInput,
    Camera_OcclusionDetectionResult occlusionDetectionResult);

/**
 * @brief Registers a callback used to check whether a camera lens is blocked or dirty.
 * 
 * @param cameraInput Pointer to the target Camera_Input instance.
 * @param occlusionDetectionCallback Callback used to check whether a camera lens is blocked or dirty.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 23
 */
Camera_ErrorCode OH_CameraInput_RegisterOcclusionDetectionCallback(Camera_Input* cameraInput,
    OH_CameraInput_OnOcclusionDetectionCallback occlusionDetectionCallback);

/**
 * @brief Unregisters the callback used to check whether a camera lens is blocked or dirty.
 * 
 * @param cameraInput Pointer to the target Camera_Input instance.
 * @param occlusionDetectionCallback Callback used to check whether a camera lens is blocked or dirty.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 23
 */
Camera_ErrorCode OH_CameraInput_UnregisterOcclusionDetectionCallback(Camera_Input* cameraInput,
    OH_CameraInput_OnOcclusionDetectionCallback occlusionDetectionCallback);

/**
 * @brief Opens the camera based on the specified concurrency type.
 * 
 * @param cameraInput Pointer to the target Camera_Input instance.
 * @param type Concurrency type.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_CONFLICT_CAMERA**: The camera cannot be used due to a conflict.
 *     <br>**CAMERA_DEVICE_DISABLED**: The camera is disabled due to security reasons.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 18
 */
Camera_ErrorCode OH_CameraInput_OpenConcurrentCameras(Camera_Input* cameraInput, Camera_ConcurrentType type);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_CAMERA_INPUT_H
/** @} */

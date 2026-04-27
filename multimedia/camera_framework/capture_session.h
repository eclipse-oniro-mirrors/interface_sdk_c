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
 * @brief The file declares the capture session concepts.
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
 * @brief The struct describes the capture session object.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_CaptureSession Camera_CaptureSession;

/**
 * @brief Defines the callback defined in the {@link CaptureSession_Callbacks} struct and used to report focus status
 * changes of a capture session.
 * 
 * @param session Pointer to the Camera_CaptureSession instance that transfers the callback.
 * @param focusState Focus status.
 * @since 11
 */
typedef void (*OH_CaptureSession_OnFocusStateChange)(Camera_CaptureSession* session, Camera_FocusState focusState);

/**
 * @brief Defines the callback defined in the {@link CaptureSession_Callbacks} struct and used to report capture
 * session errors.
 * 
 * @param session Pointer to the Camera_CaptureSession instance that transfers the callback.
 * @param errorCode Error code reported in a capture session.
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 11
 */
typedef void (*OH_CaptureSession_OnError)(Camera_CaptureSession* session, Camera_ErrorCode errorCode);

/**
 * @brief Defines the callback invoked when smooth zoom is triggered for a capture session.
 * 
 * @param session Pointer to the Camera_CaptureSession instance that transfers the callback.
 * @param smoothZoomInfo Pointer to the smooth zoom information passed by the callback.
 * @since 12
 */
typedef void (*OH_CaptureSession_OnSmoothZoomInfo)(Camera_CaptureSession* session,
    Camera_SmoothZoomInfo* smoothZoomInfo);

/**
 * @brief Capture session device switch status callback.
 *
 * @param session the {@link Camera_CaptureSession} which deliver the callback.
 * @param autoDeviceSwitchStatusInfo the {@link Camera_AutoDeviceSwitchStatusInfo} which delivered by the callback.
 * @since 13
 */
typedef void (*OH_CaptureSession_OnAutoDeviceSwitchStatusChange)(Camera_CaptureSession* session,
    Camera_AutoDeviceSwitchStatusInfo* autoDeviceSwitchStatusInfo);

/**
 * @brief Defines the callback used to listen for capture system pressure level changes.
 * 
 * @param session Pointer to the Camera_CaptureSession instance that transfers the callback.
 * @param systemPressureLevel Pointer to the system pressure level passed by the callback.
 * @since 20
 */
typedef void (*OH_CaptureSession_OnSystemPressureLevelChange)(Camera_CaptureSession* session,
    Camera_SystemPressureLevel systemPressureLevel);

/**
 * @brief The struct describes the callbacks related to a capture session.
 * 
 * @see OH_CaptureSession_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct CaptureSession_Callbacks {
    /**
     * Callback to report a focus status change of a capture session.
     */
    OH_CaptureSession_OnFocusStateChange onFocusStateChange;

    /**
     * Callback to report a capture session error.
     */
    OH_CaptureSession_OnError onError;
} CaptureSession_Callbacks;

/**
 * @brief Registers a callback to listen for capture session events.
 * 
 * @param session Pointer to the Camera_CaptureSession instance that transfers the callback.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_RegisterCallback(Camera_CaptureSession* session,
    CaptureSession_Callbacks* callback);

/**
 * @brief Unregisters the callback used to listen for capture session events.
 * 
 * @param session Pointer to the Camera_CaptureSession instance that transfers the callback.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_UnregisterCallback(Camera_CaptureSession* session,
    CaptureSession_Callbacks* callback);

/**
 * @brief Registers a callback to listen for smooth zoom events.
 * 
 * @param session Pointer to the Camera_CaptureSession instance that transfers the callback.
 * @param smoothZoomInfoCallback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_RegisterSmoothZoomInfoCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnSmoothZoomInfo smoothZoomInfoCallback);

/**
 * @brief Unregisters the callback used to listen for smooth zoom events.
 * 
 * @param session Pointer to the Camera_CaptureSession instance that transfers the callback.
 * @param smoothZoomInfoCallback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_UnregisterSmoothZoomInfoCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnSmoothZoomInfo smoothZoomInfoCallback);

/**
 * @brief Sets a session mode.
 * This API cannot be called after {@link OH_CaptureSession_BeginConfig}.
 * You are advised to call this function immediately after {@link OH_CameraManager_CreateCaptureSession}.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param sceneMode Scene mode.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 *     <br>**CAMERA_SESSION_CONFIG_LOCKED**: The session configuration is locked.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_SetSessionMode(Camera_CaptureSession* session, Camera_SceneMode sceneMode);

/**
 * @brief Marks a preview output stream as secure output.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param previewOutput Pointer to the target Camera_PreviewOutput instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 *     <br>**CAMERA_SESSION_CONFIG_LOCKED**: The session configuration is locked.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_AddSecureOutput(Camera_CaptureSession* session, Camera_PreviewOutput* previewOutput);

/**
 * @brief Starts the configuration for a capture session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_CONFIG_LOCKED**: The session configuration is locked.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_BeginConfig(Camera_CaptureSession* session);

/**
 * @brief Commits the configuration for a capture session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_CommitConfig(Camera_CaptureSession* session);

/**
 * @brief Adds a Camera_Input instance to a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param cameraInput Pointer to the Camera_Input instance to add.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_AddInput(Camera_CaptureSession* session, Camera_Input* cameraInput);

/**
 * @brief Removes a Camera_Input instance from a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param cameraInput Pointer to the Camera_Input instance to remove.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_RemoveInput(Camera_CaptureSession* session, Camera_Input* cameraInput);

/**
 * @brief Adds a PreviewOutput instance to a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param previewOutput Pointer to the PreviewOutput instance to add.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_AddPreviewOutput(Camera_CaptureSession* session,
    Camera_PreviewOutput* previewOutput);

/**
 * @brief Removes a PreviewOutput instance from a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param previewOutput Pointer to the PreviewOutput instance to remove.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_RemovePreviewOutput(Camera_CaptureSession* session,
    Camera_PreviewOutput* previewOutput);

/**
 * @brief Adds a PhotoOutput instance to a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param photoOutput Pointer to the PhotoOutput instance to add.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_AddPhotoOutput(Camera_CaptureSession* session, Camera_PhotoOutput* photoOutput);

/**
 * @brief Removes a PhotoOutput instance from a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param photoOutput Pointer to the PhotoOutput instance to remove.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_RemovePhotoOutput(Camera_CaptureSession* session, Camera_PhotoOutput* photoOutput);

/**
 * @brief Adds a **VideoOutput** instance to a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param videoOutput Pointer to the **VideoOutput** instance to add.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_AddVideoOutput(Camera_CaptureSession* session, Camera_VideoOutput* videoOutput);

/**
 * @brief Removes a VideoOutput instance from a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param videoOutput Pointer to the VideoOutput instance to remove.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_RemoveVideoOutput(Camera_CaptureSession* session, Camera_VideoOutput* videoOutput);

/**
 * @brief Adds a MetadataOutput instance to a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param metadataOutput Pointer to the MetadataOutput instance to add.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_AddMetadataOutput(Camera_CaptureSession* session,
    Camera_MetadataOutput* metadataOutput);

/**
 * @brief Removes a MetadataOutput instance from a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param metadataOutput Pointer to the MetadataOutput instance to remove.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_RemoveMetadataOutput(Camera_CaptureSession* session,
    Camera_MetadataOutput* metadataOutput);

/**
 * @brief Starts a capture session.
 * 
 * @param session Pointer to the Camera_CaptureSession instance to start.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_Start(Camera_CaptureSession* session);

/**
 * @brief Stops a capture session.
 * 
 * @param session Pointer to the Camera_CaptureSession instance to stop.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_Stop(Camera_CaptureSession* session);

/**
 * @brief Releases a CaptureSession instance.
 * 
 * @param session Pointer to the Camera_CaptureSession instance to release.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_Release(Camera_CaptureSession* session);

/**
 * @brief Checks whether the device has flash.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param hasFlash Pointer to the check result for whether the device has flash. **true** if the device has flash, **
 * false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_HasFlash(Camera_CaptureSession* session, bool* hasFlash);

/**
 * @brief Checks whether a flash mode is supported.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param flashMode Flash mode to check.
 * @param isSupported Pointer to the check result for the support of the flash mode. **true** if supported, **false**
 * otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_IsFlashModeSupported(Camera_CaptureSession* session,
    Camera_FlashMode flashMode, bool* isSupported);

/**
 * @brief Obtains the flash mode in use.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param flashMode Pointer to the flash mode.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetFlashMode(Camera_CaptureSession* session, Camera_FlashMode* flashMode);

/**
 * @brief Sets a flash mode for the device.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param flashMode Flash mode to set.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetFlashMode(Camera_CaptureSession* session, Camera_FlashMode flashMode);

/**
 * @brief Capture session flash state change callback.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} which deliver the callback.
 * @param flashState The {@link OH_Camera_FlashState} which delivered by the callback.
 * @since 24
 */
typedef void (*OH_CaptureSession_OnFlashStateChange)(const Camera_CaptureSession* session, OH_Camera_FlashState flashState);

/**
 * @brief Register flash state change event callback.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param flashStateChange The {@link OH_CaptureSession_OnFlashStateChange} to be registered.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_RegisterFlashStateChangeCallback(const Camera_CaptureSession* session,
    OH_CaptureSession_OnFlashStateChange flashStateChange);

/**
 * @brief Unregister flash state change callback.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param flashStateChange The {@link OH_CaptureSession_OnFlashStateChange} to be unregistered.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_UnregisterFlashStateChangeCallback(const Camera_CaptureSession* session,
    OH_CaptureSession_OnFlashStateChange flashStateChange);

/**
 * @brief Defines a callback function that is invoked when the exposure state changes.
 *
 * @param context Indicates the pointer to the user-defined context.
 * @param exposureState Indicates the current exposure state.
 * @since 26.0.0
 */
typedef void (*OH_CaptureSession_OnExposureStateChange)(void* context, OH_Camera_ExposureState exposureState);

/**
 * @brief Registers a callback for exposure state changes.
 *
 * After this callback is registered, the callback is invoked when the exposure state changes in the
 * capture session.
 *
 * @param session the {@link Camera_CaptureSession} instance.
 * @param context Indicates the pointer to the user-defined context.
 * @param callback {@link OH_CaptureSession_OnExposureStateChange} Indicates the callback to register.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 * @since 26.0.0
 */
Camera_ErrorCode OH_CaptureSession_RegisterExposureStateChangeCallback(
    const Camera_CaptureSession* session, void* context, OH_CaptureSession_OnExposureStateChange callback);

/**
 * @brief Unregisters the callback for exposure state changes.
 *
 * @param session the {@link Camera_CaptureSession} instance.
 * @param context Indicates the pointer to the user-defined context specified when the callback was registered.
 * @param callback {@link OH_CaptureSession_OnExposureStateChange} Indicates the callback to unregister.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 * @since 26.0.0
 */
Camera_ErrorCode OH_CaptureSession_UnregisterExposureStateChangeCallback(
    const Camera_CaptureSession* session, void* context, OH_CaptureSession_OnExposureStateChange callback);

/**
 * @brief Checks whether an exposure mode is supported.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param exposureMode Exposure mode to check.
 * @param isSupported Pointer to the check result for the support of the exposure mode. **true** if supported, **false**
 * otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_IsExposureModeSupported(Camera_CaptureSession* session,
    Camera_ExposureMode exposureMode, bool* isSupported);

/**
 * @brief Obtains the exposure mode in use. This API directly returns an invalid value if you have not set the exposure
 * mode using {@link OH_CaptureSession_SetExposureMode}.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param exposureMode Pointer to the exposure mode.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetExposureMode(Camera_CaptureSession* session, Camera_ExposureMode* exposureMode);

/**
 * @brief Checks whether the specified white balance mode is supported.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param whiteBalanceMode White balance mode.
 * @param isSupported Pointer to the check result for the support of the specified white balance mode. **true** if
 * supported, **false** otherwise.
 * @return **CAMERA_OK**: The function is successfully called.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The camera session is not configured.
 * @since 20
 */

Camera_ErrorCode OH_CaptureSession_IsWhiteBalanceModeSupported(Camera_CaptureSession* session,
    Camera_WhiteBalanceMode whiteBalanceMode, bool* isSupported);

/**
 * @brief Obtains the white balance mode in use.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param whiteBalanceMode Pointer to the white balance mode.
 * @return **CAMERA_OK**: The function is successfully called.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The camera session is not configured.
 * @since 20
 */


Camera_ErrorCode OH_CaptureSession_GetWhiteBalanceMode(Camera_CaptureSession* session, Camera_WhiteBalanceMode* whiteBalanceMode);

/**
 * @brief Sets a white balance mode.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param whiteBalanceMode White balance mode.
 * @return **CAMERA_OK**: The setting is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The camera session is not configured.
 * @since 20
 */


Camera_ErrorCode OH_CaptureSession_SetWhiteBalanceMode(Camera_CaptureSession* session, Camera_WhiteBalanceMode whiteBalanceMode);

/**
 * @brief Obtains the supported white balance color temperature range.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param minColorTemperature Pointer to the minimum supported color temperature, in Kelvin.
 * @param maxColorTemperature Pointer to the maximum supported color temperature, in Kelvin.
 * @return **CAMERA_OK**: The function is successfully called.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The camera session is not configured.
 * @since 20
 */


Camera_ErrorCode OH_CaptureSession_GetWhiteBalanceRange(Camera_CaptureSession* session, int32_t *minColorTemperature, int32_t *maxColorTemperature);

/**
 * @brief Obtains the white balance color temperature.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param colorTemperature Pointer to the white balance color temperature, in Kelvin.
 * @return **CAMERA_OK**: The function is successfully called.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The camera session is not configured.
 * @since 20
 */


Camera_ErrorCode OH_CaptureSession_GetWhiteBalance(Camera_CaptureSession* session, int32_t *colorTemperature);


/**
 * @brief Sets the white balance color temperature.
 * Before setting this parameter, you are advised to use {@link OH_CaptureSession_GetWhiteBalanceRange} to obtain the
 * supported white balance color temperature range.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param colorTemperature White balance color temperature, in Kelvin.
 * @return **CAMERA_OK**: The setting is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The camera session is not configured.
 * @since 20
 */


Camera_ErrorCode OH_CaptureSession_SetWhiteBalance(Camera_CaptureSession* session, int32_t colorTemperature);

/**
 * @brief Sets an exposure mode for the device.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param exposureMode Exposure mode to set.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetExposureMode(Camera_CaptureSession* session, Camera_ExposureMode exposureMode);

/**
 * @brief Obtains the metering point in use.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param point Pointer to the metering point.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetMeteringPoint(Camera_CaptureSession* session, Camera_Point* point);

/**
 * @brief Sets the metering point, which is the center point of the metering rectangle.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param point Metering point to set.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetMeteringPoint(Camera_CaptureSession* session, Camera_Point point);

/**
 * @brief Check whether a specified exposure metering mode is supported.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param exposureMeteringMode The {@link OH_Camera_ExposureMeteringMode} to be checked.
 * @param isSupported Pointer to the result of whether exposure mode supported.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_IsExposureMeteringModeSupported(const Camera_CaptureSession* session,
    OH_Camera_ExposureMeteringMode exposureMeteringMode, bool* isSupported);

/**
 * @brief Get current exposure metering mode.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param exposureMeteringMode Pointer to the {@link OH_Camera_ExposureMeteringMode} instance.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetExposureMeteringMode(const Camera_CaptureSession* session, OH_Camera_ExposureMeteringMode* exposureMeteringMode);

/**
 * @brief Set exposure metering mode.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param exposureMeteringMode The target {@link OH_Camera_ExposureMeteringMode} to set.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetExposureMeteringMode(const Camera_CaptureSession* session, OH_Camera_ExposureMeteringMode exposureMeteringMode);

/**
 * @brief Query the iso range.
 *
 * @param session the {@link Camera_CaptureSession} instance.
 * @param minIsoValue the minimum of iso value.
 * @param maxIsoValue the Maximum of iso value.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetSupportedISORange(const Camera_CaptureSession* session,
    int32_t *minIsoValue, int32_t *maxIsoValue);

/**
 * @brief Get current iso sensitivity value, as defined in ISO 12232:2006.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param isoValue Pointer to the current iso sensitivity value.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetIso(const Camera_CaptureSession* session, int32_t* isoValue);

/**
 * @brief Sets ISO sensitivity value, within the range of getSupportedIsoRange. This control is only effective if
 * ExposureMode is set to EXPOSURE_MODE_LOCKED.
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param isoValue Indicates target iso value to set.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetIso(const Camera_CaptureSession* session, int32_t isoValue);

/**
 * @brief Defines the callback used to listen for ISO changes in a camera session.
 * 
 * @param session Pointer to the **Camera_CaptureSession** instance.
 * @param isoValue ISO value obtained in the callback.
 * @since 22
 */
typedef void (*OH_CaptureSession_OnIsoChange)(Camera_CaptureSession* session, int32_t isoValue);

/**
 * @brief Registers a callback to listen for ISO changes.
 * 
 * @param session Pointer to the Camera_CaptureSession instance.
 * @param isoChange Callback of the **OH_CaptureSession_OnIsoChange** type, which is used to listen for ISO changes.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 22
 */
Camera_ErrorCode OH_CaptureSession_RegisterIsoChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnIsoChange isoChange);

/**
 * @brief Unregisters the callback used to listen for ISO changes.
 * 
 * @param session Pointer to the Camera_CaptureSession instance.
 * @param isoChange Callback of the **OH_CaptureSession_OnIsoChange** type, which is used to listen for ISO changes.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 22
 */
Camera_ErrorCode OH_CaptureSession_UnregisterIsoChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnIsoChange isoChange);

/**
 * @brief Gets the supported physical apertures list. 
 * Release the physical apertures memory by calling {@link OH_CaptureSession_DeletePhysicalApertures}.
 *
 * @param session the {@link Camera_CaptureSession} instance
 * @param apertures pointer to an array for storing physical aperture values
 * @param size the size of physical apertures.
 * @return {@link CAMERA_OK} success 
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetSupportedPhysicalApertures(const Camera_CaptureSession* session,
    OH_Camera_PhysicalAperture** apertures, uint32_t* size);

/**
 * @brief Gets the current physical aperture value
 *
 * @param session the {@link Camera_CaptureSession} instance
 * @param aperture returned current aperture value
 * @return {@link CAMERA_OK} success 
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetPhysicalAperture(const Camera_CaptureSession* session, double* aperture);

/**
 * @brief Delete the physical apertures.
 *
 * @param session the {@link Camera_CaptureSession} instance.
 * @param apertures pointer to an array for storing physical aperture values
 * @param size the array size of the physical apertures.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_DeletePhysicalApertures(const Camera_CaptureSession* session,
    OH_Camera_PhysicalAperture* apertures, uint32_t size);

/**
 * @brief Set physical aperture value.
 *
 * @param session the {@link Camera_CaptureSession} instance
 * @param aperture the aperture value to set
 * @return {@link CAMERA_OK} success 
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetPhysicalAperture(const Camera_CaptureSession* session, double aperture);

/**
 * @brief Obtains the exposure compensation values of the device.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param minExposureBias Pointer to the minimum exposure compensation value.
 * @param maxExposureBias Pointer to the maximum exposure compensation value.
 * @param step Pointer to the exposure compensation step.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetExposureBiasRange(Camera_CaptureSession* session, float* minExposureBias,
    float* maxExposureBias, float* step);

/**
 * @brief Sets an exposure compensation value for the device.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param exposureBias Exposure compensation value to set.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetExposureBias(Camera_CaptureSession* session, float exposureBias);

/**
 * @brief Obtains the exposure compensation value in use.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param exposureBias Pointer to the exposure compensation value.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetExposureBias(Camera_CaptureSession* session, float* exposureBias);

/**
 * @brief Get the supported range of exposure durations. Units: Microseconds.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param minExposureDuration Pointer to the minimum of exposure duration.
 * @param maxExposureDuration Pointer to the maximum of exposure duration.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetSupportedExposureDurationRange(const Camera_CaptureSession* session, int32_t* minExposureDuration,
    int32_t* maxExposureDuration);

/**
 * @brief Set exposure duration. Units: Microseconds.
 * If the sensor can't expose this duration exactly, it will shorten the duration to the nearest supported value, which is
 * reporeted by Callback {@link OH_CaptureSession_OnExposureDurationChange}.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param exposureDuration the target exposure duration to set.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetExposureDuration(const Camera_CaptureSession* session, int32_t exposureDuration);

/**
 * @brief Get current exposure duration. Units: Microseconds.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param exposureDuration Pointer to the current exposure duration.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetExposureDuration(const Camera_CaptureSession* session, int32_t* exposureDuration);

/**
 * @brief Capture session exposure duration change callback.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} which deliver the callback.
 * @param exposureDuration The exposure duration which delivered by the callback.
 * @since 24
 */
typedef void (*OH_CaptureSession_OnExposureDurationChange)(const Camera_CaptureSession* session, int32_t exposureDuration);

/**
 * @brief Register exposure info change event callback.
 *    After exposure parameters are changed, the system will returns the updated exposure infos.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param exposureDurationChange The {@link OH_CaptureSession_OnExposureDurationChange} to be registered.
 * @return {@link CAMERA_OK} if the method call succeeds.
 * {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_RegisterExposureInfoChangeCallback(
    const Camera_CaptureSession* session, OH_CaptureSession_OnExposureDurationChange exposureDurationChange);

/**
 * @brief Unregister exposure info change callback.Invoke this method after finishing camera operations.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param exposureDurationChange The {@link OH_CaptureSession_OnExposureDurationChange} to be unregistered.
 * @return {@link CAMERA_OK} if the method call succeeds.
 * {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_UnregisterExposureInfoChangeCallback(
    const Camera_CaptureSession* session, OH_CaptureSession_OnExposureDurationChange exposureDurationChange); 

/**
 * @brief Checks whether a focus mode is supported.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param focusMode Focus mode to check.
 * @param isSupported Pointer to the check result for the support of the focus mode. **true** if supported, **false**
 * otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_IsFocusModeSupported(Camera_CaptureSession* session,
    Camera_FocusMode focusMode, bool* isSupported);

/**
 * @brief Obtains the focus mode in use.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param focusMode Pointer to the focus mode.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetFocusMode(Camera_CaptureSession* session, Camera_FocusMode* focusMode);

/**
 * @brief Sets a focus mode for the device.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param focusMode Focus mode to set.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetFocusMode(Camera_CaptureSession* session, Camera_FocusMode focusMode);

/**
 * @brief Obtains the focal point in use.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param focusPoint Pointer to the focal point.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetFocusPoint(Camera_CaptureSession* session, Camera_Point* focusPoint);

/**
 * @brief Sets a focal point for the device.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param focusPoint Focal point to set.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetFocusPoint(Camera_CaptureSession* session, Camera_Point focusPoint);

/**
 * @brief Obtains the supported zoom ratio range.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param minZoom Pointer to the minimum zoom ratio.
 * @param maxZoom Pointer to the maximum zoom ratio.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetZoomRatioRange(Camera_CaptureSession* session, float* minZoom, float* maxZoom);

/**
 * @brief Obtains the zoom ratio in use.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param zoom Pointer to the zoom ratio.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetZoomRatio(Camera_CaptureSession* session, float* zoom);

/**
 * @brief Sets a zoom ratio for the device.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param zoom Target zoom ratio.
 * It takes some time for the zoom ratio to take effect at the bottom layer. To obtain the correct zoom ratio, you need
 * to wait for one to two frames.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetZoomRatio(Camera_CaptureSession* session, float zoom);

/**
 * @brief Checks whether a video stabilization mode is supported.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param mode Video stabilization mode to check.
 * @param isSupported Pointer to the check result for the support of the video stabilization mode. **true** if
 * supported, **false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_IsVideoStabilizationModeSupported(Camera_CaptureSession* session,
    Camera_VideoStabilizationMode mode, bool* isSupported);

/**
 * @brief Obtains the video stabilization mode in use.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param mode Pointer to the video stabilization mode.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_GetVideoStabilizationMode(Camera_CaptureSession* session,
    Camera_VideoStabilizationMode* mode);

/**
 * @brief Sets a video stabilization mode for the device.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param mode Video stabilization mode to set.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 11
 */
Camera_ErrorCode OH_CaptureSession_SetVideoStabilizationMode(Camera_CaptureSession* session,
    Camera_VideoStabilizationMode mode);

/**
 * @brief Checks whether a Camera_Input instance can be added to a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param cameraInput Pointer to the Camera_Input instance to check.
 * @param isSuccessful Pointer to the check result for whether the Camera_Input instance can be added to the session. **
 * true** if it can be added to the session, **false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_CanAddInput(Camera_CaptureSession* session,
    Camera_Input* cameraInput, bool* isSuccessful);

/**
 * @brief Checks whether a PreviewOutput instance can be added to a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param cameraOutput Pointer to the PreviewOutput instance to check.
 * @param isSuccessful Pointer to the check result for whether the PreviewOutput instance can be added to the session. *
 * *true** if it can be added to the session, **false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_CanAddPreviewOutput(Camera_CaptureSession* session,
    Camera_PreviewOutput* cameraOutput, bool* isSuccessful);

/**
 * @brief Checks whether a PhotoOutput instance can be added to a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param cameraOutput Pointer to the PhotoOutput instance to check.
 * @param isSuccessful Pointer to the check result for whether the PhotoOutput instance can be added to the session. **
 * true** if it can be added to the session, **false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_CanAddPhotoOutput(Camera_CaptureSession* session,
    Camera_PhotoOutput* cameraOutput, bool* isSuccessful);

/**
 * @brief Checks whether a **VideoOutput** instance can be added to a session.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param cameraOutput Pointer to the **VideoOutput** instance to check.
 * @param isSuccessful Pointer to the check result for whether the VideoOutput instance can be added to the session. **
 * true** if it can be added to the session, **false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_CanAddVideoOutput(Camera_CaptureSession* session,
    Camera_VideoOutput* cameraOutput, bool* isSuccessful);

/**
 * @brief Checks whether a preconfigured resolution type is supported.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param preconfigType Target preconfigured resolution type.
 * @param canPreconfig Pointer to the check result for the support of the preconfigured resolution type. **true** if
 * supported, **false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_CanPreconfig(Camera_CaptureSession* session,
    Camera_PreconfigType preconfigType, bool* canPreconfig);

/**
 * @brief Checks whether a preconfigured resolution type with an aspect ratio is supported.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param preconfigType Target preconfigured resolution type.
 * @param preconfigRatio Target preconfigured aspect ratio.
 * @param canPreconfig Pointer to the check result for the support of the preconfigured resolution type. **true** if
 * supported, **false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_CanPreconfigWithRatio(Camera_CaptureSession* session,
    Camera_PreconfigType preconfigType, Camera_PreconfigRatio preconfigRatio, bool* canPreconfig);

/**
 * @brief Sets a preconfigured resolution type.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param preconfigType Target preconfigured resolution type.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_Preconfig(Camera_CaptureSession* session,
    Camera_PreconfigType preconfigType);

/**
 * @brief Sets a preconfigured resolution type with an aspect ratio.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param preconfigType Target preconfigured resolution type.
 * @param preconfigRatio Target preconfigured aspect ratio.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_PreconfigWithRatio(Camera_CaptureSession* session,
    Camera_PreconfigType preconfigType, Camera_PreconfigRatio preconfigRatio);

/**
 * @brief Obtains the exposure value.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param exposureValue Pointer to the exposure value.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_GetExposureValue(Camera_CaptureSession* session, float* exposureValue);

/**
 * @brief Obtains the current focal length.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param focalLength Pointer to the focal length.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_GetFocalLength(Camera_CaptureSession* session, float* focalLength);

/**
 * @brief Check whether focus distance is supported.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param isSupported Pointer to the result of whether focus distance is supported.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_IsFocusDistanceSupported(const Camera_CaptureSession* session, bool* isSupported);

/**
 * @brief Get current focus distance, ranging from 0.0 to 1.0, with 0.0 being shortest
 * distance at which the lens can focus and 1.0 the furthest. The default value is 1.0.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param focusDistance Pointer to the current focus distance.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetFocusDistance(const Camera_CaptureSession* session, float* focusDistance);

/**
 * @brief Sets focus distance. Possible distance values range from 0.0 to 1.0, with 0.0 being shortest
 * distance at which the lens can focus and 1.0 the furthest. The default value is 1.0.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param focusDistance The focus distance to be set.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetFocusDistance(const Camera_CaptureSession* session, float focusDistance);

/**
 * @brief Sets smooth zoom.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param targetZoom Target zoom ratio.
 * @param smoothZoomMode Smooth zoom mode.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_SetSmoothZoom(Camera_CaptureSession* session,
    float targetZoom, Camera_SmoothZoomMode smoothZoomMode);

/**
 * @brief Obtains the supported color spaces.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param colorSpace Double pointer to the list of supported color spaces, which are defined in the
 * OH_NativeBuffer_ColorSpace struct, if the function is successfully called.
 * @param size Pointer to the size of the list of supported color spaces.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_GetSupportedColorSpaces(Camera_CaptureSession* session,
    OH_NativeBuffer_ColorSpace** colorSpace, uint32_t* size);

/**
 * @brief Deletes color spaces.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param colorSpace Pointer to the list of color spaces, which are defined in the OH_NativeBuffer_ColorSpace struct.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_DeleteColorSpaces(Camera_CaptureSession* session,
    OH_NativeBuffer_ColorSpace* colorSpace);

/**
 * @brief Obtains the active color space.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param colorSpace Pointer to the OH_NativeBuffer_ColorSpace instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_GetActiveColorSpace(Camera_CaptureSession* session,
    OH_NativeBuffer_ColorSpace* colorSpace);

/**
 * @brief Sets the active color space.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param colorSpace Target OH_NativeBuffer_ColorSpace instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 12
 */
Camera_ErrorCode OH_CaptureSession_SetActiveColorSpace(Camera_CaptureSession* session,
    OH_NativeBuffer_ColorSpace colorSpace);

/**
 * @brief Register device switch event callback.
 *
 * @param session the {@link Camera_CaptureSession} instance.
 * @param autoDeviceSwitchStatusChange the {@link OH_CaptureSession_OnAutoDeviceSwitchStatusChange} to be registered.
 * @return {@link #CAMERA_OK} if the method call succeeds.
 *         {@link #CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 * @since 13
 */
Camera_ErrorCode OH_CaptureSession_RegisterAutoDeviceSwitchStatusCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnAutoDeviceSwitchStatusChange autoDeviceSwitchStatusChange);

/**
 * @brief Unregister device switch event callback.
 *
 * @param session the {@link Camera_CaptureSession} instance.
 * @param autoDeviceSwitchStatusChange the {@link OH_CaptureSession_OnAutoDeviceSwitchStatusChange} to be unregistered.
 * @return {@link #CAMERA_OK} if the method call succeeds.
 *         {@link #CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 * @since 13
 */
Camera_ErrorCode OH_CaptureSession_UnregisterAutoDeviceSwitchStatusCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnAutoDeviceSwitchStatusChange autoDeviceSwitchStatusChange);

/**
 * @brief Check whether auto device switch is supported.
 *
 * @param session the {@link Camera_CaptureSession} instance.
 * @param isSupported the result of whether auto device switch supported.
 * @return {@link #CAMERA_OK} if the method call succeeds.
 *         {@link #CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link #CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 13
 */
Camera_ErrorCode OH_CaptureSession_IsAutoDeviceSwitchSupported(Camera_CaptureSession* session, bool* isSupported);

/**
 * @brief Enable auto switch or not for the camera device.
 *
 * @param session the {@link Camera_CaptureSession} instance.
 * @param enabled the flag of enable auto switch or not.
 * @return {@link #CAMERA_OK} if the method call succeeds.
 *         {@link #CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link #CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 *         {@link #CAMERA_SERVICE_FATAL_ERROR} if camera service fatal error.
 * @since 13
 */
Camera_ErrorCode OH_CaptureSession_EnableAutoDeviceSwitch(Camera_CaptureSession* session, bool enabled);

/**
 * @brief Set quality prioritization.
 *
 * @param session the {@link Camera_CaptureSession} instance.
 * @param qualityPrioritization the target {@link Camera_QualityPrioritization} to set.
 * @return {@link #CAMERA_OK} if the method call succeeds.
 *         {@link #CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link #CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 14
 */
Camera_ErrorCode OH_CaptureSession_SetQualityPrioritization(
    Camera_CaptureSession* session, Camera_QualityPrioritization qualityPrioritization);

/**
 * @brief Checks whether macro photography is supported.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param isSupported Pointer to the check result for the support of macro photography. **true** if supported, **false**
 * otherwise.
 * @return
 *     <br>**CAMERA_OK = 0**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 19
 */
Camera_ErrorCode OH_CaptureSession_IsMacroSupported(Camera_CaptureSession* session, bool* isSupported);

/**
 * @brief Enables or disables macro photography for the camera device.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param enabled Whether to enable or disable macro capability. **true** to enable, **false** otherwise.
 * @return
 *     <br>**CAMERA_OK = 0**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 * @since 19
 */
Camera_ErrorCode OH_CaptureSession_EnableMacro(Camera_CaptureSession* session, bool enabled);

/**
 * @brief Defines the callback used to listen for macro status changes of a camera session.
 * 
 * @param session Pointer to the Camera_CaptureSession instance.
 * @param isMacroDetected Whether the camera is in macro mode. **true** if the camera is in macro mode, **false**
 * otherwise.
 * @since 20
 */
typedef void (*OH_CaptureSession_OnMacroStatusChange)(Camera_CaptureSession* session, bool isMacroDetected);

/**
 * @brief Registers a callback to listen for macro status changes of a camera session.
 * 
 * @param session Pointer to the Camera_CaptureSession instance.
 * @param macroStatusChange Callback used to return the macro status change.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_RegisterMacroStatusChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnMacroStatusChange macroStatusChange);

/**
 * @brief Unregisters the callback used to listen for macro status changes of a camera session.
 * 
 * @param session Pointer to the Camera_CaptureSession instance.
 * @param macroStatusChange Callback used to return the macro status change.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_UnregisterMacroStatusChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnMacroStatusChange macroStatusChange);

/**
 * @brief Registers a callback to listen for capture system pressure level changes.
 * 
 * @param session Pointer to the Camera_CaptureSession instance that transfers the callback.
 * @param systemPressureLevelChange Target callback, which is OH_CaptureSession_OnSystemPressureLevelChange.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_RegisterSystemPressureLevelChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnSystemPressureLevelChange systemPressureLevelChange);

/**
 * @brief Unregisters the callback used to listen for capture system pressure level changes.
 * 
 * @param session Pointer to the Camera_CaptureSession instance that transfers the callback.
 * @param systemPressureLevelChange Target callback, which is OH_CaptureSession_OnSystemPressureLevelChange.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_UnregisterSystemPressureLevelChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnSystemPressureLevelChange systemPressureLevelChange);

/**
 * @brief Checks whether the camera controller is supported.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param isSupported Pointer to the check result for the support of the camera controller. **true** if supported, **
 * false** otherwise.
 * @return **CAMERA_OK = 0**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_IsControlCenterSupported(Camera_CaptureSession* session, bool* isSupported);

/**
 * @brief Obtains the effect types supported by the camera controller.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param types Double pointer to the list of supported effect types, which are defined in the
 * Camera_ControlCenterEffectType struct, if the function is successfully called.
 * @param size Pointer to the size of the list of supported effect types.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_GetSupportedEffectTypes(
    Camera_CaptureSession* session, Camera_ControlCenterEffectType** types, uint32_t* size);

/**
 * @brief Deletes the effect types supported by the camera controller.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param types Pointer to the list of effect types, which are defined in the Camera_ControlCenterEffectType struct.
 * @param size Size of the list of supported effect types.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_DeleteSupportedEffectTypes(Camera_CaptureSession* session,
    Camera_ControlCenterEffectType* types, uint32_t size);

/**
 * @brief Enables or disables the camera controller.
 * 
 * @param session Pointer to the target Camera_CaptureSession instance.
 * @param enabled Whether to enable the camera controller. **true** to enable, **false** otherwise.
 * @return **CAMERA_OK = 0**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_EnableControlCenter(Camera_CaptureSession* session, bool enabled);

/**
 * @brief Defines the callback used to listen for effect status changes of a camera controller.
 * 
 * @param session Pointer to the Camera_CaptureSession instance that transfers the callback.
 * @param controlCenterStatusInfo Pointer to the effect status information passed by the callback.
 * @since 20
 */
typedef void (*OH_CaptureSession_OnControlCenterEffectStatusChange)(Camera_CaptureSession* session,
    Camera_ControlCenterStatusInfo* controlCenterStatusInfo);

/**
 * @brief Registers a callback to listen for effect status changes of a camera controller.
 * 
 * @param session Pointer to the Camera_CaptureSession instance that transfers the callback.
 * @param controlCenterEffectStatusChange Target callback, which is OH_CaptureSession_OnControlCenterEffectStatusChange.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_RegisterControlCenterEffectStatusChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnControlCenterEffectStatusChange controlCenterEffectStatusChange);

/**
 * @brief Unregisters the callback used to listen for effect status changes of a camera controller.
 * 
 * @param session Pointer to the Camera_CaptureSession instance that transfers the callback.
 * @param controlCenterEffectStatusChange Target callback, which is OH_CaptureSession_OnControlCenterEffectStatusChange.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 20
 */
Camera_ErrorCode OH_CaptureSession_UnregisterControlCenterEffectStatusChangeCallback(Camera_CaptureSession* session,
    OH_CaptureSession_OnControlCenterEffectStatusChange controlCenterEffectStatusChange);

/**
 * @brief Query the raw zoom range.
 *
 * @param session the {@link Camera_CaptureSession} instance.
 * @param minZoom the minimum of zoom value.
 * @param maxZoom the Maximum of zoom value.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation not allowed, session or inputdevice maybe abnormal.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetRAWCaptureZoomRatioRange(const Camera_CaptureSession* session, float* minZoom, float* maxZoom);

/**
 * @brief Checks if the specified OIS mode is supported.
 *
 * @param session Pointer to a session.
 * @param oisMode The OIS mode {@link OH_Camera_OISMode} to check.
 * @param isSupported Output parameter indicating support status.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameters are invalid.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation is not allowed.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_IsOISModeSupported(const Camera_CaptureSession* session,
    OH_Camera_OISMode oisMode, bool* isSupported);

/**
 * @brief Gets the supported bias range for the specified OIS axis.
 *
 * @param session Pointer to a session.
 * @param oisAxis The OIS axis {@link OH_Camera_OISAxes}
 * @param minBias Output parameter for minimum bias value.
 * @param maxBias Output parameter for maximum bias value.
 * @param step Output parameter for bias step value.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameters are invalid.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation is not allowed.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetSupportedOISBiasRange(const Camera_CaptureSession* session,
    OH_Camera_OISAxes oisAxis, float* minBias, float* maxBias, float* step);

/**
 * @brief Gets the current OIS mode.
 *
 * @param session Pointer to a session.
 * @param oisMode Output parameter for current OIS mode {@link OH_Camera_OISMode}.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameters are invalid.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation is not allowed.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetCurrentOISMode(const Camera_CaptureSession* session,
    OH_Camera_OISMode* oisMode);

/**
 * @brief Gets the current custom bias values for all OIS axes.
 *
 * @param session Pointer to a session.
 * @param pitchBias Output parameter for pitch axis bias value.
 * @param yawBias Output parameter for yaw axis bias value.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameters are invalid.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation is not allowed.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_GetCurrentCustomOISBias(const Camera_CaptureSession* session,
    float* pitchBias, float* yawBias);

/**
 * @brief Sets the OIS mode.
 *
 * @param session Pointer to a session.
 * @param oisMode The OIS mode {@link OH_Camera_OISMode} to set.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameters are invalid.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation is not allowed.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetOISMode(const Camera_CaptureSession* session,
    OH_Camera_OISMode oisMode);

/**
 * @brief Sets custom OIS bias values for all axes.
 *
 * @param session Pointer to a session.
 * @param pitchBias Bias value for pitch axis.
 * @param yawBias Bias value for yaw axis.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameters are invalid.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation is not allowed.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 24
 */
Camera_ErrorCode OH_CaptureSession_SetOISModeCustom(const Camera_CaptureSession* session,
    float pitchBias, float yawBias);

/**
 * @brief Gets the zoom point infos.
 * Release the zoom point infos memory by calling {@link OH_CaptureSession_DeleteZoomPointInfos}.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param size Pointer to the size of queried zoom point info.
 * @param zoomPointInfo Double pointer to the queried zoom point info.
 * @return {@link CAMERA_OK} is returned if the function is called successfully.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameters are invalid.
 *         {@link CAMERA_OPERATION_NOT_ALLOWED} if operation is not allowed.
 *         {@link CAMERA_SESSION_NOT_CONFIG} if the capture session not config.
 * @since 26.0.0
 */
Camera_ErrorCode OH_CaptureSession_GetZoomPointInfos(const Camera_CaptureSession* session, uint32_t* size,
    OH_Camera_ZoomPointInfo** zoomPointInfo);

/**
 * @brief Delete the zoom point infos.
 *
 * @param session Pointer to the {@link Camera_CaptureSession} instance.
 * @param zoomPointInfo the target {@link Camera_ZoomPointInfo} list to be deleted if the method call succeeds.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 * @since 26.0.0
 */
Camera_ErrorCode OH_CaptureSession_DeleteZoomPointInfos(const Camera_CaptureSession* session,
    OH_Camera_ZoomPointInfo* zoomPointInfo);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_CAMERA_SESSION_H
/** @} */

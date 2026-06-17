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
 * @file preview_output.h
 *
 * @brief The file declares the preview output concepts.
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 11
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_CAMERA_PREVIEWOUTPUT_H
#define NATIVE_INCLUDE_CAMERA_PREVIEWOUTPUT_H

#include <stdint.h>
#include <stdio.h>
#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct describes the preview output object.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_PreviewOutput Camera_PreviewOutput;

/**
 * @brief Defines the callback defined in the {@link PreviewOutput_Callbacks} struct and used to report preview output
 * frame start events.
 * 
 * @param previewOutput Pointer to the PreviewOutput instance that transfers the callback.
 * @since 11
 */
typedef void (*OH_PreviewOutput_OnFrameStart)(Camera_PreviewOutput* previewOutput);

/**
 * @brief Defines the callback defined in the {@link PreviewOutput_Callbacks} struct and used to report preview output
 * frame end events.
 * 
 * @param previewOutput Pointer to the PreviewOutput instance that transfers the callback.
 * @param frameCount Number of frames to be included in the callback.
 * @since 11
 */
typedef void (*OH_PreviewOutput_OnFrameEnd)(Camera_PreviewOutput* previewOutput, int32_t frameCount);

/**
 * @brief Defines the callback defined in the {@link PreviewOutput_Callbacks} struct and used to report preview output
 * errors.
 * 
 * @param previewOutput Pointer to the PreviewOutput instance that transfers the callback.
 * @param errorCode Error code reported during preview output.
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 11
 */
typedef void (*OH_PreviewOutput_OnError)(Camera_PreviewOutput* previewOutput, Camera_ErrorCode errorCode);

/**
 * @brief The struct describes the callbacks related to preview output.
 * 
 * @see OH_PreviewOutput_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct PreviewOutput_Callbacks {
    /**
     * Callback to report preview output frame start events.
     */
    OH_PreviewOutput_OnFrameStart onFrameStart;

    /**
     * Callback to report preview output frame end events.
     */
    OH_PreviewOutput_OnFrameEnd onFrameEnd;

    /**
     * Callback to report preview output errors.
     */
    OH_PreviewOutput_OnError onError;
} PreviewOutput_Callbacks;

/**
 * @brief Registers a callback to listen for preview output events.
 * 
 * @param previewOutput Pointer to the target PreviewOutput instance.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_PreviewOutput_RegisterCallback(Camera_PreviewOutput* previewOutput,
    PreviewOutput_Callbacks* callback);

/**
 * @brief Unregisters the callback used to listen for preview output events.
 * 
 * @param previewOutput Pointer to the target PreviewOutput instance.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_PreviewOutput_UnregisterCallback(Camera_PreviewOutput* previewOutput,
    PreviewOutput_Callbacks* callback);

/**
 * @brief Starts preview output.
 * 
 * @param previewOutput Pointer to the PreviewOutput instance to start.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_PreviewOutput_Start(Camera_PreviewOutput* previewOutput);

/**
 * @brief Stops preview output.
 * 
 * @param previewOutput Pointer to the PreviewOutput instance to stop.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_PreviewOutput_Stop(Camera_PreviewOutput* previewOutput);

/**
 * @brief Releases a PreviewOutput instance.
 * 
 * @param previewOutput Pointer to the PreviewOutput instance to release.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_PreviewOutput_Release(Camera_PreviewOutput* previewOutput);

/**
 * @brief Obtains the profile of a PreviewOutput instance.
 * 
 * @param previewOutput Pointer to the PreviewOutput instance for which the profile is to be obtained.
 * @param profile Double pointer to the preview output profile obtained.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_GetActiveProfile(Camera_PreviewOutput* previewOutput, Camera_Profile** profile);

/**
 * @brief Deletes the profile of a PreviewOutput instance.
 * 
 * @param profile Pointer to the profile to delete.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_DeleteProfile(Camera_Profile* profile);

/**
 * @brief Obtains the preview rotation angle.
 * 
 * @param previewOutput Pointer to the PreviewOutput instance used to obtain the rotation angle.
 * @param displayRotation Rotation angle of the display.
 * @param imageRotation Pointer to the preview rotation angle.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_GetPreviewRotation(Camera_PreviewOutput* previewOutput, int displayRotation,
    Camera_ImageRotation* imageRotation);

/**
 * @brief Obtains the preview rotation angle.
 * 
 * @param previewOutput Pointer to the PreviewOutput instance used to obtain the rotation angle.
 * @param imageRotation Pointer to the preview rotation angle.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 23
 */
Camera_ErrorCode OH_PreviewOutput_GetPreviewRotationWithoutDisplayRotation(Camera_PreviewOutput* previewOutput,
    Camera_ImageRotation* imageRotation);

/**
 * @brief Sets the preview rotation angle.
 * 
 * @param previewOutput Pointer to the PreviewOutput instance used to set the rotation angle.
 * @param previewRotation Preview rotation angle.
 * @param isDisplayLocked Whether the orientation of the surface is locked when the screen rotates. If this parameter
 * is not set, the default value **false** is used, indicating that the orientation is not locked. **true** if locked, *
 * *false** otherwise. For details, see {@link SurfaceRotationOptions}.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_SetPreviewRotation(Camera_PreviewOutput* previewOutput,
    Camera_ImageRotation previewRotation, bool isDisplayLocked);

/**
 * @brief Obtains the list of frame rates supported by a PreviewOutput instance.
 * 
 * @param previewOutput Pointer to the PreviewOutput instance used to obtain the frame rates.
 * @param frameRateRange Double pointer to the list of frame rates, if the function is successfully called.
 * @param size Pointer to the size of the list of frame rates.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_GetSupportedFrameRates(Camera_PreviewOutput* previewOutput,
    Camera_FrameRateRange** frameRateRange, uint32_t* size);

/**
 * @brief Deletes the frame rate list.
 * 
 * @param previewOutput Pointer to the target PreviewOutput instance.
 * @param frameRateRange Pointer to the list of frame rates to delete.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_DeleteFrameRates(Camera_PreviewOutput* previewOutput,
    Camera_FrameRateRange* frameRateRange);

/**
 * @brief Sets the frame rates for a PreviewOutput instance.
 * 
 * @param previewOutput Pointer to the PreviewOutput instance used to set the frame rates.
 * @param minFps Minimum frame rate.
 * @param maxFps Maximum frame rate.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_SetFrameRate(Camera_PreviewOutput* previewOutput,
    int32_t minFps, int32_t maxFps);

/**
 * @brief Obtains the active frame rates of a PreviewOutput instance.
 * 
 * @param previewOutput Pointer to the PreviewOutput instance used to obtain the active frame rates.
 * @param frameRateRange Pointer to the frame rate range, which is defined in the {@link Camera_FrameRateRange} struct,
 * if the function is successfully called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_PreviewOutput_GetActiveFrameRate(Camera_PreviewOutput* previewOutput,
    Camera_FrameRateRange* frameRateRange);

/**
 * @brief Checks whether preview bandwidth compression is supported. This involves reducing data volume through
 * encoding to minimize bandwidth usage during transmission.
 * 
 * @param previewOutput Pointer to the target PreviewOutput instance.
 * @param isSupported Pointer to the check result for the support of bandwidth compression. **true** if supported, **
 * false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 23
 */
Camera_ErrorCode OH_PreviewOutput_IsBandwidthCompressionSupported(Camera_PreviewOutput* previewOutput,
    bool* isSupported);
	
/**
 * @brief Enables preview bandwidth compression.
 * This function must be called prior to {@link OH_CaptureSession_CommitConfig()}. Otherwise, the preview output stream
 * format will be affected.
 * 
 * @param previewOutput Pointer to the target PreviewOutput instance.
 * @param enabled Whether to enable preview bandwidth compression. **true** to enable, **false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The camera session is not configured.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 23
 */
Camera_ErrorCode OH_PreviewOutput_EnableBandwidthCompression(Camera_PreviewOutput* previewOutput, bool enabled);

/**
 * @brief add surface for preview output.
 *
 * @param previewOutput the {@link Camera_PreviewOutput} instance to add surfaceId.
 * @param surfaceId the which use to create {@link Camera_PreviewOutput}.
 * @return {@link CAMERA_OK} if the method call succeeds.
 *         {@link CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 * @since 24
 */
Camera_ErrorCode OH_PreviewOutput_AddDeferredSurface(const Camera_PreviewOutput* previewOutput, const char* surfaceId);
#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_PREVIEWOUTPUT_H
/** @} */

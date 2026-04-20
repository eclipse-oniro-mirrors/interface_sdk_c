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
 * @file photo_output.h
 *
 * @brief The file declares the photo output concepts.
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 11
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_CAMERA_PHOTOOUTPUT_H
#define NATIVE_INCLUDE_CAMERA_PHOTOOUTPUT_H

#include <stdint.h>
#include <stdio.h>
#include "camera.h"
#include "photo_native.h"
#include "multimedia/media_library/media_asset_base_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct describes the photo output object.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_PhotoOutput Camera_PhotoOutput;

/**
 * @brief Defines the callback defined in the {@link PhotoOutput_Callbacks} struct and used to report photo output
 * frame start events.
 * 
 * @param photoOutput Pointer to the PhotoOutput instance that transfers the callback.
 * @since 11
 */
typedef void (*OH_PhotoOutput_OnFrameStart)(Camera_PhotoOutput* photoOutput);

/**
 * @brief Defines the callback defined in the {@link PhotoOutput_Callbacks} struct and used to report frame shutter
 * events.
 * 
 * @param photoOutput Pointer to the PhotoOutput instance that transfers the callback.
 * @param info Pointer to the frame shutter information.
 * @since 11
 */
typedef void (*OH_PhotoOutput_OnFrameShutter)(Camera_PhotoOutput* photoOutput, Camera_FrameShutterInfo* info);

/**
 * @brief Defines the callback defined in the {@link PhotoOutput_Callbacks} struct and used to report photo output
 * frame end events.
 * 
 * @param photoOutput Pointer to the PhotoOutput instance that transfers the callback.
 * @param frameCount Number of frames to be included in the callback.
 * @since 11
 */
typedef void (*OH_PhotoOutput_OnFrameEnd)(Camera_PhotoOutput* photoOutput, int32_t frameCount);

/**
 * @brief Defines the callback defined in the {@link PhotoOutput_Callbacks} struct and used to report photo output
 * errors.
 * 
 * @param photoOutput Pointer to the PhotoOutput instance that transfers the callback.
 * @param errorCode Error code reported during photo output.
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 11
 */
typedef void (*OH_PhotoOutput_OnError)(Camera_PhotoOutput* photoOutput, Camera_ErrorCode errorCode);

/**
 * @brief Defines the callback invoked when the capture ends.
 * 
 * @param photoOutput Pointer to the PhotoOutput instance that transfers the callback.
 * @param frameCount Number of frames to be included in the callback.
 * @since 12
 */
typedef void (*OH_PhotoOutput_CaptureEnd) (Camera_PhotoOutput* photoOutput, int32_t frameCount);

/**
 * @brief Defines the callback invoked when the capture starts.
 * 
 * @param photoOutput Pointer to the PhotoOutput instance that transfers the callback.
 * @param info the {@link Camera_CaptureStartInfo} which is delivered by the callback.
 * @since 12
 */
typedef void (*OH_PhotoOutput_CaptureStartWithInfo) (Camera_PhotoOutput* photoOutput, Camera_CaptureStartInfo* Info);

/**
 * @brief Defines the callback invoked when frame shutter ends.
 * 
 * @param photoOutput Pointer to the PhotoOutput instance that transfers the callback.
 * @param info the {@link Camera_CaptureStartInfo} which is delivered by the callback.
 * @since 12
 */
typedef void (*OH_PhotoOutput_OnFrameShutterEnd) (Camera_PhotoOutput* photoOutput, Camera_FrameShutterInfo* Info);

/**
 * @brief Defines the callback invoked when the camera is ready to take photos. When the callback is received, the next
 * capture can be performed.
 * 
 * @param photoOutput Pointer to the PhotoOutput instance that transfers the callback.
 * @since 12
 */
typedef void (*OH_PhotoOutput_CaptureReady) (Camera_PhotoOutput* photoOutput);

/**
 * @brief Defines the callback for the estimated capture duration.
 * 
 * @param photoOutput Pointer to the PhotoOutput instance that transfers the callback.
 * @param duration Estimated capture duration passed by the callback, measured in milliseconds.
 * @since 12
 */
typedef void (*OH_PhotoOutput_EstimatedCaptureDuration) (Camera_PhotoOutput* photoOutput, int64_t duration);

/**
 * @brief Defines the callback invoked when a high-resolution photo is available.
 * 
 * @param photoOutput Pointer to the PhotoOutput instance that transfers the callback.
 * @param photo Pointer to OH_PhotoNative passed by the callback.
 * @since 12
 */
typedef void (*OH_PhotoOutput_PhotoAvailable)(Camera_PhotoOutput* photoOutput, OH_PhotoNative* photo);

/**
 * @brief Defines the callback invoked when a photo asset is available.
 * 
 * @param photoOutput Pointer to the PhotoOutput instance that transfers the callback.
 * @param photoAsset Pointer to the media asset passed by the callback.
 * @since 12
 */
typedef void (*OH_PhotoOutput_PhotoAssetAvailable)(Camera_PhotoOutput* photoOutput, OH_MediaAsset* photoAsset);

/**
 * @brief The struct describes the callbacks related to photo output.
 * 
 * @see OH_PhotoOutput_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct PhotoOutput_Callbacks {
    /**
     * Callback to report photo output frame start events.
     */
    OH_PhotoOutput_OnFrameStart onFrameStart;

    /**
     * Callback to report frame shutter events.
     */
    OH_PhotoOutput_OnFrameShutter onFrameShutter;

    /**
     * Callback to report photo output frame end events.
     */
    OH_PhotoOutput_OnFrameEnd onFrameEnd;

    /**
     * Callback to report photo output errors.
     */
    OH_PhotoOutput_OnError onError;
} PhotoOutput_Callbacks;

/**
 * @brief Registers a callback to listen for photo output events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_PhotoOutput_RegisterCallback(Camera_PhotoOutput* photoOutput, PhotoOutput_Callbacks* callback);

/**
 * @brief Unregisters the callback used to listen for photo output events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterCallback(Camera_PhotoOutput* photoOutput, PhotoOutput_Callbacks* callback);

/**
 * @brief Registers a callback to listen for capture start events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterCaptureStartWithInfoCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_CaptureStartWithInfo callback);

/**
 * @brief Obtains the photo rotation angle.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param deviceDegree Rotation angle of the device.
 * @param imageRotation Pointer to the rotation angle of the photo.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * **CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_GetPhotoRotation(Camera_PhotoOutput* photoOutput, int deviceDegree,
    Camera_ImageRotation* imageRotation);

/**
 * @brief Obtains the photo rotation angle.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param imageRotation Pointer to the rotation angle of the photo.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 23
 */
Camera_ErrorCode OH_PhotoOutput_GetPhotoRotationWithoutDeviceDegree(Camera_PhotoOutput* photoOutput,
    Camera_ImageRotation* imageRotation);

/**
 * @brief Unregisters the callback used to listen for capture start events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterCaptureStartWithInfoCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_CaptureStartWithInfo callback);

/**
 * @brief Registers a callback to listen for capture end events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterCaptureEndCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_CaptureEnd callback);

/**
 * @brief Unregisters the callback used to listen for capture end events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterCaptureEndCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_CaptureEnd callback);

/**
 * @brief Registers a callback to listen for frame shutter end events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterFrameShutterEndCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_OnFrameShutterEnd callback);

/**
 * @brief Unregisters the callback used to listen for frame shutter end events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterFrameShutterEndCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_OnFrameShutterEnd callback);

/**
 * @brief Registers a callback to listen for camera ready events. When the callback is received, the next capture can
 * be performed.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterCaptureReadyCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_CaptureReady callback);

/**
 * @brief Unregisters the callback used to listen for camera ready events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterCaptureReadyCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_CaptureReady callback);

/**
 * @brief Registers a callback to listen for estimated capture duration events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterEstimatedCaptureDurationCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_EstimatedCaptureDuration callback);

/**
 * @brief Unregisters the callback used to listen for estimated capture duration events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterEstimatedCaptureDurationCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_EstimatedCaptureDuration callback);

/**
 * @brief Registers a callback to listen for photo availability events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterPhotoAvailableCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_PhotoAvailable callback);

/**
 * @brief Unregisters the callback used to listen for photo availability events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterPhotoAvailableCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_PhotoAvailable callback);

/**
 * @brief Registers a callback to listen for photo asset availability events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_RegisterPhotoAssetAvailableCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_PhotoAssetAvailable callback);

/**
 * @brief Unregisters the callback used to listen for photo asset availability events.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param callback Target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_UnregisterPhotoAssetAvailableCallback(Camera_PhotoOutput* photoOutput,
    OH_PhotoOutput_PhotoAssetAvailable callback);

/**
 * @brief Captures a photo.
 * This function must be called in prior to {@link OH_PreviewOutput_Release}. Otherwise, photo capture fails.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_RUNNING**: The capture session is not running.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_PhotoOutput_Capture(Camera_PhotoOutput* photoOutput);

/**
 * @brief Captures a photo with photographing parameters.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param setting Photographing parameters, which are defined in the {@link Camera_PhotoCaptureSetting} struct.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_RUNNING**: The capture session is not running.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_PhotoOutput_Capture_WithCaptureSetting(Camera_PhotoOutput* photoOutput,
    Camera_PhotoCaptureSetting setting);

/**
 * @brief Releases a PhotoOutput instance.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_PhotoOutput_Release(Camera_PhotoOutput* photoOutput);

/**
 * @brief Checks whether mirroring is supported.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param isSupported Pointer to the check result for the support of mirroring. **true** if supported, **false**
 * otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_PhotoOutput_IsMirrorSupported(Camera_PhotoOutput* photoOutput, bool* isSupported);

/**
 * @brief Enables dynamic photo capture.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param enabled Whether to enable or disable dynamic photo capture. **true** to enable, **false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 13
 */
Camera_ErrorCode OH_PhotoOutput_EnableMirror(Camera_PhotoOutput* photoOutput, bool enabled);

/**
 * @brief Obtains the profile of a PhotoOutput instance.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param profile Double pointer to the photo output profile obtained.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_GetActiveProfile(Camera_PhotoOutput* photoOutput, Camera_Profile** profile);

/**
 * @brief Deletes the profile of a PhotoOutput instance.
 * 
 * @param profile Pointer to the target PhotoOutput instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_DeleteProfile(Camera_Profile* profile);

/**
 * @brief Checks whether moving photos are supported.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param isSupported Pointer to the check result for the support of moving photos. **true** if supported, **false**
 * otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_IsMovingPhotoSupported(Camera_PhotoOutput* photoOutput, bool* isSupported);

/**
 * @brief Enables or disables moving photos.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param enabled Whether to enable moving photos. **true** to enable, **false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_PhotoOutput_EnableMovingPhoto(Camera_PhotoOutput* photoOutput, bool enabled);

/**
 * @brief Checks whether the specified photo quality prioritization strategy is supported.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param qualityPrioritization Photo quality prioritization strategy.
 * @param isSupported Pointer to the check result for the support of the specified photo quality prioritization
 * strategy. **true** if supported, **false** otherwise.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 21
 */
Camera_ErrorCode OH_PhotoOutput_IsPhotoQualityPrioritizationSupported(Camera_PhotoOutput* photoOutput, 
    Camera_PhotoQualityPrioritization qualityPrioritization, bool* isSupported);

/**
 * @brief Sets the photo quality prioritization strategy.
 * 
 * @param photoOutput Pointer to the target PhotoOutput instance.
 * @param qualityPrioritization Photo quality prioritization strategy.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_OPERATION_NOT_ALLOWED**: The operation is not allowed.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 21
 */
Camera_ErrorCode OH_PhotoOutput_SetPhotoQualityPrioritization(Camera_PhotoOutput* photoOutput,
    Camera_PhotoQualityPrioritization qualityPrioritization);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_PHOTOOUTPUT_H
/** @} */

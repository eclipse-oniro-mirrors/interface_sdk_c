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
 * @file video_output.h
 *
 * @brief The file declares the video output concepts.
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 11
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_CAMERA_VIDEOOUTPUT_H
#define NATIVE_INCLUDE_CAMERA_VIDEOOUTPUT_H

#include <stdint.h>
#include <stdio.h>
#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct describes the video output object.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_VideoOutput Camera_VideoOutput;

/**
 * @brief Defines the callback defined in the {@link VideoOutput_Callbacks} struct and used to report video output
 * frame start events.
 * 
 * @param videoOutput Pointer to the VideoOutput instance that transfers the callback.
 * @since 11
 */
typedef void (*OH_VideoOutput_OnFrameStart)(Camera_VideoOutput* videoOutput);

/**
 * @brief Defines the callback defined in the {@link VideoOutput_Callbacks} struct and used to report video output
 * frame end events.
 * 
 * @param videoOutput Pointer to the VideoOutput instance that transfers the callback.
 * @param frameCount Number of frames to be included in the callback.
 * @since 11
 */
typedef void (*OH_VideoOutput_OnFrameEnd)(Camera_VideoOutput* videoOutput, int32_t frameCount);

/**
 * @brief Defines the callback defined in the {@link VideoOutput_Callbacks} struct and used to report video output
 * errors.
 * 
 * @param videoOutput Pointer to the VideoOutput instance that transfers the callback.
 * @param errorCode Error code reported during video output.
 * @see CAMERA_SERVICE_FATAL_ERROR
 * @since 11
 */
typedef void (*OH_VideoOutput_OnError)(Camera_VideoOutput* videoOutput, Camera_ErrorCode errorCode);

/**
 * @brief The struct describes the callbacks related to video output.
 * 
 * @see OH_VideoOutput_RegisterCallback
 * @since 11
 * @version 1.0
 */
typedef struct VideoOutput_Callbacks {
    /**
     * Callback to report video output frame start events.
     */
    OH_VideoOutput_OnFrameStart onFrameStart;

    /**
     * Callback to report video output frame end events.
     */
    OH_VideoOutput_OnFrameEnd onFrameEnd;

    /**
     * Callback to report video output errors.
     */
    OH_VideoOutput_OnError onError;
} VideoOutput_Callbacks;

/**
 * @brief Registers a callback to listen for video output events.
 * 
 * @param videoOutput Pointer to the target VideoOutput instance.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_VideoOutput_RegisterCallback(Camera_VideoOutput* videoOutput, VideoOutput_Callbacks* callback);

/**
 * @brief Unregisters the callback used to listen for video output events.
 * 
 * @param videoOutput Pointer to the target VideoOutput instance.
 * @param callback Pointer to the target callback.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 11
 */
Camera_ErrorCode OH_VideoOutput_UnregisterCallback(Camera_VideoOutput* videoOutput, VideoOutput_Callbacks* callback);

/**
 * @brief Starts video output.
 * 
 * @param videoOutput Pointer to the VideoOutput instance to start.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SESSION_NOT_CONFIG**: The capture session is not configured.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_VideoOutput_Start(Camera_VideoOutput* videoOutput);

/**
 * @brief Stops video output.
 * 
 * @param videoOutput Pointer to the VideoOutput instance to stop.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_VideoOutput_Stop(Camera_VideoOutput* videoOutput);

/**
 * @brief Releases a VideoOutput instance.
 * 
 * @param videoOutput Pointer to the VideoOutput instance to release.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_VideoOutput_Release(Camera_VideoOutput* videoOutput);

/**
 * @brief Obtains the profile of a VideoOutput instance.
 * 
 * @param videoOutput Pointer to the VideoOutput instance for which the profile is to be obtained.
 * @param profile Double pointer to the video output profile obtained.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_VideoOutput_GetActiveProfile(Camera_VideoOutput* videoOutput, Camera_VideoProfile** profile);

/**
 * @brief Deletes the profile of a VideoOutput instance.
 * 
 * @param profile Pointer to the profile to delete.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_VideoOutput_DeleteProfile(Camera_VideoProfile* profile);

/**
 * @brief Check whether mirror mode is supported for videoOutput
 *
 * @param videoOutput the {@link Camera_VideoOutput} instance
 * @param isSupported the result of whether mirror mode supported.
 * @return {@link #CAMERA_OK} if the method call succeeds.
 *         {@link #CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link #CAMERA_SERVICE_FATAL_ERROR} if camera service fatal error.
 * @since 15
 */
Camera_ErrorCode OH_VideoOutput_IsMirrorSupported(Camera_VideoOutput* videoOutput, bool* isSupported);

/**
 * @brief Enable or disable mirror mode for videoOutput
 *
 * @param videoOutput the {@link Camera_VideoOutput} instance
 * @param mirrorMode enable mirror mode if mirrorMode is TRUE, otherwise disable
 * @return {@link #CAMERA_OK} if the method call succeeds.
 *         {@link #CAMERA_INVALID_ARGUMENT} if parameter missing or parameter type incorrect.
 *         {@link #CAMERA_SERVICE_FATAL_ERROR} if camera service fatal error.
 * @since 15
 */
Camera_ErrorCode OH_VideoOutput_EnableMirror(Camera_VideoOutput* videoOutput, bool mirrorMode);

/**
 * @brief Obtains the rotation angle of a video.
 * 
 * @param videoOutput Pointer to the target VideoOutput instance.
 * @param deviceDegree Clockwise rotation angle of the device relative to the natural direction (the charging port
 * faces downward).
 * @param imageRotation Pointer to the rotation angle of the video output.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode  OH_VideoOutput_GetVideoRotation(Camera_VideoOutput* videoOutput, int deviceDegree,
    Camera_ImageRotation* imageRotation);

/**
 * @brief Obtains the rotation angle of a video.
 * 
 * @param videoOutput Pointer to the target VideoOutput instance.
 * @param imageRotation Pointer to the rotation angle of the video output.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 23
 */
Camera_ErrorCode  OH_VideoOutput_GetVideoRotationWithoutDeviceDegree(Camera_VideoOutput* videoOutput,
    Camera_ImageRotation* imageRotation);

/**
 * @brief Obtains the list of frame rates supported by a VideoOutput instance.
 * 
 * @param videoOutput Pointer to the target VideoOutput instance.
 * @param frameRateRange Double pointer to the list of frame rates, if the function is successfully called.
 * @param size Pointer to the size of the list of frame rates.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_VideoOutput_GetSupportedFrameRates(Camera_VideoOutput* videoOutput,
    Camera_FrameRateRange** frameRateRange, uint32_t* size);

/**
 * @brief Deletes the frame rate list.
 * 
 * @param videoOutput Pointer to the target VideoOutput instance.
 * @param frameRateRange Pointer to the list of frame rates to delete.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_VideoOutput_DeleteFrameRates(Camera_VideoOutput* videoOutput,
    Camera_FrameRateRange* frameRateRange);

/**
 * @brief Sets the frame rates for a VideoOutput instance.
 * 
 * @param videoOutput Pointer to the VideoOutput instance for which the frame rates are to be set.
 * @param minFps Minimum frame rate.
 * @param maxFps Maximum frame rate.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 */
Camera_ErrorCode OH_VideoOutput_SetFrameRate(Camera_VideoOutput* videoOutput,
    int32_t minFps, int32_t maxFps);

/**
 * @brief Obtains the active frame rates of a VideoOutput instance.
 * 
 * @param videoOutput Pointer to the target VideoOutput instance.
 * @param frameRateRange Pointer to the frame rate range, if the function is successfully called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 12
 */
Camera_ErrorCode OH_VideoOutput_GetActiveFrameRate(Camera_VideoOutput* videoOutput,
    Camera_FrameRateRange* frameRateRange);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_VIDEOOUTPUT_H
/** @} */

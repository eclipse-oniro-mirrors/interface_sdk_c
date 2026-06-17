/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup WindowManager
 * @{
 *
 * @brief Provides abilities of windowManager on the native side, such as picture in picture window.
 *
 * @since 12
 */

/**
 * @file oh_window_pip.h
 *
 * @brief The file declares the APIs related to the Picture in Picture (PiP) feature, including creating and deleting a
 * PiP controller, and starting and stopping PiP. PiP is mainly used in video playback, live streaming, video calls, or
 * video meetings.
 *
 * @kit ArkUI
 * @library libnative_window_manager.so
 * @syscap SystemCapability.Window.SessionManager
 * @since 20
 * @version 1.0
 */
#ifndef OH_WINDOW_PIP_H
#define OH_WINDOW_PIP_H

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Picture in picture config.
 * @since 20
 */
typedef void* PictureInPicture_PipConfig;

/**
 * @brief Enumerates the types of PiP templates.
 *
 * @since 20
 */
typedef enum {
    /**
     * Video playback template. A PiP window will be started during video playback, and the video playback template is
     * loaded.
     * @since 20
     */
    VIDEO_PLAY = 0,
    /**
     * Video call template. A PiP window will be started during a video call, and the video call template will be
     * loaded.
     * @since 20
     */
    VIDEO_CALL = 1,
    /**
     * Video meeting template. A PiP window will be started during a video meeting, and the video meeting template will
     * be loaded.
     * @since 20
     */
    VIDEO_MEETING = 2,

    /**
     * Live template. A PiP window will be started during a live, and the live template is loaded.
     * @since 20
     */
    VIDEO_LIVE = 3,
} PictureInPicture_PipTemplateType;

/**
 * @brief Enumerates the types of component groups displayed on the PiP controller.
 *
 * @since 20
 */
typedef enum {
    /**
     * Previous/Next component group for video playback. This component group is mutually exclusive with the fast-
     * forward/rewind component group. It cannot be added if the fast-forward/rewind component group is added.
     * @since 20
     */
    VIDEO_PLAY_VIDEO_PREVIOUS_NEXT = 101,
    /**
     * Fast-forward/Rewind component group for video playback. This component group is mutually exclusive with the
     * previous/next component group. It cannot be added if the previous/next component group is added.
     * @since 20
     */
    VIDEO_PLAY_FAST_FORWARD_BACKWARD = 102,
    /**
     * Microphone on/off component group for video calls.
     * @since 20
     */
    VIDEO_CALL_MICROPHONE_SWITCH = 201,
    /**
     * Hang-up component group for video calls.
     * @since 20
     */
    VIDEO_CALL_HANG_UP_BUTTON = 202,
    /**
     * Camera on/off component group for video calls.
     * @since 20
     */
    VIDEO_CALL_CAMERA_SWITCH = 203,
    /**
     * Mute component group for video calls.
     * @since 20
     */
    VIDEO_CALL_MUTE_SWITCH = 204,
    /**
     * Hang-up component group for video meetings.
     * @since 20
     */
    VIDEO_MEETING_HANG_UP_BUTTON = 301,
    /**
     * Camera on/off component group for video meetings.
     * @since 20
     */
    VIDEO_MEETING_CAMERA_SWITCH = 302,
    /**
     * Mute component group for video meetings.
     * @since 20
     */
    VIDEO_MEETING_MUTE_SWITCH = 303,
    /**
     * Microphone on/off component group for video meetings.
     * @since 20
     */
    VIDEO_MEETING_MICROPHONE_SWITCH = 304,
    /**
     * Play/Pause component group for live streaming.
     * @since 20
     */
    VIDEO_LIVE_VIDEO_PLAY_PAUSE = 401,
    /**
     * Mute component group for live streaming.
     * @since 20
     */
    VIDEO_LIVE_MUTE_SWITCH = 402,
} PictureInPicture_PipControlGroup;

/**
 * @brief Enumerates the types of components displayed on the PiP controller.
 *
 * @since 20
 */
typedef enum {
    /**
     * Play/Pause component.
     * @since 20
     */
    VIDEO_PLAY_PAUSE = 0,
    /**
     * Previous component in video scenarios.
     * @since 20
     */
    VIDEO_PREVIOUS = 1,
    /**
     * Next component in video scenarios.
     * @since 20
     */
    VIDEO_NEXT = 2,
    /**
     * Fast-forward component in video scenarios.
     * @since 20
     */
    FAST_FORWARD = 3,
    /**
     * Rewind component in video scenarios.
     * @since 20
     */
    FAST_BACKWARD = 4,
    /**
     * Hang-up component.
     * @since 20
     */
    HANG_UP_BUTTON = 5,
    /**
     * Microphone on/off component.
     * @since 20
     */
    MICROPHONE_SWITCH = 6,
    /**
     * Camera on/off component.
     * @since 20
     */
    CAMERA_SWITCH = 7,
    /**
     * Mute/Unmute component.
     * @since 20
     */
    MUTE_SWITCH = 8,
} PictureInPicture_PipControlType;

/**
 * @brief Enumerates the statuses of components displayed on the PiP controller.
 *
 * @since 20
 */
typedef enum {
    /**
     * A video is playing.
     * @since 20
     */
    PLAY = 1,
    /**
     * A video is paused.
     * @since 20
     */
    PAUSE = 0,
    /**
     * The camera, microphone, and mute components are enabled.
     * @since 20
     */
    OPEN = 1,
    /**
     * The camera, microphone, and mute components are disabled.
     * @since 20
     */
    CLOSE = 0,
} PictureInPicture_PipControlStatus;

/**
 * @brief Enumerates the PiP lifecycle states.
 *
 * @since 20
 */
typedef enum {
    /**
     * PiP is about to start.
     * @since 20
     */
    ABOUT_TO_START = 1,
    /**
     * PiP is started.
     * @since 20
     */
    STARTED = 2,
    /**
     * PiP is about to stop.
     * @since 20
     */
    ABOUT_TO_STOP = 3,
    /**
     * PiP is stopped.
     * @since 20
     */
    STOPPED = 4,
    /**
     * The original page is about to restore.
     * @since 20
     */
    ABOUT_TO_RESTORE = 5,
    /**
     * An error occurs during the execution of the PiP lifecycle.
     * @since 20
     */
    ERROR = 6,
} PictureInPicture_PipState;

/**
 * @brief Defines a callback function for PiP window creation.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param requestId Request ID, which indicates the number of times the PiP window has been requested to be pulled up.
 * @param surfaceId Surface ID of the **XComponent** in PiP. It is used for application rendering.
 * @since 20
 */
typedef void (*WebPipStartPipCallback)(uint32_t controllerId, uint8_t requestId, uint64_t surfaceId);

/**
 * @brief Defines a callback function for PiP window lifecycle changes.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param state PiP lifecycle state.
 * @param errcode Common status codes of PiP APIs. For details, see {@link WindowManager_ErrorCode}.
 * @since 20
 */
typedef void (*WebPipLifecycleCallback)(uint32_t controllerId, PictureInPicture_PipState state, int32_t errcode);

/**
 * @brief Defines a callback function for the component click event of the PiP window.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param controlType Type of component displayed on the PiP controller.
 * @param status Status of the component displayed on the PiP controller.
 * @since 20
 */
typedef void (*WebPipControlEventCallback)(uint32_t controllerId, PictureInPicture_PipControlType controlType,
    PictureInPicture_PipControlStatus status);

/**
 * @brief Defines a callback function for PiP window size changes.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param width PiP window width, in px. The value is a positive integer and cannot be greater than the screen width.
 * @param height PiP window height, in px. The value is a positive integer and cannot be greater than the screen
 *               height.
 * @param scale Scale factor of the PiP window, representing the display size relative to the width and height. The
 *              value is a floating-point number in the range (0.0, 1.0]. The value **1** means that the PiP window
 *              matches specified width and height.
 * @since 20
 */
typedef void (*WebPipResizeCallback)(uint32_t controllerId, uint32_t width, uint32_t height, double scale);

/**
 * @brief Creates a PiP configuration.
 *
 * @param pipConfig Pointer to the PiP parameter configuration.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 * @since 20
 */
int32_t OH_PictureInPicture_CreatePipConfig(PictureInPicture_PipConfig* pipConfig);

/**
 * @brief Destroys a PiP configuration.
 *
 * @param pipConfig Pointer to the PiP configuration.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 * @since 20
 */
int32_t OH_PictureInPicture_DestroyPipConfig(PictureInPicture_PipConfig* pipConfig);

/**
 * @brief Sets the ID of the main window that launches PiP.
 *
 * @param pipConfig PiP configuration.
 * @param mainWindowId ID of the main window that launches PiP.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipMainWindowId(PictureInPicture_PipConfig pipConfig, uint32_t mainWindowId);

/**
 * @brief Sets the PiP template type. The default value is video playback.
 *
 * @param pipConfig PiP configuration.
 * @param pipTemplateType Type of the PiP template.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipTemplateType(PictureInPicture_PipConfig pipConfig,
    PictureInPicture_PipTemplateType pipTemplateType);

/**
 * @brief Sets the size of the PiP window for calculating the aspect ratio.
 *
 * @param pipConfig PiP configuration.
 * @param width Width of the original content, in px. The value must be a positive integer. It is used to determine the
 *              aspect ratio of the PiP window.
 * @param height Height of the original content, in px. The value must be a positive integer. It is used to determine
 *               the aspect ratio of the PiP window.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipRect(PictureInPicture_PipConfig pipConfig, uint32_t width, uint32_t height);

/**
 * @brief Sets a PiP component group, which must match the template type.
 *
 * @param pipConfig PiP configuration.
 * @param controlGroup Pointer to an optional component group of the PiP controller. An application can configure
 *                     whether to display these optional components. If this parameter is not set for an application,
 *                     the basic components (for example, play/pause of the video playback component group) are
 *                     displayed. A maximum of three components can be configured.
 * @param controlGroupLength Number of components in the PiP component group. The value ranges from 0 to 3.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipControlGroup(PictureInPicture_PipConfig pipConfig,
    PictureInPicture_PipControlGroup* controlGroup, uint8_t controlGroupLength);

/**
 * @brief Sets the runtime environment for launching PiP.
 *
 * @param pipConfig PiP configuration.
 * @param env Pointer to the NAPI environment.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipNapiEnv(PictureInPicture_PipConfig pipConfig, void* env);

/**
 * @brief Creates a PiP controller.
 *
 * @param pipConfig PiP configuration.
 * @param controllerId Pointer to the ID of the PiP controller created.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_CreatePip(PictureInPicture_PipConfig pipConfig, uint32_t* controllerId);

/**
 * @brief Deletes a PiP controller.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @return Return the result code.
 *         {@link OK} The function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 * @since 20
 */
int32_t OH_PictureInPicture_DeletePip(uint32_t controllerId);

/**
 * @brief Starts PiP.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_STATE_ABNORMAL} the PiP window state is abnormal.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_CREATE_FAILED} failed to create the PiP window.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_REPEATED_OPERATION} repeated PiP operation.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 * @since 20
 */
int32_t OH_PictureInPicture_StartPip(uint32_t controllerId);

 /**
 * @brief Stops PiP.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_DESTROY_FAILED} failed to destroy the PiP window.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_STATE_ABNORMAL} the PiP window state is abnormal.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_REPEATED_OPERATION} repeated PiP operation.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 * @since 20
 */
int32_t OH_PictureInPicture_StopPip(uint32_t controllerId);

/**
 * @brief Updates the media content size when the media content changes.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param width Width of the media content, in px. The value must be a positive integer. It is used to update the
 *              aspect ratio of the PiP window.
 * @param height Height of the media content, in px. The value must be a positive integer. It is used to update the
 *               aspect ratio of the PiP window.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_UpdatePipContentSize(uint32_t controllerId, uint32_t width, uint32_t height);

/**
 * @brief Updates the PiP component status.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param controlType Type of the component displayed on the PiP controller. Currently, only **VIDEO_PLAY_PAUSE**, **
 *                    MICROPHONE_SWITCH**, **CAMERA_SWITCH**, and **MUTE_SWITCH** are supported.
 * @param status Status of the component displayed on the PiP controller.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_UpdatePipControlStatus(uint32_t controllerId, PictureInPicture_PipControlType controlType,
    PictureInPicture_PipControlStatus status);

/**
 * @brief Sets the PiP component enabled status.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param controlType Type of the component displayed on the PiP controller.
 * @param enabled Enabled status of the component displayed on the PiP controller. **true** if enabled, **false**
 *                otherwise.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipControlEnabled(uint32_t controllerId, PictureInPicture_PipControlType controlType,
    bool enabled);

/**
 * @brief Sets the main window ID for PiP.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param windowId ID of the main window. The value is a non-negative integer.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 22
 */
int32_t OH_PictureInPicture_SetParentWindowId(uint32_t controllerId, uint32_t windowId);

/**
 * @brief Sets the initial position and size of the PiP surface when the PiP launch animation starts. It can be used to
 * achieve a seamless transition effect.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param positionX X coordinate of the PiP window relative to the top-left corner of the screen when the PiP window is
 *                  started, in px.
 * @param positionY Y coordinate of the PiP window relative to the top-left corner of the screen when the PiP window is
 *                  started, in px.
 * @param width Width of the PiP window when the PiP window is started. The value is greater than 0, measured in px.
 * @param height Height of the PiP window when the PiP window is started. The value is greater than 0, measured in px.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipInitialSurfaceRect(uint32_t controllerId, int32_t positionX, int32_t positionY,
    uint32_t width, uint32_t height);

/**
 * @brief Cancels the previously set initial position and size for the PiP surface.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_UnsetPipInitialSurfaceRect(uint32_t controllerId);

/**
 * @brief Registers a callback to listen for the completion of PiP surface creation.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param callback Callback function for PiP window creation.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_RegisterStartPipCallback(uint32_t controllerId, WebPipStartPipCallback callback);

/**
 * @brief Unregisters the callback used to listen for the completion of PiP surface creation.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param callback Callback function for PiP window creation.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterStartPipCallback(uint32_t controllerId, WebPipStartPipCallback callback);

/**
 * @brief Unregisters all the callbacks used to listen for the completion of PiP surface creation.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterAllStartPipCallbacks(uint32_t controllerId);

/**
 * @brief Registers a callback to listen for PiP lifecycle state changes.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param callback Callback function for PiP window lifecycle changes.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_RegisterLifecycleListener(uint32_t controllerId, WebPipLifecycleCallback callback);

/**
 * @brief Unregisters the callback used to listen for PiP lifecycle state changes.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param callback Callback function for PiP window lifecycle changes.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterLifecycleListener(uint32_t controllerId, WebPipLifecycleCallback callback);

/**
 * @brief Unregisters all the callbacks used to listen for PiP lifecycle state changes.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterAllLifecycleListeners(uint32_t controllerId);

/**
 * @brief Registers a callback to listen for control panel action events in PiP mode.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param callback Callback function for the component click event of the PiP window.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_RegisterControlEventListener(uint32_t controllerId, WebPipControlEventCallback callback);

/**
 * @brief Unregisters the callback used to listen for control panel action events in PiP mode.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param callback Callback function for the component click event of the PiP window.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterControlEventListener(uint32_t controllerId, WebPipControlEventCallback callback);

/**
 * @brief Unregisters all the callbacks used to listen for control panel action events in PiP mode.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterAllControlEventListeners(uint32_t controllerId);

/**
 * @brief Registers a callback to listen for PiP window size changes.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param callback Callback function for PiP window size changes.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_RegisterResizeListener(uint32_t controllerId, WebPipResizeCallback callback);

/**
 * @brief Unregisters the callback used to listen for PiP window size changes.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @param callback Callback function for PiP window size changes.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterResizeListener(uint32_t controllerId, WebPipResizeCallback callback);

/**
 * @brief Unregisters all the callbacks used to listen for PiP window size changes.
 *
 * @param controllerId ID of the PiP controller. The value is a non-negative integer.
 * @return Return the result code.
 *         {@link OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} parameter error.
 *         {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *         {@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR} pip internal error.
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterAllResizeListeners(uint32_t controllerId);

#ifdef __cplusplus
}
#endif

#endif // OH_WINDOW_PIP_H
/** @} */
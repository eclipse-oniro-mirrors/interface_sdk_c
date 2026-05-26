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
 * @addtogroup AVScreenCapture
 * @{
 *
 * @brief Provides APIs of request capability for Screen Capture.
 * @since 10
 */
/**
 * @file native_avscreen_capture_base.h
 *
 * @brief The file declares the common structs, character constants, and enums used for running screen capture.
 * 
 * @library libnative_avscreen_capture.so
 * @syscap SystemCapability.Multimedia.Media.AVScreenCapture
 * @kit MediaKit
 * @since 10
 */
 
#ifndef NATIVE_AVSCREEN_CAPTURE_BASE_H
#define NATIVE_AVSCREEN_CAPTURE_BASE_H

#include <stdbool.h>
#include <stdint.h>
#include "native_avbuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct describes the native video stream class for screen capture.
 * 
 *
 * @since 10
 */
typedef struct OH_NativeBuffer OH_NativeBuffer;

/**
 * @brief Defines all the asynchronous callback function pointers of an **OH_AVScreenCapture** instance. To ensure the
 * normal running of **OH_AVScreenCapture**, you must register the instance of this struct with the **
 * OH_AVScreenCapture** instance to process the information reported by the callback functions.
 * 
 *
 * @since 10
 */
typedef struct OH_AVScreenCapture OH_AVScreenCapture;

/**
 * @brief The OH_AVScreenCapture_ContentFilter struct describes the filter used to filter audio and video content.
 * 
 *
 * @since 12
 */
typedef struct OH_AVScreenCapture_ContentFilter OH_AVScreenCapture_ContentFilter;

/**
 * @brief Enumerates the screen capture modes.
 * 
 *
 * @since 10
 */
typedef enum OH_CaptureMode {
    /* capture home screen */
    OH_CAPTURE_HOME_SCREEN = 0,
    /* capture a specified screen */
    OH_CAPTURE_SPECIFIED_SCREEN = 1,
    /* capture a specified window */
    OH_CAPTURE_SPECIFIED_WINDOW = 2,
    OH_CAPTURE_INVAILD = -1
} OH_CaptureMode;

/**
 * @brief Enumerates the audio source types during screen capture.
 * 
 *
 * @since 10
 */
typedef enum OH_AudioCaptureSourceType {
    /* Invalid audio source */
    OH_SOURCE_INVALID = -1,
    /* Default audio source */
    OH_SOURCE_DEFAULT = 0,
    /* Microphone */
    OH_MIC = 1,
    /* inner all PlayBack */
    OH_ALL_PLAYBACK = 2,
    /* inner app PlayBack */
    OH_APP_PLAYBACK = 3,
} OH_AudioCaptureSourceType;

/**
 * @brief Enumerates the audio encoding formats.
 * 
 *
 * @since 10
 */
typedef enum OH_AudioCodecFormat {
    /* Default format */
    OH_AUDIO_DEFAULT = 0,
    /* Advanced Audio Coding Low Complexity (AAC-LC) */
    OH_AAC_LC = 3,
    /* Invalid value */
    OH_AUDIO_CODEC_FORMAT_BUTT,
} OH_AudioCodecFormat;

/**
 * @brief Enumerates the video encoding formats.
 * 
 *
 * @since 10
 */
typedef enum OH_VideoCodecFormat {
    /* Default format */
    OH_VIDEO_DEFAULT = 0,
    /* H.264 */
    OH_H264 = 2,
    /* H.265/HEVC */
    OH_H265 = 4,
    /* MPEG4 */
    OH_MPEG4 = 6,
    /* VP8 */
    OH_VP8 = 8,
    /* VP9 */
    OH_VP9 = 10,
    /* Invalid format */
    OH_VIDEO_CODEC_FORMAT_BUTT,
} OH_VideoCodecFormat;

/**
 * @brief Enumerates the data types of screen capture streams.
 * 
 *
 * @since 10
 */
typedef enum OH_DataType {
    /* YUV/RGBA/PCM, etc. original stream */
    OH_ORIGINAL_STREAM = 0,
    /* h264/AAC, etc. encoded stream */
    OH_ENCODED_STREAM = 1,
    /* mp4 file */
    OH_CAPTURE_FILE = 2,
    OH_INVAILD = -1
} OH_DataType;

/**
 * @brief Enumerates the video source formats. Currently, only the RGBA format is supported.
 * 
 *
 * @since 10
 */
typedef enum OH_VideoSourceType {
    /**
     * RGBA format.
     */
    OH_VIDEO_SOURCE_SURFACE_YUV = 0,
    /* Raw encoded data provided through graphic */
    OH_VIDEO_SOURCE_SURFACE_ES,
    /* RGBA video data provided through graphic */
    OH_VIDEO_SOURCE_SURFACE_RGBA,
    /* Invalid value */
    OH_VIDEO_SOURCE_BUTT
} OH_VideoSourceType;

/**
 * @brief Enumerates the types of files generated during screen capture.
 * 
 *
 * @since 10
 */
typedef enum OH_ContainerFormatType {
    /* Audio format type -- m4a */
    CFT_MPEG_4A = 0,
    /* Video format type -- mp4 */
    CFT_MPEG_4 = 1
} OH_ContainerFormatType;

/**
 * @brief The struct describes the audio capture information.
 * 
 *
 * @since 10
 */
typedef struct OH_AudioCaptureInfo {
    /* Audio capture sample rate info, in Hz */
    int32_t audioSampleRate;
    /* Audio capture channel info */
    int32_t audioChannels;
    /* Audio capture source type */
    OH_AudioCaptureSourceType audioSource;
} OH_AudioCaptureInfo;

/**
 * @brief The struct describes the audio encoding information.
 * 
 *
 * @since 10
 */
typedef struct OH_AudioEncInfo {
    /* Audio encoder bitrate, in bit/s */
    int32_t audioBitrate;
    /* Audio codec format */
    OH_AudioCodecFormat audioCodecformat;
} OH_AudioEncInfo;

/**
 * @brief The struct describes the audio information.
 * 
 *
 * @since 10
 */
typedef struct OH_AudioInfo {
    /* Audio capture info of microphone */
    OH_AudioCaptureInfo micCapInfo;
    /* Audio capture info of inner */
    OH_AudioCaptureInfo innerCapInfo;
    /* Audio encoder info, no need to set, while dataType = OH_ORIGINAL_STREAM */
    OH_AudioEncInfo audioEncInfo;
} OH_AudioInfo;

/**
 * @brief The struct describes the video capture information. When **videoFrameWidth** and **videoFrameHeight** are
 * both **0**, video-related parameters are ignored and screen data is not recorded.
 * 
 *
 * @since 10
 */
typedef struct OH_VideoCaptureInfo {
    /* Display id, should be set while captureMode = CAPTURE_SPECIFIED_SCREEN */
    uint64_t displayId;
    /* The  ids of mission, should be set while captureMode = CAPTURE_SPECIFIED_WINDOW */
    int32_t *missionIDs;
    /* Mission ids length, should be set while captureMode = CAPTURE_SPECIFIED_WINDOW */
    int32_t missionIDsLen;
    /* Video frame width of avscreeencapture, in px */
    int32_t videoFrameWidth;
    /* Video frame height of avscreeencapture, in px */
    int32_t videoFrameHeight;
    /* Video source type of avscreeencapture */
    OH_VideoSourceType videoSource;
} OH_VideoCaptureInfo;

/**
 * @brief The struct describes the video encoding information.
 * 
 *
 * @since 10
 */
typedef struct OH_VideoEncInfo {
    /* Video encoder format */
    OH_VideoCodecFormat videoCodec;
    /* Video encoder bitrate, in bit/s */
    int32_t videoBitrate;
    /* Video encoder frame rate, in fps */
    int32_t videoFrameRate;
} OH_VideoEncInfo;

/**
 * @brief The struct describes the video information.
 * 
 *
 * @since 10
 */
typedef struct OH_VideoInfo {
    /* Video capture info */
    OH_VideoCaptureInfo videoCapInfo;
    /* Video encoder info */
    OH_VideoEncInfo videoEncInfo;
} OH_VideoInfo;

/**
 * @brief The struct describes the recording file information.
 * 
 *
 * @since 10
 */
typedef struct OH_RecorderInfo {
    /* Recorder file url */
    char *url;
    /* Recorder file url length */
    uint32_t urlLen;
    /* Recorder file format */
    OH_ContainerFormatType fileFormat;
} OH_RecorderInfo;

/**
 * @brief The struct describes the screen capture configuration.
 * 
 *
 * @since 10
 */
typedef struct OH_AVScreenCaptureConfig {
    OH_CaptureMode captureMode;
    OH_DataType dataType;
    OH_AudioInfo audioInfo;
    OH_VideoInfo videoInfo;
    /* should be set, while dataType = OH_CAPTURE_FILE */
    OH_RecorderInfo recorderInfo;
} OH_AVScreenCaptureConfig;

/**
 * @brief Defines the privacy protection information.
 * 
 * @since 24
 */
typedef struct OH_PrivacyProtectInfo {
    /**
     * @brief 
     * @since 24
     */
    bool systemWindowProtection;
    /**
     * @brief 
     * @since 24
     */
    bool sensitiveAppProtection;
} OH_PrivacyProtectInfo;

/**
 * @brief Called when an error occurs during the running of an OH_AVScreenCapture instance.
 * Starting from API version 12, you are advised to use {@link OH_AVScreenCapture_OnError} instead.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param errorCode Error code.
 * @since 10
 */
typedef void (*OH_AVScreenCaptureOnError)(OH_AVScreenCapture *capture, int32_t errorCode);

/**
 * @brief Called when an audio buffer is available during the running of an OH_AVScreenCapture instance.
 * Starting from API version 12, you are advised to use {@link OH_AVScreenCapture_OnBufferAvailable} instead.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param isReady Whether the audio buffer is available. The values include **true** (yes) and **false** (no).
 * @param type Audio source type.
 * @since 10
 */
typedef void (*OH_AVScreenCaptureOnAudioBufferAvailable)(OH_AVScreenCapture *capture, bool isReady,
    OH_AudioCaptureSourceType type);

/**
 * @brief Called when a video buffer is available during the running of an OH_AVScreenCapture instance.
 * Starting from API version 12, you are advised to use {@link OH_AVScreenCapture_OnBufferAvailable} instead.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param isReady Whether the video buffer is available. The values include **true** (yes) and **false** (no).
 * @since 10
 */
typedef void (*OH_AVScreenCaptureOnVideoBufferAvailable)(OH_AVScreenCapture *capture, bool isReady);

/**
 * @brief Defines all the asynchronous callback function pointers of an **OH_AVScreenCapture** instance. To ensure the
 * normal running of **OH_AVScreenCapture**, you must register the instance of this struct with the **
 * OH_AVScreenCapture** instance to process the information reported by the callback functions.
 * 
 * @param onError Monitor OH_AVScreenCapture operation errors, refer to {@link OH_AVScreenCaptureOnError}
 * @param onAudioBufferAvailable Monitor audio buffer, refer to {@link OH_AVScreenCaptureOnAudioBufferAvailable}
 * @param onVideoBufferAvailable Monitor video buffer, refer to {@link OH_AVScreenCaptureOnVideoBufferAvailable}
 *
 * @since 10
 */
typedef struct OH_AVScreenCaptureCallback {
    OH_AVScreenCaptureOnError onError;
    OH_AVScreenCaptureOnAudioBufferAvailable onAudioBufferAvailable;
    OH_AVScreenCaptureOnVideoBufferAvailable onVideoBufferAvailable;
} OH_AVScreenCaptureCallback;

/**
 * @brief The struct describes the width, height, and image information of the rectangle used for screen capture.
 * 
 *
 * @since 10
 */
typedef struct OH_Rect {
    /* X-coordinate of screen recording */
    int32_t x;
    /* y-coordinate of screen recording */
    int32_t y;
    /* Width of screen recording, in px */
    int32_t width;
    /* Height of screen recording, in px */
    int32_t height;
} OH_Rect;


/**
 * @brief The struct describes the configuration such as the size, type, and timestamp of audio data.
 * 
 *
 * @since 10
 */
typedef struct OH_AudioBuffer {
    /* Audio buffer memory block  */
    uint8_t *buf;
    /* Audio buffer memory block size */
    int32_t size;
    /* Audio buffer timestamp info, in nanosecond */
    int64_t timestamp;
    /* Audio capture source type */
    OH_AudioCaptureSourceType type;
} OH_AudioBuffer;

/**
 * @brief Enumerates the screen capture states.
 * 
 *
 * @since 12
 */
typedef enum OH_AVScreenCaptureStateCode {
    /* Screen capture started by user */
    OH_SCREEN_CAPTURE_STATE_STARTED = 0,
    /* Screen capture canceled by user */
    OH_SCREEN_CAPTURE_STATE_CANCELED = 1,
    /* ScreenCapture stopped by user */
    OH_SCREEN_CAPTURE_STATE_STOPPED_BY_USER = 2,
    /* ScreenCapture interrupted by other screen capture */
    OH_SCREEN_CAPTURE_STATE_INTERRUPTED_BY_OTHER = 3,
    /* ScreenCapture stopped by SIM call */
    OH_SCREEN_CAPTURE_STATE_STOPPED_BY_CALL = 4,
    /* Microphone is temporarily unavailable */
    OH_SCREEN_CAPTURE_STATE_MIC_UNAVAILABLE = 5,
    /* Microphone is muted by user */
    OH_SCREEN_CAPTURE_STATE_MIC_MUTED_BY_USER = 6,
    /* Microphone is unmuted by user */
    OH_SCREEN_CAPTURE_STATE_MIC_UNMUTED_BY_USER = 7,
    /* Current captured screen has private window */
    OH_SCREEN_CAPTURE_STATE_ENTER_PRIVATE_SCENE = 8,
    /* Private window disappeared on current captured screen*/
    OH_SCREEN_CAPTURE_STATE_EXIT_PRIVATE_SCENE = 9,
    /* ScreenCapture stopped by user switches */
    OH_SCREEN_CAPTURE_STATE_STOPPED_BY_USER_SWITCHES = 10,
    /**
     * @brief Screen capture paused by user
     * @since 26.0.0
     */
    OH_SCREEN_CAPTURE_STATE_PAUSED_BY_USER = 11,
    /**
     * @brief Screen capture resumed by user
     * @since 26.0.0
     */
    OH_SCREEN_CAPTURE_STATE_RESUMED_BY_USER = 12,
    /**
     * @brief Screen capture paused by app
     * @since 26.0.0
     */
    OH_SCREEN_CAPTURE_STATE_PAUSED_BY_APP = 13,
    /**
     * @brief Screen capture resumed by app
     * @since 26.0.0
     */
    OH_SCREEN_CAPTURE_STATE_RESUMED_BY_APP = 14,
} OH_AVScreenCaptureStateCode;

/**
 * @brief Enumerates the buffer types.
 * 
 *
 * @since 12
 */
typedef enum OH_AVScreenCaptureBufferType {
    /* Buffer of video data from screen */
    OH_SCREEN_CAPTURE_BUFFERTYPE_VIDEO = 0,
    /* Buffer of audio data from inner capture */
    OH_SCREEN_CAPTURE_BUFFERTYPE_AUDIO_INNER = 1,
    /* Buffer of audio data from microphone */
    OH_SCREEN_CAPTURE_BUFFERTYPE_AUDIO_MIC = 2,
} OH_AVScreenCaptureBufferType;

/**
 * @brief Enumerates the buffer types.
 * 
 *
 * @since 12
 */
typedef enum OH_AVScreenCaptureFilterableAudioContent {
    /* Audio content of notification sound */
    OH_SCREEN_CAPTURE_NOTIFICATION_AUDIO = 0,
    /* Audio content of the sound of the app itself */
    OH_SCREEN_CAPTURE_CURRENT_APP_AUDIO = 1,
} OH_AVScreenCaptureFilterableAudioContent;

/**
 * @brief Called when the state changes during the running of an OH_AVScreenCapture instance.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param stateCode Status code.
 * @param userData Pointer to the user-defined data carried in the function.
 * @since 12
 */
typedef void (*OH_AVScreenCapture_OnStateChange)(struct OH_AVScreenCapture *capture,
    OH_AVScreenCaptureStateCode stateCode, void *userData);

/**
 * @brief Called when an error occurs during the running of an OH_AVScreenCapture instance.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param errorCode Error code.
 * @param userData Pointer to the user-defined data carried in the function.
 * @since 12
 */
typedef void (*OH_AVScreenCapture_OnError)(OH_AVScreenCapture *capture, int32_t errorCode, void *userData);

/**
 * @brief Called when an audio buffer or a video buffer is available during the running of an OH_AVScreenCapture
 * instance.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param buffer Pointer to the OH_AVBuffer instance. After the callback is triggered, the buffer is no longer valid.
 * @param bufferType Type of the buffer.
 * @param timestamp Timestamp, in nanoseconds.
 * @param userData Pointer to the user-defined data carried in the function.
 * @since 12
 */
typedef void (*OH_AVScreenCapture_OnBufferAvailable)(OH_AVScreenCapture *capture, OH_AVBuffer *buffer,
    OH_AVScreenCaptureBufferType bufferType, int64_t timestamp, void *userData);

/**
 * @brief When one of the display devices start being captured, the function pointer will be called
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param displayId Id of the display device that being captured
 * @param userData Pointer to user specific data
 *
 * @since 15
 */
typedef void (*OH_AVScreenCapture_OnDisplaySelected)(OH_AVScreenCapture *capture, uint64_t displayId, void *userData);

/**
 * @brief Enumerates the screen capture content change events.
 * 
 *
 * @since 20
 */
typedef enum OH_AVScreenCaptureContentChangedEvent_Enum {
    /**
     * The screen capture content is hidden.
     */
    OH_SCREEN_CAPTURE_CONTENT_HIDE = 0,
    /**
     * The screen capture content is visible.
     */
    OH_SCREEN_CAPTURE_CONTENT_VISIBLE = 1,
    /**
     * The screen capture content becomes unavailable. For example, the screen capture window is closed.
     */
    OH_SCREEN_CAPTURE_CONTENT_UNAVAILABLE = 2,
} OH_AVScreenCaptureContentChangedEvent;

/**
 * @brief Called when the screen capture content changes during the running of an OH_AVScreenCapture instance.
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param event enum for content change event
 * @param area capture content rect position
 * @param userData Pointer to user specific data
 *
 * @since 20
 */
typedef void (*OH_AVScreenCapture_OnCaptureContentChanged)(OH_AVScreenCapture* capture, OH_AVScreenCaptureContentChangedEvent event,
    OH_Rect* area, void *userData);


/**
 * @brief Enumerates the display modes of the highlight border shown during screen capture.
 * 
 * @since 22
 */
typedef enum OH_ScreenCaptureHighlightMode {
    /**
     * Highlights the capture area with a full square border. This is the default mode.
     */
    OH_HIGHLIGHT_MODE_CLOSED = 0,
    /**
     * Highlights the capture area with a corner-wrapping border.
     */
    OH_HIGHLIGHT_MODE_CORNER_WRAP = 1,
} OH_ScreenCaptureHighlightMode;

/**
 * @brief The struct describes the style of the highlight border shown during screen capture, including its shape,
 * thickness, and color.
 * 
 * @since 22
 */
typedef struct OH_AVScreenCaptureHighlightConfig {
    /**
     * Shape of the highlight border. If this variable is not set, a full rectangle is used by default.
     */
    OH_ScreenCaptureHighlightMode mode;
    /**
     * Thickness of the border line. If this variable is not set, the border is invisible by default. The valid value
     * range is 1 vp to 8 vp.
     */
    uint32_t lineThickness;
    /**
     * Color of the border line. The default value is black. Valid values are in RGB (0-0xffffff) or non-transparent
     * ARGB (0xff000000-0xffffffff) format.
     */
    uint32_t lineColor;  
} OH_AVScreenCaptureHighlightConfig;

/**
 * @brief Enumerates the image fill modes.
 * 
 * @since 20
 */
typedef enum OH_AVScreenCapture_FillMode {
    /**
     * Keeps the original aspect ratio of the image to fit the target size. Black bars may appear if the aspect ratios
     * differ.
     */
    OH_SCREENCAPTURE_FILLMODE_ASPECT_SCALE_FIT = 0,
    /**
     * Stretches the image to fill the target size. The image may stretch and distort if the aspect ratios differ.
     */
    OH_SCREENCAPTURE_FILLMODE_SCALE_TO_FILL = 1,
} OH_AVScreenCapture_FillMode;

/**
 * @brief Enumerates the display modes of the picker.
 * 
 * @since 22
 */
typedef enum OH_CapturePickerMode {
    /**
     * Displays only a list of windows.
     */
    OH_CAPTURE_PICKER_MODE_WINDOW_ONLY = 0,

    /**
     * Displays only a list of screens.
     */
    OH_CAPTURE_PICKER_MODE_SCREEN_ONLY = 1,

    /**
     * Displays both screens and windows. This is the default mode.
     */
    OH_CAPTURE_PICKER_MODE_SCREEN_AND_WINDOW = 2,
   
    /** 
     * @brief Show application options only. 
     * @since 26.0.0 
     */ 
    OH_CAPTURE_PICKER_MODE_APP_ONLY = 3, 


    /** 
     * @brief Show both window and application options. 
     * @since 26.0.0 
     */ 
    OH_CAPTURE_PICKER_MODE_WINDOW_AND_APP = 4, 


    /** 
     * @brief Show both screen and application options. 
     * @since 26.0.0 
     */ 
    OH_CAPTURE_PICKER_MODE_SCREEN_AND_APP = 5, 


    /** 
     * @brief Show screen, window, and application options. 
     * @since 26.0.0 
     */ 
     OH_CAPTURE_PICKER_MODE_SCREEN_WINDOW_AND_APP = 6,
} OH_CapturePickerMode;

/**
 * @brief The OH_AVScreenCapture_CaptureStrategy struct describes the screen capture strategy.
 * 
 *
 * @since 20
 */
typedef struct OH_AVScreenCapture_CaptureStrategy OH_AVScreenCapture_CaptureStrategy;

/**
 * @brief The OH_AVScreenCapture_UserSelectionInfo struct describes the parameters selected by the user on the
 * authorization UI (selection UI).
 * 
 *
 * @since 20
 */
typedef struct OH_AVScreenCapture_UserSelectionInfo OH_AVScreenCapture_UserSelectionInfo;

/**
 * @brief Called to return the parameters selected by the user on the authorization UI to the application.
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param selections The recording parameter information
 * selected by the user on the authorization interface
 * @param userData Pointer to user specific data
 *
 * @since 20
 */
typedef void (*OH_AVScreenCapture_OnUserSelected)(OH_AVScreenCapture* capture, 
    OH_AVScreenCapture_UserSelectionInfo* selections, void *userData);

/**
 * @brief Defines a struct for the multi-screen recording capability. It includes whether the multi-screen supports
 * joint recording and the width and height of the screen for joint recording.
 * 
 * @since 24
 */
typedef struct OH_MultiDisplayCapability {
    /**
     * Whether multi-screen recording is supported. **true**: yes; **false**: no.
     */
    bool isMultiDisplaySupport;
    /**
     * Width of the screen area that can be recorded, in pixels.
     */
    uint32_t width;
    /**
     * Height of the screen area that can be recorded, in pixels.
     */
    uint32_t height;
} OH_MultiDisplayCapability;

/**
 * @brief Called when a privacy protection event occurs during the running of the {@link OH_AVScreenCapture} instance.
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param privacyProtect Pointer to privacy protect info
 * @param userData Pointer to user specific data
 * @since 24
 */
typedef void (*OH_AVScreenCapture_OnPrivacyProtect)(OH_AVScreenCapture* capture,
    OH_PrivacyProtectInfo* privacyProtect, void *userData);

/**
* @brief Key for obtaining the valid content area information in the screen recording image frame.
* The returned value is an int32_t array. The array length is 4.
* The array elements are defined as [top,left,width,height].
* The value can be obtained from {@link OH_AVFormat_GetIntBuffer}.
* @since 26.0.0
*/
extern const char *OH_SCREEN_CAPTURE_CONTENT_RECT;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSCREEN_CAPTURE_BASE_H
/** @} */
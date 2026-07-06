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
 * @brief 声明用于运行屏幕录制通用的结构体、字符常量、枚举。
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
 * @brief 提供录屏的视频原始码流类。
 * 
 *
 * @since 10
 */
typedef struct OH_NativeBuffer OH_NativeBuffer;

/**
 * @brief 通过OH_AVScreenCapture可以获取视频与音频的原始码流。
 * 
 *
 * @since 10
 */
typedef struct OH_AVScreenCapture OH_AVScreenCapture;

/**
 * @brief 通过OH_AVScreenCapture_ContentFilter过滤音视频内容。
 * 
 *
 * @since 12
 */
typedef struct OH_AVScreenCapture_ContentFilter OH_AVScreenCapture_ContentFilter;

/**
 * @brief 枚举，表示屏幕录制的不同模式。
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
 * @brief 枚举，表示屏幕录制时的音频源类型。
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
 * @brief 枚举，表示音频编码格式。
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
 * @brief 枚举，表示视频编码格式。
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
 * @brief 枚举，表示屏幕录制流的数据格式。
 * 
 * @syscap SystemCapability.Multimedia.Media.AVScreenCapture
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
 * @brief 枚举，表示视频源格式。当前仅支持RGBA格式。
 * 
 *
 * @since 10
 */
typedef enum OH_VideoSourceType {
    /**
     * RGBA格式。
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
 * @brief 枚举，表示屏幕录制生成的文件类型。
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
 * @brief 音频采样信息。
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
 * @brief 音频编码信息。
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
 * @brief 音频信息。
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
 * @brief 视频录制信息。当videoFrameWidth和videoFrameHeight同时为0时，忽略视频相关参数不录制屏幕数据。
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
 * @brief 视频编码参数。
 * 
 * @syscap SystemCapability.Multimedia.Media.AVScreenCapture
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
 * @brief 视频信息。
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
 * @brief 录制文件信息。
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
 * @brief 屏幕录制配置参数。
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
 * @brief 隐私保护信息结构体。
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
 * @brief 当OH_AVScreenCapture实例运行出错时，将调用函数指针。
 * 从API version 12开始，推荐使用接口{@link OH_AVScreenCapture_OnError}替代。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param errorCode 指定错误码。
 * @since 10
 */
typedef void (*OH_AVScreenCaptureOnError)(OH_AVScreenCapture *capture, int32_t errorCode);

/**
 * @brief 当OH_AVScreenCapture实例操作期间音频缓存区可用时，将调用函数指针。
 * 从API version 12开始，推荐使用接口{@link OH_AVScreenCapture_OnBufferAvailable}替代。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param isReady 音频缓存区是否可用。true表示音频缓存区可用，false表示音频缓存区不可用。
 * @param type 音频源类型。
 * @since 10
 */
typedef void (*OH_AVScreenCaptureOnAudioBufferAvailable)(OH_AVScreenCapture *capture, bool isReady,
    OH_AudioCaptureSourceType type);

/**
 * @brief 当OH_AVScreenCapture实例操作期间视频缓存区可用时，将调用函数指针。
 * 从API version 12开始，推荐使用接口{@link OH_AVScreenCapture_OnBufferAvailable}替代。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param isReady 视频缓存区是否可用。true表示视频缓存区可用，false表示视频缓存区不可用。
 * @since 10
 */
typedef void (*OH_AVScreenCaptureOnVideoBufferAvailable)(OH_AVScreenCapture *capture, bool isReady);

/**
 * @brief OH_AVScreenCapture中包含所有异步回调函数指针的集合。将该结构体的实例注册到OH_AVScreenCapture实例中，以便处理回调上报的信息，从而保证OH_AVScreenCapture的正常运行。
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
 * @brief 定义录屏界面的宽高以及画面信息。
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
 * @brief 定义了音频数据的大小、类型、时间戳等配置信息。
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
 * @brief 枚举，表示状态码。
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
 * @brief 枚举，表示buffer类型。
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
 * @brief 枚举，表示buffer类型。
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
 * @brief 当OH_AVScreenCapture实例操作期间发生状态变更时，将调用函数指针。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param stateCode 指定状态码。
 * @param userData 指向应用设置该回调处理方法时提供的自定义数据的指针。
 * @since 12
 */
typedef void (*OH_AVScreenCapture_OnStateChange)(struct OH_AVScreenCapture *capture,
    OH_AVScreenCaptureStateCode stateCode, void *userData);

/**
 * @brief 当OH_AVScreenCapture实例操作期间发生错误时，将调用函数指针。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param errorCode 指定错误码。
 * @param userData 指向应用设置该回调处理方法时提供的自定义数据的指针。
 * @since 12
 */
typedef void (*OH_AVScreenCapture_OnError)(OH_AVScreenCapture *capture, int32_t errorCode, void *userData);

/**
 * @brief 当OH_AVScreenCapture实例操作期间音频或视频缓存区可用时，将调用该函数指针。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param buffer 指向OH_AVBuffer缓存区实例的指针，该回调方法执行结束返回后，数据缓存区不再有效。
 * @param bufferType 可用缓存区的数据类型。
 * @param timestamp 时间戳，单位纳秒。
 * @param userData 指向应用设置该回调处理方法时提供的自定义数据的指针。
 * @since 12
 */
typedef void (*OH_AVScreenCapture_OnBufferAvailable)(OH_AVScreenCapture *capture, OH_AVBuffer *buffer,
    OH_AVScreenCaptureBufferType bufferType, int64_t timestamp, void *userData);

/**
 * @brief 枚举，表示录屏内容变更事件。
 * 
 *
 * @since 20
 */
typedef enum OH_AVScreenCaptureContentChangedEvent_Enum {
    /**
     * 录屏内容变为隐藏。
     */
    OH_SCREEN_CAPTURE_CONTENT_HIDE = 0,
    /**
     * 录屏内容变为可见。
     */
    OH_SCREEN_CAPTURE_CONTENT_VISIBLE = 1,
    /**
     * 录屏内容状态变化为不可用，如录屏窗口关闭。
     */
    OH_SCREEN_CAPTURE_CONTENT_UNAVAILABLE = 2,
} OH_AVScreenCaptureContentChangedEvent;

/**
 * @brief 当OH_AVScreenCapture实例操作期间录屏内容变化时，将调用函数指针。
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
 * @brief 表示高亮边框的样式，包括高亮边框的模式、边框宽度和边框颜色。
 * 
 * @since 22
 */
typedef struct OH_AVScreenCaptureHighlightConfig {
    /**
     * 高亮边框的模式，不设置默认为方形全包边框。
     */
    OH_ScreenCaptureHighlightMode mode;
    /**
     * 高亮边框的宽度，不设置默认不显示线宽，宽度有效值范围在1vp-8vp。
     */
    uint32_t lineThickness;
    /**
     * 高亮边框的颜色，不设置默认为黑色，颜色有效值为RGB（0-0xffffff）格式和非透明的ARGB（0xff000000-0xffffffff）格式。
     */
    uint32_t lineColor;  
} OH_AVScreenCaptureHighlightConfig;

/**
 * @brief 枚举，表示屏幕录制高亮边框的模式。
 * 
 * @since 22
 */
typedef enum OH_ScreenCaptureHighlightMode {
    /**
     * 默认模式，用方形全包边框高亮显示录制区域。
     */
    OH_HIGHLIGHT_MODE_CLOSED = 0,
    /**
     * 用四角包裹边框高亮显示录制区域。
     */
    OH_HIGHLIGHT_MODE_CORNER_WRAP = 1,
} OH_ScreenCaptureHighlightMode;

/**
 * @brief 图像填充模式。
 * 
 * @since 20
 */
typedef enum OH_AVScreenCapture_FillMode {
    /**
     * 保持图像原始宽高比匹配目标图像大小，若比例不一致可能存在黑边。
     */
    OH_SCREENCAPTURE_FILLMODE_ASPECT_SCALE_FIT = 0,
    /**
     * 图像拉伸匹配目标图像大小，若比例不一致图像变形。
     */
    OH_SCREENCAPTURE_FILLMODE_SCALE_TO_FILL = 1,
} OH_AVScreenCapture_FillMode;

/**
 * @brief 枚举，表示Picker显示模式。
 * 
 * @since 22
 */
typedef enum OH_CapturePickerMode {
    /**
     * 仅显示窗口模式。
     */
    OH_CAPTURE_PICKER_MODE_WINDOW_ONLY = 0,

    /**
     * 仅显示屏幕模式。
     */
    OH_CAPTURE_PICKER_MODE_SCREEN_ONLY = 1,

    /**
     * 显示屏幕和窗口模式（默认模式）。
     */
    OH_CAPTURE_PICKER_MODE_SCREEN_AND_WINDOW = 2,
} OH_CapturePickerMode;

/**
 * @brief 通过OH_AVScreenCapture_CaptureStrategy设置录屏策略。
 * 
 *
 * @since 20
 */
typedef struct OH_AVScreenCapture_CaptureStrategy OH_AVScreenCapture_CaptureStrategy;

/**
 * @brief 通过OH_AVScreenCapture_UserSelectionInfo获取用户在授权界面（选择界面）选择的参数。
 * 
 *
 * @since 20
 */
typedef struct OH_AVScreenCapture_UserSelectionInfo OH_AVScreenCapture_UserSelectionInfo;

/**
 * @brief 当用户在授权界面（选择界面）选择参数时，功能接口将参数返回给应用程序。
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
 * @brief 多屏幕录制能力信息。多屏场景下，用户选择的多屏幕是否支持联合录制，以及联合录制的屏幕宽度和高度。
 * 
 * @since 24
 */
typedef struct OH_MultiDisplayCapability {
    /**
     * 是否支持多屏幕录制，true表示支持多屏幕录制，false表示不支持多屏幕录制。
     */
    bool isMultiDisplaySupport;
    /**
     * 支持录制的屏幕区域宽度（单位：像素）。
     */
    uint32_t width;
    /**
     * 支持录制的屏幕区域高度（单位：像素）。
     */
    uint32_t height;
} OH_MultiDisplayCapability;

/**
 * @brief 当{@link OH_AVScreenCapture}实例在运行过程中发生隐私保护事件时，函数指针将被调用。
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param privacyProtect Pointer to privacy protect info
 * @param userData Pointer to user specific data
 * @since 24
 */
typedef void (*OH_AVScreenCapture_OnPrivacyProtect)(OH_AVScreenCapture* capture,
    OH_PrivacyProtectInfo* privacyProtect, void *userData);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSCREEN_CAPTURE_BASE_H
/** @} */

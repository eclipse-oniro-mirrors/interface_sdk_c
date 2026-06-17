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
 * @file native_avscreen_capture.h
 *
 * @brief 声明用于构造屏幕录制对象的API。
 * 
 * @library libnative_avscreen_capture.so
 * @syscap SystemCapability.Multimedia.Media.AVScreenCapture
 * @kit MediaKit
 * @since 10
 */

#ifndef NATIVE_AVSCREEN_CAPTURE_H
#define NATIVE_AVSCREEN_CAPTURE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "native_avscreen_capture_errors.h"
#include "native_avscreen_capture_base.h"
#include "native_window/external_window.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 实例化对象，创建OH_AVScreenCapture。
 * 可以通过调用{@link OH_AVScreenCapture_Release}释放实例。
 * 
 * @return 返回一个指向OH_AVScreenCapture实例的指针。
 * @since 10
 */
struct OH_AVScreenCapture *OH_AVScreenCapture_Create(void);

/**
 * @brief 初始化{@link OH_AVScreenCapture}相关参数，包括下发的音频麦克风采样相关参数（可选）、音频内录采样相关参数、视频分辨率相关参数。
 * 录屏存文件场景，应用需要保证视频编码参数、视频采样参数、音频编码参数、音频内录采样参数均合法，音频麦克风采样参数合法（可选）。
 * 录屏出码流场景，应用需要保证音频内录采样参数、视频采样参数至少一个合法，音频麦克风采样参数合法（可选）。
 * 由于结构体变量在初始化时不会对成员进行初始化，应用必须根据使用场景正确设置各项参数。建议应用先将OH_AVScreenCaptureConfig结构体变量的所有内存字节均设置为0，然后再根据录屏场景设置合法参数。
 * 音频采样参数结构体{@link OH_AudioCaptureInfo}，若audioSampleRate和audioChannels同时为0，则录屏实例OH_AVScreenCapture将忽略该类型的音频参数，
 * 且不采集该类型的音频数据。
 * 视频采样参数结构体{@link OH_VideoCaptureInfo}，若videoFrameWidth和videoFrameHeight同时为0，则录屏实例OH_AVScreenCapture将忽略对应视频参数，且不采集屏幕数据。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param config 录屏初始化相关参数。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，初始化配置失败。
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_Init(struct OH_AVScreenCapture *capture,
    OH_AVScreenCaptureConfig config);

/**
 * @brief 开始录屏，采集原始码流。
 * 调用后可以通过回调的监听（{@link OH_AVScreenCapture_OnBufferAvailable}）来监听当前是否有码流的产生,通过回调的监听（{@link OH_AVScreenCapture_OnStateChange}
 * ）来监听启动状态。
 * 通过调用获取音频buffer（{@link OH_AVScreenCapture_AcquireAudioBuffer}）和视频buffer（{@link OH_AVScreenCapture_AcquireVideoBuffer}）
 * 的接口来获取录屏的原始码流。
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_UNSUPPORT（API version 20新增）：设备不支持该操作。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，设置隐私权限启用失败或启动录屏失败。
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StartScreenCapture(struct OH_AVScreenCapture *capture);

/**
 * @brief 结束录屏，与{@link OH_AVScreenCapture_StartScreenCapture}配合使用。调用后针对调用该接口的应用会停止录屏或屏幕共享，释放麦克风。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，结束录屏失败。
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StopScreenCapture(struct OH_AVScreenCapture *capture);

/**
 * @brief 启动录屏，调用此接口，可保存录屏文件。
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_UNSUPPORT（API version 20新增）：设备不支持该操作。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，设置隐私权限启用失败或启用屏幕录制失败。
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StartScreenRecording(struct OH_AVScreenCapture *capture);

/**
 * @brief 停止录屏，与{@link OH_AVScreenCapture_StartScreenRecording}配合使用。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，停止屏幕录制失败。
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StopScreenRecording(struct OH_AVScreenCapture *capture);

/**
 * @brief 获取音频buffer。应用调用时需分配audiobuffer对应结构体大小的内存，否则影响音频buffer的获取。
 * 从API version 12开始，推荐使用接口{@link OH_AVScreenCapture_OnBufferAvailable}替代。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param audiobuffer 保存音频buffer的结构体，通过该结构体获取到音频buffer以及buffer的时间戳等信息。
 * @param type 音频buffer的类型，区分是麦克风录制的外部流还是系统内部播放音频的内录流。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针或输入参数audiobuffer为空指针。
 * AV_SCREEN_CAPTURE_ERR_NO_MEMORY：内存不足，audiobuffer分配失败。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，设置隐私权限启用失败或获取音频buffer失败。
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_AcquireAudioBuffer(struct OH_AVScreenCapture *capture,
    OH_AudioBuffer **audiobuffer, OH_AudioCaptureSourceType type);

/**
 * @brief 获取视频buffer。应用通过此接口获取视频缓存区及时间戳等信息。
 * buffer使用完成后，调用OH_AVScreenCapture_ReleaseVideoBuffer接口进行视频buffer的释放。
 * 从API version 12开始，推荐使用接口{@link OH_AVScreenCapture_OnBufferAvailable}替代。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param fence 用于同步的显示相关参数信息。
 * @param timestamp 视频帧的时间戳。
 * @param region 视频显示相关的坐标信息。
 * @return 执行成功返回OH_NativeBuffer对象，通过OH_NativeBuffer对象相关接口可以获取到视频buffer和分辨率等信息参数。
 * @since 10
 */
OH_NativeBuffer* OH_AVScreenCapture_AcquireVideoBuffer(struct OH_AVScreenCapture *capture,
    int32_t *fence, int64_t *timestamp, struct OH_Rect *region);

/**
 * @brief 根据音频类型释放buffer。当某一帧音频buffer使用完成后，调用此接口进行释放对应的音频buffer。
 * 从API version 12开始，推荐使用接口{@link OH_AVScreenCapture_OnBufferAvailable}替代。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param type 音频buffer的类型，区分麦克风录制的外部流还是系统内部播放音频的内录流。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，不允许用于已设置过DataCallback或释放音频buffer失败。
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ReleaseAudioBuffer(struct OH_AVScreenCapture *capture,
    OH_AudioCaptureSourceType type);

/**
 * @brief 根据视频类型释放buffer。当某一帧视频buffer使用完成后，调用此接口释放对应的视频buffer。
 * 从API version 12开始，推荐使用接口{@link OH_AVScreenCapture_OnBufferAvailable}替代。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，不允许用于已设置过DataCallback或释放视频buffer失败。
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ReleaseVideoBuffer(struct OH_AVScreenCapture *capture);

/**
 * @brief 设置监听接口，通过设置监听，可以监听到调用过程中的错误信息，以及是否有可用的视频buffer和音频buffer。
 * 从API version 12开始，推荐使用接口{@link OH_AVScreenCapture_SetErrorCallback}、{@link OH_AVScreenCapture_SetDataCallback}替代。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param callback OH_AVScreenCaptureCallback的结构体，保存相关回调函数指针。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针或输入参数callback为空指针。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，设置监听接口失败。
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetCallback(struct OH_AVScreenCapture *capture,
    struct OH_AVScreenCaptureCallback callback);

/**
 * @brief 释放创建的OH_AVScreenCapture实例，对应{@link OH_AVScreenCapture_Create}。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，OH_AVScreenCapture实例释放失败。
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_Release(struct OH_AVScreenCapture *capture);

/**
 * @brief 设置麦克风开关。
 * 当isMicrophone为true时，则打开麦克风，通过调用{@link OH_AVScreenCapture_StartScreenCapture}和{@link OH_AVScreenCapture_AcquireAudioBuffer}
 * 可以正常获取到音频的麦克风原始PCM数据；isMicrophone为false时，获取到的音频数据为无声数据。
 * 默认麦克风开关为开启。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param isMicrophone 麦克风开关参数。
 * true表示打开麦克风，false表示关闭麦克风。
 * 默认是true。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，设置麦克风开关失败。
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetMicrophoneEnabled(struct OH_AVScreenCapture *capture,
    bool isMicrophone);

/**
 * @brief 设置状态变更处理回调方法，在开始录制前调用。
 * 调用该方法设置状态变更处理回调方法，当OH_AVScreenCapture实例发生状态变更时，该状态变更处理回调方法将会被调用。
 * 调用该设置方法成功后，在启动录屏时将通过隐私弹窗方式征求用户同意：
 * 1. 如果用户同意则开始启动录屏流程，在启动录屏成功后，通过该状态处理回调方法上报{@link OH_AVScreenCaptureStateCode}.OH_SCREEN_CAPTURE_STATE_STARTED状态，告知应用启动录屏成功，并在屏幕显示录屏通知。如果启动录屏失败，则通过该状态处理回调方法上报失败状态信息（如，若麦克风不可用则上报{@link OH_AVScreenCaptureStateCode}.
 * OH_SCREEN_CAPTURE_STATE_MIC_UNAVAILABLE状态），或通过错误处理回调方法{@link OH_AVScreenCapture_OnError}上报错误信息。
 * 2. 如果用户拒绝，则终止启动录屏，通过该状态处理回调方法上报{@link OH_AVScreenCaptureStateCode}.OH_SCREEN_CAPTURE_STATE_CANCELED状态，告知应用用户拒绝启动录屏，
 * 启动录屏失败。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param callback 指向状态处理回调方法实例的指针。
 * @param userData 指向应用提供的自定义数据的指针，在状态处理回调方法被调用时作为入参回传。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针或输入参数callback为空指针。
 * AV_SCREEN_CAPTURE_ERR_NO_MEMORY：内存不足，内存分配失败。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，设置StateCallback失败。
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetStateCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnStateChange callback, void *userData);

/**
 * @brief 设置数据处理回调方法，在开始录制前调用。
 * 调用该方法设置数据处理回调方法，当OH_AVScreenCapture操作期间有音频或视频数据缓存区可用时，将调用该数据处理回调方法。
 * 应用需要在该数据处理回调方法中根据数据类型完成处理麦克风音频、内录音频、视频数据，当该数据处理回调方法返回后数据缓存区将不再有效。
 * 调用该方法成功后：
 * 1. 当OH_AVScreenCapture操作期间有音视频缓存区可用时，将不再调用通过{@link OH_AVScreenCapture_SetCallback}设置的数据回调方法{@link OH_AVScreenCaptureOnAudioBufferAvailable}
 * 和{@link OH_AVScreenCaptureOnVideoBufferAvailable}。
 * 2. 不允许应用调用如下4个方法{@link OH_AVScreenCapture_AcquireAudioBuffer}、{@link OH_AVScreenCapture_ReleaseAudioBuffer}、{@link OH_AVScreenCapture_AcquireVideoBuffer}
 * 和{@link OH_AVScreenCapture_ReleaseVideoBuffer}，直接返回失败。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param callback 指向数据处理回调方法实例的指针。
 * @param userData 指向应用提供的自定义数据的指针，在数据处理回调方法被调用时作为入参回传。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针或输入参数callback为空指针。
 * AV_SCREEN_CAPTURE_ERR_NO_MEMORY：内存不足，内存分配失败。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，设置DataCallback失败。
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetDataCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnBufferAvailable callback, void *userData);

/**
 * @brief 设置错误处理回调方法，在开始录制前调用。
 * 调用该方法设置错误处理回调方法，当OH_AVScreenCapture实例发生错误时，该错误处理回调方法将会被调用。
 * 调用该设置方法成功后，当OH_AVScreenCapture实例发生错误时，将不再调用通过{@link OH_AVScreenCapture_SetCallback}设置的错误处理回调方法{@link OH_AVScreenCaptureOnError}
 * 。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param callback 指向错误处理回调方法实例的指针。
 * @param userData 指向应用提供的自定义数据的指针，在错误处理回调方法被调用时作为入参回传。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针或输入参数callback为空指针。
 * AV_SCREEN_CAPTURE_ERR_NO_MEMORY：内存不足，内存分配失败。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，设置ErrorCallback失败。
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetErrorCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnError callback, void *userData);

/**
 * @brief 设置录屏内容变更回调事件，需在录屏启动前被调用。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param callback 指向录屏内容变更回调方法实例的指针。
 * @param userData 指向应用提供的自定义数据的指针，在错误处理回调方法被调用时作为入参回传。
 * @return AV_SCREEN_CAPTURE_ERR_OK：操作成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：参数无效，输入参数capture或callback为空指针。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，设置录屏内容回调失败。
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetCaptureContentChangedCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnCaptureContentChanged callback, void *userData);

/**
 * @brief 使用Surface模式录屏。
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance.
 * @param window Pointer to an OHNativeWindow instance.
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针或输入参数window为空指针或window指向的windowSurface为空指针。
 * AV_SCREEN_CAPTURE_ERR_UNSUPPORT（API version 20新增）：设备不支持该操作。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，设置隐私权限启用失败或启动ScreenCaptureWithSurface失败。
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StartScreenCaptureWithSurface(struct OH_AVScreenCapture *capture,
    OHNativeWindow *window);

/**
 * @brief 设置录屏屏幕数据旋转。
 * 调用该方法可以设置录屏屏幕数据是否旋转，当canvasRotation为true时，打开录屏屏幕数据旋转功能，录制的屏幕数据保持正向。
 * 默认为false。
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param canvasRotation whether to rotate the canvas
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_UNSUPPORT（API version 20新增）：设备不支持该操作。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，设置录屏屏幕数据旋转失败。
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetCanvasRotation(struct OH_AVScreenCapture *capture,
    bool canvasRotation);

/**
 * @brief 创建ContentFilter。
 * 
 * @return 执行成功返回OH_AVScreenCapture_ContentFilter实例，否则返回空指针。
 * @since 12
 */
struct OH_AVScreenCapture_ContentFilter *OH_AVScreenCapture_CreateContentFilter(void);

/**
 * @brief 释放ContentFilter。
 * 
 * @param filter 指向OH_AVScreenCapture_ContentFilter实例的指针。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数filter为空指针。
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ReleaseContentFilter(struct OH_AVScreenCapture_ContentFilter *filter);

/**
 * @brief 向ContentFilter实例添加可过滤的声音类型。
 * 
 * @param filter 指向OH_AVScreenCapture_ContentFilter实例的指针。
 * @param content OH_AVScreenCaptureFilterableAudioContent实例。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数filter为空指针或输入参数content无效。
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ContentFilter_AddAudioContent(
    struct OH_AVScreenCapture_ContentFilter *filter, OH_AVScreenCaptureFilterableAudioContent content);

/**
 * @brief 设置OH_AVScreenCapture实例的内容过滤器ContentFilter。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param filter 指向OH_AVScreenCapture_ContentFilter实例的指针。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针或输入参数filter为空指针。
 * AV_SCREEN_CAPTURE_ERR_UNSUPPORT：操作不支持。对于流，启动时应该调用AudioCapturer接口。
 * 对于capture文件，启动时调用Recorder接口。
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ExcludeContent(struct OH_AVScreenCapture *capture,
    struct OH_AVScreenCapture_ContentFilter *filter);

/**
 * @brief 向ContentFilter实例添加可被过滤的窗口ID列表。
 * 
 * @param filter 指向OH_AVScreenCapture_ContentFilter实例的指针。
 * @param windowIDs 指向窗口ID的指针。
 * @param windowCount 窗口ID列表的长度。
 * @return 执行成功返回AV_SCREEN_CAPTURE_ERR_OK，否则返回具体错误码。
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ContentFilter_AddWindowContent(
    struct OH_AVScreenCapture_ContentFilter *filter, int32_t *windowIDs, int32_t windowCount);

/**
 * @brief 调整屏幕的分辨率。
 * 调用该方法可以设置录屏屏幕数据的分辨率，width为屏幕的宽度，height为屏幕的高度。
 * 该接口目前仅支持录屏取码流的场景，不支持录屏存文件的场景。并且调用该接口的调用者以及视频数据的消费者需要确保自身能够支持收到的视频数据分辨率发生变化。
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param width Video frame width of avscreeencapture, in px.
 * @param height Video frame height of avscreeencapture, in px.
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_UNSUPPORT（API version 20新增）：设备不支持该操作。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作。
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ResizeCanvas(struct OH_AVScreenCapture *capture,
    int32_t width, int32_t height);

/**
 * @brief 录屏时豁免隐私窗口。
 * 调用该方法可以豁免隐私窗口，windowIDs为需要豁免的隐私窗口ID指针，windowCount 为隐私窗口ID列表的长度，目前豁免需要传入所有隐私子窗口和主窗口ID。
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param windowIDs Pointer of windowID list
 * @param windowCount length of windowID list
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_UNSUPPORT（API version 20新增）：设备不支持该操作。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作。
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SkipPrivacyMode(struct OH_AVScreenCapture *capture,
    int32_t *windowIDs, int32_t windowCount);

/**
 * @brief 设置录屏时的最大帧率。
 * 该接口应在录屏启动之后被调用。
 * 调用该方法可以设置录屏时的最大帧率，frameRate为想要设置的最大帧率。
 * 该接口设置最大帧率时，实际设置的帧率受限设备的能力，由底层的系统能力决定。
 * 调用该接口设置录屏最大帧率时，实际帧率将受限于设备能力。目前接口入参的最大值不设限制，但当前支持的最高帧率为60FPS，当入参设置超过60FPS，将以60FPS处理。不超过上限时，则按照实际入参值处理。
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param frameRate max frame rate of video, in fps.
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针或者输入参数frameRate不支持。
 * AV_SCREEN_CAPTURE_ERR_UNSUPPORT（API version 20新增）：设备不支持该操作。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作。
 * @since 14
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetMaxVideoFrameRate(struct OH_AVScreenCapture *capture,
    int32_t frameRate);

/**
 * @brief 设置光标显示开关。
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param showCursor The switch of the cursor
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_UNSUPPORT（API version 20新增）：设备不支持该操作。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，设置光标失败。
 * @since 15
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ShowCursor(struct OH_AVScreenCapture *capture,
    bool showCursor);

/**
 * @brief 设置或更新捕获区域。
 * 接口在开始录屏前后都可以设置，设置的坐标和宽高不能为负数，捕获区域不能跨屏幕，区域位置设置失败后仍按照上一次的区域进行捕获。
 * 
 * @param capture capture Pointer to an OH_AVScreenCapture instance
 * @param displayId Indicates the screen index for setting area recording
 * @param area Pointer to an object describing the location and size of the region
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针、输入displayId不存在或输入的捕获区域异常。
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetCaptureArea(struct OH_AVScreenCapture *capture, uint64_t displayId, OH_Rect* area);

/**
 * @brief 设置屏幕捕获区域高亮模式。
 * 
 * @param capture Pointer to OH_AVScreenCapture which want to set highlight style.
 * @param config the highlight parameters are to be set for this screen capture.
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针或者config参数值无效。
 * @since 22
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetCaptureAreaHighlight(struct OH_AVScreenCapture *capture,
    OH_AVScreenCaptureHighlightConfig config);

/**
 * @brief 注册手工确认界面用户选择结果的回调，需在录屏启动前被调用。
 * 
 * @param capture Pointer to OH_AVScreenCapture which want to handle user selection info
 * @param callback user selection callback function, see {@link OH_AVScreenCapture_OnUserSelected}
 * @param userData The control block pointer passed by the application is carried to the application when it is
 * returned
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetSelectionCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnUserSelected callback, void *userData);

/**
 * @brief 获取用户在确认界面选择的屏幕捕获对象类型。在{@link OH_AVScreenCapture_OnUserSelected}回调中使用，selection指针在回调结束后销毁。
 * 
 * @param selection Pointer to an OH_AVScreenCapture_UserSelectionInfo instance
 * @param type The capture object type selected by the user,
 * 0: represents the screen, 1: represents the window, 2: represents the app.
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数selection为空指针。
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_GetCaptureTypeSelected(OH_AVScreenCapture_UserSelectionInfo *selection, int32_t* type);

/**
 * @brief 获取确认页面，用户选择录制的屏幕ID。在{@link OH_AVScreenCapture_OnUserSelected}回调中使用，selection指针在回调结束后销毁。
 * 
 * @param selection Pointer to an OH_AVScreenCapture_UserSelectionInfo instance
 * @param displayId Returns the screen ID value selected by the user
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数selection为空指针。
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_GetDisplayIdSelected(OH_AVScreenCapture_UserSelectionInfo *selection, uint64_t* displayId);

/**
 * @brief 创建录屏策略对象。
 * 
 * @return 执行成功返回OH_AVScreenCapture_CaptureStrategy实例，否则返回空指针。
 * @since 20
 */
OH_AVScreenCapture_CaptureStrategy* OH_AVScreenCapture_CreateCaptureStrategy(void);

/**
 * @brief 释放录屏策略对象。
 * 
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数strategy为空指针。
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ReleaseCaptureStrategy(OH_AVScreenCapture_CaptureStrategy* strategy);

/**
 * @brief 给指定的OH_AVScreenCapture实例设置捕获策略。
 * 该接口应在录屏启动之前被调用。
 * 
 * @param capture Pointer to an OH_AVScreenCapture which need to be setted.
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy which want to
 * set.
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture或strategy为空指针。
 * AV_SCREEN_CAPTURE_ERR_INVALID_STATE：在录屏启动之后调用该接口。
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetCaptureStrategy( 
	struct OH_AVScreenCapture *capture, OH_AVScreenCapture_CaptureStrategy *strategy);

/**
 * @brief 向CaptureStrategy实例设置蜂窝通话时是否保持录屏。
 * value设置为true时并且录屏时接听蜂窝通话的过程中，出于隐私要求，双方通话的声音（本地麦克风和对方说话声音）不会被录制，其他系统音录制正常。电话挂断之后，录屏框架恢复麦克风录制。注意，如果挂断电话时录屏应用在后台运行，
 * 麦克风录制会启动失败，原因是音频模块不允许后台应用启动麦克风录制。
 * 
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @param value The default value is false, which means that screen recording is not allowed during cellular
 * calls.
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数strategy为空指针。
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForKeepCaptureDuringCall( 
    OH_AVScreenCapture_CaptureStrategy *strategy, bool value);

/**
 * @brief Set the fill mode for screen capture when a privacy window exists
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @param value 
 *         If set to 0, it means that when there is a privacy window interface, the output screen image is completely black. 
 *         If set to 1, it means that when there is a privacy window interface, only the privacy window area of 鈥嬧�媡he output screen becomes black, 
 *         and other values returns an error.
 * @return Function result code.
 *         {@link AV_SCREEN_CAPTURE_ERR_OK} if the execution is successful.
 *         {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL} strategy is nullptr or  value is invalid.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForPrivacyMaskMode( 
    OH_AVScreenCapture_CaptureStrategy *strategy, int32_t value);

/**
 * @brief 向CaptureStrategy实例设置是否使能B帧编码，用于减小录制文件的大小。
 * B帧视频编码相关的约束和限制可以参考文档{@link B帧视频编码约束和限制}。如果当前不符合B帧视频编码的约束和限制，则正常录制不含B帧的视频，不会返回错误。
 * 
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @param value The default value is false, which means B frames  encoding are disabled.
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数strategy为空指针。
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForBFramesEncoding( 
    OH_AVScreenCapture_CaptureStrategy *strategy, bool value );

/**
 * @brief 设置屏幕录屏自动跟随旋转配置。设为true，表示跟随屏幕旋转，并在横竖屏旋转后，自动调换虚拟屏尺寸，确保输出画面及时跟随旋转。
 * 设置是否自动跟随旋转配置后，在旋转通知后，无需再手动调用{@link OH_AVScreenCapture_ResizeCanvas}接口。
 * 
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @param value The default value is False, which means that the width and height of the VirtualDisplay
 * remain the initial settings. If set to True, it means that the width and height of the VirtualDisplay rotates
 * with the rotation of the screen..
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数strategy为空指针。
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForCanvasFollowRotation( 
    OH_AVScreenCapture_CaptureStrategy *strategy, bool value);

/**
 * @brief 设置是否弹出屏幕捕获Picker。
 * 
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @param value
 * If set to false, it means that the APP don't need to pop up the Picker after screen capture starts;
 * If set to True, the Picker will pop up uniformly after screen capture starts;
 * If not set, it means using the system recommended behavior.
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数strategy为空指针或输入value为无效值。
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForPickerPopUp( 
    OH_AVScreenCapture_CaptureStrategy *strategy, bool value);

/**
 * @brief 设置捕获图像在目标区域的填充模式。
 * 
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @param mode Value of the captured image fill mode
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数strategy为空指针。
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForFillMode( 
    OH_AVScreenCapture_CaptureStrategy *strategy, OH_AVScreenCapture_FillMode mode);


/**
 * @brief 设置获取录屏屏幕Id的回调。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param callback 指向录屏屏幕Id回调方法实例的指针。
 * @param userData 指向应用提供的自定义数据的指针，在状态处理回调方法被调用时作为入参回传。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针或输入参数callback为空指针。
 * AV_SCREEN_CAPTURE_ERR_NO_MEMORY：内存不足，内存分配失败。
 * AV_SCREEN_CAPTURE_ERR_INVALID_STATE：回调必须在start方法前调用。
 * @since 15
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetDisplayCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnDisplaySelected callback, void *userData);


/**
 * @brief 在Picker界面中隐藏指定的窗口。在picker界面显示前调用本接口，可对指定窗口进行过滤和隐藏。
 * 
 * @details Filters specified windows before displaying the system-level picker.
 * Excluded windows will not appear in the selection list.
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param excludedWindowIDs 需要隐藏的窗口ID数组（已存在的窗口）。
 * @param windowCount 需要隐藏的窗口ID数组长度。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针或者窗口ID参数值无效。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作。
 * @since 22
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ExcludePickerWindows(struct OH_AVScreenCapture *capture,
    const int32_t *excludedWindowIDs, uint32_t windowCount);

/**
 * @brief 设置Picker显示模式。定义picker中显示的内容类型，模式更改会在下一次调用{@link OH_AVScreenCapture_PresentPicker} 函数时生效。
 * 
 * @details Defines the content type displayed in the system-level picker.
 * Mode changes take effect upon the next call to function PresentPicker.
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param pickerMode Picker显示模式（请参阅OH_CapturePickerMode枚举）。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针或者pickerMode参数值无效。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作。
 * @since 22
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetPickerMode(struct OH_AVScreenCapture *capture,
    OH_CapturePickerMode pickerMode);

/**
 * @brief 录屏开始后，调用该接口再次弹出picker，可动态更新录制源（窗口、屏幕）。更新录制源过程中，原录制流程不中断。
 * 通过picker动态更新录制源后，可以按照新的录制源进行录制。
 * 
 * @details Activates system visual picker with two usage scenarios:
 * 1. Initial capture configuration: Select source before starting capture
 * 2. Dynamic source switching: Change capture target during active capture
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作。
 * @since 22
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_PresentPicker(struct OH_AVScreenCapture *capture);

/**
 * @brief 获取多屏幕录制能力信息，判断用户选择的多个屏幕是否支持联合录制。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param displayIds 返回用户选择的DisplayID数组。
 * @param count 返回用户选择的DisplayID的数量。
 * @param capability 指向OH_MultiDisplayCapability实例的指针。
 * @return AV_SCREEN_CAPTURE_ERR_OK：操作执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入的录屏实例参数capture为空指针。
 * AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT：不允许操作，获取数据失败。
 * @since 24
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_GetMultiDisplayCaptureCapability(
    struct OH_AVScreenCapture *capture, 
    uint64_t *displayIds, 
    size_t count,  
    OH_MultiDisplayCapability *capability);

/**
 * @brief 获取picker页面上用户选择录制的DisplayID列表。在{@link OH_AVScreenCapture_OnUserSelected}回调中使用，selection指针在回调结束后销毁。
 * 
 * @param selection 指向OH_AVScreenCapture_UserSelectionInfo实例的指针。
 * @param displayIds 返回用户选择的DisplayID数组。参数displayIds的内存由OH_AVScreenCapture_UserSelectionInfo管理，无需手动释放。
 * @param count 返回用户选择的DisplayID的数量。
 * @return AV_SCREEN_CAPTURE_ERR_OK：操作执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入包含用户选择信息的参数selection为空指针。
 * @since 24
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_GetMultiDisplayIdsSelected(
    OH_AVScreenCapture_UserSelectionInfo *selection, 
    uint64_t **displayIds, 
    size_t *count);

/**
 * @brief 设置隐私保护回调函数，以便应用程序响应屏幕捕获产生的隐私保护事件。该接口必须在调用开始录屏之前调用。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param callback 隐私保护回调函数。
 * @param userData 指向应用提供的自定义数据的指针，在状态处理回调方法被调用时作为入参回传。
 * @return AV_SCREEN_CAPTURE_ERR_OK：执行成功。
 * AV_SCREEN_CAPTURE_ERR_INVALID_VAL：输入录屏实例为空指针或输入回调为空指针。
 * @since 24
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetPrivacyProtectCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnPrivacyProtect callback, void *userData);

/**
 * @brief Allow to pause screen capture
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance.
 * @param value The default value is false, which means that screen recording is not allowed to pause
 * @return Function result code.
 *         {@link AV_SCREEN_CAPTURE_ERR_OK} if the execution is successful.
 *         {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL} strategy value is nullptr.
 * @since 26.0.0
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForPause(OH_AVScreenCapture_CaptureStrategy *strategy,
    bool value);

/**
 * @brief Pause screen capture
 * @param capture Initialized screen capture instance.
 * @return Function result code.
 *         {@link AV_SCREEN_CAPTURE_ERR_OK} if the execution is successful.
 *         {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL} capture value is nullptr.
 *         {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT} operation not permitted.
 * @since 26.0.0
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_PauseScreenCapture(struct OH_AVScreenCapture *capture);

/**
 * @brief Resume screen capture
 * @param capture Initialized screen capture instance.
 * @return Function result code.
 *         {@link AV_SCREEN_CAPTURE_ERR_OK} if the execution is successful.
 *         {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL} capture value is nullptr.
 *         {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT} operation not permitted.
 * @since 26.0.0
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ResumeScreenCapture(struct OH_AVScreenCapture *capture);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSCREEN_CAPTURE_H
/** @} */

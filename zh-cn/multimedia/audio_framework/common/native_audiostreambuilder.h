/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
 * @addtogroup OHAudio
 * @{
 *
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 10
 */

/**
 * @file native_audiostreambuilder.h
 *
 * @brief Declare audio stream builder related interfaces.
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 10
 */

#ifndef NATIVE_AUDIOSTREAM_BUILDER_H
#define NATIVE_AUDIOSTREAM_BUILDER_H

#include <stdbool.h>
#include "native_audiostream_base.h"
#include "native_audiorenderer.h"
#include "native_audiocapturer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建一个输入或者输出类型的音频流构造器。
 * <br>当构造器不再使用时，需要调用{@link OH_AudioStreamBuilder_Destroy}销毁。
 *
 * @param builder 用于接收创建的构造器实例。
 * @param type 构造器的流类型。AUDIOSTREAM_TYPE_RENDERER或AUDIOSTREAM_TYPE_CAPTURER。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioStreamBuilder_Create(OH_AudioStreamBuilder** builder, OH_AudioStream_Type type);

/**
 * @brief 销毁一个音频流构造器。
 * <br>当构造器不再使用时，需要调用该函数销毁。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of builder is nullptr.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioStreamBuilder_Destroy(OH_AudioStreamBuilder* builder);

/**
 * @brief 设置音频流的采样率属性。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param rate 音频流采样率。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of builder is nullptr;
 *                                                 2.The param of rate invalid.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetSamplingRate(OH_AudioStreamBuilder* builder, int32_t rate);

/**
 * @brief 设置音频流的通道数属性。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param channelCount 音频流通道数。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of builder is nullptr;
 *                                                 2.The param of channelCount invalid.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetChannelCount(OH_AudioStreamBuilder* builder, int32_t channelCount);

/**
 * @brief 设置音频流的采样格式属性。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param format 音频流采样格式。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of builder is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetSampleFormat(OH_AudioStreamBuilder* builder,
    OH_AudioStream_SampleFormat format);

/**
 * @brief 设置音频流的编码类型属性。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param encodingType 音频流编码类型。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of builder is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetEncodingType(OH_AudioStreamBuilder* builder,
    OH_AudioStream_EncodingType encodingType);

/**
 * @brief 设置音频流的时延模式。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param latencyMode 音频流时延模式。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of builder is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetLatencyMode(OH_AudioStreamBuilder* builder,
    OH_AudioStream_LatencyMode latencyMode);

/**
 * @brief 设置音频流的声道布局。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param channelLayout 音频流声道布局。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of builder is nullptr.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetChannelLayout(OH_AudioStreamBuilder* builder,
    OH_AudioChannelLayout channelLayout);

/**
 * @brief 设置输出音频流的工作场景。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param usage 输出音频流的使用场景。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of builder is nullptr;
 *                                                 2.The param of usage invalid.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetRendererInfo(OH_AudioStreamBuilder* builder,
    OH_AudioStream_Usage usage);

/**
 * @brief 设置输入音频流的工作场景。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param sourceType 输入音频流的使用场景。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of builder is nullptr;
 *                                                 2.The param of sourceType invalid.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetCapturerInfo(OH_AudioStreamBuilder* builder,
    OH_AudioStream_SourceType sourceType);

/**
 * @brief 设置输出音频流的回调。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callbacks 将被用来处理输出音频流相关事件的回调函数。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：
 *     <br>1. 参数builder为nullptr；
 *     <br>2. StreamType无效。
 * @since 10
 * @deprecated since 20
 * @useinstead Set the callback functions separately using OH_AudioStreamBuilder_SetRendererWriteDataCallback,
 *     OH_AudioStreamBuilder_SetRendererInterruptCallback, OH_AudioStreamBuilder_SetRendererOutputDeviceChangeCallback
 *     and OH_AudioStreamBuilder_SetRendererErrorCallback.
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetRendererCallback(OH_AudioStreamBuilder* builder,
    OH_AudioRenderer_Callbacks callbacks, void* userData);

/**
 * @brief 设置输出音频流设备变更的回调。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callback 将被用来处理输出流设备变更相关事件的回调函数。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：
 *     <br>1. 参数builder为nullptr；
 *     <br>2. StreamType无效。
 * @since 11
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetRendererOutputDeviceChangeCallback(OH_AudioStreamBuilder* builder,
    OH_AudioRenderer_OutputDeviceChangeCallback callback, void* userData);

/**
 * @brief Set the privacy of audio render.
 *
 * @param builder Builder provided by OH_AudioStreamBuilder_Create()
 * @param privacy Privacy type.
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of builder is nullptr;
 *                                                 2.StreamType invalid.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetRendererPrivacy(OH_AudioStreamBuilder* builder,
    OH_AudioStream_PrivacyType privacy);

/**
 * @brief Set the callbacks for the capturer client
 *
 * @param builder  * @param callbacks
 * @param callbacks Callbacks to the functions that will process capturer stream.
 * @param userData  * @return
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of builder is nullptr;
 *                                                 2.StreamType invalid.</li>
 *         </ul>
 * @since 10
 * @deprecated since 20
 * @useinstead Set the callback functions separately using OH_AudioStreamBuilder_SetCapturerReadDataCallback,
 *     OH_AudioStreamBuilder_SetCapturerDeviceChangeCallback, OH_AudioStreamBuilder_SetCapturerInterruptCallback
 *     and OH_AudioStreamBuilder_SetCapturerErrorCallback.
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetCapturerCallback(OH_AudioStreamBuilder* builder,
    OH_AudioCapturer_Callbacks callbacks, void* userData);

/**
 * @brief Create the audio renderer client.
 *
 * The AudioRenderer instance is used to play streaming audio data.
 * When using AudioRenderer apis, there are many instructions for application
 * to achieve better performance and lower power consumption:
 * In music or audiobook background playback situation, you can have low power
 * consumption by following this best practices document **Low-Power Rules in Music Playback Scenarios**.
 * And for navigation situation, you can follow **Low-Power Rules in Navigation and Positioning Scenarios**.
 *
 * Application developer should also be careful when app goes to background, please check if your audio playback
 * is still needed, see **Audio Resources** in best practices document.
 * And avoiding to send silence audio data continuously to waste system resources, otherwise system will take
 * control measures when this behavior is detected, see **Audio Playback** in best practices document.
 *
 * If you want to use AudioRenderer api to implement a music playback application, there are also many interactive
 * scenes to consider, see **Developing an Audio Application** in best practices document.
 *
 * @param builder Reference provided by OH_AudioStreamBuilder_Create()
 * @param audioRenderer Pointer to a variable to receive the stream client.
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of builder is nullptr;
 *                                                 2.StreamType invalid;
 *                                                 3.Create OHAudioRenderer failed.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioStreamBuilder_GenerateRenderer(OH_AudioStreamBuilder* builder,
    OH_AudioRenderer** audioRenderer);

/**
 * @brief 创建输入音频流实例。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param audioCapturer 指向输入音频流实例的指针，将被用来接收函数创建的结果。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of builder is nullptr;
 *                                                 2.StreamType invalid;
 *                                                 3.Create OHAudioCapturer failed.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioStreamBuilder_GenerateCapturer(OH_AudioStreamBuilder* builder,
    OH_AudioCapturer** audioCapturer);

/**
 * @brief 用于播放时设置每次回调的帧长，帧长至少为音频硬件一次处理的数据大小，并且小于内部缓冲容量的一半。
 * <br>低时延播放：frameSize可设置为5ms、10ms、15ms、20ms音频数据对应的帧长。
 * <br>普通通路播放：frameSize可设置为20ms-100ms音频数据对应的帧长。例如，当采样率48000Hz时，20ms音频数据对应的帧长计算方式为：frameSize = 48000 * 0.02，即960个采样点数。
 * 当frameSize为960时，对应的数据回调的长度为960 * 声道数 * 采样位宽（字节数）。比如双声道16bit时，length为960 * 2 * 2 = 3840。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param frameSize  要设置音频数据的帧长。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of builder is nullptr.</li>
 *         </ul>
 * @since 11
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetFrameSizeInCallback(OH_AudioStreamBuilder* builder,
    int32_t frameSize);

/**
 * @brief 设置同时写入音频数据和元数据的回调。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callback 将被用来同时写入音频数据和元数据的回调函数。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of builder is nullptr;
 *                                                 2.StreamType invalid.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetWriteDataWithMetadataCallback(OH_AudioStreamBuilder* builder,
    OH_AudioRenderer_WriteDataWithMetadataCallback callback, void* userData);

/**
 * @brief 设置流客户端的中断模式。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param mode 音频中断模式。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of builder is nullptr;
 *                                                 2.The param of mode invalid;
 *                                                 3.StreamType invalid.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetRendererInterruptMode(OH_AudioStreamBuilder* builder,
    OH_AudioInterrupt_Mode mode);
/**
 * @brief 设置写入音频数据的回调函数。
 * <br>此函数与{@link OH_AudioStreamBuilder_SetRendererCallback}类似。如果同时使用{@link OH_AudioStreamBuilder_SetRendererCallback}
 * 或者本函数，只有最后一次设置的回调才生效，其它回调不会生效。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callback 将被用来写入音频数据的回调函数。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：
 *     <br>1. 参数builder为nullptr；
 *     <br>2. StreamType无效。
 * @since 12
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetRendererWriteDataCallback(OH_AudioStreamBuilder* builder,
    OH_AudioRenderer_OnWriteDataCallback callback, void* userData);
/**
 * @brief 设置写入音频数据的回调函数。
 * <br>此函数与{@link OH_AudioStreamBuilder_SetRendererWriteDataCallback}类似。
 * <br>如果同时设置该回调和OH_AudioStreamBuilder_SetRendererWriteDataCallback，只有最后一次设置的回调生效。
 * <br>与OH_AudioStreamBuilder_SetRendererWriteDataCallback不同，
 * OH_AudioStreamBuilder_SetRendererWriteDataCallbackAdvanced设置的回调函数，允许应用传入可变长度的音频数据，并通知系统写入的数据长度。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callback 将被用来写入音频数据的回调函数。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数非法，比如builder为空指针，等等。
 * @since 20
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetRendererWriteDataCallbackAdvanced(OH_AudioStreamBuilder* builder,
    OH_AudioRenderer_OnWriteDataCallbackAdvanced callback, void* userData);
/**
 * @brief 设置音频流音量模式。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param volumeMode 要设置的音频流音量模式。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：
 *     <br>1. 参数builder为nullptr；
 *     <br>2. 参数volumeMode无效。
 * @since 19
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetVolumeMode(OH_AudioStreamBuilder* builder,
    OH_AudioStream_VolumeMode volumeMode);
/**
 * @brief 设置输出音频流中断事件的回调函数。
 * <br>此函数与{@link OH_AudioStreamBuilder_SetRendererCallback}类似。如果同时使用{@link OH_AudioStreamBuilder_SetRendererCallback}
 * 或者本函数，只有最后一次设置的回调才生效，其它回调不会生效。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callback 用于接收中断事件的回调函数。
 * @param userData 指向应用程序数据结构的指针，该结构将传递给回调函数。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数无效，比如，builder为空指针。
 * @since 20
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetRendererInterruptCallback(OH_AudioStreamBuilder* builder,
    OH_AudioRenderer_OnInterruptCallback callback, void* userData);
/**
 * @brief 设置输出音频流错误事件的回调函数。
 * <br>此函数与{@link OH_AudioStreamBuilder_SetRendererCallback}类似。如果同时使用{@link OH_AudioStreamBuilder_SetRendererCallback}
 * 或者本函数，那么只有最后一次设置的回调才生效，其它回调不会生效。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callback 用于接收错误事件的回调函数。
 * @param userData 指向应用程序数据结构的指针，该结构将传递给回调函数。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数无效，比如，builder为空指针。
 * @since 20
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetRendererErrorCallback(OH_AudioStreamBuilder* builder,
    OH_AudioRenderer_OnErrorCallback callback, void* userData);
/**
 * @brief 设置输入音频流读取数据的回调函数。
 * <br>此函数与{@link OH_AudioStreamBuilder_SetCapturerCallback}类似。如果同时使用{@link OH_AudioStreamBuilder_SetCapturerCallback}
 * 或者本函数，那么只有最后一次设置的回调才生效，其它回调不会生效。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callback 用于接收读取数据事件的回调函数。
 * @param userData 指向应用程序数据结构的指针，该结构将传递给回调函数。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数无效，比如，builder为空指针。
 * @since 20
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetCapturerReadDataCallback(OH_AudioStreamBuilder* builder,
    OH_AudioCapturer_OnReadDataCallback callback, void* userData);
/**
 * @brief 设置输入音频流设备变更的回调函数。
 * <br>此函数与{@link OH_AudioStreamBuilder_SetCapturerCallback}类似。如果同时使用{@link OH_AudioStreamBuilder_SetCapturerCallback}
 * 或者本函数，那么只有最后一次设置的回调才生效，其它回调不会生效。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callback 用于接收设备变更事件的回调函数。
 * @param userData 指向应用程序数据结构的指针，该结构将传递给回调函数。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数无效，比如，builder为空指针。
 * @since 20
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetCapturerDeviceChangeCallback(OH_AudioStreamBuilder* builder,
    OH_AudioCapturer_OnDeviceChangeCallback callback, void* userData);
/**
 * @brief 设置输入音频流中断事件的回调函数。
 * <br>此函数与{@link OH_AudioStreamBuilder_SetCapturerCallback}类似。如果同时使用{@link OH_AudioStreamBuilder_SetCapturerCallback}
 * 或者本函数，那么只有最后一次设置的回调才生效，其它回调不会生效。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callback 用于接收中断事件的回调函数。
 * @param userData 指向应用程序数据结构的指针，该结构将传递给回调函数。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数无效，比如，builder为空指针。
 * @since 20
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetCapturerInterruptCallback(OH_AudioStreamBuilder* builder,
    OH_AudioCapturer_OnInterruptCallback callback, void* userData);
/**
 * @brief 设置输入音频流错误事件的回调函数。
 * <br>此函数与{@link OH_AudioStreamBuilder_SetCapturerCallback}类似。如果同时使用{@link OH_AudioStreamBuilder_SetCapturerCallback}
 * 或者本函数，那么只有最后一次设置的回调才生效，其它回调不会生效。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callback 用于接收错误事件的回调函数。
 * @param userData 指向应用程序数据结构的指针，该结构将传递给回调函数。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数无效，比如，builder为空指针。
 * @since 20
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetCapturerErrorCallback(OH_AudioStreamBuilder* builder,
    OH_AudioCapturer_OnErrorCallback callback, void* userData);
/**
 * @brief 设置输入音频流是否启用静音打断模式。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param muteWhenInterrupted 设置当前录制音频流是否启用静音打断模式。true表示启用；false表示不启用，保持为默认打断模式。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数无效，比如，builder为空指针。
 * @since 20
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetCapturerWillMuteWhenInterrupted(OH_AudioStreamBuilder* builder,
    bool muteWhenInterrupted);
/**
 * @brief 设置音频播放过程中低时延状态改变事件的回调函数。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callback 用于接收播放低时延状态改变事件的回调函数。
 * @param userData 指向应用程序数据结构的指针，该结构将传递给回调函数。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数无效，比如，builder为空指针。
 * @since 20
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetRendererFastStatusChangeCallback(OH_AudioStreamBuilder* builder,
    OH_AudioRenderer_OnFastStatusChange callback, void* userData);
/**
 * @brief 设置音频录制过程中低时延状态改变事件的回调函数。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callback 用于接收录制低时延状态改变事件的回调函数。
 * @param userData 指向应用程序数据结构的指针，该结构将传递给回调函数。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数无效，比如，builder为空指针。
 * @since 20
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetCapturerFastStatusChangeCallback(OH_AudioStreamBuilder* builder,
    OH_AudioCapturer_OnFastStatusChange callback, void* userData);
/**
 * @brief 设置音频录制流是否采集带音频混响效果的音频数据。当音频环回设置为硬件模式并启用混响效果时，低时延模式的采集器可以获取到具备混响效果的录音数据。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param enabled 设置应用程序是否采集带混响效果的音频数据。true表示采集，false表示不采集。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数无效。如builder为空指针。
 * @since 26.0.0
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetCapturerLoopbackEffectEnabled(
    OH_AudioStreamBuilder* builder, bool enabled);
/**
 * 在使用内录（录制设备内部应用的声音）时设置可以录制的音频模式，该模式将决定要录制的音频流类型。此功能仅适用于{@link AudioStream_Type_Capturer}类型。该API暂不对外支持。
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param mode 要设置的内录模式，可为{@link OH_AudioStream_PlaybackCaptureMode}中多个值的组合。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数无效。例如，builder为空指针或mode值无效。
 * @since 23
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetPlaybackCaptureMode(
    OH_AudioStreamBuilder* builder, uint32_t mode);

/**
 * @brief 设置蜂窝通话下行录音风险提示语播放结束的回调函数。仅在使用{@link OH_AudioStream_SourceType}.
 * AUDIOSTREAM_SOURCE_TYPE_VOICE_DOWNLINK录制时需要设置此函数。此回调必须成功设置，否则采集器无法创建。音频采集器创建后，风险提示语将自动添加到发送给通话对方的语音数据中。
 * 应用应等待回调结果后再启动采集器，否则{@link OH_AudioCapturer_Start}将返回错误。请确保音频采集器在蜂窝通话开始后创建，否则
 * {@link OH_AudioStreamBuilder_GenerateCapturer}将返回错误。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param callback 用于接收风险提示语播放结束的回调函数，不允许为空指针。
 * @param userData 用户数据指针，将在回调中回传给应用。若无需传递数据，可传入空指针。若数据不为空指针，调用方应在收到回调时确认数据是否仍然有效。
 * @return <ul>
 *     <br><li>AUDIOSTREAM_SUCCESS：函数执行成功。</li>
 *     <br><li>AUDIOSTREAM_ERROR_INVALID_PARAM：参数builder或callback为空指针。</li>
 *     <br></ul>
 * @since 26.0.0
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetSensitiveRecordPermitCallback(
    OH_AudioStreamBuilder* builder,
    OH_AudioCapturer_SensitiveRecordPermitCallback callback,
    void* userData);

/**
 * @brief 设置蜂窝通话下行录音的电话号码和安全令牌。仅在使用{@link OH_AudioStream_SourceType}.AUDIOSTREAM_SOURCE_TYPE_VOICE_DOWNLINK录制时需要设置此函数。
 * 电话号码和安全令牌将用于校验蜂窝通话下行采集器是否匹配对应的蜂窝通话，必须成功设置，否则采集器无法创建。
 *
 * @param builder 指向{@link OH_AudioStreamBuilder_Create}创建的构造器实例。
 * @param cellularRecordPhoneNum 目标蜂窝通话的电话号码，用于makeCallWithToken()中，不允许为空指针。
 * @param cellularRecordToken 目标蜂窝通话的安全令牌，可通过通话管理的makeCallWithToken()函数获取，不允许为空指针。
 * @return <ul>
 *     <br><li>AUDIOSTREAM_SUCCESS：函数执行成功。</li>
 *     <br><li>AUDIOSTREAM_ERROR_INVALID_PARAM：参数builder、cellularRecordPhoneNum或cellularRecordToken为空指针。</li>
 *     <br></ul>
 * @since 26.0.0
 */
OH_AudioStream_Result OH_AudioStreamBuilder_SetCellularRecordSecurityParams(
    OH_AudioStreamBuilder* builder, const char* cellularRecordPhoneNum, const char* cellularRecordToken);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIOSTREAM_BUILDER_H
/** @} */
/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup AudioCodec
 * @{
 *
 * @brief AudioCodec模块提供用于音频编解码功能的函数。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @since 11
 */


/**
 * @file native_avcodec_audiocodec.h
 *
 * @brief 音频编解码Native API的声明。
 * @sample [AVCodec](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/BasicFeature/Media/AVCodec)
 *
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avcodec_audiocodec.h>
 * @library libnative_media_acodec.so
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @since 11
 */

#ifndef NATIVE_AVCODEC_AUDIOCODEC_H
#define NATIVE_AVCODEC_AUDIOCODEC_H

#include <stdint.h>
#include <stdio.h>
#include "native_avcodec_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief MediaKeySession字段。
 * @since 12
 */
typedef struct MediaKeySession MediaKeySession;

/**
 * @brief 根据MIME类型创建音频编解码器实例，大多数场景下建议使用此方式。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param mime MIME类型描述字符串，请参阅{@link AVCODEC_MIME_TYPE}。
 * @param isEncoder true表示需要创建编码器，false表示需要创建解码器。
 * @return 返回OH_AVCodec实例的指针。
 * @since 11
 */
OH_AVCodec *OH_AudioCodec_CreateByMime(const char *mime, bool isEncoder);

/**
 * @brief 通过音频编解码器名称创建音频编解码器实例，使用此接口的前提是知道编解码器的确切名称，编解码器的名称可以通过{@link OH_AVCapability_GetName}获取。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param name 音频编解码器名称。
 * @return 返回OH_AVCodec实例的指针。
 * @since 11
 */
OH_AVCodec *OH_AudioCodec_CreateByName(const char *name);

/**
 * @brief 清理编解码器内部资源，销毁编解码器实例。注意不能进行重复销毁，否则将会导致程序崩溃。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：OH_AVCodec实例为nullptr或无效。\n
 *         AV_ERR_INVALID_STATE：编解码器服务不可用。\n
 *         AV_ERR_NO_MEMORY：内部资源已经释放。\n
 *         AV_ERR_UNKNOWN：发生内部错误，建议检查日志。
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_Destroy(OH_AVCodec *codec);

/**
 * @brief 设置异步回调函数，使应用可以响应音频编解码器生成的事件。在调用Prepare之前，必须调用此接口。
 *
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @param callback 所有回调函数的集合。
 * @param userData 用户特定数据。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：输入参数为nullptr或无效。\n
 *         AV_ERR_INVALID_STATE：编解码器服务不可用。
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_RegisterCallback(OH_AVCodec *codec, OH_AVCodecCallback callback, void *userData);

/**
 * @brief 配置音频描述信息。音频编解码器通常会根据音频描述信息进行配置。在调用Prepare之前，必须调用此接口。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @param format 指向OH_AVFormat的指针，给出要编解码的音频轨道的描述。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：输入参数为nullptr或无效。\n
 *         AV_ERR_INVALID_STATE：编解码器服务不可用。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许操作，这可能是由于状态不正确或不支持的操作。\n
 *         AV_ERR_UNKNOWN：发生内部错误，建议检查日志。
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_Configure(OH_AVCodec *codec, const OH_AVFormat *format);

/**
 * @brief 准备编解码器的内部资源，在调用此接口之前必须调用Configure接口。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：OH_AVCodec实例为nullptr或无效。\n
 *         AV_ERR_INVALID_STATE：编解码器服务不可用。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许操作，这可能是由于状态不正确或不支持的操作。\n
 *         AV_ERR_UNKNOWN：发生内部错误，建议检查日志。
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_Prepare(OH_AVCodec *codec);

/**
 * @brief 调用此接口启动编解码器，在Prepare成功后执行。启动后，编解码器将开始上报OH_AVCodecOnNeedInputBuffer事件。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：OH_AVCodec实例为nullptr或无效。\n
 *         AV_ERR_INVALID_STATE：编解码器服务不可用。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许操作，这可能是由于状态不正确或不支持的操作。\n
 *         AV_ERR_UNKNOWN：发生内部错误，建议检查日志。
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_Start(OH_AVCodec *codec);

/**
 * @brief 停止编解码器。停止后，可以通过Start重新进入已启动状态（started），但需要注意的是，
 * 如果编解码器之前已输入数据，则需要重新输入编解码器数据。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：OH_AVCodec实例为nullptr或无效。\n
 *         AV_ERR_INVALID_STATE：编解码器服务不可用。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许操作，这可能是由于状态不正确或不支持的操作。\n
 *         AV_ERR_UNKNOWN：发生内部错误，建议检查日志。
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_Stop(OH_AVCodec *codec);

/**
 * @brief 清除编解码器中缓存的输入和输出数据。调用此接口后，以前通过异步回调上报的所有缓冲区
 * 索引都将失效，请确保不要访问这些索引对应的缓冲区。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：OH_AVCodec实例为nullptr或无效。\n
 *         AV_ERR_INVALID_STATE：编解码器服务不可用。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许操作，这可能是由于状态不正确或不支持的操作。\n
 *         AV_ERR_UNKNOWN：发生内部错误，建议检查日志。
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_Flush(OH_AVCodec *codec);

/**
 * @brief 重置编解码器。此时会清空已配置的参数和输入输出数据。\n
 * 如果要继续编解码，需要再次调用Configure接口配置编解码器实例。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：OH_AVCodec实例为nullptr或无效。\n
 *         AV_ERR_INVALID_STATE：编解码器服务不可用。
 * @since 11
 */

OH_AVErrCode OH_AudioCodec_Reset(OH_AVCodec *codec);

/**
 * @brief 获取编解码器输出数据的OH_AVFormat信息。\n
 * 需要注意的是，返回值所指向的OH_AVFormat实例需要开发者调用{@link OH_AVFormat_Destroy}接口手动释放。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @return 返回OH_AVFormat句柄指针，生命周期将使用下一个{@link OH_AudioCodec_GetOutputDescription}刷新，或使用OH_AVCodec销毁。
 * @since 11
 */
OH_AVFormat *OH_AudioCodec_GetOutputDescription(OH_AVCodec *codec);

/**
 * @brief 配置编解码器的动态参数。\n
 * 注意，该接口必须在编解码器启动后才能调用。另外，参数配置错误可能会导致编解码失败。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @param format OH_AVFormat句柄指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：输入参数为nullptr或无效。\n
 *         AV_ERR_INVALID_STATE：编解码器服务不可用。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许操作，这可能是由于状态不正确或不支持的操作。\n
 *         AV_ERR_UNKNOWN：发生内部错误，建议检查日志。
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_SetParameter(OH_AVCodec *codec, const OH_AVFormat *format);

/**
 * @brief 通知音频编解码器已完成对index所对应缓冲区进行输入数据的填充。\n
 * {@link OH_AVCodecOnNeedInputBuffer}回调将报告可用的输入缓冲区和对应的索引值。\n
 * 一旦具有指定索引的缓冲区被提交给音频编解码器，该缓冲区将无法再次访问，
 * 直到再次收到{@link OH_AVCodecOnNeedInputBuffer}回调，收到相同索引时此缓冲区才可使用。\n
 * 此外，对于某些编解码器，需要在开始时向编解码器输入编解码特定配置数据(Codec-Specific-Data)，以初始化编解码器的编解码过程。\n
 * 注意：当返回值为AV_ERR_UNKNOWN时此次调用不生效，输入缓冲区仍为未处理状态，
 * 需根据返回的特定错误代码处理后输入相同的index重新调用OH_AudioCodec_PushInputBuffer。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @param index 输入回调{@link OH_AVCodecOnNeedInputBuffer}给出的索引值。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：输入的index已使用或无效，需使用其他{@link OH_AVCodecOnNeedInputBuffer}回调返回的index。\n
 *         AV_ERR_INVALID_STATE：编解码器状态错误，调用OH_AudioCodec_PushInputBuffer前需确保按顺序
 * 成功调用{@link OH_AudioCodec_Configure}、{@link OH_AudioCodec_Prepare}、{@link OH_AudioCodec_Start}。\n
 *         AV_ERR_UNKNOWN：输入buffer size无效，需确保buffer设置了正确的buffer size和flags。
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_PushInputBuffer(OH_AVCodec *codec, uint32_t index);

/**
 * @brief 将处理后的输出缓冲区返回给编解码器。使用完输出缓冲区后需及时调用此接口进行释放，否则会阻塞编解码流程。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @param index 输出{@link OH_AVCodecOnNewOutputBuffer}给出的索引值。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：输入参数为nullptr或无效。缓冲区索引应该由{@link OH_AVCodecOnNewOutputBuffer}给出。\n
 *         AV_ERR_INVALID_STATE：编解码器服务不可用。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许操作，这可能是由于状态不正确或不支持的操作。\n
 *         AV_ERR_UNKNOWN：发生内部错误，建议检查日志。
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_FreeOutputBuffer(OH_AVCodec *codec, uint32_t index);

/**
 * @brief 检查当前编解码器实例是否有效。\n
 * 可用于后台故障恢复或应用程序从后台恢复时检测编解码器有效状态。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @param isValid 输出参数。指向布尔类型的指针，true：编解码器实例有效，false：编解码器实例无效。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：输入参数为nullptr或无效。\n
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_IsValid(OH_AVCodec *codec, bool *isValid);

/**
 * @brief 设置解密信息。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @param mediaKeySession 带有解密功能的媒体秘钥会话实例。
 * @param secureAudio 是否使用安全解码器。使用安全解码器为true,否则为false。\n
 * 注意：当前音频解密尚不支持使用安全解码器。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：OH_AVCodec实例为nullptr或无效，mediaKeySystemInfo实例为nullptr或无效。\n
 *         AV_ERR_INVALID_STATE：编解码器服务不可用。\n
 *         AV_ERR_NO_MEMORY：请求内存失败。
 * @since 12
 */
OH_AVErrCode OH_AudioCodec_SetDecryptionConfig(OH_AVCodec *codec, MediaKeySession *mediaKeySession,
    bool secureAudio);

/**
 * @brief 在设置的超时时间内，尝试查询对应音频编解码器可用的输入缓冲区的索引值。\n
 *
 * 获取到索引值后，使用{@link OH_AudioCodec_GetInputBuffer}接口获取索引值对应的缓冲区。\n
 * 在缓冲区填充数据后，使用{@link OH_AudioCodec_PushInputBuffer}输入对应索引值，将缓冲区数据送到编解码器。\n
 *
 * 注意：此接口仅可在音频编解码的同步模式中使用。
 *
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @param index 输出参数，获取到的输入缓冲区的索引值。
 * @param timeoutUs 超时时间，单位：微秒。设置为负值时表示无限等待。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：执行失败，输入参数错误。\n
 *         AV_ERR_INVALID_STATE：执行失败，状态非法，没有启动编解码器等。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：执行失败，不允许非同步模式下调用。\n
 *         AV_ERR_TRY_AGAIN_LATER：执行失败，超时时间内获取不到可用的缓冲区。
 * @since 20
 */
OH_AVErrCode OH_AudioCodec_QueryInputBuffer(struct OH_AVCodec *codec, uint32_t *index, int64_t timeoutUs);

/**
 * @brief 输入索引值，获取对应音频编解码器中该索引值对应的输入缓冲区。
 *
 * 注意：此接口仅可在音频编解码的同步模式中使用。
 *
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @param index 输入缓冲区的索引值。该索引值通过接口{@link OH_AudioCodec_QueryInputBuffer}获取。
 * @return 如果执行成功，则返回一个指向OH_AVBuffer实例的指针，否则返回NULL。
 * @since 20
 */
OH_AVBuffer *OH_AudioCodec_GetInputBuffer(struct OH_AVCodec *codec, uint32_t index);

/**
 * @brief 在设置的超时时间内，尝试查询对应音频编解码器可用的输出缓冲区的索引值。
 *
 * 获取到索引值后，通过{@link OH_AudioCodec_GetOutputBuffer}接口获取的输出缓冲区使用完后，\n
 * 需要调用{@link OH_AudioCodec_FreeOutputBuffer}接口进行释放。释放后无法再次使用，长期不释放会阻塞编解码流程。
 *
 * 注意：此接口仅可在音频编解码的同步模式中使用。
 *
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @param index 输出参数，获取到的输出缓冲区的索引值。
 * @param timeoutUs 超时时间，单位：微秒。设置为负值时表示无限等待。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：执行失败，输入参数错误。\n
 *         AV_ERR_INVALID_STATE：执行失败，状态非法，没有启动编解码器等。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：执行失败，不允许非同步模式下调用。\n
 *         AV_ERR_STREAM_CHANGED：解码输出流格式发生变化, 可以通过调用{@link OH_AudioCodec_GetOutputDescription}接口获取新的流信息。\n
 *         AV_ERR_TRY_AGAIN_LATER：执行失败，超时时间内获取不到可用的缓冲区。
 * @since 20
 */
OH_AVErrCode OH_AudioCodec_QueryOutputBuffer(struct OH_AVCodec *codec, uint32_t *index, int64_t timeoutUs);

/**
 * @brief 输入索引值，获取对应音频编解码器中该索引值对应的输出缓冲区。
 *
 * 注意：此接口仅可在音频编解码的同步模式中使用。
 *
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec 指向OH_AVCodec实例的指针。
 * @param index 输出缓冲区的索引值。该索引值通过接口{@link OH_AudioCodec_QueryOutputBuffer}获取。
 * @return 如果执行成功，则返回一个指向OH_AVBuffer实例的指针，否则返回NULL。
 * @since 20
 */
OH_AVBuffer *OH_AudioCodec_GetOutputBuffer(struct OH_AVCodec *codec, uint32_t index);
#ifdef __cplusplus
}
#endif
#endif // NATIVE_AVCODEC_AUDIOCODEC_H

/** @} */
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
 * @addtogroup VideoEncoder
 * @{
 * 
 * @brief VideoEncoder模块提供用于视频编码的接口。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @since 9
 */


/**
 * @file native_avcodec_videoencoder.h
 * 
 * @brief 声明用于视频编码的接口。
 * @sample [AVCodec](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/BasicFeature/Media/AVCodec)
 * 
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avcodec_videoencoder.h>
 * @library libnative_media_venc.so
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @since 9
 */

#ifndef NATIVE_AVCODEC_VIDEOENCODER_H
#define NATIVE_AVCODEC_VIDEOENCODER_H

#include <stdint.h>
#include <stdio.h>
#include "native_avcodec_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 配置随帧参数，当需要设置index对应帧的编码参数时，可以通过该接口设置。只在Surface模式生效。\n
 * 该接口只能在Surface模式下使用，使用前需要调用OH_VideoEncoder_RegisterParameterCallback接口注册。\n
 * 在Buffer模式下，OH_AVBuffer可以直接携带帧的编码参数，当前可以支持的随帧参数有帧级QPMin/QPMax，指定LTR设置参考帧。
 *
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param index 对应编码帧的index。
 * @param parameter  编码参数。
 * @param userData 开发者执行回调所依赖的数据。
 * @since 12
 */
typedef void (*OH_VideoEncoder_OnNeedInputParameter)(OH_AVCodec *codec, uint32_t index, OH_AVFormat *parameter,
                                                     void *userData);
/**
 * @brief 根据MIME类型创建视频编码器实例，推荐使用。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param mime MIME类型描述字符串，请参阅{@link AVCODEC_MIME_TYPE}。
 * @return 成功则返回一个指向视频编码实例的指针。
 * 如果输入为不支持的编码器类型或内存不足时，则返回NULL。
 * @since 9
 */
OH_AVCodec *OH_VideoEncoder_CreateByMime(const char *mime);

/**
 * @brief 根据视频编码器名称创建视频编码器实例。使用此接口的前提是知道编码器的确切名称，编码器的名称可以通过能力查询获取。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param name 视频编码器名称。
 * @return 成功则返回一个指向视频编码实例的指针。
 * 如果输入是不支持编码器名称或者内存资源不足，则返回NULL。
 * @since 9
 */
OH_AVCodec *OH_VideoEncoder_CreateByName(const char *name);

/**
 * @brief 创建支持前处理的主视频编码器实例。\n
 *
 * 该编码器支持以下能力：\n
 * 1. 前处理功能（降采样、裁剪、丢帧）。\n
 * 2. 从该主编码器创建副编码器实现一入二出双路编码。\n
 *
 * 通过该接口创建的编码器仅支持Surface模式，不支持Buffer模式和同步模式。创建成功后需通过{@link OH_VideoEncoder_Destroy}销毁。\n
 * 
 * @param mime MIME类型字符串，不可为NULL。必须是支持的类型，如OH_AVCODEC_MIMETYPE_VIDEO_AVC、OH_AVCODEC_MIMETYPE_VIDEO_HEVC。
 * @param codec 双指针，用于接收创建的编码器实例，不可为NULL。创建成功后需通过{@link OH_VideoEncoder_Destroy}销毁。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：mime为NULL/codec为NULL/MIME类型不支持。\n
 *         AV_ERR_NO_MEMORY：内存分配失败。
 *
 * @since 26.0.0
 */
OH_AVErrCode OH_VideoEncoder_CreatePrimaryWithPreproc(const char *mime, OH_AVCodec **codec);

/**
 * @brief 从主编码器创建副视频编码器实例。\n
 *
 * 副编码器具有以下特性：\n
 * 1. 与主编码器共享输入源。\n
 * 2. 可独立配置编码参数。\n
 * 3. 可使用不同的前处理参数。\n
 * 4. 可独立启动/停止（不依赖主编码器的启停状态）。\n
 * 5. 生命周期必须短于主编码器。\n
 * 6. 一个主编码器同时只能拥有一个副编码器。\n
 * 必须在主编码器创建成功之后才能创建。创建成功后需通过{@link OH_VideoEncoder_Destroy}销毁。销毁顺序建议先Destroy Secondary再Destroy Primary。\n
 *
 * @param primary 主编码器句柄，必须由{@link OH_VideoEncoder_CreatePrimaryWithPreproc}创建，不可为NULL。
 * @param codec 双指针，用于接收创建的副编码器实例，不可为NULL。创建成功后需通过{@link OH_VideoEncoder_Destroy}销毁。
 *
 * @return AV_ERR_OK：执行成功。
 *         AV_ERR_INVALID_VAL：primary为NULL/codec为NULL/primary不是有效的主编码器。
 *         AV_ERR_OPERATE_NOT_PERMIT：主编码器已存在关联的副编码器。
 *         AV_ERR_NO_MEMORY：内存分配失败。
 *
 * @since 26.0.0
 */
OH_AVErrCode OH_VideoEncoder_CreateSecondaryFromPrimary(OH_AVCodec *primary, OH_AVCodec **codec);

/**
 * @brief 清理编码器内部资源，销毁编码器实例。不能重复销毁。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Destroy(OH_AVCodec *codec);

/**
 * @brief 设置OH_AVCodecCallback回调函数，让应用可以响应视频编码器生成的事件。在调用OH_VideoEncoder_Prepare接口之前，必须调用此接口。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param callback 所有回调函数的集合。
 * @param userData 开发者执行回调所依赖的数据。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @deprecated since 11
 * @useinstead {@link OH_VideoEncoder_RegisterCallback}
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_SetCallback(OH_AVCodec *codec, OH_AVCodecAsyncCallback callback, void *userData);

/**
 * @brief 注册OH_AVCodecCallback回调函数，让应用可以响应视频编码器生成的事件。在调用OH_VideoEncoder_Prepare接口之前，必须调用此接口。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param callback 所有回调函数的集合。
 * @param userData 开发者执行回调所依赖的数据。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @since 11
 */
OH_AVErrCode OH_VideoEncoder_RegisterCallback(OH_AVCodec *codec, OH_AVCodecCallback callback, void *userData);

/**
 * @brief 注册OH_AVCodecCallback输入参数回调函数，让应用可以响应视频编码器生成的事件。编码Surface模式，需要设置随帧参数时，须使用该接口。\n
 * 如果使用该接口，必须在{@link OH_VideoEncoder_Configure}之前调用该接口。
 *
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param onInputParameter 输入参数回调指针。
 * @param userData 开发者执行回调所依赖的数据。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：本接口必须在OH_VideoEncoder_Prepare接口前调用，如果在其他状态时调用，则返回此错误码。
 * @since 12
 */
OH_AVErrCode OH_VideoEncoder_RegisterParameterCallback(OH_AVCodec *codec,
                                                       OH_VideoEncoder_OnNeedInputParameter onInputParameter,
                                                       void *userData);

/**
 * @brief 配置视频编码器的编码参数，通常需要配置输入视频帧的描述信息，如帧的宽、高、像素格式等。必须在调用OH_VideoEncoder_Prepare接口之前，调用此接口。\n
 * 该接口对配置参数进行合法性校验，部分非法参数不会强校验，使用默认值或直接丢弃。部分非法参数会强校验，具体规则如下：\n
 * 以下参数的配置范围可通过[能力查询](../../media/avcodec/obtain-supported-codecs.md)获取，OH_MD_KEY_I_FRAME_INTERVAL暂不支持能力查询。\n
 * 设置OH_MD_KEY_VIDEO_ENCODER_ENABLE_TEMPORAL_SCALABILITY、OH_MD_KEY_VIDEO_ENCODER_LTR_FRAME_COUNT参数时，
 * 如果当前平台不支持这些功能，该接口不会报错，而是继续按照正常编码流程执行。
 * @table 参数校验：
 * | Key     | 配置正常范围的值 | 配置超出范围的值 | 不配置该参数 |
 * | ------- | -------- | -------- | ------ |
 * | OH_MD_KEY_WIDTH  | AV_ERR_OK | AV_ERR_INVALID_VAL | AV_ERR_INVALID_VAL |
 * | OH_MD_KEY_HEIGHT | AV_ERR_OK | AV_ERR_INVALID_VAL | AV_ERR_INVALID_VAL |
 * | OH_MD_KEY_PIXEL_FORMAT 请参阅[OH_AVPixelFormat](_core.md#oh_avpixelformat-1) | AV_ERR_OK | AV_ERR_UNSUPPORT | AV_ERR_OK    |
 * | OH_MD_KEY_FRAME_RATE | AV_ERR_OK | AV_ERR_INVALID_VAL | AV_ERR_OK |
 * | OH_MD_KEY_PROFILE 请参阅[OH_MD_KEY_PROFILE](_codec_base.md#oh_md_key_profile)    | AV_ERR_OK | AV_ERR_INVALID_VAL | AV_ERR_OK | 
 * | OH_MD_KEY_I_FRAME_INTERVAL | AV_ERR_OK |  \\       | AV_ERR_OK | 
 * @tableEnd
 * 
 * @table
 * | OH_MD_KEY_<br>BITRATE | OH_MD_KEY_<br>QUALITY | OH_MD_KEY_<br>VIDEO_ENCODER_BITRATE_MODE | 返回值 | 说明     |
 * | -------- | ---------| ---------- | ---- | ---------- |
 * | \\      | \\      | \\           |  AV_ERR_OK    | 使用编码器默认值 |
 * | 超出范围    | 超出范围    | 不支持的模式       | AV_ERR_INVALID_VAL | 异常值均报错 |
 * | 正常值     | 正常值     | \\           | AV_ERR_INVALID_VAL | Bitrate与Quality冲突 |
 * | 正常值     | \\      | \\           | AV_ERR_OK | 使能默认码控模式 |
 * | 正常值     | \\      | BITRATE_MODE_VBR、BITRATE_MODE_CBR      | AV_ERR_OK | \\        |
 * | 正常值     | \\      | BITRATE_MODE_CQ           | AV_ERR_INVALID_VAL | Bitrate 与 CQ 模式冲突      |
 * | \\      | 正常值     | \\           | AV_ERR_OK | 使能 CQ 模式 |
 * | \\      | 正常值     | BITRATE_MODE_CQ           | AV_ERR_OK |  \\       |
 * | \\      | 正常值     | BITRATE_MODE_VBR、BITRATE_MODE_CBR      | AV_ERR_INVALID_VAL | Quality 与 VBR、CBR 模式冲突 |
 * | \\      | \\      | BITRATE_MODE_VBR、BITRATE_MODE_CBR      | AV_ERR_OK | 使用编码器默认码率|
 * | \\      | \\      | BITRATE_MODE_CQ           | AV_ERR_OK    | 使用默认quality  |
 * @tableEnd
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param format 指向OH_AVFormat的指针，用于给出要编码的视频轨的描述。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：1. 输入的codec指针为非编码器实例，或者为空指针；2. 输入format参数不支持。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：本接口必须在OH_VideoEncoder_Prepare接口前调用，如果在其他状态时调用，则返回此错误码。\n
 *         AV_ERR_UNSUPPORT：不支持的像素格式。
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Configure(OH_AVCodec *codec, OH_AVFormat *format);

/**
 * @brief 准备编码器的内部资源，在OH_VideoEncoder_Configure接口后调用。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：当前编码器状态不支持调用本接口。
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Prepare(OH_AVCodec *codec);

/**
 * @brief 调用{@link OH_VideoEncoder_Prepare}接口成功后调用此接口启动编码器。成功启动后，编码器将开始报告注册的回调事件。\n
 * Surface模式下，在surface中有正确的输入后，每完成一帧编码会触发OnNewOutputBuffer。\n
 * Buffer模式下，编码器会立即触发输入回调，开发者每完成一次输入，编码器执行编码，每完成一帧编码会触发OnNewOutputBuffer。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：当前编码器状态不支持调用本接口。
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Start(OH_AVCodec *codec);

/**
 * @brief 停止编码器，释放输入输出buffer。停止之后，可以通过调用OH_VideoEncoder_Start接口重新进入Running状态。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：当前编码器状态不支持调用本接口。
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Stop(OH_AVCodec *codec);

/**
 * @brief 清除编码器中缓存的输入和输出数据及参数集如H.264格式的PPS/SPS。\n
 * 
 * 调用此接口后，以前通过异步回调上报的所有缓冲区index都将失效，请确保不要访问这些index对应的缓冲区。该接口不能连续调用。
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：当前编码器状态不支持调用本接口。
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Flush(OH_AVCodec *codec);

/**
 * @brief 重置编码器，编码器回到初始化状态。如果要继续编码，需要再次调用OH_VideoEncoder_Configure接口配置编码器实例。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Reset(OH_AVCodec *codec);

/**
 * @brief 获取编码器输出数据的OH_AVFormat信息。\n
 * 
 * 需要注意的是，返回值指向的OH_AVFormat实例的生命周期需要开发者通过调用接口{@link OH_AVFormat_Destroy}释放。
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @return 返回指向OH_AVFormat实例的指针。
 * 当输入的codec指针非编码实例，或者为空指针，则返回NULL。
 * @since 9
 */
OH_AVFormat *OH_VideoEncoder_GetOutputDescription(OH_AVCodec *codec);

/**
 * @brief 在编码器运行时设置编码器参数。\n
 * 注意，此接口只有在编码器启动后才能调用。同时，不正确的参数设置可能会导致编码失败。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param format 指向OH_AVFormat实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：1. 输入的codec指针为非编码器实例，或者为空指针；2. 输入format参数不支持。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：当前编码器状态不支持调用本接口。
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_SetParameter(OH_AVCodec *codec, OH_AVFormat *format);

/**
 * @brief 从视频编码器获取输入surface，必须在调用OH_VideoEncoder_Configure接口之后OH_VideoEncoder_Prepare接口之前调用此接口。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param window 指向OHNativeWindow实例的指针, 请参阅{@link OHNativeWindow}。
 * 应用负责管理window的生命周期，结束时调用{@link OH_NativeWindow_DestroyNativeWindow}释放。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_GetSurface(OH_AVCodec *codec, OHNativeWindow **window);

/**
 * @brief 将处理后的输出缓冲区返回给编码器。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param index 输出缓冲区对应的索引值。由{@link OH_AVCodecOnNewOutputData}给出。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：当前编码器状态不支持调用本接口。
 * @deprecated since 11
 * @useinstead {@link OH_VideoEncoder_FreeOutputBuffer}
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_FreeOutputData(OH_AVCodec *codec, uint32_t index);

/**
 * @brief 通知视频编码器输入流已结束。建议使用此接口进行通知。该接口只在Surface模式下使用，
 * Buffer模式通过OH_AVBuffer携带EOS信息，通知输入流的结束。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：当前编码器状态不支持调用本接口。
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_NotifyEndOfStream(OH_AVCodec *codec);

/**
 * @brief 将填入数据的输入缓冲区提交给视频编码器。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param index 输入缓冲区对应的索引值。由{@link OH_AVCodecOnNeedInputData}给出。
 * @param attr 缓冲区中包含数据的描述信息。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：\n
 *         1. 输入的codec指针为非编码器实例，或者为空指针；\n
 *         2. index非法，该错误不影响后续编码流程。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：当前编码器状态不支持调用本接口。
 * @deprecated since 11
 * @useinstead {@link OH_VideoEncoder_PushInputBuffer}
 * @since 10
 */
OH_AVErrCode OH_VideoEncoder_PushInputData(OH_AVCodec *codec, uint32_t index, OH_AVCodecBufferAttr attr);

/**
 * @brief Buffer模式下，将index对应的OH_AVBuffer送入编码器编码。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param index 输入缓冲区对应的索引值。由{@link OH_AVCodecOnNeedInputBuffer}给出。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：
 *         1. 输入的codec指针为非编码器实例，或者为空指针；
 *         2. index非法，该错误不影响后续编码流程。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：当前编码器状态不支持调用本接口。
 * @since 11
 */
OH_AVErrCode OH_VideoEncoder_PushInputBuffer(OH_AVCodec *codec, uint32_t index);

/**
 * @brief Surface模式下，将index对应帧的编码参数送入编码器编码。
 *
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param index 输入参数缓冲区对应的索引值。由{@link OH_AVCodecOnNeedInputBuffer}给出。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：\n
 *         1. 输入的codec指针为非编码器实例，或者为空指针；\n
 *         2. index非法，该错误不影响后续编码流程。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：当前编码器状态不支持调用本接口。
 * @since 12
 */
OH_AVErrCode OH_VideoEncoder_PushInputParameter(OH_AVCodec *codec, uint32_t index);

/**
 * @brief 将处理后的index对应的OH_AVBuffer退回给编码器。开发者使用完需要及时调用此接口释放输出缓存区，否则会阻塞编码流程。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param index 输出缓冲区对应的索引值。由{@link OH_AVCodecOnNeedInputBuffer}给出。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码实例内部异常，如内部出现异常空指针。\n
 *         AV_ERR_INVALID_VAL：\n
 *         1. 输入的codec指针为非编码器实例，或者为空指针；\n
 *         2. index非法，该错误不影响后续编码流程。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：当前编码器状态不支持调用本接口。
 * @since 11
 */
OH_AVErrCode OH_VideoEncoder_FreeOutputBuffer(OH_AVCodec *codec, uint32_t index);

/**
 * @brief 编码器接收到的图像的描述信息。调用{@link OH_VideoEncoder_Configure}后调用此接口。\n
 * 需要注意的是，返回指针所指向的OH_AVFormat实例的生命周期需要由开发者通过调用{@link OH_AVFormat_Destroy}接口释放。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @return 返回指向OH_AVFormat实例的指针。
 * 当codec指针非编码实例，或者为空指针，则返回NULL。
 * @since 10
 */
OH_AVFormat *OH_VideoEncoder_GetInputDescription(OH_AVCodec *codec);

/**
 * @brief 在编码器实例存在的情况下，检查当前编码器服务是否有效。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param isValid 输出参数，指向布尔类型的指针。
 * 只有当接口返回AV_ERR_OK时，该值表示编码器服务的有效性（true为有效，false为无效）。建议开发者将isValid初始化为false。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。
 * @since 10
 */
OH_AVErrCode OH_VideoEncoder_IsValid(OH_AVCodec *codec, bool *isValid);

/**
 * @brief 视频编码器的码率控制模式。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @deprecated since 14
 * @useinstead {@link OH_BitrateMode}
 * @since 9
 */
typedef enum OH_VideoEncodeBitrateMode {
    /** 
     * @brief 恒定码率模式。
     * @deprecated since 14
     * @useinstead {@link BITRATE_MODE_CBR}
    */
    CBR = 0,
    /** 
     * @brief 可变码率模式。
     * @deprecated since 14
     * @useinstead {@link BITRATE_MODE_VBR}
    */
    VBR = 1,
    /** 
     * @brief 恒定QP模式。
     * @deprecated since 14
     * @useinstead {@link BITRATE_MODE_CQ}
    */
    CQ = 2,
} OH_VideoEncodeBitrateMode;

/**
 * @brief 查询下一个可用输入缓冲区的索引。\n
 * 
 * 调用此接口后需要接着调用{@link OH_VideoEncoder_GetInputBuffer}接口获取缓冲区实例，并通过{@link OH_VideoEncoder_PushInputBuffer}接口传递给编码器。\n
 * 需要注意的是，上述操作仅在同步模式下支持。
 *
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param index 输入buffer对应的索引值。
 * @param timeoutUs 超时时长，单位为微秒。负值：无限等待；0：立即退出；正值：等待指定时长后退出。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前编码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：禁止异步模式下使用。\n
 *         AV_ERR_TRY_AGAIN_LATER：查询失败，建议等待短暂间隔后重试。
 * @since 20
 */
OH_AVErrCode OH_VideoEncoder_QueryInputBuffer(struct OH_AVCodec *codec, uint32_t *index, int64_t timeoutUs);

/**
 * @brief 获取可用输入缓冲区的实例。\n
 * 需要注意的是，此接口仅适用于同步模式。
 *
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param index 输入buffer对应的索引值，可通过{@link OH_VideoEncoder_QueryInputBuffer} 接口获取。
 * @return 如果执行成功，则返回一个指向OH_AVBuffer实例的指针，否则返回NULL。
 * @since 20
 */
OH_AVBuffer *OH_VideoEncoder_GetInputBuffer(struct OH_AVCodec *codec, uint32_t index);

/**
 * @brief 查询下一个可用输出缓冲区的索引。
 * 
 * 通过{@link OH_VideoEncoder_GetOutputBuffer}接口获取的缓冲区实例可以通过{@link OH_VideoEncoder_FreeOutputBuffer}接口将处理后的输出缓冲区返回到编码器。\n
 * 需要注意的是，上述操作仅在同步模式下支持。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param index 输出buffer对应的索引值。
 * @param timeoutUs 超时时长，单位为微秒。负值：无限等待；0：立即退出；正值：等待指定时长后退出。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的编码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非编码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前编码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：禁止异步模式下使用。\n
 *         AV_ERR_STREAM_CHANGED：流格式已变更，可以通过调用{@link OH_VideoEncoder_GetOutputDescription}接口获取新的流信息。\n
 *         AV_ERR_TRY_AGAIN_LATER：查询失败，建议等待短暂间隔后重试。
 * @since 20
 */
OH_AVErrCode OH_VideoEncoder_QueryOutputBuffer(struct OH_AVCodec *codec, uint32_t *index, int64_t timeoutUs);

/**
 * @brief 获取可用输出缓冲区的实例。\n
 * 需要注意的是，此接口仅适用于同步模式。
 *
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @param codec 指向视频编码实例的指针。
 * @param index 输出buffer对应的索引值，可通过{@link OH_VideoEncoder_QueryOutputBuffer}接口获取。
 * @return 如果执行成功，则返回一个指向OH_AVBuffer实例的指针，否则返回NULL。
 * @since 20
 */
OH_AVBuffer *OH_VideoEncoder_GetOutputBuffer(struct OH_AVCodec *codec, uint32_t index);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVCODEC_VIDEOENCODER_H

/** @} */
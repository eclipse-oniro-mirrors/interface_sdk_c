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
 * @addtogroup VideoDecoder
 * @{
 * 
 * @brief VideoDecoder模块提供用于视频解码的函数。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @since 9
 */

/**
 * @file native_avcodec_videodecoder.h
 * 
 * @brief 声明用于视频解码的Native API。
 * @sample [AVCodec](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/BasicFeature/Media/AVCodec)
 * 
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avcodec_videodecoder.h>
 * @library libnative_media_vdec.so
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @since 9
 */

#ifndef NATIVE_AVCODEC_VIDEODECODER_H
#define NATIVE_AVCODEC_VIDEODECODER_H

#include <stdint.h>
#include <stdio.h>
#include "native_avcodec_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 为MediaKeySession定义native层对象。
 *
 * @since 11
 */
typedef struct MediaKeySession MediaKeySession;

/**
 * @brief 根据MIME类型创建视频解码器实例，大多数情况下建议使用。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param mime MIME类型描述字符串，请参阅{@link AVCODEC_MIME_TYPE}。
 * @return 返回一个指向视频解码实例的指针。
 * 当传入的解码器类型不支持或者内存资源耗尽时，返回NULL。
 * @since 9
 */
OH_AVCodec *OH_VideoDecoder_CreateByMime(const char *mime);

/**
 * @brief 根据视频解码器名称创建视频解码器实例。使用此接口的前提是知道解码器的确切名称，解码器的名称可以通过能力查询获取。\n
 *
 * 详情请参见：[获取支持的编解码能力](../../media/avcodec/obtain-supported-codecs.md#创建指定名称的编解码器)。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param name 视频解码器名称。
 * @return 返回指向视频解码实例的指针。
 * 当输入的解码器名称不支持或者内存资源耗尽时，返回NULL。
 * @since 9
 */
OH_AVCodec *OH_VideoDecoder_CreateByName(const char *name);

/**
 * @brief 清理解码器内部资源，销毁解码器实例。不能重复销毁。
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非解码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @since 9
 */

OH_AVErrCode OH_VideoDecoder_Destroy(OH_AVCodec *codec);

/**
 * @brief 设置异步回调函数，让应用可以响应视频解码器生成的事件。在调用OH_VideoDecoder_Prepare接口之前，必须调用此接口。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param callback 所有回调函数的集合。
 * @param userData 开发者执行回调所依赖的数据。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非解码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @deprecated since 11
 * @useinstead {@link OH_VideoDecoder_RegisterCallback}
 * @since 9
 */
OH_AVErrCode OH_VideoDecoder_SetCallback(OH_AVCodec *codec, OH_AVCodecAsyncCallback callback, void *userData);

/**
 * @brief 注册异步回调函数，让应用可以响应视频解码器生成的事件。在调用OH_VideoDecoder_Prepare接口之前，必须调用此接口。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码器实例的指针。
 * @param callback 所有回调函数的集合。
 * @param userData 开发者执行回调所依赖的数据。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非解码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @since 11
 */
OH_AVErrCode OH_VideoDecoder_RegisterCallback(OH_AVCodec *codec, OH_AVCodecCallback callback, void *userData);

/**
 * @brief 设置输出surface以提供视频解码输出。\n
 * 在初始化阶段，必须在调用OH_VideoDecoder_Prepare接口之前调用此接口。在Executing状态可以直接调用该接口。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param window 指向OHNativeWindow实例的指针，请参阅{@link OHNativeWindow}。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：本接口仅支持在Surface模式下调用, 如果在Buffer模式调用, 则返回此错误码。\n
 *         AV_ERR_INVALID_VAL：1. 输入的codec指针为非解码器实例，或者为空指针；2. window为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。
 * @since 9
 */
OH_AVErrCode OH_VideoDecoder_SetSurface(OH_AVCodec *codec, OHNativeWindow *window);

/**
 * @brief 配置视频解码器，通常需要配置解码视频的描述信息，这些信息可以从{@link OH_AVSource}中提取。在调用OH_VideoDecoder_Prepare接口之前，必须调用此接口。\n
 * 以下参数的配置范围可通过[能力查询](../../media/avcodec/obtain-supported-codecs.md)获取，OH_MD_KEY_ROTATION配置的参数都支持。\n
 * 设置OH_MD_KEY_VIDEO_ENABLE_LOW_LATENCY接口时如果当前平台不支持，不报错，走正常解码流程。\n
 * @table 参数校验规则：
 * | Key    | 配置正常范围的值 | 配置超出范围的值 | 不配置该参数 |
 * | ----------| -------- | -------- | ------ |
 * | OH_MD_KEY_WIDTH      | AV_ERR_OK       | AV_ERR_INVALID_VAL      | AV_ERR_INVALID_VAL  |
 * | OH_MD_KEY_HEIGHT     | AV_ERR_OK       | AV_ERR_INVALID_VAL       | AV_ERR_INVALID_VAL     |
 * | OH_MD_KEY_PIXEL_FORMAT 请参阅{@link OH_AVPixelFormat}    | AV_ERR_OK       | AV_ERR_UNSUPPORT       | AV_ERR_OK      |
 * | OH_MD_KEY_FRAME_RATE | AV_ERR_OK       | AV_ERR_INVALID_VAL       | AV_ERR_OK     |
 * | OH_MD_KEY_ROTATION 请参阅{@link OH_MD_KEY_ROTATION} | AV_ERR_OK       | AV_ERR_INVALID_VAL       | AV_ERR_OK      |
 * @tableEnd
 * @note 建议按照该实例需要支持的最大分辨率来配置，否则可能会出现高于该分辨率的码流解码会触发异常。该设置直接影响应用的内存使用情况。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param format 指向OH_AVFormat的指针，用于给出要解码的视频轨道的描述。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：1. 输入的codec指针为非解码器实例，或者为空指针；2. 输入format参数不支持。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_INVALID_STATE：本接口必须在OH_VideoDecoder_Prepare接口前调用，如果在其他状态时调用，则返回此错误码。\n
 *         AV_ERR_VIDEO_UNSUPPORTED_COLOR_SPACE_CONVERSION：不支持色彩空间转换功能。\n
 *         AV_ERR_UNSUPPORT：不支持的像素格式。
 * @since 9
 */
OH_AVErrCode OH_VideoDecoder_Configure(OH_AVCodec *codec, OH_AVFormat *format);

/**
 * @brief 准备解码器的内部资源，在调用该接口之前，必须调用OH_VideoDecoder_Configure接口。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非解码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：1. 操作不允许；2. 配置了色彩空间转换功能，但解码器处于Buffer模式。
 * @since 9
 */
OH_AVErrCode OH_VideoDecoder_Prepare(OH_AVCodec *codec);

/**
 * @brief 调用{@link OH_VideoDecoder_Prepare}接口成功后调用此接口启动解码器。成功启动后，解码器将开始报告注册的回调事件。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非解码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：1. 操作不允许；2. 视频色彩空间转换功能已配置，但是没有调用OH_VideoDecoder_Prepare接口。
 * @since 9
 */
OH_AVErrCode OH_VideoDecoder_Start(OH_AVCodec *codec);

/**
 * @brief 停止解码器，释放输入输出buffer。停止后，可以通过调用OH_VideoDecoder_Start接口重新进入Running状态。\n
 * 
 * 需要注意的是，如果编解码器特定数据以前已输入到解码器，则需要再次输入。
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非解码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @since 9
 */
OH_AVErrCode OH_VideoDecoder_Stop(OH_AVCodec *codec);

/**
 * @brief  清除解码器中缓存的输入和输出数据及参数集如H.264格式的PPS/SPS。\n
 * 调用此接口后，以前通过异步回调上报的所有缓冲区index都将失效，请确保不要访问这些index对应的缓冲区。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非解码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @since 9
 */
OH_AVErrCode OH_VideoDecoder_Flush(OH_AVCodec *codec);

/**
 * @brief 重置解码器，解码器回到初始化状态。如果要继续解码，需要再次调用OH_VideoDecoder_Configure接口配置解码器实例。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非解码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @since 9
 */
OH_AVErrCode OH_VideoDecoder_Reset(OH_AVCodec *codec);

/**
 * @brief 获取解码器输出数据的OH_AVFormat信息，请参阅{@link OH_AVFormat}。\n
 * 需要注意的是，指向的OH_AVFormat实例在生命周期结束时需开发者通过调用接口{@link OH_AVFormat_Destroy}释放。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @return 返回指向OH_AVFormat实例的指针。
 * 当输入的codec指针非解码器实例，或者为空指针，则返回NULL。
 * @since 9
 */
OH_AVFormat *OH_VideoDecoder_GetOutputDescription(OH_AVCodec *codec);

/**
 * @brief 设置解码器的动态参数。\n
 * 注意，该接口只能在解码器启动后调用。同时，参数配置错误可能会导致解码失败。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param format 指向OH_AVFormat实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：1. 输入的codec指针为非解码器实例，或者为空指针；2. 输入format参数不支持。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @since 9
 */
OH_AVErrCode OH_VideoDecoder_SetParameter(OH_AVCodec *codec, OH_AVFormat *format);

/**
 * @brief 将填充数据的输入缓冲区提交给视频解码器。\n
 * 输入回调将报告可用的输入缓冲区和相应的index值，请参阅{@OH_AVCodecOnNeedInputData}。
 * 一旦具有指定index的缓冲区提交到视频解码器，则无法再次访问缓冲区，直到再次收到输入回调，报告具有相同index的缓冲区可用。
 * 此外，对于某些解码器，需要在开始时向解码器输入编解码特定数据，以初始化解码器的解码过程，如H.264格式的PPS/SPS数据。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param index 输入Buffer对应的索引值。由{@link OH_AVCodecOnNeedInputData}给出。
 * @param attr 描述缓冲区中包含的数据的信息。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：\n
 *         1. 输入的codec指针为非解码器实例，或者为空指针；\n
 *         2. index非法，该错误不影响后续解码流程。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @deprecated since 11
 * @useinstead {@link OH_VideoDecoder_PushInputBuffer}
 * @since 9
 */
OH_AVErrCode OH_VideoDecoder_PushInputData(OH_AVCodec *codec, uint32_t index, OH_AVCodecBufferAttr attr);

/**
 * @brief 将处理后的输出buffer返回给解码器，并通知解码器完成在输出surface上渲染buffer中包含的解码数据。\n
 * 如果之前没有配置输出surface，则调用此接口仅将指定index对应的输出缓冲区返回给解码器。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param index 输出Buffer对应的索引值。由{@link OH_AVCodecOnNewOutputData}给出。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：\n
 *         1. 输入的codec指针为非解码器实例，或者为空指针；\n
 *         2. index非法，该错误不影响后续解码流程。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @deprecated since 11
 * @useinstead {@link OH_VideoDecoder_RenderOutputBuffer}
 * @since 9
 */
OH_AVErrCode OH_VideoDecoder_RenderOutputData(OH_AVCodec *codec, uint32_t index);

/**
 * @brief 将处理后的输出缓冲区返回到解码器。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param index 输出buffer对应的索引值。由{@link OH_AVCodecOnNewOutputData}给出。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：\n
 *         1. 输入的codec指针为非解码器实例，或者为空指针；\n
 *         2. index非法，该错误不影响后续解码流程。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @deprecated since 11
 * @useinstead {@link OH_VideoDecoder_FreeOutputBuffer}
 * @since 9
 */
OH_AVErrCode OH_VideoDecoder_FreeOutputData(OH_AVCodec *codec, uint32_t index);

/**
 * @brief 通知视频解码器已对index对应的缓冲区完成输入数据的填充。\n
 * 输入回调将报告可用的输入缓冲区和相应的index值，请参阅{@OH_AVCodecOnNeedInputBuffer}。
 * 一旦具有指定index的缓冲区提交到视频解码器，则无法再次访问缓冲区，直到再次收到输入回调，报告具有相同index的缓冲区可用。
 * 此外，对于某些解码器，需要在开始时向解码器输入编解码特定数据，以初始化解码器的解码过程，如H.264格式的PPS/SPS数据。\n
 * 开发者可以使用该接口把解码需要的参数集如H.264格式的PPS/SPS传递给解码器，该参数集可以单独送入解码器也可以和要解码的数据一起传入。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param index 输入buffer对应的索引值。由{@link OH_AVCodecOnNeedInputBuffer}给出。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：\n
 *         1. 输入的codec指针为非解码器实例，或者为空指针；\n
 *         2. index非法，该错误不影响后续解码流程。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。\n
 *         AV_ERR_DRM_DECRYPT_FAILED: 受DRM保护的视频缓冲区解密失败，建议查看日志。
 * @since 11
 */
OH_AVErrCode OH_VideoDecoder_PushInputBuffer(OH_AVCodec *codec, uint32_t index);

/**
 * @brief 将index对应的输出缓冲返回给解码器，缓冲区中携带解码输出数据，并通知解码器完成在输出surface上渲染，输出缓冲包含解码数据。\n
 * 如果之前没有配置输出surface，则调用此接口仅将指定index对应的输出缓冲区返回给解码器。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param index 输出buffer对应的索引值。由{@link OH_AVCodecOnNewOutputBuffer}给出。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：\n
 *         1. 输入的codec指针为非解码器实例，或者为空指针；\n
 *         2. index非法，该错误不影响后续解码流程。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @since 11
 */
OH_AVErrCode OH_VideoDecoder_RenderOutputBuffer(OH_AVCodec *codec, uint32_t index);

/**
 * @brief 将index对应的输出缓冲返回给解码器，缓冲区中携带解码输出数据，并通知解码器在开发者指定的时间内完成在输出surface上渲染，输出缓冲包含解码数据。\n
 * 如果之前没有配置输出surface，则调用此接口仅将指定index对应的输出缓冲区返回给解码器。\n
 * 开发者可以使用时间戳在特定时间（在VSYNC或者缓冲区时间戳之后）渲染缓冲区。若要在指定的时间戳显示，时间戳需要合理接近系统时间，有几点需要注意：\n
 * 1. 缓冲区是按照顺序处理的，因此可能会阻塞后续缓冲区在surface上的显示，如果想要对用户的一些行为做出反应，例如停止或者快进快退视频，这一点很重要。\n
 * 2. 如果多个缓冲区被发送到surface要在同一个VSYNC上渲染，那么最后一个将会被显示，其他的将被丢弃。\n
 * 3. 如果时间戳与当前的系统时间不是“合理接近”，surface将会忽略时间戳，并在可行的最早时间里显示buffer。在此模式下不会丢弃帧。
 * 4. 如果需要由系统根据显示刷新率来丢帧，则必须调用此接口，否则应用需自行实现丢帧逻辑。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param index 输出buffer对应的索引值。由{@link OH_AVCodecOnNewOutputBuffer}给出。
 * @param renderTimestampNs 输出buffer被发送到surface的时间戳，取值范围大于0，应由std::chrono::steady_clock标准库时钟生成，且单位为纳秒。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：\n
 *         1. 输入的codec指针为非解码器实例，或者为空指针；\n
 *         2. index非法，该错误不影响后续解码流程。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @since 12
 */
OH_AVErrCode OH_VideoDecoder_RenderOutputBufferAtTime(OH_AVCodec *codec, uint32_t index, int64_t renderTimestampNs);

/**
 * @brief 将处理后的输出缓冲区返回到解码器。用户使用完需要及时调用此接口释放输出缓存区，否则会阻塞解码流程。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针
 * @param index 输出buffer对应的索引值。由{@link OH_AVCodecOnNewOutputBuffer}给出。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：1. 输入的codec指针为非解码器实例，或者为空指针；2. index非法或者连续给同一个index，该错误不影响后续解码流程。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * @since 11
 */
OH_AVErrCode OH_VideoDecoder_FreeOutputBuffer(OH_AVCodec *codec, uint32_t index);

/**
 * @brief 在解码器实例存在的情况下，检查当前解码器服务是否有效。
 * 
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param isValid 输出参数，指向布尔类型的指针。只有当接口返回AV_ERR_OK时，该值表示解码器服务的有效性（true为有效，false为无效）。建议开发者将isValid初始化为false。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非解码器实例，或者为空指针。
 * @since 10
 */
OH_AVErrCode OH_VideoDecoder_IsValid(OH_AVCodec *codec, bool *isValid);

/**
 * @brief 设置解密配置。在调用OH_VideoDecoder_Prepare接口之前，可选择调用此接口。
 *
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param mediaKeySession 指向带有解密功能的DRM会话实例的指针。
 * @param secureVideoPath 安全视频通路。指定安全视频通路为true，非安全视频通路为false。
 * 在Surface模式下，既支持安全视频通路，也支持非安全视频通路。在Buffer模式下，仅支持非安全视频通路。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：1. 操作不允许；2. 解码服务进程异常；3. 媒体密钥会话服务处于错误状态。\n
 *         AV_ERR_INVALID_VAL：1. 输入的codec指针为非解码器实例或为空指针；2. mediaKeySession为nullptr或无效。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。
 * @since 11
*/
OH_AVErrCode OH_VideoDecoder_SetDecryptionConfig(OH_AVCodec *codec, MediaKeySession *mediaKeySession,
    bool secureVideoPath);

/**
 * @brief 查询下一个可用输入缓冲区的索引。\n
 * 
 * 调用此接口后需要接着调用{@link OH_VideoDecoder_GetInputBuffer}接口获取缓冲区实例，并通过{@link OH_VideoDecoder_PushInputBuffer}接口传递给解码器。\n
 * 需要注意的是，上述操作仅在同步模式下支持。
 *
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param index 输入buffer对应的索引值。
 * @param timeoutUs 超时时长，单位为微秒。负值：无限等待；0：立即退出；正值：等待指定时长后退出。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非解码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：禁止异步模式下使用。\n
 *         AV_ERR_TRY_AGAIN_LATER：查询失败，建议等待短暂间隔后重试。
 * @since 20
 */
OH_AVErrCode OH_VideoDecoder_QueryInputBuffer(struct OH_AVCodec *codec, uint32_t *index, int64_t timeoutUs);

/**
 * @brief 获取可用输入缓冲区的实例。\n
 * 需要注意的是，此接口仅适用于同步模式。
 *
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param index 输入buffer对应的索引值，可通过{@link OH_VideoDecoder_QueryInputBuffer}接口获取。
 * @return 如果执行成功，则返回一个指向OH_AVBuffer实例的指针，否则返回NULL。
 * @since 20
 */
OH_AVBuffer *OH_VideoDecoder_GetInputBuffer(struct OH_AVCodec *codec, uint32_t index);

/**
 * @brief 查询下一个可用输出缓冲区的索引。\n
 * 
 * 通过{@link OH_VideoDecoder_GetOutputBuffer}接口获取的缓冲区实例可以通过执行以下操作来显示或释放解码帧：\n
 * 1. 通过{@link OH_VideoDecoder_FreeOutputBuffer}接口将处理后的输出缓冲区返回到解码器。\n
 * 2. 通过{@link OH_VideoDecoder_RenderOutputBuffer}在输出surface上渲染。\n
 * 3. 通过{@link OH_VideoDecoder_RenderOutputBufferAtTime}在指定时间内完成输出surface上渲染。\n
 * 需要注意的是，上述操作仅在同步模式下支持。
 *
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param index 输出buffer对应的索引值。
 * @param timeoutUs 超时时长，单位为微秒。负值：无限等待；0：立即退出；正值：等待指定时长后退出。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_NO_MEMORY：输入的解码器实例已经销毁。\n
 *         AV_ERR_INVALID_VAL：输入的codec指针为非解码器实例，或者为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_INVALID_STATE：当前解码器状态不支持调用本接口。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：禁止异步模式下使用。\n
 *         AV_ERR_STREAM_CHANGED：流格式已变更，可以通过调用{@link OH_VideoDecoder_GetOutputDescription}接口获取新的流信息。\n
 *         AV_ERR_TRY_AGAIN_LATER：查询失败，建议等待短暂间隔后重试。
 * @since 20
 */
OH_AVErrCode OH_VideoDecoder_QueryOutputBuffer(struct OH_AVCodec *codec, uint32_t *index, int64_t timeoutUs);

/**
 * @brief 获取可用输出缓冲区的实例。需要注意的是，此接口仅适用于同步模式。
 *
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @param codec 指向视频解码实例的指针。
 * @param index 输出buffer对应的索引值，可通过{@link OH_VideoDecoder_QueryOutputBuffer}接口获取。
 * @return 如果执行成功，则返回一个指向OH_AVBuffer实例的指针，否则返回NULL。
 * @since 20
 */
OH_AVBuffer *OH_VideoDecoder_GetOutputBuffer(struct OH_AVCodec *codec, uint32_t index);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVCODEC_VIDEODECODER_H
/** @} */
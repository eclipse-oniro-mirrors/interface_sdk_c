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
 * @addtogroup AudioEncoder
 * @{
 *
 * @brief AudioEncoder模块提供用于音频编码的函数。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @since 9
 */


/**
 * @file native_avcodec_audioencoder.h
 *
 * @brief 音频编码Native API的声明。
 *
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avcodec_audioencoder.h>
 * @library libnative_media_aenc.so
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @since 9
 */
#ifndef NATIVE_AVCODEC_AUDIOENCODER_H
#define NATIVE_AVCODEC_AUDIOENCODER_H

#include <stdint.h>
#include <stdio.h>
#include "native_avcodec_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 根据mime类型创建音频编码器实例，大多数场景下建议使用此方式
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param mime mime类型描述字符串，请参阅 {@link AVCODEC_MIME_TYPE}
 * @return 返回指向OH_AVCodec实例的指针
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_CreateByMime}
 * @since 9
 * @version 1.0
 */
OH_AVCodec *OH_AudioEncoder_CreateByMime(const char *mime);

/**
 * @brief 通过音频编码器名称创建音频编码器实例，使用此接口的前提是知道编码器的确切名称
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param name 音频编码器名称
 * @return 返回指向OH_AVCodec实例的指针
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_CreateByName}
 * @since 9
 * @version 1.0
 */
OH_AVCodec *OH_AudioEncoder_CreateByName(const char *name);

/**
 * @brief 清理编码器内部资源，销毁编码器实例
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param codec 指向OH_AVCodec实例的指针
 * @return 如果执行成功，则返回AV_ERR_OK，否则返回特定错误代码，请参阅 {@link OH_AVErrCode}
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_Destroy}
 * @since 9
 * @version 1.0
 */
OH_AVErrCode OH_AudioEncoder_Destroy(OH_AVCodec *codec);

/**
 * @brief 设置异步回调函数，使您的应用程序可以响应音频编码器生成的事件。在调用Prepare之前，必须调用此接口。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param codec 指向OH_AVCodec实例的指针
 * @param callback 所有回调函数的集合，请参见 {@link OH_AVCodecAsyncCallback}
 * @param userData 用户特定数据
 * @return 如果执行成功，则返回AV_ERR_OK，否则返回特定错误代码，请参阅 {@link OH_AVErrCode}
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_RegisterCallback}
 * @since 9
 * @version 1.0
 */
OH_AVErrCode OH_AudioEncoder_SetCallback(OH_AVCodec *codec, OH_AVCodecAsyncCallback callback, void *userData);

/**
 * @brief 配置音频描述信息。音频编码器通常会根据音频描述信息进行配置。在调用Prepare之前，必须调用此接口
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param codec 指向OH_AVCodec实例的指针
 * @param format 指向OH_AVFormat的指针，给出要编码的音频轨道的描述
 * @return 如果执行成功，则返回AV_ERR_OK，否则返回特定错误代码，请参阅 {@link OH_AVErrCode}
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_Configure}
 * @since 9
 * @version 1.0
 */
OH_AVErrCode OH_AudioEncoder_Configure(OH_AVCodec *codec, OH_AVFormat *format);

/**
 * @brief 准备编码器的内部资源，在调用此接口之前必须调用Configure接口
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param codec 指向OH_AVCodec实例的指针
 * @return 如果执行成功，则返回AV_ERR_OK，否则返回特定错误代码，请参阅 {@link OH_AVErrCode}
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_Prepare}
 * @since 9
 * @version 1.0
 */
OH_AVErrCode OH_AudioEncoder_Prepare(OH_AVCodec *codec);

/**
 * @brief 调用此接口启动编解码器，在Prepare成功后执行。启动后，编码器将开始上报OH_AVCodecOnNeedInputData事件。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param codec 指向OH_AVCodec实例的指针
 * @return 如果执行成功，则返回AV_ERR_OK，否则返回特定错误代码，请参阅 {@link OH_AVErrCode}
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_Start}
 * @since 9
 * @version 1.0
 */
OH_AVErrCode OH_AudioEncoder_Start(OH_AVCodec *codec);

/**
 * @brief 停止编码器。停止后，您可以通过Start重新进入已启动状态
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param codec 指向OH_AVCodec实例的指针
 * @return 如果执行成功，则返回AV_ERR_OK，否则返回特定错误代码，请参阅 {@link OH_AVErrCode}
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_Stop}
 * @since 9
 * @version 1.0
 */
OH_AVErrCode OH_AudioEncoder_Stop(OH_AVCodec *codec);

/**
 * @brief 清除编码器中缓存的输入和输出数据。调用此接口后，以前通过异步回调上报的所有缓冲区
 * 索引都将失效，请确保不要访问这些索引对应的缓冲区
 *
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param codec 指向OH_AVCodec实例的指针
 * @return 如果执行成功，则返回AV_ERR_OK，否则返回特定错误代码，请参阅 {@link OH_AVErrCode}
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_Flush}
 * @since 9
 * @version 1.0
 */
OH_AVErrCode OH_AudioEncoder_Flush(OH_AVCodec *codec);

/**
 * @brief 重置编码器。如果要继续编码，需要再次调用Configure接口配置编码器实例
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param codec 指向OH_AVCodec实例的指针
 * @return 如果执行成功，则返回AV_ERR_OK，否则返回特定错误代码，请参阅 {@link OH_AVErrCode}
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_Reset}
 * @since 9
 * @version 1.0
 */
OH_AVErrCode OH_AudioEncoder_Reset(OH_AVCodec *codec);

/**
 * @brief 获取编码器输出数据的描述信息，详细信息请参见{@link OH_AVFormat}。
 * 需要注意的是，返回值所指向的OH_AVFormat实例的生命周期需要调用者手动释放
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param codec 指向OH_AVCodec实例的指针
 * @return 返回OH_AVFormat句柄指针，生命周期将使用下一个GetOutputDescription
 * 刷新，或使用OH_AVCodec销毁
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_GetOutputDescription}
 * @since 9
 * @version 1.0
 */
OH_AVFormat *OH_AudioEncoder_GetOutputDescription(OH_AVCodec *codec);

/**
 * @brief 配置编码器的动态参数。注意：该接口必须在编码器启动后才能调用。另外，参数配置错误可能会导致编码失败。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param codec 指向OH_AVCodec实例的指针
 * @param format OH_AVFormat句柄指针
 * @return 如果执行成功，则返回AV_ERR_OK，否则返回特定错误代码，请参阅 {@link OH_AVErrCode}
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_SetParameter}
 * @since 9
 * @version 1.0
 */
OH_AVErrCode OH_AudioEncoder_SetParameter(OH_AVCodec *codec, OH_AVFormat *format);

/**
 * @brief 将填充有数据的输入缓冲区提交给音频编码器。{@link OH_AVCodecOnNeedInputData}回调
 * 将报告可用的输入缓冲区和相应的索引值。一旦具有指定索引的缓冲区提交到音频编码器，则无法再次访问此缓冲区，
 * 直到再次收到{@link OH_AVCodecOnNeedInputData}回调，收到相同索引时此缓冲区才可使用。
 * 此外，对于某些编码器，需要在开始时向编码器输入特定配置参数，以初始化编码器的编码过程。
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param codec 指向OH_AVCodec实例的指针
 * @param index 输入缓冲区Buffer对应的索引值
 * @param attr 描述缓冲区中包含的数据的信息
 * @return 如果执行成功，则返回AV_ERR_OK，否则返回特定错误代码，请参阅 {@link OH_AVErrCode}
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_PushInputBuffer}
 * @since 9
 * @version 1.0
 */
OH_AVErrCode OH_AudioEncoder_PushInputData(OH_AVCodec *codec, uint32_t index, OH_AVCodecBufferAttr attr);

/**
 * @brief 将处理后的输出缓冲区返回给编码器
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param codec 指向OH_AVCodec实例的指针
 * @param index 输出缓冲区Buffer对应的索引值
 * @return 如果执行成功，则返回AV_ERR_OK，否则返回特定错误代码，请参阅 {@link OH_AVErrCode}
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_FreeOutputBuffer}
 * @since 9
 * @version 1.0
 */
OH_AVErrCode OH_AudioEncoder_FreeOutputData(OH_AVCodec *codec, uint32_t index);

/**
 * @brief 检查当前编码器实例是否有效。可用于后台故障恢复或应用程序从后台恢复时检测编码器有效状态
 * 
 * @syscap SystemCapability.Multimedia.Media.AudioEncoder
 * @param codec 指向OH_AVCodec实例的指针
 * @param isValid 指向布尔类型的指针，true：编码器实例有效，false：编码器实例无效
 * @return 如果执行成功，则返回AV_ERR_OK，否则返回特定错误代码，请参阅 {@link OH_AVErrCode}
 * @deprecated since 11
 * @useinstead {@link OH_AudioCodec_IsValid}
 * @since 10
 */
OH_AVErrCode OH_AudioEncoder_IsValid(OH_AVCodec *codec, bool *isValid);

#ifdef __cplusplus
}
#endif
#endif // NATIVE_AVCODEC_AUDIOENCODER_H
/** @} */
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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
 * @addtogroup AVTranscoder
 * @{
 *
 * @brief Provides APIs of request capability for Transcoder.
 *
 * @syscap SystemCapability.Multimedia.Media.AVTranscoder
 * @since 20
 * @}
 */
/**
 * @file avtranscoder.h
 *
 * @brief 定义AVTranscoder接口。使用AVTranscoder提供的Native API将源视频文件转码为新视频文件。
 * 
 * @kit MediaKit
 * @library libavtranscoder.so
 * @since 20
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_AVTRANSCODER_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_AVTRANSCODER_H

#include <stdint.h>
#include <stdio.h>
#include "avtranscoder_base.h"
#include "native_avcodec_base.h"
#include "native_averrors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建转码配置参数实例。
 * 
 * @return 如果创建成功返回指向OH_AVTranscoder_Config实例的指针，否则返回空指针。
 * @since 20
 */
OH_AVTranscoder_Config *OH_AVTranscoderConfig_Create();

/**
 * @brief 释放转码配置参数资源。
 * 调用成功后，config实例会被释放并置为nullptr。
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance.
 * @return AV_ERR_OK：释放成功。
 * AV_ERR_INVALID_VAL：config是空指针。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_Release(OH_AVTranscoder_Config* config);

/**
 * @brief 设置转码源视频的文件描述符。
 * 此函数必须在{@link OH_AVTranscoder_Prepare}之前调用。
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance.
 * @param srcFd Source file descriptor.
 * @param srcOffset The offset into the file where the data to be read, in bytes.
 * @param length The length in bytes of the data to be read
 * @return AV_ERR_OK：设置成功。
 * AV_ERR_INVALID_VAL：输入config为空指针，或者源视频文件相关参数错误。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetSrcFD(
    OH_AVTranscoder_Config *config, int32_t srcFd, int64_t srcOffset, int64_t length);

/**
 * @brief 设置转码输出视频的文件描述符。
 * 此函数必须在{@link OH_AVTranscoder_Prepare}之前调用。
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param dstFd Destination file descriptor
 * @return AV_ERR_OK：设置成功。
 * AV_ERR_INVALID_VAL：输入config为空指针，或者输出视频文件描述符是无效的。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstFD(OH_AVTranscoder_Config *config, int32_t dstFd);

/**
 * @brief 设置用于转码的输出视频的编码格式。
 * 当前仅支持AVC和HEVC。若源视频编码格式为HEVC，则默认设置为HEVC，否则默认设置为AVC。
 * 此函数必须在{@link OH_AVTranscoder_Prepare}之前调用。
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param mimeType Destination video mime type. See native_avcodec_base.h
 * @return AV_ERR_OK：设置成功。
 * AV_ERR_INVALID_VAL：输入的config为空指针，或者mimeType是不被允许的。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstVideoType(OH_AVTranscoder_Config *config, const char *mimeType);

/**
 * @brief 设置用于转码的输出音频的编码格式。
 * 当前仅支持AAC。若开发者不设置，则默认设置为AAC。
 * 此函数必须在{@link OH_AVTranscoder_Prepare}之前调用。
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param mimeType Destination audio mime type. See native_avcodec_base.h
 * @return AV_ERR_OK：设置成功。
 * AV_ERR_INVALID_VAL：输入的config为空指针，或者mimeType是不被允许的。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstAudioType(OH_AVTranscoder_Config *config, const char *mimeType);

/**
 * @brief 设置用于转码的输出视频文件的封装格式。
 * 当前封装格式仅支持MP4。
 * 此函数必须在{@link OH_AVTranscoder_Prepare}之前调用。
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param mimeType Destination file type. See native_avcodec_base.h
 * @return AV_ERR_OK：设置成功。
 * AV_ERR_INVALID_VAL：输入的config为空指针，或者mimeType是无效的。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstFileType(OH_AVTranscoder_Config *config, OH_AVOutputFormat mimeType);

/**
 * @brief 设置用于转码的输出音频的码率。
 * 此函数必须在{@link OH_AVTranscoder_Prepare}之前调用。
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param bitrate Destination audio bitrate, in bit/s.
 * @return AV_ERR_OK：设置成功。
 * AV_ERR_INVALID_VAL：输入的config为空指针，或者bitrate值是无效的。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstAudioBitrate(OH_AVTranscoder_Config *config, int32_t bitrate);

/**
 * @brief 设置用于转码的输出视频的码率。
 * 此函数必须在{@link OH_AVTranscoder_Prepare}之前调用。
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param bitrate Destination video bitrate, in bit/s.
 * @return AV_ERR_OK：设置成功。
 * AV_ERR_INVALID_VAL：输入的config为空指针，或者bitrate值是无效的。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstVideoBitrate(OH_AVTranscoder_Config *config, int32_t bitrate);

/**
 * @brief 设置用于转码的输出视频的分辨率，单位为像素（px），其中width为输出视频帧的宽，height为输出视频帧的高。
 * 此函数必须在{@link OH_AVTranscoder_Prepare}之前调用。
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param width Destination for video width, in px.
 * @param height Destination for video height, in px.
 * @return AV_ERR_OK：设置成功。
 * AV_ERR_INVALID_VAL：输入的config为空指针，或者width、height值是无效的。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstVideoResolution(OH_AVTranscoder_Config *config, int32_t width, int32_t height);

/**
 * @brief 创建转码实例。
 * 
 * @return 如果创建成功返回指向OH_AVTranscoder实例的指针，否则返回空指针。
 * @since 20
 */
OH_AVTranscoder *OH_AVTranscoder_Create(void);

/**
 * @brief 进行视频转码的参数设置，准备转码。
 * 此函数必须在{@link OH_AVTranscoder_Start}之前调用，调用成功之后进入AVTRANSCODER_PREPARED状态。
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @param config Pointer to an OH_AVTranscoder_Config instance,
 * see {@link OH_AVTranscoder_Config}
 * @return AV_ERR_OK：成功设置视频转码的参数设置，进入AVTRANSCODER_PREPARED状态。
 * AV_ERR_INVALID_VAL：输入的transcoder是空指针，或者转码准备操作失败。
 * AV_ERR_OPERATE_NOT_PERMIT：当前状态不允许执行Prepare操作，或者是不支持的格式。
 * AV_ERR_IO：IO访问相关的错误。
 * AV_ERR_SERVICE_DIED：媒体服务已停止。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_Prepare(OH_AVTranscoder *transcoder, OH_AVTranscoder_Config *config);

/**
 * @brief 开始转码。
 * 此函数必须在{@link OH_AVTranscoder_Prepare}成功调用之后调用，调用成功之后进入AVTRANSCODER_STARTED状态。
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @return AV_ERR_OK：成功开始转码，进入AVTRANSCODER_STARTED状态。
 * AV_ERR_INVALID_VAL：输入的transcoder是空指针，或者转码开始操作失败。
 * AV_ERR_OPERATE_NOT_PERMIT：当前状态不允许执行Start操作。
 * AV_ERR_IO：IO访问相关的错误。
 * AV_ERR_SERVICE_DIED：媒体服务已停止。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_Start(OH_AVTranscoder *transcoder);

/**
 * @brief 暂停转码。
 * 此函数必须在转码实例处于AVTRANSCODER_STARTED状态时调用，调用成功之后进入AVTRANSCODER_PAUSED状态。
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @return AV_ERR_OK：成功暂停转码，进入AVTRANSCODER_PAUSED状态。
 * AV_ERR_INVALID_VAL：输入的transcoder是空指针，或者转码暂停操作失败。
 * AV_ERR_OPERATE_NOT_PERMIT：当前状态不允许执行Pause操作。
 * AV_ERR_IO：IO访问相关的错误。
 * AV_ERR_SERVICE_DIED：媒体服务已停止。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_Pause(OH_AVTranscoder *transcoder);

/**
 * @brief 恢复转码。
 * 此函数必须在转码实例处于AVTRANSCODER_PAUSED状态时调用，调用成功之后重新进入AVTRANSCODER_STARTED状态。
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @return AV_ERR_OK：成功恢复转码，进入AVTRANSCODER_STARTED状态。
 * AV_ERR_INVALID_VAL：输入的transcoder是空指针，或者转码恢复操作失败。
 * AV_ERR_OPERATE_NOT_PERMIT：当前状态不允许执行Resume操作。
 * AV_ERR_IO：IO访问相关的错误。
 * AV_ERR_SERVICE_DIED：媒体服务已停止。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_Resume(OH_AVTranscoder *transcoder);

/**
 * @brief 取消转码。
 * 此函数须在转码实例处于AVTRANSCODER_STARTED和AVTRANSCODER_PAUSED状态时调用，调用成功之后进入AVTRANSCODER_CANCELLED状态。
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @return AV_ERR_OK：成功取消转码，进入AVTRANSCODER_CANCELLED状态。
 * AV_ERR_INVALID_VAL：输入的transcoder是空指针，或者转码取消操作失败。
 * AV_ERR_OPERATE_NOT_PERMIT：当前状态不允许执行Cancel操作。
 * AV_ERR_IO：IO访问相关的错误。
 * AV_ERR_SERVICE_DIED：媒体服务已停止。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_Cancel(OH_AVTranscoder *transcoder);

/**
 * @brief 释放转码实例资源。
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @return AV_ERR_OK：成功释放转码实例资源。
 * AV_ERR_INVALID_VAL：输入的transcoder是空指针，或者转码释放资源操作失败。
 * AV_ERR_OPERATE_NOT_PERMIT：当前状态不允许执行Release操作。
 * AV_ERR_IO：IO访问相关的错误。
 * AV_ERR_SERVICE_DIED：媒体服务已停止。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_Release(OH_AVTranscoder *transcoder);

/**
 * @brief 注册触发转码状态修改事件的回调方法。
 * 当触发状态修改事件时，通过注册的回调方法通知开发者。
 * 开发者只能注册一个状态修改事件的回调方法，当开发者重复注册时，以最后一次注册的回调接口为准。
 * 若开发者需监听转码状态修改，须在{@link OH_AVTranscoder_Prepare}之前注册转码状态回调。
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @param callback State callback function, see {@link OH_AVTranscoder_OnStateChange}
 * @param userData Pointer to user specific data
 * @return AV_ERR_OK：注册成功。
 * AV_ERR_INVALID_VAL：输入的transcoder是空指针，或者callback是空指针。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_SetStateCallback(
    OH_AVTranscoder *transcoder, OH_AVTranscoder_OnStateChange callback, void *userData);

/**
 * @brief 注册触发转码错误事件的回调方法。
 * 当触发错误事件时，通过注册的回调方法通知开发者。
 * 如果AVTranscoder上报error事件，开发者需要通过{@link OH_AVTranscoder_Release}操作退出转码操作。
 * 开发者只能注册一个错误事件的回调方法，当开发者重复注册时，以最后一次注册的回调接口为准。
 * 若开发者需监听转码错误事件，须在{@link OH_AVTranscoder_Prepare}之前注册转码错误事件。
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @param callback Error callback function, see {@link OH_AVTranscoder_OnError}
 * @param userData Pointer to user specific data
 * @return AV_ERR_OK：注册成功。
 * AV_ERR_INVALID_VAL：输入的transcoder是空指针，或者callback是空指针。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_SetErrorCallback(
    OH_AVTranscoder *transcoder, OH_AVTranscoder_OnError callback, void *userData);

/**
 * @brief 注册触发转码进度更新事件的回调方法。
 * 当触发转码进度更新事件时，通过注册的回调方法通知开发者。
 * 开发者只能注册一个错误事件的回调方法，当开发者重复注册时，以最后一次注册的回调接口为准。
 * 若开发者需监听转码处理进度，则须在{@link OH_AVTranscoder_Prepare}之前注册该事件。
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @param callback Uri callback function,
 * see {@link OH_AVTranscoder_OnProgressUpdate}
 * @param userData Pointer to user specific data
 * @return AV_ERR_OK：注册成功。
 * AV_ERR_INVALID_VAL：输入的transcoder是空指针，或者callback是空指针。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_SetProgressUpdateCallback(
    OH_AVTranscoder *transcoder, OH_AVTranscoder_OnProgressUpdate callback, void *userData);

/**
 * @brief 转码设置输出视频B帧编码。
 * B帧视频编码相关的约束和限制可以参考文档{@link B帧视频编码约束和限制}。
 * 如果当前不符合B帧视频编码的约束和限制，将忽略B帧，按不使能B帧进行编码。
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param enabled Whether enable B Frame. If this function is not called, B Frame is disabled.
 * @return AV_ERR_OK：设置成功。
 * AV_ERR_INVALID_VAL：输入的config为空指针。
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_EnableBFrame(OH_AVTranscoder_Config *config, bool enabled);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_AVTRANSCODER_H


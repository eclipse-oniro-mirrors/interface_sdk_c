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
 * @addtogroup AVMuxer
 * @{
 *
 * @brief AVMuxer模块提供用于音视频封装功能的函数。
 *
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @since 10
 */


/**
 * @file native_avmuxer.h
 *
 * @brief 声明用于音视频封装的Native API。
 * @sample [AVCodec](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/BasicFeature/Media/AVCodec)
 *
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avmuxer.h>
 * @library libnative_media_avmuxer.so
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @since 10
 */
 
#ifndef NATIVE_AVMUXER_H
#define NATIVE_AVMUXER_H

#include <stdint.h>
#include <stdio.h>
#include "native_avcodec_base.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 定义封装接口native层对象类型。
 * @since 10
 */
typedef struct OH_AVMuxer OH_AVMuxer;

/**
 * @brief 通过文件描述符fd和封装格式创建OH_AVMuxer实例。
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @param fd 用读写方式打开（O_RDWR），由调用者关闭该fd。
 * @param format 封装输出的文件格式。
 * @return 返回一个指向OH_AVMuxer实例的指针，需要调用{@link OH_AVMuxer_Destroy}销毁。
 * @since 10
 */
OH_AVMuxer *OH_AVMuxer_Create(int32_t fd, OH_AVOutputFormat format);

/**
 * @brief 设置视频的旋转角度（顺时针，且旋转角度必须为0、90、180或270）。该接口必须在{@link OH_AVMuxer_Start}前调用。
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @param muxer 指向OH_AVMuxer实例的指针。
 * @param rotation 角度，必须为0、90、180 或 270。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：muxer为空指针，或rotation无效。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许调用该接口，请检查接口调用顺序。
 * @since 10
 */
OH_AVErrCode OH_AVMuxer_SetRotation(OH_AVMuxer *muxer, int32_t rotation);

/**
 * @brief 设置format数据到封装器。\n
 * API 14起，支持设置创建时间OH_MD_KEY_CREATION_TIME。若创建时间未写入成功，请排查OH_MD_KEY_CREATION_TIME字符串设置是否符合ISO 8601标准的时间格式且为UTC时间。\n
 * API 20起，支持：\n
 * - 设置文件的描述性文本信息OH_MD_KEY_COMMENT。若文件描述信息未写入成功，请排查OH_MD_KEY_COMMENT是否为字符串类型或字符长度大于等于1且小于等于256。\n
 * - 设置MP4 moov的位置OH_MD_KEY_ENABLE_MOOV_FRONT。OH_MD_KEY_ENABLE_MOOV_FRONT为0时moov后置，为1时前置，默认后置。
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @param muxer 指向OH_AVMuxer实例的指针。
 * @param format 指向OH_AVFormat实例的指针。文件级元数据集。
 * @return AV_ERR_OK：设置format参数正确。\n
 *         AV_ERR_INVALID_VAL：muxer为空指针，或format无效。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许调用该接口，请检查接口调用顺序。
 * @since 14
 */
OH_AVErrCode OH_AVMuxer_SetFormat(OH_AVMuxer *muxer, OH_AVFormat *format);

/**
 * @brief 向封装器添加音视频轨。每调用一次本接口可以在封装器中添加一个音视频轨。该接口必须在{@link OH_AVMuxer_Start}前调用。
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @param muxer 指向OH_AVMuxer实例的指针。
 * @param trackIndex 用于获取该轨的索引，该值在{@link OH_AVMuxer_WriteSample}接口中使用。
 * 如果媒体轨添加成功，该值大于或等于0，否则小于0。
 * @param trackFormat 指向OH_AVFormat实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：muxer为空指针，或trackIndex无效，或trackFormat无效。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许调用该接口，请检查接口调用顺序。\n
 *         AV_ERR_UNSUPPORT：不支持的mime类型。\n
 *         AV_ERR_NO_MEMORY：申请内存失败。\n
 *         AV_ERR_UNKNOWN：未知错误。
 * @since 10
 */
OH_AVErrCode OH_AVMuxer_AddTrack(OH_AVMuxer *muxer, int32_t *trackIndex, OH_AVFormat *trackFormat);

/**
 * @brief 开始封装。
 * 该接口必须在{@link OH_AVMuxer_AddTrack}后，{@link OH_AVMuxer_WriteSample}前调用。
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @param muxer 指向OH_AVMuxer实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：muxer为空指针。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许调用该接口，请检查接口调用顺序。\n
 *         AV_ERR_UNKNOWN：未知错误。
 * @since 10
 */
OH_AVErrCode OH_AVMuxer_Start(OH_AVMuxer *muxer);

/**
 * @brief 将sample写入封装器。 
 * 该接口必须在{@link OH_AVMuxer_Start}后，{@link OH_AVMuxer_Stop}前调用。
 * 调用者需要按info中的时间顺序将sample写入正确的音视频轨。
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @param muxer 指向OH_AVMuxer实例的指针。
 * @param trackIndex 数据对应的音视频轨的索引。 
 * @param sample 编码或解封装得到的数据。
 * @param info sample对应的描述信息。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：muxer为空指针，或trackIndex无效，或sample无效，或info无效。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许调用该接口，请检查接口调用顺序。\n
 *         AV_ERR_NO_MEMORY：申请内存失败。\n
 *         AV_ERR_UNKNOWN：未知错误。
 * @deprecated since 11
 * @useinstead {@link OH_AVMuxer_WriteSampleBuffer}
 * @since 10
 */
OH_AVErrCode OH_AVMuxer_WriteSample(OH_AVMuxer *muxer, uint32_t trackIndex, OH_AVMemory *sample, OH_AVCodecBufferAttr info);

/**
 * @brief 将sample写入封装器。
 * 该接口必须在{@link OH_AVMuxer_Start}后，{@link OH_AVMuxer_Stop}前调用。
 * 调用者需要按sample中的时间顺序将sample写入正确的音视频轨。
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @param muxer 指向OH_AVMuxer实例的指针。
 * @param trackIndex 数据对应的音视频轨的索引。
 * @param sample 编码或解封装得到的数据及属性。
 * @return AV_ERR_OK：执行成功。
 *         AV_ERR_INVALID_VAL：muxer为空指针，或trackIndex无效，或sample无效。
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许调用该接口，请检查接口调用顺序。
 *         AV_ERR_NO_MEMORY：申请内存失败。
 *         AV_ERR_UNKNOWN：未知错误。
 * @since 11
 */
OH_AVErrCode OH_AVMuxer_WriteSampleBuffer(OH_AVMuxer *muxer, uint32_t trackIndex, const OH_AVBuffer *sample);

/**
 * @brief 停止封装。封装器停止后不支持重新开始。
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @param muxer 指向OH_AVMuxer实例的指针。
 * @return AV_ERR_OK：执行成功。
 *         AV_ERR_INVALID_VAL：muxer为空指针。
 *         AV_ERR_OPERATE_NOT_PERMIT：不允许调用该接口，请检查接口调用顺序。
 * @since 10
 */
OH_AVErrCode OH_AVMuxer_Stop(OH_AVMuxer *muxer);

/**
 * @brief 清理内部资源，销毁OH_AVMuxer实例。\n
 * 注意不能重复销毁，否则会导致程序崩溃。
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @param muxer 指向OH_AVMuxer实例的指针。
 * @return AV_ERR_OK：执行成功。
 *         AV_ERR_INVALID_VAL：muxer为空指针。
 * @since 10
 */
OH_AVErrCode OH_AVMuxer_Destroy(OH_AVMuxer *muxer);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVMUXER_H

/** @} */
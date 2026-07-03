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
 * @addtogroup AVDemuxer
 * @{
 *
 * @brief AVDemuxer模块提供从媒体文件码流中提取sample的接口。
 * 
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @since 10
 */


/**
 * @file native_avdemuxer.h
 *
 * @brief 声明用于音视频媒体数据解析的接口。
 * @sample [AVCodec](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/BasicFeature/Media/AVCodec)
 * 
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avdemuxer.h>
 * @library libnative_media_avdemuxer.so
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @since 10
 */

#ifndef NATIVE_AVDEMUXER_H
#define NATIVE_AVDEMUXER_H

#include <stdint.h>
#include "native_avcodec_base.h"
#include "native_avsource.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 为OH_AVDemuxer接口定义native层对象。
 *
 * @since 10
 */
typedef struct OH_AVDemuxer OH_AVDemuxer;
/**
 * @brief 为DRM_MediaKeySystemInfo接口定义native层对象。
 *
 * @since 11
 */
typedef struct DRM_MediaKeySystemInfo DRM_MediaKeySystemInfo;

/**
 * @brief DRM_MediaKeySystemInfo回调函数指针类型，不返回解封装器实例，适用于单个解封装器实例场景。\n
 * 需要使用{@link OH_AVDemuxer_SetMediaKeySystemInfoCallback}接口将其设置为回调。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @deprecated since 14
 * @useinstead {@link Demuxer_MediaKeySystemInfoCallback}
 * @since 11
*/
typedef void (*DRM_MediaKeySystemInfoCallback)(DRM_MediaKeySystemInfo* mediaKeySystemInfo);

/**
 * @brief DRM_MediaKeySystemInfo回调函数指针类型，返回解封装器实例，适用于多个解封装器实例场景。\n
 * 需要使用{@link OH_AVDemuxer_SetDemuxerMediaKeySystemInfoCallback}接口将其设置为回调，推荐使用。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @since 12
*/
typedef void (*Demuxer_MediaKeySystemInfoCallback)(OH_AVDemuxer *demuxer, DRM_MediaKeySystemInfo *mediaKeySystemInfo);

/**
 * @brief 通过source实例创建OH_AVDemuxer实例。\n
 * source的创建、销毁及使用，详情请参考{@link OH_AVSource}。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param source 指向OH_AVSource实例的指针。
 * @return 返回一个指向OH_AVDemuxer实例的指针。\n
 * 如果执行成功，则返回指向OH_AVDemuxer实例的指针，否则返回NULL。\n
 * 可能的失败原因：\n
 * 1. source无效，即空指针或非OH_AVSource实例。\n
 * 2. 非OH_AVSource实例。
 * @since 10
*/
OH_AVDemuxer *OH_AVDemuxer_CreateWithSource(OH_AVSource *source);

/**
 * @brief 销毁OH_AVDemuxer实例并清理内部资源。同一实例只能被销毁一次。\n
 * 注意，销毁的实例在被重新创建之前不能再被使用。建议实例销毁成功后将指针置为NULL。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param demuxer 指向OH_AVDemuxer实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：当输入的demuxer指针为空或非解封装器实例。
 * @since 10
*/
OH_AVErrCode OH_AVDemuxer_Destroy(OH_AVDemuxer *demuxer);

/**
 * @brief 指定读取sample的轨道，解封装器将会从该轨道中读取数据，未指定的轨道不会读取。\n
 * 注意，通过多次调用接口并传入不同轨道的索引来选中多个轨道。\n
 * 调用{@link OH_AVDemuxer_ReadSample}时只会读取被选中的轨道中数据，同一轨道被选择多次时，接口会返回AV_ERR_OK，并且只会生效一次。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param demuxer 指向OH_AVDemuxer实例的指针。
 * @param trackIndex 需选择的轨道的索引。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：\n
 *                           1. 输入的demuxer指针为空或为非解封装器实例。\n
 *                           2. 轨道的索引超出范围。\n
 *                           3. 不支持读取轨道。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：demuxer没有正确的初始化。
 * @since 10
*/
OH_AVErrCode OH_AVDemuxer_SelectTrackByID(OH_AVDemuxer *demuxer, uint32_t trackIndex);

/**
 * @brief 移除读取sample的轨道，未选中的轨道的数据不会被解封装器读取。\n
 * 注意，通过多次调用接口并传入不同轨道的索引来取消对多个轨道的选择。\n
 * 同一轨道被多次取消选择时，接口会返回AV_ERR_OK，并且只会生效一次。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param demuxer 指向OH_AVDemuxer实例的指针。
 * @param trackIndex 需取消选择的轨道的索引。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：输入的demuxer指针为空或为非解封装器实例。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：demuxer没有正确的初始化。
 * @since 10
*/
OH_AVErrCode OH_AVDemuxer_UnselectTrackByID(OH_AVDemuxer *demuxer, uint32_t trackIndex);

/**
 * @brief  获取指定轨道的sample及相关信息。\n
 * 注意，读取轨道sample前，轨道必须被选中。调用接口后解封装器将自动前进到下一帧。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param demuxer 指向OH_AVDemuxer实例的指针。
 * @param trackIndex 本次读取压缩帧的轨道的索引。
 * @param sample 指向OH_AVMemory实例的指针，用于储存压缩帧数据。
 * @param info 指向OH_AVCodecBufferAttr实例的指针，用于储存压缩帧的相关信息。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：\n
 *                           1. 输入的demuxer指针为空或为非解封装器实例。\n
 *                           2. 轨道的索引超出范围。\n
 *                           3. 不支持读取轨道。\n
 *                           4. 输入sample为空。\n
 *                           5. 输入info为空。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：\n
 *                           1. 轨道的索引没有被选中。\n
 *                           2. demuxer没有正确的初始化。\n
 *         AV_ERR_NO_MEMORY：sample容量不足以存储所有帧数据。\n
 *         AV_ERR_UNKNOWN：无法从文件中读取或解析帧。
 * @deprecated since 11
 * @useinstead {@link OH_AVDemuxer_ReadSampleBuffer}
 * @since 10
*/
OH_AVErrCode OH_AVDemuxer_ReadSample(OH_AVDemuxer *demuxer, uint32_t trackIndex,
    OH_AVMemory *sample, OH_AVCodecBufferAttr *info);

/**
 * @brief 获取指定轨道的sample及相关信息。\n
 * 注意，读取轨道sample前，轨道必须被选中。调用接口后解封装器将自动前进到下一帧。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param demuxer 指向OH_AVDemuxer实例的指针。
 * @param trackIndex 本次读取压缩帧的轨道的索引。
 * @param sample 指向OH_AVBuffer实例的指针，用于储存压缩帧数据以及相关信息。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：\n
 *                           1. 输入的demuxer指针为空或为非解封装器实例。\n
 *                           2. sample为空指针。\n
 *                           3. 轨道的索引超出范围。\n
 *                           4. 输入sample为空。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：\n
 *                           1. 轨道的索引没有被选中。\n
 *                           2. demuxer没有正确的初始化。\n
 *         AV_ERR_NO_MEMORY：sample容量不足以存储所有帧数据。\n
 *         AV_ERR_UNKNOWN：无法从文件中读取或解析帧。
 * @since 11
*/
OH_AVErrCode OH_AVDemuxer_ReadSampleBuffer(OH_AVDemuxer *demuxer, uint32_t trackIndex,
    OH_AVBuffer *sample);

/**
 * @brief 根据设定的跳转模式，将所有选中的轨道到指定时间附近。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param demuxer 指向OH_AVDemuxer实例的指针。
 * @param millisecond 期望跳转位置对应的时间，单位为ms，该时间戳是相对文件开始的位置。
 * @param mode 跳转的模式。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：\n
 *                           1. 输入的demuxer指针为空或为非解封装器实例。\n
 *                           2. 毫秒值超出范围。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：\n
 *                           1. 轨道的索引没有被选中。\n
 *                           2. demuxer没有正确的初始化。\n
 *                           3. 资源无法seek。\n
 *         AV_ERR_UNKNOWN：\n
 *                           1. seek失败。\n
 *                           2. OH_AVSeekMode选择SEEK_MODE_NEXT_SYNC，并且时间点后无I帧，可能会跳转失败。
 * @since 10
*/
OH_AVErrCode OH_AVDemuxer_SeekToTime(OH_AVDemuxer *demuxer, int64_t millisecond, OH_AVSeekMode mode);

/**
 * @brief  设置DRM信息回调函数。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @deprecated since 14
 * @useinstead {@link OH_AVDemuxer_SetDemuxerMediaKeySystemInfoCallback}
 * @param demuxer 指向OH_AVDemuxer实例的指针。
 * @param callback 回调函数。
 * @return AV_ERR_OK：操作成功。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：demuxer没有正确的初始化。\n
 *         AV_ERR_INVALID_VAL：输入的demuxer指针为空或为非解封装器实例。
 * @since 11
 * @version 1.0
 */
OH_AVErrCode OH_AVDemuxer_SetMediaKeySystemInfoCallback(OH_AVDemuxer *demuxer,
    DRM_MediaKeySystemInfoCallback callback);

/**
 * @brief 设置DRM信息回调函数。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param demuxer 指向OH_AVDemuxer实例的指针。
 * @param callback 回调函数。
 * @return AV_ERR_OK：操作成功。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：demuxer没有正确的初始化。\n
 *         AV_ERR_INVALID_VAL：输入的demuxer指针为空或为非解封装器实例。
 * @since 12
 * @version 1.0
 */
OH_AVErrCode OH_AVDemuxer_SetDemuxerMediaKeySystemInfoCallback(OH_AVDemuxer *demuxer,
    Demuxer_MediaKeySystemInfoCallback callback);

/**
 * @brief 获取DRM信息。在{@link Demuxer_MediaKeySystemInfoCallback}或{@link DRM_MediaKeySystemInfoCallback}接口成功回调以后，
 * 调用此接口才能获取到DRM信息。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param demuxer 指向OH_AVDemuxer实例的指针。
 * @param mediaKeySystemInfo 指向DRM信息的指针。
 * @return AV_ERR_OK：操作成功。\n
 *         AV_ERR_OPERATE_NOT_PERMIT：解封装引擎未初始化或初始化失败。\n
 *         AV_ERR_INVALID_VAL：\n
 *                           1. 输入的demuxer指针为空或为非解封装器实例。\n
 *                           2. mediaKeySystemInfo为nullptr。
 * @since 11
 * @version 1.0
 */
OH_AVErrCode OH_AVDemuxer_GetMediaKeySystemInfo(OH_AVDemuxer *demuxer, DRM_MediaKeySystemInfo *mediaKeySystemInfo);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVDEMUXER_H

/** @} */
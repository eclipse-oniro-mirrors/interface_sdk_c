/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup AVMetadataExtractor
 * @{
 *
 * @brief Provides APIs of metadata capability for Media Source.
 *
 * @syscap SystemCapability.Multimedia.Media.AVMetadataExtractor
 * @since 18
 */
/**
 * @file avmetadata_extractor.h
 *
 * @brief 定义AVMetadataExtractor接口。使用其Native API从媒体资源中获取元数据。
 * 
 * @kit MediaKit
 * @library libavmetadata_extractor.so
 * @since 18
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETADATA_EXTRACTOR_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETADATA_EXTRACTOR_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "native_averrors.h"
#include "avmetadata_extractor_base.h"
#include "native_avcodec_base.h"
#include "native_avformat.h"
#include "multimedia/image_framework/image/pixelmap_native.h"
#include "avmedia_source.h"
#include "avmedia_base.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief 定义OH_AVMetadataExtractor类型。
 * 
 * @since 18
 */
typedef struct OH_AVMetadataExtractor OH_AVMetadataExtractor;

/**
 * @brief 从媒体源中获取指定索引的轨道描述信息。该函数必须在设置资源之后使用。
 * 
 * @param extractor 指向OH_AVMetadataExtractor实例的指针。
 * @param index 要获取的轨道描述的索引。
 * @return 成功时返回包含轨道描述信息的OH_AVFormat实例指针，失败时返回空指针。
 * 可能失败的原因：
 * 1. extractor为空指针。
 * 2. 未设置媒体源。
 * 3. 格式不支持。
 * 注意：用户需要使用{@link OH_AVFormat_Destroy}在使用OH_AVFormat后将其释放。
 * @since 23
 */
OH_AVFormat *OH_AVMetadataExtractor_GetTrackDescription(OH_AVMetadataExtractor *extractor, uint32_t index);

/**
 * @brief 从媒体源中获取自定义元数据信息。该函数必须在设置资源之后使用。
 * 
 * @param extractor 指向OH_AVMetadataExtractor实例的指针。
 * @return 成功时返回包含自定义元数据的OH_AVFormat实例指针，失败时返回空指针。
 * 可能失败的原因：
 * 1. extractor为空指针。
 * 2. 未设置媒体源。
 * 3. 未找到自定义信息。
 * 注意：用户需要使用{@link OH_AVFormat_Destroy}在使用OH_AVFormat后将其释放。
 * @since 23
 */
OH_AVFormat *OH_AVMetadataExtractor_GetCustomInfo(OH_AVMetadataExtractor *extractor);

/**
 * @brief 为提取器设置媒体源。
 * 
 * @param extractor 指向OH_AVMetadataExtractor实例的指针。
 * @param source 要设置的媒体源。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：输入的extractor为空指针或输入的source无效。
 * @since 23
 */
OH_AVErrCode OH_AVMetadataExtractor_SetMediaSource(OH_AVMetadataExtractor *extractor, OH_AVMediaSource *source);

/**
 * @brief 创建OH_AVMetadataExtractor实例。
 * 
 * @return 创建成功时返回指向OH_AVMetadataExtractor实例的指针，否则返回空指针。
 * 可能的失败原因：HstEngineFactory::CreateAVMetadataHelperEngine执行失败。
 * @since 18
 */
OH_AVMetadataExtractor* OH_AVMetadataExtractor_Create(void);

/**
 * @brief 通过媒体文件描述符设置数据源。
 * 
 * @param extractor 指向OH_AVMetadataExtractor实例的指针。
 * @param fd 媒体源的文件描述符。
 * @param offset 媒体源在文件描述符中的偏移量。
 * @param size 媒体源的大小。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL： 输入的extractor为空指针或参数无效。
 * AV_ERR_OPERATE_NOT_PERMIT：操作被禁止。
 * AV_ERR_NO_MEMORY：内部内存分配失败。
 * @since 18
 */
OH_AVErrCode OH_AVMetadataExtractor_SetFDSource(OH_AVMetadataExtractor* extractor,
    int32_t fd, int64_t offset, int64_t size);

/**
 * @brief 从媒体资源中获取元数据。
 * 此函数必须在{@link OH_AVMetadataExtractor_SetFDSource}之后调用。
 * 
 * @param extractor 指向OH_AVMetadataExtractor实例的指针。
 * @param avMetadata 指向OH_AVFormat实例的指针，其内容包含获取的元数据信息。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL： 输入的extractor为空指针或参数无效。
 * AV_ERR_OPERATE_NOT_PERMIT：操作被禁止。
 * AV_ERR_UNSUPPORTED_FORMAT：格式不支持。
 * AV_ERR_NO_MEMORY：内部内存分配失败。
 * AV_ERR_IO_CLEARTEXT_NOT_PERMITTED：（API version 23新增）不允许HTTP明文流量。
 * @since 18
 */
OH_AVErrCode OH_AVMetadataExtractor_FetchMetadata(OH_AVMetadataExtractor* extractor, OH_AVFormat* avMetadata);

/**
 * @brief 获取音频专辑封面。
 * 此函数必须在{@link OH_AVMetadataExtractor_SetFDSource}之后调用。
 * 
 * @param extractor 指向OH_AVMetadataExtractor实例的指针。
 * @param pixelMap 从音频源获取的专辑封面。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL： 输入的extractor为空指针或参数无效。
 * AV_ERR_OPERATE_NOT_PERMIT：操作被禁止。
 * AV_ERR_UNSUPPORTED_FORMAT：格式不支持。
 * AV_ERR_NO_MEMORY：内部内存分配失败。
 * @since 18
 */
OH_AVErrCode OH_AVMetadataExtractor_FetchAlbumCover(OH_AVMetadataExtractor* extractor, OH_PixelmapNative** pixelMap);

/**
 * @brief 从视频源中提取指定时间点的图像。该函数必须在设置资源之后使用。
 * 
 * @param extractor 指向OH_AVMetadataExtractor实例的指针。
 * @param timeUs 要从视频资源中提取图像的时间位置（单位：微秒）。
 * @param seekMode 定义指定时间与关键帧之间关系的跳转模式。详见{@link OH_AVMedia_SeekMode}。
 * @param outputParam 图像的输出参数，例如图像的高度或者宽度。详见{@link OH_AVMetadataExtractor_OutputParam}。若为空指针，使用视频的原始尺寸。注意：用户需要使用{@link OH_PixelmapNative_Destroy}
 * 在使用pixelMap后将其释放。
 * @param pixelMap 用于接收从视频源提取的图像，详见{@link OH_PixelmapNative}。
 * @return 函数执行结果。
 * AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入参数无效。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不允许。
 * AV_ERR_UNSUPPORTED_FORMAT：格式不支持。
 * AV_ERR_SERVICE_DIED：服务已终止。
 * AV_ERR_IO_CLEARTEXT_NOT_PERMITTED：不允许HTTP明文流量。
 * @since 23
 */
OH_AVErrCode OH_AVMetadataExtractor_FetchFrameByTime(OH_AVMetadataExtractor *extractor, int64_t timeUs,
    OH_AVMedia_SeekMode seekMode, const OH_AVMetadataExtractor_OutputParam* outputParam,
    OH_PixelmapNative** pixelMap);

/**
 * @brief 定义用于获取AVMetadataExtractor捕获帧的回调函数。注意：frameInfo会在回调后自动释放，但用户需要使用{@link OH_PixelmapNative_Destroy}手动释放frameInfo.
 * image，避免内存泄漏。
 * 
 * @since 23
 */
typedef void (*OH_AVMetadataExtractor_OnFrameFetched)(OH_AVMetadataExtractor *extractor,
    const OH_AVMetadataExtractor_FrameInfo* frameInfo, OH_AVErrCode code, void *userData);

/**
 * @brief 从视频源中异步提取多个指定时间点的图像。该函数必须在设置资源之后使用。
 * 
 * @param extractor 指向OH_AVMetadataExtractor实例的指针。
 * @param timesUs The times array expected to fetch picture from the video resource. The unit is microsecond(us).
 * @param timesUsSize 输入时间点数组的长度。
 * @param seekMode 定义每个给定时间与关键帧之间关系的跳转选项，详见{@link OH_AVMedia_SeekMode}。
 * @param outputParam 图像的输出参数，例如图像的高度或者宽度。详见{@link OH_AVMetadataExtractor_OutputParam}。若该参数为空指针，则获取的帧使用视频原始尺寸。
 * @param onFrameInfoCallback 每帧提取完成或提取失败后调用的回调函数。
 * @param userData 传递给回调函数的用户自定义数据指针。
 * @return 函数执行结果。
 * AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入参数无效。
 * AV_ERR_SERVICE_DIED：服务已终止。
 * AV_ERR_IO_CLEARTEXT_NOT_PERMITTED：不允许HTTP明文流量。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不允许。由onFrameInfoCallback返回。
 * AV_ERR_UNSUPPORTED_FORMAT：格式不支持。由onFrameInfoCallback返回。
 * AV_ERR_TIMEOUT：执行超时。由onFrameInfoCallback返回。
 * @since 23
 */
OH_AVErrCode OH_AVMetadataExtractor_FetchFramesByTimes(OH_AVMetadataExtractor *extractor, int64_t timesUs[], uint16_t timesUsSize,
    OH_AVMedia_SeekMode seekMode, const OH_AVMetadataExtractor_OutputParam* outputParam,
    OH_AVMetadataExtractor_OnFrameFetched onFrameInfoCallback, void* userData);

/**
 * @brief 取消所有由{@link OH_AVMetadataExtractor_FetchFramesByTimes}发起的批量获取图像操作。在{@link OH_AVMetadataExtractor_OnFrameFetched}
 * 回调中，挂起的获取操作被取消，并标记结果为已取消。
 *  
 * @param extractor 指向OH_AVMetadataExtractor实例的指针。
 * @since 23
 */
void OH_AVMetadataExtractor_CancelAllFetchFrames(OH_AVMetadataExtractor *extractor);

/**
 * @brief 释放用于OH_AVMetadataExtractor的资源并销毁OH_AVMetadataExtractor实例。
 * 
 * @param extractor 指向OH_AVMetadataExtractor实例指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL： 输入的extractor为空指针或参数无效。
 * @since 18
 */
OH_AVErrCode OH_AVMetadataExtractor_Release(OH_AVMetadataExtractor* extractor);

/**
 * @brief 创建OH_AVMetadataExtractor_OutputParam实例。
 * 
 * @return 返回指向OH_AVMetadataExtractor_OutputParam实例的指针。
 * @since 23
 */
OH_AVMetadataExtractor_OutputParam* OH_AVMetadataExtractor_OutputParam_Create();

/**
 * @brief 释放OH_AVMetadataExtractor_OutputParam实例。
 * 
 * @param outputParam 指向OH_AVMetadataExtractor_OutputParam实例的指针。
 * @since 23
 */
void OH_AVMetadataExtractor_OutputParam_Destroy(OH_AVMetadataExtractor_OutputParam* outputParam);

/**
 * @brief 设置OH_AVMetadataExtractor_OutputParam实例的期望输出尺寸。若width或height小于0，则使用原始宽度或高度。若width或height等于0，则保持宽高比按比例缩放。
 * 若width和height均大于0，则使用输入的width和height参数缩放图像。
 * 
 * @param outputParam 指向OH_AVMetadataExtractor_OutputParam实例的指针。
 * @param width 输出图像的期望宽度，如有必要可进行缩放。
 * @param height 输出图像的期望高度，如有必要可进行缩放。
 * @return 成功返回true，失败返回false。
 * 可能失败的原因：outputParam为空指针。
 * @since 23
 */
bool OH_AVMetadataExtractor_OutputParam_SetSize(OH_AVMetadataExtractor_OutputParam* outputParam,
    int32_t width, int32_t height);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETADATA_EXTRACTOR_H
/** @} */

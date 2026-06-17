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
 * @addtogroup AVImageGenerator
 * @{
 *
 * @brief Provides APIs for generating an image at a specific time from a video resource.
 *
 * @syscap SystemCapability.Multimedia.Media.AVImageGenerator
 * @since 18
 */
/**
 * @file avimage_generator.h
 *
 * @brief 定义AVImageGenerator接口。使用其C API从视频资源中获取指定时间点视频帧。
 * 
 * @kit MediaKit
 * @library libavimage_generator.so
 * @since 18
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVIMAGE_GENERATOR_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVIMAGE_GENERATOR_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "native_averrors.h"
#include "avimage_generator_base.h"
#include "multimedia/image_framework/image/pixelmap_native.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义OH_AVImageGenerator类型，用于生成指定时间点视频帧。
 * 
 * @since 18
 */
typedef struct OH_AVImageGenerator OH_AVImageGenerator;

/**
 * @brief 创建OH_AVImageGenerator实例，用于生成指定时间点视频帧。
 * 
 * @return 创建成功时返回指向OH_AVImageGenerator实例的指针，否则返回空指针。
 * 可能的失败原因：HstEngineFactory未能创建AVMetadataHelperEngine。
 * @since 18
 */
OH_AVImageGenerator* OH_AVImageGenerator_Create(void);

/**
 * @brief 通过媒体文件描述符设置数据源。
 * 
 * @param generator 指向OH_AVImageGenerator实例的指针。
 * @param fd 媒体源的文件描述符。
 * @param offset 媒体源在文件描述符中的偏移量。
 * @param size 媒体源的大小。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的generator为空指针或参数无效。
 * AV_ERR_OPERATE_NOT_PERMIT：操作被禁止。
 * AV_ERR_NO_MEMORY：内部内存分配失败。
 * @since 18
 */
OH_AVErrCode OH_AVImageGenerator_SetFDSource(OH_AVImageGenerator* generator,
    int32_t fd, int64_t offset, int64_t size);

/**
 * @brief 从视频资源中获取指定时间点视频帧。
 * 
 * @param generator 指向OH_AVImageGenerator实例的指针。
 * @param timeUs 需要获取的视频帧在视频中的时间点，单位为微秒（μs）。
 * @param options 关于给定时间Us和视频帧之间关系的时间选项。
 * @param pixelMap 获取的视频帧对象。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的generator为空指针或参数无效。
 * AV_ERR_OPERATE_NOT_PERMIT：操作被禁止。
 * AV_ERR_UNSUPPORTED_FORMAT：格式不支持。
 * AV_ERR_NO_MEMORY：内部内存分配失败。
 * @since 18
 */
OH_AVErrCode OH_AVImageGenerator_FetchFrameByTime(OH_AVImageGenerator* generator,
    int64_t timeUs, OH_AVImageGenerator_QueryOptions options, OH_PixelmapNative** pixelMap);

/**
 * @brief 释放用于OH_AVImageGenerator的资源以及销毁OH_AVImageGenerator实例。
 * 
 * @param generator 指向OH_AVImageGenerator实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的generator为空指针或参数无效。
 * @since 18
 */
OH_AVErrCode OH_AVImageGenerator_Release(OH_AVImageGenerator* generator);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVIMAGE_GENERATOR_H
/** @} */

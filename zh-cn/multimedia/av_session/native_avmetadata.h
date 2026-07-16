/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
 * @addtogroup OHAVSession
 * @{
 *
 * @brief 提供媒体会话模块C接口定义。
 *
 * @syscap SystemCapability.Multimedia.AVSession.Core
 *
 * @since 13
 * @version 1.0
 */

/**
 * @file native_avmetadata.h
 *
 * @brief 提供播控元数据的定义。
 *
 * @library libohavsession.so
 * @syscap SystemCapability.Multimedia.AVSession.Core
 * @kit AVSessionKit
 * @since 13
 * @version 1.0
 */

#ifndef NATIVE_AVMETADATA_H
#define NATIVE_AVMETADATA_H

#include <stdint.h>
#include "native_avsession_errors.h"
#include "native_avsession_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 会话元数据构造器。
 * 用于构造会话元数据。
 *
 * @since 13
 * @version 1.0
 */
typedef struct OH_AVMetadataBuilderStruct OH_AVMetadataBuilder;

/**
 * @brief 会话元数据。
 * 用于存储媒体资源元数据的结构体定义。
 *
 * @since 13
 * @version 1.0
 */
typedef struct OH_AVMetadataStruct OH_AVMetadata;

/**
 * @brief 创建一个元数据构造器。
 *
 * @param builder 指向创建的构造器实例。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：参数builder为nullptr。\n
 *         AVMETADATA_ERROR_NO_MEMORY：内存不足。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_Create(OH_AVMetadataBuilder** builder);

/**
 * @brief 销毁元数据构造器。
 *
 * @param builder 指向元数据构造器的实例。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：参数builder为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_Destroy(OH_AVMetadataBuilder* builder);

/**
 * @brief 设置当前媒体资源ID。
 *
 * @param builder 指向元数据构造器的实例。
 * @param assetId 资源ID。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数assetId为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetAssetId(OH_AVMetadataBuilder* builder, const char* assetId);

/**
 * @brief 设置资源标题。
 *
 * @param builder 指向元数据构造器的实例。
 * @param title 标题。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数title为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetTitle(OH_AVMetadataBuilder* builder, const char* title);

/**
 * @brief 设置资源所属的艺术家信息。
 *
 * @param builder 指向元数据构造器的实例。
 * @param artist 媒体资源的艺术家。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数artist为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetArtist(OH_AVMetadataBuilder* builder, const char* artist);

/**
 * @brief 设置资源的作者。
 *
 * @param builder 指向元数据构造器的实例。
 * @param author 作者。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数author为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetAuthor(OH_AVMetadataBuilder* builder, const char* author);

/**
 * @brief 设置资源专辑名称。
 *
 * @param builder 指向元数据构造器的实例。
 * @param album 专辑名。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数album为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetAlbum(OH_AVMetadataBuilder* builder, const char* album);

/**
 * @brief 设置资源词作者。
 *
 * @param builder 指向元数据构造器的实例。
 * @param writer 词作者。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数writer为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetWriter(OH_AVMetadataBuilder* builder, const char* writer);

/**
 * @brief 设置资源作曲者。
 *
 * @param builder 指向元数据构造器的实例。
 * @param composer 作曲者。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数composer为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetComposer(OH_AVMetadataBuilder* builder, const char* composer);

/**
 * @brief 设置资源播放时长。
 *
 * @param builder 指向元数据构造器的实例。
 * @param duration 资源播放时长，以ms为单位。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：参数builder为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetDuration(OH_AVMetadataBuilder* builder, int64_t duration);

/**
 * @brief 设置媒体图片的URI地址。
 *
 * @param builder 指向元数据构造器的实例。
 * @param mediaImageUri 媒体图片的URI地址。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数mediaImageUri为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetMediaImageUri(OH_AVMetadataBuilder* builder, const char* mediaImageUri);

/**
 * @brief 设置副标题。
 *
 * @param builder 指向元数据构造器的实例。
 * @param subtitle 副标题名称。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数subtitle为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetSubtitle(OH_AVMetadataBuilder* builder, const char* subtitle);

/**
 * @brief 设置媒体描述信息。
 *
 * @param builder 指向元数据构造器的实例。
 * @param description 媒体描述信息。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数description为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetDescription(OH_AVMetadataBuilder* builder, const char* description);

/**
 * @brief 设置歌词。
 *
 * @param builder 指向元数据构造器的实例。
 * @param lyric LRC格式的歌词内容。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数lyric为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetLyric(OH_AVMetadataBuilder* builder, const char* lyric);

/**
 * @brief 设置资源的跳转间隔时间。
 *
 * @param builder 指向元数据构造器的实例。
 * @param intervals 跳转的时间间隔。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数intervals为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetSkipIntervals(OH_AVMetadataBuilder* builder,
    AVMetadata_SkipIntervals intervals);

/**
 * @brief 设置媒体资源的金标类型。
 *
 * @param builder 指向元数据构造器的实例。
 * @param tags 用于在播控中心显示的媒体资源金标类型。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：参数builder为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_SetDisplayTags(OH_AVMetadataBuilder* builder, int32_t tags);

/**
 * @brief 设置支持的协议。
 *
 * @param builder 指向元数据构造器的实例。
 * @param filter 此会话支持的协议。如果没有设置，默认为{@link AVSession_ProtocolType}.TYPE_CAST_PLUS_STREAM。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数filter是无效的。
 * @since 23
 */
AVMetadata_Result OH_AVMetadataBuilder_SetFilter(OH_AVMetadataBuilder* builder, uint32_t filter);

/**
 * @brief 生成媒体元数据对象。
 *
 * @param builder 指向元数据构造器的实例。
 * @param avMetadata 指向元数据的指针对象。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_NO_MEMORY：内存不足。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：\n
 *                                       1. 参数builder为nullptr。\n
 *                                       2. 参数avMetadata为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadataBuilder_GenerateAVMetadata(OH_AVMetadataBuilder* builder,
    OH_AVMetadata** avMetadata);

/**
 * @brief 释放媒体元数据对象。
 *
 * @param avMetadata 指向元数据实例的指针。
 * @return AVMETADATA_SUCCESS：函数执行成功。\n
 *         AVMETADATA_ERROR_INVALID_PARAM：参数avMetadata为nullptr。
 * @since 13
 */
AVMetadata_Result OH_AVMetadata_Destroy(OH_AVMetadata* avMetadata);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVMETADATA_H
/** @} */
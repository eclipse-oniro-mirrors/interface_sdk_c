/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @since 23
 * @version 1.0
 */

/**
 * @file native_avqueueitem.h
 *
 * @brief 提供音视频队列元素的定义。
 *
 * @library libohavsession.so
 * @syscap SystemCapability.Multimedia.AVSession.Core
 * @kit AVSessionKit
 * @since 23
 * @version 1.0
 */

#ifndef NATIVE_AVQUEUEITEM_H
#define NATIVE_AVQUEUEITEM_H

#include <stdint.h>
#include "native_avsession_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义OH_AVSession_AVMediaDescription结构体，用于描述应用为当前资源设置的音视频媒体信息。
 *
 * @since 23
 * @version 1.0
 */
typedef struct OH_AVSession_AVMediaDescription OH_AVSession_AVMediaDescription;

/**
 * @brief 音视频队列元素的定义。
 *
 * @since 23
 * @version 1.0
 */
typedef struct OH_AVSession_AVQueueItem {
    /**
     * @brief 资源ID。
     */
    uint32_t itemId;

    /**
     * @brief 媒体项信息。
     */
    OH_AVSession_AVMediaDescription *description;
} OH_AVSession_AVQueueItem;

/**
 * @brief 音视频媒体描述构建器的声明。
 * 构建器的实例用于创建媒体描述信息。
 *
 * @since 23
 * @version 1.0
 */
typedef struct OH_AVSession_AVMediaDescriptionBuilder OH_AVSession_AVMediaDescriptionBuilder;

/**
 * @brief 创建OH_AVSession_AVMediaDescriptionBuilder实例。
 * 当该实例不再被使用时，调用{@link OH_AVSession_AVMediaDescriptionBuilder_Destroy}来释放构建器对象。
 *
 * @param builder 指向用于接收创建结果的构建器对象。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：参数builder为nullptr。\n
 *         AVQUEUEITEM_ERROR_NO_MEMORY：内存不足。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_Create(OH_AVSession_AVMediaDescriptionBuilder** builder);

/**
 * @brief 销毁构建器。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：参数builder为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_Destroy(OH_AVSession_AVMediaDescriptionBuilder* builder);

/**
 * @brief 设置媒体资源的当前资产ID。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param assetId 媒体资源的当前资产ID。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数assetId为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_SetAssetId(OH_AVSession_AVMediaDescriptionBuilder* builder,
    const char* assetId);

/**
 * @brief 设置媒体资源的标题。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param title 媒体资源的标题。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数title为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_SetTitle(OH_AVSession_AVMediaDescriptionBuilder* builder,
    const char* title);

/**
 * @brief 设置媒体资源的副标题。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param subtitle 媒体资源的副标题。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数subtitle为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_SetSubTitle(OH_AVSession_AVMediaDescriptionBuilder* builder,
    const char* subtitle);

/**
 * @brief 设置媒体资源的艺术家信息。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param artist 媒体资源的艺术家。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数artist为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_SetArtist(OH_AVSession_AVMediaDescriptionBuilder* builder,
    const char* artist);

/**
 * @brief 设置媒体资源的媒体图像URL。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param albumCoverUri 在媒体中心显示的资源的图像URL。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数albumCoverUri为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_SetAlbumCoverUri(
    OH_AVSession_AVMediaDescriptionBuilder* builder, const char* albumCoverUri);

/**
 * @brief 设置媒体资源的媒体类型。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param mediaType 媒体资源的媒体类型。如VIDEO或AUDIO。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数mediaType为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_SetMediaType(OH_AVSession_AVMediaDescriptionBuilder* builder,
    const char* mediaType);

/**
 * @brief 设置媒体资源的歌词内容。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param lyricContent 媒体资源的歌词内容。为LRC（Lyric Reduced Codec）格式。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数lyricContent为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_SetLyricContent(
    OH_AVSession_AVMediaDescriptionBuilder* builder, const char* lyricContent);

/**
 * @brief 设置媒体资源的持续时间。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param duration 媒体资源的持续时间。单位为毫秒（ms）。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数duration为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_SetDuration(OH_AVSession_AVMediaDescriptionBuilder* builder,
    const int32_t duration);

/**
 * @brief 设置媒体资源的媒体URI。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param mediaUri 媒体资源的URI。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数mediaUri为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_SetMediaUri(OH_AVSession_AVMediaDescriptionBuilder* builder,
    const char* mediaUri);

/**
 * @brief 设置媒体资源的起始位置。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param startPosition 媒体资源的起始位置。单位为毫秒（ms）。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数startPosition是无效的。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_SetStartPosition(
    OH_AVSession_AVMediaDescriptionBuilder* builder, const int32_t startPosition);

/**
 * @brief 设置媒体资源的大小。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param mediaSize 媒体资源的大小。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数mediaSize是无效的。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_SetMediaSize(OH_AVSession_AVMediaDescriptionBuilder* builder,
    const int32_t mediaSize);

/**
 * @brief 设置媒体资源的专辑标题。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param albumTitle 媒体资源的专辑标题。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数albumTitle为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_SetAlbumTitle(OH_AVSession_AVMediaDescriptionBuilder* builder,
    const char* albumTitle);

/**
 * @brief 设置媒体资源来源的应用名称。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param appName 媒体资源来源的应用名称。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数appName为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_SetAppName(OH_AVSession_AVMediaDescriptionBuilder* builder,
    const char* appName);

/**
 * @brief 获取媒体资源的当前资产ID。
 *
 * @param description 表示音视频媒体描述实例指针。
 * @param assetId 指针变量，用于接收媒体资源的当前资产ID。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数description为nullptr。\n
 *                                        2. 参数assetId为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_GetAssetId(OH_AVSession_AVMediaDescription* description,
    char** assetId);

/**
 * @brief 获取媒体资源的标题。
 *
 * @param description 表示音视频媒体描述实例指针。
 * @param title 指针变量将返回当前媒体资源的标题。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数description为nullptr。\n
 *                                        2. 参数title为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_GetTitle(OH_AVSession_AVMediaDescription* description,
    char** title);

/**
 * @brief 获取媒体资源的副标题。
 *
 * @param description 表示音视频媒体描述实例指针。
 * @param subtitle 指针变量将返回当前媒体资源的副标题。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数description为nullptr。\n
 *                                        2. 参数subtitle为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_GetSubtitle(OH_AVSession_AVMediaDescription* description,
    char** subtitle);

/**
 * @brief 获取媒体资源的艺术家信息。
 *
 * @param description 表示音视频媒体描述实例指针。
 * @param artist 指针变量将返回当前媒体资源的艺术家信息。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数description为nullptr。\n
 *                                        2. 参数artist为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_GetArtist(OH_AVSession_AVMediaDescription* description,
    char** artist);

/**
 * @brief 获取媒体资源的媒体图像URL。
 *
 * @param description 表示音视频媒体描述实例指针。
 * @param albumCoverUri 指针变量将返回资源的媒体图像URL。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数description为nullptr。\n
 *                                        2. 参数albumCoverUri为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_GetAlbumCoverUri(OH_AVSession_AVMediaDescription* description,
    char** albumCoverUri);
/**
 * @brief 获取媒体类型信息。
 *
 * @param description 表示音视频媒体描述实例指针。
 * @param mediaType 指针变量将返回当前媒体类型。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数description为nullptr。\n
 *                                        2. 参数mediaType为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_GetMediaType(OH_AVSession_AVMediaDescription* description,
    char** mediaType);

/**
 * @brief 获取资源的歌词内容。
 *
 * @param description 表示音视频媒体描述实例指针。
 * @param lyricContent 指针变量将返回当前媒体歌词内容。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数description为nullptr。\n
 *                                        2. 参数lyricContent为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_GetLyricContent(OH_AVSession_AVMediaDescription* description,
    char** lyricContent);

/**
 * @brief 获取媒体资源的持续时间。
 *
 * @param description 表示音视频媒体描述实例指针。
 * @param duration 指针变量将返回当前媒体资源的总时长。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数description为nullptr。\n
 *                                        2. 参数duration为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_GetDuration(OH_AVSession_AVMediaDescription* description,
    int32_t* duration);

/**
 * @brief 获取媒体资源的媒体URI。
 *
 * @param description 表示音视频媒体描述实例指针。
 * @param mediaUri 指针变量将返回当前媒体资源标识符。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数description为nullptr。\n
 *                                        2. 参数mediaUri为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_GetMediaUri(OH_AVSession_AVMediaDescription* description,
    char** mediaUri);

/**
 * @brief 获取媒体资源的起始位置。
 *
 * @param description 表示音视频媒体描述实例指针。
 * @param startPosition 指针变量将返回当前媒体资源开始的位置。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数description为nullptr。\n
 *                                        2. 参数startPosition为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_GetStartPosition(OH_AVSession_AVMediaDescription* description,
    int32_t* startPosition);

/**
 * @brief 获取资源的媒体大小。
 *
 * @param description 表示音视频媒体描述实例指针。
 * @param mediaSize 指针变量将返回当前媒体资源的大小。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数description为nullptr。\n
 *                                        2. 参数mediaSize为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_GetMediaSize(OH_AVSession_AVMediaDescription* description,
    int32_t* mediaSize);

/**
 * @brief 获取媒体资源的专辑标题。
 *
 * @param description 表示音视频媒体描述实例指针。
 * @param albumTitle 指针变量将返回当前媒体资源的专辑标题。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数description为nullptr。\n
 *                                        2. 参数albumTitle为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_GetAlbumTitle(OH_AVSession_AVMediaDescription* description,
    char** albumTitle);

/**
 * @brief 获取媒体资源的应用名。
 *
 * @param description 表示音视频媒体描述实例指针。
 * @param appName 指针变量将返回媒体资源的应用名称。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数description为nullptr。\n
 *                                        2. 参数appName为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_GetAppName(OH_AVSession_AVMediaDescription* description,
    char** appName);

/**
 * @brief 创建avMediaDescription对象。
 * 当该对象不再使用时，调用{@link OH_AVSession_AVMediaDescription_Destroy}释放avMediaDescription对象。
 *
 * @param builder 表示音视频媒体描述构建器实例指针。
 * @param avMediaDescription 指向用于接收avMediaDescription对象的指针变量。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_NO_MEMORY：内存不足。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：\n
 *                                        1. 参数builder为nullptr。\n
 *                                        2. 参数avMediaDescription为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescriptionBuilder_GenerateAVMediaDescription(
    OH_AVSession_AVMediaDescriptionBuilder* builder,
    OH_AVSession_AVMediaDescription** avMediaDescription);

/**
 * @brief 释放avMediaDescription对象。
 *
 * @param avMediaDescription 指向要释放的avMediaDescription对象。
 * @return AVQUEUEITEM_SUCCESS：函数执行成功。\n
 *         AVQUEUEITEM_ERROR_INVALID_PARAM：参数avMediaDescription为nullptr。
 * @since 23
 */
AVQueueItem_Result OH_AVSession_AVMediaDescription_Destroy(OH_AVSession_AVMediaDescription* avMediaDescription);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVQUEUEITEM_H
/** @} */
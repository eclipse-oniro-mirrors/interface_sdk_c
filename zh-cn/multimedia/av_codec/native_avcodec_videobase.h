/*
 * Copyright (C) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup CodecBase
 * @{
 *
 * @brief CodecBase模块提供了用于音视频封装、解封装、编解码基础功能的变量、属性以及函数。
 *
 * @syscap SystemCapability.Multimedia.Media.VideoDecoder
 * @since 9
 */
/**
 * @file native_avcodec_videobase.h
 *
 * @brief 声明用于基础视频编解码功能以及视频特定配置和参数的Native API。
 *
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avcodec_videobase.h>
 * @library libnative_media_codecbase.so
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 26.0.0
 */

#ifndef NATIVE_AVCODEC_VIDEOBASE_H
#define NATIVE_AVCODEC_VIDEOBASE_H
#include <stdint.h>
#include "native_avformat.h"
#include "native_averrors.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于描述单个ROI（感兴趣区域）矩形顶部坐标（y）的键，值类型为int32_t。
 *
 * 坐标系的原点位于视频的左上角。
 * 取值范围为[0, {@link OH_MD_KEY_VIDEO_METADATA_ROI_BOTTOM})。
 * 这是配置ROI参数时的必填键。
*
* @since 26.0.0
*/
extern const char *OH_MD_KEY_VIDEO_METADATA_ROI_TOP;

/**
 * @brief 用于描述单个ROI矩形左侧坐标 (x) 的键，值类型为 int32_t。
 *
 * 坐标系的原点位于视频的左上角。
 * 取值范围为[0, {@link OH_MD_KEY_VIDEO_METADATA_ROI_RIGHT})。
 * 这是配置ROI参数时的必填键。
*
* @since 26.0.0
*/
extern const char *OH_MD_KEY_VIDEO_METADATA_ROI_LEFT;

/**
 * @brief 用于描述单个ROI矩形底部坐标（y）的键，值类型为int32_t。
 *
 * 坐标系的原点位于视频的左上角。
 * 取值范围为({@link OH_MD_KEY_VIDEO_METADATA_ROI_TOP}, {@link OH_MD_KEY_VIDEO_HEIGHT}]。
 * 这是配置ROI参数时的必填键。
*
* @since 26.0.0
*/
extern const char *OH_MD_KEY_VIDEO_METADATA_ROI_BOTTOM;

/**
 * @brief 用于描述单个ROI矩形右侧坐标（x）的键，值类型为int32_t。
 *
 * 坐标系的原点位于视频的左上角。
 * 取值范围为({@link OH_MD_KEY_VIDEO_METADATA_ROI_LEFT}, {@link OH_MD_KEY_VIDEO_WIDTH}]。
 * 这是配置ROI参数时的必填键。
*
* @since 26.0.0
*/
extern const char *OH_MD_KEY_VIDEO_METADATA_ROI_RIGHT;

/**
 * @brief 用于描述单个ROI的量化参数（QP）偏移量的键，值类型为int32_t。
 *
 * 该变量取值范围为[-51, 51]。
 * 这是配置ROI参数时的可选键。
 * 如果未设置此键，编码器将对此区域使用其默认的量化参数策略。
*
* @since 26.0.0
*/
extern const char *OH_MD_KEY_VIDEO_METADATA_ROI_DELTA_QP;

/**
 * @brief 用于描述单个ROI语义标签的键，值类型为int32_t。
 *
 * 该变量值必须与{@link OH_VideoMetadataRoiSemanticLabel}对应。
 * 这是配置ROI参数时的可选键。
 * 如果未设置此键，该区域将采用默认的语义处理策略。
*
* @since 26.0.0
*/
extern const char *OH_MD_KEY_VIDEO_METADATA_ROI_SEM_LABEL;

/**
 * @brief 视频编码中感兴趣区域（ROI）的语义标签。
 *
 * @since 26.0.0
 */
typedef enum OH_VideoMetadataRoiSemanticLabel {
    /**
     * @brief 表示未指定或未知的区域。
     *
     * @since 26.0.0
     */
    OH_VIDEO_METADATA_ROI_SEM_LABEL_OTHER = 0,
    /**
     * @brief 表示该ROI包含人脸。
     *
     * @since 26.0.0
     */
    OH_VIDEO_METADATA_ROI_SEM_LABEL_FACE = 1
} OH_VideoMetadataRoiSemanticLabel;

/**
 * @brief 将OH_AVFormat句柄中的感兴趣区域（ROI）配置格式化为字符串，并将其追加到目标字符串中。
 *
 * 此函数从提供的格式句柄中提取ROI属性（如坐标、量化参数偏移量和语义标签），
 * 构建标准的ROI字符串表示，并将其追加到roiStrInOut指向的字符串中末尾。
 * 如果*roiStrInOut为NULL，则会分配一个新字符串，如果不为NULL，则会重新分配现有字符串的内存以追加新配置。
 *
 * @note 调用者拥有为*roiStrInOut分配内存的所有权。
 * 内存是通过标准C库分配器（malloc/realloc）分配的。
 * 当不再需要该字符串时，调用者必须使用匹配的标准C库释放器（free）释放该字符串，
 * 并将指针设置为NULL以防止重复释放。
 *
 * @param roiStrInOut 指向目标字符串的双重指针。指针本身不能为NULL。如果*roiStrInOut为NULL，则分配一个新字符串。
 * @param format 包含要追加的ROI参数的OH_AVFormat句柄，不能为NULL。
 * @return <ul>
 *         <li>AV_ERR_OK：表示字符串成功格式化并追加。</li>
 *         <li>AV_ERR_INVALID_VAL：表示roiStrInOut指针或format句柄为NULL，或者格式缺少必需的ROI键。</li>
 *         <li>AV_ERR_NO_MEMORY：表示内部内存分配或重新分配失败。</li>
 *         </ul>
 * @release free {roiStrInOut}
 * @since 26.0.0
 */
OH_AVErrCode OH_VideoMetadata_AppendRoiString(char **roiStrInOut, OH_AVFormat *format);

/**
 * @brief 预解析ROI字符串，以获取其中包含的有效ROI区域数量。
 *
 * 此接口不受具体后端容量限制影响，并根据语法规则准确返回字符串中识别出的有效区域数。
 *
 * @param roiStr 输入的ROI配置字符串。
 * @param outCount 返回从字符串中解析出的有效ROI区域的数量。
 * @return <ul>
 *         <li>AV_ERR_OK：表示操作成功。</li>
 *         <li>AV_ERR_INVALID_VAL：表示roiStr或outCount指针为NULL。</li>
 *         </ul>
 * @since 26.0.0
*/
OH_AVErrCode OH_VideoMetadata_GetRoiCount(const char *roiStr, uint32_t *outCount);

/**
* @brief 解析ROI字符串并填充调用者提供的OH_AVFormat数组。
*
* @note 调用者拥有每个成功创建的OH_AVFormat句柄的所有权。返回时，
* 有效的句柄存储在outOwnedFormats数组的前*outCount个元素中。
* - 完全或部分成功时（*outCount > 0），调用者必须使用{@link OH_AVFormat_Destroy}逐个销毁
* 有效句柄，以防止内存泄漏。
* - 完全失败时（*outCount == 0），不会创建任何句柄，也无需销毁。
*
* @param roiStr 输入的ROI配置字符串。
* @param outOwnedFormats 由调用者分配的指针数组，用于接收解析后的OH_AVFormat句柄。调用者拥有此数组中每个非NULL句柄的所有权。
* @param maxCapacity 指示outOwnedFormats数组的最大物理容量，以防止越界写入。
* @param outCount 返回成功解析并填充到数组中的实际ROI数量。
* @return <ul>
*         <li>AV_ERR_OK：表示操作成功。</li>
*         <li>AV_ERR_INVALID_VAL：表示roiStr、outOwnedFormats或outCount为NULL。</li>
*         </ul>
* @release media_foundation/OH_AVFormat_Destroy {outOwnedFormats}。
* @since 26.0.0
*/
OH_AVErrCode OH_VideoMetadata_ParseRoiString(const char *roiStr, OH_AVFormat **outOwnedFormats, uint32_t maxCapacity,
                                             uint32_t *outCount);

#ifdef __cplusplus
}
#endif
#endif // NATIVE_AVCODEC_VIDEOBASE_H
/** @} */
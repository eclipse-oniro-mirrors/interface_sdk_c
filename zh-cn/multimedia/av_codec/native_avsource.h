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
 * @addtogroup AVSource
 * @{
 *
 * @brief AVSource模块提供用于构造媒体资源对象功能的函数。
 *
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @since 10
 */

/**
 * @file native_avsource.h
 *
 * @brief 声明用于音视频媒体数据解析的接口。
 * @sample [AVCodec](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/BasicFeature/Media/AVCodec)
 *
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avsource.h>
 * @library libnative_media_avsource.so
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @since 10
 */

#ifndef NATIVE_AVSOURCE_H
#define NATIVE_AVSOURCE_H

#include <stdint.h>
#include "native_avcodec_base.h"
#include "native_averrors.h"
#include "native_avformat.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 为媒体资源接口定义native层对象。
 * @since 10
 */
typedef struct OH_AVSource OH_AVSource;

/**
 * @brief 为用户自定义数据源的资源对象创建OH_AVSource实例，可以通过调用{@link OH_AVSource_Destroy}接口释放实例。\n
 * 参数dataSource生命周期需与返回的指针OH_AVSource *保持一致。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param dataSource 用户自定义数据源。
 * @return 如果执行成功，则返回一个指向OH_AVSource实例的指针，否则返回NULL。\n
 * 可能的故障原因：\n
 * 1. dataSource为nullptr。\n
 * 2. dataSource->size == 0。\n
 * 3. 设置数据源失败。\n
 * 4. 内存不足。\n
 * 5. 解码器引擎为nullptr。\n
 * 6. dataSource-&gt;readAt == nullptr。
 * @since 12
*/
OH_AVSource *OH_AVSource_CreateWithDataSource(OH_AVDataSource *dataSource);

/**
 * @brief 为用户自定义数据源的资源对象创建OH_AVSource实例，可以通过调用{@link OH_AVSource_Destroy}接口释放实例。\n
 * 回调支持通过userData传递用户自定义数据。\n
 * 参数dataSource生命周期需与返回的指针OH_AVSource *保持一致。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param dataSource 指向数据源结构体的指针，该结构体可用于获取输入数据。
 * @param userData 指向用户自定义数据的指针。
 * @return 如果执行成功，则返回一个指向OH_AVSource实例的指针，否则返回NULL。\n
 * 可能的故障原因：\n
 * 1. dataSource为nullptr。\n
 * 2. dataSource->size == 0。\n
 * 3. 设置数据源失败。\n
 * 4. 内存不足。\n
 * 5. 解码器引擎为nullptr。\n
 * 6. dataSource-&gt;readAt == nullptr。
 * @since 20
*/
OH_AVSource *OH_AVSource_CreateWithDataSourceExt(OH_AVDataSourceExt *dataSource, void *userData);

/**
 * @brief 为统一资源标识符对应的资源对象创建OH_AVSource实例，可以通过调用{@link OH_AVSource_Destroy}接口释放实例。
 *
 * 该接口仅支持HTTP渐进式流媒体，不支持HLS/DASH的流媒体；对于HLS/DASH的流媒体播放，推荐使用AVPlayer组件进行开发。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param uri 远程媒体资源的统一资源标识符。
 * @return 执行成功返回一个指向OH_AVSource实例的指针, 否则返回NULL。\n
 * 可能的故障原因：\n
 * 1. 网络异常。\n
 * 2. 资源无效。\n
 * 3. 文件格式不支持。\n
 * 4. 应用配置明文拦截。
 * @since 10
*/
OH_AVSource *OH_AVSource_CreateWithURI(char *uri);

/**
 * @brief 为文件描述符对应的资源对象创建OH_AVSource实例。可以通过调用{@link OH_AVSource_Destroy}接口释放实例。\n
 * 接口如果传入offset不为文件起始位置，或size不为文件大小时，可能会因数据获取不完整导致 OH_AVSource创建失败、后续解封装失败等未定义错误。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param fd 数据资源的文件描述符。
 * @param offset 开始读取数据的位置。
 * @param size 文件的字节数大小。
 * @return 执行成功返回一个指向OH_AVSource实例的指针, 否则返回NULL。\n
 * 可能的故障原因：\n
 * 1. fd无效。\n
 * 2. 传入offset不是文件起始位置。\n
 * 3. size错误。\n
 * 4. 资源无效。\n
 * 5. 文件格式不支持。
 * @since 10
*/
OH_AVSource *OH_AVSource_CreateWithFD(int32_t fd, int64_t offset, int64_t size);

/**
 * @brief 销毁OH_AVSource实例并清理内部资源。\n
 * 同一实例只能被销毁一次。销毁的实例在被重新创建之前不能再被使用。建议实例销毁成功后将指针置为NULL。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param source 指向OH_AVSource实例的指针。
 * @return AV_ERR_OK：操作成功。\n
 *         AV_ERR_INVALID_VAL：\n
 *                          1. source指针无效，空指针。\n
 *                          2. 非OH_AVSource实例。
 * @since 10
*/
OH_AVErrCode OH_AVSource_Destroy(OH_AVSource *source);

/**
 * @brief 获取媒体资源文件的基础信息。\n
 * 需要注意的是，指向的OH_AVFormat实例在生命周期结束时需调用者通过调用接口{@link OH_AVFormat_Destroy}释放。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param source 指向OH_AVSource实例的指针。
 * @return 执行成功返回文件的基础信息，否则返回NULL。\n
 * 可能的故障原因：\n
 * 1. source指针无效。\n
 * 2. 空指针或非OH_AVSource实例。\n
 * 3. source没有初始化。
 * @since 10
*/
OH_AVFormat *OH_AVSource_GetSourceFormat(OH_AVSource *source);

/**
 * @brief 获取轨道的基础信息。\n
 * 需要注意的是，指向的OH_AVFormat实例在生命周期结束时需调用者通过调用接口{@link OH_AVFormat_Destroy}释放。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param source 指向OH_AVSource实例的指针。
 * @param trackIndex 需要获取信息的轨道的索引。
 * @return 执行成功返回轨道的基础信息，否则返回NULL。\n
 * 可能的故障原因：\n
 * 1. source指针无效，空指针或非OH_AVSource实例。\n
 * 2. 轨道的索引超出范围。\n
 * 3. source没有初始化。
 * @since 10
*/
OH_AVFormat *OH_AVSource_GetTrackFormat(OH_AVSource *source, uint32_t trackIndex);

/**
 * @brief 获取自定义元数据的基础信息。\n
 *
 * 需要注意的是，指向的OH_AVFormat实例在生命周期结束时需开发者通过调用接口{@link OH_AVFormat_Destroy}释放。
 *
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param source 指向OH_AVSource实例的指针。
 * @return 执行成功返回元数据的基础信息，否则返回NULL。\n
 * 可能的故障原因：\n
 * 1. source指针无效。\n
 * 2. 空指针或非OH_AVSource实例。\n
 * 3. source没有初始化。
 * @since 18
*/
OH_AVFormat *OH_AVSource_GetCustomMetadataFormat(OH_AVSource *source);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSOURCE_H

/** @} */
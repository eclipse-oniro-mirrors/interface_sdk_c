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
 * @addtogroup Core
 * @{
 *
 * @brief Core模块提供用于媒体系统的基础骨干能力，包含内存、错误码、媒体数据结构等相关函数。
 *
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 */

/**
 * @file native_avformat.h
 *
 * @brief 声明了OH_AVFormat相关的函数和枚举。
 * @sample [AVCodec](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/BasicFeature/Media/AVCodec)
 *
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avformat.h>
 * @library libnative_media_core.so
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 */

#ifndef NATIVE_AVFORMAT_H
#define NATIVE_AVFORMAT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 为OH_AVFormat接口定义native层对象。
 * @since 9
 */
typedef struct OH_AVFormat OH_AVFormat;

/**
 * @brief 视频像素格式的枚举类。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 * @version 1.0
 */
typedef enum OH_AVPixelFormat {
    /**
     * yuv 420 planar。
     */
    AV_PIXEL_FORMAT_YUVI420 = 1,
    /**
     *  NV12. yuv 420 semiplanar。
     */
    AV_PIXEL_FORMAT_NV12 = 2,
    /**
     *  NV21. yvu 420 semiplanar。
     */
    AV_PIXEL_FORMAT_NV21 = 3,
    /**
     * 像素格式从surface获取。只作用于Surface模式，Buffer模式不生效。
     */
    AV_PIXEL_FORMAT_SURFACE_FORMAT = 4,
    /**
     * 	RGBA8888。
     */
    AV_PIXEL_FORMAT_RGBA = 5,
    /**
     * @brief RGBA1010102。
     * @since 20
     */
    AV_PIXEL_FORMAT_RGBA1010102 = 6,
} OH_AVPixelFormat;

/**
 * @brief 创建OH_AVFormat实例，用于读取数据。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @return 返回指向OH_AVFormat实例的指针。系统资源不足时返回NULL。
 * @since 9
 * @version 1.0
 */
struct OH_AVFormat *OH_AVFormat_Create(void);

/**
 * @brief 创建音频OH_AVFormat实例指针并预设置指定参数，用于读写数据。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param mimeType MIME类型描述字符串，请参阅{@link AVCODEC_MIMETYPE}。
 * @param sampleRate 采样率，单位Hz。
 * @param channelCount 声道个数，如1为单声道，2为双声道。
 * @return 如果创建成功，返回指向OH_AVFormat实例的指针，如果失败，则返回NULL。\n
 * 可能的失败原因：\n
 * 1. 传入的mimeType为NULL。\n
 * 2. 系统资源不足。
 * @since 10
 * @version 1.0
 */
struct OH_AVFormat *OH_AVFormat_CreateAudioFormat(const char *mimeType,
                                                  int32_t sampleRate,
                                                  int32_t channelCount);

/**
 * @brief 创建视频OH_AVFormat实例指针并预设置指定参数，用于读写数据。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param mimeType MIME类型描述字符串，请参阅{@link AVCODEC_MIMETYPE}。
 * @param width 图像的宽度，单位为pixel。
 * @param height 图像的高度，单位为pixel。
 * @return 如果创建成功，返回指向OH_AVFormat实例的指针，如果失败，则返回NULL。\n
 * 可能的失败原因：\n
 * 1. 传入的mimeType为NULL。\n
 * 2. 系统资源不足。
 * @since 10
 * @version 1.0
 */
struct OH_AVFormat *OH_AVFormat_CreateVideoFormat(const char *mimeType,
                                                  int32_t width,
                                                  int32_t height);

/**
 * @brief 销毁OH_AVFormat实例，不允许重复销毁。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @since 9
 * @version 1.0
 */
void OH_AVFormat_Destroy(struct OH_AVFormat *format);

/**
 * @brief 复制OH_AVFormat实例。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param to OH_AVFormat实例，用于接收数据。
 * @param from 指向复制数据的OH_AVFormat实例的指针。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入参数为空指针。\n
 * 2. 输入的OH_AVFormat参数结构校验失败。
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_Copy(struct OH_AVFormat *to, struct OH_AVFormat *from);

/**
 * @brief 对OH_AVFormat的[key](capi-codecbase.md#媒体数据键值对)赋int类型的值。
 * 该接口仅能设置int类型的参数，参数类型定义详见{@link native_avcodec_base.h}。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 写入数据的键。
 * @param value 写入数据的值。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 设置的key对应的value类型错误。
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_SetIntValue(struct OH_AVFormat *format, const char *key, int32_t value);

/**
 * @brief 对OH_AVFormat的key赋unsigned int类型的值。
 *
 * 该接口仅能设置unsigned int类型的参数，具体参数类型定义请参考{@link native_avcodec_base.h}。
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 写入数据的键。
 * @param value 写入数据的值。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。
 * @since 23
 */
bool OH_AVFormat_SetUintValue(struct OH_AVFormat *format, const char *key, uint32_t value);

/**
 * @brief 对OH_AVFormat的[key](capi-codecbase.md#媒体数据键值对)赋long类型的值。
 * 该接口仅能设置long类型的参数，参数类型定义详见{@link native_avcodec_base.h}。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 写入数据的键。
 * @param value 写入数据的值。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 设置的key对应的value类型错误。
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_SetLongValue(struct OH_AVFormat *format, const char *key, int64_t value);

/**
 * @brief 对OH_AVFormat的[key](capi-codecbase.md#媒体数据键值对)赋float类型的值。
 * 该接口仅能设置float类型的参数，参数类型定义详见{@link native_avcodec_base.h}。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 写入数据的键。
 * @param value 写入数据的值。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 设置的key对应的value类型错误。
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_SetFloatValue(struct OH_AVFormat *format, const char *key, float value);

/**
 * @brief 对OH_AVFormat的[key](capi-codecbase.md#媒体数据键值对)赋double类型的值。
 * 该接口仅能设置double类型的参数，参数类型定义详见{@link native_avcodec_base.h}。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 写入数据的键。
 * @param value 写入数据的值。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 设置的key对应的value类型错误。
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_SetDoubleValue(struct OH_AVFormat *format, const char *key, double value);

/**
 * @brief 对OH_AVFormat的[key](capi-codecbase.md#媒体数据键值对)赋string类型的值。
 * 该接口仅能设置string类型的参数，参数类型定义详见{@link native_avcodec_base.h}。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 写入数据的键。
 * @param value 写入字符串数据（使用建议：设置字符长度不超过256字节）。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 输入value为空指针。\n
 * 5. 设置的key对应的value类型错误。
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_SetStringValue(struct OH_AVFormat *format, const char *key, const char *value);

/**
 * @brief 将指定长度的数据块写入OH_AVFormat。
 * 该接口仅能设置buffer类型的参数，参数类型定义详见{@link native_avcodec_base.h}。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 写入数据的键。
 * @param addr 写入数据的地址，生命周期由开发者管理。
 * @param size 	写入数据的长度，范围为(0, 1]MB。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 输入addr为空指针。\n
 * 5. size为0或超过限制1MB。\n
 * 6. 设置的key对应的value类型错误。
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_SetBuffer(struct OH_AVFormat *format, const char *key, const uint8_t *addr, size_t size);

/**
 * @brief 从OH_AVFormat的[key](capi-codecbase.md#媒体数据键值对)获取int类型的值。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 读取数据的键。
 * @param out 读取数据的值。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 输入out为空指针。\n
 * 5. 获取的key不存在或者未设置。
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_GetIntValue(struct OH_AVFormat *format, const char *key, int32_t *out);

/**
 * @brief 使用key从OH_AVFormat中获取unsigned int类型的值。
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 读取数据的键。
 * @param out 读取数据的值。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 输入out为空指针。
 * @since 23
 */
bool OH_AVFormat_GetUintValue(struct OH_AVFormat *format, const char *key, uint32_t *out);

/**
 * @brief 从OH_AVFormat的[key](capi-codecbase.md#媒体数据键值对)获取long类型的值。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 读取数据的键。
 * @param out 读取数据的值。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 输入out为空指针。\n
 * 5. 获取的key不存在或者未设置。
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_GetLongValue(struct OH_AVFormat *format, const char *key, int64_t *out);

/**
 * @brief 从OH_AVFormat的[key](capi-codecbase.md#媒体数据键值对)获取float类型的值。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 读取数据的键。
 * @param out 读取数据的值。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 输入out为空指针。\n
 * 5. 获取的key不存在或者未设置。
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_GetFloatValue(struct OH_AVFormat *format, const char *key, float *out);

/**
 * @brief 从OH_AVFormat的[key](capi-codecbase.md#媒体数据键值对)获取double类型的值。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 读取数据的键。
 * @param out 读取数据的值。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 输入out为空指针。\n
 * 5. 获取的key不存在或者未设置。
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_GetDoubleValue(struct OH_AVFormat *format, const char *key, double *out);

/**
 * @brief 从OH_AVFormat的[key](capi-codecbase.md#媒体数据键值对)获取string类型的值。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 读取数据的键。
 * @param out 读取string指针，out数据的生命周期与format内string对应，如果开发者需要长时间保持它，必须进行拷贝内存。out最大输出字符串长度为256字节，如果长度超过256字节，会报false。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 输入out为空指针。\n
 * 5. malloc出的out字符串资源不足。\n
 * 6. 获取的key不存在或者未设置。\n
 * 7. 输出out的长度超过256字节。
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_GetStringValue(struct OH_AVFormat *format, const char *key, const char **out);

/**
 * @brief 从OH_AVFormat中读取指定长度的数据块。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 要读取数据的键。
 * @param addr 生命周期与format相同，与format一同销毁。如果开发者需要长时间保持它，必须进行内存拷贝。
 * @param size 读到数据的长度。
 * @return 返回值为true表示成功，为false表示失败。
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 输入addr为空指针。\n
 * 5. 输入size为空指针。\n
 * 6. 获取的key不存在或者未设置。
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_GetBuffer(struct OH_AVFormat *format, const char *key, uint8_t **addr, size_t *size);

/**
 * @brief 从OH_AVFormat中读取一个int32_t数据的数组。\n
 * 
 * 需要注意的是，获取的buffer生命周期与OH_AVFormat对象绑定，当format销毁时自动失效。\n
 * 如果开发者需要长时间保持绑定，应用程序必须将数据显式复制到新分配的内存。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 要读取数据的键。
 * @param addr 保存数据内存的指针。
 * @param size 读到数据的元素数量。
 * @return 返回值为true表示成功，为false表示失败。\n
 * 可能的失败原因：
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 输入addr为空指针。\n
 * 5. 输入size为空指针。
 * @since 20
 */
bool OH_AVFormat_GetIntBuffer(struct OH_AVFormat *format, const char *key, int32_t **addr, size_t *size);

/**
 * @brief 返回OH_AVFormat中包含的key-value组成的字符串。最大可返回1024字节的字符串，销毁format时释放字符串指针。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @return 如果创建成功，返回一个由key-value组成的字符串，如果失败，则返回NULL。
 * 可能的失败原因：\n
 * 1.  传入的format为NULL。\n
 * 2. 系统资源不足。
 * @since 9
 * @version 1.0
 */
const char *OH_AVFormat_DumpInfo(struct OH_AVFormat *format);

/**
 * @brief 将指定长度int32_t类型的数据块写入OH_AVFormat。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param format 指向OH_AVFormat实例的指针。
 * @param key 写入数据的键。
 * @param addr 写入数据的地址，生命周期由开发者管理。
 * @param size 写入数据的长度（以元素为单位，不是字节数）。
 * @return 返回true表示成功，返回false表示失败。\n
 * 可能的失败原因：\n
 * 1. 输入format为空指针。\n
 * 2. 输入format参数结构校验失败。\n
 * 3. 输入key为空指针。\n
 * 4. 输入addr为空指针。\n
 * 5. 输入size为0。
 * @since 20
 */
bool OH_AVFormat_SetIntBuffer(struct OH_AVFormat *format, const char *key, const int32_t *addr, size_t size);

/**
 * @brief 获取OH_AVFormat中包含的键总数。
 * @param format 指向一个OH_AVFormat实例的指针。
 * @return 成功时返回键的数量；失败时返回 0。
 * @details 可能的失败原因：\n
 * 1. 输入的format为空指针;\n
 * 2. 系统资源不足。
 * @since 23
 */
uint32_t OH_AVFormat_GetKeyCount(OH_AVFormat *format);

/**
 * @brief 通过索引从OH_AVFormat中获取键名字符串。
 * @param format 指向一个OH_AVFormat实例的指针。
 * @param index 要查询键的索引值，取值范围为[0, OH_AVFormat_GetKeyCount(format))。
 * @param key 用于接收键名字符串的输出指针；该字符串的生命周期与format绑定。
 * @return 成功时返回true，失败时返回false。
 * @details 可能的失败原因：\n
 * 1. 输入的format为空指针;\n
 * 2. index超出有效范围;\n
 * 3. key为空指针;\n
 * 4. 系统资源不足。
 * @since 23
 */
bool OH_AVFormat_GetKey(OH_AVFormat *format, uint32_t index, const char **key);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVFORMAT_H

/** @} */


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
 * @addtogroup Image
 * @{
 *
 * @brief Provides native APIs for image sources.
 *
 * @since 10
 * @version 4.0
 */

/**
 * @file image_source_mdk.h
 *
 * @brief 声明将ImageSource解码成像素位图的方法。
 *
 * @library libimage_source_ndk.z.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.Image.ImageSource
 * @since 10
 * @version 4.0
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_SOURCE_MDK_H_
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_SOURCE_MDK_H_
#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif
#include <stddef.h>
#include "napi/native_api.h"
#include "image_mdk_common.h"
#include "rawfile/raw_file.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 为图像源方法定义native层图像源对象。
 *
 * @since 10
 * @version 4.0
 */
struct ImageSourceNative_;

/**
 * @brief 为图像源方法定义native层图像源对象。
 *
 * @since 10
 * @version 4.0
 */
typedef struct ImageSourceNative_ ImageSourceNative;

/**
 * @brief 定义每个样本比特的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_BITS_PER_SAMPLE = "BitsPerSample";

/**
 * @brief 定义方向的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_ORIENTATION = "Orientation";

/**
 * @brief 定义图像长度的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_IMAGE_LENGTH = "ImageLength";

/**
 * @brief 定义图像宽度的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_IMAGE_WIDTH = "ImageWidth";

/**
 * @brief 定义GPS纬度的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_GPS_LATITUDE = "GPSLatitude";

/**
 * @brief 定义GPS经度的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_GPS_LONGITUDE = "GPSLongitude";

/**
 * @brief 定义GPS纬度参考的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_GPS_LATITUDE_REF = "GPSLatitudeRef";

/**
 * @brief 定义GPS经度参考的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_GPS_LONGITUDE_REF = "GPSLongitudeRef";

/**
 * @brief 定义初始日期时间的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_DATE_TIME_ORIGINAL = "DateTimeOriginal";

/**
 * @brief 定义曝光时间的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_EXPOSURE_TIME = "ExposureTime";

/**
 * @brief 定义场景类型的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_SCENE_TYPE = "SceneType";

/**
 * @brief 定义ISO速度等级的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_ISO_SPEED_RATINGS = "ISOSpeedRatings";

/**
 * @brief 定义FNumber的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_F_NUMBER = "FNumber";

/**
 * @brief 定义每个像素的压缩比特的图像属性关键字。
 * <br>此标签给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
static const char* OHOS_IMAGE_PROPERTY_COMPRESSED_BITS_PER_PIXEL = "CompressedBitsPerPixel";

/**
 * @brief 定义图像源解码的范围选项。是{@link OhosImageDecodingOps}的成员变量。
 *
 * @since 10
 * @version 4.0
 */
struct OhosImageRegion {
    /**
     * 起始x坐标，用pixels表示。
     */
    int32_t x;
    /**
     * 起始y坐标，用pixels表示。
     */
    int32_t y;
    /**
     * 宽度范围，用pixels表示。
     */
    int32_t width;
    /**
     * 高度范围，用pixels表示。
     */
    int32_t height;
};

/**
 * @brief 定义图像源选项信息。此选项给{@link OH_ImageSource_CreateFromUri}、{@link OH_ImageSource_CreateFromFd}、
 * {@link OH_ImageSource_CreateFromData}和{@link OH_ImageSource_CreateIncremental}接口使用。
 *
 * @since 10
 * @version 4.0
 */
struct OhosImageSourceOps {
    /**
     * 图像源像素密度。
     */
    int32_t density;
    /**
     * 图像源像素格式，通常用于描述YUV缓冲区。
     */
    int32_t pixelFormat;
    /**
     * 图像源像素宽高的大小。
     */
    struct OhosImageSize size;
};

/**
 * @brief 定义图像源解码的范围选项。是{@link OhosImageDecodingOps}的成员变量。
 *
 * @since 10
 * @version 4.0
 */
struct OhosImageDecodingOps {
    /** Defines output pixel map editable. */
    int8_t editable;
    /** Defines output pixel format. */
    int32_t pixelFormat;
    /** Defines decoding target pixel density. */
    int32_t fitDensity;
    /** Defines decoding index of image source. */
    uint32_t index;
    /** Defines decoding sample size option. */
    uint32_t sampleSize;
    /** Defines decoding rotate option. */
    uint32_t rotate;
    /** Defines decoding target pixel size of width and height. */
    struct OhosImageSize size;
    /** Defines image source pixel region for decoding. */
    struct OhosImageRegion region;
};

/**
 * @brief 定义图像源信息，由{@link OH_ImageSource_GetImageInfo}获取。
 *
 * @since 10
 * @version 4.0
 */
struct OhosImageSourceInfo {
    /**
 * 图像源像素格式，由{@link OH_ImageSource_CreateFromUri}、{@link OH_ImageSource_CreateFromFd}和
 * {@link OH_ImageSource_CreateFromData}设置。
 */
    int32_t pixelFormat;
    /**
     * 图像源色彩空间。
     */
    int32_t colorSpace;
    /**
     * 图像源透明度类型。
     */
    int32_t alphaType;
    /**
 * 图像源密度，由{@link OH_ImageSource_CreateFromUri}、{@link OH_ImageSource_CreateFromFd}和
 * {@link OH_ImageSource_CreateFromData}设置。
 */
    int32_t density;
    /**
     * 图像源像素宽高的大小。
     */
    struct OhosImageSize size;
};

/**
 * @brief 定义图像源输入资源，每次仅接收一种类型。由{@link OH_ImageSource_CreateFromUri}、{@link OH_ImageSource_CreateFromFd}和
 * {@link OH_ImageSource_CreateFromData}获取。
 *
 * @since 10
 * @version 4.0
 * @deprecated since 11
 */
struct OhosImageSource {
#ifdef __cplusplus
    /**
     * Pointer to the image source URI. Only a file URI or Base64 URI is accepted.
     * @since 10
     */
    char* uri = nullptr;
    /**
     * Length of the image source URI.
     * @since 10
     */
    size_t uriSize = 0;
    /**
     * Descriptor of the image source.
     * @since 10
     */
    int32_t fd = -1;
    /**
     * Pointer to the image source buffer. Only a formatted packet buffer or Base64 buffer is accepted.
     * @since 10
     */
    uint8_t* buffer = nullptr;
    /**
     * Size of the image source buffer.
     * @since 10
     */
    size_t bufferSize = 0;
#else
    /**
     * Pointer to the image source URI. Only a file URI or Base64 URI is accepted.
     * @since 10
     */
    char* uri;
    /**
     * Length of the image source URI.
     * @since 10
     */
    size_t uriSize;
    /**
     * Descriptor of the image source.
     * @since 10
     */
    int32_t fd;
    /**
     * Pointer to the image source buffer. Only a formatted packet buffer or Base64 buffer is accepted.
     * @since 10
     */
    uint8_t* buffer;
    /**
     * Size of the image source buffer.
     * @since 10
     */
    size_t bufferSize;
#endif
};

/**
 * @brief 定义图像源延迟时间列表。由{@link OH_ImageSource_GetDelayTime}获取。
 *
 * @since 10
 * @version 4.0
 */
struct OhosImageSourceDelayTimeList {
#ifdef __cplusplus
    /**
     * 图像源延迟时间列表头地址。
     * @since 10
     */
    int32_t* delayTimeList;
    /**
     * Size of the image source delay time list.
     * @since 10
     */
    size_t size = 0;
#else
    /**
     * 图像源延迟时间列表头地址。
     * @since 10
     */
    int32_t* delayTimeList;
    /**
     * Size of the image source delay time list.
     * @since 10
     */
    size_t size;
#endif
};

/**
 * @brief 定义图像源支持的格式字符串。此选项给{@link OhosImageSourceSupportedFormatList}和{@link OH_ImageSource_GetSupportedFormats}接口使用。
 *
 * @since 10
 * @version 4.0
 */
struct OhosImageSourceSupportedFormat {
#ifdef __cplusplus
    /**
     * Image source supported format string head.
     * @since 10
     */
    char* format = nullptr;
    /**
     * Image source supported format string size.
     * @since 10
     */
    size_t size = 0;
#else
    /**
     * Image source supported format string head.
     * @since 10
     */
    char* format;
    /**
     * Image source supported format string size.
     * @since 10
     */
    size_t size;
#endif
};

/**
 * @brief 定义图像源支持的格式字符串。此选项给{@link OhosImageSourceSupportedFormatList}和{@link OH_ImageSource_GetSupportedFormats}接口使用。
 *
 * @since 10
 * @version 4.0
 */
struct OhosImageSourceSupportedFormatList {
#ifdef __cplusplus
    /**
     * Image source supported format string list head.
     * @since 10
     */
    struct OhosImageSourceSupportedFormat** supportedFormatList = nullptr;
    /**
     * Image source supported format string list size.
     * @since 10
     */
    size_t size = 0;
#else
    /**
     * Image source supported format string list head.
     * @since 10
     */
    struct OhosImageSourceSupportedFormat** supportedFormatList;
    /**
     * Image source supported format string list size.
     * @since 10
     */
    size_t size;
#endif
};

/**
 * @brief 定义图像源属性键值字符串。此选项给{@link OH_ImageSource_GetImageProperty}和{@link OH_ImageSource_ModifyImageProperty}接口使用。
 *
 * @since 10
 * @version 4.0
 */
struct OhosImageSourceProperty {
#ifdef __cplusplus
    /**
     * Image source property key and value string head.
     * @since 10
     */
    char* value = nullptr;
    /**
     * Image source property key and value string size.
     * @since 10
     */
    size_t size = 0;
#else
    /**
     * Image source property key and value string head.
     * @since 10
     */
    char* value;
    /**
     * Image source property key and value string size.
     * @since 10
     */
    size_t size;
#endif
};

/**
 * @brief 定义图像源更新数据选项，由{@link OH_ImageSource_UpdateData}获取。
 *
 * @since 10
 * @version 4.0
 */
struct OhosImageSourceUpdateData {
#ifdef __cplusplus
    /**
     * Image source update data buffer.
     * @since 10
     */
    uint8_t* buffer = nullptr;
    /**
     * Image source update data buffer size.
     * @since 10
     */
    size_t bufferSize = 0;
    /**
     * Image source offset of update data buffer.
     * @since 10
     */
    uint32_t offset = 0;
    /**
     * Image source update data length in update data buffer.
     * @since 10
     */
    uint32_t updateLength = 0;
    /**
     * Image source update data is completed in this session.
     * @since 10
     */
    int8_t isCompleted = 0;
#else
    /**
     * Image source update data buffer.
     * @since 10
     */
    uint8_t* buffer;
    /**
     * Image source update data buffer size.
     * @since 10
     */
    size_t bufferSize;
    /**
     * Image source offset of update data buffer.
     * @since 10
     */
    uint32_t offset;
    /**
     * Image source update data length in update data buffer.
     * @since 10
     */
    uint32_t updateLength;
    /**
     * Image source update data is completed in this session.
     * @since 10
     */
    int8_t isCompleted;
#endif
};

/**
 * @brief 通过给定的信息OhosImageSource和OhosImageSourceOps结构体，获取JavaScript native层API ImageSource对象。
 *
 * @param env 表明JNI环境的指针。
 * @param src 表明创建一个图像源的信息。
 * @param ops 表明创建一个图像源的选项。
 * @param res 表明JavaScript native层API ImageSource对象的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_SOURCE_DATA_INCOMPLETE：图像源数据不完整。
 *     <br>IMAGE_RESULT_SOURCE_DATA：图像源数据错误。
 *     <br>IMAGE_RESULT_GET_DATA_ABNORMAL：图像获取数据错误。
 *     <br>IMAGE_RESULT_TOO_LARGE：图像数据太大。
 *     <br>IMAGE_RESULT_DECODE_FAILED：解码失败。
 *     <br>IMAGE_RESULT_DECODE_HEAD_ABNORMAL：图像解码头错误。
 *     <br>IMAGE_RESULT_DECODE_EXIF_UNSUPPORT：图像解码EXIF不支持。
 *     <br>IMAGE_RESULT_PROPERTY_NOT_EXIST：图像属性不存在。
 *     <br>IMAGE_RESULT_FILE_DAMAGED：文件损坏。
 *     <br>IMAGE_RESULT_FILE_FD_ERROR：文件FD错误。
 *     <br>IMAGE_RESULT_STREAM_SIZE_ERROR：数据流错误。
 *     <br>IMAGE_RESULT_SEEK_FAILED：查找文件失败。
 *     <br>IMAGE_RESULT_PEEK_FAILED：速览文件失败。
 *     <br>IMAGE_RESULT_FREAD_FAILED：读取文件失败。
 * @see {@link OhosImageSource}, {@link OhosImageSourceOps}
 *
 * @since 10
 * @version 4.0
 * @deprecated since 11
 * @useinstead image#OH_ImageSource_CreateFromUri
 * @useinstead image#OH_ImageSource_CreateFromFd
 * @useinstead image#OH_ImageSource_CreateFromData
 */
int32_t OH_ImageSource_Create(napi_env env, struct OhosImageSource* src,
    struct OhosImageSourceOps* ops, napi_value *res);

/**
 * @brief 通过给定的标识符URI和{@link OhosImageSourceOps}结构体，获取JavaScript native层API ImageSource对象。
 *
 * @param env 表明JNI环境的指针。
 * @param uri 表明图像源资源标识符，接受文件资源或者base64资源。当前文件资源只支持绝对路径。
 * @param size 表明图像源资源URI的长度。
 * @param ops 表明创建一个图像源的选项。
 * @param res 表明JavaScript native层API ImageSource对象的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 * @see {@link OhosImageSourceOps}
 *
 * @since 11
 * @version 4.1
 */
int32_t OH_ImageSource_CreateFromUri(napi_env env, char* uri, size_t size,
    struct OhosImageSourceOps* ops, napi_value *res);

/**
 * @brief 通过给定的文件描述符fd和{@link OhosImageSourceOps}结构体，获取JavaScript native层API ImageSource对象。
 *
 * @param env 表明JNI环境的指针。
 * @param fd 表明图像源文件资源描述符。
 * @param ops 表明创建一个图像源的选项。
 * @param res 表明JavaScript native层API ImageSource对象的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 * @see {@link OhosImageSourceOps}
 *
 * @since 11
 * @version 4.1
 */
int32_t OH_ImageSource_CreateFromFd(napi_env env, int32_t fd,
    struct OhosImageSourceOps* ops, napi_value *res);

/**
 * @brief 通过给定的图像源缓冲区资源data和{@link OhosImageSourceOps}结构体，获取JavaScript native层API ImageSource对象。
 *
 * @param env 表明JNI环境的指针。
 * @param data 表明图像源缓冲区资源，接受格式化包缓冲区或者base64缓冲区。
 * @param dataSize 表明图像源缓冲区资源大小。
 * @param ops 表明创建一个图像源的选项。
 * @param res 表明JavaScript native层API ImageSource对象的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 * @see {@link OhosImageSourceOps}
 *
 * @since 11
 * @version 4.1
 */
int32_t OH_ImageSource_CreateFromData(napi_env env, uint8_t* data, size_t dataSize,
    struct OhosImageSourceOps* ops, napi_value *res);

/**
 * @brief 通过给定的资源描述符{@link RawFileDescriptor}和{@link OhosImageSourceOps}结构体，获取JavaScript native层API ImageSource对象。
 *
 * @param env 表明JNI环境的指针。
 * @param rawFile 表明图像源资源描述符。
 * @param ops 表明创建一个图像源的选项。
 * @param res 表明JavaScript native层API ImageSource对象的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 * @see {@link OhosImageSourceOps}
 *
 * @since 11
 * @version 4.1
 */
int32_t OH_ImageSource_CreateFromRawFile(napi_env env, RawFileDescriptor rawFile,
    struct OhosImageSourceOps* ops, napi_value *res);

/**
 * @brief 通过给定的信息{@link OhosImageSource}和{@link OhosImageSourceOps}结构，获取增量类型的JavaScript Native API ImageSource对象，
 * 图像数据应通过{@link OH_ImageSource_UpdateData}更新。
 *
 * @param env 表明JNI环境的指针。
 * @param source Indicates a pointer to the input resource of the image source. Only the buffer type is accepted.
 *     For details, see {@link OhosImageSource}.
 * @param ops 表明创建一个图像源的选项。
 * @param res 表明JavaScript native层API ImageSource对象的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 * @see {@link OhosImageSource}, {@link OhosImageSourceOps}, {@link OH_ImageSource_UpdateData}
 *
 * @since 10
 * @version 4.0
 * @deprecated since 11
 * @useinstead image#OH_ImageSource_CreateIncrementalFromData
 */
int32_t OH_ImageSource_CreateIncremental(napi_env env, struct OhosImageSource* source,
    struct OhosImageSourceOps* ops, napi_value *res);

/**
 * @brief 通过给定的图像源缓冲区资源data和{@link OhosImageSourceOps}结构体，获取增量类型的JavaScript Native API ImageSource对象，图像数据应通过
 * {@link OH_ImageSource_UpdateData}更新。
 *
 * @param env 表明JNI环境的指针。
 * @param data 表明图像源缓冲区资源，接受格式化包缓冲区或者base64缓冲区。
 * @param dataSize 表明图像源缓冲区资源大小。
 * @param ops 表明创建一个图像源的选项。
 * @param res 表明JavaScript native层API ImageSource对象的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 * @see {@link OhosImageSourceOps}, {@link OH_ImageSource_UpdateData}
 *
 * @since 11
 * @version 4.1
 */
int32_t OH_ImageSource_CreateIncrementalFromData(napi_env env, uint8_t* data, size_t dataSize,
    struct OhosImageSourceOps* ops, napi_value *res);

/**
 * @brief 获取所有支持的解码格式元标记。
 *
 * @param res 表明指向{@link OhosImageSourceSupportedFormatList}结构体的指针。该结构体包含supportedFormatList和size两个属性。
 *     <br>该接口需要调用两次才能正确获取支持的格式列表。
 *     <br>第一次调用需将res->supportedFormatList置空，res->size会获取支持的格式数量。
 *     <br>第二次调用前，需完成内存初始化，首先将res->supportedFormatList初始化为包含res->size个{@link OhosImageSourceSupportedFormat}的列表，再为每个
 *     {@link OhosImageSourceSupportedFormat}申请内存，确保其format属性有足够的空间获取图片格式信息。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_DECODE_FAILED：解码失败。
 *     <br>IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式不对。
 * @see {@link OhosImageSourceSupportedFormatList}, {@link OhosImageSourceSupportedFormat}
 *
 * @since 10
 * @version 4.0
 */
int32_t OH_ImageSource_GetSupportedFormats(struct OhosImageSourceSupportedFormatList* res);

/**
 * @brief 从输入JavaScript native层ImageSource对象中，转换成{@link ImageSourceNative}值。
 *
 * @param env 表明JNI环境的指针。
 * @param source 表明JavaScript native层API ImageSource对象的指针。
 * @return 如果操作成功返回{@link ImageSourceNative}指针；如果操作失败，返回空指针。
 * @see {@link ImageSourceNative}, {@link OH_ImageSource_Release}
 *
 * @since 10
 * @version 4.0
 */
ImageSourceNative* OH_ImageSource_InitNative(napi_env env, napi_value source);

/**
 * @brief 通过一个给定的选项{@link OhosImageDecodingOps}结构体，从ImageSource中解码JavaScript native层PixelMap对象。
 *
 * @param native 表明native层ImageSourceNative值的指针。
 * @param ops 表明为了解码图像源的选项。
 * @param res 表明JavaScript native层PixelMap对象的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_GET_DATA_ABNORMAL：获取图片数据异常。
 *     <br>IMAGE_RESULT_DECODE_FAILED：解码失败。
 *     <br>IMAGE_RESULT_DECODE_HEAD_ABNORMAL：图像解码头错误。
 *     <br>IMAGE_RESULT_CREATE_DECODER_FAILED：创建解码器失败。
 *     <br>IMAGE_RESULT_CREATE_ENCODER_FAILED：创建编码器失败。
 *     <br>IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式不对。
 *     <br>IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia错误。
 *     <br>IMAGE_RESULT_DATA_ABNORMAL：输入图片数据错误。
 *     <br>IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST：共享内存错误。
 *     <br>IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据异常。
 *     <br>IMAGE_RESULT_DECODE_ABNORMAL：图片解码异常。
 *     <br>IMAGE_RESULT_MALLOC_ABNORMAL：图像错误。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图片初始化错误。
 *     <br>IMAGE_RESULT_INIT_ABNORMAL：图片输入数据错误。
 *     <br>IMAGE_RESULT_CROP：裁剪错误。
 *     <br>IMAGE_RESULT_UNKNOWN_FORMAT：图片格式未知。
 *     <br>IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。
 *     <br>IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。
 *     <br>IMAGE_RESULT_ENCODE_FAILED：增加位图失败。
 *     <br>IMAGE_RESULT_HW_DECODE_UNSUPPORT：不支持图片硬解码。
 *     <br>IMAGE_RESULT_HW_DECODE_FAILED：硬解码失败。
 *     <br>IMAGE_RESULT_ERR_IPC：ipc失败。
 *     <br>IMAGE_RESULT_INDEX_INVALID：索引无效。
 *     <br>IMAGE_RESULT_ALPHA_TYPE_ERROR：硬解码失败。
 *     <br>IMAGE_RESULT_ALLOCATER_TYPE_ERROR：硬解码失败。
 * @see {@link ImageSourceNative}, {@link OhosImageDecodingOps}
 *
 * @since 10
 * @version 4.0
 */
int32_t OH_ImageSource_CreatePixelMap(const ImageSourceNative* native,
    struct OhosImageDecodingOps* ops, napi_value *res);

/**
 * @brief 通过一个给定的选项{@link OhosImageDecodingOps}结构体，从ImageSource中解码所有的JavaScript native层PixelMap对象列表。
 *
 * @param native 表明native层ImageSourceNative值的指针。
 * @param ops 表明为了解码图像源的选项。
 * @param res 表明JavaScript native层PixelMap列表对象的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_GET_DATA_ABNORMAL：获取图片数据异常。
 *     <br>IMAGE_RESULT_DECODE_FAILED：解码失败。
 *     <br>IMAGE_RESULT_DECODE_HEAD_ABNORMAL：图像解码头错误。
 *     <br>IMAGE_RESULT_CREATE_DECODER_FAILED：创建解码器失败。
 *     <br>IMAGE_RESULT_CREATE_ENCODER_FAILED：创建编码器失败。
 *     <br>IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式不对。
 *     <br>IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia错误。
 *     <br>IMAGE_RESULT_DATA_ABNORMAL：输入图片数据错误。
 *     <br>IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST：共享内存错误。
 *     <br>IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据异常。
 *     <br>IMAGE_RESULT_DECODE_ABNORMAL：图片解码异常。
 *     <br>IMAGE_RESULT_MALLOC_ABNORMAL：图像错误。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图片初始化错误。
 *     <br>IMAGE_RESULT_INIT_ABNORMAL：图片输入数据错误。
 *     <br>IMAGE_RESULT_CROP：裁剪错误。
 *     <br>IMAGE_RESULT_UNKNOWN_FORMAT：图片格式未知。
 *     <br>IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。
 *     <br>IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。
 *     <br>IMAGE_RESULT_ENCODE_FAILED：增加位图失败。
 *     <br>IMAGE_RESULT_HW_DECODE_UNSUPPORT：不支持图片硬解码。
 *     <br>IMAGE_RESULT_HW_DECODE_FAILED：硬解码失败。
 *     <br>IMAGE_RESULT_ERR_IPC：ipc失败。
 *     <br>IMAGE_RESULT_INDEX_INVALID：索引无效。
 *     <br>IMAGE_RESULT_ALPHA_TYPE_ERROR：硬解码失败。
 *     <br>IMAGE_RESULT_ALLOCATER_TYPE_ERROR：硬解码失败。
 *     <br>IMAGE_RESULT_DECODE_EXIF_UNSUPPORT：解码的EXIF不支持。
 *     <br>IMAGE_RESULT_PROPERTY_NOT_EXIST：图片属性不存在。
 * @see {@link ImageSourceNative}, {@link OhosImageDecodingOps}
 *
 * @since 10
 * @version 4.0
 */
int32_t OH_ImageSource_CreatePixelMapList(const ImageSourceNative* native,
    struct OhosImageDecodingOps* ops, napi_value *res);

/**
 * @brief 从ImageSource（如GIF图像源）获取延迟时间列表。
 *
 * @param native 表明native层ImageSourceNative值的指针。
 * @param res 表明延迟时间列表OhosImageSourceDelayTimeList的指针。
 *     <br>当输入的res中delayTimeList是空指针并且size是0时，将通过res的size中返回延迟时间列表大小为了获取延迟时间，需要比返回的delayTimeList大小值大的足够空间。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_GET_DATA_ABNORMAL：获取图片数据异常。
 *     <br>IMAGE_RESULT_DECODE_FAILED：解码失败。
 *     <br>IMAGE_RESULT_DECODE_HEAD_ABNORMAL：图像解码头错误。
 *     <br>IMAGE_RESULT_CREATE_DECODER_FAILED：创建解码器失败。
 *     <br>IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia错误。
 *     <br>IMAGE_RESULT_DATA_ABNORMAL：输入图片数据错误。
 *     <br>IMAGE_RESULT_DECODE_ABNORMAL：图片解码异常。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图片初始化错误。
 *     <br>IMAGE_RESULT_UNKNOWN_FORMAT：图片格式未知。
 *     <br>IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。
 *     <br>IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。
 *     <br>IMAGE_RESULT_INDEX_INVALID：索引无效。
 *     <br>IMAGE_RESULT_DECODE_EXIF_UNSUPPORT：解码的EXIF不支持。
 *     <br>IMAGE_RESULT_PROPERTY_NOT_EXIST：图片属性不存在。
 * @see {@link ImageSourceNative}, {@link OhosImageSourceDelayTimeList}
 *
 * @since 10
 * @version 4.0
 */
int32_t OH_ImageSource_GetDelayTime(const ImageSourceNative* native,
    struct OhosImageSourceDelayTimeList* res);

/**
 * @brief 从ImageSource中获取帧计数。
 *
 * @param native 表明native层ImageSourceNative值的指针。
 * @param res 表明帧计数的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_GET_DATA_ABNORMAL：获取图片数据异常。
 *     <br>IMAGE_RESULT_DECODE_FAILED：解码失败。
 *     <br>IMAGE_RESULT_DECODE_HEAD_ABNORMAL：图像解码头错误。
 *     <br>IMAGE_RESULT_CREATE_DECODER_FAILED：创建解码器失败。
 *     <br>IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia错误。
 *     <br>IMAGE_RESULT_DATA_ABNORMAL：输入图片数据错误。
 *     <br>IMAGE_RESULT_DECODE_ABNORMAL：图片解码异常。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图片初始化错误。
 *     <br>IMAGE_RESULT_UNKNOWN_FORMAT：图片格式未知。
 *     <br>IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。
 *     <br>IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。
 *     <br>IMAGE_RESULT_INDEX_INVALID：索引无效。
 *     <br>IMAGE_RESULT_DECODE_EXIF_UNSUPPORT：解码的EXIF不支持。
 *     <br>IMAGE_RESULT_PROPERTY_NOT_EXIST：图片属性不存在。
 * @see {@link ImageSourceNative}
 *
 * @since 10
 * @version 4.0
 */
int32_t OH_ImageSource_GetFrameCount(const ImageSourceNative* native, uint32_t *res);

/**
 * @brief 通过索引从ImageSource获取图像源信息。
 *
 * @param native 表明native层ImageSourceNative值的指针。
 * @param index 表明帧计数的指针。
 * @param info 表明图像源信息OhosImageSourceInfo的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_GET_DATA_ABNORMAL：获取图片数据异常。
 *     <br>IMAGE_RESULT_DECODE_FAILED：解码失败。
 *     <br>IMAGE_RESULT_DECODE_HEAD_ABNORMAL：图像解码头错误。
 *     <br>IMAGE_RESULT_CREATE_DECODER_FAILED：创建解码器失败。
 *     <br>IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia错误。
 *     <br>IMAGE_RESULT_DATA_ABNORMAL：输入图片数据错误。
 *     <br>IMAGE_RESULT_DECODE_ABNORMAL：图片解码异常。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图片初始化错误。
 *     <br>IMAGE_RESULT_UNKNOWN_FORMAT：图片格式未知。
 *     <br>IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。
 *     <br>IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。
 *     <br>IMAGE_RESULT_INDEX_INVALID：索引无效。
 *     <br>IMAGE_RESULT_DECODE_EXIF_UNSUPPORT：解码的EXIF不支持。
 *     <br>IMAGE_RESULT_PROPERTY_NOT_EXIST：图片属性不存在。
 * @see {@link ImageSourceNative}, {@link OhosImageSourceInfo}
 *
 * @since 10
 * @version 4.0
 */
int32_t OH_ImageSource_GetImageInfo(const ImageSourceNative* native, int32_t index,
    struct OhosImageSourceInfo* info);

/**
 * @brief 通过关键字从ImageSource中获取图像源属性。
 *
 * @param native 表明native层ImageSourceNative值的指针。
 * @param key 表明属性关键字OhosImageSourceProperty的指针。
 * @param value 表明作为结果的属性值OhosImageSourceProperty的指针。当输入的value中value是空指针并且size是0时，将通过value中的size返回属性值的大小。为了获取属性值，
 *     需要比value中的结果大小大的足够的空间。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_GET_DATA_ABNORMAL：获取图片数据异常。
 *     <br>IMAGE_RESULT_DECODE_FAILED：解码失败。
 *     <br>IMAGE_RESULT_DECODE_HEAD_ABNORMAL：图像解码头错误。
 *     <br>IMAGE_RESULT_CREATE_DECODER_FAILED：创建解码器失败。
 *     <br>IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia错误。
 *     <br>IMAGE_RESULT_DATA_ABNORMAL：输入图片数据错误。
 *     <br>IMAGE_RESULT_DECODE_ABNORMAL：图片解码异常。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图片初始化错误。
 *     <br>IMAGE_RESULT_UNKNOWN_FORMAT：图片格式未知。
 *     <br>IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。
 *     <br>IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。
 *     <br>IMAGE_RESULT_INDEX_INVALID：索引无效。
 *     <br>IMAGE_RESULT_DECODE_EXIF_UNSUPPORT：解码的EXIF不支持。
 *     <br>IMAGE_RESULT_PROPERTY_NOT_EXIST：图片属性不存在。
 * @see {@link ImageSourceNative}, {@link OhosImageSourceProperty}
 *
 * @since 10
 * @version 4.0
 */
int32_t OH_ImageSource_GetImageProperty(const ImageSourceNative* native,
    struct OhosImageSourceProperty* key, struct OhosImageSourceProperty* value);

/**
 * @brief 通过关键字为ImageSource修改图像源属性。
 *
 * @param native 表明native层ImageSourceNative值的指针。
 * @param key 表明属性关键字OhosImageSourceProperty的指针。
 * @param value 为了修改表明属性值OhosImageSourceProperty的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_GET_DATA_ABNORMAL：获取图片数据异常。
 *     <br>IMAGE_RESULT_DECODE_FAILED：解码失败。
 *     <br>IMAGE_RESULT_DECODE_HEAD_ABNORMAL：图像解码头错误。
 *     <br>IMAGE_RESULT_CREATE_DECODER_FAILED：创建解码器失败。
 *     <br>IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia错误。
 *     <br>IMAGE_RESULT_DATA_ABNORMAL：输入图片数据错误。
 *     <br>IMAGE_RESULT_DECODE_ABNORMAL：图片解码异常。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图片初始化错误。
 *     <br>IMAGE_RESULT_UNKNOWN_FORMAT：图片格式未知。
 *     <br>IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。
 *     <br>IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。
 *     <br>IMAGE_RESULT_INDEX_INVALID：索引无效。
 *     <br>IMAGE_RESULT_DECODE_EXIF_UNSUPPORT：解码的EXIF不支持。
 *     <br>IMAGE_RESULT_PROPERTY_NOT_EXIST：图片属性不存在。
 * @see {@link ImageSourceNative}, {@link OhosImageSourceProperty}
 *
 * @since 10
 * @version 4.0
 */
int32_t OH_ImageSource_ModifyImageProperty(const ImageSourceNative* native,
    struct OhosImageSourceProperty* key, struct OhosImageSourceProperty* value);

/**
 * @brief 为了增量类型的ImageSource更新源数据。
 *
 * @param native 表明native层ImageSourceNative值的指针。
 * @param data 表明更新数据信息OhosImageSourceUpdateData的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_GET_DATA_ABNORMAL：获取图片数据异常。
 *     <br>IMAGE_RESULT_DECODE_FAILED：解码失败。
 *     <br>IMAGE_RESULT_DECODE_HEAD_ABNORMAL：图像解码头错误。
 *     <br>IMAGE_RESULT_CREATE_DECODER_FAILED：创建解码器失败。
 *     <br>IMAGE_RESULT_CREATE_ENCODER_FAILED：创建编码器失败。
 *     <br>IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式不对。
 *     <br>IMAGE_RESULT_THIRDPART_SKIA_ERROR：Skia第三方库出错。
 *     <br>IMAGE_RESULT_DATA_ABNORMAL：输入图片数据错误。
 *     <br>IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST：共享内存不存在。
 *     <br>IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据异常。
 *     <br>IMAGE_RESULT_DECODE_ABNORMAL：图片解码异常。
 *     <br>IMAGE_RESULT_MALLOC_ABNORMAL：图像内存分配异常。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图片初始化错误。
 *     <br>IMAGE_RESULT_INIT_ABNORMAL：图片输入数据错误。
 *     <br>IMAGE_RESULT_CROP：裁剪失败。
 *     <br>IMAGE_RESULT_UNKNOWN_FORMAT：图片格式未知。
 *     <br>IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。
 *     <br>IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。
 *     <br>IMAGE_RESULT_ENCODE_FAILED：增加位图失败。
 *     <br>IMAGE_RESULT_HW_DECODE_UNSUPPORT：不支持图片硬解码。
 *     <br>IMAGE_RESULT_HW_DECODE_FAILED：硬解码失败。
 *     <br>IMAGE_RESULT_ERR_IPC：IPC操作失败。
 *     <br>IMAGE_RESULT_INDEX_INVALID：索引无效。
 *     <br>IMAGE_RESULT_ALPHA_TYPE_ERROR：Alpha类型错误。
 *     <br>IMAGE_RESULT_ALLOCATER_TYPE_ERROR：内存分配器类型错误。
 * @see {@link ImageSourceNative}, {@link OhosImageSourceUpdateData}
 *
 * @since 10
 * @version 4.0
 */
int32_t OH_ImageSource_UpdateData(const ImageSourceNative* native, struct OhosImageSourceUpdateData* data);


/**
 * @brief 释放native层图像源ImageSourceNative。
 *
 * @param native 表明native层ImageSourceNative值的指针。
 * @return 参考{@link IRNdkErrCode}：
 *     <br>OHOS_IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI 环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_GET_DATA_ABNORMAL：获取图片数据异常。
 *     <br>IMAGE_RESULT_DATA_ABNORMAL：输入图片数据错误。
 * @see {@link ImageSourceNative}, {@link OH_ImageSource_Create}, {@link OH_ImageSource_CreateIncremental}
 *
 * @since 10
 * @version 4.0
 */
int32_t OH_ImageSource_Release(ImageSourceNative* native);
#ifdef __cplusplus
};
#endif
#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_SOURCE_MDK_H_
/** @} */

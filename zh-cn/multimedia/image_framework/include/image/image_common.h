/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup Image_NativeModule
 * @{
 *
 * @brief Provides APIs for access to the image interface.
 *
 * @since 12
 */

/**
 * @file image_common.h
 *
 * @brief 声明图像接口使用的公共枚举和结构体。
 * 
 * @library libimage_common.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 12
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_IMAGE_COMMON_H_
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_IMAGE_COMMON_H_
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 图像大小结构体。
 *
 * @since 12
 */
struct Image_Size {
    /**
     * 图片的宽，单位：像素。
     */
    uint32_t width;
    /**
     * 图片的高，单位：像素。
     */
    uint32_t height;
};

/**
 * @brief 图像大小结构体。
 *
 * @since 12
 */
typedef struct Image_Size Image_Size;

/**
 * @brief 待解码的图像源区域结构体。
 *
 * @since 12
 */
struct Image_Region {
    /**
     * 区域横坐标，不能大于原图的宽度。
     */
    uint32_t x;
    /**
     * 区域纵坐标，不能大于原图的高度。
     */
    uint32_t y;
    /**
     * 输出图片的宽，单位：像素。
     */
    uint32_t width;
    /**
     * 输出图片的高，单位：像素。
     */
    uint32_t height;
};

/**
 * @brief 待解码的图像源区域结构体。
 *
 * @since 12
 */
typedef struct Image_Region Image_Region;

/**
 * @brief Defines the area of the image pixels to read or write.
 *
 * @since 22
 */
typedef struct Image_PositionArea {
    /** Image pixels data that will be read or written. */
    uint8_t *pixels;
    /** Length of the image pixels data. */
    size_t pixelsSize;
    /** Offset for data reading or writing. */
    uint32_t offset;
    /** Number of bytes per row of the region. */
    uint32_t stride;
    /** Region to read or write. */
    Image_Region region;
} Image_PositionArea;

/**
 * @brief Defines the image scale ratio.
 *
 * @since 22
 */
typedef struct Image_Scale {
    /** Scale ratio on the x-axis. */
    float x;
     /** Scale ratio on the y-axis. */
    float y;
} Image_Scale;

#ifdef __cplusplus
/**
 * @brief 字符串结构，用于描述字符串数据地址和数据长度。Image_MimeType是Image_String的别名，用于表示MIME类型。<br>作为输入参数使用时，调用方负责保证data和size有效；作为输出参数使用时，
 * data的分配和释放方式以具体接口说明为准。
 * 
 * @since 12
 */
struct Image_String {
    /** data for string type */
    char *data = nullptr;
    /** data length for string type */
    size_t size = 0;
};
#else
/**
 * @brief 字符串结构，用于描述字符串数据地址和数据长度。Image_MimeType是Image_String的别名，用于表示MIME类型。<br>作为输入参数使用时，调用方负责保证data和size有效；作为输出参数使用时，
 * data的分配和释放方式以具体接口说明为准。
 * 
 * @since 12
 */
struct Image_String {
    /** data for string type */
    char *data;
    /** data length for string type */
    size_t size;
};
#endif

/**
 * @brief OH_PictureMetadata用于承载Picture元数据。<br>有多种方式创建和获取OH_PictureMetadata：<br>| 函数 | 描述 || -- | -- ||
 * {@link OH_PictureMetadata_Create()} | 创建OH_PictureMetadata指针。 || {@link OH_PictureMetadata_Clone()} | 拷贝元数据。 ||
 * {@link OH_PictureNative_GetMetadata()} | 获取主图的元数据。 || {@link OH_AuxiliaryPictureNative_GetMetadata()} | 获取辅助图的元数据。 |<
 * br>使用{@link OH_PictureMetadata_Release()}函数释放OH_PictureMetadata对象。<br>资源管理：通过{@link OH_PictureMetadata_Create()}、
 * {@link OH_PictureMetadata_Clone()}、{@link OH_PictureNative_GetMetadata()}或
 * {@link OH_AuxiliaryPictureNative_GetMetadata()}获取到的OH_PictureMetadata对象由调用方管理，使用完成后应调用
 * {@link OH_PictureMetadata_Release()}释放。通过{@link OH_PictureNative_SetMetadata()}或
 * {@link OH_AuxiliaryPictureNative_SetMetadata()}设置元数据时，接口不会释放传入的OH_PictureMetadata对象。<br>
 * OH_PictureMetadata结构体内容和操作方式如下：<br>| 字段类型 | 字段名称 | 字段描述 | 字段获取函数 | 字段设置函数 || -- | -- | -- | -- | -- ||
 * {@link Image_String} | property | 元数据属性。 | {@link OH_PictureMetadata_GetProperty()}、
 * {@link OH_PictureMetadata_GetPropertyWithNull()} | {@link OH_PictureMetadata_SetProperty()} || OH_PictureMetadata |
 * metadata | 元数据对象副本。 | {@link OH_PictureMetadata_Clone()} | - |
 * 
 * @since 13
 */
struct OH_PictureMetadata;

/**
 * @brief OH_PictureMetadata用于承载Picture元数据。<br>有多种方式创建和获取OH_PictureMetadata：<br>| 函数 | 描述 || -- | -- ||
 * {@link OH_PictureMetadata_Create()} | 创建OH_PictureMetadata指针。 || {@link OH_PictureMetadata_Clone()} | 拷贝元数据。 ||
 * {@link OH_PictureNative_GetMetadata()} | 获取主图的元数据。 || {@link OH_AuxiliaryPictureNative_GetMetadata()} | 获取辅助图的元数据。 |<
 * br>使用{@link OH_PictureMetadata_Release()}函数释放OH_PictureMetadata对象。<br>资源管理：通过{@link OH_PictureMetadata_Create()}、
 * {@link OH_PictureMetadata_Clone()}、{@link OH_PictureNative_GetMetadata()}或
 * {@link OH_AuxiliaryPictureNative_GetMetadata()}获取到的OH_PictureMetadata对象由调用方管理，使用完成后应调用
 * {@link OH_PictureMetadata_Release()}释放。通过{@link OH_PictureNative_SetMetadata()}或
 * {@link OH_AuxiliaryPictureNative_SetMetadata()}设置元数据时，接口不会释放传入的OH_PictureMetadata对象。<br>
 * OH_PictureMetadata结构体内容和操作方式如下：<br>| 字段类型 | 字段名称 | 字段描述 | 字段获取函数 | 字段设置函数 || -- | -- | -- | -- | -- ||
 * {@link Image_String} | property | 元数据属性。 | {@link OH_PictureMetadata_GetProperty()}、
 * {@link OH_PictureMetadata_GetPropertyWithNull()} | {@link OH_PictureMetadata_SetProperty()} || OH_PictureMetadata |
 * metadata | 元数据对象副本。 | {@link OH_PictureMetadata_Clone()} | - |
 * 
 * @since 13
 */
typedef struct OH_PictureMetadata OH_PictureMetadata;

/**
 * @brief 字符串结构，用于描述字符串数据地址和数据长度。Image_MimeType是Image_String的别名，用于表示MIME类型。<br>作为输入参数使用时，调用方负责保证data和size有效；作为输出参数使用时，
 * data的分配和释放方式以具体接口说明为准。
 * 
 * @since 12
 */
typedef struct Image_String Image_String;

/**
 * @brief Defines the image encode format.
 *
 * @since 12
 */
typedef struct Image_String Image_MimeType;

/**
 * @brief 错误码。
 *
 * @since 12
 */
typedef enum {
    /**
     * 操作成功。
     */
    IMAGE_SUCCESS = 0,
    /**
     * 无效参数。
     */
    IMAGE_BAD_PARAMETER = 401,
    /**
     * 不支持的MIME类型。
     */
    IMAGE_UNSUPPORTED_MIME_TYPE = 7600101,
    /**
     * 未知的MIME类型。
     */
    IMAGE_UNKNOWN_MIME_TYPE = 7600102,
    /**
     * 过大的数据或图片。
     */
    IMAGE_TOO_LARGE = 7600103,
    /**
     * @error Failed to get image data.
     * @since 23
     */
    IMAGE_GET_IMAGE_DATA_FAILED = 7600104,
    /**
     * @error PixelMap has been released.
     * @since 26.0.0
     */
    IMAGE_PIXELMAP_RELEASED = 7600105,
    /** @error DMA memory does not exist */
    IMAGE_DMA_NOT_EXIST = 7600173,
    /** @error DMA operation failed */
    IMAGE_DMA_OPERATION_FAILED = 7600174,
    /**
     * 不支持的操作。
     */
    IMAGE_UNSUPPORTED_OPERATION = 7600201,
    /**
     * 不支持的metadata。
     */
    IMAGE_UNSUPPORTED_METADATA = 7600202,
    /**
     * 不支持的转换。
     */
    IMAGE_UNSUPPORTED_CONVERSION = 7600203,
    /**
     * 无效区域。
     */
    IMAGE_INVALID_REGION = 7600204,
    /** @error unsupported memory format
     *  @since 13
     */
    IMAGE_UNSUPPORTED_MEMORY_FORMAT = 7600205,
    /**
     * 无效参数。
     * @since 19
     */
    IMAGE_INVALID_PARAMETER = 7600206,
    /**
     * @error Unsupported data format
     * @since 22
     */
    IMAGE_UNSUPPORTED_DATA_FORMAT = 7600207,
    /**
     * 申请内存失败。
     */
    IMAGE_ALLOC_FAILED = 7600301,
    /**
     * 内存拷贝失败。
     */
    IMAGE_COPY_FAILED = 7600302,
    /**
     * @error memory lock or unlock failed
     * @since 15
     */
    IMAGE_LOCK_UNLOCK_FAILED = 7600303,
    /**
     * @error Initialization failed
     * @since 22
     */
    IMAGE_INIT_FAILED = 7600304,
    /**
     * @error Create PixelMap failed
     * @since 22
     */
    IMAGE_CREATE_PIXELMAP_FAILED = 7600305,
    /**
     * @error Data conversion failed.
     * @since 26.0.0
     */
    IMAGE_DATA_CONVERSION_FAILED = 7600306,
    /**
     * @error unsupported allocator mode, e.g., use share memory to create a HDR image as only
     * DMA supported hdr metadata.
     * @since 20
     */
    IMAGE_ALLOCATOR_MODE_UNSUPPORTED = 7600501,
    /**
     * 未知错误。
     */
    IMAGE_UNKNOWN_ERROR = 7600901,
    /**
     * 解码数据源异常。
     */
    IMAGE_BAD_SOURCE = 7700101,
    /**
     * 图片解码中不支持的MIME类型。
     * @since 15
     */
    IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE = 7700102,
    /**
     * 图像过大。
     * @since 15
     */
    IMAGE_SOURCE_TOO_LARGE = 7700103,
    /**
     * 不支持的分配器类型。例如，DMA支持HDR元数据，可以使用共享内存解码HDR图像。
     * @since 15
     */
    IMAGE_SOURCE_UNSUPPORTED_ALLOCATOR_TYPE = 7700201,
    /**
     * 不支持的元数据类型。如不支持的属性名或属性值非法。
     * @since 23
     */
    IMAGE_SOURCE_UNSUPPORTED_METADATA = 7700202,
    /** 不支持的选项。例如，无法将图像转换为所需的像素格式。
     * @since 15
     */
    IMAGE_SOURCE_UNSUPPORTED_OPTIONS = 7700203,
    /**
     * 无效参数。
     * @since 19
     */
    IMAGE_SOURCE_INVALID_PARAMETER = 7700204,
    /**
     * 解码失败。
     */
    IMAGE_DECODE_FAILED = 7700301,
    /**
     * 内存申请失败。
     * @since 15
     */
    IMAGE_SOURCE_ALLOC_FAILED = 7700302,
    /**
     * ImagePacker的无效参数。
     * @since 19
     */
    IMAGE_PACKER_INVALID_PARAMETER = 7800202,
    /**
     * 编码失败。
     */
    IMAGE_ENCODE_FAILED = 7800301,
    /**
     * ImageReceiver的无效参数。
     * @since 20
     */
    IMAGE_RECEIVER_INVALID_PARAMETER = 7900201
} Image_ErrorCode;

/**
 * @brief 定义元数据类型。
 * 
 * @since 13
 */
typedef enum {
    /**
     * EXIF元数据。 
     * @since 13
     */
    EXIF_METADATA = 1,

    /**
     * 水印裁剪图元数据。 
     * @since 13
     */
    FRAGMENT_METADATA = 2,

    /**
     * GIF图片元数据。 
     * @since 20
     */
    GIF_METADATA = 5
} Image_MetadataType;

/**
 * @brief Type of allocator used to allocate memory of a PixelMap.
 *
 * @since 20
 */
typedef enum {
    /**
     * The system determines which memory to use to create the PixelMap.
     *
     * @since 20
     */
    IMAGE_ALLOCATOR_MODE_AUTO = 0,
    /**
     * Use DMA buffer to create the PixelMap.
     *
     * @since 20
     */
    IMAGE_ALLOCATOR_MODE_DMA = 1,
    /**
     * Use share memory to create the PixelMap.
     *
     * @since 20
     */
    IMAGE_ALLOCATOR_MODE_SHARED_MEMORY = 2,
} IMAGE_ALLOCATOR_MODE;

/**
 * @brief 创建OH_PictureMetadata指针。
 * <br>使用约束：metadata不能为空指针。接口返回失败时，输出参数内容不应使用。
 * <br>资源管理：接口成功返回的OH_PictureMetadata对象由调用方管理，使用完成后应调用{@link OH_PictureMetadata_Release}释放。
 * 
 * @param metadataType 元数据的类型。
 * @param metadata 指向OH_PictureMetadata对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_PictureMetadata_Create(Image_MetadataType metadataType, OH_PictureMetadata **metadata);

/**
 * @brief 根据key获取Metadata的单条属性。该接口获取到的value.data缺少字符串结束符'\0'，请谨慎使用。
 * <br>使用约束：metadata、key、key->data和value均不能为空指针，key->size必须大于0。接口返回失败时，不应读取value.data。
 * <br>资源管理：接口执行成功后，value.data由接口分配，调用方使用完成后应使用delete[]释放。该接口返回的value.data不以字符串结束符'\0'结尾，如需按C字符串处理，建议使用
 * {@link OH_PictureMetadata_GetPropertyWithNull}。
 * 
 * @param metadata 指向OH_PictureMetadata对象的指针。
 * @param key 属性的键。
 * @param value 属性的值。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_METADATA：不支持的元数据类型，或元数据类型与辅助图片类型不匹配。
 * @since 13
 */
Image_ErrorCode OH_PictureMetadata_GetProperty(OH_PictureMetadata *metadata, Image_String *key, Image_String *value);

/**
 * @brief 获取图片元数据的属性值。输出的value.data以字符串结束符'\0'结尾。
 * <br>使用场景：适用于读取字符串形式的元数据属性值。与{@link OH_PictureMetadata_GetProperty}相比，本接口返回的value.data以'\0'结尾，更适合直接按C字符串处理。
 * <br>使用约束：metadata、key、key->data和value均不能为空指针，key->size必须大于0。接口返回失败时，不应读取value.data。
 * <br>资源管理：接口执行成功后，value.data由接口分配，调用方使用完成后应使用delete[]释放。
 * 
 * @param metadata 将被操作的PictureMetadata指针。
 * @param key 属性键指针。
 * @param value 属性值指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_INVALID_PARAMETER：metadata、key或value为空。
 *     <br>IMAGE_UNSUPPORTED_METADATA：不支持的元数据类型，或元数据类型与辅助图片类型不匹配。
 * @since 19
 */
Image_ErrorCode OH_PictureMetadata_GetPropertyWithNull(OH_PictureMetadata *metadata, Image_String *key, Image_String *value);

/**
 * @brief 根据key修改Metadata的单条属性。
 * <br>使用约束：metadata、key、key->data、value和value->data均不能为空指针，key->size和value->size必须大于0。
 * <br>资源管理：接口会读取传入的key和value内容，不持有调用方传入的Image_String指针。接口返回后，调用方仍需自行管理key和value的生命周期。
 * 
 * @param metadata 指向OH_PictureMetadata对象的指针。
 * @param key 属性的键。
 * @param value 属性的值。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_METADATA：不支持的元数据类型，或元数据类型与辅助图片类型不匹配。
 * @since 13
 */
Image_ErrorCode OH_PictureMetadata_SetProperty(OH_PictureMetadata *metadata, Image_String *key, Image_String *value);

/**
 * @brief 使用二进制数据替换当前元数据。
 *
 * @param metadata 指向OH_PictureMetadata对象的指针。
 * @param blob 指向二进制数据的指针。
 * @param blobSize 二进制数据的大小。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：metadata或blob为空指针、blobSize为0。</li>
 *     <br><li>IMAGE_UNSUPPORTED_METADATA：不支持的元数据类型。</li>
 *     <br><li>IMAGE_UNSUPPORTED_OPERATION：未能设置二进制数据。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureMetadata_SetBlobData(OH_PictureMetadata *metadata, uint8_t *blob, uint32_t blobSize);

/**
 * @brief 获取元数据中blob数据的大小。
 *
 * @param metadata 指向OH_PictureMetadata对象的指针。
 * @param blobSize 指向二进制数据大小的指针。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：metadata或blobSize为空指针。</li>
 *     <br><li>IMAGE_UNSUPPORTED_METADATA：不支持的元数据类型。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureMetadata_GetBlobDataSize(OH_PictureMetadata *metadata, uint32_t *blobSize);

/**
 * @brief 以二进制数据的形式获取元数据。
 *
 * @param metadata 指向OH_PictureMetadata对象的指针。
 * @param blob 指向获取到的二进制数据的指针。
 * @param blobSize 二进制数据的大小。该值必须大于或等于通过OH_PictureMetadata_GetBlobDataSize方法获取的值。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：metadata或blob为空指针、blobSize为0或小于要求。</li>
 *     <br><li>IMAGE_UNSUPPORTED_METADATA：不支持的元数据类型。</li>
 *     <br><li>IMAGE_UNSUPPORTED_OPERATION：无法获取二进制数据。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureMetadata_GetBlobData(OH_PictureMetadata *metadata, uint8_t *blob, uint32_t blobSize);

/**
 * @brief 释放OH_PictureMetadata指针。
 * <br>使用约束：metadata不能为空指针。
 * <br>资源管理：调用该接口后，metadata指向的OH_PictureMetadata对象会被释放，不应继续使用。
 * 
 * @param metadata 被操作的OH_PictureMetadata指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_PictureMetadata_Release(OH_PictureMetadata *metadata);

/**
 * @brief 从OH_PictureMetadata数组中获取与指定类型匹配的PictureMetadata对象。
 *
 * @systemapi
 * @param metadatas 指向OH_PictureMetadata数组的指针。
 * @param metadataCount OH_PictureMetadata数组的长度。
 * @param type 要匹配的目标元数据类型。
 * @param metadata 指向OH_PictureMetadata输出对象的指针，用于存储匹配的内容。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>202：非系统应用程序调用该接口则返回此错误码。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：metadatas或metadata为空指针、数组长度为0。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureMetadata_GetMetadataByType(OH_PictureMetadata **metadatas, uint32_t metadataCount,
    int32_t type, OH_PictureMetadata *metadata);

/**
 * @brief 释放OH_PictureMetadata对象数组。
 *
 * @systemapi
 * @param metadatas 指向OH_PictureMetadata数组的指针。
 * @param metadatasCount OH_PictureMetadata数组的长度。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>202：非系统应用程序调用该接口则返回此错误码。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：metadatas为空指针、数组长度为0。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureMetadatas_Release(OH_PictureMetadata **metadatas, uint32_t metadatasCount);

/**
 * @brief 拷贝元数据。
 * <br>使用约束：oldMetadata和newMetadata均不能为空指针；接口返回失败时，输出参数内容不应使用。
 * <br>资源管理：接口成功返回的newMetadata由调用方管理，使用完成后应调用{@link OH_PictureMetadata_Release}释放。
 * 
 * @param oldMetadata 被操作的OH_PictureMetadata指针。
 * @param newMetadata 拷贝得到的OH_PictureMetadata指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_ALLOC_FAILED：内存分配失败。
 *     <br>IMAGE_COPY_FAILED：内存拷贝失败。
 * @since 13
 */
Image_ErrorCode OH_PictureMetadata_Clone(OH_PictureMetadata *oldMetadata, OH_PictureMetadata **newMetadata);

/**
 * @brief bmp图片格式。
 *
 * @since 12
 */
static const char* MIME_TYPE_BMP = "image/bmp";

/**
 * @brief jpeg图片格式。
 *
 * @since 12
 */
static const char* MIME_TYPE_JPEG = "image/jpeg";

/**
 * @brief heic图片格式。
 *
 * @since 12
 */
static const char* MIME_TYPE_HEIC = "image/heic";

/**
 * @brief png图片格式。
 *
 * @since 12
 */
static const char* MIME_TYPE_PNG = "image/png";

/**
 * @brief webp图片格式。
 *
 * @since 12
 */
static const char* MIME_TYPE_WEBP = "image/webp";

/**
 * @brief gif图片格式。
 *
 * @since 12
 */
static const char* MIME_TYPE_GIF = "image/gif";

/**
 * @brief ico图片格式。
 *
 * @since 12
 */
static const char* MIME_TYPE_ICON = "image/x-icon";

/**
 * @brief 每个像素比特数。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_BITS_PER_SAMPLE = "BitsPerSample";

/**
 * @brief 图片方向。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_ORIENTATION = "Orientation";

/**
 * @brief 图片长度。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_IMAGE_LENGTH = "ImageLength";

/**
 * @brief 图片宽度。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_IMAGE_WIDTH = "ImageWidth";

/**
 * @brief 图片纬度。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_LATITUDE = "GPSLatitude";

/**
 * @brief 图片经度。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_LONGITUDE = "GPSLongitude";

/**
 * @brief 纬度引用，例如N或S。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_LATITUDE_REF = "GPSLatitudeRef";

/**
 * @brief 经度引用，例如W或E。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_LONGITUDE_REF = "GPSLongitudeRef";

/**
 * @brief 拍摄时间，例如2022:09:06 15:48:00。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_DATE_TIME_ORIGINAL = "DateTimeOriginal";

/**
 * @brief 曝光时间，例如1/33 sec。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_EXPOSURE_TIME = "ExposureTime";

/**
 * @brief 拍摄场景模式，例如人像、风光、运动、夜景等。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SCENE_TYPE = "SceneType";

/**
 * @brief ISO感光度，例如400。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_ISO_SPEED_RATINGS = "ISOSpeedRatings";

/**
 * @brief 光圈值，例如f/1.8。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_F_NUMBER = "FNumber";

/**
 * @brief 用于压缩图像的压缩模式，单位为每像素位数。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_COMPRESSED_BITS_PER_PIXEL = "CompressedBitsPerPixel";

/**
 * @brief 图像压缩方案。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_COMPRESSION = "Compression";

/**
 * @brief 像素构成，例如RGB或YCbCr。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_PHOTOMETRIC_INTERPRETATION = "PhotometricInterpretation";

/**
 * @brief 每个strip的字节偏移量。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_STRIP_OFFSETS = "StripOffsets";

/**
 * @brief 每个像素的分量数。由于该标准适用于RGB和YCbCr图像，因此该标签的值设置为3。在JPEG压缩数据中，使用JPEG标记代替该标签。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SAMPLES_PER_PIXEL = "SamplesPerPixel";

/**
 * @brief 每个strip的图像数据行数。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_ROWS_PER_STRIP = "RowsPerStrip";

/**
 * @brief 每个图像数据带的总字节数。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_STRIP_BYTE_COUNTS = "StripByteCounts";

/**
 * @brief 图像宽度方向的分辨率。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_X_RESOLUTION = "XResolution";

/**
 * @brief 图像高度方向的分辨率。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_Y_RESOLUTION = "YResolution";

/**
 * @brief 表示像素组件的记录格式，chunky格式或是planar格式。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_PLANAR_CONFIGURATION = "PlanarConfiguration";

/**
 * @brief 用于测量XResolution和YResolution的单位。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_RESOLUTION_UNIT = "ResolutionUnit";

/**
 * @brief 图像的传递函数，通常用于颜色校正。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_TRANSFER_FUNCTION = "TransferFunction";

/**
 * @brief 用于生成图像的软件的名称和版本。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SOFTWARE = "Software";

/**
 * @brief 创建图像的用户名称。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_ARTIST = "Artist";

/**
 * @brief 图像的白点色度。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_WHITE_POINT = "WhitePoint";

/**
 * @brief 图像的主要颜色的色度。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_PRIMARY_CHROMATICITIES = "PrimaryChromaticities";

/**
 * @brief 从RGB到YCbCr图像数据的转换矩阵系数。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_YCBCR_COEFFICIENTS = "YCbCrCoefficients";

/**
 * @brief 色度分量与亮度分量的采样比率。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_YCBCR_SUB_SAMPLING = "YCbCrSubSampling";

/**
 * @brief 色度分量相对于亮度分量的位置。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_YCBCR_POSITIONING = "YCbCrPositioning";

/**
 * @brief 参考黑点值和参考白点值。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_REFERENCE_BLACK_WHITE = "ReferenceBlackWhite";

/**
 * @brief 图像的版权信息。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_COPYRIGHT = "Copyright";

/**
 * @brief JPEG压缩缩略图数据开始字节（SOI）的偏移。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_JPEG_INTERCHANGE_FORMAT = "JPEGInterchangeFormat";

/**
 * @brief JPEG压缩缩略图数据的字节数。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_JPEG_INTERCHANGE_FORMAT_LENGTH = "JPEGInterchangeFormatLength";

/**
 * @brief 拍照时相机用来设置曝光的程序的类别。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_EXPOSURE_PROGRAM = "ExposureProgram";

/**
 * @brief 表示所用相机的每个通道的光谱灵敏度。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SPECTRAL_SENSITIVITY = "SpectralSensitivity";

/**
 * @brief 表示ISO 14524中规定的光电转换函数（OECF）。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_OECF = "OECF";

/**
 * @brief 支持的Exif标准版本。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_EXIF_VERSION = "ExifVersion";

/**
 * @brief 图像作为数字数据存储的日期和时间，格式为YYYY:MM:DD HH:MM:SS。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_DATE_TIME_DIGITIZED = "DateTimeDigitized";

/**
 * @brief 压缩数据的特定信息。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_COMPONENTS_CONFIGURATION = "ComponentsConfiguration";

/**
 * @brief 快门速度，以APEX（摄影曝光的加法系统）值表示。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SHUTTER_SPEED_VALUE = "ShutterSpeedValue";

/**
 * @brief 图像的亮度值，以APEX单位表示。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_BRIGHTNESS_VALUE = "BrightnessValue";

/**
 * @brief 最小F数镜头。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_MAX_APERTURE_VALUE = "MaxApertureValue";

/**
 * @brief 测量单位为米的主体距离。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SUBJECT_DISTANCE = "SubjectDistance";

/**
 * @brief 该标签指示整个场景中主要主体的位置和区域。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SUBJECT_AREA = "SubjectArea";

/**
 * @brief Exif/DCF制造商使用的标签，用于记录任何所需信息。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_MAKER_NOTE = "MakerNote";

/**
 * @brief 用于为DateTime标签记录秒的分数的标签。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SUBSEC_TIME = "SubsecTime";

/**
 * @brief 用于为DateTimeOriginal标签记录秒的分数的标签。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SUBSEC_TIME_ORIGINAL = "SubsecTimeOriginal";

/**
 * @brief 用于为DateTimeDigitized标签记录秒的分数的标签。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SUBSEC_TIME_DIGITIZED = "SubsecTimeDigitized";

/**
 * @brief 该标签表示FPXR文件支持的Flashpix格式版本，增强了设备兼容性。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FLASHPIX_VERSION = "FlashpixVersion";

/**
 * @brief 色彩空间信息标签，通常记录为色彩空间指定符。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_COLOR_SPACE = "ColorSpace";

/**
 * @brief 与图像数据相关的音频文件的名称。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_RELATED_SOUND_FILE = "RelatedSoundFile";

/**
 * @brief 图像捕获时的闪光能量，以BCPS表示。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FLASH_ENERGY = "FlashEnergy";

/**
 * @brief 相机或输入设备的空间频率表。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SPATIAL_FREQUENCY_RESPONSE = "SpatialFrequencyResponse";

/**
 * @brief 图像宽度中每FocalPlaneResolutionUnit的像素。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FOCAL_PLANE_X_RESOLUTION = "FocalPlaneXResolution";

/**
 * @brief 图像高度中每FocalPlaneResolutionUnit的像素。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FOCAL_PLANE_Y_RESOLUTION = "FocalPlaneYResolution";

/**
 * @brief 测量FocalPlaneXResolution和FocalPlaneYResolution的单位。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FOCAL_PLANE_RESOLUTION_UNIT = "FocalPlaneResolutionUnit";

/**
 * @brief 主要对象相对于左边缘的位置。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SUBJECT_LOCATION = "SubjectLocation";

/**
 * @brief 捕获时选定的曝光指数。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_EXPOSURE_INDEX = "ExposureIndex";

/**
 * @brief 相机上的图像传感器类型。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SENSING_METHOD = "SensingMethod";

/**
 * @brief 表明图像来源。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FILE_SOURCE = "FileSource";

/**
 * @brief 图像传感器的色彩滤光片几何图案。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_CFA_PATTERN = "CFAPattern";

/**
 * @brief 指示图像数据上的特殊处理。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_CUSTOM_RENDERED = "CustomRendered";

/**
 * @brief 拍摄时设置的曝光模式。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_EXPOSURE_MODE = "ExposureMode";

/**
 * @brief 捕获时的数字变焦比率。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_DIGITAL_ZOOM_RATIO = "DigitalZoomRatio";

/**
 * @brief 捕获的场景类型。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SCENE_CAPTURE_TYPE = "SceneCaptureType";

/**
 * @brief 整体图像增益调整的程度。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GAIN_CONTROL = "GainControl";

/**
 * @brief 相机应用的对比度处理方向。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_CONTRAST = "Contrast";

/**
 * @brief 相机应用的饱和度处理方向。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SATURATION = "Saturation";

/**
 * @brief 相机应用的锐度处理方向。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SHARPNESS = "Sharpness";

/**
 * @brief 特定相机模型的拍照条件信息。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_DEVICE_SETTING_DESCRIPTION = "DeviceSettingDescription";

/**
 * @brief 表示主体到相机的距离范围。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SUBJECT_DISTANCE_RANGE = "SubjectDistanceRange";

/**
 * @brief 为每张图片唯一分配的标识符。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_IMAGE_UNIQUE_ID = "ImageUniqueID";

/**
 * @brief GPSInfoIFD的版本。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_VERSION_ID = "GPSVersionID";

/**
 * @brief 用于GPS高度的参照高度。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_ALTITUDE_REF = "GPSAltitudeRef";

/**
 * @brief 用于GPS高度的参照高度。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_ALTITUDE = "GPSAltitude";

/**
 * @brief 用于测量的GPS卫星。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_SATELLITES = "GPSSatellites";

/**
 * @brief 录制图像时GPS接收器的状态。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_STATUS = "GPSStatus";

/**
 * @brief GPS测量模式。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_MEASURE_MODE = "GPSMeasureMode";

/**
 * @brief GPS DOP（数据精度等级）。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_DOP = "GPSDOP";

/**
 * @brief 用来表示GPS接收器移动速度的单位。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_SPEED_REF = "GPSSpeedRef";

/**
 * @brief 用来表示GPS接收器移动速度的单位。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_SPEED = "GPSSpeed";

/**
 * @brief GPS接收机移动方向的参照。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_TRACK_REF = "GPSTrackRef";

/**
 * @brief GPS接收机移动方向的参照。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_TRACK = "GPSTrack";

/**
 * @brief 图像方向的参照。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_IMG_DIRECTION_REF = "GPSImgDirectionRef";

/**
 * @brief 图像方向的参照。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_IMG_DIRECTION = "GPSImgDirection";

/**
 * @brief GPS接收器使用的大地测量数据。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_MAP_DATUM = "GPSMapDatum";

/**
 * @brief 目的地点的纬度参照。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_DEST_LATITUDE_REF = "GPSDestLatitudeRef";

/**
 * @brief 目的地点的纬度参照。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_DEST_LATITUDE = "GPSDestLatitude";

/**
 * @brief 目的地点的经度参照。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_DEST_LONGITUDE_REF = "GPSDestLongitudeRef";

/**
 * @brief 记录定位方法名的字符串。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_PROCESSING_METHOD = "GPSProcessingMethod";

/**
 * @brief 记录GPS区域名的字符串。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_AREA_INFORMATION = "GPSAreaInformation";

/**
 * @brief 此字段表示GPS数据是否应用了差分校正，对于精确的位置准确性至关重要。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_DIFFERENTIAL = "GPSDifferential";

/**
 * @brief 相机机身的序列号。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_BODY_SERIAL_NUMBER = "BodySerialNumber";

/**
 * @brief 相机所有者的姓名。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_CAMERA_OWNER_NAME = "CameraOwnerName";

/**
 * @brief 相机所有者的姓名。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_COMPOSITE_IMAGE = "CompositeImage";

/**
 * @brief DNG版本标签编码了符合DNG规范的四级版本号。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_DNG_VERSION = "DNGVersion";

/**
 * @brief 目的地点的经度参照。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_DEST_LONGITUDE = "GPSDestLongitude";

/**
 * @brief 指向目的地点的方位参照。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_DEST_BEARING_REF = "GPSDestBearingRef";

/**
 * @brief 指向目的地点的方位参照。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_DEST_BEARING = "GPSDestBearing";

/**
 * @brief 目标点距离的测量单位。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_DEST_DISTANCE_REF = "GPSDestDistanceRef";

/**
 * @brief 目标点距离的测量单位。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_DEST_DISTANCE = "GPSDestDistance";

/**
 * @brief DefaultCropSize指定了原始坐标中的最终图像大小，考虑了额外的边缘像素。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_DEFAULT_CROP_SIZE = "DefaultCropSize";

/**
 * @brief 表示系数伽马的值。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GAMMA = "Gamma";

/**
 * @brief 该标签指示摄像机或输入设备的ISO速度纬度yyy值，该值在ISO 12232中定义。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_ISO_SPEED_LATITUDEYYY = "ISOSpeedLatitudeyyy";

/**
 * @brief 该标签指示摄像机或输入设备的ISO速度纬度zzz值，该值在ISO 12232中定义。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_ISO_SPEED_LATITUDEZZZ = "ISOSpeedLatitudezzz";

/**
 * @brief 镜头的制造商。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_LENS_MAKE = "LensMake";

/**
 * @brief 镜头的型号名称。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_LENS_MODEL = "LensModel";

/**
 * @brief 镜头的序列号。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_LENS_SERIAL_NUMBER = "LensSerialNumber";

/**
 * @brief 使用的镜头规格。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_LENS_SPECIFICATION = "LensSpecification";

/**
 * @brief 在Exif中，"NewSubfileType"字段用于标识子文件的数据类型，如全分辨率图像、缩略图或多帧图像的一部分。其值是位掩码，0代表全分辨率图像，1代表缩略图，2代表多帧图像的一部分。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_NEW_SUBFILE_TYPE = "NewSubfileType";

/**
 * @brief 在Exif中，OffsetTime字段表示与UTC（协调世界时）的时间偏移，格式为±HH:MM，用于确定照片拍摄的本地时间。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_OFFSET_TIME = "OffsetTime";

/**
 * @brief 此标签记录图像数字化时的UTC偏移量，有助于准确调整时间戳。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_OFFSET_TIME_DIGITIZED = "OffsetTimeDigitized";

/**
 * @brief 此标签记录原始图像创建时的UTC偏移量，对于时间敏感的应用至关重要。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_OFFSET_TIME_ORIGINAL = "OffsetTimeOriginal";

/**
 * @brief 合成图像的源图像曝光时间。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SOURCE_EXPOSURE_TIMES_OF_COMPOSITE_IMAGE = "SourceExposureTimesOfCompositeImage";

/**
 * @brief 用于合成图像的源图像数量。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SOURCE_IMAGE_NUMBER_OF_COMPOSITE_IMAGE = "SourceImageNumberOfCompositeImage";

/**
 * @brief 此标签指示此子文件中的数据类型。标签已弃用，请使用NewSubfileType替代。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SUBFILE_TYPE = "SubfileType";

/**
 * @brief 此标签指示水平定位误差，单位为米。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GPS_H_POSITIONING_ERROR = "GPSHPositioningError";

/**
 * @brief 此标签指示拍摄图像时相机或输入设备的灵敏度。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_PHOTOGRAPHIC_SENSITIVITY = "PhotographicSensitivity";

/**
 * @brief 连拍次数。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_BURST_NUMBER = "HwMnoteBurstNumber";

/**
 * @brief 人脸置信度。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FACE_CONF = "HwMnoteFaceConf";

/**
 * @brief 左眼中心。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FACE_LEYE_CENTER = "HwMnoteFaceLeyeCenter";

/**
 * @brief 嘴中心。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FACE_MOUTH_CENTER = "HwMnoteFaceMouthCenter";

/**
 * @brief 脸部指针。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FACE_POINTER = "HwMnoteFacePointer";

/**
 * @brief 脸部矩形。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FACE_RECT = "HwMnoteFaceRect";

/**
 * @brief 右眼中心。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FACE_REYE_CENTER = "HwMnoteFaceReyeCenter";

/**
 * @brief FaceCount张人脸的笑脸分数。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FACE_SMILE_SCORE = "HwMnoteFaceSmileScore";

/**
 * @brief 人脸算法版本信息。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FACE_VERSION = "HwMnoteFaceVersion";

/**
 * @brief 是否是前置相机自拍。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_FRONT_CAMERA = "HwMnoteFrontCamera";

/**
 * @brief 场景指针。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SCENE_POINTER = "HwMnoteScenePointer";

/**
 * @brief 场景算法版本信息。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_SCENE_VERSION = "HwMnoteSceneVersion";

/**
 * @brief 是否支持XMAGE。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_IS_XMAGE_SUPPORTED = "HwMnoteIsXmageSupported";

/**
 * @brief XMAGE水印模式。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_XMAGE_MODE = "HwMnoteXmageMode";

/**
 * @brief 水印区域X1坐标。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_XMAGE_LEFT = "HwMnoteXmageLeft";

/**
 * @brief 水印区域Y1坐标。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_XMAGE_TOP = "HwMnoteXmageTop";

/**
 * @brief 水印区域X2坐标
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_XMAGE_RIGHT = "HwMnoteXmageRight";

/**
 * @brief 水印区域Y2坐标。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_XMAGE_BOTTOM = "HwMnoteXmageBottom";

/**
 * @brief 云增强模式。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_CLOUD_ENHANCEMENT_MODE = "HwMnoteCloudEnhancementMode";

/**
 * @brief 运动快拍模式。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_WIND_SNAPSHOT_MODE = "HwMnoteWindSnapshotMode";


/**
 * @brief GIF图片循环次数。
 *
 * @since 12
 */
static const char *OHOS_IMAGE_PROPERTY_GIF_LOOP_COUNT = "GIFLoopCount";

/**
 * @brief 水印裁剪图左上角在原始图中的X坐标。
 *
 * @since 13
 */
static const char *OHOS_IMAGE_PROPERTY_X_IN_ORIGINAL = "XInOriginal";

/**
 * @brief 水印裁剪图左上角在原始图中的Y坐标。
 *
 * @since 13
 */
static const char *OHOS_IMAGE_PROPERTY_Y_IN_ORIGINAL = "YInOriginal";

/**
 * @brief 水印裁剪图的宽。
 *
 * @since 13
 */
static const char *OHOS_IMAGE_PROPERTY_FRAGMENT_WIDTH = "FragmentImageWidth";

/**
 * @brief 水印裁剪图的高。
 *
 * @since 13
 */
static const char *OHOS_IMAGE_PROPERTY_FRAGMENT_HEIGHT = "FragmentImageHeight";

/**
 * @brief GIF图片的每帧播放时长（单位为毫秒）。
 *
 * @since 20
 */

static const char *IMAGE_PROPERTY_GIF_DELAY_TIME = "GifDelayTime";

/**
 * @brief GIF图片每帧的帧过渡模式。
 *
 * @since 20
 */
static const char *IMAGE_PROPERTY_GIF_DISPOSAL_TYPE = "GifDisposalType";

/**
 * @brief DNG版本号。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_DNG_VERSION = "DNGVersion";

/**
 * @brief DNG向后兼容版本号。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_DNG_BACKWARD_VERSION = "DNGBackwardVersion";

/**
 * @brief 唯一的相机型号标识。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_UNIQUE_CAMERA_MODEL = "UniqueCameraModel";

/**
 * @brief 本地化的相机型号。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_LOCALIZED_CAMERA_MODEL = "LocalizedCameraModel";

/**
 * @brief CFA（色彩滤镜阵列）平面颜色。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_CFA_PLANE_COLOR = "CFAPlaneColor";

/**
 * @brief CFA（色彩滤镜阵列）布局。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyShort}和
 * {@link OH_ImageSourceNative_GetImagePropertyLong}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_CFA_LAYOUT = "CFALayout";

/**
 * @brief 线性化表。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_LINEARIZATION_TABLE = "LinearizationTable";

/**
 * @brief 黑电平重复维度。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_BLACK_LEVEL_REPEAT_DIM = "BlackLevelRepeatDim";

/**
 * @brief 黑电平重复维度。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_BLACK_LEVEL = "BlackLevel";

/**
 * @brief 水平方向黑电平校正增量。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_BLACK_LEVEL_DELTA_H = "BlackLevelDeltaH";

/**
 * @brief 垂直方向黑电平校正增量。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_BLACK_LEVEL_DELTA_V = "BlackLevelDeltaV";

/**
 * @brief 白电平。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_WHITE_LEVEL = "WhiteLevel";

/**
 * @brief 默认缩放比例。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_DEFAULT_SCALE = "DefaultScale";

/**
 * @brief 默认裁剪原点。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_DEFAULT_CROP_ORIGIN = "DefaultCropOrigin";

/**
 * @brief 默认裁剪尺寸。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_DEFAULT_CROP_SIZE = "DefaultCropSize";

/**
 * @brief 第一个校准光源下的变换矩阵。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_COLOR_MATRIX1 = "ColorMatrix1";

/**
 * @brief 第二个校准光源下的变换矩阵。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_COLOR_MATRIX2 = "ColorMatrix2";

/**
 * @brief 第一个校准光源下的校准矩阵。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_CAMERA_CALIBRATION1 = "CameraCalibration1";

/**
 * @brief 第二个校准光源下的校准矩阵。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_CAMERA_CALIBRATION2 = "CameraCalibration2";

/**
 * @brief 第一个校准光源下的降维矩阵。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_REDUCTION_MATRIX1 = "ReductionMatrix1";

/**
 * @brief 第二个校准光源下的降维矩阵。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_REDUCTION_MATRIX2 = "ReductionMatrix2";

/**
 * @brief 模拟平衡。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_ANALOG_BALANCE = "AnalogBalance";

/**
 * @brief 拍摄时中性色。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_AS_SHOT_NEUTRAL = "AsShotNeutral";

/**
 * @brief 拍摄时白点的CIE（1931 色彩空间） x-y色度坐标。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_AS_SHOT_WHITEXY = "AsShotWhiteXY";

/**
 * @brief 基线曝光。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyDouble}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_BASELINE_EXPOSURE = "BaselineExposure";

/**
 * @brief 基线噪点。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyDouble}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_BASELINE_NOISE = "BaselineNoise";

/**
 * @brief 基线锐度。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyDouble}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_BASELINE_SHARPNESS = "BaselineSharpness";

/**
 * @brief Bayer图像中两个绿色通道的分离程度。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyShort}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_BAYER_GREEN_SPLIT = "BayerGreenSplit";

/**
 * @brief 线性响应限制。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyDouble}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_LINEAR_RESPONSE_LIMIT = "LinearResponseLimit";

/**
 * @brief 相机序列号。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_CAMERA_SERIAL_NUMBER = "CameraSerialNumber";

/**
 * @brief 镜头信息。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_LENS_INFO = "LensInfo";

/**
 * @brief 色差模糊半径，单位：像素。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyDouble}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_CHROMA_BLUR_RADIUS = "ChromaBlurRadius";

/**
 * @brief 抗锯齿强度。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyDouble}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_ANTI_ALIAS_STRENGTH = "AntiAliasStrength";

/**
 * @brief 阴影缩放。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyDouble}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_SHADOW_SCALE = "ShadowScale";

/**
 * @brief 私有数据。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyBlob}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_DNG_PRIVATE_DATA = "DNGPrivateData";

/**
 * @brief EXIF MakerNote标签是否安全。0：不安全，1：安全。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyShort}和
 * {@link OH_ImageSourceNative_GetImagePropertyLong}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_MAKER_NOTE_SAFETY = "MakerNoteSafety";

/**
 * @brief 第一个校准光源。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyShort}和
 * {@link OH_ImageSourceNative_GetImagePropertyLong}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_CALIBRATION_ILLUMINANT1 = "CalibrationIlluminant1";

/**
 * @brief 第二个校准光源。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyShort}和
 * {@link OH_ImageSourceNative_GetImagePropertyLong}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_CALIBRATION_ILLUMINANT2 = "CalibrationIlluminant2";

/**
 * @brief 最佳质量缩放。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyDouble}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_BEST_QUALITY_SCALE = "BestQualityScale";

/**
 * @brief 原始图像数据的唯一标识符。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_RAW_DATA_UNIQUE_ID = "RawDataUniqueID";

/**
 * @brief 原始文件名。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_ORIGINAL_RAW_FILE_NAME = "OriginalRawFileName";

/**
 * @brief 原始文件数据。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyBlob}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_ORIGINAL_RAW_FILE_DATA = "OriginalRawFileData";

/**
 * @brief 活动区域。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_ACTIVE_AREA = "ActiveArea";

/**
 * @brief 掩蔽区域。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_MASKED_AREAS = "MaskedAreas";

/**
 * @brief ICC配置文件。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyBlob}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_AS_SHOT_ICC_PROFILE = "AsShotICCProfile";

/**
 * @brief 拍摄时预配置文件矩阵。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_AS_SHOT_PRE_PROFILE_MATRIX = "AsShotPreProfileMatrix";

/**
 * @brief 当前ICC配置文件。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyBlob}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_CURRENT_ICC_PROFILE = "CurrentICCProfile";

/**
 * @brief 当前预配置文件矩阵。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_CURRENT_PRE_PROFILE_MATRIX = "CurrentPreProfileMatrix";

/**
 * @brief 色度参考。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyShort}和
 * {@link OH_ImageSourceNative_GetImagePropertyLong}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_COLORIMETRIC_REFERENCE = "ColorimetricReference";

/**
 * @brief 相机校准签名。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_CAMERA_CALIBRATION_SIGNATURE = "CameraCalibrationSignature";

/**
 * @brief 配置文件校准签名。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PROFILE_CALIBRATION_SIGNATURE = "ProfileCalibrationSignature";

/**
 * @brief 额外相机配置文件。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_EXTRA_CAMERA_PROFILES = "ExtraCameraProfiles";

/**
 * @brief 拍摄时配置文件名称。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_AS_SHOT_PROFILE_NAME = "AsShotProfileName";

/**
 * @brief 应用的降噪量。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyDouble}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_NOISE_REDUCTION_APPLIED = "NoiseReductionApplied";

/**
 * @brief 配置文件名称。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PROFILE_NAME = "ProfileName";

/**
 * @brief 配置文件色调/饱和度映射维度。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PROFILE_HUE_SAT_MAP_DIMS = "ProfileHueSatMapDims";

/**
 * @brief 第一个色调/饱和度映射表数据。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PROFILE_HUE_SAT_MAP_DATA1 = "ProfileHueSatMapData1";

/**
 * @brief 第二个色调/饱和度映射表数据。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PROFILE_HUE_SAT_MAP_DATA2 = "ProfileHueSatMapData2";

/**
 * @brief 配置文件色调曲线。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PROFILE_TONE_CURVE = "ProfileToneCurve";

/**
 * @brief 配置文件嵌入策略。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyShort}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PROFILE_EMBED_POLICY = "ProfileEmbedPolicy";

/**
 * @brief 配置文件版权。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PROFILE_COPYRIGHT = "ProfileCopyright";

/**
 * @brief 第一个前向矩阵。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_FORWARD_MATRIX1 = "ForwardMatrix1";

/**
 * @brief 第二个前向矩阵。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_FORWARD_MATRIX2 = "ForwardMatrix2";

/**
 * @brief 预览应用程序名称。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PREVIEW_APPLICATION_NAME = "PreviewApplicationName";

/**
 * @brief 预览应用程序版本。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PREVIEW_APPLICATION_VERSION = "PreviewApplicationVersion";

/**
 * @brief 预览设置名称。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PREVIEW_SETTINGS_NAME = "PreviewSettingsName";

/**
 * @brief 预览设置摘要。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PREVIEW_SETTINGS_DIGEST = "PreviewSettingsDigest";

/**
 * @brief 预览颜色空间。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyShort}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PREVIEW_COLOR_SPACE = "PreviewColorSpace";

/**
 * @brief 预览日期和时间。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PREVIEW_DATE_TIME = "PreviewDateTime";

/**
 * @brief 原始图像数据的MD5摘要。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_RAW_IMAGE_DIGEST = "RawImageDigest";

/**
 * @brief 存储在OriginalRawFileData中的数据的MD5摘要。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_ORIGINAL_RAW_FILE_DIGEST = "OriginalRawFileDigest";

/**
 * @brief 子图块大小。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_SUB_TILE_BLOCK_SIZE = "SubTileBlockSize";

/**
 * @brief 行交错因子。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyShort}和
 * {@link OH_ImageSourceNative_GetImagePropertyLong}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_ROW_INTERLEAVE_FACTOR = "RowInterleaveFactor";

/**
 * @brief 配置文件查找表维度。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PROFILE_LOOK_TABLE_DIMS = "ProfileLookTableDims";

/**
 * @brief 配置文件查找表数据。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PROFILE_LOOK_TABLE_DATA = "ProfileLookTableData";

/**
 * @brief 第一个操作码列表。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyBlob}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_OPCODE_LIST1 = "OpcodeList1";

/**
 * @brief 第二个操作码列表。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyBlob}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_OPCODE_LIST2 = "OpcodeList2";

/**
 * @brief 第三个操作码列表。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyBlob}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_OPCODE_LIST3 = "OpcodeList3";

/**
 * @brief 噪点配置文件。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_NOISE_PROFILE = "NoiseProfile";

/**
 * @brief 原始默认最终尺寸。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_ORIGINAL_DEFAULT_FINAL_SIZE = "OriginalDefaultFinalSize";

/**
 * @brief 原始最佳质量最终尺寸。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_ORIGINAL_BEST_QUALITY_FINAL_SIZE = "OriginalBestQualityFinalSize";

/**
 * @brief 原始默认裁剪尺寸。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_ORIGINAL_DEFAULT_CROP_SIZE = "OriginalDefaultCropSize";

/**
 * @brief 配置文件色调、饱和度映射编码。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyShort}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PROFILE_HUE_SAT_MAP_ENCODING = "ProfileHueSatMapEncoding";

/**
 * @brief 配置文件查找表编码。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyShort}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_PROFILE_LOOK_TABLE_ENCODING = "ProfileLookTableEncoding";

/**
 * @brief 基线曝光偏移。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyDouble}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_BASELINE_EXPOSURE_OFFSET = "BaselineExposureOffset";

/**
 * @brief 默认黑色渲染。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyShort}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_DEFAULT_BLACK_RENDER = "DefaultBlackRender";

/**
 * @brief 修改后的原始图像数据MD5摘要。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyString}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_NEW_RAW_IMAGE_DIGEST = "NewRawImageDigest";

/**
 * @brief 主原始IFD（Image File Directory）和预览IFD之间的增益。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyDouble}获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_RAW_TO_PREVIEW_GAIN = "RawToPreviewGain";

/**
 * @brief 默认用户裁剪。取值可以通过{@link OH_ImageSourceNative_GetImagePropertyArraySize}和
 * {@link OH_ImageSourceNative_GetImagePropertyIntArray}共同获取。
 *
 * @since 24
 */
static const char *OHOS_DNG_PROPERTY_DEFAULT_USER_CROP = "DefaultUserCrop";

#ifdef __cplusplus
};
#endif
/** @} */

#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_IMAGE_COMMON_H_

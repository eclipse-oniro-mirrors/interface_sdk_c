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
 * @file image_source_native.h
 *
 * @brief 图片解码API。
 *
 * @library libimage_source.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.Image.ImageSource
 * @since 12
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_IMAGE_SOURCE_NATIVE_H_
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_IMAGE_SOURCE_NATIVE_H_
#include <stdbool.h>
#include "image_common.h"

#include "pixelmap_native.h"
#include "picture_native.h"
#include "rawfile/raw_file.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief OH_ImageSourceNative是native层封装的ImageSource结构体，用于创建图片数据。OH_ImageSourceNative结构体不可直接操作，而是采用函数调用方式创建、
 * 释放结构体以及操作具体字段。<br>有多种方式创建OH_ImageSourceNative，具体如下：<br>使用{@link OH_ImageSourceNative_Release}
 * 函数释放OH_ImageSourceNative对象。<br>使用约束：使用OH_ImageSourceNative对象前，必须先通过上述接口创建对象；使用完成后，应调用
 * {@link OH_ImageSourceNative_Release}释放对象。通过{@link OH_ImageSourceNative_CreateFromDataWithUserBuffer}创建对象时，
 * 在OH_ImageSourceNative对象生命周期内，调用方传入的数据缓存必须保持有效，不能被释放、复用或修改为其他图片数据。<br>资源管理：通过OH_ImageSourceNative解码或获取到的
 * {@link OH_PixelmapNative}、{@link OH_PictureNative}、{@link OH_ImageRawData}对象由调用方分别管理。
 * 释放OH_ImageSourceNative对象不会自动释放这些对象，需要调用对应接口释放或销毁。<br>OH_ImageSourceNative结构体内容和操作方式如下：
 * 
 * @since 12
 */
struct OH_ImageSourceNative;
typedef struct OH_ImageSourceNative OH_ImageSourceNative;

/**
 * @brief OH_ImageSource_Info是native层封装的ImageSource信息结构体，OH_ImageSource_Info结构体不可直接操作，而是采用函数调用方式创建、释放结构体以及操作具体字段。<br>
 * 使用{@link OH_ImageSourceInfo_Create}函数创建OH_ImageSource_Info对象。<br>使用{@link OH_ImageSourceNative_GetImageInfo}
 * 函数将OH_ImageSourceNative中的图像信息写入创建好的OH_ImageSource_Info对象。<br>使用{@link OH_ImageSourceInfo_Release}
 * 函数释放OH_ImageSource_Info对象。<br>使用约束：OH_ImageSource_Info对象通常配合{@link OH_ImageSourceNative_GetImageInfo}使用，用于承载指定序号图片的宽、
 * 高、动态范围和MIME类型等信息。使用前需通过{@link OH_ImageSourceInfo_Create}创建对象；使用完成后，应调用{@link OH_ImageSourceInfo_Release}释放对象。<br>
 * OH_ImageSource_Info结构体内容和操作方式如下：
 * 
 * @since 12
 */
struct OH_ImageSource_Info;
typedef struct OH_ImageSource_Info OH_ImageSource_Info;

/**
 * @brief Picture解码参数结构体。<br>使用{@link OH_DecodingOptionsForPicture_Create}函数创建OH_DecodingOptionsForPicture对象。<br>使用
 * {@link OH_DecodingOptionsForPicture_Release}函数释放OH_DecodingOptionsForPicture对象。<br>资源管理：
 * 释放OH_ImageSourceNative或解码生成的OH_PictureNative对象，不会自动释放OH_DecodingOptionsForPicture对象。OH_DecodingOptionsForPicture释放后，
 * 不应继续传入Picture解码接口或调用其字段获取和设置接口。<br>OH_DecodingOptionsForPicture结构体内容和操作方式如下：
 * 
 * @since 13
 */
struct OH_DecodingOptionsForPicture;

/**
 * @brief Picture解码参数结构体。<br>使用{@link OH_DecodingOptionsForPicture_Create}函数创建OH_DecodingOptionsForPicture对象。<br>使用
 * {@link OH_DecodingOptionsForPicture_Release}函数释放OH_DecodingOptionsForPicture对象。<br>资源管理：
 * 释放OH_ImageSourceNative或解码生成的OH_PictureNative对象，不会自动释放OH_DecodingOptionsForPicture对象。OH_DecodingOptionsForPicture释放后，
 * 不应继续传入Picture解码接口或调用其字段获取和设置接口。<br>OH_DecodingOptionsForPicture结构体内容和操作方式如下：
 *
 * @since 13
 */
typedef struct OH_DecodingOptionsForPicture OH_DecodingOptionsForPicture;

/**
 * @brief 解码指定期望动态范围。
 * 
 * @since 12
 */
typedef enum {
    /**
     * 根据图片自适应处理。
     */
    IMAGE_DYNAMIC_RANGE_AUTO = 0,
    /**
     * 标准动态范围。
     */
    IMAGE_DYNAMIC_RANGE_SDR = 1,
    /**
     * 高动态范围。
     */
    IMAGE_DYNAMIC_RANGE_HDR = 2,
} IMAGE_DYNAMIC_RANGE;

/**
 * @brief 用于分配PixelMap内存的分配器类型。
 *
 * @since 15
 */
typedef enum {
    /**
     * 由系统决定使用DMA内存或共享内存来创建PixelMap。
     */
    IMAGE_ALLOCATOR_TYPE_AUTO = 0,
    /**
     * 使用DMA内存来创建PixelMap。
     */
    IMAGE_ALLOCATOR_TYPE_DMA = 1,
    /**
     * 使用共享内存来创建PixelMap。
     */
    IMAGE_ALLOCATOR_TYPE_SHARE_MEMORY = 2,
} IMAGE_ALLOCATOR_TYPE;

/**
 * @brief 在同时指定desiredSize和desiredRegion时执行裁剪和缩放的策略。
 * <br>如果在配置解码选项{@link OH_DecodingOptions}时，未填入参数Image_CropAndScaleStrategy，并且同时设置了desiredRegion和desiredSize，
 * 由于系统对于不同图片格式采用的解码算法不同，最终解码效果将略有差异。
 * <br>例如原始图片大小200x200，传入desiredSize:{width: 150, height: 150}，desiredRegion:{x: 0, y: 0, width: 100, height: 100}，
 * 即预期解码原图左上角1/4区域，最终将pixelMap大小缩放至150x150返回。
 * <br>对于jpeg、webp图片（部分dng图片解码时会优先解码图片中的jpeg预览图，在此场景下也会被视为jpeg图片格式）会先进行下采样，例如按照7/8下采样，再基于175x175的图片大小进行区域裁剪，
 * 因此最终的区域内容稍大于原图的左上角1/4区域。
 * <br>对于svg图片，由于是矢量图，可以任意缩放不损失清晰度，在解码时会根据desiredSize与原图Size的比例选择缩放比例，在基于缩放后的图片大小进行区域裁剪，因此最终返回的解码区域会有所差异。
 * <br>针对该场景，建议在解码选项同时设置了desiredRegion与desiredSize时，参数Image_CropAndScaleStrategy应传入CROP_FIRST参数保证效果一致。
 * 
 * @since 18
 */
typedef enum {
    /**
     * 先缩放，后裁剪。
     * @since 18
     */
    IMAGE_CROP_AND_SCALE_STRATEGY_SCALE_FIRST = 1,

    /**
     * 先裁剪，后缩放。
     * @since 18
     */
    IMAGE_CROP_AND_SCALE_STRATEGY_CROP_FIRST = 2,
} Image_CropAndScaleStrategy;

/**
 * @brief 创建OH_ImageSource_Info指针。
 * 
 * @param info 被操作的OH_ImageSource_Info指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 * @release image_source_native/OH_ImageSourceInfo_Release {info}
 */
Image_ErrorCode OH_ImageSourceInfo_Create(OH_ImageSource_Info **info);

/**
 * @brief 获取图片的宽。对于没有width标签的SVG图片，返回默认值0。
 * 
 * @param info 被操作的OH_ImageSource_Info指针。
 * @param width 图片的宽，单位为像素（px）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceInfo_GetWidth(OH_ImageSource_Info *info, uint32_t *width);

/**
 * @brief 获取图片的高。对于没有height标签的SVG图片，返回默认值0。
 * 
 * @param info 被操作的OH_ImageSource_Info指针。
 * @param height 图片的高，单位为像素（px）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceInfo_GetHeight(OH_ImageSource_Info *info, uint32_t *height);

/**
 * @brief 获取图片是否为高动态范围的信息。
 * 
 * @param info 被操作的OH_ImageSource_Info指针。
 * @param isHdr 表示是否为高动态范围（HDR）的信息。true表示是高动态范围的信息，false表示不是高动态范围的信息。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数校验错误。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceInfo_GetDynamicRange(OH_ImageSource_Info *info, bool *isHdr);

/**
 * @brief 获取图片源的MIME类型。
 *
 * @param info OH_ImageSource_Info指针。
 * @param mimetype Pointer to the MIME type of the image source.
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：参数错误，INFO或者MIME类型为空。
 * @since 20
 */
Image_ErrorCode OH_ImageSourceInfo_GetMimeType(OH_ImageSource_Info *info, Image_MimeType *mimetype);

/**
 * @brief 释放OH_ImageSource_Info指针。调用该接口后，通过OH_ImageSourceInfo_GetMimeType()获取到的mimeType.data会失效；如需在释放后继续使用MIME类型数据，
 * 应在释放前自行深拷贝。
 * 
 * @param info 被操作的OH_ImageSource_Info指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceInfo_Release(OH_ImageSource_Info *info);

/**
 * @brief OH_DecodingOptions是native层封装的解码选项参数结构体，用于设置解码选项参数，在创建Pixelmap时作为入参传入，详细信息见
 * {@link OH_ImageSourceNative_CreatePixelmap}。<br>OH_DecodingOptions结构体不可直接操作，而是采用函数调用方式创建、释放结构体以及操作具体字段。<br>使用
 * {@link OH_DecodingOptions_Create}函数创建OH_DecodingOptions对象。<br>使用{@link OH_DecodingOptions_Release}
 * 函数释放OH_DecodingOptions对象。<br>使用约束：OH_DecodingOptions用于配置PixelMap解码参数，通常作为{@link OH_ImageSourceNative_CreatePixelmap}、
 * {@link OH_ImageSourceNative_CreatePixelmapUsingAllocator}或{@link OH_ImageSourceNative_CreatePixelmapList}的入参。使用前需通过
 * {@link OH_DecodingOptions_Create}创建对象；使用完成后，应调用{@link OH_DecodingOptions_Release}释放对象。<br>资源管理：
 * 释放OH_ImageSourceNative或解码生成的OH_PixelmapNative对象，不会自动释放OH_DecodingOptions对象。OH_DecodingOptions释放后，
 * 不应继续传入解码接口或调用其字段获取和设置接口。<br>OH_DecodingOptions结构体内容和操作方式如下：
 * 
 * @since 12
 */
struct OH_DecodingOptions;
typedef struct OH_DecodingOptions OH_DecodingOptions;

/**
 * @brief 创建OH_DecodingOptions指针。
 * 
 * @param  options 被操作的OH_DecodingOptions指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 * @release image_source_native/OH_DecodingOptions_Release {options}
 */
Image_ErrorCode OH_DecodingOptions_Create(OH_DecodingOptions **options);

/**
 * @brief 获取pixel格式。
 * 
 * @param  options 被操作的OH_DecodingOptions指针。
 * @param pixelFormat pixel格式{@link PIXEL_FORMAT}，默认值为RGBA_8888。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_DecodingOptions_GetPixelFormat(OH_DecodingOptions *options,
    int32_t *pixelFormat);

/**
 * @brief 设置pixel格式。
 * 
 * @param  options 被操作的OH_DecodingOptions指针。
 * @param pixelFormat pixel格式{@link PIXEL_FORMAT}，默认值为RGBA_8888。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_DecodingOptions_SetPixelFormat(OH_DecodingOptions *options,
    int32_t pixelFormat);

/**
 * @brief 获取解码图片序号。
 * 
 * @param  options 被操作的OH_DecodingOptions指针。
 * @param index 解码图片序号，默认值为0。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_DecodingOptions_GetIndex(OH_DecodingOptions *options, uint32_t *index);

/**
 * @brief 设置解码图片序号。
 * 
 * @param  options 被操作的OH_DecodingOptions指针。
 * @param index 解码图片序号，默认值为0。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_DecodingOptions_SetIndex(OH_DecodingOptions *options, uint32_t index);

/**
 * @brief 获取旋转角度。
 * 
 * @param  options 被操作的OH_DecodingOptions指针。
 * @param rotate 旋转角度，单位为角度（deg），默认值为0。取值范围为[0, 360]。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_DecodingOptions_GetRotate(OH_DecodingOptions *options, float *rotate);

/**
 * @brief 设置旋转角度。
 * 
 * @param  options 被操作的OH_DecodingOptions指针。
 * @param rotate 旋转角度，单位为角度（deg），默认值为0。取值范围为[0, 360]。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_DecodingOptions_SetRotate(OH_DecodingOptions *options, float rotate);

/**
 * @brief 获取期望输出大小。
 * 
 * @param  options 被操作的OH_DecodingOptions指针。
 * @param desiredSize 期望输出大小，默认为原始图片尺寸。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_DecodingOptions_GetDesiredSize(OH_DecodingOptions *options,
    Image_Size *desiredSize);

/**
 * @brief 设置期望输出大小。desiredSize参数决定解码得到的PixelMap大小，且宽、高须为正整数。若与原尺寸比例不一致，则会进行拉伸/缩放到指定尺寸。默认为原始尺寸。
 * 
 * @param  options 被操作的OH_DecodingOptions指针。
 * @param desiredSize 期望输出大小，默认为原始图片尺寸。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_DecodingOptions_SetDesiredSize(OH_DecodingOptions *options,
    Image_Size *desiredSize);

/**
 * @brief 获取解码区域。
 * <br>由于对应SetDesiredRegion接口无法满足区域解码诉求，从API version 19开始，推荐配套使用{@link OH_DecodingOptions_GetCropRegion}接口替代。
 * 
 * @param  options 被操作的OH_DecodingOptions指针。
 * @param desiredRegion 解码区域，默认为完整图片大小的区域。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_DecodingOptions_GetDesiredRegion(OH_DecodingOptions *options,
    Image_Region *desiredRegion);

/**
 * @brief 设置解码区域。
 * <br>实际解码结果会按照原图解码，无区域解码效果。从API version 19开始，推荐使用接口{@link OH_DecodingOptions_SetCropRegion}替代。
 * 
 * @param  options 被操作的OH_DecodingOptions指针。
 * @param desiredRegion 解码区域，默认为完整图片大小的区域。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_DecodingOptions_SetDesiredRegion(OH_DecodingOptions *options,
    Image_Region *desiredRegion);

/**
 * @brief 获取解码时设置的期望动态范围。
 * 
 * @param options 被操作的OH_DecodingOptions指针。
 * @param desiredDynamicRange 期望的动态范围值{@link IMAGE_DYNAMIC_RANGE}，默认值为SDR。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数校验错误。
 * @since 12
 */
Image_ErrorCode OH_DecodingOptions_GetDesiredDynamicRange(OH_DecodingOptions *options,
    int32_t *desiredDynamicRange);

/**
 * @brief 设置解码时的期望动态范围。
 * 
 * @param options 被操作的OH_DecodingOptions指针。
 * @param desiredDynamicRange 期望的动态范围值{@link IMAGE_DYNAMIC_RANGE}，默认值为SDR。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数校验错误。
 * @since 12
 */
Image_ErrorCode OH_DecodingOptions_SetDesiredDynamicRange(OH_DecodingOptions *options,
    int32_t desiredDynamicRange);

/**
 * @brief 获取解码选项的裁剪和缩放策略。
 * 
 * @param options 被操作的OH_DecodingOptions指针。
 * @param cropAndScaleStrategy 指向在同时指定desiredSize和desiredRegion时执行裁剪和缩放策略的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：options或者cropAndScaleStrategy为空指针。
 * @since 18
 */
Image_ErrorCode OH_DecodingOptions_GetCropAndScaleStrategy(OH_DecodingOptions *options,
    int32_t *cropAndScaleStrategy);

/**
 * @brief 设置解码选项的裁剪和缩放策略。
 * 
 * @param options 被操作的OH_DecodingOptions指针。
 * @param cropAndScaleStrategy 在同时指定desiredSize和desiredRegion时执行裁剪和缩放的策略。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：options空指针或者cropAndScaleStrategy取值不在Image_CropAndScaleStrategy枚举值定义之中。
 * @since 18
 */
Image_ErrorCode OH_DecodingOptions_SetCropAndScaleStrategy(OH_DecodingOptions *options,
    int32_t cropAndScaleStrategy);

/**
 * @brief 设置解码期望得到的色彩空间。
 * 
 * @param options 解码参数。
 * @param colorSpace 期望的色彩空间，参考{@link ColorSpaceName}。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：参数错误。options为空，或者传入了不支持的colorSpace。
 * @since 20
 */
Image_ErrorCode OH_DecodingOptions_SetDesiredColorSpace(OH_DecodingOptions *options, int32_t colorSpace);

/**
 * @brief 获取解码参数中设置的色彩空间。
 * 
 * @param options 解码参数。
 * @param colorSpace 解码参数中设置的色彩空间，参考{@link ColorSpaceName}。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：参数错误。options或colorSpace为空。
 * @since 20
 */
Image_ErrorCode OH_DecodingOptions_GetDesiredColorSpace(OH_DecodingOptions *options, int32_t *colorSpace);

/**
 * @brief 设置解码参数中的裁剪区域。
 * 
 * @param options 指向解码参数指针。
 * @param cropRegion 指向要裁剪的目标区域指针。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：options或cropRegion为空。
 * @since 19
 */
Image_ErrorCode OH_DecodingOptions_SetCropRegion(OH_DecodingOptions *options, Image_Region *cropRegion);

/**
 * @brief 获取解码参数中的裁剪区域。
 * 
 * @param options 指向解码参数指针。
 * @param cropRegion 指向要裁剪的目标区域指针。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：options或cropRegion为空。
 * @since 19
 */
Image_ErrorCode OH_DecodingOptions_GetCropRegion(OH_DecodingOptions *options, Image_Region *cropRegion);

/**
 * @brief 释放OH_DecodingOptions指针。
 * 
 * @param  options 被操作的OH_DecodingOptions指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_DecodingOptions_Release(OH_DecodingOptions *options);

/**
 * @brief 通过uri创建OH_ImageSourceNative指针。
 * 
 * @param uri 指向图像源URI的指针。只接受文件URI或Base64 URI。当前文件资源只支持绝对路径。
 * @param uriSize URI长度。
 * @param res 指向c++本地层创建的OH_ImageSourceNative对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_BAD_SOURCE：解码数据源异常。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceNative_CreateFromUri(char *uri, size_t uriSize, OH_ImageSourceNative **res);

/**
 * @brief 通过fd创建OH_ImageSourceNative指针。
 * 
 * @param fd 文件描述符fd。
 * @param res 指向c++本地层创建的OH_ImageSourceNative对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceNative_CreateFromFd(int32_t fd, OH_ImageSourceNative **res);

/**
 * @brief 通过缓冲区数据创建OH_ImageSourceNative指针。
 * <br>data数据应该是未解码的数据，不要传入类似于RGBA，YUV的像素buffer数据。
 * <br>如果想通过像素buffer数据创建pixelMap，可以调用{@link OH_PixelmapNative_CreatePixelmap}这一类接口。
 * <br>使用场景：适用于应用已经通过网络、文件或其他模块获取到完整编码图片数据的场景，例如JPEG、PNG、WebP等格式的二进制数据。该接口创建的是图片源对象，后续可继续调用
 * {@link OH_ImageSourceNative_GetImageInfo}读取图片信息，或调用{@link OH_ImageSourceNative_CreatePixelmap}解码为PixelMap。
 * <br>资源管理：成功创建的OH_ImageSourceNative对象由调用方持有，使用完成后必须调用{@link OH_ImageSourceNative_Release}释放。传入的data仍由调用方管理，
 * 不应传入已经解码后的像素数据。
 * 
 * @param data 图像缓冲区数据。
 * @param dataSize 图像缓冲区数据长度。
 * @param res 指向c++本地层创建的OH_ImageSourceNative对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_BAD_SOURCE：解码数据源异常。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceNative_CreateFromData(uint8_t *data, size_t dataSize, OH_ImageSourceNative **res);

/**
 * @brief 由数据缓存创建图片源。传入的数据缓存将在图片源对象中直接访问，在图片源对象的生命周期内，数据缓存需要保持可用。
 * <br>使用场景：适用于希望减少图片源创建过程中的数据拷贝，并且调用方能够保证输入缓冲区生命周期的场景。
 * <br>资源管理：在调用{@link OH_ImageSourceNative_Release}释放图片源对象之前，data指向的缓冲区不能被释放、复用或修改为其他图片数据。否则后续读取图片信息、解码或读取元数据时可能访问无效数据。
 * 
 * @param data 数据缓存指针。
 * @param datalength 数据缓存长度。
 * @param imageSource 图片源的二级指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：data或imageSource是空指针，datalength为0。
 * @since 20
 */

Image_ErrorCode OH_ImageSourceNative_CreateFromDataWithUserBuffer(uint8_t *data, size_t datalength, OH_ImageSourceNative **imageSource);

/**
 * @brief 通过图像资源文件的RawFileDescriptor创建OH_ImageSourceNative指针。
 * 
 * @param rawFile 指示raw文件的文件描述符。
 * @param res 指向c++本地层创建的OH_ImageSourceNative对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceNative_CreateFromRawFile(RawFileDescriptor *rawFile, OH_ImageSourceNative **res);

/**
 * @brief 通过图片解码参数创建OH_PixelmapNative指针。
 * <br>使用场景：适用于将JPEG、PNG、WebP、GIF单帧等编码图片解码为可读取、处理或再编码的PixelMap。解码前可通过OH_DecodingOptions设置帧序号、目标像素格式、目标尺寸、裁剪区域、期望动态范围等参数。
 * <br>使用约束：source、options和pixelmap均不能为空指针。调用前需先创建OH_ImageSourceNative对象；如需自定义解码参数，需先创建并设置OH_DecodingOptions对象。接口执行成功后，
 * pixelmap指向新创建的OH_PixelmapNative对象；接口执行失败时，不应使用pixelmap指向的对象。
 * <br>资源管理：成功创建的OH_PixelmapNative对象由调用方持有，使用完成后应调用{@link OH_PixelmapNative_Destroy}释放。
 * OH_DecodingOptions和OH_ImageSourceNative对象不会因为创建PixelMap而自动释放，需要分别调用{@link OH_DecodingOptions_Release}和
 * {@link OH_ImageSourceNative_Release}释放。
 * 
 * @param source 被操作的OH_ImageSourceNative指针。
 * @param  options 解码参数。
 * @param pixelmap 指向c++本地层创建的OH_PixelmapNative对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceNative_CreatePixelmap(OH_ImageSourceNative *source, OH_DecodingOptions *options,
    OH_PixelmapNative **pixelmap);

/**
 * @brief 根据解码参数创建一个PixelMap，PixelMap使用的内存类型可以通过allocatorType来指定。
 * <br>默认情况下，系统会根据图像类型、图像大小、平台能力等选择内存类型。在处理通过此接口返回的PixelMap时，请始终考虑步幅（stride）的影响。
 * <br>使用场景：适用于调用方需要明确指定PixelMap内存类型的场景。例如，后续图像处理链路要求DMA内存时，可指定IMAGE_ALLOCATOR_TYPE_DMA。
 * <br>使用约束：source、options和pixelmap均不能为空指针。allocator需为{@link IMAGE_ALLOCATOR_TYPE}中定义的有效枚举值。指定的内存类型可能受图片类型、图片大小、
 * 系统版本和设备能力限制，接口可能返回IMAGE_SOURCE_UNSUPPORTED_ALLOCATOR_TYPE。
 * <br>资源管理：成功创建的PixelMap需要调用{@link OH_PixelmapNative_Destroy}释放。读取或写入像素数据时，不能假设每行字节数等于宽度乘以每像素字节数，应通过
 * {@link OH_PixelmapImageInfo_GetRowStride}获取行跨距。
 * 
 * @param source 被操作的OH_ImageSourceNative指针。
 * @param options 解码参数。
 * @param allocator 指示返回的PixelMap将使用哪种内存类型。
 * @param pixelmap 指向c++本地层创建的OH_PixelmapNative对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_BAD_SOURCE：数据源异常。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持的MIME类型。
 *     <br>IMAGE_SOURCE_TOO_LARGE：图像过大。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_ALLOCATOR_TYPE：不支持的分配器类型。例如，使用共享内存解码HDR图像，因为只有DMA支持HDR元数据。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_OPTIONS：不支持的选项。例如，无法将图像转换为所需的像素格式。
 *     <br>IMAGE_DECODE_FAILED：解码失败。
 *     <br>IMAGE_SOURCE_ALLOC_FAILED：内存分配失败。
 * @since 15
 */
Image_ErrorCode OH_ImageSourceNative_CreatePixelmapUsingAllocator(OH_ImageSourceNative *source,
    OH_DecodingOptions *options, IMAGE_ALLOCATOR_TYPE allocator, OH_PixelmapNative **pixelmap);

/**
 * @brief 通过图片解码参数创建OH_PixelmapNative数组。
 * <br>注意，此接口会一次性解码全部帧，当帧数过多或单帧图像过大时，会占用较大内存，造成系统内存紧张，此种情况推荐使用Image组件显示动图，Image组件采用逐帧解码，占用内存比此接口少。
 * <br>使用场景：适用于需要一次性获取动图所有帧并自行处理的场景，例如生成缩略图序列、分析每帧内容或重新编码动图。仅播放动图时，不建议优先使用该接口。
 * <br>使用约束：source、options和resVecPixMap均不能为空指针。调用方需根据帧数准备足够长度的resVecPixMap数组，size应与数组可写入元素数量一致。调用前可通过
 * {@link OH_ImageSourceNative_GetFrameCount}查询帧数。
 * <br>资源管理：resVecPixMap数组由调用方提供，数组中的每个OH_PixelmapNative对象创建成功后都由调用方持有。使用完成后，需要逐个调用{@link OH_PixelmapNative_Destroy}释放。
 * 如果接口返回失败，也应检查数组中已写入的非空PixelMap指针并释放。
 * 
 * @param source 被操作的OH_ImageSourceNative指针。
 * @param  options 解码参数。
 * @param resVecPixMap Indicates a pointer array to the <b>Pixelmap</b> objects obtained at the C++ native layer.
 *     It cannot be a null pointer.
 * @param size 数组长度。 用户可以使用{@link OH_ImageSourceNative_GetFrameCount}获取。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：操作不支持。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceNative_CreatePixelmapList(OH_ImageSourceNative *source, OH_DecodingOptions *options,
    OH_PixelmapNative *resVecPixMap[], size_t size);

/**
 * @brief 通过图片解码创建OH_PictureNative指针。
 * <br>使用约束：source、options和picture均不能为空指针。
 * 
 * @param source 被操作的OH_ImageSourceNative指针。
 * @param options 解码参数。
 * @param picture 指向c++本地层创建的OH_PictureNative对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_DECODE_FAILED：解码失败。
 * @since 13
 */
Image_ErrorCode OH_ImageSourceNative_CreatePicture(OH_ImageSourceNative *source, OH_DecodingOptionsForPicture *options,
    OH_PictureNative **picture);

/**
 * @brief 通过指定序号的图片解码创建OH_PictureNative指针。
 * 
 * @param source 被操作的OH_ImageSourceNative指针。
 * @param index 解码图片序号。
 * @param picture 指向c++本地层创建的OH_PictureNative对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_SOURCE：数据源异常。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持的MIME类型。
 *     <br>IMAGE_SOURCE_TOO_LARGE：图像过大。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_OPTIONS：不支持的选项。例如，无效的图片序号。
 *     <br>IMAGE_DECODE_FAILED：解码失败。
 * @since 20
 */
Image_ErrorCode OH_ImageSourceNative_CreatePictureAtIndex(OH_ImageSourceNative *source, uint32_t index,
    OH_PictureNative **picture);

/**
 * @brief 获取图像延迟时间数组。
 * 
 * @param source 被操作的OH_ImageSourceNative指针。
 * @param delayTimeList 指向获得的延迟时间列表的指针。它不能是空指针。
 * @param size delayTimeList的大小。用户可以从{@link OH_ImageSourceNative_GetFrameCount}获得大小。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceNative_GetDelayTimeList(OH_ImageSourceNative *source, int32_t *delayTimeList, size_t size);

/**
 * @brief 获取指定序号的图片信息。
 * 
 * @param source 被操作的OH_ImageSourceNative指针。
 * @param index 图片序号。对GIF图片可传入[0,N-1],N表示GIF的帧数。对只有一帧数据的图片格式，可传入0。
 * @param info 指向获取的图像源信息的OH_ImageSource_Info指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceNative_GetImageInfo(OH_ImageSourceNative *source, int32_t index,
    OH_ImageSource_Info *info);

/**
 * @brief 获取图片指定属性键的值。
 * <br>该接口获取到的value.data缺少字符串结束符'\0'，请谨慎使用。
 * 
 * @param source 被操作的OH_ImageSourceNative指针。OH_ImageSourceNative使用完成后需要主动释放，参见{@link OH_ImageSourceNative_Release}。
 * @param key 指向属性的指针。key的取值范围请参考image_common.h的{@link 变量}中定义的OHOS_IMAGE_PROPERTY_XXX系列常量。
 * @param value 指向获取的值的指针（输出参数）。调用本接口前，用户应将value->data置为空指针，并将value->size设为0。接口会为value->data自动分配所需内存，并对value->size赋值。
 *     完成对该内存的使用后，用户必须使用C标准库提供的free()函数释放value->data指向的内存，否则会出现内存泄漏。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceNative_GetImageProperty(OH_ImageSourceNative *source, Image_String *key,
    Image_String *value);

/**
 * @brief 获取图像属性值。输出的value.data以字符串结束符'\0'结尾。
 * <br>使用场景：适用于读取字符串形式的图像属性，例如图片方向、拍摄时间、设备信息等。与{@link OH_ImageSourceNative_GetImageProperty}相比，本接口返回的value.data以'\0'结尾，
 * 更适合直接按C字符串处理。
 * <br>使用约束：source、key和value均不能为空指针。调用前应将value.data置为NULL、value.size置为0。接口执行成功后，可通过value.data和value.size读取属性值；接口执行失败时，
 * 不应读取value.data。
 * <br>资源管理：接口执行成功后，value.data由系统分配，调用方使用完成后必须调用free()释放。
 *
 * @param source 被操作的OH_ImageSourceNative指针。OH_ImageSourceNative使用完成后需要主动释放，参见{@link OH_ImageSourceNative_Release}。
 * @param key 指向属性键的指针。key的取值范围请参考image_common.h的{@link 变量}中定义的OHOS_IMAGE_PROPERTY_XXX系列常量。
 * @param value 指向属性值的指针（输出参数）。调用本接口前，用户应将value->data置为空指针，并将value->size设为0。接口会为value->data自动分配所需内存，并对value->size赋值。
 *     完成对该内存的使用后，用户必须使用C标准库提供的free()函数释放value->data指向的内存，否则可能导致内存泄漏。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为空。
 * @since 19
 */
Image_ErrorCode OH_ImageSourceNative_GetImagePropertyWithNull(OH_ImageSourceNative *source, Image_String *key,
    Image_String *value);

/**
 * @brief 通过指定的键修改图片属性的值。
 * <br>使用场景：适用于修改ImageSource中的图像属性，例如方向、用户注释等字符串属性。对于短整型、长整型、浮点型、数组或二进制对象类型的属性，优先使用对应的ModifyImagePropertyShort、
 * ModifyImagePropertyLong、ModifyImagePropertyDouble、ModifyImagePropertyIntArray、
 * ModifyImagePropertyDoubleArray或ModifyImagePropertyBlob接口，避免类型不匹配。
 * <br>资源管理：key和value指向的内存由调用方管理，接口不会接管其生命周期。修改后的属性保存在当前ImageSource对象中；如需生成包含修改后属性的图片文件或图片数据，需要结合编码接口重新输出。
 * 
 * @param source 被操作的OH_ImageSourceNative指针。OH_ImageSourceNative使用完成后需要主动释放，参见{@link OH_ImageSourceNative_Release}。
 * @param key 指向属性键的指针。key的取值范围请参考image_common.h的{@link 变量}中定义的OHOS_IMAGE_PROPERTY_XXX系列常量。
 * @param value 需要修改的属性值。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceNative_ModifyImageProperty(OH_ImageSourceNative *source, Image_String *key,
    Image_String *value);

/**
 * @brief 获取图像帧数。
 * 
 * @param source 被操作的OH_ImageSourceNative指针。
 * @param frameCount Indicates a pointer to the number of frames obtained.
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceNative_GetFrameCount(OH_ImageSourceNative *source, uint32_t *frameCount);

/**
 * @brief 释放OH_ImageSourceNative指针。
 * <br>资源管理：由OH_ImageSourceNative_CreateFromUri、OH_ImageSourceNative_CreateFromFd、OH_ImageSourceNative_CreateFromData、
 * OH_ImageSourceNative_CreateFromDataWithUserBuffer或OH_ImageSourceNative_CreateFromRawFile成功创建的对象，都应在不再使用时调用本接口释放。
 * 释放后不得再将该source传入读取图片信息、解码、读取或修改属性等接口。释放ImageSource不会自动释放已经创建出的OH_PixelmapNative、OH_PictureNative或OH_ImageRawData对象，
 * 这些对象需要分别调用对应释放接口。
 * 
 * @param source 要释放的OH_ImageSourceNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageSourceNative_Release(OH_ImageSourceNative *source);

/**
 * @brief 创建OH_DecodingOptionsForPicture指针。
 * <br>使用约束：options不能为空指针。接口返回失败时，输出参数的内容不能在后续流程中继续使用。
 * 
 * @param options 被操作的OH_DecodingOptionsForPicture指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_DecodingOptionsForPicture_Create(OH_DecodingOptionsForPicture **options);

/**
 * @brief 获取解码时设置的期望辅助图（期望解码出的picture包含的辅助图）。
 * <br>使用约束：options、desiredAuxiliaryPictures和length均不能为空指针。未设置期望辅助图时，接口返回IMAGE_BAD_PARAMETER。
 * <br>资源管理：接口成功返回的desiredAuxiliaryPictures数组由接口分配，使用完成后调用方应使用delete[]释放。
 * 
 * @param options 被操作的OH_DecodingOptionsForPicture指针。
 * @param desiredAuxiliaryPictures 解码选项中的期望辅助图。
 * @param length 期望辅助图长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_DecodingOptionsForPicture_GetDesiredAuxiliaryPictures(OH_DecodingOptionsForPicture *options,
    Image_AuxiliaryPictureType **desiredAuxiliaryPictures, size_t *length);

/**
 * @brief 设置解码选项中的期望辅助图。
 * <br>使用约束：options和desiredAuxiliaryPictures均不能为空指针，length必须大于0，
 * desiredAuxiliaryPictures数组中的辅助图类型必须为当前支持的Image_AuxiliaryPictureType。
 * <br>资源管理：接口会将传入数组中的辅助图类型保存到OH_DecodingOptionsForPicture对象中，不会持有传入的数组指针，接口返回后调用方可自行释放或复用该数组。多次调用该接口时，
 * 新传入的辅助图类型会追加到已有集合中；重复类型只保留一份。
 * 
 * @param options 被操作的OH_DecodingOptionsForPicture指针。
 * @param desiredAuxiliaryPictures 将要设置的期望辅助图。
 * @param length 期望辅助图长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_DecodingOptionsForPicture_SetDesiredAuxiliaryPictures(OH_DecodingOptionsForPicture *options,
    Image_AuxiliaryPictureType *desiredAuxiliaryPictures, size_t length);

/**
 * @brief 获取解码选项中的needsDecodeDfxData参数。
 *
 * @systemapi
 * @param options 指向OH_DecodingOptionsForPicture结构体的指针。
 * @param needsDecodeDfxData 图像DFX数据是否需要解码。true表示图像DFX数据需要解码，false表示图像DFX数据不需要解码。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>202：非系统应用程序调用该接口则返回此错误码。</li>
 *     <br><li>IMAGE_SOURCE_INVALID_PARAMETER：options或needsDecodeDfxData为空指针。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_DecodingOptionsForPicture_GetNeedsDecodeDfxData(OH_DecodingOptionsForPicture *options,
    bool *needsDecodeDfxData);

/**
 * @brief 设置解码选项中的needsDecodeDfxData参数。
 *
 * @systemapi
 * @param options 指向OH_DecodingOptionsForPicture结构体的指针。
 * @param needsDecodeDfxData 图像DFX数据是否需要解码。true表示图像DFX数据需要解码，false表示图像DFX数据不需要解码。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>202：非系统应用程序调用该接口则返回此错误码。</li>
 *     <br><li>IMAGE_SOURCE_INVALID_PARAMETER：options为空指针。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_DecodingOptionsForPicture_SetNeedsDecodeDfxData(OH_DecodingOptionsForPicture *options,
    bool needsDecodeDfxData);

/**
 * @brief 获取DecodingOptionsForPicture结构体中的主图期望尺寸。
 *
 * @systemapi
 * @param options 指向OH_DecodingOptionsForPicture结构体的指针。
 * @param desiredSizeForMainPixelmap 主图的期望尺寸。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>202：非系统应用程序调用该接口则返回此错误码。</li>
 *     <br><li>IMAGE_SOURCE_INVALID_PARAMETER：options为空指针。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_DecodingOptionsForPicture_GetDesiredSizeForMainPixelmap(OH_DecodingOptionsForPicture *options,
    Image_Size *desiredSizeForMainPixelmap);
 
/**
 * @brief 设置DecodingOptionsForPicture结构体中的主图期望尺寸。
 *
 * @systemapi
 * @param options 指向OH_DecodingOptionsForPicture结构体的指针。
 * @param desiredSizeForMainPixelmap 主图的期望尺寸。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>202：非系统应用程序调用该接口则返回此错误码。</li>
 *     <br><li>IMAGE_SOURCE_INVALID_PARAMETER：options为空指针。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_DecodingOptionsForPicture_SetDesiredSizeForMainPixelmap(OH_DecodingOptionsForPicture *options,
    Image_Size desiredSizeForMainPixelmap);
 
/**
 * @brief 获取DecodingOptionsForPicture结构体中的像素格式。
 *
 * @systemapi
 * @param options 指向OH_DecodingOptionsForPicture结构体的指针。
 * @param desiredPixelFormat 解码选项中的像素格式。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>202：非系统应用程序调用该接口则返回此错误码。</li>
 *     <br><li>IMAGE_SOURCE_INVALID_PARAMETER：options为空指针。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_DecodingOptionsForPicture_GetDesiredPixelFormat(OH_DecodingOptionsForPicture *options,
    PIXEL_FORMAT *desiredPixelFormat);
 
/**
 * @brief 设置DecodingOptionsForPicture结构体中的像素格式。
 *
 * @systemapi
 * @param options 指向OH_DecodingOptionsForPicture结构体的指针。
 * @param desiredPixelFormat 解码选项中的像素格式。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>202：非系统应用程序调用该接口则返回此错误码。</li>
 *     <br><li>IMAGE_SOURCE_INVALID_PARAMETER：options为空指针。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_DecodingOptionsForPicture_SetDesiredPixelFormat(OH_DecodingOptionsForPicture *options,
    PIXEL_FORMAT desiredPixelFormat);

/**
 * @brief 释放OH_DecodingOptionsForPicture指针。
 * 
 * @param options 要释放的OH_DecodingOptionsForPicture指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_DecodingOptionsForPicture_Release(OH_DecodingOptionsForPicture *options);

/**
  * @brief 获取支持解码的图片格式。
  * <br>使用场景：适用于在创建图片源或展示格式选择前，动态查询当前系统支持的解码格式。部分格式的解码能力可能和系统版本、设备能力有关，建议以该接口返回结果为准。
  * 
  * @param supportedFormats 支持解码的图片格式。
  * @param length 数组长度。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：参数异常，supportedFormats或length为空。
 * @since 20
 */
Image_ErrorCode OH_ImageSourceNative_GetSupportedFormats(Image_MimeType** supportedFormats, size_t* length);

/**
 * @brief 以短整型类型获取图像属性的值。
 *
 * @param source 被查询属性的ImageSource。
 * @param key 被查询的属性。
 * @param value 被查询的属性的查询结果。输出参数。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是短整型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_GetImagePropertyShort(OH_ImageSourceNative *source,
    Image_String *key, uint16_t *value);

/**
 * @brief 以长整型类型获取图像属性的值。
 *
 * @param source 被查询属性的ImageSource。
 * @param key 被查询的属性。
 * @param value 被查询属性的查询结果。输出参数。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是长整型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_GetImagePropertyLong(OH_ImageSourceNative *source,
    Image_String *key, uint32_t *value);

/**
 * @brief 以浮点型类型获取图像属性的值。
 *
 * @param source 被查询属性的ImageSource。
 * @param key 被查询的属性。
 * @param value 被查询属性的查询结果。输出参数。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是浮点型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_GetImagePropertyDouble(OH_ImageSourceNative *source,
    Image_String *key, double *value);

/**
 * @brief 获取数组类型属性的数组长度或字符串类型属性的字符串长度。
 * <br>使用场景：适用于读取字符串、数组或二进制对象类型的图像属性前，先查询需要分配的缓冲区大小。典型流程为：先调用本接口获取长度，再由调用方分配缓冲区，最后调用
 * {@link OH_ImageSourceNative_GetImagePropertyString}、{@link OH_ImageSourceNative_GetImagePropertyIntArray}、
 * {@link OH_ImageSourceNative_GetImagePropertyDoubleArray}或{@link OH_ImageSourceNative_GetImagePropertyBlob}读取实际内容。
 * <br>资源管理：本接口不分配属性值缓冲区。后续读取属性值时，如果缓冲区由调用方分配，则由调用方释放；如果使用{@link OH_ImageSourceNative_GetImageProperty}或
 * {@link OH_ImageSourceNative_GetImagePropertyWithNull}由系统分配value->data，使用完成后必须调用free()释放。
 *
 * @param source 被查询属性的ImageSource。
 * @param key 被查询的属性。
 * @param size 数组类型属性的数组长度，字符串类型属性的字符串长度。输出参数。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是数组或字符串类型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_GetImagePropertyArraySize(OH_ImageSourceNative *source,
    Image_String *key, size_t *size);

/**
 * @brief 以字符串类型获取图像属性的值。
 *
 * @param source 被查询属性的ImageSource。
 * @param key 被查询的属性。
 * @param value 被查询属性的查询结果。输出参数。调用者需要管理内存应用程序并释放。
 * @param size 字符串长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是字符串类型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_GetImagePropertyString(OH_ImageSourceNative *source,
    Image_String *key, char *value, size_t size);

/**
 * @brief 以整型数组类型获取图像属性的值。
 *
 * @param source 被查询属性的ImageSource。
 * @param key 被查询的属性。
 * @param value 被查询属性的查询结果。输出参数。调用者需要管理内存应用程序并释放。
 * @param size 字符串长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是整型数组类型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_GetImagePropertyIntArray(OH_ImageSourceNative *source,
    Image_String *key, int32_t *value, size_t size);

/**
 * @brief 以浮点型数组类型获取图像属性的值。
 *
 * @param source 被查询属性的ImageSource。
 * @param key 被查询的属性。
 * @param value 被查询属性的查询结果。输出参数。调用者需要管理内存应用程序并释放。
 * @param size 数组长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是浮点型数组类型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_GetImagePropertyDoubleArray(OH_ImageSourceNative *source,
    Image_String *key, double *value, size_t size);

/**
 * @brief 以二进制对象类型获取图像属性的值。
 *
 * @param source 被查询属性的ImageSource。
 * @param key 被查询的属性。
 * @param value 被查询属性的查询结果。输出参数。调用者需要管理内存应用程序并释放。
 * @param size 数组长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是二进制对象类型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_GetImagePropertyBlob(OH_ImageSourceNative *source, Image_String *key,
    void *value, size_t size);

/**
 * @brief 修改图像属性中短整型的值。
 *
 * @param source 被修改属性的ImageSource。
 * @param key 被修改的属性。
 * @param value 为属性设置的值。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是短整型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_ModifyImagePropertyShort(OH_ImageSourceNative *source, Image_String *key,
    uint16_t value);

/**
 * @brief 修改图像属性中长整型的值。
 *
 * @param source 被修改属性的ImageSource。
 * @param key 被修改的属性。
 * @param value 为属性设置的值。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是长整型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_ModifyImagePropertyLong(OH_ImageSourceNative *source, Image_String *key,
    uint32_t value);

/**
 * @brief 修改图像属性中浮点型的值。
 *
 * @param source 被修改属性的ImageSource。
 * @param key 被修改的属性。
 * @param value 为属性设置的值。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是浮点型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_ModifyImagePropertyDouble(OH_ImageSourceNative *source, Image_String *key,
    double value);

/**
 * @brief 修改图像属性中整型数组型的值。
 *
 * @param source 被修改属性的ImageSource。
 * @param key 被修改的属性。
 * @param value 为属性设置的值。
 * @param size 数组长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是整型数组类型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_ModifyImagePropertyIntArray(OH_ImageSourceNative *source, Image_String *key,
    int32_t *value, size_t size);

/**
 * @brief 修改图像属性中浮点型数组型的值。
 *
 * @param source 被修改属性的ImageSource。
 * @param key 被修改的属性。
 * @param value 为属性设置的值。
 * @param size 数组长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是浮点型数组类型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_ModifyImagePropertyDoubleArray(OH_ImageSourceNative *source, Image_String *key,
    double *value, size_t size);

/**
 * @brief 修改图像属性中二进制对象的值。
 *
 * @param source 被修改属性的ImageSource。
 * @param key 被修改的属性。
 * @param value 为属性设置的值。
 * @param size 数组长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：source、key或value为nullptr。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持查询当前mimetype的图像属性。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_METADATA：指定的元数据不存在，或者不是二进制对象类型的值。
 * @since 23
 */
Image_ErrorCode OH_ImageSourceNative_ModifyImagePropertyBlob(OH_ImageSourceNative *source, Image_String *key,
    void *value, size_t size);

/**
 * @brief 读取图像源的元数据，使用metadataTypes参数指定要读取的元数据类型。如果未指定metadataTypes，将返回所有支持的元数据。
 *
 * @systemapi
 * @param source 指向图像源的指针。
 * @param index 图片索引。
 * @param metadataTypes 指定的元数据类型。
 * @param typeCount 指定的元数据类型的数量。
 * @param outMetadataArray 输出参数，用于接收本函数分配的元数据数组。使用完成后调用者需要释放该对象。
 * @param metadataCount 输出的元数据数组中返回的OH_PictureMetadata元素数量。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>202：非系统应用程序调用该接口则返回此错误码。</li>
 *     <br><li>IMAGE_SOURCE_INVALID_PARAMETER：source、outMetadataArray或metadataCount为空指针。</li>
 *     <br><li>IMAGE_SOURCE_UNSUPPORTED_METADATA：元数据不存在，或类型不支持。</li>
 *     <br><li>IMAGE_SOURCE_ALLOC_FAILED：内存分配失败。</li>
 *     <br></ul>
 * @release image_common/OH_PictureMetadatas_Release {outMetadataArray}
 * @since 26.0.0
 */
Image_ErrorCode OH_ImageSourceNative_ReadImageMetadataByType(OH_ImageSourceNative *source, uint32_t index,
    Image_MetadataType *metadataTypes, size_t typeCount, OH_PictureMetadata **outMetadataArray, size_t *metadataCount);

/**
 * @brief OH_ImageRawData用于承载图像中的原始数据。<br>使用{@link OH_ImageSourceNative_CreateImageRawData}
 * 函数从OH_ImageSourceNative对象中创建OH_ImageRawData对象。<br>使用{@link OH_ImageSourceNative_DestroyImageRawData}
 * 函数销毁OH_ImageRawData对象。<br>资源管理：OH_ImageRawData使用完成后，应调用{@link OH_ImageSourceNative_DestroyImageRawData}销毁。
 * 释放OH_ImageSourceNative对象不会自动销毁OH_ImageRawData对象，二者生命周期相互独立。通过{@link OH_ImageSourceNative_GetBufferFromRawData}
 * 获取到的data指向OH_ImageRawData对象内部缓冲区，调用方不应对data调用free()。OH_ImageRawData对象销毁后，该data地址失效。如需在OH_ImageRawData对象销毁后继续使用数据，
 * 应在销毁前自行拷贝。<br>OH_ImageRawData结构体内容和操作方式如下：<br>| 字段类型 | 字段名称 | 字段描述 | 字段获取函数 || -- | -- | -- | -- || uint8_t * | data
 * | 原始数据缓冲区首地址。 | {@link OH_ImageSourceNative_GetBufferFromRawData} || size_t | length | 原始数据缓冲区长度。 |
 * {@link OH_ImageSourceNative_GetBufferFromRawData} || uint8_t | bitsPerPixel | 缓冲区数据中每个像素实际占用的位数。 |
 * {@link OH_ImageSourceNative_GetBitsPerPixelFromRawData} |
 *
 * @since 24
 */
struct OH_ImageRawData;

/**
 * @brief OH_ImageRawData用于承载图像中的原始数据。<br>使用{@link OH_ImageSourceNative_CreateImageRawData}
 * 函数从OH_ImageSourceNative对象中创建OH_ImageRawData对象。<br>使用{@link OH_ImageSourceNative_DestroyImageRawData}
 * 函数销毁OH_ImageRawData对象。<br>资源管理：OH_ImageRawData使用完成后，应调用{@link OH_ImageSourceNative_DestroyImageRawData}销毁。
 * 释放OH_ImageSourceNative对象不会自动销毁OH_ImageRawData对象，二者生命周期相互独立。通过{@link OH_ImageSourceNative_GetBufferFromRawData}
 * 获取到的data指向OH_ImageRawData对象内部缓冲区，调用方不应对data调用free()。OH_ImageRawData对象销毁后，该data地址失效。如需在OH_ImageRawData对象销毁后继续使用数据，
 * 应在销毁前自行拷贝。<br>OH_ImageRawData结构体内容和操作方式如下：<br>| 字段类型 | 字段名称 | 字段描述 | 字段获取函数 || -- | -- | -- | -- || uint8_t * | data
 * | 原始数据缓冲区首地址。 | {@link OH_ImageSourceNative_GetBufferFromRawData} || size_t | length | 原始数据缓冲区长度。 |
 * {@link OH_ImageSourceNative_GetBufferFromRawData} || uint8_t | bitsPerPixel | 缓冲区数据中每个像素实际占用的位数。 |
 * {@link OH_ImageSourceNative_GetBitsPerPixelFromRawData} |
 *
 * @since 24
 */
typedef struct OH_ImageRawData OH_ImageRawData;

/**
 * @brief 从图像中获取rawData对象。rawData对象通常占用大量内存，因为它包含来自相机的原始数据。
 * <br>当不再使用rawData对象时，请及时调用{@link OH_ImageSourceNative_DestroyImageRawData}方法销毁，以释放内存资源。
 * <br>使用场景：适用于从包含原始图像数据的图片源中读取rawData，并交给自定义图像处理、算法分析或保存链路使用。普通图片显示或常规像素处理场景，通常应使用
 * {@link OH_ImageSourceNative_CreatePixelmap}解码为PixelMap。
 * <br>资源管理：成功创建的OH_ImageRawData对象由调用方持有，使用完成后必须调用{@link OH_ImageSourceNative_DestroyImageRawData}销毁。
 * rawData对象和OH_ImageSourceNative对象生命周期相互独立，释放ImageSource不会自动销毁rawData。
 *
 * @param source 指向图像源的指针。
 * @param rawData 解码后获得的rawData对象的双指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_SOURCE：源错误。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：rawData对象无效。
 *     <br>IMAGE_SOURCE_UNSUPPORTED_MIME_TYPE：不支持的MIME类型。
 * @since 24
 */
Image_ErrorCode OH_ImageSourceNative_CreateImageRawData(const OH_ImageSourceNative *source, OH_ImageRawData **rawData);

/**
 * @brief Gets binary data from the rawData object.
 *
 * @param rawData Pointer to the rawData object.
 * @param data Pointer to the binary buffer data.
 * @param length Pointer to the length of data obtained.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_SOURCE_INVALID_PARAMETER} if the rawData object is invalid.
 * @since 24
 */
 Image_ErrorCode OH_ImageSourceNative_GetBufferFromRawData(const OH_ImageRawData *rawData,
    uint8_t **data, size_t *length);

/**
 * @brief 获取缓冲区数据中每个像素实际占用的位数。
 *
 * @param rawData 指向rawData对象的指针。
 * @param bitsPerPixel 指向所获取的每像素位数的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：rawData对象无效。
 * @since 24
 */
Image_ErrorCode OH_ImageSourceNative_GetBitsPerPixelFromRawData(const OH_ImageRawData *rawData, uint8_t *bitsPerPixel);

/**
 * @brief 销毁rawData对象。
 * <br>资源管理：该接口只销毁OH_ImageRawData对象及其内部资源，不会释放OH_ImageSourceNative对象。销毁后，之前通过
 * {@link OH_ImageSourceNative_GetBufferFromRawData}获取到的data地址立即失效。
 *
 * @param rawData 指向rawData对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_SOURCE_INVALID_PARAMETER：rawData对象无效。
 * @since 24
 */
Image_ErrorCode OH_ImageSourceNative_DestroyImageRawData(OH_ImageRawData *rawData);

#ifdef __cplusplus
};
#endif
/** @} */
#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_IMAGE_SOURCE_NATIVE_H_

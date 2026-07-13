/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
 * @brief Provides APIs for obtaining picture data and information.
 *
 * @since 13
 */

/**
 * @file picture_native.h
 *
 * @brief 提供获取picture数据和信息的API。
 * 
 * @library libpicture.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 13
 */
#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PICTURE_NATIVE_H_
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PICTURE_NATIVE_H_
#include <stdbool.h>

#include "image_common.h"
#include "pixelmap_native.h"
 
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Picture结构体类型，用于执行picture相关操作。<br>Picture为多图对象结构体，包含主图、辅助图和元数据。<br>主图包含图像的大部分信息，主要用于显示图像内容。<br>
 * 辅助图用于存储与主图相关但不同的数据，展示图像更丰富的信息。<br>元数据一般用来存储关于图像文件的信息。<br>有多种方式创建OH_PictureNative，具体如下：<br>使用
 * {@link OH_PictureNative_Release}函数释放OH_PictureNative对象。<br>使用约束：使用OH_PictureNative对象前，需先创建对象；使用完成后，应调用
 * {@link OH_PictureNative_Release}释放对象。通过{@link OH_ImageSourceNative_CreatePicture}或
 * {@link OH_ImageSourceNative_CreatePictureAtIndex}解码Picture时，图片源格式需支持Picture解码。通过
 * {@link OH_PictureNative_CreatePicture}创建Picture时，mainPixelmap和picture均不能为空指针。<br>资源管理：
 * 释放OH_ImageSourceNative对象不会自动释放已创建的OH_PictureNative对象。通过OH_PictureNative获取到的OH_PixelmapNative、
 * OH_AuxiliaryPictureNative和OH_PictureMetadata对象由调用方管理，使用完成后需分别调用{@link OH_PixelmapNative_Destroy}、
 * {@link OH_AuxiliaryPictureNative_Release}和{@link OH_PictureMetadata_Release}释放。获取PixelMap、辅助图或元数据的接口返回失败时，
 * 输出参数的内容不能在后续流程中继续使用。<br>OH_PictureNative结构体内容和操作方式如下：
 * 
 * @since 13
 */
struct OH_PictureNative;

/**
 * @brief Picture结构体类型，用于执行picture相关操作。<br>Picture为多图对象结构体，包含主图、辅助图和元数据。<br>主图包含图像的大部分信息，主要用于显示图像内容。<br>
 * 辅助图用于存储与主图相关但不同的数据，展示图像更丰富的信息。<br>元数据一般用来存储关于图像文件的信息。<br>有多种方式创建OH_PictureNative，具体如下：<br>使用
 * {@link OH_PictureNative_Release}函数释放OH_PictureNative对象。<br>使用约束：使用OH_PictureNative对象前，需先创建对象；使用完成后，应调用
 * {@link OH_PictureNative_Release}释放对象。通过{@link OH_ImageSourceNative_CreatePicture}或
 * {@link OH_ImageSourceNative_CreatePictureAtIndex}解码Picture时，图片源格式需支持Picture解码。通过
 * {@link OH_PictureNative_CreatePicture}创建Picture时，mainPixelmap和picture均不能为空指针。<br>资源管理：
 * 释放OH_ImageSourceNative对象不会自动释放已创建的OH_PictureNative对象。通过OH_PictureNative获取到的OH_PixelmapNative、
 * OH_AuxiliaryPictureNative和OH_PictureMetadata对象由调用方管理，使用完成后需分别调用{@link OH_PixelmapNative_Destroy}、
 * {@link OH_AuxiliaryPictureNative_Release}和{@link OH_PictureMetadata_Release}释放。获取PixelMap、辅助图或元数据的接口返回失败时，
 * 输出参数的内容不能在后续流程中继续使用。<br>OH_PictureNative结构体内容和操作方式如下：
 * 
 * @since 13
 */
typedef struct OH_PictureNative OH_PictureNative;

/**
 * @brief AuxiliaryPicture结构体类型，用于执行AuxiliaryPicture相关操作。<br>使用{@link OH_AuxiliaryPictureNative_Create}
 * 函数创建OH_AuxiliaryPictureNative对象。<br>使用{@link OH_PictureNative_GetAuxiliaryPicture}
 * 函数从OH_PictureNative对象中按辅助图类型获取OH_AuxiliaryPictureNative对象。<br>使用{@link OH_AuxiliaryPictureNative_Release}
 * 函数释放OH_AuxiliaryPictureNative对象。<br>使用约束：使用OH_AuxiliaryPictureNative对象前，需先创建或获取对象；使用完成后，应调用
 * {@link OH_AuxiliaryPictureNative_Release}释放对象。通过{@link OH_AuxiliaryPictureNative_Create}创建对象时，data、
 * size和auxiliaryPicture均不能为空指针，dataLength必须大于0，type必须为当前支持的{@link Image_AuxiliaryPictureType}。<br>资源管理：
 * 释放OH_PictureNative对象不会自动释放已经获取出的OH_AuxiliaryPictureNative对象；
 * 释放OH_AuxiliaryPictureNative对象也不会从OH_PictureNative对象中移除对应辅助图。通过{@link OH_AuxiliaryPictureNative_GetInfo}
 * 获取到的OH_AuxiliaryPictureInfo对象由调用方管理，使用完成后应调用{@link OH_AuxiliaryPictureInfo_Release}释放。通过
 * {@link OH_AuxiliaryPictureNative_GetMetadata}获取到的OH_PictureMetadata对象由调用方管理，使用完成后应调用
 * {@link OH_PictureMetadata_Release}释放。接口返回失败时，输出参数的内容不能在后续流程中继续使用。<br>OH_AuxiliaryPictureNative结构体内容和操作方式如下：
 * 
 * @since 13
 */
struct OH_AuxiliaryPictureNative;

/**
 * @brief AuxiliaryPicture结构体类型，用于执行AuxiliaryPicture相关操作。<br>使用{@link OH_AuxiliaryPictureNative_Create}
 * 函数创建OH_AuxiliaryPictureNative对象。<br>使用{@link OH_PictureNative_GetAuxiliaryPicture}
 * 函数从OH_PictureNative对象中按辅助图类型获取OH_AuxiliaryPictureNative对象。<br>使用{@link OH_AuxiliaryPictureNative_Release}
 * 函数释放OH_AuxiliaryPictureNative对象。<br>使用约束：使用OH_AuxiliaryPictureNative对象前，需先创建或获取对象；使用完成后，应调用
 * {@link OH_AuxiliaryPictureNative_Release}释放对象。通过{@link OH_AuxiliaryPictureNative_Create}创建对象时，data、
 * size和auxiliaryPicture均不能为空指针，dataLength必须大于0，type必须为当前支持的{@link Image_AuxiliaryPictureType}。<br>资源管理：
 * 释放OH_PictureNative对象不会自动释放已经获取出的OH_AuxiliaryPictureNative对象；
 * 释放OH_AuxiliaryPictureNative对象也不会从OH_PictureNative对象中移除对应辅助图。通过{@link OH_AuxiliaryPictureNative_GetInfo}
 * 获取到的OH_AuxiliaryPictureInfo对象由调用方管理，使用完成后应调用{@link OH_AuxiliaryPictureInfo_Release}释放。通过
 * {@link OH_AuxiliaryPictureNative_GetMetadata}获取到的OH_PictureMetadata对象由调用方管理，使用完成后应调用
 * {@link OH_PictureMetadata_Release}释放。接口返回失败时，输出参数的内容不能在后续流程中继续使用。<br>OH_AuxiliaryPictureNative结构体内容和操作方式如下：
 * 
 * @since 13
 */
typedef struct OH_AuxiliaryPictureNative OH_AuxiliaryPictureNative;

/**
 * @brief AuxiliaryPictureInfo结构体类型，用于执行AuxiliaryPictureInfo相关操作。<br>使用{@link OH_AuxiliaryPictureInfo_Create}
 * 函数创建OH_AuxiliaryPictureInfo对象。<br>使用{@link OH_AuxiliaryPictureNative_GetInfo}
 * 函数从OH_AuxiliaryPictureNative对象中获取OH_AuxiliaryPictureInfo对象。<br>使用{@link OH_AuxiliaryPictureInfo_Release}
 * 函数释放OH_AuxiliaryPictureInfo对象。<br>使用约束：使用OH_AuxiliaryPictureInfo对象前，需先创建或获取对象；使用完成后，应调用
 * {@link OH_AuxiliaryPictureInfo_Release}释放对象。调用{@link OH_AuxiliaryPictureInfo_GetType}、
 * {@link OH_AuxiliaryPictureInfo_GetSize}、{@link OH_AuxiliaryPictureInfo_GetRowStride}或
 * {@link OH_AuxiliaryPictureInfo_GetPixelFormat}时，输出参数不允许传入nullptr；接口返回失败时，输出参数的内容不能在后续流程中继续使用。
 * 只有在明确辅助图实际状态与OH_AuxiliaryPictureInfo对象信息不一致或有明确业务诉求时，才需要手动设置OH_AuxiliaryPictureInfo。<br>资源管理：
 * {@link OH_AuxiliaryPictureNative_GetInfo}成功返回的OH_AuxiliaryPictureInfo对象由调用方管理。通过
 * {@link OH_AuxiliaryPictureNative_SetInfo}设置辅助图信息时，接口会读取并保存OH_AuxiliaryPictureInfo中的信息值，
 * 接口返回后调用方仍需自行管理该OH_AuxiliaryPictureInfo对象的生命周期。<br>OH_AuxiliaryPictureInfo结构体内容和操作方式如下：
 * 
 * @since 13
 */
struct OH_AuxiliaryPictureInfo;

/**
 * @brief AuxiliaryPictureInfo结构体类型，用于执行AuxiliaryPictureInfo相关操作。<br>使用{@link OH_AuxiliaryPictureInfo_Create}
 * 函数创建OH_AuxiliaryPictureInfo对象。<br>使用{@link OH_AuxiliaryPictureNative_GetInfo}
 * 函数从OH_AuxiliaryPictureNative对象中获取OH_AuxiliaryPictureInfo对象。<br>使用{@link OH_AuxiliaryPictureInfo_Release}
 * 函数释放OH_AuxiliaryPictureInfo对象。<br>使用约束：使用OH_AuxiliaryPictureInfo对象前，需先创建或获取对象；使用完成后，应调用
 * {@link OH_AuxiliaryPictureInfo_Release}释放对象。调用{@link OH_AuxiliaryPictureInfo_GetType}、
 * {@link OH_AuxiliaryPictureInfo_GetSize}、{@link OH_AuxiliaryPictureInfo_GetRowStride}或
 * {@link OH_AuxiliaryPictureInfo_GetPixelFormat}时，输出参数不允许传入nullptr；接口返回失败时，输出参数的内容不能在后续流程中继续使用。
 * 只有在明确辅助图实际状态与OH_AuxiliaryPictureInfo对象信息不一致或有明确业务诉求时，才需要手动设置OH_AuxiliaryPictureInfo。<br>资源管理：
 * {@link OH_AuxiliaryPictureNative_GetInfo}成功返回的OH_AuxiliaryPictureInfo对象由调用方管理。通过
 * {@link OH_AuxiliaryPictureNative_SetInfo}设置辅助图信息时，接口会读取并保存OH_AuxiliaryPictureInfo中的信息值，
 * 接口返回后调用方仍需自行管理该OH_AuxiliaryPictureInfo对象的生命周期。<br>OH_AuxiliaryPictureInfo结构体内容和操作方式如下：
 * 
 * @since 13
 */
typedef struct OH_AuxiliaryPictureInfo OH_AuxiliaryPictureInfo;

/**
 * @brief 辅助图类型。
 *
 * @since 13
 */
typedef enum {
    /**
     * 增益图，代表了一种增强SDR图像以产生具有可变显示调整能力的HDR图像的机制。它是一组描述如何应用gainmap元数据的组合。
     */
    AUXILIARY_PICTURE_TYPE_GAINMAP = 1,
    /**
     * 深度图，储存图像的深度数据，通过捕捉每个像素与摄像机之间的距离，提供场景的三维结构信息，通常用于3D重建和场景理解。
     */
    AUXILIARY_PICTURE_TYPE_DEPTH_MAP = 2,
    /**
     * 人像未对焦的原图，提供了一种在人像拍摄中突出背景模糊效果的方式，能够帮助用户在后期处理中选择焦点区域，增加创作自由度。
     */
    AUXILIARY_PICTURE_TYPE_UNREFOCUS_MAP = 3,
    /**
     * 线性图，用于提供额外的数据视角或补充信息，通常用于视觉效果的增强，它可以包含场景中光照、颜色或其他视觉元素的线性表示。
     */
    AUXILIARY_PICTURE_TYPE_LINEAR_MAP = 4,
    /**
     * 水印裁剪图，表示在原图中被水印覆盖的区域，该图像用于修复或移除水印影响，恢复图像的完整性和可视性。
     */
    AUXILIARY_PICTURE_TYPE_FRAGMENT_MAP = 5,
} Image_AuxiliaryPictureType;

/**
 * @brief OH_ComposeOptions是native层封装的合成HDR选项参数结构体，用于设置合成选项参数。用于指定合成HDR所用的参数，例如目标像素格式。
 * 
 * @since 23
 */
typedef struct OH_ComposeOptions OH_ComposeOptions;

/**
 * @brief 创建OH_ComposeOptions实例。
 * 
 * @param options 被操作的OH_ComposeOptions指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 23
 */
Image_ErrorCode OH_ComposeOptions_Create(OH_ComposeOptions **options);

/**
 * @brief 设置OH_ComposeOptions中的目标像素格式。
 * 
 * @param options 被操作的OH_ComposeOptions指针。
 * @param desiredPixelFormat 被设置的像素格式，支持RGBA_1010102、YCBCR_P010和YCRCB_P010格式。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误，例如options为nullptr或传入了不支持的desiredPixelFormat。
 * @since 23
 */
Image_ErrorCode OH_ComposeOptions_SetDesiredPixelFormat(OH_ComposeOptions *options, PIXEL_FORMAT desiredPixelFormat);

/**
 * @brief 获取OH_ComposeOptions中的像素格式。
 * 
 * @param options 被操作的OH_ComposeOptions指针。
 * @param desiredPixelFormat 合成选项中的像素格式。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 23
 */
Image_ErrorCode OH_ComposeOptions_GetDesiredPixelFormat(OH_ComposeOptions *options, PIXEL_FORMAT *desiredPixelFormat);

/**
 * @brief 释放OH_ComposeOptions指针。
 * 
 * @param options 被操作的OH_ComposeOptions指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 23
 */
Image_ErrorCode OH_ComposeOptions_Release(OH_ComposeOptions *options);

/**
 * @brief 创建OH_PictureNative指针。
 * 
 * @param mainPixelmap 主图的OH_PixelmapNative指针。
 * @param picture 被创建的OH_PictureNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_PictureNative_CreatePicture(OH_PixelmapNative *mainPixelmap, OH_PictureNative **picture);

/**
 * @brief 获取主图的OH_PixelmapNative指针。
 * 
 * @param picture 被操作的OH_PictureNative指针。
 * @param mainPixelmap 获取的OH_PixelmapNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_PictureNative_GetMainPixelmap(OH_PictureNative *picture, OH_PixelmapNative **mainPixelmap);

/**
 * @brief 获取hdr图的OH_PixelmapNative指针。
 * <br>使用约束：picture和hdrPixelmap均不能为空指针。Picture不支持HDR合成时，接口会返回IMAGE_UNSUPPORTED_OPERATION。
 * 
 * @param picture 被操作的OH_PictureNative指针。
 * @param hdrPixelmap 获取的hdr图OH_PixelmapNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：操作不支持，例如picture对象中不包含增益图。
 * @since 13
 */
Image_ErrorCode OH_PictureNative_GetHdrComposedPixelmap(OH_PictureNative *picture, OH_PixelmapNative **hdrPixelmap);

/**
 * @brief 通过设置合成选项OH_ComposeOptions获取HDR图的OH_PixelmapNative指针。
 * <br>使用约束：picture、options和hdrPixelmap均不能为空指针。Picture不支持HDR合成时，接口会返回IMAGE_UNSUPPORTED_OPERATION。
 * 
 * @param picture 被操作的OH_PictureNative指针。
 * @param options 合成选项OH_ComposeOptions指针。
 * @param hdrPixelmap 获取的HDR图OH_PixelmapNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：操作不支持，例如picture对象中不包含增益图。
 * @since 23
 */
Image_ErrorCode OH_PictureNative_GetHdrComposedPixelmapWithOptions(OH_PictureNative *picture, OH_ComposeOptions *options, OH_PixelmapNative **hdrPixelmap);

/**
 * @brief 获取增益图的OH_PixelmapNative指针。
 * 
 * @param picture 被操作的OH_PictureNative指针。
 * @param gainmapPixelmap 获取的增益图OH_PixelmapNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_PictureNative_GetGainmapPixelmap(OH_PictureNative *picture, OH_PixelmapNative **gainmapPixelmap);

/**
 * @brief 设置辅助图。
 * <br>使用约束：picture和auxiliaryPicture均不能为空指针，type必须为当前支持的辅助图类型，且必须与auxiliaryPicture对象自身的辅助图类型一致。
 * 
 * @param picture 被操作的OH_PictureNative指针。
 * @param type 辅助图的类型。
 * @param auxiliaryPicture 设置的OH_AuxiliaryPictureNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_PictureNative_SetAuxiliaryPicture(OH_PictureNative *picture, Image_AuxiliaryPictureType type,
    OH_AuxiliaryPictureNative *auxiliaryPicture);

/**
 * @brief 根据类型获取辅助图。
 * <br>使用约束：picture和auxiliaryPicture均不能为空指针，type必须为当前支持的辅助图类型。
 * 
 * @param picture 被操作的OH_PictureNative指针。
 * @param type 辅助图类型。
 * @param auxiliaryPicture 获取的OH_AuxiliaryPictureNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_PictureNative_GetAuxiliaryPicture(OH_PictureNative *picture, Image_AuxiliaryPictureType type,
    OH_AuxiliaryPictureNative **auxiliaryPicture);

/**
 * @brief 获取主图的元数据。
 * <br>使用约束：picture和metadata均不能为空指针，metadataType必须为Picture允许的元数据类型；不支持的元数据类型会返回IMAGE_UNSUPPORTED_METADATA。
 * 
 * @param picture 被操作的OH_PictureNative指针。
 * @param metadataType 元数据类型。
 * @param metadata 主图的元数据。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_METADATA：不支持的元数据类型。
 * @since 13
 */
Image_ErrorCode OH_PictureNative_GetMetadata(OH_PictureNative *picture, Image_MetadataType metadataType,
    OH_PictureMetadata **metadata);

/**
 * @brief 设置主图的元数据。
 * <br>使用约束：picture和metadata均不能为空指针，metadataType必须为Picture允许的元数据类型。
 * 
 * @param picture 被操作的OH_PictureNative指针。
 * @param metadataType 元数据类型。
 * @param metadata 将设置的元数据。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_METADATA：不支持的元数据类型。
 * @since 13
 */
Image_ErrorCode OH_PictureNative_SetMetadata(OH_PictureNative *picture, Image_MetadataType metadataType,
    OH_PictureMetadata *metadata);

/**
 * @brief 获取辅助图数量。
 *
 * @param picture 指向OH_PictureNative对象的指针。
 * @param count 辅助图数量。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：picture或count为空指针、获取picture失败。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_GetAuxiliaryPictureCount(OH_PictureNative *picture, uint32_t *count);

/**
 * @brief 获取辅助图类型。
 *
 * @param picture 指向OH_PictureNative对象的指针。
 * @param auxiliaryPictureTypes 指向接收辅助图类型的数组的指针。
 * @param count 输入时，为辅助图类型数组的大小。输出时，为辅助图的实际数量。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：picture、auxiliaryPictureTypes或count为空指针、无法获取图片、count小于要求。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_GetAuxiliaryPictureTypes(OH_PictureNative *picture,
    Image_AuxiliaryPictureType *auxiliaryPictureTypes, uint32_t *count);

/**
 * @brief 获取Picture对象中元数据的数量。
 *
 * @param picture 指向OH_PictureNative对象的指针。
 * @param count 元数据数量。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：picture或count为空指针、获取picture失败。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_GetMetadataCount(OH_PictureNative *picture, uint32_t *count);

/**
 * @brief 获取Picture对象中元数据的类型。
 *
 * @param picture 指向OH_PictureNative对象的指针。
 * @param metadataTypes 接收元数据类型的数组指针。
 * @param count 输入时，metadataTypes数组的大小。输出时，元数据的实际数量。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：picture、metadataTypes或count为空指针、获取picture失败、count小于所需大小。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_GetMetadataTypes(OH_PictureNative *picture,
    Image_MetadataType *metadataTypes, uint32_t *count);

/**
 * @brief 从Picture对象中移除辅助图。
 *
 * @param picture 指向OH_PictureNative对象的指针。
 * @param type 移除的辅助图类型。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：辅助图被成功移除或不存在。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：picture为空指针、获取picture失败、辅助图类型不支持。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_RemoveAuxiliaryPicture(OH_PictureNative *picture, Image_AuxiliaryPictureType type);

/**
 * @brief 从Picture对象中移除元数据。
 *
 * @param picture 指向OH_PictureNative对象的指针。
 * @param type 移除的元数据类型。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：元数据被成功移除或不存在。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：picture为空指针、获取picture失败。</li>
 *     <br><li>IMAGE_UNSUPPORTED_METADATA：不支持的元数据类型。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_RemoveMetadata(OH_PictureNative *picture, Image_MetadataType type);

/**
 * @brief 此结构体用于在创建PictureNative对象的深拷贝时指定辅助图的拷贝规则。描述如何将辅助图从一种类型拷贝到另一种类型。
 *
 * @since 26.0.0
 */
typedef struct OH_PictureNative_AuxiliaryPictureCopyItem {
    /**
     * @brief 
     * @since 26.0.0
     */
    Image_AuxiliaryPictureType srcType;

    /**
     * @brief 
     * @since 26.0.0
     */
    Image_AuxiliaryPictureType dstType;
} OH_PictureNative_AuxiliaryPictureCopyItem;

/**
 * @brief 此结构体用于在创建PictureNative对象的深拷贝时指定元数据的拷贝规则。描述如何将元数据从一种类型拷贝到另一种类型。
 *
 * @since 26.0.0
 */
typedef struct OH_PictureNative_MetadataCopyItem {
    /**
     * @brief 
     * @since 26.0.0
     */
    Image_MetadataType srcType;

    /**
     * @brief 
     * @since 26.0.0
     */
    Image_MetadataType dstType;
} OH_PictureNative_MetadataCopyItem;

/**
 * @brief 创建PictureNative对象的深拷贝，并将指定的辅助图和元数据拷贝到指定的目标类型。
 *
 * @param source 源PictureNative对象，不能为NULL。
 * @param auxiliaryPictureCopyItems 描述需要拷贝的辅助图的结构体。包括源辅助图和目标辅助图类型。如果auxiliaryPictureCopyCount为0，可以为NULL。
 * @param auxiliaryPictureCopyCount 需要拷贝的辅助图数量。
 * @param metadataCopyItems 描述需要拷贝的元数据的结构体。包括源元数据类型和目标元数据类型。如果metadataCopyCount为0，可以为NULL。
 * @param metadataCopyCount 需要拷贝的元数据数量。
 * @param sourceAuxPictureAsMainPixelMap 指定源图片中作为拷贝图片主图的辅助图类型。如果应使用原始主图，可以为NULL。
 * @param picture 输出参数，用于接收新创建的PictureNative对象。当调用者不再需要时释放该对象。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：source或picture为空指针、获取picture失败或数量不匹配、数量不为零但对应数组为空指针。</li>
 *     <br><li>IMAGE_ALLOC_FAILED：内存分配失败。</li>
 *     <br></ul>
 * @release picture_native/OH_PictureNative_Release {picture}
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_DeepCopyWithItems(
    OH_PictureNative *source,
    const OH_PictureNative_AuxiliaryPictureCopyItem *auxiliaryPictureCopyItems, uint32_t auxiliaryPictureCopyCount,
    const OH_PictureNative_MetadataCopyItem *metadataCopyItems, uint32_t metadataCopyCount,
    Image_AuxiliaryPictureType *sourceAuxPictureAsMainPixelMap,
    OH_PictureNative **picture);

/**
 * @brief 释放OH_PictureNative指针。
 * 
 * @param picture 被操作的OH_PictureNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_PictureNative_Release(OH_PictureNative *picture);

/**
 * @brief 创建OH_AuxiliaryPictureNative指针。该接口仅支持传入{@link PIXEL_FORMAT}为BGRA_8888的连续像素数据，会创建出RGBA_8888的辅助图。
 * 
 * @param data 图像数据。
 * @param dataLength 图像数据长度。
 * @param size 辅助图尺寸。
 * @param type 辅助图类型。
 * @param auxiliaryPicture 被创建的OH_AuxiliaryPictureNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_Create(uint8_t *data, size_t dataLength, Image_Size *size,
    Image_AuxiliaryPictureType type, OH_AuxiliaryPictureNative **auxiliaryPicture);

/**
 * @brief 创建一个具有指定内存类型的OH_AuxiliaryPictureNative对象。<ul><li>系统默认根据图像类型、图像大小、平台能力等因素选择内存类型。</li><li>处理该接口返回的辅助图时，
 * 需要考虑stride的影响。</li><li>如果data为null或dataLength小于等于0，则不会初始化辅助图数据。</li></ul>
 *
 * @systemapi
 * @param data 指向图像数据的指针。
 * @param dataLength 图像数据的长度。
 * @param info 指向辅助图基本信息的指针。
 * @param allocator 辅助图使用的内存类型。有关可用选项的详细信息，请参阅{@link IMAGE_ALLOCATOR_MODE}。
 * @param auxiliaryPicture 输出参数，用于接收新创建的OH_AuxiliaryPictureNative对象地址。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>202：非系统应用程序调用该接口则返回此错误码。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：info或auxiliaryPicture为空指针、allocator无效、辅助图大小无效或类型不支持、dataLength小于所需大小。</li>
 *     <br><li>IMAGE_SOURCE_UNSUPPORTED_ALLOCATOR_TYPE：不支持的内存类型。
 *     <br>例如使用共享内存创建增益图，仅DMA支持HDR元数据。</li>
 *     <br><li>IMAGE_ALLOC_FAILED：内存分配失败。</li>
 *     <br></ul>
 * @release picture_native/OH_AuxiliaryPictureNative_Release {auxiliaryPicture}
 * @since 26.0.0
 */
Image_ErrorCode OH_AuxiliaryPictureNative_CreateUsingAllocator(uint8_t *data, uint32_t dataLength,
    OH_AuxiliaryPictureInfo *info, IMAGE_ALLOCATOR_MODE allocator, OH_AuxiliaryPictureNative **auxiliaryPicture);

/**
 * @brief 读取缓冲区的图像像素数据，并将结果写入辅助图中。
 * <br>使用约束：auxiliaryPicture和source均不能为空指针，bufferSize需与待写入像素数据大小匹配。
 * 
 * @param auxiliaryPicture 被操作的OH_AuxiliaryPictureNative指针。
 * @param source 将被写入的图像像素数据。
 * @param bufferSize 图像像素数据长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_ALLOC_FAILED：内存分配失败。
 *     <br>IMAGE_COPY_FAILED：内存拷贝失败。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_WritePixels(OH_AuxiliaryPictureNative *auxiliaryPicture, uint8_t *source,
    size_t bufferSize);

/**
 * @brief 读取辅助图的像素数据，结果写入缓冲区。
 * <br>使用约束：auxiliaryPicture、destination和bufferSize均不能为空指针，bufferSize需表示destination可写入的缓冲区大小；接口执行成功后，
 * bufferSize会更新为实际读取的数据大小。
 * 
 * @param auxiliaryPicture 被操作的OH_AuxiliaryPictureNative指针。
 * @param destination 缓冲区，获取的辅助图像素数据写入到该内存区域内。
 * @param bufferSize 缓冲区大小。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_ALLOC_FAILED：内存分配失败。
 *     <br>IMAGE_COPY_FAILED：内存拷贝失败。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_ReadPixels(OH_AuxiliaryPictureNative *auxiliaryPicture, uint8_t *destination,
    size_t *bufferSize);

/**
 * @brief 获取辅助图类型。
 * 
 * @param auxiliaryPicture 被操作的OH_AuxiliaryPictureNative指针。
 * @param type 辅助图类型。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_GetType(OH_AuxiliaryPictureNative *auxiliaryPicture,
    Image_AuxiliaryPictureType *type);

/**
 * @brief 获取辅助图信息。
 * <br>资源管理：接口成功返回的OH_AuxiliaryPictureInfo对象由调用方管理，使用完成后应调用OH_AuxiliaryPictureInfo_Release()释放。
 * 
 * @param auxiliaryPicture 被操作的OH_AuxiliaryPictureNative指针。
 * @param info 辅助图信息。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_GetInfo(OH_AuxiliaryPictureNative *auxiliaryPicture,
    OH_AuxiliaryPictureInfo **info);

/**
 * @brief 设置辅助图信息。
 * <br>资源管理：接口会读取并保存OH_AuxiliaryPictureInfo中的信息值，接口返回后调用方仍需自行管理该OH_AuxiliaryPictureInfo对象的生命周期。
 * 
 * @param auxiliaryPicture 将操作的OH_AuxiliaryPictureNative指针。
 * @param info 将要设置的辅助图信息。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_SetInfo(OH_AuxiliaryPictureNative *auxiliaryPicture,
    OH_AuxiliaryPictureInfo *info);

/**
 * @brief 获取辅助图的元数据。
 * 
 * @param auxiliaryPicture 将操作的OH_AuxiliaryPictureNative指针。
 * @param metadataType 元数据类型。
 * @param metadata 获取的元数据。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_METADATA：不支持的元数据类型，或者元数据类型与辅助图片类型不匹配。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_GetMetadata(OH_AuxiliaryPictureNative *auxiliaryPicture,
    Image_MetadataType metadataType, OH_PictureMetadata **metadata);

/**
 * @brief 设置辅助图的元数据。
 * 
 * @param auxiliaryPicture 将操作的OH_AuxiliaryPictureNative指针。
 * @param metadataType 元数据类型。
 * @param metadata 将要设置的元数据。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_METADATA：不支持的元数据类型，或者元数据类型与辅助图片类型不匹配。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_SetMetadata(OH_AuxiliaryPictureNative *auxiliaryPicture,
    Image_MetadataType metadataType, OH_PictureMetadata *metadata);

/**
 * @brief 获取辅助图的OH_PixelmapNative对象。
 *
 * @param auxiliaryPicture 指向OH_AuxiliaryPictureNative对象的指针。
 * @param pixelmap 输出参数，用于接收获取到的OH_PixelmapNative对象地址。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>IMAGE_INVALID_PARAMETER：auxiliaryPicture或pixelmap为空指针。</li>
 *     <br><li>IMAGE_GET_IMAGE_DATA_FAILED：无法获取辅助图或像素数据。</li>
 *     <br><li>IMAGE_ALLOC_FAILED：内存分配失败。</li>
 *     <br></ul>
 * @release pixelmap_native/OH_PixelmapNative_Destroy {pixelmap}
 * @since 26.0.0
 */
Image_ErrorCode OH_AuxiliaryPictureNative_AcquirePixelmap(OH_AuxiliaryPictureNative *auxiliaryPicture,
    OH_PixelmapNative **pixelmap);

/**
 * @brief 释放OH_AuxiliaryPictureNative指针。
 * 
 * @param picture 将操作的OH_AuxiliaryPictureNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_Release(OH_AuxiliaryPictureNative *picture);

/**
 * @brief 创建一个OH_AuxiliaryPictureInfo对象。
 * 
 * @param info 将操作的OH_AuxiliaryPictureInfo指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_Create(OH_AuxiliaryPictureInfo **info);

/**
 * @brief 获取OH_AuxiliaryPictureInfo中的辅助图类型。
 * 
 * @param info 将操作的OH_AuxiliaryPictureInfo指针。
 * @param type 获取的辅助图类型。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_GetType(OH_AuxiliaryPictureInfo *info, Image_AuxiliaryPictureType *type);

/**
 * @brief 设置OH_AuxiliaryPictureInfo中的辅助图类型。
 * 
 * @param info 将操作的OH_AuxiliaryPictureInfo指针。
 * @param type 将要设置的辅助图类型。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_SetType(OH_AuxiliaryPictureInfo *info, Image_AuxiliaryPictureType type);

/**
 * @brief 获取OH_AuxiliaryPictureInfo中的图片尺寸。
 * 
 * @param info 将操作的OH_AuxiliaryPictureInfo指针。
 * @param size 获取的图片尺寸。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_GetSize(OH_AuxiliaryPictureInfo *info, Image_Size *size);

/**
 * @brief Sets the image size in **OH_AuxiliaryPictureInfo**.
 * 
 * @param info Pointer to the OH_AuxiliaryPictureInfo object.
 * @param size Pointer to the size.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} info is nullptr, or size is nullptr.

 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_SetSize(OH_AuxiliaryPictureInfo *info, Image_Size *size);

/**
 * @brief 获取OH_AuxiliaryPictureInfo中的行跨距。
 * 
 * @param info 将操作的OH_AuxiliaryPictureInfo指针。
 * @param rowStride 跨距，内存中每行像素所占的空间。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_GetRowStride(OH_AuxiliaryPictureInfo *info, uint32_t *rowStride);

/**
 * @brief 设置OH_AuxiliaryPictureInfo中的行跨距。
 * 
 * @param info 将操作的OH_AuxiliaryPictureInfo指针。
 * @param rowStride 跨距，内存中每行像素所占的空间。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_SetRowStride(OH_AuxiliaryPictureInfo *info, uint32_t rowStride);

/**
 * @brief 获取OH_AuxiliaryPictureInfo中的像素格式。
 * 
 * @param info 将操作的OH_AuxiliaryPictureInfo指针。
 * @param pixelFormat 获取的像素格式。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_GetPixelFormat(OH_AuxiliaryPictureInfo *info, PIXEL_FORMAT *pixelFormat);

/**
 * @brief 设置OH_AuxiliaryPictureInfo中的像素格式。
 * 
 * @param info 将操作的OH_AuxiliaryPictureInfo指针。
 * @param pixelFormat 将要设置的像素格式。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_SetPixelFormat(OH_AuxiliaryPictureInfo *info, PIXEL_FORMAT pixelFormat);

/**
 * @brief 释放OH_AuxiliaryPictureInfo指针。
 * 
 * @param info 将操作的OH_AuxiliaryPictureInfo指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_Release(OH_AuxiliaryPictureInfo *info);

/**
 * @brief **OH_DecomposeOptions** is the HDR decomposition option struct encapsulated at the native layer. It is
 * used to specify parameters used for HDR decomposition, such as the target pixel format.
 *
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_DecomposeOptions OH_DecomposeOptions;

/**
 * @brief 创建OH_DecomposeOptions实例。创建的实例需通过{@link OH_DecomposeOptions_Release}释放。
 *
 * @param outOwnedOptions 指向被创建的OH_DecomposeOptions指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_INVALID_PARAMETER：参数错误，例如outOwnedOptions为nullptr。
 *     <br>IMAGE_ALLOC_FAILED：内存分配失败。
 *     <br>202：非系统应用程序调用该接口则返回此错误码。
 * @release picture_native/OH_DecomposeOptions_Release {outOwnedOptions}
 *     @systemapi
 * @since 26.0.0
 */
Image_ErrorCode OH_DecomposeOptions_Create(OH_DecomposeOptions **outOwnedOptions);

/**
 * @brief 设置是否生成全尺寸增益图（指增益图和主图尺寸一致）。若不自行设置，默认值为false，即增益图的尺寸是主图的一半。
 *
 * @param options 指向OH_DecomposeOptions对象的指针。
 * @param isFullSizeGainmap 是否生成全尺寸增益图。设置为true时生成全尺寸增益图，设置为false时生成1/2缩小的增益图。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_INVALID_PARAMETER：参数错误，例如options为nullptr。
 *     <br>202：非系统应用程序调用该接口则返回此错误码。
 *     @systemapi
 * @since 26.0.0
 */
Image_ErrorCode OH_DecomposeOptions_SetIsFullSizeGainmap(OH_DecomposeOptions *options,
    bool isFullSizeGainmap);

/**
 * @brief 获取是否生成全尺寸增益图（指增益图和主图尺寸一致）。如果isFullSizeGainmap为true，则增益图和主图尺寸一致；否则，增益图为主图尺寸的一半。
 *
 * @param options 指向OH_DecomposeOptions对象的指针。
 * @param isFullSizeGainmap 指向bool值的指针，用于接收是否生成全尺寸增益图的设置。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_INVALID_PARAMETER：参数错误，例如options或isFullSizeGainmap为nullptr。
 *     <br>202：非系统应用程序调用该接口则返回此错误码。
 *     @systemapi
 * @since 26.0.0
 */
Image_ErrorCode OH_DecomposeOptions_GetIsFullSizeGainmap(OH_DecomposeOptions *options,
    bool *isFullSizeGainmap);

/**
 * @brief 设置HDR分解后的SDR PixelMap和增益图的像素格式。若不设置，默认值为RGBA_8888。
 *
 * @param options 指向OH_DecomposeOptions对象的指针。
 * @param desiredPixelFormat 分解后SDR PixelMap和增益图的像素格式，支持RGBA_8888、NV12和NV21格式。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_INVALID_PARAMETER：参数错误，例如options为nullptr。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：不支持的像素格式。
 *     <br>202：非系统应用程序调用该接口则返回此错误码。
 *     @systemapi
 * @since 26.0.0
 */
Image_ErrorCode OH_DecomposeOptions_SetDesiredPixelFormat(OH_DecomposeOptions *options,
    int32_t desiredPixelFormat);

/**
 * @brief 获取HDR分解后的SDR PixelMap和增益图的像素格式。
 *
 * @param options 指向OH_DecomposeOptions对象的指针。
 * @param desiredPixelFormat 指向int32_t的指针，用于接收像素格式设置。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_INVALID_PARAMETER：参数错误，例如options或desiredPixelFormat为nullptr。
 *     <br>202：非系统应用程序调用该接口则返回此错误码。
 *     @systemapi
 * @since 26.0.0
 */
Image_ErrorCode OH_DecomposeOptions_GetDesiredPixelFormat(OH_DecomposeOptions *options,
    int32_t *desiredPixelFormat);

/**
 * @brief 释放OH_DecomposeOptions指针。
 *
 * @param options 指向OH_DecomposeOptions对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_INVALID_PARAMETER：参数错误，例如options为nullptr。
 *     <br>202：非系统应用程序调用该接口则返回此错误码。
 *     @systemapi
 * @since 26.0.0
 */
Image_ErrorCode OH_DecomposeOptions_Release(OH_DecomposeOptions *options);

/**
 * @brief 将HDR PixelMap分解为包含SDR PixelMap和增益图（gainmap）的Picture对象。创建的Picture实例需通过{@link OH_PictureNative_Release}释放。
 *
 * @param hdrPixelmap 被分解的HDR PixelMap指针，像素格式需为RGBA_F16、RGBA_1010102、YCBCR_P010或YCRCB_P010。
 * @param options HDR分解配置选项，此参数为必填。
 * @param outOwnedPicture 指向被创建的Picture对象指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_INVALID_PARAMETER：参数错误，例如hdrPixelmap、options或outOwnedPicture为nullptr。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：hdrPixelmap的像素格式不是RGBA_F16、RGBA_1010102、YCBCR_P010或YCRCB_P010。
 *     <br>IMAGE_DECOMPOSE_FAILED：HDR分解处理失败。
 *     <br>IMAGE_ALLOC_FAILED：内存分配失败。
 *     <br>202：非系统应用程序调用该接口则返回此错误码。
 * @release picture_native/OH_PictureNative_Release {outOwnedPicture}
 *     @systemapi
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_DecomposeToPicture(OH_PixelmapNative *hdrPixelmap, OH_DecomposeOptions *options,
    OH_PictureNative **outOwnedPicture);

#ifdef __cplusplus
};
#endif
/** @} */
#endif //INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PICTURE_NATIVE_H_

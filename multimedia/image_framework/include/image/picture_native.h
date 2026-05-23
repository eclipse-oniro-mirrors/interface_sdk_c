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
 * @brief The file declares the APIs for obtaining picture data and information.
 * 
 * @library libpicture.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 13
 */
#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PICTURE_NATIVE_H_
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PICTURE_NATIVE_H_
#include "image_common.h"
#include "pixelmap_native.h"
 
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct is used to perform operations related to the picture.
 * 
 * @since 13
 */
struct OH_PictureNative;

/**
 * @brief The struct is used to perform operations related to the picture.
 * 
 * @since 13
 */
typedef struct OH_PictureNative OH_PictureNative;

/**
 * @brief The struct describes the auxiliary picture, which is used to perform operations related to the auxiliary
 * picture.
 * 
 * @since 13
 */
struct OH_AuxiliaryPictureNative;

/**
 * @brief The struct describes the auxiliary picture, which is used to perform operations related to the auxiliary
 * picture.
 * 
 * @since 13
 */
typedef struct OH_AuxiliaryPictureNative OH_AuxiliaryPictureNative;

/**
 * @brief The struct describes the auxiliary picture information, which is used to perform operations related to the
 * auxiliary picture information.
 * 
 * @since 13
 */
struct OH_AuxiliaryPictureInfo;

/**
 * @brief The struct describes the auxiliary picture information, which is used to perform operations related to the
 * auxiliary picture information.
 * 
 * @since 13
 */
typedef struct OH_AuxiliaryPictureInfo OH_AuxiliaryPictureInfo;

/**
 * @brief Type of the auxiliary picture.
 *
 * @since 13
 */
typedef enum {
    /**
     * Gainmap
     */
    AUXILIARY_PICTURE_TYPE_GAINMAP = 1,
    /**
     * Depth map
     */
    AUXILIARY_PICTURE_TYPE_DEPTH_MAP = 2,
    /**
     * Unrefocus map
     */
    AUXILIARY_PICTURE_TYPE_UNREFOCUS_MAP = 3,
    /**
     * Linear map
     */
    AUXILIARY_PICTURE_TYPE_LINEAR_MAP = 4,
    /**
     * Fragment map
     */
    AUXILIARY_PICTURE_TYPE_FRAGMENT_MAP = 5,

    /**
     * Snap map
     *
     * @since 26.0.0
     */
    AUXILIARY_PICTURE_TYPE_SNAP_MAP = 6,

    /**
     * Snap gainmap
     *
     * @since 26.0.0
     */
    AUXILIARY_PICTURE_TYPE_SNAP_GAINMAP = 7,

    /**
     * Pan map
     *
     * @since 26.0.0
     */
    AUXILIARY_PICTURE_TYPE_PAN_MAP = 8,

    /**
     * Pan gainmap
     *
     * @since 26.0.0
     */
    AUXILIARY_PICTURE_TYPE_PAN_GAINMAP = 9
} Image_AuxiliaryPictureType;

/**
 * @brief **OH_ComposeOptions** is the HDR composition option struct encapsulated at the native layer. It is used to
 * specify parameters used for HDR composition, such as the target pixel format.
 * 
 * @since 23
 */
typedef struct OH_ComposeOptions OH_ComposeOptions;

/**
 * @brief Creates an **OH_ComposeOptions** instance.
 * 
 * @param options Pointer to **OH_ComposeOptions**.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} options is nullptr.
 * @since 23
 */
Image_ErrorCode OH_ComposeOptions_Create(OH_ComposeOptions **options);

/**
 * @brief Sets the pixel format in **OH_ComposeOptions**.
 * 
 * @param options Pointer to **OH_ComposeOptions**.
 * @param desiredPixelFormat Pixel format. The RGBA_1010102, YCBCR_P010, and YCRCB_P010 formats are supported.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} options is nullptr, or desiredPixelFormat is not supported.
 * @since 23
 */
Image_ErrorCode OH_ComposeOptions_SetDesiredPixelFormat(OH_ComposeOptions *options, PIXEL_FORMAT desiredPixelFormat);

/**
 * @brief Obtains the pixel format in **OH_ComposeOptions**.
 * 
 * @param options Pointer to **OH_ComposeOptions**.
 * @param desiredPixelFormat Pixel format in the composition options.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} options is nullptr,or desiredPixelFormat is nullptr.
 * @since 23
 */
Image_ErrorCode OH_ComposeOptions_GetDesiredPixelFormat(OH_ComposeOptions *options, PIXEL_FORMAT *desiredPixelFormat);

/**
 * @brief Releases the pointer to **OH_ComposeOptions**.
 * 
 * @param options Pointer to **OH_ComposeOptions**.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} options is nullptr.
 * @since 23
 */
Image_ErrorCode OH_ComposeOptions_Release(OH_ComposeOptions *options);

/**
 * @brief Creates the pointer to an OH_PictureNative object.
 * 
 * @param mainPixelmap Pointer to the OH_PixelmapNative object of the main picture.
 * @param picture Double pointer to the OH_PictureNative object created.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} mainPixelmap is nullptr, or picture is nullptr.
 * @since 13
 */
Image_ErrorCode OH_PictureNative_CreatePicture(OH_PixelmapNative *mainPixelmap, OH_PictureNative **picture);

/**
 * @brief Obtains the pointer to the OH_PixelmapNative object of a main picture.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param mainPixelmap Double pointer to the OH_PixelmapNative object obtained.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} picture is nullptr, or mainPixelmap is nullptr.
 * @since 13
 */
Image_ErrorCode OH_PictureNative_GetMainPixelmap(OH_PictureNative *picture, OH_PixelmapNative **mainPixelmap);

/**
 * @brief Obtains the pointer to the OH_PixelmapNative object of an HDR picture.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param hdrPixelmap Double pointer to the OH_PixelmapNative object of the HDR picture.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} picture is nullptr, or hdrPixelmap is nullptr.
 *     <br>{@link IMAGE_UNSUPPORTED_OPERATION} Unsupported operation, e.g. the picture does not has a gainmap.
 * @since 13
 */
Image_ErrorCode OH_PictureNative_GetHdrComposedPixelmap(OH_PictureNative *picture, OH_PixelmapNative **hdrPixelmap);

/**
 * @brief Obtains the pointer to **OH_PixelmapNative** of an HDR picture based on **OH_ComposeOptions**.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param options Pointer to **OH_ComposeOptions**.
 * @param hdrPixelmap Pointer to **OH_PixelmapNative** of the obtained HDR picture.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} picture is nullptr, or hdrPixelmap is nullptr.
 *     <br>{@link IMAGE_UNSUPPORTED_OPERATION} Unsupported operation, e.g. the picture does not has a gainmap.
 * @since 23
 */
Image_ErrorCode OH_PictureNative_GetHdrComposedPixelmapWithOptions(OH_PictureNative *picture, OH_ComposeOptions *options, OH_PixelmapNative **hdrPixelmap);

/**
 * @brief Obtains the pointer to the OH_PixelmapNative object of a gain map.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param gainmapPixelmap Double pointer to the OH_PixelmapNative object of the gain map.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} picture is nullptr, or gainmapPixelmap is nullptr.
 * @since 13
 */
Image_ErrorCode OH_PictureNative_GetGainmapPixelmap(OH_PictureNative *picture, OH_PixelmapNative **gainmapPixelmap);

/**
 * @brief Sets an auxiliary picture.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param type Type of the auxiliary picture.
 * @param auxiliaryPicture Pointer to an OH_AuxiliaryPictureNative object.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} picture is nullptr, or auxiliaryPicture is nullptr, or the type is invalid.
 * @since 13
 */
Image_ErrorCode OH_PictureNative_SetAuxiliaryPicture(OH_PictureNative *picture, Image_AuxiliaryPictureType type,
    OH_AuxiliaryPictureNative *auxiliaryPicture);

/**
 * @brief Obtains an auxiliary picture by type.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param type Type of the auxiliary picture.
 * @param auxiliaryPicture Double pointer to the OH_AuxiliaryPictureNative object obtained.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} picture is nullptr, or auxiliaryPicture is nullptr, or the type is invalid.
 * @since 13
 */
Image_ErrorCode OH_PictureNative_GetAuxiliaryPicture(OH_PictureNative *picture, Image_AuxiliaryPictureType type,
    OH_AuxiliaryPictureNative **auxiliaryPicture);

/**
 * @brief Obtains the number of auxiliary pictures in a Picture object.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param count Pointer to the number of auxiliary pictures.
 * @return <ul>
 *         <li>{@link IMAGE_SUCCESS} if the execution is successful.</li>
 *         <li>{@link IMAGE_INVALID_PARAMETER} picture or count is nullptr, or fail to get the picture.</li>
 *         </ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_GetAuxiliaryPictureCount(OH_PictureNative *picture, uint32_t *count);

/**
 * @brief Obtains the types of auxiliary pictures in a Picture object.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param auxiliaryPictureTypes Pointer to the array that receives the auxiliary picture types.
 * @param count On input, the size of the auxiliaryPictureTypes array.
 *              On output, the actual number of auxiliary pictures.
 * @return <ul>
 *         <li>{@link IMAGE_SUCCESS} if the execution is successful.</li>
 *         <li>{@link IMAGE_INVALID_PARAMETER} picture, auxiliaryPictureTypes, or count is nullptr,
 *         or fail to get the picture, or count is smaller than required.</li>
 *         </ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_GetAuxiliaryPictureTypes(OH_PictureNative *picture,
    Image_AuxiliaryPictureType *auxiliaryPictureTypes, uint32_t *count);

/**
 * @brief Obtains the number of metadata entries in a Picture object.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param count Pointer to the number of metadata entries.
 * @return <ul>
 *         <li>{@link IMAGE_SUCCESS} if the execution is successful.</li>
 *         <li>{@link IMAGE_INVALID_PARAMETER} picture or count is nullptr, or fail to get the picture.</li>
 *         </ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_GetMetadataCount(OH_PictureNative *picture, uint32_t *count);

/**
 * @brief Obtains the types of metadata in a Picture object.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param metadataTypes Pointer to the array that receives the metadata types.
 * @param count On input, the size of the metadataTypes array.
 *              On output, the actual number of metadata entries.
 * @return <ul>
 *         <li>{@link IMAGE_SUCCESS} if the execution is successful.</li>
 *         <li>{@link IMAGE_INVALID_PARAMETER} picture, metadataTypes, or count is nullptr, or fail to get the picture,
 *         or count is smaller than required.</li>
 *         </ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_GetMetadataTypes(OH_PictureNative *picture,
    Image_MetadataType *metadataTypes, uint32_t *count);

/**
 * @brief Deep copies a Picture object, selectively copying auxiliary pictures and metadata from the source picture
 * to specified positions of the destination picture.
 * 
 * @param source Pointer to the source OH_PictureNative object.
 * @param srcAuxiliaryPictures Array of auxiliary picture types in the source to be copied.
 * @param srcAuxiliaryPictureCount Number of elements in srcAuxiliaryPictures.
 * @param srcMetadatas Array of metadata types in the source to be copied.
 * @param srcMetadataCount Number of elements in srcMetadatas.
 * @param dstAuxiliaryPictures Array of destination auxiliary picture types corresponding to source auxiliary pictures.
 * @param dstAuxiliaryPictureCount Number of elements in dstAuxiliaryPictures.
 * @param dstMetadatas Array of destination metadata types corresponding to source metadata.
 * @param dstMetadataCount Number of elements in dstMetadatas.
 * @param mainPixelMapKeyFromSrc Pointer to the auxiliary picture type in the source to be used as the main image in the
 *     new picture. Pass nullptr to retain the main image from the source.
 * @param picture Double pointer to the newly created deep-copied OH_PictureNative object.
 * @return <ul>
 *         <li>{@link IMAGE_SUCCESS} if the execution is successful.</li>
 *         <li>{@link IMAGE_INVALID_PARAMETER} source is nullptr, or picture is nullptr, or fail to get the picture,
 *         or counts mismatch, or count is not zero but the corresponding array is nullptr.</li>
 *         <li>{@link IMAGE_ALLOC_FAILED} memory allocation failed.</li>
 *         </ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_DeepCopy(OH_PictureNative *source,
    const Image_AuxiliaryPictureType* srcAuxiliaryPictures, uint32_t srcAuxiliaryPictureCount,
    const Image_MetadataType* srcMetadatas, uint32_t srcMetadataCount,
    const Image_AuxiliaryPictureType* dstAuxiliaryPictures, uint32_t dstAuxiliaryPictureCount,
    const Image_MetadataType* dstMetadatas, uint32_t dstMetadataCount,
    Image_AuxiliaryPictureType *mainPixelMapKeyFromSrc,
    OH_PictureNative **picture);

/**
 * @brief Removes an auxiliary picture from a Picture object.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param type Type of the auxiliary picture to remove.
 * @return <ul>
 *         <li>{@link IMAGE_SUCCESS} if the auxiliary picture was successfully removed or did not exist.</li>
 *         <li>{@link IMAGE_INVALID_PARAMETER} picture is nullptr, or fail to get the picture,
 *         or the type is invalid.</li>
 *         </ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_RemoveAuxiliaryPicture(OH_PictureNative *picture, Image_AuxiliaryPictureType type);

/**
 * @brief Removes metadata from a Picture object.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param type Type of the metadata to remove.
 * @return <ul>
 *         <li>{@link IMAGE_SUCCESS} if the metadata was successfully removed or did not exist.</li>
 *         <li>{@link IMAGE_INVALID_PARAMETER} picture is nullptr, or fail to get the picture.</li>
 *         <li>{@link IMAGE_UNSUPPORTED_METADATA} unsupported metadata type.</li>
 *         </ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PictureNative_RemoveMetadata(OH_PictureNative *picture, Image_MetadataType type);

/**
 * @brief Obtains the metadata of a main picture.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param metadataType Metadata type.
 * @param metadata Double pointer to the metadata.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} picture is nullptr, or metadata is nullptr.
 *     <br>{@link IMAGE_UNSUPPORTED_METADATA} unsupported metadata type.
 * @since 13
 */
Image_ErrorCode OH_PictureNative_GetMetadata(OH_PictureNative *picture, Image_MetadataType metadataType,
    OH_PictureMetadata **metadata);

/**
 * @brief Sets the metadata for a main picture.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @param metadataType Metadata type.
 * @param metadata Pointer to the metadata.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} picture is nullptr, or metadata is nullptr.
 *     <br>{@link IMAGE_UNSUPPORTED_METADATA} unsupported metadata type.
 * @since 13
 */
Image_ErrorCode OH_PictureNative_SetMetadata(OH_PictureNative *picture, Image_MetadataType metadataType,
    OH_PictureMetadata *metadata);

/**
 * @brief Releases the pointer to an OH_PictureNative object.
 * 
 * @param picture Pointer to an OH_PictureNative object.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} picture is nullptr.
 * @since 13
 */
Image_ErrorCode OH_PictureNative_Release(OH_PictureNative *picture);

/**
 * @brief Creates the pointer to an OH_AuxiliaryPictureNative object. This API supports only continuous pixel data
 * whose {@link pixel format} is BGRA_8888 and creates an auxiliary picture in RGBA_8888 format.
 * 
 * @param data Pointer to the image data.
 * @param dataLength Length of the image data.
 * @param size Pointer to the size of the auxiliary picture.
 * @param type Type of the auxiliary picture.
 * @param auxiliaryPicture Double pointer to the OH_AuxiliaryPictureNative object created.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} data is nullptr, or dataLength is invalid, or size is nullptr, or the type
 *         is invalid, or auxiliaryPicture is nullptr.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_Create(uint8_t *data, size_t dataLength, Image_Size *size,
    Image_AuxiliaryPictureType type, OH_AuxiliaryPictureNative **auxiliaryPicture);

/**
 * @brief Creates an OH_AuxiliaryPictureNative object with a specified memory type. By default, the system selects
 * the memory type based on the image type, image size, platform capability, and other factors. When processing the
 * auxiliary picture returned by this API, always consider the impact of stride. If **data** is null or **dataLength**
 * is less than or equal to 0, the auxiliary picture will not be initialized.
 * 
 * @param data Pointer to the image data.
 * @param dataLength Length of the image data.
 * @param info Pointer to the basic information of the auxiliary picture.
 * @param allocator Memory type used by the auxiliary picture. For details about the available options, see
 *     {@link IMAGE_ALLOCATOR_MODE}.
 * @param auxiliaryPicture Double pointer to the OH_AuxiliaryPictureNative object created.
 * @return <ul>
 *         <li>{@link IMAGE_SUCCESS} if the execution is successful.</li>
 *         <li>{@link IMAGE_INVALID_PARAMETER} info or auxiliaryPicture is nullptr, or allocator is invalid,
 *         or the size is invalid, or the type is unsupported, or dataLength is smaller than required.</li>
 *         <li>{@link IMAGE_SOURCE_UNSUPPORTED_ALLOCATOR_TYPE} unsupported allocator type,
 *         e.g., use share memory create a gainmap as only DMA supported hdr metadata.</li>
 *         <li>{@link IMAGE_ALLOC_FAILED} memory allocation failed.</li>
 *         </ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_AuxiliaryPictureNative_CreateUsingAllocator(uint8_t *data, size_t dataLength,
    OH_AuxiliaryPictureInfo *info, IMAGE_ALLOCATOR_MODE allocator, OH_AuxiliaryPictureNative **auxiliaryPicture);

/**
 * @brief Reads pixels in the buffer and writes the result to an auxiliary picture.
 * 
 * @param auxiliaryPicture Pointer to an OH_AuxiliaryPictureNative object.
 * @param source Pixels to be written.
 * @param bufferSize Buffer size.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} auxiliaryPicture is nullptr, or source is nullptr, or the bufferSize is invalid.
 *     <br>{@link IMAGE_ALLOC_FAILED} memory alloc failed.
 *     <br>{@link IMAGE_COPY_FAILED} memory copy failed.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_WritePixels(OH_AuxiliaryPictureNative *auxiliaryPicture, uint8_t *source,
    size_t bufferSize);

/**
 * @brief Reads pixels of an auxiliary picture and writes the result to the buffer.
 * 
 * @param auxiliaryPicture Pointer to an OH_AuxiliaryPictureNative object.
 * @param destination Pointer to the buffer to which the pixels of the auxiliary data will be written.
 * @param bufferSize Pointer to the buffer size.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} auxiliaryPicture is nullptr, or destination is nullptr,
 *         or the bufferSize is invalid.
 *     <br>{@link IMAGE_ALLOC_FAILED} memory alloc failed.
 *     <br>{@link IMAGE_COPY_FAILED} memory copy failed.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_ReadPixels(OH_AuxiliaryPictureNative *auxiliaryPicture, uint8_t *destination,
    size_t *bufferSize);

/**
 * @brief Obtains the type of an auxiliary picture.
 * 
 * @param auxiliaryPicture Pointer to an OH_AuxiliaryPictureNative object.
 * @param type Pointer to the auxiliary picture type.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} auxiliaryPicture is nullptr, or type is nullptr.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_GetType(OH_AuxiliaryPictureNative *auxiliaryPicture,
    Image_AuxiliaryPictureType *type);

/**
 * @brief Obtains the information of an auxiliary picture.
 * 
 * @param auxiliaryPicture Pointer to an OH_AuxiliaryPictureNative object.
 * @param info Double pointer to the auxiliary picture information.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} auxiliaryPicture is nullptr, or info is nullptr.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_GetInfo(OH_AuxiliaryPictureNative *auxiliaryPicture,
    OH_AuxiliaryPictureInfo **info);

/**
 * @brief Sets the information for an auxiliary picture.
 * 
 * @param auxiliaryPicture Pointer to an OH_AuxiliaryPictureNative object.
 * @param info Pointer to the auxiliary picture information.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} auxiliaryPicture is nullptr, or info is nullptr.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_SetInfo(OH_AuxiliaryPictureNative *auxiliaryPicture,
    OH_AuxiliaryPictureInfo *info);

/**
 * @brief Obtains the metadata of an auxiliary picture.
 * 
 * @param auxiliaryPicture Pointer to an OH_AuxiliaryPictureNative object.
 * @param metadataType Metadata type.
 * @param metadata Double pointer to the metadata.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} auxiliaryPicture is nullptr, or metadata is nullptr.
 *     <br>{@link IMAGE_UNSUPPORTED_METADATA} unsupported metadata type, or the metadata type does not match the
 *         auxiliary picture type.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_GetMetadata(OH_AuxiliaryPictureNative *auxiliaryPicture,
    Image_MetadataType metadataType, OH_PictureMetadata **metadata);

/**
 * @brief Sets the metadata for an auxiliary picture.
 * 
 * @param auxiliaryPicture Pointer to an OH_AuxiliaryPictureNative object.
 * @param metadataType Metadata type.
 * @param metadata Pointer to the metadata.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} auxiliaryPicture is nullptr, or metadata is nullptr.
 *     <br>{@link IMAGE_UNSUPPORTED_METADATA} unsupported metadata type, or the metadata type does not match the
 *         auxiliary picture type.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_SetMetadata(OH_AuxiliaryPictureNative *auxiliaryPicture,
    Image_MetadataType metadataType, OH_PictureMetadata *metadata);

/**
 * @brief Obtains the OH_PixelmapNative object of an auxiliary picture.
 * 
 * @param auxiliaryPicture Pointer to an OH_AuxiliaryPictureNative object.
 * @param pixelmap Double pointer to the OH_PixelmapNative object obtained.
 * @return <ul>
 *         <li>{@link IMAGE_SUCCESS} if the execution is successful.</li>
 *         <li>{@link IMAGE_INVALID_PARAMETER} auxiliaryPicture is nullptr, or pixelmap is nullptr.</li>
 *         <li>{@link IMAGE_GET_IMAGE_DATA_FAILED} fail to get the auxiliary picture or its pixelmap content.</li>
 *         <li>{@link IMAGE_ALLOC_FAILED} memory allocation failed.</li>
 *         </ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_AuxiliaryPictureNative_GetPixelmap(OH_AuxiliaryPictureNative *auxiliaryPicture,
    OH_PixelmapNative **pixelmap);

/**
 * @brief Releases the pointer to an OH_AuxiliaryPictureNative object.
 * 
 * @param picture Pointer to an OH_AuxiliaryPictureNative object.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} picture is nullptr.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureNative_Release(OH_AuxiliaryPictureNative *picture);

/**
 * @brief Creates an OH_AuxiliaryPictureInfo object.
 * 
 * @param info Double pointer to the OH_AuxiliaryPictureInfo object created.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} info is nullptr.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_Create(OH_AuxiliaryPictureInfo **info);

/**
 * @brief Obtains the auxiliary picture type in **OH_AuxiliaryPictureInfo**.
 * 
 * @param info Pointer to the OH_AuxiliaryPictureInfo object.
 * @param type Pointer to the type of the auxiliary picture.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} info is nullptr, or type is nullptr.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_GetType(OH_AuxiliaryPictureInfo *info, Image_AuxiliaryPictureType *type);

/**
 * @brief Sets the auxiliary picture type in **OH_AuxiliaryPictureInfo**.
 * 
 * @param info Pointer to the OH_AuxiliaryPictureInfo object.
 * @param type Type of the auxiliary picture.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} info is nullptr, or type is invalid.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_SetType(OH_AuxiliaryPictureInfo *info, Image_AuxiliaryPictureType type);

/**
 * @brief Obtains the image size in **OH_AuxiliaryPictureInfo**.
 * 
 * @param info Pointer to the OH_AuxiliaryPictureInfo object.
 * @param size Pointer to the size.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} info is nullptr, or size is nullptr.
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
 * @brief Obtains the row stride in **OH_AuxiliaryPictureInfo**.
 * 
 * @param info Pointer to the OH_AuxiliaryPictureInfo object.
 * @param rowStride Pointer to the row stride, which is the number of bytes from one row of pixels in memory to the
 * next row of pixels in memory.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} info is nullptr, or rowStride is nullptr.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_GetRowStride(OH_AuxiliaryPictureInfo *info, uint32_t *rowStride);

/**
 * @brief Sets the row stride in **OH_AuxiliaryPictureInfo**.
 * 
 * @param info Pointer to the OH_AuxiliaryPictureInfo object.
 * @param rowStride Row stride, which is the number of bytes from one row of pixels in memory to the next row of pixels
 * in memory.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} info is nullptr, or rowStride is nullptr.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_SetRowStride(OH_AuxiliaryPictureInfo *info, uint32_t rowStride);

/**
 * @brief Obtains the pixel format in **OH_AuxiliaryPictureInfo**.
 * 
 * @param info Pointer to the OH_AuxiliaryPictureInfo object.
 * @param pixelFormat Pointer to the pixel format obtained.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} info is nullptr, or pixelFormat is nullptr.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_GetPixelFormat(OH_AuxiliaryPictureInfo *info, PIXEL_FORMAT *pixelFormat);

/**
 * @brief Sets the pixel format in **OH_AuxiliaryPictureInfo**.
 * 
 * @param info Pointer to the OH_AuxiliaryPictureInfo object.
 * @param pixelFormat Pixel format.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} info is nullptr.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_SetPixelFormat(OH_AuxiliaryPictureInfo *info, PIXEL_FORMAT pixelFormat);

/**
 * @brief Releases the pointer to an OH_AuxiliaryPictureInfo object.
 * 
 * @param info Pointer to the OH_AuxiliaryPictureInfo object.
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} info is nullptr.
 * @since 13
 */
Image_ErrorCode OH_AuxiliaryPictureInfo_Release(OH_AuxiliaryPictureInfo *info);

#ifdef __cplusplus
};
#endif
/** @} */
#endif //INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PICTURE_NATIVE_H_

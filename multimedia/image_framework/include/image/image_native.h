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
 * @brief Provides APIs for access to the image interface.
 *
 * @since 12
 */
/**
 * @file image_native.h
 *
 * @brief The file declares the cropping rectangle, size, and component data of an image.
 * 
 * @library libohimage.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 12
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_H
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_H

#include "image_common.h"
#include "native_buffer/native_buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct describes the alias for an image object at the native layer.
 * 
 * @since 12
 */
struct OH_ImageNative;

/**
 * @brief The struct describes the alias for an image object at the native layer.
 * 
 * @since 12
 */
typedef struct OH_ImageNative OH_ImageNative;

/**
 * @brief {@link OH_ImageBufferData} is the image data struct encapsulated at the native layer. To obtain an {@link OH_ImageBufferData}
 * object, call {@link OH_ImageNative_GetBufferData}.
 *
 * The struct stores the shallow copy of the original image data. Once the original data is released, no read
 * or write operations should be performed on the pointers within this struct; otherwise, undefined behavior
 * will occur.
 *
 * @since 23
 */
typedef struct OH_ImageBufferData {
    /** rowStride of each component. */
    int32_t *rowStride;
    /** pixelStride of each component. */
    int32_t *pixelStride;
    /** number of strides.  */
    int32_t  numStride;
    /** byte length of the buffer  */
    size_t  bufferSize;
    /** native buffer of the image. */
    OH_NativeBuffer  *nativeBuffer;
} OH_ImageBufferData;

/**
 * @brief Obtains {@link Image_Size} of an {@link OH_ImageNative} object.
 *
 * @param image Pointer to an {@link OH_ImageNative} object.
 * @param size Pointer to the {@link Image_Size} object obtained.
 * @return {@linkImage_ErrorCode} IMAGE_SUCCESS - The operation is successful.
 *     <br>{@linkImage_ErrorCode} IMAGE_BAD_PARAMETER - A parameter is incorrect.
 *     <br>{@linkImage_ErrorCode} IMAGE_UNKNOWN_ERROR - An unknown error occurs.
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetImageSize(OH_ImageNative *image, Image_Size *size);

/**
 * @brief Obtains the component types of an {@link OH_ImageNative} object.
 * 
 * @param image Pointer to an {@link OH_ImageNative} object.
 * @param types Pointer to the component type list object obtained. Since the number of components is uncertain, this
 *     API needs to be called twice: first, set **types** to **NULL** to obtain the number of components (**typeSize**);
 *     second, allocate corresponding memory for **types** based on **typeSize** and then obtain the component type list.
 * @param typeSize Pointer to the number of component types obtained.
 * @return {@linkImage_ErrorCode} IMAGE_SUCCESS - The operation is successful.
 *     <br>{@linkImage_ErrorCode} IMAGE_BAD_PARAMETER - A parameter is incorrect.
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetComponentTypes(OH_ImageNative *image,
    uint32_t **types, size_t *typeSize);

/**
 * @brief Obtains the buffer corresponding to a component type in an {@link OH_ImageNative} object.
 * 
 * @param image Pointer to an {@link OH_ImageNative} object.
 * @param componentType Component type. The value is obtained using the {@link OH_ImageNative_GetComponentTypes} API.
 * @param nativeBuffer Double pointer to the buffer, which is an {@link OH_NativeBuffer} object.
 * @return {@linkImage_ErrorCode} IMAGE_SUCCESS - The operation is successful.
 *     <br>{@linkImage_ErrorCode} IMAGE_BAD_PARAMETER - A parameter is incorrect.
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetByteBuffer(OH_ImageNative *image,
    uint32_t componentType, OH_NativeBuffer **nativeBuffer);

/**
 * @brief Obtains the size of the buffer corresponding to a component type in an {@link OH_ImageNative} object.
 * 
 * @param image Pointer to an {@link OH_ImageNative} object.
 * @param componentType Component type. The value is obtained using the {@link OH_ImageNative_GetComponentTypes} API.
 * @param size Pointer to the size of the buffer.
 * @return {@linkImage_ErrorCode} IMAGE_SUCCESS - The operation is successful.
 *     <br>{@linkImage_ErrorCode} IMAGE_BAD_PARAMETER - A parameter is incorrect.
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetBufferSize(OH_ImageNative *image,
    uint32_t componentType, size_t *size);

/**
 * @brief Obtains the row stride corresponding to a component type in an {@link OH_ImageNative} object.
 * 
 * @param image Pointer to an {@link OH_ImageNative} object.
 * @param componentType Component type. The value is obtained using the {@link OH_ImageNative_GetComponentTypes} API.
 * @param rowStride Pointer to the row stride obtained.
 * @return {@linkImage_ErrorCode} IMAGE_SUCCESS - The operation is successful.
 *     <br>{@linkImage_ErrorCode} IMAGE_BAD_PARAMETER - A parameter is incorrect.
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetRowStride(OH_ImageNative *image,
    uint32_t componentType, int32_t *rowStride);

/**
 * @brief Obtains the pixel stride corresponding to a component type in an {@link OH_ImageNative} object.
 * 
 * @param image Pointer to an {@link OH_ImageNative} object.
 * @param componentType Component type. The value is obtained using the {@link OH_ImageNative_GetComponentTypes} API.
 * @param pixelStride Pointer to the pixel stride obtained.
 * @return {@linkImage_ErrorCode} IMAGE_SUCCESS - The operation is successful.
 *     <br>{@linkImage_ErrorCode} IMAGE_BAD_PARAMETER - A parameter is incorrect.
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetPixelStride(OH_ImageNative *image,
    uint32_t componentType, int32_t *pixelStride);

/**
 * @brief Obtains the timestamp of an {@link OH_ImageNative} object. Timestamps, measured in nanoseconds, are usually
 * monotonically increasing.
 * 
 * @param image Pointer to an {@link OH_ImageNative} object.
 * @param timestamp Pointer to the timestamp.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS The operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER A parameter is incorrect.
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetTimestamp(OH_ImageNative *image, int64_t *timestamp);

/**
 * @brief Releases an {@link OH_ImageNative} object.
 * 
 * @param image Pointer to an {@link OH_ImageNative} object.
 * @return {@linkImage_ErrorCode} IMAGE_SUCCESS - The operation is successful.
 *     <br>{@linkImage_ErrorCode} IMAGE_BAD_PARAMETER - A parameter is incorrect.
 * @since 12
 */
Image_ErrorCode OH_ImageNative_Release(OH_ImageNative *image);

/**
 * @brief Obtains the color space in an {@link OH_ImageNative} object.
 * 
 * @param image Pointer to an {@link OH_ImageNative} object.
 * @param colorSpaceName Pointer to the image color space. For details about the color space corresponding to **colorSpaceName**,
 *     see {@link ColorSpaceName}.
 * @return {@link IMAGE_SUCCESS} The operation is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} A parameter is incorrect.
 * @since 23
 */
Image_ErrorCode OH_ImageNative_GetColorSpace(OH_ImageNative *image, int32_t *colorSpaceName);

/**
 * @brief Obtains the image format in an {@link OH_ImageNative} object.
 * 
 * @param image Pointer to an {@link OH_ImageNative} object.
 * @param format Pointer to the image format.
 * @return {@link IMAGE_SUCCESS} The operation is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} A parameter is incorrect.
 * @since 23
 */
Image_ErrorCode OH_ImageNative_GetFormat(OH_ImageNative *image, OH_NativeBuffer_Format *format);

/**
 * @brief Obtains the image buffer data object in an {@link OH_ImageNative} object.
 * 
 * @param image Pointer to an {@link OH_ImageNative} object.
 * @param imageBufferData Pointer to the image buffer data object.
 * @return {@link IMAGE_SUCCESS} The operation is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} A parameter is incorrect.
 * @since 23
 */
Image_ErrorCode OH_ImageNative_GetBufferData(OH_ImageNative *image, OH_ImageBufferData *imageBufferData);

#ifdef __cplusplus
};
#endif
/** @} */
#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_H

/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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
 * @brief Provides APIs for obtaining pixel map data and information.
 *
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 10
 * @version 1.0
 */

/**
 * @file image_pixel_map_mdk.h
 *
 * @brief Declares the APIs that can lock, access, and unlock a pixel map.
 * Need link <b>libpixelmap_ndk.z.so</b>
 *
 * @library libpixelmap_ndk.z.so
 * @syscap SystemCapability.Multimedia.Image.Core
 * @kit ImageKit
 * @since 10
 * @version 1.0
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PIXEL_MAP_MDK_H_
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PIXEL_MAP_MDK_H_
#include <stdint.h>
#include "napi/native_api.h"
#include "image_mdk_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the native pixel map information.
 * @since 10
 * @version 1.0
 */
struct NativePixelMap_;

/**
 * @brief Defines the data type name of the native pixel map.
 * @since 10
 * @version 1.0
 */
typedef struct NativePixelMap_ NativePixelMap;

/**
 * @brief Defines the pixel map information.
 *
 * @since 10
 * @version 1.0
 */
typedef struct OhosPixelMapInfos {
    /** Image width, in pixels. */
    uint32_t width;
    /** Image height, in pixels. */
    uint32_t height;
    /** Number of bytes per row. */
    uint32_t rowSize;
    /** Pixel format. */
    int32_t pixelFormat;
} OhosPixelMapInfos;

/**
 * @brief Enumerates the pixel map alpha types.
 *
 * @since 10
 * @version 1.0
 */
enum {
    /**
     * Unknown format.
     */
    OHOS_PIXEL_MAP_ALPHA_TYPE_UNKNOWN = 0,
    /**
     * Opaque format.
     */
    OHOS_PIXEL_MAP_ALPHA_TYPE_OPAQUE = 1,
    /**
     * Premultiplied format.
     */
    OHOS_PIXEL_MAP_ALPHA_TYPE_PREMUL = 2,
    /**
     * Unpremultiplied format.
     */
    OHOS_PIXEL_MAP_ALPHA_TYPE_UNPREMUL = 3
};

/**
 * @brief Enumerates the pixel map editing types.
 *
 * @since 10
 * @version 1.0
 */
enum {
    /**
     * Read-only.
     */
    OHOS_PIXEL_MAP_READ_ONLY = 0,
    /**
     * Editable.
     */
    OHOS_PIXEL_MAP_EDITABLE = 1,
};

/**
 * @brief Enumerates the anti-aliasing level.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Nearest-neighbor interpolation.
     */
    OH_PixelMap_AntiAliasing_NONE = 0,
    /**
     * Bilinear interpolation, without mipmap linear filtering.
     */
    OH_PixelMap_AntiAliasing_LOW = 1,
    /**
     * Bilinear interpolation, with mipmap linear filtering.
     */
    OH_PixelMap_AntiAliasing_MEDIUM = 2,
    /**
     * Cubic interpolation.
     */
    OH_PixelMap_AntiAliasing_HIGH = 3,
} OH_PixelMap_AntiAliasingLevel;

/**
 * @brief Defines the options used for creating a pixel map.
 *
 * @since 10
 * @version 1.0
 */
struct OhosPixelMapCreateOps {
    /** Image width, in pixels. */
    uint32_t width;
    /** Image height, in pixels. */
    uint32_t height;
    /** Image format. */
    int32_t pixelFormat;
    /** Editing type of the image. */
    uint32_t editable;
    /** Alpha type of the image. */
    uint32_t alphaType;
    /** Scale mode of the image. */
    uint32_t scaleMode;
};

/**
 * @brief Creates a PixelMap object. Currently, only BGRA input streams are supported.
 *
 * @param env Pointer to the NAPI environment.
 * @param info Options for setting the PixelMap object.
 * @param buf Pointer to the buffer of the image.
 * @param len Image size.
 * @param res Pointer to the PixelMap object at the application layer.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_GET_DATA_ABNORMAL}: An error occurs during image data retrieval.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_FAILED}: Decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_HEAD_ABNORMAL}: An error occurs during decoding of the image header.</li>
 *     <li>{@link IMAGE_RESULT_CREATE_DECODER_FAILED}: The decoder fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_CREATE_ENCODER_FAILED}: The encoder fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_CHECK_FORMAT_ERROR}: The format check fails.</li>
 *     <li>{@link IMAGE_RESULT_THIRDPART_SKIA_ERROR}: Skia decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST}: Sharing the memory fails.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL}: Data in the shared memory is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_ABNORMAL}: Image decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_FAILED}: Decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_MALLOC_ABNORMAL}: An error occurs during memory allocation.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li>
 *     <li>{@link IMAGE_RESULT_INIT_ABNORMAL}: The image fails to be initialized.</li>
 *     <li>{@link IMAGE_RESULT_CROP}: Cropping fails.</li>
 *     <li>{@link IMAGE_RESULT_UNKNOWN_FORMAT}: The image format is unknown.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_REGISTER_FAILED}: The plugin fails to be registered.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_CREATE_FAILED}: The plugin fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_ENCODE_FAILED}: The image fails to be encoded.</li>
 *     <li>{@link IMAGE_RESULT_HW_DECODE_UNSUPPORT}: Hardware decoding is not supported.</li>
 *     <li>{@link IMAGE_RESULT_HW_DECODE_FAILED}: Hardware decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_INDEX_INVALID}: Index fails.</li>
 *     <li>{@link IMAGE_RESULT_ALPHA_TYPE_ERROR}: The alpha type is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ALLOCATER_TYPE_ERROR}: The memory allocator type is incorrect.</li></ul>
 * @see CreatePixelMap
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_CreatePixelMap(napi_env env, OhosPixelMapCreateOps info,
    void* buf, size_t len, napi_value* res);

/**
 * @brief Creates a PixelMap object.
 *
 * @param env Pointer to the NAPI environment.
 * @param info Options for setting the PixelMap object.
 * @param buf Pointer to the buffer of the image.
 * @param len Buffer size.
 * @param rowStride Row stride. The stride is the actual memory size occupied by each row of the image, in bytes.
 * Stride = Width \*Number of bytes per pixel + Padding, where padding refers to the extra space added at the end of
 * each row for memory alignment purposes.
 * @param res Pointer to the PixelMap object at the application layer.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_GET_DATA_ABNORMAL}: An error occurs during image data retrieval.</li>
 *     <li>{@link IMAGE_RESULT_CHECK_FORMAT_ERROR}: The format check fails.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL}: Data in the shared memory is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li>
 *     <li>{@link IMAGE_RESULT_UNKNOWN_FORMAT}: The image format is unknown.</li></ul>
 * @see OH_PixelMap_CreatePixelMapWithStride
 * @since 12
 * @version 1.0
 */
int32_t OH_PixelMap_CreatePixelMapWithStride(napi_env env, OhosPixelMapCreateOps info,
    void* buf, size_t len, int32_t rowStride, napi_value* res);

/**
 * @brief Creates a PixelMap object that contains only alpha channel information.
 *
 * @param env Pointer to the NAPI environment.
 * @param source PixelMap object at the application layer.
 * @param alpha Pointer to the alpha channel.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_GET_DATA_ABNORMAL}: An error occurs during image data retrieval.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_FAILED}: Decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_HEAD_ABNORMAL}: An error occurs during decoding of the image header.</li>
 *     <li>{@link IMAGE_RESULT_CREATE_DECODER_FAILED}: The decoder fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_CREATE_ENCODER_FAILED}: The encoder fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_CHECK_FORMAT_ERROR}: The format check fails.</li>
 *     <li>{@link IMAGE_RESULT_THIRDPART_SKIA_ERROR}: Skia decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST}: Sharing the memory fails.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL}: Data in the shared memory is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_ABNORMAL}: Image decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_MALLOC_ABNORMAL}: An error occurs during memory allocation.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li>
 *     <li>{@link IMAGE_RESULT_INIT_ABNORMAL}: The image fails to be initialized.</li>
 *     <li>{@link IMAGE_RESULT_CROP}: Cropping fails.</li>
 *     <li>{@link IMAGE_RESULT_UNKNOWN_FORMAT}: The image format is unknown.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_REGISTER_FAILED}: The plugin fails to be registered.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_CREATE_FAILED}: The plugin fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_ENCODE_FAILED}: The image fails to be encoded.</li>
 *     <li>{@link IMAGE_RESULT_HW_DECODE_UNSUPPORT}: Hardware decoding is not supported.</li>
 *     <li>{@link IMAGE_RESULT_HW_DECODE_FAILED}: Hardware decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_INDEX_INVALID}: Index fails.</li>
 *     <li>{@link IMAGE_RESULT_ALPHA_TYPE_ERROR}: The alpha type is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ALLOCATER_TYPE_ERROR}: The memory allocator type is incorrect.</li></ul>
 * @see CreateAlphaPixelMap
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_CreateAlphaPixelMap(napi_env env, napi_value source, napi_value* alpha);

/**
 * @brief Initializes a NativePixelMap object.
 *
 * @param env Pointer to the NAPI environment.
 * @param source PixelMap object at the application layer.
 * @return Pointer to the NativePixelMap object.
 * @see InitNativePixelMap
 * @since 10
 * @version 1.0
 */
NativePixelMap* OH_PixelMap_InitNativePixelMap(napi_env env, napi_value source);

/**
 * @brief Obtains the number of bytes per row of a NativePixelMap object.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param num Pointer to the number of bytes per row.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li></ul>
 * @see GetBytesNumberPerRow
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_GetBytesNumberPerRow(const NativePixelMap* native, int32_t* num);

/**
 * @brief Checks whether a NativePixelMap object is editable.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param editable Pointer to the editing type of the NativePixelMap object.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li></ul>
 * @see GetIsEditable
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_GetIsEditable(const NativePixelMap* native, int32_t* editable);

/**
 * @brief Checks whether a NativePixelMap object supports alpha channels.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param alpha Pointer to the support for alpha channels.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li></ul>
 * @see IsSupportAlpha
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_IsSupportAlpha(const NativePixelMap* native, int32_t* alpha);

/**
 * @brief Sets an alpha channel for a NativePixelMap object.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param alpha Alpha channel to set.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li></ul>
 * @see SetAlphaAble
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_SetAlphaAble(const NativePixelMap* native, int32_t alpha);

/**
 * @brief Obtains the pixel density of a NativePixelMap object.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param density Pointer to the pixel density.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li></ul>
 * @see GetDensity
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_GetDensity(const NativePixelMap* native, int32_t* density);

/**
 * @brief Sets the pixel density for a NativePixelMap object.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param density Pixel density to set.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li></ul>
 * @see GetDensity
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_SetDensity(const NativePixelMap* native, int32_t density);

/**
 * @brief Sets the opacity for a NativePixelMap object.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param opacity Opacity to set.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li></ul>
 * @see SetOpacity
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_SetOpacity(const NativePixelMap* native, float opacity);

/**
 * @brief Scales a NativePixelMap object.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param x Scale ratio of the width.
 * @param y Scale ratio of the height.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_GET_DATA_ABNORMAL}: An error occurs during image data retrieval.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_FAILED}: Decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_CHECK_FORMAT_ERROR}: The format check fails.</li>
 *     <li>{@link IMAGE_RESULT_THIRDPART_SKIA_ERROR}: Skia decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST}: Sharing the memory fails.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL}: Data in the shared memory is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_MALLOC_ABNORMAL}: An error occurs during memory allocation.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li>
 *     <li>{@link IMAGE_RESULT_INIT_ABNORMAL}: The image fails to be initialized.</li>
 *     <li>{@link IMAGE_RESULT_CROP}: Cropping fails.</li>
 *     <li>{@link IMAGE_RESULT_UNKNOWN_FORMAT}: The image format is unknown.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_REGISTER_FAILED}: The plugin fails to be registered.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_CREATE_FAILED}: The plugin fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_ALPHA_TYPE_ERROR}: The alpha type is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ALLOCATER_TYPE_ERROR}: The memory allocator type is incorrect.</li></ul>
 * @see Scale
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_Scale(const NativePixelMap* native, float x, float y);

/**
 * @brief Scales a NativePixelMap object based on the specified anti-aliasing level, width, and height.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param x Scale ratio of the width.
 * @param y Scale ratio of the height.
 * @param level Anti-aliasing level.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_GET_DATA_ABNORMAL}: An error occurs during image data retrieval.</li>
 *     <li>{@link IMAGE_RESULT_CHECK_FORMAT_ERROR}: The format check fails.</li>
 *     <li>{@link IMAGE_RESULT_THIRDPART_SKIA_ERROR}: Skia decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL}: Data in the shared memory is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_MALLOC_ABNORMAL}: An error occurs during memory allocation.</li>
 *     <li>{@link IMAGE_RESULT_UNKNOWN_FORMAT}: The image format is unknown.</li></ul>
 * @see Scale
 * @since 12
 * @version 1.0
 */
int32_t OH_PixelMap_ScaleWithAntiAliasing(const NativePixelMap* native, float x, float y,
    OH_PixelMap_AntiAliasingLevel level);

/**
 * @brief Translates a NativePixelMap object.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param x Horizontal distance to translate.
 * @param y Vertical distance to translate.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_GET_DATA_ABNORMAL}: An error occurs during image data retrieval.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_FAILED}: Decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_CHECK_FORMAT_ERROR}: The format check fails.</li>
 *     <li>{@link IMAGE_RESULT_THIRDPART_SKIA_ERROR}: Skia decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST}: Sharing the memory fails.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL}: Data in the shared memory is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_MALLOC_ABNORMAL}: An error occurs during memory allocation.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li>
 *     <li>{@link IMAGE_RESULT_CROP}: Cropping fails.</li>
 *     <li>{@link IMAGE_RESULT_UNKNOWN_FORMAT}: The image format is unknown.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_REGISTER_FAILED}: The plugin fails to be registered.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_CREATE_FAILED}: The plugin fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_ALPHA_TYPE_ERROR}: The alpha type is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ALLOCATER_TYPE_ERROR}: The memory allocator type is incorrect.</li></ul>
 * @see Translate
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_Translate(const NativePixelMap* native, float x, float y);

/**
 * @brief Rotates a NativePixelMap object.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param angle Angle to rotate.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_GET_DATA_ABNORMAL}: An error occurs during image data retrieval.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_FAILED}: Decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_CHECK_FORMAT_ERROR}: The format check fails.</li>
 *     <li>{@link IMAGE_RESULT_THIRDPART_SKIA_ERROR}: Skia decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST}: Sharing the memory fails.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL}: Data in the shared memory is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_MALLOC_ABNORMAL}: An error occurs during memory allocation.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li>
 *     <li>{@link IMAGE_RESULT_CROP}: Cropping fails.</li>
 *     <li>{@link IMAGE_RESULT_UNKNOWN_FORMAT}: The image format is unknown.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_REGISTER_FAILED}: The plugin fails to be registered.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_CREATE_FAILED}: The plugin fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_ALPHA_TYPE_ERROR}: The alpha type is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ALLOCATER_TYPE_ERROR}: The memory allocator type is incorrect.</li></ul>
 * @see Rotate
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_Rotate(const NativePixelMap* native, float angle);

/**
 * @brief Flips a NativePixelMap object.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param x Whether to flip around the x axis.
 * @param y Whether to flip around the y axis.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_GET_DATA_ABNORMAL}: An error occurs during image data retrieval.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_FAILED}: Decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_CHECK_FORMAT_ERROR}: The format check fails.</li>
 *     <li>{@link IMAGE_RESULT_THIRDPART_SKIA_ERROR}: Skia decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST}: Sharing the memory fails.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL}: Data in the shared memory is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_MALLOC_ABNORMAL}: An error occurs during memory allocation.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li>
 *     <li>{@link IMAGE_RESULT_CROP}: Cropping fails.</li>
 *     <li>{@link IMAGE_RESULT_UNKNOWN_FORMAT}: The image format is unknown.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_REGISTER_FAILED}: The plugin fails to be registered.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_CREATE_FAILED}: The plugin fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_ALPHA_TYPE_ERROR}: The alpha type is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ALLOCATER_TYPE_ERROR}: The memory allocator type is incorrect.</li></ul>
 * @see Flip
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_Flip(const NativePixelMap* native, int32_t x, int32_t y);

/**
 * @brief Crops a NativePixelMap object.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param x X-coordinate of the upper left corner of the target image.
 * @param y Y-coordinate of the upper left corner of the target image.
 * @param width Width of the cropped region.
 * @param height Height of the cropped region.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_GET_DATA_ABNORMAL}: An error occurs during image data retrieval.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_FAILED}: Decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_CHECK_FORMAT_ERROR}: The format check fails.</li>
 *     <li>{@link IMAGE_RESULT_THIRDPART_SKIA_ERROR}: Skia decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST}: Sharing the memory fails.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL}: Data in the shared memory is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_MALLOC_ABNORMAL}: An error occurs during memory allocation.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li>
 *     <li>{@link IMAGE_RESULT_CROP}: Cropping fails.</li>
 *     <li>{@link IMAGE_RESULT_UNKNOWN_FORMAT}: The image format is unknown.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_REGISTER_FAILED}: The plugin fails to be registered.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_CREATE_FAILED}: The plugin fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_ALPHA_TYPE_ERROR}: The alpha type is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ALLOCATER_TYPE_ERROR}: The memory allocator type is incorrect.</li></ul>
 * @see Crop
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_Crop(const NativePixelMap* native, int32_t x, int32_t y, int32_t width, int32_t height);

/**
 * @brief Obtains the image information of a NativePixelMap object.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param info Pointer to the image information.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_GET_DATA_ABNORMAL}: An error occurs during image data retrieval.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_FAILED}: Decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_CHECK_FORMAT_ERROR}: The format check fails.</li>
 *     <li>{@link IMAGE_RESULT_THIRDPART_SKIA_ERROR}: Skia decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST}: Sharing the memory fails.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL}: Data in the shared memory is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_MALLOC_ABNORMAL}: An error occurs during memory allocation.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li>
 *     <li>{@link IMAGE_RESULT_CROP}: Cropping fails.</li>
 *     <li>{@link IMAGE_RESULT_UNKNOWN_FORMAT}: The image format is unknown.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_REGISTER_FAILED}: The plugin fails to be registered.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_CREATE_FAILED}: The plugin fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_ALPHA_TYPE_ERROR}: The alpha type is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ALLOCATER_TYPE_ERROR}: The memory allocator type is incorrect.</li></ul>
 * @see OhosPixelMapInfos
 * @since 10
 * @version 2.0
 */
int32_t OH_PixelMap_GetImageInfo(const NativePixelMap* native, OhosPixelMapInfos *info);

/**
 * @brief Obtains the memory address of a NativePixelMap object and locks the memory.
 *
 * @param native Pointer to a NativePixelMap object.
 * @param addr Double pointer to the memory address.
 * @see UnAccessPixels
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_GET_DATA_ABNORMAL}: An error occurs during image data retrieval.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_FAILED}: Decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_CHECK_FORMAT_ERROR}: The format check fails.</li>
 *     <li>{@link IMAGE_RESULT_THIRDPART_SKIA_ERROR}: Skia decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST}: Sharing the memory fails.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL}: Data in the shared memory is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_MALLOC_ABNORMAL}: An error occurs during memory allocation.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li>
 *     <li>{@link IMAGE_RESULT_CROP}: Cropping fails.</li>
 *     <li>{@link IMAGE_RESULT_UNKNOWN_FORMAT}: The image format is unknown.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_REGISTER_FAILED}: The plugin fails to be registered.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_CREATE_FAILED}: The plugin fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_ALPHA_TYPE_ERROR}: The alpha type is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ALLOCATER_TYPE_ERROR}: The memory allocator type is incorrect.</li></ul>
 * @since 10
 * @version 2.0
 */
int32_t OH_PixelMap_AccessPixels(const NativePixelMap* native, void** addr);

/**
 * @brief Unlocks the memory of a NativePixelMap object. This function is used with {@link OH_PixelMap_AccessPixels} in
 * pairs.
 *
 * @param native Pointer to a NativePixelMap object.
 * @return Result code defined in {@link IRNdkErrCode}:
 *     <ul><li>{@link IMAGE_RESULT_SUCCESS}: The operation is successful.</li>
 *     <li>{@link IMAGE_RESULT_BAD_PARAMETER}: A parameter is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_JNI_ENV_ABNORMAL}: The JNI environment is abnormal.</li>
 *     <li>{@link IMAGE_RESULT_INVALID_PARAMETER}: A parameter is invalid.</li>
 *     <li>{@link IMAGE_RESULT_GET_DATA_ABNORMAL}: An error occurs during image data retrieval.</li>
 *     <li>{@link IMAGE_RESULT_DECODE_FAILED}: Decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_CHECK_FORMAT_ERROR}: The format check fails.</li>
 *     <li>{@link IMAGE_RESULT_THIRDPART_SKIA_ERROR}: Skia decoding fails.</li>
 *     <li>{@link IMAGE_RESULT_DATA_ABNORMAL}: The image input data is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST}: Sharing the memory fails.</li>
 *     <li>{@link IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL}: Data in the shared memory is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_MALLOC_ABNORMAL}: An error occurs during memory allocation.</li>
 *     <li>{@link IMAGE_RESULT_DATA_UNSUPPORT}: The attribute is invalid or the image data is not supported.</li>
 *     <li>{@link IMAGE_RESULT_CROP}: Cropping fails.</li>
 *     <li>{@link IMAGE_RESULT_UNKNOWN_FORMAT}: The image format is unknown.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_REGISTER_FAILED}: The plugin fails to be registered.</li>
 *     <li>{@link IMAGE_RESULT_PLUGIN_CREATE_FAILED}: The plugin fails to be created.</li>
 *     <li>{@link IMAGE_RESULT_ALPHA_TYPE_ERROR}: The alpha type is incorrect.</li>
 *     <li>{@link IMAGE_RESULT_ALLOCATER_TYPE_ERROR}: The memory allocator type is incorrect.</li></ul>
 * @see AccessPixels
 * @since 10
 * @version 2.0
 */
int32_t OH_PixelMap_UnAccessPixels(const NativePixelMap* native);

#ifdef __cplusplus
};
#endif
/** @} */

#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PIXEL_MAP_NAPI_H_

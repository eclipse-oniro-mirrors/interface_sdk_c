/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup ImageProcessing
 * @{
 *
 * @brief Provide image processing including color space conversion and metadata generation.
 *
 * @since 13
 */

/**
 * @file image_processing_types.h
 *
 * @brief 图片处理的类型定义。
 *
 * @library libimage_processing.so
 * @syscap SystemCapability.Multimedia.VideoProcessingEngine
 * @kit ImageKit
 * @since 13
 */

#ifndef VIDEO_PROCESSING_ENGINE_C_API_IMAGE_PROCESSING_TYPES_H
#define VIDEO_PROCESSING_ENGINE_C_API_IMAGE_PROCESSING_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 提供OH_ImageProcessing结构体声明。<br>定义一个初始化为空的OH_ImageProcessing指针，并调用{@link OH_ImageProcessing_Create}来创建图片处理实例。
 * 调用该接口前，应确保传入的指针为空。用户可根据不同的图片处理类型，分别创建多个图片处理实例。
 *
 * @since 13
 */
typedef struct OH_ImageProcessing OH_ImageProcessing;

/**
 * @brief OH_PixelmapNative是Native层封装的图像解码后无压缩的位图格式结构体，支持像素数据读写、不透明度设置、缩放、平移、旋转、翻转、裁剪等操作，
 * 适用于需要在Native层对Pixelmap进行像素级处理与变换的场景。<br>创建OH_PixelmapNative需要使用{@link OH_PixelmapNative_CreatePixelmap}系列函数，
 * 该函数在未指定源像素格式时，会默认按BGRA_8888格式解析源像素数据。使用完毕后，必须调用{@link OH_PixelmapNative_Release}函数释放资源，两者需配对使用，否则会导致内存泄漏。<br>
 * OH_PixelmapNative结构体的部分相关函数和操作方式如下：
 *
 * @since 13
 */
typedef struct OH_PixelmapNative OH_PixelmapNative;

/**
 * @brief 为OH_AVFormat接口定义native层对象。
 *
 * @since 13
 */
typedef struct OH_AVFormat OH_AVFormat;

/**
 * @brief 用于创建色彩空间转换的图片处理实例。
 * <br>色彩空间转换包括单层HDR图片转换SDR图片，SDR图片之间的转换，以及SDR图片转换单层HDR图片，部分能力由厂商支持。使用
 * {@link OH_ImageProcessing_IsColorSpaceConversionSupported}查询某种转换是否支持在单层图片之间进行。
 * <br>**参考：**{@link OH_ImageProcessing_Create}
 *
 * @see OH_ImageProcessing_Create
 * @since 13
 */
extern const int32_t IMAGE_PROCESSING_TYPE_COLOR_SPACE_CONVERSION;

/**
 * @brief 用于创建双层HDR图片转换单层HDR图片的图片处理实例。
 * <br>包括从双层HDR图片转换为单层HDR图片的能力。部分能力由厂商支持。
 * 使用{@link OH_ImageProcessing_IsCompositionSupported}查询是否支持从双层HDR图片到单层HDR图片的转换。
 * <br>**参考：**{@link OH_ImageProcessing_Create}
 *
 * @see OH_ImageProcessing_Create
 * @since 13
 */
extern const int32_t IMAGE_PROCESSING_TYPE_COMPOSITION;

/**
 * @brief 用于创建单层HDR图片转换双层HDR图片的图片处理实例。
 * <br>包括从单层HDR图片转换为双层HDR图片的能力。部分能力由厂商支持。
 * 使用{@link OH_ImageProcessing_IsDecompositionSupported}查询是否支持从单层HDR图片到双层HDR图片的转换。
 * <br>**参考：**{@link OH_ImageProcessing_Create}
 *
 * @see OH_ImageProcessing_Create
 * @since 13
 */
extern const int32_t IMAGE_PROCESSING_TYPE_DECOMPOSITION;

/**
 * @brief 用于创建元数据生成的图片处理实例。
 * <br>生成单层HDR图片的HDR Vivid元数据。该能力由厂商支持。如果不支持该能力，{@link OH_ImageProcessing_Create}将返回
 * {@link IMAGE_PROCESSING_ERROR_UNSUPPORTED_PROCESSING}。
 * <br>**参考：**{@link OH_ImageProcessing_Create}
 *
 * @see OH_ImageProcessing_Create
 * @since 13
 */
extern const int32_t IMAGE_PROCESSING_TYPE_METADATA_GENERATION;

/**
 * @brief 用于创建细节增强的图片处理实例。
 * <br>按指定图像质量缩放或调整图片大小，或仅增强图像细节以在不更改分辨率的情况下渲染图片。
 * <br>**参考：**{@link OH_ImageProcessing_Create}
 *
 * @see OH_ImageProcessing_Create
 * @since 13
 */
extern const int32_t IMAGE_PROCESSING_TYPE_DETAIL_ENHANCER;

/**
 * @brief 用于设定图像细节增强的质量级别。
 * <br>使用{@link ImageDetailEnhancer_QualityLevel}获取其值。使用{@link OH_ImageProcessing_SetParameter}设置质量级别。使用
 * {@link OH_ImageProcessing_GetParameter}获取当前质量级别。
 *
 * @see OH_VideoProcessing_SetParameter, OH_VideoProcessing_GetParameter
 * @since 13
 */
extern const char* IMAGE_DETAIL_ENHANCER_PARAMETER_KEY_QUALITY_LEVEL;

/**
 * @brief 色彩空间信息，用于色彩空间转换能力查询。
 *
 * @see OH_ImageProcessing_IsColorSpaceConversionSupported, OH_ImageProcessing_IsCompositionSupported,
 * OH_ImageProcessing_IsDecompositionSupported
 * @since 13
 */
typedef struct ImageProcessing_ColorSpaceInfo {
    /**
     * 定义元数据类型，参考{@link OH_Pixelmap_HdrMetadataKey}。
     */
    int32_t metadataType;
    /**
     * 定义色彩空间，参考{@link ColorSpaceName}。
     */
    int32_t colorSpace;
    /**
     * 定义像素格式，参考{@link PIXEL_FORMAT}。
     */
    int32_t pixelFormat;
} ImageProcessing_ColorSpaceInfo;

/**
 * @brief 质量级别，用于细节增强能力。
 * <br>键参数的值IMAGE_DETAIL_ENHANCER_PARAMETER_KEY_QUALITY_LEVEL。
 *
 * @see OH_ImageProcessing_SetParameter, OH_ImageProcessing_GetParameter
 * @since 13
 */
typedef enum ImageDetailEnhancer_QualityLevel {
    /**
     * 无细节增强。<br>支持输入分辨率（px）：宽：[32, 3000]，高：[32, 3000]。<br>支持输出分辨率（px）：宽：[32, 3000]，高：[32, 3000]。
     */
    IMAGE_DETAIL_ENHANCER_QUALITY_LEVEL_NONE,
    /**
     * 细节增强质量较低，但速度较快。默认级别。<br>支持输入分辨率（px）：宽：[32, 3000]，高：[32, 3000]。<br>支持输出分辨率（px）：宽：[32, 3000]，高：[32, 3000]。
     */
    IMAGE_DETAIL_ENHANCER_QUALITY_LEVEL_LOW,
    /**
     * 细节增强质量中等，速度介于低级别与高级别之间。<br>支持输入分辨率（px）：宽：[32, 3000]，高：[32, 3000]。<br>支持输出分辨率（px）：宽：[32, 3000]，高：[32, 3000]。
     */
    IMAGE_DETAIL_ENHANCER_QUALITY_LEVEL_MEDIUM,
    /**
     * 细节增强质量较高，但速度较慢。<br>API version 13-22支持输入分辨率（px）：宽：[512, 2000]，高：[512, 2000]。<br>API version 13-22支持输出分辨率（px）：宽：
     * [512, 2000]，高：[512, 2000]。<br>API version 23及以后支持输入分辨率（px）：宽：[180, 2000]，高：[180, 2000]。<br>API version
     * 23及以后支持输出分辨率（px）：宽：[512, 2000]，高：[512, 2000]。
     */
    IMAGE_DETAIL_ENHANCER_QUALITY_LEVEL_HIGH,
} ImageDetailEnhancer_QualityLevel;

/**
 * @brief 图片处理接口错误码说明。
 *
 * @since 13
 */
typedef enum ImageProcessing_ErrorCode {
    /** @error 成功。 */
    IMAGE_PROCESSING_SUCCESS,
    /** @error 输入参数无效。
     *  <br>在以下错误条件下返回该错误码：
     *  <br>1. 输入或输出buffer无效，例如图片buffer为空。
     *  <br>2. 参数无效，例如参数为空。<br>3. 类型无效，例如在创建函数中传入的类型不存在。
     */
    IMAGE_PROCESSING_ERROR_INVALID_PARAMETER = 401,
    /** @error 未知错误，例如GPU计算失败或memcpy失败。 */
    IMAGE_PROCESSING_ERROR_UNKNOWN = 29200001,
    /** @error 全局环境初始化失败，例如GPU环境初始化失败。 */
    IMAGE_PROCESSING_ERROR_INITIALIZE_FAILED,
    /** @error 创建图片处理实例失败，例如实例数量超过上限。 */
    IMAGE_PROCESSING_ERROR_CREATE_FAILED,
    /** @error 处理图片buffer失败，例如处理超时。 */
    IMAGE_PROCESSING_ERROR_PROCESS_FAILED,
    /** @error 当前处理不支持，可以通过“OH_ImageProcessing_IsXXXSupported”接口查询是否支持该能力。 */
    IMAGE_PROCESSING_ERROR_UNSUPPORTED_PROCESSING,
    /** @error 无权限操作，可能由于状态不正确导致。 */
    IMAGE_PROCESSING_ERROR_OPERATION_NOT_PERMITTED,
    /** @error 内存不足。 */
    IMAGE_PROCESSING_ERROR_NO_MEMORY,
    /** @error 无效的图片处理实例，可能由于实例为空导致。 */
    IMAGE_PROCESSING_ERROR_INVALID_INSTANCE,
    /** @error 输入值无效。<br>在以下错误条件下返回该错误码：
     * <br>1. 输入或输出图片buffer无效，例如图片buffer的宽度（高度）过大或颜色空间不正确。
     * <br>2. 参数无效，例如参数不包括有效信息，例如细节增强的质量级别不正确。 */
    IMAGE_PROCESSING_ERROR_INVALID_VALUE
} ImageProcessing_ErrorCode;

#ifdef __cplusplus
}
#endif

#endif // VIDEO_PROCESSING_ENGINE_C_API_IMAGE_PROCESSING_TYPES_H
/** @} */

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
 * @brief Provide APIs for image quality processing.
 *
 * @since 13
 */

/**
 * @file image_processing.h
 *
 * @brief 声明图片处理函数。提供图片处理能力，包括色彩空间转换，元数据生成及图片缩放。
 *
 * @library libimage_processing.so
 * @syscap SystemCapability.Multimedia.VideoProcessingEngine
 * @kit ImageKit
 * @since 13
 */

#ifndef VIDEO_PROCESSING_ENGINE_C_API_IMAGE_PROCESSING_H
#define VIDEO_PROCESSING_ENGINE_C_API_IMAGE_PROCESSING_H

#include <stdint.h>
#include <stdbool.h>
#include "image_processing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化图片处理模块的全局环境。
 * <br>此函数为非必需函数。通常此函数在主进程启动时被调用，用于图片处理模块的全局环境初始化并可以减少{@link OH_ImageProcessing_Create}的耗时。调用
 * {@link OH_ImageProcessing_DeinitializeEnvironment}进行全局环境反初始化。可用于检查设备GPU是否正常工作。
 *
 * @return 如果初始化成功，则返回IMAGE_PROCESSING_SUCCESS，否则返回IMAGE_PROCESSING_ERROR_INITIALIZE_FAILED。
 * @since 13
 */
ImageProcessing_ErrorCode OH_ImageProcessing_InitializeEnvironment(void);

/**
 * @brief 反初始化图片处理模块的全局环境。
 * <br>如果{@link OH_ImageProcessing_InitializeEnvironment}被调用，则此函数为必需函数。通常此函数在主进程准备退出时被调用，用于反初始化图片处理模块的全局环境（由
 * {@link OH_ImageProcessing_InitializeEnvironment}接口初始化）。如果此时存在图片处理实例，则不应调用此函数。如果
 * {@link OH_ImageProcessing_InitializeEnvironment}未被调用，则不应调用此函数。
 *
 * @return 如果反初始化成功，则返回IMAGE_PROCESSING_SUCCESS。
 *     <br>如果存在图片处理实例未被销毁或{@link OH_ImageProcessing_InitializeEnvironment}接口未被调用，
 *     则返回IMAGE_PROCESSING_ERROR_OPERATION_NOT_PERMITTED。
 * @since 13
 */
ImageProcessing_ErrorCode OH_ImageProcessing_DeinitializeEnvironment(void);

/**
 * @brief 查询是否支持当前图片色彩空间转换能力。
 *
 * @param sourceImageInfo 指向输入图片色彩空间信息的指针。
 * @param destinationImageInfo 指向输出图片色彩空间信息的指针，
 * @return 如果支持当前色彩空间转换，返回true。
 *     <br>如果不支持当前色彩空间转换，返回false。
 * @since 13
 */
bool OH_ImageProcessing_IsColorSpaceConversionSupported(
    const ImageProcessing_ColorSpaceInfo* sourceImageInfo,
    const ImageProcessing_ColorSpaceInfo* destinationImageInfo);

/**
 * @brief 查询是否支持HDR双层图片转换为HDR单层图片。
 *
 * @param sourceImageInfo 指向输入图片色彩空间信息的指针。
 * @param sourceGainmapInfo 指向输入Gainmap色彩空间信息的指针。
 * @param destinationImageInfo 指向输出图片色彩空间信息的指针。
 * @return 如果支持HDR双层图片转换HDR单层图片能力，返回true。
 *     <br>如果不支持此能力，返回false。
 * @since 13
 */
bool OH_ImageProcessing_IsCompositionSupported(
    const ImageProcessing_ColorSpaceInfo* sourceImageInfo,
    const ImageProcessing_ColorSpaceInfo* sourceGainmapInfo,
    const ImageProcessing_ColorSpaceInfo* destinationImageInfo);

/**
 * @brief 查询是否支持HDR单层图片转换为HDR双层图片。
 *
 * @param sourceImageInfo 指向输入图片色彩空间信息的指针。
 * @param destinationImageInfo 指向输出图片色彩空间信息的指针。
 * @param destinationGainmapInfo 指向输出Gainmap色彩空间信息的指针。
 * @return 如果支持HDR单层图片转换为HDR双层图片能力，返回true。
 *     <br>如果不支持此能力，返回false。
 * @since 13
 */
bool OH_ImageProcessing_IsDecompositionSupported(
    const ImageProcessing_ColorSpaceInfo* sourceImageInfo,
    const ImageProcessing_ColorSpaceInfo* destinationImageInfo,
    const ImageProcessing_ColorSpaceInfo* destinationGainmapInfo);

/**
 * @brief 查询是否支持图片元数据生成能力。
 *
 * @param sourceImageInfo 指向输入图片色彩空间信息的指针。
 * @return 如果支持图片元数据生成能力，返回true。
 *     <br>如果不支持此能力，返回false。
 * @since 13
 */
bool OH_ImageProcessing_IsMetadataGenerationSupported(
    const ImageProcessing_ColorSpaceInfo* sourceImageInfo);
    
/**
 * @brief 创建一个图片处理模块实例。
 *
 * @param imageProcessor 输出参数。指针\*imageProcessor指向一个新的图片处理对象。指针\*imageProcessor在传递前必须是一个空指针。
 * @param type 使用IMAGE_PROCESSING_TYPE_XXX来指定图片处理类型。此实例的类型在创建后不能更改。
 * @return 如果创建成功，则返回IMAGE_PROCESSING_SUCCESS。
 *     <br>当指定的图片处理类型不支持时，返回IMAGE_PROCESSING_ERROR_UNSUPPORTED_PROCESSING，例如如果不支持图片元数据生成能力，则返回不支持该处理类型。
 *     <br>当创建失败时，返回IMAGE_PROCESSING_ERROR_CREATE_FAILED。
 *     <br>当该实例为空或指向该实例的指针为空时，返回IMAGE_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>当指定的图片处理类型无效时，返回IMAGE_PROCESSING_ERROR_INVALID_PARAMETER。
 * @since 13
 */
ImageProcessing_ErrorCode OH_ImageProcessing_Create(OH_ImageProcessing** imageProcessor, int32_t type);

/**
 * @brief 销毁当前图片处理模块实例。
 *
 * @param imageProcessor 指向图片处理模块实例的指针。当实例被销毁时，建议该指针设置为空。
 * @return 如果销毁成功，则返回IMAGE_PROCESSING_SUCCESS。
 *     <br>当该实例为空或该实例不是图片处理模块实例时，返回IMAGE_PROCESSING_ERROR_INVALID_INSTANCE。
 * @since 13
 */
ImageProcessing_ErrorCode OH_ImageProcessing_Destroy(OH_ImageProcessing* imageProcessor);

/**
 * @brief 设置图片处理模块参数。通过特定参数键添加参数。
 *
 * @param imageProcessor 指向图片处理模块实例的指针。
 * @param parameter 图片处理参数。
 * @return 如果设置参数成功，则返回IMAGE_PROCESSING_SUCCESS。
 *     <br>当该实例为空或该实例不是图片处理模块实例时，返回IMAGE_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>当参数为空时，返回IMAGE_PROCESSING_ERROR_INVALID_PARAMETER。
 *     <br>当部分参数无效时，返回IMAGE_PROCESSING_ERROR_INVALID_VALUE，例如参数包含不支持的参数键或值。
 *     <br>当内存分配失败时，返回IMAGE_PROCESSING_ERROR_NO_MEMORY。
 * @since 13
 */
ImageProcessing_ErrorCode OH_ImageProcessing_SetParameter(OH_ImageProcessing* imageProcessor,
    const OH_AVFormat* parameter);

/**
 * @brief 获取图片处理模块参数。通过特定参数键获取参数。
 *
 * @param imageProcessor 指向图片处理模块实例的指针。
 * @param parameter 该图片处理模块实例使用的参数。
 * @return 如果获取参数成功，则返回IMAGE_PROCESSING_SUCCESS。
 *     <br>当该实例为空或该实例不是图片处理模块实例时，返回IMAGE_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>当参数为空时，返回IMAGE_PROCESSING_ERROR_INVALID_PARAMETER。
 * @since 13
 */
ImageProcessing_ErrorCode OH_ImageProcessing_GetParameter(OH_ImageProcessing* imageProcessor,
    OH_AVFormat* parameter);

/**
 * @brief 实现单层图片间转换。此函数包括HDR图片到SDR图片的色彩空间转换，SDR图片到HDR图片的色彩空间转换，SDR图片到SDR图片的色彩空间转换和HDR图片的色彩空间转换。
 *
 * @param imageProcessor 指向图片处理模块实例的指针。该实例应该由IMAGE_PROCESSING_TYPE_COLOR_SPACE_CONVERSION类型创建。
 * @param sourceImage 指向输入图片的指针，指向的OH_PixelmapNative需为DMA内存，具体情况请参考{@link PixelMap的内存类型介绍}。
 * @param destinationImage 指向输出图片的指针，指向的OH_PixelmapNative需为DMA内存，具体情况请参考{@link PixelMap的内存类型介绍}。
 * @return 如果图片处理成功，则返回IMAGE_PROCESSING_SUCCESS。
 *     <br>当该实例为空或该实例不是图片处理模块实例时，返回IMAGE_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>当图片为空时，返回IMAGE_PROCESSING_ERROR_INVALID_PARAMETER。
 *     <br>当图片的某些属性无效时，返回IMAGE_PROCESSING_ERROR_INVALID_VALUE，例如图片的色彩空间是不支持的。
 *     <br>当该图片处理不支持时，返回IMAGE_PROCESSING_ERROR_UNSUPPORTED_PROCESSING。
 *     <br>当该图片处理中返回错误时，返回IMAGE_PROCESSING_ERROR_PROCESS_FAILED。
 *     <br>当内存分配失败时，返回IMAGE_PROCESSING_ERROR_NO_MEMORY。
 * @since 13
 */
ImageProcessing_ErrorCode OH_ImageProcessing_ConvertColorSpace(OH_ImageProcessing* imageProcessor,
    OH_PixelmapNative* sourceImage, OH_PixelmapNative* destinationImage);

/**
 * @brief 实现HDR双层图片到HDR单层图片的转换。此函数通过输入图片与输入Gainmap生成输出图片。
 *
 * @param imageProcessor 指向图片处理模块实例的指针。该实例应该由IMAGE_PROCESSING_TYPE_COMPOSITION类型创建。
 * @param sourceImage 指向输入图片的指针，指向的OH_PixelmapNative需为DMA内存，具体情况请参考{@link PixelMap的内存类型介绍}。
 * @param sourceGainmap 指向输入Gainmap的指针，指向的OH_PixelmapNative需为DMA内存，具体情况请参考{@link PixelMap的内存类型介绍}。
 * @param destinationImage 指向输出图片的指针，指向的OH_PixelmapNative需为DMA内存，具体情况请参考{@link PixelMap的内存类型介绍}。
 * @return 如果图片处理成功，则返回IMAGE_PROCESSING_SUCCESS。
 *     <br>当该实例为空或该实例不是图片处理模块实例时，返回IMAGE_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>当图片为空时，返回IMAGE_PROCESSING_ERROR_INVALID_PARAMETER。
 *     <br>当图片的某些属性无效时，返回IMAGE_PROCESSING_ERROR_INVALID_VALUE，例如图片的色彩空间是不支持的。
 *     <br>当该图片处理不支持时，返回IMAGE_PROCESSING_ERROR_UNSUPPORTED_PROCESSING。
 *     <br>当该图片处理中返回错误时，返回IMAGE_PROCESSING_ERROR_PROCESS_FAILED。
 *     <br>当内存分配失败时，返回IMAGE_PROCESSING_ERROR_NO_MEMORY。
 * @since 13
 */
ImageProcessing_ErrorCode OH_ImageProcessing_Compose(OH_ImageProcessing* imageProcessor,
    OH_PixelmapNative* sourceImage, OH_PixelmapNative* sourceGainmap, OH_PixelmapNative* destinationImage);

/**
 * @brief 实现HDR单层图片到HDR双层图片的转换。此函数通过输入图片生成输出图片和输出Gainmap。
 *
 * @param imageProcessor 指向图片处理模块实例的指针。该实例应该由IMAGE_PROCESSING_TYPE_DECOMPOSITION类型创建。
 * @param sourceImage 指向输入图片的指针，指向的OH_PixelmapNative需为DMA内存，具体情况请参考{@link PixelMap的内存类型介绍}。
 * @param destinationImage 指向输出图片的指针，指向的OH_PixelmapNative需为DMA内存，具体情况请参考{@link PixelMap的内存类型介绍}。
 * @param destinationGainmap 指向输出Gainmap的指针，指向的OH_PixelmapNative需为DMA内存，具体情况请参考{@link PixelMap的内存类型介绍}。
 * @return 如果图片处理成功，则返回IMAGE_PROCESSING_SUCCESS。
 *     <br>当该实例为空或该实例不是图片处理模块实例时，返回IMAGE_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>当图片为空时，返回IMAGE_PROCESSING_ERROR_INVALID_PARAMETER。
 *     <br>当图片的某些属性无效时，返回IMAGE_PROCESSING_ERROR_INVALID_VALUE，例如图片的色彩空间是不支持的。
 *     <br>当该图片处理不支持时，返回IMAGE_PROCESSING_ERROR_UNSUPPORTED_PROCESSING。
 *     <br>当该图片处理中返回错误时，返回IMAGE_PROCESSING_ERROR_PROCESS_FAILED。
 *     <br>当内存分配失败时，返回IMAGE_PROCESSING_ERROR_NO_MEMORY。
 * @since 13
 */
ImageProcessing_ErrorCode OH_ImageProcessing_Decompose(OH_ImageProcessing* imageProcessor,
    OH_PixelmapNative* sourceImage, OH_PixelmapNative* destinationImage, OH_PixelmapNative* destinationGainmap);

/**
 * @brief 生成HDR图片元数据。此函数为HDR图片生成元数据。
 *
 * @param imageProcessor 指向图片处理模块实例的指针。该实例应该由IMAGE_PROCESSING_TYPE_METADATA_GENERATION类型创建。
 * @param sourceImage 指向输入图片的指针，指向的OH_PixelmapNative需为DMA内存，具体情况请参考{@link PixelMap的内存类型介绍}。
 * @return 如果图片处理成功，则返回IMAGE_PROCESSING_SUCCESS。
 *     <br>当该实例为空或该实例不是图片处理模块实例时，返回IMAGE_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>当图片为空时，返回IMAGE_PROCESSING_ERROR_INVALID_PARAMETER。
 *     <br>当图片的某些属性无效时，返回IMAGE_PROCESSING_ERROR_INVALID_VALUE，例如图片的色彩空间是不支持的。
 *     <br>当该图片处理不支持时，返回IMAGE_PROCESSING_ERROR_UNSUPPORTED_PROCESSING。
 *     <br>当该图片处理中返回错误时，返回IMAGE_PROCESSING_ERROR_PROCESS_FAILED。
 *     <br>当内存分配失败时，返回IMAGE_PROCESSING_ERROR_NO_MEMORY。
 * @since 13
 */
ImageProcessing_ErrorCode OH_ImageProcessing_GenerateMetadata(OH_ImageProcessing* imageProcessor,
    OH_PixelmapNative* sourceImage);

/**
 * @brief 进行图片清晰度/细节增强。此函数根据输入图片和输出图片预设的尺寸，对源图片进行必要的缩放操作生成目标图片，并提供了多种缩放方法以平衡性能和图像质量。
 *
 * @param imageProcessor 指向图片处理模块实例的指针。该实例应该由IMAGE_PROCESSING_TYPE_DETAIL_ENHANCER类型创建。
 * @param sourceImage 指向输入图片的指针，指向的OH_PixelmapNative需为DMA内存，具体情况请参考{@link PixelMap的内存类型介绍}。
 * @param destinationImage 指向输出图片的指针，指向的OH_PixelmapNative需为DMA内存，具体情况请参考{@link PixelMap的内存类型介绍}。
 * @return 如果图片处理成功，则返回IMAGE_PROCESSING_SUCCESS。
 *     <br>当该实例为空或该实例不是图片处理模块实例时，返回IMAGE_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>当图片为空时，返回IMAGE_PROCESSING_ERROR_INVALID_PARAMETER。
 *     <br>当图片的某些属性无效时，返回IMAGE_PROCESSING_ERROR_INVALID_VALUE，例如图片的色彩空间是不支持的。
 *     <br>当该图片处理不支持时，返回IMAGE_PROCESSING_ERROR_UNSUPPORTED_PROCESSING。
 *     <br>当该图片处理中返回错误时，返回IMAGE_PROCESSING_ERROR_PROCESS_FAILED。
 *     <br>当内存分配失败时，返回IMAGE_PROCESSING_ERROR_NO_MEMORY。
 * @since 13
 */
ImageProcessing_ErrorCode OH_ImageProcessing_EnhanceDetail(OH_ImageProcessing* imageProcessor,
    OH_PixelmapNative* sourceImage, OH_PixelmapNative* destinationImage);
#ifdef __cplusplus
}
#endif

#endif // VIDEO_PROCESSING_ENGINE_C_API_IMAGE_PROCESSING_H
/** @} */

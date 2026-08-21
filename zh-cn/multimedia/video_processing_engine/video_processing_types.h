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
 * @addtogroup VideoProcessing
 * @{
 *
 * @brief 提供用于视频处理的API函数。
 *
 * @since 12
 */

/**
 * @file video_processing_types.h
 *
 * @brief 视频处理类型定义。
 *
 * @library libvideo_processing.so
 * @syscap SystemCapability.Multimedia.VideoProcessingEngine
 * @kit MediaKit
 * @since 12
 */

#ifndef VIDEO_PROCESSING_ENGINE_C_API_VIDEO_PROCESSING_TYPES_H
#define VIDEO_PROCESSING_ENGINE_C_API_VIDEO_PROCESSING_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义视频处理对象。
 * <br>定义一个OH_VideoProcessing空指针，调用{@link OH_VideoProcessing_Create}创建视频处理实例，该指针在创建实例之前必须为空。
 * 用户可以对不同的处理类型创建不同的视频处理实例。
 *
 * @since 12
 */
typedef struct OH_VideoProcessing OH_VideoProcessing;

/**
 * @brief 定义NativeWindow对象。
 *
 * @since 12
 */
typedef struct NativeWindow OHNativeWindow;

/**
 * @brief 定义OH_AVFormat对象。
 *
 * @since 12
 */
typedef struct OH_AVFormat OH_AVFormat;

/**
 * @brief 表示创建颜色空间转换视频处理实例。
 * <br>调用{@link OH_VideoProcessing_Create}创建颜色空间转换视频处理实例，如果不支持该能力返回{@link VideoProcessing_ErrorCode}.
 * VIDEO_PROCESSING_ERROR_UNSUPPORTED_PROCESSING。<br>可以调用{@link OH_VideoProcessing_IsColorSpaceConversionSupported}
 * 来检查是否支持这种处理。
 *
 * @see OH_VideoProcessing_Create
 * @since 12
 */
extern const int32_t VIDEO_PROCESSING_TYPE_COLOR_SPACE_CONVERSION;

/**
 * @brief 表示创建元数据生成视频处理实例。
 * <br>调用{@link OH_VideoProcessing_Create}创建元数据生成视频处理实例，如果不支持该能力返回{@link VideoProcessing_ErrorCode}.
 * VIDEO_PROCESSING_ERROR_UNSUPPORTED_PROCESSING。<br>可以调用{@link OH_VideoProcessing_IsMetadataGenerationSupported}
 * 来检查是否支持这种处理。
 *
 * @see OH_VideoProcessing_Create
 * @since 12
 */
extern const int32_t VIDEO_PROCESSING_TYPE_METADATA_GENERATION;

/**
 * @brief 表示创建细节增强视频处理实例。
 * <br>调用{@link OH_VideoProcessing_Create}创建细节增强视频处理实例，如果不支持该能力返回{@link VideoProcessing_ErrorCode}.
 * VIDEO_PROCESSING_ERROR_UNSUPPORTED_PROCESSING。
 *
 * @see OH_ImageProcessing_Create
 * @since 12
 */
extern const int32_t VIDEO_PROCESSING_TYPE_DETAIL_ENHANCER;

/**
 * @brief 指定视频细节增强的质量等级，参考{@link VideoDetailEnhancer_QualityLevel}查看具体取值。
 * <br>调用{@link OH_VideoProcessing_SetParameter}设置质量等级。
 * <br>调用{@link OH_VideoProcessing_GetParameter}获取当前质量等级。
 *
 * @see OH_VideoProcessing_SetParameter, OH_VideoProcessing_GetParameter
 * @since 12
 */
extern const char* VIDEO_DETAIL_ENHANCER_PARAMETER_KEY_QUALITY_LEVEL;

/**
 * @brief 指定视频元数据生成的风格模式。具体取值请参考{@link VideoMetadataGeneratorStyleControl}。
 * <br>调用{@link OH_AVFormat_SetIntValue}设置视频元数据生成的风格模式到AVFormat参数。
 * <br>调用{@link OH_VideoProcessing_SetParameter}设置当前视频元数据生成的风格模式。
 * <br>调用{@link OH_VideoProcessing_GetParameter}获取当前视频元数据生成的风格模式。
 *
 * @since 22
 */
extern const char* VIDEO_METADATA_GENERATOR_STYLE_CONTROL;

/**
 * @brief 视频颜色空间信息数据结构。
 *
 * @see OH_VideoProcessing_IsColorSpaceConversionSupported
 * @since 12
 */
typedef struct VideoProcessing_ColorSpaceInfo {
    /**
    * 视频元数据类型，参考{@link OH_NativeBuffer_MetadataType}。
    */
    int32_t metadataType;
    /**
    * 视频颜色空间类型，参考{@link OH_NativeBuffer_ColorSpace}。
    */
    int32_t colorSpace;
    /**
    * 视频像素格式，参考{@link OH_NativeBuffer_Format}。
    */
    int32_t pixelFormat;
} VideoProcessing_ColorSpaceInfo;

/**
 * @brief 用于细节增强的质量等级。参数{@link VIDEO_DETAIL_ENHANCER_PARAMETER_KEY_QUALITY_LEVEL}的具体取值，设置方法详见开发指南。
 *
 * @see OH_VideoProcessing_SetParameter, OH_VideoProcessing_GetParameter
 * @since 12
 */
typedef enum VideoDetailEnhancer_QualityLevel {
    /** 无细节增强。 */
    VIDEO_DETAIL_ENHANCER_QUALITY_LEVEL_NONE,
    /** 低质量等级细节增强，速度较快，默认设置。 */
    VIDEO_DETAIL_ENHANCER_QUALITY_LEVEL_LOW,
    /** 中等质量等级细节增强，速度适中。 */
    VIDEO_DETAIL_ENHANCER_QUALITY_LEVEL_MEDIUM,
    /** 高质量等级细节增强，速度相对较慢。 */
    VIDEO_DETAIL_ENHANCER_QUALITY_LEVEL_HIGH,
} VideoDetailEnhancer_QualityLevel;

/**
 * @brief 视频元数据生成的风格模式。参数的具体取值请参考{@link VIDEO_METADATA_GENERATOR_STYLE_CONTROL}。
 *
 * @see OH_AVFormat_SetIntValue, OH_VideoProcessing_SetParameter, OH_VideoProcessing_GetParameter
 * @since 22
 */
typedef enum VideoMetadataGeneratorStyleControl {
    /** 对比度优先模式。 */
    VIDEO_METADATA_GENERATOR_CONTRAST_MODE = 0,
    /** 亮度优先模式。 */
    VIDEO_METADATA_GENERATOR_BRIGHT_MODE = 1
} VideoMetadataGeneratorStyleControl;

/**
 * @brief 视频处理错误码。
 *
 * @since 12
 */
typedef enum VideoProcessing_ErrorCode {
    /** @error 处理成功。 */
    VIDEO_PROCESSING_SUCCESS,
    /** @error 输入参数无效。以下情况都会返回该错误码：
     *  <br>1. 无效的输入或输出视频buffer，视频buffer为空。
     *  <br>2. 无效的参数，参数为空。
     *  <br>3. 无效的处理类型。
     */
    VIDEO_PROCESSING_ERROR_INVALID_PARAMETER = 401,
    /** @error 未知错误，比如GPU计算失败或memcpy失败。 */
    VIDEO_PROCESSING_ERROR_UNKNOWN = 29210001,
    /** @error 视频处理全局环境初始化失败，比如初始化GPU环境失败。
     *  请检查设备是否支持GPU加速，或尝试重启应用后重试。
     */
    VIDEO_PROCESSING_ERROR_INITIALIZE_FAILED,
    /** @error 创建视频处理实例失败，比如实例总数超出上限。可调用{@link OH_VideoProcessing_Destroy}释放不再使用的实例后重试。 */
    VIDEO_PROCESSING_ERROR_CREATE_FAILED,
    /** @error 处理过程失败，比如处理时间超时。 */
    VIDEO_PROCESSING_ERROR_PROCESS_FAILED,
    /** @error 不支持的处理类型，比如试图创建不支持的视频处理实例。
     *  目前可对两种视频处理功能检查支持情况：{@link OH_VideoProcessing_IsColorSpaceConversionSupported},
     *  {@link OH_VideoProcessing_IsMetadataGenerationSupported}。
     */
    VIDEO_PROCESSING_ERROR_UNSUPPORTED_PROCESSING,
    /** @error 不允许的操作，比如不满足调用接口所需的运行状态下调用该接口。 */
    VIDEO_PROCESSING_ERROR_OPERATION_NOT_PERMITTED,
    /** @error 内存不足。请释放不再使用的资源后重试，或减少视频处理的分辨率。 */
    VIDEO_PROCESSING_ERROR_NO_MEMORY,
    /** @error 视频处理实例无效，比如视频处理实例为空实例。 */
    VIDEO_PROCESSING_ERROR_INVALID_INSTANCE,
    /** @error 输入值无效，以下情况都会造成这种错误：
     *  <br>1. 视频buffer宽高太大或者颜色空间错误。
     *  <br>2. 参数包含无效的值，比如细节增强的质量等级错误。
     */
    VIDEO_PROCESSING_ERROR_INVALID_VALUE
} VideoProcessing_ErrorCode;

/**
 * @brief 视频处理状态。视频处理状态通过回调函数{@link OH_VideoProcessingCallback_OnState}进行报告。
 *
 * @since 12
 */
typedef enum VideoProcessing_State {
    /** 视频处理进行中。 */
    VIDEO_PROCESSING_STATE_RUNNING,
    /** 视频处理已停止。 */
    VIDEO_PROCESSING_STATE_STOPPED
} VideoProcessing_State;

/**
 * @brief 视频处理回调对象类型。
 * <br>定义一个VideoProcessing_Callback空指针，调用{@link OH_VideoProcessingCallback_Create}来创建一个回调对象。
 * 创建之前该指针必须为空。通过调用{@link OH_VideoProcessing_RegisterCallback}来向视频处理实例注册回调对象。
 *
 * @since 12
 */
typedef struct VideoProcessing_Callback VideoProcessing_Callback;

/**
 * @brief 视频处理过程中报告错误的回调函数指针。
 * <br>错误码{@link VideoProcessing_ErrorCode}：
 * <br>VIDEO_PROCESSING_ERROR_UNSUPPORTED_PROCESSING，不支持的处理，比如不支持输入输出的颜色空间类型转换。
 * <br>VIDEO_PROCESSING_ERROR_INVALID_VALUE，无效的视频属性，比如视频的颜色空间无效。
 * <br>VIDEO_PROCESSING_ERROR_NO_MEMORY，内存不足。
 * <br>VIDEO_PROCESSING_ERROR_PROCESS_FAILED，处理过程中出错。
 *
 * @param videoProcessor 视频处理实例。
 * @param error 报告给用户的错误码。
 * @param userData 用户的自定义数据。
 * @since 12
 */
typedef void (*OH_VideoProcessingCallback_OnError)(OH_VideoProcessing* videoProcessor,
    VideoProcessing_ErrorCode error, void* userData);

/**
 * @brief 报告视频处理状态的回调函数指针。
 * <br>{@link OH_VideoProcessing_Start}成功调用之后状态会变为{@link VideoProcessing_State}.VIDEO_PROCESSING_STATE_RUNNING.
 * 调用{@link OH_VideoProcessing_Stop}，所有的缓存buffer处理完成后，状态会变为
 * {@link VideoProcessing_State}.VIDEO_PROCESSING_STATE_STOPPED。
 *
 * @param videoProcessor 视频处理实例。
 * @param state 视频处理状态。
 * @param userData 用户的自定义数据。
 * @since 12
 */
typedef void (*OH_VideoProcessingCallback_OnState)(OH_VideoProcessing* videoProcessor, VideoProcessing_State state,
    void* userData);

/**
 * @brief 报告输出buffer已填充好数据的回调函数指针。
 * <br>每个新输出buffer填充好数据之后该buffer的索引就会报告给用户。
 * 调用{@link OH_VideoProcessing_RenderOutputBuffer}根据索引来处理渲染并输出该buffer。如果未注册该函数，
 * 则输出buffer填充好数据后不会报告用户，而是直接进行处理渲染并输出。
 *
 * @param videoProcessor 视频处理实例。
 * @param index 新输出buffer的索引。
 * @param userData 用户自定义的数据。
 * @since 12
 */
typedef void (*OH_VideoProcessingCallback_OnNewOutputBuffer)(OH_VideoProcessing* videoProcessor, uint32_t index,
    void* userData);

/**
 * @brief Used to define video aisr autoeffect in XComponent.
 *
 * Use {@link OH_VideoProcessing_IsAutoEffectSupported} to query if aisr autoeffect is supported.
 * @since 26.1.0
 */
extern const int32_t VIDEO_PROCESSING_TYPE_AUTOEFFECT_AISR;
 
/**
 * @brief Sets the key value for enabling or disabling AutoEffect.
 *
 * Use {@link OH_AVFormat_SetIntValue} to set the enable value (0 is false, 1 is true) to the AVFormat parameter.
 * Use {@link OH_VideoProcessing_SetAutoEffectParam} to set the parameters to the video processing instance.
 * @since 26.1.0
 */
extern const char *VIDEO_AUTOEFFECT_ENABLE;
	 
/**
 * @brief Sets the AISR strength.
 *
 * Use {@link OH_AVFormat_SetFloatValue} to set the strength value to the AVFormat parameter.
 * When the value is in the range [0.0, 1.0], the larger the value, the better the image quality,
 * If this parameter is set to a value less than 0, the image quality enhancement is adaptive.
 * Use {@link OH_VideoProcessing_SetAutoEffectParam} to set the parameters of the video processing instance.
 * @since 26.1.0
 */
extern const char *VIDEO_AUTOEFFECT_AISR_STRENGTH;

#ifdef __cplusplus
}
#endif

#endif // VIDEO_PROCESSING_ENGINE_C_API_VIDEO_PROCESSING_TYPES_H
/** @} */

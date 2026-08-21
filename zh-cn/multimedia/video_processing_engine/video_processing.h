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
 * @file video_processing.h
 *
 * @brief 声明视频处理函数。
 *
 * @library libvideo_processing.so
 * @syscap SystemCapability.Multimedia.VideoProcessingEngine
 * @kit MediaKit
 * @since 12
 */

#ifndef VIDEO_PROCESSING_ENGINE_C_API_VIDEO_PROCESSING_H
#define VIDEO_PROCESSING_ENGINE_C_API_VIDEO_PROCESSING_H

#include <stdint.h>
#include <stdbool.h>
#include "video_processing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化视频处理全局环境。
 * <br>该函数是可选的。
 * <br>该函数只在主进程启动时被调用一次，用于初始化视频处理全局环境，这样可以减少{@link OH_VideoProcessing_Create}的时间。
 * <br>调用{@link OH_VideoProcessing_DeinitializeEnvironment}释放视频处理全局环境。
 * <br>初始化后，必须释放视频处理全局环境，释放方式及时机详见{@link OH_VideoProcessing_DeinitializeEnvironment}。
 *
 * @return 如果初始化成功，返回VIDEO_PROCESSING_SUCCESS，否则返回VIDEO_PROCESSING_ERROR_INITIALIZE_FAILED。
 *     <br>如果失败，应用需要检查GPU是否正常工作。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessing_InitializeEnvironment(void);

/**
 * @brief 释放视频处理全局环境。
 * <br>调用前，必须调用{@link OH_VideoProcessing_InitializeEnvironment}初始化。
 * <br>通常在主进程即将退出时调用该函数，以释放通过调用{@link OH_VideoProcessing_InitializeEnvironment}函数初始化的全局环境。
 * <br>如果仍有视频处理的实例运行中，就不能调用该函数。
 *
 * @return 如果执行成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果还有视频处理的实例没有销毁或者没有调用{@link OH_VideoProcessing_InitializeEnvironment}，
 *     返回VIDEO_PROCESSING_ERROR_OPERATION_NOT_PERMITTED。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessing_DeinitializeEnvironment(void);

/**
 * @brief 查询是否支持视频颜色空间转换。
 *
 * @param sourceVideoInfo 输入视频颜色空间信息。
 * @param destinationVideoInfo 输出视频颜色空间信息。
 * @return 如果支持视频颜色空间转换返回true，否则返回false。
 * @since 12
 */
bool OH_VideoProcessing_IsColorSpaceConversionSupported(
    const VideoProcessing_ColorSpaceInfo* sourceVideoInfo,
    const VideoProcessing_ColorSpaceInfo* destinationVideoInfo);

/**
 * @brief 查询是否支持视频元数据生成。
 *
 * @param sourceVideoInfo 输入视频颜色空间信息。
 * @return 如果支持视频元数据生成返回true，否则返回false。
 * @since 12
 */
bool OH_VideoProcessing_IsMetadataGenerationSupported(
    const VideoProcessing_ColorSpaceInfo* sourceVideoInfo);

/**
 * @brief 创建视频处理实例。
 *
 * @param videoProcessor 输出参数。指向视频处理对象的指针的指针。输入前\*videoProcessor必须是空指针。
 * @param type 使用视频处理实例常量来指定处理类型。实例的处理类型不能改变。
 * @return 如果视频处理实例创建成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果处理类型不支持，返回VIDEO_PROCESSING_ERROR_UNSUPPORTED_PROCESSING，例如，不支持元数据生成。
 *     <br>如果创建视频处理实例失败，返回VIDEO_PROCESSING_ERROR_CREATE_FAILED。
 *     <br>如果实例为空或实例的指针非空，返回VIDEO_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>如果处理类型无效，返回VIDEO_PROCESSING_ERROR_INVALID_PARAMETER。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessing_Create(OH_VideoProcessing** videoProcessor, int type);

/**
 * @brief 销毁视频处理实例。
 * <br>销毁之前先停止实例，参阅{@link OH_VideoProcessing_Stop}。
 *
 * @param videoProcessor 指向视频处理实例的指针，建议在实例销毁之后将其设置为空指针。
 * @return 如果实例销毁成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果实例为空或者不是一个视频处理实例，返回VIDEO_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>如果实例仍在运行，返回VIDEO_PROCESSING_ERROR_OPERATION_NOT_PERMITTED。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessing_Destroy(OH_VideoProcessing* videoProcessor);

/**
 * @brief 注册回调函数。
 * <br>在开始视频处理之前注册回调函数，视频处理过程中无法注册回调函数。
 *
 * @param videoProcessor 指向视频处理实例的指针。
 * @param callback 回调函数指针。
 * @param userData 指向用户特定数据的指针，如this指针。
 * @return 如果回调函数注册成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果实例为空或者不是一个视频处理实例，返回VIDEO_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>如果回调函数指针为空，返回VIDEO_PROCESSING_ERROR_INVALID_PARAMETER。
 *     <br>如果实例仍在运行，返回VIDEO_PROCESSING_ERROR_OPERATION_NOT_PERMITTED。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessing_RegisterCallback(OH_VideoProcessing* videoProcessor,
    const VideoProcessing_Callback* callback, void* userData);

/**
 * @brief 设置视频处理输出surface。
 * <br>在视频处理启动之前设置输出surface。
 *
 * @param videoProcessor 指向视频处理实例的指针。
 * @param window 指向输出surface的指针。
 * @return 如果输出surface设置成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果实例为空或者不是一个视频处理实例，返回VIDEO_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>如果window为空指针，返回VIDEO_PROCESSING_ERROR_INVALID_PARAMETER。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessing_SetSurface(OH_VideoProcessing* videoProcessor,
    const OHNativeWindow* window);

/**
 * @brief 创建surface。
 * <br>在视频处理启动之前创建输入surface。调用{@link OH_NativeWindow_DestroyNativeWindow}销毁输入surface。
 *
 * @param videoProcessor 指向视频处理实例的指针。
 * @param window 指向输入surface的指针。例如，此输入surface指针可以指向视频解码器输出surface。
 * @return 如果执行成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果实例为空或者不是一个视频处理实例，返回VIDEO_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>如果window为空指针或指向window的指针为空，返回VIDEO_PROCESSING_ERROR_INVALID_PARAMETER。
 *     <br>如果创建surface失败，或者输入surface已经创建，或者视频处理实例还在运行，返回VIDEO_PROCESSING_ERROR_OPERATION_NOT_PERMITTED。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessing_GetSurface(OH_VideoProcessing* videoProcessor, OHNativeWindow** window);

/**
 * @brief 设置视频处理输出参数。
 *
 * @param videoProcessor 指向视频处理实例的指针。
 * @param parameter 指向视频处理参数实例的指针，用于传入需设置的视频处理参数，例如视频宽度、高度、像素格式及编解码格式等。
 * @return 如果参数设置成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果实例为空或者不是一个视频处理实例，返回VIDEO_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>如果参数为空，返回VIDEO_PROCESSING_ERROR_INVALID_PARAMETER。
 *     <br>如果参数的某些属性无效，返回VIDEO_PROCESSING_ERROR_INVALID_VALUE，例如，包含不支持的参数值。
 *     <br>如果内存分配失败，返回VIDEO_PROCESSING_ERROR_NO_MEMORY。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessing_SetParameter(OH_VideoProcessing* videoProcessor,
    const OH_AVFormat* parameter);

/**
 * @brief 获取视频处理参数。
 *
 * @param videoProcessor 指向视频处理实例的指针。
 * @param parameter 指向视频处理参数实例的指针，用于获取当前视频处理的参数，比如视频宽度、高度、像素格式、编解码格式等。
 * @return 如果参数获取成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果实例为空或者不是一个视频处理实例，返回VIDEO_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>如果参数为空，返回VIDEO_PROCESSING_ERROR_INVALID_PARAMETER。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessing_GetParameter(OH_VideoProcessing* videoProcessor, OH_AVFormat* parameter);

/**
 * @brief 启动视频处理。
 * <br>成功启动后，回调函数{@link OH_VideoProcessingCallback_OnState}会报告{@link VideoProcessing_State}.
 * VIDEO_PROCESSING_STATE_RUNNING状态。
 *
 * @param videoProcessor 指向视频处理实例的指针。
 * @return 如果执行成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果实例为空或者不是一个视频处理实例，返回VIDEO_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>如果没有设置输出surface，或者没有创建输入surface，或者实例已经运行，返回VIDEO_PROCESSING_ERROR_OPERATION_NOT_PERMITTED。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessing_Start(OH_VideoProcessing* videoProcessor);

/**
 * @brief 停止视频处理。
 * <br>成功停止后，回调函数{@link OH_VideoProcessingCallback_OnState}会报告{@link VideoProcessing_State}.
 * VIDEO_PROCESSING_STATE_STOPPED状态。
 *
 * @param videoProcessor 指向视频处理实例的指针。
 * @return 如果执行成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果实例为空或者不是一个视频处理实例，返回VIDEO_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>如果实例已经停止，返回VIDEO_PROCESSING_ERROR_OPERATION_NOT_PERMITTED。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessing_Stop(OH_VideoProcessing* videoProcessor);

/**
 * @brief 渲染处理并输出buffer。
 * <br>如果设置了回调函数{@link OH_VideoProcessingCallback_OnNewOutputBuffer}，当输出buffer准备好之后会通过回调函数把buffer的索引返回给用户。
 *
 * @param videoProcessor 指向视频处理实例的指针。
 * @param index 输出buffer的索引。
 * @return 如果执行成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果实例为空或者不是一个视频处理实例，返回VIDEO_PROCESSING_ERROR_INVALID_INSTANCE。
 *     <br>如果索引值无效，输出VIDEO_PROCESSING_ERROR_INVALID_PARAMETER。
 *     <br>如果没有设置回调函数{@link OH_VideoProcessingCallback_OnNewOutputBuffer}或者实例已经停止运行，
 *     返回VIDEO_PROCESSING_ERROR_OPERATION_NOT_PERMITTED。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessing_RenderOutputBuffer(OH_VideoProcessing* videoProcessor, uint32_t index);

/**
 * @brief 创建视频处理回调函数对象。
 *
 * @param callback 输出参数。\*callback是指向回调函数对象的指针。在创建回调函数对象之前\*callback必须为空指针。
 * @return 如果回调函数对象创建成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果callback为空，返回VIDEO_PROCESSING_ERROR_INVALID_PARAMETER。
 *     <br>如果内存不足，返回VIDEO_PROCESSING_ERROR_NO_MEMORY。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessingCallback_Create(VideoProcessing_Callback** callback);

/**
 * @brief 销毁回调对象。回调对象在注册之后就可以销毁。
 *
 * @param callback 指向回调对象的指针，建议在回调对象销毁之后将其设置为空指针。
 * @return 如果回调对象销毁成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果callback为空，返回VIDEO_PROCESSING_ERROR_INVALID_PARAMETER。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessingCallback_Destroy(VideoProcessing_Callback* callback);

/**
 * @brief 绑定回调函数{@link OH_VideoProcessingCallback_OnError}到回调对象。
 * 绑定完成之后，需要调用 {@link OH_VideoProcessing_RegisterCallback}，
 * 将回调对象注册到视频处理实例，才能使其生效。
 *
 * @param callback 指向回调对象的指针。
 * @param onError 回调函数。
 * @return 如果函数绑定成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果callback为空或者onError为空，返回VIDEO_PROCESSING_ERROR_INVALID_PARAMETER。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessingCallback_BindOnError(VideoProcessing_Callback* callback,
    OH_VideoProcessingCallback_OnError onError);

/**
 * @brief 绑定回调函数{@link OH_VideoProcessingCallback_OnState}到回调对象。
 * 绑定完成之后，需要调用 {@link OH_VideoProcessing_RegisterCallback}，
 * 将回调对象注册到视频处理实例，才能使其生效。
 *
 * @param callback 指向回调对象的指针。
 * @param onState 回调函数。
 * @return 如果函数绑定成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果callback为空或者onState为空，返回VIDEO_PROCESSING_ERROR_INVALID_PARAMETER。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessingCallback_BindOnState(VideoProcessing_Callback* callback,
    OH_VideoProcessingCallback_OnState onState);

/**
 * @brief 绑定回调函数{@link OH_VideoProcessingCallback_OnNewOutputBuffer}到回调对象。绑定完成之后，需要调用
 * {@link OH_VideoProcessing_RegisterCallback}，将回调对象注册到视频处理实例，才能使其生效。
 *
 * @param callback 指向回调对象的指针。
 * @param onNewOutputBuffer 回调函数。
 * @return 如果函数绑定成功，返回VIDEO_PROCESSING_SUCCESS。
 *     <br>如果callback为空，返回VIDEO_PROCESSING_ERROR_INVALID_PARAMETER。
 * @since 12
 */
VideoProcessing_ErrorCode OH_VideoProcessingCallback_BindOnNewOutputBuffer(VideoProcessing_Callback* callback,
    OH_VideoProcessingCallback_OnNewOutputBuffer onNewOutputBuffer);

/**
 * @brief Query if the autoeffect is supported.
 *
 * @param type [in] The autoeffect type to query.
 * @return <ul><li><b>true</b> if the autoeffect is supported.</li>
 *     <li><b>false</b> if the autoeffect is not supported.</li></ul>
 * @since 26.1.0
 */
bool OH_VideoProcessing_IsAutoEffectSupported(uint32_t type);
 
/**
 * @brief Specifies whether the type effect is required in the XComponent named name that will be created.
 *
 * Records the mapping between type, enable, and name in the internal map.
 * This should be called before {@link OH_VideoProcessing_SetAutoEffectParam}.
 * @param type [in] Specify AutoEffect to use.
 * @param enable [in] Enable or disable the type effect in the XComponent named name to be created later.
 * @param name [in] Specifies the name of an XComponent. If the current application has multiple XComponents with
 *     the same name, this parameter takes effect only on the first active XComponent.
 * @return <ul><li>{@link VIDEO_PROCESSING_SUCCESS} if the operation is successful.</li>
 *     <li>{@link VIDEO_PROCESSING_ERROR_INVALID_VALUE} if type is not {@link VIDEO_PROCESSING_TYPE_AUTOEFFECT_AISR}
 *     or name is null.</li>
 *     <li>{@link VIDEO_PROCESSING_ERROR_OPERATION_NOT_PERMITTED} if {@link OH_VideoProcessing_IsAutoEffectSupported}
 *     returns false for the type, or the same name has already been registered by calling this function.</li></ul>
 * @since 26.1.0
 */
VideoProcessing_ErrorCode OH_VideoProcessing_UseAutoEffect(uint32_t type, bool enable, const char *name);
 
/**
 * @brief Sets parameters for the automatic effect associated with the XComponent. 
 * Currently, the AutoEffect only takes effect on the last invoked XComponent.
 * @param type [in] Specify AutoEffect to use.
 * @param name [in] Specifies the name of an XComponent. If the current application has multiple XComponents
 *     with the same name, this parameter takes effect only on the first active XComponent.
 * @param param [in] The parameter according to the type see video_processing_type.h.
 * @return <ul><li>{@link VIDEO_PROCESSING_SUCCESS} if the operation is successful.</li>
 *     <li>{@link VIDEO_PROCESSING_ERROR_INVALID_VALUE} if the name is nullptr or the param value is invalid.</li>
 *     <li>{@link VIDEO_PROCESSING_ERROR_OPERATION_NOT_PERMITTED} if {@link OH_VideoProcessing_IsAutoEffectSupported}
 *     returns false for the type, or name does not match any registered name, or the VPE instance has not been
 *     created or {@link OH_VideoProcessing_UseAutoEffect} has not been called for the name.</li>
 *     <li>{@link VIDEO_PROCESSING_ERROR_UNKNOWN} if an internal algorithm error occurs.</li></ul>
 * @since 26.1.0
 */
VideoProcessing_ErrorCode OH_VideoProcessing_SetAutoEffectParam(uint32_t type, const char *name,
    const OH_AVFormat *param);

#ifdef __cplusplus
}
#endif

#endif // VIDEO_PROCESSING_ENGINE_C_API_VIDEO_PROCESSING_H
/** @} */

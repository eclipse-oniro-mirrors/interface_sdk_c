/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup OHAudioSuite
 * @{
 *
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 22
 * @version 1.0
 */
/**
 * @file native_audio_suite_engine.h
 *
 * @brief 声明与音频编创相关的接口。（包括引擎、管线、节点）。
 *
 * @library libohaudiosuite.so
 * @syscap SystemCapability.Multimedia.Audio.SuiteEngine
 * @kit AudioKit
 * @since 22
 * @version 1.0
 */
#ifndef NATIVE_AUDIO_SUITE_ENGINE_H
#define NATIVE_AUDIO_SUITE_ENGINE_H

#include <stdbool.h>
#include "native_audio_suite_base.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 创建音频编创引擎。
 *
 * @param audioSuiteEngine 音频编创引擎句柄，指向接收audioSuiteEngine变量的指针。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数audioSuiteEngine为空指针。
 *     <br>AUDIOSUITE_ERROR_INVALID_STATE：引擎已经被初始化。
 *     <br>AUDIOSUITE_ERROR_MEMORY_ALLOC_FAILED：内存申请失败。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_Create(OH_AudioSuiteEngine** audioSuiteEngine);

/**
 * @brief 销毁音频编创引擎句柄。
 *
 * @param audioSuiteEngine 音频编创引擎句柄，通过{@link OH_AudioSuiteEngine_Create}获取句柄。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数audioSuiteEngine为空指针。
 *     <br>AUDIOSUITE_ERROR_INVALID_STATE：引擎已被去初始化、引擎未创建或未初始化引擎。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_Destroy(OH_AudioSuiteEngine* audioSuiteEngine);

/**
 * @brief 在当前音频编创引擎中创建1个管线。管线是引擎内负责音频编创的执行单元，1个引擎可创建多个管线。
 * <br>支持最多创建10条管线，其中至多有1条实时预览管线。
 * <br>每个管线必须至少包含1个输入节点，有且只有1个输出节点。
 * <br>当管线在{@link OH_AudioSuite_PipelineWorkMode}.AUDIOSUITE_PIPELINE_EDIT_MODE模式下工作时，支持所有的效果节点。
 * <br>在API version 23之前，当管线在{@link OH_AudioSuite_PipelineWorkMode}.AUDIOSUITE_PIPELINE_REALTIME_MODE模式下工作时，仅支持
 * {@link OH_AudioNode_Type}.EFFECT_NODE_TYPE_EQUALIZER效果节点；
 * <br>在API version 23及以后，当管线在{@link OH_AudioSuite_PipelineWorkMode}.AUDIOSUITE_PIPELINE_REALTIME_MODE模式下工作时，支持所有效果节点。
 *
 * @param audioSuiteEngine 音频编创引擎句柄。通过{@link OH_AudioSuiteEngine_Create}获取句柄。
 * @param audioSuitePipeline 音频编创管线句柄。
 * @param workMode 管线工作模式。
 *     <br>1. AUDIOSUITE_PIPELINE_EDIT_MODE: 支持所有效果节点；
 *     <br>2. AUDIOSUITE_PIPELINE_REALTIME_MODE：支持均衡器等节点。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数audioSuiteEngine为空指针或参数audioSuitePipeline为空指针。
 *     <br>AUDIOSUITE_ERROR_ENGINE_NOT_EXIST：未初始化引擎。
 *     <br>AUDIOSUITE_ERROR_CREATED_EXCEED_SYSTEM_LIMITS：创建管线数量超过系统最大数量限制（引擎最多创建10条管线）。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_MEMORY_ALLOC_FAILED：内存申请失败。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_CreatePipeline(
    OH_AudioSuiteEngine* audioSuiteEngine,
    OH_AudioSuitePipeline** audioSuitePipeline, OH_AudioSuite_PipelineWorkMode workMode);

/**
 * @brief 销毁音频编创管线句柄。
 *
 * @param audioSuitePipeline 音频编创管线句柄。通过{@link OH_AudioSuiteEngine_CreatePipeline}获取需要销毁的句柄。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数audioSuitePipeline为空指针。
 *     <br>AUDIOSUITE_ERROR_PIPELINE_NOT_EXIST：管线不存在或已经被销毁。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_DestroyPipeline(OH_AudioSuitePipeline* audioSuitePipeline);

/**
 * @brief 开始运行该管线，管线会进入{@link OH_AudioSuite_PipelineState}.AUDIOSUITE_PIPELINE_RUNNING运行状态。
 *
 * @param audioSuitePipeline 音频编创管线句柄。通过{@link OH_AudioSuiteEngine_CreatePipeline}获取句柄。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数audioSuitePipeline为空指针。
 *     <br>AUDIOSUITE_ERROR_PIPELINE_NOT_EXIST：管线不存在或已经被销毁。
 *     <br>AUDIOSUITE_ERROR_INVALID_STATE：管线已在运行或节点连接异常。
 *     <br>可能的原因如下：
 *     <br>1. 管线已经在运行状态；
 *     <br>2. 当前管线中不存在输出类型节点；
 *     <br>3. 起始节点不是输入类型节点。
 *     <br>4. HOA输入节点未连接HOA空间渲染节点，或HOA空间渲染节点的前置节点不是HOA输入节点。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_StartPipeline(OH_AudioSuitePipeline* audioSuitePipeline);

/**
 * @brief 停止运行该管线，管线会进入{@link OH_AudioSuite_PipelineState}.AUDIOSUITE_PIPELINE_STOPPED停止状态。该函数不会改变管线中节点之间的连接关系，管线一旦被停止
 * ，{@link OH_AudioSuiteEngine_RenderFrame}就不能再进行音频处理。
 *
 * @param audioSuitePipeline 音频编创管线句柄。通过{@link OH_AudioSuiteEngine_CreatePipeline}获取句柄。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数audioSuitePipeline为空指针。
 *     <br>AUDIOSUITE_ERROR_PIPELINE_NOT_EXIST：管线不存在或已经被销毁。
 *     <br>AUDIOSUITE_ERROR_INVALID_STATE：管线已在停止状态。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_StopPipeline(OH_AudioSuitePipeline* audioSuitePipeline);

/**
 * @brief 获取当前管线的状态。
 *
 * @param audioSuitePipeline 音频编创管线句柄。通过{@link OH_AudioSuiteEngine_CreatePipeline}获取句柄。
 * @param pipelineState 管线状态的输出参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioSuitePipeline为空指针等。
 *     <br>AUDIOSUITE_ERROR_PIPELINE_NOT_EXIST：管线不存在或已经被销毁。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_GetPipelineState(
    OH_AudioSuitePipeline* audioSuitePipeline, OH_AudioSuite_PipelineState* pipelineState);

/**
 * @brief 应用调用此接口获取管线处理后的音频数据（针对单输出效果节点）。
 *
 * @param audioSuitePipeline 音频编创管线句柄。通过{@link OH_AudioSuiteEngine_CreatePipeline}获取句柄。
 * @param audioData 获取音频需要写入的数据地址。
 * @param requestFrameSize audioData的内存字节大小，需大于0。
 * @param responseSize 管线写入audioData的音频数据大小，不会大于requestFrameSize，单位为字节。
 * @param finishedFlag 标识当前管线是否渲染完成。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数为空指针或无效值。
 *     <br>可能的原因如下：
 *     <br>1. 参数audioSuitePipeline为空指针；
 *     <br>2. 参数audioData为空指针；
 *     <br>3. 参数requestFrameSize小于等于0；
 *     <br>4. 参数responseSize为空指针；
 *     <br>5. 参数finishedFlag为空指针。
 *     <br>AUDIOSUITE_ERROR_PIPELINE_NOT_EXIST：管线不存在或已经被销毁。
 *     <br>AUDIOSUITE_ERROR_INVALID_STATE：管线不在运行状态。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：管线渲染已完成（之前调用该接口时finishedFlag已写入为true）。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_RenderFrame(OH_AudioSuitePipeline* audioSuitePipeline,
    void* audioData, int32_t requestFrameSize, int32_t* responseSize, bool* finishedFlag);

/**
 * @brief 渲染该管线，获取管线处理后的音频数据。针对多输出效果节点，比如包含音源分离节点的管线，audioDataArray的大小需与效果节点的输出数量一一对应（例如：音源分离节点需两个：第1个为人声，第2个为背景声）。
 *
 * @param audioSuitePipeline 音频编创管线句柄。通过{@link OH_AudioSuiteEngine_CreatePipeline}获取句柄。
 * @param audioDataArray 用户读取音频数据时所使用的数组指针，每个一维数组大小需一致。
 * @param responseSize 管线写入audioData的音频数据大小。系统会确保每个一维数组被填充的数据大小一致，单位为字节。
 * @param finishedFlag 标记当前管线是否渲染完成。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数为空指针或无效值。
 *     <br>可能的原因如下：
 *     <br>1. 参数audioSuitePipeline为空指针；
 *     <br>2. 参数audioDataArray为空指针；
 *     <br>3. 参数audioDataArray中的某个成员为空指针；
 *     <br>4. 参数audioDataArray中的requestFrameSize小于等于0；
 *     <br>5. 参数responseSize为空指针；
 *     <br>6. 参数finishedFlag为空指针。
 *     <br>AUDIOSUITE_ERROR_PIPELINE_NOT_EXIST：管线不存在或已经被销毁。
 *     <br>AUDIOSUITE_ERROR_INVALID_STATE：管线不在运行状态。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：管线渲染已完成（之前调用该接口时finishedFlag已写入为true）。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_MultiRenderFrame(OH_AudioSuitePipeline* audioSuitePipeline,
    OH_AudioDataArray* audioDataArray, int32_t* responseSize, bool* finishedFlag);

/**
 * @brief 应用程序使用此接口进行音频数据和元数据处理。
 *
 * 应用程序需要在metaFrame结构体中设置audioData和metaData指针。
 * 以及数据的大小（即AudioDataSize和metaDataSize）。
 * 通过responseAudioSize和responseMetaSize返回处理后数据的实际大小。
 *
 * @systemapi
 * @param audioSuitePipeline 由{@link OH_AudioSuiteEngine_CreatePipeline}创建的引用。
 * @param metaFrame 音频元数据帧结构体指针。
 * @param responseAudioSize 接口实际写入的音频数据的大小，单位是字节。
 * @param responseMetaSize 接口实际写入的元数据的大小，单位是字节。
 * @param finishedFlag 该标志用于向用户指示是否已完成所有数据处理。
 * @return <ul>
 * <li>{@link #AUDIOSUITE_SUCCESS} 函数执行成功。</li>
 * <li>202 非系统应用调用了此系统 API。</li>
 * <li>{@link #AUDIOSUITE_ERROR_INVALID_PARAM} 参数为空指针或其他非法值。</li>
 * <li>{@link #AUDIOSUITE_ERROR_PIPELINE_NOT_EXIST} 管线不存在或已被销毁。</li>
 * <li>{@link #AUDIOSUITE_ERROR_INVALID_STATE} 管线不在运行状态。</li>
 * <li>{@link #AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION} 管线渲染已完成（之前调用该接口时 finishedFlag 已写入为 true）。</li>
 * <li>{@link #AUDIOSUITE_ERROR_TIMEOUT} 操作处理超时。</li>
 * <li>{@link #AUDIOSUITE_ERROR_SYSTEM} 系统发生其他异常。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuiteEngine_MetaRenderFrame(OH_AudioSuitePipeline* audioSuitePipeline,
    OH_AudioSuite_MetaFrame* metaFrame, int32_t* responseAudioSize, int32_t* responseMetaSize, bool* finishedFlag);

/**
 * @brief 获取一个音频编创节点构造器，用于配置并创建音频节点。构建器可复用，但若新节点属性与之前不同，必须使用{@link OH_AudioSuiteNodeBuilder_Reset}重置。
 *
 * @param builder 音频编创节点构造器句柄。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，builder为空指针。
 *     <br>AUDIOSUITE_ERROR_MEMORY_ALLOC_FAILED：内存申请失败。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteNodeBuilder_Create(OH_AudioNodeBuilder** builder);

/**
 * @brief 销毁一个音频编创节点构造器。使用完构造器后必须调用此函数进行销毁。
 *
 * @param builder 音频编创节点构造器句柄。通过{@link OH_AudioSuiteNodeBuilder_Create}获取句柄。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，builder为空指针。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteNodeBuilder_Destroy(OH_AudioNodeBuilder* builder);

/**
 * @brief 重置一个音频编创节点构造器，同时将之前使用接口设置参数重置。若需复用构建器创建属性不同的新节点，必须调用此接口清除所有属性（如节点类型等）。
 *
 * @param builder 音频编创节点构造器句柄。通过{@link OH_AudioSuiteNodeBuilder_Create}获取句柄。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，builder为空指针。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteNodeBuilder_Reset(OH_AudioNodeBuilder* builder);

/**
 * @brief 设置当前节点构造器需要构造的节点类型。创建节点时会根据类型验证其他参数，所有节点类型的创建均需设置此属性。
 *
 * @param builder 音频编创节点构造器句柄。通过{@link OH_AudioSuiteNodeBuilder_Create}获取句柄。
 * @param type 节点类型。
 * @return AUDIOSUITE_SUCCESS：配置节点类型成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效，例如，builder为空指针。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteNodeBuilder_SetNodeType(OH_AudioNodeBuilder* builder, OH_AudioNode_Type type);

/**
 * @brief 设置要由构建器创建的音频节点类型。
 *
 * @systemapi
 * @param builder 由{@link OH_AudioSuiteNodeBuilder_Create}创建的引用。
 * @param type 音频系统节点类型。{@链接OH_AudioSuite_SystemNodeType}
 * @return <ul>
 * <li>{@link #AUDIOSUITE_SUCCESS} 配置节点类型成功。</li>
 * <li>202 非系统应用调用了此系统 API。</li>
 * <li>{@link #AUDIOSUITE_ERROR_INVALID_PARAM} 参数无效（如builder为空指针）。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuiteNodeBuilderSystem_SetNodeType(
    OH_AudioNodeBuilder* builder, OH_AudioSuite_SystemNodeType type);

/**
 * @brief 配置输入/输出节点的音频格式。其余节点不配置，且只能在创建节点之前使用。对于输入节点，此函数可使应用指定写入数据的音频格式；
 * <br>对于输出节点，此函数可使应用指定其期望获取数据的音频格式；
 * <br>对于其他类型的节点则不支持调用此函数进行音频格式设置。
 *
 * @param builder 音频编创节点构造器句柄。通过{@link OH_AudioSuiteNodeBuilder_Create}获取句柄。
 * @param audioFormat 音频流格式。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效，例如，builder为空指针。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_FORMAT：audioFormat中的channelCount不支持。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteNodeBuilder_SetFormat(OH_AudioNodeBuilder* builder, OH_AudioFormat audioFormat);

/**
 * @brief 设置节点支持的音频格式。
 *
 * @systemapi
 * @param builder 由{@link OH_AudioSuiteNodeBuilder_Create}创建的引用。
 * @param audioFormat 音频节点格式。
 * @return <ul>
 * <li>{@link #AUDIOSUITE_SUCCESS} 函数执行成功。</li>
 * <li>202 非系统应用调用了此系统 API。</li>
 * <li>{@link #AUDIOSUITE_ERROR_INVALID_PARAM} 参数无效（如builder为空指针）。</li>
 * <li>{@link #AUDIOSUITE_ERROR_UNSUPPORTED_FORMAT} audioFormat中的某个格式不支持。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuiteNodeBuilderSystem_SetFormat(
    OH_AudioNodeBuilder* builder, OH_AudioSuite_SystemNodeFormat audioFormat);

/**
 * @brief 定义输入节点请求数据的回调函数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param userData 用户使用的数据指针。系统调用此回调函数时，将使用{@link OH_AudioSuiteNodeBuilder_SetRequestDataCallback}接口传入的userData。
 * @param audioData 系统提供的内存地址，用于将需要处理的音频数据流写入（需由用户填充）。
 * @param audioDataSize audioData内存地址的字节大小。
 * @param finished 标记audioNode节点需要处理的音频数据流是否已经写入完成。true表示已完成，false表示未完成。
 * @return 写入audioData缓冲区的有效数据长度（单位为字节）。
 *     <br>返回值范围必须在[0, audioDataSize]范围内，如果返回值小于0，系统会将其修改为0，
 *     <br>如果返回值大于audioDataSize，系统会将其修改为audioDataSize。
 * @since 22
 */
typedef int32_t (*OH_InputNode_RequestDataCallback)(
    OH_AudioNode* audioNode, void* userData, void* audioData, int32_t audioDataSize, bool* finished);

/**
 * @brief 配置当前输入节点构造器的写入音频数据回调函数。
 *
 * @param builder 音频编创节点构造器句柄。通过{@link OH_AudioSuiteNodeBuilder_Create}获取句柄。
 * @param callback 写入当前节点音频数据的回调接口。
 * @param userData 用户自定义数据，会在callback函数中将地址传入给用户，如果不使用，可以传入空指针。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：
 *     <br>可能的原因如下：
 *     <br>1. 参数builder为空指针；
 *     <br>2. 参数callback为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteNodeBuilder_SetRequestDataCallback(
    OH_AudioNodeBuilder* builder, OH_InputNode_RequestDataCallback callback, void* userData);

/**
 * @brief 请求元数据的回调函数，仅{@link INPUT_NODE_TYPE_DEFAULT}支持此设置。
 *
 * 每当应用程序或用户调用{@link OH_AudioSuiteEngine_MetaRenderFrame}时，
 * 则会触发一次回调。
 *
 * @systemapi
 * @param audioNode 此回调发生的AudioNode。
 * @param userData 由用户传递的用户数据。
 * @param metaFrame 音频元数据帧结构体指针。
 * @param responseMetaDataSize 应用程序实际写入的元数据的大小，单位是字节。
 * @param finished 此布尔值指示是否已成功写入所有音频数据。
 * @return <ul>
 * <li>写入audio data缓冲区的有效音频数据长度。
 * 返回值必须在【0,metaFrame->AudioDataSize】的范围内。</li>
 * </ul>
 * @since 26.0.0
 */
typedef int32_t (*OH_InputNode_RequestMetaDataCallback)(OH_AudioNode* audioNode, void* userData,
    OH_AudioSuite_MetaFrame* metaFrame, int32_t* responseMetaDataSize, bool* finished);

/**
 * @brief 设置带帧结构的输入节点请求元数据回调。
 * 只有{@link INPUT_NODE_TYPE_DEFAULT}支持该设置。
 * @systemapi
 * @param builder 由{@link OH_AudioSuiteNodeBuilder_Create}创建的引用。
 * @param callback 将写入音频数据和元数据的函数的回调。
 * @param userData 指向将传递给回调函数的应用程序数据结构的指针。
 * @return <ul>
 * <li>{@link #AUDIOSUITE_SUCCESS} 函数执行成功。</li>
 * <li>202 非系统应用调用了此系统 API。</li>
 * <li>{@link #AUDIOSUITE_ERROR_INVALID_PARAM} 参数非法，例如 参数builder为空指针。</li>
 * <li>{@link #AUDIOSUITE_ERROR_TIMEOUT} 操作处理超时。</li>
 * <li>{@link #AUDIOSUITE_ERROR_SYSTEM} 系统发生其他异常。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuiteNodeBuilder_SetRequestMetaDataCallback(
    OH_AudioNodeBuilder* builder, OH_InputNode_RequestMetaDataCallback callback, void* userData);

/**
 * @brief 根据音频编创构造器在音频管线中构造一个音频节点。当执行此函数，系统会基于builder中设置的节点类型校验参数的合法性。
 * <br>应用可以通过返回值确定错误发生的原因。
 *
 * @param audioSuitePipeline 音频编创管线句柄。通过{@link OH_AudioSuiteEngine_CreatePipeline}获取句柄。
 * @param builder 音频编创节点构造器句柄。通过{@link OH_AudioSuiteNodeBuilder_Create}获取句柄。
 * @param audioNode 音频编创节点句柄。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数为空指针或无效值。
 *     <br>可能的原因如下：
 *     <br>1. 参数audioSuitePipeline为空指针；
 *     <br>2. 参数builder为空指针；
 *     <br>3. 参数audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_CREATED_EXCEED_SYSTEM_LIMITS：当构建当前类型的节点数量超过管线限制。
 *     <br>例如，在API version 24之前，创建效果类节点的数量超过5个；在API version 24及以后，创建效果类节点的数量超过15个。
 *     <br>AUDIOSUITE_ERROR_REQUIRED_PARAMETERS_MISSING：构建builder中type类型的节点时缺少必要参数。
 *     <br>例如，builder未设置节点类型。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：当前构造器节点类型为输出节点但设置了回调函数，
 *     <br>或构造器节点类型为效果节点但设置了音频格式或回调函数。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_MEMORY_ALLOC_FAILED：内存申请失败。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_CreateNode(
    OH_AudioSuitePipeline* audioSuitePipeline, OH_AudioNodeBuilder* builder, OH_AudioNode** audioNode);

/**
 * @brief 销毁一个音频编创节点。节点是否可以被销毁取决于它所属管线的状态，如果管线不处于{@link OH_AudioSuite_PipelineState}.AUDIOSUITE_PIPELINE_STOPPED停止状态，
 * 而节点处于管线处理路径中，将销毁失败。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_INVALID_STATE：管线不在停止状态。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_DestroyNode(OH_AudioNode* audioNode);

/**
 * @brief 获取当前节点的效果使能状态。仅效果节点支持获取。
 * <br>若对输入或输出节点调用此接口，将返回AUDIOSUITE_ERROR_INVALID_PARAM错误码。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param bypassStatus 获取当前效果类节点使能状态，false表示未跳过节点处理，true表示已跳过节点处理。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：
 *     <br>参数audioNode或bypassStatus为空指针。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非效果类节点。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_GetNodeBypassStatus(
    OH_AudioNode* audioNode, bool* bypassStatus);

/**
 * @brief 设置当前节点的效果使能状态（仅效果节点支持）。当bypass为true时，效果节点仅透传数据，不进行任何效果处理。
 * <br>当bypass为false时，效果节点进行对应的效果处理。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param bypass 当前效果类节点使能状态。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode为非效果节点。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_BypassEffectNode(OH_AudioNode* audioNode, bool bypass);

/**
 * @brief 配置输入/输出节点的音频格式，在创建节点之后使用，只有输入和输出节点能够设置。输入节点指定音源格式，输出节点指定目标格式。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param audioFormat 音频流格式。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数audioNode或audioFormat为空指针。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode是效果节点。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_FORMAT：（API版本26.0.0新增）参数audioFormat为不支持的格式。
 *     <br>AUDIOSUITE_ERROR_INVALID_STATE：管线不在停止状态。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_SetAudioFormat(OH_AudioNode* audioNode, OH_AudioFormat* audioFormat);

/**
 * @brief 设置输入输出节点的音频格式，指定音频源的音频格式
 * 输入节点，或为输出节点指定目标音频格式。
 * @systemapi
 * @param audioNode {@link OH_AudioSuiteEngine_CreateNode}创建的引用。
 * @param audioFormat 音频格式。
 * @return <ul>
 * <li>{@link #AUDIOSUITE_SUCCESS} 函数执行成功。</li>
 * <li>202 非系统应用调用了此系统 API。</li>
 * <li>{@link #AUDIOSUITE_ERROR_INVALID_PARAM} 参数为空指针获取其他非法值。</li>
 * <li>{@link #AUDIOSUITE_ERROR_NODE_NOT_EXIST} 节点不存在或已被销毁。</li>
 * <li>{@link #AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION} 节点是效果节点。</li>
 * <li>{@link #AUDIOSUITE_ERROR_INVALID_STATE} 管线不在停止状态。</li>
 * <li>{@link #AUDIOSUITE_ERROR_TIMEOUT} 操作处理超时。</li>
 * <li>{@link #AUDIOSUITE_ERROR_SYSTEM} 系统发生其他异常。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuiteEngineSystem_SetAudioFormat(
    OH_AudioNode* audioNode, OH_AudioSuite_SystemNodeFormat* audioFormat);

/**
 * @brief 连接两个节点，数据流走向从sourceAudioNode到destAudioNode。连接节点将改变管道拓扑，可能导致部分数据丢失，建议在引擎停止状态下执行此操作。
 * <br>节点连接顺序：输入节点 -> 效果节点 -> 输出节点。
 *
 * @param sourceAudioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param destAudioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数sourceAudioNode或destAudioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_CONNECT：节点之间不支持连接。
 *     <br>可能的原因如下：
 *     <br>1. 参数sourceAudioNode类型为输出类型节点；
 *     <br>2. 参数destAudioNode类型为输入类型节点；
 *     <br>3. 参数sourceAudioNode和destAudioNode为同一个节点；
 *     <br>4. 参数sourceAudioNode为音源分离类型，但是destAudioNode类型不为输出类型节点；
 *     <br>5. 参数sourceAudioNode和destAudioNode不为同一个管线中的节点；
 *     <br>6. 管线状态为运行状态，但是destAudioNode不为mix类型节点；
 *     <br>7. 管线状态为运行状态，destAudioNode为mix类型节点，但是sourceAudioNode节点未连接输入类型节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_STATE：管线为无效状态。例如，无法找到输出节点。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_ConnectNodes(
    OH_AudioNode* sourceAudioNode, OH_AudioNode* destAudioNode);

/**
 * @brief 断开两个节点的连接。此操作将改变管道拓扑并可能导致数据丢失，建议在引擎停止状态下执行。
 *
 * @param sourceAudioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param destAudioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数sourceAudioNode或destAudioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：不支持操作。
 *     <br>可能的原因如下：
 *     <br>1. 参数sourceAudioNode类型为输出类型节点；
 *     <br>2. 参数destAudioNode为类型为输入类型节点；
 *     <br>3. 参数sourceAudioNode和destAudioNode为同一个节点；
 *     <br>4. 参数sourceAudioNode和destAudioNode不为同一个管线中的节点；
 *     <br>5. 管线状态为运行状态，但是destAudioNode不为mix类型节点；
 *     <br>6. 管线状态为运行状态，destAudioNode为mix类型节点，但是mix节点当前只连接了sourceAudioNode一个输入。
 *     <br>AUDIOSUITE_ERROR_INVALID_STATE：管线为无效状态。例如，无法找到输出节点。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_DisconnectNodes(OH_AudioNode* sourceAudioNode, OH_AudioNode* destAudioNode);

/**
 * @brief 查询当前系统是否支持创建指定的节点类型，避免节点创建失败。调用该接口时不依赖引擎及管线状态，仅跟系统相关，无需创建引擎及管线。
 *
 * @param nodeType 待查的节点类型。
 * @param isSupported 表示是否支持当前节点的创建。false表示未支持，true表示已支持。
 * @return AUDIOSUITE_SUCCESS：查询函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：传入非法参数。
 *     <br>例如，入参nodeType不在OH_AudioNode_Type枚举类型范围内、isSupported为空指针等。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_IsNodeTypeSupported(OH_AudioNode_Type nodeType, bool* isSupported);

/**
 * @brief 设置当前均衡器节点的频段增益效果。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param frequencyBandGains 均衡器节点的均衡参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非均衡器节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：
 *     <br>可能的原因如下：
 *     <br>1. 参数audioNode为空指针；
 *     <br>2. 参数frequencyBandGains每个成员的值范围不在[-10, 10]。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_SetEqualizerFrequencyBandGains(
    OH_AudioNode* audioNode, OH_EqualizerFrequencyBandGains frequencyBandGains);

/**
 * @brief 获取当前均衡器节点的频段增益效果。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param frequencyBandGains 均衡器节点的均衡参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非均衡器节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode或frequencyBandGains为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_GetEqualizerFrequencyBandGains(
    OH_AudioNode* audioNode, OH_EqualizerFrequencyBandGains* frequencyBandGains);

/**
 * @brief 设置声场效果节点的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param soundFieldType 声场效果节点的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非声场节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_SetSoundFieldType(OH_AudioNode* audioNode, OH_SoundFieldType soundFieldType);

/**
 * @brief 获取声场效果节点的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param soundFieldType 声场效果节点的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非soundFieldType节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode或soundFieldType为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_GetSoundFieldType(
    OH_AudioNode* audioNode, OH_SoundFieldType* soundFieldType);

/**
 * @brief 设置环境效果节点的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param environmentType 环境效果节点的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非环境节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_SetEnvironmentType(
    OH_AudioNode* audioNode, OH_EnvironmentType environmentType);

/**
 * @brief 获取环境效果节点的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param environmentType 环境效果节点的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非环境效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode或environmentType为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_GetEnvironmentType(
    OH_AudioNode* audioNode, OH_EnvironmentType* environmentType);

/**
 * @brief 设置声音美化效果节点的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param voiceBeautifierType 声音美化效果节点的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非声音美化效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_SetVoiceBeautifierType(
    OH_AudioNode* audioNode, OH_VoiceBeautifierType voiceBeautifierType);

/**
 * @brief 获取声音美化效果节点的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param voiceBeautifierType 声音美化效果节点的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非声音美化效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。
 *     <br>例如，audioNode或voiceBeautifierType为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 22
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_GetVoiceBeautifierType(
    OH_AudioNode* audioNode, OH_VoiceBeautifierType* voiceBeautifierType);

/**
 * @brief 设置空间渲染效果节点固定摆位模式的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param position 空间渲染效果节点固定摆位模式的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非空间渲染效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 23
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_SetSpaceRenderPositionParams(
    OH_AudioNode* audioNode, OH_AudioSuite_SpaceRenderPositionParams position);

/**
 * @brief 获取空间渲染效果节点固定摆位模式的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param position 空间渲染效果节点固定摆位模式的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非空间渲染效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 23
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_GetSpaceRenderPositionParams(
    OH_AudioNode* audioNode, OH_AudioSuite_SpaceRenderPositionParams* position);

/**
 * @brief 设置空间渲染效果节点旋转模式的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param rotation 空间渲染效果节点旋转模式的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非空间渲染效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 23
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_SetSpaceRenderRotationParams(
    OH_AudioNode* audioNode, OH_AudioSuite_SpaceRenderRotationParams rotation);

/**
 * @brief 获取空间渲染效果节点旋转模式的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param rotation 空间渲染效果节点旋转模式的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非空间渲染效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 23
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_GetSpaceRenderRotationParams(
    OH_AudioNode* audioNode, OH_AudioSuite_SpaceRenderRotationParams* rotation);

/**
 * @brief 设置空间渲染效果节点扩展模式的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param extension 空间渲染效果节点扩展模式的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非空间渲染效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 23
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_SetSpaceRenderExtensionParams(
    OH_AudioNode* audioNode, OH_AudioSuite_SpaceRenderExtensionParams extension);

/**
 * @brief 获取空间渲染效果节点扩展模式的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param extension 空间渲染效果节点扩展模式的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非空间渲染效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 23
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_GetSpaceRenderExtensionParams(
    OH_AudioNode* audioNode, OH_AudioSuite_SpaceRenderExtensionParams* extension);

/**
 * @brief 设置变速变调效果节点的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param speed 变速参数。取值范围为[0.5, 10.0]。
 * @param pitch 变调参数。取值范围为[0.1, 5.0]。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非变速变调效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 23
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_SetTempoAndPitch(OH_AudioNode* audioNode, float speed, float pitch);

/**
 * @brief 获取变速变调效果节点的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param speed 变速参数。取值范围为[0.5, 10.0]。
 * @param pitch 变调参数。取值范围为[0.1, 5.0]。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非变速变调效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 23
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_GetTempoAndPitch(OH_AudioNode* audioNode, float* speed, float* pitch);

/**
 * @brief 设置传统变声节点的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param option 传统变声效果节点的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非传统变声效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 23
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_SetPureVoiceChangeOption(
    OH_AudioNode* audioNode, OH_AudioSuite_PureVoiceChangeOption option);

/**
 * @brief 获取传统变声节点的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param option 传统变声效果节点的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非传统变声效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 23
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_GetPureVoiceChangeOption(
    OH_AudioNode* audioNode, OH_AudioSuite_PureVoiceChangeOption* option);

/**
 * @brief 设置通用变声节点的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param type 通用变声节点的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非通用变声效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 23
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_SetGeneralVoiceChangeType(
    OH_AudioNode* audioNode, OH_AudioSuite_GeneralVoiceChangeType type);

/**
 * @brief 获取通用变声节点的配置参数。
 *
 * @param audioNode 音频编创节点句柄。通过{@link OH_AudioSuiteEngine_CreateNode}获取句柄。
 * @param type 通用变声节点的配置参数。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_NODE_NOT_EXIST：节点不存在或者当前节点已经被销毁。
 *     <br>AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION：audioNode节点类型为非通用变声效果节点。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数无效。例如，audioNode为空指针。
 *     <br>AUDIOSUITE_ERROR_TIMEOUT：操作处理超时。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统发生其他异常。
 * @since 23
 */
OH_AudioSuite_Result OH_AudioSuiteEngine_GetGeneralVoiceChangeType(
    OH_AudioNode* audioNode, OH_AudioSuite_GeneralVoiceChangeType* type);

/**
 * @brief 打印AudioSuite运行时快照。
 *
 * @param audioSuiteEngine 指向需要显示运行时快照的AudioSuiteEngine的指针。
 * @param audioSuitePipeline 指向需要显示运行时快照的AudioSuitePipeline的指针。
 *     <br>如果audioSuitePipeline为空，输出所有管道（引擎下的所有管道/节点）。否则，仅输出此流程和节点的快照。
 * @param fd 文件句柄，表示快照信息存储的位置。
 *     <br>如果fd小于0，快照信息存储在日志中。否则，快照将以追加模式存储在由fd句柄指向的文件中。
 * @return AUDIOSUITE_SUCCESS：函数执行成功。
 *     <br>AUDIOSUITE_ERROR_INVALID_PARAM：参数为nullptr或无效值。
 *     <br>AUDIOSUITE_ERROR_SYSTEM：系统存在其他异常。
 * @since 26.0.0
 */
OH_AudioSuite_Result OH_AudioSuite_PrintInfo(
    OH_AudioSuiteEngine* audioSuiteEngine, OH_AudioSuitePipeline* audioSuitePipeline, int fd);

/**
 * @brief 设置系统节点的参数。
 * @systemapi
 * @param audioNode {@link OH_AudioSuiteEngine_CreateNode}创建的引用。
 * @param param 参数缓冲区。
 * @param paramSize 参数缓冲区大小。
 * @return <ul>
 * <li>{@link #AUDIOSUITE_SUCCESS} 函数执行成功。</li>
 * <li>202 非系统应用调用了此系统 API。</li>
 * <li>{@link #AUDIOSUITE_ERROR_NODE_NOT_EXIST} 节点不存在或已被销毁。</li>
 * <li>{@link #AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION} 节点非系统节点。</li>
 * <li>{@link #AUDIOSUITE_ERROR_INVALID_PARAM} 参数为空指针或其他非法值。</li>
 * <li>{@link #AUDIOSUITE_ERROR_TIMEOUT} 操作处理超时。</li>
 * <li>{@link #AUDIOSUITE_ERROR_SYSTEM} 系统发生其他异常。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuiteEngineSystem_SetNodeParam(
    OH_AudioNode* audioNode, uint8_t* param, uint32_t paramSize);

/**
 * @brief 获取系统节点的参数。
 * @systemapi
 * @param audioNode {@link OH_AudioSuiteEngine_CreateNode}创建的引用。
 * @param param 参数缓冲区。
 * @param paramSize 参数缓冲区大小。
 * @return <ul>
 * <li>{@link #AUDIOSUITE_SUCCESS} 函数执行成功。</li>
 * <li>202 非系统应用调用了此系统 API。</li>
 * <li>{@link #AUDIOSUITE_ERROR_NODE_NOT_EXIST} 音频节点不存在或已被销毁。</li>
 * <li>{@link #AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION} 节点非系统节点。</li>
 * <li>{@link #AUDIOSUITE_ERROR_INVALID_PARAM} 参数为空指针或其他非法值。</li>
 * <li>{@link #AUDIOSUITE_ERROR_TIMEOUT} 操作处理超时。</li>
 * <li>{@link #AUDIOSUITE_ERROR_SYSTEM} 系统发生其他异常。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuiteEngineSystem_GetNodeParam(
    OH_AudioNode* audioNode, uint8_t* param, uint32_t paramSize);

/**
 * @brief 获取系统节点的输入和输出帧大小。
 * @systemapi
 * @param audioNode {@link OH_AudioSuiteEngine_CreateNode}创建的引用。
 * @param inSize 输入帧大小，单位为字节。
 * @param outSize 输出帧大小，单位为字节。
 * @return <ul>
 * <li>{@link #AUDIOSUITE_SUCCESS} 函数执行成功。</li>
 * <li>202 非系统应用调用了此系统 API。</li>
 * <li>{@link #AUDIOSUITE_ERROR_NODE_NOT_EXIST} 音频节点不存在或已被销毁。</li>
 * <li>{@link #AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION} 节点非系统节点。</li>
 * <li>{@link #AUDIOSUITE_ERROR_INVALID_PARAM} 参数为空指针或其他非法值。</li>
 * <li>{@link #AUDIOSUITE_ERROR_TIMEOUT} 操作处理超时。</li>
 * <li>{@link #AUDIOSUITE_ERROR_SYSTEM} 系统发生其他异常。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuiteEngineSystem_GetNodeInOutSize(
    OH_AudioNode* audioNode, uint32_t* inSize, uint32_t* outSize);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_AUDIO_SUITE_ENGINE_H
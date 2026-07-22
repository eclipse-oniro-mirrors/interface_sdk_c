/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup AudioAccessoryInputStreamManager
 * @{
 *
 * @brief Provide audio accessory input stream manager C interface.
 *
 * @since 26.0.0
 */

/**
 * @file native_audio_accessory_input_stream_manager.h
 *
 * @brief Declare audio accessory input stream manager related interfaces.
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 26.0.0
 */

#ifndef NATIVE_AUDIO_ACCESSORY_INPUT_STREAM_MANAGER_H
#define NATIVE_AUDIO_ACCESSORY_INPUT_STREAM_MANAGER_H

#include <stdbool.h>
#include "native_audio_accessory_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 在音频附件上打开输入流的回调。
 *
 * <b>When Called:</b>音频框架在
 * 应用程序从该音频附件请求音频捕获。
 * 框架将流的音频流信息传递给
 * 打开，这样附件就可以准备相应的数据路径了。
 *
 * <b>Usage Requirements:</b>在此回调中，您必须调用
 * {@链接OH_AudioAccessoryInputStreamManager_RegisterStartCallback}，
 * {@链接OH_AudioAccessoryInputStreamManager_RegisterStopCallback}，
 * {@链接OH_AudioAccessoryInputStreamManager_RegisterReleaseCallback}，
 * {@链接OH_AudioAccessoryInputStreamManager_RegisterLatencyCallback}，以及
 * {@链接OH_AudioAccessoryInputStreamManager_RegisterFramePositionCallback}到
 * 注册所需的流回调。这是唯一一次回电
 * 允许注册。
 *
 * @param accessory 打开流的音频附件。
 * @param stream 对新创建的输入流的引用。
 * 使用此句柄通过Register...Callback注册回调。
 * @param streamInfo 码流的音频码流信息指针。
 * 正在打开。该参数用于描述请求的码流格式。
 * 可以由附件用于配置其数据路径。
 * @return <ul>
 * <li>`true`如果接受流。</li>
 * <li>`false`否则。</li>
 * </ul>
 * @see OH_AudioAccessoryInputStreamManager_RegisterStartCallback
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessory_OpenInputStreamCallback)(
    OH_AudioAccessory *accessory,
    OH_AudioAccessoryInputStream *stream,
    OH_AudioStreamInfo *streamInfo);

/**
 * @brief 流开始事件的回调。
 *
 * <b>When Called:</b>流成功启动并就绪后
 * 来接收音频数据。在此回调返回后，您可以调用Write()
 * 来发送音频数据。
 *
 * @param accessory 拥有此流的音频配件。
 * @param stream 对启动的输入流的引用。
 * @return <ul>
 * <li>`true`如果成功处理开始事件</li>
 * <li>`false`否则。</li>
 * </ul>
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessoryInputStream_StartCallback)(
    OH_AudioAccessory *accessory, OH_AudioAccessoryInputStream *stream);

/**
 * @brief 流停止事件的回调。
 *
 * <b>When Called:</b>停止流后。在此回调之后
 * 返回，则必须停止调用Write()。流句柄仍然存在
 * 有效，可以再次启动。
 *
 * @param accessory 拥有此流的音频配件。
 * @param stream 对已停止的输入流的引用。
 * @return <ul>
 * <li>`true`如果停止事件处理成功</li>
 * <li>`false`否则。</li>
 * </ul>
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessoryInputStream_StopCallback)(
    OH_AudioAccessory *accessory, OH_AudioAccessoryInputStream *stream);

/**
 * @brief 流释放事件回调。
 *
 * <b>When Called:</b>流释放时。这一直都是
 * 流的最后一个回调。此回调返回后，流
 * 句柄不再有效，不得使用。
 *
 * @param accessory 拥有此流的音频配件。
 * @param stream 对被释放的输入流的引用。
 * @return <ul>
 * <li>`true`如果释放事件处理成功</li>
 * <li>`false`否则。</li>
 * </ul>
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessoryInputStream_ReleaseCallback)(
    OH_AudioAccessory *accessory, OH_AudioAccessoryInputStream *stream);

/**
 * @brief 查询流的当前时延回调。
 *
 * <b>When Called:</b>框架何时需要当前延迟值
 * 由辅助流报告。
 *
 * @param accessory 拥有此流的音频配件。
 * @param stream 对输入流的引用。
 * @param latency 输出参数。返回延迟（以毫秒为单位）。
 * @return <ul>
 * <li>`true`如果成功获取延迟</li>
 * <li>`false`否则。</li>
 * </ul>
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessoryInputStream_GetLatencyCallback)(
    OH_AudioAccessory *accessory,
    OH_AudioAccessoryInputStream *stream,
    int32_t *latency);

/**
 * @brief 查询码流当前帧位置回调。
 *
 * <b>When Called:</b>框架何时需要当前捕获位置
 * 由辅助流报告。
 *
 * @param accessory 拥有此流的音频配件。
 * @param stream 对输入流的引用。
 * @param framePosition 输出参数。返回音频的累计数量
 * 自该输入最近一次成功启动以来捕获的帧
 * 流。
 * @param timestamp 输出参数。返回捕获时间戳
 * 对应{@p framePosition}上报的帧位置。
 * 时间戳必须使用{@link CLOCK_MONOTONIC}时基，并且是
 * 以纳秒表示。它表示单调时钟时间在
 * 捕获了{@p framePosition}所标识的帧。
 * @return <ul>
 * <li>`true`如果成功获取帧位置</li>
 * <li>`false`否则。</li>
 * </ul>
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessoryInputStream_GetFramePositionCallback)(
    OH_AudioAccessory *accessory, OH_AudioAccessoryInputStream *stream,
    int64_t *framePosition, int64_t *timestamp);

/**
 * @brief 注册流启动事件的回调。
 *
 * <b>CRITICAL: Registration Timing Constraint</b>
 *
 * 此函数必须仅在执行
 * {@链接OH_AudioAccessory_OpenInputStreamCallback}。叫这个
 * 在任何其他时间执行的函数都将导致{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}。
 *
 * <b>Requirement:</b>此回调是强制的。如果未注册，
 * 框架将拒绝流创建并触发清理。
 *
 * @param stream 输入流句柄指针。
 * @param callback 回调函数指针。不能为空。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * 如果参数为空，则<li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}。</li>
 * 如果在{@link OH_AudioAccessory_OpenInputStreamCallback}外部调用，则释放流。<li>{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryInputStreamManager_RegisterStartCallback(
    OH_AudioAccessoryInputStream *stream,
    OH_AudioAccessoryInputStream_StartCallback callback);

/**
 * @brief 注册流停止事件回调。
 *
 * <b>CRITICAL: Registration Timing Constraint</b>
 *
 * 此函数必须仅在执行
 * {@链接OH_AudioAccessory_OpenInputStreamCallback}。叫这个
 * 在任何其他时间执行的函数都将导致{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}。
 *
 * <b>Requirement:</b>此回调是强制的。如果未注册，
 * 框架将拒绝流创建并触发清理。
 *
 * @param stream 输入流句柄指针。
 * @param callback 回调函数指针。不能为空。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * 如果参数为空，则<li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}。</li>
 * 如果在{@link OH_AudioAccessory_OpenInputStreamCallback}外部调用，则释放流。<li>{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryInputStreamManager_RegisterStopCallback(
    OH_AudioAccessoryInputStream *stream,
    OH_AudioAccessoryInputStream_StopCallback callback);

/**
 * @brief 注册流释放事件回调。
 *
 * <b>CRITICAL: Registration Timing Constraint</b>
 *
 * 此函数必须仅在执行
 * {@链接OH_AudioAccessory_OpenInputStreamCallback}。叫这个
 * 在任何其他时间执行的函数都将导致{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}。
 *
 * <b>Requirement:</b>此回调是强制的。如果未注册，
 * 框架将拒绝流创建并触发清理。
 *
 * @param stream 输入流句柄指针。
 * @param callback 回调函数指针。不能为空。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * 如果参数为空，则<li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}。</li>
 * 如果在{@link OH_AudioAccessory_OpenInputStreamCallback}外部调用，则释放流。<li>{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryInputStreamManager_RegisterReleaseCallback(
    OH_AudioAccessoryInputStream *stream,
    OH_AudioAccessoryInputStream_ReleaseCallback callback);

/**
 * @brief 注册码流时延查询回调。
 *
 * <b>CRITICAL: Registration Timing Constraint</b>
 *
 * 此函数必须仅在执行
 * {@链接OH_AudioAccessory_OpenInputStreamCallback}。叫这个
 * 在任何其他时间执行的函数都将导致{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}。
 *
 * <b>Requirement:</b>此回调是强制的。如果未注册，
 * 框架将拒绝流创建并触发清理。
 *
 * @param stream 输入流句柄指针。
 * @param callback 回调函数指针。不能为空。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * 如果参数为空，则<li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}。</li>
 * 如果在{@link OH_AudioAccessory_OpenInputStreamCallback}外部调用，则释放流。<li>{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryInputStreamManager_RegisterLatencyCallback(
    OH_AudioAccessoryInputStream *stream,
    OH_AudioAccessoryInputStream_GetLatencyCallback callback);

/**
 * @brief 注册码流帧位置查询回调。
 *
 * <b>CRITICAL: Registration Timing Constraint</b>
 *
 * 此函数必须仅在执行
 * {@链接OH_AudioAccessory_OpenInputStreamCallback}。叫这个
 * 在任何其他时间执行的函数都将导致{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}。
 *
 * <b>Requirement:</b>此回调是强制的。如果未注册，
 * 框架将拒绝流创建并触发清理。
 *
 * @param stream 输入流句柄指针。
 * @param callback 回调函数指针。不能为空。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * 如果参数为空，则<li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}。</li>
 * 如果在{@link OH_AudioAccessory_OpenInputStreamCallback}外部调用，则释放流。<li>{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryInputStreamManager_RegisterFramePositionCallback(
    OH_AudioAccessoryInputStream *stream,
    OH_AudioAccessoryInputStream_GetFramePositionCallback callback);

/**
 * @brief 将音频数据写入音频附件输入流。
 *
 * 这是一个阻塞接口。函数被调用后，会阻塞，直到
 * 整帧写入成功或出错。每次调用都必须
 * 写入20毫秒的音频数据。调用者必须确保dataSize
 * 匹配当前流下20 ms对应的字节数
 * 配置。如果dataSize不匹配20 ms的音频数据，则此
 * 函数返回{@link AudioCOMMON_RESULT_ERROR_FRAME_LENGTH_MISMATCH}。
 * 调用方必须以20 ms的节奏调用此函数。也就是说，每次调用
 * 必须提交20 ms的音频数据，并且间隔两个连续
 * 呼叫也必须是20 ms。
 * 如果流缓冲区当前没有足够的可写空间供
 * 整个框架，此函数会阻塞，直到有足够的空间可用或
 * 发生错误。此接口不支持部分帧写入。如果
 * 最后一帧的音频数据少于20毫秒，主叫方可能会丢弃
 * 该帧或在调用此函数之前用0填充到20 ms。
 *
 * @param stream 输入流句柄指针。
 * @param data 指向音频数据缓冲区的指针。不能为空。
 * @param dataSize 音频数据的大小，以字节为单位。必须大于0。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * 如果参数为空，则<li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_FRAME_LENGTH_MISMATCH}如果dataSize不对应当前流配置下的20 ms音频数据。</li>
 * <li>{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}如果流未启动或所需的流回调未完全注册。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM}如果音频服务器进程死掉。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryInputStreamManager_Write(
    OH_AudioAccessoryInputStream *stream,
    const uint8_t *data,
    uint32_t dataSize);

/**
 * @brief 获取音频配件输入码流buffer可写大小。
 *
 * 调用方可以使用此函数来探测当前缓冲区的可用性
 * 在调用{@link OH_AudioAccessoryInputStreamManager_Write}之前。返回的
 * 可写大小仅反映当前状态，并可能立即更改
 * 函数返回后。
 *
 * @param stream 输入流句柄指针。
 * @param writableSize 输出参数。返回可以写入的字节数。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * 如果参数为空，则<li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}。</li>
 * <li>{@link AudioCommon_RESULT_ERROR_ILAL_STATE}如果流被释放。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryInputStreamManager_GetWritableSize(
    OH_AudioAccessoryInputStream *stream,
    uint32_t *writableSize);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // NATIVE_AUDIO_ACCESSORY_INPUT_STREAM_MANAGER_H
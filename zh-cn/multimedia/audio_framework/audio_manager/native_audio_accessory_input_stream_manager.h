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
 * @addtogroup OHAudio
 * @{
 *
 * @brief 提供音频模块C接口定义。
 *
 * @syscap SystemCapability.Multimedia.Audio.Core
 *
 * @since 26.0.0
 */

/**
 * @file native_audio_accessory_input_stream_manager.h
 *
 * @brief 声明音频配件输入流管理器相关接口。\n
 *
 * 该文件接口用于管理音频配件的输入音频流，包括回调注册、数据写入和缓冲区查询等功能。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @include <ohaudio/native_audio_accessory_input_stream_manager.h>
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
 * @brief 音频配件打开输入流的回调函数。
 *
 * <b>触发时机：</b>当应用请求从该音频配件采集音频时，音频框架调用此回调。
 * 框架传递正在打开的音频流信息，以便配件准备相应的数据通路。
 *
 * <b>使用要求：</b>在此回调中，必须调用
 * {@link OH_AudioAccessoryInputStreamManager_RegisterStartCallback}、
 * {@link OH_AudioAccessoryInputStreamManager_RegisterStopCallback}、
 * {@link OH_AudioAccessoryInputStreamManager_RegisterReleaseCallback}、
 * {@link OH_AudioAccessoryInputStreamManager_RegisterLatencyCallback}
 * 和{@link OH_AudioAccessoryInputStreamManager_RegisterFramePositionCallback}
 * 注册必需的流回调。此回调是唯一允许注册回调的时机。
 *
 * @param accessory 打开流的音频配件。
 * @param stream 新创建的输入流引用。使用此句柄通过Register...Callback注册回调。
 * @param streamInfo 正在打开的流的音频流信息指针。此参数描述请求的流格式，
 *     配件可使用此信息配置数据通路。
 * @return true：流被接受。\n
 *         false：流被拒绝。
 * @see OH_AudioAccessoryInputStreamManager_RegisterStartCallback
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessory_OpenInputStreamCallback)(
    OH_AudioAccessory *accessory,
    OH_AudioAccessoryInputStream *stream,
    OH_AudioStreamInfo *streamInfo);

/**
 * @brief 输入流启动事件回调函数。
 *
 * <b>触发时机：</b>流成功启动并准备好接收音频数据后触发。
 * 此回调返回后，可以调用Write()发送音频数据。
 *
 * @param accessory 拥有该流的音频配件。
 * @param stream 已启动的输入流引用。
 * @return true：启动事件处理成功。\n
 *         false：启动事件处理失败。
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessoryInputStream_StartCallback)(
    OH_AudioAccessory *accessory, OH_AudioAccessoryInputStream *stream);

/**
 * @brief 输入流停止事件回调函数。
 *
 * <b>触发时机：</b>流停止后触发。此回调返回后，必须停止调用Write()。
 * 流句柄仍然有效，可以再次启动。
 *
 * @param accessory 拥有该流的音频配件。
 * @param stream 已停止的输入流引用。
 * @return true：停止事件处理成功。\n
 *         false：停止事件处理失败。
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessoryInputStream_StopCallback)(
    OH_AudioAccessory *accessory, OH_AudioAccessoryInputStream *stream);

/**
 * @brief 输入流释放事件回调函数。
 *
 * <b>触发时机：</b>流正在被释放时触发。这是流的最后一个回调。
 * 此回调返回后，流句柄不再有效，不得继续使用。
 *
 * @param accessory 拥有该流的音频配件。
 * @param stream 已释放的输入流引用。
 * @return true：释放事件处理成功。\n
 *         false：释放事件处理失败。
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessoryInputStream_ReleaseCallback)(
    OH_AudioAccessory *accessory, OH_AudioAccessoryInputStream *stream);

/**
 * @brief 查询输入流当前时延的回调函数。
 *
 * <b>触发时机：</b>当框架需要获取配件流上报的当前时延值时触发。
 *
 * @param accessory 拥有该流的音频配件。
 * @param stream 输入流引用。
 * @param latency 输出参数，返回时延值，单位为毫秒。
 * @return true：成功获取时延。\n
 *         false：获取时延失败。
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessoryInputStream_GetLatencyCallback)(
    OH_AudioAccessory *accessory,
    OH_AudioAccessoryInputStream *stream,
    int32_t *latency);

/**
 * @brief 查询输入流当前帧位置的回调函数。
 *
 * <b>触发时机：</b>当框架需要获取配件流上报的当前采集位置时触发。
 *
 * @param accessory 拥有该流的音频配件。
 * @param stream 输入流引用。
 * @param framePosition 输出参数，返回自该输入流最近一次成功启动以来累计采集的音频帧数。
 * @param timestamp 输出参数，返回与{@p framePosition}对应的采集时间戳。
 *     时间戳必须使用{@link CLOCK_MONOTONIC}时间基准，以纳秒为单位，
 *     表示{@p framePosition}所标识帧被采集时的单调时钟时间。
 * @return true：成功获取帧位置。\n
 *         false：获取帧位置失败。
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessoryInputStream_GetFramePositionCallback)(
    OH_AudioAccessory *accessory, OH_AudioAccessoryInputStream *stream,
    int64_t *framePosition, int64_t *timestamp);

/**
 * @brief 注册输入流启动事件回调函数。\n
 *
 * <b>关键约束：注册时机限制</b>\n
 *
 * 此函数必须在{@link OH_AudioAccessory_OpenInputStreamCallback}执行期间调用。
 * 在其他任何时间调用此函数将返回{@link AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE}。
 *
 * <b>要求：</b>此回调为必需回调。如果未注册，框架将拒绝流创建并触发清理。
 *
 * @param stream 输入流句柄指针。
 * @param callback 回调函数指针，不可为空。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数为空。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：在{@link OH_AudioAccessory_OpenInputStreamCallback}外部调用或流已释放。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryInputStreamManager_RegisterStartCallback(
    OH_AudioAccessoryInputStream *stream,
    OH_AudioAccessoryInputStream_StartCallback callback);

/**
 * @brief 注册输入流停止事件回调函数。\n
 *
 * <b>关键约束：注册时机限制</b>\n
 *
 * 此函数必须在{@link OH_AudioAccessory_OpenInputStreamCallback}执行期间调用。
 * 在其他任何时间调用此函数将返回{@link AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE}。
 *
 * <b>要求：</b>此回调为必需回调。如果未注册，框架将拒绝流创建并触发清理。
 *
 * @param stream 输入流句柄指针。
 * @param callback 回调函数指针，不可为空。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数为空。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：在{@link OH_AudioAccessory_OpenInputStreamCallback}外部调用或流已释放。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryInputStreamManager_RegisterStopCallback(
    OH_AudioAccessoryInputStream *stream,
    OH_AudioAccessoryInputStream_StopCallback callback);

/**
 * @brief 注册输入流释放事件回调函数。\n
 *
 * <b>关键约束：注册时机限制</b>\n
 *
 * 此函数必须在{@link OH_AudioAccessory_OpenInputStreamCallback}执行期间调用。
 * 在其他任何时间调用此函数将返回{@link AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE}。
 *
 * <b>要求：</b>此回调为必需回调。如果未注册，框架将拒绝流创建并触发清理。
 *
 * @param stream 输入流句柄指针。
 * @param callback 回调函数指针，不可为空。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数为空。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：在{@link OH_AudioAccessory_OpenInputStreamCallback}外部调用或流已释放。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryInputStreamManager_RegisterReleaseCallback(
    OH_AudioAccessoryInputStream *stream,
    OH_AudioAccessoryInputStream_ReleaseCallback callback);

/**
 * @brief 注册输入流时延查询回调函数。\n
 *
 * <b>关键约束：注册时机限制</b>\n
 *
 * 此函数必须在{@link OH_AudioAccessory_OpenInputStreamCallback}执行期间调用。
 * 在其他任何时间调用此函数将返回{@link AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE}。
 *
 * <b>要求：</b>此回调为必需回调。如果未注册，框架将拒绝流创建并触发清理。
 *
 * @param stream 输入流句柄指针。
 * @param callback 回调函数指针，不可为空。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数为空。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：在{@link OH_AudioAccessory_OpenInputStreamCallback}外部调用或流已释放。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryInputStreamManager_RegisterLatencyCallback(
    OH_AudioAccessoryInputStream *stream,
    OH_AudioAccessoryInputStream_GetLatencyCallback callback);

/**
 * @brief 注册输入流帧位置查询回调函数。\n
 *
 * <b>关键约束：注册时机限制</b>\n
 *
 * 此函数必须在{@link OH_AudioAccessory_OpenInputStreamCallback}执行期间调用。
 * 在其他任何时间调用此函数将返回{@link AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE}。
 *
 * <b>要求：</b>此回调为必需回调。如果未注册，框架将拒绝流创建并触发清理。
 *
 * @param stream 输入流句柄指针。
 * @param callback 回调函数指针，不可为空。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数为空。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：在{@link OH_AudioAccessory_OpenInputStreamCallback}外部调用或流已释放。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryInputStreamManager_RegisterFramePositionCallback(
    OH_AudioAccessoryInputStream *stream,
    OH_AudioAccessoryInputStream_GetFramePositionCallback callback);

/**
 * @brief 向音频配件输入流写入音频数据。\n
 *
 * 此接口为阻塞接口。调用后，函数将阻塞直到整帧数据写入成功或发生错误。
 * 每次调用必须写入恰好20ms的音频数据。调用方必须确保dataSize与当前流配置下
 * 20ms对应的字节数一致。如果dataSize不匹配20ms的音频数据，
 * 本函数返回{@link AUDIOCOMMON_RESULT_ERROR_FRAME_LENGTH_MISMATCH}。
 * 调用方必须以20ms的节奏调用此函数，即每次调用提交20ms音频数据，
 * 连续两次调用之间的间隔也必须为20ms。\n
 * 如果流缓冲区当前没有足够的可写空间容纳整帧数据，本函数将阻塞直到有足够空间或发生错误。
 * 此接口不支持部分帧写入。如果最后一帧不足20ms的音频数据，
 * 调用方可以丢弃该帧或用零填充至20ms后再调用本函数。\n
 *
 * <b>调用上下文与并发：</b>\n
 *
 * 本函数对同一流不可重入。建议调用方仅使用一个线程串行地向同一流写入音频数据。
 * 如果本函数与同一流的停止或释放回调并发调用，当停止或释放操作先于本函数获取锁完成时，
 * 本函数返回{@link AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE}。
 *
 * @param stream 输入流句柄指针。
 * @param data 音频数据缓冲区指针，不可为空。
 * @param dataSize 音频数据大小，单位为字节，必须大于0。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数为空。\n
 *         AUDIOCOMMON_RESULT_ERROR_FRAME_LENGTH_MISMATCH：dataSize与当前流配置下20ms音频数据不对应。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：流未启动或必需的流回调未全部注册。\n
 *         AUDIOCOMMON_RESULT_ERROR_SYSTEM：音频服务进程死亡。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryInputStreamManager_Write(
    OH_AudioAccessoryInputStream *stream,
    const uint8_t *data,
    uint32_t dataSize);

/**
 * @brief 获取音频配件输入流缓冲区的可写大小。\n
 *
 * 调用方可使用此函数在调用{@link OH_AudioAccessoryInputStreamManager_Write}之前探测当前缓冲区可用空间。
 * 返回的可写大小仅反映当前状态，函数返回后可能立即发生变化。
 *
 * @param stream 输入流句柄指针。
 * @param writableSize 输出参数，返回可写入的字节数。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数为空。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：流已释放。
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

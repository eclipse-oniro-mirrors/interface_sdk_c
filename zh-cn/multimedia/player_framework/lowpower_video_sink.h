/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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
 * @addtogroup LowPowerVideoSink
 * @{
 *
 * @brief The LowPowerVideoSink sub module provides variables, properties, and functions
 * for lowpower video sink.
 *
 * @since 20
 */
/**
 * @file lowpower_video_sink.h
 *
 * @brief 定义LowPowerVideoSink接口。使用LowPowerVideoSink提供的Native API进行视频通路的低功耗播放。
 * 
 * @library liblowpower_avsink.so
 * @kit MediaKit
 * @syscap SystemCapability.Multimedia.Media.LowPowerAVSink
 * @since 20
 */

#ifndef NATIVE_LOWPOWER_VIDEO_SINK_H
#define NATIVE_LOWPOWER_VIDEO_SINK_H

#include <stdint.h>
#include "native_averrors.h"
#include "native_avformat.h"
#include "lowpower_avsink_base.h"
#include "lowpower_video_sink_base.h"
#include "lowpower_audio_sink_base.h"
#include "native_window/external_window.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建低功耗LowPowerVideoSink。
 * 
 * @param mime mime type description string, refer to {@link AVCODEC_MIME_TYPE}
 * @return 如果创建成功返回指向OH_LowPowerVideoSink实例的指针，否则返回空指针。
 * @since 20
 */
OH_LowPowerVideoSink* OH_LowPowerVideoSink_CreateByMime(const char* mime);

/**
 * @brief 配置LowPowerVideoSink，需要在{@link OH_LowPowerVideoSink_Prepare}前完成。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param format A pointer to an OH_AVFormat to give the description of the video track to be decoded,
 * key of format refer to lowpower_avsink_base.h
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_UNSUPPORT：不支持的格式。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Configure(OH_LowPowerVideoSink* sink, const OH_AVFormat* format);

/**
 * @brief 为LowPowerVideoSink设置参数，支持{@link OH_LowPowerVideoSink_Prepare}后动态设置。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param format pointer to an OH_AVFormat instance, key of format refer to lowpower_avsink_base.h
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_UNSUPPORT：不支持的格式。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_SetParameter(OH_LowPowerVideoSink* sink, const OH_AVFormat* format);

/**
 * @brief 获取LowPowerVideoSink的相关参数。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param format pointer to an OH_AVFormat instance, key of format refer to lowpower_avsink_base.h
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_GetParameter(OH_LowPowerVideoSink* sink, OH_AVFormat* format);

/**
 * @brief 为LowPowerVideoSink设置渲染画面窗口。 需要在{@link OH_LowPowerVideoSink_Prepare}前完成。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param surface A pointer to a OHNativeWindow instance, see {@link OHNativeWindow}
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_SetVideoSurface(OH_LowPowerVideoSink* sink, const OHNativeWindow* surface);

/**
 * @brief 开始LowPowerVideoSink准备，需要在{@link OH_LowPowerVideoSink_SetSyncAudioSink}之后调用。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_UNSUPPORT：不支持的格式。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Prepare(OH_LowPowerVideoSink* sink);

/**
 * @brief 开始LowPowerVideoSink解码，在{@link OH_LowPowerVideoSink_Prepare}后或非播放中{@link OH_LowPowerVideoSink_SetTargetStartFrame}
 * 后调用。
 * 启动成功后，LowPowerVideoSink将开始上报{@link OH_LowPowerVideoSink_OnDataNeeded}事件。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_UNSUPPORT：不支持的格式。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_StartDecoder(OH_LowPowerVideoSink* sink);

/**
 * @brief 渲染LowPowerVideoSink解码出的第一帧，在{@link OH_LowPowerVideoSink_StartDecoder}之后调用。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_RenderFirstFrame(OH_LowPowerVideoSink* sink);

/**
 * @brief 开始LowPowerVideoSink渲染，在{@link OH_LowPowerVideoSink_StartDecoder}之后调用。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_UNSUPPORT：不支持的格式。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_StartRenderer(OH_LowPowerVideoSink* sink);

/**
 * @brief 暂停LowPowerVideoSink，在{@link OH_LowPowerVideoSink_StartRenderer}或{@link OH_LowPowerVideoSink_Resume}后调用。
 * 暂停成功后，LowPowerVideoSink将暂停{@link OH_LowPowerVideoSink_OnDataNeeded}事件的上报。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Pause(OH_LowPowerVideoSink* sink);

/**
 * @brief 恢复LowPowerVideoSink，在{@link OH_LowPowerVideoSink_Pause}后调用。
 * 恢复成功后，LowPowerVideoSink将恢复{@link OH_LowPowerVideoSink_OnDataNeeded}事件的上报。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSinkinstance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Resume(OH_LowPowerVideoSink* sink);

/**
 * @brief 清除LowPowerVideoSink中所有解码器和渲染缓存的输入输出数据。
 * 此接口不建议在{@link OH_LowPowerVideoSink_StartRenderer}或{@link OH_LowPowerVideoSink_Resume}之后调用。
 * 需要注意的是，如果编解码器之前已输入数据，则需要重新输入编解码器数据。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Flush(OH_LowPowerVideoSink* sink);

/**
 * @brief 停止LowPowerVideoSink。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Stop(OH_LowPowerVideoSink* sink);

/**
 * @brief 重置LowPowerVideoSink。
 * 如果要重新使用该实例，需要调用{@link OH_LowPowerVideoSink_Configure}完成配置。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Reset(OH_LowPowerVideoSink* sink);

/**
 * @brief 清理解码器内部资源，销毁LowPowerVideoSink实例。不能重复销毁。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Destroy(OH_LowPowerVideoSink* sink);

/**
 * @brief LowPowerVideoSink设置用于音画同步的OH_LowPowerAudioSink。
 * 
 * @param videoSink Pointer to an OH_LowPowerVideoSink instance
 * @param audioSink Pointer to an OH_LowPowerAudioSink instance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_SetSyncAudioSink(
    OH_LowPowerVideoSink* videoSink, OH_LowPowerAudioSink* audioSink);

/**
 * @brief 为LowPowerVideoSink设置目标渲染帧。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param framePts target video frame pts, in microseconds
 * @param onTargetArrived OH_LowPowerVideoSink_OnTargetArrived func,
 * will be called once, refer to {@link OH_LowPowerVideoSink_OnTargetArrived}
 * @param timeoutMs if wait first frame over timeoutMs, onTargetArrived will be called directly,
 * in milliseconds.
 * @param userData User specific data
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_SetTargetStartFrame(
    OH_LowPowerVideoSink* sink,
    const int64_t framePts,
    OH_LowPowerVideoSink_OnTargetArrived onTargetArrived,
    const int64_t timeoutMs,
    void* userData);

/**
 * @brief 为LowPowerVideoSink设置播放倍速。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param speed Indicates the value of the playback rate.
 * The current version is valid in the range of 0.25-4.0
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_SetPlaybackSpeed(OH_LowPowerVideoSink* sink, const float speed);

/**
 * @brief 给LowPowerVideoSink输入buffer。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param samples Pointer to an OH_AVSamplesBuffer instance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_ReturnSamples(OH_LowPowerVideoSink* sink, OH_AVSamplesBuffer* samples);

/**
 * @brief 为LowPowerVideoSink注册回调。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_RegisterCallback(OH_LowPowerVideoSink* sink, OH_LowPowerVideoSinkCallback* callback);

/**
 * @brief 创建OH_LowPowerVideoSinkCallback。
 * 
 * @return 返回指向OH_LowPowerVideoSinkCallback实例的指针。如果内存不足，则返回nullptr。
 * @since 20
 */
OH_LowPowerVideoSinkCallback* OH_LowPowerVideoSinkCallback_Create(void);

/**
 * @brief 销毁OH_LowPowerVideoSinkCallback对象。
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_Destroy(OH_LowPowerVideoSinkCallback* callback);

/**
 * @brief 为LowPowerVideoSinkCallback设置需要数据监听。
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @param onDataNeeded OH_LowPowerVideoSink_OnDataNeeded function,
 * refer to {@link OH_LowPowerVideoSink_OnDataNeeded}
 * @param userData User specific data
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_SetDataNeededListener(
    OH_LowPowerVideoSinkCallback* callback, OH_LowPowerVideoSink_OnDataNeeded onDataNeeded,void* userData);

/**
 * @brief 为LowPowerVideoSinkCallback回调设置错误监听。
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @param onError OH_LowPowerVideoSink_OnError function,
 * refer to {@link OH_LowPowerVideoSink_OnError}
 * @param userData User specific data
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_SetErrorListener(
    OH_LowPowerVideoSinkCallback* callback, OH_LowPowerVideoSink_OnError onError, void* userData);

/**
 * @brief 为LowPowerVideoSinkCallback回调设置开始渲染监听。
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @param onRenderStarted OH_LowPowerVideoSink_OnRenderStarted function,
 * refer to {@link OH_LowPowerVideoSink_OnRenderStarted}
 * @param userData User specific data
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_SetRenderStartListener(
    OH_LowPowerVideoSinkCallback* callback, OH_LowPowerVideoSink_OnRenderStarted onRenderStarted, void* userData);

/**
 * @brief 为LowPowerVideoSinkCallback回调设置流切换监听。
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @param onStreamChanged OH_LowPowerVideoSink_OnStreamChanged function,
 * refer to {@link OH_LowPowerVideoSink_OnStreamChanged}
 * @param userData User specific data
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_SetStreamChangedListener(
    OH_LowPowerVideoSinkCallback* callback, OH_LowPowerVideoSink_OnStreamChanged onStreamChanged, void* userData);

/**
 * @brief 为LowPowerVideoSinkCallback回调设置首帧准备完成监听。
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @param onFirstFrameDecoded OH_LowPowerVideoSink_OnFirstFrameDecoded
 * function,
 * refer to {@link OH_LowPowerVideoSink_OnFirstFrameDecoded}
 * @param userData User specific data
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_SetFirstFrameDecodedListener(
    OH_LowPowerVideoSinkCallback* callback,
    OH_LowPowerVideoSink_OnFirstFrameDecoded onFirstFrameDecoded,
    void* userData);

/**
 * @brief 为LowPowerVideoSinkCallback回调设置播放结束监听。
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @param onEos OH_LowPowerVideoSink_OnEos function,
 * refer to {@link OH_LowPowerVideoSink_OnEos}
 * @param userData User specific data
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_SetEosListener(OH_LowPowerVideoSinkCallback* callback,
    OH_LowPowerVideoSink_OnEos onEos, void* userData);

/**
 * @brief 获取当前播放的视频显示时间戳（pts）。
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance.
 * @param pts Pointer to store the latest PTS value (in microseconds).
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 21
 */
OH_AVErrCode OH_LowPowerVideoSink_GetLatestPts(OH_LowPowerVideoSink *sink, int64_t *pts);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_LOWPOWER_VIDEO_SINK_H

/** @} */

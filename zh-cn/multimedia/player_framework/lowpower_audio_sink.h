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
 * @addtogroup LowPowerAudioSink
 * @{
 *
 * @brief LowPowerAudioSink子模块提供低功耗音频输出的变量、属性和函数。
 *
 * @since 20
 */
/**
 * @file lowpower_audio_sink.h
 *
 * @brief 定义LowPowerAudioSink接口。使用LowPowerAudioSink提供的Native API进行音频通路的低功耗播放。
 * 
 * @library liblowpower_avsink.so
 * @kit MediaKit
 * @include <multimedia/player_framework/lowpower_audio_sink.h>
 * @syscap SystemCapability.Multimedia.Media.LowPowerAVSink
 * @since 20
 */

#ifndef NATIVE_LOWPOWER_AUDIO_SINK_H
#define NATIVE_LOWPOWER_AUDIO_SINK_H

#include <stdint.h>
#include <stdio.h>
#include "native_averrors.h"
#include "native_avformat.h"
#include "lowpower_audio_sink_base.h"
#include "ohaudio/native_audiostream_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建LowPowerAudioSink。
 * 
 * @param mime 音频解码器MIME类型，取值范围请参考{@link AVCODEC_MIME_TYPE}
 * @return 如果创建成功返回指向OH_LowPowerAudioSink实例的指针，否则返回空指针。
 * @since 20
 */
OH_LowPowerAudioSink* OH_LowPowerAudioSink_CreateByMime(const char* mime);

/**
 * @brief 配置LowPowerAudioSink，需要在{@link OH_LowPowerAudioSink_Prepare}前完成。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @param format 指向OH_AVFormat的指针，用于配置LowPowerAudioSink的参数。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_UNSUPPORT：不支持的格式。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Configure(OH_LowPowerAudioSink* sink, const OH_AVFormat* format);

/**
 * @brief 为LowPowerAudioSink设置参数，支持{@link OH_LowPowerAudioSink_Prepare}后动态设置。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @param format 指向OH_AVFormat的指针，为LowPowerAudioSink设置的参数
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_UNSUPPORT：不支持的格式。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_SetParameter(OH_LowPowerAudioSink* sink, const OH_AVFormat* format);

/**
 * @brief 获取LowPowerAudioSink的相关参数。应在{@link OH_LowPowerAudioSink_Configure}配置参数后调用。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @param format 指向OH_AVFormat实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_GetParameter(OH_LowPowerAudioSink* sink, OH_AVFormat* format);

/**
 * @brief 准备LowPowerAudioSink的解码、渲染资源，在{@link OH_LowPowerAudioSink_Configure}后调用。
 * 调用此接口前必须调用LowPowerVideoSink的{@link OH_LowPowerVideoSink_SetSyncAudioSink}方法。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_UNSUPPORT：不支持的格式。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Prepare(OH_LowPowerAudioSink* sink);

/**
 * @brief 启动低功耗音频接收器，此接口必须在{@link OH_LowPowerAudioSink_Prepare}成功后调用。
 * 启动成功后，LowPowerAudioSink将开始上报{@link OH_LowPowerAudioSink_OnDataNeeded}事件。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_UNSUPPORT：不支持的格式。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Start(OH_LowPowerAudioSink* sink);

/**
 * @brief 暂停LowPowerAudioSink，在{@link OH_LowPowerAudioSink_Start}或{@link OH_LowPowerAudioSink_Resume}后调用。
 * 暂停成功后，LowPowerAudioSink将暂停{@link OH_LowPowerAudioSink_OnDataNeeded}事件的上报。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Pause(OH_LowPowerAudioSink* sink);

/**
 * @brief 恢复LowPowerAudioSink，在{@link OH_LowPowerAudioSink_Pause}后调用。
 * 恢复成功后，LowPowerAudioSink将恢复{@link OH_LowPowerAudioSink_OnDataNeeded}事件的上报。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Resume(OH_LowPowerAudioSink* sink);

/**
 * @brief 清除LowPowerAudioSink中所有解码器和渲染缓存的输入输出数据。
 * 此接口不建议在{@link OH_LowPowerAudioSink_Start}或{@link OH_LowPowerAudioSink_Resume}之后调用。
 * 需要注意的是，如果编解码器之前已输入数据，则需要重新输入编解码器数据。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Flush(OH_LowPowerAudioSink* sink);

/**
 * @brief 停止LowPowerAudioSink。应在{@link OH_LowPowerAudioSink_Start}或{@link OH_LowPowerAudioSink_Pause}之后调用。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Stop(OH_LowPowerAudioSink* sink);

/**
 * @brief 重置LowPowerAudioSink。
 * 如果要重新使用该实例，需要调用{@link OH_LowPowerAudioSink_Configure}完成配置。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Reset(OH_LowPowerAudioSink* sink);

/**
 * @brief 清理LowPowerAudioSink内部资源，销毁LowPowerAudioSink实例。建议在{@link OH_LowPowerAudioSink_Stop}后调用。不能重复销毁。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Destroy(OH_LowPowerAudioSink* sink);

/**
 * @brief 为LowPowerAudioSink设置渲染音量。需要在{@link OH_LowPowerAudioSink_Prepare}后调用。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @param volume 音量值，取值范围[0.0, 1.0]。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_SetVolume(OH_LowPowerAudioSink* sink, const float volume);

/**
 * @brief 为LowPowerAudioSink设置音频渲染倍速。需要在{@link OH_LowPowerAudioSink_Prepare}后调用。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @param speed 音频渲染倍速值，取值范围[0.25, 4.0]。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_SetPlaybackSpeed(OH_LowPowerAudioSink* sink, const float speed);

/**
 * @brief 给LowPowerAudioSink输入buffer。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @param samples 需要送入LowPowerAudioSink消费的OH_AVSamplesBuffer实例，支持聚包输入。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_ReturnSamples(OH_LowPowerAudioSink* sink, OH_AVSamplesBuffer* samples);

/**
 * @brief 为LowPowerAudioSink注册回调。需要在{@link OH_LowPowerAudioSink_Start}之前调用，以确保事件回调正常接收。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @param callback 指向OH_LowPowerAudioSinkCallback实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_RegisterCallback(OH_LowPowerAudioSink* sink, OH_LowPowerAudioSinkCallback* callback);

/**
 * @brief 创建OH_LowPowerAudioSinkCallback实例。
 * 
 * @return 返回指向OH_LowPowerAudioSinkCallback实例的指针。如果内存不足，则返回nullptr。
 * @since 20
 */
OH_LowPowerAudioSinkCallback* OH_LowPowerAudioSinkCallback_Create(void);

/**
 * @brief 销毁OH_LowPowerAudioSinkCallback实例。
 * 
 * @param callback 指向OH_LowPowerAudioSinkCallback实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_Destroy(OH_LowPowerAudioSinkCallback* callback);

/**
 * @brief 为LowPowerAudioSinkCallback设置进度更新监听。
 * 
 * @param callback 指向OH_LowPowerAudioSinkCallback实例的指针。
 * @param onPositionUpdated OH_LowPowerAudioSink_OnPositionUpdated方法，在PositionUpdate事件触发时调用。
 * 请参考{@link OH_LowPowerAudioSink_OnPositionUpdated}
 * @param userData 用户执行回调所依赖的数据。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_SetPositionUpdateListener(
    OH_LowPowerAudioSinkCallback* callback,
    OH_LowPowerAudioSink_OnPositionUpdated onPositionUpdated,
    void* userData);

/**
 * @brief 为LowPowerAudioSinkCallback设置需要数据监听。
 * 
 * @param callback 指向OH_LowPowerAudioSinkCallback实例的指针。
 * @param onDataNeeded OH_LowPowerAudioSink_OnDataNeeded方法，在DataNeeded事件触发时调用。
 * 请参考{@link OH_LowPowerAudioSink_OnDataNeeded}
 * @param userData 用户执行回调所依赖的数据。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_SetDataNeededListener(
    OH_LowPowerAudioSinkCallback* callback,
    OH_LowPowerAudioSink_OnDataNeeded onDataNeeded,
    void* userData);

/**
 * @brief 为LowPowerAudioSinkCallback设置错误监听。
 * 
 * @param callback 指向OH_LowPowerAudioSinkCallback实例的指针。
 * @param onError  OH_LowPowerAudioSink_OnError方法，在Error事件触发时调用。
 * 请参考{@link OH_LowPowerAudioSink_OnError}
 * @param userData 用户执行回调所依赖的数据。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_SetErrorListener(
    OH_LowPowerAudioSinkCallback* callback,
    OH_LowPowerAudioSink_OnError onError,
    void* userData);

/**
 * @brief 为LowPowerAudioSinkCallback设置音频焦点打断监听。
 * 
 * @param callback 指向OH_LowPowerAudioSinkCallback实例的指针。
 * @param onInterrupted OH_LowPowerAudioSink_OnInterrupted方法，在Interrupted事件触发时调用。
 * 请参考{@link OH_LowPowerAudioSink_OnInterrupted}
 * @param userData 用户执行回调所依赖的数据。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_SetInterruptListener(
    OH_LowPowerAudioSinkCallback* callback,
    OH_LowPowerAudioSink_OnInterrupted onInterrupted,
    void* userData);

/**
 * @brief 为LowPowerAudioSinkCallback设置音频设备切换监听。
 * 
 * @param callback 指向OH_LowPowerAudioSinkCallback实例的指针。
 * @param onDeviceChanged OH_LowPowerAudioSink_OnDeviceChanged方法，在DeviceChanged事件触发时调用。
 * 请参考{@link OH_LowPowerAudioSink_OnDeviceChanged}
 * @param userData 用户执行回调所依赖的数据。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_SetDeviceChangeListener(
    OH_LowPowerAudioSinkCallback* callback,
    OH_LowPowerAudioSink_OnDeviceChanged onDeviceChanged,
    void* userData);

/**
 * @brief 为LowPowerAudioSinkCallback设置播放完成监听。
 * 
 * @param callback 指向OH_LowPowerAudioSinkCallback实例的指针。
 * @param onEos OH_LowPowerAudioSink_OnEos方法，在Eos事件触发时调用。
 * 请参考{@link OH_LowPowerAudioSink_OnEos}
 * @param userData 用户执行回调所依赖的数据。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不支持。
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_SetEosListener(
    OH_LowPowerAudioSinkCallback *callback,
    OH_LowPowerAudioSink_OnEos onEos,
    void* userData);

/**
 * @brief 为LowPowerAudioSink设置播放响度。
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance.
 * @param loudnessGain 响度值，取值范围[-90.0, 24.0]。默认值为0.0dB。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_SERVICE_DIED：媒体服务端已销毁。
 * @since 21
 */
OH_AVErrCode OH_LowPowerAudioSink_SetLoudnessGain(OH_LowPowerAudioSink* sink, float loudnessGain);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_LOWPOWER_AUDIO_SINK_H

/** @} */

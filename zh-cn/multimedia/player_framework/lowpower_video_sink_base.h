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
 * @brief The LowPowerVideoSink submodule provides variables, properties, and functions
 * for lowpower video sink.
 *
 * @since 20
 */
/**
 * @file lowpower_video_sink_base.h
 *
 * @brief 定义LowPowerVideoSink的结构体和枚举。
 * 
 * @library liblowpower_avsink.so
 * @kit MediaKit
 * @syscap SystemCapability.Multimedia.Media.LowPowerAVSink
 * @since 20
 */

#ifndef NATIVE_LOWPOWER_VIDEO_SINK_BASE_H
#define NATIVE_LOWPOWER_VIDEO_SINK_BASE_H

#include <stdint.h>
#include <stdbool.h>
#include "native_avformat.h"
#include "lowpower_avsink_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief LowPowerVideoSink声明。
 * 
 * @since 20
 */
typedef struct OH_LowPowerVideoSink OH_LowPowerVideoSink;

/**
 * @brief 包含了LowPowerVideoSink回调函数指针的集合。<br> 应用需注册此实例结构体到{@link OH_LowPowerVideoSink}实例中，并对回调上报的信息进行处理，
 * 保证LowPowerVideoSink的正常运行。
 * 
 * @since 20
 */
typedef struct OH_LowPowerVideoSinkCallback OH_LowPowerVideoSinkCallback;

/**
 * @brief LowPowerVideoSink需要数据时调用该方法，包含在{@link OH_LowPowerVideoSinkCallback}中。
 * 
 * @param sink OH_LowPowerVideoSink instance
 * @param buffer OH_AVSamplesBuffer instance that will be written in
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerVideoSink_OnDataNeeded)(
    OH_LowPowerVideoSink* sink,
    OH_AVSamplesBuffer* buffer,
    void *userData);

/**
 * @brief LowPowerVideoSink发生错误时调用该方法。
 * 
 * @param sink OH_LowPowerVideoSink instance
 * @param errorCode The error code returned when an error occurs during service operation.
 * See the definition of {@OH_AVErrCode}
 * @param errorMsg string of Error description information returned when an error occurs
 * during service operation
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerVideoSink_OnError)(
    OH_LowPowerVideoSink* sink,
    OH_AVErrCode errCode,
    const char* errMsg,
    void* userData);

/**
 * @brief LowPowerVideoSink到达目标点时调用该方法，包含在{@link OH_LowPowerVideoSinkCallback}中。
 * 
 * @param sink OH_LowPowerVideoSink instance
 * @param targetPts Target pts of renderred frame, in microseconds
 * @param isTimeout If wait target pts timeout, it is false
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerVideoSink_OnTargetArrived)(
    OH_LowPowerVideoSink* sink,
    const int64_t targetPts,
    const bool isTimeout,
    void* userData);

/**
 * @brief LowPowerVideoSink开始渲染时调用该方法，包含在{@link OH_LowPowerVideoSinkCallback}中。
 * 
 * @param sink OH_LowPowerVideoSink instance
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerVideoSink_OnRenderStarted)(OH_LowPowerVideoSink* sink, void* userData);

/**
 * @brief LowPowerVideoSink流切换调用该方法，包含在{@link OH_LowPowerVideoSinkCallback}中。
 * 
 * @param sink OH_LowPowerVideoSink instance
 * @param format Carrying changing parameters and corresponding values
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerVideoSink_OnStreamChanged)(OH_LowPowerVideoSink* sink, OH_AVFormat* format, void* userData);

/**
 * @brief LowPowerVideoSink第一帧解码成功时调用该方法，包含在{@link OH_LowPowerVideoSinkCallback}中。
 * 
 * @param sink OH_LowPowerVideoSink instance
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerVideoSink_OnFirstFrameDecoded)(OH_LowPowerVideoSink* sink, void* userData);

/**
 * @brief LowPowerVideoSink播放完成时调用该方法，包含在{@link OH_LowPowerVideoSinkCallback}中。
 * 
 * @param sink OH_LowPowerVideoSink instance
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerVideoSink_OnEos)(OH_LowPowerVideoSink* sink, void* userData);

#ifdef __cplusplus
}
#endif
#endif // NATIVE_LOWPOWER_VIDEO_SINK_BASE_H

/** @} */

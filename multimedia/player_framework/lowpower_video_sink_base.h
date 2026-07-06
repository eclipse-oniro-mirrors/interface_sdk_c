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
 * @brief The file declares the structs and enums of the LowPowerVideoSink.
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
 * @brief The struct describes the declaration for the LowPowerVideoSink.
 * 
 * @since 20
 */
typedef struct OH_LowPowerVideoSink OH_LowPowerVideoSink;

/**
 * @brief The struct contains a set of callback function pointers for the LowPowerVideoSink.
 * 
 * @since 20
 */
typedef struct OH_LowPowerVideoSinkCallback OH_LowPowerVideoSinkCallback;

/**
 * @brief Called when the LowPowerVideoSink needs more data. This callback is included in {@link OH_LowPowerVideoSinkCallback}.
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
 * @brief Called when an error occurs in the LowPowerVideoSink.
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
 * @brief Called when the LowPowerVideoSink reaches the target point. This callback is included in {@link OH_LowPowerVideoSinkCallback}.
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
 * @brief Called when the LowPowerVideoSink starts rendering. This callback is included in {@link OH_LowPowerVideoSinkCallback}.
 * 
 * @param sink OH_LowPowerVideoSink instance
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerVideoSink_OnRenderStarted)(OH_LowPowerVideoSink* sink, void* userData);

/**
 * @brief Called when the stream changes in the LowPowerVideoSink. This callback is included in {@link OH_LowPowerVideoSinkCallback}.
 * 
 * @param sink OH_LowPowerVideoSink instance
 * @param format Carrying changing parameters and corresponding values
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerVideoSink_OnStreamChanged)(OH_LowPowerVideoSink* sink, OH_AVFormat* format, void* userData);

/**
 * @brief Called when the first frame is successfully decoded in the LowPowerVideoSink. This callback is included in {@link OH_LowPowerVideoSinkCallback}.
 * 
 * @param sink OH_LowPowerVideoSink instance
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerVideoSink_OnFirstFrameDecoded)(OH_LowPowerVideoSink* sink, void* userData);

/**
 * @brief Called when the playback is completed in the LowPowerVideoSink. This callback is included in {@link OH_LowPowerVideoSinkCallback}.
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

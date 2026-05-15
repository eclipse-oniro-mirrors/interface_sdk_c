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
 * @addtogroup AVTranscoder
 * @{
 *
 * @brief Provides APIs of request capability for Transcoder.
 *
 * @syscap SystemCapability.Multimedia.Media.AVTranscoder
 * @since 20
 * @}
 */
/**
 * @file avtranscoder_base.h
 *
 * @brief The file declares the struct and enums used by the AVTranscoder.
 * 
 * @kit MediaKit
 * @library libavtranscoder.so
 * @since 20
 */
 
#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_AVTRANSCODER_BASE_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_AVTRANSCODER_BASE_H

#include <string>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct initializes an AVTranscoder.
 * 
 * @since 20
 */
typedef struct OH_AVTranscoder OH_AVTranscoder;

/**
 * @brief The struct initializes an AVTranscoder_Config.
 * 
 * @since 20
 */
typedef struct OH_AVTranscoder_Config OH_AVTranscoder_Config;

/**
 * @brief Enumerates the transcoding states.
 * 
 * @since 20
 */
typedef enum OH_AVTranscoder_State {
    /**
     * The transcoding process is prepared and ready to start.
     */
    AVTRANSCODER_PREPARED = 1,
    /**
     * The transcoding process has started.
     */
    AVTRANSCODER_STARTED = 2,
    /**
     * The transcoding process is paused.
     */
    AVTRANSCODER_PAUSED = 3,
    /**
     * The transcoding process has been canceled.
     */
    AVTRANSCODER_CANCELLED = 4,
    /**
     * The transcoding process is completed.
     */
    AVTRANSCODER_COMPLETED = 5
} OH_AVTranscoder_State;

/**
 * @brief Defines a callback invoked when the state of the transcoding process changes.
 * 
 * @param transcoder The pointer to an OH_AVTranscoder instance.
 * @param state Indicates the transcoder state. For details, see {@link OH_AVTranscoder_State}.
 * @param userData Pointer to user specific data.
 * @since 20
 */
typedef void (*OH_AVTranscoder_OnStateChange)(OH_AVTranscoder *transcoder, OH_AVTranscoder_State state, void *userData);

/**
 * @brief Defines a callback invoked when an error occurs during the transcoding process.
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance.
 * @param errorCode Error code.
 * {@link AV_ERR_NO_MEMORY}: memory is insufficient.
 * {@link AV_ERR_IO}: IO access failed.
 * {@link AV_ERR_INVALID_STATE}: current state does not support this operation.
 * {@link AV_ERR_UNSUPPORT}: unsupported function.
 * {@link AV_ERR_INVALID_VAL}: the parameter check failed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: operation not allowed.
 * @param errorMsg Error message.
 * @param userData Pointer to user specific data.
 * @since 20
 */
typedef void (*OH_AVTranscoder_OnError)(OH_AVTranscoder *transcoder, int32_t errorCode, const char *errorMsg,
    void *userData);

/**
 * @brief Defines a callback invoked when the progress of the transcoding process is updated.
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance.
 * @param progress Transcoding progress, in percentage.
 * @param userData Pointer to user specific data.
 * @since 20
 */
typedef void (*OH_AVTranscoder_OnProgressUpdate)(OH_AVTranscoder *transcoder, int32_t progress, void *userData);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_AVTRANSCODER_BASE_H

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
 * @brief 提供转码的请求能力接口。
 *
 * @syscap SystemCapability.Multimedia.Media.AVTranscoder
 * @since 20
 * @}
 */
/**
 * @file avtranscoder_base.h
 *
 * @brief 定义了媒体AVTranscoder的结构体和枚举。
 * 
 * @kit MediaKit
 * @include <multimedia/player_framework/avtranscoder_base.h>
 * @library libavtranscoder.so
 * @syscap SystemCapability.Multimedia.Media.AVTranscoder
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
 * @brief 定义AVTranscoder结构体类型。
 * 
 * @since 20
 */
typedef struct OH_AVTranscoder OH_AVTranscoder;

/**
 * @brief 配置AVTranscoder参数的结构体。
 * 
 * @since 20
 */
typedef struct OH_AVTranscoder_Config OH_AVTranscoder_Config;

/**
 * @brief 转码状态。
 * 
 * @since 20
 */
typedef enum OH_AVTranscoder_State {
    /**
     * 准备
     */
    AVTRANSCODER_PREPARED = 1,
    /**
     * 开始
     */
    AVTRANSCODER_STARTED = 2,
    /**
     * 暂停
     */
    AVTRANSCODER_PAUSED = 3,
    /**
     * 取消
     */
    AVTRANSCODER_CANCELLED = 4,
    /**
     * 完成
     */
    AVTRANSCODER_COMPLETED = 5
} OH_AVTranscoder_State;

/**
 * @brief 转码过程的状态回调函数。
 * 
 * @param transcoder OH_AVTranscoder实例的指针。
 * @param state 转码状态，详细说明请参见{@link OH_AVTranscoder_State}.
 * @param userData 用户特定数据的指针。
 * @since 20
 */
typedef void (*OH_AVTranscoder_OnStateChange)(OH_AVTranscoder *transcoder, OH_AVTranscoder_State state, void *userData);

/**
 * @brief 转码过程中错误事件的回调函数。
 * 
 * @param transcoder OH_AVTranscoder实例的指针。
 * @param errorCode 错误码
 * {@link AV_ERR_NO_MEMORY} 无内存，取值为1。
 * {@link AV_ERR_OPERATE_NOT_PERMIT} 操作不允许，取值为2。
 * {@link AV_ERR_INVALID_VAL} 参数检查失败，取值为3。
 * {@link AV_ERR_IO} IO错误，取值为4。
 * {@link AV_ERR_INVALID_STATE} 当前状态不支持此操作，取值为8。
 * {@link AV_ERR_UNSUPPORT} 不支持的接口，取值为9。
 * @param errorMsg 错误消息。
 * @param userData 用户特定数据的指针。
 * @since 20
 */
typedef void (*OH_AVTranscoder_OnError)(OH_AVTranscoder *transcoder, int32_t errorCode, const char *errorMsg,
    void *userData);

/**
 * @brief 转码进度更新时的回调函数。
 * 
 * @param transcoder OH_AVTranscoder实例的指针。
 * @param progress 转码百分比进度。
 * @param userData 用户特定数据的指针。
 * @since 20
 */
typedef void (*OH_AVTranscoder_OnProgressUpdate)(OH_AVTranscoder *transcoder, int32_t progress, void *userData);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_AVTRANSCODER_BASE_H

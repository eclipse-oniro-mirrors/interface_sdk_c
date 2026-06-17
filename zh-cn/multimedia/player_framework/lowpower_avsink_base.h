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
 * @addtogroup AVSinkBase
 * @{
 *
 * @brief The AVSinkBase module provides variables, properties, and functions
 * for lowpower audio sink and lowpower video sink.
 *
 * @since 20
 */
/**
 * @file lowpower_avsink_base.h
 *
 * @brief 定义OH_LowPowerAudioSink和OH_LowPowerVideoSink的基础依赖。
 * 
 * @library liblowpower_avsink.so
 * @kit MediaKit
 * @syscap SystemCapability.Multimedia.Media.LowPowerAVSink
 * @since 20
 */

#ifndef NATIVE_LOWPOWER_AVSINK_BASE_H
#define NATIVE_LOWPOWER_AVSINK_BASE_H

#include <stdint.h>
#include "native_averrors.h"
#include "native_avbuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief LowPowerAVSink输入数据的结构体。应用在收到DataNeeded回调后需要将数据打包装进OH_AVSamplesBuffer实例中送给对应的lowpower_avsink。
 * 
 * @since 20
 */
typedef struct OH_AVSamplesBuffer OH_AVSamplesBuffer;

/**
 * @brief Forward declaration of OH_LowPowerAVSink_Capability.
 *
 * @since 20
 */
typedef struct OH_LowPowerAVSink_Capability OH_LowPowerAVSink_Capability;

/**
 * @brief 将一个OH_AVBuffer中的数据添加到OH_AVSamplesBuffer实例中。
 * 
 * @param samplesBuffer 指向OH_AVSamplesBuffer实例的指针。
 * @param avBuffer 指向OH_AVBuffer实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：参数为nullptr或参数非法。
 * AV_ERR_NO_MEMORY：framePacketBuffer没有足够的剩余容量来追加一个OH_AVBuffer。
 * AV_ERR_UNKNOWN：未知错误。
 * @since 20
 */
OH_AVErrCode OH_AVSamplesBuffer_AppendOneBuffer(OH_AVSamplesBuffer *samplesBuffer, OH_AVBuffer *avBuffer);

/**
 * @brief 获取OH_AVSamplesBuffer实例的剩余可使用容量。
 * 
 * @param samplesBuffer OH_AVSamplesBuffer instance
 * @return OH_AVSamplesBuffer实例剩余可使用容量，单位为字节。如果sampleBuffer或data pointer为nullptr或无效，则返回3。
 * @since 20
 */
int32_t OH_AVSamplesBuffer_GetRemainedCapacity(OH_AVSamplesBuffer *samplesBuffer);

/**
 * @brief 获取Lpp播放器能力。该函数的主要作用是获取当前低功耗播放器所支持的功能和媒体格式。
 * 通过调用此函数，可以了解设备在音频或视频处理方面的支持能力，例如支持的编码格式、解码格式、码率范围等。
 * 
 * @return OH_LowPowerAVSink_Capability：支持Lpp播放器。
 * nullptr：不支持Lpp播放器或者获取失败。
 * @since 21
 */
OH_LowPowerAVSink_Capability *OH_LowPowerAVSink_GetCapability();

#ifdef __cplusplus
}
#endif
#endif // NATIVE_LOWPOWER_AVSINK_BASE_H

/** @} */

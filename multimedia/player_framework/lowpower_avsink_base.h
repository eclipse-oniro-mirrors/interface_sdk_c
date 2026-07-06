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
 * @brief The file declares the basic dependencies for OH_LowPowerAudioSink and OH_LowPowerVideoSink.
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
 * @brief The struct describes the input data of the LowPowerAVSink. After receiving the DataNeeded callback, the
 * application must pack data into an OH_AVSamplesBuffer instance and pass it to the corresponding LowPowerAVSink.
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
 * @brief Appends data from an OH_AVBuffer instance to an OH_AVSamplesBuffer instance.
 * 
 * @param samplesBuffer Pointer to an OH_AVSamplesBuffer instance.
 * @param avBuffer Pointer to an OH_AVBuffer instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * **AV_ERR_NO_MEMORY**: The framePacketBuffer does not have sufficient remaining capacity to append an OH_AVBuffer.
 * **AV_ERR_UNKNOWN**: An unknown error occurs.
 * @since 20
 */
OH_AVErrCode OH_AVSamplesBuffer_AppendOneBuffer(OH_AVSamplesBuffer *samplesBuffer, OH_AVBuffer *avBuffer);

/**
 * @brief Obtains the remaining capacity available in an OH_AVSamplesBuffer instance.
 * 
 * @param samplesBuffer OH_AVSamplesBuffer instance
 * @return Remaining capacity available in the OH_AVSamplesBuffer instance, in bytes. If **sampleBuffer** or data
 * pointer is nullptr or invalid, **3** is returned.
 * @since 20
 */
int32_t OH_AVSamplesBuffer_GetRemainedCapacity(OH_AVSamplesBuffer *samplesBuffer);

/**
 * @brief Obtains the capability of the low-power player. It mainly helps you find out what the low-power player can do,
 * including the media formats and features it supports.
 * When you call this function, you can learn about the device's capabilities in audio and video processing. For
 * example, you can find out which encoding and decoding formats are supported, as well as the range of bit rates that
 * the device can handle.
 * 
 * @return **OH_LowPowerAVSink_Capability**: The low-power player is supported.
 * **nullptr**: The low-power player is not supported or the capability fails to be obtained.
 * @since 21
 */
OH_LowPowerAVSink_Capability *OH_LowPowerAVSink_GetCapability();

#ifdef __cplusplus
}
#endif
#endif // NATIVE_LOWPOWER_AVSINK_BASE_H

/** @} */

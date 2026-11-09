/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup NativeDisplaySoloist
 * @{
 *
 * @brief NativeDisplaySoloist is a native-side module used to implement frame rate control in an independent thread. This module allows developers to precisely control the frame generation cadence in an independent thread, making it suitable for scenarios that require high-performance graphics rendering. With this module, developers can implement custom frame scheduling logic to meet the requirements of different scenarios.
 *
 * @since 12
 * @version 1.0
 */

/**
 * @file native_display_soloist.h
 *
 * @brief This file declares the functions for obtaining and using native display soloist.
 *
 * @kit ArkGraphics2D
 * @library libnative_display_soloist.so
 * @syscap SystemCapability.Graphic.Graphic2D.HyperGraphicManager
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_NATIVE_DISPLAY_SOLOIST_H_
#define C_INCLUDE_NATIVE_DISPLAY_SOLOIST_H_

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Declares the OH_DisplaySoloist struct, which is used for native-side services that need to implement frame rate control on a dedicated thread.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_DisplaySoloist OH_DisplaySoloist;

/**
 * @brief Type of the OH_DisplaySoloist callback function. It is invoked by the system each time a VSync signal arrives, to execute the custom service of each frame.
 *
 * @param timestamp VSync timestamp of the current frame, in nanoseconds.
 * @param targetTimestamp Expected VSync timestamp of the next frame, in nanoseconds.
 * @param data Pointer to the user-defined data.
 * @since 12
 * @version 1.0
 */
typedef void (*OH_DisplaySoloist_FrameCallback)(long long timestamp, long long targetTimestamp, void* data);

/**
 * @brief Defines the expected frame rate range struct, which is used to set the expected frame rate range of DisplaySoloist (variable frame rate drawing on an independent thread). The set expected frame rate range serves as a reference for system scheduling, and the system tries to adjust the drawing frame rate within this range.
 *
 * @since 12
 * @version 1.0
 */
typedef struct {
    /**
     * Expected minimum frame rate. Unit: fps. Value range: [0, maximum refresh rate supported by the device].
     */
    int32_t min;
    /**
     * Expected maximum frame rate. Unit: fps. Value range: [min, maximum refresh rate supported by the device].
     */
    int32_t max;
    /**
     * Expected target frame rate. Unit: fps. Value range: [min, max].
     */
    int32_t expected;
} DisplaySoloist_ExpectedRateRange;

/**
 * @brief Creates an OH_DisplaySoloist instance. Each call creates a new instance. The useExclusiveThread parameter determines the thread mode: in dedicated thread mode, the instance has an independent thread, which delivers higher performance but consumes more resources; in shared thread mode, multiple instances share a thread, which consumes fewer resources but may incur scheduling latency.
 *
 * @param useExclusiveThread Indicates whether this OH_DisplaySoloist instance uses a dedicated thread. true indicates a dedicated thread, and false indicates a shared thread (sharing a thread with other instances).
 * @return Returns the pointer to the OH_DisplaySoloist instance created if the operation is successful; returns a null pointer otherwise. The failure cause may be out of memory.
 * @since 12
 * @version 1.0
 */
OH_DisplaySoloist* OH_DisplaySoloist_Create(bool useExclusiveThread);

/**
 * @brief Destroys the OH_DisplaySoloist instance and reclaims the memory occupied by the object. Before destruction, call OH_DisplaySoloist_Stop to stop the callback. After destruction, do not access the instance or rely on its callback.
 *
 * @param displaySoloist Pointer to an OH_DisplaySoloist instance. Must not be null.
 * @return 0 indicates success; -1 indicates failure, possibly because an incorrect displaySoloist is passed in.
 * @since 12
 * @version 1.0
 */
int32_t OH_DisplaySoloist_Destroy(OH_DisplaySoloist* displaySoloist);

/**
 * @brief Starts requesting VSync signals and invokes the callback function each time a VSync signal arrives. If an expected frame rate range has been set through OH_DisplaySoloist_SetExpectedFrameRateRange, the expected frame rate range takes effect.
 *
 * @param displaySoloist Pointer to an OH_DisplaySoloist instance. Must not be null.
 * @param callback Callback invoked when the next VSync signal arrives.
 * @param data Pointer to the user-defined data, used to pass custom data to the callback function. Pass this parameter when custom data needs to be accessed in the callback function. It can be null.
 * @return The return value 0 indicates success; -1 indicates failure, possibly because an invalid displaySoloist or callback is passed in.
 * @since 12
 * @version 1.0
 */
int32_t OH_DisplaySoloist_Start(
    OH_DisplaySoloist* displaySoloist, OH_DisplaySoloist_FrameCallback callback, void* data);

/**
 * @brief Stops requesting VSync signals and stops invoking the callback function callback. It also invalidates the expected frame rate range set through OH_DisplaySoloist_SetExpectedFrameRateRange. After stopping, you can call OH_DisplaySoloist_Start again to restart. It is used in pair with OH_DisplaySoloist_Start and must be called after OH_DisplaySoloist_Start.
 *
 * @param displaySoloist Pointer to an OH_DisplaySoloist instance. Must not be null.
 * @return The value 0 indicates success, and -1 indicates failure. The possible cause is that an incorrect displaySoloist is passed in.
 * @since 12
 * @version 1.0
 */
int32_t OH_DisplaySoloist_Stop(OH_DisplaySoloist* displaySoloist);

/**
 * @brief Sets the expected VSync frame rate range. The set expected frame rate range serves as a reference for system scheduling, and the system tries to adjust the rendering frame rate within this range. If this method is not called or DisplaySoloist_ExpectedRateRange(0, 0, 0) is passed in, the frame rate follows the current running frame rate of the application. It is recommended to set it before calling OH_DisplaySoloist_Start so that it takes effect immediately. Setting it after calling OH_DisplaySoloist_Start also takes effect but may incur latency.
 *
 * @param displaySoloist Pointer to an OH_DisplaySoloist instance. Must not be null.
 * @param range Pointer to a DisplaySoloist_ExpectedRateRange instance of the expected frame rate range. Must not be null. Contains three fields: expected, min, and max, in frames per second (fps). The fields must be non-negative integers within the range [0, maximum device frame rate], and must satisfy min <= expected <= max. If the value is out of the valid range, parameter verification fails.
 * @return Returns 0 if the operation is successful; returns -1 if the operation fails. Possible failure causes: 1. A required parameter is not specified; 2. The parameter type is incorrect; 3. Parameter verification fails or DisplaySoloist_ExpectedRateRange is invalid.
 * @since 12
 * @version 1.0
 */
int32_t OH_DisplaySoloist_SetExpectedFrameRateRange(
    OH_DisplaySoloist* displaySoloist, DisplaySoloist_ExpectedRateRange* range);

#ifdef __cplusplus
}
#endif

#endif
/** @} */

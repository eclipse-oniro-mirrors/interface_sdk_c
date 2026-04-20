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
 * @brief Provides the native displaySoloist capability.
 *
 * @since 12
 * @version 1.0
 */

/**
 * @file native_display_soloist.h
 *
 * @brief Defines the functions for obtaining and using a native displaySoloist.
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
 * @brief Provides the declaration of an **OH_DisplaySoloist** struct.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_DisplaySoloist OH_DisplaySoloist;

/**
 * @brief Defines the pointer to an OH_DisplaySoloist callback function.
 *
 * @param timestamp Current frame VSync timestamp.
 * @param targetTimestamp Expected VSync timestamp of the next frame.
 * @param data Pointer to user-defined data.
 * @since 12
 * @version 1.0
 */
typedef void (*OH_DisplaySoloist_FrameCallback)(long long timestamp, long long targetTimestamp, void* data);

/**
 * @brief This struct describes the expected frame rate range.
 *
 * @since 12
 * @version 1.0
 */
typedef struct {
    /**
     * Minimum value of the expected frame rate range. The value range is [0,120].
     */
    int32_t min;
    /**
     * Maximum value of the expected frame rate range. The value range is [0,120].
     */
    int32_t max;
    /**
     * Expected frame rate. The value range is [0,120].
     */
    int32_t expected;
} DisplaySoloist_ExpectedRateRange;

/**
 * @brief Creates an **OH_DisplaySoloist** instance. A new **OH_DisplaySoloist** instance is created each time this API
 * is called.
 *
 * @param useExclusiveThread Whether the **OH_DisplaySoloist** instance is an exclusive thread. **true** means yes; **
 * false** otherwise.
 * @return Returns the pointer to the {@link OH_DisplaySoloist} instance created if the operation is successful;
 * returns a null pointer otherwise. The failure cause may be out of memory.
 * @since 12
 * @version 1.0
 */
OH_DisplaySoloist* OH_DisplaySoloist_Create(bool useExclusiveThread);

/**
 * @brief Destroys an **OH_DisplaySoloist** object and reclaims the memory occupied.
 *
 * @param displaySoloist Pointer to the {@link OH_DisplaySoloist} instance.
 * @return Returns **0** if the operation is successful; returns **-1** otherwise.
 * @since 12
 * @version 1.0
 */
int32_t OH_DisplaySoloist_Destroy(OH_DisplaySoloist* displaySoloist);

/**
 * @brief Sets a callback function for each frame. The callback function is triggered each time a VSync signal arrives.
 *
 * @param displaySoloist Pointer to the {@link OH_DisplaySoloist} instance.
 * @param callback Callback function to be triggered when the next VSync signal arrives.
 * @param data Pointer to the user-defined data struct. The type is void.
 * @return Returns **0** if the operation is successful; returns **-1** otherwise.
 * @since 12
 * @version 1.0
 */
int32_t OH_DisplaySoloist_Start(
    OH_DisplaySoloist* displaySoloist, OH_DisplaySoloist_FrameCallback callback, void* data);

/**
 * @brief Stop to request next vsync with callback.
 *
 * @param displaySoloist Pointer to the {@link OH_DisplaySoloist} instance.
 * @return Returns **0** if the operation is successful; returns **-1** otherwise.
 * @since 12
 * @version 1.0
 */
int32_t OH_DisplaySoloist_Stop(OH_DisplaySoloist* displaySoloist);

/**
 * @brief Sets the expected frame rate range.
 *
 * @param displaySoloist Pointer to the {@link OH_DisplaySoloist} instance.
 * @param range Pointer to the {@link DisplaySoloist_ExpectedRateRange} instance.
 * @return Returns **0** if the operation is successful; returns **-1** otherwise.
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
/*
 * Copyright (c) 2022-2022 Huawei Device Co., Ltd.
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
 * @addtogroup NativeVsync
 * @{
 *
 * @brief This module provides the capabilities for obtaining the system vertical synchronization (VSync) callback,
 * allowing you to synchronize your application's drawing frame rate with the system's frame rate.
 *
 * @since 9
 */

/**
 * @file native_vsync.h
 *
 * @brief This file declares the functions for obtaining and using native vertical synchronization (VSync).
 *
 * @kit ArkGraphics2D
 * @library libnative_vsync.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeVsync
 * @include <native_vsync/native_vsync.h>
 * @since 9
 */

#ifndef NDK_INCLUDE_NATIVE_VSYNC_H_
#define NDK_INCLUDE_NATIVE_VSYNC_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Provides the declaration of an **OH_NativeVSync** struct.
 *
 * @since 9
 */
typedef struct OH_NativeVSync OH_NativeVSync;

/**
 * @brief Defines the pointer to a VSync callback function.
 *
 * @param timestamp [in] System timestamp obtained by VSync using CLOCK_MONOTONIC, in nanoseconds.
 * @param data [in] Pointer to user-defined data.
 * @since 9
 */
typedef void (*OH_NativeVSync_FrameCallback)(long long timestamp, void *data);

/**
 * @brief Provides the expected frame rate range.
 *
 * @since 20
 */
typedef struct {
    /** @brief Minimum frame rate. */
    int32_t min;
    /** @brief Maximum frame rate. */
    int32_t max;
    /** @brief Expected frame rate. */
    int32_t expected;
} OH_NativeVSync_ExpectedRateRange;

/**
 * @brief Creates an OH_NativeVSync instance. Each call creates a new instance. The number of OH_NativeVSync instances
 * is limited, and a null pointer is returned when the limit is exceeded.
 * <br>This API must be used together with {@link OH_NativeVSync_Destroy}; otherwise, a memory leak occurs.
 *
 * @param name [in] Pointer to the name that associates with the **OH_NativeVSync** instance.
 * @param length [in] Length of the name (number of characters).
 * @return Returns the pointer to an **OH_NativeVSync** instance.
 * @release native_vsync/OH_NativeVSync_Destroy {return}
 * @since 9
 */
OH_NativeVSync *OH_NativeVSync_Create(const char *name, unsigned int length);

/**
 * @brief Destroys an **OH_NativeVSync** instance.
 * <br>Once the **OH_NativeVSync** pointer is destroyed, it should not be used, as this can result in dangling pointer
 * problems. Pay special attention to the management of the **OH_NativeVSync** pointer in multithreaded scenarios.
 *
 * @param nativeVsync [in] Pointer to an **OH_NativeVSync** instance.
 * @since 9
 */
void OH_NativeVSync_Destroy(OH_NativeVSync *nativeVsync);

/**
 * @brief Creates an **OH_NativeVSync** instance to bind with a window. A new **OH_NativeVSync** instance is created
 * each time this API is called.
 * <br>The actual VSync period of the **OH_NativeVSync** instance created by calling this function may be different
 * from the system's VSync period. The system adjusts the actual VSync period based on the window status.
 *
 * @param windowID [in] Window ID, which is the index identifier of the window child process and can be obtained
 *     through {@link OH_NativeWindow_GetSurfaceId}.
 * @param name [in] Pointer to the name that associates with the **OH_NativeVSync** instance.
 * @param length [in] Length of the name (number of characters).
 * @return Returns the pointer to an **OH_NativeVSync** instance.
 * @release native_vsync/OH_NativeVSync_Destroy {return}
 * @since 14
 */
OH_NativeVSync *OH_NativeVSync_Create_ForAssociatedWindow(uint64_t windowID, const char *name, unsigned int length);

/**
 * @brief Requests the next VSync signal. When the signal arrives, the callback function callback is invoked.
 * <br>If this API is called multiple times within the same frame, only the last callback is triggered.
 * <br>If this API and {@link OH_NativeVSync_RequestFrameWithMultiCallback} are called within the same frame, this API
 * does not take effect.
 *
 * @param nativeVsync [in] Pointer to an **OH_NativeVSync** instance.
 * @param callback [in] Function pointer of the **OH_NativeVSync_FrameCallback** type.
 *     This function pointer will be called when the next VSync signal arrives.
 * @param data [in] Pointer to the user-defined data struct. The type is void.
 * @return Returns **0** if the operation is successful; returns an error code defined in {@link OHNativeErrorCode}
 *     otherwise.
 * @since 9
 */
int OH_NativeVSync_RequestFrame(OH_NativeVSync *nativeVsync, OH_NativeVSync_FrameCallback callback, void *data);

/**
 * @brief Requests the next VSync signal. When the signal arrives, the callback function callback is invoked.
 * <br>If this API is called multiple times within the same frame, every callback passed in is executed.
 *
 * @param nativeVsync [in] Pointer to an **OH_NativeVSync** instance.
 * @param callback [in] Function pointer of the **OH_NativeVSync_FrameCallback** type. This function pointer will be
 *     called when the next VSync signal arrives.
 * @param data [in] Pointer to the user-defined data struct. The type is void.
 * @return Returns **0** if the operation is successful; returns an error code defined in {@link OHNativeErrorCode}
 *     otherwise.
 * @since 12
 */
int OH_NativeVSync_RequestFrameWithMultiCallback(
    OH_NativeVSync *nativeVsync, OH_NativeVSync_FrameCallback callback, void *data);

/**
 * @brief Obtains the VSync period.
 * <br>The VSync period is refreshed only when the **OH_NativeVSync_FrameCallback** callback is received following a
 * request for a VSync signal via **OH_NativeVSync_RequestFrame** or **OH_NativeVSync_RequestFrameWithMultiCallback**.
 * <br>To obtain the VSync period for the first time using this function, you need to call
 * **OH_NativeVSync_RequestFrame** or **OH_NativeVSync_RequestFrameWithMultiCallback** to request a VSync signal. 
 * Once the **OH_NativeVSync_FrameCallback** callback is received, the vsync period can be obtained.
 *
 * @param nativeVsync [in] Pointer to an **OH_NativeVSync** instance.
 * @param period [out] Pointer to the VSync period.
 * @return Returns **0** if the operation is successful; returns an error code defined in {@link OHNativeErrorCode}
 *     otherwise.
 * @since 10
 */
int OH_NativeVSync_GetPeriod(OH_NativeVSync *nativeVsync, long long *period);

/**
 * @brief Enables DVSync to improve the smoothness of self-drawing animations.
 * <br>DVSync, short for Decoupled VSync, is a frame timing management policy that is decoupled from the hardware's
 * VSync.
 * <br>DVSync drives the early rendering of upcoming animation frames by sending VSync signals with future timestamps.
 * These frames are stored in a frame buffer queue. This helps DVSync reduce potential frame drops and therefore
 * enhances the smoothness of animations.
 * <br>DVSync requires free self-drawing frame buffers to store these pre-rendered animation frames. Therefore, you
 * must ensure that at least one free frame buffer is available. Otherwise, do not enable DVSync.
 * <br>After DVSync is enabled, you must correctly respond to the early VSync signals and request the subsequent VSync
 * after the animation frame associated with the previous VSync is complete. In addition, the self-drawing frames must
 * carry timestamps that align with VSync.
 * <br>After the animation ends, disable DVSync.
 * <br>On a platform that does not support DVSync or if another application has enabled DVSync, the attempt to enable
 * it will not take effect, and the application still receives normal VSync signals.
 *
 * @param nativeVsync [in] Pointer to an **OH_NativeVSync** instance.
 * @param enable [in] Whether to enable DVSync. The value **true** means to enable DVSync, and **false** means the
 *     opposite.
 * @return Returns **0** if the operation is successful; returns an error code defined in {@link OHNativeErrorCode}
 *     otherwise.
 * @since 14
 */
int OH_NativeVSync_DVSyncSwitch(OH_NativeVSync *nativeVsync, bool enable);

/**
 * @brief Sets the expected frame rate and its range. The actual frame rate may be different from the expected frame
 * rate due to system power consumption, performance, and hardware specifications.
 *
 * @param nativeVsync [in] Pointer to an {@link OH_NativeVSync} instance.
 * @param range [in] Pointer to an {@link OH_NativeVSync_ExpectedRateRange} instance.
 *     <br>Valid expected frame rate range: 0 <= Minimum value <= Expected frame rate <= Maximum value <= 144.
 *     <br>The value **0** means that the expected frame rate is canceled.
 *     <br>You need to manage the lifecycle of this pointer.
 * @return Returns **0** if successful; returns an error code defined in {@link OHNativeErrorCode} otherwise.
 * @since 20
 */
int OH_NativeVSync_SetExpectedFrameRateRange(OH_NativeVSync *nativeVsync, OH_NativeVSync_ExpectedRateRange *range);
#ifdef __cplusplus
}
#endif

/** @} */
#endif
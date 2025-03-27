/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup NativeFence
 * @{
 *
 * @brief Provides the native fence capability
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeFence
 * @since 20
 * @version 1.0
 */

/**
 * @file native_fence.h
 *
 * @brief Defines the functions for using native fence.
 *
 * @kit ArkGraphics2D
 * @library libnative_fence.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeFence
 * @since 20
 * @version 1.0
 */

#ifndef NDK_INCLUDE_NATIVE_FENCE_H_
#define NDK_INCLUDE_NATIVE_FENCE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Checks if the fence is valid.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeFence
 * @param fenceFd Indicates a file descriptor handle, which is used for timing synchronization.
 * @return Returns true means the fence is valid, otherwise, invalid.
 * @since 20
 * @version 1.0
 */
bool OH_NativeFence_IsValid(int fenceFd);

/**
 * @brief Waits for a fence signal. The maximum waiting time is determined by the timeout parameter.\n
 * If the fence is invalid, it is equivalent to the fence having signaled, and the function will return true immediately.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeFence
 * @param fenceFd Indicates a file descriptor handle, which is used for timing synchronization.
 * @param timeout Indicates the timeout duration.
 * @return Returns true if the fence signaled, false otherwise.
 * @since 20
 * @version 1.0
 */
bool OH_NativeFence_Wait(int fenceFd, uint32_t timeout);

/**
 * @brief Waits forever for a fence signal.\n
 * If the fence is invalid, it is equivalent to the fence having signaled, and the function will return true immediately.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeFence
 * @param fenceFd Indicates a file descriptor handle, which is used for timing synchronization.
 * @return Returns true if the fence signaled, false otherwise.
 * @since 20
 * @version 1.0
 */
bool OH_NativeFence_WaitForever(int fenceFd);

/**
 * @brief Close the fence
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeFence
 * @param fenceFd Indicates a file descriptor handle, which is used for timing synchronization.
 * @since 20
 * @version 1.0
 */
void OH_NativeFence_Close(int fenceFd);
#ifdef __cplusplus
}
#endif

/** @} */
#endif
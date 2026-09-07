/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
 * @addtogroup NativeWindow
 * @{
 *
 * @brief Provides the BufferHandle struct for native window.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @since 8
 * @version 1.0
 */

/**
 * @file buffer_handle.h
 *
 * @brief Defines the BufferHandle struct for native window.
 *
 * @kit ArkGraphics2D
 * @library libnative_window.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @since 8
 * @version 1.0
 */

#ifndef INCLUDE_BUFFER_HANDLE_H
#define INCLUDE_BUFFER_HANDLE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Buffer handle used to transfer and obtain information about the buffer.
 * @since 8
 */
typedef struct {
    /** buffer fd, -1 if not supported */
    int32_t fd;
    /** the width of memory */
    int32_t width;
    /** the stride of memory */
    int32_t stride;
    /** the height of memory */
    int32_t height;
    /** size of memory */
    int32_t size;
    /** the format of memory */
    int32_t format;
    /** the usage of memory */
    uint64_t usage;
    /** Virtual address of memory  */
    void *virAddr;
    /** Shared memory key */
    int32_t key;
    /** Physical address */
    uint64_t phyAddr;
    /** the number of reserved fd value */
    uint32_t reserveFds;
    /** the number of reserved integer value */
    uint32_t reserveInts;
    /** the data */
    int32_t reserve[0];
} BufferHandle;

#ifdef __cplusplus
}
#endif

/** @} */
#endif // INCLUDE_BUFFER_HANDLE_H

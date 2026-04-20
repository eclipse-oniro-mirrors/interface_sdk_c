/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
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
 * @addtogroup Drawing
 * @{
 *
 * @brief Provides functions such as 2D graphics rendering, text drawing, and image display.
 *
 * @since 12
 * @version 1.0
 */
/**
 * @file drawing_memory_stream.h
 *
 * @brief This file declares the functions related to the memory stream in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_MEMORY_STREAM_H
#define C_INCLUDE_DRAWING_MEMORY_STREAM_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an **OH_Drawing_MemoryStream** object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **data** is NULL or **length** is **0**, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @return Returns the pointer to the {@link OH_Drawing_MemoryStream} object created.
 * @param data Pointer to the data.
 * @param length Length of the data.
 * @param copyData Whether to copy data. The value **true** means that the **OH_Drawing_MemoryStream** object copies
 * the data, and **false** means that the **OH_Drawing_MemoryStream** object directly uses the data without copying.
 * @since 12
 * @version 1.0
 */
OH_Drawing_MemoryStream* OH_Drawing_MemoryStreamCreate(const void* data, size_t length, bool copyData);

/**
 * @brief Destroys an **OH_Drawing_MemoryStream** object and reclaims the memory occupied by the object.
 *
 * @param memoryStream Pointer to an {@link OH_Drawing_MemoryStream} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MemoryStreamDestroy(OH_Drawing_MemoryStream* memoryStream);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
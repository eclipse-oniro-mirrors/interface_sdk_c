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
 * @brief 创建一个内存流对象。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * data为NULL或者length等于0时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @return 函数会返回一个指针，指针指向创建的内存流对象{@link OH_Drawing_MemoryStream}。
 * @param data 数据段。
 * @param length 数据段长度。
 * @param copyData 是否拷贝数据。true表示内存流对象会拷贝一份数据段数据，false表示内存流对象直接使用数据段数据，不拷贝。
 * @since 12
 * @version 1.0
 */
OH_Drawing_MemoryStream* OH_Drawing_MemoryStreamCreate(const void* data, size_t length, bool copyData);

/**
 * @brief 销毁内存流对象并回收该对象占用的内存。
 *
 * @param memoryStream 指向内存流对象{@link OH_Drawing_MemoryStream}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MemoryStreamDestroy(OH_Drawing_MemoryStream* memoryStream);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
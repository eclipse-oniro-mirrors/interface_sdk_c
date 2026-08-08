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
 * @brief 文件中定义了与内存流相关的功能函数，支持基于内存数据创建和销毁内存流对象。
 * 内存流支持数据拷贝或直接引用两种访问方式。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
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
 * @brief 创建一个内存流对象，用于将内存中的数据封装为流，可作为数据源供图形处理接口（如图像解码）等后续绘制接口使用。
 * 创建的内存流对象使用完毕后，需要调用
 * {@link OH_Drawing_MemoryStreamDestroy()}销毁并回收内存。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>data为NULL或者length等于0时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @return 指向创建的内存流对象{@link OH_Drawing_MemoryStream}的指针，
 * 可作为数据源传递给后续图形处理接口（如图像解码）使用。
 * @param data 要创建内存流的数据缓冲区，数据为二进制字节流，长度由length参数指定，单位为字节。data不能为NULL，
 * 为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 * 当copyData为false时，调用者还需确保data指向的数据在内存流对象生命周期内保持有效。
 * @param length 数据段长度，单位为字节，取值必须大于0。为0时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 * @param copyData 是否拷贝数据。true表示内存流对象会拷贝一份数据段数据，false表示内存流对象直接使用数据段数据，不拷贝。
 * @since 12
 * @version 1.0
 */
OH_Drawing_MemoryStream* OH_Drawing_MemoryStreamCreate(const void* data, size_t length, bool copyData);

/**
 * @brief 销毁由{@link OH_Drawing_MemoryStreamCreate()}创建的内存流对象并回收该对象占用的内存。
 * 销毁后不应再访问内存流对象。
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
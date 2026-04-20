/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @since 8
 */
/**
 * @file drawing_path_iterator.h
 *
 * @brief This file declares the functions related to the path operation iterator object.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 23
 */

#ifndef C_INCLUDE_DRAWING_PATH_ITERATOR_H
#define C_INCLUDE_DRAWING_PATH_ITERATOR_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 迭代器包含的路径操作类型枚举，可用于读取路径的操作指令。
 *
 * @since 23
 */
typedef enum {
    /**
     * 设置路径的起始点。
     */
    MOVE = 0,
    /**
     * 添加线段。
     */
    LINE = 1,
    /**
     * 添加二阶贝塞尔圆滑曲线。
     */
    QUAD = 2,
    /**
     * 添加圆锥曲线。
     */
    CONIC = 3,
    /**
     * 添加三阶贝塞尔圆滑曲线。
     */
    CUBIC = 4,
    /**
     * 闭合路径。
     */
    CLOSE = 5,
    /**
     * 完成路径设置。
     */
    DONE = CLOSE + 1,
} OH_Drawing_PathIteratorVerb;

/**
 * @brief 创建路径操作迭代器对象。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param pathIterator 指向路径操作迭代器对象{@link OH_Drawing_PathIterator}的二级指针，作为出参使用。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示path或pathIterator是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorCreate(const OH_Drawing_Path* path, OH_Drawing_PathIterator** pathIterator);

/**
 * @brief 销毁路径操作迭代器对象并回收该对象占有的内存。
 *
 * @param pathIterator 指向路径操作迭代器对象{@link OH_Drawing_PathIterator}的指针。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示pathIterator是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorDestroy(OH_Drawing_PathIterator* pathIterator);

/**
 * @brief 判断路径操作迭代器中是否还有下一个操作。
 *
 * @param pathIterator 指向路径操作迭代器对象{@link OH_Drawing_PathIterator}的指针。
 * @param hasNext 表示路径操作迭代器中是否还有下一个操作。作为出参使用。true表示还有下一个操作，false表示没有下一个操作。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示pathIterator或hasNext是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorHasNext(const OH_Drawing_PathIterator* pathIterator, bool* hasNext);

/**
 * @brief 返回当前路径的下一个操作，并将迭代器置于该操作。
 *
 * @param pathIterator 指向路径操作迭代器对象{@link OH_Drawing_PathIterator}的指针。
 * @param points 表示坐标点数组。
 * @param count 表示坐标点数组的大小。
 * @param offset 数组中写入位置相对起始点的偏移量，取值范围为[0, count-4]。
 * @param verb 表示当前路径的下一个操作。作为出参使用。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示pathIterator或points或verb是空指针。
 * 返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE，表示count小于offset + 4。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorNext(OH_Drawing_PathIterator* pathIterator,
    OH_Drawing_Point2D* points, uint32_t count, uint32_t offset, OH_Drawing_PathIteratorVerb* verb);

/**
 * @brief 返回当前路径的下一个操作，迭代器保持在原操作。
 *
 * @param pathIterator 指向路径操作迭代器对象{@link OH_Drawing_PathIterator}的指针。
 * @param verb 表示当前路径的下一个操作。作为出参使用。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示pathIterator或verb是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorPeek(const OH_Drawing_PathIterator* pathIterator,
    OH_Drawing_PathIteratorVerb* verb);

#ifdef __cplusplus
}
#endif
#endif // C_INCLUDE_DRAWING_PATH_ITERATOR_H

/** @} */
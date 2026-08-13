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
 * @brief Drawing模块提供包括2D图形渲染、文字绘制和图片显示等功能函数。
 * <br>本模块采用屏幕物理像素单位px。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @since 8
 */
/**
 * @file drawing_path_iterator.h
 *
 * @brief 声明与路径操作迭代器对象相关的函数。路径操作迭代器用于遍历路径中的操作指令（如移动、连线、贝塞尔曲线、
 * 闭合等），迭代器从路径起始位置依次遍历各操作指令，内部维护当前遍历位置。支持创建和销毁迭代器、
 * 判断是否还有下一个操作、
 * 读取下一个操作并将迭代器前移、查看下一个操作但不移动迭代器。
 * 通过迭代器可在不修改原始路径的情况下逐条读取路径操作信息。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
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
     * 添加二阶贝塞尔曲线。
     */
    QUAD = 2,
    /**
     * 添加圆锥曲线。
     */
    CONIC = 3,
    /**
     * 添加三阶贝塞尔曲线。
     */
    CUBIC = 4,
    /**
     * 闭合路径。
     */
    CLOSE = 5,
    /**
     * 表示路径操作迭代结束。
     */
    DONE = CLOSE + 1,
} OH_Drawing_PathIteratorVerb;

/**
 * @brief 创建路径操作迭代器对象。使用完毕后，必须调用{@link OH_Drawing_PathIteratorDestroy}销毁迭代器对象并释放内存，
 * 否则会导致内存泄漏。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param pathIterator 指向路径操作迭代器对象{@link OH_Drawing_PathIterator}的二级指针，作为出参使用。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示path或pathIterator是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorCreate(const OH_Drawing_Path* path, OH_Drawing_PathIterator** pathIterator);

/**
 * @brief 销毁路径操作迭代器对象并回收该对象占用的内存。
 *
 * @param pathIterator 指向需要销毁的路径操作迭代器对象{@link OH_Drawing_PathIterator}的指针。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示pathIterator是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorDestroy(OH_Drawing_PathIterator* pathIterator);

/**
 * @brief 判断路径操作迭代器中是否还有下一个操作。
 *
 * @param pathIterator 指向路径操作迭代器对象{@link OH_Drawing_PathIterator}的指针，用于判断是否还有下一个操作。
 * @param hasNext 表示路径操作迭代器中是否还有下一个操作。作为出参使用。true表示还有下一个操作，false表示没有下一个操作。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示pathIterator或hasNext是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorHasNext(const OH_Drawing_PathIterator* pathIterator, bool* hasNext);

/**
 * @brief 返回当前路径的下一个操作，并将迭代器置于该操作。
 *
 * @param pathIterator 指向路径操作迭代器对象{@link OH_Drawing_PathIterator}的指针，调用后迭代器将前移到该操作位置。
 * @param points 表示坐标点数组，作为出参使用，用于接收下一个操作对应的坐标点，坐标点从数组的offset位置开始写入。
 * 调用者需预先分配大小不小于count的内存空间，否则可能导致内存越界写入。
 * @param count 表示坐标点数组的元素个数。
 * @param offset 表示数组中写入坐标点的起始位置相对数组起始位置（索引0）的偏移量，取值范围为[0, count-4]。
 * @param verb 表示当前路径的下一个操作。作为出参使用。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示pathIterator或points或verb是空指针。
 *     <br>返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE，表示count小于offset + 4。
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
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示pathIterator或verb是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorPeek(const OH_Drawing_PathIterator* pathIterator,
    OH_Drawing_PathIteratorVerb* verb);

#ifdef __cplusplus
}
#endif
#endif // C_INCLUDE_DRAWING_PATH_ITERATOR_H

/** @} */
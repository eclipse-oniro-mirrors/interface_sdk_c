/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
 * @since 11
 * @version 1.0
 */
/**
 * @file drawing_rect.h
 *
 * @brief This file declares the functions related to the rectangle in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_RECT_H
#define C_INCLUDE_DRAWING_RECT_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于创建一个矩形对象，不会对设置的坐标排序，即允许矩形设置的左上角坐标大于对应的矩形右下角坐标。
 *
 * @param left 矩形左上角的横坐标。
 * @param top 矩形左上角的纵坐标。
 * @param right 矩形右下角的横坐标。
 * @param bottom 矩形右下角的纵坐标。
 * @return 函数会返回一个指针，指针指向创建的矩形对象。
 * @since 11
 * @version 1.0
 */
OH_Drawing_Rect* OH_Drawing_RectCreate(float left, float top, float right, float bottom);

/**
 * @brief 用于判断两个矩形是否相交，若相交，将rect设置为两个矩形的交集。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * rect、other任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param rect 指向矩形对象的指针。
 * @param other 指向矩形对象的指针。
 * @return 返回两个矩形是否相交的结果。true表示这两个矩形相交，rect被设置为两个矩形的交集；false表示不相交，rect保持不变。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_RectIntersect(OH_Drawing_Rect* rect, const OH_Drawing_Rect* other);

/**
 * @brief 将两个矩形取并集。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * rect、other任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param rect 指向矩形对象的指针。
 * @param other 指向矩形对象的指针。
 * @return 返回两个矩形取并集的结果。true表示成功，false表示失败，失败的原因可能是两个矩形至少有一个为NULL或者other矩形大小为空。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_RectJoin(OH_Drawing_Rect* rect, const OH_Drawing_Rect* other);

/**
 * @brief 用于设置矩形左上角的横坐标。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * rect为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param rect 指向矩形对象的指针。
 * @param left 矩形左上角的横坐标。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RectSetLeft(OH_Drawing_Rect* rect, float left);

/**
 * @brief 用于设置矩形左上角的纵坐标。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * rect为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param rect 指向矩形对象的指针。
 * @param top 矩形左上角的纵坐标。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RectSetTop(OH_Drawing_Rect* rect, float top);

/**
 * @brief 用于设置矩形右下角的横坐标。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * rect为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param rect 指向矩形对象的指针。
 * @param right 矩形右下角的横坐标。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RectSetRight(OH_Drawing_Rect* rect, float right);

/**
 * @brief 用于设置矩形右下角的纵坐标。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * rect为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param rect 指向矩形对象的指针。
 * @param bottom 矩形右下角的纵坐标。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RectSetBottom(OH_Drawing_Rect* rect, float bottom);

/**
 * @brief 用于获取给矩形设置的左上角的横坐标。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * rect为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param rect 指向矩形对象的指针。
 * @return 矩形左上角的横坐标。
 * @since 12
 * @version 1.0
 */
float OH_Drawing_RectGetLeft(OH_Drawing_Rect* rect);

/**
 * @brief 用于获取给矩形设置的左上角的纵坐标。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * rect为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param rect 指向矩形对象的指针。
 * @return 矩形左上角的纵坐标。
 * @since 12
 * @version 1.0
 */
float OH_Drawing_RectGetTop(OH_Drawing_Rect* rect);

/**
 * @brief 用于获取给矩形设置的右下角的横坐标。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * rect为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param rect 指向矩形对象的指针。
 * @return 矩形右下角的横坐标。
 * @since 12
 * @version 1.0
 */
float OH_Drawing_RectGetRight(OH_Drawing_Rect* rect);

/**
 * @brief 用于获取给矩形设置的右下角的纵坐标。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * rect为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param rect 指向矩形对象的指针。
 * @return 矩形右下角的纵坐标。
 * @since 12
 * @version 1.0
 */
float OH_Drawing_RectGetBottom(OH_Drawing_Rect* rect);

/**
 * @brief 用于获取矩形对象高度，计算方式为设置的矩形的右下角纵坐标减去左上角纵坐标。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * rect为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @return 返回矩形对象的高度，单位为像素。
 * @param rect 指向矩形对象的指针。
 * @since 12
 * @version 1.0
 */
float OH_Drawing_RectGetHeight(OH_Drawing_Rect* rect);

/**
 * @brief 用于获取矩形对象的宽度，计算方式为设置的矩形的右下角横坐标减去左上角横坐标。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * rect为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param rect 指向矩形对象的指针。
 * @return 返回矩形对象的宽度，单位为像素。
 * @since 12
 * @version 1.0
 */
float OH_Drawing_RectGetWidth(OH_Drawing_Rect* rect);

/**
 * @brief 用于将源矩形对象复制到目标矩形对象。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * src、dst任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param src 指向源矩形对象的指针。
 * @param dst 指向目标矩形对象的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RectCopy(OH_Drawing_Rect* src, OH_Drawing_Rect* dst);

/**
 * @brief 用于销毁矩形对象并回收该对象占有的内存。
 *
 * @param rect 指向矩形对象的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_RectDestroy(OH_Drawing_Rect* rect);

/**
 * @brief 用于创建一个矩形数组对象，用来存储多个矩形对象。不再需要{@link OH_Drawing_Array}时，请使用{@link OH_Drawing_RectDestroyArray}接口释放该对象的指针。
 *
 * @param size 指定矩形数组的大小，不超过字形索引数量最大值65536。
 * @return 返回创建的数组对象{@link OH_Drawing_Array}指针，如果返回的对象指针为空，表示创建失败。
 * 失败的原因可能为：没有可用的内存或参数错误。
 * @since 18
 * @version 1.0
 */
OH_Drawing_Array* OH_Drawing_RectCreateArray(size_t size);

/**
 * @brief 用于获取矩形数组对象{@link OH_Drawing_Array}的大小。
 *
 * @param rectArray 指向矩形数组对象{@link OH_Drawing_Array}的指针。
 * @param pSize 指向size_t类型的指针，用于存储矩形数组大小，作为出参使用。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数rectArray或者pSize为空。
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RectGetArraySize(OH_Drawing_Array* rectArray, size_t* pSize);

/**
 * @brief 用于获取矩形数组对象中指定索引的矩形对象。
 *
 * @param rectArray 指向矩形数组对象{@link OH_Drawing_Array}的指针。
 * @param index 矩形数组的索引。
 * @param rect 指向{@link OH_Drawing_Rect}的二级指针，作为出参，返回给调用者。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数rectArray或者rect为空，或者index越界。
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RectGetArrayElement(OH_Drawing_Array* rectArray, size_t index,
    OH_Drawing_Rect** rect);

/**
 * @brief 用于销毁矩形数组对象并回收该对象占有的内存。
 *
 * @param rectArray 指向矩形数组对象{@link OH_Drawing_Array}的指针。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数rectArray为空。
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RectDestroyArray(OH_Drawing_Array* rectArray);

/**
 * @brief 用于判断一个矩形是否完全包含另外一个矩形。
 *
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。此矩形用于判断是否包含另一个矩形（other）。
 * @param other 指向矩形对象{@link OH_Drawing_Rect}的指针。此矩形用于判断是否被另一个矩形（rect）所包含。
 * @param isContains 表示一个矩形是否完全包含另外一个矩形的结果，作为出参使用。true表示rect完全包含other，false表示rect不完全包含other。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数rect或other或isContains为空。
 * @since 22
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RectContains(OH_Drawing_Rect* rect, const OH_Drawing_Rect* other, bool* isContains);

/**
 * @brief 将指定的值添加到矩形边界。
 *
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @param left 添加到矩形左边界的值（矩形左上角横坐标）。
 * @param top 添加到矩形上边界的值（矩形左上角纵坐标）。
 * @param right 添加到矩形右边界的值（矩形右下角横坐标）。
 * @param bottom 添加到矩形下边界的值（矩形右下角纵坐标）。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数rect为空。
 * @since 22
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RectInset(OH_Drawing_Rect* rect, float left, float top, float right, float bottom);

/**
 * @brief 判断矩形是否为空。
 *
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @param isEmpty 表示矩形是否为空。作为出参使用。true表示矩形为空，false表示矩形不为空。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示rect或isEmpty是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RectIsEmpty(const OH_Drawing_Rect* rect, bool* isEmpty);

/**
 * @brief 将矩形分别沿x轴方向和y轴方向偏移一定距离。
 *
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @param dx 表示在x轴上的偏移距离。正数表示沿x轴正方向偏移，负数表示沿x轴负方向偏移。
 * @param dy 表示在y轴上的偏移距离。正数表示沿y轴正方向偏移，负数表示沿y轴负方向偏移。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示rect是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RectOffset(OH_Drawing_Rect* rect, float dx, float dy);

/**
 * @brief 将矩形偏移到特定位置，并保持宽度和高度不变。
 *
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @param newLeft 表示偏移后矩形左上角的x轴坐标。
 * @param newTop 表示偏移后矩形左上角的y轴坐标。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示rect是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RectOffsetTo(OH_Drawing_Rect* rect, float newLeft, float newTop);

/**
 * @brief 将矩形置空（矩形左上角和右下角的x轴、y轴坐标都置为0）。
 *
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示rect是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RectSetEmpty(OH_Drawing_Rect* rect);

/**
 * @brief 将矩形坐标按照实际位置排序。
 *
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示rect是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RectSort(OH_Drawing_Rect* rect);

/**
 * @brief 将当前矩形设置为本矩形与另一个矩形的并集。
 *
 * @param rect 指向当前矩形对象{@link OH_Drawing_Rect}的指针。
 * @param other 指向另一个矩形对象{@link OH_Drawing_Rect}的指针。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示rect或other是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RectUnion(OH_Drawing_Rect* rect, const OH_Drawing_Rect* other);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
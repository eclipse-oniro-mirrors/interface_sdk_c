
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
 * @file drawing_text_run.h
 *
 * @brief This file declares the capabilities of runs, such as obtaining the typographic boundary and drawing.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 18
 * @version 1.0
 */

/**
 * @addtogroup Drawing
 * @{
 *
 * @brief Provides the text run capability.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 *
 * @since 18
 * @version 1.0
 */
#ifndef C_INCLUDE_DRAWING_TEXT_RUN_H
#define C_INCLUDE_DRAWING_TEXT_RUN_H
#include "drawing_text_declaration.h"
#include "drawing_text_typography.h"
#include "drawing_types.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取渲染单元指定范围内字形的字符索引数组，该索引是相对于整个段落的偏移。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param run 指向渲染单元{@link OH_Drawing_Run}对象的指针。
 * @param start 渲染单元内指定的开始位置，传入负数时该方法返回空指针。
 * @param length 渲染单元内指定的长度，length为0时获取渲染单元的所有字符索引数组，length小于0时该方法返回空指针。
 * @return 返回字形的字符索引数组，不再需要{@link OH_Drawing_Array}时，请使用{@link OH_Drawing_DestroyRunStringIndices}接口释放该对象的指针。
 * @since 18
 */
OH_Drawing_Array* OH_Drawing_GetRunStringIndices(OH_Drawing_Run* run, int64_t start, int64_t length);

/**
 * @brief 获取字符索引数组中指定下标的字符索引值。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param stringIndices 字符索引数组。
 * @param index 渲染单元字形的字符索引数组下标。
 * @return 返回渲染单元单个字形的字符索引。
 * @since 18
 */
uint64_t OH_Drawing_GetRunStringIndicesByIndex(OH_Drawing_Array* stringIndices, size_t index);

/**
 * @brief 释放字形的字符索引数组对象指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param stringIndices 字符索引数组。
 * @since 18
 */
void OH_Drawing_DestroyRunStringIndices(OH_Drawing_Array* stringIndices);

/**
 * @brief 获取渲染单元生成字形的字符范围。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param run 指向渲染单元{@link OH_Drawing_Run}对象的指针。
 * @param location 表示渲染单元字形的字符范围的开始位置，该位置是相对于整个段落的偏移。
 * @param length 表示渲染单元字符范围的长度。
 * @since 18
 */
void OH_Drawing_GetRunStringRange(OH_Drawing_Run* run, uint64_t* location, uint64_t* length);

/**
 * @brief 获取渲染单元的排版边界。文本排版边界与字符本身无关，与排版字号和字体有关。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param run 指向渲染单元{@link OH_Drawing_Run}对象的指针。
 * @param ascent 渲染单元中最高字符到基准线的距离。
 * @param descent 渲染单元中最低字符到基准线的距离。
 * @param leading 渲染单元行间距。
 * @return 返回渲染单元排版宽度。
 * @since 18
 */
float OH_Drawing_GetRunTypographicBounds(OH_Drawing_Run* run, float* ascent, float* descent, float* leading);

/**
 * @brief 在画布上绘制渲染单元包含的文本。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param canvas 指向画布{@link OH_Drawing_Canvas}对象的指针。
 * @param run 指向渲染单元{@link OH_Drawing_Run}对象的指针。
 * @param x 渲染单元x坐标。
 * @param y 渲染单元y坐标。
 * @since 18
 */
void OH_Drawing_RunPaint(OH_Drawing_Canvas* canvas, OH_Drawing_Run* run, double x, double y);

/**
 * @brief 获取渲染单元的图像边界，文本图像边界与字符本身有关，相当于视觉边界。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param run 指向渲染单元{@link OH_Drawing_Run}对象的指针。
 * @return 返回指向渲染单元图像边界{@link OH_Drawing_Rect}对象的指针，不再需要{@link OH_Drawing_Rect}时，请使用
 *     {@link OH_Drawing_DestroyRunImageBounds}接口释放该对象的指针。
 * @since 18
 */
OH_Drawing_Rect* OH_Drawing_GetRunImageBounds(OH_Drawing_Run* run);

/**
 * @brief 释放渲染单元图像边界对象指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param rect 指向渲染单元图像边界{@link OH_Drawing_Rect}对象的指针。
 * @since 18
 */
void OH_Drawing_DestroyRunImageBounds(OH_Drawing_Rect* rect);

/**
 * @brief 获取渲染单元指定范围内的字形数组。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param run 指向渲染单元{@link OH_Drawing_Run}对象的指针。
 * @param start 渲染单元内指定的开始位置，传入负数时该方法返回空指针。
 * @param length 渲染单元内指定的长度，length为0时获取渲染单元的所有字符索引，length小于0时该方法返回空指针。
 * @return 返回指向渲染单元字形数组{@link OH_Drawing_Array}对象的指针，不再需要{@link OH_Drawing_Array}时，请使用
 *     {@link OH_Drawing_DestroyRunGlyphs}接口释放该对象的指针。
 * @since 18
 */
OH_Drawing_Array* OH_Drawing_GetRunGlyphs(OH_Drawing_Run* run, int64_t start, int64_t length);

/**
 * @brief 根据索引获取渲染单元单个字形。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param glyphs 指向渲染单元字形数组{@link OH_Drawing_Array}对象的指针。
 * @param index 渲染单元字形数组下标。
 * @return 渲染单元单个字形。
 * @since 18
 * @version 1.0
 */
uint16_t OH_Drawing_GetRunGlyphsByIndex(OH_Drawing_Array* glyphs, size_t index);

/**
 * @brief 释放渲染单元字形数组对象指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param glyphs 指向渲染单元字形数组{@link OH_Drawing_Array}对象的指针。
 * @since 18
 */
void OH_Drawing_DestroyRunGlyphs(OH_Drawing_Array* glyphs);

/**
 * @brief 获取渲染单元指定范围内字形的位置。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param run 指向渲染单元{@link OH_Drawing_Run}对象的指针。
 * @param start 渲染单元内指定的开始位置，传入负数时该方法返回空指针。
 * @param length 渲染单元内指定的长度，length为0时获取渲染单元的所有字符索引，length小于0时该方法返回空指针。
 * @return 返回指向渲染单元字形位置数组{@link OH_Drawing_Array}对象的指针，不再需要{@link OH_Drawing_Array}时，请使用
 *     {@link OH_Drawing_DestroyRunPositions}接口释放该对象的指针。
 * @since 18
 */
OH_Drawing_Array* OH_Drawing_GetRunPositions(OH_Drawing_Run* run, int64_t start, int64_t length);

/**
 * @brief 根据索引获取渲染单元中单个字形位置。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param positions 指向渲染单元字形位置数组{@link OH_Drawing_Array}对象的指针。
 * @param index 渲染单元字形位置数组下标。
 * @return 返回指向渲染单元单个字形位置{@link OH_Drawing_Point}对象的指针。
 * @since 18
 * @version 1.0
 */
OH_Drawing_Point* OH_Drawing_GetRunPositionsByIndex(OH_Drawing_Array* positions, size_t index);

/**
 * @brief 释放渲染单元字形位置数组对象指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param positions 指向渲染单元字形位置数组{@link OH_Drawing_Array}对象的指针。
 * @since 18
 */
void OH_Drawing_DestroyRunPositions(OH_Drawing_Array* positions);

/**
 * @brief 获取渲染单元字形数量。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param run 指向渲染单元{@link OH_Drawing_Run}对象的指针。
 * @return 返回渲染单元字形数量。
 * @since 18
 */
uint32_t OH_Drawing_GetRunGlyphCount(OH_Drawing_Run* run);

/**
 * @brief 获取渲染单元字体对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param run 指向渲染单元{@link OH_Drawing_Run}对象的指针。
 * @return 返回指向渲染单元字体{@link OH_Drawing_Font}对象的指针，不再需要{@link OH_Drawing_Font}时，请使用{@link OH_Drawing_FontDestroy}
 *     接口释放该对象的指针。
 * @since 20
 * @version 1.0
 */
OH_Drawing_Font* OH_Drawing_GetRunFont(OH_Drawing_Run* run);

/**
 * @brief 获取渲染单元文本方向。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param run 指向渲染单元{@link OH_Drawing_Run}对象的指针。
 * @return 返回渲染单元的文本方向。0为TEXT_DIRECTION_RTL，方向为从右到左；1为TEXT_DIRECTION_LTR，方向为从左到右，具体可见{@link OH_Drawing_TextDirection}枚举。
 * @since 20
 */
OH_Drawing_TextDirection OH_Drawing_GetRunTextDirection(OH_Drawing_Run* run);

/**
 * @brief 获取渲染单元字形宽度数组。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param run 指向渲染单元{@link OH_Drawing_Run}对象的指针。
 * @param start 渲染单元内指定的开始位置，传入负数时该方法返回空指针。
 * @param length 渲染单元内指定的长度，如果length是0表示从start开始获取到渲染单元结束，length小于0时该方法返回空指针。
 * @return 返回指向渲染单元字形宽度数组{@link OH_Drawing_Array}对象的指针，不再需要{@link OH_Drawing_Array}时，请使用
 *     {@link OH_Drawing_DestroyRunGlyphAdvances}接口释放该对象的指针。
 * @since 20
 */
OH_Drawing_Array* OH_Drawing_GetRunGlyphAdvances(OH_Drawing_Run* run, uint32_t start, uint32_t length);

/**
 * @brief 根据索引获取渲染单元中单个字形宽度。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param advances 指向渲染单元字形宽度数组{@link OH_Drawing_Array}对象的指针。
 * @param index 渲染单元字形宽度数组的下标。
 * @return 返回指向渲染单元单个字形宽度{@link OH_Drawing_Point}对象的指针。其中，{@link OH_Drawing_Point}对象的x值代表渲染单元单个字形宽度，y值为保留字段，默认返回0。
 * @since 20
 */
OH_Drawing_Point* OH_Drawing_GetRunGlyphAdvanceByIndex(OH_Drawing_Array* advances, size_t index);

/**
 * @brief 释放渲染单元字形宽度数组对象的指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param advances 指向渲染单元字形宽度数组{@link OH_Drawing_Array}对象的指针。
 * @since 20
 */
void OH_Drawing_DestroyRunGlyphAdvances(OH_Drawing_Array* advances);
#ifdef __cplusplus
}
#endif

/** @} */
#endif // C_INCLUDE_DRAWING_TEXT_RUN_H
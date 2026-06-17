
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
 * @file drawing_text_line.h
 *
 * @brief This file declares the capabilities for obtaining the character position in a text line, obtaining the run
 * information, and truncating text by line.
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
 * @brief Provides the 2D drawing capability.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 *
 * @since 18
 * @version 1.0
 */
#ifndef C_INCLUDE_DRAWING_TEXT_LINE_H
#define C_INCLUDE_DRAWING_TEXT_LINE_H
#include "drawing_text_declaration.h"
#include "drawing_types.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取排版对象的文本行数组。文本行数组中包含一个或多个文本行对象。不再需要{@link OH_Drawing_Array}时，请使用{@link OH_Drawing_DestroyTextLines}
 * 接口释放该对象的指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向排版对象{@link OH_Drawing_Typography}的指针。
 * @return 指向文本行数组{@link OH_Drawing_Array}的指针。
 * @since 18
 */
OH_Drawing_Array* OH_Drawing_TypographyGetTextLines(OH_Drawing_Typography* typography);

/**
 * @brief 释放文本行数组的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lines 指向文本行数组{@link OH_Drawing_Array}的指针。
 * @since 18
 * @version 1.0
 */
void OH_Drawing_DestroyTextLines(OH_Drawing_Array* lines);

/**
 * @brief 释放单个文本行对象的内存。只能释放单独申请内存的文本行对象，不能释放文本行数组中的某一个文本行对象的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line 指向文本行对象{@link OH_Drawing_TextLine}的指针。
 * @since 18
 * @version 1.0
 */
void OH_Drawing_DestroyTextLine(OH_Drawing_TextLine* line);

/**
 * @brief 获取文本行数组指定索引处的文本行对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lines 指向文本行数组{@link OH_Drawing_Array}的指针。
 * @param index 指定的文本行数组的索引。
 * @return 指向指定索引处的文本行对象{@link OH_Drawing_TextLine}的指针。
 * @since 18
 */
OH_Drawing_TextLine* OH_Drawing_GetTextLineByIndex(OH_Drawing_Array* lines, size_t index);

/**
 * @brief 获取文本行对象中字形的数量。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line 指向文本行对象{@link OH_Drawing_TextLine}的指针。
 * @return 文本行对象中字形的数量。
 * @since 18
 * @version 1.0
 */
double OH_Drawing_TextLineGetGlyphCount(OH_Drawing_TextLine* line);

/**
 * @brief 获取文本行对象中的文本在整个段落文本中的索引区间。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line 指向文本行对象{@link OH_Drawing_TextLine}的指针。
 * @param start 指向区间左侧端点索引的指针。
 * @param end 指向区间右侧端点索引的指针。
 * @since 18
 * @version 1.0
 */
void OH_Drawing_TextLineGetTextRange(OH_Drawing_TextLine* line, size_t* start, size_t* end);

/**
 * @brief 获取文本行对象中的文本渲染单元数组。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line 指向文本行对象{@link OH_Drawing_TextLine}的指针。
 * @return 指向文本渲染单元{@link OH_Drawing_Run}数组{@link OH_Drawing_Array}的指针，不再需要{@link OH_Drawing_Array}时，请使用
 *     {@link OH_Drawing_DestroyRuns}释放该对象的指针。
 * @since 18
 * @version 1.0
 */
OH_Drawing_Array* OH_Drawing_TextLineGetGlyphRuns(OH_Drawing_TextLine* line);

/**
 * @brief 释放文本渲染单元数组的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param runs 指向文本渲染单元{@link OH_Drawing_Run}数组{@link OH_Drawing_Array}的指针。
 * @since 18
 * @version 1.0
 */
void OH_Drawing_DestroyRuns(OH_Drawing_Array* runs);

/**
 * @brief 获取文本渲染单元数组指定索引处的文本渲染单元对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param runs 指向文本渲染单元{@link OH_Drawing_Run}数组{@link OH_Drawing_Array}的指针。
 * @param index 文本渲染单元数组的索引。
 * @return 指向指定索引处的文本渲染单元对象{@link OH_Drawing_Run}的指针。
 * @since 18
 */
OH_Drawing_Run* OH_Drawing_GetRunByIndex(OH_Drawing_Array* runs, size_t index);

/**
 * @brief 在画布上以坐标点 (x, y) 为左上角位置绘制文本行。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line 指向文本行对象{@link OH_Drawing_TextLine}的指针。
 * @param canvas 指向绘制的目标画布{@link OH_Drawing_Canvas}。
 * @param x 绘制的左上角位置的横坐标，单位为物理像素px。
 * @param y 绘制的左上角位置的纵坐标，单位为物理像素px。
 * @since 18
 * @version 1.0
 */
void OH_Drawing_TextLinePaint(OH_Drawing_TextLine* line, OH_Drawing_Canvas* canvas, double x, double y);

/**
 * @brief 创建一个截断的文本行对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line 指向文本行对象{@link OH_Drawing_TextLine}的指针。
 * @param width 截断后的行宽度。
 * @param mode 截断的类型，取值对应为 {@link OH_Drawing_EllipsisModal} 枚举，当前仅支持头部截断ELLIPSIS_MODAL_HEAD和尾部截断ELLIPSIS_MODAL_TAIL。
 * @param ellipsis 截断的标记字符串。
 * @return 返回指向截断的文本行对象{@link OH_Drawing_TextLine}指针。
 * @since 18
 * @version 1.0
 */
OH_Drawing_TextLine* OH_Drawing_TextLineCreateTruncatedLine(OH_Drawing_TextLine* line, double width, int mode,
    const char* ellipsis);

/**
 * @brief 获取文本行对象的排版边界。文本行排版边界与排版字体、排版字号有关，与字符本身无关。
 * 例如字符串为" a b "，'a'字符前面有1个空格，'b'字符后面有1个空格，排版边界就包括行首和末尾空格的边界。例如字符串为"j"或"E"，排版边界相同，即与字符本身无关。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line 指向文本行对象{@link OH_Drawing_TextLine}的指针。height = ascent + descent + leading。
 * @param ascent 指向文本行对象上升高度的指针。
 * @param descent 指向文本行对象下降高度的指针。
 * @param leading 指向文本行对象行间距的指针。
 * @return 排版边界的总宽度。
 * @since 18
 * @version 1.0
 */
double OH_Drawing_TextLineGetTypographicBounds(OH_Drawing_TextLine* line, double* ascent, double* descent,
    double* leading);

/**
 * @brief 获取文本行对象的图像边界。文本行图像边界与排版字体、排版字号、字符本身都有关，相当于视觉边界。
 * 例如字符串为" a b "，'a'字符前面有1个空格，'b'字符后面有1个空格,用户在界面上只能看到"a b"，图像边界即为不包括带行首和末尾空格的边界。
 * 例如字符串为"j"或"E"，视觉边界不同，即与字符本身有关，"j"字符串的视觉边界宽度小于"E"字符串的视觉边界宽度，"j"字符串的视觉边界高度大于"E"字符串的视觉边界高度。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line 指向文本行对象{@link OH_Drawing_TextLine}的指针。
 * @return 指向文本行对象的图像边界{@link OH_Drawing_Rect}的指针，不再需要{@link OH_Drawing_Rect}时，请使用{@link OH_Drawing_RectDestroy}
 *     接口释放该对象的指针。
 * @since 18
 * @version 1.0
 */
OH_Drawing_Rect* OH_Drawing_TextLineGetImageBounds(OH_Drawing_TextLine* line);

/**
 * @brief 获取文本行对象尾部空白字符的宽度。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line 指向文本行对象{@link OH_Drawing_TextLine}的指针。
 * @return 文本行对象尾部空白字符的宽度。
 * @since 18
 * @version 1.0
 */
double OH_Drawing_TextLineGetTrailingSpaceWidth(OH_Drawing_TextLine* line);

/**
 * @brief 获取文本行对象中指定位置处的字符索引。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line 指向文本行对象{@link OH_Drawing_TextLine}的指针。
 * @param point 指向要查找索引的位置{@link OH_Drawing_Point}指针。
 * @return 指定位置处的字符串索引。例如文本字符串为"abc"，"a"字符的索引为0，"b"字符的索引为1，"c"字符的索引为2。如果指定的位置在"a"字符处，则返回0。
 * @since 18
 */
int32_t OH_Drawing_TextLineGetStringIndexForPosition(OH_Drawing_TextLine* line, OH_Drawing_Point* point);

/**
 * @brief 获取文本行对象中指定字符串索引处的偏移量。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line 指向文本行对象{@link OH_Drawing_TextLine}的指针。
 * @param index 要获取偏移量的字符串索引。
 * @return 指定字符串索引处的偏移量。
 * @since 18
 */
double OH_Drawing_TextLineGetOffsetForStringIndex(OH_Drawing_TextLine* line, int32_t index);

/**
 * @brief Defines a custom callback used to receive the offset and index of each character in a text line object
 * as its parameters.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param offset Offset of each character in the text line object.
 * @param index Index of each character in the text line object.
 * @param leadingEdge Whether the cursor is located at the leading edge of a character. **true** means that the
 *     cursor is located at the front of the character, that is, the offset does not contain the character width.
 *     **false** means that the cursor is located at the rear of the character, that is, the offset contains the
 *     character width.
 * @return Whether to stop calling the callback. **true** means to stop; **false** otherwise.
 * @since 18
 * @version 1.0
 */
typedef bool (*Drawing_CaretOffsetsCallback)(double offset, int32_t index, bool leadingEdge);

/**
 * @brief 枚举文本行对象中每个字符的偏移量和索引值，传递给用户自定义的回调函数，用户可以使用偏移量和索引值进行其他操作。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line 指向文本行对象{@link OH_Drawing_TextLine}的指针。
 * @param callback 用户自定义函数{@link Drawing_CaretOffsetsCallback}。
 * @since 18
 */
void OH_Drawing_TextLineEnumerateCaretOffsets(OH_Drawing_TextLine* line, Drawing_CaretOffsetsCallback callback);

/**
 * @brief 获取文本行对象根据对齐因子和对齐宽度计算对齐后所需的偏移量。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line 指向文本行对象{@link OH_Drawing_TextLine}的指针。
 * @param alignmentFactor 对齐因子，即对齐的程度。小于等于0.0表示左对齐，大于0.0小于0.5表示偏左对齐，0.5表示居中对齐，大于0.5小于1.0表示偏右对齐，大于等于1.0表示右对齐。
 * @param alignmentWidth 对齐宽度，即最终偏移后的文本行对象右下角相对于起始位置的偏移值。如果指定对齐宽度小于文本行对象的实际宽度，则返回0。
 * @return 计算得到的对齐所需偏移量。
 * @since 18
 * @version 1.0
 */
double OH_Drawing_TextLineGetAlignmentOffset(OH_Drawing_TextLine* line, double alignmentFactor, double alignmentWidth);
#ifdef __cplusplus
}
#endif

/** @} */
#endif // C_INCLUDE_DRAWING_TEXT_LINE_H
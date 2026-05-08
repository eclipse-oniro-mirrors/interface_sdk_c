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

#ifndef C_INCLUDE_DRAWING_TEXT_LINE_H
#define C_INCLUDE_DRAWING_TEXT_LINE_H

#include "drawing_text_declaration.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Obtains the array of text lines in a typography object. This array contains one or more text line objects.
 * Release this pointer by calling {@link OH_Drawing_DestroyTextLines} when this object is no longer needed.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object.
 * @return Pointer to the {@link OH_Drawing_Array} object.
 * @since 18
 */
OH_Drawing_Array* OH_Drawing_TypographyGetTextLines(OH_Drawing_Typography* typography);

/**
 * @brief Releases the memory occupied by a text line array.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lines Pointer to the {@link OH_Drawing_Array} object.
 * @since 18
 * @version 1.0
 */
void OH_Drawing_DestroyTextLines(OH_Drawing_Array* lines);

/**
 * @brief Releases the memory occupied by a text line object. This is applicable only to text line objects that have
 * requested memory on their own and not to a particular text line object within a text line array.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @since 18
 * @version 1.0
 */
void OH_Drawing_DestroyTextLine(OH_Drawing_TextLine* line);

/**
 * @brief Obtains the text line object with the specified index in a text line array.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lines Pointer to the {@link OH_Drawing_Array} object.
 * @param index Index of the text line array.
 * @return Returns a pointer to the {@link OH_Drawing_TextLine} object at the specified index.
 * @since 18
 */
OH_Drawing_TextLine* OH_Drawing_GetTextLineByIndex(OH_Drawing_Array* lines, size_t index);

/**
 * @brief Obtains the number of glyphs in a text line object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @return Returns the number of glyphs in the text line object.
 * @since 18
 * @version 1.0
 */
double OH_Drawing_TextLineGetGlyphCount(OH_Drawing_TextLine* line);

/**
 * @brief Obtains the range of the text in a text line object in the entire paragraph.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @param start Pointer to the start of the range.
 * @param end Pointer to the end of the range.
 * @since 18
 * @version 1.0
 */
void OH_Drawing_TextLineGetTextRange(OH_Drawing_TextLine* line, size_t* start, size_t* end);

/**
 * @brief Obtains the array of glyph runs in a text line object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @return Returns a pointer to the {@link OH_Drawing_Array} array, which holds multiple {@link OH_Drawing_Run} objects.
 *      Release this pointer by calling {@link OH_Drawing_DestroyRuns} when this object is no longer needed.
 * @since 18
 * @version 1.0
 */
OH_Drawing_Array* OH_Drawing_TextLineGetGlyphRuns(OH_Drawing_TextLine* line);

/**
 * @brief Releases the memory occupied by a glyph run array.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param runs Pointer to the {@link OH_Drawing_Array} array, which holds multiple {@link OH_Drawing_Run} objects.
 * @since 18
 * @version 1.0
 */
void OH_Drawing_DestroyRuns(OH_Drawing_Array* runs);

/**
 * @brief Obtains the glyph run object with the specified index in a glyph run array.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param runs Pointer to the {@link OH_Drawing_Array} array, which holds multiple {@link OH_Drawing_Run} objects.
 * @param index Index of the glyph run array.
 * @return Returns a pointer to the {@link OH_Drawing_Run} object at the specified index.
 * @since 18
 */
OH_Drawing_Run* OH_Drawing_GetRunByIndex(OH_Drawing_Array* runs, size_t index);

/**
 * @brief Paints a text line on the canvas with the coordinate point (x, y) as the upper left corner.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @param canvas Pointer to the target canvas {@link OH_Drawing_Canvas}.
 * @param x Horizontal coordinate of the upper left corner, in px.
 * @param y Vertical coordinate of the upper left corner, in px.
 * @since 18
 * @version 1.0
 */
void OH_Drawing_TextLinePaint(OH_Drawing_TextLine* line, OH_Drawing_Canvas* canvas, double x, double y);

/**
 * @brief Creates a truncated text line object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @param width Line width after truncation.
 * @param mode Truncation type. The value is an enumerated value of {@link OH_Drawing_EllipsisModal}. Currently, only **
 *     ELLIPSIS_MODAL_HEAD** and **ELLIPSIS_MODAL_TAIL** are supported.
 * @param ellipsis Pointer to the string used to mark a truncation.
 * @return Returns a pointer to the {@link OH_Drawing_TextLine} object of the truncated text line.
 * @since 18
 * @version 1.0
 */
OH_Drawing_TextLine* OH_Drawing_TextLineCreateTruncatedLine(OH_Drawing_TextLine* line, double width, int mode,
    const char* ellipsis);

/**
 * @brief Obtains the typographic boundary of a text line object. The typographic boundary is related to the font and
 * font size used for typography, but not the characters within the text.
 * For example, for the string " a b " (which has a space before "a" and a space after "b"), the typographic boundary
 * encompasses the spaces at the beginning and end. Similarly, the strings "j" and "E" have identical typographic
 * boundaries, which are independent of the characters themselves.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object. height = ascent + descent + leading.
 * @param ascent Pointer to the ascent of the text line object.
 * @param descent Pointer to the descent of the text line object.
 * @param leading Pointer to the leading of the text line object.
 * @return Returns the total width of the layout boundary.
 * @since 18
 * @version 1.0
 */
double OH_Drawing_TextLineGetTypographicBounds(OH_Drawing_TextLine* line, double* ascent, double* descent,
    double* leading);

/**
 * @brief Obtains the image boundary of a text line object. The image boundary, equivalent to a visual boundary, is
 * related to the font, font size, and characters.
 * For example, for the string " a b " (which has a space before "a" and a space after "b"), only "a b" are visible to
 * users, and therefore the image boundary does not include these spaces at the beginning and end.
 * For the strings "j" and "E", their image boundaries are different. Specifically, the width of the boundary for "j"
 * is narrower than that for "E", and the height of the boundary for "j" is taller than that for "E".
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @return Returns the pointer to {@link OH_Drawing_Rect} of the text line object. Release this pointer by calling
 *     {@link OH_Drawing_RectDestroy} when this object is no longer needed.
 * @since 18
 * @version 1.0
 */
OH_Drawing_Rect* OH_Drawing_TextLineGetImageBounds(OH_Drawing_TextLine* line);

/**
 * @brief Obtains the width of the spaces at the end of a text line object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @return Returns the pointer to the width of the spaces.
 * @since 18
 * @version 1.0
 */
double OH_Drawing_TextLineGetTrailingSpaceWidth(OH_Drawing_TextLine* line);

/**
 * @brief Obtains the index of a character at the specified position in a text line object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @param point Pointer to the index specified, which is an {@link OH_Drawing_Point} object.
 * @return Returns the index of the character. For example, for the string "abc", the index of "a" is 0, the index of "
 *     b" is 1, and the index of "c" is 2. If the specified position is at "a", then **0** is returned.
 * @since 18
 */
int32_t OH_Drawing_TextLineGetStringIndexForPosition(OH_Drawing_TextLine* line, OH_Drawing_Point* point);

/**
 * @brief Obtains the offset of a character with the specified index in a text line object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @param index Index of the character.
 * @return Returns the offset.
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
 * @brief Enumerates the offset and index of each character in a text line object and passes them to a custom callback
 * function. You can use the offset and index array for other operations.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @param callback User-defined function {@link Drawing_CaretOffsetsCallback}.
 * @since 18
 */
void OH_Drawing_TextLineEnumerateCaretOffsets(OH_Drawing_TextLine* line, Drawing_CaretOffsetsCallback callback);

/**
 * @brief Obtains the offset of a text line object after alignment based on the alignment factor and alignment width.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @param alignmentFactor Alignment factor, which determines how text is aligned. A value less than or equal to 0.0
 *     means that the text is left-aligned; a value between 0.0 and 0.5 means that the text is slightly left-aligned;
 *     the value 0.5 means that the text is centered; a value between 0.5 and 1 means that the text is slightly right-
 *     aligned; a value greater than or equal to 1.0 means that the text is right-aligned.
 * @param alignmentWidth Alignment width, that is, the offset of the lower right corner of the text line object
 *     relative to the start position. If the specified alignment width is less than the actual width of the text line
 *     object, **0** is returned.
 * @return Returns the offset obtained.
 * @since 18
 * @version 1.0
 */
double OH_Drawing_TextLineGetAlignmentOffset(OH_Drawing_TextLine* line, double alignmentFactor, double alignmentWidth);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // C_INCLUDE_DRAWING_TEXT_LINE_H
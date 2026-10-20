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
 * @return Pointer to the text line array {@link OH_Drawing_Array}. <br>Returns NULL when typography is NULL.
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
 * @brief Releases the memory of a single text line object. Only the memory of a text line object that is independently
 * allocated can be released. The memory of a text line object obtained from a line array through
 * {@link OH_Drawing_GetTextLineByIndex} cannot be released.
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
 * @return Pointer to the {@link OH_Drawing_TextLine} text line object at the specified index. <br>Returns NULL if
 *     lines is NULL or the index is out of bounds.
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
 * @brief Obtains the array of text rendering units {@link OH_Drawing_Run} in the text line object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @return Pointer to the {@link OH_Drawing_Array} array of text rendering units {@link OH_Drawing_Run}. When the
 *     {@link OH_Drawing_Array} is no longer needed, please use the {@link OH_Drawing_DestroyRuns} API to release the
 *     pointer of the object.
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
 * @return Pointer to the text rendering unit object {@link OH_Drawing_Run} at the specified index. <br>NULL is
 *     returned if runs is NULL or the index is out of bounds.
 * @since 18
 */
OH_Drawing_Run* OH_Drawing_GetRunByIndex(OH_Drawing_Array* runs, size_t index);

/**
 * @brief Paints a text line on the canvas with the coordinate point (x, y) as the upper left corner.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @param canvas Pointer to the target canvas for drawing, which is an {@link OH_Drawing_Canvas}.
 * @param x Horizontal coordinate of the upper left corner, in px.
 * @param y Vertical coordinate of the upper left corner, in px.
 * @since 18
 * @version 1.0
 */
void OH_Drawing_TextLinePaint(OH_Drawing_TextLine* line, OH_Drawing_Canvas* canvas, double x, double y);

/**
 * @brief Creates a truncated text line object. Truncates the original text line based on the specified width,
 * truncation type, and truncation mark string, inserts the specified mark string at the truncation position, and
 * generates and returns a new independent text line object. The original text is not affected.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @param width Width of the truncated line, in physical pixels (px).
 * @param mode Truncation type. The value is an enumerated value of {@link OH_Drawing_EllipsisModal}. Currently, only **
 *     ELLIPSIS_MODAL_HEAD** and **ELLIPSIS_MODAL_TAIL** are supported.
 * @param ellipsis Pointer to the string used to mark a truncation.
 * @return Pointer to the truncated text line object {@link OH_Drawing_TextLine}. <br>NULL is returned when line or
 *     ellipsis is NULL. <br>Please use {@link OH_Drawing_DestroyTextLine} to release the object's memory when it is no
 *     longer needed.
 * @since 18
 * @version 1.0
 */
OH_Drawing_TextLine* OH_Drawing_TextLineCreateTruncatedLine(OH_Drawing_TextLine* line, double width, int mode,
    const char* ellipsis);

/**
 * @brief Obtains the typographic bounds of the text line object. The typographic bounds of a text line are related to
 * the typographic font and typographic font size, and are independent of the characters themselves.
 * <br>For example, for the string " a b ", where there is one space before the 'a' character and one space after the '
 * b' character, the typographic bounds include the bounds of the leading and trailing spaces. For example, for the
 * string "j" or "E", the typographic bounds are the same, i.e., independent of the characters themselves.
 * <br>The text height can be calculated using height = ascent + descent + leading.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the text line object {@link OH_Drawing_TextLine}.
 * @param ascent Pointer to the ascent height of the text line object. The unit is physical pixel.
 * @param descent Pointer to the descent height of the text line object. The unit is physical pixel.
 * @param leading Pointer to the leading of the text line object. The unit is physical pixel.
 * @return Total width of the typographic bounds, in physical pixels.
 * @since 18
 * @version 1.0
 */
double OH_Drawing_TextLineGetTypographicBounds(OH_Drawing_TextLine* line, double* ascent, double* descent,
    double* leading);

/**
 * @brief Obtains the image bounds of the text line object. The image bounds of a text line are related to the
 * typographic font, typographic font size, and the characters themselves, and are equivalent to the visual bounds.
 * <br>For example, for the string " a b ", where there is one space before the 'a' character and one space after the '
 * b' character, the user can only see "a b" on the UI, and the image bounds are the bounds excluding the leading and
 * trailing spaces.
 * <br>For example, for the string "j" or "E", the visual bounds are different, i.e., related to the characters
 * themselves. The visual bounds width of the string "j" is smaller than that of the string "E", and the visual bounds
 * height of the string "j" is greater than that of the string "E".
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @return Pointer to the image bounds {@link OH_Drawing_Rect} of the text line object. <br>Returns NULL when the
 *     passed-in line is NULL. <br>When the {@link OH_Drawing_Rect} is no longer needed, please use the
 *     {@link OH_Drawing_RectDestroy} API to release the pointer of the object.
 * @since 18
 * @version 1.0
 */
OH_Drawing_Rect* OH_Drawing_TextLineGetImageBounds(OH_Drawing_TextLine* line);

/**
 * @brief Obtains the width of the spaces at the end of a text line object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @return Width of the trailing whitespace characters of the text line object, in physical pixels (px).
 * @since 18
 * @version 1.0
 */
double OH_Drawing_TextLineGetTrailingSpaceWidth(OH_Drawing_TextLine* line);

/**
 * @brief Obtains the string index at the specified position in the text line object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param line Pointer to the {@link OH_Drawing_TextLine} object.
 * @param point Pointer to the position {@link OH_Drawing_Point} where the index is to be found.
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
 * @return Offset at the specified string index, in physical pixels (px).
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
 * @param alignmentFactor Alignment factor. A value less than or equal to 0.0 indicates left alignment, greater than 0.
 *     0 and less than 0.5 indicates left-biased alignment, 0.5 indicates center alignment, greater than 0.5 and less
 *     than 1.0 indicates right-biased alignment, and greater than or equal to 1.0 indicates right alignment.
 * @param alignmentWidth Alignment width, i.e., the offset of the bottom-right corner of the text line object relative
 *     to the starting position after final offset, in physical pixels (px). If the specified alignment width is less
 *     than the actual width of the text line object, 0 is returned.
 * @return Calculated offset required for alignment. The unit is physical pixel (px).
 * @since 18
 * @version 1.0
 */
double OH_Drawing_TextLineGetAlignmentOffset(OH_Drawing_TextLine* line, double alignmentFactor, double alignmentWidth);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // C_INCLUDE_DRAWING_TEXT_LINE_H
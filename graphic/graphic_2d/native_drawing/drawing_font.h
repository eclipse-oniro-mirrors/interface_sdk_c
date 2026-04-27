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
 * @since 11
 * @version 1.0
 */
/**
 * @file drawing_font.h
 *
 * @brief This file declares the functions related to the font in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_FONT_H
#define C_INCLUDE_DRAWING_FONT_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an **OH_Drawing_Font** object.
 *
 * @return Returns the pointer to the **OH_Drawing_Font** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_Font* OH_Drawing_FontCreate(void);

/**
 * @brief Defines an enum for the font hinting types.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * No font hinting is used.
     *
     * @since 12
     */
    FONT_HINTING_NONE,
    /**
     * Slight font hinting is used to improve contrast.
     *
     * @since 12
     */
    FONT_HINTING_SLIGHT,
    /**
     * Normal font hinting is used to improve contrast.
     *
     * @since 12
     */
    FONT_HINTING_NORMAL,
    /**
     * Full font hinting is used to improve contrast.
     *
     * @since 12
     */
    FONT_HINTING_FULL,
} OH_Drawing_FontHinting;

/**
 * @brief Enumerates the font edging types.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * No anti-aliasing processing is used.
     *
     * @since 12
     */
    FONT_EDGING_ALIAS,
    /**
     * Uses anti-aliasing to smooth the jagged edges.
     *
     * @since 12
     */
    FONT_EDGING_ANTI_ALIAS,
    /**
     * Uses sub-pixel anti-aliasing to provide a smoother effect for jagged edges.
     *
     * @since 12
     */
    FONT_EDGING_SUBPIXEL_ANTI_ALIAS,
} OH_Drawing_FontEdging;

/**
 * @brief Sets whether the font baselines and pixels alignment when the transformation matrix is axis aligned.
 *
 * @param font Indicates the pointer to an <b>OH_Drawing_Font</b> object.
 * @param baselineSnap Indicates whether the font baselines and pixels alignment.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontSetBaselineSnap(OH_Drawing_Font* font, bool baselineSnap);

/**
 * @brief Gets whether the font baselines and pixels alignment when the transformation matrix is axis aligned.
 *
 * @param font Indicates the pointer to an <b>OH_Drawing_Font</b> object.
 * @return Returns <b>true</b> if the font baselines and pixels alignment; returns <b>false</b> otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_FontIsBaselineSnap(const OH_Drawing_Font* font);

/**
 * @brief Sets whether to use sub-pixel rendering for a font.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param isSubpixel Whether sub-pixel rendering is used for a font. **true** means yes; **false** otherwise.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontSetSubpixel(OH_Drawing_Font* font, bool isSubpixel);

/**
 * @brief Checks whether sub-pixel rendering is used for a font.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @return Whether sub-pixel rendering is used for a font. **true** means yes; **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_FontIsSubpixel(const OH_Drawing_Font* font);

/**
 * @brief Sets whether to forcibly use auto hinting, that is, whether to always hint glyphs.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param isForceAutoHinting Whether to forcibly use auto hinting, that is, whether to always hint glyphs. **true**
 * means yes; **false** otherwise.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontSetForceAutoHinting(OH_Drawing_Font* font, bool isForceAutoHinting);

/**
 * @brief Checks whether auto hinting is forcibly used.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @return Whether auto hinting is forcibly used. **true** means yes; **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_FontIsForceAutoHinting(const OH_Drawing_Font* font);

/**
 * @brief Sets a typeface for a font.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to an **OH_Drawing_Font** object.
 * @param typeface Pointer to an **OH_Drawing_Typeface** object. If NULL is passed in, the default **
 * OH_Drawing_Typeface** object is used.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_FontSetTypeface(OH_Drawing_Font* font, OH_Drawing_Typeface* typeface);

/**
 * @brief Obtains the typeface of a font.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @return Returns a pointer to the {@link OH_Drawing_Typeface} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_FontGetTypeface(OH_Drawing_Font* font);

/**
 * @brief Sets the text size for a font object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to an **OH_Drawing_Font** object.
 * @param textSize Text size. The value is a floating point number. If a negative number is passed in, the size is set
 * to 0. If the size is 0, the text drawn will not be displayed.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_FontSetTextSize(OH_Drawing_Font* font, float textSize);

/**
 * @brief Obtains the text size of a font object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @return Returns a floating point number representing the text size.
 * @since 12
 * @version 1.0
 */
float OH_Drawing_FontGetTextSize(const OH_Drawing_Font* font);

/**
 * @brief Obtains the number of glyphs represented by text.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **font** or **text** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param text Pointer to the start address of the storage.
 * @param byteLength Text length, in bytes.
 * @param encoding Text encoding type {@link OH_Drawing_TextEncoding}.
 * @return Returns the number of characters represented by the text (non-negative integer) on success;
 * @since 12
 * @version 1.0
 */
int OH_Drawing_FontCountText(
    OH_Drawing_Font* font, const void* text, size_t byteLength, OH_Drawing_TextEncoding encoding);

/**
 * @brief Converts text into glyph indices.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If any of **font**, **text**, and **glyphs** is NULL, **byteLength** is **0**, or **maxGlyphCount** is less than or
 * equal to 0, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param text Pointer to the start address of the storage.
 * @param byteLength Text length, in bytes.
 * @param encoding Text encoding type {@link OH_Drawing_TextEncoding}.
 * @param glyphs Pointer to the start address for storing the glyph indices.
 * @param maxGlyphCount Maximum number of glyphs.
 * @return Returns the number of glyph indices.
 * @since 12
 * @version 1.0
 */
uint32_t OH_Drawing_FontTextToGlyphs(const OH_Drawing_Font* font, const void* text, uint32_t byteLength,
    OH_Drawing_TextEncoding encoding, uint16_t* glyphs, int maxGlyphCount);

/**
 * @brief Obtains the width of each glyph in a string of text.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If any of **font**, **glyphs**, and **widths** is NULL, or **count** is **0**, **OH_DRAWING_ERROR_INVALID_PARAMETER**
 * is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param glyphs Pointer to the start address for storing the glyph indices.
 * @param count Number of glyph indices.
 * @param widths Pointer to the start address for storing the glyph widths.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontGetWidths(const OH_Drawing_Font* font, const uint16_t* glyphs, int count, float* widths);

/**
 * @brief Measures the width of a single character. If the typeface of the current font does not support the character
 * to measure, the system typeface is used to measure the character width.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param str Pointer to the single character to measure. A string can be passed in, but only the first character in
 * the string is parsed and measured in UTF-8 encoding.
 * @param textWidth Pointer to the character width obtained.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if at least one of the parameters **font**, **str**, or **textWidth** is NULL,
 *  or the length of **str** is **0**.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontMeasureSingleCharacter(
    const OH_Drawing_Font* font, const char* str, float* textWidth);

/**
 * @brief Measures the width of a single character with font features. If the typeface of the current font does not
 * support the character to measure, the system typeface is used to measure the character width.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param str Pointer to the single character to measure. A string can be passed in, but only the first character in
 * the string is parsed and measured in UTF-8 encoding.
 * @param fontFeatures Pointer to the {@link OH_Drawing_FontFeatures} object. If no font feature is set, the preset
 * font feature in the TrueType fonts (TTF) file is used.
 * @param textWidth Pointer to the obtained text width, which is used as an output parameter.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * Returns **OH_DRAWING_ERROR_INVALID_PARAMETER** if at least one of the parameters **font**, **str**, **fontFeatures**,
 *  or **textWidth** is NULL, or the length of **str** is **0**.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontMeasureSingleCharacterWithFeatures(
    const OH_Drawing_Font* font, const char* str, const OH_Drawing_FontFeatures* fontFeatures, float* textWidth);

/**
 * @brief Obtains the text width and bounding box.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param text Pointer to the text.
 * @param byteLength Length of the text, in bytes.
 * @param encoding Encoding type of the text.
 * @param bounds Pointer to the bounding box. The value can be NULL.
 * @param textWidth Pointer to the text width.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if at least one of the parameters **font**, **text**, and **textWidth** is
 * NULL, or **byteLength** is **0**.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontMeasureText(const OH_Drawing_Font* font, const void* text, size_t byteLength,
    OH_Drawing_TextEncoding encoding, OH_Drawing_Rect* bounds, float* textWidth);

/**
 * @brief Obtains the width and bounding box of the text with a brush or pen.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param text Pointer to the text.
 * @param byteLength Length of the text, in bytes.
 * @param encoding Encoding type of the text.
 * @param brush Pointer to the {@link OH_Drawing_Brush} object.
 * @param pen Pointer to the {@link OH_Drawing_Pen} object.
 * @param bounds Pointer to the bounding box. The value can be NULL.
 * @param textWidth Pointer to the text width.
 * @return Operation code.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * Returns **OH_DRAWING_ERROR_INVALID_PARAMETER** if any of **font**, **text**, or **textWidth** is NULL, **byteLength**
 *  is **0**, or a brush and a pen both exist.
 * @since 19
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontMeasureTextWithBrushOrPen(const OH_Drawing_Font* font, const void* text,
    size_t byteLength, OH_Drawing_TextEncoding encoding, const OH_Drawing_Brush* brush, const OH_Drawing_Pen* pen,
    OH_Drawing_Rect* bounds, float* textWidth);

/**
 * @brief Obtains the width and bounding box of each glyph in a glyph array.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param glyphs Pointer to the start address for storing the glyph indices.
 * @param count Number of glyph indices, which must be the same as the size of glyphs array.
 * @param brush Pointer to the {@link OH_Drawing_Brush} object.
 * @param pen Pointer to the {@link OH_Drawing_Pen} object.
 * @param widths Start address for storing the glyph width.
 * @param bounds Start address for storing the glyph bounding box.
 * @return Operation code.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * Returns **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **font** or **glyphs** is NULL, **count** is not greater
 * than **0**, a brush and a pen both exist, or both **widths** and **bounds** are NULL.
 * @since 19
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontGetWidthsBounds(const OH_Drawing_Font* font, const uint16_t* glyphs, int count,
    const OH_Drawing_Brush* brush, const OH_Drawing_Pen* pen, float* widths, OH_Drawing_Array* bounds);

/**
 * @brief Obtains the relative position of each glyph from the specified origin.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param glyphs Pointer to the start address for storing the glyph indices.
 * @param count Number of glyph indices, which must be the same as the size of glyphs array.
 * @param origin Position of the first glyph. The value can be NULL, which means that the default value **(0, 0)** is
 * used.
 * @param points Start address for storing the relative position of a glyph.
 * @return Operation code.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * Returns **OH_DRAWING_ERROR_INVALID_PARAMETER** if any of **font**, **glyphs**, and **points** is NULL, or **count**
 * is less than or equal to **0**.
 * @since 19
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontGetPos(const OH_Drawing_Font* font, const uint16_t* glyphs, int count,
    const OH_Drawing_Point* origin, OH_Drawing_Point2D* points);

/**
 * @brief Obtains the recommended line spacing for a font.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param spacing Recommended line spacing for a font.
 * @return Operation code.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * Returns **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **font** or **spacing** is NULL.
 * @since 19
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontGetSpacing(const OH_Drawing_Font* font, float* spacing);

/**
 * @brief Sets linear scaling for a font.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to an **OH_Drawing_Font** object.
 * @param isLinearText Whether to enable linear scaling. The value **true** means to enable linear scaling, and **false*
 * * means the opposite.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_FontSetLinearText(OH_Drawing_Font* font, bool isLinearText);

/**
 * @brief Checks whether linear scaling is used for a font object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @return Returns **true** if linear scaling is used; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_FontIsLinearText(const OH_Drawing_Font* font);

/**
 * @brief Sets a horizontal skew factor for a font.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to an **OH_Drawing_Font** object.
 * @param skewX Skew of the X axis relative to the Y axis.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_FontSetTextSkewX(OH_Drawing_Font* font, float skewX);

/**
 * @brief Obtains the horizontal skew factor of a font.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @return Returns a floating point number representing the horizontal skew factor.
 * @since 12
 * @version 1.0
 */
float OH_Drawing_FontGetTextSkewX(const OH_Drawing_Font* font);

/**
 * @brief Sets fake bold for a font by increasing the stroke width.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to an **OH_Drawing_Font** object.
 * @param isFakeBoldText Whether to set fake bold. The value **true** means to set fake bold, and **false** means the
 * opposite.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_FontSetFakeBoldText(OH_Drawing_Font* font, bool isFakeBoldText);

/**
 * @brief Checks whether fake bold is used for a font.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @return Whether fake bold is used for a font. **true** means yes; **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_FontIsFakeBoldText(const OH_Drawing_Font* font);

/**
 * @brief Sets a horizontal scale factor for a font.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param scaleX Horizontal scale factor.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontSetScaleX(OH_Drawing_Font* font, float scaleX);

/**
 * @brief Obtains the horizontal scale ratio of this font.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @return Returns the horizontal scale factor.
 * @since 12
 * @version 1.0
 */
float OH_Drawing_FontGetScaleX(const OH_Drawing_Font* font);

/**
 * @brief Sets a font hinting effect.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **fontHinting** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param fontHinting Enumeration of font hinting types {@link OH_Drawing_FontHinting}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontSetHinting(OH_Drawing_Font* font, OH_Drawing_FontHinting fontHinting);

/**
 * @brief Obtains the font hinting effect.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @return Returns the enumeration of font hinting types {@link OH_Drawing_FontHinting}.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontHinting OH_Drawing_FontGetHinting(const OH_Drawing_Font* font);

/**
 * @brief Sets whether to use bitmaps in a font.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param isEmbeddedBitmaps Whether to use bitmaps in the font. The value **true** means to use bitmaps in the font,
 * and **false** means the opposite.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontSetEmbeddedBitmaps(OH_Drawing_Font* font, bool isEmbeddedBitmaps);

/**
 * @brief Checks whether bitmaps are used in a font.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @return Returns **true** if bitmaps are used; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_FontIsEmbeddedBitmaps(const OH_Drawing_Font* font);

/**
 * @brief Sets a font edging effect.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **fontEdging** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param fontEdging Font edging effect.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontSetEdging(OH_Drawing_Font* font, OH_Drawing_FontEdging fontEdging);

/**
 * @brief Obtains the font edging effect.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @return Font edging effect.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontEdging OH_Drawing_FontGetEdging(const OH_Drawing_Font* font);

/**
 * @brief Destroys an **OH_Drawing_Font** object and reclaims the memory occupied by the object.
 *
 * @param font Pointer to an **OH_Drawing_Font** object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_FontDestroy(OH_Drawing_Font* font);

/**
 * @brief This struct describes the measurement information about a font.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_Font_Metrics {
    /**
     * Measurement information that is valid.
     *
     * @since 12
     */
    uint32_t flags;
    /**
     * Maximum distance from the baseline to the highest coordinate of a character.
     *
     * @since 12
     */
    float top;
    /**
     * Recommended distance from the baseline to the highest coordinate of a character.
     *
     * @since 12
     */
    float ascent;
    /**
     * Recommended distance from the baseline to the lowest coordinate of a character.
     *
     * @since 12
     */
    float descent;
    /**
     * Maximum distance from the baseline to the lowest coordinate of a character.
     *
     * @since 12
     */
    float bottom;
    /**
     * Gap between rows.
     *
     * @since 12
     */
    float leading;
    /**
     * Average character width, or zero if unknown.
     *
     * @since 12
     */
    float avgCharWidth;
    /**
     * Maximum character width, or zero if unknown.
     *
     * @since 12
     */
    float maxCharWidth;
    /**
     * Maximum distance to the leftmost of the font bounding box. Generally, the value is a negative value. Variable
     * fonts are not recommended.
     *
     * @since 12
     */
    float xMin;
    /**
     * Maximum distance to the rightmost of the font bounding box. Generally, the value is a negative value. Variable
     * fonts are not recommended.
     *
     * @since 12
     */
    float xMax;
    /**
     * Height of a lowercase letter, or zero if unknown. Generally, the value is a negative value.
     *
     * @since 12
     */
    float xHeight;
    /**
     * Height of an uppercase letter, or zero if unknown. Generally, the value is a negative value.
     *
     * @since 12
     */
    float capHeight;
    /**
     * @brief Thickness of the underline.
     *
     * @since 12
     */
    float underlineThickness;
    /**
     * Position of the underline, that is, vertical distance from the baseline to the top of the underline. Generally,
     * the value is a positive value.
     *
     * @since 12
     */
    float underlinePosition;
    /**
     * Thickness of the strikethrough.
     *
     * @since 12
     */
    float strikeoutThickness;
    /**
     * Position of the strikethrough, that is, vertical distance from the baseline to the bottom of the strikethrough.
     * Generally, the value is a negative value.
     *
     * @since 12
     */
    float strikeoutPosition;
} OH_Drawing_Font_Metrics;

/**
 * @brief Obtains the measurement information about a font.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **font** or **fontMetrics** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param fontMetrics Pointer to the {@link OH_Drawing_Font_Metrics} object.
 * @return Returns a floating-point variable that indicates the recommended interline spacing.
 * @since 12
 * @version 1.0
 */
float OH_Drawing_FontGetMetrics(OH_Drawing_Font* font, OH_Drawing_Font_Metrics* fontMetrics);

/**
 * @brief Obtains the rectangular bounding box for each glyph in the glyph array.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param glyphs Pointer to a glyph array.
 * @param count Length of the glyph array.
 * @param bounds Pointer to a rectangular bounding box array.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if any of **font**, **glyphs**, or **bounds** is NULL or **count** is **0**.
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontGetBounds(
    const OH_Drawing_Font* font, const uint16_t* glyphs, uint32_t count, OH_Drawing_Array* bounds);

/**
 * @brief Obtains the path of a glyph.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param glyph Glyph index.
 * @param path Pointer to the {@link OH_Drawing_Path} object, which is used to store the glyph path.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **font** or **path** is NULL or the specified glyph does not exist.
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontGetPathForGlyph(const OH_Drawing_Font* font, uint16_t glyph, OH_Drawing_Path* path);

/**
 * @brief Obtains the text outline path.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param text Pointer to the text string.
 * @param byteLength Length of the text path. If the length is greater than the length of the text string, undefined
 * behavior occurs.
 * @param encoding Text encoding format. UTF-8, UTF-16, UTF-32, and glyph indices are supported. For details about the
 * format, see {@link OH_Drawing_TextEncoding}.
 * @param x X coordinate of the text in the drawing area, with the origin as the start point.
 * @param y Y coordinate of the text in the drawing area, with the origin as the start point.
 * @param path Pointer to the text outline path.
 * @return Returns one of the following error codes:
 * Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 * Returns {@link OH_DRAWING_ERROR_INVALID_PARAMETER} if any of **font**, **text**, or **path** is NULL.
 * @since 18
 */

OH_Drawing_ErrorCode OH_Drawing_FontGetTextPath(const OH_Drawing_Font* font, const void* text, size_t byteLength,
    OH_Drawing_TextEncoding encoding, float x, float y, OH_Drawing_Path* path);

/**
 * @brief Creates an **OH_Drawing_FontFeatures** object.
 *
 * @return Returns a pointer to the created {@link OH_Drawing_FontFeatures} object.
 * If a null pointer is returned, the creation fails. A possible cause is that no memory is available.
 * @since 20
 * @version 1.0
 */
OH_Drawing_FontFeatures* OH_Drawing_FontFeaturesCreate(void);

/**
 * @brief Adds a font feature to an **OH_Drawing_FontFeatures** object.
 *
 * @param fontFeatures Pointer to the {@link OH_Drawing_FontFeatures} object.
 * @param name Name of a font feature. Common font feature names include **liga**, **frac**, and **case**. A font
 * feature needs a TTF file to work.
 * @param value Value of the font feature. You are advised to determine the valid value range by using a font viewing
 * tool or referring to the font document.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * Returns **OH_DRAWING_ERROR_INVALID_PARAMETER** if **fontFeatures** or **name** is a null pointer.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontFeaturesAddFeature(
    OH_Drawing_FontFeatures* fontFeatures, const char* name, float value);

/**
 * @brief Destroys an **OH_Drawing_FontFeatures** object and reclaims the memory occupied by the object.
 *
 * @param fontFeatures Pointer to the {@link OH_Drawing_FontFeatures} object.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * Returns **OH_DRAWING_ERROR_INVALID_PARAMETER** if **fontFeatures** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontFeaturesDestroy(OH_Drawing_FontFeatures* fontFeatures);

/**
 * @brief Sets whether to follow the theme font. When **followed** is set to **true**, the theme font is used if it is
 * enabled by the system and no typeface is set.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param followed Whether to follow the theme font. The value **true** means to follow the theme font, and **false**
 * means the opposite.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * Returns **OH_DRAWING_ERROR_INVALID_PARAMETER** if **font** is NULL.
 * @since 15
 */
OH_Drawing_ErrorCode OH_Drawing_FontSetThemeFontFollowed(OH_Drawing_Font* font, bool followed);

/**
 * @brief Checks whether the font follows the theme font. By default, the theme font is not followed.
 *
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param followed Check result. The value **true** means that the theme font is followed, and **false** means the
 * opposite. It is used as an output parameter.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * Returns **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **font** or **followed** is NULL.
 * @since 15
 */
OH_Drawing_ErrorCode OH_Drawing_FontIsThemeFontFollowed(const OH_Drawing_Font* font, bool* followed);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
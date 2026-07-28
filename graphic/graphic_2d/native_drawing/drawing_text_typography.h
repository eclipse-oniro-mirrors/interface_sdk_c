/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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
 * @since 8
 * @version 1.0
 */

/**
 * @file drawing_text_typography.h
 *
 * @brief This file declares the functions related to typography in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_TEXT_TYPOGRAPHY_H
#define C_INCLUDE_DRAWING_TEXT_TYPOGRAPHY_H

#ifdef __cplusplus
#include <cstdint>
#include <cstddef>
#else
#include <stdint.h>
#include <stddef.h>
#endif
#include "drawing_canvas.h"
#include "drawing_error_code.h"
#include "drawing_color.h"
#include "drawing_font.h"
#include "drawing_text_declaration.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the text directions.
 *
 * @since 8
 * @version 1.0
 */
typedef enum OH_Drawing_TextDirection {
    /**
     * Right to left (RTL).
     */
    TEXT_DIRECTION_RTL,

    /**
     * Left to right (LTR).
     */
    TEXT_DIRECTION_LTR
} OH_Drawing_TextDirection;

/**
 * @brief Enumerates the text alignment modes.
 *
 * @since 8
 * @version 1.0
 */
typedef enum OH_Drawing_TextAlign {
    /**
     * Left-aligned.
     */
    TEXT_ALIGN_LEFT,

    /**
     * Right-aligned.
     */
    TEXT_ALIGN_RIGHT,

    /**
     * Center-aligned.
     */
    TEXT_ALIGN_CENTER,

    /**
     * Justified, which means that each line (except the last line) is stretched so that every line has equal width,
     * and the left and right margins are straight.
     */
    TEXT_ALIGN_JUSTIFY,

    /**
     * When **OH_Drawing_TextDirection** is set to **TEXT_DIRECTION_LTR**, **TEXT_ALIGN_START** and **TEXT_ALIGN_LEFT**
     * are the same.<br>Similarly, when **OH_Drawing_TextDirection** is set to **TEXT_DIRECTION_RTL**, **
     * TEXT_ALIGN_START** and **TEXT_ALIGN_RIGHT** are the same.
     */
    TEXT_ALIGN_START,

    /**
     * When **OH_Drawing_TextDirection** is set to **TEXT_DIRECTION_LTR**, **TEXT_ALIGN_END** and **TEXT_ALIGN_RIGHT**
     * are the same.<br>Similarly, when **OH_Drawing_TextDirection** is set to **TEXT_DIRECTION_RTL**, **TEXT_ALIGN_END*
     * * and **TEXT_ALIGN_LEFT** are the same.
     */
    TEXT_ALIGN_END
} OH_Drawing_TextAlign;

/**
 * @brief Enumerates the font weights.
 *
 * @since 8
 * @version 1.0
 */
typedef enum OH_Drawing_FontWeight {
    /**
     * Thin.
     */
    FONT_WEIGHT_100,

    /**
     * Extra-light.
     */
    FONT_WEIGHT_200,

    /**
     * Light.
     */
    FONT_WEIGHT_300,

    /**
     * Normal/Regular.
     */
    FONT_WEIGHT_400,

    /**
     * Medium.
     */
    FONT_WEIGHT_500,

    /**
     * Semi-bold.
     */
    FONT_WEIGHT_600,

    /**
     * Bold.
     */
    FONT_WEIGHT_700,

    /**
     * Extra-bold.
     */
    FONT_WEIGHT_800,

    /**
     * Black.
     */
    FONT_WEIGHT_900
} OH_Drawing_FontWeight;

/**
 * @brief Enumerates the text baselines.
 *
 * @since 8
 * @version 1.0
 */
typedef enum OH_Drawing_TextBaseline {
    /**
     * Alphabetic, where the letters in alphabets like English sit on.
     */
    TEXT_BASELINE_ALPHABETIC,

    /**
     * Ideographic, where the baseline is at the bottom of the text area.
     */
    TEXT_BASELINE_IDEOGRAPHIC
} OH_Drawing_TextBaseline;

/**
 * @brief Enumerates the text decorations.
 *
 * @since 8
 * @version 1.0
 */
typedef enum OH_Drawing_TextDecoration {
    /**
     * No decoration.
     */
    TEXT_DECORATION_NONE = 0x0,

    /**
     * An underline is used for decoration.
     */
    TEXT_DECORATION_UNDERLINE = 0x1,

    /**
     * An overline is used for decoration.
     */
    TEXT_DECORATION_OVERLINE = 0x2,

    /**
     * A strikethrough is used for decoration.
     */
    TEXT_DECORATION_LINE_THROUGH = 0x4
} OH_Drawing_TextDecoration;

/**
 * @brief Enumerates the font styles.
 *
 * @since 8
 * @version 1.0
 */
typedef enum OH_Drawing_FontStyle {
    /**
     * Normal style.
     */
    FONT_STYLE_NORMAL,

    /**
     * Italic.
     */
    FONT_STYLE_ITALIC,

    /**
     * Oblique.
     */
    FONT_STYLE_OBLIQUE
} OH_Drawing_FontStyle;

/**
 * @brief Enumerates the vertical alignment modes of placeholders.
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * Aligned to the baseline.
     */
    ALIGNMENT_OFFSET_AT_BASELINE,

    /**
     * Aligned above the baseline.
     */
    ALIGNMENT_ABOVE_BASELINE,

    /**
     * Aligned below the baseline.
     */
    ALIGNMENT_BELOW_BASELINE,

    /**
     * Aligned to the top of the row box.
     */
    ALIGNMENT_TOP_OF_ROW_BOX,

    /**
     * Aligned to the bottom of the row box.
     */
    ALIGNMENT_BOTTOM_OF_ROW_BOX,

    /**
     * Aligned to the center of the row box.
     */
    ALIGNMENT_CENTER_OF_ROW_BOX,

    /**
     * Follows the vertical alignment mode of the text.
     * @since 20
     */
    ALIGNMENT_FOLLOW_PARAGRAPH
} OH_Drawing_PlaceholderVerticalAlignment;

/**
 * @brief This struct describes the placeholder that acts as a span.
 *
 * @since 11
 * @version 1.0
 */
typedef struct {
    /**
     * Width of a placeholder.
     */
    double width;
    /**
     * Height of a placeholder.
     */
    double height;
    /**
     * Alignment mode of a placeholder.
     */
    OH_Drawing_PlaceholderVerticalAlignment alignment;
    /**
     * Baseline of a placeholder.
     */
    OH_Drawing_TextBaseline baseline;
    /**
     * Baseline offset of a placeholder.
     */
    double baselineOffset;
} OH_Drawing_PlaceholderSpan;

/**
 * @brief Enumerates the text decoration styles.
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * Solid style.
     */
    TEXT_DECORATION_STYLE_SOLID,

    /**
     * Double style.
     */
    TEXT_DECORATION_STYLE_DOUBLE,

    /**
     * Dotted style.
     */
    TEXT_DECORATION_STYLE_DOTTED,

    /**
     * Dashed style.
     */
    TEXT_DECORATION_STYLE_DASHED,

    /**
     * Wavy style.
     */
    TEXT_DECORATION_STYLE_WAVY
} OH_Drawing_TextDecorationStyle;

/**
 * @brief Enumerates the ellipsis styles.
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * Header ellipsis mode, that is, the ellipsis appears at the beginning of a line. This enumerated value is valid
     * only when the maximum number of text lines is set to **1** by calling
     * {@link OH_Drawing_SetTypographyTextMaxLines}.
     */
    ELLIPSIS_MODAL_HEAD = 0,

    /**
     * Middle ellipsis mode, that is, the ellipsis appears in the middle of a line. This enumerated value is valid only
     * when the maximum number of text lines is set to **1** by calling {@link OH_Drawing_SetTypographyTextMaxLines}.
     */
    ELLIPSIS_MODAL_MIDDLE = 1,

    /**
     * End ellipsis mode, that is, the ellipsis appears at the end of a line. This enumerated value is valid when the
     * maximum number of text lines is set to any value by calling {@link OH_Drawing_SetTypographyTextMaxLines}.
     */
    ELLIPSIS_MODAL_TAIL = 2,

    /**
     * Header ellipsis mode, that is, the ellipsis appears at the beginning of a line. This enumerated value is valid
     * when the maximum number of text lines is set to any value by calling
     * {@link OH_Drawing_SetTypographyTextMaxLines}.
     * @since 24
     */
    ELLIPSIS_MODAL_MULTILINE_HEAD = 3,

    /**
     * Middle ellipsis mode, that is, the ellipsis appears in the middle of a line. This enumerated value is valid when
     * the maximum number of text lines is set to any value by calling {@link OH_Drawing_SetTypographyTextMaxLines}.
     * @since 24
     */
    ELLIPSIS_MODAL_MULTILINE_MIDDLE = 4
} OH_Drawing_EllipsisModal;

/**
 * @brief Enumerates the text break strategies.
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * Each line is filled as much as possible during line break.
     */
    BREAK_STRATEGY_GREEDY = 0,

    /**
     * Text continuity is preferentially considered during line break.
     */
    BREAK_STRATEGY_HIGH_QUALITY = 1,

    /**
     * Line breaks are performed at the word boundary.
     */
    BREAK_STRATEGY_BALANCED = 2
} OH_Drawing_BreakStrategy;

/**
 * @brief Enumerates the word break types.
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * Normal mode.
     */
    WORD_BREAK_TYPE_NORMAL = 0,

    /**
     * Breaks the words at any character to prevent overflow.
     */
    WORD_BREAK_TYPE_BREAK_ALL = 1,

    /**
     * Breaks the words at arbitrary points to prevent overflow.
     */
    WORD_BREAK_TYPE_BREAK_WORD = 2,

    /**
     * Uses a hyphen (-) to break a word at the end of each line. If adding a hyphen is not possible, it will behave
     * the same as **WORD_BREAK_TYPE_BREAK_WORD**.
     * @since 18
     */
    WORD_BREAK_TYPE_BREAK_HYPHEN = 3
} OH_Drawing_WordBreakType;

/**
 * @brief Enumerates the rectangle height styles.
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * Tight style.
     */
    RECT_HEIGHT_STYLE_TIGHT,

    /**
     * Maximum style.
     */
    RECT_HEIGHT_STYLE_MAX,

    /**
     * Middle style that includes the line spacing.
     */
    RECT_HEIGHT_STYLE_INCLUDELINESPACEMIDDLE,

    /**
     * Top style that includes the line spacing.
     */
    RECT_HEIGHT_STYLE_INCLUDELINESPACETOP,

    /**
     * Bottom style that includes the line spacing.
     */
    RECT_HEIGHT_STYLE_INCLUDELINESPACEBOTTOM,

    /**
     * Structure style.
     */
    RECT_HEIGHT_STYLE_STRUCT
} OH_Drawing_RectHeightStyle;

/**
 * @brief Enumerates the rectangle width styles.
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * Tight style.
     */
    RECT_WIDTH_STYLE_TIGHT,

    /**
     * Maximum style.
     */
    RECT_WIDTH_STYLE_MAX
} OH_Drawing_RectWidthStyle;

/**
 * @brief Enumerates the error codes that may be used during the obtaining of system font configurations.
 *
 * @since 12
 * @version 1.0
 */
typedef enum OH_Drawing_FontConfigInfoErrorCode {
    /**
     * Operation successful.
     */
    SUCCESS_FONT_CONFIG_INFO = 0,

    /**
     * Unknown error.
     */
    ERROR_FONT_CONFIG_INFO_UNKNOWN = 1,

    /**
     * Failed to parse the system configuration file.
     */
    ERROR_FONT_CONFIG_INFO_PARSE_FILE = 2,

    /**
     * Memory allocation fails.
     */
    ERROR_FONT_CONFIG_INFO_ALLOC_MEMORY = 3,

    /**
     * Failed to copy the string data.
     */
    ERROR_FONT_CONFIG_INFO_COPY_STRING_DATA = 4
} OH_Drawing_FontConfigInfoErrorCode;

/**
 * @brief This struct describes the information about a font fallback.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontFallbackInfo {
    /**
     * Pointer to the language supported by the font fallback. The language format is bcp47.
     */
    char* language;
    /**
     * Pointer to the name of a font family.
     */
    char* familyName;
} OH_Drawing_FontFallbackInfo;

/**
 * @brief This struct describes the information about a font fallback group.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontFallbackGroup {
    /**
     * Pointer to the name of the group corresponding to the font fallback group. If null is passed in, all fonts in
     * the font fallback group can be used.
     */
    char* groupName;
    /**
     * Number of font fallbacks.
     */
    size_t fallbackInfoSize;
    /**
     * Pointer to the set of font fallbacks.
     */
    OH_Drawing_FontFallbackInfo* fallbackInfoSet;
} OH_Drawing_FontFallbackGroup;

/**
 * @brief This struct describes the information about a font weight mapping.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontAdjustInfo {
    /**
     * Original font weight.
     */
    int weight;
    /**
     * Font weight displayed in the application.
     */
    int to;
} OH_Drawing_FontAdjustInfo;

/**
 * @brief This struct describes the information about a font alias.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontAliasInfo {
    /**
     * Pointer to the name of a font family.
     */
    char* familyName;
    /**
     * Font weight. If the value is greater than 0, only the fonts with the specified weight in the font family are
     * contained. If the value is 0, all the fonts in the font family are contained.
     */
    int weight;
} OH_Drawing_FontAliasInfo;

/**
 * @brief This struct describes the information about generic fonts supported by the system.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontGenericInfo {
    /**
     * Pointer to the name of a font family.
     */
    char* familyName;
    /**
     * Number of font aliases.
     */
    size_t aliasInfoSize;
    /**
     * Number of font weight mappings.
     */
    size_t adjustInfoSize;
    /**
     * Pointer to a set of font aliases.
     */
    OH_Drawing_FontAliasInfo* aliasInfoSet;
    /**
     * Pointer to a set of font weight mappings.
     */
    OH_Drawing_FontAdjustInfo* adjustInfoSet;
} OH_Drawing_FontGenericInfo;

/**
 * @brief This struct describes the information about a system font configuration.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontConfigInfo {
    /**
     * Number of system font file paths.
     */
    size_t fontDirSize;
    /**
     * Number of generic fonts.
     */
    size_t fontGenericInfoSize;
    /**
     * Number of font fallbacks.
     */
    size_t fallbackGroupSize;
    /**
     * Double pointer to the system font file paths.
     */
    char** fontDirSet;
    /**
     * Pointer to a set of generic fonts.
     */
    OH_Drawing_FontGenericInfo* fontGenericInfoSet;
    /**
     * Pointer to a set of font fallbacks.
     */
    OH_Drawing_FontFallbackGroup* fallbackGroupSet;
} OH_Drawing_FontConfigInfo;

/**
 * @brief This struct describes the detailed information about a system font.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontDescriptor {
    /**
     * File path of the system font.
     */
    char* path;
    /**
     * PostScript name that uniquely identifies the system font.
     */
    char* postScriptName;
    /**
     * Full name of the system font.
     */
    char* fullName;
    /**
     * Family of the system font.
     */
    char* fontFamily;
    /**
     * Subfamily of the system font.
     */
    char* fontSubfamily;
    /**
     * Weight of the system font.
     */
    int weight;
    /**
     * Width of the system font.
     */
    int width;
    /**
     * Slope of the system font.
     */
    int italic;
    /**
     * Whether the system font is monospaced. **true** means yes; **false** otherwise.
     */
    bool monoSpace;
    /**
     * Whether the system font supports symbols. **true** means yes; **false** otherwise.
     */
    bool symbolic;
} OH_Drawing_FontDescriptor;

/**
 * @brief This struct describes the measurement information about a line of text.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_LineMetrics {
    /**
     * Height of a character above the baseline, after taking the absolute value.
     */
    double ascender;
    /**
     * Height of a character below the baseline, after taking the absolute value.
     */
    double descender;
    /**
     * Height of an uppercase letter above the baseline.
     */
    double capHeight;
    /**
     * Height of a lowercase letter, specifically the lowercase x, not including ascenders and descenders.
     */
    double xHeight;
    /**
     * Horizontal space taken up by a character.
     */
    double width;
    /**
     * Line height.
     */
    double height;
    /**
     * Distance from the left edge of the leftmost character to the left edge of the container. For left alignment, the
     * value is 0. For right alignment, the value is the container width minus the text width.
     */
    double x;
    /**
     * Height from the top edge of the character to the top of the container. The first line is 0, and the second line
     * is the height of the first line.
     */
    double y;
    /**
     * Index of the first character in the line.
     */
    size_t startIndex;
    /**
     * Index of the last character in the line.
     */
    size_t endIndex;
    /**
     * Measurement information of the first character.
     */
    OH_Drawing_Font_Metrics firstCharMetrics;
} OH_Drawing_LineMetrics;

/**
 * @brief Enumerates the text height modifier patterns.
 *
 * @since 12
 * @version 1.0
 */
typedef enum OH_Drawing_TextHeightBehavior {
    /**
     * Enables the height set by calling {@link OH_Drawing_SetTextStyleFontHeight} for the top of the first line and
     * the bottom of the last line in a paragraph.
     */
    TEXT_HEIGHT_ALL = 0x0,

    /**
     * Disables the height set by calling {@link OH_Drawing_SetTextStyleFontHeight} for the top of the first line in a
     * paragraph.
     */
    TEXT_HEIGHT_DISABLE_FIRST_ASCENT = 0x1,

    /**
     * Disables the height set by calling {@link OH_Drawing_SetTextStyleFontHeight} for the bottom of the last line in
     * a paragraph.
     */
    TEXT_HEIGHT_DISABLE_LAST_ASCENT = 0x2,

    /**
     * Disables the height set by calling {@link OH_Drawing_SetTextStyleFontHeight} for both the top of the first line
     * and the bottom of the last line in a paragraph.
     */
    TEXT_HEIGHT_DISABLE_ALL = 0x1 | 0x2
} OH_Drawing_TextHeightBehavior;

/**
 * @brief Enumerates the text style types.
 *
 * @since 12
 * @version 1.0
 */
typedef enum OH_Drawing_TextStyleType {
    /**
     * No text style.
     */
    TEXT_STYLE_NONE,

    /**
     * All text styles.
     */
    TEXT_STYLE_ALL_ATTRIBUTES,

    /**
     * Font style.
     */
    TEXT_STYLE_FONT,

    /**
     * Text foreground style.
     */
    TEXT_STYLE_FOREGROUND,

    /**
     * Text background style.
     */
    TEXT_STYLE_BACKGROUND,

    /**
     * Text shadow style.
     */
    TEXT_STYLE_SHADOW,

    /**
     * Text decoration style.
     */
    TEXT_STYLE_DECORATIONS,

    /**
     * Text letter spacing style.
     */
    TEXT_STYLE_LETTER_SPACING,

    /**
     * Text word spacing style.
     */
    TEXT_STYLE_WORD_SPACING
} OH_Drawing_TextStyleType;

/**
 * @brief Enumerates the font widths.
 *
 * @since 12
 * @version 1.0
 */
typedef enum OH_Drawing_FontWidth {
    /**
     * Ultra condensed font.
     */
    FONT_WIDTH_ULTRA_CONDENSED = 1,

    /**
     * Extra condensed font.
     */
    FONT_WIDTH_EXTRA_CONDENSED = 2,

    /**
     * Condensed font.
     */
    FONT_WIDTH_CONDENSED = 3,

    /**
     * Semi-condensed font.
     */
    FONT_WIDTH_SEMI_CONDENSED = 4,

    /**
     * Normal font.
     */
    FONT_WIDTH_NORMAL = 5,

    /**
     * Semi-expanded font.
     */
    FONT_WIDTH_SEMI_EXPANDED = 6,

    /**
     * Expanded font.
     */
    FONT_WIDTH_EXPANDED = 7,

    /**
     * Extra expanded font.
     */
    FONT_WIDTH_EXTRA_EXPANDED = 8,

    /**
     * Ultra expanded font.
     */
    FONT_WIDTH_ULTRA_EXPANDED = 9
} OH_Drawing_FontWidth;

/**
 * @brief Enumerates the text style attributes.
 *
 * @since 21
 */
typedef enum OH_Drawing_TextStyleAttributeId {
    /**
     * Maximum line height.<br>If line height scaling is enabled, the maximum line height takes effect only when **
     * FontHeight** (which can be obtained from {@link OH_Drawing_TextStyleGetFontHeight}) is greater than 0.<br>The
     * value is the positive part of a single-precision floating point number. By default, it equals the maximum
     * possible value for such a number.
     */
    TEXT_STYLE_ATTR_D_LINE_HEIGHT_MAXIMUM = 0,

    /**
     * Minimum line height.<br>If line height scaling is enabled, the minimum line height takes effect only when **
     * FontHeight** (which can be obtained from {@link OH_Drawing_TextStyleGetFontHeight}) is greater than 0.<br>The
     * value is the non-negative part of a single-precision floating point number. The default value is **0**.
     */
    TEXT_STYLE_ATTR_D_LINE_HEIGHT_MINIMUM = 1,

    /**
     * Scaling base style of the line height. For details, see {@link OH_Drawing_LineHeightStyle}.
     */
    TEXT_STYLE_ATTR_I_LINE_HEIGHT_STYLE = 2,

    /**
     * Font width.
     */
    TEXT_STYLE_ATTR_I_FONT_WIDTH = 3,

    /**
     * Font edge processing mode. Anti-aliasing is used by default. For details about how to process font edges, see
     * {@link OH_Drawing_FontEdging}.
     * @since 24
     */
    TEXT_STYLE_ATTR_I_FONT_EDGING = 4
} OH_Drawing_TextStyleAttributeId;

/**
 * @brief Enumerates the scaling base styles of the line height. The default style is **TEXT_LINE_HEIGHT_BY_FONT_SIZE**.
 *
 * @since 21
 */
typedef enum OH_Drawing_LineHeightStyle {
    /**
     * Uses the font size as the scaling base.<br>Formula for calculating the line height: **FontSize** x **FontHeight**
     * .<br>**FontSize** can be obtained from the {@link OH_Drawing_TextStyleGetFontSize} API.<br>**FontHeight** can be
     * obtained from the {@link OH_Drawing_TextStyleGetFontHeight} API.
     */
    TEXT_LINE_HEIGHT_BY_FONT_SIZE = 0,

    /**
     * Uses the font height as the scaling base.<br>Formula for calculating the line height: font height x **FontHeight*
     * *.<br>The font height is obtained after the text is shaped using the font file.<br>**FontHeight** can be
     * obtained from the {@link OH_Drawing_TextStyleGetFontHeight} API.
     */
    TEXT_LINE_HEIGHT_BY_FONT_HEIGHT = 1
} OH_Drawing_LineHeightStyle;

/**
 * @brief Enumerates the typography style attributes.
 * <br>For the common attributes of the typography styles and text styles, you are advised to use the text style
 * attributes, which can be obtained from {@link OH_Drawing_TextStyleAttributeId}.
 *
 * @since 21
 */
typedef enum OH_Drawing_TypographyStyleAttributeId {
    /**
     * Maximum line height.<br>If line height scaling is enabled, the maximum line height takes effect only when **
     * FontHeight** (which can be obtained from {@link OH_Drawing_TextStyleGetFontHeight}) is greater than 0.<br>The
     * value is the positive part of a single-precision floating point number. By default, it equals the maximum
     * possible value for such a number.
     */
    TYPOGRAPHY_STYLE_ATTR_D_LINE_HEIGHT_MAXIMUM = 0,

    /**
     * Minimum line height.<br>If line height scaling is enabled, the minimum line height takes effect only when **
     * FontHeight** (which can be obtained from {@link OH_Drawing_TextStyleGetFontHeight}) is greater than 0.<br>The
     * value is the non-negative part of a single-precision floating point number. The default value is **0**.
     */
    TYPOGRAPHY_STYLE_ATTR_D_LINE_HEIGHT_MINIMUM = 1,

    /**
     * Interline spacing.<br>**lineSpacing** is not restricted by the maximum and minimum line heights.<br>By default,
     * line spacing is added to the last line.<br>You can set **textHeightBehavior** to **DISABLE_LAST_ASCENT** in
     * {@link OH_Drawing_TypographyTextSetHeightBehavior} to disable the line spacing of the last line.<br>The default
     * value is **0**.
     */
    TYPOGRAPHY_STYLE_ATTR_D_LINE_SPACING = 2,

    /**
     * Scaling base style of the line height. For details, see {@link OH_Drawing_LineHeightStyle}.
     */
    TYPOGRAPHY_STYLE_ATTR_I_LINE_HEIGHT_STYLE = 3,

    /**
     * Font width.
     */
    TYPOGRAPHY_STYLE_ATTR_I_FONT_WIDTH = 4,

    /**
     * Sets whether to use punctuation compression at the beginning of a line in text layout.<br>**NOTE**<br>1. The
     * font file must support the ss08 feature in {@link OH_Drawing_FontFeature}. Otherwise, compression cannot be
     * performed.<br>2. Only the punctuations within the punctuation compression range at the beginning of a line are
     * in the scope of this feature.
     * @since 23
     */
    TYPOGRAPHY_STYLE_ATTR_B_COMPRESS_HEAD_PUNCTUATION = 5,

    /**
     * Sets whether to enable the built-in padding of the font during text typography.
     * @since 23
     */
    TYPOGRAPHY_STYLE_ATTR_B_INCLUDE_FONT_PADDING = 6,

    /**
     * Sets whether to enable the line spacing rollback mechanism during text typography.
     * @since 23
     */
    TYPOGRAPHY_STYLE_ATTR_B_FALLBACK_LINE_SPACING = 7,

    /**
     * Ellipsis style. For details about the ellipsis style, see {@link OH_Drawing_EllipsisModal}.
     * @since 24
     */
    TYPOGRAPHY_STYLE_ATTR_I_ELLIPSIS_MODAL = 8,

    /**
     * First-line indent array.<br>All values in the indent array must be greater than or equal to 0. Each element in
     * the array represents the indentation value of a single line. If the actual number of text lines exceeds the
     * length of the indent array, the last value of the array is applied to the extra lines.
     * @since 26.0.0
     */
    TYPOGRAPHY_STYLE_ATTR_DA_LINE_HEAD_INDENT = 9,

    /**
     * First-line indent of a paragraph. The indent value must be greater than or equal to 0.
     * @since 26.0.0
     */
    TYPOGRAPHY_STYLE_ATTR_D_FIRST_LINE_HEAD_INDENT = 10,

    /**
     * Last-line indent array.<br>All values in the indent array must be greater than or equal to 0. Each element in
     * the array represents the indentation value of a single line. If the actual number of text lines exceeds the
     * length of the indent array, the last value of the array is applied to the extra lines.
     * @since 26.0.0
     */
    TYPOGRAPHY_STYLE_ATTR_DA_LINE_TAIL_INDENT = 11
} OH_Drawing_TypographyStyleAttributeId;

/**
 * @brief Enumerates typography attribute.
 *
 * @since 26.0.0
 */
typedef enum OH_Drawing_TypographyAttributeId {
    /**
     * Whether to force reuse the rasterization result.
     * True means to force reuse of the rasterization result. False means to allow updates to the rasterization result.
     * The default value is false.
     * @since 26.0.0
     */
    TYPOGRAPHY_ATTR_B_FORCE_REUSE_RASTER_RESULT = 0,
} OH_Drawing_TypographyAttributeId;

/**
 * @brief Gets the bool type property's value from the typography.
 *
 * @param typography Indicates the pointer to an <b>OH_Drawing_Typography</b> object.
 * @param id Indicates the attribute id.
 * @param value Indicates the return value of the interface.
 * @return Returns the error code.
 *         Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 *         Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if the typography or value is nullptr.
 *         Returns {@link OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH} if the attribute id is not recognized or supported.
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_GetTypographyAttributeBool(const OH_Drawing_Typography* typography,
    OH_Drawing_TypographyAttributeId id, bool* value);

/**
 * @brief Sets bool value to the typography attribute.
 *
 * @param typography Indicates the pointer to an <b>OH_Drawing_Typography</b> object.
 * @param id Indicates the attribute id.
 * @param value Indicates the value to set.
 * @return Returns the error code.
 *         Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 *         Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if the typography is nullptr.
 *         Returns {@link OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH} if the attribute id is not recognized or supported.
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_SetTypographyAttributeBool(OH_Drawing_Typography* typography,
    OH_Drawing_TypographyAttributeId id, bool value);

/**
 * @brief Sets the text style attribute of the **double** type.
 *
 * @param style Pointer to an {@link OH_Drawing_TextStyle} object.
 * @param id Text style attribute ID.
 * @param value Text style attribute value.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INVALID_PARAMETER** if **style** is NULL.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 *     <br>**OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** if the value corresponding to the attribute id exceeds the
 *     allowable range.
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_SetTextStyleAttributeDouble(OH_Drawing_TextStyle* style,
    OH_Drawing_TextStyleAttributeId id, double value);

/**
 * @brief Obtains the text style attribute of the **double** type.
 *
 * @param style Pointer to an {@link OH_Drawing_TextStyle} object.
 * @param id Text style attribute ID.
 * @param value Pointer to the attribute of the **double** type. It is used as an output parameter.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INVALID_PARAMETER** if **style** is NULL.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_GetTextStyleAttributeDouble(OH_Drawing_TextStyle* style,
    OH_Drawing_TextStyleAttributeId id, double* value);

/**
 * @brief Sets the text style attribute of the **int** type.
 *
 * @param style Pointer to an {@link OH_Drawing_TextStyle} object.
 * @param id Text style attribute ID.
 * @param value Attribute value to set.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INVALID_PARAMETER** if **style** is NULL.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 *     <br>**OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** if the input value exceeds the value range of the attribute to
 *     be set.
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_SetTextStyleAttributeInt(OH_Drawing_TextStyle* style,
    OH_Drawing_TextStyleAttributeId id, int value);

/**
 * @brief Obtains the text style attribute of the **int** type.
 *
 * @param style Pointer to an {@link OH_Drawing_TextStyle} object.
 * @param id Text style attribute ID.
 * @param value Pointer to the attribute of the **int** type. It is used as an output parameter.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INVALID_PARAMETER** if **style** is NULL.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_GetTextStyleAttributeInt(OH_Drawing_TextStyle* style,
    OH_Drawing_TextStyleAttributeId id, int* value);

/**
 * @brief Sets the typography style attribute of the **double** type.
 *
 * @param style Pointer to an {@link OH_Drawing_TypographyStyle} object.
 * @param id Attribute ID of the text style.
 * @param value Attribute value to set.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INVALID_PARAMETER** if **style** is NULL.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 *     <br>**OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** if the value corresponding to the attribute id
 *     exceeds the allowable range.
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_SetTypographyStyleAttributeDouble(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, double value);

/**
 * @brief Obtains the typography style attribute of the **double** type.
 *
 * @param style Pointer to an {@link OH_Drawing_TypographyStyle} object.
 * @param id Attribute ID of the text style.
 * @param value Pointer to the attribute of the **double** type. It is used as an output parameter.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INVALID_PARAMETER** if **style** is NULL.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_GetTypographyStyleAttributeDouble(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, double* value);

/**
 * @brief Sets the typography style attribute of the **int** type.
 *
 * @param style Pointer to an {@link OH_Drawing_TypographyStyle} object.
 * @param id Attribute ID of the text style.
 * @param value Attribute value to set.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INVALID_PARAMETER** if **style** is NULL.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 *     <br>**OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** if the input value exceeds the value range of the attribute to
 *     be set.
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_SetTypographyStyleAttributeInt(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, int value);

/**
 * @brief Obtains the typography style attribute of the **int** type.
 *
 * @param style Pointer to an {@link OH_Drawing_TypographyStyle} object.
 * @param id Attribute ID of the text style.
 * @param value Pointer to the attribute of the **int** type. It is used as an output parameter.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INVALID_PARAMETER** if **style** is NULL.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_GetTypographyStyleAttributeInt(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, int* value);

/**
 * @brief Sets the typography style attribute of the **bool** type.
 *
 * @param style Pointer to an {@link OH_Drawing_TypographyStyle} object.
 * @param id Attribute ID of the text style.
 * @param value Attribute value to set.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **style** is NULL.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_SetTypographyStyleAttributeBool(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, bool value);

/**
 * @brief Obtains the typography style attribute of the **bool** type.
 *
 * @param style Pointer to an {@link OH_Drawing_TypographyStyle} object.
 * @param id Attribute ID of the text style.
 * @param value Pointer to the bool attribute. It is used as an output parameter.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **style** or **value** is NULL.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_GetTypographyStyleAttributeBool(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, bool* value);

/**
 * @brief Sets the typography style attribute of the floating-point array type.
 *
 * @param style Pointer to an {@link OH_Drawing_TypographyStyle} object.
 * @param id Attribute ID of the text style.
 * @param arrayValue Pointer to the floating-point array.
 * @param arrayLength Length of the floating-point array.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if the parameter **style** or **arrayValue** is a null pointer or
 *     **arrayLength** is 0.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_SetTypographyStyleAttributeDoubleArray(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, double* arrayValue, size_t arrayLength);

/**
 * @brief Obtains the typography style attribute of the floating-point array type.
 *
 * @param style Pointer to an {@link OH_Drawing_TypographyStyle} object.
 * @param id Attribute ID of the text style.
 * @param arrayValue Pointer to the floating-point array. It is used as an output parameter.
 * @param arrayLength Length of the floating-point array. It is used as an output parameter.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if the parameter **style** or **arrayValue** is a null pointer or
 *      **arrayLength** is a null pointer.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_GetTypographyStyleAttributeDoubleArray(const OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, double** arrayValue, size_t* arrayLength);

/**
 * @brief Enumerates the text badge styles.
 *
 * @since 20
 * @version 1.0
 */
typedef enum OH_Drawing_TextBadgeType {
    /**
     * Disables the superscript and subscript.
     */
    TEXT_BADGE_NONE,

    /**
     * Enables the superscript.
     */
    TEXT_SUPERSCRIPT,

    /**
     * Enables the subscript.
     */
    TEXT_SUBSCRIPT
} OH_Drawing_TextBadgeType;

/**
 * @brief Enumerates the vertical alignment modes.
 *
 * @since 20
 * @version 1.0
 */
typedef enum OH_Drawing_TextVerticalAlignment {
    /**
     * Aligned to the baseline.
     */
    TEXT_VERTICAL_ALIGNMENT_BASELINE,

    /**
     * Bottom aligned.
     */
    TEXT_VERTICAL_ALIGNMENT_BOTTOM,

    /**
     * Center-aligned.
     */
    TEXT_VERTICAL_ALIGNMENT_CENTER,

    /**
     * Top aligned.
     */
    TEXT_VERTICAL_ALIGNMENT_TOP
} OH_Drawing_TextVerticalAlignment;

/**
 * @brief This struct describes a font style.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontStyleStruct {
    /**
     * Font weight.
     */
    OH_Drawing_FontWeight weight;
    /**
     * Font width.
     */
    OH_Drawing_FontWidth width;
    /**
     * Font slant.
     */
    OH_Drawing_FontStyle slant;
} OH_Drawing_FontStyleStruct;

/**
 * @brief This struct describes a font feature.
 *
 * @since 12
 * @version 1.0
 */
typedef struct {
    /**
     * Tag of the font feature.
     */
    char* tag;
    /**
     * Value of the font feature.
     */
    int value;
} OH_Drawing_FontFeature;

/**
 * @brief This struct describes a strut style. The strut style determines the line spacing, baseline alignment mode,
 * and other properties related to the line height when drawing text.
 *
 * @since 12
 * @version 1.0
 */
typedef struct {
    /**
     * Font weight used for calculating the strut.
     */
    OH_Drawing_FontWeight weight;
    /**
     * Font style used for calculating the strut.
     */
    OH_Drawing_FontStyle style;
    /**
     * Size of the ascent plus descent in the logical pixels.
     */
    double size;
    /**
     * Scale factor of the line height.
     */
    double heightScale;
    /**
     * Whether to enable height override. **true**: enabled; **false**: disabled.
     */
    bool heightOverride;
    /**
     * Whether to enable half leading. **true**: enabled; **false**: disabled.
     */
    bool halfLeading;
    /**
     * Custom leading to be applied to the strut.
     */
    double leading;
    /**
     * Whether to forcibly use the strut height for all rows. **true** means yes; **false** otherwise.
     */
    bool forceStrutHeight;
    /**
     * Number of font families.
     */
    size_t familiesSize;
    /**
     * Double pointer to the font families used for calculating the strut.
     */
    char** families;
} OH_Drawing_StrutStyle;

/**
 * @brief Defines the text rect struct.
 *
 * @since 24
 */
typedef struct OH_Drawing_RectSize {
    /**
     * Rectangle width.
     */
    double width;
    /**
     * Rectangle height.
     */
    double height;
} OH_Drawing_RectSize;

/**
 * @brief Creates an **OH_Drawing_TypographyStyle** object. Release this pointer by calling
 * {@link OH_Drawing_DestroyTypographyStyle} when this object is no longer needed.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return Pointer to the created {@link OH_Drawing_TypographyStyle} object.
 * @since 8
 * @version 1.0
 */
OH_Drawing_TypographyStyle* OH_Drawing_CreateTypographyStyle(void);

/**
 * @brief Destroys an **OH_Drawing_TypographyStyle** object and reclaims the memory occupied by the object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_DestroyTypographyStyle(OH_Drawing_TypographyStyle* style);

/**
 * @brief Sets the text direction in a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param direction Text direction. For details about the available options, see {@link OH_Drawing_TextDirection}.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextDirection(OH_Drawing_TypographyStyle* style, int direction);

/**
 * @brief Text alignment mode.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param align Text alignment mode. For details about the available options, see {@link OH_Drawing_TextAlign}.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextAlign(OH_Drawing_TypographyStyle* style, int align);

/**
 * @brief Sets the maximum number of lines in the text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param lineNumber Maximum number of lines.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextMaxLines(OH_Drawing_TypographyStyle* style, int lineNumber);

/**
 * @brief Creates an **OH_Drawing_TextStyle** object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return Pointer to the created {@link OH_Drawing_TextStyle} object.
 * @since 8
 * @version 1.0
 */
OH_Drawing_TextStyle* OH_Drawing_CreateTextStyle(void);

/**
 * @brief Destroys an **OH_Drawing_TextStyle** object and reclaims the memory occupied by the object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_DestroyTextStyle(OH_Drawing_TextStyle* style);

/**
 * @brief Sets the color for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param color Color.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleColor(OH_Drawing_TextStyle* style, uint32_t color);

/**
 * @brief Sets the font size for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param fontSize Font size to set.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleFontSize(OH_Drawing_TextStyle* style, double fontSize);

/**
 * @brief Sets the font weight for a text style. Currently, only the default system font supports font weight
 * adjustment. For other fonts, if the weight is less than semi-bold, there is no variation in stroke thickness. If the
 * weight is greater than or equal to semi-bold, it might result in a fake bold effect.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param fontWeight Font weight.
 *     <br>For details about the available options, see {@link OH_Drawing_FontWeight}.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleFontWeight(OH_Drawing_TextStyle* style, int fontWeight);

/**
 * @brief Sets the baseline for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param baseline Text baseline. For details about the available options, see {@link OH_Drawing_TextBaseline}.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleBaseLine(OH_Drawing_TextStyle* style, int baseline);

/**
 * @brief Sets the decoration for a text style. Only one decoration can be set. To add multiple decorations, use
 * {@link OH_Drawing_AddTextStyleDecoration}.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param decoration Text decoration. For details about the available options, see {@link OH_Drawing_TextDecoration}.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleDecoration(OH_Drawing_TextStyle* style, int decoration);

/**
 * @brief Adds the decoration for a text style. Multiple decoration lines can be displayed.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param decoration Decoration to add. The value **1** means to add an underline, **2** means to add an overline, and *
 *     *4** means to add a strikethrough. You can add various decoration lines at a time via bitwise OR operations.
 *     <br>If a decoration style that is not in the {@link OH_Drawing_TextDecoration} enumeration is set, the original
 *     decoration is retained.
 * @since 18
 * @version 1.0
 */
void OH_Drawing_AddTextStyleDecoration(OH_Drawing_TextStyle* style, int decoration);

/**
 * @brief Removes the decoration for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param decoration Decoration to remove. The value **1** means to remove an underline, **2** means to remove an
 *     overline, and **4** means to remove a strikethrough. You can remove various text decorations at a time via
 *     bitwise OR operations.
 *     <br>If a decoration style that is not in the {@link OH_Drawing_TextDecoration} enumeration is set, the original
 *     decoration is retained.
 * @since 18
 * @version 1.0
 */
void OH_Drawing_RemoveTextStyleDecoration(OH_Drawing_TextStyle* style, int decoration);

/**
 * @brief Sets the decoration color for a text style. If this API is not called or **color** is set to **0**, the
 * decoration color follows the text color.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param color Color.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleDecorationColor(OH_Drawing_TextStyle* style, uint32_t color);

/**
 * @brief Sets the line height based on the multiple of the font size.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param fontHeight Multiple of the font size.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleFontHeight(OH_Drawing_TextStyle* style, double fontHeight);

/**
 * @brief Sets the font families for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param fontFamiliesNumber Number of font families. A negative number is not allowed.
 * @param fontFamilies Pointer to the font families.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleFontFamilies(OH_Drawing_TextStyle* style,
    int fontFamiliesNumber, const char* fontFamilies[]);

/**
 * @brief Sets the font style for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param fontStyle Font style. For details about the available options, see {@link OH_Drawing_FontStyle}.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleFontStyle(OH_Drawing_TextStyle* style, int fontStyle);

/**
 * @brief Sets the locale for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param locale Pointer to the locale. For example, **'en'** indicates English, **'zh-Hans'** indicates Simplified
 *     Chinese, and **'zh-Hant'** indicates Traditional Chinese. If it is not specified, the default locale is **'zh-
 *     Hans'**.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleLocale(OH_Drawing_TextStyle* style, const char* locale);

/**
 * @brief Sets the foreground brush for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param foregroundBrush Pointer to the {@link OH_Drawing_Brush} object, which is obtained from
 *     {@link OH_Drawing_BrushCreate}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTextStyleForegroundBrush(OH_Drawing_TextStyle* style, OH_Drawing_Brush* foregroundBrush);

/**
 * @brief Obtains the foreground brush of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param foregroundBrush Pointer to the {@link OH_Drawing_Brush} object, which is obtained from
 *     {@link OH_Drawing_BrushCreate}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleGetForegroundBrush(OH_Drawing_TextStyle* style, OH_Drawing_Brush* foregroundBrush);

/**
 * @brief Sets the foreground pen for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param foregroundPen Pointer to the {@link OH_Drawing_Pen} object, which is obtained from
 *     {@link OH_Drawing_PenCreate}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTextStyleForegroundPen(OH_Drawing_TextStyle* style, OH_Drawing_Pen* foregroundPen);

/**
 * @brief Obtains the foreground pen of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param foregroundPen Pointer to the {@link OH_Drawing_Pen} object, which is obtained from
 *     {@link OH_Drawing_PenCreate}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleGetForegroundPen(OH_Drawing_TextStyle* style, OH_Drawing_Pen* foregroundPen);

/**
 * @brief Sets the background brush for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param backgroundBrush Pointer to the {@link OH_Drawing_Brush} object, which is obtained from
 *     {@link OH_Drawing_BrushCreate}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTextStyleBackgroundBrush(OH_Drawing_TextStyle* style, OH_Drawing_Brush* backgroundBrush);

/**
 * @brief Obtains the background brush of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param backgroundBrush Pointer to the {@link OH_Drawing_Brush} object, which is obtained from
 *     {@link OH_Drawing_BrushCreate}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleGetBackgroundBrush(OH_Drawing_TextStyle* style, OH_Drawing_Brush* backgroundBrush);

/**
 * @brief Sets the background pen for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param backgroundPen Pointer to the {@link OH_Drawing_Pen} object, which is obtained from
 *     {@link OH_Drawing_PenCreate}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTextStyleBackgroundPen(OH_Drawing_TextStyle* style, OH_Drawing_Pen* backgroundPen);

/**
 * @brief Obtains the background pen of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param backgroundPen Pointer to the {@link OH_Drawing_Pen} object, which is obtained from
 *     {@link OH_Drawing_PenCreate}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleGetBackgroundPen(OH_Drawing_TextStyle* style, OH_Drawing_Pen* backgroundPen);

/**
 * @brief Creates an **OH_Drawing_TypographyCreate** object. Release this pointer by calling
 * {@link OH_Drawing_DestroyTypographyHandler} when this object is no longer needed. You are advised to use the
 * {@link OH_Drawing_CreateSharedFontCollection} function to create an {@link OH_Drawing_FontCollection} object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param fontCollection Pointer to the {@link OH_Drawing_FontCollection} object, which is obtained from
 *     {@link OH_Drawing_CreateFontCollection}.
 * @return Pointer to the **OH_Drawing_TypographyCreate** object created.
 * @since 8
 * @version 1.0
 */
OH_Drawing_TypographyCreate* OH_Drawing_CreateTypographyHandler(OH_Drawing_TypographyStyle* style,
    OH_Drawing_FontCollection* fontCollection);

/**
 * @brief Destroys an **OH_Drawing_TypographyCreate** object and reclaims the memory occupied by the object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler Pointer to the {@link OH_Drawing_TypographyCreate} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyHandler}.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_DestroyTypographyHandler(OH_Drawing_TypographyCreate* handler);

/**
 * @brief Pushes a text style into the text style stack. Any text added afterward will use the style currently on top
 * of the stack.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler Pointer to the {@link OH_Drawing_TypographyCreate} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyHandler}.
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_TypographyHandlerPushTextStyle(OH_Drawing_TypographyCreate* handler, OH_Drawing_TextStyle* style);

/**
 * @brief Adds text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler Pointer to the {@link OH_Drawing_TypographyCreate} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyHandler}.
 * @param text Pointer to the text content.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_TypographyHandlerAddText(OH_Drawing_TypographyCreate* handler, const char* text);

/**
 * @brief Pops the top text style out of the text style stack.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler Pointer to the {@link OH_Drawing_TypographyCreate} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyHandler}.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_TypographyHandlerPopTextStyle(OH_Drawing_TypographyCreate* handler);

/**
 * @brief Creates an **OH_Drawing_Typography** object. Release this pointer by calling
 * {@link OH_Drawing_DestroyTypography} when this object is no longer needed.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler Pointer to the {@link OH_Drawing_TypographyCreate} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyHandler}.
 * @return Pointer to the **OH_Drawing_Typography** object created.
 * @since 8
 * @version 1.0
 */
OH_Drawing_Typography* OH_Drawing_CreateTypography(OH_Drawing_TypographyCreate* handler);

/**
 * @brief Destroys an **OH_Drawing_Typography** object and reclaims the memory occupied by the object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_DestroyTypography(OH_Drawing_Typography* typography);

/**
 * @brief Lays out the typography.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param maxWidth Maximum text width.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_TypographyLayout(OH_Drawing_Typography* typography, double maxWidth);

/**
 * @brief Draws text from the upper left corner at a specified position. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called and applied.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param canvas Pointer to the **OH_Drawing_Canvas** object, which is obtained from {@link OH_Drawing_CanvasCreate}.
 * @param positionX X coordinate.
 * @param positionY Y coordinate.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_TypographyPaint(OH_Drawing_Typography* typography, OH_Drawing_Canvas* canvas,
    double positionX, double positionY);

/**
 * @brief Draws text along a path. To prevent text overlap caused by the text width exceeding the layout width, you are
 * advised to use {@link OH_Drawing_SetTypographyTextMaxLines} to limit the text to a single line.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param canvas Pointer to the **OH_Drawing_Canvas** object, which is obtained from {@link OH_Drawing_CanvasCreate}.
 * @param path Pointer to the **OH_Drawing_Path** object, which is obtained from {@link OH_Drawing_PathCreate}.
 * @param hOffset Horizontal offset of the text along the path (X axis). A positive number indicates that the text is
 *     moved forward, and a negative number indicates that the text is moved backward.
 * @param vOffset Vertical offset of the text along the path (Y axis). A positive number indicates that the text is
 *     moved downward, and a negative number indicates that the text is moved upward.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyPaintOnPath(OH_Drawing_Typography* typography, OH_Drawing_Canvas* canvas,
    OH_Drawing_Path* path, double hOffset, double vOffset);

/**
 * @brief Arranges the text in the constraint rectangle.
 *
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param constraintsRect Height and width of the constrained layout.
 * @param fitStrRangeArr As an output parameter, it contains the character range of the paragraph text that is actually
 *     contained. Pointer to array object {@link OH_Drawing_Array}.
 *     <br>Releases the memory through {@link OH_Drawing_ReleaseArrayBuffer}.
 * @param fitStrRangeArrayLen As an output parameter, it indicates the size of the contained string array.
 * @return Returns the OH_Drawing_RectSize object, indicating the actual rectangle of the paragraph text.
 * @since 24
 */
OH_Drawing_RectSize OH_Drawing_TypographyLayoutWithConstraintsWithBuffer(OH_Drawing_Typography* typography,
    OH_Drawing_RectSize constraintsRect, OH_Drawing_Array** fitStrRangeArr, size_t* fitStrRangeArrayLen);

/**
 * @brief Obtains the pointer to the OH_Drawing_Range object based on the array index.
 *
 * @param array Pointer to array object {@link OH_Drawing_Array}.
 * @param index Index of the target {@link OH_Drawing_Range} object in the array.
 * @return Returns the pointer to the OH_Drawing_Range object.
 * @since 24
 */
OH_Drawing_Range* OH_Drawing_GetRangeByArrayIndex(OH_Drawing_Array* array, size_t index);

/**
 * @brief Releases the memory occupied by the {@link OH_Drawing_Array} object.
 *
 * @param array Pointer to array object {@link OH_Drawing_Array}.
 *     <br>Supported array types:
 *     <br>Array of full font names, which is obtained through {@link OH_Drawing_GetSystemFontFullNamesByType}.
 *     <br>Array of text lines, which is obtained through {@link OH_Drawing_TypographyGetTextLines}.
 *     <br>Array of string indexes, which is obtained through {@link OH_Drawing_GetRunStringIndices}.
 *     <br>Array of rectangles, which is obtained through {@link OH_Drawing_RectCreateArray}.
 *     <br>Array of font descriptors, which is obtained through {@link OH_Drawing_GetFontFullDescriptorsFromStream} or {
 * @link OH_Drawing_GetFontFullDescriptorsFromPath}.
 *     <br>Array of text ranges, which is obtained through {@link OH_Drawing_TypographyLayoutWithConstraintsWithBuffer}.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if array is a null pointer or the type is not supported.
 * @since 24
 */
OH_Drawing_ErrorCode OH_Drawing_ReleaseArrayBuffer(OH_Drawing_Array* array);

/**
 * @brief Obtains the typography width set by the user. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @return Maximum width.
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetMaxWidth(OH_Drawing_Typography* typography);

/**
 * @brief Obtains the overall height of a typography object. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @return Height.
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetHeight(OH_Drawing_Typography* typography);

/**
 * @brief Obtains the width of the longest line in a typography object. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called. You are advised to round up the return value. If the text content is
 * empty, **0.0** is returned.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @return Width of the longest line.
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetLongestLine(OH_Drawing_Typography* typography);

/**
 * @brief Obtains the width of the longest line of a typography object, including its indentation. This function must
 * be called after {@link OH_Drawing_TypographyLayout} is called. You are advised to round up the return value. If the
 * text content is empty, **0.0** is returned.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @return Width of the longest line, including its indentation, in px.
 * @since 13
 * @version 1.1
 */
double OH_Drawing_TypographyGetLongestLineWithIndent(OH_Drawing_Typography* typography);

/**
 * @brief Obtains the minimum intrinsic width in a typography object. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @return Minimum intrinsic width.
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetMinIntrinsicWidth(OH_Drawing_Typography* typography);

/**
 * @brief Obtains the maximum intrinsic width in a typography object. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @return Maximum intrinsic width.
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetMaxIntrinsicWidth(OH_Drawing_Typography* typography);

/**
 * @brief Obtains the alphabetic baseline in a typography object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @return Alphabetic baseline.
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetAlphabeticBaseline(OH_Drawing_Typography* typography);

/**
 * @brief Obtains the ideographic baseline in a typography object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @return Ideographic baseline.
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetIdeographicBaseline(OH_Drawing_Typography* typography);

/**
 * @brief Adds a placeholder.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler Pointer to the {@link OH_Drawing_TypographyCreate} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyHandler}.
 * @param span Pointer to the {@link OH_Drawing_PlaceholderSpan} object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_TypographyHandlerAddPlaceholder(OH_Drawing_TypographyCreate* handler, OH_Drawing_PlaceholderSpan* span);

/**
 * @brief Checks whether the text in the typography object exceeds the line limit. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called. It returns **false** if the line limit is not set using
 * {@link OH_Drawing_SetTypographyTextMaxLines}.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @return Returns **true** if the maximum number of lines is exceeded; returns **false** otherwise.
 * @since 11
 * @version 1.0
 */
bool OH_Drawing_TypographyDidExceedMaxLines(OH_Drawing_Typography* typography);

/**
 * @brief Obtains text boxes in a given range of a typography object. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called. Release this pointer by calling
 * {@link OH_Drawing_TypographyDestroyTextBox} when this object is no longer needed.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param start Start position.
 * @param end End position.
 * @param heightStyle Height style. For details about the available options, see {@link OH_Drawing_RectHeightStyle}.
 * @param widthStyle Width style. For details about the available options, see {@link OH_Drawing_RectWidthStyle}.
 * @return Text box in the specified range. For details, see {@link OH_Drawing_TextBox}.
 * @since 11
 * @version 1.0
 */
OH_Drawing_TextBox* OH_Drawing_TypographyGetRectsForRange(OH_Drawing_Typography* typography,
    size_t start, size_t end, OH_Drawing_RectHeightStyle heightStyle, OH_Drawing_RectWidthStyle widthStyle);

/**
 * @brief Obtains text boxes for placeholders in a typography object. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called. Release this pointer by calling
 * {@link OH_Drawing_TypographyDestroyTextBox} when this object is no longer needed.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @return Placeholder text box. The return type is {@link OH_Drawing_TextBox}.
 * @since 11
 * @version 1.0
 */
OH_Drawing_TextBox* OH_Drawing_TypographyGetRectsForPlaceholders(OH_Drawing_Typography* typography);

/**
 * @brief Obtains the left position of a text box.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textbox Pointer to the **OH_Drawing_TextBox** object, which is obtained from
 *     {@link OH_Drawing_TypographyGetRectsForRange} or {@link OH_Drawing_TypographyGetRectsForPlaceholders}.
 * @param index Index of the text box.
 * @return Left position.
 * @since 11
 * @version 1.0
 */
float OH_Drawing_GetLeftFromTextBox(OH_Drawing_TextBox* textbox, int index);

/**
 * @brief Obtains the right position of a text box.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textbox Pointer to the **OH_Drawing_TextBox** object, which is obtained from
 *     {@link OH_Drawing_TypographyGetRectsForRange} or {@link OH_Drawing_TypographyGetRectsForPlaceholders}.
 * @param index Index of the text box.
 * @return Right position.
 * @since 11
 * @version 1.0
 */
float OH_Drawing_GetRightFromTextBox(OH_Drawing_TextBox* textbox, int index);

/**
 * @brief Obtains the top position of a text box.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textbox Pointer to the **OH_Drawing_TextBox** object, which is obtained from
 *     {@link OH_Drawing_TypographyGetRectsForRange} or {@link OH_Drawing_TypographyGetRectsForPlaceholders}.
 * @param index Index of the text box.
 * @return Top position.
 * @since 11
 * @version 1.0
 */
float OH_Drawing_GetTopFromTextBox(OH_Drawing_TextBox* textbox, int index);

/**
 * @brief Obtains the bottom position of a text box.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textbox Pointer to the **OH_Drawing_TextBox** object, which is obtained from
 *     {@link OH_Drawing_TypographyGetRectsForRange} or {@link OH_Drawing_TypographyGetRectsForPlaceholders}.
 * @param index Index of the text box.
 * @return Bottom position.
 * @since 11
 * @version 1.0
 */
float OH_Drawing_GetBottomFromTextBox(OH_Drawing_TextBox* textbox, int index);

/**
 * @brief Obtains the text direction of a text box.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textbox Pointer to the {@link OH_Drawing_TextBox} object, which is obtained from
 *     {@link OH_Drawing_TypographyGetRectsForRange} or {@link OH_Drawing_TypographyGetRectsForPlaceholders}.
 * @param index Index of the text box.
 * @return Text direction.
 * @since 11
 * @version 1.0
 */
int OH_Drawing_GetTextDirectionFromTextBox(OH_Drawing_TextBox* textbox, int index);

/**
 * @brief Obtains the number of text boxes.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textBox Pointer to the **OH_Drawing_TextBox** object, which is obtained from
 *     {@link OH_Drawing_TypographyGetRectsForRange} or {@link OH_Drawing_TypographyGetRectsForPlaceholders}.
 * @return Number of text boxes.
 * @since 11
 * @version 1.0
 */
size_t OH_Drawing_GetSizeOfTextBox(OH_Drawing_TextBox* textBox);

/**
 * @brief Obtains the position and affinity of the glyph at the given coordinates.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param dx X coordinate.
 * @param dy Y coordinate.
 * @return {@link OH_Drawing_PositionAndAffinity} struct that holds the position and affinity of the glyph cluster.
 * @since 11
 * @version 1.0
 * @deprecated since 18
 * @useinstead OH_Drawing_TypographyGetGlyphPositionAtCoordinateWithCluster
 */
OH_Drawing_PositionAndAffinity* OH_Drawing_TypographyGetGlyphPositionAtCoordinate(OH_Drawing_Typography* typography,
    double dx, double dy);

/**
 * @brief Obtains the position and affinity of the glyph cluster to which the glyph at the given coordinates belongs.
 * The glyph cluster is a container that holds one or more glyphs.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param dx X coordinate.
 * @param dy Y coordinate.
 * @return {@link OH_Drawing_PositionAndAffinity} struct that holds the position and affinity of the glyph cluster.
 * @since 11
 * @version 1.0
 */
OH_Drawing_PositionAndAffinity* OH_Drawing_TypographyGetGlyphPositionAtCoordinateWithCluster(
    OH_Drawing_Typography* typography, double dx, double dy);

/**
 * @brief Obtains the position attribute of an **OH_Drawing_PositionAndAffinity** object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param positionAndAffinity Pointer to the **OH_Drawing_PositionAndAffinity** object, which is obtained from
 *     {@link OH_Drawing_TypographyGetGlyphPositionAtCoordinate} or
 *     {@link OH_Drawing_TypographyGetGlyphPositionAtCoordinateWithCluster}.
 * @return Position attribute.
 * @since 11
 * @version 1.0
 */
size_t OH_Drawing_GetPositionFromPositionAndAffinity(OH_Drawing_PositionAndAffinity* positionAndAffinity);

/**
 * @brief Obtains the affinity attribute of an **OH_Drawing_PositionAndAffinity** object. The affinity determines
 * whether the font is close to the front text or rear text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param positionAndAffinity Pointer to the **OH_Drawing_PositionAndAffinity** object, which is obtained from
 *     {@link OH_Drawing_TypographyGetGlyphPositionAtCoordinate} or
 *     {@link OH_Drawing_TypographyGetGlyphPositionAtCoordinateWithCluster}.
 * @return Affinity attribute.
 * @since 11
 * @version 1.0
 */
int OH_Drawing_GetAffinityFromPositionAndAffinity(OH_Drawing_PositionAndAffinity* positionAndAffinity);

/**
 * @brief Obtains the word boundary in a typography object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param offset Index of the word.
 * @return {@link OH_Drawing_Range} struct that holds the word boundary.
 * @since 11
 * @version 1.0
 */
OH_Drawing_Range* OH_Drawing_TypographyGetWordBoundary(OH_Drawing_Typography* typography, size_t offset);

/**
 * @brief Obtains the start position of an **OH_Drawing_Range** object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param range Pointer to the **OH_Drawing_Range** object, which is obtained from
 *     {@link OH_Drawing_TypographyGetWordBoundary}.
 * @return Start position.
 * @since 11
 * @version 1.0
 */
size_t OH_Drawing_GetStartFromRange(OH_Drawing_Range* range);

/**
 * @brief Obtains the end position of an **OH_Drawing_Range** object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param range Pointer to the **OH_Drawing_Range** object, which is obtained from
 *     {@link OH_Drawing_TypographyGetWordBoundary}.
 * @return End position.
 * @since 11
 * @version 1.0
 */
size_t OH_Drawing_GetEndFromRange(OH_Drawing_Range* range);

/**
 * @brief Obtains the number of lines in a typography object. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @return Number of rows obtained.
 * @since 11
 * @version 1.0
 */
size_t OH_Drawing_TypographyGetLineCount(OH_Drawing_Typography* typography);

/**
 * @brief Sets the decoration style for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param decorationStyle Text decoration style. For details about the available options, see
 *     {@link OH_Drawing_TextDecorationStyle}.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTextStyleDecorationStyle(OH_Drawing_TextStyle* style, int decorationStyle);

/**
 * @brief Sets the thickness scale factor for the decoration style of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param decorationThicknessScale Thickness scaling ratio. The default value is **1**. If the value is less than or
 *     equal to 0, no decoration line is drawn.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTextStyleDecorationThicknessScale(OH_Drawing_TextStyle* style, double decorationThicknessScale);

/**
 * @brief Sets the letter spacing for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param letterSpacing Letter spacing.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTextStyleLetterSpacing(OH_Drawing_TextStyle* style, double letterSpacing);

/**
 * @brief Sets the word spacing for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param wordSpacing Letter spacing.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTextStyleWordSpacing(OH_Drawing_TextStyle* style, double wordSpacing);

/**
 * @brief Sets whether to enable half leading for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param halfLeading Whether the half leading takes effect. **true** means yes; **false** otherwise.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTextStyleHalfLeading(OH_Drawing_TextStyle* style, bool halfLeading);

/**
 * @brief Sets the ellipsis content for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param ellipsis Pointer to the ellipsis content. The data type is a pointer pointing to char.
 * @since 11
 * @version 1.0
 * @deprecated since 18
 * @useinstead OH_Drawing_SetTypographyTextEllipsis
 */
void OH_Drawing_SetTextStyleEllipsis(OH_Drawing_TextStyle* style, const char* ellipsis);

/**
 * @brief Sets the ellipsis style for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param ellipsisModal Ellipsis style. For details about the available options, see {@link OH_Drawing_EllipsisModal}.
 * @since 11
 * @version 1.0
 * @deprecated since 18
 * @useinstead OH_Drawing_SetTypographyTextEllipsisModal
 */
void OH_Drawing_SetTextStyleEllipsisModal(OH_Drawing_TextStyle* style, int ellipsisModal);

/**
 * @brief Sets the text break strategy.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param breakStrategy Break strategy. For details about the available options, see {@link OH_Drawing_BreakStrategy}.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextBreakStrategy(OH_Drawing_TypographyStyle* style, int breakStrategy);

/**
 * @brief Sets the word break type.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param wordBreakType Word break type. For details about the available options, see {@link OH_Drawing_WordBreakType}.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextWordBreakType(OH_Drawing_TypographyStyle* style, int wordBreakType);

/**
 * @brief Sets the ellipsis style for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TypographyStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param ellipsisModal Ellipsis style. For details about the available options, see {@link OH_Drawing_EllipsisModal}.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextEllipsisModal(OH_Drawing_TypographyStyle* style, int ellipsisModal);

/**
 * @brief Obtains the line height in a typography object. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param lineNumber Target line.
 * @return Obtains the height of a given line.
 * @since 11
 * @version 1.0
 */
double OH_Drawing_TypographyGetLineHeight(OH_Drawing_Typography* typography, int lineNumber);

/**
 * @brief Obtains the line width of a specified line. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param lineNumber Target line.
 * @return Obtains the width of a given line.
 * @since 11
 * @version 1.0
 */
double OH_Drawing_TypographyGetLineWidth(OH_Drawing_Typography* typography, int lineNumber);

/**
 * @brief Obtains the line bounds in a typography object. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called. This function can only be used to obtain the bounds of existing lines.
 *  That is, the line index must start from 0, and the maximum index is {@link OH_Drawing_TypographyGetLineCount} – 1.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param lineNumber Row index.
 * @param includeSpaces Whether the returned bounds contain spaces. The value **true** means that the bounds contain
 *     spaces, and **false** means the opposite.
 * @return Pointer to the {@link OH_Drawing_Range} object. If the line index is invalid, **start** and **end** in the
 *     result value are both **0**.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Range* OH_Drawing_TypographyGetLineTextRange(OH_Drawing_Typography* typography,
    int lineNumber, bool includeSpaces);

/**
 * @brief Creates an **OH_Drawing_FontDescriptor** object to describe the detailed information about a system font.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return Pointer to the created {@link OH_Drawing_FontDescriptor} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontDescriptor* OH_Drawing_CreateFontDescriptor(void);

/**
 * @brief Destroys an **OH_Drawing_FontDescriptor** object and reclaims the memory occupied by the object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param descriptor Pointer to the {@link OH_Drawing_FontDescriptor} object, which is obtained from
 *     {@link OH_Drawing_CreateFontDescriptor}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroyFontDescriptor(OH_Drawing_FontDescriptor* descriptor);

/**
 * @brief Creates an **OH_Drawing_FontParser** object to parse a system font.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return Pointer to the created {@link OH_Drawing_FontParser} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontParser* OH_Drawing_CreateFontParser(void);

/**
 * @brief Destroys an **OH_Drawing_FontParser** object and reclaims the memory occupied by the object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param parser Pointer to the {@link OH_Drawing_FontParser} object, which is obtained from
 *     {@link OH_Drawing_CreateFontParser}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroyFontParser(OH_Drawing_FontParser* parser);

/**
 * @brief Obtains the list of system fonts. This function can be used only on 2-in-1 devices and phones.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontParser Pointer to the {@link OH_Drawing_FontParser} object, which is obtained from
 *     {@link OH_Drawing_CreateFontParser}.
 * @param num Pointer to the number of system font names.
 * @return System font list.
 * @since 12
 * @version 1.0
 */
char** OH_Drawing_FontParserGetSystemFontList(OH_Drawing_FontParser* fontParser, size_t* num);

/**
 * @brief Reclaims the memory occupied by the system font list.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontList Double pointer to the list of system font names.
 * @param num Number of system font names.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroySystemFontList(char** fontList, size_t num);

/**
 * @brief Obtains the descriptor of a system font based on the font name.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontParser Pointer to the {@link OH_Drawing_FontParser} object, which is obtained from
 *     {@link OH_Drawing_CreateFontParser}.
 * @param name Pointer to the system font name.
 * @return Font descriptor object. Release this pointer by calling {@link OH_Drawing_DestroyFontParser} when this
 *     object is no longer needed.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontDescriptor* OH_Drawing_FontParserGetFontByName(OH_Drawing_FontParser* fontParser, const char* name);

/**
 * @brief Obtains the line metrics in a typography object. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called. Release this pointer by calling {@link OH_Drawing_DestroyLineMetrics}
 * when this object is no longer needed.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @return Pointer to the {@link OH_Drawing_LineMetrics} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_LineMetrics* OH_Drawing_TypographyGetLineMetrics(OH_Drawing_Typography* typography);

/**
 * @brief Obtains the number of lines.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lineMetrics Pointer to the {@link OH_Drawing_LineMetrics} object, which is obtained from
 *     {@link OH_Drawing_LineMetrics}.
 * @return Number of lines.
 * @since 12
 * @version 1.0
 */
size_t OH_Drawing_LineMetricsGetSize(OH_Drawing_LineMetrics* lineMetrics);

/**
 * @brief Destroys an **OH_Drawing_LineMetrics** object and reclaims the memory occupied by the object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lineMetrics Pointer to the {@link OH_Drawing_LineMetrics} object, which is obtained from
 *     {@link OH_Drawing_LineMetrics}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroyLineMetrics(OH_Drawing_LineMetrics* lineMetrics);

/**
 * @brief Obtains the metrics of the given line in a typography object. For details, see the
 * {@link OH_Drawing_LineMetr} struct. This function must be called after {@link OH_Drawing_TypographyLayout} is called.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param lineNumber Line No.
 * @param lineMetric Pointer to the {@link OH_Drawing_LineMetrics} object, which is obtained from
 *     {@link OH_Drawing_LineMetrics}.
 * @return Whether the metrics of the given line is obtained. **true** means yes; **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyGetLineMetricsAt(OH_Drawing_Typography* typography,
    int lineNumber, OH_Drawing_LineMetrics* lineMetric);

/**
 * @brief Sets the ellipsis text for a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param ellipsis Ellipsis text.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextEllipsis(OH_Drawing_TypographyStyle* style, const char* ellipsis);

/**
 * @brief Sets the locale for a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param locale Pointer to the locale. For example, **'en'** indicates English, **'zh-Hans'** indicates Simplified
 *     Chinese, and **'zh-Hant'** indicates Traditional Chinese.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLocale(OH_Drawing_TypographyStyle* style, const char* locale);

/**
 * @brief Sets the text split ratio.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param textSplitRatio Text split ratio.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextSplitRatio(OH_Drawing_TypographyStyle* style, float textSplitRatio);

/**
 * @brief Obtains the default text style of a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Pointer to the {@link OH_Drawing_TextStyle} object. Release this pointer by calling
 *     {@link OH_Drawing_DestroyTextStyle} when this object is no longer needed.
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextStyle* OH_Drawing_TypographyGetTextStyle(OH_Drawing_TypographyStyle* style);

/**
 * @brief Obtains the text alignment mode.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Text alignment mode.
 * @since 12
 * @version 1.0
 * @deprecated since 18
 * @useinstead OH_Drawing_TypographyStyleGetEffectiveAlignment
 */
int OH_Drawing_TypographyGetEffectiveAlignment(OH_Drawing_TypographyStyle* style);

/**
 * @brief Checks whether the maximum number of lines is limited for text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Returns **true** if that the maximum number of lines is limited; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyIsLineUnlimited(OH_Drawing_TypographyStyle* style);

/**
 * @brief Checks whether an ellipsis is configured for a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Whether ellipsis is configured for the specified typography style. **true** means yes; **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyIsEllipsized(OH_Drawing_TypographyStyle* style);

/**
 * @brief Sets a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextStyle(OH_Drawing_TypographyStyle* handler, OH_Drawing_TextStyle* style);

/**
 * @brief Obtains the font metrics of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param fontmetrics Pointer to the {@link OH_Drawing_Font_Metrics} object, which is obtained from
 *     {@link OH_Drawing_Font_Metrics}.
 * @return Whether the font attributes are obtained. **true** means yes; **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TextStyleGetFontMetrics(OH_Drawing_Typography* typography,
    OH_Drawing_TextStyle* style, OH_Drawing_Font_Metrics* fontmetrics);

/**
 * @brief Obtains the metrics of a given line or the metrics of the first character in a given line in a typography
 * object. This function must be called after {@link OH_Drawing_TypographyLayout} is called.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param lineNumber Row No.
 * @param oneLine Whether to obtain the metrics of the entire line. The value **true** means to obtain the metrics of
 *     the entire line, and **false** means to obtain the metrics of the first character in the line.
 * @param includeWhitespace Whether the text width includes the whitespace. **true** means yes; **false** otherwise.
 * @param drawingLineMetrics Pointer to the {@link OH_Drawing_LineMetrics} object, which is obtained from
 *     {@link OH_Drawing_LineMetrics}.
 * @return Returns **true** if the metrics of the given line or the metrics of the first character in the given line is
 *     obtained; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyGetLineInfo(OH_Drawing_Typography* typography, int lineNumber, bool oneLine,
    bool includeWhitespace, OH_Drawing_LineMetrics* drawingLineMetrics);

/**
 * @brief Sets the default font weight for a typography style. Currently, only the default system font supports font
 * weight adjustment. For other fonts, if the weight is less than semi-bold, there is no variation in stroke thickness.
 * If the weight is greater than or equal to semi-bold, it might result in a fake bold effect.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param weight Font weight.
 *     <br>For details about the available options, see {@link OH_Drawing_FontWeight}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextFontWeight(OH_Drawing_TypographyStyle* style, int weight);

/**
 * @brief Sets the default font style for a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param fontStyle Font style. For details about the available options, see {@link OH_Drawing_FontStyle}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextFontStyle(OH_Drawing_TypographyStyle* style, int fontStyle);

/**
 * @brief Sets the font family name for text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param fontFamily Pointer to the name of the font family.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextFontFamily(OH_Drawing_TypographyStyle* style, const char* fontFamily);

/**
 * @brief Sets the font size for text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param fontSize Font size, which must be greater than 0.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextFontSize(OH_Drawing_TypographyStyle* style, double fontSize);

/**
 * @brief Sets the font height for text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param fontHeight Font height.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextFontHeight(OH_Drawing_TypographyStyle* style, double fontHeight);

/**
 * @brief Sets whether to enable half leading for text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param halfLeading Whether to enable half leading. The value **true** means to enable half lading, and **false**
 *     means the opposite.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextHalfLeading(OH_Drawing_TypographyStyle* style, bool halfLeading);

/**
 * @brief Sets whether to enable the text line style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param useLineStyle Whether to enable the line style. The value **true** means to enable the line style, and **false*
 *     * means the opposite.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextUseLineStyle(OH_Drawing_TypographyStyle* style, bool useLineStyle);

/**
 * @brief Sets the text font weight of the strut style in a typography style. Currently, only the default system font
 * supports font weight adjustment. For other fonts, if the weight is less than semi-bold, there is no variation in
 * stroke thickness. If the weight is greater than or equal to semi-bold, it might result in a fake bold effect.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param weight Font weight. For details about the available options, see {@link OH_Drawing_FontWeight}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleFontWeight(OH_Drawing_TypographyStyle* style, int weight);

/**
 * @brief Sets the font style of the strut style in a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param fontStyle Font style. For details about the available options, see {@link OH_Drawing_FontStyle}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleFontStyle(OH_Drawing_TypographyStyle* style, int fontStyle);

/**
 * @brief Sets the font families for a text line style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param fontFamiliesNumber Number of font families.
 * @param fontFamilies Pointer to the font families.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleFontFamilies(OH_Drawing_TypographyStyle* style,
    int fontFamiliesNumber, const char* fontFamilies[]);

/**
 * @brief Sets the font size for a text line style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param lineStyleFontSize Font size, which must be greater than 0.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleFontSize(OH_Drawing_TypographyStyle* style, double lineStyleFontSize);

/**
 * @brief Sets the font height for a text line style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param lineStyleFontHeight Font height.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleFontHeight(OH_Drawing_TypographyStyle* style, double lineStyleFontHeight);

/**
 * @brief Sets whether to enable half leading for a text line style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param lineStyleHalfLeading Whether the half leading takes effect. **true** means yes; **false** otherwise.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleHalfLeading(OH_Drawing_TypographyStyle* style, bool lineStyleHalfLeading);

/**
 * @brief Sets the spacing scale factor for a text line style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param spacingScale Spacing ratio.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleSpacingScale(OH_Drawing_TypographyStyle* style, double spacingScale);

/**
 * @brief Sets whether to enable the text line style only.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param lineStyleOnly Whether to enable the line style only. **true** means yes; **false** otherwise.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleOnly(OH_Drawing_TypographyStyle* style, bool lineStyleOnly);

/**
 * @brief Creates an **OH_Drawing_TextShadow** object. Release this pointer by calling
 * {@link OH_Drawing_DestroyTextShadow} when this object is no longer needed.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return Pointer to the **OH_Drawing_TextShadow** object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextShadow* OH_Drawing_CreateTextShadow(void);

/**
 * @brief Destroys an **OH_Drawing_TextShadow** object and reclaims the memory occupied by the object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param shadow Pointer to the {@link OH_Drawing_TextShadow} object, which is obtained from
 *     {@link OH_Drawing_CreateTextShadow}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroyTextShadow(OH_Drawing_TextShadow* shadow);

/**
 * @brief Obtains a text shadow container. Release this pointer by calling {@link OH_Drawing_DestroyTextShadows} when
 * this object is no longer needed.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Pointer to the {@link OH_Drawing_TextShadow} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextShadow* OH_Drawing_TextStyleGetShadows(OH_Drawing_TextStyle* style);

/**
 * @brief Obtains the size of a text shadow container.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Size of a text shadow container.
 * @since 12
 * @version 1.0
 */
int OH_Drawing_TextStyleGetShadowCount(OH_Drawing_TextStyle* style);

/**
 * @brief Adds a shadow to a text shadow container.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param shadow Pointer to the {@link OH_Drawing_TextShadow} object, which is obtained from
 *     {@link OH_Drawing_CreateTextShadow}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleAddShadow(OH_Drawing_TextStyle* style, const OH_Drawing_TextShadow* shadow);

/**
 * @brief Clears all shadows in a text shadow container.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleClearShadows(OH_Drawing_TextStyle* style);

/**
 * @brief Obtains a shadow with a given index in a text shadow container.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param index Index.
 * @return Pointer to the {@link OH_Drawing_TextShadow} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextShadow* OH_Drawing_TextStyleGetShadowWithIndex(OH_Drawing_TextStyle* style, int index);

/**
 * @brief Sets indents for typography. If this function is not called, texts will have no indentation applied.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param indentsNumber Number of indents. The value must be less than or equal to the length of the indents array to
 *     avoid display exceptions caused by access to the out-of-bounds array.
 * @param indents Pointer to a floating-point array, in which each element indicates an indentation width, in px.
 *     Before calling {@link OH_Drawing_Typography} API, you need to declare and initialize the floating-point array.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographySetIndents(OH_Drawing_Typography* typography, int indentsNumber, const float indents[]);

/**
 * @brief Obtains indents with a given index in a typography object. The line index starts from 0.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param index Index.
 * @return Indents.
 * @since 12
 * @version 1.0
 */
float OH_Drawing_TypographyGetIndentsWithIndex(OH_Drawing_Typography* typography, int index);

/**
 * @brief Reclaims the memory occupied by the vector consisting of the **OH_Drawing_TextShadow** objects.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param shadow Pointer to the {@link OH_Drawing_TextShadow} object, which is obtained from
 *     {@link OH_Drawing_CreateTextShadow}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroyTextShadows(OH_Drawing_TextShadow* shadow);

/**
 * @brief Sets a text height modifier pattern.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param heightMode Text height modifier mode. The value is an enumerated value of the
 *     {@link OH_Drawing_TextHeightBehavior} type.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyTextSetHeightBehavior(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TextHeightBehavior heightMode);

/**
 * @brief Obtains the text height modifier pattern.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Text height modifier mode, which is an enumerated value of the {@link OH_Drawing_TextHeightBehavior} type.
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextHeightBehavior OH_Drawing_TypographyTextGetHeightBehavior(OH_Drawing_TypographyStyle* style);

/**
 * @brief Sets a background rectangle and style ID for a text style. The style ID is valid only when the background box
 * is a rounded rectangle.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param rectStyleInfo Pointer to the {@link OH_Drawing_RectStyle_Info} object.
 * @param styleId Style ID. The style ID is valid only when the background box is a rounded rectangle. Text processing
 *     is divided into multiple segments. Each segment has its own text style. **id** indicates the sequence number of
 *     the background box in which the segment is drawn.
 *     <br>If the ID of each segment in a row is **0**, all segments are drawn in the same background box. If a row
 *     contains segments with IDs **0** and **1**, the segment with ID **0** is drawn in a background box, and the
 *     segment with ID **1** is drawn in another background box. Other cases can be deduced in the same way.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleSetBackgroundRect(OH_Drawing_TextStyle* style,
    const OH_Drawing_RectStyle_Info* rectStyleInfo, int styleId);

/**
 * @brief Add symbols in creating typography.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler Indicates the pointer to an <b>OH_Drawing_TypographyCreate</b> object.
 * @param symbol Indicates the symbol to set.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyHandlerAddSymbol(OH_Drawing_TypographyCreate* handler, uint32_t symbol);

/**
 * @brief Adds a font feature for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param tag Pointer to the string identified by the keyword in the font feature key-value pair.
 * @param value Value of the font feature key-value pair.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleAddFontFeature(OH_Drawing_TextStyle* style, const char* tag, int value);

/**
 * @brief Adds a font variation. This function takes effect only when the corresponding font file (.ttf file) supports
 * variable adjustment. Otherwise, calling this function does not take effect.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param axis Pointer to the key in the font variation key-value pair. Currently, only **'wght'** is supported,
 *     indicating the font weight.
 * @param value Value of the font variation key-value pair. Currently, the value range of **'wght'** for the default
 *     font is \[0,900\].
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleAddFontVariation(OH_Drawing_TextStyle* style, const char* axis, const float value);

/**
 * @brief Adds the normalized variable font attributes. This function takes effect only when the corresponding font
 * file (.ttf file) supports variable adjustment.
 *
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param axis Pointer to the key in the font variation key-value pair.
 * @param normalizedValue Value of the font variation key-value pair. The normalized value range is [-1,1], mapping the
 *     range from the minimum value to the maximum value configured in the font file. **0** indicates the default value
 *     configured in the font file.
 * @since 24
 */
void OH_Drawing_TextStyleAddFontVariationWithNormalization(OH_Drawing_TextStyle* style,
    const char* axis, const float normalizedValue);

/**
 * @brief Obtains all the contents in a font feature map container of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Pointer to the font feature struct, which stores all the contents obtained.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontFeature* OH_Drawing_TextStyleGetFontFeatures(OH_Drawing_TextStyle* style);

/**
 * @brief Reclaims the memory occupied by the struct array that holds all the font features.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontFeature Pointer to the struct array that holds all the font features, which is obtained from
 *     {@link OH_Drawing_TextStyleGetFontFeatures}.
 * @param fontFeatureSize Size of the struct array that holds all the font features.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleDestroyFontFeatures(OH_Drawing_FontFeature* fontFeature, size_t fontFeatureSize);

/**
 * @brief Obtains the size of a font feature map container in a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Size of a font feature map container.
 * @since 12
 * @version 1.0
 */
size_t OH_Drawing_TextStyleGetFontFeatureSize(OH_Drawing_TextStyle* style);

/**
 * @brief Clears all the contents in a font feature map container of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleClearFontFeature(OH_Drawing_TextStyle* style);

/**
 * @brief Sets a baseline drift for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param lineShift Baseline drift of the text style.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleSetBaselineShift(OH_Drawing_TextStyle* style, double lineShift);

/**
 * @brief Obtains the baseline drift of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the **OH_Drawing_TextStyle** object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Baseline shift.
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TextStyleGetBaselineShift(OH_Drawing_TextStyle* style);

/**
 * @brief Obtains the color of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Text color.
 * @since 12
 * @version 1.0
 */
uint32_t OH_Drawing_TextStyleGetColor(OH_Drawing_TextStyle* style);

/**
 * @brief Obtains the decoration style of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Text decoration style. For details, see {@link OH_Drawing_TextDecorationStyle}.
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextDecorationStyle OH_Drawing_TextStyleGetDecorationStyle(OH_Drawing_TextStyle* style);

/**
 * @brief Obtains the font weight of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Font weight. For details, see {@link OH_Drawing_FontWeight}.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontWeight OH_Drawing_TextStyleGetFontWeight(OH_Drawing_TextStyle* style);

/**
 * @brief Obtains the font style of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Font style. For details, see {@link OH_Drawing_FontStyle}.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyle OH_Drawing_TextStyleGetFontStyle(OH_Drawing_TextStyle* style);

/**
 * @brief Obtains the baseline of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Font baseline position. For details, see {@link OH_Drawing_TextBaseline}.
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextBaseline OH_Drawing_TextStyleGetBaseline(OH_Drawing_TextStyle* style);

/**
 * @brief Obtains the font families of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param num Pointer to the number of font families.
 * @return Font families.
 * @since 12
 * @version 1.0
 */
char** OH_Drawing_TextStyleGetFontFamilies(OH_Drawing_TextStyle* style, size_t* num);

/**
 * @brief Reclaims the memory occupied by the font families, where **num** specifies the number of font families.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontFamilies Double pointer to the font families.
 * @param num Number of font families.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleDestroyFontFamilies(char** fontFamilies, size_t num);

/**
 * @brief Obtains the font size of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Font size.
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TextStyleGetFontSize(OH_Drawing_TextStyle* style);

/**
 * @brief Obtains the letter spacing of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Letter spacing.
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TextStyleGetLetterSpacing(OH_Drawing_TextStyle* style);

/**
 * @brief Obtains the word spacing of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Word spacing.
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TextStyleGetWordSpacing(OH_Drawing_TextStyle* style);

/**
 * @brief Obtains the font height of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Font height of a text style.
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TextStyleGetFontHeight(OH_Drawing_TextStyle* style);

/**
 * @brief Checks whether half leading is enabled for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Whether half leading is enabled for a text style. **true** means enabled; **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TextStyleGetHalfLeading(OH_Drawing_TextStyle* style);

/**
 * @brief Vertical alignment mode of the text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param align Vertical alignment mode of the text. The default mode is baseline alignment. For details about other
 *     options, see {@link OH_Drawing_TextVerticalAlignment}.
 * @since 20
 * @version 1.0
 */
void OH_Drawing_SetTypographyVerticalAlignment(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TextVerticalAlignment align);

/**
 * @brief Obtains the locale of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Pointer to the locale in the format of language-country. For example, zh-CN indicates Chinese (China), and
 *     en-US indicates English (United States). For details, see BCP 47.
 * @since 12
 * @version 1.0
 */
const char* OH_Drawing_TextStyleGetLocale(OH_Drawing_TextStyle* style);

/**
 * @brief Sets whether to use superscript or subscript in text layout. If this API is not called, the feature is
 * disabled by default.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param textBadgeType Sets whether to use superscript or subscript in text layout. **TEXT_SUPERSCRIPT** indicates
 *     that superscript is enabled, and **TEXT_SUBSCRIPT** indicates that subscript is enabled. The default value is **
 *     TEXT_BADGE_NONE**, indicating that neither superscript nor subscript is enabled.
 * @since 20
 */
void OH_Drawing_SetTextStyleBadgeType(OH_Drawing_TextStyle* style, OH_Drawing_TextBadgeType textBadgeType);

/**
 * @brief Sets the font style, including the font weight, width, and slant, for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingTextStyle Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @param fontStyle Font style, including the font weight, width, and slant.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTextStyleFontStyleStruct(OH_Drawing_TextStyle* drawingTextStyle,
    OH_Drawing_FontStyleStruct fontStyle);

/**
 * @brief Obtains the font style, including the font weight, width, and slant, of a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingTextStyle Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Font style, including the font weight, width, and slant.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyleStruct OH_Drawing_TextStyleGetFontStyleStruct(OH_Drawing_TextStyle* drawingTextStyle);

/**
 * @brief Sets the font style, including the font weight, width, and slant, for the default text style of a typography
 * style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingStyle Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param fontStyle Font style, including the font weight, width, and slant.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyStyleFontStyleStruct(OH_Drawing_TypographyStyle* drawingStyle,
    OH_Drawing_FontStyleStruct fontStyle);

/**
 * @brief Obtains the font style, including the font weight, width, and slant, of the default text style of a
 * typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingStyle Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Font style, including the font weight, width, and slant.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyleStruct OH_Drawing_TypographyStyleGetFontStyleStruct(OH_Drawing_TypographyStyle* drawingStyle);

/**
 * @brief Checks whether two text styles are equal. The word width property is not involved in the comparison.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the first text style.
 * @param comparedStyle Pointer to the first text style.
 * @return Whether two text style objects are equal. **true** if the source rectangle is equal to the destination
 *     rectangle; **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TextStyleIsEqual(const OH_Drawing_TextStyle* style, const OH_Drawing_TextStyle* comparedStyle);

/**
 * @brief Checks whether the font style properties of two text styles are equal.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the first text style.
 * @param comparedStyle Pointer to the first text style.
 * @return Returns **true** if the two are equal; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TextStyleIsEqualByFont(const OH_Drawing_TextStyle* style, const OH_Drawing_TextStyle* comparedStyle);

/**
 * @brief Checks whether two text styles have the same font style type.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the first text style.
 * @param comparedStyle Pointer to the first text style.
 * @param textStyleType Text style types as in {@link OH_Drawing_TextStyleType}.
 * @return Whether two text styles have the same font style type. **true** means yes; **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TextStyleIsAttributeMatched(const OH_Drawing_TextStyle* style,
    const OH_Drawing_TextStyle* comparedStyle, OH_Drawing_TextStyleType textStyleType);

/**
 * @brief Adds a placeholder.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleSetPlaceholder(OH_Drawing_TextStyle* style);

/**
 * @brief Checks whether a placeholder is set for a text style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTextStyle}.
 * @return Checks whether a placeholder is set for a text style. **true** means yes; **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TextStyleIsPlaceholder(OH_Drawing_TextStyle* style);

/**
 * @brief Obtains the text alignment mode.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Text alignment modes as in {@link OH_Drawing_TextAlign}.
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextAlign OH_Drawing_TypographyStyleGetEffectiveAlignment(OH_Drawing_TypographyStyle* style);

/**
 * @brief Checks whether font hinting is enabled for a typography style. Font hinting is used to improve the
 * readability and appearance of small-sized text when rendering it.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Whether to enable font hinting for a typography style. **true**: enabled; **false**: disabled.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyStyleIsHintEnabled(OH_Drawing_TypographyStyle* style);

/**
 * @brief Obtains the system font configuration.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param errorCode Error code. For details, see {@link OH_Drawing_FontConfigInfoErrorCode}.
 * @return Pointer to the system font configuration. When it is no longer required, call
 *     {@link OH_Drawing_DestroySystemFontConfigInfo} to release the pointer to the object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontConfigInfo* OH_Drawing_GetSystemFontConfigInfo(OH_Drawing_FontConfigInfoErrorCode* errorCode);

/**
 * @brief Reclaims the memory occupied by the system font configuration.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawFontCfgInfo Pointer to the {@link OH_Drawing_FontConfigInfo} object, which is obtained from
 *     {@link OH_Drawing_GetSystemFontConfigInfo}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroySystemFontConfigInfo(OH_Drawing_FontConfigInfo* drawFontCfgInfo);

/**
 * @brief Sets the strut style for a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param strutstyle Pointer to the {@link OH_Drawing_StrutStyle} object, which is obtained from
 *     {@link OH_Drawing_TypographyStyleGetStrutStyle}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyStyleTextStrutStyle(OH_Drawing_TypographyStyle* style, OH_Drawing_StrutStyle* strutstyle);

/**
 * @brief Reclaims the memory occupied by a strut style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param strutstyle Pointer to the {@link OH_Drawing_StrutStyle} object, which is obtained from
 *     {@link OH_Drawing_TypographyStyleGetStrutStyle}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyStyleDestroyStrutStyle(OH_Drawing_StrutStyle* strutstyle);

/**
 * @brief Obtains the strut style of a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Pointer to the {@link OH_Drawing_StrutStyle} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_StrutStyle* OH_Drawing_TypographyStyleGetStrutStyle(OH_Drawing_TypographyStyle* style);

/**
 * @brief Checks whether two strut styles are equal.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param from Pointer to the first strut style.
 * @param to Pointer to the second strut style.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyStyleStrutStyleEquals(OH_Drawing_StrutStyle* from, OH_Drawing_StrutStyle* to);

/**
 * @brief Sets whether to enable font hinting for a typography style. Font hinting is used to improve the readability
 * and appearance of small-sized text when rendering it.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param hintsEnabled Whether to enable font hinting. **true**: enabled; **false**: disabled.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyStyleSetHintsEnabled(OH_Drawing_TypographyStyle* style, bool hintsEnabled);

/**
 * @brief Obtains all font metrics from a given line in a typography object. This function must be called after
 * {@link OH_Drawing_TypographyLayout} is called. Otherwise, a null pointer is returned. Release this pointer by
 * calling {@link OH_Drawing_TypographyDestroyLineFontMetrics} when this object is no longer needed.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param lineNumber Line number, which is an integer. The minimum value is 1, and the maximum value depends on the
 *     number of lines parsed by the font engine after text input. If a value greater than the maximum number is passed
 *     in, an error value is returned and an error message is printed.
 * @param fontMetricsSize Pointer to the size of the struct.
 * @return Returns all the font metrics.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Font_Metrics* OH_Drawing_TypographyGetLineFontMetrics(OH_Drawing_Typography* typography,
    size_t lineNumber, size_t* fontMetricsSize);

/**
 * @brief Reclaims the memory occupied by the struct array that holds all the font metrics of a given line.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lineFontMetric Pointer to the first address of the struct array.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyDestroyLineFontMetrics(OH_Drawing_Font_Metrics* lineFontMetric);

/**
 * @brief Marks a typography object as dirty data. This function is used to initialize the typography state.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyMarkDirty(OH_Drawing_Typography* typography);

/**
 * @brief Obtains the number of unresolved glyphs in a typography object. This function can be called only after
 * {@link OH_Drawing_TypographyLayout} is called and applied.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @return Number of unresolved glyphs.
 * @since 12
 * @version 1.0
 */
int32_t OH_Drawing_TypographyGetUnresolvedGlyphsCount(OH_Drawing_Typography* typography);

/**
 * @brief Updates the font size in a typography object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param from Reserved field, which is not used.
 * @param to Reserved field, which is not used.
 * @param fontSize New font size.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyUpdateFontSize(OH_Drawing_Typography* typography, size_t from, size_t to, float fontSize);

/**
 * @brief Updates the font color in a typography object. This API call also updates the decoration color if it hasn't
 * been set yet. The updated font color takes effect after you call {@link OH_Drawing_TypographyPaint} to draw the text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param color New font color.
 * @since 20
 * @version 1.0
 */
void OH_Drawing_TypographyUpdateFontColor(OH_Drawing_Typography* typography, uint32_t color);

/**
 * @brief Updates the decoration type of a typography object. The updated decoration type takes effect after you call
 * {@link OH_Drawing_TypographyPaint} to draw the text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param decoration Updated decoration type. For details, see {@link OH_Drawing_TextDecoration}. You can set multiple
 *     text decoration types at a time via bitwise OR operations. If a decoration type that is not in the
 *     {@link OH_Drawing_TextDecoration} enumeration is set, the original decoration is retained.
 * @since 20
 * @version 1.0
 */
void OH_Drawing_TypographyUpdateDecoration(OH_Drawing_Typography* typography, OH_Drawing_TextDecoration decoration);

/**
 * @brief Updates the decoration thickness scale of a typography object. The updated decoration thickness scale takes
 * effect after you call {@link OH_Drawing_TypographyPaint} to draw the text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param decorationThicknessScale Thickness scaling ratio of the updated text decoration line. The thickness of the
 *     decoration line increases as the ratio increases. If the value is less than or equal to 0, the decoration line
 *     will not be drawn.
 * @since 20
 * @version 1.0
 */
void OH_Drawing_TypographyUpdateDecorationThicknessScale(OH_Drawing_Typography* typography,
    double decorationThicknessScale);

/**
 * @brief Updates the decoration style of a typography object. The updated decoration style takes effect after you call
 * {@link OH_Drawing_TypographyPaint} to draw the text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param decorationStyle Updated text decoration style. For details about the available options, see
 *     {@link OH_Drawing_TextDecorationStyle}.
 * @since 20
 * @version 1.0
 */
void OH_Drawing_TypographyUpdateDecorationStyle(OH_Drawing_Typography* typography,
    OH_Drawing_TextDecorationStyle decorationStyle);

/**
 * @brief Updates the decoration color of a typography object.
 * <br> The updated decoration color takes effect after you call {@link OH_Drawing_TypographyPaint} to draw the text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography Pointer to the {@link OH_Drawing_Typography} object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param color Updated text decoration color.
 * @since 20
 * @version 1.0
 */
void OH_Drawing_TypographyUpdateDecorationColor(OH_Drawing_Typography* typography, uint32_t color);

/**
 * @brief Checks whether the text line style is enabled for a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Whether the line style is enabled. **true**: enabled; **false**: disabled.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyTextGetLineStyle(OH_Drawing_TypographyStyle* style);

/**
 * @brief Obtains the font weight of a text line style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Font weight.
 *     <br> For details about the available options, see {@link OH_Drawing_FontWeight}.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontWeight OH_Drawing_TypographyTextlineStyleGetFontWeight(OH_Drawing_TypographyStyle* style);

/**
 * @brief Obtains the font style of the strut style in a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Font style of the strut style in a typography style. **1** indicates italic, and **0** or others indicate
 *     non-italic. For details, see the {@link OH_Drawing_FontStyle} enumeration.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyle OH_Drawing_TypographyTextlineStyleGetFontStyle(OH_Drawing_TypographyStyle* style);

/**
 * @brief Obtains the font families of a text line style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param num Pointer to the number of font families.
 * @return Font families.
 * @since 12
 * @version 1.0
 */
char** OH_Drawing_TypographyTextlineStyleGetFontFamilies(OH_Drawing_TypographyStyle* style, size_t* num);

/**
 * @brief Reclaims the memory occupied by the font families.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontFamilies Double pointer to the font families.
 * @param fontFamiliesNum Number of font families.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyTextlineStyleDestroyFontFamilies(char** fontFamilies, size_t fontFamiliesNum);

/**
 * @brief Obtains the font size of a text line style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Font size.
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TypographyTextlineStyleGetFontSize(OH_Drawing_TypographyStyle* style);

/**
 * @brief Obtains the height scale factor of a text line style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Height scale factor.
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TypographyTextlineStyleGetHeightScale(OH_Drawing_TypographyStyle* style);

/**
 * @brief Checks whether only the font height is used for a text line style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Method for calculating the height of a font block. **true** means that the height is calculated based on the
 *     font size; **false** means that the height is calculated based on the line spacing.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyTextlineStyleGetHeightOnly(OH_Drawing_TypographyStyle* style);

/**
 * @brief Checks whether half leading is enabled for a text line style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return **true** if half leading is enabled; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyTextlineStyleGetHalfLeading(OH_Drawing_TypographyStyle* style);

/**
 * @brief Obtains the spacing scale factor of a text line style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Spacing scale factor.
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TypographyTextlineStyleGetSpacingScale(OH_Drawing_TypographyStyle* style);

/**
 * @brief Checks whether only the text line style is enabled for a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Whether only the text line style is enabled for a typography style. **true**: enabled; **false**: disabled.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyTextlineGetStyleOnly(OH_Drawing_TypographyStyle* style);

/**
 * @brief Obtains the text alignment mode.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Alignment mode. For details about the available options, see {@link OH_Drawing_TextAlign}.
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextAlign OH_Drawing_TypographyGetTextAlign(OH_Drawing_TypographyStyle* style);

/**
 * @brief Obtains the text direction of a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Text direction. **0** means right-to-left; **1** means left-to-right. For details, see
 *     {@link OH_Drawing_TextDirection}.
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextDirection OH_Drawing_TypographyGetTextDirection(OH_Drawing_TypographyStyle* style);

/**
 * @brief Obtains the maximum number of lines.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Maximum number of lines.
 * @since 12
 * @version 1.0
 */
size_t OH_Drawing_TypographyGetTextMaxLines(OH_Drawing_TypographyStyle* style);

/**
 * @brief Obtains the text ellipsis content of a typography style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @return Ellipsis text.
 * @since 12
 * @version 1.0
 */
char* OH_Drawing_TypographyGetTextEllipsis(OH_Drawing_TypographyStyle* style);

/**
 * @brief Reclaims the memory occupied by the text ellipsis names.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param ellipsis Pointer to the text ellipsis names.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyDestroyEllipsis(char* ellipsis);

/**
 * @brief Checks whether two typography styles are the same. The text height modifier mode
 * {@link OH_Drawing_TextHeightBehavior} is not involved in the comparison.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param from Pointer to the first typography style.
 * @param to Pointer to the second typography style.
 * @return Returns **true** if the two are the same; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyStyleEquals(OH_Drawing_TypographyStyle* from, OH_Drawing_TypographyStyle* to);

/**
 * @brief Releases the memory occupied by a text box.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textBox Pointer to the {@link OH_Drawing_TextBox} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyDestroyTextBox(OH_Drawing_TextBox* textBox);

/**
 * @brief Sets a text shadow.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param shadow Pointer to the {@link OH_Drawing_TextShadow} object, which is obtained from
 *     {@link OH_Drawing_CreateTextShadow}.
 * @param color Color of the text shadow. For example, if the input parameter is 0xAABBCCDD, AA indicates opacity, BB
 *     indicates the value of the red component, CC indicates the value of the green component, and DD indicates the
 *     value of the blue component.
 * @param offset Pointer to the {@link OH_Drawing_Point} object, which is the offset of the text shadow relative to the
 *     text.
 * @param blurRadius Blur radius. The value is a floating point number and has no unit. The value **0.0** means that
 *     there is no blur effect.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTextShadow(OH_Drawing_TextShadow* shadow, uint32_t color, OH_Drawing_Point* offset,
    double blurRadius);

/**
 * @brief Creates a text tab object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param alignment Alignment mode of the text following the tab character. The value **1** means right alignment, **2**
 *     means center alignment, and **0** or other values mean left alignment.
 * @param location Alignment position of the text following the tab character. The unit is px. The minimum value is **1.
 *     0**.
 * @return Pointer to the **OH_Drawing_TextTab** object created. If a null pointer is returned, the creation fails. A
 *     possible cause is that no memory is available.
 * @since 18
 * @version 1.0
 */
OH_Drawing_TextTab* OH_Drawing_CreateTextTab(OH_Drawing_TextAlign alignment, float location);

/**
 * @brief Releases the memory occupied by a text tab object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param tab Pointer to an **OH_Drawing_TextTab** object.
 * @since 18
 * @version 1.0
 */
void OH_Drawing_DestroyTextTab(OH_Drawing_TextTab* tab);

/**
 * @brief Obtains the alignment mode of a text tab.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param tab Pointer to an **OH_Drawing_TextTab** object.
 * @return Alignment mode. The value **1** means right alignment, **2** means center alignment, and **0** or other
 *     values mean left alignment.
 * @since 18
 * @version 1.0
 */
OH_Drawing_TextAlign OH_Drawing_GetTextTabAlignment(OH_Drawing_TextTab* tab);

/**
 * @brief Obtains the location of a text tab.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param tab Pointer to an **OH_Drawing_TextTab** object.
 * @return Position of the text tab.
 * @since 18
 * @version 1.0
 */
float OH_Drawing_GetTextTabLocation(OH_Drawing_TextTab* tab);

/**
 * @brief Sets the alignment mode and location of a text tab. When the text alignment mode or ellipsis style is set,
 * the tab does not take effect. When the tab location is less than 1.0, the tab is replaced with a space.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object.
 * @param tab Pointer to an **OH_Drawing_TextTab** object.
 * @since 18
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextTab(OH_Drawing_TypographyStyle* style, OH_Drawing_TextTab* tab);

/**
 * @brief Obtains the number of objects in the input object array {@link OH_Drawing_Array}.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingArray Pointer to the {@link OH_Drawing_Array} object array.
 * @return Number of objects in the array.
 * @since 14
 * @version 1.0
 */
size_t OH_Drawing_GetDrawingArraySize(OH_Drawing_Array* drawingArray);

/**
 * @brief Sets whether to include the trailing spaces in alignment calculations during text typography.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Indicates the pointer to an <b>OH_Drawing_TypographyStyle</b> object.
 * @param trailingSpaceOptimized Boolean value indicating whether to optimize whitespace at the end of each line
 *     for text typography to set.
 * @since 20
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextTrailingSpaceOptimized(OH_Drawing_TypographyStyle* style, bool trailingSpaceOptimized);

/**
 * @brief Adds text encoded in a specified format.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler Pointer to the {@link OH_Drawing_TypographyCreate} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyHandler}.
 * @param text Pointer to the text content.
 * @param byteLength Length of the text, in bytes.
 * @param textEncodingType Text encoding type, which is an enumerated value of {@link OH_Drawing_TextEncoding}. Only **
 *     TEXT_ENCODING_UTF8**, **TEXT_ENCODING_UTF16**, and **TEXT_ENCODING_UTF32** are supported.
 * @since 20
 * @version 1.0
 */
void OH_Drawing_TypographyHandlerAddEncodedText(OH_Drawing_TypographyCreate* handler, const void* text,
    size_t byteLength, OH_Drawing_TextEncoding textEncodingType);

/**
 * @brief Sets whether to enable automatic spacing during text typography.
 * <br>This feature is disabled by default. If enabled, automatic spacing applies between CJK (Chinese, Japanese, and
 * Korean) and Western characters (Latin, Cyrillic, and Greek), between CJK and digits, between CJK and copyright
 * symbols, between copyright symbols and digits, and between copyright symbols and Western characters.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyStyle}.
 * @param enableAutoSpace Sets whether to enable automatic spacing during text typography. **true** means enabled; **
 *     false** (default) means disabled.
 * @since 20
 */
void OH_Drawing_SetTypographyTextAutoSpace(OH_Drawing_TypographyStyle* style, bool enableAutoSpace);

/**
 * @brief Creates a copy of an existing paragraph style object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TypographyStyle} object to be copied.
 * @return Pointer to the copied {@link OH_Drawing_TypographyStyle} object. If a null pointer is returned, the creation
 *     fails. The possible cause is that no memory is available or **style** is a null pointer. Release this pointer by
 *     calling {@link OH_Drawing_DestroyTypographyStyle} when this object is no longer needed.
 * @since 20
 * @version 1.0
 */
OH_Drawing_TypographyStyle* OH_Drawing_CopyTypographyStyle(OH_Drawing_TypographyStyle* style);

/**
 * @brief Creates a copy of an existing text style object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style Pointer to the {@link OH_Drawing_TextStyle} object to be copied.
 * @return Pointer to the copied {@link OH_Drawing_TextStyle} object. If a null pointer is returned, the creation fails.
 *      The possible cause is that no memory is available or **style** is a null pointer. Release this pointer by
 *     calling {@link OH_Drawing_DestroyTextStyle} when this object is no longer needed.
 * @since 20
 * @version 1.0
 */
OH_Drawing_TextStyle* OH_Drawing_CopyTextStyle(OH_Drawing_TextStyle* style);

/**
 * @brief Creates a copy of an existing text shadow object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param shadow Pointer to the {@link OH_Drawing_TextShadow} object to be copied.
 * @return Pointer to the copied {@link OH_Drawing_TextShadow} object. If a null pointer is returned, the creation
 *     fails. The possible cause is that no memory is available or **shadow** is a null pointer. Release this pointer
 *     by calling {@link OH_Drawing_DestroyTextShadow} when this object is no longer needed.
 * @since 20
 * @version 1.0
 */
OH_Drawing_TextShadow* OH_Drawing_CopyTextShadow(OH_Drawing_TextShadow* shadow);

/**
 * @brief Destroys an {@link OH_Drawing_PositionAndAffinity} object and reclaims the memory occupied by the object.
 *
 * @param positionAndAffinity Pointer to the {@link OH_Drawing_PositionAndAffinity} object.
 * @since 23
 */
void OH_Drawing_DestroyPositionAndAffinity(OH_Drawing_PositionAndAffinity* positionAndAffinity);

/**
 * @brief Obtains the character range corresponding to the specified glyph range.
 *
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param glyphRangeStart Start position of the glyph range.
 * @param glyphRangeEnd End position of the glyph range.
 * @param actualGlyphRange Returns the actual font range, indicating the level-2 pointer to {@link OH_Drawing_Range}.
 *     It is used as an output parameter.
 *     <br>When the requested glyph range contains only a part of a complex glyph sequence, this parameter returns the
 *     corresponding complete glyph range.
 *     <br>For example, ligatures and combined emojis may consist of multiple atomic glyphs and must be processed as a
 *     whole.
 *     <br>If this parameter is NULL, the actual glyph range is not returned, indicating that the caller does not care
 *     about the actual glyph range information.
 *     <br>After use, release the object through the {@link OH_Drawing_ReleaseRangeBuffer} API.
 * @param textEncodingType Text encoding type {@link OH_Drawing_TextEncoding}.
 *     <br>Currently, only UTF-8 and UTF-16 encoding types are supported.
 *     <br>For UTF-8 encoding, the returned character range indicates the byte range.
 *     <br>For UTF-16 encoding, the returned character range indicates the UTF-16 code unit range.
 * @return Returns the {@link OH_Drawing_Range} object pointer that indicates the character range. When the object is
 *     no longer needed, use the {@link OH_Drawing_ReleaseRangeBuffer} API to release it.
 * @since 24
 */
OH_Drawing_Range* OH_Drawing_TypographyGetCharacterRangeForGlyphRangeWithBuffer(OH_Drawing_Typography* typography,
    size_t glyphRangeStart, size_t glyphRangeEnd, OH_Drawing_Range** actualGlyphRange,
    OH_Drawing_TextEncoding textEncodingType);

/**
 * @brief Obtains the character position information closest to the specified coordinates.
 *
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param dx Horizontal coordinate in the text layout area, in physical pixels (px).
 *     <br>X offset relative to the top-left corner of the text layout area, with the right direction as positive.
 *     <br>Supports floating-point values and accepts negative values, which indicate positions to the left of the text
 *     layout area.
 *     <br>If the coordinates are beyond the text layout area, the nearest character position is returned. It can be
 *     obtained through a touch event or click event.
 * @param dy Vertical coordinate in the text layout area, in physical pixels (px).
 *     <br>Y offset relative to the top-left corner of the text layout area, with the downward direction as positive.
 *     <br>Supports floating-point values and accepts negative values, which indicate positions above the text layout
 *     area.
 *     <br>If the coordinates are beyond the text layout area, the nearest character position is returned. It can be
 *     obtained through a touch event or click event.
 * @param textEncodingType Text encoding type {@link OH_Drawing_TextEncoding}.
 *     <br>Currently, only UTF-8 and UTF-16 encoding types are supported.
 *     <br>For UTF-8 encoding, the returned position indicates the byte offset. For UTF-16 encoding, the returned
 *     position indicates the UTF-16 code unit offset.
 * @return Returns the character index position and affinity at the coordinate. The return type is the
 *     {@link OH_Drawing_PositionAndAffinity} structure.
 *     <br>When the object is no longer needed, call {@link OH_Drawing_DestroyPositionAndAffinity} to release it.
 * @since 24
 */
OH_Drawing_PositionAndAffinity* OH_Drawing_TypographyGetCharacterPositionAtCoordinateWithBuffer(
    OH_Drawing_Typography* typography, double dx, double dy, OH_Drawing_TextEncoding textEncodingType);

/**
 * @brief Obtains the glyph range corresponding to the specified character range.
 *
 * @param typography Pointer to the **OH_Drawing_Typography** object, which is obtained from
 *     {@link OH_Drawing_CreateTypography}.
 * @param characterRangeStart Start position of the character range.
 * @param characterRangeEnd End position of the character range.
 * @param actualCharacterRange Returns the actual character range, indicating the level-2 pointer to
 *     {@link OH_Drawing_Range}. It is used as an output parameter.
 *     <br>When the requested character range contains only a part of the combined character sequence, this parameter
 *     returns the corresponding complete character range.
 *     <br>For example, a combined character consisting of a base character and a diacritical mark must be processed as
 *     a whole.
 *     <br>If this parameter is NULL, the actual character range is not returned, indicating that the caller does not
 *     care about the actual character range information.
 *     <br>After use, release the object through the {@link OH_Drawing_ReleaseRangeBuffer} API.
 * @param textEncodingType Text encoding type {@link OH_Drawing_TextEncoding}.
 *     <br>Currently, only UTF-8 and UTF-16 encoding types are supported.
 *     <br>For UTF-8 encoding, the input character range should be interpreted as a byte range. For UTF-16 encoding,
 *     the input character range should be interpreted as a UTF-16 code unit range.
 * @return Returns the {@link OH_Drawing_Range} object pointer that indicates the font range. If the object is no
 *     longer needed, use the {@link OH_Drawing_ReleaseRangeBuffer} API to release it.
 * @since 24
 */
OH_Drawing_Range* OH_Drawing_TypographyGetGlyphRangeForCharacterRangeWithBuffer(OH_Drawing_Typography* typography,
    size_t characterRangeStart, size_t characterRangeEnd, OH_Drawing_Range** actualCharacterRange,
    OH_Drawing_TextEncoding textEncodingType);

/**
 * @brief Releases the memory occupied by the {@link OH_Drawing_Range} object.
 *
 * @param range Pointer to the {@link OH_Drawing_Range} object.
 * @since 24
 */
void OH_Drawing_ReleaseRangeBuffer(OH_Drawing_Range* range);
#ifdef __cplusplus
}
#endif
/** @} */
#endif
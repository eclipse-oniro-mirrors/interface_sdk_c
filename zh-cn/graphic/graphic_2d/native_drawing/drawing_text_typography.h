
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
 * @brief 文字方向。
 *
 * @since 8
 * @version 1.0
 */
typedef enum OH_Drawing_TextDirection {
    /**
     * 方向：从右到左。
     */
    TEXT_DIRECTION_RTL,

    /**
     * 方向：从左到右。
     */
    TEXT_DIRECTION_LTR
} OH_Drawing_TextDirection;

/**
 * @brief 文字对齐方式。
 *
 * @since 8
 * @version 1.0
 */
typedef enum OH_Drawing_TextAlign {
    /**
     * 左对齐。
     */
    TEXT_ALIGN_LEFT,

    /**
     * 右对齐。
     */
    TEXT_ALIGN_RIGHT,

    /**
     * 居中对齐。
     */
    TEXT_ALIGN_CENTER,

    /**
     * 两端对齐，即紧靠左和右边缘，中间单词空隙由空格填充，最后一行除外。
     */
    TEXT_ALIGN_JUSTIFY,

    /**
     * 当OH_Drawing_TextDirection是TEXT_DIRECTION_LTR时，TEXT_ALIGN_START和TEXT_ALIGN_LEFT相同；<br>类似地，
     * 当OH_Drawing_TextDirection是TEXT_DIRECTION_RTL时，TEXT_ALIGN_START和TEXT_ALIGN_RIGHT相同。
     */
    TEXT_ALIGN_START,

    /**
     * 当OH_Drawing_TextDirection是TEXT_DIRECTION_LTR时，TEXT_ALIGN_END和TEXT_ALIGN_RIGHT相同；<br>类似地，
     * 当OH_Drawing_TextDirection是TEXT_DIRECTION_RTL时，TEXT_ALIGN_END和TEXT_ALIGN_LEFT相同。
     */
    TEXT_ALIGN_END
} OH_Drawing_TextAlign;

/**
 * @brief 字重。
 *
 * @since 8
 * @version 1.0
 */
typedef enum OH_Drawing_FontWeight {
    /**
     * 字重为thin。
     */
    FONT_WEIGHT_100,

    /**
     * 字重为extra-light。
     */
    FONT_WEIGHT_200,

    /**
     * 字重为light。
     */
    FONT_WEIGHT_300,

    /**
     * 字重为normal/regular。
     */
    FONT_WEIGHT_400,

    /**
     * 字重为medium。
     */
    FONT_WEIGHT_500,

    /**
     * 字重为semi-bold。
     */
    FONT_WEIGHT_600,

    /**
     * 字重为bold。
     */
    FONT_WEIGHT_700,

    /**
     * 字重为extra-bold。
     */
    FONT_WEIGHT_800,

    /**
     * 字重为black。
     */
    FONT_WEIGHT_900
} OH_Drawing_FontWeight;

/**
 * @brief 基线位置。
 *
 * @since 8
 * @version 1.0
 */
typedef enum OH_Drawing_TextBaseline {
    /**
     * 用于表音文字，基线在中间偏下的位置。
     */
    TEXT_BASELINE_ALPHABETIC,

    /**
     * 用于表意文字，基线位于底部。
     */
    TEXT_BASELINE_IDEOGRAPHIC
} OH_Drawing_TextBaseline;

/**
 * @brief 文本装饰。
 *
 * @since 8
 * @version 1.0
 */
typedef enum OH_Drawing_TextDecoration {
    /**
     * 无装饰。
     */
    TEXT_DECORATION_NONE = 0x0,

    /**
     * 下划线。
     */
    TEXT_DECORATION_UNDERLINE = 0x1,

    /**
     * 上划线。
     */
    TEXT_DECORATION_OVERLINE = 0x2,

    /**
     * 删除线。
     */
    TEXT_DECORATION_LINE_THROUGH = 0x4
} OH_Drawing_TextDecoration;

/**
 * @brief 区分字体是否为斜体。
 *
 * @since 8
 * @version 1.0
 */
typedef enum OH_Drawing_FontStyle {
    /**
     * 非斜体。
     */
    FONT_STYLE_NORMAL,

    /**
     * 斜体。
     */
    FONT_STYLE_ITALIC,

    /**
     * 倾斜字体。
     */
    FONT_STYLE_OBLIQUE
} OH_Drawing_FontStyle;

/**
 * @brief 占位符垂直对齐枚举。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 偏移于基线对齐。
     */
    ALIGNMENT_OFFSET_AT_BASELINE,

    /**
     * 高于基线对齐。
     */
    ALIGNMENT_ABOVE_BASELINE,

    /**
     * 低于基线对齐。
     */
    ALIGNMENT_BELOW_BASELINE,

    /**
     * 行框顶部对齐。
     */
    ALIGNMENT_TOP_OF_ROW_BOX,

    /**
     * 行框底部对齐。
     */
    ALIGNMENT_BOTTOM_OF_ROW_BOX,

    /**
     * 行框中心对齐。
     */
    ALIGNMENT_CENTER_OF_ROW_BOX,

    /**
     * 跟随文本垂直对齐方式。
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
 * @brief 文本装饰样式枚举。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 实心样式。
     */
    TEXT_DECORATION_STYLE_SOLID,

    /**
     * 双重样式。
     */
    TEXT_DECORATION_STYLE_DOUBLE,

    /**
     * 圆点样式。
     */
    TEXT_DECORATION_STYLE_DOTTED,

    /**
     * 虚线样式。
     */
    TEXT_DECORATION_STYLE_DASHED,

    /**
     * 波浪样式。
     */
    TEXT_DECORATION_STYLE_WAVY
} OH_Drawing_TextDecorationStyle;

/**
 * @brief 省略号样式枚举。
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
     * 头部省略号模式，即省略号位置出现在行首。该枚举值在使用{@link OH_Drawing_SetTypographyTextMaxLines}接口设置文本最大行数为任何值时均有效。
     * @since 24
     */
    ELLIPSIS_MODAL_MULTILINE_HEAD = 3,

    /**
     * 中间省略号模式，即省略号位置出现在行的中间。该枚举值在使用{@link OH_Drawing_SetTypographyTextMaxLines}接口设置文本最大行数为任何值时均有效。
     * @since 24
     */
    ELLIPSIS_MODAL_MULTILINE_MIDDLE = 4
} OH_Drawing_EllipsisModal;

/**
 * @brief 文本的中断策略枚举。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 贪心策略，换行时尽可能填满每一行。
     */
    BREAK_STRATEGY_GREEDY = 0,

    /**
     * 高质量策略，换行时优先考虑文本的连续性。
     */
    BREAK_STRATEGY_HIGH_QUALITY = 1,

    /**
     * 平衡策略，换行时在单词边界换行。
     */
    BREAK_STRATEGY_BALANCED = 2
} OH_Drawing_BreakStrategy;

/**
 * @brief 单词的断词方式枚举。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 常规方式。
     */
    WORD_BREAK_TYPE_NORMAL = 0,

    /**
     * 全部中断方式。
     */
    WORD_BREAK_TYPE_BREAK_ALL = 1,

    /**
     * 单词中断方式。
     */
    WORD_BREAK_TYPE_BREAK_WORD = 2,

    /**
     * 每行末尾单词尝试通过连字符“-”进行断行，若无法添加连字符“-”，则跟`WORD_BREAK_TYPE_BREAK_WORD`保持一致。
     * @since 18
     */
    WORD_BREAK_TYPE_BREAK_HYPHEN = 3
} OH_Drawing_WordBreakType;

/**
 * @brief 矩形框高度样式枚举。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 紧密样式。
     */
    RECT_HEIGHT_STYLE_TIGHT,

    /**
     * 最大样式。
     */
    RECT_HEIGHT_STYLE_MAX,

    /**
     * 包含行间距中间样式。
     */
    RECT_HEIGHT_STYLE_INCLUDELINESPACEMIDDLE,

    /**
     * 包含行间距顶部样式。
     */
    RECT_HEIGHT_STYLE_INCLUDELINESPACETOP,

    /**
     * 包含行间距底部样式。
     */
    RECT_HEIGHT_STYLE_INCLUDELINESPACEBOTTOM,

    /**
     * 结构样式。
     */
    RECT_HEIGHT_STYLE_STRUCT
} OH_Drawing_RectHeightStyle;

/**
 * @brief 矩形框宽度样式枚举。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 紧密样式。
     */
    RECT_WIDTH_STYLE_TIGHT,

    /**
     * 最大样式。
     */
    RECT_WIDTH_STYLE_MAX
} OH_Drawing_RectWidthStyle;

/**
 * @brief 获取系统字体配置信息列表结果枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum OH_Drawing_FontConfigInfoErrorCode {
    /**
     * 获取系统字体配置信息列表成功。
     */
    SUCCESS_FONT_CONFIG_INFO = 0,

    /**
     * 未知错误。
     */
    ERROR_FONT_CONFIG_INFO_UNKNOWN = 1,

    /**
     * 解析系统配置文件失败。
     */
    ERROR_FONT_CONFIG_INFO_PARSE_FILE = 2,

    /**
     * 申请内存失败。
     */
    ERROR_FONT_CONFIG_INFO_ALLOC_MEMORY = 3,

    /**
     * 拷贝字符串数据失败。
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
 * @brief 文本高度修饰符模式枚举。
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
 * @brief 文本样式类型枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum OH_Drawing_TextStyleType {
    /**
     * 无文本样式。
     */
    TEXT_STYLE_NONE,

    /**
     * 所有文本样式。
     */
    TEXT_STYLE_ALL_ATTRIBUTES,

    /**
     * 字体样式。
     */
    TEXT_STYLE_FONT,

    /**
     * 文本前景样式。
     */
    TEXT_STYLE_FOREGROUND,

    /**
     * 文本背景样式。
     */
    TEXT_STYLE_BACKGROUND,

    /**
     * 文本阴影样式。
     */
    TEXT_STYLE_SHADOW,

    /**
     * 文本装饰样式。
     */
    TEXT_STYLE_DECORATIONS,

    /**
     * 文本字符间距样式。
     */
    TEXT_STYLE_LETTER_SPACING,

    /**
     * 文本单词间距样式。
     */
    TEXT_STYLE_WORD_SPACING
} OH_Drawing_TextStyleType;

/**
 * @brief 字体宽度的枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum OH_Drawing_FontWidth {
    /**
     * 表示超窄的字宽。
     */
    FONT_WIDTH_ULTRA_CONDENSED = 1,

    /**
     * 表示特窄的字宽。
     */
    FONT_WIDTH_EXTRA_CONDENSED = 2,

    /**
     * 表示窄的字宽。
     */
    FONT_WIDTH_CONDENSED = 3,

    /**
     * 表示半窄的字宽。
     */
    FONT_WIDTH_SEMI_CONDENSED = 4,

    /**
     * 表示常规的字宽。
     */
    FONT_WIDTH_NORMAL = 5,

    /**
     * 表示半宽的字宽。
     */
    FONT_WIDTH_SEMI_EXPANDED = 6,

    /**
     * 表示宽的字宽。
     */
    FONT_WIDTH_EXPANDED = 7,

    /**
     * 表示特宽的字宽。
     */
    FONT_WIDTH_EXTRA_EXPANDED = 8,

    /**
     * 表示超宽的字宽。
     */
    FONT_WIDTH_ULTRA_EXPANDED = 9
} OH_Drawing_FontWidth;

/**
 * @brief 文本样式属性枚举。
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
     * 字宽。
     */
    TEXT_STYLE_ATTR_I_FONT_WIDTH = 3,

    /**
     * 字体边缘处理方式。默认为抗锯齿，具体字体边缘处理方式可见{@link OH_Drawing_FontEdging}。
     * @since 24
     */
    TEXT_STYLE_ATTR_I_FONT_EDGING = 4
} OH_Drawing_TextStyleAttributeId;

/**
 * @brief 行高缩放基数样式枚举。默认样式为TEXT_LINE_HEIGHT_BY_FONT_SIZE。
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
 * @brief 排版样式属性枚举。
 * 针对排版样式和文本样式中的共有属性，建议优先使用文本样式属性（可由{@link OH_Drawing_TextStyleAttributeId}获取）。
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
     * 字宽。
     */
    TYPOGRAPHY_STYLE_ATTR_I_FONT_WIDTH = 4,

    /**
     * 设置文本排版时是否使能字体内部的padding。
     * @since 23
     */
    TYPOGRAPHY_STYLE_ATTR_B_INCLUDE_FONT_PADDING = 6,

    /**
     * 设置文本排版时是否使能行间距回退机制。
     * @since 23
     */
    TYPOGRAPHY_STYLE_ATTR_B_FALLBACK_LINE_SPACING = 7,

    /**
     * 省略号样式。具体省略号样式可见{@link OH_Drawing_EllipsisModal}。
     * @since 24
     */
    TYPOGRAPHY_STYLE_ATTR_I_ELLIPSIS_MODAL = 8,

    /**
     * 行首缩进数组。<br>缩进数组值需全部大于等于0，数组中每个元素代表一行缩进值，当实际文本行数超过缩进数组个数时，超过行的缩进为数组最后一个值。.0
     * @since 26.0.0
     */
    TYPOGRAPHY_STYLE_ATTR_DA_LINE_HEAD_INDENT = 9,

    /**
     * 段落首行缩进。缩进值需大于等于0。.0
     * @since 26.0.0
     */
    TYPOGRAPHY_STYLE_ATTR_D_FIRST_LINE_HEAD_INDENT = 10,

    /**
     * 行尾缩进数组。<br>缩进数组值需全部大于等于0，数组中每个元素代表一行缩进值，当实际文本行数超过缩进数组个数时，超过行的缩进为数组最后一个值。.0
     * @since 26.0.0
     */
    TYPOGRAPHY_STYLE_ATTR_DA_LINE_TAIL_INDENT = 11
} OH_Drawing_TypographyStyleAttributeId;

/**
 * @brief 设置double类型文本样式的属性。
 *
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针。
 * @param id 文本样式属性id。
 * @param value 文本样式属性值。
 * @return 函数执行结果。
 *     返回OH_DRAWING_SUCCESS，表示执行成功。
 *     返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数style为空指针。
 *     返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_SetTextStyleAttributeDouble(OH_Drawing_TextStyle* style,
    OH_Drawing_TextStyleAttributeId id, double value);

/**
 * @brief 获取double类型文本样式的属性。
 *
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针。
 * @param id 文本样式属性id。
 * @param value 指向double类型属性的指针。作为出参使用。
 * @return 函数执行结果。
 *     返回OH_DRAWING_SUCCESS，表示执行成功。
 *     返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数style为空指针。
 *     返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_GetTextStyleAttributeDouble(OH_Drawing_TextStyle* style,
    OH_Drawing_TextStyleAttributeId id, double* value);

/**
 * @brief 设置int类型文本样式的属性。
 *
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针。
 * @param id 文本样式属性id。
 * @param value 待设置属性值。
 * @return 函数执行结果。
 *     返回OH_DRAWING_SUCCESS，表示执行成功。
 *     返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数style为空指针。
 *     返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 *     返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE，表示传入的value超出待设置属性取值范围。
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_SetTextStyleAttributeInt(OH_Drawing_TextStyle* style,
    OH_Drawing_TextStyleAttributeId id, int value);

/**
 * @brief 获取int类型文本样式的属性。
 *
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针。
 * @param id 文本样式属性id。
 * @param value 指向int类型属性的指针。作为出参使用。
 * @return 函数执行结果。
 *     返回OH_DRAWING_SUCCESS，表示执行成功。
 *     返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数style为空指针。
 *     返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_GetTextStyleAttributeInt(OH_Drawing_TextStyle* style,
    OH_Drawing_TextStyleAttributeId id, int* value);

/**
 * @brief 设置double类型排版样式的属性。
 *
 * @param style 指向排版样式对象{@link OH_Drawing_TypographyStyle}的指针。
 * @param id 排版样式属性id。
 * @param value 待设置属性值。
 * @return 函数执行结果。
 *     返回OH_DRAWING_SUCCESS，表示执行成功。
 *     返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数style为空指针。
 *     返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_SetTypographyStyleAttributeDouble(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, double value);

/**
 * @brief 获取double类型排版样式的属性。
 *
 * @param style 指向排版样式对象{@link OH_Drawing_TypographyStyle}的指针。
 * @param id 排版样式属性id。
 * @param value 指向double类型属性的指针。作为出参使用。
 * @return 函数执行结果。
 *     返回OH_DRAWING_SUCCESS，表示执行成功。
 *     返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数style为空指针。
 *     返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_GetTypographyStyleAttributeDouble(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, double* value);

/**
 * @brief 设置int类型排版样式的属性。
 *
 * @param style 指向排版样式对象{@link OH_Drawing_TypographyStyle}的指针。
 * @param id 排版样式属性id。
 * @param value 待设置属性值。
 * @return 函数执行结果。
 *     返回OH_DRAWING_SUCCESS，表示执行成功。
 *     返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数style为空指针。
 *     返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 *     返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE，表示传入的value超出待设置属性取值范围。
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_SetTypographyStyleAttributeInt(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, int value);

/**
 * @brief 获取int类型排版样式的属性。
 *
 * @param style 指向排版样式对象{@link OH_Drawing_TypographyStyle}的指针。
 * @param id 排版样式属性id。
 * @param value 指向int类型属性的指针。作为出参使用。
 * @return 函数执行结果。
 *     返回OH_DRAWING_SUCCESS，表示执行成功。
 *     返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数style为空指针。
 *     返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 21
 */
OH_Drawing_ErrorCode OH_Drawing_GetTypographyStyleAttributeInt(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, int* value);

/**
 * @brief 设置bool类型排版样式的属性。
 *
 * @param style 指向排版样式对象{@link OH_Drawing_TypographyStyle}的指针。
 * @param id 排版样式属性id。
 * @param value 待设置属性值。
 * @return 函数执行结果。
 *     返回OH_DRAWING_SUCCESS，表示执行成功。
 *     返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数style为空指针。
 *     返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_SetTypographyStyleAttributeBool(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, bool value);

/**
 * @brief 获取bool类型排版样式的属性。
 *
 * @param style 指向排版样式对象{@link OH_Drawing_TypographyStyle}的指针。
 * @param id 排版样式属性id。
 * @param value 指向bool类型属性的指针。作为出参使用。
 * @return 函数执行结果。
 *     返回OH_DRAWING_SUCCESS，表示执行成功。
 *     返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数style或者value为空指针。
 *     返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_GetTypographyStyleAttributeBool(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, bool* value);

/**
 * @brief 设置浮点数数组类型排版样式的属性。
 *
 * @param style 指向排版样式对象{@link OH_Drawing_TypographyStyle}的指针。
 * @param id 排版样式属性id。
 * @param arrayValue 指向浮点数数组的指针。
 * @param arrayLength 指向浮点数数组的长度。
 * @return 函数执行结果。
 *     返回OH_DRAWING_SUCCESS，表示执行成功。
 *     返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数style或者arrayValue为空指针或arrayLength为0。
 *     返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_SetTypographyStyleAttributeDoubleArray(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, double* arrayValue, size_t arrayLength);

/**
 * @brief 获取浮点数数组类型排版样式的属性。
 *
 * @param style 指向排版样式对象{@link OH_Drawing_TypographyStyle}的指针。
 * @param id 排版样式属性id。
 * @param arrayValue 指向浮点数数组的指针。作为出参使用。
 * @param arrayLength 指向浮点数数组的长度。作为出参使用。
 * @return 函数执行结果。
 *     返回OH_DRAWING_SUCCESS，表示执行成功。
 *     返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数style或者arrayValue为空指针或arrayLength为空指针。
 *     返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_GetTypographyStyleAttributeDoubleArray(const OH_Drawing_TypographyStyle* style,
    OH_Drawing_TypographyStyleAttributeId id, double** arrayValue, size_t* arrayLength);

/**
 * @brief 上下标样式枚举。
 *
 * @since 20
 * @version 1.0
 */
typedef enum OH_Drawing_TextBadgeType {
    /**
     * 不使能上标或下标。
     */
    TEXT_BADGE_NONE,

    /**
     * 使能上标。
     */
    TEXT_SUPERSCRIPT,

    /**
     * 使能下标。
     */
    TEXT_SUBSCRIPT
} OH_Drawing_TextBadgeType;

/**
 * @brief 垂直对齐方式枚举。
 *
 * @since 20
 * @version 1.0
 */
typedef enum OH_Drawing_TextVerticalAlignment {
    /**
     * 偏移于基线对齐。
     */
    TEXT_VERTICAL_ALIGNMENT_BASELINE,

    /**
     * 底部对齐。
     */
    TEXT_VERTICAL_ALIGNMENT_BOTTOM,

    /**
     * 居中对齐。
     */
    TEXT_VERTICAL_ALIGNMENT_CENTER,

    /**
     * 顶部对齐。
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
     * 字宽。
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
 * @brief 文本框结构体
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
 * @brief 创建指向OH_Drawing_TypographyStyle对象的指针。不再需要{@link OH_Drawing_TypographyStyle}时，请使用
 * {@link OH_Drawing_DestroyTypographyStyle}接口释放该对象的指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return 指向创建的{@link OH_Drawing_TypographyStyle}对象的指针。
 * @since 8
 * @version 1.0
 */
OH_Drawing_TypographyStyle* OH_Drawing_CreateTypographyStyle(void);

/**
 * @brief 释放被OH_Drawing_TypographyStyle对象占据的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_DestroyTypographyStyle(OH_Drawing_TypographyStyle* style);

/**
 * @brief 设置指定排版样式中的文本方向。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param direction 设置文本方向，设置0为从右到左，设置1或其他值为从左到右，具体可见{@link OH_Drawing_TextDirection}枚举。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextDirection(OH_Drawing_TypographyStyle* style, int direction);

/**
 * @brief 设置文本对齐方式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param align 设置文本对齐方式，设置1为右对齐，设置2为居中对齐，设置3为两端对齐，设置4为与文字方向相同，设置5为文字方向相反，设置0或其它为左对齐，具体可见{@link OH_Drawing_TextAlign}枚举。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextAlign(OH_Drawing_TypographyStyle* style, int align);

/**
 * @brief 设置文本最大行数。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param lineNumber 最大行数。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextMaxLines(OH_Drawing_TypographyStyle* style, int lineNumber);

/**
 * @brief 创建指向OH_Drawing_TextStyle对象的指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return 指向创建的{@link OH_Drawing_TextStyle}对象的指针。
 * @since 8
 * @version 1.0
 */
OH_Drawing_TextStyle* OH_Drawing_CreateTextStyle(void);

/**
 * @brief 释放被OH_Drawing_TextStyle对象占据的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_DestroyTextStyle(OH_Drawing_TextStyle* style);

/**
 * @brief 设置文本颜色。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向{@link OH_Drawing_TextStyle}对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param color 颜色。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleColor(OH_Drawing_TextStyle* style, uint32_t color);

/**
 * @brief 设置字号。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向{@link OH_Drawing_TextStyle}对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param fontSize 字号。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleFontSize(OH_Drawing_TextStyle* style, double fontSize);

/**
 * @brief 设置字重。目前只有系统默认字体支持字重的调节，其他字体设置字重值小于semi-bold时字体粗细无变化，当设置字重值大于等于semi-bold时可能会触发伪加粗效果。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param fontWeight 设置字重，设置0字重为thin，设置1字重为extra-light，设置2字重为light，设置4字重为medium，设置5字重为semi-bold，
 *     设置6字重为bold，设置7字重为extra-bold，设置8字重为black，设置3或其它字重为normal/regular，具体可见{@link OH_Drawing_FontWeight}枚举。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleFontWeight(OH_Drawing_TextStyle* style, int fontWeight);

/**
 * @brief 设置文本样式的字体基线位置。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param baseline 设置字体基线位置，设置1基线位于底部，设置0或其它基线在中间偏下的位置，具体可见{@link OH_Drawing_TextBaseline}枚举。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleBaseLine(OH_Drawing_TextStyle* style, int baseline);

/**
 * @brief 设置指定文本样式中的装饰线类型，只能设置一个装饰线类型，添加多个需要使用{@link OH_Drawing_AddTextStyleDecoration}。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param decoration 设置装饰，设置1为下划线，设置2为上划线，设置4为删除线，设置0或其它为无装饰，具体可见{@link OH_Drawing_TextDecoration}枚举。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleDecoration(OH_Drawing_TextStyle* style, int decoration);

/**
 * @brief 新增指定装饰，可同时显示多种装饰线。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param decoration 要新增的装饰。设置1为新增下划线，设置2为新增上划线，设置4为新增删除线。可通过位或操作一次新增多种装饰线。
 *     设置非{@link OH_Drawing_TextDecoration}枚举的装饰样式则保持原有装饰。
 * @since 18
 * @version 1.0
 */
void OH_Drawing_AddTextStyleDecoration(OH_Drawing_TextStyle* style, int decoration);

/**
 * @brief 删除指定装饰。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param decoration 要删除的装饰。应该与现有的装饰相匹配，设置1为删除下划线，设置2为删除上划线，设置4为删除删除线，可通过位或操作一次删除多种装饰线。
 *     设置非{@link OH_Drawing_TextDecoration}枚举的装饰样式则保持原有装饰。
 * @since 18
 * @version 1.0
 */
void OH_Drawing_RemoveTextStyleDecoration(OH_Drawing_TextStyle* style, int decoration);

/**
 * @brief 设置指定文本样式中的装饰线颜色。如果不调用该接口或者设置color为0时，装饰线颜色跟随文本颜色。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param color 颜色。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleDecorationColor(OH_Drawing_TextStyle* style, uint32_t color);

/**
 * @brief 设置行高，按当前字体大小的倍数进行设置。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param fontHeight 当前字体大小的倍数。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleFontHeight(OH_Drawing_TextStyle* style, double fontHeight);

/**
 * @brief 设置指定文本样式的字体家族类型。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param fontFamiliesNumber 字体名称数量，禁止填入负数。
 * @param fontFamilies 指向字体家族类型的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleFontFamilies(OH_Drawing_TextStyle* style,
    int fontFamiliesNumber, const char* fontFamilies[]);

/**
 * @brief 为指定文本样式设置字体样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param fontStyle 设置字体样式，设置1为斜体，设置0或其它为非斜体，具体可见{@link OH_Drawing_FontStyle}枚举。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleFontStyle(OH_Drawing_TextStyle* style, int fontStyle);

/**
 * @brief 设置文本语言环境。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param locale 语言类型，数据类型为指向char的指针，如'en'代表英文，'zh-Hans'代表简体中文，'zh-Hant'代表繁体中文。未指定时默认locale为'zh-Hans'。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_SetTextStyleLocale(OH_Drawing_TextStyle* style, const char* locale);

/**
 * @brief 设置指定文本样式中的前景色画刷。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param foregroundBrush 指向画刷{@link OH_Drawing_Brush}对象的指针，由{@link OH_Drawing_BrushCreate}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTextStyleForegroundBrush(OH_Drawing_TextStyle* style, OH_Drawing_Brush* foregroundBrush);

/**
 * @brief 返回设置的前景色画刷。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param foregroundBrush 指向画刷{@link OH_Drawing_Brush}对象的指针，由{@link OH_Drawing_BrushCreate}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleGetForegroundBrush(OH_Drawing_TextStyle* style, OH_Drawing_Brush* foregroundBrush);

/**
 * @brief 设置指定文本样式中的前景色画笔。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param foregroundPen 指向画笔{@link OH_Drawing_Pen}对象的指针，由{@link OH_Drawing_PenCreate}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTextStyleForegroundPen(OH_Drawing_TextStyle* style, OH_Drawing_Pen* foregroundPen);

/**
 * @brief 返回设置的前景色画笔。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param foregroundPen 指向画笔{@link OH_Drawing_Pen}对象的指针，由{@link OH_Drawing_PenCreate}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleGetForegroundPen(OH_Drawing_TextStyle* style, OH_Drawing_Pen* foregroundPen);

/**
 * @brief 设置指定文本样式中的背景色画刷。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param backgroundBrush 指向画刷{@link OH_Drawing_Brush}对象的指针，由{@link OH_Drawing_BrushCreate}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTextStyleBackgroundBrush(OH_Drawing_TextStyle* style, OH_Drawing_Brush* backgroundBrush);

/**
 * @brief 返回设置的背景色画刷。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param backgroundBrush 指向画刷{@link OH_Drawing_Brush}对象的指针，由{@link OH_Drawing_BrushCreate}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleGetBackgroundBrush(OH_Drawing_TextStyle* style, OH_Drawing_Brush* backgroundBrush);

/**
 * @brief 设置指定文本样式中的背景色画笔。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param backgroundPen 指向画笔{@link OH_Drawing_Pen}对象的指针，由{@link OH_Drawing_PenCreate}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTextStyleBackgroundPen(OH_Drawing_TextStyle* style, OH_Drawing_Pen* backgroundPen);

/**
 * @brief 返回设置的背景色画笔。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param backgroundPen 指向画笔{@link OH_Drawing_Pen}对象的指针，由{@link OH_Drawing_PenCreate}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleGetBackgroundPen(OH_Drawing_TextStyle* style, OH_Drawing_Pen* backgroundPen);

/**
 * @brief 创建指向OH_Drawing_TypographyCreate对象的指针。不再需要{@link OH_Drawing_TypographyCreate}时，请使用
 * {@link OH_Drawing_DestroyTypographyHandler}接口释放该对象的指针。建议优先使用{@link OH_Drawing_CreateSharedFontCollection}函数创建
 * {@link OH_Drawing_FontCollection}对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param fontCollection 指向字体集对象{@link OH_Drawing_FontCollection}的指针，由{@link OH_Drawing_CreateFontCollection}获取。
 * @return 指向新创建的OH_Drawing_TypographyCreate对象的指针。
 * @since 8
 * @version 1.0
 */
OH_Drawing_TypographyCreate* OH_Drawing_CreateTypographyHandler(OH_Drawing_TypographyStyle* style,
    OH_Drawing_FontCollection* fontCollection);

/**
 * @brief 释放被OH_Drawing_TypographyCreate对象占据的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler 指向{@link OH_Drawing_TypographyCreate}对象的指针，由{@link OH_Drawing_CreateTypographyHandler}获取。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_DestroyTypographyHandler(OH_Drawing_TypographyCreate* handler);

/**
 * @brief 将指定文本样式压入文本样式栈，后续添加的文本总是会使用栈顶的文本样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler 指向{@link OH_Drawing_TypographyCreate}对象的指针，由{@link OH_Drawing_CreateTypographyHandler}获取。
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_TypographyHandlerPushTextStyle(OH_Drawing_TypographyCreate* handler, OH_Drawing_TextStyle* style);

/**
 * @brief 设置文本内容。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler 指向{@link OH_Drawing_TypographyCreate}对象的指针，由{@link OH_Drawing_CreateTypographyHandler}获取。
 * @param text 指向文本内容的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_TypographyHandlerAddText(OH_Drawing_TypographyCreate* handler, const char* text);

/**
 * @brief 从文本样式栈中弹出栈顶文本样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler 指向{@link OH_Drawing_TypographyCreate}对象的指针，由{@link OH_Drawing_CreateTypographyHandler}获取。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_TypographyHandlerPopTextStyle(OH_Drawing_TypographyCreate* handler);

/**
 * @brief 创建指向OH_Drawing_Typography对象的指针。不再需要{@link OH_Drawing_Typography}时，请使用{@link OH_Drawing_DestroyTypography}
 * 接口释放该对象的指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler 指向{@link OH_Drawing_TypographyCreate}对象的指针，由{@link OH_Drawing_CreateTypographyHandler}获取。
 * @return 指向OH_Drawing_Typography对象的指针。
 * @since 8
 * @version 1.0
 */
OH_Drawing_Typography* OH_Drawing_CreateTypography(OH_Drawing_TypographyCreate* handler);

/**
 * @brief 释放OH_Drawing_Typography对象占据的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向排版对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_DestroyTypography(OH_Drawing_Typography* typography);

/**
 * @brief 排版布局。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向排版对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param maxWidth 文本最大宽度。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_TypographyLayout(OH_Drawing_Typography* typography, double maxWidth);

/**
 * @brief 在指定位置绘制文本，从左上角开始绘制，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用并生效之后调用。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param canvas 指向OH_Drawing_Canvas对象的指针，由{@link OH_Drawing_CanvasCreate}获取。
 * @param positionX x坐标。
 * @param positionY y坐标。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_TypographyPaint(OH_Drawing_Typography* typography, OH_Drawing_Canvas* canvas,
    double positionX, double positionY);

/**
 * @brief 沿指定路径绘制文本。建议搭配{@link OH_Drawing_SetTypographyTextMaxLines}接口设置最大行为1行，避免因文本宽度超过排版宽度出现跨行重叠问题。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param canvas 指向OH_Drawing_Canvas对象的指针，由{@link OH_Drawing_CanvasCreate}获取。
 * @param path 指向OH_Drawing_Path对象的指针，由{@link OH_Drawing_PathCreate}获取。
 * @param hOffset 水平偏移量，文本沿路径的水平偏移（X 轴），向前为正，向后为负。
 * @param vOffset 垂直偏移量，文本沿路径的垂直偏移（Y 轴），向下为正，向上为负。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyPaintOnPath(OH_Drawing_Typography* typography, OH_Drawing_Canvas* canvas,
    OH_Drawing_Path* path, double hOffset, double vOffset);

/**
 * @brief 在约束矩形内布局文本。
 *
 * @param typography 指向文本对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param constraintsRect 约束布局的高度和宽度。
 * @param fitStrRangeArr 作为出参，包含实际容纳的段落文本的字符范围。指向数组对象{@link OH_Drawing_Array}的指针。
 *     通过{@link OH_Drawing_ReleaseArrayBuffer}释放内存。
 * @param fitStrRangeArrayLen 作为出参，容纳的字符串数组的大小。
 * @return 返回OH_Drawing_RectSize对象，表示段落文本的实际矩形。
 * @since 24
 */
OH_Drawing_RectSize OH_Drawing_TypographyLayoutWithConstraintsWithBuffer(OH_Drawing_Typography* typography,
    OH_Drawing_RectSize constraintsRect, OH_Drawing_Array** fitStrRangeArr, size_t* fitStrRangeArrayLen);

/**
 * @brief 根据数组索引获取指向OH_Drawing_Range对象的指针。
 *
 * @param array 指向数组对象{@link OH_Drawing_Array}的指针。
 * @param index 目标{@link OH_Drawing_Range}对象在数组中的索引。
 * @return 返回指向OH_Drawing_Range对象的指针。
 * @since 24
 */
OH_Drawing_Range* OH_Drawing_GetRangeByArrayIndex(OH_Drawing_Array* array, size_t index);

/**
 * @brief 释放{@link OH_Drawing_Array}对象占用的内存。
 *
 * @param array 指向数组对象{@link OH_Drawing_Array}的指针。
 *     支持的数组类型：
 *     字体全名数组，通过{@link OH_Drawing_GetSystemFontFullNamesByType}获取。
 *     文本行数组，通过{@link OH_Drawing_TypographyGetTextLines}获取。
 *     字符串索引数组，通过{@link OH_Drawing_GetRunStringIndices}获取。
 *     矩形数组，通过{@link OH_Drawing_RectCreateArray}获取。
 *     字体描述符数组，通过{@link OH_Drawing_GetFontFullDescriptorsFromStream}或{@link OH_Drawing_GetFontFullDescriptorsFromPath}
 *     获取。
 *     文本范围数组，通过{@link OH_Drawing_TypographyLayoutWithConstraintsWithBuffer}获取。
 * @return 函数执行结果。
 *     返回OH_DRAWING_SUCCESS表示操作成功。
 *     返回OH_DRAWING_ERROR_INCORRECT_PARAMETER表示array为空指针或类型不支持。
 * @since 24
 */
OH_Drawing_ErrorCode OH_Drawing_ReleaseArrayBuffer(OH_Drawing_Array* array);

/**
 * @brief 获取用户设置的排版宽度，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @return 返回最大宽度。
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetMaxWidth(OH_Drawing_Typography* typography);

/**
 * @brief 获取排版对象整体的高度，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @return 返回高度。
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetHeight(OH_Drawing_Typography* typography);

/**
 * @brief 获取排版对象最长行的宽度，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用，建议实际使用时将返回值向上取整。当文本内容为空时，返回0.0。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @return 返回最长行的宽度。
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetLongestLine(OH_Drawing_Typography* typography);

/**
 * @brief 获取排版对象最长行的宽度（该宽度包含当前行缩进的宽度），该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用，建议实际使用时将返回值向上取整。当文本内容为空时，返回0.0。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向{@link OH_Drawing_Typography}对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @return 返回最长行的宽度（该宽度包含当前行缩进的宽度），单位：物理像素px。
 * @since 13
 * @version 1.1
 */
double OH_Drawing_TypographyGetLongestLineWithIndent(OH_Drawing_Typography* typography);

/**
 * @brief 获取排版对象的最小固有宽度，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @return 返回最小固有宽度。
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetMinIntrinsicWidth(OH_Drawing_Typography* typography);

/**
 * @brief 获取排版对象的最大固有宽度，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @return 返回最大固有宽度。
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetMaxIntrinsicWidth(OH_Drawing_Typography* typography);

/**
 * @brief 获取排版样式字母文字基线。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @return 返回字母文字基线。
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetAlphabeticBaseline(OH_Drawing_Typography* typography);

/**
 * @brief 获取排版样式表意文字基线。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @return 返回表意文字基线。
 * @since 9
 * @version 1.1
 */
double OH_Drawing_TypographyGetIdeographicBaseline(OH_Drawing_Typography* typography);

/**
 * @brief 设置占位符。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler 指向{@link OH_Drawing_TypographyCreate}对象的指针，由{@link OH_Drawing_CreateTypographyHandler}获取。
 * @param span 指向{@link OH_Drawing_PlaceholderSpan}对象的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_TypographyHandlerAddPlaceholder(OH_Drawing_TypographyCreate* handler, OH_Drawing_PlaceholderSpan* span);

/**
 * @brief 获取排版对象中文本是否超过最大行，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用，如果没有通过
 * {@link OH_Drawing_SetTypographyTextMaxLines}接口设置最大行，则返回false。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @return 返回文本是否超过最大行，true表示超过，false表示未超过。
 * @since 11
 * @version 1.0
 */
bool OH_Drawing_TypographyDidExceedMaxLines(OH_Drawing_Typography* typography);

/**
 * @brief 获取排版对象中指定范围内的文本框，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用。不再需要{@link OH_Drawing_TextBox}时，请使用
 * {@link OH_Drawing_TypographyDestroyTextBox}接口释放该对象的指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param start 设置开始位置。
 * @param end 设置结束位置。
 * @param heightStyle 设置高度样式，支持可选的高度样式具体可见{@link OH_Drawing_RectHeightStyle}枚举。
 * @param widthStyle 设置宽度样式，支持可选的宽度样式具体可见{@link OH_Drawing_RectWidthStyle}枚举。
 * @return 返回指定范围内的文本框，具体可见{@link OH_Drawing_TextBox}结构体。
 * @since 11
 * @version 1.0
 */
OH_Drawing_TextBox* OH_Drawing_TypographyGetRectsForRange(OH_Drawing_Typography* typography,
    size_t start, size_t end, OH_Drawing_RectHeightStyle heightStyle, OH_Drawing_RectWidthStyle widthStyle);

/**
 * @brief 获取排版对象中占位符的文本框，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用。不再需要{@link OH_Drawing_TextBox}时，请使用
 * {@link OH_Drawing_TypographyDestroyTextBox}接口释放该对象的指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @return 返回占位符的文本框，返回类型为{@link OH_Drawing_TextBox}结构体。
 * @since 11
 * @version 1.0
 */
OH_Drawing_TextBox* OH_Drawing_TypographyGetRectsForPlaceholders(OH_Drawing_Typography* typography);

/**
 * @brief 获取文本框左侧位置。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textbox 指向OH_Drawing_TextBox对象的指针，由{@link OH_Drawing_TypographyGetRectsForRange}或
 *     {@link OH_Drawing_TypographyGetRectsForPlaceholders}获取。
 * @param index 文本框的索引。
 * @return 返回文本框左侧位置。
 * @since 11
 * @version 1.0
 */
float OH_Drawing_GetLeftFromTextBox(OH_Drawing_TextBox* textbox, int index);

/**
 * @brief 获取文本框右侧位置。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textbox 指向OH_Drawing_TextBox对象的指针，由{@link OH_Drawing_TypographyGetRectsForRange}或
 *     {@link OH_Drawing_TypographyGetRectsForPlaceholders}获取。
 * @param index 文本框的索引。
 * @return 返回文本框右侧位置。
 * @since 11
 * @version 1.0
 */
float OH_Drawing_GetRightFromTextBox(OH_Drawing_TextBox* textbox, int index);

/**
 * @brief 获取文本框顶部位置。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textbox 指向OH_Drawing_TextBox对象的指针，由{@link OH_Drawing_TypographyGetRectsForRange}或
 *     {@link OH_Drawing_TypographyGetRectsForPlaceholders}获取。
 * @param index 文本框的索引。
 * @return 返回文本框顶部位置。
 * @since 11
 * @version 1.0
 */
float OH_Drawing_GetTopFromTextBox(OH_Drawing_TextBox* textbox, int index);

/**
 * @brief 获取文本框底部位置。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textbox 指向OH_Drawing_TextBox对象的指针，由{@link OH_Drawing_TypographyGetRectsForRange}或
 *     {@link OH_Drawing_TypographyGetRectsForPlaceholders}获取。
 * @param index 文本框的索引。
 * @return 返回文本框底部位置。
 * @since 11
 * @version 1.0
 */
float OH_Drawing_GetBottomFromTextBox(OH_Drawing_TextBox* textbox, int index);

/**
 * @brief 获取文本框方向。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textbox 指向{@link OH_Drawing_TextBox}对象的指针，由{@link OH_Drawing_TypographyGetRectsForRange}或
 *     {@link OH_Drawing_TypographyGetRectsForPlaceholders}获取。
 * @param index 文本框的索引。
 * @return 返回文本框方向。
 * @since 11
 * @version 1.0
 */
int OH_Drawing_GetTextDirectionFromTextBox(OH_Drawing_TextBox* textbox, int index);

/**
 * @brief 获取文本框数量大小。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textBox 指向OH_Drawing_TextBox对象的指针，由{@link OH_Drawing_TypographyGetRectsForRange}或
 *     {@link OH_Drawing_TypographyGetRectsForPlaceholders}获取。
 * @return 返回文本框数量大小。
 * @since 11
 * @version 1.0
 */
size_t OH_Drawing_GetSizeOfTextBox(OH_Drawing_TextBox* textBox);

/**
 * @brief 获取坐标处文本的索引位置和亲和性。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param dx 光标的x坐标。
 * @param dy 光标的y坐标。
 * @return 返回坐标处字体的索引位置和亲和性，返回类型为{@link OH_Drawing_PositionAndAffinity}结构体。
 * @since 11
 * @version 1.0
 * @deprecated since 18
 * @useinstead OH_Drawing_TypographyGetGlyphPositionAtCoordinateWithCluster
 */
OH_Drawing_PositionAndAffinity* OH_Drawing_TypographyGetGlyphPositionAtCoordinate(OH_Drawing_Typography* typography,
    double dx, double dy);

/**
 * @brief 获取坐标处文本所属字符簇的索引位置和亲和性，字符簇指一个或多个字符组成的整体。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param dx 光标的x坐标。
 * @param dy 光标的y坐标。
 * @return 返回坐标处指定类型字体的索引位置和亲和性，返回类型为{@link OH_Drawing_PositionAndAffinity}结构体。
 * @since 11
 * @version 1.0
 */
OH_Drawing_PositionAndAffinity* OH_Drawing_TypographyGetGlyphPositionAtCoordinateWithCluster(
    OH_Drawing_Typography* typography, double dx, double dy);

/**
 * @brief 获取OH_Drawing_PositionAndAffinity对象的位置属性。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param positionAndAffinity 指向OH_Drawing_PositionAndAffinity对象的指针，由
 *     {@link OH_Drawing_TypographyGetGlyphPositionAtCoordinate}或
 *     {@link OH_Drawing_TypographyGetGlyphPositionAtCoordinateWithCluster}获取。
 * @return 返回OH_Drawing_PositionAndAffinity对象的位置属性。
 * @since 11
 * @version 1.0
 */
size_t OH_Drawing_GetPositionFromPositionAndAffinity(OH_Drawing_PositionAndAffinity* positionAndAffinity);

/**
 * @brief 获取OH_Drawing_PositionAndAffinity对象的亲和性，根据亲和性可判断字体会靠近前方文本还是后方文本。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param positionAndAffinity 指向OH_Drawing_PositionAndAffinity对象的指针，由
 *     {@link OH_Drawing_TypographyGetGlyphPositionAtCoordinate}或
 *     {@link OH_Drawing_TypographyGetGlyphPositionAtCoordinateWithCluster}获取。
 * @return 返回OH_Drawing_PositionAndAffinity对象的亲和性。
 * @since 11
 * @version 1.0
 */
int OH_Drawing_GetAffinityFromPositionAndAffinity(OH_Drawing_PositionAndAffinity* positionAndAffinity);

/**
 * @brief 获取排版对象中单词的边界。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param offset 单词索引。
 * @return 返回单词边界，返回类型为{@link OH_Drawing_Range}结构体。
 * @since 11
 * @version 1.0
 */
OH_Drawing_Range* OH_Drawing_TypographyGetWordBoundary(OH_Drawing_Typography* typography, size_t offset);

/**
 * @brief 获取OH_Drawing_Range对象开始位置。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param range 指向OH_Drawing_Range对象的指针，由{@link OH_Drawing_TypographyGetWordBoundary}获取。
 * @return 返回OH_Drawing_Range对象开始位置。
 * @since 11
 * @version 1.0
 */
size_t OH_Drawing_GetStartFromRange(OH_Drawing_Range* range);

/**
 * @brief 获取OH_Drawing_Range对象结束位置。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param range 指向OH_Drawing_Range对象的指针，由{@link OH_Drawing_TypographyGetWordBoundary}获取。
 * @return 返回OH_Drawing_Range对象结束位置。
 * @since 11
 * @version 1.0
 */
size_t OH_Drawing_GetEndFromRange(OH_Drawing_Range* range);

/**
 * @brief 获取排版对象中文本行数，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @return 返回行数。
 * @since 11
 * @version 1.0
 */
size_t OH_Drawing_TypographyGetLineCount(OH_Drawing_Typography* typography);

/**
 * @brief 设置指定文本样式中的装饰线样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param decorationStyle 设置的文本装饰样式，支持可选的装饰样式具体可见{@link OH_Drawing_TextDecorationStyle}枚举。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTextStyleDecorationStyle(OH_Drawing_TextStyle* style, int decorationStyle);

/**
 * @brief 设置文本装饰线的粗细缩放比例。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param decorationThicknessScale 粗细缩放比例。默认值为1，如果设置的粗细缩放比例小于等于0，不会绘制装饰线。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTextStyleDecorationThicknessScale(OH_Drawing_TextStyle* style, double decorationThicknessScale);

/**
 * @brief 设置文本的字符间距。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param letterSpacing 间距大小。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTextStyleLetterSpacing(OH_Drawing_TextStyle* style, double letterSpacing);

/**
 * @brief 设置文本的单词间距。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param wordSpacing 间距大小。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTextStyleWordSpacing(OH_Drawing_TextStyle* style, double wordSpacing);

/**
 * @brief 设置文本为一半行间距。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param halfLeading 设置一半行间距是否生效。true表示生效，false表示不生效。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTextStyleHalfLeading(OH_Drawing_TextStyle* style, bool halfLeading);

/**
 * @brief 设置文本的省略号内容。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param ellipsis 设置省略号内容，数据类型为指向char的指针。
 * @since 11
 * @version 1.0
 * @deprecated since 18
 * @useinstead OH_Drawing_SetTypographyTextEllipsis
 */
void OH_Drawing_SetTextStyleEllipsis(OH_Drawing_TextStyle* style, const char* ellipsis);

/**
 * @brief 设置文本的省略号样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param ellipsisModal 设置省略号样式，可选的省略号样式具体可见{@link OH_Drawing_EllipsisModal}枚举。
 * @since 11
 * @version 1.0
 * @deprecated since 18
 * @useinstead OH_Drawing_SetTypographyTextEllipsisModal
 */
void OH_Drawing_SetTextStyleEllipsisModal(OH_Drawing_TextStyle* style, int ellipsisModal);

/**
 * @brief 设置文本的中断策略。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param breakStrategy 设置中断策略，支持可选的中断策略具体可见{@link OH_Drawing_BreakStrategy}枚举。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextBreakStrategy(OH_Drawing_TypographyStyle* style, int breakStrategy);

/**
 * @brief 设置单词的断词方式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param wordBreakType 设置断词方式，支持可选的断词方式样式具体可见{@link OH_Drawing_WordBreakType}枚举。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextWordBreakType(OH_Drawing_TypographyStyle* style, int wordBreakType);

/**
 * @brief 设置文本的省略模式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TypographyStyle对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param ellipsisModal 设置省略号样式，可选的省略号样式具体可见{@link OH_Drawing_EllipsisModal}枚举。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextEllipsisModal(OH_Drawing_TypographyStyle* style, int ellipsisModal);

/**
 * @brief 获取排版对象中指定行的行高，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param lineNumber 要指定的行数。
 * @return 返回指定行的行高。
 * @since 11
 * @version 1.0
 */
double OH_Drawing_TypographyGetLineHeight(OH_Drawing_Typography* typography, int lineNumber);

/**
 * @brief 获取指定行的行宽，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param lineNumber 要指定的行数。
 * @return 返回指定行的行宽。
 * @since 11
 * @version 1.0
 */
double OH_Drawing_TypographyGetLineWidth(OH_Drawing_Typography* typography, int lineNumber);

/**
 * @brief 获取排版对象中行的边界，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用。该接口只能获取已有行的边界，即输入行索引从0开始，最大行索引为
 * {@link OH_Drawing_TypographyGetLineCount} - 1。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向文本对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param lineNumber 行索引
 * @param includeSpaces 设置返回的边界是否包含空格，true为包含空格，false为不包含空格。
 * @return 返回指向行边界对象的指针{@link OH_Drawing_Range}。如果输入的行索引是非法的行索引，则返回的边界范围的start和end都为0。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Range* OH_Drawing_TypographyGetLineTextRange(OH_Drawing_Typography* typography,
    int lineNumber, bool includeSpaces);

/**
 * @brief 构造字体描述对象，用于描述系统字体详细信息。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return 返回指向已创建的字体描述对象{@link OH_Drawing_FontDescriptor}的指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontDescriptor* OH_Drawing_CreateFontDescriptor(void);

/**
 * @brief 释放字体描述对象占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param descriptor 指向字体描述对象{@link OH_Drawing_FontDescriptor}的指针，由{@link OH_Drawing_CreateFontDescriptor}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroyFontDescriptor(OH_Drawing_FontDescriptor* descriptor);

/**
 * @brief 构造字体解析对象，用于解析系统字体。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return 返回指向已创建的字体解析对象{@link OH_Drawing_FontParser}的指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontParser* OH_Drawing_CreateFontParser(void);

/**
 * @brief 释放字体解析对象占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param parser 指向字体解析对象{@link OH_Drawing_FontParser}的指针，由{@link OH_Drawing_CreateFontParser}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroyFontParser(OH_Drawing_FontParser* parser);

/**
 * @brief 获取系统字体名称列表，此接口仅在2in1、phone设备上可用。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontParser 指向字体解析对象{@link OH_Drawing_FontParser}的指针，由{@link OH_Drawing_CreateFontParser}获取。
 * @param num 返回获取到的系统字体名称数量。
 * @return 返回获取到的系统字体列表。
 * @since 12
 * @version 1.0
 */
char** OH_Drawing_FontParserGetSystemFontList(OH_Drawing_FontParser* fontParser, size_t* num);

/**
 * @brief 释放系统字体名称列表占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontList 指向系统字体名称列表的指针。
 * @param num 系统字体名称列表的数量。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroySystemFontList(char** fontList, size_t num);

/**
 * @brief 根据传入的系统字体名称获取系统字体的相关信息。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontParser 指向字体解析对象{@link OH_Drawing_FontParser}的指针，由{@link OH_Drawing_CreateFontParser}获取。
 * @param name 系统字体名。
 * @return 返回系统字体描述对象，不再需要时，请使用{@link OH_Drawing_DestroyFontParser}释放该对象指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontDescriptor* OH_Drawing_FontParserGetFontByName(OH_Drawing_FontParser* fontParser, const char* name);

/**
 * @brief 获取排版对象的行位置信息，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用。不再需要{@link OH_Drawing_LineMetrics}时，请使用
 * {@link OH_Drawing_DestroyLineMetrics}接口释放该对象的指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向文本对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @return 返回指向行位置信息对象{@link OH_Drawing_LineMetrics}的指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_LineMetrics* OH_Drawing_TypographyGetLineMetrics(OH_Drawing_Typography* typography);

/**
 * @brief 获取行数量。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lineMetrics 指向行位置信息对象{@link OH_Drawing_LineMetrics}的指针，由{@link OH_Drawing_LineMetrics}获取。
 * @return 返回行数量。
 * @since 12
 * @version 1.0
 */
size_t OH_Drawing_LineMetricsGetSize(OH_Drawing_LineMetrics* lineMetrics);

/**
 * @brief 释放行位置信息对象占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lineMetrics 指向行位置信息对象{@link OH_Drawing_LineMetrics}的指针，由{@link OH_Drawing_LineMetrics}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroyLineMetrics(OH_Drawing_LineMetrics* lineMetrics);

/**
 * @brief 获取排版对象的指定行位置信息，具体参见{@link OH_Drawing_LineMetr}结构体，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向文本对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param lineNumber 要获取的行数。
 * @param lineMetric 指向行位置信息对象{@link OH_Drawing_LineMetrics}的指针，由{@link OH_Drawing_LineMetrics}获取。
 * @return 行位置信息对象是否成功获取。true表示成功获取，false表示未成功获取。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyGetLineMetricsAt(OH_Drawing_Typography* typography,
    int lineNumber, OH_Drawing_LineMetrics* lineMetric);

/**
 * @brief 设置排版样式省略号文本。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param ellipsis 省略号文本。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextEllipsis(OH_Drawing_TypographyStyle* style, const char* ellipsis);

/**
 * @brief 设置指定排版样式的语言环境。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param locale 语言环境，数据类型为指向char的指针，如'en'代表英文，'zh-Hans'代表简体中文，'zh-Hant'代表繁体中文。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLocale(OH_Drawing_TypographyStyle* style, const char* locale);

/**
 * @brief 设置文本划分比率。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param textSplitRatio 文本划分比率。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextSplitRatio(OH_Drawing_TypographyStyle* style, float textSplitRatio);

/**
 * @brief 获取指定排版样式中设置的默认文本样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回指向文本样式{@link OH_Drawing_TextStyle}的指针，不再需要时，请使用{@link OH_Drawing_DestroyTextStyle}释放该对象指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextStyle* OH_Drawing_TypographyGetTextStyle(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取文字对齐方式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回文字对齐方式。
 * @since 12
 * @version 1.0
 * @deprecated since 18
 * @useinstead OH_Drawing_TypographyStyleGetEffectiveAlignment
 */
int OH_Drawing_TypographyGetEffectiveAlignment(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取文本是否有最大行数限制。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回文本是否有最大行数限制，true表示有最大行数限制，false表示无最大行数限制。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyIsLineUnlimited(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取指定排版样式是否配置省略号。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回指定排版样式是否配置省略号，true表示已配置省略号，false表示没有配置省略号。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyIsEllipsized(OH_Drawing_TypographyStyle* style);

/**
 * @brief 设置排版样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextStyle(OH_Drawing_TypographyStyle* handler, OH_Drawing_TextStyle* style);

/**
 * @brief 获取文本字体属性。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向文本对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param fontmetrics 指向字体属性对象{@link OH_Drawing_Font_Metrics}的指针，由{@link OH_Drawing_Font_Metrics}获取。
 * @return 是否获取到字体属性。true表示获取到字体属性，false表示未获取到字体属性。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TextStyleGetFontMetrics(OH_Drawing_Typography* typography,
    OH_Drawing_TextStyle* style, OH_Drawing_Font_Metrics* fontmetrics);

/**
 * @brief 获取排版对象中指定行的位置信息或指定行第一个字符的位置信息，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向文本对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param lineNumber 行号。
 * @param oneLine true为获取整行的位置信息，false为获取第一个字符的位置信息。
 * @param includeWhitespace 文字宽度是否包含空白符。true表示不包含空白符，false表示包含空白符。
 * @param drawingLineMetrics 指向行位置信息对象{@link OH_Drawing_LineMetrics}的指针，由{@link OH_Drawing_LineMetrics}获取。
 * @return 指定行的行位置信息或第一个字符的位置信息是否成功获取，true表示成功获取，false表示未成功获取。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyGetLineInfo(OH_Drawing_Typography* typography, int lineNumber, bool oneLine,
    bool includeWhitespace, OH_Drawing_LineMetrics* drawingLineMetrics);

/**
 * @brief 设置排版样式默认字重。目前只有系统默认字体支持字重的调节，其他字体设置字重值小于semi-bold时字体粗细无变化，当设置字重值大于等于semi-bold时可能会触发伪加粗效果。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param weight 设置字重，设置0字重为thin，设置1字重为extra-light，设置2字重为light，设置4字重为medium，设置5字重为semi-bold，
 *     设置6字重为bold，设置7字重为extra-bold，设置8字重为black，设置3或其它字重为normal/regular，具体可见{@link OH_Drawing_FontWeight}枚举。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextFontWeight(OH_Drawing_TypographyStyle* style, int weight);

/**
 * @brief 设置排版样式默认的字体样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param fontStyle 设置字体样式，设置1为斜体，设置0或其它为非斜体，具体可见{@link OH_Drawing_FontStyle}枚举。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextFontStyle(OH_Drawing_TypographyStyle* style, int fontStyle);

/**
 * @brief 设置字体家族的名称。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param fontFamily 字体家族的名称，数据类型为指向char的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextFontFamily(OH_Drawing_TypographyStyle* style, const char* fontFamily);

/**
 * @brief 设置文本排版字号。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param fontSize 字号（大于0）。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextFontSize(OH_Drawing_TypographyStyle* style, double fontSize);

/**
 * @brief 设置文本排版字体高度。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param fontHeight 字体高度。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextFontHeight(OH_Drawing_TypographyStyle* style, double fontHeight);

/**
 * @brief 设置文本排版是否为一半行间距。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param halfLeading 设置一半行间距是否生效，true表示生效，false表示不生效。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextHalfLeading(OH_Drawing_TypographyStyle* style, bool halfLeading);

/**
 * @brief 设置文本排版是否启用行样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param useLineStyle 设置行样式是否启用，true表示启用，false表示不启用。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextUseLineStyle(OH_Drawing_TypographyStyle* style, bool useLineStyle);

/**
 * @brief 设置排版样式中支柱样式的文本样式字重。目前只有系统默认字体支持字重的调节，其他字体设置字重值小于semi-bold时字体粗细无变化，当设置字重值大于等于semi-bold时可能会触发伪加粗效果。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param weight 设置字重，设置0字重为thin，设置1字重为extra-light，设置2字重为light，设置4字重为medium，设置5字重为semi-bold，设置6字重为bold，设置7字重为extra-bold，
 *     设置8字重为black，设置3或其它字重为normal/regular，具体可见{@link OH_Drawing_FontWeight}枚举。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleFontWeight(OH_Drawing_TypographyStyle* style, int weight);

/**
 * @brief 设置文本排版样式中支柱样式的字体样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格指向排版样式对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param fontStyle 设置字体样式，设置1为斜体，设置0或其它为非斜体，具体可见{@link OH_Drawing_FontStyle}枚举。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleFontStyle(OH_Drawing_TypographyStyle* style, int fontStyle);

/**
 * @brief 设置文本排版行样式字体类型。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param fontFamiliesNumber 字体名称数量。
 * @param fontFamilies 指向字体类型的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleFontFamilies(OH_Drawing_TypographyStyle* style,
    int fontFamiliesNumber, const char* fontFamilies[]);

/**
 * @brief 设置文本排版行样式字号。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param lineStyleFontSize 字号（大于0）。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleFontSize(OH_Drawing_TypographyStyle* style, double lineStyleFontSize);

/**
 * @brief 设置文本排版行样式字体高度。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param lineStyleFontHeight 字体高度。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleFontHeight(OH_Drawing_TypographyStyle* style, double lineStyleFontHeight);

/**
 * @brief 设置文本排版行样式是否为一半行间距。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param lineStyleHalfLeading 设置一半行间距是否生效。true表示生效，false表示不生效。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleHalfLeading(OH_Drawing_TypographyStyle* style, bool lineStyleHalfLeading);

/**
 * @brief 设置文本排版行样式间距比例。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param spacingScale 间距比例。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleSpacingScale(OH_Drawing_TypographyStyle* style, double spacingScale);

/**
 * @brief 设置文本排版是否仅启用行样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param lineStyleOnly 设置仅启用行样式是否生效。true表示生效，false表示不生效。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextLineStyleOnly(OH_Drawing_TypographyStyle* style, bool lineStyleOnly);

/**
 * @brief 创建指向字体阴影对象的指针。不再需要{@link OH_Drawing_TextShadow}时，请使用{@link OH_Drawing_DestroyTextShadow}接口释放该对象的指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return 指向创建的字体阴影对象。
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextShadow* OH_Drawing_CreateTextShadow(void);

/**
 * @brief 释放被字体阴影对象占据的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param shadow 指向字体阴影对象{@link OH_Drawing_TextShadow}的指针，由{@link OH_Drawing_CreateTextShadow}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroyTextShadow(OH_Drawing_TextShadow* shadow);

/**
 * @brief 获取字体阴影容器。不再需要{@link OH_Drawing_TextShadow}时，请使用{@link OH_Drawing_DestroyTextShadows}接口释放该对象的指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回指向字体阴影容器{@link OH_Drawing_TextShadow}的指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextShadow* OH_Drawing_TextStyleGetShadows(OH_Drawing_TextStyle* style);

/**
 * @brief 获取字体阴影容器的大小。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return int 返回字体阴影容器的大小。
 * @since 12
 * @version 1.0
 */
int OH_Drawing_TextStyleGetShadowCount(OH_Drawing_TextStyle* style);

/**
 * @brief 字体阴影容器中添加字体阴影元素。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param shadow 指向字体阴影对象{@link OH_Drawing_TextShadow}的指针，由{@link OH_Drawing_CreateTextShadow}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleAddShadow(OH_Drawing_TextStyle* style, const OH_Drawing_TextShadow* shadow);

/**
 * @brief 清除字体阴影容器中的所有元素。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleClearShadows(OH_Drawing_TextStyle* style);

/**
 * @brief 根据下标获取字体阴影容器中的元素。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param index 下标索引。
 * @return 返回指向字体阴影对象{@link OH_Drawing_TextShadow}的指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextShadow* OH_Drawing_TextStyleGetShadowWithIndex(OH_Drawing_TextStyle* style, int index);

/**
 * @brief 设置文本的排版缩进，不调用此接口默认文本无缩进。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向排版对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param indentsNumber 为段落设置的缩进数量。该值应小于或等于 indents 数组的长度，以避免访问数组越界导致的显示异常。
 * @param indents 指向浮点类型数组的指针，每个数组元素表示一个缩进宽度，单位为物理像素（px）。在应用{@link OH_Drawing_Typography}接口时，需要先声明并初始化该浮点数组。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographySetIndents(OH_Drawing_Typography* typography, int indentsNumber, const float indents[]);

/**
 * @brief 根据行索引获取排版对象缩进容器中的元素，行索引从0开始。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向文本对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param index 下标索引。
 * @return float 返回索引对应的元素值。
 * @since 12
 * @version 1.0
 */
float OH_Drawing_TypographyGetIndentsWithIndex(OH_Drawing_Typography* typography, int index);

/**
 * @brief 释放由被字体阴影对象OH_Drawing_TextShadow构成的vector占据的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param shadow 指向字体阴影对象{@link OH_Drawing_TextShadow}的指针，由{@link OH_Drawing_CreateTextShadow}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroyTextShadows(OH_Drawing_TextShadow* shadow);

/**
 * @brief 设置文本高度修饰符模式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param heightMode 文本高度修饰符模式，为{@link OH_Drawing_TextHeightBehavior}类型的枚举值。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyTextSetHeightBehavior(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TextHeightBehavior heightMode);

/**
 * @brief 获取文本高度修饰符模式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回文本高度修饰符模式，为{@link OH_Drawing_TextHeightBehavior}类型的枚举值。
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextHeightBehavior OH_Drawing_TypographyTextGetHeightBehavior(OH_Drawing_TypographyStyle* style);

/**
 * @brief 设置文本背景矩形框和样式id。样式id仅当背景框为圆角矩形时有效。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param rectStyleInfo 指向{@link OH_Drawing_RectStyle_Info}对象的指针。
 * @param styleId 要设置的样式id，仅当背景框为圆角矩形时有效。文本处理时会被划分为多个分段，每个分段都有自己的TextStyle，id标识着这个分段将被绘制于第几个背景矩形框中。
 *     若一行中每个分段的id全为0，表示所有分段绘制在同一个圆角矩形背景框中；若一行中的id为0, 1，则id为0的分段绘制在一个圆角矩形背景框内，id为1的分段绘制在另一个圆角矩形背景框内，以此类推。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleSetBackgroundRect(OH_Drawing_TextStyle* style,
    const OH_Drawing_RectStyle_Info* rectStyleInfo, int styleId);

/**
 * @brief 设置排版创建过程中的符号。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler 指向{@link OH_Drawing_TypographyCreate}对象的指针，由{@link OH_Drawing_CreateTypographyHandler}获取。
 * @param symbol 设置的symbol码位值，详见{@link 主题图标库}列表视图下的unicode值。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyHandlerAddSymbol(OH_Drawing_TypographyCreate* handler, uint32_t symbol);

/**
 * @brief 设置文本样式中指定字体特征是否启用。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param tag 指向字体特征键值对中关键字所标识的字符串。
 * @param value 要设置的字体特征键值对的值。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleAddFontFeature(OH_Drawing_TextStyle* style, const char* tag, int value);

/**
 * @brief 添加可变字体属性。对应的字体文件（.ttf文件）需要支持可变调节，此接口才能生效。当对应的字体不支持可变调节时，此接口调用不生效。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param axis 可变字体属性键值对中的键。目前仅支持'wght'，表示字重属性。
 * @param value 设置的可变字体属性键值对的值。目前默认字体下字重属性支持的取值范围为[0,900]。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleAddFontVariation(OH_Drawing_TextStyle* style, const char* axis, const float value);

/**
 * @brief 添加归一化后的可变字体属性。对应的字体文件（.ttf文件）需要支持可变调节，此接口才能生效。
 *
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param axis 可变字体属性键值对中的键。
 * @param normalizedValue 设置的可变字体属性键值对的值。归一化取值范围为[-1,1]，映射字体文件中配置的最小值到最大值范围，0表示字体文件中配置的默认值。
 * @since 24
 */
void OH_Drawing_TextStyleAddFontVariationWithNormalization(OH_Drawing_TextStyle* style,
    const char* axis, const float normalizedValue);

/**
 * @brief 获取指定文本样式的字体特征map容器中所有内容。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 要获取的字体特征容器的所有内容，指向存放容器所有键值对的一个结构体数组。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontFeature* OH_Drawing_TextStyleGetFontFeatures(OH_Drawing_TextStyle* style);

/**
 * @brief 释放存放字体特征所有内容的结构体数组所占用的空间。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontFeature 指向存放容器所有键值对的结构体数组指针，由{@link OH_Drawing_TextStyleGetFontFeatures}获取。
 * @param fontFeatureSize 存放容器所有键值对的结构体数组的大小。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleDestroyFontFeatures(OH_Drawing_FontFeature* fontFeature, size_t fontFeatureSize);

/**
 * @brief 获取指定文本样式中字体特征map容器的大小。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 字体特征map容器的大小。
 * @since 12
 * @version 1.0
 */
size_t OH_Drawing_TextStyleGetFontFeatureSize(OH_Drawing_TextStyle* style);

/**
 * @brief 清除指定文本样式的字体特征map容器中所有内容。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleClearFontFeature(OH_Drawing_TextStyle* style);

/**
 * @brief 设置文本样式基线偏移。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param lineShift 文本的基线偏移。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleSetBaselineShift(OH_Drawing_TextStyle* style, double lineShift);

/**
 * @brief 获取指定文本样式的基线偏移。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向OH_Drawing_TextStyle对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 基线偏移的值。
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TextStyleGetBaselineShift(OH_Drawing_TextStyle* style);

/**
 * @brief 获取文本颜色。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回文本颜色。
 * @since 12
 * @version 1.0
 */
uint32_t OH_Drawing_TextStyleGetColor(OH_Drawing_TextStyle* style);

/**
 * @brief 获取文本装饰样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回文本装饰样式，具体可见{@link OH_Drawing_TextDecorationStyle}枚举。
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextDecorationStyle OH_Drawing_TextStyleGetDecorationStyle(OH_Drawing_TextStyle* style);

/**
 * @brief 获取字重。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回字重，具体可见{@link OH_Drawing_FontWeight}枚举。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontWeight OH_Drawing_TextStyleGetFontWeight(OH_Drawing_TextStyle* style);

/**
 * @brief 获取指定文本样式的字体样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向字体样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回字体样式，具体可见{@link OH_Drawing_FontStyle}枚举。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyle OH_Drawing_TextStyleGetFontStyle(OH_Drawing_TextStyle* style);

/**
 * @brief 获取指定文本样式的字体基线位置。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回字体基线位置，具体可见{@link OH_Drawing_TextBaseline}枚举。
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextBaseline OH_Drawing_TextStyleGetBaseline(OH_Drawing_TextStyle* style);

/**
 * @brief 获取字体类型名称列表。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param num 指向字体名称数量的指针。
 * @return 返回获取到的字体类型列表。
 * @since 12
 * @version 1.0
 */
char** OH_Drawing_TextStyleGetFontFamilies(OH_Drawing_TextStyle* style, size_t* num);

/**
 * @brief 释放长度为num的字体家族名称列表占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontFamilies 指向字体家族名称列表的指针。
 * @param num 字体家族名称列表的长度。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleDestroyFontFamilies(char** fontFamilies, size_t num);

/**
 * @brief 获取指定文本样式字号。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回字号。
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TextStyleGetFontSize(OH_Drawing_TextStyle* style);

/**
 * @brief 获取指定文本样式的字符间距。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回字符间距大小。
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TextStyleGetLetterSpacing(OH_Drawing_TextStyle* style);

/**
 * @brief 获取指定文本样式的单词间距。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回单词间距大小。
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TextStyleGetWordSpacing(OH_Drawing_TextStyle* style);

/**
 * @brief 获取指定文本样式行高缩放系数。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回行高缩放系数。
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TextStyleGetFontHeight(OH_Drawing_TextStyle* style);

/**
 * @brief 获取指定文本样式一半行间距开关状态。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回当前文本样式一半行间距的开关状态。true表示开启一半行间距，false表示未开启一半行间距。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TextStyleGetHalfLeading(OH_Drawing_TextStyle* style);

/**
 * @brief 设置文本垂直对齐方式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param align 设置文本垂直对齐方式。默认为基线对齐，其余对齐方式见{@link OH_Drawing_TextVerticalAlignment}。
 * @since 20
 * @version 1.0
 */
void OH_Drawing_SetTypographyVerticalAlignment(OH_Drawing_TypographyStyle* style,
    OH_Drawing_TextVerticalAlignment align);

/**
 * @brief 获取语言环境。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回语言环境，数据类型为指向char对象的指针。语言环境格式为：语言-国家。如zh-CN表示中文（中国），en-US表示英语（美国）等。具体参考BCP 47语言标签标准。
 * @since 12
 * @version 1.0
 */
const char* OH_Drawing_TextStyleGetLocale(OH_Drawing_TextStyle* style);

/**
 * @brief 设置文本排版时是否使能上标或下标。未调用此接口时，默认不使能。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TextStyle}对象的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param textBadgeType 设置文本排版时是否使能上标或下标。TEXT_SUPERSCRIPT表示使能上标，TEXT_SUBSCRIPT表示使能下标，默认值为TEXT_BADGE_NONE表示不使能。
 * @since 20
 */
void OH_Drawing_SetTextStyleBadgeType(OH_Drawing_TextStyle* style, OH_Drawing_TextBadgeType textBadgeType);

/**
 * @brief 设置文本样式中的字体样式，包括字体字重、字体宽度和字体斜度。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingTextStyle 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @param fontStyle 字体样式对象，包括字体字重、字体宽度和字体斜度信息。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTextStyleFontStyleStruct(OH_Drawing_TextStyle* drawingTextStyle,
    OH_Drawing_FontStyleStruct fontStyle);

/**
 * @brief 获取文本样式中的字体样式，包括字体字重、字体宽度和字体斜度。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingTextStyle 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回获取到的字体样式对象，包括字体字重、字体宽度和字体斜度信息。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyleStruct OH_Drawing_TextStyleGetFontStyleStruct(OH_Drawing_TextStyle* drawingTextStyle);

/**
 * @brief 设置排版样式中默认文本样式的字体样式，包括字体字重、字体宽度和字体斜度。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingStyle 指向排版样式对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param fontStyle 字体样式对象，包括字体字重、字体宽度和字体斜度信息。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyStyleFontStyleStruct(OH_Drawing_TypographyStyle* drawingStyle,
    OH_Drawing_FontStyleStruct fontStyle);

/**
 * @brief 获取排版样式中默认文本样式的字体样式，包括字体字重、字体宽度和字体斜度。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingStyle 指向文本风格对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回获取到的字体样式对象，包括字体字重、字体宽度和字体斜度信息。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyleStruct OH_Drawing_TypographyStyleGetFontStyleStruct(OH_Drawing_TypographyStyle* drawingStyle);

/**
 * @brief 判断两个文本样式对象是否相等，字宽属性不参与对比。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 比较的文本样式对象。
 * @param comparedStyle 比较的文本样式对象。
 * @return 返回两个文本样式对象是否相等。true表示相等，false表示不相等。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TextStyleIsEqual(const OH_Drawing_TextStyle* style, const OH_Drawing_TextStyle* comparedStyle);

/**
 * @brief 判断两个文本样式对象的字体样式属性是否相等。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 比较的文本样式对象。
 * @param comparedStyle 比较的文本样式对象。
 * @return 返回两个文本样式对象的字体样式属性是否相等的结果。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TextStyleIsEqualByFont(const OH_Drawing_TextStyle* style, const OH_Drawing_TextStyle* comparedStyle);

/**
 * @brief 判断两个文本样式对象是否有一样的字体样式类型。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 比较的文本样式对象。
 * @param comparedStyle 比较的文本样式对象。
 * @param textStyleType 文本样式类型枚举{@link OH_Drawing_TextStyleType}。
 * @return 返回两个TextStyle对象是否有对应的文本样式类型一样的结果。true表示其文本样式类型一样，false表示不一样。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TextStyleIsAttributeMatched(const OH_Drawing_TextStyle* style,
    const OH_Drawing_TextStyle* comparedStyle, OH_Drawing_TextStyleType textStyleType);

/**
 * @brief 设置占位符。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextStyleSetPlaceholder(OH_Drawing_TextStyle* style);

/**
 * @brief 返回是否有设置文本占位符。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本样式对象{@link OH_Drawing_TextStyle}的指针，由{@link OH_Drawing_CreateTextStyle}获取。
 * @return 返回是否有设置文本占位符。true表示有设置文本占位符，false表示未设置文本占位符。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TextStyleIsPlaceholder(OH_Drawing_TextStyle* style);

/**
 * @brief 获取文本对齐模式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回文本对齐模式的枚举值{@link OH_Drawing_TextAlign}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextAlign OH_Drawing_TypographyStyleGetEffectiveAlignment(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取文本是否启用字形轮廓自动调整，字形轮廓自动调整用于在渲染小字号文本时改善其可读性和外观。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回文本是否启用字体提示。true表示启用，false表示不启用。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyStyleIsHintEnabled(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取系统字体配置信息。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param errorCode 错误码，具体可见{@link OH_Drawing_FontConfigInfoErrorCode}枚举。
 * @return 返回系统字体配置信息的指针，不再需要时，请使用{@link OH_Drawing_DestroySystemFontConfigInfo}释放该对象指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontConfigInfo* OH_Drawing_GetSystemFontConfigInfo(OH_Drawing_FontConfigInfoErrorCode* errorCode);

/**
 * @brief 释放系统字体配置信息占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawFontCfgInfo 指向系统字体配置信息{@link OH_Drawing_FontConfigInfo}的指针，由{@link OH_Drawing_GetSystemFontConfigInfo}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DestroySystemFontConfigInfo(OH_Drawing_FontConfigInfo* drawFontCfgInfo);

/**
 * @brief 设置文本支柱样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param strutstyle 指向支柱样式对象{@link OH_Drawing_StrutStyle}的指针，由{@link OH_Drawing_TypographyStyleGetStrutStyle}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTypographyStyleTextStrutStyle(OH_Drawing_TypographyStyle* style, OH_Drawing_StrutStyle* strutstyle);

/**
 * @brief 释放被支柱样式对象占据的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param strutstyle 指向支柱样式对象{@link OH_Drawing_StrutStyle}的指针，由{@link OH_Drawing_TypographyStyleGetStrutStyle}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyStyleDestroyStrutStyle(OH_Drawing_StrutStyle* strutstyle);

/**
 * @brief 获取文本支柱样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回指向支柱样式对象{@link OH_Drawing_StrutStyle}的指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_StrutStyle* OH_Drawing_TypographyStyleGetStrutStyle(OH_Drawing_TypographyStyle* style);

/**
 * @brief 判断支柱样式结构体是否相同。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param from 被比较的支柱样式结构体。
 * @param to 用于比较的支柱样式结构体。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyStyleStrutStyleEquals(OH_Drawing_StrutStyle* from, OH_Drawing_StrutStyle* to);

/**
 * @brief 设置文本是否启用字形轮廓自动调整，字形轮廓自动调整用于在渲染小字号文本时改善其可读性和外观。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格对象{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param hintsEnabled 是否启用字体提示。true表示启用，false表示不启用。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyStyleSetHintsEnabled(OH_Drawing_TypographyStyle* style, bool hintsEnabled);

/**
 * @brief 从排版对象中目标行获取所有字体度量信息，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用之后调用，否则会返回空指针。不再需要
 * {@link OH_Drawing_Font_Metrics}时，请使用{@link OH_Drawing_TypographyDestroyLineFontMetrics}接口释放该对象的指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 指向文本对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param lineNumber 指定行数，取值为整数，最小有效值为1，最大行取决于文本输入后字体引擎解析出来的行数，若输入值大于最大行会返回错误值并打印错误消息。
 * @param fontMetricsSize 指示从当前行返回的字体度量结构的大小。
 * @return 返回当前行的所有字体度量信息。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Font_Metrics* OH_Drawing_TypographyGetLineFontMetrics(OH_Drawing_Typography* typography,
    size_t lineNumber, size_t* fontMetricsSize);

/**
 * @brief 释放指定行所有字体度量结构体集合所占用的所有空间。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lineFontMetric 指示要释放空间的指定行所有字体度量结构体集合的第一个地址。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyDestroyLineFontMetrics(OH_Drawing_Font_Metrics* lineFontMetric);

/**
 * @brief 将排版标记为脏数据，用于初始化排版状态。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 表示指向文本{@link OH_Drawing_Typography}对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyMarkDirty(OH_Drawing_Typography* typography);

/**
 * @brief 获取文本中尚未解析的字形的数量，该接口需要在{@link OH_Drawing_TypographyLayout}接口调用并生效之后调用。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 表示指向文本{@link OH_Drawing_Typography}对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @return 返回文本中尚未解析的字形的数量。
 * @since 12
 * @version 1.0
 */
int32_t OH_Drawing_TypographyGetUnresolvedGlyphsCount(OH_Drawing_Typography* typography);

/**
 * @brief 更新排版对象中的字体大小。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 表示指向排版对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param from 保留字段，暂未使用。
 * @param to 保留字段，暂未使用。
 * @param fontSize 表示更新后的字体大小。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyUpdateFontSize(OH_Drawing_Typography* typography, size_t from, size_t to, float fontSize);

/**
 * @brief 更新排版对象中的字体颜色。如果当前装饰线未设置颜色，使用该接口也会同时更新装饰线的颜色。使用该接口更新字体颜色属性后，可直接使用{@link OH_Drawing_TypographyPaint}进行绘制生效。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 表示指向排版对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param color 表示更新后的字体颜色。
 * @since 20
 * @version 1.0
 */
void OH_Drawing_TypographyUpdateFontColor(OH_Drawing_Typography* typography, uint32_t color);

/**
 * @brief 更新排版对象中的文本装饰线类型。使用该接口更新文本装饰线类型属性后，可直接使用{@link OH_Drawing_TypographyPaint}进行绘制生效。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 表示指向排版对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param decoration 表示更新后的装饰线类型，具体可见{@link OH_Drawing_TextDecoration}枚举。可通过位或操作一次设置多种装饰线类型。设置非
 *     {@link OH_Drawing_TextDecoration}枚举的装饰样式则保持原有装饰线类型。
 * @since 20
 * @version 1.0
 */
void OH_Drawing_TypographyUpdateDecoration(OH_Drawing_Typography* typography, OH_Drawing_TextDecoration decoration);

/**
 * @brief 更新排版对象中的文本装饰线的粗细缩放比例。使用该接口更新文本装饰线粗细缩放比例属性后，可直接使用{@link OH_Drawing_TypographyPaint}进行绘制生效。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 表示指向排版对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param decorationThicknessScale 表示更新后的文本装饰线的粗细缩放比例。装饰线的粗细会随着这个比例变大而变粗，如果更新的粗细缩放比例小于等于0，那么就不会绘制装饰线。
 * @since 20
 * @version 1.0
 */
void OH_Drawing_TypographyUpdateDecorationThicknessScale(OH_Drawing_Typography* typography,
    double decorationThicknessScale);

/**
 * @brief 更新排版对象中的文本装饰线样式。使用该接口更新文本装饰线样式属性后，可直接使用{@link OH_Drawing_TypographyPaint}进行绘制生效。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 表示指向排版对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param decorationStyle 表示更新后的文本装饰线样式，支持可选的装饰样式具体可见{@link OH_Drawing_TextDecorationStyle}枚举。
 * @since 20
 * @version 1.0
 */
void OH_Drawing_TypographyUpdateDecorationStyle(OH_Drawing_Typography* typography,
    OH_Drawing_TextDecorationStyle decorationStyle);

/**
 * @brief 更新排版对象中的文本装饰线颜色。
 *  使用该接口更新文本装饰线颜色属性后，可直接使用{@link OH_Drawing_TypographyPaint}进行绘制生效。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param typography 表示指向排版对象{@link OH_Drawing_Typography}的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param color 表示更新后的文本装饰线颜色。
 * @since 20
 * @version 1.0
 */
void OH_Drawing_TypographyUpdateDecorationColor(OH_Drawing_Typography* typography, uint32_t color);

/**
 * @brief 获取文本排版是否启用行样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回行样式是否启用的结果。true表示启用，false表示不启用。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyTextGetLineStyle(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取文本排版行样式字重。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回文本排版行样式字重。
 *     0字重为thin，1字重为extra-light，2字重为light，4字重为medium，5字重为semi-bold，6字重为bold，7字重为extra-bold，8字重为black，3或其它字重为normal/
 *     regular，具体可见{@link OH_Drawing_FontWeight}枚举。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontWeight OH_Drawing_TypographyTextlineStyleGetFontWeight(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取文本排版样式中支柱样式的字体样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回文本排版样式中支柱样式的字体样式。1为斜体，0或其它为非斜体，具体可见{@link OH_Drawing_FontStyle}枚举。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyle OH_Drawing_TypographyTextlineStyleGetFontStyle(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取文本排版行样式字体家族名。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param num 指向字体名称数量的指针。
 * @return 返回文本排版行样式字体家族名。
 * @since 12
 * @version 1.0
 */
char** OH_Drawing_TypographyTextlineStyleGetFontFamilies(OH_Drawing_TypographyStyle* style, size_t* num);

/**
 * @brief 释放字体类型占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontFamilies 表示指向字体类型的指针。
 * @param fontFamiliesNum 字体名称的数量。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyTextlineStyleDestroyFontFamilies(char** fontFamilies, size_t fontFamiliesNum);

/**
 * @brief 获取文本排版行样式字号。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回文本排版行样式字号。
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TypographyTextlineStyleGetFontSize(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取文本排版行样式的行高缩放系数。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回文本排版行样式的行高缩放系数。
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TypographyTextlineStyleGetHeightScale(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取字体渲染过程中计算字体块高度相关参数的方法。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回计算字体块高度相关参数的方法。true表示以字号为准计算，false表示以行距计算。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyTextlineStyleGetHeightOnly(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取文本排版行样式是否为一半行间距。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 文本排版行样式是否为一半行间距，true表示是一半行间距，false表示不是。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyTextlineStyleGetHalfLeading(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取文本排版行样式间距比例。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回文本排版行样式间距比例。
 * @since 12
 * @version 1.0
 */
double OH_Drawing_TypographyTextlineStyleGetSpacingScale(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取文本排版是否仅启用行样式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回文本排版是否仅启用行样式。true表示启用，false表示不启用。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyTextlineGetStyleOnly(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取文本对齐方式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回文本对齐方式。1为右对齐，2为居中对齐，3为两端对齐，4为与文字方向相同，5为文字方向相反，0或其它为左对齐，具体可见{@link OH_Drawing_TextAlign}枚举。
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextAlign OH_Drawing_TypographyGetTextAlign(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取指定排版样式中的文本方向。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回文本方向。0为从右到左，1为从左到右，具体可见{@link OH_Drawing_TextDirection}枚举。
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextDirection OH_Drawing_TypographyGetTextDirection(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取文本的最大行数。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向排版样式{@link OH_Drawing_TypographyStyle}的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回结果为文本最大行数。
 * @since 12
 * @version 1.0
 */
size_t OH_Drawing_TypographyGetTextMaxLines(OH_Drawing_TypographyStyle* style);

/**
 * @brief 获取指定排版样式设置的省略号文本。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @return 返回设置的省略号文本。
 * @since 12
 * @version 1.0
 */
char* OH_Drawing_TypographyGetTextEllipsis(OH_Drawing_TypographyStyle* style);

/**
 * @brief 释放省略号名称列表占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param ellipsis 表示指向省略号名称列表的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyDestroyEllipsis(char* ellipsis);

/**
 * @brief 判断排版样式是否相同，当前文本高度修饰符模式{@link OH_Drawing_TextHeightBehavior}没有被纳入比较。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param from 被比较的排版样式。
 * @param to 用于比较的排版样式。
 * @return 返回排版样式是否相同。true表示相同，false表示不相同。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_TypographyStyleEquals(OH_Drawing_TypographyStyle* from, OH_Drawing_TypographyStyle* to);

/**
 * @brief 释放文本框占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param textBox 指向文本框对象{@link OH_Drawing_TextBox}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TypographyDestroyTextBox(OH_Drawing_TextBox* textBox);

/**
 * @brief 设置字体阴影对象的参数。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param shadow 指向字体阴影对象{@link OH_Drawing_TextShadow}的指针，由{@link OH_Drawing_CreateTextShadow}获取。
 * @param color 字体阴影的颜色，例如入参为0xAABBCCDD，AA代表透明度，BB代表红色分量的值，CC代表绿色分量的值，DD代表蓝色分量的值。
 * @param offset 指向坐标点对象{@link OH_Drawing_Point}的指针，字体阴影基于当前文本的偏移位置。
 * @param blurRadius 模糊半径，浮点数，没有单位，值为0.0时表示没有模糊效果。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SetTextShadow(OH_Drawing_TextShadow* shadow, uint32_t color, OH_Drawing_Point* offset,
    double blurRadius);

/**
 * @brief 创建文本制表符对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param alignment 制表符之后的文本对齐方式。1为右对齐，2为居中对齐，0或其它为左对齐。
 * @param location 文本制表符之后的文本对齐的位置，相对于当前文本起始位置的偏移。单位为物理像素px，最小值为1.0。
 * @return 返回指向文本制表符对象的指针。如果返回空指针，表示创建失败。失败的原因可能为没有可用的内存。
 * @since 18
 * @version 1.0
 */
OH_Drawing_TextTab* OH_Drawing_CreateTextTab(OH_Drawing_TextAlign alignment, float location);

/**
 * @brief 释放文本制表符对象占据的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param tab 指向文本制表符对象的指针。
 * @since 18
 * @version 1.0
 */
void OH_Drawing_DestroyTextTab(OH_Drawing_TextTab* tab);

/**
 * @brief 获取文本制表符对象的对齐方式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param tab 指向文本制表符对象的指针。
 * @return 返回文本对齐方式。1为右对齐，2为居中对齐，0或其它为左对齐。
 * @since 18
 * @version 1.0
 */
OH_Drawing_TextAlign OH_Drawing_GetTextTabAlignment(OH_Drawing_TextTab* tab);

/**
 * @brief 获取文本制表符的位置。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param tab 指向文本制表符对象的指针。
 * @return 返回文本制表符对象的位置。
 * @since 18
 * @version 1.0
 */
float OH_Drawing_GetTextTabLocation(OH_Drawing_TextTab* tab);

/**
 * @brief 设置文本制表符对齐方式及位置。当设置了文本对齐方式或者省略号风格时制表符不生效，当制表符位置小于1.0时为替换成空格的效果。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向文本风格对象{@link OH_Drawing_TypographyStyle}的指针。
 * @param tab 指向文本制表符对象的指针。
 * @since 18
 * @version 1.0
 */
void OH_Drawing_SetTypographyTextTab(OH_Drawing_TypographyStyle* style, OH_Drawing_TextTab* tab);

/**
 * @brief 获取传入类型为对象数组{@link OH_Drawing_Array}中的对象个数。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingArray 指向对象数组{@link OH_Drawing_Array}的指针。
 * @return 数组中的对象个数。
 * @since 14
 * @version 1.0
 */
size_t OH_Drawing_GetDrawingArraySize(OH_Drawing_Array* drawingArray);

/**
 * @brief 设置文本排版时行尾空格是否参与对齐计算。
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
 * @brief 添加指定编码的文本。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler 指向{@link OH_Drawing_TypographyCreate}对象的指针，由{@link OH_Drawing_CreateTypographyHandler}获取。
 * @param text 指向文本内容的指针。
 * @param byteLength 文本的字节长度。
 * @param textEncodingType 文本的编码类型，为{@link OH_Drawing_TextEncoding}类型的枚举值。只支持TEXT_ENCODING_UTF8, TEXT_ENCODING_UTF16,
 *     TEXT_ENCODING_UTF32。
 * @since 20
 * @version 1.0
 */
void OH_Drawing_TypographyHandlerAddEncodedText(OH_Drawing_TypographyCreate* handler, const void* text,
    size_t byteLength, OH_Drawing_TextEncoding textEncodingType);

/**
 * @brief 设置文本排版时是否使能自动间距。
 * 默认不使能自动间距，一旦使能则会自动调整CJK（中文字符、日文字符、韩文字符）与西文（拉丁字母、西里尔字母、希腊字母）、CJK与数字、CJK与版权符号、版权符号与数字、版权符号与西文之间的间距。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 表示指向{@link OH_Drawing_TypographyStyle}对象的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param enableAutoSpace 设置文本排版时是否使能自动间距。true表示使能自动间距，false表示不使能自动间距，默认值为false。
 * @since 20
 */
void OH_Drawing_SetTypographyTextAutoSpace(OH_Drawing_TypographyStyle* style, bool enableAutoSpace);

/**
 * @brief 创建一个段落样式的对象副本，用于拷贝一个已有的段落样式对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向被拷贝对象{@link OH_Drawing_TypographyStyle}的指针。
 * @return 返回拷贝的{@link OH_Drawing_TypographyStyle}对象指针。如果返回空指针，表示创建失败；可能的原因是无可用内存，或者style为空指针。不再需要时，请使用
 *     {@link OH_Drawing_DestroyTypographyStyle}释放该对象指针。
 * @since 20
 * @version 1.0
 */
OH_Drawing_TypographyStyle* OH_Drawing_CopyTypographyStyle(OH_Drawing_TypographyStyle* style);

/**
 * @brief 创建一个文本样式的对象副本，用于拷贝一个已有的文本样式对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param style 指向被拷贝对象{@link OH_Drawing_TextStyle}的指针。
 * @return 返回拷贝的{@link OH_Drawing_TextStyle}对象指针。如果返回空指针，表示创建失败；可能的原因是无可用内存，或者style为空指针。不再需要时，请使用
 *     {@link OH_Drawing_DestroyTextStyle}释放该对象指针。
 * @since 20
 * @version 1.0
 */
OH_Drawing_TextStyle* OH_Drawing_CopyTextStyle(OH_Drawing_TextStyle* style);

/**
 * @brief 创建一个文本阴影的对象副本，用于拷贝一个已有的文本阴影对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param shadow 指向被拷贝对象{@link OH_Drawing_TextShadow}的指针。
 * @return 返回拷贝的{@link OH_Drawing_TextShadow}对象指针。如果返回空指针，表示创建失败；可能的原因是无可用内存，或者shadow为空指针。不再需要时，请使用
 *     {@link OH_Drawing_DestroyTextShadow}释放该对象指针。
 * @since 20
 * @version 1.0
 */
OH_Drawing_TextShadow* OH_Drawing_CopyTextShadow(OH_Drawing_TextShadow* shadow);

/**
 * @brief 释放{@link OH_Drawing_PositionAndAffinity}对象持有的内存。
 *
 * @param positionAndAffinity 指向{@link OH_Drawing_PositionAndAffinity}对象的指针。
 * @since 23
 */
void OH_Drawing_DestroyPositionAndAffinity(OH_Drawing_PositionAndAffinity* positionAndAffinity);

/**
 * @brief 获取指定字形范围对应的字符范围。
 *
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param glyphRangeStart 表示字形范围的开始位置。
 * @param glyphRangeEnd 表示字形范围的结束位置。
 * @param actualGlyphRange 返回实际的字形范围，表示指向{@link OH_Drawing_Range}的二级指针，作为出参使用。
 *     当请求的字形范围只包含复杂字形序列的一部分时，该参数返回对应的完整字形范围。
 *     例如：连字、组合表情等可能由多个原子字形组成，必须作为整体处理。
 *     如果该参数为NULL，将不返回实际字形范围，表示调用者不关心实际字形范围信息。
 *     使用后需通过{@link OH_Drawing_ReleaseRangeBuffer}接口释放该对象。
 * @param textEncodingType 表示文本编码类型{@link OH_Drawing_TextEncoding}。
 *     当前仅支持UTF-8和UTF-16编码类型。
 *     对于UTF-8编码，返回的字符范围表示字节范围。
 *     对于UTF-16编码，返回的字符范围表示UTF-16代码单元范围。
 * @return 返回表示字符范围的{@link OH_Drawing_Range}对象指针，当不再需要该对象时，请使用{@link OH_Drawing_ReleaseRangeBuffer}接口释放。
 * @since 24
 */
OH_Drawing_Range* OH_Drawing_TypographyGetCharacterRangeForGlyphRangeWithBuffer(OH_Drawing_Typography* typography,
    size_t glyphRangeStart, size_t glyphRangeEnd, OH_Drawing_Range** actualGlyphRange,
    OH_Drawing_TextEncoding textEncodingType);

/**
 * @brief 获取与指定坐标最接近的字符位置信息。
 *
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param dx 文本排版区域内的水平坐标，单位为物理像素（px）。
 *     相对于文本排版区域左上角的x偏移量，向右为正方向。
 *     支持浮点数，可取负值（表示在文本区域左侧）。
 *     坐标超出文本区域范围时，将返回最近的字符位置。可通过触摸事件或点击事件获取。
 * @param dy 文本排版区域内的垂直坐标，单位为物理像素（px）。
 *     相对于文本排版区域左上角的y偏移量，向下为正方向。
 *     支持浮点数，可取负值（表示在文本区域上方）。
 *     坐标超出文本区域范围时，将返回最近的字符位置。可通过触摸事件或点击事件获取。
 * @param textEncodingType 表示文本编码类型{@link OH_Drawing_TextEncoding}。
 *     当前仅支持UTF-8和UTF-16编码类型。
 *     对于UTF-8编码，返回的位置表示字节偏移量；对于UTF-16编码，返回的位置表示UTF-16代码单元偏移量。
 * @return 返回坐标处的字符索引位置和亲和性，返回类型为{@link OH_Drawing_PositionAndAffinity}结构体。
 *     当不再需要该对象时，请使用{@link OH_Drawing_DestroyPositionAndAffinity}接口释放。
 * @since 24
 */
OH_Drawing_PositionAndAffinity* OH_Drawing_TypographyGetCharacterPositionAtCoordinateWithBuffer(
    OH_Drawing_Typography* typography, double dx, double dy, OH_Drawing_TextEncoding textEncodingType);

/**
 * @brief 获取指定字符范围对应的字形范围。
 *
 * @param typography 指向OH_Drawing_Typography对象的指针，由{@link OH_Drawing_CreateTypography}获取。
 * @param characterRangeStart 表示字符范围的开始位置。
 * @param characterRangeEnd 表示字符范围的结束位置。
 * @param actualCharacterRange 返回实际的字符范围，表示指向{@link OH_Drawing_Range}的二级指针，作为出参使用。
 *     当请求的字符范围只包含组合字符序列的一部分时，该参数返回对应的完整字符范围。
 *     例如：基础字符加变音符号的组合字符，必须作为整体处理。
 *     如果该参数为NULL，将不返回实际字符范围，表示调用者不关心实际字符范围信息。
 *     使用后需通过{@link OH_Drawing_ReleaseRangeBuffer}接口释放该对象。
 * @param textEncodingType 表示文本编码类型{@link OH_Drawing_TextEncoding}。
 *     当前仅支持UTF-8和UTF-16编码类型。
 *     对于UTF-8编码，输入字符范围应解释为字节范围；对于UTF-16编码，输入字符范围应解释为UTF-16代码单元范围。
 * @return 返回表示字形范围的{@link OH_Drawing_Range}对象指针，当不再需要该对象时，请使用{@link OH_Drawing_ReleaseRangeBuffer}接口释放。
 * @since 24
 */
OH_Drawing_Range* OH_Drawing_TypographyGetGlyphRangeForCharacterRangeWithBuffer(OH_Drawing_Typography* typography,
    size_t characterRangeStart, size_t characterRangeEnd, OH_Drawing_Range** actualCharacterRange,
    OH_Drawing_TextEncoding textEncodingType);

/**
 * @brief 释放{@link OH_Drawing_Range}对象占用的内存。
 *
 * @param range 表示指向{@link OH_Drawing_Range}对象的指针。
 * @since 24
 */
void OH_Drawing_ReleaseRangeBuffer(OH_Drawing_Range* range);

#ifdef __cplusplus
}
#endif

/** @} */
#endif
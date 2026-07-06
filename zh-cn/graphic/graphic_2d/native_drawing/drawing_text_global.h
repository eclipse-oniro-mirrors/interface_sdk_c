
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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
 * @file drawing_text_global.h
 *
 * @brief This file declares the functions related to global text information, for example, setting the high contrast
 * mode for text rendering.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 20
 * @version 1.0
 */

/**
 * @addtogroup Drawing
 * @{
 *
 * @brief Provides the global text capability.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 *
 * @since 20
 * @version 1.0
 */

#ifndef DRAWING_TEXT_GLOBAL_H
#define DRAWING_TEXT_GLOBAL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 文本渲染高对比度模式枚举。
 *
 * @since 20
 * @version 1.0
 */
typedef enum {
    /**
     * 跟随系统设置中的高对比度文字配置。
     */
    TEXT_FOLLOW_SYSTEM_HIGH_CONTRAST,

    /**
     * 关闭APP的文本渲染高对比度配置，该模式的优先级要高于系统设置中的高对比度文字配置。
     */
    TEXT_APP_DISABLE_HIGH_CONTRAST,

    /**
     * 开启APP的文本渲染高对比度配置，该模式的优先级要高于系统设置中的高对比度文字配置。
     */
    TEXT_APP_ENABLE_HIGH_CONTRAST
} OH_Drawing_TextHighContrast;

/**
 * @brief 显示未定义字形的方式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 20
 */
typedef enum {
    /**
     * 使用字体文件中定义的默认字形（可能是空框、空白或自定义符号等）。
     */
    TEXT_NO_GLYPH_USE_DEFAULT = 0,

    /**
     * 始终使用豆腐块显示缺失的字形。
     */
    TEXT_NO_GLYPH_USE_TOFU = 1
} OH_Drawing_TextUndefinedGlyphDisplay;

/**
 * @brief 设置文本渲染高对比度模式。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param action 表示文本渲染高对比度模式，为{@link OH_Drawing_TextHighContrast}类型的枚举值。
 * @since 20
 */
void OH_Drawing_SetTextHighContrast(OH_Drawing_TextHighContrast action);

/**
 * @brief 控制未定义字形的呈现方式，影响此后渲染的所有文本。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param undefinedGlyphDisplay 表示显示未定义字形的方式，为{@link OH_Drawing_TextUndefinedGlyphDisplay}类型的枚举值。
 * @since 20
 */
void OH_Drawing_SetTextUndefinedGlyphDisplay(OH_Drawing_TextUndefinedGlyphDisplay undefinedGlyphDisplay);
#ifdef __cplusplus
}
#endif
#endif // DRAWING_TEXT_GLOBAL_H

/** @} */
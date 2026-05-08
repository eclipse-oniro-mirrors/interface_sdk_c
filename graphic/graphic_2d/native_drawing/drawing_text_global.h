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

#ifndef DRAWING_TEXT_GLOBAL_H
#define DRAWING_TEXT_GLOBAL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines an enum of the high contrast modes for text rendering.
 *
 * @since 20
 * @version 1.0
 */
typedef enum {
    /**
     * Follows the high contrast mode for text rendering in the system settings.
     */
    TEXT_FOLLOW_SYSTEM_HIGH_CONTRAST,

    /**
     * Disables the high contrast mode for text rendering in the application. This mode takes precedence over the one
     * based on system settings.
     */
    TEXT_APP_DISABLE_HIGH_CONTRAST,

    /**
     * Enables the high contrast mode for text rendering in the application. The priority of this mode is higher than
     * the mode following the system settings.
     */
    TEXT_APP_ENABLE_HIGH_CONTRAST
} OH_Drawing_TextHighContrast;

/**
 * @brief Defines an enum of the modes for displaying undefined glyphs.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 20
 */
typedef enum {
    /**
     * Uses the default glyph (which may be a blank box, space, or custom symbol) defined in the font file.
     */
    TEXT_NO_GLYPH_USE_DEFAULT = 0,

    /**
     * Always uses tofu blocks to represent absent glyphs.
     */
    TEXT_NO_GLYPH_USE_TOFU = 1
} OH_Drawing_TextUndefinedGlyphDisplay;

/**
 * @brief Sets the high contrast mode for text rendering.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param action High contrast mode for text rendering. The value is an enumerated value of the
 *     {@link OH_Drawing_TextHighContrast} type.
 * @since 20
 */
void OH_Drawing_SetTextHighContrast(OH_Drawing_TextHighContrast action);

/**
 * @brief Sets how undefined glyphs are displayed. The setting affects all subsequent text rendering.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param undefinedGlyphDisplay Mode of displaying undefined glyphs. The value is an enumerated value of the
 *     {@link OH_Drawing_TextUndefinedGlyphDisplay} type.
 * @since 20
 */
void OH_Drawing_SetTextUndefinedGlyphDisplay(OH_Drawing_TextUndefinedGlyphDisplay undefinedGlyphDisplay);
#ifdef __cplusplus
}
#endif
#endif // DRAWING_TEXT_GLOBAL_H

/** @} */
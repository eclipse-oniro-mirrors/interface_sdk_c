/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
 * @file drawing_text_declaration.h
 *
 * @brief Provides declarations of data structures related to 2D text drawing.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_TEXT_DECLARATION_H
#define C_INCLUDE_DRAWING_TEXT_DECLARATION_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines a struct used to load fonts.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_FontCollection OH_Drawing_FontCollection;

/**
 * @brief Defines a struct used to manage the typography layout and display.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_Typography OH_Drawing_Typography;

/**
 * @brief Defines a struct used to extract a single line of data from a piece of text for typography.
 *
 * @since 18
 * @version 1.0
 */
typedef struct OH_Drawing_LineTypography OH_Drawing_LineTypography;

/**
 * @brief Defines a struct used to manage text colors and decorations.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_TextStyle OH_Drawing_TextStyle;

/**
 * @brief Defines a struct used to manage the typography style, such as the text direction.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_TypographyStyle OH_Drawing_TypographyStyle;

/**
 * @brief Creates an {@link OH_Drawing_Typography} object.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_TypographyCreate OH_Drawing_TypographyCreate;

/**
 * @brief Defines a struct for a text box, which is used to receive the rectangle size, direction, and quantity.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_TextBox OH_Drawing_TextBox;

/**
 * @brief Defines a struct used to receive the position and affinity of a glyph.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_PositionAndAffinity OH_Drawing_PositionAndAffinity;

/**
 * @brief Defines a struct used to receive the start position and end position of a glyph.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Range OH_Drawing_Range;

/**
 * @brief Defines a struct used to parse system font files.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontParser OH_Drawing_FontParser;

/**
 * @brief Defines a struct used to manage text shadows.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_TextShadow OH_Drawing_TextShadow;

/**
 * @brief Defines a struct used to manage text tabs.
 *
 * @since 18
 * @version 1.0
 */
typedef struct OH_Drawing_TextTab OH_Drawing_TextTab;

/**
 * @brief Defines a struct used to manage text lines.
 *
 * @since 18
 * @version 1.0
 */
typedef struct OH_Drawing_TextLine OH_Drawing_TextLine;

/**
 * @brief Defines a struct used to manage runs.
 *
 * @since 18
 * @version 1.0
 */
typedef struct OH_Drawing_Run OH_Drawing_Run;

/**
 * @brief Defines a struct used to describe detailed information about a font, that is, the font descriptor.
 *
 * @since 22
 */
typedef struct OH_Drawing_FontFullDescriptor OH_Drawing_FontFullDescriptor;

/**
 * @brief Describes the variable axis of the font.
 *
 * @since 24
 */
typedef struct OH_Drawing_FontVariationAxis OH_Drawing_FontVariationAxis;

/**
 * @brief Describes a variable font instance and stores the preset variable font style information.
 *
 * @since 24
 */
typedef struct OH_Drawing_FontVariationInstance OH_Drawing_FontVariationInstance;
#ifdef __cplusplus
}
#endif
/** @} */
#endif
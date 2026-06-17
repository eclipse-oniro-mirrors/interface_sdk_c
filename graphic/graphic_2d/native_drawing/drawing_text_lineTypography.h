/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.. All rights reserved.
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
 * @file drawing_text_lineTypography.h
 *
 * @brief This file declares the functions related to line typography, including functions to determine the number of
 * characters that can be formatted from a given position within the text.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 18
 * @version 1.0
 */

#ifndef DRAWING_TEXT_LINETYPOGRAPHY_H
#define DRAWING_TEXT_LINETYPOGRAPHY_H

#include "drawing_text_declaration.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates a pointer to an {@link OH_Drawing_LineTypography} object, which stores the text content and style and
 * can be used to compute typography details for individual lines of text.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler Pointer to the {@link OH_Drawing_TypographyCreate} object, which is obtained from
 *     {@link OH_Drawing_CreateTypographyHandler}.
 * @return Returns the pointer to the {@link OH_Drawing_LineTypography} object created.
 * @since 18
 */
OH_Drawing_LineTypography* OH_Drawing_CreateLineTypography(OH_Drawing_TypographyCreate* handler);

/**
 * @brief Releases the memory occupied by an {@link OH_Drawing_LineTypography} object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lineTypography Pointer to the {@link OH_Drawing_LineTypography} object, which is obtained from
 *     {@link OH_Drawing_CreateLineTypography}.
 * @since 18
 */
void OH_Drawing_DestroyLineTypography(OH_Drawing_LineTypography* lineTypography);

/**
 * @brief Obtains the number of characters that can fit in the layout from the specified position within a limited
 * layout width.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lineTypography Pointer to the {@link OH_Drawing_LineTypography} object, which is obtained from
 *     {@link OH_Drawing_CreateLineTypography}.
 * @param startIndex Start position (inclusive) for layout calculation. The value must be an integer in the range [0,
 *     total number of text characters].
 * @param width Layout width. The value is a floating point number greater than 0, in px.
 * @return Returns the number of characters.
 * @since 18
 */
size_t OH_Drawing_LineTypographyGetLineBreak(OH_Drawing_LineTypography* lineTypography,
                                             size_t startIndex, double width);

/**
 * @brief Creates a pointer to an {@link OH_Drawing_TextLine} object based on the text content in a specified range.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lineTypography Pointer to the {@link OH_Drawing_LineTypography} object, which is obtained from
 *     {@link OH_Drawing_CreateLineTypography}.
 * @param startIndex Start position for layout calculation. The value is an integer in the range [0, total number of
 *     text characters).
 * @param count Number of characters from the specified start position. The value is an integer in the range [0, total
 *     number of text characters). The sum of **startIndex** and **count** cannot be greater than the total number of
 *     text characters.
 *     You can use {@link OH_Drawing_LineTypographyGetLineBreak} to obtain the number of characters that can fit in the
 *     layout. If the value is set to **0**, a null pointer is returned.
 * @return Pointer to the {@link OH_Drawing_TextLine} object.
 * @since 18
 */
OH_Drawing_TextLine* OH_Drawing_LineTypographyCreateLine(OH_Drawing_LineTypography* lineTypography,
                                                         size_t startIndex, size_t count);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
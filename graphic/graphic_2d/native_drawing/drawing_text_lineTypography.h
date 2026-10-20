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
 * @brief Provides APIs related to typography lines, such as obtaining the number of characters that can be typeset
 * starting from a specified position.
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
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates a pointer to a typography line object {@link OH_Drawing_LineTypography}. The typography line object
 * serves as a container for storing text content and styles, and can be used to calculate single-line typography
 * information.
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
 * @param startIndex Start position (inclusive) for calculating the typography. The value is an integer in the range [0,
 *     total count of text characters).
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
 * @param count Number of characters to be typeset from the specified typography start position. The value is an
 *     integer in the range [0, total count of text characters), and the sum of startIndex and count cannot exceed the
 *     total count of text characters.
 *     <br>You can first use {@link OH_Drawing_LineTypographyGetLineBreak} to obtain a reasonable total count of
 *     characters that can be typeset. If this value is set to 0, the content from startIndex to the end of the text is
 *     returned.
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
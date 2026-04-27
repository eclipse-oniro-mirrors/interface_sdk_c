/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
 * @file drawing_typeface.h
 *
 * @brief This file declares the functions related to the typeface in the drawing module.
 * Different platforms have their own default typefaces. You can also parse the .ttf file to obtain the typefaces
 * specified by the third party, such as SimSun and SimHei.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_TYPEFACE_H
#define C_INCLUDE_DRAWING_TYPEFACE_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates a default **OH_Drawing_Typeface** object.
 *
 * @return Returns the pointer to the **OH_Drawing_Typeface** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_TypefaceCreateDefault(void);

/**
 * @brief Creates an **OH_Drawing_Typeface** object through a file.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the file path.
 * @param index File index.
 * @return Returns a pointer to the created {@link OH_Drawing_Typeface} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_TypefaceCreateFromFile(const char* path, int index);

/**
 * @brief Creates an **OH_Drawing_Typeface** object with font arguments through a file.
 * If the **OH_Drawing_Typeface** object does not support the variation described in the font arguments, this function
 * creates an **OH_Drawing_Typeface** object with the default font arguments.
 * In this case, this function provides the same capability as {@link OH_Drawing_TypefaceCreateFromFile}.
 *
 * @param path Pointer to the file path.
 * @param fontArguments Pointer to an {@link OH_Drawing_FontArguments} object.
 * @return Returns a pointer to the created {@link OH_Drawing_Typeface} object.
 * If a null pointer is returned, the creation fails. Possible causes are that no memory is available, the passed-in **
 * path** or **fontArguments** is NULL, or the path is invalid.
 * @since 13
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_TypefaceCreateFromFileWithArguments(const char* path,
    const OH_Drawing_FontArguments* fontArguments);

/**
 * @brief Creates an **OH_Drawing_Typeface** object with font arguments based on an existing **OH_Drawing_Typeface**
 * object.
 *
 * @param current Pointer to the {@link OH_Drawing_Typeface} object.
 * @param fontArguments Pointer to an {@link OH_Drawing_FontArguments} object.
 * @return Returns a pointer to the created {@link OH_Drawing_Typeface} object.
 * If a null pointer is returned, the creation fails. Possible causes are that no memory is available, the passed-in **
 * path** or **fontArguments** is NULL, or the existing **OH_Drawing_FontArguments** object does not support the
 * variation described in the font arguments.
 * @since 13
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_TypefaceCreateFromCurrent(const OH_Drawing_Typeface* current,
    const OH_Drawing_FontArguments* fontArguments);

/**
 * @brief Creates an **OH_Drawing_Typeface** object through a memory stream. If the memory stream is an invalid font
 * file, a null pointer is returned. After the memory stream is passed in, the ownership is transferred and you cannot
 * release it.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **memoryStream** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param memoryStream Pointer to an {@link OH_Drawing_MemoryStream} object.
 * @param index Index of the memory stream.
 * @return Returns a pointer to the created {@link OH_Drawing_Typeface} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_TypefaceCreateFromStream(OH_Drawing_MemoryStream* memoryStream, int32_t index);

/**
 * @brief Destroys an **OH_Drawing_Typeface** object and reclaims the memory occupied by the object.
 *
 * @param typeface Pointer to an **OH_Drawing_Typeface** object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_TypefaceDestroy(OH_Drawing_Typeface* typeface);

/**
 * @brief Creates an **OH_Drawing_FontArguments** object. The font arguments are used to create an **
 * OH_Drawing_Typeface** object with custom attributes.
 *
 * @return Returns the pointer to the **OH_Drawing_FontArguments** object created.
 * @since 13
 * @version 1.0
 */
OH_Drawing_FontArguments* OH_Drawing_FontArgumentsCreate(void);

/**
 * @brief Adds a variation to an **OH_Drawing_FontArguments** object.
 *
 * @param fontArguments Pointer to an {@link OH_Drawing_FontArguments} object.
 * @param axis Pointer to the label of the variation. The value must contain four ASCII characters. The supported
 * labels depend on the loaded font file. For example, **'wght'** is the font weight label.
 * @param value Value of the variation label.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **fontArguments** or **axis** is NULL or the length of **axis** is
 * not 4.
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontArgumentsAddVariation(OH_Drawing_FontArguments* fontArguments,
    const char* axis, float value);

/**
 * @brief Destroys an **OH_Drawing_FontArguments** object.
 *
 * @param fontArguments Pointer to an {@link OH_Drawing_FontArguments} object.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **fontArguments** is NULL.
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontArgumentsDestroy(OH_Drawing_FontArguments* fontArguments);

/**
 * @brief Checks whether the typeface is bold.
 *
 * @param typeface Pointer to the {@link OH_Drawing_Typeface} object.
 * @param isBold Whether the typeface is bold. It is used as an output parameter. **true** if the typeface is bold; **
 * false** otherwise.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **typeface** or **isBold** is a null pointer.
 * @since 23
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_TypefaceIsBold(const OH_Drawing_Typeface* typeface, bool* isBold);

/**
 * @brief Checks whether the typeface is italic.
 *
 * @param typeface Pointer to the {@link OH_Drawing_Typeface} object.
 * @param isItalic Whether the typeface is italic. It is used as an output parameter. **true** if the typeface is
 * italic; **false** otherwise.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **typeface** or **isItalic** is a null pointer.
 * @since 23
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_TypefaceIsItalic(const OH_Drawing_Typeface* typeface, bool* isItalic);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
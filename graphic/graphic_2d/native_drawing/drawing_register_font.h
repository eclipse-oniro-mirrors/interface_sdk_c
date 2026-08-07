/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @since 11
 * @version 1.0
 */

/**
 * @file drawing_register_font.h
 *
 * @brief Defines functions related to the font manager in the drawing module, providing capabilities for registering
 * and unregistering custom fonts as well as detecting font formats, and supporting multiple font file formats such as
 * ttf, otf, ttc, and otc.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_REGISTER_FONT_H
#define C_INCLUDE_DRAWING_REGISTER_FONT_H

#include "drawing_text_declaration.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Registers a custom font with the font manager. The supported font file formats are .ttf and .otf.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection Indicates the pointer to an <b>OH_Drawing_FontCollection</b> object.
 * @param fontFamily Name of the font to register.
 * @param familySrc Path to the font file to register.
 * @return Result code.
 *     <br>Returns 0 if the operation is successful.
 *     <br>Returns 1 if the file does not exist.
 *     <br>Returns 2 if opening the file fails.
 *     <br>Returns 3 if reading the file fails.
 *     <br>Returns 4 if seeking the file fails.
 *     <br>Returns 5 if obtaining the file size fails.
 *     <br>Returns 8 if fontCollection is NULL.
 *     <br>Returns 9 if the file is corrupted.
 * @since 11
 * @version 1.0
 */
uint32_t OH_Drawing_RegisterFont(OH_Drawing_FontCollection* fontCollection, const char* fontFamily,
    const char* familySrc);

/**
 * @brief Registers a font buffer in the font manager, supporting data read from ttf and otf files.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection Indicates the pointer to an <b>OH_Drawing_FontCollection</b> object.
 * @param fontFamily Font name of the font to register.
 * @param fontBuffer Buffer of the font file to register.
 * @param length Length of the font file to register. Must match the actual length of fontBuffer.
 * @return Result code.
 *     <br>Returns 0 if the operation is successful.
 *     <br>Returns 6 if fontBuffer is NULL.
 *     <br>Returns 7 if the buffer size is zero.
 *     <br>Returns 8 if fontCollection is NULL.
 * @since 11
 * @version 1.0
 */
uint32_t OH_Drawing_RegisterFontBuffer(OH_Drawing_FontCollection* fontCollection, const char* fontFamily,
    uint8_t* fontBuffer, size_t length);

/**
 * @brief Registers a custom font using a ttc/otc file, with the index parameter specifying the font index to register.
 *
 * @param fontCollection Pointer to an {@link OH_Drawing_FontCollection} object.
 * @param fontFamily Family name of the font to register.
 * @param familySrc Path of the font file to register.
 * @param index Index of the font in the ttc/otc file. The value ranges from 0 to the total number of fonts minus 1.
 *     For non-ttc/otc files, set this parameter to 0.
 * @return Result code. 0 indicates function execution is successful, 1 indicates file does not exist, 2 indicates file
 *     opening failure, 3 indicates file reading failure, 4 indicates file seeking failure, 5 indicates size obtaining
 *     failure, 8 indicates fontCollection is NULL, and 9 indicates file corruption.
 * @since 23
 */
uint32_t OH_Drawing_RegisterFontByIndex(OH_Drawing_FontCollection* fontCollection,
    const char* fontFamily, const char* familySrc, uint32_t index);

/**
 * @brief Registers a font using the font buffer of a TTC/OTC file.
 *
 * @param fontCollection Pointer to an {@link OH_Drawing_FontCollection} object.
 * @param fontFamily Family name of the font to register.
 * @param fontBuffer Font buffer of the font file to register.
 * @param length Length of the byte stream data, which must match the actual length of fontBuffer.
 * @param index Index of the font in the ttc/otc file. The value ranges from 0 to the number of fonts minus 1. For
 *     files in non-ttc/otc formats, set this parameter to 0.
 * @return Result code.
 *     <br>Returns 0 the function is executed successfully.
 *     <br>Returns 6 if fontBuffer is NULL.
 *     <br>Returns 7 if the buffer size is zero.
 *     <br>Returns 8 if fontCollection is NULL.
 *     <br>Returns 9 if the file is corrupted.
 * @since 23
 */
uint32_t OH_Drawing_RegisterFontBufferByIndex(OH_Drawing_FontCollection* fontCollection,
    const char* fontFamily, uint8_t* fontBuffer, size_t length, uint32_t index);

/**
 * @brief Unregisters a custom font by font name.
 * <br>Unregistering a font that is currently in use may lead to text rendering exceptions (such as garbled characters
 * or missing glyphs).
 * <br>All typesetting objects that use the unregistered font name should be destroyed and recreated.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection Pointer to an {@link OH_Drawing_FontCollection} object.
 * @param fontFamily Font name to unregister.
 * @return Result code. Returns 0 if the function is executed successfully, 8 if the input parameter is invalid, and 1
 *     if the unregistration fails.
 * @since 20
 */
uint32_t OH_Drawing_UnregisterFont(OH_Drawing_FontCollection* fontCollection, const char* fontFamily);

/**
 * @brief Checks whether the system supports the font format of the specified path.
 *
 * @param path Absolute path of the font file.
 * @return Returns **true** if the font is supported; returns **false** otherwise.
 * @since 23
 */
bool OH_Drawing_IsFontSupportedFromPath(const char* path);

/**
 * @brief Checks whether the system supports the font format specified in the buffer.
 *
 * @param data Pointer to the buffer that contains the font data.
 * @param dataLength Size of the font data, in bytes. Must match the actual length of data.
 * @return Returns **true** if the font is supported; returns **false** otherwise.
 * @since 23
 */
bool OH_Drawing_IsFontSupportedFromBuffer(uint8_t* data, size_t dataLength);
#ifdef __cplusplus
}
#endif
/** @} */
#endif
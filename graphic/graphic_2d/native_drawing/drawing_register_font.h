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
 * @brief This file declares the functions related to the font manager in the drawing module.
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
 * @param OH_Drawing_FontCollection Indicates the pointer to an <b>OH_Drawing_FontCollection</b> object.
 * @param fontFamily Pointer to the family name of the font to register.
 * @param familySrc Pointer to the path of the font file to register.
 * @return Returns **0** if the font is registered; returns **1** if the file does not exist; returns **2** if opening
 *     the file fails; returns **3** if reading the file fails; returns **4** if the file is not found; returns **5**
 *     if the file size is not obtained; returns **9** if the file is damaged.
 * @since 11
 * @version 1.0
 */
uint32_t OH_Drawing_RegisterFont(OH_Drawing_FontCollection*, const char* fontFamily, const char* familySrc);

/**
 * @brief Registers a font buffer with the font manager.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param OH_Drawing_FontCollection Indicates the pointer to an <b>OH_Drawing_FontCollection</b> object.
 * @param fontFamily Pointer to the family name of the font to register.
 * @param fontBuffer Pointer to the buffer of the font file.
 * @param length Length of the font file.
 * @return Returns **0** if the font is registered; returns **6** if the buffer size is zero; returns **7** if the font
 *     set is empty; returns **9** if the file is damaged.
 * @since 11
 * @version 1.0
 */
uint32_t OH_Drawing_RegisterFontBuffer(OH_Drawing_FontCollection*, const char* fontFamily, uint8_t* fontBuffer,
    size_t length);

/**
 * @brief Registers a custom font using a TTC/OTC file.
 *
 * @param fontCollection Pointer to an {@link OH_Drawing_FontCollection} object.
 * @param fontFamily Family name of the font to register.
 * @param familySrc Path of the font file to register.
 * @param index Index of the font in the TTC/OTC file. Set this parameter to **0** if the file is not in TTC/OTC format.
 * @return Returns the execution result. **0**: success; **1**: file does not exist; **2**: failed to open the file; **
 *     3**: failed to read the file; **4**: failed to find the file; **5**: failed to obtain the size; **8**: **
 *     fontCollection** is null; **9**: file is corrupted.
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
 * @param length Font buffer data length.
 * @param index Index of the font in the TTC/OTC file. Set this parameter to **0** if the file is not in TTC/OTC format.
 * @return Returns the execution result. **0**: success; **6**: the font buffer pointer is null; **7**: the font buffer
 *     data length is zero; **8**: **fontCollection** is null; **9**: file is corrupted.
 * @since 23
 */
uint32_t OH_Drawing_RegisterFontBufferByIndex(OH_Drawing_FontCollection* fontCollection,
    const char* fontFamily, uint8_t* fontBuffer, size_t length, uint32_t index);

/**
 * @brief Unregisters a custom font by font family name.Unregistering a font that is currently in use may lead to text
 * rendering exceptions (such as garbled characters or missing glyphs).All typography objects using the unregistered
 * font family should be destroyed and re-created.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection Pointer to an {@link OH_Drawing_FontCollection} object.
 * @param fontFamily Name of the font family to be unregistered.
 * @return Returns the result code. **0**: success; **8**: invalid input parameter; **1**: failure.
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
 * @param dataLength Size of the font data, in bytes.
 * @return Returns **true** if the font is supported; returns **false** otherwise.
 * @since 23
 */
bool OH_Drawing_IsFontSupportedFromBuffer(uint8_t* data, size_t dataLength);
#ifdef __cplusplus
}
#endif
/** @} */
#endif
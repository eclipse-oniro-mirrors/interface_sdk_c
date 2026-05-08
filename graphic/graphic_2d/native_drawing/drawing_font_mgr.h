/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @brief Provides functions such as 2D graphics rendering, text drawing, and image display.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 *
 * @since 12
 * @version 1.0
 */

/**
 * @file drawing_font_mgr.h
 *
 * @brief This file declares the functions related to font management in the drawing module. The functions can be used
 * to load fonts and match available fonts in the system.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_FONT_MGR_H
#define C_INCLUDE_DRAWING_FONT_MGR_H

#include "drawing_types.h"
#include "drawing_text_typography.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an **OH_Drawing_FontMgr** object, which can be used only to manage system fonts.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return Returns the pointer to the <b>OH_Drawing_FontMgr</b> object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontMgr* OH_Drawing_FontMgrCreate(void);

/**
 * @brief Destroys an **OH_Drawing_FontMgr** object and reclaims the memory occupied by the object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr Pointer to an {@link OH_Drawing_FontMgr} object, which is obtained from
 *     {@link OH_Drawing_FontMgrCreate}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontMgrDestroy(OH_Drawing_FontMgr* drawingFontMgr);

/**
 * @brief Obtains the number of font families.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr Pointer to an {@link OH_Drawing_FontMgr} object, which is obtained from
 *     {@link OH_Drawing_FontMgrCreate}.
 * @return Returns the count of font families.
 * @since 12
 * @version 1.0
 */
int OH_Drawing_FontMgrGetFamilyCount(OH_Drawing_FontMgr* drawingFontMgr);

/**
 * @brief Obtains the font family name based on an index.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr Pointer to an {@link OH_Drawing_FontMgr} object, which is obtained from
 *     {@link OH_Drawing_FontMgrCreate}.
 * @param index Index of the font family name.
 * @return Returns the font family name corresponding to the index value.
 * @since 12
 * @version 1.0
 */
char* OH_Drawing_FontMgrGetFamilyName(OH_Drawing_FontMgr* drawingFontMgr, int index);

/**
 * @brief Reclaims the memory occupied by a font family name.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param familyName Pointer to a font family name.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontMgrDestroyFamilyName(char* familyName);

/**
 * @brief Creates a font style set from an **OH_Drawing_FontMgr** object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr Pointer to an {@link OH_Drawing_FontMgr} object, which is obtained from
 *     {@link OH_Drawing_FontMgrCreate}.
 * @param index Index of the font style set.
 * @return Returns the pointer to the <b>OH_Drawing_FontStyleSet</b> object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyleSet* OH_Drawing_FontMgrCreateFontStyleSet(OH_Drawing_FontMgr* drawingFontMgr, int index);

/**
 * @brief Reclaims the memory occupied by a font style set.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontStyleSet Pointer to an {@link OH_Drawing_FontStyleSet} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontMgrDestroyFontStyleSet(OH_Drawing_FontStyleSet* drawingFontStyleSet);

/**
 * @brief Obtains a font style set based on a font family name.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr Pointer to an {@link OH_Drawing_FontMgr} object, which is obtained from
 *     {@link OH_Drawing_FontMgrCreate}.
 * @param familyName Pointer to a font family name.
 * @return Returns the pointer to the <b>OH_Drawing_FontStyleSet</b> object matched.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyleSet* OH_Drawing_FontMgrMatchFamily(OH_Drawing_FontMgr* drawingFontMgr, const char* familyName);

/**
 * @brief Obtains a typeface based on the font style information and font family name.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr Pointer to an {@link OH_Drawing_FontMgr} object, which is obtained from
 *     {@link OH_Drawing_FontMgrCreate}.
 * @param familyName Pointer to a font family name.
 * @param fontStyle Font style, including the font weight, width, and slant.
 * @return Returns the pointer to the <b>OH_Drawing_Typeface</b> object matched.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_FontMgrMatchFamilyStyle(OH_Drawing_FontMgr* drawingFontMgr,
    const char* familyName, OH_Drawing_FontStyleStruct fontStyle);

/**
 * @brief Obtains a typeface for the specified character. A null pointer is returned only when no typeface
 * corresponding to the input UTF-8 character is found in the **OH_Drawing_FontMgr** object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr Pointer to an {@link OH_Drawing_FontMgr} object, which is obtained from
 *     {@link OH_Drawing_FontMgrCreate}.
 * @param familyName Pointer to a font family name.
 * @param fontStyle Font style, including the font weight, width, and slant.
 * @param bcp47 Pointer to the character language code array, which is a combination of ISO 639, 15924, and 3166-1
 *     language codes.
 * @param bcp47Count Size of the character language code array.
 * @param character UTF8 character used for matching.
 * @return Returns the pointer to the <b>OH_Drawing_Typeface</b> object matched.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_FontMgrMatchFamilyStyleCharacter(OH_Drawing_FontMgr* drawingFontMgr,
    const char* familyName, OH_Drawing_FontStyleStruct fontStyle,
    const char* bcp47[], int bcp47Count, int32_t character);

/**
 * @brief Creates a typeface for the specified index.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontStyleSet Pointer to an {@link OH_Drawing_FontStyleSet} object.
 * @param index Index of the typeface.
 * @return If successful, return a pointer to <b>OH_Drawing_Typeface</b> object; if failed, return nullptr.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_FontStyleSetCreateTypeface(OH_Drawing_FontStyleSet* fontStyleSet, int index);

/**
 * @brief Obtains the font style. Call {@link OH_Drawing_FontStyleSetFreeStyleName} to release **styleName** when it is
 * no longer needed, freeing up the allocated memory.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontStyleSet Pointer to an {@link OH_Drawing_FontStyleSet} object.
 * @param index Index of the font style.
 * @param styleName String specifying the font style name. Call {@link OH_Drawing_FontStyleSetFreeStyleName} to release
 *     it when it is no longer needed, freeing up the allocated memory.
 * @return Return the <b>OH_Drawing_FontStyleStruct<b> structure.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyleStruct OH_Drawing_FontStyleSetGetStyle(OH_Drawing_FontStyleSet* fontStyleSet, int32_t index,
    char** styleName);

/**
 * @brief Frees the memory occupied by a font style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param styleName Double pointer to the string that specifies the font style name.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontStyleSetFreeStyleName(char** styleName);

/**
 * @brief Obtains the typeface closest to the font style.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontStyleSet Pointer to an {@link OH_Drawing_FontStyleSet} object.
 * @param fontStyleStruct Font style, including the font weight, width, and slant.
 * @return A pointer to matched <b>OH_Drawing_Typeface</b>.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_FontStyleSetMatchStyle(OH_Drawing_FontStyleSet* fontStyleSet,
    OH_Drawing_FontStyleStruct fontStyleStruct);

/**
 * @brief Obtains the number of fonts in the font style set.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontStyleSet Pointer to an {@link OH_Drawing_FontStyleSet} object.
 * @return The count of typeface in this font style set.
 * @since 12
 * @version 1.0
 */
int OH_Drawing_FontStyleSetCount(OH_Drawing_FontStyleSet* fontStyleSet);
#ifdef __cplusplus
}
#endif
/** @} */
#endif
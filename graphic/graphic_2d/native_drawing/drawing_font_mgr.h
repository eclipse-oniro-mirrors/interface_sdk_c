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
 * @brief Declares functions related to system font management, used to match and obtain fonts preset in the system.
 * OH_Drawing_FontMgr (font manager) manages the font families preset in the system. Each font family corresponds to a
 * font style set {@link OH_Drawing_FontStyleSet}, and each style set contains multiple typeface objects
 * {@link OH_Drawing_Typeface}.
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
 * @return Pointer to the {@link OH_Drawing_FontMgr} object created.
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
 * @return Returns the number of font families.
 * @since 12
 * @version 1.0
 */
int OH_Drawing_FontMgrGetFamilyCount(OH_Drawing_FontMgr* drawingFontMgr);

/**
 * @brief Obtains the font family name based on an index. When the returned name is no longer needed, use
 * {@link OH_Drawing_FontMgrDestroyFamilyName} to release the memory occupied by the name.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr Pointer to an {@link OH_Drawing_FontMgr} object, which is obtained from
 *     {@link OH_Drawing_FontMgrCreate}.
 * @param index Index used to obtain the corresponding font family name. The value range is [0,
 *     OH_Drawing_FontMgrGetFamilyCount() - 1].
 * @return Font family name corresponding to the index. When no longer needed, use
 *     {@link OH_Drawing_FontMgrDestroyFamilyName} to release the memory occupied by the name.
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
 * @brief Creates a font style set object from a font manager object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr Pointer to an {@link OH_Drawing_FontMgr} object, which is obtained from
 *     {@link OH_Drawing_FontMgrCreate}.
 * @param index Index value used to obtain the font style set object from the font manager object. Value range: [0,
 *     OH_Drawing_FontMgrGetFamilyCount() - 1].
 * @return Returns a pointer to the {@link OH_Drawing_FontStyleSet} object created.
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
 * @brief Obtains a font style set object based on a specified font family name. When the object is no longer needed,
 * use {@link OH_Drawing_FontMgrDestroyFontStyleSet} to release it.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr Pointer to an {@link OH_Drawing_FontMgr} object, which is obtained from
 *     {@link OH_Drawing_FontMgrCreate}.
 * @param familyName Pointer to a font family name.
 * @return Pointer to the corresponding font style set object {@link OH_Drawing_FontStyleSet}. When no longer needed,
 *     use {@link OH_Drawing_FontMgrDestroyFontStyleSet} to release the object pointer. <br>NULL is returned if
 *     matching fails.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyleSet* OH_Drawing_FontMgrMatchFamily(OH_Drawing_FontMgr* drawingFontMgr, const char* familyName);

/**
 * @brief Obtains a typeface object based on the specified font style information and font family name. When the object
 * is no longer needed, use {@link OH_Drawing_TypefaceDestroy} to release it.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr Pointer to an {@link OH_Drawing_FontMgr} object, which is obtained from
 *     {@link OH_Drawing_FontMgrCreate}.
 * @param familyName Pointer to a font family name.
 * @param fontStyle Font style, including the font weight, width, and slant.
 * @return Pointer to the {@link OH_Drawing_Typeface} object corresponding to the font style. Use
 *     {@link OH_Drawing_TypefaceDestroy} to release the pointer when it is no longer needed. <br>NULL is returned if
 *     the match fails.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_FontMgrMatchFamilyStyle(OH_Drawing_FontMgr* drawingFontMgr,
    const char* familyName, OH_Drawing_FontStyleStruct fontStyle);

/**
 * @brief Obtains a typeface for the specified character. A null pointer is returned only when no typeface
 * corresponding to the input UTF-8 character is found in the font management object. When the object is no longer
 * needed, use {@link OH_Drawing_TypefaceDestroy} to release it.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr Pointer to an {@link OH_Drawing_FontMgr} object, which is obtained from
 *     {@link OH_Drawing_FontMgrCreate}.
 * @param familyName Pointer to a font family name.
 * @param fontStyle Font style, including the font weight, width, and slant.
 * @param bcp47 Array of BCP47 language codes, which is a combination of ISO 639, 15924, and 3166-1 language codes.
 * @param bcp47Count Size of the bcp47 array, which must match the actual number of elements in the bcp47 array.
 * @param character UTF-8 character used for matching.
 * @return Pointer to the corresponding {@link OH_Drawing_Typeface} typeface object, or NULL if no typeface is matched.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_FontMgrMatchFamilyStyleCharacter(OH_Drawing_FontMgr* drawingFontMgr,
    const char* familyName, OH_Drawing_FontStyleStruct fontStyle,
    const char* bcp47[], int bcp47Count, int32_t character);

/**
 * @brief Gets a typeface for the specified index. When the object is no longer needed, use
 * {@link OH_Drawing_TypefaceDestroy} to release it.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontStyleSet Pointer to an {@link OH_Drawing_FontStyleSet} object.
 * @param index Index of the specified typeface object. The value range is [0, OH_Drawing_FontStyleSetCount() - 1].
 * @return Typeface object if successful; NULL otherwise.
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
 * @param index Index of the specified font style. The value range is [0, OH_Drawing_FontStyleSetCount() - 1].
 * @param styleName String specifying the font style name. Call {@link OH_Drawing_FontStyleSetFreeStyleName} to release
 *     it when it is no longer needed, freeing up the allocated memory.
 * @return Returns the font style.
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
 * @brief Obtains the typeface closest to the font style (font weight, font width, and slant). When the object is no
 * longer needed, use {@link OH_Drawing_TypefaceDestroy} to release it.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontStyleSet Pointer to an {@link OH_Drawing_FontStyleSet} object.
 * @param fontStyleStruct Font style, including the font weight, width, and slant.
 * @return Pointer to the corresponding typeface object {@link OH_Drawing_Typeface}, or NULL if matching fails.
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
 * @return Returns the number of fonts.
 * @since 12
 * @version 1.0
 */
int OH_Drawing_FontStyleSetCount(OH_Drawing_FontStyleSet* fontStyleSet);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
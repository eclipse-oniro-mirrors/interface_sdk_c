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
 * @file drawing_font_collection.h
 *
 * @brief This file declares the functions related to the font collection in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_FONT_COLLECTION_H
#define C_INCLUDE_DRAWING_FONT_COLLECTION_H

#include "drawing_text_declaration.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Creates an {@link OH_Drawing_FontCollection} object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return Returns the pointer to the <b>OH_Drawing_FontCollection</b> object created.
 * @since 8
 * @version 1.0
 */
OH_Drawing_FontCollection* OH_Drawing_CreateFontCollection(void);

/**
 * @brief Destroys an **OH_Drawing_FontCollection** object and reclaims the memory occupied by the object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection Pointer to an **OH_Drawing_FontCollection** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_DestroyFontCollection(OH_Drawing_FontCollection* fontCollection);

/**
 * @brief Disables the system fonts.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection Pointer to an {@link OH_Drawing_FontCollection} object.
 * @since 12
 * @version 1.0
 * @deprecated since 18
 * @useinstead OH_Drawing_DisableFontCollectionSystemFont
 */
void OH_Drawing_DisableFontCollectionFallback(OH_Drawing_FontCollection* fontCollection);

/**
 * @brief Disables the system fonts.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection Pointer to an {@link OH_Drawing_FontCollection} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DisableFontCollectionSystemFont(OH_Drawing_FontCollection* fontCollection);

/**
 * @brief Creates a shareable {@link OH_Drawing_FontCollection} object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return Returns the pointer to the <b>OH_Drawing_FontCollection</b> object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontCollection* OH_Drawing_CreateSharedFontCollection(void);

/**
 * @brief Clears the font cache. (The font cache has a memory limit and a clearing mechanism. It occupies limited
 * memory. You are not advised to clear it unless otherwise required.)
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection Pointer to an {@link OH_Drawing_FontCollection} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ClearFontCaches(OH_Drawing_FontCollection* fontCollection);

/**
 * @brief Obtains the global {@link OH_Drawing_FontCollection} object, which can be used to sense the theme font
 * information. Do not release the object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return Return the pointer to the <b>OH_Drawing_FontCollection</b> global instance.
 * @since 14
 * @version 1.0
 */
OH_Drawing_FontCollection* OH_Drawing_GetFontCollectionGlobalInstance(void);
#ifdef __cplusplus
}
#endif
/** @} */
#endif
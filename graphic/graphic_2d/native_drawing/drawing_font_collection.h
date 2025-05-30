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
 * @brief Declares functions related to <b>FontCollection</b> in the drawing module.
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
 * @brief Creates an <b>OH_Drawing_FontCollection</b> object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return Returns the pointer to the <b>OH_Drawing_FontCollection</b> object created.
 * @since 8
 * @version 1.0
 */
OH_Drawing_FontCollection* OH_Drawing_CreateFontCollection(void);

/**
 * @brief Releases the memory occupied by an <b>OH_Drawing_FontCollection</b> object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection Indicates the pointer to an <b>OH_Drawing_FontCollection</b> object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_DestroyFontCollection(OH_Drawing_FontCollection* fontCollection);

/**
 * @brief Disable the font collection fallback.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection Indicates the pointer to an <b>OH_Drawing_FontCollection</b> object.
 * @since 12
 * @version 1.0
 * @deprecated since 18
 * @useinstead OH_Drawing_DisableFontCollectionSystemFont
 */
void OH_Drawing_DisableFontCollectionFallback(OH_Drawing_FontCollection* fontCollection);

/**
 * @brief Disable the font collection systemfont.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection Indicates the pointer to an <b>OH_Drawing_FontCollection</b> object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DisableFontCollectionSystemFont(OH_Drawing_FontCollection* fontCollection);

/**
 * @brief Creates an <b>OH_Drawing_FontCollection</b> object with shared usage between
 * <b>OH_Drawing_TypographyCreate</b>.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return Returns the pointer to the <b>OH_Drawing_FontCollection</b> object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontCollection* OH_Drawing_CreateSharedFontCollection(void);

/**
 * @brief Clear font caches.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection Indicates the pointer to an <b>OH_Drawing_FontCollection</b> object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ClearFontCaches(OH_Drawing_FontCollection* fontCollection);

/**
 * @brief Get the <b>OH_Drawing_FontCollection</b> global instance.
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
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
 * @brief 定义绘制模块中与字体集相关的函数，用于管理文本排版所需的字体资源，支持创建独立的或可共享的字体集对象，满足不同场景下的文本排版需求。通过字体集对象，可实现自定义字体加载、系统字体管理、字体缓存清理等功能。
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
 * @brief 创建字体集对象{@link OH_Drawing_FontCollection}。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return 指向创建的字体集对象的指针。该函数创建的字体集指针对象OH_Drawing_FontCollection只能被一个{@link OH_Drawing_TypographyCreate}对象使用，
 *     不支持多个OH_Drawing_TypographyCreate对象共享使用。如需在多个OH_Drawing_TypographyCreate对象间共享同一个OH_Drawing_FontCollection，请使用
 *     {@link OH_Drawing_CreateSharedFontCollection}函数创建OH_Drawing_FontCollection对象。
 * @since 8
 * @version 1.0
 * @release OH_Drawing_DestroyFontCollection {return}
 * @deprecated since 26.1.0
 * @useinstead OH_Drawing_CreateSharedFontCollection
 */
OH_Drawing_FontCollection* OH_Drawing_CreateFontCollection(void);

/**
 * @brief 释放被字体集对象占据的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection 指向字体集对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_DestroyFontCollection(OH_Drawing_FontCollection* fontCollection);

/**
 * @brief 禁用系统字体。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection 指向字体集对象{@link OH_Drawing_FontCollection}的指针。
 * @since 12
 * @version 1.0
 * @deprecated since 18
 * @useinstead OH_Drawing_DisableFontCollectionSystemFont
 */
void OH_Drawing_DisableFontCollectionFallback(OH_Drawing_FontCollection* fontCollection);

/**
 * @brief 禁用系统字体。禁用后，该字体集对象仅能使用已注册的自定义字体进行文本渲染。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection 指向需禁用系统字体的字体集对象{@link OH_Drawing_FontCollection}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_DisableFontCollectionSystemFont(OH_Drawing_FontCollection* fontCollection);

/**
 * @brief 创建可共享的字体集对象{@link OH_Drawing_FontCollection}。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return 指向创建的字体集对象的指针，可以被多个{@link OH_Drawing_TypographyCreate}对象使用。
 * @since 12
 * @version 1.0
 * @release OH_Drawing_DestroyFontCollection {return}
 */
OH_Drawing_FontCollection* OH_Drawing_CreateSharedFontCollection(void);

/**
 * @brief 清理字体排版缓存（字体排版缓存本身设有内存上限和清理机制，所占内存有限，如无内存要求，不建议清理）。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection 指向字体集对象{@link OH_Drawing_FontCollection}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ClearFontCaches(OH_Drawing_FontCollection* fontCollection);

/**
 * @brief 获取全局字体集对象{@link OH_Drawing_FontCollection}，可获取主题字信息，禁止释放该对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return 指向全局字体集对象的指针，可以被多个{@link OH_Drawing_TypographyCreate}对象使用，禁止释放。
 * @since 14
 * @version 1.0
 */
OH_Drawing_FontCollection* OH_Drawing_GetFontCollectionGlobalInstance(void);
#ifdef __cplusplus
}
#endif
/** @} */
#endif
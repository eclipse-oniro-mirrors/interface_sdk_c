
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
#ifndef C_INCLUDE_DRAWING_FONT_MGR_H
#define C_INCLUDE_DRAWING_FONT_MGR_H
#include "drawing_types.h"
#include "drawing_text_typography.h"
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建字体管理对象，只支持管理系统字体。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @return 返回指向已创建的字体管理对象{@link OH_Drawing_FontMgr}的指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontMgr* OH_Drawing_FontMgrCreate(void);

/**
 * @brief 释放字体管理对象占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr 指向字体管理对象{@link OH_Drawing_FontMgr}的指针，由{@link OH_Drawing_FontMgrCreate}获取。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontMgrDestroy(OH_Drawing_FontMgr* drawingFontMgr);

/**
 * @brief 获取字体家族的数量。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr 指向字体管理对象{@link OH_Drawing_FontMgr}的指针，由{@link OH_Drawing_FontMgrCreate}获取。
 * @return 返回字体家族的数量。
 * @since 12
 * @version 1.0
 */
int OH_Drawing_FontMgrGetFamilyCount(OH_Drawing_FontMgr* drawingFontMgr);

/**
 * @brief 由索引值获取字体家族名称。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr 指向字体管理对象{@link OH_Drawing_FontMgr}的指针，由{@link OH_Drawing_FontMgrCreate}获取。
 * @param index 用于获取对应字体家族名称的索引值。
 * @return 返回索引值对应的字体家族名称，不再需要时，请使用{@link OH_Drawing_FontMgrDestroyFamilyName}释放该对象指针。
 * @since 12
 * @version 1.0
 */
char* OH_Drawing_FontMgrGetFamilyName(OH_Drawing_FontMgr* drawingFontMgr, int index);

/**
 * @brief 释放指定字体家族名称占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param familyName 指定字体家族名称数组。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontMgrDestroyFamilyName(char* familyName);

/**
 * @brief 由字体管理对象构造字体样式集对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr 指向字体管理对象{@link OH_Drawing_FontMgr}的指针，由{@link OH_Drawing_FontMgrCreate}获取。
 * @param index 用于从字体管理对象获取字体样式集对象的索引值。
 * @return 返回指向已创建的字体样式集对象{@link OH_Drawing_FontStyleSet}的指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyleSet* OH_Drawing_FontMgrCreateFontStyleSet(OH_Drawing_FontMgr* drawingFontMgr, int index);

/**
 * @brief 释放字体样式集对象占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontStyleSet 指向字体样式集对象{@link OH_Drawing_FontStyleSet}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontMgrDestroyFontStyleSet(OH_Drawing_FontStyleSet* drawingFontStyleSet);

/**
 * @brief 由指定的字体家族名称，获取字体样式集对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr 指向字体管理对象{@link OH_Drawing_FontMgr}的指针，由{@link OH_Drawing_FontMgrCreate}获取。
 * @param familyName 指定的字体家族名称。
 * @return 返回对应的字体样式集对象{@link OH_Drawing_FontStyleSet}，不再需要时，请使用{@link OH_Drawing_FontMgrDestroyFontStyleSet}释放该对象指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyleSet* OH_Drawing_FontMgrMatchFamily(OH_Drawing_FontMgr* drawingFontMgr, const char* familyName);

/**
 * @brief 根据指定的字体样式信息和字体家族名称，获取字型对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr 指向字体管理对象{@link OH_Drawing_FontMgr}的指针，由{@link OH_Drawing_FontMgrCreate}获取。
 * @param familyName 指定的字体家族名称。
 * @param fontStyle 字体样式对象，包括字体字重、字体宽度和字体斜度信息。
 * @return 返回对应的字体样式的字型对象{@link OH_Drawing_Typeface}，不再需要时，请使用{@link OH_Drawing_TypefaceDestroy}释放该对象指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_FontMgrMatchFamilyStyle(OH_Drawing_FontMgr* drawingFontMgr,
    const char* familyName, OH_Drawing_FontStyleStruct fontStyle);

/**
 * @brief 为指定字符获取字型对象，仅在传入字体管理对象中无法找到传入UTF8字符值对应的字型对象时返回空指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param drawingFontMgr 指向字体管理对象{@link OH_Drawing_FontMgr}的指针，由{@link OH_Drawing_FontMgrCreate}获取。
 * @param familyName 指定的字体家族名称。
 * @param fontStyle 字体样式对象，包括字体字重、字体宽度和字体斜度信息。
 * @param bcp47 用来指示character语言编码数组，是ISO 639、15924和3166-1语言编码的组合。
 * @param bcp47Count 参数bcp47数组大小。
 * @param character 待匹配的UTF8字符值。
 * @return 返回对应的字型对象{@link OH_Drawing_Typeface}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_FontMgrMatchFamilyStyleCharacter(OH_Drawing_FontMgr* drawingFontMgr,
    const char* familyName, OH_Drawing_FontStyleStruct fontStyle,
    const char* bcp47[], int bcp47Count, int32_t character);

/**
 * @brief 为指定索引获取字型对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontStyleSet 指向字体样式集对象{@link OH_Drawing_FontStyleSet}的指针。
 * @param index 指定的字型对象的索引。
 * @return 如果成功，返回对应的字型对象{@link OH_Drawing_Typeface}; 如果失败，返回nullptr。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_FontStyleSetCreateTypeface(OH_Drawing_FontStyleSet* fontStyleSet, int index);

/**
 * @brief 获取字体样式，styleName会申请内存，不再需要styleName时，请使用{@link OH_Drawing_FontStyleSetFreeStyleName}释放该对象指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontStyleSet 指向字体样式集对象{@link OH_Drawing_FontStyleSet}的指针。
 * @param index 指定的字体样式的索引。
 * @param styleName 指定字体样式名称的字符串，会申请内存，不再需要时，请使用{@link OH_Drawing_FontStyleSetFreeStyleName}释放该对象指针。
 * @return 返回对应的字体样式。
 * @since 12
 * @version 1.0
 */
OH_Drawing_FontStyleStruct OH_Drawing_FontStyleSetGetStyle(OH_Drawing_FontStyleSet* fontStyleSet, int32_t index,
    char** styleName);

/**
 * @brief 释放指定字体样式名称的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param styleName 指定字体样式名称的字符串。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FontStyleSetFreeStyleName(char** styleName);

/**
 * @brief 获取最接近字体样式的字型对象。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontStyleSet 指向字体样式集对象{@link OH_Drawing_FontStyleSet}的指针。
 * @param fontStyleStruct 字体样式对象，包括字体字重、字体宽度和字体斜度信息。
 * @return 返回对应的字型对象{@link OH_Drawing_Typeface}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_FontStyleSetMatchStyle(OH_Drawing_FontStyleSet* fontStyleSet,
    OH_Drawing_FontStyleStruct fontStyleStruct);

/**
 * @brief 获取字体样式集中字体的个数。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontStyleSet 指向字体样式集对象{@link OH_Drawing_FontStyleSet}的指针。
 * @return 返回此字体样式集中字体的个数。
 * @since 12
 * @version 1.0
 */
int OH_Drawing_FontStyleSetCount(OH_Drawing_FontStyleSet* fontStyleSet);
#ifdef __cplusplus
}
#endif

/** @} */
#endif
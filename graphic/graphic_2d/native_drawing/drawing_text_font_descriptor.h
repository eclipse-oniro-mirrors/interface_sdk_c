/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef C_INCLUDE_DRAWING_TEXT_FONT_DESCRIPTOR_H
#define C_INCLUDE_DRAWING_TEXT_FONT_DESCRIPTOR_H

/**
 * @addtogroup Drawing
 * @{
 *
 * @brief Provides the font descriptor capability.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 *
 * @since 8
 * @version 1.0
 */

/**
 * @file drawing_text_font_descriptor.h
 *
 * @brief Provide the ability to provide <b>OH_Drawing_FontDescriptor</b>.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Type style flag.
 *
 * @since 14
 * @version 1.0
 */
typedef enum {
    /** Italic font */
    ITALIC = 1 << 0,
    /** Bold font */
    BOLD = 1 << 1,
} OH_Drawing_FontTypeStyle;

/**
 * @brief An enumeration of system font types.
 *
 * @since 14
 * @version 1.0
 */
typedef enum {
    /** All font types */
    ALL = 1 << 0,
    /** System generic font type */
    GENERIC = 1 << 1,
    /** Stylish font type */
    STYLISH = 1 << 2,
    /** Installed font types */
    INSTALLED = 1 << 3,
} OH_Drawing_SystemFontType;

/**
 * @brief Describes the font information.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontDescriptor {
    /** The file path of System font */
    char* path;
    /** A name that uniquely identifies the font */
    char* postScriptName;
    /** The name of System font */
    char* fullName;
    /** The family of System font */
    char* fontFamily;
    /** The subfont family of the system font */
    char* fontSubfamily;
    /** The weight of System font */
    int weight;
    /** The width of System font */
    int width;
    /** Whether the system font is tilted */
    int italic;
    /** Whether the system font is compact */
    bool monoSpace;
    /** whether symbolic fonts are supported */
    bool symbolic;
    /** Font size */
    size_t size;
    /** Font style flag, from OH_Drawing_FontTypeStyle */
    int typeStyle;
} OH_Drawing_FontDescriptor;

/**
 * @brief Obtain all system font descriptive symbols that match the specified font descriptor. Where the 'path' and
 * 'size' fields are not considered as valid matching values, It takes effect when the remaining fields are not
 * default values, If all the fields of the parameters <b>OH_Drawing_FontDescriptor</b> are default, obtain all system
 * font descriptors. If the match fails, return nullptr.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param OH_Drawing_FontDescriptor The pointer to the <b>OH_Drawing_FontDescriptor</b> object. It is recommended to
 * use OH_Drawing_CreateFontDescriptor to obtain a valid OH_Drawing_FontDescriptor instance. If you create your own
 * OH_Drawing_FontDescriptor object, ensure that fields not intended for matching are set to their default values.
 * @param size_t Indicates the count of obtained <b>OH_Drawing_FontDescriptor</b>.
 * @return Returns an array of <b>OH_Drawing_FontDescriptor</b>.
 * @since 14
 * @version 1.0
 */
OH_Drawing_FontDescriptor* OH_Drawing_MatchFontDescriptors(OH_Drawing_FontDescriptor*, size_t*);

/**
 * @brief Releases the <b>OH_Drawing_FontDescriptor</b> array.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param OH_Drawing_FontDescriptor Pointer to <b>OH_Drawing_FontDescriptor</b> array.
 * @param size_t Represents the number of members of the OH_Drawing_FontDescriptor array.
 * @since 14
 * @version 1.0
 */
void OH_Drawing_DestroyFontDescriptors(OH_Drawing_FontDescriptor*, size_t);

/**
 * @brief Get the <b>OH_Drawing_FontDescriptor</b> object by the full name of the font, supporting generic fonts,
 * stylish fonts, and installed fonts.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param OH_Drawing_String* Indicates the full name object <b>OH_Drawing_String</b>.
 * @return Returns the pointer to a font descriptor object <b>OH_Drawing_FontDescriptor</b>.
 * @since 14
 * @version 1.0
 */
OH_Drawing_FontDescriptor* OH_Drawing_GetFontDescriptorByFullName(const OH_Drawing_String*);

/**
 * @brief Obtain the corresponding font full name list by the font type.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param OH_Drawing_SystemFontType Indicates enumerates of system font type.
 * @return Returns the pointer to full name array object <b>OH_Drawing_Array</b>.
 * @since 14
 * @version 1.0
 */
OH_Drawing_Array* OH_Drawing_GetSystemFontFullNamesByType(OH_Drawing_SystemFontType);

/**
 * @brief Get the specified full name object <b>OH_Drawing_String</b> by index from the 
 * <b>OH_Drawing_Array</b> object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param OH_Drawing_Array Indicates an array of full name object <b>OH_Drawing_Array</b>.
 * @param size_t The index of full name.
 * @return Returns a full name object <b>OH_Drawing_String</b>.
 * @since 14
 * @version 1.0
 */
const OH_Drawing_String* OH_Drawing_GetSystemFontFullNamesElement(OH_Drawing_Array*, size_t);

/**
 * @brief Releases the memory occupied by a list of system font names.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param OH_Drawing_Array Indicates an array of full name.
 * @since 14
 * @version 1.0
 */
void OH_Drawing_DestroySystemFontFullNames(OH_Drawing_Array*);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
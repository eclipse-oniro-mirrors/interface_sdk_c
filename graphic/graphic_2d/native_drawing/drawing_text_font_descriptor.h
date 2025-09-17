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

/**
 * @addtogroup Drawing
 * @{
 *
 * @brief Provides the font descriptor capability.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 *
 * @since 14
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
 * @since 14
 * @version 1.0
 */

#ifndef DRAWING_TEXT_FONT_DESCRIPTOR_H
#define DRAWING_TEXT_FONT_DESCRIPTOR_H

#include "drawing_text_declaration.h"
#include "drawing_text_typography.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief An enumeration of system font types.
 *
 * @since 14
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
   /**
    * Customized font types
    * @since 18
    */
    CUSTOMIZED = 1 << 4,
} OH_Drawing_SystemFontType;

/**
 * @brief An enumeration of font full descriptor attribute.
 *
 * @since 22
 */
typedef enum {
    /** The file path of the font */
    FULL_DESCRIPTOR_ATTR_S_PATH = 0,
    /** A name that uniquely identifies the font */
    FULL_DESCRIPTOR_ATTR_S_POSTSCRIPT_NAME = 1,
    /** The full name of the font */
    FULL_DESCRIPTOR_ATTR_S_FULL_NAME = 2,
    /** The family name of the font */
    FULL_DESCRIPTOR_ATTR_S_FAMILY_NAME = 3,
    /** The subfont family of the font */
    FULL_DESCRIPTOR_ATTR_S_SUB_FAMILY_NAME = 4,
    /** The weight of the font */
    FULL_DESCRIPTOR_ATTR_I_WEIGHT = 5,
    /** The width of the font */
    FULL_DESCRIPTOR_ATTR_I_WIDTH = 6,
    /** Whether the font is tilted */
    FULL_DESCRIPTOR_ATTR_I_ITALIC = 7,
    /** Whether the font is monospaced */
    FULL_DESCRIPTOR_ATTR_B_MONO = 8,
    /** whether symbolic fonts are supported */
    FULL_DESCRIPTOR_ATTR_B_SYMBOLIC = 9,
} OH_Drawing_FontFullDescriptorAttributeId;

/**
 * @brief Obtain all system font descriptive symbols that match the specified font descriptor. Where the 'path'
 * fields are not considered as valid matching values, It takes effect when the remaining fields are not
 * default values, If all the fields of the parameters <b>OH_Drawing_FontDescriptor</b> are default, obtain all system
 * font descriptors. If the match fails, return nullptr.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param desc The pointer to the <b>OH_Drawing_FontDescriptor</b> object. It is recommended to
 * use <b>OH_Drawing_CreateFontDescriptor</b> to obtain a valid <b>OH_Drawing_FontDescriptor</b> instance.
 * If you create your own <b>OH_Drawing_FontDescriptor</b> object, ensure that fields not intended for matching are
 * set to their default values.
 * @param num Indicates the count of obtained <b>OH_Drawing_FontDescriptor</b>.
 * @return Returns an array of <b>OH_Drawing_FontDescriptor</b>. Released through the
 * <b>OH_Drawing_DestroyFontDescriptors</b> interface after use.
 * @since 18
 */
OH_Drawing_FontDescriptor* OH_Drawing_MatchFontDescriptors(OH_Drawing_FontDescriptor* desc, size_t* num);

/**
 * @brief Releases the <b>OH_Drawing_FontDescriptor</b> array.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param descriptors <b>OH_Drawing_FontDescriptor</b> object array.
 * @param num Represents the number of members of the <b>OH_Drawing_FontDescriptor</b> array.
 * @since 18
 */
void OH_Drawing_DestroyFontDescriptors(OH_Drawing_FontDescriptor* descriptors, size_t num);

/**
 * @brief Get the <b>OH_Drawing_FontDescriptor</b> object by the font full name and the font type, supporting generic
 * fonts, stylish fonts, and installed fonts.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fullName Indicates the full name object <b>OH_Drawing_String</b>.
 * @param fontType Indicates enumerates of system font type object <b>OH_Drawing_SystemFontType</b>.
 * @return Returns the pointer to a font descriptor object <b>OH_Drawing_FontDescriptor</b>.
 * @since 14
 */
OH_Drawing_FontDescriptor* OH_Drawing_GetFontDescriptorByFullName(const OH_Drawing_String* fullName,
    OH_Drawing_SystemFontType fontType);

/**
 * @brief Obtain the corresponding font full name array by the font type.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontType Indicates enumerates of system font type object <b>OH_Drawing_SystemFontType</b>.
 * @return Returns the pointer to full name array object <b>OH_Drawing_Array</b>.
 * @since 14
 */
OH_Drawing_Array* OH_Drawing_GetSystemFontFullNamesByType(OH_Drawing_SystemFontType fontType);

/**
 * @brief Get the specified full name object <b>OH_Drawing_String</b> by index from the
 * <b>OH_Drawing_Array</b> object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fullNameArray Indicates an array of full name object <b>OH_Drawing_Array</b>.
 * @param index The index of full name.
 * @return Returns a full name object <b>OH_Drawing_String</b>.
 * @since 14
 */
const OH_Drawing_String* OH_Drawing_GetSystemFontFullNameByIndex(OH_Drawing_Array* fullNameArray, size_t index);

/**
 * @brief Releases the memory occupied by an array of font full names.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fullNameArray Indicates an array of full name object <b>OH_Drawing_Array</b>.
 * @since 14
 */
void OH_Drawing_DestroySystemFontFullNames(OH_Drawing_Array* fullNameArray);

/**
 * @brief Retrieves an array of font full descriptors from raw binary data.
 *
 * @param data Pointer to the raw binary font data buffer.
 * @param size Size of the font data buffer in bytes.
 * @return Returns a pointer to <b>OH_Drawing_Array</b> containing font full descriptors. 
 *         Returns <b>NULL</b> if the operation fails due to invalid data format or parsing errors.
 * @since 22
 */
OH_Drawing_Array* OH_Drawing_GetFontFullDescriptorsFromStream(const void* data, size_t size);

/**
 * @brief Obtains an array of font full descriptors from font file path.
 *
 * @param path Indicates the pointer to the path to set.
 * @return Returns a pointer to <b>OH_Drawing_Array</b> structure containing font full descriptors.
 *         Returns <b>NULL</b> if no fonts are found, invalid path, no permission, or non-font file.
 * @since 22
 */
OH_Drawing_Array* OH_Drawing_GetFontFullDescriptorsFromPath(char* path);

/**
 * @brief Retrieves a font full descriptor from an array by index.
 *
 * @param descriptorArray Pointer to the array of font full descriptors <b>OH_Drawing_Array</b>.
 * @param index Zero-based index position of the descriptor to retrieve.
 * @return Returns a pointer to <b>OH_Drawing_FontFullDescriptor</b> at the specified index.
 *         Returns <b>NULL</b> if the index is out of bounds or the array is invalid.
 * @since 22
 */
const OH_Drawing_FontFullDescriptor* OH_Drawing_GetFontFullDescriptorByIndex(
    OH_Drawing_Array* descriptorArray, size_t index);

/**
 * @brief Releases the memory occupied by an array of font full descriptors.
 *
 * @param descriptorArray Pointer to the array of font full descriptors <b>OH_Drawing_Array</b>.
 * @since 22
 */
void OH_Drawing_DestroyFontFullDescriptors(OH_Drawing_Array* descriptorArray);

/**
 * @brief Retrieves an integer attribute value from a font full descriptor.
 *
 * @param descriptor Pointer to the font full descriptor <b>OH_Drawing_FontFullDescriptor</b>.
 * @param id Attribute identifier from <b>OH_Drawing_FontFullDescriptorAttributeId</b> enumeration.
 * @param value Output parameter to receive the requested integer attribute value.
 * @return Returns the error code.
 *         Returns <b>OH_DRAWING_SUCCESS</b> if the operation is successful.
 *         Returns <b>OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE</b> if attribute ID is invalid.
 *         Returns <b>OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH</b> if parameter type mismatch occurs.
 * @since 22
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontFullDescriptorAttributeInt(const OH_Drawing_FontFullDescriptor* descriptor,
    OH_Drawing_FontFullDescriptorAttributeId id, int* value);

/**
 * @brief Retrieves a boolean attribute value from a font full descriptor.
 *
 * @param descriptor Pointer to the font full descriptor <b>OH_Drawing_FontFullDescriptor</b>.
 * @param id Attribute identifier from <b>OH_Drawing_FontFullDescriptorAttributeId</b> enumeration.
 * @param value Output parameter to receive the requested boolean attribute value.
 * @return Returns the error code.
 *         Returns <b>OH_DRAWING_SUCCESS</b> if the operation is successful.
 *         Returns <b>OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE</b> if attribute ID is invalid.
 *         Returns <b>OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH</b> if parameter type mismatch occurs.
 * @since 22
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontFullDescriptorAttributeBool(const OH_Drawing_FontFullDescriptor* descriptor,
    OH_Drawing_FontFullDescriptorAttributeId id, bool* value);

/**
 * @brief Retrieves a string attribute value from a font full descriptor.
 *
 * @note The caller is responsible for manually releasing the internal <b>strData</b> member of the
 *       <b>OH_Drawing_String</b> structure when it is no longer needed.
 *
 * @param descriptor Pointer to the font full descriptor <b>OH_Drawing_FontFullDescriptor</b>.
 * @param id Attribute identifier from <b>OH_Drawing_FontFullDescriptorAttributeId</b> enumeration.
 * @param str Output parameter to receive pointer to the requested string attribute value.
 * @return Returns the error code.
 *         Returns <b>OH_DRAWING_SUCCESS</b> if the operation is successful.
 *         Returns <b>OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE</b> if attribute ID is invalid.
 *         Returns <b>OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH</b> if parameter type mismatch occurs.
 * @since 22
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontFullDescriptorAttributeString(const OH_Drawing_FontFullDescriptor* descriptor,
    OH_Drawing_FontFullDescriptorAttributeId id, OH_Drawing_String* str);
#ifdef __cplusplus
}
#endif
/** @} */
#endif
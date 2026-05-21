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
 * @brief This file declares the capabilities of font information, such as obtaining font information and searching for
 * a font.
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
 * @brief Defines an enum for the system font types.
 *
 * @since 14
 */
typedef enum {
    /**
     * All font types.
     */
    ALL = 1 << 0,

    /**
     * System font type.
     */
    GENERIC = 1 << 1,

    /**
     * Style font type.
     */
    STYLISH = 1 << 2,

    /**
     * User-installed font type.
     */
    INSTALLED = 1 << 3,

    /**
     * Custom font type.
     * @since 18
     */
    CUSTOMIZED = 1 << 4
} OH_Drawing_SystemFontType;

/**
 * @brief Enumerates font descriptor attributes. You can use the corresponding APIs to obtain the attributes of
 * different font descriptor types. For example, if **FULL_DESCRIPTOR_ATTR_I_WEIGHT** is of the int type, use the
 * {@link OH_Drawing_GetFontFullDescriptorAttributeInt} API to obtain its attribute value.
 *
 * @since 22
 */
typedef enum {
    /**
     * Font file path, of the {@link OH_Drawing_String} type.
     */
    FULL_DESCRIPTOR_ATTR_S_PATH = 0,

    /**
     * Postscript font name, of the {@link OH_Drawing_String} type.
     */
    FULL_DESCRIPTOR_ATTR_S_POSTSCRIPT_NAME = 1,

    /**
     * Font name, of the {@link OH_Drawing_String} type.
     */
    FULL_DESCRIPTOR_ATTR_S_FULL_NAME = 2,

    /**
     * Font family name, of the {@link OH_Drawing_String} type.
     */
    FULL_DESCRIPTOR_ATTR_S_FAMILY_NAME = 3,

    /**
     * Font subfamily name, of the {@link OH_Drawing_String} type.
     */
    FULL_DESCRIPTOR_ATTR_S_SUB_FAMILY_NAME = 4,

    /**
     * Font weight, of the int type.
     */
    FULL_DESCRIPTOR_ATTR_I_WEIGHT = 5,

    /**
     * Font width style, of the int type.
     */
    FULL_DESCRIPTOR_ATTR_I_WIDTH = 6,

    /**
     * Whether the font is italic, of the int type. **1** means that the font is italic; **0** otherwise.
     */
    FULL_DESCRIPTOR_ATTR_I_ITALIC = 7,
    /**
     * Whether the font is monospace, of the bool type. **true** means yes; **false** otherwise.
     */
    FULL_DESCRIPTOR_ATTR_B_MONO = 8,

    /**
     * Whether the font supports the symbol font, of the bool type. **true** means yes; **false** otherwise.
     */
    FULL_DESCRIPTOR_ATTR_B_SYMBOLIC = 9,

    /**
     * Extracts the postscript name of the font based on the system language configuration.
     * @since 23
     */
    FULL_DESCRIPTOR_ATTR_S_LOCAL_POSTSCRIPT_NAME = 10,

    /**
     * Extracts the full name of the font based on the system language configuration.
     * @since 23
     */
    FULL_DESCRIPTOR_ATTR_S_LOCAL_FULL_NAME = 11,

    /**
     * Extracts the font family name based on the system language configuration.
     * @since 23
     */
    FULL_DESCRIPTOR_ATTR_S_LOCAL_FAMILY_NAME = 12,

    /**
     * Extracts the font subfamily name based on the system language configuration.
     * @since 23
     */
    FULL_DESCRIPTOR_ATTR_S_LOCAL_SUB_FAMILY_NAME = 13,

    /**
     * Font version.
     * @since 23
     */
    FULL_DESCRIPTOR_ATTR_S_VERSION = 14,

    /**
     * Font manufacturer information.
     * @since 23
     */
    FULL_DESCRIPTOR_ATTR_S_MANUFACTURE = 15,

    /**
     * The copyright of the font
     * @since 23
     */
    FULL_DESCRIPTOR_ATTR_S_COPYRIGHT = 16,

    /**
     * Font trademark information.
     * @since 23
     */
    FULL_DESCRIPTOR_ATTR_S_TRADEMARK = 17,

    /**
     * Font license information.
     * @since 23
     */
    FULL_DESCRIPTOR_ATTR_S_LICENSE = 18,

    /**
     * Font variable axis array.
     * @since 24
     */
    FULL_DESCRIPTOR_ATTR_O_VARIATION_AXIS = 19,

    /**
     * Font variable instance array.
     * @since 24
     */
    FULL_DESCRIPTOR_ATTR_O_VARIATION_INSTANCE = 20,

    /**
     * Font index.
     * @since 23
     */
    FULL_DESCRIPTOR_ATTR_I_INDEX = 21
} OH_Drawing_FontFullDescriptorAttributeId;

/**
* @brief Enumerates font variable axis attributes.
*
* @since 24
*/
typedef enum {
    /**
     * Keyword identifier of the font variable axis.
     */
    FONT_VARIATION_AXIS_ATTR_S_KEY = 0,

    /**
     * Minimum value of the font variable axis.
     */
    FONT_VARIATION_AXIS_ATTR_D_MIN_VALUE = 1,

    /**
     * Maximum value of the font variable axis.
     */
    FONT_VARIATION_AXIS_ATTR_D_MAX_VALUE = 2,

    /**
     * Default value of the font variable axis.
     */
    FONT_VARIATION_AXIS_ATTR_D_DEFAULT_VALUE = 3,

    /**
     * Flag of the font variable axis. The value **0** indicates that the axis is visible to users, and the value **1**
     * indicates that the axis should be hidden.
     */
    FONT_VARIATION_AXIS_ATTR_I_FLAGS = 4,

    /**
     * English name of the font variable axis.
     */
    FONT_VARIATION_AXIS_ATTR_S_NAME = 5,

    /**
     * Localized name of the font variable axis.
     */
    FONT_VARIATION_AXIS_ATTR_S_LOCAL_NAME = 6
} OH_Drawing_FontVariationAxisAttributeId;

/**
 * @brief Enumerates font variable instance attributes.
 *
 * @since 24
 */
typedef enum {
    /**
     * English name of the font variable instance.
     */
    FONT_VARIATION_INSTANCE_ATTR_S_NAME = 0,

    /**
     * Localized name of the font variable instance.
     */
    FONT_VARIATION_INSTANCE_ATTR_S_LOCAL_NAME = 1
} OH_Drawing_FontVariationInstanceAttributeId;

/**
 * @brief Variable font attribute key-value pair.
 *
 * @since 24
 */
typedef struct {
    /**
     * String identified by the keyword in the variable font attribute key-value pair.
     */
    char* axisKey;
    /**
     * Value of the variable font attribute key-value pair.
     */
    double value;
} OH_Drawing_FontVariationInstanceCoordinate;

/**
 * @brief Obtains all system font descriptors that match a font descriptor. In the {@link OH_Drawing_FontDescriptor}
 * struct, the **path** field is not used for matching, and other fields are valid only when they are not set to their
 * default values.
 * <br>If all fields in **desc** are set to their default values, all system font descriptors are returned.
 * <br>If no matching is found, NULL is returned. Call {@link OH_Drawing_DestroyFontDescriptors} to release this
 * pointer when the object is no longer needed.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param desc Pointer.
 *     <br>You are advised to use {@link OH_Drawing_CreateFontDescriptor} to obtain a valid
 *     {@link OH_Drawing_FontDescriptor} instance.
 *     <br>For an {@link OH_Drawing_FontDescriptor} instance created by yourself, ensure that the fields that are not
 *     used for matching are set to default values.
 * @param num Pointer to the number of elements in the array.
 * @return An array of {@link OH_Drawing_FontDescriptor} objects. Use {@link OH_Drawing_DestroyFontDescriptors} to
 *     release the array.
 * @since 18
 */
OH_Drawing_FontDescriptor* OH_Drawing_MatchFontDescriptors(OH_Drawing_FontDescriptor* desc, size_t* num);

/**
 * @brief Releases an array of {@link OH_Drawing_FontDescriptor} objects.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param descriptors Array.
 * @param num Number of members in an array of {@link OH_Drawing_FontDescriptor} objects.
 * @since 18
 */
void OH_Drawing_DestroyFontDescriptors(OH_Drawing_FontDescriptor* descriptors, size_t num);

/**
 * @brief Obtains a font descriptor based on the font name and type. System fonts, style fonts, and user-installed
 * fonts are supported.
 * <br>A font descriptor is a data structure that describes font features. It contains details of the font appearance
 * and properties.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fullName Pointer to the font name, which is {@link OH_Drawing_String}.
 * @param fontType Enum for the system font types, which is {@link OH_Drawing_SystemFontType}.
 * @return Pointer to an {@link OH_Drawing_FontDescriptor} object. Call {@link OH_Drawing_DestroyFontDescriptor} to
 *     release this pointer when the object is no longer needed.
 * @since 14
 */
OH_Drawing_FontDescriptor* OH_Drawing_GetFontDescriptorByFullName(const OH_Drawing_String* fullName,
    OH_Drawing_SystemFontType fontType);

/**
 * @brief Obtains an array of font names by font type.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontType Enum for the system font types, which is {@link OH_Drawing_SystemFontType}.
 * @return Returns the pointer to the {@link OH_Drawing_Array} object of the corresponding font type. Call
 *     {@link OH_Drawing_DestroySystemFontFullNames} to release this pointer when the object is no longer needed.
 * @since 14
 */
OH_Drawing_Array* OH_Drawing_GetSystemFontFullNamesByType(OH_Drawing_SystemFontType fontType);

/**
 * @brief Obtains the font name with the specified index in the font name array.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fullNameArray Pointer to an {@link OH_Drawing_Array} object.
 * @param index Index of the font in the array.
 * @return Returns the pointer to the font name, which is an {@link OH_Drawing_String} object.
 * @since 14
 */
const OH_Drawing_String* OH_Drawing_GetSystemFontFullNameByIndex(OH_Drawing_Array* fullNameArray, size_t index);

/**
 * @brief Releases the memory occupied by the font name array obtained by font type.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fullNameArray Pointer to an {@link OH_Drawing_Array} object.
 * @since 14
 */
void OH_Drawing_DestroySystemFontFullNames(OH_Drawing_Array* fullNameArray);

/**
 * @brief Obtains the font descriptor array based on the original binary data.
 *
 * @param data Pointer to the raw binary font data buffer.
 * @param size Size of the font data buffer, in bytes.
 * @return Returns the pointer to the {@link OH_Drawing_Array} array of the font descriptor corresponding to the font
 *     file. Call {@link OH_Drawing_DestroyFontFullDescriptors} to release the pointer when the **OH_Drawing_Array**
 *     object is no longer needed.
 *     <br>Returns NULL if the operation fails due to an invalid data format or parsing error.
 * @since 22
 */
OH_Drawing_Array* OH_Drawing_GetFontFullDescriptorsFromStream(const void* data, size_t size);

/**
 * @brief Obtains an array of font descriptors based on the font file path.
 *
 * @param path Path of the font file to be queried.
 * @return Returns the pointer to the {@link OH_Drawing_Array} array of the font descriptor corresponding to the font
 *     file. Call {@link OH_Drawing_DestroyFontFullDescriptors} to release the pointer when the **OH_Drawing_Array**
 *     object is no longer needed.
 *     <br>Returns NULL if the font file is not found, the font file path is invalid, the font file does not have the
 *     required permission, or the file is not in the font format.
 * @since 22
 */
OH_Drawing_Array* OH_Drawing_GetFontFullDescriptorsFromPath(const char* path);

/**
 * @brief Obtains the font descriptor from the font descriptor array based on the index.
 *
 * @param descriptorArray Pointer to the font descriptor array {@link OH_Drawing_Array}.
 * @param index Index of the array, starting from 0.
 * @return Returns the pointer to the font descriptor object {@link OH_Drawing_FontFullDescriptor} at the specified
 *     index.
 *     <br>Returns NULL if the index is out of range or the array is invalid.
 * @since 22
 */
const OH_Drawing_FontFullDescriptor* OH_Drawing_GetFontFullDescriptorByIndex(
    OH_Drawing_Array* descriptorArray, size_t index);

/**
 * @brief Releases the memory occupied by the font descriptor array.
 *
 * @param descriptorArray Pointer to the font descriptor array {@link OH_Drawing_Array}.
 * @since 22
 */
void OH_Drawing_DestroyFontFullDescriptors(OH_Drawing_Array* descriptorArray);

/**
 * @brief Releases the memory occupied by the font descriptor pointer. This function can be used to release the font
 * descriptor pointer obtained by calling {@link OH_Drawing_GetFontFullDescriptorByFullName}.
 *
 * @param descriptor Pointer to the font descriptor object {@link OH_Drawing_FontFullDescriptor}.
 * @since 24
 */
void OH_Drawing_DestroyFontFullDescriptor(const OH_Drawing_FontFullDescriptor* descriptor);

/**
 * @brief Obtains a Unicode array from a font file.
 *
 * @param fontSrc Font file path.
 * @param index Index of the font in a TTC/OTC file. This parameter shall be set to **0** for non-TTC/OTC files.
 * @param unicodeArray Output parameter, which is used to receive the Unicode array. Use **free()** to release the
 *     Unicode array when the array is no longer needed.
 * @param arrayLength Output parameter, which is used to receive the length of the Unicode array.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if the font path is invalid or the file is not a font file.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontUnicodeArrayFromFile(const char* fontSrc, uint32_t index,
    int32_t** unicodeArray, int32_t* arrayLength);

/**
 * @brief Obtains a Unicode array from a font buffer.
 *
 * @param fontBuffer Font file data.
 * @param length Length of the font file data.
 * @param index Index of the font in a TTC/OTC file. This parameter shall be set to **0** for non-TTC/OTC files.
 * @param unicodeArray Output parameter, which is used to receive the Unicode array. Use **free()** to release the
 *     Unicode array when the array is no longer needed.
 * @param arrayLength Output parameter, which is used to receive the length of the Unicode array.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if the buffer data is invalid or not font file data.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontUnicodeArrayFromBuffer(uint8_t* fontBuffer, size_t length, uint32_t index,
    int32_t** unicodeArray, int32_t* arrayLength);

/**
 * @brief Obtains the attributes of a font descriptor of the int type.
 *
 * @param descriptor Pointer to the font descriptor object {@link OH_Drawing_FontFullDescriptor}.
 * @param id Font descriptor attribute ID. You can obtain the font descriptor attribute from
 *     {@link OH_Drawing_FontFullDescriptorAttributeId}.
 * @param value Pointer to the attribute of the **int** type. It is used as an output parameter.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if the descriptor or value parameter is null.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 22
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontFullDescriptorAttributeInt(const OH_Drawing_FontFullDescriptor* descriptor,
    OH_Drawing_FontFullDescriptorAttributeId id, int* value);

/**
 * @brief Obtains the font descriptor attribute of the bool type.
 *
 * @param descriptor Pointer to the font descriptor object {@link OH_Drawing_FontFullDescriptor}.
 * @param id Font descriptor attribute ID. You can obtain the font descriptor attribute from
 *     {@link OH_Drawing_FontFullDescriptorAttributeId}.
 * @param value Pointer to the bool attribute It is used as an output parameter.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if the descriptor or value parameter is null.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 22
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontFullDescriptorAttributeBool(const OH_Drawing_FontFullDescriptor* descriptor,
    OH_Drawing_FontFullDescriptorAttributeId id, bool* value);

/**
 * @brief Obtains the attributes of the {@link OH_Drawing_String} font descriptor.
 *
 * @note The caller is responsible for manually releasing the internal <b>strData</b> member of the
 *     <b>OH_Drawing_String</b> structure when it is no longer needed.
 *
 * @param descriptor Pointer to the font descriptor object {@link OH_Drawing_FontFullDescriptor}.
 * @param id Font descriptor attribute ID. You can obtain the font descriptor attribute from
 *     {@link OH_Drawing_FontFullDescriptorAttributeId}.
 * @param str Pointer to the **OH_Drawing_String** attribute. It is used as an output parameter.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **descriptor** or **str** is a null pointer.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 22
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontFullDescriptorAttributeString(const OH_Drawing_FontFullDescriptor* descriptor,
    OH_Drawing_FontFullDescriptorAttributeId id, OH_Drawing_String* str);

/**
 * @brief Obtains the object array attributes of the font descriptor.
 *
 * @param descriptor Pointer to the font descriptor object {@link OH_Drawing_FontFullDescriptor}.
 * @param id Font descriptor attribute ID. You can obtain the font descriptor attribute from
 *     {@link OH_Drawing_FontFullDescriptorAttributeId}.
 * @return Object array returned.
 * @since 24
 */
OH_Drawing_Array* OH_Drawing_GetFontFullDescriptorAttributeArray(const OH_Drawing_FontFullDescriptor* descriptor,
    OH_Drawing_FontFullDescriptorAttributeId id);

/**
 * @brief Obtains the corresponding font variable axis from the font variable axis array by index.
 *
 * @param array Pointer to the font variable axis array {@link OH_Drawing_Array}.
 * @param index Index of the array, starting from 0.
 * @return Returns the pointer to the font variable axis object {@link OH_Drawing_FontVariationAxis} at the specified
 *     index.
 *     <br>Returns NULL if the index is out of range or the array is invalid.
 * @since 24
 */
OH_Drawing_FontVariationAxis* OH_Drawing_GetFontVariationAxisByIndex(OH_Drawing_Array* array, size_t index);

/**
 * @brief Releases the memory occupied by the font variable axis array.
 *
 * @param fontVariaAxisArray Pointer to the font variable axis array object {@link OH_Drawing_Array}.
 * @since 24
 */
void OH_Drawing_DestroyFontVariationAxis(OH_Drawing_Array* fontVariaAxisArray);

/**
 * @brief Obtains the font variable axis attributes of the double type.
 *
 * @param variationAxis Pointer to the font variable axis object {@link OH_Drawing_FontVariationAxis}.
 * @param id Font variable axis attribute ID. You can obtain the font variable axis attribute from
 *     {@link OH_Drawing_FontVariationAxisAttributeId}.
 * @param value Pointer to the attributes of the double type. It is used as an output parameter.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if the parameter **variationAxis** or **value** is a null pointer.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 24
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontVariationAxisAttributeDouble(OH_Drawing_FontVariationAxis* variationAxis,
    OH_Drawing_FontVariationAxisAttributeId id, double *value);

/**
 * @brief Obtains the font variable axis attributes of the int type.
 *
 * @param variationAxis Pointer to the font variable axis object {@link OH_Drawing_FontVariationAxis}.
 * @param id Font variable axis attribute ID. You can obtain the font variable axis attribute from
 *     {@link OH_Drawing_FontVariationAxisAttributeId}.
 * @param value Pointer to the attribute of the **int** type. It is used as an output parameter.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if the parameter **variationAxis** or **value** is a null pointer.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 24
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontVariationAxisAttributeInt(OH_Drawing_FontVariationAxis* variationAxis,
    OH_Drawing_FontVariationAxisAttributeId id, int *value);

/**
 * @brief Obtains the font variable axis attributes of the {@link OH_Drawing_String} type.
 *
 * @note The caller is responsible for manually releasing the internal <b>strData</b> member of the
 *     <b>OH_Drawing_String</b> structure when it is no longer needed.
 *
 * @param variationAxis Pointer to the font variable axis object {@link OH_Drawing_FontVariationAxis}.
 * @param id Font variable axis attribute ID. You can obtain the font variable axis attribute from
 *     {@link OH_Drawing_FontVariationAxisAttributeId}.
 * @param str Pointer to the **OH_Drawing_String** attribute. It is used as an output parameter.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if the parameter **variationAxis** or **str** is a null pointer.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 24
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontVariationAxisAttributeStr(OH_Drawing_FontVariationAxis* variationAxis,
    OH_Drawing_FontVariationAxisAttributeId id, OH_Drawing_String *str);

/**
 * @brief Obtains the corresponding font variable instance from the font variable instance array by index.
 *
 * @param array Pointer to the font variable instance array {@link OH_Drawing_Array}.
 * @param index Index of the array, starting from 0.
 * @return Returns the pointer to the font variable instance object {@link OH_Drawing_FontVariationInstance} at the
 *     specified index.
 *     <br>Returns NULL if the index is out of range or the array is invalid.
 * @since 24
 */
OH_Drawing_FontVariationInstance* OH_Drawing_GetFontVariationInstanceByIndex(OH_Drawing_Array* array, size_t index);

/**
 * @brief Releases the memory occupied by the font variable instance array.
 *
 * @param fontVariaAxisInstance Pointer to the font variable instance array object {@link OH_Drawing_Array}.
 * @since 24
 */
void OH_Drawing_DestroyFontVariationInstance(OH_Drawing_Array* fontVariaAxisInstance);

/**
 * @brief Obtains the font variable instance attributes of the {@link OH_Drawing_String} type.
 *
 * @note The caller is responsible for manually releasing the internal <b>strData</b> member of the
 *     <b>OH_Drawing_String</b> structure when it is no longer needed.
 *
 * @param variationInstance Pointer to the font variable instance object {@link OH_Drawing_FontVariationInstance}.
 * @param id Font variable instance attribute ID. You can obtain the font variable instance attribute from
 *     {@link OH_Drawing_FontVariationInstanceAttributeId}.
 * @param str Pointer to the **OH_Drawing_String** attribute. It is used as an output parameter.
 * @return Returns the execution result.
 *     <br>**OH_DRAWING_SUCCESS** if the operation is successful.
 *     <br>**OH_DRAWING_ERROR_INCORRECT_PARAMETER** if the parameter **variationInstance** or **str** is a null pointer.
 *     <br>**OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH** if the input attribute ID does not match the called function.
 * @since 24
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontVariationInstanceAttributeStr(
    OH_Drawing_FontVariationInstance* variationInstance,
    OH_Drawing_FontVariationInstanceAttributeId id,
    OH_Drawing_String* str);

/**
 * @brief Obtains the variable font attribute object of the font variable instance.
 *
 * @param variationInstance Pointer to the font variable instance.
 * @param arrayLength Pointer to the list length of OH_Drawing_FontVariationInstanceCoordinate.
 * @return Returns the pointer to the variable font attribute list.
 * @since 24
 */
OH_Drawing_FontVariationInstanceCoordinate* OH_Drawing_GetFontVariationInstanceCoordinate(
    OH_Drawing_FontVariationInstance* variationInstance, size_t* arrayLength);

/**
 * @brief Obtains the complete font descriptor object based on the font name and type.
 *
 * @param fullName Pointer to the font name object {@link OH_Drawing_String}.
 * @param fontType Enum for the system font type object, which is {@link OH_Drawing_SystemFontType}.
 * @return Returns the pointer to the complete font descriptor object {@link OH_Drawing_FontFullDescriptor}. If
 *     OH_Drawing_FontFullDescriptor is not required, use the {@link OH_Drawing_DestroyFontFullDescriptor} API to
 *     release the pointer of the object.
 * @since 24
 */
const OH_Drawing_FontFullDescriptor* OH_Drawing_GetFontFullDescriptorByFullName(const OH_Drawing_String* fullName,
    OH_Drawing_SystemFontType fontType);

/**
 * @brief Obtains the number of fonts contained in a font file.
 *
 * @param fontSrc Font file path.
 * @return Number of fonts.
 * @since 23
 */
uint32_t OH_Drawing_GetFontCountFromFile(const char* fontSrc);

/**
* @brief Obtains the number of fonts contained in a font buffer.
*
* @param fontBuffer Font buffer data.
* @param length Length of the font data.
* @return Number of fonts.
* @since 23
*/
uint32_t OH_Drawing_GetFontCountFromBuffer(uint8_t* fontBuffer, size_t length);

/**
 * @brief Obtains all font file paths of the specified font type.
 *
 * @param fontType Enum for the system font types, which is {@link OH_Drawing_SystemFontType}.
 * @param pathCount Number of font file paths in the list returned.
 * @return Returns a list of **OH_Drawing_String** objects representing font file paths. Use **free()** to free the
 *     object pointer and the internal pointer held by each **OH_Drawing_String** object when they are no longer needed.
 * @since 23
 */
OH_Drawing_String* OH_Drawing_GetFontPathsByType(OH_Drawing_SystemFontType fontType, size_t* pathCount);
#ifdef __cplusplus
}
#endif
/** @} */
#endif
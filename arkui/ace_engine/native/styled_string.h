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
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Provides ArkUI UI capabilities on the Native side, such as UI component creation and destruction,
 * tree node operation, property setting, event monitoring, and so on.
 *
 * @since 12
 */

/**
 * @file styled_string.h
 *
 * @brief Defines the text style and layout manager for the component whose {@link type} is set to **ARKUI_NODE_TEXT**
 * on the native side.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_STYLED_STRING_H
#define ARKUI_NATIVE_STYLED_STRING_H

#include "native_drawing/drawing_text_declaration.h"
#include "native_drawing/drawing_text_typography.h"
#include "native_drawing/drawing_types.h"
#include "native_gesture.h"
#include "native_node.h"
#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines formatted string data objects supported by the text component.
 *
 * @since 12
 */
typedef struct ArkUI_StyledString ArkUI_StyledString;

/**
 * @brief Creates a pointer to the ArkUI_StyledString object.
 *
 * @param style A pointer to OH_Drawing_TypographyStyle, obtained by {@link OH_Drawing_CreateTypographyStyle}.
 * @param collection A pointer to OH_Drawing_FontCollection, obtained by {@link OH_Drawing_CreateFontCollection}.
 * @return Creates a pointer to the ArkUI_StyledString object. If the object returns a null pointer,
 *         the creation failed, either because the address space was full,
 *         or because the style, collection parameter was an exception such as a null pointer.
 * @since 12
 */
ArkUI_StyledString* OH_ArkUI_StyledString_Create(
    OH_Drawing_TypographyStyle* style, OH_Drawing_FontCollection* collection);

/**
 * @brief Free the memory occupied by the ArkUI_StyledString object.
 *
 * @param handle A pointer to the ArkUI_StyledString object.
 * @since 12
 */
void OH_ArkUI_StyledString_Destroy(ArkUI_StyledString* handle);

/**
 * @brief Sets the new layout style to the top of the current format string style stack.
 *
 * @param handle A pointer to the ArkUI_StyledString object.
 * @param style A pointer to the OH_Drawing_TextStyle object.
 * @since 12
 */
void OH_ArkUI_StyledString_PushTextStyle(ArkUI_StyledString* handle, OH_Drawing_TextStyle* style);

/**
 * @brief Sets the corresponding text content based on the current format string style.
 *
 * @param handle A pointer to the ArkUI_StyledString object.
 * @param content A pointer to the text content.
 * @since 12
 */
void OH_ArkUI_StyledString_AddText(ArkUI_StyledString* handle, const char* content);

/**
 * @brief Removes the top style from the stack in the current format string object.
 *
 * @param handle A pointer to the ArkUI_StyledString object.
 * @since 12
 */
void OH_ArkUI_StyledString_PopTextStyle(ArkUI_StyledString* handle);

/**
 * @brief Creates a pointer to an OH_Drawing_Typography object based on a format string object
 * for advanced text estimation and typography.
 *
 * @param handle A pointer to the ArkUI_StyledString object.
 * @return A pointer to the OH_Drawing_Typography object. If the object returns a null pointer,
 *         the creation fails because the handle parameter is abnormal, such as a null pointer.
 * @since 12
 */
OH_Drawing_Typography* OH_ArkUI_StyledString_CreateTypography(ArkUI_StyledString* handle);

/**
 * @brief Set the placeholder.
 *
 * @param handle A pointer to the ArkUI_StyledString object.
 * @param placeholder A pointer to the OH_Drawing_PlaceholderSpan object.
 * @since 12
 */
void OH_ArkUI_StyledString_AddPlaceholder(ArkUI_StyledString* handle, OH_Drawing_PlaceholderSpan* placeholder);

/**
 * @brief Creates an <b>ArkUI_StyledString_Descriptor</b> object.
 *
 * @return Returns the pointer to the <b>ArkUI_StyledString_Descriptor</b> object created.
 * @since 14
 */
ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_Create(void);

/**
 * @brief Destroys an <b>ArkUI_StyledString_Descriptor</b> object and reclaims the memory occupied by the object.
 *
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @since 14
 */
void OH_ArkUI_StyledString_Descriptor_Destroy(ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Converts styled string information into HTML.
 *
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @return Returns the pointer to the resulting HTML string. This pointer is managed internally and should be destroyed
 *         by calling <b>OH_ArkUI_StyledString_Descriptor_Destroy()</b> when no longer needed to free the memory.
 * @since 14
 */
const char* OH_ArkUI_ConvertToHtml(ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Deserializes a byte array containing styled string information into a styled string.
 *
 * @param buffer Byte array to be deserialized.
 * @param bufferSize Length of the byte array.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 14
 */
int32_t OH_ArkUI_UnmarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Serializes the styled string information into a byte array.
 *
 * @param buffer Byte array where the serialized data will be stored.
 * @param bufferSize Length of the byte array.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param resultSize Actual length of the byte array.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 14
 */
int32_t OH_ArkUI_MarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor, size_t* resultSize);

/**
 * @brief Defines a styled string style.<br>        {@link OH_ArkUI_SpanStyle_Create} can be used to create a styled
 * string style object.<br>        {@link OH_ArkUI_SpanStyle_Destroy} can be used to destroy the styled string style
 * object.<br>        After the object is created, {@link OH_ArkUI_SpanStyle_SetStart} and
 * {@link OH_ArkUI_SpanStyle_SetLength} can be used to set the usage scope of the style.<br>        After the object is
 * created, the **OH_ArkUI_SpanStyle_SetXXXStyle** series APIs can be used to set the specific styles that take effect.
 * For example, you can use {@link OH_ArkUI_SpanStyle_SetTextStyle} to set the font style.
 *
 * @since 24
 */
typedef struct OH_ArkUI_SpanStyle OH_ArkUI_SpanStyle;
 
/**
 * @brief Defines an image style object.<br>        {@link OH_ArkUI_ImageAttachment_Create} can be used to create an
 * image style object.<br>        {@link OH_ArkUI_ImageAttachment_Destroy} can be used to destroy the image style
 * object.<br>        After the object is created, the **OH_ArkUI_ImageAttachment_SetXXX** series APIs can be used to
 * set the styles that take effect. For example, you can use {@link OH_ArkUI_ImageAttachment_SetPixelMap} to set an
 * image source.
 *
 * @since 24
 */
typedef struct OH_ArkUI_ImageAttachment OH_ArkUI_ImageAttachment;
 
/**
 * @brief Defines a custom drawing span.<br>        {@link OH_ArkUI_CustomSpan_Create} can be used to create a custom
 * drawing span object.<br>        {@link OH_ArkUI_CustomSpan_Destroy} can be used to destroy the custom drawing span
 * object.<br>        After the object is created, {@link OH_ArkUI_CustomSpan_RegisterOnMeasureCallback} and
 * {@link OH_ArkUI_CustomSpan_RegisterOnDrawCallback} can be used to register drawing callback functions.
 *
 * @since 24
 */
typedef struct OH_ArkUI_CustomSpan OH_ArkUI_CustomSpan;
 
/**
 * @brief Enumerates the styles of a styled string.
 *
 * @since 24
 */
typedef enum {
    /**
     * No style is specified.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_UNSPECIFIED = -1,

    /**
     * Text font style.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_FONT = 0,

    /**
     * Text decorative line style.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_DECORATION = 1,

    /**
     * Text baseline offset style.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_BASELINE_OFFSET = 2,

    /**
     * Text letter spacing style.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_LETTER_SPACING = 3,

    /**
     * Text shadow style.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_TEXT_SHADOW = 4,

    /**
     * Text line height style.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_LINE_HEIGHT = 5,

    /**
     * Text background color style.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_BACKGROUND_COLOR = 6,

    /**
     * URL style.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_URL = 7,

    /**
     * Text line spacing style.
     * @since 26.0.0
     */
    OH_ARKUI_STYLEDSTRINGKEY_LINE_SPACING = 8,

    /**
     * Gesture style.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_GESTURE = 100,

    /**
     * Text paragraph style.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_PARAGRAPH_STYLE = 200,

    /**
     * Image style.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_IMAGE = 300,

    /**
     * Custom span style.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_CUSTOM_SPAN = 400,

    /**
     * User data span style.
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_USER_DATA = 500
} OH_ArkUI_StyledStringKey;
 
/**
 * @brief Creates an {@link ArkUI_StyledString_Descriptor} object of the plain text content type.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_StyledString_Descriptor_Destroy </b> to destroy it.
 *     All input pointer parameters must be allocated, managed, and released by the caller.
 * @param value Pointer to text content string of the styled string.
 * @param styles Pointer to the initialization option of the styled string, which points to an array of the
 *     {@link OH_ArkUI_SpanStyle} object.
 * @param length Length of the initialization option of the styled string.
 * @return The pointer to the <b>ArkUI_StyledString_Descriptor</b> object created. If the result is a null pointer,
 *     it may be params is invalid.
 * @since 24
 */
ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_CreateWithString(const char* value,
    const OH_ArkUI_SpanStyle** styles, int32_t length);
 
/**
 * @brief Creates an {@link ArkUI_StyledString_Descriptor} object of the image content type.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_StyledString_Descriptor_Destroy </b> to destroy it.
 *     All input pointer parameters must be allocated, managed, and released by the caller.
 * @param value Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @return The pointer to the <b>ArkUI_StyledString_Descriptor</b> object created. If the result is a null pointer,
 *     it may be params is invalid.
 * @since 24
 */
ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_CreateWithImageAttachment(
    const OH_ArkUI_ImageAttachment* value);
 
/**
 * @brief Creates an {@link ArkUI_StyledString_Descriptor} object of the custom span content type.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_StyledString_Descriptor_Destroy </b> to destroy it.
 *     All input pointer parameters must be allocated, managed, and released by the caller.
 * @param value Pointer to the {@link OH_ArkUI_CustomSpan} object.
 * @return The pointer to the <b>ArkUI_StyledString_Descriptor</b> object created. If the result is a null pointer,
 *     it may be params is invalid.
 * @since 24
 */
ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_CreateWithCustomSpan(const OH_ArkUI_CustomSpan* value);

/**
 * @brief Obtains the length of a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param length Pointer to the character length.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_GetLength(const ArkUI_StyledString_Descriptor* descriptor,
    int32_t* length);
 
/**
 * @brief Obtains the text content of a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param buffer Pointer to the buffer for storing the text content in the memory. You need to allocate the memory.
 * @param bufferSize Buffer size.
 * @param writeLength Pointer to the length of the data actually written to the buffer if
 *     {@link ARKUI_ERROR_CODE_NO_ERROR} is returned.
 *     <br>Pointer to the minimum length required for writing the entire string to the buffer if
 *     {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 *     Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_GetString(
    const ArkUI_StyledString_Descriptor* descriptor, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Checks whether a styled string is the same as another styled string. The two styled strings are the same if
 * they have the same text and style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param firstDescriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param secondDescriptor Pointer to another {@link ArkUI_StyledString_Descriptor} object.
 * @param isEqual Pointer to the **isEqual** parameter indicating whether the two styled strings are the same. **true**
 *     if the two are the same; returns **false** otherwise.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_IsEqual(const ArkUI_StyledString_Descriptor* firstDescriptor,
    const ArkUI_StyledString_Descriptor* secondDescriptor, bool* isEqual);

/**
 * @brief Obtains a sub-styled string of a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param subDescriptor Pointer to the {@link ArkUI_StyledString_Descriptor} sub-styled string object.
 * @param start Start position of the sub-styled string. The value range is [0, length of the styled string].
 * @param length Length of the sub-styled string. The value range is [0, difference between the length of the styled
 *     string and the value of **start**].
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_SubStyledString(const ArkUI_StyledString_Descriptor* descriptor,
    ArkUI_StyledString_Descriptor* subDescriptor, uint32_t start, uint32_t length);

/**
 * @brief Obtains the style set within a specified range of a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param start Start position of the specified range. The value range is [0, length of the styled string].
 * @param length Length of the specified range. The value range is [0, difference between the length of the styled
 *     string and the value of **start**].
 * @param styledKey Style type to be obtained. The value is an enumerated value of {@link OH_ArkUI_StyledStringKey}.
 * @param styles Pointer to the buffer of the style object array.
 * @param stylesSize Size of the buffer for the style object array.
 * @param writeLength Pointer to the actual size of the array of the style object obtained from the styled string.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 *     Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_GetStyles(const ArkUI_StyledString_Descriptor* descriptor,
    uint32_t start, uint32_t length, OH_ArkUI_StyledStringKey styledKey, OH_ArkUI_SpanStyle** styles,
    uint32_t stylesSize, uint32_t* writeLength);

/**
 * @brief Converts an HTML string to a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param html Pointer to the HTML string to be converted into a styled string.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_FromHtml(ArkUI_StyledString_Descriptor* descriptor, const char* html);
 
/**
 * @brief Replaces the text within a specified range of a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param start Start position of the specified range. The value range is [0, length of the styled string].
 * @param length Length of the specified range. The value range is [0, difference between the length of the styled
 *     string and the value of **start**].
 * @param string Pointer to the string to replace the content in the target range.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ReplaceString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, uint32_t length, const char* string);
 
/**
 * @brief Inserts text at a specified position of a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param start Insertion position. The value range is [0, length of the styled string].
 * @param string Pointer to the string to insert.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_InsertString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, const char* string);
 
/**
 * @brief Removes the text within a specified range of a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param start Start position of the specified range. The value range is [0, length of the styled string].
 * @param length Length of the specified range. The value range is [0, difference between the length of the styled
 *     string and the value of **start**].
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_RemoveString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, uint32_t length);
 
/**
 * @brief Replaces the style within a specified range of a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 *     <br>You need to call {@link OH_ArkUI_SpanStyle_SetStart} and {@link OH_ArkUI_SpanStyle_SetLength} to set the
 *     target range in the object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ReplaceStyle(
    ArkUI_StyledString_Descriptor* descriptor, const OH_ArkUI_SpanStyle* spanStyle);
 
/**
 * @brief Sets a new style for a specified range of a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object. You need to call
 *     {@link OH_ArkUI_SpanStyle_SetStart} and {@link OH_ArkUI_SpanStyle_SetLength} to set the target range in the
 *     object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_SetStyle(
    ArkUI_StyledString_Descriptor* descriptor, const OH_ArkUI_SpanStyle* spanStyle);
 
/**
 * @brief Removes the specified style for a specified range of a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param start Start position of the specified range. The value range is [0, length of the styled string].
 * @param length Length of the specified range. The value range is [0, difference between the length of the styled
 *     string and the value of **start**].
 * @param styledKey Style type. The value is an enumerated value of {@link OH_ArkUI_StyledStringKey}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_RemoveStyle(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, uint32_t length, OH_ArkUI_StyledStringKey styledKey);
 
/**
 * @brief Clears all styles of a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ClearStyles(ArkUI_StyledString_Descriptor* descriptor);
 
/**
 * @brief Replaces the styled string within a specified range.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param start Start position of the specified range. The value range is [0, length of the styled string].
 * @param length Length of the specified range. The value range is [0, difference between the length of the styled
 *     string and the value of **start**].
 * @param other Pointer to the new {@link ArkUI_StyledString_Descriptor} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ReplaceStyledString(ArkUI_StyledString_Descriptor* descriptor,
    uint32_t start, uint32_t length, const ArkUI_StyledString_Descriptor* other);
 
/**
 * @brief Inserts a new styled string at a specified position of a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param start Insertion position. The value range is [0, length of the styled string].
 * @param other Pointer to the new {@link ArkUI_StyledString_Descriptor} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_InsertStyledString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, const ArkUI_StyledString_Descriptor* other);
 
/**
 * @brief Appends a new styled string to the end of a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @param other Pointer to the new {@link ArkUI_StyledString_Descriptor} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_AppendStyledString(
    ArkUI_StyledString_Descriptor* descriptor, const ArkUI_StyledString_Descriptor* other);
 
/**
 * @brief Actively refreshes the custom span in a styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_InvalidateCustomSpan(const ArkUI_StyledString_Descriptor* descriptor);
 
/**
 * @brief Defines a text font style.
 * {@link OH_ArkUI_TextStyle_Create} can be used to create a text font style object.
 * {@link OH_ArkUI_TextStyle_Destroy} can be used to destroy the text font style object.<br>
 * After the object is created, the **OH_ArkUI_TextStyle_SetXXX** series APIs can be used to set the specific
 * styles that take effect. For example, you can use {@link OH_ArkUI_TextStyle_SetFontColor} to set text color.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextStyle OH_ArkUI_TextStyle;
 
/**
 * @brief Enumerates the text superscript and subscript styles.
 *
 * @since 24
 */
typedef enum {
    /**
     * Normal text style.
     * @since 24
     */
    OH_ARKUI_SUPERSCRIPTSTYLE_NORMAL = 0,

    /**
     * Superscript text style.
     * @since 24
     */
    OH_ARKUI_SUPERSCRIPTSTYLE_SUPERSCRIPT,

    /**
     * Subscript text style.
     * @since 24
     */
    OH_ARKUI_SUPERSCRIPTSTYLE_SUBSCRIPT
} OH_ArkUI_SuperscriptStyle;
 
/**
 * @brief Creates an {@link OH_ArkUI_TextStyle} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_TextStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @since 24
 */
OH_ArkUI_TextStyle* OH_ArkUI_TextStyle_Create();
 
/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_TextStyle} object.
 *
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @since 24
 */
void OH_ArkUI_TextStyle_Destroy(OH_ArkUI_TextStyle* textStyle);
 
/**
 * @brief Sets text color for a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param fontColor Font color, in 0xARGB format.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontColor(OH_ArkUI_TextStyle* textStyle, uint32_t fontColor);
 
/**
 * @brief Obtains the text color of a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param fontColor Pointer to the font color, in 0xARGB format.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontColor(const OH_ArkUI_TextStyle* textStyle, uint32_t* fontColor);
 
/**
 * @brief Sets a font family for a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param fontFamily Pointer to the font family, containing the font names to be set. Different font names are
 *     separated by commas (,).
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontFamily(OH_ArkUI_TextStyle* textStyle, const char* fontFamily);
 
/**
 * @brief Obtains the font family of a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param buffer Pointer to the buffer for storing the font family in the memory. You need to allocate the memory.
 * @param bufferSize Maximum number of characters that can be written to the buffer.
 * @param writeLength Pointer to the length of the string actually written to the buffer if
 *     {@link ARKUI_ERROR_CODE_NO_ERROR} is returned.
 *     <br>Pointer to the minimum length required for writing the entire string to the buffer if
 *     {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *     Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontFamily(const OH_ArkUI_TextStyle* textStyle,
    char* buffer, int32_t bufferSize, int32_t* writeLength);
 
/**
 * @brief Sets font size for a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param fontSize Font size, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontSize(OH_ArkUI_TextStyle* textStyle, float fontSize);
 
/**
 * @brief Obtains the font size of a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param fontSize Pointer to the font size, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontSize(const OH_ArkUI_TextStyle* textStyle, float* fontSize);
 
/**
 * @brief Sets font weight for a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param fontWeight Font weight. The value is an integer multiple of 100 within the [100, 900] range, for example, **
 *     100** or **900**.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontWeight(OH_ArkUI_TextStyle* textStyle, uint32_t fontWeight);
 
/**
 * @brief Obtains the font weight of a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param fontWeight Pointer to the font weight. The value is an integer multiple of 100 within the [100, 900] range,
 *     for example, **100** or **900**.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontWeight(const OH_ArkUI_TextStyle* textStyle, uint32_t* fontWeight);
 
/**
 * @brief Sets font style for a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param fontStyle Font style. The value is an enumerated value of {@link ArkUI_FontStyle}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontStyle(OH_ArkUI_TextStyle* textStyle, ArkUI_FontStyle fontStyle);
 
/**
 * @brief Obtains the font style of a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param fontStyle Pointer to the font style. The value is an enumerated value of {@link ArkUI_FontStyle}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontStyle(const OH_ArkUI_TextStyle* textStyle, ArkUI_FontStyle* fontStyle);
 
/**
 * @brief Sets stroke width for a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param strokeWidth Stroke width, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetStrokeWidth(OH_ArkUI_TextStyle* textStyle, float strokeWidth);
 
/**
 * @brief Obtains the stroke width of a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param strokeWidth Pointer to the stroke width, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetStrokeWidth(const OH_ArkUI_TextStyle* textStyle, float* strokeWidth);
 
/**
 * @brief Sets a stroke color for a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param strokeColor Stroke color, in 0xARGB format.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetStrokeColor(OH_ArkUI_TextStyle* textStyle, uint32_t strokeColor);
 
/**
 * @brief Obtains the stroke color of a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param strokeColor Pointer to the stroke color, in 0xARGB format.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetStrokeColor(const OH_ArkUI_TextStyle* textStyle, uint32_t* strokeColor);
 
/**
 * @brief Sets superscript and subscript styles for a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param superscript Superscript and subscript styles. The value is an enumerated value of
 *     {@link OH_ArkUI_SuperscriptStyle}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetSuperscript(OH_ArkUI_TextStyle* textStyle,
    OH_ArkUI_SuperscriptStyle superscript);
 
/**
 * @brief Obtains the superscript and subscript styles of a text font style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @param superscript Pointer to the superscript and subscript styles. The value is an enumerated value of
 *     {@link OH_ArkUI_SuperscriptStyle}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetSuperscript(const OH_ArkUI_TextStyle* textStyle,
    OH_ArkUI_SuperscriptStyle* superscript);
 
/**
 * @brief Creates an {@link OH_ArkUI_SpanStyle} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_SpanStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_SpanStyle</b> object.
 * @since 24
 */
OH_ArkUI_SpanStyle* OH_ArkUI_SpanStyle_Create();
 
/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_SpanStyle} object.
 *
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @since 24
 */
void OH_ArkUI_SpanStyle_Destroy(OH_ArkUI_SpanStyle* spanStyle);
 
/**
 * @brief Obtains the style of the styled string object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param styledKey Pointer to the style type. The value is an enumerated value of {@link OH_ArkUI_StyledStringKey}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetStyledKey(const OH_ArkUI_SpanStyle* spanStyle,
    OH_ArkUI_StyledStringKey* styledKey);
 
/**
 * @brief Sets the start position for the styled string object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param start Start position of the styled string style object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetStart(OH_ArkUI_SpanStyle* spanStyle, int32_t start);
 
/**
 * @brief Obtains the start position of the styled string object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param start Pointer to the start position of the styled string style object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetStart(const OH_ArkUI_SpanStyle* spanStyle, int32_t* start);
 
/**
 * @brief Sets the length for the styled string object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param length Length of the styled string style object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLength(OH_ArkUI_SpanStyle* spanStyle, int32_t length);
 
/**
 * @brief Obtains the length of the styled string object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param length Pointer to the length of the styled string style object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLength(const OH_ArkUI_SpanStyle* spanStyle, int32_t* length);
 
/**
 * @brief Sets the text font style for the styled string object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetTextStyle(OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_TextStyle* textStyle);
 
/**
 * @brief Obtains the text font style of the styled string object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param textStyle Pointer to the {@link OH_ArkUI_TextStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetTextStyle(const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_TextStyle* textStyle);
 
/**
 * @brief Defines a paragraph style.<br>        {@link OH_ArkUI_ParagraphStyle_Create} can be used to create a
 * paragraph style object.<br>        {@link OH_ArkUI_ParagraphStyle_Destroy} can be used to destroy the paragraph
 * style object.<br>        After the object is created, the **OH_ArkUI_ParagraphStyle_SetXXX** series APIs can be used
 * to set the specific styles that take effect. For example, you can use {@link OH_ArkUI_ParagraphStyle_SetTextAlign}
 * to set a text alignment method.
 *
 * @since 24
 */
typedef struct OH_ArkUI_ParagraphStyle OH_ArkUI_ParagraphStyle;
 
/**
 * @brief Sets the paragraph style for the styled string object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetParagraphStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_ParagraphStyle* paragraphStyle);
 
/**
 * @brief Obtains the paragraph style of the styled string object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetParagraphStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_ParagraphStyle* paragraphStyle);
 
/**
 * @brief Defines a gesture style.
 * {@link OH_ArkUI_GestureStyle_Create} can be used to create a gesture style object.
 * {@link OH_ArkUI_GestureStyle_Destroy} can be used to destroy the gesture style object.<br>
 * After the object is created, the **OH_ArkUI_GestureStyle_RegisterOnXXXCallback** series APIs can be used to
 * register specific event callbacks. For example, you can use {@link OH_ArkUI_GestureStyle_RegisterOnClickCallback} to
 * register a click event callback.
 *
 * @since 24
 */
typedef struct OH_ArkUI_GestureStyle OH_ArkUI_GestureStyle;
 
/**
 * @brief Sets the gesture style for the styled string object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param gestureStyle Pointer to the {@link OH_ArkUI_GestureStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetGestureStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_GestureStyle* gestureStyle);
 
/**
 * @brief Obtains the gesture style of the styled string object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param gestureStyle Pointer to the {@link OH_ArkUI_GestureStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetGestureStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_GestureStyle* gestureStyle);
 
/**
 * @brief Defines a text shadow style.<br>        {@link OH_ArkUI_TextShadowStyle_Create} can be used to create a text
 * shadow style object.<br>        {@link OH_ArkUI_TextShadowStyle_Destroy} can be used to destroy the text shadow
 * style object.<br>        After the object is created, {@link OH_ArkUI_TextShadowStyle_SetTextShadow} can be used to
 * set a style.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextShadowStyle OH_ArkUI_TextShadowStyle;
 
/**
 * @brief Sets the text shadow style for the styled string object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param textShadowStyle Pointer to the {@link OH_ArkUI_TextShadowStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetTextShadowStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_TextShadowStyle* textShadowStyle);
 
/**
 * @brief Obtains the text shadow style of the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param textShadowStyle Pointer to the {@link OH_ArkUI_TextShadowStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetTextShadowStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_TextShadowStyle* textShadowStyle);
 
/**
 * @brief Defines a text decoration style.<br>        {@link OH_ArkUI_DecorationStyle_Create} can be used to create a
 * text decoration style object.<br>        {@link OH_ArkUI_DecorationStyle_Destroy} can be used to destroy the text
 * decoration style object.<br>        After the object is created, the **OH_ArkUI_DecorationStyle_SetXXX** series APIs
 * can be used to set the specific styles that take effect. For example, you can use
 * {@link OH_ArkUI_DecorationStyle_SetTextDecorationType} to set the decoration type.
 *
 * @since 24
 */
typedef struct OH_ArkUI_DecorationStyle OH_ArkUI_DecorationStyle;
 
/**
 * @brief Sets the text decorative line style for the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param decorationStyle Pointer to the {@link OH_ArkUI_DecorationStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetDecorationStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_DecorationStyle* decorationStyle);
 
/**
 * @brief Obtains the text decorative line style of the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param decorationStyle Pointer to the {@link OH_ArkUI_DecorationStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetDecorationStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_DecorationStyle* decorationStyle);
 
/**
 * @brief Defines a baseline offset style.<br>        {@link OH_ArkUI_BaselineOffsetStyle_Create} can be used to create
 * a baseline offset style object.<br>        {@link OH_ArkUI_BaselineOffsetStyle_Destroy} can be used to destroy the
 * baseline offset style object.<br>        After the object is created,
 * {@link OH_ArkUI_BaselineOffsetStyle_SetBaselineOffset} can be used to set a baseline offset.
 *
 * @since 24
 */
typedef struct OH_ArkUI_BaselineOffsetStyle OH_ArkUI_BaselineOffsetStyle;

/**
 * @brief Sets the baseline offset style for the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param baselineOffsetStyle Pointer to the {@link OH_ArkUI_BaselineOffsetStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetBaselineOffsetStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle);

/**
 * @brief Obtains the baseline offset style of the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param baselineOffsetStyle Pointer to the {@link OH_ArkUI_BaselineOffsetStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetBaselineOffsetStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle);
 
/**
 * @brief Defines a letter spacing style.<br>        {@link OH_ArkUI_LetterSpacingStyle_Create} can be used to create a
 * letter spacing style object.<br>        {@link OH_ArkUI_LetterSpacingStyle_Destroy} can be used to destroy the
 * letter spacing style object.<br>        After the object is created,
 * {@link OH_ArkUI_LetterSpacingStyle_SetLetterSpacing} can be used to set letter spacing.
 *
 * @since 24
 */
typedef struct OH_ArkUI_LetterSpacingStyle OH_ArkUI_LetterSpacingStyle;
 
/**
 * @brief Sets the letter spacing style for the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param letterSpacingStyle Pointer to the {@link OH_ArkUI_LetterSpacingStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLetterSpacingStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_LetterSpacingStyle* letterSpacingStyle);
 
/**
 * @brief Obtains the letter spacing style of the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param letterSpacingStyle Pointer to the {@link OH_ArkUI_LetterSpacingStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLetterSpacingStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_LetterSpacingStyle* letterSpacingStyle);
 
/**
 * @brief Defines a line height style.<br>        {@link OH_ArkUI_LineHeightStyle_Create} can be used to create a line
 * height style object.<br>        {@link OH_ArkUI_LineHeightStyle_Destroy} can be used to destroy the line height
 * style object.<br>        After the object is created, {@link OH_ArkUI_LineHeightStyle_SetLineHeight} can be used to
 * set fixed line height.<br>        Since API version 26.0.0, {@link OH_ArkUI_LineHeightStyle_SetLineHeightMultiple}
 * can be used to set the line height multiplier after the object is created.
 *
 * @since 24
 */
typedef struct OH_ArkUI_LineHeightStyle OH_ArkUI_LineHeightStyle;
 
/**
 * @brief Sets the line height style for the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param lineHeightStyle Pointer to the {@link OH_ArkUI_LineHeightStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLineHeightStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_LineHeightStyle* lineHeightStyle);
 
/**
 * @brief Obtains the line height style of the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param lineHeightStyle Pointer to the {@link OH_ArkUI_LineHeightStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLineHeightStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_LineHeightStyle* lineHeightStyle);
 
/**
 * @brief Defines a URL style.<br>
 * {@link OH_ArkUI_UrlStyle_Create} can be used to create a URL style object.
 * {@link OH_ArkUI_UrlStyle_Destroy} can be used to destroy the URL style object.
 * After the object is created, {@link OH_ArkUI_UrlStyle_SetUrl} can be used to set a URL.
 *
 * @since 24
 */
typedef struct OH_ArkUI_UrlStyle OH_ArkUI_UrlStyle;
 
/**
 * @brief Sets the URL style for the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param urlStyle Pointer to the {@link OH_ArkUI_UrlStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetUrlStyle(OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_UrlStyle* urlStyle);
 
/**
 * @brief Obtains the URL style of the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param urlStyle Pointer to the {@link OH_ArkUI_UrlStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetUrlStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_UrlStyle* urlStyle);
 
/**
 * @brief Defines a background color style.<br>        {@link OH_ArkUI_BackgroundColorStyle_Create} can be used to
 * create a background color style object.<br>        {@link OH_ArkUI_BackgroundColorStyle_Destroy} can be used to
 * destroy the background color style object.<br>        After the object is created,
 * {@link OH_ArkUI_BackgroundColorStyle_SetColor} and {@link OH_ArkUI_BackgroundColorStyle_SetRadius} can be used to
 * set the background color and rounded corners.
 *
 * @since 24
 */
typedef struct OH_ArkUI_BackgroundColorStyle OH_ArkUI_BackgroundColorStyle;
 
/**
 * @brief Sets the background color style for the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param backgroundColorStyle Pointer to the {@link OH_ArkUI_BackgroundColorStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetBackgroundColorStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_BackgroundColorStyle* backgroundColorStyle);
 
/**
 * @brief Obtains the background color style of the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param backgroundColorStyle Pointer to the {@link OH_ArkUI_BackgroundColorStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetBackgroundColorStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_BackgroundColorStyle* backgroundColorStyle);
 
/**
 * @brief Defines a user data span style.<br>        {@link OH_ArkUI_UserDataSpan_Create} can be used to create a user
 * data span style object.<br>        {@link OH_ArkUI_UserDataSpan_Destroy} can be used to destroy the user data span
 * style object.<br>        After the object is created, {@link OH_ArkUI_UserDataSpan_SetUserData} can be used to bind
 * user data.
 *
 * @since 24
 */
typedef struct OH_ArkUI_UserDataSpan OH_ArkUI_UserDataSpan;
 
/**
 * @brief Sets the user data span style for the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param userDataSpan Pointer to the {@link OH_ArkUI_UserDataSpan} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetUserDataSpan(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_UserDataSpan* userDataSpan);
 
/**
 * @brief Obtains the user data span style of the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param userDataSpan Pointer to the {@link OH_ArkUI_UserDataSpan} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetUserDataSpan(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_UserDataSpan* userDataSpan);
 
/**
 * @brief Sets the custom span style for the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param customSpan Pointer to the {@link OH_ArkUI_CustomSpan} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetCustomSpan(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_CustomSpan* customSpan);
 
/**
 * @brief Obtains the custom span style of the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param customSpan Pointer to the {@link OH_ArkUI_CustomSpan} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetCustomSpan(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_CustomSpan* customSpan);
 
/**
 * @brief Sets the image style for the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetImageAttachment(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_ImageAttachment* imageAttachment);
 
/**
 * @brief Obtains the image style of the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetImageAttachment(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_ImageAttachment* imageAttachment);
 
/**
 * @brief Defines the custom drawing information for paragraph indentation.<br>
 * {@link OH_ArkUI_LeadingMarginSpanDrawInfo_Create} can be used to create a custom drawing information object for
 * paragraph indentation.<br>        {@link OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy} can be used to destroy the
 * custom drawing information object for paragraph indentation.<br>        This object is used to provide the drawing
 * context information of the current line in the callback function registered by
 * {@link OH_ArkUI_ParagraphStyle_RegisterOnDrawLeadingMarginCallback}.
 *
 * @since 24
 */
typedef struct OH_ArkUI_LeadingMarginSpanDrawInfo OH_ArkUI_LeadingMarginSpanDrawInfo;
 
/**
 * @brief Creates an {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @since 24
 */
OH_ArkUI_LeadingMarginSpanDrawInfo* OH_ArkUI_LeadingMarginSpanDrawInfo_Create();
 
/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 *
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @since 24
 */
void OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo);
 
/**
 * @brief Sets the horizontal offset of the current line relative to the component in the custom drawing information
 * object for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param x Horizontal offset of the current line relative to the component, in px.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetX(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float x);
 
/**
 * @brief Obtains the horizontal offset of the current line relative to the component in the custom drawing information
 * object for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param x Pointer to the horizontal offset of the current line relative to the component, in px.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetX(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float* x);
 
/**
 * @brief Sets the distance between the top of a line and the top edge of the component in the custom drawing
 * information object for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param top Distance between the top of a line and the top edge of the component, in px.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetTop(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float top);
 
/**
 * @brief Obtains the distance between the top of a line and the top edge of the component in the custom drawing
 * information object for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param top Pointer to the distance between the top of a line and the top edge of the component, in px.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetTop(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float* top);
 
/**
 * @brief Sets the distance between the bottom of a line and the top edge of the component in the custom drawing
 * information object for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param bottom Distance between the bottom of a line and the top edge of the component, in px.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetBottom(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float bottom);
 
/**
 * @brief Obtains the distance between the bottom of a line and the top edge of the component in the custom drawing
 * information object for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param bottom Pointer to the distance between the bottom of a line and the top edge of the component, in px.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetBottom(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float* bottom);
 
/**
 * @brief Sets the distance between the baseline of the current line and the top edge of the component in the custom
 * drawing information object for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param baseline Distance between the baseline of the current line and the top edge of the component, in px.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetBaseline(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float baseline);
 
/**
 * @brief Obtains the distance between the baseline of the current line and the top edge of the component in the custom
 * drawing information object for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param baseline Pointer to the distance between the baseline of the current line and the top edge of the component,
 *     in px.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetBaseline(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float* baseline);
 
/**
 * @brief Sets the text direction in the custom drawing information object for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param direction Text direction. The value is an enumerated value of {@link ArkUI_TextDirection}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetTextDirection(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    ArkUI_TextDirection direction);
 
/**
 * @brief Obtains the text direction in the custom drawing information object for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param direction Pointer to the text direction. The value is an enumerated value of {@link ArkUI_TextDirection}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetTextDirection(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    ArkUI_TextDirection* direction);
 
/**
 * @brief Sets the start index of the current line in the custom drawing information object for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param start Start index of the current line.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetStart(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    uint32_t start);
 
/**
 * @brief Obtains the start index of the current line in the custom drawing information object for paragraph
 * indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param start Pointer to the start index of the current line.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetStart(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    uint32_t* start);
 
/**
 * @brief Sets the end index of the current line in the custom drawing information object for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param end End index of the current line.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetEnd(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, uint32_t end);
 
/**
 * @brief Obtains the end index of the current line in the custom drawing information object for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param end Pointer to the end index of the current line.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetEnd(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    uint32_t* end);
 
/**
 * @brief Sets whether the current line is the first line of the paragraph in the custom drawing information object for
 * paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param first Whether the current line is the first line of the paragraph. **true** indicates the first line, and **
 *     false** indicates the opposite.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetFirst(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, bool first);
 
/**
 * @brief Obtains whether the current line is the first line of the paragraph in the custom drawing information object
 * for paragraph indentation.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the {@link OH_ArkUI_LeadingMarginSpanDrawInfo} object.
 * @param first Pointer to the **first** parameter indicating whether the current line is the first line of the
 *     paragraph. **true** indicates the first line, and **false** indicates the opposite.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetFirst(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    bool* first);
 
/**
 * @brief Creates an {@link OH_ArkUI_ParagraphStyle} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_ParagraphStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @since 24
 */
OH_ArkUI_ParagraphStyle* OH_ArkUI_ParagraphStyle_Create();
 
/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_ParagraphStyle} object.
 *
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @since 24
 */
void OH_ArkUI_ParagraphStyle_Destroy(OH_ArkUI_ParagraphStyle* paragraphStyle);
 
/**
 * @brief Sets the horizontal text alignment method in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param align Horizontal text alignment method. The value is an enumerated value of {@link ArkUI_TextAlignment}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextAlign(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextAlignment align);
 
/**
 * @brief Obtains the horizontal text alignment method in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param align Pointer to the horizontal text alignment method. The value is an enumerated value of
 *     {@link ArkUI_TextAlignment}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextAlign(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextAlignment* align);
 
/**
 * @brief Sets the first-line text indentation in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param textIndent First-line indentation value, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextIndent(OH_ArkUI_ParagraphStyle* paragraphStyle, float textIndent);
 
/**
 * @brief Obtains the first-line text indentation in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param textIndent Pointer to the first-line indentation value, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextIndent(const OH_ArkUI_ParagraphStyle* paragraphStyle, float* textIndent);
 
/**
 * @brief Sets the maximum number of lines in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param maxLines Maximum number of lines.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetMaxLines(OH_ArkUI_ParagraphStyle* paragraphStyle, int32_t maxLines);
 
/**
 * @brief Obtains the maximum number of lines in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param maxLines Pointer to the maximum number of lines.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetMaxLines(const OH_ArkUI_ParagraphStyle* paragraphStyle, int32_t* maxLines);
 
/**
 * @brief Sets the display mode when the paragraph is too long in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param overflow Display mode when the paragraph is too long. The value is an enumerated value of
 *     {@link ArkUI_TextOverflow}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetOverflow(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextOverflow overflow);
 
/**
 * @brief Obtains the display mode when the paragraph is too long in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param overflow Pointer to the display mode when the paragraph is too long. The value is an enumerated value of
 *     {@link ArkUI_TextOverflow}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetOverflow(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextOverflow* overflow);
 
/**
 * @brief Sets the word breaking rule in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param wordBreak Word breaking rule. The value is an enumerated value of {@link ArkUI_WordBreak}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetWordBreak(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_WordBreak wordBreak);
 
/**
 * @brief Obtains the word breaking rule in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param wordBreak Pointer to the word breaking rule. The value is an enumerated value of {@link ArkUI_WordBreak}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetWordBreak(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_WordBreak* wordBreak);
 
/**
 * @brief Sets the PixelMap for paragraph indentation in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param pixelmap Pointer to the PixelMap for paragraph indentation.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLeadingMarginPixelMap(OH_ArkUI_ParagraphStyle* paragraphStyle,
    struct OH_PixelmapNative* pixelmap);
 
/**
 * @brief Obtains the PixelMap for paragraph indentation in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param pixelmap Double pointer to the PixelMap for paragraph indentation.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLeadingMarginPixelMap(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    struct OH_PixelmapNative** pixelmap);
 
/**
 * @brief Sets the width for paragraph indentation in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param width Width for paragraph indentation, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLeadingMarginWidth(OH_ArkUI_ParagraphStyle* paragraphStyle, uint32_t width);
 
/**
 * @brief Obtains the width for paragraph indentation in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param width Pointer to the width for paragraph indentation, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLeadingMarginWidth(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t* width);
 
/**
 * @brief Sets the height for paragraph indentation in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param height Height for paragraph indentation, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLeadingMarginHeight(OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t height);
 
/**
 * @brief Obtains the height for paragraph indentation in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param height Pointer to the height for paragraph indentation, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLeadingMarginHeight(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t* height);
 
/**
 * @brief Sets the paragraph spacing in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param paragraphSpacing Paragraph spacing, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetParagraphSpacing(OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t paragraphSpacing);
 
/**
 * @brief Obtains the paragraph spacing in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param paragraphSpacing Pointer to the paragraph spacing, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetParagraphSpacing(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t* paragraphSpacing);
 
/**
 * @brief Sets the vertical text alignment method in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param verticalAlignment Vertical text alignment method. The value is an enumerated value of
 *     {@link ArkUI_TextVerticalAlignment}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextVerticalAlign(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextVerticalAlignment verticalAlignment);
 
/**
 * @brief Obtains the vertical text alignment method in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param verticalAlignment Pointer to the vertical text alignment method. The value is an enumerated value of
 *     {@link ArkUI_TextVerticalAlignment}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextVerticalAlign(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextVerticalAlignment* verticalAlignment);
 
/**
 * @brief Sets the callback function triggered when the paragraph indentation is drawn in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param onDraw The callback function for drawing leading margin.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_RegisterOnDrawLeadingMarginCallback(OH_ArkUI_ParagraphStyle* paragraphStyle,
    void(*onDraw)(ArkUI_DrawContext* context, OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo));
 
/**
 * @brief Sets the callback function triggered when the paragraph indentation distance is obtained in the paragraph
 * style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param leadingMargin The callback function for obtaining the indentation distance of a text paragraph.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_RegisterOnGetLeadingMarginCallback(OH_ArkUI_ParagraphStyle* paragraphStyle,
    float(*leadingMargin)());
 
/**
 * @brief Sets the text direction in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param textDirection Text direction. The value is an enumerated value of {@link ArkUI_TextDirection}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextDirection(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextDirection textDirection);
 
/**
 * @brief Obtains the text direction in the paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the {@link OH_ArkUI_ParagraphStyle} object.
 * @param textDirection Pointer to the text direction. The value is an enumerated value of {@link ArkUI_TextDirection}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextDirection(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextDirection* textDirection);

/**
 * @brief Creates an {@link OH_ArkUI_GestureStyle} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_GestureStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_GestureStyle</b> object.
 * @since 24
 */
OH_ArkUI_GestureStyle* OH_ArkUI_GestureStyle_Create();

/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_GestureStyle} object.
 *
 * @param gestureStyle Pointer to the {@link OH_ArkUI_GestureStyle} object.
 * @since 24
 */
void OH_ArkUI_GestureStyle_Destroy(OH_ArkUI_GestureStyle* gestureStyle);

/**
 * @brief Sets the click event callback in the event gesture style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param gestureStyle Pointer to the {@link OH_ArkUI_GestureStyle} object.
 * @param onClick The callback of click event.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_GestureStyle_RegisterOnClickCallback(
    OH_ArkUI_GestureStyle* gestureStyle, void(*onClick)(ArkUI_NodeEvent*));

/**
 * @brief Sets the long-pressing event callback in the event gesture style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param gestureStyle Pointer to the {@link OH_ArkUI_GestureStyle} object.
 * @param onLongPress The callback of long press event.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_GestureStyle_RegisterOnLongPressCallback(
    OH_ArkUI_GestureStyle* gestureStyle, void(*onLongPress)(ArkUI_GestureEvent*));

/**
 * @brief Sets the touch event callback in the event gesture style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param gestureStyle Pointer to the {@link OH_ArkUI_GestureStyle} object.
 * @param onTouch The callback of touch event.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_GestureStyle_RegisterOnTouchCallback(
    OH_ArkUI_GestureStyle* gestureStyle, void(*onTouch)(ArkUI_NodeEvent*));

/**
 * @brief Creates an {@link OH_ArkUI_TextShadowStyle} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_TextShadowStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_TextShadowStyle</b> object.
 * @since 24
 */
OH_ArkUI_TextShadowStyle* OH_ArkUI_TextShadowStyle_Create();

/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_TextShadowStyle} object.
 *
 * @param textShadowStyle Pointer to the {@link OH_ArkUI_TextShadowStyle} object.
 * @since 24
 */
void OH_ArkUI_TextShadowStyle_Destroy(OH_ArkUI_TextShadowStyle* textShadowStyle);

/**
 * @brief Sets the text shadow options for the text shadow style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textShadowStyle Pointer to the {@link OH_ArkUI_TextShadowStyle} object.
 * @param options Double pointer to the text shadow options, which points to an array of the
 *     {@link OH_ArkUI_ShadowOptions} object.
 * @param length Length of the text shadow options.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextShadowStyle_SetTextShadow(OH_ArkUI_TextShadowStyle* textShadowStyle,
    const OH_ArkUI_ShadowOptions** options, uint32_t length);

/**
 * @brief Obtains the text shadow options of the text shadow style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textShadowStyle Pointer to the {@link OH_ArkUI_TextShadowStyle} object.
 * @param shadowOptions Double pointer to the text shadow options, which points to an array of the
 *     {@link OH_ArkUI_ShadowOptions} object.
 * @param shadowOptionsSize Size of the shadow option buffer.
 * @param writeLength Pointer to the number of actual text shadow options in the text shadow style.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *     Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextShadowStyle_GetTextShadow(const OH_ArkUI_TextShadowStyle* textShadowStyle,
    OH_ArkUI_ShadowOptions** shadowOptions, uint32_t shadowOptionsSize, uint32_t* writeLength);

/**
 * @brief Creates an {@link OH_ArkUI_DecorationStyle} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_DecorationStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @since 24
 */
OH_ArkUI_DecorationStyle* OH_ArkUI_DecorationStyle_Create();

/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_DecorationStyle} object.
 *
 * @param decorationStyle Pointer to the {@link OH_ArkUI_DecorationStyle} object.
 * @since 24
 */
void OH_ArkUI_DecorationStyle_Destroy(OH_ArkUI_DecorationStyle* decorationStyle);
 
/**
 * @brief Sets the decoration type for the text decorative line style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the {@link OH_ArkUI_DecorationStyle} object.
 * @param type Type of the text decorative line. The value is an enumerated value of {@link ArkUI_TextDecorationType}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetTextDecorationType(OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationType type);
 
/**
 * @brief Obtains the decoration type of the text decorative line style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the {@link OH_ArkUI_DecorationStyle} object.
 * @param type Pointer to the type of the text decorative line. The value is an enumerated value of
 *     {@link ArkUI_TextDecorationType}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetTextDecorationType(const OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationType* type);
 
/**
 * @brief Sets the decoration color for the text decorative line style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the {@link OH_ArkUI_DecorationStyle} object.
 * @param color Decoration color, in 0xARGB format.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetColor(OH_ArkUI_DecorationStyle* decorationStyle, uint32_t color);
 
/**
 * @brief Obtains the decoration color of the text decorative line style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the {@link OH_ArkUI_DecorationStyle} object.
 * @param color Pointer to the decoration color, in 0xARGB format.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetColor(const OH_ArkUI_DecorationStyle* decorationStyle, uint32_t* color);
 
/**
 * @brief Sets the decoration style for the text decorative line style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the {@link OH_ArkUI_DecorationStyle} object.
 * @param style Style of the text decorative line. The value is an enumerated value of
 *     {@link ArkUI_TextDecorationStyle}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetTextDecorationStyle(OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationStyle style);
 
/**
 * @brief Obtains the decoration style of the text decorative line style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the {@link OH_ArkUI_DecorationStyle} object.
 * @param style Pointer to the style of the text decorative line. The value is an enumerated value of
 *     {@link ArkUI_TextDecorationStyle}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetTextDecorationStyle(const OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationStyle* style);
 
/**
 * @brief Sets the thickness scaling factor of the text decorative line style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the {@link OH_ArkUI_DecorationStyle} object.
 * @param thicknessScale Scaling factor of the decorative line thickness. The value range is [0, +∞).
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetThicknessScale(OH_ArkUI_DecorationStyle* decorationStyle,
    float thicknessScale);
 
/**
 * @brief Obtains the thickness scaling factor of the text decorative line style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the {@link OH_ArkUI_DecorationStyle} object.
 * @param thicknessScale Pointer to the scaling factor of the decorative line thickness. The value range is [0, +∞).
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetThicknessScale(const OH_ArkUI_DecorationStyle* decorationStyle,
    float* thicknessScale);
 
/**
 * @brief Sets whether to enable the display of multiple decorative lines in the text decorative line style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the {@link OH_ArkUI_DecorationStyle} object.
 * @param enableMultiType Whether to enable the display of multiple decorative lines. **true** to enable; **false**
 *     otherwise.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetEnableMultiType(
    OH_ArkUI_DecorationStyle* decorationStyle, bool enableMultiType);
 
/**
 * @brief Obtains whether the display of multiple decorative lines is enabled in the text decorative line style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the {@link OH_ArkUI_DecorationStyle} object.
 * @param enableMultiType Pointer to the **enableMultiType** parameter indicating whether the display of multiple
 *     decorative lines is enabled. **true** means the display is enabled; **false** otherwise.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetEnableMultiType(
    const OH_ArkUI_DecorationStyle* decorationStyle, bool* enableMultiType);
 
/**
 * @brief Creates an {@link OH_ArkUI_BaselineOffsetStyle} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_BaselineOffsetStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_BaselineOffsetStyle</b> object.
 * @since 24
 */
OH_ArkUI_BaselineOffsetStyle* OH_ArkUI_BaselineOffsetStyle_Create();
 
/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_BaselineOffsetStyle} object.
 *
 * @param baselineOffsetStyle Pointer to the {@link OH_ArkUI_BaselineOffsetStyle} object.
 * @since 24
 */
void OH_ArkUI_BaselineOffsetStyle_Destroy(OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle);
 
/**
 * @brief Sets the baseline offset.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param baselineOffsetStyle Pointer to the {@link OH_ArkUI_BaselineOffsetStyle} object.
 * @param baselineOffset Baseline offset, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BaselineOffsetStyle_SetBaselineOffset(
    OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle, float baselineOffset);
 
/**
 * @brief Obtains the baseline offset.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param baselineOffsetStyle Pointer to the {@link OH_ArkUI_BaselineOffsetStyle} object.
 * @param baselineOffset Pointer to the baseline offset, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BaselineOffsetStyle_GetBaselineOffset(
    const OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle, float* baselineOffset);
 
/**
 * @brief Creates an {@link OH_ArkUI_LetterSpacingStyle} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_LetterSpacingStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_LetterSpacingStyle</b> object.
 * @since 24
 */
OH_ArkUI_LetterSpacingStyle* OH_ArkUI_LetterSpacingStyle_Create();
 
/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_LetterSpacingStyle} object.
 *
 * @param letterSpacingStyle Pointer to the {@link OH_ArkUI_LetterSpacingStyle} object.
 * @since 24
 */
void OH_ArkUI_LetterSpacingStyle_Destroy(OH_ArkUI_LetterSpacingStyle* letterSpacingStyle);
 
/**
 * @brief Sets the letter spacing.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param letterSpacingStyle Pointer to the {@link OH_ArkUI_LetterSpacingStyle} object.
 * @param letterSpacing Letter spacing value, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LetterSpacingStyle_SetLetterSpacing(
    OH_ArkUI_LetterSpacingStyle* letterSpacingStyle, float letterSpacing);
 
/**
 * @brief Obtains the letter spacing.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param letterSpacingStyle Pointer to the {@link OH_ArkUI_LetterSpacingStyle} object.
 * @param letterSpacing Pointer to the letter spacing value, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LetterSpacingStyle_GetLetterSpacing(
    const OH_ArkUI_LetterSpacingStyle* letterSpacingStyle, float* letterSpacing);
 
/**
 * @brief Creates an {@link OH_ArkUI_LineHeightStyle} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_LineHeightStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_LineHeightStyle</b> object.
 * @since 24
 */
OH_ArkUI_LineHeightStyle* OH_ArkUI_LineHeightStyle_Create();
 
/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_LineHeightStyle} object.
 *
 * @param lineHeightStyle Pointer to the {@link OH_ArkUI_LineHeightStyle} object.
 * @since 24
 */
void OH_ArkUI_LineHeightStyle_Destroy(OH_ArkUI_LineHeightStyle* lineHeightStyle);
 
/**
 * @brief Sets the line height.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param lineHeightStyle Pointer to the {@link OH_ArkUI_LineHeightStyle} object.
 * @param lineHeight Fixed line height, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LineHeightStyle_SetLineHeight(OH_ArkUI_LineHeightStyle* lineHeightStyle,
    float lineHeight);
 
/**
 * @brief Obtains the line height.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param lineHeightStyle Pointer to the {@link OH_ArkUI_LineHeightStyle} object.
 * @param lineHeight Pointer to the fixed line height, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LineHeightStyle_GetLineHeight(const OH_ArkUI_LineHeightStyle* lineHeightStyle,
    float* lineHeight);
 
/**
 * @brief Sets a line height multiplier.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param lineHeightStyle Pointer to the {@link OH_ArkUI_LineHeightStyle} object.
 * @param lineHeightMultiple Line height multiplier. The value range is [0, +∞).
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LineHeightStyle_SetLineHeightMultiple(OH_ArkUI_LineHeightStyle* lineHeightStyle,
    float lineHeightMultiple);
 
/**
 * @brief Obtains the line height multiplier.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param lineHeightStyle Pointer to the {@link OH_ArkUI_LineHeightStyle} object.
 * @param lineHeightMultiple Pointer to the line height multiplier. The value range is [0, +∞).
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LineHeightStyle_GetLineHeightMultiple(const OH_ArkUI_LineHeightStyle* lineHeightStyle,
    float* lineHeightMultiple);
 
/**
 * @brief Defines a line spacing style.<br>        {@link OH_ArkUI_LineSpacingStyle_Create} can be used to create a
 * line spacing style object.<br>        {@link OH_ArkUI_LineSpacingStyle_Destroy} can be used to destroy the line
 * spacing style object.<br>        After the object is created, {@link OH_ArkUI_LineSpacingStyle_SetLineSpacing} can
 * be used to set a line spacing value.<br>        After the object is created,
 * {@link OH_ArkUI_LineSpacingStyle_SetOnlyBetweenLines} can be used to set whether the line spacing takes effect only
 * between lines.
 *
 * @since 26.0.0
 */
typedef struct OH_ArkUI_LineSpacingStyle OH_ArkUI_LineSpacingStyle;
 
/**
 * @brief Sets a line spacing style for the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param lineSpacingStyle Pointer to the {@link OH_ArkUI_LineSpacingStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLineSpacingStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_LineSpacingStyle* lineSpacingStyle);
 
/**
 * @brief Obtains the line spacing style of the styled string style object.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the {@link OH_ArkUI_SpanStyle} object.
 * @param lineSpacingStyle Pointer to the {@link OH_ArkUI_LineSpacingStyle} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLineSpacingStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_LineSpacingStyle* lineSpacingStyle);
 
/**
 * @brief Creates an {@link OH_ArkUI_LineSpacingStyle} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_LineSpacingStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_LineSpacingStyle</b> object.
 * @since 26.0.0
 */
OH_ArkUI_LineSpacingStyle* OH_ArkUI_LineSpacingStyle_Create();

/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_LineSpacingStyle} object.
 *
 * @param lineSpacingStyle Pointer to the {@link OH_ArkUI_LineSpacingStyle} object.
 * @since 26.0.0
 */
void OH_ArkUI_LineSpacingStyle_Destroy(OH_ArkUI_LineSpacingStyle* lineSpacingStyle);
 
/**
 * @brief Sets line spacing.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param lineSpacingStyle Pointer to the {@link OH_ArkUI_LineSpacingStyle} object.
 * @param lineSpacing Line spacing value, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LineSpacingStyle_SetLineSpacing(OH_ArkUI_LineSpacingStyle* lineSpacingStyle,
    float lineSpacing);
 
/**
 * @brief Queries the line spacing.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param lineSpacingStyle Pointer to the {@link OH_ArkUI_LineSpacingStyle} object.
 * @param lineSpacing Pointer to the line spacing value, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LineSpacingStyle_GetLineSpacing(const OH_ArkUI_LineSpacingStyle* lineSpacingStyle,
    float* lineSpacing);
 
/**
 * @brief Sets whether the line spacing takes effect only between lines.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param lineSpacingStyle Pointer to the {@link OH_ArkUI_LineSpacingStyle} object.
 * @param onlyBetweenLines Whether the line spacing takes effect only between lines. **true** indicates that the
 *     spacing is added only between lines, and no extra spacing is added above the first line or below the last line. *
 *     *false** indicates that the complete line spacing is added between all lines, above the first line, and below
 *     the last line.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LineSpacingStyle_SetOnlyBetweenLines(
    OH_ArkUI_LineSpacingStyle* lineSpacingStyle, bool onlyBetweenLines);
 
/**
 * @brief Checks whether the line spacing takes effect only between lines.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param lineSpacingStyle Pointer to the {@link OH_ArkUI_LineSpacingStyle} object.
 * @param onlyBetweenLines Pointer to the **onlyBetweenLines** parameter indicating whether the line spacing takes
 *     effect only between lines. **true** indicates that the spacing is added only between lines, and no extra spacing
 *     is added above the first line or below the last line. **false** indicates that the complete line spacing is
 *     added between all lines, above the first line, and below the last line.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LineSpacingStyle_GetOnlyBetweenLines(
    const OH_ArkUI_LineSpacingStyle* lineSpacingStyle, bool* onlyBetweenLines);
 
/**
 * @brief Creates an {@link OH_ArkUI_BackgroundColorStyle} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_BackgroundColorStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_BackgroundColorStyle</b> object.
 * @since 24
 */
OH_ArkUI_BackgroundColorStyle* OH_ArkUI_BackgroundColorStyle_Create();
 
/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_BackgroundColorStyle} object.
 *
 * @param style Pointer to the {@link OH_ArkUI_BackgroundColorStyle} object.
 * @since 24
 */
void OH_ArkUI_BackgroundColorStyle_Destroy(OH_ArkUI_BackgroundColorStyle* style);
 
/**
 * @brief Sets the background color for the background color style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param style Pointer to the {@link OH_ArkUI_BackgroundColorStyle} object.
 * @param color Background color, in 0xARGB format.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_SetColor(OH_ArkUI_BackgroundColorStyle* style, uint32_t color);
 
/**
 * @brief Obtains the background color of the background color style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param style Pointer to the {@link OH_ArkUI_BackgroundColorStyle} object.
 * @param color Pointer to the background color, in 0xARGB format.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_GetColor(const OH_ArkUI_BackgroundColorStyle* style, uint32_t* color);
 
/**
 * @brief Sets the background radii for the background color style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param style Pointer to the {@link OH_ArkUI_BackgroundColorStyle} object.
 * @param topLeft Radius of the upper left corner, in vp.
 * @param topRight Radius of the upper right corner, in vp.
 * @param bottomLeft Radius of the lower left corner, in vp.
 * @param bottomRight Radius of the lower right corner, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_SetRadius(OH_ArkUI_BackgroundColorStyle* style, float topLeft,
    float topRight, float bottomLeft, float bottomRight);
 
/**
 * @brief Obtains the background radii of the background color style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param style Pointer to the {@link OH_ArkUI_BackgroundColorStyle} object.
 * @param topLeft Pointer to the radius of the upper left corner, in vp.
 * @param topRight Pointer to the radius of the upper right corner, in vp.
 * @param bottomLeft Pointer to the radius of the lower left corner, in vp.
 * @param bottomRight Pointer to the radius of the lower right corner, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_GetRadius(const OH_ArkUI_BackgroundColorStyle* style, float* topLeft,
    float* topRight, float* bottomLeft, float* bottomRight);
 
/**
 * @brief Creates an {@link OH_ArkUI_UrlStyle} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_UrlStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_UrlStyle</b> object.
 * @since 24
 */
OH_ArkUI_UrlStyle* OH_ArkUI_UrlStyle_Create();
 
/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_UrlStyle} object.
 *
 * @param style Pointer to the {@link OH_ArkUI_UrlStyle} object.
 * @since 24
 */
void OH_ArkUI_UrlStyle_Destroy(OH_ArkUI_UrlStyle* style);
 
/**
 * @brief Sets the URL content for the URL style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param style Pointer to the {@link OH_ArkUI_UrlStyle} object.
 * @param url Pointer to the URL content.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_UrlStyle_SetUrl(OH_ArkUI_UrlStyle* style, const char* url);
 
/**
 * @brief Obtains the URL content of the URL style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param style Pointer to the {@link OH_ArkUI_UrlStyle} object.
 * @param buffer Pointer to the buffer for storing the URL content in the memory. You need to allocate the memory.
 * @param bufferSize Maximum number of characters that can be written to the buffer.
 * @param writeLength Pointer to the number of characters that are actually written to the buffer if
 *     {@link ARKUI_ERROR_CODE_NO_ERROR} is returned.
 *     <br>Pointer to the minimum length required for writing the entire string to the buffer if
 *     {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *     Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_UrlStyle_GetUrl(const OH_ArkUI_UrlStyle* style, char* buffer, int32_t bufferSize,
    int32_t* writeLength);
 
/**
 * @brief Creates an {@link OH_ArkUI_UserDataSpan} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_UserDataSpan_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_UserDataSpan</b> object.
 * @since 24
 */
OH_ArkUI_UserDataSpan* OH_ArkUI_UserDataSpan_Create();
 
/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_UserDataSpan} object.
 *
 * @param userDataSpan Pointer to the {@link OH_ArkUI_UserDataSpan} object.
 * @since 24
 */
void OH_ArkUI_UserDataSpan_Destroy(OH_ArkUI_UserDataSpan* userDataSpan);
 
/**
 * @brief Sets the user data in the user data span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param userDataSpan Pointer to the {@link OH_ArkUI_UserDataSpan} object.
 * @param userData Pointer to the user data. You need to manage the data lifecycle.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_UserDataSpan_SetUserData(OH_ArkUI_UserDataSpan* userDataSpan, void* userData);
 
/**
 * @brief Obtains the user data in the user data span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param userDataSpan Pointer to the {@link OH_ArkUI_UserDataSpan} object.
 * @param userData Double pointer to the user data.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_UserDataSpan_GetUserData(const OH_ArkUI_UserDataSpan* userDataSpan, void** userData);
 
/**
 * @brief Creates an {@link OH_ArkUI_CustomSpan} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_CustomSpan_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_CustomSpan</b> object.
 * @since 24
 */
OH_ArkUI_CustomSpan* OH_ArkUI_CustomSpan_Create();
 
/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_CustomSpan} object.
 *
 * @param customSpan Pointer to the {@link OH_ArkUI_CustomSpan} object.
 * @since 24
 */
void OH_ArkUI_CustomSpan_Destroy(OH_ArkUI_CustomSpan* customSpan);
 
/**
 * @brief Sets the callback function triggered when metrics are obtained for the custom span.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param customSpan Pointer to the {@link OH_ArkUI_CustomSpan} object.
 * @param onMeasure The callback function for measuring the size of custom span.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_CustomSpan_RegisterOnMeasureCallback(
    OH_ArkUI_CustomSpan* customSpan, ArkUI_CustomSpanMetrics*(*onMeasure)(float));
 
/**
 * @brief Registers the callback function triggered when the custom span is drawn.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param customSpan Pointer to the {@link OH_ArkUI_CustomSpan} object.
 * @param onDraw The callback function for drawing the custom span.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_CustomSpan_RegisterOnDrawCallback(
    OH_ArkUI_CustomSpan* customSpan, void(*onDraw)(ArkUI_DrawContext*, ArkUI_CustomSpanDrawInfo*));
 
/**
 * @brief Creates an {@link OH_ArkUI_ImageAttachment} object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_ImageAttachment_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @since 24
 */
OH_ArkUI_ImageAttachment* OH_ArkUI_ImageAttachment_Create();
 
/**
 * @brief Releases the memory occupied by the {@link OH_ArkUI_ImageAttachment} object.
 *
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @since 24
 */
void OH_ArkUI_ImageAttachment_Destroy(OH_ArkUI_ImageAttachment* imageAttachment);
 
/**
 * @brief Sets the image data source in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param pixelmap Pointer to the image data source.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetPixelMap(OH_ArkUI_ImageAttachment* imageAttachment,
    struct OH_PixelmapNative* pixelmap);
 
/**
 * @brief Obtains the image data source in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param pixelmap Double pointer to the image data source.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetPixelMap(const OH_ArkUI_ImageAttachment* imageAttachment,
    struct OH_PixelmapNative** pixelmap);
 
/**
 * @brief Sets the image resource address in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param resource Pointer to the image resource address.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetResource(OH_ArkUI_ImageAttachment* imageAttachment, const char* resource);
 
/**
 * @brief Obtains the image resource address in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param buffer Pointer to the buffer for storing the image resource address string in the memory. You need to
 *     allocate the memory.
 * @param bufferSize Buffer size.
 * @param writeLength Pointer to the length of the string actually written to the buffer if
 *     {@link ARKUI_ERROR_CODE_NO_ERROR} is returned.
 *     <br>Pointer to the minimum length required for writing the entire string to the buffer if
 *     {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *     Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetResource(const OH_ArkUI_ImageAttachment* imageAttachment,
    char* buffer, int32_t bufferSize, int32_t* writeLength);
 
/**
 * @brief Sets the image width in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param width Image width, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSizeWidth(OH_ArkUI_ImageAttachment* imageAttachment, float width);
 
/**
 * @brief Obtains the image width in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param width Pointer to the image width, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSizeWidth(const OH_ArkUI_ImageAttachment* imageAttachment, float* width);
 
/**
 * @brief Sets the image height in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param height Image height, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSizeHeight(OH_ArkUI_ImageAttachment* imageAttachment, float height);
 
/**
 * @brief Obtains the image height in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param height Pointer to the image height, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSizeHeight(const OH_ArkUI_ImageAttachment* imageAttachment, float* height);

/**
 * @brief Sets the image alignment method in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param verticalAlign Image alignment method. The value is an enumerated value of {@link ArkUI_ImageSpanAlignment}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetVerticalAlign(
    OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_ImageSpanAlignment verticalAlign);
 
/**
 * @brief Obtains the image alignment method in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param verticalAlign Pointer to the image alignment method. The value is an enumerated value of
 *     {@link ArkUI_ImageSpanAlignment}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetVerticalAlign(const OH_ArkUI_ImageAttachment* imageAttachment,
    ArkUI_ImageSpanAlignment* verticalAlign);
 
/**
 * @brief Sets the image scaling type in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param objectFit Image scaling type. The value is an enumerated value of {@link ArkUI_ObjectFit}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetObjectFit(
    OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_ObjectFit objectFit);
 
/**
 * @brief Obtains the image scaling type in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param objectFit Pointer to the image scaling type. The value is an enumerated value of {@link ArkUI_ObjectFit}.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetObjectFit(
    const OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_ObjectFit* objectFit);
 
/**
 * @brief Sets the image margin in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param margin Image margin, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetMargin(OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_Margin margin);
 
/**
 * @brief Obtains the image margin in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param margin Pointer to the image margin, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetMargin(const OH_ArkUI_ImageAttachment* imageAttachment,
    ArkUI_Margin* margin);
 
/**
 * @brief Sets the image padding in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param padding Image padding, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetPadding(OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_Margin padding);
 
/**
 * @brief Obtains the image padding in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param padding Pointer to the image padding, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetPadding(const OH_ArkUI_ImageAttachment* imageAttachment,
    ArkUI_Margin* padding);
 
/**
 * @brief Sets the image border radii in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param topLeft Radius of the upper left corner, in vp.
 * @param topRight Radius of the upper right corner, in vp.
 * @param bottomLeft Radius of the lower left corner, in vp.
 * @param bottomRight Radius of the lower right corner, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetBorderRadiuses(OH_ArkUI_ImageAttachment* imageAttachment,
    float topLeft, float topRight, float bottomLeft, float bottomRight);
 
/**
 * @brief Obtains the image border radii in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param topLeft Pointer to the radius of the upper left corner, in vp.
 * @param topRight Pointer to the radius of the upper right corner, in vp.
 * @param bottomLeft Pointer to the radius of the lower left corner, in vp.
 * @param bottomRight Pointer to the radius of the lower right corner, in vp.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetBorderRadiuses(const OH_ArkUI_ImageAttachment* imageAttachment,
    float* topLeft, float* topRight, float* bottomLeft, float* bottomRight);
 
/**
 * @brief Sets the image color filter in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param colorFilter Pointer to the image color filter.
 * @param size Size of the filter array.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetColorFilter(
    OH_ArkUI_ImageAttachment* imageAttachment, const float* colorFilter, uint32_t size);
 
/**
 * @brief Obtains the image color filter in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param colorFilter Double pointer to the buffer for storing the image color filter in the memory. You need to
 *     allocate the memory.
 * @param colorFilterSize Buffer size.
 * @param writeLength Pointer to the actual size of the image color filter array.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *     Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetColorFilter(const OH_ArkUI_ImageAttachment* imageAttachment,
    float** colorFilter, uint32_t colorFilterSize, uint32_t* writeLength);
 
/**
 * @brief Sets the image drawing color filter in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param drawingColorFilter Pointer to the image drawing color filter.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetDrawingColorFilter(
    OH_ArkUI_ImageAttachment* imageAttachment, const OH_Drawing_ColorFilter* drawingColorFilter);
 
/**
 * @brief Obtains the image drawing color filter in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param drawingColorFilter Pointer to the image drawing color filter.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetDrawingColorFilter(
    const OH_ArkUI_ImageAttachment* imageAttachment, OH_Drawing_ColorFilter* drawingColorFilter);
 
/**
 * @brief Sets whether to load the image synchronously in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param syncLoad Whether to load images synchronously. **true** to load synchronously; **false** to load
 *     asynchronously.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSyncLoad(OH_ArkUI_ImageAttachment* imageAttachment, bool syncLoad);
 
/**
 * @brief Obtains whether the image is loaded synchronously in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param syncLoad Pointer to the **syncLoad** parameter indicating whether the image is loaded synchronously. **true**
 *     indicates that the image is loaded synchronously; **false** indicates that the image is loaded asynchronously.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSyncLoad(const OH_ArkUI_ImageAttachment* imageAttachment, bool* syncLoad);
 
/**
 * @brief Sets whether to enable the enhanced SVG tag parsing feature in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param supportSvg Whether to enable the enhanced SVG tag parsing feature. **true** to enable, **false** otherwise.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSupportSvg(OH_ArkUI_ImageAttachment* imageAttachment, bool supportSvg);
 
/**
 * @brief Obtains whether the enhanced SVG tag parsing feature is enabled in the image style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the {@link OH_ArkUI_ImageAttachment} object.
 * @param supportSvg Pointer to the **supportSvg** parameter indicating whether the enhanced SVG tag parsing feature is
 *     enabled. **true** means the enhanced SVG tag parsing feature is enabled, and **false** means the opposite.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSupportSvg(const OH_ArkUI_ImageAttachment* imageAttachment,
    bool* supportSvg);

/**
 * @brief Obtains the range of the content to be replaced in the text change information.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param event Pointer to the {@link OH_ArkUI_TextEditorChangeEvent} object.
 * @param start Pointer to the start index of the range of the content to be replaced.
 * @param end Pointer to the end index of the range of the content to be replaced.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function params is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorChangeEvent_GetRangeBefore(const OH_ArkUI_TextEditorChangeEvent* event,
    uint32_t* start, uint32_t* end);

/**
 * @brief Obtains the styled string used for replacement in the text change information.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param event Pointer to the {@link OH_ArkUI_TextEditorChangeEvent} object.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function params is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorChangeEvent_GetReplacementStyledString(
    const OH_ArkUI_TextEditorChangeEvent* event, ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Obtains the styled string of the previewed content in the text change information.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param event Pointer to the {@link OH_ArkUI_TextEditorChangeEvent} object.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @return Returns the result code.
 *     Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function params is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorChangeEvent_GetPreviewStyledString(
    const OH_ArkUI_TextEditorChangeEvent* event, ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Defines the layout manager of text.
 *
 * @since 22
 */
typedef struct ArkUI_TextLayoutManager ArkUI_TextLayoutManager;

/**
 * @brief Dispose an object of the text layout manager.
 *
 * @param layoutManager Pointer to the ArkUI_TextLayoutManager object to be disposed.
 * @since 22
 */
void OH_ArkUI_TextLayoutManager_Dispose(ArkUI_TextLayoutManager* layoutManager);

/**
 * @brief Gets the line count.
 *
 * @param layoutManager Indicates the pointer to an <b>ArkUI_TextLayoutManager</b> object.
 * @param outLineCount Returns the line count.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetLineCount(ArkUI_TextLayoutManager* layoutManager, int32_t* outLineCount);

/**
 * @brief Gets the rects for range.
 *
 * @param layoutManager Indicates the pointer to an <b>ArkUI_TextLayoutManager</b> object.
 * @param start Indicates the start of range to set.
 * @param end Indicates the end of range to set.
 * @param widthStyle Indicates the width style to set.
 *     For details, see the enum <b>OH_Drawing_RectWidthStyle</b>.
 * @param heightStyle Indicates the height style to set.
 *     For details, see the enum <b>OH_Drawing_RectHeightStyle</b>.
 * @param outTextBoxes Returns the array of rects for range.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetRectsForRange(ArkUI_TextLayoutManager* layoutManager,
    int32_t start, int32_t end, OH_Drawing_RectWidthStyle widthStyle, OH_Drawing_RectHeightStyle heightStyle,
    OH_Drawing_TextBox** outTextBoxes);

/**
 * @brief Gets the glyph position at coordinate.
 *
 * @param layoutManager Indicates the pointer to an <b>ArkUI_TextLayoutManager</b> object.
 * @param dx Indicates the positionX of typography to set.
 * @param dy Indicates the positionY of typography to set.
 * @param outPos Returns the glyph position at coordinate.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetGlyphPositionAtCoordinate(
    ArkUI_TextLayoutManager* layoutManager, double dx, double dy, OH_Drawing_PositionAndAffinity** outPos);

/**
 * @brief Get line metrics information.
 *
 * @param layoutManager Indicates the pointer to a typography object <b>ArkUI_TextLayoutManager</b>.
 * @param lineNumber Indicates the number of line.
 * @param outMetrics Indicates the pointer to a line metrics object <b>OH_Drawing_LineMetrics</b>.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetLineMetrics(ArkUI_TextLayoutManager* layoutManager,
    int32_t lineNumber, OH_Drawing_LineMetrics* outMetrics);

/**
 * @brief Gets the character position at coordinate.
 *
 * @param layoutManager Indicates the pointer to an <b>ArkUI_TextLayoutManager</b> object.
 * @param dx Indicates the positionX of typography to set.
 * @param dy Indicates the positionY of typography to set.
 * @param outPos Returns the character position at coordinate.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinate(
    ArkUI_TextLayoutManager* layoutManager, double dx, double dy, OH_Drawing_PositionAndAffinity** outPos);

/**
 * @brief Get the glyph range produced by the specified range of characters.
 *
 * @param layoutManager Indicates the pointer to an <b>ArkUI_TextLayoutManager</b> object.
 * @param charRange The character range.
 * @param outGlyphRange The range of glyphs generated by charRange.
 * @param outActualCharRange If not null, specifies the actual character range that fully defines the returned
 *      glyph range, which may match or slightly exceed the requested range.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetGlyphRangeForCharacterRange(
    ArkUI_TextLayoutManager* layoutManager, OH_Drawing_Range* charRange,
    OH_Drawing_Range** outGlyphRange, OH_Drawing_Range** outActualCharRange);

/**
 * @brief Get the character range that maps to the glyphs in the given glyph range.
 *
 * @param layoutManager Indicates the pointer to an <b>ArkUI_TextLayoutManager</b> object.
 * @param glyphRange The glyph range.
 * @param outCharRange The range of characters generated by glyphRange.
 * @param outActualGlyphRange If not null, specifies the full glyph range generated by the returned character range,
 *      which may match or slightly exceed the requested glyph range.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetCharacterRangeForGlyphRange(
    ArkUI_TextLayoutManager* layoutManager, OH_Drawing_Range* glyphRange,
    OH_Drawing_Range** outCharRange, OH_Drawing_Range** outActualGlyphRange);

/**
 * @brief Set linear gradient of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param linearGradient Pointer to the <b>OH_ArkUI_LinearGradientOptions</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLinearGradient(
    OH_ArkUI_ParagraphStyle* paragraphStyle, const OH_ArkUI_LinearGradientOptions* linearGradient);

/**
 * @brief Get linear gradient of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param linearGradient Pointer to the <b>OH_ArkUI_LinearGradientOptions</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLinearGradient(
    const OH_ArkUI_ParagraphStyle* paragraphStyle, OH_ArkUI_LinearGradientOptions* linearGradient);

/**
 * @brief Set radial gradient of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param radialGradient Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetRadialGradient(
    OH_ArkUI_ParagraphStyle* paragraphStyle, const OH_ArkUI_RadialGradientOptions* radialGradient);

/**
 * @brief Get radial gradient of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param radialGradient Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetRadialGradient(
    const OH_ArkUI_ParagraphStyle* paragraphStyle, OH_ArkUI_RadialGradientOptions* radialGradient);

/**
 * @brief Set tail indents of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param tailIndents The tail indent values, in vp. When size is 1, all lines share the same tail indent.
 *      When size > 1, the i-th value specifies the tail indent for the i-th line. If the number of text
 *      lines exceeds size, the last value is used for the remaining lines.
 * @param size The number of tail indent values.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTailIndents(
    OH_ArkUI_ParagraphStyle* paragraphStyle, const float* tailIndents, uint32_t size);

/**
 * @brief Get tail indents of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param tailIndents The tail indent values, in vp.
 * @param tailIndentsSize The size of the tailIndents buffer provided by the caller.
 * @param writeLength The actual number of tail indent values written to the buffer.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *         Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTailIndents(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    float** tailIndents, uint32_t tailIndentsSize, uint32_t* writeLength);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_STYLED_STRING_H
/** @} */

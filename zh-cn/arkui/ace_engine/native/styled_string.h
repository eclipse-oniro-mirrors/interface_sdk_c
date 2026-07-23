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
 * @brief 在Native侧定义{@link ArkUI_NodeType}为ARKUI_NODE_TEXT的组件的文本样式和文本布局管理器。
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
 * @brief 定义文本组件支持的样式化字符串数据对象。
 *
 * @since 12
 */
typedef struct ArkUI_StyledString ArkUI_StyledString;

/**
 * @brief 创建指向ArkUI_StyledString对象的指针。
 *
 * @param style 指向OH_Drawing_TypographyStyle的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param collection 指向OH_Drawing_FontCollection的指针，由{@link OH_Drawing_CreateFontCollection}获取。
 * @return 创建指向ArkUI_StyledString对象的指针。如果返回空指针，表示创建失败，可能原因包括地址空间已满或参数异常（如style、collection为空指针）。
 * @since 12
 */
ArkUI_StyledString* OH_ArkUI_StyledString_Create(
    OH_Drawing_TypographyStyle* style, OH_Drawing_FontCollection* collection);

/**
 * @brief 释放ArkUI_StyledString对象占用的内存。
 *
 * @param handle 指向ArkUI_StyledString对象的指针。
 * @since 12
 */
void OH_ArkUI_StyledString_Destroy(ArkUI_StyledString* handle);

/**
 * @brief 将新的排版风格设置到当前格式化字符串样式栈顶。
 *
 * @param handle 指向ArkUI_StyledString对象的指针。
 * @param style 指向{@link OH_Drawing_TextStyle}对象的指针，由{@link OH_Drawing_CreateTextStyle}创建获取。
 * @since 12
 */
void OH_ArkUI_StyledString_PushTextStyle(ArkUI_StyledString* handle, OH_Drawing_TextStyle* style);

/**
 * @brief 基于当前格式化字符串样式设置对应的文本内容。所添加的文本将使用当前栈顶的排版样式，该样式由{@link OH_ArkUI_StyledString_PushTextStyle}压入。当栈顶样式通过
 * {@link OH_ArkUI_StyledString_PopTextStyle}出栈后，后续添加的文本将使用新的栈顶样式。
 *
 * @param handle 指向ArkUI_StyledString对象的指针。
 * @param content 指向文本内容的指针。
 * @since 12
 */
void OH_ArkUI_StyledString_AddText(ArkUI_StyledString* handle, const char* content);

/**
 * @brief 将当前格式化字符串对象中栈顶样式出栈。
 *
 * @param handle 指向ArkUI_StyledString对象的指针。
 * @since 12
 */
void OH_ArkUI_StyledString_PopTextStyle(ArkUI_StyledString* handle);

/**
 * @brief 基于格式化字符串对象创建指向{@link OH_Drawing_Typography}对象的指针，用于提前进行文本测算排版。
 *
 * @param handle 指向ArkUI_StyledString对象的指针。
 * @return 指向OH_Drawing_Typography对象的指针。如果对象返回空指针，表示创建失败，失败的原因是handle参数为空指针。
 * @since 12
 */
OH_Drawing_Typography* OH_ArkUI_StyledString_CreateTypography(ArkUI_StyledString* handle);

/**
 * @brief 设置占位符，用于在格式化字符串中预留指定宽高的空白区域或嵌入自定义内容。其尺寸等信息由{@link OH_Drawing_PlaceholderSpan}指定。
 *
 * @param handle 指向ArkUI_StyledString对象的指针。
 * @param placeholder 指向OH_Drawing_PlaceholderSpan对象的指针。
 * @since 12
 */
void OH_ArkUI_StyledString_AddPlaceholder(ArkUI_StyledString* handle, OH_Drawing_PlaceholderSpan* placeholder);

/**
 * @brief 创建属性字符串数据对象。
 *
 * @return 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @since 14
 */
ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_Create(void);

/**
 * @brief 释放ArkUI_StyledString_Descriptor对象占用的内存。
 *
 * @param descriptor 指向ArkUI_StyledString_Descriptor对象的指针。
 * @since 14
 */
void OH_ArkUI_StyledString_Descriptor_Destroy(ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief 将属性字符串信息转换成HTML。
 *
 * @param descriptor 指向ArkUI_StyledString_Descriptor对象的指针。
 * @return HTML。该指针由内部管理，在{@link OH_ArkUI_StyledString_Descriptor_Destroy()}时释放。
 * @since 14
 */
const char* OH_ArkUI_ConvertToHtml(ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief 将包含属性字符串信息的字节数组反序列化为属性字符串。
 *
 * @param buffer 待反序列化的字节数组。
 * @param bufferSize 字节数组长度。
 * @param descriptor 指向ArkUI_StyledString_Descriptor对象的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常，可能原因包括传入参数为空指针或参数值不在有效范围内，请检查参数是否有效。
 * @since 14
 */
int32_t OH_ArkUI_UnmarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief 将属性字符串信息序列化为字节数组。
 *
 * @param buffer 字节数组，用于存储属性字符串序列化后的数据。
 * @param bufferSize 字节数组长度。
 * @param descriptor 指向ArkUI_StyledString_Descriptor对象的指针。
 * @param resultSize 属性字符串转换后的字节数组实际长度。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常，可能原因包括传入参数为空指针或参数值不在有效范围内，请检查参数是否有效。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效，可能原因包括属性字符串对象已被销毁或未正确创建，请确保使用有效的属性字符串对象。
 * @since 14
 */
int32_t OH_ArkUI_MarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor, size_t* resultSize);

/**
 * @brief 定义属性字符串样式对象。 <br>        可以通过{@link OH_ArkUI_SpanStyle_Create}接口创建对应的属性字符串样式对象。 <br>        可以通过
 * {@link OH_ArkUI_SpanStyle_Destroy}接口销毁属性字符串样式对象。 <br>        对象创建后通过{@link OH_ArkUI_SpanStyle_SetStart}和
 * {@link OH_ArkUI_SpanStyle_SetLength}指定样式作用的范围。 <br>        对象创建后通过OH_ArkUI_SpanStyle_SetXXXStyle系列接口设置生效的具体样式，例如通过
 * {@link OH_ArkUI_SpanStyle_SetTextStyle}设置字体样式效果。
 *
 * @since 24
 */
typedef struct OH_ArkUI_SpanStyle OH_ArkUI_SpanStyle;
 
/**
 * @brief 定义图片样式对象。 <br>        可以通过{@link OH_ArkUI_ImageAttachment_Create}接口创建对应的图片样式对象。 <br>        可以通过
 * {@link OH_ArkUI_ImageAttachment_Destroy}接口销毁图片样式对象。 <br>        对象创建后通过OH_ArkUI_ImageAttachment_SetXXX系列接口设置生效的具体样式，
 * 例如通过{@link OH_ArkUI_ImageAttachment_SetPixelMap}设置图片源。
 *
 * @since 24
 */
typedef struct OH_ArkUI_ImageAttachment OH_ArkUI_ImageAttachment;
 
/**
 * @brief 定义自定义绘制Span。 <br>        可以通过{@link OH_ArkUI_CustomSpan_Create}接口创建对应的自定义绘制Span对象。 <br>        可以通过
 * {@link OH_ArkUI_CustomSpan_Destroy}接口销毁自定义绘制Span对象。 <br>        对象创建后通过
 * {@link OH_ArkUI_CustomSpan_RegisterOnMeasureCallback}和{@link OH_ArkUI_CustomSpan_RegisterOnDrawCallback}
 * 接口分别注册测量和绘制回调函数。
 *
 * @since 24
 */
typedef struct OH_ArkUI_CustomSpan OH_ArkUI_CustomSpan;
 
/**
 * @brief 属性字符串的样式类型枚举。
 *
 * @since 24
 */
typedef enum {
    /**
     * 未指定样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_UNSPECIFIED = -1,

    /**
     * 文本字体样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_FONT = 0,

    /**
     * 文本装饰线样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_DECORATION = 1,

    /**
     * 文本基线偏移量样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_BASELINE_OFFSET = 2,

    /**
     * 文本字符间距样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_LETTER_SPACING = 3,

    /**
     * 文本阴影样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_TEXT_SHADOW = 4,

    /**
     * 文本行高样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_LINE_HEIGHT = 5,

    /**
     * 文本背景颜色样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_BACKGROUND_COLOR = 6,

    /**
     * 超链接样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_URL = 7,

    /**
     * 文本行间距样式。
     * @since 26.0.0
     */
    OH_ARKUI_STYLEDSTRINGKEY_LINE_SPACING = 8,

    /**
     * 事件手势样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_GESTURE = 100,

    /**
     * 文本段落样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_PARAGRAPH_STYLE = 200,

    /**
     * 图片样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_IMAGE = 300,

    /**
     * 自定义绘制Span样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_CUSTOM_SPAN = 400,

    /**
     * 用户数据Span样式。
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_USER_DATA = 500
} OH_ArkUI_StyledStringKey;
 
/**
 * @brief 创建纯文本内容类型的{@link ArkUI_StyledString_Descriptor}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_StyledString_Descriptor_Destroy 来销毁它。
 *     所有输入指针参数必须由调用者分配、管理和释放。
 * @param value 属性字符串的纯文本内容。
 * @param styles 属性字符串的样式集合，指向{@link OH_ArkUI_SpanStyle}对象数组的指针。数组中每个OH_ArkUI_SpanStyle对象需先调用
 *     {@link OH_ArkUI_SpanStyle_SetStart}和{@link OH_ArkUI_SpanStyle_SetLength}设置样式作用的范围。
 * @param length 样式对象数组的数量。取值范围[0, +∞)，需与传入的styles指针所指向的数组实际长度一致。
 * @return 指向创建的{@link ArkUI_StyledString_Descriptor}对象的指针。
 *     <br>如果结果为空指针，表示创建失败，失败的原因是传入参数为空指针或参数值无效。
 * @since 24
 */
ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_CreateWithString(const char* value,
    const OH_ArkUI_SpanStyle** styles, int32_t length);
 
/**
 * @brief 创建图片内容类型的{@link ArkUI_StyledString_Descriptor}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_StyledString_Descriptor_Destroy 来销毁它。
 *     所有输入指针参数必须由调用者分配、管理和释放。
 * @param value 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @return 指向创建的{@link ArkUI_StyledString_Descriptor}对象的指针。
 *     <br>如果结果为空指针，表示创建失败，失败的原因是传入参数为空指针或参数值无效。
 * @since 24
 */
ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_CreateWithImageAttachment(
    const OH_ArkUI_ImageAttachment* value);
 
/**
 * @brief 创建自定义绘制Span内容类型的{@link ArkUI_StyledString_Descriptor}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_StyledString_Descriptor_Destroy 来销毁它。
 *     所有输入指针参数必须由调用者分配、管理和释放。
 * @param value 指向{@link OH_ArkUI_CustomSpan}对象的指针。
 * @return 指向创建的{@link ArkUI_StyledString_Descriptor}对象的指针。
 *     <br>如果结果为空指针，表示创建失败，失败的原因是传入参数为空指针或参数值无效。
 * @since 24
 */
ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_CreateWithCustomSpan(const OH_ArkUI_CustomSpan* value);

/**
 * @brief 获取属性字符串的字符长度。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param length 输出参数，用于接收属性字符串的字符长度结果。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常，可能原因包括descriptor为空指针或length为空指针，请检查参数是否有效。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效，可能原因包括属性字符串对象已被销毁或未正确创建，请确保使用有效的属性字符串对象。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_GetLength(const ArkUI_StyledString_Descriptor* descriptor,
    int32_t* length);
 
/**
 * @brief 获取属性字符串的文本内容。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param buffer 文本内容写入内存的缓冲区，内存空间需由开发者分配。
 * @param bufferSize 缓冲区大小。
 * @param writeLength 返回值为{@link ARKUI_ERROR_CODE_NO_ERROR}时表示实际写入缓冲区的长度。
 *     <br>返回值为{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}时表示字符串完整写入缓冲区所需要的最小长度。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常，可能原因包括descriptor为空指针、buffer为空指针或writeLength为空指针，请检查参数是否有效。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效，可能原因包括属性字符串对象已被销毁或未正确创建，请确保使用有效的属性字符串对象。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 缓冲区大小不足，当提供的bufferSize小于实际需要写入的数据长度时返回此错误码。处理步骤：
 *     通过writeLength参数获取所需最小缓冲区大小，重新分配足够大小的缓冲区后再次调用。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_GetString(
    const ArkUI_StyledString_Descriptor* descriptor, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 判断两个属性字符串是否相同。当属性字符串的文本及样式均一致，视为相同。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param firstDescriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param secondDescriptor 指向另一个{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param isEqual 两个属性字符串是否相同。true表示相同；false表示不相同。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_IsEqual(const ArkUI_StyledString_Descriptor* firstDescriptor,
    const ArkUI_StyledString_Descriptor* secondDescriptor, bool* isEqual);

/**
 * @brief 获取属性字符串的子属性字符串。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param subDescriptor 指向{@link ArkUI_StyledString_Descriptor}子属性字符串对象的指针。
 * @param start 子属性字符串的起始位置。取值范围[0, 属性字符串的字符长度]，超出范围时返回ARKUI_ERROR_CODE_PARAM_INVALID。
 * @param length 子属性字符串的字符长度。取值范围[0, 属性字符串的字符长度与参数start的差值]。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_SubStyledString(const ArkUI_StyledString_Descriptor* descriptor,
    ArkUI_StyledString_Descriptor* subDescriptor, uint32_t start, uint32_t length);

/**
 * @brief 获取属性字符串指定范围内的样式集合。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param start 指定范围的起始位置。取值范围[0, 属性字符串的字符长度]。
 * @param length 指定范围的长度。取值范围[0, 属性字符串的字符长度与参数start的差值]。
 * @param styledKey 需要获取的指定样式类型，取值为{@link OH_ArkUI_StyledStringKey}中的枚举。
 * @param styles 指向样式对象数组的缓冲区指针。
 * @param stylesSize 样式对象数组的缓冲区大小。
 * @param writeLength 属性字符串中获取到的样式对象的数组的实际大小。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_GetStyles(const ArkUI_StyledString_Descriptor* descriptor,
    uint32_t start, uint32_t length, OH_ArkUI_StyledStringKey styledKey, OH_ArkUI_SpanStyle** styles,
    uint32_t stylesSize, uint32_t* writeLength);

/**
 * @brief 将HTML格式字符串转换成属性字符串。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param html 待转换为属性字符串的HTML格式字符串，当前支持转换的HTML标签范围：\<p>、\<span>、\<img>、\
 *     <br>、\<strong>、\<b>、\<a>、\<i>、\<em>、\<s>、\<u>、\<del>、\<sup>、\<sub>、\<cite>、\<dfn>、\<small>、\<h1>、\<h2>、\<h3>、\<
 *     h4>、\<h5>、\<h6>、\<ol>、\<ul>、\<li>。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_FromHtml(ArkUI_StyledString_Descriptor* descriptor, const char* html);
 
/**
 * @brief 替换属性字符串指定范围的文本。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param start 指定范围的起始位置。取值范围[0, 属性字符串的字符长度]。
 * @param length 指定范围的长度。取值范围[0, 属性字符串的字符长度与参数start的差值]。
 * @param string 替换的新文本内容。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ReplaceString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, uint32_t length, const char* string);
 
/**
 * @brief 在属性字符串的指定位置插入文本。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param start 插入位置。取值范围[0, 属性字符串的字符长度]。
 * @param string 插入的新文本内容。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_InsertString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, const char* string);
 
/**
 * @brief 移除属性字符串指定范围的文本。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param start 指定范围的起始位置。取值范围[0, 属性字符串的字符长度]。
 * @param length 指定范围的字符长度。取值范围[0, 属性字符串的字符长度与参数start的差值]。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_RemoveString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, uint32_t length);
 
/**
 * @brief 替换属性字符串指定范围内的样式。与{@link OH_ArkUI_StyledString_Descriptor_SetStyle}的区别：ReplaceStyle会清除指定范围内所有类型的已有样式后设置新样式；
 * SetStyle为指定范围设置样式，只替换同类型的已有样式，不影响其他类型的样式。建议需要完全替换已有样式时使用ReplaceStyle，需要叠加设置样式时使用SetStyle。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 *     <br>需先调用{@link OH_ArkUI_SpanStyle_SetStart}和{@link OH_ArkUI_SpanStyle_SetLength}在该对象中设置目标范围。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ReplaceStyle(
    ArkUI_StyledString_Descriptor* descriptor, const OH_ArkUI_SpanStyle* spanStyle);
 
/**
 * @brief 为属性字符串指定范围设置新样式。与{@link OH_ArkUI_StyledString_Descriptor_ReplaceStyle}的区别：SetStyle为指定范围设置样式，只替换同类型的已有样式，
 * 不影响其他类型的样式，适用于叠加设置样式的场景；ReplaceStyle会清除指定范围内所有类型的已有样式后设置新样式，适用于完全替换已有样式的场景。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。需先调用{@link OH_ArkUI_SpanStyle_SetStart}和
 *     {@link OH_ArkUI_SpanStyle_SetLength}在该对象中设置目标范围。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_SetStyle(
    ArkUI_StyledString_Descriptor* descriptor, const OH_ArkUI_SpanStyle* spanStyle);
 
/**
 * @brief 清除属性字符串指定范围内的指定类型样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param start 指定范围的起始位置。取值范围[0, 属性字符串的字符长度]。
 * @param length 指定范围的长度。取值范围[0, 属性字符串的字符长度与参数start的差值]。
 * @param styledKey 样式类型枚举值，取值为{@link OH_ArkUI_StyledStringKey}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_RemoveStyle(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, uint32_t length, OH_ArkUI_StyledStringKey styledKey);
 
/**
 * @brief 清除属性字符串对象的所有样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ClearStyles(ArkUI_StyledString_Descriptor* descriptor);
 
/**
 * @brief 替换指定范围的属性字符串。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param start 指定范围的起始位置。取值范围[0, 属性字符串的字符长度]。
 * @param length 指定范围的长度。取值范围[0, 属性字符串的字符长度与参数start的差值]。
 * @param other 指向新的{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ReplaceStyledString(ArkUI_StyledString_Descriptor* descriptor,
    uint32_t start, uint32_t length, const ArkUI_StyledString_Descriptor* other);
 
/**
 * @brief 在属性字符串的指定位置插入新的属性字符串。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param start 插入位置。取值范围[0, 属性字符串的字符长度]。
 * @param other 指向新的{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_InsertStyledString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, const ArkUI_StyledString_Descriptor* other);
 
/**
 * @brief 在属性字符串的末尾追加新的属性字符串。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @param other 指向新的{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_AppendStyledString(
    ArkUI_StyledString_Descriptor* descriptor, const ArkUI_StyledString_Descriptor* other);
 
/**
 * @brief 主动刷新属性字符串中的自定义绘制Span。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} 属性字符串无效。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_InvalidateCustomSpan(const ArkUI_StyledString_Descriptor* descriptor);
 
/**
 * @brief 定义文本字体样式。<br>
 * 可以通过{@link OH_ArkUI_TextStyle_Create}接口创建对应的文本字体样式对象。<br>
 * 可以通过{@link OH_ArkUI_TextStyle_Destroy}接口销毁文本字体样式对象。<br>
 * 对象创建后通过OH_ArkUI_TextStyle_SetXXX系列接口设置生效的具体样式，
 * 例如通过{@link OH_ArkUI_TextStyle_SetFontColor}设置字体颜色。
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextStyle OH_ArkUI_TextStyle;
 
/**
 * @brief 定义文本上下角标样式枚举。
 *
 * @since 24
 */
typedef enum {
    /**
     * 普通文本样式，适用于不需要上下标效果的常规文本场景。
     * @since 24
     */
    OH_ARKUI_SUPERSCRIPTSTYLE_NORMAL = 0,

    /**
     * 上标文本样式，适用于数学公式中的指数表示（如x²）或脚注引用标记等场景。
     * @since 24
     */
    OH_ARKUI_SUPERSCRIPTSTYLE_SUPERSCRIPT,

    /**
     * 下标文本样式，适用于化学式中的元素下标表示（如H₂O）或数学变量下标等场景。
     * @since 24
     */
    OH_ARKUI_SUPERSCRIPTSTYLE_SUBSCRIPT
} OH_ArkUI_SuperscriptStyle;
 
/**
 * @brief 创建{@link OH_ArkUI_TextStyle}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_TextStyle_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @since 24
 */
OH_ArkUI_TextStyle* OH_ArkUI_TextStyle_Create();
 
/**
 * @brief 释放{@link OH_ArkUI_TextStyle}对象占用的内存。
 *
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @since 24
 */
void OH_ArkUI_TextStyle_Destroy(OH_ArkUI_TextStyle* textStyle);
 
/**
 * @brief 设置文本字体样式中的字体颜色。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param fontColor 字体颜色，0xARGB格式。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontColor(OH_ArkUI_TextStyle* textStyle, uint32_t fontColor);
 
/**
 * @brief 获取文本字体样式中的字体颜色。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param fontColor 字体颜色，0xARGB格式。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontColor(const OH_ArkUI_TextStyle* textStyle, uint32_t* fontColor);
 
/**
 * @brief 设置文本字体样式中的字体族。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param fontFamily 字体族。存放待设置的字体名称，不同字体名称通过逗号拼接。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontFamily(OH_ArkUI_TextStyle* textStyle, const char* fontFamily);
 
/**
 * @brief 获取文本字体样式中的字体族。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param buffer 字体族内容写入内存的缓冲区，内存空间需由开发者分配。
 * @param bufferSize 缓冲区最多可写入的字符的数量。
 * @param writeLength 返回{@link ARKUI_ERROR_CODE_NO_ERROR}时，表示实际写入缓冲区的字符串长度。
 *     <br>返回{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}时，表示字符串完整写入缓冲区所需要的最小长度。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 缓冲区大小不足，当提供的bufferSize小于实际需要写入的数据长度时返回此错误码。处理步骤：
 *     通过writeLength参数获取所需最小缓冲区大小，重新分配足够大小的缓冲区后再次调用。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontFamily(const OH_ArkUI_TextStyle* textStyle,
    char* buffer, int32_t bufferSize, int32_t* writeLength);
 
/**
 * @brief 设置文本字体样式中的字体大小。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param fontSize 字体大小，单位为vp。取值范围[0, +∞)。传入负数时使用默认字体大小。默认值为16vp
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontSize(OH_ArkUI_TextStyle* textStyle, float fontSize);
 
/**
 * @brief 获取文本字体样式中的字体大小。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param fontSize 字体大小，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontSize(const OH_ArkUI_TextStyle* textStyle, float* fontSize);
 
/**
 * @brief 设置文本字体样式中的字体粗细。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param fontWeight 字体粗细。取值为{@link ArkUI_FontWeight}中的枚举值，默认值为ARKUI_FONT_WEIGHT_W400。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontWeight(OH_ArkUI_TextStyle* textStyle, uint32_t fontWeight);
 
/**
 * @brief 获取文本字体样式中的字体粗细。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param fontWeight 字体粗细。取值为{@link ArkUI_FontWeight}中的枚举值，默认值为ARKUI_FONT_WEIGHT_W400。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontWeight(const OH_ArkUI_TextStyle* textStyle, uint32_t* fontWeight);
 
/**
 * @brief 设置文本字体样式中的字体风格。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param fontStyle 字体风格。取值为{@link ArkUI_FontStyle}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontStyle(OH_ArkUI_TextStyle* textStyle, ArkUI_FontStyle fontStyle);
 
/**
 * @brief 获取文本字体样式中的字体风格。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param fontStyle 字体风格。取值为{@link ArkUI_FontStyle}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontStyle(const OH_ArkUI_TextStyle* textStyle, ArkUI_FontStyle* fontStyle);
 
/**
 * @brief 设置文本字体样式中的描边宽度。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param strokeWidth 描边宽度，取值范围(-∞, +∞)，单位为vp。值小于0时为实体字，大于0时为轮廓字，等于0时无描边效果。默认值：0vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetStrokeWidth(OH_ArkUI_TextStyle* textStyle, float strokeWidth);
 
/**
 * @brief 获取文本字体样式中的描边宽度。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param strokeWidth 描边宽度，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetStrokeWidth(const OH_ArkUI_TextStyle* textStyle, float* strokeWidth);
 
/**
 * @brief 设置文本字体样式中的描边颜色。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param strokeColor 描边颜色，0xARGB格式。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetStrokeColor(OH_ArkUI_TextStyle* textStyle, uint32_t strokeColor);
 
/**
 * @brief 获取文本字体样式中的描边颜色。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param strokeColor 描边颜色，0xARGB格式。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetStrokeColor(const OH_ArkUI_TextStyle* textStyle, uint32_t* strokeColor);
 
/**
 * @brief 设置文本字体样式中的上下标样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param superscript 上下标样式。取值为{@link OH_ArkUI_SuperscriptStyle}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetSuperscript(OH_ArkUI_TextStyle* textStyle,
    OH_ArkUI_SuperscriptStyle superscript);
 
/**
 * @brief 获取文本字体样式中的上下标样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @param superscript 上下标样式。取值为{@link OH_ArkUI_SuperscriptStyle}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetSuperscript(const OH_ArkUI_TextStyle* textStyle,
    OH_ArkUI_SuperscriptStyle* superscript);
 
/**
 * @brief 创建{@link OH_ArkUI_SpanStyle}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_SpanStyle_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_SpanStyle}对象的指针，用于设置属性字符串样式的作用范围和具体样式。
 * @since 24
 */
OH_ArkUI_SpanStyle* OH_ArkUI_SpanStyle_Create();
 
/**
 * @brief 释放{@link OH_ArkUI_SpanStyle}对象占用的内存。
 *
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @since 24
 */
void OH_ArkUI_SpanStyle_Destroy(OH_ArkUI_SpanStyle* spanStyle);
 
/**
 * @brief 获取属性字符串样式对象的样式类型。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param styledKey 样式类型的枚举值。取值为{@link OH_ArkUI_StyledStringKey}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetStyledKey(const OH_ArkUI_SpanStyle* spanStyle,
    OH_ArkUI_StyledStringKey* styledKey);
 
/**
 * @brief 设置属性字符串样式对象的起始位置。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param start 属性字符串样式对象的起始位置，需与{@link OH_ArkUI_SpanStyle_SetLength}配合使用以指定样式作用的范围。取值范围[0, 属性字符串的长度]，超出范围时按0处理。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetStart(OH_ArkUI_SpanStyle* spanStyle, int32_t start);
 
/**
 * @brief 获取属性字符串样式对象的起始位置。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param start 属性字符串样式对象的起始位置。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetStart(const OH_ArkUI_SpanStyle* spanStyle, int32_t* start);
 
/**
 * @brief 设置属性字符串样式对象的长度。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param length 属性字符串样式对象的长度，需与{@link OH_ArkUI_SpanStyle_SetStart}配合使用以指定样式作用的范围。当length的值小于0或超出字符串长度与start的差值时，
 *     按字符串长度与start的差值处理。取值范围[0, 属性字符串的长度与参数start的差值]，按字符串长度与start的差值处理。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLength(OH_ArkUI_SpanStyle* spanStyle, int32_t length);
 
/**
 * @brief 获取属性字符串样式对象的长度。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param length 属性字符串样式对象的长度。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLength(const OH_ArkUI_SpanStyle* spanStyle, int32_t* length);
 
/**
 * @brief 设置属性字符串样式对象的文本字体样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetTextStyle(OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_TextStyle* textStyle);
 
/**
 * @brief 获取属性字符串样式对象的文本字体样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param textStyle 指向{@link OH_ArkUI_TextStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetTextStyle(const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_TextStyle* textStyle);
 
/**
 * @brief 定义段落样式。 <br>        可以通过{@link OH_ArkUI_ParagraphStyle_Create}接口创建对应的段落样式对象。 <br>        可以通过
 * {@link OH_ArkUI_ParagraphStyle_Destroy}接口销毁段落样式对象。 <br>        对象创建后通过OH_ArkUI_ParagraphStyle_SetXXX系列接口设置生效的具体样式，
 * 例如通过{@link OH_ArkUI_ParagraphStyle_SetTextAlign}设置文本对齐方式。
 *
 * @since 24
 */
typedef struct OH_ArkUI_ParagraphStyle OH_ArkUI_ParagraphStyle;
 
/**
 * @brief 设置属性字符串样式对象的段落样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetParagraphStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_ParagraphStyle* paragraphStyle);
 
/**
 * @brief 获取属性字符串样式对象的段落样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetParagraphStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_ParagraphStyle* paragraphStyle);
 
/**
 * @brief 定义事件手势样式。 <br>
 * 可以通过{@link OH_ArkUI_GestureStyle_Create}接口创建对应的事件手势样式对象。 <br>
 * 可以通过{@link OH_ArkUI_GestureStyle_Destroy}接口销毁事件手势样式对象。 <br>
 * 对象创建后通过OH_ArkUI_GestureStyle_RegisterOnXXXCallback系列接口注册具体的事件回调，例如通过
 * {@link OH_ArkUI_GestureStyle_RegisterOnClickCallback}注册点击事件回调。
 *
 * @since 24
 */
typedef struct OH_ArkUI_GestureStyle OH_ArkUI_GestureStyle;
 
/**
 * @brief 设置属性字符串样式对象的事件手势样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param gestureStyle 指向{@link OH_ArkUI_GestureStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetGestureStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_GestureStyle* gestureStyle);
 
/**
 * @brief 获取属性字符串样式对象的事件手势样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param gestureStyle 指向{@link OH_ArkUI_GestureStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetGestureStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_GestureStyle* gestureStyle);
 
/**
 * @brief 定义文本阴影样式。 <br>        可以通过{@link OH_ArkUI_TextShadowStyle_Create}接口创建对应的文本阴影样式对象。 <br>        可以通过
 * {@link OH_ArkUI_TextShadowStyle_Destroy}接口销毁文本阴影样式对象。 <br>        对象创建后通过
 * {@link OH_ArkUI_TextShadowStyle_SetTextShadow}接口设置生效的具体样式。
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextShadowStyle OH_ArkUI_TextShadowStyle;
 
/**
 * @brief 设置属性字符串样式对象的文本阴影样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param textShadowStyle 指向{@link OH_ArkUI_TextShadowStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetTextShadowStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_TextShadowStyle* textShadowStyle);
 
/**
 * @brief 获取属性字符串样式对象的文本阴影样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param textShadowStyle 指向{@link OH_ArkUI_TextShadowStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetTextShadowStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_TextShadowStyle* textShadowStyle);
 
/**
 * @brief 定义文本装饰线样式。 <br>        可以通过{@link OH_ArkUI_DecorationStyle_Create}接口创建对应的文本装饰线样式对象。 <br>        可以通过
 * {@link OH_ArkUI_DecorationStyle_Destroy}接口销毁文本装饰线样式对象。 <br>
 * 对象创建后通过OH_ArkUI_DecorationStyle_SetXXX系列接口设置生效的具体样式，例如通过{@link OH_ArkUI_DecorationStyle_SetTextDecorationType}
 * 设置装饰线类型。
 *
 * @since 24
 */
typedef struct OH_ArkUI_DecorationStyle OH_ArkUI_DecorationStyle;
 
/**
 * @brief 设置属性字符串样式对象的文本装饰线样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param decorationStyle 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetDecorationStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_DecorationStyle* decorationStyle);
 
/**
 * @brief 获取属性字符串样式对象的文本装饰线样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param decorationStyle 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetDecorationStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_DecorationStyle* decorationStyle);
 
/**
 * @brief 定义基线偏移量样式。 <br>        可以通过{@link OH_ArkUI_BaselineOffsetStyle_Create}接口创建对应的基线偏移量样式对象。 <br>        可以通过
 * {@link OH_ArkUI_BaselineOffsetStyle_Destroy}接口销毁基线偏移量样式对象。 <br>        对象创建后通过
 * {@link OH_ArkUI_BaselineOffsetStyle_SetBaselineOffset}接口设置具体的基线偏移量值。
 *
 * @since 24
 */
typedef struct OH_ArkUI_BaselineOffsetStyle OH_ArkUI_BaselineOffsetStyle;

/**
 * @brief 设置属性字符串样式对象的基线偏移量样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param baselineOffsetStyle 指向{@link OH_ArkUI_BaselineOffsetStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetBaselineOffsetStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle);

/**
 * @brief 获取属性字符串样式对象的基线偏移量样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param baselineOffsetStyle 指向{@link OH_ArkUI_BaselineOffsetStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetBaselineOffsetStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle);
 
/**
 * @brief 定义字符间距样式。 <br>        可以通过{@link OH_ArkUI_LetterSpacingStyle_Create}接口创建对应的字符间距样式对象。 <br>        可以通过
 * {@link OH_ArkUI_LetterSpacingStyle_Destroy}接口销毁字符间距样式对象。 <br>        对象创建后通过
 * {@link OH_ArkUI_LetterSpacingStyle_SetLetterSpacing}接口设置具体的字符间距值。
 *
 * @since 24
 */
typedef struct OH_ArkUI_LetterSpacingStyle OH_ArkUI_LetterSpacingStyle;
 
/**
 * @brief 设置属性字符串样式对象的字符间距样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param letterSpacingStyle 指向{@link OH_ArkUI_LetterSpacingStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLetterSpacingStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_LetterSpacingStyle* letterSpacingStyle);
 
/**
 * @brief 获取属性字符串样式对象的字符间距样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param letterSpacingStyle 指向{@link OH_ArkUI_LetterSpacingStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLetterSpacingStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_LetterSpacingStyle* letterSpacingStyle);
 
/**
 * @brief 定义行高样式。 <br>        可以通过{@link OH_ArkUI_LineHeightStyle_Create}接口创建对应的行高样式对象。 <br>        可以通过
 * {@link OH_ArkUI_LineHeightStyle_Destroy}接口销毁行高样式对象。 <br>        对象创建后可以通过
 * {@link OH_ArkUI_LineHeightStyle_SetLineHeight}接口设置具体的固定行高值。<br>        从API版本26.0.0开始，对象创建后可以通过
 * {@link OH_ArkUI_LineHeightStyle_SetLineHeightMultiple}接口设置具体的行高的倍数值。
 *
 * @since 24
 */
typedef struct OH_ArkUI_LineHeightStyle OH_ArkUI_LineHeightStyle;
 
/**
 * @brief 设置属性字符串样式对象的行高样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param lineHeightStyle 指向{@link OH_ArkUI_LineHeightStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLineHeightStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_LineHeightStyle* lineHeightStyle);
 
/**
 * @brief 获取属性字符串样式对象的行高样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param lineHeightStyle 指向{@link OH_ArkUI_LineHeightStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLineHeightStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_LineHeightStyle* lineHeightStyle);
 
/**
 * @brief 定义链接样式。 <br>        可以通过{@link OH_ArkUI_UrlStyle_Create}接口创建对应的链接样式对象。 <br>        可以通过
 * {@link OH_ArkUI_UrlStyle_Destroy}接口销毁链接样式对象。 <br>        对象创建后通过{@link OH_ArkUI_UrlStyle_SetUrl}接口设置链接地址。
 *
 * @since 24
 */
typedef struct OH_ArkUI_UrlStyle OH_ArkUI_UrlStyle;
 
/**
 * @brief 设置属性字符串样式对象的超链接样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param urlStyle 指向{@link OH_ArkUI_UrlStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetUrlStyle(OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_UrlStyle* urlStyle);
 
/**
 * @brief 获取属性字符串样式对象的超链接样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param urlStyle 指向{@link OH_ArkUI_UrlStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetUrlStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_UrlStyle* urlStyle);
 
/**
 * @brief 定义背景颜色样式。 <br>        可以通过{@link OH_ArkUI_BackgroundColorStyle_Create}接口创建对应的背景颜色样式对象。 <br>        可以通过
 * {@link OH_ArkUI_BackgroundColorStyle_Destroy}接口销毁背景颜色样式对象。 <br>        对象创建后通过
 * {@link OH_ArkUI_BackgroundColorStyle_SetColor}和{@link OH_ArkUI_BackgroundColorStyle_SetRadius}接口设置背景颜色和圆角。
 *
 * @since 24
 */
typedef struct OH_ArkUI_BackgroundColorStyle OH_ArkUI_BackgroundColorStyle;
 
/**
 * @brief 设置属性字符串样式对象的背景颜色样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param backgroundColorStyle 指向{@link OH_ArkUI_BackgroundColorStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetBackgroundColorStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_BackgroundColorStyle* backgroundColorStyle);
 
/**
 * @brief 获取属性字符串样式对象的背景颜色样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param backgroundColorStyle 指向{@link OH_ArkUI_BackgroundColorStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetBackgroundColorStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_BackgroundColorStyle* backgroundColorStyle);
 
/**
 * @brief 定义用户数据Span样式。 <br>        可以通过{@link OH_ArkUI_UserDataSpan_Create}接口创建对应的用户数据Span样式对象。 <br>        可以通过
 * {@link OH_ArkUI_UserDataSpan_Destroy}接口销毁用户数据Span样式对象。 <br>        对象创建后通过{@link OH_ArkUI_UserDataSpan_SetUserData}
 * 接口设置用户数据。
 *
 * @since 24
 */
typedef struct OH_ArkUI_UserDataSpan OH_ArkUI_UserDataSpan;
 
/**
 * @brief 设置属性字符串样式对象的用户数据Span样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param userDataSpan 指向{@link OH_ArkUI_UserDataSpan}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetUserDataSpan(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_UserDataSpan* userDataSpan);
 
/**
 * @brief 获取属性字符串样式对象的用户数据Span样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param userDataSpan 指向{@link OH_ArkUI_UserDataSpan}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetUserDataSpan(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_UserDataSpan* userDataSpan);
 
/**
 * @brief 设置属性字符串样式对象的自定义绘制Span样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param customSpan 指向{@link OH_ArkUI_CustomSpan}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetCustomSpan(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_CustomSpan* customSpan);
 
/**
 * @brief 获取属性字符串样式对象的自定义绘制Span样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param customSpan 指向{@link OH_ArkUI_CustomSpan}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetCustomSpan(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_CustomSpan* customSpan);
 
/**
 * @brief 设置属性字符串样式对象的图片样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetImageAttachment(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_ImageAttachment* imageAttachment);
 
/**
 * @brief 获取属性字符串样式对象的图片样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetImageAttachment(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_ImageAttachment* imageAttachment);
 
/**
 * @brief 定义段落缩进的自定义绘制信息。 <br>        可以通过{@link OH_ArkUI_LeadingMarginSpanDrawInfo_Create}接口创建对应的段落缩进的自定义绘制信息对象。 <br>
 *       可以通过{@link OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy}接口销毁段落缩进的自定义绘制信息对象。 <br>        对象用于在
 * {@link OH_ArkUI_ParagraphStyle_RegisterOnDrawLeadingMarginCallback}注册的回调函数中，提供当前行的绘制上下文信息。
 *
 * @since 24
 */
typedef struct OH_ArkUI_LeadingMarginSpanDrawInfo OH_ArkUI_LeadingMarginSpanDrawInfo;
 
/**
 * @brief 创建{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象。
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy </b> to destroy it.
 * @return 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @since 24
 */
OH_ArkUI_LeadingMarginSpanDrawInfo* OH_ArkUI_LeadingMarginSpanDrawInfo_Create();
 
/**
 * @brief 释放{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象占用的内存。
 *
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @since 24
 */
void OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo);
 
/**
 * @brief 设置段落缩进的自定义绘制信息对象中当前行相对于组件的水平偏移。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param x 当前行相对于组件的水平偏移，单位px。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetX(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float x);
 
/**
 * @brief 获取段落缩进的自定义绘制信息对象中当前行相对于组件的水平偏移。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param x 当前行相对于组件的水平偏移，单位px。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetX(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float* x);
 
/**
 * @brief 设置段落缩进的自定义绘制信息对象中行顶与组件上边缘的距离。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param top 行顶与组件上边缘的距离，单位px。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetTop(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float top);
 
/**
 * @brief 获取段落缩进的自定义绘制信息对象中行顶与组件上边缘的距离。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param top 行顶与组件上边缘的距离，单位px。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetTop(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float* top);
 
/**
 * @brief 设置段落缩进的自定义绘制信息对象中行底与组件上边缘的距离。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param bottom 行底与组件上边缘的距离，单位px。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetBottom(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float bottom);
 
/**
 * @brief 获取段落缩进的自定义绘制信息对象中行底与组件上边缘的距离。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param bottom 行底与组件上边缘的距离，单位px。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetBottom(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float* bottom);
 
/**
 * @brief 设置段落缩进的自定义绘制信息对象中当前行的基线与组件上边缘的距离。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param baseline 当前行的基线与组件上边缘的距离，单位px。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetBaseline(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float baseline);
 
/**
 * @brief 获取段落缩进的自定义绘制信息对象中当前行的基线与组件上边缘的距离。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param baseline 当前行的基线与组件上边缘的距离，单位px。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetBaseline(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float* baseline);
 
/**
 * @brief 设置段落缩进的自定义绘制信息对象中文本内容的方向。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param direction 文本内容的方向。取值为{@link ArkUI_TextDirection}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetTextDirection(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    ArkUI_TextDirection direction);
 
/**
 * @brief 获取段落缩进的自定义绘制信息对象中文本内容的方向。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param direction 文本内容的方向。取值为{@link ArkUI_TextDirection}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetTextDirection(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    ArkUI_TextDirection* direction);
 
/**
 * @brief 设置段落缩进的自定义绘制信息对象中当前行的起始索引。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param start 当前行的起始索引。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetStart(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    uint32_t start);
 
/**
 * @brief 获取段落缩进的自定义绘制信息对象中当前行的起始索引。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param start 当前行的起始索引。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetStart(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    uint32_t* start);
 
/**
 * @brief 设置段落缩进的自定义绘制信息对象中当前行的结束索引。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param end 当前行的结束索引。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetEnd(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, uint32_t end);
 
/**
 * @brief 获取段落缩进的自定义绘制信息对象中当前行的结束索引。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param end 当前行的结束索引。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetEnd(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    uint32_t* end);
 
/**
 * @brief 设置段落缩进的自定义绘制信息对象中当前行是否为段落的首行。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param first 当前行是否为段落的首行。true表示首行；false表示非首行。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetFirst(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, bool first);
 
/**
 * @brief 获取段落缩进的自定义绘制信息对象中当前行是否为段落的首行。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param drawInfo 指向{@link OH_ArkUI_LeadingMarginSpanDrawInfo}对象的指针。
 * @param first 当前行是否为段落的首行。true表示首行；false表示非首行。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetFirst(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    bool* first);
 
/**
 * @brief 创建{@link OH_ArkUI_ParagraphStyle}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_ParagraphStyle_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @since 24
 */
OH_ArkUI_ParagraphStyle* OH_ArkUI_ParagraphStyle_Create();
 
/**
 * @brief 释放{@link OH_ArkUI_ParagraphStyle}对象占用的内存。
 *
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @since 24
 */
void OH_ArkUI_ParagraphStyle_Destroy(OH_ArkUI_ParagraphStyle* paragraphStyle);
 
/**
 * @brief 设置段落样式中的水平方向的文本对齐方式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param align 水平方向的文本对齐方式。取值为{@link ArkUI_TextAlignment}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextAlign(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextAlignment align);
 
/**
 * @brief 获取段落样式中的水平方向的文本对齐方式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param align 水平方向的文本对齐方式。取值为{@link ArkUI_TextAlignment}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextAlign(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextAlignment* align);
 
/**
 * @brief 设置段落样式中的首行文本缩进。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param textIndent 首行缩进值，单位为vp。取值范围[0, +∞)。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextIndent(OH_ArkUI_ParagraphStyle* paragraphStyle, float textIndent);
 
/**
 * @brief 获取段落样式中的首行文本缩进。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param textIndent 首行缩进值，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextIndent(const OH_ArkUI_ParagraphStyle* paragraphStyle, float* textIndent);
 
/**
 * @brief 设置段落样式中的最大行数。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param maxLines 最大行数，取值为正整数。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetMaxLines(OH_ArkUI_ParagraphStyle* paragraphStyle, int32_t maxLines);
 
/**
 * @brief 获取段落样式中的最大行数。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param maxLines 最大行数。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetMaxLines(const OH_ArkUI_ParagraphStyle* paragraphStyle, int32_t* maxLines);
 
/**
 * @brief 设置段落样式中的段落超长时的显示方式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param overflow 段落超长时的显示方式。取值为{@link ArkUI_TextOverflow}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetOverflow(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextOverflow overflow);
 
/**
 * @brief 获取段落样式中的段落超长时的显示方式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param overflow 段落超长时的显示方式。取值为{@link ArkUI_TextOverflow}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetOverflow(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextOverflow* overflow);
 
/**
 * @brief 设置段落样式中的断行规则。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param wordBreak 断行规则。取值为{@link ArkUI_WordBreak}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetWordBreak(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_WordBreak wordBreak);
 
/**
 * @brief 获取段落样式中的断行规则。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param wordBreak 断行规则。取值为{@link ArkUI_WordBreak}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetWordBreak(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_WordBreak* wordBreak);
 
/**
 * @brief 设置段落样式中的段落缩进的像素图。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param pixelmap 段落缩进的像素图。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLeadingMarginPixelMap(OH_ArkUI_ParagraphStyle* paragraphStyle,
    struct OH_PixelmapNative* pixelmap);
 
/**
 * @brief 获取段落样式中的段落缩进的像素图。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param pixelmap 段落缩进的像素图。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLeadingMarginPixelMap(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    struct OH_PixelmapNative** pixelmap);
 
/**
 * @brief 设置段落样式中的段落缩进宽度。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param width 段落缩进宽度，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLeadingMarginWidth(OH_ArkUI_ParagraphStyle* paragraphStyle, uint32_t width);
 
/**
 * @brief 获取段落样式中的段落缩进宽度。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param width 段落缩进宽度，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLeadingMarginWidth(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t* width);
 
/**
 * @brief 设置段落样式中的段落缩进高度。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param height 段落缩进高度，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLeadingMarginHeight(OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t height);
 
/**
 * @brief 获取段落样式中的段落缩进高度。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param height 段落缩进高度，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLeadingMarginHeight(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t* height);
 
/**
 * @brief 设置段落样式中的段落间距。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param paragraphSpacing 段落间距，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetParagraphSpacing(OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t paragraphSpacing);
 
/**
 * @brief 获取段落样式中的段落间距。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param paragraphSpacing 段落间距，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetParagraphSpacing(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t* paragraphSpacing);
 
/**
 * @brief 设置段落样式中的垂直方向的文本对齐方式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param verticalAlignment 垂直方向的文本对齐方式。取值为{@link ArkUI_TextVerticalAlignment}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextVerticalAlign(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextVerticalAlignment verticalAlignment);
 
/**
 * @brief 获取段落样式中的垂直方向的文本对齐方式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param verticalAlignment 垂直方向的文本对齐方式。取值为{@link ArkUI_TextVerticalAlignment}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextVerticalAlign(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextVerticalAlignment* verticalAlignment);
 
/**
 * @brief 设置段落样式中绘制段落缩进时触发的回调函数。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param onDraw The callback function for drawing leading margin.
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_RegisterOnDrawLeadingMarginCallback(OH_ArkUI_ParagraphStyle* paragraphStyle,
    void(*onDraw)(ArkUI_DrawContext* context, OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo));
 
/**
 * @brief 设置段落样式中获取段落缩进距离时触发的回调函数。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param leadingMargin The callback function for obtaining the indentation distance of a text paragraph.
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_RegisterOnGetLeadingMarginCallback(OH_ArkUI_ParagraphStyle* paragraphStyle,
    float(*leadingMargin)());
 
/**
 * @brief 设置段落样式中的文本方向。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param textDirection 文本方向。取值为{@link ArkUI_TextDirection}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextDirection(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextDirection textDirection);
 
/**
 * @brief 获取段落样式中的文本方向。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param textDirection 文本方向。取值为{@link ArkUI_TextDirection}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextDirection(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextDirection* textDirection);

/**
 * @brief 创建{@link OH_ArkUI_GestureStyle}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_GestureStyle_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_GestureStyle}对象的指针。
 * @since 24
 */
OH_ArkUI_GestureStyle* OH_ArkUI_GestureStyle_Create();

/**
 * @brief 释放{@link OH_ArkUI_GestureStyle}对象占用的内存。
 *
 * @param gestureStyle 指向{@link OH_ArkUI_GestureStyle}对象的指针。
 * @since 24
 */
void OH_ArkUI_GestureStyle_Destroy(OH_ArkUI_GestureStyle* gestureStyle);

/**
 * @brief 注册事件手势样式中的点击事件回调。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param gestureStyle 指向{@link OH_ArkUI_GestureStyle}对象的指针。
 * @param onClick The callback of click event.
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_GestureStyle_RegisterOnClickCallback(
    OH_ArkUI_GestureStyle* gestureStyle, void(*onClick)(ArkUI_NodeEvent*));

/**
 * @brief 注册事件手势样式中的长按事件回调。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param gestureStyle 指向{@link OH_ArkUI_GestureStyle}对象的指针。
 * @param onLongPress The callback of long press event.
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_GestureStyle_RegisterOnLongPressCallback(
    OH_ArkUI_GestureStyle* gestureStyle, void(*onLongPress)(ArkUI_GestureEvent*));

/**
 * @brief 注册事件手势样式中的触摸事件回调。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param gestureStyle 指向{@link OH_ArkUI_GestureStyle}对象的指针。
 * @param onTouch The callback of touch event.
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_GestureStyle_RegisterOnTouchCallback(
    OH_ArkUI_GestureStyle* gestureStyle, void(*onTouch)(ArkUI_NodeEvent*));

/**
 * @brief 创建{@link OH_ArkUI_TextShadowStyle}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_TextShadowStyle_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_TextShadowStyle}对象的指针。
 * @since 24
 */
OH_ArkUI_TextShadowStyle* OH_ArkUI_TextShadowStyle_Create();

/**
 * @brief 释放{@link OH_ArkUI_TextShadowStyle}对象占用的内存。
 *
 * @param textShadowStyle 指向{@link OH_ArkUI_TextShadowStyle}对象的指针。
 * @since 24
 */
void OH_ArkUI_TextShadowStyle_Destroy(OH_ArkUI_TextShadowStyle* textShadowStyle);

/**
 * @brief 设置文本阴影样式的文本阴影选项。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textShadowStyle 指向{@link OH_ArkUI_TextShadowStyle}对象的指针。
 * @param options 文本阴影选项，指向{@link OH_ArkUI_ShadowOptions}对象数组的指针。
 * @param length 文本阴影选项数组元素的数量。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextShadowStyle_SetTextShadow(OH_ArkUI_TextShadowStyle* textShadowStyle,
    const OH_ArkUI_ShadowOptions** options, uint32_t length);

/**
 * @brief 获取文本阴影样式的文本阴影选项。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param textShadowStyle 指向{@link OH_ArkUI_TextShadowStyle}对象的指针。
 * @param shadowOptions 文本阴影选项，指向{@link OH_ArkUI_ShadowOptions}对象数组的指针。
 * @param shadowOptionsSize 阴影选项的缓冲区大小。
 * @param writeLength 文本阴影样式中实际的文本阴影选项数量。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextShadowStyle_GetTextShadow(const OH_ArkUI_TextShadowStyle* textShadowStyle,
    OH_ArkUI_ShadowOptions** shadowOptions, uint32_t shadowOptionsSize, uint32_t* writeLength);

/**
 * @brief 创建{@link OH_ArkUI_DecorationStyle}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_DecorationStyle_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @since 24
 */
OH_ArkUI_DecorationStyle* OH_ArkUI_DecorationStyle_Create();

/**
 * @brief 释放{@link OH_ArkUI_DecorationStyle}对象占用的内存。
 *
 * @param decorationStyle 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @since 24
 */
void OH_ArkUI_DecorationStyle_Destroy(OH_ArkUI_DecorationStyle* decorationStyle);
 
/**
 * @brief 设置文本装饰线样式的装饰线类型。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param decorationStyle 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @param type 装饰线类型。取值为{@link ArkUI_TextDecorationType}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetTextDecorationType(OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationType type);
 
/**
 * @brief 获取文本装饰线样式的装饰线类型。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param decorationStyle 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @param type 装饰线类型。取值为{@link ArkUI_TextDecorationType}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetTextDecorationType(const OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationType* type);
 
/**
 * @brief 设置文本装饰线样式的装饰线颜色。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param decorationStyle 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @param color 装饰线颜色，0xARGB格式。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetColor(OH_ArkUI_DecorationStyle* decorationStyle, uint32_t color);
 
/**
 * @brief 获取文本装饰线样式的装饰线颜色。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param decorationStyle 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @param color 装饰线颜色，0xARGB格式。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetColor(const OH_ArkUI_DecorationStyle* decorationStyle, uint32_t* color);
 
/**
 * @brief 设置文本装饰线样式的装饰线样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param decorationStyle 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @param style 装饰线样式。取值为{@link ArkUI_TextDecorationStyle}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetTextDecorationStyle(OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationStyle style);
 
/**
 * @brief 获取文本装饰线样式的装饰线样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param decorationStyle 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @param style 装饰线样式。取值为{@link ArkUI_TextDecorationStyle}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetTextDecorationStyle(const OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationStyle* style);
 
/**
 * @brief 设置文本装饰线样式的装饰线的粗细缩放比例。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param decorationStyle 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @param thicknessScale 装饰线的粗细缩放比例。取值范围为[0, +∞)。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetThicknessScale(OH_ArkUI_DecorationStyle* decorationStyle,
    float thicknessScale);
 
/**
 * @brief 获取文本装饰线样式的装饰线的粗细缩放比例。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param decorationStyle 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @param thicknessScale 装饰线的粗细缩放比例。取值范围为[0, +∞)。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetThicknessScale(const OH_ArkUI_DecorationStyle* decorationStyle,
    float* thicknessScale);
 
/**
 * @brief 设置文本装饰线样式中是否开启多装饰线显示。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param decorationStyle 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @param enableMultiType 是否开启多装饰线显示。传入true时开启多装饰线显示，允许同时显示多种类型的装饰线（如同时显示下划线和删除线），适用于需要复合装饰效果的场景；传入false时不开启，仅显示单一类型装饰线，
 *     适用于只需要一种装饰线的场景。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetEnableMultiType(
    OH_ArkUI_DecorationStyle* decorationStyle, bool enableMultiType);
 
/**
 * @brief 获取文本装饰线样式中是否开启多装饰线显示。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param decorationStyle 指向{@link OH_ArkUI_DecorationStyle}对象的指针。
 * @param enableMultiType 是否开启多装饰线显示。true表示开启，false表示关闭。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetEnableMultiType(
    const OH_ArkUI_DecorationStyle* decorationStyle, bool* enableMultiType);
 
/**
 * @brief 创建{@link OH_ArkUI_BaselineOffsetStyle}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_BaselineOffsetStyle_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_BaselineOffsetStyle}对象的指针。
 * @since 24
 */
OH_ArkUI_BaselineOffsetStyle* OH_ArkUI_BaselineOffsetStyle_Create();
 
/**
 * @brief 释放{@link OH_ArkUI_BaselineOffsetStyle}对象占用的内存。
 *
 * @param baselineOffsetStyle 指向{@link OH_ArkUI_BaselineOffsetStyle}对象的指针。
 * @since 24
 */
void OH_ArkUI_BaselineOffsetStyle_Destroy(OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle);
 
/**
 * @brief 设置基线偏移量。适用于需要调整文本基线位置的场景，例如上下角标定位、行内图标与文字垂直对齐等。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param baselineOffsetStyle 指向{@link OH_ArkUI_BaselineOffsetStyle}对象的指针。
 * @param baselineOffset 基线偏移量，单位为vp。取值范围(-∞, +∞)。正值与负值分别对应不同的偏移方向，0表示无偏移。具体方向效果需结合上下角标等场景确定。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BaselineOffsetStyle_SetBaselineOffset(
    OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle, float baselineOffset);
 
/**
 * @brief 获取基线偏移量。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param baselineOffsetStyle 指向{@link OH_ArkUI_BaselineOffsetStyle}对象的指针。
 * @param baselineOffset 基线偏移量，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BaselineOffsetStyle_GetBaselineOffset(
    const OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle, float* baselineOffset);
 
/**
 * @brief 创建{@link OH_ArkUI_LetterSpacingStyle}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_LetterSpacingStyle_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_LetterSpacingStyle}对象的指针。
 * @since 24
 */
OH_ArkUI_LetterSpacingStyle* OH_ArkUI_LetterSpacingStyle_Create();
 
/**
 * @brief 释放{@link OH_ArkUI_LetterSpacingStyle}对象占用的内存。
 *
 * @param letterSpacingStyle 指向{@link OH_ArkUI_LetterSpacingStyle}对象的指针。
 * @since 24
 */
void OH_ArkUI_LetterSpacingStyle_Destroy(OH_ArkUI_LetterSpacingStyle* letterSpacingStyle);
 
/**
 * @brief 设置字符间距。适用于需要调整文字间距的场景，例如标题加宽间距提升可读性、紧凑排版缩小间距等。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param letterSpacingStyle 指向{@link OH_ArkUI_LetterSpacingStyle}对象的指针。
 * @param letterSpacing 字符间距值，单位为vp。取值范围(-∞, +∞)。正值表示加宽字符间距，负值表示缩小字符间距，0表示使用默认间距。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LetterSpacingStyle_SetLetterSpacing(
    OH_ArkUI_LetterSpacingStyle* letterSpacingStyle, float letterSpacing);
 
/**
 * @brief 获取字符间距。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param letterSpacingStyle 指向{@link OH_ArkUI_LetterSpacingStyle}对象的指针。
 * @param letterSpacing 字符间距值，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LetterSpacingStyle_GetLetterSpacing(
    const OH_ArkUI_LetterSpacingStyle* letterSpacingStyle, float* letterSpacing);
 
/**
 * @brief 创建{@link OH_ArkUI_LineHeightStyle}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_LineHeightStyle_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_LineHeightStyle}对象的指针。
 * @since 24
 */
OH_ArkUI_LineHeightStyle* OH_ArkUI_LineHeightStyle_Create();
 
/**
 * @brief 释放{@link OH_ArkUI_LineHeightStyle}对象占用的内存。
 *
 * @param lineHeightStyle 指向{@link OH_ArkUI_LineHeightStyle}对象的指针。
 * @since 24
 */
void OH_ArkUI_LineHeightStyle_Destroy(OH_ArkUI_LineHeightStyle* lineHeightStyle);
 
/**
 * @brief 设置文本行高。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param lineHeightStyle 指向{@link OH_ArkUI_LineHeightStyle}对象的指针。
 * @param lineHeight 固定行高值，单位为vp。与{@link OH_ArkUI_LineHeightStyle_SetLineHeightMultiple}同时设置时，仅lineHeightMultiple生效，
 *     lineHeight不生效，lineHeightMultiple小于0时不生效，此时使用lineHeight设置行高。取值范围(-∞, +∞)，负值表示自适应字体大小。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LineHeightStyle_SetLineHeight(OH_ArkUI_LineHeightStyle* lineHeightStyle,
    float lineHeight);
 
/**
 * @brief 获取文本行高。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param lineHeightStyle 指向{@link OH_ArkUI_LineHeightStyle}对象的指针。
 * @param lineHeight 固定行高值，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LineHeightStyle_GetLineHeight(const OH_ArkUI_LineHeightStyle* lineHeightStyle,
    float* lineHeight);
 
/**
 * @brief 设置行高样式的行高倍数。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param lineHeightStyle 指向{@link OH_ArkUI_LineHeightStyle}对象的指针。
 * @param lineHeightMultiple 行高倍数。取值范围为[0, +∞)。传入负数时不生效，传入0时等效于设置为1。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LineHeightStyle_SetLineHeightMultiple(OH_ArkUI_LineHeightStyle* lineHeightStyle,
    float lineHeightMultiple);
 
/**
 * @brief 获取行高样式的行高倍数。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param lineHeightStyle 指向{@link OH_ArkUI_LineHeightStyle}对象的指针。
 * @param lineHeightMultiple 行高倍数。取值范围为[0, +∞)。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LineHeightStyle_GetLineHeightMultiple(const OH_ArkUI_LineHeightStyle* lineHeightStyle,
    float* lineHeightMultiple);
 
/**
 * @brief 定义行间距样式。 <br>        可以通过{@link OH_ArkUI_LineSpacingStyle_Create}接口创建对应的行间距样式对象，通过
 * {@link OH_ArkUI_LineSpacingStyle_Destroy}接口销毁行间距样式对象。 <br>        对象创建后可以通过
 * {@link OH_ArkUI_LineSpacingStyle_SetLineSpacing}接口设置具体的行间距值，通过{@link OH_ArkUI_LineSpacingStyle_SetOnlyBetweenLines}
 * 接口设置行间距是否只在行间生效。
 *
 * @since 26.0.0
 */
typedef struct OH_ArkUI_LineSpacingStyle OH_ArkUI_LineSpacingStyle;
 
/**
 * @brief 设置属性字符串样式对象的行间距样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param lineSpacingStyle 指向{@link OH_ArkUI_LineSpacingStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLineSpacingStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_LineSpacingStyle* lineSpacingStyle);
 
/**
 * @brief 获取属性字符串样式对象的行间距样式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param spanStyle 指向{@link OH_ArkUI_SpanStyle}对象的指针。
 * @param lineSpacingStyle 指向{@link OH_ArkUI_LineSpacingStyle}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLineSpacingStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_LineSpacingStyle* lineSpacingStyle);
 
/**
 * @brief 创建{@link OH_ArkUI_LineSpacingStyle}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_LineSpacingStyle_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_LineSpacingStyle}对象的指针。
 * @since 26.0.0
 */
OH_ArkUI_LineSpacingStyle* OH_ArkUI_LineSpacingStyle_Create();

/**
 * @brief 释放{@link OH_ArkUI_LineSpacingStyle}对象占用的内存。
 *
 * @param lineSpacingStyle 指向{@link OH_ArkUI_LineSpacingStyle}对象的指针。
 * @since 26.0.0
 */
void OH_ArkUI_LineSpacingStyle_Destroy(OH_ArkUI_LineSpacingStyle* lineSpacingStyle);
 
/**
 * @brief 设置行间距。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param lineSpacingStyle 指向{@link OH_ArkUI_LineSpacingStyle}对象的指针。
 * @param lineSpacing 行间距值，单位为vp。取值范围(-∞, +∞)。与{@link OH_ArkUI_LineHeightStyle_SetLineHeightMultiple}同时设置时，
 *     仅lineHeightMultiple生效，行间距不生效。lineHeightMultiple小于0时不生效，此时行间距正常生效。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LineSpacingStyle_SetLineSpacing(OH_ArkUI_LineSpacingStyle* lineSpacingStyle,
    float lineSpacing);
 
/**
 * @brief 获取行间距。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param lineSpacingStyle 指向{@link OH_ArkUI_LineSpacingStyle}对象的指针。
 * @param lineSpacing 行间距值，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LineSpacingStyle_GetLineSpacing(const OH_ArkUI_LineSpacingStyle* lineSpacingStyle,
    float* lineSpacing);
 
/**
 * @brief 设置行间距是否只在行间生效。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param lineSpacingStyle 指向{@link OH_ArkUI_LineSpacingStyle}对象的指针。
 * @param onlyBetweenLines 行间距是否只在行间生效。true表示仅在行与行之间添加间距，首行上方、尾行下方无额外间距，false表示所有行之间、首行上方、尾行下方均添加完整行间距。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LineSpacingStyle_SetOnlyBetweenLines(
    OH_ArkUI_LineSpacingStyle* lineSpacingStyle, bool onlyBetweenLines);
 
/**
 * @brief 获取行间距是否只在行间生效。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param lineSpacingStyle 指向{@link OH_ArkUI_LineSpacingStyle}对象的指针。
 * @param onlyBetweenLines 行间距是否只在行间生效。true表示仅在行与行之间添加间距，首行上方、尾行下方无额外间距，false表示所有行之间、首行上方、尾行下方均添加完整行间距。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LineSpacingStyle_GetOnlyBetweenLines(
    const OH_ArkUI_LineSpacingStyle* lineSpacingStyle, bool* onlyBetweenLines);
 
/**
 * @brief 创建{@link OH_ArkUI_BackgroundColorStyle}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_BackgroundColorStyle_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_BackgroundColorStyle}对象的指针。
 * @since 24
 */
OH_ArkUI_BackgroundColorStyle* OH_ArkUI_BackgroundColorStyle_Create();
 
/**
 * @brief 释放{@link OH_ArkUI_BackgroundColorStyle}对象占用的内存。
 *
 * @param style 指向{@link OH_ArkUI_BackgroundColorStyle}对象的指针。
 * @since 24
 */
void OH_ArkUI_BackgroundColorStyle_Destroy(OH_ArkUI_BackgroundColorStyle* style);
 
/**
 * @brief 设置背景颜色样式的背景色。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param style 指向{@link OH_ArkUI_BackgroundColorStyle}对象的指针。
 * @param color 背景颜色，0xARGB格式。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_SetColor(OH_ArkUI_BackgroundColorStyle* style, uint32_t color);
 
/**
 * @brief 获取背景颜色样式的背景色。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param style 指向{@link OH_ArkUI_BackgroundColorStyle}对象的指针。
 * @param color 背景颜色，0xARGB格式。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_GetColor(const OH_ArkUI_BackgroundColorStyle* style, uint32_t* color);
 
/**
 * @brief 设置背景颜色样式的背景圆角。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param style 指向{@link OH_ArkUI_BackgroundColorStyle}对象的指针。
 * @param topLeft 左上角圆角半径，单位为vp。取值范围[0, +∞)。
 * @param topRight 右上角圆角半径，单位为vp。取值范围[0, +∞)。
 * @param bottomLeft 左下角圆角半径，单位为vp。取值范围[0, +∞)。
 * @param bottomRight 右下角圆角半径，单位为vp。取值范围[0, +∞)。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_SetRadius(OH_ArkUI_BackgroundColorStyle* style, float topLeft,
    float topRight, float bottomLeft, float bottomRight);
 
/**
 * @brief 获取背景颜色样式的背景圆角。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param style 指向{@link OH_ArkUI_BackgroundColorStyle}对象的指针。
 * @param topLeft 左上角圆角半径，单位为vp。
 * @param topRight 右上角圆角半径，单位为vp。
 * @param bottomLeft 左下角圆角半径，单位为vp。
 * @param bottomRight 右下角圆角半径，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_GetRadius(const OH_ArkUI_BackgroundColorStyle* style, float* topLeft,
    float* topRight, float* bottomLeft, float* bottomRight);
 
/**
 * @brief 创建{@link OH_ArkUI_UrlStyle}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_UrlStyle_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_UrlStyle}对象的指针。
 * @since 24
 */
OH_ArkUI_UrlStyle* OH_ArkUI_UrlStyle_Create();
 
/**
 * @brief 释放{@link OH_ArkUI_UrlStyle}对象占用的内存。
 *
 * @param style 指向{@link OH_ArkUI_UrlStyle}对象的指针。
 * @since 24
 */
void OH_ArkUI_UrlStyle_Destroy(OH_ArkUI_UrlStyle* style);
 
/**
 * @brief 设置超链接样式的超链接内容。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param style 指向{@link OH_ArkUI_UrlStyle}对象的指针。
 * @param url 超链接内容。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_UrlStyle_SetUrl(OH_ArkUI_UrlStyle* style, const char* url);
 
/**
 * @brief 获取超链接样式的超链接内容。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param style 指向{@link OH_ArkUI_UrlStyle}对象的指针。
 * @param buffer 超链接内容写入内存的缓冲区，内存空间需由开发者分配。
 * @param bufferSize 缓冲区最多可写入的字符的数量。
 * @param writeLength 返回{@link ARKUI_ERROR_CODE_NO_ERROR}时，表示实际写入缓冲区的字符的数量。
 *     <br>返回{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}时，表示字符串完整写入缓冲区所需要的最小长度。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 缓冲区大小不足，可通过writeLength参数获取所需最小缓冲区大小，重新分配足够大小的缓冲区后再次调用。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_UrlStyle_GetUrl(const OH_ArkUI_UrlStyle* style, char* buffer, int32_t bufferSize,
    int32_t* writeLength);
 
/**
 * @brief 创建{@link OH_ArkUI_UserDataSpan}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_UserDataSpan_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_UserDataSpan}对象的指针。
 * @since 24
 */
OH_ArkUI_UserDataSpan* OH_ArkUI_UserDataSpan_Create();
 
/**
 * @brief 释放{@link OH_ArkUI_UserDataSpan}对象占用的内存。
 *
 * @param userDataSpan 指向{@link OH_ArkUI_UserDataSpan}对象的指针。
 * @since 24
 */
void OH_ArkUI_UserDataSpan_Destroy(OH_ArkUI_UserDataSpan* userDataSpan);
 
/**
 * @brief 设置用户数据Span样式中的用户数据。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param userDataSpan 指向{@link OH_ArkUI_UserDataSpan}对象的指针。
 * @param userData 用户数据，生命周期需由开发者自行管理。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_UserDataSpan_SetUserData(OH_ArkUI_UserDataSpan* userDataSpan, void* userData);
 
/**
 * @brief 获取用户数据Span样式中的用户数据。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param userDataSpan 指向{@link OH_ArkUI_UserDataSpan}对象的指针。
 * @param userData 用户数据。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_UserDataSpan_GetUserData(const OH_ArkUI_UserDataSpan* userDataSpan, void** userData);
 
/**
 * @brief 创建{@link OH_ArkUI_CustomSpan}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_CustomSpan_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_CustomSpan}对象的指针。
 * @since 24
 */
OH_ArkUI_CustomSpan* OH_ArkUI_CustomSpan_Create();
 
/**
 * @brief 释放{@link OH_ArkUI_CustomSpan}对象占用的内存。
 *
 * @param customSpan 指向{@link OH_ArkUI_CustomSpan}对象的指针。
 * @since 24
 */
void OH_ArkUI_CustomSpan_Destroy(OH_ArkUI_CustomSpan* customSpan);
 
/**
 * @brief 设置自定义绘制Span获取尺寸大小时的回调函数。适用于在文本中嵌入自定义内容（如自定义图标、内联控件、特殊表情等）时，需要根据内容计算占用尺寸的场景。回调返回的尺寸将影响该Span在文本排版中的占位大小。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param customSpan 指向{@link OH_ArkUI_CustomSpan}对象的指针。
 * @param onMeasure The callback function for measuring the size of custom span.
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_CustomSpan_RegisterOnMeasureCallback(
    OH_ArkUI_CustomSpan* customSpan, ArkUI_CustomSpanMetrics*(*onMeasure)(float));
 
/**
 * @brief 注册自定义绘制Span绘制时的回调函数。适用于需要绘制非标准文本内容的场景，例如在文本中绘制自定义图标、装饰图形、特殊标记等。通过该回调，开发者可以使用图形绘制上下文实现任意自定义绘制效果。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param customSpan 指向{@link OH_ArkUI_CustomSpan}对象的指针。
 * @param onDraw The callback function for drawing the custom span.
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_CustomSpan_RegisterOnDrawCallback(
    OH_ArkUI_CustomSpan* customSpan, void(*onDraw)(ArkUI_DrawContext*, ArkUI_CustomSpanDrawInfo*));
 
/**
 * @brief 创建{@link OH_ArkUI_ImageAttachment}对象。
 *
 * @note 当该对象不再使用时，调用 OH_ArkUI_ImageAttachment_Destroy 来销毁它。
 * @return 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @since 24
 */
OH_ArkUI_ImageAttachment* OH_ArkUI_ImageAttachment_Create();
 
/**
 * @brief 释放{@link OH_ArkUI_ImageAttachment}对象占用的内存。
 *
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @since 24
 */
void OH_ArkUI_ImageAttachment_Destroy(OH_ArkUI_ImageAttachment* imageAttachment);
 
/**
 * @brief 设置图片样式中的图片数据源。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param pixelmap 图片数据源。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetPixelMap(OH_ArkUI_ImageAttachment* imageAttachment,
    struct OH_PixelmapNative* pixelmap);
 
/**
 * @brief 获取图片样式中的图片数据源。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param pixelmap 图片数据源。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetPixelMap(const OH_ArkUI_ImageAttachment* imageAttachment,
    struct OH_PixelmapNative** pixelmap);
 
/**
 * @brief 设置图片样式中的图片资源地址。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param resource 图片资源地址。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetResource(OH_ArkUI_ImageAttachment* imageAttachment, const char* resource);
 
/**
 * @brief 获取图片样式中的图片资源地址。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param buffer 图片资源地址字符串写入内存的缓冲区，内存空间需由开发者分配。
 * @param bufferSize 缓冲区大小。
 * @param writeLength 返回{@link ARKUI_ERROR_CODE_NO_ERROR}时，表示实际写入缓冲区的字符串长度。
 *     <br>返回{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}时，表示字符串完整写入缓冲区所需要的最小长度。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 缓冲区大小不足。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetResource(const OH_ArkUI_ImageAttachment* imageAttachment,
    char* buffer, int32_t bufferSize, int32_t* writeLength);
 
/**
 * @brief 设置图片样式中的图片宽度。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param width 图片宽度，单位为vp。取值范围[0, +∞)。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSizeWidth(OH_ArkUI_ImageAttachment* imageAttachment, float width);
 
/**
 * @brief 获取图片样式中的图片宽度。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param width 图片宽度，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSizeWidth(const OH_ArkUI_ImageAttachment* imageAttachment, float* width);
 
/**
 * @brief 设置图片样式中的图片高度。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param height 图片高度，单位为vp。取值范围[0, +∞)。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSizeHeight(OH_ArkUI_ImageAttachment* imageAttachment, float height);
 
/**
 * @brief 获取图片样式中的图片高度。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param height 图片高度，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSizeHeight(const OH_ArkUI_ImageAttachment* imageAttachment, float* height);

/**
 * @brief 设置图片样式中的图片对齐方式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param verticalAlign 图片对齐方式。取值为{@link ArkUI_ImageSpanAlignment}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetVerticalAlign(
    OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_ImageSpanAlignment verticalAlign);
 
/**
 * @brief 获取图片样式中的图片对齐方式。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param verticalAlign 图片对齐方式。取值为{@link ArkUI_ImageSpanAlignment}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetVerticalAlign(const OH_ArkUI_ImageAttachment* imageAttachment,
    ArkUI_ImageSpanAlignment* verticalAlign);
 
/**
 * @brief 设置图片样式中的图片缩放类型。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param objectFit 图片缩放类型。取值为{@link ArkUI_ObjectFit}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetObjectFit(
    OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_ObjectFit objectFit);
 
/**
 * @brief 获取图片样式中的图片缩放类型。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param objectFit 图片缩放类型。取值为{@link ArkUI_ObjectFit}中的枚举。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetObjectFit(
    const OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_ObjectFit* objectFit);
 
/**
 * @brief 设置图片样式中的图片外边距。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param margin 图片外边距，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetMargin(OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_Margin margin);
 
/**
 * @brief 获取图片样式中的图片外边距。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param margin 图片外边距，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetMargin(const OH_ArkUI_ImageAttachment* imageAttachment,
    ArkUI_Margin* margin);
 
/**
 * @brief 设置图片样式中的图片内边距。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param padding 图片内边距，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetPadding(OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_Margin padding);
 
/**
 * @brief 获取图片样式中的图片内边距。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param padding 图片内边距，单位为vp。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetPadding(const OH_ArkUI_ImageAttachment* imageAttachment,
    ArkUI_Margin* padding);
 
/**
 * @brief 设置图片样式中的图片圆角。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param topLeft 左上角圆角半径，单位为vp。取值范围[0, +∞)。
 * @param topRight 右上角圆角半径，单位为vp。取值范围[0, +∞)。
 * @param bottomLeft 左下角圆角半径，单位为vp。取值范围[0, +∞)。
 * @param bottomRight 右下角圆角半径，单位为vp。取值范围[0, +∞)。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetBorderRadiuses(OH_ArkUI_ImageAttachment* imageAttachment,
    float topLeft, float topRight, float bottomLeft, float bottomRight);
 
/**
 * @brief 获取图片样式中的图片圆角。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param topLeft 左上角圆角半径，单位为vp。取值范围[0, +∞)。
 * @param topRight 右上角圆角半径，单位为vp。取值范围[0, +∞)。
 * @param bottomLeft 左下角圆角半径，单位为vp。取值范围[0, +∞)。
 * @param bottomRight 右下角圆角半径，单位为vp。取值范围[0, +∞)。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetBorderRadiuses(const OH_ArkUI_ImageAttachment* imageAttachment,
    float* topLeft, float* topRight, float* bottomLeft, float* bottomRight);
 
/**
 * @brief 设置图片样式中的图片颜色过滤器。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param colorFilter 图片颜色过滤器。
 * @param size 颜色过滤器数组的元素数量。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetColorFilter(
    OH_ArkUI_ImageAttachment* imageAttachment, const float* colorFilter, uint32_t size);
 
/**
 * @brief 获取图片样式中的图片颜色过滤器。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param colorFilter 图片颜色过滤器写入内存的缓冲区，内存空间需由开发者分配。
 * @param colorFilterSize 缓冲区大小。
 * @param writeLength 图片颜色过滤器数组的实际大小。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 缓冲区大小不足。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetColorFilter(const OH_ArkUI_ImageAttachment* imageAttachment,
    float** colorFilter, uint32_t colorFilterSize, uint32_t* writeLength);
 
/**
 * @brief 设置图片样式中的图片颜色滤镜。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param drawingColorFilter 图片颜色滤镜。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetDrawingColorFilter(
    OH_ArkUI_ImageAttachment* imageAttachment, const OH_Drawing_ColorFilter* drawingColorFilter);
 
/**
 * @brief 获取图片样式中的图片颜色滤镜。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param drawingColorFilter 图片颜色滤镜。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetDrawingColorFilter(
    const OH_ArkUI_ImageAttachment* imageAttachment, OH_Drawing_ColorFilter* drawingColorFilter);
 
/**
 * @brief 设置图片样式中是否同步加载图片。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param syncLoad 是否同步加载图片。true表示同步加载，同步加载时阻塞UI线程，不会显示占位图；false表示异步加载。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSyncLoad(OH_ArkUI_ImageAttachment* imageAttachment, bool syncLoad);
 
/**
 * @brief 获取图片样式中是否同步加载图片。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param syncLoad 是否同步加载图片。true表示同步加载；false表示异步加载。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSyncLoad(const OH_ArkUI_ImageAttachment* imageAttachment, bool* syncLoad);
 
/**
 * @brief 设置图片样式中是否开启SVG标签解析能力增强功能。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param supportSvg 是否开启SVG标签解析能力增强功能。true表示开启；false表示不开启。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSupportSvg(OH_ArkUI_ImageAttachment* imageAttachment, bool supportSvg);
 
/**
 * @brief 获取图片样式中是否开启SVG标签解析能力增强功能。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param imageAttachment 指向{@link OH_ArkUI_ImageAttachment}对象的指针。
 * @param supportSvg 是否开启SVG标签解析能力增强功能。true表示开启；false表示未开启。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSupportSvg(const OH_ArkUI_ImageAttachment* imageAttachment,
    bool* supportSvg);

/**
 * @brief 获取文本变化信息中待被替换的原文本的范围。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param event 指向{@link OH_ArkUI_TextEditorChangeEvent}对象的指针。
 * @param start 待替换内容范围的起始索引。
 * @param end 待替换内容范围的结束索引。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorChangeEvent_GetRangeBefore(const OH_ArkUI_TextEditorChangeEvent* event,
    uint32_t* start, uint32_t* end);

/**
 * @brief 获取文本变化信息中的用于替换的属性字符串。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param event 指向{@link OH_ArkUI_TextEditorChangeEvent}对象的指针。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorChangeEvent_GetReplacementStyledString(
    const OH_ArkUI_TextEditorChangeEvent* event, ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief 获取文本变化信息中的预览内容属性字符串。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param event 指向{@link OH_ArkUI_TextEditorChangeEvent}对象的指针。
 * @param descriptor 指向{@link ArkUI_StyledString_Descriptor}对象的指针。
 * @return 返回结果码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorChangeEvent_GetPreviewStyledString(
    const OH_ArkUI_TextEditorChangeEvent* event, ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief 定义文本布局管理器对象。
 *
 * @since 22
 */
typedef struct ArkUI_TextLayoutManager ArkUI_TextLayoutManager;

/**
 * @brief 释放文本布局管理器对象占用的内存。
 *
 * @param layoutManager 指向ArkUI_TextLayoutManager对象的指针。
 * @since 22
 */
void OH_ArkUI_TextLayoutManager_Dispose(ArkUI_TextLayoutManager* layoutManager);

/**
 * @brief 获取文本行数。
 *
 * @param layoutManager 指向ArkUI_TextLayoutManager对象的指针。
 * @param outLineCount 文本行数。
 * @return 返回结果。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetLineCount(ArkUI_TextLayoutManager* layoutManager, int32_t* outLineCount);

/**
 * @brief 获取给定的矩形区域宽度样式以及高度样式的规格下，文本中任意区间范围内的字符或占位符所占的绘制区域信息。
 *
 * @param layoutManager 指向ArkUI_TextLayoutManager对象的指针。
 * @param start 起始位置索引，start取值需要大于等于0，否则会返回参数异常。
 * @param end 结束位置索引，end取值需要大于等于start，否则会返回参数异常。
 * @param widthStyle 矩形区域宽度样式。
 * @param heightStyle 矩形区域高度样式。
 * @param outTextBoxes 指向OH_Drawing_TextBox对象的二级指针。
 * @return 返回结果。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetRectsForRange(ArkUI_TextLayoutManager* layoutManager,
    int32_t start, int32_t end, OH_Drawing_RectWidthStyle widthStyle, OH_Drawing_RectHeightStyle heightStyle,
    OH_Drawing_TextBox** outTextBoxes);

/**
 * @brief 获取距离给定坐标最近的字形(glyph)的位置信息。返回的位置索引基于字形单位而非字符单位——字形是渲染视觉单位，与字符(character)可能存在多对多映射关系。例如文本为"世界Hello"，其字形索引范围为[0,
 * 7]，一个汉字占三个字符，其对应的字符索引范围为[0, 11]。
 *
 * @param layoutManager 指向ArkUI_TextLayoutManager对象的指针。
 * @param dx 相对于控件的x坐标，单位为px。
 * @param dy 相对于控件的y坐标，单位为px。
 * @param outPos 指向OH_Drawing_PositionAndAffinity对象的二级指针。
 * @return 返回结果。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetGlyphPositionAtCoordinate(
    ArkUI_TextLayoutManager* layoutManager, double dx, double dy, OH_Drawing_PositionAndAffinity** outPos);

/**
 * @brief 获取指定行的行信息、文本样式信息、以及字体属性信息。
 *
 * @param layoutManager 指向ArkUI_TextLayoutManager对象的指针。
 * @param lineNumber 指定行的行号索引，行号索引从0开始计数，lineNumber小于0或大于等于文本行数时会返回参数异常。
 * @param outMetrics 指向OH_Drawing_LineMetrics对象的指针。
 * @return 返回结果。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetLineMetrics(ArkUI_TextLayoutManager* layoutManager,
    int32_t lineNumber, OH_Drawing_LineMetrics* outMetrics);

/**
 * @brief 获取距离指定坐标最近的字符的位置信息。
 *
 * @param layoutManager 指向{@link ArkUI_TextLayoutManager}对象的指针。
 * @param dx 相对于控件的x坐标，单位为px。
 * @param dy 相对于控件的y坐标，单位为px。
 * @param outPos 指向{@link OH_Drawing_PositionAndAffinity}对象的二级指针。
 * @return 返回结果。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinate(
    ArkUI_TextLayoutManager* layoutManager, double dx, double dy, OH_Drawing_PositionAndAffinity** outPos);

/**
 * @brief 获取由指定字符索引范围所生成的字形索引范围以及实际的字符索引范围。例如文本为"世界Hello"，其中文本"世"的字形索引范围为[0, 1]，一个汉字占三个字符，所以其对应的字符索引范围为[0, 3]。
 * 如果指定的字符索引范围是[0, 1]，但无法解析出三分之一个汉字，所以实际的字符索引范围是[0, 3]。outGlyphRange、outActualCharRange返回的{@link OH_Drawing_Range}
 * 对象在使用完成后，需通过{@link OH_Drawing_ReleaseRangeBuffer}释放。
 *
 * @param layoutManager 指向{@link ArkUI_TextLayoutManager}对象的指针。
 * @param charRange 指向{@link OH_Drawing_Range}对象的指针，表示字符索引范围。
 * @param outGlyphRange 指向{@link OH_Drawing_Range}对象的二级指针，表示字形索引范围。
 * @param outActualCharRange 指向{@link OH_Drawing_Range}对象的二级指针，表示实际的字符索引范围。
 * @return 返回结果。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetGlyphRangeForCharacterRange(
    ArkUI_TextLayoutManager* layoutManager, OH_Drawing_Range* charRange,
    OH_Drawing_Range** outGlyphRange, OH_Drawing_Range** outActualCharRange);

/**
 * @brief 获取由指定字形索引范围所生成的字符索引范围以及实际的字形索引范围。例如文本为"世界Hello"，其字形索引范围为[0, 7]，一个汉字占三个字符，所以其对应的字符索引范围为[0, 11]。如果指定的索引范围是[0,
 * 11]，但字形一共只有7个，所以实际的字形索引范围是[0, 7]。outCharRange、outActualGlyphRange返回的{@link OH_Drawing_Range}对象在使用完成后，需通过
 * {@link OH_Drawing_ReleaseRangeBuffer}释放。
 *
 * @param layoutManager 指向{@link ArkUI_TextLayoutManager}对象的指针。
 * @param glyphRange 指向{@link OH_Drawing_Range}对象的指针，表示字形索引范围。
 * @param outCharRange 指向{@link OH_Drawing_Range}对象的二级指针，表示字符索引范围。
 * @param outActualGlyphRange 指向{@link OH_Drawing_Range}对象的二级指针，表示实际的字形索引范围。
 * @return 返回结果。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetCharacterRangeForGlyphRange(
    ArkUI_TextLayoutManager* layoutManager, OH_Drawing_Range* glyphRange,
    OH_Drawing_Range** outCharRange, OH_Drawing_Range** outActualGlyphRange);

/**
 * @brief 设置段落样式的线性渐变。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param linearGradient 指向{@link OH_ArkUI_LinearGradientOptions}对象的指针。
 * @return 返回结果。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLinearGradient(
    OH_ArkUI_ParagraphStyle* paragraphStyle, const OH_ArkUI_LinearGradientOptions* linearGradient);

/**
 * @brief 获取段落样式的线性渐变。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param linearGradient 指向{@link OH_ArkUI_LinearGradientOptions}对象的指针。
 * @return 返回结果。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLinearGradient(
    const OH_ArkUI_ParagraphStyle* paragraphStyle, OH_ArkUI_LinearGradientOptions* linearGradient);

/**
 * @brief 设置段落样式的径向渐变。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param radialGradient 指向{@link OH_ArkUI_RadialGradientOptions}对象的指针。
 * @return 返回结果。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetRadialGradient(
    OH_ArkUI_ParagraphStyle* paragraphStyle, const OH_ArkUI_RadialGradientOptions* radialGradient);

/**
 * @brief 获取段落样式的径向渐变。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param radialGradient 指向{@link OH_ArkUI_RadialGradientOptions}对象的指针。
 * @return 返回结果。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetRadialGradient(
    const OH_ArkUI_ParagraphStyle* paragraphStyle, OH_ArkUI_RadialGradientOptions* radialGradient);

/**
 * @brief 设置段落样式的尾部缩进。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param tailIndents 尾部缩进值数组。单位：fp。取值范围：[0, +∞)。其有效长度由size指定。若size等于1，则所有文本行使用相同的尾部缩进值tailIndents[0]；若size大于1，则第i行（
 *     从0开始计数）使用tailIndents[i]作为尾部缩进值。当文本行数超过size时，超出部分的行将复用tailIndents[size - 1]的值做缩进。
 * @param size tailIndents数组中有效尾部缩进值的个数。
 * @return 返回结果。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTailIndents(
    OH_ArkUI_ParagraphStyle* paragraphStyle, const float* tailIndents, uint32_t size);

/**
 * @brief 获取段落样式的尾部缩进。
 *
 * @note 所有输入指针参数必须由调用者分配、管理和释放。
 * @param paragraphStyle 指向{@link OH_ArkUI_ParagraphStyle}对象的指针。
 * @param tailIndents 尾部缩进值，单位为fp。
 * @param tailIndentsSize tailIndents缓冲区大小。
 * @param writeLength 实际写入缓冲区的尾部缩进值个数。
 * @return 返回结果。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 缓冲区长度小于最小缓冲区长度。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTailIndents(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    float** tailIndents, uint32_t tailIndentsSize, uint32_t* writeLength);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_STYLED_STRING_H
/** @} */

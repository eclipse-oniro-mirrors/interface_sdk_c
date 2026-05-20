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
#ifndef DRAWING_TEXT_FONT_DESCRIPTOR_H
#define DRAWING_TEXT_FONT_DESCRIPTOR_H

#include "drawing_text_declaration.h"
#include "drawing_text_typography.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 字体类型的枚举。
 *
 * @since 14
 */
typedef enum {
    /**
     * 所有字体类型。
     */
    ALL = 1 << 0,

    /**
     * 系统字体类型。
     */
    GENERIC = 1 << 1,

    /**
     * 风格字体类型
     */
    STYLISH = 1 << 2,

    /**
     * 用户已安装字体类型。
     */
    INSTALLED = 1 << 3,

    /**
     * 自定义字体类型。
     * @since 18
    */
    CUSTOMIZED = 1 << 4
} OH_Drawing_SystemFontType;

/**
 * @brief 字体描述符属性的枚举。不同类型的字体描述符属性，请使用对应类型的接口获取属性。如字体描述符属性FULL_DESCRIPTOR_ATTR_I_WEIGHT为int类型，需使用
 * {@link OH_Drawing_GetFontFullDescriptorAttributeInt}接口获取其属性值。
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
     * 字体的字重，int类型。
     */
    FULL_DESCRIPTOR_ATTR_I_WEIGHT = 5,

    /**
     * 字体的宽窄风格属性，int类型。
     */
    FULL_DESCRIPTOR_ATTR_I_WIDTH = 6,

    /**
     * 字体是否倾斜，int类型。1表示字体倾斜，0表示字体非倾斜。
     */
    FULL_DESCRIPTOR_ATTR_I_ITALIC = 7,

    /**
     * 字体是否等宽，bool类型。true表示字体紧凑，false表示字体非紧凑。
     */
    FULL_DESCRIPTOR_ATTR_B_MONO = 8,

    /**
     * 字体是否支持符号字体，bool类型。true表示支持符号字体，false表示不支持符号字体。
     */
    FULL_DESCRIPTOR_ATTR_B_SYMBOLIC = 9,

    /**
    * 根据系统语言配置提取字体唯一标识的名称。
    * @since 23
    */
    FULL_DESCRIPTOR_ATTR_S_LOCAL_POSTSCRIPT_NAME = 10,

    /**
    * 根据系统语言配置提取字体全名。
    * @since 23
    */
    FULL_DESCRIPTOR_ATTR_S_LOCAL_FULL_NAME = 11,

    /**
    * 根据系统语言配置提取字体家族名称。
    * @since 23
    */
    FULL_DESCRIPTOR_ATTR_S_LOCAL_FAMILY_NAME = 12,

    /**
    * 根据系统语言配置提取子字体家族名称。
    * @since 23
    */
    FULL_DESCRIPTOR_ATTR_S_LOCAL_SUB_FAMILY_NAME = 13,

    /**
    * 字体版本。
    * @since 23
    */
    FULL_DESCRIPTOR_ATTR_S_VERSION = 14,

    /**
    * 字体制造商信息。
    * @since 23
    */
    FULL_DESCRIPTOR_ATTR_S_MANUFACTURE = 15,

    /**
    * 字体版权信息。
     * @since 23
     */
    FULL_DESCRIPTOR_ATTR_S_COPYRIGHT = 16,

    /**
    * 字体商标信息。
    * @since 23
    */
    FULL_DESCRIPTOR_ATTR_S_TRADEMARK = 17,

    /**
    * 字体许可证信息。
    * @since 23
    */
    FULL_DESCRIPTOR_ATTR_S_LICENSE = 18,

    /**
    * 字体可变轴数组。
    * @since 24
    */
    FULL_DESCRIPTOR_ATTR_O_VARIATION_AXIS = 19,

    /**
    * 字体可变实例数组。
    * @since 24
    */
    FULL_DESCRIPTOR_ATTR_O_VARIATION_INSTANCE = 20,

    /**
    * 字体索引。
    * @since 23
    */
    FULL_DESCRIPTOR_ATTR_I_INDEX = 21
} OH_Drawing_FontFullDescriptorAttributeId;

/**
* @brief 字体可变轴属性的枚举。
*
* @since 24
*/
typedef enum {
    /**
     * 字体可变轴的关键字标识。
     */
    FONT_VARIATION_AXIS_ATTR_S_KEY = 0,

    /**
     * 字体可变轴的最小值。
     */
    FONT_VARIATION_AXIS_ATTR_D_MIN_VALUE = 1,

    /**
     * 字体可变轴的最大值。
     */
    FONT_VARIATION_AXIS_ATTR_D_MAX_VALUE = 2,

    /**
     * 字体可变轴的默认值。
     */
    FONT_VARIATION_AXIS_ATTR_D_DEFAULT_VALUE = 3,

    /**
     * 字体可变轴的标志位。值为0时表示该轴对用户可见，值为1时表示该轴应隐藏。
     */
    FONT_VARIATION_AXIS_ATTR_I_FLAGS = 4,

    /**
     * 字体可变轴的英文名称。
     */
    FONT_VARIATION_AXIS_ATTR_S_NAME = 5,

    /**
     * 字体可变轴的本地化名称。
     */
    FONT_VARIATION_AXIS_ATTR_S_LOCAL_NAME = 6
} OH_Drawing_FontVariationAxisAttributeId;

/**
 * @brief 字体可变实例属性的枚举。
 *
 * @since 24
 */
typedef enum {
    /**
     * 字体可变实例的英文名称。
     */
    FONT_VARIATION_INSTANCE_ATTR_S_NAME = 0,

    /**
     * 字体可变实例的本地化名称。
     */
    FONT_VARIATION_INSTANCE_ATTR_S_LOCAL_NAME = 1
} OH_Drawing_FontVariationInstanceAttributeId;

/**
 * @brief 字体变体坐标
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
 * @brief 获取与指定字体描述符匹配的所有系统字体描述符，其中{@link OH_Drawing_FontDescriptor}的path字段不作为有效的匹配字段，其余字段不是默认值时生效。
 * <br>如果参数desc的所有字段都是默认值，则获取所有系统字体描述符。
 * <br>如果匹配失败，返回NULL。不再需要{@link OH_Drawing_FontDescriptor}时，请使用{@link OH_Drawing_DestroyFontDescriptors}接口释放该对象的指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param desc 指针。
 *     <br>建议使用{@link OH_Drawing_CreateFontDescriptor}获得有效的{@link OH_Drawing_FontDescriptor}实例。
 *     <br>如果自己创建{@link OH_Drawing_FontDescriptor}实例，请确保不用于匹配的字段是默认值。
 * @param num 表示返回值数组的成员个数。
 * @return {@link OH_Drawing_FontDescriptor}数组，释放时请使用{@link OH_Drawing_DestroyFontDescriptors}。
 * @since 18
 */
OH_Drawing_FontDescriptor* OH_Drawing_MatchFontDescriptors(OH_Drawing_FontDescriptor* desc, size_t* num);

/**
 * @brief 释放字体描述符{@link OH_Drawing_FontDescriptor}数组。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param descriptors 数组。
 * @param num {@link OH_Drawing_FontDescriptor}数组的成员个数。
 * @since 18
 */
void OH_Drawing_DestroyFontDescriptors(OH_Drawing_FontDescriptor* descriptors, size_t num);

/**
 * @brief 根据字体名称和字体类型获取指定的字体描述符，支持系统字体、风格字体和用户已安装字体。
 * <br>字体描述符是描述字体特征的一种数据结构，它包含了定义字体外观和属性的详细信息。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fullName 表示指向字体名称字符串{@link OH_Drawing_String}的指针。
 * @param fontType 表示字体类型的枚举值{@link OH_Drawing_SystemFontType}。
 * @return 指向字体描述符对象{@link OH_Drawing_FontDescriptor}的指针，不再需要{@link OH_Drawing_FontDescriptor}时，请使用
 *     {@link OH_Drawing_DestroyFontDescriptor}接口释放该对象的指针。
 * @since 14
 */
OH_Drawing_FontDescriptor* OH_Drawing_GetFontDescriptorByFullName(const OH_Drawing_String* fullName,
    OH_Drawing_SystemFontType fontType);

/**
 * @brief 根据字体类型获取对应字体的字体名称数组。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontType 表示字体类型的枚举值{@link OH_Drawing_SystemFontType}。
 * @return 返回对应字体类型的字体名称数组{@link OH_Drawing_Array}的指针，不再需要{@link OH_Drawing_Array}时，请使用
 *     {@link OH_Drawing_DestroySystemFontFullNames}接口释放该对象的指针。
 * @since 14
 */
OH_Drawing_Array* OH_Drawing_GetSystemFontFullNamesByType(OH_Drawing_SystemFontType fontType);

/**
 * @brief 在字体名称数组中通过索引获取对应位置的字体名称。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fullNameArray 表示字体名称数组{@link OH_Drawing_Array}的指针。
 * @param index 数组的索引。
 * @return 返回对应索引的字体名称{@link OH_Drawing_String}的指针。
 * @since 14
 */
const OH_Drawing_String* OH_Drawing_GetSystemFontFullNameByIndex(OH_Drawing_Array* fullNameArray, size_t index);

/**
 * @brief 释放通过字体类型获取的对应字体的字体名称数组占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fullNameArray 表示字体名称数组{@link OH_Drawing_Array}的指针。
 * @since 14
 */
void OH_Drawing_DestroySystemFontFullNames(OH_Drawing_Array* fullNameArray);

/**
 * @brief 根据原始二进制数据获取字体描述符数组。
 *
 * @param data 指向原始二进制字体数据缓冲区的指针。
 * @param size 以字节为单位的字体数据缓冲区的大小。
 * @return 返回指向对应字体文件的字体描述符数组{@link OH_Drawing_Array}的指针，不再需要OH_Drawing_Array时，请使用
 *     {@link OH_Drawing_DestroyFontFullDescriptors}接口释放该对象的指针。
 *     <br>如果因数据格式无效或解析错误导致操作失败，返回NULL。
 * @since 22
 */
OH_Drawing_Array* OH_Drawing_GetFontFullDescriptorsFromStream(const void* data, size_t size);

/**
 * @brief 根据字体文件路径获取字体描述符数组。
 *
 * @param path 需要查询的字体文件的路径。
 * @return 返回指向对应字体文件的字体描述符数组{@link OH_Drawing_Array}的指针，不再需要OH_Drawing_Array时，请使用
 *     {@link OH_Drawing_DestroyFontFullDescriptors}接口释放该对象的指针。
 *     <br>如果字体文件未找到、字体文件路径无效、字体文件无权限或者文件非字体格式，返回NULL。
 * @since 22
 */
OH_Drawing_Array* OH_Drawing_GetFontFullDescriptorsFromPath(const char* path);

/**
 * @brief 在字体描述符数组中通过索引获取对应的字体描述符。
 *
 * @param descriptorArray 表示指向字体描述符数组{@link OH_Drawing_Array}的指针。
 * @param index 数组的索引，索引值从0开始。
 * @return 返回指向指定索引处字体描述符对象{@link OH_Drawing_FontFullDescriptor}的指针。
 *     <br>如果索引超出范围或数组无效，则返回NULL。
 * @since 22
 */
const OH_Drawing_FontFullDescriptor* OH_Drawing_GetFontFullDescriptorByIndex(
    OH_Drawing_Array* descriptorArray, size_t index);

/**
 * @brief 释放字体描述符数组占用的内存。
 *
 * @param descriptorArray 表示指向字体描述符数组{@link OH_Drawing_Array}的指针。
 * @since 22
 */
void OH_Drawing_DestroyFontFullDescriptors(OH_Drawing_Array* descriptorArray);

/**
 * @brief 释放字体描述符指针占用内存。本函数可用于释放由{@link OH_Drawing_GetFontFullDescriptorByFullName}接口获取的字体描述符指针。
 *
 * @param descriptor 表示指向字体描述符对象{@link OH_Drawing_FontFullDescriptor}的指针。
 * @since 24
 */
void OH_Drawing_DestroyFontFullDescriptor(const OH_Drawing_FontFullDescriptor* descriptor);

/**
 * @brief 从字体文件中获取unicode码。
 *
 * @param fontSrc 字体文件路径。
 * @param index ttc/otc文件中字体的索引，非ttc/otc文件需设置为0。
 * @param unicodeArray 出参，用于接收unicode码数组，当不需要时，使用free()释放。
 * @param arrayLength 出参，用于接收unicode码数组的长度。
 * @return 函数执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示字体路径非法或不是字体文件。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontUnicodeArrayFromFile(const char* fontSrc, uint32_t index,
    int32_t** unicodeArray, int32_t* arrayLength);

/**
 * @brief 从字体字节流缓存中获取unicode码。
 *
 * @param fontBuffer 字体文件数据。
 * @param length 字体文件数据长度。
 * @param index ttc/otc文件中字体的索引，非ttc/otc文件需设置为0。
 * @param unicodeArray 出参，用于接收unicode码数组，当不需要时，使用free()释放。
 * @param arrayLength 出参，用于接收unicode码数组的长度。
 * @return 函数执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示缓存数据非法或缓存数据不是字体文件数据。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontUnicodeArrayFromBuffer(uint8_t* fontBuffer, size_t length, uint32_t index,
    int32_t** unicodeArray, int32_t* arrayLength);

/**
 * @brief 获取int类型字体描述符的属性。
 *
 * @param descriptor 指向字体描述符对象{@link OH_Drawing_FontFullDescriptor}的指针。
 * @param id 字体描述符属性id。从{@link OH_Drawing_FontFullDescriptorAttributeId}中可获取字体描述符属性。
 * @param value 指向int类型属性的指针。作为出参使用。
 * @return 函数执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数descriptor或者value为空指针。
 *     <br>返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 22
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontFullDescriptorAttributeInt(const OH_Drawing_FontFullDescriptor* descriptor,
    OH_Drawing_FontFullDescriptorAttributeId id, int* value);

/**
 * @brief 获取bool类型字体描述符的属性。
 *
 * @param descriptor 指向字体描述符对象{@link OH_Drawing_FontFullDescriptor}的指针。
 * @param id 字体描述符属性id。从{@link OH_Drawing_FontFullDescriptorAttributeId}中可获取字体描述符属性。
 * @param value 指向bool类型属性的指针。作为出参使用。
 * @return 函数执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数descriptor或者value为空指针。
 *     <br>返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 22
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontFullDescriptorAttributeBool(const OH_Drawing_FontFullDescriptor* descriptor,
    OH_Drawing_FontFullDescriptorAttributeId id, bool* value);

/**
 * @brief 获取{@link OH_Drawing_String}类型字体描述符的属性。
 *
 * @note The caller is responsible for manually releasing the internal <b>strData</b> member of the
 *     <b>OH_Drawing_String</b> structure when it is no longer needed.
 *
 * @param descriptor 指向字体描述符对象{@link OH_Drawing_FontFullDescriptor}的指针。
 * @param id 字体描述符属性id。从{@link OH_Drawing_FontFullDescriptorAttributeId}中可获取字体描述符属性。
 * @param str 指向OH_Drawing_String类型属性的指针。作为出参使用。
 * @return 函数执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数descriptor或者str为空指针。
 *     <br>返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 22
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontFullDescriptorAttributeString(const OH_Drawing_FontFullDescriptor* descriptor,
    OH_Drawing_FontFullDescriptorAttributeId id, OH_Drawing_String* str);

/**
 * @brief 获取字体描述符的对象数组属性。
 *
 * @param descriptor 指向字体描述符对象{@link OH_Drawing_FontFullDescriptor}的指针。
 * @param id 字体描述符属性id。从{@link OH_Drawing_FontFullDescriptorAttributeId}中可获取字体描述符属性。
 * @return 返回对象数组。
 * @since 24
 */
OH_Drawing_Array* OH_Drawing_GetFontFullDescriptorAttributeArray(const OH_Drawing_FontFullDescriptor* descriptor,
    OH_Drawing_FontFullDescriptorAttributeId id);

/**
 * @brief 在字体可变轴数组中通过索引获取对应的字体可变轴。
 *
 * @param array 指向字体可变轴数组{@link OH_Drawing_Array}的指针。
 * @param index 数组的索引，索引值从0开始。
 * @return 返回指向指定索引处字体可变轴对象{@link OH_Drawing_FontVariationAxis}的指针。
 *     <br>如果索引超出范围或数组无效，则返回NULL。
 * @since 24
 */
OH_Drawing_FontVariationAxis* OH_Drawing_GetFontVariationAxisByIndex(OH_Drawing_Array* array, size_t index);

/**
 * @brief 释放字体可变轴数组占用的内存。
 *
 * @param fontVariaAxisArray 指向字体可变轴数组对象{@link OH_Drawing_Array}的指针。
 * @since 24
 */
void OH_Drawing_DestroyFontVariationAxis(OH_Drawing_Array* fontVariaAxisArray);

/**
 * @brief 获取double类型字体可变轴的属性。
 *
 * @param variationAxis 指向字体可变轴对象{@link OH_Drawing_FontVariationAxis}的指针。
 * @param id 字体可变轴属性id。从{@link OH_Drawing_FontVariationAxisAttributeId}中可获取字体可变轴的属性。
 * @param value 指向double类型属性的指针。作为出参使用。
 * @return 函数执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数variationAxis或者value为空指针。
 *     <br>返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 24
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontVariationAxisAttributeDouble(OH_Drawing_FontVariationAxis* variationAxis,
    OH_Drawing_FontVariationAxisAttributeId id, double *value);

/**
 * @brief 获取int类型字体可变轴的属性。
 *
 * @param variationAxis 指向字体可变轴对象{@link OH_Drawing_FontVariationAxis}的指针。
 * @param id 字体可变轴属性id。从{@link OH_Drawing_FontVariationAxisAttributeId}中可获取字体可变轴的属性。
 * @param value 指向int类型属性的指针。作为出参使用。
 * @return 函数执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数variationAxis或者value为空指针。
 *     <br>返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 24
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontVariationAxisAttributeInt(OH_Drawing_FontVariationAxis* variationAxis,
    OH_Drawing_FontVariationAxisAttributeId id, int *value);

/**
 * @brief 获取{@link OH_Drawing_String}类型字体可变轴的属性。
 *
 * @note The caller is responsible for manually releasing the internal <b>strData</b> member of the
 *     <b>OH_Drawing_String</b> structure when it is no longer needed.
 *
 * @param variationAxis 指向字体可变轴对象{@link OH_Drawing_FontVariationAxis}的指针。
 * @param id 字体可变轴属性id。从{@link OH_Drawing_FontVariationAxisAttributeId}中可获取字体可变轴的属性。
 * @param str 指向OH_Drawing_String类型属性的指针。作为出参使用。
 * @return 函数执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数variationAxis或者str为空指针。
 *     <br>返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 24
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontVariationAxisAttributeStr(OH_Drawing_FontVariationAxis* variationAxis,
    OH_Drawing_FontVariationAxisAttributeId id, OH_Drawing_String *str);

/**
 * @brief 在字体可变实例数组中通过索引获取对应的字体可变实例。
 *
 * @param array 指向字体可变实例数组{@link OH_Drawing_Array}的指针。
 * @param index 数组的索引，索引值从0开始。
 * @return 返回指向指定索引处字体可变实例对象{@link OH_Drawing_FontVariationInstance}的指针。
 *     <br>如果索引超出范围或数组无效，则返回NULL。
 * @since 24
 */
OH_Drawing_FontVariationInstance* OH_Drawing_GetFontVariationInstanceByIndex(OH_Drawing_Array* array, size_t index);

/**
 * @brief 释放字体可变实例数组占用的内存。
 *
 * @param fontVariaAxisInstance 指向字体可变实例数组对象{@link OH_Drawing_Array}的指针。
 * @since 24
 */
void OH_Drawing_DestroyFontVariationInstance(OH_Drawing_Array* fontVariaAxisInstance);

/**
 * @brief 获取{@link OH_Drawing_String}类型字体可变实例的属性。
 *
 * @note The caller is responsible for manually releasing the internal <b>strData</b> member of the
 *     <b>OH_Drawing_String</b> structure when it is no longer needed.
 *
 * @param variationInstance 指向字体可变实例对象{@link OH_Drawing_FontVariationInstance}的指针。
 * @param id 字体可变实例属性id。从{@link OH_Drawing_FontVariationInstanceAttributeId}中可获取字体可变实例属性。
 * @param str 指向OH_Drawing_String类型属性的指针。作为出参使用。
 * @return 函数执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数variationInstance或者str为空指针。
 *     <br>返回OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH，表示传入属性id与调用函数不匹配。
 * @since 24
 */
OH_Drawing_ErrorCode OH_Drawing_GetFontVariationInstanceAttributeStr(
    OH_Drawing_FontVariationInstance* variationInstance,
    OH_Drawing_FontVariationInstanceAttributeId id,
    OH_Drawing_String* str);

/**
 * @brief 获取字体可变实例的可变字体属性对象。
 *
 * @param variationInstance 指向字体可变实例的指针。
 * @param arrayLength 指向OH_Drawing_FontVariationInstanceCoordinate列表长度的指针。
 * @return 返回指向可变字体属性列表的指针。
 * @since 24
 */
OH_Drawing_FontVariationInstanceCoordinate* OH_Drawing_GetFontVariationInstanceCoordinate(
    OH_Drawing_FontVariationInstance* variationInstance, size_t* arrayLength);

/**
 * @brief 根据字体名称和字体类型获取字体完整描述符对象。
 *
 * @param fullName 指向字体名称对象{@link OH_Drawing_String}的指针。
 * @param fontType 系统字体类型对象{@link OH_Drawing_SystemFontType}的枚举值。
 * @return 返回指向字体完整描述符对象{@link OH_Drawing_FontFullDescriptor}的指针。不再需要OH_Drawing_FontFullDescriptor时，请使用
 *     {@link OH_Drawing_DestroyFontFullDescriptor}接口释放该对象的指针。
 * @since 24
 */
const OH_Drawing_FontFullDescriptor* OH_Drawing_GetFontFullDescriptorByFullName(const OH_Drawing_String* fullName,
    OH_Drawing_SystemFontType fontType);

/**
 * @brief 获取字体文件中包含的字体数量。
 *
 * @param fontSrc 字体文件路径。
 * @return 字体数量。
 * @since 23
 */
uint32_t OH_Drawing_GetFontCountFromFile(const char* fontSrc);

/**
* @brief 获取字体缓存数据中包含的字体数量。
*
* @param fontBuffer 字体缓存数据。
* @param length 字体数据长度。
* @return 字体数量。
* @since 23
*/
uint32_t OH_Drawing_GetFontCountFromBuffer(uint8_t* fontBuffer, size_t length);

/**
 * @brief 获取指定字体类型的所有字体文件路径。
 *
 * @param fontType 系统字体类型对象 {@link OH_Drawing_SystemFontType} 的枚举。
 * @param pathCount 返回的字体路径列表的数量。
 * @return 返回一个字体路径对象OH_Drawing_String列表。不再需要时，请使用free释放该对象指针以及每个OH_Drawing_String对象内部持有的指针。
 * @since 23
 */
OH_Drawing_String* OH_Drawing_GetFontPathsByType(OH_Drawing_SystemFontType fontType, size_t* pathCount);

#ifdef __cplusplus
}
#endif

/** @} */
#endif
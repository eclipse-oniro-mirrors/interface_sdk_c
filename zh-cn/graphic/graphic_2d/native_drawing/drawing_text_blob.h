/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
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
 * @brief Drawing模块提供包括2D图形渲染、文字绘制和图片显示等功能函数。
 * <br>本模块采用屏幕物理像素单位px。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @since 11
 * @version 1.0
 */
/**
 * @file drawing_text_blob.h
 *
 * @brief 文件中定义了与文字相关的功能函数。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_TEXT_BLOB_H
#define C_INCLUDE_DRAWING_TEXT_BLOB_H

#include "drawing_types.h"
#include "drawing_error_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于创建一个文本构造器对象。
 *
 * @return 函数返回一个指针，指针指向创建的文本构造器对象。
 * @since 11
 * @version 1.0
 */
OH_Drawing_TextBlobBuilder* OH_Drawing_TextBlobBuilderCreate(void);

/**
 * @brief 使用文本创建一个文本对象。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>text、font任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * <br>textEncoding不在枚举范围内返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param text 指向文本的指针。
 * @param byteLength 文本的字节长度。
 * @param font 指向字体对象OH_Drawing_Font的指针。
 * @param textEncoding 文本编码类型。
 * @return 函数返回一个指针，指针指向创建的文本对象OH_Drawing_TextBlob。
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextBlob* OH_Drawing_TextBlobCreateFromText(const void* text, size_t byteLength,
    const OH_Drawing_Font* font, OH_Drawing_TextEncoding textEncoding);

/**
 * @brief 使用文本创建一组文本对象，支持字体回退。
 * 若当前字体的字形不支持某些字符时，会自动从系统中查找回退字体。每段连续且使用相同字体的字符会创建一个文本对象。
 * 所有文本对象共享整个字符串的坐标系：每个文本对象的字形位置已包含前序文本的宽度，因此所有文本对象应在同一原点绘制。
 *
 * @param text [in] 指向文本的指针。
 * @param byteLength [in] 文本长度，单位为字节。
 * @param font [in] 指向字型对象OH_Drawing_Font的指针。
 * @param textEncoding [in] 文本编码类型OH_Drawing_TextEncoding。
 * @param textBlobs [out] 指向OH_Drawing_TextBlob对象数组的指针。作为出参使用。当不再需要时，使用{@link OH_Drawing_TextBlobsArrayDestroy}释放该数组。
 * @param textBlobsCount [out] 返回数组中文本对象的数量。作为出参使用。
 * @return 返回{@link OH_DRAWING_SUCCESS} 表示执行成功。
 *     <br>返回{@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} 表示参数text、font、textBlobs、textBlobsCount任意一个为空，或者byteLength为0。
 *     <br>返回{@link OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE} 表示textEncoding不在枚举范围内。
 *     <br>返回{@link OH_DRAWING_ERROR_ALLOCATION_FAILED} 表示数组内存分配失败。
 * @release drawing_text_blob/OH_Drawing_TextBlobsArrayDestroy {textBlobs}
 * @since 26.0.1
 */
OH_Drawing_ErrorCode OH_Drawing_TextBlobCreateFromTextWithFallback(const void *text, uint32_t byteLength,
    const OH_Drawing_Font *font, OH_Drawing_TextEncoding textEncoding, OH_Drawing_TextBlob ***textBlobs,
    uint32_t *textBlobsCount);

/**
 * @brief 使用文本创建文本对象，文本对象中每个字符的坐标由OH_Drawing_Point2D数组中对应的坐标信息决定。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>text、point2D、font任意一个为NULL或byteLength等于0时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * <br>textEncoding不在枚举范围内返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param text 指向文本的指针。
 * @param byteLength 文本的字节长度。
 * @param point2D 二维点OH_Drawing_Point2D数组首地址，数组个数由{@link drawing_font.h#OH_Drawing_FontCountText}的计算结果决定。
 * @param font 指向字体对象OH_Drawing_Font的指针。
 * @param textEncoding 文本编码类型OH_Drawing_TextEncoding。
 * @return 函数返回一个指针，指针指向创建的文本对象OH_Drawing_TextBlob。
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextBlob* OH_Drawing_TextBlobCreateFromPosText(const void* text, size_t byteLength,
    OH_Drawing_Point2D* point2D, const OH_Drawing_Font* font, OH_Drawing_TextEncoding textEncoding);

/**
 * @brief 使用文本创建一组文本对象，支持字体回退。
 * 若当前字体的字形不支持某些字符时，会自动从系统中查找回退字体。
 * 每段连续且使用相同字体的字符会创建一个文本对象。文本对象中每个字符的坐标由OH_Drawing_Point2D数组中对应的坐标信息决定。
 *
 * @param text [in] 指向文本的指针。
 * @param byteLength [in] 文本长度，单位为字节。
 * @param point2D [in] 二维点OH_Drawing_Point2D数组首地址，数组个数由{@link OH_Drawing_FontCountText}的计算结果决定。
 * @param font [in] 指向字型对象OH_Drawing_Font的指针。
 * @param textEncoding [in] 文本编码类型OH_Drawing_TextEncoding。
 * @param textBlobs [out] 指向OH_Drawing_TextBlob对象数组的指针。作为出参使用。当不再需要时，使用{@link OH_Drawing_TextBlobsArrayDestroy}释放该数组。
 * @param textBlobsCount [out] 返回数组中文本对象的数量。作为出参使用。
 * @return 返回{@link OH_DRAWING_SUCCESS} 表示执行成功。
 *     <br>返回{@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} 表示参数text、point2D、font、textBlobs、textBlobsCount任意一个为空，
 *     或者byteLength为0。
 *     <br>返回{@link OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE} 表示textEncoding不在枚举范围内。
 *     <br>返回{@link OH_DRAWING_ERROR_ALLOCATION_FAILED} 表示数组内存分配失败。
 * @release drawing_text_blob/OH_Drawing_TextBlobsArrayDestroy {textBlobs}
 * @since 26.0.1
 */
OH_Drawing_ErrorCode OH_Drawing_TextBlobCreateFromPosTextWithFallback(const void *text, uint32_t byteLength,
    OH_Drawing_Point2D *point2D, const OH_Drawing_Font *font, OH_Drawing_TextEncoding textEncoding,
    OH_Drawing_TextBlob ***textBlobs, uint32_t *textBlobsCount);

/**
 * @brief 使用字符串创建文本对象。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>str、font任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * <br>textEncoding不在枚举范围内返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param str 指向字符串的指针。
 * @param font 指向字体对象OH_Drawing_Font的指针。
 * @param textEncoding 文本编码类型OH_Drawing_TextEncoding。
 * @return 函数返回一个指针，指针指向创建的文本对象OH_Drawing_TextBlob。
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextBlob* OH_Drawing_TextBlobCreateFromString(const char* str,
    const OH_Drawing_Font* font, OH_Drawing_TextEncoding textEncoding);

/**
 * @brief 使用字符串创建一组文本对象，支持字体回退。
 * 若当前字体的字形不支持某些字符时，会自动从系统中查找回退字体。每段连续且使用相同字体的字符会创建一个文本对象。
 * 所有文本对象共享整个字符串的坐标系：每个文本对象的字形位置已包含前序文本的宽度，因此所有文本对象应在同一原点绘制。
 *
 * @param str [in] 指向字符串的指针。
 * @param font [in] 指向字型对象{@link OH_Drawing_Font}的指针。
 * @param textEncoding [in] 文本编码类型{@link OH_Drawing_TextEncoding}。
 * @param textBlobs [out] 指向OH_Drawing_TextBlob对象数组的指针。作为出参使用。当不再需要时，使用{@link OH_Drawing_TextBlobsArrayDestroy}释放该数组。
 * @param textBlobsCount [out] 返回数组中文本对象的数量。作为出参使用。
 * @return 返回{@link OH_DRAWING_SUCCESS} 表示执行成功。
 *     <br>返回{@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} 表示参数str、font、textBlobs、textBlobsCount任意一个为空。
 *     <br>返回{@link OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE} 表示textEncoding不在枚举范围内。
 * @release drawing_text_blob/OH_Drawing_TextBlobsArrayDestroy {textBlobs}
 * @since 26.0.1
 */
OH_Drawing_ErrorCode OH_Drawing_TextBlobCreateFromStringWithFallback(const char *str,
    const OH_Drawing_Font *font, OH_Drawing_TextEncoding textEncoding,
    OH_Drawing_TextBlob ***textBlobs, uint32_t *textBlobsCount);

/**
 * @brief 获取文本对象的边界范围。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>textBlob、rect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param textBlob 指向文本对象OH_Drawing_TextBlob的指针。
 * @param rect 指向矩形对象OH_Drawing_Rect的指针，开发者可调用OH_Drawing_Rect接口创建。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextBlobGetBounds(OH_Drawing_TextBlob* textBlob, OH_Drawing_Rect* rect);

/**
 * @brief 获取文本的标识符，该标识符是唯一的非零值。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>textBlob为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param textBlob 指向文本对象OH_Drawing_TextBlob的指针。
 * @return 返回文本对象的标识符。
 * @since 12
 * @version 1.0
 */
uint32_t OH_Drawing_TextBlobUniqueID(const OH_Drawing_TextBlob* textBlob);

/**
 * @brief 结构体用于描述一块内存，该内存用于存储文字和位置信息。
 *
 * @since 11
 * @version 1.0
 */
typedef struct {
    /**
     * 存储字形索引。
     */
    uint16_t* glyphs;
    /**
     * 存储文字的位置。单位为物理像素px。
     */
    float* pos;
    /**
     * 存储文字UTF-8编码。
     */
    char* utf8text;
    /**
     * 存储文字簇UTF-8编码（簇指的是集合）。
     */
    uint32_t* clusters;
} OH_Drawing_RunBuffer;

/**
 * @brief 申请一块内存，用于存储文字和位置信息。返回的指针无需调用者管理，当调用{@link OH_Drawing_TextBlobBuilderMake}后禁止使用。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>textBlobBuilder、font任意一个为NULL或者count小于等于0时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param textBlobBuilder 指向文本构造器对象的指针。
 * @param font 指向字体对象OH_Drawing_Font的指针。
 * @param count 文字的数量。
 * @param rect 文本的边界框，为NULL表示不设置边界框。
 * @return 返回一个指针，指针指向创建的文本位置信息。
 * @since 11
 * @version 1.0
 */
const OH_Drawing_RunBuffer* OH_Drawing_TextBlobBuilderAllocRunPos(OH_Drawing_TextBlobBuilder* textBlobBuilder,
    const OH_Drawing_Font* font, int32_t count, const OH_Drawing_Rect* rect);

/**
 * @brief 用于从文本构造器中创建文本对象。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>textBlobBuilder为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param textBlobBuilder 指向文本构造器对象的指针。
 * @return 函数返回一个指针，指针指向创建的文本对象OH_Drawing_TextBlob。
 * @since 11
 * @version 1.0
 */
OH_Drawing_TextBlob* OH_Drawing_TextBlobBuilderMake(OH_Drawing_TextBlobBuilder* textBlobBuilder);

/**
 * @brief 用于销毁文本对象并回收该对象占用的内存。
 *
 * @param textBlob 指向文本对象OH_Drawing_TextBlob的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_TextBlobDestroy(OH_Drawing_TextBlob* textBlob);

/**
 * @brief 用于销毁文本构造器对象并回收该对象占用的内存。
 *
 * @param textBlobBuilder 指向文本构造器对象的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_TextBlobBuilderDestroy(OH_Drawing_TextBlobBuilder* textBlobBuilder);

/**
 * @brief 销毁OH_Drawing_TextBlob对象数组并回收该数组占用的内存。
 * 本函数会销毁数组中的文本对象，并释放数组本身。count必须与创建数组时返回的数量完全一致，传入其他值将导致未定义行为。
 *
 * @param textBlobs [in] 指向OH_Drawing_TextBlob对象数组的指针。
 * @param count [in] 数组的大小。
 * @return 返回{@link OH_DRAWING_SUCCESS} 表示执行成功。
 * 返回{@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} 表示textBlobs为空或者count为0。
 * @since 26.0.1
 */
OH_Drawing_ErrorCode OH_Drawing_TextBlobsArrayDestroy(OH_Drawing_TextBlob** textBlobs, uint32_t count);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
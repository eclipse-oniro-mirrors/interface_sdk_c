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

#ifdef __cplusplus
}
#endif
/** @} */
#endif
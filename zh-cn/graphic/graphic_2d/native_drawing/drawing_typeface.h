/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
 * @file drawing_typeface.h
 *
 * @brief 文件中定义了与字形相关的功能函数，支持创建默认字形、从文件或内存流创建指定字形、
 * 通过字型参数自定义字体的可变维度，以及查询字形的粗体、斜体属性等。
 * <br>不同的平台有自己的默认字形，也可以从ttf文件解析出三方指定字形，如宋体、黑体字形等。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_TYPEFACE_H
#define C_INCLUDE_DRAWING_TYPEFACE_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于创建一个默认的字形对象。
 *
 * @return 函数返回一个指针，指针指向创建的字形对象。
 * @since 11
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_TypefaceCreateDefault(void);

/**
 * @brief 通过文件创建一个字形对象。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向字体文件路径的指针。支持绝对路径，文件格式支持ttf、otf、ttc等字体文件。
 * @param index 文件索引，取值为非负整数，表示字体文件中的字体索引。对于单字体文件取值为0，
 * 对于字体集合文件取值范围为[0, 字体数量-1]。传入无效索引时创建字形对象失败，返回空指针。
 * @return 函数返回一个指针，指针指向创建的字形对象OH_Drawing_Typeface。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_TypefaceCreateFromFile(const char* path, int index);

/**
 * @brief 从指定文件路径创建带有字型参数的字体对象。
 * <br>如果字体对象不支持字型参数中描述的可变维度，此函数将会创建默认字型参数的字体对象。
 * <br>在这种情况下，此函数将提供与{@link OH_Drawing_TypefaceCreateFromFile}相同的功能。
 *
 * @param path 指向字体对象所在文件路径的指针。
 * @param fontArguments 指向字型参数对象OH_Drawing_FontArguments的指针。
 * @return 函数返回一个指针，指针指向创建的字体对象OH_Drawing_Typeface。
 *     <br>如果返回的对象指针为空，则表示字体对象创建失败。失败的原因可能为：没有可用的内存、
 * 传入的文件路径对象指针或字型参数为空、传入的路径无效。
 * @since 13
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_TypefaceCreateFromFileWithArguments(const char* path,
    const OH_Drawing_FontArguments* fontArguments);

/**
 * @brief 通过已存在的字体对象创建带有字型参数的字体对象。
 *
 * @param current 指向字体对象OH_Drawing_Typeface的指针。
 * @param fontArguments 指向字型参数对象OH_Drawing_FontArguments的指针。
 * @return 函数返回一个指针，指针指向创建的字体对象OH_Drawing_Typeface。
 *     <br>如果返回的对象指针为空，则表示字体对象创建失败。失败的原因可能为：没有可用的内存、
 * 传入的字体对象指针或字型参数为空、传入的字体对象不支持字型参数对象中描述的可变维度。
 * @since 13
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_TypefaceCreateFromCurrent(const OH_Drawing_Typeface* current,
    const OH_Drawing_FontArguments* fontArguments);

/**
 * @brief 通过内存流创建一个字形对象。如果内存流是无效的字体文件，返回空指针。内存流传入后，所有权转移，开发者不能再释放它。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>memoryStream为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param memoryStream 指向内存流对象OH_Drawing_MemoryStream的指针。
 * @param index 内存流索引。
 * @return 函数返回一个指针，指针指向创建的字形对象。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Typeface* OH_Drawing_TypefaceCreateFromStream(OH_Drawing_MemoryStream* memoryStream, int32_t index);

/**
 * @brief 用于销毁字形对象并回收该对象占用的内存。
 *
 * @param typeface 指向字形对象的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_TypefaceDestroy(OH_Drawing_Typeface* typeface);

/**
 * @brief 用于创建一个字型参数对象。字型参数用于创建带有自定义属性的字体对象。
 *
 * @return 函数返回一个指针，指针指向创建的字型参数对象。
 * @since 13
 * @version 1.0
 */
OH_Drawing_FontArguments* OH_Drawing_FontArgumentsCreate(void);

/**
 * @brief 给字型参数对象添加可变维度。
 *
 * @param fontArguments 指向字型参数对象OH_Drawing_FontArguments的指针。
 * @param axis 字型参数对象可变维度的标签，必须为4个ASCII字符。具体可支持的标签取决于加载的字体文件，如'wght'即为字重标签。
 * @param value 可变维度标签对应的取值，取值范围取决于轴标签和加载的字体文件中该可变维度标签定义的最小值与最大值。
 * @return 函数返回执行错误码。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数fontArguments或axis任意一个为NULL或者axis的长度不为4。
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontArgumentsAddVariation(OH_Drawing_FontArguments* fontArguments,
    const char* axis, float value);

/**
 * @brief 用于销毁一个字型参数对象。
 *
 * @param fontArguments 指向字型参数对象OH_Drawing_FontArguments的指针。
 * @return 函数返回执行错误码。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数fontArguments为NULL。
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_FontArgumentsDestroy(OH_Drawing_FontArguments* fontArguments);

/**
 * @brief 检查字形是否为粗体。
 *
 * @param typeface 指向字形对象OH_Drawing_Typeface的指针。
 * @param isBold 表示字形是否为粗体。作为出参使用。true表示该字形是粗体，false表示该字形不是粗体。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示typeface或isBold是空指针。
 * @since 23
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_TypefaceIsBold(const OH_Drawing_Typeface* typeface, bool* isBold);

/**
 * @brief 检查字形是否为斜体。
 *
 * @param typeface 指向字形对象OH_Drawing_Typeface的指针。
 * @param isItalic 表示字形是否为斜体。作为出参使用。true表示该字形是斜体，false表示该字形不是斜体。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示typeface或isItalic是空指针。
 * @since 23
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_TypefaceIsItalic(const OH_Drawing_Typeface* typeface, bool* isItalic);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
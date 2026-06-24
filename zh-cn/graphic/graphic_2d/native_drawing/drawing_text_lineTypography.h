
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.. All rights reserved.
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
 * @file drawing_text_lineTypography.h
 *
 * @brief This file declares the functions related to line typography, including functions to determine the number of
 * characters that can be formatted from a given position within the text.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 18
 * @version 1.0
 */

/**
 * @addtogroup Drawing
 * @{
 *
 * @brief Provides the 2D drawing capability.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 *
 * @since 18
 * @version 1.0
 */
#ifndef DRAWING_TEXT_LINETYPOGRAPHY_H
#define DRAWING_TEXT_LINETYPOGRAPHY_H
#include "drawing_text_declaration.h"
#include "drawing_types.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建一个排版行对象{@link OH_Drawing_LineTypography}的指针，排版行对象保存着文本内容以及样式的载体，可以用于计算单行排版信息。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param handler 指向{@link OH_Drawing_TypographyCreate}对象的指针，由{@link OH_Drawing_CreateTypographyHandler}获取。
 * @return 返回一个指向排版行对象{@link OH_Drawing_LineTypography}的指针。
 * @since 18
 */
OH_Drawing_LineTypography* OH_Drawing_CreateLineTypography(OH_Drawing_TypographyCreate* handler);

/**
 * @brief 释放排版行对象{@link OH_Drawing_LineTypography}占用的内存。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lineTypography 指向排版行对象{@link OH_Drawing_LineTypography}的指针，由{@link OH_Drawing_CreateLineTypography}获取。
 * @since 18
 */
void OH_Drawing_DestroyLineTypography(OH_Drawing_LineTypography* lineTypography);

/**
 * @brief 计算在限定排版宽度的情况下，从指定位置处开始可以排版的字符个数。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lineTypography 指向排版行对象{@link OH_Drawing_LineTypography}的指针，由{@link OH_Drawing_CreateLineTypography}获取。
 * @param startIndex 开始计算排版的起始位置（包括起始位置）。取值范围需要为[0,文本字符总数）的整数。
 * @param width 换行宽度，大于0的浮点数，单位为物理像素px。
 * @return 返回在限定排版宽度的情况下，从指定位置处开始可以排版的字符总数，取值为整数。
 * @since 18
 */
size_t OH_Drawing_LineTypographyGetLineBreak(OH_Drawing_LineTypography* lineTypography,
                                             size_t startIndex, double width);

/**
 * @brief 根据指定区间文本内容创建一个指向文本行对象{@link OH_Drawing_TextLine}的指针。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param lineTypography 指向排版行对象{@link OH_Drawing_LineTypography}的指针，由{@link OH_Drawing_CreateLineTypography}获取。
 * @param startIndex 表示计算排版的起始位置，整数，取值范围为[0, 文本字符总数)。
 * @param count 表示从指定排版起始位置开始进行排版的字符个数，取值为[0,文本字符总数)的整数，startIndex和count之和不能大于文本字符总数。
 *     可以先使用{@link OH_Drawing_LineTypographyGetLineBreak}获得合理的可用于进行排版的字符总数。如果该值设置为0，则返回nullptr。
 * @return 返回一个指向文本行对象{@link OH_Drawing_TextLine}的指针。
 * @since 18
 */
OH_Drawing_TextLine* OH_Drawing_LineTypographyCreateLine(OH_Drawing_LineTypography* lineTypography,
                                                         size_t startIndex, size_t count);
#ifdef __cplusplus
}
#endif

/** @} */
#endif
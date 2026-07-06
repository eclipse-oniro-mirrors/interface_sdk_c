
/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
 * @file drawing_text_declaration.h
 *
 * @brief Provides declarations of data structures related to 2D text drawing.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
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
 * @since 8
 * @version 1.0
 */
#ifndef C_INCLUDE_DRAWING_TEXT_DECLARATION_H
#define C_INCLUDE_DRAWING_TEXT_DECLARATION_H
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于加载字体。
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_FontCollection OH_Drawing_FontCollection;

/**
 * @brief 用于管理排版的布局和显示等。
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_Typography OH_Drawing_Typography;

/**
 * @brief 用于从一段文字中提取单行数据进行排版。
 *
 * @since 18
 * @version 1.0
 */
typedef struct OH_Drawing_LineTypography OH_Drawing_LineTypography;

/**
 * @brief 用于管理字体颜色、装饰等。
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_TextStyle OH_Drawing_TextStyle;

/**
 * @brief 用于管理排版风格，如文字方向等。
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_TypographyStyle OH_Drawing_TypographyStyle;

/**
 * @brief 用于创建{@link OH_Drawing_Typography}。
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_TypographyCreate OH_Drawing_TypographyCreate;

/**
 * @brief 用于接收文本框的矩形大小、方向和数量大小。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_TextBox OH_Drawing_TextBox;

/**
 * @brief 用于接收字体的位置和亲和性。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_PositionAndAffinity OH_Drawing_PositionAndAffinity;

/**
 * @brief 用于接收字体的起始位置和结束位置。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Range OH_Drawing_Range;

/**
 * @brief 用来解析系统字体文件。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontParser OH_Drawing_FontParser;

/**
 * @brief 用于管理文本阴影。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_TextShadow OH_Drawing_TextShadow;

/**
 * @brief 用于管理文本制表符。
 *
 * @since 18
 * @version 1.0
 */
typedef struct OH_Drawing_TextTab OH_Drawing_TextTab;

/**
 * @brief 用于管理文本行。
 *
 * @since 18
 * @version 1.0
 */
typedef struct OH_Drawing_TextLine OH_Drawing_TextLine;

/**
 * @brief 用于管理文本渲染单元。
 *
 * @since 18
 * @version 1.0
 */
typedef struct OH_Drawing_Run OH_Drawing_Run;

/**
 * @brief 用于描述字体的详细信息，即字体描述符。
 *
 * @since 22
 */
typedef struct OH_Drawing_FontFullDescriptor OH_Drawing_FontFullDescriptor;

/**
 * @brief 用于描述字体可变轴。
 *
 * @since 24
 */
typedef struct OH_Drawing_FontVariationAxis OH_Drawing_FontVariationAxis;

/**
 * @brief 用于描述字体可变实例，存放预设的可变字体样式信息。
 *
 * @since 24
 */
typedef struct OH_Drawing_FontVariationInstance OH_Drawing_FontVariationInstance;
#ifdef __cplusplus
}
#endif

/** @} */
#endif
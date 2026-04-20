/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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
 * @brief Provides functions such as 2D graphics rendering, text drawing, and image display.
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file drawing_types.h
 *
 * @brief This file declares the data types of the canvas, brush, pen, bitmap, and path used to draw 2D graphics.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_TYPES_H
#define C_INCLUDE_DRAWING_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义为一块矩形的画布，可以结合画笔和画刷在上面绘制各种形状、图片和文字。
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_Canvas OH_Drawing_Canvas;

/**
 * @brief 定义为画笔，画笔用于描述绘制图形轮廓的样式和颜色。
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_Pen OH_Drawing_Pen;

/**
 * @brief 定义一个区域，用于表示画布上的封闭区域，实现更精确的图形控制。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_Region OH_Drawing_Region;

/**
 * @brief 定义为画刷，画刷用于描述填充图形的样式和颜色。
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_Brush OH_Drawing_Brush;

/**
 * @brief 定义为路径，路径用于自定义各种形状。
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_Path OH_Drawing_Path;

/**
 * @brief 定义为路径操作迭代器，可通过遍历迭代器读取path的操作指令。
 *
 * @since 23
 * @version 1.0
 */
typedef struct OH_Drawing_PathIterator OH_Drawing_PathIterator;

/**
 * @brief 定义为矩形网格，用于将图片按照矩形网格进行划分。
 *
 * @since 23
 */
typedef struct OH_Drawing_Lattice OH_Drawing_Lattice;

/**
 * @brief 定义为位图，位图是一块内存，内存中包含了描述一张图片的像素数据。
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_Bitmap OH_Drawing_Bitmap;

/**
 * @brief 定义一个点，用于描述坐标点。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Point OH_Drawing_Point;

/**
 * @brief 定义像素图，用于包装图像框架支持的真实像素图。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_PixelMap OH_Drawing_PixelMap;

/**
 * @brief 定义色彩空间，用于解释颜色信息。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_ColorSpace OH_Drawing_ColorSpace;

/**
 * @brief OH_Drawing_Point2D: 定义一个二维的坐标点。
 * OH_Drawing_Corner_Radii: 定义一个圆角半径，该圆角半径由x轴方向和y轴方向上的半径组成。
 *
 * @since 12
 * @version 1.0
 */
typedef struct {
    float x;
    float y;
} OH_Drawing_Point2D;

/**
 * @brief Defines corner radii, which is on x-axis and y-axis.
 *
 * @since 12
 * @version 1.0
 */
typedef OH_Drawing_Point2D OH_Drawing_Corner_Radii;

/**
 * @brief 定义一个三维的坐标点。
 *
 * @since 12
 * @version 1.0
 */
typedef struct {
    float x;
    float y;
    float z;
} OH_Drawing_Point3D;

/**
 * @brief 定义一个路径效果，用于影响描边路径。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_PathEffect OH_Drawing_PathEffect;

/**
 * @brief 用于描述矩形。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Rect OH_Drawing_Rect;

/**
 * @brief 用于描述圆角矩形。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_RoundRect OH_Drawing_RoundRect;

/**
 * @brief 定义一个矩阵，用于描述坐标变换。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Matrix OH_Drawing_Matrix;

/**
 * @brief 定义一个着色器，用于描述绘制内容的源颜色。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_ShaderEffect OH_Drawing_ShaderEffect;

/**
 * @brief 定义一个阴影层，用于描述绘制内容的阴影层。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_ShadowLayer OH_Drawing_ShadowLayer;

/**
 * @brief 定义一个滤波器，用于存储颜色滤波器，蒙版滤波器和图像滤波器。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Filter OH_Drawing_Filter;

/**
 * @brief 定义蒙版滤波器。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_MaskFilter OH_Drawing_MaskFilter;

/**
 * @brief 定义颜色滤波器，传入一个颜色并返回一个新的颜色。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_ColorFilter OH_Drawing_ColorFilter;

/**
 * @brief 用于描述字体。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Font OH_Drawing_Font;

/**
 * @brief 用于描述字体特征容器。字体特征是字体内置的排版规则，控制字形显示。例如：连字、替代字形、上下标等。
 *
 * @since 20
 * @version 1.0
 */
typedef struct OH_Drawing_FontFeatures OH_Drawing_FontFeatures;

/**
 * @brief 用于描述内存流。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_MemoryStream OH_Drawing_MemoryStream;

/**
 * @brief 用于描述字型参数。
 *
 * @since 13
 * @version 1.0
 */
typedef struct OH_Drawing_FontArguments OH_Drawing_FontArguments;

/**
 * @brief 用于描述字形。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Typeface OH_Drawing_Typeface;

/**
 * @brief 定义一个文本对象，表示将多个文本组合到一个不可变的容器中。每个文本行由字形和位置组成。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_TextBlob OH_Drawing_TextBlob;

/**
 * @brief 定义一个用于描述绘制二维像素数组的图片。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_Image OH_Drawing_Image;

/**
 * @brief 定义图像滤波器, 用于对构成图像像素的所有颜色位进行操作。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_ImageFilter OH_Drawing_ImageFilter;

/**
 * @brief 定义一个采样选项，用于描述图片、位图等图像的采样方法。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_SamplingOptions OH_Drawing_SamplingOptions;

/**
 * @brief 定义文本构建器，用于构建文本。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_TextBlobBuilder OH_Drawing_TextBlobBuilder;

/**
 * @brief 定义图形处理器上下文，用于描述图形处理器后端上下文。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_GpuContext OH_Drawing_GpuContext;

/**
 * @brief 定义surface，用于管理画布绘制的内容。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_Surface OH_Drawing_Surface;

/**
 * @brief 用于描述位图像素的存储格式。
 *
 * @since 8
 * @version 1.0
 */
typedef enum {
    /**
     * 未知格式。
     *
     * @since 8
     */
    COLOR_FORMAT_UNKNOWN,
    /**
     * 每个像素用一个8位的量表示，8个比特位表示透明度。
     *
     * @since 8
     */
    COLOR_FORMAT_ALPHA_8,
    /**
     * 每个像素用一个16位的量表示，高位到低位依次是5个比特位表示红，6个比特位表示绿，5个比特位表示蓝。
     *
     * @since 8
     */
    COLOR_FORMAT_RGB_565,
    /**
     * 每个像素用一个16位的量表示，高位到低位依次是4个比特位表示透明度，4个比特位表示红，4个比特位表示绿，4个比特位表示蓝。
     *
     * @since 8
     */
    COLOR_FORMAT_ARGB_4444,
    /**
     * 每个像素用一个32位的量表示，高位到低位依次是8个比特位表示透明度，8个比特位表示红，8个比特位表示绿，8个比特位表示蓝。
     *
     * @since 8
     */
    COLOR_FORMAT_RGBA_8888,
    /**
     * 每个像素用一个32位的量表示，高位到低位依次是8个比特位表示蓝，8个比特位表示绿，8个比特位表示红，8个比特位表示透明度。
     *
     * @since 8
     */
    COLOR_FORMAT_BGRA_8888
} OH_Drawing_ColorFormat;

/**
 * @brief 用于描述位图像素的透明度分量。
 *
 * @since 8
 * @version 1.0
 */
typedef enum {
    /**
     * 未知格式。
     *
     * @since 8
     */
    ALPHA_FORMAT_UNKNOWN,
    /**
     * 位图无透明度。
     *
     * @since 8
     */
    ALPHA_FORMAT_OPAQUE,
    /**
     * 每个像素的颜色组件由透明度分量预先乘以。
     *
     * @since 8
     */
    ALPHA_FORMAT_PREMUL,
    /**
     * 每个像素的颜色组件未由透明度分量预先乘以。
     *
     * @since 8
     */
    ALPHA_FORMAT_UNPREMUL
} OH_Drawing_AlphaFormat;

/**
 * @brief 混合模式枚举。混合模式的操作会为两种颜色（源色、目标色）生成一种新的颜色。
 * 这些操作在红、绿、蓝3个颜色通道上是相同的（透明度有另外的处理规则）。
 * 对于这些，我们使用透明度通道作为示例，而不是单独命名每个通道。为简洁起见，我们使用以下缩写：
 * s  : source，源的缩写。
 * d  : destination，目标的缩写。
 * sa : source alpha，源透明度的缩写。
 * da : destination alpha，目标透明度的缩写。
 * 计算结果用如下缩写表示：
 * r  : 如果4个通道的计算方式相同，用r表示。
 * ra : 如果只操作透明度通道，用ra表示。
 * rc : 如果操作3个颜色通道，用rc表示。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 清除模式，r = 0。
     *
     * @since 11
     */
    BLEND_MODE_CLEAR,
    /**
     * r = s（result的4个通道，都等于source的4个通道，即结果等于源。）
     *
     * @since 11
     */
    BLEND_MODE_SRC,
    /**
     * r = d（result的4个通道，都等于destination的4个通道，即结果等于目标。）
     *
     * @since 11
     */
    BLEND_MODE_DST,
    /**
     * r = s + (1 - sa) * d.
     *
     * @since 11
     */
    BLEND_MODE_SRC_OVER,
    /**
     * r = d + (1 - da) * s.
     *
     * @since 11
     */
    BLEND_MODE_DST_OVER,
    /**
     * r = s * da.
     *
     * @since 11
     */
    BLEND_MODE_SRC_IN,
    /**
     * r = d * sa.
     *
     * @since 11
     */
    BLEND_MODE_DST_IN,
    /**
     * r = s * (1 - da).
     *
     * @since 11
     */
    BLEND_MODE_SRC_OUT,
    /**
     * r = d * (1 - sa).
     *
     * @since 11
     */
    BLEND_MODE_DST_OUT,
    /**
     * r = s * da + d * (1 - sa).
     *
     * @since 11
     */
    BLEND_MODE_SRC_ATOP,
    /**
     * r = d * sa + s * (1 - da).
     *
     * @since 11
     */
    BLEND_MODE_DST_ATOP,
    /**
     * r = s * (1 - da) + d * (1 - sa).
     *
     * @since 11
     */
    BLEND_MODE_XOR,
    /**
     * r = min(s + d, 1).
     *
     * @since 11
     */
    BLEND_MODE_PLUS,
    /**
     * r = s * d.
     *
     * @since 11
     */
    BLEND_MODE_MODULATE,
    /**
     * 滤色模式，r = s + d - s * d。
     *
     * @since 11
     */
    BLEND_MODE_SCREEN,
    /**
     * 叠加模式。
     *
     * @since 11
     */
    BLEND_MODE_OVERLAY,
    /**
     * 变暗模式，rc = s + d - max(s * da, d * sa), ra = s + (1 - sa) * d。
     *
     * @since 11
     */
    BLEND_MODE_DARKEN,
    /**
     * 变亮模式，rc = s + d - min(s * da, d * sa), ra = s + (1 - sa) * d。
     *
     * @since 11
     */
    BLEND_MODE_LIGHTEN,
    /**
     * 颜色减淡模式。
     *
     * @since 11
     */
    BLEND_MODE_COLOR_DODGE,
    /**
     * 颜色加深模式。
     *
     * @since 11
     */
    BLEND_MODE_COLOR_BURN,
    /**
     * 强光模式。
     *
     * @since 11
     */
    BLEND_MODE_HARD_LIGHT,
    /**
     * 柔光模式。
     *
     * @since 11
     */
    BLEND_MODE_SOFT_LIGHT,
    /**
     * 差值模式，rc = s + d - 2 * (min(s * da, d * sa)), ra = s + (1 - sa) * d。
     *
     * @since 11
     */
    BLEND_MODE_DIFFERENCE,
    /**
     * 排除模式，rc = s + d - two(s * d), ra = s + (1 - sa) * d。
     *
     * @since 11
     */
    BLEND_MODE_EXCLUSION,
    /**
     * 正片叠底，r = s * (1 - da) + d * (1 - sa) + s * d。
     *
     * @since 11
     */
    BLEND_MODE_MULTIPLY,
    /**
     * 色相模式。
     *
     * @since 11
     */
    BLEND_MODE_HUE,
    /**
     * 饱和度模式。
     *
     * @since 11
     */
    BLEND_MODE_SATURATION,
    /**
     * 颜色模式。
     *
     * @since 11
     */
    BLEND_MODE_COLOR,
    /**
     * 亮度模式。
     *
     * @since 11
     */
    BLEND_MODE_LUMINOSITY,
} OH_Drawing_BlendMode;

/**
 * @brief 文本编码类型枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 单字节，表示UTF-8或ASCII。
     *
     * @since 12
     */
    TEXT_ENCODING_UTF8,
    /**
     * 双字节，表示大部分Unicode。
     *
     * @since 12
     */
    TEXT_ENCODING_UTF16,
    /**
     * 四字节，表示所有Unicode。
     *
     * @since 12
     */
    TEXT_ENCODING_UTF32,
    /**
     * 双字节，表示字形索引。
     *
     * @since 12
     */
    TEXT_ENCODING_GLYPH_ID,
} OH_Drawing_TextEncoding;

/**
 * @brief 定义字体管理类, 用于字体管理。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontMgr OH_Drawing_FontMgr;

/**
 * @brief 定义字体样式集, 用于字体样式族匹配。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontStyleSet OH_Drawing_FontStyleSet;

/**
 * @brief 定义指令录制工具，用于生成录制指令。
 *
 * @since 13
 * @version 1.0
 */
typedef struct OH_Drawing_RecordCmdUtils OH_Drawing_RecordCmdUtils;

/**
 * @brief 定义录制指令类, 用于存储录制指令的集合。
 *
 * @since 13
 * @version 1.0
 */
typedef struct OH_Drawing_RecordCmd OH_Drawing_RecordCmd;

/**
 * @brief 定义数组对象, 用于存储多个同类型对象。
 *
 * @since 14
 * @version 1.0
 */
typedef struct OH_Drawing_Array OH_Drawing_Array;

/**
 * @brief This struct describes the style of a rectangle.
 *
 * @since 12
 * @version 1.0
 */
typedef struct {
    /**
     * Color of the rectangle.
     *
     * @since 12
     */
    uint32_t color;
    /**
     * Left top radius of the rectangle.
     *
     * @since 12
     */
    double leftTopRadius;
    /**
     * Right top radius of the rectangle.
     *
     * @since 12
     */
    double rightTopRadius;
    /**
     * Right bottom radius of the rectangle.
     *
     * @since 12
     */
    double rightBottomRadius;
    /**
     * Left bottom radius of the rectangle.
     *
     * @since 12
     */
    double leftBottomRadius;
} OH_Drawing_RectStyle_Info;
/**
 * @brief This struct describes the image information.
 *
 * @since 12
 * @version 1.0
 */
typedef struct {
    /**
     * Width, in pixels.
     *
     * @since 12
     */
    int32_t width;
    /**
     * Height, in pixels.
     *
     * @since 12
     */
    int32_t height;
    /**
     * Color type.
     *
     * @since 12
     */
    OH_Drawing_ColorFormat colorType;
    /**
     * Alpha type.
     *
     * @since 12
     */
    OH_Drawing_AlphaFormat alphaType;
} OH_Drawing_Image_Info;

/**
 * @brief This struct describes a string of characters encoded in UTF-16.
 *
 * @since 14
 * @version 1.0
 */
typedef struct {
    /**
     * Pointer to a byte array that stores characters in the UTF-16 encoding format.
     *
     * @since 14
     */
    uint8_t* strData;
    /**
     * Actual length of the string that **strData** points to, in bytes.
     *
     * @since 14
     */
    uint32_t strLen;
} OH_Drawing_String;
#ifdef __cplusplus
}
#endif
/** @} */
#endif
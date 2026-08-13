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
 * @brief Drawing模块提供包括2D图形渲染、文字绘制和图片显示等功能函数。
 * <br>本模块采用屏幕物理像素单位px。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file drawing_types.h
 *
 * @brief 文件中定义了用于绘制2D图形的数据类型，包括画布、画笔、画刷、位图和路径。这些数据类型提供了2D图形绘制能力，
 * 适用于需要在画布上绑定画笔和画刷绘制各种形状、图片和文字的场景，可以灵活定义路径和位图，
 * 帮助开发者高效实现自定义图形绘制、图像处理等功能，满足复杂的2D图形绘制需求。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
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
 * @brief OH_Drawing_Point2D: 定义一个二维的坐标点。<br/>OH_Drawing_Corner_Radii: 定义一个圆角半径，
 * 该圆角半径由x轴方向和y轴方向上的半径组成。
 *
 * @since 12
 * @version 1.0
 */
typedef struct {
    /**
     * x轴坐标。
     */
    float x;
    /**
     * y轴坐标。
     */
    float y;
} OH_Drawing_Point2D;

/**
 * @brief 定义一个圆角半径，该圆角半径由x轴方向和y轴方向上的半径组成。
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
    /**
     * @brief x轴坐标。
     *
     * @since 12
     */
    float x;
    /**
     * @brief y轴坐标。
     *
     * @since 12
     */
    float y;
    /**
     * @brief z轴坐标。
     *
     * @since 12
     */
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
 * @brief 定义一个阴影层，用于描述绘制内容的阴影效果。
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
 * @brief 定义图像滤波器，用于对构成图像像素的所有颜色位进行操作。
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
     * @brief 未知格式。
     *
     * @since 8
     */
    COLOR_FORMAT_UNKNOWN,
    /**
     * @brief 每个像素用一个8位的量表示，8个比特位表示透明度。
     *
     * @since 8
     */
    COLOR_FORMAT_ALPHA_8,
    /**
     * @brief 每个像素用一个16位的量表示，高位到低位依次是5个比特位表示红，6个比特位表示绿，5个比特位表示蓝。
     *
     * @since 8
     */
    COLOR_FORMAT_RGB_565,
    /**
     * @brief 每个像素用一个16位的量表示，高位到低位依次是4个比特位表示透明度，4个比特位表示红，4个比特位表示绿，4个比特位表示蓝。
     *
     * @since 8
     */
    COLOR_FORMAT_ARGB_4444,
    /**
     * @brief 每个像素用一个32位的量表示，高位到低位依次是8个比特位表示透明度，8个比特位表示红，8个比特位表示绿，8个比特位表示蓝。
     *
     * @since 8
     */
    COLOR_FORMAT_RGBA_8888,
    /**
     * @brief 每个像素用一个32位的量表示，高位到低位依次是8个比特位表示蓝，8个比特位表示绿，8个比特位表示红，8个比特位表示透明度。
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
     * @brief 未知格式。
     *
     * @since 8
     */
    ALPHA_FORMAT_UNKNOWN,
    /**
     * @brief 位图无透明度。
     *
     * @since 8
     */
    ALPHA_FORMAT_OPAQUE,
    /**
     * @brief 每个像素的颜色组件已预先乘以透明度分量。
     *
     * @since 8
     */
    ALPHA_FORMAT_PREMUL,
    /**
     * @brief 每个像素的颜色组件未预先乘以透明度分量。
     *
     * @since 8
     */
    ALPHA_FORMAT_UNPREMUL
} OH_Drawing_AlphaFormat;

/**
 * @brief 混合模式枚举。混合模式的操作会为两种颜色（源色、目标色）生成一种新的颜色。
 * <br>这些操作在红、绿、蓝3个颜色通道上是相同的（透明度有另外的处理规则）。
 * <br>对于这些，我们使用透明度通道作为示例，而不是单独命名每个通道。为简洁起见，我们使用以下缩写：
 * <br>s  : source，源的缩写。
 * <br>d  : destination，目标的缩写。
 * <br>sa : source alpha，源透明度的缩写。
 * <br>da : destination alpha，目标透明度的缩写。
 * <br>计算结果用如下缩写表示：
 * <br>r  : 如果4个通道的计算方式相同，用r表示。
 * <br>ra : 如果只操作透明度通道，用ra表示。
 * <br>rc : 如果操作3个颜色通道，用rc表示。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * @brief 清除模式，r = 0。
     *
     * @since 11
     */
    BLEND_MODE_CLEAR,
    /**
     * @brief r = s（result的4个通道，都等于source的4个通道，即结果等于源。）
     *
     * @since 11
     */
    BLEND_MODE_SRC,
    /**
     * @brief r = d（result的4个通道，都等于destination的4个通道，即结果等于目标。）
     *
     * @since 11
     */
    BLEND_MODE_DST,
    /**
     * @brief r = s + (1 - sa) * d。
     *
     * @since 11
     */
    BLEND_MODE_SRC_OVER,
    /**
     * @brief r = d + (1 - da) * s。
     *
     * @since 11
     */
    BLEND_MODE_DST_OVER,
    /**
     * @brief r = s * da。
     *
     * @since 11
     */
    BLEND_MODE_SRC_IN,
    /**
     * @brief r = d * sa。
     *
     * @since 11
     */
    BLEND_MODE_DST_IN,
    /**
     * @brief r = s * (1 - da)。
     *
     * @since 11
     */
    BLEND_MODE_SRC_OUT,
    /**
     * @brief r = d * (1 - sa)。
     *
     * @since 11
     */
    BLEND_MODE_DST_OUT,
    /**
     * @brief r = s * da + d * (1 - sa)。
     *
     * @since 11
     */
    BLEND_MODE_SRC_ATOP,
    /**
     * @brief r = d * sa + s * (1 - da)。
     *
     * @since 11
     */
    BLEND_MODE_DST_ATOP,
    /**
     * @brief r = s * (1 - da) + d * (1 - sa)。
     *
     * @since 11
     */
    BLEND_MODE_XOR,
    /**
     * @brief r = min(s + d, 1)。
     *
     * @since 11
     */
    BLEND_MODE_PLUS,
    /**
     * @brief r = s * d。
     *
     * @since 11
     */
    BLEND_MODE_MODULATE,
    /**
     * @brief 滤色模式，r = s + d - s * d。
     *
     * @since 11
     */
    BLEND_MODE_SCREEN,
    /**
     * @brief 叠加模式，根据目标像素的亮度，选择性地应用MULTIPLY或SCREEN模式，增强对比度。
     *
     * @since 11
     */
    BLEND_MODE_OVERLAY,
    /**
     * @brief 变暗模式，rc = s + d - max(s * da, d * sa), ra = s + (1 - sa) * d。
     *
     * @since 11
     */
    BLEND_MODE_DARKEN,
    /**
     * @brief 变亮模式，rc = s + d - min(s * da, d * sa), ra = s + (1 - sa) * d。
     *
     * @since 11
     */
    BLEND_MODE_LIGHTEN,
    /**
     * @brief 颜色减淡模式，通过减小对比度使目标像素变亮以反映源像素。
     *
     * @since 11
     */
    BLEND_MODE_COLOR_DODGE,
    /**
     * @brief 颜色加深模式，通过增加对比度使目标像素变暗以反映源像素。
     *
     * @since 11
     */
    BLEND_MODE_COLOR_BURN,
    /**
     * @brief 强光模式，根据源像素的亮度，选择性地应用MULTIPLY或SCREEN模式。
     *
     * @since 11
     */
    BLEND_MODE_HARD_LIGHT,
    /**
     * @brief 柔光模式，根据源像素的亮度，柔和地变亮或变暗目标像素。
     *
     * @since 11
     */
    BLEND_MODE_SOFT_LIGHT,
    /**
     * @brief 差值模式，rc = s + d - 2 * (min(s * da, d * sa)), ra = s + (1 - sa) * d。
     *
     * @since 11
     */
    BLEND_MODE_DIFFERENCE,
    /**
     * @brief 排除模式，rc = s + d - two(s * d), ra = s + (1 - sa) * d。
     *
     * @since 11
     */
    BLEND_MODE_EXCLUSION,
    /**
     * @brief 正片叠底，r = s * (1 - da) + d * (1 - sa) + s * d。
     *
     * @since 11
     */
    BLEND_MODE_MULTIPLY,
    /**
     * @brief 色相模式，使用源像素的色相，目标像素的饱和度和亮度。
     *
     * @since 11
     */
    BLEND_MODE_HUE,
    /**
     * @brief 饱和度模式，使用源像素的饱和度，目标像素的色相和亮度。
     *
     * @since 11
     */
    BLEND_MODE_SATURATION,
    /**
     * @brief 颜色模式，使用源像素的色相和饱和度，目标像素的亮度。
     *
     * @since 11
     */
    BLEND_MODE_COLOR,
    /**
     * @brief 亮度模式，使用源像素的亮度，目标像素的色相和饱和度。
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
     * @brief 单字节，表示UTF-8或ASCII。
     *
     * @since 12
     */
    TEXT_ENCODING_UTF8,
    /**
     * @brief 双字节，表示大部分Unicode。
     *
     * @since 12
     */
    TEXT_ENCODING_UTF16,
    /**
     * @brief 四字节，表示所有Unicode。
     *
     * @since 12
     */
    TEXT_ENCODING_UTF32,
    /**
     * @brief 双字节，表示字形索引。
     *
     * @since 12
     */
    TEXT_ENCODING_GLYPH_ID,
} OH_Drawing_TextEncoding;

/**
 * @brief 定义字体管理类，用于字体管理。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontMgr OH_Drawing_FontMgr;

/**
 * @brief 定义字体样式集，用于字体样式族匹配。
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
 * @brief 定义录制指令类，用于存储录制指令的集合。
 *
 * @since 13
 * @version 1.0
 */
typedef struct OH_Drawing_RecordCmd OH_Drawing_RecordCmd;

/**
 * @brief 定义数组对象，用于存储多个同类型对象。
 *
 * @since 14
 * @version 1.0
 */
typedef struct OH_Drawing_Array OH_Drawing_Array;

/**
 * @brief 定义矩形框样式结构体。
 *
 * @since 12
 * @version 1.0
 */
typedef struct {
    /**
     * @brief 矩形框的颜色。
     *
     * @since 12
     */
    uint32_t color;
    /**
     * @brief 矩形框的左上半径。
     *
     * @since 12
     */
    double leftTopRadius;
    /**
     * @brief 矩形框的右上半径。
     *
     * @since 12
     */
    double rightTopRadius;
    /**
     * @brief 矩形框的右下半径。
     *
     * @since 12
     */
    double rightBottomRadius;
    /**
     * @brief 矩形框的左下半径。
     *
     * @since 12
     */
    double leftBottomRadius;
} OH_Drawing_RectStyle_Info;
/**
 * @brief 定义图片信息结构体。
 *
 * @since 12
 * @version 1.0
 */
typedef struct {
    /**
     * @brief 宽度，单位为像素。
     *
     * @since 12
     */
    int32_t width;
    /**
     * @brief 高度，单位为像素。
     *
     * @since 12
     */
    int32_t height;
    /**
     * @brief 颜色类型{@link OH_Drawing_ColorFormat}。
     *
     * @since 12
     */
    OH_Drawing_ColorFormat colorType;
    /**
     * @brief 透明度类型{@link OH_Drawing_AlphaFormat}。
     *
     * @since 12
     */
    OH_Drawing_AlphaFormat alphaType;
} OH_Drawing_Image_Info;

/**
 * @brief 采用UTF-16编码的字符串信息结构体。
 *
 * @since 14
 * @version 1.0
 */
typedef struct {
    /**
     * @brief 指向包含UTF-16编码的字节数组的指针。
     *
     * @since 14
     */
    uint8_t* strData;
    /**
     * @brief `strData`指向的字符串的实际长度，单位为字节。
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
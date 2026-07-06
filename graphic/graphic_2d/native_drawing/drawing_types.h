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
 * @brief Defines a struct for a rectangular canvas, on which various shapes, images, and texts can be drawn by using
 * the brush and pen.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_Canvas OH_Drawing_Canvas;

/**
 * @brief Defines a struct for a pen, which is used to describe the style and color to outline a shape.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_Pen OH_Drawing_Pen;

/**
 * @brief Defines a struct for a region, which represents a closed area on the canvas for more accurate graphic control.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_Region OH_Drawing_Region;

/**
 * @brief Defines a struct for a brush, which is used to describe the style and color to fill in a shape.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_Brush OH_Drawing_Brush;

/**
 * @brief Defines a struct for a path, which is used to customize various shapes.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_Path OH_Drawing_Path;

/**
 * @brief This struct defines a path operation iterator that enables path operation instructions to be read via
 * iterator traversal.
 *
 * @since 23
 * @version 1.0
 */
typedef struct OH_Drawing_PathIterator OH_Drawing_PathIterator;

/**
 * @brief This struct defines a rectangle grid, which is used to divide an image by rectangle grid.
 *
 * @since 23
 */
typedef struct OH_Drawing_Lattice OH_Drawing_Lattice;

/**
 * @brief Defines a struct for a bitmap, which is a memory area that contains the pixel data of a shape.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_Drawing_Bitmap OH_Drawing_Bitmap;

/**
 * @brief Defines a struct for a coordinate point.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Point OH_Drawing_Point;

/**
 * @brief Defines a struct for a pixel map, which is used to wrap the real pixel map supported by the image framework.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_PixelMap OH_Drawing_PixelMap;

/**
 * @brief Defines a struct for a color space, which is used to describe the color information.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_ColorSpace OH_Drawing_ColorSpace;

/**
 * @brief **OH_Drawing_Point2D** defines a two-dimensional coordinate point.<br>**OH_Drawing_Corner_Radii** defines
 * rounded corner radii, consisting of an x-axis radius and a y-axis radius.
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
 * @brief This struct describes a three-dimensional coordinate point.
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
 * @brief Defines a struct for a path effect that affects the stroke.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_PathEffect OH_Drawing_PathEffect;

/**
 * @brief Defines a struct for a rectangle.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Rect OH_Drawing_Rect;

/**
 * @brief Defines a struct for a rounded rectangle.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_RoundRect OH_Drawing_RoundRect;

/**
 * @brief Defines a struct for a matrix, which is used to describe coordinate transformation.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Matrix OH_Drawing_Matrix;

/**
 * @brief Defines a struct for a shader effect, which is used to describe the source color of the drawn content.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_ShaderEffect OH_Drawing_ShaderEffect;

/**
 * @brief Defines a struct for a shadow, which is used to describe the shadow layer of the drawn content.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_ShadowLayer OH_Drawing_ShadowLayer;

/**
 * @brief Defines a struct for a filter, which consists of a color filter, mask filter, and image filter.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Filter OH_Drawing_Filter;

/**
 * @brief Defines a struct for a mask filter.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_MaskFilter OH_Drawing_MaskFilter;

/**
 * @brief Defines a struct for a color filter, which is used to convert a color into a new one.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_ColorFilter OH_Drawing_ColorFilter;

/**
 * @brief Defines a struct for a font.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Font OH_Drawing_Font;

/**
 * @brief Defines a struct for font features, which are typesetting rules within a font that determine how glyphs look,
 * such as ligatures, alternates, and superscripts/subscripts.
 *
 * @since 20
 * @version 1.0
 */
typedef struct OH_Drawing_FontFeatures OH_Drawing_FontFeatures;

/**
 * @brief Defines a struct for a memory stream.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_MemoryStream OH_Drawing_MemoryStream;

/**
 * @brief Defines a struct for font arguments.
 *
 * @since 13
 * @version 1.0
 */
typedef struct OH_Drawing_FontArguments OH_Drawing_FontArguments;

/**
 * @brief Defines a struct for a typeface.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_Typeface OH_Drawing_Typeface;

/**
 * @brief Defines a struct for a text blob, an immutable container that holds multiple texts. Each text blob consists
 * of glyphs and position.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_TextBlob OH_Drawing_TextBlob;

/**
 * @brief Defines a struct for an image that describes a two-dimensional pixel array.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_Image OH_Drawing_Image;

/**
 * @brief Defines a struct for an image filter, which is used to operate all color bits that make up image pixels.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_ImageFilter OH_Drawing_ImageFilter;

/**
 * @brief Defines a struct for sampling options, which describe the sampling methods for images and bitmaps.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_SamplingOptions OH_Drawing_SamplingOptions;

/**
 * @brief Defines a struct for a text blob builder, which is used to build a text blob.
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_Drawing_TextBlobBuilder OH_Drawing_TextBlobBuilder;

/**
 * @brief Defines a struct for the GPU context, which is used to describe the GPU backend context.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_GpuContext OH_Drawing_GpuContext;

/**
 * @brief Defines a struct for a surface, which is used to manage the content drawn on the canvas.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_Surface OH_Drawing_Surface;

/**
 * @brief Defines an enum for the storage formats of bitmap pixels.
 *
 * @since 8
 * @version 1.0
 */
typedef enum {
    /**
     * Unknown format.
     *
     * @since 8
     */
    COLOR_FORMAT_UNKNOWN,
    /**
     * Each pixel is represented by 8 bits, which together indicate alpha.
     *
     * @since 8
     */
    COLOR_FORMAT_ALPHA_8,
    /**
     * Each pixel is represented by 16 bits. From the most significant bit to the least significant bit, the first 5
     * bits indicate red, the subsequent 6 bits indicate green, and the last 5 bits indicate blue.
     *
     * @since 8
     */
    COLOR_FORMAT_RGB_565,
    /**
     * Each pixel is represented by 16 bits. From the most significant bit to the least significant bit, every 4 bits
     * indicate alpha, red, green, and blue, respectively.
     *
     * @since 8
     */
    COLOR_FORMAT_ARGB_4444,
    /**
     * Each pixel is represented by 32 bits. From the most significant bit to the least significant bit, every 8 bits
     * indicate alpha, red, green, and blue, respectively.
     *
     * @since 8
     */
    COLOR_FORMAT_RGBA_8888,
    /**
     * Each pixel is represented by 32 bits. From the most significant bit to the least significant bit, every 8 bits
     * indicate blue, green, red, and alpha, respectively.
     *
     * @since 8
     */
    COLOR_FORMAT_BGRA_8888
} OH_Drawing_ColorFormat;

/**
 * @brief Defines an enum for the alpha formats of bitmap pixels.
 *
 * @since 8
 * @version 1.0
 */
typedef enum {
    /**
     * Unknown format.
     *
     * @since 8
     */
    ALPHA_FORMAT_UNKNOWN,
    /**
     * The bitmap does not have the alpha component.
     *
     * @since 8
     */
    ALPHA_FORMAT_OPAQUE,
    /**
     * The color component of each pixel is premultiplied by the alpha component.
     *
     * @since 8
     */
    ALPHA_FORMAT_PREMUL,
    /**
     * The color component of each pixel is not premultiplied by the alpha component.
     *
     * @since 8
     */
    ALPHA_FORMAT_UNPREMUL
} OH_Drawing_AlphaFormat;

/**
 * @brief Defines an enum for blend modes. In blend mode, each operation generates a new color from two colors (source
 * color and destination color).
 * These operations are the same for the red, green, and blue color channels (the alpha channel follows a different
 * rule).
 * For simplicity, the following description uses the alpha channel as an example rather than naming each channel
 * individually. For brevity, the following abbreviations are used:
 * **s**: source.
 * **d**: destination.
 * **sa**: source alpha.
 * **da**: destination alpha.
 * The following abbreviations are used in the calculation result:
 * **r**: The calculation methods of the four channels are the same.
 * **ra**: used when only the alpha channel is manipulated.
 * **rc**: used when the other three color channels are manipulated.
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * Clear mode. r = 0.
     *
     * @since 11
     */
    BLEND_MODE_CLEAR,
    /**
     * r = s (The four channels of **result** are equal to the four channels of **source**, that is, the result is
     * equal to the source.)
     *
     * @since 11
     */
    BLEND_MODE_SRC,
    /**
     * r = d (The four channels of **result** are equal to the four channels of **destination**, that is, the result is
     * equal to the destination.)
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
     * Screen mode. r = s + d - s * d.
     *
     * @since 11
     */
    BLEND_MODE_SCREEN,
    /**
     * Overlay mode.
     *
     * @since 11
     */
    BLEND_MODE_OVERLAY,
    /**
     * Darken mode. rc = s + d - max(s * da, d * sa), ra = s + (1 - sa) * d.
     *
     * @since 11
     */
    BLEND_MODE_DARKEN,
    /**
     * Lighten mode. rc = rc = s + d - min(s * da, d * sa), ra = s + (1 - sa) * d.
     *
     * @since 11
     */
    BLEND_MODE_LIGHTEN,
    /**
     * Color dodge mode.
     *
     * @since 11
     */
    BLEND_MODE_COLOR_DODGE,
    /**
     * Color burn mode.
     *
     * @since 11
     */
    BLEND_MODE_COLOR_BURN,
    /**
     * Hard light mode.
     *
     * @since 11
     */
    BLEND_MODE_HARD_LIGHT,
    /**
     * Soft light mode.
     *
     * @since 11
     */
    BLEND_MODE_SOFT_LIGHT,
    /**
     * Difference mode. rc = s + d - 2 * (min(s * da, d * sa)), ra = s + (1 - sa) * d.
     *
     * @since 11
     */
    BLEND_MODE_DIFFERENCE,
    /**
     * Exclusion mode. rc = s + d - two(s * d), ra = s + (1 - sa) * d.
     *
     * @since 11
     */
    BLEND_MODE_EXCLUSION,
    /**
     * Multiply mode. r = s * (1 - da) + d * (1 - sa) + s * d.
     *
     * @since 11
     */
    BLEND_MODE_MULTIPLY,
    /**
     * Hue mode.
     *
     * @since 11
     */
    BLEND_MODE_HUE,
    /**
     * Saturation mode.
     *
     * @since 11
     */
    BLEND_MODE_SATURATION,
    /**
     * Color mode.
     *
     * @since 11
     */
    BLEND_MODE_COLOR,
    /**
     * Luminosity mode.
     *
     * @since 11
     */
    BLEND_MODE_LUMINOSITY,
} OH_Drawing_BlendMode;

/**
 * @brief Defines an enum for the text encoding types.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * One byte used to indicate UTF-8 or ASCII characters.
     *
     * @since 12
     */
    TEXT_ENCODING_UTF8,
    /**
     * Two bytes used to indicate most Unicode characters.
     *
     * @since 12
     */
    TEXT_ENCODING_UTF16,
    /**
     * Four bytes used to indicate all Unicode characters.
     *
     * @since 12
     */
    TEXT_ENCODING_UTF32,
    /**
     * Two bytes used to indicate the glyph index.
     *
     * @since 12
     */
    TEXT_ENCODING_GLYPH_ID,
} OH_Drawing_TextEncoding;

/**
 * @brief Defines a struct for the font manager, which is used for font management.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontMgr OH_Drawing_FontMgr;

/**
 * @brief Defines a struct for a font style set, which is used for font style family matching.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Drawing_FontStyleSet OH_Drawing_FontStyleSet;

/**
 * @brief Defines the recording command tool, which is used to generate recording commands.
 *
 * @since 13
 * @version 1.0
 */
typedef struct OH_Drawing_RecordCmdUtils OH_Drawing_RecordCmdUtils;

/**
 * @brief Defines the recording command class, which is used to store the set of recording commands.
 *
 * @since 13
 * @version 1.0
 */
typedef struct OH_Drawing_RecordCmd OH_Drawing_RecordCmd;

/**
 * @brief Defines a struct for an array object, which is used to store multiple objects of the same type.
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
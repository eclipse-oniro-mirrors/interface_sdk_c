/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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
 * @file drawing_bitmap.h
 *
 * @brief This file declares the functions related to the bitmap in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_BITMAP_H
#define C_INCLUDE_DRAWING_BITMAP_H

#include "drawing_types.h"
#include "drawing_error_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief This struct describes the pixel format of a bitmap, including the color type and alpha type.
 *
 * @since 8
 * @version 1.0
 */
typedef struct {
    /**
     * Storage format of bitmap pixels.
     */
    OH_Drawing_ColorFormat colorFormat;
    /**
     * Alpha format of bitmap pixels.
     */
    OH_Drawing_AlphaFormat alphaFormat;
} OH_Drawing_BitmapFormat;

/**
 * @brief 用于创建一个位图对象。
 *
 * @return 函数会返回一个指针，指针指向创建的位图对象。
 * @since 8
 * @version 1.0
 */
OH_Drawing_Bitmap* OH_Drawing_BitmapCreate(void);

/**
 * @brief 用于销毁位图对象并回收该对象占有内存。
 *
 * @param bitmap 指向位图对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_BitmapDestroy(OH_Drawing_Bitmap* bitmap);

/**
 * @brief 用于创建一个位图对象，并将位图像素存储内存地址设置为开发者申请内存的地址。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * imageInfo、pixels任意一个为NULL或者rowBytes等于0时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param imageInfo 指向图片信息对象{@link OH_Drawing_Image_Info}的指针。
 * @param pixels 指向像素存储的内存首地址，内存由开发者申请，保证有效性。
 * @param rowBytes 每行像素的大小，小于等于0时无效。
 * @return 函数返回一个指针，指针指向创建的位图对象{@link OH_Drawing_Bitmap}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Bitmap* OH_Drawing_BitmapCreateFromPixels(OH_Drawing_Image_Info* imageInfo, void* pixels, uint32_t rowBytes);

/**
 * @brief 用于初始化位图对象的宽度和高度，并且为该位图设置像素格式。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * bitmap、bitmapFormat任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象的指针。
 * @param width 位图要初始化设置的宽度。
 * @param height 位图要初始化设置的高度。
 * @param bitmapFormat 位图要初始化设置的像素格式，包括像素的颜色类型和透明度类型。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_BitmapBuild(OH_Drawing_Bitmap* bitmap,
    const uint32_t width, const uint32_t height, const OH_Drawing_BitmapFormat* bitmapFormat);

/**
 * @brief 用于获取指定位图的宽度。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * bitmap为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象的指针。
 * @return 函数返回位图的宽度。
 * @since 8
 * @version 1.0
 */
uint32_t OH_Drawing_BitmapGetWidth(OH_Drawing_Bitmap* bitmap);

/**
 * @brief 用于获取指定位图的高度。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * bitmap为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象的指针。
 * @return 函数返回位图的高度。
 * @since 8
 * @version 1.0
 */
uint32_t OH_Drawing_BitmapGetHeight(OH_Drawing_Bitmap* bitmap);

/**
 * @brief 用于获取指定位图的像素存储格式。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * bitmap为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象的指针。
 * @return 函数返回位图的像素存储格式，支持格式参考{@link OH_Drawing_ColorFormat}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ColorFormat OH_Drawing_BitmapGetColorFormat(OH_Drawing_Bitmap* bitmap);

/**
 * @brief 用于获取指定位图的像素透明度分量。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * bitmap为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象的指针。
 * @return 函数返回位图的像素透明度分量，支持格式参考{@link OH_Drawing_AlphaFormat}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_AlphaFormat OH_Drawing_BitmapGetAlphaFormat(OH_Drawing_Bitmap* bitmap);

/**
 * @brief 用于获取指定位图的像素地址，可以通过像素地址获取到位图的像素数据。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * bitmap为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象的指针。
 * @return 函数返回位图的像素地址。
 * @since 8
 * @version 1.0
 */
void* OH_Drawing_BitmapGetPixels(OH_Drawing_Bitmap* bitmap);

/**
 * @brief 用于获取指定位图的信息。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * bitmap、imageInfo任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象{@link OH_Drawing_Bitmap}的指针。
 * @param imageInfo 指向图片信息对象{@link OH_Drawing_Image_Info}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_BitmapGetImageInfo(OH_Drawing_Bitmap* bitmap, OH_Drawing_Image_Info* imageInfo);

/**
 * @brief 将位图中的矩形区域像素数据读取到指定的内存缓冲区中。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * bitmap、dstInfo、dstPixels任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象{@link OH_Drawing_Bitmap}的指针。
 * @param dstInfo 指向图片信息对象{@link OH_Drawing_Image_Info}的指针。
 * @param dstPixels 目标像素存储区域。
 * @param dstRowBytes 目标像素数据每行的字节数，应大于或等于图片信息对象中的最小每行字节数。
 * @param srcX 源位图中读取像素数据的起始x轴坐标，应小于源位图的宽度。
 * @param srcY 源位图中读取像素数据的起始y轴坐标，应小于源位图的高度。
 * @return 返回接口调用成功与否的结果。true表示复制成功，false表示复制失败。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_BitmapReadPixels(OH_Drawing_Bitmap* bitmap, const OH_Drawing_Image_Info* dstInfo,
    void* dstPixels, size_t dstRowBytes, int32_t srcX, int32_t srcY);

/**
 * @brief 获取bitmap的每行字节数
 *
 * @param bitmap 表示bitmap对象指针
 * @param bytes 表示bitmap的每行字节数
 * @return 返回错误码。
 *  操作成功时，返回{@link OH_DRAWING_SUCCESS}.
 *  bitmap或者bytes指针为空时，返回 {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER}
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_BitmapGetRowBytes(OH_Drawing_Bitmap* bitmap, uint32_t* bytes);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
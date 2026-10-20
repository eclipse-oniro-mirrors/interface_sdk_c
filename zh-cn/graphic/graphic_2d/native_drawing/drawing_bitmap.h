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
 * @brief Drawing模块提供包括2D图形渲染、文字绘制和图片显示等功能函数。
 * <br>本模块采用屏幕物理像素单位px。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file drawing_bitmap.h
 *
 * @brief 文件中定义了位图相关的功能函数，支持位图的创建与销毁、初始化宽高与像素格式、获取位图宽度、高度、行字节数、
 * 像素存储格式、透明度分量、像素地址及位图信息，以及将位图像素数据读取到指定内存缓冲区等操作。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
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
 * @brief 结构体用于描述位图像素的格式，包括颜色类型和透明度类型。
 *
 * @since 8
 * @version 1.0
 */
typedef struct {
    /**
     * 描述位图像素的存储格式。
     */
    OH_Drawing_ColorFormat colorFormat;
    /**
     * 描述位图像素的透明度分量。
     */
    OH_Drawing_AlphaFormat alphaFormat;
} OH_Drawing_BitmapFormat;

/**
 * @brief 用于创建一个位图对象。
 * 调用此方法创建的位图对象，在使用完毕后必须调用{@link OH_Drawing_BitmapDestroy}进行销毁并释放内存，
 * 否则会导致内存泄漏。
 *
 * @return 函数返回指向创建的位图对象的指针。
 * @since 8
 * @version 1.0
 */
OH_Drawing_Bitmap* OH_Drawing_BitmapCreate(void);

/**
 * @brief 用于销毁位图对象并回收该对象占用的内存。
 * 应与{@link OH_Drawing_BitmapCreate}或{@link OH_Drawing_BitmapCreateFromPixels}配对使用，
 * 对已创建的位图对象进行释放，避免内存泄漏。
 *
 * @param bitmap 指向位图对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_BitmapDestroy(OH_Drawing_Bitmap* bitmap);

/**
 * @brief 用于创建一个位图对象，并将位图存储像素的内存地址设置为开发者申请的内存地址。
 * 调用此方法创建的位图对象，在使用完毕后必须调用{@link OH_Drawing_BitmapDestroy}进行销毁并释放内存，
 * 否则会导致内存泄漏。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>imageInfo、pixels任意一个为NULL或者rowBytes等于0时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param imageInfo 指向图片信息对象{@link OH_Drawing_Image_Info}的指针，用于指定创建位图的尺寸和像素格式信息。
 * @param pixels 指向像素存储的内存首地址，内存由开发者申请，需保证内存在位图使用期间有效且大小充足。
 * 所需最小内存大小为rowBytes × imageInfo中height的值。
 * @param rowBytes 每行像素数据的字节数，等于0时无效。
 * @return 函数返回一个指针，指针指向创建的位图对象{@link OH_Drawing_Bitmap}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Bitmap* OH_Drawing_BitmapCreateFromPixels(OH_Drawing_Image_Info* imageInfo, void* pixels, uint32_t rowBytes);

/**
 * @brief 用于初始化位图对象的宽度和高度，并且为该位图设置像素格式。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>bitmap、bitmapFormat任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象的指针。
 * @param width 位图要初始化设置的宽度，单位为物理像素px，取值需大于0。
 * @param height 位图要初始化设置的高度，单位为物理像素px，取值需大于0。
 * @param bitmapFormat 位图要初始化设置的像素格式，包括像素的颜色类型和透明度类型。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_BitmapBuild(OH_Drawing_Bitmap* bitmap,
    const uint32_t width, const uint32_t height, const OH_Drawing_BitmapFormat* bitmapFormat);

/**
 * @brief 用于获取指定位图的宽度。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>bitmap为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象的指针。
 * @return 函数返回位图的宽度，单位为物理像素px。
 * @since 8
 * @version 1.0
 */
uint32_t OH_Drawing_BitmapGetWidth(OH_Drawing_Bitmap* bitmap);

/**
 * @brief 用于获取指定位图的高度。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>bitmap为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象的指针。
 * @return 函数返回位图的高度，单位为物理像素px。
 * @since 8
 * @version 1.0
 */
uint32_t OH_Drawing_BitmapGetHeight(OH_Drawing_Bitmap* bitmap);

/**
 * @brief 用于获取指定位图的像素存储格式。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>bitmap为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象的指针。
 * @return 函数返回位图的像素存储格式，支持格式参考{@link OH_Drawing_ColorFormat}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ColorFormat OH_Drawing_BitmapGetColorFormat(OH_Drawing_Bitmap* bitmap);

/**
 * @brief 用于获取指定位图的像素透明度分量。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>bitmap为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象的指针。
 * @return 函数返回位图的像素透明度分量，支持格式参考{@link OH_Drawing_AlphaFormat}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_AlphaFormat OH_Drawing_BitmapGetAlphaFormat(OH_Drawing_Bitmap* bitmap);

/**
 * @brief 用于获取指定位图的像素地址，可以通过像素地址获取到位图的像素数据。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>bitmap为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象的指针。
 * @return 函数返回位图的像素地址。
 * @since 8
 * @version 1.0
 */
void* OH_Drawing_BitmapGetPixels(OH_Drawing_Bitmap* bitmap);

/**
 * @brief 用于获取指定位图的图片信息，包括宽度、高度、颜色类型和透明度类型等。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>bitmap、imageInfo任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象{@link OH_Drawing_Bitmap}的指针。
 * @param imageInfo 指向图片信息对象{@link OH_Drawing_Image_Info}的指针。作为出参使用，用于接收获取到的图片信息。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_BitmapGetImageInfo(OH_Drawing_Bitmap* bitmap, OH_Drawing_Image_Info* imageInfo);

/**
 * @brief 将位图中的矩形区域像素数据读取到指定的内存缓冲区中。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>bitmap、dstInfo、dstPixels任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param bitmap 指向位图对象的指针。
 * @param dstInfo 指向目标图片信息对象{@link OH_Drawing_Image_Info}的指针，用于指定目标像素的格式信息及读取区域的宽高。
 * @param dstPixels 指向目标像素存储区域的内存首地址，内存由开发者申请，需保证缓冲区大小足够且有效。
 * 所需最小缓冲区大小为dstRowBytes × dstInfo中height的值。
 * @param dstRowBytes 目标像素数据每行的字节数，
 * 应大于或等于图片信息对象中的最小每行字节数（由目标区域的宽度和颜色类型决定）。
 * @param srcX 源位图中读取像素数据的起始x轴坐标，单位为物理像素px，取值范围<源位图宽度。
 * @param srcY 源位图中读取像素数据的起始y轴坐标，单位为物理像素px，取值范围为<源位图高度。
 * @return 函数返回接口调用成功与否的结果。true表示读取成功，false表示读取失败。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_BitmapReadPixels(OH_Drawing_Bitmap* bitmap, const OH_Drawing_Image_Info* dstInfo,
    void* dstPixels, size_t dstRowBytes, int32_t srcX, int32_t srcY);

/**
 * @brief 用于获取指定位图每行的字节数。
 *
 * @param bitmap 指向位图对象的指针。
 * @param bytes 指向uint32_t变量的指针，作为出参使用，用于接收位图的行字节数。
 * @return 函数返回执行错误码。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数bitmap或bytes为NULL。
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_BitmapGetRowBytes(OH_Drawing_Bitmap* bitmap, uint32_t* bytes);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
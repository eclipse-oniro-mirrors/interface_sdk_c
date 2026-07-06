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
 * @brief Provides functions such as 2D graphics rendering, text drawing, and image display.
 *
 * @since 12
 * @version 1.0
 */
/**
 * @file drawing_image.h
 *
 * @brief This file declares the functions related to the image in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_IMAGE_H
#define C_INCLUDE_DRAWING_IMAGE_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建一个图片对象，描述了要绘制的二维像素数组。
 *
 * @return 函数返回一个指针，指针指向创建的图片对象{@link OH_Drawing_Image}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Image* OH_Drawing_ImageCreate(void);

/**
 * @brief 销毁图片对象并回收该对象占用的内存。
 *
 * @param image 指向图片对象{@link OH_Drawing_Image}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ImageDestroy(OH_Drawing_Image* image);

/**
 * @brief 从位图构造图片对象内容，共享或复制位图像素。如果位图被标记为不可变状态，像素内存是共享的，不是复制。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * image、bitmap任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param image 指向图片对象{@link OH_Drawing_Image}的指针。
 * @param bitmap 指向位图对象{@link OH_Drawing_Bitmap}的指针。
 * @return 函数返回true表示构造图片内容成功，函数返回false表示构建图片内容失败。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_ImageBuildFromBitmap(OH_Drawing_Image* image, OH_Drawing_Bitmap* bitmap);

/**
 * @brief 获取图片宽度，即每行的像素个数。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * image为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param image 指向图片对象{@link OH_Drawing_Image}的指针。
 * @return 函数返回图片宽度。
 * @since 12
 * @version 1.0
 */
int32_t OH_Drawing_ImageGetWidth(OH_Drawing_Image* image);

/**
 * @brief 获取图片高度，即像素行数。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * image为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param image 指向图片对象{@link OH_Drawing_Image}的指针。
 * @return 函数返回图片高度。
 * @since 12
 * @version 1.0
 */
int32_t OH_Drawing_ImageGetHeight(OH_Drawing_Image* image);

/**
 * @brief 获取图片信息。调用该接口后，传入的图片信息对象被填充。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * image、imageInfo任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param image 指向图片对象{@link OH_Drawing_Image}的指针。
 * @param imageInfo 指向图片信息对象{@link OH_Drawing_Image_Info}的指针，开发者可调用{@link OH_Drawing_Image_Info}创建。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ImageGetImageInfo(OH_Drawing_Image* image, OH_Drawing_Image_Info* imageInfo);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
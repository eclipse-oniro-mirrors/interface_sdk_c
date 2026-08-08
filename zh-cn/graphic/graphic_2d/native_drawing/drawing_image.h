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
 * @brief 文件中定义了与图片相关的功能函数。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
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
 * @brief 创建一个图片对象，描述了要绘制的二维像素数组。使用完毕后，
 * 必须调用{@link OH_Drawing_ImageDestroy}销毁该图片对象并回收内存，否则会导致内存泄漏。
 *
 * @return 返回指向创建的图片对象{@link OH_Drawing_Image}的指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Image* OH_Drawing_ImageCreate(void);

/**
 * @brief 销毁图片对象并回收该对象占用的内存。与{@link OH_Drawing_ImageCreate}配对使用，用于销毁由其创建的图片对象。
 * 销毁后不应再使用该图片对象指针，否则可能导致未定义行为。
 *
 * @param image 指向由{@link OH_Drawing_ImageCreate}创建的图片对象{@link OH_Drawing_Image}的指针，
 * 用于销毁该图片对象并回收内存。销毁后不应再使用该指针，
 *     否则可能导致未定义行为。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ImageDestroy(OH_Drawing_Image* image);

/**
 * @brief 从位图构造图片对象内容，共享或复制位图像素。在已有位图数据需要在画布上绘制图片的场景中，
 * 可使用此接口将位图数据构造为图片对象。如果位图被标记为不可变状态，像素内存是共享的；
 * 如果位图未被标记为不可变状态（即位图为可变状态）
 * ，像素内存会被复制。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>image、bitmap任意一个为NULL时返回错误码OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param image 指向图片对象{@link OH_Drawing_Image}的指针，作为目标对象用于接收从位图构造的图片对象内容。
 * 当位图被标记为不可变状态时，图片对象的像素内存与位图共享，而非独立复制。
 * @param bitmap 指向位图对象{@link OH_Drawing_Bitmap}的指针，作为源数据用于构造图片对象内容。
 * 如果位图被标记为不可变状态，像素内存是共享的；如果位图未被标记为不可变状态（即位图为可变状态），
 *     像素内存会被复制。
 * @return 函数返回true表示构造图片内容成功，函数返回false表示构造图片内容失败。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_ImageBuildFromBitmap(OH_Drawing_Image* image, OH_Drawing_Bitmap* bitmap);

/**
 * @brief 获取图片宽度，单位为物理像素px，即每行的像素个数。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>image为NULL时返回错误码OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param image 指向要获取宽度的图片对象{@link OH_Drawing_Image}的指针。
 * @return 函数返回图片宽度，单位为物理像素px，即每行的像素个数。
 * @since 12
 * @version 1.0
 */
int32_t OH_Drawing_ImageGetWidth(OH_Drawing_Image* image);

/**
 * @brief 获取图片高度，单位为物理像素px，即像素行数。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>image为NULL时返回错误码OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param image 指向要获取高度的图片对象{@link OH_Drawing_Image}的指针。
 * @return 函数返回图片高度，单位为物理像素px，即像素行数。
 * @since 12
 * @version 1.0
 */
int32_t OH_Drawing_ImageGetHeight(OH_Drawing_Image* image);

/**
 * @brief 获取图片信息。调用该接口后，传入的图片信息对象被填充。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>image、imageInfo任意一个为NULL时返回错误码OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param image 指向要获取信息的图片对象{@link OH_Drawing_Image}的指针，作为图片信息的数据来源。
 * @param imageInfo 指向图片信息对象{@link OH_Drawing_Image_Info}的指针，作为输出参数用于接收获取到的图片信息，
 * 调用该接口后该对象会被填充。开发者可通过声明
 *     {@link OH_Drawing_Image_Info}结构体创建。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ImageGetImageInfo(OH_Drawing_Image* image, OH_Drawing_Image_Info* imageInfo);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
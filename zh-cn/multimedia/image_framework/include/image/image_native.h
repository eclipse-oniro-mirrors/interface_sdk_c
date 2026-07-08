/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup Image_NativeModule
 * @{
 *
 * @brief Provides APIs for access to the image interface.
 *
 * @since 12
 */

/**
 * @file image_native.h
 *
 * @brief 声明图像的剪辑矩形、大小和组件数据的接口函数。
 * 
 * @library libohimage.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 12
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_H
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_H

#include "image_common.h"
#include "native_buffer/native_buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 为图像接口定义native层图像对象的别名。<br>此结构体内容不可直接操作，采用函数调用方式操作具体字段，结构体内容和操作方式如下：<br>释放OH_ImageNative对象使用
 * {@link OH_ImageNative_Release}函数。
 * 
 * @since 12
 */
struct OH_ImageNative;

/**
 * @brief 为图像接口定义native层图像对象的别名。<br>此结构体内容不可直接操作，采用函数调用方式操作具体字段，结构体内容和操作方式如下：<br>释放OH_ImageNative对象使用
 * {@link OH_ImageNative_Release}函数。
 * 
 * @since 12
 */
typedef struct OH_ImageNative OH_ImageNative;

/**
 * @brief OH_ImageBufferData是native层封装的图像数据结构体。获取OH_ImageNative_GetBufferData对象使用{@link OH_ImageNative_GetBufferData}函数。
 * <br> 结构体中保存的是对原图像数据的浅拷贝，当原数据被释放后，不应再对该结构体中的指针进行任何读写操作，否则会出现未定义行为。
 *
 * @since 23
 */
typedef struct OH_ImageBufferData {
    /**
     * 图像颜色分量行间距的数组，单位为像素（px）。
     */
    int32_t *rowStride;
    /**
     * 图像颜色分量像素间距的数组，单位为像素（px）。
     */
    int32_t *pixelStride;
    /**
     * 数组长度。
     */
    int32_t  numStride;
    /**
     * 缓冲区的大小，单位为字节（Byte）。
     */
    size_t  bufferSize;
    /**
     * 图像的OH_NativeBuffer缓冲区对象的指针。
     */
    OH_NativeBuffer  *nativeBuffer;
} OH_ImageBufferData;

/**
 * @brief 获取Native {@link OH_ImageNative}对象的{@link Image_Size}信息。
 * <br>如果OH_ImageNative对象所存储的是相机预览流数据，即YUV图像数据，那么获取到的Image_Size中的宽高分别对应YUV图像的宽高；如果OH_ImageNative对象所存储的是相机拍照流数据，即JPEG图像，
 * 由于已经是编码后的数据，Image_Size中的宽等于JPEG数据大小，高等于1。
 * <br>OH_ImageNative对象所存储的数据是预览流还是拍照流，取决于应用将receiver中的surfaceId传给相机的previewOutput还是captureOutput。相机预览与拍照最佳实践请参考
 * {@link 预览流二次处理(C/C++)}与{@link 拍照(C/C++)}。
 *
 * @param image 表示OH_ImageNative native对象的指针。
 * @param size 表示作为获取结果的Image_Size对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNKNOWN_ERROR：未知原因错误。
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetImageSize(OH_ImageNative *image, Image_Size *size);

/**
 * @brief 获取Native {@link OH_ImageNative}对象的组件列表信息。
 * 
 * @param image 表示OH_ImageNative native对象的指针。
 * @param types 表示作为获取结果的组件类型列表对象的指针。由于不确定组件个数，需要调用该接口两次：第一次传入types参数为NULL，获取组件个数typeSize；第二次根据typeSize给types申请对应内存，
 *     获取组件类型列表。
 * @param typeSize 表示作为获取结果的组件列表中，元素个数的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetComponentTypes(OH_ImageNative *image,
    uint32_t **types, size_t *typeSize);

/**
 * @brief 获取Native {@link OH_ImageNative}对象中某个组件类型所对应的缓冲区。
 * 
 * @param image 表示OH_ImageNative native对象的指针。
 * @param componentType 表示组件的类型。通过{@link OH_ImageNative_GetComponentTypes}接口获取。
 * @param nativeBuffer 表示作为获取结果的OH_NativeBuffer缓冲区对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetByteBuffer(OH_ImageNative *image,
    uint32_t componentType, OH_NativeBuffer **nativeBuffer);

/**
 * @brief 获取Native {@link OH_ImageNative}对象中某个组件类型所对应的缓冲区的大小。
 * 
 * @param image 表示OH_ImageNative native对象的指针。
 * @param componentType 表示组件的类型。通过{@link OH_ImageNative_GetComponentTypes}接口获取。
 * @param size 表示作为获取结果的缓冲区大小的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetBufferSize(OH_ImageNative *image,
    uint32_t componentType, size_t *size);

/**
 * @brief 获取Native {@link OH_ImageNative}对象中某个组件类型所对应的像素行宽。
 * <br>读取相机预览流数据时，需要考虑按stride进行读取，具体用法参考{@link 预览流二次处理(C/C++)}。
 * 
 * @param image 表示OH_ImageNative native对象的指针。
 * @param componentType 表示组件的类型。通过{@link OH_ImageNative_GetComponentTypes}接口获取。
 * @param rowStride 表示作为获取结果的像素行宽的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetRowStride(OH_ImageNative *image,
    uint32_t componentType, int32_t *rowStride);

/**
 * @brief 获取Native {@link OH_ImageNative}对象中某个组件类型所对应的像素大小。
 * 
 * @param image 表示OH_ImageNative native对象的指针。
 * @param componentType 表示组件的类型。通过{@link OH_ImageNative_GetComponentTypes}接口获取。
 * @param pixelStride 表示作为获取结果的像素大小的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetPixelStride(OH_ImageNative *image,
    uint32_t componentType, int32_t *pixelStride);

/**
 * @brief 获取Native {@link OH_ImageNative}对象中的时间戳信息。时间戳以纳秒为单位，通常是单调递增的。
 * <br>时间戳的具体含义和基准取决于图像的生产者，在相机预览/拍照场景，生产者就是相机。来自不同生产者的图像的时间戳可能有不同的含义和基准，因此可能无法进行比较。
 * <br>如果要获取某张照片的生成时间，可以通过{@link OH_ImageSourceNative_GetImageProperty}接口读取相关的EXIF信息。
 * 
 * @param image 表示OH_ImageNative native对象的指针。
 * @param timestamp 表示作为获取结果的时间戳信息的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageNative_GetTimestamp(OH_ImageNative *image, int64_t *timestamp);

/**
 * @brief 释放Native {@link OH_ImageNative}对象。
 * 
 * @param image 表示OH_ImageNative native对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageNative_Release(OH_ImageNative *image);

/**
 * @brief 获取图像OH_ImageNative对象中的色彩空间。
 * 
 * @param image 表示OH_ImageNative native对象的指针。
 * @param colorSpaceName 表示图像色彩空间的指针，colorSpaceName的对应色彩空间请参考{@link ColorSpaceName}。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 23
 */
Image_ErrorCode OH_ImageNative_GetColorSpace(OH_ImageNative *image, int32_t *colorSpaceName);

/**
 * @brief 获取图像OH_ImageNative对象中的图像格式。
 * 
 * @param image 表示OH_ImageNative native对象的指针。
 * @param format 表示图像格式的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 23
 */
Image_ErrorCode OH_ImageNative_GetFormat(OH_ImageNative *image, OH_NativeBuffer_Format *format);

/**
 * @brief 获取图像OH_ImageNative对象中的图像缓冲区数据对象。
 * 
 * @param image 表示OH_ImageNative native对象的指针。
 * @param imageBufferData 表示图像缓冲区数据对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 23
 */
Image_ErrorCode OH_ImageNative_GetBufferData(OH_ImageNative *image, OH_ImageBufferData *imageBufferData);

#ifdef __cplusplus
};
#endif
/** @} */
#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_H

/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup Image
 * @{
 *
 * @brief Provides APIs for access to the image interface.
 *
 * @since 10
 * @version 2.0
 */

/**
 * @file image_mdk.h
 *
 * @brief 声明访问图像矩形、大小、格式和组件数据的函数。
 *
 * @library libimage_ndk.z.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 10
 * @version 2.0
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_MDK_H_
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_MDK_H_
#include "napi/native_api.h"
#include "image_mdk_common.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ImageNative_;

/**
 * @brief 为图像接口定义native层图像对象。
 *
 * @since 10
 * @version 2.0
 */
typedef struct ImageNative_ ImageNative;

/**
 * @brief 图像格式枚举值。
 *
 * @since 10
 * @version 2.0
 */
enum {
    /**
     * YCBCR422 semi-planar格式。
     */
    OHOS_IMAGE_FORMAT_YCBCR_422_SP = 1000,
    /**
     * JPEG编码格式。
     */
    OHOS_IMAGE_FORMAT_JPEG = 2000
};

/**
 * @brief 图像颜色通道类型枚举值。
 *
 * @since 10
 * @version 2.0
 */
enum {
    /**
     * 亮度信息。
     */
    OHOS_IMAGE_COMPONENT_FORMAT_YUV_Y = 1,
    /**
     * 色度信息。
     */
    OHOS_IMAGE_COMPONENT_FORMAT_YUV_U = 2,
    /**
     * 色差值信息。
     */
    OHOS_IMAGE_COMPONENT_FORMAT_YUV_V = 3,
    /**
     * JPEG格式。
     */
    OHOS_IMAGE_COMPONENT_FORMAT_JPEG = 4,
};

/**
 * @brief 定义图像矩形信息。
 *
 * @since 10
 * @version 2.0
 */
struct OhosImageRect {
    /**
     * 矩形x坐标值。
     */
    int32_t x;
    /**
     * 矩形y坐标值。
     */
    int32_t y;
    /**
     * 矩形宽度值，用pixels表示。
     */
    int32_t width;
    /**
     * 矩形高度值，用pixels表示。
     */
    int32_t height;
};

/**
 * @brief 定义图像组成信息。
 *
 * @since 10
 * @version 2.0
 */
struct OhosImageComponent {
    /**
     * 像素数据地址。
     */
    uint8_t* byteBuffer;
    /**
     * 内存中的像素数据大小。
     */
    size_t size;
    /**
     * 像素数据类型。<br>1：OHOS_IMAGE_COMPONENT_FORMAT_YUV_Y 亮度信息。<br>2：OHOS_IMAGE_COMPONENT_FORMAT_YUV_U 色度信息。<br>3：
     * OHOS_IMAGE_COMPONENT_FORMAT_YUV_V 色差值信息。<br>4：OHOS_IMAGE_COMPONENT_FORMAT_JPEG JPEG格式。
     */
    int32_t componentType;
    /**
     * 像素数据行宽。读取相机预览流数据时，需要考虑按stride进行读取，具体用法见{@link C/C++预览流二次处理示例}。
     */
    int32_t rowStride;
    /**
     * 像素数据的像素大小。
     */
    int32_t pixelStride;
};

/**
 * @brief 从输入的JavaScript Native API图像对象中解析native ImageNative对象。
 *
 * @param env 表示指向JNI环境的指针。
 * @param source 表示JavaScript Native API图像对象。
 * @return 如果操作成功返回ImageNative指针对象，如果操作失败返回空指针。
 * @see ImageNative, OH_Image_Release
 * @since 10
 * @version 2.0
 */
ImageNative* OH_Image_InitImageNative(napi_env env, napi_value source);

/**
 * @brief 获取native ImageNative对象OhosImageRect信息。
 *
 * @param native 表示指向ImageNative native层对象的指针。
 * @param rect 表示作为转换结果的OhosImageRect对象指针。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_SURFACE_GET_PARAMETER_FAILED：从surface获取参数失败。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 * @see ImageNative, OhosImageRect
 * @since 10
 * @version 2.0
 */
int32_t OH_Image_ClipRect(const ImageNative* native, struct OhosImageRect* rect);

/**
 * @brief 获取native ImageNative对象的OhosImageSize信息。
 * <br>如果ImageNative对象所存储的是相机预览流数据，即YUV图像数据，那么获取到的OhosImageSize中的宽高分别对应YUV图像的宽高；如果ImageNative对象所存储的是相机拍照流数据，即JPEG图像，
 * 由于已经是编码后的数据，OhosImageSize中的宽等于JPEG数据大小，高等于1。
 * <br>ImageNative对象所存储的数据是预览流还是拍照流，取决于应用将receiver中的surfaceId传给相机的previewOutput还是captureOutput。相机预览与拍照最佳实践请参考
 * {@link 预览流二次处理(C/C++)}与{@link 拍照(C/C++)}。
 *
 * @param native 表示ImageNative native对象的指针。
 * @param size 表示作为转换结果的OhosImageSize对象的指针。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_SURFACE_GET_PARAMETER_FAILED：从surface获取参数失败。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 * @see ImageNative, OhosImageSize
 * @since 10
 * @version 2.0
 */
int32_t OH_Image_Size(const ImageNative* native, struct OhosImageSize* size);

/**
 * @brief 获取native ImageNative对象的图像格式。
 *
 * @param native 表示ImageNative native对象的指针。
 * @param format 表示作为转换结果的图像格式对象的指针。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_SURFACE_GET_PARAMETER_FAILED：从surface获取参数失败。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 * @see ImageNative
 * @since 10
 * @version 2.0
 */
int32_t OH_Image_Format(const ImageNative* native, int32_t* format);

/**
 * @brief 从native ImageNative对象中获取OhosImageComponent。
 *
 * @param native 表示ImageNative native对象的指针。
 * @param componentType 表示所需组件的组件类型。
 * @param componentNative 表示转换结果的OhosImageComponent对象的指针。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_SURFACE_GET_PARAMETER_FAILED：从surface获取参数失败。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 * @see ImageNative, OhosImageComponent
 * @since 10
 * @version 2.0
 */
int32_t OH_Image_GetComponent(const ImageNative* native,
    int32_t componentType, struct OhosImageComponent* componentNative);

/**
 * @brief 释放ImageNative native对象。
 * <br>这个方法无法释放JavaScript Native API Image对象，而是释放被{@link OH_Image_InitImageNative}解析的ImageNative native对象。
 *
 * @param native 表示ImageNative native对象的指针。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 * @see ImageNative, OH_Image_InitImageNative
 * @since 10
 * @version 2.0
 */
int32_t OH_Image_Release(ImageNative* native);
#ifdef __cplusplus
};
#endif
/** @} */
#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_MDK_H_

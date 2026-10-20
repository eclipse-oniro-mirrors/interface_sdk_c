/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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
 * @brief 提供image接口的访问。
 *
 * @since 8
 * @version 1.0
 */

/**
 * @file image_pixel_map_mdk.h
 *
 * @brief 声明可以锁定并访问pixelmap数据的方法，声明解锁的方法。推荐使用[pixelmap_native.h](./image/pixelmap_native.h)。
 *
 * @library libpixelmap_ndk.z.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 10
 * @version 1.0
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PIXEL_MAP_MDK_H_
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PIXEL_MAP_MDK_H_
#include <stdint.h>
#include "napi/native_api.h"
#include "image_mdk_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义Native层PixelMap数据类型名称。作为Native层操作PixelMap的句柄类型，
 * 适用于在C/C++层对PixelMap进行像素读写、属性查询、图像变换等操作的场景。
 * @since 10
 * @version 1.0
 */
struct NativePixelMap_;

/**
 * @brief 定义native层PixelMap数据类型名称。
 * @since 10
 * @version 1.0
 */
typedef struct NativePixelMap_ NativePixelMap;

/**
 * @brief 用于描述PixelMap的基本属性信息，包括图片宽高、内存行字节数和像素格式。<br>
 * 开发者在调用PixelMap属性查询相关接口时，可通过该结构体获取PixelMap的宽、高、行字节数及像素格式等信息，
 * 便于统一读取和管理图片属性。适用于需要查询并使用PixelMap属性信息的场景。
 *
 * @since 10
 * @version 1.0
 */
typedef struct OhosPixelMapInfos {
    /** 图片的宽，单位：像素（px）。 */
    uint32_t width;
    /** 图片的高，单位：像素（px）。 */
    uint32_t height;
    /** 图片在内存中每行所占的字节数。<br>
     * DMA内存为图片的宽 * 每个像素的字节数 + 每行末尾填充字节数；其他内存（非DMA内存）为图片的宽 * 每个像素的字节数。
     * 具体内存类型取决于PixelMap的创建方式，详情可参考PixelMap创建相关接口的说明。
     */
    uint32_t rowSize;
    /** 图片像素的格式，取值范围：<br>
     * 0：未知格式。<br>
     * 2：格式为RGB_565。<br>
     * 3：格式为RGBA_8888。<br>
     * 4：格式为BGRA_8888。<br>
     * 5：格式为RGB_888。<br>
     * 6：格式为ALPHA_8。<br>
     * 7：格式为RGBA_F16。<br>
     * 8：格式为NV21。<br>
     * 9：格式为NV12。
     */
    int32_t pixelFormat;
} OhosPixelMapInfos;

/**
 * @brief PixelMap透明度类型的枚举。
 *
 * @since 10
 * @version 1.0
 */
enum {
    /**
     * 未知的格式。
     */
    OHOS_PIXEL_MAP_ALPHA_TYPE_UNKNOWN = 0,
    /**
     * 不透明的格式。
     */
    OHOS_PIXEL_MAP_ALPHA_TYPE_OPAQUE = 1,
    /**
     * 预乘的格式。
     */
    OHOS_PIXEL_MAP_ALPHA_TYPE_PREMUL = 2,
    /**
     * 预除的格式。
     */
    OHOS_PIXEL_MAP_ALPHA_TYPE_UNPREMUL = 3
};

/**
 * @brief PixelMap编辑类型的枚举。
 *
 * @since 10
 * @version 1.0
 */
enum {
    /**
     * 只读的格式。
     */
    OHOS_PIXEL_MAP_READ_ONLY = 0,
    /**
     * 可编辑的格式。
     */
    OHOS_PIXEL_MAP_EDITABLE = 1,
};

/**
 * @brief Pixelmap缩放时采用的缩放算法。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 最近邻插值算法。
     */
    OH_PixelMap_AntiAliasing_NONE = 0,
    /**
     * 双线性插值算法。
     */
    OH_PixelMap_AntiAliasing_LOW = 1,
    /**
     * 双线性插值算法，同时开启Mipmap。缩小图片时建议使用。
     */
    OH_PixelMap_AntiAliasing_MEDIUM = 2,
    /**
     * 三次插值算法。
     */
    OH_PixelMap_AntiAliasing_HIGH = 3,
} OH_PixelMap_AntiAliasingLevel;

/**
 * @brief 用于定义创建PixelMap的设置选项，包含图片宽高、像素格式、是否可编辑、透明度类型及缩放类型信息，
 * 适用于在Native层创建PixelMap时指定初始化属性的场景。
 *
 * @since 10
 * @version 1.0
 */
struct OhosPixelMapCreateOps {
    /** 图片的宽，单位：像素（px）。取值必须大于0。传入0时创建Pixelmap失败。 */
    uint32_t width;
    /** 图片的高，单位：像素（px）。取值必须大于0。传入0时创建Pixelmap失败。 */
    uint32_t height;
    /** @brief 图片的像素格式。取值范围：
      * 0：未知格式。<br>
      * 2：格式为RGB_565。<br>
      * 3：格式为RGBA_8888。<br>
      * 4：格式为BGRA_8888。<br>
      * 5：格式为RGB_888。<br>
      * 6：格式为ALPHA_8。<br>
      * 7：格式为RGBA_F16。<br>
      * 8：格式为NV21。<br>
      * 9：格式为NV12。
      */
    int32_t pixelFormat;
    /** 是否可编辑。1表示图片像素可编辑，0表示不可编辑。 */
    uint32_t editable;
    /** 图片的透明度类型。取值范围：<br>
     * 0：未知透明度。<br>
     * 1：没有Alpha通道或图片不透明。<br>
     * 2：预乘透明度格式。<br>
     * 3：非预乘透明度格式。
     */
    uint32_t alphaType;
    /** 图片的缩放类型。取值范围：<br>
      * 1：缩放图像以填充目标图像区域并居中裁剪区域外的效果。<br>
      * 0：等比缩放适配目标图片尺寸（保持宽高比）。
      */
    uint32_t scaleMode;
};

/**
 * @brief 创建PixelMap对象。当前只支持输入流为BGRA格式的流。<br>
 * 该接口传入的buf不支持stride。<br>
 * 该接口不支持DMA内存。
 *
 * @param env napi的环境指针。
 * @param info PixelMap数据设置项。
 * @param buf 图片的buffer数据。
 * @param len 图片大小信息。
 * @param res 应用层的PixelMap对象的指针。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_GET_DATA_ABNORMAL：图像获取数据失败。<br>
 * IMAGE_RESULT_DECODE_FAILED：解码失败。<br>
 * IMAGE_RESULT_DECODE_HEAD_ABNORMAL：图像头解码失败。<br>
 * IMAGE_RESULT_CREATE_DECODER_FAILED：创建解码器失败。<br>
 * IMAGE_RESULT_CREATE_ENCODER_FAILED：创建编码器失败。<br>
 * IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式失败。<br>
 * IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia能力失败。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST：共享内存失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据错误。<br>
 * IMAGE_RESULT_DECODE_ABNORMAL：图像解码失败。<br>
 * IMAGE_RESULT_DECODE_FAILED：解码失败。<br>
 * IMAGE_RESULT_MALLOC_ABNORMAL：图像分配内存失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：图像数据不支持。<br>
 * IMAGE_RESULT_INIT_ABNORMAL：图像初始化失败。<br>
 * IMAGE_RESULT_CROP：裁剪失败。<br>
 * IMAGE_RESULT_UNKNOWN_FORMAT：图像格式未知。<br>
 * IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。<br>
 * IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。<br>
 * IMAGE_RESULT_ENCODE_FAILED：图像添加像素位图失败。<br>
 * IMAGE_RESULT_HW_DECODE_UNSUPPORT：图像不支持硬件解码。<br>
 * IMAGE_RESULT_HW_DECODE_FAILED：硬件解码失败。<br>
 * IMAGE_RESULT_INDEX_INVALID：ipc失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。<br>
 * IMAGE_RESULT_ALPHA_TYPE_ERROR：透明度类型错误。<br>
 * IMAGE_RESULT_ALLOCATER_TYPE_ERROR：内存分配类型错误。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_CreatePixelMap(napi_env env, OhosPixelMapCreateOps info,
    void* buf, size_t len, napi_value* res);

/**
 * @brief 创建PixelMap对象。<br>
 * 当前只支持输入流为BGRA格式的流。pixelmap内存在RGBA格式下，默认为DMA内存（图片512\*512以上）。
 *
 * @param env napi的环境指针。
 * @param info PixelMap数据设置项。
 * @param buf 图片的buffer数据。
 * @param len 图片buffer大小信息。
 * @param rowStride 图片跨距信息。跨距，图像每行占用的真实内存大小，单位为字节。
 *     跨距 = width \* 单位像素字节数 + padding，padding为每行为内存对齐做的填充区域。
 * @param res 应用层的PixelMap对象的指针。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_GET_DATA_ABNORMAL：图像获取数据失败。<br>
 * IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式失败。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据错误。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。<br>
 * IMAGE_RESULT_UNKNOWN_FORMAT：图像格式未知。
 * @since 12
 * @version 1.0
 */
int32_t OH_PixelMap_CreatePixelMapWithStride(napi_env env, OhosPixelMapCreateOps info,
    void* buf, size_t len, int32_t rowStride, napi_value* res);

/**
 * @brief 根据Alpha通道的信息，来生成一个仅包含Alpha通道信息的PixelMap对象。
 *
 * @param env napi的环境指针。
 * @param source 应用层的PixelMap对象。
 * @param alpha alpha通道的指针。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_GET_DATA_ABNORMAL：图像获取数据失败。<br>
 * IMAGE_RESULT_DECODE_FAILED：解码失败。<br>
 * IMAGE_RESULT_DECODE_HEAD_ABNORMAL：图像头解码失败。<br>
 * IMAGE_RESULT_CREATE_DECODER_FAILED：创建解码器失败。<br>
 * IMAGE_RESULT_CREATE_ENCODER_FAILED：创建编码器失败。<br>
 * IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式失败。<br>
 * IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia能力失败。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST：共享内存失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据错误。<br>
 * IMAGE_RESULT_DECODE_ABNORMAL：图像解码失败。<br>
 * IMAGE_RESULT_MALLOC_ABNORMAL：图像分配内存失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：图像数据不支持。<br>
 * IMAGE_RESULT_INIT_ABNORMAL：图像初始化失败。<br>
 * IMAGE_RESULT_CROP：裁剪失败。<br>
 * IMAGE_RESULT_UNKNOWN_FORMAT：图像格式未知。<br>
 * IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。<br>
 * IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。<br>
 * IMAGE_RESULT_ENCODE_FAILED：图像添加像素位图失败。<br>
 * IMAGE_RESULT_HW_DECODE_UNSUPPORT：图像不支持硬件解码。<br>
 * IMAGE_RESULT_HW_DECODE_FAILED：硬件解码失败。<br>
 * IMAGE_RESULT_INDEX_INVALID：ipc失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。<br>
 * IMAGE_RESULT_ALPHA_TYPE_ERROR：透明度类型错误。<br>
 * IMAGE_RESULT_ALLOCATER_TYPE_ERROR：内存分配类型错误。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_CreateAlphaPixelMap(napi_env env, napi_value source, napi_value* alpha);

/**
 * @brief 初始化NativePixelMap对象。
 *
 * @param env napi的环境指针。
 * @param source 应用层的PixelMap对象。
 * @return 操作成功则返回NativePixelMap的指针；如果操作失败，则返回错误码。
 * @since 10
 * @version 1.0
 */
NativePixelMap* OH_PixelMap_InitNativePixelMap(napi_env env, napi_value source);

/**
 * @brief 获取PixelMap对象每行字节数。
 *
 * @param native NativePixelMap的指针。
 * @param num PixelMap对象的每行字节数指针。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_GetBytesNumberPerRow(const NativePixelMap* native, int32_t* num);

/**
 * @brief 获取PixelMap对象是否可编辑的状态。
 *
 * @param native NativePixelMap的指针。
 * @param editable PixelMap对象是否可编辑的指针。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_GetIsEditable(const NativePixelMap* native, int32_t* editable);

/**
 * @brief 获取PixelMap对象是否支持Alpha通道。
 *
 * @param native NativePixelMap的指针。
 * @param alpha 是否支持Alpha的指针。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_IsSupportAlpha(const NativePixelMap* native, int32_t* alpha);

/**
 * @brief 设置PixelMap对象的Alpha通道。
 *
 * @param native NativePixelMap的指针。
 * @param alpha Alpha通道。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_SetAlphaAble(const NativePixelMap* native, int32_t alpha);

/**
 * @brief 获取PixelMap对象像素密度。
 *
 * @param native NativePixelMap的指针。
 * @param density 像素密度指针。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_GetDensity(const NativePixelMap* native, int32_t* density);

/**
 * @brief 设置PixelMap对象像素密度。
 *
 * @param native NativePixelMap的指针。
 * @param density 像素密度。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_SetDensity(const NativePixelMap* native, int32_t density);

/**
 * @brief 设置PixelMap对象的透明度。
 *
 * @param native NativePixelMap的指针。
 * @param opacity 透明度。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_SetOpacity(const NativePixelMap* native, float opacity);

/**
 * @brief 设置PixelMap对象的缩放。<br>
 * 从API 12开始，推荐使用新接口{@link OH_PixelmapNative_Scale}。
 *
 * @param native NativePixelMap的指针。
 * @param x 宽度的缩放比例。
 * @param y 高度的缩放比例。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_GET_DATA_ABNORMAL：图像获取数据失败。<br>
 * IMAGE_RESULT_DECODE_FAILED：解码失败。<br>
 * IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式失败。<br>
 * IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia能力失败。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST：共享内存失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据错误。<br>
 * IMAGE_RESULT_MALLOC_ABNORMAL：图像分配内存失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：图像数据不支持。<br>
 * IMAGE_RESULT_INIT_ABNORMAL：图像初始化失败。<br>
 * IMAGE_RESULT_CROP：裁剪失败。<br>
 * IMAGE_RESULT_UNKNOWN_FORMAT：图像格式未知。<br>
 * IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。<br>
 * IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。<br>
 * IMAGE_RESULT_ALPHA_TYPE_ERROR：透明度类型错误。<br>
 * IMAGE_RESULT_ALLOCATER_TYPE_ERROR：内存分配类型错误。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_Scale(const NativePixelMap* native, float x, float y);

/**
 * @brief 根据指定的缩放算法和输入的宽高对图片进行缩放。<br>
 * 从API 12开始，推荐使用新接口{@link OH_PixelmapNative_ScaleWithAntiAliasing}。
 *
 * @param native NativePixelMap的指针。
 * @param x 宽度的缩放比例。
 * @param y 高度的缩放比例。
 * @param level 缩放算法。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_GET_DATA_ABNORMAL：图像获取数据失败。<br>
 * IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式失败。<br>
 * IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia能力失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据错误。<br>
 * IMAGE_RESULT_MALLOC_ABNORMAL：图像分配内存失败。<br>
 * IMAGE_RESULT_UNKNOWN_FORMAT：图像格式未知。
 * @since 12
 * @version 1.0
 */
int32_t OH_PixelMap_ScaleWithAntiAliasing(const NativePixelMap* native, float x, float y,
    OH_PixelMap_AntiAliasingLevel level);

/**
 * @brief 设置PixelMap对象的偏移。<br>
 * 从API 12开始，推荐使用新接口{@link OH_PixelmapNative_Translate}。
 *
 * @param native NativePixelMap的指针。
 * @param x 水平偏移量。
 * @param y 垂直偏移量。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_GET_DATA_ABNORMAL：图像获取数据失败。<br>
 * IMAGE_RESULT_DECODE_FAILED：解码失败。<br>
 * IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式失败。<br>
 * IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia能力失败。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST：共享内存失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据错误。<br>
 * IMAGE_RESULT_MALLOC_ABNORMAL：图像分配内存失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：图像数据不支持。<br>
 * IMAGE_RESULT_CROP：裁剪失败。<br>
 * IMAGE_RESULT_UNKNOWN_FORMAT：图像格式未知。<br>
 * IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。<br>
 * IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。<br>
 * IMAGE_RESULT_ALPHA_TYPE_ERROR：透明度类型错误。<br>
 * IMAGE_RESULT_ALLOCATER_TYPE_ERROR：内存分配类型错误。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_Translate(const NativePixelMap* native, float x, float y);

/**
 * @brief 设置PixelMap对象的旋转。<br>
 * 从API 12开始，推荐使用新接口{@link OH_PixelmapNative_Rotate}。
 *
 * @param native NativePixelMap的指针。
 * @param angle 旋转角度。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_GET_DATA_ABNORMAL：图像获取数据失败。<br>
 * IMAGE_RESULT_DECODE_FAILED：解码失败。<br>
 * IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式失败。<br>
 * IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia能力失败。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST：共享内存失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据错误。<br>
 * IMAGE_RESULT_MALLOC_ABNORMAL：图像分配内存失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：图像数据不支持。<br>
 * IMAGE_RESULT_CROP：裁剪失败。<br>
 * IMAGE_RESULT_UNKNOWN_FORMAT：图像格式未知。<br>
 * IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。<br>
 * IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。<br>
 * IMAGE_RESULT_ALPHA_TYPE_ERROR：透明度类型错误。<br>
 * IMAGE_RESULT_ALLOCATER_TYPE_ERROR：内存分配类型错误。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_Rotate(const NativePixelMap* native, float angle);

/**
 * @brief 设置PixelMap对象的翻转。<br>
 * 从API 12开始，推荐使用新接口{@link OH_PixelmapNative_Flip}。
 *
 * @param native NativePixelMap的指针。
 * @param x 根据水平方向x轴进行图片翻转。
 * @param y 根据垂直方向y轴进行图片翻转。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_GET_DATA_ABNORMAL：图像获取数据失败。<br>
 * IMAGE_RESULT_DECODE_FAILED：解码失败。<br>
 * IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式失败。<br>
 * IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia能力失败。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST：共享内存失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据错误。<br>
 * IMAGE_RESULT_MALLOC_ABNORMAL：图像分配内存失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：图像数据不支持。<br>
 * IMAGE_RESULT_CROP：裁剪失败。<br>
 * IMAGE_RESULT_UNKNOWN_FORMAT：图像格式未知。<br>
 * IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。<br>
 * IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。<br>
 * IMAGE_RESULT_ALPHA_TYPE_ERROR：透明度类型错误。<br>
 * IMAGE_RESULT_ALLOCATER_TYPE_ERROR：内存分配类型错误。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_Flip(const NativePixelMap* native, int32_t x, int32_t y);

/**
 * @brief 设置PixelMap对象的裁剪。<br>
 * 从API 12开始，推荐使用新接口{@link OH_PixelmapNative_Crop}。
 *
 * @param native NativePixelMap的指针。
 * @param x 目标图片左上角的x坐标。
 * @param y 目标图片左上角的y坐标。
 * @param width 裁剪区域的宽度。
 * @param height 裁剪区域的高度。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_GET_DATA_ABNORMAL：图像获取数据失败。<br>
 * IMAGE_RESULT_DECODE_FAILED：解码失败。<br>
 * IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式失败。<br>
 * IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia能力失败。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST：共享内存失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据错误。<br>
 * IMAGE_RESULT_MALLOC_ABNORMAL：图像分配内存失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：图像数据不支持。<br>
 * IMAGE_RESULT_CROP：裁剪失败。<br>
 * IMAGE_RESULT_UNKNOWN_FORMAT：图像格式未知。<br>
 * IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。<br>
 * IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。<br>
 * IMAGE_RESULT_ALPHA_TYPE_ERROR：透明度类型错误。<br>
 * IMAGE_RESULT_ALLOCATER_TYPE_ERROR：内存分配类型错误。
 * @since 10
 * @version 1.0
 */
int32_t OH_PixelMap_Crop(const NativePixelMap* native, int32_t x, int32_t y, int32_t width, int32_t height);

/**
 * @brief 获取PixelMap对象图像信息。<br>
 * 从API 12开始，推荐使用新接口{@link OH_PixelmapNative_GetImageInfo}。
 *
 * @param native NativePixelMap的指针。
 * @param info 图像信息指针。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_GET_DATA_ABNORMAL：图像获取数据失败。<br>
 * IMAGE_RESULT_DECODE_FAILED：解码失败。<br>
 * IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式失败。<br>
 * IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia能力失败。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST：共享内存失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据错误。<br>
 * IMAGE_RESULT_MALLOC_ABNORMAL：图像分配内存失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：图像数据不支持。<br>
 * IMAGE_RESULT_CROP：裁剪失败。<br>
 * IMAGE_RESULT_UNKNOWN_FORMAT：图像格式未知。<br>
 * IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。<br>
 * IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。<br>
 * IMAGE_RESULT_ALPHA_TYPE_ERROR：透明度类型错误。<br>
 * IMAGE_RESULT_ALLOCATER_TYPE_ERROR：内存分配类型错误。
 * @since 10
 * @version 2.0
 */
int32_t OH_PixelMap_GetImageInfo(const NativePixelMap* native, OhosPixelMapInfos *info);

/**
 * @brief 获取native PixelMap对象数据的内存地址，并锁定该内存。
 *
 * @param native NativePixelMap的指针。
 * @param addr 用于指向的内存地址的双指针对象。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_GET_DATA_ABNORMAL：图像获取数据失败。<br>
 * IMAGE_RESULT_DECODE_FAILED：解码失败。<br>
 * IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式失败。<br>
 * IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia能力失败。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST：共享内存失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据错误。<br>
 * IMAGE_RESULT_MALLOC_ABNORMAL：图像分配内存失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：图像数据不支持。<br>
 * IMAGE_RESULT_CROP：裁剪失败。<br>
 * IMAGE_RESULT_UNKNOWN_FORMAT：图像格式未知。<br>
 * IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。<br>
 * IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。<br>
 * IMAGE_RESULT_ALPHA_TYPE_ERROR：透明度类型错误。<br>
 * IMAGE_RESULT_ALLOCATER_TYPE_ERROR：内存分配类型错误。
 * @since 10
 * @version 2.0
 */
int32_t OH_PixelMap_AccessPixels(const NativePixelMap* native, void** addr);

/**
/**
 * @brief 释放native PixelMap对象数据的内存锁，用于匹配方法{@link OH_PixelMap_AccessPixels}。
 *
 * @param native NativePixelMap的指针。
 * @return {@link IRNdkErrCode}：<br>
 * IMAGE_RESULT_SUCCESS：操作成功。<br>
 * IMAGE_RESULT_BAD_PARAMETER：参数错误。<br>
 * IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。<br>
 * IMAGE_RESULT_INVALID_PARAMETER：参数无效。<br>
 * IMAGE_RESULT_GET_DATA_ABNORMAL：图像获取数据失败。<br>
 * IMAGE_RESULT_DECODE_FAILED：解码失败。<br>
 * IMAGE_RESULT_CHECK_FORMAT_ERROR：检查格式失败。<br>
 * IMAGE_RESULT_THIRDPART_SKIA_ERROR：skia能力失败。<br>
 * IMAGE_RESULT_DATA_ABNORMAL：图像输入数据失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_NOT_EXIST：共享内存失败。<br>
 * IMAGE_RESULT_ERR_SHAMEM_DATA_ABNORMAL：共享内存数据错误。<br>
 * IMAGE_RESULT_MALLOC_ABNORMAL：图像分配内存失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：图像数据不支持。<br>
 * IMAGE_RESULT_CROP：裁剪失败。<br>
 * IMAGE_RESULT_UNKNOWN_FORMAT：图像格式未知。<br>
 * IMAGE_RESULT_PLUGIN_REGISTER_FAILED：注册插件失败。<br>
 * IMAGE_RESULT_PLUGIN_CREATE_FAILED：创建插件失败。<br>
 * IMAGE_RESULT_DATA_UNSUPPORT：属性无效。<br>
 * IMAGE_RESULT_ALPHA_TYPE_ERROR：透明度类型错误。<br>
 * IMAGE_RESULT_ALLOCATER_TYPE_ERROR：内存分配类型错误。
 * @since 10
 * @version 2.0
 */
int32_t OH_PixelMap_UnAccessPixels(const NativePixelMap* native);

#ifdef __cplusplus
};
#endif
/** @} */

#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PIXEL_MAP_NAPI_H_

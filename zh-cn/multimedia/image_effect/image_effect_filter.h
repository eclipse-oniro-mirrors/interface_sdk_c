/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup ImageEffect
 * @{
 *
 * @brief 提供图片编辑能力。
 *
 * @since 12
 */

/**
 * @file image_effect_filter.h
 *
 * @brief 声明滤镜相关接口。
 *
 * 开发者可以通过滤镜的接口快速实现基本的效果处理，也可以将滤镜添加到效果器中，组合成滤镜链串联执行。
 * 系统提供了如“亮度”、“裁剪”等基本的效果处理滤镜。
 *
 * @library libimage_effect.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */

#ifndef NATIVE_IMAGE_EFFECT_FILTER_H
#define NATIVE_IMAGE_EFFECT_FILTER_H

#include <stdbool.h>
#include <stdint.h>
#include "image_effect_errors.h"
#include "multimedia/image_framework/image/pixelmap_native.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义滤镜结构类型。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef struct OH_EffectFilter OH_EffectFilter;

/**
 * @brief 亮度滤镜，对应的参数为OH_EFFECT_FILTER_INTENSITY_KEY，参数类型为{@link EFFECT_DATA_TYPE_FLOAT}。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
#define OH_EFFECT_BRIGHTNESS_FILTER "Brightness"

/**
 * @brief 对比度滤镜，对应的参数为OH_EFFECT_FILTER_INTENSITY_KEY，参数类型为{@link EFFECT_DATA_TYPE_FLOAT}。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
#define OH_EFFECT_CONTRAST_FILTER "Contrast"

/**
 * @brief 裁剪滤镜，对应的参数为OH_EFFECT_FILTER_REGION_KEY，参数类型为{@link EFFECT_DATA_TYPE_PTR}，
 * 参数值为结构体 {@link ImageEffect_Region}。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
#define OH_EFFECT_CROP_FILTER "Crop"

/**
 * @brief 强度参数。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
#define OH_EFFECT_FILTER_INTENSITY_KEY "FilterIntensity"

/**
 * @brief 图像区域参数。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
#define OH_EFFECT_FILTER_REGION_KEY "FilterRegion"

/**
 * @brief 数据类型枚举值。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef enum ImageEffect_DataType {
    /** 未定义类型。 */
    EFFECT_DATA_TYPE_UNKNOWN = 0,
    /** 整形。 */
    EFFECT_DATA_TYPE_INT32 = 1,
    /** 单精度浮点型。 */
    EFFECT_DATA_TYPE_FLOAT = 2,
    /** 双精度浮点型。 */
    EFFECT_DATA_TYPE_DOUBLE = 3,
    /** 字节类型。 */
    EFFECT_DATA_TYPE_CHAR = 4,
    /** 长整型。 */
    EFFECT_DATA_TYPE_LONG = 5,
    /** 布尔类型。 */
    EFFECT_DATA_TYPE_BOOL = 6,
    /** 指针类型。 */
    EFFECT_DATA_TYPE_PTR = 7,
} ImageEffect_DataType;

/**
 * @brief 数据值联合体。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef union ImageEffect_DataValue {
    /** 整形值，对应{@link EFFECT_DATA_TYPE_INT32}。 */
    int32_t int32Value;
    /** 单精度浮点值，对应{@link EFFECT_DATA_TYPE_FLOAT}。 */
    float floatValue;
    /** 双精度浮点值，对应{@link EFFECT_DATA_TYPE_DOUBLE}。 */
    double doubleValue;
    /** 字节值，对应{@link EFFECT_DATA_TYPE_CHAR}。 */
    char charValue;
    /** 长整型值，对应{@link EFFECT_DATA_TYPE_LONG}。 */
    long longValue;
    /** 布尔值，对应{@link EFFECT_DATA_TYPE_BOOL}。 */
    bool boolValue;
    /** 指针值，对应{@link EFFECT_DATA_TYPE_PTR}。 */
    void *ptrValue;
} ImageEffect_DataValue;

#ifdef __cplusplus
/**
 * @brief 参数结构体。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef struct ImageEffect_Any {
    /** 参数类型，默认为未定义类型。 */
    ImageEffect_DataType dataType = ImageEffect_DataType::EFFECT_DATA_TYPE_UNKNOWN;
    /** 参数值，默认为空。 */
    ImageEffect_DataValue dataValue = { 0 };
} ImageEffect_Any;
#else
/**
 * @brief 参数结构体。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef struct ImageEffect_Any {
    /** 参数类型。 */
    ImageEffect_DataType dataType;
    /** 参数值。 */
    ImageEffect_DataValue dataValue;
} ImageEffect_Any;
#endif

/**
 * @brief 像素格式枚举值。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef enum ImageEffect_Format {
    /** 未定义类型。 */
    EFFECT_PIXEL_FORMAT_UNKNOWN = 0,
    /** RGBA8888类型。 */
    EFFECT_PIXEL_FORMAT_RGBA8888 = 1,
    /** NV21类型。 */
    EFFECT_PIXEL_FORMAT_NV21 = 2,
    /** NV12类型。 */
    EFFECT_PIXEL_FORMAT_NV12 = 3,
    /** 10bit RGBA类型。 */
    EFFECT_PIXEL_FORMAT_RGBA1010102 = 4,
    /** 10bit YCBCR420类型。 */
    EFFECT_PIXEL_FORMAT_YCBCR_P010 = 5,
    /** 10bit YCRCB420类型。 */
    EFFECT_PIXEL_FORMAT_YCRCB_P010 = 6,
} ImageEffect_Format;

/**
 * @brief 内存类型枚举值。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef enum ImageEffect_BufferType {
    /** 未定义类型。 */
    EFFECT_BUFFER_TYPE_UNKNOWN = 0,
    /** 像素图类型。 */
    EFFECT_BUFFER_TYPE_PIXEL = 1,
    /** 纹理类型。 */
    EFFECT_BUFFER_TYPE_TEXTURE = 2,
} ImageEffect_BufferType;

/**
 * @brief 定义滤镜信息结构体。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef struct OH_EffectFilterInfo OH_EffectFilterInfo;

/**
 * @brief 创建OH_EffectFilterInfo实例，调用{@link OH_EffectFilterInfo_Release}进行资源释放。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @return 返回一个指向OH_EffectFilterInfo实例的指针，创建失败时返回空指针。
 * @since 12
 */
OH_EffectFilterInfo *OH_EffectFilterInfo_Create();

/**
 * @brief 设置滤镜名。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 滤镜信息指针。
 * @param name 滤镜名，例如：OH_EFFECT_BRIGHTNESS_FILTER。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectFilterInfo_SetFilterName(OH_EffectFilterInfo *info, const char *name);

/**
 * @brief 获取滤镜名。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 滤镜信息指针。
 * @param name 指向char数组的指针，返回滤镜名。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectFilterInfo_GetFilterName(OH_EffectFilterInfo *info, char **name);

/**
 * @brief 设置滤镜所支持的内存类型。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 滤镜信息指针。
 * @param size 滤镜所支持内存类型{@link ImageEffect_BufferType}个数。
 * @param bufferTypeArray 滤镜所支持内存类型{@link ImageEffect_BufferType}数组。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectFilterInfo_SetSupportedBufferTypes(OH_EffectFilterInfo *info, uint32_t size,
    ImageEffect_BufferType *bufferTypeArray);

/**
 * @brief 获取滤镜所支持的内存类型。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 滤镜信息指针。
 * @param size 滤镜所支持内存类型{@link ImageEffect_BufferType}个数。
 * @param bufferTypeArray 滤镜所支持内存类型{@link ImageEffect_BufferType}数组。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectFilterInfo_GetSupportedBufferTypes(OH_EffectFilterInfo *info, uint32_t *size,
    ImageEffect_BufferType **bufferTypeArray);

/**
 * @brief 设置滤镜所支持的像素格式。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 滤镜信息指针。
 * @param size 滤镜所支持像素格式{@link ImageEffect_Format}个数。
 * @param formatArray 滤镜所支持像素格式{@link ImageEffect_Format}数组。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectFilterInfo_SetSupportedFormats(OH_EffectFilterInfo *info, uint32_t size,
    ImageEffect_Format *formatArray);

/**
 * @brief 获取滤镜所支持的像素格式。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 滤镜信息指针。
 * @param size 滤镜所支持像素格式{@link ImageEffect_Format}个数。
 * @param formatArray 滤镜所支持像素格式{@link ImageEffect_Format}数组。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectFilterInfo_GetSupportedFormats(OH_EffectFilterInfo *info, uint32_t *size,
    ImageEffect_Format **formatArray);

/**
 * @brief 销毁OH_EffectFilterInfo实例。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 滤镜信息指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectFilterInfo_Release(OH_EffectFilterInfo *info);

#ifdef __cplusplus
/**
 * @brief 滤镜名信息。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef struct ImageEffect_FilterNames {
    /** 滤镜名个数。 */
    uint32_t size = 0;
    /** 滤镜名列表。 */
    const char **nameList = nullptr;
} ImageEffect_FilterNames;
#else
/**
 * @brief 滤镜名信息。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef struct ImageEffect_FilterNames {
    /** 滤镜名个数。 */
    uint32_t size;
    /** 滤镜名列表。 */
    const char **nameList;
} ImageEffect_FilterNames;
#endif

/**
 * @brief 定义图像信息。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef struct OH_EffectBufferInfo OH_EffectBufferInfo;

/**
 * @brief 创建OH_EffectBufferInfo实例，调用{@link OH_EffectBufferInfo_Release}进行资源释放。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @return 返回一个指向OH_EffectBufferInfo实例的指针，创建失败时返回空指针。
 * @since 12
 */
OH_EffectBufferInfo *OH_EffectBufferInfo_Create();

/**
 * @brief 设置图像内存地址。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 图像信息指针。
 * @param addr 图像虚拟内存地址。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_SetAddr(OH_EffectBufferInfo *info, void *addr);

/**
 * @brief 获取图像内存地址。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 图像信息指针。
 * @param addr 图像虚拟内存地址。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_GetAddr(OH_EffectBufferInfo *info, void **addr);

/**
 * @brief 设置图像宽度。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 图像信息指针。
 * @param width 图像宽度，单位：像素。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_SetWidth(OH_EffectBufferInfo *info, int32_t width);

/**
 * @brief 获取图像宽度。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 图像信息指针。
 * @param width 图像宽度，单位：像素。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_GetWidth(OH_EffectBufferInfo *info, int32_t *width);

/**
 * @brief 设置图像高度。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 图像信息指针。
 * @param height 图像高度，单位：像素。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_SetHeight(OH_EffectBufferInfo *info, int32_t height);

/**
 * @brief 获取图像高度。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 图像信息指针。
 * @param height 图像高度，单位：像素。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_GetHeight(OH_EffectBufferInfo *info, int32_t *height);

/**
 * @brief 设置图像每一行的字节数。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 图像信息指针。
 * @param rowSize 图像每一行的字节数，单位：字节。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_SetRowSize(OH_EffectBufferInfo *info, int32_t rowSize);

/**
 * @brief 获取图像每一行的字节数。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 图像信息指针。
 * @param rowSize 图像每一行的字节数，单位：字节。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_GetRowSize(OH_EffectBufferInfo *info, int32_t *rowSize);

/**
 * @brief 设置图像的像素格式。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 图像信息指针。
 * @param format 图像像素格式。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_SetEffectFormat(OH_EffectBufferInfo *info, ImageEffect_Format format);

/**
 * @brief 获取图像的像素格式。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 图像信息指针。
 * @param format 图像像素格式。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_GetEffectFormat(OH_EffectBufferInfo *info, ImageEffect_Format *format);

/**
 * @brief 设置OH_EffectBufferInfo的图像的textureId。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info OH_EffectBufferInfo结构体实例指针。
 * @param textureId 图像纹理标识。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：参数缺失。
 * @since 20
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_SetTextureId(OH_EffectBufferInfo *info, int32_t textureId);

/**
 * @brief 从OH_EffectBufferInfo中获取图像的textureId。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info OH_EffectBufferInfo结构体实例指针。
 * @param textureId 图像纹理标识。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：参数缺失。
 * @since 20
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_GetTextureId(OH_EffectBufferInfo *info, int32_t *textureId);

/**
 * @brief 销毁OH_EffectBufferInfo实例。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 图像信息指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_Release(OH_EffectBufferInfo *info);

/**
 * @brief 自定义滤镜设置参数的回调函数，用于开发者校验参数及参数值。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param filter 滤镜指针。
 * @param key 滤镜参数。
 * @param value 滤镜参数值。
 * @return 参数有效时返回true，否则返回false。
 * @since 12
 */
typedef bool (*OH_EffectFilterDelegate_SetValue)(OH_EffectFilter *filter, const char *key,
    const ImageEffect_Any *value);

/**
 * @brief 自定义滤镜传递图像信息到下一级滤镜的函数指针。需要在{@link OH_EffectFilterDelegate_Render}
 * 的回调中主动调用该函数指针。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param filter 滤镜指针。
 * @param info 图像信息OH_EffectBufferInfo指针。
 * @since 12
 */
typedef void (*OH_EffectFilterDelegate_PushData)(OH_EffectFilter *filter, OH_EffectBufferInfo *info);

/**
 * @brief 自定义滤镜渲染图像的回调函数。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param filter 滤镜指针。
 * @param info 图像信息OH_EffectBufferInfo指针。
 * @param pushData 自定义滤镜传递图像信息到下一级滤镜的函数指针OH_EffectFilterDelegate_PushData。
 * @return 执行成功时返回true，否则返回false。
 * @since 12
 */
typedef bool (*OH_EffectFilterDelegate_Render)(OH_EffectFilter *filter, OH_EffectBufferInfo *info,
    OH_EffectFilterDelegate_PushData pushData);

/**
 * @brief 自定义滤镜序列化的回调函数，按照JSON格式进行滤镜序列化处理。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param filter 滤镜指针。
 * @param info 指向char数组的指针，返回序列化JSON字符串。
 * @return 执行成功时返回true，否则返回false。
 * @since 12
 */
typedef bool (*OH_EffectFilterDelegate_Save)(OH_EffectFilter *filter, char **info);

/**
 * @brief 自定义滤镜反序列化的回调函数。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 序列化JSON字符串。
 * @return 执行成功时返回OH_EffectFilter实例，否则返回空指针。
 * @since 12
 */
typedef OH_EffectFilter *(*OH_EffectFilterDelegate_Restore)(const char *info);

/**
 * @brief 自定义滤镜回调函数结构体。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef struct ImageEffect_FilterDelegate {
    /** 参数设置函数指针。 */
    OH_EffectFilterDelegate_SetValue setValue;
    /** 滤镜渲染函数指针。 */
    OH_EffectFilterDelegate_Render render;
    /** 序列化效果器函数指针。 */
    OH_EffectFilterDelegate_Save save;
    /** 反序列化效果器函数指针。 */
    OH_EffectFilterDelegate_Restore restore;
} ImageEffect_FilterDelegate;

/**
 * @brief 图像区域结构体。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef struct ImageEffect_Region {
    /** X轴起始坐标。 */
    int32_t x0;
    /** Y轴起始坐标。 */
    int32_t y0;
    /** X轴终止坐标。 */
    int32_t x1;
    /** Y轴终止坐标。 */
    int32_t y1;
} ImageEffect_Region;

/**
 * @brief 图像尺寸结构体。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef struct ImageEffect_Size {
    /** 图像宽度，单位：像素。 */
    int32_t width;
    /** 图像高度，单位：像素。 */
    int32_t height;
} ImageEffect_Size;

/**
 * @brief 创建OH_EffectFilter实例，调用{@link OH_EffectFilter_Release}进行资源释放。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param name 滤镜名，例如：OH_EFFECT_BRIGHTNESS_FILTER。
 * @return 返回一个指向OH_EffectFilter实例的指针，创建失败时返回空指针。
 * @since 12
 */
OH_EffectFilter *OH_EffectFilter_Create(const char *name);

/**
 * @brief 设置滤镜参数。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param filter 滤镜指针。
 * @param key 滤镜参数，例如：OH_EFFECT_FILTER_INTENSITY_KEY。
 * @param value 滤镜参数值。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 *         EFFECT_KEY_ERROR：参数无效。
 *         EFFECT_PARAM_ERROR：参数值无效。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectFilter_SetValue(OH_EffectFilter *filter, const char *key, const ImageEffect_Any *value);

/**
 * @brief 获取滤镜参数。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param filter 滤镜指针。
 * @param key 滤镜参数，例如：OH_EFFECT_FILTER_INTENSITY_KEY。
 * @param value 滤镜参数值。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 *         EFFECT_KEY_ERROR：参数无效。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectFilter_GetValue(OH_EffectFilter *filter, const char *key, ImageEffect_Any *value);

/**
 * @brief 注册自定义滤镜。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 滤镜信息指针OH_EffectFilterInfo。
 * @param delegate 自定义滤镜回调函数ImageEffect_FilterDelegate。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectFilter_Register(const OH_EffectFilterInfo *info,
    const ImageEffect_FilterDelegate *delegate);

/**
 * @brief 查询满足条件的滤镜。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param key 查询条件，可根据“Default”关键词查询所有的滤镜。
 * @return 滤镜名列表。
 * @since 12
 */
ImageEffect_FilterNames *OH_EffectFilter_LookupFilters(const char *key);

/**
 * @brief 释放滤镜名内存资源。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
void OH_EffectFilter_ReleaseFilterNames();

/**
 * @brief 查询滤镜信息。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param name 滤镜名。
 * @param info 滤镜信息指针OH_EffectFilterInfo。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针或其他无效值。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectFilter_LookupFilterInfo(const char *name, OH_EffectFilterInfo *info);

/**
 * @brief 执行图像渲染。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param filter 滤镜指针。
 * @param inputPixelmap 输入图像。
 * @param outputPixelmap 输出图像。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectFilter_Render(OH_EffectFilter *filter, OH_PixelmapNative *inputPixelmap,
    OH_PixelmapNative *outputPixelmap);

/**
 * @brief 使用纹理标识渲染滤镜效果。该函数不支持相同的输入和输出图像。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param filter OH_EffectFilter结构体实例指针。
 * @param inputTextureId 输入纹理标识。输入的纹理标识必须是有效的且绑定了GL_TEXTURE_2D类型的纹理。
 * @param outputTextureId 输出纹理标识，输入纹理标识必须是一个有效的纹理。
 *        如果纹理标识未被绑定纹理图片，纹理标识会自动绑定GL_TEXTURE_2D类型；
 *        如果纹理标识已经被绑定纹理且尺寸不合适，结果可能会被裁剪或部分填充到此纹理上。
 * @param colorSpace 图片对应的色彩空间。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：参数缺失。
 * @since 20
 */
ImageEffect_ErrorCode OH_EffectFilter_RenderWithTextureId(OH_EffectFilter *filter, int32_t inputTextureId,
    int32_t outputTextureId, int32_t colorSpace);

/**
 * @brief 销毁OH_EffectFilter实例。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param filter 滤镜指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectFilter_Release(OH_EffectFilter *filter);

/**
 * @brief 设置滤镜时间戳。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 图像信息指针。
 * @param timestamp 图像帧数据的时间戳。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_SetTimestamp(OH_EffectBufferInfo *info, int64_t timestamp);

/**
 * @brief 获取滤镜时间戳。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 图像信息指针。
 * @param timestamp 图像帧数据的时间戳。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_EffectBufferInfo_GetTimestamp(OH_EffectBufferInfo *info, int64_t *timestamp);

#ifdef __cplusplus
}
#endif
#endif // NATIVE_IMAGE_EFFECT_FILTER_H
/** @} */
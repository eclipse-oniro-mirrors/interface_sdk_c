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
 * @addtogroup Image_NativeModule
 * @{
 *
 * @brief 提供图片处理的相关能力，包括图片编解码、从Native层获取图片数据等。\n
 *
 * 使用该模块的接口，无需通过JS接口导入，可直接使用NDK完成功能开发。
 * @since 12
 */

/**
 * @file pixelmap_native.h
 *
 * @brief 访问Pixelmap的API。提供对Pixelmap（像素图）的访问能力，支持通过像素数据、Surface、NativeBuffer等多种方式创建像素图、
 * 克隆像素图、读写像素数据，以及进行缩放、旋转、翻转、平移、裁剪等图像变换操作，同时支持HDR元数据管理、色彩空间设置、
 * 透明度类型转换、Native与Napi对象互转和内存直接访问等功能，适用于需要在Native层对解码后的图像位图进行像素级处理与变换的场景。
 *
 * @library libpixelmap.so
 * @kit ImageKit
 * @include <multimedia/image_framework/image/pixelmap_native.h>
 * @Syscap SystemCapability.Multimedia.Image.Core
 * @since 12
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PIXELMAP_NATIVE_H_
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PIXELMAP_NATIVE_H_
#include "image_common.h"
#include "napi/native_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief OH_PixelmapNative结构体是Native层封装的图像解码后无压缩的位图格式结构体。
 * <br>创建OH_PixelmapNative使用{@link OH_PixelmapNative_CreatePixelmap}函数，默认采用BGRA_8888格式处理数据。
 * <br>释放OH_PixelmapNative对象使用{@link OH_PixelmapNative_Release}函数。
 *
 * @since 12
 */
struct OH_PixelmapNative;
typedef struct OH_PixelmapNative OH_PixelmapNative;

/**
 * @brief NativeBuffer结构体类型，用于执行NativeBuffer相关操作。
 *
 * @since 12
 */
struct OH_NativeBuffer;
typedef struct OH_NativeBuffer OH_NativeBuffer;

/**
 * @brief NativeColorSpaceManager结构体类型，用于执行NativeColorSpaceManager相关操作。
 *
 * @since 13
 */
typedef struct OH_NativeColorSpaceManager OH_NativeColorSpaceManager;

/**
 * @brief Pixelmap透明度类型。
 *
 * @since 12
 */
typedef enum {
    /**
     * 未知格式。
     */
    PIXELMAP_ALPHA_TYPE_UNKNOWN = 0,
    /**
     * 不透明的格式。
     */
    PIXELMAP_ALPHA_TYPE_OPAQUE = 1,
    /**
     * 预乘透明度格式。
     */
    PIXELMAP_ALPHA_TYPE_PREMULTIPLIED = 2,
    /**
     * 非预乘透明度格式。
     */
    PIXELMAP_ALPHA_TYPE_UNPREMULTIPLIED = 3,
} PIXELMAP_ALPHA_TYPE;

/**
 * @brief 图像的像素格式，包含像素数据的颜色通道排列和位深信息。
 *
 * @since 12
 */
typedef enum {
    /**
     * 未知格式。
     */
    PIXEL_FORMAT_UNKNOWN = 0,
    /**
     * RGB_565格式。
     */
    PIXEL_FORMAT_RGB_565 = 2,
    /**
     * RGBA_8888格式。
     */
    PIXEL_FORMAT_RGBA_8888 = 3,
    /**
     * BGRA_8888格式。
     */
    PIXEL_FORMAT_BGRA_8888 = 4,
    /**
     * RGB_888格式。
     */
    PIXEL_FORMAT_RGB_888 = 5,
    /**
     * ALPHA_8格式。
     */
    PIXEL_FORMAT_ALPHA_8 = 6,
    /**
     * RGBA_F16格式。
     */
    PIXEL_FORMAT_RGBA_F16 = 7,
    /**
     * NV21格式。
     */
    PIXEL_FORMAT_NV21 = 8,
    /**
     * NV12格式。
     */
    PIXEL_FORMAT_NV12 = 9,
    /**
     * RGBA_1010102格式。
     */
    PIXEL_FORMAT_RGBA_1010102 = 10,
    /**
     * YCBCR_P010格式。
     */
    PIXEL_FORMAT_YCBCR_P010 = 11,
    /**
     * YCRCB_P010格式。
     */
    PIXEL_FORMAT_YCRCB_P010 = 12,
    /**
     * ALPHA_U8格式。
     * @since 26.0.0
     */
    PIXEL_FORMAT_ALPHA_U8 = 15,
    /**
     * ALPHA_F16格式。
     * @since 26.0.0
     */
    PIXEL_FORMAT_ALPHA_F16 = 16,
} PIXEL_FORMAT;

/**
 * @brief Pixelmap缩放时采用的缩放算法。
 *
 * @since 12
 */
typedef enum {
    /**
     * 最近邻插值算法。
     * 速度最快，放大时会有明显的马赛克/锯齿感，适合对性能要求高、对画质要求低的快速缩放场景。
     */
    OH_PixelmapNative_AntiAliasing_NONE = 0,
    /**
     * 双线性插值算法。
     * 适合一般缩放场景。
     */
    OH_PixelmapNative_AntiAliasing_LOW = 1,
    /**
     * 双线性插值算法，同时开启Mipmap。
     * 适合缩小图片的场景，能极好地消除大幅缩小时的混叠与纹理闪烁。
     */
    OH_PixelmapNative_AntiAliasing_MEDIUM = 2,
    /**
     * 三次卷积插值算法。
     * 适合对画质要求较高的放大场景。
     */
    OH_PixelmapNative_AntiAliasing_HIGH = 3,
} OH_PixelmapNative_AntiAliasingLevel;

/**
 * @brief Pixelmap使用的HDR相关元数据信息的关键字，用于{@link OH_PixelmapNative_SetMetadata}及{@link OH_PixelmapNative_GetMetadata}。
 *
 * @since 12
 */
typedef enum {
    /**
     * Pixelmap使用的元数据类型。
     */
    HDR_METADATA_TYPE = 0,
    /**
     * 静态元数据。
     */
    HDR_STATIC_METADATA = 1,
    /**
     * 动态元数据。
     */
    HDR_DYNAMIC_METADATA = 2,
    /**
     * 增益图使用的元数据。
     */
    HDR_GAINMAP_METADATA = 3,
} OH_Pixelmap_HdrMetadataKey;

/**
 * @brief HDR_METADATA_TYPE关键字对应的值。
 *
 * @since 12
 */
typedef enum {
    /**
     * 无元数据内容。
     */
    HDR_METADATA_TYPE_NONE = 0,
    /**
     * 表示用于基础图的元数据。
     */
    HDR_METADATA_TYPE_BASE = 1,
    /**
     * 表示用于Gainmap图的元数据。
     */
    HDR_METADATA_TYPE_GAINMAP = 2,
    /**
     * 表示用于合成后HDR图的元数据。
     */
    HDR_METADATA_TYPE_ALTERNATE = 3,
} OH_Pixelmap_HdrMetadataType;

/**
 * @brief 表示HDR_STATIC_METADATA关键字对应的静态元数据值，用于描述HDR显示设备的能力信息及内容亮度特征
 * （如三基色坐标、白点坐标、最值亮度、内容最大亮度等），在调用{@link OH_PixelmapNative_SetMetadata}和
 * {@link OH_PixelmapNative_GetMetadata}时作为{@link OH_Pixelmap_HdrMetadataValue}的成员使用。
 *
 * @since 12
 */
typedef struct OH_Pixelmap_HdrStaticMetadata {
    /**
     * 归一化后显示设备三基色的X坐标。数组的长度为3，按R、G、B顺序存储，以0.00002为单位，取值范围是[0.0, 0.99998]。
     */
    float displayPrimariesX[3];
    /**
     * 归一化后显示设备三基色的Y坐标。数组的长度为3，按R、G、B顺序存储，以0.00002为单位，取值范围是[0.0, 0.99998]。
     */
    float displayPrimariesY[3];
    /**
     * 归一化后白点值的X坐标。以0.00002为单位，取值范围是[0.0, 0.99998]。
     */
    float whitePointX;
    /**
     * 归一化后白点值的Y坐标。以0.00002为单位，取值范围是[0.0, 0.99998]。
     */
    float whitePointY;
    /**
     * 图像主监视器的最大亮度。以1为单位，取值范围是[0, 65535]。单位：尼特（nit）。
     */
    float maxLuminance;
    /**
     * 图像主监视器的最小亮度。以0.0001为单位，取值范围是[0, 6.5535]。单位：尼特（nit）。
     */
    float minLuminance;
    /**
     * 显示内容的最大亮度。以1为单位，取值范围是[0, 65535]。单位：尼特（nit）。
     */
    float maxContentLightLevel;
    /**
     * 显示内容的最大平均亮度。以1为单位，取值范围是[0, 65535]。单位：尼特（nit）。
     */
    float maxFrameAverageLightLevel;
} OH_Pixelmap_HdrStaticMetadata;

/**
 * @brief 表示HDR_DYNAMIC_METADATA关键字对应的动态元数据值，用于存储HDR图像的动态元数据。
 * HDR动态元数据可用于在显示过程中动态调整HDR图像的显示参数，以适配不同显示设备的能力，获得更准确的HDR显示效果。
 * 在调用{@link OH_PixelmapNative_SetMetadata}和{@link OH_PixelmapNative_GetMetadata}时作为
 * {@link OH_Pixelmap_HdrMetadataValue}的成员使用。
 *
 * @since 12
 */
typedef struct OH_Pixelmap_HdrDynamicMetadata {
    /**
     * 动态元数据值的指针，指向存储动态元数据的二进制数据缓冲区，缓冲区长度由length成员指定。
     */
    uint8_t *data;
    /**
     * 动态元数据值的长度，单位：字节（Byte），取值需与data指向的数据缓冲区实际长度一致。
     */
    uint32_t length;
} OH_Pixelmap_HdrDynamicMetadata;

/**
 * @brief 表示HDR_GAINMAP_METADATA关键字对应的增益图相关元数据值，参考ISO 21496-1。
 * 用于描述HDR增益图的版本、通道数、提亮比、偏移量及各通道增益曲线等参数，在调用{@link OH_PixelmapNative_SetMetadata}和
 * {@link OH_PixelmapNative_GetMetadata}时作为{@link OH_Pixelmap_HdrMetadataValue}的成员使用，
 * 适用于HDR图像增益映射元数据的设置与获取场景。
 *
 * @since 12
 */
typedef struct OH_Pixelmap_HdrGainmapMetadata {
    /**
     * 元数据编写器的版本。
     */
    uint16_t writerVersion;
    /**
     * 元数据解析所需的最小版本。
     */
    uint16_t miniVersion;
    /**
     * 增益图的颜色通道数。取值为1或3，值为3时RGB通道的元数据值不同，值为1时各通道元数据值相同，参考ISO 21496-1。
     */
    uint8_t gainmapChannelNum;
    /**
     * 是否使用基础图的色彩空间。true表示使用，false表示不使用，参考ISO 21496-1。
     */
    bool useBaseColorFlag;
    /**
     * 基础图的提亮比。取值范围是[1.0, +∞)，参考ISO 21496-1。
     */
    float baseHeadroom;
    /**
     * 可选择图像的提亮比。取值范围是[1.0, +∞)，参考ISO 21496-1。
     */
    float alternateHeadroom;
    /**
     * 增益图的最大值。按R、G、B三通道存储，取值范围是(0, +∞)且必须大于gainmapMin的对应通道，参考ISO 21496-1。
     */
    float gainmapMax[3];
    /**
     * 增益图的最小值。按R、G、B三通道存储，取值可以为0或负值但必须小于gainmapMax的对应通道，参考ISO 21496-1。
     */
    float gainmapMin[3];
    /**
     * 增益曲线的Gamma校正值。按R、G、B三通道存储，取值范围是(0, +∞)，参考ISO 21496-1。
     */
    float gamma[3];
    /**
     * 基础图的偏移量。按R、G、B三通道存储，参考ISO 21496-1。
     */
    float baselineOffset[3];
    /**
     * 可选择图像的偏移量。按R、G、B三通道存储，参考ISO 21496-1。
     */
    float alternateOffset[3];
} OH_Pixelmap_HdrGainmapMetadata;

/**
 * @brief Pixelmap使用的HDR元数据值，和OH_Pixelmap_HdrMetadataKey相对应。当传入相应的{@link OH_Pixelmap_HdrMetadataKey}中的关键字作为入参时，
 * 可通过本结构体设置或获取对应类型的元数据值。该结构体用于{@link OH_PixelmapNative_SetMetadata}及{@link OH_PixelmapNative_GetMetadata}接口，
 * 适用于需要对HDR图像进行元数据管理与渲染处理的场景，帮助应用正确设置和获取HDR元数据以实现HDR图像的高动态范围显示效果。
 *
 * @since 12
 */
typedef struct OH_Pixelmap_HdrMetadataValue {
    /**
     * {@link OH_Pixelmap_HdrMetadataKey}中HDR_METADATA_TYPE关键字对应的HDR元数据值类型，用于表示HDR元数据的类型。
     * 不同取值对应不同类型的HDR元数据，需根据HDR图像的实际元数据类型选择合适的值，并填充对应类型的元数据成员字段。
     */
    OH_Pixelmap_HdrMetadataType type;
    /**
     * {@link OH_Pixelmap_HdrMetadataKey}中HDR_STATIC_METADATA关键字对应的元数据值类型，用于存储HDR静态元数据。
     */
    OH_Pixelmap_HdrStaticMetadata staticMetadata;
    /**
     * {@link OH_Pixelmap_HdrMetadataKey}中HDR_DYNAMIC_METADATA关键字对应的元数据值类型，用于存储HDR动态元数据，
     * 格式遵循相关HDR动态元数据标准。
     */
    OH_Pixelmap_HdrDynamicMetadata dynamicMetadata;
    /**
     * {@link OH_Pixelmap_HdrMetadataKey}中HDR_GAINMAP_METADATA关键字对应的元数据值类型，用于存储HDR增益图元数据，
     * 参考ISO 21496-1。
     */
    OH_Pixelmap_HdrGainmapMetadata gainmapMetadata;
} OH_Pixelmap_HdrMetadataValue;

/**
 * @brief OH_Pixelmap_InitializationOptions是Native层封装的初始化选项结构体，用于在创建Pixelmap时指定其属性，
 * 可配置图片宽高、像素格式、透明度类型等参数，适用于需要在Native层创建Pixelmap并自定义其初始化属性的场景。
 * <br>使用{@link OH_PixelmapInitializationOptions_Create}函数创建OH_Pixelmap_InitializationOptions对象；
 * 使用完成后需调用{@link OH_PixelmapInitializationOptions_Release}函数释放资源，两者需配对使用，否则会导致内存泄漏。
 *
 * @since 12
 */
struct OH_Pixelmap_InitializationOptions;
typedef struct OH_Pixelmap_InitializationOptions OH_Pixelmap_InitializationOptions;

/**
 * @brief 创建OH_Pixelmap_InitializationOptions指针。
 *
 * @param options 被创建的OH_Pixelmap_InitializationOptions指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_Create(OH_Pixelmap_InitializationOptions **options);

/**
 * @brief 获取图片宽。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param width 图片的宽，单位：像素（px）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_GetWidth(OH_Pixelmap_InitializationOptions *options,
    uint32_t *width);

/**
 * @brief 设置图片宽。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param width 图片的宽，单位：像素（px）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_SetWidth(OH_Pixelmap_InitializationOptions *options,
    uint32_t width);

/**
 * @brief 获取图片高。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param height 图片的高，单位：像素（px）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_GetHeight(OH_Pixelmap_InitializationOptions *options,
    uint32_t *height);

/**
 * @brief 设置图片高。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param height 图片的高，单位：像素（px）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_SetHeight(OH_Pixelmap_InitializationOptions *options,
    uint32_t height);

/**
 * @brief 获取像素格式。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param pixelFormat 像素格式{@link PIXEL_FORMAT}。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_GetPixelFormat(OH_Pixelmap_InitializationOptions *options,
    int32_t *pixelFormat);

/**
 * @brief 设置像素格式。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param pixelFormat 像素格式{@link PIXEL_FORMAT}。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_SetPixelFormat(OH_Pixelmap_InitializationOptions *options,
    int32_t pixelFormat);

/**
 * @brief 获取源像素格式（创建Pixelmap时输入数据的像素格式）。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param srcpixelFormat 像素格式{@link PIXEL_FORMAT}。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_GetSrcPixelFormat(OH_Pixelmap_InitializationOptions *options,
    int32_t *srcpixelFormat);

/**
 * @brief 设置源像素格式（创建Pixelmap时输入数据的像素格式）。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param srcpixelFormat 源像素格式{@link PIXEL_FORMAT}。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_SetSrcPixelFormat(OH_Pixelmap_InitializationOptions *options,
    int32_t srcpixelFormat);

/**
 * @brief 获取行跨距。
 * <br>跨距，图像每行像素占用的真实内存大小。单位：字节（Byte）。
 * 跨距 = 图像宽度 \* 每像素字节数 + 填充（padding），填充是每行像素的末尾为内存对齐所增加的空白区域。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param rowStride 跨距，单位：字节（Byte）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNKNOWN_ERROR：options被释放。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_GetRowStride(OH_Pixelmap_InitializationOptions *options,
    int32_t *rowStride);

/**
 * @brief 设置行跨距。
 * <br>跨距，图像每行像素占用的真实内存大小。单位：字节（Byte）。
 * 跨距 = 图像宽度 \* 每像素字节数 + 填充（padding），填充是每行像素的末尾为内存对齐所增加的空白区域。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param rowStride 跨距，单位：字节（Byte）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNKNOWN_ERROR：options被释放。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_SetRowStride(OH_Pixelmap_InitializationOptions *options,
    int32_t rowStride);

/**
 * @brief 获取透明度类型。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param alphaType 透明度类型{@link PIXELMAP_ALPHA_TYPE}。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_GetAlphaType(OH_Pixelmap_InitializationOptions *options,
    int32_t *alphaType);

/**
 * @brief 设置透明度类型。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param alphaType 透明度类型{@link PIXELMAP_ALPHA_TYPE}。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_SetAlphaType(OH_Pixelmap_InitializationOptions *options,
    int32_t alphaType);

/**
 * @brief 获取可编辑标志。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param editable 可编辑标志。true表示可编辑，false表示不可编辑。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PixelmapInitializationOptions_GetEditable(OH_Pixelmap_InitializationOptions *options,
    bool *editable);

/**
 * @brief 设置可编辑标志。
 *
 * @param options 被操作的OH_Pixelmap_InitializationOptions指针。
 * @param editable 可编辑标志。true表示可编辑，false表示不可编辑。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PixelmapInitializationOptions_SetEditable(OH_Pixelmap_InitializationOptions *options,
    bool editable);

/**
 * @brief 释放OH_Pixelmap_InitializationOptions指针。
 *
 * @param options 被释放的OH_Pixelmap_InitializationOptions指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapInitializationOptions_Release(OH_Pixelmap_InitializationOptions *options);

/**
 * @brief OH_Pixelmap_ImageInfo是Native层封装的图像像素信息结构体，保存图像像素的宽高、行跨距、像素格式、透明度类型、
 * 是否为HDR等信息，适用于在Native层查询Pixelmap属性的场景。
 * <br>创建OH_Pixelmap_ImageInfo对象使用{@link OH_PixelmapImageInfo_Create}函数，
 * 使用完成后需调用{@link OH_PixelmapImageInfo_Release}函数释放资源，两者需配对使用，否则会导致内存泄漏。
 * <br>OH_Pixelmap_ImageInfo结构体内容和操作方式如下：
 *
 * @since 12
 */
struct OH_Pixelmap_ImageInfo;
typedef struct OH_Pixelmap_ImageInfo OH_Pixelmap_ImageInfo;

/**
 * @brief 创建OH_Pixelmap_ImageInfo指针。
 *
 * @param info 被创建的OH_Pixelmap_ImageInfo指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapImageInfo_Create(OH_Pixelmap_ImageInfo **info);

/**
 * @brief 获取图片宽。
 *
 * @param info 被操作的OH_Pixelmap_ImageInfo指针。
 * @param width 图片宽，单位：像素（px）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapImageInfo_GetWidth(OH_Pixelmap_ImageInfo *info, uint32_t *width);

/**
 * @brief 获取图片高。
 *
 * @param info 被操作的OH_Pixelmap_ImageInfo指针。
 * @param height 图片高，单位：像素（px）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapImageInfo_GetHeight(OH_Pixelmap_ImageInfo *info, uint32_t *height);

/**
 * @brief 获取图片透明通道类型。
 *
 * @param info 被操作的OH_Pixelmap_ImageInfo指针。
 * @param alphaMode 获取的透明通道类型。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 20
 */
Image_ErrorCode OH_PixelmapImageInfo_GetAlphaMode(OH_Pixelmap_ImageInfo *info, int32_t *alphaMode);

/**
 * @brief 获取行跨距。
 *
 * @param info 被操作的OH_Pixelmap_ImageInfo指针。
 * @param rowStride 跨距，内存中每行像素所占的空间。单位：字节（Byte）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapImageInfo_GetRowStride(OH_Pixelmap_ImageInfo *info, uint32_t *rowStride);

/**
 * @brief 获取像素格式。
 *
 * @param info 被操作的OH_Pixelmap_ImageInfo指针。
 * @param pixelFormat 像素格式{@link PIXEL_FORMAT}。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapImageInfo_GetPixelFormat(OH_Pixelmap_ImageInfo *info, int32_t *pixelFormat);

/**
 * @brief 获取OH_PixelmapImageInfo默认的透明度类型。若要获取图片当前透明度类型，请使用{@link OH_PixelmapImageInfo_GetAlphaMode}。
 *
 * @param info 被操作的OH_Pixelmap_ImageInfo指针。
 * @param alphaType 透明度类型{@link PIXELMAP_ALPHA_TYPE}。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapImageInfo_GetAlphaType(OH_Pixelmap_ImageInfo *info, int32_t *alphaType);

/**
 * @brief 获取Pixelmap是否为高动态范围的信息。
 *
 * @param info 被操作的OH_Pixelmap_ImageInfo指针。
 * @param isHdr 表示是否为高动态范围（HDR）的信息。true表示是高动态范围的信息，false表示不是高动态范围的信息。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数校验错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapImageInfo_GetDynamicRange(OH_Pixelmap_ImageInfo *info, bool *isHdr);

/**
 * @brief 释放OH_Pixelmap_ImageInfo指针。
 *
 * @param info 被释放的OH_Pixelmap_ImageInfo指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapImageInfo_Release(OH_Pixelmap_ImageInfo *info);

/**
 * @brief 通过像素数据和图像属性创建Pixelmap。
 * <br>此接口不支持创建以下像素格式的Pixelmap：PIXEL_FORMAT_RGBA_1010102、PIXEL_FORMAT_YCBCR_P010和PIXEL_FORMAT_YCRCB_P010。
 *
 * @param data 像素数据的数组。
 *     传入的像素数据默认按BGRA_8888格式解析，如果需要设置为其他格式，请参考{@link OH_PixelmapInitializationOptions_SetSrcPixelFormat}。
 *     如果像素数据中含有用于内存对齐的行末填充字节，则必须使用{@link OH_PixelmapInitializationOptions_SetRowStride}设置行跨距。
 * @param dataLength 像素数组的长度。单位：字节（Byte）。
 * @param options 创建图像的初始化属性。
 * @param pixelmap 被创建的OH_PixelmapNative对象指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：操作不支持。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_CreatePixelmap(uint8_t *data, size_t dataLength,
    OH_Pixelmap_InitializationOptions *options, OH_PixelmapNative **pixelmap);

/**
 * @brief 通过像素数据和图像属性创建Pixelmap，可以通过allocator指定内存类型。
 * <br>默认情况下，系统会根据图像类型、图像大小、平台能力等选择内存类型。
 * <br>在处理此接口返回的像素图时，需要考虑行跨距的影响。行跨距即图像每行占用的真实内存大小，可能因内存对齐而大于图像宽度乘以单位像素字节数，
 * 请参考{@link OH_PixelmapInitializationOptions_GetRowStride}获取详细说明。
 *
 * @param data 像素数据的数组。
 *     传入的像素数据默认按BGRA_8888格式解析，如果需要设置为其他格式，请参考{@link OH_PixelmapInitializationOptions_SetSrcPixelFormat}。
 *     如果像素数据中含有用于内存对齐的行末填充字节，则必须使用{@link OH_PixelmapInitializationOptions_SetRowStride}设置行跨距。
 * @param dataLength 像素数组的长度。单位：字节（Byte）。
 * @param options 创建图像的初始化属性。
 * @param allocator 决定Pixelmap内存分配的类型。
 * @param pixelmap 被创建的OH_PixelmapNative对象指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：操作不支持。
 *     <br>IMAGE_TOO_LARGE：图像过大，无法分配内存。
 *     <br>IMAGE_DMA_OPERATION_FAILED：DMA内存操作失败。
 *     <br>IMAGE_ALLOCATOR_MODE_UNSUPPORTED：不支持分配当前内存类型。例如，使用共享内存创建HDR图。
 * @since 20
 */
Image_ErrorCode OH_PixelmapNative_CreatePixelmapUsingAllocator(uint8_t *data, size_t dataLength,
    OH_Pixelmap_InitializationOptions *options, IMAGE_ALLOCATOR_MODE allocator, OH_PixelmapNative **pixelmap);

/**
 * @brief 将OH_PixelmapNative对象转换为PixelmapNapi对象。
 *
 * @param env Napi的环境指针。
 * @param pixelmapNative 被操作的OH_PixelmapNative指针。
 * @param pixelmapNapi 转换出来的PixelmapNapi对象指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：pixelmapNative为空。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_ConvertPixelmapNativeToNapi(napi_env env, OH_PixelmapNative *pixelmapNative,
    napi_value *pixelmapNapi);

/**
 * @brief 将PixelmapNapi对象转换为OH_PixelmapNative对象。
 *
 * @param env Napi的环境指针。
 * @param pixelmapNapi 需要转换的PixelmapNapi对象。
 * @param pixelmapNative 转换出的OH_PixelmapNative对象指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：pixelmapNative是nullptr，或者pixelmapNapi不是PixelmapNapi对象。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_ConvertPixelmapNativeFromNapi(napi_env env, napi_value pixelmapNapi,
    OH_PixelmapNative **pixelmapNative);

/**
 * @brief 读取图像像素数据，并按照Pixelmap的像素格式存入缓冲区中。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针。
 * @param destination 目标缓冲区，获取的像素数据会被拷贝至该缓冲区。缓冲区内像素的格式与PixelMap相同，不包含内存对齐填充字节。
 * @param bufferSize 缓冲区大小。单位：字节（Byte）。可通过{@link OH_PixelmapNative_GetByteCount}接口获取。
 *     RGBA格式的缓冲区大小等于width \* height \* 4，
 *     NV21与NV12格式的缓冲区大小等于width \* height + ((width+1)/2) \* ((height+1)/2) \* 2。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNKNOWN_ERROR：未知错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_ReadPixels(OH_PixelmapNative *pixelmap, uint8_t *destination, size_t *bufferSize);

/**
 * @brief 将缓冲区中的图像像素数据按照Pixelmap的像素格式写入Pixelmap。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针。
 * @param source 源数据缓冲区，该缓冲区内的图像像素数据会被写入Pixelmap。缓冲区内的像素数据必须是整个Pixelmap的像素数据，
 *     且像素格式需与Pixelmap相同，不包含内存对齐填充字节。
 * @param bufferSize 缓冲区大小。单位：字节（Byte）。可通过{@link OH_PixelmapNative_GetByteCount}接口获取。
 *     RGBA格式的缓冲区大小等于width \* height \* 4，
 *     NV21与NV12格式的缓冲区大小等于width \* height + ((width+1)/2) \* ((height+1)/2) \* 2。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：操作不支持。
 *     <br>IMAGE_UNKNOWN_ERROR：未知错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_WritePixels(OH_PixelmapNative *pixelmap, uint8_t *source, size_t bufferSize);

/**
 * @brief 从Pixelmap的指定区域中读取像素数据并存入缓冲区。如果Pixelmap的像素格式为YUV类型，则会按照Pixelmap的像素格式存入缓冲区，
 * 否则会按照BGRA_8888格式存入缓冲区。
 *
 * @param pixelmap 被读取的Pixelmap。
 * @param area 读取数据的Pixelmap指定区域，该区域的像素数据会被读取并拷贝至area->pixels。
 *     如果PixelMap的像素格式为YUV类型，则获取的像素数据格式与Pixelmap相同，否则会被转换为BGRA_8888格式。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_BAD_PARAMETER：参数无效，例如：pixelmap或area有误。
 *     <br>IMAGE_UNKNOWN_ERROR：未知的内部错误，例如：不支持的像素格式。
 * @since 22
 */
Image_ErrorCode OH_PixelmapNative_ReadPixelsFromArea(OH_PixelmapNative *pixelmap, Image_PositionArea *area);

/**
 * @brief 将缓冲区中的像素数据写入Pixelmap的指定区域。如果Pixelmap的像素格式为YUV类型，则数据源的格式需与Pixelmap相同，
 * 否则数据源需要为BGRA_8888格式。
 *
 * @param pixelmap 被写入的Pixelmap。
 * @param area 写入数据的Pixelmap指定区域，area->pixels中的像素数据会被写入Pixelmap的该区域。
 *     如果PixelMap的像素格式为YUV类型，则area->pixels中的像素数据格式需与PixelMap相同，否则需要为BGRA_8888格式。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_BAD_PARAMETER：参数无效，例如：pixelmap或area有误。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：Pixelmap不可编辑。
 *     <br>IMAGE_UNKNOWN_ERROR：未知的内部错误，例如：不支持的像素格式。
 * @since 22
 */
Image_ErrorCode OH_PixelmapNative_WritePixelsToArea(OH_PixelmapNative *pixelmap, Image_PositionArea *area);

/**
 * @brief 从Pixelmap中读取ARGB格式的数据。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针。
 * @param destination 缓冲区，获取的图像像素数据写入到该内存区域内。缓冲区大小应不小于width * height * 4字节。
 * @param bufferSize 缓冲区大小。单位：字节（Byte）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_CONVERSION：Pixelmap格式不支持读取ARGB数据。
 *     <br>IMAGE_ALLOC_FAILED：内存申请失败。
 *     <br>IMAGE_COPY_FAILED：内存数据拷贝、读取、操作失败。
 * @since 13
 */
Image_ErrorCode OH_PixelmapNative_GetArgbPixels(OH_PixelmapNative *pixelmap, uint8_t *destination, size_t *bufferSize);

/**
 * @brief 将HDR的图像内容转换为SDR的图像内容。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：操作不支持。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_ToSdr(OH_PixelmapNative *pixelmap);

/**
 * @brief 获取图像像素信息。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针。
 * @param imageInfo 图像像素信息。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_GetImageInfo(OH_PixelmapNative *pixelmap, OH_Pixelmap_ImageInfo *imageInfo);

/**
 * @brief 设置Pixelmap的不透明度。指定的不透明度值将被应用于所有像素。
 *
 * @param pixelmap 被操作的OH_PixelmapNative的指针。
 * @param value 指定的不透明度值。取值范围是(0.0, 1.0]，1.0表示完全不透明，数值越接近0.0则透明度越高。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_GET_IMAGE_DATA_FAILED：获取图像数据失败。可能的原因：内部数据损坏。详情请检查日志。
 *     <br>IMAGE_PIXELMAP_RELEASED：Pixelmap已被释放。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：Pixelmap被锁定，不支持该操作。
 *     <br>IMAGE_INVALID_PARAMETER：无效参数。可能的原因：1. 不透明度值超出范围。2. 入参为空。
 *     <br>IMAGE_UNSUPPORTED_DATA_FORMAT：不支持的数据格式。可能的原因：透明度类型不支持。
 * @since 26.0.0
 */
Image_ErrorCode OH_PixelmapNative_SetOpacity(OH_PixelmapNative *pixelmap, float value);

/**
 * @brief 设置Pixelmap的不透明度。指定的不透明度值将被应用于所有像素。
 * <br>从API版本26.0.0开始，建议使用{@link OH_PixelmapNative_SetOpacity}代替，以获得更完善的异常报错信息。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针。
 * @param rate 不透明度的值。取值范围是(0.0, 1.0]，1.0表示完全不透明，数值越接近0.0则透明度越高。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_Opacity(OH_PixelmapNative *pixelmap, float rate);

/**
 * @brief 根据指定的宽高缩放倍数对Pixelmap进行水平或垂直方向的缩放。
 *
 * @param pixelmap 被缩放的OH_PixelmapNative的指针。
 * @param scaleX 宽度的缩放倍数。
 *     取值不能为0，建议取正数，否则会产生翻转效果。
 * @param scaleY 高度的缩放倍数。
 *     取值不能为0，建议取正数，否则会产生翻转效果。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_GET_IMAGE_DATA_FAILED：获取图像数据失败。可能的原因：内部数据损坏。详情请检查日志。
 *     <br>IMAGE_PIXELMAP_RELEASED：Pixelmap已被释放。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：Pixelmap被锁定，不支持该操作。
 *     <br>IMAGE_INVALID_PARAMETER：无效参数。可能的原因：入参为空。
 *     <br>IMAGE_ALLOC_FAILED：申请内存失败。可能的原因：1. 生成的Pixelmap尺寸过大。2. 系统内存不足。
 * @since 26.0.0
 */
Image_ErrorCode OH_PixelmapNative_ApplyScale(OH_PixelmapNative *pixelmap, float scaleX, float scaleY);

/**
 * @brief 根据输入的缩放比例对Pixelmap进行缩放。
 * <br>从API版本26.0.0开始，建议使用{@link OH_PixelmapNative_ApplyScale}代替，以获得更完善的异常报错信息。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针。
 * @param scaleX 宽度的缩放比例。
 *     取值不能为0，建议取正数，否则会产生翻转效果。
 * @param scaleY 高度的缩放比例。
 *     取值不能为0，建议取正数，否则会产生翻转效果。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_Scale(OH_PixelmapNative *pixelmap, float scaleX, float scaleY);

/**
 * @brief 根据指定的宽高缩放倍数和缩放算法对Pixelmap进行水平或垂直方向的缩放。
 *
 * @param pixelmap 被缩放的OH_PixelmapNative的指针。
 * @param scaleX 宽度的缩放倍数。
 *     取值不能为0，建议取正数，否则会产生翻转效果。
 * @param scaleY 高度的缩放倍数。
 *     取值不能为0，建议取正数，否则会产生翻转效果。
 * @param level 采用的缩放算法。该参数对于ASTC格式的Pixelmap不生效。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_GET_IMAGE_DATA_FAILED：获取图像数据失败。可能的原因：内部数据损坏。详情请检查日志。
 *     <br>IMAGE_PIXELMAP_RELEASED：Pixelmap已被释放。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：Pixelmap被锁定，不支持该操作。
 *     <br>IMAGE_INVALID_PARAMETER：无效参数。可能的原因：入参为空。
 *     <br>IMAGE_ALLOC_FAILED：申请内存失败。可能的原因：1. 生成的Pixelmap尺寸过大。2. 系统内存不足。
 * @since 26.0.0
 */
Image_ErrorCode OH_PixelmapNative_ApplyScaleWithAntiAliasing(OH_PixelmapNative *pixelmap, float scaleX, float scaleY,
    OH_PixelmapNative_AntiAliasingLevel level);

/**
 * @brief 根据指定的缩放算法和输入的缩放比例对图片进行缩放。
 * <br>从API版本26.0.0开始，建议使用{@link OH_PixelmapNative_ApplyScaleWithAntiAliasing}代替，以获得更完善的异常报错信息。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针。
 * @param scaleX 宽度的缩放比例。
 *     取值不能为0，建议取正数，否则会产生翻转效果。
 * @param scaleY 高度的缩放比例。
 *     取值不能为0，建议取正数，否则会产生翻转效果。
 * @param level 缩放算法。该参数对于ASTC格式的Pixelmap不生效。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_TOO_LARGE：图片过大。
 *     <br>IMAGE_ALLOC_FAILED：内存申请失败。
 *     <br>IMAGE_UNKNOWN_ERROR：pixelmap已经被释放。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_ScaleWithAntiAliasing(OH_PixelmapNative *pixelmap, float scaleX, float scaleY,
    OH_PixelmapNative_AntiAliasingLevel level);

/**
 * @brief 根据输入的宽高的缩放比例，创建一个新的缩放后的图像，生成的新Pixelmap不可编辑。该接口不会拷贝原图像的HDR元数据和EXIF信息。
 *
 * @param srcPixelmap 被操作的OH_PixelmapNative指针，源Pixelmap对象指针。
 * @param dstPixelmap 被操作的OH_PixelmapNative指针，目标Pixelmap对象指针。
 * @param scaleX 宽度的缩放比例。
 *     取值不能为0，建议取正数，否则会产生翻转效果。
 * @param scaleY 高度的缩放比例。
 *     取值不能为0，建议取正数，否则会产生翻转效果。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PixelmapNative_CreateScaledPixelMap(OH_PixelmapNative *srcPixelmap, OH_PixelmapNative **dstPixelmap,
    float scaleX, float scaleY);

/**
 * @brief 根据指定的缩放算法和输入的宽高的缩放比例，创建一个新的缩放后的图像，生成的新Pixelmap不可编辑。
 * 该接口不会拷贝原图像的HDR元数据和EXIF信息。
 *
 * @param srcPixelmap 被操作的OH_PixelmapNative指针，源Pixelmap对象指针。
 * @param dstPixelmap 被操作的OH_PixelmapNative指针，目标Pixelmap对象指针。
 * @param scaleX 宽度的缩放比例。
 *     取值不能为0，建议取正数，否则会产生翻转效果。
 * @param scaleY 高度的缩放比例。
 *     取值不能为0，建议取正数，否则会产生翻转效果。
 * @param level 缩放算法。该参数对于ASTC格式的Pixelmap不生效。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_TOO_LARGE：图片过大。
 *     <br>IMAGE_ALLOC_FAILED：内存申请失败。
 * @since 18
 */
Image_ErrorCode OH_PixelmapNative_CreateScaledPixelMapWithAntiAliasing(OH_PixelmapNative *srcPixelmap,
    OH_PixelmapNative **dstPixelmap, float scaleX, float scaleY, OH_PixelmapNative_AntiAliasingLevel level);

/**
 * @brief 从源Pixelmap创建一个仅包含Alpha通道的ALPHA_8格式的Pixelmap，生成的新Pixelmap不可编辑。
 * <br>如果源Pixelmap的格式是ALPHA_F16，则新生成的Pixelmap将维持ALPHA_F16格式。
 *
 * @param srcPixelmap 提供Alpha通道数据的源Pixelmap。
 * @param dstPixelmap 被创建的目标Pixelmap。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_BAD_PARAMETER：参数无效，例如：srcPixelmap或dstPixelmap有误。
 * @since 22
 */
Image_ErrorCode OH_PixelmapNative_CreateAlphaPixelmap(OH_PixelmapNative *srcPixelmap, OH_PixelmapNative **dstPixelmap);

/**
 * @brief 对源Pixelmap进行拷贝，生成一个新的Pixelmap。该接口不会拷贝原图像的EXIF信息。
 *
 * @param srcPixelmap 被拷贝的源Pixelmap。
 * @param dstPixelmap 生成的目标Pixelmap。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_BAD_PARAMETER：参数无效，例如：srcPixelmap或dstPixelmap有误。
 *     <br>IMAGE_UNSUPPORTED_DATA_FORMAT：像素格式不支持。
 *     <br>IMAGE_TOO_LARGE：源Pixelmap的尺寸过大。
 *     <br>IMAGE_INIT_FAILED：目标Pixelmap初始化失败。
 *     <br>IMAGE_ALLOC_FAILED：内存申请或数据复制失败。
 * @since 22
 */
Image_ErrorCode OH_PixelmapNative_Clone(OH_PixelmapNative *srcPixelmap, OH_PixelmapNative **dstPixelmap);

/**
 * @brief 基于源Pixelmap创建一个裁剪并缩放的新Pixelmap。该接口不会拷贝原图像的EXIF信息。
 *
 * @param srcPixelmap 源Pixelmap。
 * @param region 裁剪区域。
 * @param scale 宽和高的缩放倍数。
 *     取值不能为0，建议取正数，否则会产生翻转效果。
 * @param level 要使用的缩放插值算法。该参数对于ASTC格式的Pixelmap不生效。
 * @param dstPixelmap 被创建的目标Pixelmap。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_BAD_PARAMETER：参数无效，例如：srcPixelmap、region、scale或dstPixelmap有误。
 *     <br>IMAGE_UNSUPPORTED_DATA_FORMAT：像素格式不支持。
 *     <br>IMAGE_TOO_LARGE：源Pixelmap的尺寸过大。
 *     <br>IMAGE_INIT_FAILED：目标Pixelmap初始化失败。
 *     <br>IMAGE_ALLOC_FAILED：内存申请或数据复制失败。
 * @since 22
 */
Image_ErrorCode OH_PixelmapNative_CreateCroppedAndScaledPixelMap(OH_PixelmapNative *srcPixelmap, Image_Region *region,
    Image_Scale *scale, OH_PixelmapNative_AntiAliasingLevel level, OH_PixelmapNative **dstPixelmap);

/**
 * @brief 根据指定的横向和纵向距离对Pixelmap进行水平或垂直方向的平移。
 * <br>平移后的图像尺寸将变为：宽度 = 原宽度 + x，高度 = 原高度 + y。
 *
 * @param pixelmap 被平移的OH_PixelmapNative的指针。
 * @param x 横向平移的距离。方向为正数向右，负数向左。取值范围是(-图像宽度, +∞)。单位：像素（px）。
 *     取值为负数时，平移的效果等同于裁剪掉自图像左侧起的x列像素。
 * @param y 纵向平移的距离。方向为正数向下，负数向上。取值范围是(-图像高度, +∞)。单位：像素（px）。
 *     取值为负数时，平移的效果等同于裁剪掉自图像上方起的y行像素。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_GET_IMAGE_DATA_FAILED：获取图像数据失败。可能的原因：内部数据损坏。详情请检查日志。
 *     <br>IMAGE_PIXELMAP_RELEASED：Pixelmap已被释放。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：Pixelmap被锁定，不支持该操作。
 *     <br>IMAGE_INVALID_PARAMETER：无效参数。可能的原因：入参为空。
 *     <br>IMAGE_ALLOC_FAILED：申请内存失败。可能的原因：1. 生成的Pixelmap尺寸过大。2. 系统内存不足。
 * @since 26.0.0
 */
Image_ErrorCode OH_PixelmapNative_ApplyTranslate(OH_PixelmapNative *pixelmap, float x, float y);

/**
 * @brief 根据输入的平移距离对图片进行位置变换。
 * <br>平移后的图像尺寸将变为：宽度 = 原宽度 + x，高度 = 原高度 + y。
 * <br>从API版本26.0.0开始，建议使用{@link OH_PixelmapNative_ApplyTranslate}代替，以获得更完善的异常报错信息。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针。
 * @param x 横向平移的距离。方向为正数向右，负数向左。取值范围是(-图像宽度, +∞)。单位：像素（px）。
 *     取值为负数时，平移的效果等同于裁剪掉自图像左侧起的x列像素。
 * @param y 纵向平移的距离。方向为正数向下，负数向上。取值范围是(-图像高度, +∞)。单位：像素（px）。
 *     取值为负数时，平移的效果等同于裁剪掉自图像上方起的y行像素。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_Translate(OH_PixelmapNative *pixelmap, float x, float y);

/**
 * @brief 根据指定的角度对Pixelmap进行旋转。YUV格式仅支持90°倍数的旋转角。
 *
 * @param pixelmap 被旋转的OH_PixelmapNative的指针。
 * @param angle 旋转的角度。单位：角度（°）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_GET_IMAGE_DATA_FAILED：获取图像数据失败。可能的原因：内部数据损坏。详情请检查日志。
 *     <br>IMAGE_PIXELMAP_RELEASED：Pixelmap已被释放。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：Pixelmap被锁定，不支持该操作。
 *     <br>IMAGE_INVALID_PARAMETER：无效参数。可能的原因：入参为空。
 *     <br>IMAGE_ALLOC_FAILED：申请内存失败。可能的原因：1. 生成的Pixelmap尺寸过大。2. 系统内存不足。
 * @since 26.0.0
 */
Image_ErrorCode OH_PixelmapNative_ApplyRotate(OH_PixelmapNative *pixelmap, float angle);

/**
 * @brief 根据输入的角度对图片进行旋转，YUV格式仅支持90°倍数的旋转角。
 * <br>从API版本26.0.0开始，建议使用{@link OH_PixelmapNative_ApplyRotate}代替，以获得更完善的异常报错信息。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针。
 * @param angle 图片旋转的角度。单位：角度（°）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_Rotate(OH_PixelmapNative *pixelmap, float angle);

/**
 * @brief 根据指定的水平或垂直翻转条件对Pixelmap进行翻转。
 *
 * @param pixelmap 被翻转的OH_PixelmapNative的指针。
 * @param shouldFlipHorizontally 是否进行水平翻转。true表示进行水平翻转，false表示不进行水平翻转。
 * @param shouldFlipVertically 是否进行垂直翻转。true表示进行垂直翻转，false表示不进行垂直翻转。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_GET_IMAGE_DATA_FAILED：获取图像数据失败。可能的原因：内部数据损坏。详情请检查日志。
 *     <br>IMAGE_PIXELMAP_RELEASED：Pixelmap已被释放。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：Pixelmap被锁定，不支持该操作。
 *     <br>IMAGE_INVALID_PARAMETER：无效参数。可能的原因：入参为空。
 *     <br>IMAGE_ALLOC_FAILED：申请内存失败。可能的原因：系统内存不足。
 * @since 26.0.0
 */
Image_ErrorCode OH_PixelmapNative_ApplyFlip(OH_PixelmapNative *pixelmap, bool shouldFlipHorizontally,
    bool shouldFlipVertically);

/**
 * @brief 根据输入的条件对图片进行翻转。
 * <br>从API版本26.0.0开始，建议使用{@link OH_PixelmapNative_ApplyFlip}代替，以获得更完善的异常报错信息。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针。
 * @param shouldFlipHorizontally 是否水平翻转图像。true表示进行水平翻转，false表示不进行水平翻转。
 * @param shouldFlipVertically 是否垂直翻转图像。true表示进行垂直翻转，false表示不进行垂直翻转。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_Flip(OH_PixelmapNative *pixelmap, bool shouldFlipHorizontally,
    bool shouldFlipVertically);

/**
 * @brief 根据指定的区域信息对Pixelmap进行裁剪。
 *
 * @param pixelmap 被裁剪的OH_PixelmapNative的指针。
 * @param region 裁剪区域的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_GET_IMAGE_DATA_FAILED：获取图像数据失败。可能的原因：内部数据损坏。详情请检查日志。
 *     <br>IMAGE_PIXELMAP_RELEASED：Pixelmap已被释放。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：Pixelmap被锁定，不支持该操作。
 *     <br>IMAGE_INVALID_REGION：指定的区域无效或超出范围。
 *     <br>IMAGE_INVALID_PARAMETER：无效参数。可能的原因：任意入参为空。
 *     <br>IMAGE_ALLOC_FAILED：申请内存失败。可能的原因：1. 处理像素数据失败。2. 系统内存不足。
 * @since 26.0.0
 */
Image_ErrorCode OH_PixelmapNative_ApplyCrop(OH_PixelmapNative *pixelmap, Image_Region *region);

/**
 * @brief 根据输入的区域信息对图片进行裁剪。
 * <br>从API版本26.0.0开始，建议使用{@link OH_PixelmapNative_ApplyCrop}代替，以获得更完善的异常报错信息。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针。
 * @param region 裁剪的区域，包含起始坐标和宽高。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_Crop(OH_PixelmapNative *pixelmap, Image_Region *region);

/**
 * @brief 释放OH_PixelmapNative指针（当内存被{@link OH_PixelmapNative_AccessPixels}锁定时无法释放）。
 * <br>推荐使用{@link OH_PixelmapNative_Destroy}。
 *
 * @param pixelmap 被释放的OH_PixelmapNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_Release(OH_PixelmapNative *pixelmap);

/**
 * @brief 释放OH_PixelmapNative指针，不受{@link OH_PixelmapNative_AccessPixels}锁定内存的影响。
 *
 * @param pixelmap 被释放的OH_PixelmapNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PixelmapNative_Destroy(OH_PixelmapNative **pixelmap);

/**
 * @brief 将Pixelmap像素数据的透明度类型在预乘模式（{@link PIXELMAP_ALPHA_TYPE_PREMULTIPLIED}）和非预乘模式
 * （{@link PIXELMAP_ALPHA_TYPE_UNPREMULTIPLIED}）之间转换。该转换仅支持除RGBA_F16和ASTC_4x4之外其他包含Alpha通道的像素格式。
 * <br>像素格式的列表请参考{@link PIXEL_FORMAT}。
 *
 * @param srcPixelmap 源Pixelmap的指针，包含待转换的像素数据，其透明度格式必须是预乘或非预乘。
 * @param dstPixelmap 一个空白的目标Pixelmap的指针，其属性（宽度、高度、像素格式等）必须与源Pixelmap相同，
 *     但其透明度类型必须与源Pixelmap相反（例如，如果源Pixelmap为预乘，则目标Pixelmap必须为非预乘）且必须可编辑。
 *     转换后的像素数据将写入此Pixelmap。
 * @param toPremul 指定转换方向。true表示从非预乘转换为预乘，false表示从预乘转换为非预乘。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_GET_IMAGE_DATA_FAILED：获取图像数据失败。可能的原因：内部数据损坏。详情请检查日志。
 *     <br>IMAGE_PIXELMAP_RELEASED：任一Pixelmap已被释放。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：Pixelmap被锁定，不支持该操作。
 *     <br>IMAGE_INVALID_PARAMETER：无效参数。可能的原因：1. 任一Pixelmap不符合要求。2. 任意入参为空。
 *     <br>IMAGE_UNSUPPORTED_DATA_FORMAT：任一Pixelmap的像素格式不被支持。
 * @since 26.0.0
 */
Image_ErrorCode OH_PixelmapNative_ConvertAlphaType(OH_PixelmapNative *srcPixelmap, OH_PixelmapNative *dstPixelmap,
    const bool toPremul);

/**
 * @brief 将Pixelmap像素数据的透明度类型在预乘模式和非预乘模式之间转换。该转换仅支持除RGBA_F16和ASTC_4x4之外其他包含Alpha通道的像素格式。
 * <br>从API版本26.0.0开始，建议使用{@link OH_PixelmapNative_ConvertAlphaType}代替，以获得更完善的异常报错信息。
 *
 * @param srcpixelmap 源Pixelmap的指针，包含待转换的像素数据，其透明度格式必须是预乘或非预乘。
 * @param dstpixelmap 一个空白的目标Pixelmap的指针，其属性（宽度、高度、像素格式等）必须与源Pixelmap相同，
 *     但其透明度类型必须与源Pixelmap相反（例如，如果源Pixelmap为预乘，则目标Pixelmap必须为非预乘）且必须可编辑。
 *     转换后的像素数据将写入此Pixelmap。
 * @param isPremul 转换方向，true为非预乘转预乘，false为预乘转非预乘。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_ConvertAlphaFormat(OH_PixelmapNative* srcpixelmap,
    OH_PixelmapNative* dstpixelmap, const bool isPremul);

/**
 * @brief 利用OH_Pixelmap_InitializationOptions创建空的Pixelmap对象，内存数据为0。
 *
 * @param options 创建图像的初始化属性。
 * @param pixelmap 被创建的OH_PixelmapNative对象指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_CreateEmptyPixelmap(OH_Pixelmap_InitializationOptions *options,
    OH_PixelmapNative **pixelmap);

/**
 * @brief 根据入参options创建空的Pixelmap，Pixelmap使用的内存类型可以通过allocator指定。
 * <br>默认情况下，系统会根据图像类型、图像大小、平台能力等选择内存类型。
 * <br>在处理此接口返回的像素图时，需要考虑行跨距的影响。行跨距即图像每行占用的真实内存大小，可能因内存对齐而大于图像宽度乘以单位像素字节数，
 * 请参考{@link OH_PixelmapInitializationOptions_GetRowStride}获取详细说明。
 *
 * @param options 创建图像的初始化属性。
 * @param allocator 决定pixelmap内存分配的类型。
 * @param pixelmap 被创建的OH_PixelmapNative对象指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：操作不支持。
 *     <br>IMAGE_TOO_LARGE：图像过大，无法分配内存。
 *     <br>IMAGE_DMA_OPERATION_FAILED：DMA内存操作失败。
 *     <br>IMAGE_ALLOCATOR_MODE_UNSUPPORTED：不支持分配当前内存类型。例如，使用共享内存创建HDR图。
 * @since 20
 */
Image_ErrorCode OH_PixelmapNative_CreateEmptyPixelmapUsingAllocator(
    OH_Pixelmap_InitializationOptions *options, IMAGE_ALLOCATOR_MODE allocator, OH_PixelmapNative **pixelmap);

/**
 * @brief 通过Surface的ID创建一个Pixelmap。如果Surface携带旋转或翻转的变换信息且需要校正方向，
 * 请使用{@link OH_PixelmapNative_CreatePixelmapFromSurfaceWithTransformation}。
 *
 * @param surfaceId Surface ID字符串。
 * @param length Surface ID字符串的长度。单位：字节（Byte）。
 * @param pixelmap 被创建的Pixelmap。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_BAD_PARAMETER：参数无效，例如：surfaceId或pixelmap有误。
 *     <br>IMAGE_CREATE_PIXELMAP_FAILED：Pixelmap创建失败。
 * @since 22
 */
Image_ErrorCode OH_PixelmapNative_CreatePixelmapFromSurface(const char *surfaceId, size_t length,
    OH_PixelmapNative **pixelmap);

/**
 * @brief 通过Surface的ID创建一个预览流画面的Pixelmap对象。该Surface可能携带旋转或翻转的变换信息。
 *
 * @param surfaceId 对应Surface的ID字符串。
 * @param length 对应Surface的ID字符串长度。单位：字节（Byte）。
 * @param transformEnabled 是否对携带变换信息的Surface预先进行逆变换来消除Pixelmap的旋转或翻转效果，即是否进行方向校正。
 *     如果Surface未携带变换信息，则本参数不生效。
 *     true表示进行逆变换，变换的角度与Surface携带的角度一致且方向相反，输出的Pixelmap无旋转或翻转效果。
 *     false表示不进行逆变换，输出的Pixelmap会根据Surface中的变换信息而带有旋转或翻转效果。
 * @param pixelmap 被创建的Pixelmap。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_INVALID_PARAMETER：参数无效，例如：surfaceId或pixelmap有误。
 *     <br>IMAGE_UNSUPPORTED_OPERATION：不支持的操作，例如：跨平台时调用。
 *     <br>IMAGE_GET_IMAGE_DATA_FAILED：获取Surface的数据失败。
 *     <br>IMAGE_CREATE_PIXELMAP_FAILED：Pixelmap创建失败。
 * @see OH_PixelmapNative
 * @since 23
 */
Image_ErrorCode OH_PixelmapNative_CreatePixelmapFromSurfaceWithTransformation(const char *surfaceId, size_t length,
    bool transformEnabled, OH_PixelmapNative **pixelmap);

/**
 * @brief 通过NativeBuffer创建一个Pixelmap。
 * <br>如果NativeBuffer的用途未配置CPU访问权限（详情请参考{@link OH_NativeBuffer_Usage}），则不支持创建。
 * <br>支持创建的像素格式为RGBA_8888、NV21、NV12、YCBCR_P010、YCRCB_P010。
 *
 * @param nativeBuffer 含有Pixelmap数据的NativeBuffer对象。NativeBuffer的用途必须配置CPU访问权限
 *     （详情请参考{@link OH_NativeBuffer_Usage}），且像素格式必须为RGBA_8888、NV21、NV12、YCBCR_P010或YCRCB_P010。
 * @param pixelmap 被创建的Pixelmap。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_BAD_PARAMETER：参数无效，例如：nativeBuffer或pixelmap有误，像素格式不支持，或未配置CPU访问权限。
 *     <br>IMAGE_CREATE_PIXELMAP_FAILED：Pixelmap创建失败。
 * @since 22
 */
Image_ErrorCode OH_PixelmapNative_CreatePixelmapFromNativeBuffer(OH_NativeBuffer *nativeBuffer,
    OH_PixelmapNative **pixelmap);

/**
 * @brief 从DMA内存的Pixelmap中，获取NativeBuffer对象。
 *
 * @param pixelmap 要获取NativeBuffer的源Pixelmap，内存类型必须是DMA。
 * @param nativeBuffer 被创建的NativeBuffer对象指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_DMA_NOT_EXIST：不是DMA内存。
 *     <br>IMAGE_DMA_OPERATION_FAILED：DMA内存操作失败。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_GetNativeBuffer(OH_PixelmapNative *pixelmap, OH_NativeBuffer **nativeBuffer);

/**
 * @brief 获取Pixelmap的HDR元数据。通过传入{@link OH_Pixelmap_HdrMetadataKey}关键字指定需要获取的元数据类型，
 * 并通过{@link OH_Pixelmap_HdrMetadataValue}返回对应的元数据值。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针，Pixelmap的内存类型必须是DMA。
 * @param key 元数据的关键字。
 * @param value 元数据的值。
 *     如果获取的是动态元数据（HDR_DYNAMIC_METADATA）且接口调用成功，使用完成后必须调用free(value->dynamicMetadata.data)释放内存。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_DMA_NOT_EXIST：不存在DMA内存。
 *     <br>IMAGE_COPY_FAILED：如果内存拷贝失败。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_GetMetadata(OH_PixelmapNative *pixelmap, OH_Pixelmap_HdrMetadataKey key,
    OH_Pixelmap_HdrMetadataValue **value);

/**
 * @brief 设置Pixelmap的HDR元数据。通过传入{@link OH_Pixelmap_HdrMetadataKey}关键字指定需要设置的元数据类型，
 * 并通过{@link OH_Pixelmap_HdrMetadataValue}传入对应的元数据值。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针，Pixelmap的内存类型必须是DMA。
 * @param key 元数据的关键字。
 * @param value 元数据的值。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_DMA_NOT_EXIST：不存在DMA内存。
 *     <br>IMAGE_COPY_FAILED：如果内存拷贝失败。
 * @since 12
 */
Image_ErrorCode OH_PixelmapNative_SetMetadata(OH_PixelmapNative *pixelmap, OH_Pixelmap_HdrMetadataKey key,
    OH_Pixelmap_HdrMetadataValue *value);

/**
 * @brief 设置Pixelmap的NativeColorSpaceManager对象，用于管理Pixelmap的色彩空间信息。
 *
 * @param pixelmap 要设置NativeColorSpaceManager的目标Pixelmap。
 * @param colorSpaceNative 要设置的NativeColorSpaceManager对象。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_PixelmapNative_SetColorSpaceNative(OH_PixelmapNative *pixelmap,
    OH_NativeColorSpaceManager *colorSpaceNative);

/**
 * @brief 获取Pixelmap的NativeColorSpaceManager对象，用于查询Pixelmap当前配置的色彩空间信息。
 *
 * @param pixelmap 获取到NativeColorSpaceManager的源Pixelmap。
 * @param colorSpaceNative 获取到的NativeColorSpaceManager对象。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 13
 */
Image_ErrorCode OH_PixelmapNative_GetColorSpaceNative(OH_PixelmapNative *pixelmap,
    OH_NativeColorSpaceManager **colorSpaceNative);

/**
 * @brief 设置Pixelmap的内存标识符，便于在内存调试或问题定位时识别该内存。
 * <br>仅支持DMA和SHARE_MEMORY内存类型的PixelMap设置内存标识符。
 *
 * @param pixelmap 被操作的OH_PixelmapNative指针。
 * @param name 需要设置的内存标识符。DMA内存标识符的字符串长度取值范围为[1, 255]字节，
 *     SHARE_MEMORY内存标识符的字符串长度取值范围为[1, 244]字节。
 * @param size 需要设置的内存标识符的字符串长度。单位：字节（Byte）。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：名字长度超过取值范围。DMA内存名字取值范围为[1, 255]，SHARE_MEMORY内存名字取值范围为[1, 244]。单位：字节（Byte）。
 *     <br>IMAGE_UNSUPPORTED_MEMORY_FORMAT：既不是DMA内存也不是SHARE_MEMORY内存。
 * @since 13
 */
Image_ErrorCode OH_PixelmapNative_SetMemoryName(OH_PixelmapNative *pixelmap, char *name, size_t *size);

/**
 * @brief 获取Pixelmap中所有像素所占用的总字节数，不包含内存对齐填充字节。
 *
 * @param pixelmap 被操作的Pixelmap指针。
 * @param byteCount 获取的总字节数。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：pixelmap或byteCount参数无效。
 * @since 18
 */
Image_ErrorCode OH_PixelmapNative_GetByteCount(OH_PixelmapNative *pixelmap, uint32_t *byteCount);

/**
 * @brief 获取Pixelmap实际分配的用于存储像素数据的内存字节数，包含内存对齐填充字节。
 * 与{@link OH_PixelmapNative_GetByteCount}（不包含内存填充）不同，本接口返回的是系统为Pixelmap分配的真实内存大小。
 *
 * @param pixelmap 被操作的Pixelmap指针。
 * @param allocationByteCount 获取的内存字节数。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：pixelmap或allocationByteCount参数无效。
 * @since 18
 */
Image_ErrorCode OH_PixelmapNative_GetAllocationByteCount(OH_PixelmapNative *pixelmap, uint32_t *allocationByteCount);

/**
 * @brief 获取Pixelmap像素数据的内存地址，并锁定这块内存。
 * <br>当该内存被锁定时，任何修改或释放该Pixelmap的像素数据的操作均会失败或无效。
 * <br>使用完毕后，必须调用{@link OH_PixelmapNative_UnaccessPixels}释放内存锁，两者需配对使用。
 *
 * @param pixelmap 被操作的Pixelmap指针。
 * @param addr Pixelmap内存地址的双指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：pixelmap或addr参数无效。
 *     <br>IMAGE_LOCK_UNLOCK_FAILED：内存锁定失败。
 * @since 15
 */
Image_ErrorCode OH_PixelmapNative_AccessPixels(OH_PixelmapNative *pixelmap, void **addr);

/**
 * @brief 释放Pixelmap像素数据的内存锁。
 * <br>该函数需要与{@link OH_PixelmapNative_AccessPixels}匹配使用。
 *
 * @param pixelmap 被操作的Pixelmap指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：pixelmap参数无效。
 *     <br>IMAGE_LOCK_UNLOCK_FAILED：内存解锁失败。
 * @since 15
 */
Image_ErrorCode OH_PixelmapNative_UnaccessPixels(OH_PixelmapNative *pixelmap);

/**
 * @brief 获取Pixelmap的唯一ID。
 *
 * @param pixelmap 获取唯一ID的Pixelmap。
 * @param uniqueId 获取的唯一ID。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_BAD_PARAMETER：参数无效，例如：pixelmap或uniqueId有误。
 * @since 22
 */
Image_ErrorCode OH_PixelmapNative_GetUniqueId(OH_PixelmapNative *pixelmap, uint32_t *uniqueId);

/**
 * @brief 检测Pixelmap是否已被释放。如果已被释放，则任何访问该对象内部数据的方法调用将会失效。
 *
 * @param pixelmap 被检测的Pixelmap。
 * @param released 获取的Pixelmap的释放状态。true表示已被释放，false表示未被释放。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_BAD_PARAMETER：参数无效，例如：pixelmap或released有误。
 * @since 22
 */
Image_ErrorCode OH_PixelmapNative_IsReleased(OH_PixelmapNative *pixelmap, bool *released);

#ifdef __cplusplus
};
#endif
/** @} */
#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PIXELMAP_NATIVE_H_

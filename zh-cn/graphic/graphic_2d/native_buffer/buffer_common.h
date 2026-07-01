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
 * @addtogroup OH_NativeBuffer
 * @{
 *
 * @brief 提供NativeBuffer模块的公共类型定义。
 *
 * @since 12
 * @version 1.0
 */

/**
 * @file buffer_common.h
 *
 * @brief 提供NativeBuffer模块的公共类型定义。
 *
 * @kit ArkGraphics2D
 * @library libnative_buffer.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 12
 * @version 1.0
 */

#ifndef NDK_INCLUDE_BUFFER_COMMON_H_
#define NDK_INCLUDE_BUFFER_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief OH_NativeBuffer的颜色空间。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 11
 * @version 1.0
 */
/**
 * @brief OH_NativeBuffer的颜色空间。
 * Move from native_buffer.h to native_common.h
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 12
 * @version 1.0
 */
typedef enum OH_NativeBuffer_ColorSpace {
    /** 无颜色空间。 */
    OH_COLORSPACE_NONE,
    /** 色域范围为BT601_P，传递函数为BT709，转换矩阵为BT601_P，数据范围为RANGE_FULL。 */
    OH_COLORSPACE_BT601_EBU_FULL,
    /** 色域范围为BT601_N，传递函数为BT709，转换矩阵为BT601_N，数据范围为RANGE_FULL。 */
    OH_COLORSPACE_BT601_SMPTE_C_FULL,
    /** 色域范围为BT709，传递函数为BT709，转换矩阵为BT709，数据范围为RANGE_FULL。 */
    OH_COLORSPACE_BT709_FULL,
    /** 色域范围为BT2020，传递函数为HLG，转换矩阵为BT2020，数据范围为RANGE_FULL。 */
    OH_COLORSPACE_BT2020_HLG_FULL,
    /** 色域范围为BT2020，传递函数为PQ，转换矩阵为BT2020，数据范围为RANGE_FULL。 */
    OH_COLORSPACE_BT2020_PQ_FULL,
    /** 色域范围为BT601_P，传递函数为BT709，转换矩阵为BT601_P，数据范围为RANGE_LIMITED。 */
    OH_COLORSPACE_BT601_EBU_LIMIT,
    /** 色域范围为BT601_N，传递函数为BT709，转换矩阵为BT601_N，数据范围为RANGE_LIMITED。 */
    OH_COLORSPACE_BT601_SMPTE_C_LIMIT,
    /** 色域范围为BT709，传递函数为BT709，转换矩阵为BT709，数据范围为RANGE_LIMITED。 */
    OH_COLORSPACE_BT709_LIMIT,
    /** 色域范围为BT2020，传递函数为HLG，转换矩阵为BT2020，数据范围为RANGE_LIMITED。 */
    OH_COLORSPACE_BT2020_HLG_LIMIT,
    /** 色域范围为BT2020，传递函数为PQ，转换矩阵为BT2020，数据范围为RANGE_LIMITED。 */
    OH_COLORSPACE_BT2020_PQ_LIMIT,
    /** 色域范围为SRGB，传递函数为SRGB，转换矩阵为BT601_N，数据范围为RANGE_FULL。 */
    OH_COLORSPACE_SRGB_FULL,
    /** 色域范围为P3_D65，传递函数为SRGB，转换矩阵为P3，数据范围为RANGE_FULL。 */
    OH_COLORSPACE_P3_FULL,
    /** 色域范围为P3_D65，传递函数为HLG，转换矩阵为P3，数据范围为RANGE_FULL。 */
    OH_COLORSPACE_P3_HLG_FULL,
    /** 色域范围为P3_D65，传递函数为PQ，转换矩阵为P3，数据范围为RANGE_FULL。 */
    OH_COLORSPACE_P3_PQ_FULL,
    /** 色域范围为ADOBERGB，传递函数为ADOBERGB，转换矩阵为ADOBERGB，数据范围为RANGE_FULL。 */
    OH_COLORSPACE_ADOBERGB_FULL,
    /** 色域范围为SRGB，传递函数为SRGB，转换矩阵为BT601_N，数据范围为RANGE_LIMITED。 */
    OH_COLORSPACE_SRGB_LIMIT,
    /** 色域范围为P3_D65，传递函数为SRGB，转换矩阵为P3，数据范围为RANGE_LIMITED。 */
    OH_COLORSPACE_P3_LIMIT,
    /** 色域范围为P3_D65，传递函数为HLG，转换矩阵为P3，数据范围为RANGE_LIMITED。 */
    OH_COLORSPACE_P3_HLG_LIMIT,
    /** 色域范围为P3_D65，传递函数为PQ，转换矩阵为P3，数据范围为RANGE_LIMITED。 */
    OH_COLORSPACE_P3_PQ_LIMIT,
    /** 色域范围为ADOBERGB，传递函数为ADOBERGB，转换矩阵为ADOBERGB，数据范围为RANGE_LIMITED。 */
    OH_COLORSPACE_ADOBERGB_LIMIT,
    /** 色域范围为SRGB，传递函数为LINEAR。 */
    OH_COLORSPACE_LINEAR_SRGB,
    /** 等同于 OH_COLORSPACE_LINEAR_SRGB。 */
    OH_COLORSPACE_LINEAR_BT709,
    /** 色域范围为P3_D65，传递函数为LINEAR。 */
    OH_COLORSPACE_LINEAR_P3,
    /** 色域范围为BT2020，传递函数为LINEAR。 */
    OH_COLORSPACE_LINEAR_BT2020,
    /** 等同于OH_COLORSPACE_SRGB_FULL。 */
    OH_COLORSPACE_DISPLAY_SRGB,
    /** 等同于OH_COLORSPACE_P3_FULL。 */
    OH_COLORSPACE_DISPLAY_P3_SRGB,
    /** 等同于OH_COLORSPACE_P3_HLG_FULL。 */
    OH_COLORSPACE_DISPLAY_P3_HLG,
    /** 等同于OH_COLORSPACE_P3_PQ_FULL。 */
    OH_COLORSPACE_DISPLAY_P3_PQ,
    /** 色域范围为BT2020，传递函数为SRGB，转换矩阵为BT2020，数据范围为RANGE_FULL。 */
    OH_COLORSPACE_DISPLAY_BT2020_SRGB,
    /** 等同于 OH_COLORSPACE_BT2020_HLG_FULL。 */
    OH_COLORSPACE_DISPLAY_BT2020_HLG,
    /** 等同于OH_COLORSPACE_BT2020_PQ_FULL。 */
    OH_COLORSPACE_DISPLAY_BT2020_PQ,
    /**
     * COLORPRIMARIES_BT2020 | (TRANSFUNC_PRIV_LOG << 8) | (MATRIX_BT2020 << 16) | (RANGE_FULL << 21)
     * @since 26.0.0
     */
    OH_COLORSPACE_BT2020_LOG_FULL,
    /**
     * COLORPRIMARIES_BT2020 | (TRANSFUNC_PRIV_LOG << 8) | (MATRIX_BT2020 << 16) | (RANGE_LIMITED << 21)
     * @since 26.0.0
     */
    OH_COLORSPACE_BT2020_LOG_LIMIT,
} OH_NativeBuffer_ColorSpace;

/**
 * @brief OH_NativeBuffer的图像标准。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 12
 * @version 1.0
 */
typedef enum OH_NativeBuffer_MetadataType {
    /** 视频HLG。 */
    OH_VIDEO_HDR_HLG,
    /** 视频HDR10。 */
    OH_VIDEO_HDR_HDR10,
    /** 视频HDR VIVID。 */
    OH_VIDEO_HDR_VIVID,
/**
      * 图片HDR VIVID DUAL。
      * @since 22
      */
    OH_IMAGE_HDR_VIVID_DUAL,
/**
      * 图片HDR VIVID SINGLE。
      * @since 22
      */
    OH_IMAGE_HDR_VIVID_SINGLE,
/**
      * 图片HDR ISO DUAL。
      * @since 23
      */
    OH_IMAGE_HDR_ISO_DUAL,
/**
      * 图片HDR ISO SINGLE。
      * @since 23
      */
    OH_IMAGE_HDR_ISO_SINGLE,
/**
      * 无元数据。
      * @since 13
      */
    OH_VIDEO_NONE = -1
} OH_NativeBuffer_MetadataType;

/**
 * @brief 表示基色的X和Y坐标。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 12
 * @version 1.0
 */
typedef struct OH_NativeBuffer_ColorXY {
    /** 颜色X坐标 */
    float x;
    /** 颜色Y坐标 */
    float y;
} OH_NativeBuffer_ColorXY;

/**
 * @brief 表示smpte2086静态元数据。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 12
 * @version 1.0
 */
typedef struct OH_NativeBuffer_Smpte2086 {
    /** 红基色 */
    OH_NativeBuffer_ColorXY displayPrimaryRed;
    /** 绿基色 */
    OH_NativeBuffer_ColorXY displayPrimaryGreen;
    /** 蓝基色 */
    OH_NativeBuffer_ColorXY displayPrimaryBlue;
    /** 白点 */
    OH_NativeBuffer_ColorXY whitePoint;
    /** 最大亮度 */
    float maxLuminance;
    /** 最小亮度 */
    float minLuminance;
} OH_NativeBuffer_Smpte2086;

/**
 * @brief 表示CTA-861.3静态元数据。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 12
 * @version 1.0
 */
typedef struct OH_NativeBuffer_Cta861 {
    /** 最大内容亮度水平 */
    float maxContentLightLevel;
    /** 最大帧平均亮度水平 */
    float maxFrameAverageLightLevel;
} OH_NativeBuffer_Cta861;

/**
 * @brief 表示HDR静态元数据。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 12
 * @version 1.0
 */
typedef struct OH_NativeBuffer_StaticMetadata {
    /** smpte2086静态元数据 */
    OH_NativeBuffer_Smpte2086 smpte2086;
    /** CTA-861.3静态元数据 */
    OH_NativeBuffer_Cta861 cta861;
} OH_NativeBuffer_StaticMetadata;

/**
 * @brief 表示OH_NativeBuffer的描述信息的键值，如HDR元数据，ROI元数据等。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 12
 * @version 1.0
 */
typedef enum OH_NativeBuffer_MetadataKey {
    /** value: OH_NativeBuffer_MetadataType*/
    OH_HDR_METADATA_TYPE,
    /** value: OH_NativeBuffer_StaticMetadata*/
    OH_HDR_STATIC_METADATA,
    /** byte stream of SEI in video stream*/
    OH_HDR_DYNAMIC_METADATA,
    /**
     * Region of interest(ROI) metadata is used to configure ROI feature in video encoding. Value type is string
     * in the format "Top1,Left1-Bottom1,Right1[=Params1];Top2,Left2-Bottom2,Right2[=Params2];".
     * Each "Top,Left-Bottom,Right" represents the coordinate information of one ROI.
     * The "[=Params]" is optional.
     * The format of "[=Params]" varies by version:
     * 1. Prior to version 26.0.0: Only a single int32_t value representing the
     * quantization parameter offset is supported (e.g., "=QpOffset").
     * 2. Since version 26.0.0: A Key-Value format is additionally supported and recommended.
     * It uses comma-separated key-value pairs (e.g., "=dqp:-6,slb:1").
     * Supported keys:
     * - "dqp": Quantization parameter offset.
     * - "slb": Semantic label. The value must correspond to {@link OH_VideoMetadataRoiSemanticLabel}.
     *
     * If "=Params" is omitted entirely, like "Top1,Left1-Bottom1,Right1;Top2,Left2-Bottom2,Right2=dqp:-6;",
     * the encoder will use the default parameters to perform the ROI encoding on the first ROI and
     * use the specified parameters on the second ROI.
     * Note that the number of ROIs that can be applied simultaneously does not exceed six, and the total area must
     * not exceed one-fifth of the total image area.
     *
     * @note Since version 26.0.0, it is highly recommended to use {@link OH_VideoMetadata_AppendRoiString} to format
     *     and append ROI configurations safely instead of concatenating the string manually.
     *
     * @since 22
     */
    OH_REGION_OF_INTEREST_METADATA
} OH_NativeBuffer_MetadataKey;

/**
 * @brief OH_NativeBuffer格式的枚举。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 10
 * @version 1.0
 */
typedef enum OH_NativeBuffer_Format {
    /**
     * CLUT8 format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_CLUT8 = 0,
    /**
     * CLUT1 format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_CLUT1,
    /**
     * CLUT4 format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_CLUT4,
    NATIVEBUFFER_PIXEL_FMT_RGB_565 = 3,               /// < RGB565 format */
    NATIVEBUFFER_PIXEL_FMT_RGBA_5658,                 /// < RGBA5658 format */
    NATIVEBUFFER_PIXEL_FMT_RGBX_4444,                 /// < RGBX4444 format */
    NATIVEBUFFER_PIXEL_FMT_RGBA_4444,                 /// < RGBA4444 format */
    NATIVEBUFFER_PIXEL_FMT_RGB_444,                   /// < RGB444 format */
    NATIVEBUFFER_PIXEL_FMT_RGBX_5551,                 /// < RGBX5551 format */
    NATIVEBUFFER_PIXEL_FMT_RGBA_5551,                 /// < RGBA5551 format */
    NATIVEBUFFER_PIXEL_FMT_RGB_555,                   /// < RGB555 format */
    NATIVEBUFFER_PIXEL_FMT_RGBX_8888,                 /// < RGBX8888 format */
    NATIVEBUFFER_PIXEL_FMT_RGBA_8888,                 /// < RGBA8888 format */
    NATIVEBUFFER_PIXEL_FMT_RGB_888,                   /// < RGB888 format */
    NATIVEBUFFER_PIXEL_FMT_BGR_565,                   /// < BGR565 format */
    NATIVEBUFFER_PIXEL_FMT_BGRX_4444,                 /// < BGRX4444 format */
    NATIVEBUFFER_PIXEL_FMT_BGRA_4444,                 /// < BGRA4444 format */
    NATIVEBUFFER_PIXEL_FMT_BGRX_5551,                 /// < BGRX5551 format */
    NATIVEBUFFER_PIXEL_FMT_BGRA_5551,                 /// < BGRA5551 format */
    NATIVEBUFFER_PIXEL_FMT_BGRX_8888,                 /// < BGRX8888 format */
    NATIVEBUFFER_PIXEL_FMT_BGRA_8888,                 /// < BGRA8888 format */
    /**
     * YUV422 interleaved format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_YUV_422_I,
    /**
     * YCBCR422 semi-plannar format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_YCBCR_422_SP,
    /**
     * YCRCB422 semi-plannar format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_YCRCB_422_SP,
    /**
     * YCBCR420 semi-plannar format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_YCBCR_420_SP,
    /**
     * YCRCB420 semi-plannar format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_YCRCB_420_SP,
    /**
     * YCBCR422 plannar format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_YCBCR_422_P,
    /**
     * YCRCB422 plannar format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_YCRCB_422_P,
    /**
     * YCBCR420 plannar format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_YCBCR_420_P,
    /**
     * YCRCB420 plannar format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_YCRCB_420_P,
    /**
     * YUYV422 packed format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_YUYV_422_PKG,
    /**
     * UYVY422 packed format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_UYVY_422_PKG,
    /**
     * YVYU422 packed format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_YVYU_422_PKG,
    /**
     * VYUY422 packed format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_VYUY_422_PKG,
    /**
     * RGBA_1010102 packed format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_RGBA_1010102,
    /**
     * YCBCR420 semi-planar 10bit packed format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_YCBCR_P010,
    /**
     * YCRCB420 semi-planar 10bit packed format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_YCRCB_P010,
    /**
     * Raw 10bit packed format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_RAW10,
    /**
     * BLOB format
     * @since 15
     */
    NATIVEBUFFER_PIXEL_FMT_BLOB,
    /**
     * RGBA16 float format
     * @since 15
     */
    NATIVEBUFFER_PIXEL_FMT_RGBA16_FLOAT,
    /**
     * Y8 format
     * @since 20
     */
    NATIVEBUFFER_PIXEL_FMT_Y8 = 40,
    /**
     * Y16 format
     * @since 20
     */
    NATIVEBUFFER_PIXEL_FMT_Y16 = 41,
    /**
     * vender mask format
     * @since 12
     */
    NATIVEBUFFER_PIXEL_FMT_VENDER_MASK = 0X7FFF0000,
    NATIVEBUFFER_PIXEL_FMT_BUTT = 0X7FFFFFFF          /// < Invalid pixel format */
} OH_NativeBuffer_Format;

/**
 * @brief OH_NativeBuffer转换类型的枚举。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 12
 * @version 1.0
 */
typedef enum OH_NativeBuffer_TransformType {
    NATIVEBUFFER_ROTATE_NONE = 0,         /**< 不旋转 */
    NATIVEBUFFER_ROTATE_90,               /**< 旋转90度 */
    NATIVEBUFFER_ROTATE_180,              /**< 旋转180度 */
    NATIVEBUFFER_ROTATE_270,              /**< 旋转270度 */
    NATIVEBUFFER_FLIP_H,                  /**< 水平翻转 */
    NATIVEBUFFER_FLIP_V,                  /**< 垂直翻转 */
    NATIVEBUFFER_FLIP_H_ROT90,            /**< 水平翻转并旋转90度 */
    NATIVEBUFFER_FLIP_V_ROT90,            /**< 垂直翻转并旋转90度 */
    NATIVEBUFFER_FLIP_H_ROT180,           /**< 水平翻转并旋转180度 */
    NATIVEBUFFER_FLIP_V_ROT180,           /**< 垂直翻转并旋转180度 */
    NATIVEBUFFER_FLIP_H_ROT270,           /**< 水平翻转并旋转270度 */
    NATIVEBUFFER_FLIP_V_ROT270,           /**< 垂直翻转并旋转270度 */
} OH_NativeBuffer_TransformType;

#ifdef __cplusplus
}
#endif

/** @} */
#endif
/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Provides Image type definitions of ArkUI on the native side.
 *
 * @since 12
 */

/**
 * @file image.h
 *
 * @brief 为NativeNode API提供Image节点类型定义。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义图片重复铺设枚举值。
 *
 * @since 12
 */
typedef enum {
    /**
     * 不重复。
     * @since 12
     */
    ARKUI_IMAGE_REPEAT_NONE = 0,
    /**
     * 在X轴方向重复。
     * @since 12
     */
    ARKUI_IMAGE_REPEAT_X = 1,
    /**
     * 在Y轴方向重复。
     * @since 12
     */
    ARKUI_IMAGE_REPEAT_Y = 2,
    /**
     * 在X轴和Y轴方向重复。
     * @since 12
     */
    ARKUI_IMAGE_REPEAT_XY = 3
} ArkUI_ImageRepeat;

/**
 * @brief 定义图片宽高样式。
 *
 * @since 12
 */
typedef enum {
    /**
     * 保持原图的比例不变。
     * @since 12
     */
    ARKUI_IMAGE_SIZE_AUTO = 0,
    /**
     * 保持宽高比进行缩小或者放大，使得图片两边都大于或等于显示边界。
     * @since 12
     */
    ARKUI_IMAGE_SIZE_COVER = 1,
    /**
     * 保持宽高比进行缩小或者放大，使得图片完全显示在显示边界内。
     * @since 12
     */
    ARKUI_IMAGE_SIZE_CONTAIN = 2
} ArkUI_ImageSize;

/**
 * @brief 定义{@link Image}组件的图片填充效果。
 *
 * @since 12
 */
typedef enum {
    /**
     * 保持宽高比进行缩小或者放大，使得图片完全显示在显示边界内。
     * @since 12
     */
    ARKUI_OBJECT_FIT_CONTAIN = 0,
    /**
     * 保持宽高比进行缩小或者放大，使得图片两边都大于或等于显示边界。
     * @since 12
     */
    ARKUI_OBJECT_FIT_COVER = 1,
    /**
     * 自适应显示。
     * @since 12
     */
    ARKUI_OBJECT_FIT_AUTO = 2,
    /**
     * 不保持宽高比进行放大缩小，使得图片充满显示边界。
     * @since 12
     */
    ARKUI_OBJECT_FIT_FILL = 3,
    /**
     * 保持宽高比显示，图片缩小或者保持不变。
     * @since 12
     */
    ARKUI_OBJECT_FIT_SCALE_DOWN = 4,
    /**
     * 保持原有尺寸显示。
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE = 5,
    /**
     * 图片大小不变，在image组件中顶部起始端对齐。
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_TOP_START = 6,
    /**
     * 图片大小不变，在image组件中顶部横向居中对齐。
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_TOP = 7,
    /**
     * 图片大小不变，在image组件中顶部尾端对齐。
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_TOP_END = 8,
    /**
     * 图片大小不变，在image组件中起始端纵向居中对齐。
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_START = 9,
    /**
     * 图片大小不变，在image组件中横向和纵向居中对齐。
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_CENTER = 10,
    /**
     * 图片大小不变，在image组件中尾端纵向居中对齐。
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_END = 11,
    /**
     * 图片大小不变，在image组件中底部起始端对齐。
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_BOTTOM_START = 12,
    /**
     * 图片大小不变，在image组件中底部横向居中对齐。
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_BOTTOM = 13,
    /**
     * 图片大小不变，在image组件中底部尾端对齐。
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_BOTTOM_END = 14,
    /**
     * 不改变图像原始大小，需要配合{@link ArkUI_NodeAttributeType}中的NODE_IMAGE_IMAGE_MATRIX使用。
     * @since 21
     */
    ARKUI_OBJECT_FIT_NONE_MATRIX = 15
} ArkUI_ObjectFit;
/**
 * @brief 定义图片插值效果。用于优化图片缩放时的锯齿问题。SVG类型图源不支持该属性。
 *
 * @since 12
 */
typedef enum {
    /**
     * 不使用图片插值。
     * @since 12
     */
    ARKUI_IMAGE_INTERPOLATION_NONE = 0,
    /**
     * 低图片插值。
     * @since 12
     */
    ARKUI_IMAGE_INTERPOLATION_LOW = 1,
    /**
     * 中图片插值。
     * @since 12
     */
    ARKUI_IMAGE_INTERPOLATION_MEDIUM = 2,
    /**
     * 高图片插值，插值质量最高。
     * @since 12
     */
    ARKUI_IMAGE_INTERPOLATION_HIGH = 3
} ArkUI_ImageInterpolation;
/**
 * @brief 定义图像动态范围模式（例如：SDR/HDR），用于控制图像的明暗与色彩显示范围。
 *
 * @since 21
 */
typedef enum {
    /**
     * 高动态范围（High Dynamic Range，简称HDR），表示图片中显示亮度（brightness）的最小值和最大值的范围，范围越大图像的亮度表达更逼近真实环境，在太亮的环境下不会产生过曝（一片白），
     * 太暗的环境下不会产生过暗的效果（一片黑）。
     * @since 21
     */
    ARKUI_DYNAMIC_RANGE_MODE_HIGH = 0,
    /**
     * 受限的高动态范围，包含比SDR更丰富的亮度和色彩，但不是完整的HDR，一般用于需要兼容SDR的情况。
     * @since 21
     */
    ARKUI_DYNAMIC_RANGE_MODE_CONSTRAINT = 1,
    /**
     * 标准动态范围（Standard Dynamic Range，简称SDR），表示亮度范围有限，一般在0~100尼特（亮度单位）左右，明暗对比度较小，暗部容易糊成黑，亮部容易过曝。
     * @since 21
     */
    ARKUI_DYNAMIC_RANGE_MODE_STANDARD = 2
} ArkUI_DynamicRangeMode;

/**
 * @brief 定义图像旋转方向。
 *
 * @since 21
 */
typedef enum {
    /**
     * 读取图片携带的EXIF元数据作为显示方向，支持旋转和镜像。EXIF（Exchangeable image file format）是专门为数码相机的照片设定的文件格式，可以记录数码照片的属性信息和拍摄数据。
     * @since 21
     */
    ARKUI_ORIENTATION_AUTO = 0,
    /**
     * 默认按照当前图片的像素数据进行显示，不做任何处理。
     * @since 21
     */
    ARKUI_ORIENTATION_UP = 1,
    /**
     * 将当前图片顺时针旋转90度后显示。
     * @since 21
     */
    ARKUI_ORIENTATION_RIGHT = 2,
    /**
     * 将当前图片顺时针旋转180度后显示。
     * @since 21
     */
    ARKUI_ORIENTATION_DOWN = 3,
    /**
     * 将当前图片顺时针旋转270度后显示。
     * @since 21
     */
    ARKUI_ORIENTATION_LEFT = 4,
    /**
     * 将当前图片水平翻转后显示。
     * @since 21
     */
    ARKUI_ORIENTATION_UP_MIRRORED = 5,
    /**
     * 将当前图片水平翻转再顺时针旋转90度后显示。
     * @since 21
     */
    ARKUI_ORIENTATION_RIGHT_MIRRORED = 6,
    /**
     * 将当前图片垂直翻转后显示。
     * @since 21
     */
    ARKUI_ORIENTATION_DOWN_MIRRORED = 7,
    /**
     * 将当前图片水平翻转再顺时针旋转270度后显示。
     * @since 21
     */
    ARKUI_ORIENTATION_LEFT_MIRRORED = 8
} ArkUI_ImageRotateOrientation;

/**
 * @brief 定义图片渲染模式。
 *
 * @since 12
 */
typedef enum {
    /**
     * 原色渲染模式。
     * @since 12
     */
    ARKUI_IMAGE_RENDER_MODE_ORIGINAL = 0,
    /**
     * 黑白渲染模式。
     * @since 12
     */
    ARKUI_IMAGE_RENDER_MODE_TEMPLATE = 1
} ArkUI_ImageRenderMode;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_H
/** @} */
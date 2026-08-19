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
 * @Syscap SystemCapability.Multimedia.Image.Core
 * @since 8
 * @version 1.0
 */

/**
 * @file image_pixel_map_napi.h
 *
 * @brief 声明可以锁定并访问pixelmap数据的方法，声明解锁的方法。
 *
 * @kit ImageKit
 * @include <multimedia/image_framework/image_pixel_map_napi.h>
 * @since 8
 * @version 1.0
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PIXEL_MAP_NAPI_H_
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PIXEL_MAP_NAPI_H_
#include <stdint>
#include "napi/native_api.h"
namespace OHOS {
namespace Media {
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 函数方法返回值的错误码的枚举。
 *
 * @deprecated since 10
 * @since 8
 * @version 1.0
 */
enum {
    /** 成功的结果。 */
    OHOS_IMAGE_RESULT_SUCCESS = 0,
    /** 无效值。 */
    OHOS_IMAGE_RESULT_BAD_PARAMETER = -1,
};

/**
 * @brief 像素格式的枚举。
 *
 * @deprecated since 10
 * @since 8
 * @version 1.0
 */
enum {
    /**
     * 未知的格式。
     */
    OHOS_PIXEL_MAP_FORMAT_NONE = 0,
    /**
     * RGBA_8888格式。
     */
    OHOS_PIXEL_MAP_FORMAT_RGBA_8888 = 3,
    /**
     * RGB_565格式。
     */
    OHOS_PIXEL_MAP_FORMAT_RGB_565 = 2,
};

/**
 * @brief 用于定义PixelMap的相关信息。
 *
 * @deprecated since 10
 * @since 8
 * @version 1.0
 */
struct OhosPixelMapInfo {
    /** 图片的宽，用pixels表示。 */
    uint32_t width;
    /** 图片的高，用pixels表示。 */
    uint32_t height;
    /**
      * @brief 图片在内存中，每行所占的字节数。\n
      * DMA内存为图片的宽 \* 每个像素字节数 + 每行末尾填充字节数；其他内存为图片的宽 \* 每个像素字节数。
      */
    uint32_t rowSize;
    /**
      * @brief Pixel的格式，取值范围：\n
      * 0：未知格式。\n
      * 2：格式为RGB_565。\n
      * 3：格式为RGBA_8888。\n
      * 4：格式为BGRA_8888。\n
      * 5：格式为RGB_888。\n
      * 6：格式为ALPHA_8。\n
      * 7：格式为RGBA_F16。\n
      * 8：格式为NV21。\n
      * 9：格式为NV12。
      */
    int32_t pixelFormat;
};

/**
 * @brief PixelMap缩放类型的枚举。
 *
 * @since 10
 * @version 2.0
 */
enum {
    /**
     * 适应目标图片大小的格式。
     */
    OHOS_PIXEL_MAP_SCALE_MODE_FIT_TARGET_SIZE = 0,
    /**
     * 以中心进行缩放的格式。
     */
    OHOS_PIXEL_MAP_SCALE_MODE_CENTER_CROP = 1,
};

/**
 * @brief 获取PixelMap的信息，并记录信息到{@link OhosPixelMapInfo}结构中。
 *
 * @deprecated since 10
 * @param env napi的环境指针。
 * @param value 应用层的PixelMap对象。
 * @param info 用于保存信息的指针对象。
 * @return 错误码：\n
 * OHOS_IMAGE_RESULT_SUCCESS：操作成功。\n
 * OHOS_IMAGE_RESULT_BAD_PARAMETER：操作失败。
 * @since 8
 * @version 1.0
 */
int32_t OH_GetImageInfo(napi_env env, napi_value value, OhosPixelMapInfo *info);

/**
 * @brief 获取PixelMap对象数据的内存地址，并锁定该内存。\n
 *
 * 函数执行成功后，\*addrPtr就是获取的待访问的内存地址。访问操作完成后，必须要使用{@link OH_UnAccessPixels}来释放锁，否则的话资源无法被释放。
 * 待解锁后，内存地址就不可以再被访问和操作。
 *
 * @deprecated since 10
 * @param env napi的环境指针。
 * @param value 应用层的PixelMap对象。
 * @param addrPtr 用于指向的内存地址的双指针对象。
 * @return 错误码：\n
 * OHOS_IMAGE_RESULT_SUCCESS：操作成功。\n
 * OHOS_IMAGE_RESULT_BAD_PARAMETER：操作失败。
 * @since 8
 * @version 1.0
 */
int32_t OH_AccessPixels(napi_env env, napi_value value, void** addrPtr);

/**
 * @brief 释放PixelMap对象数据的内存锁，用于匹配方法{@link OH_AccessPixels}。
 *
 * @deprecated since 10
 * @param env napi的环境指针。
 * @param value 应用层的PixelMap对象。
 * @return 错误码：\n
 * OHOS_IMAGE_RESULT_SUCCESS：操作成功。\n
 * OHOS_IMAGE_RESULT_BAD_PARAMETER：操作失败。
 * @since 8
 * @version 1.0
 */
int32_t OH_UnAccessPixels(napi_env env, napi_value value);

#ifdef __cplusplus
};
#endif
/** @} */
} // namespace Media
} // namespace OHOS
#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PIXEL_MAP_NAPI_H_

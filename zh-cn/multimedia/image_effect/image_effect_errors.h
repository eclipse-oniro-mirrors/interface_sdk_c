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
 * @file image_effect_errors.h
 *
 * @brief 声明图片效果器错误码。
 *
 * @library libimage_effect.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */

#ifndef NATIVE_IMAGE_EFFECT_ERRORS_H
#define NATIVE_IMAGE_EFFECT_ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 效果器错误码。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef enum ImageEffect_ErrorCode {
    /**
     * 操作成功。
     */
    EFFECT_SUCCESS = 0,
    /**
     * 权限校验失败。
     */
    EFFECT_ERROR_PERMISSION_DENIED = 201,
    /**
     * 参数检查失败。
     */
    EFFECT_ERROR_PARAM_INVALID = 401,
    /**
     * 输出buffer尺寸不匹配。
     */
    EFFECT_BUFFER_SIZE_NOT_MATCH = 29000001,
    /**
     * 输入输出色彩空间不匹配。
     */
    EFFECT_COLOR_SPACE_NOT_MATCH = 29000002,
    /**
     * 输入输出配置不一致。比如：输入Surface，输出Pixelmap。
     */
    EFFECT_INPUT_OUTPUT_NOT_MATCH = 29000101,
    /**
     * 超出管线最大规格。
     */
    EFFECT_EFFECT_NUMBER_LIMITED = 29000102,
    /**
     * 输入、输出配置不支持。
     */
    EFFECT_INPUT_OUTPUT_NOT_SUPPORTED = 29000103,
    /**
     * 申请内存失败。
     */
    EFFECT_ALLOCATE_MEMORY_FAILED = 29000104,
    /**
     * 参数值错误。 例如：滤镜无效的参数值。
     */
    EFFECT_PARAM_ERROR = 29000121,
    /**
     * 参数错误。例如：滤镜无效的参数。
     */
    EFFECT_KEY_ERROR = 29000122,
    /**
     * 未定义错误。
     */
    EFFECT_UNKNOWN = 29000199,
} ImageEffect_ErrorCode;

#ifdef __cplusplus
}
#endif
#endif // NATIVE_IMAGE_EFFECT_ERRORS_H
/** @} */
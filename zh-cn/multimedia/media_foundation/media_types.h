/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup Core
 * @{
 *
 * @brief Core模块提供用于媒体系统的基础骨干能力，包含内存、错误码、媒体数据结构等相关函数。
 *
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 */

/**
 * @file media_types.h
 *
 * @brief 声明了常见媒体类型的定义。
 *
 * @kit AVCodecKit
 * @include <multimedia/player_framework/media_types.h>
 * @library libnative_media_core.so
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 18
 */

#ifndef MEDIA_TYPES_H
#define MEDIA_TYPES_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief HDR类型枚举。
 *
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 18
 */
typedef enum OH_Core_HdrType {
    /**
     * 此选项用于标记非HDR类型。
     */
    OH_CORE_HDR_TYPE_NONE = 0,
    /**
     * 此选项用于标记HDR Vivid类型。
     */
    OH_CORE_HDR_TYPE_VIVID = 1,
} OH_Core_HdrType;

#ifdef __cplusplus
}
#endif

#endif // MEDIA_TYPES_H
/** @} */

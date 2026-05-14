/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup AVMediaBase
 * @{
 *
 * @brief Defines the structure and enumeration for AVMedia.
 *
 * @since 23
 */
/**
 * @file avmedia_base.h
 * 
 * @brief Defines the struct and enum of **AVMedia**.
 * 
 * @kit MediaKit
 * @library libavmedia_base.so
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 23
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMEDIA_BASE_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMEDIA_BASE_H

#include "avmetakeys.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the mappings between time points and frames.
 * 
 * @since 23
 */
 typedef enum OH_AVMedia_SeekMode {
    /**
     * The key frame at or next to the specified time is selected.
     */
    OH_AVMEDIA_SEEK_NEXT_SYNC = 0,

    /**
     * The key frame at or prior to the specified time is selected.
     */
    OH_AVMEDIA_SEEK_PREVIOUS_SYNC = 1,

    /**
     * The key frame closest to the specified time is selected.
     */
    OH_AVMEDIA_SEEK_CLOSEST_SYNC = 2,

    /**
     * The frame (not necessarily a key frame) closest to the specified time is selected.
     */
    OH_AVMEDIA_SEEK_CLOSEST = 3,
} OH_AVMedia_SeekMode;

#ifdef __cplusplus
}
#endif
#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMEDIA_BASE_H
/** @} */

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
 * @addtogroup Core
 * @{
 *
 * @brief Core模块提供用于媒体系统的基础骨干能力，包含内存、错误码、媒体数据结构等相关函数。
 *
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 */


/**
 * @file native_avmemory.h
 *
 * @brief 声明了媒体数据结构AVMemory的定义。
 *
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avmemory.h>
 * @library libnative_media_core.so
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 */

#ifndef NATIVE_AVMEMORY_H
#define NATIVE_AVMEMORY_H

#include <stdint.h>
#include "native_averrors.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 为音视频内存接口定义native层对象。
 * @since 9
 */
typedef struct OH_AVMemory OH_AVMemory;

/**
 * @brief 创建OH_AVMemory实例的指针。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param size 创建内存的大小，单位字节。
 * @return 如果创建成功，返回OH_AVMemory实例的指针，如果失败，返回NULL。
 * 使用结束后需要通过OH_AVMemory_Destroy释放内存。\n
 * 可能的失败原因：\n
 * 1. size <= 0。\n
 * 2. 创建OH_AVMemory失败。\n
 * 3.OH_AVMemory内存分配失败。
 * @deprecated since 11
 * @useinstead {@link OH_AVBuffer_Create}
 * @since 10
 */
OH_AVMemory *OH_AVMemory_Create(int32_t size);

/**
 * @brief 获取内存虚拟地址。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param mem 指向OH_AVMemory实例的指针。
 * @return 如果内存有效，返回内存的虚拟地址，如果内存无效，返回NULL。\n
 * 可能的失败原因：\n
 * 1. 输入mem为空指针。\n
 * 2. 输入mem参数结构校验失败。\n
 * 3. 输入mem中内存为空指针。
 * @deprecated since 11
 * @useinstead {@link OH_AVBuffer_GetAddr}
 * @since 9
 * @version 1.0
 */
uint8_t *OH_AVMemory_GetAddr(struct OH_AVMemory *mem);

/**
 * @brief 获取内存长度。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param mem 指向OH_AVMemory实例的指针。
 * @return 如果内存有效，返回内存长度，如果内存无效，返回-1。\n
 * 可能的失败原因：\n
 * 1. 输入mem为空指针。\n
 * 2. 输入mem参数结构校验失败。\n
 * 3.输入mem中内存为空指针。
 * @deprecated since 11
 * @useinstead {@link OH_AVBuffer_GetCapacity}
 * @since 9
 * @version 1.0
 */
int32_t OH_AVMemory_GetSize(struct OH_AVMemory *mem);

/**
 * @brief 释放OH_AVMemory实例指针的资源。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param mem 指向OH_AVMemory实例的指针。
 * @return AV_ERR_OK：释放成功。\n
 * AV_ERR_INVALID_VAL：\n
 * 1. 输入mem为空指针。\n
 * 2. 输入mem参数结构校验失败。\n
 * 3. 输入mem不是开发者创建的。
 * @deprecated since 11
 * @useinstead {@link OH_AVBuffer_Destroy}
 * @since 10
 */
OH_AVErrCode OH_AVMemory_Destroy(struct OH_AVMemory *mem);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVMEMORY_H

/** @} */

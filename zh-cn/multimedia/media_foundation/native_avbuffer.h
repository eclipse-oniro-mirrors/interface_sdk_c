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
 * @file native_avbuffer.h
 *
 * @brief 声明了媒体数据结构AVBuffer的函数接口。
 * @sample [AVCodec](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/BasicFeature/Media/AVCodec)
 * 
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avbuffer.h>
 * @library libnative_media_core.so
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 11
 */

#ifndef NATIVE_AVBUFFER_H
#define NATIVE_AVBUFFER_H

#include <stdint.h>
#include <stdio.h>
#include "native_averrors.h"
#include "native_avformat.h"
#include "native_avbuffer_info.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 为媒体内存接口定义native层对象。
 * @since 11
 */
typedef struct OH_AVBuffer OH_AVBuffer;
/**
 * @brief 为图形内存接口定义native层对象。
 * @since 11
 */
typedef struct OH_NativeBuffer OH_NativeBuffer;

/**
 * @brief 创建OH_AVBuffer实例。
 * 需要注意的是，返回值指向的创建OH_AVBuffer的实例需要开发者主动调用接口释放，请参阅{@link OH_AVBuffer_Destroy}。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param capacity 创建内存的大小，单位字节。
 * @return 如果创建成功，则返回OH_AVBuffer实例的指针，如果失败，则返回NULL。\n
 * 可能的失败原因：\n
 * 1.capacity <= 0。\n
 * 2.出现内部错误，系统没有资源等。
 * @since 11
 */
OH_AVBuffer *OH_AVBuffer_Create(int32_t capacity);

/**
 * @brief 释放OH_AVBuffer实例指针的资源，同一个buffer不允许重复销毁。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param buffer 指向OH_AVBuffer实例的指针。
 * @return AV_ERR_OK：操作成功。\n
 * AV_ERR_INVALID_VAL：输入的buffer为空指针或者buffer格式校验失败。\n
 * AV_ERR_OPERATE_NOT_PERMIT：输入的buffer不是用户创建的。
 * @since 11
 */
OH_AVErrCode OH_AVBuffer_Destroy(OH_AVBuffer *buffer);

/**
 * @brief 获取数据缓冲区的pts、size、offset、flags高频属性参数。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param buffer 指向OH_AVBuffer实例的指针。
 * @param attr 指向OH_AVCodecBufferAttr实例的指针。
 * @return AV_ERR_OK：操作成功。\n
 * AV_ERR_INVALID_VAL：可能的原因：\n
 * 1. 输入的buffer或attr为空指针。\n
 * 2. buffer结构校验失败。
 * @since 11
 */
OH_AVErrCode OH_AVBuffer_GetBufferAttr(OH_AVBuffer *buffer, OH_AVCodecBufferAttr *attr);

/**
 * @brief 设置数据缓冲区的pts、size、offset、flags高频属性参数。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param buffer 指向OH_AVBuffer实例的指针。
 * @param attr 指向OH_AVCodecBufferAttr实例的指针。
 * @return AV_ERR_OK：操作成功。\n
 * AV_ERR_INVALID_VAL：可能的原因：\n
 * 1. 输入的buffer或attr为空指针。\n
 * 2. buffer结构校验失败。\n
 * 3. 输入buffer中内存的size或offset是无效值。
 * @since 11
 */
OH_AVErrCode OH_AVBuffer_SetBufferAttr(OH_AVBuffer *buffer, const OH_AVCodecBufferAttr *attr);

/**
 * @brief 获取除基础属性外的其他参数，信息在OH_AVFormat中承载。
 * 需要注意的是，返回值指向的创建OH_AVFormat的实例需要开发者主动释放，请参阅{@link OH_AVFormat_Destroy}。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param buffer 指向OH_AVBuffer实例的指针。
 * @return AV_ERR_OK：操作成功。\n
 * AV_ERR_INVALID_VAL：可能的原因：\n
 * 1. 输入的buffer为空指针。\n
 * 2. 输入buffer的meta为空指针。\n
 * 3. buffer结构校验失败。
 * @since 11
 */
OH_AVFormat *OH_AVBuffer_GetParameter(OH_AVBuffer *buffer);

/**
 * @brief 设置除基础属性外的其他参数，信息在OH_AVFormat中承载。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param buffer 指向OH_AVBuffer实例的指针。
 * @param format 指向OH_AVFormat实例的指针。
 * @return AV_ERR_OK：操作成功。\n
 * AV_ERR_INVALID_VAL：可能的原因：\n
 * 1. 输入的buffer或format为空指针。\n
 * 2. 输入buffer的meta为空指针。\n
 * 3. buffer结构校验失败。
 * @since 11
 */
OH_AVErrCode OH_AVBuffer_SetParameter(OH_AVBuffer *buffer, const OH_AVFormat *format);

/**
 * @brief 获取数据缓冲区的虚拟地址。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param buffer 指向OH_AVBuffer实例的指针。
 * @return 如果成功，则返回数据缓冲区的虚拟地址，如果失败，则返回NULL。\n
 * 可能的失败原因：\n
 * 1.输入的buffer为空指针。\n
 * 2.OH_AVBuffer结构校验失败。\n
 * 3.出现内部错误。
 * @since 11
 */
uint8_t *OH_AVBuffer_GetAddr(OH_AVBuffer *buffer);

/**
 * @brief 获取数据缓冲区的容量（字节数）。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param buffer 指向OH_AVBuffer实例的指针。
 * @return 如果成功，则返回数据缓冲区的容量，如果失败，则返回-1。\n
 * 可能的失败原因：\n
 * 1.输入的buffer为空指针。\n
 * 2.OH_AVBuffer结构校验失败。\n
 * 3.出现内部错误。
 * @since 11
 */
int32_t OH_AVBuffer_GetCapacity(OH_AVBuffer *buffer);

/**
 * @brief 获取OH_NativeBuffer实例的指针。
 * 需要注意的是，返回值指向的创建OH_NativeBuffer的实例需要开发者主动调用接口释放，请参阅{@link OH_NativeBuffer_Unreference}。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @param buffer 指向OH_AVBuffer实例的指针。
 * @return 如果成功，则返回OH_NativeBuffer实例的指针，如果失败，则返回NULL。\n
 * 可能的失败原因：\n
 * 1.输入的buffer为空指针。\n
 * 2.OH_AVBuffer结构校验失败。\n
 * 3.出现内部错误。
 * @since 11
 */
OH_NativeBuffer *OH_AVBuffer_GetNativeBuffer(OH_AVBuffer *buffer);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVBUFFER_H

/** @} */
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup NativeFence
 * @{
 *
 * @brief 定义获取和使用NativeFence的相关函数。
 *
 * @since 20
 * @version 1.0
 */

/**
 * @file native_fence.h
 *
 * @brief 定义获取和使用NativeFence的相关函数。
 *
 * @kit ArkGraphics2D
 * @library libnative_fence.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @since 20
 * @version 1.0
 */

#ifndef NDK_INCLUDE_NATIVE_FENCE_H_
#define NDK_INCLUDE_NATIVE_FENCE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 检查fenceFd是否有效。
 *
 * @param fenceFd 表示一个文件描述符，用于定时同步。
 * @return 返回true表示fenceFd有效，返回false表示该值是一个负整数。
 * @since 20
 * @version 1.0
 */
bool OH_NativeFence_IsValid(int fenceFd);

/**
 * @brief 阻塞传入的fenceFd。最大阻塞时间由超时参数决定。传入的fenceFd需要用户自己关闭。
 *
 * @param fenceFd 表示一个文件描述符，用于定时同步。
 * @param timeout 表示等待时间。单位为毫秒，0表示接口立即返回。
 * @return 返回true表示对应的fenceFd有信号触发；\n
 *         在以下情况会返回false：\n
 *         1.传入的fenceFd为负整数。\n
 *         2.在指定的超时时间内无信号触发。\n
 *         3.调用底层poll接口失败。\n
 *         4.超时时间设置为0。\n
 *         5.接口中复制文件描述符执行失败。
 * @since 20
 * @version 1.0
 */
bool OH_NativeFence_Wait(int fenceFd, uint32_t timeout);

/**
 * @brief 永久阻塞传入的fenceFd。传入的fenceFd需要用户自己关闭。
 *
 * @param fenceFd 表示一个文件描述符，用于定时同步。
 * @return 返回true表示对应的fenceFd有信号触发；\n
 *         在以下情况会返回false：\n
 *         1.传入的fenceFd为负整数。\n
 *         2.在指定的超时时间内无信号触发，永久等待。\n
 *         3.接口中复制文件描述符执行失败。
 * @since 20
 * @version 1.0
 */
bool OH_NativeFence_WaitForever(int fenceFd);

/**
 * @brief 关闭fenceFd。
 *
 * @param fenceFd 表示一个文件描述符，用于定时同步。该值是一个非负整数。
 * @since 20
 * @version 1.0
 */
void OH_NativeFence_Close(int fenceFd);
#ifdef __cplusplus
}
#endif
/** @} */
#endif
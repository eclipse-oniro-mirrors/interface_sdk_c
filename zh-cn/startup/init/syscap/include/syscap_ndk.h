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
 * @addtogroup SyscapNdk
 * @{
 *
 * @brief Provides APIs for querying system capabilities.
 *
 * @since 8
 */

/**
 * @file syscap_ndk.h
 * @include  <syscap_ndk.h>
 * @kit BasicServicesKit
 * @brief 查询单个系统能力（SystemCapability）是否被支持的API。开发者可在运行时查询设备是否支持特定系统能力，实现差异化功能适配。
 * 典型使用场景包括：针对不同设备型号适配功能、特性降级开关控制、条件功能分支判断等。该API具有轻量级、高效的特点，能帮助开发者避免因调用设备不支持的API而导致的崩溃问题，提高应用在不同设备上的兼容性和稳定性。
 * @library NA
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 8
 */

#ifndef SYSCAP_NDK_H
#define SYSCAP_NDK_H

#include <stdbool.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief 返回指定的系统能力是否被支持。返回true表示支持，返回false表示不支持。cap参数为系统能力名称，格式为"SystemCapability.xxx.xxx"。
 * <br>系统能力（SystemCapability，简称 SysCap），指操作系统中每一个相对独立的特性。不同的设备对应不同的系统能力集，每个系统能力对应一个或多个API。开发者可根据系统能力来判断是否可以使用对应的API。
 * @param cap 待查询的系统能力名称。
 * @return 查询指定的系统能力是否被支持。
 *     <br>系统能力（SystemCapability，简称SysCap），指操作系统中每一个相对独立的特性。不同的设备对应不同的系统能力集，每个系统能力对应一个或多个API。开发者可根据系统能力来判断是否可以使用某接口。
 * @since 8
 */
bool canIUse(const char *cap);

#ifdef __cplusplus
#if __cplusplus
}
#endif // #if __cplusplus
#endif // #ifdef __cplusplus
#endif
/** @} */

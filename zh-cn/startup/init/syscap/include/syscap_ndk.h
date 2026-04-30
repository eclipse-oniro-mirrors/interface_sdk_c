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
 * @since 10
 */

/**
 * @file syscap_ndk.h
 * @kit BasicServicesKit
 * @brief Declares APIs for acquiring the set of system capabilities .
 * @library NA
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
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
 * @brief 查询单个系统能力是否被支持的API。
 * @param cap SystemCapability whether supported
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
#endif // SYSCAP_NDK_H
/** @} */

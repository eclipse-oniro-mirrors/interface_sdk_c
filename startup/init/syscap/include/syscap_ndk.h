/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
 * @brief Provides the API for querying whether a SystemCapability (SysCap) is supported.
 * SysCap refers to a standalone feature in the operating system.
 * Different devices support different SysCap sets. Each SysCap corresponds to one or more APIs.
 * You can determine whether an API can be used by checking SysCap support.
 * @param cap SystemCapability whether supported
 * @return Checks whether a SysCap is supported.
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

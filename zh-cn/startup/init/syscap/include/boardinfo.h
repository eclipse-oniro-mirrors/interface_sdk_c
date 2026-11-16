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
/*
 *@addtogroup BoardInfo
 *@{
 *
 * @brief Provides APIs for query hardware device information.
 * 
 * @since 26.0.1
 */
/*
 * @file boardinfo.h
 * @brief Declares the APIs for query hardware device information.
 * @kit BasicServiceKit
 * 
 * @library libboardinfo_ndk.z.so
 * @syscap SystemCapability.Startup.BoardInfo
 * @since 26.0.1
 */

#ifndef DEVICEINFO_CSDK_H
#define DEVICEINFO_CSDK_H

#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief 获取设备CPUID。
 *
 * @return 返回设备CPUID。字符串类型。
 *
 * @since 26.1.0
 */
const char *OH_BoardInfo_GetCpuId(void);
 
/**
 * @brief 获取设备Sn.value len为16。
 *
 * **所需权限**:ohos.permission.ACCESS_BOARD_INFO
 *
 * @param boardSn 【out】 单板序列号。
 *
 * @return <ul>
 *    <li>如果操作成功，则返回0。</li>
 *    <li>201如果调用者没有ohos.permission.ACCESS_BOARD_INFO。</li>
 *    <li>401如果调用者传入的入参为空或非法。</li>
 *    </ul>
 * @permission ohos.permission.ACCESS_BOARD_INFO
 * @since 26.1.0
 */
int32_t OH_BoardInfo_GetBoardSn(char *boardSn);

#ifdef __cplusplus
#if __cplusplus
}
#endif // #if __cplusplus
#endif // #ifdef __cplusplus
#endif // DEVICEINFO_CSDK_H
/** @} */
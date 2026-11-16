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
 * @library libdeviceinfo_ndk.z.so
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
 * @brief Obtains the device CPUID.
 *
 * @return Returns a device CPUID. The value is of the string type.
 * @since 26.1.0
 */
const char *OH_BoardInfo_GetCpuId(void);
 
/**
 * @brief Obtains the device Board Sn.value len is 16.
 *
 * **Required permission**:ohos.permission.ACCESS_BOARD_INFO
 *
 * @param boardSn [out] Board Serial Number.
 *
 * @return <ul>
 *         <li>0 if the operation is successful.</li>
 *         <li>201 if the caller does not have ohos.permission.ACCESS_BOARD_INFO.</li>
 *         <li>401 If the caller passes null or invalid parameters.</li>
 *         </ul>
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
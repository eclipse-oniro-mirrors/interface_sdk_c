/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup Telephony
 * @{
 *
 * @brief 为电话蜂窝数据定义C接口。
 *
 * @since 13
 */

/**
 * @file telephony_data.h
 *
 * @brief 为电话蜂窝数据定义C接口。
 *
 * @kit TelephonyKit
 * @syscap SystemCapability.Telephony.CellularData
 * @library libtelephony_data.so
 * @since 13
 */

#ifndef NATIVE_TELEPHONY_DATA_API_H
#define NATIVE_TELEPHONY_DATA_API_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取默认移动数据的SIM卡接口。
 *
 * @return 默认移动数据的SIM卡接口 (0 表示卡槽1, 1 表示卡槽2)。
 * @syscap SystemCapability.Telephony.CellularData
 * @since 13
 */
int32_t OH_Telephony_GetDefaultCellularDataSlotId(void);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // NATIVE_TELEPHONY_DATA_API_H

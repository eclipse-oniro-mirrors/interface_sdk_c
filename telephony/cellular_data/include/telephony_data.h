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
 * @brief Defines C APIs for cellular data module.
 *
 * @since 13
 */

/**
 * @file telephony_data.h
 *
 * @brief Defines C APIs for cellular data module.
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
 * @brief Obtains the default SIM card used for mobile data.
 *
 * @return Default SIM card used for mobile data. The value **0** indicates card slot 1, and the value **1** indicates
 *     card slot 2.
 * @syscap SystemCapability.Telephony.CellularData
 * @since 13
 */
int32_t OH_Telephony_GetDefaultCellularDataSlotId(void);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // NATIVE_TELEPHONY_DATA_API_H
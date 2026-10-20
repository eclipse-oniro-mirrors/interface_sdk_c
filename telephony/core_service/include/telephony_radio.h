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
 * @file telephony_radio.h
 *
 * @brief Provides C interface for the telephony radio.
 *
 * @kit TelephonyKit
 * @include <telephony/core_service/telephony_radio_type.h>
 * @syscap SystemCapability.Telephony.CoreService
 * @library libtelephony_radio.so
 * @since 13
 */

#ifndef NATIVE_TELEPHONY_RADIO_API_H
#define NATIVE_TELEPHONY_RADIO_API_H

#include "telephony_radio_type.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Obtains the network status.
 *
 * @param state Structure of the network status information received by the user.
 * @return Result code. For details, see {@link Telephony_RadioResult}.
 *     <br>{@link TEL_RADIO_SUCCESS}: Operation succeeded.
 *     <br>{@link TEL_RADIO_PERMISSION_DENIED}: Permission denied.
 *     <br>{@link TEL_RADIO_ERR_MARSHALLING_FAILED}: Marshalling failed.
 *     <br>{@link TEL_RADIO_ERR_SERVICE_CONNECTION_FAILED}: Telephony service connection failed.
 *     <br>{@link TEL_RADIO_ERR_OPERATION_FAILED}: Telephony service operation failed.
 *     <br>{@link TEL_RADIO_ERR_INVALID_PARAM}: Invalid parameter.
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Telephony.CoreService
 * @since 13
 */
Telephony_RadioResult OH_Telephony_GetNetworkState(Telephony_NetworkState *state);

/**
 * @brief Obtains the network status of the SIM card in the specified slot.
 *
 * @param slotId Card slot ID.
 * @param state Structure of the network status information received by the user.
 * @return Result code. For details, see {@link Telephony_RadioResult}.
 *     <br>{@link TEL_RADIO_SUCCESS}: Operation succeeded.
 *     <br>{@link TEL_RADIO_PERMISSION_DENIED}: Permission denied.
 *     <br>{@link TEL_RADIO_ERR_MARSHALLING_FAILED}: Marshalling failed.
 *     <br>{@link TEL_RADIO_ERR_SERVICE_CONNECTION_FAILED}: Telephony service connection failed.
 *     <br>{@link TEL_RADIO_ERR_OPERATION_FAILED}: Telephony service operation failed.
 *     <br>{@link TEL_RADIO_ERR_INVALID_PARAM}: Invalid parameter.
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Telephony.CoreService
 * @since 13
 */
Telephony_RadioResult OH_Telephony_GetNetworkStateForSlot(int32_t slotId, Telephony_NetworkState *state);
#ifdef __cplusplus
}
#endif

#endif // NATIVE_TELEPHONY_RADIO_API_H
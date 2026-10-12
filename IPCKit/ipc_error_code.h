/*
 * Copyright (C) 2024-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @addtogroup OHIPCErrorCode
 * @{
 *
 * @file ipc_error_code.h
 *
 * @brief Provides IPC error code definitions for identifying and handling various errors that may occur during IPC
 * communication. Based on the returned error codes, you can quickly locate the cause of issues, such as parameter
 * errors, serialization failures, memory allocation failures, and remote object death, and take appropriate error
 * handling measures.
 *
 * @include <IPCKit/ipc_error_code.h>
 * @library libipc_capi.so
 * @kit IPCKit
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */

#ifndef CAPI_INCLUDE_IPC_ERROR_CODE_H
#define CAPI_INCLUDE_IPC_ERROR_CODE_H

/**
 * @brief Enumerates the IPC error codes.
 *
 * @since 12
 */
typedef enum {
    /**
     * Execution successful.
     */
    OH_IPC_SUCCESS = 0,
    /**
     * Start of the error code range.
     */
    OH_IPC_ERROR_CODE_BASE = 1901000,
    /**
     * Parameter error. This error code is returned when the passed parameter is a null pointer, the parameter value
     * exceeds the valid range, or the parameter type does not match. You should check the validity and legality of
     * the parameters.
     */
    OH_IPC_CHECK_PARAM_ERROR = OH_IPC_ERROR_CODE_BASE,
    /**
     * Serialized object write failed. This error may occur when memory is insufficient during data serialization or the
     * data format is not supported. You should check whether the data size and format meet the requirements.
     */
    OH_IPC_PARCEL_WRITE_ERROR = OH_IPC_ERROR_CODE_BASE + 1,
    /**
     * Serialized object read failed. This error may occur when the length of the data being read exceeds the actual
     * data length or the data format does not match. You should check whether the data reading order and data
     * format are correct.
     */
    OH_IPC_PARCEL_READ_ERROR = OH_IPC_ERROR_CODE_BASE + 2,
    /**
     * Memory allocation failed. This error code is returned when the system memory is insufficient or the memory
     * allocator is abnormal. You should check memory usage, release unnecessary resources, and retry.
     */
    OH_IPC_MEM_ALLOCATOR_ERROR = OH_IPC_ERROR_CODE_BASE + 3,
    /**
     * Command word out of the defined range [0x01, 0x00FFFFFF]. This error code is returned when the command word used
     * in IPC communication is not within the valid range. You should check whether the command word definition
     * complies with the specification requirements.
     */
    OH_IPC_CODE_OUT_OF_RANGE = OH_IPC_ERROR_CODE_BASE + 4,
    /**
     * Remote object is dead. This error code is returned when the peer process of the IPC communication has exited or
     * the remote object has been destroyed. You should re-establish the connection or use an alternative service.
     */
    OH_IPC_DEAD_REMOTE_OBJECT = OH_IPC_ERROR_CODE_BASE + 5,
    /**
     * User-defined error code out of range [1909000, 1909999]. This error code is returned when the custom error code
     * set by you is not within the allowed range. You should ensure that the custom error code is within the valid
     * range.
     */
    OH_IPC_INVALID_USER_ERROR_CODE = OH_IPC_ERROR_CODE_BASE + 6,
    /**
     * IPC internal error. This error code is returned when an unknown error occurs inside the IPC system. You can log
     * the error and contact technical support or retry later.
     */
    OH_IPC_INNER_ERROR = OH_IPC_ERROR_CODE_BASE + 7,
    /**
     * Maximum error code.
     */
    OH_IPC_ERROR_CODE_MAX = OH_IPC_ERROR_CODE_BASE + 1000,
    /**
     * Minimum value for a custom error code.
     */
    OH_IPC_USER_ERROR_CODE_MIN = 1909000,
    /**
     * Maximum value for a custom error code.
     */
    OH_IPC_USER_ERROR_CODE_MAX = 1909999
} OH_IPC_ErrorCode;

/** @} */
#endif

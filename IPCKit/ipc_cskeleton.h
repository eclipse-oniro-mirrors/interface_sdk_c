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
 * @addtogroup OHIPCSkeleton
 * @{
 *
 * @brief Provides C interfaces for managing the token IDs, credentials, process IDs (PIDs),
 * user IDs (UIDs), and thread pool in the IPC framework.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
/**
 * @file ipc_cskeleton.h
 *
 * @brief Provides C APIs for managing the token IDs, credentials, process IDs (PIDs), user IDs (UIDs), and thread pool
 *     in the IPC framework.
 * 
 * @library libipc_capi.so
 * @kit IPCKit
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */

#ifndef CAPI_INCLUDE_IPC_CSKELETON_H
#define CAPI_INCLUDE_IPC_CSKELETON_H

#include <stdint.h>

#include "ipc_cparcel.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Joins this thread to the IPC worker thread pool.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
void OH_IPCSkeleton_JoinWorkThread(void);

/**
 * @brief Stops this thread.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
void OH_IPCSkeleton_StopWorkThread(void);

/**
 * @brief Obtains the token ID of the caller. This function must be called in the IPC context. Otherwise, the local
 *     token ID is returned.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns the caller token ID.
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetCallingTokenId(void);

/**
 * @brief Obtains the token ID of the first caller.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns the token ID of the first caller.
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetFirstTokenId(void);

/**
 * @brief Obtains the local token ID.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns the local token ID.
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetSelfTokenId(void);

/**
 * @brief Obtains the PID of the caller. This function must be called in the IPC context. Otherwise, the local PID is
 *     returned.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns the caller PID.
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetCallingPid(void);

/**
 * @brief Obtains the UID of the caller. This function must be called in the IPC context. Otherwise, the local UID is
 *     returned.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns the caller UID.
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetCallingUid(void);

/**
 * @brief Checks whether a local calling is being made.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns **1** if a local calling is in progress; returns **0** otherwise.
 * @since 12
 */
int OH_IPCSkeleton_IsLocalCalling(void);

/**
 * @brief Sets the maximum number of worker threads.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param maxThreadNum Maximum number of worker threads.
 *     Value range: [1, 32]
 *     Default value: **16**
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} in other cases.
 * @since 12
 */
int OH_IPCSkeleton_SetMaxWorkThreadNum(const int maxThreadNum);

/**
 * @brief Resets the caller identity credential (including the token ID, UID, and PID) to that of this process and
 *     returns the caller credential information. The credential information is used in
 *     **OH_IPCSkeleton_SetCallingIdentity**.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param identity Double pointer to the address of the memory for holding the caller identity information. The memory
 *     is allocated by the allocator provided by the user and needs to be released. This pointer cannot be NULL.
 * @param len Pointer to the length of the data written to the identity. The value cannot be empty.
 * @param allocator Memory allocator specified by the user for allocating memory for **identity**. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_MEM_ALLOCATOR_ERROR} if the memory allocation fails.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} in other cases.
 * @since 12
 */
int OH_IPCSkeleton_ResetCallingIdentity(char **identity, int32_t *len, OH_IPC_MemAllocator allocator);

/**
 * @brief Sets the caller credential information to the IPC context.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param identity Pointer to the caller credential, which cannot be empty. The value is returned by
 *     **OH_IPCSkeleton_ResetCallingIdentity**.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} in other cases.
 * @since 12
 */
int OH_IPCSkeleton_SetCallingIdentity(const char *identity);

/**
 * @brief Checks whether an IPC request is being handled.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns **1** if an IPC request is being handled; returns **0** otherwise.
 * @since 12
 */
int OH_IPCSkeleton_IsHandlingTransaction(void);

#ifdef __cplusplus
}
#endif

/** @} */
#endif

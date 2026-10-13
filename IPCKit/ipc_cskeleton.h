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
 * @file ipc_cskeleton.h
 *
 * @brief This file provides C APIs for IPC framework features such as the token ID, credentials, PID/UID, and thread
 * pool configuration. It is mainly used for context management and thread management in inter-process communication.
 *
 * @include <IPCKit/ipc_cskeleton.h>
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
 * @brief Joins the current thread to the IPC worker thread pool so that it can participate in processing IPC requests.
 * This function is applicable to scenarios where custom IPC request processing threads are needed, for example,
 * manually adding worker threads when the IPC concurrent processing capability needs to be expanded, or using
 * dedicated threads to process IPC requests in specific service scenarios to improve response speed.
 * - Call this function only in scenarios where IPC request processing is required.
 * - After this function is called, the thread blocks and waits to process IPC requests.
 * - It is recommended to use this function together with {@link OH_IPCSkeleton_StopWorkThread()} to properly exit the
 * thread pool.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
void OH_IPCSkeleton_JoinWorkThread(void);

/**
 * @brief Exits the current thread from the IPC worker thread pool so that it no longer participates in processing IPC
 * requests.
 * - Call this function when IPC request processing is no longer needed.
 * - Before calling this function, ensure that the current thread has joined the thread pool through
 * {@link OH_IPCSkeleton_JoinWorkThread()}.
 * - Ensure that all IPC transactions are completed before the thread exits.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
void OH_IPCSkeleton_StopWorkThread(void);

/**
 * @brief Obtains the token ID of the caller. This is applicable to scenarios such as permission verification and
 * identity identification on the IPC server side. Identity‑based access control can be implemented through the token
 * ID. This API must be called in the IPC context. Otherwise, the local token ID is returned.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns the caller token ID.
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetCallingTokenId(void);

/**
 * @brief Obtains the token ID of the first caller in the IPC call chain. This API must be called in the IPC context.
 * Otherwise, the local token ID is returned. This API is applicable to permission tracing and security audit scenarios
 * in multi-level service calls. For example, it can be used in permission audits where you need to trace the identity
 * of the original caller rather than the intermediate proxy service, or in cross‑process permission inheritance
 * verification to confirm the source of the original permissions.
 * - This API is meaningful only in multi-level IPC call scenarios.
 * - In single-level call scenarios, the return value is the same as that of {@link OH_IPCSkeleton_GetCallingTokenId()}.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns the token ID of the first caller.
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetFirstTokenId(void);

/**
 * @brief Obtains the token ID of the current process. This is applicable to scenarios such as process
 * self‑authentication and permission status verification. For example, it can be used to verify the permission status
 * of the process itself during service startup, to confirm whether the process has the required permissions to access
 * specific resources during permission checks, and to identify the current process identity in security audits.
 * - This function can be called in any context and does not depend on the IPC context.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns the local token ID.
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetSelfTokenId(void);

/**
 * @brief Obtains the PID of the caller. This is applicable to process-level permission control and security audit
 * scenarios, for example, checking whether the caller process is in the trustlist during whitelist verification,
 * recording caller process information in audit logs for security tracing, and making permission decisions based on
 * the PID in cross-process access control. This API must be called in the IPC context. Otherwise, the PID of the
 * current process is returned.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns the caller PID.
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetCallingPid(void);

/**
 * @brief Obtains the UID of the caller. This is applicable to user-level permission control and identity identification
 * in multi-user environments, for example, determining access permissions based on the UID in permission management,
 * isolating data access for different users in multi-user systems, and recording user identities in security audits for
 * behavior tracing. This API must be called in the IPC context. Otherwise, the ID of the current user is returned.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns the caller UID.
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetCallingUid(void);

/**
 * @brief Checks whether the current IPC call is a local call.
 * - This function must be called in the IPC context.
 * - This function is commonly used to adopt different processing strategies based on the call type.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns **1** if a local calling is in progress; returns **0** otherwise.
 * @since 12
 */
int OH_IPCSkeleton_IsLocalCalling(void);

/**
 * @brief Sets the maximum number of threads in the IPC worker thread pool to control the concurrent processing
 * capability of IPC requests.
 * - It is recommended to call this function at app startup to avoid frequent modifications at runtime.
 * - This configuration should be completed before calling {@link OH_IPCSkeleton_JoinWorkThread()} to join the worker
 * thread pool, to ensure that the thread pool works at the configured size.
 * - This configuration affects the capacity control of threads that subsequently join the thread pool.
 * - Unless there are special requirements, it is not recommended to change the maximum number of threads.
 * - Too many threads increase system resource consumption, while too few may affect IPC concurrent processing
 * performance.
 * - Set this value appropriately based on actual service scenarios and device capabilities.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param maxThreadNum Maximum number of worker threads. Default value: 16. Value range: [1, 32]. This parameter
 *     controls the IPC concurrent processing capability. A smaller value saves system resources, while a larger value
 *     improves concurrent processing efficiency. If the value is out of range, the parameter error
 *     **OH_IPC_CHECK_PARAM_ERROR** is returned.
 * @return Result code.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} (value: **0**) if the operation is successful.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} (value: **-1**) if the parameter is invalid. Possible
 *     cause: **maxThreadNum** is not within the valid range [1, 32]. Solution: Check and adjust the parameter value.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} (value: **-2**) in other cases. Possible cause: Internal
 *     exception in the IPC framework. Solution: Check the IPC service status or restart the app.
 * @since 12
 */
int OH_IPCSkeleton_SetMaxWorkThreadNum(const int maxThreadNum);

/**
 * @brief Resets the caller identity credential to the identity credential of the local process (including TokenId, UID,
 * and PID information), and returns the caller credential information. This is applicable to scenarios where you need
 * to temporarily elevate permissions or perform operations with the identity of a service process. For example, it can
 * be used to temporarily switch to a service identity when accessing protected resources in system services, or to
 * perform privileged operations on behalf of a service process in permission proxy scenarios.
 * - This function must be called in the IPC request processing context.
 * - The returned credential information must be properly managed by the caller and released after use.
 * - This function must be used in pair with {@link OH_IPCSkeleton_SetCallingIdentity()} to restore the original
 * credential after the operation is completed.
 * - Avoid maintaining the reset state for a long time, as it may affect permission verification.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param identity Pointer to the memory address for storing the calling credential. The credential contains identity
 *     information such as the caller's token ID, UID, and PID, and can be used later to restore the calling identity
 *     via {@link OH_IPCSkeleton_SetCallingIdentity()}. The memory is allocated by the user-provided allocator, and the
 *     user must release it after use. This function must be called in an IPC request processing context. This parameter
 *     cannot be null.
 * @param len Pointer to the length (in bytes) of the data written to identity. It informs the caller of the actual
 *     size of the credential data for subsequent correct use and memory release. This function must be called in an IPC
 *     request processing context. This parameter cannot be null.
 * @param allocator User-specified memory allocator used to allocate memory for **identity**. A custom allocator allows
 *     control over the memory allocation strategy (for example, using shared memory or heap memory). This function must
 *     be called in an IPC request processing context. This parameter cannot be null.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} (value: **0**) if successful.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} (value: **-1**) if the parameter is invalid. Possible
 *     cause: The **identity**, **len**, or **allocator** parameter is null. Solution: Ensure that the parameters are
 *     not null.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_MEM_ALLOCATOR_ERROR} (value: **-3**) if memory allocation fails. Possible
 *     cause: Insufficient system memory or an abnormal memory allocator. Solution: Release memory and retry, or check
 *     the memory allocator.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} (value: **-2**) in other cases. Possible cause: Internal IPC
 *     framework exception. Solution: Check the IPC service status or restart the app.
 * @since 12
 */
int OH_IPCSkeleton_ResetCallingIdentity(char **identity, int32_t *len, OH_IPC_MemAllocator allocator);

/**
 * @brief Restores the caller credential information to the IPC context. This function restores the identity credential
 * in the IPC context to the original caller credential. It must be called in the IPC request processing context. This
 * is applicable to scenarios where normal permissions are restored after temporary privilege escalation operations,
 * for example, restoring the caller identity after accessing protected resources on the server side, and restoring the
 * caller permission state after permission proxy operations are completed.
 * - After this method is called, the identity credential in the IPC context is restored to the caller credential
 * previously saved through {@link OH_IPCSkeleton_ResetCallingIdentity()}.
 * - Call this function immediately after completing operations that require the server identity.
 * - Identity credentials should be properly managed to prevent credential leakage.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param identity Caller identity, which cannot be null. This value comes from the return value of
 *     **OH_IPCSkeleton_ResetCallingIdentity**. It must be used in pairs with OH_IPCSkeleton_ResetCallingIdentity.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} in other cases.
 * @since 12
 */
int OH_IPCSkeleton_SetCallingIdentity(const char *identity);

/**
 * @brief Checks whether an IPC request is being processed. This is applicable to scenarios where conditional judgment
 * is needed based on the current IPC processing status, such as avoiding re-entry and status checks.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Whether an IPC request is being processed. The value **1** indicates that an IPC request is being processed,
 *     and **0** indicates that no IPC request is being processed.
 * @since 12
 */
int OH_IPCSkeleton_IsHandlingTransaction(void);

#ifdef __cplusplus
}
#endif

/** @} */
#endif

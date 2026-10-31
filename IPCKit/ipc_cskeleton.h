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
 * @brief The **ipc_cskeleton.h** module provides C APIs for managing the token IDs, credentials, process IDs (PIDs),
 * user IDs (UIDs), and thread pool in the IPC framework. These APIs are mainly used for context and thread management
 * in inter-process communication.
 */
/**
 * @file ipc_cskeleton.h
 *
 * @brief The **ipc_cskeleton.h** module provides C APIs for managing the token IDs, credentials, process IDs (PIDs),
 * user IDs (UIDs), and thread pool in the IPC framework. These APIs are mainly used for context and thread management
 * in inter-process communication.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @include <IPCKit/ipc_cskeleton.h>
 * @library libipc_capi.so
 * @kit IPCKit
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
 * @brief Joins this thread to the IPC worker thread pool so that it can process IPC requests. This function is
 * applicable to scenarios where you need to customize the thread for processing IPC requests. For example, you can
 * manually add worker threads when you need to expand the concurrent IPC processing capability, or you can use
 * dedicated threads to process IPC requests in specific service scenarios to improve the response speed. After this
 * function is called, the current thread is registered as an IPC worker thread and participates in processing IPC
 * requests from other processes until {@link OH_IPCSkeleton_StopWorkThread()} is called to exit the thread pool.
 * - This function is called only when IPC requests need to be processed.
 * - After this function is called, the thread is blocked and waits to process IPC requests.
 * - It is recommended that this function be used together with {@link OH_IPCSkeleton_StopWorkThread()} to exit the
 * thread pool correctly.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
void OH_IPCSkeleton_JoinWorkThread(void);

/**
 * @brief Stops this thread and stops processing IPC requests. After this function is called, the current thread is
 * removed from the IPC worker thread pool and will no longer be assigned tasks to process IPC requests. The thread can
 * then perform other operations.
 * - This function should be called when IPC requests no longer need to be processed.
 * - Before calling this function, ensure that the current thread has been added to the thread pool by calling
 * {@link OH_IPCSkeleton_JoinWorkThread()}.
 * - When a thread exits, ensure that all IPC transactions have been processed.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
void OH_IPCSkeleton_StopWorkThread(void);

/**
 * @brief Obtains the token ID of the caller. This function is applicable to scenarios where permission verification and
 * identity identification are performed on the IPC server. Token IDs can be used to implement identity-based access
 * control. This function must be called in the IPC context. Otherwise, the local token ID is returned.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return <ul>
 *         <li>Returns the caller token ID.</li>
 *         </ul>
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetCallingTokenId(void);

/**
 * @brief Obtains the token ID of the first caller in the IPC call chain. This function must be called in the IPC
 * context. Otherwise, the local token ID is returned. This function is applicable to permission tracing and security
 * audit scenarios in multi-level service calls. For example, it is used to trace the identity of the original caller
 * instead of the intermediate proxy service in permission audit, and to confirm the original permission source in
 * cross-process permission inheritance verification. Returns the token ID of the first client that initiates the IPC
 * call.
 * - This function is meaningful only in multi-level IPC call scenarios.
 * - In single call scenarios, the return value is the same as that of {@link OH_IPCSkeleton_GetCallingTokenId()}.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return <ul>
 *         <li>Returns the token ID of the first caller.</li>
 *         </ul>
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetFirstTokenId(void);

/**
 * @brief Obtains the token ID of the current process. This function is applicable to scenarios where a process needs
 * to authenticate itself and confirm its permission status. For example, a process can verify its permission status
 * during service startup, check whether it has the permission to access specific resources during permission check,
 * and identify its identity during security audit. Returns the token ID of the current process, regardless of whether
 * the function is called in the IPC context.
 * - This function can be called in any context and does not depend on the IPC context.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return <ul>
 *         <li>Returns the local token ID.</li>
 *         </ul>
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetSelfTokenId(void);

/**
 * @brief Obtains the PID of the caller. This function is applicable to process-level permission control and security
 * audit scenarios. For example, it can be used to check whether the caller process is in the trustlist during
 * trustlist verification, record caller process information in audit logs for security tracing, and determine
 * permissions based on the process ID during cross-process access control. This function must be called in the IPC
 * context. Otherwise, the local PID is returned.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return <ul>
 *         <li>Returns the caller PID.</li>
 *         </ul>
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetCallingPid(void);

/**
 * @brief Obtains the UID of the caller. This function is applicable to user-level permission control and identity
 * identification in multi-user environments. For example, it can be used to determine access permissions based on user
 * IDs in permission management, isolate data access of different users in a multi-user system, and record user
 * identities for behavior tracing in security audits. This function must be called in the IPC context. Otherwise, the
 * local UID is returned.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return <ul>
 *         <li>Returns the caller UID.</li>
 *         </ul>
 * @since 12
 */
uint64_t OH_IPCSkeleton_GetCallingUid(void);

/**
 * @brief Checks whether the current IPC call is a local call.
 * - This function must be called in the IPC context.
 * - This function is often used to adopt different processing policies based on the calling type.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return <ul>
 *         <li>Returns **1** if a local calling is in progress; returns **0** otherwise.</li>
 *         </ul>
 * @since 12
 */
int OH_IPCSkeleton_IsLocalCalling(void);

/**
 * @brief Sets the maximum number of threads in the IPC working thread pool to control the concurrent processing
 * capability of IPC requests. After this function is called, the IPC framework manages the working threads based on
 * the configured maximum number of threads. When the number of concurrent IPC requests exceeds the number of threads,
 * the requests will be queued.
 * - It is recommended that this function be called during application startup to avoid frequent modifications during
 * runtime.
 * - This configuration must be completed before {@link OH_IPCSkeleton_JoinWorkThread()} is called to add threads to the
 * working thread pool, ensuring that the thread pool works based on the configured size.
 * - This configuration affects the capacity control of threads subsequently added to the thread pool.
 * - Unless there are special requirements, you are advised not to change the maximum number of threads.
 * - If there are too many threads, system resource consumption increases. If there are too few threads, the IPC
 * concurrent processing performance may be affected.
 * - Set this parameter based on the actual service scenario and device capability.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param maxThreadNum Maximum number of worker threads. The value range is [1, 32], and the default value is **16**.
 *     This parameter can be used to control the concurrent processing capability of the IPC. A smaller value saves
 *     system resources, and a larger value improves the concurrent processing efficiency. If the value is out of range,
 *     the **OH_IPC_CHECK_PARAM_ERROR** error is returned.
 * @return <ul>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful, corresponding to value
 *         **0**.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} (corresponding to value **-1**) if the
 *         parameter is incorrect. Possible cause: The value of **maxThreadNum** is not within the valid range [1, 32].
 *         Solution: Check and adjust the parameter value.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} in other cases, corresponding to value **-2**.
 *         Possible cause: An internal error occurs in the IPC framework. Solution: Check the IPC service status or
 *         restart the application.</li>
 *         </ul>
 * @since 12
 */
int OH_IPCSkeleton_SetMaxWorkThreadNum(const int maxThreadNum);

/**
 * @brief Resets the caller identity credential (including the token ID, UID, and PID) to that of this process and
 * returns the caller credential information. This function is applicable to scenarios where temporary permission
 * escalation is required or operations need to be performed as a service process. For example, when a system service
 * needs to access protected resources, the identity is temporarily switched to that of a service; in permission
 * delegation scenarios, privileged operations are performed on behalf of a service. After this function is called, the
 * identity credential of the current IPC context is switched to that of the calling process, and the credential
 * information of the original caller is returned for subsequent restoration.
 * - This function must be called in the IPC request processing context.
 * - The returned credential information must be properly managed by the caller and released after use.
 * - This function must be used in pair with {@link OH_IPCSkeleton_SetCallingIdentity()} to restore the original
 * credential after the operation is complete.
 * - Do not stay in the reset state for a long time, as this may affect permission verification.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param identity Double pointer to the address of the memory for holding the caller identity information such as the
 *     token ID, UID, and PID of the caller. This information can be used to restore the caller's identity by calling
 *     {@link OH_IPCSkeleton_SetCallingIdentity()}. The memory is allocated by the allocator provided by the user and
 *     needs to be released. This function must be called in the IPC request processing context. It cannot be null.
 * @param len Pointer to the length of the data written to the identity. This parameter is used to notify the caller of
 *     the actual size of the credential data so that the memory can be correctly used and deallocated later. This
 *     function must be called in the IPC request processing context. It cannot be null.
 * @param allocator Memory allocator specified by the user for allocating memory for **identity**. You can use a custom
 *     allocator to control the memory allocation policy (for example, using shared memory or heap memory). This
 *     function must be called in the IPC request processing context. It cannot be null.
 * @return <ul>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful, corresponding to value
 *         **0**.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} (corresponding to value **-1**) if the
 *         parameter is incorrect. Possible cause: The **identity**, **len**, or **allocator** parameter is null.
 *         Solution: Ensure that the parameter is not null.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_MEM_ALLOCATOR_ERROR} (corresponding to value **-3**) if memory
 *         allocation fails. Possible cause: The system memory is insufficient or the memory allocator is abnormal.
 *         Solution: Deallocate the memory and try again, or check the memory allocator.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} (corresponding to value **-2**) in other cases.
 *         Possible cause: An internal error occurs in the IPC framework. Solution: Check the IPC service status or
 *         restart the app.</li>
 *         </ul>
 * @since 12
 */
int OH_IPCSkeleton_ResetCallingIdentity(char **identity, int32_t *len, OH_IPC_MemAllocator allocator);

/**
 * @brief Sets the caller credential information to the IPC context. This function restores the identity credential of
 * the IPC context to that of the original caller. This function must be called in the IPC request processing context.
 * This function is applicable to scenarios where the normal permission needs to be restored after temporary permission
 * elevation. For example, the caller identity is restored after the protected resource access is complete on the
 * server, or the caller permission status is restored after the permission delegation operation is complete.
 * - After this function is called, the identity credentials of the IPC context are restored to the caller credentials
 * previously saved by {@link OH_IPCSkeleton_ResetCallingIdentity()}.
 * - This function should be called immediately after the operation that requires the server identity is complete.
 * - Identity credentials must be properly managed to prevent credential leaks.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param identity Pointer to the caller credential, which cannot be empty. The value is returned by
 *     {@link OH_IPCSkeleton_ResetCallingIdentity()}. This function and {@link OH_IPCSkeleton_ResetCallingIdentity()}
 *     must be used in pairs.
 * @return <ul>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} in other cases.</li>
 *         </ul>
 * @since 12
 */
int OH_IPCSkeleton_SetCallingIdentity(const char *identity);

/**
 * @brief Checks whether an IPC request is being handled. This function is applicable to scenarios where condition
 * judgment needs to be performed based on the current IPC processing status, such as avoiding reentrancy and checking
 * the status.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return <ul>
 *         <li>Returns **1** if the IPC request is being processed; returns **0** otherwise.</li>
 *         </ul>
 * @since 12
 */
int OH_IPCSkeleton_IsHandlingTransaction(void);

#ifdef __cplusplus
}
#endif

/** @} */
#endif
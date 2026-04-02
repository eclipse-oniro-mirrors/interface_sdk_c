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
 * @addtogroup OHIPCRemoteObject
 * @{
 *
 * @brief Provides C interfaces for creating and destroying a remote object, transferring data,
 *     and observing the dead status of a remote object.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
/**
 * @file ipc_cremote_object.h
 *
 * @brief Provides C APIs for creating and destroying a remote object, transferring data, and observing the dead status
 *     of a remote object.
 * 
 * @library libipc_capi.so
 * @kit IPCKit
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */

#ifndef CAPI_INCLUDE_IPC_CREMOTE_OBJECT_H
#define CAPI_INCLUDE_IPC_CREMOTE_OBJECT_H

#include <stdint.h>

#include "ipc_cparcel.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Defines an object that receives death notifications.
* 
* @syscap SystemCapability.Communication.IPC.Core
* @since 12
*/
struct OHIPCDeathRecipient;

/**
* @brief Defines an object that receives death notifications.
* 
* @syscap SystemCapability.Communication.IPC.Core
* @since 12
*/
typedef struct OHIPCDeathRecipient OHIPCDeathRecipient;

/**
 * @brief Called to process the peer request at the stub.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param code Customized communication command word.
 * Value range: [0x01, 0x00ffffff]
 * @param data Pointer to the requested data object. It cannot be NULL or released in the function.
 * @param reply Pointer to the response data object. It cannot be NULL or released in the function. If this function
 * returns an error, data cannot be written to this parameter.
 * @param userData Pointer to the private user data. It can be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 * Returns a custom error code in the range [1909001, 1909999] or a system error code otherwise.
 * If the custom error code is out of range, {@link OH_IPC_ErrorCode#OH_IPC_INVALID_USER_ERROR_CODE} is returned.
 * @since 12
 */
typedef int (*OH_OnRemoteRequestCallback)(uint32_t code, const OHIPCParcel *data,
    OHIPCParcel *reply, void *userData);

/**
 * @brief Called when an observed object is destroyed.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param userData Pointer to the private user data. It can be NULL.
 * @since 12
 */
typedef void (*OH_OnRemoteDestroyCallback)(void *userData);

/**
 * @brief Creates an **OHIPCRemoteStub** object.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param descriptor Pointer to the descriptor of the **OHIPCRemoteStub** object to create. It cannot be NULL.
 * @param requestCallback Callback used to process the data request. It cannot be NULL.
 * @param destroyCallback Callback to be invoked when the object is destroyed. It can be NULL.
 * @param userData Pointer to the private user data. It can be NULL.
 * @return Returns the pointer to the **OHIPCRemoteStub** object created if the operation is successful; returns NULL
 * otherwise.
 * @since 12
 */
OHIPCRemoteStub* OH_IPCRemoteStub_Create(const char *descriptor, OH_OnRemoteRequestCallback requestCallback,
    OH_OnRemoteDestroyCallback destroyCallback, void *userData);

/**
 * @brief Destroys an **OHIPCRemoteStub** object.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param stub Pointer to the **OHIPCRemoteStub** object to destroy.
 * @since 12
 */
void OH_IPCRemoteStub_Destroy(OHIPCRemoteStub *stub);

/**
 * @brief Destroys an **OHIPCRemoteProxy** object.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object to destroy.
 * @since 12
 */
void OH_IPCRemoteProxy_Destroy(OHIPCRemoteProxy *proxy);

/**
 * @brief Enumerates the IPC request modes.
 * 
 * @since 12
 */
typedef enum {
    /**
     * Synchronous request.
     */
    OH_IPC_REQUEST_MODE_SYNC = 0,
    /**
     * Asynchronous request.
     */
    OH_IPC_REQUEST_MODE_ASYNC = 1,
} OH_IPC_RequestMode;

/**
 * @brief Defines the IPC message options.
 *
 * @since 12
 */
#pragma pack(4)
typedef struct {
    /** Message request mode. */
    OH_IPC_RequestMode mode;
    /** Parameter reserved for RPC, which is invalid for IPC. */
    uint32_t timeout;
    /** Reserved parameter, which must be NULL. */
    void* reserved;
} OH_IPC_MessageOption;
#pragma pack()

/**
 * @brief Sends an IPC message.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object. It cannot be NULL.
 * @param code Customized IPC command word, in the range [0x01, 0x00ffffff].
 * @param data Pointer to the requested data object. It cannot be NULL.
 * @param reply Pointer to the response data object. It cannot be NULL in the case of a synchronous request, and can be
 * NULL in the case of an asynchronous request.
 * @param option Pointer to the message option. It can be NULL, which indicates a synchronous request.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the message is sent successfully.
 * Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 * Returns {@link OH_IPC_ErrorCode#OH_IPC_DEAD_REMOTE_OBJECT} if the remote **OHIPCRemoteStub** object dies.
 * Returns {@link OH_IPC_ErrorCode#OH_IPC_CODE_OUT_OF_RANGE} if the code is out of range.
 * Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} or a custom error code in other cases.
 * @since 12
 */
int OH_IPCRemoteProxy_SendRequest(const OHIPCRemoteProxy *proxy, uint32_t code, const OHIPCParcel *data,
    OHIPCParcel *reply, const OH_IPC_MessageOption *option);

/**
 * @brief Obtains the interface descriptor from the stub.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object. It cannot be NULL.
 * @param descriptor Pointer to the address of the memory for holding the interface descriptor. The memory is allocated
 * by the allocator provided by the user and needs to be released. This pointer cannot be NULL. If an error code is
 * returned, you still need to check whether the memory is empty and release the memory. Otherwise, memory leaks may
 * occur.
 * @param len Pointer to the length of the data written to the descriptor, including the terminator. It cannot be NULL.
 * @param allocator Memory allocator specified by the user for allocating memory for **identity**. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the message is sent successfully.
 * Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.
 * Returns {@link OH_IPC_ErrorCode#OH_IPC_DEAD_REMOTE_OBJECT} if the remote **OHIPCRemoteStub** object dies.
 * Returns {@link OH_IPC_ErrorCode#OH_IPC_MEM_ALLOCATOR_ERROR} if the memory allocation fails.
 * Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} or a custom error code if the data in the serialized
 * object fails to be read.
 * @since 12
 */
int OH_IPCRemoteProxy_GetInterfaceDescriptor(OHIPCRemoteProxy *proxy, char **descriptor, int32_t *len,
    OH_IPC_MemAllocator allocator);

/**
 * @brief Defines a callback to be invoked when the remote **OHIPCRemoteStub** object dies unexpectedly.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param userData Pointer to the private user data. It can be NULL.
 * @since 12
 */
typedef void (*OH_OnDeathRecipientCallback)(void *userData);

/**
 * @brief Defines a callback to be invoked when the **OHIPCDeathRecipient** object is destroyed.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param userData Pointer to the private user data. It can be NULL.
 * @since 12
 */
typedef void (*OH_OnDeathRecipientDestroyCallback)(void *userData);

/**
 * @brief Creates an **OHIPCDeathRecipient** object, which triggers a notification when the **OHIPCRemoteStub** object
 * dies unexpectedly.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param deathRecipientCallback Callback to be invoked when the **OHIPCRemoteStub** object is dead. It cannot be NULL.
 * @param destroyCallback Callback to be invoked when the object is destroyed. It can be NULL.
 * @param userData Pointer to the private user data. It can be NULL.
 * @return Returns the pointer to the **OHIPCDeathRecipient** object created if the operation is successful; returns
 * NULL otherwise.
 * @since 12
 */
OHIPCDeathRecipient* OH_IPCDeathRecipient_Create(OH_OnDeathRecipientCallback deathRecipientCallback,
    OH_OnDeathRecipientDestroyCallback destroyCallback, void *userData);

/**
 * @brief Destroys an **OHIPCDeathRecipient** object.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param recipient Pointer to the **OHIPCDeathRecipient** object to destroy.
 * @since 12
 */
void OH_IPCDeathRecipient_Destroy(OHIPCDeathRecipient *recipient);

/**
 * @brief Subscribes to the death of an **OHIPCRemoteStub** object for an **OHIPCRemoteProxy** object.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object that subscribes to the death notification. It cannot be NULL.
 * @param recipient Pointer to the object that receives the death notification of the **OHIPCRemoteStub** object. It
 * cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 * Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.
 * Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} in other cases.
 * @since 12
 */
int OH_IPCRemoteProxy_AddDeathRecipient(OHIPCRemoteProxy *proxy, OHIPCDeathRecipient *recipient);

/**
 * @brief Unsubscribes from the death of the **OHIPCRemoteStub** object for an **OHIPCRemoteProxy** object.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object that unsubscribes from the death notification. It cannot be
 * NULL.
 * @param recipient Pointer to the object that receives the death notification of the **OHIPCRemoteStub** object. It
 * cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 * Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.
 * Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} in other cases.
 * @since 12
 */
int OH_IPCRemoteProxy_RemoveDeathRecipient(OHIPCRemoteProxy *proxy, OHIPCDeathRecipient *recipient);

/**
 * @brief Checks whether the **OHIPCRemoteStub** object corresponding to the **OHIPCRemoteProxy** object is dead.
 * 
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object to check. It cannot be NULL.
 * @return Returns **1** if the **OHIPCRemoteStub** object is dead or invalid parameters are found; returns **0**
 * otherwise. If invalid parameters are found, the **OHIPCRemoteStub** object does not exist.
 * @since 12
 */
int OH_IPCRemoteProxy_IsRemoteDead(const OHIPCRemoteProxy *proxy);

#ifdef __cplusplus
}
#endif

/** @} */
#endif

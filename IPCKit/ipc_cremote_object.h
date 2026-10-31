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
 * @brief This file provides C APIs for remote object creation, destruction, data sending, and remote object death
 * status listening. These APIs are suitable for Inter-Process Communication (IPC) and Remote Procedure Call (RPC)
 * communication scenarios.
 */
/**
 * @file ipc_cremote_object.h
 *
 * @brief This file provides C APIs for remote object creation, destruction, data sending, and remote object death
 * status listening. These APIs are suitable for Inter-Process Communication (IPC) and Remote Procedure Call (RPC)
 * communication scenarios.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @include <IPCKit/ipc_cremote_object.h>
 * @library libipc_capi.so
 * @kit IPCKit
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
 * @brief Defines the IPC death notification object, which is used to listen for the death event of a remote IPC object.
 * After an **OHIPCDeathRecipient** object is created, it must be registered with the {@link OHIPCRemoteObject} object
 * to take effect. If it is not registered, death events cannot be listened for. When a remote process terminates
 * unexpectedly or is destroyed, the local process that has registered the death listener will receive a death
 * notification callback. This allows the local process to release related resources or handle errors in a timely
 * manner.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
struct OHIPCDeathRecipient;

/**
 * @brief Defines the IPC death notification object, which is used to listen for the death event of a remote IPC object.
 * After an **OHIPCDeathRecipient** object is created, it must be registered with the {@link OHIPCRemoteObject} object
 * to take effect. If it is not registered, death events cannot be listened for. When a remote process terminates
 * unexpectedly or is destroyed, the local process that has registered the death listener will receive a death
 * notification callback. This allows the local process to release related resources or handle errors in a timely
 * manner.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
typedef struct OHIPCDeathRecipient OHIPCDeathRecipient;

/**
 * @brief Called to process the peer request at the stub. This callback is triggered when the proxy sends a request
 * through {@link OH_IPCRemoteProxy_SendRequest()}. The callback is executed in the Binder thread pool. Therefore, pay
 * attention to thread security. The callback should return as soon as possible to avoid long-time blocking. Otherwise,
 * the processing of other IPC requests may be affected.
 * - This function is used to receive and process cross-process requests from the client when the server implements a
 * custom IPC communication protocol.
 * - When the server capabilities need to be called across processes, the server uses this callback to process the
 * specific service logic.
 * - This function serves as the entry for message distribution and processing when the RPC server capability is
 * implemented.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param code Custom IPC command word, in the range [0x01, 0x00ffffff]. It is advised to define code values in
 *     segments based on service modules to avoid conflicts between different functional commands. For example, 0x01 to
 *     0x100 can be used for basic functions, and 0x101 to 0x200 for extended functions.
 * @param data Pointer to the requested data object. It cannot be NULL or released in the function.
 * @param reply Pointer to the response data object. It cannot be NULL or released in the function. If this function
 *     returns an error, data cannot be written to this parameter.
 * @param userData User private data. Pass this parameter when you need to access user-defined data in the callback
 *     function. If user data is not required, you can pass NULL. If this parameter is set to NULL, the callback
 *     function cannot access the user's private data.
 * @return <ul>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.</li>
 *         <li>Returns a custom error code in the range [1909000, 1909999] or a system error code otherwise.</li>
 *         <li>If the custom error code is out of range, {@link OH_IPC_ErrorCode#OH_IPC_INVALID_USER_ERROR_CODE} is
 *         returned.</li>
 *         </ul>
 * @since 12
 */
typedef int (*OH_OnRemoteRequestCallback)(uint32_t code, const OHIPCParcel *data,
    OHIPCParcel *reply, void *userData);

/**
 * @brief Called when an observed object is destroyed.
 * - Release related resources (such as memory and file handles) when the stub object is destroyed.
 * - Notify other modules to synchronize the status when the object is destroyed.
 * - Clear private user data when the object is destroyed.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param userData User private data. This parameter is passed when user-defined data needs to be accessed in the
 *     callback function. If user data does not need to be accessed, this parameter can be set to NULL. If this
 *     parameter is set to NULL, the callback function cannot access the user's private data.
 * @since 12
 */
typedef void (*OH_OnRemoteDestroyCallback)(void *userData);

/**
 * @brief Creates an {@link OHIPCRemoteStub} object, which is used on the stub side to create a server-side object for
 * processing remote data requests from the proxy side.
 * - When a server needs to provide cross-process service capabilities, it can create a stub object as the server-side
 * entity.
 * - It can also be used to implement the server side of custom IPC communication protocols, building RPC server
 * capabilities.
 * - After the stub object is created, it is typically registered with the service manager through the
 * {@link OHIPCRemoteProxy} related APIs, so that the proxy side can discover and connect to it.
 * - **requestCallback** should avoid time-consuming operations, as they may block IPC communication.
 * - If time-consuming tasks need to be handled, you can return an error code in the callback and use a thread pool to
 * process the tasks asynchronously.
 * - Ensure that the lifecycle of **userData** covers the lifecycle of the stub object to avoid dangling pointers.
 * - After the object is created by calling **OH_IPCRemoteStub_Create()**, it must be destroyed using
 * {@link OH_IPCRemoteStub_Destroy()} after use to release resources.
 * - If the object is not destroyed, memory leaks may occur.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param descriptor Pointer to the descriptor of the {@link OHIPCRemoteStub} object to create. It cannot be NULL. The
 *     string length range is (0, 204800], in bytes. If the value is out of range, NULL is returned. You are advised to
 *     use a unique identifier string, for example, **com.example.myservice** or **MyService**. The format is typically
 *     a reverse domain name or a simple service name, used to identify different IPC service APIs.
 * @param requestCallback Data request processing function. It cannot be NULL.
 * @param destroyCallback Callback function for object destruction. Pass this parameter when you need to perform
 *     cleanup operations (such as releasing **userData** resources) when the stub object is destroyed. If cleanup is
 *     not required, you can omit it or pass NULL. If not passed, no callback notifications will be triggered upon
 *     object destruction.
 * @param userData User private data. This parameter is passed when user-defined data needs to be accessed in the
 *     callback function. If user data does not need to be accessed, this parameter can be set to NULL. If this
 *     parameter is set to NULL, the callback function cannot access the user's private data.
 * @return <ul>
 *         <li>Returns the pointer to the **OHIPCRemoteStub** object read if the operation is successful; returns NULL
 *         otherwise.</li>
 *         </ul>
 * @since 12
 */
OHIPCRemoteStub* OH_IPCRemoteStub_Create(const char *descriptor, OH_OnRemoteRequestCallback requestCallback,
    OH_OnRemoteDestroyCallback destroyCallback, void *userData);

/**
 * @brief Destroys an {@link OHIPCRemoteStub} object.
 * - Release the stub object when the server no longer needs to provide the IPC service.
 * - Clear IPC resources when the server exits or the module is uninstalled.
 * - This function and {@link OH_IPCRemoteStub_Create()} must be used in pairs.
 * - This method must be called when the stub object is no longer used.
 * - After the destruction, the **destroyCallback** callback is automatically triggered to release **userData**.
 * - After the destruction, the stub object cannot be used for any operation.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param stub Pointer to the **OHIPCRemoteStub** object to destroy. It cannot be NULL.
 * @since 12
 */
void OH_IPCRemoteStub_Destroy(OHIPCRemoteStub *stub);

/**
 * @brief Destroys an {@link OHIPCRemoteProxy} object.
 * - Release the proxy object when the client no longer needs to call the remote service.
 * - Clear IPC resources when the client exits or the module is uninstalled.
 * - You must call {@link OH_IPCRemoteProxy_RemoveDeathRecipient()} to remove all added death event listeners before
 * destroying the proxy object.
 * - If the proxy object is destroyed when the listeners are not removed, the death event listener callback will be
 * abnormal or memory leakage will occur.
 * - After the destruction, no method of the proxy can be called.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object to destroy. It cannot be NULL.
 * @since 12
 */
void OH_IPCRemoteProxy_Destroy(OHIPCRemoteProxy *proxy);

/**
 * @brief Enumerates the IPC request modes. The synchronous request mode is suitable for scenarios where you need to
 * wait for a response from the remote side. The asynchronous request mode is suitable for scenarios where you do not
 * need to wait for a response or where you need to improve concurrent performance.
 *
 * @since 12
 */
typedef enum {
    /**
     * Synchronous request. Suitable for scenarios where you need to wait for a return result, such as query operations
     * and simple request-response scenarios.
     */
    OH_IPC_REQUEST_MODE_SYNC = 0,
    /**
     * Asynchronous request. Suitable for scenarios where you do not need to obtain the result immediately or where
     * operations are time-consuming, such as large-data transmission and background processing.
     */
    OH_IPC_REQUEST_MODE_ASYNC = 1,
} OH_IPC_RequestMode;

/**
 * @brief Defines IPC message options, which are used to configure request parameters during IPC communication.
 *
 * @since 12
 */
#pragma pack(4)
typedef struct {
    /**
     * @brief Message request mode, which is used to specify the request mode of IPC messages. You can select the
     * synchronous or asynchronous mode. The synchronous mode is applicable to scenarios where you need to wait for the
     * result, and the asynchronous mode is applicable to scenarios where you do not need to wait for the result. After
     * the synchronous mode is set, the call blocks the current thread and waits for the result. After the asynchronous
     * mode is set, the call returns immediately without waiting for the result. This member must be explicitly
     * initialized in the C language. You are advised to initialize the synchronous mode (when the result needs to be
     * obtained) or asynchronous mode (when the result does not need to be returned).
     *
     * @since 12
     */
    OH_IPC_RequestMode mode;
    /**
     * @brief Parameter reserved for RPC. In RPC communication, you can set the timeout interval (in seconds). This
     * parameter is invalid for IPC communication and can be ignored when IPC is used. The value range is [0,
     * 4294967295]. In RPC scenarios, you are advised to set a proper timeout interval based on service requirements to
     * avoid long-time blocking. If the timeout interval expires, the RPC call fails and a timeout error is returned.
     * This member must be explicitly initialized in the C language. The recommended initial value is **0**.
     *
     * @since 12
     */
    uint32_t timeout;
    /**
     * @brief Reserved parameter, which must be NULL. If a non-null pointer is passed, the API call may fail or
     * undefined behavior may occur.
     *
     * @since 12
     */
    void* reserved;
} OH_IPC_MessageOption;
#pragma pack()

/**
 * @brief Sends an IPC message from the proxy to the remote stub. This function supports both synchronous and
 * asynchronous communication modes.
 * - When the client needs to call server capabilities across processes, it sends a request and receives a response.
 * - This function enables IPC communication between the client and the server.
 * - This function can call service of remote services.
 * - Synchronous mode is suitable for requests that need to wait for a result, such as query operations, while
 * asynchronous mode is suitable for requests that do not need to wait for a result, such as log reporting.
 * - Synchronous calls block the current thread. Avoid using them in UI threads to prevent lag.
 * - Although asynchronous calls do not block the thread, you should still be mindful of the call frequency to avoid
 * overloading the IPC channel.
 * - It is advised to check whether the remote side is alive using {@link OH_IPCRemoteProxy_IsRemoteDead()} before
 * making a call.
 * - In case of call failure, it is advised to retry or perform error handling based on the returned error code.
 * - Frequent IPC calls may affect performance. It is advised to design the communication protocol properly to reduce
 * the number of calls.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object. It cannot be NULL.
 * @param code Custom IPC command word, in the range [0x01, 0x00ffffff]. If the value is out of range, the
 *     **OH_IPC_CODE_OUT_OF_RANGE** error is returned. It is advised to define code values in segments based on service
 *     modules, and ensure that the same command word definitions are used on both the proxy side and the stub side.
 *     Different operations of the same service API should use distinct code values for identification.
 * @param data Pointer to the requested data object. It cannot be NULL.
 * @param reply Pointer to the response data object. For a synchronous request, this parameter cannot be null and is
 *     used to store the response result. For an asynchronous request, this parameter can be null, in which case the
 *     response result is not stored.
 * @param option Pointer to the message option, which is used to configure the IPC message sending mode (synchronous/
 *     asynchronous). Pass this parameter when the asynchronous mode or custom message option is required. For
 *     asynchronous requests, the corresponding request mode must be passed and set. For synchronous requests, you may
 *     omit it or pass NULL. If omitted or NULL is passed, the synchronous mode (**OH_IPC_REQUEST_MODE_SYNC**) is used
 *     by default.
 * @return <ul>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the message is sent successfully.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_DEAD_REMOTE_OBJECT} if the remote **OHIPCRemoteStub** object dies.
 *         </li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_CODE_OUT_OF_RANGE} if the code is out of range.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} or a custom error code (range: [1909000, 1909999]) in
 *         other cases.</li>
 *         </ul>
 * @since 12
 */
int OH_IPCRemoteProxy_SendRequest(const OHIPCRemoteProxy *proxy, uint32_t code, const OHIPCParcel *data,
    OHIPCParcel *reply, const OH_IPC_MessageOption *option);

/**
 * @brief Obtains the interface descriptor from the stub. The interface descriptor is the unique identifier of the stub
 * object. It is used to identify the remote service type, check service version compatibility, or verify whether the
 * remote service implements a specific API. This function obtains the descriptor string from the remote stub via IPC
 * call and stores the result using the user-provided memory allocator.
 * - The memory of the returned descriptor string is allocated by the user-provided allocator. The user must actively
 * release it after use; otherwise, memory leaks will occur. Even if the function call fails, you should still check
 * whether the descriptor is not NULL and release it accordingly.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object. It cannot be NULL.
 * @param descriptor Pointer to the address of the memory for holding the interface descriptor. The memory is allocated
 *     by the allocator provided by the user and needs to be released. This pointer cannot be NULL. If an error code is
 *     returned, you still need to check whether the memory is empty and release the memory. Otherwise, memory leaks may
 *     occur. You are advised to release it immediately after use to prevent memory leaks.
 * @param len Pointer to the length of the data written to the descriptor, including the terminator. It cannot be NULL.
 * @param allocator Memory allocator specified by the user for allocating memory. It cannot be empty.
 * @return <ul>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the message is sent successfully.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_DEAD_REMOTE_OBJECT} if the remote **OHIPCRemoteStub** object dies.
 *         </li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_MEM_ALLOCATOR_ERROR} if the memory allocation fails.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} or a custom error code if the data in the
 *         serialized object fails to be read.</li>
 *         </ul>
 * @since 12
 */
int OH_IPCRemoteProxy_GetInterfaceDescriptor(OHIPCRemoteProxy *proxy, char **descriptor, int32_t *len,
    OH_IPC_MemAllocator allocator);

/**
 * @brief Defines a callback to be invoked when the {@link OHIPCRemoteStub} object dies unexpectedly. When the process
 * where the remote stub object resides exits abnormally or is killed by the system, the system triggers this callback
 * to notify the client. The callback is executed in the Binder thread. Therefore, pay attention to thread security.
 * Complex IPC operations are not recommended in callback to avoid potential deadlock risks. This function is commonly
 * used when the client needs to detect abnormal exit or crash of the server, perform resource cleanup or state reset
 * when the server object dies, or implement server liveness monitoring and fault recovery mechanisms.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param userData Pointer to user private data. Pass this parameter when user-defined data needs to be accessed in the
 *     death notification callback. If user data does not need to be accessed, this parameter can be omitted or set to
 *     NULL. If this parameter is set to NULL, the callback function cannot access the user's private data.
 * @since 12
 */
typedef void (*OH_OnDeathRecipientCallback)(void *userData);

/**
 * @brief Defines a callback to be invoked when the {@link OHIPCDeathRecipient} object is destroyed. This function is
 * usually used to release user private data or clear resources related to death listening when the death listening
 * object is destroyed.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param userData Pointer to user private data. Pass this parameter when user-defined data needs to be accessed in the
 *     death notification callback. If user data does not need to be accessed, this parameter can be omitted or set to
 *     NULL. If this parameter is set to NULL, the callback function cannot access the user's private data.
 * @since 12
 */
typedef void (*OH_OnDeathRecipientDestroyCallback)(void *userData);

/**
 * @brief Creates an {@link OHIPCDeathRecipient} object, which triggers a notification when the {@link OHIPCRemoteStub}
 * object dies unexpectedly. Listens for the death status of a remote stub object. It is commonly used when the client
 * needs to listen for death events of the server object, implement a mechanism for detecting abnormal server exits, or
 * perform fault handling or automatic reconnection when the server crashes.
 * - The death callback is triggered when the remote stub object is destroyed or the process crashes. It is advised to
 * release related resources, reset state, and attempt reconnection in the callback.
 * - The death callback may be executed on any thread, so thread safety must be taken into account. Avoid performing
 * time-consuming operations in the callback.
 * - It is recommended not to destroy the {@link OHIPCDeathRecipient} object directly in the callback. Destruction
 * should be performed outside the callback.
 * - Multiple proxies can share the same {@link OHIPCDeathRecipient} object, but you must ensure that it is removed from
 * all proxies before destruction.
 * - If the proxy is already dead, adding a death listener will immediately trigger the callback. Therefore, you need to
 * check the status before adding the listener.
 * - It is recommended that you create and add a death listener during application initialization, and remove and
 * destroy it when the application exits.
 * - After creation, it must be added to the proxy object via {@link OH_IPCRemoteProxy_AddDeathRecipient()}.
 * - When the listener is no longer needed, you must first remove it via
 * {@link OH_IPCRemoteProxy_RemoveDeathRecipient()}.
 * - After removal, the object must be destroyed by calling {@link OH_IPCDeathRecipient_Destroy()}.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param deathRecipientCallback Callback to be invoked when the {@link OHIPCRemoteStub} object is dead. It cannot be
 *     NULL.
 * @param destroyCallback Callback to be invoked when an object is destroyed. It can be NULL. If this parameter is NULL,
 *     the object destruction event is not listened to. Pass this parameter when you need to perform cleanup
 *     operations (such as releasing **userData** resources) when the {@link OHIPCDeathRecipient} object is destroyed.
 *     If cleanup is not required, you can omit it or pass NULL. If this parameter is set to NULL, no callback
 *     notifications will be triggered upon object destruction.
 * @param userData Pointer to user private data. Pass this parameter when user-defined data needs to be accessed in the
 *     death notification callback. If user data does not need to be accessed, this parameter can be omitted or set to
 *     NULL. If this parameter is set to NULL, the callback function cannot access the user's private data.
 * @return <ul>
 *         <li>Returns the pointer to the **OHIPCDeathRecipient** object read if the operation is successful; returns
 *         NULL otherwise.</li>
 *         </ul>
 * @since 12
 */
OHIPCDeathRecipient* OH_IPCDeathRecipient_Create(OH_OnDeathRecipientCallback deathRecipientCallback,
    OH_OnDeathRecipientDestroyCallback destroyCallback, void *userData);

/**
 * @brief Destroys an {@link OHIPCDeathRecipient} object. This function is commonly used to clear death listening
 * resources when the death events of remote objects no longer need to be listened for, or when the client exits or the
 * module is uninstalled.
 * - This function and {@link OH_IPCDeathRecipient_Create()} must be used in pairs.
 * - You must call {@link OH_IPCRemoteProxy_RemoveDeathRecipient()} to remove the listener object from all proxies
 * before destroying it.
 * - Destroy the death listening object when it is no longer needed.
 * - Destroying the listener object without removing it first may cause callback exceptions or memory leaks.
 * - After the destruction, **destroyCallback** is automatically triggered to release **userData**.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param recipient Pointer to the **OHIPCDeathRecipient** object to destroy. It cannot be NULL.
 * @since 12
 */
void OH_IPCDeathRecipient_Destroy(OHIPCDeathRecipient *recipient);

/**
 * @brief Subscribes to the death of an {@link OHIPCRemoteStub} object for an {@link OHIPCRemoteProxy} object. This
 * function is commonly used after the client starts, to register a server death listener so that server exceptions can
 * be detected in a timely manner, to implement server fault detection and automatic recovery mechanisms, and to
 * release related resources or notify the user when the server becomes unavailable.
 * - Destroying the listener object without removing it first may cause callback exceptions or memory leaks.
 * - First call {@link OH_IPCDeathRecipient_Create()} to create a listener object.
 * - Call {@link OH_IPCRemoteProxy_AddDeathRecipient()} to add a listener.
 * - The listener callback will be triggered during use.
 * - Before destroying the proxy or recipient, call {@link OH_IPCRemoteProxy_RemoveDeathRecipient()} to remove the
 * listener.
 * - Call {@link OH_IPCDeathRecipient_Destroy()} to destroy the listener object.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object to which the death notification is to be added. It cannot be
 *     NULL.
 * @param recipient Pointer to the death recipient object used to receive death notifications of the remote object. It
 *     cannot be NULL.
 * @return <ul>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} in other cases.</li>
 *         </ul>
 * @since 12
 */
int OH_IPCRemoteProxy_AddDeathRecipient(OHIPCRemoteProxy *proxy, OHIPCDeathRecipient *recipient);

/**
 * @brief Unsubscribes from the death of the **OHIPCRemoteStub** object for an {@link OHIPCRemoteProxy} object. This
 * function is commonly used to unregister the death event listener when the remote object's death events no longer
 * need to be monitored, or to remove the old death listener when switching to another service instance.
 * - If a listener object is no longer needed, call {@link OH_IPCDeathRecipient_Destroy()} to destroy it.
 * - If the object is not destroyed, memory leaks may occur.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object from which the death notification needs to be removed. It
 *     cannot be NULL.
 * @param recipient Pointer to the death recipient object used to receive death notifications of the remote object. It
 *     cannot be NULL.
 * @return <ul>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.</li>
 *         <li>Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} in other cases.</li>
 *         </ul>
 * @since 12
 */
int OH_IPCRemoteProxy_RemoveDeathRecipient(OHIPCRemoteProxy *proxy, OHIPCDeathRecipient *recipient);

/**
 * @brief Checks whether the {@link OHIPCRemoteStub} object corresponding to the {@link OHIPCRemoteProxy} object is
 * dead. This function is commonly used to proactively check whether the server is alive before sending an IPC request,
 * to determine whether a reconnection is needed in the reconnection mechanism, and to adopt different handling
 * strategies based on the server's liveness status in the service logic.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object to check. It cannot be NULL.
 * @return <ul>
 *         <li>Returns **1** if the {@link OHIPCRemoteStub} object is dead or invalid parameters are found; returns
 *         **0** otherwise. If invalid parameters are found, the {@link OHIPCRemoteStub} object does not exist, and
 *         **1** is returned.</li>
 *         </ul>
 * @since 12
 */
int OH_IPCRemoteProxy_IsRemoteDead(const OHIPCRemoteProxy *proxy);

#ifdef __cplusplus
}
#endif

/** @} */
#endif
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
 * @file ipc_cremote_object.h
 *
 * @brief This file provides C APIs for remote object creation, destruction, data sending, and remote object death
 * status listening. These APIs are suitable for Inter-Process Communication (IPC) and Remote Procedure Call (RPC)
 * communication scenarios.
 *
 * @include <IPCKit/ipc_cremote_object.h>
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
 * @brief Defines an IPC death notification object used to listen for the death event of an IPC remote object. After an
 * **OHIPCDeathRecipient** object is created, it must be registered with an **OHIPCRemoteObject** object to take effect.
 * If not registered, the death event cannot be detected. When the remote process terminates unexpectedly or is
 * destroyed proactively, the local process that has registered the death event listener will receive a death
 * notification callback, allowing it to release related resources or perform error handling in a timely manner.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
struct OHIPCDeathRecipient;

/**
 * @brief Defines an IPC death notification object used to listen for the death event of an IPC remote object. After an
 * **OHIPCDeathRecipient** object is created, it must be registered with an **OHIPCRemoteObject** object to take effect.
 * If not registered, the death event cannot be detected. When the remote process terminates unexpectedly or is
 * destroyed proactively, the local process that has registered the death event listener will receive a death
 * notification callback, allowing it to release related resources or perform error handling in a timely manner.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
typedef struct OHIPCDeathRecipient OHIPCDeathRecipient;

/**
 * @brief Called to process the peer request at the stub. This callback is triggered when the proxy sends a request
 * through {@link OH_IPCRemoteProxy_SendRequest}. The callback is executed in the Binder thread pool. Therefore, pay
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
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     Returns a custom error code in the range [1909001, 1909999] or a system error code otherwise.
 *     If the custom error code is out of range, {@link OH_IPC_ErrorCode#OH_IPC_INVALID_USER_ERROR_CODE} is returned.
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
 * @brief Creates an **OHIPCRemoteStub** object, which is used on the stub side to create a server-side object for
 * processing remote data requests from the proxy side.
 * - When a server needs to provide cross-process service capabilities, it can create a stub object as the server-side
 * entity.
 * - It can also be used to implement the server side of custom IPC communication protocols, building RPC server
 * capabilities.
 * - After the stub object is created, it is typically registered with the service manager through the
 * **OH_IPCRemoteProxy** related APIs, so that the proxy side can discover and connect to it.
 * - **requestCallback** should avoid time-consuming operations, as they may block IPC communication.
 * - If time-consuming tasks need to be handled, you can return an error code in the callback and use a thread pool to
 * process the tasks asynchronously.
 * - Ensure that the lifecycle of **userData** covers the lifecycle of the stub object to avoid dangling pointers.
 * - After the object is created via {@link OH_IPCRemoteStub_Create()}, it must be destroyed using
 * {@link OH_IPCRemoteStub_Destroy()} after use to release resources.
 * - If the object is not destroyed, memory leak occurs.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param descriptor Pointer to the descriptor of the **OHIPCRemoteStub** object to create. It cannot be NULL. The
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
 * @return Returns the pointer to the **OHIPCRemoteStub** object created if the operation is successful; returns NULL
 *     otherwise.
 * @since 12
 */
OHIPCRemoteStub* OH_IPCRemoteStub_Create(const char *descriptor, OH_OnRemoteRequestCallback requestCallback,
    OH_OnRemoteDestroyCallback destroyCallback, void *userData);

/**
 * @brief Destroys an **OHIPCRemoteStub** object.
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
 * @brief Destroys an **OHIPCRemoteProxy** object.
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
 * @brief Defines the IPC message options, which are used to configure request parameters for IPC communication.
 *
 * @since 12
 */
#pragma pack(4)
typedef struct {
    /**
     * Message request mode, which specifies the request method for IPC messages. Synchronous mode is suitable for
     * scenarios where you need to wait for the return result, while asynchronous mode is suitable for scenarios where
     * you do not need to wait for the result. When the synchronous mode is set, the call blocks the current thread to
     * wait for the return result. When the asynchronous mode is set, the call returns immediately without waiting for
     * the result. In C language, this member must be explicitly initialized. It is advised to initialize it to the
     * synchronous mode (when a return result is required) or the asynchronous mode (when no return result is required).
     */
    OH_IPC_RequestMode mode;
    /**
     * Reserved parameter for RPC. In RPC communication scenarios, this parameter can be used to set the timeout
     * interval. This parameter is invalid for IPC communication and can be ignored when IPC is used. The unit is
     * seconds. The value range is [0, 4294967295]. In RPC scenarios, it is recommended to set a reasonable timeout
     * interval based on service requirements to avoid prolonged blocking. After the timeout, the RPC call fails and
     * returns a timeout error. In C language, this member must be explicitly initialized. It is recommended to
     * initialize it to **0**.
     */
    uint32_t timeout;
    /**
     * Reserved parameter. NULL must be passed. Passing a non-null pointer may cause the API call to fail or result in
     * undefined behavior.
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
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the message is sent successfully.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_DEAD_REMOTE_OBJECT} if the remote **OHIPCRemoteStub** object dies.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_CODE_OUT_OF_RANGE} if the code is out of range.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} or a custom error code (range: [1909001, 1909999]) in other
 *     cases.
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
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the message is sent successfully.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_DEAD_REMOTE_OBJECT} if the remote **OHIPCRemoteStub** object dies.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_MEM_ALLOCATOR_ERROR} if the memory allocation fails.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} or a custom error code if the data in the serialized
 *     object fails to be read.
 * @since 12
 */
int OH_IPCRemoteProxy_GetInterfaceDescriptor(OHIPCRemoteProxy *proxy, char **descriptor, int32_t *len,
    OH_IPC_MemAllocator allocator);

/**
 * @brief Defines a callback to be invoked when the remote **OHIPCRemoteStub** object dies unexpectedly. When the
 * process where the remote stub object resides exits abnormally or is killed by the system, the system triggers this
 * callback to notify the client. The callback is executed in the Binder thread. Therefore, pay attention to thread
 * security. Complex IPC operations are not recommended in callback to avoid potential deadlock risks. This function is
 * commonly used when the client needs to detect abnormal exit or crash of the server, perform resource cleanup or
 * state reset when the server object dies, or implement server liveness monitoring and fault recovery mechanisms.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param userData Pointer to user private data.Pass this parameter when user-defined data needs to be accessed in the
 *     death notification callback. If user data does not need to be accessed, this parameter can be omitted or set to
 *     NULL. If this parameter is set to NULL, the callback function cannot access the user's private data.
 * @since 12
 */
typedef void (*OH_OnDeathRecipientCallback)(void *userData);

/**
 * @brief Defines a callback to be invoked when the **OHIPCDeathRecipient** object is destroyed. This function is
 * usually used to release user private data or clear resources related to death listening when the death listening
 * object is destroyed.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param userData Pointer to user private data.Pass this parameter when user-defined data needs to be accessed in the
 *     death notification callback. If user data does not need to be accessed, this parameter can be omitted or set to
 *     NULL. If this parameter is set to NULL, the callback function cannot access the user's private data.
 * @since 12
 */
typedef void (*OH_OnDeathRecipientDestroyCallback)(void *userData);

/**
 * @brief Creates an **OHIPCDeathRecipient** object, which triggers a notification when the **OHIPCRemoteStub** object
 * dies unexpectedly. Listens for the death status of a remote stub object. It is commonly used when the client needs
 * to listen for death events of the server object, implement a mechanism for detecting abnormal server exits, or
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
 * @param deathRecipientCallback Callback to be invoked when the **OHIPCRemoteStub** object is dead. It cannot be NULL.
 * @param destroyCallback Callback to be invoked when an object is destroyed. It can be NULL. If this parameter is NULL,
 *     the object destruction event is not listened to. Pass this parameter when you need to perform cleanup operations
 *     (such as releasing **userData** resources) when the **OHIPCDeathRecipient** object is destroyed. If cleanup is
 *     not required, you can omit it or pass NULL. If this parameter is set to NULL, no callback notifications will be
 *     triggered upon object destruction.
 * @param userData Pointer to user private data. Pass this parameter when user-defined data needs to be accessed in the
 *     death notification callback. If user data does not need to be accessed, this parameter can be omitted or set to
 *     NULL. If this parameter is set to NULL, the callback function cannot access the user's private data.
 * @return Returns the pointer to the **OHIPCDeathRecipient** object created if the operation is successful; returns
 *     NULL otherwise.
 * @since 12
 */
OHIPCDeathRecipient* OH_IPCDeathRecipient_Create(OH_OnDeathRecipientCallback deathRecipientCallback,
    OH_OnDeathRecipientDestroyCallback destroyCallback, void *userData);

/**
 * @brief Destroys an **OHIPCDeathRecipient** object. This function is commonly used to clear death listening resources
 * when the death events of remote objects no longer need to be listened for, or when the client exits or the module is
 * uninstalled.
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
 * @brief Subscribes to the death of an **OHIPCRemoteStub** object for an **OHIPCRemoteProxy** object. This function is
 * commonly used after the client starts, to register a server death listener so that server exceptions can be detected
 * in a timely manner, to implement server fault detection and automatic recovery mechanisms, and to release related
 * resources or notify the user when the server becomes unavailable.
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
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} in other cases.
 * @since 12
 */
int OH_IPCRemoteProxy_AddDeathRecipient(OHIPCRemoteProxy *proxy, OHIPCDeathRecipient *recipient);

/**
 * @brief Unsubscribes from the death of the **OHIPCRemoteStub** object for an **OHIPCRemoteProxy** object. This
 * function is commonly used to unregister the death event listener when the remote object's death events no longer
 * need to be monitored, or to remove the old death listener when switching to another service instance.
 * - If a listener object is no longer needed, call {@link OH_IPCDeathRecipient_Destroy()} to destroy it.
 * - Failure to destroy it may result in memory leaks.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object from which the death notification needs to be removed. It
 *     cannot be NULL.
 * @param recipient Pointer to the death recipient object used to receive death notifications of the remote object. It
 *     cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if the parameters are incorrect.
 *     Returns {@link OH_IPC_ErrorCode#OH_IPC_INNER_ERROR} in other cases.
 * @since 12
 */
int OH_IPCRemoteProxy_RemoveDeathRecipient(OHIPCRemoteProxy *proxy, OHIPCDeathRecipient *recipient);

/**
 * @brief Checks whether the **OHIPCRemoteStub** object corresponding to the **OHIPCRemoteProxy** object is dead. This
 * function is commonly used to proactively check whether the server is alive before sending an IPC request, to
 * determine whether a reconnection is needed in the reconnection mechanism, and to adopt different handling strategies
 * based on the server's liveness status in the service logic.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param proxy Pointer to the **OHIPCRemoteProxy** object to check. It cannot be NULL.
 * @return Returns **1** if the **OHIPCRemoteStub** object is dead or invalid parameters are found; returns **0**
 *     otherwise. If invalid parameters are found, the **OHIPCRemoteStub** object does not exist, and **1** is returned.
 * @since 12
 */
int OH_IPCRemoteProxy_IsRemoteDead(const OHIPCRemoteProxy *proxy);

#ifdef __cplusplus
}
#endif

/** @} */
#endif

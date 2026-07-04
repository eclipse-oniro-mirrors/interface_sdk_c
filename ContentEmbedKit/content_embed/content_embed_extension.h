/*
 * Copyright (c) 2026-2026 Huawei Device Co., Ltd.
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
 * @addtogroup ContentEmbed
 * @{
 *
 * @brief The ContentEmbed module provides the Object Editor (OE) framework and technologies to support document
 * embedding and collaborative editing between applications.
 * An embedded document (OE document for short) implemented by using the OE technology may be presented as a thumbnail
 * or a snapshot on a client UI, or may be serialized into a segment of binary data in a standard format and stored in
 * a memory or a file (referred to as an OE format file).
 * @since 24
 */

/**
 * @file content_embed_extension.h
 *
 * @brief Defines the data structures and operation APIs related to the OE Extension of the server application.
 *
 * @library libcontent_embed_ndk.so
 * @kit ContentEmbedKit
 * @syscap SystemCapability.ContentEmbed.ObjectEditor
 * @since 24
 */

#ifndef OHOS_CONTENT_EMBED_EXTENSION_H
#define OHOS_CONTENT_EMBED_EXTENSION_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "content_embed_common.h"
#include "AbilityKit/ability_runtime/extension_ability.h"
#include "AbilityKit/ability_runtime/context.h"
#include "AbilityKit/ability_runtime/start_options.h"
#include "AbilityKit/ability_base/want.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @brief Declares the structure type of an OE document. Encapsulates the metadata, content, and storage structure of
 * the embedded document.
 *
 * @since 24
 */
typedef struct ContentEmbed_Document ContentEmbed_Document;

/**
 * @brief Defines the structure type of the OE Extension context.
 *
 * @since 24
 */
typedef struct ContentEmbed_ExtensionContext ContentEmbed_ExtensionContext;

/**
 * @brief Declares the pointer type of the context object of the OE Extension.
 *
 * @since 24
 */
typedef struct ContentEmbed_ExtensionContext* ContentEmbed_ExtensionContextHandle;

/**
 * @brief Declares the structure type of an OE Extension instance. Manages the core functions of the extension, such as
 * lifecycle management, callback registration, and association with the client's OE object.
 *
 * @since 24
 */
typedef struct ContentEmbed_ExtensionInstance ContentEmbed_ExtensionInstance;

/**
 * @brief Declares the pointer type of the instance object of the ContentEmbed extension.
 *
 * @since 24
 */
typedef struct ContentEmbed_ExtensionInstance* ContentEmbed_ExtensionInstanceHandle;

/**
 * @brief Declares the ContentEmbed_Object structure. Points to the program object (server-side OE object for short)
 * for embedding and editing the OE document encapsulated by the server.
 *
 * @since 24
 */
typedef struct ContentEmbed_Object ContentEmbed_Object;

/**
 * @brief Declares the pointer type of the ContentEmbed_Object object.
 *
 * @since 24
 */
typedef struct ContentEmbed_Object* ContentEmbed_ObjectHandle;

/**
 * @brief Obtains the corresponding OE Extension context object from the OE Extension instance.
 *
 * @param ceInstance Pointer to the OE Extension instance object.
 * @param ceContext Output parameter. After the function is successfully called, this pointer points to the context
 *     object of the OE Extension instance.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - indicates that the operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - The operation is not supported because the application is in the DLP sandbox.
 *     </li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_GetContentEmbedContext(ContentEmbed_ExtensionInstanceHandle ceInstance,
                                                                        ContentEmbed_ExtensionContextHandle *ceContext);

/**
 * @brief Obtains the AbilityRuntime context from the OE Extension context.
 *
 * @param ceContext Pointer to the OE Extension context object.
 * @param context Output parameter. After the call is successful, this pointer points to the
 *     {@link AbilityRuntime_Context} context object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - The operation is not supported because the application is in the DLP sandbox.
 *     </li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_GetContext(ContentEmbed_ExtensionContextHandle ceContext,
                                                            AbilityRuntime_ContextHandle *context);

/**
 * @brief Obtains the corresponding OE Extension instance from the ExtensionAbility base class instance.
 *
 * @param baseInstance {@link AbilityRuntime_ExtensionInstance} instance.
 * @param ceInstance Output parameter. After the call is successful, this pointer points to the OE Extension instance
 *     object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - The operation is not supported because the application is in the DLP sandbox.
 *     </li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_GetExtensionInstance(
    AbilityRuntime_ExtensionInstanceHandle baseInstance,
    ContentEmbed_ExtensionInstanceHandle *ceInstance);

/**
 * @brief Indicates the lifecycle function type when an OE Extension instance is created.
 * <br>You need to implement this function and register it with the OE Extension instance through
 * {@link OH_ContentEmbed_Extension_RegisterOnCreateFunc}.
 *
 * @param instance Pointer to the OE Extension instance object.
 * @param want Represents a pointer to an {@link AbilityBase_Want} instance.
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnCreateFunc)(
    ContentEmbed_ExtensionInstanceHandle instance, AbilityBase_Want *want);

/**
 * @brief Indicates the lifecycle function type when an OE Extension instance is destroyed.
 * <br>You need to implement this function and register it with the OE Extension instance through
 * {@link OH_ContentEmbed_Extension_RegisterOnDestroyFunc}.
 *
 * @param instance Pointer to the OE Extension instance object.
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnDestroyFunc)(
    ContentEmbed_ExtensionInstanceHandle instance);

/**
 * @brief This callback function is triggered when the client's OE object is connected to the OE Extension instance. It
 * is used to perform the initialization operation after the server's OE object is associated.
 * <br>You need to implement this function and register it with the OE Extension instance through
 * {@link OH_ContentEmbed_Extension_RegisterOnObjectAttachFunc}.
 *
 * @param instance Pointer to the OE Extension instance object.
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnObjectAttachFunc)(
    ContentEmbed_ExtensionInstanceHandle instance, ContentEmbed_ObjectHandle object);

/**
 * @brief This callback function is triggered when the client disconnects from the OE Extension instance, and is used
 * to perform cleanup operations after the server disconnects from the OE Extension instance.
 * <br>You need to implement this function and register it with the OE Extension instance through
 * {@link OH_ContentEmbed_Extension_RegisterOnObjectDetachFunc}.
 *
 * @param instance Pointer to the OE Extension instance object.
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnObjectDetachFunc)(
    ContentEmbed_ExtensionInstanceHandle instance, ContentEmbed_ObjectHandle object);

/**
 * @brief Callback function type used when the server-side OE object writes data to the OE document.
 * <br>You need to implement this function and register it with the server-side OE object through
 * {@link OH_ContentEmbed_Extension_RegisterOnWriteToDataStreamFunc}.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnWriteToDataStreamFunc)(
    ContentEmbed_ObjectHandle object);

/**
 * @brief Callback function type used when the client-side OE object requests to obtain the OE document snapshot.
 * <br>You need to implement this function and register it with the server-side OE object through
 * {@link OH_ContentEmbed_Extension_RegisterOnGetSnapshotFunc}.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnGetSnapshotFunc)(
    ContentEmbed_ObjectHandle object);

/**
 * @brief Callback function type when the client's OE object requests to edit an OE document.
 * <br>You need to implement this function and register it with the server's OE object through
 * {@link OH_ContentEmbed_Extension_RegisterOnDoEditFunc}.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnDoEditFunc)(
    ContentEmbed_ObjectHandle object);

/**
 * @brief Callback function type when the client's OE object requests the editing state of an OE document.
 * <br>You need to implement this function and register it with the server's OE object through
 * {@link OH_ContentEmbed_Extension_RegisterOnGetEditStatusFunc}.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @param isEditing Indicates that the content embed document is being edited.
 * @param isModified Indicates that the content embed document has been modified.
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnGetEditStatusFunc)(
    ContentEmbed_ObjectHandle object, bool *isEditing, bool *isModified);

/**
 * @brief Indicates the callback function type when the client queries the capabilities supported by the OE Extension
 * instance.
 * <br>You need to implement this function and register it with the server-side OE object through
 * {@link OH_ContentEmbed_Extension_RegisterOnGetCapabilityFunc}.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @param bitmask Indicates the capabilities possessed by a content embed extension instance.
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnGetCapabilityFunc)(
    ContentEmbed_ObjectHandle object, uint32_t *bitmask);

/**
 * @brief Registers the lifecycle function for creating an OE Extension instance.
 *
 * @param instance Pointer to the OE Extension instance object.
 * @param onCreateFunc {@link OH_ContentEmbed_Extension_OnCreateFunc} lifecycle function to be registered.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnCreateFunc(
    ContentEmbed_ExtensionInstanceHandle instance, OH_ContentEmbed_Extension_OnCreateFunc onCreateFunc);

/**
 * @brief Registers the lifecycle function for destroying an OE Extension instance.
 *
 * @param instance Pointer to the OE Extension instance object.
 * @param onDestroyFunc {@link OH_ContentEmbed_Extension_OnDestroyFunc} lifecycle function to be registered.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnDestroyFunc(
    ContentEmbed_ExtensionInstanceHandle instance, OH_ContentEmbed_Extension_OnDestroyFunc onDestroyFunc);

/**
 * @brief Registers the callback function for connecting to the client's OE object.
 * <br>You can call {@link OH_ContentEmbed_Extension_UnRegisterOnObjectAttachFunc} to deregister the callback function.
 *
 * @param instance Pointer to the OE Extension instance object.
 * @param onObjectAttachFunc {@link OH_ContentEmbed_Extension_OnObjectAttachFunc} callback function to be registered.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - The operation is not supported because the application is in the DLP sandbox.
 *     </li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnObjectAttachFunc(
    ContentEmbed_ExtensionInstanceHandle instance,
    OH_ContentEmbed_Extension_OnObjectAttachFunc onObjectAttachFunc);

/**
 * @brief Cancels the registration of the callback function for disconnecting the client from the OE object.
 *
 * @param instance Pointer to the OE Extension instance object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - The operation is not supported because the application is in the DLP sandbox.
 *     </li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_UnRegisterOnObjectAttachFunc(
    ContentEmbed_ExtensionInstanceHandle instance);

/**
 * @brief Registers the callback function for disconnecting the client from the OE object.
 * <br>You can call {@link OH_ContentEmbed_Extension_UnRegisterOnObjectDetachFunc} to cancel the registration.
 *
 * @param instance Pointer to the instance object of the OE Extension.
 * @param onObjectDetachFunc {@link OH_ContentEmbed_Extension_OnObjectDetachFunc} callback function to be registered.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnObjectDetachFunc(
    ContentEmbed_ExtensionInstanceHandle instance,
    OH_ContentEmbed_Extension_OnObjectDetachFunc onObjectDetachFunc);

/**
 * @brief Cancels the callback function for disconnecting the client from the OE object.
 *
 * @param instance Pointer to the OE Extension instance object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_UnRegisterOnObjectDetachFunc(
    ContentEmbed_ExtensionInstanceHandle instance);

/**
 * @brief Registers the callback function for the server to write data streams to the OE document.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @param onWriteToDataStreamFunc {@link OH_ContentEmbed_Extension_OnWriteToDataStreamFunc} callback function to be
 *     registered.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnWriteToDataStreamFunc(
    ContentEmbed_ObjectHandle object,
    OH_ContentEmbed_Extension_OnWriteToDataStreamFunc onWriteToDataStreamFunc);

/**
 * @brief Registers the callback function for obtaining the OE document snapshot when the client requests to obtain the
 * OE document snapshot.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @param onGetSnapshotFunc {@link OH_ContentEmbed_Extension_OnGetSnapshotFunc} callback function to be registered.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnGetSnapshotFunc(
    ContentEmbed_ObjectHandle object, OH_ContentEmbed_Extension_OnGetSnapshotFunc onGetSnapshotFunc);

/**
 * @brief Registers the callback function for editing an OE document when the client requests to edit the OE document.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @param onDoEditFunc {@link OH_ContentEmbed_Extension_OnDoEditFunc} callback function to be registered.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnDoEditFunc(
    ContentEmbed_ObjectHandle object, OH_ContentEmbed_Extension_OnDoEditFunc onDoEditFunc);

/**
 * @brief Registers the callback function for requesting the editing state of an OE document from the client.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @param onGetEditStatusFunc {@link OH_ContentEmbed_Extension_OnGetEditStatusFunc} callback function to be registered.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnGetEditStatusFunc(
    ContentEmbed_ObjectHandle object, OH_ContentEmbed_Extension_OnGetEditStatusFunc onGetEditStatusFunc);

/**
 * @brief Registers the callback function for querying whether the OE Extension instance supports the capability of the
 * client's OE object.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @param onGetCapabilityFunc {@link OH_ContentEmbed_Extension_OnGetCapabilityFunc} callback function to be registered.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnGetCapabilityFunc(
    ContentEmbed_ObjectHandle object, OH_ContentEmbed_Extension_OnGetCapabilityFunc onGetCapabilityFunc);

/**
 * @brief Obtains the instance of the OE document associated with the server-side OE object.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @param ceDocument Output parameter. After the call is successful, this pointer points to the associated OE document
 *     instance.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - The operation is not supported because the application is in the DLP sandbox.
 *     </li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_GetContentEmbedDocument(
    ContentEmbed_ObjectHandle object, ContentEmbed_Document **ceDocument);

/**
 * @brief Triggers the callback function for updating the OE document to register the client's OE object.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED} - The client callback is not registered.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_FAILED} - The client callback fails to be executed.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_CallbackToOnUpdate(
    ContentEmbed_ObjectHandle object);

/**
 * @brief Trigger the callback function of the error in the OE document that triggers the registration of the client's
 * OE object.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @param code Error code. For details, see {@link ContentEmbed_ErrorCode}.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED} - The client callback is not registered.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_FAILED} - The client callback fails to be executed.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_CallbackToOnError(
    ContentEmbed_ObjectHandle object, ContentEmbed_ErrorCode code);

/**
 * @brief Registers the callback function for finishing editing an OE document.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @param dataModified Indicates whether the document data has been modified. The value true indicates that the file is
 *     modified, and the value false indicates that the file is not modified.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED} - The client callback is not registered.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_FAILED} - The client callback fails to be executed.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_CallbackToOnEditingFinished(
    ContentEmbed_ObjectHandle object, bool dataModified);

/**
 * @brief Stops the callback function of the OE Extension that is associated with all client-side OE objects and
 * registered by the OE Extension.
 *
 * @param instance Pointer to the OE Extension instance object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - Operations are successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED} - The client callback is not registered.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_FAILED} - Failed to execute the client callback.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_CallbackToOnExtensionStopped(
    ContentEmbed_ExtensionInstanceHandle instance);

/**
 * @brief Sets the snapshot image of the OE document associated with the client-side OE object.
 *
 * @param object {@link ContentEmbed_ObjectHandle} instance.
 * @param pixelMap Pixel map object of the document snapshot. For details, see {@link OH_PixelmapNative}.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - The operation is not supported because the app is in the DLP sandbox.</li>
 *     <li>{@link CE_ERR_IMAGE_PACKER_OPERATION_FAILED} - Failed to perform the image operation.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_SetSnapshot(
    ContentEmbed_ObjectHandle object, OH_PixelmapNative *pixelMap);

/**
 * @brief Starts the {@link UIAbility} of the current instance using the OE Extension context.
 *
 * @param context Pointer to the context object of the OE Extension.
 * @param want Parameter passed when the UIAbility is started. For details, see {@link AbilityBase_Want}.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL} - The system service is abnormal.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_ContextStartSelfUIAbility(
    ContentEmbed_ExtensionContextHandle context, AbilityBase_Want *want);

/**
 * @brief Starts the {@link UIAbility} of the OE Extension context using the start options.
 *
 * @param context Pointer to the OE Extension context object.
 * @param want Parameter passed when the UIAbility is started. For details, see {@link AbilityBase_Want}.
 * @param options Additional options for starting the UIAbility. For details, see {@link AbilityRuntime_StartOptions}.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL} - The system service is abnormal.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_ContextStartSelfUIAbilityWithStartOptions(
    ContentEmbed_ExtensionContextHandle context,
    AbilityBase_Want *want, AbilityRuntime_StartOptions *options);

/**
 * @brief Destroys the OE Extension.
 *
 * @param context Pointer to the OE Extension context object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - Operations are successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL} - The system service is abnormal.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_ContextTerminateAbility(
    ContentEmbed_ExtensionContextHandle context);

#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_CONTENT_EMBED_EXTENSION_H

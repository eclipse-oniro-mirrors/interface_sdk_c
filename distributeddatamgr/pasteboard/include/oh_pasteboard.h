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
 * @addtogroup Pasteboard
 * @{
 *
 * @brief Provides the copy and paste support for the system Pasteboard.
 * You can use the APIs of this module to operate the Pasteboard content of the plain text, HTML, 
 * URI, Want, pixel map, and other types.
 *
 * @since 12
 */

/**
 * @file OH_Pasteboard.h
 *
 * @brief Provides APIs and enums of the Pasteboard module.
 *
 * @kit BasicServicesKit
 * @library libpasteboard_ndk.so
 * @syscap SystemCapability.MiscServices.Pasteboard
 *
 * @since 12
 */

#ifndef OH_PASTEBOARD_H
#define OH_PASTEBOARD_H

#include <inttypes.h>
#include <stdbool.h>
#include "udmf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the types of data changes that can be observed.
 *
 * @since 12
 */
typedef enum Pasteboard_SubscribeType {
    /**
     * @brief Change of the Pasteboard data in the local device.
     */
    PASTEBOARD_SUBSCRIBE_TYPE_LOCAL = 1,
    /**
     * @brief Change of the Pasteboard data in the remote devices.
     */
    PASTEBOARD_SUBSCRIBE_TYPE_REMOTE = 2
} Pasteboard_SubscribeType;

/**
 * @brief Defines the callback function used to return the Pasteboard data changed.
 *
 * @param context The context set by {@link OH_PasteboardSubscriber_SetContext} function.
 * @param type The types of data changes. For details, see {@link Pasteboard_SubscribeType}.
 * @since 12
 */
typedef void (*Pasteboard_SubscribeCallback)(void* context, Pasteboard_SubscribeType type);

/**
 * @brief Defines the Pasteboard subscriber information
 *
 * @since 12
 */
typedef struct OH_PasteboardSubscriber OH_PasteboardSubscriber;

/**
 * @brief Creates a {@link OH_PasteboardSubscriber} instance.
 *
 * @return Returns the pointer to the {@link OH_PasteboardSubscriber} instance created if the operation is successful.
 * Returns nullptr if the operation is failed.
 * @see OH_PasteboardSubscriber.
 * @since 12
 */
OH_PasteboardSubscriber* OH_PasteboardSubscriber_Create();

/**
 * @brief Destroy a {@link OH_PasteboardSubscriber} instance.
 *
 * @param subscriber Pointer to the {@link OH_PasteboardSubscriber} instance to destroy.
 * @return Returns the status code of the execution. For details, see {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_PasteboardSubscriber PASTEBOARD_ErrCode.
 * @since 12
 */
int OH_PasteboardSubscriber_Destroy(OH_PasteboardSubscriber* subscriber);

/**
 * @brief Sets a callback function to return the Pasteboard data changed.
 *
 * @param subscriber Pointer to the {@link OH_PasteboardSubscriber} instance.
 * @param callback Callback to set. For details, see {@link Pasteboard_SubscribeCallback}.
 * @return Returns the status code of the execution. For details, see {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_PasteboardSubscriber Pasteboard_SubscribeCallback PASTEBOARD_ErrCode.
 * @since 12
 */
int OH_PasteboardSubscriber_SetCallback(OH_PasteboardSubscriber* subscriber, const Pasteboard_SubscribeCallback callback);

/**
 * @brief Obtains the callback used to return the Pasteboard data changed.
 *
 * @param subscriber Pointer to the {@link OH_PasteboardSubscriber} instance.
 * @param callback Pointer to the {@link Pasteboard_SubscribeCallback} instance to obtain.
 * @return Returns the status code of the execution. For details, see {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_PasteboardSubscriber Pasteboard_SubscribeCallback PASTEBOARD_ErrCode.
 * @since 12
 */
int OH_PasteboardSubscriber_GetCallback(OH_PasteboardSubscriber* subscriber, Pasteboard_SubscribeCallback* callback);

/**
 * @brief Sets a context instance, which is the first parameter in Pasteboard_SubscribeCallback.
 *
 * @param subscriber Pointer to the {@link OH_PasteboardSubscriber} instance.
 * @param context Pointer to the context set.
 * @return Returns the status code of the execution. For details, see {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_PasteboardSubscriber PASTEBOARD_ErrCode.
 * @since 12
 */
int OH_PasteboardSubscriber_SetContext(OH_PasteboardSubscriber* subscriber, void* context);

/**
 * @brief Obtains the context, which is the first parameter in Pasteboard_SubscribeCallback.
 *
 * @param subscriber Pointer to the {@link OH_PasteboardSubscriber} instance.
 * @param context Pointer to the context to obtain.
 * @return Returns the status code of the execution. For details, see {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_PasteboardSubscriber PASTEBOARD_ErrCode.
 * @since 12
 */
int OH_PasteboardSubscriber_GetContext(OH_PasteboardSubscriber* subscriber, void** context);

/**
 * @brief Represents the Pasteboard information.
 *
 * @since 12
 */
typedef struct OH_Pasteboard OH_Pasteboard;

/**
 * @brief Creates a {@link OH_Pasteboard} instance.
 *
 * @return Returns the pointer to the {@link OH_Pasteboard} instance created if the operation is successful.
 * Returns nullptr if the operation is failed.
 * @see OH_Pasteboard.
 * @since 12
 */
OH_Pasteboard* OH_Pasteboard_Create();

/**
 * @brief Destroy a {@link OH_Pasteboard} instance.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance to destroy.
 * @see OH_Pasteboard.
 * @since 12
 */
void OH_Pasteboard_Destroy(OH_Pasteboard* pasteboard);

/**
 * @brief Subscribes to the Pasteboard data change.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @param type Event type to subscribe to.
 * @param subscriber - Pointer to the subscriber information, which specifies the callback used to
 * reporting the pasteboard data change. For details, see {@link OH_PasteboardSubscriber}.
 * @return Returns the status code of the execution. For details, {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_Pasteboard OH_PasteboardSubscriber PASTEBOARD_ErrCode.
 * @since 12
 */
int OH_Pasteboard_Subscribe(OH_Pasteboard* pasteboard, int type, const OH_PasteboardSubscriber* subscriber);

/**
 * @brief Unsubscribes from the Pasteboard data change.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @param type Event type to subscribe to.
 * @param subscriber - Pointer to the subscriber information, which specifies the callback used to
 * reporting the pasteboard data change. For details, see {@link OH_PasteboardSubscriber}.
 * @return Returns the status code of the execution. For details, {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_Pasteboard OH_PasteboardSubscriber PASTEBOARD_ErrCode.
 * @since 12
 */
int OH_Pasteboard_Unsubscribe(OH_Pasteboard* pasteboard, int type, const OH_PasteboardSubscriber* subscriber);

/**
 * @brief Checks whether the Pasteboard data is from a remote device.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @return Returns a boolean value, which indicates whether the the data is from a remote device.
 *         The value {@code false} means Pasteboard data is not from a remote device.
 *         The value {@code true} means the opposite.
 * @see OH_Pasteboard.
 * @since 12
 */
bool OH_Pasteboard_IsRemoteData(OH_Pasteboard* pasteboard);

/**
 * @brief Obtains the source of Pasteboard data.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @param source Pointer to the source data.
 * @param len Length of the source data.
 * @return Returns the status code of the execution. For details, see {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_Pasteboard PASTEBOARD_ErrCode.
 * @since 12
 */
int OH_Pasteboard_GetDataSource(OH_Pasteboard* pasteboard, char* source, unsigned int len);

/**
 * @brief Checks whether the Pasteboard has the specified type of data.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @param type Poniter to the type of data to check.
 * @return Returns a boolean value, which indicates whether the Pasteboard has the specified type of data.
 *         The value {@code true} means the Pasteboard has the specified type of data.
 *         The value {@code false} means the opposite.
 * @see OH_Pasteboard.
 * @since 12
 */
bool OH_Pasteboard_HasType(OH_Pasteboard* pasteboard, const char* type);

/**
 * @brief Checks whether there is data in the Pasteboard.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @return Returns a boolean value, which indicates whether there is data in the Pasteboard.
 *         The value {@code true} means there is data in Pasteboard.
 *         The value {@code false} means the opposite.
 * @see OH_Pasteboard.
 * @since 12
 */
bool OH_Pasteboard_HasData(OH_Pasteboard* pasteboard);

/**
 * @brief Obtains data from the Pasteboard.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @param data Pointer to the {@link OH_UdmfData} instance.
 * @return Returns the status code of the execution. For details, see {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_Pasteboard OH_UdmfData PASTEBOARD_ErrCode.
 * @since 12
 */
int OH_Pasteboard_GetData(OH_Pasteboard* pasteboard, OH_UdmfData* data);

/**
 * @brief Writes data to the Pasteboard.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @param data Pointer to the {@link OH_UdmfData} instance.
 * @return Returns the status code of the execution. For details, see {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_Pasteboard OH_UdmfData PASTEBOARD_ErrCode.
 * @since 12
 */
int OH_Pasteboard_SetData(OH_Pasteboard* pasteboard, OH_UdmfData* data);

/**
 * @brief Clears the data in the Pastedboard.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @return Returns the status code of the execution. For details, see {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_Pasteboard PASTEBOARD_ErrCode.
 * @since 12
 */
int OH_Pasteboard_ClearData(OH_Pasteboard* pasteboard);
#ifdef __cplusplus
};
#endif

/** @} */
#endif
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
 * @since 13
 */

/**
 * @file OH_Pasteboard.h
 *
 * @brief Provides APIs and enums of the Pasteboard module.
 *
 * @kit BasicServicesKit
 * @library libpasteboard.so
 * @syscap SystemCapability.MiscServices.Pasteboard
 *
 * @since 13
 */

#ifndef OH_PASTEBOARD_H
#define OH_PASTEBOARD_H

#include <inttypes.h>
#include <stdbool.h>
#include "database/udmf/udmf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the types of data changes that can be observed.
 *
 * @since 13
 */
typedef enum Pasteboard_NotifyType {
    /**
     * @brief Change of the Pasteboard data in the local device.
     */
    NOTIFY_LOCAL_DATA_CHANGE = 1,
    /**
     * @brief Change of the Pasteboard data in the remote devices.
     */
    NOTIFY_REMOTE_DATA_CHANGE = 2
} Pasteboard_NotifyType;

/**
 * @brief Enumerates the types of file confilct options when getting data from the Pastedboard.
 *
 * @since 15
 */
typedef enum Pasteboard_FileConflictOption {
    /**
     * @brief Overwrite when destUir has file with same name.
     */
    OH_PASTEBOARD_OVERWRITE = 0,
    /**
     * @brief Skip when destUir has file with same name.
     */
    OH_PASTEBOARD_SKIP = 1
} Pasteboard_FileConflictOption;

/**
 * @brief Enumerates the types of progress indicator when getting data from the Pastedboard.
 *
 * @since 15
 */
typedef enum Pasteboard_ProgressIndicator {
    /**
     * @brief Getting data without system default progress indicator.
     */
    OH_PASTEBOARD_NONE = 0,
    /**
     * @brief Getting data with system default progress indicator.
     */
    OH_PASTEBOARD_DEFAULT = 1
} Pasteboard_ProgressIndicator;

/**
 * @brief Represents the Pasteboard progress information.
 *
 * @since 15
 */
typedef struct Pasteboard_ProgressInfo {
    /** Percentage of progress when getting PasteData without using default system progress.
     */
    int progress;
} Pasteboard_ProgressInfo;

/**
 * @brief Defines the callback function used to return the progress information when getting OH_UdmfData.
 *
 * @param progressInfo The progress information notified to Application.
 * @since 15
 */
typedef void (*Pasteboard_ProgressNotify)(Pasteboard_ProgressInfo progressInfo);

/**
 * @brief Represents the Pasteboard progress listener when getting OH_UdmfData.
 *
 * @since 15
 */
typedef struct Pasteboard_ProgressListener {
    /**
     * Indicates the callback function used to return the progress information.
     */
    Pasteboard_ProgressNotify callback;
} Pasteboard_ProgressListener;

/**
 * @brief Defines the cancel function used to cancel the progress when getting OH_PasteData.
 *
 * @since 15
 */
typedef void (*Pasteboard_ProgressCancel)(void);

/**
 * brief Represents the Pasteboard progress signal when getting data.
 *
 * @since 15
 */
typedef struct Pasteboard_ProgressSignal {
    /**
     * Indicates the signal function used to cancel the progress process.
     */
    Pasteboard_ProgressCancel cancel;
} Pasteboard_ProgressSignal;

/**
 * @brief Represents the pasteboard get data parameters when getting data from Pasteboard.
 *
 * @param destUri Indicates the uri of dest path where copy file will be copied to in sandbox of Application.
 * @param destUriLen Indicates the length of destUir.
 * @param fileConflictOption Indicates fileConflictOption when dest path has file with same name.
 * @param progressIndicator Indicates whether to use default system progress indacator.
 * @param progressListener Indicates the progress listener when getting PasteData without using default system progress.
 * @param progressSignal Indicates progress signal when getting PasteData with system progress indacator.
 * @since 15
 */
typedef struct OH_Pasteboard_GetDataParams {
    /** Indicates the uri of dest path where copy files will be copied to sandbox of Application.
     */
    char *destUri;
    /** Indicates the length of destUir.
     */
    unsigned int destUriLen;
    /** Indicates fileConflictOptions when dest path has file with same name.
     */
    Pasteboard_FileConflictOption fileConflictOption;
    /** Indicates whether to use default system progress indicator.
     */
    Pasteboard_ProgressIndicator progressIndicator;
    /** Indicates the progress listener when getting PasteData without using default system progress.
     */
    Pasteboard_ProgressListener progressListener;
    /** Indicates progress signal when getting PasteData with system progress indacator.
     */
    Pasteboard_ProgressSignal progressSignal;
} OH_Pasteboard_GetDataParams;

/**
 * @brief Defines the callback function used to return the Pasteboard data changed.
 *
 * @param context The context set by {@link OH_PasteboardObserver_SetData} function.
 * @param type The types of data changes. For details, see {@link Pasteboard_NotifyType}.
 * @since 13
 */
typedef void (*Pasteboard_Notify)(void* context, Pasteboard_NotifyType type);

/**
 * @brief Defines the callback function used free the context.
 * @param context Pointer to the context which is to be free.
 * @since 13
 */
typedef void (*Pasteboard_Finalize)(void* context);

/**
 * @brief Defines the Pasteboard subscriber information
 *
 * @since 13
 */
typedef struct OH_PasteboardObserver OH_PasteboardObserver;

/**
 * @brief Creates a {@link OH_PasteboardObserver} instance.
 *
 * @return Returns the pointer to the {@link OH_PasteboardObserver} instance created if the operation is successful.
 * Returns nullptr if the operation is failed.
 * @see OH_PasteboardObserver.
 * @since 13
 */
OH_PasteboardObserver* OH_PasteboardObserver_Create();

/**
 * @brief Destroy a {@link OH_PasteboardObserver} instance.
 *
 * @param observer Pointer to the {@link OH_PasteboardObserver} instance to destroy.
 * @return Returns the status code of the execution. For details, see {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_PasteboardObserver PASTEBOARD_ErrCode.
 * @since 13
 */
int OH_PasteboardObserver_Destroy(OH_PasteboardObserver* observer);

/**
 * @brief Sets a callback function to return the Pasteboard data changed.
 *
 * @param observer Pointer to the {@link OH_PasteboardObserver} instance.
 * @param context Pointer to the context set, which is the first parameter in Pasteboard_Notify.
 * @param callback Callback to set. For details, see {@link Pasteboard_Notify}.
 * @param finalize Optional callback that can free context when destroy observer.
 *         For details, see {@link Pasteboard_Finalize}.
 * @return Returns the status code of the execution. For details, see {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_PasteboardObserver Pasteboard_Notify PASTEBOARD_ErrCode.
 * @since 13
 */
int OH_PasteboardObserver_SetData(OH_PasteboardObserver* observer, void* context,
    const Pasteboard_Notify callback, const Pasteboard_Finalize finalize);

/**
 * @brief Represents the Pasteboard information.
 *
 * @since 13
 */
typedef struct OH_Pasteboard OH_Pasteboard;

/**
 * @brief Creates a {@link OH_Pasteboard} instance.
 *
 * @return Returns the pointer to the {@link OH_Pasteboard} instance created if the operation is successful.
 * Returns nullptr if the memory is not enough.
 * @see OH_Pasteboard.
 * @since 13
 */
OH_Pasteboard* OH_Pasteboard_Create();

/**
 * @brief Destroy a {@link OH_Pasteboard} instance.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance to destroy.
 * @see OH_Pasteboard.
 * @since 13
 */
void OH_Pasteboard_Destroy(OH_Pasteboard* pasteboard);

/**
 * @brief Subscribes to the Pasteboard data change.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @param type Event type to subscribe to.
 * @param observer - Pointer to the observer information, which specifies the callback used to
 * reporting the pasteboard data change. For details, see {@link OH_PasteboardObserver}.
 * @return Returns the status code of the execution. For details, {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_Pasteboard OH_PasteboardObserver PASTEBOARD_ErrCode.
 * @since 13
 */
int OH_Pasteboard_Subscribe(OH_Pasteboard* pasteboard, int type, const OH_PasteboardObserver* observer);

/**
 * @brief Unsubscribes from the Pasteboard data change.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @param type Event type to subscribe to.
 * @param observer - Pointer to the observer information, which specifies the callback used to
 * reporting the pasteboard data change. For details, see {@link OH_PasteboardObserver}.
 * @return Returns the status code of the execution. For details, {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_Pasteboard OH_PasteboardObserver PASTEBOARD_ErrCode.
 * @since 13
 */
int OH_Pasteboard_Unsubscribe(OH_Pasteboard* pasteboard, int type, const OH_PasteboardObserver* observer);

/**
 * @brief Checks whether the Pasteboard data is from a remote device.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @return Returns a boolean value, which indicates whether the the data is from a remote device.
 *         The value {@code false} means Pasteboard data is not from a remote device.
 *         The value {@code true} means the opposite.
 * @see OH_Pasteboard.
 * @since 13
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
 * @since 13
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
 * @since 13
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
 * @since 13
 */
bool OH_Pasteboard_HasData(OH_Pasteboard* pasteboard);

/**
 * @brief Obtains data from the Pasteboard.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @param status The status code of the execution. For details, see {@link PASTEBOARD_ErrCode}.
 * @return Returns the pointer to the {@link OH_UdmfData} instance.
 * @see OH_Pasteboard OH_UdmfData PASTEBOARD_ErrCode.
 * @since 13
 */
OH_UdmfData* OH_Pasteboard_GetData(OH_Pasteboard* pasteboard, int* status);

/**
 * @brief Writes data to the Pasteboard.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @param data Pointer to the {@link OH_UdmfData} instance.
 * @return Returns the status code of the execution. For details, see {@link PASTEBOARD_ErrCode}.
 *         Returns {@link ERR_OK} if the operation is successful.
 *         Returns {@link ERR_INVALID_PARAMETER} if invalid args are detected.
 * @see OH_Pasteboard OH_UdmfData PASTEBOARD_ErrCode.
 * @since 13
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
 * @since 13
 */
int OH_Pasteboard_ClearData(OH_Pasteboard* pasteboard);

/**
 * @brief Obtains all MIME types of Pasteboard data.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @param count Poniter to the count of MIME types.
 * @return Returns char array of MIME types in the Pasteboard.
 * Returns nullptr if the operation is failed.
 * @see OH_Pasteboard.
 * @since 14
 */
char **OH_Pasteboard_GetMimeTypes(OH_Pasteboard *pasteboard, unsigned int *count);

/**
 * @brief Gets the number of Pasteboard data changes.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @return the number of Pasteboard data changes.
 * Returns 0 means initial value or invalid value.In this case, no action is required.
 * @since 16
 */
uint32_t OH_Pasteboard_GetChangeCount(OH_Pasteboard *pasteboard);

/**
 * @brief Obtains data from the Pasteboard with system progress indicator.
 *
 * @permission ohos.permission.READ_PASTEBOARD
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @param params Pointer to indicates the  {@link OH_Pasteboard_GetDataParams}.
 * @param status The status code of the execution. For details, see {@link PASTEBOARD_Errcode}.
 * @return Returns the pointer to the {@link OH_PasteData} instance.
 * @see OH_Pasteboard OH_PasteData PASTEBOARD_ErrCode.
 * @since 15
 */
OH_UdmfData *OH_Pasteboard_GetDataWithProgress(OH_Pasteboard *pasteboard, OH_Pasteboard_GetDataParams *params,
    int *status);
#ifdef __cplusplus
};
#endif

/** @} */
#endif
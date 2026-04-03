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
 * @file oh_pasteboard.h
 *
 * @brief Provides data structure, enum types, and APIs for accessing the system pasteboard.
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
* @brief MIME type of plain text.
*
* @since 22
*/
#define PASTEBOARD_MIMETYPE_TEXT_PLAIN "text/plain"
/**
* @brief MIME type of URI.
*
* @since 22
*/
#define PASTEBOARD_MIMETYPE_TEXT_URI "text/uri"
/**
* @brief MIME type of HTML text.
*
* @since 22
*/
#define PASTEBOARD_MIMETYPE_TEXT_HTML "text/html"
/**
* @brief MIME type of PixelMap.
*
* @since 22
*/
#define PASTEBOARD_MIMETYPE_PIXELMAP "pixelMap"
/**
* @brief MIME type of want.
*
* @since 22
*/
#define PASTEBOARD_MIMETYPE_TEXT_WANT "text/want"

/**
 * @brief Enumerates the data change types of the pasteboard.
 *
 * @since 13
 */
typedef enum Pasteboard_NotifyType {
    /**
     * @brief The pasteboard data of the local device is changed.
     *
     */
    NOTIFY_LOCAL_DATA_CHANGE = 1,

    /**
     * @brief The pasteboard data of a non-local device on the network is changed.
     *
     */
    NOTIFY_REMOTE_DATA_CHANGE = 2
} Pasteboard_NotifyType;

/**
 * @brief Enumerates the options used to resolve file copy conflicts.
 *
 * @since 15
 */
typedef enum Pasteboard_FileConflictOptions {
    /**
     * @brief Overwrites the file with the same name in the destination directory.
     *
     */
    PASTEBOARD_OVERWRITE = 0,

    /**
     * @brief Skips the file if there is a file with the same name in the destination directory.
     * 
     */
    PASTEBOARD_SKIP = 1
} Pasteboard_FileConflictOptions;

/**
 * @brief Enumerates the progress indicator options. You can use the default progress indicator as required.
 *
 * @since 15
 */
typedef enum Pasteboard_ProgressIndicator {
    /**
     * @brief The system default progress indicator is not used.
     *
     */
    PASTEBOARD_NONE = 0,

    /**
     * @brief The system default progress indicator is used.
     *
     */
    PASTEBOARD_DEFAULT = 1
} Pasteboard_ProgressIndicator;

/**
 * @brief Defines a struct for the progress information.
 *
 * @since 15
 */
typedef struct Pasteboard_ProgressInfo Pasteboard_ProgressInfo;

/**
 * @brief Defines a callback to be invoked to obtain the progress information when the default progress indicator is
 * not used.
 *
 * @param progressInfo A struct for the progress information. 
 * This information is reported only when {@link Pasteboard_ProgressInfo} is set to **NONE**.
 * @since 15
 */
typedef void (*OH_Pasteboard_ProgressListener)(Pasteboard_ProgressInfo* progressInfo);

/**
 * @brief Defines the parameters required for obtaining the pasteboard data and paste progress.
 *
 * @since 15
 */
typedef struct Pasteboard_GetDataParams Pasteboard_GetDataParams;

/**
 * @brief Defines a callback to be invoked when the pasteboard content changes.
 *
 * @param context Context information, which is passed by the {@link OH_PasteboardObserver_SetData} function.
 * @param type Data change type. For details, see {@link Pasteboard_NotifyType}.
 * @since 13
 */
typedef void (*Pasteboard_Notify)(void* context, Pasteboard_NotifyType type);

/**
 * @brief Defines a callback to be invoked to release the context when the pasteboard observer object is destroyed.
 *
 * @param context Pointer to the context to release.
 * @since 13
 */
typedef void (*Pasteboard_Finalize)(void* context);

/**
 * @brief Defines the pasteboard observer.
 *
 * @since 13
 */
typedef struct OH_PasteboardObserver OH_PasteboardObserver;

/**
 * @brief Creates an {@link OH_PasteboardObserver} instance and a pointer to it.
 *
 * @return Returns a pointer to the {@link OH_PasteboardObserver} instance created if the operation is successful;
 * returns **nullptr** otherwise.
 * If this pointer is no longer required, use {@link OH_PasteboardObserver_Destroy} to destroy it. Otherwise, memory
 * leaks may occur.
 * @see OH_PasteboardObserver.
 * @since 13
 */
OH_PasteboardObserver* OH_PasteboardObserver_Create();

/**
 * @brief Destroys the {@link OH_PasteboardObserver} instance.
 *
 * @param observer Pointer to an {@link OH_PasteboardObserver} instance.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_PasteboardObserver PASTEBOARD_ErrCode.
 * @since 13
 */
int OH_PasteboardObserver_Destroy(OH_PasteboardObserver* observer);

/**
 * @brief Sets a callback for the pasteboard observer.
 *
 * @param observer Pointer to an {@link OH_PasteboardObserver} instance.
 * @param context Pointer to the context, which is passed to {@link Pasteboard_Notify} as the first parameter.
 * @param callback Callback to be invoked when the data changes. For details, see {@link Pasteboard_Notify}.
 * @param finalize Optional callback, which can be used to release context data when the pasteboard observer is
 * destroyed. For details, see {@link Pasteboard_Finalize}.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_PasteboardObserver Pasteboard_Notify PASTEBOARD_ErrCode.
 * @since 13
 */
int OH_PasteboardObserver_SetData(OH_PasteboardObserver* observer, void* context,
    const Pasteboard_Notify callback, const Pasteboard_Finalize finalize);

/**
 * @brief Defines the pasteboard object to operate the system pasteboard.
 *
 * @since 13
 */
typedef struct OH_Pasteboard OH_Pasteboard;

/**
 * @brief Creates an {@link OH_Pasteboard} instance and a pointer to it.
 *
 * @return Returns a pointer to the {@link OH_Pasteboard} instance created if the operation is successful;
 * returns **nullptr** otherwise.
 * If this pointer is no longer required, use {@link OH_PasteboardObserver_Destroy} to destroy it. Otherwise, memory
 * leaks may occur.
 * @see OH_Pasteboard.
 * @since 13
 */
OH_Pasteboard* OH_Pasteboard_Create();

/**
 * @brief Destroys the {@link OH_Pasteboard} instance.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @see OH_Pasteboard.
 * @since 13
 */
void OH_Pasteboard_Destroy(OH_Pasteboard* pasteboard);

/**
 * @brief Subscribes to the pasteboard observer.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param type Subscribed data change type of the pasteboard. For details, see {@link Pasteboard_NotifyType}.
 * @param observer Pointer to an {@link OH_PasteboardObserver} instance. It specifies the callback to be invoked when
 * the pasteboard data changes. For details, see {@link OH_PasteboardObserver}.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_Pasteboard OH_PasteboardObserver Pasteboard_NotifyType PASTEBOARD_ErrCode.
 * @since 13
 */
int OH_Pasteboard_Subscribe(OH_Pasteboard* pasteboard, int type, const OH_PasteboardObserver* observer);

/**
 * @brief Unsubscribes from the pasteboard observer.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param type Subscribed data change type of the pasteboard. For details, see {@link Pasteboard_NotifyType}.
 * @param observer Pointer to an {@link OH_PasteboardObserver} instance. It specifies the callback to be invoked when
 * the pasteboard data changes. For details, see {@link OH_PasteboardObserver}.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_Pasteboard OH_PasteboardObserver Pasteboard_NotifyType PASTEBOARD_ErrCode.
 * @since 13
 */
int OH_Pasteboard_Unsubscribe(OH_Pasteboard* pasteboard, int type, const OH_PasteboardObserver* observer);

/**
 * @brief Checks whether the pasteboard data comes from remote devices.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @return Returns a Boolean value indicating whether the data comes from a remote device. The value **true** means the
 * data is from a remote device; **false** means the data is from the local device.
 * @see OH_Pasteboard.
 * @since 13
 */
bool OH_Pasteboard_IsRemoteData(OH_Pasteboard* pasteboard);

/**
 * @brief Obtains the pasteboard data source.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param source Pointer to the pasteboard data source instance. You need to allocate the memory for the pointer before
 * calling this API.
 * @param len Memory length corresponding to the source. If the memory length is insufficient, the API call will fail.
 * The recommended length is 128 bytes.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_Pasteboard PASTEBOARD_ErrCode.
 * @since 13
 */
int OH_Pasteboard_GetDataSource(OH_Pasteboard* pasteboard, char* source, unsigned int len);

/**
 * @brief Checks whether the pasteboard contains data of the specified type.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param type Data type to be checked, which includes the basic data types and custom data types. The options of the
 * basic data types are as follows: **"text/plain"**, **"text/html"**, **"text/uri"**, **"text/want"**,
 * and **"pixelMap"**. For details, see {@link Macros}.
 * @return Returns a Boolean value indicating whether the pasteboard contains data of the specified type. The value 
 * **true** means the pasteboard contains data of the specified type; the value **false** means the opposite.
 * @see OH_Pasteboard.
 * @since 13
 */
bool OH_Pasteboard_HasType(OH_Pasteboard* pasteboard, const char* type);

/**
 * @brief Checks whether the pasteboard contains data.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @return Returns a Boolean value indicating whether the pasteboard contains data. The value **true** means the
 * pasteboard contains data; the value **false** means the opposite.
 * @see OH_Pasteboard.
 * @since 13
 */
bool OH_Pasteboard_HasData(OH_Pasteboard* pasteboard);

/**
 * @brief Checks whether the pasteboard data is on a remote device. Transferring data across devices takes time. If the
 * pasteboard data is on a remote device, do not check for custom data types or read the pasteboard data on the UI
 * thread.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @return Returns the check result. The value **true** indicates that the pasteboard data is on a remote device,
 * and **false** indicates the opposite. Default value: **false**.
 * @see OH_Pasteboard.
 * @since 24
 */
bool OH_Pasteboard_HasRemoteData(OH_Pasteboard* pasteboard);

/**
 * @brief Obtains data from the pasteboard.
 *
 * @permission ohos.permission.READ_PASTEBOARD
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param status Output parameter, indicating the error code of the operation.
 * For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * @return Returns the pointer to an {@link OH_UdmfData} instance obtained if the operation is successful; returns a
 * null pointer otherwise.
 * @see OH_Pasteboard OH_UdmfData PASTEBOARD_ErrCode.
 * @since 13
 */
OH_UdmfData* OH_Pasteboard_GetData(OH_Pasteboard* pasteboard, int* status);

/**
 * @brief Writes the unified data object to the OH_Pasteboard instance.
 *
 * @param pasteboard Pointer to the {@link OH_Pasteboard} instance.
 * @param data Pointer to an {@link OH_UdmfData} instance.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_Pasteboard OH_UdmfData PASTEBOARD_ErrCode.
 * @since 13
 */
int OH_Pasteboard_SetData(OH_Pasteboard* pasteboard, OH_UdmfData* data);

/**
 * @brief Clears data in the Pastedboard.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_Pasteboard PASTEBOARD_ErrCode.
 * @since 13
 */
int OH_Pasteboard_ClearData(OH_Pasteboard* pasteboard);

/**
 * @brief Obtains the types of data in the pasteboard.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param count Pointer to the number of MIME types obtained.
 * @return Returns the types obtained if the operation is successful; returns **nullptr** otherwise.
 * @see OH_Pasteboard.
 * @since 14
 */
char **OH_Pasteboard_GetMimeTypes(OH_Pasteboard *pasteboard, unsigned int *count);

/**
 * @brief Obtains the number of pasteboard content changes.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @return Returns the number of pasteboard content changes if this API is called successfully; 
 * otherwise, returns **0**.
 * Even though the pasteboard data expires, or the data becomes empty because of the called **OH_Pasteboard_ClearData**
 * API, the number of data changes remains.
 * When the system is restarted, or the pasteboard service is restarted due to an exception, the number of pasteboard
 * data changes counts from 0. In addition, copying the same data repeatedly is considered to change the data for
 * multiple times. Therefore, each time the data is copied, the number of data changes increases.
 * @since 18
 */
uint32_t OH_Pasteboard_GetChangeCount(OH_Pasteboard *pasteboard);

/**
 * @brief Creates a {@link Pasteboard_GetDataParams} instance and a pointer to it.
 * 
 * @return Returns a pointer to the {@link Pasteboard_GetDataParams} instance created if the operation is successful;
 * returns **nullptr** otherwise.
 * If this pointer is no longer required, use {@link OH_Pasteboard_GetDataParams_Destroy} to destroy it. Otherwise,
 * memory leaks may occur.
 * @see Pasteboard_GetDataParams.
 * @since 15
 */
Pasteboard_GetDataParams *OH_Pasteboard_GetDataParams_Create(void);

/**
 * @brief Destroys the {@link Pasteboard_GetDataParams} instance.
 *
 * @param params Pointer to an **OH_Pasteboard_GetDataParams** instance.
 * @see Pasteboard_GetDataParams.
 * @since 15
 */
void OH_Pasteboard_GetDataParams_Destroy(Pasteboard_GetDataParams* params);

/**
 * @brief Sets a progress indicator in {@link Pasteboard_GetDataParams}.
 * You can use the default progress indicator as required.
 *
 * @param params Pointer to an **OH_Pasteboard_GetDataParams** instance.
 * @param progressIndicator Progress indicator to set.
 * @see Pasteboard_GetDataParams Pasteboard_ProgressIndicator.
 * @since 15
 */
void OH_Pasteboard_GetDataParams_SetProgressIndicator(Pasteboard_GetDataParams* params,
    Pasteboard_ProgressIndicator progressIndicator);

/**
 * @brief Sets the destination URI for copying files. If file processing is not supported, this parameter is not
 * required. If the application involves complex file processing policies or needs to distinguish file multipathing
 * storage, you are advised not to set this parameter but let the application copies files by itself.
 *
 * @param params Pointer to an **OH_Pasteboard_GetDataParams** instance.
 * @param destUri Destination URI of the copied file.
 * @param destUriLen Length of the destination URI of the copied file.
 * @see Pasteboard_GetDataParams.
 * @since 15
 */
void OH_Pasteboard_GetDataParams_SetDestUri(Pasteboard_GetDataParams* params, const char* destUri, uint32_t destUriLen);

/**
 * @brief Sets the options used to resolve file copy conflicts in a {@link Pasteboard_GetDataParams} instance.
 *
 * @param params Pointer to an **OH_Pasteboard_GetDataParams** instance.
 * @param option Options used to resolve file copy conflicts. The default value is **PASTEBOARD_OVERWRITE**.
 * @see Pasteboard_GetDataParams Pasteboard_FileConflictOptions.
 * @since 15
 */
void OH_Pasteboard_GetDataParams_SetFileConflictOptions(Pasteboard_GetDataParams* params,
    Pasteboard_FileConflictOptions option);

/**
 * @brief Sets a progress listener in a {@link Pasteboard_GetDataParams} instance.
 * 
 * @param params Pointer to an **OH_Pasteboard_GetDataParams** instance.
 * @param listener Progress listener.
 * @see Pasteboard_GetDataParams OH_Pasteboard_ProgressListener.
 * @since 15
 */
void OH_Pasteboard_GetDataParams_SetProgressListener(Pasteboard_GetDataParams* params,
    const OH_Pasteboard_ProgressListener listener);

/**
 * @brief Obtains the paste progress in a {@link Pasteboard_ProgressInfo} instance.
 *
 * @param progressInfo Pointer to a {@link Pasteboard_ProgressInfo} instance.
 * @return Percentage of the paste progress.
 * @see Pasteboard_ProgressInfo.
 * @since 15
 */
int OH_Pasteboard_ProgressInfo_GetProgress(Pasteboard_ProgressInfo* progressInfo);

/**
 * @brief Cancels the ongoing paste operation when the pasteboard data is obtained.
 * 
 * @param params Pointer to an **OH_Pasteboard_GetDataParams** instance.
 * @see Pasteboard_GetDataParams.
 * @since 15
 */
void OH_Pasteboard_ProgressCancel(Pasteboard_GetDataParams* params);

/**
 * @brief Obtains the pasteboard data and paste progress. Folders cannot be copied.
 *
 * @permission ohos.permission.READ_PASTEBOARD
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param params Pointer to an **OH_Pasteboard_GetDataParams** instance.
 * @param status Output parameter, indicating the error code of the operation.
 * For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * @return Returns a pointer to the **OH_UdmfData** instance obtained if the operation is successful; returns a null
 * pointer otherwise.
 * @see OH_Pasteboard OH_PasteData PASTEBOARD_ErrCode.
 * @since 15
 */
OH_UdmfData* OH_Pasteboard_GetDataWithProgress(OH_Pasteboard* pasteboard, Pasteboard_GetDataParams* params,
    int* status);

/**
 * @brief Syncs all delayed data from the application to the pasteboard. Use this API together with the
 * {@link OH_UdmfRecordProvider_SetData}API.When the application uses the delayed copy feature,
 * only the data types supported by the application are written to the pasteboard. Before the application exits,
 * it should call the {@link OH_Pasteboard_SetData} API to submit all copied data or call the
 * **OH_Pasteboard_SyncDelayedDataAsync** API to notify the pasteboard to obtain all data. The application can exit only
 * after the data sync is complete. Otherwise, other applications may fail to obtain the data.
 * 
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param callback Indicates the pointer to the callback that is called after the synchronize is finished.
 * @since 21
 */
void OH_Pasteboard_SyncDelayedDataAsync(OH_Pasteboard* pasteboard, void (*callback)(int errorCode));
#ifdef __cplusplus
};
#endif

/** @} */
#endif
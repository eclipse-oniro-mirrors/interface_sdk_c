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
 * URI, PixelMap, and other types.
 *
 * @since 13
 */

/**
 * @file oh_pasteboard.h
 *
 * @brief Provides data structure, enum types, and APIs for accessing the system pasteboard.
 *
 * @kit BasicServicesKit
 * @include <database/pasteboard/oh_pasteboard.h>
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
 * @brief Plain text type.
 *
 * @since 22
 */
#define PASTEBOARD_MIMETYPE_TEXT_PLAIN "text/plain"
/**
 * @brief URI type.
 *
 * @since 22
 */
#define PASTEBOARD_MIMETYPE_TEXT_URI "text/uri"
/**
 * @brief HTML type.
 *
 * @since 22
 */
#define PASTEBOARD_MIMETYPE_TEXT_HTML "text/html"
/**
 * @brief PixelMap type.
 *
 * @since 22
 */
#define PASTEBOARD_MIMETYPE_PIXELMAP "pixelMap"
/**
 * @brief Want type.
 *
 * @since 22
 */
#define PASTEBOARD_MIMETYPE_TEXT_WANT "text/want"

/**
 * @brief Enumerates the data change types of the pasteboard. This enum is used to determine whether the pasteboard
 * data change is from the local device or a remote device.
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
 * @brief Enumerates the options used to resolve file copy conflicts. When a file with the same name already exists in
 * the destination directory, the pasteboard handles the conflict based on the specified policy.
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
     * @brief The default progress indicator is not used.
     *
     */
    PASTEBOARD_NONE = 0,
    /**
     * @brief The default progress indicator is used.
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
 * @brief Defines a callback to notify the app about the progress of the pasting task when the default
 * progress indicator is not used. This callback is used to support the implementation of a custom progress UI.
 *
 * @param progressInfo Progress information. This information is reported only when {@link Pasteboard_ProgressIndicator}
 *  is set to **PASTEBOARD_NONE**.
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
 * @brief Defines a callback to be invoked when the pasteboard content changes. Implement this callback when you need
 * to execute app-specific logic upon pasteboard content changes.
 *
 * @param context Context, which is passed in by the {@link OH_PasteboardObserver_SetData} function.
 * @param type Data change type. For details, see {@link Pasteboard_NotifyType}.
 * @since 13
 */
typedef void (*Pasteboard_Notify)(void* context, Pasteboard_NotifyType type);

/**
 * @brief Defines a callback to be invoked to release the context when the pasteboard observer object is destroyed. If
 * resources are dynamically allocated in the **Pasteboard_Notify** callback, you need to implement this callback to
 * release the resources.
 *
 * @param context Pointer to the context to release. If **context** points to dynamic memory or resources that need to
 * be manually released, release them in the callback. If **context** points to static memory or resources that do not
 * need to be managed, you do not need to perform any operation in the callback.
 * @since 13
 */
typedef void (*Pasteboard_Finalize)(void* context);

/**
 * @brief Defines a pasteboard observer to listen for pasteboard data change events.
 * When the pasteboard content is updated, a callback will be invoked to notify the application.
 * This API is used in applications that need to respond to pasteboard content changes.
 *
 * @since 13
 */
typedef struct OH_PasteboardObserver OH_PasteboardObserver;
/**
 * @brief Creates an {@link OH_PasteboardObserver} instance and a pointer to it. Typical use scenarios include listening
 * for pasteboard content changes to implement data synchronization and triggering service logic when the pasteboard
 * content is updated. After this function is called, the system initializes a **PasteboardObserver** instance and
 * returns a pointer to it. After the instance is created, you need to call {@link OH_PasteboardObserver_SetData}
 * to set the callback function and then call {@link OH_Pasteboard_Subscribe} to subscribe to pasteboard change events.
 *
 * - The caller must call [OH_PasteboardObserver_Destroy](#oh_pasteboardobserver_destroy) to release resources
 * when the pasteboard data changes do not need to be listened for. Otherwise, memory leaks may occur.
 * - The observer instance does not support multi-thread concurrent access and
 * must be created and destroyed in the same thread.
 *
 * @return Returns a pointer to the {@link OH_PasteboardObserver} instance created if the operation is successful;
 * returns **nullptr** otherwise.
 * If this pointer is no longer required, use {@link OH_PasteboardObserver_Destroy} to destroy it. Otherwise, memory
 * leak may occur.
 * @see OH_PasteboardObserver
 * @since 13
 */
OH_PasteboardObserver* OH_PasteboardObserver_Create();
/**
 * @brief
 * Destroys the OH_PasteboardObserver instance. When you no longer need to listen for clipboard data changes,
 * call this function to destroy the observer object. Before calling this function,
 * ensure that you have called OH_Pasteboard_Unsubscribe to cancel the subscription.
 *
 * @param observer Pointer to an {@link OH_PasteboardObserver} instance.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_PasteboardObserver
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
int OH_PasteboardObserver_Destroy(OH_PasteboardObserver* observer);

/**
 * @brief Sets a callback for the pasteboard observer. When an application needs to perform specific operations (such
 * as updating the UI display or synchronizing data to other modules) when the pasteboard data changes, this API is
 * used to set a callback function. After the setting is complete, the callback is triggered when the pasteboard data
 * of the corresponding type changes. The callback is usually executed in the system thread. Therefore, pay attention
 * to thread security. The lifecycle of the callback function must be no shorter than that of the observer.
 *
 * @param observer Pointer to an {@link OH_PasteboardObserver} instance.
 * @param context Pointer to the context data, which is passed to {@link Pasteboard_Notify} as the first parameter.
 * @param callback Callback for data changes, which is triggered when the pasteboard data changes.
 * For details, see {@link Pasteboard_Notify}.
 * @param finalize Optional callback, which can be used to release context data when the pasteboard observer is
 * destroyed. The default value is **nullptr**, indicating that no release operation is performed.
 * For details, see {@link Pasteboard_Finalize}.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_PasteboardObserver
 * @see Pasteboard_Notify
 * @see PASTEBOARD_ErrCode
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
 * @brief Creates an {@link OH_Pasteboard} instance and a pointer to it. Before accessing or operating the system
 * pasteboard, call this function to create a pasteboard instance. After the instance is created, use it in time.
 *
 * @return Returns a pointer to the {@link OH_Pasteboard} instance created if the operation is successful;
 * returns **nullptr** otherwise.
 * If this pointer is no longer required, use {@link OH_Pasteboard_Destroy} to destroy it.
 * Otherwise, memory leaks may occur.
 * @see OH_Pasteboard
 * @since 13
 */
OH_Pasteboard* OH_Pasteboard_Create();

/**
 * @brief Destroys the {@link OH_Pasteboard} instance. When access to the pasteboard is no longer required, destroy the
 * pasteboard instance to release resources. Before destroying the pasteboard instance, ensure that all subscribers
 * have been canceled.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @see OH_Pasteboard
 * @since 13
 */
void OH_Pasteboard_Destroy(OH_Pasteboard* pasteboard);

/**
 * @brief Subscribes to pasteboard data changes. Typical use scenarios include listening for pasteboard content changes,
 * implementing cross-device pasteboard data synchronization, and updating the UI when the pasteboard content changes.
 * After this function is called, the system notifies the application using the observer
 * callback {@link Pasteboard_Notify} when the pasteboard data changes. The application can subscribe to data change
 * events of the local device or a remote device by specifying the event type using **type**.
 *
 * - After this API is called to subscribe to pasteboard change events, you must call {@link OH_Pasteboard_Unsubscribe
 * to unsubscribe from the events when the listening is no longer needed.
 * - The same observer instance and event type must be passed for subscribing to and unsubscribing
 * from pasteboard change events.
 * - If the events are not subscribed from, continuous listening and resource occupation may occur.
 * - The same observer cannot subscribe to the same type of events repeatedly. Otherwise, an error will be returned.
 * - The observer instance cannot be destroyed before the events are unsubscribed from.
 * - The callback is executed in an asynchronous IPC thread. Therefore, pay attention to thread security.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param type Subscribed data change type of the pasteboard. For details, see {@link Pasteboard_NotifyType}.
 * @param observer Pointer to an {@link OH_PasteboardObserver} instance. It specifies the callback to be invoked
 * when the pasteboard data changes. For details, see {@link OH_PasteboardObserver}.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_Pasteboard
 * @see OH_PasteboardObserver
 * @see Pasteboard_NotifyType
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
int OH_Pasteboard_Subscribe(OH_Pasteboard* pasteboard, int type, const OH_PasteboardObserver* observer);

/**
 * @brief Unsubscribes from pasteboard data changes. Before calling this API, you must call **OH_Pasteboard_Subscribe**
 * to subscribe to pasteboard data changes. Unsubscribe from pasteboard data changes when they are no longer needed to
 * release resources.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param type Type of pasteboard data change subscribed to, which must be the same as the type value passed when the
 * application subscribes to the change events. For details, see {@link Pasteboard_NotifyType}.
 * @param observer Pointer to an {@link OH_PasteboardObserver} instance. It specifies the callback to be invoked when
 * the pasteboard data changes. For details, see {@link OH_PasteboardObserver}.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_Pasteboard
 * @see OH_PasteboardObserver
 * @see Pasteboard_NotifyType
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
int OH_Pasteboard_Unsubscribe(OH_Pasteboard* pasteboard, int type, const OH_PasteboardObserver* observer);

/**
 * @brief Checks whether the pasteboard data comes from remote devices. Typical use scenarios include cross-device
 * pasteboard data synchronization, selecting a processing policy based on the data source in distributed scenarios,
 * and implementing security verification of the data source.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @return Returns a Boolean value indicating whether the data comes from a remote device. The value **true** means the
 * data is from a remote device; **false** means the data is from the local device.
 * @see OH_Pasteboard
 * @since 13
 */
bool OH_Pasteboard_IsRemoteData(OH_Pasteboard* pasteboard);

/**
 * @brief Obtains the pasteboard data source. This API can be used to identify the data source or control permissions.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param source Pointer to the pasteboard data source instance. You need to allocate the memory for the pointer before
 * calling this API. The recommended size is 128 bytes.
 * @param len Memory length allocated for the source length. The value must be greater than or equal to the length of
 * the data source string (including the string terminator). The recommended length is 128 bytes. If the memory length
 * is insufficient, the error code **ERR_INVALID_PARAMETER** is returned.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_Pasteboard
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
int OH_Pasteboard_GetDataSource(OH_Pasteboard* pasteboard, char* source, unsigned int len);

/**
 * @brief Checks whether the pasteboard contains data of the specified type. Typical use scenarios include checking
 * whether the pasteboard data type is supported before pasting, selecting different processing methods based on the
 * data type, and verifying the pasteboard data format.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param type Data type to be checked, which includes the basic data types and custom data types. The options of the
 * basic data types are as follows: **"text/plain"**, **"text/html"**, **"text/uri"**, **"text/want"**,
 * and **"pixelMap"**. For details, see {@link Macros}.
 * @return Returns a Boolean value indicating whether the pasteboard contains data of the specified type.
 * The value **true** means the pasteboard contains data of the specified type; the value **false** means the opposite.
 * @see OH_Pasteboard
 * @since 13
 */
bool OH_Pasteboard_HasType(OH_Pasteboard* pasteboard, const char* type);

/**
 * @brief Checks whether the pasteboard contains data. Before reading data from the pasteboard, check whether the
 * pasteboard contains data to prevent performing any operation when there is no data.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @return Returns a Boolean value indicating whether the pasteboard contains data. The value **true** means the
 * pasteboard contains data; the value **false** means the opposite.
 * @see OH_Pasteboard
 * @since 13
 */
bool OH_Pasteboard_HasData(OH_Pasteboard* pasteboard);
/**
 * @brief Obtains data from the pasteboard. After this function is called, the system reads the content from the
 * pasteboard and returns the pointer to an {@link OH_UdmfData} instance. You can use **OH_UdmfData** APIs to parse
 * data. You need to manually release the obtained data object. The delay in obtaining data from the pasteboard is
 * affected by the data volume and network environment. Therefore, calling this API may take a long time. You are
 * advised to call this API in non-UI threads.
 *
 * - If the pasteboard is empty or the data format is not supported, **nullptr** is returned.
 * - The returned **OH_UdmfData** object needs to be released by calling {@link OH_UdmfData_Destroy}.
 * - If a large amount of data is pasted, you are advised to use {@link OH_Pasteboard_GetDataWithProgress} to
 * obtain the progress.
 *
 * @permission ohos.permission.READ_PASTEBOARD
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param status Output parameter, indicating the error code of the operation.
 * For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * @return Returns the pointer to an {@link OH_UdmfData} instance obtained if the operation is successful; returns a
 * null pointer otherwise.
 * @see OH_Pasteboard
 * @see OH_UdmfData
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
OH_UdmfData* OH_Pasteboard_GetData(OH_Pasteboard* pasteboard, int* status);

/**
 * @brief Checks whether the pasteboard data is on a remote device. Transferring data across devices takes time. If the
 * pasteboard data is on a remote device, do not check for custom data types or read the pasteboard data on the UI
 * thread.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @return Returns the check result. The value **true** indicates that the pasteboard data is on a remote device,
 * and **false** indicates the opposite. Default value: **false**.
 * @see OH_Pasteboard
 * @since 24
 */
bool OH_Pasteboard_HasRemoteData(OH_Pasteboard* pasteboard);

/**
 * @brief Sets the unified data object in the **OH_Pasteboard** instance. After the data is written successfully, other
 * apps can use the APIs for reading data provided by the system pasteboard to access the data. The size of the unified
 * data object is limited by the capacity of the system pasteboard. After the data is written to the system pasteboard,
 * the lifecycle of the data is managed by the system pasteboard. After this function is called, valid data is written
 * to the system pasteboard, overwriting the previous data. After the data is written successfully, the callback
 * function of all observers that have subscribed to the pasteboard data change event is triggered. Other apps can read
 * the data through the pasteboard APIs.
 *
 * - The size of the serialized data cannot exceed the system capacity, which varies depending on the device
 * and is usually 128 MB.
 * - The write operation will clear all the existing data in the pasteboard.
 * - When a large amount of data needs to be copied, you are advised to use the delayed copy feature
 * to improve performance.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param data Pointer to an {@link OH_UdmfData} instance.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_Pasteboard
 * @see OH_UdmfData
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
int OH_Pasteboard_SetData(OH_Pasteboard* pasteboard, OH_UdmfData* data);

/**
 * @brief Clears data from the pasteboard. This API can be used to clear data from the pasteboard, for example,
 * clearing sensitive data when exiting an app.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @return Returns an error code. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * Returns **ERR_OK** if the operation is successful.
 * Returns **ERR_INVALID_PARAMETER** if an invalid parameter is passed in.
 * @see OH_Pasteboard
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
int OH_Pasteboard_ClearData(OH_Pasteboard* pasteboard);

/**
 * @brief Obtains the MIME types from the pasteboard. Typical use scenarios include determining the pasteboard data
 * type to select a proper processing method and checking whether the data type is supported before pasting.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param count Pointer to the number of MIME types obtained.
 * @return Returns a pointer to an array of all data records on the pasteboard of the MIME type if the operation is
 * successful; returns **nullptr** otherwise. The array size is specified by the **count** parameter.
 * @see OH_Pasteboard
 * @since 14
 */
char **OH_Pasteboard_GetMimeTypes(OH_Pasteboard *pasteboard, unsigned int *count);

/**
 * @brief Obtains the number of pasteboard content changes. Typical use scenarios include determining whether the
 * pasteboard content has changed, implementing incremental pasteboard data synchronization, checking whether the
 * pasteboard content has expired, and optimizing the cache based on the change count.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @return Returns the number of pasteboard content changes if this API is called successfully;
 * otherwise, returns **0**.
 * @since 18
 */
uint32_t OH_Pasteboard_GetChangeCount(OH_Pasteboard *pasteboard);
/**
 * @brief Creates a {@link Pasteboard_GetDataParams} instance and a pointer to it. 
 * When an app needs to obtain pasteboard data and monitor the progress (for example, in large file copy scenarios),
 * the app can call {@link OH_Pasteboard_GetDataParams_SetProgressIndicator},
 * {@link OH_Pasteboard_GetDataParams_SetDestUri}, and {@link OH_Pasteboard_GetDataParams_SetFileConflictOptions} to
 * configure the progress bar, destination path for file copy, and file conflict handling options.
 *
 * @return Returns a pointer to the {@link Pasteboard_GetDataParams} instance created if the operation is successful;
 * returns **nullptr** otherwise.
 * If this pointer is no longer required, use {@link OH_Pasteboard_GetDataParams_Destroy} to destroy it. Otherwise,
 * memory leaks may occur.
 * @see Pasteboard_GetDataParams
 * @since 15
 */
Pasteboard_GetDataParams *OH_Pasteboard_GetDataParams_Create(void);

/**
 * @brief Destroys the {@link Pasteboard_GetDataParams} instance. After this function is called,
 * the **Pasteboard_GetDataParams** instance is released, and the parameter configuration becomes invalid.
 * If the parameter object is destroyed when the pasted data is obtained, the progress callback may fail to be
 * triggered. When the **Pasteboard_GetDataParams** instance is no longer needed, destroy it to release resources.
 *
 * - This API must be used in pairs with [OH_Pasteboard_GetDataParams_Create](#oh_pasteboard_getdataparams_create).
 * - The parameter object must be destroyed after {@link OH_Pasteboard_GetDataWithProgress} is called.
 * - This API cannot be called in the progress callback function.
 * @param params Pointer to a **Pasteboard_GetDataParams** instance.
 * @see Pasteboard_GetDataParams
 * @since 15
 */
void OH_Pasteboard_GetDataParams_Destroy(Pasteboard_GetDataParams* params);

/**
 * @brief Sets a progress indicator in {@link Pasteboard_GetDataParams}. You can use the default progress indicator as
 * required. Typical use scenarios: Set **Pasteboard_ProgressIndicator** to **PASTEBOARD_DEFAULT** to display the
 * default progress bar when large files need to be pasted, and to **PASTEBOARD_NONE** when a custom progress UI or
 * silent paste is required.
 *
 * @param params Pointer to a **Pasteboard_GetDataParams** instance.
 * @param progressIndicator Progress indicator to set.
 * @see Pasteboard_GetDataParams
 * @see Pasteboard_ProgressIndicator
 * @since 15
 */
void OH_Pasteboard_GetDataParams_SetProgressIndicator(Pasteboard_GetDataParams* params,
    Pasteboard_ProgressIndicator progressIndicator);

/**
 * @brief Sets the destination URI for copying files. If file processing is not supported, you do not need to set this
 * parameter. If complex file processing policies are involved or multi-path file storage is required, you are advised
 * to leave this parameter unspecified and let the application handle file copying. This parameter is used to copy a
 * file from the pasteboard to a specified destination URI.
 *
 * @param params Pointer to a **Pasteboard_GetDataParams** instance.
 * @param destUri Destination URI of the copied file. The path must be an absolute path, and the app must have the read
 * and write permissions on the path.
 * @param destUriLen Length of the destination URI (including a string terminator) of the copied file, in bytes. The
 * value must be equal to the actual length of the string pointed to by **destUri**. If the input value is **0** or
 * does not match the actual length, the API call fails.
 * @see Pasteboard_GetDataParams
 * @since 15
 */
void OH_Pasteboard_GetDataParams_SetDestUri(Pasteboard_GetDataParams* params, const char* destUri, uint32_t destUriLen);
/**
 * @brief Sets the options used to resolve file copy conflicts in a {@link Pasteboard_GetDataParams} instance.
 * When calling {@link OH_Pasteboard_GetDataWithProgress}, pass the {@link Pasteboard_GetDataParams} instance with the
 * options used to resolve file copy conflicts as a parameter. When copying a file, if a file with the same name
 * already exists in the destination directory, you need to set a conflict handling policy.
 *
 * - **PASTEBOARD_OVERWRITE**: Select this parameter if you want to overwrite the existing file with
 * the latest file content.
 * - **PASTEBOARD_SKIP**: Select this parameter if you want to retain the original file.
 *
 * @param params Pointer to a **Pasteboard_GetDataParams** instance.
 * @param option Options used to resolve file copy conflicts. The default value is **PASTEBOARD_OVERWRITE**.
 * @see Pasteboard_GetDataParams Pasteboard_FileConflictOptions
 * @since 15
 */
void OH_Pasteboard_GetDataParams_SetFileConflictOptions(Pasteboard_GetDataParams* params,
    Pasteboard_FileConflictOptions option);

/**
 * @brief Sets a progress listener in a {@link Pasteboard_GetDataParams} instance. This callback is used to receive
 * progress updates when you need to customize a progress display UI or silently process pasteboard tasks in the
 * background.
 *
 * @param params Pointer to a **Pasteboard_GetDataParams** instance.
 * @param listener Progress listener. This parameter is valid only when {@link progressIndicator} is set to
 * **PASTEBOARD_NONE**. This parameter can be set to **NULL**, indicating that no progress callback is required.
 * @see Pasteboard_GetDataParams
 * @see OH_Pasteboard_ProgressListener
 * @since 15
 */
void OH_Pasteboard_GetDataParams_SetProgressListener(Pasteboard_GetDataParams* params,
    const OH_Pasteboard_ProgressListener listener);

/**
 * @brief Obtains the paste progress in a {@link Pasteboard_ProgressInfo} instance. Typical use scenarios include
 * updating the UI progress bar in a custom progress callback, monitoring the pasting progress of large files, and
 * adjusting the service logic based on the progress.
 *
 * @param progressInfo Pointer to a {@link Pasteboard_ProgressInfo} instance.
 * @return Pasting progress, in percentage. The value ranges from 0 to 100.
 * @see Pasteboard_ProgressInfo
 * @since 15
 */
int OH_Pasteboard_ProgressInfo_GetProgress(Pasteboard_ProgressInfo* progressInfo);

/**
 * @brief Defines a function for canceling the ongoing paste operation. This function is used to interrupt data
 * transfer during the execution of {@link OH_Pasteboard_GetDataWithProgress}. After this function is called, the current paste operation will be terminated. The transferred data may be retained or cleared, depending on the specific operation status. If you need to obtain the pasteboard data after the operation is canceled, call {@link OH_Pasteboard_GetDataWithProgress}
 * again. This function can be used when the user cancels the operation, the transfer is interrupted due to an error,
 * or the paste operation times out.
 *
 * - The cancellation operation is asynchronous and may not take effect immediately.
 * - The cancellation operation is irreversible. Once the operation is canceled, you need to restart the pasting
 * process if you want to obtain the pasteboard data.
 *
 * @param params Pointer to a **Pasteboard_GetDataParams** instance.
 * @see Pasteboard_GetDataParams
 * @since 15
 */
void OH_Pasteboard_ProgressCancel(Pasteboard_GetDataParams* params);
/**
 * @brief Obtains the pasteboard data and paste progress. Folders cannot be copied. After this function is called, the
 * system starts to obtain data from the system pasteboard. If the pasteboard data comes from a remote device or
 * contains a large number of files, the progress is reported through the {@link OH_Pasteboard_ProgressListener}
 * callback. After the data transfer is complete, the pointer to the unified data object is returned. The entire
 * process may take a long time. You are advised to call this function in a non-UI thread.
 *
 * @permission ohos.permission.READ_PASTEBOARD
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param params Pointer to a **Pasteboard_GetDataParams** instance.
 * @param status Output parameter, indicating the error code of the operation. For details about the error codes,
 * see {@link PASTEBOARD_ErrCode}.
 * @return Returns a pointer to the **OH_UdmfData** instance obtained if the operation is successful;
 * returns a null pointer otherwise.
 * @see OH_Pasteboard OH_PasteData PASTEBOARD_ErrCode
 * @since 15
 */
OH_UdmfData* OH_Pasteboard_GetDataWithProgress(OH_Pasteboard* pasteboard, Pasteboard_GetDataParams* params,
    int* status);

/**
 * @brief Syncs all delayed data from the app to the pasteboard. Delayed data refers to the data transfer mechanism of
 * writing data to the pasteboard first and then loading data in delayed mode as required.
 * Use this API together with {@link OH_UdmfRecordProvider_SetData}. When all delayed data is synced, an asynchronous
 * callback is used to notify the app. When the application uses the delayed copy feature,
 * only the data types supported by the application are written to the pasteboard. Before the application exits,
 * it should call the {@link OH_Pasteboard_SetData} API to submit all copied data or call the
 * **OH_Pasteboard_SyncDelayedDataAsync** API to notify the pasteboard to obtain all data. The application can exit
 * only after the data sync is complete. Otherwise, other applications may fail to obtain the data.
 *
 * > **NOTE**
 * > - Calling this API prolongs the exit process. You are advised to directly set data to the pasteboard instead of
 * calling the {@link OH_UdmfRecordProvider_SetData} and **OH_Pasteboard_SyncDelayedDataAsync** APIs.
 *
 * @param pasteboard Pointer to an {@link OH_Pasteboard} instance.
 * @param callback Pointer to the callback invoked when data sync is complete. **errorCode** indicates the result of
 * the sync task. For details about the error codes, see {@link PASTEBOARD_ErrCode}.
 * @since 21
 */
void OH_Pasteboard_SyncDelayedDataAsync(OH_Pasteboard* pasteboard, void (*callback)(int errorCode));

#ifdef __cplusplus
};
#endif

/** @} */

/** @} */
#endif
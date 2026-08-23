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
 * @brief 系统剪贴板支持复制和粘贴多种类型的数据。可以使用此模块接口操作纯文本、HTML、URI、PixelMap等多种类型的数据。
 *
 * @since 13
 */

/**
 * @file oh_pasteboard.h
 *
 * @brief 提供访问系统剪贴板的接口、数据结构、枚举类型。支持剪贴板数据的读写、监听剪贴板内容变化、获取粘贴进度等功能。
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
 * @brief 纯文本类型。
 *
 * @since 22
 */
#define PASTEBOARD_MIMETYPE_TEXT_PLAIN "text/plain"
/**
 * @brief URI类型。
 *
 * @since 22
 */
#define PASTEBOARD_MIMETYPE_TEXT_URI "text/uri"
/**
 * @brief HTML类型。
 *
 * @since 22
 */
#define PASTEBOARD_MIMETYPE_TEXT_HTML "text/html"
/**
 * @brief PixelMap类型。
 *
 * @since 22
 */
#define PASTEBOARD_MIMETYPE_PIXELMAP "pixelMap"
/**
 * @brief Want类型。
 *
 * @since 22
 */
#define PASTEBOARD_MIMETYPE_TEXT_WANT "text/want"

/**
 * @brief 剪贴板的数据变更类型。适用于区分剪贴板数据变更的来源，判断是本地设备还是远端设备的数据变更。
 *
 * @since 13
 */
typedef enum Pasteboard_NotifyType {
    /**
     * @brief 本地设备剪贴板数据变更。
     *
     */
    NOTIFY_LOCAL_DATA_CHANGE = 1,
    /**
     * @brief 组网内的非本地设备剪贴板数据变更。
     *
     */
    NOTIFY_REMOTE_DATA_CHANGE = 2
} Pasteboard_NotifyType;

/**
 * @brief 定义文件拷贝冲突时的选项。当应用粘贴的目标路径已存在同名文件时，剪贴板会基于指定的策略处理冲突。
 *
 * @since 15
 */
typedef enum Pasteboard_FileConflictOptions {
    /**
     * @brief 目标路径存在同文件名时覆盖。
     *
     */
    PASTEBOARD_OVERWRITE = 0,
    /**
     * @brief 目标路径存在同文件名时跳过。
     *
     */
    PASTEBOARD_SKIP = 1
} Pasteboard_FileConflictOptions;

/**
 * @brief 定义进度条指示选项，可选择是否采用系统默认进度显示。
 *
 * @since 15
 */
typedef enum Pasteboard_ProgressIndicator {
    /**
     * @brief 不采用系统默认进度显示。
     *
     */
    PASTEBOARD_NONE = 0,
    /**
     * @brief 采用系统默认进度显示。
     *
     */
    PASTEBOARD_DEFAULT = 1
} Pasteboard_ProgressIndicator;

/**
 * @brief 定义进度上报的数据结构。
 *
 * @since 15
 */
typedef struct Pasteboard_ProgressInfo Pasteboard_ProgressInfo;

/**
 * @brief 当不使用系统默认进度显示时，通过此回调函数通知应用复制粘贴任务的进度，以支持自定义进度 UI 的实现。
 *
 * @param progressInfo 定义进度上报的数据结构，且仅当进度指示选项{@link Pasteboard_ProgressIndicator}设置为PASTEBOARD_NONE时才会上报此信息。
 * @since 15
 */
typedef void (*OH_Pasteboard_ProgressListener)(Pasteboard_ProgressInfo* progressInfo);

/**
 * @brief 表示从剪贴板获取粘贴数据和进度时需要提供的参数。
 *
 * @since 15
 */
typedef struct Pasteboard_GetDataParams Pasteboard_GetDataParams;

/**
 * @brief 定义剪贴板内容变更时触发的回调函数。当剪贴板中保存的复制数据变更后，如果需要执行应用特定的逻辑，实现该回调函数。
 *
 * @param context 上下文信息，由函数{@link OH_PasteboardObserver_SetData}传入。
 * @param type 数据变更的类型。详见：{@link Pasteboard_NotifyType}。
 * @since 13
 */
typedef void (*Pasteboard_Notify)(void* context, Pasteboard_NotifyType type);

/**
 * @brief 定义用于释放上下文的回调函数，剪贴板数据变更观察者对象销毁时触发。如果在Pasteboard_Notify回调中动态申请了资源，需要实现此回调来释放资源。
 *
 * @param context 要释放的上下文指针。当context指向需要手动释放的动态内存或资源时，应在回调函数中释放；当context指向静态内存或无需管理的资源时，回调函数可以不做处理。
 * @since 13
 */
typedef void (*Pasteboard_Finalize)(void* context);

/**
 * @brief 定义剪贴板数据变更观察者。用于监听系统剪贴板数据的变化事件，当剪贴板内容发生更新时，通过回调通知应用。典型使用场景：需要响应剪贴板内容变化的应用。
 *
 * @since 13
 */
typedef struct OH_PasteboardObserver OH_PasteboardObserver;

/**
 * @brief 创建一个剪贴板数据变更观察者{@link OH_PasteboardObserver}指针及实例对象。典型使用场景包括：监听剪贴板内容变化以实现数据同步、在剪贴板内容更新时触发业务逻辑等。
 * 调用此函数后，系统会初始化一个剪贴板数据变更观察者对象，返回指向该对象的指针。创建成功后，开发者需要通过{@link OH_PasteboardObserver_SetData}设置回调函数，
 * 然后通过{@link OH_Pasteboard_Subscribe}订阅剪贴板变更事件。
 *
 * - 调用者应在不需要监听剪贴板数据变更时调用{@link OH_PasteboardObserver_Destroy}释放资源，否则会导致内存泄漏。
 * - 观察者对象不支持多线程并发访问，需要在同一线程中创建和销毁。
 *
 * @return 执行成功时返回一个指向剪贴板数据变更观察者{@link OH_PasteboardObserver}实例对象的指针，否则返回空指针。
 * 当不再需要使用指针时，请使用{@link OH_PasteboardObserver_Destroy}销毁实例对象，否则会导致内存泄漏。
 * @see OH_PasteboardObserver
 * @since 13
 */
OH_PasteboardObserver* OH_PasteboardObserver_Create();

/**
 * @brief 销毁剪贴板数据变更观察者{@link OH_PasteboardObserver}指针指向的实例对象。当不再需要监听剪贴板数据变更时，调用此函数销毁观察者对象，
 * 使用前请确保已调用{@link OH_Pasteboard_Unsubscribe}取消订阅。
 *
 * @param observer 表示指向剪贴板数据变更观察者{@link OH_PasteboardObserver}实例的指针。
 * @return 返回执行的错误码。详见{@link PASTEBOARD_ErrCode}。
 * @see OH_PasteboardObserver
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
int OH_PasteboardObserver_Destroy(OH_PasteboardObserver* observer);

/**
 * @brief 向剪贴板数据变更观察者设置回调函数。当应用需要在剪贴板数据发生变化时执行特定操作（如更新UI显示、同步数据到其他模块）时，通过此接口设置回调函数。设置完成后，当剪贴板发生对应类型的数据变更时将触发回调。
 * 回调通常在系统线程中执行，需注意线程安全。回调函数的生命周期应不短于观察者的生命周期。
 *
 * @param observer 表示指向剪贴板数据变更观察者{@link OH_PasteboardObserver}实例的指针。
 * @param context 表示指向上下文数据的指针，将作为第一个参数传入{@link Pasteboard_Notify}。
 * @param callback 表示数据变更回调函数，在剪贴板数据变更时触发。详见{@link Pasteboard_Notify}。
 * @param finalize 表示可选的回调函数，可以用于剪贴板数据变更观察者销毁时释放上下文数据。默认为nullptr，不执行释放操作。详见{@link Pasteboard_Finalize}。
 * @return 返回执行的错误码。错误码定义详见{@link PASTEBOARD_ErrCode}。
 * 若返回ERR_OK，表示执行成功。
 * 若返回ERR_INVALID_PARAMETER，表示传入了无效参数。
 * @see OH_PasteboardObserver
 * @see Pasteboard_Notify
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
int OH_PasteboardObserver_SetData(OH_PasteboardObserver* observer, void* context,
    const Pasteboard_Notify callback, const Pasteboard_Finalize finalize);

/**
 * @brief 定义剪贴板对象，用以操作系统剪贴板。
 *
 * @since 13
 */
typedef struct OH_Pasteboard OH_Pasteboard;

/**
 * @brief 创建剪贴板{@link OH_Pasteboard}指针及实例对象。当需要访问或操作系统剪贴板时，使用此函数创建剪贴板对象实例。创建成功后请及时使用。
 *
 * @return 执行成功则返回一个指向剪贴板{@link OH_Pasteboard}实例对象的指针，否则返回nullptr。
 * 当不再需要使用指针时，请使用{@link OH_Pasteboard_Destroy}销毁实例对象，否则会导致内存泄漏。
 * @see OH_Pasteboard
 * @since 13
 */
OH_Pasteboard* OH_Pasteboard_Create();

/**
 * @brief 销毁剪贴板{@link OH_Pasteboard}实例对象。适用于不再需要访问剪贴板时，销毁剪贴板对象释放资源。销毁前请确保已取消所有订阅。
 *
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @see OH_Pasteboard
 * @since 13
 */
void OH_Pasteboard_Destroy(OH_Pasteboard* pasteboard);

/**
 * @brief 订阅剪贴板的数据变更事件。典型使用场景包括：监听剪贴板内容变化、实现跨设备剪贴板同步、剪贴板内容变化时更新UI等。调用此函数后，当剪贴板数据发生变化时，
 * 系统会通过观察者的回调函数{@link Pasteboard_Notify}通知应用。可以订阅本地设备或远端设备的数据变更事件，通过type参数指定需要订阅的事件类型。
 *
 * - 调用此方法订阅剪贴板变更事件后，当不再需要监听时，必须调用{@link OH_Pasteboard_Unsubscribe}取消订阅。
 * - 取消订阅时需传入与订阅时相同的观察者对象和事件类型。
 * - 未取消订阅可能导致持续监听和资源占用。
 * - 同一观察者不能重复订阅同一类型的事件，否则会返回错误。
 * - 订阅后的观察者对象在取消订阅前不能被销毁。
 * - 回调函数在异步IPC线程中执行，需要注意线程安全。
 *
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @param type 表示订阅的剪贴板数据变更类型，详见：{@link Pasteboard_NotifyType}。
 * @param observer 表示指向剪贴板数据变更观察者{@link OH_PasteboardObserver}实例的指针。
 * 它指定了剪贴板数据变更时触发的回调函数，详见：{@link OH_PasteboardObserver}。
 * @return 返回执行的错误码。错误码定义详见{@link PASTEBOARD_ErrCode}。
 * 若返回ERR_OK，表示执行成功。
 * 若返回ERR_INVALID_PARAMETER，表示传入了无效参数。
 * @see OH_Pasteboard
 * @see OH_PasteboardObserver
 * @see Pasteboard_NotifyType
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
int OH_Pasteboard_Subscribe(OH_Pasteboard* pasteboard, int type, const OH_PasteboardObserver* observer);

/**
 * @brief 取消对剪贴板数据变更事件的订阅。调用此方法前，必须先调用OH_Pasteboard_Subscribe订阅剪贴板数据变更事件。适用于不再需要监听剪贴板数据变更时，取消订阅释放资源。
 *
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @param type 表示订阅的剪贴板数据变更类型，需与订阅时传入的类型值一致，详见：{@link Pasteboard_NotifyType}。
 * @param observer 表示指向剪贴板数据变更观察者{@link OH_PasteboardObserver}实例的指针。
 * 它指定了剪贴板数据变更时触发的回调函数，详见：{@link OH_PasteboardObserver}。
 * @return 返回执行的错误码。错误码定义详见{@link PASTEBOARD_ErrCode}。
 * 若返回ERR_OK，表示执行成功。
 * 若返回ERR_INVALID_PARAMETER，表示传入了无效参数。
 * @see OH_Pasteboard
 * @see OH_PasteboardObserver
 * @see Pasteboard_NotifyType
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
int OH_Pasteboard_Unsubscribe(OH_Pasteboard* pasteboard, int type, const OH_PasteboardObserver* observer);

/**
 * @brief 判断剪贴板中的数据是否来自远端设备。典型使用场景包括：跨设备剪贴板同步、分布式场景下根据数据来源选择处理策略、实现数据来源相关的安全校验等。
 *
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @return 返回剪贴板中的数据是否来自远端设备。返回true表示剪贴板中的数据来自远端设备，返回false表示剪贴板中数据来自本端设备。
 * @see OH_Pasteboard
 * @since 13
 */
bool OH_Pasteboard_IsRemoteData(OH_Pasteboard* pasteboard);

/**
 * @brief 获取剪贴板中数据的数据源。适用于需要识别数据来源或进行权限控制的场景。
 *
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @param source 表示用于存放剪贴板数据源实例的指针，开发者需在调用接口前申请指针指向的内存，建议申请128字节。
 * @param len 表示source指针对应的内存长度，取值需不小于数据源字符串的长度（含字符串结束符），建议长度：128字节。当内存长度不足时，返回ERR_INVALID_PARAMETER错误码。
 * @return 返回执行的错误码。错误码定义详见{@link PASTEBOARD_ErrCode}。
 * 若返回ERR_OK，表示执行成功。
 * 若返回ERR_INVALID_PARAMETER，表示传入了无效参数。
 * @see OH_Pasteboard
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
int OH_Pasteboard_GetDataSource(OH_Pasteboard* pasteboard, char* source, unsigned int len);

/**
 * @brief 判断剪贴板中是否有指定类型的数据。典型使用场景包括：粘贴前检查剪贴板数据类型是否支持、根据数据类型选择不同的处理方式、验证剪贴板数据格式等。
 *
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @param type 表示要检查的数据类型。包含剪贴板基础数据类型与自定义数据类型，其中剪贴板基础数据类型有："text/plain"、"text/html"、"text/uri"、"text/want"和"pixelMap"，
 * 详见{@link 宏定义}。
 * @return 返回剪贴板中是否有指定类型的数据。返回true表示剪贴板中包含指定类型的数据，返回false表示剪贴板中没有指定类型的数据。
 * @see OH_Pasteboard
 * @since 13
 */
bool OH_Pasteboard_HasType(OH_Pasteboard* pasteboard, const char* type);

/**
 * @brief 判断剪贴板中是否有数据。适用于在读取剪贴板数据前，判断是否有数据，避免空数据操作。
 *
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @return 返回剪贴板中是否有数据。返回true表示剪贴板中有数据，返回false表示剪贴板中没有数据。
 * @see OH_Pasteboard
 * @since 13
 */
bool OH_Pasteboard_HasData(OH_Pasteboard* pasteboard);

/**
 * @brief 判断剪贴板数据是否在远端设备上。由于数据跨设备传输耗时较大，如果剪贴板数据在远端设备上，不建议在UI线程执行检查剪贴板数据中是否包含自定义数据类型，或读取剪贴板数据。
 *
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @return 返回指示剪贴板数据是否在远端设备上的结果。true表示剪贴板数据在远端设备上；false表示剪贴板数据不在远端设备上。默认为false。
 * @see OH_Pasteboard
 * @since 24
 */
bool OH_Pasteboard_HasRemoteData(OH_Pasteboard* pasteboard);

/**
 * @brief 获取剪贴板中的数据。调用此函数后，系统会读取剪贴板中的内容，返回统一数据对象{@link OH_UdmfData}实例的指针。开发者可以通过OH_UdmfData相关接口解析数据内容。获取到的数据对象需要开发者手动释放。
 * 由于获取剪贴板中数据的时延受数据量大小与网络环境的影响，调用此接口可能耗时较长，建议开发者在非UI线程调用。
 *
 * - 如果剪贴板为空或数据格式不支持，会返回nullptr。
 * - 返回的OH_UdmfData对象需要开发者调用{@link OH_UdmfData_Destroy}释放。
 * - 粘贴的数据量大时，建议使用{@link OH_Pasteboard_GetDataWithProgress}接口以获取进度信息。
 *
 * @permission ohos.permission.READ_PASTEBOARD
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @param status 该参数是输出参数，表示执行的错误码。错误码定义详见{@link PASTEBOARD_ErrCode}。
 * @return 执行成功时返回统一数据对象{@link OH_UdmfData}实例的指针。否则返回空指针。
 * @see OH_Pasteboard
 * @see OH_UdmfData
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
OH_UdmfData* OH_Pasteboard_GetData(OH_Pasteboard* pasteboard, int* status);

/**
 * @brief 将统一数据对象数据写入剪贴板。写入成功后，其他应用可以使用系统剪贴板提供的数据读取接口访问该数据。统一数据对象的数据大小受系统剪贴板容量限制，在写入系统剪贴板后，数据的生命周期由系统剪贴板进行管理。调用此函数后，
 * 合法的数据内容会被写入系统剪贴板，覆盖之前的剪贴板数据内容。写入成功后，会触发所有订阅了剪贴板数据变更事件的观察者的回调函数。其他应用可以通过剪贴板API读取这些数据。
 *
 * - 序列化后的数据大小不能超过系统容量限制（在不同设备上的容量存在差异，通常为128MB）。
 * - 写入操作会清除之前剪贴板中的所有内容。
 * - 对于复制数据的数据量比较大的场景，建议使用延迟复制功能以提升性能。
 *
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @param data 表示指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @return 返回执行的错误码。错误码定义详见{@link PASTEBOARD_ErrCode}。
 * 若返回ERR_OK，表示执行成功。
 * 若返回ERR_INVALID_PARAMETER，表示传入了无效参数。
 * @see OH_Pasteboard
 * @see OH_UdmfData
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
int OH_Pasteboard_SetData(OH_Pasteboard* pasteboard, OH_UdmfData* data);

/**
 * @brief 清空剪贴板中的数据。适用于需要清除剪贴板中的数据时使用，如退出应用时清除敏感数据。
 *
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @return 返回执行的错误码。错误码定义详见{@link PASTEBOARD_ErrCode}。
 * 若返回ERR_OK，表示执行成功。
 * 若返回ERR_INVALID_PARAMETER，表示传入了无效参数。
 * @see OH_Pasteboard
 * @see PASTEBOARD_ErrCode
 * @since 13
 */
int OH_Pasteboard_ClearData(OH_Pasteboard* pasteboard);

/**
 * @brief 获取剪贴板中的MIME类型。典型使用场景包括：判断剪贴板数据类型以选择合适的处理方式、在粘贴前检查数据类型是否支持等。
 *
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @param count 该参数是输出参数，结果集中的类型数量会写入该变量。
 * @return 执行成功时返回剪贴板所有内容的MIME类型数组的指针，否则返回nullptr。数组大小由count参数指示。
 * @see OH_Pasteboard
 * @since 14
 */
char **OH_Pasteboard_GetMimeTypes(OH_Pasteboard *pasteboard, unsigned int *count);

/**
 * @brief 获取剪贴板内容的变化次数。典型使用场景包括：判断剪贴板内容是否已变化、实现剪贴板内容增量同步、检测剪贴板内容是否过期、基于变化计数实现缓存优化等。
 *
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @return 执行成功时返回剪贴板内容的变化次数，否则返回0。
 * @since 18
 */
uint32_t OH_Pasteboard_GetChangeCount(OH_Pasteboard *pasteboard);

/**
 * @brief 创建剪贴板{@link Pasteboard_GetDataParams}指针及实例对象。当应用需要获取剪贴板数据并监控进度（如大文件拷贝场景）时，
 * 应用按需调用{@link OH_Pasteboard_GetDataParams_SetProgressIndicator}、{@link OH_Pasteboard_GetDataParams_SetDestUri}、
 * {@link OH_Pasteboard_GetDataParams_SetFileConflictOptions}
 * 接口配置进度条指示选项、拷贝文件时目标路径、文件冲突选项。
 *
 * @return 执行成功时返回一个指向剪贴板{@link Pasteboard_GetDataParams}实例对象的指针，否则返回空指针。
 * 当不再需要使用指针时，请使用{@link OH_Pasteboard_GetDataParams_Destroy}销毁实例对象，否则会导致内存泄漏。
 * @see Pasteboard_GetDataParams
 * @since 15
 */
Pasteboard_GetDataParams *OH_Pasteboard_GetDataParams_Create(void);

/**
 * @brief 销毁剪贴板{@link Pasteboard_GetDataParams}指针指向的实例对象。调用此函数后，Pasteboard_GetDataParams对象被释放，参数配置随之失效。
 * 如果在获取粘贴数据过程中销毁参数对象，可能导致进度回调无法正常触发。适用于不再需要Pasteboard_GetDataParams对象时，销毁释放资源。
 *
 * - 此方法与{@link OH_Pasteboard_GetDataParams_Create}配对使用。
 * - 必须在{@link OH_Pasteboard_GetDataWithProgress}调用完成后销毁参数对象。
 * - 不能在进度回调函数中调用此方法销毁。
 *
 * @param params 表示指向剪贴板Pasteboard_GetDataParams的指针。
 * @see Pasteboard_GetDataParams
 * @since 15
 */
void OH_Pasteboard_GetDataParams_Destroy(Pasteboard_GetDataParams* params);

/**
 * @brief 向剪贴板{@link Pasteboard_GetDataParams}设置进度条指示选项，可选择是否采用系统默认进度显示。典型使用场景：大文件粘贴时建议使用PASTEBOARD_DEFAULT显示系统默认进度条；
 * 需要自定义进度UI或后台静默粘贴时使用PASTEBOARD_NONE。
 *
 * @param params 表示指向剪贴板Pasteboard_GetDataParams的指针。
 * @param progressIndicator 定义进度条指示选项。
 * @see Pasteboard_GetDataParams
 * @see Pasteboard_ProgressIndicator
 * @since 15
 */
void OH_Pasteboard_GetDataParams_SetProgressIndicator(Pasteboard_GetDataParams* params,
    Pasteboard_ProgressIndicator progressIndicator);

/**
 * @brief 设置拷贝文件时目标路径。若不支持文件处理，则不需要设置此参数；若应用涉及复杂文件处理策略或需要区分文件多路径存储，建议不设置此参数，由应用自行完成文件复制处理。适用于需要将剪贴板中的文件拷贝到指定目标路径时设置。
 *
 * @param params 表示指向剪贴板Pasteboard_GetDataParams的指针。
 * @param destUri 定义拷贝文件目标路径。路径需为绝对路径格式，且应用需具有该路径的读写权限。
 * @param destUriLen 定义拷贝文件目标路径的长度（含字符串结束符），单位：字节。该值必须等于 destUri所指向字符串的实际长度。传入0或与实际长度不符时，接口调用失败。
 * @see Pasteboard_GetDataParams
 * @since 15
 */
void OH_Pasteboard_GetDataParams_SetDestUri(Pasteboard_GetDataParams* params, const char* destUri, uint32_t destUriLen);

/**
 * @brief 向剪贴板{@link Pasteboard_GetDataParams}设置文件冲突选项。调用{@link OH_Pasteboard_GetDataWithProgress}时，
 * 需将已设置文件冲突选项的{@link Pasteboard_GetDataParams}作为参数传入。适用于拷贝文件时，目标路径存在同名文件，需要设置冲突处理策略。
 *
 * - PASTEBOARD_OVERWRITE：需要确保使用最新文件内容时选择覆盖。
 * - PASTEBOARD_SKIP：需要保留原有文件时选择跳过。
 *
 * @param params 表示指向剪贴板Pasteboard_GetDataParams的指针。
 * @param option 定义文件拷贝冲突时的选项，默认为PASTEBOARD_OVERWRITE。
 * @see Pasteboard_GetDataParams
 * @see Pasteboard_FileConflictOptions
 * @since 15
 */
void OH_Pasteboard_GetDataParams_SetFileConflictOptions(Pasteboard_GetDataParams* params,
    Pasteboard_FileConflictOptions option);

/**
 * @brief 向剪贴板{@link Pasteboard_GetDataParams}设置进度上报回调函数。适用于需要自定义进度显示UI或后台静默处理粘贴任务时，通过设置此回调函数来接收进度更新。
 *
 * @param params 表示指向剪贴板Pasteboard_GetDataParams的指针。
 * @param listener 表示进度上报回调函数，仅在{@link progressIndicator}设置为PASTEBOARD_NONE时生效。该参数支持传入NULL，以表示无需进度回调。
 * @see Pasteboard_GetDataParams
 * @see OH_Pasteboard_ProgressListener
 * @since 15
 */
void OH_Pasteboard_GetDataParams_SetProgressListener(Pasteboard_GetDataParams* params,
    const OH_Pasteboard_ProgressListener listener);

/**
 * @brief 从{@link Pasteboard_ProgressInfo}获取粘贴进度。典型使用场景包括：在自定义进度回调中更新UI进度条、监控大文件粘贴进度、根据进度调整业务逻辑等。
 *
 * @param progressInfo 表示指向剪贴板{@link Pasteboard_ProgressInfo}的指针。
 * @return 返回粘贴进度百分比，取值范围[0, 100]。
 * @see Pasteboard_ProgressInfo
 * @since 15
 */
int OH_Pasteboard_ProgressInfo_GetProgress(Pasteboard_ProgressInfo* progressInfo);

/**
 * @brief 取消正在进行的粘贴操作。该函数用于中断{@link OH_Pasteboard_GetDataWithProgress}执行过程中的数据传输。调用后，当前粘贴操作将被终止，已传输的部分数据可能保留或清理，
 * 取决于具体操作状态。取消后如需再次获取剪贴板数据，需重新调用{@link OH_Pasteboard_GetDataWithProgress}。适用于用户主动取消、错误中断传输，或限制粘贴超时等情形。
 *
 * - 取消操作是异步的，可能不会立即生效。
 * - 取消操作不可逆，一旦取消，如需要获取剪贴板数据，需要重新开始粘贴流程。
 *
 * @param params 表示指向剪贴板Pasteboard_GetDataParams的指针。
 * @see Pasteboard_GetDataParams
 * @since 15
 */
void OH_Pasteboard_ProgressCancel(Pasteboard_GetDataParams* params);

/**
 * @brief 获取剪贴板的数据以及粘贴进度，不支持对文件夹的拷贝。调用此函数后，系统开始从系统剪贴板获取数据。如果剪贴板数据来自远端设备或包含大量文件，会通过{@link OH_Pasteboard_ProgressListener}
 * 回调函数上报进度。数据传输完成后，返回统一数据对象指针。整个过程可能耗时较长，建议在非UI线程调用。
 *
 * @permission ohos.permission.READ_PASTEBOARD
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @param params 表示指向剪贴板Pasteboard_GetDataParams的指针。
 * @param status 该参数是输出参数，表示执行的错误码。错误码定义详见{@link PASTEBOARD_ErrCode}。
 * @return 执行成功时返回统一数据对象OH_UdmfData实例的指针。否则返回空指针。
 * @see OH_Pasteboard
 * @see OH_UdmfData
 * @see PASTEBOARD_ErrCode
 * @since 15
 */
OH_UdmfData* OH_Pasteboard_GetDataWithProgress(OH_Pasteboard* pasteboard, Pasteboard_GetDataParams* params,
    int* status);

/**
 * @brief 通知剪贴板从应用同步所有延迟数据（延迟数据指在延迟复制模式下，先写入数据类型到剪贴板，实际数据内容按需延迟加载的数据传输机制），与延迟复制接口{@link OH_UdmfRecordProvider_SetData}
 * 搭配使用。当所有延迟数据同步完成时，使用callback异步通知应用。当应用使用延迟复制功能复制时，仅将应用支持的数据类型写入剪贴板。应用应在退出时，重新调用{@link OH_Pasteboard_SetData}
 * 接口主动提交所有复制数据或调用此接口通知剪贴板获取全量数据，等待数据同步完成再继续退出，否则可能导致其他应用粘贴获取不到数据。
 *
 * > **注意：**
 * > - 调用此接口会延长退出过程，建议应用直接设置数据到剪贴板，而不是调用延迟复制接口{@link OH_UdmfRecordProvider_SetData}和此接口。
 *
 * @param pasteboard 表示指向剪贴板{@link OH_Pasteboard}实例的指针。
 * @param callback 数据同步完成后调用的回调函数指针，errorCode表示同步任务的结果，错误码定义详见{@link PASTEBOARD_ErrCode}。
 * @since 21
 */
void OH_Pasteboard_SyncDelayedDataAsync(OH_Pasteboard* pasteboard, void (*callback)(int errorCode));

#ifdef __cplusplus
};
#endif

/** @} */
#endif
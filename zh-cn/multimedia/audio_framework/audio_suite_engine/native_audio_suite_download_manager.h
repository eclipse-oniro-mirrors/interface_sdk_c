/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup AudioSuite
 * @{
 *
 * @brief Provide the definition of the C interface for the audio download manager module.
 *
 * @since 26.0.0
 */
/**
 * @file native_audio_suite_download_manager.h
 * @brief Declare audio download manager related interfaces.
 * @syscap SystemCapability.Multimedia.Audio.SuiteEngine
 * @library libohaudiosuite.so
 * @kit AudioKit
 * @since 26.0.0
 */
#ifndef NATIVE_AUDIO_SUITE_DOWNLOAD_MANAGER_H
#define NATIVE_AUDIO_SUITE_DOWNLOAD_MANAGER_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义下载状态信息结构体。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_AudioSuite_DownloadStatusInfo {
    /**
     * @brief 特性名称。
     *
     * @since 26.0.0
     */
    char featureName[256];
    /**
     * @brief 下载状态。
     *
     * @since 26.0.0
     */
    int32_t downloadStatus;
    /**
     * @brief 特性包大小。
     *
     * @since 26.0.0
     */
    int64_t size;
    /**
     * @brief 安装路径。
     *
     * @since 26.0.0
     */
    char installPath[256];
    /**
     * @brief 下载进度【0-100】。
     *
     * @since 26.0.0
     */
    int32_t progress;
    /**
     * @brief 错误码。
     *
     * @since 26.0.0
     */
    int32_t errorCode;
} OH_AudioSuite_DownloadStatusInfo;

/**
 * @brief 定义下载状态信息数组结构体。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_AudioSuite_DownloadStatusInfoArray {
    /**
     * @brief 数组大小。
     *
     * @since 26.0.0
     */
    uint32_t size;
    /**
     * @brief 下载状态信息指针数组。
     *
     * @since 26.0.0
     */
    OH_AudioSuite_DownloadStatusInfo **downloadStatusInfo;
} OH_AudioSuite_DownloadStatusInfoArray;

/**
 * @brief 声明音频下载管理器。
 * 音频下载管理器的句柄用于下载相关功能。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_AudioSuite_DownloadManagerStruct OH_AudioSuite_DownloadManager;

/**
 * @brief 更新下载状态的回调函数。
 * @systemapi
 * @param downloadStatusInfoArray 下载状态信息数组指针。
 * @since 26.0.0
 */
typedef void (*OH_AudioSuite_DownloadCallback)(OH_AudioSuite_DownloadStatusInfoArray *downloadStatusInfoArray);

/**
 * @brief 获取音频下载管理器句柄。
 * @systemapi
 * @param downloadManager 接收下载管理器句柄的指针。
 * @return <ul>
 * <li>{@link AUDIOCOMMON_RESULT_SUCCESS}如果执行成功</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}如果downloadManager为nullptr。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuite_GetDownloadManager(OH_AudioSuite_DownloadManager **downloadManager);

/**
 * @brief 注册下载状态回调。
 * @systemapi
 * @param downloadManager 下载管理器句柄。
 * @param callback 接收下载状态更新的回调函数。
 * @return <ul>
 * <li>{@link AUDIOCOMMON_RESULT_SUCCESS}如果执行成功</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}如果下载管理器或回调为nullptr，则返回错误。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM}如果IPC通信失败或操作失败。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuite_RegisterDownloadCallback(
    OH_AudioSuite_DownloadManager *downloadManager, const OH_AudioSuite_DownloadCallback *callback);

/**
 * @brief 注销下载状态回调。
 * @systemapi
 * @param downloadManager 下载管理器句柄。
 * @param callback 注销的回调函数。
 * @return <ul>
 * <li>{@link AUDIOCOMMON_RESULT_SUCCESS}如果执行成功</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}如果下载管理器或回调为nullptr，则返回错误。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM}如果IPC通信失败或操作失败。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuite_UnregisterDownloadCallback(
    OH_AudioSuite_DownloadManager *downloadManager, const OH_AudioSuite_DownloadCallback *callback);

/**
 * @brief 开始下载特性。
 * @systemapi
 * @param downloadManager 下载管理器句柄。
 * @param featureName 要下载的特性的名称。
 * @return <ul>
 * <li>{@link AUDIOCOMMON_RESULT_SUCCESS}如果执行成功</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}如果downloadManager或featureName为nullptr。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM}如果IPC通信失败或操作失败。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuite_StartDownload(
    OH_AudioSuite_DownloadManager *downloadManager, const char *featureName);

/**
 * @brief 取消下载特性。
 * @systemapi
 * @param downloadManager 下载管理器句柄。
 * @param featureName 要取消的特性名称。
 * @return <ul>
 * <li>{@link AUDIOCOMMON_RESULT_SUCCESS}如果执行成功</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}如果downloadManager或featureName为nullptr。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM}如果IPC通信失败或操作失败。</li>
 * <li>{@link AVPCOMMON_RESULT_ERROR_LINAL_STATE}如果当前状态不允许取消。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuite_CancelDownload(
    OH_AudioSuite_DownloadManager *downloadManager, const char *featureName);

/**
 * @brief 开始后台下载功能。
 * @systemapi
 * @param downloadManager 下载管理器句柄。
 * @param featureName 要下载的特性的名称。
 * @return <ul>
 * <li>{@link AUDIOCOMMON_RESULT_SUCCESS}如果执行成功</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}如果downloadManager或featureName为nullptr。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM}如果IPC通信失败或操作失败。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuite_StartBackgroundDownload(
    OH_AudioSuite_DownloadManager *downloadManager, const char *featureName);

/**
 * @brief 获取功能的下载状态。
 * @systemapi
 * @param downloadManager 下载管理器句柄。
 * @param featureName 特性的名称。
 * @param status 接收下载状态信息的指针。
 * @return <ul>
 * <li>{@link AUDIOCOMMON_RESULT_SUCCESS}如果执行成功</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}如果downloadManager、featureName或status为nullptr。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM}如果IPC通信失败或操作失败。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuite_GetDownloadStatus(
    OH_AudioSuite_DownloadManager *downloadManager, const char *featureName,
    OH_AudioSuite_DownloadStatusInfo *status);

/**
 * @brief 卸载已下载的特性。
 * @systemapi
 * @param downloadManager 下载管理器句柄。
 * @param featureName 要卸载的特性名称。
 * @return <ul>
 * <li>{@link AUDIOCOMMON_RESULT_SUCCESS}如果执行成功</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}如果downloadManager或featureName为nullptr。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM}如果IPC通信失败或操作失败。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuite_UninstallCloudRom(
    OH_AudioSuite_DownloadManager *downloadManager, const char *featureName);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_AUDIO_SUITE_DOWNLOAD_MANAGER_H
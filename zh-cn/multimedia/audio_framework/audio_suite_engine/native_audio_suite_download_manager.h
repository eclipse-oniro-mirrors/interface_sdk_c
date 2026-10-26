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
 * @addtogroup OHAudioSuite
 * @{
 *
 * @brief 提供音频编创相关C接口定义，包含多种专业级音频效果处理功能，服务于音频编辑和创作类应用场景。
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
#include <stdbool.h>
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
     * @brief 下载进度[0-100]。
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
 * @brief 定义特性版本信息结构体。
 * @systemapi
 * @since 26.0.1
 */
typedef struct OH_AudioSuite_FeatureVersionInfo {
    /**
     * @brief 特性名称。
     *
     * @since 26.0.1
     */
    char featureName[256];
    /**
     * @brief 特性当前状态。
     *
     * @since 26.0.1
     */
    int32_t downloadStatus;
    /**
     * @brief 特性版本。
     *
     * @since 26.0.1
     */
    char version[128];
    /**
     * @brief 特性模块占用空间大小。单位为：字节。
     *
     * @since 26.0.1
     */
    int64_t size;
    /**
     * @brief 错误码。
     *
     * @since 26.0.1
     */
    int32_t errorCode;
} OH_AudioSuite_FeatureVersionInfo;

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
 * @brief 暂停下载特性二进制文件。
 * @systemapi
 * @param downloadManager 下载管理器句柄。
 * @param featureName 要暂停的功能的名称。
 * @return <ul>
 * <li>{@link AUDIOCOMMON_RESULT_SUCCESS}如果执行成功</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM如果downloadManager或featureName为nullptr。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM}如果IPC通信失败或操作失败。</li>
 * </ul>
 * @since 26.0.0
 */
int32_t OH_AudioSuite_PauseDownload(
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

/**
 * @brief 批量获取特性的安装状态。
 * 接口返回成功，installStatus有效数量为count。失败则installStatus有效数量为0。
 * @systemapi
 * @param downloadManager [入参] 下载管理器句柄。
 * @param featureNames [入参] 特性名称的数组。
 * @param count [入参] featureNames数组中特性名称的个数，取值为[1, 5]。
 * @param installStatus [出参] 调用者分配的接收安装状态的布尔数组。元素值为true，表示featureNames对应索引的特性已安装。为false，表示未安装。
 * @param installStatusSize [入参] 调用者分配的installStatus输出数组的容量。必须大于等于count。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 执行成功。</li>
 *         <li>202 权限验证失败。非系统应用调用系统API。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数为空指针或无效值。可能的原因如下：
 *         <ol><li>参数downloadManager为空指针。</li>
 *         <li>参数featureNames为空指针。</li>
 *         <li>参数featureNames中的值为空指针。</li>
 *         <li>参数installStatus为空指针。</li>
 *         <li>参数count为0或者大于5。</li>
 *         <li>参数installStatusSize小于count。</li></ol>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SERVICE_DIED} IPC通信失败。</li>
 *         </ul>
 * @since 26.0.1
 */
int32_t OH_AudioSuite_IsFeatureInstalled(OH_AudioSuite_DownloadManager *downloadManager,
    const char **featureNames, uint32_t count,
    bool *installStatus, uint32_t installStatusSize);

/**
 * @brief 批量获取特性的当前状态。
 * 接口返回成功，statusInfos有效数量为count。失败则statusInfos有效数量为0。
 * @systemapi
 * @param downloadManager [入参] 下载管理器句柄。
 * @param featureNames [入参] 特性名称的数组。
 * @param count [入参] featureNames数组中特性名称的个数，取值为[1, 5]。
 * @param statusInfos [出参] 调用者分配的接收特性状态的数组。
 * @param statusInfosSize [入参] 调用者分配的statusInfos输出数组的容量。必须大于等于count。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 执行成功。</li>
 *         <li>202 权限验证失败。非系统应用调用系统API。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数为空指针或无效值。可能的原因如下：
 *         <ol><li>参数downloadManager为空指针。</li>
 *         <li>参数featureNames为空指针。</li>
 *         <li>参数featureNames中的值为空指针。</li>
 *         <li>参数statusInfos为空指针。</li>
 *         <li>参数count为0或者大于5。</li>
 *         <li>参数statusInfosSize小于count。</li></ol>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SERVICE_DIED} IPC通信失败。</li>
 *         </ul>
 * @since 26.0.1
 */
int32_t OH_AudioSuite_GetFeatureStatus(
    OH_AudioSuite_DownloadManager *downloadManager,
    const char **featureNames, uint32_t count,
    OH_AudioSuite_DownloadStatusInfo *statusInfos, uint32_t statusInfosSize);

/**
 * @brief 批量获取特性的新版本信息。
 * 接口返回成功，versionInfos有效数量为count。失败则versionInfos有效数量为0。
 * @systemapi
 * @param downloadManager [入参] 下载管理器句柄。
 * @param featureNames [入参] 特性名称的数组。
 * @param count [入参] featureNames数组中特性名称的个数，取值为[1, 5]。
 * @param versionInfos [出参] 调用者分配的接收版本信息的数组。
 * @param versionInfosSize [入参] 调用者分配的输出数组的容量。必须大于等于count。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 执行成功。</li>
 *         <li>202 权限验证失败。非系统应用调用系统API。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数为空指针或无效值。可能的原因如下：
 *         <ol><li>参数downloadManager为空指针。</li>
 *         <li>参数featureNames为空指针。</li>
 *         <li>参数featureNames中的值为空指针。</li>
 *         <li>参数versionInfos为空指针。</li>
 *         <li>参数count为0或者大于5。</li>
 *         <li>参数versionInfosSize小于count。</li></ol>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SERVICE_DIED} IPC通信失败。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_NETWORK_CONDITION_NOT_MET} 当前网络状态不可用。</li>
 *         </ul>
 * @since 26.0.1
 */
int32_t OH_AudioSuite_GetNewVersionInfo(
    OH_AudioSuite_DownloadManager *downloadManager,
    const char **featureNames, uint32_t count,
    OH_AudioSuite_FeatureVersionInfo *versionInfos, uint32_t versionInfosSize);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_AUDIO_SUITE_DOWNLOAD_MANAGER_H
/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
 * @addtogroup AbilityRuntime
 * @{
 *
 * @brief 提供应用级别上下文相关的接口。
 *
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 13
 */

/**
 * @file application_context.h
 *
 * @brief 提供应用级别上下文相关的接口。
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 13
 */

#ifndef ABILITY_RUNTIME_APPLICATION_CONTEXT_H
#define ABILITY_RUNTIME_APPLICATION_CONTEXT_H

#include <stdint.h>
#include <stddef.h>
#include <AbilityKit/ability_base/want.h>
#include "ability_runtime_common.h"
#include "context_constant.h"
#include "start_options.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取本应用的应用级的缓存目录。
 *
 * @param buffer 指向缓冲区的指针，用于接收本应用的应用级的缓存目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或者writeLength为空，或者缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 13
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetCacheDir(
    char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取本应用的应用级的文件数据加密等级。
 *
 * @param areaMode 指向接收数据加密等级的指针。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - areaMode为null。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 13
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetAreaMode(AbilityRuntime_AreaMode* areaMode);

/**
 * @brief 获取应用包名。
 *
 * @param buffer 指向缓冲区的指针，用于接收应用包名。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或者writeLength为空，或者缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 13
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetBundleName(
    char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取本应用的应用级的临时文件目录。该目录用于存储应用运行期间的临时文件，这些文件在应用退出或系统清理时可能被删除。
 *
 * @param buffer 指向缓冲区的指针，用于接收临时文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或者writeLength为空，或者缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetTempDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取本应用的应用级的通用文件目录。该目录用于存储应用需要持久化的文件，如用户生成的文档、下载的文件、应用数据等。
 *
 * @param buffer 指向缓冲区的指针，用于接收通用文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或者writeLength为空，或者缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetFilesDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取本应用的应用级的数据库文件目录。
 *
 * @param buffer 指向缓冲区的指针，用于接收数据库文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或者writeLength为空，或者缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetDatabaseDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取本应用的应用级的首选项文件目录。
 *
 * @param buffer 指向缓冲区的指针，用于接收首选项文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或者writeLength为空，或者缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetPreferencesDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取本应用的应用级的安装文件目录。
 *
 * @param buffer 指向缓冲区的指针，用于接收安装文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或者writeLength为空，或者缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetBundleCodeDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取本应用的应用级的分布式文件目录。
 *
 * @param buffer 指向缓冲区的指针，用于接收分布式文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或者writeLength为空，或者缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetDistributedFilesDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取本应用的应用级的云文件目录。
 *
 * @param buffer 指向缓冲区的指针，用于接收云文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或者writeLength为空，或者缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetCloudFileDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取本应用的应用级的资源目录。
 *
 * @param moduleName 模块名，用于指定要获取资源目录的目标模块。开发者可通过bundleManager模块的接口获取应用包含的模块名列表，不同模块名对应不同的资源目录路径。
 * @param buffer 指向缓冲区的指针，用于接收资源目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或者writeLength为空，或者缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 20
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetResourceDir(const char* moduleName,
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 启动当前应用的UIAbility。
 *
 * @permission ohos.permission.NDK_START_SELF_UI_ABILITY
 * @param want 启动当前应用UIAbility时需要的Want信息。
 * @return ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 接口调用成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PERMISSION_DENIED - 调用方权限校验失败。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 调用方入参校验失败。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED - 设备类型不支持。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_SUCH_ABILITY - 指定的Ability名称不存在。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_INCORRECT_ABILITY_TYPE - 接口调用Ability类型错误。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CROWDTEST_EXPIRED - 众测应用到期。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_WUKONG_MODE - Wukong模式，不允许启动/停止Ability。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTROLLED - 应用被管控。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_EDM_CONTROLLED - 应用被EDM管控。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CROSS_APP - 限制API 11以上版本三方应用跳转。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_INTERNAL - 内部错误。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NOT_TOP_ABILITY - 非顶层应用。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_UPPER_LIMIT_REACHED - 应用多实例已达到上限（从API17开始）。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_APP_INSTANCE_KEY_NOT_SUPPORTED - 不允许设置APP_INSTANCE_KEY（从API17开始）。
 *     <br>详细内容参考AbilityRuntime_ErrorCode。
 * @since 15
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_StartSelfUIAbility(AbilityBase_Want *want);

/**
 * @brief 获取本应用首次启动UIAbility时的WantParams参数，WantParams可参考Want中的parameters参数。
 *
 * @param buffer 指向缓冲区的指针，用于接收WantParams参数。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入缓冲区的字符串长度（单位：字节）。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或者writeLength为空，或者缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 21
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetLaunchParameter(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取本应用最近一次启动UIAbility时的WantParams参数，WantParams可参考Want中的parameters参数。适用于需要获取最近一次启动时传递的参数，用于处理最新的启动请求、
 * 页面跳转参数解析等场景。
 *
 * @param buffer 指向缓冲区的指针，用于接收WantParams参数。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入缓冲区的字符串长度（单位：字节）。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或者writeLength为空，或者缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 21
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetLatestParameter(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 通过StartOptions启动当前应用的UIAbility。
 *
 * @permission ohos.permission.NDK_START_SELF_UI_ABILITY
 * @param want 启动当前应用UIAbility时需要的Want信息。
 * @param options 启动当前应用UIAbility时需要的StartOptions信息。如果该参数中{@link startVisibility}属性的值不为空，必须确保当前应用已添加到状态栏，否则会返回
 *     {@link ABILITY_RUNTIME_ERROR_VISIBILITY_SETTING_DISABLED}错误码。
 * @return ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 接口调用成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PERMISSION_DENIED - 调用方权限校验失败。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 调用方入参校验失败。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED - 设备类型不支持。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_SUCH_ABILITY - 指定的Ability名称不存在。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_INCORRECT_ABILITY_TYPE - 接口调用Ability类型错误。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CROWDTEST_EXPIRED - 众测应用到期。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_WUKONG_MODE - Wukong模式，不允许启动/停止Ability。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTROLLED - 应用被管控。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_EDM_CONTROLLED - 应用被EDM管控。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CROSS_APP - 限制API 11以上版本三方应用跳转。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_INTERNAL - 内部错误。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NOT_TOP_ABILITY - 非顶层应用。
 *     <br>ABILITY_RUNTIME_ERROR_VISIBILITY_SETTING_DISABLED - 不允许设置窗口启动可见性。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_MULTI_APP_NOT_SUPPORTED - 不支持应用分身和多实例。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_INVALID_APP_INSTANCE_KEY - 无效多实例。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_UPPER_LIMIT_REACHED - 应用多实例已达到上限。
 *     <br>ABILITY_RUNTIME_ERROR_MULTI_INSTANCE_NOT_SUPPORTED - 不支持应用多实例。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_APP_INSTANCE_KEY_NOT_SUPPORTED - 不允许设置APP_INSTANCE_KEY。
 *     <br>详细内容参考AbilityRuntime_ErrorCode。
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_StartSelfUIAbilityWithStartOptions(AbilityBase_Want *want,
    AbilityRuntime_StartOptions *options);

    /**
 * @brief 获取应用版本号。
 *
 * @param versionCode The version code of the application.
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参versionCode为空。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_GET_APPLICATION_INFO_FAILED  - 获取应用信息失败，如应用未安装或应用信息损坏。
 * @since 21
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetVersionCode(int64_t* versionCode);

/**
 * @brief 通过StartOptions启动当前应用的UIAbility，并获取目标UIAbility的进程号。
 * <br>接口不能在应用主线程调用，但可以在应用创建的{@link ChildProcess}的主线程中调用。
 * <br>如果在应用的主线程中调用，会返回ABILITY_RUNTIME_ERROR_CODE_MAIN_THREAD_NOT_SUPPORTED错误码。
 *
 * @permission ohos.permission.NDK_START_SELF_UI_ABILITY
 * @param want 启动当前应用UIAbility时需要的Want信息。
 * @param options 启动当前应用UIAbility时需要的StartOptions信息。如果该参数中{@link startVisibility}属性的值不为空，必须确保当前应用已添加到状态栏，否则会返回
 *     {@link ABILITY_RUNTIME_ERROR_VISIBILITY_SETTING_DISABLED}错误码。
 * @param targetPid 目标UIAbility所在的进程号，作为出参使用。
 * @return ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 接口调用成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PERMISSION_DENIED - 调用方权限校验失败。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 调用方入参校验失败。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED - 设备类型不支持。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_SUCH_ABILITY - 指定的Ability名称不存在。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_INCORRECT_ABILITY_TYPE - 接口调用Ability类型错误。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CROWDTEST_EXPIRED - 众测应用到期。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_WUKONG_MODE - Wukong模式，不允许启动/停止Ability。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTROLLED - 应用被管控。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_EDM_CONTROLLED - 应用被EDM管控。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CROSS_APP - 限制API 11以上版本三方应用跳转。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_INTERNAL - 内部错误。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NOT_TOP_ABILITY - 非顶层应用。
 *     <br>ABILITY_RUNTIME_ERROR_VISIBILITY_SETTING_DISABLED - 不允许设置窗口启动可见性。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_MULTI_APP_NOT_SUPPORTED - 不支持应用分身和多实例。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_INVALID_APP_INSTANCE_KEY - 无效多实例。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_UPPER_LIMIT_REACHED - 应用多实例已达到上限。
 *     <br>ABILITY_RUNTIME_ERROR_MULTI_INSTANCE_NOT_SUPPORTED - 不支持应用多实例。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_APP_INSTANCE_KEY_NOT_SUPPORTED - 不允许设置APP_INSTANCE_KEY。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_START_TIMEOUT - 启动UIAbility超时。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_MAIN_THREAD_NOT_SUPPORTED - 接口不允许在应用主线程被调用。
 * @since 21
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_StartSelfUIAbilityWithPidResult(AbilityBase_Want *want,
    AbilityRuntime_StartOptions *options, int32_t *targetPid);

/**
 * @brief 获取本应用的应用级的日志文件目录。
 *
 * @param buffer 指向缓冲区的指针，用于接收日志文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 查询成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或者writeLength为空，或者缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 应用上下文不存在，如在应用创建的{@link ChildProcess}中应用级别上下文不存在。
 * @since 22
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetLogFileDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 该接口仅支持三方框架调用。三方框架每次切换页面时，将目标页面信息（包含目标页面路径、目标页面路径长度、目标页面对应的窗口ID）通知给系统。系统可按产品策略调整/恢复页面。适用于三方框架页面导航追踪、页面状态同步、
 * 系统级页面优化等场景。
 *
 * @param targetPageName 目标页面路径。
 * @param targetPageNameLength 目标页面路径长度。
 * @param windowId 目标页面对应的{@link WindowInfo}中的窗口ID。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参targetPageName为空或者windowId无效。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_INTERNAL - 内部错误。
 * @since 23
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextNotifyPageChanged(
    const char* targetPageName, int32_t targetPageNameLength, int32_t windowId);

#ifdef __cplusplus
} // extern "C"
#endif

/** @} */
#endif // ABILITY_RUNTIME_APPLICATION_CONTEXT_H
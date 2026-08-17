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
 * @addtogroup AbilityRuntime
 * @{
 *
 * @brief 提供AbilityRuntime上下文的C接口定义。
 *
 * @since 24
 */

/**
 * @file context.h
 *
 * @brief 提供上下文数据结构AbilityRuntime_Context和相关接口用于获取当前上下文的应用文件路径、数据加密等级和进程名等信息。
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 24
 */

#ifndef ABILITY_RUNTIME_CONTEXT_H
#define ABILITY_RUNTIME_CONTEXT_H

#include <stdint.h>
#include "ability_runtime_common.h"
#include "context_constant.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义AbilityRuntime_Context结构体类型。
 *
 * @since 24
 */
struct AbilityRuntime_Context;

/**
 * @brief 定义AbilityRuntime_Context对象指针。
 *
 * @since 24
 */
typedef struct AbilityRuntime_Context* AbilityRuntime_ContextHandle;

/**
 * @brief 获取上下文的缓存目录。
 *
 * @param context 要获取缓存目录的上下文。
 * @param buffer 指向缓冲区的指针，用于接收上下文的缓存目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength   在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或writeLength为空或context为空，或缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 上下文不存在。
 * @since 24
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_Context_GetCacheDir(
    AbilityRuntime_ContextHandle context, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取上下文的临时文件目录。
 *
 * @param context 要获取临时文件目录的上下文。
 * @param buffer 指向缓冲区的指针，用于接收上下文的临时文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或writeLength为空或context为空，或缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 上下文不存在。The error code.
 * @since 24
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_Context_GetTempDir(
    AbilityRuntime_ContextHandle context, char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取上下文的通用文件目录。
 *
 * @param context 要获取通用文件目录的上下文。
 * @param buffer 指向缓冲区的指针，用于接收上下文的通用文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或writeLength为空或context为空，或缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 上下文不存在。
 * @since 24
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_Context_GetFilesDir(
    AbilityRuntime_ContextHandle context, char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取上下文的数据库文件目录。
 *
 * @param context 要获取数据库文件目录的上下文。
 * @param buffer 指向缓冲区的指针，用于接收上下文的数据库文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或writeLength为空或context为空，或缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 上下文不存在。
 * @since 24
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_Context_GetDatabaseDir(
    AbilityRuntime_ContextHandle context, char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取上下文的首选项文件目录。
 *
 * @param context 要获取首选项文件目录的上下文。
 * @param buffer 指向缓冲区的指针，用于接收上下文的首选项文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或writeLength为空或context为空，或缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 上下文不存在。
 * @since 24
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_Context_GetPreferencesDir(
    AbilityRuntime_ContextHandle context, char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取上下文的安装文件目录。
 *
 * @param context 要获取安装文件目录的上下文。
 * @param buffer 指向缓冲区的指针，用于接收上下文的安装文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength   在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或writeLength为空或context为空，或缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 上下文不存在。
 * @since 24
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_Context_GetBundleCodeDir(
    AbilityRuntime_ContextHandle context, char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取上下文的分布式文件目录。
 *
 * @param context 要获取分布式文件目录的上下文。
 * @param buffer 指向缓冲区的指针，用于接收上下文的分布式文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或writeLength为空或context为空，或缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 上下文不存在。
 * @since 24
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_Context_GetDistributedFilesDir(
    AbilityRuntime_ContextHandle context, char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取上下文的资源目录。
 *
 * @param context 要获取资源目录的上下文。
 * @param buffer 指向缓冲区的指针，用于接收上下文的资源目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或writeLength为空或context为空，或缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 上下文不存在。
 * @since 24
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_Context_GetResourceDir(AbilityRuntime_ContextHandle context,
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取上下文的云文件目录。
 *
 * @param context 要获取云文件目录的上下文。
 * @param buffer 指向缓冲区的指针，用于接收上下文的云文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或writeLength为空或context为空，或缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 上下文不存在。
 * @since 24
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_Context_GetCloudFileDir(
    AbilityRuntime_ContextHandle context, char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取上下文的数据加密等级。
 *
 * @param context 要获取数据加密等级的上下文。
 * @param areaMode 指向接收数据加密等级的指针。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参areaMode为空。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 上下文不存在。
 * @since 24
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_Context_GetAreaMode(
    AbilityRuntime_ContextHandle context, AbilityRuntime_AreaMode* areaMode);

/**
 * @brief 设置上下文的数据加密等级。
 *
 * @param context 要设置数据加密等级的上下文。
 * @param areaMode 数据加密等级。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参context为空。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 上下文不存在。
 * @since 24
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_Context_SetAreaMode(
    AbilityRuntime_ContextHandle context, AbilityRuntime_AreaMode areaMode);

/**
 * @brief 获取上下文的日志文件目录。
 *
 * @param context 要获取日志文件目录的上下文。
 * @param buffer 指向缓冲区的指针，用于接收上下文的日志文件目录。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 	返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或writeLength为空或context为空，或缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 上下文不存在。
 * @since 24
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_Context_GetLogFileDir(
    AbilityRuntime_ContextHandle context, char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取上下文所在的进程名称。
 *
 * @param context 要获取进程名称的上下文。
 * @param buffer 指向缓冲区的指针，用于接收进程名称。
 * @param bufferSize 缓冲区大小，单位为字节。
 * @param writeLength 在返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}时，表示实际写入到缓冲区的字符串长度，单位为字节。
 * @return 返回执行结果。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_NO_ERROR - 操作成功。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID - 入参buffer或writeLength为空或context为空，或缓冲区大小小于需要写入的大小。
 *     <br>ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST - 上下文不存在。
 * @since 24
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_Context_GetProcessName(
    AbilityRuntime_ContextHandle context, char* buffer, int32_t bufferSize, int32_t* writeLength);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // ABILITY_RUNTIME_CONTEXT_H
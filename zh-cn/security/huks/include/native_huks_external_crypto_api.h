
/*
 * Copyright (c) 2022-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup HuksExternalCryptoApi
 * @{
 *
 * @brief Describes the OpenHarmony Universal KeyStore (HUKS) capabilities specifical for external crypto extensions,
 * including provider management and ukey pin management and other operations, provided for applications.
 *
 * @since 22
 */

/**
 * @file native_huks_external_crypto_api.h
 *
 * @brief 定义面向外部密钥管理扩展的通用密钥库（HUKS）API。
 *
 * @library libhuks_external_crypto.z.so
 * @syscap SystemCapability.Security.Huks.CryptoExtension
 *
 *     include "huks/include/native_huks_external_crypto_type.h"
 * @kit UniversalKeystoreKit
 * @since 22
 */

#ifndef NATIVE_HUKS_EXTERNAL_CRYPTO_API_H
#define NATIVE_HUKS_EXTERNAL_CRYPTO_API_H

#include "native_huks_external_crypto_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 注册外部密钥管理能力扩展提供者。
 *
 * @permission ohos.permission.CRYPTO_EXTENSION_REGISTER
 * @param providerName 指定提供者名称。
 * @param paramSet 指向注册参数的指针。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS 0 - 操作成功。
 *     <br>OH_HUKS_ERR_CODE_PERMISSION_FAIL 201 - 权限校验失败，请先申请所需权限。
 *     <br>OH_HUKS_ERR_CODE_NOT_SUPPORTED_API 801 - 不支持的API。
 *     <br>OH_HUKS_ERR_CODE_MISSING_CRYPTO_ALG_ARGUMENT 12000002 - 未能获取提供者参数。
 *     <br>OH_HUKS_ERR_CODE_COMMUNICATION_FAIL 12000005 - IPC通信失败。
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014 - 内存不足。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT 12000018 - providerName或paramSet无效。
 *     <br>OH_HUKS_ERR_CODE_ITEM_NOT_EXIST 12000019 - 提供者已被注册。
 *     <br>OH_HUKS_ERR_CODE_EXTERNAL_ERROR 12000020 - 依赖模块发生错误。
 *     <br>OH_HUKS_ERR_CODE_EXCEED_LIMIT 12000025 - 提供者数量超过限制。
 * @since 22
 */
struct OH_Huks_Result OH_Huks_RegisterProvider(
    const struct OH_Huks_Blob *providerName, const OH_Huks_ExternalCryptoParamSet *paramSet);

/**
 * @brief 注销外部密钥管理能力扩展提供者。
 *
 * @permission ohos.permission.CRYPTO_EXTENSION_REGISTER
 * @param providerName 指定提供者名称。
 * @param paramSet 指向注册参数的指针。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS 0 - 操作成功。
 *     <br>OH_HUKS_ERR_CODE_PERMISSION_FAIL 201 - 权限校验失败，请先申请所需权限。
 *     <br>OH_HUKS_ERR_CODE_NOT_SUPPORTED_API 801 - 不支持的API。
 *     <br>OH_HUKS_ERR_CODE_COMMUNICATION_FAIL 12000005 - IPC通信失败。
 *     <br>OH_HUKS_ERR_CODE_ITEM_NOT_EXIST 12000011 - 未找到指定的提供者。
 *     <br>OH_HUKS_ERR_CODE_INTERNAL_ERROR = 12000012 - 发生系统内部错误，密钥管理扩展模块没有加载。
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014 - 内存不足。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT 12000018 - providerName无效。
 * @since 22
 */
struct OH_Huks_Result OH_Huks_UnregisterProvider(
    const struct OH_Huks_Blob *providerName, const OH_Huks_ExternalCryptoParamSet *paramSet);

/**
 * @brief 根据指定的资源ID打开资源。
 * <br>注意：打开的资源必须通过{@link OH_Huks_CloseResource}关闭。
 *
 * @param resourceId 指定提供者的资源ID。
 * @param paramSet 指向句柄操作参数的指针。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS 0 - 操作成功。
 *     <br>OH_HUKS_ERR_CODE_NOT_SUPPORTED_API 801 - 不支持的API。
 *     <br>OH_HUKS_ERR_CODE_COMMUNICATION_FAIL 12000005 - IPC通信失败。
 *     <br>OH_HUKS_ERR_CODE_CRYPTO_FAIL 12000006 - Ukey驱动报错。
 *     <br>OH_HUKS_ERR_CODE_ITEM_NOT_EXIST 12000011 - 未找到缓存的资源句柄，需要先根据资源ID打开资源。
 *     <br>OH_HUKS_ERR_CODE_INTERNAL_ERROR 12000012 - 发生系统内部错误，处理函数未找到。
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014 - 内存不足。
 *     <br>OH_HUKS_ERR_CODE_KEY_ALREADY_EXIST 12000017 - 资源已打开。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT 12000018 - resourceId或paramSet无效。
 *     <br>OH_HUKS_ERR_CODE_EXTERNAL_ERROR 12000020 - 提供者执行失败。
 *     <br>OH_HUKS_ERR_CODE_BUSY 12000024 - 提供者或Ukey忙。
 *     <br>OH_HUKS_ERR_CODE_EXCEED_LIMIT 12000025 - 打开资源的数量超过限制。
 * @since 22
 */
struct OH_Huks_Result OH_Huks_OpenResource(
    const struct OH_Huks_Blob *resourceId, const OH_Huks_ExternalCryptoParamSet *paramSet);

/**
 * @brief 根据指定的资源ID关闭资源。
 *
 * @param resourceId 指定提供者的资源ID。
 * @param paramSet 指向句柄操作参数的指针。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS 0 - 操作成功。
 *     <br>OH_HUKS_ERR_CODE_NOT_SUPPORTED_API 801 - 不支持的 API。
 *     <br>OH_HUKS_ERR_CODE_COMMUNICATION_FAIL 12000005 - IPC通信失败。
 *     <br>OH_HUKS_ERR_CODE_CRYPTO_FAIL 12000006 - Ukey驱动报错。
 *     <br>OH_HUKS_ERR_CODE_INTERNAL_ERROR 12000012 - 发生系统内部错误，处理函数未找到。
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014 - 内存不足。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT 12000018 - resourceId或paramSet无效。
 *     <br>OH_HUKS_ERR_CODE_EXTERNAL_ERROR 12000020 - 提供者执行失败。
 *     <br>OH_HUKS_ERR_CODE_BUSY 12000024 - 提供者或Ukey忙。
 * @since 22
 */
struct OH_Huks_Result OH_Huks_CloseResource(
    const struct OH_Huks_Blob *resourceId, const OH_Huks_ExternalCryptoParamSet *paramSet);

/**
 * @brief 获取指定Ukey资源ID的PIN授权状态。
 *
 * @param resourceId 指定提供者的资源ID。
 * @param paramSet 指向PIN授权参数的指针。
 * @param authState 用于返回指定索引的授权状态。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS 0 - 操作成功。
 *     <br>OH_HUKS_ERR_CODE_NOT_SUPPORTED_API 801 - 不支持的API。
 *     <br>OH_HUKS_ERR_CODE_COMMUNICATION_FAIL 12000005 - IPC通信失败。
 *     <br>OH_HUKS_ERR_CODE_CRYPTO_FAIL 12000006 - Ukey驱动报错。
 *     <br>OH_HUKS_ERR_CODE_ITEM_NOT_EXIST 12000011 - 指定的资源ID无效。
 *     <br>OH_HUKS_ERR_CODE_INTERNAL_ERROR 12000012 - 发生系统内部错误，处理函数未找到。
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014 - 内存不足。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT 12000018 - resourceId或paramSet无效。
 *     <br>OH_HUKS_ERR_CODE_EXTERNAL_ERROR 12000020 - 提供者执行失败。
 *     <br>OH_HUKS_ERR_CODE_BUSY 12000024 - 提供者或Ukey忙。
 * @since 22
 */
struct OH_Huks_Result OH_Huks_GetUkeyPinAuthState(
    const struct OH_Huks_Blob *resourceId, const OH_Huks_ExternalCryptoParamSet *paramSet,
    OH_Huks_ExternalPinAuthState *authState);

/**
 * @brief 外部密钥管理能力扩展提供者获取属性信息。
 *
 * @param resourceId 指定提供者的资源ID。
 * @param propertyId 指定按GMT 0016-2023定义的属性函数名称。
 * @param paramSetIn 指向输入操作参数的指针。
 * @param paramSetOut 指向输出参数的指针，且必须包含参数OH_HUKS_EXT_CRYPTO_TAG_EXTRA_DATA。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS 0 - 操作成功。
 *     <br>OH_HUKS_ERR_CODE_NOT_SUPPORTED_API 801 - 不支持的API。
 *     <br>OH_HUKS_ERR_CODE_COMMUNICATION_FAIL 12000005 - IPC通信失败。
 *     <br>OH_HUKS_ERR_CODE_CRYPTO_FAIL 12000006 - 驱动错误。
 *     <br>OH_HUKS_ERR_CODE_ITEM_NOT_EXIST 12000011 - 未找到缓存的指定句柄。
 *     <br>OH_HUKS_ERR_CODE_INTERNAL_ERROR 12000012 - 发生系统内部错误，处理函数未找到。
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014 - 内存不足。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT 12000018 - resourceId、propertyId、paramSet或回调无效。
 *     <br>OH_HUKS_ERR_CODE_EXTERNAL_ERROR 12000020 - 提供者或Ukey内部执行失败。
 *     <br>OH_HUKS_ERR_CODE_PIN_LOCKED 12000021 - PIN码被锁定。
 *     <br>OH_HUKS_ERR_CODE_PIN_NO_AUTH 12000023 - PIN码未通过认证。
 *     <br>OH_HUKS_ERR_CODE_BUSY 12000024 - 提供者或Ukey中的资源正在被使用。
 * @since 22
 */
struct OH_Huks_Result OH_Huks_GetProperty(const struct OH_Huks_Blob *resourceId,
    const struct OH_Huks_Blob *propertyId, const OH_Huks_ExternalCryptoParamSet *paramSetIn,
    OH_Huks_ExternalCryptoParamSet **paramSetOut);

/**
 * @brief 初始化一个参数集合。
 *
 * @param paramSet 指向要初始化的参数集合的二级指针。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS 0 - 操作成功。
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014 - 内存不足。
 *     <br>OH_HUKS_ERR_CODE_INVALID_ARGUMENT 12000018 - params为NULL或paramSet无效。
 * @since 22
 */
struct OH_Huks_Result OH_Huks_InitExternalCryptoParamSet(OH_Huks_ExternalCryptoParamSet **paramSet);

/**
 * @brief 向参数集合中添加参数。
 *
 * @param paramSet 指向将要添加参数的参数集合。
 * @param params 指向要添加的参数数组。
 * @param paramCnt 要添加的参数数量。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS 0 - 操作成功。
 *     <br>OH_HUKS_ERR_CODE_INVALID_ARGUMENT 12000018 - params为NULL或paramSet无效。
 * @since 22
 */
struct OH_Huks_Result OH_Huks_AddExternalCryptoParams(OH_Huks_ExternalCryptoParamSet *paramSet,
    const OH_Huks_ExternalCryptoParam *params, uint32_t paramCnt);

/**
 * @brief 构建一个参数集合。
 *
 * @param paramSet 指向要构建的参数集合的二级指针。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS 0 - 操作成功。
 *     <br>OH_HUKS_ERR_CODE_INVALID_ARGUMENT 12000018 - paramSet无效。
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014 - 内存不足。
 * @since 22
 */
struct OH_Huks_Result OH_Huks_BuildExternalCryptoParamSet(OH_Huks_ExternalCryptoParamSet **paramSet);

/**
 * @brief 销毁一个参数集合并释放相关内存。
 *
 * @param paramSet 指向要销毁的参数集合的二级指针。
 * @since 22
 */
void OH_Huks_FreeExternalCryptoParamSet(OH_Huks_ExternalCryptoParamSet **paramSet);

/**
 * @brief 从参数集合中获取指定参数。
 *
 * @param paramSet 指向目标参数集合的指针。
 * @param tag 指定要获取的参数标签值。
 * @param param 用于返回获取到的参数的二级指针。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS 0 - 操作成功。
 *     <br>OH_HUKS_ERR_CODE_INVALID_ARGUMENT 12000018 - paramSet或param无效，或参数在集合中不存在。
 * @since 22
 */
struct OH_Huks_Result OH_Huks_GetExternalCryptoParam(OH_Huks_ExternalCryptoParamSet *paramSet,
    const uint32_t tag, OH_Huks_ExternalCryptoParam **param);
#ifdef __cplusplus
}
#endif

/** @} */
#endif /* NATIVE_HUKS_EXTERNAL_CRYPTO_API_H */
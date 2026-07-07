/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef NET_SSL_C_H
#define NET_SSL_C_H

#include <stdbool.h>

/**
 * @addtogroup netstack
 * @{
 *
 * @brief Provides C APIs for the SSL/TLS certificate chain verification module.
 *
 * @since 11
 * @version 1.0
 */

/**
 * @addtogroup netstack
 * @{
 *
 * @brief Provides C APIs for the SSL/TLS certificate chain verification module.
 *
 * @since 11
 * @version 1.0
 */

/**
 * @file net_ssl_c.h
 *
 * @brief 定义SSL/TLS证书链校验模块C接口数据结构。
 *
 * @library libnet_ssl.so
 * @kit NetworkKit
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */

#include "net_ssl_c_type.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 对外暴露的证书链校验接口。
 *
 * @param cert 用户传入的待校验证书。
 * @param caCert 用户指定的证书，若为空则以系统预置证书进行校验。
 * @return 0 - 成功。
 *     <br>2305001 - 未指定的错误。
 *     <br>2305002 - 无法获取颁发者证书。
 *     <br>2305003 - 无法获取证书吊销列表（CRL）。
 *     <br>2305004 - 无法解密证书签名。
 *     <br>2305005 - 无法解密CRL签名。
 *     <br>2305006 - 无法解码颁发者公钥。
 *     <br>2305007 - 证书签名失败。
 *     <br>2305008 - CRL签名失败。
 *     <br>2305009 - 证书尚未生效。
 *     <br>2305010 - 证书已过期。
 *     <br>2305011 - CRL尚未有效。
 *     <br>2305012 - CRL已过期。
 *     <br>2305023 - 证书已被吊销。
 *     <br>2305024 - 证书颁发机构（CA）无效。
 *     <br>2305027 - 证书不受信任。
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */
uint32_t OH_NetStack_CertVerification(const struct NetStack_CertBlob *cert, const struct NetStack_CertBlob *caCert);

/**
 * @brief 获取证书锁定信息。
 *
 * @param hostname 主机名。
 * @param pin 证书锁定信息的结构体。
 * @return 0 - 成功。
 *     <br>401 - 参数设置错误。
 *     <br>2305999 - 内存错误。
 * @syscap SystemCapability.Communication.NetStack
 * @since 12
 * @version 1.0
 */
int32_t OH_NetStack_GetPinSetForHostName(const char *hostname, NetStack_CertificatePinning *pin);

/**
 * @brief 获取证书信息。
 *
 * @param hostname 主机名。
 * @param certs 证书信息的结构体。
 * @return 0 - 成功。
 *     <br>401 - 参数设置错误。
 *     <br>2305999 - 内存错误。
 * @syscap SystemCapability.Communication.NetStack
 * @since 12
 * @version 1.0
 */
int32_t OH_NetStack_GetCertificatesForHostName(const char *hostname, NetStack_Certificates *certs);

/**
 * @brief 释放证书内容。
 *
 * @param certs 证书信息。
 * @syscap SystemCapability.Communication.NetStack
 * @since 12
 * @version 1.0
 */
void OH_Netstack_DestroyCertificatesContent(NetStack_Certificates *certs);

/**
 * @brief 整体明文HTTP是否允许。
 *
 * @permission ohos.permission.INTERNET
 * @return 0 - 成功。
 *     <br>201 - 权限被拒。
 *     <br>401 - 参数错误。
 * @param isCleartextPermitted 输出参数，如果允许明文流量，则true，否则false。
 * @since 18
 */
int32_t OH_Netstack_IsCleartextPermitted(bool *isCleartextPermitted);

/**
 * @brief 按域名明文HTTP是否允许。
 *
 * @permission ohos.permission.INTERNET
 * @return 0 - 成功。
 *     <br>201 - 权限被拒。
 *     <br>401 - 参数错误。
 * @param hostname 主机名。
 * @param isCleartextPermitted 输出参数，如果允许指定主机名的明文流量，则true，否则false。
 * @since 18
 */
int32_t OH_Netstack_IsCleartextPermittedByHostName(const char *hostname, bool *isCleartextPermitted);

/**
 * @brief 检查组件是否已配置开启明文HTTP拦截功能。
 *
 * @return 0 - 成功。
 *     <br>2100001 - 无效的参数值。
 * @param component 组件名称，当前支持的组件：Network Kit、ArkWeb。
 * @param componentCfg 输出参数，组件是否配置开启明文HTTP拦截功能，如果开启则为true，否则为false。
 * @since 20
 */
int32_t OH_Netstack_IsCleartextCfgByComponent(const char *component, bool *componentCfg);

/**
 * @brief 创建并验证排序的证书链。
 *
 * @detail This function verifies the provided certificate chain and constructs
 *         a sorted chain output. It allocates memory for the output chain,
 *         which must be explicitly freed by the caller to avoid memory leaks.
 *
 * @param cert 要验证的证书链。不能为NULL或空。
 * @param certCount 证书链中的证书数量。
 * @param caCert 用户指定的CA证书。如果为NULL，则使用预设证书。
 * @param hostname 预期的服务器主机名。
 * @param outSortedChain 用于接收排序证书链的指针。
 *                     如果调用者不需要链数据，可以为NULL。
 *                     仅在返回值为0时有效。
 *                     必须使用OH_NetStack_FreeCertChain释放分配的内存。
 * @param outSortedCount 用于接收排序证书数量的指针。
 * @return 0 - 成功。
 *         2305001 - 未指定的错误。
 *         2305002 - 无法获取颁发者证书。
 *         2305004 - 无法解密证书签名。
 *         2305006 - 无法解码颁发者公钥。
 *         2305007 - 证书签名失败。
 *         2305009 - 证书尚未生效。
 *         2305010 - 证书已过期。
 *         2305024 - 无效的证书颁发机构(CA)。
 *         2305062 - 主机名验证失败。
 *         2305027 - 证书不受信任。
 * @stagemodelonly
 * @since 26.0.0
 * @note After use, you must call {@link OH_NetStack_FreeCertChain} to release the
 *       allocated memory pointed by outSortedChain. Failure to do so will cause memory leaks.
 */
uint32_t OH_NetStack_CreateAndVerifySortedCertChain(const struct NetStack_CertBlob *cert, size_t certCount,
    const struct NetStack_CertBlob *caCert, const char *hostname,
    struct NetStack_CertBlob **outSortedChain, size_t *outSortedCount);

/**
 * @brief 释放由OH_NetStack_CreateAndVerifySortedCertChain分配的证书链。
 *
 * @detail This function must be used to free the memory pointed to by outSortedChain
 *         from OH_NetStack_CreateAndVerifySortedCertChain.
 *         Do NOT use free() or malloc() directly on this memory.
 *
 * @param certChain 从outSortedChain接收的证书链指针。
 *                  如果为NULL，此函数不执行任何操作。
 * @param certCount 证书链中的证书数量。
 * @stagemodelonly
 * @since 26.0.0
 */
void OH_NetStack_FreeCertChain(struct NetStack_CertBlob *certChain, size_t certCount);

#ifdef __cplusplus
}
#endif

/** @} */

#endif // NET_SSL_C_H
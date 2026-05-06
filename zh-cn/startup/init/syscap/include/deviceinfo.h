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
 * @addtogroup DeviceInfo
 * @{
 *
 * @brief Provides APIs for querying terminal device information.
 *
 * @since 10
 */
/**
 * @file deviceinfo.h
 * @kit BasicServicesKit
 * @brief 声明用于查询终端设备信息的API。
 *
 * @library libdeviceinfo_ndk.z.so
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */

#ifndef DEVICEINFO_CSDK_H
#define DEVICEINFO_CSDK_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief 获取设备类型。
 *
 * @return "phone"(或"default")
 *    <br>"wearable",
 *    <br>"liteWearable",
 *    <br>"tablet",
 *    <br>"tv",
 *    <br>"car",
 *    <br>"smartVision"。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetDeviceType(void);

/**
 * @brief 获取设备制造商。
 *
 * @return 字符串类型的设备制造商。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetManufacture(void);

/**
 * @brief 获取设备品牌。
 *
 * @return 字符串类型的设备品牌。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBrand(void);

/**
 * @brief 获取外部产品系列。
 *
 * @return 字符串类型的外部产品系列。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetMarketName(void);

/**
 * @brief 获取产品系列。
 *
 * @return 字符串类型的产品系列。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetProductSeries(void);

/**
 * @brief 获取认证型号。
 *
 * @return 字符串类型的认证型号。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetProductModel(void);

/**
 * @brief 获取内部软件子型号。
 *
 * @return 字符串类型的内部软件子型号。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetSoftwareModel(void);

/**
 * @brief 获取硬件版本号。
 *
 * @return 字符串类型的硬件版本号。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetHardwareModel(void);

/**
 * @brief 获取Bootloader版本号。
 *
 * @return 字符串类型的Bootloader版本号。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBootloaderVersion(void);

/**
 * @brief 获取应用二进制接口（Abi）。
 *
 * @return 字符串类型的应用二进制接口（Abi）。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetAbiList(void);

/**
 * @brief 获取安全补丁级别。
 *
 * @return 字符串类型的安全补丁级别。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetSecurityPatchTag(void);

/**
 * @brief 获取产品版本。
 *
 * @return 字符串类型的产品版本。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetDisplayVersion(void);

/**
 * @brief 获取差异版本。
 *
 * @return 字符串类型的获取差异版本。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetIncrementalVersion(void);

/**
 * @brief 获取系统的发布类型。
 * @return 操作系统发布类别包括"Release"、"Beta"和"Canary"。
 *     <br>具体的发布类型可能是"Release"，"Beta1"，或其他类似的。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetOsReleaseType(void);

/**
 * @brief 获取完整的系统版本名。
 *
 * @return 字符串类型的完整的系统版本名。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetOSFullName(void);

/**
 * @brief 获取系统软件API版本。
 *
 * @return 系统软件API版本。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
int OH_GetSdkApiVersion(void);

/**
 * @brief 获取首个版本系统软件API版本。
 *
 * @return 首个版本系统软件API版本。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
int OH_GetFirstApiVersion(void);

/**
 * @brief 获取版本ID。
 *
 * @return 字符串类型的版本ID。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetVersionId(void);

/**
 * @brief 获取系统的构建类型。
 *
 * @return 字符串类型的系统的构建类型。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildType(void);

/**
 * @brief 获取系统的构建用户。
 *
 * @return 字符串类型的系统的构建用户。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildUser(void);

/**
 * @brief 获取系统的构建主机。
 *
 * @return 字符串类型的系统的构建主机。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildHost(void);

/**
 * @brief 获取系统的构建时间。
 *
 * @return 字符串类型的系统的构建时间。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildTime(void);

/**
 * @brief 获取系统的构建版本Hash。
 *
 * @return 字符串类型的系统的构建版本Hash。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildRootHash(void);

/**
 * @brief 获取ISV发行系统版本名称。独立软件供应商（ISV）可以使用自己定义的系统名称。
 *
 * @return ISV发行系统版本名称。
 *     <br>如果没有指定ISV，它将返回一个空字符串。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetDistributionOSName(void);

/**
 * @brief 获取ISV发行版系统版本号。
 *
 * @return ISV发行版系统版本号。
 *     <br>如果没有指定ISV，它将返回与{@link OH_GetOSFullName}相同的值。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetDistributionOSVersion(void);

/**
 * @brief 获取ISV发行版系统api版本。
 *
 * @return ISV发行版系统api版本。
 *     <br>如果没有指定ISV，它将返回与{@link OH_GetSdkApiVersion}相同的值。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
int OH_GetDistributionOSApiVersion(void);

/**
 * @brief 获取ISV发行版系统类型。
 *
 * @return ISV发行版系统类型。
 *     <br>如果没有指定ISV，它将返回与{@link OH_GetOsReleaseType}相同的值。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetDistributionOSReleaseType(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif // #if __cplusplus
#endif // #ifdef __cplusplus
#endif // DEVICEINFO_CSDK_H
/** @} */

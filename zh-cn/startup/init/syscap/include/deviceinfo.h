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
 * @brief 提供查询终端设备信息的API。
 * 该模块提供了获取设备类型、制造商、品牌、型号、版本信息等设备基础信息的能力，
 * 适用于需要根据设备特性进行适配、统计设备信息或进行设备管理的场景。
 * 这些API通过读取系统属性获取设备信息，返回值为指向常量字符串的指针。
 * 该指针指向系统内部存储的数据，调用者无需释放内存。
 *
 * @since 10
 */
/**
 * @file deviceinfo.h
 * @kit BasicServicesKit
 * @brief 声明用于查询终端设备信息的API。
 * 该模块提供了获取设备类型、制造商、品牌、型号、版本信息等设备基础信息的能力，
 * 适用于需要根据设备特性进行适配、统计设备信息或进行设备管理的场景。
 * 这些API通过读取系统属性获取设备信息，返回值为指向常量字符串的指针。
 * 该指针指向系统内部存储的数据，调用者无需释放内存。
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
 * @return 可能的值包括：
 *    <br>• "phone"
 *    <br>• "default"（设备类型无法识别时的默认返回值）
 *    <br>• "wearable"
 *    <br>• "liteWearable"
 *    <br>• "tablet"
 *    <br>• "tv"
 *    <br>• "car"
 *    <br>• "smartVision"
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
 * @brief 获取外部产品系列，即外部产品名称。
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
 * @brief 获取内部软件子型号，当多个硬件型号共用同一软件版本时，该字段用于区分不同的软件分支。
 *
 * @return 字符串类型的内部软件子型号。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetSoftwareModel(void);

/**
 * @brief 获取硬件版本号。
 *
 * @return 字符串类型的硬件版本号。常见的取值包括："TASA00CVN1"等。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetHardwareModel(void);

/**
 * @brief 获取Bootloader版本号。
 *
 * @return 字符串类型的Bootloader版本号。常见的取值包括："bootloader"等。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBootloaderVersion(void);

/**
 * @brief 获取应用二进制接口（Abi）。
 *
 * @return 字符串类型的应用二进制接口（Abi）。返回支持的ABI列表，多个取值以英文逗号分隔。常见的取值包括："arm64-v8a"等。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetAbiList(void);

/**
 * @brief 获取安全补丁级别。
 *
 * @return 字符串类型的安全补丁级别。格式通常为"YYYY/MM/DD"，表示安全补丁的发布日期，例如"2023/10/05"。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetSecurityPatchTag(void);

/**
 * @brief 获取产品版本。
 *
 * @return 产品版本号，返回设备产品版本的字符串标识。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetDisplayVersion(void);

/**
 * @brief 获取差异版本。
 *
 * @return 字符串类型的差异版本。常见的取值包括："6.1.1.120"等。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetIncrementalVersion(void);

/**
 * @brief 获取系统的发布类型。返回预定义的发布类型字符串。
 * @return 操作系统发布类别包括"Release"、"Beta"和"Canary"。
 *         <br> 具体的发布类型可能是"release"，"Beta1"，或其他类似的。
 *         <br>-&nbsp;Canary：面向特定开发者发布的早期预览版本，不承诺API稳定性。
 *         <br>-&nbsp;Beta：面向开发者公开发布的Beta版本，不承诺API稳定性。
 *         <br>-&nbsp;Release：面向开发者公开发布的正式版本，承诺API稳定性。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetOsReleaseType(void);

/**
 * @brief 获取完整的系统版本名。
 *
 * @return 字符串类型的完整的系统版本名。版本格式 OpenHarmony-x.x.x.x。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetOSFullName(void);

/**
 * @brief 获取系统软件API版本。
 *
 * @return 系统软件API版本，取值范围为整数。常见的取值包括：12等。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
int OH_GetSdkApiVersion(void);

/**
 * @brief 获取首个版本系统软件API版本。指设备首次发布时所支持的系统软件API版本。
 *
 * @return 首个版本系统软件API版本。指设备首次发布时所支持的系统软件API版本，取值范围为整数。
 *         常见的取值包括：3等。
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
 * @return 字符串类型的系统的构建类型。默认值为：default。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildType(void);

/**
 * @brief 获取系统的构建用户。
 *
 * @return 字符串类型的系统的构建用户。默认值为：default。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildUser(void);

/**
 * @brief 获取系统的构建主机。
 *
 * @return 字符串类型的系统的构建主机。默认值为：default。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildHost(void);

/**
 * @brief 获取系统的构建时间。
 *
 * @return 字符串类型的系统的构建时间，表示系统版本构建的时间戳。常见的取值包括："1783430505910"等。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildTime(void);

/**
 * @brief 获取系统的构建版本Hash。
 *
 * @return 字符串类型的系统的构建版本Hash。默认值为：default。
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildRootHash(void);

/**
 * @brief 获取ISV发行版系统名称。独立软件供应商（ISV）可以使用自定义的系统名称。
 *
 * @return ISV发行版系统名称。
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
 * @brief 获取ISV发行版系统API版本。
 *
 * @return ISV发行版系统API版本。
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

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
 * @brief Declares the APIs for querying device information.
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
 * @brief Obtains the device type.
 * 
 * @return Returns one of the following values:
 *     <br>**phone** (or **default**),
 *     <br>**wearable**,
 *     <br>**liteWearable**,
 *     <br>**tablet**,
 *     <br>**tv**,
 *     <br>**car**,
 *     <br>**smartVision**
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetDeviceType(void);

/**
 * @brief Obtains the device manufacturer.
 *
 * @return Returns a device manufacturer. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetManufacture(void);

/**
 * @brief Obtains the device brand.
 *
 * @return Returns a device brand. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBrand(void);

/**
 * @brief Obtains the market name.
 *
 * @return Returns a market name. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetMarketName(void);

/**
 * @brief Obtains the product series.
 *
 * @return Returns the product series. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetProductSeries(void);

/**
 * @brief Obtains the product model.
 *
 * @return Returns a product model. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetProductModel(void);

/**
 * @brief Obtains the software model.
 *
 * @return Returns a software model. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetSoftwareModel(void);

/**
 * @brief Obtains the hardware model.
 *
 * @return Returns a hardware model. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetHardwareModel(void);

/**
 * @brief Obtains the Bootloader version.
 *
 * @return Returns a Bootloader version. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBootloaderVersion(void);

/**
 * @brief Obtains the ABI list.
 *
 * @return Returns an ABI list. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetAbiList(void);

/**
 * @brief Obtains the security patch tag.
 *
 * @return Returns a security patch tag. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetSecurityPatchTag(void);

/**
 * @brief Obtains the display version.
 *
 * @return Returns a display version. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetDisplayVersion(void);

/**
 * @brief Obtains the incremental version.
 *
 * @return Returns an incremental version. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetIncrementalVersion(void);

/**
 * @brief Obtains the OS release type represented by a string.
 * @return Returns an OS release type. The options include **Release**, **Beta**, and **Canary**.
 *     <br>A specific release type may be **Release**, **Beta1**, or another similar type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetOsReleaseType(void);

/**
 * @brief Obtains the OS full name.
 *
 * @return Returns an OS full name. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetOSFullName(void);

/**
 * @brief Obtains the SDK API version.
 *
 * @return Returns an SDK API version.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
int OH_GetSdkApiVersion(void);

/**
 * @brief Obtains the first API version.
 *
 * @return Returns the first API version.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
int OH_GetFirstApiVersion(void);

/**
 * @brief Obtains the version ID.
 *
 * @return Returns a version ID. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetVersionId(void);

/**
 * @brief Obtains the build type.
 *
 * @return Returns a build type. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildType(void);

/**
 * @brief Obtains the build user.
 *
 * @return Returns a build user. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildUser(void);

/**
 * @brief Obtains the build host.
 *
 * @return Returns a build host. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildHost(void);

/**
 * @brief Obtains the build time.
 *
 * @return Returns the build time. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildTime(void);

/**
 * @brief Obtains the build root hash.
 *
 * @return Returns a build root hash. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildRootHash(void);

/**
 * @brief Obtains the Distribution OS name represented by a string.
 * @return Returns an ISV distribution OS name.
 *     <br>If no ISV is specified, an empty string is returned.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetDistributionOSName(void);

/**
 * @brief Obtains the ISV distribution OS version.
 * 
 * @return Returns an ISV distribution OS version.
 *     <br>If no ISV is specified, the value of {@link OH_GetOSFullName} is returned.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetDistributionOSVersion(void);

/**
 * @brief Obtains the ISV distribution OS API version.
 * 
 * @return Returns an ISV distribution OS API version.
 *     <br>If no ISV is specified, the value of {@link OH_GetSdkApiVersion} is returned.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
int OH_GetDistributionOSApiVersion(void);

/**
 * @brief Obtains the ISV distribution OS release type.
 *
 * @return Returns an ISV distribution OS release type.
 *     <br>If no ISV is specified, the value of {@link OH_GetOsReleaseType} is returned.
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

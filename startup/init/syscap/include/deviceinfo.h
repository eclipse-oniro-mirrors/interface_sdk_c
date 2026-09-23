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
 * @brief Provides APIs for querying device information.
 * This module provides the capability of obtaining basic device information, such as the device type,
 * manufacturer, brand, model, and version. It can be used to adapt device features, collect device
 * information, or manage devices. These APIs obtain device information by reading system properties.
 * The return value is a pointer to a constant string. The pointer points to the data stored in the
 * system. The caller does not need to release the memory.
 *
 * @since 10
 */
/**
 * @file deviceinfo.h
 * @include <deviceinfo.h>
 * @kit BasicServicesKit
 * @brief Declares the APIs for querying device information.
 * This module provides the capability of obtaining basic device information, such as the device type,
 * manufacturer, brand, model, and version. It can be used to adapt device features, collect device
 * information, or manage devices. These APIs obtain device information by reading system properties.
 * The return value is a pointer to a constant string. The pointer points to the data stored in the
 * system. The caller does not need to release the memory.
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
 * @brief Obtains the device type. This API returns a predefined device type in the form of a string.
 *
 * @return Device type as a string. The options are as follows:
 *    <br>• **phone**
 *    <br>• **default**: default value returned when the device type cannot be identified
 *    <br>• **wearable**
 *    <br>• **liteWearable**
 *    <br>• **tablet**
 *    <br>• **tv**
 *    <br>• **car**
 *    <br>• **smartVision**
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
 * @brief Obtains the external product series, that is, the market name.
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
 * @brief Obtains the software model. When the same software version is used on different hardware
 * models, this field is used to distinguish different software branches.
 *
 * @return Returns a software model. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetSoftwareModel(void);

/**
 * @brief Obtains the hardware model.
 *
 * @return Hardware model. The value is of the string type. Common values include **TASA00CVN1**.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetHardwareModel(void);

/**
 * @brief Obtains the Bootloader version.
 *
 * @return Bootloader version. The value is of the string type. Common values include **bootloader**.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBootloaderVersion(void);

/**
 * @brief Obtains the ABI list.
 *
 * @return ABI list supported. The value is of the string type. Multiple values are separated by
 * commas (,). Common values include **arm64-v8a**.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetAbiList(void);

/**
 * @brief Obtains the security patch tag.
 *
 * @return Security patch tag. The value is of the string type. The format is **YYYY/MM/DD**, for
 * example, **2023/10/05**, indicating the release date of the security patch.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetSecurityPatchTag(void);

/**
 * @brief Obtains the display version.
 *
 * @return Product version of the device. The value is of the string type.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetDisplayVersion(void);

/**
 * @brief Obtains the incremental version.
 *
 * @return Incremental version. The value is of the string type. Common values include **6.1.1.120**.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetIncrementalVersion(void);

/**
 * @brief Obtains the OS release type. This API returns a predefined OS release type in the form of
 * a string.
 * @return OS release type. The options include **Release**, **Beta**, and **Canary**
 *    <br>A specific release type can be **release** or **Beta1**.
 *    <br>-&nbsp;**Canary**: Preliminary release open only to specific developers. This release does
 *    not promise API stability and may require tolerance of instability.
 *    <br>-&nbsp;**Beta**: Release open to all developers. This release does not promise API stability
 *    and may require tolerance of instability.
 *    <br>-&nbsp;**Release**: Official release open to all developers. This release promises that all
 *    APIs are stable.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetOsReleaseType(void);

/**
 * @brief Obtains the OS full name.
 *
 * @return Full OS name. The value is of the string type. The version format is **OpenHarmony-x.x.x.x**.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetOSFullName(void);

/**
 * @brief Obtains the SDK API version.
 *
 * @return SDK API version. The value is an integer. Common values include **12**.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
int OH_GetSdkApiVersion(void);

/**
 * @brief Obtains the first API version, which is the API version supported by the device when it was
 * first released.
 *
 * @return First API version, which is the API version supported by the device when it was first
 * released. The value is an integer. Common values include **3**.
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
 * @return Build type. The value is of the string type. The default value is **default**.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildType(void);

/**
 * @brief Obtains the build user.
 *
 * @return Build user. The value is of the string type. The default value is **default**.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildUser(void);

/**
 * @brief Obtains the build host.
 *
 * @return Build host. The value is of the string type. The default value is **default**.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildHost(void);

/**
 * @brief Obtains the build time.
 *
 * @return Build time, indicating the timestamp when the OS version is built. The value is of the
 * string type. Common values include **1783430505910**.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildTime(void);

/**
 * @brief Obtains the build root hash.
 *
 * @return Build root hash. The value is of the string type. The default value is **default**.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetBuildRootHash(void);

/**
 * @brief Obtains the ISV distribution OS name. ISVs can use their own OS names.
 *
 * @return ISV distribution OS name.
 *     <br>If no ISV is specified, an empty string is returned.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetDistributionOSName(void);

/**
 * @brief Obtains the ISV distribution OS version.
 *
 * @return Returns an ISV distribution OS version.
 *    <br>If no ISV is specified, the value of {@link OH_GetOSFullName} is returned.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
const char *OH_GetDistributionOSVersion(void);

/**
 * @brief Obtains the ISV distribution OS API version.
 *
 * @return ISV distribution OS API version.
 *    <br>If no ISV is specified, the value of {@link OH_GetSdkApiVersion} is returned.
 * @syscap SystemCapability.Startup.SystemInfo
 * @since 10
 */
int OH_GetDistributionOSApiVersion(void);

/**
 * @brief Obtains the ISV distribution OS release type.
 *
 * @return ISV distribution OS release type.
 *    <br>If no ISV is specified, the value of {@link OH_GetOsReleaseType} is returned.
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

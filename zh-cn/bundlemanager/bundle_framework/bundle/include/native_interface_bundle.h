/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
 * @addtogroup Native_Bundle
 * @{
 *
 * @brief Describes the Native Bundle.
 *
 * @since 9
 * @version 1.0
 */

/**
 * @file native_interface_bundle.h
 *
 * @brief 提供查询应用包信息的功能，包括应用包名、应用指纹、应用appId等。
 *
 * @kit AbilityKit
 * @library libbundle_ndk.z.so
 * @syscap SystemCapability.BundleManager.BundleFramework.Core
 * @since 9
 * @version 1.0
 */
#ifndef FOUNDATION_APPEXECFWK_STANDARD_KITS_APPKIT_NATIVE_BUNDLE_INCLUDE_NATIVE_INTERFACE_BUNDLE_H
#define FOUNDATION_APPEXECFWK_STANDARD_KITS_APPKIT_NATIVE_BUNDLE_INCLUDE_NATIVE_INTERFACE_BUNDLE_H

#include <stdbool.h>
#include <stddef.h>

#include "ability_resource_info.h"
#include "bundle_manager_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 应用包信息数据结构，包含应用包名和应用指纹信息。
 *
 * @syscap SystemCapability.BundleManager.BundleFramework.Core
 * @since 9
 */
struct OH_NativeBundle_ApplicationInfo {
    /**
     * 应用包名。
     * @syscap SystemCapability.BundleManager.BundleFramework.Core
     * @since 9
     */
    char* bundleName;

    /**
     * 应用的指纹信息，由签名证书通过SHA-256算法计算哈希值生成。使用的签名证书发生变化时，该字段也会发生变化。
     * @syscap SystemCapability.BundleManager.BundleFramework.Core
     * @since 9
     */
    char* fingerprint;
};

/**
 * @brief elementName信息。
 *
 * @since 13
 */
struct OH_NativeBundle_ElementName {
    /**
     * 应用包名。
     */
    char* bundleName;
    /**
     * 模块名称。
     */
    char* moduleName;
    /**
     * 组件名。
     */
    char* abilityName;
};

/**
 * @brief 元数据信息。
 *
 * @since 20
 */
typedef struct OH_NativeBundle_Metadata {
    /**
     * @brief 元数据名称。
     *
     */
    char* name;
    /**
     * @brief 元数据值。
     *
     */
    char* value;
    /**
     * @brief 元数据资源。
     *
     */
    char* resource;
} OH_NativeBundle_Metadata;

/**
 * @brief 模块元数据的信息。
 *
 * @since 20
 */
typedef struct OH_NativeBundle_ModuleMetadata {
    /**
     * @brief 模块名称。
     *
     */
    char* moduleName;
    /**
     * @brief 模块的元数据数组。
     *
     */
    OH_NativeBundle_Metadata* metadataArray;
    /**
     * @brief 模块的元数据数组大小。
     *
     */
    size_t metadataArraySize;
} OH_NativeBundle_ModuleMetadata;

/**
 * @brief 应用包信息数据结构，包含应用包名和应用指纹信息。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_NativeBundle_ApplicationInfo OH_NativeBundle_ApplicationInfo;

/**
 * @brief elementName信息。
 *
 * @since 13
 * @version 1.0
 */
typedef struct OH_NativeBundle_ElementName OH_NativeBundle_ElementName;

/**
 * @brief 获取当前应用信息，包含应用包名和应用指纹信息。
 *
 * @return 返回新创建的OH_NativeBundle_ApplicationInfo对象。如果返回的对象中的属性值为NULL，则表示创建失败。
 *     <br> 失败的可能原因是应用程序地址空间已满，导致空间分配失败。
 * @since 9
 * @version 1.0
 */
OH_NativeBundle_ApplicationInfo OH_NativeBundle_GetCurrentApplicationInfo();

/**
 * @brief 获取当前应用的appId。appId是应用的唯一标识，由应用包名和签名信息决定。在使用此接口后，为了避免内存泄漏，需要手动释放接口返回的指针。
 *
 * @return 返回一个新创建的字符串，用于指示appID信息。如果返回的对象为NULL，则表示创建失败。
 *     <br> 失败的可能原因是应用程序地址空间已满，导致空间分配失败。
 * @since 11
 * @version 1.0
 */
char* OH_NativeBundle_GetAppId();

/**
 * @brief 获取当前应用的应用程序标识符。该应用程序标识符在应用的整个生命周期中不会发生变化，包括版本更新、证书更改、公钥和私钥更改以及应用程序迁移。在使用此接口后，为了避免内存泄漏，需要手动释放接口返回的指针。
 *
 * @return 返回一个新创建的字符串，用于指示应用程序标识符信息。如果返回的对象为NULL，则表示创建失败。
 *     <br> 失败的可能原因是应用程序地址空间已满，导致空间分配失败。
 * @since 11
 * @version 1.0
 */
char* OH_NativeBundle_GetAppIdentifier();

/**
 * @brief 获取当前应用入口元素mainElement的信息，包括包名、模块名和组件名，在使用此接口后，为了避免内存泄漏，需要手动释放接口返回的指针。
 *
 * @return 返回新创建的OH_NativeBundle_ElementName对象。如果返回的对象中的属性值为NULL，则表示创建失败。
 *     <br> 失败的可能原因是应用程序地址空间已满，导致空间分配失败。
 * @since 13
 */
OH_NativeBundle_ElementName OH_NativeBundle_GetMainElementName();

/**
 * @brief 获取当前应用适用的设备类型。用于将手机应用分发到平板/2in1设备时，合理适配布局和字体大小。在使用此接口后，为了避免内存泄漏，需要手动释放接口返回的指针。
 *
 * @return 返回一个新创建的字符串，用于指示兼容设备类型。如果返回的对象为NULL，则表示创建失败。
 *     <br> 失败的可能原因是应用程序地址空间已满，导致空间分配失败。
 * @since 14
 * @version 1.0
 */
char* OH_NativeBundle_GetCompatibleDeviceType();

/**
 * @brief 查询当前应用是否处于调试模式。
 *
 * @param isDebugMode 表示应用是否处于调试模式，取值为true表示可调试模式，取值为false表示不可调试模式。
 * @return 如果调用成功，则返回true，否则返回false。
 * @since 20
 */
bool OH_NativeBundle_IsDebugMode(bool* isDebugMode);

/**
 * @brief 获取当前应用程序的模块元数据数组。在使用该接口之后，为了防止内存泄漏，需要手动释放接口返回的指针。
 *
 * @param size 表示模块元数据数组大小。
 * @return 返回模块元数据数组，如果返回的对象为NULL，则表示获取失败。
 *     <br> 失败的可能原因是应用程序地址空间已满，导致空间分配失败。
 * @since 20
 */
OH_NativeBundle_ModuleMetadata* OH_NativeBundle_GetModuleMetadata(size_t* size);

/**
 * @brief 获取支持打开特定文件类型的组件资源信息列表。在使用完该接口之后，为了防止内存泄漏，需要调用{@link OH_AbilityResourceInfo_Destroy}进行释放。
 *
 * @permission ohos.permission.GET_ABILITY_INFO
 * @param fileType 表示待查询的特定文件类型，推荐使用{@link UTD类型}，比如：'general.plain-text'、'general.image'。目前也可以兼容使用{@link MIME type类型}
 *     和文件后缀名称，如：'text/xml' 、 '.png'等。文件后缀与文件类型的映射关系参见{@link UTD预置列表}。不支持传'\*\/\*'。
 * @param abilityResourceInfo 表示返回的组件资源信息列表。
 * @param size 表示返回的组件资源信息列表大小。
 * @return <ul><li>如果调用成功，返回{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}。</li><li>
 *     如果调用方没有正确的权限，返回{@link BUNDLE_MANAGER_ERROR_CODE_PERMISSION_DENIED}。</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_GetAbilityResourceInfo(char* fileType,
    OH_NativeBundle_AbilityResourceInfo** abilityResourceInfo, size_t* size);
#ifdef __cplusplus
};
#endif

/** @} */
#endif // FOUNDATION_APPEXECFWK_STANDARD_KITS_APPKIT_NATIVE_BUNDLE_INCLUDE_NATIVE_INTERFACE_BUNDLE_H
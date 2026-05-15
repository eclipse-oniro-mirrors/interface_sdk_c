/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @brief Describe the functions of AbilityResourceInfo.
 *
 * @since 21
 */

/**
 * @file ability_resource_info.h
 *
 * @brief The file declares the APIs for obtaining the following ability resource information: bundle name, module name,
 *  ability name, icon, clone index, and whether the application is a default application.
 *
 * @library libbundle_ndk.z.so
 * @kit AbilityKit
 * @syscap SystemCapability.BundleManager.BundleFramework.Core
 * @since 21
 */

#ifndef ABILITY_RESOURCE_INFO_H
#define ABILITY_RESOURCE_INFO_H

#include <stdbool.h>
#include <stddef.h>
#include "bundle_manager_common.h"
#include "../arkui/drawable_descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct describes the ability resource information.
 *
 * @since 21
 */
struct OH_NativeBundle_AbilityResourceInfo;
typedef struct OH_NativeBundle_AbilityResourceInfo OH_NativeBundle_AbilityResourceInfo;

/**
 * @brief Obtains the bundle name of the ability. After using this function, you must manually release the
 * pointer returned to prevent memory leakage.
 *
 * @param abilityResourceInfo Pointer to the ability resource information.
 * @param bundleName Double pointer to the bundle name.
 * @return One of the following operation results:
 *     <ul><li>{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}: The retrieval is successful.
 *     </li><li>{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}: The retrieval fails because the
 *     **abilityResourceInfo** parameter is nullptr.</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_GetBundleName(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, char** bundleName);

/**
 * @brief Obtains the module name of the ability. After using this function, you must manually release the pointer
 * returned to prevent memory leakage.
 *
 * @param abilityResourceInfo Pointer to the ability resource information.
 * @param moduleName Double pointer to the module name.
 * @return One of the following operation results:
 *     <ul><li>{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}: The retrieval is successful.
 *     </li><li>{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}: The retrieval fails because the
 *     **abilityResourceInfo** parameter is nullptr.</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_GetModuleName(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, char** moduleName);

/**
 * @brief Obtains the ability name. After using this function, you must manually release the pointer returned to
 * prevent memory leakage.
 *
 * @param abilityResourceInfo Pointer to the ability resource information.
 * @param abilityName Double pointer to the ability name.
 * @return One of the following operation results:
 *     <ul><li>{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}: The retrieval is successful.
 *     </li><li>{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}: The retrieval fails because the
 *     **abilityResourceInfo** parameter is nullptr.</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_GetAbilityName(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, char** abilityName);

/**
 * @brief Obtains the application name of the ability. After using this function, you must manually release the
 * pointerreturned to prevent memory leakage.
 *
 * @param abilityResourceInfo Pointer to the ability resource information.
 * @param label Double pointer to the application name.
 * @return One of the following operation results:
 *     <ul><li>{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}: The retrieval is successful.
 *     </li><li>{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}: The retrieval fails because the
 *     **abilityResourceInfo** parameter is nullptr.</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_GetLabel(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, char** label);

/**
 * @brief Obtains the clone index of the ability.
 *
 * @param abilityResourceInfo Pointer to the ability resource information.
 * @param appIndex Pointer to the clone index.
 * @return One of the following operation results:
 *     <ul><li>{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}: The retrieval is successful.
 *     </li><li>{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}: The retrieval fails because the **
 *     abilityResourceInfo** parameter is nullptr.</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_GetAppIndex(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, int* appIndex);

/**
 * @brief Checks whether the application to which the ability belongs is a default application.
 *
 * @param abilityResourceInfo Pointer to the ability resource information.
 * @param isDefault Pointer to the check result for whether the application is a default application. A default
 *     application is the preferred application set by the user for a specific file type or operation. **true** if the
 *     application is a default application, **false** otherwise.
 * @return One of the following operation results:
 *     <ul><li>{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}: The query is successful.
 *     </li><li>{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}: The query fails because the abilityResourceInfo
 *     parameter is nullptr.</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_CheckDefaultApp(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, bool* isDefault);

/**
 * @brief Releases memory allocated for ability resource information.
 *
 * @param abilityResourceInfo Pointer to the ability resource information.
 * @param count Size of the ability resource information array.
 * @return One of the following operation results:
 *     <ul><li>{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}: The release is successful.
 *     </li><li>{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}: The release fails because the
 *     **abilityResourceInfo** parameter is nullptr.</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_AbilityResourceInfo_Destroy(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, size_t count);

/**
 * @brief Obtains the size of a single {@link OH_NativeBundle_AbilityResourceInfo} struct.
 *
 * @return Size of a single {@link OH_NativeBundle_AbilityResourceInfo} struct.
 * @since 21
 */
int OH_NativeBundle_GetSize();

/**
 * @brief Obtains the {@link DrawableDescriptor} object of the ability icon resource. After using this function, you
 * must manually release the pointer returned to prevent memory leakage.
 *
 * @param abilityResourceInfo Pointer to the ability resource information.
 * @param drawableIcon Double pointer to the {@link DrawableDescriptor} object.
 * @return One of the following operation results:
 *     <ul><li>{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}: The retrieval is successful.
 *     </li><li>{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}: The retrieval fails because the
 *     **abilityResourceInfo** parameter is nullptr.</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_GetDrawableDescriptor(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, ArkUI_DrawableDescriptor** drawableIcon);
#ifdef __cplusplus
} // extern "C"
#endif

/** @} */
#endif // ABILITY_RESOURCE_INFO_H
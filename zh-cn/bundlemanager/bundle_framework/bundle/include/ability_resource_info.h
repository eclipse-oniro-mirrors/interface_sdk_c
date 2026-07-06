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
 * @brief 表示组件资源信息。
 *
 * @since 21
 */
struct OH_NativeBundle_AbilityResourceInfo;
typedef struct OH_NativeBundle_AbilityResourceInfo OH_NativeBundle_AbilityResourceInfo;

/**
 * @brief 获取组件的包名。在使用该接口之后，为了防止内存泄漏，需要手动释放接口返回的指针。
 *
 * @param abilityResourceInfo 指定组件资源信息。
 * @param bundleName 获取的包名。
 * @return 执行结果。
 *     <ul><li>如果获取成功，返回{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}。
 *     </li><li>如果获取失败，返回{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}，这是由于abilityResourceInfo为空指针所致。</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_GetBundleName(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, char** bundleName);

/**
 * @brief 获取组件的模块名。在使用该接口之后，为了防止内存泄漏，需要手动释放接口返回的指针。
 *
 * @param abilityResourceInfo 指定组件资源信息。
 * @param moduleName 获取的模块名。
 * @return 执行结果。
 *     <ul><li>如果获取成功，返回{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}。
 *     </li><li>如果获取失败，返回{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}，这是由于abilityResourceInfo为空指针所致。</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_GetModuleName(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, char** moduleName);

/**
 * @brief 获取组件名。在使用该接口之后，为了防止内存泄漏，需要手动释放接口返回的指针。
 *
 * @param abilityResourceInfo 指定组件资源信息。
 * @param abilityName 获取的组件名。
 * @return 执行结果。
 *     <ul><li>如果获取成功，返回{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}。
 *     </li><li>如果获取失败，返回{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}，这是由于abilityResourceInfo为空指针所致。</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_GetAbilityName(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, char** abilityName);

/**
 * @brief 获取组件的应用名称。在使用该接口之后，为了防止内存泄漏，需要手动释放接口返回的指针。
 *
 * @param abilityResourceInfo 指定组件资源信息。
 * @param label 获取的应用名称。
 * @return 执行结果。
 *     <ul><li>如果获取成功，返回{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}。
 *     </li><li>如果获取失败，返回{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}，这是由于abilityResourceInfo为空指针所致。</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_GetLabel(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, char** label);

/**
 * @brief 获取组件的分身索引。
 *
 * @param abilityResourceInfo 指定组件资源信息。
 * @param appIndex 获取的分身索引。
 * @return 执行结果。
 *     <ul><li>如果获取成功，返回{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}。
 *     </li><li>如果获取失败，返回{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}，这是由于abilityResourceInfo为空指针所致。</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_GetAppIndex(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, int* appIndex);

/**
 * @brief 查询组件所属的应用是否为默认应用。
 *
 * @param abilityResourceInfo 指定组件资源信息。
 * @param isDefault 组件所属的应用是否为默认应用，默认应用是指用户为特定文件类型或操作设定的首选应用。取值true为默认应用，false为非默认应用。
 * @return 执行结果。
 *     <ul><li>如果获取成功，返回{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}。
 *     </li><li>如果获取失败，返回{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}，这是由于abilityResourceInfo为空指针所致。</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_CheckDefaultApp(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, bool* isDefault);

/**
 * @brief 释放组件资源信息的内存。
 *
 * @param abilityResourceInfo 要释放的组件资源信息。
 * @param count 表示组件资源信息数组的大小。
 * @return 执行结果。
 *     <ul><li>如果获取成功，返回{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}。
 *     </li><li>如果获取失败，返回{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}，这是由于abilityResourceInfo为空指针所致。</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_AbilityResourceInfo_Destroy(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, size_t count);

/**
* @brief 获取单个结构体{@link OH_NativeBundle_AbilityResourceInfo}的大小。
*
 * @return 返回单个结构体{@link OH_NativeBundle_AbilityResourceInfo}的大小。
 * @since 21
 */
int OH_NativeBundle_GetSize();

/**
 * @brief 获取组件图标资源对应的{@link DrawableDescriptor}对象。在使用该接口之后，为了防止内存泄漏，需要手动释放接口返回的指针。
 *
 * @param abilityResourceInfo 指定组件资源信息。
 * @param drawableIcon 组件图标资源对应的{@link DrawableDescriptor}对象。
 * @return 执行结果。
 *     <ul><li>如果获取成功，返回{@link BUNDLE_MANAGER_ERROR_CODE_NO_ERROR}。
 *     </li><li>如果获取失败，返回{@link BUNDLE_MANAGER_ERROR_CODE_PARAM_INVALID}，这是由于abilityResourceInfo为空指针所致。</li></ul>
 * @since 21
 */
BundleManager_ErrorCode OH_NativeBundle_GetDrawableDescriptor(
    OH_NativeBundle_AbilityResourceInfo* abilityResourceInfo, ArkUI_DrawableDescriptor** drawableIcon);
#ifdef __cplusplus
} // extern "C"
#endif

/** @} */
#endif // ABILITY_RESOURCE_INFO_H
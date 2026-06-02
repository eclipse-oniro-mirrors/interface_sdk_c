/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @addtogroup resourcemanager
 * @{
 *
 * @brief Provides the c interface to obtain resources, and relies on librawfile.z.so when used.
 *
 * @since 12
 */
/**
 * @file ohresmgr.h
 *
 * @brief 提供资源管理native侧获取资源的能力。
 *
 * @syscap SystemCapability.Global.ResourceManager
 * @library libohresmgr.so
 * @kit LocalizationKit
 * @since 12
 */
#ifndef GLOBAL_OH_RESMGR_H
#define GLOBAL_OH_RESMGR_H

#include "resmgr_common.h"
#include "../rawfile/raw_file_manager.h"
#include "../arkui/drawable_descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 通过指定资源ID，获取屏幕密度对应的media资源的Base64码。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param resultValue 写入resultValue的结果。
 * @param resultLen 写入resultLen的media长度。
 * @param density 可选参数，取值范围参考{@link ScreenDensity}，默认值为0，表示使用当前系统dpi的密度。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64(const NativeResourceManager *mgr, uint32_t resId,
    char **resultValue, uint64_t *resultLen, uint32_t density = 0);

/**
 * @brief 通过指定资源ID，获取屏幕密度对应的media资源的Base64码。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param resultValue 写入resultValue的结果。
 * @param resultLen 写入resultLen的media长度。
 * @param density 可选参数，取值范围参考{@link ScreenDensity}，值为0表示使用当前系统dpi的密度。如果不需要此属性，请将此参数设置为0。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64Data(const NativeResourceManager *mgr, uint32_t resId,
    char **resultValue, uint64_t *resultLen, uint32_t density);

/**
 * @brief 通过指定资源名称，获取屏幕密度对应的media资源的Base64码。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param resultValue 写入resultValue的结果。
 * @param resultLen 写入resultLen的media长度。
 * @param density 可选参数，取值范围参考{@link ScreenDensity}，默认值为0，表示使用当前系统dpi的密度。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64ByName(const NativeResourceManager *mgr,
    const char *resName, char **resultValue, uint64_t *resultLen, uint32_t density = 0);

/**
 * @brief 通过指定资源名称，获取屏幕密度对应的media资源的Base64码。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param resultValue 写入resultValue的结果。
 * @param resultLen 写入resultLen的media长度。
 * @param density 可选参数，取值范围参考{@link ScreenDensity}，值为0表示使用当前系统dpi的密度。如果不需要此属性，请将此参数设置为0。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64DataByName(const NativeResourceManager *mgr,
    const char *resName, char **resultValue, uint64_t *resultLen, uint32_t density);

/**
 * @brief 通过指定资源ID，获取屏幕密度对应的media资源的内容。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param resultValue 写入resultValue的结果。
 * @param resultLen 写入resultLen的media长度。
 * @param density 可选参数，取值范围参考{@link ScreenDensity}，默认值为0，表示使用当前系统dpi的密度。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMedia(const NativeResourceManager *mgr, uint32_t resId,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density = 0);

/**
 * @brief 通过指定资源ID，获取屏幕密度对应的media资源的内容。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param resultValue 写入resultValue的结果。
 * @param resultLen 写入resultLen的media长度。
 * @param density 可选参数，取值范围参考{@link ScreenDensity}，值为0表示使用当前系统dpi的密度。如果不需要此属性，请将此参数设置为0。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaData(const NativeResourceManager *mgr, uint32_t resId,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density);

/**
 * @brief 通过指定资源名称，获取屏幕密度对应的media资源的内容。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param resultValue 写入resultValue的结果。
 * @param resultLen 写入resultLen的media长度。
 * @param density 可选参数，取值范围参考{@link ScreenDensity}，默认值为0，表示使用当前系统dpi的密度。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaByName(const NativeResourceManager *mgr, const char *resName,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density = 0);

/**
 * @brief 通过指定资源名称，获取屏幕密度对应的media资源的内容。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param resultValue 写入resultValue的结果。
 * @param resultLen 写入resultLen的media长度。
 * @param density 可选参数，取值范围参考{@link ScreenDensity}，值为0表示使用当前系统dpi的密度。如果不需要此属性，请将此参数设置为0。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaDataByName(const NativeResourceManager *mgr, const char *resName,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density);

/**
 * @brief 通过指定资源Id，获取屏幕密度对应的图标资源的DrawableDescriptor。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId Indicates the resource ID.
 * @param drawableDescriptor 写入drawableDescriptor的结果。
 * @param density 可选参数，取值范围参考{@link ScreenDensity}，默认值为0，表示使用当前系统dpi的密度。
 * @param type 可选参数，表示图标类型，0表示自身图标，1表示主题图标。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptor(const NativeResourceManager *mgr,
    uint32_t resId, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density = 0, uint32_t type = 0);

/**
 * @brief 通过指定资源Id，获取屏幕密度对应的图标资源的DrawableDescriptor。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param drawableDescriptor 写入drawableDescriptor的结果。
 * @param density 可选参数，取值范围参考{@link ScreenDensity}，值为0表示使用当前系统dpi的密度。如果不需要此属性，请将此参数设置为0。
 * @param type 可选参数，表示图标类型，0表示自身图标，1表示主题图标。如果该属性不是必需的，请将该参数设为0。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptorData(const NativeResourceManager *mgr,
    uint32_t resId, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density, uint32_t type);

/**
 * @brief 通过指定资源名称，获取屏幕密度对应的图标资源的DrawableDescriptor。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param drawableDescriptor 写入drawableDescriptor的结果。
 * @param density 可选参数，取值范围参考{@link ScreenDensity}，默认值为0，表示使用当前系统dpi的密度。
 * @param type 可选参数，表示图标类型，0表示自身图标，1表示主题图标，2表示动态图标。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptorByName(const NativeResourceManager *mgr,
    const char *resName, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density = 0, uint32_t type = 0);

/**
 * @brief 通过指定资源名称，获取屏幕密度对应的图标资源的DrawableDescriptor。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param drawableDescriptor 写入drawableDescriptor的结果。
 * @param density 可选参数，取值范围参考{@link ScreenDensity}，值为0表示使用当前系统dpi的密度。如果不需要此属性，请将此参数设置为0。
 * @param type 可选参数，表示图标类型，0表示自身图标，1表示主题图标。如果该属性不是必需的，请将该参数设为0。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptorDataByName(const NativeResourceManager *mgr,
    const char *resName, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density, uint32_t type);

/**
 * @brief 通过指定资源ID，获取对应的symbol资源。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param resultValue 写入resultValue的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetSymbol(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t *resultValue);

/**
 * @brief 通过指定资源名称，获取对应的symbol资源。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param resultValue 写入resultValue的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetSymbolByName(const NativeResourceManager *mgr, const char *resName,
    uint32_t *resultValue);

/**
 * @brief 获取语言列表。使用此接口后，需要调用OH_ResourceManager_ReleaseStringArray()方法来释放locales的内存。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resultValue 写入resultValue的结果。
 * @param resultLen 写入resultLen的locales长度。
 * @param includeSystem 是否包含系统资源，默认值为false，当只有系统资源查询locales列表时它不起作用。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetLocales(const NativeResourceManager *mgr, char ***resultValue,
    uint32_t *resultLen, bool includeSystem = false);

/**
 * @brief 获取语言列表。使用此接口后，需要调用OH_ResourceManager_ReleaseStringArray()方法来释放locales的内存。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resultValue 写入resultValue的结果。
 * @param resultLen 写入resultLen的locales长度。
 * @param includeSystem 是否包含系统资源，如果不需要此属性，请将此参数设置为 false。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetLocalesData(const NativeResourceManager *mgr, char ***resultValue,
    uint32_t *resultLen, bool includeSystem);

/**
 * @brief 获取设备配置。使用此接口后，需要调用{@link OH_ResourceManager_ReleaseConfiguration}方法来释放内存。
 * 如果使用malloc创建ResourceManager_Configuration对象，还需要调用free()方法来释放它。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param configuration 写入获取的设备配置。其中configuration.screenDensity的返回值为设备DPI除以160取整后的值。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_SYSTEM_RES_MANAGER_GET_FAILED} 9001009 - 无法访问系统资源。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 * @deprecated since 20
 * @useinstead OH_ResourceManager_GetResourceConfiguration
 */
ResourceManager_ErrorCode OH_ResourceManager_GetConfiguration(const NativeResourceManager *mgr,
    ResourceManager_Configuration *configuration);

/**
 * @brief 获取设备配置。使用此接口后，需要调用{@link OH_ResourceManager_ReleaseConfiguration}方法来释放内存。
 * 如果使用malloc创建ResourceManager_Configuration对象，还需要调用free()方法来释放它。
 *
 * @param {NativeResourceManager} mgr Indicates the pointer to {@link NativeResourceManager}
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param {ResourceManager_Configuration} configuration the result write to ResourceManager_Configuration.
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_SYSTEM_RES_MANAGER_GET_FAILED} 9001009 - 无法访问系统资源。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 20
 */
ResourceManager_ErrorCode OH_ResourceManager_GetResourceConfiguration(const NativeResourceManager *mgr,
    ResourceManager_Configuration *configuration);

/**
 * @brief 释放{@link OH_ResourceManager_GetConfiguration}和{@link OH_ResourceManager_GetResourceConfiguration}方法申请的内存。
 *
 * @param configuration 需要释放内存的configuration对象。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_ReleaseConfiguration(ResourceManager_Configuration *configuration);

/**
 * @brief 通过指定资源ID，获取对应的string资源。获取普通string资源使用OH_ResourceManager_GetString(mgr, resId, resultValue)接口。获取带有%d、%s、%
 * f占位符的格式化资源使用OH_ResourceManager_GetString(mgr, resId, resultValue, 10, "format", 10.10)接口。使用此接口后，需要调用free()
 * 方法来释放字符串的内存。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param resultValue 写入resultValue的结果。
 * @param { const char* | int | float } args - Indicates the formatting string resource parameters.
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetString(const NativeResourceManager *mgr, uint32_t resId,
    char **resultValue, ...);

/**
 * @brief 通过指定资源名称，获取对应的string资源。获取普通string资源使用OH_ResourceManager_GetString(mgr, resName, resultValue)接口。获取带有%d、%s、%
 * f占位符的格式化资源使用OH_ResourceManager_GetString(mgr, resName, resultValue, 10, "format", 10.10)接口。使用此接口后，需要调用free()
 * 方法来释放字符串的内存。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param resultValue 写入resultValue的结果。
 * @param { const char* | int | float } args - Indicates the formatting string resource parameters.
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetStringByName(const NativeResourceManager *mgr, const char *resName,
    char **resultValue, ...);

/**
 * @brief 通过指定资源ID，获取字符串数组。使用此接口后，需要调用OH_ResourceManager_ReleaseStringArray()接口来释放字符串数组内存。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param resultValue 写入resultValue的结果。
 * @param resultLen 写入resultLen的StringArray长度。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetStringArray(const NativeResourceManager *mgr, uint32_t resId,
    char ***resultValue, uint32_t *resultLen);

/**
 * @brief 通过指定资源名称，获取字符串数组。使用此接口后，需要调用OH_ResourceManager_ReleaseStringArray()接口来释放字符串数组内存。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param resultValue 写入resultValue的结果。
 * @param resultLen 写入resultLen的StringArray长度。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetStringArrayByName(const NativeResourceManager *mgr,
    const char *resName, char ***resultValue, uint32_t *resultLen);

/**
 * @brief 释放字符串数组内存。
 *
 * @param resValue 需要释放的字符串数组。
 * @param len 字符串数组长度。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_ReleaseStringArray(char ***resValue, uint32_t len);

/**
 * @brief 通过指定资源ID，获取对应的单复数字符串。使用此接口后，需要调用free()方法来释放字符串的内存。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param num 数量值。
 * @param resultValue 写入resultValue的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 * @deprecated since 16
 * @useinstead OH_ResourceManager_GetIntPluralString
 */
ResourceManager_ErrorCode OH_ResourceManager_GetPluralString(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t num, char **resultValue);

/**
 * @brief 通过指定资源名称，获取对应的单复数字符串。使用此接口后，需要调用free()方法来释放字符串的内存。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param num 数量值。
 * @param resultValue 写入resultValue的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 12
 * @deprecated since 16
 * @useinstead OH_ResourceManager_GetIntPluralStringByName
 */
ResourceManager_ErrorCode OH_ResourceManager_GetPluralStringByName(const NativeResourceManager *mgr,
    const char *resName, uint32_t num, char **resultValue);

/**
 * @brief 通过指定资源ID，获取对应的单复数字符串。使用此接口后，需要调用free()方法来释放字符串的内存。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param num 数量值（整数）。根据当前语言的复数规则获取该数量值对应的字符串数字。
 * @param resultValue 写入resultValue的结果。
 * @param { const char* | int | float } args - Indicates the formatting string resource parameters.
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetIntPluralString(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t num, char **resultValue, ...);

/**
 * @brief 通过指定资源名称，获取对应的单复数字符串。使用此接口后，需要调用free()方法来释放字符串的内存。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param num 数量值（整数）。根据当前语言的复数规则获取该数量值对应的字符串数字。
 * @param resultValue 写入resultValue的结果。
 * @param { const char* | int | float } args - Indicates the formatting string resource parameters.
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetIntPluralStringByName(const NativeResourceManager *mgr,
    const char *resName, uint32_t num, char **resultValue, ...);

/**
 * @brief 通过指定资源ID，获取对应的单复数字符串。使用此接口后，需要调用free()方法来释放字符串的内存。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param num 数量值（浮点数）。根据当前语言的复数规则获取该数量值对应的字符串数字。
 * @param resultValue 写入resultValue的结果。
 * @param { const char* | int | float } args - Indicates the formatting string resource parameters.
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDoublePluralString(const NativeResourceManager *mgr, uint32_t resId,
    double num, char **resultValue, ...);

/**
 * @brief 通过指定资源名称，获取对应的单复数字符串。使用此接口后，需要调用free()方法来释放字符串的内存。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param num 数量值（浮点数）。根据当前语言的复数规则获取该数量值对应的字符串数字。
 * @param resultValue 写入resultValue的结果。
 * @param { const char* | int | float } args - Indicates the formatting string resource parameters.
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 *     <br>{@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - 内存溢出。
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDoublePluralStringByName(const NativeResourceManager *mgr,
    const char *resName, double num, char **resultValue, ...);

/**
 * @brief 通过指定资源ID，获取对应的颜色值。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param resultValue 写入resultValue的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetColor(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t *resultValue);

/**
 * @brief 通过指定资源ID，获取对应的颜色值。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param resultValue 写入resultValue的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetColorByName(const NativeResourceManager *mgr, const char *resName,
    uint32_t *resultValue);

/**
 * @brief 通过指定资源ID，获取对应的int值。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param resultValue 写入resultValue的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetInt(const NativeResourceManager *mgr, uint32_t resId,
    int *resultValue);

/**
 * @brief 通过指定资源名称，获取对应的int值。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param resultValue 写入resultValue的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetIntByName(const NativeResourceManager *mgr, const char *resName,
    int *resultValue);

/**
 * @brief 通过指定资源ID，获取对应的float值。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param resultValue 写入resultValue的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetFloat(const NativeResourceManager *mgr, uint32_t resId,
    float *resultValue);

/**
 * @brief 通过指定资源名称，获取对应的float值。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param resultValue 写入resultValue的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetFloatByName(const NativeResourceManager *mgr, const char *resName,
    float *resultValue);

/**
 * @brief 通过指定资源ID，获取对应的bool值。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resId 资源ID。
 * @param resultValue 写入resultValue的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - 无效的资源ID。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - 没有根据资源ID找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetBool(const NativeResourceManager *mgr, uint32_t resId,
    bool *resultValue);

/**
 * @brief 通过指定资源名称，获取对应的bool值。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param resName 资源名称。
 * @param resultValue 写入resultValue的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - 无效的资源名称。
 *     <br>{@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - 没有根据资源名称找到匹配的资源。
 *     <br>{@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - 资源被循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetBoolByName(const NativeResourceManager *mgr, const char *resName,
    bool *resultValue);

/**
 * @brief 在应用程序运行时添加overlay资源。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param path 资源路径。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_OVERLAY_RES_PATH_INVALID} 9001010 - 无效的资源路径.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_AddResource(const NativeResourceManager *mgr, const char *path);

/**
 * @brief 在应用程序运行时删除overlay资源。
 *
 * @param mgr 指向{@link NativeResourceManager}的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param path 资源路径。
 * @return {@link SUCCESS} 0 - 成功。
 *     <br>{@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - 输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>{@link ERROR_CODE_OVERLAY_RES_PATH_INVALID} 9001010 - 无效的资源路径.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_RemoveResource(const NativeResourceManager *mgr, const char *path);
#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_OH_RESMGR_H

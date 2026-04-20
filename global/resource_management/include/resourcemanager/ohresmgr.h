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
 * @brief Provides native APIs for obtaining resources.
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
 * @brief Obtains the Base64 code of the image resource.
 *
 * Obtains the Base64 code of the image resource corresponding to the specified resource ID.
 *
 * @param mgr Indicates the pointer to {@link NativeResourceManager}
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Indicates the resource ID.
 * @param resultValue the result write to resultValue.
 * @param resultLen the media length write to resultLen.
 * @param density The optional parameter ScreenDensity{@link ScreenDensity}, A value of 0 means
 * to use the density of current system dpi.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter invalid. Possible causes:
 *         1.Incorrect parameter types; 2.Parameter verification failed.
           {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - Invalid resource ID.
           {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
           {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - Out of memory.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64(const NativeResourceManager *mgr, uint32_t resId,
    char **resultValue, uint64_t *resultLen, uint32_t density = 0);

/**
 * @brief Obtains the Base64 code of the image resource.
 *
 * Obtains the Base64 code of the image resource corresponding to the specified resource ID.
 *
 * @param mgr Indicates the pointer to {@link NativeResourceManager}
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Indicates the resource ID.
 * @param resultValue the result write to resultValue.
 * @param resultLen the media length write to resultLen.
 * @param density The optional parameter ScreenDensity{@link ScreenDensity}, A value of 0 means
 * to use the density of current system dpi. If this attribute is not required, set this parameter to 0.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter invalid. Possible causes:
 *         1.Incorrect parameter types; 2.Parameter verification failed.
           {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - Invalid resource ID.
           {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
           {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - Out of memory.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64Data(const NativeResourceManager *mgr, uint32_t resId,
    char **resultValue, uint64_t *resultLen, uint32_t density);

/**
 * @brief Obtains the Base64 code of the image resource.
 *
 * Obtains the Base64 code of the image resource corresponding to the specified resource name.
 *
 * @param mgr Indicates the pointer to {@link NativeResourceManager}
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Indicates the resource name.
 * @param resultValue the result write to resultValue.
 * @param resultLen the media length write to resultLen.
 * @param density The optional parameter ScreenDensity{@link ScreenDensity}, A value of 0 means
 * to use the density of current system dpi.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter invalid. Possible causes:
 *         1.Incorrect parameter types; 2.Parameter verification failed.
           {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - Invalid resource name.
           {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
           {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - Out of memory.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64ByName(const NativeResourceManager *mgr,
    const char *resName, char **resultValue, uint64_t *resultLen, uint32_t density = 0);

/**
 * @brief Obtains the Base64 code of the image resource.
 *
 * Obtains the Base64 code of the image resource corresponding to the specified resource name.
 *
 * @param mgr Indicates the pointer to {@link NativeResourceManager}
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Indicates the resource name.
 * @param resultValue the result write to resultValue.
 * @param resultLen the media length write to resultLen.
 * @param density The optional parameter ScreenDensity{@link ScreenDensity}, A value of 0 means
 * to use the density of current system dpi. If this attribute is not required, set this parameter to 0.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter invalid. Possible causes:
 *         1.Incorrect parameter types; 2.Parameter verification failed.
           {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - Invalid resource name.
           {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
           {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - Out of memory.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64DataByName(const NativeResourceManager *mgr,
    const char *resName, char **resultValue, uint64_t *resultLen, uint32_t density);

/**
 * @brief Obtains the content of the image resource.
 *
 * Obtains the content of the specified screen density media file corresponding to a specified resource ID.
 *
 * @param mgr Indicates the pointer to {@link NativeResourceManager}
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Indicates the resource ID.
 * @param resultValue the result write to resultValue.
 * @param resultLen the media length write to resultLen.
 * @param density The optional parameter ScreenDensity{@link ScreenDensity}, A value of 0 means
 * to use the density of current system dpi.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter invalid. Possible causes:
 *         1.Incorrect parameter types; 2.Parameter verification failed.
           {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - Invalid resource ID.
           {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
           {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - Out of memory.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMedia(const NativeResourceManager *mgr, uint32_t resId,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density = 0);

/**
 * @brief Obtains the content of the image resource.
 *
 * Obtains the content of the specified screen density media file corresponding to a specified resource ID.
 *
 * @param mgr Indicates the pointer to {@link NativeResourceManager}
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Indicates the resource ID.
 * @param resultValue the result write to resultValue.
 * @param resultLen the media length write to resultLen.
 * @param density The optional parameter ScreenDensity{@link ScreenDensity}, A value of 0 means
 * to use the density of current system dpi. If this attribute is not required, set this parameter to 0.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter invalid. Possible causes:
 *         1.Incorrect parameter types; 2.Parameter verification failed.
           {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - Invalid resource ID.
           {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
           {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - Out of memory.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaData(const NativeResourceManager *mgr, uint32_t resId,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density);

/**
 * @brief Obtains the content of the image resource.
 *
 * Obtains the content of the specified screen density media file corresponding to a specified resource name.
 *
 * @param mgr Indicates the pointer to {@link NativeResourceManager}
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Indicates the resource name.
 * @param resultValue the result write to resultValue.
 * @param resultLen the media length write to resultLen.
 * @param density The optional parameter ScreenDensity{@link ScreenDensity}, A value of 0 means
 * to use the density of current system dpi.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter invalid. Possible causes:
 *         1.Incorrect parameter types; 2.Parameter verification failed.
           {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - Invalid resource name.
           {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
           {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - Out of memory.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaByName(const NativeResourceManager *mgr, const char *resName,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density = 0);

/**
 * @brief Obtains the content of the image resource.
 *
 * Obtains the content of the specified screen density media file corresponding to a specified resource name.
 *
 * @param mgr Indicates the pointer to {@link NativeResourceManager}
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Indicates the resource name.
 * @param resultValue the result write to resultValue.
 * @param resultLen the media length write to resultLen.
 * @param density The optional parameter ScreenDensity{@link ScreenDensity}, A value of 0 means
 * to use the density of current system dpi. If this attribute is not required, set this parameter to 0.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter invalid. Possible causes:
 *         1.Incorrect parameter types; 2.Parameter verification failed.
           {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - Invalid resource name.
           {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
           {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - Out of memory.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaDataByName(const NativeResourceManager *mgr, const char *resName,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density);

/**
 * @brief Obtains the DrawableDescriptor of the media file.
 *
 * Obtains the DrawableDescriptor of the media file corresponding to a specified resource ID.
 *
 * @param mgr Indicates the pointer to {@link NativeResourceManager}
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Indicates the resource ID.
 * @param drawableDescriptor the result write to drawableDescriptor.
 * @param density The optional parameter ScreenDensity{@link ScreenDensity}, A value of 0 means
 * to use the density of current system dpi.
 * @param type The optional parameter means the media type, 0 means the normal media, 1 means the the theme style media.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter invalid. Possible causes:
 *         1.Incorrect parameter types; 2.Parameter verification failed.
           {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - Invalid resource ID.
           {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptor(const NativeResourceManager *mgr,
    uint32_t resId, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density = 0, uint32_t type = 0);

/**
 * @brief Obtains the DrawableDescriptor of the media file.
 *
 * Obtains the DrawableDescriptor of the media file corresponding to a specified resource ID.
 *
 * @param mgr Indicates the pointer to {@link NativeResourceManager}
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Indicates the resource ID.
 * @param drawableDescriptor the result write to drawableDescriptor.
 * @param density The optional parameter ScreenDensity{@link ScreenDensity}, A value of 0 means
 * to use the density of current system dpi. If this attribute is not required, set this parameter to 0.
 * @param type The optional parameter means the media type, 0 means the normal media, 1 means the the theme style media.
 * If this attribute is not required, set this parameter to 0.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter invalid. Possible causes:
 *         1.Incorrect parameter types; 2.Parameter verification failed.
           {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - Invalid resource ID.
           {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptorData(const NativeResourceManager *mgr,
    uint32_t resId, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density, uint32_t type);

/**
 * @brief Obtains the DrawableDescriptor of the media file.
 *
 * Obtains the DrawableDescriptor of the media file corresponding to a specified resource name.
 * @param mgr Indicates the pointer to {@link NativeResourceManager}
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Indicates the resource name.
 * @param drawableDescriptor the result write to drawableDescriptor.
 * @param density The optional parameter ScreenDensity{@link ScreenDensity}, A value of 0 means
 * to use the density of current system dpi.
 * @param type The optional parameter means the media type, 0 means the normal media, 1 means the the theme style media,
 * 2 means the theme dynamic media.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter invalid. Possible causes:
 *         1.Incorrect parameter types; 2.Parameter verification failed.
           {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - Invalid resource name.
           {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptorByName(const NativeResourceManager *mgr,
    const char *resName, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density = 0, uint32_t type = 0);

/**
 * @brief Obtains the DrawableDescriptor of the media file.
 *
 * Obtains the DrawableDescriptor of the media file corresponding to a specified resource name.
 * @param mgr Indicates the pointer to {@link NativeResourceManager}
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Indicates the resource name.
 * @param drawableDescriptor the result write to drawableDescriptor.
 * @param density The optional parameter ScreenDensity{@link ScreenDensity}, A value of 0 means
 * to use the density of current system dpi. If this attribute is not required, set this parameter to 0.
 * @param type The optional parameter means the media type, 0 means the normal media, 1 means the the theme style media,
 * 2 means the theme dynamic media. If this attribute is not required, set this parameter to 0.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter invalid. Possible causes:
 *         1.Incorrect parameter types; 2.Parameter verification failed.
           {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - Invalid resource name.
           {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptorDataByName(const NativeResourceManager *mgr,
    const char *resName, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density, uint32_t type);

/**
 * @brief Obtains a **symbol** resource based on the specified resource ID.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Resource ID.
 * @param resultValue Result of writing **resultValue**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - The resource ID is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetSymbol(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t *resultValue);

/**
 * @brief Obtains a **symbol** resource based on the specified resource name.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Resource name.
 * @param resultValue Result of writing **resultValue**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - The resource name is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetSymbolByName(const NativeResourceManager *mgr, const char *resName,
    uint32_t *resultValue);

/**
 * @brief Obtains the language list. After using this API, you need to call **OH_ResourceManager_ReleaseStringArray()**
 * to release the memory of **localinfo**.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resultValue Result of writing **resultValue**.
 * @param resultLen Length of locales written to **resultLen**.
 * @param includeSystem Whether system resources are included. The default value is **false**. This parameter does not
 * take effect if only system resources are involved when you query the list of locales.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetLocales(const NativeResourceManager *mgr, char ***resultValue,
    uint32_t *resultLen, bool includeSystem = false);

/**
 * @brief Obtains the language list. After using this API, you need to call **OH_ResourceManager_ReleaseStringArray()**
 * to release the memory of **localinfo**.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resultValue Result of writing **resultValue**.
 * @param resultLen Length of locales written to **resultLen**.
 * @param includeSystem Whether system resources are included. If this parameter is not required, set it to **false**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetLocalesData(const NativeResourceManager *mgr, char ***resultValue,
    uint32_t *resultLen, bool includeSystem);

/**
 * @brief Obtains the device configuration. After this API is used, call {@link OH_ResourceManager_ReleaseConfiguration}
 * to release the memory. If the **ResourceManager_Configuration** object is created by using malloc, call **free()**
 * to release the object.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param configuration Device configuration. The return value of **configuration.screenDensity** is the rounded value
 * of the device's DPI divided by 160.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_SYSTEM_RES_MANAGER_GET_FAILED} 9001009 - The attempt to access system resources fails.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 12
 * @deprecated since 20
 * @useinstead OH_ResourceManager_GetResourceConfiguration
 */
ResourceManager_ErrorCode OH_ResourceManager_GetConfiguration(const NativeResourceManager *mgr,
    ResourceManager_Configuration *configuration);

/**
 * @brief Obtains the device configuration. After this API is used, call {@link OH_ResourceManager_ReleaseConfiguration}
 * to release the memory. If the **ResourceManager_Configuration** object is created by using malloc, call **free()**
 * to release the object.
 *
 * @param {NativeResourceManager} mgr Indicates the pointer to {@link NativeResourceManager}
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param {ResourceManager_Configuration} configuration the result write to ResourceManager_Configuration.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_SYSTEM_RES_MANAGER_GET_FAILED} 9001009 - The attempt to access system resources fails.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 20
 */
ResourceManager_ErrorCode OH_ResourceManager_GetResourceConfiguration(const NativeResourceManager *mgr,
    ResourceManager_Configuration *configuration);

/**
 * @brief Releases the memory requested by using the {@link OH_ResourceManager_GetConfiguration} and
 * {@link OH_ResourceManager_GetResourceConfiguration} methods.
 *
 * @param configuration Configuration object whose memory needs to be released.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_ReleaseConfiguration(ResourceManager_Configuration *configuration);

/**
 * @brief Obtains a **string** resource based on the specified resource ID. The obtain common string resources, use **
 * OH_ResourceManager_GetString(mgr, resId, resultValue)**. The obtain formatted string resources with the **%d**, **%s*
 * *, and **%f** placeholders, use **OH_ResourceManager_GetString(mgr, resId, resultValue, 10, "format", 10.10)**.
 * After using this API, you need to call **free()** to release the memory of the strings.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Resource ID.
 * @param resultValue Result of writing **resultValue**.
 * @param { const char* | int | float } args - Indicates the formatting string resource parameters.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - The resource ID is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetString(const NativeResourceManager *mgr, uint32_t resId,
    char **resultValue, ...);

/**
 * @brief Obtains a **string** resource based on the specified resource name. The obtain common string resources, use **
 * OH_ResourceManager_GetString(mgr, resName, resultValue)**. The obtain formatted string resources with the **%d**, **%
 * s**, and **%f** placeholders, use **OH_ResourceManager_GetString(mgr, resName, resultValue, 10, "format", 10.10)**.
 * After using this API, you need to call **free()** to release the memory of the strings.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Resource name.
 * @param resultValue Result of writing **resultValue**.
 * @param { const char* | int | float } args - Indicates the formatting string resource parameters.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - The resource name is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetStringByName(const NativeResourceManager *mgr, const char *resName,
    char **resultValue, ...);

/**
 * @brief Obtains a string array based on the specified resource ID. After using this API, you need to call **
 * OH_ResourceManager_ReleaseStringArray()** to release the memory of the string array.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Resource ID.
 * @param resultValue Result of writing **resultValue**.
 * @param resultLen Length of **StringArray** written to **resultLen**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - The resource ID is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetStringArray(const NativeResourceManager *mgr, uint32_t resId,
    char ***resultValue, uint32_t *resultLen);

/**
 * @brief Obtains a string array based on the specified resource name. After using this API, you need to call **
 * OH_ResourceManager_ReleaseStringArray()** to release the memory of the string array.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Resource name.
 * @param resultValue Result of writing **resultValue**.
 * @param resultLen Length of **StringArray** written to **resultLen**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - The resource name is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetStringArrayByName(const NativeResourceManager *mgr,
    const char *resName, char ***resultValue, uint32_t *resultLen);

/**
 * @brief Releases the memory of the string array.
 *
 * @param resValue String array whose memory needs to be released.
 * @param len Length of the string array.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_ReleaseStringArray(char ***resValue, uint32_t len);

/**
 * @brief Obtains singular and plural strings based on the specified resource ID. After using this API, you need to
 * call **free()** to release the memory of the strings.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Resource ID.
 * @param num Number.
 * @param resultValue Result of writing **resultValue**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - The resource ID is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 12
 * @deprecated since 16
 * @useinstead OH_ResourceManager_GetIntPluralString
 */
ResourceManager_ErrorCode OH_ResourceManager_GetPluralString(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t num, char **resultValue);

/**
 * @brief Obtains singular and plural strings based on the specified resource name. After using this API, you need to
 * call **free()** to release the memory of the strings.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Resource name.
 * @param num Number.
 * @param resultValue Result of writing **resultValue**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - The resource name is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 12
 * @deprecated since 16
 * @useinstead OH_ResourceManager_GetIntPluralStringByName
 */
ResourceManager_ErrorCode OH_ResourceManager_GetPluralStringByName(const NativeResourceManager *mgr,
    const char *resName, uint32_t num, char **resultValue);

/**
 * @brief Obtains singular and plural strings based on the specified resource ID. After using this API, you need to
 * call **free()** to release the memory of the strings.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Resource ID.
 * @param num Quantity value (an integer number). Its string representation is obtained based on the current language's
 * plural rules.
 * @param resultValue Result of writing **resultValue**.
 * @param { const char* | int | float } args - Indicates the formatting string resource parameters.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - The resource ID is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetIntPluralString(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t num, char **resultValue, ...);

/**
 * @brief Obtains singular and plural strings based on the specified resource name. After using this API, you need to
 * call **free()** to release the memory of the strings.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Resource name.
 * @param num Quantity value (an integer number). Its string representation is obtained based on the current language's
 * plural rules.
 * @param resultValue Result of writing **resultValue**.
 * @param { const char* | int | float } args - Indicates the formatting string resource parameters.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - The resource name is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetIntPluralStringByName(const NativeResourceManager *mgr,
    const char *resName, uint32_t num, char **resultValue, ...);

/**
 * @brief Obtains singular and plural strings based on the specified resource ID. After using this API, you need to
 * call **free()** to release the memory of the strings.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Resource ID.
 * @param num Quantity value (a floating point number). Its string representation is obtained based on the current
 * language's plural rules.
 * @param resultValue Result of writing **resultValue**.
 * @param { const char* | int | float } args - Indicates the formatting string resource parameters.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - The resource ID is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDoublePluralString(const NativeResourceManager *mgr, uint32_t resId,
    double num, char **resultValue, ...);

/**
 * @brief Obtains singular and plural strings based on the specified resource name. After using this API, you need to
 * call **free()** to release the memory of the strings.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Resource name.
 * @param num Quantity value (a floating point number). Its string representation is obtained based on the current
 * language's plural rules.
 * @param resultValue Result of writing **resultValue**.
 * @param { const char* | int | float } args - Indicates the formatting string resource parameters.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - The resource name is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * {@link ERROR_CODE_OUT_OF_MEMORY} 9001100 - A memory overflow occurs.
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDoublePluralStringByName(const NativeResourceManager *mgr,
    const char *resName, double num, char **resultValue, ...);

/**
 * @brief Obtains a color value based on the specified resource ID.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Resource ID.
 * @param resultValue Result of writing **resultValue**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - The resource ID is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetColor(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t *resultValue);

/**
 * @brief Obtains a color value based on the specified resource ID.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Resource name.
 * @param resultValue Result of writing **resultValue**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - The resource name is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetColorByName(const NativeResourceManager *mgr, const char *resName,
    uint32_t *resultValue);

/**
 * @brief Obtains an int value based on the specified resource ID.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Resource ID.
 * @param resultValue Result of writing **resultValue**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - The resource ID is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetInt(const NativeResourceManager *mgr, uint32_t resId,
    int *resultValue);

/**
 * @brief Obtains an int value based on the specified resource name.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Resource name.
 * @param resultValue Result of writing **resultValue**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - The resource name is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetIntByName(const NativeResourceManager *mgr, const char *resName,
    int *resultValue);

/**
 * @brief Obtains a float value based on the specified resource ID.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Resource ID.
 * @param resultValue Result of writing **resultValue**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - The resource ID is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetFloat(const NativeResourceManager *mgr, uint32_t resId,
    float *resultValue);

/**
 * @brief Obtains a float value based on the specified resource name.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Resource name.
 * @param resultValue Result of writing **resultValue**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - The resource name is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetFloatByName(const NativeResourceManager *mgr, const char *resName,
    float *resultValue);

/**
 * @brief Obtains a bool value based on the specified resource ID.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Resource ID.
 * @param resultValue Result of writing **resultValue**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_ID_NOT_FOUND} 9001001 - The resource ID is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_ID} 9001002 - No matching resource is found based on the resource ID.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetBool(const NativeResourceManager *mgr, uint32_t resId,
    bool *resultValue);

/**
 * @brief Obtains a bool value based on the specified resource name.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Resource name.
 * @param resultValue Result of writing **resultValue**.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_RES_NAME_NOT_FOUND} 9001003 - The resource name is invalid.
 * {@link ERROR_CODE_RES_NOT_FOUND_BY_NAME} 9001004 - No matching resource is found based on the resource name.
 * {@link ERROR_CODE_RES_REF_TOO_MUCH} 9001006 - The resource is cyclically referenced.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetBoolByName(const NativeResourceManager *mgr, const char *resName,
    bool *resultValue);

/**
 * @brief Adds overlay resources when an application is running.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param path Resource path.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_OVERLAY_RES_PATH_INVALID} 9001010 - The resource path is invalid.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_AddResource(const NativeResourceManager *mgr, const char *path);

/**
 * @brief Removes overlay resources when an application is running.
 *
 * @param mgr Pointer to {@link NativeResourceManager}. It is obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param path Resource path.
 * @return {@link SUCCESS} 0 - The operation is successful.
 * {@link ERROR_CODE_INVALID_INPUT_PARAMETER} 401 - The input parameter is invalid. Possible causes: 1. The parameter
 * type is incorrect. 2. Parameter verification failed.
 * {@link ERROR_CODE_OVERLAY_RES_PATH_INVALID} 9001010 - The resource path is invalid.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_RemoveResource(const NativeResourceManager *mgr, const char *path);
#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_OH_RESMGR_H
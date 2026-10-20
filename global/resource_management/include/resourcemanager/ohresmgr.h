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
 * @brief Through the `resourcemanager` module, you can obtain application resources or system resources by resource ID
 * or resource name at the Native layer, enabling resource adaptation for multilingual, multi-device, and multi-screen-
 * density scenarios. Specifically:
 * <br>- Obtaining basic type resources: Obtain basic type resources such as color values (in ARGB format), integers,
 * floating-point numbers, and boolean values.
 * <br>- Obtaining string resources: Obtain plain strings, formatted strings (supporting %d, %s, and %f placeholders),
 * string arrays, and plural strings.
 * <br>- Obtaining media resources: Obtain raw binary data or Base64 encoding of media resources.
 * <br>- Resource overlay: Dynamically load and remove overlay resources at runtime to implement theme switching or
 * resource overlay.
 * <br>This module depends on the `rawfile` module. You must first obtain a **NativeResourceManager** object through
 * the `rawfile` module.
 *
 * @since 12
 */
/**
 * @file ohresmgr.h
 *
 * @brief Provides the capability of obtaining resources in the resource management native layer.
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

#ifdef __cplusplus
/**
 * @brief Obtains the Base64-encoded string of the media resource by the specified resource ID and screen density.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param resultValue Output parameter. Pointer to the Base64-encoded string, which is allocated by **malloc()** and
 *     must be released via **free()** after use.
 * @param resultLen Output parameter. Length of the Base64 string, in bytes.
 * @param density Input parameter, which is optional. Screen density. For details about the value range, see
 *     {@link ScreenDensity}. The default value is **0**, indicating that the current system screen density is used.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64(const NativeResourceManager *mgr, uint32_t resId,
    char **resultValue, uint64_t *resultLen, uint32_t density = 0);
#endif

/**
 * @brief Obtains the Base64-encoded string of the media resource by the specified resource ID and screen density.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param resultValue Output parameter. Pointer to the Base64-encoded string, which is allocated by **malloc()** and
 *     must be released via **free()** after use.
 * @param resultLen Output parameter. Length of the Base64 string, in bytes.
 * @param density Input parameter. Screen density. For details about the value range, see {@link ScreenDensity}. The
 *     value **0** indicates that the current system screen density is used. If no specific density is required, set
 *     this parameter to **0**.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64Data(const NativeResourceManager *mgr, uint32_t resId,
    char **resultValue, uint64_t *resultLen, uint32_t density);

#ifdef __cplusplus
/**
 * @brief Obtains the Base64-encoded string of the media resource by the specified resource name and screen density.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param resultValue Output parameter. Pointer to the Base64-encoded string, which is allocated by **malloc()** and
 *     must be released via **free()** after use.
 * @param resultLen Output parameter. Length of the Base64 string, in bytes.
 * @param density Input parameter, which is optional. Screen density. For details about the value range, see
 *     {@link ScreenDensity}. The default value is **0**, indicating that the current system screen density is used.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64ByName(const NativeResourceManager *mgr,
    const char *resName, char **resultValue, uint64_t *resultLen, uint32_t density = 0);
#endif

/**
 * @brief Obtains the Base64-encoded string of the media resource by the specified resource name and screen density.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param resultValue Output parameter. Pointer to the Base64-encoded string, which is allocated by **malloc()** and
 *     must be released via **free()** after use.
 * @param resultLen Output parameter. Length of the Base64 string, in bytes.
 * @param density Input parameter. Screen density. For details about the value range, see {@link ScreenDensity}. The
 *     value **0** indicates that the current system screen density is used. If no specific density is required, set
 *     this parameter to **0**.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64DataByName(const NativeResourceManager *mgr,
    const char *resName, char **resultValue, uint64_t *resultLen, uint32_t density);

#ifdef __cplusplus
/**
 * @brief Obtains the binary data of the media resource by the specified resource ID and screen density.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param resultValue Output parameter. Pointer to the media data, which is allocated by **malloc()** and must be
 *     released via **free()** after use.
 * @param resultLen Output parameter. Data length, in bytes.
 * @param density Input parameter, which is optional. Screen density. For details about the value range, see
 *     {@link ScreenDensity}. The default value is **0**, indicating that the current system screen density is used.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMedia(const NativeResourceManager *mgr, uint32_t resId,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density = 0);
#endif

/**
 * @brief Obtains the binary data of the media resource by the specified resource ID and screen density.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param resultValue Output parameter. Pointer to the media data, which is allocated by **malloc()** and must be
 *     released via **free()** after use.
 * @param resultLen Output parameter. Data length, in bytes.
 * @param density Input parameter. Screen density. For details about the value range, see {@link ScreenDensity}. The
 *     value **0** indicates that the current system screen density is used. If no specific density is required, set
 *     this parameter to **0**.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaData(const NativeResourceManager *mgr, uint32_t resId,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density);

#ifdef __cplusplus
/**
 * @brief Obtains the binary data of the media resource by the specified resource name and screen density.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param resultValue Output parameter. Pointer to the media data, which is allocated by **malloc()** and must be
 *     released via **free()** after use.
 * @param resultLen Output parameter. Data length, in bytes.
 * @param density Input parameter, which is optional. Screen density. For details about the value range, see
 *     {@link ScreenDensity}. The default value is **0**, indicating that the current system screen density is used.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaByName(const NativeResourceManager *mgr, const char *resName,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density = 0);
#endif

/**
 * @brief Obtains the binary data of the media resource by the specified resource name and screen density.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param resultValue Output parameter. Pointer to the media data, which is allocated by **malloc()** and must be
 *     released via **free()** after use.
 * @param resultLen Output parameter. Data length, in bytes.
 * @param density Input parameter. Screen density. For details about the value range, see {@link ScreenDensity}. The
 *     value **0** indicates that the current system screen density is used. If no specific density is required, set
 *     this parameter to **0**.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaDataByName(const NativeResourceManager *mgr, const char *resName,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density);

#ifdef __cplusplus
/**
 * @brief Obtains the DrawableDescriptor object of the icon resource by the specified resource ID, screen density, and
 * icon type.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param drawableDescriptor Output parameter. Pointer to the DrawableDescriptor object.
 * @param density Input parameter, which is optional. Screen density. For details about the value range, see
 *     {@link ScreenDensity}. The default value is **0**, indicating that the current system screen density is used.
 * @param type Input parameter, which is optional. Icon type. The default value is **0**.
 *     <br>**0**: application icon.
 *     <br>**1**: application theme icon.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptor(const NativeResourceManager *mgr,
    uint32_t resId, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density = 0, uint32_t type = 0);
#endif

/**
 * @brief Obtains the DrawableDescriptor object of the icon resource by the specified resource ID, screen density, and
 * icon type.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param drawableDescriptor Output parameter. Pointer to the DrawableDescriptor object.
 * @param density Input parameter. Screen density. For details about the value range, see {@link ScreenDensity}. The
 *     value **0** indicates that the current system screen density is used. If no specific density is required, set
 *     this parameter to **0**.
 * @param type Input parameter. Icon type. If no specific icon type is required, set this parameter to **0**.
 *     <br>**0**: application icon.
 *     <br>**1**: application theme icon.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptorData(const NativeResourceManager *mgr,
    uint32_t resId, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density, uint32_t type);

#ifdef __cplusplus
/**
 * @brief Obtains the DrawableDescriptor object of the icon resource by the specified resource name, screen density,
 * and icon type.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param drawableDescriptor Output parameter. Pointer to the DrawableDescriptor object.
 * @param density Input parameter, which is optional. Screen density. For details about the value range, see
 *     {@link ScreenDensity}. The default value is **0**, indicating that the current system screen density is used.
 * @param type Input parameter, which is optional. Icon type. The default value is **0**.
 *     <br>**0**: application icon.
 *     <br>**1**: application theme icon.
 *     <br>**2**: dynamic icon.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptorByName(const NativeResourceManager *mgr,
    const char *resName, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density = 0, uint32_t type = 0);
#endif

/**
 * @brief Obtains the DrawableDescriptor object of the icon resource by the specified resource name and screen density.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param drawableDescriptor Output parameter. Pointer to the DrawableDescriptor object.
 * @param density Input parameter. Screen density. For details about the value range, see {@link ScreenDensity}. The
 *     value **0** indicates that the current system screen density is used. If no specific density is required, set
 *     this parameter to **0**.
 * @param type Input parameter. Icon type. If no specific icon type is required, set this parameter to **0**.
 *     <br>**0**: application icon.
 *     <br>**1**: application theme icon.
 *     <br>**2**: dynamic icon.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptorDataByName(const NativeResourceManager *mgr,
    const char *resName, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density, uint32_t type);

/**
 * @brief Obtains the Unicode encoding of the symbol icon corresponding to the specified resource ID.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param resultValue Output parameter. Unicode encoding of the symbol icon.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetSymbol(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t *resultValue);

/**
 * @brief Obtains the Unicode encoding of the symbol icon corresponding to the specified resource name.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param resultValue Output parameter. Unicode encoding of the symbol icon.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetSymbolByName(const NativeResourceManager *mgr, const char *resName,
    uint32_t *resultValue);

#ifdef __cplusplus
/**
 * @brief Obtains the list of languages supported by an application.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resultValue Output parameter. Pointer to the language list array. The memory is allocated by this function
 *     and must be released through {@link OH_ResourceManager_ReleaseStringArray} after use.
 * @param resultLen Output parameter. Length of the language list.
 * @param includeSystem Input parameter, which is optional.This parameter indicates whether to include system resources.
 *     The value **true** indicates yes, and the value **false** indicates no. The default value is **false**.
 *     <br>When the system resource manager object is used to obtain the language list, the system resource language
 *     list is returned.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetLocales(const NativeResourceManager *mgr, char ***resultValue,
    uint32_t *resultLen, bool includeSystem = false);
#endif

/**
 * @brief Obtains the list of languages supported by an application.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resultValue Output parameter. Pointer to the language list array. The memory is allocated by this function
 *     and must be released through {@link OH_ResourceManager_ReleaseStringArray} after use.
 * @param resultLen Output parameter. Length of the language list.
 * @param includeSystem Input parameter. This parameter indicates whether to include system resources. The value
 *     **true** indicates yes, and the value **false** indicates no.
 *     <br>When the system resource manager object is used to obtain the language list, the system resource language
 *     list is returned.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetLocalesData(const NativeResourceManager *mgr, char ***resultValue,
    uint32_t *resultLen, bool includeSystem);

/**
 * @brief Obtains the configuration information of a device, such as the screen orientation, language and region,
 * device type, screen density, and color mode.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param configuration Output parameter. Device configuration information, where **screenDensity** is the device
 *     screen density (in dpi) divided by 160 and rounded to an integer.
 *     <br>The memory for the locale string in **configuration** is allocated by this function, and must be released
 *     through {@link OH_ResourceManager_ReleaseConfiguration} after use. If the memory for **configuration** is
 *     allocated by **malloc()**, it must be released via **free()**.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_SYSTEM_RES_MANAGER_GET_FAILED**: Failed to access the system resource.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 * @deprecated since 20
 * @useinstead {@link OH_ResourceManager_GetResourceConfiguration}
 */
ResourceManager_ErrorCode OH_ResourceManager_GetConfiguration(const NativeResourceManager *mgr,
    ResourceManager_Configuration *configuration);

/**
 * @brief Obtains the configuration information of a device, such as the screen orientation, language and region, device
 * type, screen density, and color mode.
 *
 * @param {NativeResourceManager} mgr Indicates the pointer to {@link NativeResourceManager}
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param {ResourceManager_Configuration} configuration the result write to ResourceManager_Configuration.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_SYSTEM_RES_MANAGER_GET_FAILED**: Failed to access the system resource.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 20
 */
ResourceManager_ErrorCode OH_ResourceManager_GetResourceConfiguration(const NativeResourceManager *mgr,
    ResourceManager_Configuration *configuration);

/**
 * @brief Releases the memory requested through the {@link OH_ResourceManager_GetConfiguration} or
 * {@link OH_ResourceManager_GetResourceConfiguration} function.
 *
 * @param configuration Input parameter. Pointer to the {@link ResourceManager_Configuration} object whose memory needs
 *     to be deallocated.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_ReleaseConfiguration(ResourceManager_Configuration *configuration);

/**
 * @brief Obtains a plain or formatted string based on the specified resource ID.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param resultValue Output parameter. Pointer to the string, which is allocated by **malloc()** and must be released
 *     via **free()** after use.
 * @param ... Input parameter, which is optional. Variable parameter list, which is used for string formatting. The
 *     following types are supported: const char*, int, and float.
 *     <br>You do not need to set this parameter when obtaining a plain string. This parameter is mandatory to obtain a
 *     formatted string. The variable parameters must be passed in the order corresponding to the placeholders in the
 *     string. The number and types of the parameters must match the placeholders in the string. For example, if the
 *     string contains three placeholders %d, %s, and %f, the API should be called as follows:
 *     **OH_ResourceManager_GetString(mgr, resId, resultValue, 10, "format", 10.10)**.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetString(const NativeResourceManager *mgr, uint32_t resId,
    char **resultValue, ...);

/**
 * @brief Obtains a plain or formatted string based on the specified resource name.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param resultValue Output parameter. Pointer to the string, which is allocated by **malloc()** and must be released
 *     via **free()** after use.
 * @param ... Input parameter, which is optional. Variable parameter list, which is used for string formatting. The
 *     following types are supported: const char*, int, and float.
 *     <br>You do not need to set this parameter when obtaining a plain string. This parameter is mandatory to obtain a
 *     formatted string. The variable parameters must be passed in the order corresponding to the placeholders in the
 *     string. The number and types of the parameters must match the placeholders in the string. For example, if the
 *     string contains three placeholders %d, %s, and %f, the API should be called as follows:
 *     **OH_ResourceManager_GetStringByName(mgr, resName, resultValue, 10, "format", 10.10)**.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetStringByName(const NativeResourceManager *mgr, const char *resName,
    char **resultValue, ...);

/**
 * @brief Obtains the string array based on the specified resource ID.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param resultValue Output parameter. Pointer to the string array. The memory is allocated by this function and must
 *     be released through {@link OH_ResourceManager_ReleaseStringArray} after use.
 * @param resultLen Output parameter. Length of the string array.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetStringArray(const NativeResourceManager *mgr, uint32_t resId,
    char ***resultValue, uint32_t *resultLen);

/**
 * @brief Obtains the string array based on the specified resource name.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param resultValue Output parameter. Pointer to the string array. The memory is allocated by this function and must
 *     be released through {@link OH_ResourceManager_ReleaseStringArray} after use.
 * @param resultLen Output parameter. Length of the string array.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetStringArrayByName(const NativeResourceManager *mgr,
    const char *resName, char ***resultValue, uint32_t *resultLen);

/**
 * @brief Releases the memory of the string array.
 *
 * @param resValue Input parameter. Pointer to the string array to be released.
 * @param len Input parameter. Length of the string array.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_ReleaseStringArray(char ***resValue, uint32_t len);

/**
 * @brief Obtains the plural string based on the specified resource ID.
 * <br>The Chinese language does not distinguish between singular and plural forms in strings, whereas other languages
 * do. For details about the specific rules, see {@link language plural rules}.
 * <br>In languages such as English and German, plural categories include cardinal forms (for example, 1, 2, 3) and
 * ordinal forms (for example, 1st, 2nd, 3rd). This function applies only to cardinal forms.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param num Input parameter. Quantity value, which is used to obtain the corresponding plural string based on the
 *     plural rules of the current language.
 * @param resultValue Output parameter. Pointer to the string. The memory is allocated by **malloc()**, and must be
 *     released via **free()**.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 * @deprecated since 16
 * @useinstead {@link OH_ResourceManager_GetIntPluralString}
 */
ResourceManager_ErrorCode OH_ResourceManager_GetPluralString(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t num, char **resultValue);

/**
 * @brief Obtains the plural string based on the specified resource name.
 * <br>The Chinese language does not distinguish between singular and plural forms in strings, whereas other languages
 * do. For details about the specific rules, see {@link language plural rules}.
 * <br>In languages such as English and German, plural categories include cardinal forms (for example, 1, 2, 3) and
 * ordinal forms (for example, 1st, 2nd, 3rd). This function applies only to cardinal forms.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param num Input parameter. Quantity value, which is used to obtain the corresponding plural string based on the
 *     plural rules of the current language.
 * @param resultValue Output parameter. Pointer to the string. The memory is allocated by **malloc()**, and must be
 *     released via **free()**.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 12
 * @deprecated since 16
 * @useinstead {@link OH_ResourceManager_GetIntPluralStringByName}
 */
ResourceManager_ErrorCode OH_ResourceManager_GetPluralStringByName(const NativeResourceManager *mgr,
    const char *resName, uint32_t num, char **resultValue);

/**
 * @brief Obtains the corresponding plural string and formats it based on the specified resource ID, integer quantity,
 * and variable parameters.
 * <br>The Chinese language does not distinguish between singular and plural forms in strings, whereas other languages
 * do. For details about the specific rules, see {@link language plural rules}.
 * <br>In languages such as English and German, plural categories include cardinal forms (for example, 1, 2, 3) and
 * ordinal forms (for example, 1st, 2nd, 3rd). This function applies only to cardinal forms.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param num Input parameter. Quantity value (integer), which is used to obtain the corresponding plural string based
 *     on the plural rules of the current language.
 * @param resultValue Output parameter. Pointer to the string. The memory is allocated by **malloc()**, and must be
 *     released via **free()**.
 * @param ... Input parameter, which is optional. Variable parameter list, which is used for string formatting. The
 *     following types are supported: const char*, int, and float.
 *     <br>You do not need to set this parameter when obtaining a plain string. This parameter is mandatory to obtain a
 *     formatted string. The variable parameters must be passed in the order corresponding to the placeholders in the
 *     string. The number and types of the parameters must match the placeholders in the string. For example, if the
 *     string contains three placeholders %d, %s, and %f, the API should be called as follows:
 *     **OH_ResourceManager_GetIntPluralString(mgr, resId, 10, resultValue, 10, "format", 10.10)**.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetIntPluralString(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t num, char **resultValue, ...);

/**
 * @brief Obtains the corresponding plural string and formats it based on the specified resource name, integer quantity,
 * and variable parameters.
 * <br>The Chinese language does not distinguish between singular and plural forms in strings, whereas other languages
 * do. For details about the specific rules, see {@link language plural rules}.
 * <br>In languages such as English and German, plural categories include cardinal forms (for example, 1, 2, 3) and
 * ordinal forms (for example, 1st, 2nd, 3rd). This function applies only to cardinal forms.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param num Input parameter. Quantity value (integer), which is used to obtain the corresponding plural string based
 *     on the plural rules of the current language.
 * @param resultValue Output parameter. Pointer to the string. The memory is allocated by **malloc()**, and must be
 *     released via **free()**.
 * @param ... Input parameter, which is optional. Variable parameter list, which is used for string formatting. The
 *     following types are supported: const char*, int, and float.
 *     <br>You do not need to set this parameter when obtaining a plain string. This parameter is mandatory to obtain a
 *     formatted string. The variable parameters must be passed in the order corresponding to the placeholders in the
 *     string. The number and types of the parameters must match the placeholders in the string. For example, if the
 *     string contains three placeholders %d, %s, and %f, the API should be called as follows:
 *     **OH_ResourceManager_GetIntPluralStringByName(mgr, resName, 10, resultValue, 10, "format", 10.10)**.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetIntPluralStringByName(const NativeResourceManager *mgr,
    const char *resName, uint32_t num, char **resultValue, ...);

/**
 * @brief Obtains the corresponding plural string and formats it based on the specified resource ID, floating-point
 * quantity, and variable parameters.
 * <br>The Chinese language does not distinguish between singular and plural forms in strings, whereas other languages
 * do. For details about the specific rules, see {@link language plural rules}.
 * <br>In languages such as English and German, plural categories include cardinal forms (for example, 1, 2, 3) and
 * ordinal forms (for example, 1st, 2nd, 3rd). This function applies only to cardinal forms.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param num Input parameter. Quantity value (floating-point), which is used to obtain the corresponding plural string
 *     based on the plural rules of the current language.
 * @param resultValue Output parameter. Pointer to the string. The memory is allocated by **malloc()**, and must be
 *     released via **free()**.
 * @param ... Input parameter, which is optional. Variable parameter list, which is used for string formatting. The
 *     following types are supported: const char*, int, and float.
 *     <br>You do not need to set this parameter when obtaining a plain string. This parameter is mandatory to obtain a
 *     formatted string. The variable parameters must be passed in the order corresponding to the placeholders in the
 *     string. The number and types of the parameters must match the placeholders in the string. For example, if the
 *     string contains three placeholders %d, %s, and %f, the API should be called as follows:
 *     **OH_ResourceManager_GetDoublePluralString(mgr, resId, 1.1, resultValue, 10, "format", 10.10)**.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDoublePluralString(const NativeResourceManager *mgr, uint32_t resId,
    double num, char **resultValue, ...);

/**
 * @brief Obtains the corresponding plural string and formats it based on the specified resource name, floating-point
 * quantity, and variable parameters.
 * <br>The Chinese language does not distinguish between singular and plural forms in strings, whereas other languages
 * do. For details about the specific rules, see {@link language plural rules}.
 * <br>In languages such as English and German, plural categories include cardinal forms (for example, 1, 2, 3) and
 * ordinal forms (for example, 1st, 2nd, 3rd). This function applies only to cardinal forms.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param num Input parameter. Quantity value (floating-point), which is used to obtain the corresponding plural string
 *     based on the plural rules of the current language.
 * @param resultValue Output parameter. Pointer to the string. The memory is allocated by **malloc()**, and must be
 *     released via **free()**.
 * @param ... Input parameter, which is optional. Variable parameter list, which is used for string formatting. The
 *     following types are supported: const char*, int, and float.
 *     <br>You do not need to set this parameter when obtaining a plain string. This parameter is mandatory to obtain a
 *     formatted string. The variable parameters must be passed in the order corresponding to the placeholders in the
 *     string. The number and types of the parameters must match the placeholders in the string. For example, if the
 *     string contains three placeholders %d, %s, and %f, the API should be called as follows:
 *     **OH_ResourceManager_GetDoublePluralStringByName(mgr, resName, 1.1, resultValue, 10, "format", 10.10)**.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 *     <br>**ERROR_CODE_OUT_OF_MEMORY**: Memory overflow occurs.
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDoublePluralStringByName(const NativeResourceManager *mgr,
    const char *resName, double num, char **resultValue, ...);

/**
 * @brief Obtains the color resource value based on the specified resource ID.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param resultValue Output parameter. Color resource value.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetColor(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t *resultValue);

/**
 * @brief Obtains the color resource value based on the specified resource name.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param resultValue Output parameter. Color resource value.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetColorByName(const NativeResourceManager *mgr, const char *resName,
    uint32_t *resultValue);

/**
 * @brief Obtains the integer resource value based on the specified resource ID.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param resultValue Output parameter. Integer resource value.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetInt(const NativeResourceManager *mgr, uint32_t resId,
    int *resultValue);

/**
 * @brief Obtains the integer resource value based on the specified resource name.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param resultValue Output parameter. Integer resource value.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetIntByName(const NativeResourceManager *mgr, const char *resName,
    int *resultValue);

/**
 * @brief Obtains the floating-point resource value based on the specified resource ID.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param resultValue Output parameter. Floating-point resource value.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetFloat(const NativeResourceManager *mgr, uint32_t resId,
    float *resultValue);

/**
 * @brief Obtains the floating-point resource value based on the specified resource name.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param resultValue Output parameter. Floating-point resource value.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetFloatByName(const NativeResourceManager *mgr, const char *resName,
    float *resultValue);

/**
 * @brief Obtains the Boolean resource value based on the specified resource ID.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resId Input parameter. Resource ID.
 * @param resultValue Output parameter. Boolean resource value.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_ID_NOT_FOUND**: Invalid resource ID.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_ID**: No matching resource is found based on the resource ID.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetBool(const NativeResourceManager *mgr, uint32_t resId,
    bool *resultValue);

/**
 * @brief Obtains the Boolean resource value based on the specified resource name.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param resName Input parameter. Resource name.
 * @param resultValue Output parameter. Boolean resource value.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_RES_NAME_NOT_FOUND**: Invalid resource name.
 *     <br>**ERROR_CODE_RES_NOT_FOUND_BY_NAME**: No matching resource is found based on the resource name.
 *     <br>**ERROR_CODE_RES_REF_TOO_MUCH**: The resource has a circular reference.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetBoolByName(const NativeResourceManager *mgr, const char *resName,
    bool *resultValue);

/**
 * @brief Dynamically loads overlay resources during application runtime to implement theme switching or resource
 * overriding.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param path Input parameter. Absolute path of the HSP or HAP resource package to be loaded.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_OVERLAY_RES_PATH_INVALID**: Invalid overlay path.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_AddResource(const NativeResourceManager *mgr, const char *path);

/**
 * @brief Removes the specified overlay resource during application runtime and restores the original resource before
 * the override.
 *
 * @param mgr Input parameter. Pointer to the NativeResourceManager object. The pointer is obtained through
 *     {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param path Input parameter. Absolute path of the HSP or HAP resource package to be removed.
 * @return Result code.
 *     <br>**SUCCESS**: Success.
 *     <br>**ERROR_CODE_INVALID_INPUT_PARAMETER**: Invalid input parameter. Possible causes: 1. The parameter type is
 *     incorrect. 2. Parameter verification failed.
 *     <br>**ERROR_CODE_OVERLAY_RES_PATH_INVALID**: Invalid overlay path.
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_RemoveResource(const NativeResourceManager *mgr, const char *path);
#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_OH_RESMGR_H
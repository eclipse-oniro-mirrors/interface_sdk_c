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
 * @brief 通过resourcemanager模块，开发者可以在Native层通过资源ID或资源名称获取应用资源或系统资源，实现多语言、多设备和多屏幕密度的
 * 资源适配。具体包括：
 * <br>- 获取基础类型资源：获取颜色值（ARGB格式）、整数、浮点数、布尔值等基础类型资源。
 * <br>- 获取字符串资源：获取普通字符串、格式化字符串（支持%d、%s、%f占位符）、字符串数组、复数字符串。
 * <br>- 获取媒体资源：获取媒体资源的原始二进制数据或Base64编码。
 * <br>- 资源覆盖：运行时动态加载和移除overlay资源，实现主题切换或资源覆盖。
 * <br>本模块依赖rawfile模块，需先通过rawfile模块获取NativeResourceManager对象。
 *
 * @since 12
 */
/**
 * @file ohresmgr.h
 *
 * @brief 提供资源管理Native层获取资源的能力。
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
 * @brief 通过指定资源ID和屏幕密度，获取对应的media资源的Base64编码字符串。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param resultValue 输出参数。返回Base64编码字符串指针，由malloc()分配内存，使用完后须通过free()释放。
 * @param resultLen 输出参数。返回Base64字符串长度，单位为Byte。
 * @param density 输入参数，可选。屏幕密度，取值范围请参考{@link ScreenDensity}。默认值为0，表示使用当前系统屏幕密度。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64(const NativeResourceManager *mgr, uint32_t resId,
    char **resultValue, uint64_t *resultLen, uint32_t density = 0);
#endif

/**
 * @brief 通过指定资源ID和屏幕密度，获取对应的media资源的Base64编码字符串。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param resultValue 输出参数。返回Base64编码字符串指针，由malloc()分配内存，使用完后须通过free()释放。
 * @param resultLen 输出参数。返回Base64字符串长度，单位为Byte。
 * @param density 输入参数。屏幕密度，取值范围请参考{@link ScreenDensity}。值为0表示使用当前系统屏幕密度。若不需要特定密度，请将此参数设置为0。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64Data(const NativeResourceManager *mgr, uint32_t resId,
    char **resultValue, uint64_t *resultLen, uint32_t density);

#ifdef __cplusplus
/**
 * @brief 通过指定资源名称和屏幕密度，获取对应的media资源的Base64编码字符串。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param resultValue 输出参数。返回Base64编码字符串指针，由malloc()分配内存，使用完后须通过free()释放。
 * @param resultLen 输出参数。返回Base64字符串长度，单位为Byte。
 * @param density 输入参数，可选。屏幕密度，取值范围请参考{@link ScreenDensity}。默认值为0，表示使用当前系统屏幕密度。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64ByName(const NativeResourceManager *mgr,
    const char *resName, char **resultValue, uint64_t *resultLen, uint32_t density = 0);
#endif

/**
 * @brief 通过指定资源名称和屏幕密度，获取对应的media资源的Base64编码字符串。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param resultValue 输出参数。返回Base64编码字符串指针，由malloc()分配内存，使用完后须通过free()释放。
 * @param resultLen 输出参数。返回Base64字符串长度，单位为Byte。
 * @param density 输入参数。屏幕密度，取值范围请参考{@link ScreenDensity}。值为0表示使用当前系统屏幕密度。若不需要特定密度，请将此参数设置为0。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaBase64DataByName(const NativeResourceManager *mgr,
    const char *resName, char **resultValue, uint64_t *resultLen, uint32_t density);

#ifdef __cplusplus
/**
 * @brief 通过指定资源ID和屏幕密度，获取对应的media资源的二进制数据。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param resultValue 输出参数。返回媒体数据指针，由malloc()分配内存，使用完后须通过free()释放。
 * @param resultLen 输出参数。返回数据长度，单位为Byte。
 * @param density 输入参数，可选。屏幕密度，取值范围请参考{@link ScreenDensity}。默认值为0，表示使用当前系统屏幕密度。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMedia(const NativeResourceManager *mgr, uint32_t resId,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density = 0);
#endif

/**
 * @brief 通过指定资源ID和屏幕密度，获取对应的media资源的二进制数据。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param resultValue 输出参数。返回媒体数据指针，由malloc()分配内存，使用完后须通过free()释放。
 * @param resultLen 输出参数。返回数据长度，单位为Byte。
 * @param density 输入参数。屏幕密度，取值范围请参考{@link ScreenDensity}。值为0表示使用当前系统屏幕密度。若不需要特定密度，请将此参数设置为0。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaData(const NativeResourceManager *mgr, uint32_t resId,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density);

#ifdef __cplusplus
/**
 * @brief 通过指定资源名称和屏幕密度，获取对应的media资源的二进制数据。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param resultValue 输出参数。返回媒体数据指针，由malloc()分配内存，使用完后须通过free()释放。
 * @param resultLen 输出参数。返回数据长度，单位为Byte。
 * @param density 输入参数，可选。屏幕密度，取值范围请参考{@link ScreenDensity}。默认值为0，表示使用当前系统屏幕密度。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaByName(const NativeResourceManager *mgr, const char *resName,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density = 0);
#endif

/**
 * @brief 通过指定资源名称和屏幕密度，获取对应的media资源的二进制数据。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param resultValue 输出参数。返回媒体数据指针，由malloc()分配内存，使用完后须通过free()释放。
 * @param resultLen 输出参数。返回数据长度，单位为Byte。
 * @param density 输入参数。屏幕密度，取值范围请参考{@link ScreenDensity}。值为0表示使用当前系统屏幕密度。若不需要特定密度，请将此参数设置为0。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetMediaDataByName(const NativeResourceManager *mgr, const char *resName,
    uint8_t **resultValue, uint64_t *resultLen, uint32_t density);

#ifdef __cplusplus
/**
 * @brief 通过指定资源ID、屏幕密度、图标类型，获取图标资源对应的DrawableDescriptor对象。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param drawableDescriptor 输出参数。返回指向DrawableDescriptor对象的指针。
 * @param density 输入参数，可选。屏幕密度，取值范围请参考{@link ScreenDensity}。默认值为0，表示使用当前系统屏幕密度。
 * @param type 输入参数，可选。图标类型，默认值为0。
 *     <br>0：表示应用自身图标。
 *     <br>1：表示应用主题图标。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptor(const NativeResourceManager *mgr,
    uint32_t resId, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density = 0, uint32_t type = 0);
#endif

/**
 * @brief 通过指定资源ID、屏幕密度、图标类型，获取图标资源对应的DrawableDescriptor对象。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param drawableDescriptor 输出参数。返回指向DrawableDescriptor对象的指针。
 * @param density 输入参数。屏幕密度，取值范围请参考{@link ScreenDensity}。值为0表示使用当前系统屏幕密度。若不需要特定密度，请将此参数设置为0。
 * @param type 输入参数。图标类型，若不需要特定图标类型，请将该参数设置为0。
 *     <br>0：表示应用自身图标。
 *     <br>1：表示应用主题图标。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptorData(const NativeResourceManager *mgr,
    uint32_t resId, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density, uint32_t type);

#ifdef __cplusplus
/**
 * @brief 通过指定资源名称、屏幕密度、图标类型，获取图标资源对应的DrawableDescriptor对象。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param drawableDescriptor 输出参数。返回指向DrawableDescriptor对象的指针。
 * @param density 输入参数，可选。屏幕密度，取值范围请参考{@link ScreenDensity}。默认值为0，表示使用当前系统屏幕密度。
 * @param type 输入参数，可选。图标类型，默认值为0。
 *     <br>0：表示应用自身图标。
 *     <br>1：表示应用主题图标。
 *     <br>2：表示应用动态图标。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptorByName(const NativeResourceManager *mgr,
    const char *resName, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density = 0, uint32_t type = 0);
#endif

/**
 * @brief 通过指定资源名称和屏幕密度，获取对应的图标资源的DrawableDescriptor对象。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param drawableDescriptor 输出参数。返回指向DrawableDescriptor对象的指针。
 * @param density 输入参数，屏幕密度，取值范围请参考{@link ScreenDensity}。值为0表示使用当前系统屏幕密度。若不需要特定密度，请将此参数设置为0。
 * @param type 输入参数。图标类型，若不需要特定图标类型，请将该参数设置为0。
 *     <br>0：表示应用自身图标。
 *     <br>1：表示应用主题图标。
 *     <br>2：表示应用动态图标。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDrawableDescriptorDataByName(const NativeResourceManager *mgr,
    const char *resName, ArkUI_DrawableDescriptor **drawableDescriptor, uint32_t density, uint32_t type);

/**
 * @brief 获取指定资源ID对应的Symbol图标的Unicode编码。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param resultValue 输出参数。返回Symbol图标的Unicode编码。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetSymbol(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t *resultValue);

/**
 * @brief 获取指定资源名称对应的Symbol图标的Unicode编码。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param resultValue 输出参数。返回Symbol图标的Unicode编码。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetSymbolByName(const NativeResourceManager *mgr, const char *resName,
    uint32_t *resultValue);

#ifdef __cplusplus
/**
 * @brief 获取应用支持的语言列表。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resultValue 输出参数。返回指向语言列表数组的指针，由此函数分配内存，使用完后须通过{@link OH_ResourceManager_ReleaseStringArray}释放。
 * @param resultLen 输出参数。返回语言列表长度。
 * @param includeSystem 输入参数，可选。表示是否包含系统资源，true表示包含系统资源，false表示不包含系统资源。默认值为false。
 *     <br>当使用系统资源管理对象获取语言列表时，始终返回系统资源语言列表。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetLocales(const NativeResourceManager *mgr, char ***resultValue,
    uint32_t *resultLen, bool includeSystem = false);
#endif

/**
 * @brief 获取应用支持的语言列表。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resultValue 输出参数。返回指向语言列表数组的指针，由此函数分配内存，使用完后须通过{@link OH_ResourceManager_ReleaseStringArray}释放。
 * @param resultLen 输出参数。返回语言列表长度。
 * @param includeSystem 输入参数。表示是否包含系统资源，true表示包含系统资源，false表示不包含系统资源。
 *     <br>当使用系统资源管理对象获取语言列表时，始终返回系统资源语言列表。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetLocalesData(const NativeResourceManager *mgr, char ***resultValue,
    uint32_t *resultLen, bool includeSystem);

/**
 * @brief 获取设备的屏幕方向、语言区域、设备类型、屏幕密度、颜色模式等配置信息。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param configuration 输出参数。返回设备配置信息，其中screenDensity为设备屏幕密度（dpi）除以160取整后的值。
 *     <br>configuration中的locale字符串由此函数分配内存，使用完后需通过{@link OH_ResourceManager_ReleaseConfiguration}释放locale。
 *     若configuration指针由malloc()分配内存，使用完后须通过free()释放。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_SYSTEM_RES_MANAGER_GET_FAILED，表示访问系统资源失败。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 * @deprecated since 20
 * @useinstead {@link OH_ResourceManager_GetResourceConfiguration}
 */
ResourceManager_ErrorCode OH_ResourceManager_GetConfiguration(const NativeResourceManager *mgr,
    ResourceManager_Configuration *configuration);

/**
 * @brief 获取设备的屏幕方向、语言区域、设备类型、屏幕密度、颜色模式等配置信息。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param configuration 输出参数。返回设备配置信息，其中screenDensity的值为设备屏幕密度（dpi）。
 *     <br>configuration中的locale字符串由此函数分配内存，使用完后需通过{@link OH_ResourceManager_ReleaseConfiguration}释放locale。
 *     若configuration指针由malloc()分配内存，使用完后须通过free()释放。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_SYSTEM_RES_MANAGER_GET_FAILED，表示访问系统资源失败。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 20
 */
ResourceManager_ErrorCode OH_ResourceManager_GetResourceConfiguration(const NativeResourceManager *mgr,
    ResourceManager_Configuration *configuration);

/**
 * @brief 释放{@link OH_ResourceManager_GetConfiguration}或{@link OH_ResourceManager_GetResourceConfiguration}函数申请的内存。
 *
 * @param configuration 输入参数。指向需要释放内存的{@link ResourceManager_Configuration}对象的指针。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_ReleaseConfiguration(ResourceManager_Configuration *configuration);

/**
 * @brief 获取指定资源ID对应的普通字符串或格式化字符串。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param resultValue 输出参数。返回字符串指针，由malloc()分配内存，使用完后须通过free()释放。
 * @param ... 输入参数，可选。表示可变参数列表，用于格式化字符串，支持const char*、int、float三种类型。
 *     <br>获取普通字符串时，无需填写；获取格式化字符串时，必填，须按字符串中的占位符顺序依次传入对应类型的可变参数，参数数量、类型与字符串的
 *     占位符保持一致，如字符串包含%d、%s、%f三个占位符，调用方式为
 *     OH_ResourceManager_GetString(mgr, resId, resultValue, 10, "format", 10.10)。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetString(const NativeResourceManager *mgr, uint32_t resId,
    char **resultValue, ...);

/**
 * @brief 获取指定资源名称对应的普通字符串或格式化字符串。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param resultValue 输出参数。返回字符串指针，由malloc()分配内存，使用完后须通过free()释放。
 * @param ... 输入参数，可选。表示可变参数列表，用于格式化字符串，支持const char*、int、float三种类型。
 *     <br>获取普通字符串时，无需填写；获取格式化字符串时，必填，须按字符串中的占位符顺序依次传入对应类型的可变参数，参数数量、类型与字符串的
 *     占位符保持一致，如字符串包含%d、%s、%f三个占位符，调用方式为
 *     OH_ResourceManager_GetStringByName(mgr, resName, resultValue, 10, "format", 10.10)。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetStringByName(const NativeResourceManager *mgr, const char *resName,
    char **resultValue, ...);

/**
 * @brief 获取指定资源ID对应的字符串数组。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param resultValue 输出参数。返回字符串数组指针。由此函数分配内存，使用完后须通过{@link OH_ResourceManager_ReleaseStringArray}释放。
 * @param resultLen 输出参数。返回字符串数组长度。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetStringArray(const NativeResourceManager *mgr, uint32_t resId,
    char ***resultValue, uint32_t *resultLen);

/**
 * @brief 获取指定资源名称对应的字符串数组。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param resultValue 输出参数。返回字符串数组指针。由此函数分配内存，使用完后须通过{@link OH_ResourceManager_ReleaseStringArray}释放。
 * @param resultLen 输出参数。返回字符串数组长度。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetStringArrayByName(const NativeResourceManager *mgr,
    const char *resName, char ***resultValue, uint32_t *resultLen);

/**
 * @brief 释放字符串数组内存。
 *
 * @param resValue 输入参数。待释放的字符串数组指针。
 * @param len 输入参数。字符串数组长度。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_ReleaseStringArray(char ***resValue, uint32_t len);

/**
 * @brief 获取指定资源ID对应的复数字符串。
 * <br>中文环境下，字符串不区分单复数；其他语言环境下，字符串区分单复数，具体规则参考{@link 语言单复数规则}。
 * <br>在英语、德语等语言中，单复数类型包括基数词（如1、2、3）和序数词（如1st、2nd、3rd），本函数仅支持在基数词类型下使用。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param num 输入参数。数量值，用于根据当前语言的复数规则获取对应的复数字符串。
 * @param resultValue 输出参数。返回字符串指针。由malloc()分配内存，使用完后须通过free()释放。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 * @deprecated since 16
 * @useinstead {@link OH_ResourceManager_GetIntPluralString}
 */
ResourceManager_ErrorCode OH_ResourceManager_GetPluralString(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t num, char **resultValue);

/**
 * @brief 获取指定资源名称对应的复数字符串。
 * <br>中文环境下，字符串不区分单复数；其他语言环境下，字符串区分单复数，具体规则参考{@link 语言单复数规则}。
 * <br>在英语、德语等语言中，单复数类型包括基数词（如1、2、3）和序数词（如1st、2nd、3rd），本函数仅支持在基数词类型下使用。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param num 输入参数。数量值，用于根据当前语言的复数规则获取对应的复数字符串。
 * @param resultValue 输出参数。返回字符串指针。由malloc()分配内存，使用完后须通过free()释放。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 12
 * @deprecated since 16
 * @useinstead {@link OH_ResourceManager_GetIntPluralStringByName}
 */
ResourceManager_ErrorCode OH_ResourceManager_GetPluralStringByName(const NativeResourceManager *mgr,
    const char *resName, uint32_t num, char **resultValue);

/**
 * @brief 通过指定资源ID、整数数量值和可变参数，获取对应的复数字符串并进行格式化。
 * <br>中文环境下，字符串不区分单复数；其他语言环境下，字符串区分单复数，具体规则参考{@link 语言单复数规则}。
 * <br>在英语、德语等语言中，单复数类型包括基数词（如1、2、3）和序数词（如1st、2nd、3rd），本函数仅支持在基数词类型下使用。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param num 输入参数。数量值（整数），用于根据当前语言的复数规则获取对应的复数字符串。
 * @param resultValue 输出参数。返回字符串指针。由malloc()分配内存，使用完后须通过free()释放。
 * @param ... 输入参数，可选。表示可变参数列表，用于格式化字符串，支持const char*、int、float三种类型。
 *     <br>获取普通字符串时，无需填写；获取格式化字符串时，必填，须按字符串中的占位符顺序依次传入对应类型的可变参数，参数数量、类型与字符串的
 *     占位符保持一致，如字符串包含%d、%s、%f三个占位符，调用方式为
 *     OH_ResourceManager_GetIntPluralString(mgr, resId, 10, resultValue, 10, "format", 10.10)。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetIntPluralString(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t num, char **resultValue, ...);

/**
 * @brief 通过指定资源名称、整数数量值和可变参数，获取对应的复数字符串并进行格式化。
 * <br>中文环境下，字符串不区分单复数；其他语言环境下，字符串区分单复数，具体规则参考{@link 语言单复数规则}。
 * <br>在英语、德语等语言中，单复数类型包括基数词（如1、2、3）和序数词（如1st、2nd、3rd），本函数仅支持在基数词类型下使用。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param num 输入参数。数量值（整数），用于根据当前语言的复数规则获取对应的复数字符串。
 * @param resultValue 输出参数。返回字符串指针。由malloc()分配内存，使用完后须通过free()释放。
 * @param ... 输入参数，可选。表示可变参数列表，用于格式化字符串，支持const char*、int、float三种类型。
 *     <br>获取普通字符串时，无需填写；获取格式化字符串时，必填，须按字符串中的占位符顺序依次传入对应类型的可变参数，参数数量、类型与字符串的
 *     占位符保持一致，如字符串包含%d、%s、%f三个占位符，调用方式为
 *     OH_ResourceManager_GetIntPluralStringByName(mgr, resName, 10, resultValue, 10, "format", 10.10)。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetIntPluralStringByName(const NativeResourceManager *mgr,
    const char *resName, uint32_t num, char **resultValue, ...);

/**
 * @brief 通过指定资源ID、浮点数数量值和可变参数，获取对应的复数字符串并进行格式化。
 * <br>中文环境下，字符串不区分单复数；其他语言环境下，字符串区分单复数，具体规则参考{@link 语言单复数规则}。
 * <br>在英语、德语等语言中，单复数类型包括基数词（如1、2、3）和序数词（如1st、2nd、3rd），本函数仅支持在基数词类型下使用。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param num 输入参数。数量值（浮点数），用于根据当前语言的复数规则获取对应的复数字符串。
 * @param resultValue 输出参数。返回字符串指针。由malloc()分配内存，使用完后须通过free()释放。
 * @param ... 输入参数，可选。表示可变参数列表，用于格式化字符串，支持const char*、int、float三种类型。
 *     <br>获取普通字符串时，无需填写；获取格式化字符串时，必填，须按字符串中的占位符顺序依次传入对应类型的可变参数，参数数量、类型与字符串的
 *     占位符保持一致，如字符串包含%d、%s、%f三个占位符，调用方式为
 *     OH_ResourceManager_GetDoublePluralString(mgr, resId, 1.1, resultValue, 10, "format", 10.10)。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDoublePluralString(const NativeResourceManager *mgr, uint32_t resId,
    double num, char **resultValue, ...);

/**
 * @brief 通过指定资源名称、浮点数数量值和可变参数，获取对应的复数字符串并进行格式化。
 * <br>中文环境下，字符串不区分单复数；其他语言环境下，字符串区分单复数，具体规则参考{@link 语言单复数规则}。
 * <br>在英语、德语等语言中，单复数类型包括基数词（如1、2、3）和序数词（如1st、2nd、3rd），本函数仅支持在基数词类型下使用。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param num 输入参数。数量值（浮点数），用于根据当前语言的复数规则获取对应的复数字符串。
 * @param resultValue 输出参数。返回字符串指针。由malloc()分配内存，使用完后须通过free()释放。
 * @param ... 输入参数，可选。表示可变参数列表，用于格式化字符串，支持const char*、int、float三种类型。
 *     <br>获取普通字符串时，无需填写；获取格式化字符串时，必填，须按字符串中的占位符顺序依次传入对应类型的可变参数，参数数量、类型与字符串的
 *     占位符保持一致，如字符串包含%d、%s、%f三个占位符，调用方式为
 *     OH_ResourceManager_GetDoublePluralStringByName(mgr, resName, 1.1, resultValue, 10, "format", 10.10)。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 *     <br>返回ERROR_CODE_OUT_OF_MEMORY，表示内存溢出。
 * @since 18
 */
ResourceManager_ErrorCode OH_ResourceManager_GetDoublePluralStringByName(const NativeResourceManager *mgr,
    const char *resName, double num, char **resultValue, ...);

/**
 * @brief 获取指定资源ID对应的颜色资源值。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param resultValue 输出参数。返回颜色资源值。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetColor(const NativeResourceManager *mgr, uint32_t resId,
    uint32_t *resultValue);

/**
 * @brief 获取指定资源名称对应的颜色资源值。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param resultValue 输出参数。返回颜色资源值。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetColorByName(const NativeResourceManager *mgr, const char *resName,
    uint32_t *resultValue);

/**
 * @brief 获取指定资源ID对应的整数资源值。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param resultValue 输出参数。返回整数资源值。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetInt(const NativeResourceManager *mgr, uint32_t resId,
    int *resultValue);

/**
 * @brief 获取指定资源名称对应的整数资源值。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param resultValue 输出参数。返回整数资源值。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetIntByName(const NativeResourceManager *mgr, const char *resName,
    int *resultValue);

/**
 * @brief 获取指定资源ID对应的浮点数资源值。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param resultValue 输出参数。返回浮点数资源值。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetFloat(const NativeResourceManager *mgr, uint32_t resId,
    float *resultValue);

/**
 * @brief 获取指定资源名称对应的浮点数资源值。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param resultValue 输出参数。返回浮点数资源值。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetFloatByName(const NativeResourceManager *mgr, const char *resName,
    float *resultValue);

/**
 * @brief 获取指定资源ID对应的布尔资源值。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resId 输入参数。资源ID。
 * @param resultValue 输出参数。返回布尔资源值。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_ID_NOT_FOUND，表示无效的资源ID。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_ID，表示根据资源ID未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetBool(const NativeResourceManager *mgr, uint32_t resId,
    bool *resultValue);

/**
 * @brief 获取指定资源名称对应的布尔资源值。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param resName 输入参数。资源名称。
 * @param resultValue 输出参数。返回布尔资源值。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_RES_NAME_NOT_FOUND，表示无效的资源名称。
 *     <br>返回ERROR_CODE_RES_NOT_FOUND_BY_NAME，表示根据资源名称未找到匹配的资源。
 *     <br>返回ERROR_CODE_RES_REF_TOO_MUCH，表示资源存在循环引用。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_GetBoolByName(const NativeResourceManager *mgr, const char *resName,
    bool *resultValue);

/**
 * @brief 在应用程序运行时，动态加载overlay资源，实现主题切换或资源覆盖。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param path 输入参数。待加载的HSP或HAP资源包的绝对路径。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_OVERLAY_RES_PATH_INVALID，表示无效的overlay路径。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_AddResource(const NativeResourceManager *mgr, const char *path);

/**
 * @brief 在应用程序运行时，移除指定的overlay资源，还原被覆盖前的资源。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针，此指针通过{@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 * @param path 输入参数。待移除的HSP或HAP资源包的绝对路径。
 * @return 返回错误码。
 *     <br>返回SUCCESS，表示成功。
 *     <br>返回ERROR_CODE_INVALID_INPUT_PARAMETER，表示输入参数无效。可能的原因：1.参数类型不正确；2.参数验证失败。
 *     <br>返回ERROR_CODE_OVERLAY_RES_PATH_INVALID，表示无效的overlay路径。
 * @since 12
 */
ResourceManager_ErrorCode OH_ResourceManager_RemoveResource(const NativeResourceManager *mgr, const char *path);
#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_OH_RESMGR_H
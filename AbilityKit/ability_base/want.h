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
 * @addtogroup AbilityBase
 * @{
 *
 * @brief Describe the functions of want.
 * @since 15
 */
/**
 * @file want.h
 *
 * @brief Want is a carrier for information transfer between objects (application components). Want can be used as a
 * parameter of **startAbility** to specify a startup target and information that needs to be carried during startup,
 * for example, **bundleName** and **abilityName**, which respectively indicate the bundle name of the target ability
 * and the ability name in the bundle. When ability A needs to start ability B and transfer some data to ability B, it
 * can use Want a carrier to transfer the data.
 *
 * @library libability_base_want.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityBase
 * @since 15
 */

#ifndef ABILITY_BASE_WANT_H
#define ABILITY_BASE_WANT_H

#include <stddef.h>
#include <stdint.h>
#include "ability_base_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct describes the Element in {@link Want}.
 *
 * @since 15
 */
typedef struct AbilityBase_Element {
    /**
     * Pointer to the bundle name of the application.
     *
     * @since 15
     */
    char* bundleName;
    /**
     * Pointer to the module name.
     *
     * @since 15
     */
    char* moduleName;
    /**
     * Pointer to the ability name.
     *
     * @since 15
     */
    char* abilityName;
} AbilityBase_Element;

struct AbilityBase_Want;
typedef struct AbilityBase_Want AbilityBase_Want;

/**
 * @brief Creates Want.
 *
 * @param element Element struct.
 * @return Pointer to Want.
 * @since 15
 */
AbilityBase_Want* OH_AbilityBase_CreateWant(AbilityBase_Element element);

/**
 * @brief Destroys Want. Want cannot be used after being destroyed. Otherwise, undefined behavior may occur.
 *
 * @param want Pointer to Want.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: Want is destroyed.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **element** is invalid.
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_DestroyWant(AbilityBase_Want* want);

/**
 * @brief Sets the Element struct, which consists of **bundleName**, **moduleName**, and **abilityName** in Want.
 *
 * @param want Pointer to Want.
 * @param element Element struct.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The setting is successful.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or **element** is invalid.
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_SetWantElement(AbilityBase_Want* want, AbilityBase_Element element);

/**
 * @brief Obtains the Element struct, which consists of **bundleName**, **moduleName**, and **abilityName** in Want.
 *
 * @param want Pointer to Want.
 * @param element Pointer to the Element struct.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The element struct is obtained.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or **element** is invalid.
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantElement(AbilityBase_Want* want, AbilityBase_Element* element);

/**
 * @brief Sets **Param** in Want. For details about **Param**, see {@link parameters in Want}.
 *
 * @param want Pointer to Want.
 * @param key Pointer to a key in Want.
 * @param value Pointer to the value of the key in Want.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The setting is successful.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or invalid.
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_SetWantCharParam(AbilityBase_Want* want, const char* key, const char* value);

/**
 * @brief Obtains **Param** set by {@link OH_AbilityBase_SetWantCharParam} in Want.
 *
 * @param want Pointer to Want.
 * @param key Pointer to a key in Want.
 * @param value Pointer to the value of the key in Want.
 * @param valueSize Length of the value string. If **valueSize** is less than the actual value length,
 *      the {@link ABILITY_BASE_ERROR_CODE_PARAM_INVALID} error is reported.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The param struct is obtained.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or invalid.
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantCharParam(AbilityBase_Want* want, const char* key,
    char* value, size_t valueSize);

/**
 * @brief Adds a Want file descriptor. The file descriptor can be obtained through {@link fs.open}.
 *
 * @param want Pointer to Want.
 * @param key Pointer to a key in Want.
 * @param fd File descriptor, which is obtained by calling {@link fs.open}.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The Want file descriptor is added.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or invalid.
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_AddWantFd(AbilityBase_Want* want, const char* key, int32_t fd);

/**
 * @brief Obtains a Want file descriptor.
 *
 * @param want Pointer to Want.
 * @param key Pointer to a key in Want.
 * @param fd Pointer to the file descriptor.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The Want file descriptor is obtained.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or invalid.
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantFd(AbilityBase_Want* want, const char* key, int32_t* fd);

/**
 * @brief Sets **uri** in Want. For details about the URI, see {@link uri in Want}.
 *
 * @param want Pointer to Want.
 * @param uri Pointer to a URI. If a URI is specified in Want, Want will match the specified URI information. For
 *      details about the URI, see {@link uri in Want}.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The setting is successful.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or invalid.
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_SetWantUri(AbilityBase_Want* want, const char* uri);

/**
 * @brief Obtains **uri** set in Want. For details about the URI, see {@link uri in Want}.
 *
 * @param want Pointer to Want.
 * @param uri Pointer to a URI. If a URI is specified in Want, Want will match the specified URI information. For
 *      details about the URI, see {@link uri in Want}.
 * @param uriSize Length of the URI string. If **uriSize** is less than the actual URI length,
 *      the {@link ABILITY_BASE_ERROR_CODE_PARAM_INVALID} error is reported.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The URI string in Want is obtained.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or invalid.
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantUri(AbilityBase_Want* want, char* uri, size_t uriSize);

/**
 * @brief Sets a value of the int32_t type in Want.
 *
 * @param want Pointer to Want.
 * @param key Pointer to a key in Want.
 * @param value Value of the int32_t type of the key.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The setting is successful.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or invalid.
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_SetWantInt32Param(AbilityBase_Want* want, const char* key, int32_t value);

/**
 * @brief Obtains a value of the int32_t type set in Want.
 *
 * @param want Pointer to Want.
 * @param key Pointer to a key in Want.
 * @param value Pointer to the value of the int32_t type of the key.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The value of the int32_t type is obtained.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or invalid.
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantInt32Param(AbilityBase_Want* want, const char* key, int32_t* value);

/**
 * @brief Sets a value of the bool type in Want.
 *
 * @param want Pointer to Want.
 * @param key Pointer to a key in Want.
 * @param value Value of the bool type of the key.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The setting is successful.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or invalid.
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_SetWantBoolParam(AbilityBase_Want* want, const char* key, bool value);

/**
 * @brief Obtains a value of the bool type set in Want.
 *
 * @param want Pointer to Want.
 * @param key Pointer to a key in Want.
 * @param value Pointer to the value of the bool type of the key.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The value of the bool type is obtained.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or invalid.
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantBoolParam(AbilityBase_Want* want, const char* key, bool* value);

/**
 * @brief Sets a value of the double type in Want.
 *
 * @param want Pointer to Want.
 * @param key Pointer to a key in Want.
 * @param value Value of the double type of the key.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The setting is successful.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or invalid.
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_SetWantDoubleParam(AbilityBase_Want* want, const char* key, double value);

/**
 * @brief Obtains a value of the double type set in Want.
 *
 * @param want Pointer to Want.
 * @param key Pointer to a key in Want.
 * @param value Pointer to the value of the double type of the key.
 * @return One of the following execution results:
 *      **ABILITY_BASE_ERROR_CODE_NO_ERROR**: The value of the double type is obtained.
 *      **ABILITY_BASE_ERROR_CODE_PARAM_INVALID**: **want** is null or invalid.
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantDoubleParam(AbilityBase_Want* want, const char* key, double* value);

#ifdef __cplusplus
} // extern "C"
#endif

/** @} */
#endif // ABILITY_BASE_WANT_H

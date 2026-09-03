/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 * @addtogroup AbilityBase
 * @{
 *
 * @brief 描述Want的方法。
 *
 * @syscap SystemCapability.Ability.AbilityBase
 * @since 15
 */

/**
 * @file want.h
 *
 * @brief Want是对象间信息传递的载体，可以用于应用组件间的信息传递。 Want的使用场景之一是作为startAbility的参数，其包含了指定的启动目标，以及启动时需携带的相关数据，
 * 如bundleName和abilityName字段分别指明目标Ability所在应用的Bundle名称以及对应包内的Ability名称。当Ability A需要启动Ability B并传入一些数据时，
 * 可使用Want作为载体将这些数据传递给Ability B。
 *
 * @library libability_base_want.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityBase
 * @since 15
 */

#ifndef ABILITY_BASE_WANT_H
#define ABILITY_BASE_WANT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "ability_base_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 声明{@link Want}中Element结构体。
 *
 * @since 15
 */
typedef struct AbilityBase_Element {
    /**
     * 应用的包名。
     */
    char* bundleName;
    /**
     * 模块名称。
     */
    char* moduleName;
    /**
     * Ability名称。
     */
    char* abilityName;
} AbilityBase_Element;

/**
 * @brief 声明元能力Want结构。
 *
 * @since 15
 */
struct AbilityBase_Want;

/**
 * @brief 声明元能力Want结构。
 *
 * @since 15
 */
typedef struct AbilityBase_Want AbilityBase_Want;

/**
 * @brief 创建Want。
 *
 * @param element Element数据结构。
 * @return 返回want数据结构。
 * @since 15
 */
AbilityBase_Want* OH_AbilityBase_CreateWant(AbilityBase_Element element);

/**
 * @brief 销毁Want。销毁后的Want不可使用，否则会导致未定义行为。
 *
 * @param want Want指针。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 销毁want成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want参数无效。
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_DestroyWant(AbilityBase_Want* want);

/**
 * @brief 设置Want中由bundleName、moduleName与abilityName组成的Element结构体。
 *
 * @param want Want指针。
 * @param element Element结构体。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 设置element成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空，element参数无效。
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_SetWantElement(AbilityBase_Want* want, AbilityBase_Element element);

/**
 * @brief 获取Want中由bundleName、moduleName与abilityName组成的Element结构体。
 *
 * @param want Want指针。
 * @param element Element结构体。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 获取element成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空，element参数无效。
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantElement(AbilityBase_Want* want, AbilityBase_Element* element);

/**
 * @brief 设置Want Param参数，Param可参考Want中的parameters参数。
 *
 * @param want Want指针。
 * @param key Want中字符串参数键名。
 * @param value Want中字符串。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 设置param成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空或非法入参。
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_SetWantCharParam(AbilityBase_Want* want, const char* key, const char* value);

/**
 * @brief 获取{@link OH_AbilityBase_SetWantCharParam}方法设置的Want Param参数。
 *
 * @param want Want指针。
 * @param key Want中字符串参数键名。
 * @param value Want中字符串。
 * @param valueSize value字符串长度。如果valueSize小于实际需要获取的value长度，则会报{@link ABILITY_BASE_ERROR_CODE_PARAM_INVALID}错误。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 获取param成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空或非法入参。
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantCharParam(AbilityBase_Want* want, const char* key,
    char* value, size_t valueSize);

/**
 * @brief 添加Want文件描述符，文件描述符可通过{@link fileIo.open}获取。
 *
 * @param want Want指针。
 * @param key Want中字符串参数键名。
 * @param fd 文件描述符，可通过{@link fileIo.open}获取。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 添加want文件描述符成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空或非法入参。
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_AddWantFd(AbilityBase_Want* want, const char* key, int32_t fd);

/**
 * @brief 获取Want文件描述符。
 *
 * @param want Want指针。
 * @param key Want中字符串参数键名。
 * @param fd 文件描述符。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 获取want文件描述符成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空或非法入参。
 * @since 15
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantFd(AbilityBase_Want* want, const char* key, int32_t* fd);

/**
 * @brief 设置Want中URI字符串，URI可参考{@link Want}中的uri描述。
 *
 * @param want Want指针。
 * @param uri 表示URI。如果在Want中指定了URI，则Want将匹配指定的URI信息。URI可参考{@link Want}中的uri描述。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 设置want中uri字符串成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空或非法入参。
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_SetWantUri(AbilityBase_Want* want, const char* uri);

/**
 * @brief 获取Want中URI字符串。URI可参考{@link Want}中的uri描述。
 *
 * @param want Want指针。
 * @param uri 表示URI。如果在Want中指定了URI，则Want将匹配指定的URI信息。URI可参考{@link Want}中的uri描述。
 * @param uriSize URI字符串长度。如果uriSize小于实际需要获取的URI长度，则会报{@link ABILITY_BASE_ERROR_CODE_PARAM_INVALID}错误。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 获取want中URI字符串成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空或非法入参。
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantUri(AbilityBase_Want* want, char* uri, size_t uriSize);

/**
 * @brief 设置Want中int32_t类型的值。
 *
 * @param want Want指针。
 * @param key Want中int32_t类型值的参数键名。
 * @param value Want中int32_t类型的值。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 设置want中int32_t类型的值成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空或非法入参。
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_SetWantInt32Param(AbilityBase_Want* want, const char* key, int32_t value);

/**
 * @brief 获取Want中int32_t类型的值。
 *
 * @param want Want指针。
 * @param key Want中int32_t类型值的参数键名。
 * @param value Want中int32_t类型的值。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 获取want中int32_t类型的值成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空或非法入参。
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantInt32Param(AbilityBase_Want* want, const char* key, int32_t* value);

/**
 * @brief 设置Want中bool类型的值。
 *
 * @param want Want指针。
 * @param key Want中bool类型值的参数键名。
 * @param value Want中bool类型的值。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 设置want中bool类型的值成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空或非法入参。
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_SetWantBoolParam(AbilityBase_Want* want, const char* key, bool value);

/**
 * @brief 获取Want中bool类型的值。
 *
 * @param want Want指针。
 * @param key Want中bool类型值的参数键名。
 * @param value Want中bool类型的值。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 获取want中bool类型的值成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空或非法入参。
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantBoolParam(AbilityBase_Want* want, const char* key, bool* value);

/**
 * @brief 设置Want中double类型的值。
 *
 * @param want Want指针。
 * @param key Want中double类型值的参数键名。
 * @param value Want中double类型的值。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 设置want中double类型的值成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空或非法入参。
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_SetWantDoubleParam(AbilityBase_Want* want, const char* key, double value);

/**
 * @brief 获取Want中double类型的值。
 *
 * @param want Want指针。
 * @param key Want中double类型值的参数键名。
 * @param value Want中double类型的值。
 * @return 返回执行结果。
 *     <br>ABILITY_BASE_ERROR_CODE_NO_ERROR - 获取want中double类型的值成功。
 *     <br>ABILITY_BASE_ERROR_CODE_PARAM_INVALID - want为空或非法入参。
 * @since 17
 */
AbilityBase_ErrorCode OH_AbilityBase_GetWantDoubleParam(AbilityBase_Want* want, const char* key, double* value);

#ifdef __cplusplus
} // extern "C"
#endif

/** @} */
#endif // ABILITY_BASE_WANT_H
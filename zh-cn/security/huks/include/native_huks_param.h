/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup HuksParamSetApi
 * @{
 *
 * @brief Defines the capabilities of OpenHarmony Universal KeyStore (HUKS) parameter sets.
 *    The HUKS APIs can be used to perform parameter set lifecycle management,
 *    including initializing a parameter set, adding parameters to a parameter set, constructing
 *    a parameter set, and destroying a parameter set.
 *    They can also be used to obtain parameters, copy parameter sets, and check parameter validity.
 *
 * @since 9
 * @version 1.0
 */

/**
 * @file native_huks_param.h
 *
 * @brief Provides APIs for constructing, using, and destroying a parameter set.
 *
 * @library libhuks_ndk.z.so
 * @syscap SystemCapability.Security.Huks.Core
 *
 * @kit UniversalKeystoreKit
 * @since 9
 * @version 1.0
 */
#ifndef NATIVE_HUKS_PARAM_H
#define NATIVE_HUKS_PARAM_H
#include "native_huks_type.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化参数集，无参数信息，分配参数集默认可用内存空间。初始化后的参数集需要通过{@link OH_Huks_FreeParamSet}释放。添加参数的参数集需要使用{@link OH_Huks_AddParams}
 * 添加参数并且必须使用{@link OH_Huks_BuildParamSet}构造参数集。
 *
 * @param paramSet 指向要初始化的参数集的指针地址。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS = 0 ：初始化操作成功。
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY = 12000014 ：内存不足。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401 ：参数paramSet无效。
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_InitParamSet(struct OH_Huks_ParamSet **paramSet);

/**
 * @brief 添加参数到参数集里面。
 *
 * @param paramSet 指向要被添加参数的参数集的指针。
 * @param params 指向要添加的参数数组的指针。
 * @param paramCnt 待添加参数数组的参数个数。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS = 0 ：操作成功。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401 ：params为null或者paramSet无效。
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_AddParams(struct OH_Huks_ParamSet *paramSet,
    const struct OH_Huks_Param *params, uint32_t paramCnt);

/**
 * @brief 构造参数集，在初始化参数集和添加参数操作之后，序列化参数集，将blob类型的数据拷贝到paramSet结构尾部相邻内存区域。
 *
 * @param paramSet 指向要被正式构造的参数集的指针地址。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS = 0 ：操作成功。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401 ：参数paramSet无效。
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY = 12000014 ：内存不足。
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_BuildParamSet(struct OH_Huks_ParamSet **paramSet);

/**
 * @brief 销毁参数集。
 *
 * @param paramSet 指向要被销毁的参数集的指针地址。
 * @since 9
 * @version 1.0
 */
void OH_Huks_FreeParamSet(struct OH_Huks_ParamSet **paramSet);

/**
 * @brief 复制参数集（深拷贝）。
 *
 * @param fromParamSet 指向要被复制的参数集的指针。
 * @param fromParamSetSize 被复制的参数集占用内存的大小。
 * @param paramSet 指向生成新的参数集的指针地址。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS = 0 ：操作成功。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401 ：参数fromParamSet、fromParamSetSize、paramSet有一个无效。
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY = 12000014 ：内存不足。
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_CopyParamSet(const struct OH_Huks_ParamSet *fromParamSet,
    uint32_t fromParamSetSize, struct OH_Huks_ParamSet **paramSet);

/**
 * @brief 从参数集中获取参数。
 *
 * @param paramSet 指向参数集的指针。
 * @param tag 要获取的对应参数的值。
 * @param param 指向获取到的参数的指针地址。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS = 0 ：操作成功。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401 ：参数paramSet或者param无效，或者参数param不在paramSet里面。
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_GetParam(const struct OH_Huks_ParamSet *paramSet, uint32_t tag,
    struct OH_Huks_Param **param);

/**
 * @brief 刷新参数集内{@link OH_Huks_Blob}类型的数据。
 *
 * @param paramSet 指向参数集的指针。
 * @param isCopy 如果为true，刷新{@link OH_Huks_Blob}类型数据的地址并复制到参数集。如果为false，只会刷新{@link OH_Huks_Blob}类型数据的地址。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS = 0 ：操作成功。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401 ：参数paramSet无效。
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY = 12000014 ：内存不足。
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_FreshParamSet(struct OH_Huks_ParamSet *paramSet, bool isCopy);

/**
 * @brief 检查参数集中的参数是否有效、是否有重复。
 *
 * @param paramSet 指向参数集的指针。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS = 0 ：paramSet中的参数都有效。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401 ：参数paramSet无效或者参数集中有无效、重复、不正确的标签。
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_IsParamSetTagValid(const struct OH_Huks_ParamSet *paramSet);

/**
 * @brief 检查参数集大小是否有效。
 *
 * @param paramSet 指向参数集的指针。
 * @param size 参数集占用的内存大小。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS = 0 ：参数集大小合法。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401 ：参数paramSet无效。
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_IsParamSetValid(const struct OH_Huks_ParamSet *paramSet, uint32_t size);

/**
 * @brief 比较两个参数是否相同。
 *
 * @param baseParam 指向被比较的参数的指针。
 * @param param 指向比较的参数的指针。
 * @return 可能的返回码（errorCode）：
 *     <br>OH_HUKS_SUCCESS = 0 ：比较的两个参数相同。
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401 ：其中一个参数集是无效的，或者参数不匹配，
 *     <br>或者内部有无效标签。
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_CheckParamMatch(const struct OH_Huks_Param *baseParam, const struct OH_Huks_Param *param);

/**
 * @brief 销毁密钥别名的参数集。
 *
 * @param keyAliasSet 指向要被销毁的密钥别名的参数集的指针地址。
 * @since 20
 * @version 1.0
 */
void OH_Huks_FreeKeyAliasSet(struct OH_Huks_KeyAliasSet *keyAliasSet);
#ifdef __cplusplus
}
#endif

/** @} */
#endif /* NATIVE_HUKS_PARAM_H */
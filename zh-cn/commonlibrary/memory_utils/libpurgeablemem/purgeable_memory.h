/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup memory
 * @{
 *
 * @brief 提供内存管理功能
 *
 * 提供包括内存分配、内存释放等操作在内的功能
 *
 * @since 10
 * @version 1.0
 */

/**
 * @file purgeable_memory.h
 *
 * @brief 提供可丢弃内存的内存管理功能。
 * <br>提供的功能包括创建、开始读取、结束读取、开始写入、结束写入、重建等。
 * <br>使用时需要链接libpurgeable_memory_ndk.z.so。
 *
 * @library libpurgeable_memory_ndk.z.so
 * @syscap SystemCapability.Kernel.Memory
 * @kit KernelEnhanceKit
 * @since 10
 * @version 1.0
 */

#ifndef OHOS_UTILS_MEMORY_LIBPURGEABLEMEM_C_INCLUDE_PURGEABLE_MEMORY_H
#define OHOS_UTILS_MEMORY_LIBPURGEABLEMEM_C_INCLUDE_PURGEABLE_MEMORY_H

#include <stdbool.h> /* bool */
#include <stddef.h> /* size_t */

#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */

/**
 * @brief 可清除的内存结构。
 *
 * @since 10
 * @version 1.0
 */
typedef struct PurgMem OH_PurgeableMemory;

/**
 * @brief 函数指针，它指向一个用于构建可丢弃内存对象内容的函数。
 *
 *
 * @param void *: data ptr, points to start address of a PurgMem obj's content.
 * @param size_t 内容的数据大小。
 * @param void  *: 其他私有参数。
 * @return 构建内容结果，true 表示成功，false 表示失败。
 *
 * @since 10
 * @version 1.0
 */
typedef bool (*OH_PurgeableMemory_ModifyFunc)(void *, size_t, void *);

/**
 * @brief create 一个可丢弃内存对象的指针。
 *
 *
 * @param size 可丢弃内存对象内容的数据大小。
 * @param func 函数指针，用于在可丢弃内存对象的内容被清除时恢复数据。
 * @param funcPara func使用的参数。
 * @return 一个可丢弃内存对象的指针。
 *
 * @since 10
 * @version 1.0
 */
OH_PurgeableMemory *OH_PurgeableMemory_Create(
    size_t size, OH_PurgeableMemory_ModifyFunc func, void *funcPara);

/**
 * @brief 销毁一个可丢弃内存对象
 *
 *
 * @param purgObj 待销毁的可丢弃内存对象。
 * @return true 表示成功，false 表示失败。如果 purgObj 为 NULL，则返回 true。如果返回 true，purgObj 将被设置为 NULL 以避免释放后使用（Use-After-Free）。
 *
 * @since 10
 * @version 1.0
 */
bool OH_PurgeableMemory_Destroy(OH_PurgeableMemory *purgObj);

/**
 * @brief 开始读取可丢弃内存对象。
 *
 *
 * @param purgObj 可丢弃内存对象。
 * @return  如果 purgObj 的内容存在，则返回 true；
 *    如果内容已被清除（不存在），系统将尝试恢复其数据，如果内容已被清除且恢复失败，则返回 false，如果内容恢复成功，则返回 true；
 *    当此函数返回 true 时，操作系统无法回收 purgObj 内容的内存，直到调用 PurgMemEndRead()。
 *
 * @since 10
 * @version 1.0
 */
bool OH_PurgeableMemory_BeginRead(OH_PurgeableMemory *purgObj);

/**
 * @brief 结束读取可丢弃内存对象。
 *
 *
 * @param purgObj 可丢弃内存对象。当此函数执行结束，操作系统可能会稍后回收可丢弃内存对象的内容的内存。
 * @since 10
 * @version 1.0
 */
void OH_PurgeableMemory_EndRead(OH_PurgeableMemory *purgObj);

/**
 * @brief 开始写入可丢弃内存对象。
 *
 *
 * @param purgObj 可丢弃内存对象。
 * @return 如果 purgObj 的内容存在，则返回 true；
 *     如果内容已被清除（不存在），系统将尝试恢复其数据，如果内容已被清除且恢复失败，则返回 false，如果内容成功恢复，则返回 true；
 *     当此函数返回 true 时，操作系统无法回收 purgObj 内容的内存，直到调用 PurgMemEndWrite()。
 *
 * @since 10
 * @version 1.0
 */
bool OH_PurgeableMemory_BeginWrite(OH_PurgeableMemory *purgObj);

/**
 * @brief 结束写入可丢弃内存对象。
 *
 *
 * @param purgObj 可丢弃内存对象。当此函数执行结束时，操作系统可能会稍后回收可丢弃内存对象的内容的内存。
 * @since 10
 * @version 1.0
 */
void OH_PurgeableMemory_EndWrite(OH_PurgeableMemory *purgObj);

/**
 * @brief 获取可丢弃内存对象的内容指针。
 *
 *
 * @param purgObj 可丢弃内存对象。
 * @return 返回可丢弃内存对象内容的起始地址。
 *     如果 purgObj 为 NULL，则返回 NULL。
 *     此函数应受 PurgMemBeginRead()/PurgMemEndRead() 或 PurgMemBeginWrite()/PurgMemEndWrite() 保护。
 *
 * @since 10
 * @version 1.0
 */
void *OH_PurgeableMemory_GetContent(OH_PurgeableMemory *purgObj);

/**
 * @brief 获取可丢弃内存对象的内容大小。
 *
 *
 * @param purgObj 可丢弃内存对象。
 * @return 返回 purgObj 的内容大小。
 *     如果 purgObj 为 NULL，则返回 0。
 *
 * @since 10
 * @version 1.0
 */
size_t OH_PurgeableMemory_ContentSize(OH_PurgeableMemory *purgObj);

/**
 * @brief 向可丢弃内存对象追加修改。
 *
 *
 * @param purgObj 可丢弃内存对象。
 * @param func 函数指针，用于修改可丢弃内存对象的内容。
 * @param funcPara func 使用的参数。
 * @return 追加结果，true 表示成功，false 表示失败。
 *
 * @since 10
 * @version 1.0
 */
bool OH_PurgeableMemory_AppendModify(OH_PurgeableMemory *purgObj,
    OH_PurgeableMemory_ModifyFunc func, void *funcPara);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */
#endif /* OHOS_UTILS_MEMORY_LIBPURGEABLEMEM_C_INCLUDE_PURGEABLE_MEMORY_H */
/** @} */
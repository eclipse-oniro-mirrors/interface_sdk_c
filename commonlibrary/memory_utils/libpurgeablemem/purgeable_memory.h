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
 * @brief provides memory management capabilities
 *
 * provides features include operations such as memory alloction, memory free, and so on
 *
 * @since 10
 * @version 1.0
 */

/**
 * @file purgeable_memory.h
 *
 * @brief Provides APIs for managing the purgeable memory.
 * <br>For example, you can create a purgeable memory, start or end the memory reading/writing, and rebuild the memory.
 * <br>Link to the **libpurgeable_memory_ndk.z.so** file when you use the API.
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
 * @brief Defines a purgeable memory struct.
 *
 * @since 10
 * @version 1.0
 */
typedef struct PurgMem OH_PurgeableMemory;

/**
 * @brief function pointer, it points to a function which is used to build content of a PurgMem obj.
 *
 *
 * @param void *: data ptr, points to start address of a PurgMem obj's content.
 * @param size_t Data size of the content.
 * @param void *: other private parameters.
 * @return build content result, true means success, while false is fail.
 *
 * @since 10
 * @version 1.0
 */
typedef bool (*OH_PurgeableMemory_ModifyFunc)(void *, size_t, void *);

/**
 * @brief create a PurgMem obj.
 *
 *
 * @param size Data size of the content of a purgeable memory object.
 * @param func Function used to restore data when the content of a purgeable memory object is cleared.
 * @param funcPara Pointer to the parameter used by func.
 * @return a PurgMem obj.
 *
 * @since 10
 * @version 1.0
 */
OH_PurgeableMemory *OH_PurgeableMemory_Create(
    size_t size, OH_PurgeableMemory_ModifyFunc func, void *funcPara);

/**
 * @brief destroy a PurgMem obj.
 *
 *
 * @param purgObj Pointer to the purgeable memory object to be destroyed.
 * @return true is success, while false is fail. return true if purgObj is NULL.
 *      <br>If return true, purgObj will be set to NULL to avoid Use-After-Free.
 *
 * @since 10
 * @version 1.0
 */
bool OH_PurgeableMemory_Destroy(OH_PurgeableMemory *purgObj);

/**
 * @brief begin read a PurgMem obj.
 *
 *
 * @param purgObj Pointer to the purgeable memory object.
 * @return return true if purgObj's content is present.
 *     If content is purged(no present), system will recover its data,
 *     return false if content is purged and recovered failed.
 *     While return true if content recover success.
 *     OS cannot reclaim the memory of purgObj's content when this
 *     function return true, until PurgMemEndRead() is called.
 *
 * @since 10
 * @version 1.0
 */
bool OH_PurgeableMemory_BeginRead(OH_PurgeableMemory *purgObj);

/**
 * @brief end read a PurgMem obj.
 *
 *
 * @param purgObj Pointer to the purgeable memory object. When this function ends, the OS may reclaim the memory of the
 *     content of the purgeable memory object later.
 * @since 10
 * @version 1.0
 */
void OH_PurgeableMemory_EndRead(OH_PurgeableMemory *purgObj);

/**
 * @brief begin write a PurgMem obj.
 *
 *
 * @param purgObj Pointer to the purgeable memory object.
 * @return return true if purgObj's content is present.
 *     if content is purged(no present), system will recover its data,
 *     return false if content is purged and recovered failed.
 *     While return true if content is successfully recovered.
 *     OS cannot reclaim the memory of purgObj's content when this
 *     function return true, until PurgMemEndWrite() is called.
 *
 * @since 10
 * @version 1.0
 */
bool OH_PurgeableMemory_BeginWrite(OH_PurgeableMemory *purgObj);

/**
 * @brief end write a PurgMem obj.
 *
 *
 * @param purgObj Pointer to the purgeable memory object. When this function ends, the OS may reclaim the memory of the
 *     content of the purgeable memory object later.
 * @since 10
 * @version 1.0
 */
void OH_PurgeableMemory_EndWrite(OH_PurgeableMemory *purgObj);

/**
 * @brief get content ptr of a PurgMem obj.
 *
 *
 * @param purgObj Pointer to the purgeable memory object.
 * @return return start address of a PurgMem obj's content.
 *     <br>Return NULL if purgObj is NULL.
 *     <br>This function should be protect by PurgMemBeginRead()/PurgMemEndRead()
 *     or PurgMemBeginWrite()/PurgMemEndWrite()
 *
 * @since 10
 * @version 1.0
 */
void *OH_PurgeableMemory_GetContent(OH_PurgeableMemory *purgObj);

/**
 * @brief get content size of a PurgMem obj.
 *
 *
 * @param purgObj Pointer to the purgeable memory object.
 * @return return content size of purgObj.
 *     Return 0 if purgObj is NULL.
 *
 * @since 10
 * @version 1.0
 */
size_t OH_PurgeableMemory_ContentSize(OH_PurgeableMemory *purgObj);

/**
 * @brief append a modify to a PurgMem obj.
 *
 *
 * @param purgObj Pointer to the purgeable memory object.
 * @param func Function used to modify the content of a purgeable memory object.
 * @param funcPara Pointer to the parameter used by func.
 * @return  append result, true is success, while false is fail.
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
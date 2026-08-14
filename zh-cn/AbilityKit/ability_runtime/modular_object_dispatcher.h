/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with License.
 * You may obtain a copy of License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup AbilityRuntime
 * @{
 *
 * @brief 提供ModularObject调度器延迟绑定机制的C接口定义。
 *
 * @since 26.0.0
 */

/**
 * @file modular_object_dispatcher.h
 *
 * @brief 声明ModularObject分发器接口，提供基于类型库元数据的跨进程延迟绑定调用能力。
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 26.0.0
 */

#ifndef OHOS_ABILITY_RUNTIME_C_MOD_OBJ_DISPATCHER_H
#define OHOS_ABILITY_RUNTIME_C_MOD_OBJ_DISPATCHER_H

#include <stdbool.h>
#include "ability_runtime_common.h"
#include "IPCKit/ipc_cparcel.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义ModularObject分发器的类型描述符句柄。<br>该句柄指向类型库元数据的访问接口，可用于查询远端服务定义的接口、方法、枚举和结构体等信息。<br>可通过
 * {@link OH_AbilityRuntime_ModObjDispatcher_GetTypeDescriptor}获取，使用完毕后需通过
 * {@link OH_AbilityRuntime_TypeDescriptor_Release}释放。
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_ModularObjectDispatcher_TypeDescriptor*
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle;

 /**
  * @brief 定义变体类型枚举，用于标识变体值的数据类型。
  * <br>变体（Variant）是一种能够存储多种不同类型值的通用数据容器，类似于C语言的联合体（union）。每个变体在同一时刻只持有一种类型的值，通过本枚举值标识其实际存储的数据类型。
  * <br>在本模块中，变体用于方法调用的参数传递和返回值接收，使得同一套接口能够处理布尔、整数、浮点数、字符串、数组、向量、集合、映射、结构体、远端通信对象等多种数据类型。
  *
  * @since 26.0.0
  */
typedef enum {
    /**
     * @brief 空值。表示未初始化或无效的变体值。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_EMPTY = 0,
    /**
     * @brief void类型。用于方法不返回任何值。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_VOID = 1,
    /**
     * @brief 布尔值。取值为true或false，true表示真，false表示假。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_BOOL = 2,
    /**
     * @brief 8位有符号整数。取值范围：[-128, 127]。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_I8 = 3,
    /**
     * @brief 16位有符号整数。取值范围：[-32768, 32767]。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_I16 = 4,
    /**
     * @brief 32位有符号整数。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_I32 = 5,
    /**
     * @brief 64位有符号整数。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_I64 = 6,
    /**
     * @brief 8位无符号整数。取值范围：[0, 255]。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_U8 = 7,
    /**
     * @brief 16位无符号整数。取值范围：[0, 65535]。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_U16 = 8,
    /**
     * @brief 32位无符号整数。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_U32 = 9,
    /**
     * @brief 64位无符号整数。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_U64 = 10,
    /**
     * @brief 32位浮点数（单精度）。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_F32 = 11,
    /**
     * @brief 64位浮点数（双精度）。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_F64 = 12,
    /**
     * @brief UTF-8字符串。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_STRING = 13,
    /**
     * @brief 数组。固定大小的有序元素集合，所有元素类型相同，支持按索引设置获取元素和查询数组大小。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_ARRAY = 14,
    /**
     * @brief 向量。动态大小的有序元素集合，所有元素类型相同，支持添加元素、按索引获取元素、查询向量大小和清空操作。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_VECTOR = 15,
    /**
     * @brief 集合。不重复元素的无序集合，所有元素类型相同，支持添加元素、删除元素、查询指定元素是否存在、按索引获取元素、查询集合大小和清空操作。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_SET = 16,
    /**
     * @brief 映射。键值对的有序集合，键和值类型在创建时指定，支持添加或更新键值对、按键获取值、删除键值对、查询指定键是否存在、按索引获取键或值、查询映射大小和清空操作。键仅支持基本类型（BOOL、有符号整数、无符号整数、
     * 浮点数、STRING、ENUM），不支持容器类型和复杂类型。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_MAP = 17,
    /**
     * @brief 结构体。具名字段的集合，字段类型通过类型库元数据定义。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_STRUCT = 18,
    /**
     * @brief 用于跨进程通信的远端Proxy对象。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_IPC_REMOTE_PROXY = 19,
    /**
     * @brief 用于跨进程通信的远端Stub对象。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_IPC_REMOTE_STUB = 20,
    /**
     * @brief 枚举值。以int32_t形式存储，枚举定义可通过类型描述符查询。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_MOD_OBJ_DISPATCHER_VT_ENUM = 21,
} OH_AbilityRuntime_ModObjDispatcher_ValueType;

/**
 * @brief 定义参数或返回值的类型信息。<br>使用带标签的联合体u描述类型信息，通过vt字段决定联合体中哪个成员有效。<br>使用完毕后需调用
 * {@link OH_AbilityRuntime_ModObjDispatcher_TypeInfoClear}释放内部持有的堆资源。
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_ModObjDispatcher_TypeInfo {
    /**
     * @brief 类型标签，决定联合体中哪个成员有效。
     *
     * @since 26.0.0
     */
    OH_AbilityRuntime_ModObjDispatcher_ValueType vt;
    /**
     * @brief 类型特定的元数据联合体。有效的成员由vt决定。
     *
     * @since 26.0.0
     */
    union {
        /**
         * @brief 映射类型元数据，当vt为MAP时使用。
         *
         * @since 26.0.0
         */
        struct {
            /**
             * @brief 映射的键类型，仅支持基本类型（BOOL、有符号整数、无符号整数、浮点数、STRING、ENUM），
             * 不支持容器类型（ARRAY、VECTOR、SET、MAP）和复杂类型（STRUCT、IPC_REMOTE_PROXY、IPC_REMOTE_STUB）。
             *
             * @since 26.0.0
             */
            OH_AbilityRuntime_ModObjDispatcher_ValueType keyType;
            /**
             * @brief 值类型描述符的句柄，需通过TypeInfoClear释放。
             *
             * @since 26.0.0
             */
            OH_AbilityRuntime_ModObjDispatcher_TypeInfo *pValueType;
        } mapType;
        /**
         * @brief 数组类型元数据，当vt为ARRAY时使用。
         *
         * @since 26.0.0
         */
        struct {
            /**
             * @brief 元素类型描述符的句柄，需通过TypeInfoClear释放。
             *
             * @since 26.0.0
             */
            struct OH_AbilityRuntime_ModObjDispatcher_TypeInfo *pElementType;
            /**
             * @brief 数组的固定大小。
             * @since 26.0.0
             */
            uint32_t size;
        } arrayType;
        /**
         * @brief 元素类型描述符的句柄，当vt为VECTOR或SET时使用，需通过TypeInfoClear释放。
         *
         * @since 26.0.0
         */
        OH_AbilityRuntime_ModObjDispatcher_TypeInfo *pElementType;
        /**
         * @brief IDL类型名称字符串，当vt为STRUCT、IPC_REMOTE_PROXY、IPC_REMOTE_STUB、ENUM时使用，需通过TypeInfoClear释放。
         *
         * @since 26.0.0
         */
        char* idlType;
    } u;
} OH_AbilityRuntime_ModObjDispatcher_TypeInfo;

/**
 * @brief ModularObject分发器的句柄。<br>该句柄指向一个ModularObject分发器实例，可通过
 * {@link OH_AbilityRuntime_ModObjDispatcher_CreateMainServiceInstance}或
 * {@link OH_AbilityRuntime_ModObjDispatcher_CreateSubInstance}创建，使用完毕后需通过
 * {@link OH_AbilityRuntime_ModObjDispatcher_Release}释放。
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_ModularObjectDispatcher* OH_AbilityRuntime_ModObjDispatcherHandle;

/**
 * @brief 数组句柄。<br>该句柄指向一个固定大小的有序元素集合，所有元素类型相同，支持按索引设置获取元素和查询数组大小。<br>可通过
 * {@link OH_AbilityRuntime_ModObjDispatcher_ArrayCreate}创建，使用完毕后需通过
 * {@link OH_AbilityRuntime_ModObjDispatcher_ArrayRelease}释放。
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_ModularObjectDispatcher_Array* OH_AbilityRuntime_ModObjDispatcher_ArrayHandle;

/**
 * @brief 向量句柄。<br>该句柄指向一个动态大小的有序元素集合，所有元素类型相同，支持添加元素、按索引获取元素、查询向量大小和清空操作。<br>可通过
 * {@link OH_AbilityRuntime_ModObjDispatcher_VectorCreate}创建，使用完毕后需通过
 * {@link OH_AbilityRuntime_ModObjDispatcher_VectorRelease}释放。
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_ModularObjectDispatcher_Vector* OH_AbilityRuntime_ModObjDispatcher_VectorHandle;

/**
 * @brief 集合句柄。<br>该句柄指向一个不重复元素的无序集合，所有元素类型相同，支持添加元素、删除元素、查询指定元素是否存在、按索引获取元素、查询集合大小和清空操作。<br>可通过
 * {@link OH_AbilityRuntime_ModObjDispatcher_SetCreate}创建，使用完毕后需通过{@link OH_AbilityRuntime_ModObjDispatcher_SetRelease}
 * 释放。
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_ModularObjectDispatcher_Set* OH_AbilityRuntime_ModObjDispatcher_SetHandle;

/**
 * @brief 映射句柄。<br>该句柄指向一个键值对的有序集合，键和值类型在创建时指定，支持添加或更新键值对、按键获取值、删除键值对、查询指定键是否存在、按索引获取键或值、查询映射大小和清空操作。<br>键仅支持基本类型（BOOL、
 * 有符号整数、无符号整数、浮点数、STRING、ENUM）。<br>可通过{@link OH_AbilityRuntime_ModObjDispatcher_MapCreate}创建，使用完毕后需通过
 * {@link OH_AbilityRuntime_ModObjDispatcher_MapRelease}释放。
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_ModularObjectDispatcher_Map* OH_AbilityRuntime_ModObjDispatcher_MapHandle;

/**
 * @brief 结构体句柄。<br>该句柄指向一个具名字段的结构体实例，字段类型通过类型库元数据定义。<br>可通过{@link OH_AbilityRuntime_ModObjDispatcher_StructCreate}创建，
 * 使用完毕后需通过{@link OH_AbilityRuntime_ModObjDispatcher_StructRelease}释放。
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_ModularObjectDispatcher_Struct* OH_AbilityRuntime_ModObjDispatcher_StructHandle;

/**
 * @brief 定义使用联合体加类型标签的变体结构，通过类型标签区分实际数据类型，用于在参数传递和返回值接收中安全传递多种类型的值。<br>变体值由vt字段决定实际存储的数据类型和联合体中有效的成员。<br>当变体持有堆分配资源（
 * 如字符串、容器句柄）时，需调用{@link OH_AbilityRuntime_ModObjDispatcher_VariantClear}释放。<br>简单类型（布尔、整数、浮点数）不持有堆资源，
 * 无需调用VariantClear释放。
 *
 * @since 26.0.0
 */
typedef struct {
    /**
     * @brief 变体类型标签，决定联合体中有效的成员。
     * @since 26.0.0
     */
    OH_AbilityRuntime_ModObjDispatcher_ValueType vt;
    /**
     * @brief 保留字段1。预留空间供后续版本扩展使用，调用方应将其初始化为0，且不应读取或修改。
     * @since 26.0.0
     */
    uint64_t reserved1;
    /**
     * @brief 保留字段2。预留空间供后续版本扩展使用，调用方应将其初始化为0，且不应读取或修改。
     * @since 26.0.0
     */
    uint64_t reserved2;
    /**
     * @brief 保留字段3。预留空间供后续版本扩展使用，调用方应将其初始化为0，且不应读取或修改。
     * @since 26.0.0
     */
    uint64_t reserved3;
    /**
     * @brief 变体值数据联合体。有效的成员由vt决定。
     * @since 26.0.0
     */
    union {
        /**
         * @brief 空值句柄。
         * @since 26.0.0
         */
        void *pvoidVal;
        /**
         * @brief 布尔值。
         * @since 26.0.0
         */
        bool boolVal;
        /**
         * @brief 8位有符号整数。
         * @since 26.0.0
         */
        int8_t i8Val;
        /**
         * @brief 16位有符号整数。
         * @since 26.0.0
         */
        int16_t i16Val;
        /**
         * @brief 32位有符号整数。
         * @since 26.0.0
         */
        int32_t i32Val;
        /**
         * @brief 64位有符号整数。
         * @since 26.0.0
         */
        int64_t i64Val;
        /**
         * @brief 8位无符号整数。
         * @since 26.0.0
         */
        uint8_t u8Val;
        /**
         * @brief 16位无符号整数。
         * @since 26.0.0
         */
        uint16_t u16Val;
        /**
         * @brief 32位无符号整数。
         * @since 26.0.0
         */
        uint32_t u32Val;
        /**
         * @brief 64位无符号整数。
         * @since 26.0.0
         */
        uint64_t u64Val;
        /**
         * @brief 32位浮点数（单精度）。
         * @since 26.0.0
         */
        float f32Val;
        /**
         * @brief 64位浮点数（双精度）。
         * @since 26.0.0
         */
        double f64Val;
        /**
         * @brief 枚举值，以int32_t形式存储。
         * @since 26.0.0
         */
        int32_t enumVal;
        /**
         * @brief UTF-8字符串句柄，指向堆分配的字符串。
         * @since 26.0.0
         */
        char* bstrVal;
        /**
         * @brief 数组句柄。
         * @since 26.0.0
         */
        OH_AbilityRuntime_ModObjDispatcher_ArrayHandle parrayVal;
        /**
         * @brief 向量句柄。
         * @since 26.0.0
         */
        OH_AbilityRuntime_ModObjDispatcher_VectorHandle pvectorVal;
        /**
         * @brief 集合句柄。
         * @since 26.0.0
         */
        OH_AbilityRuntime_ModObjDispatcher_SetHandle psetVal;
        /**
         * @brief 映射句柄。
         * @since 26.0.0
         */
        OH_AbilityRuntime_ModObjDispatcher_MapHandle pmapVal;
        /**
         * @brief 结构体句柄。
         * @since 26.0.0
         */
        OH_AbilityRuntime_ModObjDispatcher_StructHandle pstructVal;
        /**
         * @brief 远端Proxy对象句柄。
         * @since 26.0.0
         */
        OHIPCRemoteProxy *premoteProxyVal;
        /**
         * @brief 远端Stub对象句柄。
         * @since 26.0.0
         */
        OHIPCRemoteStub *premoteStubVal;
    } u;
} OH_AbilityRuntime_ModObjDispatcher_Variant;

/**
 * @brief 定义方法调用的参数结构。rgvarg指向参数变体数组，数组长度由cArgs指定。参数顺序应与方法定义中的参数顺序一致。
 *
 * @since 26.0.0
 */
typedef struct {
    /**
     * @brief 参数变体数组。
     * @since 26.0.0
     */
    OH_AbilityRuntime_ModObjDispatcher_Variant* rgvarg;
    /**
     * @brief 参数数量。
     * @since 26.0.0
     */
    uint32_t cArgs;
} OH_AbilityRuntime_ModObjDispatcher_InputParams;

/**
 * @brief 清理TypeInfo结构体持有的堆资源。
 * <br>递归释放TypeInfo持有的堆资源。清理后，所有内部指针被置为NULL，vt被重置为VT_EMPTY，但TypeInfo结构体本身不会被释放（通常由调用方在栈上分配）。
 * <br>各类型持有的堆资源：
 * - 映射（MAP）类型：递归释放并删除由new分配的子TypeInfo节点（u.mapType.pValueType）。
 * - 数组（ARRAY）类型：递归释放并删除由new分配的子TypeInfo节点（u.arrayType.pElementType）。
 * - 向量（VECTOR）或集合（SET）类型：递归释放并删除由new分配的子TypeInfo节点（u.pElementType）。
 * - 结构体（STRUCT）、枚举（ENUM）、远端通信对象（IPC_REMOTE_PROXY、IPC_REMOTE_STUB）类型：释放u.idlType字符串（由strdup分配）。
 * <br>释放规则：
 * - 当TypeInfo从函数返回（如{@link OH_AbilityRuntime_TypeDescriptor_GetMethodReturnType}、
 * {@link OH_AbilityRuntime_TypeDescriptor_GetMethodParamType}、
 * {@link OH_AbilityRuntime_TypeDescriptor_GetStructFieldType}、
 * {@link OH_AbilityRuntime_ModObjDispatcher_ArrayGetElementType}、
 * {@link OH_AbilityRuntime_ModObjDispatcher_VectorGetElementType}、
 * {@link OH_AbilityRuntime_ModObjDispatcher_SetGetElementType}、
 * {@link OH_AbilityRuntime_ModObjDispatcher_MapGetValueType}）时，
 * 函数执行深拷贝，调用方获得返回TypeInfo的所有权，必须调用此接口释放资源。
 * - 当TypeInfo被传入函数（如{@link OH_AbilityRuntime_ModObjDispatcher_ArrayCreate}、
 * {@link OH_AbilityRuntime_ModObjDispatcher_VectorCreate}、
 * {@link OH_AbilityRuntime_ModObjDispatcher_SetCreate}、{@link OH_AbilityRuntime_ModObjDispatcher_MapCreate}）时，
 * 函数执行深拷贝，调用方保留原始TypeInfo的所有权，需自行调用此接口释放原始TypeInfo持有的资源。
 * - 简单类型（布尔、整数、浮点数、空值等）不持有堆资源，无需调用此接口释放。
 * - 禁止对TypeInfo的浅拷贝调用此接口。如果执行了 TypeInfo t2 = t1，只能清理其中一个。
 *
 * @param pTypeInfo 指向待清理的TypeInfo的指针。
 * @since 26.0.0
 */
void OH_AbilityRuntime_ModObjDispatcher_TypeInfoClear(
    OH_AbilityRuntime_ModObjDispatcher_TypeInfo* pTypeInfo);

/**
 * @brief 清理变体持有的资源。
 * <br>释放变体持有的资源（字符串、容器句柄等），清理后变体被重置为VT_EMPTY，所有字段归零。
 * <br>释放规则：
 * - 当变体被传入函数（如{@link OH_AbilityRuntime_ModObjDispatcher_ArraySet}、{@link OH_AbilityRuntime_ModObjDispatcher_MapPut}）时，
 * 函数执行深拷贝，调用方保留原始变体的所有权，需自行释放原始变体持有的资源（如字符串需调用free(bstrVal)、容器句柄需调用对应的Release接口）。
 * - 当变体从函数返回（如{@link OH_AbilityRuntime_ModObjDispatcher_ArrayGet}、{@link OH_AbilityRuntime_ModObjDispatcher_MapGet}、
 * {@link OH_AbilityRuntime_ModObjDispatcher_CallMethod}）时，函数执行深拷贝，调用方获得返回变体的所有权，必须调用此接口释放资源。
 * - 简单类型（布尔、整数、浮点数等）不持有堆资源，无需调用此接口释放。
 * - 禁止对变体的浅拷贝调用此接口。如果执行了 Variant v2 = v1，只能清理其中一个。
 *
 * @param pVariant 指向待清理的变体的指针。
 * @since 26.0.0
 */
void OH_AbilityRuntime_ModObjDispatcher_VariantClear(
    OH_AbilityRuntime_ModObjDispatcher_Variant* pVariant);

/**
 * @brief 从远端Proxy对象为主服务接口创建ModularObject分发器实例。
 * <br>类型库元数据将在首次需要时从远端服务延迟加载（如调用{@link OH_AbilityRuntime_ModObjDispatcher_GetTypeDescriptor}、
 * {@link OH_AbilityRuntime_ModObjDispatcher_HasTypeDescriptor}、
 * {@link OH_AbilityRuntime_ModObjDispatcher_QueryMainServiceInterfaceMemIDsOfNames}或
 * {@link OH_AbilityRuntime_ModObjDispatcher_CallMethod}时触发）。
 * <br>调用方需在不再使用时调用{@link OH_AbilityRuntime_ModObjDispatcher_Release}释放分发器实例，避免内存泄漏。
 *
 * @param remoteProxy 远端Proxy对象句柄，通过连接ModularObjectExtensionAbility获取。
 * @param ppModObjDispatcher 指向接收ModularObject分发器句柄的指针，不能为NULL，且*ppModObjDispatcher必须为NULL。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} remoteProxy或ppModObjDispatcher为NULL，
 *     或ppModObjDispatcher不为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误，如内存分配失败。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_CreateMainServiceInstance(
    OHIPCRemoteProxy* remoteProxy, OH_AbilityRuntime_ModObjDispatcherHandle* ppModObjDispatcher);

/**
 * @brief 创建绑定到主服务分发器的子实例分发器。
 * <br>子实例共享主服务分发器的类型库元数据，但使用独立的IPC代理发送请求。适用于需要调用同一类型库中非主服务接口的场景。
 * <br>当在子实例上调用{@link OH_AbilityRuntime_ModObjDispatcher_CallMethod}时，方法签名从主服务分发器的类型库元数据中解析，IPC请求通过subProxy发送到远端服务。
 * <br>调用方需在不再使用时调用{@link OH_AbilityRuntime_ModObjDispatcher_Release}释放子实例，避免内存泄漏。
 *
 * @param mainServiceDispatcher 主服务分发器句柄。
 * @param subProxy 非主服务接口的远端Proxy对象句柄。
 * @param ppModObjDispatcher 指向接收创建的子实例分发器句柄的指针，不能为NULL，且*ppModObjDispatcher必须为NULL。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} mainServiceDispatcher、subProxy或ppModObjDispatcher为NULL，
 *     或ppModObjDispatcher不为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误，如内存分配失败。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_CreateSubInstance(
    OH_AbilityRuntime_ModObjDispatcherHandle mainServiceDispatcher,
    OHIPCRemoteProxy* subProxy, OH_AbilityRuntime_ModObjDispatcherHandle* ppModObjDispatcher);

/**
 * @brief 释放ModularObject分发器实例。释放后指针将被置为NULL。如果ppModObjDispatcher或*ppModObjDispatcher为NULL，则不执行任何操作。
 *
 * @param ppModObjDispatcher 指向待释放的ModularObject分发器句柄的指针。释放后该指针将被置为NULL。
 * @since 26.0.0
 */
void OH_AbilityRuntime_ModObjDispatcher_Release(OH_AbilityRuntime_ModObjDispatcherHandle* ppModObjDispatcher);

/**
 * @brief 检查远端服务是否支持类型库元数据。调用此接口将触发类型库元数据的延迟加载。如果元数据加载成功，*pctinfo 为 1；否则为 0。
 *
 * @param pModObjDispatcher ModularObject分发器句柄。
 * @param pctinfo 指向接收支持类型库元数据状态的指针。1表示支持，0表示不支持。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pModObjDispatcher或pctinfo为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_SEND_REQUEST_FAILED} IPC请求发送失败。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_METADATA_INVALID} 类型库元数据无效。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_HasTypeDescriptor(
    OH_AbilityRuntime_ModObjDispatcherHandle pModObjDispatcher, uint32_t* pctinfo);

/**
 * @brief 获取类型描述符句柄，用于查询接口元数据信息。
 * <br>类型描述符提供对远端服务类型库元数据的访问能力，包括接口、方法、枚举和结构体的定义信息。调用此接口将触发类型库元数据的延迟加载。
 * <br>使用完毕后需调用{@link OH_AbilityRuntime_TypeDescriptor_Release}释放句柄。
 *
 * @param pModObjDispatcher ModularObject分发器句柄。
 * @param ppTypeDescriptor 指向接收类型描述符句柄的指针，不能为NULL，且*ppTypeDescriptor必须为NULL。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pModObjDispatcher或ppTypeDescriptor为NULL，
 *     或ppTypeDescriptor不为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_SEND_REQUEST_FAILED} IPC请求发送失败。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_METADATA_INVALID} 类型库元数据无效。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_GetTypeDescriptor(
    OH_AbilityRuntime_ModObjDispatcherHandle pModObjDispatcher,
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle* ppTypeDescriptor);

/**
 * @brief 根据方法名称查询主服务接口中对应的方法成员ID（MemberID）。返回的成员ID可作为{@link OH_AbilityRuntime_ModObjDispatcher_CallMethod}的memID参数使用。
 * 调用此接口将触发类型库元数据的延迟加载。
 *
 * @param pModObjDispatcher ModularObject分发器句柄。
 * @param rgszNames 方法名称数组。
 * @param cNames 方法名称数量。
 * @param pMemID 指向接收成员ID数组的指针。数组长度与cNames相同，每个名称对应一个成员ID。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pModObjDispatcher、rgszNames或pMemID为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_SEND_REQUEST_FAILED} IPC请求发送失败。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_METADATA_INVALID} 类型库元数据无效。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 方法名称未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_QueryMainServiceInterfaceMemIDsOfNames(
    OH_AbilityRuntime_ModObjDispatcherHandle pModObjDispatcher, const char** rgszNames, uint32_t cNames,
    uint32_t* pMemID);

/**
 * @brief 通过成员ID（MemberID）调用远端方法。
 * <br>调用流程：通过memID从元数据管理器获取方法元数据（方法名、参数类型、返回类型、IPC码等），将参数序列化到MessageParcel，通过IPC发送请求到远端服务，最后反序列化返回结果。
 * <br>本接口采用双层错误处理机制：
 *
 * @param pModObjDispatcher ModularObject分发器句柄。
 * @param memID 方法成员ID（MemberID），可通过{@link OH_AbilityRuntime_ModObjDispatcher_QueryMainServiceInterfaceMemIDsOfNames}或
 *     {@link OH_AbilityRuntime_TypeDescriptor_GetMethodMemberId}获取。
 * @param pInputParams 指向包含调用参数的结构体。
 * @param pResult 指向接收返回结果变体的指针。返回的变体是深拷贝，调用方需调用{@link OH_AbilityRuntime_ModObjDispatcher_VariantClear}释放。
 * @param pMethodErrCode 指向接收方法级错误码的指针。0表示方法执行成功，非零表示方法返回错误，该错误码独立于框架级返回值。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pModObjDispatcher、pInputParams或pResult为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 方法未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_TYPE_MISMATCH} 参数类型与元数据定义不匹配。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_SEND_REQUEST_FAILED} IPC请求发送失败。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_METADATA_INVALID} 类型库元数据无效。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_CallMethod(
    OH_AbilityRuntime_ModObjDispatcherHandle pModObjDispatcher, uint32_t memID,
    OH_AbilityRuntime_ModObjDispatcher_InputParams* pInputParams,
    OH_AbilityRuntime_ModObjDispatcher_Variant* pResult,
    int32_t* pMethodErrCode);

// ========== TypeDescriptor Interfaces ==========

/**
 * @brief 释放类型描述符实例。释放后句柄将被置为NULL。如果pTypeDescriptor或*pTypeDescriptor为NULL，则不执行任何操作。
 *
 * @param pTypeDescriptor 指向待释放的类型描述符句柄的指针。释放后该指针将被置为NULL。
 * @since 26.0.0
 */
void OH_AbilityRuntime_TypeDescriptor_Release(OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle *pTypeDescriptor);

/**
 * @brief 获取类型库版本号。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrVersion 指向接收版本字符串的缓冲区。
 * @param cMaxVersion 缓冲区大小（字节），包括空终止符。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor或pbstrVersion为NULL，或cMaxVersion为0。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetVersion(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, char* pbstrVersion, uint32_t cMaxVersion);

/**
 * @brief 获取类型库中定义的接口总数。返回的数量可用于确定遍历接口时的索引上限。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pcInterfaces 指向接收接口总数的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor或pcInterfaces为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetInterfaceCount(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, uint32_t* pcInterfaces);

/**
 * @brief 根据索引获取接口名称。接口索引的有效范围为[0, interfaceCount - 1]，其中interfaceCount可通过
 * {@link OH_AbilityRuntime_TypeDescriptor_GetInterfaceCount}获取。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param index 接口索引。
 * @param pbstrName 指向接收接口名称的缓冲区。
 * @param cMaxName 缓冲区大小（字节），包括空终止符。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor或pbstrName为NULL，或cMaxName为0，或index超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetInterfaceName(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, uint32_t index,
    char* pbstrName, uint32_t cMaxName);

/**
 * @brief 检查指定接口是否为回调类型。回调接口表示该接口需要客户端实现并提供给服务端调用。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrName 接口名称。
 * @param pIsCallback 指向接收回调标志的指针。true表示是回调接口，false表示不是。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrName或pIsCallback为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 接口未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetInterfaceIsCallback(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, const char* pbstrName, bool* pIsCallback);

/**
 * @brief 获取主服务接口名称。
 * <br>主服务接口是远端ModularObjectExtensionAbility对外暴露的默认接口，即通过
 * {@link OH_AbilityRuntime_ModObjDispatcher_CreateMainServiceInstance}创建分发器时所绑定Proxy对象对应的接口。
 * <br>该接口由远端服务在类型库元数据中声明，可通过本接口获取其名称。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrName 指向接收主服务接口名称的缓冲区。
 * @param cMaxName 缓冲区大小（字节），包括空终止符。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor或pbstrName为NULL，或cMaxName为0。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetMainServiceInterfaceName(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, char* pbstrName, uint32_t cMaxName);

/**
 * @brief 获取指定接口中定义的方法总数。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrInterfaceName 接口名称。
 * @param pcMethods 指向接收方法总数的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrInterfaceName或pcMethods为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 接口未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetMethodCount(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor,
    const char* pbstrInterfaceName, uint32_t* pcMethods);

/**
 * @brief 根据索引获取接口中的方法名称。方法索引的有效范围为[0, methodCount - 1]，其中methodCount可通过
 * {@link OH_AbilityRuntime_TypeDescriptor_GetMethodCount}获取。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrInterfaceName 接口名称。
 * @param index 方法索引。
 * @param pbstrName 指向接收方法名称的缓冲区。
 * @param cMaxName 缓冲区大小（字节），包括空终止符。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrInterfaceName或pbstrName为NULL，
 *     或cMaxName为0，或index超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 接口未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetMethodName(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor,
    const char* pbstrInterfaceName, uint32_t index, char* pbstrName, uint32_t cMaxName);

/**
 * @brief 根据方法名称获取方法的成员ID（MemberID）。返回的成员ID可作为{@link OH_AbilityRuntime_ModObjDispatcher_CallMethod}的memID参数使用。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrInterfaceName 接口名称。
 * @param pbstrMethodName 方法名称。
 * @param pMemID 指向接收方法成员ID的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrInterfaceName、
 *     pbstrMethodName或pMemID为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 接口或方法未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetMethodMemberId(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor,
    const char* pbstrInterfaceName, const char* pbstrMethodName, uint32_t* pMemID);

/**
 * @brief 获取方法的返回类型。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrInterfaceName 接口名称。
 * @param pbstrMethodName 方法名称。
 * @param pReturnType 指向接收返回类型的TypeInfo的指针。使用完毕后需调用{@link OH_AbilityRuntime_ModObjDispatcher_TypeInfoClear}释放。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrInterfaceName、
 *     pbstrMethodName或pReturnType为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 接口或方法未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetMethodReturnType(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor,
    const char* pbstrInterfaceName, const char* pbstrMethodName,
    OH_AbilityRuntime_ModObjDispatcher_TypeInfo* pReturnType);

/**
 * @brief 获取方法的参数数量。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrInterfaceName 接口名称。
 * @param pbstrMethodName 方法名称。
 * @param pcParams 指向接收参数数量的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrInterfaceName、
 *     pbstrMethodName或pcParams为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 接口或方法未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetMethodParamCount(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor,
    const char* pbstrInterfaceName, const char* pbstrMethodName, uint32_t* pcParams);

/**
 * @brief 根据索引获取方法参数的类型。参数索引的有效范围为[0, paramCount - 1]，其中paramCount可通过
 * {@link OH_AbilityRuntime_TypeDescriptor_GetMethodParamCount}获取。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrInterfaceName 接口名称。
 * @param pbstrMethodName 方法名称。
 * @param iParamIndex 参数索引。
 * @param pParamType 指向接收参数类型的TypeInfo的指针。使用完毕后需调用{@link OH_AbilityRuntime_ModObjDispatcher_TypeInfoClear}释放。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrInterfaceName、
 *     pbstrMethodName或pParamType为NULL，或iParamIndex超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 接口或方法未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetMethodParamType(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor,
    const char* pbstrInterfaceName, const char* pbstrMethodName,
    uint32_t iParamIndex, OH_AbilityRuntime_ModObjDispatcher_TypeInfo* pParamType);

/**
 * @brief 根据索引获取方法参数的名称。参数索引的有效范围为[0, paramCount - 1]，其中paramCount可通过
 * {@link OH_AbilityRuntime_TypeDescriptor_GetMethodParamCount}获取。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrInterfaceName 接口名称。
 * @param pbstrMethodName 方法名称。
 * @param iParamIndex 参数索引。
 * @param pbstrName 指向接收参数名称的缓冲区。
 * @param cMaxName 缓冲区大小（字节），包括空终止符。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrInterfaceName、
 *     pbstrMethodName或pbstrName为NULL，或iParamIndex超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 接口或方法未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetMethodParamName(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor,
    const char* pbstrInterfaceName, const char* pbstrMethodName,
    uint32_t iParamIndex, char* pbstrName, uint32_t cMaxName);

// ========== Enum Queries ==========

/**
 * @brief 获取类型库中定义的枚举总数。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pcEnums 指向接收枚举总数的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor或pcEnums为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetEnumCount(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, uint32_t* pcEnums);

/**
 * @brief 根据索引获取枚举名称。枚举索引的有效范围为[0, enumCount - 1]，其中enumCount可通过{@link OH_AbilityRuntime_TypeDescriptor_GetEnumCount}获取。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param index 枚举索引。
 * @param pbstrName 指向接收枚举名称的缓冲区。
 * @param cMaxName 缓冲区大小（字节），包括空终止符。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor或pbstrName为NULL，或cMaxName为0，或index超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetEnumName(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, uint32_t index,
    char* pbstrName, uint32_t cMaxName);

/**
 * @brief 获取指定枚举中定义的枚举值数量。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrEnumName 枚举名称。
 * @param pcValues 指向接收枚举值数量的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrEnumName或pcValues为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 枚举未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetEnumValueCount(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, const char* pbstrEnumName,
    uint32_t* pcValues);

/**
 * @brief 根据索引获取枚举值的名称。枚举值索引的有效范围为[0, valueCount - 1]，其中valueCount可通过
 * {@link OH_AbilityRuntime_TypeDescriptor_GetEnumValueCount}获取。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrEnumName 枚举名称。
 * @param iValueIndex 枚举值索引。
 * @param pbstrValueName 指向接收枚举值名称的缓冲区。
 * @param cMaxName 缓冲区大小（字节），包括空终止符。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrEnumName或pbstrValueName为NULL，
 *     或iValueIndex超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 枚举未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetEnumValueName(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, const char* pbstrEnumName,
    uint32_t iValueIndex, char* pbstrValueName, uint32_t cMaxName);

/**
 * @brief 根据枚举值名称获取枚举值。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrEnumName 枚举名称。
 * @param pbstrValueName 枚举值名称。
 * @param pValue 指向接收枚举值的指针。枚举值以int32_t形式返回。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrEnumName、pbstrValueName或pValue为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 枚举值未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetEnumValue(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, const char* pbstrEnumName,
    const char* pbstrValueName, int32_t* pValue);

/**
 * @brief 获取类型库中定义的结构体总数。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pcStructs 指向接收结构体总数的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor或pcStructs为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetStructCount(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, uint32_t* pcStructs);

/**
 * @brief 根据索引获取结构体名称。结构体索引的有效范围为[0, structCount - 1]，其中structCount可通过
 * {@link OH_AbilityRuntime_TypeDescriptor_GetStructCount}获取。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param index 结构体索引。
 * @param pbstrName 指向接收结构体名称的缓冲区。
 * @param cMaxName 缓冲区大小（字节），包括空终止符。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor或pbstrName为NULL，或cMaxName为0，或index超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetStructName(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, uint32_t index,
    char* pbstrName, uint32_t cMaxName);

/**
 * @brief 获取指定结构体中定义的字段数量。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrStructName 结构体名称。
 * @param pcFields 指向接收字段数量的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrStructName或pcFields为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 结构体未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetStructFieldCount(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, const char* pbstrStructName,
    uint32_t* pcFields);

/**
 * @brief 根据索引获取结构体字段的名称。结构体字段索引的有效范围为[0, fieldCount - 1]，其中fieldCount可通过
 * {@link OH_AbilityRuntime_TypeDescriptor_GetStructFieldCount}获取。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrStructName 结构体名称。
 * @param iFieldIndex 结构体字段索引。
 * @param pbstrFieldName 指向接收字段名称的缓冲区。
 * @param cMaxName 缓冲区大小（字节），包括空终止符。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrStructName或pbstrFieldName为NULL，
 *     或iFieldIndex超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 结构体未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetStructFieldName(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, const char* pbstrStructName,
    uint32_t iFieldIndex, char* pbstrFieldName, uint32_t cMaxName);

/**
 * @brief 根据字段名称获取结构体字段的类型。
 *
 * @param pTypeDescriptor 类型描述符句柄。
 * @param pbstrStructName 结构体名称。
 * @param pbstrFieldName 字段名称。
 * @param pFieldType 指向接收字段类型的TypeInfo的指针。使用完毕后需调用{@link OH_AbilityRuntime_ModObjDispatcher_TypeInfoClear}释放。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pTypeDescriptor、pbstrStructName、
 *     pbstrFieldName或pFieldType为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 结构体或字段未找到。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_TypeDescriptor_GetStructFieldType(
    OH_AbilityRuntime_ModObjDispatcher_TypeDescriptorHandle pTypeDescriptor, const char* pbstrStructName,
    const char* pbstrFieldName, OH_AbilityRuntime_ModObjDispatcher_TypeInfo* pFieldType);

/**
 * @brief 创建指定元素类型和大小的数组实例。数组为固定大小，创建后不可改变长度。
 *
 * @param elementType 指向元素类型描述符的指针。
 * @param size 数组的初始大小。
 * @param ppArray 指向接收数组句柄的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} elementType或ppArray为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_ArrayCreate(
    OH_AbilityRuntime_ModObjDispatcher_TypeInfo *elementType, uint32_t size,
    OH_AbilityRuntime_ModObjDispatcher_ArrayHandle* ppArray);

/**
 * @brief 获取数组的元素类型。
 *
 * @param pArray 数组句柄。
 * @param pElementType 指向接收元素类型的TypeInfo的指针。使用完毕后需调用{@link OH_AbilityRuntime_ModObjDispatcher_TypeInfoClear}释放。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pArray或pElementType为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_ArrayGetElementType(
    OH_AbilityRuntime_ModObjDispatcher_ArrayHandle pArray, OH_AbilityRuntime_ModObjDispatcher_TypeInfo* pElementType);

/**
 * @brief 设置数组中指定索引位置的元素值。函数会执行深拷贝，调用方保留原始变体的所有权。
 *
 * @param pArray 数组句柄。
 * @param index 元素索引，范围为[0, size - 1]。
 * @param pValue 指向元素值变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pArray或pValue为NULL，或index超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_TYPE_MISMATCH} 元素类型与数组定义的类型不匹配。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_ArraySet(
    OH_AbilityRuntime_ModObjDispatcher_ArrayHandle pArray, uint32_t index,
    const OH_AbilityRuntime_ModObjDispatcher_Variant* pValue);

/**
 * @brief 获取数组中指定索引位置的元素值。返回的变体是深拷贝，调用方拥有返回变体的所有权，需调用{@link OH_AbilityRuntime_ModObjDispatcher_VariantClear}释放。
 *
 * @param pArray 数组句柄。
 * @param index 元素索引，范围为[0, size - 1]。
 * @param pValue 指向接收元素值变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pArray或pValue为NULL，或index超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_ArrayGet(
    OH_AbilityRuntime_ModObjDispatcher_ArrayHandle pArray, uint32_t index,
    OH_AbilityRuntime_ModObjDispatcher_Variant* pValue);

/**
 * @brief 获取数组的大小。
 *
 * @param pArray 数组句柄。
 * @param pSize 指向接收数组大小的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pArray或pSize为NULL。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_ArrayGetSize(
    OH_AbilityRuntime_ModObjDispatcher_ArrayHandle pArray, uint32_t* pSize);

/**
 * @brief 释放数组实例。释放后句柄将被置为NULL。如果ppArray或*ppArray为NULL，则不执行任何操作。
 *
 * @param ppArray 指向待释放的数组句柄的指针。释放后该指针将被置为NULL。
 * @since 26.0.0
 */
void OH_AbilityRuntime_ModObjDispatcher_ArrayRelease(OH_AbilityRuntime_ModObjDispatcher_ArrayHandle* ppArray);

/**
 * @brief 创建指定元素类型的向量实例。向量为动态大小的有序集合，所有元素类型相同，支持添加元素、按索引获取元素、查询大小和清空。
 *
 * @param elementType 指向元素类型描述符的指针。
 * @param ppVector 指向接收向量句柄的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} elementType或ppVector为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_VectorCreate(
    OH_AbilityRuntime_ModObjDispatcher_TypeInfo *elementType,
    OH_AbilityRuntime_ModObjDispatcher_VectorHandle* ppVector);

/**
 * @brief 获取向量的元素类型。
 *
 * @param pVector 向量句柄。
 * @param pElementType 指向接收元素类型的TypeInfo的指针。使用完毕后需调用{@link OH_AbilityRuntime_ModObjDispatcher_TypeInfoClear}释放。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pVector或pElementType为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_VectorGetElementType(
    OH_AbilityRuntime_ModObjDispatcher_VectorHandle pVector, OH_AbilityRuntime_ModObjDispatcher_TypeInfo* pElementType);

/**
 * @brief 向向量末尾添加一个元素。函数会执行深拷贝，调用方保留原始变体的所有权。
 *
 * @param pVector 向量句柄。
 * @param pValue 指向元素值变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pVector或pValue为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_TYPE_MISMATCH} 元素类型与向量定义的类型不匹配。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_VectorAdd(
    OH_AbilityRuntime_ModObjDispatcher_VectorHandle pVector, const OH_AbilityRuntime_ModObjDispatcher_Variant* pValue);

/**
 * @brief 获取向量中指定索引位置的元素值。返回的变体是深拷贝，调用方拥有返回变体的所有权，需调用{@link OH_AbilityRuntime_ModObjDispatcher_VariantClear}释放。
 *
 * @param pVector 向量句柄。
 * @param index 元素索引，范围为[0, size - 1]。
 * @param pValue 指向接收元素值变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pVector或pValue为NULL，或index超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_VectorGet(
    OH_AbilityRuntime_ModObjDispatcher_VectorHandle pVector, uint32_t index,
    OH_AbilityRuntime_ModObjDispatcher_Variant* pValue);

/**
 * @brief 获取向量中的元素数量。
 *
 * @param pVector 向量句柄。
 * @param pSize 指向接收元素数量的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pVector或pSize为NULL。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_VectorGetSize(
    OH_AbilityRuntime_ModObjDispatcher_VectorHandle pVector, uint32_t* pSize);

/**
 * @brief 清空向量中的所有元素。
 *
 * @param pVector 向量句柄。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pVector为NULL。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_VectorClear(
    OH_AbilityRuntime_ModObjDispatcher_VectorHandle pVector);

/**
 * @brief 释放向量实例。释放后句柄将被置为NULL。如果ppVector或*ppVector为NULL，则不执行任何操作。
 *
 * @param ppVector 指向待释放的向量句柄的指针。释放后该指针将被置为NULL。
 * @since 26.0.0
 */
void OH_AbilityRuntime_ModObjDispatcher_VectorRelease(OH_AbilityRuntime_ModObjDispatcher_VectorHandle* ppVector);

/**
 * @brief 创建指定元素类型的集合实例。集合为不重复元素的无序集合，所有元素类型相同，支持添加、删除、查询指定元素是否存在、按索引获取元素和清空。
 *
 * @param elementType 指向元素类型描述符的指针。
 * @param ppSet 指向接收集合句柄的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} elementType或ppSet为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_SetCreate(
    OH_AbilityRuntime_ModObjDispatcher_TypeInfo *elementType, OH_AbilityRuntime_ModObjDispatcher_SetHandle* ppSet);

/**
 * @brief 获取集合的元素类型。
 *
 * @param pSet 集合句柄。
 * @param pElementType 指向接收元素类型的TypeInfo的指针。使用完毕后需调用{@link OH_AbilityRuntime_ModObjDispatcher_TypeInfoClear}释放。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pSet或pElementType为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_SetGetElementType(
    OH_AbilityRuntime_ModObjDispatcher_SetHandle pSet, OH_AbilityRuntime_ModObjDispatcher_TypeInfo* pElementType);

/**
 * @brief 向集合中添加一个元素。如果元素已存在，则不会重复添加。函数会执行深拷贝，调用方保留原始变体的所有权。
 *
 * @param pSet 集合句柄。
 * @param pValue 指向元素值变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pSet或pValue为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_TYPE_MISMATCH} 元素类型与集合定义的类型不匹配。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_SetAdd(
    OH_AbilityRuntime_ModObjDispatcher_SetHandle pSet, const OH_AbilityRuntime_ModObjDispatcher_Variant* pValue);

/**
 * @brief 从集合中移除指定元素。如果元素不存在，则不执行任何操作。
 *
 * @param pSet 集合句柄。
 * @param pValue 指向待移除元素值变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pSet或pValue为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_TYPE_MISMATCH} 元素类型与集合定义的类型不匹配。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_SetRemove(
    OH_AbilityRuntime_ModObjDispatcher_SetHandle pSet, const OH_AbilityRuntime_ModObjDispatcher_Variant* pValue);

/**
 * @brief 检查集合中是否存在指定元素。
 *
 * @param pSet 集合句柄。
 * @param pValue 指向待查找元素值变体的指针。
 * @param pExists 指向接收存在标志的指针。true表示元素存在，false表示不存在。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pSet、pValue或pExists为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_TYPE_MISMATCH} 元素类型与集合定义的类型不匹配。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_SetContains(
    OH_AbilityRuntime_ModObjDispatcher_SetHandle pSet, const OH_AbilityRuntime_ModObjDispatcher_Variant* pValue,
    bool* pExists);

/**
 * @brief 获取集合中的元素数量。
 *
 * @param pSet 集合句柄。
 * @param pSize 指向接收元素数量的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pSet或pSize为NULL。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_SetGetSize(
    OH_AbilityRuntime_ModObjDispatcher_SetHandle pSet, uint32_t* pSize);

/**
 * @brief 根据索引获取集合中的元素值。返回的变体是深拷贝，调用方拥有返回变体的所有权，需调用{@link OH_AbilityRuntime_ModObjDispatcher_VariantClear}释放。
 *
 * @param pSet 集合句柄。
 * @param index 元素索引，范围为[0, size - 1]。
 * @param pValue 指向接收元素值变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pSet或pValue为NULL，或index超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_SetGetAt(
    OH_AbilityRuntime_ModObjDispatcher_SetHandle pSet, uint32_t index,
    OH_AbilityRuntime_ModObjDispatcher_Variant* pValue);

/**
 * @brief 清空集合中的所有元素。
 *
 * @param pSet 集合句柄。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pSet为NULL。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_SetClear(
    OH_AbilityRuntime_ModObjDispatcher_SetHandle pSet);

/**
 * @brief 释放集合实例。释放后句柄将被置为NULL。如果ppSet或*ppSet为NULL，则不执行任何操作。
 *
 * @param ppSet 指向待释放的集合句柄的指针。释放后该指针将被置为NULL。
 * @since 26.0.0
 */
void OH_AbilityRuntime_ModObjDispatcher_SetRelease(OH_AbilityRuntime_ModObjDispatcher_SetHandle* ppSet);

/**
 * @brief 创建指定键类型和值类型的映射实例。键仅支持基本类型（BOOL、有符号整数、无符号整数、浮点数、STRING、ENUM），不支持容器类型（ARRAY、VECTOR、SET、MAP）和复杂类型（STRUCT、
 * IPC_REMOTE_PROXY、IPC_REMOTE_STUB）。
 *
 * @param keyType 键类型。仅支持基本类型（BOOL、有符号整数、无符号整数、浮点数、STRING、ENUM）。
 * @param valueType 指向值类型描述符的指针。
 * @param ppMap 指向接收映射句柄的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} valueType或ppMap为NULL，或keyType为不支持的类型。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_MapCreate(
    OH_AbilityRuntime_ModObjDispatcher_ValueType keyType, OH_AbilityRuntime_ModObjDispatcher_TypeInfo *valueType,
    OH_AbilityRuntime_ModObjDispatcher_MapHandle* ppMap);

/**
 * @brief 获取映射的键类型。
 *
 * @param pMap 映射句柄。
 * @param pKeyType 指向接收键类型的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pMap或pKeyType为NULL。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_MapGetKeyType(
    OH_AbilityRuntime_ModObjDispatcher_MapHandle pMap, OH_AbilityRuntime_ModObjDispatcher_ValueType* pKeyType);

/**
 * @brief 获取映射的值类型。
 *
 * @param pMap 映射句柄。
 * @param pValueType 指向接收值类型的TypeInfo的指针。使用完毕后需调用{@link OH_AbilityRuntime_ModObjDispatcher_TypeInfoClear}释放。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pMap或pValueType为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_MapGetValueType(
    OH_AbilityRuntime_ModObjDispatcher_MapHandle pMap, OH_AbilityRuntime_ModObjDispatcher_TypeInfo* pValueType);

/**
 * @brief 向映射中添加或更新键值对。如果键已存在，则更新对应的值。函数会执行深拷贝，调用方保留原始变体的所有权。
 *
 * @param pMap 映射句柄。
 * @param pKey 指向键变体的指针。
 * @param pValue 指向值变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pMap、pKey或pValue为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_TYPE_MISMATCH} 键或值的类型与映射定义的类型不匹配。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_MapPut(
    OH_AbilityRuntime_ModObjDispatcher_MapHandle pMap, const OH_AbilityRuntime_ModObjDispatcher_Variant* pKey,
    const OH_AbilityRuntime_ModObjDispatcher_Variant* pValue);

/**
 * @brief 根据键获取映射中对应的值。返回的变体是深拷贝，调用方拥有返回变体的所有权，需调用{@link OH_AbilityRuntime_ModObjDispatcher_VariantClear}释放。
 *
 * @param pMap 映射句柄。
 * @param pKey 指向键变体的指针。
 * @param pValue 指向接收值变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pMap、pKey或pValue为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_TYPE_MISMATCH} 键或值的类型与映射定义的类型不匹配。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 键在映射中不存在。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_MapGet(
    OH_AbilityRuntime_ModObjDispatcher_MapHandle pMap, const OH_AbilityRuntime_ModObjDispatcher_Variant* pKey,
    OH_AbilityRuntime_ModObjDispatcher_Variant* pValue);

/**
 * @brief 根据键从映射中移除键值对。如果键不存在，则不执行任何操作。
 *
 * @param pMap 映射句柄。
 * @param pKey 指向键变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pMap或pKey为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_TYPE_MISMATCH} 键或值的类型与映射定义的类型不匹配。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_MapRemove(
    OH_AbilityRuntime_ModObjDispatcher_MapHandle pMap, const OH_AbilityRuntime_ModObjDispatcher_Variant* pKey);

/**
 * @brief 检查映射中是否存在指定的键。
 *
 * @param pMap 映射句柄。
 * @param pKey 指向键变体的指针。
 * @param pExists 指向接收存在标志的指针。true表示键存在，false表示不存在。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pMap、pKey或pExists为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_TYPE_MISMATCH} 键或值的类型与映射定义的类型不匹配。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_MapContainsKey(
    OH_AbilityRuntime_ModObjDispatcher_MapHandle pMap, const OH_AbilityRuntime_ModObjDispatcher_Variant* pKey,
    bool* pExists);

/**
 * @brief 获取映射中的键值对数量。
 *
 * @param pMap 映射句柄。
 * @param pSize 指向接收键值对数量的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pMap或pSize为NULL。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_MapGetSize(
    OH_AbilityRuntime_ModObjDispatcher_MapHandle pMap, uint32_t* pSize);

/**
 * @brief 根据索引获取映射中的键。返回的变体是深拷贝，调用方拥有返回变体的所有权，需调用{@link OH_AbilityRuntime_ModObjDispatcher_VariantClear}释放。
 *
 * @param pMap 映射句柄。
 * @param index 键值对索引，范围为[0, size - 1]。
 * @param pKey 指向接收键变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pMap或pKey为NULL，或index超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_MapGetKeyAt(
    OH_AbilityRuntime_ModObjDispatcher_MapHandle pMap, uint32_t index,
    OH_AbilityRuntime_ModObjDispatcher_Variant* pKey);

/**
 * @brief 根据索引获取映射中的值。返回的变体是深拷贝，调用方拥有返回变体的所有权，需调用{@link OH_AbilityRuntime_ModObjDispatcher_VariantClear}释放。
 *
 * @param pMap 映射句柄。
 * @param index 键值对索引，范围为[0, size - 1]。
 * @param pValue 指向接收值变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pMap或pValue为NULL，或index超出范围。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_MapGetValueAt(
    OH_AbilityRuntime_ModObjDispatcher_MapHandle pMap, uint32_t index,
    OH_AbilityRuntime_ModObjDispatcher_Variant* pValue);

/**
 * @brief 清空映射中的所有键值对。
 *
 * @param pMap 映射句柄。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pMap为NULL。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_MapClear(
    OH_AbilityRuntime_ModObjDispatcher_MapHandle pMap);

/**
 * @brief 释放映射实例。释放后句柄将被置为NULL。如果ppMap或*ppMap为NULL，则不执行任何操作。
 *
 * @param ppMap 指向待释放的映射句柄的指针。释放后该指针将被置为NULL。
 * @since 26.0.0
 */
void OH_AbilityRuntime_ModObjDispatcher_MapRelease(OH_AbilityRuntime_ModObjDispatcher_MapHandle* ppMap);

/**
 * @brief 根据类型库元数据中的结构体名称创建结构体实例。structName必须与类型库中定义的结构体名称一致，可通过{@link OH_AbilityRuntime_TypeDescriptor_GetStructName}
 * 获取可用结构体名称。
 *
 * @param structName 结构体名称，来源于类型库元数据。
 * @param ppStruct 指向接收结构体句柄的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} structName或ppStruct为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} structName在类型库定义的结构体名称中不存在。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_StructCreate(
    const char* structName, OH_AbilityRuntime_ModObjDispatcher_StructHandle* ppStruct);

/**
 * @brief 获取结构体的类型名称。
 *
 * @param pStruct 结构体句柄。
 * @param pbstrName 指向接收结构体名称的缓冲区。
 * @param cMaxName 缓冲区大小（字节），包括空终止符。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pStruct或pbstrName为NULL，或cMaxName为0。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_StructGetName(
    OH_AbilityRuntime_ModObjDispatcher_StructHandle pStruct, char* pbstrName, uint32_t cMaxName);

/**
 * @brief 设置结构体中指定字段的值。函数会执行深拷贝，调用方保留原始变体的所有权。
 *
 * @param pStruct 结构体句柄。
 * @param szName 字段名称。
 * @param pValue 指向字段值变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pStruct、szName或pValue为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 字段在结构体中不存在。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_TYPE_MISMATCH} 字段类型与元数据定义的类型不匹配。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_StructSetField(
    OH_AbilityRuntime_ModObjDispatcher_StructHandle pStruct, const char* szName,
    const OH_AbilityRuntime_ModObjDispatcher_Variant* pValue);

/**
 * @brief 获取结构体中指定字段的值。返回的变体是深拷贝，调用方拥有返回变体的所有权，需调用{@link OH_AbilityRuntime_ModObjDispatcher_VariantClear}释放。
 *
 * @param pStruct 结构体句柄。
 * @param szName 字段名称。
 * @param pValue 指向接收字段值变体的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} pStruct、szName或pValue为NULL。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND} 字段在结构体中不存在。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjDispatcher_StructGetField(
    OH_AbilityRuntime_ModObjDispatcher_StructHandle pStruct, const char* szName,
    OH_AbilityRuntime_ModObjDispatcher_Variant* pValue);

/**
 * @brief 释放结构体实例。释放后句柄将被置为NULL。如果ppStruct或*ppStruct为NULL，则不执行任何操作。
 *
 * @param ppStruct 指向待释放的结构体句柄的指针。释放后该指针将被置为NULL。
 * @since 26.0.0
 */
void OH_AbilityRuntime_ModObjDispatcher_StructRelease(OH_AbilityRuntime_ModObjDispatcher_StructHandle* ppStruct);
#ifdef __cplusplus
}
#endif
/** @} */
#endif // OHOS_ABILITY_RUNTIME_C_MOD_OBJ_DISPATCHER_H

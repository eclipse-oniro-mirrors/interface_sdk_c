/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef ARK_RUNTIME_ZH_CN_JSVM_JSVM_H
#define ARK_RUNTIME_ZH_CN_JSVM_JSVM_H
 
/**
 * @addtogroup JSVM
 * @{
 *
 * @brief 提供标准的JavaScript引擎能力。
 *
 * 功能概述：
 * 标准JS引擎是严格遵守Ecmascript规范的JavaScript代码执行引擎。
 * 支持Ecmascript规范定义的标准库，提供完备的C++交互JS的native API。
 * 通过jit加速代码执行，为应用提供安全、高效的JS执行能力。
 * 标准JS引擎的能力通过一套稳定的ABI，即JSVM-API提供。JSVM-API支持动态链接到不同版本的JS引擎库，
 * 从而为开发者屏蔽掉不同引擎接口的差异。JSVM-API提供引擎生命周期管理、JS context管理、
 * JS代码执行、JS/C++互操作、执行环境快照、codecache等能力。\n
 * 使用平台：arm64平台。\n
 * 使用方法：链接SDK中的libjsvm.so，并在C++代码中包含ark_runtime/jsvm.h头文件。\n
 *
 * @since 11
 */

/**
 * @file jsvm.h
 *
 * @brief 提供JSVM-API接口定义。
 *
 * 通过API接口为开发者提供独立、标准、完整的JavaScript引擎能力，
 * 包括管理引擎生命周期、编译运行JS代码、实现JS/C++跨语言调用、拍摄快照等。\n
 * @library libjsvm.so
 * @kit ArkTS
 * @syscap SystemCapability.ArkCompiler.JSVM
 * @since 11
 */

// 此文件必须与C编译器兼容。
#include <stdbool.h>  // NOLINT(modernize-deprecated-headers)
#include <stddef.h>   // NOLINT(modernize-deprecated-headers)
#include "jsvm_types.h"

/**
 * @brief JSVM实验版本号，使用INT_MAX，只能由预处理器消费。
 *
 * @since 11
 */
#define JSVM_VERSION_EXPERIMENTAL 2147483647

/**
 * @brief JSVM版本号。
 *
 * 当处于实验阶段JSVM_EXPERIMENTAL时 值为JSVM_VERSION_EXPERIMENTAL（INT_MAX），否则 默认值为8。
 *
 * @since 11
 */
#ifndef JSVM_VERSION
/**
 * @brief JSVM实验阶段标识。
 *
 * @since 11
 */
#ifdef JSVM_EXPERIMENTAL
#define JSVM_VERSION JSVM_VERSION_EXPERIMENTAL
#else
#define JSVM_VERSION 8
#endif
#endif

#include "jsvm_types.h"

/**
 * @brief 对外可见。
 *
 * WIN环境下为：    __declspec(dllexport)
 *                  在Windows上，当构建动态链接库（DLL）时，用于告知编译器一个函数或变量从DLL中导出，使其可以被其他程序使用。
 * wasm环境下为：   __attribute__((visibility("default")))                    \
 *                  __attribute__((__import_module__("jsvm")))
 *                  ①__attribute__ 是 GCC 和 Clang 编译器用来添加特殊属性的语法。
 *                  ②__attribute__((visibility("default"))): 这个属性控制符号（函数/变量名）的可见性。
 *                  "default" 意味着这个符号是公开的、可导出的。在 Wasm 模块中，这使得函数可以被宿主环境（通常是 JavaScript）调用。
 *                  ③__attribute__((__import_module__("jsvm"))): 这是最关键的部分。
 *                  它告诉编译器，被这个宏修饰的函数不是在本 C/C++ 代码中实现的，而是需要从外部导入。
 * 其他环境下为：   __attribute__((visibility("default")))
 *                  此类清空通常对应于 Linux、macOS 和其他类 Unix 系统。
 *                  与 Windows 的 dllexport 类似，这个属性用于从共享库（在 Linux 上是 .so 文件，在 macOS 上是 .dylib 文件）中导出符号。
 *                  当使用 -fvisibility=hidden 编译标志（这是一个常见的优化和安全实践，默认隐藏所有符号）时，
 *                  只有明确标记为 visibility("default") 的符号才是公开可见的。
 *
 * @since 11
 */
#ifndef JSVM_EXTERN
#ifdef _WIN32
#define JSVM_EXTERN __declspec(dllexport)
#elif defined(__wasm__)
#define JSVM_EXTERN                                           \
    __attribute__((visibility("default")))                    \
    __attribute__((__import_module__("jsvm")))
#else
#define JSVM_EXTERN __attribute__((visibility("default")))
#endif
#endif

/**
 * @brief 自动长度。
 *
 * @since 11
 */
#define JSVM_AUTO_LENGTH SIZE_MAX

/**
 * @brief 一个预处理指令，用来检查是否正在使用C++编译器进行编译的、只有C++编译器才会预定义的宏。
 */
#ifdef __cplusplus
/**
 * @brief 用于告知编译器按C Code编译以下代码段的段起始标识：
 *
 * 当预处理指令__cplusplus检查到C++编译器正在进行编译时：EXTERN_C_START被赋值为"extern "C" {" ，表示其后代码为C代码。
 * 当预处理指令__cplusplus检查到不是C++编译器时，无须标记。
 *
 * @since 11
 */
#define EXTERN_C_START extern "C" {
/**
 * @brief 用于告知编译器按C Code编译以下代码段的段终止标识：
 *
 * 当使用预处理指令__cplusplus检查到C++编译器正在编译时：EXTERN_C_START被赋值为"}" ，表示C代码到此为止。
 * 当预处理指令__cplusplus检查到不是C++编译器时，无须标记。
 *
 * @since 11
 */
#define EXTERN_C_END }
#else
#define EXTERN_C_START
#define EXTERN_C_END
#endif

EXTERN_C_START

/**
 * @brief 初始化一个JavaScript虚拟机。
 *
 * @param options 用于初始化JavaScript虚拟机的选项。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_Init(const JSVM_InitOptions* options);

/**
 * @brief 创建一个虚拟机实例。
 *
 * @param options 用于创建虚拟机实例的选项。
 * @param result 新的虚拟机实例。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateVM(const JSVM_CreateVMOptions* options,
                                         JSVM_VM* result);

/**
 * @brief 用于设置虚拟机实例的微任务执行策略。
 * 如果该方法未被调用，虚拟机实例的默认策略为 JSVM_MicrotaskPolicy::JSVM_MICROTASK_AUTO。
 *
 * @param vm 用于设置微任务执行策略的虚拟机实例。
 * @param policy 执行微任务的策略。
 * @return 如果接口调用成功，返回 JSVM_OK。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入参数不合法。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_SetMicrotaskPolicy(JSVM_VM vm,
                                                   JSVM_MicrotaskPolicy policy);

/**
 * @brief 销毁一个虚拟机实例。
 *
 * @param vm 待销毁的虚拟机实例。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入参数不合法。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_DestroyVM(JSVM_VM vm);

/**
 * @brief 创建JavaScript Proxy，等价于在 JavaScript 中执行 new Proxy(target, handler)。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param target 表示用于创建代理的 JavaScript 对象
 * @param handler 表示定义了拦截什么操作及如何处理被拦截操作的 JavaScript 对象。
 * @param result 表示创建的 JavaScript 代理。
 * @return 返回执行状态码。
 *         {@link JSVM_OK } 表示接口调用成功。\n
 *         {@link JSVM_OBJECT_EXPECTED} 如果 target 或 handler 非 JS 对象。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateProxy(JSVM_Env env,
                                            JSVM_Value target,
                                            JSVM_Value handler,
                                            JSVM_Value* result);

/**
 * @brief 判断传入值value是否为 JavaScript Proxy。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param value 需要检查的值。
 * @param isProxy 表示是否为 JavaScript Proxy。
 * @return 返回执行状态码。
 *         {@link JSVM_OK } 表示接口调用成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入参数不合法。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsProxy(JSVM_Env env,
                                        JSVM_Value value,
                                        bool* isProxy);

/**
 * @brief 获取 JavaScript Proxy 中的目标对象。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param value 需要获取目标对象的代理。
 * @param result 代理的目标对象。
 * @return 返回执行状态码。
 *         {@link JSVM_OK } 表示接口调用成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入参数不合法。\n
 *         {@link JSVM_INVALID_TYPE} 如果 value 非 Javascript Proxy。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ProxyGetTarget(JSVM_Env env,
                                               JSVM_Value value,
                                               JSVM_Value* result);

/**
 * @brief 为虚拟机实例打开一个新的虚拟机作用域。
 *
 * @param vm 目标虚拟机实例。
 * @param result 新的虚拟机作用域。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_OpenVMScope(JSVM_VM vm,
                                            JSVM_VMScope* result);

/**
 * @brief 关闭虚拟机实例的虚拟机作用域。
 *
 * @param vm 目标虚拟机实例。
 * @param scope 将要关闭的虚拟机作用域。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CloseVMScope(JSVM_VM vm,
                                             JSVM_VMScope scope);

/**
 * @brief 基于新环境上下文的可选属性，创建一个新环境。
 *
 * @param vm 虚拟机实例，新环境将在该实例中创建。
 * @param propertyCount 属性数组中元素的个数。
 * @param properties 属性描述符的数组。
 * @param result 创建的新环境。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateEnv(JSVM_VM vm,
                                          size_t propertyCount,
                                          const JSVM_PropertyDescriptor* properties,
                                          JSVM_Env* result);

/**
 * @brief 基于虚拟机的起始快照，创建一个新的环境。
 *
 * @param vm 虚拟机实例，新环境将在该实例中创建。
 * @param index 环境在快照中的索引。
 * @param result 创建的新环境。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateEnvFromSnapshot(JSVM_VM vm,
                                                      size_t index,
                                                      JSVM_Env* result);

/**
 * @brief 销毁环境。
 *
 * @param env 待销毁的环境。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_DestroyEnv(JSVM_Env env);

/**
 * @brief 打开一个新的环境作用域。
 *
 * @param env 目标环境，JSVM-API接口将在该环境下调用。
 * @param result 新的环境作用域。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_OpenEnvScope(JSVM_Env env,
                                             JSVM_EnvScope* result);

/**
 * @brief 关闭环境作用域。
 *
 * @param env 目标环境，JSVM-API接口将在该环境下调用。
 * @param scope 将要关闭的环境作用域。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CloseEnvScope(JSVM_Env env,
                                              JSVM_EnvScope scope);

/**
 * @brief 检索给定环境的虚拟机实例。
 *
 * @param env 目标环境，JSVM-API接口将在该环境下调用。
 * @param result 给定环境的虚拟机实例。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetVM(JSVM_Env env,
                                      JSVM_VM* result);

/**
 * @brief 编译一串JavaScript代码，并返回编译后的脚本。
 *
 * @param env 目标环境，JSVM-API接口将在该环境下调用。
 * @param script 包含要编译的脚本的JavaScript代码。
 * @param cachedData 可选。脚本的代码缓存数据。
 * @param cacheDataLength cachedData数组的长度。
 * @param eagerCompile 是否立即编译脚本。
 * @param cacheRejected 代码缓存是否被编译拒绝。
 * @param result 编译后的脚本。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的 data 是空指针。\n
 *         {@link JSVM_STRING_EXPECTED } 表示传入的参数不是string类型。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_CANT_RUN_JS } 表示当前无法执行JS。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CompileScript(JSVM_Env env,
                                              JSVM_Value script,
                                              const uint8_t* cachedData,
                                              size_t cacheDataLength,
                                              bool eagerCompile,
                                              bool* cacheRejected,
                                              JSVM_Script* result);

/**
 * @brief 编译一串包含 sourcemap 信息的 JavaScript 代码，并返回编译后的脚本。
 *
 * @param env 目标环境，JSVM-API接口将在该环境下调用。
 * @param script 包含要编译的脚本的JavaScript代码。
 * @param cachedData 可选。脚本的代码缓存数据。
 * @param cacheDataLength cachedData数组的长度。
 * @param eagerCompile 是否立即编译脚本。
 * @param cacheRejected 代码缓存是否被编译拒绝。
 * @param origin 源代码信息，包括 source map 的位置和源代码文件名等信息。
 * @param result 编译后的脚本。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的 data 是空指针。\n
 *         {@link JSVM_STRING_EXPECTED } 表示传入的参数不是string类型。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示执行失败。\n
 *         {@link JSVM_CANT_RUN_JS } 表示当前无法执行JS。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CompileScriptWithOrigin(JSVM_Env env,
                                                        JSVM_Value script,
                                                        const uint8_t* cachedData,
                                                        size_t cacheDataLength,
                                                        bool eagerCompile,
                                                        bool* cacheRejected,
                                                        JSVM_ScriptOrigin* origin,
                                                        JSVM_Script* result);

/**
 * @brief 编译一串JavaScript代码，并返回编译后的脚本。
 *
 * @param env 目标环境，JSVM-API接口将在该环境下调用。
 * @param script 包含要编译的脚本的JavaScript代码。
 * @param optionCount 传入的 option 数组的长度。
 * @param options option 数组，存放所有的编译选项。
 * @param result 编译后的脚本。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入参数无效。\n
 *         {@link JSVM_STRING_EXPECTED } 表示传入的参数不是string类型。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CompileScriptWithOptions(JSVM_Env env,
                                                         JSVM_Value script,
                                                         size_t optionCount,
                                                         JSVM_CompileOptions options[],
                                                         JSVM_Value* result);

/**
 * @brief 为编译后的脚本创建代码缓存。
 *
 * @param env 目标环境，JSVM-API接口将在该环境下调用。
 * @param script 目标编译脚本。
 * @param data 代码缓存的数据。
 * @param length 代码缓存数据的长度。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateCodeCache(JSVM_Env env,
                                                JSVM_Script script,
                                                const uint8_t** data,
                                                size_t* length);

/**
 * @brief 执行一串JavaScript代码并返回其结果，其中包含以下注意事项：
 * 与eval不同的是，该函数不允许脚本访问当前词法作用域，因此也不允许访问模块作用域，
 * 这意味着require等伪全局变量将不可用。
 * 脚本可以访问全局作用域。
 * 脚本中的函数和var声明将被添加到全局对象。
 * 使用let和const的变量声明将全局可见，但不会被添加到全局对象。
 * this的值在脚本内是global。
 *
 * @param env 调用JSVM-API的环境。
 * @param script 包含要执行的脚本的JavaScript字符串。
 * @param result 执行脚本产生的值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_RunScript(JSVM_Env env,
                                          JSVM_Script script,
                                          JSVM_Value* result);

/**
 * @brief 将data与当前运行的JSVM环境相关联。后续可以使用OH_JSVM_GetInstanceData()检索data。
 * 通过先前调用OH_JSVM_SetInstanceData()设置的任何与当前运行的JSVM环境相关联的现有数据都将
 * 被覆盖。如果先前提供了finalizeCb，则不会调用它。
 *
 * @param env 调用JSVM-API的环境。
 * @param data 可用于此实例的绑定的数据项。
 * @param finalizeCb 销毁环境时调用的函数，该函数接收data以便释放它。
 * @param finalizeHint 在收集期间传递给最终回调的可选提示。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_SetInstanceData(JSVM_Env env,
                                                void* data,
                                                JSVM_Finalize finalizeCb,
                                                void* finalizeHint);

/**
 * @brief 检索通过调用OH_JSVM_SetInstanceData()与当前运行JSVM环境产生关联的数据。
 * 如果未设置任何关联数据，该函数调用将成功，且data设置为NULL。
 *
 * @param env 调用JSVM-API的环境。
 * @param data 之前通过调用OH_JSVM_SetInstanceData()与当前运行的JSVM环境关联的数据项。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetInstanceData(JSVM_Env env,
                                                void** data);

/**
 * @brief 检索JSVM_ExtendedErrorInfo结构，其中包含发生的最后一个错误的有关信息。
 * 返回的JSVM_ExtendedErrorInfo的内容仅在对同一env调用JSVM-API函数之前有效。
 * 这包括对OH_JSVM_IsExceptionPending的调用，因此可能经常需要复制信息以便以后使用。
 * error_message中返回的指针指向一个静态定义的字符串，因此如果你在调用另一个JSVM-API
 * 函数之前将它从error_message字段（将被覆盖）中复制出来，则可以安全地使用该指针。
 *
 * @param env 调用JSVM-API的环境。
 * @param result 包含有关错误的更多信息的JSVM_ExtendedErrorInfo结构。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetLastErrorInfo(JSVM_Env env,
                                                 const JSVM_ExtendedErrorInfo** result);

/**
 * @brief 抛出提供的JavaScript值。
 *
 * @param env 调用JSVM-API的环境。
 * @param error 要抛出的JavaScript值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_Throw(JSVM_Env env,
                                      JSVM_Value error);

/**
 * @brief 抛出带有所提供文本的JavaScript Error。
 *
 * @param env 调用JSVM-API的环境。
 * @param code 要在错误上设置的可选错误代码。
 * @param msg 表示与错误关联的文本的C字符串。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ThrowError(JSVM_Env env,
                                           const char* code,
                                           const char* msg);

/**
 * @brief 抛出带有所提供文本的JavaScript TypeError。
 *
 * @param env 调用JSVM-API的环境。
 * @param code 要在错误上设置的可选错误代码。
 * @param msg 表示与错误关联的文本的C字符串。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ThrowTypeError(JSVM_Env env,
                                               const char* code,
                                               const char* msg);

/**
 * @brief 抛出带有所提供文本的JavaScript RangeError。
 *
 * @param env 调用JSVM-API的环境。
 * @param code 要在错误上设置的可选错误代码。
 * @param msg 表示与错误关联的文本的C字符串。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ThrowRangeError(JSVM_Env env,
                                                const char* code,
                                                const char* msg);

/**
 * @brief 抛出带有所提供文本的JavaScript SyntaxError。
 *
 * @param env 调用JSVM-API的环境。
 * @param code 要在错误上设置的可选错误代码。
 * @param msg 表示与错误关联的文本的C字符串。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ThrowSyntaxError(JSVM_Env env,
                                                 const char* code,
                                                 const char* msg);

/**
 * @brief 查询JSVM_Value以检查它是否表示错误对象。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param result 如果JSVM_Value表示错误，则设置为true的布尔值，否则设置为false。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsError(JSVM_Env env,
                                        JSVM_Value value,
                                        bool* result);

/**
 * @brief 返回带有所提供文本的JavaScript Error。
 *
 * @param env 调用JSVM-API的环境。
 * @param code 可选的JSVM_Value，带有与错误关联的错误代码的字符串。
 * @param msg 引用JavaScript string用作Error的消息。
 * @param result 表示创建的错误。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_STRING_EXPECTED } 表示传入的参数不是string类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateError(JSVM_Env env,
                                            JSVM_Value code,
                                            JSVM_Value msg,
                                            JSVM_Value* result);

/**
 * @brief 返回带有所提供文本的JavaScript TypeError。
 *
 * @param env 调用JSVM-API的环境。
 * @param code 可选的JSVM_Value，带有与错误关联的错误代码的字符串。
 * @param msg 引用JavaScript string用作Error的消息。
 * @param result 表示创建的错误。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_STRING_EXPECTED } 表示传入的参数不是string类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateTypeError(JSVM_Env env,
                                                JSVM_Value code,
                                                JSVM_Value msg,
                                                JSVM_Value* result);

/**
 * @brief  返回带有所提供文本的JavaScript RangeError。
 *
 * @param env 调用JSVM-API的环境。
 * @param code 可选的JSVM_Value，带有与错误关联的错误代码的字符串。
 * @param msg 引用JavaScript string用作Error的消息。
 * @param result 表示创建的错误。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_STRING_EXPECTED } 表示传入的参数不是string类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateRangeError(JSVM_Env env,
                                                 JSVM_Value code,
                                                 JSVM_Value msg,
                                                 JSVM_Value* result);

/**
 * @brief 返回带有所提供文本的JavaScript SyntaxError。
 *
 * @param env 调用JSVM-API的环境。
 * @param code 可选的JSVM_Value，带有与错误关联的错误代码的字符串。
 * @param msg 引用JavaScript string用作Error的消息。
 * @param result 表示创建的错误。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_STRING_EXPECTED } 表示传入的参数不是string类型。\n *
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateSyntaxError(JSVM_Env env,
                                                  JSVM_Value code,
                                                  JSVM_Value msg,
                                                  JSVM_Value* result);

/**
 * @brief 获取并清除上一次异常。如果出现挂起，则返回JavaScript异常，否则返回NULL。
 *
 * @param env 调用JSVM-API的环境。
 * @param result 如果出现挂起则返回异常，否则为NULL。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetAndClearLastException(JSVM_Env env,
                                                         JSVM_Value* result);

/**
 * @brief 查询上一次异常是否由挂起导致的。如果由异常导致，则返回true，否则返回false。
 *
 * @param env 调用JSVM-API的环境。
 * @param result 如果异常挂起，则设置为true的布尔值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsExceptionPending(JSVM_Env env,
                                                   bool* result);

/**
 * @brief 开辟了一个新的作用域。
 *
 * @param env 调用JSVM-API的环境。
 * @param result 代表新作用域。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_OpenHandleScope(JSVM_Env env,
                                                JSVM_HandleScope* result);

/**
 * @brief （必须）按照创建作用域的相反顺序关闭传入的作用域。
 *
 * @param env 调用JSVM-API的环境。
 * @param scope 表示要关闭的作用域。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_HANDLE_SCOPE_MISMATCH } 表示执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CloseHandleScope(JSVM_Env env,
                                                 JSVM_HandleScope scope);

/**
 * @brief 打开一个可以将某对象从其中提到外部作用域的新作用域。
 *
 * @param env 调用JSVM-API的环境。
 * @param result 代表新作用域。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_OpenEscapableHandleScope(JSVM_Env env,
                                                         JSVM_EscapableHandleScope* result);

/**
 * @brief （必须）按照创建作用域的相反顺序关闭传入的作用域。
 * 即使存在挂起的JavaScript异常，也可以调用此JSVM_API。
 *
 * @param env 调用JSVM-API的环境。
 * @param scope 表示要关闭的作用域。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_HANDLE_SCOPE_MISMATCH } 表示执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CloseEscapableHandleScope(JSVM_Env env,
                                                          JSVM_EscapableHandleScope scope);

/**
 * @brief 提升JavaScript对象的句柄，使其在外部作用域的生命周期内有效。
 * 每个作用域只能调用一次。如果多次调用，将返回错误。
 *
 * @param env 调用JSVM-API的环境。
 * @param scope 表示当前的作用域。
 * @param escapee 表示要提升的JavaScript Object。
 * @param result 被提升的Object在外部作用域中的句柄。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_ESCAPE_CALLED_TWICE } 表示scope对象已被关闭。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_EscapeHandle(JSVM_Env env,
                                             JSVM_EscapableHandleScope scope,
                                             JSVM_Value escapee,
                                             JSVM_Value* result);

/**
 * @brief 对传入的值创建一个具有指定引用计数的新引用。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 正在为其创建引用的JSVM_Value。
 * @param initialRefcount 新引用的初始引用计数。
 * @param result 指向新的引用。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateReference(JSVM_Env env,
                                                JSVM_Value value,
                                                uint32_t initialRefcount,
                                                JSVM_Ref* result);

/**
 * @brief 删除传入的引用。
 *
 * @param env 调用JSVM-API的环境。
 * @param ref 需删除的JSVM_Ref。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_DeleteReference(JSVM_Env env,
                                                JSVM_Ref ref);

/**
 * @brief 增加传入引用的引用计数并返回生成的引用计数。
 *
 * @param env 调用JSVM-API的环境。
 * @param ref 传入的引用，其引用计数将增加。
 * @param result 新的引用计数。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ReferenceRef(JSVM_Env env,
                                             JSVM_Ref ref,
                                             uint32_t* result);

/**
 * @brief 递减传入引用的引用计数并返回生成的引用计数。
 *
 * @param env 调用JSVM-API的环境。
 * @param ref 将减少其引用计数的JSVM_Ref。
 * @param result 新的引用计数。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ReferenceUnref(JSVM_Env env,
                                               JSVM_Ref ref,
                                               uint32_t* result);

/**
 * @brief 如果仍然有效，此JSVM-API将返回JSVM_Value，
 * 表示与JSVM_Ref关联的JavaScript值。否则，结果将为NULL。
 *
 * @param env 调用JSVM-API的环境。
 * @param ref 请求相应值的JSVM_Ref。
 * @param result JSVM_Ref引用的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetReferenceValue(JSVM_Env env,
                                                  JSVM_Ref ref,
                                                  JSVM_Value* result);

/**
 * @brief 返回对应于JavaScript Array类型的JSVM-API值。
 *
 * @param env 调用JSVM-API的环境。
 * @param result 代表JavaScript Array的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateArray(JSVM_Env env,
                                            JSVM_Value* result);


/**
 * @brief 返回对应于JavaScript Array类型的JSVM-API值。Array
 * 的长度属性设置为传入的长度参数。但是，不保证底层缓冲区在创建
 * 数组时由VM预先分配。该行为留给底层VM实现。
 *
 * @param env 调用JSVM-API的环境。
 * @param length 数组的初始长度。
 * @param result 代表JavaScript Array的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateArrayWithLength(JSVM_Env env,
                                                      size_t length,
                                                      JSVM_Value* result);

/**
 * @brief 返回JavaScript ArrayBuffer类型对应的JSVM-API值。ArrayBuffer用于
 * 表示固定长度的二进制数据缓冲区。通常用作TypedArray对象的后备缓冲区。
 * 分配的ArrayBuffer有一个底层字节缓冲区，其大小由传入的length参数决定。
 * 底层缓冲区可选择返回给调用方，调用方可直接操作该缓冲区。
 * 此缓冲区只能直接从native代码写入。如果想从JavaScript写入该缓冲区，
 * 需创建TypedArray或DataView对象。
 *
 * @param env 调用JSVM-API的环境。
 * @param byteLength 要创建的数组缓冲区的字节长度。
 * @param data 指向ArrayBuffer的底层字节缓冲区的指针。data可以选择性地通过传递NULL来忽略。
 * @param result 代表JavaScript ArrayBuffer的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateArraybuffer(JSVM_Env env,
                                                  size_t byteLength,
                                                  void** data,
                                                  JSVM_Value* result);

/**
 * @brief 申请一段 BackingStore 内存给 array buffer 使用。
 *
 * @param byteLength BackingStore 内存的大小。
 * @param initialized BackingStore 内存初始化的方式。
 * @param data 用于接受申请 BackingStore 内存地址的指针。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的 data 是空指针。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示内存申请失败。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_AllocateArrayBufferBackingStoreData(size_t byteLength,
                                                                    JSVM_InitializedFlag initialized,
                                                                    void **data);

/**
 * @brief 释放由 OH_JSVM_AllocateArrayBufferBackingStoreData 申请的 BackingStore 内存。
 *
 * @param data: 申请得到的 BackingStore 内存。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的 data 是空指针。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_FreeArrayBufferBackingStoreData(void *data);

/**
 * @brief 在申请得到的 BackingStore 内存上创建 array buffer。
 *
 * @param env 调用JSVM-API的环境。
 * @param data 申请得到的 BackingStore 内存。
 * @param backingStoreSize BackingStore 内存的大小。
 * @param offset array buffer 在这段内存上的起始位置与内存头之间的相对偏移，单位是字节。
 * @param arrayBufferSize array buffer 的大小，单位是字节。
 * @param result 接收 array buffer 地址的指针。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示触发了下面描述的异常情况之一：\n
 *         1. offset + arrayBufferSize > backingStoreSize。\n
 *         2. backingStoreSize 或者 arrayBufferSize 为 0。\n
 *         3. data 或者 result 为空。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateArrayBufferFromBackingStoreData(JSVM_Env env,
                                                                      void *data,
                                                                      size_t backingStoreSize,
                                                                      size_t offset,
                                                                      size_t arrayBufferSize,
                                                                      JSVM_Value *result);

/**
 * @brief 分配一个JavaScript Date对象。此API不处理闰秒。
 * 这是因为ECMAScript遵循POSIX时间规范，对闰秒进行忽略。
 *
 * @param env 调用JSVM-API的环境。
 * @param time 自1970年1月1日UTC以来的ECMAScript时间值（以毫秒为单位）。
 * @param result 表示JavaScript Date对象的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateDate(JSVM_Env env,
                                           double time,
                                           JSVM_Value* result);

/**
 * @brief 分配一个带有外部数据的JavaScript值。这用于通过JavaScript代码传递外部数据。
 * 后续可以使用OH_JSVM_GetValueExternal由native代码检索。
 * 该API添加了一个JSVM_Finalize回调，当刚刚创建的JavaScript对象被垃圾回收时将调用该回调。
 * 创建的值不是一个对象，因此不支持附加属性。它被认为是一个独特的值类型：
 * 使用外部值调用OH_JSVM_Typeof()会生成JSVM_EXTERNAL。
 *
 * @param env 调用JSVM-API的环境。
 * @param data 指向外部数据的原始指针。
 * @param finalizeCb 收集外部值时调用的可选回调。JSVM_Finalize提供了更多详细信息。
 * @param finalizeHint 在收集期间传递给最终回调的可选提示。
 * @param result 表示外部值的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateExternal(JSVM_Env env,
                                               void* data,
                                               JSVM_Finalize finalizeCb,
                                               void* finalizeHint,
                                               JSVM_Value* result);

/**
 * @brief 分配一个默认的JavaScript对象。该函数功能等同于在JavaScript中执行new Object()。
 *
 * @param env 调用JSVM-API的环境。
 * @param result 表示JavaScript对象的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateObject(JSVM_Env env,
                                             JSVM_Value* result);

/**
 * @brief 用UTF8编码的C字符串创建JavaScript symbol值。
 *
 * @param env 调用JSVM-API的环境。
 * @param description 可选的JSVM_Value，它指的是要设置为符号描述的JavaScript string。
 * @param result 代表JavaScript symbol的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_STRING_EXPECTED } 表示传入的参数不是string类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateSymbol(JSVM_Env env,
                                             JSVM_Value description,
                                             JSVM_Value* result);

/**
 * @brief 在全局注册表中搜索具有给定描述的现有符号。如果该
 * 符号已经存在，它将被返回，否则将在注册表中创建一个新符号。
 *
 * @param env 调用JSVM-API的环境。
 * @param utf8description UTF-8 C 字符串，表示用作符号描述的文本。
 * @param length 描述字符串的长度，以字节为单位。如果字符串以null结尾，则为JSVM_AUTO_LENGTH。
 * @param result 表示JavaScript 符号的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_SymbolFor(JSVM_Env env,
                                          const char* utf8description,
                                          size_t length,
                                          JSVM_Value* result);

/**
 * @brief 基于已有的ArrayBuffer对象，创建一个JavaScript TypedArray对象。
 * TypedArray对象在底层数据缓冲区上提供了一个类似数组的视图，其中每个元素都具有相同的底层二进制标量数据类型。
 * 要求：length * 元素标量byte值 + byteOffset 不大于传入数组的ByteLength()，否则抛出范围错误（RangeError）。
 *
 * @param env 调用JSVM-API的环境。
 * @param type TypedArray中元素的标量数据类型。
 * @param length TypedArray中的元素个数。
 * @param arraybuffer ArrayBuffer是类型化数组的基础。
 * @param byteOffset ArrayBuffer中开始投影TypedArray的字节偏移量。
 * @param result 表示JavaScript TypedArray的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateTypedarray(JSVM_Env env,
                                                 JSVM_TypedarrayType type,
                                                 size_t length,
                                                 JSVM_Value arraybuffer,
                                                 size_t byteOffset,
                                                 JSVM_Value* result);

/**
 * @brief 基于已有的ArrayBuffer对象，创建一个JavaScript DataView对象。
 * DataView对象在底层数据缓冲区上提供了一个类似数组的视图，其中的元素可以具有不同的大小和类型。
 * 要求：二进制的length + byteOffset不大于传入数组的大小（byte数）。否则，抛出范围错误（RangeError）。
 *
 * @param env 调用JSVM-API的环境。
 * @param length DataView中的元素个数。
 * @param arraybuffer 位于DataView底层的ArrayBuffer。
 * @param byteOffset ArrayBuffer中的字节偏移量，指示投影DataView的开始位置。
 * @param result 表示JavaScript DataView对象的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateDataview(JSVM_Env env,
                                               size_t length,
                                               JSVM_Value arraybuffer,
                                               size_t byteOffset,
                                               JSVM_Value* result);

/**
 * @brief 将一个C int32_t类型值转换为JavaScript number类型值。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要在JavaScript中表示的整数值。
 * @param result 表示JavaScript number类型的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateInt32(JSVM_Env env,
                                            int32_t value,
                                            JSVM_Value* result);

/**
 * @brief 将一个C uint32_t类型值转换为JavaScript number类型值。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要在JavaScript中表示的无符号整数值。
 * @param result 表示JavaScript number类型的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateUint32(JSVM_Env env,
                                             uint32_t value,
                                             JSVM_Value* result);

/**
 * @brief 将一个C int64_t类型值转换为JavaScript number类型值。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要在JavaScript中表示的整数值。
 * @param result 代表JavaScript number类型的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateInt64(JSVM_Env env,
                                            int64_t value,
                                            JSVM_Value* result);

/**
 * @brief 将一个C double类型值转换为JavaScript number类型值。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要在JavaScript中表现的双精度值。
 * @param result 代表JavaScript number类型的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateDouble(JSVM_Env env,
                                             double value,
                                             JSVM_Value* result);

/**
 * @brief 将一个C int64_t类型值转换为JavaScript BigInt类型值。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要在JavaScript中表现的整数值。
 * @param result 表示JavaScript BigInt类型的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateBigintInt64(JSVM_Env env,
                                                  int64_t value,
                                                  JSVM_Value* result);

/**
 * @brief 将一个C uint64_t类型值转换为JavaScript BigInt类型值。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要在JavaScript中表示的无符号整数值。
 * @param result 代表JavaScript BigInt类型的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateBigintUint64(JSVM_Env env,
                                                   uint64_t value,
                                                   JSVM_Value* result);

/**
 * @brief 将一组64位无符号比特位转换为单个BigInt值。
 *
 * @param env 调用JSVM-API的环境。
 * @param signBit 确定生成的BigInt是正数还是负数。
 * @param wordCount words数组的长度。
 * @param words uint64_t little-endian 64位字数组。
 * @param result 代表JavaScript BigInt类型的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateBigintWords(JSVM_Env env,
                                                  int signBit,
                                                  size_t wordCount,
                                                  const uint64_t* words,
                                                  JSVM_Value* result);

/**
 * @brief 将ISO-8859-1编码的C字符串转换为JavaScript字符串值。
 * 复制原生字符串。
 *
 * @param env 调用JSVM-API的环境。
 * @param str 表示ISO-8859-1编码的字符串的字符缓冲区。
 * @param length 字符串的长度，以字节为单位。如果它以null结尾，则为JSVM_AUTO_LENGTH。
 * @param result 表示JavaScript字符串的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateStringLatin1(JSVM_Env env,
                                                   const char* str,
                                                   size_t length,
                                                   JSVM_Value* result);

/**
 * @brief 将UTF16-LE编码的C字符串转换为JavaScript字符串值。
 * 复制原生字符串。
 *
 * @param env 调用JSVM-API的环境。
 * @param str 表示UTF16-LE编码的字符串的字符缓冲区。
 * @param length 以两字节代码单元表示的字符串长度，如果它以null终止，则为JSVM_AUTO_LENGTH。
 * @param result 代表JavaScript string的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateStringUtf16(JSVM_Env env,
                                                  const char16_t* str,
                                                  size_t length,
                                                  JSVM_Value* result);

/**
 * @brief 用UTF8编码的C字符串创建JavaScript字符串值。
 * 复制原生字符串。
 *
 * @param env 调用JSVM-API的环境。
 * @param str 表示UTF8编码字符串的字符缓冲区。
 * @param length 字符串的长度，以字节为单位。如果字符串以null结尾，则为JSVM_AUTO_LENGTH。
 * @param result 代表JavaScript字符串的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateStringUtf8(JSVM_Env env,
                                                 const char* str,
                                                 size_t length,
                                                 JSVM_Value* result);

/**
 * @brief 返回数组的长度。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表查询长度的JavaScript Array。
 * @param result uint32代表数组的长度。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_ARRAY_EXPECTED } 表示传入的参数不是Array类型。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetArrayLength(JSVM_Env env,
                                               JSVM_Value value,
                                               uint32_t* result);

/**
 * @brief 用于检索ArrayBuffer的底层数据缓冲区及其长度。
 *
 * @param env 调用JSVM-API的环境。
 * @param arraybuffer 代表被查询的ArrayBuffer。
 * @param data ArrayBuffer的底层数据缓冲区。如果byte_length为0，则该值可能为NULL或任何其他指针值。
 * @param byteLength 底层数据缓冲区的字节长度。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetArraybufferInfo(JSVM_Env env,
                                                   JSVM_Value arraybuffer,
                                                   void** data,
                                                   size_t* byteLength);

/**
 * @brief 返回对象的原型。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 表示待返回其原型的JavaScript object。
 * 这将返回Object.getPrototypeOf的等价值（与函数的prototype属性不同）。
 * @param result 表示给定对象的原型。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetPrototype(JSVM_Env env,
                                             JSVM_Value object,
                                             JSVM_Value* result);

/**
 * @brief 返回类型化数组的各种属性。如果不需要该属性，则任何输出参数都可以是 NULL。
 *
 * @param env 调用JSVM-API的环境。
 * @param typedarray 表示要查询其属性的TypedArray。
 * @param type TypedArray中元素的标量数据类型。
 * @param length TypedArray中的元素数。
 * @param data TypedArray底层的数据缓冲区由byte_offset值调整，使其指向TypedArray
 * 中的第一个元素。如果数组的长度是0，这可能是NULL或任何其他指针值。
 * @param arraybuffer 位于TypedArray下的ArrayBuffer。
 * @param byteOffset 数组的第一个元素所在的基础原生数组中的字节偏移量。
 * data 参数的值已经过调整，因此data指向数组中的第一个元素。因此，
 * 原生数组的第一个字节将位于data - byte_offset。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetTypedarrayInfo(JSVM_Env env,
                                                  JSVM_Value typedarray,
                                                  JSVM_TypedarrayType* type,
                                                  size_t* length,
                                                  void** data,
                                                  JSVM_Value* arraybuffer,
                                                  size_t* byteOffset);

/**
 * @brief 返回DataView的各种属性。
 * 如果不需要某一属性，则任何出参都可以设置为NULL。
 *
 * @param env 调用JSVM-API的环境。
 * @param dataview  表示要查询其属性的DataView。
 * @param bytelength DataView中的字节个数。
 * @param data DataView下的数据缓冲区。如果bytelength是0则可能是NULL或任何其他指针值。
 * @param arraybuffer ArrayBuffer是DataView的基础。
 * @param byteOffset 开始投影DataView的数据缓冲区中的字节偏移量。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入参数非外部的JSVM_Value。
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetDataviewInfo(JSVM_Env env,
                                                JSVM_Value dataview,
                                                size_t* bytelength,
                                                void** data,
                                                JSVM_Value* arraybuffer,
                                                size_t* byteOffset);

/**
 * @brief 返回与给定的JavaScript Date时间值等价的C双精度基础类型值。如果调用成功，返回JSVM_OK。
 * 如果传入一个非JavaScript Date类型的JSVM_Value，返回JSVM_DATA_EXPECTED。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表一个JavaScript Date。
 * @param result 作为double的时间值表示为自1970年1月1日UTC午夜以来的毫秒数。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_DATE_EXPECTED } 表示传入参数不是Date类型。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetDateValue(JSVM_Env env,
                                             JSVM_Value value,
                                             double* result);

/**
 * @brief 返回与给定的JavaScript Boolean等价的C布尔基础类型值。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表输入的JavaScript Boolean对象。
 * @param result 返回与给定JavaScript Boolean对象等价的bool值，value对象值为true则result为true，反之亦然。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_BOOLEAN_EXPECTED } 表示传入的参数不是boolean类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetValueBool(JSVM_Env env,
                                             JSVM_Value value,
                                             bool* result);

/**
 * @brief 返回与给定的JavaScript number等价的C双精度基础类型值。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表JavaScript number。
 * @param result 给定的JavaScript number的C双精度基础类型等价值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_NUMBER_EXPECTED } 表示传入的参数不是number类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetValueDouble(JSVM_Env env,
                                               JSVM_Value value,
                                               double* result);

/**
 * @brief 返回与给定的JavaScript BigInt等价的C int64_t基础类型值。
 * 如果需要，它将截断该值，将lossless设置为false。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表JavaScript BigInt。
 * @param result 给定的JavaScript BigInt的C int64_t基础类型等价值。
 * @param lossless 指示BigInt值是否已无损转换。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_BIGINT_EXPECTED } 表示传入的参数不是BigInt类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetValueBigintInt64(JSVM_Env env,
                                                    JSVM_Value value,
                                                    int64_t* result,
                                                    bool* lossless);

/**
 * @brief 返回与给定的JavaScript BigInt等价的C uint64_t基础类型值。
 * 如果需要，它将截断该值，将lossless设置为false。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表JavaScript BigInt。
 * @param result 给定的JavaScript BigInt的C uint64_t基础类型等价值。
 * @param lossless 指示BigInt值是否已无损转换。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_BIGINT_EXPECTED } 表示传入的参数不是BigInt类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetValueBigintUint64(JSVM_Env env,
                                                     JSVM_Value value,
                                                     uint64_t* result,
                                                     bool* lossless);

/**
 * @brief 将单个BigInt值转换为符号位、64位小端数组和数组中的元素数。
 * signBit和words参数可以都设置为NULL。这种情况下，只获取wordCount。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表JavaScript BigInt。
 * @param signBit 表示JavaScript BigInt是正数还是负数的整数。
 * @param wordCount 必须初始化为words数组的长度。返回后，将被设置为存储此BigInt所需的实际字数。
 * @param words 指向预分配的64位字数组的指针。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_BIGINT_EXPECTED } 表示传入的参数不是BigInt类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetValueBigintWords(JSVM_Env env,
                                                    JSVM_Value value,
                                                    int* signBit,
                                                    size_t* wordCount,
                                                    uint64_t* words);

/**
 * @brief 检索之前传递给OH_JSVM_CreateExternal()的外部数据指针。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表JavaScript外部值。
 * @param result 指向被JavaScript外部值封装的数据的指针。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入参数非外部的JSVM_Value。
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetValueExternal(JSVM_Env env,
                                                 JSVM_Value value,
                                                 void** result);

/**
 * @brief 返回与给定的JavaScript number等价的C int32基础类型值。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表JavaScript number。
 * @param result 给定的JavaScript number的C int32基础类型等价值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_NUMBER_EXPECTED } 表示传入的参数不是number类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetValueInt32(JSVM_Env env,
                                              JSVM_Value value,
                                              int32_t* result);

/**
 * @brief 返回与给定的JavaScript number等价的C int64基础类型值。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表JavaScript number。
 * @param result 给定的JavaScript number的C int64基础类型等价值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_NUMBER_EXPECTED } 表示传入的参数不是number类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetValueInt64(JSVM_Env env,
                                              JSVM_Value value,
                                              int64_t* result);

/**
 * @brief 返回与传入值对应的ISO-8859-1编码字符串。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表JavaScript number。
 * @param buf 写入ISO-8859-1编码字符串的缓冲区。如果传入NULL，则将在result中返回
 * 字符串的长度（以字节为单位，不包括null结束符）。
 * @param bufsize 目的缓冲区大小。当大小不够时，返回的字符串将被截断并以null结尾。
 * @param result 复制到缓冲区中的字节数，不包括空终止符。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_STRING_EXPECTED } 表示传入的参数不是string类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetValueStringLatin1(JSVM_Env env,
                                                     JSVM_Value value,
                                                     char* buf,
                                                     size_t bufsize,
                                                     size_t* result);

/**
 * @brief 返回与传入值对应的UTF8编码字符串。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表JavaScript字符串。
 * @param buf 将UTF8编码的字符串写入的缓冲区。如果传入NULL，则在result中
 * 返回以字节为单位的字符串长度，不包括空终止符。
 * @param bufsize 目标缓冲区的大小。当此值不足时，返回的字符串将被截断并以null终止。
 * @param result 复制到缓冲区的字节数，不包括null结束符。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_STRING_EXPECTED } 表示传入的参数不是string类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetValueStringUtf8(JSVM_Env env,
                                                   JSVM_Value value,
                                                   char* buf,
                                                   size_t bufsize,
                                                   size_t* result);

/**
 * @brief 查询与传入值对应的UTF16编码字符串。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表JavaScript字符串。
 * @param buf 将UTF16-LE编码字符串写入的缓冲区。如果传入NULL，则返回字符串的
 * 2字节代码单元长度，不包括空终止符。
 * @param bufsize 目标缓冲区的大小。当此值不足时，返回的字符串将被截断并以null终止。
 * @param result 复制到缓冲区中的2字节代码单元数，不包括空终止符。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_STRING_EXPECTED } 表示传入的参数不是string类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetValueStringUtf16(JSVM_Env env,
                                                    JSVM_Value value,
                                                    char16_t* buf,
                                                    size_t bufsize,
                                                    size_t* result);

/**
 * @brief 返回与给定的JavaScript number等价的C uint_32基础类型值。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 代表JavaScript number。
 * @param result 将给定的JSVM_Value等效为uint32_t 的C基础类型。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_NUMBER_EXPECTED } 表示传入的参数不是number类型。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetValueUint32(JSVM_Env env,
                                               JSVM_Value value,
                                               uint32_t* result);

/**
 * @brief 返回表示给定布尔值的JavaScript单例对象。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要检索的布尔值，取值为true或false。
 * @param result 表示待检索的JavaScript Boolean单例。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetBoolean(JSVM_Env env,
                                           bool value,
                                           JSVM_Value* result);

/**
 * @brief 返回global对象。
 *
 * @param env 调用JSVM-API的环境。
 * @param result 代表JavaScript global对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetGlobal(JSVM_Env env,
                                          JSVM_Value* result);

/**
 * @brief 返回null对象。
 *
 * @param env 调用JSVM-API的环境。
 * @param result 代表JavaScript null对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetNull(JSVM_Env env,
                                        JSVM_Value* result);

/**
 * @brief 返回Undefined对象。
 *
 * @param env 调用JSVM-API的环境。
 * @param result 代表JavaScript undefined值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetUndefined(JSVM_Env env,
                                             JSVM_Value* result);

/**
 * @brief 实现抽象操作ToBoolean()。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要强制转换的JavaScript值。
 * @param result 代表强制的JavaScript Boolean。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CoerceToBool(JSVM_Env env,
                                             JSVM_Value value,
                                             JSVM_Value* result);

/**
 * @brief 实现抽象操作ToNumber()。
 * 如果传入的值是对象，则函数可能会运行JavaScript代码。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要强制转换的JavaScript值。
 * @param result 代表强制的JavaScript number。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_NUMBER_EXPECTED} 如果传入的JavaScript值无法转换成Number。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CoerceToNumber(JSVM_Env env,
                                               JSVM_Value value,
                                               JSVM_Value* result);

/**
 * @brief 实现抽象操作ToObject()。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要强制转换的JavaScript值。
 * @param result 代表强制的JavaScript object。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_OBJECT_EXPECTED} 如果传入的JavaScript值无法转换成Object。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CoerceToObject(JSVM_Env env,
                                               JSVM_Value value,
                                               JSVM_Value* result);

/**
 * @brief 实现抽象操作ToString()。
 * 如果传入的值是对象，则函数可能会运行JavaScript代码。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要强制转换的JavaScript值。
 * @param result 代表强制的JavaScript string。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_STRING_EXPECTED} 如果传入的JavaScript值无法转换成String。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CoerceToString(JSVM_Env env,
                                               JSVM_Value value,
                                               JSVM_Value* result);

/**
 * @brief 提供类似于在定义的对象上调用typeof运算符的行为。
 * 不同点在于，该函数支持检测外部值；它将null检测为单独的类型，
 * 而ECMAScript typeof将用于检测object。如果value的类型无效，则返回错误。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要查询其类型的JavaScript值。
 * @param result JavaScript值的类型。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_Typeof(JSVM_Env env,
                                       JSVM_Value value,
                                       JSVM_ValueType* result);

/**
 * @brief 提供类似于在对象上调用instanceof运算符的行为。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 要检查的JavaScript值。
 * @param constructor 要检查的构造函数的JavaScript函数对象。
 * @param result 如果object instanceof constructor为true，则设置为true的布尔值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_FUNCTION_EXPECTED } 表示传入的参数不是Function类型。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_Instanceof(JSVM_Env env,
                                           JSVM_Value object,
                                           JSVM_Value constructor,
                                           bool* result);

/**
 * @brief 提供类似于在对象上调用IsArray的行为。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JavaScript值。
 * @param result 表示给定的对象是否为数组。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsArray(JSVM_Env env,
                                        JSVM_Value value,
                                        bool* result);

/**
 * @brief 检查传入的对象是否为ArrayBuffer。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JavaScript值。
 * @param result 表示指定的对象是否为ArrayBuffer。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsArraybuffer(JSVM_Env env,
                                              JSVM_Value value,
                                              bool* result);

/**
 * @brief 检查传入的Object是否为日期。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JavaScript值。
 * @param isDate 给定的JSVM_Value是否表示JavaScript Date对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsDate(JSVM_Env env,
                                       JSVM_Value value,
                                       bool* isDate);

/**
 * @brief 检查传入的Object是否为类型化数组。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JavaScript值。
 * @param result 给定的JSVM_Value是否代表TypedArray。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsTypedarray(JSVM_Env env,
                                             JSVM_Value value,
                                             bool* result);

/**
 * @brief 检查传入的对象是否是DataView。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JavaScript值。
 * @param result 给定的JSVM_Value是否代表DataView。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsDataview(JSVM_Env env,
                                           JSVM_Value value,
                                           bool* result);

/**
 * @brief 提供类似调用严格相等算法的行为。
 *
 * @param env 调用JSVM-API的环境。
 * @param lhs 待检查的JavaScript值。
 * @param rhs 要检查的JavaScript值。
 * @param result 表示两个JSVM_Value对象是否严格相等（===）。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_StrictEquals(JSVM_Env env,
                                             JSVM_Value lhs,
                                             JSVM_Value rhs,
                                             bool* result);

/**
 * @brief 提供类似调用宽松相等算法的行为。
 * 无论JavaScript值类型如何，只要值相等，就返回true。
 *
 * @param env 调用JSVM-API的环境。
 * @param lhs 待检查的JavaScript值。
 * @param rhs 要检查的JavaScript值。
 * @param result 表示两个JSVM_Value对象是否宽松相等（==）。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_Equals(JSVM_Env env,
                                       JSVM_Value lhs,
                                       JSVM_Value rhs,
                                       bool* result);

/**
 * @brief 提供类似于调用ArrayBuffer detach操作的行为。
 *
 * @param env 调用JSVM-API的环境。
 * @param arraybuffer 待分离的JavaScript ArrayBuffer。
 * @return 返回执行状态码 JSVM_Status。
 *         如果{@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_DETACHABLE_ARRAYBUFFER_EXPECTED } 表示传入的参数不是可分析的ArrayBuffer。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_DetachArraybuffer(JSVM_Env env,
                                                  JSVM_Value arraybuffer);

/**
 * @brief 提供类似调用ArrayBuffer IsDetachedBuffer操作的行为。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JavaScript ArrayBuffer。
 * @param result 表示ArrayBuffer是否被分离。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsDetachedArraybuffer(JSVM_Env env,
                                                      JSVM_Value value,
                                                      bool* result);

/**
 * @brief 以字符数数组的形式返回object的可枚举属性的名称。
 * key为符号的object的属性将不会被包含在内。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 待进行属性检索的对象。
 * @param result 表示一个JavaScript值的数组，这些值表示对象的属性名称。
 * 可以使用OH_JSVM_GetArrayLength以及OH_JSVM_GetElement对结果进行迭代。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetPropertyNames(JSVM_Env env,
                                                 JSVM_Value object,
                                                 JSVM_Value* result);

/**
 * @brief 返回包含object所有可用属性名称的数组。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 从中检索属性的对象。
 * @param keyMode 是否也检索原型属性。
 * @param keyFilter 要检索哪些属性（可枚举/可读/可写）。
 * @param keyConversion 表示是否将编号的属性键转换为字符串。
 * @param result 表示JavaScript值的数组，这些值表示对象的属性名称。
 * 可以使用OH_JSVM_GetArrayLength和OH_JSVM_GetElement对结果进行迭代。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetAllPropertyNames(JSVM_Env env,
                                                    JSVM_Value object,
                                                    JSVM_KeyCollectionMode keyMode,
                                                    JSVM_KeyFilter keyFilter,
                                                    JSVM_KeyConversion keyConversion,
                                                    JSVM_Value* result);

/**
 * @brief 为传入的object设置名为key的属性。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 将进行属性设置的对象。
 * @param key 待设置的属性名。
 * @param value 属性值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_SetProperty(JSVM_Env env,
                                            JSVM_Value object,
                                            JSVM_Value key,
                                            JSVM_Value value);

/**
 * @brief 从传入的object中获取名为key的属性。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 从中检索属性的对象。
 * @param key 要检索的属性的名称。
 * @param result 属性值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetProperty(JSVM_Env env,
                                            JSVM_Value object,
                                            JSVM_Value key,
                                            JSVM_Value* result);

/**
 * @brief 检查传入的Object是否具有命名为key的属性。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 待查询的对象。
 * @param key 要检查其存在的属性的名称。
 * @param result 该属性是否存在于对象上。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_HasProperty(JSVM_Env env,
                                            JSVM_Value object,
                                            JSVM_Value key,
                                            bool* result);

/**
 * @brief  尝试从object中删除名为key的属性。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 待查询的对象。
 * @param key 待删除的属性名。
 * @param result 表示属性删除是否成功。result可以选择性地通过传递NULL来忽略。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_DeleteProperty(JSVM_Env env,
                                               JSVM_Value object,
                                               JSVM_Value key,
                                               bool* result);

/**
 * @brief 检查传入的Object是否具有名为key的属性。
 * key必须是string或symbol，否则将抛出错误。JSVM-API不会执行任何数据类型之间的转换。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 待查询的对象。
 * @param key 要检查的是否存在的属性名称。
 * @param result 表示对象是否存在该属性。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_NAME_EXPECTED } 表示期望传入名字不合法。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_HasOwnProperty(JSVM_Env env,
                                               JSVM_Value object,
                                               JSVM_Value key,
                                               bool* result);

/**
 * @brief 此方法等效于object调用OH_JSVM_SetProperty设置名为`utf8Name`的属性。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 要对其设置属性的对象。
 * @param utf8name 要设置的属性的名称。
 * @param value 属性值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_SetNamedProperty(JSVM_Env env,
                                                 JSVM_Value object,
                                                 const char* utf8name,
                                                 JSVM_Value value);

/**
 * @brief 此方法等效于object调用OH_JSVM_GetProperty获取名为`utf8Name`的属性对象。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 从中检索属性的对象。
 * @param utf8name 要获取的属性名。
 * @param result 属性值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetNamedProperty(JSVM_Env env,
                                                 JSVM_Value object,
                                                 const char* utf8name,
                                                 JSVM_Value* result);

/**
 * @brief 此方法等效于object对象调用OH_JSVM_HasProperty查询其内部是否存在名为`utf8Name`的属性。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 待查询的对象。
 * @param utf8name 待检查的属性名。
 * @param result 该属性是否存在于对象上。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_HasNamedProperty(JSVM_Env env,
                                                 JSVM_Value object,
                                                 const char* utf8name,
                                                 bool* result);

/**
 * @brief 在传入的Object上设置一个元素。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 待进行属性设置的对象。
 * @param index 要设置的属性的索引。
 * @param value 属性值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_SetElement(JSVM_Env env,
                                           JSVM_Value object,
                                           uint32_t index,
                                           JSVM_Value value);

/**
 * @brief 获取请求索引处的元素。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 待进行属性检索的对象。
 * @param index 要获取的属性的索引。
 * @param result 属性值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetElement(JSVM_Env env,
                                           JSVM_Value object,
                                           uint32_t index,
                                           JSVM_Value* result);

/**
 * @brief 如果传入的Object在指定的索引处有一个元素，则此JSVM-API返回true。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 待查询的对象。
 * @param index 待确定是否存在元素的索引位置。
 * @param result 该属性是否存在于对象上。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_HasElement(JSVM_Env env,
                                           JSVM_Value object,
                                           uint32_t index,
                                           bool* result);

/**
 * @brief 尝试从object中删除指定index处的元素。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 待查询的对象。
 * @param index 要删除的属性的索引。
 * @param result 表示元素删除是否成功。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_DeleteElement(JSVM_Env env,
                                              JSVM_Value object,
                                              uint32_t index,
                                              bool* result);

/**
 * @brief 通过此方法可以在给定对象上高效定义多个属性，这些属性使用属性描述符进行定义。
 * 通过一个属性描述符的数组，此API将为对象依次设置数组中的属性。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 待进行属性检索的对象。
 * @param propertyCount properties数组中的元素数。
 * @param properties 属性描述符的数组。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_DefineProperties(JSVM_Env env,
                                                 JSVM_Value object,
                                                 size_t propertyCount,
                                                 const JSVM_PropertyDescriptor* properties);

/**
 * @brief 冻结指定的对象，防止为其添加新的属性、删除现有属性、更改现有属性的
 * 可枚举性/可配置性/可写性、更改现有属性的值、改变对象原型等操作。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 待冻结的对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ObjectFreeze(JSVM_Env env,
                                             JSVM_Value object);

/**
 * @brief 封装指定的对象，防止为其添加新的属性并将所有现有属性标记为不可配置。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 待封装的对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ObjectSeal(JSVM_Env env,
                                           JSVM_Value object);

/**
 * @brief 支持从native代码调用JavaScript函数对象，
 * 这是从native代码回调到JavaScript的主要机制。
 *
 * @param env 调用JSVM-API的环境。
 * @param recv 传递给被调用函数的this值。
 * @param func 表示将调用的JavaScript函数。
 * @param argc argv数组中的元素个数。
 * @param argv JSVM_values数组，表示将作为参数传递给函数的JavaScript值。
 * @param result 表示返回的JavaScript对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CallFunction(JSVM_Env env,
                                             JSVM_Value recv,
                                             JSVM_Value func,
                                             size_t argc,
                                             const JSVM_Value* argv,
                                             JSVM_Value* result);

 /**
 * @brief 支持在native代码中创建函数对象，这是从JavaScript调用native代码的主要机制。
 * 在此调用之后，新创建的函数在脚本中不再自动可见。相反，必须在JavaScript可见的任何对象上显示设置属性，
 * 才能从脚本访问该函数。
 *
 * @param env 调用JSVM-API的环境。
 * @param utf8name 编码为UTF8的函数的可选名称。这在JavaScript中是可见的，
 * 作为新函数对象的name属性。
 * @param length utf8name的长度（以字节为单位）或JSVM_AUTO_LENGTH（如果以 null 结尾）。
 * @param cb 调用此函数对象时应调用的native函数。详情请参考JSVM_Callback。
 * @param result 表示新创建函数的JavaScript函数对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateFunction(JSVM_Env env,
                                               const char* utf8name,
                                               size_t length,
                                               JSVM_Callback cb,
                                               JSVM_Value* result);

 /**
 * @brief 此方法在回调函数中用于检索有关调用的详细信息，
 * 例如来自给定回调信息的参数和this指针。
 *
 * @param env 调用JSVM-API的环境。
 * @param cbinfo 传入回调函数的回调信息。
 * @param argc 指定所提供的argv数组的长度并接收参数的实际数量，
 * 可以通过传递NULL来选择性地忽略。
 * @param argv JSVM_Value的C数组，用于存储复制的参数。如果参数数量超过提供的数量，
 * 则只复制请求数量的参数。如果提供的参数比声明的少，则argv的其余部分将由代表undefined
 * 的JSVM_Value值填充。可以通过传递NULL来忽略argv。
 * @param thisArg 接收调用的JavaScript this参数。thisArg可以通过传递NULL来进行忽略。
 * @param data 接收回调的数据指针。data可以通过传递NULL来进行忽略。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetCbInfo(JSVM_Env env,
                                          JSVM_CallbackInfo cbinfo,
                                          size_t* argc,
                                          JSVM_Value* argv,
                                          JSVM_Value* thisArg,
                                          void** data);

/**
 * @brief 返回构造函数调用的new target。
 * 如果当前回调不是构造函数调用，结果为NULL。
 *
 * @param env 调用JSVM-API的环境。
 * @param cbinfo 传递给回调函数的回调信息。
 * @param result 构造函数调用的new target。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetNewTarget(JSVM_Env env,
                                             JSVM_CallbackInfo cbinfo,
                                             JSVM_Value* result);

/**
 * @brief 使用给定的JSVM_Value表示的构造函数来实例化新的JavaScript值。
 *
 * @param env 调用JSVM-API的环境。
 * @param constructor 表示将作为构造函数调用的JavaScript函数。
 * @param argc argv数组中的元素个数。
 * @param argv JavaScript值数组。其中JSVM_Value表示构造函数的参数。
 * 如果argc为零，则可以通过传入NULL来忽略此参数。
 * @param result 表示返回的JavaScript对象，在本例中是构造的对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_NewInstance(JSVM_Env env,
                                            JSVM_Value constructor,
                                            size_t argc,
                                            const JSVM_Value* argv,
                                            JSVM_Value* result);

/**
 * @brief 定义一个JavaScript类。
 *
 * @param env 调用JSVM-API的环境。
 * @param utf8name JavaScript构造函数的名称，建议在包装C++类时使用C++类名。
 * @param length utf8name的长度（以字节为单位）或JSVM_AUTO_LENGTH（如果以 null 结尾）。
 * @param constructor 用于创建类的构造函数的回调函数。包装C++类时，此方法必须是符合JSVM_Callback。
 * callback签名的静态成员。不能使用C++类构造函数。详情请参考JSVM_Callback。
 * @param propertyCount properties数组参数中的项数。
 * @param properties 类的属性描述符，用于定义类的属性和方法。
 * @param result 表示类的构造函数的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_DefineClass(JSVM_Env env,
                                            const char* utf8name,
                                            size_t length,
                                            JSVM_Callback constructor,
                                            size_t propertyCount,
                                            const JSVM_PropertyDescriptor* properties,
                                            JSVM_Value* result);

/**
 * @brief 在JavaScript对象中封装native实例，该实例后续可以通过OH_JSVM_Unwrap()进行检索。
 *
 * @param env 调用JSVM-API的环境。
 * @param jsObject 将成为原生对象封装器的JavaScript对象。
 * @param nativeObject 将封装在JavaScript对象中的native实例。
 * @param finalizeCb 可选的原生回调，可用于在 JavaScript 对象被垃圾回收时释放native实例。
 * @param finalizeHint 传递给完成回调的可选上下文提示。
 * @param result 对封装对象的可选引用。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_Wrap(JSVM_Env env,
                                     JSVM_Value jsObject,
                                     void* nativeObject,
                                     JSVM_Finalize finalizeCb,
                                     void* finalizeHint,
                                     JSVM_Ref* result);

/**
 * @brief 当JavaScript代码调用类的方法或属性访问器时，对应的JSVM_Callback将被调用。
 * 如果回调是针对实例方法或访问器的，则回调的this参数是封装器对象；然后可以通过调用
 * 封装器对象的OH_JSVM_Unwrap()获得作为调用目标的C++实例。
 *
 * @param env 调用JSVM-API的环境。
 * @param jsObject 与native实例关联的对象。
 * @param result 指向封装的native实例的指针。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_Unwrap(JSVM_Env env,
                                       JSVM_Value jsObject,
                                       void** result);

/**
 * @brief 使用OH_JSVM_Wrap()检索先前封装在JavaScript对象——js_object中的native实例并移除封装。
 * 如果finalize回调与封装相关联，则当JavaScript对象被垃圾回收时将不再调用它。
 *
 * @param env 调用JSVM-API的环境。
 * @param jsObject 与native实例关联的对象。
 * @param result 指向封装的native实例的指针。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_RemoveWrap(JSVM_Env env,
                                           JSVM_Value jsObject,
                                           void** result);

/**
 * @brief 将typeTag指针的值与JavaScript对象或外部值相关联。可调用OH_JSVM_CheckObjectTypeTag()
 * 判断附加在对象上的标记类型，以确保对象的类型正确。如果对象已经有关联的类型标记，则返回JSVM_INVALID_ARG。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要标记的JavaScript对象或外部值。
 * @param typeTag 要标记对象的标签。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_TypeTagObject(JSVM_Env env,
                                              JSVM_Value value,
                                              const JSVM_TypeTag* typeTag);

/**
 * @brief 将类型标签typeTag与JavaScript对象或外部值上的标签作对比。如果找到相同标签，
 * 设置result为true，否则为false。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查类型标记的JavaScript对象或外部值。
 * @param typeTag 用于比较在对象上找到的任何标签的标签。
 * @param result 表示指定的类型标记是否与对象上的类型标记匹配。如果在对象上找不到该类型标记，也会返回false。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CheckObjectTypeTag(JSVM_Env env,
                                                   JSVM_Value value,
                                                   const JSVM_TypeTag* typeTag,
                                                   bool* result);

/**
 * @brief 为JavaScript对象添加JSVM_Finalize回调，当JavaScript对象被垃圾回收时调用该回调函数。
 * 可以在单个JavaScript对象上多次调用OH_JSVM_AddFinalizer。
 *
 * @param env 调用JSVM-API的环境。
 * @param jsObject 关联native数据的JavaScript对象。
 * @param finalizeData 要传递给finalizeCb的可选数据。
 * @param finalizeCb 当JavaScript对象被垃圾回收时，将用于释放native
 * 数据的原生回调。JSVM_Finalize提供了更多详细信息。
 * @param finalizeHint 传递给finalize回调的可选上下文提示。
 * @param result 可选的对JavaScript对象的引用。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的参数不合法。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_AddFinalizer(JSVM_Env env,
                                             JSVM_Value jsObject,
                                             void* finalizeData,
                                             JSVM_Finalize finalizeCb,
                                             void* finalizeHint,
                                             JSVM_Ref* result);

/**
 * @brief 返回JSVM运行时支持的最高JSVM-API版本。
 * 后续将新增JSVM-API，以便支持更多的功能。引入该API的目的：在支持某功能的JSVM版本，
 * 可以使用新的功能；在不支持某功能的JSVM版本，可以提供回调行为。
 *
 * @param env 调用JSVM-API的环境。
 * @param result 支持的最高版本的JSVM-API。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetVersion(JSVM_Env env,
                                           uint32_t* result);

/**
 * @brief 返回虚拟机的信息。
 *
 * @param result 虚拟机的信息。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetVMInfo(JSVM_VMInfo* result);

/**
 * @brief 此函数将因JavaScript对象而保持活跃的外部分配的内存大小通知给底层虚拟机。
 * 注册外部分配的内存将比其他方式更频繁地触发全局垃圾回收。
 *
 * @param env 调用JSVM-API的环境。
 * @param changeInBytes 因JavaScript对象而保持活动状态的外部分配内存的变化。
 * @param result 调整值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_AdjustExternalMemory(JSVM_Env env,
                                                     int64_t changeInBytes,
                                                     int64_t* result);

/**
 * @brief 通知虚拟机系统内存不足并有选择地触发垃圾回收。
 *
 * @param env 调用JSVM-API的环境。
 * @param level 要为当前虚拟机设置的内存压力等级。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_MemoryPressureNotification(JSVM_Env env,
                                                           JSVM_MemoryPressureLevel level);

/**
 * @brief 创建一个延迟对象和一个JavaScript promise。
 *
 * @param env 调用JSVM-API的环境。
 * @param deferred 一个新创建的延迟对象，后续可以传递给OH_JSVM_ResolveDeferred()或
 * OH_JSVM_RejectDeferred()以解析或拒绝相关的Promise。
 * @param promise 与延迟对象关联的JavaScript Promise。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreatePromise(JSVM_Env env,
                                              JSVM_Deferred* deferred,
                                              JSVM_Value* promise);

/**
 * @brief 通过与之关联的延迟对象来解析JavaScript promise。
 * 它只能用于解析对应的可用的延迟对象的JavaScript Promise。
 * 这意味着Promise必须使用OH_JSVM_CreatePromise()创建，并且
 * 从该调用返回的对象必须保留，才能将其传递给此API。
 *
 * @param env 调用JSVM-API的环境。
 * @param deferred 要解析其关联promise的延迟对象。
 * @param resolution 用来解决Promise的值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ResolveDeferred(JSVM_Env env,
                                                JSVM_Deferred deferred,
                                                JSVM_Value resolution);

/**
 * @brief 通过与之关联的延迟对象来拒绝JavaScript Promise。
 * 它只能用于拒绝对应的可用延迟对象的JavaScript Promise。
 * 这意味着Promise必须使用OH_JSVM_CreatePromise()创建，并且
 * 从该调用返回的对象必须保留，才能将其传递给此API。
 *
 * @param env 调用JSVM-API的环境。
 * @param deferred 要解析其关联promise的延迟对象。
 * @param rejection 用来拒绝Promise的值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_RejectDeferred(JSVM_Env env,
                                               JSVM_Deferred deferred,
                                               JSVM_Value rejection);

/**
 * @brief 查询Promise是否为原生Promise对象。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的值。
 * @param isPromise 表示是否为原生Promise对象（即底层引擎创建的promise对象）的标志。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsPromise(JSVM_Env env,
                                          JSVM_Value value,
                                          bool* isPromise);

/**
 * @brief 注册 处理Promise兑现/拒绝的 回调函数。
 * @param env 调用 JSVM-API 的环境。
 * @param promise 需要注册回调的 promise。
 * @param onFulfilled 该函数在 promise 兑现后调用。
 * @param onRejected 该函数在 promise 拒绝后调用。
 * @param result 输出参数，返回 promise 调用 then/catch 接口后生成的新的 promise。
 * @return 返回执行状态码。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 如果 env 或 promise 为空，或 onFulfilled 和 onRejected 同时为空。\n
 *         {@link JSVM_INVALID_TYPE } 如果 promise 非 JS 的 Promise 类型，或 onFulfilled、onRejected 非 JS 的 Function 类型。\n
 *         {@link JSVM_PENDING_EXCEPTION} 如果存在 JS 异常待处理。\n
 *         {@link JSVM_GENERIC_FAILURE} 如果 API 执行错误。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_PromiseRegisterHandler(JSVM_Env env,
                                                       JSVM_Value promise,
                                                       JSVM_Value onFulfilled,
                                                       JSVM_Value onRejected,
                                                       JSVM_Value* result);

/**
 * @brief 解析JSON字符串，并返回成功解析的值。
 *
 * @param env 调用JSVM-API的环境。
 * @param jsonString 待解析的字符串。
 * @param result 成功解析的值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_STRING_EXPECTED } 表示传入的参数不是string类型。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_JsonParse(JSVM_Env env,
                                          JSVM_Value jsonString,
                                          JSVM_Value* result);

/**
 * @brief 将对象字符串化，并返回成功转换后的字符串。
 *
 * @param env 调用JSVM-API的环境。
 * @param jsonObject 待字符串化的对象。
 * @param result 成功转换后返回的字符串。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_JsonStringify(JSVM_Env env,
                                              JSVM_Value jsonObject,
                                              JSVM_Value* result);

/**
 * @brief 创建虚拟机的启动快照。
 *
 * @param vm 目标环境，API接口将在该环境下调用。
 * @param contextCount 上下文个数。
 * @param contexts 要添加到快照的上下文数组。
 * @param blobData 快照数据。
 * @param blobSize 快照数据的大小。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 11
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateSnapshot(JSVM_VM vm,
                                               size_t contextCount,
                                               const JSVM_Env* contexts,
                                               const char** blobData,
                                               size_t* blobSize);

/**
 * @brief 返回一组虚拟机堆的统计数据。
 *
 * @param vm 返回堆统计信息的虚拟机。
 * @param result 堆统计数据。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetHeapStatistics(JSVM_VM vm,
                                                  JSVM_HeapStatistics* result);

/**
 * @brief 创建并启动一个CPU profiler。
 *
 * @param vm 启动CPU profiler的虚拟机。
 * @param result 指向CPU profiler的指针。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_StartCpuProfiler(JSVM_VM vm,
                                                 JSVM_CpuProfiler* result);

/**
 * @brief 停止CPU profiler并将结果输出到流。
 *
 * @param vm 启动CPU profiler的虚拟机。
 * @param profiler 要停止的CPU profiler。
 * @param stream 接收数据的输出流回调。
 * @param streamData 传递给输出流回调的可选数据。例如，可以是一个文件流，用来将输出流回调中传递的采样数据写入文件。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_StopCpuProfiler(JSVM_VM vm,
                                                JSVM_CpuProfiler profiler,
                                                JSVM_OutputStream stream,
                                                void* streamData);

/**
 * @brief 获取当前堆快照并将其输出到流。
 *
 * @param vm 将被获取堆快照的虚拟机。
 * @param stream 接收数据的输出流回调。
 * @param streamData 传递给输出流回调的可选数据。例如，可以是一个文件流，用来将输出流回调中传递的采样数据写入文件。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_TakeHeapSnapshot(JSVM_VM vm,
                                                 JSVM_OutputStream stream,
                                                 void* streamData);

/**
 * @brief 获取当前堆快照并将其以原始堆格式（二进制格式）输出到流。原始堆格式是VM特定的，其布局不保证在不同版本之间稳定。
 * 此操作可能会暂时暂停应用程序，频繁调用可能会生成大型快照文件并增加磁盘使用量，因此调用者应适当管理生成的文件（如果文件写入磁盘）。
 * 流回调在VM运行的线程上同步调用。回调应避免长时间阻塞操作。如果回调返回false，则中止输出流，停止快照生成。
 *
 * @param vm 将被获取堆快照的虚拟机。
 * @param stream 接收二进制数据的输出流回调。
 * @param streamData 传递给输出流回调的可选数据。
 * @return 返回JSVM函数执行结果码。
 *         {@link JSVM_INVALID_ARG } 表示vm或stream为NULL。
 *         {@link JSVM_OK } 表示其他所有情况。
 * @since 26.0.0
 */
JSVM_EXTERN JSVM_Status OH_JSVM_TakeRawHeapSnapshot(JSVM_VM vm,
                                                    JSVM_OutputStream stream,
                                                    void* streamData);

/**
 * @brief 为VM设置堆阈值回调，VM只能有一个堆阈值回调。当不再需要时，应通过OH_JSVM_ClearHeapThresholdCallback清除已注册的回调。
 * 此API不是线程安全的，必须在VM运行的线程上调用。在GC前后检查阈值，当观察到的堆使用量大于或等于阈值时调用回调。
 * 回调在同一线程上同步调用，回调运行期间跳过阈值检查。回调返回后，如果堆使用量仍大于或等于阈值，将在下一次GC前后再次调用回调。
 * 回调返回后无需再次注册。已注册的回调通过（threshold, callback, data）标识。
 *
 * @param vm 将被监控堆使用量的虚拟机。
 * @param threshold 堆使用量阈值（以字节为单位）。该值必须大于0且不得超过heapSizeLimit，其中heapSizeLimit是JSVM_HeapStatistics中的字段。
 * @param callback 当阈值检查观察到堆使用量大于或等于阈值时要调用的回调函数。
 * @param data 传递给回调的可选用户提供的数据。调用者负责管理此数据的生命周期。
 * @return 返回JSVM函数执行结果码。
 *         {@link JSVM_OK } 表示函数执行成功。
 *         {@link JSVM_INVALID_ARG } 表示vm或callback为NULL，或threshold为零或超过heapSizeLimit，或VM已注册堆阈值回调。
 * @since 26.0.0
 */
JSVM_EXTERN JSVM_Status OH_JSVM_SetHeapThresholdCallback(JSVM_VM vm,
                                                         uint64_t threshold,
                                                         JSVM_HandlerForHeapThreshold callback,
                                                         void* data);

/**
 * @brief 清除之前为VM注册的堆阈值回调。此API不是线程安全的，必须在VM运行的线程上调用。已注册的回调通过（threshold, callback, data）标识。
 *
 * @param vm 将被清除堆阈值回调的虚拟机。
 * @param threshold 先前注册的堆使用量阈值（以字节为单位）。
 * @param callback 先前通过OH_JSVM_SetHeapThresholdCallback注册的回调函数。
 * @param data 注册时使用的用户提供的数据。
 * @return 返回JSVM函数执行结果码。
 *         {@link JSVM_OK } 表示函数执行成功。
 *         {@link JSVM_INVALID_ARG } 表示vm或callback为NULL，或（threshold, callback, data）与已注册的回调不匹配。
 * @since 26.0.0
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ClearHeapThresholdCallback(JSVM_VM vm,
                                                           uint64_t threshold,
                                                           JSVM_HandlerForHeapThreshold callback,
                                                           void* data);

/**
 * @brief 在指定的主机和端口上激活inspector，将用来调试JS代码。
 *
 * @param env 调用JSVM-API的环境。
 * @param host 要监听inspector连接的主机IP地址。
 * @param port 要监听inspector连接的端口。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_OpenInspector(JSVM_Env env,
                                              const char* host,
                                              uint16_t port);

/**
 * @brief 尝试关闭剩余的所有inspector连接。
 *
 * @param env 调用JSVM-API的环境。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CloseInspector(JSVM_Env env);

/**
 * @brief 等待主机与inspector建立socket连接，连接建立后程序将继续运行。
 * 发送Runtime.runIfWaitingForDebugger命令。
 *
 * @param env 调用JSVM-API的环境。
 * @param breakNextLine 是否在下一行JavaScript代码中中断。
 * breakNextLine为true将暂停运行下一行JS代码，开发者需要通过调试器的调试按钮控制JS继续执行。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_WaitForDebugger(JSVM_Env env,
                                                bool breakNextLine);

/**
 * @brief 定义一个具有给定类名、构造函数、属性和回调处理程序的JavaScript类，
 * 属性操作包括getter、setter、deleter、enumerator等，并作为函数回调进行调用。
 *
 * @param env 调用JSVM-API的环境。
 * @param utf8name JavaScript类构造函数的名称。
 * @param length utf8name的长度（以字节为单位）或JSVM_AUTO_LENGTH（如果以 null 结尾）。
 * @param constructor 用于创建类的构造函数的回调函数。此方法必须是JSVM_Callback类型。
 * constructor中callback回调需为静态成员。不能使用C++类构造函数。详情请参考JSVM_Callback。
 * @param propertyCount properties数组参数中的项数。
 * @param properties 描述静态数据和实例数据的属性描述符数组类上的属性、访问器和方法请参考JSVM_PropertyDescriptor。
 * @param propertyHandlerCfg 访问实例对象属性触发相应的回调函数。
 * @param callAsFunctionCallback 将实例对象作为函数调用将触发此回调。
 * @param result 表示JavaScript类的构造函数的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示执行的过程中产生了JS异常。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示有未知的原因导致执行失败。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_DefineClassWithPropertyHandler(JSVM_Env env,
                                                               const char* utf8name,
                                                               size_t length,
                                                               JSVM_Callback constructor,
                                                               size_t propertyCount,
                                                               const JSVM_PropertyDescriptor* properties,
                                                               JSVM_PropertyHandlerCfg propertyHandlerCfg,
                                                               JSVM_Callback callAsFunctionCallback,
                                                               JSVM_Value* result);

/**
 * @brief 判断当前线程是否持有指定环境的锁。只有持有锁的线程才能使用该环境。
 *
 * @param env 调用该API的环境。
 * @param isLocked 输出参数，指示当前线程是否持有环境锁的标志。true为持有环境锁，false为不持有环境锁。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsLocked(JSVM_Env env, bool* isLocked);

/**
 * @brief 获取指定环境的锁。只有持有锁的线程才能使用该环境。
 *
 * @param env 调用该API的环境。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_AcquireLock(JSVM_Env env);

/**
 * @brief 释放指定环境的锁。只有持有锁的线程才能使用该环境。
 *
 * @param env 调用该API的环境。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ReleaseLock(JSVM_Env env);

/**
 * @brief 此API检查传入的值是否为Undefined。
 * 这相当于JS中的`value === undefined`。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param isUndefined 表示给定的JSVM_Value是否为Undefined。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功，这个API不会触发任何异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsUndefined(JSVM_Env env,
                                            JSVM_Value value,
                                            bool* isUndefined);

/**
 * @brief 此API检查传入的值是否为Null对象。
 * 这相当于JS中的`value === null`。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param isNull 表示给定的JSVM_Value是否为Null。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功，这个API不会触发任何异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsNull(JSVM_Env env,
                                       JSVM_Value value,
                                       bool* isNull);

/**
 * @brief 此API检查传入的值是否为Null或Undefined。
 * 这相当于JS中的`value == null`。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param isNullOrUndefined 表示给定的JSVM_Value是否为Null或Undefined。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功，这个API不会触发任何异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsNullOrUndefined(JSVM_Env env,
                                                  JSVM_Value value,
                                                  bool* isNullOrUndefined);

/**
 * @brief 此API检查传入的值是否为Boolean。
 * 这相当于JS中的`typeof value === 'boolean'`。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param isBoolean 表示给定的JSVM_Value是否为Boolean。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功，这个API不会触发任何异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsBoolean(JSVM_Env env,
                                          JSVM_Value value,
                                          bool* isBoolean);

/**
 * @brief 此API检查传入的值是否为Number。
 * 这相当于JS中的`typeof value === 'number'`。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param isNumber 表示给定的JSVM_Value是否为Number。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功，这个API不会触发任何异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsNumber(JSVM_Env env,
                                         JSVM_Value value,
                                         bool* isNumber);

/**
 * @brief 此API检查传入的值是否为String。
 * 这相当于JS中的`typeof value === 'string'`。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param isString 表示给定的JSVM_Value是否为String。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功，这个API不会触发任何异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsString(JSVM_Env env,
                                         JSVM_Value value,
                                         bool* isString);

/**
 * @brief 此API检查传入的值是否为Symbol。
 * 这相当于JS中的`typeof value === 'symbol'`。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param isSymbol 表示给定的JSVM_Value是否为Symbol。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功，这个API不会触发任何异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsSymbol(JSVM_Env env,
                                         JSVM_Value value,
                                         bool* isSymbol);

/**
 * @brief 此API检查传入的值是否为Function。
 * 这相当于JS中的`typeof value === 'function'`。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param isFunction 表示给定的JSVM_Value是否为Function。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功，这个API不会触发任何异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsFunction(JSVM_Env env,
                                           JSVM_Value value,
                                           bool* isFunction);

/**
 * @brief 此API检查传入的值是否为Object。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param isObject 表示给定的JSVM_Value是否为Object。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功，这个API不会触发任何异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsObject(JSVM_Env env,
                                         JSVM_Value value,
                                         bool* isObject);

/**
 * @brief 此API检查传入的值是否为BigInt。
 * 这相当于JS中的`typeof value === 'bigint'`。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param isBigInt 表示给定的JSVM_Value是否为BigInt。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功，这个API不会触发任何异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsBigInt(JSVM_Env env,
                                         JSVM_Value value,
                                         bool* isBigInt);

/**
 * @brief 此API返回与JavaScript Map类型对应的JavaScript值。
 *
 * @param env 调用JSVM-API的环境。
 * @param result 代表JavaScript Map的JSVM_Value。
 * @return 返回执行状态码JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示输入参数不合法。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateMap(JSVM_Env env, JSVM_Value* result);

/**
 * @brief 此API检查传入的值是否为Map。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param isMap 给定的值是否为Map。
 * @return 返回执行状态码JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示输入参数不合法。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsMap(JSVM_Env env,
                                      JSVM_Value value,
                                      bool* isMap);

/**
 * @brief 此API检查传入的值是否为构造函数。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param isConstructor 给定的值是否为构造函数。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示输入参数不合法。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsConstructor(JSVM_Env env,
                                              JSVM_Value value,
                                              bool* isConstructor);

/**
 * @brief 此API返回与输入的JavaScript字符串对应的正则表达式对象。
 * 接口可能会抛出异常。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 要转换为正则表达式的JavaScript字符串。
 * @param flags 正则表达式标志位。
 * @param result 代表JavaScript RegExp的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示输入参数不合法。\n
 *         {@link JSVM_PENDING_EXCPTION } 表示API在运行时抛出异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateRegExp(JSVM_Env env,
                                             JSVM_Value value,
                                             JSVM_RegExpFlags flags,
                                             JSVM_Value* result);

/**
 * @brief 获取JavaScript object的原型。
 *
 * @param env 调用JSVM-API的环境。
 * @param object  表示待返回其原型的JavaScript object。
 * @param result 表示给定对象的原型。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示输入参数不合法。\n
 *         {@link JSVM_PENDING_EXCPTION } 表示API在运行时抛出异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ObjectGetPrototypeOf(JSVM_Env env,
                                                     JSVM_Value object,
                                                     JSVM_Value* result);

/**
 * @brief 设置给定的JavaScript object的原型。
 *
 * @param env 调用JSVM-API的环境。
 * @param object 表示需要设置原型的JavaScript object。
 * @param prototype 对象原型。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示输入参数不合法。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示设置原型失败。如循环设置原型时，会触发该失败。\n
 *         {@link JSVM_PENDING_EXCPTION } 表示API在运行时抛出异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ObjectSetPrototypeOf(JSVM_Env env,
                                                     JSVM_Value object,
                                                     JSVM_Value prototype);

/**
 * @brief 创建JavaScript Set对象。
 *
 * @param env 调用JSVM-API的环境。
 * @param result 表示已经创建的JavaScript Set对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示输入参数不合法。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateSet(JSVM_Env env,
                                          JSVM_Value* result);

/**
 * @brief 判断给定的对象是否是Set类型。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的对象。
 * @param isSet 给定的对象是否是Set类型。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示输入参数不合法。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsSet(JSVM_Env env,
                                      JSVM_Value value,
                                      bool* isSet);

/**
 * @brief 实现抽象操作`ToBigInt()`。
 *
 * @param env 调用该JSVM-API的环境。
 * @param value 要进行强制转换的JavaScript值。
 * @param result 表示成功转换成BigInt后的JavaScript值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_BIGINT_EXPECTED} 如果传入的JavaScript值无法转换成BigInt。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CoerceToBigInt(JSVM_Env env,
                                               JSVM_Value value,
                                               JSVM_Value* result);

/**
 * @brief 此API检查传入的值是否为JavaScript RegExp对象。
 *
 * @param env 调用JSVM-API的环境。
 * @param value 待检查的JSVM_Value。
 * @param result 表示给定的JSVM_Value是否为JavaScript RegExp对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsRegExp(JSVM_Env env,
                                         JSVM_Value value,
                                         bool* result);

/**
 * @brief 创建一个以给定JavaScript为函数体的函数。
 *
 * @param env 调用JSVM-API的环境。
 * @param funcName 包含函数名称的字符串。如果传入NULL，则创建一个匿名函数。
 * @param length funcName的长度（以字节为单位）或JSVM_AUTO_LENGTH（如果以 null 结尾）。
 * @param argc argv数组中的元素个数。
 * @param argv JSVM_values数组，表示将作为参数传递给函数的JavaScript值。
 * @param script 包含作为函数体的JavaScript字符串。
 * @param result 表示新创建函数的JavaScript函数对象的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_GENERIC_FAILURE} 表示输入的JavaScript无法编译成功。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateFunctionWithScript(JSVM_Env env,
                                                         const char* funcName,
                                                         size_t length,
                                                         size_t argc,
                                                         const JSVM_Value* argv,
                                                         JSVM_Value script,
                                                         JSVM_Value* result);

/**
 * @brief 启动虚拟机内任务队列，这个任务队列可以通过外部事件循环执行。
 *
 * @param vm 启动任务队列的虚拟机实例。
 * @param result 表示任务队列是否成功启动。
 * @return 返回JSVM函数结果代码。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_PumpMessageLoop(JSVM_VM vm,
                                                bool* result);

/**
 * @brief 检查队列中是否有微任务等待，如果存在则执行它们。
 *
 * @param vm 要检查微任务的虚拟机实例。
 * @return 返回JSVM函数结果代码。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_PerformMicrotaskCheckpoint(JSVM_VM vm);

/**
 * @brief 此API检查传入的值是否可调用。
 *
 * @param env 调用该API的环境。
 * @param value 要检查的JavaScript值。
 * @param isCallable 给定值是否可调用。true为可调用，false为不可调用。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsCallable(JSVM_Env env, JSVM_Value value, bool* isCallable);

/**
 * @brief 持久保存一个JSVM_Script并将其生命周期延长到当前作用域之外。
 *
 * @param env 调用该API的环境。
 * @param script 包含要持久化保存脚本的JavaScript字符串。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG} 表示脚本为空或已被保存过。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_RetainScript(JSVM_Env env, JSVM_Script script);

/**
 * @brief 释放由 OH_JSVM_RetainScript 保留的脚本，释放后应避免对传入 script 的再次使用。
 *
 * @param env 调用该API的环境。
 * @param script 包含要释放的脚本的JavaScript字符串。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG} 表示脚本为空或未被保存过。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ReleaseScript(JSVM_Env env, JSVM_Script script);

/**
 * @brief 打开一个名为 name 的 inspector，为其打开对应 pid 的 unix domain 端口。
 *
 * @param env 调用该API的环境。
 * @param pid 用于标识 inspector 连接的进程ID。
 * @param name inspector 的名字。 如果传入nullptr, 则默认名称为jsvm。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_PENDING_EXCEPTION} 表示发生了异常。\n
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_OpenInspectorWithName(JSVM_Env env,
                                                      int pid,
                                                      const char* name);

/**
 * @brief 将 WebAssembly 字节码编译得到一个 WebAssembly 模块。
 * 如果提供了 WebAssembly 缓存，则会先尝试对缓存进行反序列化。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param wasmBytecode WebAssembly 字节码。
 * @param wasmBytecodeLength WebAssembly 字节码的长度，单位：字节。
 * @param cacheData 可选的 WebAssembly 缓存。
 * @param cacheDataLength 可选的 WebAssembly 缓存长度，单位：字节。
 * @param cacheRejected 输出参数，表示提供的 WebAssembly 缓存是否被引擎拒绝。
 * @param wasmModule 输出参数，表示生成的 WebAssembly 模块。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示 env 或 wasmBytecode 参数为空，或传入的数据长度参数无效。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示编译失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示发生了异常。\n
 *
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CompileWasmModule(JSVM_Env env,
                                                  const uint8_t *wasmBytecode,
                                                  size_t wasmBytecodeLength,
                                                  const uint8_t *cacheData,
                                                  size_t cacheDataLength,
                                                  bool *cacheRejected,
                                                  JSVM_Value *wasmModule);

/**
 * @brief 对当前 WebAssembly 模块中指定索引的函数进行指定优化等级的编译优化。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param wasmModule 待编译函数所在的 WebAssembly 模块。
 * @param functionIndex 待编译函数的索引，索引必须位于合法范围。
 * @param optLevel 优化等级，当前只支持高优化等级。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示 env 或 wasmModule 参数为空，或 wasmModule 不是一个真正的 WebAssembly 模块。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示函数索引越界，或编译失败。\n
 *         {@link JSVM_PENDING_EXCEPTION } 表示发生了异常。\n
 *
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CompileWasmFunction(JSVM_Env env,
                                                    JSVM_Value wasmModule,
                                                    uint32_t functionIndex,
                                                    JSVM_WasmOptLevel optLevel);

/**
 * @brief 判断给定的 JSVM_Value 是否是一个 WebAssembly 模块。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param value 待检查的 JavaScript 值。
 * @param result 输出参数，表示给定的值是否是一个 WebAssembly 模块。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsWasmModuleObject(JSVM_Env env,
                                                   JSVM_Value value,
                                                   bool* result);

/**
 * @brief 为给定的 WebAssembly 模块生成缓存。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param wasmModule 编译好的 WebAssembly 模块。
 * @param data 输出参数，表示生成的 WebAssembly 缓存。
 * @param length 输出参数，表示生成的 WebAssembly 缓存的长度，单位：字节。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示缓存生成失败。\n
 *
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateWasmCache(JSVM_Env env,
                                                JSVM_Value wasmModule,
                                                const uint8_t** data,
                                                size_t* length);

/**
 * @brief 释放给定类型的缓存数据。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param cacheData 待释放的缓存数据，重复释放是未定义行为。
 * @param cacheType 缓存的类型，缓存的生成和释放必须一一对应。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数，或 cacheType 参数不合法。\n
 *
 * @since 12
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ReleaseCache(JSVM_Env env,
                                             const uint8_t* cacheData,
                                             JSVM_CacheType cacheType);

/**
 * @brief 判断给定的 JSVM_Value 是否是一个 BigInt对象。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param value 待检查的 JavaScript 值。
 * @param result 输出参数，表示给定的值是否是一个BigInt对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsBigIntObject(JSVM_Env env,
                                               JSVM_Value value,
                                               bool* result);

/**
 * @brief 判断给定的 JSVM_Value 是否是一个 Boolean对象。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param value 待检查的 JavaScript 值。
 * @param result 输出参数，表示给定的值是否是一个Boolean对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsBooleanObject(JSVM_Env env,
                                                JSVM_Value value,
                                                bool* result);

/**
 * @brief 判断给定的 JSVM_Value 是否是一个 String对象。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param value 待检查的 JavaScript 值。
 * @param result 输出参数，表示给定的值是否是一个String对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsStringObject(JSVM_Env env,
                                               JSVM_Value value,
                                               bool* result);

/**
 * @brief 判断给定的 JSVM_Value 是否是一个 Number对象。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param value 待检查的 JavaScript 值。
 * @param result 输出参数，表示给定的值是否是一个Number对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsNumberObject(JSVM_Env env,
                                               JSVM_Value value,
                                               bool* result);

/**
 * @brief 判断给定的 JSVM_Value 是否是一个 Symbol对象。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param value 待检查的 JavaScript 值。
 * @param result 输出参数，表示给定的值是否是一个Symbol对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_IsSymbolObject(JSVM_Env env,
                                               JSVM_Value value,
                                               bool* result);

/**
 * @brief 获取Well-Known symbol里的Symbol.AsyncIterator能力。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param result 输出参数，Well-Known symbol里的Symbol.AsyncIterator。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetSymbolAsyncIterator(JSVM_Env env, JSVM_Value* result);

/**
 * @brief 获取Well-Known symbol里的Symbol.HasInstance能力。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param result 输出参数，Well-Known symbol里的Symbol.HasInstance。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetSymbolHasInstance(JSVM_Env env, JSVM_Value* result);

/**
 * @brief 获取Well-Known symbol里的Symbol.IsConcatSpreadable能力。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param result 输出参数，Well-Known symbol里的Symbol.IsConcatSpreadable。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetSymbolIsConcatSpreadable(JSVM_Env env, JSVM_Value* result);

/**
 * @brief 获取Well-Known symbol里的Symbol.Match能力。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param result 输出参数，Well-Known symbol里的Symbol.Match。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetSymbolMatch(JSVM_Env env, JSVM_Value* result);

/**
 * @brief 获取Well-Known symbol里的Symbol.Replace能力。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param result 输出参数，Well-Known symbol里的Symbol.Replace。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetSymbolReplace(JSVM_Env env, JSVM_Value* result);

/**
 * @brief 获取Well-Known symbol里的Symbol.Search能力。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param result 输出参数，Well-Known symbol里的Symbol.Search。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetSymbolSearch(JSVM_Env env, JSVM_Value* result);

/**
 * @brief 获取Well-Known symbol里的Symbol.Split能力。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param result 输出参数，Well-Known symbol里的Symbol.Split。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetSymbolSplit(JSVM_Env env, JSVM_Value* result);

/**
 * @brief 获取Well-Known symbol里的Symbol.ToPrimitive能力。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param result 输出参数，Well-Known symbol里的Symbol.ToPrimitive。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetSymbolToPrimitive(JSVM_Env env, JSVM_Value* result);

/**
 * @brief 获取Well-Known symbol里的Symbol.Unscopables能力。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param result 输出参数，Well-Known symbol里的Symbol.Unscopables。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetSymbolUnscopables(JSVM_Env env, JSVM_Value* result);

/**
 * @brief 获取Well-Known symbol里的Symbol.ToStringTag能力。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param result 输出参数，Well-Known symbol里的Symbol.ToStringTag。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetSymbolToStringTag(JSVM_Env env, JSVM_Value* result);

/**
 * @brief 获取Well-Known symbol里的Symbol.Iterator能力。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param result 输出参数，Well-Known symbol里的Symbol.Iterator。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入了空指针参数。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetSymbolIterator(JSVM_Env env, JSVM_Value* result);

/**
 * @brief 对所有 JSVM 运行时实例，开始采集指定 Trace 类别的信息（线程不安全）。
 *
 * @param count 进行 Trace 采集的分类数量。
 * @param categories 进行 Trace 采集的具体分类数组。
 * @param tag 用户定义并赋予 Trace 数据的标签。
 * @param eventsCount 存储的 Trace 事件数量上限。
 * @return 返回执行状态码 JSVM_Status。 。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } categories 或者 count 输入不合法。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_TraceStart(size_t count,
                                           const JSVM_TraceCategory* categories,
                                           const char* tag,
                                           size_t eventsCount);

/**
 * @brief 对所有 JSVM 运行时，停止采集指定 Trace 类别的信息（线程不安全）。
 *
 * @param stream 输出流回调函数，实现接收 Trace 数据功能。
 * @param streamData 输出流指针，用于辅助输出流回调函数进行数据输出。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } stream 或者 streamData 为空。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_TraceStop(JSVM_OutputStream stream, void* streamData);

/**
 * @brief 在VM中添加GC的回调函数。
 *
 * @param vm 调用JSVM-API的环境。
 * @param triggerTime 触发GC回调函数的时机。
 * @param handler 当触发GC时，传入的回调函数会被调用。
 * @param gcType GC类型。
 * @param userData 原生指针数据。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示函数执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的vm或者handler为空或者handler已经被添加过了。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_AddHandlerForGC(JSVM_VM vm,
                                                JSVM_CBTriggerTimeForGC triggerTime,
                                                JSVM_HandlerForGC handler,
                                                JSVM_GCType gcType,
                                                void* userData);

/**
 * @brief 在VM中移除GC的回调函数。
 *
 * @param vm 调用JSVM-API的环境。
 * @param triggerTime 触发GC回调函数的时机。
 * @param handler 当触发GC时，传入的回调函数会被调用。
 * @param userData 原生指针数据。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示函数执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的vm或者handler为空或者handler已经被删除过了或者
 * 这个handler从来没有被添加过。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_RemoveHandlerForGC(JSVM_VM vm,
                                                   JSVM_CBTriggerTimeForGC triggerTime,
                                                   JSVM_HandlerForGC handler,
                                                   void* userData);

/**
 * @brief 为OOM错误设置回调处理。当接口被重复调用时，仅最后一次生效。当传入的handler为null时，表示取消之前的设置。
 *
 * @param vm 调用JSVM-API的环境。
 * @param handler OOM错误的处理器。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示函数执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示vm为空。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_SetHandlerForOOMError(JSVM_VM vm,
                                                      JSVM_HandlerForOOMError handler);

/**
 * @brief 启用/禁用特定JSVM_Env的指定调试选项。
 *
 * @param env 调用JSVM-API的环境。
 * @param debugOption 需要更改的调试选项。
 * @param isEnabled 是否启用或禁用调试选项。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示函数执行成功。\n
 *         {@link JSVM_INVALID_ARG } 如果传入的env为空指针，返回此错误码。\n
 * @since 20
 */
JSVM_EXTERN JSVM_Status OH_JSVM_SetDebugOption(JSVM_Env env, JSVM_DebugOption debugOption, bool isEnabled);

/**
 * @brief 为Fatal错误设置回调处理。当接口被重复调用时，仅最后一次生效。当传入的handler为null时，表示取消之前的设置。
 *
 * @param vm 调用JSVM-API的环境。
 * @param handler Fatal错误的处理器。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示函数执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示vm为空。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_SetHandlerForFatalError(JSVM_VM vm,
                                                        JSVM_HandlerForFatalError handler);

/**
 * @brief 为PromiseReject错误设置回调处理。当接口被重复调用时，仅最后一次生效。当传入的handler为null时，表示取消之前的设置。
 *
 * @param vm 调用JSVM-API的环境。
 * @param handler PromiseReject错误的处理器。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示函数执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示vm为空。\n
 *
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_SetHandlerForPromiseReject(JSVM_VM vm,
                                                           JSVM_HandlerForPromiseReject handler);


/**
 * @brief 在封装一个 C++ 类时，通过构造函数传递的 C++ 构造函数回调应该是类中的一个静态方法，
 * 该方法调用实际的类构造函数，然后根据传入的不同选项，将新的 C++ 实例封装在一个 JavaScript 对象中并返回封装对象。
 *
 * @param env 调用JSVM-API的环境。
 * @param utf8name JavaScript构造函数的名称，建议在包装C++类时使用C++类名。
 * @param length utf8name的长度（以字节为单位）或JSVM_AUTO_LENGTH（如果以 null 结尾）。
 * @param constructor 用于创建类的构造函数的回调函数。包装C++类时，此方法必须是符合JSVM_Callback
 * 签名的静态成员。不能使用C++类构造函数。详情请参考JSVM_Callback。
 * @param propertyCount properties数组参数中的项目数量。
 * @param properties 类的属性描述符，用于定义类的属性和方法。
 * @param parentClass 当前所定义的class的父类class。
 * @param optionCount options数组参数中的项目数量。
 * @param options 传入的用于定义class的选项数组。
 * @param result 表示类的构造函数的JSVM_Value。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入的指针参数里面存在空指针。\n
 *         {@link JSVM_GENERIC_FAILURE} 表示传入的utf8name | constructor | properties无效，导致执行失败。\n
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_DefineClassWithOptions(JSVM_Env env,
    const char* utf8name,
    size_t length,
    JSVM_Callback constructor,
    size_t propertyCount,
    const JSVM_PropertyDescriptor* properties,
    JSVM_Value parentClass,
    size_t optionCount,
    JSVM_DefineClassOptions options[],
    JSVM_Value* result);

/**
 * @brief 此 API 使用 ISO-8859-1 编码的 C 字符串，创建一个外部的 JavaScript 字符串。
 * 创建外部字符串失败时会复制原生字符串。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param str 指向 ISO-8859-1 编码字符串的指针。
 * @param length 字符串的字节长度，如果是空终止字符串可以直接传入 JSVM_AUTO_LENGTH。
 * @param finalizeCallback 可选项，是当创建的字符串被 GC 回收时会触发的回调函数。
 * 更多细节详见 JSVM_Finalize 类型说明。
 * @param finalizeHint 可选项，当字符串被回收时会传递给触发的 finalize callback。
 * @param result 接收创建完成的 JavaScript 外部字符串，表示为 JSVM_Value 类型。
 * @param copied 指示外部字符串是否成功创建的标志，为真表示创建外部字符串失败并返回一个原生 JS 字符串，否表示成功。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG} 表示传入参数中 env, str 和 copied 中任一值为空。\n
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateExternalStringLatin1(JSVM_Env env,
                                                           char* str,
                                                           size_t length,
                                                           JSVM_Finalize finalizeCallback,
                                                           void* finalizeHint,
                                                           JSVM_Value* result,
                                                           bool* copied);

/**
 * @brief 此 API 使用 UTF16-LE 编码的 C 字符串，创建一个外部的 JavaScript 字符串。
 * 创建外部字符串失败时会复制原生字符串。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param str 指向 UTF16-LE 编码字符串的指针。
 * @param length 字符串的字节长度，如果是空终止字符串可以直接传入 JSVM_AUTO_LENGTH。
 * @param finalizeCallback 可选项，是当创建的字符串被 GC 回收时会触发的回调函数。
 * 更多细节详见 JSVM_Finalize 类型说明。
 * @param finalizeHint 可选项，当字符串被回收时会传递给触发的 finalize callback。
 * @param result 接收创建完成的 JavaScript 外部字符串，表示为 JSVM_Value 类型。
 * @param copied 指示外部字符串是否成功创建的标志，为真表示创建外部字符串失败并返回一个原生 JS 字符串，否表示成功。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG} 表示传入参数中 env, str 和 copied 中任一值为空。\n
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateExternalStringUtf16(JSVM_Env env,
                                                          char16_t* str,
                                                          size_t length,
                                                          JSVM_Finalize finalizecallback,
                                                          void* finalizeHint,
                                                          JSVM_Value* result,
                                                          bool* copied);

/**
 * @brief 创建一个 JavaScript private key 对象。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param description 可选项，它指的是要作为 private key 描述的 JavaScript 字符串。
 * @param result 接收创建成功的 JavaScript private key 对象的指针。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG} 表示传入参数中 env 和 result 中任一值为空。\n
 *         {@link JSVM_STRING_EXPECTED } 表示传入的 description 不是字符串。\n
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreatePrivate(JSVM_Env env,
                                              JSVM_Value description,
                                              JSVM_Data* result);

/**
 * @brief 为传入的object设置一个 private 属性。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param object 将要进行 private 属性设置的对象。
 * @param key private 属性的 private key 对象。
 * @param value private 属性值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG} 表示任一传入参数为空或者 key 不是一个 private key 对象。\n
 *         {@link JSVM_OBJECT_EXPECTED } 表示传入的 object 不是一个真正的 JavaScript object。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示设置 private 属性失败，同时没有异常产生。\n
 *         {@link JSVM_PENDING_EXCPTION } 表示发生了异常。\n
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_SetPrivate(JSVM_Env env,
                                           JSVM_Value object,
                                           JSVM_Data key,
                                           JSVM_Value value);

/**
 * @brief 从传入的object获取 private key 对应的 private 属性。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param object 获取 private 属性的对象。
 * @param key private 属性的 private key 对象。
 * @param result private 属性值。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG} 表示任一传入参数为空或者 key 不是一个 private key 对象。\n
 *         {@link JSVM_OBJECT_EXPECTED } 表示传入的 object 不是一个真正的 JavaScript object。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示获取 private 属性失败，同时没有异常产生。\n
 *         {@link JSVM_PENDING_EXCPTION } 表示发生了异常。\n
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetPrivate(JSVM_Env env,
                                           JSVM_Value object,
                                           JSVM_Data key,
                                           JSVM_Value *result);

/**
 * @brief 从传入的 object 上删除 private key 对应的 private 属性。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param object 删除 private 属性的对象。
 * @param key private 属性的 private key 对象。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG} 表示任一传入参数为空或者 key 不是一个 private key 对象。\n
 *         {@link JSVM_OBJECT_EXPECTED } 表示传入的 object 不是一个真正的 JavaScript object。\n
 *         {@link JSVM_GENERIC_FAILURE } 表示删除 private 属性失败，同时没有异常产生。\n
 *         {@link JSVM_PENDING_EXCPTION } 表示发生了异常。\n
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_DeletePrivate(JSVM_Env env,
                                              JSVM_Value object,
                                              JSVM_Data key);

/**
 * @brief 创建一个对于给定 JSVM_Data 对象的引用，初始的引用计数为传入的 initialRefcount。
 *
 * @param env 调用 JSVM-API 的环境。
 * @param data 将要创建引用的 JSVM_Data 对象。
 * @param initialRefcount 初始引用计数值。
 * @param result 接收新创建的对象引用，表示为 JSVM_Ref 类型。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateDataReference(JSVM_Env env,
                                                    JSVM_Data data,
                                                    uint32_t initialRefcount,
                                                    JSVM_Ref* result);

/**
 * @brief 如果引用仍然有效，通过 result 参数返回对应的 JSVM_Data，
 * 表示与 JSVM_Ref 关联的 JavaScript 值。否则结果将为空。
 *
 * @param env 调用JSVM-API的环境。
 * @param ref 请求相应值的JSVM_Ref。
 * @param result JSVM_Ref 引用的 JSVM_Data。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入参数不合法。\n
 * @since 18
 */
JSVM_EXTERN JSVM_Status OH_JSVM_GetReferenceData(JSVM_Env env,
                                                 JSVM_Ref ref,
                                                 JSVM_Data* result);

/**
 * @brief 在线程池中反序列化JSVM_CodeCache，通过OH_JSVM_ReleaseDeserializeResult接口释放JSVM_DeserializeResult。
 * JSVM_DeserializeResult。
 *
 * @param vm 调用JSVM-API的环境。
 * @param cacheData 需要进行反序列化的字节码缓存数据。
 * @param result 后台反序列化结果。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入参数不合法。\n
 * @since 24
 */
JSVM_EXTERN JSVM_Status OH_JSVM_BackgroundDeserialize(
    JSVM_VM vm, JSVM_CodeCache cacheData, JSVM_DeserializeResult* result);

/**
 * @brief 当 JSVM_DeserializeResult 不再被使用时进行释放。
 *
 * @param result 需要进行释放的后台反序列化结果。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示传入参数不合法。\n
 * @since 24
 */
JSVM_EXTERN JSVM_Status OH_JSVM_ReleaseDeserializeResult(JSVM_DeserializeResult result);

#ifdef JSVM_EXPERIMENTAL
/**
 * @brief 创建一个 JavaScript ArrayBuffer，其内容从用户提供的外部内存初始化。根据引擎实现，
 * 可能直接引用外部内存（零拷贝），也可能将数据拷贝到引擎内部管理的缓冲区。
 *
 * 当使用零拷贝时，ArrayBuffer 直接引用外部内存，调用方在 finalize 回调被调用之前不得释放该内存。
 *
 * 当发生数据拷贝时，数据将被拷贝到引擎管理的内存中，copied 输出参数会被设置为 true，以通知调用方
 * 其内存不再被引用。此时通过 OH_JSVM_GetArraybufferInfo 获取的 ArrayBuffer 数据指针将与
 * externalData 不同。
 *
 * @param env 调用该 JSVM-API 的环境。
 * @param externalData 指向源内存块的指针，须 8 字节对齐。byteLength 为 0 时可为 nullptr。
 * @param byteLength 源内存块的字节长度，不得超过引擎支持的 ArrayBuffer 最大大小。
 * @param finalizeCb 可选的回调函数，当该 API 创建的 ArrayBuffer 对象被垃圾回收时调用。
 *                   回调接收原始 externalData 指针、finalizeHint 以及一个表示数据是否已被拷贝的布尔值 copied。
 *                   当 copied 为 true 时，引擎不再引用 externalData，调用方可在该 API 返回后立即释放。
 *                   当 copied 为 false（零拷贝）时，externalData 仍在被使用，应在该回调中释放。若无需清理，可传 NULL。
 * @param finalizeHint 传递给 finalizeCb 的可选提示，可为 NULL。
 * @param copied 可选输出参数。若非 NULL，当数据被拷贝到内部缓冲区时设置为 true，使用零拷贝时
 *               设置为 false。若调用方不需要此信息，可传 NULL。
 * @param result 表示创建的 JavaScript ArrayBuffer。
 * @return 返回执行状态码 JSVM_Status。
 *         {@link JSVM_OK } 表示执行成功。\n
 *         {@link JSVM_INVALID_ARG } 表示出现了以下场景：result 为空、byteLength > 0 时但 externalData 为空、
 *         externalData 未按 8 字节对齐，byteLength 超过引擎支持的 ArrayBuffer 最大大小。\n
 *
 * @since 26.0.0
 */
JSVM_EXTERN JSVM_Status OH_JSVM_CreateArrayBufferFromExternalMemory(JSVM_Env env,
                                                                    void* externalData,
                                                                    size_t byteLength,
                                                                    JSVM_FinalizeArrayBuffer finalizeCb,
                                                                    void* finalizeHint,
                                                                    bool* copied,
                                                                    JSVM_Value* result);
#endif // JSVM_EXPERIMENTAL

EXTERN_C_END

/** @} */
#endif /* ARK_RUNTIME_ZH_CN_JSVM_JSVM_H */

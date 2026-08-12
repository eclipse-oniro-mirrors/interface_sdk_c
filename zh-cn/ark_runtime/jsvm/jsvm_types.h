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

#ifndef ARK_RUNTIME_ZH_CN_JSVM_JSVM_TYPE_H
#define ARK_RUNTIME_ZH_CN_JSVM_JSVM_TYPE_H

/**
 * @addtogroup JSVM
 * @{
 *
 * @brief 提供标准的JavaScript引擎能力。
 *
 * 通过API接口为开发者提供独立、标准、完整的JavaScript引擎能力，
 * 包括管理引擎生命周期、编译运行JS代码、实现JS/C++跨语言调用、拍摄快照等。
 *
 * @since 11
 */

/**
 * @file jsvm_types.h
 *
 * @brief 提供JSVM-API类型定义。
 *
 * 通过API接口为开发者提供独立、标准、完整的JavaScript引擎能力，
 * 包括管理引擎生命周期、编译运行JS代码、实现JS/C++跨语言调用、拍摄快照等。
 * @library libjsvm.so
 * @kit ArkTS
 * @syscap SystemCapability.ArkCompiler.JSVM
 * @since 11
 */

#include <stddef.h>  // NOLINT(modernize-deprecated-headers)
#include <stdint.h>  // NOLINT(modernize-deprecated-headers)
#include <stdbool.h>  // NOLINT(modernize-deprecated-headers)

#if !defined __cplusplus || (defined(_MSC_VER) && _MSC_VER < 1900)
/**
 * @brief 为uint16_t创建一个别名——char16_t
 *
 * 这段代码的核心目的是确保 char16_t 这个类型在所有目标编译环境中都可用，即使在一些不支持它的旧环境里。
 * char16_t 是 C++11 标准中引入的一个新的基本数据类型，专门用于存储16位字符，通常用来表示UTF-16编码的字符。
 *
 * 如果编译器本身不认识char16_t，手动创建一个底层实现是16位无符号的整数类型。
 * 前置生效条件为：当前编译器——非C++编译器编译 || 是微软Visual C++编译器且版本早于Visual Studio 2015（不含）。
 *
 * @since 11
 */
typedef uint16_t char16_t;
#endif

/**
 * @brief 为不同平台统一函数约定调用（Calling Convention）的宏。
 *
 * 如果在 Windows 上，JSVM_CDECL 宏会被展开为 __cdecl。
 * __cdecl是 C/C++ 语言在 x86 架构上的默认调用约定。它的主要特点是：参数从右到左压入栈、调用者 (caller) 负责清理栈。
 * 虽然 __cdecl 是默认的，但在 Windows API 编程中，还存在其他CC，如 __stdcall（被调用者清理栈，Win32 API常用）和 __fastcall（部分参数用寄存器传递）。
 * 通过显式指定__cdecl，确保即使项目全局编译设置被修改为其他约定，被这个宏修饰的函数依然可以保持 __cdecl 约定，从而避免不匹配问题。
 *
 * 在大多数非 Windows 系统（如遵循 System V ABI 的 Linux/macOS）上，通常只有一种标准的调用约定，无须指定JSVM_CDECL。
 *
 * @since 11
 */
#ifndef JSVM_CDECL
#ifdef _WIN32
#define JSVM_CDECL __cdecl
#else
#define JSVM_CDECL
#endif
#endif

/**
 * @brief 表示JavaScript虚拟机实例。
 *
 * @since 11
 */
typedef struct JSVM_VM__* JSVM_VM;

/**
 * @brief 表示JavaScript虚拟机作用域。
 *
 * @since 11
 */
typedef struct JSVM_VMScope__* JSVM_VMScope;

/**
 * @brief 表示用于控制附加到当前虚拟机实例的环境。只有当线程通过
 * OH_JSVM_OpenEnvScope进入该环境的JSVM_EnvScope后，该环境才
 * 对线程的虚拟机实例可用。
 *
 * @since 11
 */
typedef struct JSVM_EnvScope__* JSVM_EnvScope;

/**
 * @brief 表示一段JavaScript代码。
 *
 * @since 11
 */
typedef struct JSVM_Script__* JSVM_Script;

/**
 * @brief 表示虚拟机特定状态的上下文环境，需要在调用native函数时作为参数传递，
 * 并且传递给后续任何的JSVM-API嵌套调用。
 *
 * @since 11
 */
typedef struct JSVM_Env__* JSVM_Env;

/**
 * @brief 表示一个JavaScript CPU时间性能分析器。
 *
 * @since 12
 */
typedef struct JSVM_CpuProfiler__* JSVM_CpuProfiler;

/**
 * @brief 表示JavaScript值。
 *
 * @since 11
 */
typedef struct JSVM_Value__* JSVM_Value;

/**
 * @brief 表示一个 JavaScript Data。
 *
 * @since 18
 */
typedef struct JSVM_Data__* JSVM_Data;

/**
 * @brief 表示JavaScript值的引用。
 *
 * @since 11
 */
typedef struct JSVM_Ref__* JSVM_Ref;

/**
 * @brief 表示JavaScript值的作用域，用于控制和修改在特定范围内创建的对象的生命周期。
 * 通常，JSVM-API值是在JSVM_HandleScope的上下文中创建的。当从JavaScript调用native方法时，
 * 将存在默认JSVM_HandleScope。如果用户没有显式创建新的JSVM_HandleScope，将在默认
 * JSVM_HandleScope中创建JSVM-API值。对于native方法执行之外的任何代码调用（例如，在libuv回调调用期间），
 * 模块需要在调用任何可能导致创建JavaScript值的函数之前创建一个作用域。JSVM_HandleScope是使用
 * OH_JSVM_OpenHandleScope创建的，并使用OH_JSVM_CloseHandleScope销毁的。
 * 关闭作用域代表向GC指示在JSVM_HandleScope作用域的生命周期内创建的所有JSVM_Value将不再从当前堆的栈帧中引用。
 *
 * @since 11
 */
typedef struct JSVM_HandleScope__* JSVM_HandleScope;

/**
 * @brief 表示一种特殊类型的handle scope，用于将在特定handle scope内创建的值返回到父作用域。
 *
 * @since 11
 */
typedef struct JSVM_EscapableHandleScope__* JSVM_EscapableHandleScope;

/**
 * @brief 表示传递给回调函数的不透明数据类型。可用于获取调用该函数的上下文的附加信息。
 *
 * @since 11
 */
typedef struct JSVM_CallbackInfo__* JSVM_CallbackInfo;

/**
 * @brief 表示Promise延迟对象。
 *
 * @since 11
 */
typedef struct JSVM_Deferred__* JSVM_Deferred;


/**
 * @brief 用户提供的native回调函数的指针和数据，这些函数通过JSVM-API接口暴露给JavaScript。
 *
 * @since 11
 */
typedef struct {
    /** 用户提供的native回调函数的指针。*/
    JSVM_Value(JSVM_CDECL* callback)(JSVM_Env env,
                                   JSVM_CallbackInfo info);
    /** 用户提供的native回调函数的数据。*/
    void* data;
} JSVM_CallbackStruct;

/**
 * @brief 用户提供的native函数的函数指针类型，这些函数通过JSVM-API接口暴露给JavaScript。
 *
 * @since 11
 */
typedef JSVM_CallbackStruct* JSVM_Callback;

/**
 * @brief 函数指针类型，当native类型对象或数据与JS对象被关联时，传入该指针。该函数将会
 * 在关联的JS对象被GC回收时被调用，用以执行native的清理动作。
 *
 * @since 11
 */
typedef void (JSVM_CDECL* JSVM_Finalize)(JSVM_Env env,
                                         void* finalizeData,
                                         void* finalizeHint);

#ifdef JSVM_EXPERIMENTAL
/**
 * @brief 用于从外部内存创建的 ArrayBuffer 的 Finalize 回调函数指针类型。
 *
 * 与 JSVM_Finalize 类似，但包含一个 copied 参数，用于指示引擎是否将外部数据拷贝到内部缓冲区
 * （true）或使用了零拷贝方式（false）。当 copied 为 true 时，引擎不持有对原始外部数据的引用，
 * 调用方可在 API 调用返回后立即释放。当 copied 为 false 时，finalizeData 指向引擎正在释放
 * 的原始外部内存，回调函数应对其进行释放。
 *
 * @since 26.0.0
 */
typedef void(JSVM_CDECL* JSVM_FinalizeArrayBuffer)(JSVM_Env env,
                                                   void* finalizeData,
                                                   void* finalizeHint,
                                                   bool copied);
#endif // JSVM_EXPERIMENTAL

/**
 * @brief 输出流回调的函数指针类型。参数data是指输出的数据指针。参数size是指输出的数据大小。
 * 空数据指针指示流的结尾。参数streamData是指与回调一起传递给API函数的指针，该API函数向输出流生成数据。
 *
 * @return 返回true表示流可以继续接受数据，返回false将中止流。
 *
 * @since 12
 */
typedef bool (JSVM_CDECL* JSVM_OutputStream)(const char* data,
                                             int size,
                                             void* streamData);

/**
 * @brief 用于控制JavaScript对象属性的行为。
 *
 * @since 11
 */
typedef enum {
    /** 没有在属性上设置显式属性。*/
    JSVM_DEFAULT = 0,
    /** 该属性是可写的。*/
    JSVM_WRITABLE = 1 << 0,
    /** 该属性是可枚举的。*/
    JSVM_ENUMERABLE = 1 << 1,
    /** 该属性是可配置的。*/
    JSVM_CONFIGURABLE = 1 << 2,
    /** 用于标记本地方法的接收器无需进行检查。
     * 如果未设置 JSVM_NO_RECEIVER_CHECK，则该方法仅接受定义类的实例作为接收器，
     * 否则会向 JSVM 抛出异常“类型错误：非法调用”。
    */
    JSVM_NO_RECEIVER_CHECK = 1 << 3,
    /** 该属性将被定义为类的静态属性，而不是默认的实例属性。这仅由OH_JSVM_DefineClass使用。*/
    JSVM_STATIC = 1 << 10,
    /** 就像JS类中的方法一样，该属性是可配置和可写的，但不可枚举。*/
    JSVM_DEFAULT_METHOD = JSVM_WRITABLE | JSVM_CONFIGURABLE,
    /** 无需检查接收者的类方法。*/
    JSVM_METHOD_NO_RECEIVER_CHECK = JSVM_DEFAULT_METHOD | JSVM_NO_RECEIVER_CHECK,
    /** 就像JavaScript中通过赋值设置的属性一样，属性是可写、可枚举和可配置的。*/
    JSVM_DEFAULT_JSPROPERTY = JSVM_WRITABLE | JSVM_ENUMERABLE | JSVM_CONFIGURABLE,
    /** 无需检查接收者的对象属性。*/
    JSVM_JSPROPERTY_NO_RECEIVER_CHECK = JSVM_DEFAULT_JSPROPERTY | JSVM_NO_RECEIVER_CHECK,
} JSVM_PropertyAttributes;

/**
 * @brief 描述JSVM_Value的类型。
 *
 * @since 11
 */
typedef enum {
    /** 未定义类型。*/
    JSVM_UNDEFINED,
    /** Null类型。*/
    JSVM_NULL,
    /** 布尔类型。*/
    JSVM_BOOLEAN,
    /** 数字类型。*/
    JSVM_NUMBER,
    /** 字符串类型。*/
    JSVM_STRING,
    /** 符号类型。*/
    JSVM_SYMBOL,
    /** 对象类型。*/
    JSVM_OBJECT,
    /** 函数类型。*/
    JSVM_FUNCTION,
    /** 外部类型。*/
    JSVM_EXTERNAL,
    /** bigint类型。*/
    JSVM_BIGINT,
} JSVM_ValueType;

/**
 * @brief 描述Typedarray的类型。
 *
 * @since 11
 */
typedef enum {
    /** int8类型。*/
    JSVM_INT8_ARRAY,
    /** uint8类型。*/
    JSVM_UINT8_ARRAY,
    /** uint8固定类型。*/
    JSVM_UINT8_CLAMPED_ARRAY,
    /** int16类型。*/
    JSVM_INT16_ARRAY,
    /** uint16类型。*/
    JSVM_UINT16_ARRAY,
    /** int32类型。*/
    JSVM_INT32_ARRAY,
    /** uint32类型。*/
    JSVM_UINT32_ARRAY,
    /** float32类型。*/
    JSVM_FLOAT32_ARRAY,
    /** float64类型。*/
    JSVM_FLOAT64_ARRAY,
    /** bigint64类型。*/
    JSVM_BIGINT64_ARRAY,
    /** biguint64类型。*/
    JSVM_BIGUINT64_ARRAY,
} JSVM_TypedarrayType;

/**
 * @brief 表示JSVM-API调用成功或失败的完整状态码。
 *
 * @since 11
 */
typedef enum {
    /** 成功状态。*/
    JSVM_OK,
    /** 无效参数状态。*/
    JSVM_INVALID_ARG,
    /** 期待传入对象类型。*/
    JSVM_OBJECT_EXPECTED,
    /** 期望传入字符串类型。*/
    JSVM_STRING_EXPECTED,
    /** 期望传入名字类型。*/
    JSVM_NAME_EXPECTED,
    /** 期待传入函数类型。*/
    JSVM_FUNCTION_EXPECTED,
    /** 期待传入数字类型。*/
    JSVM_NUMBER_EXPECTED,
    /** 期待传入布尔类型。*/
    JSVM_BOOLEAN_EXPECTED,
    /** 期待传入数组类型。*/
    JSVM_ARRAY_EXPECTED,
    /** 通用失败状态。*/
    JSVM_GENERIC_FAILURE,
    /** 挂起异常状态。*/
    JSVM_PENDING_EXCEPTION,
    /** 取消状态。*/
    JSVM_CANCELLED,
    /** 转义调用了两次。*/
    JSVM_ESCAPE_CALLED_TWICE,
    /** 句柄作用域不匹配。*/
    JSVM_HANDLE_SCOPE_MISMATCH,
    /** 回调作用域不匹配。*/
    JSVM_CALLBACK_SCOPE_MISMATCH,
    /** 队列满。*/
    JSVM_QUEUE_FULL,
    /** 关闭中。*/
    JSVM_CLOSING,
    /** 期望传入Bigint类型。*/
    JSVM_BIGINT_EXPECTED,
    /** 期望传入日期类型。*/
    JSVM_DATE_EXPECTED,
    /** 期望传入ArrayBuffer类型。*/
    JSVM_ARRAYBUFFER_EXPECTED,
    /** 可分离的数组缓冲区预期状态。*/
    JSVM_DETACHABLE_ARRAYBUFFER_EXPECTED,
    /** 将死锁状态。*/
    JSVM_WOULD_DEADLOCK,
    /** 不允许外部缓冲区。*/
    JSVM_NO_EXTERNAL_BUFFERS_ALLOWED,
    /** 不能执行JS。*/
    JSVM_CANNOT_RUN_JS,
    /**
     * @brief 传入的参数为非法类型。
     *
     * @since 18
     */
    JSVM_INVALID_TYPE,
    /** 无 JIT 权限。
    * @since 18
    */
    JSVM_JIT_MODE_EXPECTED,
} JSVM_Status;

/**
 * @brief 限制查找属性的范围。
 *
 * @since 11
 */
typedef enum {
    /** 也包含对象原型链上的属性。*/
    JSVM_KEY_INCLUDE_PROTOTYPES,
    /** 仅包含对象自身属性。*/
    JSVM_KEY_OWN_ONLY,
} JSVM_KeyCollectionMode;

/**
 * @brief 属性过滤器，可以通过使用or来构造一个复合过滤器。
 *
 * @since 11
 */
typedef enum {
    /** 所有属性的键。*/
    JSVM_KEY_ALL_PROPERTIES = 0,
    /** 可写的键。*/
    JSVM_KEY_WRITABLE = 1,
    /** 可枚举的键。*/
    JSVM_KEY_ENUMERABLE = 1 << 1,
    /** 可配置的键。*/
    JSVM_KEY_CONFIGURABLE = 1 << 2,
    /** 排除字符串类型的键。*/
    JSVM_KEY_SKIP_STRINGS = 1 << 3,
    /** 排除符号类型的键。*/
    JSVM_KEY_SKIP_SYMBOLS = 1 << 4,
} JSVM_KeyFilter;

/**
 * @brief 键转换选项。
 *
 * @since 11
 */
typedef enum {
    /** 将返回整数索引的数字。*/
    JSVM_KEY_KEEP_NUMBERS,
    /** 将整数索引转换为字符串。*/
    JSVM_KEY_NUMBERS_TO_STRINGS,
} JSVM_KeyConversion;

/**
 * @brief 内存压力水平。
 *
 * @since 11
 */
typedef enum {
    /** 无压力。*/
    JSVM_MEMORY_PRESSURE_LEVEL_NONE,
    /** 中等压力。*/
    JSVM_MEMORY_PRESSURE_LEVEL_MODERATE,
    /** 临界压力。*/
    JSVM_MEMORY_PRESSURE_LEVEL_CRITICAL,
    /**
     * 通知系统内存不足，立即触发垃圾回收。
     *
     * @since 22
     */
    JSVM_MEMORY_PRESSURE_LEVEL_LOW_MEMORY,
} JSVM_MemoryPressureLevel;

/**
 *
 * @brief 编译模式。
 *
 * @since 12
 */
typedef enum {
    /** 默认编译模式。 */
    JSVM_COMPILE_MODE_DEFAULT,
    /** 使用代码缓存的模式。 */
    JSVM_COMPILE_MODE_CONSUME_CODE_CACHE,
    /** 激进编译模式。 */
    JSVM_COMPILE_MODE_EAGER_COMPILE,
    /**生成编译依赖的模式。*/
    JSVM_COMPILE_MODE_PRODUCE_COMPILE_PROFILE,
    /** 使用编译依赖的模式。 */
    JSVM_COMPILE_MODE_CONSUME_COMPILE_PROFILE,
} JSVM_CompileMode;

/**
 * @brief JSVM编译选项ID。
 *
 * @since 12
 */
typedef enum {
    /** JSVM编译模式。 */
    JSVM_COMPILE_MODE,
    /** JSVM代码缓存。 */
    JSVM_COMPILE_CODE_CACHE,
    /** JSVM脚本来源。 */
    JSVM_COMPILE_SCRIPT_ORIGIN,
    /** JSVM编译依赖。 */
    JSVM_COMPILE_COMPILE_PROFILE,
    /** JSVM的 Source Map 的使能情况。 */
    JSVM_COMPILE_ENABLE_SOURCE_MAP,
    /** JSVM脚本的后台反序列化结果。
     * @since 24
     */
    JSVM_COMPILE_BACKGROUND_DESERIALIZE_RESULT,
    /** JSVM字节码缓存是否被拒绝。
     * @since 24
     */
    JSVM_COMPILE_CODE_CACHE_REJECTED,
} JSVM_CompileOptionId;

/**
 * @brief 用于保存有关JavaScript堆内存使用情况的统计信息。
 *
 * @since 12
 */
typedef struct {
    /** 总堆大小，单位kb。 */
    size_t totalHeapSize;
    /** 可执行堆的总大小，单位kb。 */
    size_t totalHeapSizeExecutable;
    /** 总的物理内存大小，单位kb。 */
    size_t totalPhysicalSize;
    /** 总的可用内存大小，单位kb。 */
    size_t totalAvailableSize;
    /** 已使用的堆大小，单位kb。 */
    size_t usedHeapSize;
    /** 堆大小限制，单位kb。 */
    size_t heapSizeLimit;
    /** 已分配内存的大小，单位kb。 */
    size_t mallocedMemory;
    /** 外部内存大小，单位kb。 */
    size_t externalMemory;
    /** 最大可分配内存的大小，单位kb。 */
    size_t peakMallocedMemory;
    /** 表示当前活跃的native上下文的数量，该数值一直增加可能指示存在内存泄漏。 */
    size_t numberOfNativeContexts;
    /** 表示已经脱离的上下文数量。 */
    size_t numberOfDetachedContexts;
    /** 全局Handle的总大小，单位kb。 */
    size_t totalGlobalHandlesSize;
    /** 已经使用的全局Handle的大小，单位kb。 */
    size_t usedGlobalHandlesSize;
} JSVM_HeapStatistics;

/**
 * @brief 初始化选项，用于初始化JavaScript虚拟机。
 *
 * @since 11
 */
typedef struct {
    /**
     * 可选。嵌入器中可选的、以nullptr结尾的原始地址数组，
     * 虚拟机可以在序列化期间与之匹配，并可用于反序列化。
     * 此数组及其内容必须在虚拟机实例的整个生命周期内保持有效。
     */
    const intptr_t* externalReferences;

    /**
     * 虚拟机的标志。如果removeFlags为true，则已识别的标志将从
     *（argc, argv）中移除。请注意，这些标志当前仅限于V8虚拟机。
     * 它们主要用于开发。不要将它们用于生产环境，因为如果虚拟机与
     * 开发环境不同，它们可能不会生效。
     */
    int* argc;
    /** argv。 */
    char** argv;
    /** 是否删除，为true，则已识别的标志将从（argc, argv）中移除，为false，则已识别的标志不会从（argc, argv）中移除。*/
    bool removeFlags;
} JSVM_InitOptions;

/**
 * @brief 创建JavaScript虚拟机的选项。
 *
 * @since 11
 */
typedef struct {
    /** 老年代内存大小上限。*/
    size_t maxOldGenerationSize;
    /** 年轻代内存大小上限。*/
    size_t maxYoungGenerationSize;
    /** 老年代内存大小初始值。*/
    size_t initialOldGenerationSize;
    /** 年轻代内存大小初始值。*/
    size_t initialYoungGenerationSize;
    /** 启动快照数据。*/
    const char* snapshotBlobData;
    /** 启动快照数据的大小。*/
    size_t snapshotBlobSize;
    /** 虚拟机是否用于创建快照，为true，则虚拟机用于创建快照，为false，则虚拟机不用于创建快照。*/
    bool isForSnapshotting;
} JSVM_CreateVMOptions;

/**
 * @brief JavaScript虚拟机信息。
 *
 * @since 11
 */
typedef struct {
    /** 此虚拟机支持的最高API版本。*/
    uint32_t apiVersion;
    /** 实现虚拟机的引擎名称。*/
    const char* engine;
    /** 虚拟机的版本。*/
    const char* version;
    /** 缓存数据版本标签。*/
    uint32_t cachedDataVersionTag;
} JSVM_VMInfo;

/**
 * @brief 属性描述符。
 *
 * @since 11
 */
typedef struct {
    /** 描述属性键值的可选字符串，UTF8编码。
     *  必须为属性提供utf8name或name之一。
     */
    const char* utf8name;
    /** 可选的JSVM_Value，指向用作属性键的JavaScript字符串或符号。
     *  必须为属性提供utf8name或name之一。
     */
    JSVM_Value name;
    /** 设置此项使属性描述符对象的value属性成为method表示的JavaScript函数。*/
    JSVM_Callback method;
    /** 执行对属性的获取访问时调用的函数。*/
    JSVM_Callback getter;
    /** 执行属性的设置访问时调用的函数。*/
    JSVM_Callback setter;
    /** 如果属性是数据属性，则通过属性的get访问检索到的值。*/
    JSVM_Value value;
    /** 与特定属性关联的属性。*/
    JSVM_PropertyAttributes attributes;
} JSVM_PropertyDescriptor;

/**
 * @brief 扩展的异常信息。
 * @since 11
 */
typedef struct {
    /** UTF8编码的字符串，包含异常信息描述。*/
    const char* errorMessage;
    /** 特定于VM的详细异常信息。目前尚未为任何VM实现此功能。*/
    void* engineReserved;
    /** 特定于VM的异常代码。目前尚未为任何VM实现此功能。*/
    uint32_t engineErrorCode;
    /** 源自最后一个异常的JSVM-API状态代码。*/
    JSVM_Status errorCode;
} JSVM_ExtendedErrorInfo;

/**
 * @brief 类型标记，存储为两个无符号64位整数的128位值。
 * 作为一个UUID，通过它，JavaScript对象可以是"tagged"，
 * 以确保它们的类型保持不变。
 *
 * @since 11
 */
typedef struct {
    uint64_t lower;
    uint64_t upper;
} JSVM_TypeTag;

/**
 * @brief 当执行对象的getter、setter、deleter和enumerator操作时，该结构体中对应的函数回调将会触发。
 *
 * @since 12
 */
typedef struct {
    /** 通过获取实例对象的命名属性而触发的回调函数。*/
    JSVM_Value (JSVM_CDECL* genericNamedPropertyGetterCallback)(JSVM_Env env,
                                                               JSVM_Value name,
                                                               JSVM_Value thisArg,
                                                               JSVM_Value namedPropertyData);

    /** 通过设置实例对象的命名属性而触发的回调函数。*/
    JSVM_Value (JSVM_CDECL* genericNamedPropertySetterCallback)(JSVM_Env env,
                                                               JSVM_Value name,
                                                               JSVM_Value property,
                                                               JSVM_Value thisArg,
                                                               JSVM_Value namedPropertyData);

    /** 通过删除实例对象的命名属性而触发的回调函数。*/
    JSVM_Value (JSVM_CDECL* genericNamedPropertyDeleterCallback)(JSVM_Env env,
                                                                JSVM_Value name,
                                                                JSVM_Value thisArg,
                                                                JSVM_Value namedPropertyData);

    /** 通过获取对象上的所有命名属性而触发的回调函数。*/
    JSVM_Value (JSVM_CDECL* genericNamedPropertyEnumeratorCallback)(JSVM_Env env,
                                                                   JSVM_Value thisArg,
                                                                   JSVM_Value namedPropertyData);

    /** 通过获取实例对象的索引属性而触发的回调函数。*/
    JSVM_Value (JSVM_CDECL* genericIndexedPropertyGetterCallback)(JSVM_Env env,
                                                                JSVM_Value index,
                                                                JSVM_Value thisArg,
                                                                JSVM_Value indexedPropertyData);

    /** 通过设置实例对象的索引属性而触发的回调函数。*/
    JSVM_Value (JSVM_CDECL* genericIndexedPropertySetterCallback)(JSVM_Env env,
                                                                 JSVM_Value index,
                                                                 JSVM_Value property,
                                                                 JSVM_Value thisArg,
                                                                 JSVM_Value indexedPropertyData);

    /** 通过删除实例对象的索引属性而触发的回调函数。*/
    JSVM_Value (JSVM_CDECL* genericIndexedPropertyDeleterCallback)(JSVM_Env env,
                                                                  JSVM_Value index,
                                                                  JSVM_Value thisArg,
                                                                  JSVM_Value indexedPropertyData);

    /** 通过获取对象上的所有索引属性而触发的回调函数。*/
    JSVM_Value (JSVM_CDECL* genericIndexedPropertyEnumeratorCallback)(JSVM_Env env,
                                                                     JSVM_Value thisArg,
                                                                     JSVM_Value indexedPropertyData);
    /** 命名属性回调使用的数据。*/
    JSVM_Value namedPropertyData;

    /** 索引属性回调使用的数据。*/
    JSVM_Value indexedPropertyData;
} JSVM_PropertyHandlerConfigurationStruct;

/**
 * @brief 包含属性监听回调的结构的指针类型。
 *
 * @since 12
 */
typedef JSVM_PropertyHandlerConfigurationStruct* JSVM_PropertyHandlerCfg;

/**
 * @brief 某段JavaScript代码的原始信息，如sourceMap路径、源文件名、源文件中的起始行/列号等。
 *
 * @since 12
 */
typedef struct {
    /** Sourcemap 路径。 */
    const char* sourceMapUrl;
    /** 源文件名。 */
    const char* resourceName;
    /** 这段代码在源文件中的起始行号。 */
    size_t resourceLineOffset;
    /** 这段代码在源文件中的起始列号。 */
    size_t resourceColumnOffset;
} JSVM_ScriptOrigin;

/**
 * @brief 对应JSVM的编译选项，包含内容和ID。
 *
 * @since 12
 */
typedef struct {
    /** JSVM编译选项ID。*/
    JSVM_CompileOptionId id;
    /** id对应的编译选项值联合体。*/
    union {
        /** 指向编译选项值的指针。*/
        void *ptr;
        /** 存储整数类型的编译选项值。*/
        int num;
        /** 存储布尔类型的编译选项值。*/
        bool boolean;
    } content;
} JSVM_CompileOptions;
/**
 * @brief 对应JSVM代码缓存的地址与大小。
 *
 * @since 12
 */
typedef struct {
    /** 缓存地址。 */
    uint8_t *cache;
    /** 缓存大小。 */
    size_t length;
} JSVM_CodeCache;
/**
 * @brief 与JSVM_COMPILE_COMPILE_PROFILE一起传递的编译采样文件
 *
 * @since 12
 */
typedef const struct {
    /** 编译采样文件的指针。 */
    int *profile;
    /** 编译采样文件的大小。 */
    size_t length;
} JSVM_CompileProfile;

/**
 * @brief 正则表达式标志位。它们可以用来启用一组标志。
 *
 * @since 12
 */
typedef enum {
    /** None模式。 */
    JSVM_REGEXP_NONE = 0,
    /** Global模式。 */
    JSVM_REGEXP_GLOBAL = 1 << 0,
    /** Ignore Case模式。 */
    JSVM_REGEXP_IGNORE_CASE = 1 << 1,
    /** Multiline模式。 */
    JSVM_REGEXP_MULTILINE = 1 << 2,
    /** Sticky模式。 */
    JSVM_REGEXP_STICKY = 1 << 3,
    /** Unicode模式。 */
    JSVM_REGEXP_UNICODE = 1 << 4,
    /** dotAll模式。 */
    JSVM_REGEXP_DOT_ALL = 1 << 5,
    /** Linear模式。 */
    JSVM_REGEXP_LINEAR = 1 << 6,
    /** Has Indices模式。 */
    JSVM_REGEXP_HAS_INDICES = 1 << 7,
    /** Unicode Sets模式。 */
    JSVM_REGEXP_UNICODE_SETS = 1 << 8,
} JSVM_RegExpFlags;

/**
 * @brief 初始化方式的标志位。
 *
 * @since 12
 */
typedef enum {
    /** 初始化为0。 **/
    JSVM_ZERO_INITIALIZED,
    /** 不做初始化。 **/
    JSVM_UNINITIALIZED,
} JSVM_InitializedFlag;

/**
 * @brief WebAssembly 函数优化等级。
 *
 * @since 12
 */
typedef enum {
    /** baseline 优化等级。 */
    JSVM_WASM_OPT_BASELINE = 10,
    /** 高优化等级。 */
    JSVM_WASM_OPT_HIGH = 20,
} JSVM_WasmOptLevel;

/**
 * @brief 缓存类型。
 *
 * @since 12
 */
typedef enum {
    /** JS 缓存, 由接口 OH_JSVM_CreateCodeCache 生成。 */
    JSVM_CACHE_TYPE_JS,
    /** WebAssembly 缓存, 由接口 OH_JSVM_CreateWasmCache 生成。 */
    JSVM_CACHE_TYPE_WASM,
} JSVM_CacheType;

/**
 * @brief JSVM 微任务执行策略。
 *
 * @since 18
 */
typedef enum {
    /** 调用 OH_JSVM_PerformMicrotaskCheckpoint 方法后微任务执行。 */
    JSVM_MICROTASK_EXPLICIT = 0,
    /** JS 调用栈为 0 时自动执行微任务。
     *  默认模式。
     */
    JSVM_MICROTASK_AUTO,
} JSVM_MicrotaskPolicy;

/**
 * @brief JSVM 内部 Trace 事件的类别。
 *
 * @since 18
 */
typedef enum {
    /** 采集 JSVM 主要接口调用, 例如执行 js 脚本。*/
    JSVM_TRACE_VM,
    /** 采集编译相关的接口调用, 例如后台编译。*/
    JSVM_TRACE_COMPILE,
    /** 采集与运行状态相关的接口调用, 例如中断与微任务。*/
    JSVM_TRACE_EXECUTE,
    /** 采集外部函数调用相关信息。*/
    JSVM_TRACE_RUNTIME,
    /** 采集 JSVM 中回栈相关信息。*/
    JSVM_TRACE_STACK_TRACE,
    /** 采集主要的 WASM 相关接口调用, 例如编译与实例化 WASM 模块。*/
    JSVM_TRACE_WASM,
    /** 采集更多更细节的 WASM 相关接口调用，例如后台编译、跳板编译。*/
    JSVM_TRACE_WASM_DETAILED,
} JSVM_TraceCategory;

/**
 * @brief 触发回调函数的时机。
 *
 * @since 18
 */
typedef enum {
    /** 在GC之前触发回调函数。*/
    JSVM_CB_TRIGGER_BEFORE_GC,
    /** 在GC之后触发回调函数。*/
    JSVM_CB_TRIGGER_AFTER_GC,
} JSVM_CBTriggerTimeForGC;

/**
 * @brief GC类型。
 *
 * @since 18
 */
typedef enum {
    /** GC算法为Scavenge。*/
    JSVM_GC_TYPE_SCAVENGE = 1 << 0,
    /** GC算法为Minor-Mark-Compact。*/
    JSVM_GC_TYPE_MINOR_MARK_COMPACT = 1 << 1,
    /** GC算法为Mark-Sweep-Compact。*/
    JSVM_GC_TYPE_MARK_SWEEP_COMPACT = 1 << 2,
    /** GC算法为Incremental-Marking。*/
    JSVM_GC_TYPE_INCREMENTAL_MARKING = 1 << 3,
    /** GC算法为Weak-Callbacks。*/
    JSVM_GC_TYPE_PROCESS_WEAK_CALLBACKS = 1 << 4,
    /** 包含所有类型的GC算法。*/
    JSVM_GC_TYPE_ALL = JSVM_GC_TYPE_SCAVENGE | JSVM_GC_TYPE_MINOR_MARK_COMPACT |
        JSVM_GC_TYPE_MARK_SWEEP_COMPACT | JSVM_GC_TYPE_INCREMENTAL_MARKING |
        JSVM_GC_TYPE_PROCESS_WEAK_CALLBACKS,
} JSVM_GCType;

/**
 * @brief GC回调函数标记。
 *
 * @since 18
 */
typedef enum {
    /** 无回调函数标记。*/
    JSVM_NO_GC_CALLBACK_FLAGS,
    /** 垃圾回收回调中将构建保留对象信息。*/
    JSVM_GC_CALLBACK_CONSTRUCT_RETAINED_OBJECT_INFOS,
    /** 强制执行垃圾回收回调。*/
    JSVM_GC_CALLBACK_FORCED,
    /** 同步处理幽灵对象回调。*/
    JSVM_GC_CALLBACK_SYNCHRONOUS_PHANTOM_CALLBACK_PROCESSING,
    /** 垃圾回收过程中会收集所有可用的垃圾对象。*/
    JSVM_GC_CALLBACK_COLLECT_ALL_AVAILABLE_GARBAGE,
    /** 垃圾回收时会收集所有的外部内存。*/
    JSVM_GC_CALLBACK_COLLECT_ALL_EXTERNAL_MEMORY,
    /** 在空闲时调度垃圾回收。*/
    JSVM_GC_CALLBACK_SCHEDULE_IDLE_GARBAGE_COLLECTION,
} JSVM_GCCallbackFlags;

/**
 * @brief GC回调的函数指针类型。
 *
 * @since 18
 */
typedef void (JSVM_CDECL* JSVM_HandlerForGC)(JSVM_VM vm, JSVM_GCType gcType, JSVM_GCCallbackFlags flags, void* data);

/**
 * @brief promise-reject事件。
 *
 * @since 18
 */
typedef enum {
    /** Promise被拒绝，但拒绝的原因未知或不明确。*/
    JSVM_PROMISE_REJECT_OTHER_REASONS = 0,
    /** Promise被拒绝但没有处理程序。*/
    JSVM_PROMISE_REJECT_WITH_NO_HANDLER = 1,
    /** Promise已被拒绝后，再添加处理程序。*/
    JSVM_PROMISE_ADD_HANDLER_AFTER_REJECTED = 2,
    /** Promise已被解决后，再尝试拒绝该Promise。*/
    JSVM_PROMISE_REJECT_AFTER_RESOLVED = 3,
    /** Promise已被解决后，再尝试解决该Promise。*/
    JSVM_PROMISE_RESOLVE_AFTER_RESOLVED = 4,
} JSVM_PromiseRejectEvent;

/**
 * @brief message的报错级别。
 *
 * @since 18
 */
typedef enum MessageErrorLevel {
    /** Log级别的信息。*/
    JSVM_MESSAGE_LOG = (1 << 0),
    /** Debug级别的信息。*/
    JSVM_MESSAGE_DEBUG = (1 << 1),
    /** Info级别的信息。*/
    JSVM_MESSAGE_INFO = (1 << 2),
    /** Error级别的信息。*/
    JSVM_MESSAGE_ERROR = (1 << 3),
    /** Warning级别的信息。*/
    JSVM_MESSAGE_WARNING = (1 << 4),
    /** 所有级别的信息。*/
    JSVM_MESSAGE_ALL = JSVM_MESSAGE_LOG | JSVM_MESSAGE_DEBUG | JSVM_MESSAGE_INFO | JSVM_MESSAGE_ERROR |
                       JSVM_MESSAGE_WARNING,
} JSVM_MessageErrorLevel;

/**
 * @brief OOM-Error回调的函数指针类型。
 *
 * @since 18
 */
typedef void (JSVM_CDECL* JSVM_HandlerForOOMError)(const char* location,
                                                   const char* detail,
                                                   bool isHeapOOM);

/**
 * @brief Fatal-Error回调的函数指针类型。
 *
 * @since 18
 */
typedef void (JSVM_CDECL* JSVM_HandlerForFatalError)(const char* location,
                                                     const char* message);

/**
 * @brief Promise-Reject回调的函数指针类型。
 *
 * @since 18
 */
typedef void (JSVM_CDECL* JSVM_HandlerForPromiseReject)(
    JSVM_Env env, JSVM_PromiseRejectEvent rejectEvent, JSVM_Value rejectInfo);

/**
 * @brief 包含将class作为函数进行调用时所触发的回调函数的函数指针和
 * 访问实例对象属性时触发的回调函数的函数指针集。
 *
 * @since 18
 */
typedef struct {
    /** 访问实例对象属性触发相应的回调函数。 */
    JSVM_PropertyHandlerCfg propertyHandlerCfg;
    /** 将实例对象作为函数调用将触发此回调。*/
    JSVM_Callback callAsFunctionCallback;
} JSVM_PropertyHandler;

/**
 * @brief 定义Class的选项ID。
 *
 * @since 18
 */
typedef enum {
    /** 在常规模式下定义Class。 */
    JSVM_DEFINE_CLASS_NORMAL,
    /** 为所创建的Class预留指定数量的interfield槽位，在这些槽位中可以存放native-data。*/
    JSVM_DEFINE_CLASS_WITH_COUNT,
    /** 为所创建的Class设置监听拦截属性以及设置作为函数调用时回调函数。*/
    JSVM_DEFINE_CLASS_WITH_PROPERTY_HANDLER,
} JSVM_DefineClassOptionsId;

/**
 * @brief 定义Class的选项。
 *
 * @since 18
 */
typedef struct {
    /** 定义Class的选项ID。 */
    JSVM_DefineClassOptionsId id;
    /** 选项内容。 */
    union {
        /** void*类型。*/
        void* ptr;
        /** int类型。*/
        int num;
        /** bool类型。*/
        bool boolean;
    } content;
} JSVM_DefineClassOptions;

/**
 * @brief 调试选项。
 *
 * @since 20
 */
typedef enum {
    /** scope校验功能。 */
    JSVM_SCOPE_CHECK,
} JSVM_DebugOption;

/**
 * @brief 与JSVM_COMPILE_BACKGROUND_DESERIALIZE_RESULT一起传递的后台反序列化结果。
 *
 * @since 24
 */
typedef struct JSVM_DeserializeResult__* JSVM_DeserializeResult;

/**
 * @brief 堆阈值回调的函数指针类型。
 *
 * @param vm 堆使用量达到阈值的VM实例。
 * @param threshold 堆使用量阈值（以字节为单位）。
 * @param data 原生指针数据。
 * @since 26.0.0
 */
typedef void (JSVM_CDECL* JSVM_HandlerForHeapThreshold)(JSVM_VM vm, uint64_t threshold, void* data);

/** @} */
#endif /* ARK_RUNTIME_ZH_CN_JSVM_JSVM_TYPE_H */

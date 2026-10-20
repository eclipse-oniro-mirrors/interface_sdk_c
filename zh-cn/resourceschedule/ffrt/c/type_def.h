/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
 * @addtogroup FFRT
 * @{
 *
 * @brief 提供Function Flow Runtime（FFRT）C接口。
 *
 * FFRT是一种基于任务的并发运行时库，根据任务依赖关系自动调度任务，
 * 开发者无需手动管理线程。
 *
 * @since 10
 */

/**
 * @file type_def.h
 *
 * @brief 定义通用类型。
 *
 * @library libffrt.z.so
 * @kit FunctionFlowRuntimeKit
 * @syscap SystemCapability.Resourceschedule.Ffrt.Core
 * @since 10
 */

#ifndef FFRT_API_C_TYPE_DEF_H
#define FFRT_API_C_TYPE_DEF_H

#include <stdint.h>
#include <errno.h>

#ifdef __cplusplus
#define FFRT_C_API  extern "C"
#else
#define FFRT_C_API
#endif

/**
 * @brief 并发队列中用于排序任务调度的任务优先级类型枚举。
 *
 * @since 12
 */
typedef enum {
    /** 最高优先级。任务尽快被调度（句柄时间等于提交时间）；优先于`high`被调度。 */
    ffrt_queue_priority_immediate = 0,
    /** 高优先级。按句柄时间排序；优先于`low`被调度。 */
    ffrt_queue_priority_high,
    /** 低优先级。按句柄时间排序；优先于`idle`被调度。 */
    ffrt_queue_priority_low,
    /** 最低优先级。按句柄时间排序；仅在队列中不存在其他优先级任务时才被调度。 */
    ffrt_queue_priority_idle,
} ffrt_queue_priority_t;

/**
 * @brief 任务QoS类型枚举。
 *
 * @since 10
 */
typedef enum {
    /**
     * @brief 继承。
     *
     * 继承调用线程的QoS。用于任务需要采用创建者优先级的场景。
     */
    ffrt_qos_inherit = -1,
    /**
     * @brief 后台任务。
     *
     * 最低优先级。用于用户无感知的工作，例如后台数据同步或日志刷新。
     */
    ffrt_qos_background,
    /**
     * @brief 实用工具类任务。
     *
     * 用于用户可感知但不主动等待的长时间任务，例如数据加载或内容索引。
     */
    ffrt_qos_utility,
    /**
     * @brief 默认类型。
     *
     * 无特殊QoS要求时使用的默认QoS，适用于大多数一般任务。
     */
    ffrt_qos_default,
    /**
     * @brief 用户发起的任务。
     *
     * 用于用户主动触发、需要快速响应但不阻塞UI的任务，例如打开文档或执行搜索。
     */
    ffrt_qos_user_initiated,
    /**
     * @brief 时限请求任务。
     *
     * 用于有明确截止时间的任务，系统优先保障其调度资源。
     *
     * @since 23
     */
    ffrt_qos_deadline_request,
    /**
     * @brief 用户交互任务。
     *
     * 适用于UI响应等需要立即与用户交互的操作。
     *
     * @since 23
     */
    ffrt_qos_user_interactive,
    /**
     * @brief 最高QoS等级。
     *
     * 等价于ffrt_qos_user_interactive。
     *
     * @since 23
     */
    ffrt_qos_max = ffrt_qos_user_interactive,
} ffrt_qos_default_t;

/**
 * @brief QoS类型，用于设置任务的QoS等级。
 *
 * @since 10
 */
typedef int ffrt_qos_t;

/**
 * @brief 任务执行函数指针类型。
 *
 * 函数指针定义了FFRT任务的入口点。FFRT在调度执行任务时调用该函数，并通过唯一的`void*`参数传入用户数据指针。
 *
 * @since 10
 */
typedef void (*ffrt_function_t)(void*);

/**
 * @brief 任务执行体，用于定义任务的执行和销毁回调。
 *
 * `exec`回调在任务被调度时调用，`destroy`回调在任务完成后被调用以释放任务相关资源。两者共同管理FFRT任务的完整生命周期。
 *
 * @since 10
 */
typedef struct {
    /** 执行任务的函数。在任务被调度时由框架调用。 */
    ffrt_function_t exec;
    /** 销毁任务的函数。在任务执行完毕后由框架调用以释放资源。 */
    ffrt_function_t destroy;
    /** 保留字段。需设置为0。 */
    uint64_t reserve[2];
} ffrt_function_header_t;

/**
 * @brief 多种类型结构体的存储大小定义，单位是字节。
 *
 * @since 10
 */
typedef enum {
    /** 任务属性存储大小，单位是字节。 */
    ffrt_task_attr_storage_size = 128,
    /** 任务执行体存储大小，单位是字节。 */
    ffrt_auto_managed_function_storage_size = 64 + sizeof(ffrt_function_header_t),
    /** 互斥锁存储大小，单位是字节。 */
    ffrt_mutex_storage_size = 64,
    /** 条件变量存储大小，单位是字节。 */
    ffrt_cond_storage_size = 64,
    /** 队列属性存储大小，单位是字节。 */
    ffrt_queue_attr_storage_size = 128,
    /**
     * @brief 读写锁存储大小，单位是字节。
     *
     * @since 18
     */
    ffrt_rwlock_storage_size = 64,
    /**
     * @brief 纤程存储大小，单位是字节。
     *
     * 该常量定义纤程存储大小。实际值取决于目标架构：
     * - `__aarch64__`：22
     * - `__arm__`：64
     * - `__x86_64__`：8
     *
     * @since 20
     */
#if defined(__aarch64__)
    ffrt_fiber_storage_size = 22,
#elif defined(__arm__)
    ffrt_fiber_storage_size = 64,
#elif defined(__x86_64__)
    ffrt_fiber_storage_size = 8,
#else
#error "unsupported architecture"
#endif
} ffrt_storage_size_t;

/**
 * @brief 任务类型枚举，用于区分通用并发任务和队列调度的任务。
 *
 * @since 10
 */
typedef enum {
    /** 通用任务。任务可提交到FFRT调度器并发执行。 */
    ffrt_function_kind_general,
    /** 队列任务。任务通过队列按提交顺序依次执行。 */
    ffrt_function_kind_queue,
} ffrt_function_kind_t;

/**
 * @brief 依赖类型枚举。
 *
 * 用于指定任务间的依赖关系（数据就绪或任务完成）。
 *
 * @since 10
 */
typedef enum {
    /** 数据依赖类型。任务仅在所引用的数据就绪后被调度。 */
    ffrt_dependence_data,
    /** 任务依赖类型。任务仅在所引用的任务完成后被调度。 */
    ffrt_dependence_task,
} ffrt_dependence_type_t;

/**
 * @brief 依赖数据项结构，用于描述任务间的单个依赖关系。
 *
 * @since 10
 */
typedef struct {
    /** 依赖类型。 */
    ffrt_dependence_type_t type;
    /** 依赖指针。数据依赖时指向数据，任务依赖时指向任务句柄。 */
    const void* ptr;
} ffrt_dependence_t;

/**
 * @brief 依赖结构体，用于保存任务的依赖列表。
 *
 * @since 10
 */
typedef struct {
    /** 依赖数量。 */
    uint32_t len;
    /** 依赖数据数组。 */
    const ffrt_dependence_t* items;
} ffrt_deps_t;

/**
 * @brief 任务属性结构体，用于存储任务的属性信息。
 *
 * @since 10
 */
typedef struct {
    /**
     * 任务属性的内部存储。请勿直接访问，
     * 通过{@link ffrt_task_attr_init}和`ffrt_task_attr_set_*`等接口管理内容。
     */
    uint32_t storage[(ffrt_task_attr_storage_size + sizeof(uint32_t) - 1) / sizeof(uint32_t)];
} ffrt_task_attr_t;

/**
 * @brief 队列属性结构体，用于存储队列的属性信息。
 *
 * @since 10
 */
typedef struct {
    /**
     * 队列属性的内部存储。请勿直接访问，
     * 通过{@link ffrt_queue_attr_init}和`ffrt_queue_attr_set_*`等接口管理内容。
     */
    uint32_t storage[(ffrt_queue_attr_storage_size + sizeof(uint32_t) - 1) / sizeof(uint32_t)];
} ffrt_queue_attr_t;

/**
 * @brief 任务句柄，用于标识不同的任务。
 *
 * @since 10
 */
typedef void* ffrt_task_handle_t;

/**
 * @brief 错误码枚举，由FFRT接口返回。
 *
 * @since 10
 */
typedef enum {
    /** 通用错误。 */
    ffrt_error = -1,
    /** 成功。 */
    ffrt_success = 0,
    /** 内存不足错误。 */
    ffrt_error_nomem = ENOMEM,
    /** 超时错误。 */
    ffrt_error_timedout = ETIMEDOUT,
    /** 资源忙碌错误。资源正忙，请稍后重试。 */
    ffrt_error_busy = EBUSY,
    /** 无效值错误。 */
    ffrt_error_inval = EINVAL
} ffrt_error_t;

/**
 * @brief 条件变量属性结构体，用于存储条件变量的属性信息。
 *
 * @since 10
 */
typedef struct {
    /** 条件变量属性的内部存储。请勿直接访问。 */
    long storage;
} ffrt_condattr_t;

/**
 * @brief 互斥锁属性结构体，用于存储互斥锁的属性信息。
 *
 * @since 10
 */
typedef struct {
    /** 互斥锁属性的内部存储。请勿直接访问，通过{@link ffrt_mutexattr_init}初始化。 */
    long storage;
} ffrt_mutexattr_t;

/**
 * @brief 读写锁属性结构体，用于存储读写锁的属性信息。
 *
 * @since 18
 */
typedef struct {
    /** 读写锁属性的内部存储。请勿直接访问，直接访问可能导致读写锁属性失效。 */
    long storage;
} ffrt_rwlockattr_t;

/**
 * @brief 互斥锁类型枚举。
 *
 * @since 12
 */
typedef enum {
    /** 普通互斥锁类型。 */
    ffrt_mutex_normal = 0,
    /** 递归互斥锁类型，允许同一线程对同一互斥锁多次加锁。 */
    ffrt_mutex_recursive = 2,
    /** 默认互斥锁类型，等价于`ffrt_mutex_normal`。 */
    ffrt_mutex_default = ffrt_mutex_normal
} ffrt_mutex_type;

/**
 * @brief 互斥锁结构体，用于存储互斥锁的内部数据。
 *
 * @since 10
 */
typedef struct {
    /** 互斥锁的内部存储。请勿直接访问，通过`ffrt_mutex_*`等接口管理。 */
    uint32_t storage[(ffrt_mutex_storage_size + sizeof(uint32_t) - 1) / sizeof(uint32_t)];
} ffrt_mutex_t;

/**
 * @brief 读写锁结构体，用于存储读写锁的内部数据。
 *
 * @since 18
 */
typedef struct {
    /** 读写锁的内部存储。请勿直接访问，通过`ffrt_rwlock_*`等接口管理。 */
    uint32_t storage[(ffrt_rwlock_storage_size + sizeof(uint32_t) - 1) / sizeof(uint32_t)];
} ffrt_rwlock_t;

/**
 * @brief 条件变量结构体，用于存储条件变量的内部数据。
 *
 * @since 10
 */
typedef struct {
    /** 条件变量的内部存储。请勿直接访问，通过`ffrt_cond_*`等接口管理。 */
    uint32_t storage[(ffrt_cond_storage_size + sizeof(uint32_t) - 1) / sizeof(uint32_t)];
} ffrt_cond_t;

/**
 * @brief 纤程结构体，用于存储纤程执行上下文。
 *
 * @since 20
 */
typedef struct {
    /**
     * 纤程执行上下文的内部存储。请勿直接访问，
     * 通过{@link ffrt_fiber_init}初始化，通过{@link ffrt_fiber_switch}切换。
     */
    uintptr_t storage[ffrt_fiber_storage_size];
} ffrt_fiber_t;

/**
 * @brief poller回调函数类型。
 *
 * 当poller检测到已注册事件时调用该回调。`data`指针携带注册时传入的用户数据，`event`值标识触发的事件类型。
 *
 * @param data 指向poller注册时传入的用户数据指针。
 * @param event 触发回调的事件类型。
 * @since 12
 */
typedef void (*ffrt_poller_cb)(void* data, uint32_t event);

/**
 * @brief 定时器回调函数类型。
 *
 * 当定时器到期时调用该回调。`data`指针携带定时器注册时传入的用户数据。
 *
 * @param data 指向定时器注册时传入的用户数据指针。
 * @since 12
 */
typedef void (*ffrt_timer_cb)(void* data);

/**
 * @brief 定时器句柄，用于标识已创建的定时器。
 *
 * @since 12
 */
typedef int ffrt_timer_t;

#ifdef __cplusplus
namespace ffrt {

/**
 * @brief 任务QoS类型枚举。
 *
 * 各枚举值与{@link ffrt_qos_default_t}中对应的枚举值等价。
 *
 * @since 10
 */
enum qos_default {
    /**
     * @brief 继承。
     *
     * 继承调用线程的QoS。用于任务需要采用创建者优先级的场景。
     */
    qos_inherit = ffrt_qos_inherit,
    /**
     * @brief 后台任务。
     *
     * 最低优先级。用于用户无感知的工作，例如后台数据同步或日志刷新。
     */
    qos_background = ffrt_qos_background,
    /**
     * @brief 实用工具类任务。
     *
     * 用于用户可感知但不主动等待的长时间任务，例如数据加载或内容索引。
     */
    qos_utility = ffrt_qos_utility,
    /**
     * @brief 默认类型。
     *
     * 无特殊QoS要求时使用的默认QoS，适用于大多数一般任务。
     */
    qos_default = ffrt_qos_default,
    /**
     * @brief 用户发起的任务。
     *
     * 用于用户主动触发、需要快速响应但不阻塞UI的任务，例如打开文档或执行搜索。
     */
    qos_user_initiated = ffrt_qos_user_initiated,
    /**
     * @brief 时限请求任务。
     *
     * 用于有明确截止时间的任务，系统优先保障其调度资源。
     *
     * @since 23
     */
    qos_deadline_request = ffrt_qos_deadline_request,
    /**
     * @brief 用户交互任务。
     *
     * 适用于UI响应等需要立即与用户交互的操作。
     *
     * @since 23
     */
    qos_user_interactive = ffrt_qos_user_interactive,
    /**
     * @brief 最高QoS等级。
     *
     * 等价于ffrt_qos_user_interactive。
     *
     * @since 23
     */
    qos_max = ffrt_qos_user_interactive,
};

/**
 * @brief QoS类型。
 *
 * @since 10
 */
using qos = int;

}

#endif // __cplusplus
#endif // FFRT_API_C_TYPE_DEF_H
/** @} */

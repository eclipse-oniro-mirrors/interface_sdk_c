/*
 * Copyright (C) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup AbilityRuntime
 * @{
 *
 * @brief 提供原生AbilityRuntime的C接口定义。
 *
 * @since 13
 */
/**
 * @file ability_runtime_common.h
 *
 * @brief 声明AbilityRuntime模块的错误码。
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 13
 */

#ifndef ABILITY_RUNTIME_COMMON_H
#define ABILITY_RUNTIME_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief AbilityRuntime模块的错误码的枚举。
 *
 * @since 13
 */
typedef enum {
    /**
     * 操作成功。
     *
     * @since 13
     */
    ABILITY_RUNTIME_ERROR_CODE_NO_ERROR = 0,
    /**
     * 权限校验失败。
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_PERMISSION_DENIED = 201,
    /**
     * 无效参数。
     *
     * @since 13
     */
    ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID = 401,
    /**
     * 设备类型不支持。
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED = 801,
    /**
     * 指定的Ability名称不存在。
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_NO_SUCH_ABILITY = 16000001,
    /**
     * 接口调用Ability类型错误。
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_INCORRECT_ABILITY_TYPE = 16000002,
    /**
     * 无法启动不可见组件。
     *
     * @since 26.0.0
     */
    ABILITY_RUNTIME_ERROR_CODE_VISIBILITY_VERIFICATION_FAILED = 16000004,
    /**
     * 指定的进程没有权限。
     *
     * @since 26.0.0
     */
    ABILITY_RUNTIME_ERROR_CODE_STATIC_CFG_PERMISSION = 16000005,
    /**
     * 不允许跨用户操作。
     *
     * @since 26.0.0
     */
    ABILITY_RUNTIME_ERROR_CODE_CROSS_USER_OPERATION = 16000006,
    /**
     * 众测应用到期。
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_CROWDTEST_EXPIRED = 16000008,
    /**
     * Wukong模式，不允许启动/停止Ability。
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_WUKONG_MODE = 16000009,
    /**
     * 上下文不存在。
     *
     * @since 13
     */
    ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST = 16000011,
    /**
     * 应用被管控。
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_CONTROLLED = 16000012,
    /**
     * 应用被EDM管控。
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_EDM_CONTROLLED = 16000013,
    /**
     * 限制API 11以上版本三方应用跳转。
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_CROSS_APP = 16000018,
    /**
     * 内部错误。
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_INTERNAL = 16000050,
    /**
     * 非顶层应用。
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_NOT_TOP_ABILITY = 16000053,
    /**
     * 不允许设置窗口启动可见性。
     *
     * @since 17
     */
    ABILITY_RUNTIME_ERROR_VISIBILITY_SETTING_DISABLED = 16000067,
    /**
     * 不支持应用分身和多实例。
     *
     * @since 17
     */
    ABILITY_RUNTIME_ERROR_CODE_MULTI_APP_NOT_SUPPORTED = 16000072,
    /**
     * 无效多实例。
     *
     * @since 17
     */
    ABILITY_RUNTIME_ERROR_CODE_INVALID_APP_INSTANCE_KEY = 16000076,
    /**
     * 应用多实例已达到上限。
     *
     * @since 17
     */
    ABILITY_RUNTIME_ERROR_CODE_UPPER_LIMIT_REACHED = 16000077,
    /**
     * 不支持应用多实例。
     *
     * @since 17
     */
    ABILITY_RUNTIME_ERROR_MULTI_INSTANCE_NOT_SUPPORTED = 16000078,
    /**
     * 不允许设置APP_INSTANCE_KEY。
     *
     * @since 17
     */
    ABILITY_RUNTIME_ERROR_CODE_APP_INSTANCE_KEY_NOT_SUPPORTED = 16000079,
    /**
     * 获取应用信息失败。
     *
     * @since 21
     */
    ABILITY_RUNTIME_ERROR_CODE_GET_APPLICATION_INFO_FAILED = 16000081,
    /**
     * 启动UIAbility超时。
     *
     * @since 21
     */
    ABILITY_RUNTIME_ERROR_CODE_START_TIMEOUT = 16000133,
    /**
     * 接口不允许在应用主线程调用。
     *
     * @since 21
     */
    ABILITY_RUNTIME_ERROR_CODE_MAIN_THREAD_NOT_SUPPORTED = 16000134,
    /**
     * 目标应用程序没有UI的运行能力。
     *
     * @since 26.0.0
     */
    ABILITY_RUNTIME_ERROR_CODE_NO_RUNNING_ABILITIES_WITH_UI = 16000170,
    /**
     * API调用频率过高，超过速率控制限制。
     *
     * @since 26.0.0
     */
    ABILITY_RUNTIME_ERROR_CODE_UPPER_RATE_LIMIT = 16000171,
    /**
     * 连接数超过限制。
     *
     * @since 26.0.0
     */
    ABILITY_RUNTIME_ERROR_CODE_UPPER_CONNECTION_NUMBER_LIMIT = 16000172,
    /**
     * 找不到该属性。
     *
     * @since 26.0.0
     */
    ABILITY_RUNTIME_ERROR_CODE_PROPERTY_NOT_FOUND = 16000173,
    /**
     * 类型不匹配。
     *
     * @since 26.0.0
     */
    ABILITY_RUNTIME_ERROR_CODE_TYPE_MISMATCH = 16000174,
    /**
     * 向远程发送请求失败。
     *
     * @since 26.0.0
     */
    ABILITY_RUNTIME_ERROR_CODE_SEND_REQUEST_FAILED = 16000175,
    /**
     * 调用方和目标不在{@link OH_ABILITY_RUNTIME_LAUNCH_MODE_IN_PROCESS}模式的同一应用程序中。
     *
     * @since 26.0.0
     */
    ABILITY_RUNTIME_ERROR_CODE_CROSS_APP_IN_PROCESS = 16000176,
    /**
     * native ability wrapper无效或不完整。
     *
     * @since 26.0.0
     */
    ABILITY_RUNTIME_ERROR_CODE_ABILITY_WRAPPER_INVALID = 16000177,
    /**
     * 类型库元数据无效，例如主接口缺失或重复。
     *
     * @since 26.0.0
     */
    ABILITY_RUNTIME_ERROR_CODE_METADATA_INVALID = 16000178
} AbilityRuntime_ErrorCode;

#ifdef __cplusplus
}
#endif

/** @} */
#endif // ABILITY_RUNTIME_COMMON_H

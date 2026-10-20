/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
 * @addtogroup AbilityRuntime
 * @{
 *
 * @brief 提供AbilityRuntime模块上下文常量的定义。
 *
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 13
 */

/**
 * @file context_constant.h
 *
 * @brief 提供AbilityRuntime模块上下文常量的定义。
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 13
 */

#ifndef ABILITY_RUNTIME_CONTEXT_CONSTANT_H
#define ABILITY_RUNTIME_CONTEXT_CONSTANT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 文件数据加密等级。
 *
 * @since 13
 */
typedef enum {
    /**
     * 设备级加密区，设备开机后可访问的数据区。<br>对于私有文件，如闹铃、壁纸等，应用可以将这些文件放到设备级加密分区（EL1）中，以保证在用户输入密码前就可以被访问。
     */
    ABILITY_RUNTIME_AREA_MODE_EL1 = 0,
    /**
     * 用户级加密区，设备开机，首次输入密码后才能够访问的数据区。<br>对于需要用户解锁后才能安全使用的个人敏感数据，应用可以将这些文件放到用户级加密区（EL2）中，以保证在用户输入密码后才能被访问。
     */
    ABILITY_RUNTIME_AREA_MODE_EL2 = 1,
    /**
     * 用户级加密区，不同场景的文件权限如下：<br>已打开文件：锁屏时，可读写；解锁后，可读写。<br>未打开文件：锁屏时，不可打开、不可读写；解锁后，可打开、可读写。<br>创建新文件：锁屏时，可创建、可打开、可写不可读；解锁后，
     * 可创建、可打开、可读写。<br>对于应用中的记录步数、文件下载、音乐播放，需要在锁屏时读写和创建新文件，放在（EL3）的加密分区比较合适。
     */
    ABILITY_RUNTIME_AREA_MODE_EL3 = 2,
    /**
     * 用户级加密区，不同场景的文件权限如下：<br>已打开文件：锁屏时，FEB2.0可读写、FEB3.0不可读写；解锁后，可读写。<br>未打开文件：锁屏时，不可打开、不可读写；解锁后，可打开、可读写。<br>创建新文件：锁屏时，
     * 不可创建；解锁后，可创建、可打开、可读写。<br>对于用户安全信息相关的文件，锁屏时不需要读写文件、也不能创建文件，放在（EL4）的加密分区更合适。
     */
    ABILITY_RUNTIME_AREA_MODE_EL4 = 3,
    /**
     * 应用级加密区，不同场景的文件权限如下：<br>已打开文件：锁屏时，可读写；解锁后，可读写。<br>未打开文件：锁屏时，获取DataAccessLock（JS API）下可打开、可读写，否则不可打开、不可读写；解锁后，可打开、
     * 可读写。<br>创建新文件：锁屏时，可创建、可打开、可读写；解锁后，可创建、可打开、可读写。<br>对于用户隐私敏感数据文件，锁屏后默认不可读写，如果锁屏后需要读写文件，则锁屏前可以调用{@link Access}
     * 接口申请继续读写文件，或者锁屏后也需要创建新文件且可读写，放在（EL5）的应用级加密分区更合适。
     */
    ABILITY_RUNTIME_AREA_MODE_EL5 = 4,
} AbilityRuntime_AreaMode;

/**
* @brief 启动Ability时的窗口和dock栏图标的显示模式。例如：需要在后台静默启动服务而不显示UI时使用隐藏模式；需要正常显示UI并与用户交互时使用显示模式。
*
* @since 17
*/
typedef enum {
    /**
     * 隐藏窗口及dock栏图标。仅在PC/2in1设备上生效。
     */
    ABILITY_RUNTIME_HIDE_UPON_START = 0,
    /**
     * 显示窗口及dock栏图标。仅在PC/2in1设备上生效。
     */
    ABILITY_RUNTIME_SHOW_UPON_START = 1,
} AbilityRuntime_StartVisibility;

/**
* @brief 窗口模式。
*
* @since 17
*/
typedef enum {
    /**
     * 窗口模式未定义。
     */
    ABILITY_RUNTIME_WINDOW_MODE_UNDEFINED = 0,
    /**
     * 全屏模式。仅在PC/2in1设备上生效。
     */
    ABILITY_RUNTIME_WINDOW_MODE_FULL_SCREEN = 1,
} AbilityRuntime_WindowMode;

/**
* 在应用内启动UIAbility时，指定窗口支持的显示模式。如果未配置该字段，则默认采用该UIAbility对应的{@link module.json5配置文件}中{@link abilities标签}
* 的supportWindowMode字段取值。
* @since 17
*/
typedef enum {
    /**
     * 窗口支持全屏显示。
     */
    ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_FULL_SCREEN = 0,
    /**
     * 窗口支持分屏显示。
     * 通常需要与ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_FULL_SCREEN或ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_FLOATING组合使用（通过位或运算）
     * ，不建议单独使用ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_SPLIT。当仅配置ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_SPLIT时，PC/
     * 2in1设备上的窗口默认为悬浮窗模式，支持进入分屏模式。
     */
    ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_SPLIT = 1,
    /**
     * 支持窗口化显示。
     */
    ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_FLOATING = 2,
} AbilityRuntime_SupportedWindowMode;

#ifdef __cplusplus
} // extern "C"
#endif

/** @} */
#endif // ABILITY_RUNTIME_CONTEXT_CONSTANT_H
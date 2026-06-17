/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
 * @brief Describes the constants of context.
 * @since 13
 */
/**
 * @file context_constant.h
 *
 * @brief The file declares the context constants of the AbilityRuntime module.
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
 * @brief Enumerates the data encryption levels.
 *
 * @since 13
 */
typedef enum {
    /**
     * Device-level encryption. Directories with this encryption level are accessible after the device is powered on.<
     * br>For private files, such as alarms and wallpapers, the application can place them in a directory with the
     * device-level encryption (EL1) to ensure that they can be accessed before the user enters the password.
     *
     * @since 13
     */
    ABILITY_RUNTIME_AREA_MODE_EL1 = 0,
    /**
     * User-level encryption. Directories with this encryption level are accessible only after the device is powered on
     * and the password is entered (for the first time).<br>For private files, such as alarms and wallpapers, the
     * application can place them in a directory with the device-level encryption (EL1) to ensure that they can be
     * accessed before the user enters the password.
     *
     * @since 13
     */
    ABILITY_RUNTIME_AREA_MODE_EL2 = 1,
    /**
     * User-level encryption. The file permissions vary according to their scenarios.<br>- Open files: You can read and
     * write to files that are already open, whether the screen is locked or unlocked.<br>- Closed files: When the
     * screen is locked, you cannot open, read, or write to closed files. Once the screen is unlocked, you can open,
     * read, and write to closed files.<br>- New files: When the screen is locked, you can create, open, and write to
     * new files, but reading them is not permitted. Once the screen is unlocked, you can create, open, read, and write
     * to new files.<br>For step recording, file download, or music playback that needs to read, write, and create
     * files when the screen is locked, the application can place these files in EL3.
     *
     * @since 13
     */
    ABILITY_RUNTIME_AREA_MODE_EL3 = 2,
    /**
     * User-level encryption. The file permissions vary according to their scenarios.<br>- Open files: When the screen
     * is locked, you can read and write to open files in FEB2.0, but not in FEB3.0. When the screen is unlocked, you
     * can read and write to open files.<br>- Closed files: When the screen is locked, you cannot open, read, or write
     * to closed files. Once the screen is unlocked, you can open, read, and write to closed files.<br>- New files:
     * When the screen is locked, you cannot create files. Once the screen is unlocked, you can create, open, read, and
     * write to new files.<br>For files that are related to user security information and do not need to be read,
     * written, or created when the screen is locked, the application can place them in EL4.
     *
     * @since 13
     */
    ABILITY_RUNTIME_AREA_MODE_EL4 = 3,
    /**
     * Application-level encryption. The file permissions vary according to their scenarios.<br>- Open files: You can
     * read and write to files that are already open, whether the screen is locked or unlocked.<br>* Closed files: When
     * the screen is locked, you can open, read, and write to closed files only if a DataAccessLock (JS API) is
     * obtained. When the screen is unlocked, you can always open, read, and write to closed files.<br>- New files: You
     * can create, open, read, and write to new files, whether the screen is locked or unlocked.<br>By default,
     * sensitive user privacy files cannot be read or written on the lock screen. If such files need to be read or
     * written on the lock screen, you can call {@link Access} to apply for reading or writing files before the screen
     * is locked or create new files that can be read and written after the screen is locked. It is more appropriate to
     * place these files in EL5.
     *
     * @since 13
     */
    ABILITY_RUNTIME_AREA_MODE_EL5 = 4,
} AbilityRuntime_AreaMode;

/**
* @brief Enumerates the visibility modes of the window and dock bar icons when the ability is started.
*
* @since 17
*/
typedef enum {
    /**
     * Hides the window and dock bar icons. This mode takes effect only on 2-in-1 devices.
     *
     * @since 17
     */
    ABILITY_RUNTIME_HIDE_UPON_START = 0,
    /**
     * Displays the window and dock bar icons. This mode takes effect only on 2-in-1 devices.
     *
     * @since 17
     */
    ABILITY_RUNTIME_SHOW_UPON_START = 1,
} AbilityRuntime_StartVisibility;

/**
* @brief Enumerates the window modes.
*
* @since 17
*/
typedef enum {
    /**
     * Window mode not defined.
     *
     * @since 17
     */
    ABILITY_RUNTIME_WINDOW_MODE_UNDEFINED = 0,
    /**
     * Full-screen mode. This mode takes effect only on 2-in-1 devices.
     *
     * @since 17
     */
    ABILITY_RUNTIME_WINDOW_MODE_FULL_SCREEN = 1,
} AbilityRuntime_WindowMode;

/**
* Supported window modes
*
* @since 17
*/
typedef enum {
    /**
     * A window in full-screen mode is supported.
     *
     * @since 17
     */
    ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_FULL_SCREEN = 0,
    /**
     * A window in split-screen mode is supported. Generally, **ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_FULL_SCREEN** or *
     * *ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_FLOATING** must be used together. You are not advised to configure only **
     * ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_SPLIT**. If only **ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_SPLIT** is
     * configured, the window on 2-in-1 devices is in floating window mode by default and can transition to the split-
     * screen mode.
     *
     * @since 17
     */
    ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_SPLIT = 1,
    /**
     * A floating window is supported.
     *
     * @since 17
     */
    ABILITY_RUNTIME_SUPPORTED_WINDOW_MODE_FLOATING = 2,
} AbilityRuntime_SupportedWindowMode;

#ifdef __cplusplus
} // extern "C"
#endif

/** @} */
#endif // ABILITY_RUNTIME_CONTEXT_CONSTANT_H

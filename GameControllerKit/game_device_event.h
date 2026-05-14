/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup GameController
 * @{
 *
 * @brief Provides APIs for game controller capability.
 *
 * @since 21
 */

/**
 * @file game_device_event.h
 * @brief Defines APIs for game device events.
 * @kit GameControllerKit
 * @library libohgame_controller.z.so
 * @syscap SystemCapability.Game.GameController
 * @since 21
 */

#ifndef GAME_DEVICE_EVENT_H
#define GAME_DEVICE_EVENT_H

#include <stdint.h>
#include "game_controller_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines status change types of game devices.
 * @since 21
 */
typedef enum GameDevice_StatusChangedType {
    /**
     * The game device is offline.
     * @since 21
     */
    OFFLINE = 0,

    /**
     * The game device is online.
     * @since 21
     */
    ONLINE = 1,
} GameDevice_StatusChangedType;

/**
 * @brief Defines game device types.
 * @since 21
 */
typedef enum GameDevice_DeviceType {
    /**
     * Unknown.
     * @since 21
     */
    UNKNOWN = 0,

    /**
     * Gamepad.
     * @since 21
     */
    GAME_PAD = 1,
} GameDevice_DeviceType;

/**
 * @brief Defines the game device information.
 * @since 21
 */
typedef struct GameDevice_DeviceInfo GameDevice_DeviceInfo;

/**
 * @brief Defines game device status change events.
 * @since 21
 */
typedef struct GameDevice_DeviceEvent GameDevice_DeviceEvent;

/**
 * @brief Defines the callback function used in {@link OH_GameDevice_RegisterDeviceMonitor}.
 * Called when the game device goes online or offline.
 * @param deviceEvent Output parameter. Game device status change event {@link GameDevice_DeviceEvent}.
 * @since 21
 */
typedef void(* GameDevice_DeviceMonitorCallback)(const struct GameDevice_DeviceEvent* deviceEvent);

/**
 * @brief Obtains the status change type from {@link GameDevice_DeviceEvent}.
 * @param deviceEvent Pointer to the {@link GameDevice_DeviceEvent} instance.
 *     The pointer cannot be null. Otherwise, an error code is returned.
 * @param statusChangedType Output parameter. Game device status change type.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceEvent_GetChangedType(
    const struct GameDevice_DeviceEvent* deviceEvent,
    GameDevice_StatusChangedType* statusChangedType);

/**
 * @brief Obtains the game device information from {@link GameDevice_DeviceEvent}.
 * @param deviceEvent Pointer to the {@link GameDevice_DeviceEvent} instance.
 *     The pointer cannot be null. Otherwise, an error code is returned.
 * @param deviceInfo Output parameter. The level-2 pointer points to the {@link GameDevice_DeviceInfo} instance.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceEvent_GetDeviceInfo(
    const struct GameDevice_DeviceEvent* deviceEvent,
    GameDevice_DeviceInfo** deviceInfo);

/**
 * @brief Destroys the {@link GameDevice_DeviceInfo} instance when it is no longer in use.
 * @param deviceInfo Level-2 pointer to the {@link GameDevice_DeviceInfo} instance.
 *     The pointer cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceInfo is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DestroyDeviceInfo(GameDevice_DeviceInfo** deviceInfo);

/**
 * @brief Obtains the device ID from {@link GameDevice_DeviceInfo}.
 * @param deviceInfo Pointer to the {@link GameDevice_DeviceInfo} instance.
 *     The pointer cannot be null. Otherwise, an error code is returned.
 * @param deviceId Output parameter. The level-2 pointer points to the game device ID.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceInfo or deviceId is null.</li>
 *     <li>Returns {@link GAME_CONTROLLER_NO_MEMORY} if there is no sufficient memory.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetDeviceId(const struct GameDevice_DeviceInfo* deviceInfo,
                                                              char** deviceId);

/**
 * @brief Obtains the game device name from {@link GameDevice_DeviceInfo}.
 * @param deviceInfo Pointer to the {@link GameDevice_DeviceInfo} instance.
 *     The pointer cannot be null. Otherwise, an error code is returned.
 * @param name Output parameter. The level-2 pointer points to the game device name.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceInfo or name is null.</li>
 *     <li>Returns {@link GAME_CONTROLLER_NO_MEMORY} if there is no sufficient memory.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetName(const struct GameDevice_DeviceInfo* deviceInfo,
                                                          char** name);

/**
 * @brief Obtains the product information from {@link GameDevice_DeviceInfo}.
 * @param deviceInfo Pointer to the {@link GameDevice_DeviceInfo} instance.
 *     The pointer cannot be null. Otherwise, an error code is returned.
 * @param product Output parameter. Product information.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceInfo is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetProduct(const struct GameDevice_DeviceInfo* deviceInfo,
                                                             int32_t* product);

/**
 * @brief Obtains the version information from {@link GameDevice_DeviceInfo}.
 * @param deviceInfo Pointer to the {@link GameDevice_DeviceInfo} instance.
 *     The pointer cannot be null. Otherwise, an error code is returned.
 * @param version Output parameter. Version information.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceInfo is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetVersion(const struct GameDevice_DeviceInfo* deviceInfo,
                                                             int32_t* version);

/**
 * @brief Obtains the physical address from {@link GameDevice_DeviceInfo}.
 * @param deviceInfo Pointer to the {@link GameDevice_DeviceInfo} instance.
 *     The pointer cannot be null. Otherwise, an error code is returned.
 * @param physicalAddress Output parameter. The level-2 pointer points to the physical address.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceInfo or physicalAddress is null.</li>
 *     <li>Returns {@link GAME_CONTROLLER_NO_MEMORY} if there is no sufficient memory.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetPhysicalAddress(const struct GameDevice_DeviceInfo* deviceInfo,
                                                                     char** physicalAddress);

/**
 * @brief Obtains the game device type from {@link GameDevice_DeviceInfo}.
 * @param deviceInfo Pointer to the {@link GameDevice_DeviceInfo} instance.
 *     The pointer cannot be null. Otherwise, an error code is returned.
 * @param deviceType Output parameter. Game device type.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceInfo is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetDeviceType(const struct GameDevice_DeviceInfo* deviceInfo,
                                                                GameDevice_DeviceType* deviceType);

#ifdef __cplusplus
}
#endif

#endif //GAME_DEVICE_EVENT_H
/** @} */

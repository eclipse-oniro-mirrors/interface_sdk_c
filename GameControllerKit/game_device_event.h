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
 *
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
 * @brief Defines status change types of devices.
 *
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
 * @brief Defines device types.
 *
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
 * @brief Defines the device information.
 *
 * @since 21
 */
typedef struct GameDevice_DeviceInfo GameDevice_DeviceInfo;

/**
 * @brief Defines device status change events.
 *
 * @since 21
 */
typedef struct GameDevice_DeviceEvent GameDevice_DeviceEvent;

/**
 * @brief Defines the callback function used in {@link OH_GameDevice_RegisterDeviceMonitor}. Called when the device
 * goes online or offline.
 *
 * @param deviceEvent Output parameter. Game device status change event {@link GameDevice_DeviceEvent}.
 * @since 21
 */
typedef void(* GameDevice_DeviceMonitorCallback)(const struct GameDevice_DeviceEvent* deviceEvent);

/**
 * @brief Obtains the status change type from a device status change event.
 *
 * @param deviceEvent Pointer to the {@link GameDevice_DeviceEvent} instance. The pointer cannot be null.
 * @param statusChangedType Output parameter. Device status change type.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceEvent_GetChangedType(
    const struct GameDevice_DeviceEvent* deviceEvent,
    GameDevice_StatusChangedType* statusChangedType);

/**
 * @brief Obtains the device information from a device status change event.
 *
 * @param deviceEvent Pointer to the {@link GameDevice_DeviceEvent} instance. The pointer cannot be null.
 * @param deviceInfo Output parameter. Double pointer to the device information.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceEvent_GetDeviceInfo(
    const struct GameDevice_DeviceEvent* deviceEvent,
    GameDevice_DeviceInfo** deviceInfo);

/**
 * @brief Destroys a device information instance.
 *
 * @param deviceInfo Double pointer to the {@link GameDevice_DeviceInfo} instance. The pointer cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceInfo is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DestroyDeviceInfo(GameDevice_DeviceInfo** deviceInfo);

/**
 * @brief Obtains the device ID from the device information.
 *
 * @param deviceInfo Pointer to the {@link GameDevice_DeviceInfo} instance. The pointer cannot be null.
 * @param deviceId Output parameter. Double pointer to the device ID.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceInfo or deviceId is null.</li>
 *     <li>Returns {@link GAME_CONTROLLER_NO_MEMORY} if there is no sufficient memory.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetDeviceId(const struct GameDevice_DeviceInfo* deviceInfo,
                                                              char** deviceId);

/**
 * @brief Obtains the device name from the device information.
 *
 * @param deviceInfo Pointer to the {@link GameDevice_DeviceInfo} instance. The pointer cannot be null.
 * @param name Output parameter. Double pointer to the device name.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceInfo or name is null.</li>
 *     <li>Returns {@link GAME_CONTROLLER_NO_MEMORY} if there is no sufficient memory.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetName(const struct GameDevice_DeviceInfo* deviceInfo,
                                                          char** name);

/**
 * @brief Obtains the product information from the device information.
 *
 * @param deviceInfo Pointer to the {@link GameDevice_DeviceInfo} instance. The pointer cannot be null.
 * @param product Output parameter. Product information.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceInfo is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetProduct(const struct GameDevice_DeviceInfo* deviceInfo,
                                                             int32_t* product);

/**
 * @brief Obtains the version information from the device information.
 *
 * @param deviceInfo Pointer to the {@link GameDevice_DeviceInfo} instance. The pointer cannot be null.
 * @param version Output parameter. Version information.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceInfo is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetVersion(const struct GameDevice_DeviceInfo* deviceInfo,
                                                             int32_t* version);

/**
 * @brief Obtains the physical address from the device information.
 *
 * @param deviceInfo Pointer to the {@link GameDevice_DeviceInfo} instance. The pointer cannot be null.
 * @param physicalAddress Output parameter. Double pointer to the physical address.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceInfo or physicalAddress is null.</li>
 *     <li>Returns {@link GAME_CONTROLLER_NO_MEMORY} if there is no sufficient memory.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetPhysicalAddress(const struct GameDevice_DeviceInfo* deviceInfo,
                                                                     char** physicalAddress);

/**
 * @brief Obtains the device type from the device information.
 *
 * @param deviceInfo Pointer to the {@link GameDevice_DeviceInfo} instance. The pointer cannot be null.
 * @param deviceType Output parameter. Device type.
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

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
 * @file game_device.h
 * @brief Defines APIs for game devices.
 * @kit GameControllerKit
 * @library libohgame_controller.z.so
 * @syscap SystemCapability.Game.GameController
 * @since 21
 */

#ifndef GAME_DEVICE_H
#define GAME_DEVICE_H

#include <stdint.h>
#include "game_device_event.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the calling result of {@link OH_GameDevice_GetAllDeviceInfos}.
 * @since 21
 */
typedef struct GameDevice_AllDeviceInfos GameDevice_AllDeviceInfos;

/**
 * @brief Obtains information about all online game devices.
 * @param allDeviceInfos Output parameter. Level-2 pointer to the {@link GameDevice_AllDeviceInfos}
 * instance. The pointer cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_MULTIMODAL_INPUT_ERROR} if the multimodal input is abnormal.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_GetAllDeviceInfos(GameDevice_AllDeviceInfos** allDeviceInfos);

/**
 * @brief Registers the listening callback for game device status change events.
 * @param deviceMonitorCallback Callback function {@link GameDevice_DeviceMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if deviceMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_RegisterDeviceMonitor(
    GameDevice_DeviceMonitorCallback deviceMonitorCallback);

/**
 * @brief Unregisters the listening callback for game device status change events.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_UnregisterDeviceMonitor(void);

/**
 * @brief Destroys the {@link GameDevice_AllDeviceInfos} instance when it is no longer in use.
 * @param allDeviceInfos Level-2 pointer to the {@link GameDevice_AllDeviceInfos} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if allDeviceInfos is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DestroyAllDeviceInfos(GameDevice_AllDeviceInfos** allDeviceInfos);

/**
 * @brief Obtains the number of game devices.
 * @param allDeviceInfos Pointer to the {@link GameDevice_AllDeviceInfos} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param count Output parameter. Number of game devices.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if allDeviceInfos is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_AllDeviceInfos_GetCount(
    const struct GameDevice_AllDeviceInfos* allDeviceInfos,
    int32_t* count);

/**
 * @brief Obtains information about a game device with a specified index.
 * @param allDeviceInfos Pointer to the {@link GameDevice_AllDeviceInfos} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param index Index of the game device to be queried.
 * @param deviceInfo Output parameter. The level-2 pointer points to the {@link GameDevice_DeviceInfo} instance.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if allDeviceInfos is null, or the index is less than 0
 * or greater than or equal to the total number of game devices.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_AllDeviceInfos_GetDeviceInfo(
    const struct GameDevice_AllDeviceInfos* allDeviceInfos,
    const int32_t index,
    GameDevice_DeviceInfo** deviceInfo);

#ifdef __cplusplus
}
#endif

#endif //GAME_DEVICE_H
/** @} */

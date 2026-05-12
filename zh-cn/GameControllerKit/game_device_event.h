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
 * @brief 定义游戏设备事件的接口。
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
 * @brief 此枚举定义设备的状态变化类型。
 * @since 21
 */
typedef enum GameDevice_StatusChangedType {
    /**
     * 设备下线。
     * @since 21
     */
    OFFLINE = 0,

    /**
     * 设备上线。
     * @since 21
     */
    ONLINE = 1,
} GameDevice_StatusChangedType;

/**
 * @brief 此枚举定义设备类型。
 * @since 21
 */
typedef enum GameDevice_DeviceType {
    /**
     * 未知。
     * @since 21
     */
    UNKNOWN = 0,

    /**
     * 游戏手柄。
     * @since 21
     */
    GAME_PAD = 1,
} GameDevice_DeviceType;

/**
 * @brief 定义设备信息。
 * @since 21
 */
typedef struct GameDevice_DeviceInfo GameDevice_DeviceInfo;

/**
 * @brief 定义设备状态变化事件。
 * @since 21
 */
typedef struct GameDevice_DeviceEvent GameDevice_DeviceEvent;

/**
 * @brief 定义{@link OH_GameDevice_RegisterDeviceMonitor}中使用的回调函数。当设备上线或下线时，该回调函数将被调用。
 * @param deviceEvent 输出参数。设备状态变化事件{@link GameDevice_DeviceEvent}。
 * @since 21
 */
typedef void(* GameDevice_DeviceMonitorCallback)(const struct GameDevice_DeviceEvent* deviceEvent);

/**
 * @brief 从设备状态变化事件中获取状态变化类型。
 * @param deviceEvent 指针指向{@link GameDevice_DeviceEvent}实例，不能为空，否则将返回错误码。
 * @param statusChangedType 输出参数，设备状态变化类型。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数deviceEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceEvent_GetChangedType(
    const struct GameDevice_DeviceEvent* deviceEvent,
    GameDevice_StatusChangedType* statusChangedType);

/**
 * @brief 从设备状态变化事件中获取设备信息。
 * @param deviceEvent 指针指向{@link GameDevice_DeviceEvent}实例，不能为空，否则将返回错误码。
 * @param deviceInfo 输出参数，二级指针指向设备信息。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数deviceEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceEvent_GetDeviceInfo(
    const struct GameDevice_DeviceEvent* deviceEvent,
    GameDevice_DeviceInfo** deviceInfo);

/**
 * @brief 销毁设备信息实例。
 * @param deviceInfo 二级指针指向{@link GameDevice_DeviceInfo}实例，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数deviceInfo为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DestroyDeviceInfo(GameDevice_DeviceInfo** deviceInfo);

/**
 * @brief 从设备信息中获取设备ID。
 * @param deviceInfo 指针指向{@link GameDevice_DeviceInfo}实例，不能为空，否则将返回错误码。
 * @param deviceId 输出参数，二级指针指向设备ID。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数deviceInfo或deviceId为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li>
 * <li>如果设备内存不足，返回{@link GAME_CONTROLLER_NO_MEMORY}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetDeviceId(const struct GameDevice_DeviceInfo* deviceInfo,
                                                              char** deviceId);

/**
 * @brief 从设备信息中获取设备名称。
 * @param deviceInfo 指针指向{@link GameDevice_DeviceInfo}实例，不能为空，否则将返回错误码。
 * @param name 输出参数，二级指针指向设备名称。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数deviceInfo或name为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li>
 * <li>如果设备内存不足，返回{@link GAME_CONTROLLER_NO_MEMORY}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetName(const struct GameDevice_DeviceInfo* deviceInfo,
                                                          char** name);

/**
 * @brief 从设备信息中获取产品信息。
 * @param deviceInfo 指针指向{@link GameDevice_DeviceInfo}实例，不能为空，否则将返回错误码。
 * @param product 输出参数，产品信息。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数deviceInfo为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetProduct(const struct GameDevice_DeviceInfo* deviceInfo,
                                                             int32_t* product);

/**
 * @brief 从设备信息中获取版本信息。
 * @param deviceInfo 指针指向{@link GameDevice_DeviceInfo}实例，不能为空，否则将返回错误码。
 * @param version 输出参数，版本信息。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数deviceInfo为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetVersion(const struct GameDevice_DeviceInfo* deviceInfo,
                                                             int32_t* version);

/**
 * @brief 从设备信息中获取物理地址。
 * @param deviceInfo 指针指向{@link GameDevice_DeviceInfo}实例，不能为空，否则将返回错误码。
 * @param physicalAddress 输出参数，二级指针指向物理地址。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数deviceInfo或physicalAddress为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li>
 * <li>如果设备内存不足，返回{@link GAME_CONTROLLER_NO_MEMORY}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetPhysicalAddress(const struct GameDevice_DeviceInfo* deviceInfo,
                                                                     char** physicalAddress);

/**
 * @brief 从设备信息中获取设备类型。
 * @param deviceInfo 指针指向{@link GameDevice_DeviceInfo}实例，不能为空，否则将返回错误码。
 * @param deviceType 输出参数，设备类型。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数deviceInfo为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DeviceInfo_GetDeviceType(const struct GameDevice_DeviceInfo* deviceInfo,
                                                                GameDevice_DeviceType* deviceType);

#ifdef __cplusplus
}
#endif

#endif //GAME_DEVICE_EVENT_H
/** @} */

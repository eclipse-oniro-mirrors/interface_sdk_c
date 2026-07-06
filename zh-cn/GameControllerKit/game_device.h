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
 * @brief 定义游戏设备的接口。
 *
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
 * @brief 定义{@link OH_GameDevice_GetAllDeviceInfos}接口的调用结果。
 *
 * @since 21
 */
typedef struct GameDevice_AllDeviceInfos GameDevice_AllDeviceInfos;

/**
 * @brief 获取所有在线设备的信息。
 *
 * @param allDeviceInfos 输出参数。二级指针指向{@link GameDevice_AllDeviceInfos}实例，不能为空。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数allDeviceInfos为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li>
 *     <li>如果查询多模输入中所有设备信息失败，返回{@link GAME_CONTROLLER_MULTIMODAL_INPUT_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_GetAllDeviceInfos(GameDevice_AllDeviceInfos** allDeviceInfos);

/**
 * @brief 注册设备状态变化事件的监听回调。
 *
 * @param deviceMonitorCallback 回调函数{@link GameDevice_DeviceMonitorCallback}，不能为空。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数deviceMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_RegisterDeviceMonitor(
    GameDevice_DeviceMonitorCallback deviceMonitorCallback);

/**
 * @brief 取消注册设备状态变化事件的监听回调。
 *
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_UnregisterDeviceMonitor(void);

/**
 * @brief 销毁所有设备信息实例。
 *
 * @param allDeviceInfos 二级指针指向{@link GameDevice_AllDeviceInfos}实例，不能为空。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数allDeviceInfos为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_DestroyAllDeviceInfos(GameDevice_AllDeviceInfos** allDeviceInfos);

/**
 * @brief 获取设备数量。
 *
 * @param allDeviceInfos 指针指向{@link GameDevice_AllDeviceInfos}实例，不能为空。
 * @param count 输出参数，设备数量。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数allDeviceInfos为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GameDevice_AllDeviceInfos_GetCount(
    const struct GameDevice_AllDeviceInfos* allDeviceInfos,
    int32_t* count);

/**
 * @brief 获取指定索引的设备信息。
 *
 * @param allDeviceInfos 指针指向{@link GameDevice_AllDeviceInfos}实例，不能为空。
 * @param index 指定设备索引。
 * @param deviceInfo 输出参数，二级指针指向设备信息。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数allDeviceInfos为null，或index小于0或大于等于设备总数，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
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

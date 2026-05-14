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
 * @file game_pad.h
 * @brief 定义游戏手柄的接口。
 * @kit GameControllerKit
 * @library libohgame_controller.z.so
 * @syscap SystemCapability.Game.GameController
 * @since 21
 */

#ifndef GAME_PAD_H
#define GAME_PAD_H

#include <stdint.h>
#include "game_pad_event.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 注册LeftShoulder按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftShoulder_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册LeftShoulder按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftShoulder_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册RightShoulder按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightShoulder_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册RightShoulder按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightShoulder_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册LeftTrigger按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftTrigger_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册LeftTrigger按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftTrigger_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册LeftTrigger轴事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_AxisInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *      <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftTrigger_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册LeftTrigger轴事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftTrigger_UnregisterAxisInputMonitor(void);

/**
 * @brief 注册RightTrigger按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *      <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightTrigger_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册RightTrigger按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightTrigger_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册RightTrigger轴事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_AxisInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightTrigger_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册RightTrigger轴事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightTrigger_UnregisterAxisInputMonitor(void);

/**
 * @brief 注册Menu按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonMenu_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册Menu按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonMenu_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册Home按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonHome_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册Home按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonHome_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册A按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonA_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册A按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonA_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册B按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonB_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册B按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonB_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册X按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonX_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册X按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonX_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册Y按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonY_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册Y按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonY_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册C按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonC_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册C按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonC_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册Dpad_LeftButton按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_LeftButton_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册Dpad_LeftButton按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_LeftButton_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册Dpad_RightButton按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_RightButton_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册Dpad_RightButton按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_RightButton_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册Dpad_UpButton按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_UpButton_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册Dpad_UpButton按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_UpButton_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册Dpad_DownButton按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_DownButton_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册Dpad_DownButton按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_DownButton_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册Dpad轴事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_AxisInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册Dpad轴事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_UnregisterAxisInputMonitor(void);

/**
 * @brief 注册LeftThumbstick按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftThumbstick_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册LeftThumbstick按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftThumbstick_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册LeftThumbstick轴事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_AxisInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftThumbstick_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册LeftThumbstick轴事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftThumbstick_UnregisterAxisInputMonitor(void);

/**
 * @brief 注册RightThumbstick按键事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_ButtonInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightThumbstick_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册RightThumbstick按键事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightThumbstick_UnregisterButtonInputMonitor(void);

/**
 * @brief 注册RightThumbstick轴事件的监听回调。
 * @param inputMonitorCallback 回调函数{@link GamePad_AxisInputMonitorCallback}，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 *     <li>如果参数inputMonitorCallback为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightThumbstick_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief 取消注册RightThumbstick轴事件的监听回调。
 * @return 如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightThumbstick_UnregisterAxisInputMonitor(void);

#ifdef __cplusplus
}
#endif

#endif //GAME_PAD_H
/** @} */

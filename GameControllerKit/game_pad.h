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
 * @brief Defines APIs for gamepads.
 *
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
 * @brief Registers a callback for Left Shoulder button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftShoulder_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for Left Shoulder button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftShoulder_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for Right Shoulder button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightShoulder_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for Right Shoulder button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightShoulder_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for Left Trigger button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftTrigger_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for Left Trigger button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftTrigger_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for Left Trigger axis events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_AxisInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftTrigger_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for Left Trigger axis events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftTrigger_UnregisterAxisInputMonitor(void);

/**
 * @brief Registers a callback for Right Trigger button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightTrigger_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for Right Trigger button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightTrigger_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for Right Trigger axis events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_AxisInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightTrigger_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for Right Trigger axis events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightTrigger_UnregisterAxisInputMonitor(void);

/**
 * @brief Registers a callback for Menu button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonMenu_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for Menu button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonMenu_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for Home button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonHome_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for Home button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonHome_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for A button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonA_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for A button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonA_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for B button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonB_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for B button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonB_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for X button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonX_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for X button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonX_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for Y button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonY_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for Y button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonY_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for C button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonC_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for C button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonC_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for D-pad Left button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_LeftButton_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for D-pad Left button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_LeftButton_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for D-pad Right button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_RightButton_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for D-pad Right button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_RightButton_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for D-pad Up button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_UpButton_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for D-pad Up button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_UpButton_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for D-pad Down button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_DownButton_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for D-pad Down button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_DownButton_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for D-pad axis events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_AxisInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for D-pad axis events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_UnregisterAxisInputMonitor(void);

/**
 * @brief Registers a callback for Left Thumbstick button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftThumbstick_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for Left Thumbstick button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftThumbstick_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for Left Thumbstick axis events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_AxisInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftThumbstick_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for Left Thumbstick axis events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftThumbstick_UnregisterAxisInputMonitor(void);

/**
 * @brief Registers a callback for Right Thumbstick button events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightThumbstick_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for Right Thumbstick button events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightThumbstick_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers a callback for Right Thumbstick axis events.
 *
 * @param inputMonitorCallback Callback function {@link GamePad_AxisInputMonitorCallback}, which cannot be null.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 *     <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightThumbstick_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the callback for Right Thumbstick axis events.
 *
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightThumbstick_UnregisterAxisInputMonitor(void);

#ifdef __cplusplus
}
#endif

#endif //GAME_PAD_H
/** @} */

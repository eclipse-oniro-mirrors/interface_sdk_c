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
 * @brief Registers the listening callback for the Left Shoulder button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftShoulder_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Left Shoulder button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftShoulder_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the Right Shoulder button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightShoulder_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Right Shoulder button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightShoulder_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the Left Trigger button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftTrigger_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Left Trigger button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftTrigger_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the Left Trigger axis event.
 * @param inputMonitorCallback Callback function {@link GamePad_AxisInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftTrigger_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Left Trigger axis event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftTrigger_UnregisterAxisInputMonitor(void);

/**
 * @brief Registers the listening callback for the Right Trigger button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightTrigger_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Right Trigger button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightTrigger_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the Right Trigger axis event.
 * @param inputMonitorCallback Callback function {@link GamePad_AxisInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightTrigger_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Right Trigger axis event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightTrigger_UnregisterAxisInputMonitor(void);

/**
 * @brief Registers the listening callback for the Menu button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonMenu_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Menu button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonMenu_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the Home button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonHome_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Home button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonHome_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the A button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonA_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the A button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonA_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the B button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonB_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the B button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonB_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the X button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonX_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the X button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonX_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the Y button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonY_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Y button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonY_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the C button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonC_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the C button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonC_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the Left Directional button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_LeftButton_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Left Directional button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_LeftButton_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the Right Directional button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_RightButton_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Right Directional button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_RightButton_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the Up Directional button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_UpButton_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Up Directional button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_UpButton_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the Down Directional button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_DownButton_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Down Directional button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_DownButton_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the Directional Pad button axis event.
 * @param inputMonitorCallback Callback function {@link GamePad_AxisInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Directional Pad button axis event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_Dpad_UnregisterAxisInputMonitor(void);

/**
 * @brief Registers the listening callback for the Left Thumbstick button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftThumbstick_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Left Thumbstick button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftThumbstick_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the Left Thumbstick axis event.
 * @param inputMonitorCallback Callback function {@link GamePad_AxisInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftThumbstick_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Left Thumbstick axis event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_LeftThumbstick_UnregisterAxisInputMonitor(void);

/**
 * @brief Registers the listening callback for the Right Thumbstick button event.
 * @param inputMonitorCallback Callback function {@link GamePad_ButtonInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightThumbstick_RegisterButtonInputMonitor(
    GamePad_ButtonInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Right Thumbstick button event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightThumbstick_UnregisterButtonInputMonitor(void);

/**
 * @brief Registers the listening callback for the Right Thumbstick axis event.
 * @param inputMonitorCallback Callback function {@link GamePad_AxisInputMonitorCallback}.
 * The callback function cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if inputMonitorCallback is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightThumbstick_RegisterAxisInputMonitor(
    GamePad_AxisInputMonitorCallback inputMonitorCallback);

/**
 * @brief Unregisters the listening callback for the Right Thumbstick axis event.
 * @return Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.
 * @since 21
 */
GameController_ErrorCode OH_GamePad_RightThumbstick_UnregisterAxisInputMonitor(void);

#ifdef __cplusplus
}
#endif

#endif //GAME_PAD_H
/** @} */

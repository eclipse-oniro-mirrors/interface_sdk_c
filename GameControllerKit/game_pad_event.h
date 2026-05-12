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
 * @file game_pad_event.h
 * @brief Defines APIs for gamepad events.
 * @kit GameControllerKit
 * @library libohgame_controller.z.so
 * @syscap SystemCapability.Game.GameController
 * @since 21
 */

#ifndef GAME_PAD_EVENT_H
#define GAME_PAD_EVENT_H

#include <stdint.h>
#include "game_controller_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines source types of gamepad axis events.
 * @since 21
 */
typedef enum GamePad_AxisSourceType {
    /**
     * The axis event comes from the directional pad (D-pad).
     * @since 21
     */
    DPAD = 0,

    /**
     * The axis event comes from the left thumbstick.
     * @since 21
     */
    LEFT_THUMBSTICK = 1,

    /**
     * The axis event comes from the right thumbstick.
     * @since 21
     */
    RIGHT_THUMBSTICK = 2,

    /**
     * The axis event comes from the left trigger.
     * @since 21
     */
    LEFT_TRIGGER = 3,

    /**
     * The axis event comes from the right trigger.
     * @since 21
     */
    RIGHT_TRIGGER = 4,
} GamePad_AxisSourceType;

/**
 * @brief Defines button action types of the gamepad.
 * @since 21
 */
typedef enum GamePad_Button_ActionType {
    /**
     * The button is pressed.
	 * @since 21
     */
    DOWN = 0,

    /**
     * The button is released.
	 * @since 21
     */
    UP = 1,
} GamePad_Button_ActionType;

/**
 * @brief Defines gamepad button events.
 * @since 21
 */
typedef struct GamePad_ButtonEvent GamePad_ButtonEvent;

/**
 * @brief Defines gamepad axis events.
 * @since 21
 */
typedef struct GamePad_AxisEvent GamePad_AxisEvent;

/**
 * @brief Defines pressed buttons.
 * @since 21
 */
typedef struct GamePad_PressedButton GamePad_PressedButton;

/**
 * @brief Defines the callback function used in the button event registration listening API.
 * Called when a player presses a button.
 * @param buttonEvent Output parameter. Gamepad button event {@link GamePad_ButtonEvent}.
 * @since 21
 */
typedef void(* GamePad_ButtonInputMonitorCallback)(const struct GamePad_ButtonEvent* buttonEvent);

/**
 * @brief Defines the callback function used in the axis event registration listening API.
 * Called when a player operates a joystick.
 * @param axisEvent Output parameter. Game controller axis event {@link GamePad_AxisEvent}.
 * @since 21
 */
typedef void(* GamePad_AxisInputMonitorCallback)(const struct GamePad_AxisEvent* axisEvent);

/**
 * @brief Obtains the game device ID from {@link GamePad_ButtonEvent}.
 * @param buttonEvent Pointer to the {@link GamePad_ButtonEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param deviceId Output parameter. The level-2 pointer points to the game device ID.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if buttonEvent or deviceId is null.</li>
 * <li>Returns {@link GAME_CONTROLLER_NO_MEMORY} if there is no sufficient memory.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonEvent_GetDeviceId(const struct GamePad_ButtonEvent* buttonEvent,
                                                            char** deviceId);

/**
 * @brief Obtains the button action type from {@link GamePad_ButtonEvent}.
 * @param buttonEvent Pointer to the {@link GamePad_ButtonEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param actionType Output parameter. Button action type.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if buttonEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonEvent_GetButtonAction(const struct GamePad_ButtonEvent* buttonEvent,
                                                                GamePad_Button_ActionType* actionType);

/**
 * @brief Obtains the button code from {@link GamePad_ButtonEvent}.
 * @param buttonEvent Pointer to the {@link GamePad_ButtonEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param code Output parameter. Button code.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if buttonEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonEvent_GetButtonCode(const struct GamePad_ButtonEvent* buttonEvent,
                                                              int32_t* code);

/**
 * @brief Obtains the button name from {@link GamePad_ButtonEvent}.
 * @param buttonEvent Pointer to the {@link GamePad_ButtonEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param codeName Output parameter. The level-2 pointer points to the button name.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if buttonEvent or codeName is null.</li>
 * <li>Returns {@link GAME_CONTROLLER_NO_MEMORY} if there is no sufficient memory.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonEvent_GetButtonCodeName(const struct GamePad_ButtonEvent* buttonEvent,
                                                                  char** codeName);

/**
 * @brief Obtains the number of pressed buttons from {@link GamePad_ButtonEvent}.
 * @param buttonEvent Pointer to the {@link GamePad_ButtonEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param count Output parameter. Number of pressed buttons.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if buttonEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_PressedButtons_GetCount(const struct GamePad_ButtonEvent* buttonEvent,
                                                            int32_t* count);

/**
 * @brief Obtains the pressed button with a given index from {@link GamePad_ButtonEvent}.
 * @param buttonEvent Pointer to the {@link GamePad_ButtonEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param index Button index.
 * @param pressedButton Output parameter. The level-2 pointer points to the pressed button.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if buttonEvent is null, or the index is less than 0
 * or greater than or equal to the number of all buttons.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_PressedButtons_GetButtonInfo(const struct GamePad_ButtonEvent* buttonEvent,
                                                                 const int32_t index,
                                                                 GamePad_PressedButton** pressedButton);

/**
 * @brief Destroys the {@link GamePad_PressedButton} instance when it is no longer in use.
 * @param pressedButton Level-2 pointer to the {@link GamePad_PressedButton} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if pressedButton is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_DestroyPressedButton(GamePad_PressedButton** pressedButton);

/**
 * @brief Obtains the button code from {@link GamePad_PressedButton}.
 * @param pressedButton Pointer to the {@link GamePad_PressedButton} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param code Output parameter. Button code.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if pressedButton is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_PressedButton_GetButtonCode(const struct GamePad_PressedButton* pressedButton,
                                                                int32_t* code);

/**
 * @brief Obtains the button name from {@link GamePad_PressedButton}.
 * @param pressedButton Pointer to the {@link GamePad_PressedButton} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param codeName Output parameter. The level-2 pointer points to the button name.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if pressedButton or codeName is null.</li>
 * <li>Returns {@link GAME_CONTROLLER_NO_MEMORY} if there is no sufficient memory.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_PressedButton_GetButtonCodeName(const struct GamePad_PressedButton* pressedButton,
                                                                    char** codeName);

/**
 * @brief Obtains the button action time from {@link GamePad_ButtonEvent}.
 * @param buttonEvent Pointer to the {@link GamePad_ButtonEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param actionTime Output parameter. Time when the button action is performed.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if buttonEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonEvent_GetActionTime(const struct GamePad_ButtonEvent* buttonEvent,
                                                              int64_t* actionTime);

/**
 * @brief Obtains the game device ID from {@link GamePad_AxisEvent}.
 * @param axisEvent Pointer to the {@link GamePad_AxisEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param deviceId Output parameter. The level-2 pointer points to the game device ID.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if axisEvent or deviceId is null.</li>
 * <li>Returns {@link GAME_CONTROLLER_NO_MEMORY} if there is no sufficient memory.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetDeviceId(const struct GamePad_AxisEvent* axisEvent,
                                                          char** deviceId);

/**
 * @brief Obtains the source type of axis event from {@link GamePad_AxisEvent}.
 * @param axisEvent Pointer to the {@link GamePad_AxisEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param axisSourceType Output parameter. Source type of the axis event {@link GamePad_AxisSourceType}.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if axisEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetAxisSourceType(const struct GamePad_AxisEvent* axisEvent,
                                                                GamePad_AxisSourceType* axisSourceType);

/**
 * @brief Obtains the X-axis value from {@link GamePad_AxisEvent}.
 * @param axisEvent Pointer to the {@link GamePad_AxisEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param axisValue Output parameter. Axis value.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if axisEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetXAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                            double* axisValue);

/**
 * @brief Obtains the Y-axis value from {@link GamePad_AxisEvent}.
 * @param axisEvent Pointer to the {@link GamePad_AxisEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param axisValue Output parameter. Axis value.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if axisEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetYAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                            double* axisValue);

/**
 * @brief Obtains the Z-axis value from {@link GamePad_AxisEvent}.
 * @param axisEvent Pointer to the {@link GamePad_AxisEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param axisValue Output parameter. Axis value.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if axisEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetZAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                            double* axisValue);

/**
 * @brief Obtains the RZ-axis value from {@link GamePad_AxisEvent}.
 * @param axisEvent Pointer to the {@link GamePad_AxisEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param axisValue Output parameter. Axis value.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if axisEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetRZAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                             double* axisValue);

/**
 * @brief Obtains the HatX-axis value from {@link GamePad_AxisEvent}.
 * @param axisEvent Pointer to the {@link GamePad_AxisEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param axisValue Output parameter. Axis value.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if axisEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetHatXAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                               double* axisValue);

/**
 * @brief Obtains the HatY-axis value from {@link GamePad_AxisEvent}.
 * @param axisEvent Pointer to the {@link GamePad_AxisEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param axisValue Output parameter. Axis value.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if axisEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetHatYAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                               double* axisValue);

/**
 * @brief Obtains the Brake-axis value from {@link GamePad_AxisEvent}.
 * @param axisEvent Pointer to the {@link GamePad_AxisEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param axisValue Output parameter. Axis value.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if axisEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetBrakeAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                                double* axisValue);

/**
 * @brief Obtains the Gas-axis value from {@link GamePad_AxisEvent}.
 * @param axisEvent Pointer to the {@link GamePad_AxisEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param axisValue Output parameter. Axis value.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if axisEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetGasAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                              double* axisValue);

/**
 * @brief Obtains the action time from {@link GamePad_AxisEvent}.
 * @param axisEvent Pointer to the {@link GamePad_AxisEvent} instance.
 * The pointer cannot be null. Otherwise, an error code is returned.
 * @param actionTime Output parameter. Action time.
 * @return <ul><li>Returns {@link GAME_CONTROLLER_SUCCESS} if the execution is successful.</li>
 * <li>Returns {@link GAME_CONTROLLER_PARAM_ERROR} if axisEvent is null.</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetActionTime(const struct GamePad_AxisEvent* axisEvent,
                                                            int64_t* actionTime);

#ifdef __cplusplus
}
#endif

#endif //GAME_PAD_EVENT_H
/** @} */

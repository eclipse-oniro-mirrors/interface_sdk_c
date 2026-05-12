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
 * @brief 定义游戏手柄事件的接口。
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
 * @brief 此枚举定义手柄轴事件来源类型。
 * @since 21
 */
typedef enum GamePad_AxisSourceType {
    /**
     * 轴事件来源于方向按键DPAD。
     * @since 21
     */
    DPAD = 0,

    /**
     * 轴事件来源于LeftThumbstick。
     * @since 21
     */
    LEFT_THUMBSTICK = 1,

    /**
     * 轴事件来源于RightThumbstick。
     * @since 21
     */
    RIGHT_THUMBSTICK = 2,

    /**
     * 轴事件来源于LeftTrigger。
     * @since 21
     */
    LEFT_TRIGGER = 3,

    /**
     * 轴事件来源于RightTrigger。
     * @since 21
     */
    RIGHT_TRIGGER = 4,
} GamePad_AxisSourceType;

/**
 * @brief 此枚举定义手柄按键动作类型。
 * @since 21
 */
typedef enum GamePad_Button_ActionType {
    /**
     * 按键按下。
     * @since 21
     */
    DOWN = 0,

    /**
     * 按键抬起。
     * @since 21
     */
    UP = 1,
} GamePad_Button_ActionType;

/**
 * @brief 定义手柄按键事件。
 * @since 21
 */
typedef struct GamePad_ButtonEvent GamePad_ButtonEvent;

/**
 * @brief 定义手柄轴事件。
 * @since 21
 */
typedef struct GamePad_AxisEvent GamePad_AxisEvent;

/**
 * @brief 定义手柄按下的按键。
 * @since 21
 */
typedef struct GamePad_PressedButton GamePad_PressedButton;

/**
 * @brief 定义在按键事件注册监听接口中使用的回调函数。当玩家按下按键时，该回调函数将被调用。
 * @param buttonEvent 输出参数，手柄按键事件{@link GamePad_ButtonEvent}.
 * @since 21
 */
typedef void(* GamePad_ButtonInputMonitorCallback)(const struct GamePad_ButtonEvent* buttonEvent);

/**
 * @brief 定义在轴事件注册监听接口中使用的回调函数。当玩家操作摇杆时，该回调函数将被调用。
 * @param axisEvent 输出参数，手柄轴事件{@link GamePad_AxisEvent}.
 * @since 21
 */
typedef void(* GamePad_AxisInputMonitorCallback)(const struct GamePad_AxisEvent* axisEvent);

/**
 * @brief 从按键事件中获取设备ID。
 * @param buttonEvent 指针指向{@link GamePad_ButtonEvent}实例，不能为空，否则将返回错误码。
 * @param deviceId 输出参数，二级指针指向设备ID。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数buttonEvent或deviceId为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li>
 * <li>如果设备内存不足，返回{@link GAME_CONTROLLER_NO_MEMORY}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonEvent_GetDeviceId(const struct GamePad_ButtonEvent* buttonEvent,
                                                            char** deviceId);

/**
 * @brief 从按键事件中获取按键动作类型。
 * @param buttonEvent 指针指向{@link GamePad_ButtonEvent}实例，不能为空，否则将返回错误码。
 * @param actionType 输出参数，按键动作类型。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数buttonEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonEvent_GetButtonAction(const struct GamePad_ButtonEvent* buttonEvent,
                                                                GamePad_Button_ActionType* actionType);

/**
 * @brief 从按键事件中获取按键编码。
 * @param buttonEvent 指针指向{@link GamePad_ButtonEvent}实例，不能为空，否则将返回错误码。
 * @param code 输出参数，按键编码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数buttonEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonEvent_GetButtonCode(const struct GamePad_ButtonEvent* buttonEvent,
                                                              int32_t* code);

/**
 * @brief 从按键事件中获取按键名称。
 * @param buttonEvent 指针指向{@link GamePad_ButtonEvent}实例，不能为空，否则将返回错误码。
 * @param codeName 输出参数，二级指针指向按键名称。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数buttonEvent或codeName为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li>
 * <li>如果设备内存不足，返回{@link GAME_CONTROLLER_NO_MEMORY}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonEvent_GetButtonCodeName(const struct GamePad_ButtonEvent* buttonEvent,
                                                                  char** codeName);

/**
 * @brief 从按键事件中获取按下的按键数量。
 * @param buttonEvent 指针指向{@link GamePad_ButtonEvent}实例，不能为空，否则将返回错误码。
 * @param count 输出参数，按键数量。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数buttonEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_PressedButtons_GetCount(const struct GamePad_ButtonEvent* buttonEvent,
                                                            int32_t* count);

/**
 * @brief 从按键事件中获取指定索引的按键信息。
 * @param buttonEvent 指针指向{@link GamePad_ButtonEvent}实例，不能为空，否则将返回错误码。
 * @param index 指定按键索引。
 * @param pressedButton 输出参数，二级指针指向按下的按键。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数buttonEvent为null，或index小于0或大于等于按键总数，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_PressedButtons_GetButtonInfo(const struct GamePad_ButtonEvent* buttonEvent,
                                                                 const int32_t index,
                                                                 GamePad_PressedButton** pressedButton);

/**
 * @brief 销毁按下的按键实例。
 * @param pressedButton 二级指针指向{@link GamePad_PressedButton}实例，不能为空，否则将返回错误码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数pressedButton为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_DestroyPressedButton(GamePad_PressedButton** pressedButton);

/**
 * @brief 从按下的按键中获取按键编码。
 * @param pressedButton 指针指向{@link GamePad_PressedButton}实例，不能为空，否则将返回错误码。
 * @param code 输出参数，按键编码。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数pressedButton为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_PressedButton_GetButtonCode(const struct GamePad_PressedButton* pressedButton,
                                                                int32_t* code);

/**
 * @brief 从按下的按键中获取按键名称。
 * @param pressedButton 指针指向{@link GamePad_PressedButton}实例，不能为空，否则将返回错误码。
 * @param codeName 输出参数，二级指针指向按键名称。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数pressedButton或codeName为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li>
 * <li>如果设备内存不足，返回{@link GAME_CONTROLLER_NO_MEMORY}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_PressedButton_GetButtonCodeName(const struct GamePad_PressedButton* pressedButton,
                                                                    char** codeName);

/**
 * @brief 从按键事件中获取动作时间。
 * @param buttonEvent 指针指向{@link GamePad_ButtonEvent}实例，不能为空，否则将返回错误码。
 * @param actionTime 输出参数，动作时间。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数buttonEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_ButtonEvent_GetActionTime(const struct GamePad_ButtonEvent* buttonEvent,
                                                              int64_t* actionTime);

/**
 * @brief 从轴事件中获取设备ID。
 * @param axisEvent 指针指向{@link GamePad_AxisEvent}实例，不能为空，否则将返回错误码。
 * @param deviceId 输出参数，二级指针指向设备ID。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数axisEvent或deviceId为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li>
 * <li>如果设备内存不足，返回{@link GAME_CONTROLLER_NO_MEMORY}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetDeviceId(const struct GamePad_AxisEvent* axisEvent,
                                                          char** deviceId);

/**
 * @brief 从轴事件中获取轴类型。
 * @param axisEvent 指针指向{@link GamePad_AxisEvent}实例，不能为空，否则将返回错误码。
 * @param axisSourceType 输出参数，轴类型。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数axisEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetAxisSourceType(const struct GamePad_AxisEvent* axisEvent,
                                                                GamePad_AxisSourceType* axisSourceType);

/**
 * @brief 从轴事件中获取X轴的值。
 * @param axisEvent 指针指向{@link GamePad_AxisEvent}实例，不能为空，否则将返回错误码。
 * @param axisValue 输出参数，轴的值。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数axisEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetXAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                            double* axisValue);

/**
 * @brief 从轴事件中获取Y轴的值。
 * @param axisEvent 指针指向{@link GamePad_AxisEvent}实例，不能为空，否则将返回错误码。
 * @param axisValue 输出参数，轴的值。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数axisEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetYAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                            double* axisValue);

/**
 * @brief 从轴事件中获取Z轴的值。
 * @param axisEvent 指针指向{@link GamePad_AxisEvent}实例，不能为空，否则将返回错误码。
 * @param axisValue 输出参数，轴的值。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数axisEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetZAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                            double* axisValue);

/**
 * @brief 从轴事件中获取RZ轴的值。
 * @param axisEvent 指针指向{@link GamePad_AxisEvent}实例，不能为空，否则将返回错误码。
 * @param axisValue 输出参数，轴的值。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数axisEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetRZAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                             double* axisValue);

/**
 * @brief 从轴事件中获取HatX轴的值。
 * @param axisEvent 指针指向{@link GamePad_AxisEvent}实例，不能为空，否则将返回错误码。
 * @param axisValue 输出参数，轴的值。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数axisEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetHatXAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                               double* axisValue);

/**
 * @brief 从轴事件中获取HatY轴的值。
 * @param axisEvent 指针指向{@link GamePad_AxisEvent}实例，不能为空，否则将返回错误码。
 * @param axisValue 输出参数，轴的值。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数axisEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetHatYAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                               double* axisValue);

/**
 * @brief 从轴事件中获取Brake轴的值。
 * @param axisEvent 指针指向{@link GamePad_AxisEvent}实例，不能为空，否则将返回错误码。
 * @param axisValue 输出参数，轴的值。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数axisEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetBrakeAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                                double* axisValue);

/**
 * @brief 从轴事件中获取Gas轴的值。
 * @param axisEvent 指针指向{@link GamePad_AxisEvent}实例，不能为空，否则将返回错误码。
 * @param axisValue 输出参数，轴的值。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数axisEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetGasAxisValue(const struct GamePad_AxisEvent* axisEvent,
                                                              double* axisValue);

/**
 * @brief 从轴事件中获取动作时间。
 * @param axisEvent 指针指向{@link GamePad_AxisEvent}实例，不能为空，否则将返回错误码。
 * @param actionTime 输出参数，动作时间。
 * @return <ul><li>如果执行成功，返回{@link GAME_CONTROLLER_SUCCESS}。</li>
 * <li>如果参数axisEvent为null，返回{@link GAME_CONTROLLER_PARAM_ERROR}。</li></ul>
 * @since 21
 */
GameController_ErrorCode OH_GamePad_AxisEvent_GetActionTime(const struct GamePad_AxisEvent* axisEvent,
                                                            int64_t* actionTime);

#ifdef __cplusplus
}
#endif

#endif //GAME_PAD_EVENT_H
/** @} */

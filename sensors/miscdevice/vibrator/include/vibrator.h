/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @addtogroup Vibrator
 * @{
 *
 * @brief Provides APIs for vibrator services to access the vibrator driver.
 * @since 11
 */
/**
 * @file vibrator.h
 * @brief Declares the APIs for starting or stopping vibration. Two vibration modes are supported: simple continuous
 * vibration and custom vibration sequence. Simple continuous vibration is suitable for scenarios that require a single
 * vibration of a fixed duration, such as alarm clocks and timing reminders. You only need to specify the vibration
 * duration. Custom vibration sequences are suitable for scenarios that require complex vibration patterns, such as
 * notification reminders and game feedback. You can define a vibration sequence file to achieve rich tactile effects.
 * This helps you implement precise vibration control and improve user interaction experience.
 *
 * @kit SensorServiceKit
 * @library libohvibrator.z.so
 * @syscap SystemCapability.Sensors.MiscDevice
 * @since 11
 */

#ifndef VIBRATOR_H
#define VIBRATOR_H

#include "vibrator_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configures the vibrator to vibrate continuously for a given duration. After the API is successfully called,
 * the vibrator starts to vibrate immediately and automatically stops after the specified duration. This method is
 * applicable to scenarios where the vibrator needs to vibrate for a fixed duration, such as alarm clock, timing
 * reminder, game feedback, and message notification.
 *
 * @param duration Vibration duration, in milliseconds. It is used to control the duration of vibration. The value
 *     range is [1, 60000].
 * @param attribute Vibration attribute, which is used to configure the vibration strength and mode. For details, see
 *     {@link Vibrator_Attribute}.
 * @return If the operation is successful, **0** is returned. Otherwise, an error code in {@link Vibrator_ErrorCode} is
 *     returned. Common error codes include:
 *     <br>**201**: **PERMISSION_DENIED** (The permission verification failed);
 *     <br>**401**: **PARAMETER_ERROR** (The parameter check fails);
 *     <br>**801**: **UNSUPPORTED** (It is not supported on the device).
 * @permission ohos.permission.VIBRATE
 *
 * @since 11
 * @see {@link OH_Vibrator_Cancel} Stops the ongoing vibration.
 * @see {@link OH_Vibrator_PlayVibrationCustom} Configures the vibrator to vibrate with the custom sequence.
 */
int32_t OH_Vibrator_PlayVibration(int32_t duration, Vibrator_Attribute attribute);

/**
 * @brief Configures the vibrator to vibrate with the custom sequence. After the API is successfully called, the system
 * plays the vibration effect based on the custom vibration sequence. This method is applicable to scenarios that
 * require complex vibration patterns, such as notification reminders, games, and tactile feedback, to provide
 * personalized vibration experiences and enhance user immersion.
 *
 * @param fileDescription File descriptor of the custom vibration effect, which specifies the location and range of the
 *     file that contains the vibration sequence data. You can play a custom vibration effect by setting the file
 *     handle, offset address, and length. For details, see {@link Vibrator_FileDescription}.
 * @param vibrateAttribute Vibration attribute, which is used to control the strength and frequency of the custom
 *     vibration effect. For details, see {@link Vibrator_Attribute}.
 * @return If the operation is successful, **0** is returned.
 *     <br>Otherwise, an error code in {@link Vibrator_ErrorCode} is returned.
 *     <br>If the parameters are incorrect, check whether the values of **fileDescription** and **
 *     vibrateAttribute** are valid. If the device does not support vibration, check the device capability. For details
 *     about the error codes, see {@link Vibrator_ErrorCode}.
 * @permission ohos.permission.VIBRATE
 *
 * @since 11
 * @see {@link OH_Vibrator_Cancel} Stops the ongoing vibration.
 */
int32_t OH_Vibrator_PlayVibrationCustom(Vibrator_FileDescription fileDescription,
    Vibrator_Attribute vibrateAttribute);

/**
 * @brief Stops the vibration. After the API is successfully called, the ongoing vibration or custom vibration sequence
 * is stopped immediately. This method is applicable to scenarios where vibration needs to be stopped immediately, such
 * as when a user cancels an operation, switches between apps, or clears a system notification. It helps optimize user
 * experience and reduce device power consumption.
 *
 * @permission ohos.permission.VIBRATE
 * @return If the operation is successful, **0** is returned. Otherwise, an error code in {@link Vibrator_ErrorCode} is
 *     returned. For details about the possible causes and solutions, see the table below.
 * @permission ohos.permission.VIBRATE
 *
 * @since 11
 */
int32_t OH_Vibrator_Cancel();
#ifdef __cplusplus
}
#endif
/** @} */
#endif // endif VIBRATOR_H

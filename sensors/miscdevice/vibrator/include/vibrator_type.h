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
 * @brief Provides the enums, structs, and error codes used in the vibrator APIs.
 * @since 11
 */
/**
 * @file vibrator_type.h
 * @brief Declares the APIs for controlling vibration. This module supports multiple vibration scenarios, such as
 * alarms, ringtones, notifications, communication, touch, media, physical feedback, and simulated reality. By setting
 * vibration priorities, you can meet vibration requirements in different scenarios, improving user interaction
 * experience and device usability.
 *
 * @kit SensorServiceKit
 * @library libohvibrator.z.so
 * @syscap SystemCapability.Sensors.MiscDevice
 * @since 11
 */


#ifndef VIBRATOR_TYPE_H
#define VIBRATOR_TYPE_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Enumerates the error codes. If an exception occurs during use of vibration APIs, the corresponding error code
* is returned.
*
* @since 11
*/
typedef enum Vibrator_ErrorCode : int32_t {
    /**
     * Permission verification failed. Check whether you have requested the required permission
	 * (for example, **ohos.permission.VIBRATE**).
     */
    PERMISSION_DENIED = 201,
    /**
     * Parameter check failed. For example, a mandatory parameter is not passed in, or the parameter type passed
	 * in is incorrect.
     */
    PARAMETER_ERROR = 401,
    /**
     * The device does not support the API. This error code is reported when the device supports the SysCap but
	 * does not support a specific API.
     */
    UNSUPPORTED = 801,
    /**
     * Device operation failed. Check the device status and parameter configuration.
     */
    DEVICE_OPERATION_FAILED = 14600101,
} Vibrator_ErrorCode;

/**
 * @brief Enumerates the vibration priorities in different scenarios. A vibration with a higher priority interrupts a
 * vibration with a lower priority. Suggestions: Select a proper priority based on the application scenario. In
 * scenarios where continuous vibration is required, keep the priority consistent to avoid performance loss caused by
 * frequently switching priorities. It is recommended that a higher priority be used for physical feedback and touch
 * vibrations to ensure timely response.
 *
 * @since 11
 */
typedef enum Vibrator_Usage {
	/**
     * Unknown scenario, with the lowest priority. Choose this option when the specific application scenario
	 * cannot be determined. In this case, the system complies with the default policy.
     */
    VIBRATOR_USAGE_UNKNOWN = 0,
	/**
     * Alarm. Choose this option in scenarios such as alarm clock and countdown reminders. The vibration is
	 * strong and lasts for a long time.
     */
    VIBRATOR_USAGE_ALARM = 1,
	/**
     * Ringtone. Choose this option for incoming calls. The vibration mode is cyclic vibration, which helps
	 * users answer calls in a timely manner.
     */
    VIBRATOR_USAGE_RING = 2,
	/**
     * Notification. Choose this option in scenarios such as system notifications and app messages.
	 * The vibration is short, prompting users to view the notifications.
     */
    VIBRATOR_USAGE_NOTIFICATION = 3,
	/**
     * Communication. Choose this option in communication scenarios such as calls, instant messaging, and SMS
	 * messages. The vibration mode is one-shot vibration.
     */
    VIBRATOR_USAGE_COMMUNICATION = 4,
	/**
     * Touch. Choose this option in feedback scenarios such as screen touches and key operations. The vibration
	 * is extremely short, providing a sense of operation confirmation.
     */
    VIBRATOR_USAGE_TOUCH = 5,
	/**
     * Media. Choose this option in media app scenarios such as music and videos. The vibration is synchronized
	 * with the media content to enhance the immersive experience.
     */
    VIBRATOR_USAGE_MEDIA = 6,
	/**
     * Physical feedback. Choose this option in scenarios that require physical feedback, such as games and
	 * simulations. It provides physical interaction experiences such as physical key feedback and tactile force
	 * feedback. The vibration mode can be customized to simulate real touch sensations.
     */
    VIBRATOR_USAGE_PHYSICAL_FEEDBACK = 7,
	/**
     * Simulated reality. Choose this option for tactile feedback in immersive scenarios such as VR/AR. The
	 * vibration intensity and mode are precisely controllable to provide realistic environmental feedback.
     */
    VIBRATOR_USAGE_SIMULATED_REALITY = 8,
    VIBRATOR_USAGE_MAX
} Vibrator_Usage;

/**
 * @brief The **Vibrator_Attribute** struct is used to describe the attributes of the vibrator. You can use this struct
 * to specify the vibrator ID and vibration scenario. For details about the application scenarios and implementation
 * mechanism, see the {@link Vibrator} module documentation.
 *
 * @since 11
 */
typedef struct Vibrator_Attribute {
    /**
	 * Vibrator ID. Its value is obtained through the system API. This is the ID of the vibrator to be
	 * operated. Different IDs correspond to different vibrators on the device. The value range is
	 * [0, Maximum number of supported vibrators – 1].
	 */
    int32_t vibratorId;
    /**
	 * Vibration scenario. This parameter specifies the application scenario of the vibrator. Different
	 * scenarios correspond to different vibration modes. For example, notifications, buttons, and alarm clocks have
	 * their own vibration effects. For details about the options, see the **Vibrator_Usage** enumeration.
	 */
    Vibrator_Usage usage;
} Vibrator_Attribute;

/**
 * @brief Defines the vibration file description. This method is used to describe the file information of a custom
 * vibration pattern. You can use a custom vibration file to implement precise vibration control.
 *
 * @since 11
 */
typedef struct Vibrator_FileDescription {
    /**
	 * File handle of the customized vibration sequence, which must point to a valid file that contains the
	 * vibration sequence data. Before using this API, you must open the file and obtain the file descriptor using
	 * the file operation API such as **open**. The file descriptor must be valid and readable. It cannot be a
	 * negative value or an invalid handle.
	 */
    int32_t fd;
    /**
	 * Offset address of the custom vibration sequence, in bytes. This parameter specifies the start position
	 * for reading the vibration sequence from the file. The value of **offset** must be greater than or equal to 0
	 * and less than the file size. If **offset** is 0, the file is read from the beginning. If **offset** is greater
	 * than 0, the first **offset** bytes are skipped. If the value of **offset** exceeds the file size, undefined
	 * behavior may occur.
	 */
    int64_t offset;
    /**
	 * Total length of the custom vibration sequence, in bytes. This parameter specifies the number of bytes
	 * to read from the position specified by **offset**. The value of **length** must be greater than 0, and the sum
	 * of **offset** and **length** cannot exceed the file size. If the value of **length** exceeds the remaining
	 * file size, the read operation may fail or undefined behavior may occur.
	 */
    int64_t length;
} Vibrator_FileDescription;
#ifdef __cplusplus
}
#endif
/** @} */
#endif  // endif VIBRATOR_TYPE_H

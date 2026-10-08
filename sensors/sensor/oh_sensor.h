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
 * @addtogroup Sensor
 * @{
 *
 * @brief Provides APIs to use common sensor features. For example, you can call the APIs to obtain sensor information
 * and subscribe to or unsubscribe from sensor data.
 * @since 11
 */
/**
 * @file oh_sensor.h
 * @brief Declares the APIs for the sensor service, including obtaining sensor information and subscribing to and
 * unsubscribing from sensor data.
 *
 * @kit SensorServiceKit
 * @library libohsensor.so
 * @syscap SystemCapability.Sensors.Sensor
 * @since 11
 */

#ifndef OH_SENSOR_H
#define OH_SENSOR_H

#include "oh_sensor_type.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Obtains information about all sensors on the device. Use scenarios: When an app is launched, it queries the
 * list of sensors supported by the device, displays or hides related functions based on the sensor capabilities, and
 * selects appropriate sensors for subscription. After the call is successful, the sensor information array is returned
 * through the pointer **infos**, and the number of sensors is returned through the pointer **count**.
 *
 * @param infos Double pointers to the information about all sensors on the device. This is an output parameter. The
 *     caller does not need to allocate memory in advance. Memory is allocated inside the function. After using the
 *     memory, the caller needs to call the corresponding deallocation function to free the memory. After the function
 *     is called, **\*infos** points to the sensor information array. For details, see {@link Sensor_Info}.
 *     This parameter must not be null.
 * @param count Pointer to the number of sensors on the device. This is an output parameter. The caller only needs to
 *     pass a pointer to a **uint32_t** variable. After the function is called, the variable pointed to by **count**
 *     will be set to the number of sensors. This parameter must not be null.
 * @return Enumerated values of {@link Sensor_Result}:
 *     <br>**SENSOR_SUCCESS**: The sensor information is successfully obtained.
 *     <br>{@link SENSOR_PARAMETER_ERROR}: The parameter verification fails. For example, the passed **infos** or **
 *     count** is a null pointer.
 *     <br>{@link SENSOR_SERVICE_EXCEPTION}: The sensor service is abnormal. For example, the sensor service is not
 *     started or an internal error occurs.
 *     <br>For other possible error codes, refer to {@link Sensor_Result}.
 * @since 11
 */
Sensor_Result OH_Sensor_GetInfos(Sensor_Info **infos, uint32_t *count);

/**
 * @brief Subscribes to sensor data. The system will report sensor data to the subscriber at the specified frequency.
 * The subscription is implemented through the event callback mechanism. Use scenarios: Health and fitness apps monitor
 * users' step count and heart rate in real time. Game apps use the accelerometer to implement gravity sensing.
 * Navigation apps use the gyroscope sensor to assist in positioning.
 * <br>Permission description: To subscribe to data of acceleration sensors, request the **ohos.permission.
 * ACCELEROMETER** permission. To subscribe to data of gyroscope sensors, request the **ohos.permission.GYROSCOPE**
 * permission. To subscribe to data of pedometer-related sensors, request the **ohos.permission.ACTIVITY_MOTION**
 * permission. To subscribe to data of health-related sensors, such as heart rate sensors, request the **ohos.
 * permission.READ_HEALTH_DATA** permission. Otherwise, the subscription fails. You do not need to request any
 * permission to subscribe to data of other types of sensors.
 *
 * @param id Pointer to the sensor subscription ID. This is an input parameter. This is the ID of the sensor type to be
 *     subscribed to. Different sensor types correspond to different IDs, such as the acceleration sensor, gyroscope
 *     sensor, and heart rate sensor. For details, see {@link Sensor_SubscriptionId}. The caller must ensure that the
 *     data pointed to by the ID is valid. This parameter must not be null.
 * @param attribute Pointer to the subscription attribute, in Hz, which is used to specify the data reporting
 *     frequency. This is an input parameter. The caller needs to create a **Sensor_SubscriptionAttribute** object,
 *     set the required data reporting frequency, and then pass the object to this function. The frequency value must
 *     be within the range supported by the sensor. The specific range varies depending on the sensor type. High
 *     frequencies (above 100 Hz) are suitable for scenarios that require real-time data monitoring (such as gaming),
 *     while low frequencies (1–10 Hz) are suitable for power-saving scenarios where high-frequency data is not
 *     required (such as background monitoring). Select a proper data reporting frequency based on your requirements.
 *     If the data reporting frequency is not set, the default value will be used.
 *     For details, see {@link Sensor_SubscriptionAttribute}. This parameter must not be null.
 * @param subscriber Pointer to the subscriber information, including the callback used to report sensor data. This is
 *     an input parameter. Before calling this function, the caller must set the callback function. The system will
 *     call the callback function at the frequency specified in the subscription attributes. Before the subscription
 *     is canceled, the callback function must remain valid and should not be modified or released. For details,
 *     see {@link Sensor_Subscriber}. This parameter must not be null. Note: The callback function is executed
 *     in the sensor service thread. Do not perform time-consuming operations or block the call in the callback
 *     function. Otherwise, the real-time performance of sensor data reporting may be affected.
 * @return Enumerated values of {@link Sensor_Result}:
 *     <br>**SENSOR_SUCCESS**: The sensor data is successfully subscribed to.
 *     <br>{@link SENSOR_PERMISSION_DENIED}: The permission verification fails. This error is returned when the
 *     permission required for subscribing to the sensor is missing. For details about the permissions required for
 *     different sensors, see the function description. Request the permissions and try again.
 *     <br>{@link SENSOR_PARAMETER_ERROR}: The parameter verification fails. For example, the passed **id**, **
 *     attribute**, or **subscriber** is a null pointer.
 *     <br>{@link SENSOR_SERVICE_EXCEPTION}: The sensor service is abnormal. For example, the sensor service is not
 *     started or an internal error occurs.
 *     <br>For other possible error codes, refer to {@link Sensor_Result}.
 * @permission ohos.permission.ACCELEROMETER or ohos.permission.GYROSCOPE or
 *     ohos.permission.ACTIVITY_MOTION or ohos.permission.READ_HEALTH_DATA
 * @since 11
 */
Sensor_Result OH_Sensor_Subscribe(const Sensor_SubscriptionId *id,
    const Sensor_SubscriptionAttribute *attribute, const Sensor_Subscriber *subscriber);

/**
 * @brief Unsubscribes from sensor data. This operation will stop the reporting of sensor data.
 * <br>To unsubscribe from data of acceleration sensors, request the **ohos.permission.ACCELEROMETER** permission. To
 * unsubscribe from data of gyroscope sensors, request the **ohos.permission.GYROSCOPE** permission. To unsubscribe
 * from data of pedometer-related sensors, request the **ohos.permission.ACTIVITY_MOTION** permission. To unsubscribe
 * from data of health-related sensors (such as the heart rate sensor), request the **ohos.permission.READ_HEALTH_DATA**
 * permission. Otherwise, the unsubscription fails. You do not need to request any permission to unsubscribe from data
 * of other types of sensors.
 *
 * @param id Pointer to the sensor subscription ID. This is an input parameter. This is the ID of the subscription to
 *     be canceled. It must be the same as the subscription ID used when **OH_Sensor_Subscribe** is called.
 *     Otherwise, **SENSOR_PARAMETER_ERROR** may be returned. Different sensor types correspond to different IDs,
 *     such as the acceleration sensor, gyroscope sensor, and heart rate sensor. For details,
 *     see {@link Sensor_SubscriptionId}. This parameter must not be null.
 * @param subscriber Pointer to the subscriber information, including the callback used to report sensor data. This is
 *     an input parameter. This subscriber must be the same as the one when **OH_Sensor_Subscribe** is called.
 *     Otherwise, **SENSOR_PARAMETER_ERROR** may be returned. After the subscription is canceled successfully, the
 *     callback function will no longer be called. For details, see {@link Sensor_Subscriber}.
 *     This parameter must not be null.
 * @return Enumerated values of {@link Sensor_Result}:
 *     <br>**SENSOR_SUCCESS**: The subscription to sensor data is successfully canceled.
 *     <br>{@link SENSOR_PERMISSION_DENIED}: The permission verification fails. This error is returned when the
 *     permission required for unsubscribing from the sensor is missing. For details about the permissions required for
 *     different sensors, see the function description. Request the permissions and try again.
 *     <br>{@link SENSOR_PARAMETER_ERROR}: The parameter verification fails. For example, the passed **id** or **
 *     subscriber** is a null pointer.
 *     <br>{@link SENSOR_SERVICE_EXCEPTION}: The sensor service is abnormal. For example, the sensor service is not
 *     started or an internal error occurs.
 *     <br>For other possible error codes, refer to {@link Sensor_Result}.
 * @permission ohos.permission.ACCELEROMETER or ohos.permission.GYROSCOPE or
 *     ohos.permission.ACTIVITY_MOTION or ohos.permission.READ_HEALTH_DATA
 *
 * @since 11
 */
Sensor_Result OH_Sensor_Unsubscribe(const Sensor_SubscriptionId *id, const Sensor_Subscriber *subscriber);
#ifdef __cplusplus
}
#endif
/** @} */
#endif // OH_SENSOR_H

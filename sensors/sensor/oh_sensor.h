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
 * @brief The **oh_sensor.h** file declares the APIs for operating sensors, including obtaining sensor information and
 * subscribing to and unsubscribing from sensor data.
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
 * @brief Obtains information about all sensors on the device.
 *
 * @param infos Double pointer to the information about all sensors on the device. For details, see {@link Sensor_Info}.
 * @param count Pointer to the number of sensors on the device.
 * @return **SENSOR_SUCCESS** if the operation is successful; an error code defined in {@link Sensor_Result} otherwise.
 * The error code can be:
 * - {@link SENSOR_PARAMETER_ERROR} if the parameter verification fails. For example, the parameter is invalid or the
 * parameter type is incorrect.
 * - {@link SENSOR_SERVICE_EXCEPTION} if the sensor service is abnormal.
 * @since 11
 */
Sensor_Result OH_Sensor_GetInfos(Sensor_Info **infos, uint32_t *count);

/**
 * @brief Subscribes to sensor data. The system will report sensor data to the subscriber at the specified frequency.
 * To subscribe to data of acceleration sensors, request the **ohos.permission.ACCELEROMETER** permission. To subscribe
 * to data of gyroscope sensors, request the **ohos.permission.GYROSCOPE** permission. To subscribe to data of
 * pedometer-related sensors, request the **ohos.permission.ACTIVITY_MOTION** permission. To subscribe to data of
 * health-related sensors, such as heart rate sensors, request the **ohos.permission.READ_HEALTH_DATA** permission.
 * Otherwise, the subscription fails. You do not need to request any permission to subscribe to data of other types of
 * sensors.
 *
 * @param id Pointer to the sensor subscription ID. For details, see {@link Sensor_SubscriptionId}.
 * @param attribute Pointer to the subscription attribute, which is used to specify the data reporting frequency. For
 * details, see {@link Sensor_SubscriptionAttribute}.
 * @param subscriber Pointer to the subscriber information, which is used by the callback function to report sensor
 * data. For details, see {@link Sensor_Subscriber}.
 * @return **SENSOR_SUCCESS** if the operation is successful; an error code defined in {@link Sensor_Result} otherwise.
 * The error code can be:
 * - {@link SENSOR_PERMISSION_DENIED} if the permission verification fails.
 * - {@link SENSOR_PARAMETER_ERROR} if the parameter verification fails. For example, the parameter is invalid or the
 * parameter type is incorrect.
 * - {@link SENSOR_SERVICE_EXCEPTION} if the sensor service is abnormal.
 * @permission ohos.permission.ACCELEROMETER or ohos.permission.GYROSCOPE or
 * ohos.permission.ACTIVITY_MOTION or ohos.permission.READ_HEALTH_DATA
 * @since 11
 */
Sensor_Result OH_Sensor_Subscribe(const Sensor_SubscriptionId *id,
    const Sensor_SubscriptionAttribute *attribute, const Sensor_Subscriber *subscriber);

/**
 * @brief Unsubscribes from sensor data. To unsubscribe from data of acceleration sensors, request the **ohos.
 * permission.ACCELEROMETER** permission. To unsubscribe from data of gyroscope sensors, request the **ohos.permission.
 * GYROSCOPE** permission. To unsubscribe from data of pedometer-related sensors, request the **ohos.permission.
 * ACTIVITY_MOTION** permission. To unsubscribe from data of health-related sensors, request the **ohos.permission.
 * READ_HEALTH_DATA** permission. Otherwise, the unsubscription fails. You do not need to request any permission to
 * unsubscribe from data of other types of sensors.
 *
 * @param id Pointer to the sensor subscription ID. For details, see {@link Sensor_SubscriptionId}.
 * @param subscriber Pointer to the subscriber information, which is used by the callback function to report sensor
 * data. For details, see {@link Sensor_Subscriber}.
 * @return **SENSOR_SUCCESS** if the operation is successful; an error code defined in {@link Sensor_Result} otherwise.
 * The error code can be:
 * - {@link SENSOR_PERMISSION_DENIED} if the permission verification fails.
 * - {@link SENSOR_PARAMETER_ERROR} if the parameter verification fails. For example, the parameter is invalid or the
 * parameter type is incorrect.
 * - {@link SENSOR_SERVICE_EXCEPTION} if the sensor service is abnormal.
 * @permission ohos.permission.ACCELEROMETER or ohos.permission.GYROSCOPE or
 * ohos.permission.ACTIVITY_MOTION or ohos.permission.READ_HEALTH_DATA
 *
 * @since 11
 */
Sensor_Result OH_Sensor_Unsubscribe(const Sensor_SubscriptionId *id, const Sensor_Subscriber *subscriber);
#ifdef __cplusplus
}
#endif
/** @} */
#endif // OH_SENSOR_H

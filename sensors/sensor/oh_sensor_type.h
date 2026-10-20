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
 * @brief Provides APIs to define common sensor attributes.
 *
 * @since 11
 */
/**
 * @file oh_sensor_type.h
 * @brief Declares the common sensor attributes.
 *
 * @kit SensorServiceKit
 * @library libohsensor.so
 * @syscap SystemCapability.Sensors.Sensor
 * @since 11
 */

#ifndef OH_SENSOR_TYPE_H
#define OH_SENSOR_TYPE_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the sensor types.
 *
 * @since 11
 */
typedef enum Sensor_Type {
    /**
     * Acceleration sensor.
     * @since 11
     */
    SENSOR_TYPE_ACCELEROMETER = 1,
    /**
     * Gyroscope sensor.
     * @since 11
     */
    SENSOR_TYPE_GYROSCOPE = 2,
    /**
     * Ambient light sensor.
     * @since 11
     */
    SENSOR_TYPE_AMBIENT_LIGHT = 5,
    /**
     * Magnetic field sensor.
     * @since 11
     */
    SENSOR_TYPE_MAGNETIC_FIELD = 6,
    /**
     * Barometer sensor.
     * @since 11
     */
    SENSOR_TYPE_BAROMETER = 8,
    /**
     * Hall effect sensor.
     * @since 11
     */
    SENSOR_TYPE_HALL = 10,
    /**
     * Proximity sensor.
     * @since 11
     */
    SENSOR_TYPE_PROXIMITY = 12,
    /**
     * Orientation sensor.
     * @since 11
     */
    SENSOR_TYPE_ORIENTATION = 256,
    /**
     * Gravity sensor.
     * @since 11
     */
    SENSOR_TYPE_GRAVITY = 257,
    /**
     * Linear acceleration sensor.
     * @since 13
     */
    SENSOR_TYPE_LINEAR_ACCELERATION = 258,
    /**
     * Rotation vector sensor.
     * @since 11
     */
    SENSOR_TYPE_ROTATION_VECTOR = 259,
    /**
     * Game rotation vector sensor.
     * @since 13
     */
    SENSOR_TYPE_GAME_ROTATION_VECTOR = 262,
    /**
     * Pedometer detection sensor.
     * @since 11
     */
    SENSOR_TYPE_PEDOMETER_DETECTION = 265,
    /**
     * Pedometer sensor.
     * @since 11
     */
    SENSOR_TYPE_PEDOMETER = 266,
    /**
     * Heart rate sensor.
     * @since 11
     */
    SENSOR_TYPE_HEART_RATE = 278,
} Sensor_Type;

/**
 * @brief Enumerates the sensor result codes.
 *
 * @since 11
 */
typedef enum Sensor_Result {
    /**
     * Operation success.
	 * @since 11
     */
    SENSOR_SUCCESS = 0,
    /**
     * Permission verification failed. Possible causes: The app does not have the required sensor permission, the
     * permission request is rejected, or the permission level is insufficient. Solution: Check whether the required
     * sensor permission has been requested in the app configuration file. Ensure that the permission is correctly
     * requested and obtained during app running.
	 * @since 11
     */
    SENSOR_PERMISSION_DENIED = 201,
    /**
     * An error occurs during parameter verification. Possible causes: The parameter is empty, the parameter value is
     * out of the valid range, the parameter type does not match, or a mandatory parameter is missing. Solution: Check
     * whether the input parameters are complete, meet the type requirements, and are within the valid range based on
     * the parameter description of the specific function, and modify the parameter values if necessary.
	 * @since 11
     */
    SENSOR_PARAMETER_ERROR = 401,
    /**
     * The sensor service is abnormal. Possible causes: The sensor service is not started or has crashed, the device
     * does not support the specified sensor, or the system resources are insufficient. Solution: Check whether the
     * device supports the required sensor and ensure that the system resources are sufficient. If necessary, restart
     * the device or reinitialize the sensor service.
	 * @since 11
     */
    SENSOR_SERVICE_EXCEPTION = 14500101,
} Sensor_Result;

/**
 * @brief Enumerates the accuracy levels of data reported by a sensor.
 *
 * @since 11
 */
typedef enum Sensor_Accuracy {
    /**
     * The sensor data is unreliable. It is possible that the sensor does not contact with the device to measure.
     * @since 11
     */
    SENSOR_ACCURACY_UNRELIABLE = 0,
    /**
     * The sensor data is at a low accuracy level. The data must be calibrated based on the environment before being
     * used.
	 * @since 11
     */
    SENSOR_ACCURACY_LOW = 1,
    /**
     * The sensor data is at a medium accuracy level. You are advised to calibrate the data based on the environment
     * before using it.
	 * @since 11
     */
    SENSOR_ACCURACY_MEDIUM = 2,
    /**
     * The sensor data is at a high accuracy level. The data can be used directly.
	 * @since 11
     */
    SENSOR_ACCURACY_HIGH = 3
} Sensor_Accuracy;

/**
 * @brief Defines a struct for the sensor information, which is used to store the basic attributes and data of a sensor,
 * including key fields such as the sensor type, version, and ID. You can use this struct to obtain the complete
 * description of a sensor, which is used for sensor initialization and data query.
 *
 * @since 11
 */
typedef struct Sensor_Info Sensor_Info;

/**
 * @brief Creates an instance array using a given number. For details, see {@link Sensor_Info}. After the instance is
 * successfully created, a pointer to the array of **count** **Sensor_Info** instances is returned.
 * <br>After the instance array created by calling this function is used, you must call **OH_Sensor_DestroyInfos()** to
 * destroy the instance array and reclaim the memory. Otherwise, resource leak may occur.
 *
 * @param count Number of instances to be created. For details, see {@link Sensor_Info}.
 * @return Double pointer to the {@link Sensor_Info} instance array if the operation is successful. The array contains *
 *     *count** **Sensor_Info** instances for storing sensor information. Otherwise, **NULL** is returned.
 * @since 11
 */
Sensor_Info **OH_Sensor_CreateInfos(uint32_t count);

/**
 * @brief Destroys the instance array and reclaims the memory. For details, see {@link Sensor_Info}. After this API is
 * successfully called, the memory occupied by the instance array is released, and the **sensors** pointer and all **
 * Sensor_Info** instances to which the pointer points can no longer be used.
 *
 * @param sensors Double pointer to the {@link Sensor_Info} instance array.
 * @param count Number of {@link Sensor_Info} instances to be destroyed.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that all
 *     instances have been successfully destroyed. Otherwise, the error code defined in {@link Sensor_Result} is
 *     returned.
 * @since 11
 */
int32_t OH_Sensor_DestroyInfos(Sensor_Info **sensors, uint32_t count);

/**
 * @brief Obtains the sensor name. After the sensor name is obtained, the **sensorName** parameter is filled with the
 * sensor name string, and the **length** parameter returns the length of the string (including the terminator).
 *
 * @param sensor Pointer to the sensor information.
 * @param sensorName Pointer to the sensor data.
 * @param length Pointer to the length, in bytes. Before the call, set this parameter to the buffer size. After the
 *     call, the actual name length is returned.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     sensor name has been successfully obtained. Otherwise, the error code defined in {@link Sensor_Result} is
 *     returned.
 * @since 11
 */
int32_t OH_SensorInfo_GetName(Sensor_Info* sensor, char *sensorName, uint32_t *length);

/**
 * @brief Obtains the sensor's vendor name. After the vendor name is obtained, the **vendorName** parameter is filled
 * with the sensor vendor name string, and the **length** parameter returns the length of the string (including the
 * terminator).
 *
 * @param sensor Pointer to the sensor information.
 * @param vendorName Pointer to the vendor name.
 * @param length Pointer to the length, in bytes. Before the call, set this parameter to the buffer size. After the
 *     call, the actual vendor name length is returned.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     vendor sensor name has been successfully obtained. Otherwise, the error code defined in {@link Sensor_Result} is
 *     returned.
 * @since 11
 */
int32_t OH_SensorInfo_GetVendorName(Sensor_Info* sensor, char *vendorName, uint32_t *length);

/**
 * @brief Obtains the {@link Sensor_Type}. After the sensor type is obtained, the **sensorType** parameter is filled
 * with the sensor type value.
 *
 * @param sensor Pointer to the sensor information.
 * @param sensorType Pointer to the sensor type.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     sensor type has been successfully obtained. Otherwise, the error code defined in {@link Sensor_Result} is
 *     returned.
 * @since 11
 */
int32_t OH_SensorInfo_GetType(Sensor_Info* sensor, Sensor_Type *sensorType);

/**
 * @brief Obtains the sensor resolution. After the sensor resolution is obtained, the **resolution** parameter is
 * filled with the sensor resolution value.
 *
 * @param sensor Pointer to the sensor information.
 * @param resolution Pointer to the sensor resolution.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     sensor resolution has been successfully obtained. Otherwise, the error code defined in {@link Sensor_Result} is
 *     returned.
 * @since 11
 */
int32_t OH_SensorInfo_GetResolution(Sensor_Info* sensor, float *resolution);

/**
 * @brief Obtains the minimum data reporting interval of a sensor. After the interval is obtained, the **
 * minSamplingInterval** parameter is filled with the minimum data reporting interval of the sensor, in nanoseconds.
 *
 * @param sensor Pointer to the sensor information.
 * @param minSamplingInterval Pointer to the minimum data reporting interval, in nanoseconds. This value indicates the
 *     fastest data reporting interval supported by the sensor. If the interval is set to a value smaller than this
 *     value, data may be lost or performance may deteriorate.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     minimum data reporting interval has been successfully obtained. Otherwise, the error code defined in
 *     {@link Sensor_Result} is returned.
 * @since 11
 */
int32_t OH_SensorInfo_GetMinSamplingInterval(Sensor_Info* sensor, int64_t *minSamplingInterval);

/**
 * @brief Obtains the maximum data reporting interval of a sensor. After the interval is obtained, the **
 * maxSamplingInterval** parameter is filled with the maximum data reporting interval of the sensor, in nanoseconds.
 *
 * @param sensor Pointer to the sensor information.
 * @param maxSamplingInterval Pointer to the maximum data reporting interval, in nanoseconds. This value indicates the
 *     slowest data reporting interval supported by the sensor. If the interval is set to a value greater than this
 *     value, data may not be updated in a timely manner.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     maximum data reporting interval has been successfully obtained. Otherwise, the error code defined in
 *     {@link Sensor_Result} is returned.
 * @since 11
 */
int32_t OH_SensorInfo_GetMaxSamplingInterval(Sensor_Info* sensor, int64_t *maxSamplingInterval);

/**
 * @brief Defines a struct for the sensor event, including the sensor type, timestamp, and sensor data.
 *
 * @since 11
 */
typedef struct Sensor_Event Sensor_Event;

/**
 * @brief Obtains the sensor type.
 *
 * @param sensorEvent Pointer to the sensor data information.
 * @param sensorType Pointer to the sensor type.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     sensor event type has been successfully obtained. Otherwise, the error code defined in {@link Sensor_Result} is
 *     returned.
 * @since 11
 */
int32_t OH_SensorEvent_GetType(Sensor_Event* sensorEvent, Sensor_Type *sensorType);

/**
 * @brief Obtains the timestamp of sensor data.
 *
 * @param sensorEvent Pointer to the sensor data information.
 * @param timestamp Pointer to the timestamp, in nanoseconds. It indicates the time when the sensor data is collected,
 *     that is, the number of nanoseconds since the system startup.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     timestamp has been successfully obtained. Otherwise, the error code defined in {@link Sensor_Result} is returned.
 * @since 11
 */
int32_t OH_SensorEvent_GetTimestamp(Sensor_Event* sensorEvent, int64_t *timestamp);

/**
 * @brief Obtains the accuracy of sensor data.
 *
 * @param sensorEvent Pointer to the sensor data information.
 * @param accuracy Pointer to the sensor data accuracy level.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     sensor data accuracy has been successfully obtained. Otherwise, the error code defined in {@link Sensor_Result}
 *     is returned.
 * @since 11
 */
int32_t OH_SensorEvent_GetAccuracy(Sensor_Event* sensorEvent, Sensor_Accuracy *accuracy);

/**
 * @brief Obtains sensor data. The data length and content depend on the sensor type. The format of the sensor data
 * reported is as follows:
 *
 * | Type| Data Element and Description|
 * | --- | --- |
 * | SENSOR_TYPE_ACCELEROMETER | **data[0]**, **data[1]**, and **data[2]** indicate the acceleration around the x, y,
 * and z axes of a device, respectively, in m/s².|
 * | SENSOR_TYPE_GYROSCOPE | **data[0]**, **data[1]**, and **data[2]** indicate the angular velocity of rotation around
 * the x, y, and z axes of a device, respectively, in rad/s.|
 * | SENSOR_TYPE_AMBIENT_LIGHT | **data[0]** indicates the ambient light intensity, in lux.<br> Two additional data
 * values are returned since API version 12. **data[1]** indicates the color temperature, in kelvin (K),
 * and **data[2]** indicates the infrared luminance, in cd/m².|
 * | SENSOR_TYPE_MAGNETIC_FIELD | **data[0]**, **data[1]**, and **data[2]** indicate the magnetic field strength around
 * the x, y, and z axes of a device, respectively, in μT.|
 * | SENSOR_TYPE_BAROMETER | **data[0]** indicates the atmospheric pressure, in hPa.|
 * | SENSOR_TYPE_HALL | **data[0]** indicates the opening/closing state of the flip cover. The value **0** means that
 * the flip cover is opened, and a value greater than 0 means that the flip cover is closed.|
 * | SENSOR_TYPE_PROXIMITY | **data[0]** indicates the approaching state. The value **0** means the two objects are
 * close to each other, and a value greater than 0 means that they are far away from each other.|
 * | SENSOR_TYPE_ORIENTATION | **data[0]**, **data[1]**, and **data[2]** indicate the rotation angles of a device
 * around the z, x, and y axes, respectively, in degree.|
 * | SENSOR_TYPE_GRAVITY | **data[0]**, **data[1]**, and **data[2]** indicate the gravitational acceleration around the
 * x, y, and z axes of a device, respectively, in m/s².|
 * | SENSOR_TYPE_ROTATION_VECTOR | **data[0]**, **data[1]**, and **data[2]** indicate the rotation angles of a device
 * around the x, y, and z axes, respectively, in degree. data[3] indicates the rotation vector.|
 * | SENSOR_TYPE_PEDOMETER_DETECTION | **data[0]** indicates the pedometer detection status. The value **1** means that
 * the number of detected steps changes.|
 * | SENSOR_TYPE_PEDOMETER | **data[0]** indicates the number of steps a user has walked.|
 * | SENSOR_TYPE_HEART_RATE | **data[0]** indicates the heart rate value.|
 * | SENSOR_TYPE_LINEAR_ACCELERATION | This parameter is available since API version 13. **data[0]**, **data[1]**,
 * and **data[2]** indicate the linear acceleration around the x, y, and z axes of a device, respectively, in m/s².|
 * | SENSOR_TYPE_GAME_ROTATION_VECTOR | This parameter is available since API version 13. **data[0]**, **data[1]**,
 * and **data[2]** indicate the rotation angles of a device around the x, y, and z axes, respectively, in degree.
 * **data[3]** indicates the rotation vector.|
 *
 * @param sensorEvent Pointer to the sensor data information.
 * @param data Pointer to the sensor data array. This is an output parameter. The data format depends on the sensor
 *     type. For details, see the function description.
 * @param length Length of the data array, which indicates the number of valid data records in the data array. This is
 *     an output parameter.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     sensor data has been successfully obtained. Otherwise, the error code defined in {@link Sensor_Result} is
 *     returned.
 * @since 11
 */
int32_t OH_SensorEvent_GetData(Sensor_Event* sensorEvent, float **data, uint32_t *length);

/**
 * @brief Defines a struct for the sensor subscription ID, which uniquely identifies a sensor subscription. This struct
 * is used to identify a sensor subscription, including the sensor type and subscription conditions. You can use the
 * sensor subscription ID to manage the lifecycle of a sensor subscription, including activating, deactivating, and
 * querying the subscription status.<br>When subscribing to sensor data, the sensor subscription ID is used as a
 * parameter in the subscription request to identify the subscription relationship. When querying the subscribed sensor
 * information, the sensor subscription ID is used to obtain the corresponding subscription status and data. When
 * canceling a sensor subscription, the sensor subscription ID is used to specify the subscription to be canceled.
 *
 * @since 11
 */
typedef struct Sensor_SubscriptionId Sensor_SubscriptionId;

/**
 * @brief Creates a {@link Sensor_SubscriptionId} instance.
 * <br>After using the instance created by calling this function, you must call **OH_Sensor_DestroySubscriptionId()**
 * to destroy the instance and reclaim the memory. Otherwise, resource leakage may occur.
 *
 * @return Pointer to the {@link Sensor_SubscriptionId} instance (which can be used to identify sensor subscription) if
 *     the operation is successful; **NULL** otherwise.
 * @since 11
 */
Sensor_SubscriptionId *OH_Sensor_CreateSubscriptionId(void);

/**
 * @brief Destroys a {@link Sensor_SubscriptionId} instance and reclaims the memory.
 *
 * @param id Pointer to the {@link Sensor_SubscriptionId} instance.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     instance ID has been successfully destroyed. Otherwise, the error code defined in {@link Sensor_Result} is
 *     returned.
 * @since 11
 */
int32_t OH_Sensor_DestroySubscriptionId(Sensor_SubscriptionId *id);

/**
 * @brief Obtains the sensor type.
 *
 * @param id Pointer to the sensor subscription ID.
 * @param sensorType Pointer to the sensor type.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     sensor subscription type has been successfully obtained. Otherwise, the error code defined in
 *     {@link Sensor_Result} is returned.
 * @since 11
 */
int32_t OH_SensorSubscriptionId_GetType(Sensor_SubscriptionId* id, Sensor_Type *sensorType);

/**
 * @brief Sets the sensor type. After this method is successfully called, the subscription ID type is set to the value
 * of **sensorType**.
 *
 * @param id Pointer to the sensor subscription ID.
 * @param sensorType Sensor type to be set, which specifies the type of the sensor to be subscribed to. The value range
 *     is the sensor types defined in the {@link Sensor_Type} enumeration, for example, **SENSOR_TYPE_ACCELEROMETER**.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     sensor subscription type has been successfully set. Otherwise, the error code defined in {@link Sensor_Result}
 *     is returned.
 * @since 11
 */
int32_t OH_SensorSubscriptionId_SetType(Sensor_SubscriptionId* id, const Sensor_Type sensorType);

/**
 * @brief Defines a struct for the sensor subscription attribute, including the sensor type, sampling rate, and data
 * reporting interval. This attribute is applicable to sensor data subscription scenarios, helping developers configure
 * the subscription mode based on service requirements and providing flexible capabilities for obtaining sensor data.
 * This attribute can be used for step count and heart rate data subscription in health and fitness apps, real-time
 * collection of temperature and humidity data in environment monitoring apps, and status change monitoring in device
 * control apps.
 *
 * @since 11
 */
typedef struct Sensor_SubscriptionAttribute Sensor_SubscriptionAttribute;

/**
 * @brief Creates a {@link Sensor_SubscriptionAttribute} instance.
 * <br>After using the instance created by calling this function, you must call **
 * OH_Sensor_DestroySubscriptionAttribute()** to destroy the instance and reclaim the memory. Otherwise, resource
 * leakage may occur.
 *
 * @return Pointer to the {@link Sensor_SubscriptionAttribute} instance if the operation is successful. The instance
 *     can be used to configure sensor subscription attributes. Otherwise, **NULL** is returned.
 * @since 11
 */
Sensor_SubscriptionAttribute *OH_Sensor_CreateSubscriptionAttribute(void);

/**
 * @brief Destroys a {@link Sensor_SubscriptionAttribute} instance and reclaims the memory.
 *
 * @param attribute Pointer to the {@link Sensor_SubscriptionAttribute} instance.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     attribute instance has been successfully destroyed. Otherwise, the error code defined in {@link Sensor_Result}
 *     is returned.
 * @since 11
 */
int32_t OH_Sensor_DestroySubscriptionAttribute(Sensor_SubscriptionAttribute *attribute);

/**
 * @brief Sets the sensor data reporting interval. After this API is called successfully, the sampling interval of the
 * subscription is set to the value of **samplingInterval**. Subsequent sensor data will be reported at this interval.
 *
 * @param attribute Pointer to the sensor subscription attribute.
 * @param samplingInterval Data reporting interval to be set, in nanoseconds. This value determines the frequency at
 *     which sensor data is reported. A smaller value indicates a higher reporting frequency. However, if the value is
 *     too small, it may cause system performance pressure. Therefore, select a proper value range based on the sensor
 *     type.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     sensor data reporting interval has been successfully set. Otherwise, the error code defined in
 *     {@link Sensor_Result} is returned.
 * @since 11
 */
int32_t OH_SensorSubscriptionAttribute_SetSamplingInterval(Sensor_SubscriptionAttribute* attribute,
    const int64_t samplingInterval);

/**
 * @brief Obtains the sensor data reporting interval.
 *
 * @param attribute Pointer to the sensor subscription attribute.
 * @param samplingInterval Pointer to the data reporting interval, in nanoseconds. This value is the current data
 *     reporting interval of the sensor and can be used to determine the frequency of data reporting. For details about
 *     the value range, see the specific requirements of the sensor.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     sensor data reporting interval has been successfully obtained. Otherwise, the error code defined in
 *     {@link Sensor_Result} is returned.
 * @since 11
 */
int32_t OH_SensorSubscriptionAttribute_GetSamplingInterval(Sensor_SubscriptionAttribute* attribute,
    int64_t *samplingInterval);

/**
 * @brief Defines the callback function used to report sensor data.
 *
 * @param event Pointer to the sensor data information.
 * @since 11
 */
typedef void (*Sensor_EventCallback)(Sensor_Event *event);

/**
 * @brief Defines a struct for the sensor subscriber, including the subscription callback function and user data. You
 * can use this struct to specify the parameters of a sensor subscriber. After the subscription is successful, the
 * sensor data updates will be received.
 *
 * @since 11
 */
typedef struct Sensor_Subscriber Sensor_Subscriber;

/**
 * @brief Creates a {@link Sensor_Subscriber} instance.
 * <br>After using the instance created by calling this function, you must call **OH_Sensor_DestroySubscriber()** to
 * destroy the instance and reclaim the memory. Otherwise, resource leakage may occur.
 *
 * @return Pointer to the {@link Sensor_Subscriber} instance if the operation is successful. The instance can be used
 *     to subscribe to sensor data. Otherwise, **NULL** is returned.
 * @since 11
 */
Sensor_Subscriber *OH_Sensor_CreateSubscriber(void);

/**
 * @brief Destroys a {@link Sensor_Subscriber} instance and reclaims the memory.
 *
 * @param subscriber Pointer to the {@link Sensor_Subscriber} instance.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     subscriber instance has been successfully destroyed. Otherwise, the error code defined in {@link Sensor_Result}
 *     is returned.
 * @since 11
 */
int32_t OH_Sensor_DestroySubscriber(Sensor_Subscriber *subscriber);

/**
 * @brief Sets a callback function to report sensor data. After this API is called successfully, the subscriber will
 * use the specified callback function to report sensor data.
 *
 * @param subscriber Pointer to the sensor subscriber information.
 * @param callback Callback to be set, which is used to receive the reported sensor data. The callback signature is **
 *     void (*Sensor_EventCallback)(Sensor_Event *event)**, where the **event** parameter contains the detailed
 *     information about the sensor data, such as the data type, timestamp, precision, and sensor data value.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     callback function has been successfully set. Otherwise, the error code defined in {@link Sensor_Result} is
 *     returned.
 * @since 11
 */
int32_t OH_SensorSubscriber_SetCallback(Sensor_Subscriber* subscriber, const Sensor_EventCallback callback);

/**
 * @brief Obtains the callback function used to report sensor data.
 *
 * @param subscriber Pointer to the sensor subscriber information.
 * @param callback Pointer to the callback function. The value is the pointer to the currently set callback function.
 *     If no callback function is set, the value is **NULL**.
 * @return Operation result. If the operation is successful, <b>SENSOR_SUCCESS</b> is returned, indicating that the
 *     callback function has been successfully obtained. Otherwise, the error code defined in {@link Sensor_Result} is
 *     returned.
 * @since 11
 */
int32_t OH_SensorSubscriber_GetCallback(Sensor_Subscriber* subscriber, Sensor_EventCallback *callback);
#ifdef __cplusplus
}
#endif
/** @} */
#endif // OH_SENSOR_TYPE_H

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
 * @brief 定义常用传感器属性。
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
 * @brief 枚举传感器类型。
 *
 * @since 11
 */
typedef enum Sensor_Type {
    /**
     * @brief 加速度传感器。
     * @since 11
     */
    SENSOR_TYPE_ACCELEROMETER = 1,
    /**
     * @brief 陀螺仪传感器。
     * @since 11
     */
    SENSOR_TYPE_GYROSCOPE = 2,
    /**
     * @brief 环境光传感器。
     * @since 11
     */
    SENSOR_TYPE_AMBIENT_LIGHT = 5,
    /**
     * @brief 地磁传感器。
     * @since 11
     */
    SENSOR_TYPE_MAGNETIC_FIELD = 6,
    /**
     * @brief 气压传感器。
     * @since 11
     */
    SENSOR_TYPE_BAROMETER = 8,
    /**
     * @brief 霍尔传感器。
     * @since 11
     */
    SENSOR_TYPE_HALL = 10,
    /**
     * @brief 接近光传感器。
     * @since 11
     */
    SENSOR_TYPE_PROXIMITY = 12,
    /**
     * @brief 方向传感器。
     * @since 11
     */
    SENSOR_TYPE_ORIENTATION = 256,
    /**
     * @brief 重力传感器。
     * @since 11
     */
    SENSOR_TYPE_GRAVITY = 257,
    /**
     * @brief 线性加速度传感器。
     * @since 13
     */
    SENSOR_TYPE_LINEAR_ACCELERATION = 258,
    /**
     * @brief 旋转矢量传感器。
     * @since 11
     */
    SENSOR_TYPE_ROTATION_VECTOR = 259,
    /**
     * @brief 游戏旋转矢量传感器。
     * @since 13
     */
    SENSOR_TYPE_GAME_ROTATION_VECTOR = 262,
    /**
     * @brief 计步器检测传感器。
     * @since 11
     */
    SENSOR_TYPE_PEDOMETER_DETECTION = 265,
    /**
     * @brief 计步器传感器。
     * @since 11
     */
    SENSOR_TYPE_PEDOMETER = 266,
    /**
     * @brief 心率传感器。
     * @since 11
     */
    SENSOR_TYPE_HEART_RATE = 278,
} Sensor_Type;

/**
 * @brief 定义传感器错误码。
 *
 * @since 11
 */
typedef enum Sensor_Result {
    /**
     * @brief 操作成功。
	 * @since 11
     */
    SENSOR_SUCCESS = 0,
    /**
     * @brief 权限验证失败。可能原因：应用缺少必要的传感器权限、权限申请被拒绝、权限级别不足等。解决措施：请检查应用配置文件中是否已申请所需的传感器权限，确保在运行时正确请求和获取权限。
	 * @since 11
     */
    SENSOR_PERMISSION_DENIED = 201,
    /**
     * @brief 参数检查失败。可能原因：参数为空、参数超出有效范围、参数类型不匹配、缺少必填参数等。解决措施：请根据具体函数的参数说明，检查传入的参数是否完整、符合类型要求、在有效范围内，并修正参数值。
	 * @since 11
     */
    SENSOR_PARAMETER_ERROR = 401,
    /**
     * @brief 传感器服务异常。可能原因：传感器服务未启动、传感器服务崩溃、设备不支持指定传感器、系统资源不足等。解决措施：请检查设备是否支持所需传感器，确保系统资源充足，必要时重启设备或重新初始化传感器服务。
	 * @since 11
     */
    SENSOR_SERVICE_EXCEPTION = 14500101,
} Sensor_Result;

/**
 * @brief 枚举传感器报告的数据的精度级别。
 *
 * @since 11
 */
typedef enum Sensor_Accuracy {
    /**
     * @brief 传感器数据不可靠。有可能传感器不与设备接触而进行测量。
     * @since 11
     */
    SENSOR_ACCURACY_UNRELIABLE = 0,
    /**
     * @brief 传感器数据精度较低。数据在使用前必须根据环境进行校准。
	 * @since 11
     */
    SENSOR_ACCURACY_LOW = 1,
    /**
     * @brief 传感器数据处于中等精度水平。建议用户在使用前根据实际环境进行数据校准。
	 * @since 11
     */
    SENSOR_ACCURACY_MEDIUM = 2,
    /**
     * @brief 传感器数据具有很高的精度。数据可以直接使用。
	 * @since 11
     */
    SENSOR_ACCURACY_HIGH = 3
} Sensor_Accuracy;

/**
 * @brief 定义传感器信息结构体，用于存储传感器的基本属性和数据信息，包括传感器类型、版本、标识等关键字段。开发者通过该结构体可获取传感器的完整描述信息，用于传感器的初始化和数据查询。
 *
 * @since 11
 */
typedef struct Sensor_Info Sensor_Info;

/**
 * @brief 用给定的数字创建一个实例数组，请参考{@link Sensor_Info}。创建成功后，返回指向count个Sensor_Info实例的指针数组。
 * <br>调用此函数创建的实例数组，在使用完毕后必须调用OH_Sensor_DestroyInfos()销毁并回收内存，否则会导致资源泄漏。
 *
 * @param count 要创建的实例的数量，请参考 {@link Sensor_Info}。
 * @return 如果操作成功，返回指向{@link Sensor_Info}实例数组的双指针，数组中包含count个Sensor_Info实例，用于存储传感器信息；否则返回<b>NULL</b>。
 * @since 11
 */
Sensor_Info **OH_Sensor_CreateInfos(uint32_t count);

/**
 * @brief 销毁实例数组并回收内存，请参考{@link Sensor_Info}。调用成功后，实例数组占用的内存被释放，sensors指针及其指向的所有Sensor_Info实例不能再使用。
 *
 * @param sensors 指向{@link Sensor_Info}实例数组的双指针。
 * @param count 要销毁的{@link Sensor_Info}实例的数量。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示所有实例已成功销毁；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_Sensor_DestroyInfos(Sensor_Info **sensors, uint32_t count);

/**
 * @brief 获取传感器名称。获取成功后，sensorName参数中会填充传感器名称的字符串，length参数中会返回字符串的长度（包含结束符）。
 *
 * @param sensor 指向传感器信息的指针。
 * @param sensorName 指向传感器名称的指针。
 * @param length 指向长度的指针，单位：B（字节）。调用前应设置为缓冲区大小，调用后返回实际名称长度。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示传感器名称已成功获取；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorInfo_GetName(Sensor_Info* sensor, char *sensorName, uint32_t *length);

/**
 * @brief 获取传感器的厂商名称。获取成功后，vendorName参数中会填充传感器厂商名称的字符串，length参数中会返回字符串的长度（包含结束符）。
 *
 * @param sensor 指向传感器信息的指针。
 * @param vendorName 指向厂商名称的指针。
 * @param length 指向长度的指针，单位：B（字节）。调用前应设置为缓冲区大小，调用后返回实际厂商名称长度。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示传感器厂商名称已成功获取；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorInfo_GetVendorName(Sensor_Info* sensor, char *vendorName, uint32_t *length);

/**
 * @brief 获取{@link Sensor_Type}。获取成功后，sensorType参数中会填充传感器的类型值。
 *
 * @param sensor 指向传感器信息的指针。
 * @param sensorType 指向传感器类型的指针。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示传感器类型已成功获取；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorInfo_GetType(Sensor_Info* sensor, Sensor_Type *sensorType);

/**
 * @brief 获取传感器分辨率。获取成功后，resolution参数中会填充传感器的分辨率值。
 *
 * @param sensor 指向传感器信息的指针。
 * @param resolution 指向传感器分辨率的指针。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示传感器分辨率已成功获取；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorInfo_GetResolution(Sensor_Info* sensor, float *resolution);

/**
 * @brief 获取传感器的最小数据上报间隔。获取成功后，minSamplingInterval参数中会填充传感器的最小数据上报间隔值，单位：ns（纳秒）。
 *
 * @param sensor 指向传感器信息的指针。
 * @param minSamplingInterval 指向最小数据报告间隔的指针，单位：ns（纳秒）。该值表示传感器支持的最快数据上报间隔，小于该值的设置可能导致数据丢失或性能下降。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示最小数据上报间隔已成功获取；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorInfo_GetMinSamplingInterval(Sensor_Info* sensor, int64_t *minSamplingInterval);

/**
 * @brief 获取传感器的最大数据上报间隔。获取成功后，maxSamplingInterval参数中会填充传感器的最大数据上报间隔值，单位：ns（纳秒）。
 *
 * @param sensor 指向传感器信息的指针。
 * @param maxSamplingInterval 指向最大数据报告间隔的指针，单位：ns（纳秒）。该值表示传感器支持的最慢数据上报间隔，大于该值的设置可能导致数据更新不及时。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示最大数据上报间隔已成功获取；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorInfo_GetMaxSamplingInterval(Sensor_Info* sensor, int64_t *maxSamplingInterval);

/**
 * @brief 定义传感器事件的数据结构，包含传感器类型、时间戳和传感器数据等信息。
 *
 * @since 11
 */
typedef struct Sensor_Event Sensor_Event;

/**
 * @brief 获取传感器类型。
 *
 * @param sensorEvent 指向传感器数据信息的指针。
 * @param sensorType 指向传感器类型的指针。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示传感器事件类型已成功获取；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorEvent_GetType(Sensor_Event* sensorEvent, Sensor_Type *sensorType);

/**
 * @brief 获取传感器数据的时间戳。
 *
 * @param sensorEvent 指向传感器数据信息的指针。
 * @param timestamp 指向时间戳的指针，单位：ns（纳秒），表示传感器数据采集的时间。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示时间戳已成功获取；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorEvent_GetTimestamp(Sensor_Event* sensorEvent, int64_t *timestamp);

/**
 * @brief 获取传感器数据的精度。
 *
 * @param sensorEvent 指向传感器数据信息的指针。
 * @param accuracy 指向传感器数据精度级别的指针。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示传感器数据精度已成功获取；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorEvent_GetAccuracy(Sensor_Event* sensorEvent, Sensor_Accuracy *accuracy);

/**
 * @brief 数据的长度和内容依赖于监听的传感器类型，传感器上报的数据格式如下所示：
 * <br>| 传感器类型 | 数据元素及描述 |
 * <br>| SENSOR_TYPE_ACCELEROMETER | data[0]、data[1]、data[2]分别表示设备x、y、z轴的加速度分量，单位：m/s² |
 * <br>| SENSOR_TYPE_GYROSCOPE | data[0]、data[1]、data[2]分别表示设备x、y、z轴的旋转角速度，单位：rad/s（弧度/秒） |
 * <br>| SENSOR_TYPE_AMBIENT_LIGHT | data[0]表示环境光强度，单位：lux（勒克斯）；从API version 12开始，data[1]表示色温，单位：K（开尔文）；
 * data[2]表示红外亮度，单位：cd/m²（坎德拉每平方米） |
 * <br>| SENSOR_TYPE_MAGNETIC_FIELD | data[0]、data[1]、data[2]分别表示设备x、y、z轴的地磁分量，单位：μT（微特斯拉） |
 * <br>| SENSOR_TYPE_BAROMETER | data[0]表示气压值，单位：hPa（百帕） |
 * <br>| SENSOR_TYPE_HALL | data[0]表示皮套吸合状态，0表示打开，大于0表示吸附 |
 * <br>| SENSOR_TYPE_PROXIMITY | data[0]表示接近状态，0表示接近，大于0表示远离 |
 * <br>| SENSOR_TYPE_ORIENTATION | data[0]、data[1]、data[2]分别表示设备绕z、x、y轴的角度，单位：°（度） |
 * <br>| SENSOR_TYPE_GRAVITY | data[0]、data[1]、data[2]分别表示设备x、y、z轴的重力加速度分量，单位：m/s² |
 * <br>| SENSOR_TYPE_ROTATION_VECTOR | data[0]、data[1]、data[2]分别表示设备x、y、z轴的旋转角度，单位：°（度）；data[3]表示旋转向量元素 |
 * <br>| SENSOR_TYPE_PEDOMETER_DETECTION | data[0]表示步数检测状态，1表示检测到了步数变化 |
 * <br>| SENSOR_TYPE_PEDOMETER | data[0]表示步数 |
 * <br>| SENSOR_TYPE_HEART_RATE | data[0]表示心率数值 |
 * <br>| SENSOR_TYPE_LINEAR_ACCELERATION | 从API version 13开始支持。data[0]、data[1]、data[2]分别表示设备x、y、z轴的线性加速度，单位：m/s² |
 * <br>| SENSOR_TYPE_GAME_ROTATION_VECTOR | 从API version 13开始支持。data[0]、data[1]、data[2]分别表示设备x、y、z轴的旋转角度，单位：°（度）；
 * data[3]表示旋转向量 |
 *
 * @param sensorEvent - 指向传感器数据信息的指针。
 * @param data - 出参，传感器数据数组指针。数据格式依赖传感器类型，具体格式参考函数描述。
 * @param length - 出参，数据数组的长度，表示data数组中有效数据的个数。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示传感器数据已成功获取；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorEvent_GetData(Sensor_Event* sensorEvent, float **data, uint32_t *length);

/**
 * @brief 定义传感器订阅ID结构体，用于唯一标识传感器订阅请求。该结构体用于标识一个传感器订阅操作，包含传感器类型、订阅的具体订阅条件等信息。开发者可以通过传感器订阅ID来管理传感器的订阅生命周期，包括激活、
 * 去激活和查询订阅状态等操作。<br>在订阅传感器数据时，作为订阅请求的参数，用于标识订阅关系，在查询已订阅的传感器信息时，用于获取对应的订阅状态和数据，在取消传感器订阅时，用于指定需要取消的订阅。
 *
 * @since 11
 */
typedef struct Sensor_SubscriptionId Sensor_SubscriptionId;

/**
 * @brief 创建一个{@link Sensor_SubscriptionId}实例。
 * <br>调用此函数创建的实例，在使用完毕后必须调用OH_Sensor_DestroySubscriptionId()销毁并回收内存，否则会导致资源泄漏。
 *
 * @return 如果操作成功，返回指向{@link Sensor_SubscriptionId}实例的指针，该实例可用于标识传感器订阅；否则返回<b>NULL</b>。
 * @since 11
 */
Sensor_SubscriptionId *OH_Sensor_CreateSubscriptionId(void);

/**
 * @brief 销毁{@link Sensor_SubscriptionId}实例并回收内存。
 *
 * @param id 指向{@link Sensor_SubscriptionId}实例的指针。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示订阅ID实例已成功销毁；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_Sensor_DestroySubscriptionId(Sensor_SubscriptionId *id);

/**
 * @brief 获取传感器类型。
 *
 * @param id 指向传感器订阅ID的指针。
 * @param sensorType 指向传感器类型的指针。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示传感器订阅类型已成功获取；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorSubscriptionId_GetType(Sensor_SubscriptionId* id, Sensor_Type *sensorType);

/**
 * @brief 设置传感器类型。调用成功后，订阅ID的类型被设置为指定的sensorType值。
 *
 * @param id 指向传感器订阅ID的指针。
 * @param sensorType 要设置的传感器类型，用于指定订阅的传感器类型。取值范围为{@link Sensor_Type}枚举中定义的传感器类型，如SENSOR_TYPE_ACCELEROMETER(加速度传感器)等。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示传感器订阅类型已成功设置；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorSubscriptionId_SetType(Sensor_SubscriptionId* id, const Sensor_Type sensorType);

/**
 * @brief 定义传感器订阅属性结构体，用于指定传感器订阅的相关参数，包括订阅的传感器类型、采样间隔等。该属性适用于传感器数据订阅场景，帮助开发者根据业务需求配置订阅方式，提供灵活的传感器数据获取能力。
 * 该属性用于指定传感器订阅的具体参数，如采样率、数据上报间隔等，用于配置传感器的数据采集和上报行为。用于运动健康应用中的步数和心率数据订阅，环境监测应用中的温湿度数据实时采集，设备控制应用中的状态变化监听等。
 *
 * @since 11
 */
typedef struct Sensor_SubscriptionAttribute Sensor_SubscriptionAttribute;

/**
 * @brief 创建{@link Sensor_SubscriptionAttribute}实例。
 * <br>调用此函数创建的实例，在使用完毕后必须调用OH_Sensor_DestroySubscriptionAttribute()销毁并回收内存，否则会导致资源泄漏。
 *
 * @return 如果操作成功，返回指向{@link Sensor_SubscriptionAttribute}实例的指针，该实例可用于配置传感器订阅属性；否则返回<b>NULL</b>。
 * @since 11
 */
Sensor_SubscriptionAttribute *OH_Sensor_CreateSubscriptionAttribute(void);

/**
 * @brief 销毁{@link Sensor_SubscriptionAttribute}实例并回收内存。
 *
 * @param attribute 指向{@link Sensor_SubscriptionAttribute}实例的指针。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示订阅属性实例已成功销毁；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_Sensor_DestroySubscriptionAttribute(Sensor_SubscriptionAttribute *attribute);

/**
 * @brief 设置传感器数据报告间隔。调用成功后，订阅属性的采样间隔被设置为指定的samplingInterval值，后续传感器数据上报将按照此间隔进行。
 *
 * @param attribute 指向传感器订阅属性的指针。
 * @param samplingInterval 要设置的数据报告间隔，单位：ns（纳秒）。该值决定了传感器数据上报的频率，值越小上报频率越高，过小可能导致系统性能压力，需根据传感器类型选择合适范围。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示传感器数据报告间隔已成功设置；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorSubscriptionAttribute_SetSamplingInterval(Sensor_SubscriptionAttribute* attribute,
    const int64_t samplingInterval);

/**
 * @brief 获取传感器数据报告间隔。
 *
 * @param attribute 指向传感器订阅属性的指针。
 * @param samplingInterval 指向数据报告间隔的指针，单位：ns（纳秒）。该值为当前设置的传感器数据上报间隔，可用于判断数据上报的频率，一般范围需参考传感器具体要求。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示传感器数据报告间隔已成功获取；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorSubscriptionAttribute_GetSamplingInterval(Sensor_SubscriptionAttribute* attribute,
    int64_t *samplingInterval);

/**
 * @brief 定义用于报告传感器数据的回调函数。
 *
 * @param event 指向传感器数据信息的指针。
 * @since 11
 */
typedef void (*Sensor_EventCallback)(Sensor_Event *event);

/**
 * @brief 用于注册传感器数据订阅的订阅者信息结构体，包含订阅回调函数和用户数据。使用该结构体可以指定传感器订阅者的参数，订阅成功后，将接收传感器的数据更新。
 *
 * @since 11
 */
typedef struct Sensor_Subscriber Sensor_Subscriber;

/**
 * @brief 创建一个{@link Sensor_Subscriber}实例。
 * <br>调用此函数创建的实例，在使用完毕后必须调用OH_Sensor_DestroySubscriber()销毁并回收内存，否则会导致资源泄漏。
 *
 * @return 如果操作成功，返回指向{@link Sensor_Subscriber}实例的指针，该实例可用于订阅传感器数据；否则返回<b>NULL</b>。
 * @since 11
 */
Sensor_Subscriber *OH_Sensor_CreateSubscriber(void);

/**
 * @brief 销毁{@link Sensor_Subscriber}实例并回收内存。
 *
 * @param subscriber 指向{@link Sensor_Subscriber}实例的指针。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示订阅者实例已成功销毁；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_Sensor_DestroySubscriber(Sensor_Subscriber *subscriber);

/**
 * @brief 设置一个回调函数来报告传感器数据。调用成功后，订阅者将使用指定的回调函数来报告传感器数据。
 *
 * @param subscriber 指向传感器订阅者信息的指针。
 * @param callback 要设置的回调函数，用于接收传感器数据上报。回调函数签名为void (*Sensor_EventCallback)(Sensor_Event *event)，其中event参数包含传感器数据的详细信息，
 *     如数据类型、时间戳、精度和传感器数据值。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示回调函数已成功设置；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorSubscriber_SetCallback(Sensor_Subscriber* subscriber, const Sensor_EventCallback callback);

/**
 * @brief 获取用于报告传感器数据的回调函数。
 *
 * @param subscriber 指向传感器订阅者信息的指针。
 * @param callback 指向回调函数的指针。该值为当前设置的回调函数指针，若未设置则为NULL。
 * @return 返回操作结果，如果成功返回<b>SENSOR_SUCCESS</b>，表示回调函数已成功获取；否则返回{@link Sensor_Result}中定义的错误代码。
 * @since 11
 */
int32_t OH_SensorSubscriber_GetCallback(Sensor_Subscriber* subscriber, Sensor_EventCallback *callback);
#ifdef __cplusplus
}
#endif
/** @} */
#endif // OH_SENSOR_TYPE_H

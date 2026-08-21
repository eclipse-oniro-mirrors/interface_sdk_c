/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup Location
 * @{
 *
 * @brief 提供查询位置开关状态、启动定位、停止定位的接口。
 *
 * @since 13
 */

/**
 * @file oh_location_type.h
 * @kit LocationKit
 * @brief 定义位置服务常用的属性。
 * @library liblocation_ndk.so
 * @syscap SystemCapability.Location.Location.Core
 * @since 13
 */

#ifndef OH_LOCATION_TYPE_H
#define OH_LOCATION_TYPE_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义位置服务的错误码。
 * @since 13
 */
typedef enum Location_ResultCode {
    /**
     * 操作成功。
     */
    LOCATION_SUCCESS = 0,
    /**
     * 权限校验失败。
     */
    LOCATION_PERMISSION_DENIED = 201,
    /**
     * 参数错误。
     * 可能原因：1.输入参数为空指针；2.参数数值超出定义范围。
     */
    LOCATION_INVALID_PARAM = 401,
    /**
     * 该功能不支持。由于设备能力有限，无法调用该函数。
     */
    LOCATION_NOT_SUPPORTED = 801,
    /**
     * 位置服务不可用。
     */
    LOCATION_SERVICE_UNAVAILABLE = 3301000,
    /**
     * 位置开关处于关闭状态。
     */
    LOCATION_SWITCH_OFF = 3301100
} Location_ResultCode;

/**
 * @brief 定义位置请求中的用户活动场景类型。
 *
 * @since 13
 */
typedef enum Location_UseScene {
    /**
     * 导航场景。
     * 适用于在户外获取设备实时位置的场景，如车载、步行导航。
     * 主要使用GNSS定位技术提供定位服务，功耗较高。
     */
    LOCATION_USE_SCENE_NAVIGATION = 0x0401,
    /**
     * 表示运动场景。
     * 适用于记录用户位置轨迹的场景，如运动类应用记录轨迹功能。
     * 主要使用GNSS定位技术提供定位服务，功耗较高。
     */
    LOCATION_USE_SCENE_SPORT = 0x0402,
    /**
     * 表示出行场景。
     * 适用于用户出行场景，如打车、乘坐公共交通等场景。
     * 主要使用GNSS定位技术提供定位服务，功耗较高。
     */
    LOCATION_USE_SCENE_TRANSPORT = 0x0403,
    /**
     * 表示日常服务使用场景。
     * 适用于不需要定位用户精确位置的使用场景，如新闻资讯、网购、点餐类应用。
     * 该场景仅使用网络定位技术提供定位服务，功耗较低。
     */
    LOCATION_USE_SCENE_DAILY_LIFE_SERVICE = 0x0404
} Location_UseScene;

/**
 * @brief 定义位置请求中的功耗场景类型。
 *
 * @since 13
 */
typedef enum Location_PowerConsumptionScene {
    /**
     * 高功耗。
     * 以GNSS定位技术为主。在GNSS提供稳定位置结果之前会使用网络定位技术提供服务。
     * 在持续定位时，如果超过30秒无法获取GNSS定位结果则会使用网络定位技术获取位置。
     * 对设备的硬件资源消耗较大，功耗较大。
     */
    LOCATION_HIGH_POWER_CONSUMPTION = 0x0601,
    /**
     * 低功耗。
     * 适用于对用户位置精度要求不高的使用场景，如新闻资讯、网购、点餐类应用。
     * 该场景仅使用网络定位技术提供定位服务，功耗较低。
     */
    LOCATION_LOW_POWER_CONSUMPTION = 0x0602,
    /**
     * 无功耗。
     * 这种场景下不会主动触发定位，会在其他应用定位时，才给当前应用返回位置。
     */
    LOCATION_NO_POWER_CONSUMPTION = 0x0603
} Location_PowerConsumptionScene;

/**
 * @brief 定义位置信息的来源。
 *
 * @since 13
 */
typedef enum Location_SourceType {
    /**
     * 表示定位结果来自于GNSS定位技术。
     */
    LOCATION_SOURCE_TYPE_GNSS = 1,
    /**
     * 表示定位结果来自于网络定位技术。
     */
    LOCATION_SOURCE_TYPE_NETWORK = 2,
    /**
     * 表示定位结果来自于室内高精度定位技术。
     */
    LOCATION_SOURCE_TYPE_INDOOR = 3,
    /**
     * 表示定位结果来自于室外高精度定位技术。
     */
    LOCATION_SOURCE_TYPE_RTK = 4
} Location_SourceType;

/**
 * @brief 定义位置基本信息的结构体。
 *
 * @since 13
 */
typedef struct Location_BasicInfo {
    /**
     * 表示纬度信息，正值表示北纬，负值表示南纬。取值范围为-90到90。仅支持WGS84坐标系。
     */
    double latitude;
    /**
     * 表示经度信息，正值表示东经，负值表示西经。取值范围为-180到180。仅支持WGS84坐标系。
     */
    double longitude;
    /**
     * 表示高度信息，单位米。
     */
    double altitude;
    /**
     * 表示精度信息，单位米。
     */
    double accuracy;
    /**
     * 表示速度信息，单位米每秒。
     */
    double speed;
    /**
     * 表示航向信息。单位是“度”，取值范围为0到360。
     */
    double direction;
    /**
     * 表示位置时间戳，UTC格式。
     */
    int64_t timeForFix;
    /**
     * 表示获取位置的时间戳，值表示从本次开机到获取位置所经过的时间，单位为纳秒。
     */
    int64_t timeSinceBoot;
    /**
     * 表示高度信息的精度，单位米。
     */
    double altitudeAccuracy;
    /**
     * 表示速度信息的精度，单位米每秒。
     */
    double speedAccuracy;
    /**
     * 表示航向信息的精度。单位是“度”，取值范围为0到360。
     */
    double directionAccuracy;
    /**
     * 表示位置时间戳的不确定度，单位为纳秒。
     */
    int64_t uncertaintyOfTimeSinceBoot;
    /**
     * 表示定位结果的来源。详细定义请参考Location_SourceType。
     */
    Location_SourceType locationSourceType;
} Location_BasicInfo;

/**
 * @brief 定义位置信息的结构体。
 * @since 13
 */
typedef struct Location_Info Location_Info;

/**
 * @brief 判断定位信息是否来自模拟位置功能。
 *
 * @param location - 指向位置信息结构体的指针。
 *     需要传入非空指针，该指针可以在{@link Location_InfoCallback}中获取。
 * @return 返回bool类型的结果，用于指示该位置是否来自模拟位置功能。
 *     如果值为 true，表示该位置来自模拟位置功能；如果值为false，表示该位置源自系统的真实定位结果。
 * @since 26.0.0
 */
bool OH_LocationInfo_IsFromMock(Location_Info* location);

/**
 * @brief 获取位置基本信息。
 *
 * @param location - 指向位置信息结构体的指针。
 *     需要传入非空指针，该指针可以在{@link Location_InfoCallback}中获取。
 * @return Return 返回位置基本信息结构体。详细定义请参考{@link Location_BasicInfo}
 * @since 13
 */
Location_BasicInfo OH_LocationInfo_GetBasicInfo(Location_Info* location);

/**
 * @brief 获取位置信息中的附加信息。
 *
 * @param location - 指向位置信息结构体的指针。
 *     需要传入非空指针，该指针可以在 {@link Location_InfoCallback}中获取。
 * @param additionalInfo - char类型的非空指针；该变量用于保存附加信息字符串，该字符串是JSON格式。
 *     该指针和对应的内存由调用者创建，建议申请大于等于256字节的内存。
 *     如果传入空指针，会返回错误码。
 * @param length - 表示additionalInfo的内存大小。
 * @return 返回操作结果。详细定义参见{@link Location_ResultCode}。
 *     {@link LOCAION_SUCCESS} 获取附加信息成功。
 *     {@link LOCATION_INVALID_PARAM} 1. 入参location或additionalInfo是空指针。
 *     2. 入参length太小，也就是additionalInfo指向的内存太小导致无法保存完整的附加信息字符串。
 * @since 13
 */
Location_ResultCode OH_LocationInfo_GetAdditionalInfo(Location_Info* location,
    char* additionalInfo, uint32_t length);

/**
 * @brief 用于接收位置上报的回调函数。
 *
指向Location_Info实例的指针，携带最新的位置信息。

location实例的内存会在Location_InfoCallback结束时回收，请在此之前调用OH_LocationInfo_GetBasicInfo等接口获取位置信息。

 * @param location - 指向{@link Location_Info} 实例的指针，携带最新的位置信息。
 *     location实例的内存会在{@link Location_InfoCallback}结束时回收，
 *     请在此之前调用{@link OH_LocationInfo_GetBasicInfo}等接口获取位置信息。
 * @param userData - 指向调用者数据结构或对象的指针，该参数是通过{@link OH_LocationRequestConfig_SetCallback}传入的。
 * @since 13
 */
typedef void (*Location_InfoCallback)(Location_Info* location, void* userData);

/**
 * @brief 定义位置请求参数的结构体。
 * @since 13
 */
typedef struct Location_RequestConfig Location_RequestConfig;

/**
 * @brief 创建一个位置请求参数结构体实例。
 *
 * @return 返回指向{@link Location_RequestConfig}实例的指针。
 *     如果返回NULL表示创建失败，可能的原因是应用地址空间满，导致空间分配不出来。
 * @since 13
 */
Location_RequestConfig* OH_Location_CreateRequestConfig(void);

/**
 * @brief 销毁位置请求参数实例并回收内存。
 *
 * @param requestConfig - 指向{@link Location_RequestConfig}实例的指针。
 *     该实例是由{@link OH_Location_CreateRequestConfig}创建的。
 * @since 13
 */
void OH_Location_DestroyRequestConfig(Location_RequestConfig* requestConfig);

/**
 * @brief 设置位置请求参数中的用户活动场景。
 *     位置请求参数{@link Location_RequestConfig}中以useScene优先。
 *     如果设置了useScene，则powerConsumptionScene参数无效。
 *     如果未设置useScene，设置了powerConsumptionScene则该参数生效。
 *     如果两个参数都未设置，则默认useScene为{@link LOCATION_USE_SCENE_DAILY_LIFE_SERVICE}，
 *     powerConsumptionScene参数无效。
 *
 * @param requestConfig - 指向{@link Location_RequestConfig}实例的指针。
 *     该实例是由{@link OH_Location_CreateRequestConfig}创建的。
 * @param useScene - 表示位置请求时的用户活动场景。
 *     默认值是{@link LOCATION_USE_SCENE_DAILY_LIFE_SERVICE}。
 *     详细定义见{@link Location_UseScene}。
 * @since 13
 */
void OH_LocationRequestConfig_SetUseScene(Location_RequestConfig* requestConfig,
    Location_UseScene useScene);

/**
 * @brief 设置位置请求参数中的功耗场景。
 *
 * @param requestConfig - 指向{@link Location_RequestConfig}实例的指针。
 *     该实例是由{@link OH_Location_CreateRequestConfig}创建的。
 * @param powerConsumptionScene - 表示位置请求的功耗场景。
 *     默认值是{@link LOCATION_LOW_POWER_CONSUMPTION}。
 *     详细定义见{@link Location_PowerConsumptionScene}。
 * @since 13
 */
void OH_LocationRequestConfig_SetPowerConsumptionScene(Location_RequestConfig* requestConfig,
    Location_PowerConsumptionScene powerConsumptionScene);

/**
 * @brief 设置位置请求参数中的位置上报间隔。
 *
 * @param requestConfig - 指向{@link Location_RequestConfig}实例的指针。
 *     该实例是由{@link OH_Location_CreateRequestConfig}创建的。
 * @param interval - 表示位置上报时间间隔，单位是“秒”。取值范围为大于等于1，默认值为1。
 * @since 13
 */
void OH_LocationRequestConfig_SetInterval(Location_RequestConfig* requestConfig,
    int interval);

/**
 * @brief 设置回调函数。
 *
 * @param requestConfig - 指向{@link Location_RequestConfig}实例的指针。
 *     该实例是由{@link OH_Location_CreateRequestConfig}创建的。
 * @param callback - 指向回调函数的指针，该回调函数用于接收位置信息变化。
 *     详细定义请参考{@link Location_InfoCallback}。
 * @param userData - 指向调用者数据结构或对象的指针。这个指针会在回调函数执行时作为入参回传给调用者。
 * @since 13
 */
void OH_LocationRequestConfig_SetCallback(Location_RequestConfig* requestConfig,
    Location_InfoCallback callback, void* userData);
#ifdef __cplusplus
}
#endif
/** @} */
#endif // OH_LOCATION_TYPE_H
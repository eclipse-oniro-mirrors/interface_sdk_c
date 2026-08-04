/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup OH_Camera
 * @{
 *
 * @brief Provide the definition of the C interface for the camera module.
 *
 * @since 11
 * @version 1.0
 */

/**
 * @file camera.h
 *
 * @brief 定义相机的基本接口和功能。
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 11
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_CAMERA_CAMERA_H
#define NATIVE_INCLUDE_CAMERA_CAMERA_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 相机管理器对象。<br> 可以使用{@link OH_Camera_GetCameraManager}方法创建指针。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Manager Camera_Manager;

/**
 * @brief 相机错误代码的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_ErrorCode {
    /**
     * 相机结果正常。
     */
    CAMERA_OK = 0,

    /**
     * 参数丢失或参数类型不正确。
     */
    CAMERA_INVALID_ARGUMENT = 7400101,

    /**
     * 不允许操作。
     */
    CAMERA_OPERATION_NOT_ALLOWED = 7400102,

    /**
     * 会话未配置。
     */
    CAMERA_SESSION_NOT_CONFIG = 7400103,

    /**
     * 会话未运行。
     */
    CAMERA_SESSION_NOT_RUNNING = 7400104,

    /**
     * 会话配置已锁定。
     */
    CAMERA_SESSION_CONFIG_LOCKED = 7400105,

    /**
     * 设备设置已锁定。
     */
    CAMERA_DEVICE_SETTING_LOCKED = 7400106,

    /**
     * 因冲突而无法使用相机。
     */
    CAMERA_CONFLICT_CAMERA = 7400107,

    /**
     * 由于安全原因，相机已禁用。
     */
    CAMERA_DEVICE_DISABLED = 7400108,

    /**
     * 因被抢占而无法使用相机。
     */
    CAMERA_DEVICE_PREEMPTED = 7400109,

    /**
     * 与当前配置存在冲突。
     * @since 12
     */
    CAMERA_UNRESOLVED_CONFLICTS_WITH_CURRENT_CONFIGURATIONS = 7400110,

    /**
     * 可选属性不存在。
     * @since 26.0.0
     */
    CAMERA_ERROR_OPTIONAL_PROPERTY_NOT_EXIST = 7400113,

    /**
     * 相机服务异常。<br> 比如没有相机权限、相机服务重启、跨进程调用异常等。
     */
    CAMERA_SERVICE_FATAL_ERROR = 7400201,

    /**
    * 表示设备当前不支持该能力。
    * @since 26.0.0
    */
    CAMERA_ERROR_CAPABILITY_NOT_SUPPORTED = 7400114,
} Camera_ErrorCode;

/**
 * @brief 相机状态的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_Status {
    /**
     * 显示状态。
     */
    CAMERA_STATUS_APPEAR = 0,

    /**
     * 消失状态。
     */
    CAMERA_STATUS_DISAPPEAR = 1,

    /**
     * 可用状态。
     */
    CAMERA_STATUS_AVAILABLE = 2,

    /**
     * 不可用状态。
     */
    CAMERA_STATUS_UNAVAILABLE = 3
} Camera_Status;

/**
 * @brief 相机模式的枚举。
 * 
 * @since 12
 * @version 1.0
 */
typedef enum Camera_SceneMode {
    /**
     * 普通相机模式。
     */
    NORMAL_PHOTO = 1,

    /**
     * 普通视频模式。
     */
    NORMAL_VIDEO = 2,

    /**
     * 安全相机模式，主要为银行等有活体检测等安全诉求的应用提供。安全相机的使用需要加密算法框架及可信应用服务，详情请参见{@link Device Certificate Kit简介}。
     */
    SECURE_PHOTO = 12
} Camera_SceneMode;

/**
 * @brief 相机位置的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_Position {
    /**
     * 相对于设备屏幕没有固定的朝向的相机。
     */
    CAMERA_POSITION_UNSPECIFIED = 0,

    /**
     * 后置。
     */
    CAMERA_POSITION_BACK = 1,

    /**
     * 前置。
     */
    CAMERA_POSITION_FRONT = 2
} Camera_Position;

/**
 * @brief Car设备摄像头位置的枚举。
 *
 * @since 26.0.0
 */
typedef enum OH_Camera_AutomotiveCameraPosition {
    /**
     * Car设备外部其他位置摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_EXTERIOR_OTHER = 0,

    /**
     * Car设备外部前侧摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_EXTERIOR_FRONT = 1,

    /**
     * Car设备外部后侧摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_EXTERIOR_REAR = 2,

    /**
     * Car设备外部左侧摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_EXTERIOR_LEFT = 3,

    /**
     * Car设备外部右侧摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_EXTERIOR_RIGHT = 4,

    /**
     * Car设备内部其他位置摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_INTERIOR_OTHER = 5,

    /**
     * Car设备内部第一排左侧摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_INTERIOR_ROW_1_LEFT = 6,

    /**
     * Car设备内部第一排中央摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_INTERIOR_ROW_1_CENTER = 7,

    /**
     * Car设备内部第一排右侧摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_INTERIOR_ROW_1_RIGHT = 8,

    /**
     * Car设备内部第二排左侧摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_INTERIOR_ROW_2_LEFT = 9,

    /**
     * Car设备内部第二排中央摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_INTERIOR_ROW_2_CENTER = 10,

    /**
     * Car设备内部第二排右侧摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_INTERIOR_ROW_2_RIGHT = 11,

    /**
     * Car设备内部第三排左侧摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_INTERIOR_ROW_3_LEFT = 12,

    /**
     * Car设备内部第三排中央摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_INTERIOR_ROW_3_CENTER = 13,

    /**
     * Car设备内部第三排右侧摄像头。
     * @since 26.0.0
     */
    OH_CAMERA_AUTOMOTIVE_CAMERA_POSITION_INTERIOR_ROW_3_RIGHT = 14
} OH_Camera_AutomotiveCameraPosition;

/**
 * @brief 相机类型的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_Type {
    /**
     * 默认相机类型。
     */
    CAMERA_TYPE_DEFAULT = 0,

    /**
     * 广角相机。
     */
    CAMERA_TYPE_WIDE_ANGLE = 1,

    /**
     * 超广角相机。
     */
    CAMERA_TYPE_ULTRA_WIDE = 2,

    /**
     * 长焦相机。
     */
    CAMERA_TYPE_TELEPHOTO = 3,

    /**
     * 景深相机。
     */
    CAMERA_TYPE_TRUE_DEPTH = 4
} Camera_Type;

/**
 * @brief 相机连接类型的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_Connection {
    /**
     * 内置相机。
     */
    CAMERA_CONNECTION_BUILT_IN = 0,

    /**
     * 使用USB连接的相机。
     */
    CAMERA_CONNECTION_USB_PLUGIN = 1,

    /**
     * 远程相机。
     */
    CAMERA_CONNECTION_REMOTE = 2
} Camera_Connection;

/**
 * @brief 传感器滤色阵列排列方式。
 *
 * @since 24
 */
typedef enum OH_Camera_SensorColorFilterArrangement{
    /**
     * BGGR（Blue-Green-Green-Red）滤色阵列排列。
     * @since 24
     */
    OH_CAMERA_SENSOR_CFA_BGGR = 0,

    /**
     * GBRG（Green-Blue-Red-Green）滤色阵列排列。
     * @since 24
     */
    OH_CAMERA_SENSOR_CFA_GBRG = 1,

    /**
     * GRBG（Green-Red-Blue-Green）滤色阵列排列。
     * @since 24
     */
    OH_CAMERA_SENSOR_CFA_GRBG = 2,

    /**
     * RGGB（Red-Green-Green-Blue）滤色阵列排列。
     * @since 24
     */
    OH_CAMERA_SENSOR_CFA_RGGB = 3
} OH_Camera_SensorColorFilterArrangement;

/**
 * @brief 相机格式类型的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_Format {
    /**
     * RGBA 8888格式。
     */
    CAMERA_FORMAT_RGBA_8888 = 3,

    /**
     * DNG格式。
     * @since 24
     */
    CAMERA_FORMAT_DNG = 4,

    /**
     * 增强型DNG格式。
     * @since 26.0.0
     */
    CAMERA_FORMAT_DNG_XDRAW = 5,

    /**
     * YUV 420格式。
     */
    CAMERA_FORMAT_YUV_420_SP = 1003,

    /**
     * JPEG格式。
     */
    CAMERA_FORMAT_JPEG = 2000,

    /**
     * YCBCR P010 格式。
     * @since 12
     */
    CAMERA_FORMAT_YCBCR_P010 = 2001,

    /**
     * YCRCB P010 格式。
     * @since 12
     */
    CAMERA_FORMAT_YCRCB_P010 = 2002,

    /**
     * HEIC格式。
     * @since 23
     */
    CAMERA_FORMAT_HEIC = 2003,
} Camera_Format;

/**
 * @brief 闪光模式的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_FlashMode {
    /**
     * 关闭模式。
     */
    FLASH_MODE_CLOSE = 0,

    /**
     * 打开模式。
     */
    FLASH_MODE_OPEN = 1,

    /**
     * 自动模式。
     */
    FLASH_MODE_AUTO = 2,

    /**
     * 始终打开模式。
     */
    FLASH_MODE_ALWAYS_OPEN = 3
} Camera_FlashMode;

/**
 * @brief 闪光灯状态枚举。
 *
 * @since 24
 */
typedef enum OH_Camera_FlashState {
    /**
     * 闪光灯为不可用状态，为默认值。
     * @since 24
     */
   OH_CAMERA_FLASH_STATE_UNAVAILABLE = 0,

    /**
     * 闪光灯为可用状态。
     * @since 24
     */
    OH_CAMERA_FLASH_STATE_READY = 1,

    /**
     * 闪光灯已经被打开。
     * @since 24
     */
    OH_CAMERA_FLASH_STATE_FLASHING = 2
} OH_Camera_FlashState;

/**
 * @brief 曝光模式的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_ExposureMode {
    /**
     * 曝光模式未指定。
     * @since 24
     */
    EXPOSURE_MODE_UNSPECIFIED = -1,

    /**
     * 锁定曝光模式。 不支持曝光区域中心点设置。<br>设置该模式后，每次拍照时曝光都会默认锁定。
     */
    EXPOSURE_MODE_LOCKED = 0,

    /**
     * 自动曝光模式。支持曝光区域中心点设置，可以使用{@link OH_CaptureSession_SetMeteringPoint}接口设置曝光区域中心点。<br>设置该模式后，仅设置后的首次拍照生效。
     */
    EXPOSURE_MODE_AUTO = 1,

    /**
     * 连续自动曝光。<br>设置该模式后，拍照系统会根据每次的环境变化自动调整曝光。
     */
    EXPOSURE_MODE_CONTINUOUS_AUTO = 2,

    /**
     * 手动曝光模式。可以使用{@link OH_CaptureSession_SetExposureDuration}接口设置曝光时长。
     * @since 24
     */
    EXPOSURE_MODE_MANUAL = 3
} Camera_ExposureMode;

/**
 * @brief 曝光测光模式枚举。
 *
 * @since 24
 */
typedef enum OH_Camera_ExposureMeteringMode {
    /**
     * 矩阵测光模式。对整个画面测光，适用于自然风景拍摄。
     * @since 24
     */
    OH_CAMERA_EXPOSURE_METERING_MODE_MATRIX = 0,

    /** 
     * 中央测光模式。对画面中心区域测光，适用于人像拍摄。
     * @since 24
     */
    OH_CAMERA_EXPOSURE_METERING_MODE_CENTER = 1,

    /**
     * 点测光模式。对指定微小区域测光，适用于拍摄主体细节（如人物眼睛）。
     * @since 24
     */
    OH_CAMERA_EXPOSURE_METERING_MODE_SPOT = 2
} OH_Camera_ExposureMeteringMode;

/**
 * @brief 枚举相机曝光状态。
 *
 * @since 26.0.0
 */
typedef enum OH_Camera_ExposureState {
    /**
     * 表示曝光处于扫描状态。
     * @since 26.0.0
     */
    OH_CAMERA_EXPOSURE_STATE_SCAN = 0,

    /**
     * 表示曝光已经收敛。
     * @since 26.0.0
     */
    OH_CAMERA_EXPOSURE_STATE_CONVERGED = 1
} OH_Camera_ExposureState;

/**
 * @brief 白平衡模式枚举。
 * 
 * @since 20
 * @version 1.0
 */

typedef enum Camera_WhiteBalanceMode {
    /**
     * 白平衡模式：自动。
     */
    CAMERA_WHITE_BALANCE_MODE_AUTO = 0,

    /**
     * 白平衡模式：阴天。
     */
    CAMERA_WHITE_BALANCE_MODE_CLOUDY = 1,

    /**
     * 白平衡模式：白炽灯。
     */
    CAMERA_WHITE_BALANCE_MODE_INCANDESCENT = 2,

    /**
     * 白平衡模式：荧光。
     */
    CAMERA_WHITE_BALANCE_MODE_FLUORESCENT = 3,

    /**
     * 白平衡模式：晴天。
     */
    CAMERA_WHITE_BALANCE_MODE_DAYLIGHT = 4,

    /**
     * 白平衡模式：手动。
     */
    CAMERA_WHITE_BALANCE_MODE_MANUAL = 5,

    /**
     * 白平衡模式：锁定。
     */
    CAMERA_WHITE_BALANCE_MODE_LOCKED = 6,
} Camera_WhiteBalanceMode;

/**
 * @brief 聚焦模式的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_FocusMode {
    /**
     * 手动模式。
     */
    FOCUS_MODE_MANUAL = 0,

    /**
     * 连续自动模式。
     */
    FOCUS_MODE_CONTINUOUS_AUTO = 1,

    /**
     * 自动模式。
     */
    FOCUS_MODE_AUTO = 2,

    /**
     * 锁定模式。
     */
    FOCUS_MODE_LOCKED = 3
} Camera_FocusMode;

/**
 * @brief 焦点状态的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_FocusState {
    /**
     * 扫描状态。
     */
    FOCUS_STATE_SCAN = 0,

    /**
     * 聚焦状态。
     */
    FOCUS_STATE_FOCUSED = 1,

    /**
     * 非聚焦状态。
     */
    FOCUS_STATE_UNFOCUSED = 2
} Camera_FocusState;

/**
 * @brief 录像防抖模式的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_VideoStabilizationMode {
    /**
     * 关闭录像防抖。
     */
    STABILIZATION_MODE_OFF = 0,

    /**
     * LOW模式，提供基本的防抖效果。
     */
    STABILIZATION_MODE_LOW = 1,

    /**
     * MIDDLE模式，表示通过算法可以获得比LOW模式更好的效果。
     */
    STABILIZATION_MODE_MIDDLE = 2,

    /**
     * HIGH模式，表示通过算法可以获得比MIDDLE模式更好的效果。
     */
    STABILIZATION_MODE_HIGH = 3,

    /**
     * 自动选择模式，HDF相机可用。
     */
    STABILIZATION_MODE_AUTO = 4
} Camera_VideoStabilizationMode;

/**
 * @brief 图像旋转角度的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_ImageRotation {
    /**
     * 捕获图像旋转0度。<br> 从API version 23开始，推荐使用新枚举值{@link CAMERA_IMAGE_ROTATION_0}。
     */
    IAMGE_ROTATION_0 = 0,

    /**
     * 捕获图像旋转0度。
     * @since 23
     */
    CAMERA_IMAGE_ROTATION_0 = 0,

    /**
     * 捕获图像旋转90度。<br> 从API version 23开始，推荐使用新枚举值{@link CAMERA_IMAGE_ROTATION_90}。
     */
    IAMGE_ROTATION_90 = 90,

    /**
     * 捕获图像旋转90度。
     * @since 23
     */
    CAMERA_IMAGE_ROTATION_90 = 90,

    /**
     * 捕获图像旋转180度。<br> 从API version 23开始，推荐使用新枚举值{@link CAMERA_IMAGE_ROTATION_180}。
     */
    IAMGE_ROTATION_180 = 180,

    /**
     * 捕获图像旋转180度。
     * @since 23
     */
    CAMERA_IMAGE_ROTATION_180 = 180,

    /**
     * 捕获图像旋转270度。<br> 从API version 23开始，推荐使用新枚举值{@link CAMERA_IMAGE_ROTATION_270}。
     */
    IAMGE_ROTATION_270 = 270,

    /**
     * 捕获图像旋转270度。
     * @since 23
     */
    CAMERA_IMAGE_ROTATION_270 = 270
} Camera_ImageRotation;

/**
 * @brief 图像质量等级的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_QualityLevel {
    /**
     * 高图像质量。
     */
    QUALITY_LEVEL_HIGH = 0,

    /**
     * 中等图像质量。
     */
    QUALITY_LEVEL_MEDIUM = 1,

    /**
     * 低图像质量。
     */
    QUALITY_LEVEL_LOW = 2
} Camera_QualityLevel;

/**
 * @brief 元数据对象类型的枚举。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_MetadataObjectType {
    /**
     * 元数据的对象类型，用于人脸检测。<br> 从API version 23开始，推荐使用新枚举值{@link CAMERA_METADATA_OBJECT_TYPE_FACE_DETECTION}。
     */
    FACE_DETECTION = 0,

    /**
     * 元数据的对象类型，用于人脸检测。
     * @since 23
     */
    CAMERA_METADATA_OBJECT_TYPE_FACE_DETECTION = 0,

    /**
     * 元数据的对象类型，用于人体检测。
     * @since 23
     */
    CAMERA_METADATA_OBJECT_TYPE_HUMAN_BODY = 1,

    /**
     * 元数据的对象类型，用于猫脸检测。
     * @since 26.0.0
     */
    CAMERA_METADATA_OBJECT_TYPE_CAT_FACE = 2,

    /**
     * 元数据的对象类型，用于猫体检测。
     * @since 26.0.0
     */
    CAMERA_METADATA_OBJECT_TYPE_CAT_BODY = 3,

    /**
     * 元数据的对象类型，用于狗脸检测。
     * @since 26.0.0
     */
    CAMERA_METADATA_OBJECT_TYPE_DOG_FACE = 4,

    /**
     * 元数据的对象类型，用于狗体检测。
     * @since 26.0.0
     */
    CAMERA_METADATA_OBJECT_TYPE_DOG_BODY = 5,

    /**
     * 元数据的对象类型，用于显著性物体检测。
     * @since 26.0.0
     */
    CAMERA_METADATA_OBJECT_TYPE_SALIENT_DETECTION = 6,

    /**
     * 元数据的对象类型，用于二维码检测。
     * @since 26.0.0
     */
    CAMERA_METADATA_OBJECT_TYPE_BAR_CODE_DETECTION = 7,

    /**
     * 元数据的对象类型，用于基础人脸检测。
     * @since 26.0.0
     */
    CAMERA_METADATA_OBJECT_TYPE_BASIC_FACE_DETECTION = 8
} Camera_MetadataObjectType;

/**
 * @brief 手电筒模式的枚举。
 * 
 * @since 12
 * @version 1.0
 */
typedef enum Camera_TorchMode {
    /**
     * 设备手电筒常关。<br> 从API version 23开始，推荐使用新枚举值{@link CAMERA_TORCH_MODE_OFF}。
     */
    OFF = 0,

    /**
     * 设备手电筒常关。
     * @since 23
     */
    CAMERA_TORCH_MODE_OFF = 0,

    /**
     * 设备手电筒常开。<br> 从API version 23开始，推荐使用新枚举值{@link CAMERA_TORCH_MODE_ON}。
     */
    ON = 1,

    /**
     * 设备手电筒常开。
     * @since 23
     */
    CAMERA_TORCH_MODE_ON = 1,

    /**
     * 设备手电筒自动模式，将根据环境光照水平打开手电筒。<br> 从API version 23开始，推荐使用新枚举值{@link CAMERA_TORCH_MODE_AUTO}。
     */
    AUTO = 2,

    /**
     * 设备手电筒自动模式，将根据环境光照水平打开手电筒。
     * @since 23
     */
    CAMERA_TORCH_MODE_AUTO = 2
} Camera_TorchMode;

/**
 * @brief 平滑变焦模式的枚举。
 * 
 * @since 12
 * @version 1.0
 */
typedef enum Camera_SmoothZoomMode {
    /**
     * 贝塞尔曲线模式。<br> 从API version 23开始，推荐使用新枚举值{@link CAMERA_SMOOTH_ZOOM_MODE_NORMAL}。
     */
    NORMAL = 0,

    /**
     * 贝塞尔曲线模式。
     * @since 23
     */
    CAMERA_SMOOTH_ZOOM_MODE_NORMAL = 0
} Camera_SmoothZoomMode;

/**
 * @brief 预配置照片分辨率的枚举。
 * 
 * @since 12
 * @version 1.0
 */
typedef enum Camera_PreconfigType {
    /**
     * 预配置照片分辨率为720P。
     */
    PRECONFIG_720P = 0,

    /**
     * 预配置照片分辨率为1080P。
     */
    PRECONFIG_1080P = 1,

    /**
     * 预配置照片分辨率为4K。
     */
    PRECONFIG_4K = 2,

    /**
     * 预配置照片为高质量。
     */
    PRECONFIG_HIGH_QUALITY = 3,
    
    /**
     * 预配置支持预览高动态范围显示和HDR动图拍摄。
     * @since 23
     */
    PRECONFIG_HIGH_QUALITY_PHOTOSESSION_BT2020 = 4
} Camera_PreconfigType;

/**
 * @brief 预配置照片比例的枚举。
 * 
 * @since 12
 * @version 1.0
 */
typedef enum Camera_PreconfigRatio {
    /**
     * 预配置照片比例为1:1。
     */
    PRECONFIG_RATIO_1_1 = 0,

    /**
     * 预配置照片比例为4:3。
     */
    PRECONFIG_RATIO_4_3 = 1,

    /**
     * 预配置照片比例为16:9。
     */
    PRECONFIG_RATIO_16_9 = 2
} Camera_PreconfigRatio;

/**
 * @brief 远程设备类型枚举。
 *
 * @since 15
 * @version 1.0
 */
typedef enum Camera_HostDeviceType {
    /**
     * 未知设备类型。
     */
    HOST_DEVICE_TYPE_UNKNOWN_TYPE = 0,

    /**
     * 手机设备。
     */
    HOST_DEVICE_TYPE_PHONE = 0x0E,

    /**
     * 平板设备。
     */
    HOST_DEVICE_TYPE_TABLET = 0x11
} Camera_HostDeviceType;

/**
 * @brief 大小参数。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Size {
    /**
     * 宽度，单位为像素。
     */
    uint32_t width;

    /**
     * 高度，单位为像素。
     */
    uint32_t height;
} Camera_Size;

/**
 * @brief 相机流的配置文件。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Profile {
    /**
     * 相机格式。
     */
    Camera_Format format;

    /**
     * 图片大小。
     */
    Camera_Size size;
} Camera_Profile;

/**
 * @brief 帧速率范围。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_FrameRateRange {
    /**
     * 最小帧速率，单位帧每秒。
     */
    uint32_t min;

    /**
     * 最大帧速率，单位帧每秒。
     */
    uint32_t max;
} Camera_FrameRateRange;

/**
 * @brief 录像配置文件。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_VideoProfile {
    /**
     * 相机格式。
     */
    Camera_Format format;

    /**
     * 图片大小。
     */
    Camera_Size size;

    /**
     * 帧速率，单位为fps（每秒帧数）。
     */
    Camera_FrameRateRange range;
} Camera_VideoProfile;

/**
 * @brief 相机输出能力。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_OutputCapability {
    /**
     * 预览配置文件列表。
     */
    Camera_Profile** previewProfiles;

    /**
     * 预览配置文件列表的大小。
     */
    uint32_t previewProfilesSize;

    /**
     * 拍照配置文件列表。<br> 配置文件中的size设置的是相机分辨率宽高，非实际出图宽高。
     */
    Camera_Profile** photoProfiles;

    /**
     * 拍照配置文件列表的大小。
     */
    uint32_t photoProfilesSize;

    /**
     * 录像配置文件列表。
     */
    Camera_VideoProfile** videoProfiles;

    /**
     * 录像配置文件列表的大小。
     */
    uint32_t videoProfilesSize;

    /**
     * 元数据对象类型列表。
     */
    Camera_MetadataObjectType** supportedMetadataObjectTypes;

    /**
     * 元数据对象类型列表的大小。
     */
    uint32_t metadataProfilesSize;
} Camera_OutputCapability;

/**
 * @brief 相机设备对象。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Device {
    /**
     * 相机id属性。
     */
    char* cameraId;

    /**
     * 相机位置属性。
     */
    Camera_Position cameraPosition;

    /**
     * 相机类型属性。
     */
    Camera_Type cameraType;

    /**
     * 相机连接类型属性。
     */
    Camera_Connection connectionType;
} Camera_Device;

/**
 * @brief 相机状态信息。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_StatusInfo {
    /**
     * 相机实例。
     */
    Camera_Device* camera;

    /**
     * 当前相机状态。
     */
    Camera_Status status;
} Camera_StatusInfo;

/**
 * @brief 点参数。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Point {
    /**
     * X坐标，取值范围为[0,1]。
     */
    double x;

    /**
     * Y坐标，取值范围为[0,1]。
     */
    double y;
} Camera_Point;

/**
 * @brief 拍照位置。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Location {
    /**
     * 纬度。
     */
    double latitude;

    /**
     * 经度。
     */
    double longitude;

    /**
     * 海拔高度，单位为米。
     */
    double altitude;
} Camera_Location;

/**
 * @brief 要设置的拍照捕获选项。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_PhotoCaptureSetting {
    /**
     * 拍照图像质量。
     */
    Camera_QualityLevel quality;

    /**
     * 拍照旋转角度。
     */
    Camera_ImageRotation rotation;

    /**
     * 拍照位置。
     */
    Camera_Location* location;

    /**
     * 设置镜像拍照功能开关。<br> true为打开，false为关闭，默认为false。
     */
    bool mirror;
} Camera_PhotoCaptureSetting;

/**
 * @brief 帧快门回调信息。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_FrameShutterInfo {
    /**
     * 捕获id。
     */
    int32_t captureId;

    /**
     * 帧的时间戳，单位毫秒。
     */
    uint64_t timestamp;
} Camera_FrameShutterInfo;

/**
 * @brief 捕获结束信息。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_CaptureEndInfo {
    /**
     * 捕获id。
     */
    int32_t captureId;

    /**
     * 帧数。
     */
    int64_t frameCount;
} Camera_CaptureEndInfo;

/**
 * @brief 相机矩形。用于各类检测对象的矩形框绘制。<br> 检测点坐标系以设备横向位置（充电口朝右）为基准。<br> 坐标系原点位于左上角 (0, 0)，右下角对应相机预览流的像素分辨率。<br> 所有参数均为整型像素值，
 * 其中topLeftX与topLeftY表示矩形左上角坐标，width与height分别表示矩形的宽高。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Rect {
    /**
     * 矩形左上角的X坐标。<br>取值范围：[0, 预览流宽度]，例如对于1920*1440的预览流，取值范围为[0,1920]。
     * @since 11
     */
    int32_t topLeftX;

    /**
     * 矩形左上角的Y坐标。<br>取值范围：[0, 预览流高度]，例如对于 1920*1440 的预览流，取值范围为[0,1440]。
     * @since 11
     */
    int32_t topLeftY;

    /**
     * 矩形宽度。<br>该值不超过坐标系X轴的上限，即topLeftX的最大值。
     * @since 11
     */
    int32_t width;

    /**
     * 矩形高度。<br>该值不超过坐标系Y轴的上限，即topLeftY的最大值。
     * @since 11
     */
    int32_t height;
} Camera_Rect;

/**
 * @brief 元数据对象基础。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_MetadataObject {
    /**
     * 元数据对象类型。
     */
    Camera_MetadataObjectType type;

    /**
     * 元数据对象时间戳，单位为纳秒（ns）。
     */
    int64_t timestamp;

    /**
     * 检测到的元数据对象的轴对齐边界框。
     */
    Camera_Rect* boundingBox;
} Camera_MetadataObject;

/**
 * @brief 手电筒状态信息。
 * 
 * @since 12
 * @version 1.0
 */
typedef struct Camera_TorchStatusInfo {
    /**
     * 手电筒是否可用，true表示可用，false表示不可用。
     */
    bool isTorchAvailable;

    /**
     * 手电筒是否激活，true表示激活，false表示未激活。
     */
    bool isTorchActive;

    /**
     * 手电筒亮度等级。取值范围为[0,1]，越靠近1，亮度越大。
     */
    float torchLevel;
} Camera_TorchStatusInfo;

/**
 * @brief 平滑变焦参数信息。
 * 
 * @since 12
 * @version 1.0
 */
typedef struct Camera_SmoothZoomInfo {
    /**
     * 平滑变焦总时长（以毫秒为单位）。
     */
    int32_t duration;
} Camera_SmoothZoomInfo;

/**
 * @brief 拍照开始信息。
 * 
 * @since 12
 * @version 1.0
 */
typedef struct Camera_CaptureStartInfo {
    /**
     * 捕获id。
     */
    int32_t captureId;

    /**
     * 预估的单次拍照底层出sensor采集帧时间，如果上报-1，代表没有预估时间。
     */
    int64_t time;
} Camera_CaptureStartInfo;

/**
 * @brief 拍照曝光结束信息。
 * 
 * @since 12
 * @version 1.0
 */
typedef struct Camera_FrameShutterEndInfo {
    /**
     * 捕获id。
     */
    int32_t captureId;
} Camera_FrameShutterEndInfo;

/**
* @brief 折叠状态枚举。
* 
* @since 13
* @version 1.0
*/
typedef enum Camera_FoldStatus {
    /**
     * 不可折叠状态。<br> 从API version 23开始，推荐使用新枚举值{@link CAMERA_FOLD_STATUS_NON_FOLDABLE}。
     */
    NON_FOLDABLE = 0,

    /**
     * 不可折叠状态。
     * @since 23
     */
    CAMERA_FOLD_STATUS_NON_FOLDABLE = 0,

    /**
     * 展开状态。<br> 从API version 23开始，推荐使用新枚举值{@link CAMERA_FOLD_STATUS_EXPANDED}。
     */
    EXPANDED = 1,

    /**
     * 展开状态。
     * @since 23
     */
    CAMERA_FOLD_STATUS_EXPANDED = 1,

    /**
     * 折叠状态。<br> 从API version 23开始，推荐使用新枚举值{@link CAMERA_FOLD_STATUS_FOLDED}。
     */
    FOLDED = 2,

    /**
     * 折叠状态。
     * @since 23
     */
    CAMERA_FOLD_STATUS_FOLDED = 2
} Camera_FoldStatus;

/**
 * @brief 折叠状态信息。
 * 
 * @since 13
 * @version 1.0
 */
typedef struct Camera_FoldStatusInfo {
    /**
     * 相机实例列表。
     */
    Camera_Device** supportedCameras;

    /**
     * 相机列表数量。
     */
    uint32_t cameraSize;

    /**
     * 当前折叠状态。
     */
    Camera_FoldStatus foldStatus;
} Camera_FoldStatusInfo;

/**
 * @brief 自动设备切换状态信息。
 *
 * @since 13
 * @version 1.0
 */
typedef struct Camera_AutoDeviceSwitchStatusInfo {
    /**
     * 设备是否已切换，true表示已切换，false表示未切换。
     */
    bool isDeviceSwitched;

    /**
     * 设备功能是否改变，true表示已改变，false表示未改变。
     */
    bool isDeviceCapabilityChanged;
} Camera_AutoDeviceSwitchStatusInfo;

/**
 * @brief 录像质量优先级的枚举。
 *
 * @since 14
 * @version 1.0
 */
typedef enum Camera_QualityPrioritization {
    /**
     * 高录像质量。
     */
    HIGH_QUALITY = 0,

    /**
     * 功耗平衡录像质量。
     */
    POWER_BALANCE = 1
} Camera_QualityPrioritization;

/**
 * @brief 相机并发状态的枚举。
 *
 * @since 18
 * @version 1.0
 */
typedef enum Camera_ConcurrentType {
    /**
     * 相机限制并发。
     */
    CAMERA_CONCURRENT_TYPE_LIMITED_CAPABILITY  = 0,

    /**
     * 相机全量并发。
     */
    CAMERA_CONCURRENT_TYPE_FULL_CAPABILITY = 1
} Camera_ConcurrentType;

/**
 * @brief 相机并发能力信息。
 *
 * @since 18
 * @version 1.0
 */
typedef struct Camera_ConcurrentInfo {
    /**
     * 相机实例。
     */
    Camera_Device camera;

    /**
     * 相机并发状态。
     */
    Camera_ConcurrentType type;

    /**
     * 相机并发支持的模式。
     */
    Camera_SceneMode* sceneModes;

    /**
     * 相机输出能力集。
     */
    Camera_OutputCapability* outputCapabilities;

    /**
     * 相机输出能力集大小。
     */
    uint32_t modeAndCapabilitySize;
} Camera_ConcurrentInfo;

/**
 * @brief 系统压力等级的枚举。
 * 
 * @since 20
 * @version 1.0
 */

typedef enum Camera_SystemPressureLevel {
    /**
     * 系统压力正常。
     */
    SYSTEM_PRESSURE_NORMAL = 0,

    /**
     * 系统压力升高，但是系统不会主动管控。
     */
    SYSTEM_PRESSURE_MILD = 1,

    /**
     * 系统压力可能对图像总质量、性能产生影响。
     */
    SYSTEM_PRESSURE_SEVERE = 2,

    /**
     * 系统图像质量、性能产生显著影响。
     */
    SYSTEM_PRESSURE_CRITICAL = 3,

    /**
     * 系统压力过高，停止工作。
     */
    SYSTEM_PRESSURE_SHUTDOWN = 4
} Camera_SystemPressureLevel;

/**
 * @brief 拍照画质优先策略枚举。
 * 
 * @since 21
 * @version 1.0
 */
typedef enum Camera_PhotoQualityPrioritization {
    /**
     * 画质优先，拍照需要较长的时间，以输出高画质的图片。
     */
    CAMERA_PHOTO_QUALITY_PRIORITIZATION_HIGH_QUALITY = 0,

    /**
     * 性能优先，会降低画质来提升拍照的速度。
     */
    CAMERA_PHOTO_QUALITY_PRIORITIZATION_SPEED = 1
} Camera_PhotoQualityPrioritization;

/**
 * @brief 控制器效果类型枚举。
 * 
 * @since 20
 * @version 1.0
 */
typedef enum Camera_ControlCenterEffectType {
    /**
     * 控制器效果类型：美颜。
     */
    CONTROL_CENTER_EFFECT_TYPE_BEAUTY = 0,

    /**
     * 控制器效果类型：人像虚化。
     */
    CONTROL_CENTER_EFFECT_TYPE_PORTRAIT = 1,

    /**
     * 控制器效果类型：自动对焦。
     * @since 24
     */
    CONTROL_CENTER_EFFECT_TYPE_AUTO_FRAMING = 2,

    /**
     * 控制器效果类型：XMAGE风格。
     * @since 26.0.0
     */
    CONTROL_CENTER_EFFECT_TYPE_COLOR_EFFECT = 3
} Camera_ControlCenterEffectType;

/**
 * @brief 控制器效果激活状态信息。
 * 
 * @since 20
 * @version 1.0
 */
typedef struct Camera_ControlCenterStatusInfo {
    /**
     * 控制器效果类型。
     */
    Camera_ControlCenterEffectType effectType;

    /**
     * 控制器是否激活。true表示激活，false表示未激活。
     */
    bool isActive;
} Camera_ControlCenterStatusInfo;

/**
 * @brief 创建CameraManager实例。
 * 
 * @param cameraManager 如果方法调用成功，将创建Camera_Manager实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_Camera_GetCameraManager(Camera_Manager** cameraManager);

/**
 * @brief 删除CameraManager实例。
 * 
 * @param cameraManager 要删除的Camera_Manager实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 11
 */
Camera_ErrorCode OH_Camera_DeleteCameraManager(Camera_Manager* cameraManager);

/**
 * @brief 相机设备的查询信息。
 * 
 * @since 23
 * @version 1.0
 */
typedef struct Camera_DeviceQueryInfo {
    /**
     * 相机类型属性列表。
     */
    Camera_Type* cameraType;
    /**
     * 相机类型属性列表的大小。
     */
    uint32_t cameraTypeSize;
    /**
     * 相机位置属性。
     */
    Camera_Position cameraPosition;
    /**
     * 相机连接类型属性。
     */
    Camera_Connection connectionType;
} Camera_DeviceQueryInfo;

/**
 * @brief 相机镜头遮挡、脏污检测结果。
 * 
 * @since 23
 * @version 1.0
 */
typedef struct Camera_OcclusionDetectionResult {
    /**
     * 检查相机镜头是否被遮挡。true表示被遮挡，false表示未被遮挡。
     */
    bool isCameraOccluded;

    /**
     * 检查相机镜头是否有脏污。true表示有脏污，false表示没有脏污。
     */
    bool isCameraLensDirty;
} Camera_OcclusionDetectionResult;

/**
 * @brief 变焦范围配置。
 * 
 * @since 24
 */
typedef struct OH_Camera_ZoomRange {
    /**
     * 最小变焦值。
     * @since 24
     */
    float minZoom;

    /**
     * 最大变焦值。
     * @since 24
    */
    float maxZoom;
} OH_Camera_ZoomRange;

/**
 * @brief 物理光圈配置。
 *
 * @since 24
 */
typedef struct OH_Camera_PhysicalAperture {
    /**
     * 变焦范围。
     * @since 24
     */
    OH_Camera_ZoomRange zoomRange;

    /**
     * 支持的光圈值数组。
     * @since 24
     */
    float* apertures;

    /**
     * 光圈值数量。
     * @since 24
     */
    size_t apertureCount;
} OH_Camera_PhysicalAperture;

/**
 * @brief 光学防抖（Optical Image Stabilization）模式枚举。
 *
 * @since 24
 * @version 1.0
 */
typedef enum OH_Camera_OISMode {
    /**
     * 关闭光学防抖模式。
     * @since 24
     */
    OH_CAMERA_OIS_MODE_OFF = 0,

    /**
     * 自动光学防抖模式。
     * @since 24
     */
    OH_CAMERA_OIS_MODE_AUTO = 1,

    /** 
     * 手动光学防抖模式。
     * @since 24
     */
    OH_CAMERA_OIS_MODE_CUSTOM = 2
} OH_Camera_OISMode;

/**
 * @brief 光学防抖（OIS）轴枚举。
 *
 * @since 24
 * @version 1.0
 */
typedef enum OH_Camera_OISAxes {
    /**
     * 俯仰轴：控制相机机身上下旋转，即机身围绕与镜头水平方向的轴旋转。
     * @since 24
     */
    OH_CAMERA_OIS_AXES_PITCH = 0,

    /**
     * 偏航轴：控制相机机身左右旋转，即机身围绕与镜头垂直方向的轴旋转。
     * @since 24
     */
    OH_CAMERA_OIS_AXES_YAW = 1
} OH_Camera_OISAxes;

/**
 * @brief 描述变焦点信息。
 *
 * @since 26.0.0
 */
typedef struct OH_Camera_ZoomPointInfo {
    /**
     * 变焦比例。
     * @since 26.0.0
     */
    float zoomRatio;

    /**
     * 等效焦距。
     * @since 26.0.0
     */
    uint32_t equivalentFocalLength;
} OH_Camera_ZoomPointInfo;

/**
 * @brief 矩形定义。<br> 检测点应在0-1坐标系内，该坐标系左上角为(0，0)，右下角为(1，1)。<br> 此坐标系以设备充电口在右侧时的横向设备方向为基准。<br>
 * 例如应用的预览界面布局以设备充电口在下侧时的竖向方向为基准，布局宽高为(w，h)，返回点为(x，y)，则转换后的坐标点为(1-y，x)。
 *
 * @since 26.0.0
 * @version 1.0
 */
typedef struct OH_Camera_Rect_Ext {
    /**
     * 矩形左上角的X坐标，范围[0, 1]。
     * @since 26.0.0
     */
    double topLeftX;

    /**
     * 矩形左上角的Y坐标，范围[0, 1]。
     * @since 26.0.0
     */
    double topLeftY;

    /**
     * 矩形宽度，范围[0, 1]。
     * @since 26.0.0
     */
    double width;

    /**
     * 矩形高度，范围[0, 1]。
     * @since 26.0.0
     */
    double height;
} OH_Camera_Rect_Ext;

/**
 * @brief 元数据对象情绪类型枚举。
 *
 * @since 26.0.0
 * @version 1.0
 */
typedef enum OH_Camera_MetadataObjectEmotion {
    /**
     * 平静。
     * @since 26.0.0
     */
    OH_CAMERA_METADATA_OBJECT_EMOTION_NEUTRAL = 0,

    /**
     * 悲伤。
     * @since 26.0.0
     */
    OH_CAMERA_METADATA_OBJECT_EMOTION_SADNESS = 1,

    /**
     * 微笑。
     * @since 26.0.0
     */
    OH_CAMERA_METADATA_OBJECT_EMOTION_SMILE = 2,

    /**
     * 惊讶。
     * @since 26.0.0
     */
    OH_CAMERA_METADATA_OBJECT_EMOTION_SURPRISE = 3
} OH_Camera_MetadataObjectEmotion;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_CAMERA_H
/** @} */

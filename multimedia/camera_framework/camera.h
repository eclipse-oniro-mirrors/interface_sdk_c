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
 * @brief Defines the basic APIs of the camera.
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
 * @brief The struct describes the camera manager.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Manager Camera_Manager;

/**
 * @brief Enumerates the camera error codes.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_ErrorCode {
    /**
     * The camera is normal.
     */
    CAMERA_OK = 0,

    /**
     * A parameter is missing or the parameter type is incorrect.
     */
    CAMERA_INVALID_ARGUMENT = 7400101,

    /**
     * The operation is not allowed.
     */
    CAMERA_OPERATION_NOT_ALLOWED = 7400102,

    /**
     * The session is not configured.
     */
    CAMERA_SESSION_NOT_CONFIG = 7400103,

    /**
     * The session is not running.
     */
    CAMERA_SESSION_NOT_RUNNING = 7400104,

    /**
     * The session configuration is locked.
     */
    CAMERA_SESSION_CONFIG_LOCKED = 7400105,

    /**
     * The device setting is locked.
     */
    CAMERA_DEVICE_SETTING_LOCKED = 7400106,

    /**
     * The device is already started.
     */
    CAMERA_CONFLICT_CAMERA = 7400107,

    /**
     * The camera is disabled for security reasons.
     */
    CAMERA_DEVICE_DISABLED = 7400108,

    /**
     * The camera is preempted.
     */
    CAMERA_DEVICE_PREEMPTED = 7400109,

    /**
     * The configuration conflicts with the current configuration.
     *
     * @since 12
     */
    CAMERA_UNRESOLVED_CONFLICTS_WITH_CURRENT_CONFIGURATIONS = 7400110,

    /**
     * The camera service is abnormal, for example, no camera permission, camera service restart, or abnormal cross-
     * process invocation.
     */
    CAMERA_SERVICE_FATAL_ERROR = 7400201
} Camera_ErrorCode;

/**
 * @brief Enumerates the camera statuses.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_Status {
    /**
     * A camera appears.
     */
    CAMERA_STATUS_APPEAR = 0,

    /**
     * The camera disappears.
     */
    CAMERA_STATUS_DISAPPEAR = 1,

    /**
     * The camera is available.
     */
    CAMERA_STATUS_AVAILABLE = 2,

    /**
     * The camera is unavailable.
     */
    CAMERA_STATUS_UNAVAILABLE = 3
} Camera_Status;

/**
 * @brief Enumerates the camera scene modes.
 * 
 * @since 12
 * @version 1.0
 */
typedef enum Camera_SceneMode {
    /**
     * Normal photo mode.
     */
    NORMAL_PHOTO = 1,

    /**
     * Normal video mode.
     */
    NORMAL_VIDEO = 2,

    /**
     * Secure mode, which is mainly provided for high-security applications like banking that require features such as
     * biometric verification. The secure mode requires the encryption algorithm framework and trusted application
     * services. For details,
     * see [Device Certificate Kit](docroot://security/DeviceCertificateKit/device-certificate-kit-intro.md).
     */
    SECURE_PHOTO = 12
} Camera_SceneMode;

/**
 * @brief Enumerates the camera positions.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_Position {
    /**
     * A camera that does not have a fixed orientation relative to the device screen.
     */
    CAMERA_POSITION_UNSPECIFIED = 0,

    /**
     * Rear camera.
     */
    CAMERA_POSITION_BACK = 1,

    /**
     * Front camera.
     */
    CAMERA_POSITION_FRONT = 2
} Camera_Position;

/**
 * @brief Enumerates the camera types.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_Type {
    /**
     * Default camera type.
     */
    CAMERA_TYPE_DEFAULT = 0,

    /**
     * Wide camera.
     */
    CAMERA_TYPE_WIDE_ANGLE = 1,

    /**
     * Ultra-wide camera.
     */
    CAMERA_TYPE_ULTRA_WIDE = 2,

    /**
     * Telephoto camera.
     */
    CAMERA_TYPE_TELEPHOTO = 3,

    /**
     * Camera with depth of field information.
     */
    CAMERA_TYPE_TRUE_DEPTH = 4
} Camera_Type;

/**
 * @brief Enumerates the camera connection types.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_Connection {
    /**
     * Built-in camera.
     */
    CAMERA_CONNECTION_BUILT_IN = 0,

    /**
     * Camera connected using USB.
     */
    CAMERA_CONNECTION_USB_PLUGIN = 1,

    /**
     * Remote camera.
     */
    CAMERA_CONNECTION_REMOTE = 2
} Camera_Connection;

/**
 * @brief Sensor color filter arrangement.
 *
 * @since 24
 */
typedef enum OH_Camera_SensorColorFilterArrangement{
    /**
     * Blue-Green-Green-Red (BGGR) filter arrangement.
     * @since 24
     */
    OH_CAMERA_SENSOR_CFA_BGGR = 0,

    /**
     * Green-Blue-Red-Green (GBRG) filter arrangement.
     * @since 24
     */
    OH_CAMERA_SENSOR_CFA_GBRG = 1,

    /**
     * Green-Red-Green-Blue (GRBG) filter arrangement.
     * @since 24
     */
    OH_CAMERA_SENSOR_CFA_GRBG = 2,

    /**
     * Red-Green-Green-Blue (RGGB) filter arrangement. 
     * @since 24
     */
    OH_CAMERA_SENSOR_CFA_RGGB = 3
} OH_Camera_SensorColorFilterArrangement;

/**
 * @brief Enumerates the camera output formats.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_Format {
    /**
     * RGBA 8888.
     */
    CAMERA_FORMAT_RGBA_8888 = 3,

    /**
     * DNG Format.
     * @since 24
     */
    CAMERA_FORMAT_DNG = 4,

    /**
     * YUV 420 SP.
     */
    CAMERA_FORMAT_YUV_420_SP = 1003,

    /**
     * JPEG.
     */
    CAMERA_FORMAT_JPEG = 2000,

    /**
     * YCBCR P010.
     * 
     * @since 12
     */
    CAMERA_FORMAT_YCBCR_P010 = 2001,

    /**
     * YCRCB P010.
     * 
     * @since 12
     */
    CAMERA_FORMAT_YCRCB_P010 = 2002,

    /**
     * HEIC.
     * 
     * @since 23
     */
    CAMERA_FORMAT_HEIC = 2003,
} Camera_Format;

/**
 * @brief Enumerates the flash modes.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_FlashMode {
    /**
     * The flash is off.
     */
    FLASH_MODE_CLOSE = 0,

    /**
     * The flash is on.
     */
    FLASH_MODE_OPEN = 1,

    /**
     * The flash is auto.
     */
    FLASH_MODE_AUTO = 2,

    /**
     * The flash is steady on.
     */
    FLASH_MODE_ALWAYS_OPEN = 3
} Camera_FlashMode;

/**
 * @brief Enum for flash state.
 *
 * @since 24
 */
typedef enum OH_Camera_FlashState {
    /**
     * Flash is unavailable, default value.
     * @since 24
     */
   OH_CAMERA_FLASH_STATE_UNAVAILABLE = 0,

    /**
     * This status indicates that the flash is available.
     * @since 24
     */
    OH_CAMERA_FLASH_STATE_READY = 1,

    /**
     * This status indicates that flashing can be performed.
     * @since 24
     */
    OH_CAMERA_FLASH_STATE_FLASHING = 2
} OH_Camera_FlashState;

/**
 * @brief Enumerates the exposure modes.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_ExposureMode {
    /**
     * Unspecified exposure.
     * 
     * @since 24
     */
    EXPOSURE_MODE_UNSPECIFIED = -1,

    /**
     * Exposure locked. The metering point cannot be set.<br>After this mode is used, the exposure will be locked by
     * default for each photo capture.
     */
    EXPOSURE_MODE_LOCKED = 0,

    /**
     * Auto exposure. The metering point can be set by calling {@link OH_CaptureSession_SetMeteringPoint}.
     * 
     * After this mode is used, it takes effect only for the first photo capture.
     */
    EXPOSURE_MODE_AUTO = 1,

    /**
     * Continuous auto exposure.<br>After this mode is used, the camera system automatically adjusts the exposure based
     * on the environment changes each time.
     */
    EXPOSURE_MODE_CONTINUOUS_AUTO = 2,

    /**
     * Manual exposure mode.
     * @since 24
     */
    EXPOSURE_MODE_MANUAL = 3
} Camera_ExposureMode;

/**
 * @brief Enum for exposure metering mode.
 *
 * @since 24
 */
typedef enum OH_Camera_ExposureMeteringMode {
    /**
     * Matrix metering mode: Measures the light in the whole frame, ideal for shooting natural landscapes.
     * @since 24
     */
    OH_CAMERA_EXPOSURE_METERING_MODE_MATRIX = 0,

    /** 
     * Center metering mode: Focuses in on light near the center of the screen, ideal for shooting portraits.
     * @since 24
     */
    OH_CAMERA_EXPOSURE_METERING_MODE_CENTER = 1,

    /**
     * Spot metering mode: Focuses in on light from a specific tiny region, such as a subject's eyes.
     * @since 24
     */
    OH_CAMERA_EXPOSURE_METERING_MODE_SPOT = 2
} OH_Camera_ExposureMeteringMode;

/**
 * @brief Enumerates camera exposure states.
 * @since 26.0.0
 */
typedef enum OH_Camera_ExposureState {
    /**
     * Indicates that the exposure is in scanning state.
     * @since 26.0.0
     */
    OH_CAMERA_EXPOSURE_STATE_SCAN = 0,

    /**
     * Indicates that the exposure has converged.
     * @since 26.0.0
     */
    OH_CAMERA_EXPOSURE_STATE_CONVERGED = 1
} OH_Camera_ExposureState;

/**
 * @brief Enumerates the white balance modes.
 * 
 * @since 20
 * @version 1.0
 */

typedef enum Camera_WhiteBalanceMode {
    /**
     * Automatic.
     */
    CAMERA_WHITE_BALANCE_MODE_AUTO = 0,

    /**
     * Cloudy.
     */
    CAMERA_WHITE_BALANCE_MODE_CLOUDY = 1,

    /**
     * Incandescent light.
     */
    CAMERA_WHITE_BALANCE_MODE_INCANDESCENT = 2,

    /**
     * Fluorescence light.
     */
    CAMERA_WHITE_BALANCE_MODE_FLUORESCENT = 3,

    /**
     * Daylight.
     */
    CAMERA_WHITE_BALANCE_MODE_DAYLIGHT = 4,

    /**
     * Manual.
     */
    CAMERA_WHITE_BALANCE_MODE_MANUAL = 5,

    /**
     * Locked.
     */
    CAMERA_WHITE_BALANCE_MODE_LOCKED = 6,
} Camera_WhiteBalanceMode;

/**
 * @brief Enumerates the focus modes.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_FocusMode {
    /**
     * Manual focus.
     */
    FOCUS_MODE_MANUAL = 0,

    /**
     * Continuous auto focus.
     */
    FOCUS_MODE_CONTINUOUS_AUTO = 1,

    /**
     * The flash is auto.
     */
    FOCUS_MODE_AUTO = 2,

    /**
     * Focus locked.
     */
    FOCUS_MODE_LOCKED = 3
} Camera_FocusMode;

/**
 * @brief Enumerates the focus states.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_FocusState {
    /**
     * Focusing.
     */
    FOCUS_STATE_SCAN = 0,

    /**
     * Focused.
     */
    FOCUS_STATE_FOCUSED = 1,

    /**
     * Unfocused.
     */
    FOCUS_STATE_UNFOCUSED = 2
} Camera_FocusState;

/**
 * @brief Enumerates the video stabilization modes.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_VideoStabilizationMode {
    /**
     * Video stabilization is disabled.
     */
    STABILIZATION_MODE_OFF = 0,

    /**
     * The basic video stabilization algorithm is used.
     */
    STABILIZATION_MODE_LOW = 1,

    /**
     * A video stabilization algorithm with a stabilization effect better than that of the **LOW** type is used.
     */
    STABILIZATION_MODE_MIDDLE = 2,

    /**
     * A video stabilization algorithm with a stabilization effect better than that of the **MIDDLE** type is used.
     */
    STABILIZATION_MODE_HIGH = 3,

    /**
     * Automatic video stabilization is used. This value is available for HDF cameras.
     */
    STABILIZATION_MODE_AUTO = 4
} Camera_VideoStabilizationMode;

/**
 * @brief Enumerates the image rotation angles.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_ImageRotation {
    /**
     * The image rotates 0 degrees.<br> Since API version 23, you are advised to use the new enum value {@link CAMERA_IMAGE_ROTATION_0}
     *  instead.
     */
    IAMGE_ROTATION_0 = 0,

    /**
     * The image rotates 0 degrees.
     * 
     * @since 23
     */
    CAMERA_IMAGE_ROTATION_0 = 0,

    /**
     * The image rotates 90 degrees.<br> Since API version 23, you are advised to use the new enum value {@link CAMERA_IMAGE_ROTATION_90}
     *  instead.
     */
    IAMGE_ROTATION_90 = 90,

    /**
     * The image rotates 90 degrees.
     * 
     * @since 23
     */
    CAMERA_IMAGE_ROTATION_90 = 90,

    /**
     * The image rotates 180 degrees.<br> Since API version 23, you are advised to use the new enum value {@link CAMERA_IMAGE_ROTATION_180}
     *  instead.
     */
    IAMGE_ROTATION_180 = 180,

    /**
     * The image rotates 180 degrees.
     * 
     * @since 23
     */
    CAMERA_IMAGE_ROTATION_180 = 180,

    /**
     * The image rotates 270 degrees.<br> Since API version 23, you are advised to use the new enum value {@link CAMERA_IMAGE_ROTATION_270}
     *  instead.
     */
    IAMGE_ROTATION_270 = 270,

    /**
     * The image rotates 270 degrees.
     * 
     * @since 23
     */
    CAMERA_IMAGE_ROTATION_270 = 270
} Camera_ImageRotation;

/**
 * @brief Enumerates the image quality levels.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_QualityLevel {
    /**
     * High image quality.
     */
    QUALITY_LEVEL_HIGH = 0,

    /**
     * Medium image quality.
     */
    QUALITY_LEVEL_MEDIUM = 1,

    /**
     * Low image quality.
     */
    QUALITY_LEVEL_LOW = 2
} Camera_QualityLevel;

/**
 * @brief Enumerates the metadata object types.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum Camera_MetadataObjectType {
    /**
     * Metadata object used for face detection.<br> Since API version 23, you are advised to use the new enum value {@link CAMERA_METADATA_OBJECT_TYPE_FACE_DETECTION}
     *  instead.
     */
    FACE_DETECTION = 0,

    /**
     * Metadata object used for face detection.
     * 
     * @since 23
     */
    CAMERA_METADATA_OBJECT_TYPE_FACE_DETECTION = 0,

    /**
     * Metadata object used for body detection.
     * 
     * @since 23
     */
    CAMERA_METADATA_OBJECT_TYPE_HUMAN_BODY = 1
} Camera_MetadataObjectType;

/**
 * @brief Enumerates the flashlight modes.
 * 
 * @since 12
 * @version 1.0
 */
typedef enum Camera_TorchMode {
    /**
     * The flashlight is always off.<br> Since API version 23, you are advised to use the new enum value {@link CAMERA_TORCH_MODE_OFF}
     *  instead.
     */
    OFF = 0,

    /**
     * The flashlight is always off.
     * 
     * @since 23
     */
    CAMERA_TORCH_MODE_OFF = 0,

    /**
     * The flashlight is always on.<br> Since API version 23, you are advised to use the new enum value {@link CAMERA_TORCH_MODE_ON}
     *  instead.
     */
    ON = 1,

    /**
     * The flashlight is always on.
     * 
     * @since 23
     */
    CAMERA_TORCH_MODE_ON = 1,

    /**
     * The flashlight will be turned on automatically based on the ambient lighting level.<br> Since API version 23,
     * you are advised to use the new enum value {@link CAMERA_TORCH_MODE_AUTO} instead.
     */
    AUTO = 2,

    /**
     * The flashlight will be turned on automatically based on the ambient lighting level.
     * 
     * @since 23
     */
    CAMERA_TORCH_MODE_AUTO = 2
} Camera_TorchMode;

/**
 * @brief Enumerates the smooth zoom modes.
 * 
 * @since 12
 * @version 1.0
 */
typedef enum Camera_SmoothZoomMode {
    /**
     * Bessel curve mode.<br> Since API version 23, you are advised to use the new enum value {@link CAMERA_SMOOTH_ZOOM_MODE_NORMAL}
     *  instead.
     */
    NORMAL = 0,

    /**
     * Bessel curve mode.
     * 
     * @since 23
     */
    CAMERA_SMOOTH_ZOOM_MODE_NORMAL = 0
} Camera_SmoothZoomMode;

/**
 * @brief Enumerates the preconfigured photo resolution types.
 * 
 * @since 12
 * @version 1.0
 */
typedef enum Camera_PreconfigType {
    /**
     * 720p resolution.
     */
    PRECONFIG_720P = 0,

    /**
     * 1080p resolution.
     */
    PRECONFIG_1080P = 1,

    /**
     * 4K resolution.
     */
    PRECONFIG_4K = 2,

    /**
     * High-quality photos.
     */
    PRECONFIG_HIGH_QUALITY = 3,
    
    /**
     * Resolution that supports HDR preview and GIF photography.
     * 
     * @since 23
     */
    PRECONFIG_HIGH_QUALITY_PHOTOSESSION_BT2020 = 4
} Camera_PreconfigType;

/**
 * @brief Enumerates the preconfigured photo aspect ratios.
 * 
 * @since 12
 * @version 1.0
 */
typedef enum Camera_PreconfigRatio {
    /**
     * 1:1 aspect ratio.
     */
    PRECONFIG_RATIO_1_1 = 0,

    /**
     * 4:3 aspect ratio.
     */
    PRECONFIG_RATIO_4_3 = 1,

    /**
     * 16:9 aspect ratio.
     */
    PRECONFIG_RATIO_16_9 = 2
} Camera_PreconfigRatio;

/**
 * @brief Enum for remote camera device type.
 *
 * @since 15
 * @version 1.0
 */
typedef enum Camera_HostDeviceType {
    /**
     * Indicates an unknown device camera.
     */
    HOST_DEVICE_TYPE_UNKNOWN_TYPE = 0,

    /**
     * Indicates a smartphone camera.
     */
    HOST_DEVICE_TYPE_PHONE = 0x0E,

    /**
     * Indicates tablet camera.
     */
    HOST_DEVICE_TYPE_TABLET = 0x11
} Camera_HostDeviceType;

/**
 * @brief The struct describes the parameters related to the size.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Size {
    /**
     * Width, in pixels.
     */
    uint32_t width;

    /**
     * Height, in pixels.
     */
    uint32_t height;
} Camera_Size;

/**
 * @brief The struct describes the profile of a camera stream.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Profile {
    /**
     * Camera format.
     */
    Camera_Format format;

    /**
     * Image size.
     */
    Camera_Size size;
} Camera_Profile;

/**
 * @brief The struct describes the frame rate range.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_FrameRateRange {
    /**
     * Minimum frame rate, in fps.
     */
    uint32_t min;

    /**
     * Maximum frame rate, in fps.
     */
    uint32_t max;
} Camera_FrameRateRange;

/**
 * @brief The struct describes the video profile.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_VideoProfile {
    /**
     * Camera format.
     */
    Camera_Format format;

    /**
     * Image size.
     */
    Camera_Size size;

    /**
     * Frame rate, in frames per second (FPS).
     */
    Camera_FrameRateRange range;
} Camera_VideoProfile;

/**
 * @brief The struct describes the camera output capability.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_OutputCapability {
    /**
     * Double pointer to the list of preview profiles.
     */
    Camera_Profile** previewProfiles;

    /**
     * Size of the preview profiles.
     */
    uint32_t previewProfilesSize;

    /**
     * Double pointer to the list of photo profiles.<br> In the configuration file, **size** is set to the width and
     * height of the camera resolution, not the actual width and height of an output image.
     */
    Camera_Profile** photoProfiles;

    /**
     * Size of the photo profiles.
     */
    uint32_t photoProfilesSize;

    /**
     * Double pointer to the list of video profiles.
     */
    Camera_VideoProfile** videoProfiles;

    /**
     * Size of the video profiles.
     */
    uint32_t videoProfilesSize;

    /**
     * Double pointer to the list of the metadata object types supported.
     */
    Camera_MetadataObjectType** supportedMetadataObjectTypes;

    /**
     * Size of the metadata profiles.
     */
    uint32_t metadataProfilesSize;
} Camera_OutputCapability;

/**
 * @brief The struct describes the camera device.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Device {
    /**
     * Pointer to the camera ID.
     */
    char* cameraId;

    /**
     * Camera position.
     */
    Camera_Position cameraPosition;

    /**
     * Camera type.
     */
    Camera_Type cameraType;

    /**
     * Camera connection type.
     */
    Camera_Connection connectionType;
} Camera_Device;

/**
 * @brief The struct describes the camera status information.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_StatusInfo {
    /**
     * Pointer to the camera instance.
     */
    Camera_Device* camera;

    /**
     * Camera status.
     */
    Camera_Status status;
} Camera_StatusInfo;

/**
 * @brief The struct describes the parameters related to a point.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Point {
    /**
     * X coordinate. The value range is [0,1].
     */
    double x;

    /**
     * Y coordinate. The value range is [0,1].
     */
    double y;
} Camera_Point;

/**
 * @brief The struct describes the location where a photo is taken.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Location {
    /**
     * Latitude.
     */
    double latitude;

    /**
     * Longitude.
     */
    double longitude;

    /**
     * Altitude, in meters.
     */
    double altitude;
} Camera_Location;

/**
 * @brief The struct describes the parameters related to photo capture.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_PhotoCaptureSetting {
    /**
     * Quality of the photo.
     */
    Camera_QualityLevel quality;

    /**
     * Rotation angle.
     */
    Camera_ImageRotation rotation;

    /**
     * Pointer to the location where the photo is taken.
     */
    Camera_Location* location;

    /**
     * Whether mirroring is enabled.<br> **true** if enabled, **false** otherwise. The default value is **false**.
     */
    bool mirror;
} Camera_PhotoCaptureSetting;

/**
 * @brief The struct describes the frame shutter information.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_FrameShutterInfo {
    /**
     * Capture ID.
     */
    int32_t captureId;

    /**
     * Timestamp of the frame, in milliseconds.
     */
    uint64_t timestamp;
} Camera_FrameShutterInfo;

/**
 * @brief The struct describes the capture end information.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_CaptureEndInfo {
    /**
     * Capture ID.
     */
    int32_t captureId;

    /**
     * Number of frames captured.
     */
    int64_t frameCount;
} Camera_CaptureEndInfo;

/**
 * @brief The struct describes a rectangle. The coordinate system for the returned detection points is based on the
 * landscape device orientation, with the charging port on the right. In this coordinate system, the top-left corner is
 * (0, 0), and the bottom-right corner is (1, 1). Here, **topLeftX** and **topLeftY** represent the coordinates of the
 * top-left corner of the rectangle, whereas **width** and **height** represent the width and height of the rectangle,
 * respectively. When cropping or selecting a face region based on specific requirements, the x and y coordinates of
 * the rectangle must be multiplied by the width and height of the actual camera preview output stream to obtain the
 * cropped face region.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_Rect {
    /**
     * X coordinate of the top-left corner of the rectangle, in the range of [0, 1].
     */
    int32_t topLeftX;

    /**
     * Y coordinate of the top-left corner of the rectangle, in the range of [0, 1].
     */
    int32_t topLeftY;

    /**
     * Width of the rectangle, in the range of [0, 1].
     */
    int32_t width;

    /**
     * Height of the rectangle, in the range of [0, 1].
     */
    int32_t height;
} Camera_Rect;

/**
 * @brief The struct describes the camera metadata.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct Camera_MetadataObject {
    /**
     * Type of the metadata object.
     */
    Camera_MetadataObjectType type;

    /**
     * Timestamp of the metadata object, in nanoseconds (ns).
     */
    int64_t timestamp;

    /**
     * Pointer to the axis aligned bounding box of the metadata object.
     */
    Camera_Rect* boundingBox;
} Camera_MetadataObject;

/**
 * @brief The struct describes the flashlight status information.
 * 
 * @since 12
 * @version 1.0
 */
typedef struct Camera_TorchStatusInfo {
    /**
     * Whether the flashlight is available. **true** if available, **false** otherwise.
     */
    bool isTorchAvailable;

    /**
     * Whether the flashlight is activated. **true** if activated, **false** otherwise.
     */
    bool isTorchActive;

    /**
     * Flashlight level. The value range is [0, 1]. A larger value indicates a greater luminance.
     */
    float torchLevel;
} Camera_TorchStatusInfo;

/**
 * @brief The struct describes the smooth zoom information.
 * 
 * @since 12
 * @version 1.0
 */
typedef struct Camera_SmoothZoomInfo {
    /**
     * Total duration of smooth zoom, in ms.
     */
    int32_t duration;
} Camera_SmoothZoomInfo;

/**
 * @brief The struct describes the capture start information.
 * 
 * @since 12
 * @version 1.0
 */
typedef struct Camera_CaptureStartInfo {
    /**
     * Capture ID.
     */
    int32_t captureId;

    /**
     * Estimated duration when the sensor captures frames at the bottom layer in a single capture. If **–1** is
     * reported, there is no estimated duration.
     */
    int64_t time;
} Camera_CaptureStartInfo;

/**
 * @brief The struct describes the frame shutter end information during capture.
 * 
 * @since 12
 * @version 1.0
 */
typedef struct Camera_FrameShutterEndInfo {
    /**
     * Capture ID.
     */
    int32_t captureId;
} Camera_FrameShutterEndInfo;

/**
* @brief Enumerates the fold statuses.
* 
* @since 13
* @version 1.0
*/
typedef enum Camera_FoldStatus {
    /**
     * Unfoldable.<br> Since API version 23, you are advised to use the new enum value {@link CAMERA_FOLD_STATUS_NON_FOLDABLE}
     *  instead.
     */
    NON_FOLDABLE = 0,

    /**
     * Unfoldable.
     * 
     * @since 23
     */
    CAMERA_FOLD_STATUS_NON_FOLDABLE = 0,

    /**
     * Unfolded.<br> Since API version 23, you are advised to use the new enum value {@link CAMERA_FOLD_STATUS_EXPANDED}
     *  instead.
     */
    EXPANDED = 1,

    /**
     * Unfolded.
     * 
     * @since 23
     */
    CAMERA_FOLD_STATUS_EXPANDED = 1,

    /**
     * Folded.<br> Since API version 23, you are advised to use the new enum value {@link CAMERA_FOLD_STATUS_FOLDED}
     * instead.
     */
    FOLDED = 2,

    /**
     * Folded.
     * 
     * @since 23
     */
    CAMERA_FOLD_STATUS_FOLDED = 2
} Camera_FoldStatus;

/**
 * @brief The struct describes the fold status information of the camera.
 * 
 * @since 13
 * @version 1.0
 */
typedef struct Camera_FoldStatusInfo {
    /**
     * Double pointer to the camera list.
     */
    Camera_Device** supportedCameras;

    /**
     * Number of cameras in the list.
     */
    uint32_t cameraSize;

    /**
     * Current fold status.
     */
    Camera_FoldStatus foldStatus;
} Camera_FoldStatusInfo;

/**
 * @brief Auto device switch status info.
 *
 * @since 13
 * @version 1.0
 */
typedef struct Camera_AutoDeviceSwitchStatusInfo {
    /**
     * is device switched.
     */
    bool isDeviceSwitched;

    /**
     * is device capability changed.
     */
    bool isDeviceCapabilityChanged;
} Camera_AutoDeviceSwitchStatusInfo;

/**
 * @brief Enum for quality prioritization.
 *
 * @since 14
 * @version 1.0
 */
typedef enum Camera_QualityPrioritization {
    /**
     * Hight quality priority.
     */
    HIGH_QUALITY = 0,

    /**
     * Power balance priority.
     */
    POWER_BALANCE = 1
} Camera_QualityPrioritization;

/**
 * @brief Enum for camera concurrent type.
 *
 * @since 18
 * @version 1.0
 */
typedef enum Camera_ConcurrentType {
    /**
     * Cameras concurrency with limited capability.
     */
    CAMERA_CONCURRENT_TYPE_LIMITED_CAPABILITY  = 0,

    /**
     * Cameras concurrenct with full capability.
     */
    CAMERA_CONCURRENT_TYPE_FULL_CAPABILITY = 1
} Camera_ConcurrentType;

/**
 * @brief Concurrency capability infos.
 *
 * @since 18
 * @version 1.0
 */
typedef struct Camera_ConcurrentInfo {
    /**
     * Camera instance.
     */
    Camera_Device camera;

    /**
     * Supported concurrent type.
     */
    Camera_ConcurrentType type;

    /**
     * Supported Modes.
     */
    Camera_SceneMode* sceneModes;

    /**
     * Supported outputCapabilities
     */
    Camera_OutputCapability* outputCapabilities;

    /**
     * Supported outputCapabilities size.
     */
    uint32_t modeAndCapabilitySize;
} Camera_ConcurrentInfo;

/**
 * @brief Enumerates the system pressure levels.
 * 
 * @since 20
 * @version 1.0
 */

typedef enum Camera_SystemPressureLevel {
    /**
     * The system pressure is normal.
     */
    SYSTEM_PRESSURE_NORMAL = 0,

    /**
     * The system pressure is elevated but not actively managed by the system.
     */
    SYSTEM_PRESSURE_MILD = 1,

    /**
     * The system pressure may affect the overall image quality and performance.
     */
    SYSTEM_PRESSURE_SEVERE = 2,

    /**
     * The system pressure has a significant impact on the image quality and performance.
     */
    SYSTEM_PRESSURE_CRITICAL = 3,

    /**
     * The system pressure is too high, causing the system to shut down.
     */
    SYSTEM_PRESSURE_SHUTDOWN = 4
} Camera_SystemPressureLevel;

/**
 * @brief Enumerates the photo quality prioritization strategies.
 * 
 * @since 21
 * @version 1.0
 */
typedef enum Camera_PhotoQualityPrioritization {
    /**
     * Focuses on image quality, which may increase the time required for capturing photos to ensure high-quality
     * output.
     */
    CAMERA_PHOTO_QUALITY_PRIORITIZATION_HIGH_QUALITY = 0,

    /**
     * Focuses on performance, trading off image quality for faster capture times.
     */
    CAMERA_PHOTO_QUALITY_PRIORITIZATION_SPEED = 1
} Camera_PhotoQualityPrioritization;

/**
 * @brief Enumerates the effect types of a camera controller.
 * 
 * @since 20
 * @version 1.0
 */
typedef enum Camera_ControlCenterEffectType {
    /**
     * Beauty effect.
     */
    CONTROL_CENTER_EFFECT_TYPE_BEAUTY = 0,

    /**
     * Portrait blur effect.
     */
    CONTROL_CENTER_EFFECT_TYPE_PORTRAIT = 1,

    /**
     * Applies a auto-framing effect.
     * @since 24
     */
    CONTROL_CENTER_EFFECT_TYPE_AUTO_FRAMING = 2
} Camera_ControlCenterEffectType;

/**
 * @brief The struct describes the effect status information of a camera controller.
 * 
 * @since 20
 * @version 1.0
 */
typedef struct Camera_ControlCenterStatusInfo {
    /**
     * Effect type of the camera controller.
     */
    Camera_ControlCenterEffectType effectType;

    /**
     * Whether the controller is activated. **true** if activated, **false** otherwise.
     */
    bool isActive;
} Camera_ControlCenterStatusInfo;

/**
 * @brief Obtains a Camera_Manager instance.
 * 
 * @param cameraManager Double pointer to the Camera_Manager instance created, if the function is successfully called.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_Camera_GetCameraManager(Camera_Manager** cameraManager);

/**
 * @brief Deletes a Camera_Manager instance.
 * 
 * @param cameraManager Pointer to the target Camera_Manager instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 *     <br>**CAMERA_SERVICE_FATAL_ERROR**: The camera service is abnormal.
 * @since 11
 */
Camera_ErrorCode OH_Camera_DeleteCameraManager(Camera_Manager* cameraManager);

/**
 * @brief Camera device query information.
 * 
 * @since 23
 * @version 1.0
 */
typedef struct Camera_DeviceQueryInfo {
    /**
     * List of camera types.
     */
    Camera_Type* cameraType;
    /**
     * Size of the camera type list.
     */
    uint32_t cameraTypeSize;
    /**
     * Camera position.
     */
    Camera_Position cameraPosition;
    /**
     * Camera connection type.
     */
    Camera_Connection connectionType;
} Camera_DeviceQueryInfo;

/**
 * @brief Provides the check result for whether a camera lens is blocked or dirty.
 * 
 * @since 23
 * @version 1.0
 */
typedef struct Camera_OcclusionDetectionResult {
    /**
     * Checks whether the camera lens is blocked. The value **true** indicates that the camera lens is blocked, and **
     * false** indicates the opposite.
     */
    bool isCameraOccluded;

    /**
     * Checks whether the camera lens is dirty. The value **true** indicates that the camera lens is dirty, and **false*
     * * indicates the opposite.
     */
    bool isCameraLensDirty;
} Camera_OcclusionDetectionResult;

/**
 * @brief Describes the zoom range configuration.
 * 
 * @since 24
 */
typedef struct OH_Camera_ZoomRange {
    /**
     * Minimum zoom value.
     * @since 24
     */
    float minZoom;

    /**
     * Maximum zoom value.
     * @since 24
    */
    float maxZoom;
} OH_Camera_ZoomRange;

/**
 * @brief Describes the physical aperture configuration.
 * @since 24
 */
typedef struct OH_Camera_PhysicalAperture {
    /**
     * Zoom range specification.
     * @since 24
     */
    OH_Camera_ZoomRange zoomRange;

    /**
     * Array of supported aperture values.
     * @since 24
     */
    float* apertures;

    /**
     * Number of aperture values.
     * @since 24
     */
    size_t apertureCount;
} OH_Camera_PhysicalAperture;

/**
 * @brief Enum for OIS (Optical Image Stabilization) mode.
 *
 * @since 24
 * @version 1.0
 */
typedef enum OH_Camera_OISMode {
    /**
     * OIS is disabled.
     * @since 24
     */
    OH_CAMERA_OIS_MODE_OFF = 0,

    /**
     * OIS is controlled automatically.
     * @since 24
     */
    OH_CAMERA_OIS_MODE_AUTO = 1,

    /** 
     * OIS is controlled by the application.
     * @since 24
     */
    OH_CAMERA_OIS_MODE_CUSTOM = 2
} OH_Camera_OISMode;

/**
 * @brief Enum for OIS (Optical Image Stabilization) axes.
 *
 * @since 24
 * @version 1.0
 */
typedef enum OH_Camera_OISAxes {
    /**
     * Pitch axis: up-and-down rotation of the camera body.
     * Rotation around the horizontal axis through the lens.
     * @since 24
     */
    OH_CAMERA_OIS_AXES_PITCH = 0,

    /**
     * Yaw axis: side-to-side rotation of the camera body.
     * Rotation around the vertical axis.
     * @since 24
     */
    OH_CAMERA_OIS_AXES_YAW = 1
} OH_Camera_OISAxes;

/**
 * @brief Describes the zoom point info.
 *
 * @since 26.0.0
 */
typedef struct OH_Camera_ZoomPointInfo {
    /**
     * Zoom ratio.
     * @since 26.0.0
     */
    float zoomRatio;

    /**
     * Equivalent focal length.
     * @since 26.0.0
     */
    uint32_t equivalentFocalLength;
} OH_Camera_ZoomPointInfo;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_CAMERA_H
/** @} */

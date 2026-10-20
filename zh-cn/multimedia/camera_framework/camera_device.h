/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @since 12
 * @version 1.0
 */

/**
 * @file camera_device.h
 *
 * @brief 定义相机的基本接口和功能。
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 12
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_CAMERA_CAMERADEVICE_H
#define NATIVE_INCLUDE_CAMERA_CAMERADEVICE_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取相机设备的传感器方向属性。
 * 
 * @param camera 用于获取属性的Camera_Device。
 * @param orientation 返回相机sensor角度属性。
 * @return CAMERA_OK：方法调用成功，返回传感器方向属性。
 *     <br>CAMERA_CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 12
 */
Camera_ErrorCode OH_CameraDevice_GetCameraOrientation(Camera_Device* camera, uint32_t* orientation);
/**
 * @brief 获取远程设备名称。
 * 
 * @param camera 用于获取属性的Camera_Device。
 * @param hostDeviceName 返回远程设备名称属性。
 * @return CAMERA_OK：方法调用成功，将返回远程设备名称属性。
 *     <br>CAMERA_CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 15
 */
Camera_ErrorCode OH_CameraDevice_GetHostDeviceName(Camera_Device* camera, char** hostDeviceName);
/**
 * @brief 获取远程设备类型。
 * 
 * @param camera 用于获取属性的Camera_Device。
 * @param hostDeviceType 远程设备类型属性。
 * @return CAMERA_OK：方法调用成功，将返回远程设备名称属性。
 *     <br>CAMERA_CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 15
 */
Camera_ErrorCode OH_CameraDevice_GetHostDeviceType(Camera_Device* camera, Camera_HostDeviceType* hostDeviceType);

/**
 * @brief 获取相机设备的等效焦距。
 *
 * @param camera 用于获取属性的Camera_Device指针。
 * @param equivalentFocalLengths 输出参数，返回等效焦距数组。
 * @param size 输出参数，返回数组大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 24
 */
Camera_ErrorCode OH_CameraDevice_GetLensEquivalentFocalLengths(const Camera_Device* camera, uint32_t** equivalentFocalLengths, uint32_t* size);

/**
 * @brief 检查相机设备是否为逻辑摄像头（由一个或多个物理摄像头组成）。
 *
 * @param camera 用于获取属性的Camera_Device指针。
 * @param isLogicalCamera 输出参数，返回表示是否为逻辑摄像头的布尔值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 24
 */
Camera_ErrorCode OH_CameraDevice_IsLogicalCamera(const Camera_Device* camera, bool* isLogicalCamera);

/**
 * @brief 获取组成逻辑摄像头的所有物理摄像头。调用{@link OH_CameraDevice_DeleteConstituentCameraDevices}释放组成逻辑摄像头的所有物理摄像头。
 *
 * @param logicalCamera 逻辑摄像头的Camera_Device指针。
 * @param constituentCameras 输出参数，返回组成逻辑摄像头的物理摄像头集合指针数组。
 * @param size 输出物理摄像头数量数组的大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 24
 */
Camera_ErrorCode OH_CameraDevice_GetLogicalCameraConstituentCameraDevices(const Camera_Device* logicalCamera, Camera_Device** constituentCameras, uint32_t* size);

/**
 * @brief 删除组成逻辑摄像头的所有物理摄像头。
 *
 * @param logicalCamera 逻辑摄像头的Camera_Device指针。
 * @param constituentCameras 期望被释放的组成逻辑摄像头的物理摄像头集合。
 * @param size 物理摄像头数量数组的大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 * @since 24
 */
Camera_ErrorCode OH_CameraDevice_DeleteConstituentCameraDevices(const Camera_Device* logicalCamera, Camera_Device* constituentCameras, uint32_t size);

/**
 * @brief 获取相机镜头的焦距。
 *
 * @param camera 用于获取属性的Camera_Device指针。
 * @param lensFocalLength 输出参数，返回镜头焦距值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 24
 */
Camera_ErrorCode OH_CameraDevice_GetLensFocalLength(const Camera_Device* camera, float* lensFocalLength);

/**
 * @brief 获取相机设备的最小对焦距离。
 *
 * @param camera 用于获取属性的Camera_Device指针。
 * @param minimumFocusDistance 输出参数，返回最小对焦距离。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 24
 */
Camera_ErrorCode OH_CameraDevice_GetMinimumFocusDistance(const Camera_Device* camera, float* minimumFocusDistance);

/**
 * @brief 获取相机设备的镜头畸变参数。
 *
 * @param camera 用于获取属性的Camera_Device指针。
 * @param lens 输出参数，返回镜头畸变参数数组。
 * @param size 输出参数，返回数组大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 24
 */
Camera_ErrorCode OH_CameraDevice_GetLensDistortion(const Camera_Device* camera, float** lens, uint32_t* size);

/**
 * @brief 获取相机设备的内参标定参数。
 *
 * @param camera 用于获取属性的Camera_Device指针。
 * @param intrinsicCalibration 输出参数，返回内参标定参数数组。
 * @param size 输出参数，返回数组大小。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 24
 */
Camera_ErrorCode OH_CameraDevice_GetIntrinsicCalibration(const Camera_Device* camera, float** intrinsicCalibration, uint32_t* size);

/**
 * @brief 获取相机传感器的物理尺寸。
 *
 * @param camera 用于获取属性的Camera_Device指针。
 * @param width 输出参数，返回传感器宽度（单位：毫米）。
 * @param height 输出参数，返回传感器高度（单位：毫米）。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 24
 */
Camera_ErrorCode OH_CameraDevice_GetSensorPhysicalSize(const Camera_Device* camera, float* width, float* height);

/**
 * @brief 获取相机传感器的像素阵列大小。
 *
 * @param camera 用于获取属性的Camera_Device指针。
 * @param width 输出参数，返回像素阵列宽度（单位：像素）。
 * @param height 输出参数，返回像素阵列高度（单位：像素）。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 24
 */
Camera_ErrorCode OH_CameraDevice_GetSensorPixelArraySize(const Camera_Device* camera, uint32_t* width, uint32_t* height);

/**
 * @brief 获取相机传感器的滤色阵列排列方式。
 *
 * @param camera 用于获取属性的Camera_Device指针。
 * @param sensorCFA 输出参数，返回传感器滤色阵列排列枚举值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 24
 */
Camera_ErrorCode OH_CameraDevice_GetSensorColorFilterArrangement(const Camera_Device* camera, OH_Camera_SensorColorFilterArrangement* sensorCFA);

/**
 * @brief 获取Car设备相机摄像头的位置。
 *
 * @param camera 指向用于检索属性的Camera_Device的指针。
 * @param automotiveCameraPosition 输出参数，返回Car设备摄像头位置枚举值。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或者参数不正确。
 *     <br>CAMERA_SERVICE_FATAL_ERROR：相机服务异常。
 * @since 26.0.0
 */
Camera_ErrorCode OH_CameraDevice_GetAutomotiveCameraPosition(const Camera_Device* camera, OH_Camera_AutomotiveCameraPosition* automotiveCameraPosition);
#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_CAMERA_CAMERADEVICE_H
/** @} */

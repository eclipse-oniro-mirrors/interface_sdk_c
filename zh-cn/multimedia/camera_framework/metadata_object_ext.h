/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @since 26.0.0
 * @version 1.0
 */

/**
 * @file metadata_object_ext.h
 *
 * @brief 声明元数据对象扩展概念。
 *
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 26.0.0
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_METADATA_OBJECT_EXT_H
#define NATIVE_INCLUDE_METADATA_OBJECT_EXT_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 元数据对象扩展结构体。
 *
 * @since 26.0.0
 */
typedef struct OH_Camera_MetadataObjectExt OH_Camera_MetadataObjectExt;

/**
 * @brief 获取元数据对象类型。
 *
 * @param metadataObjectExt OH_Camera_MetadataObjectExt实例的指针。
 * @param type 元数据对象类型的指针，是一个Camera_MetadataObjectType实例。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataObjectExt_GetMetadataObjectType(const OH_Camera_MetadataObjectExt* metadataObjectExt,
    Camera_MetadataObjectType* type);

/**
 * @brief 获取元数据对象的时间戳。
 *
 * @param metadataObjectExt OH_Camera_MetadataObjectExt实例的指针。
 * @param timestamp 存储时间戳的指针。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataObjectExt_GetTimestamp(const OH_Camera_MetadataObjectExt* metadataObjectExt,
    int64_t* timestamp);

/**
 * @brief 获取元数据对象的边界框。
 *
 * @param metadataObjectExt OH_Camera_MetadataObjectExt实例的指针。
 * @param boundingBox 元数据对象边界框的指针，是一个OH_Camera_Rect_Ext实例。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataObjectExt_GetBoundingBox(const OH_Camera_MetadataObjectExt* metadataObjectExt,
    OH_Camera_Rect_Ext* boundingBox);

/**
 * @brief 获取元数据对象（如人脸）的俯仰角度。取值范围为[-90, 90]，以向下为正方向。
 *
 * @param metadataObjectExt OH_Camera_MetadataObjectExt实例的指针。
 * @param pitchAngle 存储俯仰角的指针。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 *     <br>CAMERA_ERROR_OPTIONAL_PROPERTY_NOT_EXIST：可选属性不存在。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataObjectExt_GetPitchAngle(const OH_Camera_MetadataObjectExt* metadataObjectExt,
    float* pitchAngle);

/**
 * @brief 获取元数据对象（如人脸）的左右旋转角度。取值范围为[-90, 90]，以向右为正方向。
 *
 * @param metadataObjectExt OH_Camera_MetadataObjectExt实例的指针。
 * @param yawAngle 存储左右旋转角度的指针。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 *     <br>CAMERA_ERROR_OPTIONAL_PROPERTY_NOT_EXIST：可选属性不存在。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataObjectExt_GetYawAngle(const OH_Camera_MetadataObjectExt* metadataObjectExt,
    float* yawAngle);

/**
 * @brief 获取元数据对象（如人脸）的平面内旋转角度。取值范围为[-180, 180]，以顺时针方向为正方向。
 *
 * @param metadataObjectExt OH_Camera_MetadataObjectExt实例的指针。
 * @param rollAngle 存储翻滚角的指针。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 *     <br>CAMERA_ERROR_OPTIONAL_PROPERTY_NOT_EXIST：可选属性不存在。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataObjectExt_GetRollAngle(const OH_Camera_MetadataObjectExt* metadataObjectExt,
    float* rollAngle);

/**
 * @brief 获取元数据对象（如人脸）的左眼边界框。
 *
 * @param metadataObjectExt OH_Camera_MetadataObjectExt实例的指针。
 * @param boundingBox 元数据对象边界框的指针，是一个OH_Camera_Rect_Ext实例。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 *     <br>CAMERA_ERROR_OPTIONAL_PROPERTY_NOT_EXIST：可选属性不存在。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataObjectExt_GetLeftEyeBoundingBox(const OH_Camera_MetadataObjectExt* metadataObjectExt,
    OH_Camera_Rect_Ext* boundingBox);

/**
 * @brief 获取元数据对象（如人脸）的右眼边界框。
 *
 * @param metadataObjectExt OH_Camera_MetadataObjectExt实例的指针。
 * @param boundingBox 元数据对象边界框的指针，是一个OH_Camera_Rect_Ext实例。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 *     <br>CAMERA_ERROR_OPTIONAL_PROPERTY_NOT_EXIST：可选属性不存在。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataObjectExt_GetRightEyeBoundingBox(const OH_Camera_MetadataObjectExt* metadataObjectExt,
    OH_Camera_Rect_Ext* boundingBox);

/**
 * @brief 获取元数据对象（如人脸）的情绪类型。
 *
 * @param metadataObjectExt OH_Camera_MetadataObjectExt实例的指针。
 * @param emotion 存储情绪类型的指针。
 * @return CAMERA_OK：操作成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数缺失或参数类型错误。
 *     <br>CAMERA_ERROR_OPTIONAL_PROPERTY_NOT_EXIST：可选属性不存在。
 * @since 26.0.0
 */
Camera_ErrorCode OH_MetadataObjectExt_GetEmotion(const OH_Camera_MetadataObjectExt* metadataObjectExt,
    OH_Camera_MetadataObjectEmotion* emotion);

/**
 * @brief 销毁OH_Camera_MetadataObjectExt实例数组。
 *
 * @param metadataObjectExt OH_Camera_MetadataObjectExt实例数组的指针。
 * @param objectCount 要销毁的元数据对象数量。
 * @since 26.0.0
 */
void OH_MetadataObjectExt_Destroy(OH_Camera_MetadataObjectExt** metadataObjectExt, uint32_t objectCount);

/**
 * @brief 查询焦点是否已锁定跟踪。
 *
 * @param metadataObjectExt OH_Camera_MetadataObjectExt实例指针。
 * @return 焦点是否已锁定跟踪，返回true表示已锁定，返回false表示未锁定。
 * @since 26.0.0
 */
bool OH_MetadataObjectExt_IsLockFocusTracked(const OH_Camera_MetadataObjectExt* metadataObjectExt);
#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_METADATA_OBJECT_EXT_H
/** @} */
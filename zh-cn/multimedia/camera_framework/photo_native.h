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
 * @file photo_native.h
 *
 * @brief 声明相机照片的概念。
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 12
 * @version 1.0
 */

#ifndef NATIVE_INCLUDE_PHOTO_NATIVE_H
#define NATIVE_INCLUDE_PHOTO_NATIVE_H

#include <stdint.h>
#include <stdio.h>
#include "camera.h"
#include "multimedia/image_framework/image/image_native.h"
#include "multimedia/image_framework/image/picture_native.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 相机照片对象。<br> 全质量图对象。
 * 
 * @since 12
 * @version 1.0
 */
typedef struct OH_PhotoNative OH_PhotoNative;

/**
 * @brief 获取全质量图。
 * 
 * @param photo OH_PhotoNative实例。
 * @param mainImage 用于获取全质量图的OH_ImageNative。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 * @version 1.0
 */
Camera_ErrorCode OH_PhotoNative_GetMainImage(OH_PhotoNative* photo, OH_ImageNative** mainImage);

/**
 * @brief 获取非压缩图片。
 * 
 * @param photo OH_PhotoNative实例。
 * @param picture 用于获取非压缩图片的OH_PictureNative。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 23
 * @version 1.0
 */
Camera_ErrorCode OH_PhotoNative_GetUncompressedImage(OH_PhotoNative* photo, OH_PictureNative** picture);

/**
 * @brief 释放全质量图实例。
 * 
 * @param photo 要被释放的OH_PhotoNative实例。
 * @return CAMERA_OK：方法调用成功。
 *     <br>CAMERA_INVALID_ARGUMENT：参数丢失或参数类型不正确。
 * @since 12
 * @version 1.0
 */
Camera_ErrorCode OH_PhotoNative_Release(OH_PhotoNative* photo);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_PHOTO_NATIVE_H
/** @} */

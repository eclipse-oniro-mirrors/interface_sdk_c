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
 * @brief 获取指定类型的辅助图。
 *     <br>
 *     <br>使用场景：使用本接口前需先通过[OH_PhotoOutput_SetAutoAuxiliaryPhotosDeliveryEnabled()]
 * (capi-photo-output-h.md#oh_photooutput_setautoauxiliaryphotosdeliveryenabled)开启指定类型辅助图的自动回传功能，拍照获得的OH_PhotoNative
 * 对象中才会包含辅助图，并通过本接口按类型获取辅助图，用于后续分析处理。支持的辅助图类型及各自用途请参考
 * [OH_Camera_AuxiliaryPhotoType](capi-camera-h.md#oh_camera_auxiliaryphototype)。
 *
 * @param photo 指向OH_PhotoNative实例的指针。
 * @param type 辅助图类型。
 * @param outImage 指向OH_ImageNative实例的双重指针，用于接收获取的辅助图。调用成功时，指向有效的辅助图实例；调用失败时，该参数返回NULL。
 *     该实例由调用方管理，使用完成后应调用OH_PhotoNative_ReleaseImage()释放。
 * @return <ul>
 *         <li>**CAMERA_OK**: 操作成功。</li>
 *         <li>**CAMERA_INVALID_ARGUMENT**: 缺少参数或参数类型不正确。</li>
 *         <li>**CAMERA_ERROR_PARAM_OUT_OF_RANGE**: 参数超出范围。</li>
 *         </ul>
 * @release OH_PhotoNative_ReleaseImage {outImage}
 * @since 26.0.1
 */
Camera_ErrorCode OH_PhotoNative_GetAuxiliaryImage(const OH_PhotoNative* photo, OH_Camera_AuxiliaryPhotoType type,
    OH_ImageNative** outImage);

/**
 * @brief 获取指定类型的未压缩辅助图。
 *     <br>
 *     <br>使用场景：使用本接口前需先通过[OH_PhotoOutput_SetAutoAuxiliaryPhotosDeliveryEnabled()]
 * (capi-photo-output-h.md#oh_photooutput_setautoauxiliaryphotosdeliveryenabled)开启指定类型辅助图的自动回传功能，拍照获得的OH_PhotoNative
 * 对象中才会包含辅助图，并通过本接口按类型获取辅助图，用于后续分析处理。支持的辅助图类型及各自用途请参考
 * [OH_Camera_AuxiliaryPhotoType](capi-camera-h.md#oh_camera_auxiliaryphototype)。
 *
 * @param photo 指向OH_PhotoNative实例的指针。
 * @param type 辅助图类型。
 * @param outImage 指向OH_PictureNative实例的双重指针，用于接收获取的未压缩辅助图。调用成功时，指向有效的辅助图实例；调用失败时，该参数返回NULL。
 *     该实例由调用方管理，使用完成后应调用OH_PhotoNative_ReleasePicture()释放。
 * @return <ul>
 *         <li>**CAMERA_OK**: 操作成功。</li>
 *         <li>**CAMERA_INVALID_ARGUMENT**: 缺少参数或参数类型不正确。</li>
 *         <li>**CAMERA_ERROR_PARAM_OUT_OF_RANGE**: 参数超出范围。</li>
 *         </ul>
 * @release OH_PhotoNative_ReleasePicture {outImage}
 * @since 26.0.1
 */
Camera_ErrorCode OH_PhotoNative_GetUncompressedAuxiliaryImage(const OH_PhotoNative* photo,
    OH_Camera_AuxiliaryPhotoType type, OH_PictureNative** outImage);

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

/**
 * @brief 释放OH_PictureNative实例。
 *
 * @param picture 指向要释放的OH_PictureNative实例的指针。
 * @return <ul>
 *         <li>**CAMERA_OK**: 操作成功。</li>
 *         <li>**CAMERA_INVALID_ARGUMENT**: 缺少参数或参数类型不正确。</li>
 *         </ul>
 * @since 26.0.1
 */
Camera_ErrorCode OH_PhotoNative_ReleasePicture(OH_PictureNative* picture);
 
/**
 * @brief 释放OH_ImageNative实例。
 *
 * @param image 指向要释放的OH_ImageNative实例的指针。
 * @return <ul>
 *         <li>**CAMERA_OK**: 操作成功。</li>
 *         <li>**CAMERA_INVALID_ARGUMENT**: 缺少参数或参数类型不正确。</li>
 *         </ul>
 * @since 26.0.1
 */
Camera_ErrorCode OH_PhotoNative_ReleaseImage(OH_ImageNative* image);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_PHOTO_NATIVE_H
/** @} */

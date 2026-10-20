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
 * @brief The file declares the camera photo concepts.
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
 * @brief The struct describes the photo object, which is a full-quality image object.
 * 
 * @since 12
 * @version 1.0
 */
typedef struct OH_PhotoNative OH_PhotoNative;

/**
 * @brief Obtains a full-quality image.
 * 
 * @param photo Pointer to an **OH_PhotoNative** instance.
 * @param mainImage Double pointer to the full-quality image, which is an **OH_ImageNative** instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 * @version 1.0
 */
Camera_ErrorCode OH_PhotoNative_GetMainImage(OH_PhotoNative* photo, OH_ImageNative** mainImage);

/**
 * @brief Obtains an uncompressed image.
 * 
 * @param photo Pointer to an **OH_PhotoNative** instance.
 * @param picture Double pointer to the uncompressed image, which is an **OH_PictureNative** instance.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 23
 * @version 1.0
 */
Camera_ErrorCode OH_PhotoNative_GetUncompressedImage(OH_PhotoNative* photo, OH_PictureNative** picture);

/**
 * @brief Obtains an auxiliary image.
 *
 * @param photo [in] Pointer to an **OH_PhotoNative** instance.
 * @param type [in] The auxiliary photo type.
 * @param outImage [out] Double pointer to the auxiliary image, which is an **OH_ImageNative** instance. On success,
 *     points to a valid image instance. On failure, may be set to NULLThe caller is responsible for releasing the
 *     allocated memory using the appropriate release function.
 * @return <ul>
 *         <li>**CAMERA_OK**: The operation is successful.</li>
 *         <li>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.</li>
 *         <li>**CAMERA_ERROR_PARAM_OUT_OF_RANGE**: A parameter is out of the range.</li>
 *         </ul>
 * @release OH_PhotoNative_ReleaseImage {outImage}
 * @since 26.0.1
 */
Camera_ErrorCode OH_PhotoNative_GetAuxiliaryImage(const OH_PhotoNative* photo, OH_Camera_AuxiliaryPhotoType type,
    OH_ImageNative** outImage);

/**
 * @brief Obtains an uncompressed auxiliary image.
 *
 * @param photo [in] Pointer to an **OH_PhotoNative** instance.
 * @param type [in] The auxiliary photo type.
 * @param outImage [out] Double pointer to the uncompressed auxiliary image, which is an **OH_PictureNative** instance.
 *     On success, points to a valid image instance. On failure, may be set to NULL. The caller is responsible for
 *     releasing the allocated memory using the appropriate release function.
 * @return <ul>
 *         <li>**CAMERA_OK**: The operation is successful.</li>
 *         <li>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.</li>
 *         <li>**CAMERA_ERROR_PARAM_OUT_OF_RANGE**: A parameter is out of the range.</li>
 *         </ul>
 * @release OH_PhotoNative_ReleasePicture {outImage}
 * @since 26.0.1
 */
Camera_ErrorCode OH_PhotoNative_GetUncompressedAuxiliaryImage(const OH_PhotoNative* photo,
    OH_Camera_AuxiliaryPhotoType type, OH_PictureNative** outImage);

/**
 * @brief Releases a full-quality image.
 * 
 * @param photo Pointer to the **OH_PhotoNative** instance to release.
 * @return **CAMERA_OK**: The operation is successful.
 *     <br>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.
 * @since 12
 * @version 1.0
 */
Camera_ErrorCode OH_PhotoNative_Release(OH_PhotoNative* photo);

/**
 * @brief Releases an allocated native picture instance.
 *
 * @param picture [in] Pointer to the **OH_PictureNative** instance to release.
 * @return <ul>
 *         <li>**CAMERA_OK**: The operation is successful.</li>
 *         <li>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.</li>
 *         </ul>
 * @since 26.0.1
 */
Camera_ErrorCode OH_PhotoNative_ReleasePicture(OH_PictureNative* picture);

/**
 * @brief Releases an allocated native image instance.
 *
 * @param image [in] Pointer to the **OH_ImageNative** instance to release.
 * @return <ul>
 *         <li>**CAMERA_OK**: The operation is successful.</li>
 *         <li>**CAMERA_INVALID_ARGUMENT**: A parameter is missing or the parameter type is incorrect.</li>
 *         </ul>
 * @since 26.0.1
 */
Camera_ErrorCode OH_PhotoNative_ReleaseImage(OH_ImageNative* image);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_PHOTO_NATIVE_H
/** @} */

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
 * @addtogroup CameraNotificationInfo
 * @{
 *
 * @brief Provide the definition of the C interface for the camera module.
 *
 * @since 26.0.0
 */
/**
 * @file camera_notification_info.h
 *
 * @brief The file declares the notification info.
 * 
 * @library libohcamera.so
 * @kit CameraKit
 * @syscap SystemCapability.Multimedia.Camera.Core
 * @since 26.0.0
 */

#ifndef NATIVE_INCLUDE_CAMERA_NOTIFICATION_H
#define NATIVE_INCLUDE_CAMERA_NOTIFICATION_H

#include <stdint.h>
#include <stdio.h>
#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct describes the camera notification info.
 *
 * @since 26.0.0
 */
typedef struct OH_Camera_NotificationInfo OH_Camera_NotificationInfo;

/**
 * @brief Obtains the notification name from a camera notification info instance.
 *
 * @param notificationInfo Pointer to an OH_Camera_NotificationInfo instance.
 * @param name Pointer to the notification name, which is an {@link OH_Camera_NotificationName} instance.
 * @return {@link #CAMERA_OK} : The operation is successful.
 *         {@link #CAMERA_INVALID_ARGUMENT}: A parameter is missing or the parameter type is incorrect.
 * @since 26.0.0
 */
Camera_ErrorCode OH_CameraNotificationInfo_GetNotificationName(
    const OH_Camera_NotificationInfo* notificationInfo,
    OH_Camera_NotificationName* name);

/**
 * @brief Obtains the proximity state for focus from a camera notification info instance.
 *
 * @param notificationInfo Pointer to an {@link OH_Camera_NotificationInfo} instance.
 * @param state Pointer to the proximity state for focus, which is an
 *        {@link OH_Camera_ProximityStateForFocus} instance.
 * @return {@link #CAMERA_OK} : The operation is successful.
 *         {@link #CAMERA_INVALID_ARGUMENT}: A parameter is missing or the parameter type is incorrect.
 * @since 26.0.0
 */
Camera_ErrorCode OH_CameraNotificationInfo_GetProximityStateForFocus(
    const OH_Camera_NotificationInfo* notificationInfo, OH_Camera_ProximityStateForFocus* state);

/**
 * @brief Destroys camera notification info instances.
 *
 * @param notificationInfo Pointer to the pointer of {@link OH_Camera_NotificationInfo} instances to be destroyed.
 * @since 26.0.0
 */
void OH_CameraNotificationInfo_Destroy(OH_Camera_NotificationInfo* notificationInfo);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_INCLUDE_METADATA_OBJECT_EXT_H
/** @} */
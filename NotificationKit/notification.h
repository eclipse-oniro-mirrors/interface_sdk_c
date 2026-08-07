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
 * @addtogroup NOTIFICATION
 * @{
 *
 * @brief Defines APIs for notification services.
 *
 * @since 13
 */
/**
 * @file notification.h
 *
 * @brief Defines APIs for notification services.
 * 
 * @library libohnotification.so
 * @kit NotificationKit
 * @syscap SystemCapability.Notification.Notification
 * @since 13
 */

#ifndef OH_NOTIFICATION_H
#define OH_NOTIFICATION_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Checks whether the notification of the specified application is enabled.
 *
 * @return true  - Notification is enabled for the specified application.
 *         false - Notification is not enabled for the specified application.
 * @since 13
 */
bool OH_Notification_IsNotificationEnabled(void);

#ifdef __cplusplus
}
#endif
#endif // OH_NOTIFICATION_H
/** @} */

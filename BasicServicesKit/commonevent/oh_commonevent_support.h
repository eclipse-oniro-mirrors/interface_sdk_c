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
 * @addtogroup OH_CommonEvent
 * @{
 *
 * @brief Provides the APIs of common event service.
 *
 * @since 12
 */

/**
 * @file oh_commonevent_support.h
 *
 * @brief Provides common event constants defined by the system.
 *
 * @library libohcommonevent.so
 * @kit BasicServicesKit
 * @syscap SystemCapability.Notification.CommonEvent
 * @since 12
 * @version 1.0
 */

#ifndef OH_COMMONEVENT_SUPPORT_H
#define OH_COMMONEVENT_SUPPORT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Indicates the common event that the device is being shut down and the final shutdown will proceed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_SHUTDOWN = "usual.event.SHUTDOWN";

/**
 * @brief Indicates the common event that the charging state, level, and other information about the battery have
 * changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_BATTERY_CHANGED = "usual.event.BATTERY_CHANGED";

/**
 * @brief Indicates the common event that the battery level is low.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_BATTERY_LOW = "usual.event.BATTERY_LOW";

/**
 * @brief Indicates the common event that the battery exits the low state.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_BATTERY_OKAY = "usual.event.BATTERY_OKAY";

/**
 * @brief Indicates the common event that the device is connected to an external power supply.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_POWER_CONNECTED = "usual.event.POWER_CONNECTED";

/**
 * @brief Indicates the common event that the device is disconnected from the external power supply.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_POWER_DISCONNECTED = "usual.event.POWER_DISCONNECTED";

/**
 * @brief Indicates the common event that the device screen is off and the device is sleeping.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_SCREEN_OFF = "usual.event.SCREEN_OFF";

/**
 * @brief Indicates the common event that the device screen is on and the device is in interactive state.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_SCREEN_ON = "usual.event.SCREEN_ON";

/**
 * @brief Indicates the common event that the device is about to enter the hibernation mode.
 *
 * @since 15
 */
static const char* const COMMON_EVENT_ENTER_HIBERNATE = "usual.event.ENTER_HIBERNATE";

/**
 * @brief Indicates the common event that the device exits the hibernation mode.
 *
 * @since 15
 */
static const char* const COMMON_EVENT_EXIT_HIBERNATE = "usual.event.EXIT_HIBERNATE";

/**
 * @brief Indicates the common event that the device's thermal level has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_THERMAL_LEVEL_CHANGED = "usual.event.THERMAL_LEVEL_CHANGED";

/**
 * @brief Indicates the common event that the system time has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_TIME_TICK = "usual.event.TIME_TICK";

/**
 * @brief Indicates the common event that the system time has been set.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_TIME_CHANGED = "usual.event.TIME_CHANGED";

/**
 * @brief Indicates the common event that the system time zone has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_TIMEZONE_CHANGED = "usual.event.TIMEZONE_CHANGED";

/**
 * @brief Indicates the common event that a new application package has been installed on the device.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_PACKAGE_ADDED = "usual.event.PACKAGE_ADDED";

/**
 * @brief Indicates the common event that an installed application has been uninstalled from the device with the
 * application data retained.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_PACKAGE_REMOVED = "usual.event.PACKAGE_REMOVED";

/**
 * @brief Indicates the common event that an installed bundle has been uninstalled from the device with the application
 * data retained.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_BUNDLE_REMOVED = "usual.event.BUNDLE_REMOVED";

/**
 * @brief Indicates the common event that an installed application, including both the application data and code, has
 * been completely uninstalled from the device.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_PACKAGE_FULLY_REMOVED = "usual.event.PACKAGE_FULLY_REMOVED";

/**
 * @brief Indicates the common event that an application package has been changed (for example, a component in the
 * package has been enabled or disabled).
 *
 * @since 12
 */
static const char* const COMMON_EVENT_PACKAGE_CHANGED = "usual.event.PACKAGE_CHANGED";

/**
 * @brief Indicates the common event that the user has restarted the application package and killed all its processes.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_PACKAGE_RESTARTED = "usual.event.PACKAGE_RESTARTED";

/**
 * @brief Indicates the common event that the user cleared the application package data.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_PACKAGE_DATA_CLEARED = "usual.event.PACKAGE_DATA_CLEARED";

/**
 * @brief Indicates the common event that the user has cleared the application package data cache.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_PACKAGE_CACHE_CLEARED = "usual.event.PACKAGE_CACHE_CLEARED";

/**
 * @brief Indicates the common event that application packages have been suspended.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_PACKAGES_SUSPENDED = "usual.event.PACKAGES_SUSPENDED";

/**
 * @brief Indicates the common event that application packages are suspended.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_MY_PACKAGE_SUSPENDED = "usual.event.MY_PACKAGE_SUSPENDED";

/**
 * @brief Indicates the common event that application packages have not been suspended.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_MY_PACKAGE_UNSUSPENDED = "usual.event.MY_PACKAGE_UNSUSPENDED";

/**
 * @brief Indicates the common event that the device locale has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_LOCALE_CHANGED = "usual.event.LOCALE_CHANGED";

/**
 * @brief Indicates the common event that the device storage is insufficient.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_MANAGE_PACKAGE_STORAGE = "usual.event.MANAGE_PACKAGE_STORAGE";

/**
 * @brief Indicates the common event that the credential-encrypted storage has been unlocked for the current user when
 * the device is unlocked upon restart.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_USER_UNLOCKED = "usual.event.USER_UNLOCKED";

/**
 * @brief Indicates the common event that a distributed account is successfully logged out.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_DISTRIBUTED_ACCOUNT_LOGOUT = "common.event.DISTRIBUTED_ACCOUNT_LOGOUT";

/**
 * @brief Indicates the common event that the token of a distributed account is invalid.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_DISTRIBUTED_ACCOUNT_TOKEN_INVALID =
    "common.event.DISTRIBUTED_ACCOUNT_TOKEN_INVALID";

/**
 * @brief Indicates the common event that a distributed account is deregistered.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_DISTRIBUTED_ACCOUNT_LOGOFF = "common.event.DISTRIBUTED_ACCOUNT_LOGOFF";

/**
 * @brief Indicates the common event that the Wi-Fi state has changed to a new state, such as enabled or disabled.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_POWER_STATE = "usual.event.wifi.POWER_STATE";

/**
 * @brief Indicates the common event that the Wi-Fi access point has been scanned and proven to be available.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_SCAN_FINISHED = "usual.event.wifi.SCAN_FINISHED";

/**
 * @brief Indicates the common event that the Wi-Fi signal strength (RSSI) has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_RSSI_VALUE = "usual.event.wifi.RSSI_VALUE";

/**
 * @brief Indicates the common event that the Wi-Fi connection state has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_CONN_STATE = "usual.event.wifi.CONN_STATE";

/**
 * @brief Indicates the common event that the Wi-Fi hotspot state has changed to a new state, such as enabled or
 * disabled.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_HOTSPOT_STATE = "usual.event.wifi.HOTSPOT_STATE";

/**
 * @brief Indicates the common event that a client has joined the Wi-Fi hotspot of the current device.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_AP_STA_JOIN = "usual.event.wifi.WIFI_HS_STA_JOIN";

/**
 * @brief Indicates the common event that a client has disconnected from the Wi-Fi hotspot of the current device.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_AP_STA_LEAVE = "usual.event.wifi.WIFI_HS_STA_LEAVE";

/**
 * @brief Indicates the common event that the state of MPLINK (an enhanced Wi-Fi feature) has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_MPLINK_STATE_CHANGE = "usual.event.wifi.mplink.STATE_CHANGE";

/**
 * @brief Indicates the common event that the Wi-Fi P2P connection state has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_P2P_CONN_STATE = "usual.event.wifi.p2p.CONN_STATE_CHANGE";

/**
 * @brief Indicates the common event that the Wi-Fi P2P state has changed to enabled or disabled.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_P2P_STATE_CHANGED = "usual.event.wifi.p2p.STATE_CHANGE";

/**
 * @brief Indicates the common event that the state of the Wi-Fi P2P peer device has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_P2P_PEERS_STATE_CHANGED = "usual.event.wifi.p2p.DEVICES_CHANGE";

/**
 * @brief Indicates the common event that the Wi-Fi P2P discovery state has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_P2P_PEERS_DISCOVERY_STATE_CHANGED =
    "usual.event.wifi.p2p.PEER_DISCOVERY_STATE_CHANGE";

/**
 * @brief Indicates the common event that the state of the Wi-Fi P2P local device has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_P2P_CURRENT_DEVICE_STATE_CHANGED =
    "usual.event.wifi.p2p.CURRENT_DEVICE_CHANGE";

/**
 * @brief Indicates the common event that the Wi-Fi P2P group information has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_WIFI_P2P_GROUP_STATE_CHANGED = "usual.event.wifi.p2p.GROUP_STATE_CHANGED";

/**
 * @brief Indicates the common event that the state of the device NFC adapter has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_NFC_ACTION_ADAPTER_STATE_CHANGED = "usual.event.nfc.action.ADAPTER_STATE_CHANGED";

/**
 * @brief Indicates the common event that the NFC RF field is on.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_NFC_ACTION_RF_FIELD_ON_DETECTED = "usual.event.nfc.action.RF_FIELD_ON_DETECTED";

/**
 * @brief Indicates the common event that the NFC RF field is off.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_NFC_ACTION_RF_FIELD_OFF_DETECTED = "usual.event.nfc.action.RF_FIELD_OFF_DETECTED";

/**
 * @brief Indicates the common event that the system stops charging the battery.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_DISCHARGING = "usual.event.DISCHARGING";

/**
 * @brief Indicates the common event that the system starts charging the battery.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_CHARGING = "usual.event.CHARGING";

/**
 * @brief Indicates the common event that the system standby mode has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_DEVICE_IDLE_MODE_CHANGED = "usual.event.DEVICE_IDLE_MODE_CHANGED";

/**
 * @brief Indicates the common event that the device enters the charging idle mode.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_CHARGE_IDLE_MODE_CHANGED = "usual.event.CHARGE_IDLE_MODE_CHANGED";

/**
 * @brief Indicates the common event that the system power saving mode is changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_POWER_SAVE_MODE_CHANGED = "usual.event.POWER_SAVE_MODE_CHANGED";

/**
 * @brief Indicates the common event that the USB device state has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_USB_STATE = "usual.event.hardware.usb.action.USB_STATE";

/**
 * @brief Indicates the common event that the USB port state of the user device has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_USB_PORT_CHANGED = "usual.event.hardware.usb.action.USB_PORT_CHANGED";

/**
 * @brief Indicates the common event that a USB device has been attached when the user device functions as a USB host.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_USB_DEVICE_ATTACHED = "usual.event.hardware.usb.action.USB_DEVICE_ATTACHED";

/**
 * @brief Indicates the common event that a USB device has been detached when the user device functions as a USB host.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_USB_DEVICE_DETACHED = "usual.event.hardware.usb.action.USB_DEVICE_DETACHED";

/**
 * @brief Indicates the common event that the airplane mode of a device has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_AIRPLANE_MODE_CHANGED = "usual.event.AIRPLANE_MODE";

/**
 * @brief Indicates the common event of screen splitting.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_SPLIT_SCREEN = "common.event.SPLIT_SCREEN";

/**
 * @brief Indicates the common event that a quick fix is applied to an application.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_QUICK_FIX_APPLY_RESULT = "usual.event.QUICK_FIX_APPLY_RESULT";

/**
 * @brief Indicates the common event that a quick fix is revoked.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_QUICK_FIX_REVOKE_RESULT = "usual.event.QUICK_FIX_REVOKE_RESULT";

/**
 * @brief Indicates the common event that the user information has been updated.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_USER_INFO_UPDATED = "usual.event.USER_INFO_UPDATED";

/**
 * @brief Indicates the common event that the SIM card state has been updated.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_SIM_STATE_CHANGED = "usual.event.SIM_STATE_CHANGED";

/**
 * @brief Indicates the common event that the call state has been updated.
 *
 * To subscribe to this common event, your application must have the ohos.permission.GET_TELEPHONY_STATE
 * permission.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_CALL_STATE_CHANGED = "usual.event.CALL_STATE_CHANGED";

/**
 * @brief Indicates the common event that the network state has been updated.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_NETWORK_STATE_CHANGED = "usual.event.NETWORK_STATE_CHANGED";

/**
 * @brief Indicates the common event that the signal information has been updated.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_SIGNAL_INFO_CHANGED = "usual.event.SIGNAL_INFO_CHANGED";

/**
 * @brief Indicates the common event that the screen has been unlocked.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_SCREEN_UNLOCKED = "usual.event.SCREEN_UNLOCKED";

/**
 * @brief Indicates the common event that the screen has been locked.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_SCREEN_LOCKED = "usual.event.SCREEN_LOCKED";

/**
 * @brief Indicates the common event that the HTTP proxy configuration has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_HTTP_PROXY_CHANGE = "usual.event.HTTP_PROXY_CHANGE";

/**
 * @brief Indicates the common event that the network connection state has changed.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_CONNECTIVITY_CHANGE = "usual.event.CONNECTIVITY_CHANGE";

/**
 * @brief Indicates the common event that the minor mode is enabled.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_MINORSMODE_ON = "usual.event.MINORSMODE_ON";

/**
 * @brief Indicates the common event that the minor mode is disabled.
 *
 * @since 12
 */
static const char* const COMMON_EVENT_MINORSMODE_OFF = "usual.event.MINORSMODE_OFF";

/**
 * @brief Indicates the common event that the browser hosting policy has been changed.
 *
 * @since 15
 */
static const char* const COMMON_EVENT_MANAGED_BROWSER_POLICY_CHANGED = "usual.event.MANAGED_BROWSER_POLICY_CHANGED";

/**
 * @brief Indicates the common event that the tablet mode of a device has been changed.
 *
 * @since 23
 */
static const char* const COMMON_EVENT_TABLET_MODE_CHANGED = "usual.event.TABLET_MODE_CHANGED";

/**
 * @brief This common event indicates that specific volumes on the device have been decrypted.
 *
 * @since 26.0.0
 */
static const char* const COMMON_EVENT_VOLUME_DECRYPTED = "usual.event.VOLUME_DECRYPTED";

/**
 * @brief This common event indicates that specific volumes on the device have been encrypted.
 *
 * @since 26.0.0
 */
static const char* const COMMON_EVENT_VOLUME_ENCRYPTED = "usual.event.VOLUME_ENCRYPTED";

/**
 * @brief This common event indicates that specific volumes on the device have had their encryption policy set.
 *
 * To subscribe to this common event, your application must have the ohos.permission.QUERY_VOLUME_ENCRYPTION_STATUS
 * permission.
 *
 * @since 26.0.0
 */
static const char* const COMMON_EVENT_VOLUME_ENCRYPTION_POLICY_SET = "usual.event.VOLUME_ENCRYPTION_POLICY_SET";

/**
 * @brief Indicates the common event that the lid state of a device has been changed.
 *
 * @since 23
 */
static const char* const COMMON_EVENT_LID_STATE_CHANGED = "usual.event.LID_STATE_CHANGED";
#ifdef __cplusplus
}
#endif
#endif // OH_COMMONEVENT_SUPPORT_H
/** @} */

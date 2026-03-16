/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup wifiservice
 * @{
 *
 * @brief Provides functions for the Wi-Fi station and hotspot modes.
 *
 * You can use this module to enable and disable the Wi-Fi station or hotspot mode, connect to and disconnect from a
 * station or hotspot, query the station or hotspot status, and listen for events. \n
 *
 * @since 24.0.0
 */

/**
 * @file wifi_linked_info.h
 *
 * @brief Defines the data structure and macro of the Wi-Fi connection information.
 *
 * @since 24.0.0
 */
#ifndef WIFI_LITE_WIFI_LINKED_INFO_H
#define WIFI_LITE_WIFI_LINKED_INFO_H


/**
 * @brief Indicates the maximum length of a Wi-Fi SSID.
 *
 * The maximum length is 32, and the last bit is reserved and set to <b>\0</b>. \n
 */
#define WIFI_MAX_SSID_LEN 33 // 32 + \0
/**
 * @brief Indicates the maximum length of a Wi-Fi MAC address or a Wi-Fi BSSID.
 *
 */
#define WIFI_MAC_LEN 18

/**
 * @brief Enumerates Wi-Fi connection states.
 *
 * @since 24.0.0
 */
typedef enum {
    DISCONNECT = -1,
    DEFAULT_LINK = 0,
    WIFI7_SINGLE_LINK = 1,
    WIFI7_MLSR = 2,
    WIFI7_EMLSR = 3,
    WIFI7_STR = 4,
    WIFI7_LEGACY = 5 //非MLO接入
} OHWifiLinkType;

/**
 * @brief Enumerates Wi-Fi connection states.
 *
 * @since 24.0.0
 */
typedef enum {
    /** The device is searching for an available AP. */
    WIFI_CONN_SCANNING,

    /** The Wi-Fi connection is being set up. */
    WIFI_CONN_CONNECTING,

    /** The Wi-Fi connection is being authenticated. */
    WIFI_CONN_AUTHENTICATING,

    /** The IP address of the Wi-Fi connection is being obtained. */
    WIFI_CONN_OBTAINING_IPADDR,

    /** The Wi-Fi connection has been set up. */
    WIFI_CONN_CONNECTED,

    /** The Wi-Fi connection is being torn down. */
    WIFI_CONN_DISCONNECTING,

    /** The Wi-Fi connection has been torn down. */
    WIFI_CONN_DISCONNECTED,

    /** The Wi-Fi special connection. */
    WIFI_CONN_SPECIAL_CONNECT,

    /** Failed to set up the Wi-Fi connection. */
    WIFI_CONN_UNKNOWN
} OHWifiConnState;

/**
 * @brief Enumerates Wi-Fi supplicant state.
 *
 * @since 24.0.0
 */
typedef enum {
    WIFI_SUPP_DISCONNECTED = 0,
    WIFI_SUPP_INTERFACE_DISABLED = 1,
    WIFI_SUPP_INACTIVE = 2,
    WIFI_SUPP_SCANNING = 3,
    WIFI_SUPP_AUTHENTICATING = 4,
    WIFI_SUPP_ASSOCIATING = 5,
    WIFI_SUPP_ASSOCIATED = 6,
    WIFI_SUPP_FOUR_WAY_HANDSHAKE = 7,
    WIFI_SUPP_GROUP_HANDSHAKE = 8,
    WIFI_SUPP_COMPLETED = 9,
    WIFI_SUPP_UNKNOWN = 10,

    WIFI_SUPP_INVALID = 0xFF,
} OHWifiSupplicantState;

/**
 * @brief Enumerates Wi-Fi detailed connection state.
 *
 * @since 24.0.0
 */
typedef enum {
    WIFI_DETAIL_AUTHENTICATING = 0,
    WIFI_DETAIL_BLOCKED = 1,
    WIFI_DETAIL_CAPTIVE_PORTAL_CHECK = 2,
    WIFI_DETAIL_CONNECTED = 3,
    WIFI_DETAIL_CONNECTING = 4,
    WIFI_DETAIL_DISCONNECTED = 5,
    WIFI_DETAIL_DISCONNECTING = 6,
    WIFI_DETAIL_FAILED = 7,
    WIFI_DETAIL_IDLE = 8,
    WIFI_DETAIL_OBTAINING_IPADDR = 9,
    WIFI_DETAIL_WORKING = 10,
    WIFI_DETAIL_NOTWORKING = 11,
    WIFI_DETAIL_SCANNING = 12,
    WIFI_DETAIL_SUSPENDED = 13,
    WIFI_DETAIL_VERIFYING_POOR_LINK = 14,
    WIFI_DETAIL_PASSWORD_ERROR = 15,
    WIFI_DETAIL_CONNECTION_REJECT = 16,
    WIFI_DETAIL_CONNECTION_FULL = 17,
    WIFI_DETAIL_CONNECTION_TIMEOUT = 18,
    WIFI_DETAIL_OBTAINING_IPADDR_FAIL = 19,
    WIFI_DETAIL_INVALID = 0xFF,
} OHWifiDetailedState;

/**
 * @brief Enumerates Wi-Fi Channel Width.
 *
 * @since 24.0.0
 */
typedef enum {
    WIDTH_20MHZ = 0,
    WIDTH_40MHZ = 1,
    WIDTH_80MHZ = 2,
    WIDTH_160MHZ = 3,
    WIDTH_80MHZ_PLUS = 4,
    WIDTH_INVALID
} OHWifiChannelWidth;

/**
 * @brief Enumerates Wi-Fi category.
 *
 * @since 24.0.0
 */
typedef enum {
    CATEGORY_DEFAULT = 1,
    CATEGORY_WIFI6 = 2,
    CATEGORY_WIFI6_PLUS = 3,
    CATEGORY_WIFI7 = 4,
    CATEGORY_WIFI7_PLUS = 5
} OHWifiCategory;

/**
 * @brief Represents the Wi-Fi connection information.
 *
 * This refers to the information about the hotspot connected to this station. The information is obtained using
 * {@link GetLinkedInfo}.
 *
 * @since 24.0.0
 */
typedef struct {
    /** Service set ID (SSID). For its length, see {@link WIFI_MAX_SSID_LEN}. */
    char ssid[WIFI_MAX_SSID_LEN];
    /** Basic service set ID (BSSID). For its length, see {@link WIFI_MAC_LEN}. */
    char bssid[WIFI_MAC_LEN];
    /** MAC address of the connected hotspot */
    char macAddress[WIFI_MAC_LEN];
    /** Received signal strength indicator (RSSI) */
    int rssi;
    /** Wi-Fi band information of hotspot */
    int band;
    /** Wi-Fi link speed (units: Mbps) */
    int linkSpeed;
    /** Wi-Fi frequency information of hotspot */
    int frequency;
    /** MAC address type */
    int macType;
    /** Wi-Fi connection state, which is defined in {@link OHWiFiConnState} */
    OHWifiConnState connState;
    /** Whether the SSID is hidden */
    int ifHiddenSSID;
    /** Whether data is restricted */
    int isDataRestricted;
    /** Supplicant state, defined in {@link OHWiFiSupplicantState} */
    OHWifiSupplicantState supplicantState;
    /** Detailed connection state, defined in {@link OHWiFiDetailedState} */
    OHWifiDetailedState detailedState;
    /** Wi-Fi link type, defined in {@link OHWiFiLinkType} */
    OHWifiLinkType wifiLinkType;
    /** Wi-Fi standard */
    int wifiStandard;
    /** Maximum supported RX link speed */
    int maxSupportedRxLinkSpeed;
    /** Maximum supported TX link speed */
    int maxSupportedTxLinkSpeed;
    /** Downstream network speed */
    int rxLinkSpeed;
    /** Current AP channel width */
    OHWifiChannelWidth channelWidth;
    /** Supported Wi-Fi category, defined in {@link WifiCategory} */
    OHWifiCategory supportedWifiCategory;
    /** Whether is HiLink network */
    int isHiLinkNetwork;
    /** IP address of the connected hotspot */
    unsigned int ipAddress;
} OHWifiLinkedInfo;
#endif // WIFI_LITE_WIFI_LINKED_INFO_H
/** @} */
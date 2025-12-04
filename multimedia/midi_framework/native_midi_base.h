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
 * @addtogroup OHMIDI
 * @{
 *
 * @brief Provide the definition of the C interface for the MIDI module.
 *
 * @since 24
 * @version 1.0
 */
/**
 * @file native_midi_base.h
 *
 * @brief Declare underlying data structure for MIDI module.
 *
 * @library libohmidi.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 24
 * @version 1.0
 */
#ifndef NATIVE_MIDI_BASE_H
#define NATIVE_MIDI_BASE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief MIDI status code enumeration
 * @since 24
 */
typedef enum {
    /**
     * @error Operation successful.
     */
    MIDI_STATUS_OK = 0,

    /**
     * @error Invalid parameter (e.g., null pointer).
     */
    MIDI_STATUS_GENERIC_INVALID_ARGUMENT,

    /**
     * @error IPC communication failure.
     */
    MIDI_STATUS_GENERIC_IPC_FAILURE,

    /**
     * @error Insufficient result space.
     * Returned when the buffer provided by the caller is too small to hold the result.
     */
    MIDI_STATUS_INSUFFICIENT_RESULT_SPACE,

    /**
     * @error Invalid client handle.
     */
    MIDI_STATUS_INVALID_CLIENT,

    /**
     * @error Invalid device handle.
     */
    MIDI_STATUS_INVALID_DEVICE_HANDLE,

    /**
     * @error Invalid port configuration.
     */
    MIDI_STATUS_INVALID_PORT,

    /**
     * @error Device is already open.
     */
    MIDI_STATUS_DEVICE_ALREADY_OPEN,

    /**
     * @error Device is not open.
     */
    MIDI_STATUS_DEVICE_NOT_OPEN,

    /**
     * @error Send buffer is full.
     * Returned by non-blocking send when the atomic message cannot fit in the buffer.
     */
    MIDI_STATUS_WOULD_BLOCK,

    /**
     * @error The MIDI system service has died or disconnected.
     * This is a fatal error. The client must be destroyed and recreated.
     */
    MIDI_STATUS_SERVICE_DIED,

    /**
     * @error Unknown system error.
     */
    MIDI_STATUS_UNKNOWN_ERROR = -1
} MidiStatusCode;

/**
 * @brief Port direction enumeration
 * @since 24
 */
typedef enum {
    /**
     * @brief Input port (Device -> Host).
     */
    MIDI_PORT_DIRECTION_INPUT  = 1,

    /**
     * @brief Output port (Host -> Device).
     */
    MIDI_PORT_DIRECTION_OUTPUT = 2
} MidiPortDirection;

/**
 * @brief MIDI transport protocol enumeration
 * @since 24
 */
typedef enum {
    /**
     * @brief Legacy MIDI 1.0 Byte Stream.
     * The SDK will automatically convert this to UMP internally.
     */
    MIDI_TRANSPORT_PROTOCOL_MIDI1 = 1,

    /**
     * @brief Universal MIDI Packet (UMP).
     * Native MIDI 2.0 format (32-bit words).
     */
    MIDI_TRANSPORT_PROTOCOL_UMP   = 2
} MidiTransportProtocol;

/**
 * @brief MIDI Device Type
 * @since 24
 */
typedef enum {
    /**
     * @brief USB MIDI Device.
     */
    MIDI_DEVICE_TYPE_USB = 0,

    /**
     * @brief Bluetooth LE MIDI Device.
     */
    MIDI_DEVICE_TYPE_BLE = 1
} MidiDeviceType;

/**
 * @brief Device connection state change action
 * @since 24
 */
typedef enum {
    /**
     * @brief A MIDI device has been connected (attached).
     */
    MIDI_DEVICE_CHANGE_ACTION_CONNECTED = 0,

    /**
     * @brief A MIDI device has been disconnected (detached).
     */
    MIDI_DEVICE_CHANGE_ACTION_DISCONNECTED = 1
} MidiDeviceChangeAction;

/**
 * @brief MIDI Event Structure (Universal)
 * Designed to handle both raw Byte Stream (MIDI 1.0) and UMP.
 * @since 24
 */
typedef struct {
    /**
     * @brief Timestamp in nanoseconds.
     * 0 indicates "send immediately".
     */
    uint64_t timestamp;

    /**
     * @brief Data length in bytes.
     * - For MIDI 1.0: The number of bytes (e.g., 3 for NoteOn).
     * - For UMP: The number of bytes (e.g., 8 for a 64-bit UMP packet).
     */
    size_t length;

    /**
     * @brief Pointer to data.
     * Can point to a uint8_t array (MIDI 1.0) or a casted uint32_t array (UMP).
     */
    const uint8_t *data;
} MidiEvent;

/**
 * @brief Device Information
 * Used for enumeration and display.
 * @since 24
 */
typedef struct {
    /**
     * @brief Unique identifier for the MIDI device.
     */
    int64_t midiDeviceId;

    /**
     * @brief Type of the device (USB, BLE, etc.).
     */
    MidiDeviceType deviceType;

    /**
     * @brief Product name of the device (e.g., "Yamaha UX16").
     */
    char productName[256];

    /**
     * @brief Vendor name of the device.
     */
    char vendorName[256];
} DeviceInformation;

/**
 * @brief Port Descriptor (Lightweight)
 * Used for identifying ports in Open/Send calls to avoid large stack copies.
 * @since 24
 */
typedef struct {
    /**
     * @brief The unique ID of the port within the device (index).
     */
    uint32_t portIndex;

    /**
     * @brief The protocol the application wishes to use.
     * If protocol is MIDI1, the SDK handles conversion to UMP automatically.
     */
    MidiTransportProtocol protocol;
} MidiPortDescriptor;

/**
 * @brief Port Information (Detailed)
 * Used for enumeration (contains display names).
 * @since 24
 */
typedef struct {
    /**
     * @brief The index of the port.
     */
    uint32_t portIndex;

    /**
     * @brief The ID of the device this port belongs to.
     */
    int64_t deviceId;

    /**
     * @brief Direction of the port (Input/Output).
     */
    MidiPortDirection direction;

    /**
     * @brief Human-readable name of the port.
     */
    char name[256];
} MidiPortInformation;

/**
 * @brief Opaque handle for MIDI Client
 */
typedef struct MidiClientStruct MidiClient;

/**
 * @brief Opaque handle for MIDI Device Session
 */
typedef struct MidiDeviceStruct MidiDevice;

/**
 * @brief Callback for monitoring device connection/disconnection
 *
 * @param userData User context provided during client creation.
 * @param action Device change action (Connected/Disconnected).
 * @param deviceInfo Information of the changed device.
 * @since 24
 */
typedef void (*MidiDeviceChangeHandler)(void *userData,
                                         MidiDeviceChangeAction action,
                                         DeviceInformation deviceInfo);

/**
 * @brief Callback for receiving MIDI data (Batch Processing)
 *
 * @note The callback is invoked on a high-priority thread.
 * @note The 'events' array and its data pointers are transient and valid ONLY 
 * for the duration of this callback. If you need to keep the data, copy it.
 *
 * @param userData User context provided during port opening.
 * @param events Pointer to the array of MIDI events received.
 * @param eventCount The number of events in the array.
 * @since 24
 */
typedef void (*MidiInputHandler)(void *userData, const MidiEvent *events, size_t eventCount);

/**
 * @brief Callback for handling client-level errors
 * * Invoked when a critical error occurs in the MIDI service (e.g., service crash).
 * Applications may need to recreate the client when this occurs.
 *
 * @param userData User context provided during client creation.
 * @param code The error code indicating the cause.
 * @since 24
 */
typedef void (*OnMidiError)(void *userData, MidiStatusCode code);

/**
 * @brief Client callbacks structure
 * @since 24
 */
typedef struct {
    /**
     * @brief Handler for device hotplug events.
     */
    MidiDeviceChangeHandler onDeviceChange;

    /**
     * @brief Handler for critical service errors.
     */
    OnMidiError onMidiError;
} OH_MIDI_Callbacks;

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_MIDI_BASE_H
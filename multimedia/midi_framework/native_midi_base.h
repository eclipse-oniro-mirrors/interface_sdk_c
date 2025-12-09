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
 * @brief Provide the definition of the C interface for the Midi module.
 *
 * @since 24
 * @version 1.0
 */
/**
 * @file native_midi_base.h
 *
 * @brief Declare underlying data structure for Midi module.
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
 * @brief Midi status code enumeration
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
     * @error Invalid port index.
     */
    MIDI_STATUS_INVALID_PORT,

    /**
     * @error Send buffer is transiently full.
     * Indicates that the shared memory buffer currently lacks space
     * The application should wait briefly or retry later.
     * Returned by non-blocking send when message cannot fit in the buffer.
     */
    MIDI_STATUS_WOULD_BLOCK,

    /**
     * @error Operation can not be handle in a resonable time.
     */
    MIDI_STATUS_TIMEOUT,

    /**
     * @error The Midi system service has died or disconnected.
     * The client must be destroyed and recreated.
     */
    MIDI_STATUS_SERVICE_DIED,

    /**
     * @error Unknown system error.
     */
    MIDI_STATUS_UNKNOWN_ERROR = -1
} OH_MidiStatusCode;

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
} OH_MidiPortDirection;

/**
 * @brief Midi transport protocol enumeration
 * @since 24
 */
typedef enum {
    /**
     * @brief Legacy Midi 1.0 Byte Stream.
     * Even when this protocol is selected, data is transported as UMP(with 0x2 as status byte).
     */
    MIDI_TRANSPORT_PROTOCOL_MIDI1 = 1,

    /**
     * @brief Universal Midi Packet (UMP).
     * Native Midi 2.0 format (32-bit words).
     */
    MIDI_TRANSPORT_PROTOCOL_UMP   = 2
} OH_MidiTransportProtocol;

/**
 * @brief Midi Device Type
 * @since 24
 */
typedef enum {
    /**
     * @brief USB Midi Device.
     */
    MIDI_DEVICE_TYPE_USB = 0,

    /**
     * @brief Bluetooth LE Midi Device.
     */
    MIDI_DEVICE_TYPE_BLE = 1
} OH_MidiDeviceType;

/**
 * @brief Device connection state change action
 * @since 24
 */
typedef enum {
    /**
     * @brief A Midi device has been connected (attached).
     */
    MIDI_DEVICE_CHANGE_ACTION_CONNECTED = 0,

    /**
     * @brief A Midi device has been disconnected (detached).
     */
    MIDI_DEVICE_CHANGE_ACTION_DISCONNECTED = 1
} OH_MidiDeviceChangeAction;

/**
 * @brief Midi Event Structure (Universal)
 * Designed to handle both raw Byte Stream (Midi 1.0) and UMP.
 * @since 24
 */
typedef struct {
    /**
     * @brief Timestamp in nanoseconds.
     * Base time obtained via clock_gettime(CLOCK_MONOTONIC, &time) 
     * 0 indicates "send immediately".
     */
    uint64_t timestamp;

    /**
     * @brief Number of 32-bit words in the packet.
     * e.g., 1 for Type 2/4 (64-bit messages use 2 words)
     */
    size_t length;

    /**
     * @brief Pointer to UMP data (Must be 4-byte aligned).
     * This contains the raw UMP words (uint32_t).
     */
    uint32_t *data;
} OH_MidiEvent;

/**
 * @brief Device Information
 * Used for enumeration and display.
 * @since 24
 */
typedef struct {
    /**
     * @brief Unique identifier for the Midi device.
     */
    int64_t midiDeviceId;

    /**
     * @brief Type of the device (USB, BLE, etc.).
     */
    OH_MidiDeviceType deviceType;

    /**
     * @brief Product name of the device.
     */
    char productName[256];

    /**
     * @brief Vendor name of the device.
     */
    char vendorName[256];
} OH_MidiDeviceInformation;

/**
 * @brief Port Descriptor
 * @since 24
 */
typedef struct {
    /**
     * @brief The unique ID of the port within the device (index).
     */
    uint32_t portIndex;

    /**
     * @brief The protocol the application wishes to use.
     * If protocol is Midi1, the SDK will use 0x2 as status byte in UMP packet.
     */
    OH_MidiTransportProtocol protocol;
} OH_MidiPortDescriptor;

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
    OH_MidiPortDirection direction;

    /**
     * @brief Name of the port.
     */
    char name[256];
} OH_MidiPortInformation;

/**
 * @brief Declare the midi client
 */
typedef struct OH_MidiClientStruct OH_MidiClient;

/**
 * @brief Declare the midi device
 */
typedef struct OH_MidiDeviceStruct OH_MidiDevice;

/**
 * @brief Callback for monitoring device connection/disconnection
 *
 * @param userData User context provided during client creation.
 * @param action Device change action (Connected/Disconnected).
 * @param deviceInfo Information of the changed device.
 * @since 24
 */
typedef void (*OH_OnMidiDeviceChange)(void *userData,
                                      OH_MidiDeviceChangeAction action,
                                      OH_MidiDeviceInformation deviceInfo);

/**
 * @brief Callback for receiving Midi data (Batch Processing)
 *
 * @note The callback is invoked on a high-priority thread.
 * @note The 'events' array and its data pointers are transient and valid ONLY 
 * for the duration of this callback. If you need to keep the data, copy it.
 *
 * @param userData User context provided during port opening.
 * @param events Pointer to the array of Midi events received.
 * @param eventCount The number of events in the array.
 * @since 24
 */
typedef void (*OH_MidiInputHandler)(void *userData, const OH_MidiEvent *events, size_t eventCount);

/**
 * @brief Callback for handling client-level errors
 * * Invoked when a critical error occurs in the Midi service (e.g., service crash).
 * Applications may need to recreate the client when this occurs.
 *
 * @param userData User context provided during client creation.
 * @param code The error code indicating the cause.
 * @since 24
 */
typedef void (*OH_OnMidiError)(void *userData, OH_MidiStatusCode code);

/**
 * @brief Client callbacks structure
 * @since 24
 */
typedef struct {
    /**
     * @brief Handler for device hotplug events.
     */
    OH_OnMidiDeviceChange onDeviceChange;

    /**
     * @brief Handler for critical service errors.
     */
    OH_OnMidiError onError;
} OH_MidiCallbacks;

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_MIDI_BASE_H
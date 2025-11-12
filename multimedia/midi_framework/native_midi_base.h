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
 * @since 23
 * @version 1.0
 */
/**
 * @file native_midi_base.h
 *
 * @brief Declare underlying data structure for MIDI module.
 *
 * @library libohmidi.so
 * @syscap SystemCapability.Multimedia.Audio.Midi
 * @kit AudioKit
 * @since 23
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
 * @brief MIDI 2.0 UMP message element (32-bit)
 *
 * @since 23
 */
typedef uint32_t HMidiUmp;

/**
 * @brief HMIDI timestamp type (nanoseconds)
 *
 * @since 23
 */
typedef uint64_t HMidiTimestamp;

/**
 * @brief Device ID type
 *
 * @since 23
 */
typedef int64_t DeviceId;

/**
 * @brief HMIDI status code enumeration
 *
 * @since 23
 */
typedef enum {
    /**
     * @error Operation successful.
     *
     * @since 23
     */
    HMIDI_ERR_OK = 0,
    
    /**
     * @error Invalid parameter.
     *
     * @since 23
     */
    HMIDI_ERR_GENERIC_INVALID_ARGUMENT,
    
    /**
     * @error IPC communication failure.
     *
     * @since 23
     */
    HMIDI_ERR_GENERIC_IPC_FAILURE,
    
    /**
     * @error Insufficient result space.
     *
     * @since 23
     */
    HMIDI_ERR_INSUFFICIENT_RESULT_SPACE,
    
    /**
     * @error Driver already registered.
     *
     * @since 23
     */
    HMIDI_ERR_DRIVER_ALREADY_REGISTERED,
    
    /**
     * @error Invalid client.
     *
     * @since 23
     */
    HMIDI_ERR_INVALID_CLIENT,
    
    /**
     * @error Invalid driver.
     *
     * @since 23
     */
    HMIDI_ERR_INVALID_DRIVER,
    
    /**
     * @error Invalid device.
     *
     * @since 23
     */
    HMIDI_ERR_INVALID_DEVICE,
    
    /**
     * @error Invalid port.
     *
     * @since 23
     */
    HMIDI_ERR_INVALID_PORT,
    
    /**
     * @error Device already open.
     *
     * @since 23
     */
    HMIDI_ERR_DEVICE_ALREADY_OPEN,
    
    /**
     * @error Device not open.
     *
     * @since 23
     */
    HMIDI_ERR_DEVICE_NOT_OPEN,
    
    /**
     * @error Device activation failed.
     *
     * @since 23
     */
    HMIDI_ERR_DEVICE_ACTIVATION_FAILED
} HMidiStatusCode;

/**
 * @brief Port direction enumeration
 *
 * @since 23
 */
typedef enum {
    /**
     * Input port.
     *
     * @since 23
     */
    HMIDI_PORT_DIRECTION_INPUT  = 1,
    
    /**
     * Output port.
     *
     * @since 23
     */
    HMIDI_PORT_DIRECTION_OUTPUT = 2
} MidiPortDirection;

/**
 * @brief MIDI transport protocol enumeration
 *
 * @since 23
 */
typedef enum {
    /**
     * MIDI 1.0 protocol.
     *
     * @since 23
     */
    MIDI_TRANSPORT_PROTOCOL_MIDI1 = 1,
    
    /**
     * UMP (Universal MIDI Packet) protocol.
     *
     * @since 23
     */
    MIDI_TRANSPORT_PROTOCOL_UMP   = 2
} MidiTransportProtocol;

/**
 * @brief MIDI data protocol enumeration
 *
 * @since 23
 */
typedef enum {
    /**
     * MIDI 1.0 data format.
     *
     * @since 23
     */
    HMIDI_DATA_PROTOCOL_MIDI1 = 1,
    
    /**
     * MIDI 2.0 data format.
     *
     * @since 23
     */
    HMIDI_DATA_PROTOCOL_MIDI2 = 2
} HMidiDataProtocol;

/**
 * @brief Device change action type
 *
 * @since 23
 */
typedef enum {
    /**
     * Device connected.
     *
     * @since 23
     */
    MIDI_DEVICE_CHANGE_ACTION_CONNECTED,
    
    /**
     * Device disconnected.
     *
     * @since 23
     */
    MIDI_DEVICE_CHANGE_ACTION_DISCONNECTED
} MidiDeviceChangeAction;

/**
 * @brief API return result structure
 *
 * @since 23
 */
typedef struct {
    /**
     * @brief Status code.
     *
     * @since 23
     */
    HMidiStatusCode statusCode;
    
    /**
     * @brief Error description information.
     *
     * @since 23
     */
    char error[256];
} HMidiResult;

/**
 * @brief MIDI event chunk structure
 *
 * @since 23
 */
typedef struct {
    /**
     * @brief Buffer valid size (in uint32_t elements).
     *
     * @since 23
     */
    size_t sizeInInts;
    
    /**
     * @brief Absolute timestamp (nanoseconds).
     *
     * @since 23
     */
    HMidiTimestamp timestamp;
    
    /**
     * @brief UMP buffer pointer.
     *
     * @since 23
     */
    HMidiUmp *buffer;
} MidiEventChunk;

/**
 * @brief Device information structure
 *
 * @since 23
 */
typedef struct {
    /**
     * @brief Device unique identifier.
     *
     * @since 23
     */
    DeviceId deviceId;
    
    /**
     * @brief Product name.
     *
     * @since 23
     */
    char productName[256];
    
    /**
     * @brief Vendor name.
     *
     * @since 23
     */
    char vendorName[256];
} DeviceInformation;

/**
 * @brief Port information structure
 *
 * @since 23
 */
typedef struct {
    /**
     * @brief Port direction (input/output).
     *
     * @since 23
     */
    MidiPortDirection direction;
    
    /**
     * @brief Port name.
     *
     * @since 23
     */
    char name[256];
    
    /**
     * @brief Transport protocol.
     *
     * @since 23
     */
    MidiTransportProtocol transportProtocol;
} MidiPortInformation;

/**
 * @brief MIDI device structure with port information
 *
 * @since 23
 */
typedef struct {
    /**
     * @brief Device ID.
     *
     * @since 23
     */
    DeviceId deviceId;
    
    /**
     * @brief Number of ports.
     *
     * @since 23
     */
    size_t numPorts;
    
    /**
     * @brief Port information array.
     *
     * @since 23
     */
    MidiPortInformation *ports;
} MidiDevice;

/**
 * @brief UMP input handler function type
 *
 * @param context User context pointer
 * @param events Received MIDI event list
 * @param event_size Length of received MIDI event list
 * @since 23
 */
typedef void (*MidiUmpInputHandler)(void *context, MidiEventChunk *events, size_t event_size);

/**
 * @brief Device change handler function type
 *
 * @param userData User context
 * @param action Device change action
 * @param deviceInfo Changed device information
 * @since 23
 */
typedef void (*MidiDeviceChangeHandler)(void *userData, 
                                         MidiDeviceChangeAction action, 
                                         DeviceInformation deviceInfo);

/**
 * @brief Declare the MIDI client.
 * The handle of MIDI client is used for MIDI client related functions.
 *
 * @since 23
 */
typedef struct MidiClientStruct MidiClient;

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_MIDI_BASE_H
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
 * @file native_midi.h
 *
 * @brief Declare MIDI related interfaces.
 *
 * This file interfaces are used for MIDI device management, 
 * MIDI message sending and receiving, and device status monitoring.
 *
 * @library libohmidi.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 24
 * @version 1.0
 */
#ifndef NATIVE_MIDI_H
#define NATIVE_MIDI_H

#include "native_midi_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create MIDI client instance
 *
 * @param[out] client Pointer to receive the new client handle.
 * @param callbacks Callback structure for system events.
 * @param userData User context to be passed to callbacks.
 * @return {@link #MIDI_STATUS_OK} if execution succeeds,
 * or {@link #MIDI_STATUS_GENERIC_INVALID_ARGUMENT} if client is nullptr.
 * @since 24
 */
MidiStatusCode OH_MIDI_CreateClient(MidiClient **client, OH_MIDI_Callbacks callbacks, void *userData);

/**
 * @brief Destroy MIDI client and release resources
 *
 * @param client Target client handle.
 * @return {@link #MIDI_STATUS_OK} if execution succeeds.
 * @since 24
 */
MidiStatusCode OH_MIDI_DestroyClient(MidiClient *client);

// ============================================================================================
// Device Enumeration
// ============================================================================================

/**
 * @brief Enumerate all MIDI devices (Double Call Pattern)
 *
 * Pattern:
 * 1. Call with informations=nullptr to get the count in numDevices.
 * 2. Allocate memory.
 * 3. Call with allocated buffer to get data.
 *
 * @param client Target client handle.
 * @param[out] informations User-allocated buffer, or nullptr.
 * @param[in,out] numDevices Capacity (in) / Actual count (out).
 * @return {@link #MIDI_STATUS_OK} if execution succeeds,
 * or {@link #MIDI_STATUS_INSUFFICIENT_RESULT_SPACE} if buffer is too small.
 * @since 24
 */
MidiStatusCode OH_MIDI_GetDevices(MidiClient *client, DeviceInformation *informations, size_t *numDevices);

// ============================================================================================
// Device Management
// ============================================================================================

/**
 * @brief Open MIDI device
 *
 * @param client Target client handle.
 * @param deviceId Device ID.
 * @param[out] deviceHandle Pointer to receive the device handle.
 * @return {@link #MIDI_STATUS_OK} if execution succeeds.
 * @since 24
 */
MidiStatusCode OH_MIDI_OpenDevice(MidiClient *client, int64_t deviceId, MidiDevice **deviceHandle);

/**
 * @brief Open MIDI BLE device
 *
 * @param client Target client handle.
 * @param deviceAddress BLE Mac Address.
 * @param[out] deviceHandle Pointer to receive the device handle.
 * @return {@link #MIDI_STATUS_OK} if execution succeeds.
 * @since 24
 */
MidiStatusCode OH_MIDI_OpenBleDevice(MidiClient *client, const char *deviceAddress, MidiDevice **deviceHandle);

/**
 * @brief Close MIDI device
 *
 * @param deviceHandle Target device handle.
 * @return {@link #MIDI_STATUS_OK} if execution succeeds.
 * @since 24
 */
MidiStatusCode OH_MIDI_CloseDevice(MidiDevice *deviceHandle);

// ============================================================================================
// Port Management
// ============================================================================================

/**
 * @brief Get port information (Double Call Pattern)
 *
 * @param device Target device handle.
 * @param[out] portInfos User-allocated buffer, or nullptr.
 * @param[in,out] numPorts Capacity (in) / Actual count (out).
 * @return {@link #MIDI_STATUS_OK} if execution succeeds.
 * @since 24
 */
MidiStatusCode OH_MIDI_GetDevicePorts(MidiDevice *device, MidiPortInformation *portInfos, size_t *numPorts);

/**
 * @brief Open MIDI input port (Receive Data)
 *
 * Registers a callback to receive MIDI data in batches.
 *
 * @param device Target device handle.
 * @param descriptor Port index and protocol configuration.
 * @param inputHandler Callback function invoked when data is available.
 * @param userData Context pointer passed to the callback.
 * @return {@link #MIDI_STATUS_OK} if execution succeeds,
 * or {@link #MIDI_STATUS_INVALID_DEVICE_HANDLE} if device is invalid.
 * @since 24
 */
MidiStatusCode OH_MIDI_OpenInputPort(MidiDevice *device,
                                     MidiPortDescriptor descriptor,
                                     MidiInputHandler inputHandler,
                                     void *userData);

/**
 * @brief Open MIDI output port (Send Data)
 *
 * @param device Target device handle.
 * @param descriptor Port index and protocol configuration.
 * @return {@link #MIDI_STATUS_OK} if execution succeeds.
 * @since 24
 */
MidiStatusCode OH_MIDI_OpenOutputPort(MidiDevice *device,
                                      MidiPortDescriptor descriptor);

/**
 * @brief Close MIDI input port
 *
 * @param device Target device handle.
 * @param portIndex Port index.
 * @return {@link #MIDI_STATUS_OK} if execution succeeds.
 * @since 24
 */
MidiStatusCode OH_MIDI_CloseInputPort(MidiDevice *device, uint32_t portIndex);

/**
 * @brief Close MIDI output port
 *
 * @param device Target device handle.
 * @param portIndex Port index.
 * @return {@link #MIDI_STATUS_OK} if execution succeeds.
 * @since 24
 */
MidiStatusCode OH_MIDI_CloseOutputPort(MidiDevice *device, uint32_t portIndex);

// ============================================================================================
// Data Transfer
// ============================================================================================

/**
 * @brief Send MIDI messages (Batch, Non-blocking & Atomic)
 *
 * Attempts to write an array of events to the shared memory buffer.
 *
 * - Atomicity: Each event in the array is treated atomically. 
 * It is either fully written or not written at all.
 * - Partial Success: If the buffer becomes full midway, the function returns 
 * {@link #MIDI_STATUS_WOULD_BLOCK} and sets eventsWritten to the number of events 
 * successfully enqueued.
 *
 * @param device Target device handle.
 * @param descriptor Target port and protocol.
 * @param events Pointer to the array of events to send.
 * @param eventCount Number of events in the array.
 * @param[out] eventsWritten (Optional) Returns the number of events successfully consumed.
 * @return {@link #MIDI_STATUS_OK} if all events were written.
 * @return {@link #MIDI_STATUS_WOULD_BLOCK} if buffer is full (check eventsWritten).
 * @return {@link #MIDI_STATUS_INVALID_...} if arguments are invalid.
 * @since 24
 */
MidiStatusCode OH_MIDI_Send(MidiDevice *device,
                            MidiPortDescriptor descriptor,
                            const MidiEvent *events,
                            uint32_t eventCount,
                            uint32_t *eventsWritten);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_MIDI_H
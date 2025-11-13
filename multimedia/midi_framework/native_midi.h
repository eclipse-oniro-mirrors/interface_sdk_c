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
 * @brief Enumerate all MIDI devices
 *
 * @param[out] numDevices Returned device count
 * @return Device information array, caller must free the returned pointer using free()
 * @return {@link #HMIDI_ERR_OK} if execution succeeds,
 * or {@link #HMIDI_ERR_GENERIC_INVALID_ARGUMENT} if numDevices is nullptr,
 * or {@link #HMIDI_ERR_GENERIC_IPC_FAILURE} if IPC communication fails.
 * @since 24
 */
DeviceInformation *OH_MIDI_GetDevices(size_t *numDevices);

/**
 * @brief Create MIDI client and connect to system service
 *
 * @return Client pointer, returns nullptr if creation fails
 * @return {@link #HMIDI_ERR_OK} if execution succeeds,
 * or {@link #HMIDI_ERR_GENERIC_IPC_FAILURE} if system service connection fails,
 * or {@link #HMIDI_ERR_INSUFFICIENT_RESULT_SPACE} if system resources are insufficient.
 * @since 24
 */
MidiClient* OH_MIDI_CreateClient();

/**
 * @brief Destroy MIDI client and disconnect
 *
 * @param client Target client
 * @return {@link #HMIDI_ERR_OK} if execution succeeds,
 * or {@link #HMIDI_ERR_INVALID_CLIENT} if client is invalid or already destroyed,
 * or {@link #HMIDI_ERR_GENERIC_IPC_FAILURE} if IPC communication fails during destruction.
 * @since 24
 */
HMidiStatusCode OH_MIDI_DestroyClient(MidiClient *client);

/**
 * @brief Register device change notification handler
 *
 * @param client Target client
 * @param handler Handler function
 * @param userData User context
 * @return {@link #HMIDI_ERR_OK} if execution succeeds,
 * or {@link #HMIDI_ERR_INVALID_CLIENT} if client is invalid,
 * or {@link #HMIDI_ERR_GENERIC_INVALID_ARGUMENT} if handler is nullptr.
 * @since 24
 */
HMidiStatusCode OH_MIDI_RegisterDeviceChangeHandler(MidiClient *client, 
                                                    MidiDeviceChangeHandler handler, 
                                                    void *userData);

/**
 * @brief Unregister device change notification handler
 *
 * @param client Target client
 * @return {@link #HMIDI_ERR_OK} if execution succeeds,
 * or {@link #HMIDI_ERR_INVALID_CLIENT} if client is invalid,
 * or {@link #HMIDI_ERR_GENERIC_IPC_FAILURE} if IPC communication fails.
 * @since 24
 */
HMidiStatusCode OH_MIDI_UnregisterDeviceChangeHandler(MidiClient *client);

/**
 * @brief Open MIDI device
 *
 * @param client Target client
 * @param deviceId Device ID
 * @return Device handle with operation result, returns nullptr if opening fails
 * @return {@link #HMIDI_ERR_OK} if execution succeeds,
 * or {@link #HMIDI_ERR_INVALID_CLIENT} if client is invalid,
 * or {@link #HMIDI_ERR_INVALID_DEVICE} if deviceId is invalid,
 * or {@link #HMIDI_ERR_DEVICE_ALREADY_OPEN} if device is already open,
 * or {@link #HMIDI_ERR_DEVICE_ACTIVATION_FAILED} if device activation fails.
 * @note This is a synchronous operation. For asynchronous operations, please call in your own thread.
 * @since 24
 */
MidiDevice* OH_MIDI_OpenDevice(MidiClient *client, DeviceId deviceId);

/**
 * @brief Close MIDI device
 *
 * @param client Target client
 * @param deviceId Target device ID
 * @return {@link #HMIDI_ERR_OK} if execution succeeds,
 * or {@link #HMIDI_ERR_INVALID_CLIENT} if client is invalid,
 * or {@link #HMIDI_ERR_INVALID_DEVICE} if deviceId is invalid,
 * or {@link #HMIDI_ERR_DEVICE_NOT_OPEN} if device is not open.
 * @since 24
 */
HMidiStatusCode OH_MIDI_CloseDevice(MidiClient *client, DeviceId deviceId);

/**
 * @brief Open MIDI input port
 *
 * @param client Target client
 * @param deviceId Target device ID
 * @param portIndex Port index
 * @param inputCallback Data reception callback function
 * @param userData Callback context
 * @return {@link #HMIDI_ERR_OK} if execution succeeds,
 * or {@link #HMIDI_ERR_INVALID_CLIENT} if client is invalid,
 * or {@link #HMIDI_ERR_INVALID_DEVICE} if deviceId is invalid,
 * or {@link #HMIDI_ERR_INVALID_PORT} if portIndex is invalid,
 * or {@link #HMIDI_ERR_GENERIC_INVALID_ARGUMENT} if inputCallback is nullptr,
 * or {@link #HMIDI_ERR_DEVICE_NOT_OPEN} if device is not open.
 * @since 24
 */
HMidiStatusCode OH_MIDI_OpenInputPort(MidiClient *client, DeviceId deviceId, size_t portIndex,
                                      MidiUmpInputHandler inputCallback, void *userData);

/**
 * @brief Open MIDI output port
 *
 * @param client Target client
 * @param deviceId Target device ID
 * @param portIndex Port index
 * @return {@link #HMIDI_ERR_OK} if execution succeeds,
 * or {@link #HMIDI_ERR_INVALID_CLIENT} if client is invalid,
 * or {@link #HMIDI_ERR_INVALID_DEVICE} if deviceId is invalid,
 * or {@link #HMIDI_ERR_INVALID_PORT} if portIndex is invalid,
 * or {@link #HMIDI_ERR_DEVICE_NOT_OPEN} if device is not open.
 * @since 24
 */
HMidiStatusCode OH_MIDI_OpenOutputPort(MidiClient *client, DeviceId deviceId, size_t portIndex);

/**
 * @brief Close MIDI input port
 *
 * @param client Target client
 * @param deviceId Target device ID
 * @param portIndex Port index
 * @return {@link #HMIDI_ERR_OK} if execution succeeds,
 * or {@link #HMIDI_ERR_INVALID_CLIENT} if client is invalid,
 * or {@link #HMIDI_ERR_INVALID_DEVICE} if deviceId is invalid,
 * or {@link #HMIDI_ERR_INVALID_PORT} if portIndex is invalid.
 * @since 24
 */
HMidiStatusCode OH_MIDI_CloseInputPort(MidiClient *client, DeviceId deviceId, size_t portIndex);

/**
 * @brief Close MIDI output port
 *
 * @param client Target client
 * @param deviceId Target device ID
 * @param portIndex Port index
 * @return {@link #HMIDI_ERR_OK} if execution succeeds,
 * or {@link #HMIDI_ERR_INVALID_CLIENT} if client is invalid,
 * or {@link #HMIDI_ERR_INVALID_DEVICE} if deviceId is invalid,
 * or {@link #HMIDI_ERR_INVALID_PORT} if portIndex is invalid.
 * @since 24
 */
HMidiStatusCode OH_MIDI_CloseOutputPort(MidiClient *client, DeviceId deviceId, size_t portIndex);

/**
 * @brief Send MIDI message through output port
 *
 * @param client Target client
 * @param deviceId Target device ID
 * @param portIndex Port index
 * @param events Event list to be sent
 * @param event_size Length of event list to be sent
 * @return {@link #HMIDI_ERR_OK} if execution succeeds,
 * or {@link #HMIDI_ERR_INVALID_CLIENT} if client is invalid,
 * or {@link #HMIDI_ERR_INVALID_DEVICE} if deviceId is invalid,
 * or {@link #HMIDI_ERR_INVALID_PORT} if portIndex is invalid,
 * or {@link #HMIDI_ERR_GENERIC_INVALID_ARGUMENT} if events is nullptr or event_size is 0,
 * or {@link #HMIDI_ERR_GENERIC_IPC_FAILURE} if message sending fails.
 * @since 24
 */
HMidiStatusCode OH_MIDI_Send(MidiClient *client, DeviceId deviceId, size_t portIndex, 
                             MidiEventChunk *events, size_t event_size);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_MIDI_H
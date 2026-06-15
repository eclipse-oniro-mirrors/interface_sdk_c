/*
 * Copyright (C) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup Core
 * @{
 *
 * @brief The AudioVivid module provides builder for audio vivid meta data.
 *
 * @since 26.0.0
 */

/**
 * @file native_audio_vivid.h
 *
 * @brief The file declares the functions and enums related to Audio Vivid.
 *
 * @kit AVCodecKit
 * @library libnative_media_core.so
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 26.0.0
 */

#ifndef NATIVE_AUDIO_VIVID_H
#define NATIVE_AUDIO_VIVID_H

#include "native_avformat.h"
#include "native_averrors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the signal formats of the Audio Vivid encoder.
 *
 * @since 26.0.0
 */
typedef enum OH_AudioVividSignalFormat {
    /**
     * Mono. The encoder accepts mono data and internally sets the channel layout to {@link OH_AudioChannelLayout}.
     * CH_LAYOUT_MONO.
     * @since 26.0.0
     */
    OH_AUDIO_VIVID_SIGNAL_FORMAT_MONO = 0,
    /**
     * Stereo. The encoder accepts stereo data and internally sets the channel layout to {@link OH_AudioChannelLayout}.
     * CH_LAYOUT_STEREO.
     * @since 26.0.0
     */
    OH_AUDIO_VIVID_SIGNAL_FORMAT_STEREO = 1,
    /**
     * Multi-channel audio. The encoder supports the following channel layouts: {@link OH_AudioChannelLayout}.
     * CH_LAYOUT_5POINT1, {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1POINT2, {@link OH_AudioChannelLayout}.
     * CH_LAYOUT_5POINT1POINT4, {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1, {@link OH_AudioChannelLayout}.
     * CH_LAYOUT_7POINT1POINT2, and {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1POINT4.
     * @since 26.0.0
     */
    OH_AUDIO_VIVID_SIGNAL_FORMAT_MC = 2,
    /**
     * Hybrid mode, including a bed and an object. The bed supports the following channel layouts:
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_STEREO, {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1POINT2, {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1POINT4,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1, {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1POINT2, and
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1POINT4.
     * @since 26.0.0
     */
    OH_AUDIO_VIVID_SIGNAL_FORMAT_MIX = 4,
} OH_AudioVividSignalFormat;

/**
 * @brief Represents a position in Cartesian coordinates.
 *
 * Cartesian coordinates use x, y, and z axes to define a postion in three-dimensional space.
 *
 * @since 26.0.0
 */
typedef struct OH_CartesianPosition {
    /**
     * Normalized X coordinate of an object's left/right dimension when object is in the Cartesian coordinate system.
     * Value range is [-1.0, 1.0].
     * @since 26.0.0
     */
    float x;
    /**
     * Normalized Y coordinate of an object's front/back dimension when object is in the Cartesian coordinate system.
     * Value range is [-1.0, 1.0].
     * @since 26.0.0
     */
    float y;
    /**
     * Normalized Z coordinate of an object's upper/lower dimension when object is in the Cartesian coordinate system.
     * Value range is [-1.0 1.0].
     * @since 26.0.0
     */
    float z;
} OH_CartesianPosition;

/**
 * @brief Represents a position in polar (spherical) coordinates.
 *
 * Polar coordinates use azimuth, elevation, and distance to define a position in three-dimensional space.
 * @since 26.0.0
 */
typedef struct OH_PolarPosition {
    /**
     * Indicates the azimuth angle of the object's location when the polar coordinate system is used.
     * Value range is [-180.0, 180.0], where 0.0 is front, 90.0 is left, -90.0 is right, -180.0 or 180.0 is back.
     * @since 26.0.0
     */
    float azimuth;
    /**
     * Indicates the elevation angle of the object's location when the polar coordinate system is used.
     * Value range is [-90.0, 90.0], where 0.0 is horizontal, 90.0 is up, -90.0 is down.
     * @since 26.0.0
     */
    float elevation;
    /**
     * Normalized distance of an object's location when an object is placed in the polar coordinate system.
     * Value range is [0.0, 1.0].
     * @since 26.0.0
     */
    float distance;
} OH_PolarPosition;

/**
 * @brief Represents the position of an audio object in three-dimensional space.
 *
 * The position can be expressed in either Cartesian or polar coordinates.
 *
 * @since 26.0.0
 */
typedef struct OH_AudioObjectPosition {
    /**
     * Indicates whether the position is in Cartesian coordinates.
     * true: use pos.cartesian, false: use pos.polar.
     * @since 26.0.0
     */
    bool isCartesian;
    /**
     * @brief Union containing the position data in either Cartesian or polar coordinates.
     *
     * @since 26.0.0
     */
    union {
        /**
         * Represents position by Cartesian coordinates.
         * @since 26.0.0
         */
        OH_CartesianPosition cartesian;
        /**
         * Represents position by polar coordinates.
         * @since 26.0.0
         */
        OH_PolarPosition polar;
    } pos;
} OH_AudioObjectPosition;

/**
 * @brief Forward declaration of OH_AudioVividMetaBuilder.
 *
 * @since 26.0.0
 */
typedef struct OH_AudioVividMetaBuilderStruct OH_AudioVividMetaBuilder;

/**
 * @brief Creates an Audio Vivid metadata builder.
 *
 * @param builder Output parameter, which is used to obtain the double pointer to the **OH_AudioVividMetaBuilder**
 *     instance.
 * @param format Pointer to **OH_AVFormat** that contains the audio format information.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The **builder** or **format** parameter is a null pointer or invalid.
 *     <br>{@link AV_ERR_UNSUPPORT}: This function is not supported on the device.
 *     <br>{@link AV_ERR_UNKNOWN}: Failed to create the builder. This is an unknown error. Check the log for details.
 * @note **Lifecycle Management:**
 *     The instance created by this function must be manually released by calling
 *     {@link OH_AudioVividMetaBuilder_Destroy} when it is no longer needed to
 *     prevent memory leaks.
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_Create(OH_AudioVividMetaBuilder **builder, const OH_AVFormat *format);

/**
 * @brief Updates the position of the audio object when the Audio Vivid signal format is
 * {@link OH_AudioVividSignalFormat}.OH_AUDIO_VIVID_SIGNAL_FORMAT_MIX. In this signal format, the channel arrangement
 * in the input encoded Pulse Code Modulation (PCM) data is as follows: bed channels come first, followed by object
 * channels.
 *
 * The object channels correspond to **objectIndex** in sequence, starting from 0.
 *
 * @param builder Pointer to **OH_AudioVividMetaBuilder**.
 * @param objectIndex Index of the audio object to be updated, starting from 0. The value cannot be greater than
 *     {@link OH_MD_KEY_AUDIO_OBJECT_NUMBER} set in the **format** parameter passed to
 *     {@link OH_AudioVividMetaBuilder_Create} for creating the builder.
 * @param pos New position of the audio object source.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The **builder** parameter is a null pointer or invalid, or the **objectIndex**
 *     or **pos** parameter is invalid.
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_UpdateObjectPos(OH_AudioVividMetaBuilder *builder,
    int32_t objectIndex, OH_AudioObjectPosition pos);

/**
 * @brief Updates the linear gain of audio object rendering when the Audio Vivid signal format is
 * {@link OH_AudioVividSignalFormat}.OH_AUDIO_VIVID_SIGNAL_FORMAT_MIX.
 *
 * @param builder Pointer to **OH_AudioVividMetaBuilder**.
 * @param objectIndex Index of the audio object to be updated, starting from 0. The value cannot be greater than
 *     {@link OH_MD_KEY_AUDIO_OBJECT_NUMBER} set in the **format** parameter passed to
 *     {@link OH_AudioVividMetaBuilder_Create} for creating the builder.
 * @param gain Linear gain applied during object rendering. The value range is [0.0, 6.0], where **0.0** indicates
 *     silence, and **1.0** indicates no change. This parameter is optional. If it is not set, no gain is applied.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The **builder** parameter is a null pointer or invalid, or the **objectIndex**
 *     or **gain** parameter is invalid.
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_UpdateObjectGain(OH_AudioVividMetaBuilder *builder,
    int32_t objectIndex, float gain);
/**
 * @brief Obtains the length of metadata.
 *
 * @param builder Pointer to **OH_AudioVividMetaBuilder**.
 * @param withStaticMeta Whether the output length includes static metadata. The value **true** indicates that the
 *     output length includes static metadata, and the value **false** indicates that the output length includes only
 *     dynamic metadata.
 * @param len Pointer used to receive the metadata length. The unit is bytes.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The **builder** parameter is a null pointer or invalid, or the **len** parameter
 *     is a null pointer.
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_GetMetaLen(const OH_AudioVividMetaBuilder *builder, bool withStaticMeta,
    int32_t *len);

/**
 * @brief Obtains the metadata buffer.
 *
 * @param builder Pointer to **OH_AudioVividMetaBuilder**.
 * @param withStaticMeta Whether the output buffer includes static metadata. The value **true** indicates that the
 *     output buffer includes static metadata, and the value **false** indicates that the output buffer includes only
 *     dynamic metadata.
 * @param buffer Pointer to the buffer for receiving the metadata.
 * @param len Buffer length, in bytes.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The **builder** parameter is a null pointer or invalid, the **buffer** parameter
 *     is a null pointer, or the **len** parameter value is insufficient.
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_GetMeta(const OH_AudioVividMetaBuilder *builder, bool withStaticMeta,
    uint8_t *buffer, int32_t len);

/**
 * @brief Destroys an Audio Vivid metadata builder and releases resources.
 *
 * @param builder Pointer to **OH_AudioVividMetaBuilder** to be destroyed.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The **builder** parameter is a null pointer.
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_Destroy(OH_AudioVividMetaBuilder *builder);

/**
 * @brief Creates an empty Audio Vivid metadata builder.
 *
 * This function is used for merging metadata scenarios. After creating an empty builder,
 * you can update base metadata by calling {@link OH_AudioVividMetaBuilder_UpdateBaseMeta},
 * then add, modify, or remove objects.
 *
 * @param builder Output Parameter. Pointer to retrieve the OH_AudioVividMetaBuilder instance pointer.
 * @return Returns AV_ERR_OK if successful, otherwise returns a specific error code, refer to {@link OH_AVErrCode}.
 * {@link AV_ERR_INVALID_VAL}, builder is nullptr.
 * {@link AV_ERR_UNSUPPORT}, current device not support this function.
 * {@link AV_ERR_UNKNOWN}, create builder fail with unknown error. For details, check logs.
 * @note **Lifecycle Management:**
 *      The instance created by this function must be manually released by calling
 *      {@link OH_AudioVividMetaBuilder_Destroy} when it is no longer needed to
 *      prevent memory leaks.
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_CreateEmptyBuilder(OH_AudioVividMetaBuilder **builder);

/**
 * @brief Updates the base metadata of the builder.
 *
 * The buffer contains complete Audio Vivid metadata, which may include static metadata
 * and/or dynamic metadata. The builder will retain the soundbed and object information
 * from the base metadata.
 *
 * @param builder Pointer to the OH_AudioVividMetaBuilder.
 * @param buffer Pointer to the buffer containing the base metadata data.
 * @param len Length of the buffer in bytes.
 * @return Returns AV_ERR_OK if successful, otherwise returns a specific error code, refer to {@link OH_AVErrCode}.
 * {@link AV_ERR_INVALID_VAL}, builder is nullptr or invalid, buffer is nullptr or len is invalid.
 * @note **Constraint:**
 *      The total number of soundbed channels plus base objects plus added objects must not exceed 16.
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_UpdateBaseMeta(OH_AudioVividMetaBuilder *builder, const uint8_t *buffer,
    int32_t len);

/**
 * @brief Adds a new audio object to the builder.
 *
 * After adding an object, you can update its position and gain using
 * {@link OH_AudioVividMetaBuilder_UpdateObjectPos} and {@link OH_AudioVividMetaBuilder_UpdateObjectGain}.
 *
 * @param builder Pointer to the OH_AudioVividMetaBuilder.
 * @param objectIndex Output parameter. Pointer to receive the index of the newly added object.
 * @return Returns AV_ERR_OK if successful, otherwise returns a specific error code, refer to {@link OH_AVErrCode}.
 * {@link AV_ERR_INVALID_VAL}, builder is nullptr or invalid, objectIndex is nullptr.
 * {@link AV_ERR_UNKNOWN}, add object fail with unknown error. For details, check logs.
 * @note **Constraint:**
 *      The total number of soundbed channels plus base objects plus added objects must not exceed 16.
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_AddObject(OH_AudioVividMetaBuilder *builder, int32_t *objectIndex);

/**
 * @brief Removes an audio object from the builder.
 *
 * Only objects added by {@link OH_AudioVividMetaBuilder_AddObject} can be removed.
 * Base objects from the base metadata cannot be removed. After removal, the indices
 * of remaining objects remain unchanged.
 *
 * @param builder Pointer to the OH_AudioVividMetaBuilder.
 * @param objectIndex Index of the audio object to remove.
 * @return Returns AV_ERR_OK if successful, otherwise returns a specific error code, refer to {@link OH_AVErrCode}.
 * {@link AV_ERR_INVALID_VAL}, builder is nullptr or invalid, objectIndex is invalid.
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_RemoveObject(OH_AudioVividMetaBuilder *builder, int32_t objectIndex);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_VIVID_H

/** @} */
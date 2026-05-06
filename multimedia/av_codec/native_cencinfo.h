/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup Multimedia_Drm
 * @{
 *
 * @brief This feature enables third-party applications to implement the
 * media decapsulation and demultiplexing functions by themselves instead
 * of using the functions provided by the system.
 *
 * After the DRM instance and session are created, the decryption interface
 * provided by the DRM can be invoked for decryption. The decryption parameter
 * structure defines the transmission format of decryption parameters.
 *
 * @since 12
 */
 /**
 * @file native_cencinfo.h
 *
 * @brief The file declares the native APIs used to set decryption parameters.
 *
 * @kit AVCodecKit
 * @library libnative_media_avcencinfo.so
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @since 12
 */

#ifndef NATIVE_AVCENCINFO_H
#define NATIVE_AVCENCINFO_H

#include <stdint.h>
#include "native_averrors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct describes a native object for the media memory interface.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_AVBuffer OH_AVBuffer;
/**
 * @brief The struct describes the audio/video Common Encryption Scheme (CENC) information.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_AVCencInfo OH_AVCencInfo;

/**
 * @brief The length of the key ID is 16 bytes.
 *
 * @since 12
 * @version 1.0
 */
#define DRM_KEY_ID_SIZE 16
/**
 * @brief The length of the Initialization Vector (IV) is 16 bytes.
 *
 * @since 12
 * @version 1.0
 */
#define DRM_KEY_IV_SIZE 16
/**
 * @brief The maximum number of subsamples is 64.
 *
 * @since 12
 * @version 1.0
 */
#define DRM_KEY_MAX_SUB_SAMPLE_NUM 64

/**
 * @brief Enumerates the DRM CENC algorithm types.
 *
 * @since 12
 * @version 1.0
 */
typedef enum DrmCencAlgorithm {
    /**
     * Unencrypted.
     */
    DRM_ALG_CENC_UNENCRYPTED = 0x0,
    /**
     * Aes ctr.
     */
    DRM_ALG_CENC_AES_CTR = 0x1,
    /**
     * Aes wv.
     */
    DRM_ALG_CENC_AES_WV = 0x2,
    /**
     * Aes cbc.
     */
    DRM_ALG_CENC_AES_CBC = 0x3,
    /**
     * Sm4 cbc.
     */
    DRM_ALG_CENC_SM4_CBC = 0x4,
    /**
     * Sm4 ctr.
     */
    DRM_ALG_CENC_SM4_CTR = 0x5
} DrmCencAlgorithm;

/**
 * @brief Enumerates the modes for setting the key ID, IV, and subsample in the CENC information.
 *
 * @since 12
 * @version 1.0
 */
typedef enum DrmCencInfoMode {
    /* key/iv/subsample set. */
    DRM_CENC_INFO_KEY_IV_SUBSAMPLES_SET = 0x0,
    /* key/iv/subsample not set. */
    DRM_CENC_INFO_KEY_IV_SUBSAMPLES_NOT_SET = 0x1
} DrmCencInfoMode;

/**
 * @brief The struct describes the subsample type.
 *
 * @since 12
 * @version 1.0
 */
typedef struct DrmSubsample {
    /* Clear header len. */
    uint32_t clearHeaderLen;
    /* Payload Len. */
    uint32_t payLoadLen;
} DrmSubsample;

/**
 * @brief Creates an OH_AVCencInfo instance for setting the CENC information.
 *
 * @return Pointer to the OH_AVCencInfo instance created. If the operation fails, nullptr is returned.
 *     <br>The possible causes of an operation failure are as follows: The application address space is full,
 *     or the data in the object fails to be initialized.
 * @since 12
 * @version 1.0
 */
OH_AVCencInfo *OH_AVCencInfo_Create();

/**
 * @brief Destroys an OH_AVCencInfo instance and clears internal resources.
 *
 * An instance can be destroyed only once. Do not use the instance until it is created again. You are advised to set
 * the instance pointer to nullptr once the instance is destroyed.
 *
 * @param cencInfo Pointer to an OH_AVCencInfo instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **cencInfo** is null.
 * @since 12
 * @version 1.0
 */
OH_AVErrCode OH_AVCencInfo_Destroy(OH_AVCencInfo *cencInfo);

/**
 * @brief Sets an encryption algorithm of the CENC information.
 *
 * @param cencInfo Pointer to an OH_AVCencInfo instance.
 * @param algo Encryption algorithm.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **cencInfo** is null.
 * @since 12
 * @version 1.0
 */
OH_AVErrCode OH_AVCencInfo_SetAlgorithm(OH_AVCencInfo *cencInfo, enum DrmCencAlgorithm algo);

/**
 * @brief Sets the key ID and IV in the CENC information.
 *
 * @param cencInfo Pointer to an OH_AVCencInfo instance.
 * @param keyId Pointer to the key ID.
 * @param keyIdLen Length of the key ID.
 * @param iv Pointer to the IV.
 * @param ivLen Length of the IV.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **cencInfo**, **keyId**, or **iv** is null,
 *     **keyIdLen** is not equal to **DRM_KEY_ID_SIZE**, **ivLen** is not equal to **DRM_KEY_IV_SIZE**,
 *     the key ID or IV fails to be copied.
 * @since 12
 * @version 1.0
 */
OH_AVErrCode OH_AVCencInfo_SetKeyIdAndIv(OH_AVCencInfo *cencInfo, uint8_t *keyId,
    uint32_t keyIdLen, uint8_t *iv, uint32_t ivLen);

/**
 * @brief Sets the subsample information in the CENC information.
 *
 * @param cencInfo Pointer to an OH_AVCencInfo instance.
 * @param encryptedBlockCount Number of encrypted blocks.
 * @param skippedBlockCount Number of non-encrypted blocks.
 * @param firstEncryptedOffset Offset of the first encrypted payload.
 * @param subsampleCount Number of subsamples.
 * @param subsamples Pointer to the subsamples.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **cencInfo** is null, **subsampleCount** is greater than
 *     **DRM_KEY_MAX_SUB_SAMPLE_NUM**, or **subsamples** is null.
 * @since 12
 * @version 1.0
 */
OH_AVErrCode OH_AVCencInfo_SetSubsampleInfo(OH_AVCencInfo *cencInfo, uint32_t encryptedBlockCount,
    uint32_t skippedBlockCount, uint32_t firstEncryptedOffset, uint32_t subsampleCount, DrmSubsample *subsamples);

/**
 * @brief Sets the CENC information mode.
 *
 * @param cencInfo Pointer to an OH_AVCencInfo instance.
 * @param mode CENC information mode, indicating whether the key ID, IV, and subsample are set.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **cencInfo** is null.
 * @since 12
 * @version 1.0
 */
OH_AVErrCode OH_AVCencInfo_SetMode(OH_AVCencInfo *cencInfo, enum DrmCencInfoMode mode);

/**
 * @brief Sets the CENC information to an AVBuffer.
 *
 * @param cencInfo Pointer to an OH_AVCencInfo instance.
 * @param buffer Pointer to the frame buffer that carries data.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **cencInfo**, **buffer**, **buffer->buffer_**,
 *     or **buffer->buffer_->meta_** is null.
 * @since 12
 * @version 1.0
 */
OH_AVErrCode OH_AVCencInfo_SetAVBuffer(OH_AVCencInfo *cencInfo, OH_AVBuffer *buffer);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVCENCINFO_H
/** @} */
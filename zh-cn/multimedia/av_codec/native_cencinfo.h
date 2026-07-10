/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup Multimedia_Drm
 * @{
 *
 * @brief 该功能使第三方应用程序可以自行实现媒体解封装和解复用功能，而不是使用系统提供的。\n
 * 在创建DRM实例和会话后，可以调用DRM提供的解密接口进行解密。解密参数结构定义了解密参数的传输格式。
 * @since 12
 */

/**
 * @file native_cencinfo.h
 *
 * @brief 声明用于设置解密参数的Native API。
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_cencinfo.h>
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
 * @brief AVBuffer结构。
 * @since 12
 * @version 1.0
 */
typedef struct OH_AVBuffer OH_AVBuffer;
/**
 * @brief AVCencInfo结构。
 * @since 12
 * @version 1.0
 */
typedef struct OH_AVCencInfo OH_AVCencInfo;
/**
 * @brief Key id长度为16字节。
 * @since 12
 * @version 1.0
 */
#define DRM_KEY_ID_SIZE 16
/**
 * @brief Iv长度为16字节。
 * @since 12
 * @version 1.0
 */
#define DRM_KEY_IV_SIZE 16
/**
 * @brief 最大的Subsample数量为64个。
 * @since 12
 * @version 1.0
 */
#define DRM_KEY_MAX_SUB_SAMPLE_NUM 64

/**
 * @brief Drm CENC算法类型。
 * @since 12
 * @version 1.0
 */
typedef enum DrmCencAlgorithm {
    /**
     * 不加密算法。
     */
    DRM_ALG_CENC_UNENCRYPTED = 0x0,
    /**
     * AES CTR算法。
     */
    DRM_ALG_CENC_AES_CTR = 0x1,
    /**
     * AES WV算法。
     */
    DRM_ALG_CENC_AES_WV = 0x2,
    /**
     * AES CBC算法。
     */
    DRM_ALG_CENC_AES_CBC = 0x3,
    /**
     * SM4 CBC算法。
     */
    DRM_ALG_CENC_SM4_CBC = 0x4,
    /**
     * SM4 CTR算法。
     */
    DRM_ALG_CENC_SM4_CTR = 0x5
} DrmCencAlgorithm;

/**
 * @brief 枚举类型，表示cencInfo中keyId/iv/subsample信息是否设置。
 * @since 12
 * @version 1.0
 */
typedef enum DrmCencInfoMode {
    /** keyId/iv/subsample信息已设置。 */
    DRM_CENC_INFO_KEY_IV_SUBSAMPLES_SET = 0x0,
    /** keyId/iv/subsample信息未设置。 */
    DRM_CENC_INFO_KEY_IV_SUBSAMPLES_NOT_SET = 0x1
} DrmCencInfoMode;

/**
 * @brief Subsample结构类型定义。
 * @since 12
 * @version 1.0
 */
typedef struct DrmSubsample {
    /** 头部清流数据的长度。 */
    uint32_t clearHeaderLen;
    /** 加密数据的长度。 */
    uint32_t payLoadLen;
} DrmSubsample;

/**
 * @brief 创建用于设置cencInfo的OH_AVCencInfo实例。
 *
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @return 返回新创建的OH_AVCencInfo对象。如果返回nullptr，则表示创建对象失败。\n
 * 可能失败的原因：应用程序地址空间已满，或者对象中的数据初始化失败。
 * @since 12
 * @version 1.0
 */
OH_AVCencInfo *OH_AVCencInfo_Create();

/**
 * @brief 销毁OH_AVCencInfo实例并释放内部资源。\n
 *
 * 同一个实例只能销毁一次。在再次创建实例之前，不应使用该实例。
 * 建议在实例销毁成功后立即将实例指针设置为nullptr。
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param cencInfo 指向OH_AVCencInfo实例的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：cencInfo为空。
 * @since 12
 * @version 1.0
*/
OH_AVErrCode OH_AVCencInfo_Destroy(OH_AVCencInfo *cencInfo);

/**
 * @brief 设置cencInfo加密算法。
 *
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param cencInfo 指向OH_AVCencInfo实例的指针。
 * @param algo 加密算法模式。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：cencInfo为空。
 * @since 12
 * @version 1.0
 */
OH_AVErrCode OH_AVCencInfo_SetAlgorithm(OH_AVCencInfo *cencInfo, enum DrmCencAlgorithm algo);

/**
 * @brief 设置cencInfo的keyId和iv。
 *
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param cencInfo 指向OH_AVCencInfo实例的指针。
 * @param keyId Key标识。
 * @param keyIdLen Key标识长度。
 * @param iv 初始化向量。
 * @param ivLen 初始化向量长度。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：cencInfo为空、keyId为空、keyIdLen != DRM_KEY_ID_SIZE、iv是空、
 * ivLen != DRM_KEY_IV_SIZE、keyId拷贝失败，或者iv拷贝失败。
 * @since 12
 * @version 1.0
 */
OH_AVErrCode OH_AVCencInfo_SetKeyIdAndIv(OH_AVCencInfo *cencInfo, uint8_t *keyId,
    uint32_t keyIdLen, uint8_t *iv, uint32_t ivLen);

/**
 * @brief 设置cencInfo的subsamples信息。
 *
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param cencInfo 指向OH_AVCencInfo实例的指针。
 * @param encryptedBlockCount 加密块的数量。
 * @param skippedBlockCount 不加密块的数量。
 * @param firstEncryptedOffset 第一个加密有效负载的偏移量。
 * @param subsampleCount Subsample数量。
 * @param subsamples Subsample内容集。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：cencInfo为空、subsampleCount > DRM_KEY_MAX_SUB_SAMPLE_NUM，或者subsamples为空。
 * @since 12
 * @version 1.0
 */
OH_AVErrCode OH_AVCencInfo_SetSubsampleInfo(OH_AVCencInfo *cencInfo, uint32_t encryptedBlockCount,
    uint32_t skippedBlockCount, uint32_t firstEncryptedOffset, uint32_t subsampleCount, DrmSubsample *subsamples);

/**
 * @brief 设置cencInfo的模式。
 *
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param cencInfo 指向OH_AVCencInfo实例的指针。
 * @param mode cencInfo模式，指示是否设置了keyId/iv/subsample。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：cencInfo为空。
 * @since 12
 * @version 1.0
 */
OH_AVErrCode OH_AVCencInfo_SetMode(OH_AVCencInfo *cencInfo, enum DrmCencInfoMode mode);

/**
 * @brief 将cencInfo设置到AVBuffer。
 *
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @param cencInfo 指向OH_AVCencInfo实例的指针。
 * @param buffer 携带数据的帧buffer。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：cencInfo为空、buffer为空、buffer->buffer_为空，或者buffer->buffer_->meta_为空。
 * @since 12
 * @version 1.0
 */
OH_AVErrCode OH_AVCencInfo_SetAVBuffer(OH_AVCencInfo *cencInfo, OH_AVBuffer *buffer);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVCENCINFO_H

 /** @} */
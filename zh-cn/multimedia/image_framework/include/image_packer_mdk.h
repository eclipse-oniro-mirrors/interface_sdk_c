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
 * @addtogroup Image
 * @{
 *
 * @brief Provides native APIs for encoding image data
 *
 * The encoding image data module part of image module.
 * It used to pack pixel data information into a target like data or file.
 *
 * @since 11
 * @version 4.1
 */

/**
 * @file image_packer_mdk.h
 *
 * @brief 声明用于将图像编码到缓冲区或文件的api。可用于将像素数据编码到目标缓冲区或文件中。
 *
 * @library libimage_packer_ndk.z.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.Image.ImagePacker
 * @since 11
 * @version 4.1
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PACKER_MDK_H_
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PACKER_MDK_H_
#include "napi/native_api.h"
#include "image_mdk_common.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ImagePacker_Native_;

/**
 * @brief 为编码器方法定义native层编码器对象。
 *
 * @since 11
 * @version 4.1
 */
typedef struct ImagePacker_Native_ ImagePacker_Native;

/**
 * @brief 定义图像编码选项信息。
 *
 * @since 11
 * @version 4.1
 */
struct ImagePacker_Opts_ {
    /**
     * 编码格式。
     */
    const char* format;
    /**
     * 编码质量。
     */
    int quality;
};

/**
 * @brief 定义图像编码选项信息。
 *
 * @since 11
 * @version 4.1
 */
typedef struct ImagePacker_Opts_ ImagePacker_Opts;

/**
 * @brief 获取JavaScript native层ImagePacker对象。
 *
 * @param env 表明JNI环境的指针。
 * @param res 表明JavaScript native层ImagePacker对象的指针。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：执行成功。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 * @since 11
 * @version 4.1
 */
int32_t OH_ImagePacker_Create(napi_env env, napi_value *res);

/**
 * @brief 从输入JavaScript native层ImagePacker对象中，转换成ImagePacker_Native值。
 *
 * @param env 表明JNI环境的指针。
 * @param packer 表明JavaScript native层ImagePacker对象。
 * @return 如果操作成功则返回ImagePacker_Native指针，否则返回空指针。
 * @see {@link OH_ImagePacker_Release}
 * @since 11
 * @version 4.1
 */
ImagePacker_Native* OH_ImagePacker_InitNative(napi_env env, napi_value packer);

/**
 * @brief 通过一个给定的选项ImagePacker_Opts结构体，将输入JavaScript native层PixelMap对象或者ImageSource对象编码并输出到指定的缓存区outData中。
 *
 * @param native 表明指向native层ImagePacker的指针。
 * @param source 表明待编码JavaScript native层PixelMap对象或者ImageSource对象。
 * @param opts 表明位图编码的选项。
 * @param outData 输出的指定缓存区。
 * @param size 输出的指定缓存区大小。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：执行成功。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>ERR_IMAGE_DATA_ABNORMAL：输出缓冲区异常。
 *     <br>ERR_IMAGE_MISMATCHED_FORMAT：格式不匹配。
 *     <br>ERR_IMAGE_MALLOC_ABNORMAL：malloc内部缓冲区错误。
 *     <br>ERR_IMAGE_DECODE_ABNORMAL：init编解码器内部错误。
 *     <br>ERR_IMAGE_ENCODE_FAILED：编码器在编码过程中出现错误。
 * @see {@link OH_ImagePacker_PackToFile}
 * @since 11
 * @version 4.1
 */
int32_t OH_ImagePacker_PackToData(ImagePacker_Native* native, napi_value source,
    ImagePacker_Opts* opts, uint8_t* outData, size_t* size);

/**
 * @brief 通过一个给定的选项ImagePacker_Opts结构体，将输入JavaScript native层PixelMap对象或者ImageSource对象编码并输出到指定的文件中。
 *
 * @param native 表明指向native层ImagePacker的指针。
 * @param source 表明待编码JavaScript native层PixelMap对象或者ImageSource对象。
 * @param opts 表明位图编码的选项。
 * @param fd 输出的指定文件描述符。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：执行成功。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>ERR_IMAGE_DATA_ABNORMAL：输出缓冲区异常。
 *     <br>ERR_IMAGE_MISMATCHED_FORMAT：格式不匹配。
 *     <br>ERR_IMAGE_MALLOC_ABNORMAL：malloc内部缓冲区错误。
 *     <br>ERR_IMAGE_DECODE_ABNORMAL：init编解码器内部错误。
 *     <br>ERR_IMAGE_ENCODE_FAILED：编码器在编码过程中出现错误。
 * @see {@link OH_ImagePacker_PackToData}
 * @since 11
 * @version 4.1
 */
int32_t OH_ImagePacker_PackToFile(ImagePacker_Native* native, napi_value source,
    ImagePacker_Opts* opts, int fd);


/**
 * @brief 释放native层编码器对象{@link ImagePacker_Native}。
 * <br>此API不用于释放JavaScript原生API ImagePacker对象，它用于释放native层对象ImagePacker_Native。
 * <br>通过调用{@link OH_ImagePacker_InitNative}解析。
 *
 * @param native 表明native层ImagePacker_Native值的指针。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：执行成功。
 * @see {@link OH_ImagePacker_InitNative}
 * @since 11
 * @version 4.1
 */
int32_t OH_ImagePacker_Release(ImagePacker_Native* native);
#ifdef __cplusplus
};
#endif
/** @} */
#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_PACKER_MDK_H_

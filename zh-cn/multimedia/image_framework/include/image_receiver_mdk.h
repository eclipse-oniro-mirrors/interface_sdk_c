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
 * @brief Provides APIs for obtaining image data from the native layer.
 *
 * @since 10
 * @version 2.0
 */

/**
 * @file image_receiver_mdk.h
 *
 * @brief 声明从native层获取图片数据的方法。
 *
 * @library libimage_receiver_ndk.z.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.Image.ImageReceiver
 * @since 10
 * @version 2.0
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_RECEIVER_MDK_H_
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_RECEIVER_MDK_H_
#include "napi/native_api.h"
#include "image_mdk_common.h"
#include "image_mdk.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于定义ImageReceiverNative数据类型名称。
 *
 * @since 10
 * @version 2.0
 */
struct ImageReceiverNative_;

/**
 * @brief 用于定义ImageReceiverNative数据类型名称。
 *
 * @since 10
 * @version 2.0
 */
typedef struct ImageReceiverNative_ ImageReceiverNative;

/**
 * @brief 定义native层图片的回调方法。
 *
 * @since 10
 * @version 2.0
 */
typedef void (*OH_Image_Receiver_On_Callback)(void);

/**
 * @brief 定义ImageReceiver的相关信息。
 *
 * @since 10
 * @version 2.0
 */
struct OhosImageReceiverInfo {
    /* Default width of the image received by the consumer, in pixels. */
    int32_t width;
    /* Default height of the image received by the consumer, in pixels. */
    int32_t height;
    /* Image format {@link OHOS_IMAGE_FORMAT_JPEG} created by using the receiver. */
    int32_t format;
    /* Maximum number of images that can be cached. */
    int32_t capicity;
};

/**
 * @brief 创建应用层ImageReceiver对象。
 *
 * @param env napi的环境指针。
 * @param info ImageReceiver数据设置项。
 * @param res 应用层的ImageReceiver对象的指针。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_CREATE_SURFACE_FAILED：创建surface失败。
 *     <br>IMAGE_RESULT_SURFACE_GRALLOC_BUFFER_FAILED：surface分配内存失败。
 *     <br>IMAGE_RESULT_GET_SURFACE_FAILED：获取surface失败。
 *     <br>IMAGE_RESULT_MEDIA_RTSP_SURFACE_UNSUPPORT：媒体rtsp surface不支持。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图像类型不支持。
 *     <br>IMAGE_RESULT_MEDIA_DATA_UNSUPPORT：媒体类型不支持。
 * @see OhosImageReceiverInfo
 * @since 10
 * @version 2.0
 */
int32_t OH_Image_Receiver_CreateImageReceiver(napi_env env, struct OhosImageReceiverInfo info, napi_value* res);

/**
 * @brief 通过应用层ImageReceiver对象初始化native层{@link ImageReceiverNative}对象。
 *
 * @param env napi的环境指针。
 * @param source napi的ImageReceiver对象。
 * @return 操作成功则返回ImageReceiverNative指针；如果操作失败，则返回nullptr。
 * @see ImageReceiverNative, OH_Image_Receiver_Release
 * @since 10
 * @version 2.0
 */
ImageReceiverNative* OH_Image_Receiver_InitImageReceiverNative(napi_env env, napi_value source);

/**
 * @brief 通过{@link ImageReceiverNative}获取receiver的id。
 *
 * @param native native层的ImageReceiverNative指针。
 * @param id 指向字符缓冲区的指针，用于获取字符串的id。
 * @param len id所对应的字符缓冲区的大小。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：从surface获取参数失败。
 *     <br>IMAGE_RESULT_GET_SURFACE_FAILED：获取surface失败。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图像类型不支持。
 *     <br>IMAGE_RESULT_MEDIA_DATA_UNSUPPORT：媒体类型不支持。
 * @see ImageReceiverNative
 * @since 10
 * @version 2.0
 */
int32_t OH_Image_Receiver_GetReceivingSurfaceId(const ImageReceiverNative* native, char* id, size_t len);

/**
 * @brief 通过{@link ImageReceiverNative}获取最新的一张图片。
 * <br>注意，此接口需要在{@link OH_Image_Receiver_On_Callback}回调后调用，才能正常的接收到数据。并且使用此接口返回Image对象创建的{@link ImageNative}使用完毕后需要调用
 * {@link OH_Image_Release}方法释放，释放后才可以继续接收新的数据。
 *
 * @param native native层的ImageReceiverNative指针。
 * @param image 获取到的应用层的Image指针对象。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：从surface获取参数失败。
 *     <br>IMAGE_RESULT_CREATE_SURFACE_FAILED：创建surface失败。
 *     <br>IMAGE_RESULT_SURFACE_GRALLOC_BUFFER_FAILED：surface分配内存失败。
 *     <br>IMAGE_RESULT_GET_SURFACE_FAILED：获取surface失败。
 *     <br>IMAGE_RESULT_MEDIA_RTSP_SURFACE_UNSUPPORT：媒体rtsp surface不支持。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图像类型不支持。
 *     <br>IMAGE_RESULT_MEDIA_DATA_UNSUPPORT：媒体类型不支持。
 * @see ImageReceiverNative
 * @since 10
 * @version 2.0
 */
int32_t OH_Image_Receiver_ReadLatestImage(const ImageReceiverNative* native, napi_value* image);

/**
 * @brief 通过{@link ImageReceiverNative}获取下一张图片。
 * <br>注意，此接口需要在{@link OH_Image_Receiver_On_Callback}回调后调用，才能正常的接收到数据。并且使用此接口返回Image对象创建的{@link ImageNative}使用完毕后需要调用
 * {@link OH_Image_Release}方法释放，释放后才可以继续接收新的数据。
 *
 * @param native native层的ImageReceiverNative指针。
 * @param image 读取到的应用层的Image指针对象。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：从surface获取参数失败。
 *     <br>IMAGE_RESULT_CREATE_SURFACE_FAILED：创建surface失败。
 *     <br>IMAGE_RESULT_SURFACE_GRALLOC_BUFFER_FAILED：surface分配内存失败。
 *     <br>IMAGE_RESULT_GET_SURFACE_FAILED：获取surface失败。
 *     <br>IMAGE_RESULT_MEDIA_RTSP_SURFACE_UNSUPPORT：媒体rtsp surface不支持。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图像类型不支持。
 *     <br>IMAGE_RESULT_MEDIA_DATA_UNSUPPORT：媒体类型不支持。
 * @see ImageReceiverNative
 * @since 10
 * @version 2.0
 */
int32_t OH_Image_Receiver_ReadNextImage(const ImageReceiverNative* native, napi_value* image);

/**
 * @brief 注册一个{@link OH_Image_Receiver_On_Callback}回调事件。每当接收新图片，该回调事件就会响应。
 *
 * @param native native层的ImageReceiverNative指针。
 * @param callback {@link OH_Image_Receiver_On_Callback}事件的回调函数。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：从surface获取参数失败。
 *     <br>IMAGE_RESULT_GET_SURFACE_FAILED：获取surface失败。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图像类型不支持。
 *     <br>IMAGE_RESULT_MEDIA_DATA_UNSUPPORT：媒体类型不支持。
 * @see ImageReceiverNative
 * @since 10
 * @version 2.0
 */
int32_t OH_Image_Receiver_On(const ImageReceiverNative* native, OH_Image_Receiver_On_Callback callback);

/**
 * @brief 通过{@link ImageReceiverNative}获取ImageReceiver的大小。
 *
 * @param native native层的ImageReceiverNative指针。
 * @param size 作为结果的OhosImageSize指针。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图像类型不支持。
 * @see ImageReceiverNative, OH_Image_Receiver_On_Callback
 * @since 10
 * @version 2.0
 */
int32_t OH_Image_Receiver_GetSize(const ImageReceiverNative* native, struct OhosImageSize* size);

/**
 * @brief 通过{@link ImageReceiverNative}获取ImageReceiver的容量。
 *
 * @param native native层的ImageReceiverNative指针。
 * @param capacity 作为结果的指向容量的指针。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_JNI_ENV_ABNORMAL：JNI环境异常。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图像类型不支持。
 * @see ImageReceiverNative, OhosImageSize
 * @since 10
 * @version 2.0
 */
int32_t OH_Image_Receiver_GetCapacity(const ImageReceiverNative* native, int32_t* capacity);

/**
 * @brief Obtains the format of the image receiver through an {@link ImageReceiverNative} object.
 *
 * @param native Indicates the pointer to an {@link ImageReceiverNative} object at the native layer.
 * @param format Indicates the pointer to the format obtained.
 * @return Returns {@link IRNdkErrCode} IMAGE_RESULT_SUCCESS - if the operation is successful.
 * returns {@link IRNdkErrCode} IMAGE_RESULT_BAD_PARAMETER - if bad parameter.
 * returns {@link IRNdkErrCode} IMAGE_RESULT_JNI_ENV_ABNORMAL - if Abnormal JNI environment.
 * returns {@link IRNdkErrCode} IMAGE_RESULT_INVALID_PARAMETER - if invalid parameter.
 * returns {@link IRNdkErrCode} IMAGE_RESULT_DATA_UNSUPPORT - if image type unsupported.
 * @see ImageReceiverNative

 * @since 10
 * @version 2.0
 */
int32_t OH_Image_Receiver_GetFormat(const ImageReceiverNative* native, int32_t* format);

/**
 * @brief 释放native层{@link ImageReceiverNative}对象。
 * <br>注意，此方法不能释放应用层ImageReceiver对象。
 *
 * @param native native层的ImageReceiverNative指针。
 * @return {@link IRNdkErrCode}：
 *     <br>IMAGE_RESULT_SUCCESS：操作成功。
 *     <br>IMAGE_RESULT_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_RESULT_INVALID_PARAMETER：参数无效。
 *     <br>IMAGE_RESULT_DATA_UNSUPPORT：图像类型不支持。
 * @see ImageReceiverNative
 * @since 10
 * @version 2.0
 */
int32_t OH_Image_Receiver_Release(ImageReceiverNative* native);
#ifdef __cplusplus
};
#endif
/** @} */

#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_RECEIVER_MDK_H_

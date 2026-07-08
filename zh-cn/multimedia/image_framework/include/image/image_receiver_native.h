/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup Image_NativeModule
 * @{
 *
 * @brief Provides APIs for obtaining image data.
 *
 * @since 12
 */

/**
 * @file image_receiver_native.h
 *
 * @brief 声明从native层获取图片数据的方法。
 * 
 * @library libimage_receiver.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.Image.ImageReceiver
 * @since 12
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_RECEIVER_NATIVE_H
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_RECEIVER_NATIVE_H

#include "image_native.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
/**
 * @brief OH_ImageReceiverNative是native层封装的图片接收器结构体，OH_ImageReceiverNative结构体不可直接操作，而是采用函数调用方式创建、释放结构体以及操作具体字段。<br>
 * 创建OH_ImageReceiverNative对象使用{@link OH_ImageReceiverNative_Create}函数。<br>释放OH_ImageReceiverNative对象使用
 * {@link OH_ImageReceiverNative_Release}函数。<br>OH_ImageReceiverNative结构体内容和操作方式如下：
 * 
 * @since 12
 */
struct OH_ImageReceiverNative;

/**
 * @brief OH_ImageReceiverNative是native层封装的图片接收器结构体，OH_ImageReceiverNative结构体不可直接操作，而是采用函数调用方式创建、释放结构体以及操作具体字段。<br>
 * 创建OH_ImageReceiverNative对象使用{@link OH_ImageReceiverNative_Create}函数。<br>释放OH_ImageReceiverNative对象使用
 * {@link OH_ImageReceiverNative_Release}函数。<br>OH_ImageReceiverNative结构体内容和操作方式如下：
 * 
 * @since 12
 */
typedef struct OH_ImageReceiverNative OH_ImageReceiverNative;

/**
 * @brief 用于定义OH_ImageReceiverOptions数据类型名称。<br>OH_ImageReceiverOptions是native层封装的图片接收器选项设置器结构体，
 * 用于创建OH_ImageReceiverNative时传入设置参数。OH_ImageReceiverOptions结构体不可直接操作，而是采用函数调用方式创建、释放结构体以及操作具体字段。<br>
 * 创建OH_ImageReceiverOptions对象使用{@link OH_ImageReceiverOptions_Create}函数。<br>释放OH_ImageReceiverOptions对象使用
 * {@link OH_ImageReceiverOptions_Release}函数。<br>OH_ImageReceiverOptions结构体内容和操作方式如下：
 * 
 * @since 12
 */
struct OH_ImageReceiverOptions;

/**
 * @brief 用于定义OH_ImageReceiverOptions数据类型名称。<br>OH_ImageReceiverOptions是native层封装的图片接收器选项设置器结构体，
 * 用于创建OH_ImageReceiverNative时传入设置参数。OH_ImageReceiverOptions结构体不可直接操作，而是采用函数调用方式创建、释放结构体以及操作具体字段。<br>
 * 创建OH_ImageReceiverOptions对象使用{@link OH_ImageReceiverOptions_Create}函数。<br>释放OH_ImageReceiverOptions对象使用
 * {@link OH_ImageReceiverOptions_Release}函数。<br>OH_ImageReceiverOptions结构体内容和操作方式如下：
 * 
 * @since 12
 */
typedef struct OH_ImageReceiverOptions OH_ImageReceiverOptions;

/**
 * @brief 定义native层图片的回调方法。
 * 
 * @since 12
 */
typedef void (*OH_ImageReceiver_OnCallback)(OH_ImageReceiverNative *receiver);

/**
 * @brief ImageArrive事件的回调方法。
 * 
 * @since 20
 */
typedef void (*OH_ImageReceiver_ImageArriveCallback)(OH_ImageReceiverNative *receiver, void *userData);


/**
 * @brief Creates an OH_ImageReceiverOptions object at the application layer.
 * 
 * @param options Double pointer to the OH_ImageReceiverOptions object created.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 *     <br>{@link Image_ErrorCode} IMAGE_ALLOC_FAILED - if alloc failed.

 * @since 12
 */
Image_ErrorCode OH_ImageReceiverOptions_Create(OH_ImageReceiverOptions **options);

/**
 * @brief 获取OH_ImageReceiverOptions对象的Image_Size。
 * 
 * @param options 表示OH_ImageReceiverOptions对象的指针。
 * @param size 表示作为获取结果的Image_Size对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverOptions_GetSize(OH_ImageReceiverOptions* options, Image_Size* size);

/**
 * @brief 设置OH_ImageReceiverOptions对象的Image_Size。
 * 
 * @param options 表示OH_ImageReceiverOptions对象的指针。
 * @param size 表示Image_Size对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverOptions_SetSize(OH_ImageReceiverOptions* options, Image_Size size);

/**
 * @brief 获取OH_ImageReceiverOptions对象的图片缓存容量。
 * 
 * @param options 表示OH_ImageReceiverOptions对象的指针。
 * @param capacity 表示作为获取结果的图片缓存容量对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverOptions_GetCapacity(OH_ImageReceiverOptions* options, int32_t* capacity);

/**
 * @brief 设置OH_ImageReceiverOptions对象的图片缓存容量。
 * 
 * @param options 表示OH_ImageReceiverOptions对象的指针。
 * @param capacity 表示图片缓存容量值。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverOptions_SetCapacity(OH_ImageReceiverOptions* options, int32_t capacity);

/**
 * @brief 释放OH_ImageReceiverOptions对象。
 * 
 * @param options 表示OH_ImageReceiverOptions对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @see OH_ImageReceiverOptions
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverOptions_Release(OH_ImageReceiverOptions* options);

/**
 * @brief 创建应用层OH_ImageReceiverNative对象。
 * 
 * @param options 表示OH_ImageReceiverOptions对象的指针。
 * @param receiver 表示作为获取结果的OH_ImageReceiverNative对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_ALLOC_FAILED：申请内存失败。
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_Create(OH_ImageReceiverOptions* options, OH_ImageReceiverNative** receiver);

/**
 * @brief 通过OH_ImageReceiverNative获取SurfaceId。
 * 
 * @param receiver 表示OH_ImageReceiverNative对象的指针。
 * @param surfaceId 表示作为获取结果的id对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNKNOWN_ERROR：未知原因错误。
 * @see OH_ImageReceiverNative
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_GetReceivingSurfaceId(OH_ImageReceiverNative* receiver, uint64_t* surfaceId);

/**
 * @brief 通过OH_ImageReceiverNative获取最新的一张图片。
 * 
 * @param receiver 表示OH_ImageReceiverNative对象的指针。
 * @param image 获取到的应用层的OH_ImageNative指针对象。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNKNOWN_ERROR：未知原因错误。
 *     <br>IMAGE_ALLOC_FAILED：申请内存失败。
 * @see OH_ImageReceiverNative, OH_ImageNative
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_ReadLatestImage(OH_ImageReceiverNative* receiver, OH_ImageNative** image);

/**
 * @brief 通过OH_ImageReceiverNative获取下一张图片。
 * 
 * @param receiver 表示OH_ImageReceiverNative对象的指针。
 * @param image 获取到的应用层的OH_ImageNative指针对象。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_UNKNOWN_ERROR：未知原因错误。
 *     <br>IMAGE_ALLOC_FAILED：申请内存失败。
 * @see OH_ImageReceiverNative, OH_ImageNative
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_ReadNextImage(OH_ImageReceiverNative* receiver, OH_ImageNative** image);

/**
 * @brief 注册一个{@link OH_ImageReceiver_OnCallback}回调事件。
 * <br>每当接收到新的图片，该回调事件就会响应。
 * 
 * @param receiver 表示OH_ImageReceiverNative对象的指针。
 * @param callback 表示OH_ImageReceiver_OnCallback事件的回调函数。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @see OH_ImageReceiverNative, OH_ImageReceiver_OnCallback
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_On(OH_ImageReceiverNative* receiver, OH_ImageReceiver_OnCallback callback);

/**
 * @brief 关闭{@link OH_ImageReceiver_OnCallback}回调事件。
 * <br>关闭被{@link OH_ImageReceiverNative_On}开启的回调事件。
 * 
 * @param receiver 表示OH_ImageReceiverNative对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @see OH_ImageReceiverNative, OH_ImageReceiverNative_On
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_Off(OH_ImageReceiverNative* receiver);

/**
 * @brief 通过OH_ImageReceiverNative获取ImageReceiver的大小。
 *
 * @param receiver 表示OH_ImageReceiverNative对象的指针。
 * @param size 表示作为获取结果的Image_Size对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @see OH_ImageReceiverNative, Image_Size
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_GetSize(OH_ImageReceiverNative* receiver, Image_Size* size);

/**
 * @brief 通过OH_ImageReceiverNative获取ImageReceiver的容量。
 * 
 * @param receiver 表示OH_ImageReceiverNative对象的指针。
 * @param capacity 表示作为获取结果的图片缓存容量对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @see OH_ImageReceiverNative
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_GetCapacity(OH_ImageReceiverNative* receiver, int32_t* capacity);

/**
 * @brief 释放Native OH_ImageReceiverNative对象。
 * 
 * @param receiver 表示OH_ImageReceiverNative对象的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @see OH_ImageReceiverNative
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_Release(OH_ImageReceiverNative* receiver);

/**
 * 注册{@link OH_ImageReceiver_ImageArriveCallback}回调。
 * @param receiver 处理回调的OH_ImageReceiverNative对象。
 * @param callback 要注册的OH_ImageReceiver_ImageArriveCallback回调方法。
 * @param userData 用户自定义数据指针。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_RECEIVER_INVALID_PARAMETER：参数错误。
 * @since 20
 */

Image_ErrorCode OH_ImageReceiverNative_OnImageArrive(OH_ImageReceiverNative* receiver, OH_ImageReceiver_ImageArriveCallback callback, void *userData);

/** 
 * 注销{@link OH_ImageReceiver_ImageArriveCallback}回调。 
 * @param receiver 处理回调的OH_ImageReceiverNative对象。
 * @param callback 要注册的OH_ImageReceiver_ImageArriveCallback回调。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_RECEIVER_INVALID_PARAMETER：参数错误，receiver或callback未注册。
 * @since 20
 */
Image_ErrorCode OH_ImageReceiverNative_OffImageArrive(OH_ImageReceiverNative* receiver, OH_ImageReceiver_ImageArriveCallback callback);

#ifdef __cplusplus
};
#endif
/** @} */

#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_RECEIVER_NATIVE_H
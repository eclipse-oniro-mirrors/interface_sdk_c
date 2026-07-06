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
 * @brief The file declares the APIs used to obtain image data from the native layer.
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
 * @brief The OH_ImageReceiverNative struct describes the image receiver, which is encapsulated at the native layer.
 * The struct cannot be directly operated. Instead, functions must be called to create and release the struct and
 * operate the fields in the struct.
 * 
 * @since 12
 */
struct OH_ImageReceiverNative;

/**
 * @brief The OH_ImageReceiverNative struct describes the image receiver, which is encapsulated at the native layer.
 * The struct cannot be directly operated. Instead, functions must be called to create and release the struct and
 * operate the fields in the struct.
 * 
 * @since 12
 */
typedef struct OH_ImageReceiverNative OH_ImageReceiverNative;

/**
 * @brief The struct describes the data type name of the image receiver options.
 * 
 * @since 12
 */
struct OH_ImageReceiverOptions;

/**
 * @brief The struct describes the data type name of the image receiver options.
 * 
 * @since 12
 */
typedef struct OH_ImageReceiverOptions OH_ImageReceiverOptions;

/**
 * @brief Defines the callbacks for the image receiver at the native layer.
 * 
 * @since 12
 */
typedef void (*OH_ImageReceiver_OnCallback)(OH_ImageReceiverNative *receiver);

/**
 * @brief Defines the callback for the ImageArrive event.
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
 * @brief Obtains the image size of an OH_ImageReceiverOptions object.
 * 
 * @param options Pointer to an OH_ImageReceiverOptions object.
 * @param size Pointer to the Image_Size object obtained.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverOptions_GetSize(OH_ImageReceiverOptions* options, Image_Size* size);

/**
 * @brief Sets the image size of an OH_ImageReceiverOptions object.
 * 
 * @param options Pointer to an OH_ImageReceiverOptions object.
 * @param size Image_Size object.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverOptions_SetSize(OH_ImageReceiverOptions* options, Image_Size size);

/**
 * @brief Obtains the image cache capacity of an OH_ImageReceiverOptions object.
 * 
 * @param options Pointer to an OH_ImageReceiverOptions object.
 * @param capacity Pointer to the capacity obtained.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverOptions_GetCapacity(OH_ImageReceiverOptions* options, int32_t* capacity);

/**
 * @brief Sets the image cache capacity of an OH_ImageReceiverOptions object.
 * 
 * @param options Pointer to an OH_ImageReceiverOptions object.
 * @param capacity Capacity.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverOptions_SetCapacity(OH_ImageReceiverOptions* options, int32_t capacity);

/**
 * @brief Releases an OH_ImageReceiverOptions object.
 * 
 * @param options Pointer to an OH_ImageReceiverOptions object.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 * @see OH_ImageReceiverOptions
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverOptions_Release(OH_ImageReceiverOptions* options);

/**
 * @brief Creates an OH_ImageReceiverNative object at the application layer.
 * 
 * @param options Pointer to an OH_ImageReceiverOptions object.
 * @param receiver Double pointer to the OH_ImageReceiverNative object obtained.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 *     <br>{@link Image_ErrorCode} IMAGE_ALLOC_FAILED - if alloc failed.
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_Create(OH_ImageReceiverOptions* options, OH_ImageReceiverNative** receiver);

/**
 * @brief Obtains the surface ID through an OH_ImageReceiverNative object.
 * 
 * @param receiver Pointer to an OH_ImageReceiverNative object.
 * @param surfaceId Pointer to the surface ID obtained.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 *     <br>{@link Image_ErrorCode} IMAGE_UNKNOWN_ERROR - inner unknown error.
 * @see OH_ImageReceiverNative
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_GetReceivingSurfaceId(OH_ImageReceiverNative* receiver, uint64_t* surfaceId);

/**
 * @brief Obtains the latest image through an OH_ImageReceiverNative object.
 * 
 * @param receiver Pointer to an OH_ImageReceiverNative object.
 * @param image Double pointer to the image obtained, which is an OH_ImageNative object at the application layer.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 *     <br>{@link Image_ErrorCode} IMAGE_UNKNOWN_ERROR - inner unknown error.
 *     <br>{@link Image_ErrorCode} IMAGE_ALLOC_FAILED - if alloc failed.
 * @see OH_ImageReceiverNative, OH_ImageNative
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_ReadLatestImage(OH_ImageReceiverNative* receiver, OH_ImageNative** image);

/**
 * @brief Obtains the next image through an OH_ImageReceiverNative object.
 * 
 * @param receiver Pointer to an OH_ImageReceiverNative object.
 * @param image Double pointer to the image obtained, which is an OH_ImageNative object at the application layer.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 *     <br>{@link Image_ErrorCode} IMAGE_UNKNOWN_ERROR - inner unknown error.
 *     <br>{@link Image_ErrorCode} IMAGE_ALLOC_FAILED - if alloc failed.
 * @see OH_ImageReceiverNative, OH_ImageNative
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_ReadNextImage(OH_ImageReceiverNative* receiver, OH_ImageNative** image);

/**
 * @brief Registers the {@link OH_ImageReceiver_OnCallback} callback.
 * 
 * @param receiver Pointer to an OH_ImageReceiverNative object.
 * @param callback Callback to register.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 * @see OH_ImageReceiverNative, OH_ImageReceiver_OnCallback
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_On(OH_ImageReceiverNative* receiver, OH_ImageReceiver_OnCallback callback);

/**
 * @brief Unregisters the {@link OH_ImageReceiver_OnCallback} callback.
 * 
 * @param receiver Pointer to an OH_ImageReceiverNative object.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 * @see OH_ImageReceiverNative, OH_ImageReceiverNative_On
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_Off(OH_ImageReceiverNative* receiver);

/**
 * @brief Obtains the size of an **ImageReceiver** using **OH_ImageReceiverNative**.
 * 
 * @param receiver Pointer to an OH_ImageReceiverNative object.
 * @param size Pointer to the Image_Size object obtained.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 * @see OH_ImageReceiverNative, Image_Size
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_GetSize(OH_ImageReceiverNative* receiver, Image_Size* size);

/**
 * @brief Obtains the capacity of an **OH_ImageReceiverNative**.
 * 
 * @param receiver Pointer to an OH_ImageReceiverNative object.
 * @param capacity Pointer to the capacity obtained.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 * @see OH_ImageReceiverNative
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_GetCapacity(OH_ImageReceiverNative* receiver, int32_t* capacity);

/**
 * @brief Releases an OH_ImageReceiverNative object.
 * 
 * @param receiver Pointer to an OH_ImageReceiverNative object.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_BAD_PARAMETER - if bad parameter.
 * @see OH_ImageReceiverNative
 * @since 12
 */
Image_ErrorCode OH_ImageReceiverNative_Release(OH_ImageReceiverNative* receiver);

/**
 * Registers an {@link OH_ImageReceiver_ImageArriveCallback} callback.
 *
 * @param receiver Pointer to an OH_ImageReceiverNative object that processes the callback.
 * @param callback Callback to register.
 * @param userData Pointer to user data.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS is returned if the operation is successful.
 *     <br>{@link Image_ErrorCode} IMAGE_RECEIVER_INVALID_PARAMETER is returned if receiver or callback is null.
 * @since 20
 */

Image_ErrorCode OH_ImageReceiverNative_OnImageArrive(OH_ImageReceiverNative* receiver, OH_ImageReceiver_ImageArriveCallback callback, void *userData);

/** 
 * Unregisters an {@link OH_ImageReceiver_ImageArriveCallback} callback.
 * 
 * @param receiver Pointer to an OH_ImageReceiverNative object that processes the callback.
 * @param callback Callback to unregister.
 * @return {@link Image_ErrorCode} IMAGE_SUCCESS - Operation succeeded.
 *     <br>{@link Image_ErrorCode} IMAGE_RECEIVER_INVALID_PARAMETER - <b>receiver</b> is empty or <b>callback</b> is not registered.
 * @since 20
 */
Image_ErrorCode OH_ImageReceiverNative_OffImageArrive(OH_ImageReceiverNative* receiver, OH_ImageReceiver_ImageArriveCallback callback);

#ifdef __cplusplus
};
#endif
/** @} */

#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_RECEIVER_NATIVE_H
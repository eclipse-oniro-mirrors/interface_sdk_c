/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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
 * @addtogroup Drawing
 * @{
 *
 * @brief Provides functions such as 2D graphics rendering, text drawing, and image display.
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file drawing_bitmap.h
 *
 * @brief This file declares the functions related to the bitmap in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_BITMAP_H
#define C_INCLUDE_DRAWING_BITMAP_H

#include "drawing_types.h"
#include "drawing_error_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief This struct describes the pixel format of a bitmap, including the color type and alpha type.
 *
 * @since 8
 * @version 1.0
 */
typedef struct {
    /**
     * Storage format of bitmap pixels.
     */
    OH_Drawing_ColorFormat colorFormat;
    /**
     * Alpha format of bitmap pixels.
     */
    OH_Drawing_AlphaFormat alphaFormat;
} OH_Drawing_BitmapFormat;

/**
 * @brief Creates an **OH_Drawing_Bitmap** object.
 *
 * @return Returns the pointer to the **OH_Drawing_Bitmap** object created.
 * @since 8
 * @version 1.0
 */
OH_Drawing_Bitmap* OH_Drawing_BitmapCreate(void);

/**
 * @brief Destroys an **OH_Drawing_Bitmap** object and reclaims the memory occupied by the object.
 *
 * @param bitmap Pointer to an **OH_Drawing_Bitmap** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_BitmapDestroy(OH_Drawing_Bitmap* bitmap);

/**
 * @brief Creates an **OH_Drawing_Bitmap** object, with the address of the memory for storing the bitmap pixels set to
 * the memory address that you applied for.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **imageInfo** or **pixels** is NULL or **rowBytes** is **0**, **OH_DRAWING_ERROR_INVALID_PARAMETER** is
 * returned.
 *
 * @param imageInfo Pointer to an {@link OH_Drawing_Image_Info} object.
 * @param pixels Pointer to the start address of the memory for storing the bitmap pixels. You need to apply for the
 * memory and ensure its validity.
 * @param rowBytes Number of bytes in each row of pixels. The value is invalid if it is less than or equal to 0.
 * @return Returns a pointer to the {@link OH_Drawing_Bitmap} object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Bitmap* OH_Drawing_BitmapCreateFromPixels(OH_Drawing_Image_Info* imageInfo, void* pixels, uint32_t rowBytes);

/**
 * @brief Initializes the width and height of a bitmap and sets the pixel format for the bitmap.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **bitmap** or **bitmapFormat** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param bitmap Pointer to an **OH_Drawing_Bitmap** object.
 * @param width Width of the bitmap to be initialized.
 * @param height Height of the bitmap to be initialized.
 * @param bitmapFormat Pointer to the pixel format of the bitmap to be initialized, including the pixel color type and
 * alpha type.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_BitmapBuild(OH_Drawing_Bitmap* bitmap,
    const uint32_t width, const uint32_t height, const OH_Drawing_BitmapFormat* bitmapFormat);

/**
 * @brief Obtains the width of a bitmap.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **bitmap** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param bitmap Pointer to an **OH_Drawing_Bitmap** object.
 * @return Returns the width.
 * @since 8
 * @version 1.0
 */
uint32_t OH_Drawing_BitmapGetWidth(OH_Drawing_Bitmap* bitmap);

/**
 * @brief Obtains the height of a bitmap.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **bitmap** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param bitmap Pointer to an **OH_Drawing_Bitmap** object.
 * @return Returns the height.
 * @since 8
 * @version 1.0
 */
uint32_t OH_Drawing_BitmapGetHeight(OH_Drawing_Bitmap* bitmap);

/**
 * @brief Obtains the pixel format of a bitmap.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **bitmap** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param bitmap Pointer to an **OH_Drawing_Bitmap** object.
 * @return Returns the pixel format. For details about the supported formats, see {@link OH_Drawing_ColorFormat}.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ColorFormat OH_Drawing_BitmapGetColorFormat(OH_Drawing_Bitmap* bitmap);

/**
 * @brief Obtains the alpha component of a bitmap.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **bitmap** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param bitmap Pointer to an **OH_Drawing_Bitmap** object.
 * @return Returns the alpha component. For details about the supported formats, see {@link OH_Drawing_AlphaFormat}.
 * @since 12
 * @version 1.0
 */
OH_Drawing_AlphaFormat OH_Drawing_BitmapGetAlphaFormat(OH_Drawing_Bitmap* bitmap);

/**
 * @brief Obtains the pixel address of a bitmap. You can use this address to obtain the pixel data of the bitmap.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **bitmap** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param bitmap Pointer to an **OH_Drawing_Bitmap** object.
 * @return Returns the pixel address.
 * @since 8
 * @version 1.0
 */
void* OH_Drawing_BitmapGetPixels(OH_Drawing_Bitmap* bitmap);

/**
 * @brief Obtains the image information of a bitmap.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **bitmap** or **imageInfo** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param bitmap Pointer to the {@link OH_Drawing_Bitmap} object.
 * @param imageInfo Pointer to an {@link OH_Drawing_Image_Info} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_BitmapGetImageInfo(OH_Drawing_Bitmap* bitmap, OH_Drawing_Image_Info* imageInfo);

/**
 * @brief Reads pixels of a rectangle in a bitmap to the specified buffer.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If any of **bitmap**, **dstInfo**, and **dstPixels** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param bitmap Pointer to the {@link OH_Drawing_Bitmap} object.
 * @param dstInfo Pointer to an {@link OH_Drawing_Image_Info} object.
 * @param dstPixels Pointer to the buffer for storing the pixels read.
 * @param dstRowBytes Number of bytes in each row of the pixel data read. The value must be greater than or equal to
 * the minimum number of bytes in each row in the **OH_Drawing_Image_Info** object.
 * @param srcX Start X coordinate of the pixel data to read from the bitmap. The value must be less than the width of
 * the bitmap.
 * @param srcY Start Y coordinate of the pixel data to read from the bitmap. The value must be less than the height of
 * the bitmap.
 * @return Returns **true** if the pixels are read; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_BitmapReadPixels(OH_Drawing_Bitmap* bitmap, const OH_Drawing_Image_Info* dstInfo,
    void* dstPixels, size_t dstRowBytes, int32_t srcX, int32_t srcY);

/**
 * @brief Gets the row bytes of the bitmap.
 *
 * @param bitmap Indicates the pointer to an <b>OH_Drawing_Bitmap</b> object.
 * @param bytes Indicates the row bytes of the bitmap.
 * @return Returns the error code.
 *         Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 *         Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if bitmap or bytes is nullptr.
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_BitmapGetRowBytes(OH_Drawing_Bitmap* bitmap, uint32_t* bytes);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
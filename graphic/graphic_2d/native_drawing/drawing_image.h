/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
 * @since 12
 * @version 1.0
 */
/**
 * @file drawing_image.h
 *
 * @brief This file declares the functions related to the image in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_IMAGE_H
#define C_INCLUDE_DRAWING_IMAGE_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an **OH_Drawing_Image** object that describes an array of two-dimensional pixels to draw.
 *
 * @return Returns a pointer to the {@link OH_Drawing_Image} object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Image* OH_Drawing_ImageCreate(void);

/**
 * @brief Destroys an **OH_Drawing_Image** object and reclaims the memory occupied by the object.
 *
 * @param image Pointer to the {@link OH_Drawing_Image} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ImageDestroy(OH_Drawing_Image* image);

/**
 * @brief Builds an image from a bitmap by sharing or copying bitmap pixels. If the bitmap is marked as immutable, the
 * pixel memory is shared, not copied.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **image** or **bitmap** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param image Pointer to the {@link OH_Drawing_Image} object.
 * @param bitmap Pointer to the {@link OH_Drawing_Bitmap} object.
 * @return Returns **true** if the image is built; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_ImageBuildFromBitmap(OH_Drawing_Image* image, OH_Drawing_Bitmap* bitmap);

/**
 * @brief Obtains the image width, that is, the number of pixels in each line.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **image** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param image Pointer to the {@link OH_Drawing_Image} object.
 * @return Returns the width.
 * @since 12
 * @version 1.0
 */
int32_t OH_Drawing_ImageGetWidth(OH_Drawing_Image* image);

/**
 * @brief Obtains the image height, that is, the number of pixel lines.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **image** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param image Pointer to the {@link OH_Drawing_Image} object.
 * @return Returns the height.
 * @since 12
 * @version 1.0
 */
int32_t OH_Drawing_ImageGetHeight(OH_Drawing_Image* image);

/**
 * @brief Obtains the image information. After this function is called, the passed-in image information object is
 * filled.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **image** or **imageInfo** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param image Pointer to the {@link OH_Drawing_Image} object.
 * @param imageInfo Pointer to an  {@link OH_Drawing_Image_Info}  object, which can be created by calling
 * {@link OH_Drawing_Image_Info}
 * .
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ImageGetImageInfo(OH_Drawing_Image* image, OH_Drawing_Image_Info* imageInfo);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
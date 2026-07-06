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
 * @since 11
 * @version 1.0
 */
/**
 * @file drawing_text_blob.h
 *
 * @brief This file declares the functions related to the text blob in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_TEXT_BLOB_H
#define C_INCLUDE_DRAWING_TEXT_BLOB_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an **OH_Drawing_TextBlobBuilder** object.
 *
 * @return Returns the pointer to the **OH_Drawing_TextBlobBuilder** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_TextBlobBuilder* OH_Drawing_TextBlobBuilderCreate(void);

/**
 * @brief Creates an **OH_Drawing_TextBlob** object from the text.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **text** or **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **textEncoding** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param text Pointer to the text.
 * @param byteLength Length of the text, in bytes.
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param textEncoding Text encoding type {@link OH_Drawing_TextEncoding}.
 * @return Returns a pointer to the created {@link OH_Drawing_TextBlob} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextBlob* OH_Drawing_TextBlobCreateFromText(const void* text, size_t byteLength,
    const OH_Drawing_Font* font, OH_Drawing_TextEncoding textEncoding);

/**
 * @brief Creates an **OH_Drawing_TextBlob** object from the text. The coordinates of each character in the **
 * OH_Drawing_TextBlob** object are determined by the coordinate information in the **OH_Drawing_Point2D** array.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If any of **text**, **point2D**, and **font** is NULL or **byteLength** is **0**, **
 * OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **textEncoding** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param text Pointer to the text.
 * @param byteLength Length of the text, in bytes.
 * @param point2D Pointer to the start address of the  {@link OH_Drawing_Point2D}
 *  array. The number of entries in the array is determined by  {@link OH_Drawing_FontCountText}
 * .
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param textEncoding Text encoding type {@link OH_Drawing_TextEncoding}.
 * @return Returns a pointer to the created {@link OH_Drawing_TextBlob} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextBlob* OH_Drawing_TextBlobCreateFromPosText(const void* text, size_t byteLength,
    OH_Drawing_Point2D* point2D, const OH_Drawing_Font* font, OH_Drawing_TextEncoding textEncoding);

/**
 * @brief Creates an **OH_Drawing_TextBlob** object from a string.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **str** or **font** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **textEncoding** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param str Pointer to a string.
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param textEncoding Text encoding type {@link OH_Drawing_TextEncoding}.
 * @return Returns a pointer to the created {@link OH_Drawing_TextBlob} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_TextBlob* OH_Drawing_TextBlobCreateFromString(const char* str,
    const OH_Drawing_Font* font, OH_Drawing_TextEncoding textEncoding);

/**
 * @brief Obtains the bounds of an **OH_Drawing_TextBlob** object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **textBlob** or **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param textBlob Pointer to the {@link OH_Drawing_TextBlob} object.
 * @param rect Pointer to the {@link OH_Drawing_Rect} object. You can call {@link OH_Drawing_Rect} to create a
 * rectangle object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_TextBlobGetBounds(OH_Drawing_TextBlob* textBlob, OH_Drawing_Rect* rect);

/**
 * @brief Obtains the unique identifier of a text blob. The identifier is a non-zero value.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **textBlob** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param textBlob Pointer to the {@link OH_Drawing_TextBlob} object.
 * @return Returns the unique identifier of the text blob.
 * @since 12
 * @version 1.0
 */
uint32_t OH_Drawing_TextBlobUniqueID(const OH_Drawing_TextBlob* textBlob);

/**
 * @brief This struct describes a run, which provides storage for glyphs and positions.
 *
 * @since 11
 * @version 1.0
 */
typedef struct {
    /**
     * Storage for glyph indexes in the run.
     */
    uint16_t* glyphs;
    /**
     * Storage for glyph positions in the run.
     */
    float* pos;
    /**
     * Storage for UTF-8 encoded text units in the run.
     */
    char* utf8text;
    /**
     * Storage for glyph clusters (index of the UTF-8 encoded text unit) in the run.
     */
    uint32_t* clusters;
} OH_Drawing_RunBuffer;

/**
 * @brief Allocates a run to store glyphs and positions. The pointer returned does not need to be managed by the caller.
 * It can no longer be used after {@link OH_Drawing_TextBlobBuilderMake} is called.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **textBlobBuilder** or **font** is NULL or **count** is less than or equal to 0, **
 * OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param textBlobBuilder Pointer to an **OH_Drawing_TextBlobBuilder** object.
 * @param font Pointer to an **OH_Drawing_Font** object.
 * @param count Number of text blobs.
 * @param rect Rectangle of the text blob. The value NULL means that no rectangle is set.
 * @return Returns the pointer to the **OH_Drawing_RunBuffer** object created.
 * @since 11
 * @version 1.0
 */
const OH_Drawing_RunBuffer* OH_Drawing_TextBlobBuilderAllocRunPos(OH_Drawing_TextBlobBuilder* textBlobBuilder,
    const OH_Drawing_Font* font, int32_t count, const OH_Drawing_Rect* rect);

/**
 * @brief Makes an **OH_Drawing_TextBlob** object from an **OH_Drawing_TextBlobBuilder**.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **textBlobBuilder** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param textBlobBuilder Pointer to an **OH_Drawing_TextBlobBuilder** object.
 * @return Returns the pointer to the **OH_Drawing_TextBlob** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_TextBlob* OH_Drawing_TextBlobBuilderMake(OH_Drawing_TextBlobBuilder* textBlobBuilder);

/**
 * @brief Destroys an **OH_Drawing_TextBlob** object and reclaims the memory occupied by the object.
 *
 * @param textBlob Pointer to an **OH_Drawing_TextBlob** object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_TextBlobDestroy(OH_Drawing_TextBlob* textBlob);

/**
 * @brief Destroys an **OH_Drawing_TextBlobBuilder** object and reclaims the memory occupied by the object.
 *
 * @param textBlobBuilder Pointer to an **OH_Drawing_TextBlobBuilder** object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_TextBlobBuilderDestroy(OH_Drawing_TextBlobBuilder* textBlobBuilder);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
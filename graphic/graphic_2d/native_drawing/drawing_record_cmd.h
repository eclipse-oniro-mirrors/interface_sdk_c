/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @since 13
 * @version 1.0
 */
/**
 * @file drawing_record_cmd.h
 *
 * @brief This file declares the functions related to a recording command object.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 13
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_RECORD_CMD_H
#define C_INCLUDE_DRAWING_RECORD_CMD_H

#include "drawing_types.h"
#include "drawing_error_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an **OH_Drawing_RecordCmdUtils** object.
 *
 * @return Returns the pointer to the **OH_Drawing_RecordCmdUtils** object created.
 * @since 13
 * @version 1.0
 */
OH_Drawing_RecordCmdUtils* OH_Drawing_RecordCmdUtilsCreate(void);

/**
 * @brief Destroys an **OH_Drawing_RecordCmdUtils** object and reclaims the memory occupied by the object.
 *
 * @param recordCmdUtils Pointer to an {@link OH_Drawing_RecordCmdUtils} object.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **recordCmdUtils** is NULL.
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RecordCmdUtilsDestroy(OH_Drawing_RecordCmdUtils* recordCmdUtils);

/**
 * @brief Starts recording. This API must be used together with {@link OH_Drawing_RecordCmdUtilsFinishRecording}.
 * The **OH_Drawing_RecordCmdUtils** object generates a canvas object of the recording type and calls the interface of
 * the drawing object to record all drawing commands.
 *
 * @param recordCmdUtils Pointer to an {@link OH_Drawing_RecordCmdUtils} object.
 * @param width Width of the canvas.
 * @param height Height of the canvas.
 * @param canvas Double pointer to the {@link OH_Drawing_Canvas} object. You do not need to release this pointer.
 * This object does not support nested calling of {@link OH_Drawing_CanvasDrawRecordCmd}.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **recordCmdUtils** or **canvas** is NULL.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **width** or **height** is less than 0.
 * **OH_DRAWING_ERROR_ALLOCATION_FAILED** if the system memory is insufficient.
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RecordCmdUtilsBeginRecording(OH_Drawing_RecordCmdUtils* recordCmdUtils,
    int32_t width, int32_t height, OH_Drawing_Canvas** canvas);

/**
 * @brief Stops video recording. This function must be called after {@link OH_Drawing_RecordCmdUtilsBeginRecording}.
 * The **OH_Drawing_RecordCmdUtils** object ends recording and stores the drawing commands recorded by the canvas
 * object of the recording type into the generated {@link OH_Drawing_RecordCmdUtilsBeginRecording} object.
 *
 * @param recordCmdUtils Pointer to an {@link OH_Drawing_RecordCmdUtils} object.
 * @param recordCmd Double pointer to the  {@link OH_Drawing_RecordCmd}  object. You need to call
 * {@link OH_Drawing_CanvasDrawRecordCmd}
 * to draw the object, and call {@link OH_Drawing_RecordCmdDestroy} to release it.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **recordCmdUtils** or **recordCmd** is NULL.
 * **OH_DRAWING_ERROR_ALLOCATION_FAILED** if the system memory is insufficient.
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RecordCmdUtilsFinishRecording(OH_Drawing_RecordCmdUtils* recordCmdUtils,
    OH_Drawing_RecordCmd** recordCmd);

/**
 * @brief Destroys an **OH_Drawing_RecordCmd** object and reclaims the memory occupied by the object.
 *
 * @param recordCmd Pointer to an {@link OH_Drawing_RecordCmd} object.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **recordCmd** is NULL.
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RecordCmdDestroy(OH_Drawing_RecordCmd* recordCmd);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
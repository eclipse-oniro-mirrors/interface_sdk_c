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
 * @brief 创建一个录制指令工具对象。
 *
 * @return 返回用于录制指令的工具对象。
 * @since 13
 * @version 1.0
 */
OH_Drawing_RecordCmdUtils* OH_Drawing_RecordCmdUtilsCreate(void);

/**
 * @brief 销毁一个录制指令工具对象，并回收该对象占用的内存。
 *
 * @param recordCmdUtils 指向录制指令工具对象{@link OH_Drawing_RecordCmdUtils}的指针。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数recordCmdUtils为空。
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RecordCmdUtilsDestroy(OH_Drawing_RecordCmdUtils* recordCmdUtils);

/**
 * @brief 开始录制。此接口需要与{@link OH_Drawing_RecordCmdUtilsFinishRecording}接口成对使用。
 * 指令录制工具生成录制类型的画布对象，可调用drawing的绘制接口，记录接下来所有的绘制指令。
 *
 * @param recordCmdUtils 指向录制工具对象{@link OH_Drawing_RecordCmdUtils}的指针。
 * @param width 画布的宽度。
 * @param height 画布的高度。
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的二级指针，作为出参，开发者无需释放。
 * 该画布对象不支持嵌套调用{@link OH_Drawing_CanvasDrawRecordCmd}接口。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS, 表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER, 表示参数recordCmdUtils或者canvas为空。
 * 当width和height小于等于0的时，也会返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 * 返回OH_DRAWING_ERROR_ALLOCATION_FAILED，表示系统内存不足。
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RecordCmdUtilsBeginRecording(OH_Drawing_RecordCmdUtils* recordCmdUtils,
    int32_t width, int32_t height, OH_Drawing_Canvas** canvas);

/**
 * @brief 结束录制。在调用此接口前，需要先调用{@link OH_Drawing_RecordCmdUtilsBeginRecording}接口。
 * 指令录制工具结束录制指令，将录制类型画布对象记录的绘制指令存入生成的录制指令对象。
 *
 * @param recordCmdUtils 指向录制指令工具对象{@link OH_Drawing_RecordCmdUtils}的指针。
 * @param recordCmd 指向录制指令对象 {@link OH_Drawing_RecordCmd} 的二级指针，作为出参，开发者调用 {@link OH_Drawing_CanvasDrawRecordCmd}
 * 接口绘制该对象。需要调用 {@link OH_Drawing_RecordCmdDestroy}
 * 接口释放。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数recordCmdUtils或者recordCmd为空。
 * 返回OH_DRAWING_ERROR_ALLOCATION_FAILED，表示系统内存不足。
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RecordCmdUtilsFinishRecording(OH_Drawing_RecordCmdUtils* recordCmdUtils,
    OH_Drawing_RecordCmd** recordCmd);

/**
 * @brief 销毁录制指令对象，并回收该对象占用的内存。
 *
 * @param recordCmd 指向对象{@link OH_Drawing_RecordCmd}的指针。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数recordCmd为空。
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RecordCmdDestroy(OH_Drawing_RecordCmd* recordCmd);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
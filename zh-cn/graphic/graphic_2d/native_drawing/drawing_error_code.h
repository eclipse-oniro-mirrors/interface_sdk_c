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
 * @since 8
 * @version 1.0
 */
/**
 * @file drawing_error_code.h
 *
 * @brief This file declares the functions related to the error code in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_ERROR_CODE_H
#define C_INCLUDE_DRAWING_ERROR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 枚举本模块可能产生的错误码。
 *
 * @since 12
 */
typedef enum {
    /**
     * 操作成功完成。
     *
     * @since 12
     */
    OH_DRAWING_SUCCESS = 0,
    /**
     * 权限校验失败。
     *
     * @since 12
     */
    OH_DRAWING_ERROR_NO_PERMISSION = 201,
    /**
     * 无效的输入参数，如参数中传入了NULL。
     *
     * @since 12
     */
    OH_DRAWING_ERROR_INVALID_PARAMETER = 401,
    /**
     * 输入参数不在有效的范围内。
     *
     * @since 12
     */
    OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE = 26200001,
    /**
     * 内存分配失败。
     *
     * @since 13
     */
    OH_DRAWING_ERROR_ALLOCATION_FAILED = 26200002,
    /**
     * 输入属性id无匹配的函数。
     *
     * @since 21
     */
    OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH = 26200003,
    /**
     * 输入参数不正确，例如入参的指针为空。
     *
     * @since 22
     */
    OH_DRAWING_ERROR_INCORRECT_PARAMETER = 26200004,
    /**
     * 文件未找到，指定的文件不存在或路径不正确。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_FILE_NOT_FOUND = 26200005,
    /**
     * 打开文件失败，权限不足或I/O问题造成。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_OPEN_FILE_FAILED = 26200006,
    /**
     * 文件定位失败。系统无法重新定位文件读取指针。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_FILE_SEEK_FAILED = 26200007,
    /**
     * 获取文件大小失败，系统无法获取文件大小信息。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_GET_FILE_SIZE_FAILED = 26200008,
    /**
     * 读取文件失败，文件无法完整读取或包含不可读数据。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_READ_FILE_FAILED = 26200009,
    /**
     * 文件为空，指定的字体文件为空，不包含有效数据。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_EMPTY_FILE = 26200010,
    /**
     * 文件损坏，文件内容无效或损坏，无法解析。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_FILE_CORRUPTED = 26200011,
} OH_Drawing_ErrorCode;

/**
 * @brief 获取本模块的错误码。
 *
 * @return 获取本模块的最近一次的错误码。当函数成功运行后，本函数返回的错误码不会被修改。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_ErrorCodeGet();

/**
 * @brief 将本模块的错误码重置为OH_DRAWING_SUCCESS。
 * 通过{@link OH_Drawing_ErrorCodeGet}获取的本模块错误码会在不以错误码为返回值的接口执行失败时被置为
 * 对应的错误编号，但是不会在执行成功后被重置为OH_DRAWING_SUCCESS。调用本接口可将错误码重置为
 * OH_DRAWING_SUCCESS，避免多个接口间互相干扰，方便开发者调试。
 *
 * @since 18
 * @version 1.0
 */
void OH_Drawing_ErrorCodeReset(void);
#ifdef __cplusplus
}
#endif
/** @} */
#endif
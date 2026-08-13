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
 * @brief Drawing模块提供包括2D图形渲染、文字绘制和图片显示等功能函数。
 * <br>本模块采用屏幕物理像素单位px。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file drawing_error_code.h
 *
 * @brief 声明与绘图模块中的错误码相关的函数。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
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
     * @brief 操作成功完成。
     *
     * @since 12
     */
    OH_DRAWING_SUCCESS = 0,
    /**
     * @brief 权限校验失败。请检查是否已申请所需权限。
     *
     * @since 12
     */
    OH_DRAWING_ERROR_NO_PERMISSION = 201,
    /**
     * @brief 无效的输入参数，如参数中传入了NULL。请检查参数类型、取值范围或参数是否为空。
     *
     * @since 12
     */
    OH_DRAWING_ERROR_INVALID_PARAMETER = 401,
    /**
     * @brief 输入参数不在有效的范围内。请检查参数值是否在接口文档规定的有效范围内。
     *
     * @since 12
     */
    OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE = 26200001,
    /**
     * @brief 内存分配失败。
     *
     * @since 13
     */
    OH_DRAWING_ERROR_ALLOCATION_FAILED = 26200002,
    /**
     * @brief 输入属性id无匹配的函数。请检查属性id是否正确，确保使用有效的属性id。
     *
     * @since 21
     */
    OH_DRAWING_ERROR_ATTRIBUTE_ID_MISMATCH = 26200003,
    /**
     * @brief 输入参数不正确，例如入参的指针为空。请检查传入的参数是否正确，确保指针参数有效且不为空。
     *
     * @since 22
     */
    OH_DRAWING_ERROR_INCORRECT_PARAMETER = 26200004,
    /**
     * @brief 文件未找到，指定的文件不存在或路径不正确。请检查文件路径是否正确，确保文件存在且路径格式有效。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_FILE_NOT_FOUND = 26200005,
    /**
     * @brief 打开文件失败，权限不足或I/O问题造成。请检查文件权限设置是否正确，或稍后重试。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_OPEN_FILE_FAILED = 26200006,
    /**
     * @brief 文件定位失败。系统无法重新定位文件读取指针。请检查文件是否被其他进程占用，或重新打开文件后重试。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_FILE_SEEK_FAILED = 26200007,
    /**
     * @brief 获取文件大小失败，系统无法获取文件大小信息。请检查文件是否存在且可访问，确保文件未被损坏。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_GET_FILE_SIZE_FAILED = 26200008,
    /**
     * @brief 读取文件失败，文件无法完整读取或包含不可读数据。请检查文件是否完整且未被损坏，确保文件格式正确。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_READ_FILE_FAILED = 26200009,
    /**
     * @brief 文件为空，指定的字体文件为空，不包含有效数据。请检查文件内容，确保使用包含有效数据的字体文件。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_EMPTY_FILE = 26200010,
    /**
     * @brief 文件损坏，文件内容无效或损坏，无法解析。请检查文件是否完整，尝试重新获取或替换有效的文件。
     *
     * @since 23
     */
    OH_DRAWING_ERROR_FILE_CORRUPTED = 26200011,
} OH_Drawing_ErrorCode;

/**
 * @brief 获取本模块最近一次的错误码。
 * <br>本模块的错误码会在不以错误码为返回值的接口执行失败时被置为对应的错误编号，
 * 在执行成功后不会被重置为OH_DRAWING_SUCCESS。可通过{@link OH_Drawing_ErrorCodeReset}重置错误码。
 *
 * @return 返回本模块最近一次的错误码。当函数成功运行后，本函数返回的错误码不会被修改。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_ErrorCodeGet();

/**
 * @brief 将本模块的错误码重置为OH_DRAWING_SUCCESS。
 * <br>通过{@link OH_Drawing_ErrorCodeGet}获取的本模块错误码会在不以错误码为返回值的接口执行失败时被置为对应的错误编号，
 * 但是不会在执行成功后被重置为OH_DRAWING_SUCCESS。
 * <br>调用本接口可将错误码重置为OH_DRAWING_SUCCESS，避免多个接口间互相干扰，方便开发者调试。
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
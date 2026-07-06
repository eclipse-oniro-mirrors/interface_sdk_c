/*
* Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup InputMethod
 * @{
 *
 * @brief InputMethod模块提供方法来使用输入法和开发输入法。
 *
 * @since 12
 */

/**
 * @file inputmethod_cursor_info_capi.h
 *
 * @brief 提供光标信息对象的创建、销毁与读写方法。
 *
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_CURSOR_INFO_CAPI_H
#define OHOS_INPUTMETHOD_CURSOR_INFO_CAPI_H
#include "inputmethod_types_capi.h"
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
/**
 * @brief InputMethod_CursorInfo是光标信息的不透明类型（opaque type），用于描述文本输入时光标在物理屏幕上的位置和尺寸，包括光标的水平坐标（left）、垂直坐标（top）、宽度（width）和高度（
 * height）。
 *
 * @since 12
 */
typedef struct InputMethod_CursorInfo InputMethod_CursorInfo;

/**
 * @brief 创建一个新的{@link InputMethod_CursorInfo}实例，初始化光标的位置和尺寸信息。
 *
 * @param left 输入参数，光标靠左点相对于物理屏幕左侧的距离的绝对值。
 *     <br>**含义/功能：** 定义光标矩形区域的左边界在物理屏幕上的水平位置。
 *     <br>**使用场景：** 标识光标在屏幕上的水平起始位置，输入法据此定位光标区域。
 *     <br>**使用后效果：** 输入法根据left值确定光标的水平位置，实现键盘面板的光标跟随效果。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 必须为物理屏幕的绝对坐标值，不可使用相对坐标（如相对于父组件或窗口的坐标）。在多窗口场景下，仍需使用物理屏幕绝对坐标。
 *     <br>**生效机制：** 输入法服务将根据此值计算光标在屏幕上的实际位置。
 * @param top 输入参数，光标顶点与物理屏幕上侧距离的绝对值。
 *     <br>**含义/功能：** 定义光标矩形区域的顶边界在物理屏幕上的垂直位置。
 *     <br>**使用场景：** 标识光标在屏幕上的垂直起始位置。
 *     <br>**使用后效果：** 输入法根据top值确定光标的垂直位置，用于键盘避让计算和候选词定位。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 必须为物理屏幕的绝对坐标值，不可使用相对坐标。
 * @param width 输入参数，光标的宽度。
 *     <br>**含义/功能：** 定义光标矩形区域的宽度。
 *     <br>**使用场景：** 描述光标的水平尺寸，输入法据此判断光标区域大小。
 *     <br>**使用后效果：** 输入法根据光标宽度调整候选词区域的定位。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 通常设置为光标的实际显示宽度，单字符光标宽度通常为1-2px，选区光标宽度为选区文本的宽度。
 * @param height 输入参数，光标的高度。
 *     <br>**含义/功能：** 定义光标矩形区域的高度。
 *     <br>**使用场景：** 描述光标的垂直尺寸，输入法据此判断光标区域大小和计算避让区域。
 *     <br>**使用后效果：** 输入法根据光标高度调整键盘面板的避让区域。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 通常设置为光标的实际显示高度，与文本行高一致。
 * @return 返回指针类型。
 *     <br>**创建成功：** 返回一个指向新创建的InputMethod_CursorInfo实例的指针，该指针有效且可用于后续操作。
 *     <br>**创建失败：** 返回NULL，可能的失败原因包括应用程序的地址空间耗尽（内存不足）。
 *     <br>**NULL判断：** 调用者必须在使用返回值前检查是否为NULL，若为NULL则不可使用该指针，应排查内存状况或稍后重试。
 *     <br>**内存管理：** 返回的指针由Create函数内部分配内存，调用者需通过OH_CursorInfo_Destroy释放，不可使用free()或其他方式释放。
 * @since 12
 */
InputMethod_CursorInfo *OH_CursorInfo_Create(double left, double top, double width, double height);

/**
 * @brief 销毁一个{@link InputMethod_CursorInfo}实例，释放由Create函数分配的内存资源。
 *
 * @param cursorInfo 输入指针，表示指向即将被销毁的InputMethod_CursorInfo实例的指针。
 *     <br>**含义/功能：** 指定要销毁的CursorInfo实例，Destroy将释放该实例占用的内存资源。
 *     <br>**使用场景：** 在CursorInfo不再需要时调用，典型时机为NotifyCursorUpdate调用完成后或应用退出时。
 *     <br>**使用后效果：** cursorInfo指向的内存被释放，该指针不再有效。
 *     <br>**NULL指针处理：** 若cursorInfo为NULL，Destroy函数不做任何操作（安全处理），不会导致崩溃。但建议调用者避免传入NULL。
 *     <br>**内存释放责任：** 由调用者负责在适当时机调用Destroy释放内存。
 * @since 12
 */
void OH_CursorInfo_Destroy(InputMethod_CursorInfo *cursorInfo);

/**
 * @brief 设置光标信息内容，更新光标的位置和尺寸。适用于在已有的CursorInfo实例上修改光标信息，无需重新创建实例。
 *
 * @param cursorInfo 输入指针，表示指向InputMethod_CursorInfo实例的指针。
 *     <br>**含义/功能：** 指定要修改的CursorInfo实例。
 *     <br>**NULL指针处理：** 不可为NULL，传入NULL将返回IME_ERR_NULL_POINTER。
 *     <br>**前提条件：** 必须通过OH_CursorInfo_Create创建的有效实例。
 * @param left 输入参数，光标靠左点与物理屏幕左侧距离的绝对值。
 *     <br>**含义/功能：** 定义光标矩形区域的左边界在物理屏幕上的水平位置。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 必须为物理屏幕的绝对坐标值，不可使用相对坐标。
 *     <br>**生效机制：** 设置后覆盖原有的left值，下次GetRect将返回新值。
 * @param top 输入参数，光标顶点与物理屏幕上侧距离的绝对值。
 *     <br>**含义/功能：** 定义光标矩形区域的顶边界在物理屏幕上的垂直位置。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 必须为物理屏幕的绝对坐标值，不可使用相对坐标。
 * @param width 输入参数，光标的宽度。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 * @param height 输入参数，光标的高度。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。光标信息已更新。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。cursorInfo为NULL时返回，调用前需确保cursorInfo为有效指针。
 *     <br>**错误处理建议：** 若返回IME_ERR_NULL_POINTER，检查cursorInfo是否为有效指针。具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_CursorInfo_SetRect(
    InputMethod_CursorInfo *cursorInfo, double left, double top, double width, double height);

/**
 * @brief 获取光标信息内容，读取光标的位置和尺寸。
 *
 * @param cursorInfo 输入指针，表示指向InputMethod_CursorInfo实例的指针。
 *     <br>**含义/功能：** 指定要读取的CursorInfo实例。
 *     <br>**NULL指针处理：** 不可为NULL，传入NULL将返回IME_ERR_NULL_POINTER。
 *     <br>**前提条件：** 必须通过OH_CursorInfo_Create创建的有效实例。
 * @param left 输出指针，靠左点与物理屏幕左侧距离的绝对值。
 *     <br>**含义/功能：** 接收光标左边界的水平坐标值。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**输出值范围：** ≥0。
 *     <br>**NULL指针处理：** 不可为NULL，传入NULL将返回IME_ERR_NULL_POINTER。
 *     <br>**内存分配责任：** 由调用者分配double变量的内存，GetRect仅写入值，不分配内存。
 * @param top 输出指针，顶点与物理屏幕上侧距离的绝对值。
 *     <br>**含义/功能：** 接收光标顶边界的垂直坐标值。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**输出值范围：** ≥0。
 *     <br>**NULL指针处理：** 不可为NULL。
 *     <br>**内存分配责任：** 由调用者分配double变量的内存。
 * @param width 输出指针，光标的宽度。
 *     <br>**含义/功能：** 接收光标宽度值。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**输出值范围：** ≥0。
 *     <br>**NULL指针处理：** 不可为NULL。
 *     <br>**内存分配责任：** 由调用者分配double变量的内存。
 * @param height 输出指针，光标的高度。
 *     <br>**含义/功能：** 接收光标高度值。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**输出值范围：** ≥0。
 *     <br>**NULL指针处理：** 不可为NULL。
 *     <br>**内存分配责任：** 由调用者分配double变量的内存。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。left、top、width、height已被赋值为正确的光标信息。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。cursorInfo、left、top、width或height为NULL时返回，调用前需确保所有参数均为有效指针。
 *     <br>**错误处理建议：** 若返回IME_ERR_NULL_POINTER，检查所有参数是否为有效指针；若返回IME_ERR_OK，四个输出参数即为正确的光标信息值。具体错误码可以参考
 *     {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_CursorInfo_GetRect(
    InputMethod_CursorInfo *cursorInfo, double *left, double *top, double *width, double *height);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_CURSOR_INFO_CAPI_H
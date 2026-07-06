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
 * @brief InputMethod provides functions to use input methods and develop input methods.
 *
 * @since 12
 */

/**
 * @file inputmethod_text_avoid_info_capi.h
 *
 * @brief 提供输入框避让信息对象的创建、销毁与读写方法，用于在软键盘弹起时动态调整输入框的位置，避免遮挡输入内容。
 *
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_TEXT_AVOID_INFO_CAPI_H
#define OHOS_INPUTMETHOD_TEXT_AVOID_INFO_CAPI_H
#include "inputmethod_types_capi.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief 输入框避让信息结构体，描述编辑框在物理屏幕上的位置和高度信息。输入法框架根据TextAvoidInfo中的positionY和height计算避让区域，使编辑框在软键盘弹起时能够自动上移或调整布局，
 * 确保输入区域不被键盘遮挡，保证用户可见并可操作输入内容。
 *
 * @since 12
 */
typedef struct InputMethod_TextAvoidInfo InputMethod_TextAvoidInfo;

/**
 * @brief 创建一个新的{@link InputMethod_TextAvoidInfo}实例。该函数根据指定的Y坐标和高度创建一个避让信息对象，用于描述编辑框在物理屏幕上的位置和尺寸。
 *
 * @param positionY 表示输入框位置的Y坐标值，单位px。Y坐标值即输入框顶点与物理屏幕上侧距离的绝对值，单位px。取值范围≥0，建议使用物理屏幕的实际坐标值。若传入负值，创建仍会成功，但该值在实际避让计算中无意义。
 * @param height 表示输入框高度，单位px。取值范围≥0，建议使用编辑框的实际像素高度。若传入负值，创建仍会成功，但该值在实际避让计算中无意义。
 * @return 如果创建成功，返回一个指向新创建的{@link InputMethod_TextAvoidInfo}实例的指针。调用方必须负责该实例的生命周期管理，使用完毕后调用
 *     {@link OH_TextAvoidInfo_Destroy}销毁实例以释放内存。
 *     <br>如果创建失败，返回NULL。可能的失败原因：内存分配不足（应用地址空间满）。对NULL指针的后续操作（如Set/Get函数）将返回IME_ERR_NULL_POINTER。
 * @since 12
 */
InputMethod_TextAvoidInfo *OH_TextAvoidInfo_Create(double positionY, double height);
/**
 * @brief 销毁一个{@link InputMethod_TextAvoidInfo}实例，释放其占用的内存资源。
 *
 * @param info 表示指向即将被销毁的{@link InputMethod_TextAvoidInfo}实例的指针。若传入NULL，函数不执行任何操作，安全返回。建议销毁后将指针置为NULL以避免误用悬空指针。
 * @since 12
 */
void OH_TextAvoidInfo_Destroy(InputMethod_TextAvoidInfo *info);
/**
 * @brief 设置{@link InputMethod_TextAvoidInfo}中的Y坐标值。Y坐标值表示输入框顶点与物理屏幕上侧距离的绝对值。
 *
 * @param info 指向即将被设置值的{@link InputMethod_TextAvoidInfo}实例的指针。不允许传入NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @param positionY Y坐标值，即输入框顶点与物理屏幕上侧距离的绝对值，单位px。取值范围≥0，建议使用物理屏幕的实际坐标值。传入负值不会报错，但在实际避让计算中无意义。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，info参数为NULL。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_SetPositionY(InputMethod_TextAvoidInfo *info, double positionY);
/**
 * @brief 设置{@link InputMethod_TextAvoidInfo}中的高度值。高度值表示编辑框在屏幕上占据的垂直像素尺寸。
 *
 * @param info 指向即将被设置值的{@link InputMethod_TextAvoidInfo}实例的指针。不允许传入NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @param height 高度值，单位px。取值范围≥0，建议使用编辑框的实际像素高度。传入负值不会报错，但在实际避让计算中无意义。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，info参数为NULL。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_SetHeight(InputMethod_TextAvoidInfo *info, double height);
/**
 * @brief 从{@link InputMethod_TextAvoidInfo}获取Y坐标值。Y坐标值即输入框顶点与物理屏幕上侧距离的绝对值。
 *
 * @param info 指向即将被获取值的{@link InputMethod_TextAvoidInfo}实例的指针。不允许传入NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @param positionY 输出参数，用于接收Y坐标值，即输入框顶点与物理屏幕上侧距离的绝对值，单位px。此参数为输出指针，调用方需分配double类型变量的内存并将其地址传入。不允许传入NULL指针，
 *     否则返回IME_ERR_NULL_POINTER。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功，positionY指针指向的内存已被写入Y坐标值。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，info或positionY参数为NULL。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_GetPositionY(InputMethod_TextAvoidInfo *info, double *positionY);
/**
 * @brief 从{@link InputMethod_TextAvoidInfo}获取高度值。高度值表示编辑框在屏幕上占据的垂直像素尺寸。
 *
 * @param info 指向即将被获取值的{@link InputMethod_TextAvoidInfo}实例的指针。不允许传入NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @param height 输出参数，用于接收输入框高度，单位px。此参数为输出指针，调用方需分配double类型变量的内存并将其地址传入。不允许传入NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功，height指针指向的内存已被写入高度值。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，info或height参数为NULL。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_GetHeight(InputMethod_TextAvoidInfo *info, double *height);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_TEXT_AVOID_INFO_CAP_H
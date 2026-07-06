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
 * @file inputmethod_attach_options_capi.h
 *
 * @brief 提供输入法绑定选项对象的创建、销毁与读写方法，用于管理应用绑定输入法时的配置参数。
 *
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_ATTACH_OPTIONS_CAPI_H
#define OHOS_INPUTMETHOD_ATTACH_OPTIONS_CAPI_H
#include <stdbool.h>
#include "inputmethod_types_capi.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @brief InputMethod_AttachOptions是输入法绑定选项的不透明类型（opaque type），用于在应用绑定输入法服务时携带配置参数，控制绑定时的初始行为。
 *
 * @since 12
 */
typedef struct InputMethod_AttachOptions InputMethod_AttachOptions;

/**
 * @brief 创建一个{@link InputMethod_AttachOptions}实例，适用于仅需控制键盘显示状态的简单场景。如需同时指定触发输入法拉起的场景原因，建议使用
 * {@link OH_AttachOptions_CreateWithRequestKeyboardReason}。
 *
 * @param showKeyboard 输入参数，表示绑定时是否显示键盘。
 *     <br>**含义/功能：** 控制Attach绑定输入法时是否自动拉起键盘面板。
 *     <br>**使用场景：** true适用于输入框获得焦点后需要立即输入的场景（如文本编辑框）；false适用于先建立交互通道但暂不需要键盘的场景（如搜索框，等用户主动点击后再拉起键盘）。
 *     <br>**使用后效果：** showKeyboard=true时，绑定成功后键盘将自动弹出；showKeyboard=false时，绑定成功后键盘不弹出，
 *     需后续通过OH_InputMethodProxy_ShowKeyboard主动拉起。
 *     <br>**取值范围：** true或false。
 *     <br>**默认值：** 无默认值，调用者必须显式指定。
 *     <br>**取值原则：** 根据业务场景决定。需要立即输入的场景设为true；需要延迟拉起键盘的场景设为false，后续通过ShowKeyboard主动拉起。
 * @return 返回指针类型。
 *     <br>**创建成功：** 返回一个指向新创建的InputMethod_AttachOptions实例的指针，该指针有效且可用于后续操作。
 *     <br>**创建失败：** 返回NULL，可能的失败原因包括应用地址空间满（内存不足）。
 *     <br>**NULL判断：** 调用者必须在使用返回值前检查是否为NULL，若为NULL则不可使用该指针，应排查内存状况或稍后重试。
 *     <br>**内存管理：** 返回的指针由Create函数内部分配内存，调用者需通过OH_AttachOptions_Destroy释放，不可使用free()或其他方式释放。
 * @since 12
 */
InputMethod_AttachOptions *OH_AttachOptions_Create(bool showKeyboard);
/**
 * @brief 创建一个{@link InputMethod_AttachOptions}实例，同时指定键盘显示状态和请求键盘的原因。requestKeyboardReason参数用于标识触发输入法拉起的场景原因，
 * 帮助系统识别输入场景以提供更好的用户体验。
 *
 * @param showKeyboard 输入参数，表示绑定时是否显示键盘。含义/功能、使用场景、使用后效果、取值范围、取值原则与OH_AttachOptions_Create中的showKeyboard参数一致。
 * @param requestKeyboardReason 输入参数，表示请求键盘输入的原因。
 *     <br>**含义/功能：** 标识触发输入法拉起的场景原因，用于帮助系统识别输入场景并优化用户体验。
 *     <br>**使用场景：** 当应用需要告知系统为何拉起键盘时使用，例如区分用户通过鼠标点击、触摸事件还是应用主动调用API触发输入法。
 *     <br>**使用后效果：** 系统可根据此原因调整输入法行为（如选择合适的键盘布局或输入模式）。
 *     <br>**取值范围：** InputMethod_RequestKeyboardReason枚举值，包括：
 *     <br>- IME_REQUEST_REASON_NONE (0)：无特定原因。
 *     <br>- IME_REQUEST_REASON_MOUSE (1)：通过鼠标点击触发。
 *     <br>- IME_REQUEST_REASON_TOUCH (2)：通过触摸事件触发。
 *     <br>- IME_REQUEST_REASON_OTHER (20)：其他原因（应用主动调用API等）。
 *     <br>**取值原则：** 根据实际触发场景选择对应的枚举值。用户通过触摸输入框触发时使用IME_REQUEST_REASON_TOUCH；通过鼠标点击触发时使用IME_REQUEST_REASON_MOUSE；
 *     应用内部逻辑主动触发时使用IME_REQUEST_REASON_OTHER。
 *     <br>**规格限制：** 仅支持上述枚举值，传入其他值可能导致未定义行为。
 * @return 返回指针类型。
 *     <br>**创建成功：** 返回一个指向新创建的InputMethod_AttachOptions实例的指针。
 *     <br>**创建失败：** 返回NULL，可能的失败原因有应用地址空间满（内存不足）。
 *     <br>**NULL判断：** 调用者必须在使用返回值前检查是否为NULL，若为NULL则不可使用该指针。
 *     <br>**内存管理：** 返回的指针由Create函数内部分配内存，调用者需通过OH_AttachOptions_Destroy释放，不可使用free()或其他方式释放。
 * @since 15
 */
InputMethod_AttachOptions *OH_AttachOptions_CreateWithRequestKeyboardReason(
    bool showKeyboard, InputMethod_RequestKeyboardReason requestKeyboardReason);
/**
 * @brief 销毁一个{@link InputMethod_AttachOptions}实例，释放由OH_AttachOptions_Create函数分配的内存资源。
 * 该方法与OH_AttachOptions_Create和OH_AttachOptions_CreateWithRequestKeyboardReason配对使用。
 *
 * @param options 输入指针，表示即将被销毁的InputMethod_AttachOptions实例。
 *     <br>**含义/功能：** 指定要销毁的AttachOptions实例，OH_AttachOptions_Destroy将释放该实例占用的内存资源。
 *     <br>**使用场景：** 在AttachOptions不再需要时调用，典型时机为Attach绑定完成后。
 *     <br>**使用后效果：** options指向的内存被释放，该指针不再有效。
 *     <br>**NULL指针处理：** 若options为NULL，OH_AttachOptions_Destroy函数不做任何操作（安全处理），不会导致崩溃。但建议调用者避免传入NULL，
 *     因为这意味着OH_AttachOptions_Create失败未被正确处理。
 *     <br>**内存释放责任：** 由调用者负责在适当时机调用OH_AttachOptions_Destroy释放内存。
 * @since 12
 */
void OH_AttachOptions_Destroy(InputMethod_AttachOptions *options);
/**
 * @brief 从{@link InputMethod_AttachOptions}中获取是否显示键盘的值。
 *
 * @param options 输入指针，表示被读取值的InputMethod_AttachOptions实例。
 *     <br>**含义/功能：** 指定要从哪个AttachOptions实例中读取showKeyboard属性。
 *     <br>**NULL指针处理：** 不可为NULL，传入NULL将返回IME_ERR_NULL_POINTER。
 *     <br>**前提条件：** 必须通过OH_AttachOptions_Create函数创建的有效实例。
 * @param showKeyboard 输出指针，表示从InputMethod_AttachOptions中获取的是否显示键盘的值。
 *     <br>**含义/功能：** 用于接收showKeyboard属性的值。true表示绑定完成时需要显示键盘；false表示绑定完成时不需要显示键盘。
 *     <br>**使用场景：** 需要查询AttachOptions的键盘显示配置时使用，如Attach前确认配置、调试时验证配置等。
 *     <br>**NULL指针处理：** 不可为NULL，传入NULL将返回IME_ERR_NULL_POINTER。调用者需确保showKeyboard指向有效的bool变量。
 *     <br>**内存分配责任：** 由调用者分配bool变量的内存，IsShowKeyboard仅写入值，不分配内存。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。*showKeyboard已被赋值为正确的布尔值。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。表示options或showKeyboard为空指针，调用前需确保这两个参数已正确初始化且不为NULL。
 *     <br>**错误处理建议：** 若返回IME_ERR_NULL_POINTER，检查options和showKeyboard是否为有效指针；若返回IME_ERR_OK，*showKeyboard即为正确的配置值。
 *     具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_AttachOptions_IsShowKeyboard(InputMethod_AttachOptions *options, bool *showKeyboard);
/**
 * @brief 从{@link InputMethod_AttachOptions}中获取请求键盘输入的原因。
 *
 * @param options 输入指针，表示被读取值的InputMethod_AttachOptions实例。
 *     <br>**含义/功能：** 指定要从哪个AttachOptions实例中读取requestKeyboardReason属性。
 *     <br>**NULL指针处理：** 不可为NULL，传入NULL将返回IME_ERR_NULL_POINTER。
 *     <br>**前提条件：** 必须通过OH_AttachOptions_Create函数创建的有效实例。若实例通过OH_AttachOptions_Create（
 *     而非CreateWithRequestKeyboardReason）创建，读取的requestKeyboardReason默认值为IME_REQUEST_REASON_NONE。
 * @param requestKeyboardReason 输出指针，表示请求键盘输入的原因。
 *     <br>**含义/功能：** 输出参数，用于获取触发输入法拉起的场景原因枚举值。
 *     <br>**使用场景：** 需要查询AttachOptions的请求键盘原因配置时使用。
 *     <br>**取值范围：** 输出值为InputMethod_RequestKeyboardReason枚举：IME_REQUEST_REASON_NONE(0)、IME_REQUEST_REASON_MOUSE(1)、
 *     IME_REQUEST_REASON_TOUCH(2)、IME_REQUEST_REASON_OTHER(20)。
 *     <br>**NULL指针处理：** 不可为NULL，传入NULL将返回IME_ERR_NULL_POINTER。调用者需确保requestKeyboardReason指向有效的变量。
 *     <br>**内存分配责任：** 由调用者分配变量的内存，GetRequestKeyboardReason仅写入值，不分配内存。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。*requestKeyboardReason已被赋值为正确的枚举值。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。表示options或requestKeyboardReason为空指针，调用前需确保这两个参数已正确初始化且不为NULL。
 *     <br>**错误处理建议：** 若返回IME_ERR_NULL_POINTER，检查options和requestKeyboardReason是否为有效指针；若返回IME_ERR_OK，*
 *     requestKeyboardReason即为正确的配置值。具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 15
 */
InputMethod_ErrorCode OH_AttachOptions_GetRequestKeyboardReason(
    InputMethod_AttachOptions *options, int *requestKeyboardReason);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_ATTACH_OPTIONS_CAPI_H
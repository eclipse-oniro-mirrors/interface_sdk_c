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
 * @brief InputMethod模块提供C语言接口来使用输入法。"使用输入法"面向应用侧调用。
 *     <br>
 *     <br>功能定位：该模块为应用侧开发者提供自绘输入框与输入法服务交互的完整C API，支持应用绑定/解绑输入法服务、向输入法发送请求
 * 和通知、接收输入法的回调通知、配置输入框属性、管理光标和避让信息等核心功能。
 *     <br>
 *     <br>使用场景：适用于使用NDK开发自绘输入框的应用，需要与系统输入法服务进行交互的场景。典型流程为：应用创建TextEditorProxy
 * （文本编辑器代理）和AttachOptions（绑定配置选项），通过Controller绑定输入法服务，绑定成功后通过InputMethodProxy（输入法代
 * 理）与输入法交互，使用完毕后通过Controller解绑。
 *     <br>
 *     <br>使用后效果：绑定输入法后，应用可接收输入法的文本插入、删除、光标移动等回调通知，也可主动向输入法发送光标更新、选区变
 * 更、私有命令等请求。解绑后，所有交互通道关闭，相关资源释放。
 *     <br>
 *     <br>生命周期管理：本模块遵循严格的创建/销毁配对原则和绑定/解绑配对原则：
 *     <br>
 *     <br>- 绑定/解绑配对：OH_InputMethodController_Attach必须与OH_InputMethodController_Detach配对调用，未解绑会导致输入法
 * 资源泄漏。
 *     <br>- 创建/销毁配对：所有Create函数创建的对象必须通过对应的Destroy函数销毁，否则会导致内存泄漏。
 *     <br>- 调用顺序：先创建依赖对象（TextEditorProxy、AttachOptions），再执行Attach绑定，绑定成功后使用InputMethodProxy交
 * 互，最后Detach解绑并销毁所有创建的对象。
 *     <br>
 *     <br>线程安全：本模块的API非线程安全，建议在主线程调用。TextEditorProxy的回调执行线程可通过
 * OH_TextEditorProxy_SetCallbackInMainThread配置。
 *
 *     <br>模块架构: 本模块由9个头文件组成，按职责分为四层：
 *     <br>
 *     <br>- 控制层：inputmethod_controller_capi.h —— 模块核心入口，提供绑定/解绑输入法服务的能力，是所有交互的起点和终点。
 *     <br>- 交互层：inputmethod_text_editor_proxy_capi.h和inputmethod_inputmethod_proxy_capi.h —— 双向交互通道。
 * TextEditorProxy是输入法→应用方向的回调注册通道，应用通过它接收输入法的文本插入、删除等通知；InputMethodProxy是应用→输入法方向
 * 的请求发送通道，应用通过它向输入法发送光标更新、选区变更等通知。
 *     <br>- 配置层：inputmethod_attach_options_capi.h、inputmethod_text_config_capi.h、inputmethod_cursor_info_capi.h、
 * inputmethod_text_avoid_info_capi.h —— 各类配置和信息的承载对象，分别管理绑定选项、输入框配置、光标位置信息、避让区域信息。
 *     <br>- 数据层：inputmethod_private_command_capi.h和inputmethod_types_capi.h —— 私有命令数据和公共类型定义（枚举、错误
 * 码等）。
 *     <br>
 *     <br>典型调用流程：
 *     <br>1. 通过inputmethod_text_editor_proxy_capi.h创建TextEditorProxy并注册回调。
 *     <br>2. 通过inputmethod_attach_options_capi.h创建AttachOptions配置绑定选项。
 *     <br>3. 通过inputmethod_controller_capi.h调用Attach绑定输入法，获取InputMethodProxy。
 *     <br>4. 通过inputmethod_inputmethod_proxy_capi.h使用InputMethodProxy与输入法交互。
 *     <br>5. 通过inputmethod_text_config_capi.h、inputmethod_cursor_info_capi.h等管理配置信息。
 *     <br>6. 通过inputmethod_controller_capi.h调用Detach解绑。
 *     <br>7. 销毁所有创建的对象。
 *
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 */

/**
 * @file inputmethod_attach_options_capi.h
 *
 * @brief 输入法绑定选项的头文件，提供AttachOptions实例的创建、销毁与属性读写方法。AttachOptions用于配置绑定输入法时的行为参数，
 * 如是否显示键盘（showKeyboard）和请求键盘的原因（requestKeyboardReason），是调用Attach时的必要参数。Create/Destroy必须配对。
 *     <br>
 *     <br>功能：创建和管理InputMethod_AttachOptions实例，支持配置绑定时是否显示键盘（showKeyboard）以及触发输入法拉起的场景原
 * 因（requestKeyboardReason）。AttachOptions是调用OH_InputMethodController_Attach时的必要参数，用于控制绑定输入法服务时的初
 * 始行为。
 *     <br>
 *     <br>使用场景：在应用绑定输入法服务前，创建AttachOptions配置绑定行为：
 *     <br>- showKeyboard=true时，绑定时自动拉起键盘，适用于输入框获得焦点后需要立即输入的场景。
 *     <br>- showKeyboard=false时，绑定时不拉起键盘，适用于需要先建立交互通道但暂不输入的场景（如搜索框先绑定输入法，等用户点击
 * 后再拉起键盘）。
 *     <br>- requestKeyboardReason用于标识触发输入法拉起的原因（如鼠标点击、触摸事件等），帮助系统识别输入场景以提供更好的用户体
 * 验。
 *     <br>
 *     <br>使用后效果：创建AttachOptions后，将其传入Attach函数，Attach函数将读取其中的配置来决定绑定行为。Attach完成后，
 * AttachOptions可销毁，因为配置信息已被读取。
 *
 * @include <inputmethod/inputmethod_attach_options_capi.h>
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
 * @brief 输入法绑定选项，用于在绑定输入法时携带相关配置。这是一个不透明类型（opaque type），调用者不可直接访问其成员变量，只能通
 * 过本头文件提供的函数操作。
 *     <br>
 *     <br>用途：作为OH_InputMethodController_Attach和OH_InputMethodController_AttachWithUIContext的必要参数，用于配置绑定
 * 输入法时的行为选项，包括：
 *     <br>- 是否在绑定时自动显示键盘（showKeyboard）：控制绑定完成后键盘是否立即弹出。
 *     <br>- 请求键盘的原因（requestKeyboardReason）：标识触发输入法拉起的场景原因（如触摸点击、鼠标点击或应用主动调用），帮助系
 * 统优化输入体验。
 *     <br>
 *     <br>使用场景：
 *     <br>- showKeyboard=true：适用于输入框获得焦点后需要立即输入的场景（如文本编辑框），绑定后键盘自动弹出。
 *     <br>- showKeyboard=false：适用于先建立交互通道但暂不需要键盘的场景（如搜索框），绑定后键盘不弹出，后续通过ShowKeyboard主
 * 动拉起。
 *     <br>- requestKeyboardReason：适用于需要向系统说明触发输入法的场景原因，帮助系统选择合适的输入策略。
 *     <br>
 *     <br>相关函数：<br>
 * | 函数 | 说明 |
 * | -- | -- |
 * | [OH_AttachOptions_Create](capi-inputmethod-attach-options-capi-h.md#oh_attachoptions_create) | 创建
 * AttachOptions实例。 |
 * | [OH_AttachOptions_CreateWithRequestKeyboardReason](capi-inputmethod-attach-options-capi-h.
 * md#oh_attachoptions_createwithrequestkeyboardreason) | 创建AttachOptions实例并指定requestKeyboardReason。 |
 * | [OH_AttachOptions_Destroy](capi-inputmethod-attach-options-capi-h.md#oh_attachoptions_destroy) | 销毁
 * AttachOptions实例。 |
 * | [OH_AttachOptions_IsShowKeyboard](capi-inputmethod-attach-options-capi-h.
 * md#oh_attachoptions_isshowkeyboard) | 获取showKeyboard值。 |
 * | [OH_AttachOptions_GetRequestKeyboardReason](capi-inputmethod-attach-options-capi-h.
 * md#oh_attachoptions_getrequestkeyboardreason) | 获取requestKeyboardReason值。 |
 *     <br>
 *     <br>与其他结构体的关系：
 *     <br>- InputMethod_AttachOptions是OH_InputMethodController_Attach和OH_InputMethodController_AttachWithUIContext的
 * 必要参数之一。Attach函数同时需要InputMethod_TextEditorProxy和InputMethod_AttachOptions两个参数。
 *     <br>- InputMethod_AttachOptions中的requestKeyboardReason使用InputMethod_RequestKeyboardReason枚举类型，该枚举定义在
 * [inputmethod_types_capi.h](capi-inputmethod-types-capi-h.md)中。
 *     <br>- OH_InputMethodProxy_ShowTextInput函数也接受InputMethod_AttachOptions作为参数，用于在已绑定的状态下重新请求显示
 * 键盘并指定请求原因。
 *
 * @since 12
 */
typedef struct InputMethod_AttachOptions InputMethod_AttachOptions;

/**
 * @brief 创建一个{@link InputMethod_AttachOptions}实例，适用于仅需控制键盘显示状态的简单场景。
 * 如需同时指定触发输入法拉起的场景原因，建议使用[OH_AttachOptions_CreateWithRequestKeyboardReason]
 * (#oh_attachoptions_createwithrequestkeyboardreason)。
 *     <br>
 *     <br>配对调用：必须与[OH_AttachOptions_Destroy](#oh_attachoptions_destroy)配对调用，OH_AttachOptions_Create创建的对象
 * 必须通过OH_AttachOptions_Destroy销毁，否则会导致内存泄漏。
 *     <br>
 *     <br>生命周期管理：
 *     <br>- 创建后可多次读取（IsShowKeyboard）。
 *     <br>- 将options传入Attach函数后，Attach函数将读取配置信息。Attach完成后options可立即销毁，因为配置已被读取。
 *     <br>- 不可将已销毁的options再次使用。
 *
 * @param showKeyboard 输入参数，表示绑定时是否显示键盘。
 *     <br>**含义/功能：** 控制Attach绑定输入法时是否自动拉起键盘面板。
 *     <br>**使用场景：** true适用于输入框获得焦点后需要立即输入的场景（如文本编辑框）；false适用于先建立交互通道但暂不需要键盘的
 * 场景（如搜索框，等用户主动点击后再拉起键盘）。
 *     <br>**使用后效果：** showKeyboard=true时，绑定成功后键盘将自动弹出；showKeyboard=false时，绑定成功后键盘不弹出，
 *     需后续通过OH_InputMethodProxy_ShowKeyboard主动拉起。
 *     <br>**取值范围：** true或false。
 *     <br>**默认值：** 无默认值，调用者必须显式指定。
 *     <br>**取值原则：** 根据业务场景决定。需要立即输入的场景设为true；需要延迟拉起键盘的场景设为false，后续通过ShowKeyboard主
 * 动拉起。
 * @return 返回指针类型。
 *     <br>**创建成功：** 返回一个指向新创建的InputMethod_AttachOptions实例的指针，该指针有效且可用于后续操作。
 *     <br>**创建失败：** 返回NULL，可能的失败原因包括应用地址空间满（内存不足）。
 *     <br>**NULL判断：** 调用者必须在使用返回值前检查是否为NULL，若为NULL则不可使用该指针，应排查内存状况或稍后重试。
 *     <br>**内存管理：** 返回的指针由Create函数内部分配内存，调用者需通过OH_AttachOptions_Destroy释放，不可使用free()或其他方
 * 式释放。
 * @since 12
 */
InputMethod_AttachOptions *OH_AttachOptions_Create(bool showKeyboard);
/**
 * @brief 创建一个{@link InputMethod_AttachOptions}实例，同时指定键盘显示状态和请求键盘的原因。
 * requestKeyboardReason参数用于标识触发输入法拉起的场景原因，帮助系统识别输入场景以提供更好的用户体验。
 *     <br>
 *     <br>配对调用：必须与[OH_AttachOptions_Destroy](#oh_attachoptions_destroy)配对调用，Create创建的对象必须通过
 * OH_AttachOptions_Destroy销毁。
 *     <br>
 *     <br>生命周期管理：与OH_AttachOptions_Create一致。创建后可多次读取，Attach完成后可立即销毁。
 *
 * @param showKeyboard 输入参数，表示绑定时是否显示键盘。含义/功能、使用场景、使用后效果、取值范围、取值原则与
 * OH_AttachOptions_Create中的showKeyboard参数一致。
 * @param requestKeyboardReason 输入参数，表示请求键盘输入的原因。
 *     <br>**含义/功能：** 标识触发输入法拉起的场景原因，用于帮助系统识别输入场景并优化用户体验。
 *     <br>**使用场景：** 当应用需要告知系统为何拉起键盘时使用，例如区分用户通过鼠标点击、触摸事件还是应用主动调用API触发输入法。
 *     <br>**使用后效果：** 系统可根据此原因调整输入法行为（如选择合适的键盘布局或输入模式）。
 *     <br>**取值范围：** {@link InputMethod_RequestKeyboardReason}枚举值，包括：
 *     <br>- IME_REQUEST_REASON_NONE (0)：无特定原因。
 *     <br>- IME_REQUEST_REASON_MOUSE (1)：通过鼠标点击触发。
 *     <br>- IME_REQUEST_REASON_TOUCH (2)：通过触摸事件触发。
 *     <br>- IME_REQUEST_REASON_OTHER (20)：其他原因（应用主动调用API等）。
 *     <br>**取值原则：** 根据实际触发场景选择对应的枚举值。用户通过触摸输入框触发时使用IME_REQUEST_REASON_TOUCH；通过鼠标点击
 * 触发时使用IME_REQUEST_REASON_MOUSE；
 *     应用内部逻辑主动触发时使用IME_REQUEST_REASON_OTHER。
 *     <br>**规格限制：** 仅支持上述枚举值，传入其他值可能导致未定义行为。
 * @return 返回指针类型。
 *     <br>**创建成功：** 返回一个指向新创建的InputMethod_AttachOptions实例的指针。
 *     <br>**创建失败：** 返回NULL，可能的失败原因有应用地址空间满（内存不足）。
 *     <br>**NULL判断：** 调用者必须在使用返回值前检查是否为NULL，若为NULL则不可使用该指针。
 *     <br>**内存管理：** 返回的指针由Create函数内部分配内存，调用者需通过OH_AttachOptions_Destroy释放，不可使用free()或其他方
 * 式释放。
 * @since 15
 */
InputMethod_AttachOptions *OH_AttachOptions_CreateWithRequestKeyboardReason(
    bool showKeyboard, InputMethod_RequestKeyboardReason requestKeyboardReason);
/**
 * @brief 销毁一个{@link InputMethod_AttachOptions}实例，释放由OH_AttachOptions_Create函数分配的内存资源。
 * 该方法与OH_AttachOptions_Create和OH_AttachOptions_CreateWithRequestKeyboardReason配对使用。
 *     <br>
 *     <br>配对调用：必须与OH_AttachOptions_Create或OH_AttachOptions_CreateWithRequestKeyboardReason配对调用。每个
 * OH_AttachOptions_Create创建的实例必须且只能调用一次OH_AttachOptions_Destroy。
 *     <br>
 *     <br>生命周期管理：
 *     <br>- OH_AttachOptions_Destroy后，options指针不再有效，不可继续使用。
 *     <br>- 不可对同一个options指针调用两次OH_AttachOptions_Destroy，否则会导致重复释放（double-free）。
 *     <br>- 建议在Attach成功后立即调用OH_AttachOptions_Destroy，因为Attach已读取完配置信息。
 *
 * @param options 输入指针，表示即将被销毁的InputMethod_AttachOptions实例。
 *     <br>**含义/功能：** 指定要销毁的AttachOptions实例，OH_AttachOptions_Destroy将释放该实例占用的内存资源。
 *     <br>**使用场景：** 在AttachOptions不再需要时调用，典型时机为Attach绑定完成后。
 *     <br>**使用后效果：** options指向的内存被释放，该指针不再有效。
 *     <br>**NULL指针处理：** 若options为NULL，OH_AttachOptions_Destroy函数不做任何操作（安全处理），不会导致崩溃。但建议调用
 * 者避免传入NULL，
 *     因为这意味着OH_AttachOptions_Create失败未被正确处理。
 *     <br>**内存释放责任：** 由调用者负责在适当时机调用OH_AttachOptions_Destroy释放内存。
 * @since 12
 */
void OH_AttachOptions_Destroy(InputMethod_AttachOptions *options);
/**
 * @brief 从{@link InputMethod_AttachOptions}中获取是否显示键盘的值。
 *     <br>
 *     <br>前置条件：options必须是通过OH_AttachOptions_Create函数创建的有效实例，showKeyboard必须指向有效的bool变量。
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
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。表示options或showKeyboard为空指针，调用前需确保这两个参数已正确初始
 * 化且不为NULL。
 *     <br>**错误处理建议：** 若返回IME_ERR_NULL_POINTER，检查options和showKeyboard是否为有效指针；
 * 若返回IME_ERR_OK，*showKeyboard即为正确的配置值。
 *     具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_AttachOptions_IsShowKeyboard(InputMethod_AttachOptions *options, bool *showKeyboard);
/**
 * @brief 从{@link InputMethod_AttachOptions}中获取请求键盘输入的原因。
 *     <br>
 *     <br>前置条件：options必须是通过OH_AttachOptions_CreateWithRequestKeyboardReason创建的实例
 * （通过OH_AttachOptions_Create创建的实例的requestKeyboardReason默认值为IME_REQUEST_REASON_NONE）。
 *     requestKeyboardReason必须指向有效的InputMethod_RequestKeyboardReason变量。
 *
 * @param options 输入指针，表示被读取值的InputMethod_AttachOptions实例。
 *     <br>**含义/功能：** 指定要从哪个AttachOptions实例中读取requestKeyboardReason属性。
 *     <br>**NULL指针处理：** 不可为NULL，传入NULL将返回IME_ERR_NULL_POINTER。
 *     <br>**前提条件：** 必须通过OH_AttachOptions_Create函数创建的有效实例。若实例通过OH_AttachOptions_Create
 * （而非CreateWithRequestKeyboardReason）创建，读取的requestKeyboardReason默认值为IME_REQUEST_REASON_NONE。
 * @param requestKeyboardReason 输出指针，表示请求键盘输入的原因。
 *     <br>**含义/功能：** 输出参数，用于获取触发输入法拉起的场景原因枚举值。
 *     <br>**使用场景：** 需要查询AttachOptions的请求键盘原因配置时使用。
 *     <br>**取值范围：** 输出值为{@link InputMethod_RequestKeyboardReason}枚举：IME_REQUEST_REASON_NONE(0)、
 * IME_REQUEST_REASON_MOUSE(1)、IME_REQUEST_REASON_TOUCH(2)、IME_REQUEST_REASON_OTHER(20)。
 *     <br>**NULL指针处理：** 不可为NULL，传入NULL将返回IME_ERR_NULL_POINTER。调用者需确保requestKeyboardReason指向有效的变
 * 量。
 *     <br>**内存分配责任：** 由调用者分配变量的内存，GetRequestKeyboardReason仅写入值，不分配内存。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。*requestKeyboardReason已被赋值为正确的枚举值。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。表示options或requestKeyboardReason为空指针，调用前需确保这两个参数
 * 已正确初始化且不为NULL。
 *     <br>**错误处理建议：** 若返回IME_ERR_NULL_POINTER，检查options和requestKeyboardReason是否为有效指针；若返IME_ERR_OK，
 * *requestKeyboardReason即为正确的配置值。具体错误码可以参考{@link InputMethod_ErrorCode}。
 *
 * @since 15
 */
InputMethod_ErrorCode OH_AttachOptions_GetRequestKeyboardReason(
    InputMethod_AttachOptions *options, int *requestKeyboardReason);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_ATTACH_OPTIONS_CAPI_H
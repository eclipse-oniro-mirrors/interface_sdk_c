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
 * @file inputmethod_text_editor_proxy_capi.h
 *
 * @brief 文本编辑器代理的头文件，提供一套方法支持应用开发的自绘输入框获取来自输入法应用的通知和请求。该模块采用回调机制实现输入法
 * 应用与自绘输入框之间的双向通信。
 * 提供创建/销毁TextEditorProxy实例以及注册/获取回调函数的方法。TextEditorProxy是应用接收输入法通知和请求的回调通道，
 * 应用需在绑定前创建TextEditorProxy并注册必要的回调函数（如InsertText、DeleteForward等），绑定后输入法将通过这些回调与应用交
 * 互。生命周期由调用者管理，Create/Destroy必须配对。
 *
 * @include <inputmethod/inputmethod_text_editor_proxy_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_TEXT_EDITOR_PROXY_CAPI_H
#define OHOS_INPUTMETHOD_TEXT_EDITOR_PROXY_CAPI_H
#include <stddef.h>

#include "inputmethod_private_command_capi.h"
#include "inputmethod_text_config_capi.h"
#include "inputmethod_types_capi.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @brief 输入法文本编辑器代理类。用于处理输入法应用与文本编辑器之间的交互，提供接收输入法请求和通知的方法，适用于需要实现输入法与
 * 编辑器双向通信的场景。该结构体为不透明类型（opaque type），调用者不可直接访问其内部成员，
 * 仅可通过本模块提供的函数接口进行操作。
 *     <br>
 *     <br>结构体用途：
 *     <br>InputMethod_TextEditorProxy是文本编辑器端与输入法应用交互的代理对象，采用回调机制实现输入法应用向编辑器发送请求和通知
 * 的双向通信。当输入法应用向编辑器发送请求（如插入文本、删除文本、移动光标等）或通知（如键盘状态变化、回车键事件等）时，通过此代理
 * 对象中注册的回调函数进行处理。开发者需实现各回调函数并通过Set*Func接口将其注册到TextEditorProxy中，再通过Attach完成注册。
 *     <br>
 *     <br>生命周期管理：
 *     <br>- 创建方式：通过[OH_TextEditorProxy_Create](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_create)函数创建，返回一个新的InputMethod_TextEditorProxy实例指针。创建失败时返回NULL，可能原因为内存
 * 不足。
 *     <br>- 销毁方式：通过[OH_TextEditorProxy_Destroy](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_destroy)函数销毁，传入要销毁的实例指针。销毁后指针不可再使用，建议将指针设置为NULL避免误用。
 *     <br>- 配对关系：OH_TextEditorProxy_Create与OH_TextEditorProxy_Destroy必须配对使用，创建的对象必须最终通过Destroy释
 * 放，否则会导致内存泄漏。同一个TextEditorProxy实例只能被销毁一次，不可重复销毁。
 *     <br>- 使用时机：创建TextEditorProxy后，须先通过Set*Func接口注册回调函数，再通过[OH_InputMethodController_Attach]
 * (capi-inputmethod-controller-capi-h.md#oh_inputmethodcontroller_attach)完成绑定注册。Attach之后不建议再修改回调函数设
 * 置。
 *     <br>
 *     <br>回调机制说明：
 *     <br>TextEditorProxy采用回调函数机制实现输入法应用与编辑器之间的双向通信：
 *     <br>- 回调注册流程：创建TextEditorProxy → 通过Set*Func接口注册各回调函数 → 通过Attach完成注册。
 *     <br>- 回调触发时机：当输入法应用向编辑器发送请求或通知时，系统自动调用TextEditorProxy中已注册的对应回调函数。
 *     <br>- 回调函数中指针的临时性：回调函数中接收到的指针参数（如text、privateCommand等）仅在回调执行期间有效，回调返回后该内
 * 存将被释放，不可再访问。开发者应在回调内部完成必要的数据拷贝或处理，不得在回调外部继续使用这些指针。
 *     <br>- GetTextConfigFunc不受SetCallbackInMainThread影响：[OH_TextEditorProxy_GetTextConfigFunc]
 * (capi-inputmethod-text-editor-proxy-capi-h.md#oh_texteditorproxy_gettextconfigfunc)的执行线程由调用
 * [OH_InputMethodController_Attach](capi-inputmethod-controller-capi-h.md#oh_inputmethodcontroller_attach)的线程决定，不
 * 受[OH_TextEditorProxy_SetCallbackInMainThread](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setcallbackinmainthread)的影响。若需GetTextConfigFunc也在主线程执行，需确保Attach在主线程调用。
 *     <br>
 *     <br>使用注意事项：
 *     <br>- 所有Set*Func接口必须在Attach之前调用，Attach后设置的回调函数将不会被输入法调用。
 *     <br>- 回调函数中的指针参数具有临时性，回调返回后不可再访问，必须在回调内部完成数据处理。
 *     <br>- 建议至少注册GetTextConfigFunc和InsertTextFunc两个核心回调，否则输入法可能无法正常工作。
 *     <br>- 非线程安全，不建议在多线程环境下同时操作同一个TextEditorProxy对象。可通过
 * [OH_TextEditorProxy_SetCallbackInMainThread](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setcallbackinmainthread)将回调切换到主线程执行以避免多线程并发问题。
 *     <br>- 此对象为不透明类型，不可直接访问内部成员或进行内存操作。
 *     <br>
 *     <br>相关函数：
 *     <br>
 *     <br>- 创建/销毁函数<br>
 * | 函数 | 描述 |
 * | -- | -- |
 * | [OH_TextEditorProxy_Create](capi-inputmethod-text-editor-proxy-capi-h.md#oh_texteditorproxy_create) | 创建
 * 一个新的InputMethod_TextEditorProxy实例。 |
 * | [OH_TextEditorProxy_Destroy](capi-inputmethod-text-editor-proxy-capi-h.md#oh_texteditorproxy_destroy) | 销
 * 毁一个InputMethod_TextEditorProxy实例。 |
 *     <br>
 *     <br>- 回调设置函数（Set*Func，须在Attach前调用）<br>
 * | 函数 | 描述 |
 * | -- | -- |
 * | [OH_TextEditorProxy_SetGetTextConfigFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setgettextconfigfunc) | 设置GetTextConfigFunc回调。 |
 * | [OH_TextEditorProxy_SetInsertTextFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setinserttextfunc) | 设置InsertTextFunc回调。 |
 * | [OH_TextEditorProxy_SetDeleteForwardFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setdeleteforwardfunc) | 设置DeleteForwardFunc回调。 |
 * | [OH_TextEditorProxy_SetDeleteBackwardFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setdeletebackwardfunc) | 设置DeleteBackwardFunc回调。 |
 * | [OH_TextEditorProxy_SetSendKeyboardStatusFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setsendkeyboardstatusfunc) | 设置SendKeyboardStatusFunc回调。 |
 * | [OH_TextEditorProxy_SetSendEnterKeyFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setsendenterkeyfunc) | 设置SendEnterKeyFunc回调。 |
 * | [OH_TextEditorProxy_SetMoveCursorFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setmovecursorfunc) | 设置MoveCursorFunc回调。 |
 * | [OH_TextEditorProxy_SetHandleSetSelectionFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_sethandlesetselectionfunc) | 设置HandleSetSelectionFunc回调。 |
 * | [OH_TextEditorProxy_SetHandleExtendActionFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_sethandleextendactionfunc) | 设置HandleExtendActionFunc回调。 |
 * | [OH_TextEditorProxy_SetGetLeftTextOfCursorFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setgetlefttextofcursorfunc) | 设置GetLeftTextOfCursorFunc回调。 |
 * | [OH_TextEditorProxy_SetGetRightTextOfCursorFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setgetrighttextofcursorfunc) | 设置GetRightTextOfCursorFunc回调。 |
 * | [OH_TextEditorProxy_SetGetTextIndexAtCursorFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setgettextindexatcursorfunc) | 设置GetTextIndexAtCursorFunc回调。 |
 * | [OH_TextEditorProxy_SetReceivePrivateCommandFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setreceiveprivatecommandfunc) | 设置ReceivePrivateCommandFunc回调。 |
 * | [OH_TextEditorProxy_SetSetPreviewTextFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setsetpreviewtextfunc) | 设置SetPreviewTextFunc回调。 |
 * | [OH_TextEditorProxy_SetFinishTextPreviewFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setfinishtextpreviewfunc) | 设置FinishTextPreviewFunc回调。 |
 *     <br>
 *     <br>- 回调获取函数（Get*Func）<br>
 * | 函数 | 描述 |
 * | -- | -- |
 * | [OH_TextEditorProxy_GetGetTextConfigFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_getgettextconfigfunc) | 获取已注册的GetTextConfigFunc回调。 |
 * | [OH_TextEditorProxy_GetInsertTextFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_getinserttextfunc) | 获取已注册的InsertTextFunc回调。 |
 * | [OH_TextEditorProxy_GetDeleteForwardFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_getdeleteforwardfunc) | 获取已注册的DeleteForwardFunc回调。 |
 * | [OH_TextEditorProxy_GetDeleteBackwardFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_getdeletebackwardfunc) | 获取已注册的DeleteBackwardFunc回调。 |
 * | [OH_TextEditorProxy_GetSendKeyboardStatusFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_getsendkeyboardstatusfunc) | 获取已注册的SendKeyboardStatusFunc回调。 |
 * | [OH_TextEditorProxy_GetSendEnterKeyFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_getsendenterkeyfunc) | 获取已注册的SendEnterKeyFunc回调。 |
 * | [OH_TextEditorProxy_GetMoveCursorFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_getmovecursorfunc) | 获取已注册的MoveCursorFunc回调。 |
 * | [OH_TextEditorProxy_GetHandleSetSelectionFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_gethandlesetselectionfunc) | 获取已注册的HandleSetSelectionFunc回调。 |
 * | [OH_TextEditorProxy_GetHandleExtendActionFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_gethandleextendactionfunc) | 获取已注册的HandleExtendActionFunc回调。 |
 * | [OH_TextEditorProxy_GetGetLeftTextOfCursorFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_getgetlefttextofcursorfunc) | 获取已注册的GetLeftTextOfCursorFunc回调。 |
 * | [OH_TextEditorProxy_GetGetRightTextOfCursorFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_getgetrighttextofcursorfunc) | 获取已注册的GetRightTextOfCursorFunc回调。 |
 * | [OH_TextEditorProxy_GetGetTextIndexAtCursorFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_getgettextindexatcursorfunc) | 获取已注册的GetTextIndexAtCursorFunc回调。 |
 * | [OH_TextEditorProxy_GetReceivePrivateCommandFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_getreceiveprivatecommandfunc) | 获取已注册的ReceivePrivateCommandFunc回调。 |
 * | [OH_TextEditorProxy_GetSetPreviewTextFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_getsetpreviewtextfunc) | 获取已注册的SetPreviewTextFunc回调。 |
 * | [OH_TextEditorProxy_GetFinishTextPreviewFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_getfinishtextpreviewfunc) | 获取已注册的FinishTextPreviewFunc回调。 |
 *     <br>
 *     <br>- 线程配置函数：<br>
 * | 函数 | 描述 |
 * | -- | -- |
 * | [OH_TextEditorProxy_SetCallbackInMainThread](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_setcallbackinmainthread) | 配置回调函数的执行线程策略。 |
 *     <br>
 *     <br>关联关系：
 *     <br>
 *     <br>- 与InputMethodProxy的关系：[InputMethod_InputMethodProxy](capi-inputmethod-inputmethod-inputmethodproxy.md)负
 * 责向输入法服务发送请求和通知，InputMethod_TextEditorProxy负责接收输入法应用的请求和通知。两者在Attach时同时建立关联，构成双向
 * 通信通道。
 *     <br>- 与TextConfig的关系：[InputMethod_TextConfig](capi-inputmethod-inputmethod-textconfig.md)在GetTextConfigFunc
 * 回调中使用，用于向输入法传递编辑框的配置信息。GetTextConfigFunc回调被触发时，开发者需在回调内对config参数赋值以填充配置信息。
 *
 * @since 12
 */
typedef struct InputMethod_TextEditorProxy InputMethod_TextEditorProxy;

/**
 * @brief 输入法获取输入框配置时触发的回调函数。开发者需实现此函数，在函数中对config参数设置编辑框的配置信息（输入类型、回车键类
 * 型、光标信息等），输入法框架将据此调整键盘布局和输入行为。
 *     <br>
 *     <br>使用场景：当输入法应用需要获取编辑框的配置信息时，系统将自动调用此回调。此回调是输入法与编辑器交互的核心回调之一，必须
 * 实现。
 *     <br>
 *     <br>使用后效果：回调返回后，输入法框架将读取config中的配置信息并据此调整键盘行为。config参数的内存将在回调返回后被释放，不
 * 可再访问。
 *     <br>
 *     <br>前置条件：须通过[OH_TextEditorProxy_SetGetTextConfigFunc](#oh_texteditorproxy_setgettextconfigfunc)将此回调设置
 * 到TextEditorProxy中，并通过[OH_InputMethodController_Attach](capi-inputmethod-controller-capi-h.
 * md#oh_inputmethodcontroller_attach)完成注册。此回调的执行线程由调用Attach的线程决定，不受
 * [OH_TextEditorProxy_SetCallbackInMainThread](#oh_texteditorproxy_setcallbackinmainthread)影响。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的{@link InputMethod_TextEditorProxy}实例。用于标识触发回调的代理对象。
 * @param config 输出指针，表示指向{@link InputMethod_TextConfig}实例的指针。需要在函数实现中对其设置各配置属性（输入类型、回车
 * 键类型、光标信息等）以填充输入框配置。此指针仅在回调执行期间有效，回调返回后该内存将被释放，不可再访问。开发者必须在回调内部完成
 * 所有设置操作，不得在回调外部继续使用此指针。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_GetTextConfigFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_TextConfig *config);
/**
 * @brief 输入法应用插入文本时触发的回调函数。开发者需实现此函数，在函数中将text参数指定的文本内容插入到编辑框的光标位置。
 *     <br>
 *     <br>使用场景：当输入法应用向编辑框插入文本时（如用户选择候选词、输入字符等），系统将自动调用此回调。此回调是输入法与编辑器
 * 交互的核心回调之一，必须实现。
 *     <br>
 *     <br>使用后效果：回调执行后，编辑框应在光标位置插入指定文本，并更新文本内容和光标位置。
 *     <br>
 *     <br>前置条件：须通过OH_TextEditorProxy_SetInsertTextFunc将此回调设置到TextEditorProxy中，并通过Attach完成注册。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param text 输入指针，插入的文本内容，采用UTF-16编码。此指针仅在回调执行期间有效，回调返回后该内存将被释放，不可再访问。开发者
 * 应在回调内部完成必要的数据拷贝或处理。
 * @param length 输入参数，插入字符的数量（单位：char16_t字符个数）。取值范围：大于0。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_InsertTextFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, const char16_t *text, size_t length);
/**
 * @brief 输入法删除光标右侧文本时触发的回调函数。开发者需实现此函数，在函数中从光标位置向右删除指定数量的字符。
 *     <br>
 *     <br>使用场景：当输入法应用请求删除光标右侧文本时（如用户在输入法中执行向前删除操作），系统将自动调用此回调。
 *     <br>
 *     <br>使用后效果：回调执行后，编辑框应从光标位置向右删除指定数量的字符，并更新文本内容和光标位置。
 *     <br>
 *     <br>前置条件：须通过OH_TextEditorProxy_SetDeleteForwardFunc将此回调设置到TextEditorProxy中，并通过Attach完成注册。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param length 输入参数，要删除的字符数量（单位：字符个数）。取值范围：大于0且不超过光标右侧剩余文本长度。取值原则：若length超
 * 过右侧剩余文本长度，应删除到文本末尾。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_DeleteForwardFunc)(InputMethod_TextEditorProxy *textEditorProxy, int32_t length);
/**
 * @brief 输入法删除光标左侧文本时触发的回调函数。开发者需实现此函数，在函数中从光标位置向左删除指定数量的字符。
 *     <br>
 *     <br>输入法删除光标左侧文本时触发的回调函数。开发者需实现此函数，在函数中从光标位置向左删除指定数量的字符。
 *     <br>
 *     <br>使用场景：当输入法应用请求删除光标左侧文本时（如用户在输入法中执行退格删除操作），系统将自动调用此回调。
 *     <br>
 *     <br>使用后效果：回调执行后，编辑框应从光标位置向左删除指定数量的字符，并更新文本内容和光标位置。
 *     <br>
 *     <br>前置条件：须通过[OH_TextEditorProxy_SetDeleteBackwardFunc](#oh_texteditorproxy_setdeletebackwardfunc)将此回调设
 * 置到TextEditorProxy中，并通过Attach完成注册。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param length 输入参数，要删除的字符数量（单位：字符个数）。取值范围：大于0且不超过光标左侧已有文本长度。取值原则：若length超
 * 过左侧已有文本长度，应删除到文本开头。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_DeleteBackwardFunc)(InputMethod_TextEditorProxy *textEditorProxy, int32_t length);
/**
 * @brief 输入法通知键盘状态时触发的回调函数。开发者需实现此函数，在函数中根据keyboardStatus参数更新编辑框对键盘状态的感知。
 *     <br>
 *     <br>使用场景：当输入法应用的键盘状态发生变化（显示或隐藏）时，系统将自动调用此回调，通知编辑框当前的键盘状态。
 *     <br>
 *     <br>使用后效果：回调执行后，编辑框应据此更新对键盘可见性的感知，例如调整避让策略或UI布局。
 *     <br>
 *     <br>前置条件：须通过[OH_TextEditorProxy_SetSendKeyboardStatusFunc](#oh_texteditorproxy_setsendkeyboardstatusfunc)
 * 将此回调设置到TextEditorProxy中，并通过Attach完成注册。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param keyboardStatus 输入参数，键盘状态。取值范围：{@link InputMethod_KeyboardStatus}枚举值（IME_KEYBOARD_NONE=0、
 * IME_KEYBOARD_SHOW=1、IME_KEYBOARD_HIDE=2）。使用后效果：设置为IME_KEYBOARD_SHOW时表示键盘已弹出，IME_KEYBOARD_HIDE时表示
 * 键盘已收起。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_SendKeyboardStatusFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_KeyboardStatus keyboardStatus);
/**
 * @brief 输入法发送回车键时触发的回调函数。开发者需实现此函数，在函数中根据enterKeyType参数执行对应的回车键动作。
 *     <br>
 *     <br>使用场景：当输入法应用通知编辑框回车键事件时，系统将自动调用此回调。
 *     <br>
 *     <br>使用后效果：回调执行后，编辑框应据此执行对应的回车键行为（如搜索、发送、完成等）。
 *     <br>
 *     <br>前置条件：须通过[OH_TextEditorProxy_SetSendEnterKeyFunc](#oh_texteditorproxy_setsendenterkeyfunc)将此回调设置到
 * TextEditorProxy中，并通过Attach完成注册。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param enterKeyType 输入参数，回车键类型。取值范围：{@link InputMethod_EnterKeyType}枚举值。使用后效果：不同类型对应不同的
 * 回车键行为，如IME_ENTER_KEY_GO表示"前往"、
 *     IME_ENTER_KEY_SEARCH表示"搜索"等。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_SendEnterKeyFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_EnterKeyType enterKeyType);
/**
 * @brief 输入法移动光标时触发的回调函数。开发者需实现此函数，在函数中根据direction参数移动编辑框中的光标位置。
 *     <br>
 *     <br>使用场景：当输入法应用请求移动光标时，系统将自动调用此回调。
 *     <br>
 *     <br>使用后效果：回调执行后，编辑框应据此移动光标位置，并更新光标显示。
 *     <br>
 *     <br>前置条件：须通过[OH_TextEditorProxy_SetMoveCursorFunc](#oh_texteditorproxy_setmovecursorfunc)将此回调设置到
 * TextEditorProxy中，并通过Attach完成注册。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param direction 输入参数，光标移动方向。取值范围：{@link InputMethod_Direction}枚举值。使用后效果：不同方向对应不同的光标移
 * 动行为，如IME_DIRECTION_UP表示上移、IME_DIRECTION_DOWN表示下移、IME_DIRECTION_LEFT表示左移、IME_DIRECTION_RIGHT表示右移。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_MoveCursorFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_Direction direction);
/**
 * @brief 输入法请求选中文本时触发的回调函数。开发者需实现此函数，在函数中根据start和end参数选中编辑框中的指定范围文本。
 *     <br>
 *     <br>使用场景：当输入法应用请求选中编辑框中一段文本时，系统将自动调用此回调。
 *     <br>
 *     <br>使用后效果：回调执行后，编辑框应将start到end范围内的文本选中，并更新选中状态和UI显示。
 *     <br>
 *     <br>前置条件：须通过[OH_TextEditorProxy_SetHandleSetSelectionFunc](#oh_texteditorproxy_sethandlesetselectionfunc)
 * 将此回调设置到TextEditorProxy中，并通过Attach完成注册。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param start 输入参数，选中文本的起始位置（单位：字符偏移量，从0开始计数）。取值原则：start应大于等于0且小于等于end。
 * @param end 输入参数，选中文本的结束位置（单位：字符偏移量，从0开始计数）。取值原则：end应大于等于start且小于文本总长度。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_HandleSetSelectionFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, int32_t start, int32_t end);
/**
 * @brief 输入法发送扩展编辑操作时触发的回调函数。开发者需实现此函数，在函数中根据action参数执行对应的扩展编辑操作。
 *     <br>
 *     <br>使用场景：当输入法应用请求执行扩展编辑操作（如剪切、复制、全选等）时，系统将自动调用此回调。
 *     <br>
 *     <br>使用后效果：回调执行后，编辑框应据此执行对应的扩展编辑动作。
 *     <br>
 *     <br>前置条件：须通过[OH_TextEditorProxy_SetHandleExtendActionFunc](#oh_texteditorproxy_sethandleextendactionfunc)
 * 将此回调设置到TextEditorProxy中，并通过Attach完成注册。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param action 输入参数，扩展编辑操作。取值范围：{@link InputMethod_ExtendAction}枚举值。使用后效果：不同操作对应不同的编辑行
 * 为，如IME_EXTEND_ACTION_SELECT_ALL表示全选、IME_EXTEND_ACTION_CUT表示剪切、IME_EXTEND_ACTION_COPY表示复制等。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_HandleExtendActionFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_ExtendAction action);
/**
 * @brief 输入法获取光标左侧文本时触发的回调函数。开发者需实现此函数，在函数中将光标左侧指定数量的文本内容写入text参数，并将实际字
 * 符数量写入length参数。
 *     <br>
 *     <br>使用场景：当输入法应用需要获取光标左侧的文本内容（如用于联想输入、上下文分析等）时，系统将自动调用此回调。
 *     <br>
 *     <br>使用后效果：回调返回后，输入法应用将读取text和length中的数据用于上下文分析。
 *     <br>
 *     <br>前置条件：须通过[OH_TextEditorProxy_SetGetLeftTextOfCursorFunc]
 * (#oh_texteditorproxy_setgetlefttextofcursorfunc)将此回调设置到TextEditorProxy中，并通过Attach完成注册。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param number 输入参数，要获取的字符数量（单位：字符个数）。取值范围：大于0。取值原则：若number超过光标左侧已有文本长度，应返
 * 回左侧全部文本。
 * @param text 输出指针，光标左侧指定长度的文本内容，需要在函数实现中对它赋值。采用UTF-16编码。此指针仅在回调执行期间有效，回调返
 * 回后该内存将被释放，不可再访问。开发者需在回调内部完成赋值操作。
 * @param length 输出指针，用于返回实际获取到的字符数量（单位：char16_t字符个数）。由调用者（输入法框架）分配内存，开发者需在回调
 * 内部对*length赋值。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_GetLeftTextOfCursorFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, int32_t number, char16_t text[], size_t *length);
/**
 * @brief 输入法获取光标右侧文本时触发的回调函数。开发者需实现此函数，在函数中将光标右侧指定数量的文本内容写入text参数，并将实际字
 * 符数量写入length参数。
 *     <br>
 *     <br>使用场景：当输入法应用需要获取光标右侧的文本内容时，系统将自动调用此回调。
 *     <br>
 *     <br>使用后效果：回调返回后，输入法应用将读取text和length中的数据用于上下文分析。
 *     <br>
 *     <br>前置条件：须通过[OH_TextEditorProxy_SetGetRightTextOfCursorFunc]
 * (#oh_texteditorproxy_setgetrighttextofcursorfunc)将此回调设置到TextEditorProxy中，并通过Attach完成注册。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param number 输入参数，要获取的字符数量（单位：字符个数）。取值范围：大于0。取值原则：若number超过光标右侧剩余文本长度，应返
 * 回右侧全部文本。
 * @param text 输出指针，光标右侧指定长度的文本内容，需要在函数实现中对它赋值。采用UTF-16编码。此指针仅在回调执行期间有效，回调返
 * 回后该内存将被释放，不可再访问。
 * @param length 输出指针，用于返回实际获取到的字符数量（单位：char16_t字符个数）。由调用者分配内存，开发者需在回调内部对*length
 * 赋值。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_GetRightTextOfCursorFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, int32_t number, char16_t text[], size_t *length);
/**
 * @brief 输入法获取光标所在输入框文本索引时触发的回调函数。开发者需实现此函数，在函数中返回光标在编辑框文本中的字符索引位置。
 *     <br>
 *     <br>使用场景：当输入法应用需要获取光标在文本中的精确位置时，系统将自动调用此回调。
 *     <br>
 *     <br>使用后效果：回调返回后，输入法应用将读取返回的索引值用于定位上下文。
 *     <br>
 *     <br>前置条件：须通过[OH_TextEditorProxy_SetGetTextIndexAtCursorFunc]
 * (#oh_texteditorproxy_setgettextindexatcursorfunc)将此回调设置到TextEditorProxy中，并通过Attach完成注册。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @return 返回光标在文本内容中的字符索引位置，索引从0开始计数（单位：字符偏移量）。取值范围：大于等于0且小于文本总长度。
 * @since 12
 */
typedef int32_t (*OH_TextEditorProxy_GetTextIndexAtCursorFunc)(InputMethod_TextEditorProxy *textEditorProxy);
/**
 * @brief 输入法应用发送私有数据命令时触发的回调函数。开发者需实现此函数，在函数中处理输入法应用发送的私有命令数据。
 *     <br>
 *     <br>使用场景：当输入法应用通过[OH_InputMethodProxy_SendPrivateCommand](capi-inputmethod-inputmethod-proxy-capi-h.
 * md#oh_inputmethodproxy_sendprivatecommand)向编辑框发送私有命令时，系统将自动调用此回调。
 *     <br>
 *     <br>使用后效果：回调返回后，输入法应用将根据返回值判断命令是否被成功处理。
 *     <br>
 *     <br>前置条件：须通过[OH_TextEditorProxy_SetReceivePrivateCommandFunc]
 * (#oh_texteditorproxy_setreceiveprivatecommandfunc)将此回调设置到TextEditorProxy中，并通过Attach完成注册。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param privateCommand 输入指针，私有数据命令数组。此指针仅在回调执行期间有效，回调返回后该内存将被释放，不可再访问。开发者应在
 * 回调内部完成必要的数据拷贝或处理，不得在回调外部继续使用此指针。
 * @param size 输入参数，私有数据命令数组中的元素数量。取值范围：大于0且不超过5。
 * @return 返回对私有数据命令的处理结果。0表示成功，非0表示失败。
 * @since 12
 */
typedef int32_t (*OH_TextEditorProxy_ReceivePrivateCommandFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_PrivateCommand *privateCommand[], size_t size);
/**
 * @brief 输入法设置预上屏文本时触发的回调函数。预上屏是输入法的候选文本展示功能，通常在用户输入拼音或输入码未确定汉字时显示。此函
 * 数负责设置预上屏文本及其光标位置。与{@link OH_TextEditorProxy_FinishTextPreviewFunc}配合使用：先调用SetPreviewTextFunc设置
 * 预上屏内容，当用户选择候选词或取消输入时，调用FinishTextPreviewFunc结束预上屏。
 *     <br>
 *     <br> 使用场景：当输入法应用需要展示候选文本（如拼音输入时的预上屏文本）时，系统将自动调用此回调。
 *     <br>
 *     <br> 使用后效果：回调执行后，编辑框应将text内容以预上屏样式显示在start到end范围内，并将返回值反馈给输入法。
 *     <br>
 *     <br> 前置条件：须通过[OH_TextEditorProxy_SetSetPreviewTextFunc](#oh_texteditorproxy_setsetpreviewtextfunc)将此回调
 * 设置到TextEditorProxy中，并通过Attach完成注册。编辑框需在TextConfig中设置支持预上屏（supported=true）。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param text 输入指针，请求设置为预上屏样式的文本内容，采用UTF-16编码。此指针仅在回调执行期间有效，回调返回后该内存将被释放，不
 * 可再访问。开发者应在回调内部完成必要的数据拷贝。
 * @param length 输入参数，预上屏文本的字符数量（单位：char16_t字符个数）。
 * @param start 输入参数，预上屏文本起始光标位置（单位：字符偏移量，相对于文本开头）。
 * @param end 输入参数，预上屏文本结束光标位置（单位：字符偏移量，相对于文本开头）。
 * @return 返回处理结果。0表示成功，非0表示失败。
 * @since 12
 */
typedef int32_t (*OH_TextEditorProxy_SetPreviewTextFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, const char16_t text[], size_t length, int32_t start, int32_t end);
/**
 * @brief 输入法结束预上屏时触发的回调函数。此函数用于清理预上屏状态，通常在用户选择候选词（确定输入）或取消输入时调用。
 * 与{@link OH_TextEditorProxy_SetPreviewTextFunc}配合使用。
 *     <br>
 *     <br> 使用场景：当输入法应用需要结束预上屏状态时，系统将自动调用此回调。
 *     <br>
 *     <br> 使用后效果：回调执行后，编辑框应清理预上屏显示状态，恢复到正常文本显示。
 *     <br>
 *     <br> 前置条件：须通过[OH_TextEditorProxy_SetFinishTextPreviewFunc](#oh_texteditorproxy_setfinishtextpreviewfunc)将
 * 此回调设置到TextEditorProxy中，并通过Attach完成注册。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_FinishTextPreviewFunc)(InputMethod_TextEditorProxy *textEditorProxy);

/**
 * @brief 创建一个新的{@link InputMethod_TextEditorProxy}实例。创建后需通过Set*Func接口注册回调函数，再通过
 * {@link OH_InputMethodController_Attach}完成绑定注册。
 *     <br>
 *     <br> 使用场景：当应用需要创建文本编辑器代理对象以接收输入法请求和通知时调用此函数。
 *     <br>
 *     <br> 使用后效果：创建成功后返回一个新的TextEditorProxy实例指针，后续可通过Set*Func接口注册回调函数。
 *     <br>
 *     <br> 生命周期管理：返回的对象必须通过[OH_TextEditorProxy_Destroy](#oh_texteditorproxy_destroy)销毁，Create与Destroy
 * 必须配对使用。未销毁会导致内存泄漏。同一个实例只能被销毁一次。
 *
 * @return 如果创建成功，返回一个指向新创建的{@link InputMethod_TextEditorProxy}实例的指针。如果创建失败，返回NULL，可能的失败
 * 原因有内存不足。返回NULL时应检查系统内存状态。返回的指针在使用完毕后必须通过{@link OH_TextEditorProxy_Destroy}销毁，销毁后指
 * 针应设置为NULL避免误用。
 * @since 12
 */
InputMethod_TextEditorProxy *OH_TextEditorProxy_Create(void);
/**
 * @brief 销毁一个{@link InputMethod_TextEditorProxy}实例。销毁后proxy指针不可再使用，建议将指针设置为NULL避免误用。
 *     <br>
 *     <br>使用场景：当应用需要创建文本编辑器代理对象以接收输入法请求和通知时调用此函数。
 *     <br>
 *     <br>使用后效果：创建成功后返回一个新的TextEditorProxy实例指针，后续可通过Set*Func接口注册回调函数。
 *     <br>
 *     <br>生命周期管理：返回的对象必须通过[OH_TextEditorProxy_Destroy](#oh_texteditorproxy_destroy)销毁，Create与Destroy必
 * 须配对使用。未销毁会导致内存泄漏。同一个实例只能被销毁一次。
 *
 * @param proxy 输入指针，表示指向即将被销毁的{@link InputMethod_TextEditorProxy}实例的指针。若传入NULL，函数不做任何处理，不
 * 会导致崩溃。销毁后该指针失效，建议设置为NULL。
 * @since 12
 */
void OH_TextEditorProxy_Destroy(InputMethod_TextEditorProxy *proxy);
/**
 * @brief 将函数{@link OH_TextEditorProxy_GetTextConfigFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach
 * 之前完成，Attach后设置的回调不会被输入法调用。
 *     <br>
 *     <br> 使用场景：当应用需要注册GetTextConfigFunc回调以响应输入法获取配置请求时调用此函数。
 *     <br>
 *     <br> 使用后效果：设置成功后，GetTextConfigFunc回调将被注册到TextEditorProxy中，Attach后当输入法请求获取配置时将自动触发
 * 此回调。
 *     <br>
 *     <br> 前置条件：proxy须先通过[OH_TextEditorProxy_Create](#oh_texteditorproxy_create)创建。
 *
 * @param proxy 输入指针，指向即将被设置的{@link InputMethod_TextEditorProxy}实例的指针。不可为NULL，若传入NULL将返回
 * IME_ERR_NULL_POINTER。
 * @param getTextConfigFunc 输入参数，表示被设置到proxy的回调函数{@link OH_TextEditorProxy_GetTextConfigFunc}。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，proxy或getTextConfigFunc为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetGetTextConfigFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetTextConfigFunc getTextConfigFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_InsertTextFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前
 * 完成。
 *     <br>
 *     <br>使用场景：当应用需要注册InsertTextFunc回调以响应输入法插入文本请求时调用此函数。
 *     <br>
 *     <br>使用后效果：设置成功后，InsertTextFunc回调将被注册到TextEditorProxy中，Attach后当输入法请求插入文本时将自动触发此回
 * 调。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param insertTextFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetInsertTextFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_InsertTextFunc insertTextFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_DeleteForwardFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach
 * 之前完成。
 *     <br>
 *     <br>使用场景：当应用需要注册DeleteForwardFunc回调以响应输入法删除光标右侧文本请求时调用此函数。
 *     <br>
 *     <br>使用后效果：设置成功后，DeleteForwardFunc回调将被注册到TextEditorProxy中，Attach后当输入法请求删除光标右侧文本时将自
 * 动触发此回调。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param deleteForwardFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetDeleteForwardFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_DeleteForwardFunc deleteForwardFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_DeleteBackwardFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach
 * 之前完成。
 *     <br>
 *     <br>使用场景：当应用需要注册DeleteBackwardFunc回调以响应输入法删除光标左侧文本请求时调用此函数。
 *     <br>
 *     <br>使用后效果：设置成功后，DeleteBackwardFunc回调将被注册到TextEditorProxy中，Attach后当输入法请求删除光标左侧文本时将
 * 自动触发此回调。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param deleteBackwardFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetDeleteBackwardFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_DeleteBackwardFunc deleteBackwardFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_SendKeyboardStatusFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在
 * Attach之前完成。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param sendKeyboardStatusFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetSendKeyboardStatusFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_SendKeyboardStatusFunc sendKeyboardStatusFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_SendEnterKeyFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之
 * 前完成。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param sendEnterKeyFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetSendEnterKeyFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_SendEnterKeyFunc sendEnterKeyFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_MoveCursorFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前
 * 完成。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param moveCursorFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetMoveCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_MoveCursorFunc moveCursorFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_HandleSetSelectionFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在
 * Attach之前完成。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param handleSetSelectionFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetHandleSetSelectionFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_HandleSetSelectionFunc handleSetSelectionFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_HandleExtendActionFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在
 * Attach之前完成。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param handleExtendActionFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetHandleExtendActionFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_HandleExtendActionFunc handleExtendActionFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_GetLeftTextOfCursorFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在
 * Attach之前完成。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param getLeftTextOfCursorFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetGetLeftTextOfCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetLeftTextOfCursorFunc getLeftTextOfCursorFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_GetRightTextOfCursorFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在
 * Attach之前完成。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param getRightTextOfCursorFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetGetRightTextOfCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetRightTextOfCursorFunc getRightTextOfCursorFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_GetTextIndexAtCursorFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在
 * Attach之前完成。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param getTextIndexAtCursorFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetGetTextIndexAtCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetTextIndexAtCursorFunc getTextIndexAtCursorFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_ReceivePrivateCommandFunc}设置到{@link InputMethod_TextEditorProxy}中。
 * 此设置须在Attach之前完成。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param receivePrivateCommandFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetReceivePrivateCommandFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_ReceivePrivateCommandFunc receivePrivateCommandFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_SetPreviewTextFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach
 * 之前完成。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param setPreviewTextFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetSetPreviewTextFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_SetPreviewTextFunc setPreviewTextFunc);
/**
 * @brief 将函数{@link OH_TextEditorProxy_FinishTextPreviewFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在
 * Attach之前完成。
 *
 * @param proxy 输入指针，指向即将被设置的TextEditorProxy实例的指针。不可为NULL。
 * @param finishTextPreviewFunc 输入参数，表示被设置到proxy的回调函数。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetFinishTextPreviewFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_FinishTextPreviewFunc finishTextPreviewFunc);

/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_GetTextConfigFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param getTextConfigFunc 输出指针，表示从proxy获取到的函数指针。由调用者分配内存，函数将把回调函数指针写入此地址。不可为
 * NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，proxy或getTextConfigFunc为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetGetTextConfigFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetTextConfigFunc *getTextConfigFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_InsertTextFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param insertTextFunc 输出指针，表示从proxy获取到的函数指针。由调用者分配内存。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetInsertTextFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_InsertTextFunc *insertTextFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_DeleteForwardFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param deleteForwardFunc 输出指针，表示从proxy获取到的函数指针。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetDeleteForwardFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_DeleteForwardFunc *deleteForwardFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_DeleteBackwardFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param deleteBackwardFunc 输出指针，表示从proxy获取到的函数指针。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetDeleteBackwardFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_DeleteBackwardFunc *deleteBackwardFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_SendKeyboardStatusFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param sendKeyboardStatusFunc 输出指针，表示从proxy获取到的函数指针。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetSendKeyboardStatusFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_SendKeyboardStatusFunc *sendKeyboardStatusFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_SendEnterKeyFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param sendEnterKeyFunc 输出指针，表示从proxy获取到的函数指针。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetSendEnterKeyFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_SendEnterKeyFunc *sendEnterKeyFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_MoveCursorFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param moveCursorFunc 输出指针，表示从proxy获取到的函数指针。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetMoveCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_MoveCursorFunc *moveCursorFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_HandleSetSelectionFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param handleSetSelectionFunc 输出指针，表示从proxy获取到的函数指针。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetHandleSetSelectionFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_HandleSetSelectionFunc *handleSetSelectionFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_HandleExtendActionFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param handleExtendActionFunc 输出指针，表示从proxy获取到的函数指针。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetHandleExtendActionFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_HandleExtendActionFunc *handleExtendActionFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_GetLeftTextOfCursorFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param getLeftTextOfCursorFunc 输出指针，表示从proxy获取到的函数指针。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetGetLeftTextOfCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetLeftTextOfCursorFunc *getLeftTextOfCursorFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_GetRightTextOfCursorFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param getRightTextOfCursorFunc 输出指针，表示从proxy获取到的函数指针。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetGetRightTextOfCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetRightTextOfCursorFunc *getRightTextOfCursorFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_GetTextIndexAtCursorFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param getTextIndexAtCursorFunc 输出指针，表示从proxy获取到的函数指针。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetGetTextIndexAtCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetTextIndexAtCursorFunc *getTextIndexAtCursorFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_ReceivePrivateCommandFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param receivePrivateCommandFunc 输出指针，表示从proxy获取到的函数指针。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetReceivePrivateCommandFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_ReceivePrivateCommandFunc *receivePrivateCommandFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_SetPreviewTextFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param setPreviewTextFunc 输出指针，表示从proxy获取到的函数指针。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetSetPreviewTextFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_SetPreviewTextFunc *setPreviewTextFunc);
/**
 * @brief 从{@link InputMethod_TextEditorProxy}中获取{@link OH_TextEditorProxy_FinishTextPreviewFunc}函数。
 *
 * @param proxy 输入指针，指向被读取的TextEditorProxy实例的指针。不可为NULL。
 * @param finishTextPreviewFunc 输出指针，表示从proxy获取到的函数指针。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetFinishTextPreviewFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_FinishTextPreviewFunc *finishTextPreviewFunc);

/**
 * @brief 为InputMethod_TextEditorProxy的回调函数配置执行线程（主线程/IPC线程）。本接口仅控制InputMethod_TextEditorProxy中除
 * {@link OH_TextEditorProxy_GetTextConfigFunc}之外的所有回调函数。{@link OH_TextEditorProxy_GetTextConfigFunc}的执行线程
 * 由调用{@link OH_InputMethodController_Attach}的线程决定，不受本接口影响。若需GetTextConfigFunc也在主线程执行，需确保Attach
 * 在主线程调用。
 *     <br>
 *     <br>使用场景：当应用需要避免多线程并发问题时，可将回调切换到主线程执行；当应用对回调响应速度要求较高时，可保持IPC线程执行。
 *     <br>
 *     <br>使用后效果：设置为true后，除GetTextConfigFunc外的所有回调将在主线程执行，避免多线程并发但需注意避免在回调内执行耗时操
 * 作；设置为false后，回调在IPC线程执行，响应更快但可能存在并发问题。
 *     <br>
 *     <br>前置条件：proxy须先通过[OH_TextEditorProxy_Create](#oh_texteditorproxy_create)创建。建议在Attach之前调用此接口配
 * 置线程策略。
 *
 * @param proxy 输入指针，指向目标InputMethod_TextEditorProxy实例的指针。不可为NULL，若传入NULL将返回IME_ERR_NULL_POINTER。
 * @param isCallbackInMainThread 输入参数，线程执行策略。取值范围：true或false。取值原则：true-回调函数切换至主线程执行（用于避
 * 免多线程并发问题），避免在回调内执行耗时操作防止主线程阻塞；false-回调函数在IPC线程执行（可能存在多线程并发情况），响应速度更
 * 快。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 配置成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 当proxy为NULL时返回。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 22
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetCallbackInMainThread(
    InputMethod_TextEditorProxy *proxy, bool isCallbackInMainThread);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_TEXT_EDITOR_PROXY_CAP_H
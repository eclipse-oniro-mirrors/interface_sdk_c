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
 * @file inputmethod_text_config_capi.h
 *
 * @brief 输入框配置信息的头文件，提供TextConfig实例的创建、销毁与属性读写方法。InputMethod_TextConfig承载编辑框的配置信息，
 * 包括输入类型、回车键类型、光标信息、避让信息、选区范围、窗口ID、占位文本等，在[OH_TextEditorProxy_GetTextConfigFunc]
 * (capi-inputmethod-text-editor-proxy-capi-h.md#oh_texteditorproxy_gettextconfigfunc)回调中使用，开发者需在回调内对config
 * 参数设置各配置项。
 *
 * @include <inputmethod/inputmethod_text_config_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_TEXT_CONFIG_CAPI_H
#define OHOS_INPUTMETHOD_TEXT_CONFIG_CAPI_H
#include <stdint.h>
#include <stddef.h>

#include "inputmethod_cursor_info_capi.h"
#include "inputmethod_text_avoid_info_capi.h"
#include "inputmethod_types_capi.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @brief 文本输入框的文本输入行为配置结构体，用于输入框向输入法框架传递核心输入规则，输入法框架根据配置执行相应输入行为。通过配置
 * 输入属性（如输入类型、文本格式等），能够满足不同场景下的输入需求，提升用户输入体验，适用于需要精细化控制输入行为的文本输入场景。
 * 该结构体为不透明类型（opaque type），调用者不可直接访问其内部成员，仅可通过本模块提供的函数接口进行操作。
 *     <br>
 *     <br>结构体用途:
 *     <br>InputMethod_TextConfig承载编辑框的配置信息，包括输入类型、回车键类型、预上屏支持、选区范围、光标信息、避让信息、窗口
 * ID、占位符文本、abilityName等。该配置信息在[OH_TextEditorProxy_GetTextConfigFunc]
 * (capi-inputmethod-text-editor-proxy-capi-h.md#oh_texteditorproxy_gettextconfigfunc)回调中使用，开发者需在回调内对config
 * 参数设置各配置项，输入法框架据此调整键盘布局和输入行为。
 *     <br>
 *     <br>包含关系:
 *     <br>InputMethod_TextConfig内部包含以下子结构体信息：
 *     <br>- [InputMethod_CursorInfo](capi-inputmethod-inputmethod-cursorinfo.md)：光标信息，包括光标位置、高度等。可通过
 * [OH_TextConfig_GetCursorInfo](capi-inputmethod-text-config-capi-h.md#oh_textconfig_getcursorinfo)获取，返回双指针（函
 * 数内部分配内存）。
 *     <br>- [InputMethod_TextAvoidInfo](capi-inputmethod-inputmethod-textavoidinfo.md)：避让信息，包括避让区域的位置和尺
 * 寸。可通过[OH_TextConfig_GetTextAvoidInfo](capi-inputmethod-text-config-capi-h.md#oh_textconfig_gettextavoidinfo)获
 * 取，返回双指针（函数内部分配内存）。
 *     <br>
 *     <br>相关函数：
 *     <br>
 *     <br>- 创建/销毁函数：
 *     <br>| 函数 | 描述 |
 *     <br>| -- | -- |
 *     <br>| [OH_TextConfig_Create](capi-inputmethod-text-config-capi-h.md#oh_textconfig_create) | 创建一个新的
 * InputMethod_TextConfig实例。 |
 *     <br>| [OH_TextConfig_Destroy](capi-inputmethod-text-config-capi-h.md#oh_textconfig_destroy) | 销毁一个
 * InputMethod_TextConfig实例。 |
 *     <br>
 *     <br>- 设置函数（Set*）：
 *     <br>| 函数 | 描述 |
 *     <br>| -- | -- |
 *     <br>| [OH_TextConfig_SetInputType](capi-inputmethod-text-config-capi-h.md#oh_textconfig_setinputtype) | 设置文本
 * 配置信息中的输入框类型。 |
 *     <br>| [OH_TextConfig_SetEnterKeyType](capi-inputmethod-text-config-capi-h.md#oh_textconfig_setenterkeytype) | 设
 * 置文本配置信息中的回车键功能类型。 |
 *     <br>| [OH_TextConfig_SetPreviewTextSupport](capi-inputmethod-text-config-capi-h.
 * md#oh_textconfig_setpreviewtextsupport) | 设置预上屏支持情况。 |
 *     <br>| [OH_TextConfig_SetSelection](capi-inputmethod-text-config-capi-h.md#oh_textconfig_setselection) | 设置选中
 * 文本范围。 |
 *     <br>| [OH_TextConfig_SetWindowId](capi-inputmethod-text-config-capi-h.md#oh_textconfig_setwindowid) | 设置所属窗口
 * 的窗口ID。 |
 *     <br>| [OH_TextConfig_SetPlaceholder](capi-inputmethod-text-config-capi-h.md#oh_textconfig_setplaceholder) | 设置
 * 占位符文本信息。 |
 *     <br>| [OH_TextConfig_SetAbilityName](capi-inputmethod-text-config-capi-h.md#oh_textconfig_setabilityname) | 设置
 * abilityName信息。 |
 *     <br>| [OH_TextConfig_SetConsumeKeyEvents](capi-inputmethod-text-config-capi-h.
 * md#oh_textconfig_setconsumekeyevents) | 将编辑框是否具有完整处理字母、字符、功能等按键的能力设
 * 置到文本配置信息中。<br/>**起始版本：** 26.0.0 |
 *     <br>
 *     <br>- 获取函数（Get*）：
 *     <br>| 函数 | 描述 |
 *     <br>| -- | -- |
 *     <br>| [OH_TextConfig_GetInputType](capi-inputmethod-text-config-capi-h.md#oh_textconfig_getinputtype) | 获取输入
 * 框类型。 |
 *     <br>| [OH_TextConfig_GetEnterKeyType](capi-inputmethod-text-config-capi-h.md#oh_textconfig_getenterkeytype) | 获
 * 取回车键功能类型。 |
 *     <br>| [OH_TextConfig_IsPreviewTextSupported](capi-inputmethod-text-config-capi-h.
 * md#oh_textconfig_ispreviewtextsupported) | 获取是否支持预上屏。 |
 *     <br>| [OH_TextConfig_GetCursorInfo](capi-inputmethod-text-config-capi-h.md#oh_textconfig_getcursorinfo) | 获取光
 * 标信息（双指针，函数内部分配内存）。 |
 *     <br>| [OH_TextConfig_GetTextAvoidInfo](capi-inputmethod-text-config-capi-h.md#oh_textconfig_gettextavoidinfo) |
 *  获取避让信息（双指针，函数内部分配内存）。 |
 *     <br>| [OH_TextConfig_GetSelection](capi-inputmethod-text-config-capi-h.md#oh_textconfig_getselection) | 获取选区
 * 范围信息。 |
 *     <br>| [OH_TextConfig_GetWindowId](capi-inputmethod-text-config-capi-h.md#oh_textconfig_getwindowid) | 获取所属窗口
 * 的窗口ID。 |
 *     <br>| [OH_TextConfig_GetPlaceholder](capi-inputmethod-text-config-capi-h.md#oh_textconfig_getplaceholder) | 获取
 * 占位符文本信息。 |
 *     <br>| [OH_TextConfig_GetAbilityName](capi-inputmethod-text-config-capi-h.md#oh_textconfig_getabilityname) | 获取
 * abilityName信息。 |
 *     <br>| [OH_TextConfig_GetConsumeKeyEvents](capi-inputmethod-text-config-capi-h.
 * md#oh_textconfig_getconsumekeyevents) | 获取文本配置中编辑框是否具有完整处理字母、字符、功能等按键的能力。<br/>**起始版本：** 26.0.0 |
 *
 * @since 12
 */
typedef struct InputMethod_TextConfig InputMethod_TextConfig;

/**
 * @brief 创建一个新的{@link InputMethod_TextConfig}实例。主要用于在[OH_TextEditorProxy_GetTextConfigFunc]
 * (capi-inputmethod-text-editor-proxy-capi-h.md#oh_texteditorproxy_gettextconfigfunc)回调中对config参数进行设置操作。
 *     <br>
 *     <br>使用场景：当开发者需要在GetTextConfigFunc回调外部预先创建TextConfig对象以准备配置信息时调用此函数。通常config参数由
 * 回调框架提供，开发者直接在回调内设置即可，无需自行创建。
 *     <br>
 *     <br>使用后效果：创建成功后返回一个新的TextConfig实例指针，后续可通过Set*接口设置配置属性。
 *     <br>
 *     <br>生命周期管理：返回的对象必须通过[OH_TextConfig_Destroy](#oh_textconfig_destroy)销毁。Create与Destroy必须配对使
 * 用，同一个实例只能被销毁一次，未销毁会导致内存泄漏。
 *     <br>
 *     <br> > **说明：**
 *     <br> >
 *     <br> > 由[OH_TextEditorProxy_GetTextConfigFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_gettextconfigfunc)回调框架提供的config参数的内存由框架管理，回调返回后自动释放，不可调用Destroy销毁，
 * 仅由OH_TextConfig_Create创建的对象需要自行销毁。
 *
 * @return 如果创建成功，返回一个指向新创建的{@link InputMethod_TextConfig}实例的指针。如果创建失败，返回NULL，可能的失败原因有
 * 内存不足。返回的指针在使用完毕后必须通过
 *     {@link OH_TextConfig_Destroy}销毁，销毁后指针应设置为NULL避免误用。
 * @since 12
 */
InputMethod_TextConfig *OH_TextConfig_Create(void);
/**
 * @brief 销毁一个{@link InputMethod_TextConfig}实例。销毁后config指针不可再使用，建议将指针设置为NULL避免误用。
 *     <br>
 *     <br>使用场景：当应用不再需要TextConfig对象时调用此函数释放资源。
 *     <br>
 *     <br>使用后效果：config对象将被释放，其内部资源被回收，此后不可再通过config指针调用任何函数。
 *     <br>
 *     <br>生命周期管理：与[OH_TextConfig_Create](#oh_textconfig_create)配对使用。同一个实例只能被销毁一次，不可重复销毁。若
 * config为NULL，函数不做任何处理。
 *
 * @param config 输入指针，表示指向即将被销毁的{@link InputMethod_TextConfig}实例的指针。若传入NULL，函数不做任何处理，不会导
 * 致崩溃。销毁后该指针失效，建议设置为NULL。注意：由GetTextConfigFunc回调框架提供的config参数的内存由框架管理，回调返回后自动释
 * 放，不可在回调外部调用Destroy销毁。
 * @since 12
 */
void OH_TextConfig_Destroy(InputMethod_TextConfig *config);

/**
 * @brief 设置文本配置信息中的输入框类型。输入法框架将根据此类型调整键盘布局。
 *     <br>
 *     <br>使用场景：在GetTextConfigFunc回调内设置编辑框的输入类型，或在创建TextConfig后预先设置输入类型。
 *     <br>
 *     <br>使用后效果：设置成功后，输入法框架将据此切换对应的键盘布局（如文本键盘、数字键盘等）。
 *     <br>
 *     <br>前置条件：config须为有效的InputMethod_TextConfig实例指针。
 *
 * @param config 输入指针，指向即将被设置值的{@link InputMethod_TextConfig}实例的指针。不可为NULL，若传入NULL将返回
 * IME_ERR_NULL_POINTER。
 * @param inputType 输入参数，输入框的输入类型。取值范围：{@link InputMethod_TextInputType}枚举值，如
 * IME_TEXT_INPUT_TYPE_TEXT、IME_TEXT_INPUT_TYPE_NUMBER、IME_TEXT_INPUT_TYPE_PHONE等。使用后效果：不同类型将触发输入法切换到
 * 不同的键盘布局。
 * @return 返回一个特定的错误码。
 *     <br>IME_ERR_OK = 0：表示成功。
 *     <br>IME_ERR_NULL_POINTER = 12802000：非预期的空指针，config为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_SetInputType(InputMethod_TextConfig *config, InputMethod_TextInputType inputType);
/**
 * @brief 设置文本配置信息中的回车键功能类型。输入法框架将据此调整回车键的显示标签和功能。
 *     <br>
 *     <br>使用场景：在GetTextConfigFunc回调内设置编辑框的回车键类型。
 *     <br>
 *     <br>使用后效果：设置成功后，输入法键盘上的回车键将显示对应的标签（如"搜索"、"完成"等）并执行对应功能。
 *
 * @param config 输入指针，指向即将被设置值的TextConfig实例的指针。不可为NULL。
 * @param enterKeyType 输入参数，回车键功能类型。取值范围：{@link InputMethod_EnterKeyType}枚举值。使用后效果：不同类型对应不
 * 同的回车键行为和显示标签。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_SetEnterKeyType(
    InputMethod_TextConfig *config, InputMethod_EnterKeyType enterKeyType);
/**
 * @brief 将预上屏支持情况设置到文本配置信息中。预上屏是输入法的候选文本展示功能，设置supported为true后输入法将启用预上屏功能。
 *     <br>
 *     <br>使用场景：在GetTextConfigFunc回调内设置编辑框是否支持预上屏功能。
 *     <br>
 *     <br>使用后效果：设置为true后，输入法将启用预上屏功能，通过SetPreviewTextFunc回调向编辑框发送预上屏文本；设置为false后，输
 * 入法不使用预上屏功能。
 *
 * @param config 输入指针，指向即将被设置值的TextConfig实例的指针。不可为NULL。
 * @param supported 输入参数，表示输入框是否支持预上屏。取值范围：true或false。true表示支持预上屏，输入法将使用
 * SetPreviewTextFunc回调；false表示不支持预上屏。此参数为必需参数，
 *     必须设置。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_SetPreviewTextSupport(InputMethod_TextConfig *config, bool supported);
/**
 * @brief 设置文本配置信息中的选中文本范围。用于告知输入法当前编辑框的文本选区状态。
 *     <br>
 *     <br>使用场景：在GetTextConfigFunc回调内设置当前编辑框的选区范围。
 *     <br>
 *     <br>使用后效果：设置成功后，输入法将据此感知编辑框的选中状态。
 *
 * @param config 输入指针，指向即将被设置值的TextConfig实例的指针。不可为NULL。
 * @param start 输入参数，所选文本的起始位置（单位：字符偏移量，从0开始计数）。取值原则：start应大于等于0且小于等于end。
 * @param end 输入参数，所选文本的结束位置（单位：字符偏移量，从0开始计数）。取值原则：end应大于等于start且小于等于文本总长度。无
 * 选中文本时start与end相等表示光标位置。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_SetSelection(InputMethod_TextConfig *config, int32_t start, int32_t end);
/**
 * @brief 设置文本配置信息中所属窗口的窗口id。用于标识编辑框所属的应用窗口，输入法据此确定避让区域和候选词窗口定位。
 *     <br>
 *     <br>使用场景：在GetTextConfigFunc回调内设置编辑框所属窗口的窗口ID。
 *     <br>
 *     <br>使用后效果：设置成功后，输入法将据此确定候选词窗口的定位和避让策略。
 *
 * @param config 输入指针，指向即将被设置值的TextConfig实例的指针。不可为NULL。
 * @param windowId 输入参数，绑定输入法的应用所属窗口的窗口id。此参数为必需参数，必须设置。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_SetWindowId(InputMethod_TextConfig *config, int32_t windowId);

/**
 * @brief 设置文本配置信息中的占位符文本信息。占位符文本是编辑框中当无用户输入时显示的提示文本，输入法据此感知编辑框的提示内容。
 *     <br>
 *     <br>使用场景：在GetTextConfigFunc回调内设置编辑框的占位符提示文本。
 *     <br>
 *     <br>使用后效果：设置成功后，输入法将据此感知编辑框的占位提示内容，可用于上下文分析。
 *
 * @param config 输入指针，指向即将被设置值的TextConfig实例的指针。不可为NULL，若传入NULL将返回IME_ERR_NULL_POINTER。
 * @param placeholder 输入指针，指向UTF-16编码的双字节字符串。若传NULL指针，则会将占位文本信息设置为空字符串。函数仅读取该数据，
 * 不会修改或释放。
 * @param length 输入参数，placeholder指针指向的UTF-16字符个数（不包含结尾符）。取值范围：0到255。1. 如果长度为0，占位文本信息
 * 会被设置为空字符串。2. UTF-16编码的最大长度为255个字符（
 *     不包含结尾符），超过255个字符会被截断。
 * @return {@link InputMethod_ErrorCode}：IME_ERR_OK = 0：表示成功。IME_ERR_NULL_POINTER = 12802000：非预期的空指针，
 * config为NULL。
 * @since 20
 */
InputMethod_ErrorCode OH_TextConfig_SetPlaceholder(InputMethod_TextConfig *config, const char16_t *placeholder,
    size_t length);

/**
 * @brief 设置文本配置信息中的abilityName信息。abilityName用于标识编辑框所属的Ability，输入法据此感知编辑框的业务场景。
 *     <br>
 *     <br>使用场景：在GetTextConfigFunc回调内设置编辑框所属Ability的名称。
 *     <br>
 *     <br>使用后效果：设置成功后，输入法将据此感知编辑框的业务场景。
 *
 * @param config 输入指针，指向即将被设置值的TextConfig实例的指针。不可为NULL。
 * @param abilityName 输入指针，指向UTF-16编码的双字节字符串。若传NULL指针，则会将abilityName设置为空字符串。函数仅读取该数据。
 * @param length 输入参数，abilityName指针指向的UTF-16字符个数（不包含结尾符）。取值范围：0到127。1. 如果长度为0，abilityName
 * 会被设置为空字符串。2. UTF-16编码的最大长度为127个字符（不包含结尾符），超过127个字符会被截断。
 * @return {@link InputMethod_ErrorCode}：IME_ERR_OK = 0：表示成功。IME_ERR_NULL_POINTER = 12802000：非预期的空指针，
 * config为NULL。
 * @since 20
 */
InputMethod_ErrorCode OH_TextConfig_SetAbilityName(InputMethod_TextConfig *config, const char16_t *abilityName,
    size_t length);

/**
 * @brief 将编辑框是否具有完整处理字母、字符、功能等按键的能力设置到文本配置信息中。当设置为true时，表示编辑框具备完整处理按键事件
 * 的能力，输入法框架将跳过对这些按键的处理；当设置为false时，表示编辑框不具备此能力，按键事件将由输入法框架自行处理。
 *     <br>
 *     <br>使用场景：在GetTextConfigFunc回调内设置编辑框是否具有按键事件处理能力。当编辑框已实现完整的按键处理逻辑（如自行处理字
 * 母键、字符键、功能键等）时，应设置为true；否则应设置为false。
 *     <br>
 *     <br>使用后效果：设置为true后，输入法框架将跳过对字母、字符、功能等按键的处理，由编辑框自行消费这些按键事件；设置为false
 * 后，输入法框架将自行处理这些按键事件，编辑框不再消费。
 *     <br>
 *     <br>前置条件：config须为有效的InputMethod_TextConfig实例指针。
 *
 * @param config 输入指针，指向即将被设置值的{@link InputMethod_TextConfig}实例的指针。不可为NULL，若传入NULL将返回
 * IME_ERR_NULL_POINTER。
 * @param consumeKeyEvents 输入参数，表示编辑框是否具有完整处理字母、字符、功能等按键的能力。取值范围：true或false。true表示编
 * 辑框具备完整处理按键事件的能力，输入法框架将跳过对字母、字符、功能等按键的处理，由编辑框自行消费；false表示编辑框不具备此能力，
 * 按键事件将由输入法框架处理。此参数为必需参数，必须设置。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 26.0.0
 */
InputMethod_ErrorCode OH_TextConfig_SetConsumeKeyEvents(InputMethod_TextConfig *config, bool consumeKeyEvents);

/**
 * @brief 获取文本配置信息中的输入框类型。
 *     <br>
 *     <br>使用场景：当需要读取已设置的输入框类型时调用此函数。
 *
 * @param config 输入指针，指向即将被获取值的TextConfig实例的指针。不可为NULL。
 * @param inputType 输出指针，表示指向{@link InputMethod_TextInputType}变量的指针。由调用者分配内存，函数将把输入类型值写入此
 * 地址。不可为NULL。取值范围：{@link InputMethod_TextInputType}枚举值。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config或inputType为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetInputType(InputMethod_TextConfig *config, InputMethod_TextInputType *inputType);
/**
 * @brief 获取文本配置信息中的回车键功能类型。
 *     <br>
 *     <br>使用场景：当需要读取已设置的回车键类型时调用此函数。
 *
 * @param config 输入指针，指向即将被获取值的TextConfig实例的指针。不可为NULL。
 * @param enterKeyType 输出指针，表示指向{@link InputMethod_EnterKeyType}变量的指针。由调用者分配内存。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config或enterKeyType为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetEnterKeyType(
    InputMethod_TextConfig *config, InputMethod_EnterKeyType *enterKeyType);
/**
 * @brief 获取文本配置中是否支持预上屏。
 *     <br>
 *     <br>使用场景：当需要读取已设置的预上屏支持状态时调用此函数。
 *
 * @param config 输入指针，指向即将被获取值的TextConfig实例的指针。不可为NULL。
 * @param supported 输出指针，用于返回是否支持预上屏。由调用者分配内存。不可为NULL。取值范围：true表示支持预上屏，false表示不支
 * 持预上屏。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config或supported为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_IsPreviewTextSupported(InputMethod_TextConfig *config, bool *supported);
/**
 * @brief 获取文本配置信息中的光标信息。此接口使用双指针参数，函数内部分配内存返回CursorInfo对象。
 *     <br>
 *     <br>使用场景：当需要读取已设置的光标信息时调用此函数。
 *     <br>
 *     <br>使用后效果：调用成功后，cursorInfo指向由函数内部分配的CursorInfo对象，包含光标位置和高度等信息。
 *
 * @param config 输入指针，指向即将被获取值的TextConfig实例的指针。不可为NULL。
 * @param cursorInfo 输出双指针，用于返回光标信息对象。函数内部分配内存创建{@link InputMethod_CursorInfo}实例，并通过此双指针
 * 返回。不可为NULL。返回的对象必须在使用完毕后调用{@link OH_CursorInfo_Destroy}释放，不可使用free直接释放，否则会造成内存泄
 * 漏。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config或cursorInfo为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetCursorInfo(InputMethod_TextConfig *config, InputMethod_CursorInfo **cursorInfo);

/**
 * @brief 获取文本配置信息中的避让信息。此接口使用双指针参数，函数内部分配内存返回TextAvoidInfo对象。
 *     <br>
 *     <br> 使用场景：当需要读取已设置的避让信息时调用此函数。
 *     <br>
 *     <br> 使用后效果：调用成功后，avoidInfo指向由函数内部分配的TextAvoidInfo对象，包含避让区域的位置和尺寸等信息。
 *     <br>
 *     <br> 内存管理：avoidInfo为双指针（输出指针），函数内部分配内存创建[InputMethod_TextAvoidInfo]
 * (capi-inputmethod-inputmethod-textavoidinfo.md)对象并通过此参数返回。
 * 返回的TextAvoidInfo对象必须在使用完毕后调用[OH_TextAvoidInfo_Destroy](capi-inputmethod-text-avoid-info-capi-h.
 * md#oh_textavoidinfo_destroy)释放，否则会造成内存泄漏。不可使用free直接释放。
 *
 * @param config 输入指针，表示文本配置信息。不可为NULL。
 * @param avoidInfo 输出双指针，用于返回输入框避让信息对象。函数内部分配内存创建{@link InputMethod_TextAvoidInfo}实例，并通过
 * 此双指针返回。不可为NULL。返回的对象必须在使用完毕后调用{@link OH_TextAvoidInfo_Destroy}释放，不可使用free直接释放，否则会造
 * 成内存泄漏。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config或avoidInfo为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetTextAvoidInfo(
    InputMethod_TextConfig *config, InputMethod_TextAvoidInfo **avoidInfo);

/**
 * @brief 获取文本配置信息中的选区范围信息。
 *     <br>
 *     <br>使用场景：当需要读取已设置的选区范围时调用此函数。
 *
 * @param config 输入指针，指向即将被获取值的TextConfig实例的指针。不可为NULL。
 * @param start 输出指针，所选文本的起始位置（单位：字符偏移量）。由调用者分配内存。不可为NULL。
 * @param end 输出指针，所选文本的结束位置（单位：字符偏移量）。由调用者分配内存。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config、start或end为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetSelection(InputMethod_TextConfig *config, int32_t *start, int32_t *end);
/**
 * @brief 获取文本配置信息中所属窗口的窗口id。
 *     <br>
 *     <br>使用场景：当需要读取已设置的窗口ID时调用此函数。
 *
 * @param config 输入指针，指向即将被获取值的TextConfig实例的指针。不可为NULL。
 * @param windowId 输出指针，绑定输入法的应用所属窗口的窗口id。由调用者分配内存。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config或windowId为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetWindowId(InputMethod_TextConfig *config, int32_t *windowId);

/**
 * @brief 获取文本配置信息中的占位符文本信息。此接口采用两步调用策略：第一次调用时以NULL作为placeholder参数，length将返回实际占
 * 位文本长度；根据返回的长度分配足够内存后第二次调用获取完整内容。
 *     <br>
 *     <br>使用场景：当需要读取已设置的占位符文本时调用此函数。
 *     <br>
 *     <br>使用后效果：调用成功后，placeholder中将包含完整的占位文本内容，length返回实际长度。
 *
 * @param config 输入指针，指向即将被获取值的TextConfig实例的指针。不可为NULL。
 * @param placeholder 输出指针，用于存放占位文本信息，该指针内存由调用者分配和维护。采用两步调用策略：第一次可传NULL获取实际长
 * 度；第二次传已分配的足够内存获取完整内容。最大支持255个UTF-16字符（不含结尾符），分配时建议预留length+1个元素空间以包含结尾
 * 符。
 * @param length 输入/输出指针，占位文本信息长度（单位：UTF-16字符个数，不包含结尾符）。作为入参时，表示placeholder指向的内存可
 * 用长度（最大支持255个字符）；作为出参时，表示实际的占位文本长度。
 *     不可为NULL。
 * @return {@link InputMethod_ErrorCode}：IME_ERR_OK = 0：表示成功。IME_ERR_PARAMCHECK = 401：参数检查失败，
 * 可能是placeholder为NULL或length不足，此时length会被设置为实际长度。IME_ERR_NULL_POINTER = 12802000：非预期的空指针，config
 * 或length为NULL。
 * @since 20
 */
InputMethod_ErrorCode OH_TextConfig_GetPlaceholder(InputMethod_TextConfig *config, char16_t *placeholder,
    size_t *length);

/**
 * @brief 获取文本配置信息中的abilityName信息。此接口采用两步调用策略：第一次调用时以NULL作为abilityName参数，length将返回实际
 * abilityName长度；根据返回的长度分配足够内存后第二次调用获取完整内容。
 *     <br>
 *     <br>使用场景：当需要读取已设置的abilityName时调用此函数。
 *     <br>
 *     <br>使用后效果：调用成功后，abilityName中将包含完整的abilityName内容，length返回实际长度。
 *
 * @param config 输入指针，指向即将被获取值的TextConfig实例的指针。不可为NULL。
 * @param abilityName 输出指针，用于存放abilityName，该指针内存由调用者分配和维护。采用两步调用策略：第一次可传NULL获取实际长
 * 度；第二次传已分配的足够内存获取完整内容。最大支持127个UTF-16字符（
 *     不含结尾符），分配时建议预留length+1个元素空间。
 * @param length 输入/输出指针，abilityName长度（单位：UTF-16字符个数，不包含结尾符）。作为入参时，表示abilityName指向的内存可
 * 用长度（最大支持127个字符）；作为出参时，
 *     表示实际的abilityName长度。不可为NULL。
 * @return {@link InputMethod_ErrorCode}：
 *     <br>IME_ERR_OK = 0：表示成功。
 *     <br>IME_ERR_PARAMCHECK = 401：参数检查失败。
 *     <br>IME_ERR_NULL_POINTER = 12802000：非预期的空指针。
 * @since 20
 */
InputMethod_ErrorCode OH_TextConfig_GetAbilityName(InputMethod_TextConfig *config, char16_t *abilityName,
    size_t *length);

/**
 * @brief 获取文本配置中编辑框是否具有完整处理字母、字符、功能等按键的能力。即读取通过
 * {@link OH_TextConfig_SetConsumeKeyEvents}设置的按键事件消费能力配置。
 *     <br>
 *     <br>使用场景：当需要读取已设置的按键事件处理能力配置时调用此函数，用于判断编辑框是否具备完整消费按键事件的能力。
 *     <br>
 *     <br>使用后效果：调用成功后，consumeKeyEvents将返回编辑框的按键事件处理能力状态。true表示编辑框具备完整处理按键事件的能
 * 力，输入法框架将跳过对字母、字符、功能等按键的处理；false表示编辑框不具备此能力，按键事件将由输入法框架处理。
 *
 * @param config 输入指针，指向即将被获取值的{@link InputMethod_TextConfig}实例的指针。不可为NULL，若传入NULL将返回
 * IME_ERR_NULL_POINTER。
 * @param consumeKeyEvents 输出指针，用于返回编辑框是否具有完整处理字母、字符、功能等按键的能力。由调用者分配内存。不可为NULL。
 * 取值范围：true表示编辑框具备完整处理按键事件的能力，输入法框架将跳过对字母、
 *     字符、功能等按键的处理；false表示编辑框不具备此能力，按键事件将由输入法框架处理。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config或consumeKeyEvents为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 26.0.0
 */
InputMethod_ErrorCode OH_TextConfig_GetConsumeKeyEvents(InputMethod_TextConfig *config, bool *consumeKeyEvents);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_TEXT_CONFIG_CAPI_H
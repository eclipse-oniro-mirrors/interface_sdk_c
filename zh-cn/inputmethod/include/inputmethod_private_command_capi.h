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
 * @file inputmethod_private_command_capi.h
 *
 * @brief 提供私有数据对象的创建、销毁与读写方法。InputMethod_PrivateCommand采用key-value机制，支持输入法应用与编辑框客户端之间
 * 传递自定义私有数据，用于扩展输入法功能、传递特定场景指令或交换自定义配置信息。
 *     <br>
 *     <br>该结构体的value支持三种数据类型：布尔值（bool）、整数（int32_t）和字符串（string），但同一个PrivateCommand实例只能设
 * 置一种类型的value。设置value时会覆盖之前已设置的value及其类型。获取value时，建议先通过OH_PrivateCommand_GetValueType判断当
 * 前value的数据类型，再调用对应的GetValue函数获取实际值，否则当请求的类型与实际存储类型不匹配时将返回IME_ERR_QUERY_FAILED。
 *     <br>
 *     <br>该结构体主要在两种场景中使用：输入法应用通过OH_InputMethodProxy_SendPrivateCommand向编辑框客户端发送私有指令；编辑框
 * 客户端通过OH_TextEditorProxy_ReceivePrivateCommandFunc回调接收来自输入法应用的私有指令。单次发送的所有私有数据与key值的大小
 * 总和限制为32KB，最多可发送5个PrivateCommand实例。
 *
 * @include <inputmethod/inputmethod_private_command_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_PRIVATE_COMMAND_CAPI_H
#define OHOS_INPUTMETHOD_PRIVATE_COMMAND_CAPI_H
#include <stddef.h>
#include <stdint.h>

#include "inputmethod_types_capi.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @brief 私有命令结构体，采用key-value机制，作为输入框与输入法应用之间传递私有数据的载体。可用于传递自定义指令、扩展能力参数和特
 * 定场景数据，提升输入法功能的扩展性和兼容性。每个PrivateCommand实例包含一个key（标识符字符串）和一个value（布尔值、整数或字符
 * 串，三种类型只能选择一种），value的数据类型由InputMethod_CommandValueType标识。
 *     <br>
 *     <br>私有命令结构体，采用key-value机制，作为输入框与输入法应用之间传递私有数据的载体。可用于传递自定义指令、扩展能力参数和
 * 特定场景数据，提升输入法功能的扩展性和兼容性。每个PrivateCommand实例包含一个key（标识符字符串）和一个value（布尔值、整数或字符
 * 串，三种类型只能选择一种），value的数据类型由InputMethod_CommandValueType标识。
 *     <br>
 *     <br>用途：在输入法应用与编辑框客户端之间传递私有数据，实现双方的自定义通信。输入法应用通过
 * OH_InputMethodProxy_SendPrivateCommand向编辑框客户端发送私有指令；编辑框客户端通过
 * OH_TextEditorProxy_ReceivePrivateCommandFunc回调接收来自输入法应用的私有指令。每个PrivateCommand实例携带一条key-value私有
 * 数据，最多可同时发送5个实例，单次发送的所有私有数据与key值的大小总和限制为32KB。
 *     <br>
 *     <br>使用场景：
 *     <br>- 输入法应用向编辑框发送私有指令：输入法应用创建PrivateCommand实例，设置key和value后，通过
 * [OH_InputMethodProxy_SendPrivateCommand](capi-inputmethod-inputmethod-proxy-capi-h.
 * md#oh_inputmethodproxy_sendprivatecommand)发送给编辑框客户端。
 *     <br>- 编辑框客户端接收私有指令：编辑框客户端在[OH_TextEditorProxy_ReceivePrivateCommandFunc]
 * (capi-inputmethod-text-editor-proxy-capi-h.md#oh_texteditorproxy_receiveprivatecommandfunc)回调中接收PrivateCommand实
 * 例数组，遍历数组解析每个实例的key和value。
 *     <br>
 *     <br>相关函数：
 *     <br>| 函数 | 说明 |
 *     <br>| --- | --- |
 *     <br>| [OH_PrivateCommand_Create](capi-inputmethod-private-command-capi-h.md#oh_privatecommand_create) | 创建
 * InputMethod_PrivateCommand实例。|
 *     <br>| [OH_PrivateCommand_Destroy](capi-inputmethod-private-command-capi-h.md#oh_privatecommand_destroy) | 销毁
 * InputMethod_PrivateCommand实例。 |
 *     <br>| [OH_PrivateCommand_SetKey](capi-inputmethod-private-command-capi-h.md#oh_privatecommand_setkey) | 设置key
 * 值。 |
 *     <br>| [OH_PrivateCommand_SetBoolValue](capi-inputmethod-private-command-capi-h.
 * md#oh_privatecommand_setboolvalue) | 设置布尔类型value值。 |
 *     <br>| [OH_PrivateCommand_SetIntValue](capi-inputmethod-private-command-capi-h.
 * md#oh_privatecommand_setintvalue) | 设置整数类型value值。 |
 *     <br>| [OH_PrivateCommand_SetStrValue](capi-inputmethod-private-command-capi-h.
 * md#oh_privatecommand_setstrvalue) | 设置字符串类型value值。 |
 *     <br>| [OH_PrivateCommand_GetKey](capi-inputmethod-private-command-capi-h.md#oh_privatecommand_getkey) | 获取key
 * 值。 |
 *     <br>| [OH_PrivateCommand_GetValueType](capi-inputmethod-private-command-capi-h.
 * md#oh_privatecommand_getvaluetype) | 获取value的数据类型。 |
 *     <br>| [OH_PrivateCommand_GetBoolValue](capi-inputmethod-private-command-capi-h.
 * md#oh_privatecommand_getboolvalue) | 获取布尔类型value值。 |
 *     <br>| [OH_PrivateCommand_GetIntValue](capi-inputmethod-private-command-capi-h.
 * md#oh_privatecommand_getintvalue) | 获取整数类型value值。 |
 *     <br>| [OH_PrivateCommand_GetStrValue](capi-inputmethod-private-command-capi-h.
 * md#oh_privatecommand_getstrvalue) | 获取字符串类型value值。 |
 *     <br>
 *     <br>相关接口：
 *     <br>| 接口 | 说明 |
 *     <br>| --- | --- |
 *     <br>| [OH_InputMethodProxy_SendPrivateCommand](capi-inputmethod-inputmethod-proxy-capi-h.
 * md#oh_inputmethodproxy_sendprivatecommand) | 输入法应用向编辑框客户端发送私有指令，PrivateCommand实例数组作为参数传入。最
 * 多5个实例，数据总大小限制32KB。 |
 *     <br>| [OH_TextEditorProxy_ReceivePrivateCommandFunc](capi-inputmethod-text-editor-proxy-capi-h.
 * md#oh_texteditorproxy_receiveprivatecommandfunc) | 编辑框客户端接收私有指令的回调函数，PrivateCommand实例数组作为参数传
 * 入。回调返回后实例内存被释放。 |
 *     <br>
 *     <br>相关枚举：
 *     <br>| 枚举 | 说明 |
 *     <br>| --- | --- |
 *     <br>| [InputMethod_CommandValueType](capi-inputmethod-types-capi-h.md#
 * inputmethod_commandvaluetype) | PrivateCommand中value的数据类型枚举（NONE/STRING/BOOL/INT32）。 |
 *
 * @since 12
 */
typedef struct InputMethod_PrivateCommand InputMethod_PrivateCommand;

/**
 * @brief 创建一个新的{@link InputMethod_PrivateCommand}实例。创建时需指定key值，key为私有命令的标识符，用于区分不同的私有数据
 * 项。创建后的实例value类型默认为IME_COMMAND_VALUE_TYPE_NONE，需后续通过SetBoolValue/SetIntValue/SetStrValue设置value值及其
 * 类型。
 *     <br>
 *     <br>使用场景：输入法应用需要向编辑框客户端传递私有数据时，首先调用此函数创建PrivateCommand实例，设置key和value后，通过
 * OH_InputMethodProxy_SendPrivateCommand发送。编辑框客户端在OH_TextEditorProxy_ReceivePrivateCommandFunc回调中接收到的
 * PrivateCommand实例也可使用本函数创建新的回复指令。
 *     <br>
 *     <br>前置条件：key参数必须为非NULL指针，keyLength必须大于0且不超过单次所有私有数据与key值的大小总和32KB的限制。
 *     <br>
 *     <br>使用后效果：成功调用后返回一个新创建的InputMethod_PrivateCommand实例指针，该实例的value类型初始为
 * IME_COMMAND_VALUE_TYPE_NONE。调用方需负责该实例的生命周期管理，在使用完毕后必须调用OH_PrivateCommand_Destroy销毁实例以释放
 * 内存。
 *
 * @param key 私有数据的key值，用于标识该私有命令的含义。key值为字符串形式，不允许传入NULL指针。单次发送的所有私有数据与key值的大
 * 小总和限制为32KB（包括所有PrivateCommand实例的key和value数据）。建议key值具有明确的语义标识，便于接收方解析。
 * @param keyLength key值的字节长度，不包括结尾空字符。必须大于0。单次所有私有数据与key值的大小限制32KB。若keyLength为0，创建行
 * 为未定义。
 * @return 如果创建成功，返回一个指向新创建的{@link InputMethod_PrivateCommand}实例的指针。调用方必须负责该实例的生命周期管理，
 * 使用完毕后调用{@link OH_PrivateCommand_Destroy}销毁实例以释放内存。
 *     <br>如果创建失败，返回NULL。可能的失败原因：内存分配不足（应用地址空间满）。对NULL指针的后续操作（如Set/Get函数）将返回
 * IME_ERR_NULL_POINTER。
 * @since 12
 */
InputMethod_PrivateCommand *OH_PrivateCommand_Create(char key[], size_t keyLength);
/**
 * @brief 销毁一个{@link InputMethod_PrivateCommand}实例，释放其占用的内存资源，包括key值和value值（字符串类型value）所占用的
 * 内部内存。
 *     <br>
 *     <br>使用场景：当PrivateCommand实例不再使用时，调用此函数销毁实例。必须在Create函数成功返回后、且实例不再被任何其他对象引
 * 用时调用。特别注意：通过OH_InputMethodProxy_SendPrivateCommand发送后，原始实例仍需由发送方自行销毁；通过
 * ReceivePrivateCommandFunc回调接收到的实例，其生命周期由回调调用期间管理，回调返回后该实例内存将被释放，不应再销毁或访问。
 *     <br>
 *     <br>生命周期管理：OH_PrivateCommand_Create和OH_PrivateCommand_Destroy必须配对使用，每个Create创建的实例必须有对应的
 * Destroy调用，否则会导致内存泄漏。调用Destroy后，原指针变为无效指针，不应再被使用。
 *     <br>
 *     <br>前置条件：command参数应为OH_PrivateCommand_Create成功返回的非NULL指针。
 *     <br>
 *     <br>使用后效果：command指向的内存被释放，包括内部存储的key字符串和value字符串的内存。command指针变为无效指针。对已销毁指
 * 针的任何后续访问均为未定义行为。
 *
 * @param command 指向即将被销毁的{@link InputMethod_PrivateCommand}实例的指针。若传入NULL，函数不执行任何操作，安全返回。建议
 * 销毁后将指针置为NULL以避免误用悬空指针。
 * @since 12
 */
void OH_PrivateCommand_Destroy(InputMethod_PrivateCommand *command);
/**
 * @brief 设置{@link InputMethod_PrivateCommand}的key值。key值为私有命令的标识符，用于接收方区分不同含义的私有数据。
 *     <br>
 *     <br>使用场景：当需要修改已有PrivateCommand实例的key值时调用此函数。通常在Create时已设置初始key值，若需要更新key可再次调
 * 用此函数。
 *     <br>
 *     <br>前置条件：command参数必须为OH_PrivateCommand_Create成功返回的非NULL指针；key参数必须为非NULL指针；keyLength必须大
 * 于0。
 *
 * @param command 指向即将被设置的{@link InputMethod_PrivateCommand}实例的指针。不允许传入NULL指针，否则返回
 * IME_ERR_NULL_POINTER。
 * @param key key值，用于标识私有命令的含义。不允许传入NULL指针，否则返回IME_ERR_NULL_POINTER。建议使用具有明确语义的字符串作为
 * key，便于接收方解析和处理。
 * @param keyLength key值的字节长度，不包括结尾空字符。必须大于0。单次所有私有数据与key值的大小限制32KB。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 传入的command参数或key参数为空指针。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_SetKey(InputMethod_PrivateCommand *command, char key[], size_t keyLength);
/**
 * @brief 设置{@link InputMethod_PrivateCommand}的布尔类型value值。调用此函数后，
 * 该PrivateCommand实例的value类型将变为IME_COMMAND_VALUE_TYPE_BOOL，之前已设置的其他类型value值（int32_t或string）将被覆盖。
 *     <br>
 *     <br>使用场景：当私有命令的value需要传递布尔类型数据时调用此函数，如传递开关状态、是否启用某功能等布尔语义的数据。
 *     <br>
 *     <br>前置条件：command参数必须为OH_PrivateCommand_Create成功返回的非NULL指针。
 *     <br>
 *     <br>值类型规则：同一个PrivateCommand实例只能持有一种类型的value。调用SetBoolValue后，value类型变为
 * IME_COMMAND_VALUE_TYPE_BOOL，之前通过SetIntValue或SetStrValue设置的value将被覆盖。后续通过GetIntValue或GetStrValue获取值
 * 时将返回IME_ERR_QUERY_FAILED。
 *
 * @param command 指向即将被设置的{@link InputMethod_PrivateCommand}实例的指针。不允许传入NULL指针，否则返回
 * IME_ERR_NULL_POINTER。
 * @param value 布尔类型value值，true或false。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功，value类型已设置为IME_COMMAND_VALUE_TYPE_BOOL。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，command参数为NULL。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_SetBoolValue(InputMethod_PrivateCommand *command, bool value);
/**
 * @brief 设置{@link InputMethod_PrivateCommand}的整数类型value值。调用此函数后，
 * 该PrivateCommand实例的value类型将变为IME_COMMAND_VALUE_TYPE_INT32，之前已设置的其他类型value值（bool或string）将被覆盖。
 *     <br>
 *     <br>使用场景：当私有命令的value需要传递整数类型数据时调用此函数，如传递数值参数、计数、版本号等整数语义的数据。
 *     <br>
 *     <br>前置条件：command参数必须为OH_PrivateCommand_Create成功返回的非NULL指针。
 *     <br>
 *     <br>值类型规则：同一个PrivateCommand实例只能持有一种类型的value。调用SetIntValue后，value类型变为
 * IME_COMMAND_VALUE_TYPE_INT32，之前通过SetBoolValue或SetStrValue设置的value将被覆盖。后续通过GetBoolValue或GetStrValue获
 * 取值时将返回IME_ERR_QUERY_FAILED。
 *
 * @param command 指向即将被设置的{@link InputMethod_PrivateCommand}实例的指针。不允许传入NULL指针，否则返回
 * IME_ERR_NULL_POINTER。
 * @param value 整数类型的value值，32位带符号整数。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功，value类型已设置为IME_COMMAND_VALUE_TYPE_INT32。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，command参数为NULL。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_SetIntValue(InputMethod_PrivateCommand *command, int32_t value);
/**
 * @brief 设置{@link InputMethod_PrivateCommand}的字符串类型value值。调用此函数后，
 * 该PrivateCommand实例的value类型将变为IME_COMMAND_VALUE_TYPE_STRING，之前已设置的其他类型value值（bool或int32_t）将被覆盖。
 *     <br>
 *     <br>使用场景：当私有命令的value需要传递字符串类型数据时调用此函数，如传递文本配置、URL、JSON格式参数等字符串语义的数据。
 *     <br>
 *     <br>前置条件：command参数必须为OH_PrivateCommand_Create成功返回的非NULL指针；value参数必须为非NULL指针；valueLength必
 * 须大于0。
 *     <br>
 *     <br>值类型规则：同一个PrivateCommand实例只能持有一种类型的value。调用SetStrValue后，value类型变为
 * IME_COMMAND_VALUE_TYPE_STRING，之前通过SetBoolValue或SetIntValue设置的value将被覆盖。后续通过GetBoolValue或GetIntValue获
 * 取值时将返回IME_ERR_QUERY_FAILED。
 *     <br>
 *     <br>内存管理：value字符串由调用方提供，SetStrValue函数会将字符串内容拷贝到PrivateCommand实例的内部存储中。调用方可在
 * SetStrValue调用后立即释放原始value内存，无需保持value指针有效。
 *
 * @param command 指向即将被设置的{@link InputMethod_PrivateCommand}实例的指针。不允许传入NULL指针，否则返回
 * IME_ERR_NULL_POINTER。
 * @param value 字符串类型value值。不允许传入NULL指针，否则返回IME_ERR_NULL_POINTER。字符串内容将被拷贝到PrivateCommand实例的
 * 内部存储中，调用方无需在SetStrValue调用后保持value指针有效。
 * @param valueLength 表示字符串数据值的字节长度，不包括结尾空字符。必须大于0。单次所有私有数据与key值的大小限制32KB。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功，value类型已设置为IME_COMMAND_VALUE_TYPE_STRING。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，command参数或value参数为NULL。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_SetStrValue(
    InputMethod_PrivateCommand *command, char value[], size_t valueLength);

/**
 * @brief 从{@link InputMethod_PrivateCommand}获取key值。key值为私有命令的标识符。
 *     <br>
 *     <br>使用场景：接收方在OH_TextEditorProxy_ReceivePrivateCommandFunc回调中获取到PrivateCommand实例后，首先通过此函数获取
 * key值，根据key的含义决定如何处理对应的value数据。
 *     <br>
 *     <br>前置条件：command参数必须为非NULL指针；key和keyLength输出参数必须为非NULL指针，且由调用方分配内存。
 *     <br>
 *     <br>内存管理：key指针指向的字符串生命周期与command实例一致。请勿直接保存key地址（因为在command销毁后key指针将失效），也不
 * 应直接修改key内容。推荐做法是先拷贝key字符串到调用方的自有内存后再使用。
 * command实例销毁后（OH_PrivateCommand_Destroy或回调返回后），key指针失效，对失效指针的访问为未定义行为。
 *
 * @param command 指向即将被获取key值的{@link InputMethod_PrivateCommand}实例的指针。不允许传入NULL指针，否则返回
 * IME_ERR_NULL_POINTER。
 * @param key 输出参数，用于接收key值的字符串指针。key的生命周期和command一致，请勿直接保存key地址，也不应直接操作key内容；推荐
 * 先拷贝后再使用。command实例销毁后，key指针失效，不应再访问。
 *     不允许传入NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @param keyLength 输出参数，用于接收key值的字节长度。不允许传入NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功，key和keyLength已被写入值。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，command、key或keyLength参数为NULL。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_GetKey(
    InputMethod_PrivateCommand *command, const char **key, size_t *keyLength);
/**
 * @brief 从{@link InputMethod_PrivateCommand}获取value的数据类型。返回的类型指示了该实例当前存储的value值的类型，用于指导后续
 * 应调用哪个GetValue函数来获取实际的value值。
 *     <br>
 *     <br>使用场景：在获取value值之前，必须先调用此函数判断value的数据类型，再根据类型调用对应的GetValue函数（GetBoolValue、
 * GetIntValue或GetStrValue）。若直接调用与实际类型不匹配的GetValue函数，将返回IME_ERR_QUERY_FAILED错误码。
 *     <br>
 *     <br>前置条件：command参数必须为非NULL指针；type输出参数必须为非NULL指针，且由调用方分配内存。
 *     <br>
 *     <br>使用建议：建议在每次获取value值前都先调用GetValueType确认类型，避免因类型不匹配导致IME_ERR_QUERY_FAILED错误。
 *     <br>
 *     <br>典型调用顺序：
 *     <br>1. 调用OH_PrivateCommand_GetValueType获取类型；
 *     <br>2. 根据类型判断调用OH_PrivateCommand_GetBoolValue/OH_PrivateCommand_GetIntValue/
 * OH_PrivateCommand_GetStrValue。
 *
 * @param command 指向即将被获取value类型的{@link InputMethod_PrivateCommand}实例的指针。不允许传入NULL指针，否则返回
 * IME_ERR_NULL_POINTER。
 * @param type 输出参数，用于获取value值的数据类型。返回值为{@link InputMethod_CommandValueType}枚举值：
 * IME_COMMAND_VALUE_TYPE_NONE表示未设置value；IME_COMMAND_VALUE_TYPE_STRING表示字符串类型；IME_COMMAND_VALUE_TYPE_BOOL表
 * 示布尔类型；IME_COMMAND_VALUE_TYPE_INT32表示32位带符号整数类型。不允许传入NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功，type已被写入当前value的数据类型。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，command或type参数为NULL。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_GetValueType(
    InputMethod_PrivateCommand *command, InputMethod_CommandValueType *type);
/**
 * @brief 从{@link InputMethod_PrivateCommand}获取布尔类型的value的值。
 *     <br>
 *     <br>使用场景：当通过OH_PrivateCommand_GetValueType确认value类型为IME_COMMAND_VALUE_TYPE_BOOL后，调用此函数获取布尔
 * 值。
 *     <br>
 *     <br>前置条件：command参数必须为非NULL指针；value输出参数必须为非NULL指针，且由调用方分配内存。当前PrivateCommand实例的
 * value类型必须为IME_COMMAND_VALUE_TYPE_BOOL，否则将返回IME_ERR_QUERY_FAILED。
 *     <br>
 *     <br>类型不匹配处理：若当前value类型不是IME_COMMAND_VALUE_TYPE_BOOL（例如为IME_COMMAND_VALUE_TYPE_INT32或
 * IME_COMMAND_VALUE_TYPE_STRING），此函数将返回IME_ERR_QUERY_FAILED错误码，表示查询失败——命令中没有布尔值。建议先调用
 * OH_PrivateCommand_GetValueType确认类型后再获取值。
 *
 * @param command 指向即将被获取value值的{@link InputMethod_PrivateCommand}实例的指针。不允许传入NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @param value 输出参数，用于接收布尔类型的value值。此参数为输出指针，调用方需分配bool类型变量的内存并将其地址传入。不允许传入
 * NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功，value指针指向的内存已被写入布尔值。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，command或value参数为NULL。
 *     <br>{@link IME_ERR_QUERY_FAILED} - 查询失败，命令中没有布尔值，即当前value类型不是IME_COMMAND_VALUE_TYPE_BOOL（类型不
 * 匹配）。建议先调用OH_PrivateCommand_GetValueType确认类型。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_GetBoolValue(InputMethod_PrivateCommand *command, bool *value);
/**
 * @brief 从{@link InputMethod_PrivateCommand}获取整数类型的value的值。
 *     <br>
 *     <br>使用场景：当通过OH_PrivateCommand_GetValueType确认value类型为IME_COMMAND_VALUE_TYPE_INT32后，调用此函数获取整数
 * 值。
 *     <br>
 *     <br>前置条件：command参数必须为非NULL指针；value输出参数必须为非NULL指针，且由调用方分配内存。当前PrivateCommand实例的
 * value类型必须为IME_COMMAND_VALUE_TYPE_INT32，否则将返回IME_ERR_QUERY_FAILED。
 *     <br>
 *     <br>类型不匹配处理：若当前value类型不是IME_COMMAND_VALUE_TYPE_INT32（例如为IME_COMMAND_VALUE_TYPE_BOOL或
 * IME_COMMAND_VALUE_TYPE_STRING），此函数将返回IME_ERR_QUERY_FAILED错误码，表示查询失败——命令中没有整数值。建议先调用
 * OH_PrivateCommand_GetValueType确认类型后再获取值。
 *
 * @param command 指向即将被获取value值的{@link InputMethod_PrivateCommand}实例的指针。不允许传入NULL指针，否则返回
 * IME_ERR_NULL_POINTER。
 * @param value 输出参数，用于接收整数类型的value值。此参数为输出指针，调用方需分配int32_t类型变量的内存并将其地址传入。不允许传
 * 入NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功，value指针指向的内存已被写入整数值。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，command或value参数为NULL。
 *     <br>{@link IME_ERR_QUERY_FAILED} - 查询失败，命令中没有整数值，即当前value类型不是IME_COMMAND_VALUE_TYPE_INT32（类型
 * 不匹配）。 建议先调用OH_PrivateCommand_GetValueType确认类型。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_GetIntValue(InputMethod_PrivateCommand *command, int32_t *value);
/**
 * @brief 从{@link InputMethod_PrivateCommand}获取字符串类型的value的值。
 *     <br>
 *     <br>使用场景：当通过OH_PrivateCommand_GetValueType确认value类型为IME_COMMAND_VALUE_TYPE_STRING后，调用此函数获取字符
 * 串值。
 *     <br>
 *     <br>前置条件：command参数必须为非NULL指针；value和valueLength输出参数必须为非NULL指针，且由调用方分配内存。当前
 * PrivateCommand实例的value类型必须为IME_COMMAND_VALUE_TYPE_STRING，否则将返回IME_ERR_QUERY_FAILED。
 *     <br>
 *     <br>类型不匹配处理：若当前value类型不是IME_COMMAND_VALUE_TYPE_STRING（例如为IME_COMMAND_VALUE_TYPE_BOOL或
 * IME_COMMAND_VALUE_TYPE_INT32），此函数将返回IME_ERR_QUERY_FAILED错误码，表示查询失败——命令中没有字符串值。建议先调用
 * OH_PrivateCommand_GetValueType确认类型后再获取值。
 *     <br>
 *     <br>内存管理：value指针指向的字符串生命周期与command实例一致。请勿直接保存value地址（因为在command销毁后value指针将失
 * 效），也不应直接修改value内容。推荐做法是先拷贝字符串到调用方的自有内存后再使用。command实例销毁后
 * （OH_PrivateCommand_Destroy或回调返回后），value指针失效，对失效指针的访问为未定义行为。
 *
 * @param command 指向即将被获取value值的{@link InputMethod_PrivateCommand}实例的指针。不允许传入NULL指针，否则返回
 * IME_ERR_NULL_POINTER。
 * @param value 输出参数，用于接收字符串类型value值的指针。value的生命周期和command一致，请勿直接保存value地址，也不应直接修改
 * value内容；推荐先拷贝后再使用。command实例销毁后，value指针失效，不应再访问。不允许传入NULL指针，否则返回
 * IME_ERR_NULL_POINTER。
 * @param valueLength 输出参数，用于返回字符串类型value值的字节长度。不允许传入NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功，value和valueLength已被写入值。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，command、value或valueLength参数为NULL。
 *     <br>{@link IME_ERR_QUERY_FAILED} - 查询失败，命令中没有字符串值，即当前value类型不是IME_COMMAND_VALUE_TYPE_STRING（类
 * 型不匹配）。建议先调用OH_PrivateCommand_GetValueType确认类型。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_GetStrValue(
    InputMethod_PrivateCommand *command, const char **value, size_t *valueLength);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_PRIVATE_COMMAND_CAPI_H
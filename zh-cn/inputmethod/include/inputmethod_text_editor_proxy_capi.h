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
 * @file inputmethod_text_editor_proxy_capi.h
 *
 * @brief 提供一套方法支持应用开发的自绘输入框获取来自输入法应用的通知和请求。该模块采用回调机制实现输入法应用与自绘输入框之间的双向通信。
 *
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
 * @brief 输入法文本编辑器代理类。用于处理输入法应用与文本编辑器之间的交互，提供接收输入法请求和通知的方法，适用于需要实现输入法与编辑器双向通信的场景。该结构体为不透明类型（opaque type），调用者不可直接访问其内部成员，
 * 仅可通过本模块提供的函数接口进行操作。
 *
 * @since 12
 */
typedef struct InputMethod_TextEditorProxy InputMethod_TextEditorProxy;

/**
 * @brief 输入法获取输入框配置时触发的回调函数。开发者需实现此函数，在函数中对config参数设置编辑框的配置信息（输入类型、回车键类型、光标信息等），输入法框架将据此调整键盘布局和输入行为。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的{@link InputMethod_TextEditorProxy}实例。用于标识触发回调的代理对象。
 * @param config 输出指针，表示指向{@link InputMethod_TextConfig}实例的指针。需要在函数实现中对其设置各配置属性（输入类型、回车键类型、光标信息等）以填充输入框配置。此指针仅在回调执行期间有效，
 *     回调返回后该内存将被释放，不可再访问。开发者必须在回调内部完成所有设置操作，不得在回调外部继续使用此指针。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_GetTextConfigFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_TextConfig *config);
/**
 * @brief 输入法应用插入文本时触发的回调函数。开发者需实现此函数，在函数中将text参数指定的文本内容插入到编辑框的光标位置。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param text 输入指针，插入的文本内容，采用UTF-16编码。此指针仅在回调执行期间有效，回调返回后该内存将被释放，不可再访问。开发者应在回调内部完成必要的数据拷贝或处理。
 * @param length 输入参数，插入字符的数量（单位：char16_t字符个数）。取值范围：大于0。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_InsertTextFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, const char16_t *text, size_t length);
/**
 * @brief 输入法删除光标右侧文本时触发的回调函数。开发者需实现此函数，在函数中从光标位置向右删除指定数量的字符。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param length 输入参数，要删除的字符数量（单位：字符个数）。取值范围：大于0且不超过光标右侧剩余文本长度。取值原则：若length超过右侧剩余文本长度，应删除到文本末尾。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_DeleteForwardFunc)(InputMethod_TextEditorProxy *textEditorProxy, int32_t length);
/**
 * @brief 输入法删除光标左侧文本时触发的回调函数。开发者需实现此函数，在函数中从光标位置向左删除指定数量的字符。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param length 输入参数，要删除的字符数量（单位：字符个数）。取值范围：大于0且不超过光标左侧已有文本长度。取值原则：若length超过左侧已有文本长度，应删除到文本开头。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_DeleteBackwardFunc)(InputMethod_TextEditorProxy *textEditorProxy, int32_t length);
/**
 * @brief 输入法通知键盘状态时触发的回调函数。开发者需实现此函数，在函数中根据keyboardStatus参数更新编辑框对键盘状态的感知。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param keyboardStatus 输入参数，键盘状态。取值范围：{@link InputMethod_KeyboardStatus}枚举值（IME_KEYBOARD_NONE=0、IME_KEYBOARD_SHOW=1、
 *     IME_KEYBOARD_HIDE=2）。使用后效果：设置为IME_KEYBOARD_SHOW时表示键盘已弹出，IME_KEYBOARD_HIDE时表示键盘已收起。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_SendKeyboardStatusFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_KeyboardStatus keyboardStatus);
/**
 * @brief 输入法发送回车键时触发的回调函数。开发者需实现此函数，在函数中根据enterKeyType参数执行对应的回车键动作。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param enterKeyType 输入参数，回车键类型。取值范围：{@link InputMethod_EnterKeyType}枚举值。使用后效果：不同类型对应不同的回车键行为，如IME_ENTER_KEY_GO表示"前往"、
 *     IME_ENTER_KEY_SEARCH表示"搜索"等。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_SendEnterKeyFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_EnterKeyType enterKeyType);
/**
 * @brief 输入法移动光标时触发的回调函数。开发者需实现此函数，在函数中根据direction参数移动编辑框中的光标位置。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param direction 输入参数，光标移动方向。取值范围：{@link InputMethod_Direction}枚举值。使用后效果：不同方向对应不同的光标移动行为，如IME_DIRECTION_UP表示上移、
 *     IME_DIRECTION_DOWN表示下移、IME_DIRECTION_LEFT表示左移、IME_DIRECTION_RIGHT表示右移。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_MoveCursorFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_Direction direction);
/**
 * @brief 输入法请求选中文本时触发的回调函数。开发者需实现此函数，在函数中根据start和end参数选中编辑框中的指定范围文本。
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
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param action 输入参数，扩展编辑操作。取值范围：{@link InputMethod_ExtendAction}枚举值。使用后效果：不同操作对应不同的编辑行为，
 *     如IME_EXTEND_ACTION_SELECT_ALL表示全选、IME_EXTEND_ACTION_CUT表示剪切、IME_EXTEND_ACTION_COPY表示复制等。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_HandleExtendActionFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_ExtendAction action);
/**
 * @brief 输入法获取光标左侧文本时触发的回调函数。开发者需实现此函数，在函数中将光标左侧指定数量的文本内容写入text参数，并将实际字符数量写入length参数。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param number 输入参数，要获取的字符数量（单位：字符个数）。取值范围：大于0。取值原则：若number超过光标左侧已有文本长度，应返回左侧全部文本。
 * @param text Represents the left text of cursor, you need to assing this parameter. You can only access the memory
 *     when this callback is called. After this callback returns, the memory will be released and you should not access
 *     this
 *     memory again.
 * @param length 输出指针，用于返回实际获取到的字符数量（单位：char16_t字符个数）。由调用者（输入法框架）分配内存，开发者需在回调内部对*length赋值。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_GetLeftTextOfCursorFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, int32_t number, char16_t text[], size_t *length);
/**
 * @brief 输入法获取光标右侧文本时触发的回调函数。开发者需实现此函数，在函数中将光标右侧指定数量的文本内容写入text参数，并将实际字符数量写入length参数。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param number 输入参数，要获取的字符数量（单位：字符个数）。取值范围：大于0。
 * @param text Represents the right text of cursor, you need to assing this parameter. You can only access the memory
 *     when this callback is called. After this callback returns, the memory will be released and you should not access
 *     this
 *     memory again.
 * @param length 输出指针，用于返回实际获取到的字符数量（单位：char16_t字符个数）。由调用者分配内存，开发者需在回调内部对*length赋值。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_GetRightTextOfCursorFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, int32_t number, char16_t text[], size_t *length);
/**
 * @brief 输入法获取光标所在输入框文本索引时触发的回调函数。开发者需实现此函数，在函数中返回光标在编辑框文本中的字符索引位置。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @return 返回光标在文本内容中的字符索引位置，索引从0开始计数（单位：字符偏移量）。取值范围：大于等于0且小于文本总长度。
 * @since 12
 */
typedef int32_t (*OH_TextEditorProxy_GetTextIndexAtCursorFunc)(InputMethod_TextEditorProxy *textEditorProxy);
/**
 * @brief 输入法应用发送私有数据命令时触发的回调函数。开发者需实现此函数，在函数中处理输入法应用发送的私有命令数据。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param privateCommand Private command from input method. You can only access the memory when this callback is called.
 *     After this callback returns, the memory will be released and you should not access this memory again.
 * @param size 输入参数，私有数据命令数组中的元素数量。取值范围：大于0且不超过5。
 * @return 返回对私有数据命令的处理结果。0表示成功，非0表示失败。
 * @since 12
 */
typedef int32_t (*OH_TextEditorProxy_ReceivePrivateCommandFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_PrivateCommand *privateCommand[], size_t size);
/**
 * @brief 输入法设置预上屏文本时触发的回调函数。预上屏是输入法的候选文本展示功能，通常在用户输入拼音或输入码未确定汉字时显示。此函数负责设置预上屏文本及其光标位置。与
 * {@link OH_TextEditorProxy_FinishTextPreviewFunc}配合使用：先调用SetPreviewTextFunc设置预上屏内容，当用户选择候选词或取消输入时，
 * 调用FinishTextPreviewFunc结束预上屏。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @param text Represents text to be previewd. You can only access the memory when this callback is called.
 *     After this callback returns, the memory will be released and you should not access this memory again.
 * @param length 输入参数，预上屏文本的字符数量（单位：char16_t字符个数）。
 * @param start 输入参数，预上屏文本起始光标位置（单位：字符偏移量，相对于文本开头）。
 * @param end 输入参数，预上屏文本结束光标位置（单位：字符偏移量，相对于文本开头）。
 * @return 返回处理结果。0表示成功，非0表示失败。
 * @since 12
 */
typedef int32_t (*OH_TextEditorProxy_SetPreviewTextFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, const char16_t text[], size_t length, int32_t start, int32_t end);
/**
 * @brief 输入法结束预上屏时触发的回调函数。此函数用于清理预上屏状态，通常在用户选择候选词（确定输入）或取消输入时调用。与{@link OH_TextEditorProxy_SetPreviewTextFunc}配合使用。
 *
 * @param textEditorProxy 输入指针，指向当前被回调的TextEditorProxy实例。
 * @since 12
 */
typedef void (*OH_TextEditorProxy_FinishTextPreviewFunc)(InputMethod_TextEditorProxy *textEditorProxy);

/**
 * @brief 创建一个新的{@link InputMethod_TextEditorProxy}实例。创建后需通过Set*Func接口注册回调函数，再通过{@link OH_InputMethodController_Attach}
 * 完成绑定注册。
 *
 * @return 如果创建成功，返回一个指向新创建的{@link InputMethod_TextEditorProxy}实例的指针。如果创建失败，返回NULL，可能的失败原因有内存不足。返回NULL时应检查系统内存状态。
 *     返回的指针在使用完毕后必须通过{@link OH_TextEditorProxy_Destroy}销毁，销毁后指针应设置为NULL避免误用。
 * @since 12
 */
InputMethod_TextEditorProxy *OH_TextEditorProxy_Create(void);
/**
 * @brief 销毁一个{@link InputMethod_TextEditorProxy}实例。销毁后proxy指针不可再使用，建议将指针设置为NULL避免误用。
 *
 * @param proxy 输入指针，表示指向即将被销毁的{@link InputMethod_TextEditorProxy}实例的指针。若传入NULL，函数不做任何处理，不会导致崩溃。销毁后该指针失效，建议设置为NULL。
 * @since 12
 */
void OH_TextEditorProxy_Destroy(InputMethod_TextEditorProxy *proxy);
/**
 * @brief 将函数{@link OH_TextEditorProxy_GetTextConfigFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成，
 * Attach后设置的回调不会被输入法调用。
 *
 * @param proxy 输入指针，指向即将被设置的{@link InputMethod_TextEditorProxy}实例的指针。不可为NULL，若传入NULL将返回IME_ERR_NULL_POINTER。
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
 * @brief 将函数{@link OH_TextEditorProxy_InsertTextFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成。
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
 * @brief 将函数{@link OH_TextEditorProxy_DeleteForwardFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成。
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
 * @brief 将函数{@link OH_TextEditorProxy_DeleteBackwardFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成。
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
 * @brief 将函数{@link OH_TextEditorProxy_SendKeyboardStatusFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成。
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
 * @brief 将函数{@link OH_TextEditorProxy_SendEnterKeyFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成。
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
 * @brief 将函数{@link OH_TextEditorProxy_MoveCursorFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成。
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
 * @brief 将函数{@link OH_TextEditorProxy_HandleSetSelectionFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成。
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
 * @brief 将函数{@link OH_TextEditorProxy_HandleExtendActionFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成。
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
 * @brief 将函数{@link OH_TextEditorProxy_GetLeftTextOfCursorFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成。
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
 * @brief 将函数{@link OH_TextEditorProxy_GetRightTextOfCursorFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成。
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
 * @brief 将函数{@link OH_TextEditorProxy_GetTextIndexAtCursorFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成。
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
 * @brief 将函数{@link OH_TextEditorProxy_SetPreviewTextFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成。
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
 * @brief 将函数{@link OH_TextEditorProxy_FinishTextPreviewFunc}设置到{@link InputMethod_TextEditorProxy}中。此设置须在Attach之前完成。
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
 * @param getTextConfigFunc 输出指针，表示从proxy获取到的函数指针。由调用者分配内存，函数将把回调函数指针写入此地址。不可为NULL。
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
 * {@link OH_TextEditorProxy_GetTextConfigFunc}之外的所有回调函数。{@link OH_TextEditorProxy_GetTextConfigFunc}的执行线程由调用
 * {@link OH_InputMethodController_Attach}的线程决定，不受本接口影响。若需GetTextConfigFunc也在主线程执行，需确保Attach在主线程调用。
 *
 * @param proxy 输入指针，指向目标InputMethod_TextEditorProxy实例的指针。不可为NULL，若传入NULL将返回IME_ERR_NULL_POINTER。
 * @param isCallbackInMainThread 输入参数，线程执行策略。取值范围：true或false。取值原则：true-回调函数切换至主线程执行（用于避免多线程并发问题），避免在回调内执行耗时操作防止主线程阻塞；
 *     false-回调函数在IPC线程执行（可能存在多线程并发情况），响应速度更快。
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
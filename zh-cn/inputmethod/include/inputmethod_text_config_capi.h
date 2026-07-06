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
 * @file inputmethod_text_config_capi.h
 *
 * @brief 提供输入框配置信息对象的创建、销毁与读写方法。InputMethod_TextConfig承载编辑框的配置信息，在GetTextConfigFunc回调中使用，开发者需在回调内对config参数设置各配置项。
 *
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
 * @brief 文本输入框的文本输入行为配置结构体，用于输入框向输入法框架传递核心输入规则，输入法框架根据配置执行相应输入行为。通过配置输入属性（如输入类型、文本格式等），能够满足不同场景下的输入需求，提升用户输入体验，
 * 适用于需要精细化控制输入行为的文本输入场景。该结构体为不透明类型（opaque type），调用者不可直接访问其内部成员，仅可通过本模块提供的函数接口进行操作。
 *
 * @since 12
 */
typedef struct InputMethod_TextConfig InputMethod_TextConfig;

/**
 * @brief 创建一个新的{@link InputMethod_TextConfig}实例。主要用于在{@link OH_TextEditorProxy_GetTextConfigFunc}回调中对config参数进行设置操作。
 *
 * @return 如果创建成功，返回一个指向新创建的{@link InputMethod_TextConfig}实例的指针。如果创建失败，返回NULL，可能的失败原因有内存不足。返回的指针在使用完毕后必须通过
 *     {@link OH_TextConfig_Destroy}销毁，销毁后指针应设置为NULL避免误用。
 * @since 12
 */
InputMethod_TextConfig *OH_TextConfig_Create(void);
/**
 * @brief 销毁一个{@link InputMethod_TextConfig}实例。销毁后config指针不可再使用，建议将指针设置为NULL避免误用。
 *
 * @param config 输入指针，表示指向即将被销毁的{@link InputMethod_TextConfig}实例的指针。若传入NULL，函数不做任何处理，不会导致崩溃。销毁后该指针失效，建议设置为NULL。注意：
 *     由GetTextConfigFunc回调框架提供的config参数的内存由框架管理，回调返回后自动释放，不可在回调外部调用Destroy销毁。
 * @since 12
 */
void OH_TextConfig_Destroy(InputMethod_TextConfig *config);

/**
 * @brief 设置文本配置信息中的输入框类型。输入法框架将根据此类型调整键盘布局。
 *
 * @param config 输入指针，指向即将被设置值的{@link InputMethod_TextConfig}实例的指针。不可为NULL，若传入NULL将返回IME_ERR_NULL_POINTER。
 * @param inputType 输入参数，输入框的输入类型。取值范围：{@link InputMethod_TextInputType}枚举值，如IME_TEXT_INPUT_TYPE_TEXT、
 *     IME_TEXT_INPUT_TYPE_NUMBER、IME_TEXT_INPUT_TYPE_PHONE等。使用后效果：不同类型将触发输入法切换到不同的键盘布局。
 * @return 返回一个特定的错误码。
 *     <br>IME_ERR_OK = 0：表示成功。
 *     <br>IME_ERR_NULL_POINTER = 12802000：非预期的空指针，config为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_SetInputType(InputMethod_TextConfig *config, InputMethod_TextInputType inputType);
/**
 * @brief 设置文本配置信息中的回车键功能类型。输入法框架将据此调整回车键的显示标签和功能。
 *
 * @param config 输入指针，指向即将被设置值的TextConfig实例的指针。不可为NULL。
 * @param enterKeyType 输入参数，回车键功能类型。取值范围：{@link InputMethod_EnterKeyType}枚举值。使用后效果：不同类型对应不同的回车键行为和显示标签。
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
 *
 * @param config 输入指针，指向即将被设置值的TextConfig实例的指针。不可为NULL。
 * @param supported 输入参数，表示输入框是否支持预上屏。取值范围：true或false。true表示支持预上屏，输入法将使用SetPreviewTextFunc回调；false表示不支持预上屏。此参数为必需参数，
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
 *
 * @param config 输入指针，指向即将被设置值的TextConfig实例的指针。不可为NULL。
 * @param start 输入参数，所选文本的起始位置（单位：字符偏移量，从0开始计数）。取值原则：start应大于等于0且小于等于end。
 * @param end 输入参数，所选文本的结束位置（单位：字符偏移量，从0开始计数）。取值原则：end应大于等于start且小于等于文本总长度。无选中文本时start与end相等表示光标位置。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_SetSelection(InputMethod_TextConfig *config, int32_t start, int32_t end);
/**
 * @brief 设置文本配置信息中所属窗口的窗口id。用于标识编辑框所属的应用窗口，输入法据此确定避让区域和候选词窗口定位。
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
 *
 * @param config 输入指针，指向即将被设置值的TextConfig实例的指针。不可为NULL，若传入NULL将返回IME_ERR_NULL_POINTER。
 * @param placeholder 输入指针，指向UTF-16编码的双字节字符串。若传NULL指针，则会将占位文本信息设置为空字符串。函数仅读取该数据，不会修改或释放。
 * @param length 输入参数，placeholder指针指向的UTF-16字符个数（不包含结尾符）。取值范围：0到255。1. 如果长度为0，占位文本信息会被设置为空字符串。2. UTF-16编码的最大长度为255个字符（
 *     不包含结尾符），超过255个字符会被截断。
 * @return {@link InputMethod_ErrorCode}：IME_ERR_OK = 0：表示成功。IME_ERR_NULL_POINTER = 12802000：非预期的空指针，config为NULL。
 * @since 20
 */
InputMethod_ErrorCode OH_TextConfig_SetPlaceholder(InputMethod_TextConfig *config, const char16_t *placeholder,
    size_t length);

/**
 * @brief 设置文本配置信息中的abilityName信息。abilityName用于标识编辑框所属的Ability，输入法据此感知编辑框的业务场景。
 *
 * @param config 输入指针，指向即将被设置值的TextConfig实例的指针。不可为NULL。
 * @param abilityName 输入指针，指向UTF-16编码的双字节字符串。若传NULL指针，则会将abilityName设置为空字符串。函数仅读取该数据。
 * @param length 输入参数，abilityName指针指向的UTF-16字符个数（不包含结尾符）。取值范围：0到127。1. 如果长度为0，abilityName会被设置为空字符串。2. UTF-
 *     16编码的最大长度为127个字符（不包含结尾符），超过127个字符会被截断。
 * @return {@link InputMethod_ErrorCode}：IME_ERR_OK = 0：表示成功。IME_ERR_NULL_POINTER = 12802000：非预期的空指针，config为NULL。
 * @since 20
 */
InputMethod_ErrorCode OH_TextConfig_SetAbilityName(InputMethod_TextConfig *config, const char16_t *abilityName,
    size_t length);

/**
 * @brief 将编辑框是否具有完整处理字母、字符、功能等按键的能力设置到文本配置信息中。当设置为true时，表示编辑框具备完整处理按键事件的能力，输入法框架将跳过对这些按键的处理；当设置为false时，表示编辑框不具备此能力，
 * 按键事件将由输入法框架自行处理。
 *
 * @param config 输入指针，指向即将被设置值的{@link InputMethod_TextConfig}实例的指针。不可为NULL，若传入NULL将返回IME_ERR_NULL_POINTER。
 * @param consumeKeyEvents 输入参数，表示编辑框是否具有完整处理字母、字符、功能等按键的能力。取值范围：true或false。true表示编辑框具备完整处理按键事件的能力，输入法框架将跳过对字母、字符、
 *     功能等按键的处理，由编辑框自行消费；false表示编辑框不具备此能力，按键事件将由输入法框架处理。此参数为必需参数，必须设置。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 26.0.0
 */
InputMethod_ErrorCode OH_TextConfig_SetConsumeKeyEvents(InputMethod_TextConfig *config, bool consumeKeyEvents);

/**
 * @brief 获取文本配置信息中的输入框类型。
 *
 * @param config 输入指针，指向即将被获取值的TextConfig实例的指针。不可为NULL。
 * @param inputType 输出指针，表示指向{@link InputMethod_TextInputType}变量的指针。由调用者分配内存，函数将把输入类型值写入此地址。不可为NULL。取值范围：
 *     {@link InputMethod_TextInputType}枚举值。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config或inputType为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetInputType(InputMethod_TextConfig *config, InputMethod_TextInputType *inputType);
/**
 * @brief 获取文本配置信息中的回车键功能类型。
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
 *
 * @param config 输入指针，指向即将被获取值的TextConfig实例的指针。不可为NULL。
 * @param supported 输出指针，用于返回是否支持预上屏。由调用者分配内存。不可为NULL。取值范围：true表示支持预上屏，false表示不支持预上屏。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config或supported为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_IsPreviewTextSupported(InputMethod_TextConfig *config, bool *supported);
/**
 * @brief 获取文本配置信息中的光标信息。此接口使用双指针参数，函数内部分配内存返回CursorInfo对象。
 *
 * @param config 输入指针，指向即将被获取值的TextConfig实例的指针。不可为NULL。
 * @param cursorInfo 输出双指针，用于返回光标信息对象。函数内部分配内存创建{@link InputMethod_CursorInfo}实例，并通过此双指针返回。不可为NULL。返回的对象必须在使用完毕后调用
 *     {@link OH_CursorInfo_Destroy}释放，不可使用free直接释放，否则会造成内存泄漏。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config或cursorInfo为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetCursorInfo(InputMethod_TextConfig *config, InputMethod_CursorInfo **cursorInfo);

/**
 * @brief 获取文本配置信息中的避让信息。此接口使用双指针参数，函数内部分配内存返回TextAvoidInfo对象。
 *
 * @param config 输入指针，表示文本配置信息。不可为NULL。
 * @param avoidInfo 输出双指针，用于返回输入框避让信息对象。函数内部分配内存创建{@link InputMethod_TextAvoidInfo}实例，并通过此双指针返回。不可为NULL。
 *     返回的对象必须在使用完毕后调用{@link OH_TextAvoidInfo_Destroy}释放，不可使用free直接释放，否则会造成内存泄漏。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，config或avoidInfo为NULL。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 *@since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetTextAvoidInfo(
    InputMethod_TextConfig *config, InputMethod_TextAvoidInfo **avoidInfo);

/**
 * @brief 获取文本配置信息中的选区范围信息。
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
 * @brief 获取文本配置信息中的占位符文本信息。此接口采用两步调用策略：第一次调用时以NULL作为placeholder参数，length将返回实际占位文本长度；根据返回的长度分配足够内存后第二次调用获取完整内容。
 *
 * @param config 输入指针，指向即将被获取值的TextConfig实例的指针。不可为NULL。
 * @param placeholder 输出指针，用于存放占位文本信息，该指针内存由调用者分配和维护。采用两步调用策略：第一次可传NULL获取实际长度；第二次传已分配的足够内存获取完整内容。最大支持255个UTF-16字符（不含结尾符）
 *     ，分配时建议预留length+1个元素空间以包含结尾符。
 * @param length 输入/输出指针，占位文本信息长度（单位：UTF-16字符个数，不包含结尾符）。作为入参时，表示placeholder指向的内存可用长度（最大支持255个字符）；作为出参时，表示实际的占位文本长度。
 *     不可为NULL。
 * @return {@link InputMethod_ErrorCode}：IME_ERR_OK = 0：表示成功。IME_ERR_PARAMCHECK = 401：参数检查失败，
 *     可能是placeholder为NULL或length不足，此时length会被设置为实际长度。IME_ERR_NULL_POINTER = 12802000：非预期的空指针，config或length为NULL。
 * @since 20
 */
InputMethod_ErrorCode OH_TextConfig_GetPlaceholder(InputMethod_TextConfig *config, char16_t *placeholder,
    size_t *length);

/**
 * @brief 获取文本配置信息中的abilityName信息。此接口采用两步调用策略：第一次调用时以NULL作为abilityName参数，length将返回实际abilityName长度；
 * 根据返回的长度分配足够内存后第二次调用获取完整内容。
 *
 * @param config 输入指针，指向即将被获取值的TextConfig实例的指针。不可为NULL。
 * @param abilityName 输出指针，用于存放abilityName，该指针内存由调用者分配和维护。采用两步调用策略：第一次可传NULL获取实际长度；第二次传已分配的足够内存获取完整内容。最大支持127个UTF-16字符（
 *     不含结尾符），分配时建议预留length+1个元素空间。
 * @param length 输入/输出指针，abilityName长度（单位：UTF-16字符个数，不包含结尾符）。作为入参时，表示abilityName指向的内存可用长度（最大支持127个字符）；作为出参时，
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
 * @brief 获取文本配置中编辑框是否具有完整处理字母、字符、功能等按键的能力。即读取通过{@link OH_TextConfig_SetConsumeKeyEvents}设置的按键事件消费能力配置。
 *
 * @param config 输入指针，指向即将被获取值的{@link InputMethod_TextConfig}实例的指针。不可为NULL，若传入NULL将返回IME_ERR_NULL_POINTER。
 * @param consumeKeyEvents 输出指针，用于返回编辑框是否具有完整处理字母、字符、功能等按键的能力。由调用者分配内存。不可为NULL。取值范围：true表示编辑框具备完整处理按键事件的能力，输入法框架将跳过对字母、
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
/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @brief InputMethod provides functions to use input methods.
 *
 * @since 12
 */

/**
 * @file inputmethod_preview_text_style_capi.h
 *
 * @brief 预上屏文本样式的头文件，提供PreviewTextStyle实例的创建、销毁与属性读写方法。PreviewTextStyle描述预上屏文本的下划线
 * 样式和颜色，用于输入法设置带样式的预上屏文本时传递样式信息。Create/Destroy必须配对。
 * <br>
 * <br>功能：创建和管理OH_InputMethod_PreviewTextStyle实例，用于描述预上屏文本的下划线样式（无下划线/实线/波浪线/虚线）和颜色
 * 信息。颜色格式为0xRRGGBB，透明度通道（AA）无效，将被编辑器忽略。
 * <br>
 * <br>使用场景：当输入法应用通过SetPreviewTextWithStyleFunc回调设置带样式的预上屏文本时，系统将构造PreviewTextStyle对象
 * 并传递给应用，应用通过Get方法读取样式信息进行渲染。
 *
 * @include <inputmethod/inputmethod_preview_text_style_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 26.1.0
 */
#ifndef OHOS_INPUTMETHOD_PREVIEW_TEXT_STYLE_CAPI_H
#define OHOS_INPUTMETHOD_PREVIEW_TEXT_STYLE_CAPI_H
#include <stdbool.h>
#include <stdint.h>
#include "inputmethod_types_capi.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
* @brief OH_InputMethod_PreviewTextStyle是预上屏文本样式的不透明类型（opaque type），用于描述预上屏文本的下划线样式和颜色信息。
 * 调用者不可直接访问其内部成员，仅可通过本头文件提供的函数接口进行操作。
 * <br>
 * <br>用途：为输入法设置带样式的预上屏文本提供样式描述。包含以下属性：
 * <br>- 下划线样式（underlineStyle）：枚举值，取值为{@link OH_InputMethod_UnderlineStyle}，默认值为
 * {@link OH_INPUTMETHOD_UNDERLINE_STYLE_NONE}。
 * <br>- 下划线颜色（underlineColor）：格式为0xRRGGBB，仅当hasUnderlineColor为true时有效。透明度通道（AA）无效，将被
 * 编辑器忽略。
 * <br>- 是否显式设置颜色（hasUnderlineColor）：false表示跟随应用主题色。
 * <br>
 * <br>生命周期管理：
 * <br>- 创建方式：通过[OH_InputMethod_PreviewTextStyle_Create](#oh_inputmethod_previewtextstyle_create)函数创建，返回一个
 * 新的OH_InputMethod_PreviewTextStyle实例指针。创建失败时返回NULL，可能原因为内存不足。
 * <br>- 销毁方式：通过[OH_InputMethod_PreviewTextStyle_Destroy](#oh_inputmethod_previewtextstyle_destroy)函数销毁，传入
 * 要销毁的实例指针。销毁后指针不可再使用，建议将指针设置为NULL避免误用。
 * <br>- 配对关系：OH_InputMethod_PreviewTextStyle_Create与OH_InputMethod_PreviewTextStyle_Destroy必须配对使用，创建的对象
 * 必须最终通过Destroy释放，否则会导致内存泄漏。
 *
 * @since 26.1.0
 */
typedef struct OH_InputMethod_PreviewTextStyle OH_InputMethod_PreviewTextStyle;

/**
* @brief 创建一个新的{@link OH_InputMethod_PreviewTextStyle}实例。默认下划线样式为
 * {@link OH_INPUTMETHOD_UNDERLINE_STYLE_NONE}，默认下划线颜色为0，hasUnderlineColor为false。
 * <br>
 * <br>使用场景：当需要构造预上屏文本样式对象时调用此函数。
 * <br>
 * <br>生命周期管理：返回的对象必须通过[OH_InputMethod_PreviewTextStyle_Destroy](#oh_inputmethod_previewtextstyle_destroy)
 * 销毁，Create与Destroy必须配对使用。未销毁会导致内存泄漏。
 *
 * @return 如果创建成功，返回一个指向新创建的{@link OH_InputMethod_PreviewTextStyle}实例的指针。如果创建失败，返回NULL，
 *     可能的失败原因有内存不足。
 * @since 26.1.0
 */
OH_InputMethod_PreviewTextStyle *OH_InputMethod_PreviewTextStyle_Create(void);

/**
* @brief 销毁一个{@link OH_InputMethod_PreviewTextStyle}实例。销毁后style指针不可再使用，建议将指针设置为NULL避免误用。
 * <br>
 * <br>使用场景：当不再需要PreviewTextStyle实例时调用此函数释放内存。
 * <br>
 * <br>生命周期管理：传入NULL时函数不做任何处理，不会导致崩溃。
 *
 * @param style 输入指针，表示指向即将被销毁的{@link OH_InputMethod_PreviewTextStyle}实例的指针。若传入NULL，函数不做任何处理。
 * @since 26.1.0
 */
void OH_InputMethod_PreviewTextStyle_Destroy(OH_InputMethod_PreviewTextStyle *style);

/**
 * @brief 设置预上屏文本的下划线样式。
 *
 * @param style 输入指针，指向即将被设置的{@link OH_InputMethod_PreviewTextStyle}实例的指针。不可为NULL。
 * @param underlineStyle 输入参数，下划线样式，参见{@link OH_InputMethod_UnderlineStyle}。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_PreviewTextStyle_SetUnderlineStyle(
    OH_InputMethod_PreviewTextStyle *style, OH_InputMethod_UnderlineStyle underlineStyle);

/**
 * @brief 获取预上屏文本的下划线样式。
 *
 * @param style 输入指针，指向被读取的{@link OH_InputMethod_PreviewTextStyle}实例的指针。不可为NULL。
 * @param underlineStyle 输出指针，用于返回下划线样式。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_PreviewTextStyle_GetUnderlineStyle(
    OH_InputMethod_PreviewTextStyle *style, OH_InputMethod_UnderlineStyle *underlineStyle);

/**
 * @brief 设置预上屏文本的下划线颜色。颜色格式为0xRRGGBB，透明度通道（AA）无效，将被编辑器忽略。
 * 调用此函数后，下划线颜色将被标记为已显式指定；之后调用{@link OH_InputMethod_PreviewTextStyle_HasUnderlineColor}时，其hasUnderlineColor输出参数将为true。
 *
 * @param style 输入指针，指向即将被设置的{@link OH_InputMethod_PreviewTextStyle}实例的指针。不可为NULL。
 * @param underlineColor 输入参数，下划线颜色，格式为0xRRGGBB。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_PreviewTextStyle_SetUnderlineColor(
    OH_InputMethod_PreviewTextStyle *style, uint32_t underlineColor);

/**
 * @brief 获取预上屏文本的下划线颜色。
 *
 * @param style 输入指针，指向被读取的{@link OH_InputMethod_PreviewTextStyle}实例的指针。不可为NULL。
 * @param underlineColor 输出指针，用于返回下划线颜色，格式为0xRRGGBB。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_PreviewTextStyle_GetUnderlineColor(
    OH_InputMethod_PreviewTextStyle *style, uint32_t *underlineColor);

/**
 * @brief 从{@link OH_InputMethod_PreviewTextStyle}中获取是否设置了下划线颜色。
 *
 * 结果由是否调用过{@link OH_InputMethod_PreviewTextStyle_SetUnderlineColor}决定。若已调用过则hasUnderlineColor输出true，否则输出false。
 *
 * @param style 输入指针，指向被读取的{@link OH_InputMethod_PreviewTextStyle}实例的指针。不可为NULL。
 * @param hasUnderlineColor 输出指针，用于返回是否设置了下划线颜色。不可为NULL。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。
 *     <br>具体错误码可以参考{@link InputMethod_ErrorCode}。
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_PreviewTextStyle_HasUnderlineColor(
    OH_InputMethod_PreviewTextStyle *style, bool *hasUnderlineColor);

#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_PREVIEW_TEXT_STYLE_CAPI_H

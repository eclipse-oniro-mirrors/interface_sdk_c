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
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Defines a set of RichEditor enum and interface.
 *
 * @since 24
 */

/**
 * @file rich_editor.h
 *
 * @brief Defines a set of RichEditor enum and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 24
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_RICH_EDITOR_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_RICH_EDITOR_H

#include <stdint.h>
#include <stdbool.h>
#include "text_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义文本编辑器的文本选择菜单选项。
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorSelectionMenuOptions OH_ArkUI_TextEditorSelectionMenuOptions;

/**
 * @brief 定义文本编辑器中没有输入内容时的提示文本选项。
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorPlaceholderOptions OH_ArkUI_TextEditorPlaceholderOptions;

/**
 * @brief 定义文本编辑器的属性字符串控制器。
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorStyledStringController OH_ArkUI_TextEditorStyledStringController;

/**
 * @brief 定义文本编辑器的段落样式。
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorParagraphStyle OH_ArkUI_TextEditorParagraphStyle;

/**
 * @brief 定义文本编辑器的文本样式。
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorTextStyle OH_ArkUI_TextEditorTextStyle;

/**
 * @brief 枚举振动效果类型。
 *
 * @since 24
 */
typedef enum {
    /**
     * 无震动效果。
     * @since 24
     */
    OH_ARKUI_HAPTIC_FEEDBACK_MODE_DISABLED = 0,
    /**
     * 有震动效果。
     * @since 24
     */
    OH_ARKUI_HAPTIC_FEEDBACK_MODE_ENABLED = 1,
    /**
     * 跟随系统的震动效果。
     * @since 24
     */
    OH_ARKUI_HAPTIC_FEEDBACK_MODE_AUTO = 2
} OH_ArkUI_HapticFeedbackMode;

/**
 * @brief 自定义文本选择菜单span类型枚举。
 *
 * @since 24
 */
typedef enum {
    /**
     * 文本Span
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_TEXT = 0,
    /**
     * 图片Span。
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_IMAGE = 1,
    /**
     * 混合span
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_MIXED = 2,
    /**
     * 自定义布局span。
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_BUILDER = 3,
    /**
     * 默认span。
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_DEFAULT = 4
} OH_ArkUI_TextEditorSpanType;

/**
 * @brief 自定义文本选择菜单响应类型枚举。
 *
 * @since 24
 */
typedef enum {
    /**
     * 通过鼠标右键触发菜单弹出。
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_RESPONSE_TYPE_RIGHT_CLICK = 0,
    /**
     * 通过长按触发菜单弹出。
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_RESPONSE_TYPE_LONG_PRESS = 1,
    /**
     * 通过鼠标选中触发菜单弹出。
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_RESPONSE_TYPE_SELECT = 2,
    /**
     * 默认响应类型。
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_RESPONSE_TYPE_DEFAULT = 3
} OH_ArkUI_TextEditorResponseType;

/**
 * @brief 文本菜单类型枚举。
 *
 * @since 24
 */
typedef enum {
    /**
     * 文本选择菜单。
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SELECTION_MENU = 0,
    /**
     * 预览菜单。
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_PREVIEW_MENU = 1
} OH_ArkUI_TextMenuType;

/**
 * @brief 为无输入时使用的占位符文本创建选项对象。当对象不再是
 * 使用时，调用{@link OH_ArkUI_TextEditorPlaceholderOptions_Destroy}将其销毁。
 *
 * @return 指向{@link OH_ArkUI_TextEditorPlaceholderOptions}对象的指针。
 * @since 24
 */
OH_ArkUI_TextEditorPlaceholderOptions* OH_ArkUI_TextEditorPlaceholderOptions_Create();

/**
 * @brief 销毁没有输入时使用的占位符文本的选项对象。
 *
 * @param options 指向{@link OH_ArkUI_TextEditorPlaceholderOptions}对象的指针。
 * @since 24
 */
void OH_ArkUI_TextEditorPlaceholderOptions_Destroy(OH_ArkUI_TextEditorPlaceholderOptions* options);

/**
 * @brief 为文本编辑器创建一个带样式的字符串控制器对象。当对象不再使用时，调用
 * {@链接OH_ArkUI_TextEditorStyledStringController_Destroy}来销毁它。
 *
 * @return 指向{@link OH_ArkUI_TextEditorStyledStringController}对象的指针。
 * @since 24
 */
OH_ArkUI_TextEditorStyledStringController* OH_ArkUI_TextEditorStyledStringController_Create();

/**
 * @brief 销毁样式化的字符串控制器对象。
 *
 * @param controller 指向{@link OH_ArkUI_TextEditorStyledStringController}对象的指针。
 * @since 24
 */
void OH_ArkUI_TextEditorStyledStringController_Destroy(OH_ArkUI_TextEditorStyledStringController* controller);

/**
 * @brief 为文本编辑器创建段落样式对象。当对象不再使用时，调用
 * {@链接OH_ArkUI_TextEditorParagraphStyle_Destroy}来销毁它。
 *
 * @return 指向{@link OH_ArkUI_TextEditorParagraphStyle}对象的指针。
 * @since 24
 */
OH_ArkUI_TextEditorParagraphStyle* OH_ArkUI_TextEditorParagraphStyle_Create();

/**
 * @brief 销毁段落样式对象。
 *
 * @param style 指向{@link OH_ArkUI_TextEditorParagraphStyle}对象的指针。
 * @since 24
 */
void OH_ArkUI_TextEditorParagraphStyle_Destroy(OH_ArkUI_TextEditorParagraphStyle* style);

/**
 * @brief 创建文本样式对象。当对象不再使用时，调用
 * {@链接OH_ArkUI_TextEditorTextStyle_Destroy}来销毁它。
 *
 * @return 指向{@link OH_ArkUI_TextEditorTextStyle}对象的指针。
 * @since 24
 */
OH_ArkUI_TextEditorTextStyle* OH_ArkUI_TextEditorTextStyle_Create();

/**
 * @brief 销毁文本样式对象。
 *
 * @param style 指向{@link OH_ArkUI_TextEditorTextStyle}对象的指针。
 * @since 24
 */
void OH_ArkUI_TextEditorTextStyle_Destroy(OH_ArkUI_TextEditorTextStyle* style);

/**
 * @brief 创建文本编辑器的文本选择菜单选项对象。当对象不再使用时，调用
 * {@链接OH_ArkUI_TextEditorSelectionMenuOptions_Destroy}来销毁它。
 *
 * @return 指向{@link OH_ArkUI_TextEditorSelectionMenuOptions}对象的指针。
 * @since 24
 */
OH_ArkUI_TextEditorSelectionMenuOptions* OH_ArkUI_TextEditorSelectionMenuOptions_Create();
#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_RICH_EDITOR_H

/**
 * @brief Destroys the text selection menu option object of the text editor.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @since 24
 */
void OH_ArkUI_TextEditorSelectionMenuOptions_Destroy(OH_ArkUI_TextEditorSelectionMenuOptions* options);
/** @} */
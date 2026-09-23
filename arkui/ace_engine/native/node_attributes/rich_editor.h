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
 * @brief Defines structs, enumerations, and APIs related to <b>RichEditor</b>. <b>RichEditor</b> provides rich
 * text editing capabilities, supporting custom text selection menus, styled string controllers, paragraph and
 * text style settings, and haptic feedback control. It is suitable for scenarios where rich text editing and
 * custom interaction menus need to be implemented in applications.
 *
 * @since 24
 */

/**
 * @file rich_editor.h
 *
 * @brief Defines structs, enumerations, and APIs related to <b>RichEditor</b>. <b>RichEditor</b> provides rich
 * text editing capabilities, supporting custom text selection menus, styled string controllers, paragraph and
 * text style settings, and haptic feedback control. It is suitable for scenarios where rich text editing and
 * custom interaction menus need to be implemented in applications.
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
 * @brief Defines the text selection menu options of a text editor, which are used to customize the content of
 * the text selection menu. It supports you in adding, replacing, or removing menu items based on service
 * requirements, and is applicable to scenarios that require text operation menu customization, such as adding
 * custom operation items like "Translate", "Search", and "Share", or replacing the default menu options.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorSelectionMenuOptions OH_ArkUI_TextEditorSelectionMenuOptions;

/**
 * @brief Defines the placeholder text options for a text editor when there is no input. When the text editor
 * content is empty, the placeholder text is displayed based on these options. After the user enters content,
 * the placeholder text is automatically hidden. This is applicable to scenarios where input guidance needs to
 * be provided for users.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorPlaceholderOptions OH_ArkUI_TextEditorPlaceholderOptions;

/**
 * @brief Defines the styled string controller of a text editor, which supports operations such as setting and
 * obtaining a styled string, setting an input style, and controlling the cursor. It can be used to adjust the
 * cursor position, set the selection, obtain the preview text, and perform backward deletion.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorStyledStringController OH_ArkUI_TextEditorStyledStringController;

/**
 * @brief Defines the paragraph style of a text editor, which describes the formatting attributes of paragraphs
 * in a text editor. You can call related APIs to set and obtain the paragraph style. It applies to scenarios
 * where style attributes such as the paragraph alignment, indentation, and line spacing need to be set.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorParagraphStyle OH_ArkUI_TextEditorParagraphStyle;

/**
 * @brief Defines the text style of a text editor, which supports the setting of text attributes such as the
 * font, color, and size. It applies to scenarios where the content style of a text editor needs to be
 * controlled, helping you flexibly customize the display effect of text in the editor. For example, in a rich
 * text editor, you can set styles such as the font, color, and size for different paragraphs or text.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorTextStyle OH_ArkUI_TextEditorTextStyle;

/**
 * @brief Enumerates vibration effect types.
 *
 * @since 24
 */
typedef enum {
    /**
     * No vibration.
     * @since 24
     */
    OH_ARKUI_HAPTIC_FEEDBACK_MODE_DISABLED = 0,
    /**
     * Vibration.
     * @since 24
     */
    OH_ARKUI_HAPTIC_FEEDBACK_MODE_ENABLED = 1,
    /**
     * System vibration.
     * @since 24
     */
    OH_ARKUI_HAPTIC_FEEDBACK_MODE_AUTO = 2,
} OH_ArkUI_HapticFeedbackMode;

/**
 * @brief Enumerates the span types of a custom text selection menu, which are used to identify the span type
 * of the text selection menu in the text editor. Different span types correspond to different content structures,
 * affecting the display and interaction behavior of the custom menu. For example, the
 * <b>OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_TEXT</b> type is used when the user selects only text content, the
 * <b>OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_MIXED</b> type is used when the selection contains mixed content such as
 * text and images, and the <b>OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_BUILDER</b> type is used when a custom menu item
 * layout is required.
 *
 * @since 24
 */
typedef enum {
    /**
     * Text span.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_TEXT = 0,
    /**
     * Image span.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_IMAGE = 1,
    /**
     * Mixed span.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_MIXED = 2,
    /**
     * Custom layout span.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_BUILDER = 3,
    /**
     * Default span.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_DEFAULT = 4
} OH_ArkUI_TextEditorSpanType;

/**
 * @brief Enumerates the response types of a custom text selection menu, which are used to identify the
 * interaction method that triggers the menu pop-up. Different response types correspond to different user
 * operations (such as right-click, long press, and mouse-based selection), allowing different menu content
 * to be customized based on the response type.
 *
 * @since 24
 */
typedef enum {
    /**
     * The menu is displayed when the component is right-clicked.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_RESPONSE_TYPE_RIGHT_CLICK = 0,
    /**
     * The menu is displayed when the component is long-pressed.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_RESPONSE_TYPE_LONG_PRESS = 1,
    /**
     * The menu is displayed when the component is selected.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_RESPONSE_TYPE_SELECT = 2,
    /**
     * Default response type.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_RESPONSE_TYPE_DEFAULT = 3,
} OH_ArkUI_TextEditorResponseType;

/**
 * @brief Enumerates text menu types, which are used to distinguish different types of pop-up menus in the text
 * editor, including the text selection menu and the preview menu. Different menu types correspond to different
 * interaction scenarios and menu display modes. For example, the text selection menu pops up when the user
 * selects text and is used for text operations such as copy and delete; the preview menu pops up when the user
 * long-presses an image and is used to trigger image content drag preview as well as copy and deletion
 * operations.
 *
 * @since 24
 */
typedef enum {
    /**
     * Text selection menu.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SELECTION_MENU = 0,
    /**
     * Preview menu.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_PREVIEW_MENU = 1,
} OH_ArkUI_TextMenuType;


/**
 * @brief Creates an option object for the placeholder text used when there is no input. When the object is no longer
 * used, call {@link OH_ArkUI_TextEditorPlaceholderOptions_Destroy} to destroy it.
 *
 * @return Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @since 24
 */
OH_ArkUI_TextEditorPlaceholderOptions* OH_ArkUI_TextEditorPlaceholderOptions_Create();

/**
 * @brief Destroys the option object for the placeholder text used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @since 24
 */
void OH_ArkUI_TextEditorPlaceholderOptions_Destroy(OH_ArkUI_TextEditorPlaceholderOptions* options);

/**
 * @brief Creates a styled string controller object, which is used to control the styled string of the text
 * editor when rich text content needs to be managed through styled strings (such as mixed layout of text and
 * images, dynamic setting of paragraph or character styles, and other scenarios). When the object is no longer
 * used, call {@link OH_ArkUI_TextEditorStyledStringController_Destroy} to destroy it.
 *
 * @return Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @since 24
 */
OH_ArkUI_TextEditorStyledStringController* OH_ArkUI_TextEditorStyledStringController_Create();

/**
 * @brief Destroys the styled string controller object.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @since 24
 */
void OH_ArkUI_TextEditorStyledStringController_Destroy(OH_ArkUI_TextEditorStyledStringController* controller);

/**
 * @brief Creates a paragraph style object for the text editor. When the object is no longer used, call
 * {@link OH_ArkUI_TextEditorParagraphStyle_Destroy} to destroy it.
 *
 * @return Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @since 24
 */
OH_ArkUI_TextEditorParagraphStyle* OH_ArkUI_TextEditorParagraphStyle_Create();

/**
 * @brief Destroys the paragraph style object.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @since 24
 */
void OH_ArkUI_TextEditorParagraphStyle_Destroy(OH_ArkUI_TextEditorParagraphStyle* style);

/**
 * @brief Creates a text style object. When the object is no longer used, call
 * {@link OH_ArkUI_TextEditorTextStyle_Destroy} to destroy it.
 *
 * @return Pointer to the {@link OH_ArkUI_TextEditorTextStyle} object.
 * @since 24
 */
OH_ArkUI_TextEditorTextStyle* OH_ArkUI_TextEditorTextStyle_Create();

/**
 * @brief Destroys the text style object.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorTextStyle} object.
 * @since 24
 */
void OH_ArkUI_TextEditorTextStyle_Destroy(OH_ArkUI_TextEditorTextStyle* style);

/**
 * @brief Creates a text selection menu option object of the text editor. When the object is no longer used, call
 * {@link OH_ArkUI_TextEditorSelectionMenuOptions_Destroy} to destroy it.
 *
 * @return Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @since 24
 */
OH_ArkUI_TextEditorSelectionMenuOptions* OH_ArkUI_TextEditorSelectionMenuOptions_Create();

/**
 * @brief Destroys the text selection menu option object of the text editor.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @since 24
 */
void OH_ArkUI_TextEditorSelectionMenuOptions_Destroy(OH_ArkUI_TextEditorSelectionMenuOptions* options);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_RICH_EDITOR_H
/** @} */

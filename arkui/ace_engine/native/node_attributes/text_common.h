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
 * @brief Defines a set of text common enum and interface.
 *
 * @since 12
 */

/**
 * @file text_common.h
 *
 * @brief Defines common text enumerations and APIs, covering text alignment, decoration line styles, copy and paste,
 * overflow handling, line break policies, and menu customization. It is applicable to scenarios such as text boxes and
 * text display, helping you flexibly control text styles and interaction behavior while reducing development
 * complexity.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_COMMON_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_COMMON_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the styled string descriptor object supported by the text component, which is used for style setting
 * and management of text content. It applies to scenarios such as rich text display and style customization.
 *
 * @since 14
 */
typedef struct ArkUI_StyledString_Descriptor ArkUI_StyledString_Descriptor;

/**
 * @brief Defines the counter configuration of a text input box for managing character counting. It applies to
 * scenarios where character count limits and real-time prompts are required for user input, helping users track input
 * progress and prevent exceeding the character limit.
 *
 * @since 22
 */
typedef struct ArkUI_ShowCounterConfig ArkUI_ShowCounterConfig;

/**
 * @brief Defines a text content base controller, providing content control capabilities for text components and
 * supporting operations such as obtaining, setting, and updating text content. It is suitable for scenarios that
 * require dynamic content management and real-time control of text components, helping you manage text display content
 * more flexibly.
 *
 * @since 23
 */
typedef struct ArkUI_TextContentBaseController ArkUI_TextContentBaseController;

/**
 * @brief Enumerates text horizontal alignment styles.
 *
 * @since 12
 */
typedef enum {
    /** Aligned with the start. */
    ARKUI_TEXT_ALIGNMENT_START = 0,
    /** Horizontally centered. */
    ARKUI_TEXT_ALIGNMENT_CENTER,
    /** Aligned with the end. */
    ARKUI_TEXT_ALIGNMENT_END,
    /** Aligned with both margins. */
    ARKUI_TEXT_ALIGNMENT_JUSTIFY,
    /** Aligned with left to right.
     * @since 23
     */
    ARKUI_TEXT_ALIGNMENT_LEFT_TO_RIGHT = 4,
    /** Aligned with right to left.
     * @since 23
     */
    ARKUI_TEXT_ALIGNMENT_RIGHT_TO_LEFT = 5
} ArkUI_TextAlignment;

/**
 * @brief Enumerates text vertical alignment styles.
 *
 * @since 20
 */
typedef enum {
    /** Aligned to the baseline. */
    ARKUI_TEXT_VERTICAL_ALIGNMENT_BASELINE = 0,
    /** Bottom aligned. */
    ARKUI_TEXT_VERTICAL_ALIGNMENT_BOTTOM,
    /** Center aligned. */
    ARKUI_TEXT_VERTICAL_ALIGNMENT_CENTER,
    /** Top aligned. */
    ARKUI_TEXT_VERTICAL_ALIGNMENT_TOP
} ArkUI_TextVerticalAlignment;

/**
 * @brief Enumerates vertical alignment styles in the text content area.
 *
 * @since 21
 */
typedef enum {
    /** Top aligned. */
    ARKUI_TEXT_CONTENT_ALIGN_TOP = 0,
    /** Center aligned. */
    ARKUI_TEXT_CONTENT_ALIGN_CENTER = 1,
    /** Bottom aligned. */
    ARKUI_TEXT_CONTENT_ALIGN_BOTTOM = 2
} ArkUI_TextContentAlign;

/**
 * @brief Enumerates text layout directions.
 *
 * @since 23
 */
typedef enum {
    /** The text direction is left to right. */
    ARKUI_TEXT_DIRECTION_LTR = 0,
    /** The text direction is right to left. */
    ARKUI_TEXT_DIRECTION_RTL = 1,
    /** The text direction follows the component layout. */
    ARKUI_TEXT_DIRECTION_DEFAULT = 2,
    /** The text direction follows the actual text. */
    ARKUI_TEXT_DIRECTION_AUTO = 3
} ArkUI_TextDirection;

/**
 * @brief Enumerates the types of the **Enter** key for single-line text input.
 *
 * @since 12
 */
typedef enum {
    /** The Enter key is labeled "Go." */
    ARKUI_ENTER_KEY_TYPE_GO = 2,
    /** The Enter key is labeled "Search." */
    ARKUI_ENTER_KEY_TYPE_SEARCH = 3,
    /** The Enter key is labeled "Send." */
    ARKUI_ENTER_KEY_TYPE_SEND,
    /** The Enter key is labeled "Next." */
    ARKUI_ENTER_KEY_TYPE_NEXT,
    /** The Enter key is labeled "Done." */
    ARKUI_ENTER_KEY_TYPE_DONE,
    /** The Enter key is labeled "Previous." */
    ARKUI_ENTER_KEY_TYPE_PREVIOUS,
    /** The Enter key is labeled "New Line." */
    ARKUI_ENTER_KEY_TYPE_NEW_LINE
} ArkUI_EnterKeyType;

/**
 * @brief Enumerates text decoration types.
 *
 * @since 12
 */
typedef enum {
    /** No text decoration. */
    ARKUI_TEXT_DECORATION_TYPE_NONE = 0,
    /** Line under the text. */
    ARKUI_TEXT_DECORATION_TYPE_UNDERLINE,
    /** Line over the text. */
    ARKUI_TEXT_DECORATION_TYPE_OVERLINE,
    /** Line through the text. */
    ARKUI_TEXT_DECORATION_TYPE_LINE_THROUGH
} ArkUI_TextDecorationType;

/**
 * @brief Enumerates text decoration styles.
 *
 * @since 12
 */
typedef enum {
    /** Single solid line. */
    ARKUI_TEXT_DECORATION_STYLE_SOLID = 0,
    /** Double solid line. */
    ARKUI_TEXT_DECORATION_STYLE_DOUBLE,
    /** Dotted line. */
    ARKUI_TEXT_DECORATION_STYLE_DOTTED,
    /** Dashed line. */
    ARKUI_TEXT_DECORATION_STYLE_DASHED,
    /** Wavy line. */
    ARKUI_TEXT_DECORATION_STYLE_WAVY
} ArkUI_TextDecorationStyle;

/**
 * @brief Enumerates text cases.
 *
 * @since 12
 */
typedef enum {
    /** The original case of the text is retained. */
    ARKUI_TEXT_CASE_NORMAL = 0,
    /** All letters in the text are in lowercase. */
    ARKUI_TEXT_CASE_LOWER,
    /** All letters in the text are in uppercase. */
    ARKUI_TEXT_CASE_UPPER
} ArkUI_TextCase;

/**
 * @brief Enumerates copy options, which define whether copy and paste is allowed for text content.
 *
 * @since 12
 */
typedef enum {
    /** Copy is not allowed. */
    ARKUI_TEXT_COPY_OPTIONS_NONE = 0,
    /** Intra-application copy is allowed. */
    ARKUI_TEXT_COPY_OPTIONS_IN_APP,
    /** Intra-device copy is allowed. */
    ARKUI_TEXT_COPY_OPTIONS_LOCAL_DEVICE,
    /** Cross-device copy is allowed. */
    ARKUI_TEXT_COPY_OPTIONS_CROSS_DEVICE
} ArkUI_TextCopyOptions;

/**
 * @brief Enumerates the display modes when the text is too long.
 *
 * @since 12
 */
typedef enum {
    /** Extra-long text is not clipped. */
    ARKUI_TEXT_OVERFLOW_NONE = 0,
    /** Extra-long text is clipped. */
    ARKUI_TEXT_OVERFLOW_CLIP,
    /** An ellipsis (...) is used to represent text overflow. */
    ARKUI_TEXT_OVERFLOW_ELLIPSIS,
    /** Text continuously scrolls when text overflow occurs. */
    ARKUI_TEXT_OVERFLOW_MARQUEE
} ArkUI_TextOverflow;

/**
 * @brief Enumerates word break rules.
 *
 * @since 12
 */
typedef enum {
    /** Word breaks can occur between any two characters for Chinese, Japanese, and Korean (CJK) text, but can occur
     *  only at a space character for non-CJK text (such as English). */
    ARKUI_WORD_BREAK_NORMAL = 0,
    /** Word breaks can occur between any two characters for non-CJK text. CJK text behavior is the same as for
     *  <b>NORMAL</b>. */
    ARKUI_WORD_BREAK_BREAK_ALL,
    /** This option has the same effect as <b>BREAK_ALL</b> for non-CJK text, except that if it preferentially wraps
     *  lines at appropriate characters (for example, spaces) whenever possible.
     CJK text behavior is the same as for <b>NORMAL</b>. */
    ARKUI_WORD_BREAK_BREAK_WORD,
    /**
     * @brief Line breaks can occur between any two syllabic units for non-CJK text.
     * CJK text behavior is the same as for <b>NORMAL</b>.
     * @since 18
     */
    ARKUI_WORD_BREAK_HYPHENATION
} ArkUI_WordBreak;

/**
 * @brief Enumerates ellipsis positions.
 *
 * @since 12
 */
typedef enum {
    /** An ellipsis is used at the start of the line of text. */
    ARKUI_ELLIPSIS_MODE_START = 0,
    /** An ellipsis is used at the center of the line of text. */
    ARKUI_ELLIPSIS_MODE_CENTER,
    /** An ellipsis is used at the end of the line of text. */
    ARKUI_ELLIPSIS_MODE_END,
    /**
     * @brief An ellipsis is used at the start of the line of text for multiline and single line.
     * @since 24
     */
    ARKUI_ELLIPSIS_MODE_MULTILINE_START,
    /**
     * @brief An ellipsis is used at the center of the line of text for multiline and single line.
     * @since 24
     */
    ARKUI_ELLIPSIS_MODE_MULTILINE_CENTER
} ArkUI_EllipsisMode;

/**
 * @brief Enumerates the appearance of the keyboard when the text box is focused.
 *
 * @since 15
 */
typedef enum {
    /**
     * Default appearance mode, won't adopt immersive styles.
     * @since 15
     */
    ARKUI_KEYBOARD_APPEARANCE_NONE_IMMERSIVE = 0,
    /**
     * Immersive mode.
     * @since 15
     */
    ARKUI_KEYBOARD_APPEARANCE_IMMERSIVE = 1,
    /**
     * Light immersive style.
     * @since 15
     */
    ARKUI_KEYBOARD_APPEARANCE_LIGHT_IMMERSIVE = 2,
    /**
     * Dark immersive style.
     * @since 15
     */
    ARKUI_KEYBOARD_APPEARANCE_DARK_IMMERSIVE = 3
} ArkUI_KeyboardAppearance;

/**
 * @brief Defines a text menu item, used to represent a single menu item in a text selection menu. This struct supports
 * setting attributes such as the title, icon, and enabled state of the menu item. It is applicable to scenarios where
 * you need to customize text selection menu content and menu item extension, helping you flexibly customize the text
 * selection menu.
 *
 * @since 22
 */
typedef struct ArkUI_TextMenuItem ArkUI_TextMenuItem;

/**
 * @brief Defines an array of text menu items, which carries data of multiple text menu items in a text selection menu
 * or context menu scenario.
 *
 * @since 22
 */
typedef struct ArkUI_TextMenuItemArray ArkUI_TextMenuItemArray;

/**
 * @brief Enumerates the IDs of text menu items.
 *
 * @since 22
 */
typedef enum {
    /**
     * Indicates the TextMenuItemId to copy and delete the currently selected text.
     */
    ARKUI_TEXT_MENU_ITEM_ID_CUT = 0,

    /**
     * Indicates the TextMenuItemId to copy the currently selected text to the clipboard.
     */
    ARKUI_TEXT_MENU_ITEM_ID_COPY = 1,

    /**
     * Indicates the TextMenuItemId to copy the current contents of the clipboard into the text view.
     */
    ARKUI_TEXT_MENU_ITEM_ID_PASTE = 2,

    /**
     * Indicates the TextMenuItemId to select all text in a text view.
     */
    ARKUI_TEXT_MENU_ITEM_ID_SELECT_ALL = 3,

    /**
     * Indicates the TextMenuItemId for collaboration service menu items.
     */
    ARKUI_TEXT_MENU_ITEM_ID_COLLABORATION_SERVICE = 4,

    /**
     * Indicates the TextMenuItemId to recognize the text in the picture and input it into the text view.
     */
    ARKUI_TEXT_MENU_ITEM_ID_CAMERA_INPUT = 5,

    /**
     * Indicates the TextMenuItemId to help with text creation by invoking large models.
     */
    ARKUI_TEXT_MENU_ITEM_ID_AI_WRITER = 6,

    /**
     * Indicates the TextMenuItemId to translate the selected content.
     */
    ARKUI_TEXT_MENU_ITEM_ID_TRANSLATE = 7,

    /**
     * Indicates the TextMenuItemId to search the selected content.
     */
    ARKUI_TEXT_MENU_ITEM_ID_SEARCH = 8,

    /**
     * Indicates the TextMenuItemId to share the selected content.
     */
    ARKUI_TEXT_MENU_ITEM_ID_SHARE = 9,

    /**
     * Indicates the TextMenuItemId to open url.
     */
    ARKUI_TEXT_MENU_ITEM_ID_URL = 10,

    /**
     * Indicates the TextMenuItemId to open email.
     */
    ARKUI_TEXT_MENU_ITEM_ID_EMAIL = 11,

    /**
     * Indicates the TextMenuItemId to call the phone number.
     */
    ARKUI_TEXT_MENU_ITEM_ID_PHONE_NUMBER = 12,

    /**
     * Indicates the TextMenuItemId to open map.
     */
    ARKUI_TEXT_MENU_ITEM_ID_ADDRESS = 13,

    /**
     * Indicates the TextMenuItemId to open calendar.
     */
    ARKUI_TEXT_MENU_ITEM_ID_DATA_TIME = 14,

    /**
     * Indicates the TextMenuItemId for asking AI.
     */
    ARKUI_TEXT_MENU_ITEM_ID_ASK_AI = 15,

    /**
     * Autofill. For example, the account and password can be automatically filled.
     * @since 24
     */
    ARKUI_TEXT_MENU_ITEM_ID_AUTO_FILL = 16,

    /**
     * Password vault.
     * @since 24
     */
    ARKUI_TEXT_MENU_ITEM_ID_PASSWORD_VAULT = 17,

    /**
     * Inclusive begin of app-reserved ID range.
     */
    ARKUI_TEXT_MENU_ITEM_ID_APP_RESERVED_BEGIN = 10000,

    /**
     * Inclusive end of app-reserved ID range.
     */
    ARKUI_TEXT_MENU_ITEM_ID_APP_RESERVED_END = 20000
} ArkUI_TextMenuItemId;

/**
 * @brief Defines editable text menu extension options, used to extend the functionality of the text editing menu. It
 * is applicable to scenarios where you need to customize text editing menu operations.
 *
 * @since 22
 */
typedef struct ArkUI_TextEditMenuOptions ArkUI_TextEditMenuOptions;

/**
 * Callback for the text menu creation event. This callback is triggered when a text menu is created, allowing you to
 * set menu data in it.
 * @param items Pointer to the **ArkUI_TextMenuItemArray** object, which is created and released by the system. You can
 *     call {@link OH_ArkUI_TextMenuItemArray_Insert} and {@link OH_ArkUI_TextMenuItemArray_Erase} to modify the array
 *     in the callback.
 * @param userData Pointer to the user-defined data, which is passed by you when registering the callback and returned
 *     as-is when the callback is triggered. It is used to obtain context data in the callback. The value **null**
 *     indicates that no custom data is passed.
 * @since 22
 */
typedef void (*ArkUI_TextCreateMenuCallback)(
    ArkUI_TextMenuItemArray*    items,
    void*                       userData
);

/**
 * Callback for the text menu preparation event. This callback is called when the text selection area changes and
 * before the menu is displayed, allowing you to set menu data in it.
 * @param items Pointer to the **ArkUI_TextMenuItemArray** object, which is created and released by the system. You can
 *     call {@link OH_ArkUI_TextMenuItemArray_Insert} and {@link OH_ArkUI_TextMenuItemArray_Erase} to modify the array
 *     in the callback.
 * @param userData Pointer to the user-defined data, which is passed by you when registering the callback and returned
 *     as-is when the callback is triggered. It is used to obtain context data in the callback. The value **null**
 *     means no custom data is passed.
 * @since 22
 */
typedef void (*ArkUI_TextPrepareMenuCallback)(
    ArkUI_TextMenuItemArray*    items,
    void*                       userData
);

/**
 * The text menu item click callback function.
 *
 * @param item The menu item click.
 * @param start The start offset of the selected content.
 * @param end The end offset of the selected content.
 * @param userData The user data.
 * @return bool Return True, the event is consumed, false otherwise.
 * @since 22
 */
typedef bool (*ArkUI_TextMenuItemClickCallback)(
    const ArkUI_TextMenuItem*    item,
    int32_t                      start,
    int32_t                      end,
    void*                        userData
);

/**
 * @brief Defines the options of a custom text selection menu, supporting custom configuration of menu content, styles,
 * and behavior. It is applicable to scenarios where the text selection menu interaction needs to be customized.
 *
 * @since 22
 */
typedef struct ArkUI_TextSelectionMenuOptions ArkUI_TextSelectionMenuOptions;

/**
 * @brief Defines decoration style options, which are used to add decorative line effects to text. You can set the type
 * (such as underline, strikethrough, and overline), style (such as solid, dashed, and wavy), and color of the
 * decorative line. Typical use cases include adding an underline to link text, adding a strikethrough to deleted
 * content, and adding an overline to important text.
 *
 * @since 24
 */
typedef struct OH_ArkUI_DecorationStyleOptions OH_ArkUI_DecorationStyleOptions;

/**
 * @brief Enumerates line break policies.
 *
 * @since 24
 */
typedef enum {
    /**
     * Greedy mode.<br>Places as many words on a line as possible and moves to the next line only if no more words can
     * fit into the same line.
     * @since 24
     */
    OH_ARKUI_LINE_BREAK_STRATEGY_GREEDY = 0,
    /**
     * High-quality mode.<br>Fills in lines as much as possible on the basis of **BALANCED**, which may results in a
     * large blank area on the last line.
     * @since 24
     */
    OH_ARKUI_LINE_BREAK_STRATEGY_HIGH_QUALITY = 1,
    /**
     * Balance mode.<br>Without splitting words, the width of each line in a paragraph is the same as much as possible.
     * @since 24
     */
    OH_ARKUI_LINE_BREAK_STRATEGY_BALANCE = 2
} OH_ArkUI_LineBreakStrategy;

/**
 * @brief Enumerates the join styles of a text stroke.
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * Miter join. The text stroke joins with a sharp corner.
     * @since 26.2.0
     */
    OH_ARKUI_STROKE_JOIN_STYLE_MITER_JOIN = 0,
    /**
     * Round join. The text stroke joins with a rounded corner.
     * @since 26.2.0
     */
    OH_ARKUI_STROKE_JOIN_STYLE_ROUND_JOIN = 1,
    /**
     * Bevel join. The text stroke joins with a beveled corner.
     * @since 26.2.0
     */
    OH_ARKUI_STROKE_JOIN_STYLE_BEVEL_JOIN = 2,
} OH_ArkUI_StrokeJoinStyle;

/**
 * @brief Enumerates the text span type.
 *
 * @since 22
 */
typedef enum {
    /** The span type only contains text. */
    ARKUI_TEXT_SPAN_TYPE_TEXT = 0,
    /** The span type only contains image. */
    ARKUI_TEXT_SPAN_TYPE_IMAGE = 1,
    /** The span type contains both text and image. */
    ARKUI_TEXT_SPAN_TYPE_MIXED = 2,
    /**
     * When no other types are explicitly specified, this type will be matched.
     * When this type is registered but TEXT, IMAGE, or MIXED types are not registered,
     * this type will be triggered and displayed for those registered types.
     */
    ARKUI_TEXT_SPAN_TYPE_DEFAULT = 3
} ArkUI_TextSpanType;

/**
 * @brief Enumerates the response types of a custom text selection menu.
 *
 * @since 22
 */
typedef enum {
    /** The response type of right click. */
    ARKUI_TEXT_RESPONSE_TYPE_RIGHT_CLICK = 0,
    /** The response type of long press. */
    ARKUI_TEXT_RESPONSE_TYPE_LONG_PRESS = 1,
    /** The response type of select by mouse. */
    ARKUI_TEXT_RESPONSE_TYPE_SELECT = 2,
    /**
     * When no other types are explicitly specified, this type will be matched.
     * When this type is registered but RIGHT_CLICK, LONG_PRESS, or SELECT types are not registered,
     * this type will be triggered and displayed for right-click, long press, and mouse selection actions.
     */
    ARKUI_TEXT_RESPONSE_TYPE_DEFAULT = 3
} ArkUI_TextResponseType;

/**
 * @brief Creates a text input counter configuration object. When this object is no longer used, call
 * {@link OH_ArkUI_ShowCounterConfig_Dispose} to dispose of it.
 *
 * @return Pointer to the text input counter configuration object.
 * @since 22
 */
ArkUI_ShowCounterConfig* OH_ArkUI_ShowCounterConfig_Create();

/**
 * @brief Disposes of the text input counter configuration object created by {@link OH_ArkUI_ShowCounterConfig_Create}.
 *
 * @param config Pointer to the text input counter configuration object to be disposed of.
 * @since 22
 */
void OH_ArkUI_ShowCounterConfig_Dispose(ArkUI_ShowCounterConfig* config);

/**
 * @brief Sets the text color of the counter when the text input has not reached the maximum character limit. If this
 * API is not called, the default color is **0x66182431**, displayed as gray.
 *
 * @param config Pointer to the text input counter configuration object. It must be created using **
 *     OH_ArkUI_ShowCounterConfig_Create()** before use.
 * @param color Text color of the counter when the text input has not reached the maximum character limit, in 0xARGB
 *     format.
 * @since 22
 */
void OH_ArkUI_ShowCounterConfig_SetCounterTextColor(ArkUI_ShowCounterConfig* config, uint32_t color);

/**
 * @brief Sets the text color of the counter when the text input exceeds the maximum character limit. If this API is
 * not called, the default color is **0x99FA2A2D**, displayed as red.
 *
 * @param config Pointer to the text input counter configuration object.
 * @param color Text color of the counter when the text input exceeds the maximum character limit, in 0xARGB format.
 * @since 22
 */
void OH_ArkUI_ShowCounterConfig_SetCounterTextOverflowColor(ArkUI_ShowCounterConfig* config, uint32_t color);

/**
 * @brief Obtains the text color of the counter when the text input has not reached the maximum character limit.
 *
 * @param config Pointer to the text input counter configuration object.
 * @return Text color of the counter when the text input has not reached the maximum character limit, in 0xARGB format.
 *     **0** is returned if the color is not set using {@link OH_ArkUI_ShowCounterConfig_SetCounterTextColor};
 *     otherwise, the set color value is returned.
 * @since 22
 */
uint32_t OH_ArkUI_ShowCounterConfig_GetCounterTextColor(ArkUI_ShowCounterConfig* config);

/**
 * @brief Obtains the text color of the counter when the text input exceeds the maximum character limit.
 *
 * @param config Pointer to the text input counter configuration object.
 * @return Text color of the counter when the text input exceeds the maximum character limit, in 0xARGB format. **0**
 *     is returned if the color is not set using {@link OH_ArkUI_ShowCounterConfig_SetCounterTextOverflowColor};
 *     otherwise, the set color value is returned.
 * @since 22
 */
uint32_t OH_ArkUI_ShowCounterConfig_GetCounterTextOverflowColor(ArkUI_ShowCounterConfig* config);

/**
 * @brief Creates a text menu item object for customizing the text selection menu or extending the system menu. It is
 * applicable when custom menu items need to be added, such as sharing to a specific platform or performing custom
 * editing operations. When this object is no longer used, call {@link OH_ArkUI_TextMenuItem_Dispose} to dispose of it.
 *
 * @return Pointer to the text menu item object, used to represent a single menu item in the text selection menu.
 * @since 22
 */
ArkUI_TextMenuItem* OH_ArkUI_TextMenuItem_Create();

/**
 * @brief Disposes of the text menu item object created by {@link OH_ArkUI_TextMenuItem_Create}.
 *
 * @param textMenuItem Pointer to the **ArkUI_TextMenuItem** object.
 * @since 22
 */
void OH_ArkUI_TextMenuItem_Dispose(ArkUI_TextMenuItem* textMenuItem);

/**
 * @brief Creates a text menu extension object for extending the text editing menu functionality. It is applicable when
 * custom menu items need to be added to the text editing component, such as inserting special characters or performing
 * quick formatting. When this object is no longer used, call {@link OH_ArkUI_TextEditMenuOptions_Dispose} to dispose
 * of it.
 *
 * @return Pointer to the text menu extension object, used to extend the functionality of the text editing menu.
 * @since 22
 */
ArkUI_TextEditMenuOptions* OH_ArkUI_TextEditMenuOptions_Create();

/**
 * @brief Disposes of the text menu extension object created by {@link OH_ArkUI_TextEditMenuOptions_Create}.
 *
 * @param editMenuOptions Pointer to the **ArkUI_TextEditMenuOptions** object.
 * @since 22
 */
void OH_ArkUI_TextEditMenuOptions_Dispose(ArkUI_TextEditMenuOptions* editMenuOptions);

/**
 * @brief Creates a custom text selection menu object for configuring the content and behavior of the text selection
 * menu. It is applicable when the text selection menu needs to be fully customized, such as replacing the default menu
 * and adding application-specific operations. When this object is no longer used, call
 * {@link OH_ArkUI_TextSelectionMenuOptions_Dispose} to dispose of it.
 *
 * @return Pointer to the custom text selection menu object, used for custom configuration of menu content, styles, and
 *     behavior.
 * @since 22
 */
ArkUI_TextSelectionMenuOptions* OH_ArkUI_TextSelectionMenuOptions_Create();

/**
 * @brief Disposes of the custom text selection menu object created by {@link OH_ArkUI_TextSelectionMenuOptions_Create}.
 *
 * @param selectionMenuOptions Pointer to the **ArkUI_TextSelectionMenuOptions** object.
 * @since 22
 */
void OH_ArkUI_TextSelectionMenuOptions_Dispose(ArkUI_TextSelectionMenuOptions* selectionMenuOptions);

/**
 * @brief Creates a text content base controller object. When this object is no longer used, call
 * {@link OH_ArkUI_TextContentBaseController_Dispose} to dispose of it.
 *
 * @return Pointer to the text content base controller object, used for content control of text components, supporting
 *     operations such as obtaining, setting, and updating text content.
 * @since 23
 */
ArkUI_TextContentBaseController* OH_ArkUI_TextContentBaseController_Create();

/**
 * @brief Disposes of the text content base controller object created by
 * {@link OH_ArkUI_TextContentBaseController_Create}.
 *
 * @param {ArkUI_TextContentBaseController*} controller Pointer to the controller object to be disposed.
 * @since 23
 */
void OH_ArkUI_TextContentBaseController_Dispose(ArkUI_TextContentBaseController* controller);

/**
 * @brief Deletes the character before the cursor in editing state; deletes the last character of the text box
 * component in other states.
 *
 * @param {ArkUI_TextContentBaseController*} controller Pointer to the configuration object to be modified.
 * @since 23
 */
void OH_ArkUI_TextContentBaseController_DeleteBackward(ArkUI_TextContentBaseController* controller);

/**
 * @brief Passes the start and end indexes to the bound text box component, and scrolls the text within the range to
 * the visible area.
 *
 * @param {ArkUI_TextContentBaseController*} controller Pointer to the
 *     configuration object to be modified.
 * @param {int32_t} start Start text index.
 *     The start index must be less than or equal to the end index. Otherwise, the API call is invalid.
 *     The value range is [0, Total length of the text in the text box]. If the start index is less than 0,
 *     the start index is regarded as 0. If the start index is greater than the total length,
 *     the start indexis regarded as the total length.
 * @param {int32_t} end End text index.
 *     The end index must be greater than or equal to the start index. Otherwise, the API call is invalid.
 *     The value range is [0, Total length of the text in the text box]. If the end index is less than 0,
 *     the end index is regarded as 0. If the end index is greater than the total length,
 *     the end index is regarded as the total length.
 * @since 23
 */
void OH_ArkUI_TextContentBaseController_ScrollToVisible(
    ArkUI_TextContentBaseController *controller, int32_t start, int32_t end);

/**
 * @brief Creates a decoration style object for setting the type, style, and color of text decorative lines. It is
 * applicable when decoration effects such as underlines or strikethroughs need to be added to text, for example, in
 * rich text editors, hyperlink text, or price tags. When this object is no longer used, call
 * {@link OH_ArkUI_DecorationStyleOptions_Destroy} to destroy it.
 *
 * @return Pointer to the decoration style object, used to define the decorative line style.
 * @since 24
 */
OH_ArkUI_DecorationStyleOptions* OH_ArkUI_DecorationStyleOptions_Create();

/**
 * @brief Destroys the decoration style object created by {@link OH_ArkUI_DecorationStyleOptions_Create}.
 *
 * @param options Pointer to the option object to be destroyed.
 * @since 24
 */
void OH_ArkUI_DecorationStyleOptions_Destroy(OH_ArkUI_DecorationStyleOptions* options);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_COMMON_H
/** @} */
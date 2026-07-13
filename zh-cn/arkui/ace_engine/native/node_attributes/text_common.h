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
 * @brief Defines a set of text common enum and interface.
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
 * @brief Define the data objects of styled string supported by text components.
 *
 * @since 14
 */
typedef struct ArkUI_StyledString_Descriptor ArkUI_StyledString_Descriptor;
/**
 * @brief 定义textField的计数器配置。
 *
 * @since 22
 */
typedef struct ArkUI_ShowCounterConfig ArkUI_ShowCounterConfig;
/**
 * @brief 定义文本内容基础控制器。
 *
 * @since 23
 */
typedef struct ArkUI_TextContentBaseController ArkUI_TextContentBaseController;
/**
 * @brief 定义字体水平对齐样式枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 水平对齐首部。 */
    ARKUI_TEXT_ALIGNMENT_START = 0,
    /** 水平居中对齐。 */
    ARKUI_TEXT_ALIGNMENT_CENTER,
    /** 水平对齐尾部。 */
    ARKUI_TEXT_ALIGNMENT_END,
    /** 双端对齐。 */
    ARKUI_TEXT_ALIGNMENT_JUSTIFY,
    /** 从左到右对齐。
     * @since 23
     */
    ARKUI_TEXT_ALIGNMENT_LEFT_TO_RIGHT = 4,
    /** 从右到左对齐。
     * @since 23
     */
    ARKUI_TEXT_ALIGNMENT_RIGHT_TO_LEFT = 5
} ArkUI_TextAlignment;
/**
 * @brief 定义文本垂直对齐样式枚举值。
 *
 * @since 20
 */
typedef enum {
    /** 基线对齐。 */
    ARKUI_TEXT_VERTICAL_ALIGNMENT_BASELINE = 0,
    /** 底部对齐。 */
    ARKUI_TEXT_VERTICAL_ALIGNMENT_BOTTOM,
    /** 居中对齐。 */
    ARKUI_TEXT_VERTICAL_ALIGNMENT_CENTER,
    /** 顶部对齐。 */
    ARKUI_TEXT_VERTICAL_ALIGNMENT_TOP
} ArkUI_TextVerticalAlignment;
/**
 * @brief 定义文本内容区垂直对齐样式枚举值。
 *
 * @since 21
 */
typedef enum {
    /** 顶部对齐。 */
    ARKUI_TEXT_CONTENT_ALIGN_TOP = 0,
    /** 居中对齐。 */
    ARKUI_TEXT_CONTENT_ALIGN_CENTER = 1,
    /** 底部对齐。 */
    ARKUI_TEXT_CONTENT_ALIGN_BOTTOM = 2
} ArkUI_TextContentAlign;
/**
 * @brief 定义文本方向枚举值。
 *
 * @since 23
 */
typedef enum {
    /** 文本排版方向从左到右。 */
    ARKUI_TEXT_DIRECTION_LTR = 0,
    /** 文本排版方向从右到左。 */
    ARKUI_TEXT_DIRECTION_RTL = 1,
    /** 文本排版方向遵循组件布局。 */
    ARKUI_TEXT_DIRECTION_DEFAULT = 2,
    /** 遵循自身实际文本内容的排版方向，如果文本为
RTL（Right-to-Left）类语言（如藏文、维吾尔文），文本排版方向为从右到左。如果为
LTR（Left-to-Right）类语言（如中文、英文），文本排版方向为从左到右。 */
    ARKUI_TEXT_DIRECTION_AUTO = 3
} ArkUI_TextDirection;
/**
 * @brief 定义单行文本输入法回车键类型枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 显示为开始样式。 */
    ARKUI_ENTER_KEY_TYPE_GO = 2,
    /** 显示为搜索样式。 */
    ARKUI_ENTER_KEY_TYPE_SEARCH = 3,
    /** 显示为发送样式。 */
    ARKUI_ENTER_KEY_TYPE_SEND,
    /** 显示为下一个样式。 */
    ARKUI_ENTER_KEY_TYPE_NEXT,
    /** 显示为完成样式。 */
    ARKUI_ENTER_KEY_TYPE_DONE,
    /** 显示为上一个样式。 */
    ARKUI_ENTER_KEY_TYPE_PREVIOUS,
    /** 显示为换行样式。 */
    ARKUI_ENTER_KEY_TYPE_NEW_LINE
} ArkUI_EnterKeyType;
/**
 * @brief 定义装饰线类型枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 不使用装饰线。*/
    ARKUI_TEXT_DECORATION_TYPE_NONE = 0,
    /** 文字下划线修饰。*/
    ARKUI_TEXT_DECORATION_TYPE_UNDERLINE,
    /** 文字上划线修饰。*/
    ARKUI_TEXT_DECORATION_TYPE_OVERLINE,
    /** 穿过文本的修饰线。*/
    ARKUI_TEXT_DECORATION_TYPE_LINE_THROUGH
} ArkUI_TextDecorationType;
/**
 * @brief 定义装饰线样式枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 单实线。*/
    ARKUI_TEXT_DECORATION_STYLE_SOLID = 0,
    /** 双实线。*/
    ARKUI_TEXT_DECORATION_STYLE_DOUBLE,
    /** 点线。*/
    ARKUI_TEXT_DECORATION_STYLE_DOTTED,
    /** 虚线。*/
    ARKUI_TEXT_DECORATION_STYLE_DASHED,
    /** 波浪线。*/
    ARKUI_TEXT_DECORATION_STYLE_WAVY
} ArkUI_TextDecorationStyle;
/**
 * @brief 定义文本大小写枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 保持原有大小写。*/
    ARKUI_TEXT_CASE_NORMAL = 0,
    /** 文本全小写。*/
    ARKUI_TEXT_CASE_LOWER,
    /** 文本全大写。*/
    ARKUI_TEXT_CASE_UPPER
} ArkUI_TextCase;
/**
 * @brief 定义组件支持设置文本是否可复制粘贴。
 *
 * @since 12
 */
typedef enum {
    /** 不支持复制。 */
    ARKUI_TEXT_COPY_OPTIONS_NONE = 0,
    /** 支持应用内复制。*/
    ARKUI_TEXT_COPY_OPTIONS_IN_APP,
    /** 支持设备内复制。*/
    ARKUI_TEXT_COPY_OPTIONS_LOCAL_DEVICE,
    /** 支持跨设备复制。*/
    ARKUI_TEXT_COPY_OPTIONS_CROSS_DEVICE
} ArkUI_TextCopyOptions;
/**
 * @brief 定义文本超长时的显示方式。
 *
 * @since 12
 */
typedef enum {
    /** 文本超长时不裁剪显示。 */
    ARKUI_TEXT_OVERFLOW_NONE = 0,
    /** 文本超长时进行裁剪显示。 */
    ARKUI_TEXT_OVERFLOW_CLIP,
    /** 文本超长时显示不下的文本用省略号代替。 */
    ARKUI_TEXT_OVERFLOW_ELLIPSIS,
    /** 文本超长时以跑马灯的方式展示。 */
    ARKUI_TEXT_OVERFLOW_MARQUEE
} ArkUI_TextOverflow;
/**
 * @brief 定义文本断行规则。
 *
 * @since 12
 */
typedef enum {
    /** CJK(中文、日文、韩文)文本可以在任意2个字符间断行，而Non-CJK文本（如英文等）只能在空白符处断行。 */
    ARKUI_WORD_BREAK_NORMAL = 0,
    /** 对于Non-CJK的文本，可在任意2个字符间断行。CJK(中文、日文、韩文)文本可以在任意2个字符间断行。 */
    ARKUI_WORD_BREAK_BREAK_ALL,
    /** 对于Non-CJK的文本可在任意2个字符间断行，一行文本中有断行破发点（如空白符）时，优先按破发点换行。
对于CJK的文本，换行效果与NORMAL效果保持一致。 */
    ARKUI_WORD_BREAK_BREAK_WORD,
    /**
     * @brief 对于Non-CJK的文本，可以按照音节断行。对于CJK的文本，换行效果与NORMAL效果保持一致。
     * @since 18
     */
    ARKUI_WORD_BREAK_HYPHENATION
} ArkUI_WordBreak;
/**
 * @brief 定义文本省略位置。
 *
 * @since 12
 */
typedef enum {
    /** 省略行首内容。适用单行文本场景。*/
    ARKUI_ELLIPSIS_MODE_START = 0,
    /** 省略行中内容。适用单行文本场景。*/
    ARKUI_ELLIPSIS_MODE_CENTER,
    /** 省略行末内容。适用单行文本和多行文本场景。*/
    ARKUI_ELLIPSIS_MODE_END,
    /**
     * @brief 省略行首内容。适用单行文本和多行文本场景。
     * @since 24
     */
    ARKUI_ELLIPSIS_MODE_MULTILINE_START,
    /**
     * @brief 省略行中内容。适用单行文本和多行文本场景。
     * @since 24
     */
    ARKUI_ELLIPSIS_MODE_MULTILINE_CENTER
} ArkUI_EllipsisMode;
/**
 * @brief 定义输入框拉起的键盘样式。
 *
 * @since 15
 */
typedef enum {
    /**
     * 默认模式，不使用沉浸式样式。
     * @since 15
     */
    ARKUI_KEYBOARD_APPEARANCE_NONE_IMMERSIVE = 0,
    /**
     * 沉浸式模式，由系统决定采用的样式。
     * @since 15
     */
    ARKUI_KEYBOARD_APPEARANCE_IMMERSIVE = 1,
    /**
     * 浅色沉浸式样式。
     * @since 15
     */
    ARKUI_KEYBOARD_APPEARANCE_LIGHT_IMMERSIVE = 2,
    /**
     * 深色沉浸式样式。
     * @since 15
     */
    ARKUI_KEYBOARD_APPEARANCE_DARK_IMMERSIVE = 3
} ArkUI_KeyboardAppearance;
/**
 * @brief 为菜单定义文本菜单项.
 *
 * @since 22
 */
typedef struct ArkUI_TextMenuItem ArkUI_TextMenuItem;
/**
 * @brief 定义菜单数组结构体
 *
 * @since 22
 */
typedef struct ArkUI_TextMenuItemArray ArkUI_TextMenuItemArray;
/**
 * @brief 文本菜单项id枚举。
 *
 * @since 22
 */
typedef enum {
    /** 裁剪。 */
    ARKUI_TEXT_MENU_ITEM_ID_CUT = 0,

    /** 复制。 */
    ARKUI_TEXT_MENU_ITEM_ID_COPY = 1,

    /** 粘贴。 */
    ARKUI_TEXT_MENU_ITEM_ID_PASTE = 2,

    /** 全选。 */
    ARKUI_TEXT_MENU_ITEM_ID_SELECT_ALL = 3,

    /** 互通服务。例如跨设备交互，包括跨设备的相机访问等能力。 */
    ARKUI_TEXT_MENU_ITEM_ID_COLLABORATION_SERVICE = 4,

    /** 拍摄输入。 */
    ARKUI_TEXT_MENU_ITEM_ID_CAMERA_INPUT = 5,

    /** AI帮写。该菜单项依赖大模型能力，否则不生效。 */
    ARKUI_TEXT_MENU_ITEM_ID_AI_WRITER = 6,

    /** 翻译。对选中的文本提供翻译服务。 */
    ARKUI_TEXT_MENU_ITEM_ID_TRANSLATE = 7,

    /** 搜索。对选中的文本提供搜索服务，拉起浏览器搜索选中文本内容。 */
    ARKUI_TEXT_MENU_ITEM_ID_SEARCH = 8,

    /** 分享。对选中的文本提供分享服务，拉起分享窗口分享选中文本内容。 */
    ARKUI_TEXT_MENU_ITEM_ID_SHARE = 9,

    /** 打开链接。对选中的URL提供跳转服务，拉起浏览器搜索或者应用页面。 */
    ARKUI_TEXT_MENU_ITEM_ID_URL = 10,

    /** 新建邮件。对选中的邮箱地址提供跳转服务，拉起邮箱应用。 */
    ARKUI_TEXT_MENU_ITEM_ID_EMAIL = 11,

    /** 呼叫。对选中的电话号码跳转服务，拉起电话拨号页面。 */
    ARKUI_TEXT_MENU_ITEM_ID_PHONE_NUMBER = 12,

    /** 导航前往。对选中的地址提供跳转服务，拉起地图应用。 */
    ARKUI_TEXT_MENU_ITEM_ID_ADDRESS = 13,

    /** 新建日程。对选中的日期和时间提供跳转服务，拉起新建日程页面。*/
    ARKUI_TEXT_MENU_ITEM_ID_DATA_TIME = 14,

    /** 问问AI。对选中的文本提供AI问询能力。 */
    ARKUI_TEXT_MENU_ITEM_ID_ASK_AI = 15,

    /**
     * 自动填充。例如自动填充账号密码。
     * @since 24
     */
    ARKUI_TEXT_MENU_ITEM_ID_AUTO_FILL = 16,

    /**
     * 密码保险箱。
     * @since 24
     */
    ARKUI_TEXT_MENU_ITEM_ID_PASSWORD_VAULT = 17,

    /** 应用自定义菜单项起始id，除了系统内置的菜单项id，应用还可以自定义菜单项id。 */
    ARKUI_TEXT_MENU_ITEM_ID_APP_RESERVED_BEGIN = 10000,

    /** 应用自定义菜单项结束id，除了系统内置的菜单项id，应用还可以自定义菜单项id。 */
    ARKUI_TEXT_MENU_ITEM_ID_APP_RESERVED_END = 20000
} ArkUI_TextMenuItemId;
/**
 * @brief 文本默认菜单配置项结构体定义
 *
 * @since 22
 */
typedef struct ArkUI_TextEditMenuOptions ArkUI_TextEditMenuOptions;
/**
 * 菜单创建回调函数
 *
 * @param items 框架创建并释放数组，在回调函数中开发者可以调用{@link OH_ArkUI_TextMenuItemArray_Insert},
 * {@link OH_ArkUI_TextMenuItemArray_Erase}进行数组修改。
 * 开发者不能释放数组，统一由框架管理
 * @param userData 自定义数据
 * @since 22
 */
typedef void (*ArkUI_TextCreateMenuCallback)(
    ArkUI_TextMenuItemArray*    items,
    void*                       userData
);
/**
 * 文本菜单准备接口
 *
 * @param items 框架创建并释放数组，在回调函数中开发者可以调用{@link OH_ArkUI_TextMenuItemArray_Insert},
 * {@link OH_ArkUI_TextMenuItemArray_Erase}进行数组修改。
 * 开发者不能释放数组，统一由框架管理
 * @param userData 自定义数据
 * @since 22
 */
typedef void (*ArkUI_TextPrepareMenuCallback)(
    ArkUI_TextMenuItemArray*    items,
    void*                       userData
);
/**
 * 注册文本菜单点击回调函数
 *
 * @param item 点击的菜单项
 * @param start 选中文本起始位置
 * @param end 选中文本结束位置
 * @param userData 自定义数据
 * @return 返回true表示已消费，false表示事件未消费
 * @since 22
 */
typedef bool (*ArkUI_TextMenuItemClickCallback)(
    const ArkUI_TextMenuItem*    item,
    int32_t                      start,
    int32_t                      end,
    void*                        userData
);
/**
 * @brief 定义文本自定义选择菜单结构体
 *
 * @since 22
 */
typedef struct ArkUI_TextSelectionMenuOptions ArkUI_TextSelectionMenuOptions;
/**
 * @brief 定义装饰线样式。
 *
 * @since 24
 */
typedef struct OH_ArkUI_DecorationStyleOptions OH_ArkUI_DecorationStyleOptions;
/**
 * @brief 换行策略类型枚举。
 *
 * @since 24
 */
typedef enum {
    /**
     * 贪婪模式。
     * 使每一行尽可能显示多的字符，直到这一行不能显示更多字符时进行折行。
     * @since 24
     */
    OH_ARKUI_LINE_BREAK_STRATEGY_GREEDY = 0,
    /**
     * 高质量模式。
     * 在平衡模式的基础上，尽可能填满行，同时最后一行的权重较低，可能出现最后一行留白较多的情形。
     * @since 24
     */
    OH_ARKUI_LINE_BREAK_STRATEGY_HIGH_QUALITY = 1,
    /**
     * 平衡模式。
     * 在不拆词的情况下，尽量使一个段落中每一行的宽度相同。
     * @since 24
     */
    OH_ARKUI_LINE_BREAK_STRATEGY_BALANCE = 2
} OH_ArkUI_LineBreakStrategy;
/**
 * @brief 自定义文本选择菜单的文本识别类型枚举。
 *
 * @since 22
 */
typedef enum {
    /** 选中文本内容为文字类型。 */
    ARKUI_TEXT_SPAN_TYPE_TEXT = 0,
    /** 选中文本内容为图像类型。 */
    ARKUI_TEXT_SPAN_TYPE_IMAGE = 1,
    /** 选中文本内容为图文混合类型。 */
    ARKUI_TEXT_SPAN_TYPE_MIXED = 2,
    /**
     * 如果设置为此类型且设置了其他类型时，选中文本后会显示与选中文本内容类型对应的菜单。如果设置为此类型但其他类型未设置时，选中文本后会显示此类型对应的菜单。
     * 例如，同时设置了文本识别类型为ARKUI_TEXT_SPAN_TYPE_TEXT、ARKUI_TEXT_SPAN_TYPE_DEFAULT的两个菜单，
     * 此时选中文本内容为文字类型会触发ARKUI_TEXT_SPAN_TYPE_TEXT对应的菜单弹出，选中文本内容为图像类型则会触发ARKUI_TEXT_SPAN_TYPE_DEFAULT对应的菜单弹出。
     */
    ARKUI_TEXT_SPAN_TYPE_DEFAULT = 3
} ArkUI_TextSpanType;
/**
 * @brief 自定义文本选择菜单的响应类型枚举。
 *
 * @since 22
 */
typedef enum {
    /** 通过鼠标右键触发菜单弹出。 */
    ARKUI_TEXT_RESPONSE_TYPE_RIGHT_CLICK = 0,
    /** 通过长按触发菜单弹出。 */
    ARKUI_TEXT_RESPONSE_TYPE_LONG_PRESS = 1,
    /** 通过鼠标选中触发菜单弹出。 */
    ARKUI_TEXT_RESPONSE_TYPE_SELECT = 2,
    /**
     * 如果设置为此类型且设置了其他类型时，触发其他类型的操作会显示对应类型的菜单。如果设置为此类型但其他类型未设置时，触发其他类型的操作会显示此类型对应的菜单。
     * 例如，同时设置了响应类型为ARKUI_TEXT_RESPONSE_TYPE_RIGHT_CLICK、ARKUI_TEXT_RESPONSE_TYPE_DEFAULT的两个菜单，
     * 此时通过鼠标右键会触发ARKUI_TEXT_RESPONSE_TYPE_RIGHT_CLICK对应的菜单弹出，长按则会触发ARKUI_TEXT_RESPONSE_TYPE_DEFAULT对应的菜单弹出。
     */
    ARKUI_TEXT_RESPONSE_TYPE_DEFAULT = 3
} ArkUI_TextResponseType;

/**
 * @brief 创建文本输入框计数器的配置对象。
 *
 * @return 指向文本输入框计数器的配置对象的指针。
 * @since 22
 */
ArkUI_ShowCounterConfig* OH_ArkUI_ShowCounterConfig_Create();

/**
 * @brief 销毁文本输入框计数器的配置对象。
 *
 * @param config 销毁文本输入框计数器的配置对象指针。
 * @since 22
 */
void OH_ArkUI_ShowCounterConfig_Dispose(ArkUI_ShowCounterConfig* config);

/**
 * @brief 设置文本输入框未达到最大字符数时计数器的颜色。
 *
 * @param config 指向文本输入框计数器的配置对象指针。
 * @param color 文本输入框未达到最大字符数时计数器的颜色，格式为0xARGB，默认值为0x66182431。
 * @since 22
 */
void OH_ArkUI_ShowCounterConfig_SetCounterTextColor(ArkUI_ShowCounterConfig* config, uint32_t color);

/**
 * @brief 设置文本输入框超出最大字符数时计数器的颜色。
 *
 * @param config 指向文本输入框计数器的配置对象指针。
 * @param color 文本输入框超出最大字符数时计数器的颜色，格式为0xARGB，默认值为0x99FA2A2D。
 * @since 22
 */
void OH_ArkUI_ShowCounterConfig_SetCounterTextOverflowColor(ArkUI_ShowCounterConfig* config, uint32_t color);

/**
 * @brief 获取文本输入框未达到最大字符数时计数器的颜色。
 *
 * @param config 指向文本输入框计数器的配置对象指针。
 * @return 返回文本输入框未达到最大字符数时计数器的颜色，格式为0xARGB，如果未通过
 *      {@link OH_ArkUI_ShowCounterConfig_SetCounterTextColor}接口设置计数器颜色，则返回0。
 * @since 22
 */
uint32_t OH_ArkUI_ShowCounterConfig_GetCounterTextColor(ArkUI_ShowCounterConfig* config);

/**
 * @brief 获取文本输入框超出最大字符数时计数器的颜色。
 *
 * @param config 指向文本输入框计数器的配置对象指针。
 * @return 返回文本输入框超出最大字符数时计数器的颜色，格式为0xARGB，如果未通过
 *      {@link OH_ArkUI_ShowCounterConfig_SetCounterTextOverflowColor}接口设置计数器颜色，则返回0。
 * @since 22
 */
uint32_t OH_ArkUI_ShowCounterConfig_GetCounterTextOverflowColor(ArkUI_ShowCounterConfig* config);
/**
 * @brief 创建文本菜单项对象。
 *
 * @return 指向ArkUI_TextMenuItem对象的指针。
 * @since 22
 */
ArkUI_TextMenuItem* OH_ArkUI_TextMenuItem_Create();

/**
 * @brief 释放文本菜单项对象。
 *
 * @param textMenuItem 指向ArkUI_TextMenuItem对象的指针。
 * @since 22
 */
void OH_ArkUI_TextMenuItem_Dispose(ArkUI_TextMenuItem* textMenuItem);
/**
 * @brief 创建文本菜单扩展项对象。
 *
 * @return 指向ArkUI_TextEditMenuOptions对象的指针。
 * @since 22
 */
ArkUI_TextEditMenuOptions* OH_ArkUI_TextEditMenuOptions_Create();

/**
 * @brief 释放文本菜单扩展项对象。
 *
 * @param editMenuOptions 指向ArkUI_TextEditMenuOptions对象的指针。
 * @since 22
 */
void OH_ArkUI_TextEditMenuOptions_Dispose(ArkUI_TextEditMenuOptions* editMenuOptions);
/**
 * @brief 创建自定义文本选择菜单对象。
 *
 * @return 指向ArkUI_TextSelectionMenuOptions对象的指针。
 * @since 22
 */
ArkUI_TextSelectionMenuOptions* OH_ArkUI_TextSelectionMenuOptions_Create();

/**
 * @brief 释放自定义文本选择菜单对象。
 *
 * @param selectionMenuOptions 指向ArkUI_TextSelectionMenuOptions对象的指针。
 * @since 22
 */
void OH_ArkUI_TextSelectionMenuOptions_Dispose(ArkUI_TextSelectionMenuOptions* selectionMenuOptions);
/**
 * @brief 创建文本内容基础控制器对象。
 *
 * @return 指向控制器对象的指针。
 * @since 23
 */
ArkUI_TextContentBaseController* OH_ArkUI_TextContentBaseController_Create();

/**
 * @brief 销毁文本内容基础控制器对象。
 *
 * @param {ArkUI_TextContentBaseController*} controller Pointer to the controller object to be disposed.
 * @since 23
 */
void OH_ArkUI_TextContentBaseController_Dispose(ArkUI_TextContentBaseController* controller);

/**
 * @brief 在编辑态时删除光标前字符。
 * 其他状态删除输入框组件的最后一个字符。
 *
 * @param {ArkUI_TextContentBaseController*} controller Pointer to the configuration object to be modified.
 * @since 23
 */
void OH_ArkUI_TextContentBaseController_DeleteBackward(ArkUI_TextContentBaseController* controller);

/**
 * @brief 将起始索引与结束索引传递给与其绑定的输入框组件，并将此范围内的文字滚动到可视区域。
 *
 * @param {ArkUI_TextContentBaseController*} controller Pointer to the
 * configuration object to be modified.
 * @param {int32_t} start The start offset of the content to be made visible.
 * @param {int32_t} end The end offset of the content to be made visible
 * @since 23
 */
void OH_ArkUI_TextContentBaseController_ScrollToVisible(
    ArkUI_TextContentBaseController *controller, int32_t start, int32_t end);
/**
 * @brief 创建一个装饰线样式对象。
 * 当该对象不再使用时，请调用{@link OH_ArkUI_DecorationStyleOptions_Destroy}销毁。
 *
 * @return 指向{@link OH_ArkUI_DecorationStyleOptions}对象的指针。
 * @since 24
 */
OH_ArkUI_DecorationStyleOptions* OH_ArkUI_DecorationStyleOptions_Create();

/**
 * @brief 销毁装饰线样式对象。
 *
 * @param options 指向待销毁的选项对象的指针。
 * @since 24
 */
void OH_ArkUI_DecorationStyleOptions_Destroy(OH_ArkUI_DecorationStyleOptions* options);
#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_COMMON_H
/** @} */
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
 * @addtogroup ArkUI_Accessibility
 * @{
 *
 * @brief 描述ArkUI Accessibility对外支持的Native能力，如查询无障碍节点、上报无障碍事件等。
 *
 * @since 13
 */

/**
 * @file native_interface_accessibility.h
 *
 * @brief 声明用于访问Native Accessibility的API，提供无障碍相关能力。
 *
 * @sample [AccessibilityCapi](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/DocsSample/ArkUISample/AccessibilityCapi)
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @include <arkui/native_interface_accessibility.h>
 * @since 13
 */
#ifndef _NATIVE_INTERFACE_ACCESSIBILITY_H
#define _NATIVE_INTERFACE_ACCESSIBILITY_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 无障碍元素信息，用于向无障碍服务、辅助应用（屏幕朗读等）传递元素的属性、操作、位置、文本等信息，适用于无障碍服务获取和操作界面元素的辅助场景。
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityElementInfo ArkUI_AccessibilityElementInfo;

/**
 * @brief 无障碍事件信息。\n
 * 当无障碍服务或辅助应用要求控件执行操作后，应用需发送执行成功事件以通知操作结果，适用于需要向无障碍服务反馈操作执行情况的场景。
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityEventInfo ArkUI_AccessibilityEventInfo;

/**
 * @brief 该结构体为无障碍第三方操作提供者，用于承载回调函数的实现。\n
 * 开发者可通过该结构体注册和管理无障碍操作相关的回调，实现自定义的无障碍交互逻辑，适用于需要扩展或定制ArkUI无障碍能力的场景。
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityProvider ArkUI_AccessibilityProvider;

/**
 * @brief 用于设置无障碍操作的具体参数。在进行无障碍操作时，通过该结构体向无障碍服务传递操作所需的附加上下文信息。\n
 * 适用于开发者需要向无障碍服务精确描述无障碍操作细节的场景，例如自定义控件的无障碍读屏播报、
 * 辅助功能服务中的操作参数传递、语音助手触发的无障碍交互等应用功能。
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityActionArguments ArkUI_AccessibilityActionArguments;

/**
 * @brief 定义 ArkUI Native 组件实例对象指针，用于在 ArkUI Native 接口中标识和传递组件实例，例如创建、挂载、移除或销毁组件节点。
 *
 * @since 23
 */
typedef struct ArkUI_Node* ArkUI_NodeHandle;

/**
 * @brief Accessibility操作类型的枚举。
 *
 * @since 13
 */
typedef enum {
    /**
     * 无效值。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_INVALID = 0,
    /**
     * 收到事件后，组件需要对点击做出响应。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK = 0x00000010,
    /**
     * 收到事件后，组件需要对长按做出响应。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_LONG_CLICK = 0x00000020,
    /**
     * 表示获取辅助功能焦点的操作，执行后对应组件将获得无障碍焦点。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_GAIN_ACCESSIBILITY_FOCUS = 0x00000040,
    /**
     * 表示清除辅助功能焦点的操作。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLEAR_ACCESSIBILITY_FOCUS = 0x00000080,
    /**
     * 滚动组件响应向前滚动动作。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_FORWARD = 0x00000100,
    /**
     * 滚动组件响应反向滚动操作。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_BACKWARD = 0x00000200,
    /**
     * 复制文本组件的选定内容。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_COPY = 0x00000400,
    /**
     * 粘贴文本组件的选定内容。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_PASTE = 0x00000800,
    /**
     * 剪切文本组件的选定内容。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CUT = 0x00001000,
    /**
     * 针对文本组件进行选择操作。结合ArkUI_AccessibilityActionArguments使用，配置selectTextBegin（表示选择起始位置），selectTextEnd（表示选择结束位置），
     * selectTextInForward（true表示为前光标，false表示为后光标）进入编辑区选择一段文本内容。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SELECT_TEXT = 0x00002000,
    /**
     * 设置文本组件的文本内容。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SET_TEXT = 0x00004000,
    /**
     * 针对文本组件设置光标位置，结合{@link ArkUI_AccessibilityActionArguments}使用，配置可输入文本组件的光标位置。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SET_CURSOR_POSITION = 0x00100000,
    /**
     * 焦点移动操作中支持查找下一个焦点。此处的HTML并不代表网页元素，仅用于表示具有可自行查找下一个可见聚焦组件的能力，与Web支持的能力相似。实现{@link findNextFocusAccessibilityNode}
     * 的能力才可配置该属性。
     * @since 15
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_NEXT_HTML_ITEM = 0x02000000,
    /**
     * 焦点移动操作中支持查找上一个焦点。此处的HTML并不代表网页元素，仅用于表示具有可自行查找上一个可见聚焦组件的能力，与Web支持的能力相似。实现{@link findNextFocusAccessibilityNode}
     * 的能力才可配置该属性。
     * @since 15
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_PREVIOUS_HTML_ITEM = 0x04000000,
} ArkUI_Accessibility_ActionType;

/**
 * @brief Accessibility事件类型的枚举。
 *
 * @since 13
 */
typedef enum {
    /**
     * 无效值。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_INVALID = 0,
    /**
     * 点击事件，在UI组件响应后发送。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_CLICKED = 0x00000001,
    /**
     * 长按事件，在UI组件响应后发送。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_LONG_CLICKED = 0x00000002,
    /**
     * 被选中事件，控件响应完成后发送。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_SELECTED = 0x00000004,
    /**
     * 文本更新事件，需要在文本更新时发送。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_TEXT_UPDATE = 0x00000010,
    /**
     * 页面更新事件，当页面跳转、切换、大小更改或移动时发送。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_PAGE_STATE_UPDATE = 0x00000020,
    /**
     * 页面内容发生变化时需要发送事件。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_PAGE_CONTENT_UPDATE = 0x00000800,
    /**
     * scrolled事件，当可滚动的组件上发生滚动事件时，会发送此事件。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_SCROLLED = 0x000001000,
    /**
     * Accessibility焦点事件，在UI组件响应后发送。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUSED = 0x00008000,
    /**
     * Accessibility焦点清除事件，在UI组件响应后发送。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUS_CLEARED = 0x00010000,
    /**
     * 主动请求指定节点聚焦。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_REQUEST_ACCESSIBILITY_FOCUS = 0x02000000,
    /**
     * UI组件上报页面打开事件。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_PAGE_OPEN = 0x20000000,
    /**
     * UI组件上报页面关闭事件。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_PAGE_CLOSE = 0x08000000,
    /**
     * 广播Accessibility事件，请求主动播报指定的内容。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ANNOUNCE_FOR_ACCESSIBILITY = 0x10000000,
    /**
     * 焦点更新事件，用于焦点更新场景。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_FOCUS_NODE_UPDATE = 0x10000001,
} ArkUI_AccessibilityEventType;

/**
 * @brief 无障碍操作内容结构。该结构体用于描述无障碍节点支持的操作类型及其描述信息。\n
 * 支持无障碍服务向用户呈现节点可执行的操作（如点击、长按、滚动等），并提供操作的文字说明，以帮助用户理解操作含义。
 *
 * @since 13
 */
typedef struct {
    /**
     * 操作类型。
     * @since 13
     */
    ArkUI_Accessibility_ActionType actionType;
    /**
     * 操作描述信息。
     * @since 13
     */
    const char* description;
} ArkUI_AccessibleAction;

/**
 * @brief 节点在屏幕中的矩形区域坐标位置。\n
 * 该结构体用于描述无障碍节点的边界矩形，通过左上角和右下角的坐标定义节点在屏幕上的可视区域，支持无障碍服务获取节点的位置和大小信息。
 *
 * @since 13
 */
typedef struct {
    /**
     * 左上角X轴坐标位置。
     * @since 13
     */
    int32_t leftTopX;
    /**
     * 左上角Y轴坐标位置。
     * @since 13
     */
    int32_t leftTopY;
    /**
     * 右下角X轴坐标位置。
     * @since 13
     */
    int32_t rightBottomX;
    /**
     * 右下角Y轴坐标位置。
     * @since 13
     */
    int32_t rightBottomY;
} ArkUI_AccessibleRect;

/**
 * @brief 用于表示特定组件（如{@link Slider}、{@link Rating}、{@link Progress}）的范围值信息，包含当前值、最大值和最小值，供无障碍服务读取并向障碍用户播报。
 *
 * @since 13
 */
typedef struct {
    /**
     * 组件的最小值。
     * @since 13
     */
    double min;
    /**
     * 组件的最大值。
     * @since 13
     */
    double max;
    /**
     * 组件的当前值。
     * @since 13
     */
    double current;
} ArkUI_AccessibleRangeInfo;

/**
 * @brief 用于描述网格组件的整体布局属性。\n
 * 该结构体用于向无障碍服务提供网格组件的行数、列数和选择模式等信息，支持无障碍服务获取网格的整体布局信息。
 *
 * @since 13
 */
typedef struct {
    /**
     * 网格的行数。取值范围为大于0的整数，传入非正整数时不生效。
     * @since 13
     */
    int32_t rowCount;
    /**
     * 网格的列数。取值范围为大于0的整数，传入非正整数时不生效。
     * @since 13
     */
    int32_t columnCount;
    /**
     * 选择模式。值为0时表示仅选中网格的一行，非0值时表示选中网格的多行。
     * @since 13
     */
    int32_t selectionMode;
} ArkUI_AccessibleGridInfo;

/**
 * @brief 用于描述网格组件内某个网格项的无障碍属性。\n
 * 该结构体用于向无障碍服务提供网格项的位置、跨度、选中状态等信息，支持无障碍服务获取网格项的布局信息。
 *
 * @since 13
 */
typedef struct {
    /**
     * 是否是标题。true表示是标题，false表示不是标题。
     * @since 13
     */
    bool heading;
    /**
     * 是否被选中。true表示被选中，false表示未被选中。
     * @since 13
     */
    bool selected;
    /**
     * 列下标。取值范围为大于等于0的整数。传入0或负数时该字段不生效。
     * @since 13
     */
    int32_t columnIndex;
    /**
     * 行下标。取值范围为大于等于0的整数。传入0或负数时该字段不生效。
     * @since 13
     */
    int32_t rowIndex;
    /**
     * 列跨度。取值范围为大于0的整数。传入0或负数时该字段不生效。
     * @since 13
     */
    int32_t columnSpan;
    /**
     * 行跨度。取值范围为大于0的整数。传入0或负数时该字段不生效。
     * @since 13
     */
    int32_t rowSpan;
} ArkUI_AccessibleGridItemInfo;

/**
 * @brief Accessibility错误代码状态的枚举。
 *
 * @since 13
 */
typedef enum {
    /**
     * 成功。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL = 0,
    /**
     * 操作失败，请检查接口调用流程。可能原因:接口执行过程中出现内部错误。解决措施:请检查调用流程是否正确,若问题持续存在请排查系统状态。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_RESULT_FAILED = -1,
    /**
     * 无效参数，请检查传入的参数是否正确。可能原因:传入的参数为空指针或不符合接口要求。解决措施:请检查传入参数是否合法,确保指针不为空且参数值在有效范围内。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER = -2,
    /**
     * 内存不足，请检查系统内存使用情况。可能原因:系统内存资源不足,无法完成操作。解决措施:请释放不必要的资源后重试。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_RESULT_OUT_OF_MEMORY = -3,
} ArkUI_AcessbilityErrorCode;

/**
 * @brief Accessibility搜索类型的枚举。
 *
 * @since 13
 */
typedef enum {
    /**
     * 查询当前节点。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_CURRENT = 0,
    /**
     * 查询父节点。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_PREDECESSORS = 1 << 0,
    /**
     * 查询兄弟节点。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_SIBLINGS = 1 << 1,
    /**
     * 查询下一层孩子节点。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_CHILDREN = 1 << 2,
    /**
     * 查询所有孩子节点。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_RECURSIVE_CHILDREN = 1 << 3,
} ArkUI_AccessibilitySearchMode;

/**
 * @brief Accessibility焦点类型的枚举。
 *
 * @since 13
 */
typedef enum {
    /**
     * 无效值。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_FOCUS_TYPE_INVALID = -1,
    /**
     * 输入焦点类型。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_FOCUS_TYPE_INPUT = 1 << 0,
    /**
     * Accessibility焦点类型。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_FOCUS_TYPE_ACCESSIBILITY = 1 << 1,
} ArkUI_AccessibilityFocusType;

/**
 * @brief Accessibility焦点移动方向的枚举。
 *
 * @since 13
 */
typedef enum {
    /**
     * 无效值。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_INVALID = 0,
    /**
     * 焦点向上移动。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_UP = 0x00000001,
    /**
     * 焦点向下移动。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_DOWN = 0x00000002,
    /**
     * 焦点向左移动。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_LEFT = 0x00000004,
    /**
     * 焦点向右移动。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_RIGHT = 0x00000008,
    /**
     * 焦点向下一个可聚焦节点移动，基于查询请求中指定的基准节点。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_FORWARD = 0x00000010,
    /**
     * 焦点向上一个可聚焦节点移动，基于查询请求中指定的基准节点。
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_BACKWARD = 0x00000020,
} ArkUI_AccessibilityFocusMoveDirection;

/**
 * @brief 提供封装{@link ArkUI_AccessibilityElementInfo}的List实例，用于批量存储和管理无障碍元素信息，适用于需要一次获取多个无障碍元素信息的场景。
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityElementInfoList ArkUI_AccessibilityElementInfoList;

/**
 * @brief 第三方{@link provider}回调函数结构定义，需要第三方平台实现的相关函数，通过{@link OH_ArkUI_AccessibilityProviderRegisterCallback}注册到系统侧。
 * 适用于读屏软件、语音控制、开关控制等无障碍辅助场景，第三方平台通过实现这些回调响应系统的无障碍查询和操作请求。
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityProviderCallbacks {
    /**
    * @brief 查询指定节点的节点信息。由接入方平台实现的回调函数，注册给系统侧调用。
    *
    * @param elementId 无障碍元素的唯一编号。
    * @param mode 表示无障碍搜索模式。具体取值及含义参见{@link ArkUI_AccessibilitySearchMode}。
    * @param requestId 表示请求ID。
    * @param elementList 表示无障碍元素信息列表。
    * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}，表示操作成功。
    *     <br>{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}，表示参数错误。可能原因：传入的elementId无效或elementList为空指针。处理步骤：
    *     请检查参数elementId、mode、elementList的有效性。
    * @since 13
    */
    int32_t (*findAccessibilityNodeInfosById)(int64_t elementId, ArkUI_AccessibilitySearchMode mode,
        int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList);
    /**
    * @brief 基于指定的节点，查询满足指定文本内容的节点信息。由接入方平台实现的回调函数，注册给系统侧调用。
    *
    * @param elementId 无障碍元素的唯一编号。
    * @param text 表示用于查找节点的文本内容。
    * @param requestId 表示请求ID。
    * @param elementList 表示无障碍元素信息列表。
    * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}，表示操作成功。
    *     <br>{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}，表示参数错误。
    */
    int32_t (*findAccessibilityNodeInfosByText)(int64_t elementId, const char* text, int32_t requestId,
        ArkUI_AccessibilityElementInfoList* elementList);
    /**
    * @brief 从指定节点出发，根据焦点类型查找当前已获得焦点的节点，并将该节点元素信息返回。\n
    * 由接入方平台实现的回调函数，注册给系统侧调用。
    *
    * @param elementId 无障碍元素的唯一编号。
    * @param focusType 表示焦点的类型。具体取值及含义参见{@link ArkUI_AccessibilityFocusType}。
    * @param requestId 表示请求ID。
    * @param elementInfo 表示无障碍元素信息。
    * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}，表示操作成功。
    *     <br>{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}，表示参数错误。
    */
    int32_t (*findFocusedAccessibilityNode)(int64_t elementId, ArkUI_AccessibilityFocusType focusType,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    /**
    * @brief 根据参考节点和查找方向，查询下一个可以聚焦的节点。由接入方平台实现的回调函数，注册给系统侧调用。
    *
    * @param elementId 无障碍元素的唯一编号。
    * @param direction 表示查找方向。具体取值及含义参见{@link ArkUI_AccessibilityFocusMoveDirection}。
    * @param requestId 表示请求ID。
    * @param elementInfo 表示无障碍元素信息。
    * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}，表示操作成功。
    *     <br>{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}，表示参数错误。
    */
    int32_t (*findNextFocusAccessibilityNode)(
        int64_t elementId, ArkUI_AccessibilityFocusMoveDirection direction,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    /**
    * @brief 在指定的无障碍节点上执行无障碍Action操作。\n
    * 例如，当读屏软件用户通过语音指令或开关控制触发点击、滚动、选择等操作时，系统通过此回调通知第三方平台执行相应动作。\n
    * 由接入方平台实现的回调函数，注册给系统侧调用。
    *
    * @param elementId 无障碍元素的唯一编号。
    * @param action 表示要执行的动作。具体取值及含义参见{@link ArkUI_Accessibility_ActionType}。
    * @param actionArguments Indicates action arguments.
    * @param requestId 表示请求ID。
    * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}，表示操作成功。
    *     <br>{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}，表示参数错误。
    */
    int32_t (*executeAccessibilityAction)(int64_t elementId, ArkUI_Accessibility_ActionType action,
        ArkUI_AccessibilityActionArguments *actionArguments, int32_t requestId);
    /**
    * @brief 清除当前焦点节点的焦点状态。由接入方平台实现的回调函数，注册给系统侧调用。
    *
    * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}，表示操作成功。
    *     <br>{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}，表示参数错误。
    */
    int32_t (*clearFocusedFocusAccessibilityNode)();
    /**
    * @brief 查询指定节点的当前光标位置。由接入方平台实现的回调函数，注册给系统侧调用。
    *
    * @param elementId 无障碍元素的唯一编号。
    * @param requestId 表示请求ID。
    * @param index 表示光标位置的索引，取值为非负整数，表示光标在文本中的字符位置。
    * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}，表示操作成功。
    *     <br>{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}，表示参数错误。
    */
    int32_t (*getAccessibilityNodeCursorPosition)(int64_t elementId, int32_t requestId, int32_t* index);
} ArkUI_AccessibilityProviderCallbacks;

/**
 * @brief 注册第三方操作provider回调函数到系统侧，由第三方平台实现相关函数并通过本接口完成注册。
 *
 * @param provider 表示指向{@link ArkUI_AccessibilityProvider}实例的指针。
 * @param callbacks 表示指向{@link ArkUI_AccessibilityProviderCallbacks}实例的指针。
 * @return 如果操作成功，则返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
 *     <br>如果参数错误，则返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityProviderRegisterCallback(
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityProviderCallbacks* callbacks);

/**
 * @brief \n
 * 适配多实例场景第三方操作{@link provider}回调函数结构定义，包含节点信息查询、焦点查找与清除、操作执行、光标位置获取等无障碍相关回调函数。\n
 * 该结构需由第三方平台实现，并通过
 * {@link OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance}注册到系统侧，以支持第三方平台接入系统无障碍服务。
 *
 * @since 15
 */
typedef struct ArkUI_AccessibilityProviderCallbacksWithInstance {
    /**
     * @brief 基于指定的节点，根据搜索模式查询对应的节点信息。由接入方平台实现的回调函数，注册给系统侧调用。\n
     * 支持多实例场景。
     *
     * @param instanceId 第三方框架的实例编码。
     * @param elementId 无障碍元素的唯一编号。
     * @param mode 无障碍服务的搜索模式，决定基于指定节点查询节点信息的方式，例如按子树搜索、按前序遍历搜索、按后序遍历搜索等。具体取值及含义详见ArkUI_AccessibilitySearchMode枚举说明。
     * @param requestId 请求id，用于关联请求过程，建议日志打印时附带输出该信息，方便问题定位。
     * @param elementList 本次查询到的所有无障碍元素列表。
     * @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
     *     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
     * @since 15
     */
    int32_t (*findAccessibilityNodeInfosById)(const char* instanceId, int64_t elementId,
        ArkUI_AccessibilitySearchMode mode, int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList);
    /**
     * @brief 基于指定的节点，查询文本内容匹配指定文本的节点信息。由接入方平台实现的回调函数，注册给系统侧调用。\n
     * 支持多实例场景。**使用场景**：当无障碍服务执行文本搜索（如用户通过屏幕阅读器查找包含特定文本的元素）时，
     * 通过此回调向接入方平台查询匹配的节点。
     *
     * @param instanceId 第三方框架的实例编码。
     * @param elementId 无障碍元素的唯一编号，需指向文本组件。
     * @param text 组件需要匹配的文本内容。
     * @param requestId 请求id，用于关联请求过程，建议日志打印时附带输出该信息，方便问题定位。
     * @param elementList 本次查询到的所有无障碍元素列表。
     * @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
     *     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
     */
    int32_t (*findAccessibilityNodeInfosByText)(const char* instanceId, int64_t elementId, const char* text,
        int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList);
    /**
     * @brief 从指定节点查找已经聚焦的节点。由接入方平台实现的回调函数，注册给系统侧调用。支持多实例场景。
     *
     * @param instanceId 第三方框架的实例编码。
     * @param elementId 无障碍元素的唯一编号。
     * @param focusType 焦点类型，用于区分输入焦点和无障碍焦点。
     * @param requestId 请求id，用于关联请求过程，建议日志打印时附带输出该信息，方便问题定位。
     * @param elementInfo 本次查询到的无障碍元素。
     * @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
     *     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
     */
    int32_t (*findFocusedAccessibilityNode)(const char* instanceId, int64_t elementId,
        ArkUI_AccessibilityFocusType focusType, int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    /**
     * @brief 从指定节点查询指定方向的下一个可聚焦节点。由接入方平台实现的回调函数，注册给系统侧调用。支持多实例场景。
     *
     * @param instanceId 第三方框架的实例编码。
     * @param elementId 无障碍元素的唯一编号。
     * @param direction 焦点移动方向，指定查找下一个焦点节点的方向。
     * @param requestId 请求id，用于关联请求过程，建议日志打印时附带输出该信息，方便问题定位。
     * @param elementInfo 本次查询到的无障碍元素。
     * @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
     *     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
     */
    int32_t (*findNextFocusAccessibilityNode)(
        const char* instanceId, int64_t elementId, ArkUI_AccessibilityFocusMoveDirection direction,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    /**
     * @brief 对指定节点执行指定的操作。由接入方平台实现的回调函数，注册给系统侧调用。支持多实例场景。
     *
     * @param instanceId 第三方框架的实例编码。
     * @param elementId 无障碍元素的唯一编号。
     * @param action 需要执行的操作，比如聚焦、点击和长按等。
     * @param actionArguments Indicates action arguments.
     * @param requestId 请求id，用于关联请求过程，建议日志打印时附带输出该信息，方便问题定位。
     * @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
     *     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
     */
    int32_t (*executeAccessibilityAction)(const char* instanceId, int64_t elementId,
        ArkUI_Accessibility_ActionType action, ArkUI_AccessibilityActionArguments *actionArguments, int32_t requestId);
    /**
     * @brief 清除当前获焦的节点。由接入方平台实现的回调函数，注册给系统侧调用。支持多实例场景。
     *
     * @param instanceId 第三方框架的实例编码。
     * @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
     *     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
     */
    int32_t (*clearFocusedFocusAccessibilityNode)(const char* instanceId);
    /**
     * @brief 获取当前组件中（文本组件）光标位置。由接入方平台实现的回调函数，注册给系统侧调用。支持多实例场景。
     *
     * @param instanceId 第三方框架的实例编码。
     * @param elementId 无障碍元素的唯一编号。
     * @param requestId 请求id，用于关联请求过程，建议日志打印时附带输出该信息，方便问题定位。
     * @param index 光标的位置结果，表示光标在文本中从起始位置开始的字符索引，索引从0开始。
     * @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
     *     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
     */
    int32_t (*getAccessibilityNodeCursorPosition)(const char* instanceId, int64_t elementId,
        int32_t requestId, int32_t* index);
} ArkUI_AccessibilityProviderCallbacksWithInstance;

/**
 * @brief 无障碍多实例场景第三方平台将回调函数注册到系统侧。
 *
 * @param instanceId 第三方平台接入的实例ID，用于区分多实例场景中不同的第三方实例，ID由第三方平台指定与维护。
 * @param provider 第三方平台接入provider句柄。
 * @param callbacks 表示指向{@link ArkUI_AccessibilityProviderCallbacksWithInstance}实例的指针。
 * @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
 *     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
 * @since 15
 */
int32_t OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance(const char* instanceId,
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityProviderCallbacksWithInstance* callbacks);

/**
 * @brief 主动上报事件接口，通知无障碍服务。
 *
 * @param provider 第三方平台接入provider句柄。
 * @param eventInfo 表示指向Accessibility事件信息的指针。
 * @param callback Indicates the pointer to the callback that is called after the event is sent.
 * @since 13
 */
void OH_ArkUI_SendAccessibilityAsyncEvent(
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityEventInfo* eventInfo,
    void (*callback)(int32_t errorCode));

/**
 * @brief 在指定的list中增加element成员，并返回element结构。
 *
 * @param list 指定的{@link ArkUI_AccessibilityElementInfoList}结构，新创建的ElementInfo成员加入该list后返回给函数调用方。
 * @return 返回创建完成的{@link ArkUI_AccessibilityElementInfo}结构指针；如果创建失败，则返回NULL。
 * @since 13
 */
ArkUI_AccessibilityElementInfo* OH_ArkUI_AddAndGetAccessibilityElementInfo(
    ArkUI_AccessibilityElementInfoList* list);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置无障碍元素的唯一标识（elementId）。
*
* @param elementInfo {@link ArkUI_AccessibilityElementInfo}指针。
* @param elementId 无障碍元素的唯一编号，在当前组件树中必须唯一。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetElementId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t elementId);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置父节点的无障碍编号（parentId）。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param parentId 表示元素的父组件无障碍编号，应指向已存在的父节点elementId。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetParentId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t parentId);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件类型。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param componentType 表示元素所属的组件类型字符串，不能为空指针。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetComponentType(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* componentType);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件文本内容。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param contents 表示元素被无障碍服务所识别的文本内容，不能为空指针。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetContents(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* contents);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置提示文本。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param hintText 表示提示文本，不能为空指针。默认为""。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetHintText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hintText);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置无障碍专用的替代文本。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param accessibilityText 表示Accessibility文本，不能为空指针。默认为""。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityText);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置无障碍描述信息。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param accessibilityDescription 表示Accessibility描述信息，不能为空指针。默认为""。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityDescription(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityDescription);

/**
* @brief 设置{@link ArkUI_AccessibilityElementInfo}的子节点数量和子节点ID集合。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param childCount 表示孩子节点数量，必须大于0。
* @param childNodeIds 表示孩子节点id集合，每个ID应指向已存在的子节点elementId，不能为空指针。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetChildNodeIds(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t childCount, int64_t* childNodeIds);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件支持的无障碍操作列表。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param operationCount 组件支持的action数量，必须大于0。传入0或负数时返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。
* @param operationActions 组件支持的action数组，数组中应至少包含operationCount个有效元素，不能为空指针。具体支持的action类型可以参考
*     {@link ArkUI_Accessibility_ActionType}。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetOperationActions(ArkUI_AccessibilityElementInfo* elementInfo,
    int32_t operationCount, ArkUI_AccessibleAction* operationActions);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件在屏幕上的矩形区域。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param screenRect 表示屏幕区域，包含左上角和右下角坐标，不能为空指针。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetScreenRect(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleRect* screenRect);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否可勾选。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param checkable 表示是否可勾选。true表示可勾选，false表示不可勾选。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetCheckable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checkable);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置当前的勾选状态。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param checked 表示是否被勾选。true表示已勾选，false表示未勾选。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetChecked(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checked);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否可聚焦。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param focusable 表示是否可聚焦。true表示可聚焦，false表示不可聚焦。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetFocusable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool focusable);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否已聚焦。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param isFocused 表示是否聚焦。true表示已聚焦，false表示未聚焦。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isFocused);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件是否在屏幕上可见。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param isVisible 表示是否可见。true表示可见，false表示不可见。默认值false。所有需要被辅助应用识别的组件必须显式设置为true。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetVisible(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isVisible);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置当前的无障碍辅助焦点状态。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param accessibilityFocused 表示是否被无障碍聚焦。true表示被无障碍聚焦，false表示未被无障碍聚焦。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityFocused);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否处于选中状态。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param selected 表示是否被选中。true表示被选中，false表示未选中。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetSelected(
    ArkUI_AccessibilityElementInfo* elementInfo, bool selected);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否支持点击操作。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param clickable 表示是否支持点击。true表示支持，false表示不支持。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool clickable);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否支持长按操作。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param longClickable 表示是否支持长按。true表示支持，false表示不支持。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetLongClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool longClickable);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件是否处于启用状态。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param isEnabled 表示是否启用。true表示启用，false表示未启用。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetEnabled(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isEnabled);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否为密码输入框。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param isPassword 表示是否为密码。true表示是密码，false表示不是密码。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetIsPassword(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isPassword);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否支持滚动操作。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param scrollable 表示是否支持滚动。true表示支持，false表示不支持。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetScrollable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool scrollable);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置文本内容是否可编辑。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param editable 表示是否支持编辑。true表示支持，false表示不支持。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetEditable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool editable);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否处于提示文本状态。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param isHint 表示是否为提示状态。true表示是提示状态，false表示不是提示状态。在提示状态下无障碍辅助应用播报hintText，否则播报contents。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetIsHint(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isHint);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置范围值信息。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param rangeInfo 表示特定组件的当前值、最大值、最小值，不能为空指针。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetRangeInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleRangeInfo* rangeInfo);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置网格信息。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param gridInfo 表示特定组件的行数、列数以及选择模式，不能为空指针。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetGridInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridInfo* gridInfo);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置网格容器中子项的属性信息。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param gridItem 表示网格子项的属性值，不能为空指针。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetGridItemInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridItemInfo* gridItem);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置选中文本的起始位置。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param selectedTextStart 文本类控件使用，设置选中文本的起始位置索引（从0开始）。应与selectedTextEnd配合使用。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetSelectedTextStart(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t selectedTextStart);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置选中文本的结束位置。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param selectedTextEnd 文本类控件使用，设置选中文本的结束位置索引（从0开始）。应与selectedTextStart配合使用。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetSelectedTextEnd(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t selectedTextEnd);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置当前获焦或高亮子项的位置索引。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param currentItemIndex 当前获焦控件的位置索引（从0开始），取值范围为[0, itemCount-1]。应与itemCount配合使用。适用于{@link List}、{@link Select}、
*     {@link Swiper}、{@link Tab}等容器组件。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetCurrentItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t currentItemIndex);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置当前屏幕可见区域中第一个元素的位置索引。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param startItemIndex 当前屏幕可见区域中第一个元素的位置索引（从0开始）。List、Select、Swiper、{@link Tab}等容器组件使用。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetStartItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t startItemIndex);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置当前屏幕可见区域中最后一个元素的位置索引。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param endItemIndex 当前屏幕可见区域中最后一个元素的位置索引（从0开始），取值范围为[0, itemCount-1]，且应大于等于startItemIndex。List、Select、Swiper、
*     {@link Tab}等容器组件使用。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetEndItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t endItemIndex);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置容器中子项的总数。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param itemCount 表示容器中子项的总数（包括可见和不可见的），应为非负整数，0表示容器为空。用于辅助应用播报“第X项，共Y项”。如{@link List}、{@link Select}、{@link Swiper}、
*     {@link Tab}等容器组件使用。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetItemCount(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t itemCount);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置滚动偏移量。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param offset 对于可滚动类容器组件，如{@link List}、{@link Grid}，内容区相对于元素顶部坐标的滚动像素偏移量（单位：像素）。offset为0表示未滚动，正值表示已滚动的距离。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityOffset(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t offset);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置无障碍分组。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param accessibilityGroup 表示是否启用无障碍分组。true表示将组件及其子组件作为一个整体播报，false表示逐个遍历子节点。默认值false。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityGroup(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityGroup);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置无障碍重要性级别。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param accessibilityLevel 表示组件的无障碍重要性级别，取值为“auto”/“yes”/“no”/“no-hide-descendants”，不能为空指针。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityLevel);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件的Z序。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param zIndex 组件z序，用于控制元素在垂直于屏幕的z轴上的位置。{@link UiTest}需要使用。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetZIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t zIndex);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置透明度。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param opacity 表示透明度。取值范围[0, 1]，包含0和1，其中1表示完全不透明，0表示完全透明。超出范围时按边界值截断处理。{@link UiTest}需要使用。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityOpacity(
    ArkUI_AccessibilityElementInfo* elementInfo, float opacity);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置背景色。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param backgroundColor 表示背景色。数据为“#ARGB”格式，例如非透明白色即“#FFFFFFFF”。不能为空指针。{@link UiTest}需要使用。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetBackgroundColor(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundColor);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置背景图片。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param backgroundImage 表示背景图片的资源路径字符串。不能为空指针。{@link UiTest}需要使用。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetBackgroundImage(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundImage);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置模糊效果。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param blur 表示模糊度参数字符串。具体取值格式参考ArkUI组件对应模糊度属性的取值规范。不能为空指针。{@link UiTest}需要使用。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetBlur(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* blur);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置触摸测试的响应逻辑及节点阻塞规则。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param hitTestBehavior 表示触摸测试响应模式，取值为“Default”（默认行为，不阻断触摸事件）、“Block”（阻断自身及子组件的触摸事件）、“Transparent”（自身不响应但子组件可响应）、“None”
*     （自身和子组件都不响应），不能为空指针。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetHitTestBehavior(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hitTestBehavior);

/**
* @brief 为无障碍节点信息{@link ArkUI_AccessibilityElementInfo}设置组件标识，可用于自动化测试识别特定组件。
*
* @param elementInfo 表示指向ArkUI_AccessibilityElementInfo的指针。
* @param identifier 表示组件的唯一标识字符串，不能为空指针。
*     <br>需保证上报的组件树中的组件标识唯一，且字符串长度不大于1024，超过1024会截断使用。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 24
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetComponentIdentifier(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* identifier);

/**
 * @brief 创建一个{@link ArkUI_AccessibilityElementInfo}对象，创建后需要调用{@link OH_ArkUI_DestoryAccessibilityElementInfo}释放。
 *
 * @return 返回新创建的{@link ArkUI_AccessibilityElementInfo}对象指针，用于承载无障碍节点信息；如果创建失败，则返回NULL。
 * @since 13
 * @version 1.0
 */
ArkUI_AccessibilityElementInfo* OH_ArkUI_CreateAccessibilityElementInfo(void);

/**
 * @brief 销毁一个{@link ArkUI_AccessibilityElementInfo}对象。
 *
 * @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
 * @since 13
 * @version 1.0
 */
void OH_ArkUI_DestoryAccessibilityElementInfo(ArkUI_AccessibilityElementInfo* elementInfo);

/**
 * @brief 创建一个{@link ArkUI_AccessibilityEventInfo}对象，创建后需要调用{@link OH_ArkUI_DestoryAccessibilityEventInfo}释放。
 *
 * @return 返回新创建的{@link ArkUI_AccessibilityEventInfo}对象指针，用于承载无障碍事件信息；如果创建失败，则返回NULL。
 * @since 13
 */
ArkUI_AccessibilityEventInfo* OH_ArkUI_CreateAccessibilityEventInfo(void);

/**
 * @brief 销毁{@link ArkUI_AccessibilityEventInfo}对象。
 *
 * @param eventInfo 需要被销毁的{@link ArkUI_AccessibilityEventInfo}对象。
 * @since 13
 */
void OH_ArkUI_DestoryAccessibilityEventInfo(ArkUI_AccessibilityEventInfo* eventInfo);

/**
* @brief 为{@link ArkUI_AccessibilityEventInfo}设置事件类型。
*
* @param eventInfo 表示指向{@link ArkUI_AccessibilityEventInfo}的指针。
* @param eventType 表示事件类型，可选值参考{@link ArkUI_AccessibilityEventType}枚举定义，如点击事件、长按事件、文本更新事件、焦点事件、页面更新事件等。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityEventSetEventType(
    ArkUI_AccessibilityEventInfo* eventInfo,  ArkUI_AccessibilityEventType eventType);

/**
* @brief 为{@link ArkUI_AccessibilityEventInfo}设置主动播报的内容。
*
* @param eventInfo 表示事件信息。
* @param textAnnouncedForAccessibility 表示主动播报的内容，不能为空指针。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityEventSetTextAnnouncedForAccessibility(
    ArkUI_AccessibilityEventInfo* eventInfo,  const char* textAnnouncedForAccessibility);

/**
* @brief 为{@link ArkUI_AccessibilityEventInfo}设置请求焦点id。
*
* @param eventInfo 表示事件信息。
* @param requestFocusId 表示请求聚焦的无障碍元素编号，需与ArkUI_AccessibilityElementInfo中设置的elementId一致，用于通知无障碍服务聚焦到指定节点。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityEventSetRequestFocusId(
    ArkUI_AccessibilityEventInfo* eventInfo,  int32_t requestFocusId);

/**
* @brief 为{@link ArkUI_AccessibilityEventInfo}设置elementInfo。
*
* @param eventInfo 表示事件信息。
* @param elementInfo 表示{@link ArkUI_AccessibilityElementInfo}元素信息。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityEventSetElementInfo(
    ArkUI_AccessibilityEventInfo* eventInfo,  ArkUI_AccessibilityElementInfo* elementInfo);

/**
* @brief 获取{@link ArkUI_AccessibilityActionArguments}中指定key的value值。
*
* @param arguments 表示指向{@link ArkUI_AccessibilityActionArguments}的指针。
* @param key 表示要查找的参数键名。key的取值需与ArkUI_AccessibilityActionArguments中设置的key一致。
* @param value 表示用于接收查找到的value值的二级指针（输出参数）。
* @return 成功返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*     <br>参数错误返回{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_FindAccessibilityActionArgumentByKey(
    ArkUI_AccessibilityActionArguments* arguments, const char* key, char** value);

/**
 * @brief 获取指向{@link ArkUI_AccessibilityProvider}对象指针的二级指针变量。
 * <br>其中{@link ArkUI_AccessibilityProvider}对象与传入的{@link ArkUI_NodeHandle}的实例一一对应。
 * <br>三方框架将自身UI组件映射为{@link ARKUI_NODE_CUSTOM}类型的{@link RenderNode}并得到{@link ArkUI_NodeHandle}。
 * <br>再调用OH_ArkUI_NativeModule_GetNativeAccessibilityProvider接口获取{@link ArkUI_AccessibilityProvider}指针并注册无障碍回调。
 * <br>最终实现ArkUI无障碍服务对三方框架UI的识别与事件触发。
 * <br>仅当三方框架将自身UI组件映射为{@link ARKUI_NODE_CUSTOM}的{@link RenderNode}，该接口才会生效，否则会报错误码。
 * <br>本接口通过{@link RenderNode}实现三方框架的接入，仅支持{@link ARKUI_NODE_CUSTOM}接入无障碍服务，可以实现无障碍控件树获取能力。
 * <br>不支持多线程并发，由三方框架保证调用时的线程安全。
 *
 * @param node 指向一个{@link ArkUI_NodeHandle}对象的指针。
 * @param provider 表示指向{@link ArkUI_AccessibilityProvider}指针的二级指针（输出参数），用于接收ArkUI_AccessibilityProvider对象指针，
 *     该对象用于注册无障碍回调函数。不能为空指针。
 * @return 返回状态码。
 *     <br>成功返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>参数错误返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>参数错误：1. 传入的参数node或者provider为空指针。
 *     <br>2. node对应的ArkUI_NodeHandle类型不为ARKUI_NODE_CUSTOM。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_GetNativeAccessibilityProvider(
    ArkUI_NodeHandle* node, ArkUI_AccessibilityProvider** provider);
#ifdef __cplusplus
};
#endif
#endif // _NATIVE_INTERFACE_ACCESSIBILITY_H

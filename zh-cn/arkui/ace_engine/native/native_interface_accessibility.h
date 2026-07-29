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
extern "C"{
#endif

/**
 * @brief 无障碍节点信息，用于向无障碍服务、无障碍辅助应用传递节点信息。
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityElementInfo ArkUI_AccessibilityElementInfo;

/**
 * @brief 无障碍事件信息。当无障碍服务或辅助应用要求控件执行操作后，需要发送执行成功事件。
 * 控件自身交互需求要同步状态给无障碍服务或辅助应用时，也需要主动发送事件。
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityEventInfo ArkUI_AccessibilityEventInfo;

/**
 * @brief 该结构体为无障碍第三方操作提供者，用于承载回调函数的实现。
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityProvider ArkUI_AccessibilityProvider;

/**
 * @brief 用于设置无障碍操作的具体参数。
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityActionArguments  ArkUI_AccessibilityActionArguments;

/**
 * @brief 定义ArkUI native组件实例对象指针。
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
    /** 无效值。 */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_INVALID = 0,
    /** 收到事件后，组件需要对点击做出响应。 */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK = 0x00000010,
    /** 收到事件后，组件需要对长按做出响应。 */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_LONG_CLICK = 0x00000020,
    /** 表示获取辅助功能焦点的操作，特定组件已聚焦。 */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_GAIN_ACCESSIBILITY_FOCUS = 0x00000040,
    /** 表示清除辅助功能焦点的操作。 */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLEAR_ACCESSIBILITY_FOCUS = 0x00000080,
    /** 滚动组件响应向前滚动动作。 */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_FORWARD = 0x00000100,
    /** 滚动组件响应反向滚动操作。 */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_BACKWARD = 0x00000200,
    /** 复制文本组件的选定内容。 */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_COPY = 0x00000400,
    /** 粘贴文本组件的选定内容。 */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_PASTE = 0x00000800,
    /** 剪切文本组件的选定内容。 */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CUT = 0x00001000,
    /** 针对文本组件进行选择操作。结合{@link ArkUI_AccessibilityActionArguments}使用，
     * 配置selectTextBegin（表示选择起始位置），selectTextEnd（表示选择结束位置），selectTextInForWard（true表示为前光标，false表示为后光标）进入编辑区选择一段文本内容。
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SELECT_TEXT = 0x00002000,
    /** 设置文本组件的文本内容。 */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SET_TEXT = 0x00004000,
    /** 针对文本组件设置光标位置，结合ArkUI_AccessibilityActionArguments使用，配置可输入文本控件的光标位置。 */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SET_CURSOR_POSITION = 0x00100000,
    /** 焦点移动操作中支持查找下一个焦点。
     * 此处的HTML并不代表网页元素，仅用于表示具有可自行查找下一个可见聚焦组件的能力，与Web支持的能力相似。
     * 实现findNextFocusAccessibilityNode的能力才可配置该属性。
     *  @since 15
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_NEXT_HTML_ITEM = 0x02000000,
    /** 焦点移动操作中支持查找上一个焦点。
     * 此处的HTML并不代表网页元素，仅用于表示具有可自行查找上一个可见聚焦组件的能力，与Web支持的能力相似。
     * 实现findNextFocusAccessibilityNode的能力才可配置该属性。
     *  @since 15
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_PREVIOUS_HTML_ITEM = 0x04000000,
} ArkUI_Accessibility_ActionType;

/**
 * @brief Accessibility事件类型的枚举。
 *
 * @since 13
 */
typedef enum {
    /** 无效值。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_INVALID = 0,
    /** 点击事件，在UI组件响应后发送。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_CLICKED = 0x00000001,
    /** 长按事件，在UI组件响应后发送。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_LONG_CLICKED = 0x00000002,
    /** 被选中事件，控件响应完成后发送。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_SELECTED = 0x00000004,
    /** 文本更新事件，需要在文本更新时发送。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_TEXT_UPDATE = 0x00000010,
    /** 页面更新事件，当页面跳转、切换、大小更改或移动时发送。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_PAGE_STATE_UPDATE = 0x00000020,
    /** 页面内容发生变化时需要发送事件。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_PAGE_CONTENT_UPDATE = 0x00000800,
    /** scrolled事件，当可滚动的组件上发生滚动事件时，会发送此事件。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_SCROLLED = 0x000001000,
    /** Accessibility焦点事件，在UI组件响应后发送。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUSED = 0x00008000,
    /** Accessibility焦点清除事件，在UI组件响应后发送。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUS_CLEARED = 0x00010000,
    /** 主动请求指定节点聚焦。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_REQUEST_ACCESSIBILITY_FOCUS = 0x02000000,
    /** UI组件上报页面打开事件。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_PAGE_OPEN = 0x20000000,
    /** UI组件上报页面关闭事件。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_PAGE_CLOSE = 0x08000000,
    /** 广播Accessibility事件，请求主动播放指定的内容事件。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ANNOUNCE_FOR_ACCESSIBILITY = 0x10000000,
    /** 焦点更新事件，用于焦点更新场景。 */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_FOCUS_NODE_UPDATE = 0x10000001,
} ArkUI_AccessibilityEventType;

/**
 * @brief 无障碍操作内容结构。
 *
 * @since 13
 */
typedef struct {
    /** 无障碍操作类型。 */
    ArkUI_Accessibility_ActionType actionType;
    /** 操作描述信息。 */
    const char* description;
} ArkUI_AccessibleAction;

/**
 * @brief 节点所在坐标位置。
 *
 * @since 13
 */
typedef struct {
    /** 左上角X轴坐标位置。 */
    int32_t leftTopX;
    /** 左上角Y轴坐标位置。 */
    int32_t leftTopY;
    /** 右下角X轴坐标位置。 */
    int32_t rightBottomX;
    /** 右下角Y轴坐标位置。 */
    int32_t rightBottomY;
} ArkUI_AccessibleRect;

/**
 * @brief 用于特定组件设置组件的当前值、最大值、最小值，如Slider、Rating、Progress组件。
 *
 * @since 13
 */
typedef struct {
    /** 最小值。 */
    double min;
    /** 最大值。 */
    double max;
    /** 当前值。 */
    double current;
} ArkUI_AccessibleRangeInfo;

/**
 * @brief 用于特定组件设置组件的行数、列数以及选择模式，如List、Flex、Select、Swiper组件。
 *
 * @since 13
 */
typedef struct {
    /** 行数。 */
    int32_t rowCount;
    /** 列数。 */
    int32_t columnCount;
    /** 值为0时表示仅选中网格的一行，非0值时表示选中网格的多行。 */
    int32_t selectionMode;
} ArkUI_AccessibleGridInfo;

/**
 * @brief 用于特定组件设置组件的属性值，如List、Flex、Select、Swiper组件。
 *
 * @since 13
 */
typedef struct {
    /** 是否是标题。 true表示是标题，false表示不是标题。*/
    bool heading;
    /** 是否被选中。 true表示被选中，false表示未被选中。*/
    bool selected;
    /** 列下标。 */
    int32_t columnIndex;
    /** 行下标。 */
    int32_t rowIndex;
    /** 列跨度。 */
    int32_t columnSpan;
    /** 行跨度。 */
    int32_t rowSpan;
} ArkUI_AccessibleGridItemInfo;

/**
 * @brief Accessibility错误代码状态的枚举。
 *
 * @since 13
 */
typedef enum{
    /** 成功。 */
    ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL = 0,
    /** 失败。 */
    ARKUI_ACCESSIBILITY_NATIVE_RESULT_FAILED = -1,
    /** 无效参数。 */
    ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER = -2,
    /** 内存不足。 */
    ARKUI_ACCESSIBILITY_NATIVE_RESULT_OUT_OF_MEMORY = -3,
} ArkUI_AcessbilityErrorCode;

/**
 * @brief Accessibility搜索类型的枚举。
 *
 * @since 13
 */
typedef enum {
    /** 查询当前节点。 */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_CURRENT = 0,
    /** 查询父节点。 */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_PREDECESSORS = 1 << 0,
    /** 查询兄弟节点。 */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_SIBLINGS = 1 << 1,
    /** 查询下一层孩子节点。 */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_CHILDREN = 1 << 2,
    /** 查询所有孩子节点。 */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_RECURSIVE_CHILDREN = 1 << 3,
} ArkUI_AccessibilitySearchMode;

/**
 * @brief Accessibility焦点类型的枚举。
 *
 * @since 13
 */
typedef enum {
    /** 无效值。 */
    ARKUI_ACCESSIBILITY_NATIVE_FOCUS_TYPE_INVALID = -1,
    /** 输入焦点类型。 */
    ARKUI_ACCESSIBILITY_NATIVE_FOCUS_TYPE_INPUT = 1 << 0,
    /** Accessibility焦点类型。 */
    ARKUI_ACCESSIBILITY_NATIVE_FOCUS_TYPE_ACCESSIBILITY = 1 << 1,
} ArkUI_AccessibilityFocusType;

/**
 * @brief Accessibility焦点移动方向的枚举。
 *
 * @since 13
 */
typedef enum {
    /** 无效值。 */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_INVALID = 0,
    /** 焦点向上移动。 */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_UP = 0x00000001,
    /** 焦点向下移动。 */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_DOWN = 0x00000002,
    /** 焦点向左移动。 */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_LEFT = 0x00000004,
    /** 焦点向右移动。 */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_RIGHT = 0x00000008,
    /** 焦点向下一个可聚焦节点移动，基于查询请求中指定的基准节点。 */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_FORWARD = 0x00000010,
    /** 焦点向上一个可聚焦节点移动，基于查询请求中指定的基准节点。 */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_BACKWARD = 0x00000020,
} ArkUI_AccessibilityFocusMoveDirection;

/**
 * @brief 提供封装的{@link ArkUI_AccessibilityElementInfo}的List实例。
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityElementInfoList ArkUI_AccessibilityElementInfoList;

/**
 * @brief 第三方操作provider回调函数结构定义，需要第三方平台实现的相关函数，
 * 通过{@link OH_ArkUI_AccessibilityProviderRegisterCallback}注册到系统侧。
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityProviderCallbacks {
    /**
    * @brief 查询指定节点的节点信息。由接入方平台实现的回调函数，注册给系统侧调用。
    *
    * @param elementId 无障碍元素的唯一编号。
    * @param mode 表示无障碍搜索模式。
    * @param requestId 表示请求ID。
    * @param elementList 表示无障碍元素信息列表。
    * @return 如果操作成功，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         如果参数错误，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*findAccessibilityNodeInfosById)(int64_t elementId, ArkUI_AccessibilitySearchMode mode,
        int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList);
    /**
    * @brief 基于指定的节点，查询满足指定text内容的节点信息。由接入方平台实现的回调函数，注册给系统侧调用。
    *
    * @param elementId 无障碍元素的唯一编号。
    * @param text 表示无障碍文本。
    * @param requestId 表示请求ID。
    * @param elementList 表示无障碍元素信息列表。
    * @return 如果操作成功，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         如果参数错误，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*findAccessibilityNodeInfosByText)(int64_t elementId, const char* text, int32_t requestId,
        ArkUI_AccessibilityElementInfoList* elementList);
    /**
    * @brief 从指定节点出发，根据焦点类型查找当前已获得焦点的节点，并将该节点元素信息返回。由接入方平台实现的回调函数，注册给系统侧调用。
    *
    * @param elementId 无障碍元素的唯一编号。
    * @param focusType 表示焦点的类型。
    * @param requestId 表示请求ID。
    * @param elementInfo 表示无障碍元素信息。
    * @return 如果操作成功，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         如果参数错误，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*findFocusedAccessibilityNode)(int64_t elementId, ArkUI_AccessibilityFocusType focusType,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    /**
     * @brief 根据参考节点和查找方向，查询下一个可以聚焦的节点。由接入方平台实现的回调函数，注册给系统侧调用。
    *
    * @param elementId 无障碍元素的唯一编号。
    * @param direction 表示查找方向。
    * @param requestId 表示请求ID。
    * @param elementInfo 表示查询到的无障碍元素信息。
    * @return 如果操作成功，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         如果参数错误，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*findNextFocusAccessibilityNode)(
        int64_t elementId, ArkUI_AccessibilityFocusMoveDirection direction,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    /**
    * @brief 在指定节点上执行Action操作。
    *
    * @param elementId 无障碍元素的唯一编号。
    * @param action 表示要执行的动作。
    * @param actionArguments 表示动作的参数。
    * @param requestId 表示请求ID。
    * @return 如果操作成功，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         如果参数错误，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*executeAccessibilityAction)(int64_t elementId, ArkUI_Accessibility_ActionType action,
        ArkUI_AccessibilityActionArguments *actionArguments, int32_t requestId);
    /**
    * @brief 清除当前焦点节点的焦点状态。
    *
    * @return 如果操作成功，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         如果参数错误，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*clearFocusedFocusAccessibilityNode)();
    /**
    * @brief 查询指定节点的当前光标位置。
    *
    * @param elementId 无障碍元素的唯一编号。
    * @param requestId 表示请求ID。
    * @param index 表示光标位置的索引。
    * @return 如果操作成功，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         如果参数错误，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*getAccessibilityNodeCursorPosition)(int64_t elementId, int32_t requestId, int32_t* index);
} ArkUI_AccessibilityProviderCallbacks;

/**
 * @brief 第三方操作provider回调函数结构定义，需要第三方平台实现的相关函数，通过OH_ArkUI_AccessibilityProviderRegisterCallback注册到系统侧。
 *
 * @param provider 表示指向{@link ArkUI_AccessibilityProvider}实例的指针。
 * @param callbacks 表示指向{@link ArkUI_AccessibilityProviderCallbacks}实例的指针。
 * @return 如果操作成功，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
 *         如果参数错误，则返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityProviderRegisterCallback(
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityProviderCallbacks* callbacks);

/**
 * @brief 适配多实例场景第三方操作provider回调函数结构定义。
 * 需要第三方平台实现的相关函数，通过{@link OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance}注册到系统侧。
 * @since 15
 */
typedef struct ArkUI_AccessibilityProviderCallbacksWithInstance {
    /**
    * @brief 基于指定的节点，查询所需的节点信息。由接入方平台实现的回调函数，注册给系统侧调用。支持多实例场景。
    * @param instanceId 第三方框架的实例编码。
    * @param elementId 无障碍元素的唯一编号。
    * @param mode 无障碍服务的搜索模式。
    * @param requestId 请求id，用于关联请求过程，建议日志打印时附带输出该信息，方便问题定位。
    * @param elementList 本次查询到的所有无障碍元素列表。
    * @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*findAccessibilityNodeInfosById)(const char* instanceId, int64_t elementId,
        ArkUI_AccessibilitySearchMode mode, int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList);
    /**
    * @brief 基于指定的节点，查询满足指定组件文本内容的节点信息。由接入方平台实现的回调函数，注册给系统侧调用。支持多实例场景。
    * @param instanceId 第三方框架的实例编码。
    * @param elementId 无障碍元素的唯一编号。
    * @param text 组件需要匹配的文本内容。
    * @param requestId 请求id，用于关联请求过程，方便问题定位。建议日志打印时附带输出该信息，方便定位。
    * @param elementList 本次查询到的所有无障碍元素列表。
    * @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*findAccessibilityNodeInfosByText)(const char* instanceId, int64_t elementId, const char* text,
        int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList);
    /**
    * @brief 从指定节点查找已经聚焦的节点。由接入方平台实现的回调函数，注册给系统侧调用。支持多实例场景。
    * @param instanceId 第三方框架的实例编码。
    * @param elementId 无障碍元素的唯一编号。
    * @param focusType 焦点类型。
    * @param requestId 请求id，用于关联请求过程，建议日志打印时附带输出该信息，方便问题定位。
    * @param elementInfo 本次查询到的无障碍元素。
    * @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*findFocusedAccessibilityNode)(const char* instanceId, int64_t elementId,
        ArkUI_AccessibilityFocusType focusType, int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    /**
    * @brief 从指定节点查询指定方向的下一个可聚焦节点。由接入方平台实现的回调函数，注册给系统侧调用。支持多实例场景。
    * @param instanceId 第三方框架的实例编码。
    * @param elementId 无障碍元素的唯一编号。
    * @param direction 焦点移动方向。
    * @param requestId 请求id，用于关联请求过程，方便问题定位。建议日志打印时附带输出该信息，方便定位。
    * @param elementInfo 本次查询到的无障碍元素。
    * @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*findNextFocusAccessibilityNode)(
        const char* instanceId, int64_t elementId, ArkUI_AccessibilityFocusMoveDirection direction,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    /**
    * @brief 对指定节点执行指定的操作。由接入方平台实现的回调函数，注册给系统侧调用。支持多实例场景。
    * @param instanceId 第三方框架的实例编码。
    * @param elementId 无障碍元素的唯一编号。
    * @param action 需要执行的操作，比如聚焦、点击和长按等。
    * @param actionArguments 控制操作的参数。
    * @param requestId 请求id，用于关联请求过程，方便问题定位。建议日志打印时附带输出该信息，方便定位。
    * @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*executeAccessibilityAction)(const char* instanceId, int64_t elementId,
        ArkUI_Accessibility_ActionType action, ArkUI_AccessibilityActionArguments *actionArguments, int32_t requestId);
    /**
    * @brief 清除当前获焦的节点。由接入方平台实现的回调函数，注册给系统侧调用。支持多实例场景。
    * @param instanceId 第三方框架的实例编码。
    * @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*clearFocusedFocusAccessibilityNode)(const char* instanceId);
    /**
    * @brief 获取当前组件中（文本组件）光标位置。由接入方平台实现的回调函数，注册给系统侧调用。支持多实例场景。
    * @param instanceId 第三方框架的实例编码。
    * @param elementId 无障碍元素的唯一编号。
    * @param requestId 请求id，用于关联请求过程，方便问题定位。建议日志打印时附带输出该信息，方便定位。
    * @param index 光标的位置结果。
    * @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
    *         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
    */
    int32_t (*getAccessibilityNodeCursorPosition)(const char* instanceId, int64_t elementId,
        int32_t requestId, int32_t* index);
} ArkUI_AccessibilityProviderCallbacksWithInstance;
/**
 * @brief 无障碍多实例场景第三方平台将回调函数注册到系统侧。
 * @param instanceId 第三方平台接入的实例ID，用于区分多实例场景中不同的第三方实例，ID由第三方平台指定与维护。
 * @param provider 第三方平台接入provider句柄。
 * @param callbacks 表示指向{@link ArkUI_AccessibilityProviderCallbacksWithInstance}实例的指针。
 * @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
 *         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
 * @since 15
 */
int32_t OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance(const char* instanceId,
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityProviderCallbacksWithInstance* callbacks);

/**
 * @brief 主动上报事件接口，通知无障碍服务。
 * 
 * @param provider 第三方平台接入provider句柄。
 * @param eventInfo 表示指向Accessibility事件信息的指针。
 * @param callback 表示指向SendAccessibilityAsyncEvent回调。
 * @since 13
 */
void OH_ArkUI_SendAccessibilityAsyncEvent(
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityEventInfo* eventInfo,
    void (*callback)(int32_t errorCode));

/**
 * @brief 在指定的list中增加element成员，并返回element结构。
 * 
 * @param list 指定的{@link ArkUI_AccessibilityElementInfoList}结构，新创建的ElementInfo成员加入该list后返回给函数调用方。
 * @return 返回创建完成的ArkUI_AccessibilityElementInfo结构指针，如果创建失败返回NULL。
 * @since 13
 */
ArkUI_AccessibilityElementInfo* OH_ArkUI_AddAndGetAccessibilityElementInfo(
    ArkUI_AccessibilityElementInfoList* list);
/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置无障碍元素的唯一标识（elementId）。
*
* @note elementId是无障碍组件树中节点的唯一标识，用于无障碍服务定位和引用特定节点。\n
* 无障碍服务查找节点信息、执行操作和移动焦点时均依赖此标识。\n
* 三方框架需保证同一组件树中各节点的elementId全局唯一，否则可能导致无障碍服务无法正确查找节点。\n
* elementId的值由三方框架自行分配和维护，建议使用递增整数或稳定的组件标识。\n
*
* @param elementInfo ArkUI_AccessibilityElementInfo指针。
* @param elementId 无障碍元素的唯一编号，在当前组件树中必须唯一。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetElementId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t elementId);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置父节点的无障碍编号（parentId）。
*
* @note parentId用于构建无障碍组件树的层级关系，标识当前节点的父节点。无障碍服务在遍历节点树、查找兄弟节点时依赖父子关系。\n
* 若当前节点为根节点，建议将parentId设置为-1或0（与根节点自身的elementId不同即可）。\n
* parentId指向的父节点elementId必须在组件树中真实存在，否则无障碍服务向上遍历时可能出现异常。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param parentId 表示元素的父组件无障碍编号，应指向已存在的父节点elementId。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetParentId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t parentId);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件类型。
*
* @note componentType用于标识无障碍节点的组件类型，如Button、Text、Image、List。\n
* 无障碍服务（如无障碍辅助应用）根据组件类型决定如何向用户描述和交互该节点。\n
* 例如，Button类型会被朗读为按钮，Text类型会被朗读为文本。\n
* 三方框架可使用自身组件类型名称，建议使用与ArkUI组件名称一致的字符串以便获得最佳朗读效果。\n
* 建议使用的组件类型名称包括：Button、Text、Image、List、TextInput、Slider、Rating、Progress、CheckBox、Toggle、Grid、Swiper、Select、Tab。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param componentType 表示元素所属的组件类型字符串，不能为空指针。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetComponentType(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* componentType);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件文本内容。
*
* @note contents是组件的主要文本内容，无障碍辅助应用会将其作为主要播报内容朗读给用户。\n
* 对于文本类组件（如Text、TextInput），contents通常设置为组件显示的文本。\n
* 对于非文本类组件（如Button、Image），若设置了accessibilityText，则无障碍辅助应用优先使用accessibilityText。
* 通过{@link OH_ArkUI_AccessibilityElementInfoSetAccessibilityText}设置accessibilityText，否则使用contents作为朗读内容。
* 当组件同时设置了contents和accessibilityText时，无障碍辅助应用优先使用accessibilityText。\n
* contents不支持传入空指针，传入空指针将返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param contents 表示元素被无障碍服务所识别的文本内容，不能为空指针。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetContents(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* contents);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置提示文本。
*
* @note hintText用于为组件提供辅助说明，通常用于可编辑组件的占位提示文本（例如输入框）。\n
* 无障碍辅助应用在组件处于提示状态（isHint为true）时，会朗读hintText代替contents。例如，当输入框为空时显示的占位文本“请输入用户名”，应通过hintText传递。\n
* hintText与isHint配合使用：当isHint为true时，无障碍辅助应用播报hintText。当isHint为false时，播报contents。\n
* isHint通过{@link OH_ArkUI_AccessibilityElementInfoSetIsHint}设置，contents通过{@link OH_ArkUI_AccessibilityElementInfoSetContents}设置。\n
* hintText不支持传入空指针，传入空指针将返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param hintText 表示提示文本，不能为空指针。默认为""。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetHintText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hintText);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置无障碍专用的替代文本。
*
* @note accessibilityText是无障碍专用的替代文本，用于覆盖contents提供给无障碍辅助应用的内容。\n
* 当组件设置了accessibilityText且不为空时，无障碍辅助应用会优先播报accessibilityText而非contents。\n
* 适用于视觉内容需要额外描述的场景，例如：图片组件可设置accessibilityText为“一张大海照片”，即使图片本身无文本内容，无障碍辅助应用也能向用户描述图片含义。\n
* 若accessibilityText为空字符串，无障碍辅助应用会回退使用contents。\n
* accessibilityText不支持传入空指针，传入空指针将返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param accessibilityText 表示Accessibility文本，不能为空指针。默认为""。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityText);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置无障碍描述信息。
*
* @note accessibilityDescription用于为组件提供额外的无障碍描述信息。\n
* 无障碍辅助应用在播报完组件的主要内容（accessibilityText或contents）后，会继续播报accessibilityDescription。\n
* 例如，一个按钮的contents为“提交”，accessibilityDescription可设置为“点击提交表单数据”，无障碍辅助应用将播报“提交，点击提交表单数据”。\n
* 此属性适用于需要为用户提供额外操作提示或状态说明的场景。\n
* accessibilityDescription不支持传入空指针，传入空指针将返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param accessibilityDescription 表示Accessibility描述信息，不能为空指针。默认为""。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityDescription(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityDescription);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置子节点数量和子节点ID集合。
*
* @note childNodeIds用于构建无障碍组件树的父子关系，标识当前节点的所有直接子节点。\n
* 无障碍服务通过childNodeIds遍历子节点来获取完整的无障碍树结构。\n
* 每次调用本接口将清空之前设置的所有子节点信息，替换为本次传入的子节点集合（覆盖式更新，非追加）。\n
* childNodeIds中的每个值对应已存在的子节点的elementId。\n
* childCount必须大于0，且childNodeIds数组中至少包含childCount个有效元素。\n
* childNodeIds和elementInfo不支持传入空指针，childCount不支持小于等于0，否则返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param childCount 表示孩子节点数量，必须大于0。
* @param childNodeIds 表示孩子节点id集合，每个ID应指向已存在的子节点elementId，不能为空指针。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetChildNodeIds(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t childCount, int64_t* childNodeIds);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件支持的无障碍操作列表。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param operationCount 组件支持的action数量，必须大于0。
* @param operationActions 组件支持的action数组，不能为空指针。具体支持的action类型可以参考{@link ArkUI_Accessibility_ActionType}。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetOperationActions(ArkUI_AccessibilityElementInfo* elementInfo,
    int32_t operationCount, ArkUI_AccessibleAction* operationActions);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件在屏幕上的矩形区域。
*
* @note screenRect定义了组件在屏幕上的位置和大小，以像素为单位。\n
* 无障碍服务使用screenRect进行焦点高亮绘制、触摸目标定位和元素可见性判断。\n
* 无障碍辅助应用等辅助应用依赖screenRect来确定焦点框的显示位置，帮助用户了解当前聚焦元素在屏幕上的位置。\n
* 如果screenRect的区域面积为0或不在屏幕可见范围内，该节点可能不会被辅助应用聚焦。\n
* screenRect和elementInfo不支持传入空指针，否则返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param screenRect 表示屏幕区域，包含左上角和右下角坐标，不能为空指针。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetScreenRect(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleRect* screenRect);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否可勾选。
*
* @note 适用于具备可勾选语义的组件（例如ArkUI的CheckBox、Toggle、Radio）。\n
* 无障碍辅助应用会根据checkable状态向用户播报“可勾选”提示，并告知用户可以通过操作来切换勾选状态。\n
* 设置checkable为true时，应同时通过{@link OH_ArkUI_AccessibilityElementInfoSetChecked}来设置checked来表示当前勾选状态。
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param checkable 表示是否可勾选。true表示可勾选，false表示不可勾选。默认值为false。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetCheckable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checkable);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置当前的勾选状态。
*
* @note 无障碍辅助应用会根据checked状态播报“已勾选”或“未勾选”。\n
* 本接口仅设置勾选状态，不会自动设置checkable属性。\n
* 若需要组件被识别为可勾选，需同时调用{@link OH_ArkUI_AccessibilityElementInfoSetCheckable}设置checkable属性为true。\n
* 仅设置checked而不设置checkable为true时，checked状态不会在辅助应用中体现。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param checked 表示是否被勾选。true表示已勾选，false表示未勾选。默认值false。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetChecked(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checked);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否可聚焦。
*
* @note 适用于可聚焦的交互组件（例如ArkUI的TextInput、Button）。\n
* 无障碍辅助应用等辅助应用在遍历可聚焦节点时，会跳过focusable为false的节点。\n
* 设置focusable为true的组件通常也需要通过{@link OH_ArkUI_AccessibilityElementInfoSetClickable}设置clickable为true，并注册相应的操作动作。\n
* focusable与accessibilityFocused是不同的概念：focusable表示输入焦点能力，accessibilityFocused表示无障碍辅助焦点的当前状态。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param focusable 表示是否可聚焦。true表示可聚焦，false表示不可聚焦。默认值false。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetFocusable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool focusable);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否已聚焦。
*
* @note 无障碍辅助应用在获焦时会播报当前焦点元素的信息。\n
* 设置isFocused为true时，通常应同时通过{@link OH_ArkUI_AccessibilityElementInfoSetFocusable}设置focusable为true，否则焦点状态的含义不完整。\n
* isFocused与accessibilityFocused是不同的概念：isFocused表示输入焦点状态，accessibilityFocused（由{@link OH_ArkUI_AccessibilityElementInfoSetAccessibilityFocused}设置）表示无障碍辅助焦点状态。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param isFocused 表示是否聚焦。true表示已聚焦，false表示未聚焦。默认值false。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isFocused);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件是否在屏幕上可见。
*
* @note 无障碍辅助应用等辅助应用在遍历节点时，默认会跳过isVisible为false的节点，不会对这些节点聚焦或播报。\n
* 对于因滚动而暂时不在可视区域的组件，建议设置isVisible为false。\n
* 若一个可交互组件被错误地设置为不可见，用户将无法通过辅助应用访问该组件。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param isVisible 表示是否可见。true表示可见，false表示不可见。默认值false。所有需要被辅助应用识别的组件必须显式设置为true。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetVisible(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isVisible);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置当前的无障碍辅助焦点状态。
*
* @note 当用户通过辅助应用的焦点移动操作浏览界面时，被聚焦的节点accessibilityFocused应为true。\n
* 无障碍辅助应用会对accessibilityFocused为true的节点播报其内容，并在屏幕上绘制焦点高亮框。\n
* 无障碍服务在执行{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_GAIN_ACCESSIBILITY_FOCUS}和{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLEAR_ACCESSIBILITY_FOCUS}操作时，三方框架应相应更新此状态。\n
* 并通过发送{@link ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUSED}或{@link ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUS_CLEARED}事件通知系统。\n
* accessibilityFocused与isFocused不同：前者是无障碍辅助焦点，后者是输入焦点（键盘焦点）。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param accessibilityFocused 表示是否被无障碍聚焦。true表示被无障碍聚焦，false表示未被无障碍聚焦。默认值false。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityFocused);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否处于选中状态。
*
* @note 适用于具备选中语义的组件（例如ArkUI的Tab、ListItem）。\n
* 无障碍辅助应用会根据selected状态播报“已选中”或“未选中”。\n
* 在Tab页签场景中，selected为true的Tab页签会被朗读为当前活动页签。\n
* 在列表场景中，selected可与accessibilityGroup（通过{@link OH_ArkUI_AccessibilityElementInfoSetAccessibilityGroup}设置）配合使用，标记当前激活的列表项。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param selected 表示是否被选中。true表示被选中，false表示未选中。默认值false。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetSelected(
    ArkUI_AccessibilityElementInfo* elementInfo, bool selected);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否支持点击操作。
*
* @note 无障碍辅助应用会向用户提示该组件可点击，用户可通过辅助应用执行点击操作时，系统会通过{@link ArkUI_AccessibilityProviderCallbacks}中的executeAccessibilityAction回调通知三方框架。\n
* 设置clickable为true时，通常需要通过{@link OH_ArkUI_AccessibilityElementInfoSetOperationActions}在operationActions中添加{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK}，否则用户无法通过辅助应用对该组件执行点击操作。\n
* clickable与enabled（通过{@link OH_ArkUI_AccessibilityElementInfoSetEnabled}设置）应配合使用：当clickable为true但enabled为false时，无障碍辅助应用会播报“已禁用”，提示用户该组件虽可点击但当前不可用。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param clickable 表示是否支持点击。true表示支持，false表示不支持。默认值false。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool clickable);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否支持长按操作。
*
* @note 无障碍辅助应用会向用户提示该组件支持长按，用户可通过辅助应用执行长按操作时，系统会通过{@link ArkUI_AccessibilityProviderCallbacks}中的executeAccessibilityAction回调通知三方框架。\n
* 设置longClickable为true时，通常需要通过{@link OH_ArkUI_AccessibilityElementInfoSetOperationActions}在operationActions中添加{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_LONG_CLICK}。\n
* 否则用户无法通过辅助应用对该组件执行长按操作。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param longClickable 表示是否支持长按。true表示支持，false表示不支持。默认值false。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetLongClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool longClickable);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件是否处于启用状态。
*
* @note 当isEnabled为false时，无障碍辅助应用会播报“已禁用”或“不可用”，提示用户该组件当前不可交互。\n
* 对于被禁用的组件（如灰色按钮），应设置isEnabled为false，并通过{@link OH_ArkUI_AccessibilityElementInfoSetClickable}设置clickable为true，这样无障碍辅助应用会提示用户该组件存在但当前不可用。\n
* 如果isEnabled为false且clickable也为false，无障碍辅助应用可能完全跳过该组件。\n
* 所有需要被用户交互的组件必须显式设置为true。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param isEnabled 表示是否启用。true表示启用，false表示未启用。默认值false。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetEnabled(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isEnabled);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否为密码输入框。
*
* @note 当isPassword为true时，无障碍辅助应用不会朗读具体的密码字符内容，而是播报“密码框”或“已输入密码”等替代提示，以防止密码被朗读泄露。\n
* 对于TextInput等文本输入组件，若用于密码输入场景，必须设置isPassword为true。\n
* 若未设置或设置为false，无障碍辅助应用可能直接朗读密码内容，造成安全隐患。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param isPassword 表示是否为密码。true表示是密码，false表示不是密码。默认值false。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetIsPassword(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isPassword);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否支持滚动操作。
*
* @note 适用于支持内容滚动的容器组件（例如ArkUI的List、Grid、Scroll、Swiper）。\n
* 无障碍辅助应用等辅助应用会根据scrollable状态向用户提供滚动操作提示，用户可通过辅助应用执行向前滚动（{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_FORWARD}）或向后滚动（{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_BACKWARD}）操作。\n
* 设置scrollable为true时，需要通过{@link OH_ArkUI_AccessibilityElementInfoSetOperationActions}在operationActions中添加滚动操作。\n
* 包括{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_FORWARD}和{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_BACKWARD}。\n
* 否则用户无法通过辅助应用对该组件执行滚动操作。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param scrollable 表示是否支持滚动。true表示支持，false表示不支持。默认值false。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetScrollable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool scrollable);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置文本内容是否可编辑。
*
* @note 适用于文本内容可被用户编辑的组件（例如ArkUI的TextInput、TextArea）。\n
* 无障碍辅助应用会根据editable状态向用户提示该组件可编辑，并允许用户通过辅助应用输入或修改文本。\n
* 设置editable为true的组件，通常还应通过{@link OH_ArkUI_AccessibilityElementInfoSetOperationActions}注册相应的无障碍操作动作，\n
* 如{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SET_TEXT}、{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_COPY}、\n
* {@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_PASTE}、{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CUT}等，以便用户通过辅助应用执行编辑操作。\n
* editable为true且isPassword（通过{@link OH_ArkUI_AccessibilityElementInfoSetIsPassword}设置）为true时，无障碍辅助应用会播报“密码编辑框”。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param editable 表示是否支持编辑。true表示支持，false表示不支持。默认值false。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetEditable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool editable);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置是否处于提示文本状态。
*
* @note 当isHint为true时，无障碍辅助应用会朗读hintText（提示文本，通过{@link OH_ArkUI_AccessibilityElementInfoSetHintText}设置）而非contents（主文本内容，通过{@link OH_ArkUI_AccessibilityElementInfoSetContents}设置）。\n
* 此属性主要用于可编辑文本组件（如TextInput）在用户尚未输入内容时显示占位提示文本的场景。\n
* 例如：输入框显示“请输入用户名”时，isHint应设为true，hintText应设为“请输入用户名”；用户输入内容后，isHint应设为false，contents应设为用户输入的文本。\n
* 若isHint设置为true但未设置hintText，无障碍辅助应用可能播报空内容。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param isHint 表示是否为提示状态。true表示是提示状态，false表示不是提示状态。
*               在提示状态下无障碍辅助应用播报hintText，否则播报contents。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetIsHint(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isHint);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置范围值信息。
*
* @note rangeInfo用于设置具有连续范围值的组件的当前值、最小值和最大值，适用于在连续数值范围内取值的组件（例如ArkUI的Slider、Rating、Progress、SeekBar）。\n
* 无障碍辅助应用会根据rangeInfo播报当前值和范围，例如“进度50%，范围0到100”。\n
* rangeInfo中的current表示当前值，min表示最小值，max表示最大值。\n
* 设置rangeInfo时，应确保min不大于max，current应在min和max之间。\n
* rangeInfo和elementInfo不支持传入空指针，否则返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param rangeInfo 表示特定组件的当前值、最大值、最小值，不能为空指针。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetRangeInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleRangeInfo* rangeInfo);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置网格信息。
*
* @note gridInfo用于设置网格类容器的行数、列数和选择模式，适用于网格/列表类容器组件（例如ArkUI的Grid、List、Flex、Select、Swiper）。\n
* 无障碍辅助应用会根据gridInfo播报网格的结构信息，如“第2行，共5行3列”。\n
* rowCount表示行数，columnCount表示列数，selectionMode表示选择模式（值为0表示单行选择，非0表示多行选择）。\n
* gridInfo和elementInfo不支持传入空指针，否则返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param gridInfo 表示特定组件的行数、列数以及选择模式，不能为空指针。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetGridInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridInfo* gridInfo);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置网格容器中子项的属性信息。
*
* @note gridItem用于设置Grid组件中每个子项的属性，包括是否为标题、是否被选中、所在行列下标及跨度信息。\n
* 适用于网格/列表类容器的子项（例如ArkUI的Grid、List、Flex、Select、Swiper的子项）。\n
* 无障碍辅助应用会根据gridItem的rowIndex和columnIndex播报子项的位置信息，如“第2行第3列”。\n
* {@link ArkUI_AccessibleGridItemInfo}中的heading为true时，无障碍辅助应用会播报“标题”。\n
* gridItem和elementInfo不支持传入空指针，否则返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param gridItem 表示网格子项的属性值，不能为空指针。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetGridItemInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridItemInfo* gridItem);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置选中文本的起始位置。
*
* @note selectedTextStart用于文本类可编辑组件，标记当前选中文本的起始字符索引位置（从0开始计数）。\n
* 无障碍辅助应用等辅助应用会根据selectedTextStart和selectedTextEnd播报当前选中的文本范围。\n
* 当用户通过辅助应用执行{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SELECT_TEXT}操作时，三方框架应获取起始位置。
* 通过{@link ArkUI_AccessibilityActionArguments}中的selectTextBegin参数获取起始位置。
* selectedTextStart应与selectedTextEnd（通过{@link OH_ArkUI_AccessibilityElementInfoSetSelectedTextEnd}设置）配合使用，且selectedTextStart不应大于selectedTextEnd。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param selectedTextStart 文本类控件使用，设置选中文本的起始位置索引（从0开始）。应与selectedTextEnd配合使用。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetSelectedTextStart(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t selectedTextStart);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置选中文本的结束位置。
*
* @note selectedTextEnd用于文本类可编辑组件，标记当前选中文本的结束字符索引位置（从0开始计数）。\n
* 无障碍辅助应用等辅助应用会根据selectedTextStart和selectedTextEnd计算并播报选中的文本内容。\n
* selectedTextEnd应与selectedTextStart配合使用，且selectedTextEnd不应小于selectedTextStart。\n
* 其中selectedTextStart通过{@link OH_ArkUI_AccessibilityElementInfoSetSelectedTextStart}设置。\n
* 当没有文本被选中时，selectedTextStart和selectedTextEnd可以设置为相同的值（即光标位置）。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param selectedTextEnd 文本类控件使用，设置选中文本的结束位置索引（从0开始）。应与selectedTextStart配合使用。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetSelectedTextEnd(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t selectedTextEnd);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置当前获焦或高亮子项的位置索引。
*
* @note currentItemIndex用于含多项子节点的容器组件（例如ArkUI的List、Select、Swiper、TabBar），表示当前获得焦点或处于激活状态的子项在容器中的位置索引（从0开始计数）。\n
* 无障碍辅助应用会播报当前项的位置信息，如“第3项，共10项”。\n
* currentItemIndex应与itemCount（通过{@link OH_ArkUI_AccessibilityElementInfoSetItemCount}设置）配合使用，以便辅助应用播报“第X项，共Y项”的完整信息。\n
* currentItemIndex的值应在0到itemCount-1的范围内。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param currentItemIndex 当前获焦控件的位置索引（从0开始），应与itemCount配合使用。
*                       适用于含多项子节点的容器组件（例如ArkUI的List、Select、Swiper、Tab）。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetCurrentItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t currentItemIndex);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置当前屏幕可见区域中第一个元素的位置索引。
*
* @note startItemIndex用于支持内容滚动的容器组件（例如ArkUI的List、Select、Swiper、TabBar），表示当前屏幕可见区域中第一个子项的位置索引（从0开始计数）。\n
* 无障碍辅助应用等辅助应用根据startItemIndex和endItemIndex（通过{@link OH_ArkUI_AccessibilityElementInfoSetEndItemIndex}设置）判断可见区域范围，用于优化焦点移动和播报。\n
* startItemIndex应小于等于endItemIndex，且两者均应在0到itemCount-1的范围内。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param startItemIndex 当前屏幕可见区域中第一个元素的位置索引（从0开始）。
*                       含多项子节点的容器组件使用（例如ArkUI的List、Select、Swiper、Tab_Bar）。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetStartItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t startItemIndex);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置当前屏幕可见区域中最后一个元素的位置索引。
*
* @note endItemIndex用于支持内容滚动的容器组件（例如ArkUI的List、Select、Swiper、TabBar），表示当前屏幕可见区域中最后一个子项的位置索引（从0开始计数）。\n
* 无障碍辅助应用等辅助应用根据startItemIndex（通过{@link OH_ArkUI_AccessibilityElementInfoSetStartItemIndex}设置）和endItemIndex判断可见区域范围，当用户执行滚动操作时，辅助应用可据此播报滚动进度。\n
* endItemIndex应大于等于startItemIndex，且两者均应在0到itemCount-1的范围内。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param endItemIndex 当前屏幕可见区域中最后一个元素的位置索引（从0开始）。
*                     含多项子节点的容器组件使用（例如ArkUI的List、Select、Swiper、Tab_Bar）。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetEndItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t endItemIndex);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置容器中子项的总数。
*
* @note itemCount用于含多项子节点的容器组件（例如ArkUI的List、Select、Swiper、TabBar），表示容器中子项的总数量。\n
* 无障碍辅助应用等辅助应用结合currentItemIndex（通过{@link OH_ArkUI_AccessibilityElementInfoSetCurrentItemIndex}设置）和itemCount播报位置信息，如“第3项，共10项”。\n
* itemCount的值应为容器中所有子项的总数（包括可见和不可见的），而不仅是当前屏幕可见区域的子项数。\n
* itemCount应为非负整数，设置为0表示容器为空。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param itemCount 表示容器中子项的总数（包括可见和不可见的），用于辅助应用播报“第X项，共Y项”。
*                  含多项子节点的容器组件使用（例如ArkUI的List、Select、Swiper、Tab）。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetItemCount(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t itemCount);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置滚动偏移量。
*
* @note offset用于可滚动类容器组件（如List、Grid、Scroll），表示内容区相对于元素顶部坐标的滚动像素偏移量。\n
* 无障碍服务使用offset来判断滚动位置，辅助应用可据此播报滚动进度。\n
* 当用户执行{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_FORWARD}或{@link ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_BACKWARD}操作后，三方框架应在更新后的节点信息中同步更新offset值。\n
* offset为0表示内容区未滚动（处于初始位置），正值表示向下/向右滚动的像素距离。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param offset 对于可滚动类控件，如List、Grid，内容区相对于元素顶部坐标的滚动像素偏移量（单位：像素）。
*               offset为0表示未滚动，正值表示已滚动的距离。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityOffset(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t offset);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置无障碍分组。
*
* @note accessibilityGroup表示是否将该组件及其所有子组件作为一个整体对待。\n
* 当accessibilityGroup为true时，无障碍辅助应用会将该节点视为一个整体，不会单独聚焦或播报其子节点的信息，而是将子节点的文本内容合并后一起播报。\n
* 此属性适用于将一组相关内容（如一个列表项包含图标和文本）作为一个无障碍单元的场景。\n
* 例如：一个列表项包含商品图片和商品名称，设置accessibilityGroup为true后，无障碍辅助应用会将整个列表项作为一个节点播报，而不是分别播报图片和文本。\n
* accessibilityGroup为false时，无障碍辅助应用会逐个遍历子节点。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param accessibilityGroup 表示是否启用无障碍分组。true表示将组件及其子组件作为一个整体播报，false表示逐个遍历子节点。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityGroup(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityGroup);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置无障碍重要性级别。
*
* @note accessibilityLevel用于控制组件是否被无障碍辅助服务识别，影响无障碍节点树中该节点的可见性。\n
* 无障碍辅助应用等辅助应用根据accessibilityLevel决定是否向用户展示该节点。\n
* 取值范围及含义如下：- “auto”：由系统根据当前组件的属性自动判断该组件是否重要，决定是否让辅助服务识别该组件。\n
* 通常具有可交互属性（如clickable）或文本内容的组件会被自动识别为重要。\n
* - “yes”：表示该组件重要，允许辅助服务识别该组件。无论组件属性如何，辅助服务都会识别。\n
* - “no”：表示该组件不重要，不允许辅助服务识别该组件。辅助服务会跳过该节点，但其子节点仍可被识别。\n
* - “no-hide-descendants”：表示该组件及其所有子孙节点都不重要，辅助服务不会识别该组件及其子孙节点。适用于纯装饰性容器，避免辅助服务播报无意义的内容。\n
* accessibilityLevel不支持传入空指针，传入空指针将返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param accessibilityLevel 表示组件的无障碍重要性级别，取值为“auto”/“yes”/“no”/“no-hide-descendants”，不能为空指针。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityLevel);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置组件的Z序。
*
* @note zIndex用于控制元素在垂直于屏幕的Z轴上的层级位置。\n
* 当多个组件在屏幕上重叠时，zIndex值较大的组件会覆盖zIndex值较小的组件。\n
* 此属性主要供UiTest自动化测试框架使用，用于识别组件的层叠顺序。\n
* 无障碍服务在确定焦点移动方向时也可能参考zIndex进行判断。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param zIndex 组件z序，用于控制元素在垂直于屏幕的z轴上的位置。UiTest需要使用。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetZIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t zIndex);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置透明度。
*
* @note opacity表示组件的透明度。此属性主要供UiTest自动化测试框架使用，用于识别组件的视觉透明状态。\n
* 取值范围为0到1，其中1表示完全不透明，0表示完全透明。\n
* 注意：传入NaN值将返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER，但超出0到1范围的值（如负数或大于1的值）不会被自动修正，建议始终传入0到1之间的有效值。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param opacity 表示透明度。其取值范围是0到1，其中1表示完全不透明，0表示完全透明。不支持NaN值。UiTest需要使用。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityOpacity(
    ArkUI_AccessibilityElementInfo* elementInfo, float opacity);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置背景色。
*
* @note backgroundColor表示组件的背景颜色。此属性主要供UiTest自动化测试框架使用，用于识别组件的视觉背景色。\n
* 数据格式为“#ARGB”字符串，例如非透明白色为“#FFFFFFFF”，半透明红色为“#80FF0000”。\n
* backgroundColor不支持传入空指针，传入空指针将返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param backgroundColor 表示背景色。数据为“#ARGB”格式，例如非透明白色即“#FFFFFFFF”。不能为空指针。UiTest需要使用。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetBackgroundColor(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundColor);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置背景图片。
*
* @note backgroundImage表示组件的背景图片资源。此属性主要供UiTest自动化测试框架使用，用于识别组件的视觉背景图。\n
* backgroundImage不支持传入空指针，传入空指针将返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param backgroundImage 表示背景图片资源路径或描述。不能为空指针。UiTest需要使用。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetBackgroundImage(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundImage);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置模糊效果。
*
* @note blur表示组件的模糊效果参数。此属性主要供UiTest自动化测试框架使用，用于识别组件的视觉模糊状态。\n
* blur不支持传入空指针，传入空指针将返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param blur 表示模糊度。不能为空指针。UiTest需要使用。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetBlur(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* blur);

/**
* @brief 为{@link ArkUI_AccessibilityElementInfo}设置触摸测试的响应逻辑及节点阻塞规则。
*
* @note hitTestBehavior用于控制组件在触摸测试过程中的响应行为，决定触摸事件是否可以穿透该组件。\n
* 此属性主要供UiTest自动化测试框架使用。\n
* 取值范围参考{@link ArkUI_HitTestMode}，包括：- “Default”：默认行为，不阻断触摸事件。\n
* - “Block”：阻断自身及子组件的触摸事件。\n
* - “Transparent”：自身不响应触摸事件，但子组件可以响应。\n
* - “None”：自身和子组件都不响应触摸事件。\n
* hitTestBehavior不支持传入空指针，传入空指针将返回ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER。\n
*
* @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
* @param hitTestBehavior 表示hitTest模式，不能为空指针。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityElementInfoSetHitTestBehavior(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hitTestBehavior);

/**
 * @brief 创建一个{@link ArkUI_AccessibilityElementInfo}对象。
 *
 * 创建后需要调用{@link OH_ArkUI_DestoryAccessibilityElementInfo}释放。
 *
 * @return 返回{@link ArkUI_AccessibilityElementInfo}对象。
 * @since 13
 */
ArkUI_AccessibilityElementInfo* OH_ArkUI_CreateAccessibilityElementInfo(void);

/**
 * @brief 销毁一个{@link ArkUI_AccessibilityElementInfo}对象。
 *
 * @param elementInfo 表示指向{@link ArkUI_AccessibilityElementInfo}的指针。
 * @since 13
 */
void OH_ArkUI_DestoryAccessibilityElementInfo(ArkUI_AccessibilityElementInfo* elementInfo);

/**
 * @brief 创建一个{@link ArkUI_AccessibilityEventInfo}对象。
 *
 * 创建后需要调用{@link OH_ArkUI_DestoryAccessibilityEventInfo}释放。
 *
 * @return 返回{@link ArkUI_AccessibilityEventInfo}对象。
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
* @param eventInfo 表示事件信息。
* @param eventType 表示事件类型。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityEventSetEventType(
    ArkUI_AccessibilityEventInfo* eventInfo,  ArkUI_AccessibilityEventType eventType);
/**
* @brief 为{@link ArkUI_AccessibilityEventInfo}设置主动播报的内容。
*
* @param eventInfo 表示事件信息。
* @param textAnnouncedForAccessibility 表示主动播报的内容。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityEventSetTextAnnouncedForAccessibility(
    ArkUI_AccessibilityEventInfo* eventInfo,  const char* textAnnouncedForAccessibility);

/**
* @brief 为{@link ArkUI_AccessibilityEventInfo}设置请求焦点id。
*
* @param eventInfo 表示事件信息。
* @param requestFocusId 表示请求焦点id。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityEventSetRequestFocusId(
    ArkUI_AccessibilityEventInfo* eventInfo,  int32_t requestFocusId);

/**
* @brief 为{@link ArkUI_AccessibilityEventInfo}设置elementInfo。
*
* @param eventInfo 表示事件信息。
* @param elementInfo 表示{@link ArkUI_AccessibilityElementInfo}元素信息。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_AccessibilityEventSetElementInfo(
    ArkUI_AccessibilityEventInfo* eventInfo,  ArkUI_AccessibilityElementInfo* elementInfo);

/**
* @brief 获取{@link ArkUI_AccessibilityActionArguments}中指定key的value值。
*
* @param arguments 表示{@link ArkUI_AccessibilityActionArguments}对象信息。
* @param key 表示key。
* @param value 表示value。
* @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。
*         参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
* @since 13
*/
int32_t OH_ArkUI_FindAccessibilityActionArgumentByKey(
    ArkUI_AccessibilityActionArguments* arguments, const char* key, char** value);

/**
 * @brief 获取指向{@link ArkUI_AccessibilityProvider}对象指针的二级指针变量。\n
 *        其中{@link ArkUI_AccessibilityProvider}对象与传入的
 *        {@link ArkUI_NodeHandle}的实例一一对应。\n
 *        三方框架将自身UI组件映射为{@link ARKUI_NODE_CUSTOM}类型的
 *        RenderNode并得到{@link ArkUI_NodeHandle}。\n
 *        再调用OH_ArkUI_NativeModule_GetNativeAccessibilityProvider接口获取
 *        {@link ArkUI_AccessibilityProvider}指针并注册无障碍回调。\n
 *        最终实现ArkUI无障碍服务对三方框架UI的识别与事件触发。\n
 *        仅当三方框架将自身UI组件映射为{@link ARKUI_NODE_CUSTOM}的RenderNode，该接口才会生效，否则会报错误码。\n
 *        本接口通过RenderNode实现三方框架的接入，仅支持ARKUI_NODE_CUSTOM接入无障碍服务，可以实现无障碍控件树获取能力。\n
 *        不支持多线程并发，由三方框架保证调用时的线程安全。\n
 *
 * @param node 指向一个{@link ArkUI_NodeHandle}对象的指针。
 * @param provider 指向一个{@link ArkUI_AccessibilityProvider}类型对象的指针。provider用于注册无障碍回调函数。
 * @return 返回状态码。\n
 *         成功返回 {@link ARKUI_ERROR_CODE_NO_ERROR}。\n
 *         参数错误返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID}。\n
 *         参数错误：1. 传入的参数node或者provider为空指针。2. node对应的ArkUI_NodeHandle类型不为ARKUI_NODE_CUSTOM。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_GetNativeAccessibilityProvider(
    ArkUI_NodeHandle* node, ArkUI_AccessibilityProvider** provider);

/**
 * @brief 为无障碍节点信息{@link ArkUI_AccessibilityElementInfo}设置组件标识，可用于自动化测试识别特定组件。
 *
 * @param elementInfo 表示无障碍节点信息元素信息。
 * @param identifier 表示组件的唯一标识字符串。<br>需保证上报的组件树中的组件标识唯一，且字符串长度不大于1024，超过1024会截断使用。
 * @return 成功返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL}。\n
 * 参数错误返回 {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER}。
 * @since 24
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetComponentIdentifier(
    ArkUI_AccessibilityElementInfo *elementInfo, const char *identifier);

#ifdef __cplusplus
};
#endif
#endif // _NATIVE_INTERFACE_ACCESSIBILITY_H
/** @} */

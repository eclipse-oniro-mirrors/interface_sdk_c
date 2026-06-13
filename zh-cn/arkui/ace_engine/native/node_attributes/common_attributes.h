/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 12
 */

/**
 * @file common_attributes.h
 *
 * @brief Defines the common property and method types for the native module.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_COMMON_ATTRIBUTES_H
#define ARKUI_COMMON_ATTRIBUTES_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief 触摸测试控制枚举值。
*
* @since 12
*/
typedef enum {
    /** 默认触摸测试效果。自身及子节点响应触摸测试，但阻塞兄弟节点的触摸测试，不影响祖先节点的触摸测试。 */
    ARKUI_HIT_TEST_MODE_DEFAULT = 0,
    /** 自身响应触摸测试，阻塞子节点、兄弟节点和祖先节点的触摸测试。 */
    ARKUI_HIT_TEST_MODE_BLOCK,
    /** 自身和子节点都响应触摸测试，不会阻塞兄弟节点和祖先节点的触摸测试。 */
    ARKUI_HIT_TEST_MODE_TRANSPARENT,
    /** 自身不响应触摸测试，不会阻塞子节点、兄弟节点和祖先节点的触摸测试。 */
    ARKUI_HIT_TEST_MODE_NONE,
    /**
     * 自身和子节点响应触摸测试，阻止所有优先级较低的兄弟节点和父节点参与触摸测试。
     * @since 20
     */
    ARKUI_HIT_TEST_MODE_BLOCK_HIERARCHY,
    /**
     * 自身不响应触摸测试，并且所有的后代（孩子，孙子等）也不响应触摸测试，不会影响祖先节点的触摸测试。
     * @since 20
     */
    ARKUI_HIT_TEST_MODE_BLOCK_DESCENDANTS
} ArkUI_HitTestMode;

/**
* @brief 控制组件的显隐枚举值。
*
* @since 12
*/
typedef enum {
    /** 显示。 */
    ARKUI_VISIBILITY_VISIBLE = 0,
    /** 隐藏，但参与布局进行占位。 */
    ARKUI_VISIBILITY_HIDDEN,
    /** 隐藏，但不参与布局，不进行占位。 */
    ARKUI_VISIBILITY_NONE
} ArkUI_Visibility;

/**
* @brief 组件被悬停时的效果。
*
* @since 23
*/
typedef enum {
    /** 默认效果。 */
    ARKUI_HOVER_EFFECT_AUTO = 0,
    /** 缩放效果。 */
    ARKUI_HOVER_EFFECT_SCALE,
    /** 高亮效果。 */
    ARKUI_HOVER_EFFECT_HIGHLIGHT,
    /** 无效果。 */
    ARKUI_HOVER_EFFECT_NONE
} ArkUI_HoverEffect;

/**
* @brief 应用程序内焦点管理的优先级级别。确定UI组件在交互期间接收焦点的顺序。
*
* @since 23
*/
typedef enum {
    /** 默认优先级。 */
    ARKUI_FOCUS_PRIORITY_AUTO = 0,
    /** 容器内优先获焦的优先级。 */
    ARKUI_FOCUS_PRIORITY_PRIOR = 2000,
    /** 上一次容器整体失焦时获焦节点的优先级。 */
    ARKUI_FOCUS_PRIORITY_PREVIOUS = 3000
} ArkUI_FocusPriority;

/**
* @brief 组件的UI状态枚举，用于处理状态样式。
*
* @since 20
*/
typedef enum {
    /** 正常状态。 */
    UI_STATE_NORMAL = 0,
    /** 按压状态。 */
    UI_STATE_PRESSED = 1 << 0,
    /** 获焦状态。 */
    UI_STATE_FOCUSED = 1 << 1,
    /** 禁用状态。 */
    UI_STATE_DISABLED = 1 << 2,
    /** 选中状态，此状态仅由某些特定类型的组件支持，分别是Checkbox、Radio、Toggle、List、Grid和MenuItem。 */
    UI_STATE_SELECTED = 1 << 3,
    /**
* 悬浮状态。
* @since 26.0.0
*/
    UI_STATE_HOVERED = 1 << 4
} ArkUI_UIState;

/**
* @brief 定义焦点移动方向的枚举值。
*
* @since 18
*/
typedef enum {
    /** 向前移动焦点。 */
    ARKUI_FOCUS_MOVE_FORWARD = 0,
    /** 向后移动焦点。 */
    ARKUI_FOCUS_MOVE_BACKWARD,
    /** 向上移动焦点。 */
    ARKUI_FOCUS_MOVE_UP,
    /** 向下移动焦点。 */
    ARKUI_FOCUS_MOVE_DOWN,
    /** 向左移动焦点。 */
    ARKUI_FOCUS_MOVE_LEFT,
    /** 向右移动焦点。 */
    ARKUI_FOCUS_MOVE_RIGHT
} ArkUI_FocusMove;

/**
* @brief 定义支持响应区域设置的事件工具类型。
*
* @since 23
*/
typedef enum {
    /** 所有输入工具类型。 */
    ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_ALL = 0,
    /** 手指类型。 */
    ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_FINGER = 1,
    /** 手写笔类型。 */
    ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_PEN = 2,
    /** 鼠标类型。 */
    ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_MOUSE = 3
} ArkUI_ResponseRegionSupportedTool;

/**
* @brief 定义截图的可选项。
*
* @since 15
*/
typedef struct ArkUI_SnapshotOptions ArkUI_SnapshotOptions;

/**
* @brief 创建一个截图选项，当返回值不再使用时必须通过{@link OH_ArkUI_DestroySnapshotOptions()}释放。
*
* @return 返回指向创建的截图选项对象的指针。如果对象返回空指针，则表示创建失败，失败的原因可能是地址空间已满。
* @since 15
*/
ArkUI_SnapshotOptions* OH_ArkUI_CreateSnapshotOptions();

/**
* @brief 销毁截图选项指针。
*
* @param snapshotOptions 截图选项。
* @since 15
*/
void OH_ArkUI_DestroySnapshotOptions(ArkUI_SnapshotOptions* snapshotOptions);

/**
* @brief 配置截图选项中的缩放属性。
*
* @param snapshotOptions 截图选项。
* @param scale 缩放值。
* @return 错误码
*     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
*     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
*     <br>异常原因：传入参数验证失败，参数不能为空。
*
* @since 15
*/
int32_t OH_ArkUI_SnapshotOptions_SetScale(ArkUI_SnapshotOptions* snapshotOptions, float scale);

/**
* @brief 设置截图选项中的色彩空间。
*
* @param snapshotOptions 截图选项指针。
* @param colorSpace 指定截图使用的色彩空间。
*     <br>如果知道需要截图的组件使用的色彩空间，可以通过colorSpace参数指定，并将isAuto设置为false，以达到预期的截图效果。
*     <br>支持的取值为：3（RGB色域为Display P3类型）、4（RGB色域为SRGB类型）、27（RGB色域为DISPLAY BT2020类型）。
*     <br>默认值：4
*     <br>仅当isAuto设置为false，该参数设置生效。
* @param isAuto 是否由系统自动决定所使用的色彩空间。
*     <br>true表示系统自动决定所使用的色彩空间。在不确定组件使用的色彩空间时，建议将isAuto设置为true，让系统根据实际情况自动决定使用的色彩空间。
*     <br>false表示使用通过colorSpace字段设置的色彩空间类型进行截图。
*     <br>默认值：false
* @return 错误码。
*     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
*     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
* @since 23
*/
int32_t OH_ArkUI_SnapshotOptions_SetColorMode(ArkUI_SnapshotOptions* snapshotOptions, int32_t colorSpace, bool isAuto);

/**
* @brief 设置截图选项中的动态范围模式。
*
* @param snapshotOptions 截图选项指针。
* @param dynamicRangeMode 指定截图使用的动态范围模式。
*     <br>如果知道截图对象使用的动态范围模式，可通过dynamicRangeMode参数指定动态范围模式，并将isAuto设置为false，以达到预期的截图效果。
*     <br>支持的取值为：{@link ArkUI_DynamicRangeMode}枚举值。
*     <br>默认值：ARKUI_DYNAMIC_RANGE_MODE_STANDARD
*     <br>仅当isAuto设置为false，该参数设置生效。
* @param isAuto 是否由系统自动决定所使用的动态范围模式。
*     <br>true表示系统自动决定所使用的动态范围模式。在不确定组件使用的动态范围模式时，建议将isAuto设置为true，让系统根据实际情况自动决定使用的动态范围模式。
*     <br>false表示使用通过dynamicRangeMode字段设置的动态范围模式进行截图。
*     <br>默认值：false
* @return 错误码。
*     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
* 	<br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
* @since 23
*/
int32_t OH_ArkUI_SnapshotOptions_SetDynamicRangeMode(
    ArkUI_SnapshotOptions* snapshotOptions, int32_t dynamicRangeMode, bool isAuto);

/**
* @brief 可见区域变化监听的参数。
*
* @since 17
*/
typedef struct ArkUI_VisibleAreaEventOptions ArkUI_VisibleAreaEventOptions;

/**
* @brief 创建可见区域变化监听的参数。
*
* @return 可见区域变化监听的参数。
* @since 17
*/
ArkUI_VisibleAreaEventOptions* OH_ArkUI_VisibleAreaEventOptions_Create();

/**
* @brief 销毁可见区域变化监听的参数。
*
* @param option 需要销毁的实例。
* @since 17
*/
void OH_ArkUI_VisibleAreaEventOptions_Dispose(ArkUI_VisibleAreaEventOptions* option);

/**
* @brief 设置阈值数组。
*
* @param option 可见区域变化监听的参数实例。
* @param value 阈值数组。其中每个元素代表组件可见面积（即组件在屏幕显示区的面积，只计算父组件内的面积，超出父组件部分不会计算）与组件自身面积的比值。
*     每个阈值的取值范围为[0.0, 1.0]，如果开发者设置的阈值超出该范围，则会实际取值0.0或1.0。
* @param size 阈值数组大小。
* @return 错误码。
*    <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
*    <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
*    <br>异常原因：传入参数验证失败，参数不能为空。
* @since 17
*/
int32_t OH_ArkUI_VisibleAreaEventOptions_SetRatios(ArkUI_VisibleAreaEventOptions* option, float* value, int32_t size);

/**
* @brief 设置预期更新间隔，单位为ms。定义了开发者期望的更新间隔。
*
* @param option 可见区域变化监听的参数实例。
* @param value 预期更新间隔，单位为ms。定义了开发者期望的更新间隔。默认值：1000。
* @return 错误码。
*    <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
*    <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常
*    <br>异常原因：传入参数验证失败，参数不能为空。
* @since 17
*/
int32_t OH_ArkUI_VisibleAreaEventOptions_SetExpectedUpdateInterval(
    ArkUI_VisibleAreaEventOptions *option, int32_t value);

/**
* @brief 设置可见区域计算模式。
*
* @param option 可见区域变化监听的参数实例。
* @param measureFromViewport 当measureFromViewport设置为true时，系统在计算该组件的可见区域时，会考虑父组件的NODE_CLIP属性设置。如果父组件的NODE_CLIP为false，
*     则认为其内的子组件可以超出其区域进行显示，因此超出父组件的区域也将被视为可见区域纳入计算；如果父组件的NODE_CLIP设置为true，则组件超出父组件的区域会被裁剪，
*     无法显示，因此会被视为不可见区域进行计算。而当measureFromViewport设置为false时，则不考虑NODE_CLIP的影响，直接将组件超出父组件的部分视为不可见区域。
*     默认值：false
* @return 错误码。
*     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
*     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
*     <br>异常原因：传入参数验证失败，参数不能为空。
* @since 22
*/
int32_t OH_ArkUI_VisibleAreaEventOptions_SetMeasureFromViewport(
    ArkUI_VisibleAreaEventOptions* option, bool measureFromViewport);

/**
* @brief 获取阈值数组。
*
* @param option 可见区域变化监听的参数实例。
* @param value 阈值数组。
* @param size 阈值数组大小。
* @return 错误码。
*     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
*     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
*     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 数组大小不够。
*     <br>异常原因：传入参数验证失败，参数不能为空。
* @since 17
*/
int32_t OH_ArkUI_VisibleAreaEventOptions_GetRatios(ArkUI_VisibleAreaEventOptions* option, float* value, int32_t* size);

/**
* @brief 获取预期更新间隔。
*
* @param option 可见区域变化监听的参数实例。
* @return 预期更新间隔，单位为ms。定义了开发者期望的更新间隔。默认值：1000。
* @since 17
*/
int32_t OH_ArkUI_VisibleAreaEventOptions_GetExpectedUpdateInterval(ArkUI_VisibleAreaEventOptions* option);

/**
* @brief 获取可见区域计算模式。
*
* @param option 可见区域变化监听的参数实例。
* @return 获取可见区域计算模式。
*     当measureFromViewport设置为true时，系统在计算该组件的可见区域时，会考虑父组件的NODE_CLIP属性设置。如果父组件的NODE_CLIP为false，则认为其内的子组件可以超出其区域进行显示，
*     因此超出父组件的区域也将被视为可见区域纳入计算；如果父组件的NODE_CLIP设置为true，则组件超出父组件的区域会被裁剪，无法显示，因此会被视为不可见区域进行计算。
*     而当measureFromViewport设置为false时，则不考虑NODE_CLIP的影响，直接将组件超出父组件的部分视为不可见区域。
*     默认值：false
* @since 22
*/
bool OH_ArkUI_VisibleAreaEventOptions_GetMeasureFromViewport(ArkUI_VisibleAreaEventOptions* option);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_COMMON_ATTRIBUTES_H
/** @} */
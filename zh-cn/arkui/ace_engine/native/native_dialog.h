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
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 12
 */

/**
 * @file native_dialog.h
 *
 * @brief 提供ArkUI在Native侧的自定义弹窗接口定义集合。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_DIALOG_H
#define ARKUI_NATIVE_DIALOG_H

#include <stdbool.h>
#include "native_type.h"
#include "native_node.h"
#include "native_material.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief 弹窗关闭的触发方式。
*
* @since 12
*/
typedef enum {
    /**
     * 点击三键back、侧滑（左滑/右滑）、键盘ESC触发。
     */
    DIALOG_DISMISS_BACK_PRESS = 0,
    /**
     * 点击遮障层触发。
     */
    DIALOG_DISMISS_TOUCH_OUTSIDE,
    /**
     * 点击关闭按钮。
     */
    DIALOG_DISMISS_CLOSE_BUTTON,
    /**
     * 下拉关闭。
     */
    DIALOG_DISMISS_SLIDE_DOWN,
} ArkUI_DismissReason;

/**
* @brief 枚举对话框的状态。
*
* @syscap SystemCapability.ArkUI.ArkUI.Full
*
* @since 20
*/
typedef enum {
    /**
     * @brief 未初始化，控制器未与dialog绑定时。
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    DIALOG_UNINITIALIZED = 0,
    /**
     * @brief 已初始化，控制器与dialog绑定后。
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    DIALOG_INITIALIZED,
    /**
     * @brief 显示中，dialog显示动画过程中。
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    DIALOG_APPEARING,
    /**
     * @brief 已显示，dialog显示动画结束。
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    DIALOG_APPEARED,
    /**
     * @brief 消失中，dialog消失动画过程中。
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    DIALOG_DISAPPEARING,
    /**
     * @brief 已消失，dialog消失动画结束后。
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    DIALOG_DISAPPEARED,
} ArkUI_DialogState;

/**
* @brief 设置弹窗显示层级。
*
* @since 15
*/
typedef enum {
    /**
     * 显示在应用最上层。
     */
    ARKUI_LEVEL_MODE_OVERLAY = 0,
    /**
     * 嵌入式显示在应用的页面内。
     */
    ARKUI_LEVEL_MODE_EMBEDDED,
} ArkUI_LevelMode;

/**
* @brief 指定嵌入式弹窗的蒙层覆盖区域。
*
* @since 15
*/
typedef enum {
    /**
     * 弹窗蒙层按照显示页面给定的布局约束显示。
     */
    ARKUI_IMMERSIVE_MODE_DEFAULT = 0,
    /**
     * 弹窗蒙层可扩展至覆盖状态栏和导航条。
     */
    ARKUI_IMMERSIVE_MODE_EXTEND,
} ArkUI_ImmersiveMode;

/**
 * @brief 弹窗在子窗口中的显示模式。
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * 弹窗在屏幕居中显示。
     * @since 26.0.0
     */
    OH_ARKUI_DIALOG_DISPLAY_MODE_SCREEN_BASED = 0,
    /**
     * 弹窗在应用窗口居中显示。
     * @since 26.0.0
     */
    OH_ARKUI_DIALOG_DISPLAY_MODE_WINDOW_BASED,
} OH_ArkUI_DialogDisplayModeInSubWindow;

/**
* @brief Invoked when the dialog box is closed.
*
* @since 12
*/
typedef bool (*ArkUI_OnWillDismissEvent)(int32_t reason);

/**
 * @brief 定义弹窗关闭事件对象。
 *
 * @since 12
 */
typedef struct ArkUI_DialogDismissEvent ArkUI_DialogDismissEvent;

/**
 * @brief 定义自定义弹窗的内容对象。
 *
 * @since 19
 */
typedef struct ArkUI_CustomDialogOptions ArkUI_CustomDialogOptions;

/**
 * @brief ArkUI提供的Native侧自定义弹窗接口集合。
 *
 * @version 1
 * @since 12
 */
typedef struct {
    /**
    * @brief 创建自定义弹窗并返回指向自定义弹窗的指针。
    *
    * @note This method must be called before the <b>show</b> method.
    * @return 返回指向自定义弹窗的指针，如果创建失败，则返回空指针。
    */
    ArkUI_NativeDialogHandle (*create)();
    /**
    * @brief 销毁自定义弹窗。
    * <br>| 参数项                                                                                | 描述 ||------------------
    * ------------------------------------------------------------------| -- || {@link ArkUI_NativeDialogHandle} handle
    * | 指向自定义弹窗控制器的指针。 |
    *
    * @param handle Indicates the pointer to the custom dialog box controller.
    */
    void (*dispose)(ArkUI_NativeDialogHandle handle);
    /**
    * @brief 挂载自定义弹窗内容。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param content 弹窗内容根节点指针。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*setContent)(ArkUI_NativeDialogHandle handle, ArkUI_NodeHandle content);
    /**
    * @brief 卸载自定义弹窗内容。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*removeContent)(ArkUI_NativeDialogHandle handle);
    /**
    * @brief 设置自定义弹窗对齐方式。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param alignment 对齐方式，参数类型{@link ArkUI_Alignment}。
    * @param offsetX 弹窗的水平偏移量，浮点型，单位：vp。
    * @param offsetY 弹窗的垂直偏移量，浮点型，单位：vp。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*setContentAlignment)(ArkUI_NativeDialogHandle handle, int32_t alignment, float offsetX, float offsetY);
    /**
    * @brief 重置setContentAlignment方法设置的属性，使用系统默认的对齐方式，默认值：ARKUI_ALIGNMENT_TOP_START，参考{@link ArkUI_Alignment}。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*resetContentAlignment)(ArkUI_NativeDialogHandle handle);
    /**
    * @brief 设置自定义弹窗是否开启模态样式的弹窗。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param isModal 设置是否开启模态窗口，模态窗口有蒙层，非模态窗口无蒙层。为true时开启模态窗口，为false时不开启模态窗口。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*setModalMode)(ArkUI_NativeDialogHandle handle, bool isModal);
    /**
    * @brief 设置自定义弹窗是否允许通过点击遮罩层退出。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param autoCancel 设置是否允许通过点击遮罩层退出，true表示关闭弹窗，false表示不关闭弹窗。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*setAutoCancel)(ArkUI_NativeDialogHandle handle, bool autoCancel);
    /**
    * @brief 设置自定义弹窗遮罩属性。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param maskColor 设置遮罩颜色，0xargb格式。
    * @param maskRect 遮蔽层区域范围的指针，遮蔽层区域内的事件不透传，在遮蔽层区域外的事件透传。参数类型{@link ArkUI_Rect}。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*setMask)(ArkUI_NativeDialogHandle handle, uint32_t maskColor, const ArkUI_Rect* maskRect);
    /**
    * @brief 设置弹窗背景色。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param backgroundColor 设置弹窗背景颜色，0xargb格式。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*setBackgroundColor)(ArkUI_NativeDialogHandle handle, uint32_t backgroundColor);
    /**
    * @brief 设置弹窗背板圆角半径。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param topLeft 设置弹窗背板左上角圆角半径，单位：vp。默认值：从API version 12开始，为32vp。API version 11及之前版本，为24vp。
    * @param topRight 设置弹窗背板右上角圆角半径，单位：vp。默认值：从API version 12开始，为32vp。API version 11及之前版本，为24vp。
    * @param bottomLeft 设置弹窗背板左下圆角半径，单位：vp。默认值：从API version 12开始，为32vp。API version 11及之前版本，为24vp。
    * @param bottomRight 设置弹窗背板右下角圆角半径，单位：vp。默认值：从API version 12开始，为32vp。API version 11及之前版本，为24vp。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*setCornerRadius)(ArkUI_NativeDialogHandle handle, float topLeft, float topRight,
        float bottomLeft, float bottomRight);
    /**
    * @brief 设置弹窗宽度占栅格宽度的个数。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param gridCount 默认为按照窗口大小自适应，最大栅格数为{@link 系统最大栅格数}。
    *     取值范围：大于等于0的整数。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*setGridColumnCount)(ArkUI_NativeDialogHandle handle, int32_t gridCount);
    /**
    * @brief 弹窗容器样式是否可以自定义。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param enableCustomStyle 弹窗容器样式是否可以自定义。
    *     默认值：false
    *     true：弹窗容器样式不能自定义，宽度自适应子节点，圆角为0，弹窗背景色透明；false：弹窗容器样式可以自定义，高度自适应子节点，宽度由栅格系统定义，圆角半径24vp，PC/2in1设备避让屏幕边缘以及窗口标题栏。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*enableCustomStyle)(ArkUI_NativeDialogHandle handle, bool enableCustomStyle);
    /**
    * @brief 弹窗容器是否使用自定义弹窗动画。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param enableCustomAnimation true:使用自定义动画，关闭系统默认动画；false:使用系统默认动画。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*enableCustomAnimation)(ArkUI_NativeDialogHandle handle, bool enableCustomAnimation);
    /**
    * @brief 当触发系统定义的返回操作、键盘ESC关闭交互操作时，如果注册了该回调函数，弹窗不会立即关闭，而是由用户决定是否关闭。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param eventHandler 弹窗关闭的回调函数。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*registerOnWillDismiss)(ArkUI_NativeDialogHandle handle, ArkUI_OnWillDismissEvent eventHandler);
    /**
    * @brief 显示自定义弹窗。
    *
    * @param handle 指向自定义弹窗控制器的指针。
    * @param showInSubWindow 是否在子窗口显示弹窗。true表示在子窗显示弹窗。false表示不在子窗显示弹窗。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*show)(ArkUI_NativeDialogHandle handle, bool showInSubWindow);
    /**
    * @brief 关闭自定义弹窗，如已关闭，则不生效。该接口后台执行是异步的，在关闭动画执行完成后弹窗节点才会下树。如需关闭后再次打开弹窗，请在延迟300ms以后再执行。
    *
    * @param handle 指向自定义弹窗控制器的指针。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。此时仅表示关闭指令下发成功，不代表弹窗完全关闭。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*close)(ArkUI_NativeDialogHandle handle);
    /**
    * @brief 注册系统关闭自定义弹窗的监听事件。
    *
    * @param handle 指向自定义弹窗控制器的指针。
    * @param userData 用户自定义数据指针。
    * @param callback 监听自定义弹窗关闭的回调事件。
    *     <br>- event: 回调函数的入参，捕获关闭原因。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    */
    int32_t (*registerOnWillDismissWithUserData)(
        ArkUI_NativeDialogHandle handle, void* userData, void (*callback)(ArkUI_DialogDismissEvent* event));
} ArkUI_NativeDialogAPI_1;

/**
 * @brief ArkUI提供的Native侧自定义弹窗接口集合。
 *
 * @version 2
 * @since 15
 */
typedef struct {
    /**
     * @brief 
     * @since 15
     */
    ArkUI_NativeDialogAPI_1 nativeDialogAPI1;
    /**
     * @brief 弹窗避让键盘后，和键盘之间距离。
     *
	 * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param distance 避让键盘的距离，单位为vp。
     * @param unit 避让距离的单位，参数类型{@link ArkUI_LengthMetricUnit}。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} 接口初始化错误。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 15
     */
    int32_t (*setKeyboardAvoidDistance)(ArkUI_NativeDialogHandle handle, float distance, ArkUI_LengthMetricUnit unit);

    /**
    * @brief 设置弹窗的显示层级。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param levelMode 显示层级的枚举值， 类型为{@link ArkUI_LevelMode}。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    * @since 15
    */
    int32_t (*setLevelMode)(ArkUI_NativeDialogHandle handle, ArkUI_LevelMode levelMode);

    /**
    * @brief 设置弹窗显示层级页面下的节点id。
    *
    * @note This method must be called before the <b>setLevelMode</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param uniqueId 指定节点id，会查找该节点所在页面，并将弹窗显示在该页面下。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    * @since 15
    */
    int32_t (*setLevelUniqueId)(ArkUI_NativeDialogHandle handle, int32_t uniqueId);

    /**
    * @brief 设置嵌入式弹窗蒙层的显示区域。
    *
    * @note This method must be called before the <b>show</b> method.
    * @param handle 指向自定义弹窗控制器的指针。
    * @param immersiveMode 显示区域类型的枚举值， 类型为{@link ArkUI_ImmersiveMode}。
    * @return 错误码。
    *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
    *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
    * @since 15
    */
    int32_t (*setImmersiveMode)(ArkUI_NativeDialogHandle handle, ArkUI_ImmersiveMode immersiveMode);
} ArkUI_NativeDialogAPI_2;

/**
 * @brief ArkUI提供的Native侧自定义弹窗接口集合。
 *
 * @version 3
 * @since 19
 */
typedef struct {
    /**
     * @brief ArkUI提供的Native侧自定义弹窗接口集合，范围是{@link ArkUI_NativeDialogAPI_1}。
     * @since 19
     */
    ArkUI_NativeDialogAPI_1 nativeDialogAPI1;
    /**
     * @brief ArkUI提供的Native侧自定义弹窗接口集合，范围是{@link ArkUI_NativeDialogAPI_2}。
     * @since 19
     */
    ArkUI_NativeDialogAPI_2 nativeDialogAPI2;
    /**
     * @brief 设置自定义弹窗显示的顺序。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param levelOrder 自定义弹窗显示的顺序。
     *     <br>默认值：0，取值范围：[-100000.0, 100000.0]。超出取值范围属性不生效。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setLevelOrder)(ArkUI_NativeDialogHandle handle, double levelOrder);
    /**
     * @brief 注册自定义弹窗显示之前的回调函数。
     *
     * @param handle 指向自定义弹窗控制器的指针。
     * @param userData 用户自定义数据。
     * @param callback 自定义弹窗显示之前的回调函数。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */

    int32_t (*registerOnWillAppear)(
        ArkUI_NativeDialogHandle handle, void* userData, void (*callback)(void* userData));

    /**
     * @brief 注册自定义弹窗显示之后的回调函数。
     *
     * @param handle 指向自定义弹窗控制器的指针。
     * @param userData 用户自定义数据。
     * @param callback 自定义弹窗显示之后的回调函数。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*registerOnDidAppear)(
        ArkUI_NativeDialogHandle handle, void* userData, void (*callback)(void* userData));

    /**
     * @brief 注册自定义弹窗关闭之前的回调函数。
     *
     * @param handle 指向自定义弹窗控制器的指针。
     * @param userData 用户自定义数据。
     * @param callback 自定义弹窗关闭之前的回调函数。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*registerOnWillDisappear)(
        ArkUI_NativeDialogHandle handle, void* userData, void (*callback)(void* userData));

    /**
     * @brief 注册自定义弹窗关闭之后的回调函数。
     *
     * @param handle 指向自定义弹窗控制器的指针。
     * @param userData 用户自定义数据。
     * @param callback 自定义弹窗关闭之后的回调函数。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*registerOnDidDisappear)(
        ArkUI_NativeDialogHandle handle, void* userData, void (*callback)(void* userData));

    /**
     * @brief 设置自定义弹窗的边框宽度。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param top 上边框的宽度。
     * @param right 右边框的宽度。
     * @param bottom 下边框的宽度。
     * @param left 左边框的宽度。
     * @param unit 指定宽度单位，默认为vp。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setBorderWidth)(
        ArkUI_NativeDialogHandle handle, float top, float right, float bottom, float left, ArkUI_LengthMetricUnit unit);

    /**
     * @brief 设置自定义弹窗的边框颜色。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param top 上边框的颜色。
     * @param right 右边框的颜色。
     * @param bottom 下边框的颜色。
     * @param left 左边框的颜色。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setBorderColor)(
        ArkUI_NativeDialogHandle handle, uint32_t top, uint32_t right, uint32_t bottom, uint32_t left);

    /**
     * @brief 设置自定义弹窗的边框样式。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param top 上边框的样式。参数类型{@link ArkUI_BorderStyle}，默认值为ARKUI_BORDER_STYLE_SOLID。
     * @param right 右边框的样式。参数类型{@link ArkUI_BorderStyle}，默认值为ARKUI_BORDER_STYLE_SOLID。
     * @param bottom 下边框的样式。参数类型{@link ArkUI_BorderStyle}，默认值为ARKUI_BORDER_STYLE_SOLID。
     * @param left 左边框的样式。参数类型{@link ArkUI_BorderStyle}，默认值为ARKUI_BORDER_STYLE_SOLID。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setBorderStyle)(
        ArkUI_NativeDialogHandle handle, int32_t top, int32_t right, int32_t bottom, int32_t left);

    /**
     * @brief 设置自定义弹窗的背板宽度。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param width 背板宽度。
     * @param unit 指定宽度的单位，默认为vp。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setWidth)(ArkUI_NativeDialogHandle handle, float width, ArkUI_LengthMetricUnit unit);

    /**
     * @brief 设置自定义弹窗的背板高度。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param height 背板高度。
     * @param unit 指定高度的单位，默认为vp。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setHeight)(ArkUI_NativeDialogHandle handle, float height, ArkUI_LengthMetricUnit unit);

    /**
     * @brief 设置自定义弹窗的背板阴影。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param shadow 背板阴影样式，枚举值。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setShadow)(ArkUI_NativeDialogHandle handle, ArkUI_ShadowStyle shadow);

    /**
     * @brief 设置自定义弹窗的背板阴影。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param customShadow 自定义阴影参数，格式与{@link ArkUI_NodeAttributeType}中的NODE_SHADOW属性一致。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setCustomShadow)(ArkUI_NativeDialogHandle handle, const ArkUI_AttributeItem* customShadow);

    /**
     * @brief 设置自定义弹窗的背板模糊材质。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param blurStyle 背板模糊材质，枚举值。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setBackgroundBlurStyle)(ArkUI_NativeDialogHandle handle, ArkUI_BlurStyle blurStyle);

    /**
     * @brief 设置自定义弹窗避让键盘模式。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param keyboardAvoidMode 避让键盘模式，枚举值。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setKeyboardAvoidMode)(ArkUI_NativeDialogHandle handle, ArkUI_KeyboardAvoidMode keyboardAvoidMode);

    /**
     * @brief 设置自定义弹窗是否响应悬停态。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param enableHoverMode 是否响应悬停态，默认false。true表示响应悬停态，false表示不响应悬停态。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*enableHoverMode)(ArkUI_NativeDialogHandle handle, bool enableHoverMode);

    /**
     * @brief 设置悬停态下自定义弹窗默认展示区域。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param hoverModeAreaType 悬停态区域，枚举值。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setHoverModeArea)(ArkUI_NativeDialogHandle handle, ArkUI_HoverModeAreaType hoverModeAreaType);

    /**
     * @brief 设置自定义弹窗是否获取焦点。
     *
     * @param handle 指向自定义弹窗控制器的指针。
     * @param focusable 自定义弹窗是否获取焦点。true表示自动获取焦点，false表示不自动获取焦点。默认值：true
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setFocusable)(ArkUI_NativeDialogHandle handle, bool focusable);

    /**
     * @brief 设置自定义弹窗的背景模糊效果。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param backgroundBlurStyleOptions 背景模糊效果。参数{@link ArkUI_AttributeItem}格式：
     *     <br>.value[0].i32：表示深浅色模式，取{@link ArkUI_ColorMode}枚举值。
     *     <br>.value[1]?.i32：表示取色模式，取{@link ArkUI_AdaptiveColor}枚举值。
     *     <br>.value[2]?.f32：表示模糊效果程度，取[0.0,1.0]范围内的值，超出有效值区间时取边界值。
     *     <br>.value[3]?.u32：表示灰阶模糊参数，对黑色的提亮程度，有效值范围为[0,127]，超出有效值范围，取0。
     *     <br>.value[4]?.u32：表示灰阶模糊参数，对白色的压暗程度，有效值范围为[0,127]，超出有效值范围，取0。
     *     <br>.value[5]?.i32：表示模糊激活策略，取{@link ArkUI_BlurStyleActivePolicy}枚举值。
     *     <br>.value[6]?.u32：表示窗口失焦后，窗口内控件模糊效果会被移除，此时控件背板的颜色，0xargb类型。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setBackgroundBlurStyleOptions)(
        ArkUI_NativeDialogHandle handle, const ArkUI_AttributeItem* backgroundBlurStyleOptions);

    /**
     * @brief 设置自定义弹窗的背景效果参数。
     *
     * @note This method must be called before the <b>show</b> method.
     * @param handle 指向自定义弹窗控制器的指针。
     * @param backgroundEffect 背景效果参数。参数{@link ArkUI_AttributeItem}格式：
     *     <br>.value[0].f32：表示模糊半径，单位为vp。
     *     <br>.value[1]?.f32：表示饱和度。
     *     <br>.value[2]?.f32：表示亮度。
     *     <br>.value[3]?.u32：表示颜色，0xargb类型。
     *     <br>.value[4]?.i32：表示取色模式，取{@link ArkUI_AdaptiveColor}枚举值。
     *     <br>.value[5]?.u32：表示灰阶模糊参数，对黑色的提亮程度，有效值范围为[0,127]，超出有效值范围，取0。
     *     <br>.value[6]?.u32：表示灰阶模糊参数，对白色的压暗程度，有效值范围为[0,127]，超出有效值范围，取0。
     *     <br>.value[7]?.i32：表示模糊激活策略，取{@link ArkUI_BlurStyleActivePolicy}枚举值。
     *     <br>.value[8]?.u32：表示窗口失焦后，窗口内控件模糊效果会被移除，此时控件背板的颜色，0xargb类型。
     * @return 错误码。
     *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
     * @since 19
     */
    int32_t (*setBackgroundEffect)(ArkUI_NativeDialogHandle handle, const ArkUI_AttributeItem* backgroundEffect);
} ArkUI_NativeDialogAPI_3;

/**
 * @brief 设置是否需要屏蔽系统关闭弹窗行为，true表示屏蔽系统行为，不关闭弹窗，false表示不屏蔽。
 *
 * @param event 弹窗关闭事件对象指针。
 * @param shouldBlockDismiss 实现需要屏蔽系统关闭弹窗行为。
 * @since 12
 */
void OH_ArkUI_DialogDismissEvent_SetShouldBlockDismiss(ArkUI_DialogDismissEvent* event, bool shouldBlockDismiss);

/**
 * @brief 获取弹窗关闭事件对象中的用户自定义数据指针。
 *
 * @param event 弹窗关闭事件对象指针。
 * @return 用户自定义数据指针。
 * @since 12
 */
void* OH_ArkUI_DialogDismissEvent_GetUserData(ArkUI_DialogDismissEvent* event);

/**
 * @brief 获取交互式关闭事件指针中的关闭原因。
 *
 * @param event 弹窗关闭事件对象指针。
 * @return 关闭原因，异常情况返回-1。
 *     <br>{@link DIALOG_DISMISS_BACK_PRESS} 点击三键back、侧滑（左滑/右滑）、键盘ESC关闭。
 *     <br>{@link DIALOG_DISMISS_TOUCH_OUTSIDE} 点击遮障层时。
 *     <br>{@link DIALOG_DISMISS_CLOSE_BUTTON} 点击关闭按钮。
 *     <br>{@link DIALOG_DISMISS_SLIDE_DOWN} 下拉关闭。
 * @since 12
 */
int32_t OH_ArkUI_DialogDismissEvent_GetDismissReason(ArkUI_DialogDismissEvent* event);

/**
 * @brief 弹出自定义弹窗。
 *
 * @param options 弹窗参数。
 * @param callback Callback to be invoked when the custom dialog box displays.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_OpenDialog(ArkUI_CustomDialogOptions* options, void (*callback)(int32_t dialogId));

/**
 * @brief Callback function when the dialog is displayed.
 *
 * @param errorCode the error code.
 * {@link ARKUI_ERROR_CODE_NO_ERROR} The operation is successful.
 * {@link ARKUI_ERROR_CODE_PARAM_INVALID} A parameter error occurs.
 * {@link ARKUI_ERROR_CODE_DIALOG_CANNOT_BE_OPENED_BY_MODAL_UEC_WINDOW} The dialog cannot be opened by the modal UEC window.
 * @param dialogId Dialog id. Returns -1 when the dialog cannot be displayed.
 * @param userData Indicates the pointer to the custom data.
 * @since 26.1.0
 */
typedef void (*ArkUI_OpenDialogCallback)(int32_t errorCode, int32_t dialogId, void* userData);

/**
 * @brief Displays a custom dialog box.
 *
 * @param options Dialog box parameters.
 * @param userData Indicates the pointer to the custom data.
 * @param callback Callback function when the dialog is displayed.
 * @since 26.1.0
 */
void OH_ArkUI_CustomDialog_OpenDialogWithCallback(ArkUI_CustomDialogOptions* options, void* userData,
    ArkUI_OpenDialogCallback callback);

/**
 * @brief 更新自定义弹窗。
 *
 * @param options 弹窗参数。
 * @param callback Callback to be invoked when the custom dialog box updates.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_UpdateDialog(ArkUI_CustomDialogOptions* options, void (*callback)(int32_t dialogId));

/**
 * @brief 关闭自定义弹窗。
 *
 * @param dialogId 需要关闭的弹窗ID。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_CloseDialog(int32_t dialogId);

/**
 * @brief 创建自定义弹窗配置。
 *
 * @param content 自定义弹窗的内容。
 * @return 自定义弹窗配置的指针。
 * @since 19
 */
ArkUI_CustomDialogOptions* OH_ArkUI_CustomDialog_CreateOptions(ArkUI_NodeHandle content);

/**
 * @brief 销毁自定义弹窗配置。
 *
 * @param options 自定义弹窗配置的指针。
 * @since 19
 */
void OH_ArkUI_CustomDialog_DisposeOptions(ArkUI_CustomDialogOptions* options);

/**
 * @brief 设置弹窗的显示层级。
 *
 * @note This method must be called before the <b>OH_ArkUI_CustomDialog_OpenDialog</b> method.
 * @param options 指向自定义弹窗options的指针。
 * @param levelMode 显示层级的枚举值， 类型为{@link ArkUI_LevelMode}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetLevelMode(ArkUI_CustomDialogOptions* options, ArkUI_LevelMode levelMode);

/**
 * @brief 设置弹窗显示层级页面下的节点id。
 *
 * @param options 指向自定义弹窗options的指针。
 * @param uniqueId 指定节点id，会查找该节点所在页面，并将弹窗显示在该页面下。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetLevelUniqueId(ArkUI_CustomDialogOptions* options, int32_t uniqueId);

/**
 * @brief 设置嵌入式弹窗蒙层的显示区域。
 *
 * @note This method must be called before the <b>OH_ArkUI_CustomDialog_OpenDialog</b> method.
 * @param options 指向自定义弹窗options的指针。
 * @param immersiveMode 显示区域类型的枚举值， 类型为{@link ArkUI_ImmersiveMode}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetImmersiveMode(ArkUI_CustomDialogOptions* options, ArkUI_ImmersiveMode immersiveMode);

/**
 * @brief 设置弹窗的背景颜色。
 *
 * @param options 弹窗参数。
 * @param backgroundColor 弹窗背景颜色，0xARGB格式。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetBackgroundColor(ArkUI_CustomDialogOptions* options, uint32_t backgroundColor);

/**
 * @brief 设置弹窗的圆角半径。
 *
 * @param options 弹窗参数。
 * @param topLeft 弹窗左上角的圆角半径，单位：vp。默认值：从API version 12开始，为32vp。API version 11及之前版本，为24vp。
 * @param topRight 弹窗右上角的圆角半径，单位：vp。默认值：从API version 12开始，为32vp。API version 11及之前版本，为24vp。
 * @param bottomLeft 弹窗左下角的圆角半径，单位：vp。默认值：从API version 12开始，为32vp。API version 11及之前版本，为24vp。
 * @param bottomRight 弹窗右下角的圆角半径，单位：vp。默认值：从API version 12开始，为32vp。API version 11及之前版本，为24vp。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetCornerRadius(
    ArkUI_CustomDialogOptions* options, float topLeft, float topRight, float bottomLeft, float bottomRight);

/**
 * @brief 设置弹窗的边框宽度。
 *
 * @param options 弹窗参数。
 * @param top 弹窗上边框的宽度。
 * @param right 弹窗右边框的宽度。
 * @param bottom 弹窗下边框的宽度。
 * @param left 弹窗左边框的宽度。
 * @param unit 指定宽度的单位，默认为vp。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetBorderWidth(
    ArkUI_CustomDialogOptions* options, float top, float right, float bottom, float left, ArkUI_LengthMetricUnit unit);

/**
 * @brief 设置弹窗的边框颜色。
 *
 * @param options 弹窗参数。
 * @param top 弹窗上边框的颜色，0xARGB格式。
 * @param right 弹窗右边框的颜色，0xARGB格式。
 * @param bottom 弹窗下边框的颜色，0xARGB格式。
 * @param left 弹窗左边框的颜色，0xARGB格式。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetBorderColor(
    ArkUI_CustomDialogOptions* options, uint32_t top, uint32_t right, uint32_t bottom, uint32_t left);

/**
 * @brief 设置弹窗的边框样式。
 *
 * @param options 弹窗参数。
 * @param top 弹窗上边框的样式，参数类型{@link ArkUI_BorderStyle}，默认值为ARKUI_BORDER_STYLE_SOLID。
 * @param right 弹窗右边框的样式，参数类型{@link ArkUI_BorderStyle}，默认值为ARKUI_BORDER_STYLE_SOLID。
 * @param bottom 弹窗下边框的样式，参数类型{@link ArkUI_BorderStyle}，默认值为ARKUI_BORDER_STYLE_SOLID。
 * @param left 弹窗左边框的样式，参数类型{@link ArkUI_BorderStyle}，默认值为ARKUI_BORDER_STYLE_SOLID。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetBorderStyle(
    ArkUI_CustomDialogOptions* options, int32_t top, int32_t right, int32_t bottom, int32_t left);

/**
 * @brief 设置弹窗的背板宽度。
 *
 * @param options 弹窗参数。
 * @param width 弹窗的背板宽度。
 * @param unit 指定宽度的单位，默认为vp。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetWidth(ArkUI_CustomDialogOptions* options, float width, ArkUI_LengthMetricUnit unit);

/**
 * @brief 设置弹窗的背板高度。
 *
 * @param options 弹窗参数。
 * @param height 弹窗的背板高度。
 * @param unit 指定高度的单位，默认为vp。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetHeight(ArkUI_CustomDialogOptions* options, float height, ArkUI_LengthMetricUnit unit);

/**
 * @brief 设置弹窗的背板阴影。
 *
 * @param options 弹窗参数。
 * @param shadow 弹窗的背板阴影样式，枚举值。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetShadow(ArkUI_CustomDialogOptions* options, ArkUI_ShadowStyle shadow);

/**
 * @brief 设置弹窗的背板阴影。
 *
 * @param options 弹窗参数。
 * @param customShadow 弹窗的自定义阴影参数，格式与{@link ArkUI_NodeAttributeType}中的NODE_CUSTOM_SHADOW属性一致。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetCustomShadow(
    ArkUI_CustomDialogOptions* options, const ArkUI_AttributeItem* customShadow);

/**
 * @brief 设置弹窗的背板模糊材质。
 *
 * @param options 弹窗参数。
 * @param blurStyle 弹窗的背板模糊材质，枚举值。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetBackgroundBlurStyle(ArkUI_CustomDialogOptions* options, ArkUI_BlurStyle blurStyle);

/**
 * @brief 设置弹窗的对齐模式。
 *
 * @param options 弹窗参数。
 * @param alignment 弹窗的对齐模式，参数类型{@link ArkUI_Alignment}。
 * @param offsetX 弹窗的水平偏移量，浮点型，单位：vp。
 * @param offsetY 弹窗的垂直偏移量，浮点型，单位：vp。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetAlignment(
    ArkUI_CustomDialogOptions* options, int32_t alignment, float offsetX, float offsetY);

/**
 * @brief 设置自定义弹窗是否开启模态样式的弹窗。
 *
 * @param options 弹窗参数。
 * @param isModal 设置是否开启模态窗口。模态窗口有蒙层，非模态窗口无蒙层。设置为true表示开启模态窗口。设置为false表示关闭模态窗口。
 *     默认值：false
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetModalMode(ArkUI_CustomDialogOptions* options, bool isModal);

/**
 * @brief 设置自定义弹窗是否允许点击遮罩层退出。
 *
 * @param options 弹窗参数。
 * @param autoCancel 设置是否允许点击遮罩层退出，true表示关闭弹窗，false表示不关闭弹窗。
 *     默认值：true
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetAutoCancel(ArkUI_CustomDialogOptions* options, bool autoCancel);

/**
 * @brief 设置弹窗是否在子窗口显示此弹窗。
 *
 * @param options 弹窗参数。
 * @param showInSubwindow 设置弹窗需要显示在主窗口之外时，是否在子窗口显示此弹窗。值为true：弹窗可以显示在主窗口外，独立子窗口。值为false：弹窗显示在应用内，非独立子窗口。
 *     默认值：false
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetSubwindowMode(ArkUI_CustomDialogOptions* options, bool showInSubwindow);

/**
 * @brief 设置弹窗在子窗口中的显示模式。
 *
 * @note This method takes effect only when the dialog box is displayed in a subwindow.
 * @param options 弹窗参数。
 * @param displayModeInSubWindow 弹窗在子窗口中的显示模式，类型为{@link OH_ArkUI_DialogDisplayModeInSubWindow}。
 *     默认值：OH_ARKUI_DIALOG_DISPLAY_MODE_SCREEN_BASED
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
int32_t OH_ArkUI_CustomDialog_SetDisplayModeInSubWindow(
    ArkUI_CustomDialogOptions* options, OH_ArkUI_DialogDisplayModeInSubWindow displayModeInSubWindow);

/**
 * @brief 设置自定义弹窗遮罩属性。
 *
 * @param options 弹窗参数。
 * @param maskColor 弹窗的遮罩颜色，0xargb格式。
 * @param maskRect 遮蔽层区域范围的指针，遮蔽层区域内的事件不透传，在遮蔽层区域外的事件透传。参数类型{@link ArkUI_Rect}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetMask(
    ArkUI_CustomDialogOptions* options, uint32_t maskColor, const ArkUI_Rect* maskRect);

/**
 * @brief 设置弹窗避让键盘的模式。
 *
 * @param options 弹窗参数。
 * @param keyboardAvoidMode 键盘避让模式，枚举值。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetKeyboardAvoidMode(
    ArkUI_CustomDialogOptions* options, ArkUI_KeyboardAvoidMode keyboardAvoidMode);

/**
 * @brief 设置弹窗是否响应悬停态。
 *
 * @param options 弹窗参数。
 * @param enabled 是否响应悬停态，默认false。值为true时响应悬停态，值为false时不响应悬停态。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetHoverModeEnabled(ArkUI_CustomDialogOptions* options, bool enabled);

/**
 * @brief 设置悬停态下弹窗默认展示区域。
 *
 * @param options 弹窗参数。
 * @param hoverModeAreaType 悬停态区域，枚举值。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetHoverModeArea(
    ArkUI_CustomDialogOptions* options, ArkUI_HoverModeAreaType hoverModeAreaType);

/**
 * @brief 注册系统关闭自定义弹窗的监听事件。
 *
 * @param options 弹窗参数。
 * @param userData 用户自定义数据指针。
 * @param callback Callback for the dismissal event of the custom dialog box.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_RegisterOnWillDismissCallback(
    ArkUI_CustomDialogOptions* options, void* userData, void (*callback)(ArkUI_DialogDismissEvent* event));

/**
 * @brief 注册自定义弹窗显示动效前的监听事件。
 *
 * @param options 弹窗参数。
 * @param userData 用户自定义数据指针。
 * @param callback Callback to be invoked when the dialog box is about to appear.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_RegisterOnWillAppearCallback(
    ArkUI_CustomDialogOptions* options, void* userData, void (*callback)(void* userData));

/**
 * @brief 注册自定义弹窗弹出时的监听事件。
 *
 * @param options 弹窗参数。
 * @param userData 用户自定义数据指针。
 * @param callback Callback to be invoked when the custom dialog box appears.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_RegisterOnDidAppearCallback(
    ArkUI_CustomDialogOptions* options, void* userData, void (*callback)(void* userData));

/**
 * @brief 注册自定义弹窗退出动效前的监听事件。
 *
 * @param options 弹窗参数。
 * @param userData 用户自定义数据指针。
 * @param callback Callback to be invoked when the dialog box is about to disappear.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_RegisterOnWillDisappearCallback(
    ArkUI_CustomDialogOptions* options, void* userData, void (*callback)(void* userData));

/**
 * @brief 注册自定义弹窗消失时的监听事件。
 *
 * @param options 弹窗参数。
 * @param userData 用户自定义数据指针。
 * @param callback Callback to be invoked when the custom dialog box disappears.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_RegisterOnDidDisappearCallback(
    ArkUI_CustomDialogOptions* options, void* userData, void (*callback)(void* userData));

/**
 * @brief 获取弹窗的状态。
 *
 * @param handle 指向自定义弹窗控制器的指针。
 * @param state 自定义弹窗的状态。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 20
 */
int32_t OH_ArkUI_CustomDialog_GetState(ArkUI_NativeDialogHandle handle, ArkUI_DialogState* state);

/**
 * @brief 设置弹窗的背景模糊效果。
 *
 * @param options 弹窗参数。
 * @param backgroundBlurStyleOptions 弹窗的背景模糊效果。参数{@link ArkUI_AttributeItem}格式：
 *     <br>.value[0].i32：表示深浅色模式，取{@link ArkUI_ColorMode}枚举值。
 *     <br>.value[1]?.i32：表示取色模式，取{@link ArkUI_AdaptiveColor}枚举值。
 *     <br>.value[2]?.f32：表示模糊效果程度，取[0.0,1.0]范围内的值，超出有效值区间时取边界值。
 *     <br>.value[3]?.u32：表示灰阶模糊参数，对黑色的提亮程度，有效值范围为[0,127]，超出有效值范围，取0。
 *     <br>.value[4]?.u32：表示灰阶模糊参数，对白色的压暗程度，有效值范围为[0,127]，超出有效值范围，取0。
 *     <br>.value[5]?.i32：表示模糊激活策略，取{@link ArkUI_BlurStyleActivePolicy}枚举值。
 *     <br>.value[6]?.u32：表示窗口失焦后，窗口内控件模糊效果会被移除，此时控件背板的颜色，0xargb类型。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetBackgroundBlurStyleOptions(
    ArkUI_CustomDialogOptions* options, const ArkUI_AttributeItem* backgroundBlurStyleOptions);

/**
 * @brief 设置弹窗的背景效果参数。
 *
 * @param options 弹窗参数。
 * @param backgroundEffect 弹窗的背景效果参数。参数{@link ArkUI_AttributeItem}格式：
 *     <br>.value[0].f32：表示模糊半径，单位为vp。
 *     <br>.value[1]?.f32：表示饱和度。
 *     <br>.value[2]?.f32：表示亮度。
 *     <br>.value[3]?.u32：表示颜色，0xargb类型。
 *     <br>.value[4]?.i32：表示取色模式，取{@link ArkUI_AdaptiveColor}枚举值。
 *     <br>.value[5]?.u32：表示灰阶模糊参数，对黑色的提亮程度，有效值范围为[0,127]，超出有效值范围，取0。
 *     <br>.value[6]?.u32：表示灰阶模糊参数，对白色的压暗程度，有效值范围为[0,127]，超出有效值范围，取0。
 *     <br>.value[7]?.i32：表示模糊激活策略，取{@link ArkUI_BlurStyleActivePolicy}枚举值。
 *     <br>.value[8]?.u32：表示窗口失焦后，窗口内控件模糊效果会被移除，此时控件背板的颜色，0xargb类型。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
int32_t OH_ArkUI_CustomDialog_SetBackgroundEffect(
    ArkUI_CustomDialogOptions* options, const ArkUI_AttributeItem* backgroundEffect);

/**
 * @brief 设置弹窗参数的沉浸式材质属性。
 *
 * @param options 指向弹窗参数对象的指针。
 * @param material 指向沉浸式材质对象的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
int32_t OH_ArkUI_NativeModule_CustomDialog_SetSystemMaterialInOptions(
    ArkUI_CustomDialogOptions* options, ArkUI_ImmersiveMaterialHandle material);

 /**
  * @brief 设置指定弹窗的沉浸式材质。沉浸式材质根据设备算力等级分为不同等级。材质等级由{@link ArkUI_MaterialLevel}定义，可通过
  * {@link OH_ArkUI_NativeModule_GetGlobalMaterialLevel}获取。在高算力和中算力设备上，会影响材质层的滤镜效果和阴影（
  * {@link OH_ArkUI_CustomDialog_SetShadow}或{@link OH_ArkUI_CustomDialog_SetCustomShadow}）、背景模糊
  * {@link OH_ArkUI_CustomDialog_SetBackgroundBlurStyle}、背景效果{@link OH_ArkUI_CustomDialog_SetBackgroundEffect}效果。
  * 在低算力设备上，会影响背景颜色{@link OH_ArkUI_CustomDialog_SetBackgroundColor}、背景模糊
  * {@link OH_ArkUI_CustomDialog_SetBackgroundBlurStyle}、背景效果{@link OH_ArkUI_CustomDialog_SetBackgroundEffect}、边框颜色
  * {@link OH_ArkUI_CustomDialog_SetBorderColor}、边框宽度{@link OH_ArkUI_CustomDialog_SetBorderWidth}和阴影（
  * {@link OH_ArkUI_CustomDialog_SetShadow}或{@link OH_ArkUI_CustomDialog_SetCustomShadow}）效果。依据设备算力档位自动生效交互形变和流光效果，
  * 高算力设备生效交互形变和流光效果，中算力设备生效交互形变效果，低算力设备不生效。
  *
  * @param handle 指向自定义弹窗控制器的指针。
  * @param material 指向沉浸式材质对象的指针。
  * @return 错误码。
  *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
  *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
  * @since 26.0.0
  */
int32_t OH_ArkUI_NativeModule_CustomDialog_SetSystemMaterial(
    ArkUI_NativeDialogHandle handle, ArkUI_ImmersiveMaterialHandle material);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_DIALOG_H
/** @} */

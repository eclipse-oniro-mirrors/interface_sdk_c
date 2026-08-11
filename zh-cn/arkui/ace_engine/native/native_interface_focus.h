/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @brief Provides focus capabilities of ArkUI on the native side, such as focus transfer operaions.
 *
 * @since 15
 */

/**
 * @file native_interface_focus.h
 *
 * @brief 定义焦点管理接口，主要用于主动转移焦点、清除焦点、管理焦点转移默认行为、控制焦点激活态，以及设置按键事件的处理模式。适用于页面切换、键盘导航等需要统一管理焦点状态和焦点转移行为的场景，
 * 有助于提升焦点控制的可预测性和交互体验。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 15
 */

#ifndef ARKUI_NATIVE_INTERFACE_FOCUS_H
#define ARKUI_NATIVE_INTERFACE_FOCUS_H

#include "napi/native_api.h"
#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 按键事件的处理模式。
 *
 * @since 15
 */
typedef enum {
    /**
     * 按键事件用于移动焦点。
     */
    ARKUI_KEY_PROCESSING_MODE_FOCUS_NAVIGATION = 0,
    /**
     * 按键事件向上传递给祖先组件。
     */
    ARKUI_KEY_PROCESSING_MODE_FOCUS_ANCESTOR_EVENT,
} ArkUI_KeyProcessingMode;

/**
 * @brief 为特定节点请求焦点，适用于需要主动将焦点移动到指定组件的场景，例如页面初始化后设置默认焦点或通过键盘、遥控器进行焦点导航。调用前需确保节点存在且可获焦，同时其祖先节点也可获焦，否则将返回对应错误码。
 *
 * @param node 指定请求焦点的目标节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 请求成功。
 *     <br>{@link ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE} 节点无法获得焦点。
 *     <br>{@link ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE_ANCESTOR} 祖先节点无法获得焦点。
 *     <br>{@link ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT} 节点不存在。
 * @since 15
 */
ArkUI_ErrorCode OH_ArkUI_FocusRequest(ArkUI_NodeHandle node);

/**
 * @brief 清除当前焦点，焦点回到根容器节点。适用于退出当前焦点交互或需要重置页面焦点状态的场景。
 *
 * @param uiContext 需要清除焦点的UI实例对象的指针。
 * @since 15
 */
void OH_ArkUI_FocusClear(ArkUI_ContextHandle uiContext);

/**
 * @brief 设置当前界面的焦点激活态，获焦节点显示焦点框，适用于需要在键盘、遥控器等非触摸交互中显示焦点位置的场景。缺省配置：默认情况下焦点激活态为关闭状态。注意：OH_ArkUI_FocusActivate仅控制焦点激活态（
 * 即焦点框的显示与隐藏），不影响焦点的逻辑归属；若需将焦点实际移到根容器节点，应使用OH_ArkUI_FocusClear。
 *
 * @param uiContext 需要设置焦点激活态的UI实例对象指针。
 * @param isActive 设置是否进入/退出焦点激活态。true表示进入焦点激活态，false表示退出焦点激活态。
 * @param isAutoInactive 仅在isActive为true时生效。当触摸事件或鼠标按下事件触发时，true表示将状态设置为退出焦点激活态，false表示保持当前焦点激活态，
 *     直到再次调用OH_ArkUI_FocusActivate主动设置。
 * @since 15
 */
void OH_ArkUI_FocusActivate(ArkUI_ContextHandle uiContext, bool isActive, bool isAutoInactive);

/**
 * @brief 设置页面切换时焦点是否自动转移。
 *
 * @param uiContext UI实例对象指针。
 * @param autoTransfer 页面切换时，是否转移焦点。true表示页面切换时自动转移焦点到新页面；false表示页面切换时焦点不转移。
 * @since 15
 */
void OH_ArkUI_FocusSetAutoTransfer(ArkUI_ContextHandle uiContext, bool autoTransfer);


/**
 * @brief 设置按键事件的处理模式，适用于需要在焦点导航和祖先组件按键事件处理之间选择优先策略的场景。缺省配置：默认按键事件处理优先级为ARKUI_KEY_PROCESSING_MODE_FOCUS_NAVIGATION，
 * 即按键事件用于移动焦点。
 *
 * @param uiContext 需要设置按键事件处理模式的UI实例对象指针。
 * @param mode 按键事件处理模式。取值原则：ARKUI_KEY_PROCESSING_MODE_FOCUS_NAVIGATION(0)用于焦点导航，
 *     ARKUI_KEY_PROCESSING_MODE_FOCUS_ANCESTOR_EVENT(1)用于按键事件向上传递给祖先组件。
 * @since 15
*/
void OH_ArkUI_FocusSetKeyProcessingMode(ArkUI_ContextHandle uiContext, ArkUI_KeyProcessingMode mode);
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_INTERFACE_FOCUS_H
/** @} */

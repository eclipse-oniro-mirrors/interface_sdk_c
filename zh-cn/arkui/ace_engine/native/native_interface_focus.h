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
 * @brief Declares APIs for focus management, mainly used for actively transferring focus, managing the default focus
 * transfer behavior, and controlling the focus activation state.
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
 * @brief 按键事件处理的优先级。
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
    ARKUI_KEY_PROCESSING_MODE_FOCUS_ANCESTOR_EVENT
} ArkUI_KeyProcessingMode;

/**
 * @brief 为特定节点请求焦点。
 *
 * @param node 节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 请求成功。
 *     <br>{@link ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE} 节点无法获得焦点。
 *     <br>{@link ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE_ANCESTOR} 祖先节点无法获得焦点。
 *     <br>{@link ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT} 节点不存在。
 * @since 15
 */
ArkUI_ErrorCode OH_ArkUI_FocusRequest(ArkUI_NodeHandle node);

/**
 * @brief 将当前焦点清除到根容器节点。
 *
 * @param uiContext UI实例对象指针。
 * @since 15
 */
void OH_ArkUI_FocusClear(ArkUI_ContextHandle uiContext);

/**
 * @brief 设置当前界面的焦点激活态，获焦节点显示焦点框。
 *
 * @param uiContext UI实例对象指针。
 * @param isActive 设置是否进入/退出焦点激活态。true表示进入焦点激活态，false表示退出焦点激活态。
 * @param isAutoInactive 当触摸事件或鼠标按下事件触发时，"true" 表示将状态设置为退出焦点激活态,"false" 表示在调用对应设置API前，保持当前状态。
 * @since 15
 */
void OH_ArkUI_FocusActivate(ArkUI_ContextHandle uiContext, bool isActive, bool isAutoInactive);

/**
 * @brief 设置页面切换时，焦点转移行为。
 *
 * @param uiContext UI实例对象指针。
 * @param autoTransfer 页面切换时，是否转移焦点。true表示页面切换时转移焦点，false表示页面切换时焦点不转移。
 * @since 15
 */
void OH_ArkUI_FocusSetAutoTransfer(ArkUI_ContextHandle uiContext, bool autoTransfer);

/**
 * @brief 设置按键事件处理的优先级。
 *
 * @param uiContext UI实例对象指针。
 * @param mode 按键事件处理的优先级。
 * @since 15
*/
void OH_ArkUI_FocusSetKeyProcessingMode(ArkUI_ContextHandle uiContext, ArkUI_KeyProcessingMode mode);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_INTERFACE_FOCUS_H

/** @} */
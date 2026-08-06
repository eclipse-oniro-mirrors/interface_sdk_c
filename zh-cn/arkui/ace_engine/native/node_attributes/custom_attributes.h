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
 * @brief ArkUI Custom Node event type on the native side.
 *
 * @since 12
 */

/**
 * @file custom_attributes.h
 *
 * @brief 为NativeNode API提供自定义节点事件定义。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_CUSTOM_ATTRIBUTES_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_CUSTOM_ATTRIBUTES_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义自定义组件事件类型。
 *
 * @since 12
 */
typedef enum {
/**
     * 自定义测量类型。
 * @since 12
 */
ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE = 1 << 0,
/**
     * 自定义布局类型。
 * @since 12
 */
ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT = 1 << 1,
/**
     * 自定义内容层绘制类型。
 * @since 12
 */
ARKUI_NODE_CUSTOM_EVENT_ON_DRAW = 1 << 2,
/**
     * 自定义前景绘制类型。
 * @since 12
 */
ARKUI_NODE_CUSTOM_EVENT_ON_FOREGROUND_DRAW = 1 << 3,
/**
     * 自定义浮层绘制类型。
 * @since 12
 */
ARKUI_NODE_CUSTOM_EVENT_ON_OVERLAY_DRAW = 1 << 4,
/**
     * 自定义内容层前景绘制类型。
 * @since 20
 */
ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_FRONT = 1 << 5,
/**
     * 自定义内容层背景绘制类型。
 * @since 20
 */
ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_BEHIND = 1 << 6
} ArkUI_NodeCustomEventType;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_CUSTOM_ATTRIBUTES_H
/** @} */
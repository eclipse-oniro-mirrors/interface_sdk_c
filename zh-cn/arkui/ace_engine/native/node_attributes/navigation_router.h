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
 * @brief Defines a set of navigation or router enum and interface.
 *
 * @since 12
 */

/**
 * @file navigation_router.h
 *
 * @brief 定义Navigation或Router组件的枚举和接口。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_NAVIGATION_ROUTER_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_NAVIGATION_ROUTER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义NavDestination组件的状态。
 *
 * @since 12
 */
typedef enum {
    /**
     * NavDestination组件显示。
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_SHOW = 0,
    /**
     * NavDestination组件隐藏。
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_HIDE = 1,
    /**
     * NavDestination从组件树上挂载。
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_APPEAR = 2,
    /**
     * NavDestination从组件树上卸载。
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_DISAPPEAR = 3,
    /**
     * NavDestination组件显示之前。
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_WILL_SHOW = 4,
    /**
     * NavDestination组件隐藏之前。
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_WILL_HIDE = 5,
    /**
     * NavDestination挂载到组件树之前。
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_WILL_APPEAR = 6,
    /**
     * NavDestination从组件树上卸载之前。
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_WILL_DISAPPEAR = 7,
    /**
     * NavDestination从组件返回。
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_BACK_PRESS = 100
} ArkUI_NavDestinationState;

/**
 * @brief 定义[Router](arkts-apis-uicontext-router.md)（路由页面）的状态。
 *
 * @since 12
 */
typedef enum {
    /**
     * Router Page即将创建。
     * @since 12
     */
    ARKUI_ROUTER_PAGE_STATE_ABOUT_TO_APPEAR = 0,
    /**
     * Router Page即将销毁。
     * @since 12
     */
    ARKUI_ROUTER_PAGE_STATE_ABOUT_TO_DISAPPEAR = 1,
    /**
     * Router Page显示。
     * @since 12
     */
    ARKUI_ROUTER_PAGE_STATE_ON_SHOW = 2,
    /**
     * Router Page隐藏。
     * @since 12
     */
    ARKUI_ROUTER_PAGE_STATE_ON_HIDE = 3,
    /**
     * Router Page返回时。
     * @since 12
     */
    ARKUI_ROUTER_PAGE_STATE_ON_BACK_PRESS = 4
} ArkUI_RouterPageState;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_NAVIGATION_ROUTER_H
/** @} */
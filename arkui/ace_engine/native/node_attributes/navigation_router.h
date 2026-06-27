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
 * @brief Defines a set of navigation or router enum and interface.
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
 * @brief Defines the state of the NavDestination component.
 *
 * @since 12
 */
typedef enum {
    /**
     * The NavDestination show.
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_SHOW = 0,
    /**
     * The NavDestination hide.
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_HIDE = 1,
    /**
     * The NavDestination is mounted to the component tree.
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_APPEAR = 2,
    /**
     * The NavDestination removed from the component tree.
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_DISAPPEAR = 3,
    /**
     * Before the NavDestination show.
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_WILL_SHOW = 4,
    /**
     * Before the NavDestination hide.
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_WILL_HIDE = 5,
    /**
     * Before the NavDestination mount to the component tree.
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_WILL_APPEAR = 6,
    /**
     * Before the NavDestination removed from the component tree.
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_WILL_DISAPPEAR = 7,
    /**
     * The NavDestination returns from the component.
     * @since 12
     */
    ARKUI_NAV_DESTINATION_STATE_ON_BACK_PRESS = 100,
} ArkUI_NavDestinationState;

/**
 * @brief Define the state of Router Page.
 *
 * @since 12
 */
typedef enum {
    /**
     * The Router Page is about to be created.
     * @since 12
     */
    ARKUI_ROUTER_PAGE_STATE_ABOUT_TO_APPEAR = 0,
    /**
     * The Router Page is about to be destroyed.
     * @since 12
     */
    ARKUI_ROUTER_PAGE_STATE_ABOUT_TO_DISAPPEAR = 1,
    /**
     * The Router Page show.
     * @since 12
     */
    ARKUI_ROUTER_PAGE_STATE_ON_SHOW = 2,
    /**
     * The Router Page hide.
     * @since 12
     */
    ARKUI_ROUTER_PAGE_STATE_ON_HIDE = 3,
    /**
     * The Router Page returns.
     * @since 12
     */
    ARKUI_ROUTER_PAGE_STATE_ON_BACK_PRESS = 4,
} ArkUI_RouterPageState;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_NAVIGATION_ROUTER_H
/** @} */
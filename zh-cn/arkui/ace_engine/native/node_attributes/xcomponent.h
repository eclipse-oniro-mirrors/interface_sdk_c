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
 * @brief XComponent组件的枚举类型定义。
 *
 * @since 12
 */

/**
 * @file xcomponent.h
 *
 * @brief XComponent组件的枚举类型定义。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */
#ifndef ARKUI_XCOMPONENT_H
#define ARKUI_XCOMPONENT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义XComponent类型枚举值。
 *
 * @since 12
 */
typedef enum {
    /**
     * 用于EGL/OpenGLES和媒体数据写入，开发者定制绘制内容单独显示在屏幕上。
     * @since 12
     */
    ARKUI_XCOMPONENT_TYPE_SURFACE = 0,
    /**
     * 用于EGL/OpenGLES和媒体数据写入，开发者定制绘制内容和XComponent组件内容合成后展示在屏幕上。
     * @since 12
     */
    ARKUI_XCOMPONENT_TYPE_TEXTURE = 2,
} ArkUI_XComponentType;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_XCOMPONENT_H
/** @} */

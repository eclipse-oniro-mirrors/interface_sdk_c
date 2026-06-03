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
 * @brief ArkUI Slider Node types on the native side.
 *
 * @since 12
 */

/**
 * @file slider.h
 *
 * @brief Provides Slider node type definitions for <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_SLIDER_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_SLIDER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义滑块形状。
 *
 * @since 12
 */
typedef enum {
    /**
     * 使用默认滑块（圆形）。
     * @since 12
     */
    ARKUI_SLIDER_BLOCK_STYLE_DEFAULT = 0,
    /**
     * 使用图片资源作为滑块。
     * @since 12
     */
    ARKUI_SLIDER_BLOCK_STYLE_IMAGE,
    /**
     * 使用自定义形状作为滑块。
     * @since 12
     */
    ARKUI_SLIDER_BLOCK_STYLE_SHAPE,
} ArkUI_SliderBlockStyle;

/**
 * @brief 定义滑动条滑动方向。
 *
 * @since 12
 */
typedef enum {
    /**
     * 方向为纵向。
     * @since 12
     */
    ARKUI_SLIDER_DIRECTION_VERTICAL = 0,
    /**
     * 方向为横向。
     * @since 12
     */
    ARKUI_SLIDER_DIRECTION_HORIZONTAL,
} ArkUI_SliderDirection;

/**
 * @brief 定义滑块与滑轨显示样式。
 *
 * @since 12
 */
typedef enum {
    /**
     * 滑块在滑轨上。
     * @since 12
     */
    ARKUI_SLIDER_STYLE_OUT_SET = 0,
    /**
     * 滑块在滑轨内。
     * @since 12
     */
    ARKUI_SLIDER_STYLE_IN_SET,
    /**
     * 无滑块。
     * @since 12
     */
    ARKUI_SLIDER_STYLE_NONE,
} ArkUI_SliderStyle;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_SLIDER_H
/** @} */

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
 * @brief Defines a set of ImageSpan enum and interface.
 *
 * @since 12
 */

/**
 * @file image_span.h
 *
 * @brief Defines a set of ImageSpan enum and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_SPAN_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_SPAN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义图片基于文本的对齐方式。
 *
 * @since 12
 */
typedef enum {
    /** 图片下边沿与文本BaseLine对齐。*/
    ARKUI_IMAGE_SPAN_ALIGNMENT_BASELINE = 0,
    /** 图片下边沿与文本下边沿对齐。*/
    ARKUI_IMAGE_SPAN_ALIGNMENT_BOTTOM,
    /** 图片中间与文本中间对齐。*/
    ARKUI_IMAGE_SPAN_ALIGNMENT_CENTER,
    /** 图片上边沿与文本上边沿对齐。 */
    ARKUI_IMAGE_SPAN_ALIGNMENT_TOP,
    /**
     * 图片对齐方式跟随Text组件对齐方式。
     *
     * @since 20
     */
    ARKUI_IMAGE_SPAN_ALIGNMENT_FOLLOW_PARAGRAPH
} ArkUI_ImageSpanAlignment;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_SPAN_H
/** @} */
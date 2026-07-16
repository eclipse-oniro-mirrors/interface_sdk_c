/**
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
 * @brief 提供ArkUI在Native侧的UI能力，包括UI组件创建与销毁、组件树节点操作、属性设置和事件监听等。
 *
 * @since 12
 */

/**
 * @file common_type.h
 *
 * @brief 定义ArkUI Native API的公共类型。
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @library libace_ndk.z.so
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_COMMON_TYPE_H
#define ARKUI_COMMON_TYPE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义ArkUI Native组件对象指针。
 *
 * @since 12
 */
typedef struct ArkUI_Node* ArkUI_NodeHandle;

/**
 * @brief 定义ArkUI节点内容对象指针。
 *
 * @since 12
 */
typedef struct ArkUI_NodeContent* ArkUI_NodeContentHandle;

/**
 * @brief 定义组件布局过程中的尺寸约束。
 *
 * @since 12
 */
typedef struct ArkUI_LayoutConstraint ArkUI_LayoutConstraint;

/**
 * @brief 定义组件绘制上下文。
 *
 * @since 12
 */
typedef struct ArkUI_DrawContext ArkUI_DrawContext;

/**
 * @brief 定义ArkUI Native上下文对象指针。
 *
 * @since 12
 */
typedef struct ArkUI_Context* ArkUI_ContextHandle;

/**
 * @brief 定义组件事件通用结构类型。
 *
 * @since 12
 */
typedef struct ArkUI_NodeEvent ArkUI_NodeEvent;

/**
 * @brief 定义事件回调类型。
 *
 * @since 12
 */
typedef struct {
    /**
     * 用户自定义数据。
     *
     * @since 12
     */
    void* userData;
    /**
     * 事件回调。
     *
     * @since 12
     */
    void (*callback)(void* userData);
} ArkUI_ContextCallback;

/**
 * @brief 定义ArkUI Native侧使用的数值类型。
 *
 * @since 12
 */
typedef union {
    /**
     * 浮点数。
     *
     * @since 12
     */
    float f32;
    /**
     * 有符号整数。
     *
     * @since 12
     */
    int32_t i32;
    /**
     * 无符号整数。
     *
     * @since 12
     */
    uint32_t u32;
} ArkUI_NumberValue;

/**
 * @brief 定义节点属性接口的通用入参结构。
 *
 * @since 12
 */
typedef struct {
    /**
     * 数值数组。
     *
     * @since 12
     */
    const ArkUI_NumberValue* value;
    /**
     * 数值数组长度。
     *
     * @since 12
     */
    int32_t size;
    /**
     * 字符串参数。
     *
     * @since 12
     */
    const char* string;
    /**
     * 对象参数。
     *
     * @since 12
     */
    void* object;
} ArkUI_AttributeItem;

/**
 * @brief 定义矩形区域。
 *
 * @since 12
 */
typedef struct {
    /**
     * 矩形区域的X坐标。
     *
     * @since 12
     */
    float x;
    /**
     * 矩形区域的Y坐标。
     *
     * @since 12
     */
    float y;
    /**
     * 矩形区域的宽度。
     *
     * @since 12
     */
    float width;
    /**
     * 矩形区域的高度。
     *
     * @since 12
     */
    float height;
} ArkUI_Rect;

/**
 * @brief 定义组件宽高。
 *
 * @since 12
 */
typedef struct {
    /**
     * 宽度，单位为px。
     *
     * @since 12
     */
    int32_t width;
    /**
     * 高度，单位为px。
     *
     * @since 12
     */
    int32_t height;
} ArkUI_IntSize;

/**
 * @brief 定义组件位置。
 *
 * @since 12
 */
typedef struct {
    /**
     * 水平坐标，单位为px。
     *
     * @since 12
     */
    int32_t x;
    /**
     * 垂直坐标，单位为px。
     *
     * @since 12
     */
    int32_t y;
} ArkUI_IntOffset;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_COMMON_TYPE_H
/** @} */

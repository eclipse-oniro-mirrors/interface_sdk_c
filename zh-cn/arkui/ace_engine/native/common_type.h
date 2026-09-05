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
 * @brief 定义 ArkUI Native 组件实例对象指针，用于在 ArkUI Native 接口中标识和传递组件实例，例如创建、挂载、移除或销毁组件节点。
 *
 * @since 12
 */
typedef struct ArkUI_Node* ArkUI_NodeHandle;

/**
 * @brief 定义ArkUI_NodeContent在Native侧的实例对象指针，用于在Native接口中引用和传递NodeContent实例。
 *
 * @since 12
 */
typedef struct ArkUI_NodeContent* ArkUI_NodeContentHandle;

/**
 * @brief 布局约束，用于组件布局时进行尺寸范围限制。支持设置最小尺寸和最大尺寸约束，约束值为非负浮点数，在组件布局时，系统会根据约束值限定组件的最终尺寸范围，确保布局结果符合约束条件。
 * 适用于自定义布局容器时控制子组件的尺寸范围，如瀑布流布局中限制图片卡片的高度、网格布局中限制单元格尺寸，以及需要限制组件尺寸上下限的场景，如图片展示组件限制最大宽度防止拉伸、响应式布局中限制最小尺寸保证可读性。
 * 防止组件尺寸超出预期范围，实现更精确的布局控制，提高布局的可预测性和稳定性，增强界面的可控性。
 *
 * @since 12
 */
typedef struct ArkUI_LayoutConstraint ArkUI_LayoutConstraint;

/**
 * @brief 定义组件绘制上下文的结构体类型，用于在自定义组件绘制过程中提供绘制上下文信息，可获取用于绘制的 Canvas 指针和可绘制区域大小。
 *
 * @since 12
 */
typedef struct ArkUI_DrawContext ArkUI_DrawContext;

/**
 * @brief ArkUI在Native侧的上下文实例对象指针，用于表示组件所在页面的UIContext。
 * 开发者可通过{@link OH_ArkUI_GetContextByNode}或{@link OH_ArkUI_GetContextFromNapiValue}获取该指针，
 * 并将其作为 UI 任务调度、动画、焦点控制等接口的上下文入参。
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
 * @brief 事件回调类型，用于定义回调函数及其用户自定义数据。使用该类型的接口触发回调时，会调用callback，并将userData作为参数传入。
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
     * 事件触发时执行的回调函数，调用时会传入userData指向的用户自定义数据。
     *
     * @since 12
     */
    void (*callback)(void* userData);
} ArkUI_ContextCallback;

/**
 * @brief ArkUI 在 Native 侧使用的数字类型，用于通过统一类型承载浮点、有符号整型和无符号整型数值。
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
 * @brief 定义遮罩屏蔽区域的范围结构体。
 *
 * @since 12
 */
typedef struct {
    /**
     * @brief 区域在x轴的位置，单位：vp。
     *
     * @since 12
     */
    float x;
    /**
     * @brief 区域在y轴的位置，单位：vp。
     *
     * @since 12
     */
    float y;
    /**
     * @brief 区域宽度，单位：vp。
     *
     * @since 12
     */
    float width;
    /**
     * @brief 区域高度，单位：vp。
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

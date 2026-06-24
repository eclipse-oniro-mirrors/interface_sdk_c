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
 * @brief ArkUI Scroll related enums on the native side.
 *
 * @since 12
 */

/**
 * @file node_scroll.h
 *
 * @brief Provides shared scroll-related enum definitions for <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUIKit
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_SCROLL_SCROLL_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_SCROLL_SCROLL_H

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 定义边缘滑动效果枚举值。Grid、Scroll、WaterFlow组件默认值为ARKUI_EDGE_EFFECT_NONE，List组件默认值为ARKUI_EDGE_EFFECT_SPRING。
 *
 * @since 12
 */
typedef enum {
    /** 弹性物理动效，滑动到边缘后可以根据初始速度或通过触摸事件继续滑动一段距离，松手后回弹。*/
    ARKUI_EDGE_EFFECT_SPRING = 0,

    /** 阴影效果，滑动到边缘后会有圆弧状的阴影。*/
    ARKUI_EDGE_EFFECT_FADE,

    /** 滑动到边缘后无效果。*/
    ARKUI_EDGE_EFFECT_NONE
} ArkUI_EdgeEffect;

/**
 * @brief 定义文本控制滚动条状态枚举值。
 *
 * @since 22
 */
typedef enum {
    /** 不显示。 */
    ARKUI_BAR_STATE_OFF = 0,

    /** 按需显示。 */
    ARKUI_BAR_STATE_AUTO = 1,

    /** 常驻显示。 */
    ARKUI_BAR_STATE_ON = 2
} ArkUI_BarState;

/**
 * @brief 定义边缘效果生效边缘的方向枚举值。
 *
 * @since 18
 */
typedef enum {
    /** 起始边生效。*/
    ARKUI_EFFECT_EDGE_START = 1,

    /** 末尾边生效。*/
    ARKUI_EFFECT_EDGE_END = 2
} ArkUI_EffectEdge;

/**
 * @brief 定义Scroll组件排列方向枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 仅支持竖直方向滚动。*/
    ARKUI_SCROLL_DIRECTION_VERTICAL = 0,

    /** 仅支持水平方向滚动。*/
    ARKUI_SCROLL_DIRECTION_HORIZONTAL,

    /** 禁止滚动。*/
    ARKUI_SCROLL_DIRECTION_NONE = 3,

    /**
     * 自由滚动。
     *
     * @since 20
     */
    ARKUI_SCROLL_DIRECTION_FREE = 4
} ArkUI_ScrollDirection;

/**
 * @brief 定义列表项滚动结束对齐效果枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 默认无列表滚动对齐效果。*/
    ARKUI_SCROLL_SNAP_ALIGN_NONE = 0,

    /** 视图中的第一项将在列表的开头对齐。*/
    ARKUI_SCROLL_SNAP_ALIGN_START,

    /** 视图中的中间项将在列表中心对齐。*/
    ARKUI_SCROLL_SNAP_ALIGN_CENTER,

    /** 视图中的最后一项将在列表末尾对齐。*/
    ARKUI_SCROLL_SNAP_ALIGN_END
} ArkUI_ScrollSnapAlign;

/**
 * @brief 定义列表限位滚动动画速度。
 *
 * @since 22
 */
typedef enum {
    /** 限位滚动动画速度快。*/
    ARKUI_SCROLL_SNAP_ANIMATION_NORMAL = 0,

    /** 限位滚动动画速度慢。*/
    ARKUI_SCROLL_SNAP_ANIMATION_SLOW = 1
} ArkUI_ScrollSnapAnimationSpeed;

/**
 * @brief  定义滚动条状态枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 不显示。 */
    ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF = 0,

    /** 按需显示(触摸时显示，2s后消失)。*/
    ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO,

    /** 常驻显示。 */
    ARKUI_SCROLL_BAR_DISPLAY_MODE_ON
} ArkUI_ScrollBarDisplayMode;

/**
 * @brief 定义滚动容器的内容层裁剪区域枚举值。
 *
 * @since 18
 */
typedef enum {
    /** 按内容区裁剪。 */
    ARKUI_CONTENT_CLIP_MODE_CONTENT_ONLY = 0,

    /** 按组件区域裁剪。 */
    ARKUI_CONTENT_CLIP_MODE_BOUNDARY,

    /**
     * Clip to the {@link safe area} configured for the component.
     */
    ARKUI_CONTENT_CLIP_MODE_SAFE_AREA
} ArkUI_ContentClipMode;

/**
 * @brief 定义嵌套滚动选项。
 *
 * @since 12
 */
typedef enum {
    /** 只自身滚动，不与父组件联动。 */
    ARKUI_SCROLL_NESTED_MODE_SELF_ONLY = 0,

    /** 自身先滚动，自身滚动到边缘以后父组件滚动。父组件滚动到边缘以后，如果父组件有边缘效果，则父组件触发边缘效果，否则子组件触发边缘效果。*/
    ARKUI_SCROLL_NESTED_MODE_SELF_FIRST,

    /** 父组件先滚动，父组件滚动到边缘以后自身滚动。自身滚动到边缘后，如果有边缘效果，会触发自身的边缘效果，否则触发父组件的边缘效果。*/
    ARKUI_SCROLL_NESTED_MODE_PARENT_FIRST,
    /** 自身和父组件同时滚动，自身和父组件都到达边缘以后，如果自身有边缘效果，则自身触发边缘效果，否则父组件触发边缘效果。 */
    ARKUI_SCROLL_NESTED_MODE_PARALLEL
} ArkUI_ScrollNestedMode;

/**
 * @brief 定义滚动到的边缘位置。
 *
 * @since 12
 */
typedef enum {
    /** 竖直方向上边缘。*/
    ARKUI_SCROLL_EDGE_TOP = 0,

    /** 竖直方向下边缘。*/
    ARKUI_SCROLL_EDGE_BOTTOM,

    /** 水平方向起始位置。*/
    ARKUI_SCROLL_EDGE_START,

    /** 水平方向末尾位置。*/
    ARKUI_SCROLL_EDGE_END
} ArkUI_ScrollEdge;

/**
 * @brief 滚动到具体item时的对齐方式。
 *
 * @since 12
 */
typedef enum {
    /** 首部对齐。指定item首部与容器首部对齐。*/
    ARKUI_SCROLL_ALIGNMENT_START = 0,

    /** 居中对齐。指定item主轴方向居中对齐于容器。*/
    ARKUI_SCROLL_ALIGNMENT_CENTER,

    /** 尾部对齐。指定item尾部与容器尾部对齐。*/
    ARKUI_SCROLL_ALIGNMENT_END,

    /** 自动对齐。若指定item完全处于显示区，不做调整。否则依照滑动距离最短的原则，将指定item首部对齐或尾部对齐于容器,使指定item完全处于显示区。*/
    ARKUI_SCROLL_ALIGNMENT_AUTO
} ArkUI_ScrollAlignment;

/**
 * @brief 定义当前滚动状态。
 *
 * @since 12
 */
typedef enum {
    /** 空闲状态。使用控制器提供的方法控制滚动时触发，拖动滚动条滚动时触发。*/
    ARKUI_SCROLL_STATE_IDLE = 0,

    /** 滚动状态。使用手指拖动容器滚动时触发。*/
    ARKUI_SCROLL_STATE_SCROLL,

    /** 惯性滚动状态。快速划动松手后进行惯性滚动和划动到边缘回弹时触发。*/
    ARKUI_SCROLL_STATE_FLING
} ArkUI_ScrollState;

/**
 * @brief 定义滚动来源枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 手指拖动。*/
    ARKUI_SCROLL_SOURCE_DRAG = 0,

    /** 手指拖动后的惯性滚动。*/
    ARKUI_SCROLL_SOURCE_FLING,

    /**
     * {@link EdgeEffect.Spring} for boundary crossing.
     */
    ARKUI_SCROLL_SOURCE_EDGE_EFFECT,

    /** 除了拖动以外的其他用户输入，如鼠标滚轮、键盘事件等。*/
    ARKUI_SCROLL_SOURCE_OTHER_USER_INPUT,

    /** 拖动滚动条。*/
    ARKUI_SCROLL_SOURCE_SCROLL_BAR,

    /** 拖动滚动条后的惯性滚动。*/
    ARKUI_SCROLL_SOURCE_SCROLL_BAR_FLING,

    /** 滚动控制器引起的无动画的滚动。*/
    ARKUI_SCROLL_SOURCE_SCROLLER,

    /** 滚动控制器引起的带动画的滚动。*/
    ARKUI_SCROLL_SOURCE_ANIMATION
} ArkUI_ScrollSource;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_SCROLL_SCROLL_H

/** @} */
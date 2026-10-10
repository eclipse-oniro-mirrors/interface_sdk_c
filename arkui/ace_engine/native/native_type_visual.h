/*
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
 * @brief Provides visual effect capabilities of ArkUI on the native side.
 *
 * @since 12
 */

/**
 * @file native_type_visual.h
 *
 * @brief Defines the visual types for the native module.
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_TYPE_VISUAL_H
#define ARKUI_NATIVE_TYPE_VISUAL_H

#include <stdint.h>
#include <stdbool.h>

#include "error_code.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Defines a fourth-order matrix object used to describe matrix transformation operations such as translation,
 * rotation, and scaling of UI components. For details, see {@link ArkUI_NativeModule}.
 * @since 24
 */
typedef struct ArkUI_Matrix4 ArkUI_Matrix4;

/**
 * @brief Enumerates shadow types.
 *
 * @since 12
 */
typedef enum {
    /**
     * Color shadow.
     */
    ARKUI_SHADOW_TYPE_COLOR = 0,
    /**
     * Blur shadow.
     */
    ARKUI_SHADOW_TYPE_BLUR
} ArkUI_ShadowType;

/**
 * @brief Enumerates shadow styles.
 *
 * @since 12
 */
typedef enum {
    /**
     * Mini shadow.<br>
     */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_XS = 0,
    /**
     * Small shadow.<br>
     */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_SM,
    /**
     * Medium shadow.<br>
     */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_MD,
    /**
     * Large shadow.<br>
     */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_LG,
    /**
     * Floating small shadow.<br>
     */
    ARKUI_SHADOW_STYLE_OUTER_FLOATING_SM,
    /**
     * Floating medium shadow.<br>
     */
    ARKUI_SHADOW_STYLE_OUTER_FLOATING_MD,
} ArkUI_ShadowStyle;

/**
 * @brief Enumerates animation curves.
 * @since 12
 */
typedef enum {
    /**
     * The animation speed keeps unchanged.
     */
    ARKUI_CURVE_LINEAR = 0,
    /**
     * The animation starts slowly, accelerates, and then slows down towards the end.
     */
    ARKUI_CURVE_EASE,
    /**
     * The animation starts at a low speed and then picks up speed until the end.
     */
    ARKUI_CURVE_EASE_IN,
    /**
     * The animation ends at a low speed.
     */
    ARKUI_CURVE_EASE_OUT,
    /**
     * The animation starts and ends at a low speed, providing a smooth and natural transition.
     */
    ARKUI_CURVE_EASE_IN_OUT,
    /**
     * The animation uses the standard curve
     */
    ARKUI_CURVE_FAST_OUT_SLOW_IN,
    /**
     * The animation uses the deceleration curve.
     */
    ARKUI_CURVE_LINEAR_OUT_SLOW_IN,
    /**
     * The animation uses the acceleration curve.
     */
    ARKUI_CURVE_FAST_OUT_LINEAR_IN,
    /**
     * The animation uses the extreme deceleration curve.
     */
    ARKUI_CURVE_EXTREME_DECELERATION,
    /**
     * The animation uses the sharp curve.
     */
    ARKUI_CURVE_SHARP,
    /**
     * The animation uses the rhythm curve.
     */
    ARKUI_CURVE_RHYTHM,
    /**
     * The animation uses the smooth curve.
     */
    ARKUI_CURVE_SMOOTH,
    /**
     * The animation uses the friction curve
     */
    ARKUI_CURVE_FRICTION,
} ArkUI_AnimationCurve;

/**
 * @brief Enumerates animation playback modes.
 * @since 12
 */
typedef enum {
    /**
     * The animation is played forwards.
     */
    ARKUI_ANIMATION_PLAY_MODE_NORMAL = 0,
    /**
     * The animation is played backwards.
     */
    ARKUI_ANIMATION_PLAY_MODE_REVERSE,
    /**
     * The animation plays in alternating loop mode. When the animation is played for an odd number of times, the
     * playback is in forward direction. When the animation is played for an even number of times, the playback is in
     * reverse direction.
     */
    ARKUI_ANIMATION_PLAY_MODE_ALTERNATE,
    /**
     * The animation plays in reverse alternating loop mode. When the animation is played for an odd number of times,
     * the playback is in reverse direction. When the animation is played for an even number of times, the playback is
     * in forward direction.
     */
    ARKUI_ANIMATION_PLAY_MODE_ALTERNATE_REVERSE,
} ArkUI_AnimationPlayMode;

/**
 * @brief Enumerates blur styles.
 * @since 12
 */
typedef enum {
    /**
     * Thin material.<br>
     */
    ARKUI_BLUR_STYLE_THIN = 0,
    /**
     * Regular material.<br>
     */
    ARKUI_BLUR_STYLE_REGULAR,
    /**
     * Thick material.<br>
     */
    ARKUI_BLUR_STYLE_THICK,
    /**
     * Material that creates the minimum depth of field effect.<br>
     */
    ARKUI_BLUR_STYLE_BACKGROUND_THIN,
    /**
     * Material that creates a medium shallow depth of field effect.<br>
     */
    ARKUI_BLUR_STYLE_BACKGROUND_REGULAR,
    /**
     * Material that creates a high shallow depth of field effect.<br>
     */
    ARKUI_BLUR_STYLE_BACKGROUND_THICK,
    /**
     * Material that creates the maximum depth of field effect.<br>
     */
    ARKUI_BLUR_STYLE_BACKGROUND_ULTRA_THICK,
    /**
     * No blur.<br>
     */
    ARKUI_BLUR_STYLE_NONE,
    /**
     * Component ultra-thin material.<br>
     */
    ARKUI_BLUR_STYLE_COMPONENT_ULTRA_THIN,
    /**
     * Component thin material.<br>
     */
    ARKUI_BLUR_STYLE_COMPONENT_THIN,
    /**
     * Component regular material.<br>
     */
    ARKUI_BLUR_STYLE_COMPONENT_REGULAR,
    /**
     * Component thick material.<br>
     */
    ARKUI_BLUR_STYLE_COMPONENT_THICK,
    /**
     * Component ultra-thick material.<br>
     */
    ARKUI_BLUR_STYLE_COMPONENT_ULTRA_THICK,
} ArkUI_BlurStyle;

/**
 * @brief Enumerates the activation policies for the background blur effect.
 *
 * @since 19
 */
typedef enum {
    /**
     * The blur effect changes according to the window's focus state;
     * it is inactive when the window is not in focus and active when the window is in focus.
     */
    ARKUI_BLUR_STYLE_ACTIVE_POLICY_FOLLOWS_WINDOW_ACTIVE_STATE = 0,
    /**
     * The blur effect is always active.
     */
    ARKUI_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_ACTIVE,
    /**
     * The blur effect is always inactive.
     */
    ARKUI_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_INACTIVE,
} ArkUI_BlurStyleActivePolicy;

/**
 * @brief Enumerates blend modes.
 * @since 12
 */
typedef enum {
    /**
     * The top image is superimposed on the bottom image without any blending.
     */
    ARKUI_BLEND_MODE_NONE = 0,
    /**
     * The target pixels covered by the source pixels are erased by being turned to completely transparent.
     */
    ARKUI_BLEND_MODE_CLEAR,
    /**
     * r = s: Only the source pixels are displayed.
     */
    ARKUI_BLEND_MODE_SRC,
    /**
     * r = d: Only the target pixels are displayed.
     */
    ARKUI_BLEND_MODE_DST,
    /**
     * r = s + (1 - sa) * d: The source pixels are blended based on opacity and cover the target pixels.
     */
    ARKUI_BLEND_MODE_SRC_OVER,
    /**
     * r = d + (1 - da) * s: The target pixels are blended based on opacity and cover on the source pixels.
     */
    ARKUI_BLEND_MODE_DST_OVER,
    /**
     * r = s * da: Only the part of the source pixels that overlap with the target pixels is displayed.
     */
    ARKUI_BLEND_MODE_SRC_IN,
    /**
     * r = d * sa: Only the part of the target pixels that overlap with the source pixels is displayed.
     */
    ARKUI_BLEND_MODE_DST_IN,
    /**
     * r = s * (1 - da): Only the part of the source pixels that do not overlap with the target pixels is displayed.
     */
    ARKUI_BLEND_MODE_SRC_OUT,
    /**
     * r = d * (1 - sa): Only the part of the target pixels that do not overlap with the source pixels is displayed.
     */
    ARKUI_BLEND_MODE_DST_OUT,
    /**
     * r = s * da + d * (1 - sa): The part of the source pixels that overlap with the target pixels is displayed and
     * the part of the target pixels that do not overlap with the source pixels are displayed.
     */
    ARKUI_BLEND_MODE_SRC_ATOP,
    /**
     * r = d * sa + s * (1 - da): The part of the target pixels that overlap with the source pixels and the part of
     * the source pixels that do not overlap with the target pixels are displayed.
     */
    ARKUI_BLEND_MODE_DST_ATOP,
    /**
     * r = s * (1 - da) + d * (1 - sa): Only the non-overlapping part between the source pixels and the target pixels
     * is displayed.
     */
    ARKUI_BLEND_MODE_XOR,
    /**
     * r = min(s + d, 1): New pixels resulting from adding the source pixels to the target pixels are displayed.
     */
    ARKUI_BLEND_MODE_PLUS,
    /**
     * r = s * d: New pixels resulting from multiplying the source pixels with the target pixels are displayed.
     */
    ARKUI_BLEND_MODE_MODULATE,
    /**
     * r = s + d - s * d: Pixels are blended by adding the source pixels to the target pixels and subtracting the
     * product of their multiplication.
     */
    ARKUI_BLEND_MODE_SCREEN,
    /**
     * The MULTIPLY or SCREEN mode is used based on the target pixels.
     */
    ARKUI_BLEND_MODE_OVERLAY,
    /**
     * rc = s + d - max(s * da, d * sa), ra = kSrcOver: When two colors overlap, whichever is darker is used.
     */
    ARKUI_BLEND_MODE_DARKEN,
    /**
     * rc = s + d - min(s * da, d * sa), ra = kSrcOver: The final pixels are composed of the lightest values of pixels.
     */
    ARKUI_BLEND_MODE_LIGHTEN,
    /**
     * The colors of the target pixels are lightened to reflect the source pixels.
     */
    ARKUI_BLEND_MODE_COLOR_DODGE,
    /**
     * The colors of the target pixels are darkened to reflect the source pixels.
     */
    ARKUI_BLEND_MODE_COLOR_BURN,
    /**
     * The MULTIPLY or SCREEN mode is used, depending on the source pixels.
     */
    ARKUI_BLEND_MODE_HARD_LIGHT,
    /**
     * The LIGHTEN or DARKEN mode is used, depending on the source pixels.
     */
    ARKUI_BLEND_MODE_SOFT_LIGHT,
    /**
     * rc = s + d - 2 * (min(s * da, d * sa)), ra = kSrcOver: The final pixel is the result of subtracting the darker of the two pixels (source and target) from
     * the lighter one.
     */
    ARKUI_BLEND_MODE_DIFFERENCE,
    /**
     * rc = s + d - two(s * d), ra = kSrcOver: The final pixel is similar to <b>DIFFERENCE</b>, but with less contrast.
     */
    ARKUI_BLEND_MODE_EXCLUSION,
    /**
     * r = s * (1 - da) + d * (1 - sa) + s * d: The final pixel is the result of multiplying the source pixel
     * by the target pixel.
     */
    ARKUI_BLEND_MODE_MULTIPLY,
    /**
     * The resultant image is created with the luminance and saturation of the source image and the hue of the target
     * image.
     */
    ARKUI_BLEND_MODE_HUE,
    /**
     * The resultant image is created with the luminance and hue of the target image and the saturation of the source
     * image.
     */
    ARKUI_BLEND_MODE_SATURATION,
    /**
     * The resultant image is created with the saturation and hue of the source image and the luminance of the target
     * image.
     */
    ARKUI_BLEND_MODE_COLOR,
    /**
     * The resultant image is created with the saturation and hue of the target image and the luminance of the source
     * image.
     */
    ARKUI_BLEND_MODE_LUMINOSITY,
} ArkUI_BlendMode;

/**
 * @brief Enumerates foreground and shadow colors.
 *
 * @since 12
 */
typedef enum {
    /**
     * The foreground colors are the inverse of the component background colors.
     */
    ARKUI_COLOR_STRATEGY_INVERT = 0,
    /**
     * The shadow colors of the component are the average color obtained from the component background shadow area.
     */
    ARKUI_COLOR_STRATEGY_AVERAGE,
    /**
     * The shadow colors of the component are the primary color obtained from the component background shadow area.
     */
    ARKUI_COLOR_STRATEGY_PRIMARY,
} ArkUI_ColorStrategy;

/**
 * @brief Enumerates mask types. A mask is a means to limit the display area of a component. It uses a specific shape
 * to crop the component content so that only the content in the mask area is visible.
 * @since 12
 */
typedef enum {
    /**
     * Rectangle.
     */
    ARKUI_MASK_TYPE_RECTANGLE = 0,
    /**
     * Circle.
     */
    ARKUI_MASK_TYPE_CIRCLE,
    /**
     * Ellipse.
     */
    ARKUI_MASK_TYPE_ELLIPSE,
    /**
     * Path.
     */
    ARKUI_MASK_TYPE_PATH,
    /**
     * Progress indicator.
     */
    ARKUI_MASK_TYPE_PROGRESS,
} ArkUI_MaskType;

/**
 * @brief Enumerates clipping region types.
 * @since 12
 */
typedef enum {
    /**
     * Rectangle.
     */
    ARKUI_CLIP_TYPE_RECTANGLE = 0,
    /**
     * Circle.
     */
    ARKUI_CLIP_TYPE_CIRCLE,
    /**
     * Ellipse.
     */
    ARKUI_CLIP_TYPE_ELLIPSE,
    /**
     * Path.
     */
    ARKUI_CLIP_TYPE_PATH,
} ArkUI_ClipType;

/**
 * @brief Enumerates shape types.
 * @since 12
 */
typedef enum {
    /**
     * Rectangle.
     */
    ARKUI_SHAPE_TYPE_RECTANGLE = 0,
    /**
     * Circle.
     */
    ARKUI_SHAPE_TYPE_CIRCLE,
    /**
     * Ellipse.
     */
    ARKUI_SHAPE_TYPE_ELLIPSE,
    /**
     * Path.
     */
    ARKUI_SHAPE_TYPE_PATH,
} ArkUI_ShapeType;

/**
 * @brief Enumerates linear gradient directions.
 * @since 12
 */
typedef enum {
    /**
     * From right to left.
     */
    ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT = 0,
    /**
     * From bottom to top.
     */
    ARKUI_LINEAR_GRADIENT_DIRECTION_TOP,
    /**
     * From left to right.
     */
    ARKUI_LINEAR_GRADIENT_DIRECTION_RIGHT,
    /**
     * From top to bottom.
     */
    ARKUI_LINEAR_GRADIENT_DIRECTION_BOTTOM,
    /**
     * From lower right to upper left.
     */
    ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT_TOP,
    /**
     * From upper right to lower left.
     */
    ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT_BOTTOM,
    /**
     * From lower left to upper right.
     */
    ARKUI_LINEAR_GRADIENT_DIRECTION_RIGHT_TOP,
    /**
     * From upper left to lower right.
     */
    ARKUI_LINEAR_GRADIENT_DIRECTION_RIGHT_BOTTOM,
    /**
     * No gradient.
     */
    ARKUI_LINEAR_GRADIENT_DIRECTION_NONE,
    /**
     * Custom direction.
     */
    ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM,
} ArkUI_LinearGradientDirection;

/**
 * @brief Enumerates the slide-in and slide-out positions of the component from the screen edge during transition.
 *
 * @since 12
 */
typedef enum {
    /**
     * Top edge of the window.
     */
    ARKUI_TRANSITION_EDGE_TOP = 0,
    /**
     * Bottom edge of the window.
     */
    ARKUI_TRANSITION_EDGE_BOTTOM,
    /**
     * Left edge of the window.
     */
    ARKUI_TRANSITION_EDGE_START,
    /**
     * Right edge of the window.
     */
    ARKUI_TRANSITION_EDGE_END,
} ArkUI_TransitionEdge;

/**
 * @brief Defines how the specified blend mode is applied.
 *
 * @since 12
 */
typedef enum {
    /**
     * The content of the view is blended in sequence on the target image.
     */
    BLEND_APPLY_TYPE_FAST = 0,
    /**
     * The content of the component and its child components are drawn on the offscreen canvas, and then blended with
     * the existing content on the canvas.
     */
    BLEND_APPLY_TYPE_OFFSCREEN,
} ArkUI_BlendApplyType;

/**
 * @brief Enumerates the callback types for {@link OH_ArkUI_AnimatorOption_RegisterOnFinishCallback} in an animation.
 *
 * @since 12
 */
typedef enum {
    /**
     * The callback is invoked when the entire animation is removed once it has finished.
     */
    ARKUI_FINISH_CALLBACK_REMOVED = 0,
    /**
     * The callback is invoked when the animation logically enters the falling state, though it may still be in its
     * long tail state.
     */
    ARKUI_FINISH_CALLBACK_LOGICALLY,
} ArkUI_FinishCallbackType;

/**
 * @brief Enumerates the sizing and positioning behaviors of animated content in its final state.
 *
 * @since 12
 */
typedef enum {
    /**
     * Maintains the content size of the animation's final state,
     * and the content is always centered with the component.
     */
    ARKUI_RENDER_FIT_CENTER = 0,
    /**
     * Maintains the content size of the animation's final state,
     * and the content is always aligned with the top center of the component.
     */
    ARKUI_RENDER_FIT_TOP,
    /**
     * Maintains the content size of the animation's final state,
     * and the content is always aligned with the bottom center of the component.
     */
    ARKUI_RENDER_FIT_BOTTOM,
    /**
     * Maintains the content size of the animation's final state,
     * and the content is always aligned to the left of the component.
     */
    ARKUI_RENDER_FIT_LEFT,
    /**
     * Maintains the content size of the animation's final state,
     * and the content is always right-aligned with the component.
     */
    ARKUI_RENDER_FIT_RIGHT,
    /**
     * Maintains the content size of the animation's final state,
     * and the content is always aligned with the top left corner of the component.
     */
    ARKUI_RENDER_FIT_TOP_LEFT,
    /**
     * Keep the content size of the animation final state,
     * and the content is always aligned with the upper right corner of the component.
     */
    ARKUI_RENDER_FIT_TOP_RIGHT,
    /**
     * Keep the content size of the animation final state,
     * and the content always aligns with the lower-left corner of the component.
     */
    ARKUI_RENDER_FIT_BOTTOM_LEFT,
    /**
     * Keep the content size of the animation final state,
     * and the content always aligns with the lower-right corner of the component.
     */
    ARKUI_RENDER_FIT_BOTTOM_RIGHT,
    /**
     * The aspect ratio of the animation's final state content is not considered,
     * and the content is always scaled to the size of the component.
     */
    ARKUI_RENDER_FIT_RESIZE_FILL,
    /**
     * Reduce or enlarge the aspect ratio of the animation final state content,
     * so that the content is fully displayed in the component,
     * and keep the center aligned with the component.
     */
    ARKUI_RENDER_FIT_RESIZE_CONTAIN,
    /**
     * Keep the aspect ratio of the animation final state content to reduce or enlarge,
     * so that the content is fully displayed in the component.
     * When there is left over in the broad direction of the component,
     * the content is aligned to the left of the component,
     * and when there is left over in the high direction of the component,
     * the content is aligned to the top of the component.
     */
    ARKUI_RENDER_FIT_RESIZE_CONTAIN_TOP_LEFT,
    /**
     * Keep the aspect ratio of the animation final state content to reduce or enlarge,
     * so that the content is fully displayed in the component.
     * When there is left in the wide direction of the component,
     * the content is aligned with the component on the right.
     * When there is left in the high direction of the component,
     * the content is aligned with the component on the bottom.
     */
    ARKUI_RENDER_FIT_RESIZE_CONTAIN_BOTTOM_RIGHT,
    /**
     * Keep the aspect ratio of the animation final state content reduced or enlarged,
     * so that both sides of the content are greater than or equal to both sides of the component,
     * and keep the center aligned with the component to display the middle part of the content.
     */
    ARKUI_RENDER_FIT_RESIZE_COVER,
    /**
     * Keep the aspect ratio of the final content of the animation reduced or enlarged
     * so that both sides of the content are exactly greater than or equal to both sides of the component.
     * When the content width is left, the content is aligned to the left of the component,
     * and the left portion of the content is displayed. When the content is left in the high direction,
     * the content and the component remain top aligned, showing the top side of the content.
     */
    ARKUI_RENDER_FIT_RESIZE_COVER_TOP_LEFT,
    /**
     * Keep the aspect ratio of the final content of the animation reduced or enlarged so
     * that both sides of the content are exactly greater than or equal to both sides of the component.
     * When the content width is left, the content and the component remain right aligned,
     * and the right part of the content is displayed. When the content is left in the high direction,
     * the content and the component remain aligned at the bottom,
     * and the bottom part of the content is displayed.
     */
    ARKUI_RENDER_FIT_RESIZE_COVER_BOTTOM_RIGHT
} ArkUI_RenderFit;

/**
 * @brief Enumerates the states before and after execution of the frame-by-frame animation.
 * @since 12
*/
typedef enum {
    /**
     * Before execution, the animation does not apply any styles to the target component.
     * After execution, the animation restores the target component to its default state.
     */
    ARKUI_ANIMATION_FILL_MODE_NONE,
    /**
     * The target component retains the state set by the last keyframe encountered
     * during execution of the animation.
     */
    ARKUI_ANIMATION_FILL_MODE_FORWARDS,
    /**
     * The animation applies the values defined in the first relevant keyframe once it is applied to
     * the target component, and retains the values during the period set by delay.
     */
    ARKUI_ANIMATION_FILL_MODE_BACKWARDS,
    /**
     * The animation follows the rules for both Forwards and Backwards,
     * extending the animation attributes in both directions.
     */
    ARKUI_ANIMATION_FILL_MODE_BOTH,
} ArkUI_AnimationFillMode;

/**
 * @brief Enumerates animation playback directions.
 * @since 12
 */
typedef enum {
    /**
     * The animation plays in forward loop mode.
     */
    ARKUI_ANIMATION_DIRECTION_NORMAL = 0,
    /**
     * The animation plays in reverse loop mode.
     */
    ARKUI_ANIMATION_DIRECTION_REVERSE,
    /**
     * The animation plays in alternating loop mode. When the animation is played for an odd number of times, the
     * playback is in forward direction. When the animation is played for an even number of times, the playback is in
     * reverse direction.
     */
    ARKUI_ANIMATION_DIRECTION_ALTERNATE,
    /**
     * The animation plays in reverse alternating loop mode. When the animation is played for an odd number of times,
     * the playback is in reverse direction. When the animation is played for an even number of times, the playback is
     * in forward direction.
     */
    ARKUI_ANIMATION_DIRECTION_ALTERNATE_REVERSE,
} ArkUI_AnimationDirection;

/**
 * @brief Enumerates the animatable property types for property animations, keyframe animations, and path animations.
 *
 * @since 26.0.1
 */
typedef enum {
    /**
     * @brief Translation in both x and y directions.
     * When setting or getting this property value, requires two f32 {@link ArkUI_NumberValue} elements, for
     * the x and y translation amounts respectively, in px.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION = 0,
    /**
     * @brief Translation in the x direction.
     * When setting or getting this property value, requires one f32 {@link ArkUI_NumberValue} element, in px.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION_X = 1,
    /**
     * @brief Translation in the y direction.
     * When setting or getting this property value, requires one f32 {@link ArkUI_NumberValue} element, in px.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION_Y = 2,
    /**
     * @brief Translation in the z direction.
     * When setting or getting this property value, requires one f32 {@link ArkUI_NumberValue} element, in px.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION_Z = 3,
    /**
     * @brief Scale in both x and y directions.
     * When setting or getting this property value, requires two f32 {@link ArkUI_NumberValue} elements, for
     * the x and y scale ratios respectively.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_SCALE = 4,
    /**
     * @brief Scale in the x direction.
     * When setting or getting this property value, requires one f32 {@link ArkUI_NumberValue} element.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_SCALE_X = 5,
    /**
     * @brief Scale in the y direction.
     * When setting or getting this property value, requires one f32 {@link ArkUI_NumberValue} element.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_SCALE_Y = 6,
    /**
     * @brief Rotation angle for all axes.
     * When setting or getting this property value, requires three f32 {@link ArkUI_NumberValue} elements,
     * for the x, y, and z axis rotation angles respectively, in degrees.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_ROTATION = 7,
    /**
     * @brief Rotation angle around the x-axis.
     * When setting or getting this property value, requires one f32 {@link ArkUI_NumberValue} element, in degrees.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_ROTATION_X = 8,
    /**
     * @brief Rotation angle around the y-axis.
     * When setting or getting this property value, requires one f32 {@link ArkUI_NumberValue} element, in degrees.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_ROTATION_Y = 9,
    /**
     * @brief Rotation angle around the z-axis.
     * When setting or getting this property value, requires one f32 {@link ArkUI_NumberValue} element, in degrees.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_ROTATION_Z = 10,
    /**
     * @brief Opacity of the component.
     * When setting or getting this property value, requires one f32 {@link ArkUI_NumberValue} element.
     * Value range: [0, 1].
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_OPACITY = 11,
    /**
     * @brief Bounds (position and size).
     * When setting or getting this property value, requires four i32 {@link ArkUI_NumberValue} elements,
     * for the x coordinate, y coordinate, width, and height respectively, in px. Value range of width and
     * height: greater than or equal to 0.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_BOUNDS = 12,
    /**
     * @brief Position x within bounds.
     * When setting or getting this property value, requires one i32 {@link ArkUI_NumberValue} element, in px.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_X = 13,
    /**
     * @brief Position y within bounds.
     * When setting or getting this property value, requires one i32 {@link ArkUI_NumberValue} element, in px.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_Y = 14,
    /**
     * @brief Width of the bounds.
     * When setting or getting this property value, requires one i32 {@link ArkUI_NumberValue} element, in px.
     * Value range: greater than or equal to 0.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_WIDTH = 15,
    /**
     * @brief Height of the bounds.
     * When setting or getting this property value, requires one i32 {@link ArkUI_NumberValue} element, in px.
     * Value range: greater than or equal to 0.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_HEIGHT = 16,
    /**
     * @brief Background color of the component.
     * When setting or getting this property value, requires one u32 {@link ArkUI_NumberValue} element.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_PROPERTY_BACKGROUND_COLOR = 17,
} OH_ArkUI_AnimationPropertyType;

/**
 * @brief Enumerates the playback states of an animation group.
 *
 * @since 26.0.1
 */
typedef enum {
    /**
     * @brief The animation group is running.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_GROUP_STATE_RUNNING = 0,
    /**
     * @brief The animation group is paused.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_GROUP_STATE_PAUSED = 1,
    /**
     * @brief The animation group is inactive, for example, when the animation has finished or when the group is
     * in an invalid state.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_GROUP_STATE_INACTIVE = 2,
} OH_ArkUI_AnimationGroupState;

/**
 * @brief Enumerates the finish modes of an animation group.
 *
 * @since 26.0.1
 */
typedef enum {
    /**
     * @brief Finishes the animation group and jumps to the start state.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_FINISH_TO_START = 0,
    /**
     * @brief Finishes the animation group and stays at the current value.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_FINISH_TO_CURRENT = 1,
    /**
     * @brief Finishes the animation group and jumps to the end state.
     * @since 26.0.1
     */
    OH_ARKUI_ANIMATION_FINISH_TO_END = 2,
} OH_ArkUI_AnimationFinishMode;

/**
 * @brief Defines the translation options for component transition, used to set the translation distance of a component
 * in the x, y, and z directions during the transition.
 *
 * @since 12
 */
typedef struct {
    /**
     * X-axis translation distance, in vp. Value principles: A positive value indicates translation to the right, a
     * negative value indicates translation to the left, and **0** indicates no translation. Default value: **0**.
     */
    float x;
    /**
     * Y-axis translation distance, in vp. Value principles: A positive value indicates translation downward, a negative
     * value indicates translation upward, and **0** indicates no translation. Default value: **0**.
     */
    float y;
    /**
     * Z-axis translation distance, in vp. Value principles: A positive value indicates translation toward the observer,
     * a negative value indicates translation away from the observer, and **0** indicates no translation. When moving
     * along the z-axis, since the observation point remains unchanged, the component will be scaled up as the value of *
     **z** approaches the observation point and scaled in as it moves away. Default value: **0**.
     */
    float z;
} ArkUI_TranslationOptions;

/**
 * @brief Defines the scale options for component transition.
 * @since 12
 */
typedef struct {
    /**
     * Scale factor along the x-axis. The default value is **1.0**. x > 1: The component is scaled up along the x-axis.
     *0 < x < 1: The component is scaled down along the x-axis. x < 0: The component is scaled in the reversed
     * direction along the x-axis, with the scale factor being |x|. The scaling is performed with **centerX** as the
     * anchor point. Note: when x = 0, the component completely disappears along the x-axis. Pay attention to the impact
     * of this special value when using it.
     */
    float x;
    /**
     * Scale factor along the y-axis. The default value is **1.0**. y > 1: The component is scaled up along the y-axis.
     *0 < y < 1: The component is scaled down along the y-axis. y < 0: The component is scaled in the reversed
     * direction along the y-axis, with the scale factor being |y|. Note: when y = 0, the component completely
     * disappears along the y-axis. Pay attention to the impact of this special value when using it.
     */
    float y;
    /**
     * Scale factor along the z-axis. The default value is **1.0**. In 2D display mode, this parameter does not take
     * effect.
     */
    float z;
    /**
     * X-coordinate of the component transformation center point (that is, the anchor point), in percentage. **0**
     * indicates the left edge of the component, **1** indicates the right edge of the component, and **0.5** indicates
     * the horizontal center of the component. The default value is **0.5**. The scaling effect along the x-axis is
     * performed with this point as the anchor point. Different **centerX** values determine the x-direction positions
     * of the scaling anchor point. When the value is **0**, the scaling is performed from the left edge of the
     * component; when the value is **0.5**, the scaling is performed from the horizontal center; when the value is **1**
     *, the scaling is performed from the right edge.
     */
    float centerX;
    /**
     * Y-coordinate of the component transformation center point (that is, the anchor point), in percentage. **0**
     * indicates the top edge of the component, **1** indicates the bottom edge of the component, and **0.5** indicates
     * the vertical center of the component. The default value is **0.5**. The scaling effect along the y-axis is
     * performed with this point as the anchor point. Different **centerY** values determine the y-direction positions
     * of the scaling anchor point. When the value is **0**, the scaling is performed from the top edge of the component;
     * when the value is **0.5**, the scaling is performed from the vertical center; when the value is **1**, the
     * scaling is performed from the bottom edge.
     */
    float centerY;
} ArkUI_ScaleOptions;

/**
 * @brief Defines the rotation options for component transition.
 *
 * @since 12
 */
typedef struct {
    /**
     * X-component of the rotation vector, which jointly defines the rotation axis direction with the y axis and z axis.
     * Value range: (-∞, +∞).
     */
    float x;
    /**
     * Y-component of the rotation vector, which jointly defines the rotation axis direction with the x axis and z axis.
     * Value range: (-∞, +∞).
     */
    float y;
    /**
     * Z-component of the rotation vector, which jointly defines the rotation axis direction with the x axis and y axis.
     * Value range: (-∞, +∞).
     */
    float z;
    /**
     * Rotation angle, in degrees (°). Value range: (-∞, +∞). A positive value indicates clockwise rotation along the
     * rotation axis direction determined by (x, y, z), and a negative value indicates counterclockwise rotation along
     * that direction.
     */
    float angle;
    /**
     * X-coordinate of the component transformation center point (that is, the anchor point), in percentage. **0**
     * indicates the left edge of the component, **1** indicates the right edge of the component, and **0.5** indicates
     * the horizontal center of the component. The default value is **0.5**. The scaling effect along the x-axis is
     * performed with this point as the anchor point. Different **centerX** values determine the x-direction positions
     * of the scaling anchor point. When the value is **0**, the scaling is performed from the left edge of the
     * component; when the value is **0.5**, the scaling is performed from the horizontal center; when the value is **1**
     *, the scaling is performed from the right edge.
     */
    float centerX;
    /**
     * Y-coordinate of the component transformation center point (that is, the anchor point), in percentage. **0**
     * indicates the top edge of the component, **1** indicates the bottom edge of the component, and **0.5** indicates
     * the vertical center of the component. The default value is **0.5**. The scaling effect along the y-axis is
     * performed with this point as the anchor point. Different **centerY** values determine the y-direction positions
     * of the scaling anchor point. When the value is **0**, the scaling is performed from the top edge of the component;
     * when the value is **0.5**, the scaling is performed from the vertical center; when the value is **1**, the
     * scaling is performed from the bottom edge.
     */
    float centerY;
    /**
     * Z-component of the 3D rotation center point, in percentage. **0** indicates the plane where the component is
     * located, a positive value indicates that the rotation center is offset toward the observer, and a negative value
     * indicates that the rotation center is offset away from the observer. The presentation of the 3D rotation effect
     * is affected by the **perspective** parameter.
     */
    float centerZ;
    /**
     * Viewing distance, that is, the distance from the viewpoint to the z=0 plane, which is the z-coordinate where the
     * camera is placed, in px. The value indicates the viewing distance, that is, the distance from the camera to the z=
     *0 plane. The sign of the value determines the direction in which the camera observes. When **perspective** is set
     * to **0**, the system automatically calculates a suitable z-axis position for the camera, which is a negative
     * value.
     */
    float perspective;
} ArkUI_RotationOptions;

/**
 * @brief Defines a two-dimensional coordinate point, used to describe coordinate information such as the component
 * position or offset. The coordinates are stored as floating-point numbers.
 * @since 24
 */
typedef struct {
    /**
     * X-coordinate, in px. Value range: (-∞, +∞).
     */
    float x;
    /**
     * Y-coordinate, in px. Value range: (-∞, +∞).
     */
    float y;
} ArkUI_PointF;

/**
 * @brief Defines shadow options for setting the shadow effect of a component, including attributes such as the
 * shadow color, offset, blur radius, shadow type, and whether to fill.<br>
 * Call {@link OH_ArkUI_ShadowOptions_Create} to create the corresponding shadow option object.<br>
 * Call {@link OH_ArkUI_ShadowOptions_Destroy} to destroy the shadow option object.<br>
 * After the object is created, call the <b>OH_ArkUI_ShadowOptions_SetXXX</b> series APIs to set the specific
 * styles to take effect, for example, call {@link OH_ArkUI_ShadowOptions_SetRadius} to set the shadow blur
 * radius. If the object fails to be created (a null pointer is returned), calling the <b>SetXXX</b> series APIs
 * will not take effect.
 *
 * @since 24
 */
typedef struct OH_ArkUI_ShadowOptions OH_ArkUI_ShadowOptions;

/**
 * @brief Defines the motion path configuration options of path animation, which are used to set the trajectory and
 * related parameters of a component moving along a specified path during animation, so that the component can perform
 * displacement animation along the preset motion path.
 * @since 23
 */
typedef struct ArkUI_MotionPathOptions ArkUI_MotionPathOptions;

/**
 * @brief Create a motion path option for path animation. When the object is no longer used, call
 * {@link OH_ArkUI_MotionPathOptions_Dispose} to dispose of it.
 * @return Pointer to {@link ArkUI_MotionPathOptions}.
 *     <br>In the newly created {@link ArkUI_MotionPathOptions} object, **path** (motion path) is an empty string,
 *     **from** ( start progress) is **0**, **to** (end progress) is **1**, and **rotatable** (whether the component
 *     rotates along the path) is **false**.
 * @since 23
 */
ArkUI_MotionPathOptions* OH_ArkUI_MotionPathOptions_Create();

/**
 * @brief Disposes of a motion path option of path animation.
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @since 23
 */
void OH_ArkUI_MotionPathOptions_Dispose(ArkUI_MotionPathOptions* options);

/**
 * @brief Sets the motion path of path animation.
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param svgPath Pointer to the motion path string of path animation.
 * The path supports "start" and "end" as placeholders for the start and end points, for example, "Mstart.x start.y L50
 * 50 Lend.x end.y Z". For details about the path string format, see {@link Path Drawing}. Setting this to an empty
 * string is equivalent to not setting a motion path.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetPath(ArkUI_MotionPathOptions* options, const char* svgPath);

/**
 * @brief Obtains the motion path string stored in the motion path configuration item of the path animation.
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param svgPathBuffer Pointer to the buffer for storing the motion path string. The pointer cannot be null. The
 * buffer size must be sufficient to accommodate the path string.
 * @param bufferSize Size of the buffer specified by the **svgPathBuffer** parameter. The value must be greater than 0.
 * If 0 or a negative number is passed, {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param writeLength Pointer to the length of the string (including the terminator) actually written to the buffer if
 * {@link ARKUI_ERROR_CODE_NO_ERROR} is returned.
 * When {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned due to an input parameter error, **writeLength** is not
 * assigned. If the error is due to a copy exception, **writeLength** indicates the minimum buffer size required to
 * hold the target string.
 * When {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned, it indicates the minimum buffer size required to hold
 * the target string.
 * @return <ul> .
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the buffer size is less than the minimum buffer size.</li>
 *         </ul>
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetPath(const ArkUI_MotionPathOptions* options, char* svgPathBuffer,
    const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Sets the start progress of the path animation. The progress refers to the ratio of the distance already moved
 * along the path to the total path length.
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param from Start progress of the path animation, ranging from 0.0 to 1.0. This value must be less than or equal to
 * the end progress specified by **to**. Otherwise, the error {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} will be
 * returned.
 * For details about **to**, see {@link OH_ArkUI_MotionPathOptions_SetTo}.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if **from** is out of the range [0.0, 1.0] or **from** is
 *              greater than **to**.</li>
 *         </ul>
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetFrom(ArkUI_MotionPathOptions* options, const float from);

/**
 * @brief Obtains the start progress of the path animation.
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param from Pointer to the start progress in {@link ArkUI_MotionPathOptions}.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetFrom(const ArkUI_MotionPathOptions* options, float* from);

/**
 * @brief Sets the end progress of the path animation. The progress refers to the ratio of the distance already moved
 * along the path to the total path length.
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param to End progress of the path animation, ranging from 0.0 to 1.0. This value must be greater than or equal to
 * the start progress specified by **from**. Otherwise, the error {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} will be
 * returned.
 * For details about the meaning of **from**, see {@link OH_ArkUI_MotionPathOptions_SetFrom}.
 * @return <ul>.
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if **to** is out of the range [0.0, 1.0] or **to** is less than
 *          **from**.</li>
 *         </ul>
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetTo(ArkUI_MotionPathOptions* options, const float to);

/**
 * @brief Obtains the end progress of the path animation.
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param to Pointer to the end progress in {@link ArkUI_MotionPathOptions}.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetTo(const ArkUI_MotionPathOptions* options, float* to);

/**
 * @brief Sets whether a component rotates along the motion path.
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param rotatable Whether the component rotates along the path. **true**: The component rotates along the path. **
 * false**: The component does not rotate along the path. The default value is **false**.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetRotatable(ArkUI_MotionPathOptions* options, const bool rotatable);

/**
 * @brief Obtains whether a component rotates along the motion path.
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param rotatable Pointer to the **rotatable** parameter value in {@link ArkUI_MotionPathOptions}, indicating whether
 * the component rotates along the path.
 * **true**: The component rotates along the path. **false**: The component does not rotate along the path.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetRotatable(const ArkUI_MotionPathOptions* options, bool* rotatable);

/**
 * @brief Creates a shadow option object. In the newly created object, the default value of the blur radius (**radius**)
 * is **0**, the default value of the shadow offset on the x-axis (**offsetX**) is **0**, the default value of the
 * shadow offset on the y-axis (**offsetY**) is **0**, the default value of the shadow color (**color**) is **
 * 0xFF000000**, the default value of the shadow type (**type**) is **ARKUI_SHADOW_TYPE_COLOR**, and the default value
 * of whether to fill the component with shadow (**isFill**) is **false**. If the object is no longer used, call
 * {@link OH_ArkUI_ShadowOptions_Destroy} to destroy it.
 * @return Pointer to the newly created {@link OH_ArkUI_ShadowOptions} object, which is used to set the blur radius,
 * type, color, and offset of the shadow.
 * @since 24
 */
OH_ArkUI_ShadowOptions* OH_ArkUI_ShadowOptions_Create();

/**
 * @brief Destroys the shadow option object.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @since 24
 */
void OH_ArkUI_ShadowOptions_Destroy(OH_ArkUI_ShadowOptions* options);

/**
 * @brief Sets the blur radius for the shadow options.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param radius Blur radius of the shadow, in vp.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetRadius(OH_ArkUI_ShadowOptions* options, float radius);

/**
 * @brief Obtains the blur radius for the shadow options.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param radius Pointer to the blur radius of the shadow, in vp.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetRadius(OH_ArkUI_ShadowOptions* options, float* radius);

/**
 * @brief Sets the shadow type for the shadow options.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param type Shadow type ({@link ArkUI_ShadowType}).
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetType(OH_ArkUI_ShadowOptions* options, ArkUI_ShadowType type);

/**
 * @brief Obtains the shadow type for the shadow options.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param type Shadow type ({@link ArkUI_ShadowType}).
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetType(OH_ArkUI_ShadowOptions* options, ArkUI_ShadowType* type);

/**
 * @brief Sets the shadow color for the shadow options.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param color Shadow color, in 0xARGB format.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetColor(OH_ArkUI_ShadowOptions* options, uint32_t color);

/**
 * @brief Obtains the shadow color of the shadow options.
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param color Pointer to the shadow color, in 0xARGB format.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetColor(OH_ArkUI_ShadowOptions* options, uint32_t* color);

/**
 * @brief Sets the shadow offset on the x-axis.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param offsetX Shadow offset on the x-axis, in vp.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetOffsetX(OH_ArkUI_ShadowOptions* options, float offsetX);

/**
 * @brief Obtains the shadow offset on the x-axis.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param offsetX Pointer to the shadow offset on the x-axis, in vp.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetOffsetX(OH_ArkUI_ShadowOptions* options, float* offsetX);

/**
 * @brief Sets the shadow offset on the y-axis.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param offsetY Shadow offset on the y-axis, in vp.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetOffsetY(OH_ArkUI_ShadowOptions* options, float offsetY);

/**
 * @brief Obtains the shadow offset on the y-axis.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param offsetY Pointer to the shadow offset on the y-axis, in vp.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetOffsetY(OH_ArkUI_ShadowOptions* options, float* offsetY);

/**
 * @brief Sets whether to fill a component with a shadow.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param isFill Whether to fill a component with a shadow. **true** means to fill a component with a shadow, and **
 * false** means the opposite. The default value is **false**.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetFill(OH_ArkUI_ShadowOptions* options, bool isFill);

/**
 * @brief Obtains whether a component is filled with a shadow.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param isFill Pointer to the **isFill** parameter indicating whether a component is filled with a shadow. **true**
 * means a component is filled with a shadow, and **false** means the opposite. The default value is **false**.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetFill(OH_ArkUI_ShadowOptions* options, bool* isFill);

/**
 * @brief Defines the configuration options for 4 × 4 matrix scaling. For details about the parameters and their value
 * principles, see member variable descriptions.
 * @since 24
 */
typedef struct ArkUI_Matrix4ScaleOptions ArkUI_Matrix4ScaleOptions;

/**
 * @brief Creates a pointer to the scaling parameter object for matrix operations. In the newly created object, the
 * default scaling coefficients in the x, y, and z directions are 1. The default values of **centerX** and **centerY**
 * of the transformation center point are 0. When the object is no longer used, call
 * {@link OH_ArkUI_Matrix4ScaleOptions_Dispose} to destroy it.
 * @return Pointer to the newly created {@link ArkUI_Matrix4ScaleOptions} object, which is used to set the scaling
 * parameters for matrix operations.
 * @since 24
 */
ArkUI_Matrix4ScaleOptions* OH_ArkUI_Matrix4ScaleOptions_Create();

/**
 * @brief Disposes of the pointer to the scaling parameter object for matrix operations.
 * @param options Pointer to the {@link ArkUI_Matrix4ScaleOptions} object to be disposed of.
 * @since 24
 */
void OH_ArkUI_Matrix4ScaleOptions_Dispose(ArkUI_Matrix4ScaleOptions* options);

/**
 * @brief Sets the scaling factor in the x direction of the scaling parameter object for matrix operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param scaleX Scaling factor in the x direction. The value range is (-∞, +∞).
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetX(ArkUI_Matrix4ScaleOptions* options, const float scaleX);

/**
 * @brief Obtains the scaling factor in the x direction of the scaling parameter object for matrix operations. If the
 * value of **x** is not set, the default value of the scaling factor in the x direction is 1.
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param scaleX Pointer to the scaling factor in the x direction.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetX(const ArkUI_Matrix4ScaleOptions* options, float* scaleX);

/**
 * @brief Sets the scaling factor in the y direction of the scaling parameter object for matrix operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param scaleY Scaling factor in the y direction. The value range is (-∞, +∞).
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetY(ArkUI_Matrix4ScaleOptions* options, const float scaleY);

/**
 * @brief Obtains the scaling factor in the y direction of the scaling parameter object for matrix operations. If the
 * value of **y** is not set, the default value of the scaling factor in the y direction is 1.
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param scaleY Pointer to the scaling factor in the y direction.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetY(const ArkUI_Matrix4ScaleOptions* options, float* scaleY);

/**
 * @brief Sets the scaling factor in the z direction of the scaling parameter object for matrix operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param scaleZ Scaling factor in the z direction. The value range is (-∞, +∞).
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetZ(ArkUI_Matrix4ScaleOptions* options, const float scaleZ);

/**
 * @brief Obtains the scaling factor in the z direction of the scaling parameter object for matrix operations. If the
 * value of **z** is not set, the default value of the scaling factor in the z direction is 1.
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param scaleZ Pointer to the scaling factor in the z direction.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetZ(const ArkUI_Matrix4ScaleOptions* options, float* scaleZ);

/**
 * @brief Sets the x coordinate of the transformation center point of the scaling parameter object for matrix
 * operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param centerX X-coordinate of the transformation center point. The value range is (-∞, +∞). **0** indicates that
 * there is no x-axis offset based on the transformation center. The unit is px.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetCenterX(ArkUI_Matrix4ScaleOptions* options, const float centerX);

/**
 * @brief Obtains the x coordinate of the transformation center point of the scaling parameter object for matrix
 * operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param centerX Pointer to the X-coordinate of the transformation center point. The unit is px. The default value is *
 * *0**.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetCenterX(const ArkUI_Matrix4ScaleOptions* options, float* centerX);

/**
 * @brief Sets the y coordinate of the transformation center point of the scaling parameter object for matrix
 * operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param centerY Y-coordinate of the transformation center point. The value range is (-∞, +∞). **0** indicates that
 * there is no y-axis offset based on the transformation center. The unit is px.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetCenterY(ArkUI_Matrix4ScaleOptions* options, const float centerY);

/**
 * @brief Obtains the y coordinate of the transformation center point of the scaling parameter object for matrix
 * operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param centerY Pointer to the Y-coordinate of the transformation center point. The unit is px. The default value is *
 * *0**.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetCenterY(const ArkUI_Matrix4ScaleOptions* options, float* centerY);

/**
 * @brief Defines matrix rotation options.
 * @since 24
 */
typedef struct ArkUI_Matrix4RotationOptions ArkUI_Matrix4RotationOptions;

/**
 * @brief Creates a pointer to the rotation parameter object for matrix operations. In the newly created object, the
 * default value of an x-axis offset (**centerX**) of a single matrix transformation center point relative to a
 * component transformation center point, the default value of a y-axis offset (**centerY**) of the single matrix
 * transformation center point relative to the component transformation center point, and the default value of a
 * rotation angle (**angle**) are 0. If any one of the vectors in the x, y, and z directions is not specified, the
 * rotate effect is equivalent to rotating around the z axis (that is, the direction vectors are x=0, y=0, and z=1
 * during calculation). Once any of the vectors in the x, y, and z directions is specified, the specified vector takes
 * effect.
 * @return Pointer to the newly created {@link ArkUI_Matrix4RotationOptions} object, which is used to set the rotation
 * parameters for matrix operations.
 * @since 24
 */
ArkUI_Matrix4RotationOptions* OH_ArkUI_Matrix4RotationOptions_Create();

/**
 * @brief Disposes of the pointer to the rotation parameter object for matrix operations.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @since 24
 */
void OH_ArkUI_Matrix4RotationOptions_Dispose(ArkUI_Matrix4RotationOptions* options);

/**
 * @brief Sets the direction vector in the x direction of the rotation parameter object for matrix operations.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param x Value of the direction vector in the x direction. The value range is (-∞, +∞). It forms the rotation axis
 * together with the vectors in the y and z directions. For example, if x=1, y=0, and z=0, the rotation is around the x
 * axis.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetX(ArkUI_Matrix4RotationOptions* options, const float x);

/**
 * @brief Obtains the direction vector in the x direction of the rotation parameter object for matrix operations. If
 * the value of **x** has never been set, the value is undefined. In this case, {@link ARKUI_ERROR_CODE_PARAM_INVALID}
 * is returned.
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param x Pointer to the value of the direction vector in the x direction. If the value of **x** has never been set,
 * the value is undefined. This parameter, together with the y and z direction vectors, forms the rotation axis.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetX(const ArkUI_Matrix4RotationOptions* options, float* x);

/**
 * @brief Sets the direction vector in the y direction of the rotation parameter object for matrix operations.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param y Value of the direction vector in the y direction. The value range is (-∞, +∞). It forms the rotation axis
 * together with the vectors in the x and z directions. For example, if y=1, x=0, and z=0, the rotation is around the y
 * axis.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetY(ArkUI_Matrix4RotationOptions* options, const float y);

/**
 * @brief Obtains the direction vector in the y direction of the rotation parameter object for matrix operations. If
 * the value of **y** has never been set, the value is undefined. In this case, {@link ARKUI_ERROR_CODE_PARAM_INVALID}
 * is returned.
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param y Pointer to the value of the direction vector in the y direction. If the value of **y** has never been set,
 * the value is undefined. This parameter, together with the x and z direction vectors, forms the rotation axis.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetY(const ArkUI_Matrix4RotationOptions* options, float* y);

/**
 * @brief Sets the direction vector in the z direction of the rotation parameter object for matrix operations.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param z Value of the direction vector in the z direction. The value range is (-∞, +∞). It forms the rotation axis
 * together with the vectors in the x and y directions. For example, if z=1, x=0, and y=0, the rotation is around the z
 * axis (default behavior).
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetZ(ArkUI_Matrix4RotationOptions* options, const float z);

/**
 * @brief Obtains the direction vector in the z direction of the rotation parameter object for matrix operations. If
 * the value of **z** has never been set, the value is undefined. In this case, {@link ARKUI_ERROR_CODE_PARAM_INVALID}
 * is returned.
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param z Pointer to the value of the direction vector in the z direction. If the value of **z** has never been set,
 * the value is undefined. This parameter, together with the x and y direction vectors, forms the rotation axis.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetZ(const ArkUI_Matrix4RotationOptions* options, float* z);

/**
 * @brief Sets the rotation angle in the rotation parameter object for matrix operations.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param angle Value of the rotation angle. The value range is (-∞, +∞). The unit is degree.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetAngle(ArkUI_Matrix4RotationOptions* options, const float angle);

/**
 * @brief Obtains the rotation angle in the rotation parameter object for matrix operations.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param angle Pointer to the value of the rotation angle. The unit is degree. If the angle has never been set, the
 * default value is **0**.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetAngle(const ArkUI_Matrix4RotationOptions* options, float* angle);

/**
 * @brief Sets the x-axis offset of a single matrix transformation center point relative to a component transformation
 * center point.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param centerX X-axis offset of a single matrix transformation center point relative to a component transformation
 * center point. The value range is (-∞, +∞). **0** indicates that there is no x-axis offset based on the
 * transformation center. The unit is px.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetCenterX(ArkUI_Matrix4RotationOptions* options, const float centerX);

/**
 * @brief Obtains the x-axis offset of a single matrix transformation center point relative to a component
 * transformation center point.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param centerX Pointer to the x-axis offset of a single matrix transformation center point relative to a component
 * transformation center point. The unit is px. If **centerX** has never been set, the default value is **0**.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetCenterX(const ArkUI_Matrix4RotationOptions* options, float* centerX);

/**
 * @brief Sets the y-axis offset of a single matrix transformation center point relative to a component transformation
 * center point.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param centerY Y-axis offset of a single matrix transformation center point relative to a component transformation
 * center point. The value range is (-∞, +∞). **0** indicates that there is no y-axis offset based on the
 * transformation center. The unit is px.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetCenterY(ArkUI_Matrix4RotationOptions* options, const float centerY);

/**
 * @brief Obtains the y-axis offset of a single matrix transformation center point relative to a component
 * transformation center point.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param centerY Pointer to the y-axis offset of a single matrix transformation center point relative to a component
 * transformation center point. The unit is px. If **centerY** has never been set, the default value is **0**.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>curs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetCenterY(const ArkUI_Matrix4RotationOptions* options, float* centerY);

/**
 * @brief Defines the configuration options for matrix translation.
 * @since 24
 */
typedef struct ArkUI_Matrix4TranslationOptions ArkUI_Matrix4TranslationOptions;

/**
 * @brief Creates a pointer to a translation object for matrix operations. In the newly created object, the default
 * translation distances on the x, y, and z axes are 0. When the object is no longer used, call
 * {@link OH_ArkUI_Matrix4TranslationOptions_Dispose} to destroy it.
 * @return Pointer to the newly created {@link ArkUI_Matrix4TranslationOptions} object, which is used to set the
 * translation parameters for matrix operations.
 * @since 24
 */
ArkUI_Matrix4TranslationOptions* OH_ArkUI_Matrix4TranslationOptions_Create();

/**
 * @brief Disposes of the pointer to the translation object for matrix operations.
 * @param options Pointer to the {@link ArkUI_Matrix4TranslationOptions} object to be disposed of.
 * @since 24
 */
void OH_ArkUI_Matrix4TranslationOptions_Dispose(ArkUI_Matrix4TranslationOptions* options);

/**
 * @brief Sets the translation value of a translation object on the x-axis for matrix operations, in px.
 * @param options Pointer to the translation parameter object for matrix operations.
 * @param x Translation value on the x-axis. The value range is (-∞, +∞). The unit is px. If the value of **x** has
 * never been set, the default value is **0**.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetX(ArkUI_Matrix4TranslationOptions* options, const float x);

/**
 * @brief Obtains the translation value of a translation object on the x-axis for matrix operations, in px. If the
 * value of **x** has never been set, the default value is **0**.
 * @param options Pointer to the translation parameter object for matrix operations.
 * @param x Pointer to the translation value on the x-axis. The unit is px.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetX(const ArkUI_Matrix4TranslationOptions* options, float* x);

/**
 * @brief Sets the translation value of a translation object on the y-axis for matrix operations, in px.
 * @param options Pointer to the translation parameter object for matrix operations.
 * @param y Translation value on the y-axis. The value range is (-∞, +∞). The unit is px. If the value of **y** has
 * never been set, the default value is **0**.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetY(ArkUI_Matrix4TranslationOptions* options, const float y);

/**
 * @brief Obtains the translation value of a translation object on the y-axis for matrix operations, in px. If the
 * value of **y** has never been set, the default value is **0**.
 * @param options Pointer to the translation parameter object for matrix operations.
 * @param y Pointer to the translation value on the y-axis. The unit is px.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetY(const ArkUI_Matrix4TranslationOptions* options, float* y);

/**
 * @brief Sets the translation value of a translation object on the z-axis for matrix operations, in px.
 * @param options Pointer to the translation parameter object for matrix operations.
 * @param z Translation value on the z-axis. The value range is (-∞, +∞). The unit is px. If the value of **z** has
 * never been set, the default value is **0**.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetZ(ArkUI_Matrix4TranslationOptions* options, const float z);

/**
 * @brief Obtains the translation value of a translation object on the z-axis for matrix operations, in px. If the
 * value of **z** has never been set, the default value is **0**.
 * @param options Pointer to the translation parameter object for matrix operations.
 * @param z Pointer to the translation value on the z-axis. The unit is px.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetZ(const ArkUI_Matrix4TranslationOptions* options, float* z);

/**
 * @brief Creates a fourth-order identity matrix object.
 *
 * @return Pointer to the created fourth-order identity matrix object.
 * @since 24
 */
ArkUI_Matrix4* OH_ArkUI_Matrix4_CreateIdentity();

/**
 * @brief Creates a fourth-order matrix object by specifying each element of the matrix.
 *
 * @param elements Pointer to the array of expected matrix element data. The array length must be greater than or equal
 * to 16. If the length is less than 16, undefined behavior may occur. This parameter cannot be a null pointer. If it
 * is a null pointer, the API returns a null value.
 * @return Pointer to the fourth-order matrix object created using the specified matrix elements. If the **elements**
 * pointer is null, **NULL** is returned.
 * @since 24
 */
ArkUI_Matrix4* OH_ArkUI_Matrix4_CreateByElements(const float* elements);

/**
 * @brief Disposes of the pointer to the matrix object.
 * @param matrix Pointer to the fourth-order matrix object to be disposed of.
 * @since 24
 */
void OH_ArkUI_Matrix4_Dispose(ArkUI_Matrix4* matrix);

/**
 * @brief Creates a copy of a fourth-order matrix object. By copying the original matrix, you can perform operations on
 * it independently to obtain different matrix transformation results. When the copy object is no longer used, call
 * {@link OH_ArkUI_Matrix4_Dispose} to dispose of it.
 * @param matrix Pointer to the original fourth-order matrix object.
 * @return Pointer to the copy of the fourth-order matrix object.
 * @since 24
 */
ArkUI_Matrix4* OH_ArkUI_Matrix4_Copy(const ArkUI_Matrix4* matrix);

/**
 * @brief Performs an inverse matrix transformation on the input matrix. The input matrix object will be modified after
 * the transformation.
 * @param matrix Pointer to the fourth-order matrix object for which inverse matrix transformation is to be performed.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Invert(ArkUI_Matrix4* matrix);

/**
 * @brief Combines another matrix with the original matrix and stores the result matrix in **oriMatrix**. In this case,
 * the result matrix applies the transformation of **oriMatrix** and then applies the transformation of **anotherMatrix*
 * *. This API will modify the **oriMatrix** object.
 * @param oriMatrix Pointer to the original fourth-order matrix object.
 * @param anotherMatrix Pointer to another matrix object to be combined.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Combine(ArkUI_Matrix4* oriMatrix, const ArkUI_Matrix4* anotherMatrix);

/**
 * @brief Applies translation transformation to the original matrix to obtain the translated matrix. Each translation
 * transformation is accumulated on the previous matrix. The input matrix object will be modified after the
 * transformation.
 * @param matrix Pointer to the fourth-order matrix object to be translated.
 * @param translate Pointer to the translation object.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Translate(ArkUI_Matrix4* matrix, const ArkUI_Matrix4TranslationOptions* translate);

/**
 * @brief Applies scaling transformation to the original matrix to obtain the scaled matrix. Each scaling
 * transformation is accumulated on the previous matrix. This API will modify the input matrix object.
 * @param matrix Pointer to the fourth-order matrix object to be scaled.
 * @param scale Pointer to the scaling object.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Scale(ArkUI_Matrix4* matrix, const ArkUI_Matrix4ScaleOptions* scale);

/**
 * @brief Applies rotation transformation to the original matrix to obtain the rotated matrix. Each rotation
 * transformation is accumulated on the previous matrix. This API will modify the input matrix object.
 * @param matrix Pointer to the fourth-order matrix object to be rotated.
 * @param rotate Pointer to the rotation object.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Rotate(ArkUI_Matrix4* matrix, const ArkUI_Matrix4RotationOptions* rotate);

/**
 * @brief Applies skew transformation to the original matrix to obtain the skewed matrix. Each skew transformation is
 * accumulated on the previous matrix. The input matrix object will be modified after the transformation.
 * @param matrix Pointer to the fourth-order matrix object to be skewed.
 * @param skewX Skew coefficient in the x direction. The value range is (-∞, +∞). The value **0** indicates no skew. A
 * positive value skews the content forward in the x direction, and a negative value skews the content backward in the
 * x direction.
 * @param skewY Skew coefficient in the y direction. The value range is (-∞, +∞). The value **0** indicates no skew. A
 * positive value skews the content forward in the y direction, and a negative value skews the content backward in the
 * y direction.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Skew(ArkUI_Matrix4* matrix, const float skewX, const float skewY);

/**
 * @brief Calculates the new coordinate position of a point after it is transformed by a matrix.
 *
 * @param matrix Pointer to the fourth-order matrix object.
 * @param oriPoint Pointer to the original coordinate point.
 * @param result Pointer to the result point. This parameter cannot be set to a null pointer.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_TransformPoint(const ArkUI_Matrix4* matrix, const ArkUI_PointF* oriPoint, ArkUI_PointF* result);

/**
 * @brief Maps the vertex coordinates of one polygon to the vertex coordinates of another polygon and calculates the
 *     required matrix.
 *
 * @param matrix Pointer to the fourth-order matrix object, which is used to store the result matrix.
 * @param src Pointer to the array of original polygon coordinate points. The array length must be at least
 *     **pointCount**.
 * @param dst Pointer to the array of mapped polygon coordinate points. The array length must be at least **pointCount**.
 * @param pointCount Number of polygon points, which must be one of the values 0, 1, 2, 3, or 4.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_SetPolyToPoly(ArkUI_Matrix4* matrix, const ArkUI_PointF* src, const ArkUI_PointF* dst, const uint32_t pointCount);

/**
 * @brief Obtains the 16 elements of the fourth-order matrix.
 *
 * @param matrix Pointer to the fourth-order matrix object.
 * @param result Pointer to an array that can hold 16 floating-point numbers. This parameter cannot be set to a null
 *     pointer.
 * @return <ul> 
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_GetElements(const ArkUI_Matrix4* matrix, float* result);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_TYPE_VISUAL_H
/** @} */

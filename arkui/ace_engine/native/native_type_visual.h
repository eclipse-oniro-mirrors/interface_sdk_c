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
 * @brief Defines the visual effect types for the native module.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_TYPE_VISUAL_H
#define ARKUI_NATIVE_TYPE_VISUAL_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Defines a fourth-order matrix object.
 *
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
     * Mini shadow.<br>!{@link defaultxs}
     */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_XS = 0,
    /**
     * Small shadow.<br>!{@link defaultsm}
     */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_SM,
    /**
     * Medium shadow.<br>!{@link defaultmd}
     */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_MD,
    /**
     * Large shadow.<br>!{@link defaultlg}
     */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_LG,
    /**
     * Floating small shadow.<br>!{@link floatingsm}
     */
    ARKUI_SHADOW_STYLE_OUTER_FLOATING_SM,
    /**
     * Floating medium shadow.<br>!{@link floatingmd}
     */
    ARKUI_SHADOW_STYLE_OUTER_FLOATING_MD,
} ArkUI_ShadowStyle;

/**
 * @brief Enumerates the animation curves.
 *
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
 * @brief Enumerates the animation playback directions.
 *
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
 * @brief Enumerates the blur styles.
 *
 * @since 12
 */
typedef enum {
    /**
     * Thin material.<br>!{@link thin}
     */
    ARKUI_BLUR_STYLE_THIN = 0,
    /**
     * Regular material.<br>!{@link regular}
     */
    ARKUI_BLUR_STYLE_REGULAR,
    /**
     * Thick material.<br>!{@link thick}
     */
    ARKUI_BLUR_STYLE_THICK,
    /**
     * Material that creates the minimum depth of field effect.<br>!{@link backgroundthin}
     */
    ARKUI_BLUR_STYLE_BACKGROUND_THIN,
    /**
     * Material that creates a medium shallow depth of field effect.<br>!{@link backgroundregular}
     */
    ARKUI_BLUR_STYLE_BACKGROUND_REGULAR,
    /**
     * Material that creates a high shallow depth of field effect.<br>!{@link backgroundthick}
     */
    ARKUI_BLUR_STYLE_BACKGROUND_THICK,
    /**
     * Material that creates the maximum depth of field effect.<br>!{@link backgroundultrathick}
     */
    ARKUI_BLUR_STYLE_BACKGROUND_ULTRA_THICK,
    /**
     * No blur.<br>!{@link none}
     */
    ARKUI_BLUR_STYLE_NONE,
    /**
     * Component ultra-thin material.<br>!{@link componentultrathin}
     */
    ARKUI_BLUR_STYLE_COMPONENT_ULTRA_THIN,
    /**
     * Component thin material.<br>!{@link componentthin}
     */
    ARKUI_BLUR_STYLE_COMPONENT_THIN,
    /**
     * Component regular material.<br>!{@link componentregular}
     */
    ARKUI_BLUR_STYLE_COMPONENT_REGULAR,
    /**
     * Component thick material.<br>!{@link componentthick}
     */
    ARKUI_BLUR_STYLE_COMPONENT_THICK,
    /**
     * Component ultra-thick material.<br>!{@link componentultrathick}
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
 * @brief Enumerates the blend modes.
 *
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
 * @brief Enumerates the foreground colors.
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
 * @brief Enumerates the mask types.
 *
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
 * @brief Enumerates the clipping region types.
 *
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
 * @brief Enumerates the custom shapes.
 *
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
 * @brief Enumerates the gradient directions.
 *
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
 * @brief Enumerates the animation onFinish callback types.
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
 * @brief Enumerates the render fit.
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
 * @brief Defines the status before and after execution of the animation in the current playback direction.
 *
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
 * @brief Enumerates the animation playback modes.
 *
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
 * @brief Defines the translation options for component transition.
 *
 * @since 12
 */
typedef struct {
    /**
     * Translation distance along the x-axis.
     */
    float x;
    /**
     * Translation distance along the y-axis.
     */
    float y;
    /**
     * Translation distance along the z-axis.
     */
    float z;
} ArkUI_TranslationOptions;

/**
 * @brief Defines the scaling options for component transition.
 *
 * @since 12
 */
typedef struct {
    /**
     * Scale ratio along the x-axis.
     */
    float x;
    /**
     * Scale ratio along the y-axis.
     */
    float y;
    /**
     * Scale factor along the z-axis (not effective for the current 2D graphics).
     */
    float z;
    /**
     * X coordinate of the center point.
     */
    float centerX;
    /**
     * Y coordinate of the center point.
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
     * X-component of the rotation vector.
     */
    float x;
    /**
     * Y-component of the rotation vector.
     */
    float y;
    /**
     * Z-component of the rotation vector.
     */
    float z;
    /**
     * Rotation angle.
     */
    float angle;
    /**
     * X coordinate of the center point.
     */
    float centerX;
    /**
     * Y coordinate of the center point.
     */
    float centerY;
    /**
     * Z-axis anchor, that is, the z-component of the 3D rotation center point.
     */
    float centerZ;
    /**
     * Distance from the user to the z=0 plane.
     */
    float perspective;
} ArkUI_RotationOptions;

/**
 * @brief Defines shadow options.
 *
 * @since 24
 */
typedef struct OH_ArkUI_ShadowOptions OH_ArkUI_ShadowOptions;

/**
 * @brief Defines the motion path options for path animation.
 *
 * @since 23
 */
typedef struct ArkUI_MotionPathOptions ArkUI_MotionPathOptions;

/**
 * @brief Create a motion path option for path animation.
 *
 * @return Pointer to {@link ArkUI_MotionPathOptions}.
 *     <br>In the newly created {@link ArkUI_MotionPathOptions} object, **path** (motion path) is an empty string, **
 *     from** (start progress) is **0**, **to** (end progress) is **1**, and **rotatable** (whether the component
 *     rotates along the path) is **false**.
 * @since 23
 */
ArkUI_MotionPathOptions* OH_ArkUI_MotionPathOptions_Create();

/**
 * @brief Destroys a motion path option of path animation.
 *
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @since 23
 */
void OH_ArkUI_MotionPathOptions_Dispose(ArkUI_MotionPathOptions* options);

/**
 * @brief Sets the motion path for the animation using an SVG path string. The path supports using **start** and
 *     **end** as placeholders for the starting and ending points, for example:
 *     **Mstart.x start.y L50 50 Lend.x end.y Z**. For details about the path string format, see {@link Path}. If this
 *     parameter is set to an empty string, it is equivalent to not setting a path animation.
 *
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param svgPath Motion path string for the path animation.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetPath(ArkUI_MotionPathOptions* options, const char* svgPath);

/**
 * @brief Obtains the motion path string stored in the motion path option.
 *
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param svgPathBuffer Buffer pointer to the motion path string.
 * @param bufferSize Buffer size of the **svgPathBuffer** parameter.
 * @param writeLength Indicates the string length actually written to the buffer when {@link ARKUI_ERROR_CODE_NO_ERROR}
 *     is returned. Indicates the minimum buffer size that can accommodate the target string when
 *     {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the buffer size is less than the minimum buffer size.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetPath(const ArkUI_MotionPathOptions* options, char* svgPathBuffer,
    const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Sets the start progress of the motion path. Progress refers to the ratio of the length of the path that has
 *     been traveled to the total length of the entire path.
 *
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param from Start progress of the motion path. The value ranges from **0.0** to **1.0**. The value of **from** must
 *     be less than or equal to that of **to**; otherwise, {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} is returned.
 *     For details about the meaning of **to**, see {@link OH_ArkUI_MotionPathOptions_SetTo}.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if **from** is out of the range [0.0, 1.0] or **from** is
 *     greater than **to**.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetFrom(ArkUI_MotionPathOptions* options, const float from);

/**
 * @brief Obtains the start progress of the motion path from the motion path option.
 *
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param from Pointer to the variable used to receive the start progress of the motion path.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetFrom(const ArkUI_MotionPathOptions* options, float* from);

/**
 * @brief Sets the end progress of the motion path. Progress refers to the ratio of the length of the path that has
 *     been traveled to the total length of the entire path.
 *
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param to End progress of the motion path. The value ranges from **0.0** to **1.0**. The value of **to** must be
 *     greater than or equal to that of **from**; otherwise, {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} is returned.
 *     For details about the meaning of **from**, see {@link OH_ArkUI_MotionPathOptions_SetFrom}.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if **to** is out of the range [0.0, 1.0] or **to** is less than
 *     **from**.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetTo(ArkUI_MotionPathOptions* options, const float to);

/**
 * @brief Obtains the end progress of the motion path from the motion path option.
 *
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param to Pointer to the variable used to receive the end progress of the motion path.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetTo(const ArkUI_MotionPathOptions* options, float* to);

/**
 * @brief Sets whether the component rotates along the motion path.
 *
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param rotatable Whether the component rotates along the path. The value **true** means that the component rotates
 *     along the path, and **false** means that the component does not rotate along the path. The default value is
 *     **false**.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetRotatable(ArkUI_MotionPathOptions* options, const bool rotatable);

/**
 * @brief Obtains whether the component rotates along the motion path.
 *
 * @param options Pointer to {@link ArkUI_MotionPathOptions}.
 * @param rotatable Pointer to the variable used to receive the value of **rotatable**, which indicates whether the
 *     component rotates along the path. The value **true** means that the component rotates along the path, and
 *     **false** means that the component does not rotate along the path.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetRotatable(const ArkUI_MotionPathOptions* options, bool* rotatable);

/**
 * @brief Creates a shadow option object. When the object is no longer in use, call
 * {@link OH_ArkUI_ShadowOptions_Destroy} to destroy it.
 *
 * @return Pointer to the {@link OH_ArkUI_ShadowOptions} object.
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
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetRadius(OH_ArkUI_ShadowOptions* options, float radius);

/**
 * @brief Obtains the blur radius of the shadow options.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param radius Pointer to the variable used to receive the blur radius of the shadow, in vp.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetRadius(OH_ArkUI_ShadowOptions* options, float* radius);

/**
 * @brief Sets the shadow type for the shadow options.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param type Shadow type. For details, see {@link ArkUI_ShadowType}.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetType(OH_ArkUI_ShadowOptions* options, ArkUI_ShadowType type);

/**
 * @brief Obtains the shadow type of the shadow options.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param type Pointer to the variable used to receive the shadow type. For details, see {@link ArkUI_ShadowType}.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetType(OH_ArkUI_ShadowOptions* options, ArkUI_ShadowType* type);

/**
 * @brief Sets the shadow color for the shadow options.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param color Shadow color, in 0xARGB format.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetColor(OH_ArkUI_ShadowOptions* options, uint32_t color);

/**
 * @brief Obtains the shadow color of the shadow options.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param color Pointer to the variable used to receive the shadow color, in 0xARGB format.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetColor(OH_ArkUI_ShadowOptions* options, uint32_t* color);

/**
 * @brief Sets the offset of the shadow along the x-axis.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param offsetX Offset of the shadow along the x-axis, in vp.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetOffsetX(OH_ArkUI_ShadowOptions* options, float offsetX);

/**
 * @brief Obtains the offset of the shadow along the x-axis.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param offsetX Pointer to the variable used to receive the offset of the shadow along the x-axis, in vp.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetOffsetX(OH_ArkUI_ShadowOptions* options, float* offsetX);

/**
 * @brief Sets the offset of the shadow along the y-axis.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param offsetY Offset of the shadow along the y-axis, in vp.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetOffsetY(OH_ArkUI_ShadowOptions* options, float offsetY);

/**
 * @brief Obtains the offset of the shadow along the y-axis.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param offsetY Pointer to the variable used to receive the offset of the shadow along the y-axis, in vp.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetOffsetY(OH_ArkUI_ShadowOptions* options, float* offsetY);

/**
 * @brief Sets whether to fill the inside of the component with shadow.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param isFill Whether to fill the inside of the component with shadow. The value **true** means to fill the inside
 *     of the component with shadow, and **false** means not to fill the inside of the component with shadow. The
 *     default value is **false**.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetFill(OH_ArkUI_ShadowOptions* options, bool isFill);

/**
 * @brief Obtains whether to fill the inside of the component with shadow.
 *
 * @param options Pointer to the {@link OH_ArkUI_ShadowOptions} object.
 * @param isFill Pointer to the variable used to receive whether to fill the inside of the component with shadow. The
 *     value **true** means to fill the inside of the component with shadow, and **false** means not to fill the inside
 *     of the component with shadow.
 * @return Returns the result code.
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetFill(OH_ArkUI_ShadowOptions* options, bool* isFill);

/**
 * @brief Defines a matrix scaling object.
 *
 * @since 24
 */
typedef struct ArkUI_Matrix4ScaleOptions ArkUI_Matrix4ScaleOptions;

/**
 * @brief Creates a pointer to the scaling parameter object for matrix operations. In the newly created object, the
 * default scaling coefficients in the x, y, and z directions are 1. The default values of **centerX** and **centerY**
 * of the transformation center point are 0.
 *
 * @return Pointer to the new {@link ArkUI_Matrix4ScaleOptions} object.
 * @since 24
 */
ArkUI_Matrix4ScaleOptions* OH_ArkUI_Matrix4ScaleOptions_Create();

/**
 * @brief Disposes of the pointer to the scaling parameter object for matrix operations.
 *
 * @param options Pointer to the {@link ArkUI_Matrix4ScaleOptions} object to be destroyed.
 * @since 24
 */
void OH_ArkUI_Matrix4ScaleOptions_Dispose(ArkUI_Matrix4ScaleOptions* options);

/**
 * @brief Sets the scaling factor in the x direction of the scaling parameter object for matrix operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param scaleX Scaling factor in the x direction. The value range is (-∞, +∞).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetX(ArkUI_Matrix4ScaleOptions* options, const float scaleX);

/**
 * @brief Obtains the scaling factor in the x direction of the scaling parameter object for matrix operations. If the
 * value of x is not set, the default value of the scaling factor in the x direction is 1.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param scaleX Pointer to the scaling factor in the x direction.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetX(const ArkUI_Matrix4ScaleOptions* options, float* scaleX);

/**
 * @brief Sets the scaling factor in the y direction of the scaling parameter object for matrix operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param scaleY Scaling factor in the y direction. The value range is (-∞, +∞).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetY(ArkUI_Matrix4ScaleOptions* options, const float scaleY);

/**
 * @brief Obtains the scaling factor in the y direction of the scaling parameter object for matrix operations. If the
 * value of y is not set, the default value of the scaling factor in the y direction is 1.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param scaleY Pointer to the scaling factor in the y direction.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetY(const ArkUI_Matrix4ScaleOptions* options, float* scaleY);

/**
 * @brief Sets the scaling factor in the z direction of the scaling parameter object for matrix operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param scaleZ Scaling factor in the z direction. The value range is (-∞, +∞).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetZ(ArkUI_Matrix4ScaleOptions* options, const float scaleZ);

/**
 * @brief Obtains the scaling factor in the z direction of the scaling parameter object for matrix operations. If the
 * value of z is not set, the default value of the scaling factor in the z direction is 1.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param scaleZ Pointer to the scaling factor in the z direction.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetZ(const ArkUI_Matrix4ScaleOptions* options, float* scaleZ);

/**
 * @brief Sets the x coordinate of the transformation center point of the scaling parameter object for matrix
 * operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param centerX X-coordinate of the transformation center point. The value range is (-∞, +∞). **0** indicates that
 *     there is no x-axis offset based on the transformation center. The unit is px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetCenterX(ArkUI_Matrix4ScaleOptions* options, const float centerX);

/**
 * @brief Obtains the x coordinate of the transformation center point of the scaling parameter object for matrix
 * operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param centerX Pointer to the X-coordinate of the transformation center point. The unit is px. The default value is *
 *     **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetCenterX(const ArkUI_Matrix4ScaleOptions* options, float* centerX);

/**
 * @brief Sets the y coordinate of the transformation center point of the scaling parameter object for matrix
 * operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param centerY Y-coordinate of the transformation center point. The value range is (-∞, +∞). **0** indicates that
 *     there is no y-axis offset based on the transformation center. The unit is px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetCenterY(ArkUI_Matrix4ScaleOptions* options, const float centerY);

/**
 * @brief Obtains the y coordinate of the transformation center point of the scaling parameter object for matrix
 * operations.
 *
 * @param options Pointer to the scaling parameter object for matrix operations.
 * @param centerY Pointer to the Y-coordinate of the transformation center point. The unit is px. The default value is *
 *     **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetCenterY(const ArkUI_Matrix4ScaleOptions* options, float* centerY);

/**
 * @brief Defines a matrix rotation object.
 *
 * @since 24
 */
typedef struct ArkUI_Matrix4RotationOptions ArkUI_Matrix4RotationOptions;

/**
 * @brief Creates a pointer to the rotation parameter object for matrix operations. In the newly created object, the
 * default value of an x-axis offset (**centerX**) of a single matrix transformation center point relative to a
 * component transformation center point, the default value of a y-axis offset (**centerY**) of the single matrix
 * transformation center point relative to the component transformation center point, and the default value of a
 * rotation angle (**angle**) are 0. If none of the direction vectors in the x, y, and z directions is specified, the
 * value is equivalent to x=0, y=0, and z=1, indicating rotation around the z-axis. Once any of the direction vectors
 * in the x, y, and z directions is specified, the unspecified values are equivalent to 0.
 *
 * @return Pointer to the new {@link ArkUI_Matrix4RotationOptions} object.
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
 * @param x Value of the direction vector in the x direction. The value range is (-∞, +∞).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetX(ArkUI_Matrix4RotationOptions* options, const float x);

/**
 * @brief Obtains the direction vector in the x direction of the rotation parameter object for matrix operations. If
 * the value of x has never been set, the value is undefined. In this case, {@link ARKUI_ERROR_CODE_PARAM_INVALID} is
 * returned.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param x Pointer to the value of the direction vector in the x direction. If the value of x has never been set, the
 *     value is undefined.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetX(const ArkUI_Matrix4RotationOptions* options, float* x);

/**
 * @brief Sets the direction vector in the y direction of the rotation parameter object for matrix operations.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param y Value of the direction vector in the y direction. The value range is (-∞, +∞).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetY(ArkUI_Matrix4RotationOptions* options, const float y);

/**
 * @brief Obtains the direction vector in the y direction of the rotation parameter object for matrix operations. If
 * the value of y has never been set, the value is undefined. In this case, {@link ARKUI_ERROR_CODE_PARAM_INVALID} is
 * returned.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param y Pointer to the value of the direction vector in the y direction. If the value of y has never been set, the
 *     value is undefined.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetY(const ArkUI_Matrix4RotationOptions* options, float* y);

/**
 * @brief Sets the direction vector in the z direction of the rotation parameter object for matrix operations.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param z Value of the direction vector in the z direction. The value range is (-∞, +∞).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetZ(ArkUI_Matrix4RotationOptions* options, const float z);

/**
 * @brief Obtains the direction vector in the z direction of the rotation parameter object for matrix operations. If
 * the value of z has never been set, the value is undefined. In this case, {@link ARKUI_ERROR_CODE_PARAM_INVALID} is
 * returned.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param z Pointer to the value of the direction vector in the z direction. If the value of z has never been set, the
 *     value is undefined.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetZ(const ArkUI_Matrix4RotationOptions* options, float* z);

/**
 * @brief Sets the rotation angle in the rotation parameter object for matrix operations.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param angle Value of the rotation angle. The value range is (-∞, +∞). The unit is degree.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetAngle(ArkUI_Matrix4RotationOptions* options, const float angle);

/**
 * @brief Obtains the rotation angle in the rotation parameter object for matrix operations.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param angle Pointer to the value of the rotation angle. The unit is degree. If the angle has never been set, the
 *     default value is **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetAngle(const ArkUI_Matrix4RotationOptions* options, float* angle);

/**
 * @brief Sets the x-axis offset of a single matrix transformation center point relative to a component transformation
 * center point.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param centerX X-axis offset of a single matrix transformation center point relative to a component transformation
 *     center point. The value range is (-∞, +∞). **0** indicates that there is no x-axis offset based on the
 *     transformation center. The unit is px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetCenterX(ArkUI_Matrix4RotationOptions* options, const float centerX);

/**
 * @brief Obtains the x-axis offset of a single matrix transformation center point relative to a component
 * transformation center point.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param centerX Pointer to the x-axis offset of a single matrix transformation center point relative to a component
 *     transformation center point. The unit is px. If **centerX** has never been set, the default value is **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetCenterX(const ArkUI_Matrix4RotationOptions* options, float* centerX);

/**
 * @brief Sets the y-axis offset of a single matrix transformation center point relative to a component transformation
 * center point.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param centerY Y-axis offset of a single matrix transformation center point relative to a component transformation
 *     center point. The value range is (-∞, +∞). **0** indicates that there is no y-axis offset based on the
 *     transformation center. The unit is px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetCenterY(ArkUI_Matrix4RotationOptions* options, const float centerY);

/**
 * @brief Obtains the y-axis offset of a single matrix transformation center point relative to a component
 * transformation center point.
 *
 * @param options Pointer to the rotation parameter object for matrix operations.
 * @param centerY Pointer to the y-axis offset of a single matrix transformation center point relative to a component
 *     transformation center point. The unit is px. If **centerY** has never been set, the default value is **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetCenterY(const ArkUI_Matrix4RotationOptions* options, float* centerY);

/**
 * @brief Defines a matrix translation object.
 *
 * @since 24
 */
typedef struct ArkUI_Matrix4TranslationOptions ArkUI_Matrix4TranslationOptions;

/**
 * @brief Creates a pointer to a translation object for matrix operations. In the newly created object, the default
 * translation distances on the x, y, and z axes are 0.
 *
 * @return Pointer to the new {@link ArkUI_Matrix4TranslationOptions} object.
 * @since 24
 */
ArkUI_Matrix4TranslationOptions* OH_ArkUI_Matrix4TranslationOptions_Create();

/**
 * @brief Disposes of a pointer to a translation object for matrix operations.
 *
 * @param options Pointer to the {@link ArkUI_Matrix4TranslationOptions} object to be disposed.
 * @since 24
 */
void OH_ArkUI_Matrix4TranslationOptions_Dispose(ArkUI_Matrix4TranslationOptions* options);

/**
 * @brief Sets the translation value of a translation object on the x-axis for matrix operations.
 *
 * @param options Pointer to the translation parameter object for matrix operations.
 * @param x Translation value on the x-axis. The value range is (-∞, +∞). The unit is px. If the value of x has never
 *     been set, the default value is **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetX(ArkUI_Matrix4TranslationOptions* options, const float x);

/**
 * @brief Obtains the translation value of a translation object on the x-axis for matrix operations.
 *
 * @param options Pointer to the translation parameter object for matrix operations.
 * @param x Pointer to the translation value on the x-axis.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetX(const ArkUI_Matrix4TranslationOptions* options, float* x);

/**
 * @brief Sets the translation value of a translation object on the y-axis for matrix operations.
 *
 * @param options Pointer to the translation parameter object for matrix operations.
 * @param y Translation value on the y-axis. The value range is (-∞, +∞). The unit is px. If the value of y has never
 *     been set, the default value is **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetY(ArkUI_Matrix4TranslationOptions* options, const float y);

/**
 * @brief Obtains the translation value of a translation object on the y-axis for matrix operations.
 *
 * @param options Pointer to the translation parameter object for matrix operations.
 * @param y Pointer to the translation value on the y-axis.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetY(const ArkUI_Matrix4TranslationOptions* options, float* y);

/**
 * @brief Sets the translation value of a translation object on the z-axis for matrix operations.
 *
 * @param options Pointer to the translation parameter object for matrix operations.
 * @param z Translation value on the z-axis. The value range is (-∞, +∞). The unit is px. If the value of z has never
 *     been set, the default value is **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetZ(ArkUI_Matrix4TranslationOptions* options, const float z);

/**
 * @brief Obtains the translation value of a translation object on the z-axis for matrix operations.
 *
 * @param options Pointer to the translation parameter object for matrix operations.
 * @param z Pointer to the translation value on the z-axis.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
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
 *     to 16. This parameter cannot be set to a null pointer.
 * @return Pointer to the created fourth-order matrix object. If the **elements** pointer is a null pointer, a null
 *     value is returned.
 * @since 24
 */
ArkUI_Matrix4* OH_ArkUI_Matrix4_CreateByElements(const float* elements);

/**
 * @brief Disposes of a fourth-order matrix object.
 *
 * @param matrix Pointer to the fourth-order matrix object to be disposed.
 * @since 24
 */
void OH_ArkUI_Matrix4_Dispose(ArkUI_Matrix4* matrix);

/**
 * @brief Creates a copy of a fourth-order matrix object. It is used to perform operations on the same matrix to obtain
 *     different matrix objects.
 *
 * @param matrix Pointer to the original fourth-order matrix object.
 * @return Pointer to the created fourth-order matrix object.
 * @since 24
 */
ArkUI_Matrix4* OH_ArkUI_Matrix4_Copy(const ArkUI_Matrix4* matrix);

/**
 * @brief Performs an inverse matrix transformation on the input matrix.
 *
 * @param matrix Pointer to the fourth-order matrix object to be inverted.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the matrix is not invertible.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Invert(ArkUI_Matrix4* matrix);

/**
 * @brief Combines another matrix with the original matrix and stores the resulting matrix in **oriMatrix**. The
 *     resulting matrix is equivalent to first applying the transformation of **oriMatrix** and then applying the
 *     transformation of **anotherMatrix**. This function modifies the **oriMatrix** object.
 *
 * @param oriMatrix Pointer to the original fourth-order matrix object.
 * @param anotherMatrix Pointer to another matrix object to be combined.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Combine(ArkUI_Matrix4* oriMatrix, const ArkUI_Matrix4* anotherMatrix);

/**
 * @brief Applies a translation transformation to the original matrix to obtain the translated matrix. Each translation
 *     transformation is cumulative on the previous matrix. The input matrix object is modified after the
 *     transformation.
 *
 * @param matrix Pointer to the fourth-order matrix object to be translated.
 * @param translate Pointer to the translation object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Translate(ArkUI_Matrix4* matrix, const ArkUI_Matrix4TranslationOptions* translate);

/**
 * @brief Applies a scaling transformation to the original matrix to obtain the scaled matrix. Each scaling
 *     transformation is cumulative on the previous matrix. This function modifies the input matrix object.
 *
 * @param matrix Pointer to the fourth-order matrix object to be scaled.
 * @param scale Pointer to the scaling object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Scale(ArkUI_Matrix4* matrix, const ArkUI_Matrix4ScaleOptions* scale);

/**
 * @brief Applies a rotation transformation to the original matrix to obtain the rotated matrix. Each rotation
 *     transformation is cumulative on the previous matrix. This function modifies the input matrix object.
 *
 * @param matrix Pointer to the fourth-order matrix object to be rotated.
 * @param rotate Pointer to the rotation object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Rotate(ArkUI_Matrix4* matrix, const ArkUI_Matrix4RotationOptions* rotate);

/**
 * @brief Applies a skew transformation to the original matrix to obtain the skewed matrix. Each skew transformation is
 *     cumulative on the previous matrix. The input matrix object is modified after the transformation.
 *
 * @param matrix Pointer to the fourth-order matrix object to be skewed.
 * @param skewX Skew coefficient in the x direction.
 * @param skewY Skew coefficient in the y direction.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Skew(ArkUI_Matrix4* matrix, const float skewX, const float skewY);

/**
 * @brief Calculates the new coordinate position of a point after it is transformed by a matrix.
 *
 * @param matrix Pointer to the fourth-order matrix object.
 * @param oriPoint Pointer to the original coordinate point.
 * @param result Pointer to the result point. This parameter cannot be set to a null pointer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
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
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_SetPolyToPoly(ArkUI_Matrix4* matrix, const ArkUI_PointF* src, const ArkUI_PointF* dst, const uint32_t pointCount);

/**
 * @brief Obtains the 16 elements of the fourth-order matrix.
 *
 * @param matrix Pointer to the fourth-order matrix object.
 * @param result Pointer to an array that can hold 16 floating-point numbers. This parameter cannot be set to a null
 *     pointer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_GetElements(const ArkUI_Matrix4* matrix, float* result);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_TYPE_VISUAL_H
/** @} */

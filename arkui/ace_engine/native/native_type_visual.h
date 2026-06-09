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
 * @brief Defines the matrix4 object.
 *
 * @since 24
 */
typedef struct ArkUI_Matrix4 ArkUI_Matrix4;

/**
 * @brief Enumerates the shadow types.
 *
 * @since 12
 */
typedef enum {
    /** Color. */
    ARKUI_SHADOW_TYPE_COLOR = 0,
    /** Blur. */
    ARKUI_SHADOW_TYPE_BLUR
} ArkUI_ShadowType;

/**
 * @brief Enumerates the shadow styles.
 *
 * @since 12
 */
typedef enum {
    /** Mini shadow. */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_XS = 0,
    /** Little shadow. */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_SM,
    /** Medium shadow. */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_MD,
    /** Large shadow. */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_LG,
    /** Floating small shadow. */
    ARKUI_SHADOW_STYLE_OUTER_FLOATING_SM,
    /** Floating medium shadow. */
    ARKUI_SHADOW_STYLE_OUTER_FLOATING_MD,
} ArkUI_ShadowStyle;

/**
 * @brief Enumerates the animation curves.
 *
 * @since 12
 */
typedef enum {
    /** The animation speed keeps unchanged. */
    ARKUI_CURVE_LINEAR = 0,
    /** The animation starts slowly, accelerates, and then slows down towards the end. */
    ARKUI_CURVE_EASE,
    /** The animation starts at a low speed and then picks up speed until the end. */
    ARKUI_CURVE_EASE_IN,
    /** The animation ends at a low speed. */
    ARKUI_CURVE_EASE_OUT,
    /** The animation starts and ends at a low speed. */
    ARKUI_CURVE_EASE_IN_OUT,
    /** The animation uses the standard curve */
    ARKUI_CURVE_FAST_OUT_SLOW_IN,
    /** The animation uses the deceleration curve. */
    ARKUI_CURVE_LINEAR_OUT_SLOW_IN,
    /** The animation uses the acceleration curve. */
    ARKUI_CURVE_FAST_OUT_LINEAR_IN,
    /** The animation uses the extreme deceleration curve. */
    ARKUI_CURVE_EXTREME_DECELERATION,
    /** The animation uses the sharp curve. */
    ARKUI_CURVE_SHARP,
    /** The animation uses the rhythm curve. */
    ARKUI_CURVE_RHYTHM,
    /** The animation uses the smooth curve. */
    ARKUI_CURVE_SMOOTH,
    /** The animation uses the friction curve */
    ARKUI_CURVE_FRICTION,
} ArkUI_AnimationCurve;

/**
 * @brief Enumerates the animation playback modes.
 *
 * @since 12
 */
typedef enum {
    /** The animation is played forwards. */
    ARKUI_ANIMATION_PLAY_MODE_NORMAL = 0,
    /** The animation is played reversely. */
    ARKUI_ANIMATION_PLAY_MODE_REVERSE,
    /** The animation is played normally for an odd number of times (1, 3, 5...) and reversely for an even number
     *  of times (2, 4, 6...). */
    ARKUI_ANIMATION_PLAY_MODE_ALTERNATE,
    /** The animation is played reversely for an odd number of times (1, 3, 5...) and normally for an even number
     *  of times (2, 4, 6...). */
    ARKUI_ANIMATION_PLAY_MODE_ALTERNATE_REVERSE,
} ArkUI_AnimationPlayMode;

/**
 * @brief Enumerates the blur styles.
 *
 * @since 12
 */
typedef enum {
    /** Thin material. */
    ARKUI_BLUR_STYLE_THIN = 0,
    /** Regular material. */
    ARKUI_BLUR_STYLE_REGULAR,
    /** Thick material. */
    ARKUI_BLUR_STYLE_THICK,
    /** Material that creates the minimum depth of field effect. */
    ARKUI_BLUR_STYLE_BACKGROUND_THIN,
    /** Material that creates a medium shallow depth of field effect. */
    ARKUI_BLUR_STYLE_BACKGROUND_REGULAR,
    /** Material that creates a high shallow depth of field effect. */
    ARKUI_BLUR_STYLE_BACKGROUND_THICK,
    /** Material that creates the maximum depth of field effect. */
    ARKUI_BLUR_STYLE_BACKGROUND_ULTRA_THICK,
    /** No blur. */
    ARKUI_BLUR_STYLE_NONE,
    /** Component ultra-thin material. */
    ARKUI_BLUR_STYLE_COMPONENT_ULTRA_THIN,
    /** Component thin material. */
    ARKUI_BLUR_STYLE_COMPONENT_THIN,
    /** Component regular material. */
    ARKUI_BLUR_STYLE_COMPONENT_REGULAR,
    /** Component thick material. */
    ARKUI_BLUR_STYLE_COMPONENT_THICK,
    /** Component ultra-thick material. */
    ARKUI_BLUR_STYLE_COMPONENT_ULTRA_THICK,
} ArkUI_BlurStyle;

/**
 * @brief Enumerates the activation policies for the background blur effect.
 *
 * @since 19
 */
typedef enum {
    /** The blur effect changes according to the window's focus state;
     *  it is inactive when the window is not in focus and active when the window is in focus. */
    ARKUI_BLUR_STYLE_ACTIVE_POLICY_FOLLOWS_WINDOW_ACTIVE_STATE = 0,
    /** The blur effect is always active. */
    ARKUI_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_ACTIVE,
    /** The blur effect is always inactive. */
    ARKUI_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_INACTIVE,
} ArkUI_BlurStyleActivePolicy;

/**
 * @brief Enumerates the blend modes.
 *
 * @since 12
 */
typedef enum {
    /** The top image is superimposed on the bottom image without any blending. */
    ARKUI_BLEND_MODE_NONE = 0,
    /** The target pixels covered by the source pixels are erased by being turned to completely transparent. */
    ARKUI_BLEND_MODE_CLEAR,
    /** r = s: Only the source pixels are displayed. */
    ARKUI_BLEND_MODE_SRC,
    /** r = d: Only the target pixels are displayed. */
    ARKUI_BLEND_MODE_DST,
    /** r = s + (1 - sa) * d: The source pixels are blended based on opacity and cover the target pixels. */
    ARKUI_BLEND_MODE_SRC_OVER,
    /** r = d + (1 - da) * s: The target pixels are blended based on opacity and cover on the source pixels. */
    ARKUI_BLEND_MODE_DST_OVER,
    /** r = s * da: Only the part of the source pixels that overlap with the target pixels is displayed. */
    ARKUI_BLEND_MODE_SRC_IN,
    /** r = d * sa: Only the part of the target pixels that overlap with the source pixels is displayed. */
    ARKUI_BLEND_MODE_DST_IN,
    /** r = s * (1 - da): Only the part of the source pixels that do not overlap with the target pixels is displayed. */
    ARKUI_BLEND_MODE_SRC_OUT,
    /** r = d * (1 - sa): Only the part of the target pixels that do not overlap with the source pixels is displayed. */
    ARKUI_BLEND_MODE_DST_OUT,
    /** r = s * da + d * (1 - sa): The part of the source pixels that overlap with the target pixels is displayed and
     *  the part of the target pixels that do not overlap with the source pixels are displayed.
     */
    ARKUI_BLEND_MODE_SRC_ATOP,
    /** r = d * sa + s * (1 - da): The part of the target pixels that overlap with the source pixels and the part of
     *  the source pixels that do not overlap with the target pixels are displayed.
     */
    ARKUI_BLEND_MODE_DST_ATOP,
    /** r = s * (1 - da) + d * (1 - sa): Only the non-overlapping part between the source pixels and the target pixels
     * is displayed. */
    ARKUI_BLEND_MODE_XOR,
    /** r = min(s + d, 1): New pixels resulting from adding the source pixels to the target pixels are displayed. */
    ARKUI_BLEND_MODE_PLUS,
    /** r = s * d: New pixels resulting from multiplying the source pixels with the target pixels are displayed. */
    ARKUI_BLEND_MODE_MODULATE,
    /** r = s + d - s * d: Pixels are blended by adding the source pixels to the target pixels and subtracting the
     *  product of their multiplication. */
    ARKUI_BLEND_MODE_SCREEN,
    /** The MULTIPLY or SCREEN mode is used based on the target pixels. */
    ARKUI_BLEND_MODE_OVERLAY,
    /** rc = s + d - max(s * da, d * sa), ra = kSrcOver: When two colors overlap, whichever is darker is used. */
    ARKUI_BLEND_MODE_DARKEN,
    /** rc = s + d - min(s * da, d * sa), ra =
       kSrcOver: The final pixels are composed of the lightest values of pixels. */
    ARKUI_BLEND_MODE_LIGHTEN,
    /** The colors of the target pixels are lightened to reflect the source pixels. */
    ARKUI_BLEND_MODE_COLOR_DODGE,
    /** The colors of the target pixels are darkened to reflect the source pixels. */
    ARKUI_BLEND_MODE_COLOR_BURN,
    /** The MULTIPLY or SCREEN mode is used, depending on the source pixels. */
    ARKUI_BLEND_MODE_HARD_LIGHT,
    /** The LIGHTEN or DARKEN mode is used, depending on the source pixels. */
    ARKUI_BLEND_MODE_SOFT_LIGHT,
    /** rc = s + d - 2 * (min(s * da, d * sa)), ra =
       kSrcOver: The final pixel is the result of subtracting the darker of the two pixels (source and target) from
       the lighter one. */
    ARKUI_BLEND_MODE_DIFFERENCE,
    /** rc = s + d - two(s * d), ra = kSrcOver: The final pixel is similar to <b>DIFFERENCE</b>, but with less contrast.
     */
    ARKUI_BLEND_MODE_EXCLUSION,
    /** r = s * (1 - da) + d * (1 - sa) + s * d: The final pixel is the result of multiplying the source pixel
     *  by the target pixel.	 */
    ARKUI_BLEND_MODE_MULTIPLY,
    /** The resultant image is created with the luminance and saturation of the source image and the hue of the target
     *  image. */
    ARKUI_BLEND_MODE_HUE,
    /** The resultant image is created with the luminance and hue of the target image and the saturation of the source
     *  image. */
    ARKUI_BLEND_MODE_SATURATION,
    /** The resultant image is created with the saturation and hue of the source image and the luminance of the target
     *  image. */
    ARKUI_BLEND_MODE_COLOR,
    /** The resultant image is created with the saturation and hue of the target image and the luminance of the source
     *  image. */
    ARKUI_BLEND_MODE_LUMINOSITY,
} ArkUI_BlendMode;

/**
 * @brief Enumerates the foreground colors.
 *
 * @since 12
 */
typedef enum {
    /** The foreground colors are the inverse of the component background colors. */
    ARKUI_COLOR_STRATEGY_INVERT = 0,
    /** The shadow colors of the component are the average color obtained from the component background shadow area. */
    ARKUI_COLOR_STRATEGY_AVERAGE,
    /** The shadow colors of the component are the primary color obtained from the component background shadow area. */
    ARKUI_COLOR_STRATEGY_PRIMARY,
} ArkUI_ColorStrategy;

/**
 * @brief Enumerates the mask types.
 *
 * @since 12
 */
typedef enum {
    /** Rectangle. */
    ARKUI_MASK_TYPE_RECTANGLE = 0,
    /** Circle. */
    ARKUI_MASK_TYPE_CIRCLE,
    /** Ellipse. */
    ARKUI_MASK_TYPE_ELLIPSE,
    /** Path. */
    ARKUI_MASK_TYPE_PATH,
    /** Progress indicator. */
    ARKUI_MASK_TYPE_PROGRESS,
} ArkUI_MaskType;

/**
 * @brief Enumerates the clipping region types.
 *
 * @since 12
 */
typedef enum {
    /** Rectangle. */
    ARKUI_CLIP_TYPE_RECTANGLE = 0,
    /** Circle. */
    ARKUI_CLIP_TYPE_CIRCLE,
    /** Ellipse. */
    ARKUI_CLIP_TYPE_ELLIPSE,
    /** Path. */
    ARKUI_CLIP_TYPE_PATH,
} ArkUI_ClipType;

/**
 * @brief Enumerates the custom shapes.
 *
 * @since 12
 */
typedef enum {
    /** Rectangle. */
    ARKUI_SHAPE_TYPE_RECTANGLE = 0,
    /** Circle. */
    ARKUI_SHAPE_TYPE_CIRCLE,
    /** Ellipse. */
    ARKUI_SHAPE_TYPE_ELLIPSE,
    /** Path. */
    ARKUI_SHAPE_TYPE_PATH,
} ArkUI_ShapeType;

/**
 * @brief Enumerates the gradient directions.
 *
 * @since 12
 */
typedef enum {
    /** From right to left. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT = 0,
    /** From bottom to top. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_TOP,
    /** From left to right. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_RIGHT,
    /** From top to bottom. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_BOTTOM,
    /** From lower right to upper left. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT_TOP,
    /** From upper right to lower left. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT_BOTTOM,
    /** From lower left to upper right. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_RIGHT_TOP,
    /** From upper left to lower right. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_RIGHT_BOTTOM,
    /** No gradient. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_NONE,
    /** Custom direction. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM,
} ArkUI_LinearGradientDirection;

/**
 * @brief Enumerates the slide-in and slide-out positions of the component from the screen edge during transition.
 *
 * @since 12
 */
typedef enum {
    /** Top edge of the window. */
    ARKUI_TRANSITION_EDGE_TOP = 0,
    /** Bottom edge of the window. */
    ARKUI_TRANSITION_EDGE_BOTTOM,
    /** Left edge of the window. */
    ARKUI_TRANSITION_EDGE_START,
    /** Right edge of the window. */
    ARKUI_TRANSITION_EDGE_END,
} ArkUI_TransitionEdge;

/**
 * @brief Defines how the specified blend mode is applied.
 *
 * @since 12
 */
typedef enum {
    /** The content of the view is blended in sequence on the target image. */
    BLEND_APPLY_TYPE_FAST = 0,
    /** The content of the component and its child components are drawn on the offscreen canvas, and then blended with
     *  the existing content on the canvas. */
    BLEND_APPLY_TYPE_OFFSCREEN,
} ArkUI_BlendApplyType;

/**
 * @brief Enumerates the animation onFinish callback types.
 *
 * @since 12
 */
typedef enum {
    /** The callback is invoked when the entire animation is removed once it has finished. */
    ARKUI_FINISH_CALLBACK_REMOVED = 0,
    /** The callback is invoked when the animation logically enters the falling state, though it may still be in its
      * long tail state. */
    ARKUI_FINISH_CALLBACK_LOGICALLY,
} ArkUI_FinishCallbackType;

/**
 * @brief Enumerates the render fit.
 *
 * @since 12
 */
typedef enum {
    /** Maintains the content size of the animation's final state,
      * and the content is always centered with the component.*/
    ARKUI_RENDER_FIT_CENTER = 0,
    /** Maintains the content size of the animation's final state,
      * and the content is always aligned with the top center of the component. */
    ARKUI_RENDER_FIT_TOP,
    /** Maintains the content size of the animation's final state,
      * and the content is always aligned with the bottom center of the component. */
    ARKUI_RENDER_FIT_BOTTOM,
    /** Maintains the content size of the animation's final state,
      * and the content is always aligned to the left of the component. */
    ARKUI_RENDER_FIT_LEFT,
    /** Maintains the content size of the animation's final state,
      * and the content is always right-aligned with the component. */
    ARKUI_RENDER_FIT_RIGHT,
    /** Maintains the content size of the animation's final state,
      * and the content is always aligned with the top left corner of the component. */
    ARKUI_RENDER_FIT_TOP_LEFT,
    /** Keep the content size of the animation final state,
      * and the content is always aligned with the upper right corner of the component. */
    ARKUI_RENDER_FIT_TOP_RIGHT,
    /** Keep the content size of the animation final state,
      * and the content always aligns with the lower-left corner of the component. */
    ARKUI_RENDER_FIT_BOTTOM_LEFT,
    /** Keep the content size of the animation final state,
      *and the content always aligns with the lower-right corner of the component. */
    ARKUI_RENDER_FIT_BOTTOM_RIGHT,
    /** The aspect ratio of the animation's final state content is not considered,
      *and the content is always scaled to the size of the component. */
    ARKUI_RENDER_FIT_RESIZE_FILL,
    /** Reduce or enlarge the aspect ratio of the animation final state content,
      * so that the content is fully displayed in the component,
      * and keep the center aligned with the component. */
    ARKUI_RENDER_FIT_RESIZE_CONTAIN,
    /** Keep the aspect ratio of the animation final state content to reduce or enlarge,
      * so that the content is fully displayed in the component.
      * When there is left over in the broad direction of the component,
      * the content is aligned to the left of the component,
      * and when there is left over in the high direction of the component,
      * the content is aligned to the top of the component. */
    ARKUI_RENDER_FIT_RESIZE_CONTAIN_TOP_LEFT,
    /** Keep the aspect ratio of the animation final state content to reduce or enlarge,
      * so that the content is fully displayed in the component.
      * When there is left in the wide direction of the component,
      * the content is aligned with the component on the right.
      * When there is left in the high direction of the component,
      * the content is aligned with the component on the bottom. */
    ARKUI_RENDER_FIT_RESIZE_CONTAIN_BOTTOM_RIGHT,
    /** Keep the aspect ratio of the animation final state content reduced or enlarged,
      * so that both sides of the content are greater than or equal to both sides of the component,
      * and keep the center aligned with the component to display the middle part of the content. */
    ARKUI_RENDER_FIT_RESIZE_COVER,
    /** Keep the aspect ratio of the final content of the animation reduced or enlarged
      * so that both sides of the content are exactly greater than or equal to both sides of the component.
      * When the content width is left, the content is aligned to the left of the component,
      * and the left portion of the content is displayed. When the content is left in the high direction,
      * the content and the component remain top aligned, showing the top side of the content. */
    ARKUI_RENDER_FIT_RESIZE_COVER_TOP_LEFT,
    /** Keep the aspect ratio of the final content of the animation reduced or enlarged so
      * that both sides of the content are exactly greater than or equal to both sides of the component.
      * When the content width is left, the content and the component remain right aligned,
      * and the right part of the content is displayed. When the content is left in the high direction,
      * the content and the component remain aligned at the bottom,
      * and the bottom part of the content is displayed. */
    ARKUI_RENDER_FIT_RESIZE_COVER_BOTTOM_RIGHT
} ArkUI_RenderFit;

/**
 * @brief Defines the status before and after execution of the animation in the current playback direction.
 *
 * @since 12
*/
typedef enum {
    /** Before execution, the animation does not apply any styles to the target component.
     * After execution, the animation restores the target component to its default state. */
    ARKUI_ANIMATION_FILL_MODE_NONE,
    /** The target component retains the state set by the last keyframe encountered
     * during execution of the animation. */
    ARKUI_ANIMATION_FILL_MODE_FORWARDS,
    /** The animation applies the values defined in the first relevant keyframe once it is applied to
     * the target component, and retains the values during the period set by delay. */
    ARKUI_ANIMATION_FILL_MODE_BACKWARDS,
    /** The animation follows the rules for both Forwards and Backwards,
     * extending the animation attributes in both directions. */
    ARKUI_ANIMATION_FILL_MODE_BOTH,
} ArkUI_AnimationFillMode;

/**
 * @brief Enumerates the animation playback modes.
 *
 * @since 12
 */
typedef enum {
    /** The animation plays in forward loop mode. */
    ARKUI_ANIMATION_DIRECTION_NORMAL = 0,
    /** The animation plays in reverse loop mode. */
    ARKUI_ANIMATION_DIRECTION_REVERSE,
    /** The animation plays in alternating loop mode. When the animation is played for an odd number of times, the
     *  playback is in forward direction. When the animation is played for an even number of times, the playback is in
     *  reverse direction. */
    ARKUI_ANIMATION_DIRECTION_ALTERNATE,
    /** The animation plays in reverse alternating loop mode. When the animation is played for an odd number of times,
     *  the playback is in reverse direction. When the animation is played for an even number of times, the playback is
     *  in forward direction. */
    ARKUI_ANIMATION_DIRECTION_ALTERNATE_REVERSE,
} ArkUI_AnimationDirection;

/**
 * @brief Defines the translation options for component transition.
 *
 * @since 12
 */
typedef struct {
    /** Translation distance along the x-axis. */
    float x;
    /** Translation distance along the y-axis. */
    float y;
    /** Translation distance along the z-axis. */
    float z;
} ArkUI_TranslationOptions;

/**
 * @brief Defines the scaling options for component transition.
 *
 * @since 12
 */
typedef struct {
    /** Scale ratio along the x-axis. */
    float x;
    /** Scale ratio along the y-axis. */
    float y;
    /** Scale factor along the z-axis (not effective for the current 2D graphics). */
    float z;
    /** X coordinate of the center point. */
    float centerX;
    /** Y coordinate of the center point. */
    float centerY;
} ArkUI_ScaleOptions;

/**
 * @brief Defines the rotation options for component transition.
 *
 * @since 12
 */
typedef struct {
    /** X-component of the rotation vector. */
    float x;
    /** Y-component of the rotation vector. */
    float y;
    /** Z-component of the rotation vector. */
    float z;
    /** Rotation angle. */
    float angle;
    /** X coordinate of the center point. */
    float centerX;
    /** Y coordinate of the center point. */
    float centerY;
    /** Z-axis anchor, that is, the z-component of the 3D rotation center point. */
    float centerZ;
    /** Distance from the user to the z=0 plane. */
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
 * @brief Create an object of the motion path options for path animation.
 *        In the newly created ArkUI_MotionPathOptions, the "path" value is an empty string, the "from" value is 0,
 *        the "to" value is 1, and the "rotatable" value is false.
 *
 * @return A pointer to the ArkUI_MotionPathOptions.
 * @since 23
 */
ArkUI_MotionPathOptions* OH_ArkUI_MotionPathOptions_Create();

/**
 * @brief Dispose the ArkUI_MotionPathOptions object.
 *
 * @param options Pointer to the ArkUI_MotionPathOptions object to be disposed.
 * @since 23
 */
void OH_ArkUI_MotionPathOptions_Dispose(ArkUI_MotionPathOptions* options);

/**
 * @brief Sets the the motion path for the animation using an SVG path string. The path supports using "start" and
 *        "end" as placeholders for the starting and ending points, for example:
 *        "Mstart.x start.y L50 50 Lend.x end.y Z". Refer to the SVG path format for the path string.
 *        When set to an empty string, it is equivalent to not setting a path animation.
 *
 * @param options Pointer to the ArkUI_MotionPathOptions object.
 * @param svgPath The motion path for the path animation.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetPath(ArkUI_MotionPathOptions* options, const char* svgPath);

/**
 * @brief Gets the motion path string in the ArkUI_MotionPathOptions object.
 *
 * @param options Pointer to the ArkUI_MotionPathOptions object.
 * @param svgPathBuffer Buffer pointer to the motion path string.
 * @param bufferSize The buffer size of the svgPathBuffer parameter.
 * @param writeLength Indicates the string length actually written to the buffer
 *                    when returning {@link ARKUI_ERROR_CODE_NO_ERROR}.
 *                    Indicates the minimum buffer size that can accommodate the target
 *                    when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *         Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the buffer size is less than the minimum buffer size.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetPath(const ArkUI_MotionPathOptions* options, char* svgPathBuffer,
    const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Sets the starting progress in the ArkUI_MotionPathOptions. Progress refers to the ratio of the length of the
 *        path that has been traveled to the total length of the entire path. The value range is [0.0, 1.0], and the
 *        "from" value should be less than or equal to the "to" value; otherwise, an ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE
 *        error code will be returned.
 *
 * @param options Pointer to the ArkUI_MotionPathOptions object.
 * @param from The starting progress in the ArkUI_MotionPathOptions.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the "from" value is out of range or the "from" value
 *                 is greater than the "to" value.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetFrom(ArkUI_MotionPathOptions* options, const float from);

/**
 * @brief Gets the starting progress in the ArkUI_MotionPathOptions object.
 *
 * @param options Pointer to the ArkUI_MotionPathOptions object.
 * @param from The starting progress in the ArkUI_MotionPathOptions.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetFrom(const ArkUI_MotionPathOptions* options, float* from);

/**
 * @brief Sets the endpoint progress in the ArkUI_MotionPathOptions. Progress refers to the ratio of the length of the
 *        path that has been traveled to the total length of the entire path. The value range is [0.0, 1.0], and the
 *        "from" value should be less than or equal to the "to" value; otherwise, an ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE
 *        error code will be returned.
 *
 * @param options Pointer to the ArkUI_MotionPathOptions object.
 * @param to The endpoint progress in the ArkUI_MotionPathOptions.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the "to" value is out of range or the "to" value
 *                 is less than the "from" value.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetTo(ArkUI_MotionPathOptions* options, const float to);

/**
 * @brief Gets the endpoint progress in the ArkUI_MotionPathOptions object.
 *
 * @param options Pointer to the ArkUI_MotionPathOptions object.
 * @param to The endpoint progress in the ArkUI_MotionPathOptions.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetTo(const ArkUI_MotionPathOptions* options, float* to);

/**
 * @brief Sets the rotatable parameter in the ArkUI_MotionPathOptions. It indicates whether to rotate along the path.
 *        True means rotating along the path, while false means not rotating along the path.
 *
 * @param options Pointer to the ArkUI_MotionPathOptions object.
 * @param rotatable The rotatable parameter in the ArkUI_MotionPathOptions.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetRotatable(ArkUI_MotionPathOptions* options, const bool rotatable);

/**
 * @brief Gets the rotatable parameter in the ArkUI_MotionPathOptions.
 *
 * @param options Pointer to the ArkUI_MotionPathOptions object.
 * @param rotatable The rotatable parameter in the ArkUI_MotionPathOptions.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetRotatable(const ArkUI_MotionPathOptions* options, bool* rotatable);

/**
 * @brief Create a shadow options object.
 * When the object is no longer in use, invoke {@link OH_ArkUI_ShadowOptions_Destroy} to destroy it.
 *
 * @return A pointer to the shadow options object.
 * @since 24
 */
OH_ArkUI_ShadowOptions* OH_ArkUI_ShadowOptions_Create();

/**
 * @brief Destroys the shadow options object.
 *
 * @param options Pointer to the object to be destroyed.
 * @since 24
 */
void OH_ArkUI_ShadowOptions_Destroy(OH_ArkUI_ShadowOptions* options);

/**
 * @brief Sets blur radius of the shadow options.
 *
 * @param options shadow options.
 * @param radius blur radius of the shadow.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetRadius(OH_ArkUI_ShadowOptions* options, float radius);

/**
 * @brief Gets blur radius of the shadow options.
 *
 * @param options shadow options.
 * @param radius blur radius of the shadow.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetRadius(OH_ArkUI_ShadowOptions* options, float* radius);

/**
 * @brief Set shadow type of the shadow options.
 *
 * @param options shadow options.
 * @param type shadow type.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetType(OH_ArkUI_ShadowOptions* options, ArkUI_ShadowType type);

/**
 * @brief Get shadow type of the shadow options.
 *
 * @param options shadow options.
 * @param type shadow type.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetType(OH_ArkUI_ShadowOptions* options, ArkUI_ShadowType* type);

/**
 * @brief Set shadow color of the shadow options.
 *
 * @param options shadow options.
 * @param color shadow color.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetColor(OH_ArkUI_ShadowOptions* options, uint32_t color);

/**
 * @brief Get shadow color of the shadow options.
 *
 * @param options shadow options.
 * @param color shadow color.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetColor(OH_ArkUI_ShadowOptions* options, uint32_t* color);

/**
 * @brief Set offset of the shadow along the x-axis.
 *
 * @param options shadow options.
 * @param offsetX offset of the shadow along the x-axis.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetOffsetX(OH_ArkUI_ShadowOptions* options, float offsetX);

/**
 * @brief Get offset of the shadow along the x-axis.
 *
 * @param options shadow options.
 * @param offsetX offset of the shadow along the x-axis.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetOffsetX(OH_ArkUI_ShadowOptions* options, float* offsetX);

/**
 * @brief Set offset of the shadow along the y-axis.
 *
 * @param options shadow options.
 * @param offsetY offset of the shadow along the y-axis.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetOffsetY(OH_ArkUI_ShadowOptions* options, float offsetY);

/**
 * @brief Get offset of the shadow along the y-axis.
 *
 * @param options shadow options.
 * @param offsetY offset of the shadow along the y-axis.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetOffsetY(OH_ArkUI_ShadowOptions* options, float* offsetY);

/**
 * @brief Set whether to fill the inside of the component with shadow.
 *
 * @param options shadow options.
 * @param isFill whether to fill the inside of the component with shadow.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetFill(OH_ArkUI_ShadowOptions* options, bool isFill);

/**
 * @brief Get whether to fill the inside of the component with shadow.
 *
 * @param options shadow options.
 * @param isFill whether to fill the inside of the component with shadow.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetFill(OH_ArkUI_ShadowOptions* options, bool* isFill);

/**
 * @brief Defines the scale options for matrix scaling.
 *
 * @since 24
 */
typedef struct ArkUI_Matrix4ScaleOptions ArkUI_Matrix4ScaleOptions;

/**
 * @brief Create an object of ArkUI_Matrix4ScaleOptions.
 *        In the newly created options, the default values for the scaling coefficients in the x, y and z directions
 *        are 1, and the default values for centerX, centerY are 0.
 *
 * @return Returns a pointer to the newly created ArkUI_Matrix4ScaleOptions.
 * @since 24
 */
ArkUI_Matrix4ScaleOptions* OH_ArkUI_Matrix4ScaleOptions_Create();

/**
 * @brief Disposes the ArkUI_Matrix4ScaleOptions object.
 *
 * @param options Pointer to the ArkUI_Matrix4ScaleOptions instance to be destroyed.
 * @since 24
 */
void OH_ArkUI_Matrix4ScaleOptions_Dispose(ArkUI_Matrix4ScaleOptions* options);

/**
 * @brief Set the scaling factor in the x direction in ArkUI_Matrix4ScaleOptions.
 *
 * @param options Pointer to the ArkUI_Matrix4ScaleOptions object.
 * @param scaleX The scaling factor in the x direction. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetX(ArkUI_Matrix4ScaleOptions* options, const float scaleX);

/**
 * @brief Get the scaling factor in the x direction in ArkUI_Matrix4ScaleOptions.
 *        If the value of x is never set, its default value is 1.
 *
 * @param options Pointer to the ArkUI_Matrix4ScaleOptions object.
 * @param scaleX The scaling factor in the x direction.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetX(const ArkUI_Matrix4ScaleOptions* options, float* scaleX);

/**
 * @brief Set the scaling factor in the y direction in ArkUI_Matrix4ScaleOptions.
 *
 * @param options Pointer to the ArkUI_Matrix4ScaleOptions object.
 * @param scaleY The scaling factor in the y direction. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetY(ArkUI_Matrix4ScaleOptions* options, const float scaleY);

/**
 * @brief Get the scaling factor in the y direction in ArkUI_Matrix4ScaleOptions.
 *        If the value of y is never set, its default value is 1.
 *
 * @param options Pointer to the ArkUI_Matrix4ScaleOptions object.
 * @param scaleY The scaling factor in the y direction.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetY(const ArkUI_Matrix4ScaleOptions* options, float* scaleY);

/**
 * @brief Set the scaling factor in the z direction in ArkUI_Matrix4ScaleOptions.
 *
 * @param options Pointer to the ArkUI_Matrix4ScaleOptions object.
 * @param scaleZ The scaling factor in the z direction. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetZ(ArkUI_Matrix4ScaleOptions* options, const float scaleZ);

/**
 * @brief Get the scaling factor in the z direction in ArkUI_Matrix4ScaleOptions.
 *        If the value of z is never set, its default value is 1.
 *
 * @param options Pointer to the ArkUI_Matrix4ScaleOptions object.
 * @param scaleZ The scaling factor in the z direction.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetZ(const ArkUI_Matrix4ScaleOptions* options, float* scaleZ);

/**
 * @brief Set x offset relative to the transformation center. 0 means no additional x-direction offset from the
 *        transformation center. The unit is px.
 *
 * @param options Pointer to the ArkUI_Matrix4ScaleOptions object.
 * @param centerX The x offset relative to the transformation center. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetCenterX(ArkUI_Matrix4ScaleOptions* options, const float centerX);

/**
 * @brief Get the value of centerX from the options, which represents the x-direction offset relative to the
 *        transformation center. The unit is px. If the value of centerX is never set, its default value is 0.
 *
 * @param options Pointer to the ArkUI_Matrix4ScaleOptions object.
 * @param centerX The x-direction offset relative to the transformation center.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetCenterX(const ArkUI_Matrix4ScaleOptions* options, float* centerX);

/**
 * @brief Set y offset relative to the transformation center. 0 means no additional y-direction offset from the
 *        transformation center. The unit is px.
 *
 * @param options Pointer to the ArkUI_Matrix4ScaleOptions object.
 * @param centerY The y offset relative to the transformation center. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetCenterY(ArkUI_Matrix4ScaleOptions* options, const float centerY);

/**
 * @brief Get the value of centerY from the options, which represents the y-direction offset relative to the
 *        transformation center. The unit is px. If the value of centerY is never set, its default value is 0.
 *
 * @param options Pointer to the ArkUI_Matrix4ScaleOptions object.
 * @param centerY The y-direction offset relative to the transformation center.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetCenterY(const ArkUI_Matrix4ScaleOptions* options, float* centerY);

/**
 * @brief Defines the rotation options for matrix rotating.
 *
 * @since 24
 */
typedef struct ArkUI_Matrix4RotationOptions ArkUI_Matrix4RotationOptions;

/**
 * @brief Create an object of ArkUI_Matrix4RotationOptions.
 *        In the newly created options, the x, y, and z values in the direction vector specifying the rotation axis
 *        are undetermined; The default values for centerX, centerY are 0; The default value for angle is 0.
 *        If none of x, y, z are specified, it is equivalent to x=0, y=0, z=1, which means rotation around the z-axis.
 *        Once any one of x, y, z is specified, the remaining unspecified values are equivalent to 0.
 *
 * @return Returns a pointer to the newly created ArkUI_Matrix4RotationOptions.
 * @since 24
 */
ArkUI_Matrix4RotationOptions* OH_ArkUI_Matrix4RotationOptions_Create();

/**
 * @brief Disposes the ArkUI_Matrix4RotationOptions object.
 *
 * @param options Pointer to the ArkUI_Matrix4RotationOptions instance to be destroyed.
 * @since 24
 */
void OH_ArkUI_Matrix4RotationOptions_Dispose(ArkUI_Matrix4RotationOptions* options);

/**
 * @brief Set the value of the direction vector for the x-axis direction in ArkUI_Matrix4RotationOptions.
 *
 * @param options Pointer to the ArkUI_Matrix4RotationOptions object.
 * @param x The value of the direction vector for the x-axis direction. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetX(ArkUI_Matrix4RotationOptions* options, const float x);

/**
 * @brief Get the value of the direction vector for the x-axis direction in ArkUI_Matrix4RotationOptions.
 *        If the value of x is never set, its value will be undefined, so the function will return
 *        ARKUI_ERROR_CODE_PARAM_INVALID.
 *
 * @param options Pointer to the ArkUI_Matrix4RotationOptions object.
 * @param x The value of the direction vector for the x-axis direction.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetX(const ArkUI_Matrix4RotationOptions* options, float* x);

/**
 * @brief Set the value of the direction vector for the y-axis direction in ArkUI_Matrix4RotationOptions.
 *
 * @param options Pointer to the ArkUI_Matrix4RotationOptions object.
 * @param y The value of the direction vector for the y-axis direction. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetY(ArkUI_Matrix4RotationOptions* options, const float y);

/**
 * @brief Get the value of the direction vector for the y-axis direction in ArkUI_Matrix4RotationOptions.
 *        If the value of y is never set, its value will be undefined, so the function will return
 *        ARKUI_ERROR_CODE_PARAM_INVALID.
 *
 * @param options Pointer to the ArkUI_Matrix4RotationOptions object.
 * @param y The value of the direction vector for the y-axis direction.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetY(const ArkUI_Matrix4RotationOptions* options, float* y);

/**
 * @brief Set the value of the direction vector for the z-axis direction in ArkUI_Matrix4RotationOptions.
 *
 * @param options Pointer to the ArkUI_Matrix4RotationOptions object.
 * @param z The value of the direction vector for the z-axis direction. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetZ(ArkUI_Matrix4RotationOptions* options, const float z);

/**
 * @brief Get the value of the direction vector for the z-axis direction in ArkUI_Matrix4RotationOptions.
 *        If the value of z is never set, its value will be undefined, so the function will return
 *        ARKUI_ERROR_CODE_PARAM_INVALID.
 *
 * @param options Pointer to the ArkUI_Matrix4RotationOptions object.
 * @param z The value of the direction vector for the z-axis direction.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetZ(const ArkUI_Matrix4RotationOptions* options, float* z);

/**
 * @brief Set the value of the rotation angle in ArkUI_Matrix4RotationOptions. The unit is degree.
 *
 * @param options Pointer to the ArkUI_Matrix4RotationOptions object.
 * @param angle The value of the rotation angle in ArkUI_Matrix4RotationOptions. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetAngle(ArkUI_Matrix4RotationOptions* options, const float angle);

/**
 * @brief Get the value of the rotation angle in ArkUI_Matrix4RotationOptions. The unit is degree.
 *        If the value of angle is never set, its default value is 0.
 *
 * @param options Pointer to the ArkUI_Matrix4RotationOptions object.
 * @param angle The value of the rotation angle in ArkUI_Matrix4RotationOptions.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetAngle(const ArkUI_Matrix4RotationOptions* options, float* angle);

/**
 * @brief Set x offset relative to the transformation center. 0 means no additional x-direction offset from the
 *        transformation center. The unit is px.
 *
 * @param options Pointer to the ArkUI_Matrix4RotationOptions object.
 * @param centerX The x offset relative to the transformation center. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetCenterX(ArkUI_Matrix4RotationOptions* options, const float centerX);

/**
 * @brief Get the value of centerX from the options, which represents the x-direction offset relative to the
 *        transformation center. The unit is px. If the value of centerX is never set, its default value is 0.
 *
 * @param options Pointer to the ArkUI_Matrix4RotationOptions object.
 * @param centerX The x-direction offset relative to the transformation center.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetCenterX(const ArkUI_Matrix4RotationOptions* options, float* centerX);

/**
 * @brief Set y offset relative to the transformation center. 0 means no additional y-direction offset from the
 *        transformation center. The unit is px.
 *
 * @param options Pointer to the ArkUI_Matrix4RotationOptions object.
 * @param centerY The y offset relative to the transformation center. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetCenterY(ArkUI_Matrix4RotationOptions* options, const float centerY);

/**
 * @brief Get the value of centerY from the options, which represents the y-direction offset relative to the
 *        transformation center. The unit is px. If the value of centerY is never set, its default value is 0.
 *
 * @param options Pointer to the ArkUI_Matrix4RotationOptions object.
 * @param centerY The y-direction offset relative to the transformation center.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetCenterY(const ArkUI_Matrix4RotationOptions* options, float* centerY);

/**
 * @brief Defines the translation options for matrix translating.
 *
 * @since 24
 */
typedef struct ArkUI_Matrix4TranslationOptions ArkUI_Matrix4TranslationOptions;

/**
 * @brief Create an object of ArkUI_Matrix4TranslationOptions.
 *        In the newly created options, the default values for x, y and z are 0.
 *
 * @return Returns a pointer to the newly created ArkUI_Matrix4TranslationOptions.
 * @since 24
 */
ArkUI_Matrix4TranslationOptions* OH_ArkUI_Matrix4TranslationOptions_Create();

/**
 * @brief Disposes the ArkUI_Matrix4TranslationOptions object.
 *
 * @param options Pointer to the ArkUI_Matrix4TranslationOptions instance to be destroyed.
 * @since 24
 */
void OH_ArkUI_Matrix4TranslationOptions_Dispose(ArkUI_Matrix4TranslationOptions* options);

/**
 * @brief Set the translation value in the x-axis direction. The unit is px.
 *        If the value of x is never set, its default value is 0.
 *
 * @param options Pointer to the ArkUI_Matrix4TranslationOptions object.
 * @param x The translation value in the x-axis direction. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetX(ArkUI_Matrix4TranslationOptions* options, const float x);

/**
 * @brief Get the translation value in the x-axis direction from ArkUI_Matrix4TranslationOptions.
 *
 * @param options Pointer to the ArkUI_Matrix4TranslationOptions object.
 * @param x The translation value in the x-axis direction.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetX(const ArkUI_Matrix4TranslationOptions* options, float* x);

/**
 * @brief Set the translation value in the y-axis direction. The unit is px.
 *        If the value of y is never set, its default value is 0.
 *
 * @param options Pointer to the ArkUI_Matrix4TranslationOptions object.
 * @param y The translation value in the y-axis direction. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetY(ArkUI_Matrix4TranslationOptions* options, const float y);

/**
 * @brief Get the translation value in the y-axis direction from ArkUI_Matrix4TranslationOptions.
 *
 * @param options Pointer to the ArkUI_Matrix4TranslationOptions object.
 * @param y The translation value in the y-axis direction.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetY(const ArkUI_Matrix4TranslationOptions* options, float* y);

/**
 * @brief Set the translation value in the z-axis direction. The unit is px.
 *        If the value of z is never set, its default value is 0.
 *
 * @param options Pointer to the ArkUI_Matrix4TranslationOptions object.
 * @param z The translation value in the z-axis direction. Value range: (-∞, +∞).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetZ(ArkUI_Matrix4TranslationOptions* options, const float z);

/**
 * @brief Get the translation value in the z-axis direction from ArkUI_Matrix4TranslationOptions.
 *
 * @param options Pointer to the ArkUI_Matrix4TranslationOptions object.
 * @param z The translation value in the z-axis direction.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetZ(const ArkUI_Matrix4TranslationOptions* options, float* z);

/**
 * @brief Create an identity matrix4 object.
 *
 * @return Returns the created identity matrix4 object.
 * @since 24
 */
ArkUI_Matrix4* OH_ArkUI_Matrix4_CreateIdentity();

/**
 * @brief Specify each element of the matrix to create a matrix4 object.
 *
 * @param elements Pointer to the array of expected matrix element data. The length of array should be greater than
 *                 or equal to 16. The parameter must not be null.
 * @return Returns the newly created matrix4 object.
 *         If the pointer of elements is null, the function will return null.
 * @since 24
 */
ArkUI_Matrix4* OH_ArkUI_Matrix4_CreateByElements(const float* elements);

/**
 * @brief Disposes a matrix4 object.
 *
 * @param matrix Pointer to the matrix4 object to be disposed.
 * @since 24
 */
void OH_ArkUI_Matrix4_Dispose(ArkUI_Matrix4* matrix);

/**
 * @brief Create a copy of the matrix4 object.
 *
 * @param matrix Pointer to the original matrix4 object.
 * @return Returns the newly created matrix4 object.
 * @since 24
 */
ArkUI_Matrix4* OH_ArkUI_Matrix4_Copy(const ArkUI_Matrix4* matrix);

/**
 * @brief Perform an inverse matrix transformation on the input matrix.
 *        If the matrix is invertible, this function will modify the input matrix; otherwise, the matrix will remain
 *        unchanged and an error code will be returned.
 *
 * @param matrix Pointer to the matrix4 object to be inverted.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the matrix is not invertible.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Invert(ArkUI_Matrix4* matrix);

/**
 * @brief Combine another matrix with the original matrix, and storing the resulting matrix in oriMatrix.
 *        The resulting matrix is equivalent to first applying the transformation of oriMatrix and then applying
 *        the transformation of anotherMatrix. This function will alter the oriMatrix object.
 *
 * @param oriMatrix Pointer to the original matrix4 object.
 * @param anotherMatrix Pointer to another matrix object to be combined.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Combine(ArkUI_Matrix4* oriMatrix, const ArkUI_Matrix4* anotherMatrix);

/**
 * @brief Apply a tranlation transformation to the original matrix to obtain the translated matrix. Each translation
 *        transformation is applied cumulatively. This function will alter the input matrix object.
 *
 * @param matrix Pointer to the matrix4 object to be translated.
 * @param translate Pointer to the translation options.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Translate(ArkUI_Matrix4* matrix, const ArkUI_Matrix4TranslationOptions* translate);

/**
 * @brief Apply a scale transformation to the original matrix to obtain the scaled matrix. Each scale
 *        transformation is applied cumulatively. This function will alter the input matrix object.
 *
 * @param matrix Pointer to the matrix4 object to be scaled.
 * @param scale Pointer to the scale options.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Scale(ArkUI_Matrix4* matrix, const ArkUI_Matrix4ScaleOptions* scale);

/**
 * @brief Apply a rotation transformation to the original matrix to obtain the rotated matrix. Each rotation
 *        transformation is applied cumulatively. This function will alter the input matrix object.
 *
 * @param matrix Pointer to the matrix4 object to be rotated.
 * @param rotate Pointer to the rotation options.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Rotate(ArkUI_Matrix4* matrix, const ArkUI_Matrix4RotationOptions* rotate);

/**
 * @brief Apply a skew transformation to the original matrix to obtain the skewed matrix. Each skew
 *        transformation is applied cumulatively. This function will alter the input matrix object.
 *
 * @param matrix Pointer to the matrix4 object to be skewed. It must not be null.
 * @param skewX Skew coefficient in the x direction.
 * @param skewY Skew coefficient in the y direction.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_Skew(ArkUI_Matrix4* matrix, const float skewX, const float skewY);

/**
 * @brief Calculate the new coordinate position of a point after it has been transformed by a matrix.
 *        The calculated transformed coordinate point will be filled into the ArkUI_PointF structure
 *        pointed to by result.
 *
 * @param matrix Pointer to the matrix4 object.
 * @param oriPoint Pointer to the original coordinate point.
 * @param result Pointer to the result point. It must not be null.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_TransformPoint(const ArkUI_Matrix4* matrix, const ArkUI_PointF* oriPoint, ArkUI_PointF* result);

/**
 * @brief Map the vertex coordinates of one polygon to the vertex coordinates of another polygon, and calculate the required
 *        matrix. The resulting matrix will be filled into the object pointed to by matrix.
 * 
 * @param matrix Pointer to the original matrix4 object. The result matrix will be filled into the object pointed to by it.
 *               It must not be null.
 * @param src Pointer to the array of original polygon coordinate points. The array should be at least as long as pointCount.
 * @param dst Pointer to the array of polygon coordinate points after mapping. The array should be at least as long as pointCount.
 * @param pointCount The number of polygon points, which must be one of the values 0, 1, 2, 3, or 4.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_SetPolyToPoly(ArkUI_Matrix4* matrix, const ArkUI_PointF* src, const ArkUI_PointF* dst, const uint32_t pointCount);

/**
 * @brief Obtain the 16 elements of the matrix and fill them into the array pointed to by result.
 *        The array pointed to by result must have space for 16 float elements.
 *
 * @param matrix Pointer to the original matrix4 object.
 * @param result Pointer to an array that can hold 16 floating-point numbers. It must not be null.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_Matrix4_GetElements(const ArkUI_Matrix4* matrix, float* result);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_TYPE_VISUAL_H
/** @} */

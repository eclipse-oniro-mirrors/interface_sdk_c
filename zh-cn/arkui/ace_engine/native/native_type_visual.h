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
  * @brief 定义四阶矩阵对象。
  *
  * @since 24
  */
 typedef struct ArkUI_Matrix4 ArkUI_Matrix4;
 
 /**
  * @brief 定义阴影类型枚举值。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 彩色阴影。
      */
     ARKUI_SHADOW_TYPE_COLOR = 0,
     /**
      * 模糊阴影。
      */
     ARKUI_SHADOW_TYPE_BLUR
 } ArkUI_ShadowType;
 
 /**
  * @brief 阴影效果枚举值。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 超小阴影。
      * !{@link defaultxs}
      */
     ARKUI_SHADOW_STYLE_OUTER_DEFAULT_XS = 0,
     /**
      * 小阴影。
      * !{@link defaultsm}
      */
     ARKUI_SHADOW_STYLE_OUTER_DEFAULT_SM,
     /**
      * 中阴影。
      * !{@link defaultmd}
      */
     ARKUI_SHADOW_STYLE_OUTER_DEFAULT_MD,
     /**
      * 大阴影。
      * !{@link defaultlg}
      */
     ARKUI_SHADOW_STYLE_OUTER_DEFAULT_LG,
     /**
      * 浮动小阴影。
      * !{@link floatingsm}
      */
     ARKUI_SHADOW_STYLE_OUTER_FLOATING_SM,
     /**
      * 浮动中阴影。
      * !{@link floatingmd}
      */
     ARKUI_SHADOW_STYLE_OUTER_FLOATING_MD,
 } ArkUI_ShadowStyle;
 
 /**
  * @brief 动画曲线枚举值。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 动画从头到尾的速度都是相同。
      */
     ARKUI_CURVE_LINEAR = 0,
     /**
      * 动画以低速开始，然后加快，在结束前变慢。
      */
     ARKUI_CURVE_EASE,
     /**
      * 动画以低速开始。
      */
     ARKUI_CURVE_EASE_IN,
     /**
      * 动画以低速结束。
      */
     ARKUI_CURVE_EASE_OUT,
     /**
      * 动画以低速开始和结束，提供平滑自然的动画过渡效果。
      */
     ARKUI_CURVE_EASE_IN_OUT,
     /**
      * 动画标准曲线。
      */
     ARKUI_CURVE_FAST_OUT_SLOW_IN,
     /**
      * 动画减速曲线。
      */
     ARKUI_CURVE_LINEAR_OUT_SLOW_IN,
     /**
      * 动画加速曲线。
      */
     ARKUI_CURVE_FAST_OUT_LINEAR_IN,
     /**
      * 动画急缓曲线。
      */
     ARKUI_CURVE_EXTREME_DECELERATION,
     /**
      * 动画锐利曲线。
      */
     ARKUI_CURVE_SHARP,
     /**
      * 动画节奏曲线。
      */
     ARKUI_CURVE_RHYTHM,
     /**
      * 动画平滑曲线。
      */
     ARKUI_CURVE_SMOOTH,
     /**
      * 动画阻尼曲线。
      */
     ARKUI_CURVE_FRICTION,
 } ArkUI_AnimationCurve;
 
 /**
  * @brief 定义动画播放模式。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 动画正向播放。
      */
     ARKUI_ANIMATION_PLAY_MODE_NORMAL = 0,
     /**
      * 动画反向播放。
      */
     ARKUI_ANIMATION_PLAY_MODE_REVERSE,
     /**
      * 动画交替循环播放，在奇数次正向播放，在偶数次反向播放。
      */
     ARKUI_ANIMATION_PLAY_MODE_ALTERNATE,
     /**
      * 动画反向交替循环播放，在奇数次反向播放，在偶数次正向播放。
      */
     ARKUI_ANIMATION_PLAY_MODE_ALTERNATE_REVERSE,
 } ArkUI_AnimationPlayMode;
 
 /**
  * @brief 定义背景模糊样式。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 轻薄材质模糊。
      * !{@link thin}
      */
     ARKUI_BLUR_STYLE_THIN = 0,
     /**
      * 普通厚度材质模糊。
      * !{@link regular}
      */
     ARKUI_BLUR_STYLE_REGULAR,
     /**
      * 厚材质模糊。
      * !{@link thick}
      */
     ARKUI_BLUR_STYLE_THICK,
     /**
      * 近距景深模糊。
      * !{@link backgroundthin}
      */
     ARKUI_BLUR_STYLE_BACKGROUND_THIN,
     /**
      * 中距景深模糊。
      * !{@link backgroundregular}
      */
     ARKUI_BLUR_STYLE_BACKGROUND_REGULAR,
     /**
      * 远距景深模糊。
      * !{@link backgroundthick}
      */
     ARKUI_BLUR_STYLE_BACKGROUND_THICK,
     /**
      * 超远距景深模糊。
      * !{@link backgroundultrathick}
      */
     ARKUI_BLUR_STYLE_BACKGROUND_ULTRA_THICK,
     /**
      * 关闭模糊。
      * !{@link none}
      */
     ARKUI_BLUR_STYLE_NONE,
     /**
      * 组件超轻薄材质模糊。
      * !{@link componentultrathin}
      */
     ARKUI_BLUR_STYLE_COMPONENT_ULTRA_THIN,
     /**
      * 组件轻薄材质模糊。
      * !{@link componentthin}
      */
     ARKUI_BLUR_STYLE_COMPONENT_THIN,
     /**
      * 组件普通材质模糊。
      * !{@link componentregular}
      */
     ARKUI_BLUR_STYLE_COMPONENT_REGULAR,
     /**
      * 组件厚材质模糊。
      * !{@link componentthick}
      */
     ARKUI_BLUR_STYLE_COMPONENT_THICK,
     /**
      * 组件超厚材质模糊。
      * !{@link componentultrathick}
      */
     ARKUI_BLUR_STYLE_COMPONENT_ULTRA_THICK,
 } ArkUI_BlurStyle;
 
 /**
  * @brief 定义背景模糊激活策略。
  *
  * @since 19
  */
 typedef enum {
     /**
      * 跟随窗口焦点状态变化，窗口非焦点状态不激活，窗口焦点状态激活。
      */
     ARKUI_BLUR_STYLE_ACTIVE_POLICY_FOLLOWS_WINDOW_ACTIVE_STATE = 0,
     /**
      * 始终激活。
      */
     ARKUI_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_ACTIVE,
     /**
      * 始终不激活。
      */
     ARKUI_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_INACTIVE,
 } ArkUI_BlurStyleActivePolicy;
 
 /**
  * @brief 混合模式枚举值。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 将上层图像直接覆盖到下层图像上，不进行任何混合操作。
      */
     ARKUI_BLEND_MODE_NONE = 0,
     /**
      * 将源像素覆盖的目标像素清除为完全透明。
      */
     ARKUI_BLEND_MODE_CLEAR,
     /**
      * r = s，只显示源像素。
      */
     ARKUI_BLEND_MODE_SRC,
     /**
      * r = d，只显示目标像素。
      */
     ARKUI_BLEND_MODE_DST,
     /**
      * r = s + (1 - sa) * d，将源像素按照透明度进行混合，覆盖在目标像素上。
      */
     ARKUI_BLEND_MODE_SRC_OVER,
     /**
      * r = d + (1 - da) * s，将目标像素按照透明度进行混合，覆盖在源像素上。
      */
     ARKUI_BLEND_MODE_DST_OVER,
     /**
      * r = s * da，只显示源像素中与目标像素重叠的部分。
      */
     ARKUI_BLEND_MODE_SRC_IN,
     /**
      * r = d * sa，只显示目标像素中与源像素重叠的部分。
      */
     ARKUI_BLEND_MODE_DST_IN,
     /**
      * r = s * (1 - da)，只显示源像素中与目标像素不重叠的部分。
      */
     ARKUI_BLEND_MODE_SRC_OUT,
     /**
      * r = d * (1 - sa)，只显示目标像素中与源像素不重叠的部分。
      */
     ARKUI_BLEND_MODE_DST_OUT,
     /**
      * r = s * da + d * (1 - sa)，在源像素和目标像素重叠的地方绘制源像素，在源像素和目标像素不重叠的地方绘制目标像素。
      */
     ARKUI_BLEND_MODE_SRC_ATOP,
     /**
      * r = d * sa + s * (1 - da)，在源像素和目标像素重叠的地方绘制目标像素，在源像素和目标像素不重叠的地方绘制源像素。
      */
     ARKUI_BLEND_MODE_DST_ATOP,
     /**
      * r = s * (1 - da) + d * (1 - sa)，只显示源像素与目标像素不重叠的部分。
      */
     ARKUI_BLEND_MODE_XOR,
     /**
      * r = min(s + d, 1)，将源像素值与目标像素值相加，并将结果作为新的像素值。
      */
     ARKUI_BLEND_MODE_PLUS,
     /**
      * r = s * d，将源像素与目标像素进行乘法运算，并将结果作为新的像素值。
      */
     ARKUI_BLEND_MODE_MODULATE,
     /**
      * r = s + d - s * d，将两个图像的像素值相加，然后减去它们的乘积来实现混合。
      */
     ARKUI_BLEND_MODE_SCREEN,
     /**
      * 根据目标像素来决定使用MULTIPLY混合模式还是SCREEN混合模式。
      */
     ARKUI_BLEND_MODE_OVERLAY,
     /**
      * rc = s + d - max(s * da, d * sa), ra = kSrcOver，当两个颜色重叠时，较暗的颜色会覆盖较亮的颜色。
      */
     ARKUI_BLEND_MODE_DARKEN,
     /**
      * rc = s + d - min(s * da, d * sa), ra = kSrcOver，将源图像和目标图像中的像素进行比较，选取两者中较亮的像素作为最终的混合结果。
      */
     ARKUI_BLEND_MODE_LIGHTEN,
     /**
      * 使目标像素变得更亮来反映源像素。
      */
     ARKUI_BLEND_MODE_COLOR_DODGE,
     /**
      * 使目标像素变得更暗来反映源像素。
      */
     ARKUI_BLEND_MODE_COLOR_BURN,
     /**
      * 根据源像素的值来决定目标像素变得更亮或者更暗。根据源像素来决定使用MULTIPLY混合模式还是SCREEN混合模式。
      */
     ARKUI_BLEND_MODE_HARD_LIGHT,
     /**
      * 根据源像素来决定使用LIGHTEN混合模式还是DARKEN混合模式。
      */
     ARKUI_BLEND_MODE_SOFT_LIGHT,
     /**
      * rc = s + d - 2 * (min(s * da, d * sa)), ra = kSrcOver，对比源像素和目标像素，亮度更高的像素减去亮度更低的像素，产生高对比度的效果。
      */
     ARKUI_BLEND_MODE_DIFFERENCE,
     /**
      * rc = s + d - two(s * d), ra = kSrcOver，对比源像素和目标像素，亮度更高的像素减去亮度更低的像素，产生柔和的效果。
      */
     ARKUI_BLEND_MODE_EXCLUSION,
     /**
      * r = s * (1 - da) + d * (1 - sa) + s * d，将源图像与目标图像进行乘法混合，得到一张新的图像。
      */
     ARKUI_BLEND_MODE_MULTIPLY,
     /**
      * 保留源图像的亮度和饱和度，但会使用目标图像的色调来替换源图像的色调。
      */
     ARKUI_BLEND_MODE_HUE,
     /**
      * 保留目标像素的亮度和色调，但会使用源像素的饱和度来替换目标像素的饱和度。
      */
     ARKUI_BLEND_MODE_SATURATION,
     /**
      * 保留源像素的饱和度和色调，但会使用目标像素的亮度来替换源像素的亮度。
      */
     ARKUI_BLEND_MODE_COLOR,
     /**
      * 保留目标像素的色调和饱和度，但会用源像素的亮度替换目标像素的亮度。
      */
     ARKUI_BLEND_MODE_LUMINOSITY,
 } ArkUI_BlendMode;
 
 /**
  * @brief 前景和阴影颜色的枚举值。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 前景色为控件背景色的反色。
      */
     ARKUI_COLOR_STRATEGY_INVERT = 0,
     /**
      * 控件背景阴影色为控件背景阴影区域的平均色。
      */
     ARKUI_COLOR_STRATEGY_AVERAGE,
     /**
      * 控件背景阴影色为控件背景阴影区域的主色。
      */
     ARKUI_COLOR_STRATEGY_PRIMARY,
 } ArkUI_ColorStrategy;
 
 /**
  * @brief 遮罩类型枚举。遮罩是一种用于限制组件显示区域的手段，它利用特定的形状对组件内容进行裁剪，从而实现只有遮罩区域内的内容才可见的效果。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 矩形类型。
      */
     ARKUI_MASK_TYPE_RECTANGLE = 0,
     /**
      * 圆形。
      */
     ARKUI_MASK_TYPE_CIRCLE,
     /**
      * 椭圆形类型。
      */
     ARKUI_MASK_TYPE_ELLIPSE,
     /**
      * 路径类型。
      */
     ARKUI_MASK_TYPE_PATH,
     /**
      * 进度类型。
      */
     ARKUI_MASK_TYPE_PROGRESS,
 } ArkUI_MaskType;
 
 /**
  * @brief 裁剪类型枚举。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 矩形类型。
      */
     ARKUI_CLIP_TYPE_RECTANGLE = 0,
     /**
      * 圆形。
      */
     ARKUI_CLIP_TYPE_CIRCLE,
     /**
      * 椭圆形类型。
      */
     ARKUI_CLIP_TYPE_ELLIPSE,
     /**
      * 路径类型。
      */
     ARKUI_CLIP_TYPE_PATH,
 } ArkUI_ClipType;
 
 /**
  * @brief 自定义形状。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 矩形类型。
      */
     ARKUI_SHAPE_TYPE_RECTANGLE = 0,
     /**
      * 圆形。
      */
     ARKUI_SHAPE_TYPE_CIRCLE,
     /**
      * 椭圆形类型。
      */
     ARKUI_SHAPE_TYPE_ELLIPSE,
     /**
      * 路径类型。
      */
     ARKUI_SHAPE_TYPE_PATH,
 } ArkUI_ShapeType;
 
 /**
  * @brief 定义渐变方向结构。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 向左渐变。
      */
     ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT = 0,
     /**
      * 向上渐变。
      */
     ARKUI_LINEAR_GRADIENT_DIRECTION_TOP,
     /**
      * 向右渐变。
      */
     ARKUI_LINEAR_GRADIENT_DIRECTION_RIGHT,
     /**
      * 向下渐变。
      */
     ARKUI_LINEAR_GRADIENT_DIRECTION_BOTTOM,
     /**
      * 向左上渐变。
      */
     ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT_TOP,
     /**
      * 向左下渐变。
      */
     ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT_BOTTOM,
     /**
      * 向右上渐变。
      */
     ARKUI_LINEAR_GRADIENT_DIRECTION_RIGHT_TOP,
     /**
      * 向右下渐变。
      */
     ARKUI_LINEAR_GRADIENT_DIRECTION_RIGHT_BOTTOM,
     /**
      * 不渐变。
      */
     ARKUI_LINEAR_GRADIENT_DIRECTION_NONE,
     /**
      * 自定义渐变方向.
      */
     ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM,
 } ArkUI_LinearGradientDirection;
 
 /**
  * @brief 定义转场从边缘滑入和滑出的效果。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 转场从窗口的上边缘滑入和滑出。
      */
     ARKUI_TRANSITION_EDGE_TOP = 0,
     /**
      * 转场从窗口的下边缘滑入和滑出。
      */
     ARKUI_TRANSITION_EDGE_BOTTOM,
     /**
      * 转场从窗口的左边缘滑入和滑出。
      */
     ARKUI_TRANSITION_EDGE_START,
     /**
      * 转场从窗口的右边缘滑入和滑出。
      */
     ARKUI_TRANSITION_EDGE_END,
 } ArkUI_TransitionEdge;
 
 /**
  * @brief 指定的混合模式应用于视图的内容选项.
  *
  * @since 12
  */
 typedef enum {
     /**
      * 在目标图像上按顺序混合视图的内容.
      */
     BLEND_APPLY_TYPE_FAST = 0,
     /**
      * 将此组件和子组件内容绘制到离屏画布上，然后整体进行混合.
      */
     BLEND_APPLY_TYPE_OFFSCREEN,
 } ArkUI_BlendApplyType;
 
 /**
  * @brief 在动画中定义{@link OH_ArkUI_AnimatorOption_RegisterOnFinishCallback}回调的类型。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 当整个动画结束并立即删除时，将触发回调。
      */
     ARKUI_FINISH_CALLBACK_REMOVED = 0,
     /**
      * 当动画在逻辑上处于下降状态，但可能仍处于其长尾状态时，将触发回调。长尾状态是指动画即将完全停止前的残余变化过程，此时动画的数值变化已非常微小，接近目标值。
      */
     ARKUI_FINISH_CALLBACK_LOGICALLY,
 } ArkUI_FinishCallbackType;
 
 /**
  * @brief 定义动画终态内容大小与位置的枚举值。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 保持动画终态的内容大小，并且内容始终与组件保持中心对齐。
      */
     ARKUI_RENDER_FIT_CENTER = 0,
     /**
      * 保持动画终态的内容大小，并且内容始终与组件保持顶部中心对齐。
      */
     ARKUI_RENDER_FIT_TOP,
     /**
      * 保持动画终态的内容大小，并且内容始终与组件保持底部中心对齐。
      */
     ARKUI_RENDER_FIT_BOTTOM,
     /**
      * 保持动画终态的内容大小，并且内容始终与组件保持左侧对齐。
      */
     ARKUI_RENDER_FIT_LEFT,
     /**
      * 保持动画终态的内容大小，并且内容始终与组件保持右侧对齐。
      */
     ARKUI_RENDER_FIT_RIGHT,
     /**
      * 保持动画终态的内容大小，并且内容始终与组件保持左上角对齐。
      */
     ARKUI_RENDER_FIT_TOP_LEFT,
     /**
      * 保持动画终态的内容大小，并且内容始终与组件保持右上角对齐。
      */
     ARKUI_RENDER_FIT_TOP_RIGHT,
     /**
      * 保持动画终态的内容大小，并且内容始终与组件保持左下角对齐。
      */
     ARKUI_RENDER_FIT_BOTTOM_LEFT,
     /**
      * 保持动画终态的内容大小，并且内容始终与组件保持右下角对齐。
      */
     ARKUI_RENDER_FIT_BOTTOM_RIGHT,
     /**
      * 不考虑动画终态内容的宽高比，并且内容始终缩放到组件的大小。
      */
     ARKUI_RENDER_FIT_RESIZE_FILL,
     /**
      * 保持动画终态内容的宽高比进行缩小或放大，使内容完整显示在组件内，且与组件保持中心对齐。
      */
     ARKUI_RENDER_FIT_RESIZE_CONTAIN,
     /**
      * 保持动画终态内容的宽高比进行缩小或放大，使内容完整显示在组件内。当组件宽方向有剩余时，内容与组件保持左侧对齐，当组件高方向有剩余时，内容与组件保持顶部对齐。
      */
     ARKUI_RENDER_FIT_RESIZE_CONTAIN_TOP_LEFT,
     /**
      * 保持动画终态内容的宽高比进行缩小或放大，使内容完整显示在组件内。当组件宽方向有剩余时，内容与组件保持右侧对齐，当组件高方向有剩余时，内容与组件保持底部对齐。
      */
     ARKUI_RENDER_FIT_RESIZE_CONTAIN_BOTTOM_RIGHT,
     /**
      * 保持动画终态内容的宽高比进行缩小或放大，使内容两边都大于或等于组件两边，且与组件保持中心对齐，显示内容的中间部分。
      */
     ARKUI_RENDER_FIT_RESIZE_COVER,
     /**
      * 保持动画终态内容的宽高比进行缩小或放大，使内容的两边都恰好大于或等于组件两边。当内容宽方向有剩余时，内容与组件保持左侧对齐，显示内容的左侧部分。当内容高方向有剩余时，内容与组件保持顶部对齐，显示内容的顶侧部分。
      */
     ARKUI_RENDER_FIT_RESIZE_COVER_TOP_LEFT,
     /**
      * 保持动画终态内容的宽高比进行缩小或放大，使内容的两边都恰好大于或等于组件两边。当内容宽方向有剩余时，内容与组件保持右侧对齐，显示内容的右侧部分。当内容高方向有剩余时，内容与组件保持底部对齐，显示内容的底侧部分。
      */
     ARKUI_RENDER_FIT_RESIZE_COVER_BOTTOM_RIGHT
 } ArkUI_RenderFit;
 
 /**
  * @brief 定义帧动画组件在动画开始前和结束后的状态。
  *
  * @since 12
 */
 typedef enum {
     /**
      * 动画未执行时不会将任何样式应用于目标，动画播放完成之后恢复初始默认状态。
      */
     ARKUI_ANIMATION_FILL_MODE_NONE,
     /**
      * 目标将保留动画执行期间最后一个关键帧的状态。
      */
     ARKUI_ANIMATION_FILL_MODE_FORWARDS,
     /**
      * 动画将在应用于目标时立即应用第一个关键帧中定义的值，并在{@link delay}期间保留此值。
      */
     ARKUI_ANIMATION_FILL_MODE_BACKWARDS,
     /**
      * 动画将遵循{@link ARKUI_ANIMATION_FILL_MODE_FORWARDS}和{@link ARKUI_ANIMATION_FILL_MODE_BACKWARDS}的规则，从而在两个方向上扩展动画属性。
      */
     ARKUI_ANIMATION_FILL_MODE_BOTH,
 } ArkUI_AnimationFillMode;
 
 /**
  * @brief 定义动画播放模式。
  *
  * @since 12
  */
 typedef enum {
     /**
      * 动画正向循环播放。
      */
     ARKUI_ANIMATION_DIRECTION_NORMAL = 0,
     /**
      * 动画反向循环播放。
      */
     ARKUI_ANIMATION_DIRECTION_REVERSE,
     /**
      * 动画交替循环播放，在奇数次正向播放，在偶数次反向播放。
      */
     ARKUI_ANIMATION_DIRECTION_ALTERNATE,
     /**
      * 动画反向交替循环播放，在奇数次反向播放，在偶数次正向播放。
      */
     ARKUI_ANIMATION_DIRECTION_ALTERNATE_REVERSE,
 } ArkUI_AnimationDirection;
 
 /**
  * @brief 定义组件转场时的平移效果对象。
  *
  * @since 12
  */
 typedef struct {
     /**
      * 横向的平移距离，单位为vp。
      */
     float x;
     /**
      * 纵向的平移距离，单位为vp。
      */
     float y;
     /**
      * 深度方向的平移距离，单位为vp。
      */
     float z;
 } ArkUI_TranslationOptions;
 
 /**
  * @brief 定义组件转场时的缩放效果对象。
  *
  * @since 12
  */
 typedef struct {
     /**
      * x轴的缩放倍数。x>1时以x轴方向放大，0<x<1时以x轴方向缩小，x=0时表示在x轴方向缩小成0，x=1时表示在x轴方向缩放倍数是1，x<0时沿x轴反向并缩放。
      */
     float x;
     /**
      * y轴的缩放倍数。y>1时以y轴方向放大，0<y<1时以y轴方向缩小，y=0时表示在y轴方向缩小成0，y=1时表示在y轴方向缩放倍数是1，y<0时沿y轴反向并缩放。
      */
     float y;
     /**
      * 当前为二维显示，该参数无效。
      */
     float z;
     /**
      * 变换中心点x轴坐标。表示组件变换中心点（即锚点）的x方向坐标，单位为vp。
      */
     float centerX;
     /**
      * 变换中心点y轴坐标。表示组件变换中心点（即锚点）的y方向坐标，单位为vp。
      */
     float centerY;
 } ArkUI_ScaleOptions;
 
 /**
  * @brief 定义组件转场时的旋转效果对象。
  *
  * @since 12
  */
 typedef struct {
     /**
      * 横向的旋转向量分量。
      */
     float x;
     /**
      * 纵向的旋转向量分量。
      */
     float y;
     /**
      * 竖向的旋转向量分量。
      */
     float z;
     /**
      * 旋转角度。取值范围：(-∞, +∞)。取值为正时相对于旋转轴方向顺时针转动，取值为负时相对于旋转轴方向逆时针转动。
      */
     float angle;
     /**
      * 变换中心点x轴坐标。表示组件变换中心点（即锚点）的x方向坐标，单位为vp。
      */
     float centerX;
     /**
      * 变换中心点y轴坐标。表示组件变换中心点（即锚点）的y方向坐标，单位为vp。
      */
     float centerY;
     /**
      * z轴锚点，即3D旋转中心点的z轴分量，单位为px。
      */
     float centerZ;
     /**
      * 视距，即视点到z=0平面的距离，单位为px。
      */
     float perspective;
 } ArkUI_RotationOptions;
 
 /**
  * @brief 定义阴影选项对象。
  *
  * @since 24
  */
 typedef struct OH_ArkUI_ShadowOptions OH_ArkUI_ShadowOptions;
 
 /**
  * @brief 定义路径动画的运动路径配置项。
  *
  * @since 23
  */
 typedef struct ArkUI_MotionPathOptions ArkUI_MotionPathOptions;
 
 /**
  * @brief 创建路径动画的运动路径配置项。
  *
  * @return 指向路径动画的运动路径配置项{@link ArkUI_MotionPathOptions}的指针。
  *     <br>新建的{@link ArkUI_MotionPathOptions}对象中，路径动画的运动路径path值为空字符串，路径动画起点进度from值为0，路径动画终点进度to值为1，
  *     组件是否沿路径旋转rotatable值为false。
  * @since 23
  */
 ArkUI_MotionPathOptions* OH_ArkUI_MotionPathOptions_Create();
 
 /**
  * @brief 销毁路径动画的运动路径配置项。
  *
  * @param options 指向路径动画的运动路径配置项{@link ArkUI_MotionPathOptions}的指针。
  * @since 23
  */
 void OH_ArkUI_MotionPathOptions_Dispose(ArkUI_MotionPathOptions* options);
 
 /**
  * @brief 设置路径动画的运动路径。
  *
  * @param options 指向路径动画的运动路径配置项{@link ArkUI_MotionPathOptions}的指针。
  * @param svgPath 路径动画的运动路径字符串。
  *     <br>该路径支持使用"start"和"end"作为起点和终点的占位符，例如："Mstart.x start.y L50 50 Lend.x end.y Z"。路径字符串格式请参考{@link 绘制路径}。若设置为空字符串，
  *     等效于未设置路径动画。
  * @return 错误码。
  *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
  *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
  * @since 23
  */
 ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetPath(ArkUI_MotionPathOptions* options, const char* svgPath);
 
 /**
  * @brief 获取路径动画的运动路径配置项中存储的运动路径字符串。
  *
  * @param options 指向路径动画的运动路径配置项{@link ArkUI_MotionPathOptions}的指针。
  * @param svgPathBuffer 存储运动路径字符串的缓冲区指针。
  * @param bufferSize svgPathBuffer参数的缓冲区大小。
  * @param writeLength 返回{@link ARKUI_ERROR_CODE_NO_ERROR}时，表示实际写入缓冲区的字符串长度。
  *     <br>返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}时，表示如果为入参异常，writeLength不会被赋值，如果为拷贝异常，writeLength为可容纳目标字符串的最小缓冲区大小。
  *     <br>返回{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}时，表示可容纳目标字符串的最小缓冲区大小。
  * @return 错误码。
  *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
  *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
  *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 缓冲区大小不足。
  * @since 23
  */
 ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetPath(const ArkUI_MotionPathOptions* options, char* svgPathBuffer,
     const int32_t bufferSize, int32_t* writeLength);
 
 /**
  * @brief 设置路径动画起点进度。进度指已移动路径长度与总路径长度的比值。
  *
  * @param options 指向路径动画的运动路径配置项{@link ArkUI_MotionPathOptions}的指针。
  * @param from 路径动画的起点进度，取值范围为[0.0, 1.0]，且需满足from小于或等于终点进度to，否则将返回{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE}错误码。
  *     <br>to的含义参考{@link OH_ArkUI_MotionPathOptions_SetTo}。
  * @return 错误码。
  *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
  *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
  *     <br>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} from超出[0.0, 1.0]范围，或from大于终点进度to。
  * @since 23
  */
 ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetFrom(ArkUI_MotionPathOptions* options, const float from);
 
 /**
  * @brief 获取路径动画的运动路径配置项中的路径动画起点进度。
  *
  * @param options 指向路径动画的运动路径配置项{@link ArkUI_MotionPathOptions}的指针。
  * @param from 用于接收路径动画的运动路径配置项{@link ArkUI_MotionPathOptions}中起点进度值的指针。
  * @return 错误码。
  *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
  *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
  * @since 23
  */
 ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetFrom(const ArkUI_MotionPathOptions* options, float* from);
 
 /**
  * @brief 设置路径动画终点进度。进度指已移动路径长度与总路径长度的比值。
  *
  * @param options 指向路径动画的运动路径配置项{@link ArkUI_MotionPathOptions}的指针。
  * @param to 路径动画的终点进度，取值范围为[0.0, 1.0]，且需满足to大或等于起点进度from；否则将返回{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE}错误码。
  *     <br>from的含义参考{@link OH_ArkUI_MotionPathOptions_SetFrom}。
  * @return 错误码。
  *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
  *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
  *     <br>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} to超出[0.0, 1.0]范围，或to小于起点进度from。
  * @since 23
  */
 ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetTo(ArkUI_MotionPathOptions* options, const float to);
 
 /**
  * @brief 获取路径动画的运动路径配置项中的路径动画终点进度。
  *
  * @param options 指向路径动画的运动路径配置项{@link ArkUI_MotionPathOptions}的指针。
  * @param to 用于接收路径动画的运动路径配置项{@link ArkUI_MotionPathOptions}中终点进度值的指针。
  * @return 错误码。
  *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
  *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
  * @since 23
  */
 ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetTo(const ArkUI_MotionPathOptions* options, float* to);
 
 /**
  * @brief 设置组件是否沿运动路径旋转。
  *
  * @param options 指向路径动画的运动路径配置项{@link ArkUI_MotionPathOptions}的指针。
  * @param rotatable 组件是否沿路径旋转。true表示组件沿路径旋转；false表示组件不沿路径旋转。默认值：false。
  * @return 错误码。
  *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
  *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
  * @since 23
  */
 ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetRotatable(ArkUI_MotionPathOptions* options, const bool rotatable);
 
 /**
  * @brief 获取组件是否沿运动路径旋转。
  *
  * @param options 指向路径动画的运动路径配置项{@link ArkUI_MotionPathOptions}的指针。
  * @param rotatable 用于接收路径动画的运动路径配置项{@link ArkUI_MotionPathOptions}中rotatable参数值的指针，表示组件是否沿路径旋转。
  *     <br>true表示组件沿路径旋转；false表示组件不沿路径旋转。
  * @return 错误码。
  *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
  *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
  * @since 23
  */
 ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetRotatable(const ArkUI_MotionPathOptions* options, bool* rotatable);
 
 /**
  * @brief 创建一个阴影选项对象。当该对象不再使用时，请调用{@link OH_ArkUI_ShadowOptions_Destroy}销毁。
  *
  * @return 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @since 24
  */
 OH_ArkUI_ShadowOptions* OH_ArkUI_ShadowOptions_Create();
 
 /**
  * @brief 销毁阴影选项对象。
  *
  * @param options 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @since 24
  */
 void OH_ArkUI_ShadowOptions_Destroy(OH_ArkUI_ShadowOptions* options);
 
 /**
  * @brief 设置阴影选项的模糊半径。
  *
  * @param options 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @param radius 阴影的模糊半径，单位为vp。
  * @return 返回结果码。
  *     <br>若操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>若参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetRadius(OH_ArkUI_ShadowOptions* options, float radius);
 
 /**
  * @brief 获取阴影选项的模糊半径。
  *
  * @param options 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @param radius 阴影的模糊半径，单位为vp。
  * @return 返回结果码。
  *     <br>若操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>若参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetRadius(OH_ArkUI_ShadowOptions* options, float* radius);
 
 /**
  * @brief 设置阴影选项的阴影类型。
  *
  * @param options 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @param type 阴影类型{@link ArkUI_ShadowType}。
  * @return 返回结果码。
  *     <br>若操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>若参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetType(OH_ArkUI_ShadowOptions* options, ArkUI_ShadowType type);
 
 /**
  * @brief 获取阴影选项的阴影类型。
  *
  * @param options 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @param type 阴影类型{@link ArkUI_ShadowType}。
  * @return 返回结果码。
  *     <br>若操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>若参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetType(OH_ArkUI_ShadowOptions* options, ArkUI_ShadowType* type);
 
 /**
  * @brief 设置阴影选项的阴影颜色。
  *
  * @param options 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @param color 阴影颜色，0xARGB格式。
  * @return 返回结果码。
  *     <br>若操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>若参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetColor(OH_ArkUI_ShadowOptions* options, uint32_t color);
 
 /**
  * @brief 获取阴影选项的阴影颜色。
  *
  * @param options 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @param color 阴影颜色，0xARGB格式。
  * @return 返回结果码。
  *     <br>若操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>若参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetColor(OH_ArkUI_ShadowOptions* options, uint32_t* color);
 
 /**
  * @brief 设置阴影在x轴上的偏移量。
  *
  * @param options 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @param offsetX 阴影在x轴上的偏移量，单位为vp。
  * @return 返回结果码。
  *     <br>若操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>若参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetOffsetX(OH_ArkUI_ShadowOptions* options, float offsetX);
 
 /**
  * @brief 获取阴影在x轴上的偏移量。
  *
  * @param options 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @param offsetX 阴影在x轴上的偏移量，单位为vp。
  * @return 返回结果码。
  *     <br>若操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>若参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetOffsetX(OH_ArkUI_ShadowOptions* options, float* offsetX);
 
 /**
  * @brief 设置阴影在y轴上的偏移量。
  *
  * @param options 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @param offsetY 阴影在y轴上的偏移量，单位为vp。
  * @return 返回结果码。
  *     <br>若操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>若参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetOffsetY(OH_ArkUI_ShadowOptions* options, float offsetY);
 
 /**
  * @brief 获取阴影在y轴上的偏移量。
  *
  * @param options 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @param offsetY 阴影在y轴上的偏移量，单位为vp。
  * @return 返回结果码。
  *     <br>若操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>若参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetOffsetY(OH_ArkUI_ShadowOptions* options, float* offsetY);
 
 /**
  * @brief 设置是否用阴影填充组件内部。
  *
  * @param options 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @param isFill 是否用阴影填充组件内部。true表示用阴影填充组件内部，false表示不用阴影填充组件内部。默认值为false。
  * @return 返回结果码。
  *     <br>若操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>若参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetFill(OH_ArkUI_ShadowOptions* options, bool isFill);
 
 /**
  * @brief 获取是否用阴影填充组件内部。
  *
  * @param options 指向{@link OH_ArkUI_ShadowOptions}对象的指针。
  * @param isFill 是否用阴影填充组件内部。true表示用阴影填充组件内部，false表示不用阴影填充组件内部。
  * @return 返回结果码。
  *     <br>若操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>若参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetFill(OH_ArkUI_ShadowOptions* options, bool* isFill);
 
 /**
  * @brief 定义矩阵缩放的缩放对象。
  *
  * @since 24
  */
 typedef struct ArkUI_Matrix4ScaleOptions ArkUI_Matrix4ScaleOptions;
 
 /**
  * @brief 创建指向矩阵运算的缩放参数对象的指针。在新创建的对象中，x、y和z轴方向的缩放系数默认值，为1。变换中心点的x轴坐标centerX、变换中心点的y轴坐标centerY取默认值，为0。
  *
  * @return 返回指向新创建的{@link ArkUI_Matrix4ScaleOptions}的指针。
  * @since 24
  */
 ArkUI_Matrix4ScaleOptions* OH_ArkUI_Matrix4ScaleOptions_Create();
 
 /**
  * @brief 销毁指向矩阵运算的缩放参数对象的指针。
  *
  * @param options 指向要销毁的{@link ArkUI_Matrix4ScaleOptions}对象的指针。
  * @since 24
  */
 void OH_ArkUI_Matrix4ScaleOptions_Dispose(ArkUI_Matrix4ScaleOptions* options);
 
 /**
  * @brief 设置矩阵运算的缩放参数对象x方向的缩放因子。
  *
  * @param options 指向矩阵运算的缩放参数对象的指针。
  * @param scaleX x方向的缩放因子。取值范围：(-∞, +∞)。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetX(ArkUI_Matrix4ScaleOptions* options, const float scaleX);
 
 /**
  * @brief 获取矩阵运算的缩放参数对象x方向的缩放因子。如果从未设置x的值，则x方向的缩放因子默认值为1。
  *
  * @param options 指向矩阵运算的缩放参数对象的指针。
  * @param scaleX x方向的缩放因子。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetX(const ArkUI_Matrix4ScaleOptions* options, float* scaleX);
 
 /**
  * @brief 设置矩阵运算的缩放参数对象y方向的缩放因子。
  *
  * @param options 指向矩阵运算的缩放参数对象的指针。
  * @param scaleY y方向的缩放因子。取值范围：(-∞, +∞)。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetY(ArkUI_Matrix4ScaleOptions* options, const float scaleY);
 
 /**
  * @brief 获取矩阵运算的缩放参数对象y方向的缩放因子。如果从未设置y的值，则y方向的缩放因子默认值为1。
  *
  * @param options 指向矩阵运算的缩放参数对象的指针。
  * @param scaleY y方向的缩放因子。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetY(const ArkUI_Matrix4ScaleOptions* options, float* scaleY);
 
 /**
  * @brief 设置矩阵运算的缩放参数对象z方向的缩放因子。
  *
  * @param options 指向矩阵运算的缩放参数对象的指针。
  * @param scaleZ z方向的缩放因子。取值范围：(-∞, +∞)。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetZ(ArkUI_Matrix4ScaleOptions* options, const float scaleZ);
 
 /**
  * @brief 获取矩阵运算的缩放参数对象z方向的缩放因子。如果从未设置z的值，则z方向的缩放因子默认值为1。
  *
  * @param options 指向矩阵运算的缩放参数对象的指针。
  * @param scaleZ z方向的缩放因子。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetZ(const ArkUI_Matrix4ScaleOptions* options, float* scaleZ);
 
 /**
  * @brief 设置矩阵运算的缩放参数对象变换中心点的x轴坐标。
  *
  * @param options 指向矩阵运算的缩放参数对象的指针。
  * @param centerX 变换中心点的x轴坐标。取值范围：(-∞, +∞)。0表示在变换中心基础上没有x方向偏移。单位为px。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetCenterX(ArkUI_Matrix4ScaleOptions* options, const float centerX);
 
 /**
  * @brief 获取矩阵运算的缩放参数对象变换中心点的x轴坐标。
  *
  * @param options 指向矩阵运算的缩放参数对象的指针。
  * @param centerX 变换中心点的x轴坐标。单位为px。默认值为0。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetCenterX(const ArkUI_Matrix4ScaleOptions* options, float* centerX);
 
 /**
  * @brief 设置矩阵运算的缩放参数对象变换中心点的y轴坐标。
  *
  * @param options 指向矩阵运算的缩放参数对象的指针。
  * @param centerY 变换中心点的y轴坐标。取值范围：(-∞, +∞)。0表示在变换中心基础上没有y方向偏移。单位为px。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetCenterY(ArkUI_Matrix4ScaleOptions* options, const float centerY);
 
 /**
  * @brief 获取矩阵运算的缩放参数对象变换中心点的y轴坐标。
  *
  * @param options 指向矩阵运算的缩放参数对象的指针。
  * @param centerY 变换中心点的y轴坐标。单位为px。默认值为0。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetCenterY(const ArkUI_Matrix4ScaleOptions* options, float* centerY);
 
 /**
  * @brief 定义矩阵旋转的旋转对象。
  *
  * @since 24
  */
 typedef struct ArkUI_Matrix4RotationOptions ArkUI_Matrix4RotationOptions;
 
 /**
  * @brief 创建矩阵运算的旋转参数对象的指针。在新创建的对象中，单次矩阵变换中心点相对于组件变换中心点的x轴偏移值centerX、单次矩阵变换中心点相对于组件变换中心点的y轴偏移值centerY、旋转角度angle的默认值，为0。
  * 如果未指定x、y、z方向的方向向量中的任何一个，则等同于x=0、y=0、z=1，表示绕z轴旋转。一旦指定了x、y、z方向的方向向量中的任意一个，其余未指定的值等同于0。
  *
  * @return 返回指向新创建的{@link ArkUI_Matrix4RotationOptions}的指针
  * @since 24
  */
 ArkUI_Matrix4RotationOptions* OH_ArkUI_Matrix4RotationOptions_Create();
 
 /**
  * @brief 销毁指向矩阵运算的旋转参数对象的指针。
  *
  * @param options 指向矩阵运算的旋转参数对象的指针。
  * @since 24
  */
 void OH_ArkUI_Matrix4RotationOptions_Dispose(ArkUI_Matrix4RotationOptions* options);
 
 /**
  * @brief 设置矩阵运算的旋转参数对象x方向的方向向量。
  *
  * @param options 指向矩阵运算的旋转参数对象的指针。
  * @param x x轴方向的方向向量的值。取值范围：(-∞, +∞)。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetX(ArkUI_Matrix4RotationOptions* options, const float x);
 
 /**
  * @brief 获取矩阵运算的旋转参数对象x方向的方向向量。如果从未设置过x值，其值将处于未定义状态，此时函数将返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  *
  * @param options 指向矩阵运算的旋转参数对象的指针。
  * @param x x轴方向的方向向量的值。如果从未设置x的值，其值将未定义。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetX(const ArkUI_Matrix4RotationOptions* options, float* x);
 
 /**
  * @brief 设置矩阵运算的旋转参数对象y方向的方向向量。
  *
  * @param options 指向矩阵运算的旋转参数对象的指针。
  * @param y y轴方向的方向向量的值。取值范围：(-∞, +∞)。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetY(ArkUI_Matrix4RotationOptions* options, const float y);
 
 /**
  * @brief 获取矩阵运算的旋转参数对象y方向的方向向量。如果从未设置过y值，其值将处于未定义状态，此时函数将返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  *
  * @param options 指向矩阵运算的旋转参数对象的指针。
  * @param y y轴方向的方向向量的值。如果从未设置y的值，其值将未定义。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetY(const ArkUI_Matrix4RotationOptions* options, float* y);
 
 /**
  * @brief 设置矩阵运算的旋转参数对象z方向的方向向量。
  *
  * @param options 指向矩阵运算的旋转参数对象的指针。
  * @param z z轴方向的方向向量的值。取值范围：(-∞, +∞)。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetZ(ArkUI_Matrix4RotationOptions* options, const float z);
 
 /**
  * @brief 获取矩阵运算的旋转参数对象z方向的方向向量。如果从未设置过z值，其值将处于未定义状态，此时函数将返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  *
  * @param options 指向矩阵运算的旋转参数对象的指针。
  * @param z z轴方向的方向向量的值。如果从未设置z的值，其值将未定义。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetZ(const ArkUI_Matrix4RotationOptions* options, float* z);
 
 /**
  * @brief 设置矩阵运算的旋转参数对象中旋转角度的值。
  *
  * @param options 指向矩阵运算的旋转参数对象的指针。
  * @param angle 旋转角度的值。取值范围：(-∞, +∞)。单位为度。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetAngle(ArkUI_Matrix4RotationOptions* options, const float angle);
 
 /**
  * @brief 获取矩阵运算的旋转参数对象中旋转角度的值。
  *
  * @param options 指向矩阵运算的旋转参数对象的指针。
  * @param angle 旋转角度的值。单位为度。如果从未设置angle的值，其默认值为0。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetAngle(const ArkUI_Matrix4RotationOptions* options, float* angle);
 
 /**
  * @brief 设置单次矩阵变换中心点相对于组件变换中心点的x轴偏移值。
  *
  * @param options 指向矩阵运算的旋转参数对象的指针。
  * @param centerX 单次矩阵变换中心点相对于组件变换中心点的x轴偏移值。取值范围：(-∞, +∞)。0表示在变换中心基础上没有x方向偏移。单位为px。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetCenterX(ArkUI_Matrix4RotationOptions* options, const float centerX);
 
 /**
  * @brief 获取单次矩阵变换中心点相对于组件变换中心点的x轴偏移值。
  *
  * @param options 指向矩阵运算的旋转参数对象的指针。
  * @param centerX 单次矩阵变换中心点相对于组件变换中心点的x轴偏移值。单位为px。如果从未设置centerX的值，其默认值为0。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetCenterX(const ArkUI_Matrix4RotationOptions* options, float* centerX);
 
 /**
  * @brief 设置单次矩阵变换中心点相对于组件变换中心点的y轴偏移值。
  *
  * @param options 指向矩阵运算的旋转参数对象的指针。
  * @param centerY 单次矩阵变换中心点相对于组件变换中心点的y轴偏移值。取值范围：(-∞, +∞)。0表示在变换中心基础上没有y方向偏移。单位为px。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetCenterY(ArkUI_Matrix4RotationOptions* options, const float centerY);
 
 /**
  * @brief 获取单次矩阵变换中心点相对于组件变换中心点的y轴偏移值。
  *
  * @param options 指向矩阵运算的旋转参数对象的指针。
  * @param centerY 单次矩阵变换中心点相对于组件变换中心点的y轴偏移值。单位为px。如果从未设置centerY的值，其默认值为0。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetCenterY(const ArkUI_Matrix4RotationOptions* options, float* centerY);
 
 /**
  * @brief 定义矩阵平移的平移对象。
  *
  * @since 24
  */
 typedef struct ArkUI_Matrix4TranslationOptions ArkUI_Matrix4TranslationOptions;
 
 /**
  * @brief 创建指向矩阵运算的平移对象的指针。在新创建的对象中，x轴的平移距离x、y轴的平移距离y和z轴的平移距离z的默认值为0。
  *
  * @return 返回指向新创建的{@link ArkUI_Matrix4TranslationOptions}的指针。
  * @since 24
  */
 ArkUI_Matrix4TranslationOptions* OH_ArkUI_Matrix4TranslationOptions_Create();
 
 /**
  * @brief 销毁指向矩阵运算的平移对象的指针。
  *
  * @param options 指向要销毁的{@link ArkUI_Matrix4TranslationOptions}对象的指针。
  * @since 24
  */
 void OH_ArkUI_Matrix4TranslationOptions_Dispose(ArkUI_Matrix4TranslationOptions* options);
 
 /**
  * @brief 设置矩阵运算的平移对象x轴方向的平移值。
  *
  * @param options 指向矩阵运算的平移参数对象的指针。
  * @param x x轴方向的平移值。取值范围：(-∞, +∞)。单位为px。如果从未设置x的值，其默认值为0。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetX(ArkUI_Matrix4TranslationOptions* options, const float x);
 
 /**
  * @brief 获取矩阵运算的平移对象x轴方向的平移值。
  *
  * @param options 指向矩阵运算的平移参数对象的指针。
  * @param x x轴方向的平移值。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetX(const ArkUI_Matrix4TranslationOptions* options, float* x);
 
 /**
  * @brief 设置矩阵运算的平移对象y轴方向的平移值。
  *
  * @param options 指向矩阵运算的平移参数对象的指针。
  * @param y y轴方向的平移值。取值范围：(-∞, +∞)。单位为px。如果从未设置y的值，其默认值为0。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetY(ArkUI_Matrix4TranslationOptions* options, const float y);
 
 /**
  * @brief 获取矩阵运算的平移对象y轴方向的平移值。
  *
  * @param options 指向矩阵运算的平移参数对象的指针。
  * @param y y轴方向的平移值。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetY(const ArkUI_Matrix4TranslationOptions* options, float* y);
 
 /**
  * @brief 设置矩阵运算的平移对象z轴方向的平移值。
  *
  * @param options 指向矩阵运算的平移参数对象的指针。
  * @param z z轴方向的平移值。取值范围：(-∞, +∞)。单位为px。如果从未设置z的值，其默认值为0。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetZ(ArkUI_Matrix4TranslationOptions* options, const float z);
 
 /**
  * @brief 获取矩阵运算的平移对象z轴方向的平移值。
  *
  * @param options 指向矩阵运算的平移参数对象的指针。
  * @param z z轴方向的平移值。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetZ(const ArkUI_Matrix4TranslationOptions* options, float* z);
 
 /**
  * @brief 创建一个单位四阶矩阵对象。
  *
  * @return 返回指向创建的单位四阶矩阵对象的指针。
  * @since 24
  */
 ArkUI_Matrix4* OH_ArkUI_Matrix4_CreateIdentity();
 
 /**
  * @brief 通过指定矩阵的每个元素来创建一个四阶矩阵对象。
  *
  * @param elements 指向预期矩阵元素数据的数组指针。数组长度应大于或等于16。该参数不可为空指针。
  * @return 返回新创建的四阶矩阵对象。如果elements指针为空，函数将返回空值。
  * @since 24
  */
 ArkUI_Matrix4* OH_ArkUI_Matrix4_CreateByElements(const float* elements);
 
 /**
  * @brief 销毁矩阵对象的指针。
  *
  * @param matrix 指向要销毁的四阶矩阵对象的指针。
  * @since 24
  */
 void OH_ArkUI_Matrix4_Dispose(ArkUI_Matrix4* matrix);
 
 /**
  * @brief 创建四阶矩阵对象的副本。用于对同一个矩阵进行操作以此获取不同矩阵对象。
  *
  * @param matrix 指向原始四阶矩阵对象的指针。
  * @return 返回新创建的四阶矩阵对象。
  * @since 24
  */
 ArkUI_Matrix4* OH_ArkUI_Matrix4_Copy(const ArkUI_Matrix4* matrix);
 
 /**
  * @brief 对输入矩阵执行逆矩阵变换。
  *
  * @param matrix 指向要逆矩阵变换的四阶矩阵对象的指针。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4_Invert(ArkUI_Matrix4* matrix);
 
 /**
  * @brief 将另一个矩阵与原始矩阵合并，并将结果矩阵存储在oriMatrix中。结果矩阵相当于先应用oriMatrix的变换，然后再应用anotherMatrix的变换。此函数将修改oriMatrix对象。
  *
  * @param oriMatrix 指向原始四阶矩阵对象的指针。
  * @param anotherMatrix 指向要合并的另一个矩阵对象的指针。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4_Combine(ArkUI_Matrix4* oriMatrix, const ArkUI_Matrix4* anotherMatrix);
 
 /**
  * @brief 对原始矩阵应用平移变换以获取平移后的矩阵。每次平移变换都是在先前的矩阵上累积的。变换后将修改输入的矩阵对象。
  *
  * @param matrix 指向待平移四阶矩阵对象的指针。
  * @param translate 指向平移对象的指针。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4_Translate(ArkUI_Matrix4* matrix, const ArkUI_Matrix4TranslationOptions* translate);
 
 /**
  * @brief 对原始矩阵应用缩放变换以获取缩放后的矩阵。每次缩放变换都是在先前的矩阵上累积的。此函数将修改输入的矩阵对象。
  *
  * @param matrix 指向待缩放四阶矩阵对象的指针。
  * @param scale 指向缩放对象的指针。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4_Scale(ArkUI_Matrix4* matrix, const ArkUI_Matrix4ScaleOptions* scale);
 
 /**
  * @brief 对原始矩阵应用旋转变换以获取旋转后的矩阵。每次旋转变换都是在先前的矩阵上累积的。此函数将修改输入的矩阵对象。
  *
  * @param matrix 指向待旋转四阶矩阵对象的指针。
  * @param rotate 指向旋转对象的指针。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4_Rotate(ArkUI_Matrix4* matrix, const ArkUI_Matrix4RotationOptions* rotate);
 
 /**
  * @brief 对原始矩阵应用倾斜变换以获取倾斜后的矩阵。每次倾斜变换都是在先前的矩阵上累积的。变换后将修改输入的矩阵对象。
  *
  * @param matrix 指向待倾斜四阶矩阵对象的指针。
  * @param skewX x方向的倾斜系数。
  * @param skewY y方向的倾斜系数。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4_Skew(ArkUI_Matrix4* matrix, const float skewX, const float skewY);
 
 /**
  * @brief 计算一个点经过矩阵变换后的新坐标位置。
  *
  * @param matrix 指向四阶矩阵对象的指针。
  * @param oriPoint 指向原始坐标点的指针。
  * @param result 指向结果点的指针。不能为空。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4_TransformPoint(const ArkUI_Matrix4* matrix, const ArkUI_PointF* oriPoint, ArkUI_PointF* result);
 
 /**
  * @brief 将一个多边形的顶点坐标映射到另一个多边形的顶点坐标，并计算所需的矩阵。
  * 
  * @param matrix 指向四阶矩阵对象的指针，用于存放结果矩阵。
  * @param src 指向原始多边形坐标点数组的指针。数组长度应至少为pointCount。
  * @param dst 指向映射后多边形坐标点数组的指针。数组长度应至少为pointCount。
  * @param pointCount 多边形点的数量，必须是0、1、2、3或4中的一个值。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4_SetPolyToPoly(ArkUI_Matrix4* matrix, const ArkUI_PointF* src, const ArkUI_PointF* dst, const uint32_t pointCount);
 
 /**
  * @brief 获取四阶矩阵的16个元素。
  *
  * @param matrix 指向四阶矩阵对象的指针。
  * @param result 指向可容纳16个浮点数的数组的指针。不能为空。
  * @return 错误码。
  *     <br>如果操作成功，返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
  *     <br>如果发生参数异常，返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
  * @since 24
  */
 ArkUI_ErrorCode OH_ArkUI_Matrix4_GetElements(const ArkUI_Matrix4* matrix, float* result);
 
 #ifdef __cplusplus
 }
 #endif
 
 #endif // ARKUI_NATIVE_TYPE_VISUAL_H
 /** @} */
 
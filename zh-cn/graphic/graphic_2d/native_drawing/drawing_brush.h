/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup Drawing
 * @{
 *
 * @brief Drawing模块提供包括2D图形渲染、文字绘制和图片显示等功能函数。
 * <br>本模块采用屏幕物理像素单位px。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file drawing_brush.h
 *
 * @brief 文件中定义了与画刷相关的功能函数。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_BRUSH_H
#define C_INCLUDE_DRAWING_BRUSH_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 声明色彩空间管理对象，提供获取色彩空间基础属性的能力。
 *
 * @since 20
 */
typedef struct OH_NativeColorSpaceManager OH_NativeColorSpaceManager;

/**
 * @brief 用于创建一个画刷对象。调用本接口创建的画刷对象，
 * 在使用完毕后必须调用{@link OH_Drawing_BrushDestroy}销毁并回收内存，否则会导致内存泄漏。
 *
 * @return 函数会返回一个指针，指针指向创建的画刷对象。如果返回NULL，表示创建失败；可能的原因是可用内存不足。
 * @since 8
 * @version 1.0
 */
OH_Drawing_Brush* OH_Drawing_BrushCreate(void);

/**
 * @brief 拷贝一个已有画刷对象，创建其画刷对象副本{@link OH_Drawing_Brush}。调用本接口创建的画刷对象，
 * 在使用完毕后必须调用{@link OH_Drawing_BrushDestroy}销毁并回收内存，
 * 否则会导致内存泄漏。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>brush为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param brush 指向画刷对象的指针。
 * @return 函数会返回一个指针，指针指向创建的画刷对象副本{@link OH_Drawing_Brush}。如果返回NULL，表示创建失败；
 * 可能的原因是可用内存不足，或者是brush为NULL。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Brush* OH_Drawing_BrushCopy(OH_Drawing_Brush* brush);

/**
 * @brief 用于销毁画刷对象并回收该对象占用的内存。
 * 应与{@link OH_Drawing_BrushCreate}或{@link OH_Drawing_BrushCopy}配对使用，对已创建或拷贝得到的画刷对象进行释放，
 * 避免内存泄漏。
 *
 * @param brush 指向画刷对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_BrushDestroy(OH_Drawing_Brush* brush);

/**
 * @brief 用于获取画刷是否设置抗锯齿属性，如果为真则说明画刷会启用抗锯齿功能，在绘制图形时会对图形的边缘像素进行半透明的模糊处理。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>brush为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param brush 指向画刷对象的指针。
 * @return 函数返回画刷对象是否设置抗锯齿属性，返回真则设置了抗锯齿，返回假则没有设置抗锯齿。
 * @since 8
 * @version 1.0
 */
bool OH_Drawing_BrushIsAntiAlias(const OH_Drawing_Brush* brush);

/**
 * @brief 用于设置画刷的抗锯齿属性，设置为真则画刷在绘制图形时会对图形的边缘像素进行半透明的模糊处理。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>brush为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param brush 指向画刷对象的指针。
 * @param antiAlias 真为抗锯齿，假则不做抗锯齿处理。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_BrushSetAntiAlias(OH_Drawing_Brush* brush, bool antiAlias);

/**
 * @brief 用于获取画刷的颜色属性，颜色属性描述了画刷填充图形时使用的颜色，用一个32位（ARGB）的变量表示。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>brush为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param brush 指向画刷对象的指针。
 * @return 函数返回一个描述颜色的32位（ARGB）变量，各颜色通道取值范围为[0, 255]。
 * @since 8
 * @version 1.0
 */
uint32_t OH_Drawing_BrushGetColor(const OH_Drawing_Brush* brush);

/**
 * @brief 用于设置画刷的颜色属性，颜色属性描述了画刷填充图形时使用的颜色，用一个32位（ARGB）的变量表示。
 * 当需要色彩空间管理或高精度颜色表示时，建议优先使用{@link OH_Drawing_BrushSetColor4f}。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>brush为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param brush 指向画刷对象的指针。
 * @param color 描述颜色的32位（ARGB）变量，各颜色通道取值范围为[0, 255]。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_BrushSetColor(OH_Drawing_Brush* brush, uint32_t color);

/**
 * @brief 用于获取画刷的透明度值。画刷在填充形状时透明通道会使用该值。
 * 当画刷颜色通过{@link OH_Drawing_BrushSetColor4f}设置时，建议使用
 * {@link OH_Drawing_BrushGetAlphaFloat}获取透明度以避免精度丢失。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>brush为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param brush 指向画刷对象的指针。
 * @return 返回一个8位无符号整数，用于表示透明度值，取值范围为[0, 255]，0表示完全透明，255表示完全不透明。
 * @since 11
 * @version 1.0
 */
uint8_t OH_Drawing_BrushGetAlpha(const OH_Drawing_Brush* brush);

/**
 * @brief 为画刷设置透明度值。画刷在填充形状时透明通道会使用该值。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>brush为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param brush 指向画刷对象的指针。
 * @param alpha 表示要设置的透明度值，取值范围为[0, 255]的8位无符号整数，0表示完全透明，255表示完全不透明。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_BrushSetAlpha(OH_Drawing_Brush* brush, uint8_t alpha);

/**
 * @brief 设置画刷的颜色。画刷使用该颜色填充形状。
 * <br>与{@link OH_Drawing_BrushSetColor}相比，本接口使用浮点数表示ARGB分量，精度更高，
 * 并支持通过colorSpaceManager指定色彩空间；当需要色彩空间管理或高精度颜色表示时，
 * 优先使用本接口。
 * <br>颜色采用浮点数表示的ARGB格式，色彩空间由{@link OH_NativeColorSpaceManager}指定。
 * <br>如果colorSpaceManager为NULL，使用sRGB（基于IEC 61966-2.1:1999的标准红绿蓝色彩空间）色彩空间作为默认值。
 *
 * @param brush 表示指向{@link OH_Drawing_Brush}对象的指针。
 * @param a 表示颜色中的透明度值，用[0.0, 1.0]之间的浮点数表示，大于1.0时，取1.0，小于0.0时，取0.0。
 * @param r 表示颜色中的红色分量，用[0.0, 1.0]之间的浮点数表示，大于1.0时，取1.0，小于0.0时，取0.0。
 * @param g 表示颜色中的绿色分量，用[0.0, 1.0]之间的浮点数表示，大于1.0时，取1.0，小于0.0时，取0.0。
 * @param b 表示颜色中的蓝色分量，用[0.0, 1.0]之间的浮点数表示，大于1.0时，取1.0，小于0.0时，取0.0。
 * @param colorSpaceManager 表示指向{@link OH_NativeColorSpaceManager}对象的指针。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数brush为NULL。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_BrushSetColor4f(OH_Drawing_Brush* brush, float a, float r, float g, float b,
    OH_NativeColorSpaceManager* colorSpaceManager);

/**
 * @brief 用于获取画刷颜色的透明度值，以浮点数形式表示。与{@link OH_Drawing_BrushGetAlpha}相比，
 * 本接口返回浮点数表示的透明度，精度更高；当画刷颜色通过
 * {@link OH_Drawing_BrushSetColor4f}设置时，应使用本接口获取透明度以避免精度丢失。
 *
 * @param brush 表示指向{@link OH_Drawing_Brush}对象的指针。
 * @param a 表示指向浮点数的指针，用于接收画刷颜色的透明度值，取值范围为[0.0, 1.0]。调用前需确保指针指向有效内存。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数brush或a为NULL。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_BrushGetAlphaFloat(const OH_Drawing_Brush* brush, float* a);

/**
 * @brief 用于获取画刷颜色的红色分量，以浮点数形式表示。与{@link OH_Drawing_BrushGetColor}相比，
 * 本接口以浮点数返回颜色分量，精度更高；当画刷颜色通过
 * {@link OH_Drawing_BrushSetColor4f}设置时，应使用本接口获取红色分量以避免精度丢失。
 *
 * @param brush 表示指向{@link OH_Drawing_Brush}对象的指针。
 * @param r 表示指向浮点数的指针，用于接收画刷颜色的红色分量值，取值范围为[0.0, 1.0]。调用前需确保指针指向有效内存。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数brush或r为NULL。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_BrushGetRedFloat(const OH_Drawing_Brush* brush, float* r);

/**
 * @brief 用于获取画刷颜色的绿色分量，以浮点数形式表示。与{@link OH_Drawing_BrushGetColor}相比，
 * 本接口以浮点数返回颜色分量，精度更高；当画刷颜色通过
 * {@link OH_Drawing_BrushSetColor4f}设置时，应使用本接口获取绿色分量以避免精度丢失。
 *
 * @param brush 表示指向{@link OH_Drawing_Brush}对象的指针。
 * @param g 表示指向浮点数的指针，用于接收画刷颜色的绿色分量值，取值范围为[0.0, 1.0]。调用前需确保指针指向有效内存。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数brush或g为NULL。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_BrushGetGreenFloat(const OH_Drawing_Brush* brush, float* g);

/**
 * @brief 用于获取画刷颜色的蓝色分量，以浮点数形式表示。与{@link OH_Drawing_BrushGetColor}相比，
 * 本接口以浮点数返回颜色分量，精度更高；当画刷颜色通过
 * {@link OH_Drawing_BrushSetColor4f}设置时，应使用本接口获取蓝色分量以避免精度丢失。
 *
 * @param brush 表示指向{@link OH_Drawing_Brush}对象的指针。
 * @param b 表示指向浮点数的指针，用于接收画刷颜色的蓝色分量值，取值范围为[0.0, 1.0]。调用前需确保指针指向有效内存。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数brush或b为NULL。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_BrushGetBlueFloat(const OH_Drawing_Brush* brush, float* b);

/**
 * @brief 为画刷设置着色器效果。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>brush为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param brush 指向画刷对象的指针。
 * @param shaderEffect 表示指向着色器对象的指针，为NULL表示清空画刷的着色器效果。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_BrushSetShaderEffect(OH_Drawing_Brush* brush, OH_Drawing_ShaderEffect* shaderEffect);

/**
 * @brief 为画刷设置阴影层，设置的阴影层效果当前仅在绘制文字时生效。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>brush为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param brush 指向画刷对象的指针。
 * @param shadowLayer 表示指向阴影层的指针，为NULL表示清空画刷的阴影层效果。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_BrushSetShadowLayer(OH_Drawing_Brush* brush, OH_Drawing_ShadowLayer* shadowLayer);

/**
 * @brief 为画刷设置滤波器{@link OH_Drawing_Filter}。滤波器是一个容器，可以承载蒙版滤波器和颜色滤波器。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>brush为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param brush 指向画刷对象的指针。
 * @param filter 表示指向滤波器对象的指针，为NULL表示清空画刷滤波器。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_BrushSetFilter(OH_Drawing_Brush* brush, OH_Drawing_Filter* filter);

/**
 * @brief 从画刷获取滤波器{@link OH_Drawing_Filter}。滤波器是一个容器，可以承载蒙版滤波器和颜色滤波器。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>brush、filter任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param brush 指向画刷对象{@link OH_Drawing_Brush}的指针。
 * @param filter 表示指向滤波器对象{@link OH_Drawing_Filter}的指针，用于接收从画刷中获取的滤波器。调用前需分配好内存，
 * 由函数写入结果。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_BrushGetFilter(OH_Drawing_Brush* brush, OH_Drawing_Filter* filter);

/**
 * @brief 为画刷设置混合模式，通过指定的混合模式枚举决定画刷在绘制时源像素与目标像素的合成方式。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>brush为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * <br>blendMode不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param brush 指向画刷对象{@link OH_Drawing_Brush}的指针。
 * @param blendMode 要设置的混合模式，用于指定画刷在绘制时源像素与目标像素的混合方式。
 * 枚举类型{@link OH_Drawing_BlendMode}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_BrushSetBlendMode(OH_Drawing_Brush* brush, OH_Drawing_BlendMode blendMode);

/**
 * @brief 将画刷重置至初始状态，清空所有已设置的属性。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>brush为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param brush 指向画刷对象{@link OH_Drawing_Brush}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_BrushReset(OH_Drawing_Brush* brush);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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
 * @addtogroup ArkUI_RenderNodeUtils
 * @{
 *
 * @brief Provides RenderNode capabilities of ArkUI on the native side, such as RenderNode creation and destruction,
 * tree node operations, and attribute setting.
 *
 * @since 20
 */

/**
 * @file native_render.h
 *
 * @brief 提供NativeRender接口的类型定义。更多详细介绍请参考{@link 构建渲染节点}。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 20
 */

#ifndef ARKUI_NATIVE_RENDER_H
#define ARKUI_NATIVE_RENDER_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义渲染节点指针，用于在ArkUI_RenderNodeUtils相关接口中表示和传递渲染节点对象。
 *
 * @since 20
 */
typedef struct ArkUI_RenderNode* ArkUI_RenderNodeHandle;

/**
 * @brief 定义渲染内容修改器指针，用于引用内容修改器。内容修改器可挂载到渲染节点，并附加渲染属性或设置onDraw回调。
 *
 * @since 20
 */
typedef struct ArkUI_RenderContentModifier* ArkUI_RenderContentModifierHandle;

/**
 * @brief 定义ArkUI原生浮点渲染属性指针，用于创建、传递并管理目标内容修改器上的浮点属性。
 *
 * @since 20
 */
typedef struct ArkUI_FloatProperty* ArkUI_FloatPropertyHandle;

/**
 * @brief 定义二维向量属性指针，用于在ArkUI原生渲染属性接口中创建、附加、设置、获取和释放二维向量属性。
 *
 * @since 20
 */
typedef struct ArkUI_Vector2Property* ArkUI_Vector2PropertyHandle;

/**
 * @brief 定义颜色属性指针，用于表示ArkUI中的颜色属性。
 *
 * @since 20
 */
typedef struct ArkUI_ColorProperty* ArkUI_ColorPropertyHandle;

/**
 * @brief 定义可动画的浮点数属性指针。
 *
 * @since 20
 */
typedef struct ArkUI_FloatAnimatableProperty* ArkUI_FloatAnimatablePropertyHandle;

/**
 * @brief 定义可动画的二维向量属性指针。
 *
 * @since 20
 */
typedef struct ArkUI_Vector2AnimatableProperty* ArkUI_Vector2AnimatablePropertyHandle;

/**
 * @brief 定义可动画的颜色属性指针。
 *
 * @since 20
 */
typedef struct ArkUI_ColorAnimatableProperty* ArkUI_ColorAnimatablePropertyHandle;

/**
 * @brief 定义矩形形状配置项，用于在ArkUI渲染节点中描述矩形或椭圆形的形状范围，可作为创建遮罩或裁剪配置项的输入。
 *
 * @since 20
 */
typedef struct ArkUI_RectShape ArkUI_RectShapeOption;

/**
 * @brief 定义边框样式配置项，用于为渲染节点的各边设置边框样式。
 *
 * @since 20
 */
typedef struct ArkUI_NodeBorderStyle ArkUI_NodeBorderStyleOption;

/**
 * @brief 定义边框宽度配置项，用于配置渲染节点各边的边框宽度。
 *
 * @since 20
 */
typedef struct ArkUI_NodeBorderWidth ArkUI_NodeBorderWidthOption;

/**
 * @brief 定义边框颜色配置项。
 *
 * @since 20
 */
typedef struct ArkUI_NodeBorderColor ArkUI_NodeBorderColorOption;

/**
 * @brief 定义边框圆角配置项。
 *
 * @since 20
 */
typedef struct ArkUI_NodeBorderRadius ArkUI_NodeBorderRadiusOption;

/**
 * @brief 定义圆形形状配置项，用于在ArkUI_RenderNodeUtils中创建圆形形状，并配置圆心坐标和半径，作为RenderNode的遮罩或裁剪形状。
 *
 * @since 20
 */
typedef struct ArkUI_CircleShape ArkUI_CircleShapeOption;

/**
 * @brief 定义圆角矩形形状配置项，用于配置圆角矩形形状，并可用于创建渲染节点遮罩或裁剪。
 *
 * @since 20
 */
typedef struct ArkUI_RoundRectShape ArkUI_RoundRectShapeOption;

/**
 * @brief 定义自定义绘制路径配置项，用于为渲染节点创建基于路径的遮罩或裁剪效果。
 *
 * @since 20
 */
typedef struct ArkUI_CommandPath ArkUI_CommandPathOption;

/**
 * @brief 定义节点遮罩配置项。
 *
 * @since 20
 */
typedef struct ArkUI_RenderNodeMaskOption ArkUI_RenderNodeMaskOption;

/**
 * @brief 定义节点裁剪配置项。
 *
 * @since 20
 */
typedef struct ArkUI_RenderNodeClipOption ArkUI_RenderNodeClipOption;

/**
 * @brief 定义模糊样式结构体。
 *
 * @since 26.0.0
 */
typedef struct ArkUI_RenderBlurStyleOption ArkUI_RenderBlurStyleOption;

/**
 * @brief 创建一个模糊样式对象。
 *
 * @return 模糊样式对象的指针。模糊半径默认值是0.0。
 * @since 26.0.0
 */
ArkUI_RenderBlurStyleOption* OH_ArkUI_RenderNodeUtils_CreateBlurStyleOption();

/**
 * @brief 销毁一个模糊样式对象。
 *
 * @param option {@link ArkUI_RenderBlurStyleOption}指针，待销毁的目标模糊样式对象的指针。
 * @since 26.0.0
 */
void OH_ArkUI_RenderNodeUtils_DisposeBlurStyleOption(ArkUI_RenderBlurStyleOption* option);

/**
 * @brief 为目标模糊样式设置模糊半径。
 *
 * @param option {@link ArkUI_RenderBlurStyleOption}指针，要设置模糊半径的目标模糊样式的指针。
 * @param radius 要设置的模糊半径。取值范围：[0, +∞)。单位：px。模糊半径用于控制模糊的密度，即半径越大，模糊处理的密度越大。设置0即表示不进行模糊处理。对于背景模糊处理，半径达到80，即可实现良好的磨砂玻璃效果。
 *     应避免使用超过200像素的模糊半径，否则将导致性能下降。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBlurStyleOptionRadius(ArkUI_RenderBlurStyleOption* option, float radius);

/**
 * @brief 为渲染节点设置背景模糊样式。
 *
 * @param node ArkUI_RenderNodeHandle指针，要设置背景模糊样式的目标渲染节点。
 * @param option {@link ArkUI_RenderBlurStyleOption}指针，要设置的模糊样式的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBackgroundBlurOption(
    ArkUI_RenderNodeHandle node, ArkUI_RenderBlurStyleOption* option);

/**
 * @brief 为渲染节点重置背景模糊样式。重置后无背景模糊样式。
 *
 * @param node ArkUI_RenderNodeHandle指针，要重置背景模糊样式的目标渲染节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_ResetBackgroundBlurOption(ArkUI_RenderNodeHandle node);

/**
 * @brief 为渲染节点设置前景模糊样式。
 *
 * @param node ArkUI_RenderNodeHandle指针，要设置前景模糊样式的目标渲染节点。
 * @param option {@link ArkUI_RenderBlurStyleOption}指针，要设置的模糊样式的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_SetForegroundBlurOption(
    ArkUI_RenderNodeHandle node, ArkUI_RenderBlurStyleOption* option);

/**
 * @brief 为渲染节点重置前景模糊样式。重置后无前景模糊样式。
 *
 * @param node ArkUI_RenderNodeHandle指针，要重置前景模糊样式的目标渲染节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_ResetForegroundBlurOption(ArkUI_RenderNodeHandle node);

/**
 * @brief 为渲染节点设置内容模糊样式。
 *
 * @param node ArkUI_RenderNodeHandle指针，要设置内容模糊样式的目标渲染节点。
 * @param option {@link ArkUI_RenderBlurStyleOption}指针，要设置的模糊样式的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_SetContentBlurOption(ArkUI_RenderNodeHandle node, ArkUI_RenderBlurStyleOption* option);

/**
 * @brief 为渲染节点重置内容模糊样式。重置后无内容模糊样式。
 *
 * @param node ArkUI_RenderNodeHandle指针，要重置内容模糊样式的目标渲染节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_ResetContentBlurOption(ArkUI_RenderNodeHandle node);

/**
 * @brief 向父自定义节点添加子渲染节点。
 *
 * @param node 目标父节点。
 * @param child 待添加的子渲染节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_NOT_CUSTOM_NODE} 目标节点非自定义节点。
 *     <br>{@link ARKUI_ERROR_CODE_CHILD_EXISTED} 目标节点已存在子节点。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_PARENT_EXISTED} 目标渲染节点存在父节点。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE} 当前渲染节点从FrameNode中获取且该FrameNode已被取消接纳为附属节点或销毁。从API
 *     version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AddRenderNode(ArkUI_NodeHandle node, ArkUI_RenderNodeHandle child);

/**
 * @brief 从父节点移除指定的子渲染节点。
 *
 * @param node 目标父节点。
 * @param child 移除的目标子渲染节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_NOT_CUSTOM_NODE} 目标节点非自定义节点。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_RemoveRenderNode(ArkUI_NodeHandle node, ArkUI_RenderNodeHandle child);

/**
 * @brief 清除父节点内的子渲染节点。
 *
 * @param node 目标父节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_NOT_CUSTOM_NODE} 目标节点非自定义节点。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_ClearRenderNodeChildren(ArkUI_NodeHandle node);

/**
 * @brief 标记目标节点，触发其生命周期和子节点的重新渲染。
 *
 * @param node 目标节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_Invalidate(ArkUI_NodeHandle node);

/**
 * @brief 创建渲染节点。
 *
 * @return 目标渲染节点。
 * @since 20
 */
ArkUI_RenderNodeHandle OH_ArkUI_RenderNodeUtils_CreateNode();

/**
 * @brief 销毁渲染节点。
 *
 * @param node 目标渲染节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_DisposeNode(ArkUI_RenderNodeHandle node);

/**
 * @brief 向目标父渲染节点上添加子节点。
 *
 * @param node 目标父渲染节点。
 * @param child 目标添加子渲染节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE} 当前渲染节点从FrameNode中获取且该FrameNode已被取消接纳为附属节点或销毁。从API
 *     version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AddChild(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle child);

/**
 * @brief 向父节点的目标子节点后添加子节点。
 *
 * @param node 目标父渲染节点。
 * @param child 待添加的子渲染节点。
 * @param sibling 目标子节点，用于确定插入位置的参考兄弟渲染节点。若该节点不在`node`的当前子节点列表中，则将`child`追加到末尾。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE} 当前渲染节点从FrameNode中获取且该FrameNode已被取消接纳为附属节点或销毁。从API
 *     version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_InsertChildAfter(
    ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle child, ArkUI_RenderNodeHandle sibling);

/**
 * @brief 从指定渲染节点中移除子节点。
 *
 * @param node 目标父渲染节点。
 * @param child 目标被移除子渲染节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_RemoveChild(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle child);

/**
 * @brief 清空指定渲染节点的所有子节点。
 *
 * @param node 目标渲染节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_ClearChildren(ArkUI_RenderNodeHandle node);

/**
 * @brief 获取指定索引位置的子节点。
 *
 * @param node 目标父渲染节点。
 * @param index 子节点的从零开始的索引。
 * @param child 用于接收子节点的渲染节点指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST} 未找到对应的渲染子节点。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetChild(ArkUI_RenderNodeHandle node, int32_t index, ArkUI_RenderNodeHandle* child);

/**
 * @brief 获取指定渲染节点的第一个子节点。
 *
 * @param node 目标渲染节点。
 * @param child 用于接收第一个子节点的渲染节点指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST} 未找到对应的渲染子节点。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetFirstChild(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle* child);

/**
 * @brief 获取指定节点的下一个兄弟节点。
 *
 * @param node 参考节点。
 * @param sibling 用于接收下一个兄弟节点的渲染节点指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST} 未找到对应的渲染子节点。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetNextSibling(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle* sibling);

/**
 * @brief 获取指定节点的上一个兄弟节点。
 *
 * @param node 参考节点。
 * @param sibling 用于接收上一个兄弟节点的渲染节点指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST} 未找到对应的渲染子节点。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetPreviousSibling(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle* sibling);

/**
 * @brief 获取父渲染节点的所有子渲染节点，调用者负责释放返回的子节点数组。
 *
 * @param node 目标父渲染节点。
 * @param children 用于存储所有子渲染节点的指针数组。
 * @param count 用于存储获取到的子节点数量的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetChildren(
    ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle** children, int32_t* count);

/**
 * @brief 获取指定渲染节点的子渲染节点数量。
 *
 * @param node 目标父渲染节点。
 * @param count 用于存储子节点数量的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetChildrenCount(ArkUI_RenderNodeHandle node, int32_t* count);

/**
 * @brief 为渲染节点设置背景颜色。
 *
 * @param node 目标渲染节点。
 * @param color ARGB 颜色值（32 位无符号整数）。
 *     默认值：0x00000000。
 *     <br>**颜色字节布局说明：**
 *     <br>- 位24-31：Alpha通道（0x00完全透明，0xFF完全不透明）。
 *     <br>- 位16-23：红色通道。
 *     <br>- 位8-15：绿色通道。
 *     <br>- 位0-7：蓝色通道。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBackgroundColor(ArkUI_RenderNodeHandle node, uint32_t color);

/**
 * @brief 获取渲染节点的背景颜色。
 *
 * @param node 目标渲染节点。
 * @param color 用于存储获取到的 RGBA 颜色值的整数指针。
 *     默认值：0x00000000。
 *     <br>**颜色字节布局说明：**
 *     <br>- 位24-31：Alpha通道（0x00完全透明，0xFF完全不透明）。
 *     <br>- 位16-23：红色通道。
 *     <br>- 位8-15：绿色通道。
 *     <br>- 位0-7：蓝色通道。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBackgroundColor(ArkUI_RenderNodeHandle node, uint32_t* color);

/**
 * @brief 设置是否对当前渲染节点裁剪。
 *
 * @param node 目标渲染节点。
 * @param clipToFrame 整数（1 = 裁剪到框架，0 = 不裁剪）。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} 参数值超出范围。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetClipToFrame(ArkUI_RenderNodeHandle node, int32_t clipToFrame);

/**
 * @brief 获取是否对当前渲染节点裁剪。
 *
 * @param node 目标渲染节点。
 * @param clipToFrame 用于接收裁剪状态（1 或 0）的整数指针。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetClipToFrame(ArkUI_RenderNodeHandle node, int32_t* clipToFrame);

/**
 * @brief 设置是否对当前渲染节点边界裁剪。
 *
 * @param node 目标渲染节点。
 * @param clipToBounds 裁剪标志（1：裁剪到边界，0：不裁剪）。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} 参数值超出范围。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetClipToBounds(ArkUI_RenderNodeHandle node, int32_t clipToBounds);

/**
 * @brief 获取是否对当前渲染节点边界裁剪。
 *
 * @param node 目标渲染节点。
 * @param clipToBounds 整数指针（1 = 根据边界裁剪，0 = 不裁剪）。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetClipToBounds(ArkUI_RenderNodeHandle node, int32_t* clipToBounds);

/**
 * @brief 为渲染节点设置不透明度值。
 *
 * @param node 目标渲染节点。
 * @param opacity 不透明度值（0.0-1.0）。
 *     默认值：1。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} 参数值超出范围。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetOpacity(ArkUI_RenderNodeHandle node, float opacity);

/**
 * @brief 获取渲染节点的不透明度值。
 *
 * @param node 目标渲染节点。
 * @param opacity 用于接收不透明度值（0.0-1.0）的指针。
 *     默认值：1。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetOpacity(ArkUI_RenderNodeHandle node, float* opacity);

/**
 * @brief 为渲染节点设置尺寸。
 *
 * @param node 目标渲染节点。
 * @param width 宽度值（以像素为单位）。
 *     默认值：0，单位：px。取值大于等于0，传入负值时返回{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE}。
 * @param height 高度值（以像素为单位）。
 *     默认值：0，单位：px。取值大于等于0，传入负值时返回{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} 参数值超出范围。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetSize(ArkUI_RenderNodeHandle node, int32_t width, int32_t height);

/**
 * @brief 获取渲染节点的尺寸。
 *
 * @param node 目标渲染节点。
 * @param width 用于接收宽度值（以像素为单位）的指针。
 *     默认值：0，单位：px。
 * @param height 用于接收高度值（以像素为单位）的指针。
 *     默认值：0，单位：px。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetSize(ArkUI_RenderNodeHandle node, int32_t* width, int32_t* height);

/**
 * @brief 为渲染节点设置位置坐标。
 *
 * @param node 目标渲染节点。
 * @param x X坐标值（以像素为单位）。
 *     默认值：0，单位：px。
 * @param y Y坐标值（以像素为单位）。
 *     默认值：0，单位：px。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetPosition(ArkUI_RenderNodeHandle node, int32_t x, int32_t y);

/**
 * @brief 获取渲染节点的位置坐标。该坐标是渲染节点布局后相对父节点的位置偏移，单位为px。该坐标是父节点对该节点进行布局之后的结果，因此布局之后生效的offset属性和不参与布局的position属性不影响该坐标。
 *
 * @param node 目标渲染节点。
 * @param x 用于接收X坐标值（以像素为单位）的指针。
 *     默认值：0，单位：px。
 * @param y 用于接收Y坐标值（以像素为单位）的指针。
 *     默认值：0，单位：px。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetPosition(ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y);

/**
 * @brief 为渲染节点的变换设置中心点。
 *
 * @param node 目标渲染节点。
 * @param x 中心点的X坐标（标准取值范围：0.0-1.0）。
 *     默认值：0.5。
 * @param y 中心点的Y坐标（标准取值范围：0.0-1.0）。
 *     默认值：0.5。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetPivot(ArkUI_RenderNodeHandle node, float x, float y);

/**
 * @brief 获取渲染节点的中心点坐标。
 *
 * @param node 目标渲染节点。
 * @param x 用于接收中心点X坐标的指针。
 *     默认值：0.5。
 * @param y 用于接收中心点Y坐标的指针。
 *     默认值：0.5。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetPivot(ArkUI_RenderNodeHandle node, float* x, float* y);

/**
 * @brief 为渲染节点设置缩放因子。
 *
 * @param node 目标渲染节点。
 * @param x 水平缩放因子。
 *     默认值：1。
 * @param y 垂直缩放因子。
 *     默认值：1。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetScale(ArkUI_RenderNodeHandle node, float x, float y);

/**
 * @brief 获取渲染节点的缩放因子。
 *
 * @param node 目标渲染节点。
 * @param x 用于接收水平缩放因子的指针。
 *     默认值：1。
 * @param y 用于接收垂直缩放因子的指针。
 *     默认值：1。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetScale(ArkUI_RenderNodeHandle node, float* x, float* y);

/**
 * @brief 为渲染节点设置平移偏移量。
 *
 * @param node 目标渲染节点。
 * @param x 水平平移量（以像素为单位）。
 *     默认值：0。
 * @param y 垂直平移量（以像素为单位）。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetTranslation(ArkUI_RenderNodeHandle node, float x, float y);

/**
 * @brief 获取渲染节点的平移偏移量。
 *
 * @param node 目标渲染节点。
 * @param x 用于接收水平平移量的指针。
 *     默认值：0。
 * @param y 用于接收垂直平移量的指针。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetTranslation(ArkUI_RenderNodeHandle node, float* x, float* y);

/**
 * @brief 为渲染节点设置旋转角度。
 *
 * @param node 目标渲染节点。
 * @param x 绕X轴的旋转角度（以度为单位）。
 *     默认值：0。
 * @param y 绕Y轴的旋转角度（以度为单位）。
 *     默认值：0。
 * @param z 绕Z轴的旋转角度（以度为单位）。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetRotation(ArkUI_RenderNodeHandle node, float x, float y, float z);

/**
 * @brief 获取渲染节点的旋转角度。
 *
 * @param node 目标渲染节点。
 * @param x 用于接收绕X轴旋转角度（以度为单位）的指针。
 *     默认值：0。
 * @param y 用于接收绕Y轴旋转角度（以度为单位）的指针。
 *     默认值：0。
 * @param z 用于接收绕Z轴旋转角度（以度为单位）的指针。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetRotation(ArkUI_RenderNodeHandle node, float* x, float* y, float* z);

/**
 * @brief 为渲染节点设置变换矩阵。
 *
 * @param node 目标渲染节点。
 * @param matrix 4x4 变换矩阵的浮点数数组（16 个连续值）。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} 参数超出范围。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetTransform(ArkUI_RenderNodeHandle node, float* matrix);

/**
 * @brief 为渲染节点设置阴影颜色。
 *
 * @param node 目标渲染节点。
 * @param color ARGB 颜色值（32位无符号整数）。
 *     默认值：0x00000000。
 *     <br>**颜色字节布局说明：**
 *     <br>- 位24-31：Alpha通道（0x00完全透明，0xFF完全不透明）。
 *     <br>- 位16-23：红色通道。
 *     <br>- 位8-15：绿色通道。
 *     <br>- 位0-7：蓝色通道。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowColor(ArkUI_RenderNodeHandle node, uint32_t color);

/**
 * @brief 获取渲染节点的阴影颜色。
 *
 * @param node 目标渲染节点。
 * @param color 用于存储获取到的RGBA颜色值的整数指针。
 *     默认值：0xFF000000。
 *     <br>**颜色字节布局说明：**
 *     <br>- 位24-31：Alpha通道（0x00完全透明，0xFF完全不透明）。
 *     <br>- 位16-23：红色通道。
 *     <br>- 位8-15：绿色通道。
 *     <br>- 位0-7：蓝色通道。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetShadowColor(ArkUI_RenderNodeHandle node, uint32_t* color);

/**
 * @brief 为渲染节点设置阴影偏移量。
 *
 * @param node 目标渲染节点。
 * @param x 水平偏移值（以像素为单位）。
 *     默认值：0。
 * @param y 垂直偏移值（以像素为单位）。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowOffset(ArkUI_RenderNodeHandle node, int32_t x, int32_t y);

/**
 * @brief 获取渲染节点的阴影偏移量。
 *
 * @param node 目标渲染节点。
 * @param x 用于接收水平偏移值的指针。
 *     默认值：0，单位：px。
 * @param y 用于接收垂直偏移值的指针。
 *     默认值：0，单位：px。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetShadowOffset(ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y);

/**
 * @brief 为渲染节点设置阴影透明度。
 *
 * @param node 目标渲染节点。
 * @param alpha 阴影 Alpha 值（0.0-1.0）。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} 参数超出范围。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowAlpha(ArkUI_RenderNodeHandle node, float alpha);

/**
 * @brief 获取渲染节点的阴影透明度。
 *
 * @param node 目标渲染节点。
 * @param alpha 用于接收阴影 Alpha 值的指针。
 *     默认值：1。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetShadowAlpha(ArkUI_RenderNodeHandle node, float* alpha);

/**
 * @brief 为渲染节点设置阴影高度。
 *
 * @param node 目标渲染节点。
 * @param elevation 高度值。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} 参数超出范围。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowElevation(ArkUI_RenderNodeHandle node, float elevation);

/**
 * @brief 获取渲染节点的阴影高度。
 *
 * @param node 目标渲染节点。
 * @param elevation 用于接收高度值的指针。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetShadowElevation(ArkUI_RenderNodeHandle node, float* elevation);

/**
 * @brief 为渲染节点设置阴影半径。
 *
 * @param node 目标渲染节点。
 * @param radius 半径值。
 *     默认值：0。取值大于等于0，传入负值时返回{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} 参数超出范围。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowRadius(ArkUI_RenderNodeHandle node, float radius);

/**
 * @brief 获取渲染节点的阴影半径。
 *
 * @param node 目标渲染节点。
 * @param radius 用于接收半径值的指针。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetShadowRadius(ArkUI_RenderNodeHandle node, float* radius);

/**
 * @brief 为渲染节点设置边框样式。
 *
 * @param node 目标渲染节点。
 * @param borderStyle 边框样式的指针。
 *     结构体指针内默认值：{@link ARKUI_BORDER_STYLE_SOLID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBorderStyle(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderStyleOption* borderStyle);

/**
 * @brief 获取渲染节点的边框样式。
 *
 * @param node 目标渲染节点。
 * @param borderStyle 用于接收边框样式的指针。
 *     结构体指针内默认值：{@link ARKUI_BORDER_STYLE_SOLID}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBorderStyle(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderStyleOption** borderStyle);

/**
 * @brief 为渲染节点设置边框宽度，边框宽度需小于节点尺寸。
 *
 * @param node 目标渲染节点。
 * @param borderWidth 边框宽度的指针。
 *     结构体指针内默认值：0。单位：px。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBorderWidth(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderWidthOption* borderWidth);

/**
 * @brief 获取渲染节点的边框宽度。
 *
 * @param node 目标渲染节点。
 * @param borderWidth 用于接收边框宽度的指针。
 *     结构体指针内默认值：0。单位：px。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBorderWidth(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderWidthOption** borderWidth);

/**
 * @brief 为渲染节点设置边框颜色。
 *
 * @param node 目标渲染节点。
 * @param borderColor 边框颜色的指针。
 *     结构体指针内默认值：0x00000000。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBorderColor(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderColorOption* borderColor);

/**
 * @brief 获取渲染节点的边框颜色。
 *
 * @param node 目标渲染节点。
 * @param borderColor 用于接收边框颜色的指针。
 *     结构体指针内默认值：0x00000000。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBorderColor(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderColorOption** borderColor);

/**
 * @brief 为渲染节点设置边框角半径。
 *
 * @param node 目标渲染节点。
 * @param borderRadius 边框半径的指针。
 *     结构体指针内默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBorderRadius(
    ArkUI_RenderNodeHandle node, ArkUI_NodeBorderRadiusOption* borderRadius);

/**
 * @brief 获取渲染节点的边框角半径。
 *
 * @param node 目标渲染节点。
 * @param borderRadius 用于接收边框半径的指针。
 *     结构体指针内默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBorderRadius(
    ArkUI_RenderNodeHandle node, ArkUI_NodeBorderRadiusOption** borderRadius);

/**
 * @brief 使用遮罩配置为渲染节点应用遮罩。
 *
 * 遮罩创建方式如下：
 * 1. 给遮罩图层增加亮度和线性颜色滤镜。
 * 2. 在该滤镜下绘制遮罩图形。
 * 3. 将原节点图像作为源颜色，遮罩图形为目标颜色，通过{@link BlendMode.SRC_IN}方式混合成Mask图像。
 *
 * @param node 目标渲染节点。
 * @param mask 遮罩配置的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetMask(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeMaskOption* mask);

/**
 * @brief 使用裁剪配置为渲染节点应用裁剪。
 *
 * @param node 目标渲染节点。
 * @param clip 裁剪配置的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetClip(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeClipOption* clip);

/**
 * @brief 标记是否优先绘制该节点及其子节点。
 *
 * @param node 目标渲染节点。
 * @param markNodeGroup 布尔值，是否优先绘制该节点及其子节点。
 *     true：优先绘制节点及其子节点；false：不优先绘制节点及其子节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetMarkNodeGroup(ArkUI_RenderNodeHandle node, bool markNodeGroup);

/**
 * @brief 为渲染节点设置边界。
 *
 * @param node 目标渲染节点。
 * @param x 边界左上角的X坐标（以像素为单位）。
 *     默认值：0。
 * @param y 边界左上角的Y坐标（以像素为单位）。
 *     默认值：0。
 * @param width 边界的宽度（以像素为单位）。
 *     默认值：0。取值大于等于0，传入负值时返回{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE}。
 * @param height 边界的高度（以像素为单位）。
 *     默认值：0。取值大于等于0，传入负值时返回{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} 参数超出范围。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBounds(
    ArkUI_RenderNodeHandle node, int32_t x, int32_t y, int32_t width, int32_t height);

/**
 * @brief 获取渲染节点的边界。
 *
 * @param node 目标渲染节点。
 * @param x 用于接收边界左上角X坐标（以像素为单位）的指针。
 *     默认值：0。
 * @param y 用于接收边界左上角Y坐标（以像素为单位）的指针。
 *     默认值：0。
 * @param width 用于接收边界宽度（以像素为单位）的指针。
 *     默认值：0。
 * @param height 用于接收边界高度（以像素为单位）的指针。
 *     默认值：0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBounds(
    ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y, int32_t* width, int32_t* height);

/**
 * @brief 为渲染节点设置绘制区域，该绘制区域主要用于超出边界导致的绘制问题，建议根据实际绘制范围设置大小。
 *
 * @param node 目标渲染节点。
 * @param x 边界左上角的X坐标（以像素为单位）。
 * @param y 边界左上角的Y坐标（以像素为单位）。
 * @param w 边界的宽度（以像素为单位）。
 * @param h 边界的高度（以像素为单位）。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetDrawRegion(ArkUI_RenderNodeHandle node, float x, float y, float w, float h);

/**
 * @brief 为渲染节点添加内容修改器。
 *
 * @param node 目标渲染节点。
 * @param modifier 内容修改器。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} 目标节点是从一个FrameNode获取的。从API version 22开始支持。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachContentModifier(
    ArkUI_RenderNodeHandle node, ArkUI_RenderContentModifierHandle modifier);

/**
 * @brief 创建内容修改器。
 *
 * @return 内容修改器。
 * @since 20
 */
ArkUI_RenderContentModifierHandle OH_ArkUI_RenderNodeUtils_CreateContentModifier();

/**
 * @brief 释放内容修改器。
 *
 * @param modifier 内容修改器。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeContentModifier(ArkUI_RenderContentModifierHandle modifier);

/**
 * @brief 为目标内容修改器附加浮点属性。
 *
 * @param modifier 为目标内容修改器设置浮点属性。
 * @param property 浮点属性。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachFloatProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_FloatPropertyHandle property);

/**
 * @brief 为目标内容修改器附加二维向量属性。
 *
 * @param modifier 为目标内容修改器设置二维向量属性。
 * @param property 二维向量属性。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachVector2Property(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_Vector2PropertyHandle property);

/**
 * @brief 为目标内容修改器附加颜色属性。
 *
 * @param modifier 为目标内容修改器设置颜色属性。
 * @param property 颜色属性。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachColorProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_ColorPropertyHandle property);

/**
 * @brief 为目标内容修改器附加可动画的浮点属性。
 *
 * @param modifier 为目标内容修改器设置可动画的浮点属性。
 * @param property 可动画的浮点属性。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachFloatAnimatableProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_FloatAnimatablePropertyHandle property);

/**
 * @brief 为目标内容修改器附加可动画的二维向量属性。
 *
 * @param modifier 为目标内容修改器设置可动画的二维向量属性。
 * @param property 可动画的二维向量属性。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachVector2AnimatableProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_Vector2AnimatablePropertyHandle property);

/**
 * @brief 为目标内容修改器附加可动画的颜色属性。
 *
 * @param modifier 为目标内容修改器设置可动画的颜色属性。
 * @param property 可动画的颜色属性。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachColorAnimatableProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_ColorAnimatablePropertyHandle property);

/**
 * @brief 创建浮点属性。
 *
 * @param value 属性值。
 * @return 浮点属性。
 * @since 20
 */
ArkUI_FloatPropertyHandle OH_ArkUI_RenderNodeUtils_CreateFloatProperty(float value);

/**
 * @brief 设置浮点属性的值。
 *
 * @param property 浮点属性。
 * @param value 属性值。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetFloatPropertyValue(ArkUI_FloatPropertyHandle property, float value);

/**
 * @brief 获取浮点属性的值。
 *
 * @param property 浮点属性。
 * @param value 用于接收属性值的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetFloatPropertyValue(ArkUI_FloatPropertyHandle property, float* value);

/**
 * @brief 释放浮点属性。
 *
 * @param property 浮点属性。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeFloatProperty(ArkUI_FloatPropertyHandle property);

/**
 * @brief 创建二维向量属性。
 *
 * @param x 属性的X坐标值。
 * @param y 属性的Y坐标值。
 * @return 二维向量属性。
 * @since 20
 */
ArkUI_Vector2PropertyHandle OH_ArkUI_RenderNodeUtils_CreateVector2Property(float x, float y);

/**
 * @brief 设置二维向量属性的值。
 *
 * @param property 二维向量属性。
 * @param x 属性的X坐标值。
 * @param y 属性的Y坐标值。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetVector2PropertyValue(ArkUI_Vector2PropertyHandle property, float x, float y);

/**
 * @brief 获取二维向量属性的值。
 *
 * @param property 二维向量属性。
 * @param x 用于接收属性X坐标值的指针。
 * @param y 用于接收属性Y坐标值的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetVector2PropertyValue(ArkUI_Vector2PropertyHandle property, float* x, float* y);

/**
 * @brief 释放二维向量属性。
 *
 * @param property 二维向量属性。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeVector2Property(ArkUI_Vector2PropertyHandle property);

/**
 * @brief 创建颜色属性。
 *
 * @param value 属性值。
 * @return 颜色属性。
 * @since 20
 */
ArkUI_ColorPropertyHandle OH_ArkUI_RenderNodeUtils_CreateColorProperty(uint32_t value);

/**
 * @brief 设置颜色属性的值。
 *
 * @param property 颜色属性。
 * @param value 属性值。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetColorPropertyValue(ArkUI_ColorPropertyHandle property, uint32_t value);

/**
 * @brief 获取颜色属性的值。
 *
 * @param property 颜色属性。
 * @param value 用于接收属性值的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetColorPropertyValue(ArkUI_ColorPropertyHandle property, uint32_t* value);

/**
 * @brief 释放颜色属性。
 *
 * @param property 颜色属性。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeColorProperty(ArkUI_ColorPropertyHandle property);

/**
 * @brief 创建可动画的浮点属性。
 *
 * @param value 属性值。
 * @return 可动画的浮点属性。
 * @since 20
 */
ArkUI_FloatAnimatablePropertyHandle OH_ArkUI_RenderNodeUtils_CreateFloatAnimatableProperty(float value);

/**
 * @brief 设置可动画的浮点属性的值。
 *
 * @param property 可动画的浮点属性。
 * @param value 属性值。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetFloatAnimatablePropertyValue(
    ArkUI_FloatAnimatablePropertyHandle property, float value);

/**
 * @brief 获取可动画的浮点属性的值。
 *
 * @param property 可动画的浮点属性。
 * @param value 用于接收属性值的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetFloatAnimatablePropertyValue(
    ArkUI_FloatAnimatablePropertyHandle property, float* value);

/**
 * @brief 释放可动画的浮点属性。
 *
 * @param property 可动画的浮点属性。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeFloatAnimatableProperty(ArkUI_FloatAnimatablePropertyHandle property);

/**
 * @brief 创建可动画的二维向量属性。
 *
 * @param x 属性的X坐标值。
 * @param y 属性的Y坐标值。
 * @return 可动画的二维向量属性。
 * @since 20
 */
ArkUI_Vector2AnimatablePropertyHandle OH_ArkUI_RenderNodeUtils_CreateVector2AnimatableProperty(float x, float y);

/**
 * @brief 设置可动画的二维向量属性的值。
 *
 * @param property 可动画的二维向量属性。
 * @param x 属性的X坐标值。
 * @param y 属性的Y坐标值。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetVector2AnimatablePropertyValue(
    ArkUI_Vector2AnimatablePropertyHandle property, float x, float y);

/**
 * @brief 获取可动画的二维向量属性的值。
 *
 * @param property 可动画的二维向量属性。
 * @param x 用于接收属性X坐标值的指针。
 * @param y 用于接收属性Y坐标值的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetVector2AnimatablePropertyValue(
    ArkUI_Vector2AnimatablePropertyHandle property, float* x, float* y);

/**
 * @brief 释放可动画的二维向量属性。
 *
 * @param property 可动画的二维向量属性。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeVector2AnimatableProperty(ArkUI_Vector2AnimatablePropertyHandle property);

/**
 * @brief 创建可动画的颜色属性。
 *
 * @param value 属性值。
 * @return 可动画的颜色属性。
 * @since 20
 */
ArkUI_ColorAnimatablePropertyHandle OH_ArkUI_RenderNodeUtils_CreateColorAnimatableProperty(uint32_t value);

/**
 * @brief 设置可动画的颜色属性的值。
 *
 * @param property 可动画的颜色属性。
 * @param value 属性值。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetColorAnimatablePropertyValue(
    ArkUI_ColorAnimatablePropertyHandle property, uint32_t value);

/**
 * @brief 获取可动画的颜色属性的值。
 *
 * @param property 可动画的颜色属性。
 * @param value 用于接收属性值的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetColorAnimatablePropertyValue(
    ArkUI_ColorAnimatablePropertyHandle property, uint32_t* value);

/**
 * @brief 释放可动画的颜色属性。
 *
 * @param property 可动画的颜色属性。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeColorAnimatableProperty(ArkUI_ColorAnimatablePropertyHandle property);

/**
 * @brief 设置内容修改器的onDraw函数。
 *
 * @param modifier 目标内容修改器。
 * @param userData 要传递给回调的自定义数据。
 * @param callback The draw event receiver callback.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetContentModifierOnDraw(
    ArkUI_RenderContentModifierHandle modifier, void* userData,
    void (*callback)(ArkUI_DrawContext* context, void* userData));

/**
 * @brief 创建矩形形状。
 *
 * @return 指向矩形形状的指针。
 * @since 20
 */
ArkUI_RectShapeOption* OH_ArkUI_RenderNodeUtils_CreateRectShapeOption();

/**
 * @brief 释放矩形形状。
 *
 * @param option 指向矩形形状的指针。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption(ArkUI_RectShapeOption* option);

/**
 * @brief 设置矩形形状的边缘值。当设置左边界和上边界为负数时，因显示涉及到图层叠加效果，会导致部分超出节点内容部分无法绘制。
 * @param option 指向矩形形状的指针。
 * @param edgeValue 矩形形状的边缘值。
 * @param direction 要设置边缘值的矩形方向。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRectShapeOptionEdgeValue(
    ArkUI_RectShapeOption* option, float edgeValue, ArkUI_EdgeDirection direction);

/**
 * @brief 创建节点边框样式。
 *
 * @return 指向节点边框样式的指针。
 * @since 20
 */
ArkUI_NodeBorderStyleOption* OH_ArkUI_RenderNodeUtils_CreateNodeBorderStyleOption();

/**
 * @brief 释放节点边框样式。
 *
 * @param option 指向节点边框样式的指针。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderStyleOption(ArkUI_NodeBorderStyleOption* option);

/**
 * @brief 设置节点边框样式的边缘值。
 * @param option 指向节点边框样式的指针。
 * @param edgeStyle 节点边框样式的边缘边框样式值。
 * @param direction 边缘的方向。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetNodeBorderStyleOptionEdgeStyle(
    ArkUI_NodeBorderStyleOption* option, ArkUI_BorderStyle edgeStyle, ArkUI_EdgeDirection direction);

/**
 * @brief 创建节点边框宽度。
 *
 * @return 指向节点边框宽度的指针。
 * @since 20
 */
ArkUI_NodeBorderWidthOption* OH_ArkUI_RenderNodeUtils_CreateNodeBorderWidthOption();

/**
 * @brief 释放节点边框宽度。
 *
 * @param option 指向节点边框宽度的指针。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderWidthOption(ArkUI_NodeBorderWidthOption* option);

/**
 * @brief 设置节点边框宽度的边缘值。
 *
 * @param option 指向节点边框宽度的指针。
 * @param edgeWidth 节点边框宽度的边缘宽度值。
 *     <br>取值范围：[0, +∞)
 * @param direction 边缘的方向。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetNodeBorderWidthOptionEdgeWidth(
    ArkUI_NodeBorderWidthOption* option, float edgeWidth, ArkUI_EdgeDirection direction);

/**
 * @brief 创建节点边框颜色。
 *
 * @return 指向节点边框颜色的指针。
 * @since 20
 */
ArkUI_NodeBorderColorOption* OH_ArkUI_RenderNodeUtils_CreateNodeBorderColorOption();

/**
 * @brief 释放节点边框颜色。
 *
 * @param option 指向节点边框颜色的指针。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderColorOption(ArkUI_NodeBorderColorOption* option);

/**
 * @brief 设置节点边框颜色的边缘值。
 *
 * @param option 指向节点边框颜色的指针。
 * @param edgeColor 节点边框颜色的边缘颜色值。
 * @param direction 边缘的方向。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetNodeBorderColorOptionEdgeColor(
    ArkUI_NodeBorderColorOption* option, uint32_t edgeColor, ArkUI_EdgeDirection direction);

/**
 * @brief 创建节点边框半径。
 *
 * @return 指向节点边框半径的指针。
 * @since 20
 */
ArkUI_NodeBorderRadiusOption* OH_ArkUI_RenderNodeUtils_CreateNodeBorderRadiusOption();

/**
 * @brief 释放节点边框半径。
 *
 * @param option 指向节点边框半径的指针。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderRadiusOption(ArkUI_NodeBorderRadiusOption* option);

/**
 * @brief 设置节点边框半径的边缘值。请注意，入参cornerRadius为uint32_t，仅支持传入正整数。
 * @param option 指向节点边框半径的指针。
 * @param cornerRadius 节点边框半径的边缘半径值。
 * @param direction 边缘的方向。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetNodeBorderRadiusOptionCornerRadius(
    ArkUI_NodeBorderRadiusOption* option, uint32_t cornerRadius, ArkUI_CornerDirection direction);

/**
 * @brief 创建圆形形状。
 *
 * @return 指向圆形形状的指针。
 * @since 20
 */
ArkUI_CircleShapeOption* OH_ArkUI_RenderNodeUtils_CreateCircleShapeOption();

/**
 * @brief 释放圆形形状。
 *
 * @param option 指向圆形形状的指针。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeCircleShapeOption(ArkUI_CircleShapeOption* option);

/**
 * @brief 设置圆形形状的圆心x轴坐标值。
 *
 * @param option 指向圆形形状的指针。
 * @param centerX 圆心x轴坐标值。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionCenterX(ArkUI_CircleShapeOption* option, float centerX);

/**
 * @brief 设置圆形形状的圆心y轴坐标值。
 *
 * @param option 指向圆形形状的指针。
 * @param centerY 圆心y轴坐标值。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionCenterY(ArkUI_CircleShapeOption* option, float centerY);

/**
 * @brief 设置圆形形状的半径值。
 *
 * @param option 指向圆形形状的指针。
 * @param radius 半径值（以像素为单位）。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionRadius(ArkUI_CircleShapeOption* option, float radius);

/**
 * @brief 创建圆角矩形形状。
 * @return 指向圆角矩形形状的指针。
 * @since 20
 */
ArkUI_RoundRectShapeOption* OH_ArkUI_RenderNodeUtils_CreateRoundRectShapeOption();

/**
 * @brief 释放圆角矩形形状。
 *
 * @param option 指向圆角矩形形状的指针。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeRoundRectShapeOption(ArkUI_RoundRectShapeOption* option);

/**
 * @brief 设置圆角矩形形状的边缘值。
 * @param option 指向圆角矩形形状的指针。
 * @param edgeValue 圆角矩形形状的边缘值。
 * @param direction 要设置边缘值的矩形方向。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionEdgeValue(
    ArkUI_RoundRectShapeOption* option, float edgeValue, ArkUI_EdgeDirection direction);

/**
 * @brief 设置目标角的坐标值。
 * @param option 指向圆角矩形形状的指针。
 * @param x 目标角的X坐标（以像素为单位）。
 * @param y 目标角的Y坐标（以像素为单位）。
 * @param direction 角的方向。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionCornerXY(
    ArkUI_RoundRectShapeOption* option, float x, float y, ArkUI_CornerDirection direction);

/**
 * @brief 创建自定义绘制路径。
 *
 * @return 指向自定义绘制路径的指针。
 * @since 20
 */
ArkUI_CommandPathOption* OH_ArkUI_RenderNodeUtils_CreateCommandPathOption();

/**
 * @brief 释放自定义绘制路径。
 *
 * @param option 指向自定义绘制路径的指针。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeCommandPathOption(ArkUI_CommandPathOption* option);

/**
 * @brief 设置自定义绘制路径的命令值。
 *
 * @param option 指向自定义绘制路径的指针。
 * @param commands 命令值。入参格式为SVG{@link 基础形状}中的\<path>形状标签。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetCommandPathOptionCommands(ArkUI_CommandPathOption* option, char* commands);

/**
 * @brief 从矩形形状创建遮罩。
 *
 * @param shape 指向矩形形状的指针。
 * @return 指向渲染节点遮罩的指针。
 * @since 20
 */
ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromRectShape(
    ArkUI_RectShapeOption* shape);

/**
 * @brief 从圆角矩形形状创建遮罩。
 *
 * @param shape 指向圆角矩形形状的指针。
 * @return 指向渲染节点遮罩的指针。
 * @since 20
 */
ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromRoundRectShape(
    ArkUI_RoundRectShapeOption* shape);

/**
 * @brief 从圆形形状创建遮罩。
 *
 * @param shape 指向圆形形状的指针。
 * @return 指向渲染节点遮罩的指针。
 * @since 20
 */
ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromCircleShape(
    ArkUI_CircleShapeOption* shape);

/**
 * @brief 从椭圆形形状创建遮罩。
 *
 * @param shape 指向椭圆形形状的指针。
 * @return 指向渲染节点遮罩的指针。
 * @since 20
 */
ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromOvalShape(
    ArkUI_RectShapeOption* shape);

/**
 * @brief 从自定义绘制路径创建遮罩。
 *
 * @param path 指向自定义绘制路径的指针。
 * @return 指向渲染节点遮罩的指针。
 * @since 20
 */
ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromCommandPath(
    ArkUI_CommandPathOption* path);

/**
 * @brief 释放渲染节点遮罩。
 *
 * @param option 指向渲染节点遮罩的指针。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption(ArkUI_RenderNodeMaskOption* option);

/**
 * @brief 设置渲染节点遮罩的填充颜色。
 *
 * @param mask 指向渲染节点遮罩的指针。
 * @param fillColor 遮罩的填充颜色。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionFillColor(ArkUI_RenderNodeMaskOption* mask, uint32_t fillColor);

/**
 * @brief 设置渲染节点遮罩的描边颜色。
 *
 * @param mask 指向渲染节点遮罩的指针。
 * @param strokeColor 遮罩的描边颜色。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeColor(
    ArkUI_RenderNodeMaskOption* mask, uint32_t strokeColor);

/**
 * @brief 设置渲染节点遮罩的描边宽度。以边框路径为中心进行相应宽度的绘制。
 *
 * @param mask 指向渲染节点遮罩的指针。
 * @param strokeWidth 遮罩的描边宽度。
 *     <br>取值范围：(0, +∞)，当取值为负数或0时，绘制时会被设定成1像素。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeWidth(ArkUI_RenderNodeMaskOption* mask, float strokeWidth);

/**
 * @brief 从矩形形状创建裁剪。
 *
 * @param shape 指向矩形形状的指针。
 * @return 指向渲染节点裁剪的指针。
 * @since 20
 */
ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromRectShape(
    ArkUI_RectShapeOption* shape);

/**
 * @brief 从圆角矩形形状创建裁剪。
 *
 * @param shape 指向圆角矩形形状的指针。
 * @return 指向渲染节点裁剪的指针。
 * @since 20
 */
ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromRoundRectShape(
    ArkUI_RoundRectShapeOption* shape);

/**
 * @brief 从圆形形状创建裁剪。
 *
 * @param shape 指向圆形形状的指针。
 * @return 指向渲染节点裁剪的指针。
 * @since 20
 */
ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromCircleShape(
    ArkUI_CircleShapeOption* shape);

/**
 * @brief 从椭圆形形状创建裁剪。
 *
 * @param shape 指向椭圆形形状的指针。
 * @return 指向渲染节点裁剪的指针。
 * @since 20
 */
ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromOvalShape(
    ArkUI_RectShapeOption* shape);

/**
 * @brief 从自定义绘制路径创建裁剪。
 *
 * @param path 指向自定义绘制路径的指针。
 * @return 指向渲染节点裁剪的指针。
 * @since 20
 */
ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromCommandPath(
    ArkUI_CommandPathOption* path);

/**
 * @brief 释放渲染节点裁剪。
 *
 * @param option 指向渲染节点裁剪的指针。
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption(ArkUI_RenderNodeClipOption* option);

/**
 * @brief 获取已被接纳为附属节点的目标节点的RenderNode。如果一个RenderNode是通过该接口获取的，调用{@link ArkUI_NativeNodeAPI_1}的{@link disposeNode}
 * 接口主动销毁FrameNode时，需要额外调用{@link OH_ArkUI_RenderNodeUtils_DisposeNode}释放该RenderNode。
 *
 * @param node ArkUI_NodeHandle指针，指定目标节点。
 * @param renderNode ArkUI_RenderNodeHandle*指针，目标节点的RenderNode。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_NOT_ADOPTED_NODE} 该节点未被接纳为附属节点。
 * @since 22
 */
int32_t OH_ArkUI_RenderNodeUtils_GetRenderNode(ArkUI_NodeHandle node, ArkUI_RenderNodeHandle* renderNode);

/**
 * @brief 为圆角矩形形状选项设置边框矩形范围。该函数通过指定位置和尺寸来定义圆角矩形的几何框架。
 *
 * @param option 指向待配置圆角矩形形状选项的指针。
 * @param x 矩形左上角的X坐标，用于确定左边界位置。
 * @param y 矩形左上角的Y坐标，用于确定上边界位置。
 * @param width 矩形宽度，表示从X坐标起的水平跨度，用于确定右侧边界的位置，即矩形右下角的X坐标 = x + width。
 * @param height 矩形高度，表示从Y坐标起的垂直跨度，用于确定底部边界的位置，即矩形右下角的Y坐标 = y + height。
 * @since 26.0.0
 */
void OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionValue(
    ArkUI_RoundRectShapeOption* option, float x, float y, float width, float height);

/**
 * @brief 为矩形形状选项设置边框矩形范围。该函数通过指定位置和尺寸来定义矩形的几何框架。
 *
 * @param option 指向待配置矩形形状选项的指针。
 * @param x 矩形左上角的X坐标，用于确定左边界位置。
 * @param y 矩形左上角的Y坐标，用于确定上边界位置。
 * @param width 矩形宽度，表示从X坐标起的水平跨度，用于确定右侧边界的位置，即矩形右下角的X坐标 = x + width。
 * @param height 矩形高度，表示从Y坐标起的垂直跨度，用于确定底部边界的位置，即矩形右下角的Y坐标 = y + height。
 * @since 26.0.0
 */
void OH_ArkUI_RenderNodeUtils_SetRectShapeOptionValue(
    ArkUI_RectShapeOption* option, float x, float y, float width, float height);

/**
 * @brief 在父节点下的指定位置插入子渲染节点。
 *
 * @param node 目标父节点。只支持{@link ArkUI_NodeType}中ARKUI_NODE_CUSTOM类型的节点。
 * @param child 将要插入的子渲染节点。
 * @param position 插入子渲染节点的索引。
 *     <br>索引范围必须处于[0, 当前子节点数量]。
 *     <br>如果索引等于当前子节点数量，那么等同于添加操作。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 *     <br>{@link ARKUI_ERROR_CODE_NOT_CUSTOM_NODE} 目标节点非自定义节点。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_PARENT_EXISTED} 目标渲染节点存在父节点。
 *     <br>{@link ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE} 当前渲染节点从FrameNode中获取且该FrameNode已被取消接纳为附属节点或销毁。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RenderNodeUtils_InsertRenderNodeAt(
    ArkUI_NodeHandle node, ArkUI_RenderNodeHandle child, int32_t position);
    
/**
 * @brief 获取指定父节点的子渲染节点数量。
 *
 * @param node 待查询的父节点。
 * @param count 子渲染节点的数量。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RenderNodeUtils_GetRenderNodeChildrenCount(ArkUI_NodeHandle node, int32_t* count);

/**
 * @brief 获取父节点下指定位置的子渲染节点。
 *
 * @param node 目标父节点。
 * @param position 子渲染节点的索引。索引范围必须处于[0, 当前子节点数量-1]。
 * @param child 接收子渲染节点的函数出参。不可为空指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化失败。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RenderNodeUtils_GetRenderNodeAt(
    ArkUI_NodeHandle node, int32_t position, ArkUI_RenderNodeHandle* child);
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_RENDER_H
/** @} */

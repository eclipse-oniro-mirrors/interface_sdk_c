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
 * @brief Declares the APIs of **NativeRender**. For details, see {@link Building a Rendering Node}.
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
 * @brief Defines a render node pointer, which is used to represent and pass render node objects in the APIs related
 * to ArkUI_RenderNodeUtils.
 *
 * @since 20
 */
typedef struct ArkUI_RenderNode* ArkUI_RenderNodeHandle;

/**
 * @brief Defines the pointer to a render content modifier, which is used to reference a content modifier. A content
 * modifier can be attached to a render node to add render attributes or set the onDraw callback.
 *
 * @since 20
 */
typedef struct ArkUI_RenderContentModifier* ArkUI_RenderContentModifierHandle;

/**
 * @brief Defines the pointer to an ArkUI native float rendering property, which is used to create, pass, and manage
 * the floating-point property on the target content modifier.
 *
 * @since 20
 */
typedef struct ArkUI_FloatProperty* ArkUI_FloatPropertyHandle;

/**
 * @brief Defines a pointer to a two-dimensional vector property, used to create, attach, set, obtain, and release
 * two-dimensional vector properties in the ArkUI native rendering property API.
 *
 * @since 20
 */
typedef struct ArkUI_Vector2Property* ArkUI_Vector2PropertyHandle;

/**
 * @brief Defines a color property pointer, which is used to represent a color property in ArkUI.
 *
 * @since 20
 */
typedef struct ArkUI_ColorProperty* ArkUI_ColorPropertyHandle;

/**
 * @brief Defines an animatable float property pointer.
 *
 * @since 20
 */
typedef struct ArkUI_FloatAnimatableProperty* ArkUI_FloatAnimatablePropertyHandle;

/**
 * @brief Defines an animatable 2D vector property pointer.
 *
 * @since 20
 */
typedef struct ArkUI_Vector2AnimatableProperty* ArkUI_Vector2AnimatablePropertyHandle;

/**
 * @brief Defines an animatable color property pointer.
 *
 * @since 20
 */
typedef struct ArkUI_ColorAnimatableProperty* ArkUI_ColorAnimatablePropertyHandle;

/**
 * @brief Defines a rectangle shape option. It is used to describe the shape range of a rectangle or an ellipse in an
 * ArkUI render node, and can be used as input for creating mask or clipping options.
 *
 * @since 20
 */
typedef struct ArkUI_RectShape ArkUI_RectShapeOption;

/**
 * @brief Defines a border style configuration option, which is used to set the style type of a node border,
 * including solid, dashed, dotted, and other styles.
 *
 * @since 20
 */
typedef struct ArkUI_NodeBorderStyle ArkUI_NodeBorderStyleOption;

/**
 * @brief Defines a border width configuration option, which is used to set the border width of each side of the
 * render node.
 *
 * @since 20
 */
typedef struct ArkUI_NodeBorderWidth ArkUI_NodeBorderWidthOption;

/**
 * @brief Defines a node border color configuration option, used to set the border color of a render node by edge
 * direction.
 *
 * @since 20
 */
typedef struct ArkUI_NodeBorderColor ArkUI_NodeBorderColorOption;

/**
 * @brief Defines a node border radius option.
 *
 * @since 20
 */
typedef struct ArkUI_NodeBorderRadius ArkUI_NodeBorderRadiusOption;

/**
 * @brief Defines a circle shape option, which is used to create a circle shape in ArkUI_RenderNodeUtils and
 * configure the center coordinates and radius, serving as a mask or clip shape for a RenderNode.
 *
 * @since 20
 */
typedef struct ArkUI_CircleShape ArkUI_CircleShapeOption;

/**
 * @brief Defines a rounded rectangle shape option, which can be used to create a mask or clipping for a render node.
 *
 * @since 20
 */
typedef struct ArkUI_RoundRectShape ArkUI_RoundRectShapeOption;

/**
 * @brief Defines a custom path option, used to create path-based mask or clip effects for render nodes.
 *
 * @since 20
 */
typedef struct ArkUI_CommandPath ArkUI_CommandPathOption;

/**
 * @brief Defines a render node mask option. It is used to describe the mask area of a render node through a
 * rectangle, rounded rectangle, circle, ellipse, or custom path, and serves as the input parameter of
 * {@link OH_ArkUI_RenderNodeUtils_SetMask} to apply a mask to the render node.
 *
 * @since 20
 */
typedef struct ArkUI_RenderNodeMaskOption ArkUI_RenderNodeMaskOption;

/**
 * @brief Defines a clipping option for a render node. It is used to describe the clipping area of a render node
 * through a rectangle, rounded rectangle, circle, ellipse, or custom path, and serves as the input parameter of
 * {@link OH_ArkUI_RenderNodeUtils_SetClip} to apply clipping to the render node.
 *
 * @since 20
 */
typedef struct ArkUI_RenderNodeClipOption ArkUI_RenderNodeClipOption;

/**
 * @brief Defines a blur style.
 *
 * @since 26.0.0
 */
typedef struct ArkUI_RenderBlurStyleOption ArkUI_RenderBlurStyleOption;

/**
 * @brief Creates a blur style object.
 *
 * After using the object, call {@link OH_ArkUI_RenderNodeUtils_DisposeBlurStyleOption} to destroy it and release
 * resources.
 *
 * @return Pointer to a blur style object. The default blur radius is 0.0.
 * @since 26.0.0
 */
ArkUI_RenderBlurStyleOption* OH_ArkUI_RenderNodeUtils_CreateBlurStyleOption();

/**
 * @brief Dispose of a blur style object.
 *
 * @param option {@link ArkUI_RenderBlurStyleOption} pointer to the blur style object to be disposed of.
 * @since 26.0.0
 */
void OH_ArkUI_RenderNodeUtils_DisposeBlurStyleOption(ArkUI_RenderBlurStyleOption* option);

/**
 * @brief Sets a blur radius for a target blur style.
 *
 * The blur radius is used to control the blur density. A larger radius indicates a higher blur density. If the radius
 * is set to 0, no blur processing is performed. For background blur, a radius of 80 px can achieve a good frosted
 * glass effect. Avoid using a blur radius greater than 200 px, as this may cause performance degradation.
 *
 * @param option {@link ArkUI_RenderBlurStyleOption} pointer to the target blur style for which the blur radius is to
 *     be set.
 * @param radius Blur radius to be set.<br>The value range is [0, +∞).<br>Unit: px.<br>If a negative value is passed,
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBlurStyleOptionRadius(ArkUI_RenderBlurStyleOption* option, float radius);

/**
 * @brief Sets a background blur style for a render node. This API is applicable to scenarios where the background
 * content of the node needs to be blurred.
 *
 * @param node **ArkUI_RenderNodeHandle** pointer to the target render node for which the background blur style is to
 *     be set.
 * @param option {@link ArkUI_RenderBlurStyleOption} pointer to the blur style to be set.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBackgroundBlurOption(
    ArkUI_RenderNodeHandle node, ArkUI_RenderBlurStyleOption* option);

/**
 * @brief Resets a background blur style for a render node.
 *
 * After the reset, there is no background blur style.
 *
 * @param node **ArkUI_RenderNodeHandle** pointer to the target render node for which the background blur style is to
 *     be reset.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_ResetBackgroundBlurOption(ArkUI_RenderNodeHandle node);

/**
 * @brief Sets a foreground blur style for a render node. This API is applicable to scenarios where the foreground
 * image layer of the node needs to be blurred.
 *
 * @param node **ArkUI_RenderNodeHandle** pointer to the target render node for which the foreground blur style is to
 *     be set.
 * @param option {@link ArkUI_RenderBlurStyleOption} pointer to the blur style to be set.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_SetForegroundBlurOption(
    ArkUI_RenderNodeHandle node, ArkUI_RenderBlurStyleOption* option);

/**
 * @brief Resets a foreground blur style for a render node.
 *
 * After the reset, there is no foreground blur style.
 *
 * @param node **ArkUI_RenderNodeHandle** pointer to the target render node for which the foreground blur style is to
 *     be reset.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_ResetForegroundBlurOption(ArkUI_RenderNodeHandle node);

/**
 * @brief Sets a content blur style for a render node. This API is applicable to scenarios where the content drawn by
 * the node needs to be blurred.
 *
 * @param node **ArkUI_RenderNodeHandle** pointer to the target render node for which the content blur style is to be
 *     set.
 * @param option {@link ArkUI_RenderBlurStyleOption} pointer to the blur style to be set.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_SetContentBlurOption(ArkUI_RenderNodeHandle node, ArkUI_RenderBlurStyleOption* option);

/**
 * @brief Resets a content blur style for a render node.
 *
 * After the reset, there is no content blur style.
 *
 * @param node **ArkUI_RenderNodeHandle** pointer to the target render node for which the content blur style is to be
 *     reset.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_ResetContentBlurOption(ArkUI_RenderNodeHandle node);

/**
 * @brief Adds a child render node to the parent custom node.
 *
 * The parent node supports only the nodes of the **ARKUI_NODE_CUSTOM** type in
 * [ArkUI_NodeType](capi-native-node-h.md#arkui_nodetype). By default, when the
 * [OH_ARKUI_NODE_MOUNT_POLICY_SINGLE_IF_RENDER_NODE](capi-native-type-h.md#oh_arkui_nodemountpolicy) mount policy is
 * used, a custom node can mount only one child render node and cannot mount child nodes of other types at the same
 * time. Since API version 26.0.0, you can set the mount policy to **OH_ARKUI_NODE_MOUNT_POLICY_MIXED** using
 * [OH_ArkUI_NativeModule_SetChildMountPolicy](capi-native-node-h.md#oh_arkui_nativemodule_setchildmountpolicy) to
 * support mixed mounting of multiple child nodes.
 *
 * @param node Target parent node.
 * @param child Child render node to be added.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CUSTOM_NODE} if the target node is not a custom node.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CHILD_EXISTED} if the parent node already has a child node when a
 *     non-**OH_ARKUI_NODE_MOUNT_POLICY_MIXED** mount policy is used.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_PARENT_EXISTED} if the target render node has a parent node.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE} if the current render node originates from a
 *     **FrameNode** that has been either detached as a child node or destroyed. This specification is supported since
 *     API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AddRenderNode(ArkUI_NodeHandle node, ArkUI_RenderNodeHandle child);

/**
 * @brief Removes the specified child render node from the parent node.
 *
 * The parent node supports only the nodes of the **ARKUI_NODE_CUSTOM** type in
 * [ArkUI_NodeType](capi-native-node-h.md#arkui_nodetype).
 *
 * @param node Target parent node.
 * @param child Child render node to be removed.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CUSTOM_NODE} if the target node is not a custom node.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_RemoveRenderNode(ArkUI_NodeHandle node, ArkUI_RenderNodeHandle child);

/**
 * @brief Clears child render nodes in the parent node.
 *
 * The parent node supports only the nodes of the **ARKUI_NODE_CUSTOM** type in
 * [ArkUI_NodeType](capi-native-node-h.md#arkui_nodetype).
 *
 * @param node Target parent node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CUSTOM_NODE} if the target node is not a custom node.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_ClearRenderNodeChildren(ArkUI_NodeHandle node);

/**
 * @brief Marks the target node, triggering its lifecycle and child nodes to re-render.
 *
 * @param node Target node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_Invalidate(ArkUI_NodeHandle node);

/**
 * @brief Creates a render node.
 *
 * After using the render node, call {@link OH_ArkUI_RenderNodeUtils_DisposeNode} to destroy it and release the
 * resources.
 *
 * @return Target render node.
 * @since 20
 */
ArkUI_RenderNodeHandle OH_ArkUI_RenderNodeUtils_CreateNode();

/**
 * @brief Destroys the render node.
 *
 * @param node Target render node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_DisposeNode(ArkUI_RenderNodeHandle node);

/**
 * @brief Adds a child node to the target parent render node.
 *
 * @param node Target parent render node.
 * @param child Child render node to be added.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE} if the current render node originates from a
 *     **FrameNode** that has been either detached as a child node or destroyed. This specification is supported
 *     since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AddChild(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle child);

/**
 * @brief Adds a child node after the target child node of the parent node.
 *
 * @param node Target parent render node.
 * @param child Child render node to be added.
 * @param sibling Target child node, which is used to determine the reference sibling render node of the insertion
 *     position. If the node is not in the current child node list of **node**, the node is appended to the end.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**. This specification is supported since API version 22.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE} if the current render node originates from a
 *     **FrameNode** that has been either detached as a child node or destroyed. This specification is supported since
 *     API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_InsertChildAfter(
    ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle child, ArkUI_RenderNodeHandle sibling);

/**
 * @brief Removes a child node from the specified render node.
 *
 * @param node Target parent render node.
 * @param child Child render node to be removed.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_RemoveChild(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle child);

/**
 * @brief Clears all child nodes of the specified render node.
 *
 * @param node Target render node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_ClearChildren(ArkUI_RenderNodeHandle node);

/**
 * @brief Obtains the child node at the specified index.
 *
 * @param node Target parent render node.
 * @param index Index of the child node. The value range is [0, Number of child nodes - 1]. If the index is
 *     less than 0, {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned. If the index is greater than or equal to the
 *     number of child nodes, {@link ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST} is returned.
 * @param child Render node pointer used to receive the child node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST} if the corresponding render child node is not found.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetChild(ArkUI_RenderNodeHandle node, int32_t index, ArkUI_RenderNodeHandle* child);

/**
 * @brief Obtains the first child node of the specified render node.
 *
 * @param node Target render node.
 * @param child Render node pointer used to receive the first child node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST} if the corresponding render child node is not found.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetFirstChild(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle* child);

/**
 * @brief Obtains the next sibling node of the specified node.
 *
 * @param node Reference node.
 * @param sibling Pointer to the render node, which is used to receive the next sibling node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST} if the corresponding render child node is not found.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetNextSibling(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle* sibling);

/**
 * @brief Obtains the previous sibling node of the specified node.
 *
 * @param node Reference node.
 * @param sibling Pointer to the render node, which is used to receive the previous sibling node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST} if the corresponding render child node is not found.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetPreviousSibling(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle* sibling);

/**
 * @brief Obtains all child render nodes of the parent render node.
 *
 * The caller is responsible for releasing the returned child node array.
 *
 * @param node Target parent render node.
 * @param children Pointer array used to store all child render nodes.
 * @param count Pointer used to store the number of obtained child nodes.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetChildren(
    ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle** children, int32_t* count);

/**
 * @brief Obtains the number of child render nodes of the specified render node.
 *
 * @param node Target parent render node.
 * @param count Pointer used to store the number of child nodes.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetChildrenCount(ArkUI_RenderNodeHandle node, int32_t* count);

/**
 * @brief Sets the background color for the render node.
 *
 * @param node Target render node.
 * @param color ARGB color value (32-bit unsigned integer).
 *     <br>Default value: **0x00000000**.
 *     <br>**Description of color byte layout**:
 *     <br>- Bits 24-31: alpha channel (0x00 for fully transparent, 0xFF for fully opaque).
 *     <br>- Bits 16-23: red channel.
 *     <br>- Bits 8-15: green channel.
 *     <br>- Bits 0-7: blue channel.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBackgroundColor(ArkUI_RenderNodeHandle node, uint32_t color);

/**
 * @brief Obtains the background color of the render node.
 *
 * @param node Target render node.
 * @param color Integer pointer used to store the obtained ARGB color value.
 *     <br>Default value: **0x00000000**.
 *     <br>**Description of color byte layout**:
 *     <br>- Bits 24-31: alpha channel (0x00 for fully transparent, 0xFF for fully opaque).
 *     <br>- Bits 16-23: red channel.
 *     <br>- Bits 8-15: green channel.
 *     <br>- Bits 0-7: blue channel.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBackgroundColor(ArkUI_RenderNodeHandle node, uint32_t* color);

/**
 * @brief Sets whether to clip the render node based on the frame area.
 *
 * The frame area is determined by the node size and position. Different from
 * {@link OH_ArkUI_RenderNodeUtils_SetClipToBounds}, which clips the render node based on the node bounds
 * (rounded corner bounds are used when rounded corners are configured), this API always uses the frame rectangle.
 * To clip the render node based on a custom shape, use {@link OH_ArkUI_RenderNodeUtils_SetClip}.
 * If this parameter is set to **1**, the content that exceeds the clipping area will be clipped.
 *
 * @param node Target render node.
 * @param clipToFrame Whether to clip the render node based on the frame area.
 *     <br>**1**: yes; **0**: no.
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetClipToFrame(ArkUI_RenderNodeHandle node, int32_t clipToFrame);

/**
 * @brief Obtains whether the render node is clipped based on the frame area.
 *
 * @param node Target render node.
 * @param clipToFrame Pointer used to receive the state value indicating whether the render node is clipped based on the
 *     frame area.
 *     <br>**1**: The render node is clipped based on the frame area; **0**: The render node is not clipped based on the
 *     frame area.
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetClipToFrame(ArkUI_RenderNodeHandle node, int32_t* clipToFrame);

/**
 * @brief Sets whether to clip the render node based on its bounds.
 *
 * When rounded corners are configured for a node, the rounded corner bounds are used. When this parameter is set to
 * **1**, the content that exceeds the clipping area will be clipped.
 *
 * @param node Target render node.
 * @param clipToBounds Whether to clip the render node based on its bounds.
 *     <br>**1**: yes; **0**: no.
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetClipToBounds(ArkUI_RenderNodeHandle node, int32_t clipToBounds);

/**
 * @brief Obtains whether the render node is clipped based on its bounds.
 *
 * When rounded corners are configured for a node, the rounded corner bounds are used.
 *
 * @param node Target render node.
 * @param clipToBounds Pointer used to receive the state value indicating whether the render node is clipped
 *     based on its bounds.
 *     <br>**1**: The render node is clipped based on its bounds; **0**: The render node is not clipped based on its
 *     bounds.
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetClipToBounds(ArkUI_RenderNodeHandle node, int32_t* clipToBounds);

/**
 * @brief Sets the opacity value for the render node.
 *
 * @param node Target render node.
 * @param opacity Opacity value (0.0–1.0).
 *     <br>Default value: **1**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetOpacity(ArkUI_RenderNodeHandle node, float opacity);

/**
 * @brief Obtains the opacity value of the render node.
 *
 * @param node Target render node.
 * @param opacity Pointer used to store the opacity value (0.0–1.0).
 *     <br>Default value: **1**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetOpacity(ArkUI_RenderNodeHandle node, float* opacity);

/**
 * @brief Sets the size for the render node.
 *
 * @param node Target render node.
 * @param width Width, in px.
 *     <br>Default value: **0**. The value must be greater than or equal to 0. If a negative value is passed,
 *     {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} is returned.
 * @param height Height, in px.
 *     <br>Default value: **0**. The value must be greater than or equal to 0. If a negative value is passed,
 *     {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetSize(ArkUI_RenderNodeHandle node, int32_t width, int32_t height);

/**
 * @brief Obtains the size of the render node.
 *
 * @param node Target render node.
 * @param width Pointer used to receive the width value, in px. The value range is [0, INT_MAX].
 *     <br>Default value: **0**.
 * @param height Pointer used to receive the height value, in px. The value range is [0, INT_MAX].
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetSize(ArkUI_RenderNodeHandle node, int32_t* width, int32_t* height);

/**
 * @brief Sets the position coordinates for the render node.
 *
 * @param node Target render node.
 * @param x X-coordinate (in px).
 *     <br>Default value: **0**, in px.
 * @param y Y-coordinate (in px).
 *     <br>Default value: **0**, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetPosition(ArkUI_RenderNodeHandle node, int32_t x, int32_t y);

/**
 * @brief Obtains the position coordinates of the render node. The coordinates are the position offset of the render
 * node relative to its parent node after the parent node lays out the node. The unit is px. The **offset** attribute
 * that takes effect after the layout and the **position** attribute that does not participate in the layout do not
 * affect the coordinates.
 *
 * @param node Target render node.
 * @param x Pointer used to store the x-coordinate (in px).
 *     <br>Default value: **0**, in px.
 * @param y Pointer used to store the y-coordinate (in px).
 *     <br>Default value: **0**, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetPosition(ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y);

/**
 * @brief Sets the pivot point for the transformation of the render node.
 *
 * @param node Target render node.
 * @param x Normalized X-coordinate of the pivot point. The value range is [0.0, 1.0]. The API does not verify this
 *     range. If the value is out of range, the input value is still used.
 *     <br>Default value: **0.5**.
 * @param y Normalized Y-coordinate of the pivot point. The value range is [0.0, 1.0]. The API does not verify this
 *     range. If the value is out of range, the input value is still used.
 *     <br>Default value: **0.5**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetPivot(ArkUI_RenderNodeHandle node, float x, float y);

/**
 * @brief Obtains the pivot point coordinates of the render node.
 *
 * @param node Target render node.
 * @param x Pointer used to store the x-coordinate of the pivot point.
 *     <br>Default value: **0.5**.
 * @param y Pointer used to store the y-coordinate of the pivot point.
 *     <br>Default value: **0.5**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetPivot(ArkUI_RenderNodeHandle node, float* x, float* y);

/**
 * @brief Sets the scale factors for the render node.
 *
 * @param node Target render node.
 * @param x Scale factor on the x-axis.
 *     <br>Default value: **1**.
 * @param y Scale factor on the y-axis.
 *     <br>Default value: **1**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetScale(ArkUI_RenderNodeHandle node, float x, float y);

/**
 * @brief Obtains the scale factors of the render node.
 *
 * @param node Target render node.
 * @param x Pointer used to store the scale factor on the x-axis.
 *     <br>Default value: **1**.
 * @param y Pointer used to store the scale factor on the y-axis.
 *     <br>Default value: **1**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetScale(ArkUI_RenderNodeHandle node, float* x, float* y);

/**
 * @brief Sets the translation offset for the render node.
 *
 * @param node Target render node.
 * @param x Horizontal translation offset (in pixels).
 *     <br>Default value: **0**.
 * @param y Vertical translation offset (in pixels).
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetTranslation(ArkUI_RenderNodeHandle node, float x, float y);

/**
 * @brief Obtains the translation offset of the render node.
 *
 * @param node Target render node.
 * @param x Pointer used to receive the horizontal translation offset, in px.
 *     <br>Default value: **0**.
 * @param y Pointer used to receive the vertical translation offset, in px.
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetTranslation(ArkUI_RenderNodeHandle node, float* x, float* y);

/**
 * @brief Sets the rotation angles for the render node.
 *
 * @param node Target render node.
 * @param x Rotation angle around the x-axis (in degrees).
 *     <br>Default value: **0**.
 * @param y Rotation angle around the y-axis (in degrees).
 *     <br>Default value: **0**.
 * @param z Rotation angle around the z-axis (in degrees).
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetRotation(ArkUI_RenderNodeHandle node, float x, float y, float z);

/**
 * @brief Obtains the rotation angles of the render node.
 *
 * @param node Target render node.
 * @param x Pointer used to store the rotation angle around the x-axis (in degrees).
 *     <br>Default value: **0**.
 * @param y Pointer used to store the rotation angle around the y-axis (in degrees).
 *     <br>Default value: **0**.
 * @param z Pointer used to store the rotation angle around the z-axis (in degrees).
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetRotation(ArkUI_RenderNodeHandle node, float* x, float* y, float* z);

/**
 * @brief Sets the transformation matrix for the render node.
 *
 * This API is used to control the scaling, rotation, translation, skewing, and perspective projection effects of a
 * render node using a 4 x 4 matrix.
 *
 * @param node Target render node.
 * @param matrix Float array of 4x4 transformation matrix (16 consecutive values).
 *     The transformation matrix must be provided as 16 consecutive float values in row-major order:
 *       [m00, m01, m02, m03,
 *        m10, m11, m12, m13,
 *        m20, m21, m22, m23,
 *        m30, m31, m32, m33]
 *     The matrix is represented as follows:
 *       | m00 m01 m02 m03 |
 *       | m10 m11 m12 m13 |
 *       | m20 m21 m22 m23 |
 *       | m30 m31 m32 m33 |
 *     Matrix components:
 *       | m00  | Scale value for the x-axis. The default value is **1** in the identity matrix.        |
 *       | m01  | Second value, affected by rotation or skewing around x, y, z axes.                    |
 *       | m02  | Third value, affected by rotation around x, y, z axes.                                |
 *       | m03  | Fourth value, affected by perspective projection.                                     |
 *       | m10  | Fifth value, affected by rotation or skewing around x, y, z axes.                     |
 *       | m11  | Scale value for the y-axis. The default value is **1** in the identity matrix.        |
 *       | m12  | Seventh value, affected by rotation around x, y, z axes.                              |
 *       | m13  | Eighth value, affected by perspective projection.                                     |
 *       | m20  | Ninth value, affected by rotation around x, y, z axes.                                |
 *       | m21  | Tenth value, affected by rotation around x, y, z axes.                                |
 *       | m22  | Scale value for the z-axis. The default value is **1** in the identity matrix.        |
 *       | m23  | Twelfth value, affected by perspective projection.                                    |
 *       | m30  | Translation value for the x-axis (in px). The default value is **0** in the identity   |
 *       |      | matrix.                                                                                |
 *       | m31  | Translation value for the y-axis (in px). The default value is **0** in the identity   |
 *       |      | matrix.                                                                                |
 *       | m32  | Translation value for the z-axis (in px). The default value is **0** in the identity   |
 *       |      | matrix.                                                                                |
 *       | m33  | Valid in homogeneous coordinates, producing perspective projection effects.            |
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetTransform(ArkUI_RenderNodeHandle node, float* matrix);

/**
 * @brief Sets the shadow color for the render node.
 *
 * @param node Target render node.
 * @param color ARGB color value (32-bit unsigned integer).
 *     <br>Default value: **0x00000000**.
 *     <br>**Description of color byte layout**:
 *     <br>- Bits 24-31: alpha channel (0x00 for fully transparent, 0xFF for fully opaque).
 *     <br>- Bits 16-23: red channel.
 *     <br>- Bits 8-15: green channel.
 *     <br>- Bits 0-7: blue channel.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowColor(ArkUI_RenderNodeHandle node, uint32_t color);

/**
 * @brief Obtains the shadow color of the render node.
 *
 * @param node Target render node.
 * @param color Integer pointer used to receive the ARGB color value. If the shadow color is not set, the
 *     received value is **0x00000000** (fully transparent).
 *     <br>**Description of color byte layout**:
 *     <br>- Bits 24-31: alpha channel (0x00 for fully transparent, 0xFF for fully opaque).
 *     <br>- Bits 16-23: red channel.
 *     <br>- Bits 8-15: green channel.
 *     <br>- Bits 0-7: blue channel.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetShadowColor(ArkUI_RenderNodeHandle node, uint32_t* color);

/**
 * @brief Sets the shadow offset for the render node.
 *
 * @param node Target render node.
 * @param x Horizontal offset (in pixels).
 *     <br>Default value: **0**.
 * @param y Vertical offset (in pixels).
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowOffset(ArkUI_RenderNodeHandle node, int32_t x, int32_t y);

/**
 * @brief Obtains the shadow offset of the render node.
 *
 * @param node Target render node.
 * @param x Pointer used to store the horizontal offset.
 *     <br>Default value: **0**, in px.
 * @param y Pointer used to store the vertical offset.
 *     <br>Default value: **0**, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetShadowOffset(ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y);

/**
 * @brief Sets the shadow alpha (transparency) for the render node.
 *
 * @param node Target render node.
 * @param alpha Alpha channel of the shadow. The value range is [0.0, 1.0]. If a value beyond the range is
 *     passed, {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowAlpha(ArkUI_RenderNodeHandle node, float alpha);

/**
 * @brief Obtains the shadow alpha (transparency) of the render node.
 *
 * @param node Target render node.
 * @param alpha Pointer used to receive the alpha channel of the shadow. If no shadow-related attribute is set,
 *     the received value is **-1.0**, indicating that no attribute is configured. After a shadow-related attribute is
 *     set, the received value ranges from 0.0 to 1.0.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetShadowAlpha(ArkUI_RenderNodeHandle node, float* alpha);

/**
 * @brief Sets the shadow elevation for the render node.
 *
 * @param node Target render node.
 * @param elevation Shadow elevation, in px. The value range is [0, +∞). If a negative value is passed,
 *     {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} is returned.
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowElevation(ArkUI_RenderNodeHandle node, float elevation);

/**
 * @brief Obtains the shadow elevation of the render node.
 *
 * @param node Target render node.
 * @param elevation Pointer used to receive the shadow elevation value, in px. The value range is [0, +∞). If the
 *     shadow elevation is not set, the received value is **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetShadowElevation(ArkUI_RenderNodeHandle node, float* elevation);

/**
 * @brief Sets the shadow radius for the render node.
 *
 * @param node Target render node.
 * @param radius Shadow radius, in px. The value range is [0, +∞). If a negative value is passed,
 *     {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowRadius(ArkUI_RenderNodeHandle node, float radius);

/**
 * @brief Obtains the shadow radius of the render node.
 *
 * @param node Target render node.
 * @param radius Pointer used to receive the shadow radius, in px. After the shadow radius is set, the received
 *     value range is [0, +∞). If the shadow radius is not set, the received value is **0** in versions earlier than
 *     API 26.0.0 and **-1** since API 26.0.0.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetShadowRadius(ArkUI_RenderNodeHandle node, float* radius);

/**
 * @brief Sets the border style for the render node.
 *
 * @param node Target render node.
 * @param borderStyle Pointer to the border style.
 *     <br>Default value in the struct pointer: {@link ARKUI_BORDER_STYLE_SOLID}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBorderStyle(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderStyleOption* borderStyle);

/**
 * @brief Obtains the border style of the render node.
 *
 * @param node Target render node.
 * @param borderStyle Pointer used to store the border style.
 *     <br>Default value in the struct pointer: {@link ARKUI_BORDER_STYLE_SOLID}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBorderStyle(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderStyleOption** borderStyle);

/**
 * @brief Sets the border width for the render node.
 *
 * The border width must be less than the node size.
 *
 * @param node Target render node.
 * @param borderWidth Pointer to the border width.
 *     <br>Default value in the struct pointer: **0**. Unit: px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBorderWidth(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderWidthOption* borderWidth);

/**
 * @brief Obtains the border width of the render node.
 *
 * @param node Target render node.
 * @param borderWidth Pointer used to store the border width.
 *     <br>Default value in the struct pointer: **0**. Unit: px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBorderWidth(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderWidthOption** borderWidth);

/**
 * @brief Sets the border color for the render node.
 *
 * @param node Target render node.
 * @param borderColor Pointer to the border color.
 *     <br>Default value in the struct pointer: **0x00000000**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBorderColor(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderColorOption* borderColor);

/**
 * @brief Obtains the border color of the render node.
 *
 * @param node Target render node.
 * @param borderColor Pointer used to store the border color.
 *     <br>Default value in the struct pointer: **0x00000000**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBorderColor(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderColorOption** borderColor);

/**
 * @brief Sets the border corner radius for the render node.
 *
 * @param node Target render node.
 * @param borderRadius Pointer to the border radius.
 *     <br>The default radius of each corner is 0, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBorderRadius(
    ArkUI_RenderNodeHandle node, ArkUI_NodeBorderRadiusOption* borderRadius);

/**
 * @brief Obtains the border corner radius of the render node.
 *
 * @param node Target render node.
 * @param borderRadius Pointer used to store the border corner radius.
 *     <br>The default radius of each corner is 0, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBorderRadius(
    ArkUI_RenderNodeHandle node, ArkUI_NodeBorderRadiusOption** borderRadius);

/**
 * @brief Applies a mask to the render node using the mask configuration.
 *
 * The mask layer range is determined by the node boundary. The part of the mask shape that exceeds the node boundary
 * is not displayed. Calling {@link OH_ArkUI_RenderNodeUtils_SetDrawRegion} will not expand the mask layer range.
 *
 * The mask is created as follows:
 * 1. Add brightness and a linear color filter to the mask layer.
 * 2. Draw the mask graphic under this filter.
 * 3. Use the original node image as the source color and the mask graphic as the target color, and blend them into a
 * mask image using the [BlendMode.SRC_IN](../apis-arkgraphics2d/arkts-apis-graphics-drawing-e.md#blendmode) API.
 *
 * @param node Target render node.
 * @param mask Pointer to the mask configuration.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetMask(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeMaskOption* mask);

/**
 * @brief Applies clipping to the render node using the clipping configuration.
 *
 * The clipping shape can exceed the node boundary. To display the drawing content outside the node boundary, call
 * {@link OH_ArkUI_RenderNodeUtils_SetDrawRegion} to set the drawing area that covers the content. The final display
 * is still affected by other clipping conditions.
 *
 * @param node Target render node.
 * @param clip Pointer to the clipping configuration.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetClip(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeClipOption* clip);

/**
 * @brief Sets whether to form a render group with the target node and its subtree.
 *
 * If the **markNodeGroup** parameter is set to **true**, the system generates an offscreen cache that contains the
 * node and its subtree to reuse the drawing result. This is applicable to scenarios where the subtree content is
 * fixed and only the overall application animation is required. When this API is used together with screenshot, blur,
 * brightness adjustment, or blending operations, display exceptions or performance deterioration may occur.
 *
 * @param node Target render node.
 * @param markNodeGroup Whether to form a node group with the target node and its subtree.
 *     <br>**true**: form a node group and perform offscreen rendering; **false**: do not form a node group.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetMarkNodeGroup(ArkUI_RenderNodeHandle node, bool markNodeGroup);

/**
 * @brief Sets the bounds for the render node.
 *
 * @param node Target render node.
 * @param x X-coordinate of the upper left corner of the bounds, in pixels.
 *     <br>Default value: **0**.
 * @param y Y-coordinate of the upper left corner of the bounds, in pixels.
 *     <br>Default value: **0**.
 * @param width Width of the bounds (in pixels).
 *     <br>Default value: **0**. The value must be greater than or equal to 0. If a negative value is passed,
 *     {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} is returned.
 * @param height Height of the bounds (in pixels).
 *     <br>Default value: **0**. The value must be greater than or equal to 0. If a negative value is passed,
 *     {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBounds(
    ArkUI_RenderNodeHandle node, int32_t x, int32_t y, int32_t width, int32_t height);

/**
 * @brief Obtains the bounds of the render node.
 *
 * @param node Target render node.
 * @param x Pointer used to store the x-coordinate of the upper left corner of the bounds, in pixels.
 *     <br>Default value: **0**.
 * @param y Pointer used to store the y-coordinate of the upper left corner of the bounds, in pixels.
 *     <br>Default value: **0**.
 * @param width Pointer used to store the width of the bound, in pixels. The value range is [0, INT_MAX].
 *     <br>Default value: **0**.
 * @param height Pointer used to store the height of the bound, in pixels. The value range is [0, INT_MAX].
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBounds(
    ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y, int32_t* width, int32_t* height);

/**
 * @brief Sets the drawing region for the render node.
 *
 * The drawing area is defined by the x, y, w, and h coordinates in the local coordinate system of the node. This area
 * is combined with the node's own range and is used to calculate the node's drawing range and dirty regions. If the
 * drawing content exceeds the node's boundary, the area should cover the entire overflow. This API does not change the
 * node's boundary or expand the mask layer's range.
 *
 * @param node Target render node.
 * @param x X-coordinate of the upper left corner of the drawing area relative to the origin of the local coordinate
 *     system of the node, in px.
 * @param y Y-coordinate of the upper left corner of the drawing area relative to the origin of the local coordinate
 *     system of the node, in px.
 * @param w Width of the drawing area, in px.
 * @param h Height of the drawing area, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetDrawRegion(ArkUI_RenderNodeHandle node, float x, float y, float w, float h);

/**
 * @brief Attaches a content modifier to the render node.
 *
 * This API is used to extend the custom drawing content of a node through the **onDraw** callback.
 *
 * @param node Target render node.
 * @param modifier Content modifier.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a
 *     **FrameNode**.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachContentModifier(
    ArkUI_RenderNodeHandle node, ArkUI_RenderContentModifierHandle modifier);

/**
 * @brief Creates a content modifier.
 *
 * This API is used to save the drawing attributes, set the **onDraw** callback, and attach the content modifier to the
 * render node. After using the content modifier, call {@link OH_ArkUI_RenderNodeUtils_DisposeContentModifier} to
 * release it.
 *
 * @return Content modifier.
 * @since 20
 */
ArkUI_RenderContentModifierHandle OH_ArkUI_RenderNodeUtils_CreateContentModifier();

/**
 * @brief Disposes of the content modifier.
 *
 * @param modifier Content modifier.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeContentModifier(ArkUI_RenderContentModifierHandle modifier);

/**
 * @brief Attaches a float property to the target content modifier.
 *
 * This API is used to pass or update floating-point drawing parameters in the drawing callback.
 *
 * @param modifier Target content modifier to which the property is to be attached.
 * @param property Float property.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachFloatProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_FloatPropertyHandle property);

/**
 * @brief Attaches a 2D vector property to the target content modifier.
 *
 * This API is used to pass or update drawing parameters such as 2D coordinates and offsets in the drawing callback.
 *
 * @param modifier Target content modifier to which the property is to be attached.
 * @param property 2D vector property.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachVector2Property(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_Vector2PropertyHandle property);

/**
 * @brief Attaches a color property to the target content modifier.
 *
 * This API is used to pass or update color drawing parameters in the drawing callback.
 *
 * @param modifier Target content modifier to which the property is to be attached.
 * @param property Color property.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachColorProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_ColorPropertyHandle property);

/**
 * @brief Attaches an animatable float property to the target content modifier.
 *
 * This API is used to set floating-point drawing parameters that change with the animation in the drawing callback.
 *
 * @param modifier Target content modifier to which the property is to be attached.
 * @param property Animatable float property.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachFloatAnimatableProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_FloatAnimatablePropertyHandle property);

/**
 * @brief Attaches an animatable 2D vector property to the target content modifier.
 *
 * This API is used to set drawing parameters such as 2D coordinates and offsets that change with the animation in the
 * drawing callback.
 *
 * @param modifier Target content modifier to which the property is to be attached.
 * @param property Animatable 2D vector property.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachVector2AnimatableProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_Vector2AnimatablePropertyHandle property);

/**
 * @brief Attaches an animatable color property to the target content modifier.
 *
 * This API is used to set color drawing parameters that change with the animation in the drawing callback.
 *
 * @param modifier Target content modifier to which the property is to be attached.
 * @param property Animatable color property.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachColorAnimatableProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_ColorAnimatablePropertyHandle property);

/**
 * @brief Creates a float property.
 *
 * After using the property, call {@link OH_ArkUI_RenderNodeUtils_DisposeFloatProperty} to release it.
 *
 * @param value Property value.
 * @return Float property.
 * @since 20
 */
ArkUI_FloatPropertyHandle OH_ArkUI_RenderNodeUtils_CreateFloatProperty(float value);

/**
 * @brief Sets the value of the float property.
 *
 * @param property Float property.
 * @param value Property value.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetFloatPropertyValue(ArkUI_FloatPropertyHandle property, float value);

/**
 * @brief Obtains the value of the float property.
 *
 * @param property Float property.
 * @param value Pointer used to store the property value.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetFloatPropertyValue(ArkUI_FloatPropertyHandle property, float* value);

/**
 * @brief Disposes of the float property.
 *
 * @param property Float property.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeFloatProperty(ArkUI_FloatPropertyHandle property);

/**
 * @brief Creates a 2D vector property.
 *
 * After using the property, call {@link OH_ArkUI_RenderNodeUtils_DisposeVector2Property} to release it.
 *
 * @param x X-coordinate of the property.
 * @param y Y-coordinate of the property.
 * @return 2D vector property.
 * @since 20
 */
ArkUI_Vector2PropertyHandle OH_ArkUI_RenderNodeUtils_CreateVector2Property(float x, float y);

/**
 * @brief Sets the value of the 2D vector property.
 *
 * @param property 2D vector property.
 * @param x X-coordinate of the property.
 * @param y Y-coordinate of the property.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetVector2PropertyValue(ArkUI_Vector2PropertyHandle property, float x, float y);

/**
 * @brief Obtains the value of the 2D vector property.
 *
 * @param property 2D vector property.
 * @param x Pointer used to store the x-coordinate of the property.
 * @param y Pointer used to store the y-coordinate of the property.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetVector2PropertyValue(ArkUI_Vector2PropertyHandle property, float* x, float* y);

/**
 * @brief Disposes of the 2D vector property.
 *
 * @param property 2D vector property.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeVector2Property(ArkUI_Vector2PropertyHandle property);

/**
 * @brief Creates a color property.
 *
 * After using the property, call {@link OH_ArkUI_RenderNodeUtils_DisposeColorProperty} to release it.
 *
 * @param value ARGB color value used to initialize the color property. The value is in the format of 0xAARRGGBB,
 *     where A, R, G, and B indicate the alpha, red, green, and blue channels, respectively.
 * @return Color property.
 * @since 20
 */
ArkUI_ColorPropertyHandle OH_ArkUI_RenderNodeUtils_CreateColorProperty(uint32_t value);

/**
 * @brief Sets the value of the color property.
 *
 * @param property Color property.
 * @param value ARGB color value to be set. The value is in the format of 0xAARRGGBB, where A, R, G, and B indicate
 *     the alpha, red, green, and blue channels, respectively.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetColorPropertyValue(ArkUI_ColorPropertyHandle property, uint32_t value);

/**
 * @brief Obtains the value of the color property.
 *
 * @param property Color property.
 * @param value Pointer used to receive the ARGB color value. The color value is in the format of 0xAARRGGBB, where
 *     A, R, G, and B indicate the alpha, red, green, and blue channels, respectively.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetColorPropertyValue(ArkUI_ColorPropertyHandle property, uint32_t* value);

/**
 * @brief Disposes of the color property.
 *
 * @param property Color property.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeColorProperty(ArkUI_ColorPropertyHandle property);

/**
 * @brief Creates an animatable float property.
 *
 * This API is used to save the float drawing parameters that can change with the animation. After using the property,
 * call {@link OH_ArkUI_RenderNodeUtils_DisposeFloatAnimatableProperty} to release it.
 *
 * @param value Property value.
 * @return Animatable float property.
 * @since 20
 */
ArkUI_FloatAnimatablePropertyHandle OH_ArkUI_RenderNodeUtils_CreateFloatAnimatableProperty(float value);

/**
 * @brief Sets the value of the animatable float property.
 *
 * @param property Animatable float property.
 * @param value Property value.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetFloatAnimatablePropertyValue(
    ArkUI_FloatAnimatablePropertyHandle property, float value);

/**
 * @brief Obtains the value of the animatable float property.
 *
 * @param property Animatable float property.
 * @param value Pointer used to store the property value.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetFloatAnimatablePropertyValue(
    ArkUI_FloatAnimatablePropertyHandle property, float* value);

/**
 * @brief Disposes of the animatable float property.
 *
 * @param property Animatable float property.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeFloatAnimatableProperty(ArkUI_FloatAnimatablePropertyHandle property);

/**
 * @brief Creates an animatable 2D vector property.
 *
 * This API is used to save the drawing parameters such as 2D coordinates and offsets that can change with animation.
 * After using the property, call {@link OH_ArkUI_RenderNodeUtils_DisposeVector2AnimatableProperty} to release it.
 *
 * @param x X-coordinate of the property.
 * @param y Y-coordinate of the property.
 * @return Animatable 2D vector property.
 * @since 20
 */
ArkUI_Vector2AnimatablePropertyHandle OH_ArkUI_RenderNodeUtils_CreateVector2AnimatableProperty(float x, float y);

/**
 * @brief Sets the value of the animatable 2D vector property.
 *
 * @param property Animatable 2D vector property.
 * @param x X-coordinate of the property.
 * @param y Y-coordinate of the property.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetVector2AnimatablePropertyValue(
    ArkUI_Vector2AnimatablePropertyHandle property, float x, float y);

/**
 * @brief Obtains the value of the animatable 2D vector property.
 *
 * @param property Animatable 2D vector property.
 * @param x Pointer used to store the x-coordinate of the property.
 * @param y Pointer used to store the y-coordinate of the property.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetVector2AnimatablePropertyValue(
    ArkUI_Vector2AnimatablePropertyHandle property, float* x, float* y);

/**
 * @brief Disposes of the animatable 2D vector property.
 *
 * @param property Animatable 2D vector property.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeVector2AnimatableProperty(ArkUI_Vector2AnimatablePropertyHandle property);

/**
 * @brief Creates an animatable color property.
 *
 * This API is used to save the color drawing parameters that can change with the animation. After using the property,
 * call {@link OH_ArkUI_RenderNodeUtils_DisposeColorAnimatableProperty} to release it.
 *
 * @param value ARGB color value used to initialize the animatable color property. The value is in the format of
 *     0xAARRGGBB, where A, R, G, and B indicate the alpha, red, green, and blue channels, respectively.
 * @return Animatable color property.
 * @since 20
 */
ArkUI_ColorAnimatablePropertyHandle OH_ArkUI_RenderNodeUtils_CreateColorAnimatableProperty(uint32_t value);

/**
 * @brief Sets the value of the animatable color property.
 *
 * @param property Animatable color property.
 * @param value ARGB color value to be set. The value is in the format of 0xAARRGGBB, where A, R, G, and B indicate
 *     the alpha, red, green, and blue channels, respectively.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetColorAnimatablePropertyValue(
    ArkUI_ColorAnimatablePropertyHandle property, uint32_t value);

/**
 * @brief Obtains the value of the animatable color property.
 *
 * @param property Animatable color property.
 * @param value Pointer used to receive the ARGB color value. The color value is in the format of 0xAARRGGBB, where
 *     A, R, G, and B indicate the alpha, red, green, and blue channels, respectively.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetColorAnimatablePropertyValue(
    ArkUI_ColorAnimatablePropertyHandle property, uint32_t* value);

/**
 * @brief Disposes of the animatable color property.
 *
 * @param property Animatable color property.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeColorAnimatableProperty(ArkUI_ColorAnimatablePropertyHandle property);

/**
 * @brief Sets the **onDraw** callback of the content modifier.
 *
 * This callback is used to execute the custom drawing logic during the drawing phase of the content modifier.
 *
 * @param modifier Target content modifier.
 * @param userData Pointer to the custom data to be passed to the callback.
 * @param callback Pointer to the callback for receiving drawing events. **context** indicates the drawing context,
 *     and **userData** indicates the custom data passed when this API is called.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetContentModifierOnDraw(ArkUI_RenderContentModifierHandle modifier, void* userData,
    void (*callback)(ArkUI_DrawContext* context, void* userData));

/**
 * @brief Creates a rectangle shape option.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption} to release it.
 *
 * @return Pointer to the rectangle shape option.
 * @since 20
 */
ArkUI_RectShapeOption* OH_ArkUI_RenderNodeUtils_CreateRectShapeOption();

/**
 * @brief Disposes of the rectangle shape option.
 *
 * @param option Pointer to the rectangle shape option.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption(ArkUI_RectShapeOption* option);

/**
 * @brief Sets the edge value for the rectangle shape option.
 *
 * The left or top edge can be a negative value, indicating that the corresponding edge is on the left or above the
 * node origin. When the shape is used for masking, the part that exceeds the node boundary is not displayed. When the
 * shape is used for clipping and the content outside the node boundary needs to be displayed, you need to use
 * {@link OH_ArkUI_RenderNodeUtils_SetDrawRegion} to set the drawing area that covers the content.
 *
 * @param option Pointer to the rectangle shape option.
 * @param edgeValue Edge value of the rectangle shape option, in px.
 * @param direction Edge direction to apply the value.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRectShapeOptionEdgeValue(
    ArkUI_RectShapeOption* option, float edgeValue, ArkUI_EdgeDirection direction);

/**
 * @brief Creates a node border style option.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeNodeBorderStyleOption} to release it.
 *
 * @return Pointer to the node border style option.
 * @since 20
 */
ArkUI_NodeBorderStyleOption* OH_ArkUI_RenderNodeUtils_CreateNodeBorderStyleOption();

/**
 * @brief Disposes of the node border style option.
 *
 * @param option Pointer to the node border style option.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderStyleOption(ArkUI_NodeBorderStyleOption* option);

/**
 * @brief Sets the edge style of the node border.
 *
 * @param option Pointer to the node border style option.
 * @param edgeStyle Edge style of the node border.
 * @param direction Edge direction.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetNodeBorderStyleOptionEdgeStyle(
    ArkUI_NodeBorderStyleOption* option, ArkUI_BorderStyle edgeStyle, ArkUI_EdgeDirection direction);

/**
 * @brief Creates a node border width option.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeNodeBorderWidthOption} to release it.
 *
 * @return Pointer to the node border width option.
 * @since 20
 */
ArkUI_NodeBorderWidthOption* OH_ArkUI_RenderNodeUtils_CreateNodeBorderWidthOption();

/**
 * @brief Disposes of the node border width option.
 *
 * @param option Pointer to the node border width option.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderWidthOption(ArkUI_NodeBorderWidthOption* option);

/**
 * @brief Sets the edge width of the node border.
 *
 * @param option Pointer to the node border width option.
 * @param edgeWidth Edge width of the node border, in px. The value range is [0, +∞). If a negative value is passed,
 *     the width of the corresponding edge remains unchanged.
 * @param direction Edge direction.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetNodeBorderWidthOptionEdgeWidth(
    ArkUI_NodeBorderWidthOption* option, float edgeWidth, ArkUI_EdgeDirection direction);

/**
 * @brief Creates a node border color option.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeNodeBorderColorOption} to release it.
 *
 * @return Pointer to the node border color option.
 * @since 20
 */
ArkUI_NodeBorderColorOption* OH_ArkUI_RenderNodeUtils_CreateNodeBorderColorOption();

/**
 * @brief Disposes of the node border color option.
 *
 * @param option Pointer to the node border color option.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderColorOption(ArkUI_NodeBorderColorOption* option);

/**
 * @brief Sets the edge color of the node border.
 *
 * @param option Pointer to the node border color option.
 * @param edgeColor Edge color of the node border, in 0xAARRGGBB format, where A, R, G, and B indicate the alpha, red,
 *     green, and blue channels, respectively.
 * @param direction Edge direction.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetNodeBorderColorOptionEdgeColor(
    ArkUI_NodeBorderColorOption* option, uint32_t edgeColor, ArkUI_EdgeDirection direction);

/**
 * @brief Creates a node border radius option.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeNodeBorderRadiusOption} to release it.
 *
 * @return Pointer to the node border radius option.
 * @since 20
 */
ArkUI_NodeBorderRadiusOption* OH_ArkUI_RenderNodeUtils_CreateNodeBorderRadiusOption();

/**
 * @brief Disposes of the node border radius option.
 *
 * @param option Pointer to the node border radius option.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderRadiusOption(ArkUI_NodeBorderRadiusOption* option);

/**
 * @brief Sets the border radius of a specified corner of a node.
 *
 * @param option Pointer to the node border radius option.
 * @param cornerRadius Border radius of a specified corner of a node, in px. The value is a non-negative integer.
 * @param direction Direction of the target corner.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetNodeBorderRadiusOptionCornerRadius(
    ArkUI_NodeBorderRadiusOption* option, uint32_t cornerRadius, ArkUI_CornerDirection direction);

/**
 * @brief Creates a circle shape option.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeCircleShapeOption} to release it.
 *
 * @return Pointer to the circle shape option.
 * @since 20
 */
ArkUI_CircleShapeOption* OH_ArkUI_RenderNodeUtils_CreateCircleShapeOption();

/**
 * @brief Disposes of the circle shape option.
 *
 * @param option Pointer to the circle shape option.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeCircleShapeOption(ArkUI_CircleShapeOption* option);

/**
 * @brief Sets the X-coordinate of the center for the circle shape option.
 *
 * @param option Pointer to the circle shape option.
 * @param centerX X-coordinate of the center, in px.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionCenterX(ArkUI_CircleShapeOption* option, float centerX);

/**
 * @brief Sets the Y-coordinate of the center for the circle shape option.
 *
 * @param option Pointer to the circle shape option.
 * @param centerY Y-coordinate of the center, in px.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionCenterY(ArkUI_CircleShapeOption* option, float centerY);

/**
 * @brief Sets the radius value for the circle shape option.
 *
 * @param option Pointer to the circle shape option.
 * @param radius Radius, in pixels.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionRadius(ArkUI_CircleShapeOption* option, float radius);

/**
 * @brief Creates a rounded rectangle shape option.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeRoundRectShapeOption} to release it.
 *
 * @return Pointer to the rounded rectangle shape option.
 * @since 20
 */
ArkUI_RoundRectShapeOption* OH_ArkUI_RenderNodeUtils_CreateRoundRectShapeOption();

/**
 * @brief Disposes of the rounded rectangle shape option.
 *
 * @param option Pointer to the rounded rectangle shape option.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeRoundRectShapeOption(ArkUI_RoundRectShapeOption* option);

/**
 * @brief Sets the edge value for the rounded rectangle shape option.
 *
 * The left or top edge can be a negative value, indicating that the corresponding edge is on the left or above the
 * node origin. When the shape is used for masking, the part that exceeds the node boundary is not displayed. When the
 * shape is used for clipping and the content outside the node boundary needs to be displayed, you need to use
 * {@link OH_ArkUI_RenderNodeUtils_SetDrawRegion} to set the drawing area that covers the content.
 *
 * @param option Pointer to the rounded rectangle shape option.
 * @param edgeValue Edge value of the rounded rectangle shape option, in px.
 * @param direction Edge direction to apply the value.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionEdgeValue(
    ArkUI_RoundRectShapeOption* option, float edgeValue, ArkUI_EdgeDirection direction);

/**
 * @brief Sets the corner radius for the X and Y axes of a specified corner.
 *
 * @param option Pointer to the rounded rectangle shape option.
 * @param x Corner radius of the X axis of the specified corner, in px.
 * @param y Corner radius of the Y axis of the specified corner, in px.
 * @param direction Direction of the target corner.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionCornerXY(
    ArkUI_RoundRectShapeOption* option, float x, float y, ArkUI_CornerDirection direction);

/**
 * @brief Creates a custom drawing path option.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeCommandPathOption} to release it.
 *
 * @return Pointer to the custom drawing path option.
 * @since 20
 */
ArkUI_CommandPathOption* OH_ArkUI_RenderNodeUtils_CreateCommandPathOption();

/**
 * @brief Disposes of the custom drawing path option.
 *
 * @param option Pointer to the custom drawing path option.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeCommandPathOption(ArkUI_CommandPathOption* option);

/**
 * @brief Sets the command values for the custom drawing path option.
 *
 * @param option Pointer to the custom drawing path option.
 * @param commands Command values. The input parameter format is the \<path> shape label in Basic Shapes of SVG.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetCommandPathOptionCommands(ArkUI_CommandPathOption* option, char* commands);

/**
 * @brief Creates a mask from a rectangle shape.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption} to release it.
 *
 * @param shape Pointer to the rectangle shape option.
 * @return Pointer to the render node mask.
 * @since 20
 */
ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromRectShape(
    ArkUI_RectShapeOption* shape);

/**
 * @brief Creates a mask from a rounded rectangle shape.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption} to release it.
 *
 * @param shape Pointer to the rounded rectangle shape option.
 * @return Pointer to the render node mask.
 * @since 20
 */
ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromRoundRectShape(
    ArkUI_RoundRectShapeOption* shape);

/**
 * @brief Creates a mask from a circle shape.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption} to release it.
 *
 * @param shape Pointer to the circle shape option.
 * @return Pointer to the render node mask.
 * @since 20
 */
ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromCircleShape(
    ArkUI_CircleShapeOption* shape);

/**
 * @brief Creates a mask from an oval shape.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption} to release it.
 *
 * @param shape Pointer to the oval shape option.
 * @return Pointer to the render node mask.
 * @since 20
 */
ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromOvalShape(
    ArkUI_RectShapeOption* shape);

/**
 * @brief Creates a mask from a custom drawing path.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption} to release it.
 *
 * @param path Pointer to the custom drawing path option.
 * @return Pointer to the render node mask.
 * @since 20
 */
ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromCommandPath(
    ArkUI_CommandPathOption* path);

/**
 * @brief Disposes of the render node mask option.
 *
 * @param option Pointer to the render node mask.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption(ArkUI_RenderNodeMaskOption* option);

/**
 * @brief Sets the fill color for the render node mask option.
 *
 * @param mask Pointer to the render node mask.
 * @param fillColor Fill color of the mask, in 0xAARRGGBB format, where A, R, G, and B indicate the alpha, red, green,
 *     and blue channels, respectively.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionFillColor(ArkUI_RenderNodeMaskOption* mask, uint32_t fillColor);

/**
 * @brief Sets the stroke color for the render node mask option.
 *
 * @param mask Pointer to the render node mask.
 * @param strokeColor Stroke color of the mask, in 0xAARRGGBB format, where A, R, G, and B indicate the alpha, red,
 *     green, and blue channels, respectively.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeColor(
    ArkUI_RenderNodeMaskOption* mask, uint32_t strokeColor);

/**
 * @brief Sets the stroke width for the render node mask option.
 *
 * Drawing with the corresponding width is performed centered on the border path.
 *
 * @param mask Pointer to the render node mask.
 * @param strokeWidth Stroke width of the mask, in px. If the value is greater than 0, the stroke is drawn based on the
 *     specified width. If the value is 0 or a negative number, the stroke is drawn as a thin line with a width of 1 px
 *     on the device.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeWidth(ArkUI_RenderNodeMaskOption* mask, float strokeWidth);

/**
 * @brief Creates a render node clip option from a rectangle shape.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption} to release it.
 *
 * @param shape Pointer to the rectangle shape option.
 * @return Pointer to the render node clip.
 * @since 20
 */
ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromRectShape(
    ArkUI_RectShapeOption* shape);

/**
 * @brief Creates a render node clip option from a rounded rectangle shape.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption} to release it.
 *
 * @param shape Pointer to the rounded rectangle shape option.
 * @return Pointer to the render node clip.
 * @since 20
 */
ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromRoundRectShape(
    ArkUI_RoundRectShapeOption* shape);

/**
 * @brief Creates a render node clip option from a circle shape.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption} to release it.
 *
 * @param shape Pointer to the circle shape option.
 * @return Pointer to the render node clip.
 * @since 20
 */
ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromCircleShape(
    ArkUI_CircleShapeOption* shape);

/**
 * @brief Creates a render node clip option from an oval shape.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption} to release it.
 *
 * @param shape Pointer to the oval shape option.
 * @return Pointer to the render node clip.
 * @since 20
 */
ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromOvalShape(
    ArkUI_RectShapeOption* shape);

/**
 * @brief Creates a render node clip option from a custom drawing path.
 *
 * After using the option, call {@link OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption} to release it.
 *
 * @param path Pointer to the custom drawing path option.
 * @return Pointer to the render node clip.
 * @since 20
 */
ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromCommandPath(
    ArkUI_CommandPathOption* path);

/**
 * @brief Disposes of the render node clip option.
 *
 * @param option Pointer to the render node clip.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption(ArkUI_RenderNodeClipOption* option);

/**
 * @brief Obtains the RenderNode of the target node that has been accepted as a child node. If a RenderNode is obtained
 * through this API, when the {@link disposeNode} API of {@link ArkUI_NativeNodeAPI_1} is invoked to destroy the
 * FrameNode, the {@link OH_ArkUI_RenderNodeUtils_DisposeNode} API needs to be invoked additionally to release the
 * RenderNode.
 *
 * @param node Pointer to **ArkUI_NodeHandle**, which specifies the target node.
 * @param renderNode Pointer to **ArkUI_RenderNodeHandle**, which specifies the RenderNode of the target node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_NOT_ADOPTED_NODE} if this node is not accepted as a child node.
 * @since 22
 */
int32_t OH_ArkUI_RenderNodeUtils_GetRenderNode(ArkUI_NodeHandle node, ArkUI_RenderNodeHandle* renderNode);

/**
 * @brief Sets the border range for a rounded rectangle shape option.
 *
 * @param option Pointer to the rounded rectangle shape option to be configured.
 * @param x X coordinate of the upper left corner of the rectangle, which is used to determine the position of the left
 *     boundary.
 * @param y Y coordinate of the upper left corner of the rectangle, which is used to determine the position of the
 *     upper boundary.
 * @param width Width of the rectangle, which indicates the horizontal span starting from the X coordinate and is used
 *     to determine the position of the right boundary. That is, the X coordinate of the lower right corner of the
 *     rectangle is equal to **x** + **width**.
 * @param height Height of the rectangle, which indicates the vertical span starting from the Y coordinate and is used
 *     to determine the position of the bottom boundary. That is, the Y coordinate of the lower right corner of the
 *     rectangle is equal to **y** + **height**.
 * @since 26.0.0
 */
void OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionValue(
    ArkUI_RoundRectShapeOption* option, float x, float y, float width, float height);

/**
 * @brief Sets the border range for a rectangle shape option.
 *
 * @param option Pointer to the rectangle shape option to be configured.
 * @param x X coordinate of the upper left corner of the rectangle, which is used to determine the position of the left
 *     boundary.
 * @param y Y coordinate of the upper left corner of the rectangle, which is used to determine the position of the
 *     upper boundary.
 * @param width Width of the rectangle, which indicates the horizontal span starting from the X coordinate and is used
 *     to determine the position of the right boundary. That is, the X coordinate of the lower right corner of the
 *     rectangle is equal to **x** + **width**.
 * @param height Height of the rectangle, which indicates the vertical span starting from the Y coordinate and is used
 *     to determine the position of the bottom boundary. That is, the Y coordinate of the lower right corner of the
 *     rectangle is equal to **y** + **height**.
 * @since 26.0.0
 */
void OH_ArkUI_RenderNodeUtils_SetRectShapeOptionValue(
    ArkUI_RectShapeOption* option, float x, float y, float width, float height);

/**
 * @brief Inserts a child render node at a specified position under a parent custom node.
 *
 * By default, the {@link OH_ARKUI_NODE_MOUNT_POLICY_SINGLE_IF_RENDER_NODE} mount policy is used. The child render node
 * to be inserted must be the only child node of the parent element. You can use
 * {@link OH_ArkUI_NativeModule_SetChildMountPolicy} to set the mount policy to
 * **OH_ARKUI_NODE_MOUNT_POLICY_MIXED** to mount multiple child nodes.
 *
 * @param node Target parent node. Only the **ARKUI_NODE_CUSTOM** type in
 *     [ArkUI_NodeType](capi-native-node-h.md#arkui_nodetype) is supported.
 * @param child Child render node to be inserted.
 * @param position Index of the child render node to be inserted. The value range is [0, Number of current child nodes].
 *     If the value is equal to the number of current child nodes, the operation is equivalent to adding a child render
 *     node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CUSTOM_NODE} if the target node is not a custom node.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CHILD_EXISTED} if the parent node already has a child node when a
 *     non-**OH_ARKUI_NODE_MOUNT_POLICY_MIXED** mount policy is used.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_PARENT_EXISTED} if the target render node has a parent node.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE} if the current render node originates from a
 *     **FrameNode** that has been either detached as a child node or destroyed.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RenderNodeUtils_InsertRenderNodeAt(
    ArkUI_NodeHandle node, ArkUI_RenderNodeHandle child, int32_t position);

/**
 * @brief Obtains the number of all child nodes of a parent custom node in the mixed mount order.
 *
 * The count includes both common nodes and render nodes. The parent node must be of the **ARKUI_NODE_CUSTOM** type and
 * the **OH_ARKUI_NODE_MOUNT_POLICY_MIXED** policy must have been set using
 * {@link OH_ArkUI_NativeModule_SetChildMountPolicy}. Otherwise, {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 *
 * @param node Parent node to be queried.
 * @param count Pointer used to receive the number of child nodes.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RenderNodeUtils_GetRenderNodeChildrenCount(ArkUI_NodeHandle node, int32_t* count);

/**
 * @brief Obtains the render node handle corresponding to the child node at a specified position of a parent custom node
 * in the mixed mount order.
 *
 * The parent node must be of the **ARKUI_NODE_CUSTOM** type and the **OH_ARKUI_NODE_MOUNT_POLICY_MIXED** policy must
 * have been set using {@link OH_ArkUI_NativeModule_SetChildMountPolicy}. Otherwise,
 * {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 *
 * @param node Target parent node.
 * @param position Index of a child node. The value range is [0, Number of current child nodes - 1].
 * @param child Pointer used to receive the render node handle corresponding to the child node at the
 *     specified position. The value cannot be null.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RenderNodeUtils_GetRenderNodeAt(
    ArkUI_NodeHandle node, int32_t position, ArkUI_RenderNodeHandle* child);
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_RENDER_H
/** @} */

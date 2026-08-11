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
 * @brief Defines a render node pointer.
 *
 * @since 20
 */
typedef struct ArkUI_RenderNode* ArkUI_RenderNodeHandle;

/**
 * @brief Defines a content modifier pointer.
 *
 * @since 20
 */
typedef struct ArkUI_RenderContentModifier* ArkUI_RenderContentModifierHandle;

/**
 * @brief Defines a float property pointer.
 *
 * @since 20
 */
typedef struct ArkUI_FloatProperty* ArkUI_FloatPropertyHandle;

/**
 * @brief Defines a 2D vector property pointer.
 *
 * @since 20
 */
typedef struct ArkUI_Vector2Property* ArkUI_Vector2PropertyHandle;

/**
 * @brief Defines a color property pointer.
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
 * @brief Defines a rectangle shape option.
 *
 * @since 20
 */
typedef struct ArkUI_RectShape ArkUI_RectShapeOption;

/**
 * @brief Defines a node border style option.
 *
 * @since 20
 */
typedef struct ArkUI_NodeBorderStyle ArkUI_NodeBorderStyleOption;

/**
 * @brief Defines a node border width option.
 *
 * @since 20
 */
typedef struct ArkUI_NodeBorderWidth ArkUI_NodeBorderWidthOption;

/**
 * @brief Defines a node border color option.
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
 * @brief Defines a circle shape option.
 *
 * @since 20
 */
typedef struct ArkUI_CircleShape ArkUI_CircleShapeOption;

/**
 * @brief Defines a rounded rectangle shape option.
 *
 * @since 20
 */
typedef struct ArkUI_RoundRectShape ArkUI_RoundRectShapeOption;

/**
 * @brief Defines a custom path option.
 *
 * @since 20
 */
typedef struct ArkUI_CommandPath ArkUI_CommandPathOption;

/**
 * @brief Defines a render node mask option.
 *
 * @since 20
 */
typedef struct ArkUI_RenderNodeMaskOption ArkUI_RenderNodeMaskOption;

/**
 * @brief Defines a render node clipping option.
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
 * @param option {@link ArkUI_RenderBlurStyleOption} pointer to the target blur style for which the blur radius is to
 *     be set.
 * @param radius Blur radius to be set. The value range is [0, +∞). Unit: px. The blur radius is used to control the
 *     blur density. A larger radius indicates a higher blur density. The value **0** indicates that no blur processing
 *     is performed. For background blur processing, a radius of 80 can achieve a good frosted glass effect. Avoid
 *     using a blur radius greater than 200 pixels, as this may cause performance degradation.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBlurStyleOptionRadius(ArkUI_RenderBlurStyleOption* option, float radius);

/**
 * @brief Sets a background blur style for a render node.
 *
 * @param node **ArkUI_RenderNodeHandle** pointer to the target render node for which the background blur style is to
 *     be set.
 * @param option {@link ArkUI_RenderBlurStyleOption} pointer to the blur style to be set.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBackgroundBlurOption(
    ArkUI_RenderNodeHandle node, ArkUI_RenderBlurStyleOption* option);

/**
 * @brief Resets a background blur style for a render node. After the reset, there is no background blur style.
 *
 * @param node **ArkUI_RenderNodeHandle** pointer to the target render node for which the background blur style is to
 *     be reset.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_ResetBackgroundBlurOption(ArkUI_RenderNodeHandle node);

/**
 * @brief Sets a foreground blur style for a render node.
 *
 * @param node **ArkUI_RenderNodeHandle** pointer to the target render node for which the foreground blur style is to
 *     be set.
 * @param option {@link ArkUI_RenderBlurStyleOption} pointer to the blur style to be set.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_SetForegroundBlurOption(
    ArkUI_RenderNodeHandle node, ArkUI_RenderBlurStyleOption* option);

/**
 * @brief Resets a foreground blur style for a render node. After the reset, there is no foreground blur style.
 *
 * @param node **ArkUI_RenderNodeHandle** pointer to the target render node for which the foreground blur style is to
 *     be reset.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_ResetForegroundBlurOption(ArkUI_RenderNodeHandle node);

/**
 * @brief Sets a content blur style for a render node.
 *
 * @param node **ArkUI_RenderNodeHandle** pointer to the target render node for which the content blur style is to be
 *     set.
 * @param option {@link ArkUI_RenderBlurStyleOption} pointer to the blur style to be set.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_SetContentBlurOption(ArkUI_RenderNodeHandle node, ArkUI_RenderBlurStyleOption* option);

/**
 * @brief Resets a content blur style for a render node. After the reset, there is no content blur style.
 *
 * @param node **ArkUI_RenderNodeHandle** pointer to the target render node for which the content blur style is to be
 *     reset.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 26.0.0
 */
int32_t OH_ArkUI_RenderNodeUtils_ResetContentBlurOption(ArkUI_RenderNodeHandle node);

/**
 * @brief Adds a child render node to the parent custom node.
 *
 * The parent node supports only nodes of the **ARKUI_NODE_CUSTOM** type in
 * [ArkUI_NodeType](capi-native-node-h.md#arkui_nodetype). Each custom node can be mounted to only one
 * **ArkUI_RenderNodeHandle**. **customNode** cannot be mounted to another **ArkUI_NodeHandle**.
 *
 * @param node Target parent node.
 * @param child Child render node to be added.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CUSTOM_NODE} if the target node is not a custom node.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CHILD_EXISTED} if the target node already has a child node.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_PARENT_EXISTED} if the target rendering node already has a parent
 *     node.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE} if the current render node originates from a
 *     FrameNode that has been either detached as a child node or destroyed. This specification is supported since API
 *     version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AddRenderNode(ArkUI_NodeHandle node, ArkUI_RenderNodeHandle child);

/**
 * @brief Removes the specified child render node from the parent node.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE} if the current render node originates from a
 *     FrameNode that has been either detached as a child node or destroyed. This specification is supported since API
 *     version 22.
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
 * @return Error code.
 *     {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 *     {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if CAPI init error.
 *     {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the node is obtained from a FrameNode. Add since api 22.
 *     {@link ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE} if the child is obtained from a FrameNode, and its
 *     corresponding FrameNode is
 *     no longer in the adopted state. Add since api 22.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_ClearChildren(ArkUI_RenderNodeHandle node);

/**
 * @brief Obtains the child node at the specified index.
 *
 * @param node Target parent render node.
 * @param index Zero-based index of the child node.
 * @param child Render node pointer used to receive the child node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST} if the corresponding render child node is not found.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 * @brief Obtains all child render nodes of the parent render node. The caller is responsible for releasing the
 * returned child node array.
 *
 * @param node Target parent render node.
 * @param children Pointer array used to store all child render nodes.
 * @param count Pointer used to store the number of obtained child nodes.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetBackgroundColor(ArkUI_RenderNodeHandle node, uint32_t color);

/**
 * @brief Obtains the background color of the render node.
 *
 * @param node Target render node.
 * @param color Integer pointer used to store the obtained RGBA color value.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBackgroundColor(ArkUI_RenderNodeHandle node, uint32_t* color);

/**
 * @brief Sets whether to clip the render node.
 *
 * @param node Target render node.
 * @param clipToFrame Whether to clip the current render node. **1**: Clip to frame. **0**: Do not clip.
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetClipToFrame(ArkUI_RenderNodeHandle node, int32_t clipToFrame);

/**
 * @brief Obtains whether the render node is clipped.
 *
 * @param node Target render node.
 * @param clipToFrame Integer pointer used to receive the clipping status (1 or 0).
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetClipToFrame(ArkUI_RenderNodeHandle node, int32_t* clipToFrame);

/**
 * @brief Sets whether to clip to the bounds of the render node.
 *
 * @param node Target render node.
 * @param clipToBounds Clipping flag. **1**: Clip to bounds. **0**: Do not clip.
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetClipToBounds(ArkUI_RenderNodeHandle node, int32_t clipToBounds);

/**
 * @brief Sets whether clipping to the bounds of the render node is enabled.
 *
 * @param node Target render node.
 * @param clipToBounds Clipping flag. **1**: Clip to bounds. **0**: Do not clip.
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetOpacity(ArkUI_RenderNodeHandle node, float* opacity);

/**
 * @brief Sets the size for the render node.
 *
 * @param node Target render node.
 * @param width Width value (in px).
 *     <br>Default value: **0**, in px. The value must be greater than or equal to 0. If a negative value is passed,
 *     {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} is returned.
 * @param height Height value (in px).
 *     <br>Default value: **0**, in px. The value must be greater than or equal to 0. If a negative value is passed,
 *     {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetSize(ArkUI_RenderNodeHandle node, int32_t width, int32_t height);

/**
 * @brief Obtains the size of the render node.
 *
 * @param node Target render node.
 * @param width Pointer used to store the width value (in px).
 *     <br>Default value: **0**, in px.
 * @param height Pointer used to store the height value (in px).
 *     <br>Default value: **0**, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetPosition(ArkUI_RenderNodeHandle node, int32_t x, int32_t y);

/**
 * @brief Obtains the position coordinates of the render node. The coordinates are the position offset of the render
 * node relative to its parent node after the layout. The unit is px. The coordinates are the result after the parent
 * node lays out the node. Therefore, the **offset** attribute that takes effect after the layout and the **position**
 * attribute that does not participate in the layout do not affect the coordinates.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetPosition(ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y);

/**
 * @brief Sets the pivot point for the transformation of the render node.
 *
 * @param node Target render node.
 * @param x X-coordinate of the pivot point. Standard value range: 0.0–1.0.
 *     <br>Default value: **0.5**.
 * @param y Y-coordinate of the pivot point. Standard value range: 0.0–1.0.
 *     <br>Default value: **0.5**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetTranslation(ArkUI_RenderNodeHandle node, float x, float y);

/**
 * @brief Obtains the translation offset of the render node.
 *
 * @param node Target render node.
 * @param x Pointer used to store the horizontal translation offset.
 *     <br>Default value: **0**.
 * @param y Pointer used to store the vertical translation offset.
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetRotation(ArkUI_RenderNodeHandle node, float* x, float* y, float* z);

/**
 * @brief Sets the transformation matrix for the render node.
 *
 * @param node Target render node.
 * @param matrix Float array of 4x4 transformation matrix (16 consecutive values).
 *     The transformation matrix should be provided as 16 consecutive floating-point values in row-major order:
 *       [m00, m01, m02, m03,
 *        m10, m11, m12, m13,
 *        m20, m21, m22, m23,
 *        m30, m31, m32, m33]
 *     Where the matrix represents:
 *       | m00 m01 m02 m03 |
 *       | m10 m11 m12 m13 |
 *       | m20 m21 m22 m23 |
 *       | m30 m31 m32 m33 |
 *     Matrix components:
 *       | m00  | Scaling value of the x-axis. The default value is **1** for the identity matrix.     |
 *       | m01  | The second value, which is affected by the rotation or tilt of the x, y, and z axes.  |
 *       | m02  | The third value, which is affected by the rotation of the x, y, and z axes.  |
 *       | m03  | The fourth value, which is affected by perspective projection.              |
 *       | m10  | The fifth value, which is affected by the rotation or tilt of the x, y, and z axes.  |
 *       | m11  | Scaling value of the y-axis. The default value is **1** for the identity matrix.     |
 *       | m12  | The seventh value, which is affected by the rotation of the x, y, and z axes.  |
 *       | m13  | The eighth value, which is affected by perspective projection.              |
 *       | m20  | The ninth value, which is affected by the rotation of the x, y, and z axes.  |
 *       | m21  | The tenth value, which is affected by the rotation of the x, y, and z axes. |
 *       | m22  | Scaling value of the z-axis. The default value is **1** for the identity matrix.     |
 *       | m23  | The 12th value, which is affected by perspective projection.              |
 *       | m30  | Translation value of the x-axis, in px. The default value is **0** for the identity matrix.|
 *       | m31  | Translation value of the y-axis, in px. The default value is **0** for the identity matrix.|
 *       | m32  | Translation value of the z-axis, in px. The default value is **0** for the identity matrix.|
 *       | m33  | Valid in homogeneous coordinates, presenting the perspective projection effect.   |
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowColor(ArkUI_RenderNodeHandle node, uint32_t color);

/**
 * @brief Obtains the shadow color of the render node.
 *
 * @param node Target render node.
 * @param color Integer pointer used to store the obtained RGBA color value.
 *     <br>Default value: **0xFF000000**.
 *     <br>**Description of color byte layout**:
 *     <br>- Bits 24-31: alpha channel (0x00 for fully transparent, 0xFF for fully opaque).
 *     <br>- Bits 16-23: red channel.
 *     <br>- Bits 8-15: green channel.
 *     <br>- Bits 0-7: blue channel.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetShadowOffset(ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y);

/**
 * @brief Sets the shadow alpha (transparency) for the render node.
 *
 * @param node Target render node.
 * @param alpha Shadow alpha value (0.0–1.0).
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowAlpha(ArkUI_RenderNodeHandle node, float alpha);

/**
 * @brief Obtains the shadow alpha (transparency) of the render node.
 *
 * @param node Target render node.
 * @param alpha Pointer used to store the shadow alpha value.
 *     <br>Default value: **1**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetShadowAlpha(ArkUI_RenderNodeHandle node, float* alpha);

/**
 * @brief Sets the shadow elevation for the render node.
 *
 * @param node Target render node.
 * @param elevation Elevation.
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowElevation(ArkUI_RenderNodeHandle node, float elevation);

/**
 * @brief Obtains the shadow elevation of the render node.
 *
 * @param node Target render node.
 * @param elevation Pointer used to store the elevation value.
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetShadowElevation(ArkUI_RenderNodeHandle node, float* elevation);

/**
 * @brief Sets the shadow radius for the render node.
 *
 * @param node Target render node.
 * @param radius Radius value.
 *     <br>Default value: **0**. The value must be greater than or equal to 0. If a negative value is passed,
 *     {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the parameter value is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetShadowRadius(ArkUI_RenderNodeHandle node, float radius);

/**
 * @brief Obtains the shadow radius of the render node.
 *
 * @param node Target render node.
 * @param radius Pointer used to store the radius value.
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBorderStyle(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderStyleOption** borderStyle);

/**
 * @brief Sets the border width for the render node. The border width must be smaller than the node size.
 *
 * @param node Target render node.
 * @param borderWidth Pointer to the border width.
 *     <br>Default value in the struct pointer: **0**. Unit: px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBorderColor(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderColorOption** borderColor);

/**
 * @brief Sets the border corner radius for the render node.
 *
 * @param node Target render node.
 * @param borderRadius Pointer to the border radius.
 *     <br>Default value in the struct pointer: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Default value in the struct pointer: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBorderRadius(
    ArkUI_RenderNodeHandle node, ArkUI_NodeBorderRadiusOption** borderRadius);

/**
 * @brief Applies a mask to the render node using the mask configuration.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetMask(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeMaskOption* mask);

/**
 * @brief Applies clipping to the render node using the clipping configuration.
 *
 * @param node Target render node.
 * @param clip Pointer to the clipping configuration.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetClip(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeClipOption* clip);

/**
 * @brief Marks whether to prioritize drawing the node and its child nodes.
 *
 * @param node Target render node.
 * @param markNodeGroup Whether to prioritize drawing the node and its child nodes.
 *     <br>**true**: Enable drawing priority. **false**: Disable drawing priority.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
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
 * @param width Pointer used to store the width of the bounds (in pixels).
 *     <br>Default value: **0**.
 * @param height Pointer used to store the height of the bounds (in pixels).
 *     <br>Default value: **0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_GetBounds(
    ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y, int32_t* width, int32_t* height);

/**
 * @brief Sets the drawing region for the render node. This drawing region is mainly used to address drawing issues
 * caused by exceeding boundaries. When possible, set the size according to the actual drawing range.
 *
 * @param node Target render node.
 * @param x X-coordinate of the upper left corner of the bounds, in pixels.
 * @param y Y-coordinate of the upper left corner of the bounds, in pixels.
 * @param w Width of the bounds (in pixels).
 * @param h Height of the bounds (in pixels).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_SetDrawRegion(ArkUI_RenderNodeHandle node, float x, float y, float w, float h);

/**
 * @brief Attaches a content modifier to the render node.
 *
 * @param node Target render node.
 * @param modifier Content modifier.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE} if the target node originates from a FrameNode.
 *     This specification is supported since API version 22.
 * @since 20
 */
int32_t OH_ArkUI_RenderNodeUtils_AttachContentModifier(
    ArkUI_RenderNodeHandle node, ArkUI_RenderContentModifierHandle modifier);

/**
 * @brief Creates a content modifier.
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
 * @param modifier Target content modifier.
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
 * @param modifier Target content modifier.
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
 * @param modifier Target content modifier.
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
 * @param modifier Target content modifier.
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
 * @param modifier Target content modifier.
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
 * @param modifier Target content modifier.
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
 * @param value Property value.
 * @return Color property.
 * @since 20
 */
ArkUI_ColorPropertyHandle OH_ArkUI_RenderNodeUtils_CreateColorProperty(uint32_t value);

/**
 * @brief Sets the value of the color property.
 *
 * @param property Color property.
 * @param value Property value.
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
 * @param value Pointer used to store the property value.
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
 * @param value Property value.
 * @return Animatable color property.
 * @since 20
 */
ArkUI_ColorAnimatablePropertyHandle OH_ArkUI_RenderNodeUtils_CreateColorAnimatableProperty(uint32_t value);

/**
 * @brief Sets the value of the animatable color property.
 *
 * @param property Animatable color property.
 * @param value Property value.
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
 * @param value Pointer used to store the property value.
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
 * @brief Sets the **onDraw** callback function for the content modifier.
 *
 * @param modifier Target content modifier.
 * @param userData Custom data to be passed to the callback.
 * @param callback The draw event receiver callback.
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
 * @brief Sets the edge value for the rectangle shape option. When the left and top boundaries are set to negative
 * values, part of the content that exceeds the node may fail to draw due to the layer overlay effect involved in
 * display.
 *
 * @param option Pointer to the rectangle shape option.
 * @param edgeValue Edge value to set.
 * @param direction Edge direction to apply the value.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRectShapeOptionEdgeValue(
    ArkUI_RectShapeOption* option, float edgeValue, ArkUI_EdgeDirection direction);

/**
 * @brief Creates a node border style option.
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
 * @brief Sets the edge style for the node border style option.
 *
 * @param option Pointer to the node border style option.
 * @param edgeStyle Edge border style value of the node border style option.
 * @param direction Edge direction.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetNodeBorderStyleOptionEdgeStyle(
    ArkUI_NodeBorderStyleOption* option, ArkUI_BorderStyle edgeStyle, ArkUI_EdgeDirection direction);

/**
 * @brief Creates a node border width option.
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
 * @brief Sets the edge width for the node border width option.
 *
 * @param option Pointer to the node border width option.
 * @param edgeWidth Edge width of the node border width option.
 *     <br>Value range: [0, +∞).
 * @param direction Edge direction.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetNodeBorderWidthOptionEdgeWidth(
    ArkUI_NodeBorderWidthOption* option, float edgeWidth, ArkUI_EdgeDirection direction);

/**
 * @brief Creates a node border color option.
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
 * @brief Sets the edge color for the node border color option.
 *
 * @param option Pointer to the node border color option.
 * @param edgeColor Edge color of the node border color option.
 * @param direction Edge direction.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetNodeBorderColorOptionEdgeColor(
    ArkUI_NodeBorderColorOption* option, uint32_t edgeColor, ArkUI_EdgeDirection direction);

/**
 * @brief Creates a node border radius option.
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
 * @brief Sets the corner radius for the node border radius option. Note that the input parameter **cornerRadius** is
 * of type uint32_t, and only positive integers are supported.
 *
 * @param option Pointer to the node border radius option.
 * @param cornerRadius Corner radius of the node border radius option.
 * @param direction Edge direction.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetNodeBorderRadiusOptionCornerRadius(
    ArkUI_NodeBorderRadiusOption* option, uint32_t cornerRadius, ArkUI_CornerDirection direction);

/**
 * @brief Creates a circle shape option.
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
 * @brief Sets the x-coordinate of the center for the circle shape option.
 *
 * @param option Pointer to the circle shape option.
 * @param centerX X-coordinate of the center of the circle shape option.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionCenterX(ArkUI_CircleShapeOption* option, float centerX);

/**
 * @brief Sets the y-coordinate of the center for the circle shape option.
 *
 * @param option Pointer to the circle shape option.
 * @param centerY Y-coordinate of the center of the circle shape option.
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
 * @brief Sets the edge values for the rounded rectangle shape option.
 *
 * @param option Pointer to the rounded rectangle shape option.
 * @param edgeValue Edge value to set.
 * @param direction Edge direction to apply the value.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionEdgeValue(
    ArkUI_RoundRectShapeOption* option, float edgeValue, ArkUI_EdgeDirection direction);

/**
 * @brief Sets the coordinates for the target corner.
 *
 * @param option Pointer to the rounded rectangle shape option.
 * @param x X-coordinate of the target corner, in pixels.
 * @param y Y-coordinate of the target corner, in pixels.
 * @param direction Direction of the target corner.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionCornerXY(
    ArkUI_RoundRectShapeOption* option, float x, float y, ArkUI_CornerDirection direction);

/**
 * @brief Creates a custom drawing path option.
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
 * @param commands Command values. The input parameter format is {@link \<path>shape}.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetCommandPathOptionCommands(ArkUI_CommandPathOption* option, char* commands);

/**
 * @brief Creates a mask from a rectangle shape.
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
 * @param shape Pointer to the rounded rectangle shape option.
 * @return Pointer to the render node mask.
 * @since 20
 */
ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromRoundRectShape(
    ArkUI_RoundRectShapeOption* shape);

/**
 * @brief Creates a mask from a circle shape.
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
 * @param shape Pointer to the oval shape option.
 * @return Pointer to the render node mask.
 * @since 20
 */
ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromOvalShape(
    ArkUI_RectShapeOption* shape);

/**
 * @brief Creates a mask from a custom drawing path.
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
 * @param fillColor Fill color of the mask.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionFillColor(ArkUI_RenderNodeMaskOption* mask, uint32_t fillColor);

/**
 * @brief Sets the stroke color for the render node mask option.
 *
 * @param mask Pointer to the render node mask.
 * @param strokeColor Stroke color of the mask.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeColor(
    ArkUI_RenderNodeMaskOption* mask, uint32_t strokeColor);

/**
 * @brief Sets the stroke width for the render node mask option. Drawing with the corresponding width is performed
 * centered on the border path.
 *
 * @param mask Pointer to the render node mask.
 * @param strokeWidth Stroke width of the mask.
 *     <br>Value range: (0, +∞). If the value is a negative number or 0, the stroke width is set to 1 pixel during
 *     drawing.
 * @since 20
 */
void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeWidth(ArkUI_RenderNodeMaskOption* mask, float strokeWidth);

/**
 * @brief Creates a render node clip option from a rectangle shape.
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
 * @param shape Pointer to the rounded rectangle shape option.
 * @return Pointer to the render node clip.
 * @since 20
 */
ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromRoundRectShape(
    ArkUI_RoundRectShapeOption* shape);

/**
 * @brief Creates a render node clip option from a circle shape.
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
 * @param shape Pointer to the oval shape option.
 * @return Pointer to the render node clip.
 * @since 20
 */
ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromOvalShape(
    ArkUI_RectShapeOption* shape);

/**
 * @brief Creates a render node clip option from a custom drawing path.
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
 * @brief Sets the border range for a rounded rectangle shape option. This function defines the geometric frame of a
 * rounded rectangle by specifying its position and size.
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
 * @brief Sets the border range for a rectangle shape option. This function defines the geometric frame of a rectangle
 * by specifying its position and size.
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
 * @brief Insert a child render node at the specified position in the parent node.
 *
 * @param node the target parent node. Only customNode type parent nodes are supported.
 * @param child the child RenderNode to insert.
 * @param position the index at which to insert the child node.
 *     The position must be within the range [0, currentChildCount].
 *     If the position equals currentChildCount, it is equivalent to an add operation.
 * @return Error code.
 *     <ul><li>{@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *     </li><li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 *     </li><li>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if CAPI init error.
 *     </li><li>{@link ARKUI_ERROR_CODE_NOT_CUSTOM_NODE} The node is not a customNode.
 *     </li><li>{@link ARKUI_ERROR_CODE_CHILD_EXISTED} The node already has a child.
 *     </li><li>{@link ARKUI_ERROR_CODE_RENDER_PARENT_EXISTED} The child already has a parent node.
 *     </li><li>{@link ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE} if the child is obtained from a FrameNode,
 *     and its corresponding FrameNode is no longer in the adopted state.</li></ul>
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RenderNodeUtils_InsertRenderNodeAt(
    ArkUI_NodeHandle node, ArkUI_RenderNodeHandle child, int32_t position);

/**
 * @brief Get the number of child render nodes of the specified parent node.
 *
 * @param node the parent node to query.
 * @param count the count of the child render node.
 * @return Error code.
 *     <ul><li>{@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *     </li><li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 *     </li><li>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if CAPI init error.</li></ul>
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RenderNodeUtils_GetRenderNodeChildrenCount(ArkUI_NodeHandle node, int32_t* count);

/**
 * @brief Get the child render node at the specified position from the parent node.
 *
 * @param node Indicates the target parent node.
 * @param position Index location. The position must be in the range [0, childCount-1].
 * @param child the output parameter that will receive the child render node handle. Cannot be null.
 * @return Error code.
 *     <ul><li>{@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *     </li><li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 *     </li><li>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if CAPI init error.</li></ul>
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RenderNodeUtils_GetRenderNodeAt(
    ArkUI_NodeHandle node, int32_t position, ArkUI_RenderNodeHandle* child);
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_RENDER_H
/** @} */

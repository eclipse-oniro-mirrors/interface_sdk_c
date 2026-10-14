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
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 12
 */

/**
 * @file common_type.h
 *
 * @brief Defines the common types for ArkUI native APIs.
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
 * @brief Defines the pointer to an ArkUI native component object, which is used to identify and pass component
 * instances in ArkUI native APIs, for example, creating, mounting, removing, or destroying component nodes.
 *
 * @since 12
 */
typedef struct ArkUI_Node* ArkUI_NodeHandle;

/**
 * @brief Defines the pointer to an **ArkUI_NodeContent** object on the native side, which is used to reference and
 * pass a **NodeContent** instance in native APIs.
 *
 * @since 12
 */
typedef struct ArkUI_NodeContent* ArkUI_NodeContentHandle;

/**
 * @brief Sets the size constraints of a component during component layout.
 *
 * @since 12
 */
typedef struct ArkUI_LayoutConstraint ArkUI_LayoutConstraint;

/**
 * @brief Defines component drawing context, which is used to provide drawing context information during the drawing
 * of a custom component. You can obtain the canvas pointer used for drawing and the size of the drawing area.
 *
 * @since 12
 */
typedef struct ArkUI_DrawContext ArkUI_DrawContext;

/**
 * @brief Defines a context object of the ArkUI native UI, which is used to represent the UI context of the page
 * where the component is located. The pointer type is {@link ArkUI_ContextHandle}. You can obtain the context using
 * {@link OH_ArkUI_GetContextByNode} and use it as the input parameter for APIs such as dragging, animation, and UI
 * task scheduling.
 *
 * @since 12
 */
typedef struct ArkUI_Context ArkUI_Context;

/**
 * @brief Defines the pointer to the context object of ArkUI on the native side, which is used to represent the UI
 * context of the page where the component is located. You can obtain the pointer through
 * {@link OH_ArkUI_GetContextByNode} or {@link OH_ArkUI_GetContextFromNapiValue} and use the pointer as the context
 * input parameter for APIs such as UI task scheduling, animation, and focus control.
 *
 * @since 12
 */
typedef struct ArkUI_Context* ArkUI_ContextHandle;

/**
 * @brief Defines a component event. This is a general struct type. This struct is used to pass event information in the
 * component event handling process.
 *
 * @since 12
 */
typedef struct ArkUI_NodeEvent ArkUI_NodeEvent;

/**
 * @brief Provides an event callback type, which is used to define the callback function and its user-defined data.
 * When an API of this type is called to trigger a callback, the callback is invoked and **userData** is passed as
 * a parameter.
 *
 * @since 12
 */
typedef struct {
    /**
     * @brief Pointer to the user-defined data, which is passed as a parameter during callback.
     *
     * @since 12
     */
    void* userData;
    /**
     * @brief Pointer to the callback executed when an event is triggered. This callback does not return any value. When
     * the callback is triggered, the user-defined data pointed to by **userData** is passed as a parameter to execute
     * the custom processing logic. The specific triggering time is defined by the API of this type.
     *
     * @since 12
     */
    void (*callback)(void* userData);
} ArkUI_ContextCallback;

/**
 * @brief Defines a numeric type used by ArkUI on the native side, including floating-point, signed integer, and
 * unsigned integer types.
 *
 * @since 12
 */
typedef union {
    /**
     * @brief Variable of floating-point type, used to store floating-point values.
     *
     * @since 12
     */
    float f32;
    /**
     * @brief Variable of signed integer type, used to store signed integer values.
     *
     * @since 12
     */
    int32_t i32;
    /**
     * @brief Variable of unsigned integer type, used to store unsigned integer values.
     *
     * @since 12
     */
    uint32_t u32;
} ArkUI_NumberValue;

/**
 * @brief Defines the {@link setAttribute} function. This is a general input parameter struct. Individual
 * attribute-setting API can use appropriate member variables within it to store parameter data of specific types.
 *
 * @since 12
 */
typedef struct {
    /**
     * @brief Pointer to the numeric array used to store attribute parameters of the numeric type. The array length is
     * specified by **size**.
     *
     * @since 12
     */
    const ArkUI_NumberValue* value;
    /**
     * @brief Length of the **value** array, which must be used together with the **value** variable.
     *
     * @since 12
     */
    int32_t size;
    /**
     * @brief Pointer to the string used to store attribute parameters of the string type.
     *
     * @since 12
     */
    const char* string;
    /**
     * @brief Pointer to the object data used to store attribute parameters of the object type.
     *
     * @since 12
     */
    void* object;
} ArkUI_AttributeItem;

/**
 * @brief Defines a rectangular area.
 *
 * @since 12
 */
typedef struct {
    /**
     * @brief X coordinate of the rectangular area.
     *
     * @since 12
     */
    float x;
    /**
     * @brief Y coordinate of the rectangular area.
     *
     * @since 12
     */
    float y;
    /**
     * @brief Width of the rectangular area.
     *
     * @since 12
     */
    float width;
    /**
     * @brief Height of the rectangular area.
     *
     * @since 12
     */
    float height;
} ArkUI_Rect;

/**
 * @brief Describes the width and height of a component.
 *
 * @since 12
 */
typedef struct {
    /**
     * @brief Width, in px.
     *
     * @since 12
     */
    int32_t width;
    /**
     * @brief Height, in px.
     *
     * @since 12
     */
    int32_t height;
} ArkUI_IntSize;

/**
 * @brief Describes the position of a component.
 *
 * @since 12
 */
typedef struct {
    /**
     * @brief Horizontal coordinate, in px.
     *
     * @since 12
     */
    int32_t x;
    /**
     * @brief Vertical coordinate, in px.
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

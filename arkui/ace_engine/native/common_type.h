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
 * @brief Defines the pointer to the ArkUI native component object.
 *
 * @since 12
 */
typedef struct ArkUI_Node* ArkUI_NodeHandle;

/**
 * @brief Defines the pointer type of the ArkUI node content.
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
 * @brief Defines the structure of the component drawing context.
 *
 * @since 12
 */
typedef struct ArkUI_DrawContext ArkUI_DrawContext;

/**
 * @brief Defines the pointer to the context instance object of ArkUI on the native side.
 *
 * @since 12
 */
typedef struct ArkUI_Context* ArkUI_ContextHandle;

/**
 * @brief Defines the common structure type of a component event.
 *
 * @since 12
 */
typedef struct ArkUI_NodeEvent ArkUI_NodeEvent;

/**
 * @brief Defines the event callback type.
 *
 * @since 12
 */
typedef struct {
    /**
     * Custom type, data of a user-defined type that is passed as a parameter during callbacks.
     *
     * @since 12
     */
    void* userData;
    /**
     * Event callback.
     *
     * @since 12
     */
    void (*callback)(void* userData);
} ArkUI_ContextCallback;

/**
 * @brief Provides the number types of ArkUI in the native code.
 *
 * @since 12
 */
typedef union {
    /**
     * Floating-point type, used to store a floating-point value.
     *
     * @since 12
     */
    float f32;
    /**
     * Signed integer, used to store a signed integer value.
     *
     * @since 12
     */
    int32_t i32;
    /**
     * Unsigned integer, used to store an unsigned integer value.
     *
     * @since 12
     */
    uint32_t u32;
} ArkUI_NumberValue;

/**
 * @brief Defines the general input parameter structure of the node attribute functions.
 *
 * @since 12
 */
typedef struct {
    /**
     * A number array, used to store parameters of the number array type.
     *
     * @since 12
     */
    const ArkUI_NumberValue* value;
    /**
     * The size of the number array.
     *
     * @since 12
     */
    int32_t size;
    /**
     * String type, used to store parameters of the string type.
     *
     * @since 12
     */
    const char* string;
    /**
     * Object type, used to store parameters of the object type.
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
     * X coordinate of the rectangular area.
     *
     * @since 12
     */
    float x;
    /**
     * Y coordinate of the rectangular area.
     *
     * @since 12
     */
    float y;
    /**
     * Width of the rectangular area.
     *
     * @since 12
     */
    float width;
    /**
     * Height of the rectangular area.
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
     * Width, in px.
     *
     * @since 12
     */
    int32_t width;
    /**
     * Height, in px.
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
     * Horizontal coordinate, in px.
     *
     * @since 12
     */
    int32_t x;
    /**
     * Vertical coordinate, in px.
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

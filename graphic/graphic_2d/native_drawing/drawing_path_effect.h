/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
 * @brief Provides functions such as 2D graphics rendering, text drawing, and image display.
 *
 * @since 12
 * @version 1.0
 */
/**
 * @file drawing_path_effect.h
 *
 * @brief This file declares the functions related to the path effect in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_PATH_EFFECT_H
#define C_INCLUDE_DRAWING_PATH_EFFECT_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the drawing styles for path effects.
 *
 * @since 18
 * @version 1.0
 */
typedef enum {
    /**
     * Translation effect.
     */
    DRAWING_PATH_DASH_STYLE_TRANSLATE,
    /**
     * Rotation effect.
     */
    DRAWING_PATH_DASH_STYLE_ROTATE,
    /**
     * Morphing effect.
     */
    DRAWING_PATH_DASH_STYLE_MORPH,
} OH_Drawing_PathDashStyle;

/**
 * @brief Creates a path effect by sequentially applying the inner effect and then the outer effect.
 *
 * @param outer Pointer to an outer effect, which is an {@link OH_Drawing_PathEffect} object.
 * @param inner Pointer to an inner effect, which is an {@link OH_Drawing_PathEffect} object.
 * @return Returns a pointer to the created {@link OH_Drawing_PathEffect} object.
 * If a null pointer is returned, the creation fails. The possible failure cause is that **inner** or **inner** is a
 * null pointer.
 * @since 18
 * @version 1.0
 */
OH_Drawing_PathEffect* OH_Drawing_CreateComposePathEffect(OH_Drawing_PathEffect* outer, OH_Drawing_PathEffect* inner);

/**
 * @brief Creates a path effect that transforms the sharp angle between line segments into a rounded corner with the
 * specified radius.
 *
 * @param radius Radius of the rounded corner. The value is valid only when it is greater than 0.
 * @return Returns a pointer to the created {@link OH_Drawing_PathEffect} object.
 * If a null pointer is returned, the creation fails. The possible failure cause is that **radius** is less than or
 * equal to **0**.
 * @since 18
 * @version 1.0
 */
OH_Drawing_PathEffect* OH_Drawing_CreateCornerPathEffect(float radius);

/**
 * @brief Creates a dashed path effect. The dashed line effect is determined by a group of "on" and "off" intervals.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **intervals** is NULL or **count** is less than or equal to 0, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param intervals Pointer to the start address of the dashed line interval array. In the array, an even entry
 * indicates an "on" interval and an odd entry indicates an "off" interval. The unit is px.
 * @param count Number of entries in the dashed line interval array. The value must be an even number greater than 0.
 * @param phase Offset in the dashed line interval array.
 * @return Returns a pointer to the created {@link OH_Drawing_PathEffect} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_PathEffect* OH_Drawing_CreateDashPathEffect(float* intervals, int count, float phase);

/**
 * @brief Creates a path effect that segments the path and scatters the segments in an irregular pattern along the path.
 *
 * @param segLength Distance along the path at which each segment is fragmented. An effect is created when it is
 * greater than 0.
 * @param deviation Maximum amount by which the end points of the segments can be randomly displaced during rendering.
 * @return Returns a pointer to the created {@link OH_Drawing_PathEffect} object.
 * @since 18
 * @version 1.0
 */
OH_Drawing_PathEffect* OH_Drawing_CreateDiscretePathEffect(float segLength, float deviation);

/**
 * @brief Creates a dashed path effect.
 *
 * @param path Pointer to an {@link OH_Drawing_Path} object.
 * @param advance Length of each dashed line segment.
 * @param phase Offset of the pattern within the dash segment length.
 * @param type Style of the dashed path effect.
 * @return Returns a pointer to the created {@link OH_Drawing_PathEffect} object.
 * If a null pointer is returned, the creation fails. The possible failure cause is that **path** is a null pointer or *
 * *advance** is less than or equal to **0**.
 * @since 18
 * @version 1.0
 */
OH_Drawing_PathEffect* OH_Drawing_CreatePathDashEffect(const OH_Drawing_Path* path, float advance, float phase,
    OH_Drawing_PathDashStyle type);

/**
 * @brief Creates an overlay path effect based on two distinct path effects that take effect separately.
 *
 * @param firstPathEffect Pointer to an {@link OH_Drawing_PathEffect} object.
 * @param secondPathEffect Pointer to an {@link OH_Drawing_PathEffect} object.
 * @return Returns a pointer to the created {@link OH_Drawing_PathEffect} object.
 * If a null pointer is returned, the creation fails. The possible failure cause is that **firstPathEffect** or **
 * secondPathEffect** is a null pointer.
 * @since 18
 * @version 1.0
 */
OH_Drawing_PathEffect* OH_Drawing_CreateSumPathEffect(OH_Drawing_PathEffect* firstPathEffect,
    OH_Drawing_PathEffect* secondPathEffect);

/**
 * @brief Destroys an **OH_Drawing_PathEffect** object and reclaims the memory occupied by the object.
 *
 * @param pathEffect Pointer to an {@link OH_Drawing_PathEffect} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathEffectDestroy(OH_Drawing_PathEffect* pathEffect);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
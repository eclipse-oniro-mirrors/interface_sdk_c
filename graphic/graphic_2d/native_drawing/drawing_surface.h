/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
 * @since 8
 * @version 1.0
 */
/**
 * @file drawing_surface.h
 *
 * @brief This file declares the functions related to the surface in the drawing module, including creating, destroying,
 *  and using the surface.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_SURFACE_H
#define C_INCLUDE_DRAWING_SURFACE_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an **OH_Drawing_Surface** object using the GPU context to manage the content drawn on the canvas.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **gpuContext** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param gpuContext Pointer to an {@link OH_Drawing_GpuContext} object.
 * @param flag Whether the memory allocation is counted in the cache budget. **true** means yes; **false** otherwise.
 * @param imageInfo Image information struct.
 * @return Returns a pointer to the created {@link OH_Drawing_Surface} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Surface* OH_Drawing_SurfaceCreateFromGpuContext(
    OH_Drawing_GpuContext* gpuContext, bool flag, OH_Drawing_Image_Info imageInfo);

/**
 * @brief Creates an **OH_Drawing_Surface** object bound to the window using the GPU context to manage the content
 * drawn on the canvas.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **gpuContext** or **window** is NULL.
 *
 * @param gpuContext Pointer to an {@link OH_Drawing_GpuContext} object.
 * This object must be created by {@link OH_Drawing_GpuContextCreate}. Otherwise, the **OH_Drawing_Surface** object
 * fails to be created.
 * @param imageInfo Image information struct.
 * @param window Pointer to the window object.
 * @return Returns a pointer to the created {@link OH_Drawing_Surface} object.
 * @since 16
 * @version 1.0
 */
OH_Drawing_Surface* OH_Drawing_SurfaceCreateOnScreen(
    OH_Drawing_GpuContext* gpuContext, OH_Drawing_Image_Info imageInfo, void* window);

/**
 * @brief Obtains a canvas from an **OH_Drawing_Surface** object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **surface** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param surface Pointer to an **OH_Drawing_Surface** object.
 * @return Returns a pointer to the created {@link OH_Drawing_Canvas} object. The pointer returned does not need to be
 * managed by the caller.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Canvas* OH_Drawing_SurfaceGetCanvas(OH_Drawing_Surface* surface);

/**
 * @brief Pushes the drawing content from an **OH_Drawing_Surface** object to the GPU for rendering.
 *
 * @param surface Pointer to the created  {@link OH_Drawing_Surface}  object. This object must be created by calling
 * {@link OH_Drawing_SurfaceCreateOnScreen}
 * . Otherwise, calling the current API has no effect.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **surface** is NULL.
 * @since 16
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_SurfaceFlush(OH_Drawing_Surface* surface);

/**
 * @brief Destroys an **OH_Drawing_Surface** object and reclaims the memory occupied.
 *
 * @param surface Pointer to an **OH_Drawing_Surface** object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SurfaceDestroy(OH_Drawing_Surface* surface);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
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
 * @file drawing_gpu_context.h
 *
 * @brief This file declares the functions related to the GPU context in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_GPU_CONTEXT_H
#define C_INCLUDE_DRAWING_GPU_CONTEXT_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief This struct describes the options about the GPU context.
 *
 * @since 12
 * @version 1.0
 * @deprecated since 18
 */
typedef struct {
    /**
     * Whether to allow path mask textures to be cached. The value **true** means to allow the path mask textures to be
     * cached, and **false** means the opposite.
     */
    bool allowPathMaskCaching;
} OH_Drawing_GpuContextOptions;

/**
 * @brief Creates an **OH_Drawing_GpuContext** object that uses OpenGL as the backend interface.
 *
 * @param gpuContextOptions GPU context options, which is {@link OH_Drawing_GpuContextOptions}.
 * @return Returns the pointer to the {@link OH_Drawing_GpuContext} object created.
 * @since 12
 * @version 1.0
 * @deprecated since 18
 * @useinstead OH_Drawing_GpuContextCreate
 */
OH_Drawing_GpuContext* OH_Drawing_GpuContextCreateFromGL(OH_Drawing_GpuContextOptions gpuContextOptions);

/**
 * @brief Creates an **OH_Drawing_GpuContext** object, for which the backend type depends on the device.
 *
 * @return Returns the pointer to the {@link OH_Drawing_GpuContext} object created.
 * @since 16
 * @version 1.0
 */
OH_Drawing_GpuContext* OH_Drawing_GpuContextCreate(void);

/**
 * @brief Destroys an **OH_Drawing_GpuContext** object and reclaims the memory occupied by the object.
 *
 * @param gpuContext Pointer to an {@link OH_Drawing_GpuContext} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_GpuContextDestroy(OH_Drawing_GpuContext* gpuContext);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
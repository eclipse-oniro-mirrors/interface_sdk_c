/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @since 11
 * @version 1.0
 */
/**
 * @file drawing_mask_filter.h
 *
 * @brief This file declares the functions related to the mask filter in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_MASK_FILTER_H
#define C_INCLUDE_DRAWING_MASK_FILTER_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines an enum for the blur types.
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * Blurs both inside and outside the original border.
     */
    NORMAL,
    /**
     * Draws solid inside the border, and blurs outside.
     */
    SOLID,
    /**
     * Draws nothing inside the border, and blurs outside.
     */
    OUTER,
    /**
     * Blurs inside the border, and draws nothing outside.
     */
    INNER,
} OH_Drawing_BlurType;

/**
 * @brief Creates an **OH_Drawing_MaskFilter** object with a blur type.
 *
 * @param blurType Blur type.
 * @param sigma Standard deviation of the Gaussian blur to apply. The value must be greater than 0.
 * @param respectCTM Whether the blur standard deviation is modified by the current transformation matrix (CTM). The
 * default value is **true**. **true**: The blur standard deviation is affected by the CTM. **false**: The blur
 * standard deviation is fixed and not affected by the CTM.
 * @return Returns the pointer to the **OH_Drawing_MaskFilter** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_MaskFilter* OH_Drawing_MaskFilterCreateBlur(OH_Drawing_BlurType blurType, float sigma, bool respectCTM);

/**
 * @brief Destroys an **OH_Drawing_MaskFilter** object and reclaims the memory occupied by the object.
 *
 * @param maskFilter Pointer to an **OH_Drawing_MaskFilter** object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_MaskFilterDestroy(OH_Drawing_MaskFilter* maskFilter);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
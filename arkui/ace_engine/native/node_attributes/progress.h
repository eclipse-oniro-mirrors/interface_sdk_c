/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @brief Defines a set of Progress enum and interface.
 *
 * @since 12
 */

/**
 * @file progress.h
 *
 * @brief Defines enumerations and APIs related to **Progress**, supporting multiple progress indicator types such as
 * linear, ring, eclipse, and capsule, and providing customization capabilities for linear progress indicator style
 * options (smooth animation, scan effect, width, and corner radius). It is suitable for scenarios such as displaying
 * task progress and loading states, helping you quickly implement diverse progress displays and interactive feedback.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_PROGRESS_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_PROGRESS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the style option of a linear progress indicator. It is applicable to scenarios where the display
 * style of a linear progress indicator needs to be customized.
 *
 * @since 15
 */
typedef struct ArkUI_ProgressLinearStyleOption ArkUI_ProgressLinearStyleOption;

/**
 * @brief Enumerates progress indicator types.
 *
 * @since 12
 */
typedef enum {
    /** Linear style. */
    ARKUI_PROGRESS_TYPE_LINEAR = 0,
    /** Indeterminate ring style. */
    ARKUI_PROGRESS_TYPE_RING,
    /** Eclipse style. */
    ARKUI_PROGRESS_TYPE_ECLIPSE,
    /** Determinate ring style. */
    ARKUI_PROGRESS_TYPE_SCALE_RING,
    /** Capsule style. */
    ARKUI_PROGRESS_TYPE_CAPSULE
} ArkUI_ProgressType;

/**
 * @brief Creates a **ProgressLinearStyleOption** instance. After use, you must call
 * {@link OH_ArkUI_ProgressLinearStyleOption_Destroy} to release resources to avoid memory leaks.
 *
 * @return Pointer to the **ArkUI_ProgressLinearStyleOption** instance, which can be used to configure display styles
 *     such as smooth animation, scan effect, width, and corner radius of a linear progress indicator.
 *     <br>If a null pointer is returned, the memory may be insufficient.
 * @since 15
 */
ArkUI_ProgressLinearStyleOption* OH_ArkUI_ProgressLinearStyleOption_Create(void);

/**
 * @brief Destroys a **ProgressLinearStyleOption** instance. This API must be used in pair with
 * {@link OH_ArkUI_ProgressLinearStyleOption_Create}. The **option** parameter should be obtained through **
 * OH_ArkUI_ProgressLinearStyleOption_Create()**, and the object should not be used after **
 * OH_ArkUI_ProgressLinearStyleOption_Destroy()** is called.
 *
 * @param option Pointer to the **ProgressLinearStyleOption** instance, which is obtained through **
 *     OH_ArkUI_ProgressLinearStyleOption_Create()**.
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_Destroy(ArkUI_ProgressLinearStyleOption* option);

/**
 * @brief Sets whether to enable the scan effect. It is suitable for loading scenarios that require enhanced visual
 * feedback of the progress indicator, such as data loading and file upload. The scan effect refers to the dynamic
 * visual effect of a light beam scanning across the progress indicator.
 *
 * @param option Pointer to the **ProgressLinearStyleOption** instance. It should be created using **
 *     OH_ArkUI_ProgressLinearStyleOption_Create()**.
 * @param enabled Whether to enable the scan effect.
 *     <br>**true**: Enable the scan effect.
 *     <br>**false**: Disable the scan effect.
 *     <br>Default value: **false**.
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetScanEffectEnabled(ArkUI_ProgressLinearStyleOption* option, bool enabled);

/**
 * @brief Sets whether to enable the smooth effect.
 *
 * @param option Pointer to the **ProgressLinearStyleOption** instance. It should be created using **
 *     OH_ArkUI_ProgressLinearStyleOption_Create()**.
 * @param enabled Whether to enable the smooth effect. When this effect is enabled, the progress changes smoothly from
 *     the current value to the target value. When this effect is disabled, the progress changes abruptly to the target
 *     value.
 *     <br>**true**: Enable the smooth effect.
 *     <br>**false**: Disable the smooth effect.
 *     <br>Default value: **true**.
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetSmoothEffectEnabled(ArkUI_ProgressLinearStyleOption* option, bool enabled);

/**
 * @brief Sets the stroke width for a progress indicator.
 *
 * @param option Pointer to the **ProgressLinearStyleOption** instance. It should be created using **
 *     OH_ArkUI_ProgressLinearStyleOption_Create()**.
 * @param strokeWidth Stroke width of the progress indicator, in vp.  Percentage values are not supported. The value
 *     must be greater than 0. If an invalid value is passed, the default value is used. Default value: **4.0vp**.
 *     Setting **strokeWidth** affects the value range of **strokeRadius**, which is [0, strokeWidth/2].
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetStrokeWidth(ArkUI_ProgressLinearStyleOption* option, float strokeWidth);

/**
 * @brief Sets the corner radius for a progress indicator.
 *
 * @param option Pointer to the **ProgressLinearStyleOption** instance. It should be created using **
 *     OH_ArkUI_ProgressLinearStyleOption_Create()**.
 * @param strokeRadius Corner radius of the progress indicator, in vp. The value range is [0, strokeWidth/2]. The value
 *     **0** indicates a right-angle corner. A larger value indicates a more obvious corner radius effect. The maximum
 *     value indicates a fully rounded corner. If the value is out of range, it is automatically corrected to the
 *     boundary value. Default value: **strokeWidth/2**.
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetStrokeRadius(ArkUI_ProgressLinearStyleOption* option, float strokeRadius);

/**
 * @brief Obtains the enabled status of the scan effect.
 *
 * @param option Pointer to the **ProgressLinearStyleOption** instance. It should be created using **
 *     OH_ArkUI_ProgressLinearStyleOption_Create()**.
 * @return Whether the scan effect is enabled. **true**: The scan effect is enabled. **false**: The scan effect is
 *     disabled. The default value is **false**.
 * @since 15
 */
bool OH_ArkUI_ProgressLinearStyleOption_GetScanEffectEnabled(ArkUI_ProgressLinearStyleOption* option);

/**
 * @brief Obtains the enabled status of the smooth effect.
 *
 * @param option Pointer to the **ProgressLinearStyleOption** instance. It should be created using **
 *     OH_ArkUI_ProgressLinearStyleOption_Create()**.
 * @return Whether the smooth effect is enabled. **true**: The smooth effect is enabled. **false**: The smooth effect
 *     is disabled. The default value is **true**.
 * @since 15
 */
bool OH_ArkUI_ProgressLinearStyleOption_GetSmoothEffectEnabled(ArkUI_ProgressLinearStyleOption* option);

/**
 * @brief Obtains the stroke width of the progress indicator.
 *
 * @param option Pointer to the **ProgressLinearStyleOption** instance. It should be created using **
 *     OH_ArkUI_ProgressLinearStyleOption_Create()**.
 * @return Stroke width of the progress indicator, in vp.
 * @since 15
 */
float OH_ArkUI_ProgressLinearStyleOption_GetStrokeWidth(ArkUI_ProgressLinearStyleOption* option);

/**
 * @brief Obtains the corner radius of the progress indicator.
 *
 * @param option Pointer to the **ProgressLinearStyleOption** instance. It should be created using **
 *     OH_ArkUI_ProgressLinearStyleOption_Create()**.
 * @return Corner radius of the progress indicator, in vp.
 * @since 15
 */
float OH_ArkUI_ProgressLinearStyleOption_GetStrokeRadius(ArkUI_ProgressLinearStyleOption* option);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_PROGRESS_H
/** @} */
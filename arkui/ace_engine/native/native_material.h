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
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 26.0.0
 */

/**
 * @file native_material.h
 *
 * @brief Provides immersive material types and API declarations for ArkUI on the native side, to implement immersive
 * UI effects such as the blurred background in semi-transparent mode and light sensing interaction feedback.
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 26.0.0
 */
#ifndef ARKUI_NATIVE_MATERIAL_H
#define ARKUI_NATIVE_MATERIAL_H

#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the immersive material styles.
 * Different styles correspond to different material parameters, which affect the thickness of the material.
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * Ultra thin style. The material layer is ultra thin, with a very strong transparency effect.
     *
     * @since 26.0.0
     */
    ARKUI_IMMERSIVE_STYLE_ULTRA_THIN = 0,
    /**
     * Thin style. The material layer is thin, with a strong transparency effect.
     *
     * @since 26.0.0
     */
    ARKUI_IMMERSIVE_STYLE_THIN,
    /**
     * Regular style. The material layer has a standard thickness with balanced visual effect.
     *
     * @since 26.0.0
     */
    ARKUI_IMMERSIVE_STYLE_REGULAR,
    /**
     * Thick style. The blur effect is strong.
     *
     * @since 26.0.0
     */
    ARKUI_IMMERSIVE_STYLE_THICK,
    /**
     * Ultra thick style.
     *
     * @since 26.0.0
     */
    ARKUI_IMMERSIVE_STYLE_ULTRA_THICK,
} ArkUI_ImmersiveStyle;

/**
 * @brief Enumerates the material levels, which indicate the computing power level of the device.
 * Use {@link OH_ArkUI_NativeModule_GetGlobalMaterialLevel} to obtain the material level of the current device.
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * Exquisite level. The effect is exquisite and is suitable for high-end computing device.
     *
     * @since 26.0.0
     */
    ARKUI_MATERIAL_LEVEL_EXQUISITE = 0,
    /**
     * Gentle level. The effect is gentle and is suitable for mid-range computing device.
     *
     * @since 26.0.0
     */
    ARKUI_MATERIAL_LEVEL_GENTLE,
    /**
     * Smooth level. The effect is smooth and is suitable for low-end computing device.
     *
     * @since 26.0.0
     */
    ARKUI_MATERIAL_LEVEL_SMOOTH,
} ArkUI_MaterialLevel;

/**
 * @brief Defines an immersive material object on the native side, which provides adaptive visual effects based on the
 * device computing power level.
 * @since 26.0.0
 */
typedef struct ArkUI_ImmersiveMaterial ArkUI_ImmersiveMaterial;

/**
 * @brief Defines the pointer to an immersive material object, which is used to implement immersive visual effects.
 * @since 26.0.0
 */
typedef struct ArkUI_ImmersiveMaterial* ArkUI_ImmersiveMaterialHandle;

/**
 * @brief Defines a light sensing interaction effect configuration object for immersive materials, which is used to
 * configure the light sensing response effect generated when users interact with immersive materials. For details
 * about the design logic, see {@link native_material.h}. An immersive material is a visual material style with a sense
 * of depth and layering, and the light sensing interaction effect refers to the light and shadow visual feedback
 * generated when users interact with components. After creation, the configuration object must be set to the immersive
 * material object through {@link OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect} to take effect.
 * @since 26.0.0
 */
typedef struct ArkUI_LightEffectOptions ArkUI_LightEffectOptions;

/**
 * @brief Defines the pointer to the light effect options.
 *
 * @since 26.0.0
 */
typedef ArkUI_LightEffectOptions* ArkUI_LightEffectOptionsHandle;

/**
 * @brief Checks whether the current device supports system materials (that is, the built-in material rendering
 * capability of the device system).
 * @return Whether the current device supports system materials. The value **true** indicates that the current device
 * supports system materials, and **false** indicates the opposite.
 * @since 26.0.0
 */
bool OH_ArkUI_NativeModule_GetSystemMaterialSupported();

/**
 * @brief Obtains the global material level, which is related to the device computing power. This configuration item is
 * defined by the device and cannot be modified.
 * @return Material level of the device.
 * {@link ARKUI_MATERIAL_LEVEL_EXQUISITE} (0): material level for devices with high-level computing power.
 * {@link ARKUI_MATERIAL_LEVEL_GENTLE} (1): material level for devices with medium-level computing power.
 * {@link ARKUI_MATERIAL_LEVEL_SMOOTH} (2): material level for devices with low-level computing power.
 * @since 26.0.0
 */
ArkUI_MaterialLevel OH_ArkUI_NativeModule_GetGlobalMaterialLevel();

/**
 * @brief Creates an immersive material object with a specified style. The material level of the created object follows
 * the global material level, which can be obtained through {@link OH_ArkUI_NativeModule_GetGlobalMaterialLevel}.
 * @param style Material style. Passing an invalid style will cause the setting failure, and the error code
 * {@link ARKUI_ERROR_CODE_PARAM_INVALID} will be returned. This style is effective only for the display effect on
 * devices with high- and mid-level computing power, and has no effect on devices with low-level computing power but no
 * error will be reported.
 * @return Pointer to the created immersive material object. If the creation fails or the material style is invalid,
 * null is returned.
 * The returned object must be released by calling {@link OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy} after being
 * used.
 * @release native_material/OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy {return}
 * @since 26.0.0
 */
ArkUI_ImmersiveMaterialHandle OH_ArkUI_NativeModule_ImmersiveMaterial_Create(ArkUI_ImmersiveStyle style);

/**
 * @brief Destroys the immersive material object.
 * @param material Pointer to the immersive material object.
 * @since 26.0.0
 */
void OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy(ArkUI_ImmersiveMaterialHandle material);

/**
 * @brief Sets a style for an immersive material object. This attribute is valid only for display effects of devices
 * with high- and mid-level computing power. It does not take effect for devices with low-level computing power, but no
 * error is reported. You can call {@link OH_ArkUI_NativeModule_GetGlobalMaterialLevel} to obtain the material level of
 * the current device to determine whether this attribute takes effect.
 * @param material Pointer to the immersive material object.
 * If **material** is **NULL**, the API returns the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID}.
 * @param style Material style. Passing an invalid style will cause the setting failure, and the error code
 * {@link ARKUI_ERROR_CODE_PARAM_INVALID} will be returned.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 * Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs (**material** is **NULL** or **style** is
 * invalid). Ensure that a valid material pointer and a valid style enumerated value are passed.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetStyle(
    ArkUI_ImmersiveMaterialHandle material, ArkUI_ImmersiveStyle style);

/**
 * @brief Obtains the style of an immersive material object.
 * @param material Pointer to the immersive material object.
 * @param style Pointer to the variable used to receive the material style.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 * Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs (**material** or **style** is **NULL**).
 * Ensure that both **material** and **style** are valid pointers.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetStyle(
    ArkUI_ImmersiveMaterialHandle material, ArkUI_ImmersiveStyle* style);

/**
 * @brief Sets a material color for an immersive material object. This attribute is valid for the display effects on
 * devices with all computing power levels. You can call {@link OH_ArkUI_NativeModule_GetGlobalMaterialLevel} to obtain
 * the material level of the current device to determine whether this attribute takes effect. If this parameter is not
 * set, the default value **0** is used, indicating the transparent color.
 * @param material Pointer to the immersive material object.
 * If **material** is **NULL**, the API returns the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID}.
 * @param color Material color, in 0xAARRGGBB format, which takes effect on the display effects of devices with all
 * computing power levels. The value **0** indicates transparent (default value).
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 * Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs (**material** is **NULL**). Ensure that
 * **material** is a valid pointer.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetMaterialColor(
    ArkUI_ImmersiveMaterialHandle material, uint32_t color);

/**
 * @brief Obtains the material color of an immersive material object.
 * @param material Pointer to the immersive material object.
 * @param color Pointer to the variable used to receive the material color in 0xAARRGGBB format.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 * Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs (**material** or **color** is **NULL**).
 * Ensure that both **material** and **color** are valid pointers.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetMaterialColor(
    ArkUI_ImmersiveMaterialHandle material, uint32_t* color);

/**
 * @brief Sets whether to apply a shadow to an immersive material object. This parameter takes effect for materials of
 * all levels.
 * @param material Pointer to the immersive material object.
 * @param applyShadow Whether to apply a shadow to the material. The value **true** indicates that the material shadow
 * takes effect and takes precedence over the common shadow attribute. The value **false** indicates that the material
 * shadow is not added and the common shadow attribute takes effect. The default value is **true**.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 * Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs (**material** is **NULL**). Ensure that
 * **material** is a valid pointer.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetApplyShadow(
    ArkUI_ImmersiveMaterialHandle material, bool applyShadow);

/**
 * @brief Obtains whether a shadow is applied to an immersive material object.
 * @param material Pointer to the immersive material object.
 * @param applyShadow Pointer to the variable used to receive whether the shadow is applied. If never explicitly set,
 * this pointer receives the default value **true**.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 * Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs (**material** or **applyShadow** is
 * **NULL**). Ensure that both **material** and **applyShadow** are valid pointers.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetApplyShadow(
    ArkUI_ImmersiveMaterialHandle material, bool* applyShadow);

/**
 * @brief Sets whether an immersive material object can be interactively deformed. That is, whether the material
 * generates a visual deformation response during user interaction (such as touch and press). This parameter takes
 * effect for materials of all levels.
 * @param material Pointer to the immersive material object.
 * @param interactive Whether interactive deformation can be performed for a material. The value **true** indicates
 * that interactive deformation can be performed for a material, and **false** indicates the opposite. If this
 * parameter is not set, the component behavior is followed.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 * Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs (**material** is **NULL**). Ensure that
 * **material** is a valid pointer.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetInteractive(
    ArkUI_ImmersiveMaterialHandle material, bool interactive);

/**
 * @brief Obtains whether an immersive material object can be interactively deformed. You are advised to call
 * {@link OH_ArkUI_NativeModule_ImmersiveMaterial_SetInteractive} to set this attribute before calling this API. If this
 * attribute has never been set, {@link ARKUI_ERROR_CODE_PARAM_ERROR} will be returned.
 * @param material Pointer to the immersive material object.
 * If **material** is **NULL**, the API returns the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID}.
 * @param interactive Pointer to the variable used to receive whether the material supports interactive deformation.
 * If **interactive** is **NULL**, the API returns the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID}.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 * Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs (**material** or **interactive** is
 * **NULL**). Ensure that both **material** and **interactive** are valid pointers.
 * Returns {@link ARKUI_ERROR_CODE_PARAM_ERROR} if this attribute has never been set. Call
 * **OH_ArkUI_NativeModule_ImmersiveMaterial_SetInteractive** to set this attribute before obtaining it.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetInteractive(
    ArkUI_ImmersiveMaterialHandle material, bool* interactive);

/**
 * @brief Creates a light sensing interaction effect configuration object, which is used to configure the effect of
 * highlighted feedback upon touch for an immersive material. The default color is white (0xffffffff). After the
 * creation is complete, you need to call {@link OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect} to set the
 * configuration object to the immersive material object for the configuration to take effect.
 * @return Pointer to the created light sensing interaction effect configuration object. The returned object must be
 * released by calling {@link OH_ArkUI_NativeModule_LightEffectOptions_Destroy} after being used.
 * @release native_material/OH_ArkUI_NativeModule_LightEffectOptions_Destroy {return}
 * @since 26.0.0
 */
ArkUI_LightEffectOptionsHandle OH_ArkUI_NativeModule_LightEffectOptions_Create();

/**
 * @brief Destroys the light sensing interaction effect configuration object.
 * @param options Pointer to the light sensing interaction effect configuration object.
 * @since 26.0.0
 */
void OH_ArkUI_NativeModule_LightEffectOptions_Destroy(ArkUI_LightEffectOptionsHandle options);

/**
 * @brief Sets a color for the light sensing interaction effect. If this parameter is not set, the default color is
 * white (0xffffffff).
 * @param options Pointer to the light sensing interaction effect configuration object.
 * @param color Color of the light sensing interaction effect, in 0xAARRGGBB format. If this parameter is not set, the
 * default color is white (0xffffffff).
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 * Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs (**options** is **NULL**). Ensure that
 * **options** is a valid pointer.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_LightEffectOptions_SetColor(
    ArkUI_LightEffectOptionsHandle options, uint32_t color);

/**
 * @brief Sets the light sensing interaction effect for an immersive material object, that is, the light reflection on
 * the material surface that dynamically changes with user interaction. This parameter takes effect for materials of
 * all levels.
 * @param material Pointer to the immersive material object.
 * @param options Pointer to the light sensing interaction effect configuration object. A null pointer disables the
 * light sensing interaction effect, and a non-null enables it. A non-null pointer must be created through
 * {@link OH_ArkUI_NativeModule_LightEffectOptions_Create}.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 * Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs (**material** is **NULL**). Ensure that
 * **material** is a valid pointer.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect(
    ArkUI_ImmersiveMaterialHandle material, const ArkUI_LightEffectOptionsHandle options);

/**
 * @brief Obtains the color of the light sensing interaction effect for an immersive material object.
 * @param material Pointer to the immersive material object.
 * @param color Pointer to the variable used to receive the light sensing interaction effect color in 0xAARRGGBB format.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 * Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs (**material** or **color** is **NULL**).
 * Ensure that both **material** and **color** are valid pointers.
 * Returns {@link ARKUI_ERROR_CODE_PARAM_ERROR} if the light sensing interaction effect has never been set or has been
 * disabled. Call **OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect** first to set a non-null light sensing
 * interaction effect configuration pointer before obtaining the color.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetLightEffectColor(
    ArkUI_ImmersiveMaterialHandle material, uint32_t* color);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_MATERIAL_H
/** @} */

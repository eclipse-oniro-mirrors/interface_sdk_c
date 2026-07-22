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
 * @brief 提供ArkUI在Native侧的沉浸式材质类型和API声明，用于实现半透明模糊背景、光感交互反馈等沉浸式UI效果。
 *
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
     * 超薄样式。材质层极薄，透明度效果极强。
     *
     * @since 26.0.0
     */
    ARKUI_IMMERSIVE_STYLE_ULTRA_THIN = 0,
    /**
     * 薄样式。材质层较薄，透明度效果强。
     *
     * @since 26.0.0
     */
    ARKUI_IMMERSIVE_STYLE_THIN,
    /**
     * 常规样式。材质层厚度标准，视觉效果均衡。
     *
     * @since 26.0.0
     */
    ARKUI_IMMERSIVE_STYLE_REGULAR,
    /**
     * 厚样式。模糊效果强。
     *
     * @since 26.0.0
     */
    ARKUI_IMMERSIVE_STYLE_THICK,
    /**
     * 超厚样式。
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
     * 高算力设备材质等级。
     *
     * @since 26.0.0
     */
    ARKUI_MATERIAL_LEVEL_EXQUISITE = 0,
    /**
     * 中算力设备材质等级。
     *
     * @since 26.0.0
     */
    ARKUI_MATERIAL_LEVEL_GENTLE,
    /**
     * 低算力设备材质等级。
     *
     * @since 26.0.0
     */
    ARKUI_MATERIAL_LEVEL_SMOOTH,
} ArkUI_MaterialLevel;

/**
 * @brief 定义Native侧的沉浸式材质对象，根据设备算力等级提供适配的视觉效果。<br>沉浸式材质的等级根据设备算力等级而不同。<br>材质等级由{@link ArkUI_MaterialLevel}定义，可通过
 * {@link OH_ArkUI_NativeModule_GetGlobalMaterialLevel}获取。<br>在高算力和中算力设备上，会影响沉浸式材质渲染层的滤镜效果和阴影（{@link NODE_SHADOW}或
 * {@link NODE_CUSTOM_SHADOW}）效果。在低算力设备上，会影响背景颜色{@link NODE_BACKGROUND_COLOR}、边框颜色{@link NODE_BORDER_COLOR}、边框宽度
 * {@link NODE_BORDER_WIDTH}和阴影（{@link NODE_SHADOW}或{@link NODE_CUSTOM_SHADOW}）效果。
 *
 * @since 26.0.0
 */
typedef struct ArkUI_ImmersiveMaterial ArkUI_ImmersiveMaterial;

/**
 * @brief 定义指向沉浸式材质对象的指针，沉浸式材质用于实现的沉浸式视觉效果对象。<br>可以通过{@link OH_ArkUI_NativeModule_ImmersiveMaterial_Create}创建沉浸式材质对象，
 * 创建后必须在使用完毕时调用{@link OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy}销毁沉浸式材质对象以释放资源，避免内存泄漏。
 *
 * @since 26.0.0
 */
typedef struct ArkUI_ImmersiveMaterial* ArkUI_ImmersiveMaterialHandle;

/**
 * @brief 定义沉浸式材质的光感交互效果配置对象。<br>创建时默认光感交互颜色为白色（0xffffffff）。
 *
 * @since 26.0.0
 */
typedef struct ArkUI_LightEffectOptions ArkUI_LightEffectOptions;

/**
 * @brief 定义指向光感交互效果配置对象的指针。可以通过{@link OH_ArkUI_NativeModule_LightEffectOptions_Create}创建光感交互效果配置对象，通过
 * {@link OH_ArkUI_NativeModule_LightEffectOptions_Destroy}接口销毁光感交互效果配置对象。
 *
 * @since 26.0.0
 */
typedef ArkUI_LightEffectOptions* ArkUI_LightEffectOptionsHandle;

/**
 * @brief 检查当前设备是否支持系统材质（即设备系统内置的材质渲染能力）。
 * <br>如果返回true，则可以使用{@link NODE_SYSTEM_MATERIAL}属性，否则设置该属性将无效。该配置项由设备定义，不可修改。
 *
 * @return 返回当前设备是否支持系统材质。true表示当前设备支持系统材质，false表示当前设备不支持系统材质。
 * @since 26.0.0
 */
bool OH_ArkUI_NativeModule_GetSystemMaterialSupported();

/**
 * @brief 获取全局材质等级，与设备的算力相关。该配置项由设备定义，不可修改。
 *
 * @return 返回设备的材质等级。返回类型为{@link ArkUI_MaterialLevel}。
 * @since 26.0.0
 */
ArkUI_MaterialLevel OH_ArkUI_NativeModule_GetGlobalMaterialLevel();

/**
 * @brief 创建具有指定样式的沉浸式材质对象。创建的材质等级跟随全局材质等级，可通过{@link OH_ArkUI_NativeModule_GetGlobalMaterialLevel}获取。
 *
 * @param style 材质样式。
 * @return 返回指向创建的沉浸式材质对象的指针。如果创建失败或材质样式无效，返回NULL。
 *     <br>返回的对象使用完后需要通过{@link OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy}释放。
 * @release native_material/OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy {return}
 * @since 26.0.0
 */
ArkUI_ImmersiveMaterialHandle OH_ArkUI_NativeModule_ImmersiveMaterial_Create(ArkUI_ImmersiveStyle style);

/**
 * @brief 销毁沉浸式材质对象。
 *
 * @param material 指向沉浸式材质对象的指针。
 * @since 26.0.0
 */
void OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy(ArkUI_ImmersiveMaterialHandle material);

/**
 * @brief 设置沉浸式材质对象的样式。该参数仅对高算力和中算力设备的显示效果有效，对低算力设备不生效但不会报错。
 *
 * @param material 指向沉浸式材质对象的指针。
 * @param style 材质样式。传入无效样式将导致创建失败并返回NULL。
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常（material为NULL或style无效）。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetStyle(
    ArkUI_ImmersiveMaterialHandle material, ArkUI_ImmersiveStyle style);

/**
 * @brief 获取沉浸式材质对象的样式。
 *
 * @param material 指向沉浸式材质对象的指针。
 * @param style 指向用于接收材质样式的变量的指针。
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常（material为NULL或style为NULL）。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetStyle(
    ArkUI_ImmersiveMaterialHandle material, ArkUI_ImmersiveStyle* style);

/**
 * @brief 设置沉浸式材质对象的材质颜色。该参数仅对高算力和中算力设备的显示效果有效，对低算力设备不生效但不会报错。如果不设置，默认值为0，表示透明色。
 *
 * @param material 指向沉浸式材质对象的指针。
 * @param color 材质颜色，0xAARRGGBB格式。传入0表示透明（默认值）。
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常（material为NULL）。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetMaterialColor(
    ArkUI_ImmersiveMaterialHandle material, uint32_t color);

/**
 * @brief 获取沉浸式材质对象的材质颜色。
 *
 * @param material 指向沉浸式材质对象的指针。
 * @param color 指向用于接收0xAARRGGBB格式的材质颜色的变量的指针。
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常（material为NULL或color为NULL）。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetMaterialColor(
    ArkUI_ImmersiveMaterialHandle material, uint32_t* color);

/**
 * @brief 设置沉浸式材质对象是否应用阴影。该参数对所有等级材质都生效。
 * <br>当该参数为true时，材质中的阴影效果生效，优先于阴影通用属性。当该参数为false时，阴影通用属性生效，材质无阴影效果。如果不设置，默认值为true。
 *
 * @param material 指向沉浸式材质对象的指针。
 * @param applyShadow 是否添加材质效果的阴影。true表示材质阴影生效并优先于阴影通用属性，false表示不添加材质阴影、阴影通用属性生效。默认值为true。
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常（material为NULL）。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetApplyShadow(
    ArkUI_ImmersiveMaterialHandle material, bool applyShadow);

/**
 * @brief 获取沉浸式材质对象是否应用阴影。
 *
 * @param material 指向沉浸式材质对象的指针。
 * @param applyShadow 指向用于接收是否应用阴影的变量的指针。默认值为true。
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常（material为NULL或applyShadow为NULL）。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetApplyShadow(
    ArkUI_ImmersiveMaterialHandle material, bool* applyShadow);

/**
 * @brief 设置沉浸式材质对象是否可交互形变。即材质在用户交互（如触摸、按压）时是否产生视觉形变响应。该参数对所有等级材质都生效。
 * <br>当该参数为true时，材质可交互形变。当该参数为false时，材质不可交互形变。如果不设置，遵循组件的行为。
 *
 * @param material 指向沉浸式材质对象的指针。
 * @param interactive 材质是否可交互形变。true表示材质可交互形变，false表示材质不可交互形变。如果不设置，遵循组件的行为。
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常（material为NULL）。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetInteractive(
    ArkUI_ImmersiveMaterialHandle material, bool interactive);

/**
 * @brief 获取沉浸式材质对象是否可交互形变。
 * <br>如果从未设置过该属性，函数将返回{@link ARKUI_ERROR_CODE_PARAM_ERROR}。
 *
 * @param material 指向沉浸式材质对象的指针。
 * @param interactive 指向用于接收材质是否可交互形变的变量的指针。
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常（material为NULL或interactive为NULL）。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_ERROR} 从未设置过该属性。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetInteractive(
    ArkUI_ImmersiveMaterialHandle material, bool* interactive);

/**
 * @brief 创建光感交互效果配置对象，用于配置沉浸式材质的触摸高亮反馈效果。默认颜色为白色（0xffffffff）。创建完成后，需通过
 * {@link OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect}将配置对象设置到沉浸式材质对象上才能生效。
 *
 * @return 返回指向创建的光感交互效果配置对象的指针。返回的对象使用完后需要通过{@link OH_ArkUI_NativeModule_LightEffectOptions_Destroy}释放。
 * @release native_material/OH_ArkUI_NativeModule_LightEffectOptions_Destroy {return}
 * @since 26.0.0
 */
ArkUI_LightEffectOptionsHandle OH_ArkUI_NativeModule_LightEffectOptions_Create();

/**
 * @brief 销毁光感交互效果配置对象。
 *
 * @param options 指向光感交互效果配置对象的指针。
 * @since 26.0.0
 */
void OH_ArkUI_NativeModule_LightEffectOptions_Destroy(ArkUI_LightEffectOptionsHandle options);

/**
 * @brief 设置光感交互效果的颜色。如果不设置，默认颜色为白色（0xffffffff）。
 *
 * @param options 指向光感交互效果配置对象的指针。
 * @param color 光感交互效果颜色，0xAARRGGBB格式。如果不设置，默认颜色为白色（0xffffffff）。
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常（options为NULL）。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_LightEffectOptions_SetColor(
    ArkUI_LightEffectOptionsHandle options, uint32_t color);

/**
 * @brief 设置沉浸式材质对象的光感交互效果，即在材质表面呈现随用户交互动态变化的光效反射。该参数对所有等级材质都生效。
 * <br>传入NULL的光感交互效果配置指针表示禁用光感交互效果，传入非NULL的光感交互效果配置指针表示使用该配置参数进行光感交互。如果不调用该接口设置，光感交互效果遵循组件的行为。
 *
 * @param material 指向沉浸式材质对象的指针。
 * @param options 指向光感交互效果配置对象的指针。传入NULL禁用光感交互效果，传入非NULL启用。
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常（material为NULL）。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect(
    ArkUI_ImmersiveMaterialHandle material, const ArkUI_LightEffectOptionsHandle options);

/**
 * @brief 获取沉浸式材质对象的光感交互效果颜色。
 * <br>只有在调用{@link OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect}成功设置非NULL的光感交互效果配置指针后，此接口才能成功获取颜色值。
 * 如果从未设置过光感交互效果或已禁用（传入NULL的光感交互效果配置指针），函数将返回{@link ARKUI_ERROR_CODE_PARAM_ERROR}。
 *
 * @param material 指向沉浸式材质对象的指针。
 * @param color 指向用于接收光感交互效果颜色的变量的指针。
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常（material为NULL或color为NULL）。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_ERROR} 光感交互效果从未设置或已禁用。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetLightEffectColor(
    ArkUI_ImmersiveMaterialHandle material, uint32_t* color);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_MATERIAL_H
/** @} */

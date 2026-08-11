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
 * @brief EmbeddedComponent组件相关的结构体和方法定义。
 *
 * @since 12
 */

/**
 * @file embedded_component.h
 *
 * @brief 声明EmbeddedComponent组件选项（ArkUI_EmbeddedComponentOption）相关的结构体和方法。\n
 * 开发者可通过这些方法创建、销毁组件选项对象，
 * 并为EmbeddedComponent组件设置运行异常回调（onError）和正常退出回调（onTerminated）。
 *
 * @sample [embedded_component_sample](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/DocsSample/ArkUISample/UIExtensionAndAccessibility)
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @include <arkui/embedded_component.h>
 * @since 12
 */
#ifndef ARKUI_EMBEDDED_COMPONENT_H
#define ARKUI_EMBEDDED_COMPONENT_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 声明元能力want结构。
 *
 * @since 20
 */
typedef struct AbilityBase_Want AbilityBase_Want;

/**
 * @brief 为EmbeddedComponent定义配置参数ArkUI_EmbeddedComponentOption，用于在创建或配置EmbeddedComponent时设置该组件的配置选项，
 * 适用于需要在页面中嵌入并管理其他组件的嵌入式UI开发场景。
 *
 * @since 20
 */
typedef struct ArkUI_EmbeddedComponentOption ArkUI_EmbeddedComponentOption;

/**
 * @brief 创建EmbeddedComponent组件选项的对象。
 *
 * @return 返回指向EmbeddedComponent组件选项的对象的指针。
 * @since 20
 */
ArkUI_EmbeddedComponentOption* OH_ArkUI_EmbeddedComponentOption_Create();

/**
 * @brief 删除EmbeddedComponent组件选项的对象。
 *
 * @param option 要销毁的EmbeddedComponent组件选项的对象的指针。
 * @since 20
 */
void OH_ArkUI_EmbeddedComponentOption_Dispose(ArkUI_EmbeddedComponentOption* option);

/**
 * @brief 设置EmbeddedComponent组件的{@link onError}回调。
 * EmbeddedComponent组件在运行过程中发生异常时触发本回调。
 *
 * @param option EmbeddedComponent组件选项的对象的指针。
 * @param callback 开发者自定义回调函数。
        - code：接口调用失败返回的错误码信息。错误码的详细介绍请参考[UIExtension错误码](errorcode-uiextension.md)。
        - name：接口调用失败返回的名称信息。
        - message：接口调用失败返回的详细信息。
 * @since 20
 */
void OH_ArkUI_EmbeddedComponentOption_SetOnError(
    ArkUI_EmbeddedComponentOption* option, void (*callback)(int32_t code, const char* name, const char* message));

/**
 * @brief 设置EmbeddedComponent组件的{@link onTerminated}回调。
 * EmbeddedComponent组件正常退出时触发本回调。
 *
 * @param option EmbeddedComponent组件选项的对象的指针。
 * @param callback 开发者自定义回调函数。
         - code：被拉起EmbeddedUIExtensionAbility退出时返回的结果码。
         若EmbeddedUIExtensionAbility通过调用terminateSelfWithResult退出，结果码为EmbeddedUIExtensionAbility设置的值。
         若EmbeddedUIExtensionAbility通过调用terminateSelf退出，结果码为默认值"0"。
         - want：被拉起EmbeddedUIExtensionAbility退出时返回的数据。
 * @since 20
 */
void OH_ArkUI_EmbeddedComponentOption_SetOnTerminated(
    ArkUI_EmbeddedComponentOption* option, void (*callback)(int32_t code, AbilityBase_Want* want));

#ifdef __cplusplus
}
#endif

#endif // ARKUI_EMBEDDED_COMPONENT_H
/** @} */

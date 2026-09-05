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
 * @brief 定义TextArea相关的枚举类型。TextArea组件用于接收多行文本输入，枚举值用于指定不同的输入类型，会影响输入内容的验证规则，例如支持基本输入、纯数字、电话号码、邮箱地址、验证码等模式。
 *        开发者可根据表单类型选择合适的枚举值，系统将自动提供对应的内容验证，从而优化用户输入体验并确保数据格式的正确性。
 *
 * @since 12
 */

/**
 * @file text_area.h
 *
 * @brief 定义TextArea相关的枚举类型。TextArea组件用于接收多行文本输入，枚举值用于指定不同的输入类型，会影响输入内容的验证规则，例如支持基本输入、纯数字、电话号码、邮箱地址、验证码等模式。
 *        开发者可根据表单类型选择合适的枚举值，系统将自动提供对应的内容验证，从而优化用户输入体验并确保数据格式的正确性。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_AREA_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_AREA_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义多行文本输入法类型枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 基本输入模式。 */
    ARKUI_TEXTAREA_TYPE_NORMAL = 0,
    /** 纯数字模式。 */
    ARKUI_TEXTAREA_TYPE_NUMBER = 2,
    /** 电话号码输入模式。 */
    ARKUI_TEXTAREA_TYPE_PHONE_NUMBER = 3,
    /** 邮箱地址输入模式。 */
    ARKUI_TEXTAREA_TYPE_EMAIL = 5,
    /**
     * 验证码输入模式。
     * @since 20
     */
    ARKUI_TEXTAREA_TYPE_ONE_TIME_CODE = 14
} ArkUI_TextAreaType;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_AREA_H
/** @} */

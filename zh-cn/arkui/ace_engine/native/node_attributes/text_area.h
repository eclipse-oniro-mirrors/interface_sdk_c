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
 * @brief Defines a set of TextArea enum and interface.
 *
 * @since 12
 */

/**
 * @file text_area.h
 *
 * @brief Defines a set of TextArea enum and interface.
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
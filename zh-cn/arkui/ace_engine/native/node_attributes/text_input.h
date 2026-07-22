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
 * @brief Defines a set of TextInput enum and interface.
 *
 * @since 12
 */

/**
 * @file text_input.h
 *
 * @brief Defines a set of TextInput enum and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_INPUT_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_INPUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义单行文本输入法类型枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 基本输入模式。 */
    ARKUI_TEXTINPUT_TYPE_NORMAL = 0,
    /** 纯数字模式。 */
    ARKUI_TEXTINPUT_TYPE_NUMBER = 2,
    /** 电话号码输入模式。 */
    ARKUI_TEXTINPUT_TYPE_PHONE_NUMBER = 3,
    /** 邮箱地址输入模式。 */
    ARKUI_TEXTINPUT_TYPE_EMAIL = 5,
    /** 密码输入模式。 */
    ARKUI_TEXTINPUT_TYPE_PASSWORD = 7,
    /** 纯数字密码输入模式。 */
    ARKUI_TEXTINPUT_TYPE_NUMBER_PASSWORD = 8,
    /** 锁屏应用密码输入模式。 */
    ARKUI_TEXTINPUT_TYPE_SCREEN_LOCK_PASSWORD = 9,
    /** 用户名输入模式。 */
    ARKUI_TEXTINPUT_TYPE_USER_NAME = 10,
    /** 新密码输入模式。 */
    ARKUI_TEXTINPUT_TYPE_NEW_PASSWORD = 11,
    /** 带小数点的数字输入模式。 */
    ARKUI_TEXTINPUT_TYPE_NUMBER_DECIMAL = 12,
    /**
     * 验证码输入模式。
     * @since 20
     */
    ARKUI_TEXTINPUT_TYPE_ONE_TIME_CODE = 14
} ArkUI_TextInputType;
/**
 * @brief 定义清除按钮样式枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 清除按钮常显样式。*/
    ARKUI_CANCELBUTTON_STYLE_CONSTANT = 0,
    /** 清除按钮常隐样式。*/
    ARKUI_CANCELBUTTON_STYLE_INVISIBLE,
    /** 清除按钮输入样式。*/
    ARKUI_CANCELBUTTON_STYLE_INPUT
} ArkUI_CancelButtonStyle;
/**
 * @brief 定义自动填充类型。
 *
 * @since 12
 */
typedef enum {
    /** 【用户名】在已启用密码保险箱的情况下，支持用户名的自动保存和自动填充。 */
    ARKUI_TEXTINPUT_CONTENT_TYPE_USER_NAME = 0,
    /** 【密码】在已启用密码保险箱的情况下，支持密码的自动保存和自动填充。 */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PASSWORD,
    /** 【新密码】在已启用密码保险箱的情况下，支持自动生成新密码。 */
    ARKUI_TEXTINPUT_CONTENT_TYPE_NEW_PASSWORD,
    /** 【详细地址】在已启用情景化自动填充的情况下，支持详细地址的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_FULL_STREET_ADDRESS,
    /** 【门牌号】在已启用情景化自动填充的情况下，支持门牌号的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_HOUSE_NUMBER,
    /** 【区/县】在已启用情景化自动填充的情况下，支持区/县的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_DISTRICT_ADDRESS,
    /** 【市】在已启用情景化自动填充的情况下，支持市的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_CITY_ADDRESS,
    /** 【省】在已启用情景化自动填充的情况下，支持省的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_PROVINCE_ADDRESS,
    /** 【国家】在已启用情景化自动填充的情况下，支持国家的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_COUNTRY_ADDRESS,
    /** 【姓名】在已启用情景化自动填充的情况下，支持姓名的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_PERSON_FULL_NAME,
    /** 【姓氏】在已启用情景化自动填充的情况下，支持姓氏的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_PERSON_LAST_NAME,
    /** 【名字】在已启用情景化自动填充的情况下，支持名字的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_PERSON_FIRST_NAME,
    /** 【手机号】在已启用情景化自动填充的情况下，支持手机号的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_PHONE_NUMBER,
    /** 【国家代码】在已启用情景化自动填充的情况下，支持国家代码的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_PHONE_COUNTRY_CODE,
    /** 【包含国家代码的手机号】在已启用情景化自动填充的情况下，支持包含国家代码的手机号的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_FULL_PHONE_NUMBER,
    /** 【邮箱地址】在已启用情景化自动填充的情况下，支持邮箱地址的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_EMAIL_ADDRESS,
    /** 【银行卡号】在已启用情景化自动填充的情况下，支持银行卡号的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_BANK_CARD_NUMBER,
    /** 【身份证号】在已启用情景化自动填充的情况下，支持身份证号的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_ID_CARD_NUMBER,
    /** 【昵称】在已启用情景化自动填充的情况下，支持昵称的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_NICKNAME,
    /** 【无街道地址】在已启用情景化自动填充的情况下，支持无街道地址的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_DETAIL_INFO_WITHOUT_STREET,
    /** 【标准地址】在已启用情景化自动填充的情况下，支持标准地址的自动保存和自动填充。*/
    ARKUI_TEXTINPUT_CONTENT_TYPE_FORMAT_ADDRESS,
    /**
     * 【护照号】在已启用情景化自动填充的情况下，支持护照号的自动保存和自动填充。
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PASSPORT_NUMBER,
    /**
     * 【护照有效期】在已启用情景化自动填充的情况下，支持护照有效期的自动保存和自动填充。
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_VALIDITY,
    /**
     * 【护照签发地】在已启用情景化自动填充的情况下，支持护照签发地的自动保存和自动填充。
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ISSUE_AT,
    /**
     * 【发票抬头名称】在已启用情景化自动填充的情况下，支持发票抬头名称的自动保存和自动填充。
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ORGANIZATION,
    /**
     * 【税号】在已启用情景化自动填充的情况下，支持税号的自动保存和自动填充。
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_TAX_ID,
    /**
     * 【所在地区】在已启用情景化自动填充的情况下，支持所在地区的自动保存和自动填充。
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ADDRESS_CITY_AND_STATE,
    /**
     * 【航班号】暂不支持自动保存和自动填充。
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_FLIGHT_NUMBER,
    /**
     * 【驾驶证号】暂不支持自动保存和自动填充。
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_LICENSE_NUMBER,
    /**
     * 【驾驶证档案编号】暂不支持自动保存和自动填充。
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_LICENSE_FILE_NUMBER,
    /**
     * 【车牌号】在已启用情景化自动填充的情况下，支持车牌号的自动保存和自动填充。
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_LICENSE_PLATE,
    /**
     * 【行驶证发动机号】暂不支持自动保存和自动填充。
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ENGINE_NUMBER,
    /**
     * 【车牌识别号】暂不支持自动保存和自动填充。
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_LICENSE_CHASSIS_NUMBER
} ArkUI_TextInputContentType;
/**
 * @brief 定义输入框风格。
 *
 * @since 12
 */
typedef enum {
    /** 默认风格，光标宽1.5vp，光标高度与文本选中底板高度和字体大小相关。*/
    ARKUI_TEXTINPUT_STYLE_DEFAULT = 0,
    /** 内联输入风格。文本选中底板高度与输入框高度相同。 */
    ARKUI_TEXTINPUT_STYLE_INLINE
} ArkUI_TextInputStyle;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_INPUT_H
/** @} */
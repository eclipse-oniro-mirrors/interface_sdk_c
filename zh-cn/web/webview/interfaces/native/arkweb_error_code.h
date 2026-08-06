/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup Web
 * @{
 *
 * @brief Provides APIs for the ArkWeb errors.
 * @since 12
 */
/**
 * @file arkweb_error_code.h
 *
 * @brief 声明ArkWeb NDK接口异常错误码。
 *
 * @kit ArkWeb
 * @library libohweb.so
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
#ifndef ARKWEB_ERROR_CODE_H
#define ARKWEB_ERROR_CODE_H

/**
 * @brief 定义ArkWeb NDK接口异常错误码。
 *
 * @since 12
 */
typedef enum ArkWeb_ErrorCode {
/**
 * 成功。
 */
ARKWEB_SUCCESS = 0,

/**
 * 初始化失败。请检查系统环境，确保依赖库已安装，重试初始化。
 */
ARKWEB_INIT_ERROR = 17100001,

/**
 * 未知错误，请收集日志反馈。
 */
ARKWEB_ERROR_UNKNOWN = 17100100,

/**
 * 参数无效。请检查传入参数的格式、范围和类型是否符合接口要求。
 */
ARKWEB_INVALID_PARAM = 17100101,

/**
 * 注册scheme的配置失败，应该在创建ArkWeb之前注册。
 */
ARKWEB_SCHEME_REGISTER_FAILED = 17100102,

/**
 * 无效的URL，请检查URL格式或协议支持。
 */
ARKWEB_INVALID_URL = 17100103,

/**
 * 无效的cookie值，请检查cookie格式与有效性。
 */
ARKWEB_INVALID_COOKIE_VALUE = 17100104,

/*
 * @brief Failed to open the library.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 15
 */
ARKWEB_LIBRARY_OPEN_FAILURE = 17100105,

/*
 * @brief The required symbol was not found in the library.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 15
 */
ARKWEB_LIBRARY_SYMBOL_NOT_FOUND = 17100106,

/**
 * @brief CookieManager未初始化。请先调用初始化接口完成CookieManager的初始化。
 *
 * @since 20
 */
ARKWEB_COOKIE_MANAGER_NOT_INITIALIZED = 17100107,

/**
 * @brief CookieManager初始化失败，请检查系统能力与权限配置。
 *
 * @since 20
 */
ARKWEB_COOKIE_MANAGER_INITIALIZE_FAILED = 17100108,

/**
 * @brief 保存cookie失败。请检查存储空间是否充足、是否有写入权限，以及cookie值是否符合规范。
 *
 * @since 20
 */
ARKWEB_COOKIE_SAVE_FAILED = 17100109
} ArkWeb_ErrorCode;

/**
 * @brief 定义无白屏加载的异常错误码。
 *
 * @since 20
 */
typedef enum ArkWeb_BlanklessErrorCode {
/**
 * 成功。
 */
ARKWEB_BLANKLESS_SUCCESS = 0,

/**
 *未知错误，内部状态错误等。
 */
ARKWEB_BLANKLESS_ERR_UNKNOWN = -1,

/**
 * 参数不合法。
 */
ARKWEB_BLANKLESS_ERR_INVALID_ARGS = -2,

/**
 * WebViewController未绑定组件。
 */
ARKWEB_BLANKLESS_ERR_CONTROLLER_NOT_INITED = -3,

/**
 * 未匹配到key值，对于OH_NativeArkWeb_SetBlanklessLoadingWithKey需与OH_NativeArkWeb_GetBlanklessInfoWithKey配套使用并且key值一致，否则返回该错误码。
 */
ARKWEB_BLANKLESS_ERR_KEY_NOT_MATCH = -4,

/**
 * 当相似度较低时，系统会判定为跳变太大，OH_NativeArkWeb_SetBlanklessLoadingWithKey接口启用插帧不成功。
 */
ARKWEB_BLANKLESS_ERR_SIGNIFICANT_CHANGE = -5,

/**
 * 该设备不适用于此功能。
 */
ARKWEB_BLANKLESS_ERR_DEVICE_NOT_SUPPORT = 801
} ArkWeb_BlanklessErrorCode;

#endif // ARKWEB_ERROR_CODE_H
/** @} */
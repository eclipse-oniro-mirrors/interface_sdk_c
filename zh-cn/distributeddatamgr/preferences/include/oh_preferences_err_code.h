/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup Preferences
 * @{
 *
 * @brief 用户首选项为应用提供Key-Value键值型的数据处理能力，支持应用持久化轻量级数据，并对其修改和查询。
 * 数据存储采用键值对形式，键为字符串类型，值可为数字、字符串、布尔类型、数组、Uint8Array、object或bigint。
 *
 * @since 13
 */

/**
 * @file oh_preferences_err_code.h
 *
 * @brief 声明首选项模块统一使用的错误码信息。
 * 
 * @kit ArkData
 * @library libohpreferences.so
 * @syscap SystemCapability.DistributedDataManager.Preferences.Core
 *
 * @since 13
 */


#ifndef OH_PREFERENCES_ERR_CODE_H
#define OH_PREFERENCES_ERR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 错误码信息。
 * 
 * @since 13
 */
typedef enum OH_Preferences_ErrCode {
    /**
     * 操作执行成功。
     */
    PREFERENCES_OK = 0,
    /**
     * 参数不合法。
     */
    PREFERENCES_ERROR_INVALID_PARAM = 401,
    /**
     * 系统能力不支持。
     */
    PREFERENCES_ERROR_NOT_SUPPORTED = 801,
    /**
     * 基准错误码。
     */
    PREFERENCES_ERROR_BASE = 15500000,
    /**
     * 删除文件失败。
     */
    PREFERENCES_ERROR_DELETE_FILE = 15500010,
    /**
     * 存储异常。
     */
    PREFERENCES_ERROR_STORAGE = 15500011,
    /**
     * 申请内存失败。
     */
    PREFERENCES_ERROR_MALLOC = 15500012,
    /**
     * Key不存在。
     */
    PREFERENCES_ERROR_KEY_NOT_FOUND = 15500013,
    /**
     * 获取数据变更订阅服务失败。
     */
    PREFERENCES_ERROR_GET_DATAOBSMGRCLIENT = 15500019,
} OH_Preferences_ErrCode;

#ifdef __cplusplus
};
#endif
/** @} */
#endif // OH_PREFERENCES_ERR_CODE_H

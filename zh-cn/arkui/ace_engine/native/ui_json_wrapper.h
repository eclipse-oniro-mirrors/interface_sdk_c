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
 * @brief Defines the shared immutable JSON data object used by the UI perception and control APIs
 * for in-app intelligent agents and UI automation. JSON is adopted as the mainstream structured
 * format for cross-language and cross-process consumption, as an alternative to a large set of
 * field accessors.
 *
 * @since 26.2.0
 */

/**
 * @file ui_json_wrapper.h
 *
 * @brief Declares the shared JSON data object for the UI perception and control APIs.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @include <arkui/ui_json_wrapper.h>
 * @library libace_ndk.z.so
 * @kit ArkUI
 * @since 26.2.0
 */

#ifndef ARKUI_NATIVE_UI_JSON_WRAPPER_H
#define ARKUI_NATIVE_UI_JSON_WRAPPER_H

#include <stdint.h>

#include "error_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义一个不透明、不可变的JSON数据对象。
 *
 * 对象拥有一个UTF-8 JSON字符串以及该字符串的模式版本
 * JSON，它既用于框架传递的数据（UI感知），也用于
 * 应用程序（UI控件）提交的命令。
 *
 * @since 26.2.0
 */
typedef struct OH_ArkUI_NativeModule_UIJsonWrapper OH_ArkUI_NativeModule_UIJsonWrapper;

/**
 * @brief 从调用方提供的JSON字符串创建JSON数据对象。
 *
 * 将提供的字符串复制到对象中。调用方拥有创建的对象，必须
 * 当不再需要它时，使用{@链接OH_ArkUI_NativeModule_UIJsonWrapper_Destroy}释放它。
 *
 * 提供的字符串应包含schemaVersion字段。如果不存在，或指定的
 * 版本值超出支持的范围，它被视为1，如下所示：
 * { "schemaVersion": 1, ... }
 *
 * 注意：传递给此函数的数据字符串仍由调用方拥有。销毁JSON
 * 此接口返回的包装器对象不会释放数据指向的内存
 * 调用者的代表。
 *
 * @param data 【in】指向JSON字符串的指针。它不能为空，并且必须对
 * 呼叫的持续时间。被调用方不保留。空字符串是有效的，对应
 * 的大小为0。
 * @param size [in]JSON字符串的字节长度，单位为字节，不包括终止null。
 * 字符，必须等于数据的实际长度。如果大小与实际不一致
 * 返回字符串长度{@link RKUI_ERROR_CODE_PARAM_INVALID}。
 * @param outOwned 【out】成功时接收创建的对象。调用方拥有返回的对象
 * 并且必须使用{@link OH_ArkUI_NativeModule_UIJsonWrapper_Destroy}来释放它。一定不是这样的
 * null，不需要初始化，失败时设置为null。
 * @return <ul>
 * 如果操作成功，则返回<li>{@link RKUI_ERROR_CODE_NO_ERROR}。</li>
 * 如果参数无效，则<li>{@link RKUI_ERROR_CODE_PARAM_INVALID}。</li>
 * </ul>
 * @release ui_json_wrapper/OH_ArkUI_NativeModule_UIJsonWrapperDestroy {outOwned}
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIJsonWrapperCreate(const char *data, uint32_t size,
    OH_ArkUI_NativeModule_UIJsonWrapper **outOwned);

/**
 * @brief 获取对象持有的JSON字符串。
 *
 * 返回的字符串是只读的，并且以null终止。它指向JSON拥有的内存
 * 对象，并保持有效，直到对象被销毁。调用者不得修改或释放
 * 返回的字符串。
 *
 * @param json [in]JSON数据对象。不能为空。
 * @return 借用的JSON字符串，如果json为null，则为null。
 * @since 26.2.0
 */
const char *OH_ArkUI_NativeModule_UIJsonWrapperGetData(const OH_ArkUI_NativeModule_UIJsonWrapper *json);

/**
 * @brief 获取JSON字符串的字节长度。
 *
 * 返回的长度不包括终止空字符。对于一个空的JSON字符串，零是
 * 返回。
 *
 * @param json [in]JSON数据对象。不能为空。
 * @return <ul>
 * <li>JSON字符串的字节长度，不包括终止空字符。</li>
 * <li>对于空的JSON字符串返回0。</li>
 * </ul>
 * @since 26.2.0
 */
uint32_t OH_ArkUI_NativeModule_UIJsonWrapperGetSize(const OH_ArkUI_NativeModule_UIJsonWrapper *json);

/**
 * @brief 销毁JSON数据对象并释放其资源。
 *
 * 传递null没有任何效果。返回的任何指针
 * {@链接OH_ArkUI_NativeModule_UIJsonWrapper_GetData}在此次调用后失效。
 *
 * 注意：仅在您显式持有其所有权的JSON包装器对象上调用此函数，对于
 * 例如，使用{@link OH_ArkUI_NativeModule_UIJsonWrapper_Create}创建的包装器，或者包装器
 * 你通过所有权转移函数明确地获得了所有权。不使用
 * 该函数用于释放系统构造并传递出去的JSON包装器对象。
 * 例如，通过传递的对象
 * {@链接OH_ArkUI_NativeModule_UIInfoCollectionInteractionJsonCallback}。
 *
 * @param json 【in】要销毁的JSON数据对象。
 * @since 26.2.0
 */
void OH_ArkUI_NativeModule_UIJsonWrapperDestroy(OH_ArkUI_NativeModule_UIJsonWrapper *json);

/**
 * @brief JSON输出格式枚举类型。
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief 生成规范的JSON，没有不必要的空白。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_JSON_COMPACT = 0,
    /**
     * @brief 生成带有双空格缩进和换行符的JSON。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_JSON_PRETTY = 1
} OH_ArkUI_NativeModule_UIJsonFormat;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_UI_JSON_WRAPPER_H
/** @} */
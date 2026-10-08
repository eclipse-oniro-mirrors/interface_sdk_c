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
 * @brief 定义UI感知与控制接口共用的不可变JSON数据对象，供应用内智能体和UI自动化使用。
 * JSON是一种主流的结构化数据格式，可供不同编程语言和进程使用，避免为各个字段提供大量访问接口。
 *
 * @since 26.2.0
 */

/**
 * @file ui_json_wrapper.h
 *
 * @brief 声明UI感知与控制接口共用的JSON数据对象。
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
 * @brief 定义内部结构不对外公开的不可变JSON数据对象。
 *
 * 该对象保存一个JSON字符串，既用于承载框架传递的数据（UI感知），也用于承载应用提交的命令（UI控制）。
 *
 * @since 26.2.0
 */
typedef struct OH_ArkUI_NativeModule_UIJsonWrapper OH_ArkUI_NativeModule_UIJsonWrapper;

/**
 * @brief 根据调用方提供的JSON字符串创建JSON数据对象。
 *
 * 传入的字符串会被复制到对象中。调用方拥有所创建对象的所有权，
 * 并且必须在不再使用时调用{@link OH_ArkUI_NativeModule_UIJsonWrapperDestroy}释放该对象。
 *
 * 传入的字符串应包含schemaVersion字段。如果缺少该字段，或其值超出支持的版本范围，则按版本1处理，如下所示：
 * { "schemaVersion": 1, ... }
 *
 * 注意：传入的data字符串仍归调用方所有。销毁本接口返回的JSON封装对象，
 * 不会代替调用方释放data所指向的内存。
 *
 * @param data [in] 指向JSON字符串的指针。不能为NULL，且必须在整个调用期间保持有效。
 *     被调用方不会保留该指针。允许传入空字符串，此时size为0。
 * @param size [in] JSON字符串的长度，单位为字节，不包含末尾的空字符。
 *     必须与data字符串的实际长度一致，否则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param outOwned [out] 用于接收创建成功的对象的输出参数。调用方拥有返回对象的所有权，
 *     必须调用{@link OH_ArkUI_NativeModule_UIJsonWrapperDestroy}释放该对象。
 *     outOwned不能为NULL，其指向的对象指针无需初始化；创建失败时，该对象指针被设置为NULL。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数无效。</li>
 *     </ul>
 * @release ui_json_wrapper/OH_ArkUI_NativeModule_UIJsonWrapperDestroy {outOwned}
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIJsonWrapperCreate(const char *data, uint32_t size,
    OH_ArkUI_NativeModule_UIJsonWrapper **outOwned);

/**
 * @brief 获取对象保存的JSON字符串。
 *
 * 返回的字符串为只读字符串，以空字符结尾。字符串所在的内存归JSON对象所有，在该对象销毁前一直有效。
 * 调用方不得修改或释放返回的字符串。
 *
 * @param json [in] JSON数据对象，不能为NULL。
 * @return 返回借用的JSON字符串指针，调用方不拥有其所有权；如果json为NULL，则返回NULL。
 * @since 26.2.0
 */
const char *OH_ArkUI_NativeModule_UIJsonWrapperGetData(const OH_ArkUI_NativeModule_UIJsonWrapper *json);

/**
 * @brief 获取JSON字符串的字节长度。
 *
 * 返回的长度不包含末尾的空字符。对于空JSON字符串，返回0。
 *
 * @param json [in] JSON数据对象，不能为NULL。
 * @return <ul>
 *     <li>JSON字符串的字节长度，不包含末尾的空字符。</li>
 *     <li>对于空JSON字符串，返回0。</li>
 *     </ul>
 * @since 26.2.0
 */
uint32_t OH_ArkUI_NativeModule_UIJsonWrapperGetSize(const OH_ArkUI_NativeModule_UIJsonWrapper *json);

/**
 * @brief 销毁JSON数据对象并释放其资源。
 *
 * 传入NULL时不执行任何操作。调用本函数后，
 * {@link OH_ArkUI_NativeModule_UIJsonWrapperGetData}返回的所有指针均失效。
 *
 * 注意：仅可对调用方明确拥有所有权的JSON封装对象调用本函数，
 * 例如通过{@link OH_ArkUI_NativeModule_UIJsonWrapperCreate}创建的对象，
 * 或通过所有权转移函数明确取得所有权的对象。
 * 不得使用本函数释放由系统构造并传出的JSON封装对象，
 * 例如通过{@link OH_ArkUI_NativeModule_UIInfoCollectionInteractionJsonCallback}传入的对象。
 *
 * @param json [in] 要销毁的JSON数据对象。
 * @since 26.2.0
 */
void OH_ArkUI_NativeModule_UIJsonWrapperDestroy(OH_ArkUI_NativeModule_UIJsonWrapper *json);

/**
 * @brief 定义JSON输出格式的枚举类型。
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief 输出不含多余空白字符的规范JSON。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_JSON_COMPACT = 0,
    /**
     * @brief 输出带有两个空格缩进和换行符的JSON。
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
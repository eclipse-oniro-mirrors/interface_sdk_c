/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @since 12
 */

/**
 * @file native_interface.h
 *
 * @brief Provides a unified entry for the native module APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_INTERFACE_H
#define ARKUI_NATIVE_INTERFACE_H

#include <stdint.h>

#include "error_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the native API types.
 *
 * @since 12
 */
typedef enum {
    /** API related to UI components. For details, see the struct definition in <arkui/native_node.h>. */
    ARKUI_NATIVE_NODE,
    /** API related to dialog boxes. For details, see the struct definition in <arkui/native_dialog.h>. */
    ARKUI_NATIVE_DIALOG,
    /** API related to gestures. For details, see the struct definition in <arkui/native_gesture.h>. */
    ARKUI_NATIVE_GESTURE,
    /** API related to animations. For details, see the struct definition in <arkui/native_animate.h>.*/
    ARKUI_NATIVE_ANIMATE,
    /**
     * 多线程UI组件相关接口类型，详见{@link native_node.h}中的{@link 结构体}类型定义。
     * @since 22
     */
    ARKUI_MULTI_THREAD_NATIVE_NODE
} ArkUI_NativeAPIVariantKind;

/**
 * @brief ArkUI C API的运行时检查类型枚举。
 *
 * 每种检查类型对应一种ArkUI C API的不当使用场景，用于在运行时检测开发者
 * 对C API的误用行为（如跨线程调用、访问已销毁对象等）。
 * 可通过{@link OH_ArkUI_NativeModule_SetRuntimeCheckMode}为每种检查类型
 * 独立配置运行时检查模式，检查失败时的行为由所配置的运行时检查模式决定，模式取值见{@link OH_ArkUI_NativeModule_RuntimeCheckMode}。
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief UI线程检查类型：部分ArkUI C API要求必须在UI线程调用，
     * 此类型用于检测这些API是否被非UI线程调用。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_TYPE_UI_THREAD = 0,
    /**
     * @brief 节点销毁检查类型：检测传递给C API的ArkUI_NodeHandle是否已经被销毁。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_TYPE_NODE_DISPOSED = 1
} OH_ArkUI_NativeModule_RuntimeCheckType;

/**
 * @brief ArkUI C API运行时检查的模式枚举。
 *
 *  所有C API的运行时检查类型均使用本枚举中定义的相同模式集合（DISABLED、LOG、CRASH）设置检查失败时的行为，
 * 即每种检查类型都可以独立设置为以下三种模式之一。
 * 默认模式取决于应用程序的构建类型：
 * 以debug模式编译的应用（DevEco Studio中Debug构建，用于开发调试）
 * 默认为{@link OH_ARKUI_NATIVEMODULE_CHECK_MODE_CRASH}，
 * 以release模式编译的应用（DevEco Studio中Release构建，用于正式发布）
 * 默认为{@link OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED}。
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief  禁用指定的运行时检查。C API行为与引入该检查之前一致。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED = 0,
    /**
     * @brief 打印诊断日志（检查类型、API名称、原因、native堆栈）并继续C API调用。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG = 1,
    /**
     * @brief 打印诊断日志并立即终止应用程序。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_MODE_CRASH = 2
} OH_ArkUI_NativeModule_RuntimeCheckMode;
/**
 * @brief Obtains the native API set of a specified type.
 *
 * @param type Indicates the type of the native API set provided by ArkUI, for example, <b>ARKUI_NATIVE_NODE</b>
 * and <b>ARKUI_NATIVE_GESTURE</b>.
 * @param structName Indicates the name of a native struct defined in the corresponding header file, for example,
 * <b>ArkUI_NativeNodeAPI_1</b> in <arkui/native_node.h>.
 * @return Returns the pointer to the abstract native API, which can be used after being converted into a specific type.
 * @code {.cpp}
 * #include<arkui/native_interface.h>
 * #include<arkui/native_node.h>
 * #include<arkui/native_gesture.h>
 *
 * auto* anyNativeAPI = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1");
 * if (anyNativeAPI) {
 *     auto nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(anyNativeAPI);
 * }
 * auto anyGestureAPI = OH_ArkUI_QueryModuleInterface(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_1");
 * if (anyNativeAPI) {
 *     auto basicGestureApi = reinterpret_cast<ArkUI_NativeGestureAPI_1*>(anyGestureAPI);
 * }
 * @endcode
 *
 * @since 12
 */
void* OH_ArkUI_QueryModuleInterfaceByName(ArkUI_NativeAPIVariantKind type, const char* structName);

/**
 * @brief 获取最新的错误消息，该消息包含错误码、方法名称及错误原因。
 * 当其他接口返回错误码时，会保存对应的错误信息，
 * 通过此接口可获取当前存储的错误消息。
 * 此接口返回的信息可能随版本演进，仅用于输出以辅助分析和定位问题，
 * 不得用于逻辑判断。
 *
 * 返回的字符串为系统创建的全局字符串，可能被其他线程修改。调用方不能对其内容进行修改，如果有对齐编辑的需要，自行创建字符串拷贝内容。无需调用方进行内存释放。
 *
 * @return 返回最新的错误信息。
 * @since 26.0.0
 */
const char* OH_ArkUI_NativeModule_GetErrorMessage();

/**
 * @brief 设置ArkUI C API的进程级运行时检查模式。
 *
 * 本函数配置特定运行时检查类型在检测到误用时的行为。
 * 该设置为进程级，在针对同一检查类型的下一次成功调用之前持续有效。
 *
 * <b>线程要求：</b>本函数必须在UI线程上调用。
 * 从其他线程调用将立即终止应用程序，不会返回。
 * 线程检查在参数校验之前执行。
 *
 * <b>默认行为：</b>如果未针对某个检查类型调用本函数，
 * debug应用构建默认为{@link ARKUI_RUNTIME_CHECK_MODE_CRASH}，
 * release应用构建默认为{@link ARKUI_RUNTIME_CHECK_MODE_DISABLED}。
 *
 * @param checkType [入参] 指定要配置的运行时检查类型，
 *     取值为{@link OH_ArkUI_NativeModule_RuntimeCheckType}中的枚举值。
 * @param mode [入参] 指定运行时检查模式，取值为{@link OH_ArkUI_NativeModule_RuntimeCheckMode}中的枚举值。
 * @return 返回值：
 *     <ul><li>设置更新成功返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     </li><li>checkType或mode无效时返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。</li></ul>
 *  *     返回无效参数错误时，保留之前的设置。
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_SetRuntimeCheckMode(
    OH_ArkUI_NativeModule_RuntimeCheckType checkType, OH_ArkUI_NativeModule_RuntimeCheckMode mode);

/**
 * @brief Obtains the macro function corresponding to a struct pointer based on the struct type.
 *
 * @code {.cpp}
 * #include<arkui/native_interface.h>
 * #include<arkui/native_node.h>
 *
 * ArkUI_NativeNodeAPI_1* nativeNodeApi = nullptr;
 * OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nativeNodeApi);
 * @endcode
 *
 * @since 12
 */
#define OH_ArkUI_GetModuleInterface(nativeAPIVariantKind, structType, structPtr)                     \
    do {                                                                                             \
        void* anyNativeAPI = OH_ArkUI_QueryModuleInterfaceByName(nativeAPIVariantKind, #structType); \
        if (anyNativeAPI) {                                                                          \
            structPtr = (structType*)(anyNativeAPI);                                                 \
        }                                                                                            \
    } while (0)

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_INTERFACE_H
/** @} */
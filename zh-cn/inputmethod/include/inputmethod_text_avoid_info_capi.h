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
 * @addtogroup InputMethod
 * @{
 *
 * @brief InputMethod模块提供C语言接口来使用输入法。"使用输入法"面向应用侧调用。
 *     <br>
 *     <br>功能定位：该模块为应用侧开发者提供自绘输入框与输入法服务交互的完整C API，支持应用绑定/解绑输入法服务、向输入法发送请求
 * 和通知、接收输入法的回调通知、配置输入框属性、管理光标和避让信息等核心功能。
 *     <br>
 *     <br>使用场景：适用于使用NDK开发自绘输入框的应用，需要与系统输入法服务进行交互的场景。典型流程为：应用创建TextEditorProxy
 * （文本编辑器代理）和AttachOptions（绑定配置选项），通过Controller绑定输入法服务，绑定成功后通过InputMethodProxy（输入法代
 * 理）与输入法交互，使用完毕后通过Controller解绑。
 *     <br>
 *     <br>使用后效果：绑定输入法后，应用可接收输入法的文本插入、删除、光标移动等回调通知，也可主动向输入法发送光标更新、选区变
 * 更、私有命令等请求。解绑后，所有交互通道关闭，相关资源释放。
 *     <br>
 *     <br>生命周期管理：本模块遵循严格的创建/销毁配对原则和绑定/解绑配对原则：
 *     <br>
 *     <br>- 绑定/解绑配对：OH_InputMethodController_Attach必须与OH_InputMethodController_Detach配对调用，未解绑会导致输入法
 * 资源泄漏。
 *     <br>- 创建/销毁配对：所有Create函数创建的对象必须通过对应的Destroy函数销毁，否则会导致内存泄漏。
 *     <br>- 调用顺序：先创建依赖对象（TextEditorProxy、AttachOptions），再执行Attach绑定，绑定成功后使用InputMethodProxy交
 * 互，最后Detach解绑并销毁所有创建的对象。
 *     <br>
 *     <br>线程安全：本模块的API非线程安全，建议在主线程调用。TextEditorProxy的回调执行线程可通过
 * OH_TextEditorProxy_SetCallbackInMainThread配置。
 *
 *     <br>模块架构: 本模块由9个头文件组成，按职责分为四层：
 *     <br>
 *     <br>- 控制层：inputmethod_controller_capi.h —— 模块核心入口，提供绑定/解绑输入法服务的能力，是所有交互的起点和终点。
 *     <br>- 交互层：inputmethod_text_editor_proxy_capi.h和inputmethod_inputmethod_proxy_capi.h —— 双向交互通道。
 * TextEditorProxy是输入法→应用方向的回调注册通道，应用通过它接收输入法的文本插入、删除等通知；InputMethodProxy是应用→输入法方向
 * 的请求发送通道，应用通过它向输入法发送光标更新、选区变更等通知。
 *     <br>- 配置层：inputmethod_attach_options_capi.h、inputmethod_text_config_capi.h、inputmethod_cursor_info_capi.h、
 * inputmethod_text_avoid_info_capi.h —— 各类配置和信息的承载对象，分别管理绑定选项、输入框配置、光标位置信息、避让区域信息。
 *     <br>- 数据层：inputmethod_private_command_capi.h和inputmethod_types_capi.h —— 私有命令数据和公共类型定义（枚举、错误
 * 码等）。
 *     <br>
 *     <br>典型调用流程：
 *     <br>1. 通过inputmethod_text_editor_proxy_capi.h创建TextEditorProxy并注册回调。
 *     <br>2. 通过inputmethod_attach_options_capi.h创建AttachOptions配置绑定选项。
 *     <br>3. 通过inputmethod_controller_capi.h调用Attach绑定输入法，获取InputMethodProxy。
 *     <br>4. 通过inputmethod_inputmethod_proxy_capi.h使用InputMethodProxy与输入法交互。
 *     <br>5. 通过inputmethod_text_config_capi.h、inputmethod_cursor_info_capi.h等管理配置信息。
 *     <br>6. 通过inputmethod_controller_capi.h调用Detach解绑。
 *     <br>7. 销毁所有创建的对象。
 *
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 */

/**
 * @file inputmethod_text_avoid_info_capi.h
 *
 * @brief 输入框避让信息的头文件，提供TextAvoidInfo实例的创建、销毁与属性读写方法，用于在软键盘弹起时动态调整输入框的位置，避免遮
 * 挡输入内容。TextAvoidInfo描述键盘弹起时需要避让的区域（positionY和height），用于应用在TextConfig中告知输入法当前的避让区域信
 * 息。Create/Destroy必须配对。
 *     <br>
 *     <br>InputMethod_TextAvoidInfo描述了编辑框在屏幕上的位置和高度信息，输入法框架根据这些信息计算避让区域，使编辑框在键盘弹起
 * 时能够自动上移或调整布局，确保用户可见并可操作输入区域。该结构体作为InputMethod_TextConfig的子属性，通过
 * OH_TextConfig_GetTextAvoidInfo从TextConfig中获取，用于向输入法框架传递编辑框的避让参数。
 *
 * @include <inputmethod/inputmethod_text_avoid_info_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_TEXT_AVOID_INFO_CAPI_H
#define OHOS_INPUTMETHOD_TEXT_AVOID_INFO_CAPI_H
#include "inputmethod_types_capi.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief 输入框避让信息结构体，描述编辑框在物理屏幕上的位置和高度信息。输入法框架根据TextAvoidInfo中的positionY和height计算避让
 * 区域，使编辑框在软键盘弹起时能够自动上移或调整布局，确保输入区域不被键盘遮挡，保证用户可见并可操作输入内容。
 *     <br>
 *     <br>用途：作为编辑框避让键盘区域的参数载体，向输入法框架传递编辑框的垂直位置和高度信息。输入法框架根据positionY（编辑框顶
 * 部Y坐标，取值原则：大于等于0的有效屏幕Y坐标）和height（编辑框高度，
 * 取值原则：大于0的有效高度值）确定编辑框在屏幕上的完整垂直范围（positionY到positionY+height），并与键盘占据的屏幕区域进行比较，
 * 计算是否需要避让以及避让的偏移量。
 *     <br>
 *     <br>使用场景：在编辑框与输入法服务绑定后（通过OH_InputMethodController_Attach），编辑框客户端通过
 * InputMethod_TextConfig将TextAvoidInfo传递给输入法框架。输入法框架在键盘弹起时读取避让信息，判断编辑框是否处于键盘遮挡区域，并
 * 触发相应的避让调整。该结构体也可由输入法应用读取，用于了解编辑框的屏幕位置以优化键盘布局。
 *     <br>
 *     <br>相关函数：<br>
 * | 函数 | 说明 |
 * | --- | --- |
 * | [OH_TextAvoidInfo_Create](capi-inputmethod-text-avoid-info-capi-h.md#oh_textavoidinfo_create) | 创建
 * InputMethod_TextAvoidInfo实例 |
 * | [OH_TextAvoidInfo_Destroy](capi-inputmethod-text-avoid-info-capi-h.md#oh_textavoidinfo_destroy) | 销毁
 * InputMethod_TextAvoidInfo实例 |
 * | [OH_TextAvoidInfo_SetPositionY](capi-inputmethod-text-avoid-info-capi-h.
 * md#oh_textavoidinfo_setpositiony) | 设置Y坐标值 |
 * | [OH_TextAvoidInfo_SetHeight](capi-inputmethod-text-avoid-info-capi-h.md#oh_textavoidinfo_setheight) | 设置高度值 |
 * | [OH_TextAvoidInfo_GetPositionY](capi-inputmethod-text-avoid-info-capi-h.
 * md#oh_textavoidinfo_getpositiony) | 获取Y坐标值 |
 * | [OH_TextAvoidInfo_GetHeight](capi-inputmethod-text-avoid-info-capi-h.md#oh_textavoidinfo_getheight) | 获取高度值 |
 * | [OH_TextConfig_GetTextAvoidInfo](capi-inputmethod-text-config-capi-h.md#
 * oh_textconfig_gettextavoidinfo) | 从TextConfig中获取TextAvoidInfo |
 *     <br>
 *     <br>相关结构体：<br>
 * | 结构体 | 说明 |
 * | --- | --- |
 * | [InputMethod_TextConfig](capi-inputmethod-inputmethod-textconfig.md) | 文本输入框配置结构体，TextAvoidInfo作
 * 为其子属性被包含 |
 *
 * @since 12
 */
typedef struct InputMethod_TextAvoidInfo InputMethod_TextAvoidInfo;

/**
 * @brief 创建一个新的{@link InputMethod_TextAvoidInfo}实例。该函数根据指定的Y坐标和高度创建一个避让信息对象，用于描述编辑框在
 * 物理屏幕上的位置和尺寸。
 *     <br>
 *     <br>使用场景：当编辑框需要向输入法框架传递避让参数时，首先调用此函数创建TextAvoidInfo实例，设置编辑框的Y坐标和高度，然后通
 * 过InputMethod_TextConfig将该信息传递给输入法框架。输入法框架根据避让信息计算键盘弹起后的编辑框调整区域。
 *     <br>
 *     <br>使用后效果：成功调用后返回一个新创建的InputMethod_TextAvoidInfo实例指针，该实例包含指定的positionY和height值。调用
 * 方需负责该实例的生命周期管理，在使用完毕后必须调用OH_TextAvoidInfo_Destroy销毁实例以释放内存。
 *
 * @param positionY 表示输入框位置的Y坐标值，单位px。Y坐标值即输入框顶点与物理屏幕上侧距离的绝对值，单位px。取值范围≥0，建议使用
 * 物理屏幕的实际坐标值。若传入负值，创建仍会成功，但该值在实际避让计算中无意义。
 * @param height 表示输入框高度，单位px。取值范围≥0，建议使用编辑框的实际像素高度。若传入负值，创建仍会成功，但该值在实际避让计算
 * 中无意义。
 * @return 如果创建成功，返回一个指向新创建的{@link InputMethod_TextAvoidInfo}实例的指针。调用方必须负责该实例的生命周期管理，
 * 使用完毕后调用
 *     {@link OH_TextAvoidInfo_Destroy}销毁实例以释放内存。
 *     <br>如果创建失败，返回NULL。可能的失败原因：内存分配不足（应用地址空间满）。对NULL指针的后续操作（如Set/Get函数）将返回
 * IME_ERR_NULL_POINTER。
 * @since 12
 */
InputMethod_TextAvoidInfo *OH_TextAvoidInfo_Create(double positionY, double height);
/**
 * @brief 销毁一个{@link InputMethod_TextAvoidInfo}实例，释放其占用的内存资源。
 *     <br>
 *     <br>使用场景：当TextAvoidInfo实例不再使用时，调用此函数销毁实例。必须在Create函数成功返回后、且实例不再被任何其他对象引用
 * 时调用。
 *     <br>
 *     <br>生命周期管理：OH_TextAvoidInfo_Create和OH_TextAvoidInfo_Destroy必须配对使用，每个Create创建的实例必须有对应的
 * Destroy调用，否则会导致内存泄漏。调用Destroy后，原指针变为无效指针，不应再被使用。
 *     <br>
 *     <br>前置条件：info参数应为OH_TextAvoidInfo_Create成功返回的非NULL指针。
 *     <br>
 *     <br>使用后效果：info指向的内存被释放，info指针变为无效指针。对已销毁指针的任何后续访问均为未定义行为。
 *
 * @param info 表示指向即将被销毁的{@link InputMethod_TextAvoidInfo}实例的指针。若传入NULL，函数不执行任何操作，安全返回。建议
 * 销毁后将指针置为NULL以避免误用悬空指针。
 * @since 12
 */
void OH_TextAvoidInfo_Destroy(InputMethod_TextAvoidInfo *info);
/**
 * @brief 设置{@link InputMethod_TextAvoidInfo}中的Y坐标值。Y坐标值表示输入框顶点与物理屏幕上侧距离的绝对值。
 *     <br>
 *     <br>使用场景：当编辑框位置发生变化时（如窗口移动、布局调整），需要更新避让信息中的Y坐标值，使输入法框架能够根据最新位置重新
 * 计算避让区域。
 *     <br>
 *     <br>前置条件：info参数必须为OH_TextAvoidInfo_Create成功返回的非NULL指针。
 *
 * @param info 指向即将被设置值的{@link InputMethod_TextAvoidInfo}实例的指针。不允许传入NULL指针，否则返回
 * IME_ERR_NULL_POINTER。
 * @param positionY Y坐标值，即输入框顶点与物理屏幕上侧距离的绝对值，单位px。取值范围≥0，建议使用物理屏幕的实际坐标值。传入负值不
 * 会报错，但在实际避让计算中无意义。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，info参数为NULL。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_SetPositionY(InputMethod_TextAvoidInfo *info, double positionY);
/**
 * @brief 设置{@link InputMethod_TextAvoidInfo}中的高度值。高度值表示编辑框在屏幕上占据的垂直像素尺寸。
 *     <br>
 *     <br>使用场景：当编辑框高度发生变化时（如布局调整、窗口缩放），需要更新避让信息中的高度值，使输入法框架能够根据最新高度重新
 * 计算避让区域。避让区域计算依赖于positionY和height的组合，确保编辑框在键盘弹起时不被遮挡。
 *     <br>
 *     <br>前置条件：info参数必须为OH_TextAvoidInfo_Create成功返回的非NULL指针。
 *
 * @param info 指向即将被设置值的{@link InputMethod_TextAvoidInfo}实例的指针。不允许传入NULL指针，否则返回
 * IME_ERR_NULL_POINTER。
 * @param height 高度值，单位px。取值范围≥0，建议使用编辑框的实际像素高度。传入负值不会报错，但在实际避让计算中无意义。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，info参数为NULL。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_SetHeight(InputMethod_TextAvoidInfo *info, double height);
/**
 * @brief 从{@link InputMethod_TextAvoidInfo}获取Y坐标值。Y坐标值即输入框顶点与物理屏幕上侧距离的绝对值。
 *     <br>
 *     <br>使用场景：输入法应用在处理避让逻辑时，需要获取编辑框的Y坐标值，以确定编辑框在屏幕上的垂直位置，从而判断是否需要调整编辑
 * 框位置或布局。
 *     <br>
 *     <br>前置条件：info参数必须为OH_TextAvoidInfo_Create成功返回的非NULL指针；positionY输出参数必须为非NULL的double类型指
 * 针，且由调用方分配内存。
 *
 * @param info 指向即将被获取值的{@link InputMethod_TextAvoidInfo}实例的指针。不允许传入NULL指针，否则返回
 * IME_ERR_NULL_POINTER。
 * @param positionY 输出参数，用于接收Y坐标值，即输入框顶点与物理屏幕上侧距离的绝对值，单位px。此参数为输出指针，调用方需分配
 * double类型变量的内存并将其地址传入。不允许传入NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功，positionY指针指向的内存已被写入Y坐标值。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，info或positionY参数为NULL。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_GetPositionY(InputMethod_TextAvoidInfo *info, double *positionY);
/**
 * @brief 从{@link InputMethod_TextAvoidInfo}获取高度值。高度值表示编辑框在屏幕上占据的垂直像素尺寸。
 *     <br>
 *     <br>使用场景：输入法应用在处理避让逻辑时，需要获取编辑框的高度值，结合Y坐标值确定编辑框在屏幕上的完整垂直范围（positionY到
 * positionY+height），从而判断编辑框是否会被键盘遮挡。
 *     <br>
 *     <br>前置条件：info参数必须为OH_TextAvoidInfo_Create成功返回的非NULL指针；height输出参数必须为非NULL的double类型指针，且
 * 由调用方分配内存。
 *
 * @param info 指向即将被获取值的{@link InputMethod_TextAvoidInfo}实例的指针。不允许传入NULL指针，否则返回
 * IME_ERR_NULL_POINTER。
 * @param height 输出参数，用于接收输入框高度，单位px。此参数为输出指针，调用方需分配double类型变量的内存并将其地址传入。不允许传
 * 入NULL指针，否则返回IME_ERR_NULL_POINTER。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功，height指针指向的内存已被写入高度值。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针，info或height参数为NULL。
 *     <br>具体错误码可以参考 {@link InputMethod_ErrorCode}。
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_GetHeight(InputMethod_TextAvoidInfo *info, double *height);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_TEXT_AVOID_INFO_CAP_H
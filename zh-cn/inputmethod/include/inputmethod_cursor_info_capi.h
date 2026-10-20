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
 * @file inputmethod_cursor_info_capi.h
 *
 * @brief 光标信息的头文件，提供CursorInfo实例的创建、销毁与属性读写方法。CursorInfo描述光标在物理屏幕上的位置和尺寸，坐标必须为
 * 物理屏幕绝对坐标（单位px），用于输入法定位光标区域以实现精准输入和光标跟随。
 * 可通过TextConfig传递给输入法，也可通过NotifyCursorUpdate主动通知输入法。Create/Destroy必须配对。
 *     <br>
 *     <br>功能：创建和管理InputMethod_CursorInfo实例，用于描述文本输入时光标在物理屏幕上的位置和尺寸信息。光标信息是输入法服务
 * 确定光标区域、实现精准输入和光标跟随的关键数据。
 *     <br>
 *     <br>使用场景：在两种场景下使用CursorInfo：
 *     <br>1. 在TextConfig中设置光标信息：应用在GetTextConfig回调中返回TextConfig时，其中包含的CursorInfo告知输入法当前光标位
 * 置，输入法据此定位光标区域。
 *     <br>2. 主动通知光标更新：当光标位置发生变化时（如用户移动光标、文本插入导致光标偏移），应用通过
 * OH_InputMethodProxy_NotifyCursorUpdate主动通知输入法最新的光标位置。
 *     <br>
 *     <br>使用后效果：输入法根据CursorInfo中的光标位置调整键盘面板位置以实现光标跟随效果，同时在光标附近显示候选词区域。
 *
 * @include <inputmethod/inputmethod_cursor_info_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_CURSOR_INFO_CAPI_H
#define OHOS_INPUTMETHOD_CURSOR_INFO_CAPI_H
#include "inputmethod_types_capi.h"
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
/**
 * @brief InputMethod_CursorInfo是光标信息的不透明类型（opaque type），用于描述文本输入时光标在物理屏幕上的位置和尺寸，包括光标
 * 的水平坐标（left）、垂直坐标（top）、宽度（width）和高度（height）。 单位为px。
 *     <br>
 *     <br>用途：为输入法服务提供光标的精确位置和尺寸信息，输入法根据此信息实现以下功能：
 *     <br>- 光标跟随：键盘面板根据光标位置调整显示位置，确保键盘不遮挡光标所在区域。
 *     <br>- 候选词定位：输入法的候选词区域在光标附近显示，提供精准的输入体验。
 *     <br>- 避让计算：输入法根据光标高度和位置计算需要避让的区域。
 *     <br>
 *     <br>使用场景：
 *     <br>1. 在TextConfig中携带光标信息：应用在[OH_TextEditorProxy_GetTextConfigFunc]
 * (capi-inputmethod-text-editor-proxy-capi-h.md#oh_texteditorproxy_gettextconfigfunc)回调中返回TextConfig时，其中包含的
 * CursorInfo告知输入法当前光标位置和尺寸。
 *     <br>2. 主动通知光标更新：当光标位置发生变化时（如用户移动光标、文本插入导致光标偏移），应用通过
 * [OH_InputMethodProxy_NotifyCursorUpdate](capi-inputmethod-inputmethod-proxy-capi-h.
 * md#oh_inputmethodproxy_notifycursorupdate)主动通知输入法最新的光标位置。
 *     <br>
 *     <br>相关函数：<br>
 * | 函数 | 说明 |
 * | -- | -- |
 * | [OH_CursorInfo_Create](capi-inputmethod-cursor-info-capi-h.md#oh_cursorinfo_create) | 创建CursorInfo实例，需
 * 传入left、top、width、height。 |
 * | [OH_CursorInfo_Destroy](capi-inputmethod-cursor-info-capi-h.md#oh_cursorinfo_destroy) | 销毁CursorInfo实例。 |
 * | [OH_CursorInfo_SetRect](capi-inputmethod-cursor-info-capi-h.md#oh_cursorinfo_setrect) | 设置光标的位置和尺寸。 |
 * | [OH_CursorInfo_GetRect](capi-inputmethod-cursor-info-capi-h.md#oh_cursorinfo_getrect) | 获取光标的位置和尺寸。 |
 *     <br>
 *     <br>与其他结构体的关系：
 *     <br>- 与InputMethod_TextConfig的关系：CursorInfo是TextConfig的子属性。应用在[OH_TextEditorProxy_GetTextConfigFunc]
 * (capi-inputmethod-text-editor-proxy-capi-h.md#oh_texteditorproxy_gettextconfigfunc)回调中返回TextConfig时，TextConfig
 * 内部包含CursorInfo，输入法通过[OH_TextConfig_GetCursorInfo](capi-inputmethod-text-config-capi-h.
 * md#oh_textconfig_getcursorinfo)获取光标信息。因此应用需先创建CursorInfo并设置正确的光标坐标，然后在GetTextConfig回调中将
 * CursorInfo放入TextConfig。
 *     <br>- 与OH_InputMethodProxy_NotifyCursorUpdate的关系：CursorInfo作为NotifyCursorUpdate函数的参数直接传入，用于在光标
 * 位置变化时主动通知输入法。应用创建或更新CursorInfo后，通过NotifyCursorUpdate将最新光标信息发送给输入法。
 *
 *     <br>- 与InputMethod_InputMethodProxy的关系：NotifyCursorUpdate函数需要InputMethod_InputMethodProxy参数（由Attach返
 * 回）和InputMethod_CursorInfo参数配合使用，inputMethodProxy标识交互通道，cursorInfo携带光标信息。
 *
 * @since 12
 */
typedef struct InputMethod_CursorInfo InputMethod_CursorInfo;

/**
 * @brief 创建一个新的{@link InputMethod_CursorInfo}实例，初始化光标的位置和尺寸信息。
 *     <br>
 *     <br>配对调用：必须与[OH_CursorInfo_Destroy](#oh_cursorinfo_destroy)配对调用，Create创建的对象必须通过Destroy销毁，否
 * 则会导致内存泄漏。
 *     <br>
 *     <br>生命周期管理：
 *     <br>- 创建后可通过SetRect修改光标信息，通过GetRect读取光标信息。
 *     <br>- CursorInfo实例可作为TextConfig的属性传递给输入法（在GetTextConfig回调中返回）。
 *     <br>- CursorInfo实例也可作为NotifyCursorUpdate的参数主动通知输入法光标更新。
 *     <br>- 在这两种场景中，CursorInfo的内存由调用者管理，输入法仅在回调执行期间或NotifyCursorUpdate调用期间读取数据，完成后不
 * 再持有引用。
 *     <br>- 不再需要时必须通过Destroy销毁。
 *
 * @param left 输入参数，光标靠左点相对于物理屏幕左侧的距离的绝对值。
 *     <br>**含义/功能：** 定义光标矩形区域的左边界在物理屏幕上的水平位置。
 *     <br>**使用场景：** 标识光标在屏幕上的水平起始位置，输入法据此定位光标区域。
 *     <br>**使用后效果：** 输入法根据left值确定光标的水平位置，实现键盘面板的光标跟随效果。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 必须为物理屏幕的绝对坐标值，不可使用相对坐标（如相对于父组件或窗口的坐标）。在多窗口场景下，仍需使用物理
 * 屏幕绝对坐标。
 *     <br>**生效机制：** 输入法服务将根据此值计算光标在屏幕上的实际位置。
 * @param top 输入参数，光标顶点与物理屏幕上侧距离的绝对值。
 *     <br>**含义/功能：** 定义光标矩形区域的顶边界在物理屏幕上的垂直位置。
 *     <br>**使用场景：** 标识光标在屏幕上的垂直起始位置。
 *     <br>**使用后效果：** 输入法根据top值确定光标的垂直位置，用于键盘避让计算和候选词定位。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 必须为物理屏幕的绝对坐标值，不可使用相对坐标。
 * @param width 输入参数，光标的宽度。
 *     <br>**含义/功能：** 定义光标矩形区域的宽度。
 *     <br>**使用场景：** 描述光标的水平尺寸，输入法据此判断光标区域大小。
 *     <br>**使用后效果：** 输入法根据光标宽度调整候选词区域的定位。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 通常设置为光标的实际显示宽度，单字符光标宽度通常为1-2px，选区光标宽度为选区文本的宽度。
 * @param height 输入参数，光标的高度。
 *     <br>**含义/功能：** 定义光标矩形区域的高度。
 *     <br>**使用场景：** 描述光标的垂直尺寸，输入法据此判断光标区域大小和计算避让区域。
 *     <br>**使用后效果：** 输入法根据光标高度调整键盘面板的避让区域。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 通常设置为光标的实际显示高度，与文本行高一致。
 * @return 返回指针类型。
 *     <br>**创建成功：** 返回一个指向新创建的InputMethod_CursorInfo实例的指针，该指针有效且可用于后续操作。
 *     <br>**创建失败：** 返回NULL，可能的失败原因包括应用程序的地址空间耗尽（内存不足）。
 *     <br>**NULL判断：** 调用者必须在使用返回值前检查是否为NULL，若为NULL则不可使用该指针，应排查内存状况或稍后重试。
 *     <br>**内存管理：** 返回的指针由Create函数内部分配内存，调用者需通过OH_CursorInfo_Destroy释放，不可使用free()或其他方式释
 * 放。
 *
 * @since 12
 */
InputMethod_CursorInfo *OH_CursorInfo_Create(double left, double top, double width, double height);

/**
 * @brief 销毁一个{@link InputMethod_CursorInfo}实例，释放由Create函数分配的内存资源。
 *     <br>
 *     <br>配对调用：必须与OH_CursorInfo_Create配对调用。每个Create创建的实例必须且只能调用一次Destroy。
 *     <br>
 *     <br>生命周期管理：
 *     <br>- Destroy后，cursorInfo指针不再有效，不可继续使用。
 *     <br>- 不可对同一个cursorInfo指针调用两次Destroy，否则会导致重复释放（double-free）。
 *     <br>- 若cursorInfo正在被输入法回调使用（如处于GetTextConfig回调执行期间），不可在此期间调用Destroy，应在回调返回后再销
 * 毁。
 *
 * @param cursorInfo 输入指针，表示指向即将被销毁的InputMethod_CursorInfo实例的指针。
 *     <br>**含义/功能：** 指定要销毁的CursorInfo实例，Destroy将释放该实例占用的内存资源。
 *     <br>**使用场景：** 在CursorInfo不再需要时调用，典型时机为NotifyCursorUpdate调用完成后或应用退出时。
 *     <br>**使用后效果：** cursorInfo指向的内存被释放，该指针不再有效。
 *     <br>**NULL指针处理：** 若cursorInfo为NULL，Destroy函数不做任何操作（安全处理），不会导致崩溃。但建议调用者避免传入NULL。
 *     <br>**内存释放责任：** 由调用者负责在适当时机调用Destroy释放内存。
 * @since 12
 */
void OH_CursorInfo_Destroy(InputMethod_CursorInfo *cursorInfo);

/**
 * @brief 设置光标信息内容，更新光标的位置和尺寸。适用于在已有的CursorInfo实例上修改光标信息，无需重新创建实例。
 *     <br>
 *     <br>前置条件：cursorInfo必须是通过OH_CursorInfo_Create创建的有效实例。
 *
 * @param cursorInfo 输入指针，表示指向InputMethod_CursorInfo实例的指针。
 *     <br>**含义/功能：** 指定要修改的CursorInfo实例。
 *     <br>**NULL指针处理：** 不可为NULL，传入NULL将返回IME_ERR_NULL_POINTER。
 *     <br>**前提条件：** 必须通过OH_CursorInfo_Create创建的有效实例。
 * @param left 输入参数，光标靠左点与物理屏幕左侧距离的绝对值。
 *     <br>**含义/功能：** 定义光标矩形区域的左边界在物理屏幕上的水平位置。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 必须为物理屏幕的绝对坐标值，不可使用相对坐标。
 *     <br>**生效机制：** 设置后覆盖原有的left值，下次GetRect将返回新值。
 * @param top 输入参数，光标顶点与物理屏幕上侧距离的绝对值。
 *     <br>**含义/功能：** 定义光标矩形区域的顶边界在物理屏幕上的垂直位置。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 必须为物理屏幕的绝对坐标值，不可使用相对坐标。
 * @param width 输入参数，光标的宽度。
 *     <br>**使用场景：** 描述光标的水平尺寸，输入法据此判断光标区域大小。
 *     <br>**使用后效果：** 输入法根据光标宽度调整候选词区域的定位。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 通常设置为光标的实际显示宽度，单字符光标宽度通常为1-2px，选区光标宽度为选区文本的宽度。
 * @param height 输入参数，光标的高度。
 *     <br>**使用场景：** 描述光标的垂直尺寸，输入法据此判断光标区域大小和计算避让区域。
 *     <br>**使用后效果：** 输入法根据光标高度调整键盘面板的避让区域。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**取值范围：** ≥0。
 *     <br>**取值原则：** 通常设置为光标的实际显示高度，与文本行高一致。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。光标信息已更新。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。cursorInfo为NULL时返回，调用前需确保cursorInfo为有效指针。
 *     <br>**错误处理建议：** 若返回IME_ERR_NULL_POINTER，检查cursorInfo是否为有效指针。具体错误码可以参考
 * {@link InputMethod_ErrorCode}。
 *
 * @since 12
 */
InputMethod_ErrorCode OH_CursorInfo_SetRect(
    InputMethod_CursorInfo *cursorInfo, double left, double top, double width, double height);

/**
 * @brief 获取光标信息内容，读取光标的位置和尺寸。
 *     <br>
 *     <br>前置条件：cursorInfo必须是通过OH_CursorInfo_Create创建的有效实例。left、top、width、height必须指向有效的double变
 * 量。
 *
 * @param cursorInfo 输入指针，表示指向InputMethod_CursorInfo实例的指针。
 *     <br>**含义/功能：** 指定要读取的CursorInfo实例。
 *     <br>**NULL指针处理：** 不可为NULL，传入NULL将返回IME_ERR_NULL_POINTER。
 *     <br>**前提条件：** 必须通过OH_CursorInfo_Create创建的有效实例。
 * @param left 输出指针，靠左点与物理屏幕左侧距离的绝对值。
 *     <br>**含义/功能：** 接收光标左边界的水平坐标值。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**输出值范围：** ≥0。
 *     <br>**NULL指针处理：** 不可为NULL，传入NULL将返回IME_ERR_NULL_POINTER。
 *     <br>**内存分配责任：** 由调用者分配double变量的内存，GetRect仅写入值，不分配内存。
 * @param top 输出指针，顶点与物理屏幕上侧距离的绝对值。
 *     <br>**含义/功能：** 接收光标顶边界的垂直坐标值。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**输出值范围：** ≥0。
 *     <br>**NULL指针处理：** 不可为NULL。
 *     <br>**内存分配责任：** 由调用者分配double变量的内存。
 * @param width 输出指针，光标的宽度。
 *     <br>**含义/功能：** 接收光标宽度值。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**输出值范围：** ≥0。
 *     <br>**NULL指针处理：** 不可为NULL。
 *     <br>**内存分配责任：** 由调用者分配double变量的内存。
 * @param height 输出指针，光标的高度。
 *     <br>**含义/功能：** 接收光标高度值。
 *     <br>**参数单位：** px（物理像素）。
 *     <br>**输出值范围：** ≥0。
 *     <br>**NULL指针处理：** 不可为NULL。
 *     <br>**内存分配责任：** 由调用者分配double变量的内存。
 * @return 返回一个特定的错误码。
 *     <br>{@link IME_ERR_OK} - 表示成功。left、top、width、height已被赋值为正确的光标信息。
 *     <br>{@link IME_ERR_NULL_POINTER} - 非预期的空指针。cursorInfo、left、top、width或height为NULL时返回，调用前需确保所有
 * 参数均为有效指针。
 *     <br>**错误处理建议：** 若返回IME_ERR_NULL_POINTER，检查所有参数是否为有效指针；若返回IME_ERR_OK，四个输出参数即为正确的
 * 光标信息值。具体错误码可以参考{@link InputMethod_ErrorCode}。
 *
 * @since 12
 */
InputMethod_ErrorCode OH_CursorInfo_GetRect(
    InputMethod_CursorInfo *cursorInfo, double *left, double *top, double *width, double *height);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_CURSOR_INFO_CAPI_H
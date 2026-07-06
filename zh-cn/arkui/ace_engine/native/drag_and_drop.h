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
 * @brief Provides drag and drop APIs of ArkUI on the native side.
 *
 * @since 12
 */

/**
 * @file drag_and_drop.h
 *
 * @brief Declares the APIs of **NativeDrag**.
 *
 * @library libace_ndk.z.so
 * @kit ArkUI
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_DRAG_AND_DROP_H

#define ARKUI_NATIVE_DRAG_AND_DROP_H

#include <stdint.h>

#include "native_type.h"

#include "database/udmf/udmf.h"

#include "multimedia/image_framework/image/pixelmap_native.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 拖拽结果定义，由数据接收方设置，并由系统传递给数据拖出方，拖出方可感知接收方对数据的处理结果。
 *
 * @since 12
 */
typedef enum {
    /**
     * 拖拽处理成功。
     */
    ARKUI_DRAG_RESULT_SUCCESSFUL = 0,

    /**
     * 拖拽处理失败。
     */
    ARKUI_DRAG_RESULT_FAILED,

    /**
     * 拖拽处理取消。
     */
    ARKUI_DRAG_RESULT_CANCELED
} ArkUI_DragResult;

/**
 * @brief 定义拖拽释放时的数据处理方式，影响角标的显示。当设置为复制行为时角标显示加号，设置为剪切行为时角标不显示加号。
 *
 * @since 12
 */
typedef enum {
    /**
     * 复制行为。
     */
    ARKUI_DROP_OPERATION_COPY = 0,

    /**
     * 剪切行为。
     */
    ARKUI_DROP_OPERATION_MOVE
} ArkUI_DropOperation;

/**
 * @brief 定义拖拽发起前的长按交互阶段的变化状态。
 *
 * @since 12
 */
typedef enum {
    /**
     * Unknown.
     */
    ARKUI_PRE_DRAG_STATUS_UNKNOWN = -1,

    /**
     * 拖拽手势启动阶段。
     */
    ARKUI_PRE_DRAG_STATUS_ACTION_DETECTING,

    /**
     * 拖拽准备完成，可发起拖拽阶段。
     */
    ARKUI_PRE_DRAG_STATUS_READY_TO_TRIGGER_DRAG,

    /**
     * 拖拽浮起动效发起阶段。
     */
    ARKUI_PRE_DRAG_STATUS_PREVIEW_LIFT_STARTED,

    /**
     * 拖拽浮起动效结束阶段。
     */
    ARKUI_PRE_DRAG_STATUS_PREVIEW_LIFT_FINISHED,

    /**
     * 拖拽落回动效发起阶段。
     */
    ARKUI_PRE_DRAG_STATUS_PREVIEW_LANDING_STARTED,

    /**
     * 拖拽落回动效结束阶段。
     */
    ARKUI_PRE_DRAG_STATUS_PREVIEW_LANDING_FINISHED,

    /**
     * 拖拽浮起落位动效中断。
     */
    ARKUI_PRE_DRAG_STATUS_CANCELED_BEFORE_DRAG
} ArkUI_PreDragStatus;

/**
 * @brief 拖拽预览缩放模式。
 *
 * @since 12
 */
typedef enum {
    /**
     * 系统根据拖拽场景自动改变跟手点位置，根据规则自动对拖拽背板图进行缩放变换等。
     */
    ARKUI_DRAG_PREVIEW_SCALE_AUTO = 0,

    /**
     * 禁用系统对拖拽背板图的缩放行为。
     */
    ARKUI_DRAG_PREVIEW_SCALE_DISABLED
} ArkUI_DragPreviewScaleMode;

/**
 * @brief 拖拽状态。
 *
 * @since 12
 */
typedef enum {
    /**
     * Unknown.
     */
    ARKUI_DRAG_STATUS_UNKNOWN = -1,

    /**
     * 拖拽开始。
     */
    ARKUI_DRAG_STATUS_STARTED,

    /**
     * 拖拽结束。
     */
    ARKUI_DRAG_STATUS_ENDED
} ArkUI_DragStatus;

/**
 * @brief 定义组件事件的通用结构类型。
 *
 * @since 12
 */
typedef struct ArkUI_NodeEvent ArkUI_NodeEvent;

/**
 * @brief native UI的上下文实例对象。
 *
 * @since 12
 */
typedef struct ArkUI_Context ArkUI_Context;

/**
 * @brief 定义ArkUI native UI的上下文实例对象指针定义。
 *
 * @since 12
 */
typedef struct ArkUI_Context* ArkUI_ContextHandle;

/**
 * @brief 拖拽事件。
 *
 * @since 12
 */
typedef struct ArkUI_DragEvent ArkUI_DragEvent;

/**
 * @brief 定义拖拽跟手图的相关自定义参数。
 *
 * @since 12
 */
typedef struct ArkUI_DragPreviewOption ArkUI_DragPreviewOption;

/**
 * @brief 拖拽行为，用于主动发起拖拽。
 *
 * @since 12
 */
typedef struct ArkUI_DragAction ArkUI_DragAction;

/**
 * @brief 主动发起拖拽后，通过拖拽状态监听返回的系统拖拽相关数据。
 *
 * @since 12
 */
typedef struct ArkUI_DragAndDropInfo ArkUI_DragAndDropInfo;

/**
 * @brief 从 NodeEvent 中获取DragEvent。
 *
 * @param nodeEvent ArkUI_NodeEvent事件指针。
 * @return ArkUI_DragEvent 事件指针，当传入的 NodeEvent 无效或不是拖拽相关的事件时，则返回空。
 * @since 12
 */
ArkUI_DragEvent* OH_ArkUI_NodeEvent_GetDragEvent(ArkUI_NodeEvent* nodeEvent);

/**
 * @brief 获取预览拖拽事件状态。
 *
 * @param nodeEvent ArkUI_NodeEvent节点对象。
 * @return ArkUI_PreDragStatus 拖拽发起前交互状态。
 * @since 12
 */
ArkUI_PreDragStatus OH_ArkUI_NodeEvent_GetPreDragStatus(ArkUI_NodeEvent* nodeEvent);

/**
 * @brief 设置是否禁用松手时的系统默认动效，默认不禁用，通常在应用需要自定义落位动效时配置。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @param disable 是否禁用松手时的系统默认动效，true禁用，false不禁用。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_DisableDefaultDropAnimation(ArkUI_DragEvent* event, bool disable);

/**
 * @brief 设置数据处理方式。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @param dropOperation 角标显示状态的类型。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_SetSuggestedDropOperation(ArkUI_DragEvent* event, ArkUI_DropOperation dropOperation);

/**
 * @brief 设置拖拽事件的结果。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @param result 拖拽数据处理结果。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_SetDragResult(ArkUI_DragEvent* event, ArkUI_DragResult result);

/**
 * @brief 向ArkUI_DragEvent中设置拖拽数据。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @param data 拖拽数据。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_SetData(ArkUI_DragEvent* event, OH_UdmfData* data);

/**
 * @brief 使用此方法为系统提供一个数据加载参数，而不是直接提供一个完整的数据对象。当用户拖拽到目标应用程序并落入时，系统将使用dataLoadParams请求数据。可以极大地提高拖拽大量数据的效率，
 * 以及目标应用程序中处理落入数据的效率。此方法应始终优先于{@link OH_ArkUI_DragEvent_SetData}使用。请参考<b>udmf.h</b>中的
 * {@link OH_UdmfDataLoadParams_Create}了解如何创建和准备数据加载参数。该方法与{@link OH_ArkUI_DragEvent_SetData}存在冲突，系统始终以最后调用的方法为准。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @param dataLoadParams 落入操作时使用的数据加载参数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_DragEvent_SetDataLoadParams(ArkUI_DragEvent* event, OH_UdmfDataLoadParams* dataLoadParams);

/**
 * @brief 从ArkUI_DragEvent中获取拖拽默认相关数据。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @param data OH_UdmfData 拖拽的数据指针，应用在接收时需通过 {@link OH_UdmfData_Create} 方法创建一个用于接收数据的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_GetUdmfData(ArkUI_DragEvent* event, OH_UdmfData *data);

/**
 * @brief 从ArkUI_DragEvent中获取所拖拽的数据类型种类个数。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @param count 出参，返回所拖拽数据的类型的数量。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_GetDataTypeCount(ArkUI_DragEvent* event, int32_t* count);

/**
 * @brief 从ArkUI_DragEvent中获取拖拽数据的类型列表。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @param eventTypeArray Indicates the list of the drag data types. You need to create a string array first.
 * @param length 数组总长度，不应少于使用{@link OH_ArkUI_DragEvent_GetDataTypeCount}获取到的数量。
 * @param maxStrLen 拖拽数据类型的最大字符串长度。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 传入的缓冲区大小异常。
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_GetDataTypes(
    ArkUI_DragEvent *event, char *eventTypeArray[], int32_t length, int32_t maxStrLen);

/**
 * @brief 从ArkUI_DragEvent中获取拖拽结果。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @param result 出参，返回拖拽事件对应的拖拽结果。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_GetDragResult(ArkUI_DragEvent* event, ArkUI_DragResult* result);

/**
 * @brief 从ArkUI_DragEvent中获取数据处理方式。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @param operation 数据的处理方式.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>可能原因: 1. 参数为空或event非有效的DragEvent.
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_GetDropOperation(ArkUI_DragEvent* event, ArkUI_DropOperation* operation);

/**
 * @brief 从ArkUI_DragEvent中获取预览图跟手点的x轴坐标。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @return float 返回拖拽跟手点的x轴坐标，单位为px，传入参数无效时返回默认值0。
 * @since 12
 */
float OH_ArkUI_DragEvent_GetPreviewTouchPointX(ArkUI_DragEvent* event);

/**
 * @brief 从ArkUI_DragEvent中获取预览图跟手点的y轴坐标。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @return float 返回拖拽跟手点的y轴坐标，单位px，传入参数无效时返回默认值0。
 * @since 12
 */
float OH_ArkUI_DragEvent_GetPreviewTouchPointY(ArkUI_DragEvent* event);

/**
 * @brief 从ArkUI_DragEvent中获取预览图的宽。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @return float 返回拖拽跟手图宽度，单位为px，传入参数无效时返回默认值0。
 * @since 12
 */
float OH_ArkUI_DragEvent_GetPreviewRectWidth(ArkUI_DragEvent* event);

/**
 * @brief 从ArkUI_DragEvent中获取预览图的高。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @return float 返回拖拽跟手图高度，单位为px，传入参数无效时返回默认值0。
 * @since 12
 */
float OH_ArkUI_DragEvent_GetPreviewRectHeight(ArkUI_DragEvent* event);

/**
 * @brief 从ArkUI_DragEvent中获取跟手点相对于window的x轴坐标。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @return float 返回跟手点相对于window的x轴坐标，单位为px，传入参数无效时返回默认值0。
 * @since 12
 */
float OH_ArkUI_DragEvent_GetTouchPointXToWindow(ArkUI_DragEvent* event);

/**
 * @brief 从ArkUI_DragEvent中获取跟手点相对于window的y轴坐标。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @return float 返回跟手点相对于window的y轴坐标，单位为px，传入参数无效时返回默认值0。
 * @since 12
 */
float OH_ArkUI_DragEvent_GetTouchPointYToWindow(ArkUI_DragEvent* event);

/**
 * @brief 从ArkUI_DragEvent中获取跟手点相对于当前Display的x轴坐标。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @return float 返回拖拽跟手点相对于当前Display的x轴坐标，单位为px，传入参数无效时返回默认值0。
 * @since 12
 */
float OH_ArkUI_DragEvent_GetTouchPointXToDisplay(ArkUI_DragEvent* event);

/**
 * @brief 从ArkUI_DragEvent中获取跟手点相对于当前Display的y轴坐标。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @return float 返回拖拽跟手点相对于当前Display的y轴坐标，单位为px，传入参数无效时返回默认值0。
 * @since 12
 */
float OH_ArkUI_DragEvent_GetTouchPointYToDisplay(ArkUI_DragEvent* event);

/**
 * @brief 从ArkUI_DragEvent中获取跟手点相对于全局屏幕的x轴坐标。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @return float 返回拖拽跟手点相对于全局Display的x轴坐标，单位为px，传入参数无效时返回默认值0。
 * @since 20
 */
float OH_ArkUI_DragEvent_GetTouchPointXToGlobalDisplay(ArkUI_DragEvent* event);

/**
 * @brief 从ArkUI_DragEvent中获取跟手点相对于全局屏幕的y轴坐标。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @return float 返回拖拽跟手点相对于全局Display的y轴坐标，单位为px，传入参数无效时返回默认值0。
 * @since 20
 */
float OH_ArkUI_DragEvent_GetTouchPointYToGlobalDisplay(ArkUI_DragEvent* event);

/**
 * @brief 获取当前拖拽的x轴方向拖动速度。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @return float 返回当前拖拽的x轴方向移动速度，单位为px/s，传入参数无效时返回默认值0。
 * @since 12
 */
float OH_ArkUI_DragEvent_GetVelocityX(ArkUI_DragEvent* event);

/**
 * @brief 获取当前拖拽的y轴方向拖动速度。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @return float 返回当前拖拽的y轴方向移动速度，单位为px/s，传入参数无效时返回默认值0。
 * @since 12
 */
float OH_ArkUI_DragEvent_GetVelocityY(ArkUI_DragEvent* event);

/**
 * @brief 获取当前拖拽的主方向拖动速度。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @return float 返回当前拖拽移动速度，单位为px/s，传入参数无效时返回默认值0。
 * @since 12
 */
float OH_ArkUI_DragEvent_GetVelocity(ArkUI_DragEvent* event);

/**
 * @brief 获取功能键按压状态。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @param keys 返回当前处于按下状态的修饰键组合（Ctrl、Shift和Alt），应用可通过位运算进行判断。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_GetModifierKeyStates(ArkUI_DragEvent* event, uint64_t* keys);

/**
 * @brief 获取当前拖拽事件发生时所在的屏幕ID，不支持当eventType为NODE_ON_DRAG_END时获取。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @param displayId 返回当前拖拽事件发生时所在的屏幕ID。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_DragEvent_GetDisplayId(ArkUI_DragEvent* event, int32_t* displayId);

/**
 * @brief 使用指定的同步参数开始数据同步。
 *
 * @param event ArkUI_DragEvent事件指针。
 * @param options OH_UdmfGetDataParams参数指针。
 * @param key 返回数据设置成功之后的key值，字符串长度不小于{@link UDMF_KEY_BUFFER_LEN}。
 * @param keyLen 表示key字符串的长度。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 15
 */
int32_t OH_ArkUI_DragEvent_StartDataLoading(
    ArkUI_DragEvent* event, OH_UdmfGetDataParams* options, char* key, unsigned int keyLen);

/**
 * @brief 取消正在进行的数据同步。
 *
 * @param uiContext UI实例对象指针。
 * @param key 表示数据的key值并通过 {@link OH_ArkUI_DragEvent_StartDataLoading} 返回。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 15
 */
int32_t OH_ArkUI_CancelDataLoading(ArkUI_ContextHandle uiContext, const char* key);

/**
 * @brief 设置是否在执行{@link NODE_ON_DROP}之前禁用数据预获取过程。系统将重试获取数据，直到达到最大时间限制（目前为2.4秒），这对跨设备的拖动操作非常有用，因为它有助于系统稳定通信。然而，对于
 * {@link OH_ArkUI_DragEvent_StartDataLoading}方法而言，这一特性显得多余。该方法采用异步机制获取数据，因此在NODE_ON_DROP中使用
 * {@link OH_ArkUI_DragEvent_StartDataLoading}时，为了避免在NODE_ON_DROP执行前意外获取数据，必须将此字段设置为true。
 *
 * @param node 组件节点指针。
 * @param disabled 表示是禁用数据预取过程。true表示禁止，false表示不禁止。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 15
 */
int32_t OH_ArkUI_DisableDropDataPrefetchOnNode(ArkUI_NodeHandle node, bool disabled);

/**
 * @brief 控制是否使能严格dragEvent上报，建议开启；默认是不开启的；当不开启时，从父组件拖移进子组件时，父组件并不会收到leave的通知；而开启之后，只要前后两个组件发生变化，上一个组件就会收到leave，
 * 新的组件收到enter通知；该配置与具体的UI实例相关，需要通过传入一个当前UI实例上的一个具体的组件节点来关联。
 *
 * @param node 组件节点指针。
 * @param enabled 是否开启严格上报。true表示开启严格上报，false表示关闭严格上报。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_SetDragEventStrictReportWithNode(ArkUI_NodeHandle node, bool enabled);

/**
 * @brief 控制是否使能严格dragEvent上报，建议开启；默认是不开启的;当不开启时，从父组件拖移进子组件时，父组件并不会收到leave的通知；而开启之后，只要前后两个组件发生变化，上一个组件就会收到leave，
 * 新的组件收到enter通知；该配置与具体的UI实例相关，可通过传入一个UI实例进行关联。
 *
 * @param uiContext UI实例指针。
 * @param enabled 是否开启严格上报。true表示开启严格上报，false表示关闭严格上报。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_SetDragEventStrictReportWithContext(ArkUI_ContextHandle uiContext, bool enabled);

/**
 * @brief 配置组件允许接受落入的数据类型，该接口会重置通过 {@link OH_ArkUI_DisallowNodeAnyDropDataTypes} 或
 * {@link OH_ArkUI_AllowNodeAllDropDataTypes}进行的配置。
 *
 * @param node 组件节点指针。
 * @param typesArray Indicates the array of types of data that can be dropped.
 * @param count 数组的长度。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_SetNodeAllowedDropDataTypes(ArkUI_NodeHandle node, const char* typesArray[], int32_t count);

/**
 * @brief 配置组件不允许接受任何数据类型，该接口会重置通过{@link OH_ArkUI_SetNodeAllowedDropDataTypes}配置的数据类型。
 *
 * @param node 组件节点指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DisallowNodeAnyDropDataTypes(ArkUI_NodeHandle node);

/**
 * @brief 配置组件允许接受任意数据类型，该接口会重置通过{@link OH_ArkUI_SetNodeAllowedDropDataTypes}配置的数据类型。
 *
 * @param node 组件节点指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_AllowNodeAllDropDataTypes(ArkUI_NodeHandle node);

/**
 * @brief 设置该组件是否允许进行拖拽。
 *
 * @param node 组件节点指针。
 * @param enabled 是否支持拖出。true表示支持拖出，false表示不支持拖出。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_SetNodeDraggable(ArkUI_NodeHandle node, bool enabled);

/**
 * @brief 设置组件在被拖拽时的自定义跟手图。
 *
 * @param node 目标组件节点指针。
 * @param preview 自定义跟手图，使用 pixelmap 格式。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_SetNodeDragPreview(ArkUI_NodeHandle node, OH_PixelmapNative* preview);

/**
 * @brief Creates an ArkUI_DragPreviewOption对象。
 *
 * @return ArkUI_DragPreviewOption对象。
 * @since 12
 */
ArkUI_DragPreviewOption* OH_ArkUI_CreateDragPreviewOption(void);

/**
 * @brief 销毁跟手图自定义参数对象实例。
 *
 * @param option 自定义参数。
 * @since 12
 */
void OH_ArkUI_DragPreviewOption_Dispose(ArkUI_DragPreviewOption* option);

/**
 * @brief 设置拖拽跟手图是否根据系统定义自动进行缩放。
 *
 * @param option 自定义参数。
 * @param scaleMode 设置组件拖拽过程中的跟手图缩放模式。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragPreviewOption_SetScaleMode(ArkUI_DragPreviewOption* option, ArkUI_DragPreviewScaleMode scaleMode);

/**
 * @brief 设置跟手图背板默认的投影效果，默认不开启。
 *
 * @param option 自定义参数。
 * @param enabled 是否使用默认投影效果。true表示使用默认投影效果，false表示不使用默认投影效果。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled(ArkUI_DragPreviewOption* option, bool enabled);

/**
 * @brief 设置跟手图背板默认的圆角效果（默认圆角半径为12.0vp），默认不开启。
 *
 * @param option 自定义参数。
 * @param enabled 是否开启圆角效果显示。true表示开启圆角效果显示，false表示不开启圆角效果显示。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragPreviewOption_SetDefaultRadiusEnabled(ArkUI_DragPreviewOption* option, bool enabled);

/**
 * @brief 设置跟手图背板是否显示角标,开启后,系统会根据拖拽数量自动进行角标显示。
 *
 * @param option 自定义参数。
 * @param enabled 是否开启角标显示。true表示开启角标显示，false表示不开启角标显示。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragPreviewOption_SetNumberBadgeEnabled(ArkUI_DragPreviewOption* option, bool enabled);

/**
 * @brief 强制显示角标的数量，覆盖{@link OH_ArkUI_DragPreviewOption_SetNumberBadgeEnabled}设置的值。
 *
 * @param option 自定义参数。
 * @param forcedNumber 角标的数量。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragPreviewOption_SetBadgeNumber(ArkUI_DragPreviewOption* option, uint32_t forcedNumber);

/**
 * @brief 配置是否开启点按时的默认动画。
 *
 * @param option 自定义参数。
 * @param enabled 是否开启默认点按效果。true表示开启默认点按效果，false表示不开启默认点按效果。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragPreviewOption_SetDefaultAnimationBeforeLiftingEnabled(
    ArkUI_DragPreviewOption* option, bool enabled);

/**
 * @brief 将构造的ArkUI_DragPreviewOption设置给组件。
 *
 * @param node 组件节点指针。
 * @param option 自定义参数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_SetNodeDragPreviewOption(ArkUI_NodeHandle node, ArkUI_DragPreviewOption* option);

/**
 * @brief 创建一个拖拽操作对象，该对象需与一个UI实例相关联，可通过传入一个当前UI实例的某个组件节点来指定。
 *
 * @param node 组件节点指针。
 * @return ArkUI_DragAction对象指针，如果创建失败，则返回空。
 * @since 12
 */
ArkUI_DragAction* OH_ArkUI_CreateDragActionWithNode(ArkUI_NodeHandle node);

/**
 * @brief 创建一个拖拽操作对象，该对象需与一个UI实例相关联，可通过传入一个UI实例指针来关联。
 *
 * @param uiContext UI实例对象指针。
 * @return ArkUI_DragAction对象，如果创建失败，则返回空。
 * @since 12
 */
ArkUI_DragAction* OH_ArkUI_CreateDragActionWithContext(ArkUI_ContextHandle uiContext);

/**
 * @brief 销毁创建的 ArkUI_DragAction 对象。
 *
 * @param dragAction 拖拽行为对象。
 * @since 12
 */
void OH_ArkUI_DragAction_Dispose(ArkUI_DragAction* dragAction);

/**
 * @brief 设置手指ID，当屏幕上仅有一只手指在操作时，手指ID为0；一般情况下，配置0即可。
 *
 * @param dragAction 拖拽行为对象。
 * @param pointer 手指ID，范围0～9。取值超出时默认置为-1。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragAction_SetPointerId(ArkUI_DragAction* dragAction, int32_t pointer);

/**
 * @brief 设置拖拽跟手图，只能使用 pixelmap 格式对象。
 *
 * @param dragAction 拖拽行为对象。
 * @param pixelmapArray Indicates the array of the drag previews to set, which must be pixel maps.
 * @param size 拖拽跟手图数量。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragAction_SetPixelMaps(
    ArkUI_DragAction* dragAction, OH_PixelmapNative* pixelmapArray[], int32_t size);

/**
 * @brief 设置跟手点，相对于设置的第一个pixelmap的左上角。
 *
 * @param dragAction 拖拽行为对象。
 * @param x 跟手点坐标x值，单位为px。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragAction_SetTouchPointX(ArkUI_DragAction* dragAction, float x);

/**
 * @brief 设置跟手点，相对于设置的第一个pixelmap的左上角。
 *
 * @param dragAction 拖拽行为对象。
 * @param y 跟手点坐标y值，单位为px。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragAction_SetTouchPointY(ArkUI_DragAction* dragAction, float y);

/**
 * @brief 设置拖拽数据。
 *
 * @param dragAction 拖拽行为对象。
 * @param data 拖拽数据。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragAction_SetData(ArkUI_DragAction* dragAction, OH_UdmfData* data);

/**
 * @brief 使用此方法为系统提供一个数据加载参数，而不是直接提供一个完整的数据对象。当用户拖拽到目标应用程序并落入时，系统将使用dataLoadParams请求数据。可以极大地提高拖拽大量数据的效率，
 * 以及目标应用程序中处理落入数据的效率。此方法应始终优先于{@link OH_ArkUI_DragAction_SetData}使用。请参考<b>udmf.h</b>中的
 * {@link OH_UdmfDataLoadParams_Create}了解如何创建和准备数据加载参数。该方法与{@link OH_ArkUI_DragAction_SetData}存在冲突，系统始终以最后调用的方法为准。
 *
 * @param dragAction 拖拽行为对象。
 * @param dataLoadParams 在落入操作时使用的数据加载参数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_DragAction_SetDataLoadParams(ArkUI_DragAction* dragAction,
    OH_UdmfDataLoadParams* dataLoadParams);

/**
 * @brief 将构造的ArkUI_DragPreviewOption设置给ArkUI_DragAction。
 *
 * @param dragAction 拖拽行为对象。
 * @param option 自定义参数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragAction_SetDragPreviewOption(ArkUI_DragAction* dragAction, ArkUI_DragPreviewOption* option);

/**
 * @brief 注册拖拽状态监听回调，该回调可感知到拖拽已经发起或用户松手结束的状态，可通过该监听获取到落入方对数据的接收处理是否成功。
 *
 * @param dragAction 拖拽行为对象。
 * @param userData 应用自定义数据。
 * @param listener 状态监听回调，回调触发时，系统会返回一个拖拽状态对象指针，该指针会在回调执行完成后被销毁，应用不应再持有。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_DragAction_RegisterStatusListener(ArkUI_DragAction* dragAction, void* userData,
    void(*listener)(ArkUI_DragAndDropInfo* dragAndDropInfo, void* userData));

/**
 * @brief 解注册拖拽状态监听回调。
 *
 * @param dragAction 拖拽行为对象。
 * @since 12
 */
void OH_ArkUI_DragAction_UnregisterStatusListener(ArkUI_DragAction* dragAction);

/**
 * @brief 获取{@link ArkUI_DragAction}发起拖拽的状态，获取异常时返回 ArkUI_DRAG_STATUS_UNKNOWN。
 *
 * @param dragAndDropInfo 拖拽状态监听返回的拖拽相关信息。
 * @return ArkUI_DragStatus 拖拽状态，如果获取失败，返回默认值 ArkUI_DRAG_STATUS_UNKNOWN。
 * @since 12
 */
ArkUI_DragStatus OH_ArkUI_DragAndDropInfo_GetDragStatus(ArkUI_DragAndDropInfo* dragAndDropInfo);

/**
 * @brief 通过dragAndDropInfo获取到DragEvent，可通过DragEvent获取释放结果等。
 *
 * @param dragAndDropInfo 拖拽状态监听返回的拖拽相关信息。
 * @return ArkUI_DragEvent 拖拽事件，如果获取失败，则返回空。
 * @since 12
 */
ArkUI_DragEvent* OH_ArkUI_DragAndDropInfo_GetDragEvent(ArkUI_DragAndDropInfo* dragAndDropInfo);

/**
 * @brief 通过构造的DragAction对象发起拖拽。
 *
 * @param dragAction 拖拽action对象。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_StartDrag(ArkUI_DragAction* dragAction);

/**
 * @brief 请求延迟处理拖拽结束事件，等待应用程序确认操作结果。应用程序需通过 {@link OH_ArkUI_NotifyDragResult}接口将最终结果回传至系统，并在所有处理完成后调用
 * {@link OH_ArkUI_NotifyDragEndPendingDone}。最大等待时间为2秒。
 *
 * @param event 指向 <b>ArkUI_DragEvent</b> 对象的指针。
 * @param requestIdentify 系统自动生成的请求标识符，是一个输出参数，需要为一个有效的地址。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR}  成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID}  函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED}  当前阶段不允许该操作。
 * @since 19
 */
int32_t OH_ArkUI_DragEvent_RequestDragEndPending(ArkUI_DragEvent* event, int32_t* requestIdentify);

/**
 * @brief 通知系统最终拖拽结果。系统会校验请求标识符是否与{@link OH_ArkUI_DragEvent_RequestDragEndPending}返回的一致，不一致则忽略本次调用。
 *
 * @param requestIdentify 由 {@link OH_ArkUI_DragEvent_RequestDragEndPending} 返回的标识符。
 * @param result 拖拽结果枚举值（{@link ArkUI_DragResult} 类型）。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR}  成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID}  函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED}  当前阶段不允许该操作。
 * @since 19
 */
int32_t OH_ArkUI_NotifyDragResult(int32_t requestIdentify, ArkUI_DragResult result);

/**
 * @brief 通知拖拽发起方本次落入的行为类型。拖拽发起方可以在拖拽结束的回调中调用{@link OH_ArkUI_DragEvent_GetDropOperation}获取本次落入的行为类型，进行自定义处理。也可以选择忽略该通知，
 * 不进行处理。拖拽失败时，本次落入的行为类型不可信，此时调用{@link OH_ArkUI_DragEvent_GetDropOperation}获取到的行为类型恒为ARKUI_DROP_OPERATION_COPY。
 * 系统会校验requestIdentity是否与{@link OH_ArkUI_DragEvent_RequestDragEndPending}返回的一致，不一致则本次调用不生效。
 *
 * @param requestIdentity The identity returned by {@link OH_ArkUI_DragEvent_RequestDragEndPending} interface.
 * @param operation 落入行为类型{@link ArkUI_DropOperation}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED} 函数未在落入阶段调用。
 * @since 24
 */
int32_t OH_ArkUI_NotifySuggestedDropOperation(int32_t requestIdentity, ArkUI_DropOperation operation);

/**
 * @brief 通知系统是否禁用默认的落入动画。拖拽失败时，默认的落入动画为扩散动画，拖拽成功时默认的落入动画为收缩淡出动画。调用此方法可禁用默认动画，根据需要实现自定义落入动画。系统会校验requestIdentity是否与
 * {@link OH_ArkUI_DragEvent_RequestDragEndPending}返回的一致，不一致则本次调用不生效。
 *
 * @param requestIdentity The identity returned by {@link OH_ArkUI_DragEvent_RequestDragEndPending} interface.
 * @param disable 通知是否禁用系统默认落入动画。true表示禁用系统默认落入动画，false表示使用系统默认落入动画。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED} 函数未在落入阶段调用。
 * @since 24
 */
int32_t OH_ArkUI_NotifyDisableDefaultDropAnimation(int32_t requestIdentity, bool disable);

/**
 * @brief 通知系统所有异步处理已完成，可结束拖拽结束挂起状态。
 *
 * @param requestIdentify 由 {@link OH_ArkUI_DragEvent_RequestDragEndPending} 返回的标识符。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR}  成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID}  函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED}  当前阶段不允许该操作。
 * @since 19
 */
int32_t OH_ArkUI_NotifyDragEndPendingDone(int32_t requestIdentify);

/**
 * @brief 获取拖拽发起方的应用包名信息，需要传递一个字符数组来接收包名字符串，并显式指明数组长度，该数组长度不小于128个字符。
 *
 * @param event 指向<b>ArkUI_DragEvent</b>对象的指针。
 * @param bundleName 用来接收拖起方包名的字符串数组，长度不应小于128个字符。
 * @param length 用来显式指明传入的字符串数组长度，不应小于128个字符。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_DragEvent_GetDragSource(ArkUI_DragEvent* event, char *bundleName, int32_t length);

/**
 * @brief 判断当前的拖拽操作是否是跨设备拖拽。
 *
 * @param event 指向<b>ArkUI_DragEvent</b>对象的指针。
 * @param isRemote 布尔变量指针，用来接收是否是跨设备拖拽。true表示是跨设备拖拽，false表示非跨设备拖拽。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_DragEvent_IsRemote(ArkUI_DragEvent* event, bool* isRemote);

/**
  * @brief 设置是否可以显示禁用角标。
  *
  * @param uiContext UI实例对象指针。
  * @param enabled 是否可以显示禁用角标。true表示可以显示禁用角标，false表示不可以显示禁用角标。
  * @return 错误码。
  *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
  *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
  * @since 20
  */
ArkUI_ErrorCode OH_ArkUI_EnableDropDisallowedBadge(ArkUI_ContextHandle uiContext, bool enabled);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_DRAG_AND_DROP_H

/** @} */
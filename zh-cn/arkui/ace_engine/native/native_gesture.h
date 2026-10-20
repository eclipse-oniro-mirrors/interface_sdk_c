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
 * @brief Defines APIs for ArkUI to register gesture callbacks on the native side.
 *
 * @since 12
 */

/**
 * @file native_gesture.h
 *
 * @brief 提供NativeGesture接口的类型定义，支持手势识别器、手势事件、手势打断、触摸识别器、手势收集干预以及手势参数查询与设置等能力，适用于应用通过Native接口处理手势识别、手势冲突和手势收集干预等场景。
 * 手势识别管线按优先级和竞争规则进行识别，可通过打断回调拦截手势；手势收集干预机制允许在手势收集阶段动态干预手势的收集流程。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_GESTURE_H
#define ARKUI_NATIVE_GESTURE_H

#include "ui_input_event.h"
#include "native_type.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 提供手势组件实例对象定义，用于在ArkUI手势识别接口中表示手势识别器对象。手势识别器绑定到UI组件后监听触摸事件，并在满足对应手势类型的识别条件时通过回调通知开发者；不同类型的识别器可用于敲击、长按、拖动、捏合、
 * 旋转和快滑等手势。详细机制和使用方式请参见{@link native_gesture.h}中的手势接口说明。
 *
 * @since 12
 */
typedef struct ArkUI_GestureRecognizer ArkUI_GestureRecognizer;

/**
 * @brief 定义手势打断事件数据类型，用于向手势打断回调传递手势识别器、响应链手势识别器和触摸识别器等信息。回调可根据这些信息返回继续或拒绝结果。手势打断机制和接口请参见{@link native_gesture.h}
 * 中的手势打断接口说明。
 *
 * @since 12
 */
typedef struct ArkUI_GestureInterruptInfo ArkUI_GestureInterruptInfo;

/**
 * @brief 提供手势事件数据类型对象定义，用于在手势事件处理过程中承载和传递手势事件相关数据，支持获取手势事件类型、坐标、时间戳等关键信息；适用于需要处理触摸手势交互的场景，如点击、长按、拖动、缩放等手势识别与响应；
 * 开发者可通过相关手势事件接口获取事件信息。
 *
 * @since 12
 */
typedef struct ArkUI_GestureEvent ArkUI_GestureEvent;

/**
 * @brief 定义手势事件类型。
 *
 * @since 12
 */
typedef enum {
    /**
     * 手势事件触发。
     */
    GESTURE_EVENT_ACTION_ACCEPT = 0x01,

    /**
     * 手势事件更新。
     */
    GESTURE_EVENT_ACTION_UPDATE = 0x02,

    /**
     * 手势事件结束。
     */
    GESTURE_EVENT_ACTION_END = 0x04,

    /**
     * 手势事件取消。
     */
    GESTURE_EVENT_ACTION_CANCEL = 0x08
} ArkUI_GestureEventActionType;

/**
 * @brief 定义手势事件类型集合。例：ArkUI_GestureEventActionTypeMask actions = GESTURE_EVENT_ACTION_ACCEPT \|
 * GESTURE_EVENT_ACTION_UPDATE。
 *
 * @since 12
 */
typedef uint32_t ArkUI_GestureEventActionTypeMask;

/**
 * @brief 定义手势优先级。NORMAL适用于默认手势识别场景；PRIORITY适用于需要确保某个手势优先响应的场景（如优先响应点击而非滑动）；PARALLEL适用于多个手势需要同时独立响应的场景（如同时识别捏合和旋转）。
 *
 * @since 12
 */
typedef enum {
    /**
     * 正常手势。
     */
    NORMAL = 0,

    /**
     * 高优先级手势。
     */
    PRIORITY = 1,

    /**
     * 并发手势。
     */
    PARALLEL = 2
} ArkUI_GesturePriority;

/**
 * @brief 定义手势组事件模式。SEQUENTIAL_GROUP适用于需要按步骤依次识别手势的场景（如先长按再滑动）；PARALLEL_GROUP适用于多个手势需要独立同时识别的场景（如同时监听捏合和旋转）；
 * EXCLUSIVE_GROUP适用于多个手势互斥竞争、只需一个成功的场景（如滑动和长按互斥）。
 *
 * @since 12
 */
typedef enum {
    /**
     * 顺序手势模式，按照注册顺序识别手势，直到所有手势识别成功。若有识别失败，后续识别均失败。仅有最后一个手势响应结束事件。
     */
    SEQUENTIAL_GROUP = 0,

    /**
     * 并发手势模式，注册的手势同时识别，直到所有手势识别结束，手势识别互相不影响。
     */
    PARALLEL_GROUP = 1,

    /**
     * 互斥手势模式，注册的手势同时识别，若有一个手势识别成功，则结束手势识别。
     */
    EXCLUSIVE_GROUP = 2
} ArkUI_GroupGestureMode;

/**
 * @brief 定义滑动手势方向。
 *
 * @since 12
 */
typedef enum {
    /**
     * 所有方向。
     */
    GESTURE_DIRECTION_ALL = 0b1111,

    /**
     * 水平方向。
     */
    GESTURE_DIRECTION_HORIZONTAL = 0b0011,

    /**
     * 竖直方向。
     */
    GESTURE_DIRECTION_VERTICAL = 0b1100,

    /**
     * 向左方向。
     */
    GESTURE_DIRECTION_LEFT = 0b0001,

    /**
     * 向右方向。
     */
    GESTURE_DIRECTION_RIGHT = 0b0010,

    /**
     * 向上方向。
     */
    GESTURE_DIRECTION_UP = 0b0100,

    /**
     * 向下方向。
     */
    GESTURE_DIRECTION_DOWN = 0b1000,

    /**
     * 任何方向都不触发手势事件。
     */
    GESTURE_DIRECTION_NONE = 0
} ArkUI_GestureDirection;

/**
 * @brief 定义滑动手势方向集合。
 * <br>例：ArkUI_GestureDirectionMask directions = GESTURE_DIRECTION_LEFT \| GESTURE_DIRECTION_RIGHT。
 * <br>directions 表明支持左右水平方向。
 *
 * @since 12
 */
typedef uint32_t ArkUI_GestureDirectionMask;

/**
 * @brief 定义手势屏蔽模式。NORMAL_GESTURE_MASK适用于默认场景，子组件手势按正常顺序识别；IGNORE_INTERNAL_GESTURE_MASK适用于父组件需要独占手势控制的场景（
 * 如全屏滑动时屏蔽子组件的手势干扰），会屏蔽子组件包括系统内置的手势。
 *
 * @since 12
 */
typedef enum {
    /**
     * 不屏蔽子组件的手势，按照默认手势识别顺序进行识别。
     */
    NORMAL_GESTURE_MASK = 0,

    /**
     * 屏蔽子组件的手势，包括子组件上系统内置的手势。
     */
    IGNORE_INTERNAL_GESTURE_MASK
} ArkUI_GestureMask;

/**
 * @brief 定义手势类型。
 *
 * @since 12
 */
typedef enum {
    /**
     * 敲击手势。
     */
    TAP_GESTURE = 0,

    /**
     * 长按手势。
     */
    LONG_PRESS_GESTURE,

    /**
     * 滑动手势。
     */
    PAN_GESTURE,

    /**
     * 捏合手势。
     */
    PINCH_GESTURE,

    /**
     * 旋转手势。
     */
    ROTATION_GESTURE,

    /**
     * 快滑手势。
     */
    SWIPE_GESTURE,

    /**
     * 手势组合。
     */
    GROUP_GESTURE,

    /**
     * 通过onClick注册的点击手势。
     * @since 20
     */
    CLICK_GESTURE,

    /**
     * 用于拖放的拖拽手势。
     * @since 20
     */
    DRAG_DROP
} ArkUI_GestureRecognizerType;

/**
 * @brief 定义手势打断结果。
 *
 * @since 12
 */
typedef enum {
    /**
     * 手势继续。
     */
    GESTURE_INTERRUPT_RESULT_CONTINUE = 0,

    /**
     * 手势打断。
     */
    GESTURE_INTERRUPT_RESULT_REJECT
} ArkUI_GestureInterruptResult;

/**
 * @brief 定义手势识别器状态。
 *
 * @since 12
 */
typedef enum {
    /**
     * 准备状态。
     */
    ARKUI_GESTURE_RECOGNIZER_STATE_READY = 0,

    /**
     * 检测状态。
     */
    ARKUI_GESTURE_RECOGNIZER_STATE_DETECTING = 1,

    /**
     * 等待状态。
     */
    ARKUI_GESTURE_RECOGNIZER_STATE_PENDING = 2,

    /**
     * 阻塞状态。
     */
    ARKUI_GESTURE_RECOGNIZER_STATE_BLOCKED = 3,

    /**
     * 成功状态。
     */
    ARKUI_GESTURE_RECOGNIZER_STATE_SUCCESSFUL = 4,

    /**
     * 失败状态。
     */
    ARKUI_GESTURE_RECOGNIZER_STATE_FAILED = 5
} ArkUI_GestureRecognizerState;

/**
 * @brief 定义手势和事件收集的干预操作类型。
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * @brief 继续正常的手势和事件收集流程。不进行任何干预。
     *
     * @since 26.0.0
     */
    OH_ARKUI_GESTURE_COLLECT_INTERVENTION_CONTINUE = 0,

    /**
     * @brief 丢弃所有待收集的低优先级手势和事件。
     * <br>丢弃的部分包括左侧兄弟节点以及祖先节点（父节点及以上）的手势。
     * <br>仅保留当前节点和更高优先级节点中已收集的手势。
     *
     * @since 26.0.0
     */
    OH_ARKUI_GESTURE_COLLECT_INTERVENTION_DISCARD_LOWER = 1,

    /**
     * @brief 丢弃已经收集到的高优先级手势和事件。
     * <br>会丢弃已收集的右侧兄弟节点和当前节点上的手势。
     * <br>将继续处理低优先级手势的收集流程（左侧兄弟节点和祖先节点）。
     *
     * @since 26.0.0
     */
    OH_ARKUI_GESTURE_COLLECT_INTERVENTION_DISCARD_HIGHER = 2,

    /**
     * @brief 丢弃当前节点自身的手势和事件。
     * <br>当前节点的手势和事件将从手势树中排除。
     * <br>兄弟节点（左侧和右侧）以及祖先节点的手势仍会继续收集。
     *
     * @since 26.0.0
     */
    OH_ARKUI_GESTURE_COLLECT_INTERVENTION_DISCARD_SELF = 3,

    /**
     * @brief 丢弃左侧兄弟节点中待收集的手势和事件。
     * <br>当前节点以及已收集的右侧兄弟节点的手势和事件将被保留。
     * <br>将继续处理父节点以及祖先节点的收集流程。
     *
     * @since 26.0.0
     */
    OH_ARKUI_GESTURE_COLLECT_INTERVENTION_DISCARD_LOWER_PRIORITY_SIBLINGS = 4
} OH_ArkUI_GestureCollectIntervention;

/**
 * @brief 定义手势识别器句柄类型，是ArkUI_GestureRecognizer指针类型的别名封装，用于在ArkUI原生手势接口中表示手势识别器对象。
 *
 * @since 12
 */
typedef ArkUI_GestureRecognizer* ArkUI_GestureRecognizerHandle;

/**
 * @brief 定义手势识别器句柄数组类型，用于表示或传递多个手势识别器句柄，例如获取响应链中的手势识别器集合。
 *
 * @since 12
 */
typedef ArkUI_GestureRecognizerHandle* ArkUI_GestureRecognizerHandleArray;

/**
 * @brief 定义手势事件目标信息类型，用于在手势处理过程中查询手势事件目标对象的滚动开始、滚动结束等状态，主要适用于滚动类容器组件。开发者可通过{@link OH_ArkUI_GetGestureEventTargetInfo}
 * 从手势识别器中获取该对象，并通过目标信息查询接口读取目标状态。
 *
 * @since 12
 */
typedef struct ArkUI_GestureEventTargetInfo ArkUI_GestureEventTargetInfo;

/**
 * @brief 定义并行内部手势事件。该结构体作为{@link setInnerGestureParallelTo}回调函数的参数传递，包含当前内置手势识别器、响应链中的冲突手势识别器和用户自定义数据，
 * 供回调选择需要与当前内置手势并行识别的对象。
 *
 * @since 12
 */
typedef struct ArkUI_ParallelInnerGestureEvent ArkUI_ParallelInnerGestureEvent;

/**
 * @brief 定义手势模块接口集合，包含{@link ArkUI_NativeGestureAPI_1}、{@link ArkUI_NativeGestureAPI_2}结构体中的手势接口及新增手势接口。<br>
 * 该接口集合支持为ArkUI节点设置并行手势事件回调。回调可从响应链中的冲突手势识别器中选择需要与当前手势并行识别的对象。相关事件数据请参见{@link ArkUI_ParallelGestureEvent}。
 *
 * @since 26.0.0
 */
typedef struct ArkUI_ParallelGestureEvent ArkUI_ParallelGestureEvent;

/**
 * @brief 定义触摸识别器。触摸识别器用于表示手势打断或手势收集拦截信息中返回的触摸事件处理对象，可通过相关接口获取其节点句柄或取消触摸事件。具体接口请参见{@link native_gesture.h}。
 *
 * @since 15
 */
typedef struct ArkUI_TouchRecognizer ArkUI_TouchRecognizer;

/**
 * @brief 定义触摸识别器句柄，用于表示触摸识别器对象，并在手势打断、手势收集拦截等接口中传递该对象。
 *
 * @since 15
 */
typedef ArkUI_TouchRecognizer* ArkUI_TouchRecognizerHandle;

/**
 * @brief 定义触摸识别器句柄数组，用于在批量管理多个触摸识别器时使用，例如从手势打断信息中获取多个触摸识别器句柄。
 *
 * @since 15
 */
typedef ArkUI_TouchRecognizerHandle* ArkUI_TouchRecognizerHandleArray;

/**
 * @brief 定义手势识别器析构通知事件的回调函数类型。
 *
 * @param recognizer 手势识别器指针。
 * @param userData 用户自定义数据。
 * @since 12
 */
typedef void (*ArkUI_GestureRecognizerDisposeNotifyCallback)(ArkUI_GestureRecognizer* recognizer, void* userData);

/**
 * @brief 判断是否为系统内置手势。
 *
 * @param event 手势打断回调事件。
 * @return true: 系统内置手势；<br>false: 非系统内置手势。

 * @since 12
 */
bool OH_ArkUI_GestureInterruptInfo_GetSystemFlag(const ArkUI_GestureInterruptInfo* event);

/**
 * @brief 返回被打断的手势指针。
 *
 * @param event 手势打断回调事件。
 * @return 被打断的手势指针。
 * @since 12
 */
ArkUI_GestureRecognizer* OH_ArkUI_GestureInterruptInfo_GetRecognizer(const ArkUI_GestureInterruptInfo* event);

/**
 * @brief 返回打断的手势事件数据。
 *
 * @param event 手势打断回调事件。
 * @return 打断的手势事件数据。
 * @since 12
 */
ArkUI_GestureEvent* OH_ArkUI_GestureInterruptInfo_GetGestureEvent(const ArkUI_GestureInterruptInfo* event);

/**
 * @brief 当要触发的是系统内置手势时，使用该方法可返回该系统内置手势的类型。
 *
 * @param event 手势打断回调事件。
 * @return 要触发的系统内置手势对应的手势类型，取值由{@link ArkUI_GestureRecognizerType}定义。如果当前触发的手势不是系统内置手势，则返回-1。
 * @since 12
 */
int32_t OH_ArkUI_GestureInterruptInfo_GetSystemRecognizerType(const ArkUI_GestureInterruptInfo* event);

/**
 * @brief 从手势打断信息中获取触摸识别器。
 *
 * @param info 指向手势打断信息的指针。
 * @param recognizers 指向触摸识别器数组的指针。
 * @param size 触摸识别器数组的大小。
 * @return 错误码。
 *     <br>返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 表示成功。
 *     <br>返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 表示参数错误。
 * @since 15
 */
int32_t OH_ArkUI_GestureInterruptInfo_GetTouchRecognizers(const ArkUI_GestureInterruptInfo* info,
    ArkUI_TouchRecognizerHandleArray* recognizers, int32_t* size);

/**
 * @brief 获取触摸识别器对应的组件句柄。
 *
 * @param recognizer 触摸识别器的句柄。
 * @return 触摸识别器对应的组件句柄。
 * @since 15
 */
ArkUI_NodeHandle OH_ArkUI_TouchRecognizer_GetNodeHandle(const ArkUI_TouchRecognizerHandle recognizer);

/**
 * @brief 在手势打断回调中向指定的触摸识别器发送取消触摸的事件。适用于嵌套滚动等场景中，当父组件需要接管滚动控制时，可通过此接口取消子组件触摸识别器的触摸事件，避免手势冲突。
 *
 * @param recognizer 触摸识别器的句柄。
 * @param info 指向手势打断信息的指针。
 * @return 错误码。
 *     <br>返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数错误。
 * @since 15
 */
int32_t OH_ArkUI_TouchRecognizer_CancelTouch(ArkUI_TouchRecognizerHandle recognizer, ArkUI_GestureInterruptInfo* info);

/**
 * @brief 返回手势事件类型。
 *
 * @param event 手势事件。
 * @return 手势事件类型。
 * @since 12
 */
ArkUI_GestureEventActionType OH_ArkUI_GestureEvent_GetActionType(const ArkUI_GestureEvent* event);

/**
 * @brief 返回手势的原始输入事件。
 *
 * @param event 手势事件。
 * @return 手势事件的原始输入事件。
 * @since 12
 */
const ArkUI_UIInputEvent* OH_ArkUI_GestureEvent_GetRawInputEvent(const ArkUI_GestureEvent* event);

/**
 * @brief 返回是否为重复触发事件。
 *
 * @param event 手势事件。
 * @return 是否为重复触发事件。1表示为重复触发事件，0表示为非重复触发事件。
 * @since 12
 */
int32_t OH_ArkUI_LongPress_GetRepeatCount(const ArkUI_GestureEvent* event);

/**
 * @brief 滑动手势返回手势主方向速度。
 *
 * @param event 手势事件。
 * @return 当前手势主方向速度，为xy轴方向速度的平方和的算术平方根，单位px/s。
 * @since 12
 */
float OH_ArkUI_PanGesture_GetVelocity(const ArkUI_GestureEvent* event);

/**
 * @brief 滑动手势返回当前手势的x轴方向速度。
 *
 * @param event 手势事件。
 * @return 当前手势的x轴方向速度，单位px/s。
 * @since 12
 */
float OH_ArkUI_PanGesture_GetVelocityX(const ArkUI_GestureEvent* event);

/**
 * @brief 滑动手势返回当前手势的y轴方向速度。
 *
 * @param event 手势事件。
 * @return 当前手势的y轴方向速度，单位px/s。
 * @since 12
 */
float OH_ArkUI_PanGesture_GetVelocityY(const ArkUI_GestureEvent* event);

/**
 * @brief 滑动手势返回当前手势事件x轴相对偏移量。
 *
 * @param event 手势事件。
 * @return 当前手势事件x轴相对偏移量，单位为px。
 * @since 12
 */
float OH_ArkUI_PanGesture_GetOffsetX(const ArkUI_GestureEvent* event);

/**
 * @brief 滑动手势返回当前手势事件y轴相对偏移量。
 *
 * @param event 手势事件。
 * @return 当前手势事件y轴相对偏移量，单位为px。
 * @since 12
 */
float OH_ArkUI_PanGesture_GetOffsetY(const ArkUI_GestureEvent* event);

/**
 * @brief 快滑手势返回当前手势事件角度信息，即手指滑动的瞬时方向与水平正方向的夹角。以水平正方向为基准，滑动方向位于水平正方向顺时针侧时，角度范围为0到180度；位于水平正方向逆时针侧时，角度范围为0到-180度。
 *
 * @param event 手势事件。
 * @return 快滑手势的角度，即手指滑动的瞬时方向与水平正方向的夹角，单位为deg。
 * @since 12
 */
float OH_ArkUI_SwipeGesture_GetAngle(const ArkUI_GestureEvent* event);

/**
 * @brief 快滑手势场景中所有手指滑动平均速度。
 *
 * @param event 手势事件。
 * @return 快滑手势速度，即所有手指滑动的平均速度，单位为px/s。
 * @since 12
 */
float OH_ArkUI_SwipeGesture_GetVelocity(const ArkUI_GestureEvent* event);

/**
 * @brief 旋转手势返回当前手势事件角度信息。
 *
 * @param event 手势事件。
 * @return 旋转角度。单位为deg。
 * @since 12
 */
float OH_ArkUI_RotationGesture_GetAngle(const ArkUI_GestureEvent* event);

/**
 * @brief 捏合手势返回当前手势事件缩放信息。
 *
 * @param event 手势事件。
 * @return 捏合手势的缩放比例，值大于1表示放大，小于1表示缩小。
 * @since 12
 */
float OH_ArkUI_PinchGesture_GetScale(const ArkUI_GestureEvent* event);

/**
 * @brief 捏合手势中心点相对于当前组件元素左上角x轴坐标。
 *
 * @param event 手势事件。
 * @return 捏合手势中心点相对于当前组件元素左上角x轴坐标，单位为px。
 * @since 12
 */
float OH_ArkUI_PinchGesture_GetCenterX(const ArkUI_GestureEvent* event);

/**
 * @brief 捏合手势中心点相对于当前组件元素左上角y轴坐标。
 *
 * @param event 手势事件。
 * @return 捏合手势中心点相对于当前组件元素左上角y轴坐标，单位为px。
 * @since 12
 */
float OH_ArkUI_PinchGesture_GetCenterY(const ArkUI_GestureEvent* event);

/**
 * @brief 获取绑定该手势的ArkUI组件。
 *
 * @param event 手势事件。
 * @return 绑定该手势的ArkUI组件。若返回Null，则表示event是无效值。
 * @since 12
 */
ArkUI_NodeHandle OH_ArkUI_GestureEvent_GetNode(const ArkUI_GestureEvent* event);

/**
 * @brief 获取手势响应链的信息。
 *
 * @param event 手势打断回调事件。
 * @param responseChain 响应链组件上的手势识别器。
 * @param count 响应链组件上的手势识别器的数量。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} - 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} - 参数错误。
 * @since 12
 */
int32_t OH_ArkUI_GetResponseRecognizersFromInterruptInfo(const ArkUI_GestureInterruptInfo* event,
    ArkUI_GestureRecognizerHandleArray* responseChain, int32_t* count);

/**
 * @brief 设置手势识别器的使能状态。
 *
 * @param recognizer 手势识别器指针。
 * @param enabled 使能状态。true表示使能，false表示禁用。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} - 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} - 参数错误。
 * @since 12
 */
int32_t OH_ArkUI_SetGestureRecognizerEnabled(ArkUI_GestureRecognizer* recognizer, bool enabled);

/**
 * @brief 设置是否严格检查触摸手指数量的标志。实际触摸手指数量不等于设置的手指数量的时候，该手势识别不成功。
 *
 * @param recognizer 手势识别器指针。
 * @param limitFingerCount 表示严格检查触摸手指数量的状态。true表示检查手指数量，false表示不检查手指数量。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} - 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} - 参数错误。
 * @since 15
 */
int32_t OH_ArkUI_SetGestureRecognizerLimitFingerCount(ArkUI_GestureRecognizer* recognizer, bool limitFingerCount);

/**
 * @brief 获取手势识别器的使能状态。
 *
 * @param recognizer 手势识别器指针。
 * @return true - 使能。
 *     <br>false - 禁用。
 * @since 12
 */
bool OH_ArkUI_GetGestureRecognizerEnabled(ArkUI_GestureRecognizer* recognizer);

/**
 * @brief 获取手势识别器的状态。
 *
 * @param recognizer 手势识别器指针。
 * @param state 手势识别器的状态。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} - 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} - 参数错误。
 * @since 12
 */
int32_t OH_ArkUI_GetGestureRecognizerState(ArkUI_GestureRecognizer* recognizer, ArkUI_GestureRecognizerState* state);

/**
 * @brief 获取手势事件目标信息。
 *
 * @param recognizer 手势识别器指针。
 * @param info 手势事件目标信息。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} - 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} - 参数错误。
 * @since 12
 */
int32_t OH_ArkUI_GetGestureEventTargetInfo(ArkUI_GestureRecognizer* recognizer, ArkUI_GestureEventTargetInfo** info);

/**
 * @brief 当前滚动类容器组件是否在顶部。
 *
 * @param info 手势事件目标信息。
 * @param ret 当前滚动类容器组件是否在顶部。true表示在顶部，false表示不在顶部。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} - 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} - 参数错误。
 *     <br>{@link ARKUI_ERROR_CODE_NON_SCROLLABLE_CONTAINER} - 非滚动类容器。
 * @since 12
 */
int32_t OH_ArkUI_GestureEventTargetInfo_IsScrollBegin(ArkUI_GestureEventTargetInfo* info, bool* ret);

/**
 * @brief 当前滚动类容器组件是否在底部。
 *
 * @param info 手势事件目标信息。
 * @param ret 当前滚动类容器组件是否在底部。true表示在底部，false表示不在底部。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} - 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} - 参数错误。
 *     <br>{@link ARKUI_ERROR_CODE_NON_SCROLLABLE_CONTAINER} - 非滚动类容器。
 * @since 12
 */
int32_t OH_ArkUI_GestureEventTargetInfo_IsScrollEnd(ArkUI_GestureEventTargetInfo* info, bool* ret);

/**
 * @brief 获取滑动手势的滑动方向。建议优先使用OH_ArkUI_GetGestureParam_DirectMask（API version 18），该接口为统一参数查询接口；
 * OH_ArkUI_GetPanGestureDirectionMask为早期接口（API version 12），功能与OH_ArkUI_GetGestureParam_DirectMask相同。
 *
 * @param recognizer 手势识别器指针。
 * @param directionMask 滑动手势的滑动方向。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} - 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} - 参数错误。
 * @since 12
 */
int32_t OH_ArkUI_GetPanGestureDirectionMask(ArkUI_GestureRecognizer* recognizer,
    ArkUI_GestureDirectionMask* directionMask);

/**
 * @brief 当前手势是否为系统内置手势。
 *
 * @param recognizer 手势识别器指针。
 * @return true - 是系统内置手势。
 *     <br>false - 不是系统内置手势。
 * @since 12
 */
bool OH_ArkUI_IsBuiltInGesture(ArkUI_GestureRecognizer* recognizer);

/**
 * @brief 获取手势识别器的标记。
 *
 * @param recognizer 手势识别器指针。
 * @param buffer 存储区。
 * @param bufferSize buffer缓冲区的大小，用于限制可写入的手势识别器标记字符串长度。
 * @param result 拷贝的字符串长度。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} - 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} - 参数错误。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH} - 存储区大小不足。
 * @since 12
 */
int32_t OH_ArkUI_GetGestureTag(ArkUI_GestureRecognizer* recognizer, char* buffer, int32_t bufferSize, int32_t* result);

/**
 * @brief 获取手势识别器绑定的组件的ID（字符串形式，即开发者在ArkUI组件上设置的nodeId属性值）。如需获取系统自动分配的整数形式唯一标识，请使用OH_ArkUI_GetGestureBindNodeUniqueId。
 *
 * @param recognizer 手势识别器指针。
 * @param nodeId 组件的ID。
 * @param size nodeId缓冲区的大小，用于限制可写入的组件ID字符串长度。
 * @param result 拷贝的字符串长度。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} - 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} - 参数错误。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH} - 存储区大小不足。
 * @since 12
 */
int32_t OH_ArkUI_GetGestureBindNodeId(ArkUI_GestureRecognizer* recognizer, char* nodeId, int32_t size,
    int32_t* result);

/**
 * @brief 当前手势识别器是否有效。
 *
 * @param recognizer 手势识别器指针。
 * @return true - 手势识别器有效。
 *     <br>false - 手势识别器无效。
 * @since 12
 */
bool OH_ArkUI_IsGestureRecognizerValid(ArkUI_GestureRecognizer* recognizer);

/**
 * @brief 获取并行内置手势事件中的用户自定义数据。
 *
 * @param event 并行内置手势事件。
 * @return 用户自定义数据的指针。
 * @since 12
 */
void* OH_ArkUI_ParallelInnerGestureEvent_GetUserData(ArkUI_ParallelInnerGestureEvent* event);

/**
 * @brief 获取并行内置手势事件中的当前手势识别器。
 *
 * @param event 并行内置手势事件。
 * @return 当前手势识别器的指针。
 * @since 12
 */
ArkUI_GestureRecognizer* OH_ArkUI_ParallelInnerGestureEvent_GetCurrentRecognizer(
    ArkUI_ParallelInnerGestureEvent* event);

/**
 * @brief 获取并行内置手势事件中的冲突的手势识别器。
 *
 * @param event 并行内置手势事件。
 * @param array 冲突的手势识别器数组。
 * @param size 冲突的手势识别器数组的大小。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} - 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} - 参数错误。
 * @since 12
 */
int32_t OH_ArkUI_ParallelInnerGestureEvent_GetConflictRecognizers(ArkUI_ParallelInnerGestureEvent* event,
    ArkUI_GestureRecognizerHandleArray* array, int32_t* size);

/**
 * @brief 设置手势识别器对象析构通知回调函数。
 *
 * @param recognizer 手势识别器指针。
 * @param callback 手势识别器对象析构通知回调函数。
 * @param userData 用户自定义数据，会在手势识别器对象析构通知回调callback中透传给调用方。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} - 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} - 参数错误。
 * @since 12
 */
int32_t OH_ArkUI_SetArkUIGestureRecognizerDisposeNotify(ArkUI_GestureRecognizer* recognizer,
    ArkUI_GestureRecognizerDisposeNotifyCallback callback, void* userData);

/**
 * @brief 获取手势识别器的滑动方向。
 *
 * @param recognizer 手势识别器指针。
 * @param directMask 手势识别器的滑动方向。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数错误。
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_DirectMask(
    ArkUI_GestureRecognizer* recognizer, ArkUI_GestureDirectionMask* directMask);

/**
 * @brief 获取手势识别器的手指数。
 *
 * @param recognizer 手势识别器指针。
 * @param finger 手势识别器的手指数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数错误。
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_FingerCount(ArkUI_GestureRecognizer* recognizer, int* finger);

/**
 * @brief 获取手势识别器是否有手指数限制。
 *
 * @param recognizer 手势识别器指针。
 * @param isLimited 手势识别器是否有手指数限制。true表示有手指数限制，false表示没有手指数限制。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数错误。
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_limitFingerCount(ArkUI_GestureRecognizer* recognizer, bool* isLimited);

/**
 * @brief 获取手势识别器是否连续触发事件回调。
 *
 * @param recognizer 手势识别器指针。
 * @param isRepeat 手势识别器是否连续触发事件回调。true表示连续触发，false表示不连续触发。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} 不支持手势识别器类型。
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_repeat(ArkUI_GestureRecognizer* recognizer, bool* isRepeat);

/**
 * @brief 获取手势识别器的手指允许的移动距离范围。
 *
 * @param recognizer 手势识别器指针。
 * @param distance 手势识别器的手指允许的移动距离范围。单位为px。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} 不支持手势识别器类型。
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_distance(ArkUI_GestureRecognizer* recognizer, double* distance);

/**
 * @brief 获取手势识别器的识别滑动的最小速度。
 *
 * @param recognizer 手势识别器指针。
 * @param speed 手势识别器的识别滑动的最小速度。单位为px/s。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} 不支持手势识别器类型。
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_speed(ArkUI_GestureRecognizer* recognizer, double* speed);

/**
 * @brief 获取手势识别器的触发长按的最短时间。
 *
 * @param recognizer 手势识别器指针。
 * @param duration 手势识别器的触发长按的最短时间。单位为ms。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} 不支持手势识别器类型。
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_duration(ArkUI_GestureRecognizer* recognizer, int* duration);

/**
 * @brief 获取手势识别器的旋转手势的最小改变度数。
 *
 * @param recognizer 手势识别器指针。
 * @param angle 手势识别器的旋转手势的最小改变度数。单位为deg。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} 不支持手势识别器类型。
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_angle(ArkUI_GestureRecognizer* recognizer, double* angle);

/**
 * @brief 获取手势识别器的手势移动阈值。
 *
 * @param recognizer 手势识别器指针。
 * @param distanceThresHold Movement threshold.
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} 不支持手势识别器类型。
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_distanceThreshold(ArkUI_GestureRecognizer* recognizer, double* distanceThreshold);

/**
 * @brief 获取长按手势识别器识别的手势的最大移动距离。
 *
 * @param recognizer 手势识别器指针。
 * @param allowableMovement 指向长按手势识别器识别的手势的最大移动距离的指针，单位为px。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数错误。
 *     <br>{@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} 不支持手势识别器类型。
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_LongPressGesture_GetAllowableMovement(
    ArkUI_GestureRecognizer* recognizer, double* allowableMovement);

/**
 * @brief 设置手势最小滑动阈值表，用于需要根据不同输入工具类型配置滑动手势识别阈值的场景。
 *
 * @param recognizer 手势识别器指针。
 * @param size toolTypeArray和distanceArray数组的元素个数，取值需大于0，且需与toolTypeArray和distanceArray的实际元素数一致。
 * @param toolTypeArray 指向输入事件工具类型数组的指针，元素取值为UI_INPUT_EVENT_TOOL_TYPE_XXX；当设置该范围以外的值时，设置不生效。
 * @param distanceArray 指向最小滑动阈值数组的指针，取值范围为(0, +∞)，单位为px。传入0或负数时，设置不生效。distanceArray[i]表示toolTypeArray[i]对应工具类型的最小滑动阈值。
 * @return 错误码。
 *     <br>返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数错误。
 *     <br>返回 {@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} 不支持手势识别器类型。
 * @since 19
 */
ArkUI_ErrorCode OH_ArkUI_PanGesture_SetDistanceMap(
    ArkUI_GestureRecognizer* recognizer, int size, int* toolTypeArray, double* distanceArray);

/**
 * @brief 获取手势识别器的手势移动阈值表。仅支持对通过OH_ArkUI_PanGesture_SetDistanceMap修改过的设备类型的阈值查询。默认滑动阈值可通过查询
 * {@link UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN}类型获得，其他未设置过的类型不会返回对应的滑动阈值。
 *
 * @param recognizer 手势识别器指针。
 * @param toolType 输入事件的工具类型，取值为UI_INPUT_EVENT_TOOL_TYPE_XXX。仅支持对通过OH_ArkUI_PanGesture_SetDistanceMap修改过的设备类型及
 *     {@link UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN}类型的阈值查询，其他未设置过的类型不会返回对应阈值。
 * @param distance 手势识别器的手势移动阈值。单位为px。
 * @return 错误码。
 *     <br>返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数错误。
 *     <br>返回 {@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} 不支持手势识别器类型。
 * @since 19
 */
ArkUI_ErrorCode OH_ArkUI_PanGesture_GetDistanceByToolType(
    ArkUI_GestureRecognizer* recognizer, int toolType, double* distance);

/**
 * @brief 注册一个在所有手势识别器收集完成后执行的回调函数。当用户开始触摸屏幕时，系统会进行命中测试并根据触摸位置收集手势识别器。随后，在处理任何移动事件之前，组件可以使用此接口确定将参与识别并相互竞争的手势识别器。
 *
 * @param node 需要设置手势收集完成回调的节点句柄。
 * @param userData 用户自定义数据，会在touchTestDone回调中作为userData参数透传给调用方。
 * @param touchTestDone 手势收集完成的回调函数。
 *     - event: 手势的基本信息。
 *     - recognizers: 手势识别器数组。
 *     - count: 手势识别器个数。
 * @return 错误码。
 *     <br>返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数错误。
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_SetTouchTestDoneCallback(
    ArkUI_NodeHandle node,
    void* userData,
    void (*touchTestDone)(
        ArkUI_GestureEvent* event,
        ArkUI_GestureRecognizerHandleArray recognizers,
        int32_t count,
        void* userData
    )
);

/**
 * @brief 获取手势中断事件中的用户自定义数据。
 *
 * @param event 是指向手势中断信息的指针。
 * @return 返回指向用户自定义数据的指针。
 * @since 18
 */
void* OH_ArkUI_GestureInterrupter_GetUserData(ArkUI_GestureInterruptInfo* event);

/**
 * @brief 在手指全部抬起前阻止手势识别器参与当前手势识别，适用于需要在手势竞争过程中动态排除指定手势识别器的场景。如果系统已确定该手势识别器的结果（无论成功与否），调用此接口将无效。
 *
 * @param recognizer 手势识别器指针。
 * @return 错误码。
 *     <br>返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数错误。
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_PreventGestureRecognizerBegin(ArkUI_GestureRecognizer* recognizer);

/**
 * @brief 设置长按手势识别器识别的手势的最大移动距离。
 *
 * @param recognizer 手势识别器指针。
 * @param allowableMovement 长按手势识别器识别的手势的最大移动距离。
 *     <br>单位为px。
 *     <br>取值范围：(0, +∞)，设置小于等于0时，按照默认值15处理。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数错误。
 *     <br>{@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} 不支持手势识别器类型。
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_LongPressGesture_SetAllowableMovement(
    ArkUI_GestureRecognizer* recognizer, double allowableMovement);

/**
 * @brief 从手势收集拦截信息中获取手势识别器。
 *
 * @param info 表示指向手势收集拦截信息的指针。
 * @param array 表示响应手势识别器数组的指针。
 * @param size 表示响应手势识别器数组的大小。
 * @return 返回{@link ARKUI_ERROR_CODE_NO_ERROR}表示成功。
 *     <br>返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}表示发生参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_GestureCollectInterceptInfo_GetResponseRecognizers(
    const ArkUI_GestureCollectInterceptInfo* info, ArkUI_GestureRecognizerHandleArray* array, int32_t* size);
/**
 * @brief Defines information about gesture collection interception.
 *
 * @since 26.0.0
 */
typedef struct ArkUI_GestureCollectInterceptInfo ArkUI_GestureCollectInterceptInfo;

/**
 * @brief 从手势收集拦截信息中获取触摸识别器句柄。
 *
 * @param info 表示指向手势收集拦截信息的指针。
 * @param recognizers 表示触摸识别器句柄数组的指针。
 * @param size 表示recognizers数组的大小。
 * @return 返回{@link ARKUI_ERROR_CODE_NO_ERROR}表示成功。
 *     <br>返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}表示发生参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_GestureCollectInterceptInfo_GetTouchRecognizers(const ArkUI_GestureCollectInterceptInfo* info,
    ArkUI_TouchRecognizerHandleArray* recognizers, int32_t* size);

/**
 * @brief 设置手势收集干预模式。
 *
 * @param info 手势收集拦截信息指针。
 * @param intervention 手势收集干预模式，类型为{@link OH_ArkUI_GestureCollectIntervention}。
 * @return 如果成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>参数异常返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_GestureCollectInterceptInfo_SetGestureCollectIntervention(
    ArkUI_GestureCollectInterceptInfo* info, OH_ArkUI_GestureCollectIntervention intervention);

/**
 * @brief 获取与手势识别器绑定的组件唯一ID。
 *
 * @param recognizer 表示指向手势识别器的指针。
 * @param uniqueId 表示与手势识别器绑定的组件唯一ID。
 * @return 返回{@link ARKUI_ERROR_CODE_NO_ERROR}表示成功。
 *     <br>返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}表示发生参数异常。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_GetGestureBindNodeUniqueId(const ArkUI_GestureRecognizer* recognizer, int32_t* uniqueId);

/**
 * @brief 检查当前触摸识别器绑定节点是否为传入组件的后代节点。
 *
 * @param recognizer 表示触摸识别器句柄。
 * @param uniqueId 表示组件的唯一ID，可通过{@link OH_ArkUI_GetGestureBindNodeUniqueId}获取。
 * @return 如果当前触摸识别器绑定节点是传入组件的后代，则返回true，否则返回false。
 * @since 26.0.0
 */
bool OH_ArkUI_TouchRecognizer_IsHostBelongsTo(const ArkUI_TouchRecognizerHandle recognizer, int32_t uniqueId);

/**
 * @brief 检查当前手势识别器绑定节点是否为传入组件的后代节点。
 *
 * @param recognizer 表示指向手势识别器的指针。
 * @param uniqueId 表示组件的唯一ID，可通过{@link OH_ArkUI_GetGestureBindNodeUniqueId}获取。
 * @return 如果当前手势绑定节点是传入组件的后代，则返回true，否则返回false。
 * @since 26.0.0
 */
bool OH_ArkUI_GestureRecognizer_IsHostBelongsTo(const ArkUI_GestureRecognizer* recognizer, int32_t uniqueId);

/**
 * @brief 提供创建敲击、长按、滑动、捏合、旋转、快滑手势及手势组的接口，并支持绑定手势、移除手势、设置手势打断回调和并行内部手势回调，用于配置和管理组件的触控交互识别与事件处理。<br>使用该模块配置手势时，推荐按以下流程操作：
 * 调用{@link createTapGesture}等接口创建手势识别器，调用{@link setGestureEventTarget}注册手势事件回调，再调用{@link addGestureToNode}
 * 将手势识别器绑定至组件节点；不再使用该手势时，调用{@link dispose}释放手势资源，如需先解除节点绑定，可在调用dispose()前调用{@link removeGestureFromNode}。对于手势竞争场景，
 * 可通过手势优先级、屏蔽模式或{@link setGestureInterrupterToNode}配置响应策略；对于组件内部手势与外部自定义手势需要并行识别的场景，可调用
 * {@link setInnerGestureParallelTo}设置并行内部手势事件回调。
 *
 * @since 12
 */
typedef struct {
    /**
     * 结构版本号 = 1。
     */
    int32_t version;

    /**
     * @brief 创建敲击手势。创建成功后返回的手势识别器可通过addGestureToNode()添加到节点；不再使用时，调用dispose()释放资源，释放后不得继续使用该手势识别器。如需先解除节点绑定，可在dispose()
    * 前调用removeGestureFromNode()。
    *
     * @param countNum 识别的连续点击次数，取值范围为大于0的整数。当设置的值小于1时，会被转化为默认值1。
     * @param fingersNum 触发点击的手指数，最小为1指，最大为10指。当设置小于1的值时，按照最小值1处理；当设置大于10的值时，按照最大值10处理。
     * @return Returns the pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createTapGesture)(int32_t countNum, int32_t fingersNum);

    /**
     * @brief 创建长按手势。创建成功后返回的手势识别器可通过addGestureToNode()添加到节点；不再使用时，调用dispose()释放资源，释放后不得继续使用该手势识别器。如需先解除节点绑定，可在dispose()
    * 前调用removeGestureFromNode()。
    *
     * @param fingersNum 触发长按的最少手指数，最小为1指，最大取值为10指。超出取值范围时按照默认值1处理。
     * @param repeatResult 是否连续触发事件回调。
    *     <br>true：连续触发；false：不连续触发。
     * @param durationNum 触发长按的最短时间，单位为毫秒（ms），有效值大于0。当传入的值小于等于0时，按照默认值500ms处理。当组件默认支持可拖拽时，长按触发时间小于500ms时长按事件优先拖拽事件响应；
    *     长按触发时间大于等于500ms时，拖拽事件优先长按事件响应。
     * @return Returns the pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createLongPressGesture)(int32_t fingersNum, bool repeatResult, int32_t durationNum);

    /**
     * @brief 创建滑动手势。与{@link createSwipeGesture}（快滑手势）不同，滑动手势基于最小拖动距离触发，快滑手势基于最小滑动速度触发。
     * 创建成功后返回的手势识别器可通过addGestureToNode()添加到节点；不再使用时，调用dispose()释放资源，释放后不得继续使用该手势识别器。
     * 如需先解除节点绑定，可在dispose()前调用removeGestureFromNode()。
     *
     * @param fingersNum 用于指定触发滑动的最少手指数，最小为1指，最大取值为10指。超出取值范围时按照默认值1处理。
     * @param directions 用于指定触发滑动的手势方向，此枚举值支持逻辑与(&)和逻辑或（\|）运算。可根据业务需要选择方向：GESTURE_DIRECTION_HORIZONTAL适用于只识别水平滑动的场景，
     *     GESTURE_DIRECTION_VERTICAL适用于只识别垂直滑动的场景，GESTURE_DIRECTION_LEFT/RIGHT/UP/DOWN适用于只识别单一方向滑动的场景，
     *     GESTURE_DIRECTION_ALL适用于任意方向均可触发的场景，GESTURE_DIRECTION_NONE表示任何方向都不触发手势事件。
     * @param distanceNum 用于指定触发滑动手势事件的最小拖动距离，取值范围(0, +∞)，单位为px。当设定的值小于等于0时，按默认值5px处理。
     * @return Pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createPanGesture)(
        int32_t fingersNum, ArkUI_GestureDirectionMask directions, double distanceNum);

    /**
     * @brief 创建捏合手势。创建成功后返回的手势识别器可通过addGestureToNode()添加到节点；不再使用时，调用dispose()释放资源，释放后不得继续使用该手势识别器。如需先解除节点绑定，可在dispose()
    * 前调用removeGestureFromNode()。
    *
     * @param fingersNum 触发捏合的最少手指数，最小为2指，最大为5指。超出取值范围时按照默认值2处理。
     * @param distanceNum 最小识别距离，取值范围(0, +∞)，单位为px。当设置识别距离的值小于等于0时，会被转化为默认值5px处理。
     * @return Returns the pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createPinchGesture)(int32_t fingersNum, double distanceNum);

    /**
     * @brief 创建旋转手势。创建成功后返回的手势识别器可通过addGestureToNode()添加到节点；不再使用时，调用dispose()释放资源，释放后不得继续使用该手势识别器。如需先解除节点绑定，可在dispose()
    * 前调用removeGestureFromNode()。
    *
     * @param fingersNum 触发旋转的最少手指数，最小为2指，最大为5指。超出取值范围时按照默认值2处理。
     * @param angleNum 触发旋转手势的最小改变度数，取值范围(0, 360]，单位为deg。默认值：1deg。当传入的值小于等于0或大于360时，会被转化为默认值1。
     * @return Returns the pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createRotationGesture)(int32_t fingersNum, double angleNum);

    /**
     * @brief 创建快滑手势。创建成功后返回的手势识别器可通过addGestureToNode()添加到节点；不再使用时，调用dispose()释放资源，释放后不得继续使用该手势识别器。如需先解除节点绑定，可在dispose()
     * 前调用removeGestureFromNode()。
     *
     * @param fingersNum 触发滑动的最少手指数，最小为1指，最大为10指。超出取值范围时，按照默认值1处理。
     * @param directions 触发快滑手势的滑动方向。可根据需要识别的快滑方向选择：GESTURE_DIRECTION_HORIZONTAL适用于水平快滑场景，
     *     GESTURE_DIRECTION_VERTICAL适用于垂直快滑场景，GESTURE_DIRECTION_LEFT/RIGHT/UP/DOWN适用于只识别指定单一方向快滑的场景，
     *     GESTURE_DIRECTION_ALL适用于任意方向快滑均可触发的场景，GESTURE_DIRECTION_NONE表示任何方向都不触发手势事件。
     * @param speedNum 识别滑动的最小速度，取值范围(0, +∞)，单位px/s。当设置滑动速度的值小于等于0时，会被转化为默认值100px/s。
     * @return Returns the pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createSwipeGesture)(
        int32_t fingersNum, ArkUI_GestureDirectionMask directions, double speedNum);

    /**
     * @brief 创建手势组。创建成功后，可调用addChildGesture()向该手势组添加子手势，再通过addGestureToNode()将手势组绑定到节点；不再使用时可按需调用removeChildGesture()
    * 移除子手势，并调用dispose()释放资源，释放后不得继续使用该手势识别器。如需先解除节点绑定，可在dispose()前调用removeGestureFromNode()。
    *
     * @param gestureMode 手势组模式。SEQUENTIAL_GROUP适用于需要按注册顺序依次识别多个手势的场景；PARALLEL_GROUP适用于多个手势需要同时识别且互不影响的场景；
    *     EXCLUSIVE_GROUP适用于多个手势同时竞争、任一手势识别成功后结束其他识别的互斥场景。
     * @return Returns the pointer to the created gesture group.
     */
    ArkUI_GestureRecognizer* (*createGroupGesture)(ArkUI_GroupGestureMode gestureMode);

    /**
     * @brief 销毁通过createTapGesture()、createLongPressGesture()、createPanGesture()、createPinchGesture()、
    * createRotationGesture()、createSwipeGesture()、createGroupGesture()或createTapGestureWithDistanceThreshold()创建的手势，
    * 释放资源。若手势已通过addGestureToNode()添加到节点，建议先调用removeGestureFromNode()解除节点绑定后再调用dispose()；调用dispose()后不得继续使用该手势指针。
    *
     * @param recognizer Pointer to the gesture to be disposed of.
     */
    void (*dispose)(ArkUI_GestureRecognizer* recognizer);

    /**
     * @brief Adds a gesture to a gesture group.
     *
     * @param group Pointer to the target gesture group.
     * @param child Pointer to the target gesture.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs, for example, attempting to
     *     add a gesture to an object that is not a gesture group.
     */
    int32_t (*addChildGesture)(ArkUI_GestureRecognizer* group, ArkUI_GestureRecognizer* child);

    /**
     * @brief Removes a gesture from a gesture group.
     *
     * @param group Pointer to the target gesture group.
     * @param child Pointer to the target gesture.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*removeChildGesture)(ArkUI_GestureRecognizer* group, ArkUI_GestureRecognizer* child);

    /**
     * @brief Registers a callback for gestures.
     *
     * @param recognizer Pointer to a gesture recognizer.
     * @param actionTypeMask Gesture event types. Multiple callbacks can be registered at once, with the callback event
     *     types distinguished in the callbacks. Example: actionTypeMask = GESTURE_EVENT_ACTION_ACCEPT \|
     *     GESTURE_EVENT_ACTION_UPDATE;
     * @param extraParams Context passed in the **targetReceiver** callback.
     * @param targetReceiver Callback to register for processing the gesture event types. **event** indicates the
     *     gesture callback data.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*setGestureEventTarget)(
        ArkUI_GestureRecognizer* recognizer, ArkUI_GestureEventActionTypeMask actionTypeMask, void* extraParams,
        void (*targetReceiver)(ArkUI_GestureEvent* event, void* extraParams));

    /**
     * @brief Adds a gesture to a UI component.
     *
     * @param node Pointer to the ArkUI component node to which you want to add the gesture.
     * @param recognizer Gesture to be added to the UI component.
     * @param mode Mode of the gesture.
     * @param mask Gesture masking mode.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*addGestureToNode)(
        ArkUI_NodeHandle node, ArkUI_GestureRecognizer* recognizer, ArkUI_GesturePriority mode,
        ArkUI_GestureMask mask);

    /**
     * @brief Removes a gesture from a node.
     *
     * @param node Pointer to the node from which you want to remove the gesture.
     * @param recognizer Gesture to be removed.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*removeGestureFromNode)(ArkUI_NodeHandle node, ArkUI_GestureRecognizer* recognizer);

    /**
     * @brief Sets a gesture interruption callback for a node.
     *
     * @param node Pointer to the ArkUI node for which you want to set a gesture interruption callback.
     * @param interrupter Indicates the gesture interruption callback to set.
     *     <b>info</b> indicates the gesture interruption data. If <b>interrupter</b> returns
     *     <b>GESTURE_INTERRUPT_RESULT_CONTINUE</b>, the gesture recognition process continues. If it returns
     *     <b>GESTURE_INTERRUPT_RESULT_REJECT</b>, the gesture recognition process is paused.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*setGestureInterrupterToNode)(
        ArkUI_NodeHandle node, ArkUI_GestureInterruptResult (*interrupter)(ArkUI_GestureInterruptInfo* info));

    /**
     * @brief 获取手势类别。
    *
     * @param recognizer 手势指针。
     * @return Returns the gesture type.
     */
    ArkUI_GestureRecognizerType (*getGestureType)(ArkUI_GestureRecognizer* recognizer);

    /**
     * @brief Sets the callback function for the parallel internal gesture event.
     *
     * @param node Pointer to the ArkUI node for which you want to set the callback of the parallel internal gesture
     *     event.
     * @param userData Custom data.
     * @param parallelInnerGesture Parallel internal gesture event. **event** returns the data of the parallel internal
     *     gesture event. **parallelInnerGesture** returns the pointer to the gesture recognizer that requires parallel
     *     recognition.
     * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*setInnerGestureParallelTo)(
        ArkUI_NodeHandle node, void* userData, ArkUI_GestureRecognizer* (*parallelInnerGesture)(
            ArkUI_ParallelInnerGestureEvent* event));

    /**
     * @brief 创建带移动范围限制的敲击手势。创建成功后返回的手势识别器可通过addGestureToNode()添加到节点；
     * 不再使用时，调用dispose()释放资源，释放后不得继续使用该手势识别器。如需先解除节点绑定，
     * 可在dispose()前调用removeGestureFromNode()。
     *
     * @param countNum 识别的连续点击次数，取值范围为大于0的整数。当设置的值小于1时，会被转化为默认值1。
     * @param fingersNum 触发点击的手指数，最小为1指，最大为10指。当设置小于1的值时，按照最小值1处理；当设置大于10的值时，按照最大值10处理。
     * @param distanceThreshold 手指允许的移动距离范围，取值范围(0, +∞)，单位为vp。当设置的值小于等于0时，会被转化为默认值无穷大。
     * @return Returns the pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createTapGestureWithDistanceThreshold)(
        int32_t countNum, int32_t fingersNum, double distanceThreshold);
} ArkUI_NativeGestureAPI_1;

/**
 * @brief 定义手势模块接口集合，在{@link ArkUI_NativeGestureAPI_1}的基础上扩展提供设置手势打断事件回调函数的能力，用于在手势识别过程中根据回调结果继续或打断手势。开发者可以通过
 * {@link gestureApi1}访问基础手势接口，配合{@link setGestureInterrupterToNode}处理手势打断。
 *
 * @since 18
 */
typedef struct {
    /**
     * @brief 指向ArkUI_NativeGestureAPI_1结构体的指针。
     *
     */
    ArkUI_NativeGestureAPI_1* gestureApi1;

    /**
     * @brief Sets the callback for gesture interruption events.
     *
     * @param node Pointer to the ArkUI node for which you want to set a gesture interruption callback.
     * @param userData Pointer to user-defined data.
     * @param interrupter Gesture interruption callback to set. <b>info</b> indicates the gesture interruption data.
     *     If <b>interrupter</b> returns <b>GESTURE_INTERRUPT_RESULT_CONTINUE</b>, the gesture recognition process
     *     proceeds
     *     properly. If it returns <b>GESTURE_INTERRUPT_RESULT_REJECT</b>, the gesture recognition process is paused.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*setGestureInterrupterToNode)(
        ArkUI_NodeHandle node, void* userData, ArkUI_GestureInterruptResult (*interrupter)(
            ArkUI_GestureInterruptInfo* info));
} ArkUI_NativeGestureAPI_2;

/**
 * @brief 定义手势模块接口集合，包含{@link ArkUI_NativeGestureAPI_1}、{@link ArkUI_NativeGestureAPI_2}结构体中的手势接口及新增手势接口。<br>
 * 该接口集合支持为ArkUI节点设置并行手势事件回调。回调可从响应链中的冲突手势识别器中选择需要与当前手势并行识别的对象。相关事件数据请参见{@link ArkUI_ParallelGestureEvent}。
 *
 * @since 26.0.0
 */
typedef struct {
    /**
     * @brief 指向ArkUI_NativeGestureAPI_2结构体的指针。
     *
     * @since 26.0.0
     */
    ArkUI_NativeGestureAPI_2* gestureApi2;

    /**
     * @brief Sets the callback function for a parallel gesture event.
     *
     * @param node Pointer to the ArkUI node for which you want to set a parallel gesture event callback.
     * @param userData Pointer to the user-defined data. The caller must ensure the security of the data lifecycle.
     * @param parallelGesture Parallel gesture event. event returns the data of the parallel gesture event. \n
     *     ParallelGesture returns the pointer to the gesture recognizer that needs parallel recognition.
     * @return {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 26.0.0
     */
    ArkUI_ErrorCode (*setGestureParallelTo)(
        ArkUI_NodeHandle node, void* userData, ArkUI_GestureRecognizer* (*parallelGesture)(
            ArkUI_ParallelGestureEvent* event));
} ArkUI_NativeGestureAPI_3;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_GESTURE_H
/** @} */
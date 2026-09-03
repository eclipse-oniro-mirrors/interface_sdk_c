/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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
 * @addtogroup OH_NativeXComponent Native XComponent
 * @{
 *
 * @brief OH_NativeXComponent提供ArkUI XComponent持有的Surface和触摸事件能力。
 * 支持将EGL/OpenGLES渲染输出、媒体数据等自绘内容上屏显示，并实现Native层与ArkUI之间的触摸等事件交互。
 * 适用于游戏/图形渲染、视频播放、相机预览等需要在Native侧进行高性能绘制并与ArkUI联动交互的场景，具体使用请参考Native XComponent。
 *
 * @since 8
 * @version 1.0
 */

/**
 * @file native_interface_xcomponent.h
 *
 * @brief 声明用于访问Native XComponent的API。
 * Native XComponent提供Surface生命周期管理、触摸事件、鼠标事件、按键事件、帧率控制、图像AI分析及无障碍接入等能力，适用于需要在ArkUI中嵌入自渲染内容（如游戏渲染、媒体播放等）的场景。
 * @sample [NativeXComponentSample](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/DocsSample/ArkUISample/NativeXComponentSample)
 * @kit ArkUI
 * @include <ace/xcomponent/native_interface_xcomponent.h>
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 8
 * @version 1.0
 */

#ifndef _NATIVE_INTERFACE_XCOMPONENT_H_
#define _NATIVE_INTERFACE_XCOMPONENT_H_

#include <stdbool.h>
#include <stdint.h>
#ifdef __cplusplus
#include <vector>
#endif

#include "arkui/native_interface_accessibility.h"
#include "arkui/native_type.h"
#include "arkui/ui_input_event.h"

#include "native_xcomponent_key_event.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 代表Native XComponent实例。
 *
 * @since 8
 * @version 1.0
 */
#define OH_NATIVE_XCOMPONENT_OBJ ("__NATIVE_XCOMPONENT_OBJ__")

/**
 * @brief 触摸事件中的可识别的触摸点个数最大值。
 *
 * @since 8
 * @version 1.0
 */
#define OH_NATIVE_XCOMPONENT_MAX_TOUCH_POINTS_NUMBER 10

/** ArkUI XComponent的id最大长度。 */
const uint32_t OH_XCOMPONENT_ID_LEN_MAX = 128;
/** 触摸事件中的可识别的触摸点个数最大值。 */
const uint32_t OH_MAX_TOUCH_POINTS_NUMBER = 10;

/**
 * @brief 枚举API执行结果状态。
 *
 * @since 8
 * @version 1.0
 */
enum {
    /** 成功结果。 */
    OH_NATIVEXCOMPONENT_RESULT_SUCCESS = 0,
    /** 失败结果。表示接口执行失败，可能由以下原因导致：1. XComponent组件尚未完成初始化；2. Surface已被销毁或释放；3. 系统内部错误。请检查XComponent初始化状态和Surface生命周期后重试。 */
    OH_NATIVEXCOMPONENT_RESULT_FAILED = -1,
    /** 无效参数。表示传入的参数为空指针或不符合接口要求，请检查传入参数是否合法。 */
    OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER = -2,
};

/**
 * @brief XComponent图像AI分析状态码。
 *
 * @since 18
 */
typedef enum {
    /** 图像AI分析完成。 */
    ARKUI_XCOMPONENT_AI_ANALYSIS_FINISHED = 0,
    /** 图像AI分析已禁用。 */
    ARKUI_XCOMPONENT_AI_ANALYSIS_DISABLED = 110000,
    /** 设备不支持图像AI分析。 */
    ARKUI_XCOMPONENT_AI_ANALYSIS_UNSUPPORTED = 110001,
    /** 图像AI分析进行中。 */
    ARKUI_XCOMPONENT_AI_ANALYSIS_ONGOING = 110002,
    /** 图像AI分析停止。 */
    ARKUI_XCOMPONENT_AI_ANALYSIS_STOPPED = 110003,
} ArkUI_XComponent_ImageAnalyzerState;

/**
 * @brief 触摸事件类型。
 *
 * @since 8
 */
typedef enum {
    /** 手指按下时触发触摸事件。 */
    OH_NATIVEXCOMPONENT_DOWN = 0,
    /** 手指抬起时触发触摸事件。 */
    OH_NATIVEXCOMPONENT_UP,
    /** 手指按下状态下在屏幕上移动时触发触摸事件。 */
    OH_NATIVEXCOMPONENT_MOVE,
    /** 触摸事件取消时触发事件。 */
    OH_NATIVEXCOMPONENT_CANCEL,
    /** 无效的触摸类型。 */
    OH_NATIVEXCOMPONENT_UNKNOWN,
} OH_NativeXComponent_TouchEventType;

/**
 * @brief 触摸点工具类型。
 *
 * @since 9
 * @version 1.0
 */
typedef enum {
    /** 未识别工具类型。 */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN = 0,
    /** 表示用手指。 */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_FINGER,
    /** 表示用触笔。 */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_PEN,
    /** 表示用橡皮。 */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_RUBBER,
    /** 表示用笔刷。 */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_BRUSH,
    /** 表示用铅笔。 */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_PENCIL,
    /** 表示用喷枪。 */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_AIRBRUSH,
    /** 表示用鼠标。 */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_MOUSE,
    /** 表示用透镜。 */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_LENS,
} OH_NativeXComponent_TouchPointToolType;

/**
 * @brief 事件源类型。
 *
 * @since 9
 * @version 1.0
 */
typedef enum {
    /** 未知的输入源类型。 */
    OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN = 0,
    /** 表示输入源生成鼠标事件。 */
    OH_NATIVEXCOMPONENT_SOURCE_TYPE_MOUSE,
    /** 表示输入源生成一个触摸屏多点触摸事件。 */
    OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHSCREEN,
    /** 表示输入源生成一个触摸板多点触摸事件。 */
    OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHPAD,
    /** 表示输入源生成一个操纵杆事件。 */
    OH_NATIVEXCOMPONENT_SOURCE_TYPE_JOYSTICK,
    /**
     * @brief 表示输入源生成一个键盘事件。
     *
     * @since 10
     * @version 1.0
     */
    OH_NATIVEXCOMPONENT_SOURCE_TYPE_KEYBOARD,
} OH_NativeXComponent_EventSourceType;

/**
 * @brief 鼠标事件动作。
 *
 * @since 9
 * @version 1.0
 */
typedef enum {
    /** 无效鼠标事件。*/
    OH_NATIVEXCOMPONENT_MOUSE_NONE = 0,
    /** 鼠标按键按下时触发鼠标事件。 */
    OH_NATIVEXCOMPONENT_MOUSE_PRESS,
    /** 鼠标按键松开时触发鼠标事件。 */
    OH_NATIVEXCOMPONENT_MOUSE_RELEASE,
    /** 鼠标在屏幕上移动时触发鼠标事件。 */
    OH_NATIVEXCOMPONENT_MOUSE_MOVE,
    /**
     * 鼠标操作被取消时触发鼠标事件。
     * <b>起始版本：</b> 18
     * <b>说明：</b> OH_NATIVEXCOMPONENT_MOUSE_CANCEL表示鼠标事件被取消，通常在以下场景被触发：
     * 1.组件失去焦点：当前持有焦点的XComponent因系统事件（如弹窗打断、应用切换）失去焦点时，会触发该动作。
     * 2.事件中断：鼠标操作过程中发生更高优先级事件（如系统级手势或强制回收事件流），导致当前鼠标操作被强制终止。
     * 3.异常状态退出：如组件销毁、渲染环境异常等场景下，未完成的鼠标事件会被标记为取消。
     *
     * @since 18
     */
    OH_NATIVEXCOMPONENT_MOUSE_CANCEL,
} OH_NativeXComponent_MouseEventAction;

/**
 * @brief 鼠标事件按键。
 *
 * @since 9
 * @version 1.0
 */
typedef enum {
    /** 鼠标无按键操作时触发鼠标事件。 */
    OH_NATIVEXCOMPONENT_NONE_BUTTON = 0,
    /** 按下鼠标左键时触发鼠标事件。 */
    OH_NATIVEXCOMPONENT_LEFT_BUTTON = 0x01,
    /** 按下鼠标右键时触发鼠标事件。 */
    OH_NATIVEXCOMPONENT_RIGHT_BUTTON = 0x02,
    /** 按下鼠标中键时触发鼠标事件。 */
    OH_NATIVEXCOMPONENT_MIDDLE_BUTTON = 0x04,
    /** 按下鼠标左侧后退键时触发鼠标事件。 */
    OH_NATIVEXCOMPONENT_BACK_BUTTON = 0x08,
    /** 按下鼠标左侧前进键时触发鼠标事件。 */
    OH_NATIVEXCOMPONENT_FORWARD_BUTTON = 0x10,
} OH_NativeXComponent_MouseEventButton;

/**
 * @brief 表示触摸事件的源工具类型。
 *
 * @since 10
 * @version 1.0
 */
typedef enum {
    /** 未知的触摸事件的源工具。 */
    OH_NATIVEXCOMPONENT_SOURCETOOL_UNKNOWN = 0,
    /** 表示触摸事件的源工具是手指。 */
    OH_NATIVEXCOMPONENT_SOURCETOOL_FINGER = 1,
    /** 表示触摸事件的源工具是触笔。 */
    OH_NATIVEXCOMPONENT_SOURCETOOL_PEN = 2,
    /** 表示触摸事件的源工具是橡皮擦。 */
    OH_NATIVEXCOMPONENT_SOURCETOOL_RUBBER = 3,
    /** 表示触摸事件的源工具是笔刷。 */
    OH_NATIVEXCOMPONENT_SOURCETOOL_BRUSH = 4,
    /** 表示触摸事件的源工具是铅笔。 */
    OH_NATIVEXCOMPONENT_SOURCETOOL_PENCIL = 5,
    /** 表示触摸事件的源工具是喷枪。 */
    OH_NATIVEXCOMPONENT_SOURCETOOL_AIRBRUSH = 6,
    /** 表示触摸事件的源工具是鼠标。 */
    OH_NATIVEXCOMPONENT_SOURCETOOL_MOUSE = 7,
    /** 表示触摸事件的源工具是透镜。 */
    OH_NATIVEXCOMPONENT_SOURCETOOL_LENS = 8,
    /** 表示触摸事件的源工具是触摸板。 */
    OH_NATIVEXCOMPONENT_SOURCETOOL_TOUCHPAD = 9,
} OH_NativeXComponent_TouchEvent_SourceTool;

/**
 * @brief 历史触摸点。
 * 在触摸事件处理中，系统会记录触摸轨迹中的历史触摸点信息，用于还原高速滑动等场景下的完整触摸轨迹。每个历史触摸点包含该时刻触摸点的坐标、类型、压力、时间戳、倾斜角度等属性，适用于需要分析触摸轨迹、手势识别等场景。
 *
 * @since 10
 * @version 1.0
 */
typedef struct {
    /** 手指的唯一标识符。 */
    int32_t id;
    /** 触摸点相对于XComponent所在应用窗口左上角的x坐标。 */
    float screenX;
    /** 触摸点相对于XComponent所在应用窗口左上角的y坐标。 */
    float screenY;
    /** 触摸点相对于XComponent组件左边缘的x坐标。 */
    float x;
    /** 触摸点相对于XComponent组件上边缘的y坐标。 */
    float y;
    /** 触摸事件的触摸类型。 */
    OH_NativeXComponent_TouchEventType type;
    /** 指垫和屏幕之间的接触面积。 */
    double size;
    /** 当前触摸事件的压力。 */
    float force;
    /** 当前触摸事件的时间戳。触发事件时距离系统启动的时间间隔，单位纳秒。 */
    int64_t timeStamp;
    /** 平面X-Y上的投影与当前触摸事件的Z轴之间的角度。 */
    float titlX;
    /** 当前触摸事件在平面Y-Z和轴Z上的投影之间的角度。 */
    float titlY;
    /** 当前触摸事件的源工具。 */
    OH_NativeXComponent_TouchEvent_SourceTool sourceTool;
} OH_NativeXComponent_HistoricalPoint;

/**
 * @brief 触摸事件中触摸点的信息。
 * 该结构体由系统在触摸事件回调中填充，开发者可通过回调获取各触摸点的状态数据（包括相对于应用窗口和组件的坐标、触摸类型、接触面积、压力大小、时间戳以及按下状态等信息）。适用于需要精确获取和处理多点触控信息的场景。
 *
 * @since 8
 * @version 1.0
 */
typedef struct {
    /** 手指的唯一标识符。 */
    int32_t id;
    /** 触摸点相对于XComponent所在应用窗口左上角的x坐标。 */
    float screenX;
    /** 触摸点相对于XComponent所在应用窗口左上角的y坐标。 */
    float screenY;
    /** 触摸点相对于XComponent组件左边缘的x坐标。 */
    float x;
    /** 触摸点相对于XComponent组件上边缘的y坐标。 */
    float y;
    /** 触摸事件的触摸类型。 */
    OH_NativeXComponent_TouchEventType type;
    /** 指垫和屏幕之间的接触面积。 */
    double size;
    /** 当前触摸事件的压力。 */
    float force;
    /** 当前触摸事件的时间戳。触发事件时距离系统启动的时间间隔，单位纳秒。 */
    int64_t timeStamp;
    /** 当前点是否被按下，按下时为true，离开时为false。 */
    bool isPressed;
} OH_NativeXComponent_TouchPoint;

/**
 * @brief 触摸事件。
 * 当用户在XComponent组件上进行触摸操作时，通过该结构体可获取触摸点的坐标、触摸类型、接触面积、压力、时间戳等信息，适用于需要在Native层处理XComponent触摸交互的场景。
 *
 * @since 8
 * @version 1.0
 */
typedef struct {
    /** 手指的唯一标识符。 */
    int32_t id;
    /** 触摸点相对于XComponent所在应用窗口左上角的x坐标。 */
    float screenX;
    /** 触摸点相对于XComponent所在应用窗口左上角的y坐标。 */
    float screenY;
    /** 触摸点相对于XComponent组件左边缘的x坐标。 */
    float x;
    /** 触摸点相对于XComponent组件上边缘的y坐标。 */
    float y;
    /** 触摸事件的触摸类型。 */
    OH_NativeXComponent_TouchEventType type;
    /** 指垫和屏幕之间的接触面积。 */
    double size;
    /** 当前触摸事件的压力。 */
    float force;
    /** 产生当前触摸事件的设备的ID。 */
    int64_t deviceId;
    /** 当前触摸事件的时间戳。触发事件时距离系统启动的时间间隔，单位纳秒。 */
    int64_t timeStamp;
    /** 当前触摸点的数组。OH_NATIVE_XCOMPONENT_MAX_TOUCH_POINTS_NUMBER的介绍请参考[宏定义](capi-native-interface-xcomponent-h.md#宏定义)。*/
    OH_NativeXComponent_TouchPoint touchPoints[OH_NATIVE_XCOMPONENT_MAX_TOUCH_POINTS_NUMBER];
    /** 当前触摸点的数量，值为1时为单指触摸，大于1时为多指触摸。 */
    uint32_t numPoints;
} OH_NativeXComponent_TouchEvent;

/**
 * @brief 鼠标事件。
 * 用于在XComponent的鼠标事件回调中传递鼠标事件信息，包含触点相对于组件和屏幕的坐标、事件时间戳、鼠标动作及按键信息。
 *
 * @since 9
 * @version 1.0
 */
typedef struct {
    /** 鼠标触点相对于当前组件左上角的x轴坐标。单位：vp。 */
    float x;
    /** 鼠标触点相对于当前组件左上角的y轴坐标。单位：vp。 */
    float y;
    /** 鼠标触点相对于XComponent所在应用屏幕左上角的x轴坐标。单位：vp。 */
    float screenX;
    /** 鼠标触点相对于XComponent所在应用屏幕左上角的y轴坐标。单位：vp。 */
    float screenY;
    /** 当前鼠标事件的时间戳。触发事件时距离系统启动的时间间隔，单位纳秒。 */
    int64_t timestamp;
    /** 当前鼠标事件动作。 */
    OH_NativeXComponent_MouseEventAction action;
    /** 鼠标事件按键。 */
    OH_NativeXComponent_MouseEventButton button;
} OH_NativeXComponent_MouseEvent;

/**
 * @brief OH_NativeXComponent是ArkUI提供的XComponent在Native侧的实例封装。
 * 用于在ArkUI页面中嵌入自绘制渲染内容（如EGL/OpenGL ES/Vulkan渲染表面），并支持Native层与ArkUI层之间的触摸事件、尺寸变化等事件交互。适用于游戏、地图、视频渲染等需要在应用内集成高性能自绘制内容的场景。
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_NativeXComponent OH_NativeXComponent;

/**
 * @brief OH_NativeXComponent_Callback用于注册XComponent的Surface生命周期（创建、改变、销毁）和触摸事件回调。
 * 适用于需要在Native侧感知Surface状态变化并处理用户触摸交互的场景。
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_NativeXComponent_Callback {
    /**
     * @brief 当Surface创建时调用。
     *
     * @param component 表示指向OH_NativeXComponent实例的指针。
     * @param window 表示NativeWindow句柄。
     *         通过XComponent生命周期获取的NativeWindow本身由系统侧持有了一次引用计数，并会在OnSurfaceDestroyed回调触发之后将引用计数减一，
     * 引用计数归零后NativeWindow将被释放。
     *
     * @since 8
     * @version 1.0
     */
    void (*OnSurfaceCreated)(OH_NativeXComponent* component, void* window);

    /**
     * @brief 当Surface尺寸发生改变时调用。
     *
     * @param component 表示指向OH_NativeXComponent实例的指针。
     * @param window 表示NativeWindow句柄。该句柄在Surface尺寸发生变化时传入，开发者可通过该句柄感知Surface的最新状态并更新渲染配置。
     *
     * @since 8
     * @version 1.0
     */
    void (*OnSurfaceChanged)(OH_NativeXComponent* component, void* window);

    /**
     * @brief 当Surface被销毁时调用。
     *
     * @param component 表示指向OH_NativeXComponent实例的指针。
     * @param window 表示NativeWindow句柄。此回调触发后，系统侧持有的NativeWindow引用计数将减一，引用计数归零后NativeWindow将被释放，请勿在此回调之后继续使用该window句柄。
     *
     * @since 8
     * @version 1.0
     */
    void (*OnSurfaceDestroyed)(OH_NativeXComponent* component, void* window);

    /**
     * @brief 当触摸事件被分发时调用，开发者可在此回调中获取触摸事件数据以实现自定义交互逻辑（如手势识别、自定义绘制等）。
     *
     * @param component 表示指向OH_NativeXComponent实例的指针。
     * @param window 表示NativeWindow句柄。
     *         通过XComponent生命周期获取的NativeWindow本身由系统侧持有了一次引用计数，并会在OnSurfaceDestroyed回调触发之后将引用计数减一，
     * 引用计数归零后NativeWindow将被释放。
     *
     * @since 8
     * @version 1.0
     */
    void (*DispatchTouchEvent)(OH_NativeXComponent* component, void* window);
} OH_NativeXComponent_Callback;

/**
 * @brief 提供了鼠标事件和悬停事件的回调注册能力，开发者可通过该回调结构体监听NativeXComponent上的鼠标和手写笔交互行为，适用于需要在Native侧处理指针输入交互的场景。
 * 其中，DispatchMouseEvent侧重鼠标按键按下、释放、移动等组件内的操作行为，DispatchHoverEvent侧重鼠标或手写笔进入/离开组件的悬停状态变化，两者监听维度不同，可按需同时注册。
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_NativeXComponent_MouseEvent_Callback {
    /**
     * @brief 当鼠标事件（例如鼠标按键按下、释放、移动等操作）被触发时调用。
     *
     * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
     * @param window 表示触发鼠标事件时关联的NativeWindow句柄。
     *
     * @since 9
     * @version 1.0
     */
    void (*DispatchMouseEvent)(OH_NativeXComponent* component, void* window);

    /**
     * @brief 当悬停事件被触发时调用。
     * 该函数在鼠标或手写笔进入或离开组件时触发。
     *
     * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
     * @param isHover 表示鼠标或手写笔是否悬停在组件上，进入时为true，离开时为false。
     *
     * @since 9
     * @version 1.0
     */
    void (*DispatchHoverEvent)(OH_NativeXComponent* component, bool isHover);
} OH_NativeXComponent_MouseEvent_Callback;

struct OH_NativeXComponent_KeyEvent;
/**
 * @brief OH_NativeXComponent_KeyEvent用于封装XComponent按键事件的信息，提供按键的键值、动作类型、事件时间戳等关键数据。
 * 适用于Native侧接收和处理ArkUI XComponent按键事件的场景。
 *
 * @since 10
 * @version 1.0
 */
typedef struct OH_NativeXComponent_KeyEvent OH_NativeXComponent_KeyEvent;

/**
 * @brief 定义期望帧率范围，用于设置XComponent渲染时的期望帧率区间，适用于需要对动画或渲染帧率进行精确控制的场景，可帮助在画面流畅度与功耗之间取得平衡。
 *
 * @since 11
 * @version 1.0
 */
typedef struct {
    /** 期望帧率范围最小值。单位为帧/秒。 */
    int32_t min;
    /** 期望帧率范围最大值。单位为帧/秒。 */
    int32_t max;
    /** 期望帧率。单位为帧/秒。 */
    int32_t expected;
} OH_NativeXComponent_ExpectedRateRange;

/**
 * @brief 获取ArkUI XComponent的id。
 *
 * @param component 返回指向{@link OH_NativeXComponent}实例的指针，用于访问和管理XComponent的Native能力。
 * @param id 表示用于保存此{@link OH_NativeXComponent}实例的ID的字符缓冲区。请注意，空终止符将附加到字符缓冲区，因此字符缓冲区的大小应至少比真实id长度大一个单位。
 * 建议字符缓冲区的大小为\[OH_XCOMPONENT_ID_LEN_MAX + 1]。
 * @param size 表示指向id长度的指针，用于接收id的长度信息。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetXComponentId(OH_NativeXComponent* component, char* id, uint64_t* size);

/**
 * @brief 获取ArkUI XComponent持有的Surface的大小。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param window 表示NativeWindow句柄。
 * @param width 表示指向当前Surface宽度的指针。单位：px。
 * @param height 表示指向当前Surface高度的指针。单位：px。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetXComponentSize(
    OH_NativeXComponent* component, const void* window, uint64_t* width, uint64_t* height);

/**
 * @brief 获取ArkUI XComponent持有的Surface相对其父组件左顶点的偏移量。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param window 表示NativeWindow句柄。
 * @param x 表示指向当前Surface相对于XComponent父组件左顶点x坐标的指针。单位：vp。
 * @param y 表示指向当前Surface相对于XComponent父组件左顶点y坐标的指针。单位：vp。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetXComponentOffset(
    OH_NativeXComponent* component, const void* window, double* x, double* y);

/**
 * @brief 获取ArkUI XComponent调度的触摸事件。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param window 表示NativeWindow句柄。
 * @param touchEvent 表示指向当前触摸事件的指针。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchEvent(
    OH_NativeXComponent* component, const void* window, OH_NativeXComponent_TouchEvent* touchEvent);

/**
 * @brief 获取ArkUI XComponent触摸点工具类型。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param pointIndex 表示触摸点的索引。取值范围为[0, OH_NATIVE_XCOMPONENT_MAX_TOUCH_POINTS_NUMBER-1]，超出范围将返回参数错误。
 * @param toolType 表示指向工具类型的指针。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointToolType(OH_NativeXComponent* component, uint32_t pointIndex,
    OH_NativeXComponent_TouchPointToolType* toolType);

/**
 * @brief 获取ArkUI XComponent触摸点倾斜与X轴角度。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param pointIndex 表示触摸点的索引，取值范围[0, 触摸事件中触摸点数量-1]。传入无效索引时返回OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER。
 * @param tiltX 表示指向触摸点沿X轴倾斜角度的指针。取值范围为[-90, 90]，单位：度。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointTiltX(OH_NativeXComponent* component, uint32_t pointIndex, float* tiltX);

/**
 * @brief 获取ArkUI XComponent触摸点倾斜与Y轴角度。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param pointIndex 表示触摸点的索引，取值范围[0, 触摸事件中触摸点数量-1]。传入无效索引时返回OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER。
 * @param tiltY 表示指向触摸点沿Y轴倾斜角度的指针。取值范围为[-90, 90]，单位：度。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointTiltY(OH_NativeXComponent* component, uint32_t pointIndex, float* tiltY);

/**
 * @brief 获取ArkUI XComponent触摸点相对于应用窗口左上角的X坐标。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param pointIndex 表示触摸点的索引。取值范围[0, 当前触摸事件中的触摸点数量-1]。传入越界索引时返回OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER。
 * @param windowX 表示指向触摸点相对于应用窗口左上角的X坐标的指针。单位：px。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS 获取windowX成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER component是空指针、windowX是空指针或者pointIndex不在有效范围内。
 *
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointWindowX(OH_NativeXComponent* component, uint32_t pointIndex, float* windowX);

/**
 * @brief 获取ArkUI XComponent触摸点相对于应用窗口左上角的Y坐标。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param pointIndex 表示触摸点的索引。取值范围[0, 当前触摸事件中的触摸点数量-1]。传入越界索引时返回OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER。
 * @param windowY 表示指向触摸点相对于应用窗口左上角的Y坐标的指针。单位：px。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS 获取windowY成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER component是空指针、windowY是空指针或者pointIndex不在有效范围内。
 *
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointWindowY(OH_NativeXComponent* component, uint32_t pointIndex, float* windowY);

/**
 * @brief 获取ArkUI XComponent触摸点相对于应用所在屏幕左上角的X坐标。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param pointIndex 表示触摸点的索引。
 * @param displayX 表示指向触摸点相对于应用所在屏幕左上角的X坐标的指针。单位：px。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS 获取displayX成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER component是空指针或displayX是空指针。
 *
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointDisplayX(OH_NativeXComponent* component, uint32_t pointIndex, float* displayX);

/**
 * @brief 获取ArkUI XComponent触摸点相对于应用所在屏幕左上角的Y坐标。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param pointIndex 表示触摸点的索引。
 * @param displayY 表示指向触摸点相对于应用所在屏幕左上角的Y坐标的指针。单位：px。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS 获取displayY成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER component是空指针或displayY是空指针。
 *
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointDisplayY(OH_NativeXComponent* component, uint32_t pointIndex, float* displayY);

/**
 * @brief 获取当前XComponent触摸事件的历史点信息。
 * 由于部分输入设备上报触点的频率非常高（最高可达每1 ms上报一次），而对输入事件的响应通常是为了使UI界面发生变化以响应用户操作。如果按照触点上报的频率将触摸事件高频率上报给应用，大多会造成冗余。
 * 因此，触摸事件在一帧内只会上报一次给应用。在当前帧内上报的触点均作为历史点保存，如果应用需要直接处理这些数据，可调用该接口获取历史点信息。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param window 表示NativeWindow句柄。
 * @param size 表示当前历史点数组的长度。
 * @param historicalPoints 表示指向当前历史接触点数组的指针。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetHistoricalPoints(OH_NativeXComponent* component, const void* window,
    int32_t* size, OH_NativeXComponent_HistoricalPoint** historicalPoints);

/**
 * @brief 获取ArkUI XComponent调度的鼠标事件。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param window 表示NativeWindow句柄。
 * @param mouseEvent 表示指向当前鼠标事件的指针。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetMouseEvent(
    OH_NativeXComponent* component, const void* window, OH_NativeXComponent_MouseEvent* mouseEvent);

/**
 * @brief 为此{@link OH_NativeXComponent}实例注册回调。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param callback 表示指向Surface生命周期和触摸事件回调的指针。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterCallback(OH_NativeXComponent* component, OH_NativeXComponent_Callback* callback);

/**
 * @brief 为此{@link OH_NativeXComponent}实例注册鼠标事件回调。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param callback 表示指向鼠标事件回调的指针。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterMouseEventCallback(
    OH_NativeXComponent* component, OH_NativeXComponent_MouseEvent_Callback* callback);

/**
 * @brief 提供扩展鼠标事件信息的封装类型，用于在鼠标事件回调中获取基础鼠标事件之外的额外鼠标事件属性，适用于需要处理更丰富鼠标交互信息的应用场景。
 *
 * @since 20
 * @version 1.0
 */
typedef struct OH_NativeXComponent_ExtraMouseEventInfo OH_NativeXComponent_ExtraMouseEventInfo;

/**
 * @brief 从此{@link OH_NativeXComponent}实例中获取扩展的鼠标事件信息。
 * 此接口需在鼠标事件回调（通过OH_NativeXComponent_RegisterMouseEventCallback注册）执行期间调用。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param extraMouseEventInfo 表示指向{@link OH_NativeXComponent_ExtraMouseEventInfo}类型指针的地址。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 20
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetExtraMouseEventInfo(
    OH_NativeXComponent* component, OH_NativeXComponent_ExtraMouseEventInfo** extraMouseEventInfo);

/**
 * @brief 从{@link OH_NativeXComponent_ExtraMouseEventInfo}实例中获取功能键按压状态信息。
 *
 * @param extraMouseEventInfo 表示指向扩展的鼠标事件信息实例的指针。
 * @param keys 表示用于接收功能键按压状态信息的64位无符号整数的地址。每一位对应一个功能键的按压状态（如某比特为1表示对应键被按下），
 * 具体比特位与功能键的对应关系请参考{@link ArkUI_UIInputEvent}中功能键状态位的定义。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 20
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetMouseEventModifierKeyStates(
    OH_NativeXComponent_ExtraMouseEventInfo* extraMouseEventInfo, uint64_t* keys);

/**
 * @brief 为此{@link OH_NativeXComponent}实例注册获焦事件回调。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param window) 表示指向获焦事件回调的指针。- window：表示NativeWindow句柄。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterFocusEventCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window));

/**
 * @brief 为此{@link OH_NativeXComponent}实例注册按键事件回调。
 * 该接口注册的回调无返回值，无法控制按键事件是否继续分发。如需拦截按键事件，请使用OH_NativeXComponent_RegisterKeyEventCallbackWithResult。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param window) 表示指向按键事件回调的指针。- window: 表示NativeWindow句柄。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterKeyEventCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window));

/**
 * @brief 为此{@link OH_NativeXComponent}实例注册失焦事件回调。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param window) 表示指向失焦事件回调的指针。- window: 表示NativeWindow句柄。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterBlurEventCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window));

/**
 * @brief 获取ArkUI XComponent调度的按键事件。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param keyEvent 表示指向当前按键事件指针的指针。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEvent(OH_NativeXComponent* component, OH_NativeXComponent_KeyEvent** keyEvent);

/**
 * @brief 获取传入按键事件的动作。
 *
 * @param keyEvent 表示指向{@link OH_NativeXComponent_KeyEvent}实例的指针。
 * @param action 表示指向按键事件动作的指针。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventAction(
    OH_NativeXComponent_KeyEvent* keyEvent, OH_NativeXComponent_KeyAction* action);

/**
 * @brief 获取传入按键事件的按键码。
 *
 * @param keyEvent 表示指向{@link OH_NativeXComponent_KeyEvent}实例的指针。
 * @param code 表示指向按键事件按键码的指针。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventCode(OH_NativeXComponent_KeyEvent* keyEvent, OH_NativeXComponent_KeyCode* code);

/**
 * @brief 获取传入按键事件的事件源类型。
 *
 * @param keyEvent 表示指向{@link OH_NativeXComponent_KeyEvent}实例的指针。
 * @param sourceType 表示指向按键事件的事件源类型的指针。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventSourceType(
    OH_NativeXComponent_KeyEvent* keyEvent, OH_NativeXComponent_EventSourceType* sourceType);

/**
 * @brief 获取传入按键事件的设备id。
 *
 * @param keyEvent 表示指向{@link OH_NativeXComponent_KeyEvent}实例的指针。
 * @param deviceId 表示指向按键事件设备id的指针。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventDeviceId(OH_NativeXComponent_KeyEvent* keyEvent, int64_t* deviceId);

/**
 * @brief 获取传入按键事件的时间戳。
 *
 * @param keyEvent 表示指向{@link OH_NativeXComponent_KeyEvent}实例的指针。
 * @param timestamp 表示指向按键事件时间戳的指针。单位：纳秒。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventTimestamp(OH_NativeXComponent_KeyEvent* keyEvent, int64_t* timestamp);

/**
 * @brief 从按键事件中获取功能键按压状态信息。
 *
 * @param keyEvent 表示指向按键事件的指针。
 * @param keys 表示用于接收功能键按压状态信息的64位无符号整数的地址。每个bit位对应一个功能键的按压状态，具体bit位与功能键的映射关系请参考{@link ArkUI_UIInputEvent}中功能键状态位的定义。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 20
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventModifierKeyStates(OH_NativeXComponent_KeyEvent* keyEvent, uint64_t* keys);

/**
 * @brief 从按键事件中获取NumLock（小键盘锁定）键的状态信息。
 *
 * @param keyEvent 表示指向按键事件的指针。
 * @param isNumLockOn 表示用于接收NumLock（小键盘锁定）键状态的bool类型变量的地址。true表示小键盘锁定，false表示小键盘解锁。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 20
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventNumLockState(OH_NativeXComponent_KeyEvent* keyEvent, bool* isNumLockOn);

/**
 * @brief 从按键事件中获取CapsLock（大写锁定）键的状态信息。
 *
 * @param keyEvent 表示指向按键事件的指针。
 * @param isCapsLockOn 表示用于接收CapsLock（大写锁定）键状态的bool类型变量的地址。true表示大写处于锁定，false表示大写处于解锁。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 20
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventCapsLockState(OH_NativeXComponent_KeyEvent* keyEvent, bool* isCapsLockOn);

/**
 * @brief 从按键事件中获取ScrollLock（滚动锁定）键的状态信息。
 *
 * @param keyEvent 表示指向按键事件的指针。
 * @param isScrollLockOn 表示用于接收ScrollLock（滚动锁定）键状态的bool类型变量的地址。true表示滚动处于锁定，false表示滚动处于解锁。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 20
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventScrollLockState(OH_NativeXComponent_KeyEvent* keyEvent, bool* isScrollLockOn);

/**
 * @brief 设置期望帧率范围。
 * 本接口适用于通过OH_NativeXComponent指针操作的场景。若使用NativeNode（ArkUI_NodeHandle）创建的XComponent，
 * 请使用OH_ArkUI_XComponent_SetExpectedFrameRateRange接口。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param range 表示指向{@link OH_NativeXComponent_ExpectedRateRange}类型的期望帧率信息对象的指针。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 11
 * @version 1.0
 */
int32_t OH_NativeXComponent_SetExpectedFrameRateRange(
    OH_NativeXComponent* component, OH_NativeXComponent_ExpectedRateRange* range);

/**
 * @brief 为此{@link OH_NativeXComponent}实例注册显示更新回调，并使能每帧回调此函数。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param targetTimestamp) 表示指向显示更新回调的指针。- timestamp: 当前帧到达的时间（单位：ns）。- targetTimestamp: 下一帧预期到达的时间（单位：ns）。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 11
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterOnFrameCallback(OH_NativeXComponent* component,
    void (*callback)(OH_NativeXComponent* component, uint64_t timestamp, uint64_t targetTimestamp));

/**
 * @brief 为此{@link OH_NativeXComponent}实例取消注册回调函数，并关闭每帧回调此函数。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 11
 * @version 1.0
 */
int32_t OH_NativeXComponent_UnregisterOnFrameCallback(OH_NativeXComponent* component);

/**
 * @brief 将通过ArkUI的Native接口创建出来的UI组件挂载到当前XComponent上。
 * > <b>说明：</b>
 * >
 * > 挂载的组件在不再需要时，必须调用OH_NativeXComponent_DetachNativeRootNode进行卸载，避免内存泄漏。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param root 表示指向Native接口创建的组件实例的指针。
 *
 * @return 返回执行的状态代码。
 *         返回 OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         返回 OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 12
 * @deprecated since 20
 */
int32_t OH_NativeXComponent_AttachNativeRootNode(OH_NativeXComponent* component, ArkUI_NodeHandle root);

/**
 * @brief 将ArkUI的Native组件从当前XComponent上卸载。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param root 表示指向Native接口创建的组件实例的指针。
 *
 * @return 返回执行的状态代码。
 *         返回 OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 成功。
 *         返回 OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 参数异常。
 *
 * @since 12
 * @deprecated since 20
 */
int32_t OH_NativeXComponent_DetachNativeRootNode(OH_NativeXComponent* component, ArkUI_NodeHandle root);

/**
 * @brief 为此{@link OH_NativeXComponent}实例注册UI输入事件回调，并使能收到UI输入事件时回调此函数。
 * 当前仅支持轴事件。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param type) 表示指向UI输入事件回调的指针。- event: 表示指向UI输入事件的指针。
 * @param type 表示需要注册回调的UI输入事件类型，当前仅支持轴事件类型。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 参数异常。
 *
 * @since 12
 */
int32_t OH_NativeXComponent_RegisterUIInputEventCallback(
    OH_NativeXComponent *component,
    void (*callback)(OH_NativeXComponent *component, ArkUI_UIInputEvent *event,
                     ArkUI_UIInputEvent_Type type),
    ArkUI_UIInputEvent_Type type);

/**
 * @brief 为此{@link OH_NativeXComponent}实例注册自定义事件拦截回调，并使能在做触摸测试时回调此函数。
 * 通过该回调获取到的事件对象不支持UIInput相关信息操作接口，建议切换为通过注册native node上的NODE_ON_TOUCH_INTERCEPT通用事件来支持。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param event) 表示指向自定义事件拦截回调的指针。- event: 表示指向UI输入事件的指针。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 参数异常。
 *
 * @since 12
 */
int32_t OH_NativeXComponent_RegisterOnTouchInterceptCallback(
    OH_NativeXComponent* component, HitTestMode (*callback)(OH_NativeXComponent* component, ArkUI_UIInputEvent* event));

/**
 * @brief 为此{@link OH_NativeXComponent}实例设置是否需要软键盘。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param needSoftKeyboard 表示此{@link OH_NativeXComponent}实例是否需要软键盘。需要时为true，不需要时为false，默认值为false。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_SetNeedSoftKeyboard(OH_NativeXComponent* component, bool needSoftKeyboard);

/**
 * @brief 为此{@link OH_NativeXComponent}实例注册Surface显示回调，该回调在应用窗口已经从后台回到前台时触发。
 * 对于基于NativeNode（ArkUI_NodeHandle）创建的XComponent，建议使用OH_ArkUI_SurfaceCallback_SetSurfaceShowEvent。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param window) 表示指向Surface显示回调的指针。- window: 表示NativeWindow句柄。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterSurfaceShowCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window));

/**
 * @brief 为此{@link OH_NativeXComponent}实例注册Surface隐藏回调，该回调在应用窗口已经从前台进入后台时触发。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param window) 表示指向Surface隐藏回调的指针。- window: 表示NativeWindow句柄。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 执行成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterSurfaceHideCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window));

/**
 * @brief 获取ArkUI XComponent触摸事件的输入设备类型。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param pointId 表示触摸点的id。仅当传入的id为触发该触摸事件的触点id时，可正确返回输入设备类型，否则返回OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER。
 * @param sourceType 表示指向返回设备类型的指针。
 *
 * @return OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 参数异常。
 *         OH_NATIVEXCOMPONENT_RESULT_FAILED - 其他错误。
 *
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchEventSourceType(
    OH_NativeXComponent* component, int32_t pointId, OH_NativeXComponent_EventSourceType* sourceType);

/**
 * @brief 基于Native接口创建的组件实例获取{@link OH_NativeXComponent}类型的指针。
 *
 * @param node 表示指向Native接口创建的组件实例的指针。
 *
 * @return 表示指向{@link OH_NativeXComponent}实例的指针。
 *
 * @since 12
 * @version 1.0
 */
OH_NativeXComponent* OH_NativeXComponent_GetNativeXComponent(ArkUI_NodeHandle node);

/**
 * @brief 获取ArkUI XComponent无障碍接入句柄指针。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param handle 表示指向{@link ArkUI_AccessibilityProvider}实例指针的指针（即用于接收实例指针的地址）。
 *
 * @return OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 参数异常。
 *         OH_NATIVEXCOMPONENT_RESULT_FAILED - 其他错误。
 *
 * @since 13
 */
int32_t OH_NativeXComponent_GetNativeAccessibilityProvider(
    OH_NativeXComponent* component, ArkUI_AccessibilityProvider** handle);

/**
 * @brief 为此{@link OH_NativeXComponent}实例注册带有返回值的按键事件回调。
 * 通过此接口注册的按键事件回调都必须返回一个结果，即true或false。当返回值为true时，该事件将不会继续分发；当返回值为false时，该事件将按照事件处理流程继续分发。
 *
 * @param component 表示指向{@link OH_NativeXComponent}实例的指针。
 * @param window) 表示指向按键事件回调的指针。- window: 表示NativeWindow句柄。当回调返回值为true时，该事件将不会继续分发；当回调返回值为false时，该事件将按照事件处理流程继续分发。
 *
 * @return 返回执行的状态代码。
 *         OH_NATIVEXCOMPONENT_RESULT_SUCCESS - 回调函数注册成功。
 *         OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER - 传入参数异常。
 *
 * @since 14
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterKeyEventCallbackWithResult(
    OH_NativeXComponent* component, bool (*callback)(OH_NativeXComponent* component, void* window));

/**
 * @brief 为此XComponent组件实例开始图像AI分析，使用前需先使能图像AI分析能力（例如通过XComponent组件的enableAnalyzer属性开启）。
 * - <b>前置条件：</b> 调用此方法前，需先通过XComponent组件的enableAnalyzer属性使能图像AI分析能力（具体参见XComponent图像分析相关配置说明）。
 * - <b>配对调用：</b> 此方法与OH_ArkUI_XComponent_StopImageAnalyzer配对使用，开始分析后应在分析完成或不再需要时调用Stop停止分析。
 * - <b>状态说明：</b> 可通过回调函数返回的ArkUI_XComponent_ImageAnalyzerState获取分析状态（如ARKUI_XCOMPONENT_AI_ANALYSIS_FINISHED、
 * ARKUI_XCOMPONENT_AI_ANALYSIS_ONGOING等）。
 *
 * @param node 表示指向XComponent组件实例的指针。
 * @param userData 表示开发者需要在回调函数执行时获取的数据的指针。
 * @param userData) 表示图像AI分析状态刷新时触发的回调函数。- statusCode: 回调函数的入参之一，表示当前的图像分析状态。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 18
 */
int32_t OH_ArkUI_XComponent_StartImageAnalyzer(ArkUI_NodeHandle node, void* userData,
    void (*callback)(ArkUI_NodeHandle node, ArkUI_XComponent_ImageAnalyzerState statusCode, void* userData));

/**
 * @brief 为此XComponent组件实例停止图像AI分析。
 * 使用前需先使能图像AI分析能力。
 * <b>方法关系（配对调用）：</b> 此方法为OH_ArkUI_XComponent_StartImageAnalyzer的配对方法，需在调用StartImageAnalyzer分析完成或不再需要分析时，
 * 调用此方法停止分析并释放相关资源。
 *
 * @param node 表示指向XComponent组件实例的指针。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 18
 */
int32_t OH_ArkUI_XComponent_StopImageAnalyzer(ArkUI_NodeHandle node);

/**
 * @brief OH_ArkUI_SurfaceHolder用于封装和管理Native XComponent的Surface，提供对底层渲染表面的访问与操作能力。
 * 可通过OH_ArkUI_SurfaceHolder_Create接口创建实例，适用于在Native侧需要进行自定义渲染或与图形/媒体组件对接的场景。
 *
 * @since 19
 */
typedef struct OH_ArkUI_SurfaceHolder OH_ArkUI_SurfaceHolder;

/**
 * @brief 创建XComponent组件的{@link OH_ArkUI_SurfaceHolder}对象。
 *
 * @param node 表示指向Native接口创建的XComponent组件实例的指针。
 *
 * @return 返回被创建的{@link OH_ArkUI_SurfaceHolder}对象的指针。
 *
 * @since 19
 */
OH_ArkUI_SurfaceHolder* OH_ArkUI_SurfaceHolder_Create(ArkUI_NodeHandle node);

/**
 * @brief 销毁{@link OH_ArkUI_SurfaceHolder}对象。
 *
 * @param surfaceHolder 表示指向需要销毁的{@link OH_ArkUI_SurfaceHolder}实例的指针。
 *
 * @since 19
 */
void OH_ArkUI_SurfaceHolder_Dispose(OH_ArkUI_SurfaceHolder* surfaceHolder);

/**
 * @brief 向{@link OH_ArkUI_SurfaceHolder}实例存储自定义数据。
 *
 * @param surfaceHolder 表示指向存储自定义数据的{@link OH_ArkUI_SurfaceHolder}实例的指针。
 * @param userData 表示指向要存储的自定义数据的指针。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 19
 */
int32_t OH_ArkUI_SurfaceHolder_SetUserData(OH_ArkUI_SurfaceHolder* surfaceHolder, void* userData);

/**
 * @brief 获取{@link OH_ArkUI_SurfaceHolder}实例存储的自定义数据。
 *
 * @param surfaceHolder 表示指向存储自定义数据的{@link OH_ArkUI_SurfaceHolder}实例的指针。
 *
 * @return 返回自定义数据。
 *
 * @since 19
 */
void* OH_ArkUI_SurfaceHolder_GetUserData(OH_ArkUI_SurfaceHolder* surfaceHolder);

/**
 * @brief 定义Surface生命周期回调结构体。
 * 当XComponent的Surface创建、销毁、尺寸发生变化时，会触发对应的回调；当应用窗口前后台切换导致Surface显示、隐藏时，会触发对应的回调（该显示、隐藏回调能力自API version 20起支持）。
 * 开发者可在回调中获取Surface指针并执行自定义渲染（如OpenGL ES渲染、Vulkan渲染或视频解码渲染等场景）。
 *
 * @since 19
 */
typedef struct OH_ArkUI_SurfaceCallback OH_ArkUI_SurfaceCallback;

/**
 * @brief 创建{@link OH_ArkUI_SurfaceCallback}对象。
 *
 * @return 返回创建的{@link OH_ArkUI_SurfaceCallback}对象的指针。
 *
 * @since 19
 */
OH_ArkUI_SurfaceCallback* OH_ArkUI_SurfaceCallback_Create();

/**
 * @brief 销毁{@link OH_ArkUI_SurfaceCallback}对象。
 *
 * @param callback 表示指向需要销毁的{@link OH_ArkUI_SurfaceCallback}对象的指针。
 *
 * @since 19
 */
void OH_ArkUI_SurfaceCallback_Dispose(OH_ArkUI_SurfaceCallback* callback);

/**
 * @brief 设置Surface生命周期回调中的创建回调事件。
 *
 * @param callback 表示指向Surface生命周期回调的指针。
 * @param surfaceHolder) 表示声明Surface创建时会触发的回调事件。- surfaceHolder: 表示指向{@link OH_ArkUI_SurfaceHolder}实例的指针。
 *
 * @since 19
 */
void OH_ArkUI_SurfaceCallback_SetSurfaceCreatedEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceCreated)(OH_ArkUI_SurfaceHolder* surfaceHolder));

/**
 * @brief 设置Surface生命周期回调中的大小改变回调事件。
 *
 * @param callback 表示指向Surface生命周期回调的指针。
 * @param height) 表示声明Surface大小改变时会触发的回调事件。- surfaceHolder: 表示指向{@link OH_ArkUI_SurfaceHolder}实例的指针。
 * - width: 表示Surface大小变化后的宽度。单位：px。- height: 表示Surface大小变化后的高度。单位：px。
 *
 * @since 19
 */
void OH_ArkUI_SurfaceCallback_SetSurfaceChangedEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceChanged)(OH_ArkUI_SurfaceHolder* surfaceHolder, uint64_t width, uint64_t height));

/**
 * @brief 设置Surface生命周期回调中的销毁回调事件。
 *
 * @param callback 表示指向Surface生命周期回调的指针。
 * @param surfaceHolder) 表示声明Surface销毁时会触发的回调事件。- surfaceHolder: 表示指向{@link OH_ArkUI_SurfaceHolder}实例的指针。
 *
 * @since 19
 */
void OH_ArkUI_SurfaceCallback_SetSurfaceDestroyedEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceDestroyed)(OH_ArkUI_SurfaceHolder* surfaceHolder));

/**
 * @brief 添加Surface生命周期回调到{@link OH_ArkUI_SurfaceHolder}实例。
 *
 * @param surfaceHolder 表示指向{@link OH_ArkUI_SurfaceHolder}实例的指针。
 * @param callback 表示指向新回调的指针。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 19
 */
int32_t OH_ArkUI_SurfaceHolder_AddSurfaceCallback(
    OH_ArkUI_SurfaceHolder* surfaceHolder,
    OH_ArkUI_SurfaceCallback* callback);

/**
 * @brief 删除{@link OH_ArkUI_SurfaceHolder}实例先前添加的Surface生命周期回调。
 *
 * @param surfaceHolder 表示指向{@link OH_ArkUI_SurfaceHolder}实例的指针。
 * @param callback 表示指向需要删除的回调的指针。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 19
 */
int32_t OH_ArkUI_SurfaceHolder_RemoveSurfaceCallback(
    OH_ArkUI_SurfaceHolder* surfaceHolder,
    OH_ArkUI_SurfaceCallback* callback);

/**
 * @brief 提供封装的NativeWindow实例。
 *
 * @since 19
 */
typedef struct NativeWindow OHNativeWindow;

/**
 * @brief 获取{@link OH_ArkUI_SurfaceHolder}实例关联的NativeWindow。
 *
 * @param surfaceHolder 表示指向{@link OH_ArkUI_SurfaceHolder}实例的指针。
 *
 * @return 返回{@link OH_ArkUI_SurfaceHolder}实例关联的OHNativeWindow。
 *
 * @since 19
 */
OHNativeWindow* OH_ArkUI_XComponent_GetNativeWindow(OH_ArkUI_SurfaceHolder* surfaceHolder);

/**
 * @brief 设置XComponent组件是否需要自动初始化Surface的标志位。
 * 配置依赖：
 * - 当autoInitialize为true（默认值）时，Surface会在组件挂树/下树时自动初始化和销毁，无需手动调用OH_ArkUI_XComponent_Initialize和OH_ArkUI_XComponent_Final
 * ize。
 * - 当autoInitialize设置为false时，开发者必须手动调用OH_ArkUI_XComponent_Initialize初始化Surface，
 * 并在不再使用时调用OH_ArkUI_XComponent_Finalize销毁Surface。
 *
 * @param node 表示指向XComponent组件实例的指针。
 * @param autoInitialize 表示XComponent组件是否需要自动初始化Surface。如果autoInitialize值是true，OnSurfaceCreated回调会在组件挂载到组件树时被触发，
 * OnSurfaceDestroyed回调会在组件从组件树卸载时被触发。false表示组件不需要自动初始化Surface。
 *         autoInitialize默认值是true。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 19
 */
int32_t OH_ArkUI_XComponent_SetAutoInitialize(ArkUI_NodeHandle node, bool autoInitialize);

/**
 * @brief 初始化XComponent组件持有的Surface。
 * 需在调用此接口前，先通过OH_ArkUI_XComponent_SetAutoInitialize()将autoInitialize设置为false，以避免Surface在组件挂树时被自动初始化。
 * 配对调用：
 * - 调用此接口初始化Surface后，必须在Surface不再使用时调用OH_ArkUI_XComponent_Finalize销毁Surface。
 * - 若Surface已经处于初始化状态，再次调用将返回ARKUI_ERROR_CODE_XCOMPONENT_STATE_INVALID。
 * - 可通过OH_ArkUI_XComponent_IsInitialized查询当前初始化状态。
 *
 * @param node 表示指向XComponent组件实例的指针。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *         返回 ARKUI_ERROR_CODE_XCOMPONENT_STATE_INVALID - XComponent持有的Surface已经被初始化。
 *
 * @since 19
 */
int32_t OH_ArkUI_XComponent_Initialize(ArkUI_NodeHandle node);

/**
 * @brief 销毁XComponent组件持有的Surface。
 * 配对调用：
 * - 此接口用于销毁由OH_ArkUI_XComponent_Initialize初始化的Surface，必须在Initialize之后调用。
 * - 若Surface尚未初始化或已被销毁，调用将返回ARKUI_ERROR_CODE_XCOMPONENT_STATE_INVALID。
 *
 * @param node 表示指向XComponent组件实例的指针。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *         返回 ARKUI_ERROR_CODE_XCOMPONENT_STATE_INVALID - XComponent持有的Surface尚未初始化或已经被销毁。
 *
 * @since 19
 */
int32_t OH_ArkUI_XComponent_Finalize(ArkUI_NodeHandle node);

/**
 * @brief 获取XComponent组件是否已经初始化的标志位。
 *
 * @param node 表示指向XComponent组件实例的指针。
 * @param isInitialized 表示XComponent组件是否已经初始化Surface。true表示组件已初始化Surface，false表示组件未初始化Surface。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 19
 */
int32_t OH_ArkUI_XComponent_IsInitialized(ArkUI_NodeHandle node, bool* isInitialized);

/**
 * @brief 为此XComponent组件实例设置期望帧率范围。
 *
 * @param node 表示指向XComponent组件实例的指针。
 * @param range 表示{@link OH_NativeXComponent_ExpectedRateRange}类型的期望帧率信息对象。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 20
 * @version 1.0
 */
int32_t OH_ArkUI_XComponent_SetExpectedFrameRateRange(
    ArkUI_NodeHandle node, OH_NativeXComponent_ExpectedRateRange range);

/**
 * @brief 为此XComponent组件实例注册帧回调函数，并使能每帧回调此函数。
 *
 * @param node 表示指向XComponent组件实例的指针。
 * @param targetTimestamp) 表示执行帧回调函数的指针。- timestamp: 当前帧到达的时间，表示系统启动运行至今的纳秒数（单位：纳秒）。
 * - targetTimestamp: 下一帧预期到达的时间，表示系统启动运行至下一帧预期时刻的纳秒数（单位：纳秒）。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 20
 * @version 1.0
 */
int32_t OH_ArkUI_XComponent_RegisterOnFrameCallback(ArkUI_NodeHandle node,
    void (*callback)(ArkUI_NodeHandle node, uint64_t timestamp, uint64_t targetTimestamp));

/**
 * @brief 为此XComponent组件实例取消注册帧回调函数，并关闭每帧回调此函数。
 *
 * @param node 表示指向XComponent组件实例的指针。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 20
 * @version 1.0
 */
int32_t OH_ArkUI_XComponent_UnregisterOnFrameCallback(ArkUI_NodeHandle node);

/**
 * @brief 为此XComponent组件实例设置是否需要软键盘。
 *
 * @param node 表示指向XComponent组件实例的指针。
 * @param needSoftKeyboard 表示是否需要软键盘。需要时为true，不需要时为false，默认值为false。
 *
 * @return 返回执行的状态代码。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 20
 */
int32_t OH_ArkUI_XComponent_SetNeedSoftKeyboard(ArkUI_NodeHandle node, bool needSoftKeyboard);

/**
 * @brief 基于此XComponent实例创建{@link ArkUI_AccessibilityProvider}实例。
 *
 * @param node 表示指向XComponent组件实例的指针。
 *
 * @return 返回创建的{@link ArkUI_AccessibilityProvider}对象的指针，用于无障碍接入。
 *
 * @since 20
 */
ArkUI_AccessibilityProvider* OH_ArkUI_AccessibilityProvider_Create(ArkUI_NodeHandle node);

/**
 * @brief 销毁由Native接口OH_ArkUI_AccessibilityProvider_Create创建的{@link ArkUI_AccessibilityProvider}实例。
 *
 * @param provider 表示由Native接口OH_ArkUI_AccessibilityProvider_Create创建的{@link ArkUI_AccessibilityProvider}实例。
 *
 * @since 20
 */
void OH_ArkUI_AccessibilityProvider_Dispose(ArkUI_AccessibilityProvider* provider);

/**
 * @brief 为此{@link OH_ArkUI_SurfaceCallback}实例设置Surface显示回调，该回调在应用窗口已经从后台回到前台时触发。
 *
 * @param callback 表示指向{@link OH_ArkUI_SurfaceCallback}实例的指针。
 * @param surfaceHolder) 表示Surface显示回调函数指针。- surfaceHolder: 表示指向{@link OH_ArkUI_SurfaceHolder}实例的指针。
 *
 * @since 20
 */
void OH_ArkUI_SurfaceCallback_SetSurfaceShowEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceShow)(OH_ArkUI_SurfaceHolder* surfaceHolder));

/**
 * @brief 为此{@link OH_ArkUI_SurfaceCallback}实例设置Surface隐藏回调，该回调在应用窗口已经从前台进入后台时触发。
 *
 * @param callback 表示指向{@link OH_ArkUI_SurfaceCallback}实例的指针。
 * @param surfaceHolder) 表示Surface隐藏回调函数指针。- surfaceHolder: 表示指向{@link OH_ArkUI_SurfaceHolder}实例的指针。
 *
 * @since 20
 */
void OH_ArkUI_SurfaceCallback_SetSurfaceHideEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceHide)(OH_ArkUI_SurfaceHolder* surfaceHolder));

/**
 * @brief 定义XComponent组件持有的Surface配置，用于设置XComponent组件持有的Surface在渲染时是否被视为不透明。
 * 适用于对XComponent渲染性能有要求的场景，将Surface设置为不透明可以减少渲染合成开销，提升渲染性能。需要注意的是，仅当Surface实际渲染的内容全部为不透明时才应设置为不透明，否则可能导致渲染异常。
 *
 * @since 22
 */
typedef struct ArkUI_XComponentSurfaceConfig ArkUI_XComponentSurfaceConfig;

/**
 * @brief 创建XComponent组件的{@link ArkUI_XComponentSurfaceConfig}对象。
 *
 * @return 返回创建的{@link ArkUI_XComponentSurfaceConfig}对象的指针。
 *
 * @since 22
 */
ArkUI_XComponentSurfaceConfig* OH_ArkUI_XComponentSurfaceConfig_Create();

/**
 * @brief 销毁{@link ArkUI_XComponentSurfaceConfig}对象。
 *
 * @param config 表示指向需要销毁的{@link ArkUI_XComponentSurfaceConfig}对象的指针。
 *
 * @since 22
 */
void OH_ArkUI_XComponentSurfaceConfig_Dispose(ArkUI_XComponentSurfaceConfig* config);

/**
 * @brief 设置XComponent组件持有的Surface在渲染时是否被视为不透明，无论该Surface是否存在半透明像素。
 *
 * @param config 表示指向{@link ArkUI_XComponentSurfaceConfig}实例的指针。
 * @param isOpaque 表示设置XComponent组件持有的Surface在渲染时是否需要被视为不透明。true表示需要被视为不透明，false表示不需要被视为不透明，默认值为false，
 * 即在渲染时会应用Surface中绘制内容像素的透明度。
 *
 * @since 22
 */
void OH_ArkUI_XComponentSurfaceConfig_SetIsOpaque(ArkUI_XComponentSurfaceConfig* config, bool isOpaque);

/**
 * @brief 为{@link OH_ArkUI_SurfaceHolder}实例设置Surface选项。
 *
 * @param surfaceHolder 表示指向{@link OH_ArkUI_SurfaceHolder}实例的指针。
 * @param config 表示指向{@link ArkUI_XComponentSurfaceConfig}实例的指针。
 *
 * @return 返回执行结果。
 *         返回 ARKUI_ERROR_CODE_NO_ERROR - 执行成功。
 *         返回 ARKUI_ERROR_CODE_PARAM_INVALID - 传入参数异常。
 *
 * @since 22
 */
int32_t OH_ArkUI_SurfaceHolder_SetSurfaceConfig(
    OH_ArkUI_SurfaceHolder *surfaceHolder,
    ArkUI_XComponentSurfaceConfig *config);
#ifdef __cplusplus
};
#endif
#endif // _NATIVE_INTERFACE_XCOMPONENT_H_
/** @} */

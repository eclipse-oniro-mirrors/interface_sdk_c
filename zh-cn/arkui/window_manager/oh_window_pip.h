
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup WindowManager
 * @{
 *
 * @brief Provides abilities of windowManager on the native side, such as picture in picture window.
 *
 * @since 12
 */

/**
 * @file oh_window_pip.h
 *
 * @brief 定义画中画功能的相关接口，包含创建、删除画中画控制器，以及启动、停止画中画等。主要用于视频播放、直播、视频通话或视频会议场景下，以小窗（画中画）模式呈现内容。
 *
 * @kit ArkUI
 * @library libnative_window_manager.so
 * @syscap SystemCapability.Window.SessionManager
 * @since 20
 * @version 1.0
 */
#ifndef OH_WINDOW_PIP_H
#define OH_WINDOW_PIP_H

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Picture in picture config.
 * @since 20
 */
typedef void* PictureInPicture_PipConfig;

/**
 * @brief 画中画模板类型。
 *
 * @since 20
 */
typedef enum {
    /**
     * 表示将要切换为画中画播放的媒体类型是视频，系统依此加载视频播放模板。
     * @since 20
     */
    VIDEO_PLAY = 0,
    /**
     * 表示将要切换为画中画播放的媒体类型是视频通话，系统依此加载视频通话模板。
     * @since 20
     */
    VIDEO_CALL = 1,
    /**
     *表示将要切换为画中画播放的媒体类型是视频会议，系统依此加载视频会议模板。
     * @since 20
     */
    VIDEO_MEETING = 2,

    /**
     * 表示将要切换为画中画播放的媒体类型是直播，系统依此加载直播模板。
     * @since 20
     */
    VIDEO_LIVE = 3,
} PictureInPicture_PipTemplateType;

/**
 * @brief 画中画控制面板的控件组类型。
 *
 * @since 20
 */
typedef enum {
    /**
     * 视频播放模板的视频上一个/下一个控件组。与视频快进/后退控件组为互斥控件组。如添加视频快进/后退控件组，则不可添加该控件组。
     * @since 20
     */
    VIDEO_PLAY_VIDEO_PREVIOUS_NEXT = 101,
    /**
     * 视频播放模板的视频快进/后退控件组。与视频上一个/下一个控件组为互斥控件组。如添加视频上一个/下一个控件组，则不可添加该控件组。
     * @since 20
     */
    VIDEO_PLAY_FAST_FORWARD_BACKWARD = 102,
    /**
     * 视频通话模板的打开/关闭麦克风控件组。
     * @since 20
     */
    VIDEO_CALL_MICROPHONE_SWITCH = 201,
    /**
     * 视频通话模板的挂断控件组。
     * @since 20
     */
    VIDEO_CALL_HANG_UP_BUTTON = 202,
    /**
     * 视频通话模板的打开/关闭摄像头控件组。
     * @since 20
     */
    VIDEO_CALL_CAMERA_SWITCH = 203,
    /**
     * 视频通话模板的静音控件组。
     * @since 20
     */
    VIDEO_CALL_MUTE_SWITCH = 204,
    /**
     * 视频会议模板的挂断控件组。
     * @since 20
     */
    VIDEO_MEETING_HANG_UP_BUTTON = 301,
    /**
     * 视频会议模板的打开/关闭摄像头控件组。
     * @since 20
     */
    VIDEO_MEETING_CAMERA_SWITCH = 302,
    /**
     * 视频会议模板的静音控件组。
     * @since 20
     */
    VIDEO_MEETING_MUTE_SWITCH = 303,
    /**
     * 视频会议模板的打开/关闭麦克风控件组。
     * @since 20
     */
    VIDEO_MEETING_MICROPHONE_SWITCH = 304,
    /**
     * 直播模板的播放/暂停直播控件组。
     * @since 20
     */
    VIDEO_LIVE_VIDEO_PLAY_PAUSE = 401,
    /**
     * 直播模板的静音控件组。
     * @since 20
     */
    VIDEO_LIVE_MUTE_SWITCH = 402,
} PictureInPicture_PipControlGroup;

/**
 * @brief 控制面板控件类型枚举。
 *
 * @since 20
 */
typedef enum {
    /**
     * 播放/暂停控件。
     * @since 20
     */
    VIDEO_PLAY_PAUSE = 0,
    /**
     * 视频上一个控件。
     * @since 20
     */
    VIDEO_PREVIOUS = 1,
    /**
     * 视频下一个控件。
     * @since 20
     */
    VIDEO_NEXT = 2,
    /**
     * 视频快进控件。
     * @since 20
     */
    FAST_FORWARD = 3,
    /**
     * 视频快退控件。
     * @since 20
     */
    FAST_BACKWARD = 4,
    /**
     * 挂断控件。
     * @since 20
     */
    HANG_UP_BUTTON = 5,
    /**
     * 打开/关闭麦克风控件。
     * @since 20
     */
    MICROPHONE_SWITCH = 6,
    /**
     * 打开/关闭摄像头控件。
     * @since 20
     */
    CAMERA_SWITCH = 7,
    /**
     * 打开/关闭静音控件。
     * @since 20
     */
    MUTE_SWITCH = 8,
} PictureInPicture_PipControlType;

/**
 * @brief 控制面板控件状态枚举。
 *
 * @since 20
 */
typedef enum {
    /**
     * 视频播放状态。
     * @since 20
     */
    PLAY = 1,
    /**
     * 视频暂停状态。
     * @since 20
     */
    PAUSE = 0,
    /**
     * 摄像头/麦克风/静音控件的打开状态。
     * @since 20
     */
    OPEN = 1,
    /**
     * 摄像头/麦克风/静音控件的关闭状态。
     * @since 20
     */
    CLOSE = 0,
} PictureInPicture_PipControlStatus;

/**
 * @brief 画中画生命周期状态枚举。
 *
 * @since 20
 */
typedef enum {
    /**
     * 表示画中画将要启动。
     * @since 20
     */
    ABOUT_TO_START = 1,
    /**
     * 表示画中画已经启动。
     * @since 20
     */
    STARTED = 2,
    /**
     * 表示画中画将要停止。
     * @since 20
     */
    ABOUT_TO_STOP = 3,
    /**
     * 表示画中画已经停止。
     * @since 20
     */
    STOPPED = 4,
    /**
     * 表示画中画将从小窗播放恢复到原始播放界面。
     * @since 20
     */
    ABOUT_TO_RESTORE = 5,
    /**
     * 表示画中画生命周期执行过程出现了异常。
     * @since 20
     */
    ERROR = 6,
} PictureInPicture_PipState;

/**
 * @brief 定义画中画窗口创建完成的回调函数。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param requestId 请求Id，表示当前请求拉起画中画窗口的次数。
 * @param surfaceId 画中画内部Xcomponent组件的surfaceId，用于应用自行渲染。
 * @since 20
 */
typedef void (*WebPipStartPipCallback)(uint32_t controllerId, uint8_t requestId, uint64_t surfaceId);

/**
 * @brief 定义画中画窗口的生命周期回调函数。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param state 当前画中画生命周期状态。
 * @param errcode 画中画接口的通用状态码。具体可见{@link WindowManager_ErrorCode}。
 * @since 20
 */
typedef void (*WebPipLifecycleCallback)(uint32_t controllerId, PictureInPicture_PipState state, int32_t errcode);

/**
 * @brief 定义画中画窗口的控件点击事件回调函数。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param controlType 画中画控制面板的控件类型。
 * @param status 画中画控制面板的控件状态。
 * @since 20
 */
typedef void (*WebPipControlEventCallback)(uint32_t controllerId, PictureInPicture_PipControlType controlType,
    PictureInPicture_PipControlStatus status);

/**
 * @brief 定义画中画窗口的尺寸变化回调函数。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param width 画中画窗口宽度，单位为px，该参数为正整数，不大于屏幕宽。
 * @param height 画中画窗口高度，单位为px，该参数为正整数，不大于屏幕高。
 * @param scale 画中画窗口缩放比，显示大小相对于width和height的缩放比，该参数为浮点数，取值范围大于0.0，小于等于1.0。等于1表示画中画窗口的实际显示宽高值与width和height一样大。
 * @since 20
 */
typedef void (*WebPipResizeCallback)(uint32_t controllerId, uint32_t width, uint32_t height, double scale);

/**
 * @brief 创建画中画参数配置器。
 *
 * @param pipConfig 用于接受创建的画中画参数配置器。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * @since 20
 */
int32_t OH_PictureInPicture_CreatePipConfig(PictureInPicture_PipConfig* pipConfig);

/**
 * @brief 销毁画中画参数配置器。
 *
 * @param pipConfig 画中画参数配置器。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * @since 20
 */
int32_t OH_PictureInPicture_DestroyPipConfig(PictureInPicture_PipConfig* pipConfig);

/**
 * @brief Sets the 拉起画中画的主窗口Id。
 *
 * @param pipConfig 画中画参数配置器。
 * @param mainWindowId 拉起画中画的主窗口Id。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipMainWindowId(PictureInPicture_PipConfig pipConfig, uint32_t mainWindowId);

/**
 * @brief 设置画中画模板类型，默认为视频播放。
 *
 * @param pipConfig 画中画参数配置器。
 * @param pipTemplateType 画中画模板类型。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipTemplateType(PictureInPicture_PipConfig pipConfig,
    PictureInPicture_PipTemplateType pipTemplateType);

/**
 * @brief 设置画中画窗口大小，用于计算尺寸比例。
 *
 * @param pipConfig 画中画参数配置器。
 * @param width 原始内容宽度，单位为px，该参数应为正整数。用于确定画中画窗口比例。
 * @param height 原始内容高度，单位为px，该参数应为正整数。用于确定画中画窗口比例。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipRect(PictureInPicture_PipConfig pipConfig, uint32_t width, uint32_t height);

/**
 * @brief 设置画中画控件组，需保证控件组与模板类型匹配。
 *
 * @param pipConfig 画中画参数配置器。
 * @param controlGroup 画中画控制面板的可选控件组列表，应用可以对此进行配置以决定是否显示。应用未配置时，面板显示基础控件（如视频播放控件组的播放/暂停控件）；应用选择配置时，则最多可以选择三个控件。
 * @param controlGroupLength 画中画控件组数量，取值范围为0 ~ 3。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipControlGroup(PictureInPicture_PipConfig pipConfig,
    PictureInPicture_PipControlGroup* controlGroup, uint8_t controlGroupLength);

/**
 * @brief 设置拉起画中画的运行时环境。
 *
 * @param pipConfig 画中画参数配置器。
 * @param env napi的环境指针。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipNapiEnv(PictureInPicture_PipConfig pipConfig, void* env);

/**
 * @brief 创建画中画控制器。
 *
 * @param pipConfig 画中画参数配置器。
 * @param controllerId 用于接收创建画中画控制器的id。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_CreatePip(PictureInPicture_PipConfig pipConfig, uint32_t* controllerId);

/**
 * @brief 删除画中画控制器。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * @since 20
 */
int32_t OH_PictureInPicture_DeletePip(uint32_t controllerId);

/**
 * @brief 开启画中画。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_STATE_ABNORMAL，表示画中画窗口状态异常。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_CREATE_FAILED，表示画中画窗口创建失败。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_REPEATED_OPERATION，表示画中画窗口重复操作。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * @since 20
 */
int32_t OH_PictureInPicture_StartPip(uint32_t controllerId);

/**
 * @brief 关闭画中画。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_DESTROY_FAILED，表示画中画窗口销毁失败。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_STATE_ABNORMAL，表示画中画窗口状态异常。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_REPEATED_OPERATION，表示画中画窗口重复操作。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * @since 20
 */
int32_t OH_PictureInPicture_StopPip(uint32_t controllerId);

/**
 * @brief 当媒体源切换时，向画中画控制器更新媒体源尺寸信息。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param width 表示媒体内容宽度，单位为px，该参数应为正整数。用于更新画中画窗口比例。
 * @param height 表示媒体内容高度，单位为px，该参数应为正整数。用于更新画中画窗口比例。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_UpdatePipContentSize(uint32_t controllerId, uint32_t width, uint32_t height);

/**
 * @brief 更新画中画控制面板控件功能状态。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param controlType 表示画中画控制面板控件类型。目前仅支持VIDEO_PLAY_PAUSE、MICROPHONE_SWITCH、CAMERA_SWITCH和MUTE_SWITCH这几种控件类型，传入其他控件类型无效。
 * @param status 表示画中画控制面板控件状态。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_UpdatePipControlStatus(uint32_t controllerId, PictureInPicture_PipControlType controlType,
    PictureInPicture_PipControlStatus status);

/**
 * @brief 设置控制面板控件使能状态。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param controlType 表示画中画控制面板控件类型。
 * @param enabled 表示画中画控制面板控件使能状态。true表示控件为可使用状态，false则为禁用状态。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipControlEnabled(uint32_t controllerId, PictureInPicture_PipControlType controlType,
    bool enabled);

/**
 * @brief 设置画中画主窗口ID。
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param windowId 表示画中画父窗口Id，为非负整数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 22
 */
int32_t OH_PictureInPicture_SetParentWindowId(uint32_t controllerId, uint32_t windowId);

/**
 * @brief 设置画中画拉起动效开始时的位置和大小，可用于实现一镜到底效果。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param positionX 拉起时画中画窗口相对页面左上角的X坐标，单位为px。
 * @param positionY 拉起时画中画窗口相对页面左上角的Y坐标，单位为px。
 * @param width 拉起时画中画窗口的宽度，该参数值大于0，单位为px。
 * @param height 拉起时画中画窗口的高度，该参数值大于0，单位为px。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_SetPipInitialSurfaceRect(uint32_t controllerId, int32_t positionX, int32_t positionY,
    uint32_t width, uint32_t height);

/**
 * @brief 取消已设置的画中画拉起动效的起始位置和大小。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_UnsetPipInitialSurfaceRect(uint32_t controllerId);

/**
 * @brief 开启画中画窗口创建完成的监听。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param callback 画中画窗口创建完成的回调函数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_RegisterStartPipCallback(uint32_t controllerId, WebPipStartPipCallback callback);

/**
 * @brief 关闭画中画窗口创建完成的监听。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param callback 画中画窗口创建完成的回调函数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterStartPipCallback(uint32_t controllerId, WebPipStartPipCallback callback);

/**
 * @brief 关闭所有画中画窗口创建完成的监听。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterAllStartPipCallbacks(uint32_t controllerId);

/**
 * @brief 开启画中画生命周期状态的监听。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param callback 画中画窗口的生命周期回调函数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_RegisterLifecycleListener(uint32_t controllerId, WebPipLifecycleCallback callback);

/**
 * @brief 关闭画中画生命周期状态的监听。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param callback 画中画窗口的生命周期回调函数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterLifecycleListener(uint32_t controllerId, WebPipLifecycleCallback callback);

/**
 * @brief 关闭所有画中画生命周期状态的监听。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterAllLifecycleListeners(uint32_t controllerId);

/**
 * @brief 开启画中画控制面板控件动作事件的监听。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param callback 画中画窗口的控件点击事件回调函数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_RegisterControlEventListener(uint32_t controllerId, WebPipControlEventCallback callback);

/**
 * @brief 关闭画中画控制面板控件动作事件的监听。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param callback 画中画窗口的控件点击事件回调函数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterControlEventListener(uint32_t controllerId, WebPipControlEventCallback callback);

/**
 * @brief 关闭所有画中画控制面板控件动作事件的监听。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterAllControlEventListeners(uint32_t controllerId);

/**
 * @brief 开启画中画窗口尺寸变化事件的监听。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param callback 画中画窗口尺寸变化的回调函数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_RegisterResizeListener(uint32_t controllerId, WebPipResizeCallback callback);

/**
 * @brief 关闭画中画窗口尺寸变化事件的监听。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @param callback 画中画窗口尺寸变化的回调函数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterResizeListener(uint32_t controllerId, WebPipResizeCallback callback);

/**
 * @brief 关闭所有画中画窗口尺寸变化事件的监听。
 *
 * @param controllerId 画中画控制器Id，为非负整数。
 * @return 返回结果代码。
 * 返回OK，表示函数调用成功。
 * 返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误。
 * 返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示设备不支持画中画。
 * 返回WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR，表示画中画内部错误。
 * @since 20
 */
int32_t OH_PictureInPicture_UnregisterAllResizeListeners(uint32_t controllerId);

/**
 * @brief 设置是否在返回桌面时自动启动画中画，默认不自动拉起。
 *
 * @param controllerId 画中画控制器ID。取值为非负整数。
 * @param enabled 如返回桌面时需自动启动画中画，则该参数配置为true，否则为false。若设置-系统-智慧多窗-自动启动画中画开关为关闭状态，就算该参数配置为true，应用返回桌面时也不会自动启动画中画窗口。
 * @return 返回结果码。 <ul>
 *         <li>{@link OK}函数调用成功。</li>
 *         <li>{@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM}参数错误。可能原因：
 *             找不到controllerId ID对应的画中画控制器。</li>
 *         <li>{@link WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR}pip内部错误。可能原因：
 *             画中画控制器已被销毁。</li>
 *         </ul>
 * @since 26.0.0
 */
int32_t OH_PictureInPicture_SetAutoStartEnabled(uint32_t controllerId, bool enabled);

#ifdef __cplusplus
}
#endif

#endif // OH_WINDOW_PIP_H
/** @} */
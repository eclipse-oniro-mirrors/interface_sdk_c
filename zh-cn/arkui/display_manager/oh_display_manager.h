
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
 * @file oh_display_manager.h
 *
 * @brief The file declares the functions for basic display management. You can call the functions to obtain various
 * information about the default display and listen for display status changes, such as rotation, folding, and
 * unfolding.
 * 
 * @kit ArkUI
 * @library libnative_display_manager.so
 * @syscap SystemCapability.WindowManager.WindowManager.Core
 * @since 12
 * @version 1.0
 */

/**
 * @addtogroup OH_DisplayManager
 * @{
 *
 * @brief Defines the data structures for the C APIs of the display module.
 *
 * @syscap SystemCapability.WindowManager.WindowManager.Core
 * @since 12
 * @version 1.0
 */
#ifndef OH_NATIVE_DISPLAY_MANAGER_H
#define OH_NATIVE_DISPLAY_MANAGER_H
#include "oh_display_info.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取默认屏幕的id号。
 * 
 * @param displayId 默认屏幕的id号，非负整数，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayId(uint64_t *displayId);

/**
 * @brief 获取默认屏幕的宽度。
 * 
 * @param displayWidth 默认屏幕的宽度，单位为px，该参数应为整数，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayWidth(int32_t *displayWidth);

/**
 * @brief 获取默认屏幕的高度。
 * 
 * @param displayHeight 默认屏幕的高度，单位为px，该参数应为整数，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayHeight(int32_t *displayHeight);

/**
 * @brief 获取默认屏幕的顺时针旋转角度。
 * 
 * @param displayRotation 默认屏幕的顺时针旋转角度，具体可见{@link NativeDisplayManager_Rotation}，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayRotation(
    NativeDisplayManager_Rotation *displayRotation);

/**
 * @brief 获取默认屏幕的旋转方向。
 * 
 * @param displayOrientation 屏幕当前显示的方向，具体可见{@link NativeDisplayManager_Orientation}，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayOrientation(
    NativeDisplayManager_Orientation *displayOrientation);

/**
 * @brief 获取默认屏幕的虚拟像素密度。
 * 
 * @param virtualPixels 屏幕的虚拟像素密度，该参数为浮点数，通常与densityPixels相同，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayVirtualPixelRatio(float *virtualPixels);

/**
 * @brief 获取默认屏幕的刷新率。
 * 
 * @param refreshRate 屏幕的刷新率，该参数应为整数，单位为Hz，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayRefreshRate(uint32_t *refreshRate);

/**
 * @brief 获取屏幕的物理像素密度。
 * 
 * @param densityDpi 屏幕的物理像素密度，表示每英寸上的像素点数。该参数为整数，单位为px，实际能取到的值取决于不同设备设置里提供的可选值。此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayDensityDpi(int32_t *densityDpi);

/**
 * @brief 获取屏幕逻辑像素的密度。
 * 
 * @param densityPixels 设备逻辑像素的密度，代表物理像素与逻辑像素的缩放系数，该参数为浮点数，受densityDPI范围限制，取值范围在[0.5，4.0]。一般取值1.0、3.0等，
 *     实际取值取决于不同设备提供的densityDpi。此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayDensityPixels(float *densityPixels);

/**
 * @brief 获取屏幕显示字体的缩放因子。
 * 
 * @param scaledDensity 显示字体的缩放因子，该参数为浮点数，通常与densityPixels相同，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayScaledDensity(float *scaledDensity);

/**
 * @brief 获取屏幕X方向中每英寸屏幕的物理像素值。
 * 
 * @param xDpi X方向中每英寸屏幕的物理像素值，该参数为浮点数，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayDensityXdpi(float *xDpi);

/**
 * @brief 获取Y方向中每英寸屏幕的物理像素值。
 * 
 * @param yDpi 获取Y方向中每英寸屏幕的物理像素值，该参数为浮点数，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayDensityYdpi(float *yDpi);

/**
 * @brief 获取挖孔屏、刘海屏、瀑布屏等不可用屏幕区域信息。
 * 
 * @param cutoutInfo 挖孔屏、刘海屏、瀑布屏等不可用屏幕区域信息，具体可见{@link NativeDisplayManager_CutoutInfo}，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_CreateDefaultDisplayCutoutInfo(
    NativeDisplayManager_CutoutInfo **cutoutInfo);

/**
 * @brief 销毁挖孔屏、刘海屏、瀑布屏等不可用屏幕区域信息。
 * 
 * @param cutoutInfo 销毁通过{@link OH_NativeDisplayManager_CreateDefaultDisplayCutoutInfo}接口获取的挖孔屏、刘海屏、瀑布屏等不可用屏幕区域信息对象，
 *     具体可见{@link NativeDisplayManager_CutoutInfo}。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_DestroyDefaultDisplayCutoutInfo(
    NativeDisplayManager_CutoutInfo *cutoutInfo);

/**
 * @brief 查询设备是否可折叠。
 * 
 * @return 返回查询设备是否可折叠的结果。true表示设备可折叠，false表示设备不可折叠。
 * @since 12
 */
bool OH_NativeDisplayManager_IsFoldable();

/**
 * @brief 获取可折叠设备的显示模式。
 * 
 * @param displayMode 折叠设备当前的显示模式，具体可见{@link NativeDisplayManager_FoldDisplayMode}，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetFoldDisplayMode(
    NativeDisplayManager_FoldDisplayMode *displayMode);

/**
 * @brief 注册屏幕状态变化的回调函数。
 * 
 * @param displayId 屏幕状态发生变化的编号。
 * @since 12
 */
typedef void (*OH_NativeDisplayManager_DisplayChangeCallback)(uint64_t displayId);

/**
 * @brief 注册屏幕状态变化监听（如旋转变化、刷新率、DPI、分辨率等变化）。
 * 
 * @param displayChangeCallback 屏幕状态变化后触发的回调函数，回调函数定义见{@link OH_NativeDisplayManager_DisplayChangeCallback}。
 * @param listenerIndex 注册成功后返回的监听编号，调用取消注册函数{@link OH_NativeDisplayManager_UnregisterDisplayChangeListener}时作为入参使用，
 *     此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_RegisterDisplayChangeListener(
    OH_NativeDisplayManager_DisplayChangeCallback displayChangeCallback, uint32_t *listenerIndex);

/**
 * @brief 取消屏幕状态变化的监听。
 * 
 * @param listenerIndex 调用注册函数{@link OH_NativeDisplayManager_RegisterDisplayChangeListener}时获取到的监听编号。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_UnregisterDisplayChangeListener(uint32_t listenerIndex);

/**
 * @brief 注册屏幕展开、折叠状态变化的回调函数。
 * 
 * @param displayMode 折叠/展开动作执行后屏幕的状态，具体可见{@link NativeDisplayManager_FoldDisplayMode}。
 * @since 12
 */
typedef void (*OH_NativeDisplayManager_FoldDisplayModeChangeCallback)(
    NativeDisplayManager_FoldDisplayMode displayMode);

/**
 * @brief 注册屏幕展开、折叠状态变化的监听。
 * 
 * @param displayModeChangeCallback 屏幕展开和折叠变化后触发的回调函数，回调函数定义见
 *     {@link OH_NativeDisplayManager_FoldDisplayModeChangeCallback}。
 * @param listenerIndex 注册成功后返回的监听编号，调用取消注册函数{@link OH_NativeDisplayManager_UnregisterFoldDisplayModeChangeListener}
 *     时作为入参使用，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_RegisterFoldDisplayModeChangeListener(
    OH_NativeDisplayManager_FoldDisplayModeChangeCallback displayModeChangeCallback, uint32_t *listenerIndex);

/**
 * @brief 取消屏幕展开、折叠状态变化的监听。
 * 
 * @param listenerIndex 调用注册函数{@link OH_NativeDisplayManager_RegisterFoldDisplayModeChangeListener}时获取到的监听编号。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_UnregisterFoldDisplayModeChangeListener(uint32_t listenerIndex);

/**
 * @brief 获取当前所有屏幕信息对象。
 * 
 * @param allDisplays 当前所有的屏幕信息，具体可见{@link NativeDisplayManager_DisplaysInfo}，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 14
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_CreateAllDisplays(
    NativeDisplayManager_DisplaysInfo **allDisplays);

/**
 * @brief 销毁所有屏幕的信息对象。
 * 
 * @param allDisplays 销毁通过{@link OH_NativeDisplayManager_CreateAllDisplays}接口获取的所有的屏幕信息，具体可见
 *     {@link NativeDisplayManager_DisplaysInfo}。
 * @since 14
 */
void OH_NativeDisplayManager_DestroyAllDisplays(NativeDisplayManager_DisplaysInfo *allDisplays);

/**
 * @brief 获取指定屏幕的信息对象。
 * 
 * @param displayId 指定屏幕的id编号，该值为非负整数。
 * @param displayInfo 指定的屏幕信息对象，具体可见{@link NativeDisplayManager_DisplayInfo}，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 14
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_CreateDisplayById(uint32_t displayId,
    NativeDisplayManager_DisplayInfo **displayInfo);

/**
 * @brief 销毁指定屏幕的信息对象。
 * 
 * @param displayInfo 销毁通过{@link OH_NativeDisplayManager_CreateDisplayById}或者
 *     {@link OH_NativeDisplayManager_CreatePrimaryDisplay}接口获取到的屏幕信息，具体可见{@link NativeDisplayManager_DisplayInfo}。
 * @since 14
 */
void OH_NativeDisplayManager_DestroyDisplay(NativeDisplayManager_DisplayInfo *displayInfo);

/**
 * @brief 获取主屏信息对象。除2in1之外的设备获取的是设备自带屏幕的屏幕信息；2in1设备外接屏幕时获取的是当前主屏幕的屏幕信息；2in1设备没有外接屏幕时获取的是自带屏幕的屏幕信息。
 * 
 * @param displayInfo 主屏的屏幕信息对象，具体可见{@link NativeDisplayManager_DisplayInfo}，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 14
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_CreatePrimaryDisplay(
    NativeDisplayManager_DisplayInfo **displayInfo);

/**
 * @brief 注册屏幕可用区域变化的回调函数。
 * 
 * @param displayId 屏幕的id号，非负整数。
 * @since 20
 */
typedef void (*OH_NativeDisplayManager_AvailableAreaChangeCallback)(uint64_t displayId);

/**
 * @brief 注册屏幕可用区域变化监听。
 * 
 * @param availableAreaChangeCallback 屏幕可用区域变化后触发的回调函数，
 *     回调函数定义见{@link OH_NativeDisplayManager_AvailableAreaChangeCallback}。
 * @param listenerIndex 注册成功后返回的监听编号，
 *     调用取消注册函数{@link OH_NativeDisplayManager_UnregisterAvailableAreaChangeListener}时作为入参使用，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_RegisterAvailableAreaChangeListener(
    OH_NativeDisplayManager_AvailableAreaChangeCallback availableAreaChangeCallback, uint32_t *listenerIndex);

/**
 * @brief 取消屏幕可用区域变化的监听。
 * 
 * @param listenerIndex 调用注册函数
 *     {@link OH_NativeDisplayManager_RegisterAvailableAreaChangeListener}时获取到的监听编号。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_UnregisterAvailableAreaChangeListener(uint32_t listenerIndex);

/**
 * @brief 获取屏幕的可用区域。
 * 
 * @param displayId 查询屏幕的id号，非负整数。
 * @param availableArea 屏幕可用区域，具体可见{@link NativeDisplayManager_Rect}，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_CreateAvailableArea(uint64_t displayId, NativeDisplayManager_Rect **availableArea);

/**
 * @brief 销毁屏幕的可用区域。
 * 
 * @param availableArea 销毁通过{@link OH_NativeDisplayManager_CreateAvailableArea}获取的屏幕可用区域，
 *     可用区域定义具体可见{@link NativeDisplayManager_Rect}。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_DestroyAvailableArea(NativeDisplayManager_Rect *availableArea);

/**
 * @brief 注册屏幕连接的回调函数。
 * 
 * @param displayId 新增屏幕的id号，非负整数。
 * @since 20
 */
typedef void (*OH_NativeDisplayManager_DisplayAddCallback)(uint64_t displayId);

/**
 * @brief 注册屏幕连接变化监听（如插入显示器）。
 * 
 * @param displayAddCallback 屏幕连接后触发的回调函数，回调函数定义见{@link OH_NativeDisplayManager_DisplayAddCallback}。
 * @param listenerIndex 注册成功后返回的监听编号，
 *     调用取消注册函数{@link OH_NativeDisplayManager_UnregisterDisplayAddListener}时作为入参使用，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_RegisterDisplayAddListener(
    OH_NativeDisplayManager_DisplayAddCallback displayAddCallback, uint32_t *listenerIndex);

/**
 * @brief 取消屏幕连接的监听。
 * 
 * @param listenerIndex 调用注册函数{@link OH_NativeDisplayManager_RegisterDisplayAddListener}时获取到的监听编号。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_UnregisterDisplayAddListener(uint32_t listenerIndex);

/**
 * @brief 注册屏幕移除的回调函数。
 * 
 * @param displayId 被移除屏幕的id号，非负整数。
 * @since 20
 */
typedef void (*OH_NativeDisplayManager_DisplayRemoveCallback)(uint64_t displayId);

/**
 * @brief 注册屏幕移除变化监听（如移除显示器）。
 * 
 * @param displayRemoveCallback 屏幕移除后触发的回调函数，回调函数定义见{@link OH_NativeDisplayManager_DisplayRemoveCallback}。
 * @param listenerIndex 注册成功后返回的监听编号，
 *     调用取消注册函数{@link OH_NativeDisplayManager_UnregisterDisplayRemoveListener}时作为入参使用，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_RegisterDisplayRemoveListener(
    OH_NativeDisplayManager_DisplayRemoveCallback displayRemoveCallback, uint32_t *listenerIndex);

/**
 * @brief 取消屏幕移除的监听。
 * 
 * @param listenerIndex 调用注册函数{@link OH_NativeDisplayManager_RegisterDisplayRemoveListener}时获取到的监听编号。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_UnregisterDisplayRemoveListener(uint32_t listenerIndex);

/**
 * @brief 获取屏幕的显示模式。
 * 
 * @param displayId 查询屏幕的id号，非负整数。
 * @param sourceMode 屏幕当前的显示模式，具体可见{@link NativeDisplayManager_SourceMode}，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDisplaySourceMode(uint64_t displayId, NativeDisplayManager_SourceMode *sourceMode);

/**
 * @brief 获取屏幕的位置信息，即相对于原点（主屏左上角）的x坐标和y坐标。
 * 
 * @param displayId 查询屏幕的id号，非负整数。
 * @param x 相对于主屏左上角的x方向坐标，单位为px，该参数应为整数，此处作为出参返回。
 * @param y 相对于主屏左上角的y方向坐标，单位为px，该参数应为整数，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 *     当前仅支持主屏幕和扩展屏幕查询屏幕位置信息，其他屏幕查询会返回DISPLAY_MANAGER_ERROR_ILLEGAL_PARAM。
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDisplayPosition(uint64_t displayId, int32_t *x, int32_t *y);
#ifdef __cplusplus
}
#endif

/** @} */
#endif // OH_NATIVE_DISPLAY_MANAGER_H
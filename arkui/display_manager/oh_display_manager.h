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
 * @addtogroup OH_DisplayManager
 * @{
 *
 * @brief Defines the data structures for the C APIs of the display module.
 *
 * @syscap SystemCapability.WindowManager.WindowManager.Core
 * @since 12
 * @version 1.0
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

#ifndef OH_NATIVE_DISPLAY_MANAGER_H
#define OH_NATIVE_DISPLAY_MANAGER_H
#include "oh_display_info.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Obtains the ID of the default display.
 *
 * @param displayId Pointer to the display ID. The value is a non-negative integer.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayId(uint64_t *displayId);

/**
 * @brief Obtains the width of the default display.
 *
 * @param displayWidth Pointer to the width, in px. The value is an integer.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayWidth(int32_t *displayWidth);

/**
 * @brief Obtains the height of the default display.
 *
 * @param displayHeight Pointer to the height, in px. The value is an integer.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayHeight(int32_t *displayHeight);

/**
 * @brief Obtains the clockwise rotation angle of the default display.
 *
 * @param displayRotation Pointer to the clockwise rotation angle. For details about the available options, see
 *     {@link NativeDisplayManager_Rotation}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayRotation(
    NativeDisplayManager_Rotation *displayRotation);

/**
 * @brief Obtains the orientation of the default display.
 *
 * @param displayOrientation Pointer to the orientation. For details about the available options, see
 *     {@link NativeDisplayManager_Orientation}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayOrientation(
    NativeDisplayManager_Orientation *displayOrientation);

/**
 * @brief Obtains the virtual pixel ratio of the default display.
 *
 * @param virtualPixels Pointer to the virtual pixel ratio. The value is a floating-point number, and it is usually the
 *     same as that of **densityPixels**.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayVirtualPixelRatio(float *virtualPixels);

/**
 * @brief Obtains the refresh rate of the default display.
 *
 * @param refreshRate Pointer to the refresh rate. The value is an integer, in Hz.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayRefreshRate(uint32_t *refreshRate);

/**
 * @brief Obtains the physical pixel density of the default display.
 *
 * @param densityDpi Pointer to the physical pixel density, that is, the number of pixels per inch. The value is an
 *     integer, in px. The actual value depends on the options provided in device settings.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayDensityDpi(int32_t *densityDpi);

/**
 * @brief Obtains the logical pixel density of the default display.
 *
 * @param densityPixels Pointer to the logical pixel density, which indicates the scaling coefficient of the physical
 *     pixels and logical pixels. The value is a floating-point number in the range [0.5, 4.0]. Generally, the value is
 *     **1.0** or **3.0**. The actual value depends on the density DPI provided by the device in use.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayDensityPixels(float *densityPixels);

/**
 * @brief Obtains the scale factor of fonts displayed on the default display.
 *
 * @param scaledDensity Pointer to the scale factor. The value is a floating-point number, and it is usually the same
 *     as that of **densityPixels**.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayScaledDensity(float *scaledDensity);

/**
 * @brief Obtains the number of physical pixels per inch on the default display in the X dimension.
 *
 * @param xDpi Pointer to the number of physical pixels per inch in the X dimension. The value is a floating-point
 *     number.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayDensityXdpi(float *xDpi);

/**
 * @brief Obtains the number of physical pixels per inch on the default display in the Y dimension.
 *
 * @param yDpi Pointer to the number of physical pixels per inch in the Y dimension. The value is a floating-point
 *     number.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDefaultDisplayDensityYdpi(float *yDpi);

/**
 * @brief Obtains the unusable area of the default display, including punch hole, notch, and curved area of a waterfall
 * display.
 *
 * @param cutoutInfo Double pointer to the unusable area information, which is encapsulated in
 *     {@link NativeDisplayManager_CutoutInfo}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_CreateDefaultDisplayCutoutInfo(
    NativeDisplayManager_CutoutInfo **cutoutInfo);

/**
 * @brief Destroys the unusable area of the default display, including punch hole, notch, and curved area of a
 * waterfall display.
 *
 * @param cutoutInfo Pointer to the unusable area information object, which is obtained by calling
 *     {@link OH_NativeDisplayManager_CreateDefaultDisplayCutoutInfo}. For details, see
 *     {@link NativeDisplayManager_CutoutInfo}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_DestroyDefaultDisplayCutoutInfo(
    NativeDisplayManager_CutoutInfo *cutoutInfo);

/**
 * @brief Checks whether the current device is foldable.
 *
 * @return { bool } true means the device is foldable.
 * @since 12
 */
bool OH_NativeDisplayManager_IsFoldable();

/**
 * @brief Obtains the display mode of the foldable device.
 *
 * @param displayMode Pointer to the display mode. For details about the available options, see
 *     {@link NativeDisplayManager_FoldDisplayMode}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_DEVICE_NOT_SUPPORTED } device not support.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetFoldDisplayMode(
    NativeDisplayManager_FoldDisplayMode *displayMode);

/**
 * @brief Defines a callback function to listen for display status changes.
 *
 * @param displayId ID of the display.
 * @since 12
 */
typedef void (*OH_NativeDisplayManager_DisplayChangeCallback)(uint64_t displayId);

/**
 * @brief Registers a listener for display status changes (such as rotation, refresh rate, DPI, and resolution changes).
 *
 * @param displayChangeCallback Callback function triggered when the display status is changed. For details, see
 *     {@link OH_NativeDisplayManager_DisplayChangeCallback}.
 * @param listenerIndex Pointer to the index of the listener registered. It can be used as an input parameter of
 *     {@link OH_NativeDisplayManager_UnregisterDisplayChangeListener}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_RegisterDisplayChangeListener(
    OH_NativeDisplayManager_DisplayChangeCallback displayChangeCallback, uint32_t *listenerIndex);

/**
 * @brief Unregisters a listener for display status changes.
 *
 * @param listenerIndex Index of the listener returned when
 *     {@link OH_NativeDisplayManager_RegisterDisplayChangeListener} is called.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_UnregisterDisplayChangeListener(uint32_t listenerIndex);

/**
 * @brief Defines a callback function to listen for folded/unfolded state changes of the display.
 *
 * @param displayMode Folded or unfolded state of the display. For details about the available options, see
 *     {@link NativeDisplayManager_FoldDisplayMode}.
 * @since 12
 */
typedef void (*OH_NativeDisplayManager_FoldDisplayModeChangeCallback)(
    NativeDisplayManager_FoldDisplayMode displayMode);

/**
 * @brief Registers a listener for folded/unfolded state changes of the display.
 *
 * @param displayModeChangeCallback Callback function triggered when the folded/unfolded state of the display is
 *     changed. For details, see {@link OH_NativeDisplayManager_FoldDisplayModeChangeCallback}.
 * @param listenerIndex Pointer to the index of the listener registered. It can be used as an input parameter of
 *     {@link OH_NativeDisplayManager_UnregisterFoldDisplayModeChangeListener}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_DEVICE_NOT_SUPPORTED } device not support.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_RegisterFoldDisplayModeChangeListener(
    OH_NativeDisplayManager_FoldDisplayModeChangeCallback displayModeChangeCallback, uint32_t *listenerIndex);

/**
 * @brief Unregisters a listener for folded/unfolded state changes of the display.
 *
 * @param listenerIndex Index of the listener returned when
 *     {@link OH_NativeDisplayManager_RegisterFoldDisplayModeChangeListener} is called.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_DEVICE_NOT_SUPPORTED } device not support.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 12
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_UnregisterFoldDisplayModeChangeListener(uint32_t listenerIndex);

/**
 * @brief Obtains the object that contains the information about all displays.
 *
 * @param allDisplays Double pointer to the display information, which is encapsulated in
 *     {@link NativeDisplayManager_DisplaysInfo}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful.
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 14
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_CreateAllDisplays(
    NativeDisplayManager_DisplaysInfo **allDisplays);

/**
 * @brief Destroys the object that contains the information about all displays.
 *
 * @param allDisplays Pointer to the display information object, which is obtained by calling
 *     {@link OH_NativeDisplayManager_CreateAllDisplays}. For details, see {@link NativeDisplayManager_DisplaysInfo}.
 * @since 14
 */
void OH_NativeDisplayManager_DestroyAllDisplays(NativeDisplayManager_DisplaysInfo *allDisplays);

/**
 * @brief Obtains the object that contains the information about a display.
 *
 * @param displayId ID of the display. The value must be a non-negative integer.
 * @param displayInfo Double pointer to the display information, which is encapsulated in
 *     {@link NativeDisplayManager_DisplayInfo}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful.
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 14
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_CreateDisplayById(uint32_t displayId,
    NativeDisplayManager_DisplayInfo **displayInfo);

/**
 * @brief Destroys the object that contains the information about a display.
 *
 * @param displayInfo Pointer to the display information object, which is obtained by calling
 *     {@link OH_NativeDisplayManager_CreateDisplayById} or {@link OH_NativeDisplayManager_CreatePrimaryDisplay}. For
 *     details, see {@link NativeDisplayManager_DisplayInfo}.
 * @since 14
 */
void OH_NativeDisplayManager_DestroyDisplay(NativeDisplayManager_DisplayInfo *displayInfo);

/**
 * @brief Obtains the object that contains the information about the primary display. For devices other than 2-in-1
 * devices, the displayInfo object obtained contains information about the built-in screen. For 2-in-1 devices with an
 * external screen, the displayInfo object obtained contains information about the current primary screen. For 2-in-1
 * devices without an external screen, the displayInfo object obtained contains information about the built-in screen.
 *
 * @param displayInfo Double pointer to the display information, which is encapsulated in
 *     {@link NativeDisplayManager_DisplayInfo}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful.
 *     <br>{@link DISPLAY_MANAGER_ERROR_INVALID_PARAM } If Parameter error.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 14
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_CreatePrimaryDisplay(
    NativeDisplayManager_DisplayInfo **displayInfo);

/**
 * @brief Defines a callback function to listen for available area changes of a display.
 *
 * @param displayId Display ID, which is a non-negative integer.
 * @since 20
 */
typedef void (*OH_NativeDisplayManager_AvailableAreaChangeCallback)(uint64_t displayId);

/**
 * @brief Registers a listener for available area changes of the display.
 *
 * @param availableAreaChangeCallback Callback function triggered when the available area of the display changes.
 *     For details, see {@link OH_NativeDisplayManager_AvailableAreaChangeCallback}.
 * @param listenerIndex Pointer to the index of the listener registered.
 *     It can be used as an input parameter of {@link OH_NativeDisplayManager_UnregisterAvailableAreaChangeListener}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_ILLEGAL_PARAM } If Parameter illegal.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_RegisterAvailableAreaChangeListener(
    OH_NativeDisplayManager_AvailableAreaChangeCallback availableAreaChangeCallback, uint32_t *listenerIndex);

/**
 * @brief Unregisters a listener for available area changes of the display.
 *
 * @param listenerIndex Index of the listener returned
 *     when {@link OH_NativeDisplayManager_RegisterAvailableAreaChangeListener} is called.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_ILLEGAL_PARAM } If Parameter illegal.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_UnregisterAvailableAreaChangeListener(uint32_t listenerIndex);

/**
 * @brief Obtains the available area of a display.
 *
 * @param displayId Display ID, which is a non-negative integer.
 * @param availableArea Double pointer to the available area of the display. For details, see
 *     {@link NativeDisplayManager_Rect}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_DEVICE_NOT_SUPPORTED } device not support.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_CreateAvailableArea(uint64_t displayId, NativeDisplayManager_Rect **availableArea);

/**
 * @brief Destroys the available area of a display.
 *
 * @param availableArea Pointer to the available area, which is obtained by calling
 *     {@link OH_NativeDisplayManager_CreateAvailableArea}.
 *     For details about the available area, see {@link NativeDisplayManager_Rect}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_ILLEGAL_PARAM } If Parameter illegal.
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_DestroyAvailableArea(NativeDisplayManager_Rect *availableArea);

/**
 * @brief Defines a callback function to listen for display addition events.
 *
 * @param displayId Display ID, which is a non-negative integer.
 * @since 20
 */
typedef void (*OH_NativeDisplayManager_DisplayAddCallback)(uint64_t displayId);

/**
 * @brief Registers a listener for display addition events (for example, monitor inserted).
 *
 * @param displayAddCallback Callback function triggered when a display is added. For details, see
 *     {@link OH_NativeDisplayManager_DisplayAddCallback}.
 * @param listenerIndex Pointer to the index of the listener registered.
 *     It can be used as an input parameter of {@link OH_NativeDisplayManager_UnregisterDisplayAddListener}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_ILLEGAL_PARAM } If Parameter illegal.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_RegisterDisplayAddListener(
    OH_NativeDisplayManager_DisplayAddCallback displayAddCallback, uint32_t *listenerIndex);

/**
 * @brief Unregisters a listener for display addition events.
 *
 * @param listenerIndex Index of the listener returned when {@link OH_NativeDisplayManager_RegisterDisplayAddListener}
 *     is called.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_ILLEGAL_PARAM } If Parameter illegal.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_UnregisterDisplayAddListener(uint32_t listenerIndex);

/**
 * @brief Defines a callback function to listen for display removal events.
 *
 * @param displayId Display ID, which is a non-negative integer.
 * @since 20
 */
typedef void (*OH_NativeDisplayManager_DisplayRemoveCallback)(uint64_t displayId);

/**
 * @brief Registers a listener for display removal events (for example, monitor removed).
 *
 * @param displayRemoveCallback Callback function triggered when a display is removed. For details, see
 *     {@link OH_NativeDisplayManager_DisplayRemoveCallback}.
 * @param listenerIndex Pointer to the index of the listener registered.
 *     It can be used as an input parameter of {@link OH_NativeDisplayManager_UnregisterDisplayRemoveListener}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_ILLEGAL_PARAM } If Parameter illegal.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_RegisterDisplayRemoveListener(
    OH_NativeDisplayManager_DisplayRemoveCallback displayRemoveCallback, uint32_t *listenerIndex);

/**
 * @brief Unregisters the listener for display removal events.
 *
 * @param listenerIndex Index of the listener returned when
 *     {@link OH_NativeDisplayManager_RegisterDisplayRemoveListener} is called.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_ILLEGAL_PARAM } If Parameter illegal.
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_UnregisterDisplayRemoveListener(uint32_t listenerIndex);

/**
 * @brief Obtains the display source mode. The default value is **DisplaySourceMode.None**.
 *
 * @param displayId Display ID, which is a non-negative integer.
 * @param sourceMode Pointer to the source mode. For details about the available options, see
 *     {@link NativeDisplayManager_SourceMode}.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDisplaySourceMode(uint64_t displayId, NativeDisplayManager_SourceMode *sourceMode);

/**
 * @brief Obtains the display position, that is, the x-coordinate and y-coordinate relative to the original point (the
 * upper left corner of the main screen).
 *
 * @param displayId Display ID, which is a non-negative integer.
 * @param x Pointer to the x-coordinate relative to the upper left corner of the main screen, in px. The value must be
 *     an integer and is returned as an output parameter.
 * @param y Pointer to the y-coordinate relative to the upper left corner of the main screen, in px. The value must be
 *     an integer and is returned as an output parameter.
 * @return {@link DISPLAY_MANAGER_OK } If the operation is successful
 *     <br>{@link DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL } If display manager service works abnormally.
 * @since 20
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_GetDisplayPosition(uint64_t displayId, int32_t *x, int32_t *y);
#ifdef __cplusplus
}
#endif

/** @} */
#endif // OH_NATIVE_DISPLAY_MANAGER_H
/**
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 * @brief Declares the APIs of **NativeDrag**, supporting obtaining drag events, setting and obtaining drag data,
 * configuring drag previews, initiating drag operations, and listening for drag states. It is suitable for scenarios
 * where applications need to implement native drag interactions, data drag-in and drag-out, and custom drag effects.
 * This module supports cross-device drag interactions, provides an asynchronous data loading mechanism to improve
 * the efficiency of dragging large amounts of data, and supports fine-grained drag behavior control and state
 * listening.
 *
 * @library libace_ndk.z.so
 * @kit ArkUI
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_DRAG_AND_DROP_H
#define ARKUI_NATIVE_DRAG_AND_DROP_H

#include <stdint.h>

#include "common_type.h"
#include "native_type.h"
#include "database/udmf/udmf.h"
#include "multimedia/image_framework/image/pixelmap_native.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates drag results, which are set by the data receiver and transferred by the system to the drag source
 * so that the drag source is aware of the data processing result of the receiver.
 *
 * @since 12
 */
typedef enum {
    /**
     * The drag and drop operation succeeded.
     */
    ARKUI_DRAG_RESULT_SUCCESSFUL = 0,
    /**
     * The drag and drop operation failed.
     */
    ARKUI_DRAG_RESULT_FAILED,
    /**
     * The drag and drop operation was canceled.
     */
    ARKUI_DRAG_RESULT_CANCELED,
} ArkUI_DragResult;

/**
 * @brief Enumerates data processing modes used when data is dropped, which affects the display of the badge. When the
 * copy operation is set, the badge displays a plus sign (+). When the cut operation is set, the badge does not display
 * a plus sign (+).
 *
 * @since 12
 */
typedef enum {
    /**
     * Copy.
     */
    ARKUI_DROP_OPERATION_COPY = 0,
    /**
     * Cut.
     */
    ARKUI_DROP_OPERATION_MOVE,
} ArkUI_DropOperation;

/**
 * @brief Enumerates interaction states prior to a drop and drop operation.
 *
 * @since 12
 */
typedef enum {
    /**
     * Failed to obtain the status before drag is initiated.
     */
    ARKUI_PRE_DRAG_STATUS_UNKNOWN = -1,
    /**
     * A drag gesture is being detected.
     */
    ARKUI_PRE_DRAG_STATUS_ACTION_DETECTING,
    /**
     * The component is ready to be dragged.
     */
    ARKUI_PRE_DRAG_STATUS_READY_TO_TRIGGER_DRAG,
    /**
     * A lift animation is started.
     */
    ARKUI_PRE_DRAG_STATUS_PREVIEW_LIFT_STARTED,
    /**
     * A lift animation is finished.
     */
    ARKUI_PRE_DRAG_STATUS_PREVIEW_LIFT_FINISHED,
    /**
     * A drop animation is started.
     */
    ARKUI_PRE_DRAG_STATUS_PREVIEW_LANDING_STARTED,
    /**
     * A drop animation is finished.
     */
    ARKUI_PRE_DRAG_STATUS_PREVIEW_LANDING_FINISHED,
    /**
     * A drop animation is canceled.
     */
    ARKUI_PRE_DRAG_STATUS_CANCELED_BEFORE_DRAG,
} ArkUI_PreDragStatus;

/**
 * @brief Enumerates drag preview scale modes.
 *
 * @since 12
 */
typedef enum {
    /**
     * Enables the system to automatically change the position of the dragged point based on the scenario and apply
     * scaling transformations to the drag preview based on set rules.
     */
    ARKUI_DRAG_PREVIEW_SCALE_AUTO = 0,
    /**
     * Disables the system's scaling behavior for the drag preview.
     */
    ARKUI_DRAG_PREVIEW_SCALE_DISABLED,
} ArkUI_DragPreviewScaleMode;

/**
 * @brief Enumerates drag operation states.
 *
 * @since 12
 */
typedef enum {
    /**
     * Unknown drag state.
     */
    ARKUI_DRAG_STATUS_UNKNOWN = -1,
    /**
     * The drag operation has started.
     */
    ARKUI_DRAG_STATUS_STARTED,
    /**
     * The drag operation has ended.
     */
    ARKUI_DRAG_STATUS_ENDED,
} ArkUI_DragStatus;

/**
 * @brief Defines a drag event, used to represent event information during the drag process of an ArkUI component.
 * You can obtain the drag status and event data through related drag event APIs in the following header file. For
 * details about the drag event binding process, see Binding Drag Events.
 *
 * @since 12
 */
typedef struct ArkUI_DragEvent ArkUI_DragEvent;

/**
 * @brief Sets a custom drag preview option (such as the shadow and rounded corner effect), which is used to
 * customize the preview image display effect in drag scenarios and help applications provide a drag interaction
 * experience that better meets service requirements.
 *
 * @since 12
 */
typedef struct ArkUI_DragPreviewOption ArkUI_DragPreviewOption;

/**
 * @brief Defines a drag action handle, which is used to proactively initiate dragging, where you proactively call
 * an API to start dragging, as opposed to passively responding to drag events. This handle supports creating,
 * configuring, executing, and destroying a drag action. You can set drag data and proactively start dragging.
 *
 * The usage process of **ArkUI_DragAction** is as follows:
 *
 * 1. Create an object by calling {@link OH_ArkUI_CreateDragActionWithNode} or
 * {@link OH_ArkUI_CreateDragActionWithContext}.
 * 2. Set drag parameters by calling APIs such as **OH_ArkUI_DragAction_SetData**.
 * 3. Start dragging by calling {@link OH_ArkUI_StartDrag}.
 * 4. When the object is no longer needed, call {@link OH_ArkUI_DragAction_Dispose} to destroy the object and
 * release resources.
 *
 * For details about the creation, configuration, and execution mechanisms, see Binding Drag Events.
 *
 * @since 12
 */
typedef struct ArkUI_DragAction ArkUI_DragAction;

/**
 * @brief Defines drag and drop information returned through a drag status listener after dragging is proactively
 * initiated. You can obtain the drag start or end status and the drag event data when the drag ends from this
 * struct, and perform subsequent processing based on the status. For details about how to register the drag
 * callback, see drag_and_drop.h.
 *
 * @since 12
 */
typedef struct ArkUI_DragAndDropInfo ArkUI_DragAndDropInfo;

/**
 * @brief Obtains a **DragEvent** object from the specified **NodeEvent** object.
 *
 * @param nodeEvent Pointer to the target **ArkUI_NodeEvent** object.
 * @return Returns the pointer to an **ArkUI_DragEvent** object; returns null if the parameter passed in is invalid or
 *     is not a drag-related event.
 * @since 12
 */
ArkUI_DragEvent* OH_ArkUI_NodeEvent_GetDragEvent(ArkUI_NodeEvent* nodeEvent);

/**
 * @brief Obtains the state prior to a drop and drop operation.
 *
 * @param nodeEvent Pointer to the target **ArkUI_NodeEvent** object.
 * @return Interaction status before drag is initiated.
 * @since 12
 */
ArkUI_PreDragStatus OH_ArkUI_NodeEvent_GetPreDragStatus(ArkUI_NodeEvent* nodeEvent);

/**
 * @brief Sets whether to disable the default drop animation, which is enabled by default. Use this API to apply a
 * custom drop animation. It has the same functionality as {@link OH_ArkUI_NotifyDisableDefaultDropAnimation}, with
 * the following difference: this API sets the configuration directly in a synchronous drag event callback, making it
 * suitable for scenarios where deferred processing of the drag end event is not required;
 * **OH_ArkUI_NotifyDisableDefaultDropAnimation** notifies the configuration in the asynchronous
 * **RequestDragEndPending** flow, making it suitable for scenarios where
 * {@link OH_ArkUI_DragEvent_RequestDragEndPending} has been called to defer processing of the drag end event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param disable Whether to disable the default drop animation. The value **true** means to disable the default drop
 *     animation, and **false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_DisableDefaultDropAnimation(ArkUI_DragEvent* event, bool disable);

/**
 * @brief Sets the data processing mode, which affects how the badge is displayed during dragging. This is suitable
 * for scenarios where you need to suggest data processing behavior to the system when data is dropped. For example,
 * when copyable text or image content is dragged, it is recommended to set the copying behavior
 * (**ARKUI_DROP_OPERATION_COPY**); when dragging content needs to be removed from the source location, it is
 * recommended to set the cutting behavior (**ARKUI_DROP_OPERATION_MOVE**). This API has the same functionality as
 * {@link OH_ArkUI_NotifySuggestedDropOperation}, with the following difference: this API sets the data processing
 * mode directly in a synchronous drag event callback, which is suitable for scenarios where delayed processing of
 * the drag end event is not required; **OH_ArkUI_NotifySuggestedDropOperation** sends the data processing mode
 * notification in the asynchronous **RequestDragEndPending** flow, which is suitable for scenarios where
 * {@link OH_ArkUI_DragEvent_RequestDragEndPending} has been called to delay processing of the drag end event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param dropOperation Data processing mode, used to set the operation type upon drop.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_SetSuggestedDropOperation(ArkUI_DragEvent* event, ArkUI_DropOperation dropOperation);

/**
 * @brief Sets the result for a drag event. As the data receiver, this API sets the processing result of the drag
 * event in the drop callback so that the drag initiator can perceive the data receiving and processing status. This
 * API has the same functionality as {@link OH_ArkUI_NotifyDragResult}, with the following difference: this API sets
 * the drag result directly in a synchronous drag event callback, which is suitable for scenarios where delayed
 * processing of the drag end event is not required; **OH_ArkUI_NotifyDragResult** sends the result notification in
 * the asynchronous **RequestDragEndPending** flow, which is suitable for scenarios where
 * {@link OH_ArkUI_DragEvent_RequestDragEndPending} has been called to delay processing of the drag end event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param result Drag data processing result.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_SetDragResult(ArkUI_DragEvent* event, ArkUI_DragResult result);

/**
 * @brief Sets drag data for **ArkUI_DragEvent**. {@link OH_ArkUI_DragEvent_SetDataLoadParams} should be used
 * preferentially to provide data loading parameters, so as to improve the efficiency of dragging large amounts of
 * data and the efficiency of processing dropped data in the target application. If this API conflicts with
 * {@link OH_ArkUI_DragEvent_SetDataLoadParams}, the system always uses the last called API.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param data Pointer to the drag data object to set.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_SetData(ArkUI_DragEvent* event, OH_UdmfData* data);

/**
 * @brief Provides data loading parameters to the system instead of directly providing a complete data object. When
 * the user drops data on the target application, the system will use **dataLoadParams** to request data. This can
 * significantly improve the efficiency of dragging large volumes of data and the efficiency of processing the dropped
 * data in the target application. This API must always be used in preference to {@link OH_ArkUI_DragEvent_SetData}.
 * For details about how to create and prepare data loading parameters, see {@link OH_UdmfDataLoadParams_Create} in
 * **udmf.h**. If this API conflicts with {@link OH_ArkUI_DragEvent_SetData}, the system always uses the last called
 * API.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param dataLoadParams Data loading parameters used during a drop operation.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_DragEvent_SetDataLoadParams(ArkUI_DragEvent* event, OH_UdmfDataLoadParams* dataLoadParams);

/**
 * @brief Obtains the drag data from **ArkUI_DragEvent**.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param data Pointer to an **OH_UdmfData** object. The application needs to create a pointer for receiving data by
 *     using the {@link OH_UdmfData_Create} API.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_GetUdmfData(ArkUI_DragEvent* event, OH_UdmfData *data);

/**
 * @brief Obtains the number of drag data types from a drag event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param count Number of drag data types returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_GetDataTypeCount(ArkUI_DragEvent* event, int32_t* count);

/**
 * @brief Obtains the type list of drag data types from a drag event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param eventTypeArray Pointer to the list of the drag data types. You need to create a string array first.
 * @param length Total length of the array, which cannot be less than the number obtained using
 *     {@link OH_ArkUI_DragEvent_GetDataTypeCount}.
 * @param maxStrLen Maximum string length of the drag data type, used to limit the buffer size of each data type
 *     string. Recommended value: no less than 128 characters to ensure that all standard UDMF data type strings
 *     can be fully received.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the input buffer size is abnormal.
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_GetDataTypes(
    ArkUI_DragEvent *event, char *eventTypeArray[], int32_t length, int32_t maxStrLen);

/**
 * @brief Obtains the data summary from a drag event.
 *
 * @param event [in] Pointer to an <b>ArkUI_DragEvent</b> object. The pointer cannot be null.
 * @param summary [out] Pointer to an <b>OH_UDMF_Summary</b> object used to receive the summary.
 *     The pointer cannot be null. The object must be created by the caller before this API is called and destroyed
 *     by the caller after use. If the operation fails, the content of the object is not guaranteed to be valid.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_INTERNAL_ERROR} if an internal error occurs.
 * @since 26.2.0
 */
int32_t OH_ArkUI_DragEvent_GetSummary(ArkUI_DragEvent* event, OH_UDMF_Summary* summary);

/**
 * @brief Obtains the drag and drop result from the drag event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param result Drag result returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_GetDragResult(ArkUI_DragEvent* event, ArkUI_DragResult* result);

/**
 * @brief Obtains the data processing method from **ArkUI_DragEvent**. When the drag fails, the operation type of
 * the current drop is unreliable, and the operation type obtained is always **ARKUI_DROP_OPERATION_COPY**.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param operation Pointer to the data processing mode of the drag event.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Possible cause: 1. Parameters are null or the event is not a valid **DragEvent**.
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_GetDropOperation(ArkUI_DragEvent* event, ArkUI_DropOperation* operation);

/**
 * @brief Obtains the x-coordinate of the touch point for a drag preview from a drag event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @return X-coordinate of the touch point, in px, or the default value **0** if the input parameter is invalid.
 * @since 12
 */
float OH_ArkUI_DragEvent_GetPreviewTouchPointX(ArkUI_DragEvent* event);

/**
 * @brief Obtains the y-coordinate of the touch point on the preview image from a drag event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @return Y-coordinate of the touch point, in px. The default value **0** is returned when the input parameter is
 *     invalid.
 * @since 12
 */
float OH_ArkUI_DragEvent_GetPreviewTouchPointY(ArkUI_DragEvent* event);

/**
 * @brief Obtains the width of a drag preview from a drag event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @return Width of the drag preview, in px, or the default value **0** if the input parameter is invalid.
 * @since 12
 */
float OH_ArkUI_DragEvent_GetPreviewRectWidth(ArkUI_DragEvent* event);

/**
 * @brief Obtains the height of a drag preview from a drag event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @return Height of the drag preview, in px, or the default value **0** if the input parameter is invalid.
 * @since 12
 */
float OH_ArkUI_DragEvent_GetPreviewRectHeight(ArkUI_DragEvent* event);

/**
 * @brief Obtains the x-coordinate of the touch point relative to the window from a drag event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @return X-coordinate of the touch point relative to the window, in px, or the default value **0** if the input
 *     parameter is invalid.
 * @since 12
 */
float OH_ArkUI_DragEvent_GetTouchPointXToWindow(ArkUI_DragEvent* event);

/**
 * @brief Obtains the y-coordinate of the touch point relative to the window from a drag event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @return Y-coordinate of the touch point relative to the window, in px, or the default value **0** if the input
 *     parameter is invalid.
 * @since 12
 */
float OH_ArkUI_DragEvent_GetTouchPointYToWindow(ArkUI_DragEvent* event);

/**
 * @brief Obtains the x-coordinate of the touch point relative to the display from a drag event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @return X-coordinate of the touch point relative to the display, in px, or the default value **0** if the input
 *     parameter is invalid.
 * @since 12
 */
float OH_ArkUI_DragEvent_GetTouchPointXToDisplay(ArkUI_DragEvent* event);

/**
 * @brief Obtains the y-coordinate of the touch point relative to the display from a drag event.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @return Y-coordinate of the touch point relative to the display, in px, or the default value **0** if the input
 *     parameter is invalid.
 * @since 12
 */
float OH_ArkUI_DragEvent_GetTouchPointYToDisplay(ArkUI_DragEvent* event);

/**
 * @brief Obtains the x-coordinate of the drag touch point relative to the global display from the specified **
 * ArkUI_DragEvent** object.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @return X-coordinate of the touch point relative to the global display, in px, or the default value **0** if the
 *     input parameter is invalid.
 * @since 20
 */
float OH_ArkUI_DragEvent_GetTouchPointXToGlobalDisplay(ArkUI_DragEvent* event);

/**
 * @brief Obtains the y-coordinate of the drag touch point relative to the global display from the specified **
 * ArkUI_DragEvent** object.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @return Y-coordinate of the touch point relative to the global display, in px, or the default value **0** if the
 *     input parameter is invalid.
 * @since 20
 */
float OH_ArkUI_DragEvent_GetTouchPointYToGlobalDisplay(ArkUI_DragEvent* event);

/**
 * @brief Obtains the dragging velocity along the x-axis.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @return Dragging velocity along the x-axis, in px/s, or the default value **0** if the input parameter is invalid.
 * @since 12
 */
float OH_ArkUI_DragEvent_GetVelocityX(ArkUI_DragEvent* event);

/**
 * @brief Obtains the dragging velocity along the y-axis.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @return Dragging velocity along the y-axis, in px/s, or the default value **0** if the input parameter is invalid.
 * @since 12
 */
float OH_ArkUI_DragEvent_GetVelocityY(ArkUI_DragEvent* event);

/**
 * @brief Obtains the dragging velocity along the main axis.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @return Dragging velocity along the main axis, in px/s, or the default value **0** if the input parameter is invalid.
 * @since 12
 */
float OH_ArkUI_DragEvent_GetVelocity(ArkUI_DragEvent* event);

/**
 * @brief Obtains the pressed states of modifier keys.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param keys Pointer to the combination of pressed modifier keys. The value is a bitwise OR of the masks
 *     corresponding to each modifier key: the **Ctrl** key corresponds to bit 0 (mask value 0x1), the **Shift**
 *     key corresponds to bit 1 (mask value 0x2), and the **Alt** key corresponds to bit 2 (mask value 0x4). The
 *     application can use bitwise operations to determine which keys are pressed, for example, using
 *     **(*keys & 0x1)** to check whether the **Ctrl** key is pressed.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragEvent_GetModifierKeyStates(ArkUI_DragEvent* event, uint64_t* keys);

/**
 * @brief Obtains the ID of the display where this drag event occurs. This is suitable for multi-display device
 * scenarios where it is necessary to determine which display the drag operation occurs on, such as performing
 * differentiated processing based on the display ID during cross-screen dragging. This API is not supported when
 * **eventType** is set to **NODE_ON_DRAG_END**.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param displayId Pointer to the ID of the display where the current drag event occurs.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_DragEvent_GetDisplayId(ArkUI_DragEvent* event, int32_t* displayId);

/**
 * @brief Obtains the bundle name of the drag source application. This API can be used to identify the drag source
 * application, perform verification based on the source, or execute differentiated processing. When calling, a
 * character array must be passed to receive the bundle name string, and the array length must be explicitly
 * specified, with a length of no less than 128 characters.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param bundleName Character array to store the bundle name string, with a length of at least 128 characters.
 * @param length Length of the character array to store the bundle name string. The minimum length is 128 characters.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_DragEvent_GetDragSource(ArkUI_DragEvent* event, char *bundleName, int32_t length);

/**
 * @brief Checks whether the current drag operation is a cross-device drag. This API is suitable for scenarios where
 * it is necessary to distinguish between local drag and cross-device drag. For example, cross-device dragging may
 * require additional verification of data transmission or display different UI prompts, while local dragging can
 * process data directly.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param isRemote Pointer to a boolean variable to store the result. The value **true** means that the current drag
 *     operation is a cross-device drag, and **false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_DragEvent_IsRemote(ArkUI_DragEvent* event, bool* isRemote);

/**
 * @brief Starts data synchronization using the specified synchronization parameters. When this API is used in
 * **NODE_ON_DROP**, to avoid accidentally obtaining data before **NODE_ON_DROP** is executed, data prefetching must
 * first be disabled through {@link OH_ArkUI_DisableDropDataPrefetchOnNode}.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param options Pointer to the option array for data obtaining, used to configure data request options during this
 *     drag data synchronization.
 * @param key Pointer to the key value allocated after data loading is successfully started. The length of the
 *     character array used to receive the key must be no less than that specified by {@link UDMF_KEY_BUFFER_LEN}.
 * @param keyLen Length of the key string. It must be no less than the length defined by {@link UDMF_KEY_BUFFER_LEN},
 *     which is used to ensure that the key can be completely received.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_DragEvent_StartDataLoading(
    ArkUI_DragEvent* event, OH_UdmfGetDataParams* options, char* key, unsigned int keyLen);

/**
 * @brief Cancels the ongoing data synchronization.
 *
 * @param uiContext Pointer to the UI instance.
 * @param key Pointer to the data key returned by {@link OH_ArkUI_DragEvent_StartDataLoading}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_CancelDataLoading(ArkUI_ContextHandle uiContext, const char* key);

/**
 * @brief Sets whether to disable the data prefetch process before executing {@link NODE_ON_DROP}. The system will
 * retry data fetching until the maximum time limit (currently 2.4 seconds) is reached, which is useful for cross-
 * device drag and drop operations as it helps stabilize system communication. However, this feature is redundant for
 * the {@link OH_ArkUI_DragEvent_StartDataLoading} API. Since this API uses an asynchronous mechanism to fetch data,
 * when {@link OH_ArkUI_DragEvent_StartDataLoading} is used in **NODE_ON_DROP**, this field must be set to **true** to
 * prevent accidental data fetching before **NODE_ON_DROP** is executed.
 *
 * @param node Pointer to the component node.
 * @param disabled Whether to disable data prefetching. The value **true** means to disable it, and **false** means
 *     the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_DisableDropDataPrefetchOnNode(ArkUI_NodeHandle node, bool disabled);

/**
 * @brief Sets whether to enable strict reporting on drag events. This feature is disabled by default, and you are
 * advised to enable it. If this feature is disabled, the parent component is not notified when an item in it is
 * dragged over its child component. If this feature is enabled, the component is notified of the dragged item's
 * leaving, and the child component to which the dragged item is dropped is notified of the item's entering. This
 * configuration is related to a specific UI instance. You can pass in a specific component node on the current UI
 * instance for association.
 *
 * @param node Pointer to the component node.
 * @param enabled Whether to enable strict reporting on drag events. The value **true** means to enable strict
 *     reporting on drag events, and **false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_SetDragEventStrictReportWithNode(ArkUI_NodeHandle node, bool enabled);

/**
 * @brief Sets whether to enable strict reporting on drag events. This feature is disabled by default, and you are
 * advised to enable it. If this feature is disabled, the parent component is not notified when an item in it is
 * dragged over its child component. If this feature is enabled, the component is notified of the dragged item's
 * leaving, and the child component to which the dragged item is dropped is notified of the item's entering. This
 * configuration is related to a specific UI instance. You can pass in a specific UI instance for association.
 *
 * @param uiContext Pointer to the UI instance.
 * @param enabled Whether to enable strict reporting on drag events. The value **true** means to enable strict
 *     reporting on drag events, and **false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_SetDragEventStrictReportWithContext(ArkUI_ContextHandle uiContext, bool enabled);

/**
 * @brief Sets the types of data that can be dropped to the specified component. This API resets the settings
 * configured through {@link OH_ArkUI_DisallowNodeAnyDropDataTypes} or {@link OH_ArkUI_AllowNodeAllDropDataTypes}.
 *
 * @param node Pointer to the component node.
 * @param typesArray Pointer to the array of types of data that can be dropped. The array elements are strings of
 *     unified data type identifiers defined by UDMF.
 * @param count Length of the array, indicating the number of data type strings in **typesArray**. The number must
 *     be consistent with the actual number of elements in **typesArray**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_SetNodeAllowedDropDataTypes(ArkUI_NodeHandle node, const char* typesArray[], int32_t count);

/**
 * @brief Configures the specified component to disallow any data types. This API resets the settings configured
 * through {@link OH_ArkUI_SetNodeAllowedDropDataTypes}. Note: Calling
 * **OH_ArkUI_SetNodeAllowedDropDataTypes** also resets the configuration made by this API.
 *
 * @param node Pointer to the component node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DisallowNodeAnyDropDataTypes(ArkUI_NodeHandle node);

/**
 * @brief Configures the specified component to allow any data types. This API resets the settings configured through
 * {@link OH_ArkUI_SetNodeAllowedDropDataTypes}. Note: Calling **OH_ArkUI_SetNodeAllowedDropDataTypes** also resets
 * the configuration made by this API.
 *
 * @param node Pointer to the component node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_AllowNodeAllDropDataTypes(ArkUI_NodeHandle node);

/**
 * @brief Sets whether the component is draggable.
 *
 * @param node Pointer to the component node.
 * @param enabled Whether the component is draggable. The value **true** means that the component is draggable, and **
 *     false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_SetNodeDraggable(ArkUI_NodeHandle node, bool enabled);

/**
 * @brief Sets a custom drag preview for the specified component.
 *
 * @param node Pointer to the component node.
 * @param preview Custom drag preview, which is a pixel map.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_SetNodeDragPreview(ArkUI_NodeHandle node, OH_PixelmapNative* preview);

/**
 * @brief Creates an **ArkUI_DragPreviewOption** object. When the object is no longer needed, you can call
 * {@link OH_ArkUI_DragPreviewOption_Dispose} to dispose of it to prevent resource leaks.
 *
 * @return Pointer to the **ArkUI_DragPreviewOption** object, which is used to configure custom parameters for the
 *     drag preview.
 * @since 12
 */
ArkUI_DragPreviewOption* OH_ArkUI_CreateDragPreviewOption(void);

/**
 * @brief Disposes of an **ArkUI_DragPreviewOption** object.
 *
 * @param option Pointer to the custom drag preview parameter object to dispose of.
 * @since 12
 */
void OH_ArkUI_DragPreviewOption_Dispose(ArkUI_DragPreviewOption* option);

/**
 * @brief Sets whether the drag preview is automatically scaled according to the system definition. This API is
 * suitable for scenarios where the drag preview size needs to be adjusted according to system rules during
 * dragging, or where the original size of the custom drag preview needs to be maintained.
 *
 * @param option Pointer to the custom drag preview parameter object, which is used to set the scale mode of the
 *     drag preview.
 * @param scaleMode Scale mode to set.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragPreviewOption_SetScaleMode(ArkUI_DragPreviewOption* option, ArkUI_DragPreviewScaleMode scaleMode);

/**
 * @brief Sets whether to enable the default shadow effect for an **ArkUI_DragPreviewOption** object. The effect is
 * disabled by default.
 *
 * @param option Pointer to the custom drag preview parameter object, which is used to set the default projection
 *     effect of the drag preview.
 * @param enabled Whether to enable the default shadow effect. The value **true** means to enable the default shadow
 *     effect, and **false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled(ArkUI_DragPreviewOption* option, bool enabled);

/**
 * @brief Sets whether to enable the default corner radius effect for an **ArkUI_DragPreviewOption** object. The
 * rounded corner radius is 12.0 vp by default. The effect is disabled by default.
 *
 * @param option Pointer to the custom drag preview parameter object, which is used to set the default corner radius
 *     effect of the drag preview.
 * @param enabled Whether to enable the default corner radius effect. The value **true** means to enable the default
 *     corner radius effect, and **false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragPreviewOption_SetDefaultRadiusEnabled(ArkUI_DragPreviewOption* option, bool enabled);

/**
 * @brief Sets whether to enable the badge for an **ArkUI_DragPreviewOption** object. If this feature is enabled, a
 * badge that contains the number of dragged items is displayed. Note: Calling
 * {@link OH_ArkUI_DragPreviewOption_SetBadgeNumber} overrides the value set by this API.
 *
 * @param option Pointer to the custom drag preview parameter object, which is used to set whether to display the
 *     count badge on the drag preview.
 * @param enabled Whether to enable the badge. The value **true** means to enable the badge, and **false** means the
 *     opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragPreviewOption_SetNumberBadgeEnabled(ArkUI_DragPreviewOption* option, bool enabled);

/**
 * @brief Sets the count on the badge. The settings will overwrite the value in
 * {@link OH_ArkUI_DragPreviewOption_SetNumberBadgeEnabled}.
 *
 * @param option Pointer to the custom drag preview parameter object, which is used to set the count that is
 *     forcibly displayed on the badge.
 * @param forcedNumber Count on the badge. The value is a positive integer used to forcibly specify the count
 *     displayed on the badge.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragPreviewOption_SetBadgeNumber(ArkUI_DragPreviewOption* option, uint32_t forcedNumber);

/**
 * @brief Sets whether to enable the default animation on a click or touch. This API is suitable for scenarios where
 * press visual feedback is needed before the drag preview lifts.
 *
 * @param option Pointer to the custom drag preview parameter object.
 * @param enabled Whether to enable the default animation on a click or touch. The value **true** means to enable the
 *     default animation on a click or touch, and **false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragPreviewOption_SetDefaultAnimationBeforeLiftingEnabled(
    ArkUI_DragPreviewOption* option, bool enabled);
/**
 * @brief Sets an **ArkUI_DragPreviewOption** object for the specified component.
 *
 * @param node Pointer to the component node.
 * @param option Pointer to the custom drag preview parameter object to be set on the target component.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_SetNodeDragPreviewOption(ArkUI_NodeHandle node, ArkUI_DragPreviewOption* option);

/**
 * @brief Creates a drag operation object, which must be associated with a UI instance. This can be specified by
 * passing in a component node of the current UI instance. After the object is used, you need to call
 * {@link OH_ArkUI_DragAction_Dispose} to dispose of it to prevent resource leaks.
 *
 * @param node Pointer to the component node.
 * @return Pointer to the **ArkUI_DragAction** object, which is used to configure and initiate a drag operation. If
 *     creation fails, null is returned.
 * @since 12
 */
ArkUI_DragAction* OH_ArkUI_CreateDragActionWithNode(ArkUI_NodeHandle node);

/**
 * @brief Creates a drag operation object, which must be associated with a UI instance. This can be associated by
 * passing in a UI instance pointer. After the object is used, you need to call
 * {@link OH_ArkUI_DragAction_Dispose} to dispose of it to prevent resource leaks.
 *
 * @param uiContext Pointer to the UI instance.
 * @return Pointer to the **ArkUI_DragAction** object, which is used to configure and initiate a drag operation. If
 *     creation fails, null is returned.
 * @since 12
 */
ArkUI_DragAction* OH_ArkUI_CreateDragActionWithContext(ArkUI_ContextHandle uiContext);

/**
 * @brief Disposes of an **ArkUI_DragAction** object.
 *
 * @param dragAction Pointer to the target drag action object.
 * @since 12
 */
void OH_ArkUI_DragAction_Dispose(ArkUI_DragAction* dragAction);

/**
 * @brief Sets the pointer ID. If only one finger is used on the screen, the finger ID is 0. Generally, you can set
 * this parameter to **0**.
 *
 * @param dragAction Pointer to the target drag action object.
 * @param pointer Pointer ID. The value ranges from 0 to 9. If the value is out of the range, **-1** is used by default.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragAction_SetPointerId(ArkUI_DragAction* dragAction, int32_t pointer);

/**
 * @brief Sets the drag previews for a drag action. Only pixel map objects are supported.
 *
 * @param dragAction Pointer to the target drag action object.
 * @param pixelmapArray Array of the drag previews to set, which must be pixel maps.
 *     <br>Note: This parameter must be an object allocated on the heap. You need to manually manage the lifecycle
 *     of the object.
 * @param size Number of drag previews. The value must be a positive integer and must match the actual number of
 *     elements in **pixelmapArray**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragAction_SetPixelMaps(
    ArkUI_DragAction* dragAction, OH_PixelmapNative* pixelmapArray[], int32_t size);

/**
 * @brief Sets the touch point relative to the upper left corner of the first drag preview (pixel map).
 *
 * @param dragAction Pointer to the target drag action object.
 * @param x X-coordinate of the touch point, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragAction_SetTouchPointX(ArkUI_DragAction* dragAction, float x);

/**
 * @brief Sets the touch point relative to the upper left corner of the first drag preview (pixel map).
 *
 * @param dragAction Pointer to the target drag action object.
 * @param y Y-coordinate of the touch point, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragAction_SetTouchPointY(ArkUI_DragAction* dragAction, float y);

/**
 * @brief Sets drag data. {@link OH_ArkUI_DragAction_SetDataLoadParams} should be used preferentially to provide
 * data loading parameters, so as to improve the efficiency of dragging large amounts of data and the efficiency of
 * processing dropped data in the target application. If this API conflicts with
 * {@link OH_ArkUI_DragAction_SetDataLoadParams}, the system always uses the last called API.
 *
 * @param dragAction Pointer to the target drag action object.
 * @param data Pointer to the drag data object to set.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragAction_SetData(ArkUI_DragAction* dragAction, OH_UdmfData* data);

/**
 * @brief Provides data loading parameters to the system instead of directly providing a complete data object.
 * When the user drops data on the target application, the system will use **dataLoadParams** to request data. This
 * can significantly improve the efficiency of dragging large volumes of data and the efficiency of processing the
 * dropped data in the target application. This API must always be used in preference to
 * {@link OH_ArkUI_DragAction_SetData}. For details about how to create and prepare data loading parameters, see
 * {@link OH_UdmfDataLoadParams_Create} in **udmf.h**. If this API conflicts with
 * {@link OH_ArkUI_DragAction_SetData}, the system always uses the last called API.
 *
 * @param dragAction Pointer to the target drag action object.
 * @param dataLoadParams Data loading parameters used during a drop operation.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_DragAction_SetDataLoadParams(ArkUI_DragAction* dragAction,
    OH_UdmfDataLoadParams* dataLoadParams);

/**
 * @brief Sets an **ArkUI_DragPreviewOption** object for the specified drag action object.
 *
 * @param dragAction Pointer to the target drag action object.
 * @param option Pointer to the custom drag preview parameter object to be set on **ArkUI_DragAction**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragAction_SetDragPreviewOption(ArkUI_DragAction* dragAction, ArkUI_DragPreviewOption* option);

/**
 * @brief Registers a drag status listener, which can perceive the status of the drag having been initiated or the
 * user having released to end. Through this listener, you can obtain whether the data receiving and processing by
 * the drop target is successful. When the drag status no longer needs to be listened for, you need to call
 * {@link OH_ArkUI_DragAction_UnregisterStatusListener} to unregister the listener.
 *
 * @param dragAction Pointer to the target drag action object.
 * @param userData Pointer to the user-defined data. After the status listener is registered, the data will be
 *     passed back through the **userData** parameter of the listener when the callback is triggered.
 * @param listener Pointer to the state listener callback. **dragAndDropInfo** indicates the pointer to the drag
 *     state object returned by the system. This pointer will be destroyed after the callback execution is
 *     complete, and the application should no longer hold it. **userData** indicates the user-defined data passed
 *     during registration.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_DragAction_RegisterStatusListener(ArkUI_DragAction* dragAction, void* userData,
    void(*listener)(ArkUI_DragAndDropInfo* dragAndDropInfo, void* userData));

/**
 * @brief Unregisters a drag status listener.
 *
 * @param dragAction Pointer to the target drag action object.
 * @since 12
 */
void OH_ArkUI_DragAction_UnregisterStatusListener(ArkUI_DragAction* dragAction);

/**
 * @brief Obtains the drag status of the {@link ArkUI_DragAction}. **ArkUI_DRAG_STATUS_UNKNOWN** is returned if the
 * acquisition fails.
 *
 * @param dragAndDropInfo Drag and drop information returned by the drag status listener.
 * @return Drag status. If the status fails to be obtained, the default value **ArkUI_DRAG_STATUS_UNKNOWN** is
 *     returned.
 * @since 12
 */
ArkUI_DragStatus OH_ArkUI_DragAndDropInfo_GetDragStatus(ArkUI_DragAndDropInfo* dragAndDropInfo);

/**
 * @brief Obtains **DragEvent** through **dragAndDropInfo**. **DragEvent** can be used to obtain the drop result.
 *
 * @param dragAndDropInfo Drag and drop information returned by the drag status listener.
 * @return Pointer to the drag event object. If the obtaining fails, null is returned.
 * @since 12
 */
ArkUI_DragEvent* OH_ArkUI_DragAndDropInfo_GetDragEvent(ArkUI_DragAndDropInfo* dragAndDropInfo);

/**
 * @brief Initiates a drag action through the specified **DragAction** object.
 *
 * @param dragAction Drag action object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_StartDrag(ArkUI_DragAction* dragAction);

/**
 * @brief Requests deferred processing of the drag end event, allowing the application to confirm the operation
 * result. The application must pass the final result back to the system via the
 * {@link OH_ArkUI_NotifyDragResult} API, and call {@link OH_ArkUI_NotifyDragEndPendingDone} after all processing is
 * complete. The maximum waiting time is 2 seconds.
 *
 * @param event Pointer to the target **ArkUI_DragEvent** object.
 * @param requestIdentify System-generated request identifier, which is an output parameter and must point to a valid
 *     address.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED} if the requested operation is not
 *     allowed in the current drag event processing phase.
 * @since 19
 */
int32_t OH_ArkUI_DragEvent_RequestDragEndPending(ArkUI_DragEvent* event, int32_t* requestIdentify);

/**
 * @brief Notifies the system of the final drag result. The system will verify whether the request identifier matches
 * that returned by {@link OH_ArkUI_DragEvent_RequestDragEndPending}. If they do not match, this call will be ignored.
 *
 * @param requestIdentify Identifier returned by {@link OH_ArkUI_DragEvent_RequestDragEndPending}.
 * @param result Enumerated value of the drag result (of the {@link ArkUI_DragResult} type).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED} if the requested operation is not
 *     allowed in the current drag event processing phase.
 * @since 19
 */
int32_t OH_ArkUI_NotifyDragResult(int32_t requestIdentify, ArkUI_DragResult result);

/**
 * @brief Notifies the drag initiator of the operation type of the current drop. This API must be called during the
 * drop phase. The drag initiator can call {@link OH_ArkUI_DragEvent_GetDropOperation} in the drag end callback to
 * obtain the operation type of the current drop and perform custom processing. The drag initiator can also ignore
 * the notification. If the drag operation fails, the operation type of the current drop is unreliable. In this
 * case, the operation type obtained by calling {@link OH_ArkUI_DragEvent_GetDropOperation} is always
 * **ARKUI_DROP_OPERATION_COPY**. The system will verify whether the value of **requestIdentity** is the same as
 * that returned by {@link OH_ArkUI_DragEvent_RequestDragEndPending}. If they are different, this API call does not
 * take effect.
 *
 * @param requestIdentity Identifier returned by {@link OH_ArkUI_DragEvent_RequestDragEndPending}, which is used to
 *     identify the drag event.
 * @param operation Operation type of the current drop.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED} if the API is not called in the drop phase.
 * @since 24
 */
int32_t OH_ArkUI_NotifySuggestedDropOperation(int32_t requestIdentity, ArkUI_DropOperation operation);

/**
 * @brief Notifies the system whether to disable the default drop animation. This API must be called during the
 * drop phase. If the drag fails, the default drop animation is diffusion. If the drag succeeds, the default drop
 * animation is shrinking and fading. Calling this API can disable the default animation and implement a custom
 * drop animation as required. The system will verify whether the value of **requestIdentity** is the same as that
 * returned by {@link OH_ArkUI_DragEvent_RequestDragEndPending}. If they are different, this API call does not take
 * effect.
 *
 * @param requestIdentity Identifier returned by {@link OH_ArkUI_DragEvent_RequestDragEndPending}, which is used to
 *     identify the drag event.
 * @param disable Whether to disable the default drop animation. **true** if disable; **false** otherwise.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED} if the API is not called in the drop phase.
 * @since 24
 */
int32_t OH_ArkUI_NotifyDisableDefaultDropAnimation(int32_t requestIdentity, bool disable);

/**
 * @brief Notifies the system that all asynchronous processing is complete and the drag end pending state can be
 * ended. The system will verify whether the value of **requestIdentify** matches the identifier returned by
 * {@link OH_ArkUI_DragEvent_RequestDragEndPending}. If they do not match or the current state is not in the drop
 * phase, this call does not take effect.
 *
 * @param requestIdentify Identifier returned by {@link OH_ArkUI_DragEvent_RequestDragEndPending}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED} if the requested operation is not
 *     allowed in the current drag event processing phase.
 * @since 19
 */
int32_t OH_ArkUI_NotifyDragEndPendingDone(int32_t requestIdentify);

 /**
  * @brief Sets whether the drop-disallowed badge can be displayed. This API is suitable for scenarios where a
  * drop-disallowed badge is needed to prompt the user when data is dragged to a target area that does not allow
  * dropping or does not support receiving the current data type.
  *
  * @param uiContext Pointer to the UI instance.
  * @param enabled Whether the drop-disallowed badge can be displayed. The value **true** means that the drop-
  *     disallowed badge can be displayed, and **false** means the opposite.
  * @return Result code.
  *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
  *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
  * @since 20
  */
ArkUI_ErrorCode OH_ArkUI_EnableDropDisallowedBadge(ArkUI_ContextHandle uiContext, bool enabled);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_DRAG_AND_DROP_H
/** @} */

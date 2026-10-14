/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @file error_code.h
 *
 * @brief Defines the error code for the native module.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_ERROR_CODE_H
#define ARKUI_NATIVE_ERROR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates error codes of ArkUI native APIs, which are used to indicate the results or failure causes of API
 * calls.
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief No error.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NO_ERROR = 0,
    /**
     * @brief Parameter error.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_PARAM_INVALID = 401,
    /**
     * @brief API initialization error.
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_CAPI_INIT_ERROR = 500,
    /**
     * @brief Internal error, such as API call failure due to abnormal running environment or operation failure caused
     * by API internal execution errors.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_INTERNAL_ERROR = 100001,
    /**
     * @brief Parameter error. For details about the error code, see {@link 100023 Parameter Error}.
     *
     * @since 21
     */
    ARKUI_ERROR_CODE_PARAM_ERROR = 100023,
    /**
     * @brief The **XComponent** is in an invalid or unsupported state. For details about the error code, see
     * {@link XComponent Error Codes}.
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_XCOMPONENT_STATE_INVALID = 103501,
    /**
     * @brief The component does not support specific attributes or events. For details, see
     * {@link Interaction Event Error Codes}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED = 106102,
    /**
     * @brief The corresponding operations cannot be performed on the node created by ArkTS.
     * For details about the error code, see {@link 106103 Operation Not Allowed on Nodes Created by ArkTS}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED = 106103,
    /**
     * @brief The adapter for lazy loading is not bound to the component. For details about the error code, see
     * {@link 106104 Adapter Not Bound}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ADAPTER_NOT_BOUND = 106104,
    /**
     * @brief The adapter already exists. For details about the error code, see {@link 106105 Adapter Already Exists}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ADAPTER_EXIST = 106105,
    /**
     * @brief Failed to add the adapter because the corresponding node already has a child node.
     * For details about the error code, see {@link 106106 Child Node Exists}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_CHILD_NODE_EXIST = 106106,
    /**
     * @brief The index parameter in the component event exceeds the array length limit. For details about the error
     * code, see {@link 106107 Index Out of Range}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE = 106107,
    /**
     * @brief The data requested by the caller does not exist in the component event. For details about the error code,
     * see {@link 106108 Data Not Found}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID = 106108,
    /**
     * @brief The component event does not support return values. For details about the error code, see
     * {@link 106109 Return Value Not Supported}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_EVENT_NO_RETURN = 106109,
    /**
     * @brief The event type is not supported. For details about the error code,
     * see {@link 106110 Unsupported Event Type}.
     *
     * @since 21
     */
    ARKUI_ERROR_CODE_NODE_UNSUPPORTED_EVENT_TYPE = 106110,
    /**
     * @brief Invalid index.<br>For details about the error code, see {@link 106200 Invalid Index Value}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_INDEX_INVALID = 106200,
    /**
     * @brief Failed to obtain the route navigation information.<br>For details about the error code, see
     * {@link 106201 Failed to Obtain Route Navigation Information}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_GET_INFO_FAILED = 106201,
    /**
     * @brief The buffer size passed is insufficient to accommodate the target data.<br>For details about the error
     * code, see {@link 106202 Invalid Buffer Size}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR = 106202,
    /**
     * @brief The passed node is not mounted to the component tree. For details about the error code, see
     * {@link 106203 Passed Node Not Mounted to Component Tree}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE = 106203,
    /**
     * @brief Operations on the provided node are not supported on non-UI threads. For details about the error code.
     * See {@link 106204 Operations on the Provided Node Not Supported on Non-UI Threads}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_ON_INVALID_THREAD = 106204,
    /**
     * @brief The input parameter for the color inversion capability is incorrect. For details about the error code,
     * see {@link 106205 Color Inversion Capability Configuration Error}.
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_FORCE_DARK_CONFIG_INVALID = 106205,
    /**
     * @brief The node has been accepted as an auxiliary node. For details about the error code, see
     * {@link 106206 The Node Has Been Accepted as an Auxiliary Node}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_IS_ADOPTED = 106206,
    /**
     * @brief The accepted node already has a parent node. For details about the error code, see
     * {@link 106207 The Auxiliary Node to Accept Has a Parent Node}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_HAS_PARENT = 106207,
    /**
     * @brief The node cannot be accepted as an auxiliary node. For details about the error code, see
     * {@link 106208 The Node Cannot Be Accepted as an Auxiliary Node}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_CAN_NOT_BE_ADOPTED = 106208,
    /**
     * @brief The node cannot accept other nodes. For details about the error code, see
     * {@link 106209 The Node Cannot Accept Other Nodes}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_CAN_NOT_ADOPT_TO = 106209,
    /**
     * @brief The node is not an auxiliary node accepted by the target node. For details about the error code, see
     * {@link 106210 The Node Is Not an Affiliated Node Accepted by the Target Node}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_IS_NOT_IN_ADOPTED_CHILDREN = 106210,
    /**
     * @brief Can not get attribute because it is not set before.
     * @since 26.0.1
     */
    ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND = 106211,
    /**
     * @brief The parameters of sub animation are invalid.
     * @since 26.0.1
     */
    ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID = 106212,
    /**
     * @brief The animation group is not found on the UIContext.
     * @since 26.0.1
     */
    ARKUI_ERROR_CODE_ANIMATION_GROUP_NOT_FOUND = 106213,
    /**
     * @brief A re-entrant call to the animation group API is detected on the same thread.
     * @since 26.0.1
     */
    ARKUI_ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL = 106214,
    /**
     * @brief The animation group is not in the state required by the operation.
     * @since 26.0.1
     */
    ARKUI_ERROR_CODE_ANIMATION_GROUP_INVALID_STATE = 106215,
    /**
     * @brief The resolved target node does not belong to the same UIContext as the context parameter.
     * @since 26.0.1
     */
    ARKUI_ERROR_CODE_TARGET_NODE_NOT_IN_SAME_CONTEXT = 106216,
    /**
     * @brief The current node is not a custom node. For details, see {@link Render Node Error Codes}.
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_NOT_CUSTOM_NODE = 106401,
    /**
     * @brief The current node already has child nodes. For details, see {@link Render Node Error Codes}.
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_CHILD_EXISTED = 106402,
    /**
     * @brief The current render node has a parent component. For details, see {@link Render Node Error Codes}.
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_RENDER_PARENT_EXISTED = 106403,
    /**
     * @brief Corresponding render child node not found. For details, see {@link Render Node Error Codes}.
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST = 106404,
    /**
     * @brief The parameter value is out of range. For details, see {@link Render Node Error Codes}.
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE = 106405,
    /**
     * @brief The current render node is obtained from a {@link FrameNode}. For details about the error code, see
     * {@link 106406 Current Render Node Is Obtained from FrameNode}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE = 106406,
    /**
     * @brief The current render node is obtained from a {@link FrameNode} and the {@link FrameNode} has not been
     * adopted as an affiliated node or has been disposed of. For details about the error code, see
     * {@link 106407 Current Render Node Is Obtained from FrameNode and the FrameNode Is Disposed or No Longer Adopted}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE = 106407,
    /**
     * @brief The current node is not in the adopted state. For details about the error code, see
     * {@link 106408 Current Node Is Not in Adopted State}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_NOT_ADOPTED_NODE = 106408,
    /**
     * @brief The last request was not finished.
     * @since 26.2.0
     */
    ARKUI_ERROR_CODE_COMMAND_UNFINISHED = 106409,
    /**
     * @brief The node corresponding to uniqueId is not found.
     * @since 26.2.0
     */
    ARKUI_ERROR_CODE_NODE_NOT_FOUND = 106410,
    /**
     * @brief result too large.
     * @since 26.2.0
     */
    ARKUI_ERROR_CODE_RESULT_TOO_LARGE = 106411,
    /**
     * @brief resource exhausted.
     * @since 26.2.0
     */
    ARKUI_ERROR_CODE_RESOURCE_EXHAUSTED = 106412,
    /**
     * @brief The current node is not focusable. For details about the error code, see
     * {@link 150001 Component Not Focusable}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE = 150001,
    /**
     * @brief An ancestor of the current node is not focusable. For details about the error code, see
     * {@link 150002 Ancestor Component Not Focusable}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE_ANCESTOR = 150002,
    /**
     * @brief The current node does not exist. For details about the error code, see
     * {@link 150003 Component Does Not Exist}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT = 150003,
    /**
     * @brief Snapshot timed out. For details, see {@link Snapshot Error Codes}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT = 160002,
    /**
     * @brief The color space or dynamic range mode set in the screenshot options is not supported. For details, see
     * {@link Snapshot Error Codes}.
     *
     * @since 23
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_MODE_NOT_SUPPORTED = 160003,
    /**
     * @brief The **isAuto** parameter corresponding to the color space or dynamic range mode cannot be set to **true**
     * for offscreen node screenshots. For details, see {@link Snapshot Error Codes}.
     *
     * @since 23
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_AUTO_NOT_SUPPORTED = 160004,
    /**
     * @brief The component is not a scrollable container. For details, see {@link Interaction Event Error Codes}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NON_SCROLLABLE_CONTAINER = 180001,
    /**
     * @brief Buffer is not large enough. For details, see {@link Interaction Event Error Codes}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH = 180002,
    /**
     * @brief The event is not a cloned event. For details, see {@link Interaction Event Error Codes}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT = 180003,
    /**
     * @brief The component status is abnormal. For details, see {@link Interaction Event Error Codes}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL = 180004,
    /**
     * @brief No component hit to respond to the event. For details, see {@link Interaction Event Error Codes}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_POST_CLONED_NO_COMPONENT_HIT_TO_RESPOND_TO_THE_EVENT = 180005,
    /**
     * @brief The API does not support this input event type. For details about the error code, see
     * {@link Interaction Event Error Codes}.
     *
     * @since 20
     */
    ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED = 180006,
    /**
     * @brief Invalid styled string. For details, see {@link Styled String Error Codes}.
     *
     * @since 14
     */
    ARKUI_ERROR_CODE_INVALID_STYLED_STRING = 180101,
    /**
     * @brief Invalid UIContext object. For details, see {@link UI Context Error Codes}.
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_UI_CONTEXT_INVALID = 190001,
    /**
     * @brief Invalid callback function. For details, see {@link UI Context Error Codes}.
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_CALLBACK_INVALID = 190002,
    /**
     * @brief The gesture recognizer type is not supported. For details, see {@link Interaction Event Error Codes}.
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED = 180102,
    /**
     * @brief The requested operation is not allowed in the current drag and drop event processing phase. For details,
     * see {@link Drag Event Error Codes}.
     *
     * @since 19
     */
    ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED = 190004,
    /**
     * @brief The dialog box cannot be opened because the node fails to be mounted. For details, see
     * {@link Popup Window Error Codes}.
     *
     * @since 26.0.1
     */
    ARKUI_ERROR_CODE_DIALOG_NODE_MOUNT_FAILURE = 103306,
    /**
     * @brief The dialog box cannot be opened because the subwindow fails to be created. For details, see
     * {@link Popup Window Error Codes}.
     *
     * @since 26.0.1
     */
    ARKUI_ERROR_CODE_DIALOG_SUBWINDOW_CREATE_FAILURE = 103308,
} ArkUI_ErrorCode;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_ERROR_CODE_H
/** @} */

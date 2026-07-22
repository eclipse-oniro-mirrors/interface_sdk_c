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
 * @brief Enumerates the error codes.
 *
 * @since 12
 */
typedef enum {
    /**
     * No error.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NO_ERROR = 0,
    /**
     * Parameter error.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_PARAM_INVALID = 401,
    /**
     * API initialization error.
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_CAPI_INIT_ERROR = 500,
    /**
     * Internal error, such as failure due to internal environment issues or operation failure caused by internal
     * execution errors.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_INTERNAL_ERROR = 100001,
    /**
     * Parameter error. For details about the error code, see {@link 100023 Parameter Error}.
     *
     * @since 21
     */
    ARKUI_ERROR_CODE_PARAM_ERROR = 100023,
    /**
     * The **XComponent** is in an invalid or unsupported state. For details, see {@link XComponent Error Codes}.
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_XCOMPONENT_STATE_INVALID = 103501,
    /**
     * The component does not support specific attributes or events. For details, see
     * {@link Interaction Event Error Codes}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED = 106102,
    /**
     * The corresponding operations cannot be performed on the node created by ArkTS. For details about the error code,
     * see {@link 106103 Operation Not Allowed on Nodes Created by ArkTS}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED = 106103,
    /**
     * The adapter for lazy loading is not bound to the component. For details about the error code, see
     * {@link 106104 Adapter Not Bound}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ADAPTER_NOT_BOUND = 106104,
    /**
     * The adapter already exists. For details about the error code, see {@link 106105 Adapter Already Exists}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ADAPTER_EXIST = 106105,
    /**
     * Failed to add the adapter because the corresponding node already has a subnode. For details about the error code,
     * see {@link 106106 Child Node Exists}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_CHILD_NODE_EXIST = 106106,
    /**
     * The parameter length in the parameter event exceeds the limit. For details about the error code, see
     * {@link 106107 Index Out of Range}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE = 106107,
    /**
     * The data does not exist in the component event. For details about the error code, see
     * {@link 106108 Data Not Found}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID = 106108,
    /**
     * The component event does not support return values. For details about the error code, see
     * {@link 106109 Return Value Not Supported}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_EVENT_NO_RETURN = 106109,
    /**
     * This event type is not supported. For details about the error code, see {@link 106110 Unsupported Event Type}.
     *
     * @since 21
     */
    ARKUI_ERROR_CODE_NODE_UNSUPPORTED_EVENT_TYPE = 106110,
    /**
     * Invalid index.<br>For details about the error code, see {@link 106200 Invalid Index Value}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_INDEX_INVALID = 106200,
    /**
     * Failed to obtain the route navigation information.<br>For details about the error code, see
     * {@link 106201 Failed to Obtain Route Navigation Information}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_GET_INFO_FAILED = 106201,
    /**
     * The passed buffer size is invalid (the data is too large).<br>For details about the error code, see
     * {@link 106202 Invalid Buffer Size}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR = 106202,
    /**
     * The passed node is not mounted to the component tree. For details about the error code, see
     * {@link 106203 Passed Node Not Mounted to Component Tree}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE = 106203,
    /**
     * Operations on the provided node are not supported on non-UI threads. For details about the error code, see
     * {@link 106204 Operations on the Provided Node Not Supported on Non-UI Threads}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_ON_INVALID_THREAD = 106204,
    /**
     * The input parameter for the color inversion capability is incorrect. For details about the error code, see
     * {@link 106205 Invalid Input Parameter for the Color Inversion Capability}.
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_FORCE_DARK_CONFIG_INVALID = 106205,
    /**
     * The node has been accepted as an auxiliary node. For details about the error code, see
     * {@link 106206 The Node Has Been Accepted as an Auxiliary Node}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_IS_ADOPTED = 106206,
    /**
     * The accepted node already has a parent node. For details about the error code, see
     * {@link 106207 The Auxiliary Node to Accept Has a Parent Node}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_HAS_PARENT = 106207,
    /**
     * The node cannot be accepted as an auxiliary node. For details about the error code, see
     * {@link 106208 The Node Cannot Be Accepted as an Auxiliary Node}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_CAN_NOT_BE_ADOPTED = 106208,
    /**
     * The node cannot accept other nodes. For details about the error code, see
     * {@link 106209 The Node Cannot Accept Other Nodes}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_CAN_NOT_ADOPT_TO = 106209,
    /**
     * The node is not an auxiliary node accepted by the target node. For details about the error code, see
     * {@link 106210 The Node Is Not an Affiliated Node Accepted by the Target Node}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_IS_NOT_IN_ADOPTED_CHILDREN = 106210,
    /**
     * The current node is not a custom node. For details, see {@link Render Node Error Codes}.
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_NOT_CUSTOM_NODE = 106401,
    /**
     * The current node already has child nodes. For details, see {@link Render Node Error Codes}.
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_CHILD_EXISTED = 106402,
    /**
     * The current render node has a parent component. For details, see {@link Render Node Error Codes}.
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_RENDER_PARENT_EXISTED = 106403,
    /**
     * Corresponding render child node not found. For details, see {@link Render Node Error Codes}.
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST = 106404,
    /**
     * The parameter value is out of range. For details, see {@link Render Node Error Codes}.
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE = 106405,
    /**
     * The current render node is obtained from a {@link FrameNode}. For details about the error code, see
     * {@link 106406 Current Render Node Is Obtained from FrameNode}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE = 106406,
    /**
     * The current render node is obtained from a {@link FrameNode} and the {@link FrameNode} has not been adopted as
     * an affiliated node or has been disposed of. For details about the error code, see
     * {@link 106407 Current Render Node Is Obtained from FrameNode and the FrameNode Is Disposed or No Longer Adopted}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE = 106407,
    /**
     * The current node is not in the adopted state. For details about the error code, see
     * {@link 106408 Current Node Is Not in Adopted State}.
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_NOT_ADOPTED_NODE = 106408,
    /**
     * The current node is not focusable. For details about the error code, see {@link 150001 Component Not Focusable}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE = 150001,
    /**
     * An ancestor of the current node is not focusable. For details about the error code, see
     * {@link 150002 Ancestor Component Not Focusable}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE_ANCESTOR = 150002,
    /**
     * The current node does not exist. For details about the error code, see {@link 150003 Component Does Not Exist}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT = 150003,
    /**
     * Snapshot timed out. For details, see {@link Snapshot Error Codes}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT = 160002,
    /**
     * The provided color space or dynamic range mode is not supported. For details, see {@link Snapshot Error Codes}.
     *
     * @since 23
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_MODE_NOT_SUPPORTED = 160003,
    /**
     * The **isAuto** setting of the color space or dynamic range mode is not supported for offscreen node snapshots.
     * For details, see {@link Snapshot Error Codes}.
     *
     * @since 23
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_AUTO_NOT_SUPPORTED = 160004,
    /**
     * The component is not a scrollable container. For details, see {@link Interaction Event Error Codes}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NON_SCROLLABLE_CONTAINER = 180001,
    /**
     * The buffer is not large enough. For details, see {@link Interaction Event Error Codes}.
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH = 180002,
    /**
     * The event is not a cloned event. For details, see {@link Interaction Event Error Codes}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT = 180003,
    /**
     * The component status is abnormal. For details, see {@link Interaction Event Error Codes}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL = 180004,
    /**
     * No component hit to respond to the event. For details, see {@link Interaction Event Error Codes}.
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_POST_CLONED_NO_COMPONENT_HIT_TO_RESPOND_TO_THE_EVENT = 180005,
    /**
     * Input event type not supported.
     *
     * @since 20
     */
    ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED = 180006,
    /**
     * Invalid styled string. For details, see {@link Styled String Error Codes}.
     *
     * @since 14
     */
    ARKUI_ERROR_CODE_INVALID_STYLED_STRING = 180101,
    /**
     * Invalid UIContext object. For details, see {@link UI Context Error Codes}.
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_UI_CONTEXT_INVALID = 190001,
    /**
     * Invalid callback function. For details, see {@link UI Context Error Codes}.
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_CALLBACK_INVALID = 190002,
    /**
     * The gesture recognizer type is not supported. For details, see {@link Interaction Event Error Codes}.
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED = 180102,
    /**
     * The operation is not allowed in the current phase. For details, see {@link Drag Event Error Codes}.
     *
     * @since 19
     */
    ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED = 190004,
    /**
     * The dialog cannot be opened due to node mount failure. For details, see {@link promptAction Error Codes}.
     * @since 26.1.0
     */
    ARKUI_ERROR_CODE_DIALOG_NODE_MOUNT_FAILURE = 103306,
    /**
     * The dialog cannot be opened due to subwindow create failure. For details, see {@link promptAction Error Codes}.
     * @since 26.1.0
     */
    ARKUI_ERROR_CODE_DIALOG_SUBWINDOW_CREATE_FAILURE = 103308,
} ArkUI_ErrorCode;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_ERROR_CODE_H
/** @} */

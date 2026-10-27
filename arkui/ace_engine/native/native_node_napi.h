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
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 12
 */

/**
 * @file native_node_napi.h
 *
 * @brief Declares APIs for converting <b>FrameNode</b> objects on the ArkTS side to <b>ArkUI_NodeHandle</b> objects on
 * the native side.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_NAPI_H
#define ARKUI_NATIVE_NODE_NAPI_H

#include "drawable_descriptor.h"
#include "napi/native_api.h"
#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Obtains an <b>ArkUI_NodeHandle</b> object on the native side mapped from the <b>FrameNode</b> object created
 * on the ArkTS side. This is applicable to scenarios where the native side needs to operate on or manage a FrameNode
 * on the ArkTS side.
 *
 * @param env Pointer to the Node-API environment.
 * @param frameNode <b>FrameNode</b> object created on the ArkTS side.
 * @param handle Pointer to the <b>ArkUI_NodeHandle</b>.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs. Check whether the passed
 *         parameters <b>env</b>, <b>frameNode</b>, and <b>handle</b> are valid.
 * @since 12
 */
int32_t OH_ArkUI_GetNodeHandleFromNapiValue(napi_env env, napi_value frameNode, ArkUI_NodeHandle* handle);

/**
 * @brief Obtains an <b>ArkUI_ContextHandle</b> object on the native side mapped from the UIContext object created on
 * the ArkTS side. This is applicable to scenarios where the native side needs to invoke ArkUI capabilities based on
 * <b>UIContext</b>.
 *
 * @param env Pointer to the Node-API environment.
 * @param value <b>UIContext</b> object created on the ArkTS side.
 * @param context Pointer to the <b>ArkUI_ContextHandle</b>.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs. Check whether the passed
 *         parameters <b>env</b>, <b>value</b>, and <b>context</b> are valid.
 * @since 12
 */
int32_t OH_ArkUI_GetContextFromNapiValue(napi_env env, napi_value value, ArkUI_ContextHandle* context);


/**
 * @brief Obtains an <b>ArkUI_NodeContentHandle</b> object on the native side mapped from the <b>NodeContent</b> object
 * created on the ArkTS side. This is applicable to scenarios where the native side needs to operate on or mount the
 * <b>NodeContent</b> content on the ArkTS side.
 *
 * @param env Pointer to the Node-API environment.
 * @param value <b>NodeContent</b> object created on the ArkTS side.
 * @param content Pointer to the <b>ArkUI_NodeContentHandle</b>.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs. Check whether the passed
 *         parameters <b>env</b>, <b>value</b>, and <b>content</b> are valid.
 * @since 12
 */
int32_t OH_ArkUI_GetNodeContentFromNapiValue(napi_env env, napi_value value, ArkUI_NodeContentHandle* content);

/**
 * @brief Obtains an {@link ArkUI_DrawableDescriptor} object on the native side mapped from the DrawableDescriptor
 * object created on the ArkTS side. This is applicable to scenarios where the native side needs to use an image
 * resource description object on the ArkTS side.
 *
 * @param env Pointer to the Node-API environment.
 * @param value DrawableDescriptor object created on the ArkTS side.
 * @param drawableDescriptor Double pointer used to receive the <b>ArkUI_DrawableDescriptor</b> object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs. Check whether the passed
 *         parameters <b>env</b>, <b>value</b>, and <b>drawableDescriptor</b> are valid.
 * @since 12
 */
int32_t OH_ArkUI_GetDrawableDescriptorFromNapiValue(
    napi_env env, napi_value value, ArkUI_DrawableDescriptor** drawableDescriptor);

/**
 * @brief Converts a resource object obtained through <b>$r()</b> on the ArkTS side into an
 * {@link ArkUI_DrawableDescriptor} object usable on the native side. This is applicable to scenarios where the native
 * side needs to use an ArkTS resource object as an image resource descriptor.
 *
 * @param env Pointer to the Node-API environment.
 * @param value Resource object obtained by <b>$r()</b> on the ArkTS side.
 * @param drawableDescriptor Double pointer used to receive the <b>ArkUI_DrawableDescriptor</b> object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs. Check whether the passed
 *         parameters <b>env</b>, <b>value</b>, and <b>drawableDescriptor</b> are valid.
 * @since 12
 */
int32_t OH_ArkUI_GetDrawableDescriptorFromResourceNapiValue(
    napi_env env, napi_value value, ArkUI_DrawableDescriptor** drawableDescriptor);

/**
 * @brief Obtains the ID of the Navigation component where the specified node is located.
 *
 * @param node Target node.
 * @param buffer Pointer to the buffer to which the obtained ID is written.
 * @param bufferSize Buffer size.
 * @param writeLength Pointer to the length of the string actually written to the buffer if
 *                    {@link ARKUI_ERROR_CODE_NO_ERROR} is returned. Pointer to the minimum size of the buffer required
 *                    to hold the target when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_GET_INFO_FAILED} if the information fails to be obtained, possibly because
 *         the current node is not mounted to the page.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the data size exceeds the specified buffer size.
 * @since 12
 */
ArkUI_ErrorCode  OH_ArkUI_GetNavigationId(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the name of the NavDestination component where the specified node is located.
 *
 * @param node Target node.
 * @param buffer Pointer to the buffer to which the obtained name is written.
 * @param bufferSize Buffer size.
 * @param writeLength Pointer to the length of the string actually written to the buffer if
 *                    {@link ARKUI_ERROR_CODE_NO_ERROR} is returned. Pointer to the minimum size of the buffer required
 *                    to hold the target when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_GET_INFO_FAILED} if the information fails to be obtained, possibly because
 *         the current node is not mounted to the page.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the specified buffer size is smaller than the minimum
 *         buffer size required to hold the target.
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetNavDestinationName(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the length of the Navigation stack where the specified node is located.
 *
 * @param node Target node.
 * @param length Pointer to the length of the navigation stack. The result, if obtained successfully, is written back
 *               to this parameter.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_GET_INFO_FAILED} if the information fails to be obtained, possibly because
 *         the current node is not mounted to the page.
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetNavStackLength(ArkUI_NodeHandle node, int32_t* length);

/**
 * @brief Obtains the name of the page in the navigation stack where the specified node is located based on the given
 * index. The index starts from 0, which indicates the bottom of the stack.
 *
 * @param node Target node.
 * @param index Index of the target page in the navigation stack.
 * @param buffer Pointer to the buffer to which the obtained name is written.
 * @param bufferSize Buffer size.
 * @param writeLength Pointer to the length of the string actually written to the buffer if
 *                    {@link ARKUI_ERROR_CODE_NO_ERROR} is returned. Pointer to the minimum size of the buffer required
 *                    to hold the target when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_INDEX_INVALID} if the index is invalid.
 *     <br>Returns {@link ARKUI_ERROR_CODE_GET_INFO_FAILED} if the information fails to be obtained, possibly because
 *         the current node is not mounted to the page.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the specified buffer size is smaller than the minimum
 *         buffer size required to hold the target.
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetNavDestinationNameByIndex(
    ArkUI_NodeHandle node, int32_t index, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the ID of the NavDestination component where the specified node is located.
 *
 * @param node Target node.
 * @param buffer Pointer to the buffer to which the obtained ID is written.
 * @param bufferSize Buffer size.
 * @param writeLength Pointer to the length of the string actually written to the buffer if
 *                    {@link ARKUI_ERROR_CODE_NO_ERROR} is returned. Pointer to the minimum size of the buffer required
 *                    to hold the target when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_GET_INFO_FAILED} if the information fails to be obtained, possibly because
 *         the current node is not mounted to the page.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the data size exceeds the specified buffer size.
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetNavDestinationId(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the state of the NavDestination component where the specified node is located.
 *
 * @param node Target node.
 * @param state Pointer to the state of the NavDestination component. The result, if obtained successfully, is written
 *              back to this parameter.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_GET_INFO_FAILED} if the information fails to be obtained, possibly because
 *         the current node is not mounted to the page.
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetNavDestinationState(ArkUI_NodeHandle node, ArkUI_NavDestinationState* state);

/**
 * @brief Obtains the index of the NavDestination component where the current node is located in the page stack.
 *
 * @param node Target node.
 * @param index Pointer to the zero-based index.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_GET_INFO_FAILED} if the information fails to be obtained, possibly because
 *         the current node is not mounted to the page.
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetNavDestinationIndex(ArkUI_NodeHandle node, int32_t* index);

/**
 * @brief Obtains the parameter of the NavDestination component where the specified node is located.
 *
 * @param node Target node.
 * @return Parameter object. Returns an empty value if the parameters do not exist or the specified node is null.
 * @since 12
 */
napi_value OH_ArkUI_GetNavDestinationParam(ArkUI_NodeHandle node);

/**
 * @brief Obtains the index of the Router page stack where the specified node is located.
 *
 * @param node Target node.
 * @param index Pointer to the one-based index.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the specified node or the passed index is invalid.
 *     <br>Returns {@link ARKUI_ERROR_CODE_GET_INFO_FAILED} if the information fails to be obtained, possibly because
 *         the current node is not mounted to the page.
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetRouterPageIndex(ArkUI_NodeHandle node, int32_t* index);

/**
 * @brief Obtains the name of the Router page where the specified node is located.
 *
 * @param node Target node.
 * @param buffer Pointer to the buffer to which the obtained name is written.
 * @param bufferSize Buffer size.
 * @param writeLength Pointer to the length of the string actually written to the buffer if
 *                    {@link ARKUI_ERROR_CODE_NO_ERROR} is returned. Pointer to the minimum size of the buffer required
 *                    to hold the target when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_GET_INFO_FAILED} if the information fails to be queried.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the specified buffer size is smaller than the minimum
 *         buffer size required to hold the target.
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetRouterPageName(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the path of the Router page where the specified node is located.
 *
 * @param node Target node.
 * @param buffer Pointer to the buffer to which the page path is written.
 * @param bufferSize Buffer size.
 * @param writeLength Pointer to the length of the string actually written to the buffer if
 *                    {@link ARKUI_ERROR_CODE_NO_ERROR} is returned. Pointer to the minimum size of the buffer required
 *                    to hold the target when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_GET_INFO_FAILED} if the information fails to be queried.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the specified buffer size is smaller than the minimum
 *         buffer size required to hold the target.
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetRouterPagePath(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength);
/**
 * @brief Obtains the status of the Router page where the specified node is located.
 *
 * @param node Target node.
 * @param state Pointer to the status of the Router page. The result, if obtained successfully, is written back to
 *              this parameter.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_GET_INFO_FAILED} if the information fails to be queried.
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetRouterPageState(ArkUI_NodeHandle node, ArkUI_RouterPageState* state);

/**
 * @brief Obtains the ID of the Router page where the specified node is located.
 *
 * @param node Target node.
 * @param buffer Pointer to the buffer to which the page ID is written.
 * @param bufferSize Buffer size.
 * @param writeLength Pointer to the length of the string actually written to the buffer if
 *                    {@link ARKUI_ERROR_CODE_NO_ERROR} is returned. Pointer to the minimum size of the buffer required
 *                    to hold the target when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_GET_INFO_FAILED} if the information fails to be queried.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the data size exceeds the specified buffer size.
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetRouterPageId(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Register a callback to be executed when rendering in the next frame. Cannot be called on
 *        the non-UI thread. Checking for non-UI thread calls will abort.
 *
 * @param uiContext ArkUI_ContextHandle.
 * @param userData Indicates the custom data to be saved.
 * @param callback Custom callback function.
 * @param nanoTimestamp Timestamp of frame signal.
 * @param frameCount Frame count.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if the CAPI init error.
 *         Returns {@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if the uiContext is invalid.
 *         Returns {@link ARKUI_ERROR_CODE_CALLBACK_INVALID} if the callback function is invalid.
 * @since 18
 */
int32_t OH_ArkUI_PostFrameCallback(ArkUI_ContextHandle uiContext, void* userData,
    void (*callback)(uint64_t nanoTimestamp, uint32_t frameCount, void* userData));

/**
 * @brief Initializes ArkUI-related APIs for the specified context environment. This is applicable to scenarios where
 * the context environment needs to be initialized before the native side uses ArkUI-related APIs. This API must not be
 * called on a non-UI thread; otherwise, the program will actively abort. After the specified context environment is
 * initialized using this API, call {@link OH_ArkUI_NotifyArkTSEnvDestroy} to notify that the environment has been
 * destroyed when the corresponding environment is destroyed.
 *
 * @param env Pointer to the Node-API environment.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs. The possible cause is that
 *         <b>env</b> is null or the trustlist setting fails. Verify that <b>env</b> is valid and try again.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if a C API initialization error occurs. Verify that the
 *         current running environment supports ArkUI native APIs and try again.
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_InitModuleForArkTSEnv(napi_env env);

/**
 * @brief Notifies that the specified context environment has been destroyed. This is applicable to scenarios where the
 * native side synchronously cleans up related states when the ArkTS context environment is destroyed. After the
 * context environment is initialized using {@link OH_ArkUI_InitModuleForArkTSEnv}, this API should be called when the
 * environment is destroyed. This API must not be called on a non-UI thread; otherwise, the program will actively abort.
 *
 * @param env Pointer to the Node-API environment.
 * @since 20
 */
void OH_ArkUI_NotifyArkTSEnvDestroy(napi_env env);

/**
 * @brief Registers a callback. This is applicable to scenarios where the native side needs to use the idle time
 * between frames to process non-urgent tasks. After the next frame is rendered, if the remaining time before the next
 * VSync signal following that frame is greater than 1 ms, the callback will be executed; if the remaining time is less
 * than 1 ms, the callback will be postponed until the remaining time after a subsequent frame is rendered is greater
 * than 1 ms. If there is no next frame currently, the next frame will be requested automatically. This API must not be
 * called on a non-UI thread; otherwise, the program will actively abort.
 *
 * @param uiContext <b>UIContext</b> object handle, which is used to bind an instance.
 * @param userData Pointer to the custom event parameter, which is passed in the callback when the custom callback is
 *                 triggered.
 * @param callback Pointer to the custom callback with the signature <b>void (*callback)(uint64_t nanoTimeLeft,
 *                 uint32_t frameCount, void* userData)</b>, which is executed after the next frame is rendered when the
 *                 remaining time is greater than 1 ms. <b>nanoTimeLeft</b> indicates the remaining time before the
 *                 deadline of the current frame, <b>frameCount</b> indicates the frame number, and <b>userData</b>
 *                 indicates the custom data passed in during registration and carried back when the callback is
 *                 triggered.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if a C API initialization error occurs. Ensure that the
 *         ArkUI native API running environment has been initialized and try again.
 *     <br>Returns {@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if the <b>UIContext</b> object is invalid. Check whether
 *         <b>UIContext</b> is null or invalid.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CALLBACK_INVALID} if the callback is invalid. Check whether callback is null.
 * @since 20
 */
int32_t OH_ArkUI_PostIdleCallback(ArkUI_ContextHandle uiContext, void* userData,
    void (*callback)(uint64_t nanoTimeLeft, uint32_t frameCount, void* userData));

/**
 * @brief Enables or disables event passthrough. Event passthrough indicates that an event is directly delivered to a
 * component without resampling during event distribution.
 *
 * @param uiContext UIContext object, which is used to bind an instance.
 * @param enabled Whether to enable event passthrough. <b>true</b> to enable; <b>false</b> otherwise.
 * @param type Raw input event type {@link ArkUI_RawInputEventType} for enabling or disabling event passthrough.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the UIContext object is invalid.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_EnableEventPassthrough(ArkUI_ContextHandle uiContext, bool enabled,
    ArkUI_RawInputEventType type);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_NODE_NAPI_H
/** @} */

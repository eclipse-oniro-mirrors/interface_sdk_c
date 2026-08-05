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
 * @brief 提供ArkTS侧的{@link FrameNode}转换{@link NodeHandle}的方式。
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
 * @brief 获取ArkTS侧创建的FrameNode节点对象映射到Native侧的ArkUI_NodeHandle。
 *
 * @param env Node-API的环境指针。
 * @param frameNode ArkTS侧创建的FrameNode对象。
 * @param handle ArkUI_NodeHandle指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_GetNodeHandleFromNapiValue(napi_env env, napi_value frameNode, ArkUI_NodeHandle* handle);

/**
 * @brief 获取ArkTS侧创建的{@link UIContext}对象映射到Native侧的ArkUI_ContextHandle。
 *
 * @param env napi的环境指针。
 * @param value ArkTS侧创建的context对象。
 * @param context ArkUI_ContextHandle指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_GetContextFromNapiValue(napi_env env, napi_value value, ArkUI_ContextHandle* context);

/**
 * @brief 获取ArkTS侧创建的NodeContent对象映射到Native侧的ArkUI_NodeContentHandle。
 *
 * @param env napi的环境指针。
 * @param value ArkTS侧创建的NodeContent对象。
 * @param content ArkUI_NodeContentHandle指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_GetNodeContentFromNapiValue(napi_env env, napi_value value, ArkUI_NodeContentHandle* content);

/**
 * @brief 将ArkTS侧创建的{@link DrawableDescriptor}对象映射到Native侧的{@link ArkUI_DrawableDescriptor}。
 *
 * @param env napi的环境指针。
 * @param value ArkTS侧创建的{@link DrawableDescriptor}对象。
 * @param drawableDescriptor 接受ArkUI_DrawableDescriptor指针的对象。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_GetDrawableDescriptorFromNapiValue(
    napi_env env, napi_value value, ArkUI_DrawableDescriptor** drawableDescriptor);

/**
 * @brief 将ArkTS侧通过$r()获取的资源对象转换为Native侧可使用的{@link ArkUI_DrawableDescriptor}对象。
 *
 * @param env napi的环境指针。
 * @param value ArkTS侧创建的$r资源对象。
 * @param drawableDescriptor 接受ArkUI_DrawableDescriptor指针的对象。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_GetDrawableDescriptorFromResourceNapiValue(
    napi_env env, napi_value value, ArkUI_DrawableDescriptor** drawableDescriptor);

/**
 * @brief 获取当前节点所在的{@link Navigation}组件的ID。
 *
 * @param node 指定的节点。
 * @param buffer 缓冲区，NavigationID写入该内存区域。
 * @param bufferSize 缓冲区大小。
 * @param writeLength 在返回{@link ARKUI_ERROR_CODE_NO_ERROR}时表示实际写入到缓冲区的字符串长度。
 *     <br>在返回{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}时表示可以容纳目标的最小缓冲区大小。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_GET_INFO_FAILED} 查询信息失败，可能因为当前节点未挂载在页面下。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 数据大小超过指定的缓冲区大小。
 * @since 12
 */
ArkUI_ErrorCode  OH_ArkUI_GetNavigationId(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取当前节点所在的{@link NavDestination}组件的名称。
 *
 * @param node 指定的节点。
 * @param buffer 缓冲区，被查询的NavDestination名称写入该内存区域。
 * @param bufferSize 缓冲区大小。
 * @param writeLength 在返回{@link ARKUI_ERROR_CODE_NO_ERROR}时表示实际写入到缓冲区的字符串长度。
 *     <br>在返回{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}时表示可以容纳目标的最小缓冲区大小。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_GET_INFO_FAILED} 查询信息失败，可能因为当前节点未挂载在页面下。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 给定的buffer size小于可以容纳目标的最小缓冲区大小。
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetNavDestinationName(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取当前节点所在的Navigation栈的长度。
 *
 * @param node 指定的节点。
 * @param length 栈的长度。查询成功后将结果写回该参数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_GET_INFO_FAILED} 查询信息失败，可能因为当前节点未挂载在页面下。
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetNavStackLength(ArkUI_NodeHandle node, int32_t* length);

/**
 * @brief 根据给定索引值，获取当前节点所在的Navigation栈中的页面名称。索引值从0开始计数，0为栈底。
 *
 * @param node 指定的节点。
 * @param index 被查询NavDestination在栈中的索引。
 * @param buffer 缓冲区，被查询页面的名称写入该内存区域。
 * @param bufferSize 缓冲区大小。
 * @param writeLength 在返回{@link ARKUI_ERROR_CODE_NO_ERROR}时表示实际写入到缓冲区的字符串长度。
 *     <br>在返回{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}时表示可以容纳目标的最小缓冲区大小。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_NODE_INDEX_INVALID} index为非法值。
 *     <br>{@link ARKUI_ERROR_CODE_GET_INFO_FAILED} 查询信息失败，可能因为当前节点未挂载在页面下。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 给定的buffer size小于可以容纳目标的最小缓冲区大小。
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetNavDestinationNameByIndex(
    ArkUI_NodeHandle node, int32_t index, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取当前节点所在的NavDestination组件的ID。
 *
 * @param node 指定的节点。
 * @param buffer 缓冲区，NavDestinationID写入该内存区域。
 * @param bufferSize 缓冲区大小。
 * @param writeLength 在返回{@link ARKUI_ERROR_CODE_NO_ERROR}时表示实际写入到缓冲区的字符串长度。
 *     <br>在返回{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}时表示可以容纳目标的最小缓冲区大小。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_GET_INFO_FAILED} 查询信息失败，可能因为当前节点未挂载在页面下。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 数据大小超过指定的缓冲区大小。
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetNavDestinationId(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取当前节点所在的NavDestination组件的状态。
 *
 * @param node 指定的节点。
 * @param state NavDestination的状态值写回该参数中。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_GET_INFO_FAILED} 查询信息失败，可能因为当前节点未挂载在页面下。
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetNavDestinationState(ArkUI_NodeHandle node, ArkUI_NavDestinationState* state);

/**
 * @brief 获取当前节点所在的NavDestination组件在页面栈的索引。
 *
 * @param node 指定的节点。
 * @param index 索引值，从0开始计数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_GET_INFO_FAILED} 查询信息失败，可能因为当前节点未挂载在页面下。
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetNavDestinationIndex(ArkUI_NodeHandle node, int32_t* index);

/**
 * @brief 获取当前节点所在的NavDestination组件的参数。
 *
 * @param node 指定的节点。
 * @return 参数对象。如返回为空，则说明参数不存在或指定的节点为空。
 * @since 12
 */
napi_value OH_ArkUI_GetNavDestinationParam(ArkUI_NodeHandle node);

/**
 * @brief 获取当前节点所在{@link Router}页面栈中的索引。
 *
 * @param node 指定的节点。
 * @param index 索引值，从1开始计数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 指定的节点或传递的索引异常。
 *     <br>{@link ARKUI_ERROR_CODE_GET_INFO_FAILED} 查询信息失败，可能因为当前节点未挂载在页面下。
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetRouterPageIndex(ArkUI_NodeHandle node, int32_t* index);

/**
 * @brief 获取当前节点所在Router页面的名称。
 *
 * @param node 指定的节点。
 * @param buffer 缓冲区，页面名称写入该内存区域。
 * @param bufferSize 缓冲区大小。
 * @param writeLength 在返回{@link ARKUI_ERROR_CODE_NO_ERROR}时表示实际写入到缓冲区的字符串长度。
 *     <br>在返回{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}时表示可以容纳目标的最小缓冲区大小。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_GET_INFO_FAILED} 查询信息失败。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 给定的buffer size小于可以容纳目标的最小缓冲区大小。
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetRouterPageName(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief 获取当前节点所在Router页面的路径。
 *
 * @param node 指定的节点。
 * @param buffer 缓冲区，页面路径写入该内存区域。
 * @param bufferSize 缓冲区大小。
 * @param writeLength 在返回{@link ARKUI_ERROR_CODE_NO_ERROR}时表示实际写入到缓冲区的字符串长度。
 *     <br>在返回{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}时表示可以容纳目标的最小缓冲区大小。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_GET_INFO_FAILED} 查询信息失败。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 给定的buffer size小于可以容纳目标的最小缓冲区大小。
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetRouterPagePath(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength);
/**
 * @brief 获取当前节点所在Router页面的状态。
 *
 * @param node 指定的节点。
 * @param state Router页面的状态值写回该参数中。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_GET_INFO_FAILED} 查询信息失败。
 * @since 12
 */
ArkUI_ErrorCode OH_ArkUI_GetRouterPageState(ArkUI_NodeHandle node, ArkUI_RouterPageState* state);

/**
 * @brief 获取当前节点所在Router页面的ID。
 *
 * @param node 指定的节点。
 * @param buffer 缓冲区，页面ID写入该内存区域。
 * @param bufferSize 缓冲区大小。
 * @param writeLength 在返回{@link ARKUI_ERROR_CODE_NO_ERROR}时表示实际写入到缓冲区的字符串长度。
 *     <br>在返回{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}时表示可以容纳目标的最小缓冲区大小。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_GET_INFO_FAILED} 查询信息失败。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 数据大小超过指定的缓冲区大小。
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
 * @brief 注册一个回调函数，在下一帧渲染结束后如果距离下一帧到来剩余时间大于1ms时，该回调函数将被执行；如果剩余时间小于1ms时，回调函数将被顺延至当某个下一帧的剩余时间大于1ms时再执行。如果当前没有下一帧，将自动请求下一帧。
 *
 * @param uiContext UIContext对象，用以绑定实例。
 * @param userData 自定义事件参数，当自定义回调函数触发时在回调参数中携带回来。
 * @param callback 自定义回调函数，会在下一帧事件结束后剩余时间大于1ms时回调执行。
 * @param nanoTimeLeft 下一帧渲染后的剩余时间。
 * @param frameCount 帧号。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。
 *     <br>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} uiContext对象无效。
 *     <br>{@link ARKUI_ERROR_CODE_CALLBACK_INVALID} 回调函数无效。
 * @since 20
 */
int32_t OH_ArkUI_PostIdleCallback(ArkUI_ContextHandle uiContext, void* userData,
    void (*callback)(uint64_t nanoTimeLeft, uint32_t frameCount, void* userData));

/**
 * @brief 初始化指定上下文环境的ArkUI相关接口。该函数禁止在非UI线程中调用，否则程序将主动abort。
 *
 * @param env Node-API的环境指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数无效（如env为null或设置白名单失败）。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_InitModuleForArkTSEnv(napi_env env);

/**
 * @brief 通知指定的上下文环境已销毁。该函数禁止在非UI线程中调用，否则程序将主动abort。
 *
 * @param env Node-API的环境指针。
 * @since 20
 */
void OH_ArkUI_NotifyArkTSEnvDestroy(napi_env env);

/**
 * @brief 启用或禁用事件直通。事件直通表示在事件分发过程中，不经过{@link 重采样}直接下发给组件。
 *
 * @param uiContext {@link UIContext}对象，用以绑定实例。
 * @param enabled 启用或禁用事件直通。true表示启用事件直通，false表示禁用事件直通。
 * @param type 指定启用或禁用事件直通的原始输入事件类型{@link ArkUI_RawInputEventType}。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} UIContext对象无效。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_EnableEventPassthrough(ArkUI_ContextHandle uiContext, bool enabled,
    ArkUI_RawInputEventType type);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_NODE_NAPI_H
/** @} */
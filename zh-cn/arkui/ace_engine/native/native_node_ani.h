/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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
 * @since 23
 */

/**
 * @file native_node_ani.h
 *
 * @brief 提供ArkTS1.2的FrameNode转换NodeHandle的方式。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 23
 */

#ifndef ARKUI_NATIVE_NODE_ANI_H
#define ARKUI_NATIVE_NODE_ANI_H

#include "ani/ani.h"

#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取ArkTS侧创建的FrameNode节点对象映射到Native侧的ArkUI_NodeHandle。
 *
 * @param env ANI的环境指针。
 * @param frameNode ArkTS侧创建的FrameNode对象。
 * @param handle ArkUI_NodeHandle指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_GetNodeHandleFromAniValue(ani_env* env, ani_object frameNode, ArkUI_NodeHandle* handle);

/**
 * @brief 获取ArkTS侧创建的UIContext对象映射到Native侧的ArkUI_ContextHandle。
 *
 * @param env ANI的环境指针。
 * @param context ArkTS侧创建的UIContext对象。
 * @param handle ArkUI_ContextHandle指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_GetContextFromAniValue(ani_env* env, ani_object context, ArkUI_ContextHandle* handle);

/**
 * @brief 获取ArkTS侧创建的NodeContent对象映射到Native侧的ArkUI_NodeContentHandle。
 *
 * @param env ANI的环境指针。
 * @param nodeContent ArkTS侧创建的NodeContent对象。
 * @param content ArkUI_NodeContentHandle指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_GetNodeContentFromAniValue(
    ani_env *env, ani_object nodeContent, ArkUI_NodeContentHandle *content);

/**
 * @brief 获取指定节点所在的NavDestination页面的参数。
 *
 * @param node 指定的节点。
 * @param env ANI的环境指针。
 * @param param 返回的页面参数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_GET_INFO_FAILED} 查询页面参数信息失败。
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_GetNavDestinationAniParam(ArkUI_NodeHandle node, ani_env* env, ani_value* param);

/**
 * @brief 获取ArkTS侧的<b>DrawableDescriptor</b>对象，并将其映射到Native侧的<b>ArkUI_DrawableDescriptor</b>对象。
 *
 * @param env 表示ANI环境指针。
 * @param drawable 表示在ArkTS侧创建的<b>DrawableDescriptor</b>对象。
 * @param drawableDescriptor 表示指向<b>ArkUI_DrawableDescriptor</b>对象的指针。
 * @return 返回错误代码。
 *     如果操作成功，则返回 {@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     如果发生参数错误，则返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_GetDrawableDescriptorFromAniValue(
    ani_env *env, ani_object drawable, ArkUI_DrawableDescriptor **drawableDescriptor);

/**
 * @brief 获取ArkTS侧的<b>Resource</b>对象，并将其映射到Native侧的<b>ArkUI_DrawableDescriptor</b>对象。
 *
 * @param env 表示ANI环境指针。
 * @param resource 表示在ArkTS端创建的<b>Resource</b>对象。
 * @param drawableDescriptor 表示指向<b>ArkUI_DrawableDescriptor</b>对象的指针。
 * @return 返回错误代码。
 *     如果操作成功，则返回 {@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     如果发生参数错误，则返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_GetDrawableDescriptorFromResourceAniValue(
    ani_env *env, ani_object resource, ArkUI_DrawableDescriptor **drawableDescriptor);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_NODE_ANI_H
/** @} */
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
 * @brief Defines a set of CustomSpan enum and interface.
 *
 * @since 12
 */

/**
 * @file custom_span.h
 *
 * @brief Defines a set of CustomSpan enum and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_CUSTOM_SPAN_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_CUSTOM_SPAN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 自定义Span组件的测量信息。该结构体用于在自定义Span组件的测量回调中提供组件的测量数据，帮助开发者实现自定义文本组件的精确尺寸测量与布局排版。
 *
 * @since 12
 */
typedef struct ArkUI_CustomSpanMeasureInfo ArkUI_CustomSpanMeasureInfo;
/**
 * @brief 自定义Span组件的度量指标，用于描述自定义Span的宽高、位置等布局信息。开发者可通过该结构体设置自定义Span的宽高数据，实现更精准的文本布局控制和排版优化。
 * 适用于需要精细控制文本显示效果的场景，如富文本编辑器中的图文混排、聊天应用中的表情内嵌、文档应用中的自定义标记等。
 *
 * @since 12
 */
typedef struct ArkUI_CustomSpanMetrics ArkUI_CustomSpanMetrics;
/**
 * @brief 自定义段落组件的绘制信息，用于在该组件的绘制回调中向开发者传递绘制信息，开发者可在自定义绘制流程中获取并使用该信息，实现定制化的段落组件绘制效果。
 *
 * @since 12
 */
typedef struct ArkUI_CustomSpanDrawInfo ArkUI_CustomSpanDrawInfo;
/**
 * @brief 销毁自定义段落组件测量信息。
 *
 * @param info  自定义段落组件测量信息指针。
 * @since 12
 */
void OH_ArkUI_CustomSpanMeasureInfo_Dispose(ArkUI_CustomSpanMeasureInfo* info);
/**
 * @brief 获取自定义段落组件的父节点Text的字体大小。
 *
 * @param info  自定义段落组件测量信息指针。
 * @return 父节点Text的字体大小，单位为fp。若函数参数异常，返回0.0f。 \n
 *         异常返回原因：传入参数验证失败，参数不能为空。
 * @since 12
 */
float OH_ArkUI_CustomSpanMeasureInfo_GetFontSize(ArkUI_CustomSpanMeasureInfo* info);
/**
 * @brief 销毁自定义段落组件度量信息。
 *
 * @param metrics CustomSpanMetrics实例。
 * @since 12
 */
void OH_ArkUI_CustomSpanMetrics_Dispose(ArkUI_CustomSpanMetrics* metrics);
/**
 * @brief 设置自定义段落组件的宽度。
 *
 * @param metrics CustomSpanMetrics实例。
 * @param width 宽度大小，单位为vp。默认值为0.0f，负值与默认值效果一致。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。 \n
 *         异常原因：传入参数验证失败，参数不能为空。
 * @since 12
 */
int32_t OH_ArkUI_CustomSpanMetrics_SetWidth(ArkUI_CustomSpanMetrics* metrics, float width);
/**
 * @brief 设置自定义段落组件的高度。
 *
 * @param metrics CustomSpanMetrics实例。
 * @param height 高度大小，单位为vp。默认值为0.0f，负值与默认值效果一致。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。 \n
 *         异常原因：传入参数验证失败，参数不能为空。
 * @since 12
 */
int32_t OH_ArkUI_CustomSpanMetrics_SetHeight(ArkUI_CustomSpanMetrics* metrics, float height);
/**
 * @brief 销毁自定义段落组件绘制信息。
 *
 * @param info  自定义段落组件绘制信息指针。
 * @since 12
 */
void OH_ArkUI_CustomSpanDrawInfo_Dispose(ArkUI_CustomSpanDrawInfo* info);
/**
 * @brief 获取自定义段落组件相对于挂载组件的x轴偏移值。
 *
 * @param info  自定义段落组件绘制信息指针。
 * @return x轴偏移值，单位为px。若函数参数异常，返回0.0f。 \n
 *         异常返回原因：传入参数验证失败，参数不能为空。
 * @since 12
 */
float OH_ArkUI_CustomSpanDrawInfo_GetXOffset(ArkUI_CustomSpanDrawInfo* info);
/**
 * @brief 获取自定义段落组件相对于挂载组件的上边距。
 *
 * @param info  自定义段落组件绘制信息指针。
 * @return 上边距值，单位为px。若函数参数异常，返回0.0f。 \n
 *         异常返回原因：传入参数验证失败，参数不能为空。
 * @since 12
 */
float OH_ArkUI_CustomSpanDrawInfo_GetLineTop(ArkUI_CustomSpanDrawInfo* info);
/**
 * @brief 获取自定义段落组件相对于挂载组件的下边距。
 *
 * @param info  自定义段落组件绘制信息指针。
 * @return 下边距值，单位为px。若函数参数异常，返回0.0f。 \n
 *         异常返回原因：传入参数验证失败，参数不能为空。
 * @since 12
 */
float OH_ArkUI_CustomSpanDrawInfo_GetLineBottom(ArkUI_CustomSpanDrawInfo* info);
/**
 * @brief 获取自定义段落组件相对于挂载组件的基线偏移量。
 *
 * @param info  自定义段落组件绘制信息指针。
 * @return 基线偏移量值，单位为px。若函数参数异常，返回0.0f。 \n
 *         异常返回原因：传入参数验证失败，参数不能为空。
 * @since 12
 */
float OH_ArkUI_CustomSpanDrawInfo_GetBaseline(ArkUI_CustomSpanDrawInfo* info);

/**
 * @brief 创建自定义段落组件测量信息。
 *
 * @return CustomSpanMeasureInfo实例。 \n
 *         如果返回空指针，可能是因为内存不足。
 * @since 12
 */
ArkUI_CustomSpanMeasureInfo* OH_ArkUI_CustomSpanMeasureInfo_Create(void);
/**
 * @brief 创建自定义段落组件度量信息。
 *
 * @return CustomSpanMetrics实例。 \n
 *         如果返回空指针，可能是因为内存不足。
 * @since 12
 */
ArkUI_CustomSpanMetrics* OH_ArkUI_CustomSpanMetrics_Create(void);
/**
 * @brief 创建自定义段落组件绘制信息。
 *
 * @return CustomSpanDrawInfo实例。 \n
 *         如果返回空指针，可能是因为内存不足。
 * @since 12
 */
ArkUI_CustomSpanDrawInfo* OH_ArkUI_CustomSpanDrawInfo_Create(void);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_CUSTOM_SPAN_H
/** @} */
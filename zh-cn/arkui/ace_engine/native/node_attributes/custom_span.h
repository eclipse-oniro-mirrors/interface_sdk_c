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
 * @brief 定义CustomSpan相关的结构体和接口，用于实现自定义绘制Span的精确尺寸测量、布局排版和绘制效果。支持开发者在富文本编辑器、聊天应用、文档应用等场景中实现图文混排、表情内嵌、自定义标记等功能，
 *        提供灵活的自定义绘制Span能力，帮助开发者提升开发效率，实现更丰富的文本排版效果。
 *
 * @since 12
 */

/**
 * @file custom_span.h
 *
 * @brief 定义CustomSpan相关的结构体和接口，用于实现自定义绘制Span的精确尺寸测量、布局排版和绘制效果。支持开发者在富文本编辑器、聊天应用、文档应用等场景中实现图文混排、表情内嵌、自定义标记等功能，
 * 提供灵活的自定义绘制Span能力，帮助开发者提升开发效率，实现更丰富的文本排版效果。
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
 * @brief 自定义绘制Span的测量信息。该结构体用于在自定义绘制Span的测量回调中提供组件的测量数据，帮助开发者实现自定义文本组件的精确尺寸测量与布局排版。
 *
 * @since 12
 */
typedef struct ArkUI_CustomSpanMeasureInfo ArkUI_CustomSpanMeasureInfo;

/**
 * @brief 自定义绘制Span的度量指标，用于设置组件的宽高等布局信息。适用于富文本编辑器、聊天应用等场景的图文混排。
 *
 * @since 12
 */
typedef struct ArkUI_CustomSpanMetrics ArkUI_CustomSpanMetrics;

/**
 * @brief 自定义绘制Span的绘制信息，用于在该组件的绘制回调中向开发者传递绘制信息，开发者可在自定义绘制流程中获取并使用该信息，实现定制化的段落组件绘制效果。
 *
 * @since 12
 */
typedef struct ArkUI_CustomSpanDrawInfo ArkUI_CustomSpanDrawInfo;

/**
 * @brief 创建自定义绘制Span测量信息。
 *
 * @return ArkUI_CustomSpanMeasureInfo实例，用于在自定义绘制Span的测量回调中提供组件的测量数据。
 *     <br>如果返回空指针，可能是因为内存不足。
 * @since 12
 */
ArkUI_CustomSpanMeasureInfo* OH_ArkUI_CustomSpanMeasureInfo_Create(void);

/**
 * @brief 销毁自定义绘制Span测量信息。
 *
 * @param info 自定义绘制Span测量信息指针，用于传入需要销毁的测量信息对象。参数不能为空，否则会导致参数验证失败。必须是由OH_ArkUI_CustomSpanMeasureInfo_Create()创建的对象。
 * @since 12
 */
void OH_ArkUI_CustomSpanMeasureInfo_Dispose(ArkUI_CustomSpanMeasureInfo* info);

/**
 * @brief 获取自定义绘制Span的父节点Text的字体大小。在自定义绘制Span的测量回调中，可根据父节点Text的字体大小计算自定义组件的布局尺寸，用于实现图文混排、表情内嵌等场景的精确排版。
 *
 * @param info 自定义绘制Span测量信息指针。参数不能为空，否则会导致参数验证失败。
 * @return 父节点Text的字体大小，单位为fp。若参数验证失败，返回0.0f。
 *     <br>异常返回原因：参数验证失败，参数不能为空。
 * @since 12
 */
float OH_ArkUI_CustomSpanMeasureInfo_GetFontSize(ArkUI_CustomSpanMeasureInfo* info);

/**
 * @brief 创建自定义绘制Span度量信息。
 *
 * @return ArkUI_CustomSpanMetrics实例，用于描述自定义绘制Span的宽高等布局信息。
 *     <br>如果返回空指针，可能是因为内存不足。
 * @since 12
 */
ArkUI_CustomSpanMetrics* OH_ArkUI_CustomSpanMetrics_Create(void);

/**
 * @brief 销毁自定义绘制Span度量信息。
 *
 * @param metrics 自定义绘制Span度量信息实例指针，用于传入需要销毁的度量信息对象。参数不能为空，否则会导致参数验证失败。必须是由OH_ArkUI_CustomSpanMetrics_Create()创建的对象。
 * @since 12
 */
void OH_ArkUI_CustomSpanMetrics_Dispose(ArkUI_CustomSpanMetrics* metrics);

/**
 * @brief 设置自定义绘制Span的宽度。在图文混排场景中，需要为嵌入的图片或表情设置合适的宽度以匹配文本行高；在文档应用中，可能需要为自定义标记元素设置固定宽度。
 *
 * @param metrics 自定义绘制Span度量信息实例指针，用于传入需要设置宽度的度量信息对象。参数不能为空，否则会导致参数验证失败。
 * @param width 宽度大小，单位为vp。取值范围[0, +∞)，默认值为0.0f，负值与默认值效果一致。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数验证失败。
 *     <br>可能原因：参数不能为空。
 *     <br>处理步骤：请确保传入的metrics参数不为空指针。
 * @since 12
 */
int32_t OH_ArkUI_CustomSpanMetrics_SetWidth(ArkUI_CustomSpanMetrics* metrics, float width);

/**
 * @brief 设置自定义绘制Span的高度。在表情内嵌场景中，需要根据表情大小设置合适的高度以保持与文本对齐；在图文混排场景中，需要为嵌入元素设置与文本行高匹配的高度。
 *
 * @param metrics 自定义绘制Span度量信息实例指针，用于传入需要设置高度的度量信息对象。参数不能为空，否则会导致参数验证失败。必须是通过OH_ArkUI_CustomSpanMetrics_Create()
 *     创建的有效对象。
 * @param height 高度大小，单位为vp。取值范围[0, +∞)，默认值为0.0f，负值与默认值效果一致。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数验证失败。
 *     <br>可能原因：参数不能为空。
 *     <br>处理步骤：请确保传入的metrics参数不为空指针。
 * @since 12
 */
int32_t OH_ArkUI_CustomSpanMetrics_SetHeight(ArkUI_CustomSpanMetrics* metrics, float height);

/**
 * @brief 创建自定义绘制Span绘制信息。
 *
 * @return ArkUI_CustomSpanDrawInfo实例，表示自定义绘制Span的绘制信息。
 *     <br>如果返回空指针，可能是因为内存不足。
 * @since 12
 */
ArkUI_CustomSpanDrawInfo* OH_ArkUI_CustomSpanDrawInfo_Create(void);

/**
 * @brief 销毁自定义绘制Span绘制信息。
 *
 * @param info 自定义绘制Span绘制信息指针，用于传入需要销毁的绘制信息对象。参数不能为空，否则会导致参数验证失败。必须是由OH_ArkUI_CustomSpanDrawInfo_Create()创建的对象。
 * @since 12
 */
void OH_ArkUI_CustomSpanDrawInfo_Dispose(ArkUI_CustomSpanDrawInfo* info);

/**
 * @brief 获取自定义绘制Span相对于挂载组件的x轴偏移值。在自定义绘制回调中，需要根据偏移值确定绘制起始位置，用于实现表情内嵌、图文混排等场景的精确绘制。
 *
 * @param info 自定义绘制Span绘制信息指针，用于传入需要获取x轴偏移值的绘制信息对象。参数不能为空，否则会导致参数验证失败。必须是通过OH_ArkUI_CustomSpanDrawInfo_Create()创建的有效对象。
 * @return x轴偏移值，单位为px。若参数验证失败，返回0.0f。
 *     <br>异常返回原因：参数验证失败，参数不能为空。
 * @since 12
 */
float OH_ArkUI_CustomSpanDrawInfo_GetXOffset(ArkUI_CustomSpanDrawInfo* info);

/**
 * @brief 获取自定义绘制Span相对于挂载组件的上边距。在自定义绘制时，需要根据上边距确定绘制区域的垂直起始位置，用于富文本编辑器、文档应用等场景的精确排版。
 *
 * @param info 自定义绘制Span绘制信息指针，用于传入需要获取上边距的绘制信息对象。参数不能为空，否则会导致参数验证失败。必须是通过OH_ArkUI_CustomSpanDrawInfo_Create()创建的有效对象。
 * @return 上边距值，单位为px。若参数验证失败，返回0.0f。
 *     <br>异常返回原因：参数验证失败，参数不能为空。
 * @since 12
 */
float OH_ArkUI_CustomSpanDrawInfo_GetLineTop(ArkUI_CustomSpanDrawInfo* info);

/**
 * @brief 获取自定义绘制Span相对于挂载组件的下边距。在自定义绘制时，需要结合上边距和下边距计算绘制区域的高度范围，用于图文混排、表情内嵌等场景的精确布局。
 *
 * @param info 自定义绘制Span绘制信息指针，用于传入需要获取下边距的绘制信息对象。参数不能为空，否则会导致参数验证失败。必须是通过OH_ArkUI_CustomSpanDrawInfo_Create()创建的有效对象。
 * @return 下边距值，单位为px。若参数验证失败，返回0.0f。
 *     <br>异常返回原因：参数验证失败，参数不能为空。
 * @since 12
 */
float OH_ArkUI_CustomSpanDrawInfo_GetLineBottom(ArkUI_CustomSpanDrawInfo* info);

/**
 * @brief 获取自定义绘制Span相对于挂载组件的基线偏移量。在自定义绘制Span的绘制回调中，通过本接口获取基线偏移量用于文本对齐排版，实现富文本编辑器、图文混排等场景的精准绘制效果。
 *
 * @param info 自定义绘制Span绘制信息指针，用于传入需要获取基线偏移量的绘制信息对象。参数不能为空，否则会导致参数验证失败。
 * @return 基线偏移量值，单位为px。若参数验证失败，返回0.0f。
 *     <br>异常返回原因：参数验证失败，参数不能为空。
 * @since 12
 */
float OH_ArkUI_CustomSpanDrawInfo_GetBaseline(ArkUI_CustomSpanDrawInfo* info);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_CUSTOM_SPAN_H
/** @} */
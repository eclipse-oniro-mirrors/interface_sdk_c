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
 * @brief Defines enumerations and APIs related to **CustomSpan**, which is used to implement precise size measurement,
 * layout typesetting, and drawing effects for custom spans. It supports you in implementing text and image layout,
 * emoji embedding, custom markers, and other features in scenarios such as rich text editors, chat applications, and
 * document applications, providing flexible custom span capabilities to help improve development efficiency and
 * achieve richer text layout effects.
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
 * @brief Defines the measurement information of a custom span. This struct is used to provide measurement data in the
 * measurement callback of a custom span, helping you implement precise size measurement and layout of custom text.
 *
 * @since 12
 */
typedef struct ArkUI_CustomSpanMeasureInfo ArkUI_CustomSpanMeasureInfo;

/**
 * @brief Describes the metrics of a custom span, which is used to set layout information such as the width and height
 * of a component. It applies to mixed text and image layout in scenarios such as rich text editors and chat
 * applications.
 *
 * @since 12
 */
typedef struct ArkUI_CustomSpanMetrics ArkUI_CustomSpanMetrics;

/**
 * @brief Defines the drawing information of a custom span, which is passed to you in the drawing callback of the span.
 * You can obtain and use the information in the custom drawing process to achieve custom drawing effects for the span.
 *
 * @since 12
 */
typedef struct ArkUI_CustomSpanDrawInfo ArkUI_CustomSpanDrawInfo;

/**
 * @brief Creates measurement information for a custom span.
 *
 * @return Pointer to the **ArkUI_CustomSpanMeasureInfo** instance. It is used to provide measurement data of the
 *     component in the measurement callback of the custom span.
 *     <br>If a null pointer is returned, the memory may be insufficient.
 * @since 12
 */
ArkUI_CustomSpanMeasureInfo* OH_ArkUI_CustomSpanMeasureInfo_Create(void);

/**
 * @brief Disposes of measurement information of a custom span.
 *
 * @param info Pointer to the measurement information of a custom span. It is used to pass the measurement information
 *     object to dispose of. The parameter cannot be null; otherwise, it will cause parameter verification failure. The
 *     object must be the one created by **OH_ArkUI_CustomSpanMeasureInfo_Create()**.
 * @since 12
 */
void OH_ArkUI_CustomSpanMeasureInfo_Dispose(ArkUI_CustomSpanMeasureInfo* info);

/**
 * @brief Obtains the font size of the parent text node of a custom span. In the measurement callback of a custom span,
 * the layout size of the custom component can be calculated based on the font size of the parent text node. This API
 * is used to implement precise typesetting in scenarios such as layout of text and images and emoji embedding.
 *
 * @param info Pointer to the measurement information of a custom span. This parameter cannot be null; otherwise, it
 *     will cause parameter verification failure.
 * @return Font size of the parent node text, in fp. If parameter verification fails, **0.0f** is returned.
 *     <br>A possible cause is that the parameter is null.
 * @since 12
 */
float OH_ArkUI_CustomSpanMeasureInfo_GetFontSize(ArkUI_CustomSpanMeasureInfo* info);

/**
 * @brief Creates measurement metrics for a custom span.
 *
 * @return Pointer to the **ArkUI_CustomSpanMetrics** instance. It is used to describe layout information such as the
 *     width and height of a custom span.
 *     <br>If a null pointer is returned, the memory may be insufficient.
 * @since 12
 */
ArkUI_CustomSpanMetrics* OH_ArkUI_CustomSpanMetrics_Create(void);

/**
 * @brief Disposes of measurement metrics of a custom span.
 *
 * @param metrics Pointer to the **CustomSpanMetrics** instance. It is used to pass the measurement metric object to
 *     dispose of. The parameter cannot be null; otherwise, it will cause parameter verification failure. The object
 *     must be the one created by **OH_ArkUI_CustomSpanMetrics_Create()**.
 * @since 12
 */
void OH_ArkUI_CustomSpanMetrics_Dispose(ArkUI_CustomSpanMetrics* metrics);

/**
 * @brief Sets the width for a custom span. In text and image layout scenarios, you need to set an appropriate width
 * for embedded images or emojis to match the text line height. In document applications, you may need to set a fixed
 * width for custom marker elements.
 *
 * @param metrics Pointer to the **CustomSpanMetrics** instance. It is used to pass the measurement metric object whose
 *     width needs to be set. The parameter cannot be null; otherwise, parameter validation fails.
 * @param width Width, in vp. The value range is [0, +∞). The default value is **0.0f**. Negative values have the same
 *     effect as the default value.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Possible cause: Parameter validation fails because the parameter is null.
 *     <br>Handling steps: Ensure that the **metrics** parameter passed in is not a null pointer.
 * @since 12
 */
int32_t OH_ArkUI_CustomSpanMetrics_SetWidth(ArkUI_CustomSpanMetrics* metrics, float width);

/**
 * @brief Sets the height for a custom span. In emoji embedding scenarios, you need to set an appropriate height based
 * on the emoji size to maintain alignment with the text. In text and image layout scenarios, you need to set a height
 * for embedded elements that matches the text line height.
 *
 * @param metrics Pointer to the **CustomSpanMetrics** instance. It is used to pass the measurement metric object whose
 *     height needs to be set. The parameter cannot be null; otherwise, it will cause parameter verification failure.
 *     The object must be a valid object created by **OH_ArkUI_CustomSpanMetrics_Create()**.
 * @param height Height, in vp. The value range is [0, +∞), and the default value is **0.0f**. Negative values have the
 *     same effect as the default value.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Possible cause: Parameter validation fails because the parameter is null.
 *     <br>Handling steps: Ensure that the **metrics** parameter passed in is not a null pointer.
 * @since 12
 */
int32_t OH_ArkUI_CustomSpanMetrics_SetHeight(ArkUI_CustomSpanMetrics* metrics, float height);

/**
 * @brief Creates drawing information for a custom span.
 *
 * @return Pointer to the **ArkUI_CustomSpanDrawInfo** instance, indicating the drawing information of the custom span.
 *     <br>If a null pointer is returned, the memory may be insufficient.
 * @since 12
 */
ArkUI_CustomSpanDrawInfo* OH_ArkUI_CustomSpanDrawInfo_Create(void);

/**
 * @brief Disposes of drawing information for a custom span.
 *
 * @param info Pointer to the drawing information of a custom span. It is used to pass the drawing information object
 *     to dispose of. The parameter cannot be null, otherwise it will cause parameter verification failure. The object
 *     must be the one created by **OH_ArkUI_CustomSpanDrawInfo_Create()**.
 * @since 12
 */
void OH_ArkUI_CustomSpanDrawInfo_Dispose(ArkUI_CustomSpanDrawInfo* info);

/**
 * @brief Obtains the x-axis offset of the custom span relative to the mounted component. In the custom drawing
 * callback, you need to determine the drawing start position based on the offset value. This API is used to implement
 * precise drawing in scenarios such as emoji embedding and layout of text and images.
 *
 * @param info Pointer to the drawing information of a custom span. It is used to pass the drawing information object
 *     for which the x-axis offset value needs to be obtained. The parameter cannot be null; otherwise, parameter
 *     verification will fail.
 * @return X-axis offset value, in px. If parameter verification fails, **0.0f** is returned.
 *     <br>The parameter verification fails because the parameter is null.
 * @since 12
 */
float OH_ArkUI_CustomSpanDrawInfo_GetXOffset(ArkUI_CustomSpanDrawInfo* info);

/**
 * @brief Obtains the top margin of the custom span relative to the mounted component. In custom drawing, you need to
 * determine the vertical start position of the drawing area based on the top margin. This API is used for precise
 * typesetting in scenarios such as rich text editors and document applications.
 *
 * @param info Pointer to the drawing information of a custom span. It is used to pass the drawing information object
 *     for which the top margin needs to be obtained. The parameter cannot be null; otherwise, parameter verification
 *     will fail. The value must be a valid object created by **OH_ArkUI_CustomSpanDrawInfo_Create()**.
 * @return Top margin, in px. If parameter validation fails, **0.0f** is returned.
 *     <br>The parameter validation fails because the parameter is null.
 * @since 12
 */
float OH_ArkUI_CustomSpanDrawInfo_GetLineTop(ArkUI_CustomSpanDrawInfo* info);

/**
 * @brief Obtains the bottom margin of the custom span relative to the mounted component. In custom drawing, you need
 * to calculate the height range of the drawing area by combining the top margin and bottom margin. This API is used
 * for precise layout in scenarios such as layout of text and images and emoji embedding.
 *
 * @param info Pointer to the drawing information of a custom span. It is used to pass the drawing information object
 *     whose bottom margin needs to be obtained. The parameter cannot be null; otherwise, parameter verification will
 *     fail.
 * @return Bottom margin, in px. If parameter validation fails, **0.0f** is returned.
 *     <br>The parameter validation fails because the parameter is null.
 * @since 12
 */
float OH_ArkUI_CustomSpanDrawInfo_GetLineBottom(ArkUI_CustomSpanDrawInfo* info);

/**
 * @brief Obtains the baseline offset of the custom span relative to the mounted component. In the drawing callback of
 * a custom span, use this API to obtain the baseline offset for text alignment and typesetting, achieving precise
 * drawing effects in scenarios such as rich text editors and layout of text and images.
 *
 * @param info Pointer to the drawing information of a custom span. It is used to pass the drawing information object
 *     for which the baseline offset needs to be obtained. The parameter cannot be empty; otherwise, parameter
 *     verification will fail.
 * @return Baseline offset, in px. If parameter verification fails, **0.0f** is returned.
 *     <br>The parameter verification fails because the parameter is null.
 * @since 12
 */
float OH_ArkUI_CustomSpanDrawInfo_GetBaseline(ArkUI_CustomSpanDrawInfo* info);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_CUSTOM_SPAN_H
/** @} */
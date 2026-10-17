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
 * @brief Defines a set of Text enum and interface.
 *
 * @since 12
 */

/**
 * @file text.h
 *
 * @brief Defines enumerations and APIs related to **Text** for configuring text styles, controlling marquee effects,
 * implementing text entity recognition, and managing text controllers. It is applicable to scenarios such as
 * customizing text display effects, implementing dynamic text interaction, recognizing special entities in text (such
 * as addresses and phone numbers), and precisely controlling text font weight. With these configuration APIs, you can
 * flexibly control the display effects and interaction behaviors of text components to improve user experience.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_H

#include <stdint.h>
#include <stdbool.h>
#include "../error_code.h"
#include "text_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates font styles.
 *
 * @since 12
 */
typedef enum {
    /** Standard font style. */
    ARKUI_FONT_STYLE_NORMAL = 0,
    /** Italic font style. */
    ARKUI_FONT_STYLE_ITALIC
} ArkUI_FontStyle;

/**
 * @brief Enumerates font weights.
 *
 * @since 12
 */
typedef enum {
    /** 100 */
    ARKUI_FONT_WEIGHT_W100 = 0,
    /** 200 */
    ARKUI_FONT_WEIGHT_W200,
    /** 300 */
    ARKUI_FONT_WEIGHT_W300,
    /** 400 */
    ARKUI_FONT_WEIGHT_W400,
    /** 500 */
    ARKUI_FONT_WEIGHT_W500,
    /** 600 */
    ARKUI_FONT_WEIGHT_W600,
    /** 700 */
    ARKUI_FONT_WEIGHT_W700,
    /** 800 */
    ARKUI_FONT_WEIGHT_W800,
    /** 900 */
    ARKUI_FONT_WEIGHT_W900,
    /** The font weight is bold. */
    ARKUI_FONT_WEIGHT_BOLD,
    /** The font weight is normal. */
    ARKUI_FONT_WEIGHT_NORMAL,
    /** The font weight is bolder. */
    ARKUI_FONT_WEIGHT_BOLDER,
    /** The font weight is lighter. */
    ARKUI_FONT_WEIGHT_LIGHTER,
    /** The font weight is medium. */
    ARKUI_FONT_WEIGHT_MEDIUM,
    /** The font weight is normal. */
    ARKUI_FONT_WEIGHT_REGULAR
} ArkUI_FontWeight;

/**
 * @brief Enumerates how the adaptive height is determined for the text.
 *
 * @since 12
 */
typedef enum {
    /** Prioritize the <b>maxLines</b> settings. */
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST = 0,
    /** Prioritize the <b>minFontSize</b> settings. */
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST,
    /** Prioritize the layout constraint settings in terms of height. */
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST
} ArkUI_TextHeightAdaptivePolicy;

/**
 * @brief Enumerates the entity types of text recognition.
 *
 * @since 12
 */
typedef enum {
    /** Phone Number.*/
    ARKUI_TEXT_DATA_DETECTOR_TYPE_PHONE_NUMBER = 0,
    /** Link. */
    ARKUI_TEXT_DATA_DETECTOR_TYPE_URL,
    /** Mailbox. */
    ARKUI_TEXT_DATA_DETECTOR_TYPE_EMAIL,
    /** Address. */
    ARKUI_TEXT_DATA_DETECTOR_TYPE_ADDRESS
} ArkUI_TextDataDetectorType;

/**
 * @brief Defines the configuration for text entity detection. By setting the entity types to be detected (such as
 * phone numbers, URLs, emails, addresses, and dates), the corresponding entity detection feature is enabled in the
 * text component, and the detected entities are presented in an interactive format. This applies to scenarios such as
 * automatically recognizing contact information in chat messages and extracting links from documents.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextDataDetectorConfig OH_ArkUI_TextDataDetectorConfig;

/**
 * @brief Enumerates marquee startup policies.
 *
 * @since 23
 */
typedef enum {
    /** Start marquee in any case. This is the default policy. */
    ARKUI_MARQUEESTARTPOLICY_DEFAULT = 0,
    /** Start marquee only when get focus. */
    ARKUI_MARQUEESTARTPOLICY_ONFOCUS = 1
} ArkUI_MarqueeStartPolicy;

/**
 * @brief Enumerates marquee update policies.
 *
 * @since 23
 */
typedef enum {
    /** Reset scroll position and restart scroll. */
    ARKUI_MARQUEEUPDATEPOLICY_DEFAULT = 0,
    /** Preserve scroll position, just change to new text. */
    ARKUI_MARQUEEUPDATEPOLICY_PRESERVEPOSITION = 1
} ArkUI_MarqueeUpdatePolicy;

/**
 * @brief Defines text marquee mode options, which are used to configure the display parameters of the text marquee
 * effect. It is suitable for scenarios where long text content needs to be displayed cyclically in limited space, such
 * as scrolling notification messages and scrolling titles, effectively solving the display problem when text exceeds
 * the display area.
 *
 * @since 23
 */
typedef struct ArkUI_TextMarqueeOptions ArkUI_TextMarqueeOptions;

/**
 * @brief Defines a text component controller, which is used to control and interact with the text component on the
 * native side. You can create a controller object through {@link OH_ArkUI_TextController_Create}. When the object is
 * created, you must call {@link OH_ArkUI_TextController_Destroy} to destroy it and release resources after use. The
 * two must be used in pairs; otherwise, memory leaks will occur. After the controller is created, you can use APIs
 * such as {@link OH_ArkUI_TextController_SetStyledString} to set the styled string of the text component, implementing
 * dynamic management and style control of the text content. This is applicable to scenarios where the text component
 * needs to be operated at the native layer.
 *
 * @since 26.0.0
 */
typedef struct OH_ArkUI_TextController OH_ArkUI_TextController;

/**
 * @brief Defines the font weight configurations of text. It is suitable for scenarios that require precise control
 * over text font weight or where the text font weight needs to follow device font setting changes. You can create a
 * text font weight configuration object through {@link OH_ArkUI_FontWeightConfigs_Create}, and must call
 * {@link OH_ArkUI_FontWeightConfigs_Destroy} to destroy the object and release resources after use to avoid memory
 * leaks. After the configuration object is created, you can set and query the information through the following APIs:
 * use {@link OH_ArkUI_FontWeightConfigs_SetEnableVariableFontWeight} to set whether to enable variable font weight
 * adjustment, use {@link OH_ArkUI_FontWeightConfigs_GetEnableVariableFontWeight} to check whether variable font weight
 * adjustment is enabled, use {@link OH_ArkUI_FontWeightConfigs_SetEnableDeviceFontWeightCategory} to set whether the
 * text font weight is updated with the font weight level of the device, and use
 * {@link OH_ArkUI_FontWeightConfigs_GetEnableDeviceFontWeightCategory} to check whether the text font weight is
 * updated with the font weight level of the device. When this configuration object is used and is not a null pointer,
 * if the user does not explicitly make the configuration through the APIs, each configuration item uses its default
 * value (variable font weight adjustment is disabled by default, and text font weight is updated with the font weight
 * level of the device by default). When this configuration object is a null pointer, the default values are not used,
 * and the text font weight behavior is the same as that of the parent component.
 *
 * @since 24
 */
typedef struct OH_ArkUI_FontWeightConfigs OH_ArkUI_FontWeightConfigs;

/**
 * @brief Defines the font configurations of text. Currently, it supports setting and obtaining the font weight
 * configuration through related APIs, and is applicable to scenarios that require custom font weight display effects.
 * You can create a font configuration object through the {@link OH_ArkUI_FontConfigs_Create} API and destroy it
 * through the {@link OH_ArkUI_FontConfigs_Destroy} API. After the configurations are created, you can set and query
 * them through the following APIs: set the font weight configuration through the
 * {@link OH_ArkUI_FontConfigs_SetFontWeightConfigs} API, and obtain the font weight configuration through the
 * {@link OH_ArkUI_FontConfigs_GetFontWeightConfigs} API.
 *
 * @since 24
 */
typedef struct OH_ArkUI_FontConfigs OH_ArkUI_FontConfigs;

/**
 * @brief Creates a text marquee option object. When the object is no longer used, call
 * {@link OH_ArkUI_TextMarqueeOptions_Dispose} to dispose of it and release resources to avoid memory leaks.
 *
 * @return Pointer to the text marquee option object. If creation fails, a null pointer is returned. You need to call
 *     {@link OH_ArkUI_TextMarqueeOptions_Dispose} to dispose of it after use.
 * @since 23
 */
ArkUI_TextMarqueeOptions* OH_ArkUI_TextMarqueeOptions_Create();

/**
 * @brief Disposes of the text marquee option object. This API must be used in pair with
 * {@link OH_ArkUI_TextMarqueeOptions_Create}; otherwise, memory leaks will occur.
 *
 * @param option Pointer to the text marquee option object.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_Dispose(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets whether to play the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @param start Whether to play the text marquee option. **true** indicates to play; **false** otherwise. Default value:
 *      **true**.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetStart(ArkUI_TextMarqueeOptions* option, bool start);

/**
 * @brief Obtains whether the text marquee option is played.
 *
 * @param option Pointer to the text marquee option object.
 * @return Whether the text marquee option is played. **true** indicates the text marquee option is played; **false**
 *     indicates the text marquee option is not played.
 * @since 23
 */
bool OH_ArkUI_TextMarqueeOptions_GetStart(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the step of the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @param step Step length. Unit: vp. Value range: (0, Text length]. If the value is out of range, **4.0vp** is used.
 *     Default value: **4.0vp**. After the step is set, the marquee moves by this step value each time. A larger step
 *     results in faster scrolling.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetStep(ArkUI_TextMarqueeOptions* option, float step);

/**
 * @brief Obtains the step of the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @return Step. The unit is vp.
 * @since 23
 */
float OH_ArkUI_TextMarqueeOptions_GetStep(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the distance between the start and end items of the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @param spacing Spacing between the start and end items. Unit: vp. Value range: [0, +∞). If the value is less than 0,
 *     the default value **48.0vp** is used. Default value: **48.0vp**. After setting, when the marquee finishes one
 *     scroll cycle, the distance between the start and end text is this spacing value. It is recommended to set this
 *     value based on the width of the display area.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetSpacing(ArkUI_TextMarqueeOptions* option, float spacing);

/**
 * @brief Obtains the spacing between the start and end items of the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @return Spacing between the start and end items. The unit is vp.
 * @since 23
 */
float OH_ArkUI_TextMarqueeOptions_GetSpacing(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the number of repetitions for looping the text marquee option. The value less than or equal to **0**
 * indicates infinite looping.
 *
 * @param option Pointer to the text marquee option object.
 * @param loop Number of loops. The value less than or equal to **0** indicates infinite looping.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetLoop(ArkUI_TextMarqueeOptions* option, int32_t loop);

/**
 * @brief Obtains the number of repetitions for looping the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @return Number of loops.
 * @since 23
 */
int32_t OH_ArkUI_TextMarqueeOptions_GetLoop(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the direction for scrolling the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @param fromStart Whether to scroll the text marquee option from the start. **true** to scroll from the start; **
 *     false** to scroll in reverse. Default value: **true**.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetFromStart(ArkUI_TextMarqueeOptions* option, bool fromStart);

/**
 * @brief Obtains the direction for scrolling the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @return Whether the text marquee option is scrolled from the start. **true** to scroll from the start; **false** to
 *     scroll in reverse.
 * @since 23
 */
bool OH_ArkUI_TextMarqueeOptions_GetFromStart(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the delay of each loop for the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @param delay Delay of each loop, in milliseconds. Value range: [0, +∞). Default value: **0**.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetDelay(ArkUI_TextMarqueeOptions* option, int32_t delay);

/**
 * @brief Obtains the delay of each loop for the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @return Delay of each loop, in milliseconds.
 * @since 23
 */
int32_t OH_ArkUI_TextMarqueeOptions_GetDelay(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets whether the text marquee option supports a fade-out effect when the text is too long. When this
 * parameter is set to **true**: if the text content exceeds the display range, a fade-out effect is applied to the
 * edges of the partially visible text;
 * <br>if text is partially visible at both ends, the fade-out effect is applied to both ends.
 * <br>When the fade-out effect is enabled, the **NODE_CLIP** attribute in {@link ArkUI_NodeAttributeType} is
 * automatically locked to **true** and cannot be set to **false**.
 *
 * @param option Pointer to the text marquee option object.
 * @param fadeout Whether the text marquee option supports a fade-out effect when the text is too long.
 *     <br>The value **true** means to apply a fade-out effect when the text is too long, in which case the
 *     **NODE_CLIP** attribute is automatically locked to **true** and cannot be set to **false**.
 *     <br>The value **false** means not to apply a fade-out effect.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetFadeout(ArkUI_TextMarqueeOptions* option, bool fadeout);

/**
 * @brief Obtains whether the text marquee option supports a fade-out effect when the text is too long.
 *
 * @param option Pointer to the text marquee option object.
 * @return Whether the text marquee option supports a fade-out effect when the text is too long. The value **true**
 *     means the fade-out effect is supported, and **false** means the opposite.
 * @since 23
 */
bool OH_ArkUI_TextMarqueeOptions_GetFadeout(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the start policy of the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @param startPolicy Start policy.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetStartPolicy(ArkUI_TextMarqueeOptions* option, ArkUI_MarqueeStartPolicy startPolicy);

/**
 * @brief Obtains the startup policy of the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @return Start policy.
 * @since 23
 */
ArkUI_MarqueeStartPolicy OH_ArkUI_TextMarqueeOptions_GetStartPolicy(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the update policy of the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @param updatePolicy Update policy.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetUpdatePolicy(ArkUI_TextMarqueeOptions* option,
    ArkUI_MarqueeUpdatePolicy updatePolicy);

/**
 * @brief Obtains the update policy of the text marquee option.
 *
 * @param option Pointer to the text marquee option object.
 * @return Update policy.
 * @since 23
 */
ArkUI_MarqueeUpdatePolicy OH_ArkUI_TextMarqueeOptions_GetUpdatePolicy(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Creates a text entity recognition configuration object. When the object is no longer used, call
 * {@link OH_ArkUI_TextDataDetectorConfig_Destroy} to destroy it and release resources to avoid memory leaks.
 *
 * @return Pointer to the {@link OH_ArkUI_TextDataDetectorConfig} object.<br>
 *      If creation fails, a null pointer is returned.<br>
 *      This object must be destroyed by calling {@link OH_ArkUI_TextDataDetectorConfig_Destroy} after use.
 * @since 24
 */
OH_ArkUI_TextDataDetectorConfig* OH_ArkUI_TextDataDetectorConfig_Create();

/**
 * @brief Destroys the text entity recognition configuration object.
 *
 * @param config Pointer to the {@link OH_ArkUI_TextDataDetectorConfig} object.
 * @since 24
 */
void OH_ArkUI_TextDataDetectorConfig_Destroy(OH_ArkUI_TextDataDetectorConfig* config);

/**
 * @brief Creates a text controller object. When the object is no longer used, call
 * {@link OH_ArkUI_TextController_Destroy} to destroy it and release resources to avoid memory leaks.
 *
 * @return Pointer to the text controller object. If creation fails, a null pointer is returned. After use, call
 *     {@link OH_ArkUI_TextController_Destroy} to destroy it.
 * @since 26.0.0
 */
OH_ArkUI_TextController* OH_ArkUI_TextController_Create();

/**
 * @brief Destroys the text controller object. This API must be used in pair with
 * {@link OH_ArkUI_TextController_Create}; otherwise, memory leaks will occur.
 *
 * @param controller Pointer to the text component controller object.
 * @since 26.0.0
 */
void OH_ArkUI_TextController_Destroy(OH_ArkUI_TextController* controller);

/**
 * @brief Creates a text font weight configuration object. When the object is no longer used, call
 * {@link OH_ArkUI_FontWeightConfigs_Destroy} to destroy it and release resources to avoid memory leaks.
 *
 * @return Pointer to the text font weight configuration object. If creation fails, a null pointer is returned. You
 *     need to call {@link OH_ArkUI_FontWeightConfigs_Destroy} to destroy it after use. When the configuration object
 *     is a null pointer, no default value is applied, and the text font weight behavior remains consistent with that
 *     of the parent component.
 * @since 24
 */
OH_ArkUI_FontWeightConfigs* OH_ArkUI_FontWeightConfigs_Create();

/**
 * @brief Destroys the text font weight configuration object. This API must be used in pair with
 * {@link OH_ArkUI_FontWeightConfigs_Create}; otherwise, memory leaks will occur.
 *
 * @param option Pointer to the text font weight configuration object to be destroyed.
 * @since 24
 */
void OH_ArkUI_FontWeightConfigs_Destroy(OH_ArkUI_FontWeightConfigs* option);

/**
 * @brief Sets whether to enable variable font weight adjustment. Variable font weight adjustment allows the font to
 * display weight at any integer value from 100 to 900, enabling finer control over font weight.
 *
 * @param option Pointer to the text font weight configuration object to be modified.
 * @param enable Whether to enable variable font weight adjustment. The default value is **false**. The value true
 *     means to enable variable font weight adjustment. In this case, if the value of **weight** is any integer in the
 *     range [100, 900], the value is used; otherwise, the default value **400** is used. The value **false** means to
 *     disable variable font weight adjustment. In this case, the value of **weight** can only be multiples of 100 in
 *     the range [100, 900]; for a non-multiple of 100, the default value **400** is used.
 * @since 24
 */
void OH_ArkUI_FontWeightConfigs_SetEnableVariableFontWeight(OH_ArkUI_FontWeightConfigs* option, bool enable);

/**
 * @brief Obtains whether variable font weight adjustment is enabled for the text font weight configuration object.
 *
 * @param option Pointer to the text font weight configuration object.
 * @return Whether variable font weight adjustment is enabled.
 *     <br>**true** indicates variable font weight adjustment is enabled. If the value of **weight** is any integer in
 *     the range of [100, 900], the value of **weight** is used. Otherwise, the default value **400** is used.
 *     <br>**false** indicates variable font weight adjustment is disabled. If the value of **weight** is an integer
 *     multiple of 100 in the range of [100, 900], the value of **weight** is used. Otherwise, the default value **400**
 *      is used.
 *     <br>If the value of **weight** is not within the range of [100, 900], the default value **400** is used.
 * @since 24
 */
bool OH_ArkUI_FontWeightConfigs_GetEnableVariableFontWeight(OH_ArkUI_FontWeightConfigs* option);

/**
 * @brief Sets whether to automatically update the text font weight when the font weight level of the device changes.
 * The font weight level of the device refers to the global font weight configuration in system settings, which users
 * can adjust in system settings.
 *
 * @param option Pointer to the text font weight configuration object to be modified.
 * @param enable Whether to enable the text font weight to be updated along with the font weight level of the device. **
 *     true** indicates that the text font weight is automatically updated when the font weight level of the device
 *     changes. **false** indicates that the text font weight is not automatically updated when the font weight level
 *     of the device changes. The default value is **true**.
 * @since 24
 */
void OH_ArkUI_FontWeightConfigs_SetEnableDeviceFontWeightCategory(OH_ArkUI_FontWeightConfigs* option, bool enable);

/**
 * @brief Obtains whether the text font weight is updated along with the font weight level of the device.
 *
 * @param option Pointer to the text font weight configuration object.
 * @return Whether the text font weight is updated along with the font weight level of the device.
 *     <br>**true** indicates that the text font weight is automatically updated when the font weight level of the
 *     device changes.
 *     <br>**false** indicates that the text font weight is not automatically updated when the font weight level of the
 *     device changes.
 * @since 24
 */
bool OH_ArkUI_FontWeightConfigs_GetEnableDeviceFontWeightCategory(OH_ArkUI_FontWeightConfigs* option);

/**
 * @brief Creates a text font configuration object. When the object is no longer used, call
 * {@link OH_ArkUI_FontConfigs_Destroy} to destroy it and release resources to avoid memory leaks.
 *
 * @return Pointer to the text font configuration object. If creation fails, a null pointer is returned. After use,
 *     call {@link OH_ArkUI_FontConfigs_Destroy} to destroy it.
 * @since 24
 */
OH_ArkUI_FontConfigs* OH_ArkUI_FontConfigs_Create();

/**
 * @brief Destroys the text font configuration object. This API must be used in pair with
 * {@link OH_ArkUI_FontConfigs_Create}; otherwise, memory leaks will occur.
 *
 * @param option Pointer to the text font configuration object to be destroyed.
 * @since 24
 */
void OH_ArkUI_FontConfigs_Destroy(OH_ArkUI_FontConfigs* option);

/**
 * @brief Sets the text font weight configurations for the text font configuration object.
 *
 * @param option Pointer to the text font configuration object to be modified.
 * @param fontWeightConfigs Pointer to the text font weight configuration. When this parameter is not a null pointer,
 *     if the user does not explicitly set it, each configuration item uses the default value (variable font weight
 *     adjustment is disabled by default, and the text font weight following the device font weight level update is
 *     enabled by default). When this parameter is a null pointer, the above default values are not applied, and the
 *     text font weight behavior keeps consistent with that of the parent component.
 * @since 24
 */
void OH_ArkUI_FontConfigs_SetFontWeightConfigs(OH_ArkUI_FontConfigs* option,
    OH_ArkUI_FontWeightConfigs* fontWeightConfigs);

/**
 * @brief Obtains the text font weight configurations of the text font configuration object.
 *
 * @param option Pointer to the text font configuration object. If not set or set to a null pointer, a null pointer is
 *     returned.
 * @return Pointer to the text font weight configuration object.
 * @since 24
 */
OH_ArkUI_FontWeightConfigs* OH_ArkUI_FontConfigs_GetFontWeightConfigs(OH_ArkUI_FontConfigs* option);

/**
 * @brief Defines a text line spacing option object, which is used to set whether the text line spacing takes effect
 * only between lines. You can create a line spacing option object by calling
 * {@link OH_ArkUI_NativeModule_LineSpacingOptions_Create}. After the object is used, you must call
 * {@link OH_ArkUI_NativeModule_LineSpacingOptions_Destroy} to destroy it and release resources. The two APIs must be
 * used in pairs; otherwise, a memory leak occurs. After the object is created, you can call
 * {@link OH_ArkUI_NativeModule_LineSpacingOptions_SetOnlyBetweenLines} to set whether the line spacing takes effect
 * only between lines, and call {@link OH_ArkUI_NativeModule_LineSpacingOptions_GetOnlyBetweenLines} to obtain the line
 * spacing configuration. This struct is applicable to scenarios that require precise control over the display effect
 * of text line spacing, such as text display where no line spacing is added to the first and last lines.
 *
 * @since 26.0.1
 */
typedef struct OH_ArkUI_NativeModule_LineSpacingOptions OH_ArkUI_NativeModule_LineSpacingOptions;

/**
 * @brief Creates a text line spacing option object. After use, call
 * {@link OH_ArkUI_NativeModule_LineSpacingOptions_Destroy} to destroy the object.
 *
 * @return Pointer to the {@link OH_ArkUI_NativeModule_LineSpacingOptions} object.
 * @release OH_ArkUI_NativeModule_LineSpacingOptions_Destroy {return}
 * @since 26.0.1
 */
OH_ArkUI_NativeModule_LineSpacingOptions *OH_ArkUI_NativeModule_LineSpacingOptions_Create();

/**
 * @brief Destroys a text line spacing option object.
 *
 * @param options Pointer to the {@link OH_ArkUI_NativeModule_LineSpacingOptions} object.
 * @since 26.0.1
 */
void OH_ArkUI_NativeModule_LineSpacingOptions_Destroy(OH_ArkUI_NativeModule_LineSpacingOptions *options);

/**
 * @brief Sets the **onlyBetweenLines** parameter of the text line spacing options. When set to **true**, the line
 * spacing is applied only between lines, with no extra line spacing above the first line or below the last line. When
 * set to **false**, line spacing also exists above the first line and below the last line.
 *
 * @param options Pointer to the {@link OH_ArkUI_NativeModule_LineSpacingOptions} object.
 * @param onlyBetweenLines Whether the line spacing is applied only between lines. The value **true** indicates that
 *     the line spacing is applied only between lines, and **false** indicates that line spacing also exists above the
 *     first line and below the last line. The default value is **false**.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the **options** parameter is a null pointer.
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_LineSpacingOptions_SetOnlyBetweenLines(
    OH_ArkUI_NativeModule_LineSpacingOptions *options, bool onlyBetweenLines);

/**
 * @brief Obtains the **onlyBetweenLines** parameter of the text line spacing options.
 *
 * @param options Pointer to the {@link OH_ArkUI_NativeModule_LineSpacingOptions} object.
 * @param onlyBetweenLines Output parameter, which is a pointer to a variable of the bool type, used to receive the
 *     value. The value **true** indicates that the line spacing is applied only between lines, and the value **false**
 *     indicates that the line spacing also exists above the first line and below the last line. The default value is **
 *     false**.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if any parameter is a null pointer.
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_LineSpacingOptions_GetOnlyBetweenLines(
    const OH_ArkUI_NativeModule_LineSpacingOptions *options, bool *onlyBetweenLines);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_H
/** @} */
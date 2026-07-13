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
 * @brief Defines a set of Text enum and interface.
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
#include "text_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义字体样式枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 标准字体样式。 */
    ARKUI_FONT_STYLE_NORMAL = 0,
    /** 斜体字体样式。 */
    ARKUI_FONT_STYLE_ITALIC
} ArkUI_FontStyle;
/**
 * @brief 定义字体粗细/字重枚举值。
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
    /** 字体较粗。 */
    ARKUI_FONT_WEIGHT_BOLD,
    /** 字体粗细正常。 */
    ARKUI_FONT_WEIGHT_NORMAL,
    /** 字体非常粗。 */
    ARKUI_FONT_WEIGHT_BOLDER,
    /** 字体较细。 */
    ARKUI_FONT_WEIGHT_LIGHTER,
    /** 字体粗细适中。 */
    ARKUI_FONT_WEIGHT_MEDIUM,
    /** 字体粗细正常。 */
    ARKUI_FONT_WEIGHT_REGULAR
} ArkUI_FontWeight;
/**
 * @brief 定义文本自适应高度的方式。
 *
 * @since 12
 */
typedef enum {
    /** 设置文本高度自适应方式为以MaxLines优先。 */
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST = 0,
    /** 设置文本高度自适应方式为以缩小字体优先。*/
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST,
    /** 设置文本高度自适应方式为以布局约束（高度）优先。*/
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST
} ArkUI_TextHeightAdaptivePolicy;
/**
 * @brief 定义文本识别的实体类型。
 *
 * @since 12
 */
typedef enum {
    /** 电话号码。*/
    ARKUI_TEXT_DATA_DETECTOR_TYPE_PHONE_NUMBER = 0,
    /** 链接。 */
    ARKUI_TEXT_DATA_DETECTOR_TYPE_URL,
    /** 邮箱。 */
    ARKUI_TEXT_DATA_DETECTOR_TYPE_EMAIL,
    /** 地址。 */
    ARKUI_TEXT_DATA_DETECTOR_TYPE_ADDRESS
} ArkUI_TextDataDetectorType;
/**
 * @brief 定义文本实体识别的配置。
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextDataDetectorConfig OH_ArkUI_TextDataDetectorConfig;
/**
 * @brief 定义跑马灯启动策略枚举。
 *
 * @since 23
 */
typedef enum {
    /** 默认持续滚动。 */
    ARKUI_MARQUEESTARTPOLICY_DEFAULT = 0,
    /** 获焦以及鼠标悬浮时开始滚动。 */
    ARKUI_MARQUEESTARTPOLICY_ONFOCUS = 1
} ArkUI_MarqueeStartPolicy;
/**
 * @brief 定义跑马灯更新策略枚举。
 *
 * @since 23
 */
typedef enum {
    /** 跑马灯组件属性更新后，从开始位置，运行跑马灯效果。 */
    ARKUI_MARQUEEUPDATEPOLICY_DEFAULT = 0,
    /** 跑马灯组件属性更新后，保持当前位置，运行跑马灯效果。 */
    ARKUI_MARQUEEUPDATEPOLICY_PRESERVEPOSITION = 1
} ArkUI_MarqueeUpdatePolicy;
/**
 * @brief 定义文本跑马灯选项类型。
 *
 * @since 23
 */
typedef struct ArkUI_TextMarqueeOptions ArkUI_TextMarqueeOptions;
/**
 * @brief 定义文本控制器。
 * @since 26.0.0
 */
typedef struct OH_ArkUI_TextController OH_ArkUI_TextController;
/**
 * @brief 定义文本的字体粗细配置。
 *
 * @since 24
 */
typedef struct OH_ArkUI_FontWeightConfigs OH_ArkUI_FontWeightConfigs;
/**
 * @brief 定义文本的字体配置。
 *
 * @since 24
 */
typedef struct OH_ArkUI_FontConfigs OH_ArkUI_FontConfigs;

/**
 * @brief 创建文本跑马灯模式配置项。
 *
 * @return 创建文本跑马灯模式配置项的对象指针。
 * @since 23
 */
ArkUI_TextMarqueeOptions* OH_ArkUI_TextMarqueeOptions_Create();

/**
 * @brief 销毁文本跑马灯模式配置项指针。
 *
 * @param option 需要销毁的文本跑马灯模式配置项对象指针。
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_Dispose(ArkUI_TextMarqueeOptions* option);

/**
 * @brief 设置文本跑马灯模式配置项是否播放。
 *
 * @param option 文本跑马灯模式配置项。
 * @param start 是否播放。true表示播放，false表示不播放。
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetStart(ArkUI_TextMarqueeOptions* option, bool start);

/**
 * @brief 获取文本跑马灯模式配置项是否播放。
 *
 * @param option 文本跑马灯模式配置项。
 * @return 是否播放。true表示播放，false表示不播放。
 * @since 23
 */
bool OH_ArkUI_TextMarqueeOptions_GetStart(ArkUI_TextMarqueeOptions* option);

/**
 * @brief 设置文本跑马灯模式配置项的步长。
 *
 * @param option 文本跑马灯模式配置项。
 * @param step 步长。单位：vp。
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetStep(ArkUI_TextMarqueeOptions* option, float step);

/**
 * @brief 获取文本跑马灯模式配置项的步长。
 *
 * @param option 文本跑马灯模式配置项。
 * @return 步长。单位：vp。
 * @since 23
 */
float OH_ArkUI_TextMarqueeOptions_GetStep(ArkUI_TextMarqueeOptions* option);

/**
 * @brief 设置文本跑马灯模式配置项的首尾间距。
 *
 * @param option 文本跑马灯模式配置项。
 * @param spacing 首尾间距。单位：vp。
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetSpacing(ArkUI_TextMarqueeOptions* option, float spacing);

/**
 * @brief 获取文本跑马灯模式配置项的首尾间距。
 *
 * @param option 文本跑马灯模式配置项。
 * @return 首尾间距。单位：vp。
 * @since 23
 */
float OH_ArkUI_TextMarqueeOptions_GetSpacing(ArkUI_TextMarqueeOptions* option);

/**
 * @brief 设置文本跑马灯模式配置项的重复滚动的次数，小于等于零时无限循环。
 *
 * @param option 文本跑马灯模式配置项。
 * @param loop 重复滚动的次数。
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetLoop(ArkUI_TextMarqueeOptions* option, int32_t loop);

/**
 * @brief 获取文本跑马灯模式配置项的重复滚动的次数。
 *
 * @param option 文本跑马灯模式配置项。
 * @return 重复滚动的次数。
 * @since 23
 */
int32_t OH_ArkUI_TextMarqueeOptions_GetLoop(ArkUI_TextMarqueeOptions* option);

/**
 * @brief 设置文本跑马灯模式配置项的运行方向。
 *
 * @param option 文本跑马灯模式配置项。
 * @param fromStart 跑马灯运行方向。true表示从头开始滚动，false表示反向滚动。
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetFromStart(ArkUI_TextMarqueeOptions* option, bool fromStart);

/**
 * @brief 获取文本跑马灯模式配置项的运行方向。
 *
 * @param option 文本跑马灯模式配置项。
 * @return 跑马灯运行方向。true表示从头开始滚动，false表示反向滚动。
 * @since 23
 */
bool OH_ArkUI_TextMarqueeOptions_GetFromStart(ArkUI_TextMarqueeOptions* option);

/**
 * @brief 设置文本跑马灯模式配置项的每轮滚动延迟时间。
 *
 * @param option 文本跑马灯模式配置项。
 * @param delay 每轮滚动延迟时间，单位为毫秒。
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetDelay(ArkUI_TextMarqueeOptions* option, int32_t delay);

/**
 * @brief 获取文本跑马灯模式配置项的每轮滚动延迟时间。
 *
 * @param option 文本跑马灯模式配置项。
 * @return 返回每轮滚动延迟时间，单位为毫秒。
 * @since 23
 */
int32_t OH_ArkUI_TextMarqueeOptions_GetDelay(ArkUI_TextMarqueeOptions* option);

/**
 * @brief 设置文本跑马灯模式配置项是否支持文字超长时的渐隐效果。当Text内容超出显示范围时，未完全展现的文字边缘将应用渐隐效果。
 *        若两端均有文字未完全显示，则两端同时应用渐隐效果。
 *        在渐隐效果开启状态下，{@link ArkUI_NodeAttributeType}中的NODE_CLIP属性将自动锁定为true，不允许设置为false。
 *
 * @param option 文本跑马灯模式配置项。
 * @param fadeout 跑马灯是否支持文字超长时的渐隐效果。true表示支持渐隐效果，false表示不支持渐隐效果。
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetFadeout(ArkUI_TextMarqueeOptions* option, bool fadeout);

/**
 * @brief 获取文本跑马灯模式配置项是否支持文字超长时的渐隐效果。
 *
 * @param option 文本跑马灯模式配置项。
 * @return 是否支持文字超长时的渐隐效果。
 * @since 23
 */
bool OH_ArkUI_TextMarqueeOptions_GetFadeout(ArkUI_TextMarqueeOptions* option);

/**
 * @brief 设置文本跑马灯模式配置项的启动策略。
 *
 * @param option 文本跑马灯模式配置项。
 * @param startPolicy 启动策略。
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetStartPolicy(ArkUI_TextMarqueeOptions* option, ArkUI_MarqueeStartPolicy startPolicy);

/**
 * @brief 获取文本跑马灯模式配置项的启动策略。
 *
 * @param option 文本跑马灯模式配置项。
 * @return 启动策略。
 * @since 23
 */
ArkUI_MarqueeStartPolicy OH_ArkUI_TextMarqueeOptions_GetStartPolicy(ArkUI_TextMarqueeOptions* option);

/**
 * @brief 设置文本跑马灯模式配置项的更新策略。
 *
 * @param option 文本跑马灯模式配置项。
 * @param updatePolicy 更新策略。
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetUpdatePolicy(ArkUI_TextMarqueeOptions* option,
    ArkUI_MarqueeUpdatePolicy updatePolicy);

/**
 * @brief 获取文本跑马灯模式配置项的更新策略。
 *
 * @param option 文本跑马灯模式配置项。
 * @return 更新策略。
 * @since 23
 */
ArkUI_MarqueeUpdatePolicy OH_ArkUI_TextMarqueeOptions_GetUpdatePolicy(ArkUI_TextMarqueeOptions* option);
/**
 * @brief 创建一个文本实体识别配置对象。
 * 当该对象不再使用时，请调用{@link OH_ArkUI_TextDataDetectorConfig_Destroy}销毁。
 *
 * @return 指向{@link OH_ArkUI_TextDataDetectorConfig}对象的指针。
 * @since 24
 */
OH_ArkUI_TextDataDetectorConfig* OH_ArkUI_TextDataDetectorConfig_Create();

/**
 * @brief 销毁文本实体识别配置对象。
 *
 * @param config 指向{@link OH_ArkUI_TextDataDetectorConfig}对象的指针。
 * @since 24
 */
void OH_ArkUI_TextDataDetectorConfig_Destroy(OH_ArkUI_TextDataDetectorConfig* config);
/**
 * @brief 创建一个文本控制器对象。
 *
 * @return 返回指向文本控制器对象的指针。
 * @since 26.0.0
 */
OH_ArkUI_TextController* OH_ArkUI_TextController_Create();

/**
 * @brief 销毁文本控制器。
 *
 * @param controller 文本的控制器。
 * @since 26.0.0
 */
void OH_ArkUI_TextController_Destroy(OH_ArkUI_TextController* controller);
/**
 * @brief 创建文本字体粗细配置对象。
 *
 * @return 返回指向文本字体粗细配置对象的指针。如果创建失败，返回空指针。
 * @since 24
 */
OH_ArkUI_FontWeightConfigs* OH_ArkUI_FontWeightConfigs_Create();

/**
 * @brief 销毁文本字体粗细配置对象。
 *
 * @param option 指向要销毁的文本字体粗细配置对象的指针。
 * @since 24
 */
void OH_ArkUI_FontWeightConfigs_Destroy(OH_ArkUI_FontWeightConfigs* option);

/**
 * @brief 设置是否启用可变字重调节。
 *
 * @param option 指向待修改的文本字体粗细配置对象的指针。
 * @param enable 是否启用可变字重调节。
 *               true表示启用可变字重调节。此时如果设置的字重weight取值为[100, 900]范围内任意整数，则字重取值为weight，否则取默认值400。
 *               false表示禁用可变字重调节。此时如果设置的字重weight取值为[100, 900]范围内的整百数值，字重取值为weight；weight是非整百数值时，字重取默认值400。
 *               默认值为false。
 * @since 24
 */
void OH_ArkUI_FontWeightConfigs_SetEnableVariableFontWeight(OH_ArkUI_FontWeightConfigs* option, bool enable);

/**
 * @brief 获取文本字体粗细配置对象是否启用了可变字重调节。
 *
 * @param option 指向文本字体粗细配置对象的指针。
 * @return 返回是否启用可变字重调节。
 *  *      true表示启用可变字重调节。此时如果设置的字重weight取值为[100, 900]范围内任意整数，则字重取值为weight，否则取默认值400。
 *         false表示禁用可变字重调节。此时如果设置的字重weight取值为[100, 900]范围内的整百数值，字重取值为weight；weight是非整百数值时，字重取默认值400。
 *         默认值为false。字重weight取值为[100, 900]范围外的值，字重取默认值400。
 * @since 24
 */
bool OH_ArkUI_FontWeightConfigs_GetEnableVariableFontWeight(OH_ArkUI_FontWeightConfigs* option);

/**
 * @brief 设置设备的字体粗细级别改变时文本字体粗细是否自动更新。
 *
 * @param option 指向待修改的文本文本字体粗配置对象的指针。
 * @param enable 是否启用文本字体粗细跟随设备的字体粗细级别更新。
 *               true表示当设备的字体粗细级别改变时，文本字体粗细将自动更新。
 *               false表示当设备的字体粗细级别改变时，文本字体粗不会自动更新。
 *               默认值为true。
 * @since 24
 */
void OH_ArkUI_FontWeightConfigs_SetEnableDeviceFontWeightCategory(OH_ArkUI_FontWeightConfigs* option, bool enable);

/**
 * @brief 获取文本字体粗细是否跟随设备的字体粗细级别更新。
 *
 * @param option 指向文本字体粗细配置对象的指针。
 * @return 返回文本字体粗细是否跟随设备的字体粗细级别更新。
 *         true表示当设备的字体粗细级别改变时，文本字体粗细将自动更新。
 *         false表示当设备的字体粗细级别改变时，文本字体粗细不会自动更新。
 * @since 24
 */
bool OH_ArkUI_FontWeightConfigs_GetEnableDeviceFontWeightCategory(OH_ArkUI_FontWeightConfigs* option);
/**
 * @brief 创建文本字体配置对象。
 *
 * @return 返回指向文本字体配置对象的指针。如果创建失败，返回空指针。
 * @since 24
 */
OH_ArkUI_FontConfigs* OH_ArkUI_FontConfigs_Create();

/**
 * @brief 销毁文本字体配置对象。
 *
 * @param option 指向要销毁的文本字体配置对象的指针。
 * @since 24
 */
void OH_ArkUI_FontConfigs_Destroy(OH_ArkUI_FontConfigs* option);

/**
 * @brief 设置文本字体配置对象的文本字体粗细配置。
 *
 * @param option 指向待修改的文本字体配置对象的指针。
 * @param fontWeightConfigs 文本字体粗细配置。
 *        当该配置不为空指针时，若用户未显式设置，各项配置将使用默认值（可变字重调节默认为禁用，文本字体粗细跟随设备字体粗细级别更新默认为启用）。
 *        当该配置为空指针时，不应用上述默认值，文本字体粗细行为与父组件保持一致。
 * @since 24
 */
void OH_ArkUI_FontConfigs_SetFontWeightConfigs(OH_ArkUI_FontConfigs* option,
    OH_ArkUI_FontWeightConfigs* fontWeightConfigs);

/**
 * @brief 获取文本字体配置对象的文本字体粗细配置。
 *
 * @param option 指向文本字体配置对象的指针。
 * @return 返回文本字体粗细配置。
 * @since 24
 */
OH_ArkUI_FontWeightConfigs* OH_ArkUI_FontConfigs_GetFontWeightConfigs(OH_ArkUI_FontConfigs* option);
#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_H
/** @} */
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
 * @brief ArkUI Grid related types and functions on the native side.
 *
 * @since 22
 */

/**
 * @file node_grid.h
 *
 * @brief Provides Grid-related type and function definitions for <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUIKit
 * @since 22
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_GRID_GRID_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_GRID_GRID_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the return value for the **onGetIrregularSizeByIndex** callback in **Grid** layout options.
 *
 * @since 22
 */
typedef struct {
    /**
     * Number of rows occupied by the **GridItem** component.
     */
    uint32_t rowSpan;

    /**
     * Number of columns occupied by the **GridItem** component.
     */
    uint32_t columnSpan;
} ArkUI_GridItemSize;

/**
 * @brief Defines the return value for the **onGetRectByIndex** callback in **Grid** layout options.
 *
 * @since 22
 */
typedef struct {
    /**
     * Starting row position of the **GridItem** component.
     */
    uint32_t rowStart;

    /**
     * Starting column position of the **GridItem** component.
     */
    uint32_t columnStart;

    /**
     * Number of rows occupied by the **GridItem** component.
     */
    uint32_t rowSpan;

    /**
     * Number of columns occupied by the **GridItem** component.
     */
    uint32_t columnSpan;
} ArkUI_GridItemRect;

/**
 * @brief 定义Grid布局选项。
 *
 * @since 22
 */
typedef struct ArkUI_GridLayoutOptions ArkUI_GridLayoutOptions;

/**
 * @brief GridItem对齐方式枚举。
 *
 * @since 22
 */
typedef enum {
    /** Grid的默认对齐方式。*/
    GRID_ITEM_ALIGNMENT_DEFAULT = 0,

    /** 以一行中的最高的GridItem作为其他GridItem的高度。*/
    GRID_ITEM_ALIGNMENT_STRETCH = 1
} ArkUI_GridItemAlignment;

/**
 * @brief GridItem样式枚举。
 *
 * @since 22
 */
typedef enum {
    /** 无样式。*/
    GRID_ITEM_STYLE_NONE = 0,

    /** 显示Hover、Press态样式。*/
    GRID_ITEM_STYLE_PLAIN = 1
} ArkUI_GridItemStyle;

/**
 * @brief 创建Grid布局选项。
 *
 * @return Grid布局选项。
 * @since 22
 */
ArkUI_GridLayoutOptions* OH_ArkUI_GridLayoutOptions_Create();

/**
 * @brief 销毁Grid布局选项。
 *
 * @param option Grid布局选项。
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_Dispose(ArkUI_GridLayoutOptions* option);
/**
 * @brief 设置Grid中不规则GridItem的索引数组。
 *
 * @param option Grid布局选项。
 * @param irregularIndexes GridItem索引数组。
 * @param size GridItem索引数组大小。
 * @return 错误码。
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *         异常原因：传入参数验证失败，参数不能为空。
 * @since 22
 */
int32_t OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(
    ArkUI_GridLayoutOptions* option, uint32_t* irregularIndexes, int32_t size);
/**
 * @brief 获取Grid中不规则GridIte的索引数组。当不设置OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback时，
 * irregularIndexes中GridItem的默认大小为垂直滚动Grid的一整行或水平滚动Grid的一整列。
 *
 * @param option Grid布局选项。
 * @param irregularIndexes GridItem索引数组。
 * @param size GridItem索引数组大小。
 * @return 错误码。
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *         {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 数组大小不够。
 *         异常原因：传入参数验证失败，参数不能为空。
 * @since 22
 */
int32_t OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(
    ArkUI_GridLayoutOptions* option, uint32_t* irregularIndexes, int32_t* size);

/**
 * @brief Grid布局选项通过GridItem索引获取指定Item占用的行列数。
 *
 * @param option Grid布局选项。
 * @param userData 用户自定义数据。
 * @param callback 根据index获取指定Item占用的行列数。
 *        itemIndex：GridItem索引值，取值范围来自{@link OH_ArkUI_GridLayoutOptions_SetIrregularIndexes}。
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback(
    ArkUI_GridLayoutOptions* option, void* userData, ArkUI_GridItemSize (*callback)(int32_t itemIndex, void* userData));

/**
 * @brief Grid布局选项通过GridItem索引获取指定Item的起始行列和占用的行列数。
 *
 * @param option Grid布局选项。
 * @param userData 用户自定义数据。
 * @param callback 根据index获取指定Item的起始行列和占用的行列数。
 *        itemIndex：GridItem索引值。
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_RegisterGetRectByIndexCallback(
    ArkUI_GridLayoutOptions* option, void* userData, ArkUI_GridItemRect (*callback)(int32_t itemIndex, void* userData));

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_GRID_GRID_H

/** @} */
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
 * @file grid.h
 *
 * @brief 定义Grid组件相关的枚举和接口。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 22
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_GRID_GRID_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_GRID_GRID_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义Grid布局选项{@link OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback}回调返回值结构体，
 * 用于通过GridItem索引指定不规则GridItem占用的行数和列数。
 *
 * @since 22
 */
typedef struct {
    /**
     * GridItem占用的行数，用于设置GridItem在行方向上的跨度。取值范围：[1, +∞)，设置为0时按1处理；Grid横向布局时，超过Grid实际行数的值按实际行数处理。
     */
    uint32_t rowSpan;

    /**
     * GridItem占用的列数，用于设置GridItem在列方向上的跨度。取值范围：[1, +∞)，设置为0时按1处理；Grid纵向布局时，超过Grid实际列数的值按实际列数处理。
     */
    uint32_t columnSpan;
} ArkUI_GridItemSize;

/**
 * @brief 定义Grid布局选项{@link OH_ArkUI_GridLayoutOptions_RegisterGetRectByIndexCallback}回调返回值结构体，
 * 用于通过GridItem索引指定该GridItem在Grid中的起始行列位置和占用的行列数。
 *
 * @since 22
 */
typedef struct {
    /**
     * GridItem行起始位置，从0开始计数，用于确定GridItem在Grid中的起始行。
     */
    uint32_t rowStart;

    /**
     * GridItem列起始位置，从0开始计数，用于确定GridItem在Grid中的起始列。
     */
    uint32_t columnStart;

    /**
     * GridItem占用的行数，用于设置GridItem在行方向上的跨度。取值范围：[1, +∞)，设置为0时按1处理；Grid横向布局时，超过Grid实际行数的值按实际行数处理。
     */
    uint32_t rowSpan;

    /**
     * GridItem占用的列数，用于设置GridItem在列方向上的跨度。取值范围：[1, +∞)，设置为0时按1处理；Grid纵向布局时，超过Grid实际列数的值按实际列数处理。
     */
    uint32_t columnSpan;
} ArkUI_GridItemRect;

/**
 * @brief 定义Grid（网格）布局选项，用于配置Grid组件中不规则GridItem的布局参数，包括不规则项索引和布局回调。不规则GridItem是指在网格布局中跨行跨列或尺寸不同的网格项。
 *
 * @since 22
 */
typedef struct ArkUI_GridLayoutOptions ArkUI_GridLayoutOptions;

/**
 * @brief {@link GridItem}对齐方式枚举。
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
 * @brief 创建Grid布局选项。使用完毕后调用OH_ArkUI_GridLayoutOptions_Dispose销毁。
 *
 * @return 创建的Grid布局选项。
 * @since 22
 */
ArkUI_GridLayoutOptions* OH_ArkUI_GridLayoutOptions_Create();

/**
 * @brief 销毁Grid布局选项并释放资源。
 *
 * @param option 待销毁的Grid布局选项。
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_Dispose(ArkUI_GridLayoutOptions* option);
/**
 * @brief 设置Grid中不规则GridItem的索引数组。
 *
 * @param option 待设置的Grid布局选项。
 * @param irregularIndexes 用于设置Grid布局选项的不规则GridItem索引数组。
 * @param size irregularIndexes数组元素个数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID}  函数参数异常。
 *     <br>异常原因：传入参数验证失败，参数不能为空。
 * @since 22
 */
int32_t OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(
    ArkUI_GridLayoutOptions* option, uint32_t* irregularIndexes, int32_t size);
/**
 * @brief 获取Grid中不规则GridItem的索引数组。当不设置OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback时，
 * irregularIndexes中GridItem的默认大小为垂直滚动Grid的一整行或水平滚动Grid的一整列。
 *
 * @param option 待获取的Grid布局选项。
 * @param irregularIndexes 用于接收不规则GridItem索引数组的缓冲区。
 * @param size irregularIndexes缓冲区可容纳的元素个数。调用前传入缓冲区容量，调用成功后更新为实际写入的索引数量。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} 数组大小不够。
 *     <br>异常原因：传入参数验证失败，参数不能为空。
 * @since 22
 */
int32_t OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(
    ArkUI_GridLayoutOptions* option, uint32_t* irregularIndexes, int32_t* size);

/**
 * @brief Grid布局选项通过GridItem索引获取指定Item占用的行列数。
 *
 * @param option Grid布局选项。
 * @param userData 用户自定义数据。
 * @param callback 根据index获取指定Item占用的行列数。itemIndex: GridItem索引值，取值范围来自
 *     {@link OH_ArkUI_GridLayoutOptions_SetIrregularIndexes}.
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback(
    ArkUI_GridLayoutOptions* option, void* userData, ArkUI_GridItemSize (*callback)(int32_t itemIndex, void* userData));

/**
 * @brief Grid布局选项通过GridItem索引获取指定Item的起始行列和占用的行列数。
 *
 * @param option Grid布局选项。
 * @param userData 用户自定义数据。
 * @param callback Grid布局选项通过GridItem索引获取指定Item的起始行列和占用的行列数。
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_RegisterGetRectByIndexCallback(
    ArkUI_GridLayoutOptions* option, void* userData, ArkUI_GridItemRect (*callback)(int32_t itemIndex, void* userData));

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_GRID_GRID_H

/** @} */
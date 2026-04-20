/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup Drawing
 * @{
 *
 * @brief Provides functions such as 2D graphics rendering, text drawing, and image display.
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file drawing_region.h
 *
 * @brief This file declares the functions related to the region in the drawing module, including creating a region,
 * setting the boundary, and destroying a region.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_REGION_H
#define C_INCLUDE_DRAWING_REGION_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 区域操作类型枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 差集操作。
     */
    REGION_OP_MODE_DIFFERENCE,
    /**
     * 交集操作。
     */
    REGION_OP_MODE_INTERSECT,
    /**
     * 并集操作。
     */
    REGION_OP_MODE_UNION,
    /**
     * 异或操作。
     */
    REGION_OP_MODE_XOR,
    /**
     * 反向差集操作。
     */
    REGION_OP_MODE_REVERSE_DIFFERENCE,
    /**
     * 替换操作。
     */
    REGION_OP_MODE_REPLACE,
} OH_Drawing_RegionOpMode;

/**
 * @brief 用于创建一个区域对象，实现更精确的图形控制。
 *
 * @return 函数会返回一个指针，指针指向创建的区域对象{@link OH_Drawing_Region}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Region* OH_Drawing_RegionCreate(void);

/**
 * @brief 用于创建一个区域对象的拷贝。
 *
 * @param region 指向用于拷贝的区域对象{@link OH_Drawing_Region}的指针。
 * @return 函数会返回一个指针，指针指向创建的新区域对象。
 * @since 20
 * @version 1.0
 */
OH_Drawing_Region* OH_Drawing_RegionCopy(const OH_Drawing_Region* region);

/**
 * @brief 判断区域是否包含指定坐标点。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * region为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @param x 表示指定坐标点的x轴坐标。
 * @param y 表示指定坐标点的y轴坐标。
 * @return 返回区域是否包含指定坐标点。true表示区域包含该坐标点，false表示区域不包含该坐标点。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_RegionContains(OH_Drawing_Region* region, int32_t x, int32_t y);

/**
 * @brief 将两个区域按照指定的区域操作类型合并。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * region、dst任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * op不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针，操作完成后的区域结果将会保存在此区域对象中。
 * @param other 指向区域对象{@link OH_Drawing_Region}的指针。
 * @param op 区域操作枚举类型，支持可选的具体模式可见{@link OH_Drawing_RegionOpMode}枚举。
 * @return 返回操作后的区域是否为空。true表示区域不为空，false表示区域为空。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_RegionOp(OH_Drawing_Region* region, const OH_Drawing_Region* other, OH_Drawing_RegionOpMode op);

/**
 * @brief 用于尝试给区域对象设置矩形边界。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * region、rect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @param rect 指向矩形对象的指针。
 * @return 返回区域对象设置矩形边界是否成功的结果。true表示设置矩形边界成功，false表示设置矩形边界失败。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_RegionSetRect(OH_Drawing_Region* region, const OH_Drawing_Rect* rect);

/**
 * @brief 给区域对象设置为指定区域内路径表示的范围。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * region、path、clip任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param clip 指向区域对象{@link OH_Drawing_Region}的指针。
 * @return 返回操作后的区域是否为空。true表示区域不为空，false表示区域为空。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_RegionSetPath(OH_Drawing_Region* region, const OH_Drawing_Path* path, const OH_Drawing_Region* clip);

/**
 * @brief 用于销毁区域对象并回收该对象占有的内存。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RegionDestroy(OH_Drawing_Region* region);

/**
 * @brief 设置当前区域为空。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数region为空。
 * @since 22
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RegionEmpty(OH_Drawing_Region* region);

/**
 * @brief 设置路径为区域的边界。如果区域为空，则路径也将为空。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。作为出参使用。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示region或path是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionGetBoundaryPath(const OH_Drawing_Region* region, OH_Drawing_Path* path);

/**
 * @brief 获取包含该区域的最小边界矩形。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。作为出参使用。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示region或rect是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionGetBounds(const OH_Drawing_Region* region, OH_Drawing_Rect* rect);

/**
 * @brief 检查该区域是否包含多个（两个及两个以上）矩形。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @param isComplex 表示该区域是否包含多个矩形。作为出参使用。true表示该区域包含多个矩形，false表示该区域不包含多个矩形。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示region或isComplex是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionIsComplex(const OH_Drawing_Region* region, bool* isComplex);

/**
 * @brief 检查该区域是否为空。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @param isEmpty 表示该区域是否为空。作为出参使用。true表示该区域为空，false表示该区域不为空。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示region或isEmpty是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionIsEmpty(const OH_Drawing_Region* region, bool* isEmpty);

/**
 * @brief 检查该区域是否等同于一个矩形。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @param isRect 表示该区域是否等同于一个矩形。作为出参使用。true表示该区域等同于一个矩形，false表示该区域不等同于一个矩形。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示region或isRect是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionIsRect(const OH_Drawing_Region* region, bool* isRect);

/**
 * @brief 检查该区域是否等同于单个矩形并且包含指定的矩形。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @param left 表示指定矩形左上角的x轴坐标。
 * @param top 表示指定矩形左上角的y轴坐标。
 * @param right 表示指定矩形右下角的x轴坐标。
 * @param bottom 表示指定矩形右下角的y轴坐标。
 * @param isContained 指示该区域是否等同于单个矩形并且包含指定的矩形。作为出参使用。
 * true表示该区域等同于单个矩形并且包含指定的矩形，false表示该区域不等同于单个矩形或不包含指定的矩形。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示region或isContained是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionQuickContains(const OH_Drawing_Region* region,
    int32_t left, int32_t top, int32_t right, int32_t bottom, bool* isContained);

/**
 * @brief 检查当前区域是否为空或是否与指定矩形不相交。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @param left 表示指定矩形左上角的x轴坐标。
 * @param top 表示指定矩形左上角的y轴坐标。
 * @param right 表示指定矩形右下角的x轴坐标。
 * @param bottom 表示指定矩形右下角的y轴坐标。
 * @param isReject 表示检查区域是否为空或指定的矩形是否与区域不相交。作为出参使用。
 * true表示当前区域为空或与指定矩形不相交；false表示当前区域不为空且与指定矩形相交。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示region或isReject是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionQuickReject(const OH_Drawing_Region* region,
    int32_t left, int32_t top, int32_t right, int32_t bottom, bool* isReject);

/**
 * @brief 将当前区域在x轴和y轴上按指定距离平移。如果当前区域为空，则不执行任何操作。
 *
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @param dx 表示在x轴上要平移的距离，单位为像素px。
 * @param dy 表示在y轴上要平移的距离，单位为像素px。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示region是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionTranslate(OH_Drawing_Region* region, int32_t dx, int32_t dy);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
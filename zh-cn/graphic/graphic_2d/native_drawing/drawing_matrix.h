/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
 * @brief Drawing模块提供包括2D图形渲染、文字绘制和图片显示等功能函数。
 * <br>本模块采用屏幕物理像素单位px。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @since 11
 * @version 1.0
 */
/**
 * @file drawing_matrix.h
 *
 * @brief 文件中定义了矩阵的创建、拷贝、变换（旋转、缩放、平移、倾斜）、查询（判断相等、判断单位矩阵、
 * 获取元素值）和映射等功能函数。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_MATRIX_H
#define C_INCLUDE_DRAWING_MATRIX_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于创建一个矩阵对象。调用此函数创建的矩阵对象，
 * 在使用完毕后必须调用{@link OH_Drawing_MatrixDestroy}释放该对象占用的内存，否则会导致内存泄漏。
 *
 * @return 函数返回一个指针，指针指向创建的矩阵对象{@link OH_Drawing_Matrix}。
 * @since 11
 * @version 1.0
 */
OH_Drawing_Matrix* OH_Drawing_MatrixCreate(void);

/**
 * @brief 用于创建一个矩阵对象的拷贝。调用此函数返回的是一个新的独立矩阵对象，
 * 在使用完毕后必须调用{@link OH_Drawing_MatrixDestroy}单独释放拷贝对象占用的内存，否则会导致内存泄漏。
 *
 * @param matrix 指向用于拷贝的矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @return 函数返回一个指针，指针指向创建的新矩阵对象{@link OH_Drawing_Matrix}。
 * @since 20
 * @version 1.0
 */
OH_Drawing_Matrix* OH_Drawing_MatrixCopy(const OH_Drawing_Matrix* matrix);

/**
 * @brief 创建一个带旋转属性的矩阵对象。
 * <br>该矩阵对象为：单位矩阵在(x, y)旋转中心点以度为单位进行旋转后得到的矩阵。调用此函数创建的矩阵对象，
 * 在使用完毕后必须调用{@link OH_Drawing_MatrixDestroy}释放该对象占用的内存，
 * 否则会导致内存泄漏。
 *
 * @param deg 旋转的角度，单位为度。正数表示顺时针旋转，负数表示逆时针旋转。
 * @param x 旋转中心点的x轴坐标，单位为物理像素px。
 * @param y 旋转中心点的y轴坐标，单位为物理像素px。
 * @return 函数返回一个指针，指针指向创建的矩阵对象{@link OH_Drawing_Matrix}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Matrix* OH_Drawing_MatrixCreateRotation(float deg, float x, float y);

/**
 * @brief 创建一个带缩放属性的矩阵对象。
 * <br>该矩阵对象为：单位矩阵在(px, py)缩放中心点以sx和sy为缩放因子进行缩放后得到的矩阵。调用此函数创建的矩阵对象，
 * 在使用完毕后必须调用{@link OH_Drawing_MatrixDestroy}释放该对象占用的内存。
 *
 * @param sx 水平缩放因子，为负数时可看作是先关于x = px作镜像翻转后再进行缩放。
 * @param sy 垂直缩放因子，为负数时可看作是先关于y = py作镜像翻转后再进行缩放。
 * @param px 缩放中心点的x轴坐标，单位为物理像素px。
 * @param py 缩放中心点的y轴坐标，单位为物理像素px。
 * @return 函数返回一个指针，指针指向创建的矩阵对象{@link OH_Drawing_Matrix}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Matrix* OH_Drawing_MatrixCreateScale(float sx, float sy, float px, float py);

/**
 * @brief 创建一个带平移属性的矩阵对象。
 * <br>该矩阵对象为：单位矩阵平移(dx, dy)后得到的矩阵。调用此函数创建的矩阵对象，
 * 在使用完毕后必须调用{@link OH_Drawing_MatrixDestroy}释放该对象占用的内存，否则会导致内存泄漏。
 *
 * @param dx 水平方向平移距离，单位为物理像素px。正数表示往x轴正方向平移，负数表示往x轴负方向平移。
 * @param dy 垂直方向平移距离，单位为物理像素px。正数表示往y轴正方向平移，负数表示往y轴负方向平移。
 * @return 函数返回一个指针，指针指向创建的矩阵对象{@link OH_Drawing_Matrix}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Matrix* OH_Drawing_MatrixCreateTranslation(float dx, float dy);

/**
 * @brief 用于给矩阵对象设置变换参数，包括缩放、倾斜、位移和透视系数。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>OH_Drawing_Matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象的指针。
 * @param scaleX 水平缩放因子。
 * @param skewX 水平倾斜系数。
 * @param transX 水平位移系数。
 * @param skewY 垂直倾斜系数。
 * @param scaleY 垂直缩放因子。
 * @param transY 垂直位移系数。
 * @param persp0 x轴透视系数。
 * @param persp1 y轴透视系数。
 * @param persp2 透视缩放系数。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_MatrixSetMatrix(OH_Drawing_Matrix* matrix, float scaleX, float skewX, float transX,
    float skewY, float scaleY, float transY, float persp0, float persp1, float persp2);

/**
 * @brief 矩阵缩放方式枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 按水平轴和垂直轴缩放以填充目标矩形，不保留源矩形宽高比例。
     */
    SCALE_TO_FIT_FILL,
    /**
     * 缩放并对齐到左侧和顶部。
     */
    SCALE_TO_FIT_START,
    /**
     * 缩放并居中对齐。
     */
    SCALE_TO_FIT_CENTER,
    /**
     * 缩放并向右和向下对齐。
     */
    SCALE_TO_FIT_END,
} OH_Drawing_ScaleToFit;

/**
 * @brief 将矩阵以缩放方式适配目标矩形。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix、src或dst任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param src 指向源矩形对象{@link OH_Drawing_Rect}的指针。
 * @param dst 指向目标矩形对象{@link OH_Drawing_Rect}的指针。
 * @param stf 缩放方式，详见{@link OH_Drawing_ScaleToFit}。
 * @return 如果设置成功，则返回true；如果设置失败，则返回false。特殊情况：
 *     <br>如果源矩形src的宽高任意一个小于等于0，则返回false，并将矩阵设置为单位矩阵；
 *     <br>如果目标矩形dst的宽高任意一个小于等于0，则返回true，并将矩阵设置为除透视缩放系数为1外其余值皆为0的矩阵。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_MatrixSetRectToRect(OH_Drawing_Matrix* matrix, const OH_Drawing_Rect* src,
    const OH_Drawing_Rect* dst, OH_Drawing_ScaleToFit stf);

/**
 * @brief 将矩阵设置为矩阵左乘围绕旋转中心点旋转degree指定角度的单位矩阵后得到的矩阵。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param degree 旋转角度，单位为度。正数表示顺时针旋转，负数表示逆时针旋转。
 * @param px 旋转中心点的x轴坐标，单位为物理像素px。
 * @param py 旋转中心点的y轴坐标，单位为物理像素px。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixPreRotate(OH_Drawing_Matrix* matrix, float degree, float px, float py);

/**
 * @brief 将矩阵设置为矩阵左乘围绕缩放中心点按缩放因子sx和sy缩放后的单位矩阵后得到的矩阵。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param sx 水平缩放因子，为负数时可看作是先关于x = px作镜像翻转后再进行缩放。
 * @param sy 垂直缩放因子，为负数时可看作是先关于y = py作镜像翻转后再进行缩放。
 * @param px 缩放中心点的x轴坐标，单位为物理像素px。
 * @param py 缩放中心点的y轴坐标，单位为物理像素px。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixPreScale(OH_Drawing_Matrix* matrix, float sx, float sy, float px, float py);

/**
 * @brief 将矩阵设置为矩阵左乘平移dx和dy距离后的单位矩阵后得到的矩阵。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param dx 水平方向平移距离，单位为物理像素px。正数表示往x轴正方向平移，负数表示往x轴负方向平移。
 * @param dy 垂直方向平移距离，单位为物理像素px。正数表示往y轴正方向平移，负数表示往y轴负方向平移。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixPreTranslate(OH_Drawing_Matrix* matrix, float dx, float dy);

/**
 * @brief 将矩阵设置为矩阵右乘围绕旋转中心点旋转degree角度的单位矩阵后得到的矩阵。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param degree 旋转角度，单位为度。正数表示顺时针旋转，负数表示逆时针旋转。
 * @param px 旋转中心点的x轴坐标，单位为物理像素px。
 * @param py 旋转中心点的y轴坐标，单位为物理像素px。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixPostRotate(OH_Drawing_Matrix* matrix, float degree, float px, float py);

/**
 * @brief 将矩阵设置为矩阵右乘围绕缩放中心点按sx和sy缩放因子缩放后的单位矩阵后得到的矩阵。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param sx 水平缩放因子，为负数时可看作是先关于x = px作镜像翻转后再进行缩放。
 * @param sy 垂直缩放因子，为负数时可看作是先关于y = py作镜像翻转后再进行缩放。
 * @param px 缩放中心点的x轴坐标，单位为物理像素px。
 * @param py 缩放中心点的y轴坐标，单位为物理像素px。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixPostScale(OH_Drawing_Matrix* matrix, float sx, float sy, float px, float py);

/**
 * @brief 将矩阵设置为矩阵右乘平移dx和dy距离后的单位矩阵后得到的矩阵。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param dx 水平方向平移距离，单位为物理像素px。正数表示往x轴正方向平移，负数表示往x轴负方向平移。
 * @param dy 垂直方向平移距离，单位为物理像素px。正数表示往y轴正方向平移，负数表示往y轴负方向平移。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixPostTranslate(OH_Drawing_Matrix* matrix, float dx, float dy);

/**
 * @brief 重置当前矩阵为单位矩阵。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixReset(OH_Drawing_Matrix* matrix);

/**
 * @brief 将矩阵total设置为矩阵a乘以矩阵b。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>total、a或b任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param total 指向最终的矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param a 指向矩阵对象a{@link OH_Drawing_Matrix}的指针。
 * @param b 指向矩阵对象b{@link OH_Drawing_Matrix}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixConcat(OH_Drawing_Matrix* total, const OH_Drawing_Matrix* a,
    const OH_Drawing_Matrix* b);

/**
 * @brief 获取矩阵所有元素值。9个元素按行主序存储，对应3×3矩阵结构，具体排列方式参见{@link OH_Drawing_MatrixSetMatrix}。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param value 用于存储得到的矩阵元素值的数组。
 * @return 返回错误码。
 *     <br>返回OH_DRAWING_SUCCESS，表示成功获取矩阵的所有元素值。
 *     <br>返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示matrix或value为NULL。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_MatrixGetAll(OH_Drawing_Matrix* matrix, float value[9]);

/**
 * @brief 对矩阵a左乘矩阵b。与{@link OH_Drawing_MatrixConcat}功能类似，
 * 区别在于OH_Drawing_MatrixConcat将结果存入单独的total矩阵，而本方法直接修改矩阵a。
 *
 * @param a 指向被左乘的矩阵对象{@link OH_Drawing_Matrix}的指针，左乘后该矩阵会被修改为a × b的结果。
 * @param b 指向作为乘数的矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @return 返回错误码。
 *     <br>返回OH_DRAWING_SUCCESS，表示成功执行左乘方法。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示a或b为NULL。
 * @since 22
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_MatrixPreConcat(OH_Drawing_Matrix* a, OH_Drawing_Matrix* b);

/**
 * @brief 获取矩阵给定索引位的值。索引范围0-8。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * <br>index小于0或者大于8时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param index 索引位置，范围0-8。
 * @return 函数返回矩阵给定索引位对应的值。
 * @since 12
 * @version 1.0
 */
float OH_Drawing_MatrixGetValue(OH_Drawing_Matrix* matrix, int index);

/**
 * @brief 设置矩阵为单位矩阵，并围绕位于(px, py)的旋转中心点进行旋转。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param degree 角度，单位为度。正数表示顺时针旋转，负数表示逆时针旋转。
 * @param px 旋转中心点的x轴坐标，单位为物理像素px。
 * @param py 旋转中心点的y轴坐标，单位为物理像素px。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixRotate(OH_Drawing_Matrix* matrix, float degree, float px, float py);

/**
 * @brief 设置矩阵为单位矩阵，并平移(dx, dy)。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param dx 水平方向平移距离，单位为物理像素px。正数表示往x轴正方向平移，负数表示往x轴负方向平移。
 * @param dy 垂直方向平移距离，单位为物理像素px。正数表示往y轴正方向平移，负数表示往y轴负方向平移。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixTranslate(OH_Drawing_Matrix* matrix, float dx, float dy);

/**
 * @brief 设置矩阵为单位矩阵，并围绕位于(px, py)的缩放中心点，以sx和sy进行缩放。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param sx 水平缩放因子，为负数时可看作是先关于x = px作镜像翻转后再进行缩放。
 * @param sy 垂直缩放因子，为负数时可看作是先关于y = py作镜像翻转后再进行缩放。
 * @param px 缩放中心点的x轴坐标，单位为物理像素px。
 * @param py 缩放中心点的y轴坐标，单位为物理像素px。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixScale(OH_Drawing_Matrix* matrix, float sx, float sy, float px, float py);

/**
 * @brief 将矩阵inverse设置为矩阵的逆矩阵，并返回结果。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix或inverse任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param inverse 指向逆矩阵对象{@link OH_Drawing_Matrix}的指针，开发者可调用{@link OH_Drawing_MatrixCreate}接口创建。
 * @return 函数返回true表示矩阵可逆，inverse被填充为逆矩阵；函数返回false表示矩阵不可逆，inverse不被改变。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_MatrixInvert(OH_Drawing_Matrix* matrix, OH_Drawing_Matrix* inverse);

/**
 * @brief 通过设置源点以及目标点，生成对应的变换矩阵。
 * <br>源点以及目标点的个数要大于等于0，小于等于4。本接口会产生错误码，
 * 可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * <br>count小于0或者大于4时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param src 源点数组，为NULL时count应当为0。
 * @param dst 目标点数组，个数要与源点相等，为NULL时count应当为0。
 * @param count 源点数组以及目标点数组的个数，取值范围为[0, 4]，为0时将矩阵对象设为单位矩阵。
 * @return 函数返回是否可以生成对应矩阵用来完成变换。true表示矩阵生成成功，false表示无法生成对应矩阵。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_MatrixSetPolyToPoly(OH_Drawing_Matrix* matrix, const OH_Drawing_Point2D* src,
    const OH_Drawing_Point2D* dst, uint32_t count);

/**
 * @brief 通过矩阵变换将源点数组映射到目标点数组。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix、src或dst任意一个为NULL或者count小于等于0时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param src 源点数组，数组长度应大于等于count，否则可能导致越界访问。
 * @param dst 目标点数组，数组长度应大于等于count，否则可能导致越界访问。
 * @param count 源点数组以及目标点数组的个数，必须大于0。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixMapPoints(const OH_Drawing_Matrix* matrix, const OH_Drawing_Point2D* src,
    OH_Drawing_Point2D* dst, int count);

/**
 * @brief 将目标矩形设置为一个新的矩形，该矩形是能够包围源矩形的四个顶点通过矩阵变换映射后形成的新顶点的最小矩形。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix、src或dst任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param src 指向源矩形{@link OH_Drawing_Rect}的指针。
 * @param dst 指向目标矩形{@link OH_Drawing_Rect}的指针，用于存储映射后的结果。
 * @return 函数返回源矩形与映射后的目标矩形是否相等。true表示相等，false表示不相等。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_MatrixMapRect(const OH_Drawing_Matrix* matrix, const OH_Drawing_Rect* src, OH_Drawing_Rect* dst);

/**
 * @brief 判断两个矩阵是否相等。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix或other任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向用于判断的其中一个矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param other 指向用于判断的另一个矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @return 函数返回两个矩阵的比较结果，返回true表示两个矩阵相等，返回false表示两个矩阵不相等。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_MatrixIsEqual(OH_Drawing_Matrix* matrix, OH_Drawing_Matrix* other);

/**
 * @brief 判断矩阵是否是单位矩阵。单位矩阵为：`[1 0 0; 0 1 0; 0 0 1]`。
 * <br>如需判断两个矩阵是否相等，请使用{@link OH_Drawing_MatrixIsEqual}。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @return 函数返回true表示矩阵是单位矩阵，函数返回false表示矩阵不是单位矩阵。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_MatrixIsIdentity(OH_Drawing_Matrix* matrix);

/**
 * @brief 判断当前矩阵是否为仿射矩阵。仿射矩阵是一种包括平移、旋转或缩放等变换的矩阵。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param isAffine 表示当前矩阵是否为仿射矩阵。作为出参使用。true表示当前矩阵是仿射矩阵，false表示当前矩阵不是仿射矩阵。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示matrix或isAffine为NULL。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_MatrixIsAffine(const OH_Drawing_Matrix* matrix, bool* isAffine);

/**
 * @brief 将当前矩阵左乘一个以(px, py)为中心按(kx, ky)倾斜构造的矩阵。与{@link OH_Drawing_MatrixPreRotate}、
 * {@link OH_Drawing_MatrixPreScale}、
 * {@link OH_Drawing_MatrixPreTranslate}同属Pre系列方法。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param kx 表示x轴上的倾斜量。
 * @param ky 表示y轴上的倾斜量。
 * @param px 表示倾斜中心点的x轴坐标，单位为物理像素px。
 * @param py 表示倾斜中心点的y轴坐标，单位为物理像素px。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示matrix为NULL。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_MatrixPreSkew(OH_Drawing_Matrix* matrix, float kx, float ky, float px, float py);

/**
 * @brief 判断矩形经过当前矩阵映射后是否仍保持矩形形状。当矩阵是单位矩阵或仅包含平移、缩放、
 * 旋转90度倍数这类仿射变换时满足该条件。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param isRectStaysRect 表示经过该矩阵映射后的矩形的形状是否仍为矩形。作为出参使用。
 *     <br>true表示映射后的矩形形状是矩形，false表示映射后的矩形形状不是矩形。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示matrix或isRectStaysRect为NULL。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_MatrixRectStaysRect(const OH_Drawing_Matrix* matrix, bool* isRectStaysRect);

/**
 * @brief 设置矩阵，使其围绕旋转中心 (px, py) 以指定的正弦值和余弦值进行旋转。
 * 与{@link OH_Drawing_MatrixRotate}功能类似，
 * 区别在于OH_Drawing_MatrixRotate直接传入角度值，而本方法传入正弦值和余弦值。
 *
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param sinValue 表示旋转角度的正弦值。
 * @param cosValue 表示旋转角度的余弦值。
 * @param px 表示旋转中心的x轴坐标。
 * @param py 表示旋转中心的y轴坐标。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示matrix为NULL。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_MatrixSetSinCos(OH_Drawing_Matrix* matrix, float sinValue, float cosValue,
    float px, float py);

/**
 * @brief 用于销毁矩阵对象并回收该对象占用的内存。
 *
 * @param matrix 指向矩阵对象的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_MatrixDestroy(OH_Drawing_Matrix* matrix);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
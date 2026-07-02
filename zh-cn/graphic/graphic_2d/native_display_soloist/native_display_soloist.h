/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup NativeDisplaySoloist
 * @{
 *
 * @brief 主要是用于UI线程以外的线程中进行帧率控制的Native侧业务。
 *
 * @since 12
 * @version 1.0
 */

/**
 * @file native_display_soloist.h
 *
 * @brief 定义获取和使用NativeDisplaySoloist的相关函数。
 *
 * @kit ArkGraphics2D
 * @library libnative_display_soloist.so
 * @syscap SystemCapability.Graphic.Graphic2D.HyperGraphicManager
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_NATIVE_DISPLAY_SOLOIST_H_
#define C_INCLUDE_NATIVE_DISPLAY_SOLOIST_H_

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 提供OH_DisplaySoloist结构体声明。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_DisplaySoloist OH_DisplaySoloist;

/**
 * @brief OH_DisplaySoloist回调函数类型。
 *
 * @param timestamp 当前帧VSync时间戳。
 * @param targetTimestamp 预期的下一帧VSync时间戳。
 * @param data 用户自定义数据。
 * @since 12
 * @version 1.0
 */
typedef void (*OH_DisplaySoloist_FrameCallback)(long long timestamp, long long targetTimestamp, void* data);

/**
 * @brief 提供期望帧率范围结构体。
 *
 * @since 12
 * @version 1.0
 */
typedef struct {
    /**
     * 期望帧率范围最小值，取值范围为[0,120]。
     */
    int32_t min;
    /**
     * 期望帧率范围最大值，取值范围为[0,120]。
     */
    int32_t max;
    /**
     * 期望帧率，取值范围为[0,120]。
     */
    int32_t expected;
} DisplaySoloist_ExpectedRateRange;

/**
 * @brief 创建一个OH_DisplaySoloist实例，每次调用都会产生一个新的实例。
 *
 * @param useExclusiveThread 表示此OH_DisplaySoloist实例是否是独占线程。true表示独占一个线程，false表示共享线程。
 * @return 返回一个指向OH_DisplaySoloist实例的指针，如果返回空表示执行失败，可能的原因是内存不足。
 * @since 12
 * @version 1.0
 */
OH_DisplaySoloist* OH_DisplaySoloist_Create(bool useExclusiveThread);

/**
 * @brief 销毁OH_DisplaySoloist实例并回收对象占用的内存。
 *
 * @param displaySoloist 一个指向OH_DisplaySoloist实例的指针。
 * @return 返回值为0表示执行成功，-1表示执行失败。
 * @since 12
 * @version 1.0
 */
int32_t OH_DisplaySoloist_Destroy(OH_DisplaySoloist* displaySoloist);

/**
 * @brief 设置每帧回调函数，每次VSync信号到来时启动每帧回调。
 *
 * @param displaySoloist 一个指向OH_DisplaySoloist实例的指针。
 * @param callback 表示下一次VSync信号到来时执行的回调函数类型。
 * @param data 一个指向用户自定义数据结构的指针，类型是void。
 * @return 返回值为0表示执行成功，-1表示执行失败。
 * @since 12
 * @version 1.0
 */
int32_t OH_DisplaySoloist_Start(
    OH_DisplaySoloist* displaySoloist, OH_DisplaySoloist_FrameCallback callback, void* data);

/**
 * @brief 停止请求下一次VSync信号，并停止调用回调函数callback。
 *
 * @param displaySoloist 一个指向OH_DisplaySoloist实例的指针。
 * @return 返回值为0表示执行成功，-1表示执行失败。
 * @since 12
 * @version 1.0
 */
int32_t OH_DisplaySoloist_Stop(OH_DisplaySoloist* displaySoloist);

/**
 * @brief 设置VSync期望帧率范围。
 *
 * @param displaySoloist 一个指向OH_DisplaySoloist实例的指针。
 * @param range 一个指向期望帧率范围DisplaySoloist_ExpectedRateRange实例的指针。
 * @return 返回值为0表示执行成功，-1表示执行失败。
 * @since 12
 * @version 1.0
 */
int32_t OH_DisplaySoloist_SetExpectedFrameRateRange(
    OH_DisplaySoloist* displaySoloist, DisplaySoloist_ExpectedRateRange* range);

#ifdef __cplusplus
}
#endif

#endif
/** @} */
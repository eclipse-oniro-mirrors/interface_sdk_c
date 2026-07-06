/*
 * Copyright (c) 2022-2022 Huawei Device Co., Ltd.
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
 * @addtogroup NativeVsync
 * @{
 *
 * @brief 定义获取和使用NativeVsync的相关函数。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeVsync
 * @since 9
 * @version 1.0
 */

/**
 * @file native_vsync.h
 *
 * @brief 定义获取和使用NativeVsync的相关函数。
 *
 * @kit ArkGraphics2D
 * @library libnative_vsync.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeVsync
 * @since 9
 * @version 1.0
 */

#ifndef NDK_INCLUDE_NATIVE_VSYNC_H_
#define NDK_INCLUDE_NATIVE_VSYNC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct OH_NativeVSync;
typedef struct OH_NativeVSync OH_NativeVSync;
typedef void (*OH_NativeVSync_FrameCallback)(long long timestamp, void *data);

/**
 * @brief 期望帧率范围结构体。
 *
 * @since 20
 * @version 1.0
 */
typedef struct {
    /**动态回调帧率范围的最小帧率 */
    int32_t min;
    /**动态回调帧率范围的最大帧率 */
    int32_t max;
    /**动态回调帧率范围的期望帧率 */
    int32_t expected;
} OH_NativeVSync_ExpectedRateRange;

/**
 * @brief 创建一个OH_NativeVSync实例，每次调用都会产生一个新的实例。\n
 * 本接口需要与OH_NativeVSync_Destroy接口配合使用，否则会存在内存泄露。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeVsync
 * @param name 表示一个名字，与创建的OH_NativeVSync实例关联。
 * @param length name的长度（字符数）。
 * @return 返回一个指向OH_NativeVSync实例的指针。
 * @since 9
 * @version 1.0
 */
OH_NativeVSync* OH_NativeVSync_Create(const char* name, unsigned int length);

/**
 * @brief 销毁OH_NativeVSync实例。\n
 * 销毁后的OH_NativeVSync指针不能再继续使用，否则会有野指针问题，尤其需要注意多线程并发时对于OH_NativeVSync指针的管理。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeVsync
 * @param nativeVsync 一个指向OH_NativeVSync实例的指针。
 * @since 9
 * @version 1.0
 */
void OH_NativeVSync_Destroy(OH_NativeVSync* nativeVsync);

/**
 * @brief 创建一个和窗口绑定的OH_NativeVSync实例，每次调用都会产生一个新的实例。\n
 * 使用本接口创建出来的OH_NativeVSync实例的实际vsync周期与系统vsync周期不完全一致，系统会根据窗口的状态对实际vsync周期进行调整。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeVsync
 * @param windowID 表示窗口ID，窗口子进程索引标识符。
 * @param name 表示一个名称，与创建的OH_NativeVSync实例关联。
 * @param length name的长度（字符数）。
 * @return 返回一个指向OH_NativeVSync实例的指针。
 * @since 14
 * @version 1.0
 */
OH_NativeVSync* OH_NativeVSync_Create_ForAssociatedWindow(uint64_t windowID, const char* name, unsigned int length);
/**
 * @brief 请求下一次vsync信号，当信号到来时，调用回调函数callback。\n
 * 如果在同一帧内中多次调用此接口，则只会触发最后一个回调。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeVsync
 * @param nativeVsync 一个指向OH_NativeVSync实例的指针。
 * @param callback 一个OH_NativeVSync_FrameCallback类型的函数指针，当下一次vsync信号到来时会被调用。
 * @param data 一个指向用户自定义数据结构的指针，类型是void。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - 参数nativeVsync或callback为空。\n
 *     NATIVE_ERROR_BINDER_ERROR 50401000 - ipc发送失败。
 * @since 9
 * @version 1.0
 */
int OH_NativeVSync_RequestFrame(OH_NativeVSync* nativeVsync, OH_NativeVSync_FrameCallback callback, void* data);

/**
 * @brief 请求下一次vsync信号，当信号到来时，调用回调函数callback。\n
 * 如果在同一帧内中多次调用此接口，每一次传入的callback都会被执行。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeVsync
 * @param nativeVsync 一个指向OH_NativeVSync实例的指针。
 * @param callback 一个OH_NativeVSync_FrameCallback类型的函数指针，当下一次vsync信号到来时会被调用。
 * @param data 一个指向用户自定义数据结构的指针，类型是void。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - 参数nativeVsync或callback为空。\n
 *     NATIVE_ERROR_BINDER_ERROR 50401000 - ipc发送失败。
 * @since 12
 * @version 1.0
 */
int OH_NativeVSync_RequestFrameWithMultiCallback(
    OH_NativeVSync* nativeVsync, OH_NativeVSync_FrameCallback callback, void* data);

/**
 * @brief 获取vsync周期。\n
 * vsync周期是在每次使用OH_NativeVSync_RequestFrame接口请求vsync信号后收到OH_NativeVSync_FrameCallback回调的时候才会更新。\n
 * 首次使用该接口获取vsync周期之前，需要先使用OH_NativeVSync_RequestFrame接口请求vsync信号，\n
 * 在收到OH_NativeVSync_FrameCallback回调之后，才可以通过该接口获取到vsync周期。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeVsync
 * @param nativeVsync 一个指向OH_NativeVSync实例的指针。
 * @param period 表示vsync周期，作为出参使用。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 10
 * @version 1.0
 */
int OH_NativeVSync_GetPeriod(OH_NativeVSync* nativeVsync, long long* period);

/**
 * @brief 启用DVSync以提高自绘制动画场景的流畅性。\n
 * DVSync是Decoupled VSync的缩写，它是一种与硬件VSync解耦的帧时序管理策略。\n
 * DVSync通过提前发送带有未来时间戳的VSync信号驱动后续动画帧的提前绘制，这些帧会被帧缓冲队列缓存；DVSync通过缓存的帧减少未来可能发生的丢帧，进而提高动画场景的流畅性。\n
 * 因为DVSync需要占用空闲的自绘制帧缓冲用于缓存提前绘制的动画帧，用户需要确保至少有一个空闲的帧缓冲区，否则不建议启用此功能。\n
 * 启用DVSync后，用户需要正确响应提前发送的VSync信号，并在前一个VSync对应的动画帧完成后再请求下一个VSync，且自绘制帧需要携带与VSync一致的时间戳。\n
 * 在动画结束之后，用户需要关闭DVSync。\n
 * 在不支持DVSync的平台或者如果有另一个应用程序已经启用了DVSync，则当前的启用操作将不会生效，应用程序仍将收到正常的VSync信号。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeVsync
 * @param nativeVsync 一个指向OH_NativeVSync实例的指针。
 * @param enable 表示打开或者关闭DVSync，true表示打开，false表示关闭。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - 参数nativeVsync为空。\n
 *     NATIVE_ERROR_BINDER_ERROR 50401000 - ipc发送失败。
 * @since 14
 * @version 1.0
 */
int OH_NativeVSync_DVSyncSwitch(OH_NativeVSync* nativeVsync, bool enable);

/**
 * @brief 设置VSync期望帧率及其范围。实际帧率可能因系统功耗、性能和硬件规格等限制而与设置的期望值不一致。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeVsync
 * @param nativeVsync 指向OH_NativeVSync实例的指针。
 * @param range 指向OH_NativeVSync_ExpectedRateRange实例的指针。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - 参数nativeVsync为空，或者range为空或无效。
 * @since 20
 * @version 1.0
 */
int OH_NativeVSync_SetExpectedFrameRateRange(OH_NativeVSync* nativeVsync, OH_NativeVSync_ExpectedRateRange* range);
#ifdef __cplusplus
}
#endif

/** @} */
#endif
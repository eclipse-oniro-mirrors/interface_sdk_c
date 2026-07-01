/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
 * @addtogroup NativeWindow
 * @{
 *
 * @brief 定义获取和使用NativeWindow的相关函数。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @since 8
 * @version 1.0
 */

/**
 * @file external_window.h
 *
 * @brief 定义获取和使用NativeWindow的相关函数。
 *
 * @kit ArkGraphics2D
 * @library libnative_window.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @since 8
 * @version 1.0
 */

#ifndef NDK_INCLUDE_EXTERNAL_NATIVE_WINDOW_H_
#define NDK_INCLUDE_EXTERNAL_NATIVE_WINDOW_H_

#include <stdint.h>
#include "buffer_handle.h"
#include "../native_buffer/buffer_common.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct OH_NativeBuffer OH_NativeBuffer;

/**
 * @brief 提供OHIPCParcel结构体声明，用于进程间通信。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OHIPCParcel OHIPCParcel;

/**
 * @brief 提供对OHNativeWindow的访问功能。
 * @since 8
 */
struct NativeWindow;

/**
 * @brief 提供对OHNativeWindowBuffer的访问功能。
 * @since 8
 */
struct NativeWindowBuffer;

/**
 * @brief 定义结构体NativeWindow的新类型名OHNativeWindow。
 * @since 8
 */
typedef struct NativeWindow OHNativeWindow;

/**
 * @brief 定义结构体NativeWindowBuffer的新类型名OHNativeWindowBuffer。
 * @since 8
 */
typedef struct NativeWindowBuffer OHNativeWindowBuffer;

/**
 * @brief 表示本地窗口OHNativeWindow需要更新内容的矩形区域（脏区）。
 * @since 8
 */
typedef struct Region {
    /** 如果rects是空指针nullptr，默认Buffer大小为脏区 */
    struct Rect {
        int32_t x;
        int32_t y;
        uint32_t w;
        uint32_t h;
    } *rects;
    /** 如果rectNumber是0，默认Buffer大小为脏区 */
    int32_t rectNumber;
}Region;


/**
 * @brief OH_NativeWindow_NativeWindowHandleOpt函数中的操作码。
 * @since 8
 */
typedef enum NativeWindowOperation {
    /**
     * 设置本地窗口缓冲区几何图形，函数中的可变参数是
     * [输入] int32_t width, [输入] int32_t height
     */
    SET_BUFFER_GEOMETRY,
    /**
     * 获取本地窗口缓冲区几何图形，函数中的可变参数是
     * [输出] int32_t *height, [输出] int32_t *width
     */
    GET_BUFFER_GEOMETRY,
    /**
     * 获取本地窗口缓冲区格式，函数中的可变参数是
     * [输出] int32_t *format，取值具体可见OH_NativeBuffer_Format枚举值。
     */
    GET_FORMAT,
    /**
     * 设置本地窗口缓冲区格式，函数中的可变参数是
     * [输入] int32_t format，取值具体可见OH_NativeBuffer_Format枚举值。
     */
    SET_FORMAT,
    /**
     * get native window buffer usage,
     * variable parameter in function is
     * [out] uint64_t *usage, the enumeration value refers to {@link OH_NativeBuffer_Usage}.
     */
    GET_USAGE,
    /**
     * 设置本地窗口缓冲区读写方式，函数中的可变参数是
     * [输入] uint64_t usage，取值具体可见OH_NativeBuffer_Usage枚举值。
     */
    SET_USAGE,
    /**
     * 设置本地窗口缓冲区步幅，函数中的可变参数是
     * [输入] int32_t stride。
     * @deprecated since 16
     */
    SET_STRIDE,
    /**
     * 获取本地窗口缓冲区步幅，函数中的可变参数是
     * [输出] int32_t *stride。
     * @deprecated since 16
     * @useinstead 使用OH_NativeWindow_GetBufferHandleFromNative获取BufferHandle，从中获取stride值。
     */
    GET_STRIDE,
    /**
     * 设置本地窗口缓冲区交换间隔，函数中的可变参数是
     * [输入] int32_t interval。
     */
    SET_SWAP_INTERVAL,
    /**
     * 获取本地窗口缓冲区交换间隔，函数中的可变参数是
     * [输出] int32_t *interval。
     */
    GET_SWAP_INTERVAL,
    /**
     * 设置请求本地窗口请求缓冲区的超时等待时间，未手动设置时默认值为3000毫秒，
     * 函数中的可变参数是
     * [输入] int32_t timeout, 单位为毫秒。
     */
    SET_TIMEOUT,
    /**
     * 获取请求本地窗口请求缓冲区的超时等待时间，未手动设置时默认值为3000毫秒，
     * 函数中的可变参数是
     * [输出] int32_t *timeout, 单位为毫秒。
     */
    GET_TIMEOUT,
    /**
     * 设置本地窗口缓冲区色彩空间，函数中的可变参数是
     * [输入] int32_t colorGamut，取值具体可见OH_NativeBuffer_ColorGamut枚举值。
     */
    SET_COLOR_GAMUT,
    /**
     * 获取本地窗口缓冲区色彩空间，函数中的可变参数是
     * [输出] int32_t *colorGamut，取值具体可见OH_NativeBuffer_ColorGamut枚举值。
     */
    GET_COLOR_GAMUT,
    /**
     * 设置本地窗口缓冲区变换，函数中的可变参数是
     * [输入] int32_t transform，取值具体可见OH_NativeBuffer_TransformType枚举值。
     */
    SET_TRANSFORM,
    /**
     * 获取本地窗口缓冲区变换，函数中的可变参数是
     * [输出] int32_t *transform，取值具体可见OH_NativeBuffer_TransformType枚举值。
     */
    GET_TRANSFORM,
    /**
     * 设置本地窗口缓冲区UI时间戳，函数中的可变参数是
     * [输入] uint64_t uiTimestamp。
     */
    SET_UI_TIMESTAMP,
    /**
     * 获取内存队列大小，函数中的可变参数是
     * [输出] int32_t *size。
     * @since 12
     */
    GET_BUFFERQUEUE_SIZE,
    /**
     * 设置本地窗口内容来源，函数中的可变参数是
     * [输入] int32_t sourceType，取值具体可见OHSurfaceSource枚举值。
     * @since 12
     */
    SET_SOURCE_TYPE,
    /**
     * 获取本地窗口内容来源，函数中的可变参数是
     * [输出] int32_t *sourceType，取值具体可见OHSurfaceSource枚举值。
     * @since 12
     */
    GET_SOURCE_TYPE,
    /**
     * 设置本地窗口应用框架名称，函数中的可变参数是
     * [输入] char* frameworkType，最大支持64字节。
     * @since 12
     */
    SET_APP_FRAMEWORK_TYPE,
    /**
     * 获取本地窗口应用框架名称，函数中的可变参数是
     * [输出] char** frameworkType。
     * @since 12
     */
    GET_APP_FRAMEWORK_TYPE,
    /**
     * 设置HDR白点亮度，函数中的可变参数是
     * [输入] float brightness，取值范围为0.0f到1.0f。
     * @since 12
     */
    SET_HDR_WHITE_POINT_BRIGHTNESS,
    /**
     * 设置SDR白点亮度，函数中的可变参数是
     * [输入] float brightness，取值范围为0.0f到1.0f。
     * @since 12
     */
    SET_SDR_WHITE_POINT_BRIGHTNESS,
    /**
     * 设置本地窗口缓冲区期望上屏时间的时间戳。\n
     * 该时间戳应由std::chrono::steady_clock标准库时钟生成，单位为纳秒。\n
     * 当且仅当RenderService为本地窗口的消费者时，该时间戳生效。\n
     * 生产者下一次放入队列的buffer，达到该期望上屏时间后，才会被RenderService消费并上屏。\n
     * 如果buffer队列中存在多个生产者放入的buffer都设置了desiredPresentTimestamp并已达到期望上屏时间，则较早入队的buffer将被消费者丢弃回队列。\n
     * 如果期望上屏时间大于消费者提供的时间1秒以上，则该期望上屏时间戳将被忽略。\n
     * 本操作执行后需要配合调用OH_NativeWindow_NativeWindowFlushBuffer生效。\n
     * 函数中的可变参数是
     * [输入] int64_t desiredPresentTimestamp。
     * @since 13
     */
    SET_DESIRED_PRESENT_TIMESTAMP = 24,
} NativeWindowOperation;

/**
 * @brief Indicates Scaling Mode.
 * @since 9
 * @deprecated since 10
 * @useinstead OHScalingModeV2
 */
typedef enum {
    /**
     * the window content is not updated until a buffer of
     * the window size is received
     */
    OH_SCALING_MODE_FREEZE = 0,
    /**
     * the buffer is scaled in two dimensions to match the window size
     */
    OH_SCALING_MODE_SCALE_TO_WINDOW,
    /**
     * the buffer is uniformly scaled so that the smaller size of
     * the buffer matches the window size
     */
    OH_SCALING_MODE_SCALE_CROP,
    /**
     * the window is clipped to the size of the buffer's clipping rectangle
     * pixels outside the clipping rectangle are considered fully transparent.
     */
    OH_SCALING_MODE_NO_SCALE_CROP,
} OHScalingMode;

/**
 * @brief Indicates Scaling Mode.
 * @since 12
 */
typedef enum {
    /**
     * the window content is not updated until a buffer of
     * the window size is received
     */
    OH_SCALING_MODE_FREEZE_V2 = 0,
    /**
     * the buffer is scaled in two dimensions to match the window size
     */
    OH_SCALING_MODE_SCALE_TO_WINDOW_V2,
    /**
     * the buffer is uniformly scaled so that the smaller size of
     * the buffer matches the window size
     */
    OH_SCALING_MODE_SCALE_CROP_V2,
    /**
     * the window is clipped to the size of the buffer's clipping rectangle
     * pixels outside the clipping rectangle are considered fully transparent.
     */
    OH_SCALING_MODE_NO_SCALE_CROP_V2,
    /**
     * Adapt to the buffer and scale proportionally to the buffer size. Prioritize displaying all buffer content.
     * If the size is not the same as the window size, fill the unfilled area of the window with a background color.
     */
    OH_SCALING_MODE_SCALE_FIT_V2,
} OHScalingModeV2;

/**
 * @brief Enumerates the HDR metadata keys.
 * @since 9
 * @deprecated since 10
 */
typedef enum {
    OH_METAKEY_RED_PRIMARY_X = 0,
    OH_METAKEY_RED_PRIMARY_Y = 1,
    OH_METAKEY_GREEN_PRIMARY_X = 2,
    OH_METAKEY_GREEN_PRIMARY_Y = 3,
    OH_METAKEY_BLUE_PRIMARY_X = 4,
    OH_METAKEY_BLUE_PRIMARY_Y = 5,
    OH_METAKEY_WHITE_PRIMARY_X = 6,
    OH_METAKEY_WHITE_PRIMARY_Y = 7,
    OH_METAKEY_MAX_LUMINANCE = 8,
    OH_METAKEY_MIN_LUMINANCE = 9,
    OH_METAKEY_MAX_CONTENT_LIGHT_LEVEL = 10,
    OH_METAKEY_MAX_FRAME_AVERAGE_LIGHT_LEVEL = 11,
    OH_METAKEY_HDR10_PLUS = 12,
    OH_METAKEY_HDR_VIVID = 13,
} OHHDRMetadataKey;

/**
 * @brief Defines the HDR metadata.
 * @since 9
 * @deprecated since 10
 */
typedef struct {
    OHHDRMetadataKey key;
    float value;
} OHHDRMetaData;

/**
 * @brief Defines the ExtData Handle
 * @since 9
 * @deprecated since 10
 */
typedef struct OHExtDataHandle {
    /**< Handle fd, -1 if not supported */
    int32_t fd;
    /**< the number of reserved integer value */
    uint32_t reserveInts;
    /**< the reserved data */
    int32_t reserve[0];
} OHExtDataHandle;

/**
 * @brief Indicates the source type of surface.
 * @since 12
 */
typedef enum {
    /*
     * the default source type of surface.
     */
    OH_SURFACE_SOURCE_DEFAULT = 0,
    /*
     * the surface is created by ui.
     */
    OH_SURFACE_SOURCE_UI,
    /*
     * the surface is created by game.
     */
    OH_SURFACE_SOURCE_GAME,
    /*
     * the surface is created by camera.
     */
    OH_SURFACE_SOURCE_CAMERA,
    /*
     * the surface is created by video.
     */
    OH_SURFACE_SOURCE_VIDEO,
} OHSurfaceSource;

/**
 * @brief 创建OHNativeWindow实例，每次调用都会产生一个新的OHNativeWindow实例。\n
 * 说明：此接口不可用，可通过OH_NativeImage_AcquireNativeWindow创建，或通过XComponent创建。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param pSurface 一个指向生产者ProduceSurface的指针，类型为sptr<OHOS::Surface>。
 * @return 返回一个指针，指向OHNativeWindow的结构体实例。
 * @since 8
 * @version 1.0
 * @deprecated since 12
 */
OHNativeWindow* OH_NativeWindow_CreateNativeWindow(void* pSurface);

/**
 * @brief 将OHNativeWindow对象的引用计数减1，当引用计数为0的时候，该OHNativeWindow对象会被析构掉。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @since 8
 * @version 1.0
 */
void OH_NativeWindow_DestroyNativeWindow(OHNativeWindow* window);

/**
 * @brief 创建OHNativeWindowBuffer实例，每次调用都会产生一个新的OHNativeWindowBuffer实例。\n
 * 说明：此接口不可用，使用OH_NativeWindow_CreateNativeWindowBufferFromNativeBuffer替代。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param pSurfaceBuffer 一个指向生产者buffer的指针，类型为sptr<OHOS::SurfaceBuffer>。
 * @return 返回一个指针，指向OHNativeWindowBuffer的结构体实例。
 * @since 8
 * @version 1.0
 * @deprecated since 12
 * @useinstead OH_NativeWindow_CreateNativeWindowBufferFromNativeBuffer
 */
OHNativeWindowBuffer* OH_NativeWindow_CreateNativeWindowBufferFromSurfaceBuffer(void* pSurfaceBuffer);

/**
 * @brief 创建OHNativeWindowBuffer实例，每次调用都会产生一个新的OHNativeWindowBuffer实例。\n
 * 本接口需要与OH_NativeWindow_DestroyNativeWindowBuffer接口配合使用，否则会存在内存泄露。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param nativeBuffer 一个指向OH_NativeBuffer的指针。
 * @return 返回一个指针，指向OHNativeWindowBuffer的结构体实例。
 * @since 11
 * @version 1.0
 */
OHNativeWindowBuffer* OH_NativeWindow_CreateNativeWindowBufferFromNativeBuffer(OH_NativeBuffer* nativeBuffer);

/**
 * @brief 将OHNativeWindowBuffer对象的引用计数减1，当引用计数为0的时候，该OHNativeWindowBuffer对象会被析构掉。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param buffer 一个OHNativeWindowBuffer的结构体实例的指针。
 * @since 8
 * @version 1.0
 */
void OH_NativeWindow_DestroyNativeWindowBuffer(OHNativeWindowBuffer* buffer);

/**
 * @brief 通过OHNativeWindow对象申请一块OHNativeWindowBuffer，用以内容生产。\n
 * 在调用本接口前，需要通过SET_BUFFER_GEOMETRY对OHNativeWindow设置宽高。\n
 * 本接口需要与OH_NativeWindow_NativeWindowFlushBuffer接口配合使用，否则内存会耗尽。\n
 * 当fenceFd使用完，用户需要将其close。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @param buffer 一个指向OHNativeWindowBuffer指针的指针（二级指针）。\n
 * 通过OH_NativeWindow_GetBufferHandleFromNative可获取BufferHandle结构体，访问缓冲区内存。
 * @param fenceFd 一个文件描述符句柄，用于GPU/CPU同步：不同取值及含义如下：<br>- 返回≥0：缓冲区正被GPU使用，需要等待文件描述符fenceFd就绪。<br>- 返回-1：缓冲区可直接使用。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeWindow_NativeWindowRequestBuffer(OHNativeWindow *window,
    OHNativeWindowBuffer **buffer, int *fenceFd);

/**
 * @brief 通过OHNativeWindow将生产好内容的OHNativeWindowBuffer放回到Buffer队列中，用以内容消费。\n
 * 系统会将fenceFd关闭，无需用户close。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @param buffer 一个OHNativeWindowBuffer的结构体实例的指针。
 * @param fenceFd 一个文件描述符句柄，用以同步时序。不同取值及含义如下：<br>- -1：CPU渲染完成，无需同步时序。<br>- ≥0：从GPU同步对象转换\n
 * （如EGL的eglDupNativeFenceFDANDROID），对端需要通过此fenceFd同步时序。
 * @param region 一个Region结构体，表示一块脏区域，该区域有内容更新。<br>Region.rectNumber限制最大数量为1000，\n
 * 当rectNumber≤0或者rectNumber>1000时，使用整个buffer作为脏区。<br>Region.rect以buffer左下角为坐标原点。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeWindow_NativeWindowFlushBuffer(OHNativeWindow *window, OHNativeWindowBuffer *buffer,
    int fenceFd, Region region);

/**
 * @brief 从OHNativeWindow获取上次送回到buffer队列中的OHNativeWindowBuffer。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @param buffer 一个OHNativeWindowBuffer结构体指针的指针。
 * @param fenceFd 一个文件描述符的指针。
 * @param matrix 表示检索到的4*4变换矩阵。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 11
 * @version 1.0
 * @deprecated since 12
 * @useinstead OH_NativeWindow_GetLastFlushedBufferV2
 */
int32_t OH_NativeWindow_GetLastFlushedBuffer(OHNativeWindow *window, OHNativeWindowBuffer **buffer,
    int *fenceFd, float matrix[16]);

/**
  * @brief 通过OHNativeWindow将之前申请出来的OHNativeWindowBuffer返还到Buffer队列中，供下次再申请。\n
  * 本接口为非线程安全类型接口。\n
  *
  * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
  * @param window 一个OHNativeWindow的结构体实例的指针。
  * @param buffer 一个OHNativeWindowBuffer的结构体实例的指针。
  * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
  * @since 8
  * @version 1.0
  */
int32_t OH_NativeWindow_NativeWindowAbortBuffer(OHNativeWindow *window, OHNativeWindowBuffer *buffer);

/**
 * @brief 设置/获取OHNativeWindow的属性，包括设置/获取宽高、内容格式等。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @param code 表示操作码，详见NativeWindowOperation。
 * @param ... 可变参数，必须与操作码对应的数据类型保持一致，且入参数量严格按照操作码提示传入，否则会存在未定义行为。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeWindow_NativeWindowHandleOpt(OHNativeWindow *window, int code, ...);

/**
 * @brief 通过OHNativeWindowBuffer获取该buffer的BufferHandle指针。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param buffer 一个OHNativeWindowBuffer的结构体实例的指针。
 * @return 返回一个指针，指向BufferHandle的结构体实例。
 * @since 8
 * @version 1.0
 */
BufferHandle *OH_NativeWindow_GetBufferHandleFromNative(OHNativeWindowBuffer *buffer);

/**
 * @brief 增加一个NativeObject的引用计数。\n
 * 本接口需要与OH_NativeWindow_NativeObjectUnreference接口配合使用，否则会存在内存泄露。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param obj 一个OHNativeWindow或者OHNativeWindowBuffer的结构体实例的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeWindow_NativeObjectReference(void *obj);

/**
 * @brief 减少一个NativeObject的引用计数，当引用计数减少为0时，该NativeObject将被析构掉。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param obj 一个OHNativeWindow或者OHNativeWindowBuffer的结构体实例的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeWindow_NativeObjectUnreference(void *obj);

/**
 * @brief 获取NativeObject的MagicId。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param obj 一个OHNativeWindow或者OHNativeWindowBuffer的结构体实例的指针。
 * @return 返回值为魔鬼数字，每个NativeObject唯一。
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeWindow_GetNativeObjectMagic(void *obj);

/**
 * @brief 设置OHNativeWindow的ScalingMode。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @param sequence 生产缓冲区的序列。
 * @param scalingMode 枚举值OHScalingMode。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 9
 * @version 1.0
 * @deprecated since 10
 * @useinstead OH_NativeWindow_NativeWindowSetScalingModeV2
 */
int32_t OH_NativeWindow_NativeWindowSetScalingMode(OHNativeWindow *window, uint32_t sequence,
                                                   OHScalingMode scalingMode);

/**
 * @brief 设置OHNativeWindow的元数据。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @param sequence 生产缓冲区的序列。
 * @param size OHHDRMetaData数组的大小，最大支持为3000，超出会返回NATIVE_ERROR_INVALID_ARGUMENTS。
 * @param metaData 指向OHHDRMetaData数组的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 9
 * @version 1.0
 * @deprecated since 10
 */
int32_t OH_NativeWindow_NativeWindowSetMetaData(OHNativeWindow *window, uint32_t sequence, int32_t size,
                                                const OHHDRMetaData *metaData);

/**
 * @brief 设置OHNativeWindow的元数据集。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @param sequence 生产缓冲区的序列。
 * @param key 枚举值OHHDRMetadataKey。
 * @param size uint8_t向量的大小，最大支持为3000，超出会返回NATIVE_ERROR_INVALID_ARGUMENTS。
 * @param metaData 指向uint8_t向量的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 9
 * @version 1.0
 * @deprecated since 10
 */
int32_t OH_NativeWindow_NativeWindowSetMetaDataSet(OHNativeWindow *window, uint32_t sequence, OHHDRMetadataKey key,
                                                   int32_t size, const uint8_t *metaData);

/**
 * @brief 设置OHNativeWindow的TunnelHandle。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @param handle 指向OHExtDataHandle的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 9
 * @version 1.0
 * @deprecated since 10
 */
int32_t OH_NativeWindow_NativeWindowSetTunnelHandle(OHNativeWindow *window, const OHExtDataHandle *handle);

/**
 * @brief 将OHNativeWindowBuffer添加进OHNativeWindow中。\n
 * 本接口需要与OH_NativeWindow_NativeWindowDetachBuffer接口配合使用，否则会存在内存管理混乱问题。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @param buffer 一个OHNativeWindowBuffer的结构体实例的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeWindow_NativeWindowAttachBuffer(OHNativeWindow *window, OHNativeWindowBuffer *buffer);

/**
 * @brief 将OHNativeWindowBuffer从OHNativeWindow中分离。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @param buffer 一个OHNativeWindowBuffer的结构体实例的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeWindow_NativeWindowDetachBuffer(OHNativeWindow *window, OHNativeWindowBuffer *buffer);

/**
 * @brief 通过OHNativeWindow获取对应的surfaceId。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @param surfaceId 一个surface对应ID的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeWindow_GetSurfaceId(OHNativeWindow *window, uint64_t *surfaceId);

/**
 * @brief 通过surfaceId创建对应的OHNativeWindow。\n
 * 本接口需要与OH_NativeWindow_DestroyNativeWindow接口配合使用，否则会存在内存泄露。\n
 * 如果存在并发释放OHNativeWindow的情况，需要通过OH_NativeWindow_NativeObjectReference和\n
 * OH_NativeWindow_NativeObjectUnreference对OHNativeWindow进行引用计数加一和减一。\n
 * 通过surfaceId获取的surface需要是在本进程中创建的，不能跨进程获取surface。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param surfaceId 一个surface对应的ID。
 * @param window 一个OHNativeWindow的结构体实例的二级指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeWindow_CreateNativeWindowFromSurfaceId(uint64_t surfaceId, OHNativeWindow **window);

/**
 * @brief 设置OHNativeWindow的渲染缩放模式。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @param scalingMode 一个OHScalingModeV2类型的枚举值。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeWindow_NativeWindowSetScalingModeV2(OHNativeWindow *window, OHScalingModeV2 scalingMode);

/**
 * @brief 启用单帧缓存机制，通过提前缓存一帧buffer并延迟显示，用于平滑帧率波动。\n
 * 启用后，系统会预留一帧buffer作为缓冲，该帧会延迟一个显示周期才上屏。当后续渲染出现超长帧或帧间不均匀时，可使用该缓存帧填补空白，减少画面卡顿。\n
 * 建议在预知即将出现渲染高峰前提前调用，以建立缓冲保护；缓存仅生效一次，被消费后自动失效，如需持续保护需重新调用本接口。\n
 * 适用于游戏、动画、复杂UI渲染等对帧率稳定性要求较高的场景，但会引入一帧显示延迟（比如，在60hz的刷新率下，会延迟16.6ms上屏显示），不建议在高交互实时场景中使用。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @since 12
 * @version 1.0
 */
void OH_NativeWindow_SetBufferHold(OHNativeWindow *window);

/**
 * @brief 将窗口对象写入IPC序列化对象中。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个指向OHNativeWindow的结构体实例的指针。
 * @param parcel 一个指向OHIPCParcel的结构体实例的指针。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - parcel为空或window为空。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeWindow_WriteToParcel(OHNativeWindow *window, OHIPCParcel *parcel);

/**
 * @brief 从IPC序列化对象中读取窗口对象。\n
 * 本接口将会创建一个OHNativeWindow，当窗口对象使用完，开发者需要与OH_NativeWindow_DestroyNativeWindow接口配合使用，否则会存在内存泄漏。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param parcel 一个指向OHIPCParcel的结构体实例的指针。
 * @param window 一个指向OHNativeWindow的结构体实例的二级指针。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - parcel为空或parcel不包含window。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeWindow_ReadFromParcel(OHIPCParcel *parcel, OHNativeWindow **window);

/**
 * @brief 从OHNativeWindow获取上次送回到buffer队列中的OHNativeWindowBuffer，与OH_NativeWindow_GetLastFlushedBuffer的差异在于matrix不同。\n
 * 本接口需要与OH_NativeWindow_NativeObjectUnreference接口配合使用，否则会存在内存泄露。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个OHNativeWindow的结构体实例的指针。
 * @param buffer 一个OHNativeWindowBuffer结构体指针的指针。
 * @param fenceFd 一个文件描述符的指针。
 * @param matrix 表示检索到的4*4变换矩阵。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - window为空或buffer为空或fenceFd为空。\n
 *     NATIVE_ERROR_BUFFER_STATE_INVALID 41207000 - buffer状态错误。
 * @since 12
 * @version 1.0
 */

int32_t OH_NativeWindow_GetLastFlushedBufferV2(OHNativeWindow *window, OHNativeWindowBuffer **buffer,
    int *fenceFd, float matrix[16]);
/**
 * @brief 为OHNativeWindow设置颜色空间属性。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个指向OHNativeWindow的结构体实例的指针。
 * @param colorSpace 为OHNativeWindow设置的颜色空间，其值从OH_NativeBuffer_ColorSpace获取。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - window为空。\n
 *     NATIVE_ERROR_BUFFER_STATE_INVALID 41207000 - colorSpace状态错误。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeWindow_SetColorSpace(OHNativeWindow *window, OH_NativeBuffer_ColorSpace colorSpace);

/**
 * @brief 获取OHNativeWindow颜色空间属性。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个指向OHNativeWindow的结构体实例的指针。
 * @param colorSpace OHNativeWindow的颜色空间，值从OH_NativeBuffer_ColorSpace获取。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - window为空。\n
 *     NATIVE_ERROR_BUFFER_STATE_INVALID 41207000 - colorSpace状态错误。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeWindow_GetColorSpace(OHNativeWindow *window, OH_NativeBuffer_ColorSpace *colorSpace);

/**
 * @brief 为OHNativeWindow设置元数据属性值。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个指向OHNativeWindow的结构体实例的指针。
 * @param metadataKey Window的元数据类型，其值从OH_NativeBuffer_MetadataKey获取。
 * @param size uint8_t向量的大小，其取值范围见OH_NativeBuffer_MetadataKey。
 * @param metadata 指向uint8_t向量的指针。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - window或metadata为空。\n
 *     NATIVE_ERROR_BUFFER_STATE_INVALID 41207000 - metadata状态错误。\n
 *     NATIVE_ERROR_UNSUPPORTED 50102000 - 不支持的metadata key。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeWindow_SetMetadataValue(OHNativeWindow *window, OH_NativeBuffer_MetadataKey metadataKey,
    int32_t size, uint8_t *metadata);

/**
 * @brief 获取OHNativeWindow元数据属性值。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个指向OHNativeWindow的结构体实例的指针。
 * @param metadataKey Window的元数据类型，其值从OH_NativeBuffer_MetadataKey获取。
 * @param size uint8_t向量的大小，其取值范围见OH_NativeBuffer_MetadataKey。
 * @param metadata 指向uint8_t向量的二级指针。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - window、metadata或size为空。\n
 *     NATIVE_ERROR_BUFFER_STATE_INVALID 41207000 - metadata状态错误。\n
 *     NATIVE_ERROR_UNSUPPORTED 50102000 - 不支持的metadata key。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeWindow_GetMetadataValue(OHNativeWindow *window, OH_NativeBuffer_MetadataKey metadataKey,
    int32_t *size, uint8_t **metadata);

/**
 * @brief 清理OHNativeWindow中的OHNativeWindowBuffer缓存。\n
 * 使用该接口清理缓存前，需确保已通过OH_NativeWindow_NativeWindowRequestBuffer接口成功申请OHNativeWindowBuffer。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个指向OHNativeWindow的结构体实例的指针。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - window为空。\n
 *     NATIVE_ERROR_CONSUMER_DISCONNECTED 41211000 - consumer断开连接。\n
 *     NATIVE_ERROR_BINDER_ERROR 50401000 - ipc发送失败。
 * @since 19
 * @version 1.0
 */
int32_t OH_NativeWindow_CleanCache(OHNativeWindow *window);

/**
 * @brief 通过OHNativeWindow对象提前申请多块OHNativeWindowBuffer，用以内容生产。\n
 * 在调用本接口前，需要通过OH_NativeWindow_NativeWindowHandleOpt对OHNativeWindow设置宽高。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个指向OHNativeWindow的结构体实例的指针。
 * @param allocBufferCnt 提前申请buffer的数量。当allocBufferCnt大于bufferQueueSize时，只能提前申请bufferQueueSize数量的buffer。\n
 * bufferQueueSize可以通过OH_NativeWindow_NativeWindowHandleOpt获取。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 22
 * @version 1.0
 */
int32_t OH_NativeWindow_PreAllocBuffers(OHNativeWindow *window, uint32_t allocBufferCnt);

/**
 * @brief 通过OHNativeWindow对象申请一块OHNativeWindowBuffer，用以内容生产，并对该OHNativeWindowBuffer加锁。\n
 * 本接口需要和OH_NativeWindow_UnlockAndFlushBuffer接口配合使用。\n
 * 本接口对OHNativeWindowBuffer加锁后，需要调OH_NativeWindow_UnlockAndFlushBuffer接口解锁后才能重新对OHNativeWindowBuffer加锁。\n
 * 若用本接口重复对OHNativeWindowBuffer加锁，会返回操作非法错误码。\n
 * 本接口支持通过CPU上的内存读写直接渲染图像。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个指向OHNativeWindow的结构体实例的指针。
 * @param region 一个Region结构体，表示一块脏区域，该区域有内容更新。<br>Region.rectNumber限制最大数量为1000，\n
 * 当rectNumber≤0或者rectNumber>1000时，使用整个buffer作为脏区。<br>Region.rect以buffer左下角为坐标原点。
 * @param buffer 一个指向OHNativeWindowBuffer的二级指针。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - window或buffer为空。\n
 *     NATIVE_ERROR_UNKNOWN 50002000 - window的surface成员为空。
 * @since 23
 * @version 1.0
 */
int32_t OH_NativeWindow_LockBuffer(OHNativeWindow* window, Region region, OHNativeWindowBuffer** buffer);

/**
 * @brief 通过OHNativeWindow将生产好内容的OHNativeWindowBuffer放回到Buffer队列中，用以内容消费，并对OHNativeWindowBuffer解锁。\n
 * 本接口需要和OH_NativeWindow_LockBuffer接口配合使用。\n
 * 若用本接口重复对OHNativeWindowBuffer解锁，会返回操作非法错误码。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @param window 一个指向OHNativeWindow的结构体实例的指针。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - window为空。\n
 *     NATIVE_ERROR_UNKNOWN 50002000 - window的surface成员为空。
 * @since 23
 * @version 1.0
 */
int32_t OH_NativeWindow_UnlockAndFlushBuffer(OHNativeWindow* window);
#ifdef __cplusplus
}
#endif

/** @} */
#endif
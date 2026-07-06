/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
 * @addtogroup OH_NativeBuffer
 * @{
 *
 * @brief 定义获取和使用NativeBuffer的相关函数。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 9
 * @version 1.0
 */

/**
 * @file native_buffer.h
 *
 * @brief 定义获取和使用NativeBuffer的相关函数。
 *
 * @kit ArkGraphics2D
 * @library libnative_buffer.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 9
 * @version 1.0
 */

#ifndef NDK_INCLUDE_NATIVE_BUFFER_H_
#define NDK_INCLUDE_NATIVE_BUFFER_H_

#include <stdint.h>
#include <native_window/external_window.h>
#include <native_buffer/buffer_common.h>

#ifdef __cplusplus
extern "C" {
#endif

struct OH_NativeBuffer;
typedef struct OH_NativeBuffer OH_NativeBuffer;

/**
 * @brief 提供OHIPCParcel结构体声明，用于进程间通信。
 *
 * @since 23
 * @version 1.0
 */
typedef struct OHIPCParcel OHIPCParcel;

/**
 * @brief OH_NativeBuffer的用途。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 10
 * @version 1.0
 */
typedef enum OH_NativeBuffer_Usage {
    NATIVEBUFFER_USAGE_CPU_READ = (1ULL << 0),        /// < CPU可读 */
    NATIVEBUFFER_USAGE_CPU_WRITE = (1ULL << 1),       /// < CPU可写 */
    NATIVEBUFFER_USAGE_MEM_DMA = (1ULL << 3),         /// < 直接内存访问缓冲区 */
    /**
     * 媒体内存区域缓存
     * @since 20
     */
    NATIVEBUFFER_USAGE_MEM_MMZ_CACHE = (1ULL << 5),
    /**
     * @since 12
     */
    NATIVEBUFFER_USAGE_HW_RENDER = (1ULL << 8),       /// < GPU可写 */
    /**
     * @since 12
     */
    NATIVEBUFFER_USAGE_HW_TEXTURE = (1ULL << 9),      /// < GPU可读 */
    /**
     * @since 12
     */
    NATIVEBUFFER_USAGE_CPU_READ_OFTEN = (1ULL << 16), /// < CPU可直接映射 */
    /**
     * @since 12
     */
    NATIVEBUFFER_USAGE_ALIGNMENT_512 = (1ULL << 18),  /// < 512字节对齐 */
} OH_NativeBuffer_Usage;

/**
 * @brief OH_NativeBuffer的色域。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 12
 * @version 1.0
 */
typedef enum OH_NativeBuffer_ColorGamut {
    NATIVEBUFFER_COLOR_GAMUT_NATIVE = 0,            /**< 默认色域格式 */
    NATIVEBUFFER_COLOR_GAMUT_STANDARD_BT601 = 1,    /**< Standard BT601色域格式 */
    NATIVEBUFFER_COLOR_GAMUT_STANDARD_BT709 = 2,    /**< Standard BT709色域格式 */
    NATIVEBUFFER_COLOR_GAMUT_DCI_P3 = 3,            /**< DCI P3色域格式 */
    NATIVEBUFFER_COLOR_GAMUT_SRGB = 4,              /**< SRGB色域格式 */
    NATIVEBUFFER_COLOR_GAMUT_ADOBE_RGB = 5,         /**< Adobe RGB色域格式 */
    NATIVEBUFFER_COLOR_GAMUT_DISPLAY_P3 = 6,        /**< Display P3色域格式 */
    NATIVEBUFFER_COLOR_GAMUT_BT2020 = 7,            /**< BT2020色域格式 */
    NATIVEBUFFER_COLOR_GAMUT_BT2100_PQ = 8,         /**< BT2100 PQ色域格式 */
    NATIVEBUFFER_COLOR_GAMUT_BT2100_HLG = 9,        /**< BT2100 HLG色域格式 */
    NATIVEBUFFER_COLOR_GAMUT_DISPLAY_BT2020 = 10,   /**< Display BT2020色域格式 */
} OH_NativeBuffer_ColorGamut;

/**
 * @brief OH_NativeBuffer的属性配置，用于申请新的OH_NativeBuffer实例或查询现有实例的相关属性。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 9
 * @version 1.0
 */
typedef struct {
    int32_t width;           ///< 宽度（像素）
    int32_t height;          ///< 高度（像素）
    int32_t format;          ///< PixelFormat之一
    int32_t usage;           ///< buffer usage的组合
    /**
     * @since 10
     */
    int32_t stride;          ///< stride stride in bytes
} OH_NativeBuffer_Config;

/**
 * @brief 单个图像平面格式信息。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 12
 * @version 1.0
 */
typedef struct {
    uint64_t offset;         ///< 平面字节偏移
    uint32_t rowStride;      ///< 图像一行第一个值到下一行第一个值的字节距离
    uint32_t columnStride;   ///< 图像一列第一个值到下一列第一个值的字节距离
} OH_NativeBuffer_Plane;

/**
 * @brief OH_NativeBuffer的图像平面格式信息。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @since 12
 * @version 1.0
 */
typedef struct {
    uint32_t planeCount;              ///< 不同平面的数量
    OH_NativeBuffer_Plane planes[4];  ///< 图像平面数组
} OH_NativeBuffer_Planes;

/**
 * @brief 通过OH_NativeBuffer_Config创建OH_NativeBuffer实例，每次调用都会产生一个新的OH_NativeBuffer实例。\n
 * 本接口需要与OH_NativeBuffer_Unreference接口配合使用，否则会存在内存泄露。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param config 一个指向OH_NativeBuffer_Config类型的指针。
 * @return 创建成功则返回一个指向OH_NativeBuffer结构体实例的指针，否则返回NULL。
 * @since 9
 * @version 1.0
 */
OH_NativeBuffer* OH_NativeBuffer_Alloc(const OH_NativeBuffer_Config* config);

/**
 * @brief 将OH_NativeBuffer对象的引用计数加1。\n
 * 本接口需要与OH_NativeBuffer_Unreference接口配合使用，否则会存在内存泄露。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer实例的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeBuffer_Reference(OH_NativeBuffer *buffer);

/**
 * @brief 将OH_NativeBuffer对象的引用计数减1，当引用计数为0的时候，该NativeBuffer对象会被析构掉。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer实例的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeBuffer_Unreference(OH_NativeBuffer *buffer);

/**
 * @brief 用于获取OH_NativeBuffer的属性。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer实例的指针。
 * @param config 一个指向OH_NativeBuffer_Config的指针，用于接收OH_NativeBuffer的属性。
 * @since 9
 * @version 1.0
 */
void OH_NativeBuffer_GetConfig(OH_NativeBuffer *buffer, OH_NativeBuffer_Config* config);

/**
 * @brief 将OH_NativeBuffer对应的ION内存映射到进程空间。\n
 * 本接口需要与OH_NativeBuffer_Unmap接口配合使用。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer实例的指针。
 * @param virAddr 一个二级指针，二级指针指向映射到当前进程的虚拟内存的地址。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 9
 * @version 1.0
 */

int32_t OH_NativeBuffer_Map(OH_NativeBuffer *buffer, void **virAddr);

/**
 * @brief 将OH_NativeBuffer对应的ION内存从进程空间移除。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer实例的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeBuffer_Unmap(OH_NativeBuffer *buffer);

/**
 * @brief 获取OH_NativeBuffer的序列号。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer实例的指针。
 * @return 返回对应OH_NativeBuffer的唯一序列号。
 * @since 9
 * @version 1.0
 */
uint32_t OH_NativeBuffer_GetSeqNum(OH_NativeBuffer *buffer);

/**
 * @brief 将OH_NativeBuffer对应的多通道ION内存映射到进程空间。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer实例的指针。
 * @param virAddr 一个二级指针，二级指针指向映射到当前进程的虚拟内存的地址。
 * @param outPlanes 一个指向所有图像平面格式信息的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeBuffer_MapPlanes(OH_NativeBuffer *buffer, void **virAddr, OH_NativeBuffer_Planes *outPlanes);

/**
 * @brief 将OHNativeWindowBuffer实例转换为OH_NativeBuffer实例。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param nativeWindowBuffer 一个指向OHNativeWindowBuffer实例的指针。
 * @param buffer 一个指向OH_NativeBuffer实例的二级指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeBuffer_FromNativeWindowBuffer(OHNativeWindowBuffer *nativeWindowBuffer, OH_NativeBuffer **buffer);

/**
 * @brief 为OH_NativeBuffer设置颜色空间属性。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer实例的指针。
 * @param colorSpace 为OH_NativeBuffer设置的颜色空间，其值从OH_NativeBuffer_ColorSpace获取。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 11
 * @version 1.0
 */
int32_t OH_NativeBuffer_SetColorSpace(OH_NativeBuffer *buffer, OH_NativeBuffer_ColorSpace colorSpace);

/**
 * @brief 获取OH_NativeBuffer颜色空间属性。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer实例的指针。
 * @param colorSpace 为OH_NativeBuffer设置的颜色空间，其值从OH_NativeBuffer_ColorSpace获取。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeBuffer_GetColorSpace(OH_NativeBuffer *buffer, OH_NativeBuffer_ColorSpace *colorSpace);

/**
 * @brief 为OH_NativeBuffer设置元数据属性值。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer实例的指针。
 * @param metadataKey OH_NativeBuffer的元数据类型，其值从OH_NativeBuffer_MetadataKey获取。
 * @param size uint8_t向量的大小，其取值范围参考OH_NativeBuffer_MetadataKey。
 * @param metadata 指向uint8_t向量的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeBuffer_SetMetadataValue(OH_NativeBuffer *buffer, OH_NativeBuffer_MetadataKey metadataKey,
    int32_t size, uint8_t *metadata);

/**
 * @brief 获取OH_NativeBuffer元数据属性值。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer实例的指针。
 * @param metadataKey OH_NativeBuffer的元数据类型，其值从OH_NativeBuffer_MetadataKey获取。
 * @param size uint8_t向量的大小，其取值范围参考OH_NativeBuffer_MetadataKey。
 * @param metadata 指向uint8_t向量的二级指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeBuffer_GetMetadataValue(OH_NativeBuffer *buffer, OH_NativeBuffer_MetadataKey metadataKey,
    int32_t *size, uint8_t **metadata);

/**
 * @brief 将OH_NativeBuffer对应的ION内存映射到进程空间，永久阻塞传入的fenceFd。\n
 * 如果接口返回OK，系统会将fenceFd关闭，无需用户close，否则，用户需要自行关闭fenceFd。\n
 * 本接口需要与OH_NativeBuffer_Unmap接口配合使用。\n
 * 本接口为非线程安全类型接口。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer实例的指针。
 * @param fenceFd 指向文件描述符句柄，用于并发同步控制。
 * @param virAddr 一个二级指针，二级指针指向映射到当前进程的虚拟内存的地址。
 * @return 执行成功时返回NATIVE_ERROR_OK。\n
 * buffer、virAddr是空指针或fenceFd小于0时返回NATIVE_ERROR_INVALID_ARGUMENTS。\n
 * 映射失败时返回NATIVE_ERROR_UNKNOWN。\n
 * 其他返回值可参考OHNativeErrorCode。
 * @since 23
 * @version 1.0
 */
int32_t OH_NativeBuffer_MapWaitFence(OH_NativeBuffer *buffer, int32_t fenceFd, void **virAddr);

/**
 * @brief 将OH_NativeBuffer对象写入IPC序列化对象中。\n
 * 本接口为非线程安全类型接口。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer实例的指针。
 * @param parcel 一个指向OHIPCParcel结构体实例的指针，作为出参使用。
 * @return 执行成功时返回NATIVE_ERROR_OK。\n
 * buffer或parcel为空指针时返回NATIVE_ERROR_INVALID_ARGUMENTS。\n
 * IPC发送失败返回NATIVE_ERROR_BINDER_ERROR。\n
 * 其他返回值可参考OHNativeErrorCode。
 * @since 23
 * @version 1.0
 */
int32_t OH_NativeBuffer_WriteToParcel(OH_NativeBuffer* buffer, OHIPCParcel* parcel);

/**
 * @brief 从IPC序列化对象中读取OH_NativeBuffer对象。\n
 * 本接口将会创建一个OH_NativeBuffer，当OH_NativeBuffer对象使用完，开发者需要与OH_NativeBuffer_Unreference接口配合使用，否则会存在内存泄漏。\n
 * 本接口为非线程安全类型接口。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param parcel 一个指向OHIPCParcel的结构体实例的指针。
 * @param buffer 一个指向OH_NativeBuffer结构体实例的二级指针，作为出参使用。
 * @return 执行成功时返回NATIVE_ERROR_OK。\n
 * parcel或buffer为空指针时返回NATIVE_ERROR_INVALID_ARGUMENTS。\n
 * parcel反序列化失败返回NATIVE_ERROR_UNKNOWN。\n
 * 其他返回值可参考OHNativeErrorCode。
 * @since 23
 * @version 1.0
 */
int32_t OH_NativeBuffer_ReadFromParcel(OHIPCParcel* parcel, OH_NativeBuffer** buffer);

/**
 * @brief 检查系统是否支持传入的OH_NativeBuffer_Config配置信息。\n
 * 本接口为非线程安全类型接口。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param config OH_NativeBuffer_Config结构体实例。
 * @param isSupported 为true代表系统支持传入的OH_NativeBuffer_Config配置信息，为false表示系统不支持传入的OH_NativeBuffer_Config配置信息，作为出参使用。
 * @return 执行成功时返回NATIVE_ERROR_OK。\n
 * isSupported为空指针时返回NATIVE_ERROR_INVALID_ARGUMENTS。\n
 * 其他返回值可参考OHNativeErrorCode。
 * @since 23
 * @version 1.0
 */
int32_t OH_NativeBuffer_IsSupported(OH_NativeBuffer_Config config, bool* isSupported);

/**
 * @brief 将OH_NativeBuffer对应的多通道ION内存映射到进程空间，并获取OH_NativeBuffer对应的OH_NativeBuffer_Config。\n
 * 本接口为非线程安全类型接口。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeBuffer
 * @param buffer 一个指向OH_NativeBuffer的结构体实例的指针。
 * @param virAddr 一个指向映射到当前进程的虚拟内存的地址的二级指针，作为出参使用。
 * @param config 一个指向OH_NativeBuffer_Config的结构体实例的指针，作为出参使用。
 * @return 执行成功时返回NATIVE_ERROR_OK。\n
 * buffer、virAddr或config为空指针时返回NATIVE_ERROR_INVALID_ARGUMENTS。\n
 * 映射失败时返回NATIVE_ERROR_UNKNOWN。\n
 * 其他返回值可参考OHNativeErrorCode。
 * @since 23
 * @version 1.0
 */
int32_t OH_NativeBuffer_MapAndGetConfig(OH_NativeBuffer* buffer, void** virAddr, OH_NativeBuffer_Config* config);
#ifdef __cplusplus
}
#endif

/** @} */
#endif
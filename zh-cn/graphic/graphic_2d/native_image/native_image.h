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
 * @addtogroup OH_NativeImage
 * @{
 *
 * @brief 定义获取和使用NativeImage的相关函数。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @since 9
 * @version 1.0
 */

/**
 * @file native_image.h
 *
 * @brief 定义获取和使用NativeImage的相关函数。
 *
 * @kit ArkGraphics2D
 * @library libnative_image.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @since 9
 * @version 1.0
 */

#ifndef NDK_INCLUDE_NATIVE_IMAGE_H_
#define NDK_INCLUDE_NATIVE_IMAGE_H_

#include <stdint.h>
#include "native_buffer/buffer_common.h"

#ifdef __cplusplus
extern "C" {
#endif

struct OH_NativeImage;
typedef struct OH_NativeImage OH_NativeImage;
typedef struct NativeWindow OHNativeWindow;
/**
 * @brief 定义结构体NativeWindowBuffer的新类型名OHNativeWindowBuffer。
 * @since 12
 */
typedef struct NativeWindowBuffer OHNativeWindowBuffer;
/**
 * @brief 有buffer可获取时触发的回调函数。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param context 用户自定义的上下文信息，会在回调触发时返回给用户。
 * @since 11
 * @version 1.0
 */
typedef void (*OH_OnFrameAvailable)(void *context);

/**
 * @brief 一个OH_NativeImage的监听者，通过OH_NativeImage_SetOnFrameAvailableListener接口注册该监听结构体，当有buffer可获取时，将触发回调给用户。
 *
 * @since 11
 * @version 1.0
 */
typedef struct OH_OnFrameAvailableListener {
    /** 用户自定义的上下文信息，会在回调触发时返回给用户 */
    void *context;
    /** 有buffer可获取时触发的回调函数 */
    OH_OnFrameAvailable onFrameAvailable;
} OH_OnFrameAvailableListener;

/**
 * @brief 创建一个OH_NativeImage实例，该实例与OpenGL ES的纹理ID和纹理目标相关联。\n
 * 本接口需要与OH_NativeImage_Destroy接口配合使用，否则会存在内存泄露。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param textureId OpenGL ES的纹理ID，OH_NativeImage实例会与之相关联。
 * @param textureTarget OpenGL ES的纹理目标，取值范围为GL_TEXTURE_2D和GL_TEXTURE_EXTERNAL_OES。
 * @return 创建成功则返回一个指向OH_NativeImage实例的指针，否则返回NULL。
 * @since 9
 * @version 1.0
 */
OH_NativeImage* OH_NativeImage_Create(uint32_t textureId, uint32_t textureTarget);

/**
 * @brief 获取与OH_NativeImage相关联的OHNativeWindow指针。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @return 成功则返回一个指向OHNativeWindow实例的指针，否则返回NULL。
 * @since 9
 * @version 1.0
 */
OHNativeWindow* OH_NativeImage_AcquireNativeWindow(OH_NativeImage* image);

/**
 * @brief 将OH_NativeImage实例附加到当前OpenGL ES上下文，且该OpenGL ES纹理会绑定到GL_TEXTURE_EXTERNAL_OES, 并通过OH_NativeImage进行更新。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param textureId OH_NativeImage要附加到的OpenGL ES纹理的id。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeImage_AttachContext(OH_NativeImage* image, uint32_t textureId);

/**
 * @brief 将OH_NativeImage实例从当前OpenGL ES上下文分离。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 9
 * @version 1.0
 */

int32_t OH_NativeImage_DetachContext(OH_NativeImage* image);

/**
 * @brief 通过OH_NativeImage获取最新帧更新相关联的OpenGL ES纹理。\n
 * 本接口需要在OpenGL ES环境上下文的线程中调用。\n
 * 本接口需要在接收到OH_OnFrameAvailableListener回调后调用。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeImage_UpdateSurfaceImage(OH_NativeImage* image);

/**
 * @brief 获取最近调用OH_NativeImage_UpdateSurfaceImage的纹理图像的相关时间戳。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @return 返回纹理图像的相关时间戳。
 * @since 9
 * @version 1.0
 */
int64_t OH_NativeImage_GetTimestamp(OH_NativeImage* image);

/**
 * @brief 获取最近调用OH_NativeImage_UpdateSurfaceImage的纹理图像的变化矩阵。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param matrix 用来存储要获取的4*4的变化矩阵。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 9
 * @version 1.0
 * @deprecated since 12
 * @useinstead OH_NativeImage_GetTransformMatrixV2
 */
int32_t OH_NativeImage_GetTransformMatrix(OH_NativeImage* image, float matrix[16]);

/**
 * @brief 获取OH_NativeImage的surface编号。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param surfaceId 是指向surface编号的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 11
 * @version 1.0
 */
int32_t OH_NativeImage_GetSurfaceId(OH_NativeImage* image, uint64_t* surfaceId);

/**
 * @brief 设置帧可用回调。\n
 * 不允许在回调函数中调用本模块的其他接口。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param listener 表示回调监听者。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 11
 * @version 1.0
 */
int32_t OH_NativeImage_SetOnFrameAvailableListener(OH_NativeImage* image, OH_OnFrameAvailableListener listener);

/**
 * @brief 取消设置帧可用回调。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @return 返回值为0表示执行成功，其他返回值可参考OHNativeErrorCode。
 * @since 11
 * @version 1.0
 */
int32_t OH_NativeImage_UnsetOnFrameAvailableListener(OH_NativeImage* image);

/**
 * @brief 销毁通过OH_NativeImage_Create创建的OH_NativeImage实例，销毁后该OH_NativeImage指针会被赋值为空。\n
 * 并将对应OHNativeWindow引用计数减一。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @since 9
 * @version 1.0
 */
void OH_NativeImage_Destroy(OH_NativeImage** image);

/**
 * @brief 根据生产端设置的旋转角度，获取最近调用OH_NativeImage_UpdateSurfaceImage的纹理图像的变化矩阵。\n
 * matrix在OH_NativeImage_UpdateSurfaceImage接口调用后，才会更新。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param matrix 用来存储要获取的4*4的变化矩阵。
 * @return 0 - 成功。\n
 *     40001000 - image为空。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeImage_GetTransformMatrixV2(OH_NativeImage* image, float matrix[16]);

/**
 * @brief 获取根据生产端设置的旋转角度和buffer实际有效内容区域计算出的变换矩阵。\n
 *
 * 本接口返回一个变换矩阵，该矩阵是OH_NativeImage在消费buffer，即调用\n
 * OH_NativeImage_UpdateSurfaceImage或者OH_NativeImage_AcquireNativeWindowBuffer时，\n
 * 根据buffer的旋转角度和实际有效内容区域计算所得。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param matrix 用于存储获取的4*4变换矩阵。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - image为空。\n
 *     NATIVE_ERROR_MEM_OPERATION_ERROR 30001000 - 内存操作错误，获取变换矩阵失败。
 * @since 15
 * @version 1.0
 */
int32_t OH_NativeImage_GetBufferMatrix(OH_NativeImage* image, float matrix[16]);

/**
 * @brief 通过消费端的OH_NativeImage获取一个OHNativeWindowBuffer。\n
 * 本接口不能与OH_NativeImage_UpdateSurfaceImage接口同时使用。\n
 * 本接口将会创建一个OHNativeWindowBuffer。\n
 * 当使用OHNativeWindowBuffer时，用户需要通过OH_NativeWindow_NativeObjectReference接口将其引用计数加一。\n
 * 当OHNativeWindowBuffer使用完，用户需要通过OH_NativeWindow_NativeObjectUnreference接口将其引用计数减一。\n
 * 本接口需要和OH_NativeImage_ReleaseNativeWindowBuffer接口配合使用，否则会存在内存泄露。\n
 * 当fenceFd使用完，用户需要将其close。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param nativeWindowBuffer 指向OHNativeWindowBuffer指针的指针。
 * @param fenceFd 指向文件描述符句柄的指针。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - image、nativeWindowBuffer、fenceFd为空。\n
 *     NATIVE_ERROR_NO_BUFFER 40601000 - 无buffer可供消费。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeImage_AcquireNativeWindowBuffer(OH_NativeImage* image,
    OHNativeWindowBuffer** nativeWindowBuffer, int* fenceFd);

/**
 * @brief 通过OH_NativeImage实例将OHNativeWindowBuffer归还到buffer队列中。\n
 * 系统会将fenceFd关闭，无需用户close。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param nativeWindowBuffer 指向OHNativeWindowBuffer实例的指针。
 * @param fenceFd 指向文件描述符句柄，用于并发同步控制。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - image、nativeWindowBuffer为空。\n
 *     NATIVE_ERROR_BUFFER_STATE_INVALID 41207000 - nativeWindowBuffer状态非法。\n
 *     NATIVE_ERROR_BUFFER_NOT_IN_CACHE 41210000 - nativeWindowBuffer不在缓存中。
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeImage_ReleaseNativeWindowBuffer(OH_NativeImage* image,
    OHNativeWindowBuffer* nativeWindowBuffer, int fenceFd);

/**
 * @brief 创建一个OH_NativeImage实例，作为surface的消费端。\n
 * 本接口仅用于surface消费端的内存轮转，创建的OH_NativeImage内部不会主动进行内存渲染处理。\n
 * 本接口不能与OH_NativeImage_UpdateSurfaceImage接口同时使用。\n
 * 本接口与OH_NativeImage_AcquireNativeWindowBuffer和OH_NativeImage_ReleaseNativeWindowBuffer配合使用。\n
 * 本接口需要和OH_NativeImage_Destroy接口配合使用，否则会存在内存泄露。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @return 成功则返回一个指向OH_NativeImage实例的指针，否则返回NULL。
 * @since 12
 * @version 1.0
 */
OH_NativeImage* OH_ConsumerSurface_Create(void);

/**
 * @brief 设置默认读写方式。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param usage 表示读写方式。枚举值参考OH_NativeBuffer_Usage。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - image为空。
 * @since 13
 * @version 1.0
 */
int32_t OH_ConsumerSurface_SetDefaultUsage(OH_NativeImage* image, uint64_t usage);

/**
 * @brief 设置几何图形默认尺寸。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param width 表示几何图形宽度，取值范围大于0，单位为像素。
 * @param height 表示几何图形高度，取值范围大于0，单位为像素。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - image为空，或width、height小于等于0。
 * @since 13
 * @version 1.0
 */
int32_t OH_ConsumerSurface_SetDefaultSize(OH_NativeImage* image, int32_t width, int32_t height);

/**
 * @brief 设置OH_NativeImage是否为渲染丢帧模式。\n
 * 处于此模式时，大部分生产端生产的buffer将会被丢弃，最新的buffer会及时上屏渲染。\n
 * 此模式不能同时保证帧率高的要求。\n
 * 此接口建议在OH_NativeImage_Create接口调用后立即调用。\n
 * 此接口在与OH_NativeImage_UpdateSurfaceImage接口一起使用的场景下才会生效。\n
 * 通过OH_NativeImage_SetOnFrameAvailableListener设置的listener回调不会因为设置了丢帧模式而减少。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param isOpen 是否设置渲染丢帧。true表示设置为渲染丢帧模式，false表示不设置。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - image为空。
 * @since 17
 * @version 1.0
 */
int32_t OH_NativeImage_SetDropBufferMode(OH_NativeImage* image, bool isOpen);

/**
 * @brief 使用纹理ID创建一个OH_NativeImage实例，该实例与OpenGL ES的纹理ID和纹理目标相关联，并选择是否设置单buffer模式。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param textureId OpenGL ES的纹理ID，OH_NativeImage实例会与之相关联。
 * @param textureTarget OpenGL ES的纹理目标。
 * @param singleBufferMode 是否设置单buffer模式。true表示设置为单buffer模式，false表示不设置。
 * @return 创建成功则返回一个指向OH_NativeImage实例的指针，否则返回NULL。
 * @since 22
 * @version 1.0
 */
OH_NativeImage* OH_NativeImage_CreateWithSingleBufferMode(
    uint32_t textureId, uint32_t textureTarget, bool singleBufferMode);

/**
 * @brief 不使用纹理ID创建一个OH_NativeImage实例，作为surface的消费端，并选择是否设置单buffer模式。\n
 * 本接口仅用于surface消费端的内存轮转，创建的OH_NativeImage内部不会主动进行内存渲染处理。\n
 * 本接口不能与OH_NativeImage_UpdateSurfaceImage接口同时使用。\n
 * 本接口需要和OH_NativeImage_Destroy接口配合使用，否则会存在内存泄露。\n
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param singleBufferMode 是否设置单buffer模式。true表示设置为单buffer模式，false表示不设置。
 * @return 成功则返回一个指向OH_NativeImage实例的指针，否则返回NULL。
 * @since 22
 * @version 1.0
 */
OH_NativeImage* OH_ConsumerSurface_CreateWithSingleBufferMode(bool singleBufferMode);

/**
 * @brief 解除SurfaceBuffer与纹理的绑定，将纹理恢复到未使用状态。\n
 * 单buffer模式下，需要调用该接口释放纹理，否则生产者下次无法申请buffer。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - image为空。
 * @since 22
 * @version 1.0
 */
int32_t OH_NativeImage_ReleaseTextImage(OH_NativeImage* image);

/**
 * @brief 获取最近调用OH_NativeImage_UpdateSurfaceImage的纹理图像的相关色彩空间。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param colorSpace 为OH_NativeImage设置的颜色空间，其值从OH_NativeBuffer_ColorSpace获取。
 * @return NATIVE_ERROR_OK 0 - 成功。
 * @since 22
 * @version 1.0
 */
int32_t OH_NativeImage_GetColorSpace(OH_NativeImage* image, OH_NativeBuffer_ColorSpace* colorSpace);

/**
 * @brief 通过消费端的OH_NativeImage获取一个生产者最近生产的OHNativeWindowBuffer，并将其余buffer丢弃。\n
 * 消费端可以通过OH_OnFrameAvailableListener注册的回调，收到所有可用buffer（包括被丢弃的buffer）的回调。\n
 * 本接口不能与OH_NativeImage_UpdateSurfaceImage接口同时使用。\n
 * 本接口将会创建一个OHNativeWindowBuffer。\n
 * 如果在调用OH_NativeImage_ReleaseNativeWindowBuffer之后还在使用OHNativeWindowBuffer的情况，需要注意以下两点。\n
 * 1) 当使用OHNativeWindowBuffer时，用户需要通过OH_NativeWindow_NativeObjectReference接口将其引用计数加一。\n
 * 2) 当OHNativeWindowBuffer使用完，用户需要通过OH_NativeWindow_NativeObjectUnreference接口将其引用计数减一。\n
 * 本接口需要和OH_NativeImage_ReleaseNativeWindowBuffer接口配合使用，否则会存在内存泄露。\n
 * 当fenceFd使用完，用户需要将其close。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param nativeWindowBuffer 指向OHNativeWindowBuffer的二级指针。
 * @param fenceFd 指向文件描述符句柄的指针。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - image、nativeWindowBuffer、fenceFd为空。\n
 *     NATIVE_ERROR_NO_BUFFER 40601000 - 无buffer可供消费。
 * @since 22
 * @version 1.0
 */
int32_t OH_NativeImage_AcquireLatestNativeWindowBuffer(OH_NativeImage* image,
    OHNativeWindowBuffer** nativeWindowBuffer, int* fenceFd);

/**
 * @brief 查询与OH_NativeImage关联的纹理是否已释放。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @param isReleased 纹理是否已释放。true表示纹理已释放，false表示纹理未释放，作为出参使用。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - image或isReleased为空。
 * @since 23
 * @version 1.0
 */
int32_t OH_NativeImage_IsReleased(OH_NativeImage* image, bool* isReleased);

/**
 * @brief 清除所有OHNativeWindow的OHNativeWindowBuffer缓存，并将OH_NativeImage从OpenGL ES上下文中分离。\n
 * 本接口为非线程安全类型接口。\n
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeImage
 * @param image 指向OH_NativeImage实例的指针。
 * @return NATIVE_ERROR_OK 0 - 成功。\n
 *     NATIVE_ERROR_INVALID_ARGUMENTS 40001000 - image为空。
 * @since 23
 * @version 1.0
 */
int32_t OH_NativeImage_Release(OH_NativeImage* image);
#ifdef __cplusplus
}
#endif

/** @} */
#endif
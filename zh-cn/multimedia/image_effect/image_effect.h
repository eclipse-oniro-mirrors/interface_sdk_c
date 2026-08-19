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
 * @addtogroup ImageEffect
 * @{
 *
 * @brief 提供图片编辑能力。
 *
 * @since 12
 */

/**
 * @file image_effect.h
 *
 * @brief 声明效果器相关接口。
 *
 * 效果器提供了滤镜的添加、删除、查询等功能。开发者可以通过效果器提供的接口将多个滤镜组合串联，从而实现较为复杂的效果调节功能。
 * 同时，效果器支持多种输入类型，如Pixelmap、URI、Surface、Picture。不同的输入类型在效果器内部都会转换为内存对象，通过滤镜的效果处理，
 * 获得处理结果。
 *
 * @library libimage_effect.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */

#ifndef NATIVE_IMAGE_EFFECT_H
#define NATIVE_IMAGE_EFFECT_H

#include "image_effect_errors.h"
#include "image_effect_filter.h"
#include "native_buffer/native_buffer.h"
#include "native_window/external_window.h"
#include "multimedia/image_framework/image/picture_native.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义效果器结构类型。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @since 12
 */
typedef struct OH_ImageEffect OH_ImageEffect;

/**
 * @brief 创建OH_ImageEffect实例，调用{@link OH_ImageEffect_Release}进行资源释放。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param name 效果器名，用于标识效果器，由用户自定义，建议为非空的字符串。
 * @return 返回一个指向OH_ImageEffect实例的指针，创建失败时返回空指针。
 * @since 12
 */
OH_ImageEffect *OH_ImageEffect_Create(const char *name);

/**
 * @brief 添加滤镜。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param filterName 滤镜名。
 * @return 返回一个指向OH_EffectFilter实例的指针，滤镜名无效时返回空指针。
 * @since 12
 */
OH_EffectFilter *OH_ImageEffect_AddFilter(OH_ImageEffect *imageEffect, const char *filterName);

/**
 * @brief 添加指定滤镜。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param filter 滤镜指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_AddFilterByFilter(OH_ImageEffect *imageEffect, OH_EffectFilter *filter);

/**
 * @brief 插入滤镜。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param index 插入滤镜位置索引。
 * @param filterName 滤镜名。
 * @return 返回一个指向OH_EffectFilter实例的指针，参数无效时返回空指针。
 * @since 12
 */
OH_EffectFilter *OH_ImageEffect_InsertFilter(OH_ImageEffect *imageEffect, uint32_t index, const char *filterName);

/**
 * @brief 按指定位置插入滤镜。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param index 插入滤镜位置索引。
 * @param filter 滤镜指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_InsertFilterByFilter(OH_ImageEffect *imageEffect, uint32_t index,
    OH_EffectFilter *filter);

/**
 * @brief 移除滤镜。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param filterName 滤镜名。
 * @return 所删除的滤镜个数。
 * @since 12
 */
int32_t OH_ImageEffect_RemoveFilter(OH_ImageEffect *imageEffect, const char *filterName);

/**
 * @brief 移除指定位置滤镜。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param index 移除滤镜位置索引。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_RemoveFilterByIndex(OH_ImageEffect *imageEffect, uint32_t index);

/**
 * @brief 替换滤镜。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param index OH_EffectFilter创建和替换的位置
 * @param filterName 滤镜名。
 * @return 返回一个指向OH_EffectFilter实例的指针，替换失败时返回空指针。
 * @since 12
 */
OH_EffectFilter *OH_ImageEffect_ReplaceFilter(OH_ImageEffect *imageEffect, uint32_t index, const char *filterName);

/**
 * @brief 替换指定位置滤镜。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param index 替换滤镜位置索引。
 * @param filter 滤镜指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_ReplaceFilterByFilter(OH_ImageEffect *imageEffect, uint32_t index,
    OH_EffectFilter *filter);

/**
 * @brief 查询已添加滤镜个数。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @return 已添加的滤镜个数。
 * @since 12
 */
int32_t OH_ImageEffect_GetFilterCount(OH_ImageEffect *imageEffect);

/**
 * @brief 查询已添加滤镜。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param index 待查询滤镜位置索引。
 * @return 返回一个指向OH_EffectFilter实例的指针，参数无效时返回空指针。
 * @since 12
 */
OH_EffectFilter *OH_ImageEffect_GetFilter(OH_ImageEffect *imageEffect, uint32_t index);

/**
 * @brief 设置配置信息。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param key 配置参数。
 * @param value 配置参数值。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 *         EFFECT_KEY_ERROR：参数无效。
 *         EFFECT_PARAM_ERROR：参数值无效。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_Configure(OH_ImageEffect *imageEffect, const char *key,
    const ImageEffect_Any *value);

/**
 * @brief 设置输出Surface。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param nativeWindow 指向OHNativeWindow实例的指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_SetOutputSurface(OH_ImageEffect *imageEffect, OHNativeWindow *nativeWindow);

/**
 * @brief 获取输入Surface。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param nativeWindow 指向OHNativeWindow实例的指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_GetInputSurface(OH_ImageEffect *imageEffect, OHNativeWindow **nativeWindow);

/**
 * @brief 设置输入的Pixelmap。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param pixelmap 指向OH_PixelmapNative实例的指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_SetInputPixelmap(OH_ImageEffect *imageEffect, OH_PixelmapNative *pixelmap);

/**
 * @brief 设置输出的Pixelmap。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param pixelmap 指向OH_PixelmapNative实例的指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 *         EFFECT_PARAM_ERROR：如果参数异常导致方法调用失败。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_SetOutputPixelmap(OH_ImageEffect *imageEffect, OH_PixelmapNative *pixelmap);

/**
 * @brief 设置输入的NativeBuffer。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param nativeBuffer 指向OH_NativeBuffer实例的指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_SetInputNativeBuffer(OH_ImageEffect *imageEffect, OH_NativeBuffer *nativeBuffer);

/**
 * @brief 设置输出的NativeBuffer。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param nativeBuffer 指向OH_NativeBuffer实例的指针，允许为空，当输入为空时渲染结果返回到输入的OH_NativeBuffer对象上。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
  *        EFFECT_PARAM_ERROR：如果参数异常导致方法调用失败。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_SetOutputNativeBuffer(OH_ImageEffect *imageEffect, OH_NativeBuffer *nativeBuffer);

/**
 * @brief 设置输入的URI。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param uri 图片URI（只支持Jpeg，Heif）。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_SetInputUri(OH_ImageEffect *imageEffect, const char *uri);

/**
 * @brief 设置输出的URI。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param uri 图片URI。输出URI的格式和输入保持一致，如果不支持Heif编码能力，则进行Jpeg编码。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_SetOutputUri(OH_ImageEffect *imageEffect, const char *uri);

/**
 * @brief 设置输入的Picture。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param picture 指向OH_PictureNative实例的指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 13
 */
ImageEffect_ErrorCode OH_ImageEffect_SetInputPicture(OH_ImageEffect *imageEffect, OH_PictureNative *picture);

/**
 * @brief 设置输出的Picture。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param picture 指向OH_PictureNative实例的指针，允许为空，当输入为空时渲染结果返回到输入的OH_PictureNative对象上。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 *         EFFECT_PARAM_ERROR：如果参数异常导致方法调用失败。
 * @since 13
 */
ImageEffect_ErrorCode OH_ImageEffect_SetOutputPicture(OH_ImageEffect *imageEffect, OH_PictureNative *picture);

/**
 * @brief 配置输入包含图片内容的纹理标识。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect OH_ImageEffect结构体实例指针。
 * @param textureId 包含图片内容的纹理标识，纹理标识必须是有效的且绑定了GL_TEXTURE_2D类型的纹理。
 * @param colorSpace 图片对应的色彩空间。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针或参数超出有效范围。
 *         EFFECT_PARAM_ERROR：参数缺失或参数错误。
 * @since 20
 */
ImageEffect_ErrorCode OH_ImageEffect_SetInputTextureId(OH_ImageEffect *imageEffect, int32_t textureId,
    int32_t colorSpace);

/**
 * @brief 配置输出包含渲染后的纹理标识。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect OH_ImageEffect结构体实例指针。
 * @param textureId 包含图片渲染后内容的纹理标识，纹理标识必须是一个有效的纹理。
 *        如果纹理标识未被绑定纹理图片，纹理标识会自动绑定GL_TEXTURE_2D类型；
 *        如果纹理标识已经被绑定纹理且尺寸不合适，结果可能会被裁剪或部分填充到此纹理上。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针或参数超出有效范围。
 *         EFFECT_PARAM_ERROR：参数缺失或参数错误。
 * @since 20
 */
ImageEffect_ErrorCode OH_ImageEffect_SetOutputTextureId(OH_ImageEffect *imageEffect, int32_t textureId);

/**
 * @brief 启动效果器。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 *         EFFECT_INPUT_OUTPUT_NOT_SUPPORTED：待处理输入、输出图像数据类型不一致。
 *         EFFECT_COLOR_SPACE_NOT_MATCH：输入、输出图像色彩空间不配置。
 *         EFFECT_ALLOCATE_MEMORY_FAILED：内存申请失败。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_Start(OH_ImageEffect *imageEffect);

/**
 * @brief 停止生效效果。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_Stop(OH_ImageEffect *imageEffect);

/**
 * @brief 释放OH_ImageEffect实例资源。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_Release(OH_ImageEffect *imageEffect);

/**
 * @brief 序列化效果器。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param imageEffect 效果器指针。
 * @param info 指向char数组的指针，返回序列化JSON字符串。
 * @return EFFECT_SUCCESS：方法调用成功。
 *         EFFECT_ERROR_PARAM_INVALID：入参为空指针。
 * @since 12
 */
ImageEffect_ErrorCode OH_ImageEffect_Save(OH_ImageEffect *imageEffect, char **info);

/**
 * @brief 反序列化效果器。
 *
 * @syscap SystemCapability.Multimedia.ImageEffect.Core
 * @param info 序列化JSON字符串。
 * @return 反序列化成功时返回OH_ImageEffect实例，否则返回空指针。
 * @since 12
 */
OH_ImageEffect *OH_ImageEffect_Restore(const char *info);

#ifdef __cplusplus
}
#endif
#endif // NATIVE_IMAGE_EFFECT_H
/** @} */
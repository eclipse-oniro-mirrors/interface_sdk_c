/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup Image_NativeModule
 * @{
 *
 * @brief Provides APIs for access to the image interface.
 *
 * @since 12
 */

/**
 * @file image_packer_native.h
 *
 * @brief 图片编码API。
 * 
 * @library libimage_packer.so
 * @kit ImageKit
 * @syscap SystemCapability.Multimedia.Image.ImagePacker
 * @since 12
 */

#ifndef INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_IMAGE_PACKER_NATIVE_H_
#define INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_IMAGE_PACKER_NATIVE_H_
#include <stdbool.h>

#include "image_common.h"
#include "image_source_native.h"
#include "pixelmap_native.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief OH_ImagePackerNative用于将ImageSource、PixelMap、Picture或PixelMap序列编码为图片数据或文件。<br>使用
 * {@link OH_ImagePackerNative_Create}函数创建OH_ImagePackerNative对象。<br>使用{@link OH_ImagePackerNative_Release}
 * 函数释放OH_ImagePackerNative对象。<br>资源管理：OH_ImagePackerNative使用完成后，应调用{@link OH_ImagePackerNative_Release}释放。
 * 释放OH_ImagePackerNative对象不会释放OH_PackingOptions、OH_PackingOptionsForSequence、OH_ImageSourceNative、
 * OH_PixelmapNative或OH_PictureNative对象。<br>OH_ImagePackerNative支持的编码方式如下：<br>| 输入对象 | 输出位置 | 编码函数 | 描述 || -- | -- | --
 * | -- || {@link OH_ImageSourceNative} | 数据缓冲区 | {@link OH_ImagePackerNative_PackToDataFromImageSource} |
 * 将ImageSource编码为指定格式的数据。 || {@link OH_PixelmapNative} | 数据缓冲区 | {@link OH_ImagePackerNative_PackToDataFromPixelmap} |
 * 将PixelMap编码为指定格式的数据。 || {@link OH_PictureNative} | 数据缓冲区 | {@link OH_ImagePackerNative_PackToDataFromPicture} |
 * 将Picture编码为指定格式的数据，仅支持JPEG和HEIF。 || OH_PixelmapNative数组 | 数据缓冲区 |
 * {@link OH_ImagePackerNative_PackToDataFromPixelmapSequence} | 将PixelMap序列编码为GIF格式数据。 || {@link OH_ImageSourceNative}
 * | 文件描述符 | {@link OH_ImagePackerNative_PackToFileFromImageSource} | 将ImageSource编码到文件中。 || {@link OH_PixelmapNative} |
 *  文件描述符 | {@link OH_ImagePackerNative_PackToFileFromPixelmap} | 将PixelMap编码到文件中。 || {@link OH_PictureNative} | 文件描述符 |
 *  {@link OH_ImagePackerNative_PackToFileFromPicture} | 将Picture编码到文件中，仅支持JPEG和HEIF。 || OH_PixelmapNative数组 | 文件描述符 |
 *  {@link OH_ImagePackerNative_PackToFileFromPixelmapSequence} | 将PixelMap序列编码为GIF格式并写入文件。 |<br>获取支持编码的图片格式使用
 * {@link OH_ImagePackerNative_GetSupportedFormats}函数。
 * 
 * @since 12
 */
struct OH_ImagePackerNative;
typedef struct OH_ImagePackerNative OH_ImagePackerNative;

/**
 * @brief OH_PackingOptions是native层封装的图像编码选项结构体，不可直接操作，而是采用函数调用方式创建、释放结构体以及操作具体字段。<br>使用
 * {@link OH_PackingOptions_Create}函数创建OH_PackingOptions对象。<br>使用{@link OH_PackingOptions_Release}
 * 函数释放OH_PackingOptions对象。<br>使用约束：OH_PackingOptions用于配置ImageSource、PixelMap或Picture编码参数。<br>资源管理：
 * 释放OH_ImagePackerNative对象不会自动释放OH_PackingOptions对象。OH_PackingOptions使用完成后，应调用{@link OH_PackingOptions_Release}释放，
 * 释放后不应继续传入图像编码接口或调用其字段获取和设置接口。<br>OH_PackingOptions结构体内容和操作方式如下：<br>| 字段类型 | 字段名称 | 字段描述 | 字段获取函数 | 字段设置函数 || -- | --
 * | -- | -- | -- || {@link Image_MimeType} | mimeType | 目标编码格式的MIME类型。ImageSource或PixelMap编码支持`image/jpeg`、`image/webp`
 * 、`image/png`、`image/heic`或`image/heif`、`image/sdr_astc_4x4`、`image/sdr_sut_superfast_4x4`、`image/hdr_astc_4x4`；
 * Picture编码支持`image/jpeg`、`image/heic`或`image/heif`。实际支持范围以{@link OH_ImagePackerNative_GetSupportedFormats}返回结果为准。 |
 * {@link OH_PackingOptions_GetMimeType}、{@link OH_PackingOptions_GetMimeTypeWithNull} |
 * {@link OH_PackingOptions_SetMimeType} || uint32_t | quality | 编码质量，实际编码效果取决于目标编码格式。 |
 * {@link OH_PackingOptions_GetQuality} | {@link OH_PackingOptions_SetQuality} || bool | needsPackProperties |
 * 是否需要编码图像属性，例如Exif。 | {@link OH_PackingOptions_GetNeedsPackProperties} |
 * {@link OH_PackingOptions_SetNeedsPackProperties} || int32_t | desiredDynamicRange | 编码时期望的图片动态范围，取值见
 * {@link IMAGE_PACKER_DYNAMIC_RANGE}。 | {@link OH_PackingOptions_GetDesiredDynamicRange} |
 * {@link OH_PackingOptions_SetDesiredDynamicRange} |
 * 
 * @since 12
 */
struct OH_PackingOptions;
typedef struct OH_PackingOptions OH_PackingOptions;

/**
 * @brief OH_PackingOptionsForSequence是native层封装的GIF序列编码选项结构体，不可直接操作，而是采用函数调用方式创建、释放结构体以及操作具体字段。<br>使用
 * {@link OH_PackingOptionsForSequence_Create}函数创建OH_PackingOptionsForSequence对象。<br>使用
 * {@link OH_PackingOptionsForSequence_Release}函数释放OH_PackingOptionsForSequence对象。<br>使用约束：
 * OH_PackingOptionsForSequence用于配置PixelMap序列编码为GIF格式时的编码参数，需传入
 * {@link OH_ImagePackerNative_PackToDataFromPixelmapSequence}或
 * {@link OH_ImagePackerNative_PackToFileFromPixelmapSequence}使用。<br>资源管理：OH_PackingOptionsForSequence使用完成后，应调用
 * {@link OH_PackingOptionsForSequence_Release}释放。释放后不应继续传入图像序列编码接口或调用其字段获取和设置接口。通过
 * {@link OH_PackingOptionsForSequence_SetDelayTimeList}和{@link OH_PackingOptionsForSequence_SetDisposalTypes}
 * 传入的数组不会被拷贝，调用方需保证OH_PackingOptionsForSequence对象使用期间数组数据有效。释放OH_PackingOptionsForSequence对象不会释放这些数组。<br>
 * OH_PackingOptionsForSequence结构体内容和操作方式如下：<br>| 字段类型 | 字段名称 | 字段描述 | 字段获取函数 | 字段设置函数 || -- | -- | -- | -- | -- ||
 * uint32_t | frameCount | 编码时指定的帧数，编码时必须大于0。 | {@link OH_PackingOptionsForSequence_GetFrameCount} |
 * {@link OH_PackingOptionsForSequence_SetFrameCount} || int32_t * | delayTimeList | 编码时图片的延迟时间数组，
 * 数组中的每个延迟时间必须大于0且不超过65535，单位为10毫秒（ms）。 | {@link OH_PackingOptionsForSequence_GetDelayTimeList} |
 * {@link OH_PackingOptionsForSequence_SetDelayTimeList} || uint32_t * | disposalTypes | 编码时图片的过渡帧模式数组，数组中的每个取值必须小于等于3，
 * 取值含义见{@link OH_PackingOptionsForSequence_SetDisposalTypes}。 | {@link OH_PackingOptionsForSequence_GetDisposalTypes} |
 *  {@link OH_PackingOptionsForSequence_SetDisposalTypes} || uint32_t | loopCount | 编码时图片循环播放次数，取值范围为[0, 65535]。 |
 * {@link OH_PackingOptionsForSequence_GetLoopCount} | {@link OH_PackingOptionsForSequence_SetLoopCount} |
 * 
 * @since 18
 */
struct OH_PackingOptionsForSequence;

/**
 * @brief OH_PackingOptionsForSequence是native层封装的GIF序列编码选项结构体，不可直接操作，而是采用函数调用方式创建、释放结构体以及操作具体字段。<br>使用
 * {@link OH_PackingOptionsForSequence_Create}函数创建OH_PackingOptionsForSequence对象。<br>使用
 * {@link OH_PackingOptionsForSequence_Release}函数释放OH_PackingOptionsForSequence对象。<br>使用约束：
 * OH_PackingOptionsForSequence用于配置PixelMap序列编码为GIF格式时的编码参数，需传入
 * {@link OH_ImagePackerNative_PackToDataFromPixelmapSequence}或
 * {@link OH_ImagePackerNative_PackToFileFromPixelmapSequence}使用。<br>资源管理：OH_PackingOptionsForSequence使用完成后，应调用
 * {@link OH_PackingOptionsForSequence_Release}释放。释放后不应继续传入图像序列编码接口或调用其字段获取和设置接口。通过
 * {@link OH_PackingOptionsForSequence_SetDelayTimeList}和{@link OH_PackingOptionsForSequence_SetDisposalTypes}
 * 传入的数组不会被拷贝，调用方需保证OH_PackingOptionsForSequence对象使用期间数组数据有效。释放OH_PackingOptionsForSequence对象不会释放这些数组。<br>
 * OH_PackingOptionsForSequence结构体内容和操作方式如下：<br>| 字段类型 | 字段名称 | 字段描述 | 字段获取函数 | 字段设置函数 || -- | -- | -- | -- | -- ||
 * uint32_t | frameCount | 编码时指定的帧数，编码时必须大于0。 | {@link OH_PackingOptionsForSequence_GetFrameCount} |
 * {@link OH_PackingOptionsForSequence_SetFrameCount} || int32_t * | delayTimeList | 编码时图片的延迟时间数组，
 * 数组中的每个延迟时间必须大于0且不超过65535，单位为10毫秒（ms）。 | {@link OH_PackingOptionsForSequence_GetDelayTimeList} |
 * {@link OH_PackingOptionsForSequence_SetDelayTimeList} || uint32_t * | disposalTypes | 编码时图片的过渡帧模式数组，数组中的每个取值必须小于等于3，
 * 取值含义见{@link OH_PackingOptionsForSequence_SetDisposalTypes}。 | {@link OH_PackingOptionsForSequence_GetDisposalTypes} |
 *  {@link OH_PackingOptionsForSequence_SetDisposalTypes} || uint32_t | loopCount | 编码时图片循环播放次数，取值范围为[0, 65535]。 |
 * {@link OH_PackingOptionsForSequence_GetLoopCount} | {@link OH_PackingOptionsForSequence_SetLoopCount} |
 * 
 * @since 18
 */
typedef struct OH_PackingOptionsForSequence OH_PackingOptionsForSequence;

/**
 * @brief 编码指定动态范围。
 * 
 * @since 12
 */
typedef enum {
    /**
     * 编码动态范围根据图像信息自适应。
     */
    IMAGE_PACKER_DYNAMIC_RANGE_AUTO = 0,
    /**
     * 编码图片为标准动态范围。
     */
    IMAGE_PACKER_DYNAMIC_RANGE_SDR = 1,
} IMAGE_PACKER_DYNAMIC_RANGE;

/**
 * @brief 创建PackingOptions结构体的指针。
 * <br>使用约束：options不能为空指针；接口返回失败时，输出参数内容不应使用。
 * <br>资源管理：接口成功返回的OH_PackingOptions对象由调用方管理，使用完成后应调用{@link OH_PackingOptions_Release}释放。
 * 
 * @param options 用于操作的PackingOptions指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @release image_packer_native/OH_PackingOptions_Release {options}
 * @since 12
 */
Image_ErrorCode OH_PackingOptions_Create(OH_PackingOptions **options);

/**
 * @brief 获取编码参数中的MIME类型。该接口获取的format.data缺少字符串结束符'\0'，请谨慎使用。
 * <br>使用约束：options和format均不能为空指针。调用前若format->size不为0，则format->size必须大于或等于当前MIME类型长度。接口返回失败时，不应读取format.data。
 * <br>资源管理：接口执行成功后，format.data由接口分配，调用方使用完成后应使用free()释放。该接口返回的format.data不以字符串结束符'\0'结尾，如需按C字符串处理，建议使用
 * {@link OH_PackingOptions_GetMimeTypeWithNull}。
 * 
 * @param options 被操作的OH_PackingOptions指针。
 * @param format 图像格式。format无需手动初始化，系统将分配内存，但必须在使用后释放内存。
 *     <br>该接口获取到的format.data缺少字符串结束符'\0'，需要检查实际数据长度是否超出了申请缓冲区的长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PackingOptions_GetMimeType(OH_PackingOptions *options,
    Image_MimeType *format);

/**
 * @brief 获取编码参数中的MIME类型。该接口获取的format.data以字符串结束符'\0'结尾。
 * <br>使用场景：适用于读取字符串形式的MIME类型。与{@link OH_PackingOptions_GetMimeType}相比，本接口返回的format.data以'\0'结尾，更适合直接按C字符串处理。
 * <br>使用约束：options和format均不能为空指针。调用前若format->size不为0，则format->size必须大于或等于当前MIME类型长度。接口返回失败时，不应读取format.data。
 * <br>资源管理：接口执行成功后，format.data由接口分配，调用方使用完成后应使用free()释放。
 *
 * @param options 编码参数指针。
 * @param format 编码参数中的 MIME 类型的指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_PACKER_INVALID_PARAMETER：options或format为空。
 * @since 19
 */
Image_ErrorCode OH_PackingOptions_GetMimeTypeWithNull(OH_PackingOptions *options,
    Image_MimeType *format);

/**
 * @brief Sets the MIME type.
 * 
 * @param options Pointer to an OH_PackingOptions struct.
 * @param format Pointer to a MIME type string in the form "type/subtype".
 * @return {@link IMAGE_SUCCESS} if the execution is successful.
 *     <br>{@link IMAGE_BAD_PARAMETER} options is nullptr, or format is nullptr.
 *     <br>{@link IMAGE_ALLOC_FAILED} allocate memory failed.
 *     <br>{@link IMAGE_COPY_FAILED} copy memory failed.

 * @since 12
 */
Image_ErrorCode OH_PackingOptions_SetMimeType(OH_PackingOptions *options,
    Image_MimeType *format);

/**
 * @brief 获取编码质量。
 * <br>使用约束：options和quality均不能为空指针。接口返回失败时，输出参数内容不应使用。
 * 
 * @param options 被操作的OH_PackingOptions指针。
 * @param quality 编码质量。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PackingOptions_GetQuality(OH_PackingOptions *options,
    uint32_t *quality);

/**
 * @brief 设置编码质量。
 * <br>使用约束：options不能为空指针，quality取值范围为[0, 100]。OH_PackingOptions创建后，quality默认值为0，建议设置quality不低于80。quality的实际效果取决于目标编码格式。
 * 
 * @param options 被操作的OH_PackingOptions指针。
 * @param quality 编码质量，取值范围为[0, 100]，默认值为0。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PackingOptions_SetQuality(OH_PackingOptions *options,
    uint32_t quality);

/**
 * @brief 获取OH_PackingOptions结构体的needsPackProperties参数。
 * <br>使用约束：options和needsPackProperties均不能为空指针。接口返回失败时，输出参数内容不应使用。
 * 
 * @param options 被操作的OH_PackingOptions指针。
 * @param needsPackProperties 是否需要编码图片属性信息（例如Exif）。true表示需要，false表示不需要。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PackingOptions_GetNeedsPackProperties(OH_PackingOptions *options,
    bool *needsPackProperties);

/**
 * @brief 设置OH_PackingOptions结构体的needsPackProperties参数。
 * <br>使用场景：当需要在编码输出中保留或写入图片属性信息（例如Exif）时，将needsPackProperties设置为true。如果只关心像素内容、希望减少输出数据体积或目标格式不需要保留属性信息，可设置为false。
 * <br>使用约束：options不能为空指针。
 * 
 * @param options 被操作的OH_PackingOptions指针。
 * @param needsPackProperties 是否需要编码图片属性信息（例如Exif）。true表示需要，false表示不需要。默认值为false。
 *     <br>如果原始图片本身没有Exif数据，那么即使设置needsPackProperties为true，输出文件也不会包含这些属性。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PackingOptions_SetNeedsPackProperties(OH_PackingOptions *options,
    bool needsPackProperties);

/**
 * @brief 获取OH_PackingOptions结构体中的needsPackDfxData参数。
 *
 * @systemapi
 * @param options 指向OH_PackingOptions结构体的指针。
 * @param needsPackDfxData 图像DFX数据是否需要编码。true表示图像DFX数据需要编码，false表示图像DFX数据不需要编码。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>202：非系统应用程序调用该接口则返回此错误码。</li>
 *     <br><li>IMAGE_PACKER_INVALID_PARAMETER：options或needsPackDfxData为空指针。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PackingOptions_GetNeedsPackDfxData(OH_PackingOptions *options,
    bool *needsPackDfxData);

/**
 * @brief 设置OH_PackingOptions结构体中的needsPackDfxData参数。
 *
 * @systemapi
 * @param options 指向OH_PackingOptions结构体的指针。
 * @param needsPackDfxData 图像DFX数据是否需要编码。true表示图像DFX数据需要编码，false表示图像DFX数据不需要编码。
 * @return <ul>
 *     <br><li>IMAGE_SUCCESS：执行成功。</li>
 *     <br><li>202：非系统应用程序调用该接口则返回此错误码。</li>
 *     <br><li>IMAGE_PACKER_INVALID_PARAMETER：options为空指针。</li>
 *     <br></ul>
 * @since 26.0.0
 */
Image_ErrorCode OH_PackingOptions_SetNeedsPackDfxData(OH_PackingOptions *options,
    bool needsPackDfxData);

/**
 * @brief 获取编码时期望的图片动态范围。
 * <br>使用约束：options和desiredDynamicRange均不能为空指针。接口返回失败时，输出参数内容不应使用。
 * 
 * @param options 被操作的OH_PackingOptions指针。
 * @param desiredDynamicRange 期望的动态范围{@link IMAGE_PACKER_DYNAMIC_RANGE}。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PackingOptions_GetDesiredDynamicRange(OH_PackingOptions *options, int32_t* desiredDynamicRange);

/**
 * @brief 设置编码时期望的图片动态范围。
 * <br>使用约束：options不能为空指针。
 * 
 * @param options 被操作的OH_PackingOptions指针。
 * @param desiredDynamicRange 期望的动态范围{@link IMAGE_PACKER_DYNAMIC_RANGE}。默认值为IMAGE_PACKER_DYNAMIC_RANGE_SDR。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PackingOptions_SetDesiredDynamicRange(OH_PackingOptions *options, int32_t desiredDynamicRange);

/**
 * @brief 释放OH_PackingOptions指针。
 * <br>使用约束：options不能为空指针。
 * <br>资源管理：由{@link OH_PackingOptions_Create}成功创建的对象，都应在编码完成后调用本接口释放。释放OH_PackingOptions不会影响已经完成的编码输出，
 * 也不会释放OH_ImagePackerNative对象；调用该接口后，options指向的OH_PackingOptions对象会被释放，不应继续使用。
 * 
 * @param options 被操作的OH_PackingOptions指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_PackingOptions_Release(OH_PackingOptions *options);

/**
 * @brief 创建OH_PackingOptionsForSequence结构体的指针。
 * <br>使用约束：options不能为空指针。接口返回失败时，输出参数内容不应使用。
 * <br>资源管理：接口成功返回的OH_PackingOptionsForSequence对象由调用方管理，使用完成后应调用{@link OH_PackingOptionsForSequence_Release}释放。
 * 
 * @param options 用于操作的OH_PackingOptionsForSequence指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PackingOptionsForSequence_Create(OH_PackingOptionsForSequence **options);

/**
 * @brief 设置编码时指定的帧数。
 * <br>使用约束：options不能为空指针。
 * 
 * @param options 用于操作的OH_PackingOptionsForSequence指针。
 * @param frameCount 图片的帧数。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PackingOptionsForSequence_SetFrameCount(OH_PackingOptionsForSequence *options,
    uint32_t frameCount);

/**
 * @brief 获取编码时指定的帧数。
 * <br>使用约束：options和frameCount均不能为空指针。接口返回失败时，输出参数内容不应使用。
 * 
 * @param options 用于操作的OH_PackingOptionsForSequence指针。
 * @param frameCount 图片的帧数。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PackingOptionsForSequence_GetFrameCount(OH_PackingOptionsForSequence *options,
    uint32_t *frameCount);

/**
 * @brief 设定编码时图片的延迟时间数组。
 * <br>使用约束：options不能为空指针。
 * <br>资源管理：接口会保存传入的delayTimeList指针，不拷贝数组内容。调用方需保证OH_PackingOptionsForSequence对象使用期间delayTimeList指向的数据有效。多次调用该接口时，
 * 新的delayTimeList指针会替换此前保存的指针。
 * 
 * @param options 用于操作的OH_PackingOptionsForSequence指针。
 * @param delayTimeList 图片延迟时间数组的指针。延迟时间的单位为10毫秒（ms）。
 * @param delayTimeListLength 图片延迟时间数组的长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PackingOptionsForSequence_SetDelayTimeList(OH_PackingOptionsForSequence *options,
    int32_t *delayTimeList, size_t delayTimeListLength);

/**
 * @brief 获取编码时图片的延迟时间数组。
 * <br>使用约束：options和delayTimeList均不能为空指针，delayTimeListLength必须大于0。接口会将已设置的延迟时间数组拷贝到调用方传入的delayTimeList缓冲区。接口返回失败时，
 * 输出缓冲区内容不应使用。
 * 
 * @param options 用于操作的OH_PackingOptionsForSequence指针。
 * @param delayTimeList 图片延迟时间数组的指针。
 * @param delayTimeListLength 图片延迟时间数组的长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PackingOptionsForSequence_GetDelayTimeList(OH_PackingOptionsForSequence *options,
    int32_t *delayTimeList, size_t delayTimeListLength);

/**
 * @brief 设定编码时图片的过渡帧模式数组。
 * <br>使用约束：options不能为空指针。
 * <br>资源管理：接口会保存传入的disposalTypes指针，不拷贝数组内容。调用方需保证OH_PackingOptionsForSequence对象使用期间disposalTypes指向的数据有效。多次调用该接口时，
 * 新的disposalTypes指针会替换此前保存的指针。
 * 
 * @param options 用于操作的OH_PackingOptionsForSequence指针。
 * @param disposalTypes 图片过渡帧模式数组的指针，图片帧过渡模式的参数，如果长度小于frameCount，不足的部分将使用disposalTypes中的最后一个值进行填充，可取值如下：
 *     <br>0：不需要任何操作。
 *     <br>1：保持图形不变。
 *     <br>2：恢复背景色。
 *     <br>3：恢复到之前的状态。
 * @param disposalTypesLength 图片过渡帧模式数组的长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PackingOptionsForSequence_SetDisposalTypes(OH_PackingOptionsForSequence *options,
    uint32_t *disposalTypes, size_t disposalTypesLength);

/**
 * @brief 获取编码时图片的过渡帧模式数组。
 * <br>使用约束：options和disposalTypes均不能为空指针，disposalTypesLength必须大于0。接口会将已设置的过渡帧模式数组拷贝到调用方传入的disposalTypes缓冲区。接口返回失败时，
 * 输出缓冲区内容不应使用。
 * 
 * @param options 用于操作的OH_PackingOptionsForSequence指针。
 * @param disposalTypes 图片过渡帧模式数组的指针。
 * @param disposalTypesLength 图片过渡帧模式数组的长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PackingOptionsForSequence_GetDisposalTypes(OH_PackingOptionsForSequence *options,
    uint32_t *disposalTypes, size_t disposalTypesLength);

/**
 * @brief 设定编码时图片循环播放次数，取值范围为[0，65535]，0表示无限循环；若无此字段，则表示不循环播放。
 * <br>使用约束：options不能为空指针。本接口仅保存传入的loopCount。当loopCount大于65535时，本接口仍会返回成功，但后续调用
 * {@link OH_ImagePackerNative_PackToDataFromPixelmapSequence}或
 * {@link OH_ImagePackerNative_PackToFileFromPixelmapSequence}编码时会返回参数错误。
 * 
 * @param options 用于操作的OH_PackingOptionsForSequence指针。
 * @param loopCount 图片循环播放次数。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PackingOptionsForSequence_SetLoopCount(OH_PackingOptionsForSequence *options, uint32_t loopCount);

/**
 * @brief 获取编码时图片循环播放次数。
 * <br>使用约束：options和loopCount均不能为空指针。接口返回失败时，输出参数内容不应使用。
 * 
 * @param options 用于操作的OH_PackingOptionsForSequence指针。
 * @param loopCount 图片循环播放次数。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PackingOptionsForSequence_GetLoopCount(OH_PackingOptionsForSequence *options, uint32_t *loopCount);

/**
 * @brief 释放OH_PackingOptionsForSequence指针。
 * <br>使用约束：options不能为空指针。
 * <br>资源管理：调用该接口后，options指向的OH_PackingOptionsForSequence对象会被释放，不应继续使用。释放OH_PackingOptionsForSequence对象不会释放通过
 * {@link OH_PackingOptionsForSequence_SetDelayTimeList}或{@link OH_PackingOptionsForSequence_SetDisposalTypes}传入的数组。
 * 
 * @param options 用于操作的OH_PackingOptionsForSequence指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 18
 */
Image_ErrorCode OH_PackingOptionsForSequence_Release(OH_PackingOptionsForSequence *options);

/**
 * @brief 创建OH_ImagePackerNative指针。
 * <br>使用场景：适用于将ImageSource、PixelMap、Picture或PixelMap序列编码为JPEG、PNG、WebP等格式的数据或文件。创建ImagePacker后，
 * 需要结合OH_PackingOptions或OH_PackingOptionsForSequence设置编码格式、质量、是否保留图片属性等参数。
 * <br>使用约束：imagePacker不能为空指针。接口返回失败时，输出参数内容不应使用。
 * <br>资源管理：成功创建的OH_ImagePackerNative对象由调用方持有，使用完成后必须调用{@link OH_ImagePackerNative_Release}释放。Packer不会接管输入ImageSource、
 * PixelMap、Picture或编码参数对象的生命周期。
 * 
 * @param imagePacker 被操作的OH_ImagePackerNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @release image_packer_native/OH_ImagePackerNative_Release {imagePacker}
 * @since 12
 */
Image_ErrorCode OH_ImagePackerNative_Create(OH_ImagePackerNative **imagePacker);

/**
 * @brief 将ImageSource编码为指定格式的数据。
 * <br>使用场景：适用于将已有ImageSource转码为另一种图片格式，或在修改图片属性后重新输出为内存数据。
 * <br>使用约束：imagePacker、options、imageSource、outData和size均不能为空指针。调用前，*size应设置为outData的容量。接口返回失败时，不应使用outData中的内容或size输出值。
 * <br>资源管理：outData由调用方申请和释放。调用前，*size应设置为outData可写缓冲区大小。调用成功后，*size会更新为实际写入的编码数据长度。imagePacker、
 * options和imageSource的生命周期仍由调用方管理，本接口不会释放这些对象。
 * 
 * @param imagePacker 被操作的OH_ImagePackerNative指针。
 * @param options 编码选项参数。
 * @param imageSource 用于编码的image source指针。
 * @param outData 用于存储打包图像输出数据的缓冲区。
 * @param size 用于存储打包图像输出数据的缓冲区大小。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_DECODE_FAILED：解码失败。
 *     <br>IMAGE_ALLOC_FAILED：申请内存失败。
 *     <br>IMAGE_TOO_LARGE：数据或图片过大。
 *     <br>IMAGE_UNKNOWN_ERROR：未知错误。
 * @since 12
 */
Image_ErrorCode OH_ImagePackerNative_PackToDataFromImageSource(OH_ImagePackerNative *imagePacker,
    OH_PackingOptions *options, OH_ImageSourceNative *imageSource, uint8_t *outData, size_t *size);

/**
 * @brief 将Pixelmap编码为指定格式的数据。
 * <br>使用场景：适用于将解码、编辑、绘制或算法处理后的PixelMap编码为JPEG、PNG、WebP等格式的内存数据，以便上传、缓存或继续写入文件。
 * <br>使用约束：imagePacker、options、pixelmap、outData和size均不能为空指针。调用前，*size应设置为outData的容量；接口返回失败时，不应使用outData中的内容或size输出值。
 * <br>资源管理：outData由调用方申请和释放。调用前，*size应设置为outData可写缓冲区大小。调用成功后，*size会更新为实际写入的编码数据长度。imagePacker、
 * options和pixelmap的生命周期仍由调用方管理，本接口不会释放这些对象。
 * 
 * @param imagePacker 被操作的OH_ImagePackerNative指针。
 * @param options 编码选项参数。
 * @param pixelmap 用于编码的Pixelmap指针。
 * @param outData 用于存储打包图像输出数据的缓冲区。
 * @param size 用于存储打包图像输出数据的缓冲区大小。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_DECODE_FAILED：解码失败。
 *     <br>IMAGE_ALLOC_FAILED：申请内存失败。
 *     <br>IMAGE_TOO_LARGE：数据或图片过大。
 *     <br>IMAGE_UNKNOWN_ERROR：未知错误。
 * @since 12
 */
Image_ErrorCode OH_ImagePackerNative_PackToDataFromPixelmap(OH_ImagePackerNative *imagePacker,
    OH_PackingOptions *options, OH_PixelmapNative *pixelmap, uint8_t *outData, size_t *size);

/**
 * @brief 将Picture编码为指定格式的数据。
 * <br>使用约束：imagePacker、options、picture、outData和size均不能为空指针。调用前，*size应设置为outData的容量。接口返回失败时，不应使用outData中的内容或size输出值。
 * <br>资源管理：outData由调用方申请和释放。调用前，*size应设置为outData可写缓冲区大小。调用成功后，*size会更新为实际写入的编码数据长度。imagePacker、
 * options和picture的生命周期仍由调用方管理，本接口不会释放这些对象。
 * 
 * @param imagePacker 被操作的OH_ImagePackerNative指针。
 * @param options 编码选项参数。
 * @param picture 用于编码的Picture指针。
 * @param outData 用于存储打包图像输出数据的缓冲区。
 * @param size 用于存储打包图像输出数据的缓冲区大小。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_DECODE_FAILED：解码失败。
 * @since 13
 */
Image_ErrorCode OH_ImagePackerNative_PackToDataFromPicture(OH_ImagePackerNative *imagePacker,
    OH_PackingOptions *options, OH_PictureNative *picture, uint8_t *outData, size_t *size);

/**
 * @brief 将Pixelmap序列编码为数据。
 * <br>使用场景：适用于将多帧PixelMap编码为动图或其他支持序列帧的图片格式。编码前应通过OH_PackingOptionsForSequence设置帧数、延迟时间、循环次数等参数。
 * <br>使用约束：接口返回失败时，不应使用outData中的内容或outDataSize输出值。
 * <br>资源管理：outData由调用方申请和释放。imagePacker、options和pixelmapSequence中PixelMap对象的生命周期仍由调用方管理，本接口不会释放这些对象。
 * 
 * @param imagePacker 被操作的OH_ImagePackerNative指针，不允许为NULL。
 * @param options 编码选项参数，不允许为NULL。frameCount必须大于0，需设置有效的delayTimeList，loopCount取值范围为[0, 65535]。
 *     delayTimeList中的每个延迟时间必须大于0且不超过65535，单位为10毫秒（ms）。disposalTypes中的每个取值必须小于等于3。
 * @param pixelmapSequence 用于编码的Pixelmap序列指针，不允许为NULL。数组中用于编码的Pixelmap指针不允许为NULL。
 * @param sequenceLength 用于编码的Pixelmap序列长度，必须大于0。
 * @param outData 用于存储编码后图像输出数据的缓冲区，不允许为NULL。
 * @param outDataSize 用于存储编码后图像输出数据缓冲区大小的指针，不允许为NULL。调用前，*outDataSize应设置为outData可写缓冲区大小；调用成功后，*
 *     outDataSize会更新为实际写入的编码数据长度。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_DECODE_FAILED：解码失败。
 * @since 18
 */
Image_ErrorCode OH_ImagePackerNative_PackToDataFromPixelmapSequence(OH_ImagePackerNative *imagePacker,
    OH_PackingOptionsForSequence *options, OH_PixelmapNative **pixelmapSequence,
    size_t sequenceLength, uint8_t *outData, size_t *outDataSize);

/**
 * @brief 将一个ImageSource编码到文件中。
 * <br>使用场景：适用于将ImageSource转码后直接写入文件描述符，避免调用方自行管理编码后的内存缓冲区。
 * <br>使用约束：imagePacker、options和imageSource均不能为空指针，fd必须为可写文件描述符。
 * <br>资源管理：fd必须是可写文件描述符，文件描述符的打开和关闭由调用方负责。接口不会释放imagePacker、options或imageSource。
 * 
 * @param imagePacker 被操作的OH_ImagePackerNative指针。
 * @param options 编码选项参数。
 * @param imageSource 用于编码的image source指针。
 * @param fd 可写的文件描述符。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_DECODE_FAILED：解码失败。
 *     <br>IMAGE_UNKNOWN_ERROR：未知错误。
 * @since 12
 */
Image_ErrorCode OH_ImagePackerNative_PackToFileFromImageSource(OH_ImagePackerNative *imagePacker,
    OH_PackingOptions *options, OH_ImageSourceNative *imageSource, int32_t fd);

/**
 * @brief 将一个Pixelmap编码到文件中。
 * <br>使用场景：适用于将处理后的PixelMap直接保存为文件。与PackToDataFromPixelmap相比，该接口不需要调用方预先分配输出数据缓冲区。
 * <br>使用约束：imagePacker、options和pixelmap均不能为空指针，fd必须为可写文件描述符。
 * <br>资源管理：fd必须是可写文件描述符，文件描述符的打开和关闭由调用方负责。接口不会释放imagePacker、options或pixelmap。
 * 
 * @param imagePacker 被操作的OH_ImagePackerNative指针。
 * @param options 编码选项参数。
 * @param pixelmap 用于编码的pixelmap指针。
 * @param fd 可写的文件描述符。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_DECODE_FAILED：解码失败。
 *     <br>IMAGE_UNKNOWN_ERROR：未知错误。
  * @since 12
 */
Image_ErrorCode OH_ImagePackerNative_PackToFileFromPixelmap(OH_ImagePackerNative *imagePacker,
    OH_PackingOptions *options, OH_PixelmapNative *pixelmap, int32_t fd);

/**
 * @brief 将一个Picture编码到文件中。
 * <br>使用约束：imagePacker、options和picture均不能为空指针，fd必须为可写文件描述符。
 * <br>资源管理：fd的打开和关闭由调用方负责。接口不会释放imagePacker、options或picture。
 * 
 * @param imagePacker 被操作的OH_ImagePackerNative指针。
 * @param options 编码选项参数。
 * @param picture 用于编码的picture指针。
 * @param fd 可写的文件描述符。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_DECODE_FAILED：解码失败。
 *     <br>IMAGE_UNKNOWN_ERROR：未知错误。
 * @since 13
 */
Image_ErrorCode OH_ImagePackerNative_PackToFileFromPicture(OH_ImagePackerNative *imagePacker,
    OH_PackingOptions *options, OH_PictureNative *picture, int32_t fd);

/**
 * @brief 将一个Pixelmap序列编码到文件中。
 * <br>使用约束：接口返回失败时，目标文件中的内容不应继续使用。
 * <br>资源管理：fd的打开和关闭由调用方负责。接口不会释放imagePacker、options或pixelmapSequence中的PixelMap对象。
 * 
 * @param imagePacker 被操作的OH_ImagePackerNative指针，不允许为NULL。
 * @param options 编码选项参数，不允许为NULL。frameCount必须大于0，需设置有效的delayTimeList，loopCount取值范围为[0, 65535]。
 *     delayTimeList中的每个延迟时间必须大于0且不超过65535。disposalTypes中的每个取值必须小于等于3。
 * @param pixelmapSequence 用于编码的Pixelmap序列指针，不允许为NULL。数组中用于编码的Pixelmap指针不允许为NULL。
 * @param sequenceLength 用于编码的Pixelmap序列长度，必须大于0。
 * @param fd 文件描述符，必须为可写文件描述符。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 *     <br>IMAGE_DECODE_FAILED：解码失败。
 * @since 18
 */
Image_ErrorCode OH_ImagePackerNative_PackToFileFromPixelmapSequence(OH_ImagePackerNative *imagePacker,
    OH_PackingOptionsForSequence *options, OH_PixelmapNative **pixelmapSequence, size_t sequenceLength, int32_t fd);

/**
 * @brief 释放OH_ImagePackerNative指针。
 * <br>使用约束：imagePacker不能为空指针。
 * <br>资源管理：由{@link OH_ImagePackerNative_Create}成功创建的对象，在使用完毕后必须调用本接口释放。释放Packer不会释放OH_PackingOptions、
 * OH_PackingOptionsForSequence、OH_ImageSourceNative、OH_PixelmapNative或OH_PictureNative对象。调用该接口后，
 * imagePacker指向的OH_ImagePackerNative对象会被释放，不应继续使用。
 * 
 * @param imagePacker 被操作的OH_ImagePackerNative指针。
 * @return IMAGE_SUCCESS：执行成功。
 *     <br>IMAGE_BAD_PARAMETER：参数错误。
 * @since 12
 */
Image_ErrorCode OH_ImagePackerNative_Release(OH_ImagePackerNative *imagePacker);

/**
 * @brief 获取支持编码的图片格式。
 * <br>使用场景：适用于在编码前动态查询当前系统支持的目标格式，并据此设置{@link OH_PackingOptions_SetMimeType}的MIME类型。
 * <br>使用约束：supportedFormats和length均不能为空指针。接口返回失败时，输出参数内容不应使用。
 * <br>资源管理：接口成功返回的supportedFormats数组由系统内部管理，调用方不需要也不应释放或修改。如需长期保存，应自行拷贝数组内容。
 * 
 * @param supportedFormats 支持编码的图片格式。
 * @param length 数组长度。
 * @return IMAGE_SUCCESS：操作成功。
 *     <br>IMAGE_PACKER_INVALID_PARAMETER：参数异常，supportedFormats或length为空。
 * @since 20
 */
Image_ErrorCode OH_ImagePackerNative_GetSupportedFormats(Image_MimeType** supportedFormats, size_t* length);

#ifdef __cplusplus
};
#endif
/** @} */
#endif // INTERFACES_KITS_NATIVE_INCLUDE_IMAGE_IMAGE_PACKER_NATIVE_H_

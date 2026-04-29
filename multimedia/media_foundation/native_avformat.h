
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
 * @addtogroup Core
 * @{
 *
 * @brief The Core module provides basic backbone capabilities for media frameworks,
 * including functions such as memory, error codes, and media data structures.
 *
 * @since 9
 */
/**
 * @file native_avformat.h
 *
 * @brief The file declares the functions and enums related to OH_AVFormat.
 *
 * @kit AVCodecKit
 * @library libnative_media_core.so
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 */

#ifndef NATIVE_AVFORMAT_H
#define NATIVE_AVFORMAT_H
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Describes a native object for the OH_AVFormat interface.
 *
 * @since 9
 */
typedef struct OH_AVFormat OH_AVFormat;

/**
 * @brief Enumerates the video pixel formats.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_AVPixelFormat {
    /**
     * YUV 420 Planar.
     * @since 9
     */
    AV_PIXEL_FORMAT_YUVI420 = 1,
    /**
     * NV12. YUV 420 semi-planar.
     * @since 9
     */
    AV_PIXEL_FORMAT_NV12 = 2,
    /**
     * NV21. YVU 420 semi-planar.
     * @since 9
     */
    AV_PIXEL_FORMAT_NV21 = 3,
    /**
     * Pixel format obtained from the surface. This value takes effect only in surface mode.
     * @since 9
     */
    AV_PIXEL_FORMAT_SURFACE_FORMAT = 4,
    /**
     * RGBA8888
     * @since 9
     */
    AV_PIXEL_FORMAT_RGBA = 5,
    /**
     * RGBA1010102
     * @since 20
     */
    AV_PIXEL_FORMAT_RGBA1010102 = 6
} OH_AVPixelFormat;

/**
 * @brief Create an OH_AVFormat handle pointer to read and write data
 *
 * @return Pointer to an OH_AVFormat instance. If system resources are insufficient, NULL is returned.
 * @since 9
 * @version 1.0
 */
struct OH_AVFormat *OH_AVFormat_Create(void);

/**
 * @brief Create an audio OH_AVFormat handle pointer to read and write data
 *
 * @param mimeType Pointer to a string that describes the MIME type. For details, see {@link AVCODEC_MIMETYPE}.
 * @param sampleRate Sampling rate, in Hz.
 * @param channelCount Number of audio channels. For example, 1 indicates mono and 2 indicates stereo.
 * @return Pointer to the OH_AVFormat instance created. If the operation fails, NULL is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **mimeType** is NULL.
 *     <br>2. System resources are insufficient.
 * @since 10
 * @version 1.0
 */
struct OH_AVFormat *OH_AVFormat_CreateAudioFormat(const char *mimeType,
                                                  int32_t sampleRate,
                                                  int32_t channelCount);

/**
 * @brief Create a video OH_AVFormat handle pointer to read and write data
 *
 * @param mimeType Pointer to a string that describes the MIME type. For details, see {@link AVCODEC_MIMETYPE}.
 * @param width Image width, in pixels.
 * @param height Image height, in pixels.
 * @return Pointer to the OH_AVFormat instance created. If the operation fails, NULL is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **mimeType** is NULL.
 *     <br>2. System resources are insufficient.
 * @since 10
 * @version 1.0
 */
struct OH_AVFormat *OH_AVFormat_CreateVideoFormat(const char *mimeType,
                                                  int32_t width,
                                                  int32_t height);

/**
 * @brief Destroys an OH_AVFormat instance. The instance cannot be destroyed repeatedly.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @return void
 * @since 9
 * @version 1.0
 */
void OH_AVFormat_Destroy(struct OH_AVFormat *format);

/**
 * @brief Copies an OH_AVFormat instance.
 *
 * @param to Pointer to the OH_AVFormat instance to which the data will be copied.
 * @param from Pointer to the OH_AVFormat instance from which the data will be copied.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The input parameter is nullptr.
 *     <br>2. The value of **OH_AVFormat** fails parameter structure verification.
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_Copy(struct OH_AVFormat *to, struct OH_AVFormat *from);

/**
 * @brief Assigns a value of the int type to a {@link key} in an OH_AVFormat instance. This function can be used to set
 * only parameters of the int type. For details, see {@link native_avcodec_base.h}.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to write.
 * @param value Value of the data to write.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value type corresponding to the key is incorrect.
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_SetIntValue(struct OH_AVFormat *format, const char *key, int32_t value);

/**
 * @brief Assigns an unsigned int value to the key of an OH_AVFormat instance. This API can be used to set only
 * parameters of the unsigned int type. For details, see {@link native_avcodec_base.h}.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to write.
 * @param value Value of the data to write.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 * @since 23
 */
bool OH_AVFormat_SetUintValue(struct OH_AVFormat *format, const char *key, uint32_t value);

/**
 * @brief Assigns a value of the long type to a {@link key} in an OH_AVFormat instance. This function can be used to
 * set only parameters of the long type. For details, see {@link native_avcodec_base.h}.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to write.
 * @param value Value of the data to write.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value type corresponding to the key is incorrect.
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_SetLongValue(struct OH_AVFormat *format, const char *key, int64_t value);

/**
 * @brief Assigns a value of the float type to a {@link key} in an OH_AVFormat instance. This function can be used to
 * set only parameters of the float type. For details, see {@link native_avcodec_base.h}.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to write.
 * @param value Value of the data to write.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value type corresponding to the key is incorrect.
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_SetFloatValue(struct OH_AVFormat *format, const char *key, float value);

/**
 * @brief Assigns a value of the double type to a {@link key} in an OH_AVFormat instance. This function can be used to
 * set only parameters of the double type. For details, see {@link native_avcodec_base.h}.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to write.
 * @param value Value of the data to write.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value type corresponding to the key is incorrect.
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_SetDoubleValue(struct OH_AVFormat *format, const char *key, double value);

/**
 * @brief Assigns a value of the string type to a {@link key} in an OH_AVFormat instance. This function can be used to
 * set only parameters of the string type. For details, see {@link native_avcodec_base.h}.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to write.
 * @param value Pointer to the data to be written to the string. The length should not exceed 256 bytes.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The passed-in value of **value** is a null pointer.
 *     <br>5. The value type corresponding to the key is incorrect.
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_SetStringValue(struct OH_AVFormat *format, const char *key, const char *value);

/**
 * @brief Writes data blocks of a specified length to an OH_AVFormat instance. This function can be used to set only
 * parameters of the buffer type. For details, see {@link native_avcodec_base.h}.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to write.
 * @param addr Pointer to the address to which data is written. The lifecycle is managed by the developer.
 * @param size Length of the data written, in MB. The value range is (0, 1].
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value of **addr** is nullptr.
 *     <br>5. The size is 0 or exceeds the upper limit 1 MB.
 *     <br>6. The value type corresponding to the key is incorrect.
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_SetBuffer(struct OH_AVFormat *format, const char *key, const uint8_t *addr, size_t size);

/**
 * @brief Obtains the value of the int type of a {@link key} in an OH_AVFormat instance.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to read.
 * @param out Pointer to the value of the data read.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value of **out** is nullptr.
 *     <br>5. The obtained key does not exist or is not set.
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_GetIntValue(struct OH_AVFormat *format, const char *key, int32_t *out);

/**
 * @brief Obtains the value of the unsigned int type from an OH_AVFormat instance using a key.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to read.
 * @param out Pointer to the value of the data read.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value of **out** is nullptr.
 * @since 23
 */
bool OH_AVFormat_GetUintValue(struct OH_AVFormat *format, const char *key, uint32_t *out);

/**
 * @brief Obtains the value of the long type of a {@link key} in an OH_AVFormat instance.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to read.
 * @param out Pointer to the value of the data read.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value of **out** is nullptr.
 *     <br>5. The obtained key does not exist or is not set.
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_GetLongValue(struct OH_AVFormat *format, const char *key, int64_t *out);

/**
 * @brief Obtains the value of the float type of a {@link key} in an OH_AVFormat instance.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to read.
 * @param out Pointer to the value of the data read.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value of **out** is nullptr.
 *     <br>5. The obtained key does not exist or is not set.
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_GetFloatValue(struct OH_AVFormat *format, const char *key, float *out);

/**
 * @brief Obtains the value of the double type of a {@link key} in an OH_AVFormat instance.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to read.
 * @param out Pointer to the value of the data read.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value of **out** is nullptr.
 *     <br>5. The obtained key does not exist or is not set.
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_GetDoubleValue(struct OH_AVFormat *format, const char *key, double *out);

/**
 * @brief Obtains the value of the string type of a {@link key} in an OH_AVFormat instance.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to read.
 * @param out Double pointer to the string read. The lifecycle of the **out** data matches the string in **format**. To
 *     keep the **out** data for an extended period of time, you must copy it to the memory. The maximum length of the
 *     output string is 256 bytes. If the length exceeds 256 bytes, **false** is returned.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value of **out** is nullptr.
 *     <br>5. The system resources are insufficient.
 *     <br>6. The obtained key does not exist or is not set.
 *     <br>7. The length of the **out** data exceeds 256 bytes.
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_GetStringValue(struct OH_AVFormat *format, const char *key, const char **out);

/**
 * @brief Reads data blocks of a specified length from an OH_AVFormat instance.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to read.
 * @param addr Double pointer to the address where the data read is stored. The data read is destroyed when the
 *     OH_AVFormat instance is destroyed. To hold the data for an extended period of time, copy it to the memory.
 * @param size Pointer to the size of the data read.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value of **addr** is nullptr.
 *     <br>5. The value of **size** is nullptr.
 *     <br>6. The obtained key does not exist or is not set.
 * @since 9
 * @version 1.0
 */
bool OH_AVFormat_GetBuffer(struct OH_AVFormat *format, const char *key, uint8_t **addr, size_t *size);

/**
 * @brief Returns a string consisting of key-value pairs in an OH_AVFormat instance. A string of up to 1024 bytes can
 * be returned. The string pointer is released when the OH_AVFormat instance is destroyed.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @return A string consisting of key-value pairs. If the operation fails, NULL is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1.  The value of **format** is NULL.
 *     <br>2. System resources are insufficient.
 * @since 9
 * @version 1.0
 */
const char *OH_AVFormat_DumpInfo(struct OH_AVFormat *format);

/**
 * @brief Reads an array of int32_t data from an OH_AVFormat instance.
 *
 * Note that the buffer lifecycle is bound to the OH_AVFormat instance. The buffer becomes invalid automatically when
 * the OH_AVFormat instance is destroyed.
 *
 * To keep the data for an extended period, explicitly copy the data to newly allocated memory.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to read.
 * @param addr Double pointer to the memory where the data is stored.
 * @param size Pointer to the number of elements read.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value of **addr** is nullptr.
 *     <br>5. The value of **size** is nullptr.
 * @since 20
 */
bool OH_AVFormat_GetIntBuffer(struct OH_AVFormat *format, const char *key, int32_t **addr, size_t *size);

/**
 * @brief Writes data blocks of the int32_t type with a specified length to an OH_AVFormat instance.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param key Pointer to the key of the data to write.
 * @param addr Pointer to the address to which data is written. The lifecycle is managed by the developer.
 * @param size Length of the data to write, in units of elements, not bytes.
 * @return **true** if the operation is successful; **false** otherwise.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **format** is nullptr.
 *     <br>2. The value of **format** fails parameter structure verification.
 *     <br>3. The value of **key** is nullptr.
 *     <br>4. The value of **addr** is nullptr.
 *     <br>5. The value of **size** is **0**.
 * @since 20
 */
bool OH_AVFormat_SetIntBuffer(struct OH_AVFormat *format, const char *key, const int32_t *addr, size_t size);

/**
 * @brief Obtains the total number of keys in an OH_AVFormat instance.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @return Returns the number of keys on success; returns **0** otherwise.
 * @since 23
 */
uint32_t OH_AVFormat_GetKeyCount(OH_AVFormat *format);

/**
 * @brief Obtains the key name string from an OH_AVFormat instance by index.
 *
 * @param format Pointer to an OH_AVFormat instance.
 * @param index Index of the key to be queried. The value range is [0, OH_AVFormat_GetKeyCount(format)).
 * @param key Output pointer for receiving the key name string. The lifecycle of the string is bound to the **format**
 *     object.
 * @return Returns **true** on success; returns **false** otherwise.
 * @since 23
 */
bool OH_AVFormat_GetKey(OH_AVFormat *format, uint32_t index, const char **key);
#ifdef __cplusplus
}
#endif
#endif // NATIVE_AVFORMAT_H
/** @} */
/*
* Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup RDB
 * @{
 *
 * @brief 分布式数据管理（Distributed Data Manager，data）支持单设备的各种结构化数据的持久化，以及端云间的同步、共享功能。
 * 分布式数据管理定义了一系列数据类型，可以对数据进行增删改查。
 *
 * @since 10
 */

/**
 * @file oh_value_object.h
 *
 * @include database/rdb/oh_value_object.h
 * @brief 提供类型转换方法。
 *
 * @kit ArkData
 * @library libnative_rdb_ndk.z.so
 * @syscap SystemCapability.DistributedDataManager.RelationalStore.Core
 * @since 10
 */

#ifndef OH_VALUE_OBJECT_ZH_CN_H
#define OH_VALUE_OBJECT_ZH_CN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 表示允许的数据字段类型。
 *
 * @since 10
 */
typedef struct OH_VObject OH_VObject;


/**
 * @brief 表示允许的数据字段类型。
 *
 * @since 10
 */
typedef struct OH_VObject {
    /**
     * OH_VObject结构体的唯一标识符。
     */
    int64_t id;

    /**
     * @brief 将int64类型的单个参数或者数组转换为OH_VObject类型的值。
     *
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @param value 表示指向int64_t类型输入参数或int64_t类型数组的指针。
     * @param count 如果value是指向单个数值的指针，则count = 1；如果value是指向数组的指针，则count是数组的长度。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_VObject.
     * @since 10
     */
    int (*putInt64)(OH_VObject *valueObject, int64_t *value, uint32_t count);

    /**
     * @brief 将double类型的单个参数或者数组转换为OH_VObject类型的值。
     *
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @param value 表示指向double类型输入参数或double类型数组的指针。
     * @param count 如果value是指向单个数值的指针，则count = 1；如果value是指向数组的指针，则count是数组的长度。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_VObject.
     * @since 10
     */
    int (*putDouble)(OH_VObject *valueObject, double *value, uint32_t count);

    /**
     * @brief 将char *类型的字符数组转换为OH_VObject类型的值。
     *
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @param value 表示const char *类型的输入参数。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_VObject.
     * @since 10
     */
    int (*putText)(OH_VObject *valueObject, const char *value);

    /**
     * @brief 将char *类型的字符串数组转换为OH_VObject类型的值。
     *
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @param value 表示const char *数组类型的输入参数。
     * @param count 表示字符串数组参数value的长度。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_VObject.
     * @since 10
     */
    int (*putTexts)(OH_VObject *valueObject, const char **value, uint32_t count);

    /**
     * @brief 销毁OH_VObject对象，并回收该对象占用的内存。
     *
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_VObject.
     * @since 10
     */
    int (*destroy)(OH_VObject *valueObject);
};

#ifdef __cplusplus
};
#endif

/** @} */

#endif // OH_VALUE_OBJECT_ZH_CN_H

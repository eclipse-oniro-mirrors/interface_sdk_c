/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
 * @addtogroup NeuralNetworkRuntime
 * @{
 *
 * @brief 提供Neural Network Runtime加速模型推理的相关接口。
 *
 * @since 9
 * @version 2.0
 */

/**
 * @file neural_network_core.h
 *
 * @brief Neural Network Core模块接口定义，AI推理框架使用Neural Network Core提供的Native接口，
 * 完成模型编译，并在加速硬件上执行推理和计算。\n
 * 部分接口定义从neural_network_runtime.h移动至此头文件统一呈现，对于此类接口，
 * API version 11 版本之前即支持使用，各版本均可正常使用。
 * Neural Network Core的接口目前均不支持多线程并发调用。
 *
 * include "neural_network_runtime/neural_network_core.h"
 * @library libneural_network_core.so
 * @kit NeuralNetworkRuntimeKit
 * @syscap SystemCapability.AI.NeuralNetworkRuntime
 * @since 11
 * @version 1.0
 */

#ifndef NEURAL_NETWORK_CORE_H
#define NEURAL_NETWORK_CORE_H

#include "neural_network_runtime_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建{@link OH_NNCompilation}类型的编译实例。\n
 *
 * 使用OH_NNModel模块完成模型的构造后，借助OH_NNCompilation模块提供的接口，将模型传递到底层硬件完成编译。\n
 * 该接口接受一个{@link OH_NNModel}实例，创建出{@link OH_NNCompilation}实例；通过{@link OH_NNCompilation_SetDevice}接口，
 * 设置编译的设备，最后调用{@link OH_NNCompilation_Build}完成编译。\n
 * 除了计算硬件的选择，OH_NNCompilation模块支持模型缓存、性能偏好、优先级设置、float16计算等特性，参考以下接口：\n
 * {@link OH_NNCompilation_SetCache} \n
 * {@link OH_NNCompilation_SetPerformanceMode} \n
 * {@link OH_NNCompilation_SetPriority} \n
 * {@link OH_NNCompilation_EnableFloat16} \n
 *
 * 调用该接口创建{@link OH_NNCompilation}后，{@link OH_NNModel}实例就可以释放了。
 *
 * @param model 指向{@link OH_NNModel}实例的指针。
 * @return 指向{@link OH_NNCompilation}实例的指针，如果创建失败就返回NULL。
 * @since 9
 * @version 1.0
 */
OH_NNCompilation *OH_NNCompilation_Construct(const OH_NNModel *model);

/**
 * @brief 基于离线模型文件创建编译实例。\n
 *
 * 该接口与传递在线构建模型或离线模型文件内存的方式冲突，您只能选择三种构建接口中的一种。\n
 *
 * 离线模型是由硬件供应商提供的模型转换器离线编译的模型类型，所以离线模型只能在指定的设备上使用，
 * 但离线模型的编译时间通常远小于构图实例{@link OH_NNModel}的编译时间。\n
 *
 * 在开发过程中需要离线执行编译，并在应用包中部署离线模型。\n
 *
 * @param modelPath 离线模型文件路径。
 * @return 指向{@link OH_NNCompilation}实例的指针，如果创建失败就返回NULL。
 * @since 11
 * @version 1.0
 */
OH_NNCompilation *OH_NNCompilation_ConstructWithOfflineModelFile(const char *modelPath);

/**
 * @brief 基于离线模型文件内存创建编译实例。\n
 *
 * 该接口与传递在线构建模型或离线模型文件路径的方式冲突，您只能选择三种构建接口中的一种。\n
 *
 * 返回的{@link OH_NNCompilation}实例只将modelBuffer指针保存在里面，而不是复制其数据。
 * 在销毁{@link OH_NNCompilation}实例之前，不应释放modelBuffer。
 *
 * @param modelBuffer 离线模型文件内存。
 * @param modelSize 离线模型内存大小。
 * @return 指向{@link OH_NNCompilation}实例的指针，如果创建失败就返回NULL。
 * @since 11
 * @version 1.0
 */
OH_NNCompilation *OH_NNCompilation_ConstructWithOfflineModelBuffer(const void *modelBuffer, size_t modelSize);

/**
 * @brief 创建一个空的编译实例，以便稍后从模型缓存中恢复。\n
 *
 * 模型缓存的相关描述参考{@link OH_NNCompilation_SetCache}。\n
 *
 * 从模型缓存恢复的时间少于使用{@link OH_NNModel}进行编译的时间。\n
 *
 * 应该先调用{@link OH_NNCompilation_SetCache}或{@link OH_NNCompilation_ImportCacheFromBuffer}，
 * 然后调用{@link OH_NNCompilation_Build}完成恢复。
 *
 * @return 指向{@link OH_NNCompilation}实例的指针，如果创建失败就返回NULL。
 * @since 11
 * @version 1.0
 */
OH_NNCompilation *OH_NNCompilation_ConstructForCache();

/**
 * @brief 将模型缓存写入到指定内存区域。\n
 *
 * 模型缓存的相关描述参考{@link OH_NNCompilation_SetCache}。\n
 *
 * 模型缓存是编译构建的结果{@link OH_NNCompilation_Build}，因此必须在{@link OH_NNCompilation_Build}之后调用该接口。
 *
 * @param compilation 指向{@link OH_NNCompilation}实例的指针。
 * @param buffer 指向给定内存的指针。
 * @param length 内存长度。
 * @param modelSize 模型缓存的字节大小。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNCompilation_ExportCacheToBuffer(OH_NNCompilation *compilation,
                                                      const void *buffer,
                                                      size_t length,
                                                      size_t *modelSize);

/**
 * @brief 从指定内存区域读取模型缓存。\n
 *
 * 模型缓存的相关描述参考{@link OH_NNCompilation_SetCache}。\n
 *
 * 调用{@link OH_NNCompilation_ImportCacheFromBuffer}后，应调用{@link OH_NNCompilation_Build}完成恢复。\n
 *
 * compilation只将buffer指针保存在里面，而不是复制其数据。您不能在compilation被销毁之前释放内存buffer。
 *
 * @param compilation 指向{@link OH_NNCompilation}实例的指针。
 * @param buffer 指向给定内存的指针。
 * @param modelSize 模型缓存的字节大小。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNCompilation_ImportCacheFromBuffer(OH_NNCompilation *compilation,
                                                        const void *buffer,
                                                        size_t modelSize);

/**
 * @brief 为自定义硬件属性添加扩展配置。\n
 *
 * 某些设备有自己的特定属性，这些属性尚未在NNRt中打开。该接口为您提供了另一种方式设置设备的这些自定义硬件属性。\n
 * 您应该从设备供应商的文档查询它们的名称和值，并将它们逐一添加到编译实例中。这些属性将直接传递给设备驱动程序，
 * 如果驱动程序无法解析它们，该接口将返回错误码。\n
 *
 * 调用{@link OH_NNCompilation_Build}后，configName和configValue就可以释放了。
 *
 * @param compilation 指向{@link OH_NNCompilation}实例的指针。
 * @param configName 配置名称。
 * @param configValue 保存配置值的地址。
 * @param configValueSize 配置值的字节大小。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNCompilation_AddExtensionConfig(OH_NNCompilation *compilation,
                                                     const char *configName,
                                                     const void *configValue,
                                                     const size_t configValueSize);

/**
 * @brief 指定模型编译和计算的硬件。\n
 *
 * 编译阶段，需要指定模型编译和执行计算的硬件设备。先调用{@link OH_NNDevice_GetAllDevicesID}获取可用的设备ID，
 * 通过{@link OH_NNDevice_GetType}和{@link OH_NNDevice_GetType}获取设备信息后，将期望编译执行的设备ID传入该接口进行设置。
 *
 * @param compilation 指向{@link OH_NNCompilation}实例的指针。
 * @param deviceID 指定的硬件ID。如果为0，则默认使用当前设备列表中的第1台设备。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 9
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNCompilation_SetDevice(OH_NNCompilation *compilation, size_t deviceID);

/**
 * @brief 设置编译模型的缓存目录和版本。\n
 *
 * 在支持模型缓存的硬件上，模型在硬件驱动层编译后可以保存为模型缓存文件，下次编译时直接从模型缓存文件读取模型，
 * 减少重新编译的耗时。\n
 * 该接口接受模型缓存路径和版本，根据缓存路径中和版本的不同情况，该接口采取不同的行为：\n
 *
 * - 模型缓存路径指定的目录下没有文件：\n
 * 将编译后的模型缓存到目录下，设置缓存版本等于version。\n
 *
 * - 模型缓存路径指定的目录下存在完整的缓存文件，且版本号 == version：\n
 * 读取路径下的缓存文件，传递到底层硬件中转换为可以执行的模型实例。\n
 *
 * - 模型缓存路径指定的目录下存在完整的缓存文件，但版本号 < version：\n
 * 路径下的缓存文件需要更新，模型在底层硬件完成编译后，覆写路径下的缓存文件，将版本号更新为version。\n
 *
 * - 模型缓存路径指定的目录下存在完整的缓存文件，但版本号 > version：\n
 * 路径下的缓存文件版本高于version，不读取缓存文件，同时返回{@link OH_NN_INVALID_PARAMETER}错误码。\n
 *
 * - 模型缓存路径指定的目录下的缓存文件不完整或没有缓存文件的访问权限：\n
 * 返回{@link OH_NN_INVALID_FILE}错误码。\n
 *
 * - 模型缓存目录不存在，或者没有访问权限：\n
 * 返回{@link OH_NN_INVALID_PATH}错误码。
 *
 * @param compilation 指向{@link OH_NNCompilation}实例的指针。
 * @param cachePath 模型缓存文件目录，该接口在cachePath目录下为不同的硬件创建模型缓存目录。建议每个模型使用单独的模型缓存目录。
 * @param version 模型缓存版本。
 * @return  函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 9
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNCompilation_SetCache(OH_NNCompilation *compilation, const char *cachePath, uint32_t version);

/**
 * @brief 设置模型计算的性能模式。\n
 *
 * Neural Network Runtime 支持为模型计算设置性能模式，满足低功耗到极致性能的需求。如果编译阶段没有调用该接口设置性能模式，
 * 编译实例为模型默认分配{@link OH_NN_PERFORMANCE_NONE}模式。在{@link OH_NN_PERFORMANCE_NONE}模式下，
 * 硬件按默认的性能模式执行计算。\n
 *
 * 在不支持性能模式设置的硬件上调用该接口，将返回{@link OH_NN_UNAVAILABLE_DEVICE}错误码。
 *
 * @param compilation 指向{@link OH_NNCompilation}实例的指针。
 * @param performanceMode 指定性能模式，可选的性能模式参考{@link OH_NN_PerformanceMode}。
 * @return  函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 9
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNCompilation_SetPerformanceMode(OH_NNCompilation *compilation,
                                                     OH_NN_PerformanceMode performanceMode);

/**
 * @brief 设置模型计算的优先级。\n
 *
 * Neural Network Runtime 支持为模型设置计算优先级，优先级仅作用于相同uid进程创建的模型，
 * 不同uid进程、不同设备的优先级不会相互影响。\n
 *
 * 在不支持优先级设置的硬件上调用该接口，将返回{@link OH_NN_UNAVAILABLE_DEVICE}错误码。
 *
 * @param compilation 指向{@link OH_NNCompilation}实例的指针。
 * @param priority 指定优先级，可选的优先级参考{@link OH_NN_Priority}。
 * @return  函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 9
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNCompilation_SetPriority(OH_NNCompilation *compilation, OH_NN_Priority priority);

/**
 * @brief 是否以float16的浮点数精度计算。\n
 *
 * 浮点模型默认使用float32精度计算。如果在支持float16精度的硬件上调用该接口，float32浮点数精度的模型将以float16的精度执行计算，
 * 可减少内存占用和执行时间。\n
 *
 * 该选项对于定点模型是无效的，例如int8类型的定点模型。\n
 *
 * 在不支持float16精度计算的硬件上调用该接口，将返回{@link OH_NN_UNAVAILABLE_DEVICE}错误码。
 *
 * @param compilation 指向{@link OH_NNCompilation}实例的指针。
 * @param enableFloat16 Float16低精度计算标志位。设置为true时，执行Float16推理；设置为false时，执行float32推理。
 * @return  函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 9
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNCompilation_EnableFloat16(OH_NNCompilation *compilation, bool enableFloat16);

/**
 * @brief 执行模型编译。\n
 *
 * 完成编译配置后，调用该接口执行模型编译。编译实例将模型和编译选项推送至硬件设备进行编译。\n
 * 在调用该接口后，无法进行额外的编译操作，调用{@link OH_NNCompilation_SetDevice}、{@link OH_NNCompilation_SetCache}、
 * {@link OH_NNCompilation_SetPerformanceMode}、{@link OH_NNCompilation_SetPriority}和
 * {@link OH_NNCompilation_EnableFloat16}接口将返回{@link OH_NN_OPERATION_FORBIDDEN}。
 *
 * @param compilation 指向{@link OH_NNCompilation}实例的指针。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 9
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNCompilation_Build(OH_NNCompilation *compilation);

/**
 * @brief 销毁Compilation实例。\n
 *
 * 调用{@link OH_NNCompilation_Construct}、{@link OH_NNCompilation_ConstructWithOfflineModelFile}、
 * {@link OH_NNCompilation_ConstructWithOfflineModelBuffer}、{@link OH_NNCompilation_ConstructForCache}创建的编译实例
 * 需要调用该接口主动销毁。\n
 *
 * 如果compilation为空指针或者*compilation为空指针，该接口仅打印警告日志，不执行销毁操作。
 *
 * @param compilation 指向{@link OH_NNCompilation}实例的二级指针。编译实例销毁后，该接口将*compilation主动设置为空指针。
 * @since 9
 * @version 1.0
 */
void OH_NNCompilation_Destroy(OH_NNCompilation **compilation);

/**
 * @brief 创建一个{@link NN_TensorDesc}实例。\n
 *
 * {@link NN_TensorDesc}描述了各种张量属性，如名称/数据类型/形状/格式等。 \n
 *
 * 可以调用以下接口，基于传入的{@link NN_TensorDesc}实例创建{@link NN_Tensor}实例：\n
 * {@link OH_NNTensor_Create} \n
 * {@link OH_NNTensor_CreateWithSize} \n
 * {@link OH_NNTensor_CreateWithFd} \n
 *
 * 该接口会将{@link NN_TensorDesc}实例复制到{@link NN_Tensor}中，因此您可以创建多个{@link NN_Tensor}个实例，
 * 并持有相同的{@link NN_TensorDesc}实例。 \n
 *
 * 当{@link NN_TensorDesc}实例不再使用时，您应该调用{@link OH_NNTensorDesc_Destroy}接口销毁它。
 *
 * @return 指向{@link NN_TensorDesc}实例的指针，如果创建失败就返回NULL。
 * @since 11
 * @version 1.0
 */
NN_TensorDesc *OH_NNTensorDesc_Create();

/**
 * @brief 释放一个{@link NN_TensorDesc}实例。\n
 *
 * 当{@link NN_TensorDesc}实例不再使用时，需要调用该接口销毁，否则将发生内存泄漏。\n
 *
 * 如果tensorDesc或*tensorDesc为空指针，则该接口将返回错误码，并且不会执行销毁操作。
 *
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的二级指针。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensorDesc_Destroy(NN_TensorDesc **tensorDesc);

/**
 * @brief 设置{@link NN_TensorDesc}的名称。\n
 *
 * {@link NN_TensorDesc}实例创建完成后，调用该接口设置张量的名称，*name的值是以'\0'结尾的C风格字符串。\n
 *
 * 如果tensorDesc或name为空指针，则该接口将返回错误码。
 *
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的指针。
 * @param name 需要设置的张量名称。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensorDesc_SetName(NN_TensorDesc *tensorDesc, const char *name);

/**
 * @brief 获取{@link NN_TensorDesc}的名称。\n
 *
 * 调用该接口获取指定{@link NN_TensorDesc}实例的名称，*name的值是以'\0'结尾的C风格字符串。\n
 *
 * 如果tensorDesc或name为空指针，则该接口将返回错误码。作为输出参数，*name必须为空指针，否则该接口将返回错误码。\n
 * 例如您应该定义char* tensorName = NULL，并传递&tensorName作为name的参数。\n
 *
 * 您不需要释放name的内存，当tensorDesc被销毁时，它会被自动释放。
 *
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的指针。
 * @param name 返回的张量名称。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensorDesc_GetName(const NN_TensorDesc *tensorDesc, const char **name);

/**
 * @brief 设置{@link NN_TensorDesc}的数据类型。\n
 *
 * {@link NN_TensorDesc}实例创建完成后，调用该接口设置张量数据类型。\n
 *
 * 如果tensorDesc为空指针，则该接口将返回错误码。
 *
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的指针。
 * @param dataType 需要设置的张量数据类型。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensorDesc_SetDataType(NN_TensorDesc *tensorDesc, OH_NN_DataType dataType);

/**
 * @brief 获取{@link NN_TensorDesc}的数据类型。\n
 *
 * 调用该接口获取指定{@link NN_TensorDesc}实例的数据类型。\n
 *
 * 如果tensorDesc或dataType为空指针，则该接口将返回错误码。
 *
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的指针。
 * @param dataType 指向返回的张量数据类型的指针，作为出参使用。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensorDesc_GetDataType(const NN_TensorDesc *tensorDesc, OH_NN_DataType *dataType);

/**
 * @brief 设置{@link NN_TensorDesc}的数据形状。\n
 *
 * {@link NN_TensorDesc}实例创建完成后，调用该接口设置张量形状。\n
 *
 * 如果tensorDesc或shape为空指针，或shapeLength为0，则该接口将返回错误码。
 *
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的指针。
 * @param shape 需要设置的张量形状列表。
 * @param shapeLength 需要设置的张量形状列表长度。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensorDesc_SetShape(NN_TensorDesc *tensorDesc, const int32_t *shape, size_t shapeLength);

/**
 * @brief 获取{@link NN_TensorDesc}的形状。\n
 *
 * 调用该接口获取指定{@link NN_TensorDesc}实例的形状。\n
 *
 * 如果tensorDesc、shape或shapeLength为空指针，则该接口将返回错误码。作为输出参数，*shape必须为空指针，
 * 否则该接口将返回错误码。\n
 * 例如您应该定义 int32_t* tensorShape = NULL，并传递&tensorShape作为shape的参数。\n
 *
 * 您不需要释放shape的内存。当tensorDesc被销毁时，它会自动释放。
 *
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的指针。
 * @param shape 返回的张量形状列表。
 * @param shapeLength 返回的形状列表长度。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensorDesc_GetShape(const NN_TensorDesc *tensorDesc, int32_t **shape, size_t *shapeLength);

/**
 * @brief 设置{@link NN_TensorDesc}的数据布局。\n
 *
 * {@link NN_TensorDesc}实例创建完成后，调用该接口设置张量的数据布局{@link OH_NN_Format}。\n
 *
 * 如果tensorDesc为空指针，则该接口将返回错误码。
 *
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的指针。
 * @param format 需要设置的张量数据布局。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensorDesc_SetFormat(NN_TensorDesc *tensorDesc, OH_NN_Format format);

/**
 * @brief 获取{@link NN_TensorDesc}的数据布局。\n
 *
 * 调用该接口获取指定{@link NN_TensorDesc}实例的数据布局{@link OH_NN_Format}。\n
 *
 * 如果tensorDesc或format为空指针，则该接口将返回错误码。
 *
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的指针。
 * @param format 返回的张量数据布局。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensorDesc_GetFormat(const NN_TensorDesc *tensorDesc, OH_NN_Format *format);

/**
 * @brief 获取{@link NN_TensorDesc}的元素个数。\n
 *
 * 调用该接口获取指定{@link NN_TensorDesc}实例的元素个数。如果需要获取张量数据的字节大小，
 * 请调用{@link OH_NNTensorDesc_GetByteSize}。\n
 *
 * 如果张量形状是动态可变的，则该接口将返回错误码，elementCount将为0。\n
 *
 * 如果tensorDesc或elementCount为空指针，则该接口将返回错误码。
 *
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的指针。
 * @param elementCount 张量返回的元素个数。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensorDesc_GetElementCount(const NN_TensorDesc *tensorDesc, size_t *elementCount);

/**
 * @brief 获取基于{@link NN_TensorDesc}的形状和数据类型计算的数据占用字节数。\n
 *
 * 调用该接口可基于{@link NN_TensorDesc}的形状和数据类型计算得到的数据占用字节数。\n
 *
 * 如果张量形状是动态可变的，该接口将返回错误码，byteSize将为0。\n
 *
 * 如果需要获取张量数据的元素个数，请调用{@link OH_NNTensorDesc_GetElementCount}。\n
 *
 * 如果tensorDesc或byteSize为空指针，则该接口将返回错误码。
 *
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的指针。
 * @param byteSize 返回的数据字节数。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensorDesc_GetByteSize(const NN_TensorDesc *tensorDesc, size_t *byteSize);

/**
 * @brief 从{@link NN_TensorDesc}创建一个{@link NN_Tensor}实例。\n
 *
 * 该接口使用{@link OH_NNTensorDesc_GetByteSize}计算张量数据的字节数，并为其分配设备内存。
 * 设备驱动将直接通过“零拷贝”方式获取张量数据。\n
 *
 * 该接口会将tensorDesc复制到{@link NN_Tensor}中，因此当tensorDesc不再使用时，
 * 您应该调用{@link OH_NNTensorDesc_Destroy}接口销毁它。\n
 *
 * 如果张量形状是动态的，该接口将返回错误码。\n
 *
 * deviceID表示所选设备。如果为0，则默认使用设备列表中的第1台设备。\n
 *
 * 必须提供tensorDesc，如果它是空指针，则返回错误码。\n
 *
 * 当{@link NN_Tensor}实例不再使用时，需要调用{@link OH_NNTensor_Destroy}销毁它。
 *
 * @param deviceID 设备 ID。如果为0，则默认使用当前设备列表中的第1台设备。
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的指针。
 * @return 指向{@link NN_Tensor}实例的指针，如果创建失败就返回NULL。
 * @since 11
 * @version 1.0
 */
NN_Tensor *OH_NNTensor_Create(size_t deviceID, NN_TensorDesc *tensorDesc);

/**
 * @brief 按照指定内存大小和{@link NN_TensorDesc}创建{@link NN_Tensor}实例。\n
 *
 * 该接口使用size作为张量数据的字节数，并为其分配设备内存。设备将直接通过“零拷贝”方式获取张量数据。\n
 *
 * 该接口会将tensorDesc复制到{@link NN_Tensor}中。因此当tensorDesc不再使用时，
 * 您应该调用{@link OH_NNTensorDesc_Destroy}接口销毁它。\n
 *
 * deviceID表示所选设备ID，如果为0，则使用第1台设备。\n
 *
 * tensorDesc必须提供，如果它是空指针，则该接口返回错误码。\n
 * size必须不小于tensorDesc的数据占用字节数（可由{@link OH_NNTensorDesc_GetByteSize}获取），
 * 否则该接口将返回错误码。如果张量形状是动态的，不会检查size。\n
 *
 * 当{@link NN_Tensor}实例不再使用时，需要调用{@link OH_NNTensor_Destroy}销毁它。
 *
 * @param deviceID 设备ID。如果为0，则默认使用当前设备列表中的第1台设备。
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的指针。
 * @param size 需要分配的张量数据的大小。
 * @return 指向{@link NN_Tensor}实例的指针，如果创建失败就返回NULL。
 * @since 11
 * @version 1.0
 */
NN_Tensor *OH_NNTensor_CreateWithSize(size_t deviceID, NN_TensorDesc *tensorDesc, size_t size);

/**
 * @brief 按照指定共享内存的文件描述符和{@link NN_TensorDesc}创建{@link NN_Tensor}实例。\n
 *
 * 该接口复用文件描述符fd对应的共享内存，fd可能来自另一个{@link NN_Tensor}实例。
 * 当调用{@link OH_NNTensor_Destroy}接口销毁该接口创建的张量时，不会释放该张量数据的内存。\n
 *
 * 该接口会将tensorDesc复制到{@link NN_Tensor}中。因此当tensorDesc不再使用时，
 * 您应该调用{@link OH_NNTensorDesc_Destroy}接口销毁它。\n
 *
 * deviceID表示所选设备。如果为0，则默认使用当前设备列表中的第1台设备。\n
 *
 * 必须提供tensorDesc，如果为空指针，则该接口返回错误码。\n
 *
 * 当{@link NN_Tensor}实例不再使用时，需要调用{@link OH_NNTensor_Destroy}销毁它。
 *
 * @param deviceID 设备ID，如果为0，则默认使用当前设备列表中的第1台设备。
 * @param tensorDesc 指向{@link NN_TensorDesc}实例的指针。
 * @param fd 要使用的共享内存的文件描述符。
 * @param size 要使用的共享内存的大小。
 * @param offset 要使用的共享内存的偏移量。
 * @return 指向{@link NN_Tensor}实例的指针，如果创建失败就返回NULL。
 * @since 11
 * @version 1.0
 */
NN_Tensor *OH_NNTensor_CreateWithFd(size_t deviceID,
                                    NN_TensorDesc *tensorDesc,
                                    int fd,
                                    size_t size,
                                    size_t offset);

/**
 * @brief 销毁一个{@link NN_Tensor}实例。\n
 *
 * 当不再使用{@link NN_Tensor}实例时，需要调用该接口销毁该实例，否则将发生内存泄漏。\n
 *
 * 如果tensor或*tensor为空指针，则该接口将返回错误码，并且不执行销毁操作。
 *
 * @param tensor 指向{@link NN_Tensor}实例的二级指针。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensor_Destroy(NN_Tensor **tensor);

/**
 * @brief 获取{@link NN_Tensor}的{@link NN_TensorDesc}实例。\n
 *
 * 调用该接口获取指定{@link NN_Tensor}实例的内部{@link NN_TensorDesc}实例指针。\n
 * 您可以从返回的{@link NN_TensorDesc}实例中获取各种类型的张量属性，例如名称/数据布局/数据类型/形状等。\n
 *
 * 您不应销毁返回的{@link NN_TensorDesc}实例，因为它指向了{@link NN_Tensor}的内部实例，
 * 否则一旦调用{@link OH_NNTensor_Destroy}将会发生双重释放的内存崩溃。\n
 *
 * 如果Tensor是空指针，则该接口将会返回空指针。
 *
 * @param tensor 指向{@link NN_Tensor}实例的指针。
 * @return 指向{@link NN_TensorDesc}实例的指针，如果创建失败就返回NULL。
 * @since 11
 * @version 1.0
 */
NN_TensorDesc *OH_NNTensor_GetTensorDesc(const NN_Tensor *tensor);

/**
 * @brief 获取{@link NN_Tensor}数据的内存地址。\n
 *
 * 您可以从张量数据内存读取/写入数据。数据内存是从设备上的共享内存映射的，因此设备驱动可通过这种“零拷贝”方式直接获取张量数据。\n
 *
 * 张量数据仅能使用对应共享内存中的[offset, size)一段，其中offset是共享内存上的偏移量，
 * 可以通过{@link OH_NNTensor_GetOffset}获取。 \n
 *
 * 而size是共享内存的总大小，可以通过{@link OH_NNTensor_GetSize}获取。 \n
 *
 * 如果Tensor是空指针，则该接口将会返回空指针。
 *
 * @param tensor 指向{@link NN_Tensor}实例的指针。
 * @return 指向张量数据内存的指针。如果操作失败，则返回空指针。
 * @since 11
 * @version 1.0
 */
void *OH_NNTensor_GetDataBuffer(const NN_Tensor *tensor);

/**
 * @brief 获取{@link NN_Tensor}数据所在共享内存的文件描述符。\n
 *
 * 文件描述符fd对应了一块设备共享内存，可以通过{@link OH_NNTensor_CreateWithFd}被另外一个{@link NN_Tensor}使用。 \n
 *
 * 如果 tensor 或 fd 为空指针，该接口将返回错误。
 *
 * @param tensor 指向{@link NN_Tensor}实例的指针。
 * @param fd 返回的共享内存文件描述符。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensor_GetFd(const NN_Tensor *tensor, int *fd);

/**
 * @brief 获取{@link NN_Tensor}数据所在共享内存的大小。\n
 *
 * size与接口{@link OH_NNTensor_CreateWithSize}和{@link OH_NNTensor_CreateWithFd}的参数size相同,
 * 但对于通过{@link OH_NNTensor_Create}创建的张量，size等于张量数据实际占用字节数
 * （可由{@link OH_NNTensorDesc_GetByteSize}获取）。 \n
 *
 * 张量数据仅能使用文件描述符 fd 对应的共享内存中的[offset, size)一段，其中 offset 是共享内存上的偏移量,
 * 可以通过{@link OH_NNTensor_GetOffset}获取，而size是共享内存的总大小，可以通过{@link OH_NNTensor_GetSize}获取。 \n
 *
 * 如果tensor或size为空指针，该接口将返回错误。
 *
 * @param tensor 指向{@link NN_Tensor}实例的指针。
 * @param size 返回的数据所在共享内存的大小。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensor_GetSize(const NN_Tensor *tensor, size_t *size);

/**
 * @brief 获取{@link NN_Tensor}数据所在共享内存上的偏移量。\n
 *
 * offset是张量数据在对应共享内存上的偏移量，可以通过{@link OH_NNTensor_CreateWithFd}接口，连同共享内存文件描述符、
 * 共享内存总大小一起被另外的{@link NN_Tensor}使用。 \n
 *
 * 张量数据仅能使用文件描述符fd对应的共享内存中的[offset, size)一段，其中offset是共享内存上的偏移量，
 * 可以通过{@link OH_NNTensor_GetOffset}获取,
 * 而size是共享内存的总大小，可以通过{@link OH_NNTensor_GetSize}获取。 \n
 *
 * 如果tensor或offset为空指针，该接口将返回错误。
 *
 * @param tensor 指向{@link NN_Tensor}实例的指针。
 * @param offset 返回的张量内存fd的偏移量。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNTensor_GetOffset(const NN_Tensor *tensor, size_t *offset);

/**
 * @brief 创建{@link OH_NNExecutor}执行器实例。\n
 *
 * 该接口接受一个{@link OH_NNCompilation}实例，构造一个与硬件关联的模型推理执行器。
 * 通过{@link OH_NNExecutor_SetInput}设置模型输入数据，设置输入数据后，
 * 调用{@link OH_NNExecutor_Run}接口执行推理，最后通过{@link OH_NNExecutor_SetOutput}获取计算结果。 \n
 *
 * 通过{@link OH_NNCompilation}实例创建一个{@link OH_NNExecutor}实例后，
 * 如果不再使用{@link OH_NNCompilation}实例创建其他{@link OH_NNExecutor}实例，就可以销毁{@link OH_NNCompilation}实例了。
 *
 * @param compilation 指向{@link OH_NNCompilation}实例的指针。
 * @return 指向{@link OH_NNExecutor}实例的指针，如果创建失败就返回NULL。
 * @since 9
 * @version 1.0
 */
OH_NNExecutor *OH_NNExecutor_Construct(OH_NNCompilation *compilation);

/**
 * @brief 获取输出张量的维度信息。\n
 *
 * 调用{@link OH_NNExecutor_Run}完成单次推理后，该接口获取指定输出的维度信息和维数。在动态形状输入、输出的场景中常用。 \n
 *
 * 如果索引值outputIndex达到或超过输出张量的数量，接口将返回错误。
 * 输出张量的数量可以通过{@link OH_NNExecutor_GetOutputCount}获取。 \n
 *
 * 作为输出参数，*shape不能为空指针，否则会返回错误。例如您应该定义int32_t* tensorShape = NULL，
 * 然后将&tensorShape作为参数传入。 \n
 *
 * 您无需释放shape的内存，它会随executor一起被释放。
 *
 * @param executor 指向{@link OH_NNExecutor}实例的指针。
 * @param outputIndex 输出的索引值，与调用{@link OH_NNModel_SpecifyInputsAndOutputs}时输出数据的顺序一致。
 *                    假设调用{@link OH_NNModel_SpecifyInputsAndOutputs}时，outputIndices为{4, 6, 8}，则在获取输出张量
 *                    维度信息时，三个输出的索引值分别为{0, 1, 2}。
 * @param shape 指向int32_t数组的指针，数组中的每个元素值，是输出张量在每个维度上的长度。
 * @param shapeLength uint32_t类型的指针，返回输出的维数。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 9
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNExecutor_GetOutputShape(OH_NNExecutor *executor,
                                              uint32_t outputIndex,
                                              int32_t **shape,
                                              uint32_t *shapeLength);

/**
 * @brief 销毁执行器实例，释放执行器占用的内存。\n
 *
 * 调用{@link OH_NNExecutor_Construct}创建的执行器实例需要调用该接口主动销毁，否则将造成内存泄漏。 \n
 *
 * 如果executor为空指针或者*executor为空指针，该接口仅打印警告日志，不执行销毁操作。
 *
 * @param executor 指向{@link OH_NNExecutor}实例的二级指针。
 * @since 9
 * @version 1.0
 */
void OH_NNExecutor_Destroy(OH_NNExecutor **executor);

/**
 * @brief 获取输入张量的数量。\n
 *
 * 可以先从executor中获取输入张量的数量，然后通过{@link OH_NNExecutor_CreateInputTensorDesc}由指定张量索引创建张量描述。
 *
 * @param executor 指向{@link OH_NNExecutor}实例的指针。
 * @param inputCount 返回的输入张量数量。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNExecutor_GetInputCount(const OH_NNExecutor *executor, size_t *inputCount);

/**
 * @brief 获取输出张量的数量。\n
 *
 * 可以先从executor中获取输出张量的数量，然后通过{@link OH_NNExecutor_CreateOutputTensorDesc}由指定张量索引创建张量描述。
 *
 * @param executor 指向{@link OH_NNExecutor}实例的指针。
 * @param OutputCount Output tensor count returned.
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNExecutor_GetOutputCount(const OH_NNExecutor *executor, size_t *outputCount);

/**
 * @brief 由指定索引值创建一个输入张量的描述。\n
 *
 * 输入张量描述包含了该张量所有类型的属性值。如果索引值index达到或超过输入张量的数量，接口将返回错误码。
 * 输入张量的数量可以通过{@link OH_NNExecutor_GetInputCount}获取。
 *
 * @param executor 指向{@link OH_NNExecutor}实例的指针。
 * @param index 输入张量的索引值。
 * @return 指向{@link NN_TensorDesc}实例的指针，如果创建失败就返回NULL。
 * @since 11
 * @version 1.0
 */
NN_TensorDesc *OH_NNExecutor_CreateInputTensorDesc(const OH_NNExecutor *executor, size_t index);

/**
 * @brief 由指定索引值创建一个输出张量的描述。\n
 *
 * 输出张量描述包含了该张量所有类型的属性值。如果索引值index达到或超过输出张量的数量，接口将返回错误码。
 * 输出张量的数量可以通过{@link OH_NNExecutor_GetOutputCount}获取。
 *
 * @param executor 指向{@link OH_NNExecutor}实例的指针。
 * @param index 输出张量的索引值。
 * @return 指向{@link NN_TensorDesc}实例的指针，如果创建失败就返回NULL。
 * @since 11
 * @version 1.0
 */
NN_TensorDesc *OH_NNExecutor_CreateOutputTensorDesc(const OH_NNExecutor *executor, size_t index);

/**
 * @brief 获取所有输入张量的维度范围。\n
 *
 * 当输入张量具有动态形状时，它在不同硬件上支持的维度范围可能是不同的，可以通过该接口获取当前设备上支持的维度范围。 \n
 *
 * *minInputDims保存了指定输入张量的最小维度（维度数与形状匹配），而*maxInputDims则保存了最大维度。 \n
 *
 * 例如，一个输入张量具有动态形状 [-1, -1, -1, 3]，那么当前设备上它的*minInputDims可以是[1, 10, 10, 3]，
 * 而*maxInputDims可以是[100, 1024, 1024, 3]。 \n
 *
 * 如果索引值index达到或超过输入张量的数量，接口将返回错误。输入张量的数量可以通过{@link OH_NNExecutor_GetInputCount}获取。 \n
 *
 * 作为输出参数，*minInputDims和*maxInputDims不能为空指针，否则会返回错误。例如您应该定义int32_t* minInDims = NULL，
 * 然后将&minInDims作为参数传入。 \n
 *
 * 您无需释放*minInputDims和*maxInputDims的内存，它会随executor一起被释放。
 *
 * @param executor 指向{@link OH_NNExecutor}实例的指针。
 * @param index 输入张量的索引值。
 * @param minInputDims 返回的数组的指针，保存了指定输入张量的最小维度（维度数与形状匹配）。
 * @param maxInputDims 返回的数组的指针，保存了指定输入张量的最大维度（维度数与形状匹配）。
 * @param shapeLength 返回的输入张量的维度数量，与形状一致。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNExecutor_GetInputDimRange(const OH_NNExecutor *executor,
                                                size_t index,
                                                size_t **minInputDims,
                                                size_t **maxInputDims,
                                                size_t *shapeLength);

/**
 * @brief 设置异步推理结束后的回调处理函数。\n
 *
 * 回调函数的定义详见{@link NN_OnRunDone}。
 *
 * @param executor 指向{@link OH_NNExecutor}实例的指针。
 * @param onRunDone 回调函数句柄{@link NN_OnRunDone}。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNExecutor_SetOnRunDone(OH_NNExecutor *executor, NN_OnRunDone onRunDone);

/**
 * @brief 设置异步推理执行期间设备驱动服务突然死亡时的回调处理函数。\n
 *
 * 回调函数的定义详见{@link NN_OnServiceDied}。
 *
 * @param executor 指向{@link OH_NNExecutor}实例的指针。
 * @param onServiceDied 回调函数句柄{@link NN_OnServiceDied}。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNExecutor_SetOnServiceDied(OH_NNExecutor *executor, NN_OnServiceDied onServiceDied);

/**
 * @brief 执行同步推理。\n
 *
 * 需要先通过{@link OH_NNTensor_Create}、{@link OH_NNTensor_CreateWithSize}或{@link OH_NNTensor_CreateWithFd}接口
 * 创建输入和输出张量。然后由{@link OH_NNTensor_GetDataBuffer}获取张量数据指针并向其拷贝输入数据。
 * 执行器会通过执行推理产生推理结果，并将结果写入输出张量中。 \n
 *
 * 如果输出张量具有动态形状，可以通过{@link OH_NNExecutor_GetOutputShape}接口获取输出张量的实际形状。
 * 或者通过{@link OH_NNTensor_GetTensorDesc}接口从输入张量中获取张量描述，
 * 然后通过{@link OH_NNTensorDesc_GetShape}接口获取实际形状。
 *
 * @param executor 指向{@link OH_NNExecutor}实例的指针。
 * @param inputTensor 输入张量的数组。
 * @param inputCount 输入张量的数量。
 * @param outputTensor 输出张量的数组。
 * @param outputCount 输出张量的数量。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNExecutor_RunSync(OH_NNExecutor *executor,
                                       NN_Tensor *inputTensor[],
                                       size_t inputCount,
                                       NN_Tensor *outputTensor[],
                                       size_t outputCount);

/**
 * @brief 执行异步推理。\n
 *
 * 需要先通过{@link OH_NNTensor_Create}、{@link OH_NNTensor_CreateWithSize}或{@link OH_NNTensor_CreateWithFd}接口
 * 创建输入和输出张量。然后由{@link OH_NNTensor_GetDataBuffer}获取张量数据指针并向其拷贝输入数据。
 * 执行器会通过执行推理产生推理结果，并将结果写入输出张量中。 \n
 *
 * 如果输出张量具有动态形状，可以通过{@link OH_NNExecutor_GetOutputShape}接口获取输出张量的实际形状。
 * 或者通过{@link OH_NNTensor_GetTensorDesc}接口从输入张量中获取张量描述，
 * 然后通过{@link OH_NNTensorDesc_GetShape}接口获取实际形状。 \n
 *
 * 该接口是非阻塞式的，调用后会立刻返回，而推理结果、执行返回状态可以通过回调函数{@link NN_OnRunDone}来获取。
 * 如果设备驱动服务在执行过程中异常终止，可以通过回调函数{@link NN_OnServiceDied}来处理。 \n
 *
 * 可以通过接口{@link OH_NNExecutor_SetOnRunDone}和{@link OH_NNExecutor_SetOnServiceDied}设置回调函数{@link NN_OnRunDone}
 * 和{@link NN_OnServiceDied}。 \n
 *
 * 如果推理时长超过了timeout，会立刻终止推理，回调函数{@link NN_OnRunDone}的errCode参数会返回{@link OH_NN_TIMEOUT}错误。 \n
 *
 * userData是区分不同次异步执行的标识符，会作为回调函数的第一个参数返回，您可以使用能够区分不同次执行的任意数据作为标识符。
 *
 * @param executor 指向{@link OH_NNExecutor}实例的指针。
 * @param inputTensor 输入张量的数组。
 * @param inputCount 输入张量的数量。
 * @param outputTensor 输出张量的数组。
 * @param outputCount 输出张量的数量。
 * @param timeout 异步推理的超时时间（单位ms），例如1000。
 * @param userData 异步执行的标识符。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 11
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNExecutor_RunAsync(OH_NNExecutor *executor,
                                        NN_Tensor *inputTensor[],
                                        size_t inputCount,
                                        NN_Tensor *outputTensor[],
                                        size_t outputCount,
                                        int32_t timeout,
                                        void *userData);

/**
 * @brief 获取对接到Neural Network Runtime的硬件ID。\n
 *
 * 每个硬件存在唯一且固定的ID，该接口通过uint32_t数组返回当前设备上已经对接的硬件ID。 \n
 *
 * 硬件ID通过size_t数组返回，数组的每个元素是单个硬件的ID值。数组内存由内部进行管理，在下次调用该接口前，数据指针将一直有效。
 *
 * @param allDevicesID 指向size_t数组的指针。要求传入的*allDevicesID为空指针，
 * 否则将返回错误码{@link OH_NN_INVALID_PARAMETER}。
 * @param deviceCount uint32_t类型的指针，用于返回*allDevicesID的长度。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 9
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNDevice_GetAllDevicesID(const size_t **allDevicesID, uint32_t *deviceCount);

/**
 * @brief 获取指定硬件的名称。\n
 *
 * 通过deviceID指定计算硬件，获取硬件的名称。硬件ID需要调用{@link OH_NNDevice_GetAllDevicesID}获取。
 * 如果deviceID是0，那么会默认使用设备列表中的第一个设备。 \n
 *
 * name是一个C风格的字符串，以'\0'作为结束符。 \n
 *
 * name必须是一个空指针，否则接口会返回{@link OH_NN_INVALID_PARAMETER}错误。
 * 例如您应该定义char* deviceName = NULL，然后将 &deviceName 作为参数传入。
 *
 * @param deviceID 指定硬件ID。如果deviceID是0，那么会默认使用设备列表中的第一个设备。
 * @param name 指向char数组的指针，保存返回的硬件名称。
 * @return 函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 9
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNDevice_GetName(size_t deviceID, const char **name);

/**
 * @brief 获取指定硬件的类别信息。\n
 *
 * 通过deviceID指定计算硬件，获取硬件的类别。如果deviceID是0，那么会默认使用设备列表中的第一个设备。目前支持的设备类型有：\n
 * - CPU设备：OH_NN_CPU \n
 * - GPU设备：OH_NN_GPU \n
 * - 机器学习专用加速器：OH_NN_ACCELERATOR \n
 * - 不属于以上类型的其他硬件类型：OH_NN_OTHERS
 *
 * @param deviceID 指定硬件ID。如果deviceID是0，那么会默认使用设备列表中的第一个设备。
 * @param deviceType 指向{@link OH_NN_DeviceType}实例的指针，返回硬件的类别信息。
 * @return  函数执行的结果状态。执行成功返回OH_NN_SUCCESS；失败返回具体错误码，具体失败错误码可参考{@link OH_NN_ReturnCode}。
 * @since 9
 * @version 1.0
 */
OH_NN_ReturnCode OH_NNDevice_GetType(size_t deviceID, OH_NN_DeviceType *deviceType);

#ifdef __cplusplus
}
#endif // __cplusplus

/** @} */
#endif // NEURAL_NETWORK_CORE_H
/*
 * Copyright (C) 2024-2026 Huawei Device Co., Ltd.
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
 * @addtogroup IPCKit
 * @{
 *
 * @brief IPC（Inter-Process Communication，进程间通信）Kit提供了进程间通信的能力，支持跨进程数据传输、方法调用等功能，帮助开发者快速构建稳定可靠的进程间通信能力。
 * 开发者可以通过引用ipc_kit.h头文件，使用IPC Kit提供的API进行进程间通信开发。典型使用场景包括：多进程协作、服务间通信、跨进程数据共享等。
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
/**
 * @file ipc_kit.h
 *
 * @brief IPC（Inter-Process Communication，进程间通信）头文件，提供IPC Kit的C API接口声明，方便开发者引用。开发者可通过此头文件使用进程间通信能力。
 *
 * @include <IPCKit/ipc_cparcel.h>
 * @library libipc_capi.so
 * @kit IPCKit
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */

#ifndef CAPI_INCLUDE_IPC_KIT_H
#define CAPI_INCLUDE_IPC_KIT_H

#include "ipc_error_code.h"
#include "ipc_cparcel.h"
#include "ipc_cremote_object.h"
#include "ipc_cskeleton.h"

/** @} */
#endif
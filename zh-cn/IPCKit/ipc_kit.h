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
 * @brief IPC（Inter-Process Communication，进程间通信）头文件，提供IPC Kit的C API接口声明，方便开发者引用。开发者可通过此
 * 头文件使用进程间通信能力。
 */
/**
 * @file ipc_kit.h
 *
 * @brief IPC（Inter-Process Communication，进程间通信）头文件，提供IPC Kit的C API接口声明，方便开发者引用。开发者可通过此
 * 头文件使用进程间通信能力。
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @include <IPCKit/ipc_kit.h>
 * @library libipc_capi.so
 * @kit IPCKit
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
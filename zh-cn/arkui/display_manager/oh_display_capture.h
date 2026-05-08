
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
 * @file oh_display_capture.h
 *
 * @brief The file declares the capability to take screenshots.
 * 
 * @kit ArkUI
 * @library libnative_display_manager.so
 * @syscap SystemCapability.WindowManager.WindowManager.Core
 * @since 14
 * @version 1.0
 */

/**
 * @addtogroup OH_DisplayManager
 * @{
 *
 * @brief Defines the data structures for the C APIs of the display module.
 *
 * @syscap SystemCapability.WindowManager.WindowManager.Core
 * @since 14
 * @version 1.0
 */
#ifndef OH_NATIVE_DISPLAY_CAPTURE_H
#define OH_NATIVE_DISPLAY_CAPTURE_H
#include "multimedia/image_framework/image/pixelmap_native.h"
#include "oh_display_info.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取屏幕全屏截图，可以通过设置不同的屏幕id号截取不同屏幕的截图。
 * 
 * @permission ohos.permission.CUSTOM_SCREEN_CAPTURE or ohos.permission.CUSTOM_SCREEN_RECORDING [since 22]
 * @permission ohos.permission.CUSTOM_SCREEN_CAPTURE [since 14]
 * @param displayId 需要截屏的屏幕id号，该值为非负整数。
 * @param pixelMap 创建指定屏幕id的OH_PixelmapNative对象，此处作为出参返回。
 * @return 返回屏幕管理接口的通用状态码，具体可见{@link NativeDisplayManager_ErrorCode}。
 * @since 14
 */
NativeDisplayManager_ErrorCode OH_NativeDisplayManager_CaptureScreenPixelmap(uint32_t displayId,
    OH_PixelmapNative **pixelMap);
#ifdef __cplusplus
}
#endif

/** @} */
#endif // OH_NATIVE_DISPLAY_CAPTURE_H
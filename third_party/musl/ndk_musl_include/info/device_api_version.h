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

#ifndef _INFO_DEVICE_API_VERSION_H
#define _INFO_DEVICE_API_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief Get the api version number of the device.
  *        Note: the interface function is not implemented.
  * @return The api version number of the device.
  * @since 12
  * @deprecated since 15
  */
int get_device_api_version(void);

#ifdef __cplusplus
}
#endif

#endif // _INFO_DEVICE_API_VERSION_H

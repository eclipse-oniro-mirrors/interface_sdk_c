
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
 * @file oh_window.h
 *
 * @brief The file declares the window management APIs. You can use the APIs to set and obtain the properties of a
 * window, and set its status bar style and navigation bar style.
 * 
 * @library libnative_window_manager.so
 * @kit ArkUI
 * @syscap SystemCapability.Window.SessionManager
 * @since 15
 */

/**
 * @addtogroup WindowManager
 * @{
 *
 * @brief Provides abilities of window on the native side.
 * @since 15
 */
#ifndef OH_WINDOW_H
#define OH_WINDOW_H
#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#include "stdbool.h"
#include "stdint.h"

#include "oh_window_comm.h"
#include "multimodalinput/oh_input_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief �����������Ƿ���ʾ״̬����
 * 
 * @param windowId ������id�������������idʱ������Ч�������ڶ�Ӧ����idʱ�ӿڷ��ش�����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL��
 * @param enabled ����״̬���Ƿ���ʾ��true��ʾ����״̬����ʾ��false��ʾ����״̬�����ء�
 * @param enableAnimation �����Ƿ���״̬��������������true��ʾ����״̬��������������false��ʾ�ر�״̬��������������
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED����ʾ��֧�ֹ��ܡ�
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 15
 */
int32_t OH_WindowManager_SetWindowStatusBarEnabled(int32_t windowId, bool enabled, bool enableAnimation);

/**
 * @brief ���������ڵ�״̬��������ɫ��
 * 
 * @param windowId ������id�������������idʱ������Ч�������ڶ�Ӧ����idʱ�ӿڷ��ش�����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL��
 * @param color Ҫ���õ���ɫֵ����ʽΪARGB��
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED����ʾ��֧�ֹ��ܡ�
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 15
 */
int32_t OH_WindowManager_SetWindowStatusBarColor(int32_t windowId, int32_t color);

/**
 * @brief �����������Ƿ���ʾ��������<!--RP2--><!--RP2End-->
 * 
 * @param windowId ������id�������������idʱ������Ч�������ڶ�Ӧ����idʱ�ӿڷ��ش�����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL��
 * @param enabled ���õ������Ƿ���ʾ��true��ʾ���õ�������ʾ��false��ʾ���õ��������ء�
 * @param enableAnimation �����Ƿ���������������������true��ʾ����������������������false��ʾ�رյ�����������������
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED����ʾ��֧�ֹ��ܡ�
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 15
 */
int32_t OH_WindowManager_SetWindowNavigationBarEnabled(int32_t windowId, bool enabled, bool enableAnimation);

/**
 * @brief ��ȡָ�����ڵı�������
 * 
 * @param windowId ��������ʱ�Ĵ���id��Ĭ��ֵΪ0���ò���Ϊ������
 * @param type ������������͡�
 * @param avoidArea ����ָ��ָ�����ڵı��������ָ�룬��Ϊ����ʹ�á�
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ�������ָ���Ӧ����id�ı��������ָ�롣
 *     ����WINDOW_MANAGER_ERRORCODE_INVALID_PARAM����ʾ��������
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 15
 */
int32_t OH_WindowManager_GetWindowAvoidArea(
    int32_t windowId, WindowManager_AvoidAreaType type, WindowManager_AvoidArea* avoidArea);

/**
 * @brief �ж�ָ�������Ƿ���ʾ��
 * 
 * @param windowId ��������ʱ�Ĵ���id��Ĭ��ֵΪ0���ò���Ϊ������
 * @param isShow ����ָ�������Ƿ���ʾ�Ľ����true��ʾָ��������ʾ��false��ʾָ�����ڲ���ʾ����Ϊ����ʹ�á�
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_INVALID_PARAM����ʾ��������
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 * @since 15
 */
int32_t OH_WindowManager_IsWindowShown(int32_t windowId, bool* isShow);

/**
 * @brief ��ʾָ�����ڡ�
 * 
 * @param windowId ��������ʱ�Ĵ���id��Ĭ��ֵΪ0���ò���Ϊ������
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 15
 */
int32_t OH_WindowManager_ShowWindow(int32_t windowId);

/**
 * @brief ����ָ�������Ƿ�ɴ���
 * 
 * @param windowId ��������ʱ�Ĵ���id��Ĭ��ֵΪ0���ò���Ϊ������
 * @param isTouchable �����Ƿ�ɴ���true��ʾ���ڿɴ���false��ʾ���ڲ��ɴ���
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 15
 */
int32_t OH_WindowManager_SetWindowTouchable(int32_t windowId, bool isTouchable);

/**
 * @brief ����ָ�������Ƿ�ɻ񽹡�
 * 
 * @param windowId ��������ʱ�Ĵ���id��Ĭ��ֵΪ0���ò���Ϊ������
 * @param isFocusable �����Ƿ�ɻ񽹡�true��ʾ���ڿɻ񽹣�false��ʾ���ڲ��ɻ񽹡�
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 15
 */
int32_t OH_WindowManager_SetWindowFocusable(int32_t windowId, bool isFocusable);

/**
 * @brief ����ָ�����ڱ�����ɫ��
 * 
 * @param windowId ��������ʱ�Ĵ���id��Ĭ��ֵΪ0���ò���Ϊ������
 * @param color ���ô��ڵı���ɫ���ò���Ϊ�ַ������ͣ���ʽΪʮ������RGB��ARGB��ɫ��
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_INVALID_PARAM����ʾ��������
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 * @since 18
 */
int32_t OH_WindowManager_SetWindowBackgroundColor(int32_t windowId, const char* color);

/**
 * @brief ָ�����������ô������ȡ������ڴ���ǰ̨�һ�ʱ������������Ч��
 * 
 * @param windowId ��������ʱ�Ĵ���id��Ĭ��ֵΪ0���ò���Ϊ������
 * @param brightness ָ������Ļ����ֵ���ò���Ϊ��������ȡֵ��ΧΪ[0.0, 1.0]��-1.0��1.0��ʾ������-1.0��ʾ�ָ������ô�������ǰ��ϵͳ�����������ȡ�
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_INVALID_PARAM����ʾ��������
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 18
 */
int32_t OH_WindowManager_SetWindowBrightness(int32_t windowId, float brightness);

/**
 * @brief ����ָ�������Ƿ�����Ļ������
 * 
 * @param windowId ��������ʱ�Ĵ���id��Ĭ��ֵΪ0���ò���Ϊ������
 * @param isKeepScreenOn ָ�������Ƿ�����Ļ������true��ʾ������Ļ������false��ʾ�ر���Ļ������
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 15
 */
int32_t OH_WindowManager_SetWindowKeepScreenOn(int32_t windowId, bool isKeepScreenOn);

/**
 * @brief ����ָ�������Ƿ�����˽ģʽ��
 * 
 * @permission ohos.permission.PRIVACY_WINDOW
 * @param windowId ��������ʱ�Ĵ���id��Ĭ��ֵΪ0���ò���Ϊ������
 * @param isPrivacy ָ�������Ƿ�����˽ģʽ��true��ʾ������˽ģʽ��false��ʾ�ر���˽ģʽ��
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_NO_PERMISSION��Ȩ��У�����
 * @since 15
 */
int32_t OH_WindowManager_SetWindowPrivacyMode(int32_t windowId, bool isPrivacy);

/**
 * @brief ��ȡָ���������ԡ�
 * 
 * @param windowId ��������ʱ�Ĵ���id��Ĭ��ֵΪ0���ò���Ϊ������
 * @param windowProperties ����ָ��ָ�����ڵ����Ե�ָ�룬��Ϊ����ʹ�á�
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ�����windowProperties�з��ش������Ե�ָ�롣
 *     ����WINDOW_MANAGER_ERRORCODE_INVALID_PARAM����ʾ��������
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 * @since 15
 */
int32_t OH_WindowManager_GetWindowProperties(
    int32_t windowId, WindowManager_WindowProperties* windowProperties);

/**
 * @brief ��ȡָ�����ڽ�ͼ��
 * 
 * @param windowId ��������ʱ�Ĵ���id��Ĭ��ֵΪ0���ò���Ϊ������
 *     ����id�Ƿ����ߴ����Ѿ����٣����ܻ�ȡָ�����ڽ�ͼ����Ҫ������Ч�Ĵ���id���ܳɹ���ȡָ�����ڽ�ͼ��
 *     ��ͨ�����ڶ������{@link getWindowProperties()}�ӿڣ�ArkTS�ӿڣ���ȡ��Ч�Ĵ���id��
 * @param pixelMap ����ָ��ָ�����ڵĽ�ͼ��ָ�룬��Ϊ����ʹ�á�
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ����ڷ���pixelMap�е�����ͼ��ָ�롣
 *     ����WINDOW_MANAGER_ERRORCODE_INVALID_PARAM����ʾ��������
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 15
 */
int32_t OH_WindowManager_Snapshot(int32_t windowId, OH_PixelmapNative* pixelMap);

/**
 * @brief ��ȡָ����Ļ�Ͽɼ��Ĵ��ڲ�����Ϣ���飬����ǰ���ڲ㼶���У��㼶��ߵĶ�Ӧ�����±�Ϊ0��
 * 
 * @param displayId ָ����Ļ��id����ͨ�����ڶ������{@link getWindowProperties()}�ӿڣ�ArkTS�ӿڣ���ȡ��Ч����Ļid��
 * @param windowLayoutInfoList ָ����Ļ�Ͽɼ��Ĵ��ڲ�����Ϣ���������ָ�룬��Ϊ����ʹ�á�
 * @param windowLayoutInfoSize ָ����Ļ�Ͽɼ��Ĵ��ڲ�����Ϣ���鳤�ȵ�ָ�룬��Ϊ����ʹ�á�
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ�������ָ����Ļ�Ͽɼ��Ĵ��ڲ�����Ϣ���������ָ������鳤�ȵ�ָ�롣
 *     ����WINDOW_MANAGER_ERRORCODE_INVALID_PARAM����ʾ��������
 *     ����WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED����ʾ��֧�ֹ��ܡ�
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 17
 */
int32_t OH_WindowManager_GetAllWindowLayoutInfoList(int64_t displayId,
    WindowManager_Rect** windowLayoutInfoList, size_t* windowLayoutInfoSize);

/**
 * @brief �ͷŴ��ڲ�����Ϣ����ռ�õ��ڴ档
 * 
 * @param windowLayoutInfoList ָ����Ļ�Ͽɼ��Ĵ��ڲ�����Ϣ���������ָ�룬��ͨ��{@link OH_WindowManager_GetAllWindowLayoutInfoList}�ӿڻ�ȡ��
 * @since 17
 */
void OH_WindowManager_ReleaseAllWindowLayoutInfoList(WindowManager_Rect* windowLayoutInfoList);

/**
 * @brief ����ģ�����¼�ע���Ŀ�괰�ڣ���֧��ע��ͬ���̴��ڣ��Ҹ�ע�벻�ᴥ�����ڽ���Ͳ㼶�仯�����ᴥ��������ק���¼���ֱ�ӷ��͸�ArkUI���ýӿ���Ҫ��ָ�����ڼ���UI֮����á�
 * 
 * @param windowId ��������ʱ�Ĵ���id��Ĭ��ֵΪ0���ò���Ϊ������
 * @param touchEvent ��ģ�����¼�������ɼ�{@link Input_TouchEvent}���¼�������oh_input_manager.h�С��ò��������Ĳ����ֶ��в������ƣ����У�
 *     actionӦΪ���ڵ���0��С�ڵ���3��������id��displayX��displayY��actionTimeӦΪ��С��0��������
 *     ���ϲ������������������᷵��WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ�����ڹ����������쳣��
 * @param windowX ע���¼������ע�봰�ڵ��������ꡣ�ò���Ϊ������
 * @param windowY ע���¼������ע�봰�ڵ���������ꡣ�ò���Ϊ������
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 20
 */
int32_t OH_WindowManager_InjectTouchEvent(
    int32_t windowId, Input_TouchEvent* touchEvent, int32_t windowX, int32_t windowY);

/**
 * @brief ��ȡȫ��������Ϣ��
 * 
 * @permission ohos.permission.CUSTOM_SCREEN_CAPTURE
 * @param infoList ָ����������Ϣ�б���ָ�룬��Ϊ����ʹ�á�
 * @param mainWindowInfoSize ָ����������Ϣ���鳤�ȵ�ָ�룬��Ϊ����ʹ�á�
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_NO_PERMISSION��Ȩ��У�����
 *     ����WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED����ʾ��֧�ֹ��ܡ�
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 21
 */
int32_t OH_WindowManager_GetAllMainWindowInfo(
    WindowManager_MainWindowInfo** infoList, size_t* mainWindowInfoSize);

/**
 * @brief �ͷ���������Ϣ�б����ڴ档
 * 
 * @param infoList ������Ϣ�б���
 * @since 21
 */
void OH_WindowManager_ReleaseAllMainWindowInfo(WindowManager_MainWindowInfo* infoList);

/**
 * @brief ���������ڽ�ͼ�б��Ļص��ӿڡ�
 * 
 * @param snapshotPixelMapList ���ڽ�ͼ�б���
 * @param snapshotListSize ���ڽ�ͼ�б��Ĵ�С��
 * @since 21
 */
typedef void (*OH_WindowManager_WindowSnapshotCallback)(const OH_PixelmapNative** snapshotPixelMapList,
    size_t snapshotListSize);

/**
 * @brief ��ȡһ������ָ��windowId�������ڽ�ͼ��
 * 
 * @permission ohos.permission.CUSTOM_SCREEN_CAPTURE
 * @param windowIdList ��Ҫ��ȡ��ͼ��������ID�б���
 * @param windowIdListSize ������ID�б��ĳ��ȡ�
 * @param config ��ȡ���ڽ�ͼʱ��������Ϣ��
 * @param callback ��ȡ���ڽ�ͼ�Ļص��������ڷ��ش��ڽ�ͼ�б���������ָ���Ĵ���ID�б�˳�����С�
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_NO_PERMISSION��Ȩ��У�����
 *     ����WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED����ʾ��֧�ֹ��ܡ�
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 21
 */
int32_t OH_WindowManager_GetMainWindowSnapshot(int32_t* windowIdList, size_t windowIdListSize,
    WindowManager_WindowSnapshotConfig config, OH_WindowManager_WindowSnapshotCallback callback);

/**
 * @brief �ͷ������ڽ�ͼ�б����ڴ档
 * 
 * @param snapshotPixelMapList ���ڽ�ͼ�б���
 * @since 21
 */
void OH_WindowManager_ReleaseMainWindowSnapshot(const OH_PixelmapNative* snapshotPixelMapList);

/**
 * @brief ��������꣬��������겻����ָ����������ͬʱ�ɿ��ƹ���Ƿ��������ƶ�����֧�ֻ񽹴��ڵ��ã�ʧ��֮����Զ�ȡ��������
 * 
 * @permission ohos.permission.LOCK_WINDOW_CURSOR
 * @param windowId ��������ʱ�Ĵ���ID���ò���Ϊ������
 * @param isCursorFollowMovement ��������������ģʽ����Ϊtrue��������������ƶ�����Ϊfalse�����겻���������ƶ���
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_NO_PERMISSION����ʾû��Ȩ�޵��øýӿڡ�
 *     ����WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED����ʾ��֧�ָ��豸��
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 22
 */
int32_t OH_WindowManager_LockCursor(int32_t windowId, bool isCursorFollowMovement);

/**
 * @brief ����������õ������ָ����ģʽ��
 * 
 * @permission ohos.permission.LOCK_WINDOW_CURSOR
 * @param windowId ��������ʱ�Ĵ���ID���ò���Ϊ������
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_NO_PERMISSION����ʾû��Ȩ�޵��øýӿڡ�
 *     ����WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED����ʾ��֧�ָ��豸��
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL����ʾ���ڹ����������쳣��
 * @since 22
 */
int32_t OH_WindowManager_UnlockCursor(int32_t windowId);

/**
 * @brief �жϵ�ǰ֡�Ƿ�Ϊ��֡��
 *  
 * @param metrics ֡��ָ�����ݶ���
 * @param isFirstDrawFrame ��Ϊ����ʹ�ã���ʾ��ǰ֡�Ƿ�Ϊ��֡��true��ʾ����֡��false��ʾ������֡��
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM����ʾ�������󣬶�Ӧ����ȡֵ��Χ��������
 *     ����ɼ�{@link WindowManager_ErrorCode}��
 * @since 26.0.0
 */
int32_t OH_WindowManager_FrameMetrics_IsFirstDrawFrame(
    const OH_WindowManager_FrameMetrics* metrics, bool* isFirstDrawFrame);

/**
 * @brief ��ȡ��ǰ֡�����ƴ����ĺ�ʱ��
 * 
 * @param metrics ֡��ָ�����ݶ���
 * @param duration ��Ϊ����ʹ�ã���ʾ��ǰ֡�����ƴ����ĺ�ʱ����λΪ���롣
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM����ʾ�������󣬶�Ӧ����ȡֵ��Χ��������
 *     ����ɼ�{@link WindowManager_ErrorCode}��
 * @since 26.0.0
 */
int32_t OH_WindowManager_FrameMetrics_GetInputHandlingDuration(
    const OH_WindowManager_FrameMetrics* metrics, uint64_t* duration);

/**
 * @brief ��ȡ��ǰ֡�в��ֲ����ĺ�ʱ��
 * 
 * @param metrics ֡��ָ�����ݶ���
 * @param duration ��Ϊ����ʹ�ã���ʾ��ǰ֡�в��ֲ����ĺ�ʱ����λΪ���롣
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM����ʾ�������󣬶�Ӧ����ȡֵ��Χ��������
 *     ����ɼ�{@link WindowManager_ErrorCode}��
 * @since 26.0.0
 */
int32_t OH_WindowManager_FrameMetrics_GetLayoutMeasureDuration(
    const OH_WindowManager_FrameMetrics* metrics, uint64_t* duration);

/**
 * @brief ��ȡ��ǰ֡��ʼ��ʱ�����
 * 
 * @param metrics ֡��ָ�����ݶ���
 * @param timestamp ��Ϊ����ʹ�ã���ʾ��ǰ֡��ʼ��ʱ�������λΪ���롣
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM����ʾ�������󣬶�Ӧ����ȡֵ��Χ��������
 *     ����ɼ�{@link WindowManager_ErrorCode}��
 * @since 26.0.0
 */
int32_t OH_WindowManager_FrameMetrics_GetVsyncTimestamp(
    const OH_WindowManager_FrameMetrics* metrics, uint64_t* timestamp);

/**
 * @brief ���Ĵ���֡��ָ���������¼��� 
 *  �ýӿ���������ҳ�����ݼ��أ�����Ҫ��ArkTS��loadContent()�ӿڻ�setUIContent()�ӿ���Ч����á� 
 *  Ӧ��ע��֡��ָ���������󣬽����ͻ���UI���ݷ����ػ棨����ҳ���л�����Ӧʽ������������ñ���ɫ��͸���ȵȣ�ʱ�Żᴥ����ע��ص��� 
 *  ����ȡ�����ģ���ʹ��{@link OH_WindowManager_UnregisterFrameMetricsMeasuredCallback}�ӿڡ�
 * 
 * @param windowId ��������ʱ�Ĵ���ID��
 * @param callback ���ڷ���֡��ָ�����Ļص�������
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣������ԭ��
 *     1. ����δ�����������٣�
 *     2. ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM����ʾ�������󣬶�Ӧ����ȡֵ��Χ��������
 *     ����ɼ�{@link WindowManager_ErrorCode}��
 * @since 26.0.0
 */
int32_t OH_WindowManager_RegisterFrameMetricsMeasuredCallback(int32_t windowId, 
    OH_WindowManager_FrameMetricsMeasuredCallback callback);

/**
 * @brief ȡ�����Ĵ���֡��ָ���������¼��� 
 *  �ýӿ���������ҳ�����ݼ��أ�����Ҫ��ArkTS��loadContent()�ӿڻ�setUIContent()�ӿ���Ч����á� 
 *  ���趩�ģ���ʹ��{@link OH_WindowManager_RegisterFrameMetricsMeasuredCallback}�ӿڡ�
 * 
 * @param windowId ��������ʱ�Ĵ���ID��
 * @param callback ���ڷ���֡��ָ�����Ļص�������
 * @return ���ؽ�����롣
 *     ����OK����ʾ�������óɹ���
 *     ����WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL����ʾ����״̬�쳣������ԭ��
 *     1. ����δ�����������٣�
 *     2. ����״̬�쳣��
 *     ����WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM����ʾ�������󣬶�Ӧ����ȡֵ��Χ��������
 *     ����ɼ�{@link WindowManager_ErrorCode}��
 * @since 26.0.0
 */
int32_t OH_WindowManager_UnregisterFrameMetricsMeasuredCallback(int32_t windowId, 
    OH_WindowManager_FrameMetricsMeasuredCallback callback);

/**
 * @brief ��ȡ����������Ļ��ϵͳĬ����ʾ��С�������ӡ�
 *
 * @param info ��ʾ��ǰ���ڵĴ�С����������Ϣ��
 * @param density ϵͳĬ����ʾ�ߴ��������
 * @return ����ִ�е�״̬���롣
 * {@link WS_OK}�������óɹ���
 * {@link WINDOWS_MANAGER_ERRORCODE_INCORRECT_PARAM}�������󡣿���ԭ��
 * 1.������Χ�Ƿ���
 * @since 24
 */
int32_t OH_WindowManager_DensityInfo_GetDefaultDensity(const OH_WindowManager_DensityInfo* info,
    float* density);

/**
 * @brief ��ȡ����������Ļ��ϵͳ��ʾ��С�������ӡ�
 *
 * @param info ��ʾ��ǰ���ڵĴ�С����������Ϣ��
 * @param density ϵͳ��ʾ�ߴ��������
 * @return ����ִ�е�״̬���롣
 * {@link WS_OK}�������óɹ���
 * {@link WINDOWS_MANAGER_ERRORCODE_INCORRECT_PARAM}�������󡣿���ԭ��
 * 1.������Χ�Ƿ���
 * @since 24
 */
int32_t OH_WindowManager_DensityInfo_GetSystemDensity(const OH_WindowManager_DensityInfo* info,
    float* density);

/**
 * @brief ��ȡ���ڵ��Զ�����ʾ��С�������ӡ�
 *
 * @param info ��ǰ����������Ļ����ʾ��С����������Ϣ��
 * @param density ���ڵ��Զ�����ʾ��С�������ӡ�����ֵ-1��ʾû���Զ���
 * ��������ʾ��С�������ӣ��������á�
 * @return ����ִ�е�״̬���롣
 * {@link WS_OK}�������óɹ���
 * {@link WINDOWS_MANAGER_ERRORCODE_INCORRECT_PARAM}�������󡣿���ԭ��
 * 1.������Χ�Ƿ���
 * @since 24
 */
int32_t OH_WindowManager_DensityInfo_GetCustomDensity(const OH_WindowManager_DensityInfo* info,
    float* density);

/**
 * @brief ��ȡ����������Ļ��ϵͳ��ʾ��С����ϵ��������������Ļ��ϵͳĬ����ʾ��С����ϵ����
 * �Լ���ǰ�����Զ������õ���ʾ��С����ϵ����
 *
 * @param windowId ����windowʱ��WindowId��
 * @param info ��ʾ��ǰ���ڵ���ʾ�ܶ���Ϣ��
 * ����ֵNULL��ʾ��ǰ�豸��֧�ִ˽ӿڡ�
 * @return ����ִ�е�״̬���롣
 * {@link WS_OK}�������óɹ���
 * {@link WINDOWS_MANAGER_ERRORCODE_STATE_ABNORMAL}�˴���״̬������������ԭ��
 * 1.���ڲ������������٣�
 * 2.�ô���״̬��������
 * {@link WINDOWS_MANAGER_ERRORCODE_INCORRECT_PARAM}�������󡣿���ԭ��
 * 1.������Χ�Ƿ���
 * @since 24
 */
int32_t OH_WindowManager_GetDensityInfoCopy(int32_t windowId,
    const OH_WindowManager_DensityInfo** info);

/**
 * @brief Listen for changes in the display size scaling factor information of the window. The callback function is
 *     triggered when any of the system display size scaling factor, system default display size scaling factor, or
 *     custom display size scaling factor of the screen where the window resides changes.
 *
 * @param windowId WindowId when window is created.
 * @param callback Callback used to return the result of density information.
 * @return Returns the status code of the execution.
 *         {@link WS_OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal. Possible cause:
 *             1. The window is not created or destroyed;
 *             2. This window state is abnormal.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *             1. Invalid parameter range.
 * @since 24
 */
int32_t OH_WindowManager_RegisterDensityInfoChangeCallback(int32_t windowId, 
    OH_WindowManager_DensityInfoCallback callback);

/**
 * @brief Unlisten for changes in the display size scaling factor information of the window. The callback function is
 *     triggered when any of the system display size scaling factor, system default display size scaling factor, or
 *     custom display size scaling factor of the screen where the window resides changes.
 *
 * @param windowId WindowId when window is created.
 * @param callback Callback used to return the result of density information.
 * @return Returns the status code of the execution.
 *         {@link WS_OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal. Possible cause:
 *             1. The window is not created or destroyed;
 *             2. This window state is abnormal.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *             1. Invalid parameter range.
 * @since 24
 */
int32_t OH_WindowManager_UnregisterDensityInfoChangeCallback(int32_t windowId, 
    OH_WindowManager_DensityInfoCallback callback);

/**
 * @brief �ͷ�DensityInfoָ��ָ����ڴ�ռ�
 *
 * @param info ��ʾ��ǰ���ڵ�DensityInfo��
 * @return ����ִ�е�״̬���롣
 * {@link WS_OK}�������óɹ���
 * {@link WINDOWS_MANAGER_ERRORCODE_INCORRECT_PARAM}�������󡣿���ԭ��
 * 1.������Χ�Ƿ���
 * @since 24
 */
int32_t OH_WindowManager_DensityInfo_Release(const OH_WindowManager_DensityInfo* info);

#ifdef __cplusplus
}
#endif

#endif // OH_WINDOW_H
/** @} */
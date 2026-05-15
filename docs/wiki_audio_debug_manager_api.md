# OH_AudioDebugManager 接口说明

> 文件路径：`multimedia/audio_framework/audio_manager/native_audio_debug_manager.h`  
> 库：`libohaudio.so`  
> SysCap：`SystemCapability.Multimedia.Audio.Core`  
> Kit：`AudioKit`  
> 起始版本：26.0.0

---

## 概述

`OH_AudioDebugManager` 提供音频运行时快照（Runtime Snapshot）功能，允许开发者获取音频系统中各组件的运行状态信息，用于调试和问题定位。

---

## 数据类型

### OH_AudioDebugManager

```c
typedef struct OH_AudioDebugManager OH_AudioDebugManager;
```

音频调试管理器，提供获取音频系统运行时信息的功能。

---

## 接口列表

| 接口 | 说明 |
|------|------|
| `OH_AudioManager_GetAudioDebugManager` | 获取 Debug Manager 单例句柄 |
| `OH_AudioDebugManager_PrintAppInfo` | 打印单应用音频运行时快照 |
| `OH_AudioDebugManager_PrintRendererInfo` | 打印 AudioRenderer 运行时快照 |
| `OH_AudioDebugManager_PrintCapturerInfo` | 打印 AudioCapturer 运行时快照 |
| `OH_AudioDebugManager_PrintLoopbackInfo` | 打印 AudioLoopback 运行时快照 |
| `OH_AudioDebugManager_PrintSessionInfo` | 打印 AudioSession 运行时快照 |
| `OH_AudioDebugManager_PrintSuiteInfo` | 打印 AudioSuiteEngine 运行时快照 |

---

## 接口详细说明

### OH_AudioManager_GetAudioDebugManager

```c
OH_AudioCommon_Result OH_AudioManager_GetAudioDebugManager(OH_AudioDebugManager **debugManager);
```

获取音频调试管理器的单例句柄。

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| debugManager | `OH_AudioDebugManager **` | 输出参数，用于获取 `OH_AudioDebugManager` 实例 |

**返回值：**

| 返回值 | 说明 |
|--------|------|
| `AUDIOCOMMON_RESULT_SUCCESS` | 执行成功 |
| `AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM` | 参数无效（debugManager 为 nullptr） |

---

### OH_AudioDebugManager_PrintAppInfo

```c
OH_AudioCommon_Result OH_AudioDebugManager_PrintAppInfo(OH_AudioDebugManager *debugManager, int32_t fd);
```

打印当前应用的音频运行时快照。

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| debugManager | `OH_AudioDebugManager *` | 由 `OH_AudioManager_GetAudioDebugManager` 获取的句柄 |
| fd | `int32_t` | 文件描述符。fd < 0 时快照信息输出到流水线日志；fd ≥ 0 时快照信息写入 fd 指向的文件 |

**返回值：**

| 返回值 | 说明 |
|--------|------|
| `AUDIOCOMMON_RESULT_SUCCESS` | 执行成功 |
| `AUDIOCOMMON_RESULT_ERROR_SYSTEM` | 系统处理错误 |

---

### OH_AudioDebugManager_PrintRendererInfo

```c
OH_AudioCommon_Result OH_AudioDebugManager_PrintRendererInfo(
    OH_AudioDebugManager *debugManager,
    OH_AudioRenderer *renderer,
    int32_t fd);
```

打印指定 AudioRenderer 的运行时快照。

**参数：**

| 参数 |  | 说明 |
|------|------|------|
| debugManager | `OH_AudioDebugManager *` | 由 `OH_AudioManager_GetAudioDebugManager` 获取的句柄 |
| renderer | `OH_AudioRenderer *` | 指向需要打印快照的 AudioRenderer |
| fd | `int32_t` | 文件描述符。fd < 0 时快照信息输出到流水线日志；fd ≥ 0 时快照信息写入 fd 指向的文件 |

**返回值：**

| 返回值 | 说明 |
|--------|------|
| `AUDIOCOMMON_RESULT_SUCCESS` | 执行成功 |
| `AUDIOCOMMON_RESULT_ERROR_SYSTEM` | 系统处理错误 |

---

### OH_AudioDebugManager_ShowCapturerInfo

```c
OH_AudioCommon_Result OH_AudioDebugManager_ShowCapturerInfo(
    OH_AudioDebugManager *debugManager,
    OH_AudioCapturer *capturer,
    int fd);
```

显示指定 AudioCapturer 的运行时快照。

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| debugManager | `OH_AudioDebugManager *` | 由 `OH_AudioManager_GetAudioDebugManager` 获取的句柄 |
| capturer | `OH_AudioCapturer *` | 指向需要显示快照的 AudioCapturer |
| fd | `int` | 文件描述符。fd < 0 时快照信息输出到流水线日志；fd ≥ 0 时快照信息写入 fd 指向的文件 |

**返回值：**

| 返回值 | 说明 |
|--------|------|
| `AUDIOCOMMON_RESULT_SUCCESS` | 执行成功 |
| `AUDIOCOMMON_RESULT_ERROR_SYSTEM` | 系统处理错误 |

---

### OH_AudioDebugManager_ShowSessionInfo

```c
OH_AudioCommon_Result OH_AudioDebugManager_ShowSessionInfo(
    OH_AudioDebugManager *debugManager,
    OH_AudioSessionManager *session,
    int fd);
```

显示指定 AudioSessionManager 的运行时快照。

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| debugManager | `OH_AudioDebugManager *` | 由 `OH_AudioManager_GetAudioDebugManager` 获取的句柄 |
| session | `OH_AudioSessionManager *` | 指向需要显示快照的 AudioSessionManager |
| fd | `int` | 文件描述符。fd < 0 时快照信息输出到流水线日志；fd ≥ 0 时快照信息写入 fd 指向的文件 |

**返回值：**

| 返回值 | 说明 |
|--------|------|
| `AUDIOCOMMON_RESULT_SUCCESS` | 执行成功 |
| `AUDIOCOMMON_RESULT_ERROR_SYSTEM` | 系统处理错误 |

---

### OH_AudioDebugManager_ShowSuiteInfo

```c
OH_AudioCommon_Result OH_AudioDebugManager_ShowSuiteInfo(
    OH_AudioDebugManager *debugManager,
    OH_AudioSuiteEngine *audioSuiteEngine,
    int fd);
```

显示指定 AudioSuiteEngine 的运行时快照。

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| debugManager | `OH_AudioDebugManager *` | 由 `OH_AudioManager_GetAudioDebugManager` 获取的句柄 |
| audioSuiteEngine | `OH_AudioSuiteEngine *` | 指向需要显示快照的 AudioSuiteEngine |
| fd | `int` | 文件描述符。fd < 0 时快照信息输出到流水线日志；fd ≥ 0 时快照信息写入 fd 指向的文件 |

**返回值：**

| 返回值 | 说明 |
|--------|------|
| `AUDIOCOMMON_RESULT_SUCCESS` | 执行成功 |
| `AUDIOCOMMON_RESULT_ERROR_SYSTEM` | 系统处理错误 |

---

## 依赖头文件

| 头文件 | 说明 |
|--------|------|
| `native_audio_common.h` | 定义 `OH_AudioCommon_Result` 返回值枚举 |
| `native_audiostream_base.h` | 定义 `OH_AudioRenderer`、`OH_AudioCapturer` 类型 |
| `native_audio_session_manager.h` | 定义 `OH_AudioSessionManager` 类型 |
| `native_audio_suite_engine.h` | 定义 `OH_AudioSuiteEngine` 类型 |

---

## 使用示例

```c
#include "native_audio_debug_manager.h"

// 1. 获取 Debug Manager
OH_AudioDebugManager *debugManager = NULL;
OH_AudioCommon_Result result = OH_AudioManager_GetAudioDebugManager(&debugManager);
if (result != AUDIOCOMMON_RESULT_SUCCESS) {
    // 处理错误
    return;
}

// 2. 输出应用级音频快照到日志
OH_AudioDebugManager_ShowAppInfo(debugManager, -1);

// 3. 输出 Renderer 快照到文件
int fd = open("/data/local/tmp/audio_snapshot.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
if (fd >= 0) {
    OH_AudioDebugManager_ShowRendererInfo(debugManager, renderer, fd);
    close(fd);
}
```

---

## 变更历史

| 版本 | 说明 |
|------|------|
| 26.0.0 | 首次新增 |

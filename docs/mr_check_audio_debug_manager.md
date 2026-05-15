# MR 检查清单 — native_audio_debug_manager.h

> **分支**: `feature/audio-debug-manager` → `master`  
> **仓库**: https://gitcode.com/jvgang/interface_sdk_c  
> **MR 创建页**: https://gitcode.com/jvgang/interface_sdk_c/merge_requests/new?source_branch=feature/audio-debug-manager&target_branch=master  
> **提交数**: 2  
> **变更文件**: 3 (新增1 + 修改2)  
> **变更行数**: +179  

---

## 一、提交记录

| Commit | 说明 |
|--------|------|
| `98a82e6d` | feat(audio): add native_audio_debug_manager.h with Debug Manager C API |
| `5cf444ba` | feat(audio): register native_audio_debug_manager in BUILD.gn and ndk.json |

---

## 二、变更文件清单

| 文件路径 | 类型 | 变更 |
|----------|------|------|
| `multimedia/audio_framework/audio_manager/native_audio_debug_manager.h` | **新增** | +153 行 |
| `multimedia/audio_framework/BUILD.gn` | 修改 | +2 行 |
| `multimedia/audio_framework/ohaudio.ndk.json` | 修改 | +24 行 |

---

## 三、新增 API 列表

| # | API 名称 | 参数 | 返回值 | 版本 |
|---|---------|------|--------|------|
| 1 | `OH_AudioManager_GetAudioDebugManager` | `OH_AudioDebugManager **debugManager` | `OH_AudioCommon_Result` | 26.0.0 |
| 2 | `OH_AudioDebugManager_PrintAppInfo` | `OH_AudioDebugManager *debugManager, int32_t fd` | `OH_AudioCommon_Result` | 26.0.0 |
| 3 | `OH_AudioDebugManager_PrintRendererInfo` | `OH_AudioDebugManager *debugManager, OH_AudioRenderer *renderer, int32_t fd` | `OH_AudioCommon_Result` | 26.0.0 |
| 4 | `OH_AudioDebugManager_PrintCapturerInfo` | `OH_AudioDebugManager *debugManager, OH_AudioCapturer *capturer, int32_t fd` | `OH_AudioCommon_Result` | 26.0.0 |
| 5 | `OH_AudioDebugManager_PrintLoopbackInfo` | `OH_AudioDebugManager *debugManager, OH_AudioLoopback *loopback, int32_t fd` | `OH_AudioCommon_Result` | 26.0.0 |
| 6 | `OH_AudioDebugManager_PrintSessionInfo` | `OH_AudioDebugManager *debugManager, OH_AudioSession *session, int32_t fd` | `OH_AudioCommon_Result` | 26.0.0 |
| 7 | `OH_AudioDebugManager_PrintSuiteInfo` | `OH_AudioDebugManager *debugManager, OH_AudioSuiteEngine *audioSuiteEngine, int32_t fd` | `OH_AudioCommon_Result` | 26.0.0 |

---

## 四、逐项检查

### 4.1 头文件规范检查

| 检查项 | 结果 | 说明 |
|--------|------|------|
| Apache 2.0 许可证头 | ✅ 通过 | Copyright 2026，格式与同目录其他头文件一致 |
| Include guard | ✅ 通过 | `NATIVE_AUDIO_DEBUG_MANAGER_H` |
| `@addtogroup OHAudio` 模块分组 | ✅ 通过 | 与其他 audio_manager 头文件一致 |
| `@file` / `@brief` 文件注释 | ✅ 通过 | 声明文件用途 |
| `@library libohaudio.so` | ✅ 通过 | 与 `BUILD.gn` 中 `output_name = "ohaudio"` 一致 |
| `@syscap SystemCapability.Multimedia.Audio.Core` | ✅ 通过 | 与 `BUILD.gn` 中 `system_capability` 一致 |
| `@kit AudioKit` | ✅ 通过 | |
| `@since 26.0.0` | ✅ 通过 | 所有接口均标注 |
| `extern "C"` 包裹 | ✅ 通过 | `#ifdef __cplusplus` 条件编译 |
| 尾部 `/** @} */` | ✅ 通过 | 与其他头文件格式一致 |
| 不透明结构体前向声明 | ✅ 通过 | `typedef struct OH_AudioDebugManager OH_AudioDebugManager` |
| 函数命名规范 | ✅ 通过 | `OH_AudioDebugManager_Show*Info` / `OH_AudioManager_Get*` |
| 参数 Doxygen 注释 | ✅ 通过 | `@param` + `@return` + `{@link #}` 交叉引用 |

### 4.2 C 语法检查

| 检查项 | 结果 | 说明 |
|--------|------|------|
| 头文件自包含 | ✅ 通过 | 包含 `native_audio_common.h`、`native_audostream_base.h`、`native_audio_session_manager.h`、`native_audio_suite_engine.h` |
| 类型引用完整 | ✅ 通过 | `OH_AudioCommon_Result` 来自 common、`OH_AudioRenderer`/`OH_AudioCapturer` 来自 audiostream_base、`OH_AudioSessionManager` 来自 session_manager、`OH_AudioSuiteEngine` 来自 suite_engine |
| 无 C++ 特性 | ✅ 通过 | 纯 C 兼容 |

### 4.3 注释规则检查

| 检查项 | 结果 | 说明 |
|--------|------|------|
| 每个接口均有 `@brief` | ✅ 通过 | |
| 参数说明含方向（input/output） | ✅ 通过 | `output parameter` / 指针参数语义 |
| 返回值枚举值完整 | ✅ 通过 | SUCCESS + ERROR_INVALID_PARAM / ERROR_SYSTEM |
| `{@link #}` 引用正确 | ✅ 通过 | 引用已有类型和枚举值 |
| `fd` 参数说明完整 | ✅ 通过 | 包含 fd < 0 和 fd ≥ 0 两种情况 |

### 4.4 JSON 文件检查

| 检查项 | 结果 | 说明 |
|--------|------|------|
| 6 个 API 已注册到 `ohaudio.ndk.json` | ✅ 通过 | `first_introduced: "26.0.0"` |
| API 名称与头文件一致 | ✅ 通过 | 逐条核对 |
| JSON 格式合法 | ✅ 通过 | 尾部逗号处理正确 |

### 4.5 BUILD.gn 检查

| 检查项 | 结果 | 说明 |
|--------|------|------|
| `ohaudio_header` sources 已添加 | ✅ 通过 | `audio_manager/native_audio_debug_manager.h` |
| `system_capability_headers` 已添加 | ✅ 通过 | `ohaudio/native_audio_debug_manager.h` |
| 字母排序位置正确 | ✅ 通过 | 插入在 `native_audio_device_enhance_manager.h` 之前 |

### 4.6 ndk_targets.gni 检查

| 检查项 | 结果 | 说明 |
|--------|------|------|
| 是否需要新增 target | ❌ 不需要 | 已有 `//interface/sdk_c/multimedia/audio_framework:libohaudio_nd` 和 `ohaudio_header`，新头文件通过现有 target 注册 |

### 4.7 Library 声明一致性检查

| 检查项 | 结果 | 说明 |
|--------|------|------|
| `@library` 声明 | `libohaudio.so` | |
| `BUILD.gn` output_name | `ohaudio` → `libohaudio.so` | ✅ 一致 |

---

## 五、依赖类型交叉验证

| 类型 | 来源头文件 | 声明方式 |
|------|-----------|---------|
| `OH_AudioCommon_Result` | `native_audio_common.h` | enum 枚举 |
| `OH_AudioDebugManager` | `native_audio_debug_manager.h` | typedef struct 前向声明 |
| `OH_AudioRenderer` | `native_audio_debug_manager.h` | typedef struct OH_AudioRendererStruct 前向声明 |
| `OH_AudioCapturer` | `native_audio_debug_manager.h` | typedef struct OH_AudioCapturerStruct 前向声明 |
| `OH_AudioLoopback` | `native_audio_debug_manager.h` | typedef struct OH_AudioLoopbackStruct 前向声明 |
| `OH_AudioSession` | `native_audio_debug_manager.h` | typedef struct OH_AudioSessionStruct 前向声明 |
| `OH_AudioSuiteEngine` | `native_audio_debug_manager.h` | typedef struct OH_AudioSuiteEngineStruct 前向声明 |

---

## 六、兼容性影响评估

- **评估结果**: N（无兼容性影响）
- **原因**: 纯新增 API，不修改任何已有接口签名、参数、返回值，不影响已有代码编译和运行

---

## 七、待确认项

| # | 待确认项 | 状态 |
|---|---------|------|
| 1 | 实现代码是否已合入（头文件声明需要实现侧支撑） | ⏳ 待确认 |
| 2 | L0 用例是否已新增 | ⏳ 待确认 |
| 3 | API 参考文档是否需刷新（docs 仓 PR） | ⏳ 待确认 |

---

## 八、MR 描述（可直接粘贴到 GitCode）

```
### 相关的Issue

无

### 原因（目的、解决的问题等）

为音频模块新增 Debug Manager C API，提供音频运行时快照功能，支持开发者获取应用级、Renderer、Capturer、Session、SuiteEngine 等组件的运行时状态信息，便于调试和问题定位。

### 描述（做了什么，变更了什么）

1. **新增头文件** `multimedia/audio_framework/audio_manager/native_audio_debug_manager.h`
   - 定义 `OH_AudioDebugManager` 不透明结构体
   - 新增 7 个 C API 接口：
     - `OH_AudioManager_GetAudioDebugManager` — 获取 Debug Manager 单例句柄
     - `OH_AudioDebugManager_PrintAppInfo` — 打印应用级音频运行时快照
     - `OH_AudioDebugManager_PrintRendererInfo` — 打印 AudioRenderer 运行时快照
     - `OH_AudioDebugManager_PrintCapturerInfo` — 打印 AudioCapturer 运行时快照
     - `OH_AudioDebugManager_PrintLoopbackInfo` — 打印 AudioLoopback 运行时快照
     - `OH_AudioDebugManager_PrintSessionInfo` — 打印 AudioSession 运行时快照
     - `OH_AudioDebugManager_PrintSuiteInfo` — 打印 AudioSuiteEngine 运行时快照

2. **更新 BUILD.gn** — 在 ohaudio_header 的 sources 和 system_capability_headers 中注册新头文件

3. **更新 ohaudio.ndk.json** — 注册 6 个新 API 符号，first_introduced: "26.0.0"

### 自检结果
- [x] 是否通过C语法扫描
- [x] 是否通过注释规则扫描
- [x] 是否更新json文件
- [ ] 实现代码是否已经合入
- [x] 目标是否已经添加到interface/sdk_c仓ndk依赖目标(ndk_targets.gni)里（已有target，无需新增）
- [x] 头文件library声明与SDK so库名称一致（libohaudio.so）

### 兼容性影响评估（Y/N）
- [x] N — 纯新增API，无兼容性影响

### L0新增用例自检结果
- [ ] 是，有新增L0用例，且完成自检
- [x] 否

### API参考文档影响评估
- [ ] 是，已刷新API参考文档
- [x] 否，不涉及刷新API参考文档
```

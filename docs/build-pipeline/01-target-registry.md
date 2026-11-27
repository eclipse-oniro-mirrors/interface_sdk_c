# 01 目标注册表（`interface/sdk_c/ndk_targets.gni`）

> 对应 [00-总览](./00-overview.md)「环节 01」，GN 生成期的目标注册表。
> 被 `build/ohos/ndk/BUILD.gn:26` import，产出 `all_ndk_targets_list` / `all_lite_ndk_targets_list`，
> 供 `_parse_ndk_headers` / `_collect_ndk_syscap` 等 action 作为 deps。

## 1. 环节职责

| 项 | 内容 |
| -- | ---- |
| 作用 | 把全仓 285+ 个 NDK 库 / 头文件目标、基础库、sysroot、工具链集中注册为两组列表 |
| 归属领域 | sdk（interface/sdk_c 仓） |
| 消费者 | `build/ohos/ndk/BUILD.gn` 的 action / group |
| 覆盖范围 | 约 123 个模块目录，`graphic` / `multimedia` / `filemanagement` / `security` 等子系统 |

## 2. 目标分类

### 2.1 `_ndk_library_targets`（库 + 头文件，约 285 条）

每个条目形如 `"//interface/sdk_c/<子系统>/<模块>:<目标名>"`，目标名两类：

| 类型 | 命名 | 数量（约） | 由哪个模板生成 |
| ---- | ---- | ---------- | -------------- |
| 库目标 | `:libxxx_ndk` / `:libxxx` | 141 | [2.1 `ohos_ndk_library`](./02-subsystem-build.md#ohos_ndk_library) |
| 头文件目标 | `:xxx_header` / `:ohxxx_header` | 144 | [2.2 `ohos_ndk_headers`](./02-subsystem-build.md#ohos_ndk_headers) |

> 特殊条目：`//interface/sdk_c/third_party/musl/ndk_script:copy_compatible_config`
> （musl 兼容性配置拷贝）、`//interface/sdk_c/third_party/musl/ndk_script/adapter:libc_ndk_lite`（lite libc）。

### 2.2 其余 NDK 目标组

| 变量 | 内容 | 作用 |
| ---- | ---- | ---- |
| `_ndk_lite_library_targets` | `libc_ndk_lite` | lite（cortex-m / riscv32）版 libc |
| `_ndk_base_libs` | `libc_ndk`、`musl_ndk_libs_{arm32,aarch64,x86_64}`、`ndk_toolchain` | libc 库 + crt 启动文件 + LLVM 工具链 |
| `_ndk_sysroot_uapi` | `musl_sysroot` | musl libc sysroot 头文件 → `sysroot/usr/include` |
| `_ndk_sysroot_lite_uapi` | `musl_sysroot_lite` | lite sysroot → `sysroot_lite/usr/include` |
| `_ndk_cmake` | `//build/ohos/ndk:ndk_cmake_files` + 各平台 `prebuilts/cmake/...` 拷贝 | cmake 配置 + 预置 cmake 二进制 |
| `_ndk_ninja` | `//prebuilts/build-tools/...:linux_ninja_copy` 等 | 各平台 ninja 二进制 |
| `_ndk_tee_build_tool` | `//base/tee/tee_dev_kit/sdk/build:tee_ndk_ta_linux_compile` | TEE 开发套件（TA 编译工具） |

## 3. 聚合列表

```
all_ndk_targets_list =
    _ndk_library_targets + _ndk_base_libs + _ndk_sysroot_uapi +
    _ndk_cmake + _ndk_ninja + _ndk_tee_build_tool + _ndk_sysroot_lite_uapi

all_lite_ndk_targets_list =
    _ndk_lite_library_targets + _ndk_base_libs + _ndk_sysroot_lite_uapi
```

平台专用目标按开关追加：

| 开关 | 追加目标 |
| ---- | -------- |
| `build_windows_ndk_target` | `//interface/sdk_c/third_party/musl/ndk_script:windows_x86_64` |
| `build_mac_ndk_target` | `...:darwin_arm64` / `...:darwin_x86_64`（按 `host_cpu`） |
| `build_linux_ndk_target` | `...:linux_arm64` / `...:linux_x86_64`（按 `host_cpu`） |
| `build_ohos_ndk_target` | `...:ohos_arm64` |
| `ndk_platform == "default"`（兜底） | 按 `host_os` / `host_cpu` 选 windows / linux / ohos 组合 |

## 4. 消费关系

> 各 action 依赖的目标列表（`all_ndk_targets_list` / `all_lite_ndk_targets_list`，见 [3. 聚合列表](#3-聚合列表)）
> 由 `ohos_ndk_library` / `ohos_ndk_headers` 等模板实例构成，模板机制详见 [02-子系统BUILD](./02-subsystem-build.md)。

| 消费者（`build/ohos/ndk/BUILD.gn`） | 依赖的列表 | 消费后动作（详细环节） |
| ----------------------------------- | ---------- | ---------------------- |
| `_parse_ndk_headers`（82-96 行）     | `all_ndk_targets_list`（先拷贝齐所有头文件再加工） | [03 头文件加工](./03-header-processing-00-overview.md) |
| `_collect_ndk_syscap`（57-80 行）    | `all_ndk_targets_list`（读取每个目标的 `.build_config`） | [04 syscap 收集](./04-syscap-and-ani-cleanup.md) |
| `_parse_lite_ndk_headers`（98-113 行） | `all_lite_ndk_targets_list` | [03 头文件加工（lite 分支）](./03-header-processing-00-overview.md) |
| `_collect_lite_ndk_syscap`（115-138 行） | `all_lite_ndk_targets_list` | [04 syscap 收集（lite 分支）](./04-syscap-and-ani-cleanup.md) |

## 5. 相关文件

| 文件 | 作用 |
| ---- | ---- |
| `interface/sdk_c/ndk_targets.gni` | 目标注册表（本环节） |
| `build/ohos/ndk/BUILD.gn` | import 注册表并串起后续 action 链 |
| `build/ohos_var.gni` | `build_windows_ndk_target` 等开关定义（430-437 行） |
| `build/ohos/ndk/scan_ndk_targets.py` | 全量扫描各子系统 `BUILD.gn` 中的 `ohos_*` 模板实例并生成 `all_ndk_targets` group。其 `ALL_NDK_TEMPLATES_NAMES`（36-40 行）中的 `ohos_ndk_prebuilt_library` 属**多余配置**：该模板为预留模板、全仓无调用实例，故扫描结果中永远匹配不到该模板目标，仅作占位保留 |

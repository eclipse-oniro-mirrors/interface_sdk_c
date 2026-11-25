# C API / NDK 构建流水线知识索引

> 本文档供 AI 在修改 SDK 构建脚本、排查 Native SDK（NDK）打包产物时使用。
> AI 通过读取 interface 仓库根目录的 AGENTS.md 发现并加载本文件。

本索引是 `docs/build-pipeline/` 下 C API / NDK 构建文档树的稳定入口：
从 `interface/sdk_c` 源码头文件与 `.ndk.json` 开始，经目标注册、子系统
`BUILD.gn` 模板、头文件加工、syscap 收集与 ANI 清理、汇聚检查、打包归档，
到最终 `native-<os>-<arch>-<version>.zip` 的完整流水线。由根
[AGENTS.md](../AGENTS.md) 的「API Design Knowledge Index」注册。文档若移动，
只改本索引与本索引的上游链接。

## 适用范围与修改限制

本索引及 `docs/build-pipeline/` 文档树**只用于 C API / NDK 构建**任务：对
NDK 产物的头文件加工、库生成、syscap / ANI 清理、归档打包等环节定位。其他任务
（API 元数据、命名规范、声明注释等）请走根 [AGENTS.md](../AGENTS.md) 的其他
知识域。

依据本索引定位修改点时，注意脚本归属：

- **sdk_c 仓负责**（`interface/sdk_c`）：`ndk_targets.gni` 目标注册表、
  头文件加工三步（`build-tools/parse_native_headers.py`、
  `header_processor.py`、`parse_interfaces_since.py`）、
  ANI 清理（`build-tools/clean_ndk_ani.py`）。
- **build 仓负责**（`//build`）：NDK 模板（`ohos/ndk/ndk.gni`）、
  action 编排（`ohos/ndk/BUILD.gn`）、syscap 收集 / 文档 / Notice / 归档等脚本
  （`ohos/ndk/collect_ndk_syscap.py`、`generate_ndk_docs.py`、
  `archive_ndk.py` 等），以及 SDK 聚合（`ohos/sdk/BUILD.gn`、
  `core/gn/BUILD.gn`）。

跨仓脚本只读参考、不越权修改；归属有疑义时先确认再动。

## 阅读索引

| 知识域 | 何时读 | 入口 |
|--------|--------|------|
| 全链路总览 | 初次了解 NDK 打包流程，或按环节定位脚本/路径 | [00-总览](./build-pipeline/00-总览.md) |
| 01 目标注册 | `interface/sdk_c/ndk_targets.gni` 目标列表、消费关系、模板对应 | [01-目标注册表](./build-pipeline/01-目标注册表.md) |
| 02 子系统 BUILD | `build/ohos/ndk/ndk.gni` 各模板（`ohos_ndk_library` / `ohos_ndk_headers` / `ohos_ndk_copy` / `ohos_ndk_prebuilt_library` / `ohos_ndk_lite_library`）机制与工具链 | [02-子系统BUILD](./build-pipeline/02-子系统BUILD.md) |
| 环节 03 头文件加工（总览） | `_parse_ndk_headers` / `_parse_lite_ndk_headers` 并行流程与三步概览 | [03-头文件加工-00总览](./build-pipeline/03-头文件加工-00总览.md) |
| 03.1 删除系统 API | `header_processor.py` 裁剪 `@systemapi` 声明 | [03-头文件加工-01删除系统API](./build-pipeline/03-头文件加工-01删除系统API.md) |
| 03.2 API 版本校验 | `parse_interfaces_since.py` 校验 `@since` 不高于构建版本 | [03-头文件加工-02API版本校验](./build-pipeline/03-头文件加工-02API版本校验.md) |
| 03.3 注入版本可用性宏 | `HeaderProcessor` 为带 `@since` 声明注入 `availability` 宏 | [03-头文件加工-03API版本宏注入](./build-pipeline/03-头文件加工-03API版本宏注入.md) |
| 04 syscap 收集 + ANI 清理 | `collect_ndk_syscap.py` 汇总映射表、`clean_ndk_ani.py` 剔除 ani 头文件 | [04-syscap与ANI清理](./build-pipeline/04-syscap与ANI清理.md) |
| 05 汇聚与检查 | `all_ndk_targets` group、doxygen 文档生成、Notice 合规 | [05-汇聚与检查](./build-pipeline/05-汇聚与检查.md) |
| 06 打包归档 | `archive_*_ndk` ×5 平台、`archive_ndk.py` 生成 `native-*.zip` | [06-打包归档](./build-pipeline/06-打包归档.md) |
| 07 SDK 聚合 | `build_ohos_sdk` 聚合 NDK + TS SDK、完整性校验、签名与 Notice | [07-SDK聚合](./build-pipeline/07-SDK聚合.md) |

## 使用约定

- 流水线顺序即文档编号 00~07；每个环节文档顶部标注对应 action / 脚本与
  BUILD.gn / 脚本行号，作为定位证据。
- 两个 `_parse_*_ndk_headers` 为独立 action、ninja 并行执行，lite 分支仅追加
  `--skip-version-macro`（跳过 03.3），不要误认为串行依赖。
- 路径占位 `out/<产品>/...` 为构建产物；不手改生成物，修改应回到源仓
  （`interface/sdk_c` / `build`）。
- 涉及构建参数（`sdk_build_public` / `sdk_build_check_level` /
  `check_ndk_signature` / `ndk_check_header` 等）时，以各环节文档说明为准。

# AGENTS.md

## Repository Overview

OpenHarmony C API declaration repository. The repository stores public `.h`
declaration files and the tooling used to build and validate the Native SDK.

## C API 元数据格式

C API 元数据 schema、字段含义、类型分支和使用样例，详见
[docs/AGENTS-api-metadata.md](./docs/AGENTS-api-metadata.md)。

## 相关知识库与规范

- C API 命名规范：[docs/capi_naming.md](./docs/capi_naming.md)
- C API 用户指导：[docs/user_guide.md](./docs/user_guide.md)
- 新增 C API 构建目标：[docs/howto_add.md](./docs/howto_add.md)

## Important Notes

- C API 是系统与应用之间的 C 语言契约，接口稳定性和 ABI 兼容性必须优先考虑。
- 新增或修改 API 时，应遵守本仓文档注释规范和 C API 编码规范。
- 元数据格式属于 API 知识库，不改变现有头文件构建流程。

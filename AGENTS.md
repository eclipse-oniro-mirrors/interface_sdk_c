# AGENTS.md

## Repository Overview

OpenHarmony C API declaration repository. The repository stores public `.h`
declaration files and the tooling used to build and validate the Native SDK.

## API Design Knowledge Index

AI agents and tools must use this root `AGENTS.md` as the stable knowledge entry.
They must not assume or hardcode repository-internal paths; if a document moves,
update only the links in this index.

| Knowledge area | Required when | Entry |
|----------------|---------------|-------|
| C API metadata format and schema | generating, validating, or consuming C metadata | [AGENTS-api-metadata.md](./docs/AGENTS-api-metadata.md) |
| C API naming and ABI rules | naming a new symbol or reviewing public C API design | [capi_naming.md](./docs/capi_naming.md) |
| C API declaration-comment and user-facing API rules | writing or validating Doxygen/API documentation | [user_guide.md](./docs/user_guide.md) |
| Adding C API build targets and NDK version metadata | adding a library/header target or determining introduction version | [howto_add.md](./docs/howto_add.md) |

The C metadata guide dynamically links to:

- Schema: `c-api-metadata.schema.json`
- Example: `c-api-metadata.example.yaml`

Consumers must resolve those artifacts through
[AGENTS-api-metadata.md](./docs/AGENTS-api-metadata.md), not by hardcoding their
paths.

For API contract generation, the metadata-format entry is mandatory; also load
the naming/comment/build entries that apply to the task. A deterministic
repository rule must be used directly and cited as the evidence source; do not
ask the developer to reconfirm a fact already resolved by this knowledge index.

## Important Notes

- C API 是系统与应用之间的 C 语言契约，接口稳定性和 ABI 兼容性必须优先考虑。
- 新增或修改 API 时，应遵守本仓文档注释规范和 C API 编码规范。
- 元数据格式属于 API 知识库，不改变现有头文件构建流程。

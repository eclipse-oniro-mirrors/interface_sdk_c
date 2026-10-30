# C API 元数据格式

> 本文档定义 C API 元数据的机器可读格式。schema 位于
> [api-metadata/c-api-metadata.schema.json](./api-metadata/c-api-metadata.schema.json)，
> 使用示例位于 [api-metadata/c-api-metadata.example.yaml](./api-metadata/c-api-metadata.example.yaml)。
>
> 该格式属于 interface_sdk_c 仓 API 知识库的一部分，用于描述 `.h` 声明、
> Doxygen 注释、参数方向、内存所有权、错误码和设备能力，供 spec 生成、
> 头文件生成和后续一致性校验复用。

## 1. 设计目标

C API 元数据按 C 语言实体建模，而不是把所有声明都塞进一个 flat 对象：

- 每个 API 使用 `kind` 标识类型。
- 公共字段统一定义。
- function / callback / struct / enum / typedef / macro / variable 各有专属结构。
- 保留 `declaration` 原始文本，便于人工核对和 diff。
- 将参数方向、指针层级、所有权、错误码、返回语义结构化，支持机器校验。
- 双语文本使用 `en` / `zh` 成对维护，与 Doxygen 中文归档证据对应。

## 2. 文件与版本

| 文件 | 作用 |
|------|------|
| `docs/api-metadata/c-api-metadata.schema.json` | JSON Schema 2020-12 格式定义 |
| `docs/api-metadata/c-api-metadata.example.yaml` | 覆盖 C API 主要类型的样例 |
| `docs/AGENTS-api-metadata.md` | 本说明文档 |

当前版本：

```text
schemaVersion: 1.0.0
```

修改不兼容字段时必须递增主版本；新增可选字段可以递增次版本。

## 3. 顶层结构

```yaml
schemaVersion: "1.0.0"
language: c
source:
  repository: interface_sdk_c
  branch: master
  commit: "<sha>"
  path: sensors/sensor
header:
  path: sensors/sensor/oh_sensor.h
  kit: SensorServiceKit
  library: libohsensor.so
  syscap: SystemCapability.Sensors.Sensor
  license: Apache-2.0
  includes:
    - sensors/sensor/oh_sensor_type.h
  macroGuard: OH_SENSOR_H
common:
  accessLevel: public
  since: "11"
  syscap: SystemCapability.Sensors.Sensor
  permissions: []
  library: libohsensor.so
apis:
  - kind: function
    id: sensor.get_infos
    name: OH_Sensor_GetInfos
    qualifiedName: OH_Sensor_GetInfos
    declaration: Sensor_Result OH_Sensor_GetInfos(Sensor_Info **infos, uint32_t *count)
    filePath: sensors/sensor/oh_sensor.h
    startLine: 48
    endLine: 49
    parameters: []
    returnType:
      text: Sensor_Result
      semantic: error-code
```

- `source` 描述元数据对应的声明来源。
- `header` 描述头文件级事实，包括 Kit、库、syscap、include、宏保护。
- `common` 只描述默认值或继承策略，不替代单个 API 的显式字段。
- `apis` 是 API 实体数组，每个条目是一个 discriminated union。

## 4. 公共字段

| 字段 | 必填 | 说明 |
|------|------|------|
| `kind` | 是 | API 实体类型 |
| `id` | 是 | 元数据内部稳定 ID |
| `parentId` | 否 | 父级或逻辑分组 ID，顶层可为 `null` |
| `name` | 是 | C 标识符名称 |
| `qualifiedName` | 是 | 完整限定名，C 中通常等同符号名 |
| `declaration` | 是 | 原始声明文本 |
| `filePath` | 是 | 头文件路径 |
| `startLine` / `endLine` | 是 | 声明位置 |
| `changeKind` | 否 | `added` / `modified` / `removed` / `deprecated` |
| `isExported` | 否 | 是否进入公开头文件或 NDK 符号列表 |
| `accessLevel` | 否 | `public` / `system` / `inner` |
| `kit` | 否 | 所属 Kit |
| `library` | 否 | 关联 so 库 |
| `since` | 否 | 引入版本 |
| `syscap` | 否 | 关联系统能力 |
| `permissions` | 否 | 调用所需权限 |
| `deprecated` / `useInstead` | 否 | 废弃信息 |
| `description` | 否 | 双语说明 |
| `deviceSupport` | 否 | 支持设备列表 |
| `deviceDifferences` | 否 | 设备行为差异 |
| `specRefs` | 否 | 关联 AC / BR / SC |
| `confirmation` | 否 | 事实性字段确认记录 |
| `attributionParts` | 否 | 归属部件 |

C 的 `description` 采用双语自由文本。参数、返回值、错误码和内存所有权有独立
结构化字段，不能只放在 `description` 里。

## 5. API 类型

| `kind` | 专属核心字段 | 说明 |
|--------|--------------|------|
| `function` | `parameters`, `returnType`, `errorCodes`, `isVariadic`, `callingConvention`, `memoryOwnership`, `threadSafety` | C 函数 |
| `struct` | `isOpaque`, `fields`, `sizeBytes`, `alignment` | 结构体；opaque struct 的 `fields` 为空 |
| `union` | `members`, `sizeBytes`, `alignment` | C union；`members` 使用字段结构 |
| `enum` | `underlyingType`, `isFlags`, `members` | 枚举 |
| `enumMember` | `value`, `initializer`, `valueType`, `ownerEnum` | 枚举成员 |
| `typedef` | `aliasedType`, `typedefKind`, `targetApi` | 类型别名 |
| `callback` | `parameters`, `returnType`, `callingConvention` | 函数指针/回调类型 |
| `macro` | `parameters`, `expression`, `isFunctionLike` | 宏 |
| `variable` | `cType`, `value`, `initializer`, `isConst`, `linkage` | 导出变量 |

## 6. C 专属语义

### 6.1 参数

每个参数必须包含：

- `name`
- `cType`
- `direction`: `input` / `output` / `input-output`

建议同时填写：

- `isPointer`
- `isConst`
- `isNullable`
- `required`
- `description`
- `constraints`
- `memoryOwnership`

C API 的输出参数不能用 ArkTS 的 `returnType` 替代；`output` / `input-output`
参数是函数契约的一部分。

### 6.2 返回值

`returnType` 必须包含 `text` 和 `semantic`：

```yaml
returnType:
  text: Sensor_Result
  semantic: error-code
```

`semantic` 常用取值：

- `void`
- `primitive`
- `error-code`
- `pointer`
- `handle`
- `boolean`
- `other`

返回指针或句柄时必须描述内存所有权和释放函数，避免生成注释时丢失生命周期约束。

### 6.3 错误码

错误码至少包含：

```yaml
constant: SENSOR_PARAMETER_ERROR
code: 401
condition: Parameter verification fails.
message:
  en: Parameter error.
  zh: 参数错误。
```

`constant` 是 C 宏或枚举名，`code` 是数值。生成和校验时两者都必须与
`enum` / `#define` 对齐。

## 7. 与现有解析器字段的对应

| 解析器输出 / C 声明 | 元数据字段 |
|----------------------|------------|
| `filePath` | `filePath` |
| `start_line` / `end_line` | `startLine` / `endLine` |
| 函数符号 | `kind=function`, `name`, `declaration` |
| 参数 | `parameters[]` |
| 返回类型 | `returnType` |
| `typedef enum` | `kind=enum` |
| 枚举成员 | `kind=enumMember` |
| `typedef struct` | `kind=struct` |
| `typedef union` | `kind=union` |
| 函数指针 typedef | `kind=callback` |
| 普通 typedef | `kind=typedef` |
| 宏 | `kind=macro` |
| 导出变量 | `kind=variable` |
| Doxygen `@brief` / 中文说明 | `description.en` / `description.zh` |
| `@param` | `parameters[].description` |
| `@return` | `returnType.description` |
| `@permission` | `permissions` |
| `@syscap` | `syscap` |
| `@since` | `since` |
| NDK 符号版本 | `since` / `changeKind` |

## 8. 生成与校验边界

- 生成 `.h` 时必须逐字段消费本元数据。
- C API 只建模 C 语言实体；不建模 C++ `class` 或 `namespace`。
- `declaration` 只作为原始文本和兜底比对，不得替代参数、返回值、错误码结构。
- `since`、权限、库、syscap、设备差异等事实性字段必须保留 `confirmation`。
- 生成器不得用既有头文件填补元数据缺口；缺口应回溯到 spec 阶段补充确认。
- 校验器应先检查 schema，再比较元数据、头文件和 Doxygen 注释。
- C 语法、类型、ABI 和编译结果仍由本仓工具链与 CI 负责，元数据校验不替代
  编译检查。

## 9. 最小校验规则

1. `schemaVersion` 必须为当前支持版本。
2. `apis[].id` 必须唯一。
3. `parentId` 引用的 ID 必须存在。
4. `declaration` 非空且不得是占位符。
5. function / callback 必须有 `parameters` 与 `returnType`。
6. `parameters[].direction` 必填，输出参数必须有明确说明。
7. 返回 `pointer` / `handle` 时必须有 `memoryOwnership`。
8. enum 与 enumMember 的 `members` / `ownerEnum` 必须互相闭合。
9. 错误码 `constant` 与 `code` 必须能对应到 enum 或宏。
10. 双语描述中一方存在时另一方也应存在，避免中英文证据漂移。

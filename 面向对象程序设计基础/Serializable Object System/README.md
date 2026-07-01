# Serializable Object System

Problem 1.24：实现可序列化对象系统，支持 JSON 子集（object、array、string、number、boolean、null）的序列化与反序列化，并使用面向对象的 `JsonValue` 类层次结构。

## 团队成员

| 姓名 | 主要职责 |
|-----|----------|
| 司汶蓬 | 模型层、序列化、工程集成、报告统稿 |
| 付文聪 | 反序列化（解析）、测试用例、边界样例 |


## 分工说明

### 组长：模型 + 序列化 + 工程集成

| 任务 | 说明 |
|------|------|
| M0 接口对齐 | 与组员在 `json_api.h` 中约定 `serialize` / `parse`、数字类型、转义规则、错误返回方式 |
| `JsonValue` 层次 | 基类 + `JsonNull` / `JsonBool` / `JsonNumber` / `JsonString` / `JsonArray` / `JsonObject` |
| 序列化 | 递归输出 JSON；字符串转义至少支持 `\"` `\\` `\n` `\r` `\t` |
| 工程与演示 | 维护 VS 工程；`main.cpp` 中构造样例并打印 JSON；组员完成后接入 parse 回读 |
| 管理 | 里程碑检查、合并冲突、与组员对齐异常/错误码策略 |

**主要负责文件：** `json_api.h`、`json_value.h`、`json_value.cpp`、`json_serialize.h`、`json_serialize.cpp`、`main.cpp`（演示部分）

### 组员：反序列化 + 测试

| 任务 | 说明 |
|------|------|
| 词法分析 | 跳过空白；识别 `{}[]:,`、字符串、数字、`true`/`false`/`null` |
| 语法分析 | 递归下降：`parseValue` → `parseObject` / `parseArray` / 字面量等 |
| 字符串 | 反转义；至少正确处理 `\` 与 `\"`（与序列化互逆） |
| 错误处理 | 统一 `ParseError`（含错误位置），非法输入不崩溃 |
| 测试 | Round-trip；负例（缺逗号、尾逗号、错误转义、截断输入等） |

**主要负责文件：** `json_parse.h`、`json_parse.cpp`；与组长共同维护 `main.cpp`（测试部分）

## 里程碑

| 阶段 | 产出 | 负责人 |
|------|------|--------|
| M0 对齐 | API、类型范围、数字与转义范围 | 两人 |
| M1 可运行骨架 | 子类齐全 + 序列化 + `main` 能打印 JSON | 组长 |
| M2 解析 MVP | 能解析 M1 输出格式的 JSON | 组员 |
| M3 硬化 | 负例、边界、round-trip、代码整理 | 两人 |
| M4 交付 | 演示、分工说明、设计/测试说明 | 组长统稿，组员补测试章节 |

## 工程结构

```
json_api.h          # 对外接口约定（serialize / parse 等）
json_value.h/.cpp   # JsonValue 基类及六种 JSON 类型子类
json_serialize.h/.cpp   # 序列化：内存树 → JSON 字符串
json_parse.h/.cpp   # 反序列化：JSON 字符串 → 内存树
main.cpp            # 演示与测试入口
```

**协作约定：** 尽量避免两人同时修改同一文件；每日简短同步是否变更 `JsonObject` 存储结构或错误返回类型。

## M0 接口约定（待两人填写确认）

- 序列化：`std::string serialize(const JsonValue&)` 或 `JsonValue::toJson() const` → （选定：________）
- 反序列化：成功返回 `std::unique_ptr<JsonValue>`；失败返回 → （选定：________）
- 数字类型：`double` → （是 / 否）
- 对象键：UTF-8 字符串字面量 → （是 / 否）
- 科学计数法：→ （支持 / 不支持）
- 循环引用：→ （不支持，未定义行为）

## 验收清单

- [ ] 六种 JSON 值类型均可构造、序列化、反序列化
- [ ] 嵌套 object/array 在合理深度内正常工作
- [ ] 字符串转义与序列化/反序列化互逆
- [ ] 非法 JSON 有明确错误提示，程序不崩溃
- [ ] Visual Studio 可一键编译运行

## 构建

需使用 Visual Studio 2026 打开 `Serializable Object System.slnx` 并编辑，随时同步至github

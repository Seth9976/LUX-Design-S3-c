# Lux AI Season 3 - C Starter Kit

这是Lux AI Season 3比赛的C语言入门套件。

## 环境要求

- GCC编译器
- Make工具
- json-c库 (用于JSON解析)

## 安装依赖

在Ubuntu/Debian系统上:

```bash
sudo apt-get update
sudo apt-get install build-essential libjson-c-dev
```

## 编译

```bash
make
```

## 运行对战

使用提供的Python包装器运行对战:

```bash
python main.py
```

或者直接使用luxai-s3命令:

```bash
luxai-s3 "make run" "make run" --out=replay.json
```

## 代码结构

- `src/main.c` - 主程序入口
- `src/agent.c` - AI代理实现
- `src/lux/` - Lux游戏相关工具函数和数据结构
  - `kit.c` - 核心游戏数据结构
  - `utils.c` - 工具函数

## 开发指南

1. 主要的AI逻辑在`src/agent.c`中实现
2. 使用`EnvConfig`结构体获取游戏配置
3. 使用`Observation`结构体获取游戏状态
4. 返回`Actions`结构体指定单位行动

## 许可证

Apache License 2.0

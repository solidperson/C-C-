# C / 嵌入式 C 学习记录

每天一课，代码 + 练习 + 提交。

## 环境

- 编译器：gcc / g++ 16.2.0（MSYS2 UCRT64），`D:\msys64\ucrt64\bin`
- 调试：gdb（F5 断点调试，配置见 `.vscode/launch.json`）
- 编辑器：VS Code + C/C++ 插件 + Code Runner

## 目录约定

```
dayNN_basics.c     第 N 天的课程（每个知识点单独一块，带注释）
dayNN_exercises.c  第 N 天的练习题（TODO 处填代码）
dayNN_answers.c    第 N 天练习题的参考答案（卡住再看）
学习日志.md          每天一行进度记录
.vscode/          编译任务、调试配置、IntelliSense
提交.cmd           一键提交并推送
```

## 当前进度

| 天 | 课程 | 练习 | 状态 |
|---|---|---|---|
| Day 1 | `day01_basics.c`：变量与类型 / printf / 数组 / for / 函数 / while与if / 指针 | `day01_exercises.c` 三道题 | 进行中 |

## 怎么跑

1. 打开 `.c` 文件，右键 → Run Code（推荐，中文不乱码）
2. `Ctrl+Shift+B` 编译，再手动运行同目录 exe
3. 命令行：

```cmd
cd /d D:\c-study
gcc -Wall -Wextra -g day01_basics.c -o day01_basics.exe
day01_basics.exe
```

## 怎么调试

打开文件 → 行号左侧点红点 → `F5` → 选「调试当前C文件 (gdb)」→ 左侧变量面板看值，`F10` 单步。

## 每天收工

双击 `提交.cmd`，或手动：

```cmd
git add .
git commit -m "Day 1：基础语法与三道练习"
git push
```

编译产物（`*.exe`、`*.o`）已被 `.gitignore` 排除。

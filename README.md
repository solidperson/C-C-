# C / 嵌入式 C 学习记录

每天写的 C 语言、数据结构、嵌入式 C 练习代码都提交到这里，按天提交、可回溯。

## 环境

- 编译器：gcc / g++ 16.2.0（MSYS2 UCRT64 版），路径 `D:\msys64\ucrt64\bin`
- 调试器：gdb（`D:\msys64\ucrt64\bin\gdb.exe`）
- 构建：mingw32-make
- 编辑器：VS Code + C/C++ 插件 + Code Runner

## 课程进度

| 课时 | 文件 | 主题 | 状态 |
|---|---|---|---|
| 第 1 课 | `lesson01_basics.c` | 变量、数组、循环、函数、指针初体验 | 已完成 |
| 第 2 课 | `lesson02_operators.c` | 运算符、类型转换、位运算、分支 | 已完成 |
| 第 3 课 | `lesson03_embedded_basics.c` | 定宽类型、位操作、volatile、寄存器指针、位域、字节序、对齐 | 已完成 |
| 练习 | `exercises/ex01.c` | 第一至三课综合练习 | 待作答 |

完整学习路线见 [`嵌入式C学习路线.md`](./嵌入式C学习路线.md)。

## 目录结构

```
lesson01_basics.c            第 1 课
lesson02_operators.c         第 2 课
lesson03_embedded_basics.c   第 3 课
exercises/                   练习题
.vscode/                     VS Code 配置（编译任务、调试配置、IntelliSense）
嵌入式C学习路线.md           学习路线
```

## 三种运行方式

1. 打开 `.c` 文件，右键 → Run Code（Code Runner，已配好中文输出）
2. Ctrl+Shift+B 编译，再手动运行同目录的 exe
3. 命令行：

```cmd
cd /d D:\c-study
gcc lesson01_basics.c -o lesson01_basics.exe
lesson01_basics.exe
```

## 断点调试

打开文件 → 行号左侧点红点 → F5 → 选择「调试当前C文件 (gdb)」或「调试当前C++文件 (gdb)」。

## 每天怎么上传

双击仓库根目录的 `提交.cmd`，会自动带上日期提交并推送。或者手动：

```cmd
cd /d D:\c-study
git add .
git commit -m "第X课：今天的主题"
git push
```

`*.exe`、`*.o` 等编译产物已在 `.gitignore` 里排除，不会上传。

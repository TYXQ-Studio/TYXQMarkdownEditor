# TYXQMarkdownEditor

## 项目介绍

**软件名称：**

TYXQMarkdownEditor

**功能点描述：**

> 蓝色为可能有一定难度的功能。

- 核心功能

  - 编辑器
    - 文件树
    - <font color="blue">多标签</font>
    - <font color="blue">左右/上下分屏</font>
  - Markdown编辑
    - 实时预览

    - 导出pdf

- 拓展功能

  - 图片、视频、音频预览
  - <font color="blue">代码块增强</font>
    - <font color="blue">python解释运行</font>
    - <font color="blue">c/cpp编译运行</font>
    - <font color="blue">java编译运行</font>
  - 链接可视化

  - 其他功能
    - 主题配色设置
    - <font color="blue">局域网下演示功能（共享给多台设备观看）</font>
    - <font color="blue">局域网下协作功能（共享给多台设备协作）</font>
    - 账号登陆 - 设置同步
  - ......

**技术方案**：

- 客户端：C/C++ QT

- 服务端（账号数据维护）：Golang + GORM

## 目录说明

- `doc` 存放项目文档
- `client` 存放客户端代码（QT项目）
- `server` 存放服务端代码

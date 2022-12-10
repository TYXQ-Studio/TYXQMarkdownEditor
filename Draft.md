# Draft

### 计划：

```mermaid
gantt
    title PolyWar
    dateFormat  YYYY-MM-DD
    section 整体项目
    TYXQMarkdownEditor								   :2022-12-02, 2022-12-17
    立项           									 :done, a1, 2022-12-02, 1d
    中期答辩      									   :done, a2, 2022-12-10, 1d
    最终答辩      									   :done, a3, 2022-12-16, 1d
    section 客户端
    文件树                                             :file_tree, after a1, 1d
    基本文本编辑                                       :basic, after file_tree, 3d
    Markdown实时渲染                                   :render, after basic, 3d
    链接可视化                                         :visual_link, after file_tree, 6d
    pdf导出                                            :after file_tree, 1d
    图片、视频、音频预览                               :after file_tree, 4d
    代码块增强                                         :after render, 3d
    主题                                               :after file_tree, 6d
    设置                                               :after file_tree, 6d
    多人协作                                           :after render, 6d
    section 服务端
    服务端                                             :after render, 6d
    section 功能类
```

### 实际：

```mermaid
gantt
    title PolyWar
    dateFormat  YYYY-MM-DD
    section 整体项目
    TYXQMarkdownEditor								   :2022-12-02, 2022-12-17
    立项           									 :done, a1, 2022-12-02, 1d
    中期答辩      									   :done, a2, 2022-12-10, 1d
    最终答辩      									   :done, a3, 2022-12-16, 1d
    section 客户端
    CMake                                              :done, cmake, 2022-12-03, 2022-12-06
    引入FramelessHelper库                              :done, frameless, 2022-12-04, 2022-12-06
    基本 Markdown 编辑 以及 实时渲染                   :done, basic, 2022-12-05, 3d
    Markdown编辑高亮                                   :done, 2022-12-08, 1d
    链接可视化                                         :2022-12-09, 6d
    pdf导出                                            :2022-12-09, 1d
    图片、视频、音频预览                               :2022-12-09, 4d
    代码块增强                                         :2022-12-09, 3d
    主题                                               :2022-12-09, 6d
    设置                                               :2022-12-09, 6d
    多人协作                                           :2022-12-09, 6d
    section 服务端
    服务端                                             :2022-12-09, 6d
    section 功能类
```

### STH：

#### 1> 核心功能

- 编辑器
  - <font color="red">文件树</font> XB
  - 多标签
  - 左右/上下分屏

- **<font color="red">Markdown编辑</font>**
  - **<font color="red">实时预览</font>**

    Markdown词法分析
  
  - 导出pdf

#### 2> 拓展功能

- <font color="red">图片、视频、音频预览</font>
- 代码块增强
  - python解释运行
  - c/cpp编译运行
  - java编译运行
- 链接可视化 XB

- 其他功能
  - <font color="red">主题配色设置（深色浅色切换）</font>
  - 局域网下演示功能（共享给多台设备观看）
  - 局域网下协作功能（共享给多台设备协作）
  - 账号登陆 - 设置同步
- ......

#### 3> 参考即注意事项

需要使用 msvc 编译（因为Windows下 WebEngine 模块在 msvc 里才有）

##### 项目参考

- [cloose/CuteMarkEd: Qt Markdown Editor (github.com)](https://github.com/cloose/CuteMarkEd)

##### 开源库

- [wangwenx190/framelesshelper: Cross-platform window customization framework for Qt Widgets and Qt Quick. Supports Windows, Linux and macOS. (github.com)](https://github.com/wangwenx190/framelesshelper)
- [pbek/qmarkdowntextedit: A C++ Qt QPlainTextEdit widget with markdown highlighting support and a lot of other extras (github.com)](https://github.com/pbek/qmarkdowntextedit)

##### 一些文章

- 如何使用 C++ 库：[c++ - How to use Libraries - Stack Overflow](https://stackoverflow.com/questions/10358745/how-to-use-libraries)

- [Qt官方示例-Markdown编辑器 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/88771103)
- [Qt实现文本编辑器（一） - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/461346513)
- [[QT小项目练习]TextEditor 一个简单的文本编辑器 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/35012666)
- [QT实时保存的简单纯文本编辑器 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/579012389)
- [(1 封私信 / 14 条消息) 用Qt如何实现一个能够列选取的文本编辑器？ - 知乎 (zhihu.com)](https://www.zhihu.com/question/57444362/answer/152994644)

- [(1 封私信 / 14 条消息) 如何使用 QtWidget 写出好看的界面？ - 知乎 (zhihu.com)](https://www.zhihu.com/question/460991049/answer/1908111553)

- [CMake 良心教程，教你从入门到入魂 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/500002865)



#### Preview部分

- [cjmdaixi/QuickMarkdownViewer: Simple markdown viewer written in Qt Quick. (github.com)](https://github.com/cjmdaixi/QuickMarkdownViewer)

- [qyvlik/MarkdownEditor: 使用 QML 和 Markdown.Converter.js 实现的 Markdown 编辑器，特性少得可怜 (github.com)](https://github.com/qyvlik/MarkdownEditor)



- [Qt Quick渲染Markdown文本 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/44102857)



- [QML中能使用什么JS库 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/34307199)

- [quickly/quickly: ES6 and Node.js-like environment for QML (github.com)](https://github.com/quickly/quickly)

- [trollixx/node.qml: A port of Node.js to QML (github.com)](https://github.com/trollixx/node.qml)



- [Markdown 解析原理详解和 Markdown AST 描述 - D 的个人博客 (b3log.org)](https://88250.b3log.org/articles/2020/04/23/1587637426085.html)
- [C++ 打造 Markdown 解析器_牛客博客 (nowcoder.net)](https://blog.nowcoder.net/n/1e0817a420b94d118c01c60be195f1cc)

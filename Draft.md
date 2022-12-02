# Draft

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

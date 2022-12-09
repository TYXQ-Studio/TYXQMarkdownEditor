//
// Created by xiaob on 2022/12/9.
//

#ifndef TYXQMARKDOWNEDITORCLIENT_MARKDOWNUTILS_H
#define TYXQMARKDOWNEDITORCLIENT_MARKDOWNUTILS_H

#include <utility>
#include <QString>

class MarkdownUtils {
    static std::pair<int, int> countSpace(const QString &src) {
        // 如果该行内容为空，则直接返回
        if (src.isEmpty())
            return std::make_pair(0, 0);
        // 统计空格键和 Tab 键的个数
        int cntSpace = 0, cntTab = 0;
        // 从该行的第一个字符读其, 统计空格键和 Tab 键,
        // 当遇到不是空格和 Tab 时，立即停止
        for (int i = 0; src[i] != '\0'; i++) {
            if (src[i] == ' ') cntSpace++;
            else if (src[i] == '\t') cntTab++;
            // 如果内容前有空格和 Tab，那么将其统一按 Tab 的个数处理,
            // 其中, 一个 Tab = 四个空格
            else return std::make_pair(cntTab + cntSpace / 4, i);
        }
        return std::make_pair(0, 0);
    }
    static std::pair<int, int> getType(const QString src) {

    }
};


#endif //TYXQMARKDOWNEDITORCLIENT_MARKDOWNUTILS_H

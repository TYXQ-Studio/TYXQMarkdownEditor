#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <FramelessMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include <QSplitter>
#include "utils/Document.h"
#include <QPlainTextEdit>
//#include <QWebEngineView>
#include <QTextBrowser>
#include "../../qmarkdowntextedit/qmarkdowntextedit.h"

FRAMELESSHELPER_BEGIN_NAMESPACE
class StandardTitleBar;
FRAMELESSHELPER_END_NAMESPACE

class MainWindow : public FRAMELESSHELPER_PREPEND_NAMESPACE(FramelessMainWindow)
{
Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindow)

public:
    explicit MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = {});
    ~MainWindow() override;

    void openFile(const QString &path);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void initialize();

private:
    bool isModified() const;

    QScopedPointer<FRAMELESSHELPER_PREPEND_NAMESPACE(StandardTitleBar)> m_titleBar;

    QMarkdownTextEdit *editor;
    QTextBrowser *preview;
    QString m_filePath;
    Document m_content;

    QFileSystemModel *fileTreeModel;
    QTreeView *fileTreeView;
    QString curDir;

    QSplitter *splitter;
    QSplitter *contentSplitter;

    // Menu things
    QMenuBar *m_menuBar;
    QMenu *fileMenu;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionOpenDir;
    QAction *actionSave;
    QAction *actionSaveAs;

    // Handlers
    void onFileNew();
    void onFileOpen();
    void onFileSave();
    void onFileSaveAs();

    void initTitleBar();
    void initMenu();
    void initFramelessWindow();
    void initView();

    void onDirOpen();
};


#endif // MAINWINDOW_H

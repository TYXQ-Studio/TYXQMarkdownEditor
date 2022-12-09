#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <FramelessMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include <QSplitter>
#include "MarkdownDocument.h"
#include <QPlainTextEdit>
#include <QWebEngineView>
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
//    QScopedPointer<Ui::MainWindow> m_mainWindow;

//    QString curFile;
//    QString curDir;

    QMarkdownTextEdit *editor;
    QTextBrowser *preview;
    QString m_filePath;
    MarkdownDocument m_content;

//    QFileSystemModel *fileTreeModel;
//    QTreeView *fileTreeView;

    QSplitter *splitter;

    // Menu things
    QMenuBar *m_menuBar;
    QMenu *fileMenu;
    QAction *actionNew;
    QAction *actionOpen;
//    QAction *openDirAct;
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
};


#endif // MAINWINDOW_H

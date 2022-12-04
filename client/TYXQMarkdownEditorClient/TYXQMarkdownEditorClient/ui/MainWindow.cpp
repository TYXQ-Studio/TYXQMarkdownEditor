#include "MainWindow.h"

#include <StandardTitleBar>
#include <StandardSystemButton>
#include <FramelessWidgetsHelper>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QFileIconProvider>
#include <QFileDialog>
#include "../settings.h"
#include <iostream>

FRAMELESSHELPER_USE_NAMESPACE
using namespace Global;

FRAMELESSHELPER_STRING_CONSTANT(Geometry)
FRAMELESSHELPER_STRING_CONSTANT(State)

MainWindow::MainWindow(QWidget *parent, const Qt::WindowFlags flags) : FramelessMainWindow(parent, flags)
{
    initialize();
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent *event)
{
    Settings::set({}, kGeometry, saveGeometry());
    Settings::set({}, kState, saveState());
    FramelessMainWindow::closeEvent(event);
}

void MainWindow::initialize()
{
    m_titleBar.reset(new StandardTitleBar(this));
    m_titleBar->setTitleLabelAlignment(Qt::AlignCenter);

    // Menu
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));

    openFileAct = new QAction(tr("&Open File"), this);
    openFileAct->setShortcuts(QKeySequence::Open);
    openFileAct->setStatusTip(tr("Open a file"));

    openDirAct = new QAction(tr("&Open Directory"), this);
    openDirAct->setStatusTip(tr("Open a directory"));

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the file"));

    QMenuBar * const mb = menuBar();
    mb->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    mb->setStyleSheet(FRAMELESSHELPER_STRING_LITERAL(R"(
QMenuBar {
    background-color: transparent;
}

QMenuBar::item {
    background: transparent;
}

QMenuBar::item:selected {
    background: #a8a8a8;
}

QMenuBar::item:pressed {
    background: #888888;
}
    )"));
    fileMenu = mb->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openFileAct);
    fileMenu->addAction(openDirAct);
    fileMenu->addAction(saveAct);

    connect(openFileAct, &QAction::triggered, this, &MainWindow::onOpenFile);
    connect(openDirAct, &QAction::triggered, this, &MainWindow::onOpenDir);

    const auto titleBarLayout = static_cast<QHBoxLayout *>(m_titleBar->layout());
    titleBarLayout->insertWidget(0, mb);

    // setMenuWidget(): make the menu widget become the first row of the window.
    setMenuWidget(m_titleBar.data());

    splitter = new QSplitter(this);
    setCentralWidget(splitter);
    fileTreeModel = new QFileSystemModel();
    fileTreeView = new QTreeView();
    fileTreeView->setMaximumWidth(300);
    fileTreeView->setModel(fileTreeModel);
    splitter->addWidget(fileTreeView);


    FramelessWidgetsHelper *helper = FramelessWidgetsHelper::get(this);
    helper->setTitleBarWidget(m_titleBar.data());
    helper->setSystemButton(m_titleBar->minimizeButton(), SystemButtonType::Minimize);
    helper->setSystemButton(m_titleBar->maximizeButton(), SystemButtonType::Maximize);
    helper->setSystemButton(m_titleBar->closeButton(), SystemButtonType::Close);
    helper->setHitTestVisible(mb); // IMPORTANT!
    connect(helper, &FramelessWidgetsHelper::ready, this, [this, helper](){
        const QByteArray geoData = Settings::get({}, kGeometry);
        const QByteArray stateData = Settings::get({}, kState);
        if (geoData.isEmpty()) {
            helper->moveWindowToDesktopCenter();
        } else {
            restoreGeometry(geoData);
        }
        if (!stateData.isEmpty()) {
            restoreState(stateData);
        }
    });

    setWindowTitle(tr("TYXQMarkdownEditor"));
    setWindowIcon(QFileIconProvider().icon(QFileIconProvider::Computer));
}

void MainWindow::onOpenFile() {
    QString filepath = QFileDialog::getOpenFileName(this, " Open file ", "./", ".md");
    if (filepath == nullptr) return;
    // TODO: 这里写打开文件相关处理
}

void MainWindow::onOpenDir() {
    QString dir = QFileDialog::getExistingDirectory(this, " Open directory ", "./",
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (dir == nullptr) return;
//    std::cout << dir.toStdString() << std::endl;
    fileTreeModel->setRootPath(dir);
    fileTreeView->setRootIndex(fileTreeModel->index(dir));
}

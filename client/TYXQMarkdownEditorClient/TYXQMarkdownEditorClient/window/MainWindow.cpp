#include "MainWindow.h"

#include <StandardTitleBar>
#include <FramelessWidgetsHelper>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QFileIconProvider>
#include <QFileDialog>
#include "../settings.h"
#include <iostream>
#include <QWebEngineView>
#include <QPlainTextEdit>
#include "PreviewPage.h"
#include <QWebChannel>
#include <QMessageBox>
#include <QStatusBar>
#include <QTextBrowser>
#include "../../qmarkdowntextedit/qmarkdowntextedit.h"
#include "../utils/mdtransform.hpp"

FRAMELESSHELPER_USE_NAMESPACE
using namespace Global;

FRAMELESSHELPER_STRING_CONSTANT(Geometry)
FRAMELESSHELPER_STRING_CONSTANT(State)

MainWindow::MainWindow(QWidget *parent, const Qt::WindowFlags flags) : FramelessMainWindow(parent, flags) {
    initialize();
}

MainWindow::~MainWindow() = default;


void MainWindow::initTitleBar() {
    m_titleBar.reset(new StandardTitleBar(this));
    m_titleBar->setTitleLabelAlignment(Qt::AlignCenter);

    initMenu();

    const auto titleBarLayout = static_cast<QHBoxLayout *>(m_titleBar->layout());
    titleBarLayout->insertWidget(0, m_menuBar);
    // setMenuWidget(): make the menu widget become the first row of the window.
    setMenuWidget(m_titleBar.data());
}

void MainWindow::initMenu() {
    m_menuBar = menuBar();
    m_menuBar->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_menuBar->setStyleSheet(FRAMELESSHELPER_STRING_LITERAL(R"(
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

    // File
    fileMenu = m_menuBar->addMenu(tr("&File"));
    // File -> New
    actionNew = new QAction(tr("&New"), this);
    actionNew->setShortcuts(QKeySequence::New);
    actionNew->setStatusTip(tr("Create a new file"));
    fileMenu->addAction(actionNew);
    // File -> Open File
    actionOpen = new QAction(tr("&Open File"), this);
    actionOpen->setShortcuts(QKeySequence::Open);
    actionOpen->setStatusTip(tr("Open a file"));
    fileMenu->addAction(actionOpen);
    // File -> Open Directory
    // TODO: Open Directory
//    openDirAct = new QAction(tr("&Open Directory"), this);
//    openDirAct->setStatusTip(tr("Open a directory"));
//    fileMenu->addAction(openDirAct);
    // File -> Save
    actionSave = new QAction(tr("&Save"), this);
    actionSave->setShortcuts(QKeySequence::Save);
    actionSave->setStatusTip(tr("Save the file"));
    fileMenu->addAction(actionSave);
    // File -> Save As
    actionSaveAs = new QAction(tr("&Save As"), this);
    actionSaveAs->setShortcuts(QKeySequence::SaveAs);
    actionSaveAs->setStatusTip(tr("Save the file as"));
    fileMenu->addAction(actionSaveAs);

//    connect(actionOpen, &QAction::triggered, this, &MainWindow::onFileOpen);
//    connect(openDirAct, &QAction::triggered, this, &MainWindow::onOpenDir);

}

void MainWindow::initFramelessWindow() {
    FramelessWidgetsHelper *helper = FramelessWidgetsHelper::get(this);
    helper->setTitleBarWidget(m_titleBar.data());
    helper->setSystemButton(m_titleBar->minimizeButton(), SystemButtonType::Minimize);
    helper->setSystemButton(m_titleBar->maximizeButton(), SystemButtonType::Maximize);
    helper->setSystemButton(m_titleBar->closeButton(), SystemButtonType::Close);
    helper->setHitTestVisible(m_menuBar); // IMPORTANT!
    connect(helper, &FramelessWidgetsHelper::ready, this, [this, helper]() {
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

QString headHtml = "<!DOCTYPE html><html><head>"
        "<meta charset=\"utf-8\">"
        "<title>Markdown</title>"
        "<link rel=\"stylesheet\" href=\"github-markdown.css\">"
        "</head><body><article class=\"markdown-body\">";

QString endHtml = "</article></body></html>";


void MainWindow::initView() {
    splitter = new QSplitter(this);
    setCentralWidget(splitter);

    editor = new QMarkdownTextEdit();
    splitter->addWidget(editor);
    preview = new QTextBrowser();
    preview->setOpenExternalLinks(true);
    splitter->addWidget(preview);

    connect(editor, &QMarkdownTextEdit::textChanged,this, [=]() {
        m_content.setText(editor->toPlainText());
        qDebug() << "Editor:" << editor->toPlainText();
        auto transform = MarkdownTransform::fromStr(editor->toPlainText());
        qDebug() << "TOC:" << transform.getTableOfContents();
        qDebug() << "Contents:" << transform.getContents();
        preview->setHtml(headHtml + transform.getTableOfContents() + transform.getContents() + endHtml);
    });

//    QWebChannel *channel = new QWebChannel(this);
//    channel->registerObject(QStringLiteral("content"), &m_content);
//    page->setWebChannel(channel);

//    preview->setUrl(QUrl("qrc:/index.html"));

    connect(actionNew, &QAction::triggered, this, &MainWindow::onFileNew);
    connect(actionOpen, &QAction::triggered, this, &MainWindow::onFileOpen);
    connect(actionSave, &QAction::triggered, this, &MainWindow::onFileSave);
    connect(actionSaveAs, &QAction::triggered, this, &MainWindow::onFileSaveAs);
//    connect(actionExit, &QAction::triggered, this, &QWidget::close);

    connect(editor->document(), &QTextDocument::modificationChanged,
            actionSave, &QAction::setEnabled);
}

void MainWindow::initialize() {
    initTitleBar();
    initFramelessWindow();

    initView();

    /*
//    QFile defaultTextFile(":/default.md");
//    defaultTextFile.open(QIODevice::ReadOnly);
//    editor->setPlainText(defaultTextFile.readAll());

//    fileTreeModel = new QFileSystemModel();
//    fileTreeView = new QTreeView();
//    fileTreeView->setMaximumWidth(300);
//    fileTreeView->setModel(fileTreeModel);
//    splitter->addWidget(fileTreeView);
     */

}

void MainWindow::onFileNew() {
    if (isModified()) {
        QMessageBox::StandardButton button = QMessageBox::question(this, windowTitle(),
                                                                   tr("You have unsaved changes. Do you want to create a new document anyway?"));
        if (button != QMessageBox::Yes)
            return;
    }

    m_filePath.clear();
    editor->setPlainText(tr("## New document"));
    editor->document()->setModified(false);
}


void MainWindow::onFileOpen() {
    if (isModified()) {
        QMessageBox::StandardButton button = QMessageBox::question(this, windowTitle(),
                                                                   tr("You have unsaved changes. Do you want to open a new document anyway?"));
        if (button != QMessageBox::Yes)
            return;
    }

    QFileDialog dialog(this, tr("Open MarkDown File"));
    dialog.setMimeTypeFilters({"text/markdown"});
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    if (dialog.exec() == QDialog::Accepted)
        openFile(dialog.selectedFiles().constFirst());

//    QString filepath = QFileDialog::getOpenFileName(this, " Open file ", "./", ".md");
//    if (filepath == nullptr) return;
//    curFile = filepath;
//    onLoadFile();
}

void MainWindow::onFileSave() {
    if (m_filePath.isEmpty()) {
        onFileSaveAs();
        return;
    }

    QFile f(m_filePath);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, windowTitle(),
                             tr("Could not write to file %1: %2").arg(
                                     QDir::toNativeSeparators(m_filePath), f.errorString()));
        return;
    }
    QTextStream str(&f);
    str << editor->toPlainText();
    editor->document()->setModified(false);
    statusBar()->showMessage(tr("Wrote %1").arg(QDir::toNativeSeparators(m_filePath)));
}


void MainWindow::onFileSaveAs() {
    QFileDialog dialog(this, tr("Save MarkDown File"));
    dialog.setMimeTypeFilters({"text/markdown"});
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix("md");
    if (dialog.exec() != QDialog::Accepted)
        return;

    m_filePath = dialog.selectedFiles().constFirst();
    onFileSave();
}

void MainWindow::closeEvent(QCloseEvent *e) {
    if (isModified()) {
        QMessageBox::StandardButton button = QMessageBox::question(this, windowTitle(),
                                                                   tr("You have unsaved changes. Do you want to exit anyway?"));
        if (button != QMessageBox::Yes) {
            e->ignore();
            return;
        }
    }
    Settings::set({}, kGeometry, saveGeometry());
    Settings::set({}, kState, saveState());
    FramelessMainWindow::closeEvent(e);
}


void MainWindow::openFile(const QString &path) {
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, windowTitle(),
                             tr("Could not open file %1: %2").arg(
                                     QDir::toNativeSeparators(path), f.errorString()));
        return;
    }
    m_filePath = path;
    editor->setPlainText(f.readAll());
    statusBar()->showMessage(tr("Opened %1").arg(QDir::toNativeSeparators(path)));
}

bool MainWindow::isModified() const {
    return editor->document()->isModified();
}
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <FramelessMainWindow>

FRAMELESSHELPER_BEGIN_NAMESPACE
class StandardTitleBar;
FRAMELESSHELPER_END_NAMESPACE

class MainWindow : public FRAMELESSHELPER_PREPEND_NAMESPACE(FramelessMainWindow)
{
Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindow)

public:
    explicit MainWindow(QWidget *parent = nullptr, const Qt::WindowFlags flags = {});
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void initialize();

private:
    QScopedPointer<FRAMELESSHELPER_PREPEND_NAMESPACE(StandardTitleBar)> m_titleBar;
//    QScopedPointer<Ui::MainWindow> m_mainWindow;
};


#endif // MAINWINDOW_H

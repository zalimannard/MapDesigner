#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QPointer>
#include "createprojectform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_create_project_triggered();

    void on_close_triggered();

    void on_action_triggered();

    void on_open_triggered();

private:
    Ui::MainWindow *ui;
    QPointer<CreateProjectForm> mCreateProjectForm;

    void loadSubWindow(QWidget *widget);
};

#endif // MAINWINDOW_H

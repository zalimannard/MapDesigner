#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QLabel>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSubWindow(QWidget *widget)
{
    auto window = ui->mdiArea->addSubWindow(widget);
    window->setWindowTitle(widget->windowTitle());
    window->setWindowIcon(widget->windowIcon());
    window->show();
}

void MainWindow::on_create_project_triggered()
{
    QString str = QFileDialog::getExistingDirectory(0, "Создание проекта", "");
}

void MainWindow::on_open_triggered()
{
    QString str = QFileDialog::getOpenFileName(0, "Открытие проекта", "", "*.mdn");
}

void MainWindow::on_close_triggered()
{
    close();
}

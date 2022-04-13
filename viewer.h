#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>

class Viewer : public QMainWindow
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
    ~Viewer();

private:
    void createActions();
    void createMenus();

    QAction *aboutAct;

    QMenu *helpMenu;
};
#endif // VIEWER_H

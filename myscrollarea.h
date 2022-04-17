#ifndef MYSCROLLAREA_H
#define MYSCROLLAREA_H

#include <QScrollArea>
#include <QWheelEvent>

class MyScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    MyScrollArea();

protected:
    bool eventFilter(QObject *obj,QEvent *evt);
    void wheelEvent(QWheelEvent *event);
};

#endif // MYSCROLLAREA_H

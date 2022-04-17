#include <QEvent>

#include "myscrollarea.h"

MyScrollArea::MyScrollArea()
{
    installEventFilter(this);
}

bool MyScrollArea::eventFilter(QObject *obj, QEvent *evt)
{
    if (evt->type() == QEvent::Wheel)
    {
        evt->ignore();
    }
    return false;
}

void MyScrollArea::wheelEvent(QWheelEvent *event)
{
    event->ignore();
}

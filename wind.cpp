#include "wind.h"

#include <QPainter>
#include <QtMath>

Wind::Wind(const Point &firstPoint, const QString &name,
           const QString &description, const bool &visibility)
    : DrawableObject(firstPoint, name, description, visibility)
{

}

bool Wind::isHealthy() const
{
    return (points_.size() == 2);
}

bool Wind::isMaximumPoint() const
{
    return (points_.size() == 2);
}

bool Wind::isApplied() const
{
    return applied_;
}

void Wind::setApplied(bool value)
{
    applied_ = value;
}

void Wind::draw(QPixmap &pixmap) const
{
    QPainter *painter = new QPainter(&pixmap);
    QPen pen;
    pen.setColor(QColor(0, 0, 200, 200));
    pen.setWidth(7);
    painter->setPen(pen);
    QBrush brush;
    brush.setColor(QColor(0, 0, 200, 200));
    painter->setBrush(brush);

    painter->drawText(10, 15, QString("Ветер: ") + QString(" м/с"));
    painter->drawEllipse(40, 40, 100, 100);
    painter->drawEllipse(85, 85, 10, 10);
    if (isHealthy())
    {
        if (isApplied())
        {
            qreal angle = getDegreesDuration();
            qreal angleFrom0to1 = angle / 360;

            painter->drawArc(50, 50, 80, 80, (angleFrom0to1 - 0.1) * 5600, 0.2 * 5600);
            painter->drawArc(60, 60, 60, 60, (angleFrom0to1 - 0.1) * 5600, 0.2 * 5600);
            painter->drawArc(70, 70, 40, 40, (angleFrom0to1 - 0.1) * 5600, 0.2 * 5600);
        }
        else
        {
            painter->drawLine(points_.at(0).getX(), points_.at(0).getY(),
                              points_.at(1).getX(), points_.at(1).getY());
        }
    }
    delete painter;
}

qreal Wind::getDegreesDuration() const
{
    qreal oppositeCathet = points_.at(1).getY() - points_.at(0).getY();
    qreal adjacentCathet = points_.at(1).getX() - points_.at(0).getX();
    qreal hypothesis = qSqrt(qPow(oppositeCathet, 2) + qPow(adjacentCathet, 2));
    qreal cos = qAbs(adjacentCathet / hypothesis);
    qreal angle = qRadiansToDegrees(qAcos(cos));
    if ((points_.at(0).getX() > points_.at(1).getX()) && (points_.at(0).getY() > points_.at(1).getY()))
    {
        angle = 180 - angle;
    }
    else if ((points_.at(0).getX() > points_.at(1).getX()) && (points_.at(0).getY() < points_.at(1).getY()))
    {
        angle = 180 + angle;
    }
    else if ((points_.at(0).getX() < points_.at(1).getX()) && (points_.at(0).getY() < points_.at(1).getY()))
    {
        angle = 360 - angle;
    }
    return angle;
}

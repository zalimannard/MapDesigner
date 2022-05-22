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
    pen.setColor(QColor(24, 26, 30, 240));
    pen.setWidth(100);
    painter->setPen(pen);
    QBrush brush;
    brush.setColor(QColor(24, 26, 30, 240));
    painter->setBrush(brush);

    painter->drawEllipse(20, 20, 100, 100);


    pen.setColor(QColor(236, 130, 130, 200));
    pen.setWidth(7);
    painter->setPen(pen);
    brush.setColor(QColor(236, 130, 130, 200));
    painter->setBrush(brush);

    painter->drawText(30, 15, QString("Ветер: ") + QString::number(getSpeed()) + QString("м/с"));
    painter->drawEllipse(20, 20, 100, 100);
    painter->drawEllipse(65, 65, 10, 10);
    if (isHealthy())
    {
        if (isApplied())
        {
            qreal angle = getDegreesDuration();
            qreal angleFrom0to1 = angle / 360;
            qreal graphAngle = qPow(0.3, getSpeed() * 0.5);
            qreal halfGraphAngle = graphAngle / 2;

            painter->drawArc(30, 30, 80, 80, (angleFrom0to1 - halfGraphAngle) * 5600, graphAngle * 5600);
            painter->drawArc(40, 40, 60, 60, (angleFrom0to1 - halfGraphAngle) * 5600, graphAngle * 5600);
            painter->drawArc(50, 50, 40, 40, (angleFrom0to1 - halfGraphAngle) * 5600, graphAngle * 5600);
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
    qreal hypotenuse = qSqrt(qPow(oppositeCathet, 2) + qPow(adjacentCathet, 2));
    qreal cos = qAbs(adjacentCathet / hypotenuse);
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

qreal Wind::getSpeed() const
{
    return speed_;
}

void Wind::setSpeed(qreal value)
{
    speed_ = value;
}

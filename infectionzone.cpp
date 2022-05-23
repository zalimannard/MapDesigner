#include <QPainter>
#include <QtMath>

#include "infectionzone.h"

InfectionZone::InfectionZone(const Point &firstPoint, Map* map, qreal time,
                             qreal weight, const QString &name,
                             const QString &description)
    : LayerItem(firstPoint, name, description)
{
    setMap(map);
    setTime(time);
    setWeight(weight);
}

qreal InfectionZone::perimeter(const Map &map) const
{
    qreal perimeter = 0.0;

    return perimeter;
}

qreal InfectionZone::area(const Map &map) const
{
    return 0.0;
}

QString InfectionZone::report(const Map &map) const
{
    // TODO
    return "TODO";
}

bool InfectionZone::isHealthy() const
{
    return (points_.size() == 1);
}

bool InfectionZone::isMaximumPoint() const
{
    return (points_.size() == 1);
}

void InfectionZone::draw(QPixmap &pixmap) const
{
    qreal lengthKilometers = getDepthInfection();
    qreal meterPerPixel = (getMap()->getMeterPerPixelX() + getMap()->getMeterPerPixelY()) / 2;
    qreal lengthPixel = lengthKilometers * 1000 / meterPerPixel;
    if (getMap()->getWind()->isApplied())
    {
        qreal windDurationFrom0To1 = 0;
        if (getMap()->getWind()->getSpeed() != 0)
        {
            windDurationFrom0To1 = getMap()->getWind()->getDegreesDuration() / 360;
        }
        if (isHealthy())
        {
            QPainter *painter = new QPainter(&pixmap);
            QRect pie(getPosition().getX() - lengthPixel / 2,
                      getPosition().getY() - lengthPixel / 2,
                      lengthPixel, lengthPixel);
            QPen pen;
            pen.setColor(QColor(0, 200, 0, 200));
            pen.setWidth(getStyle().getLineWidth());
            painter->setPen(pen);
            QBrush brush;
            brush.setColor(QColor(0, 200, 0, 200));
            painter->setBrush(QBrush(Qt::darkGreen));

            if (getMap()->getWind()->getSpeed() < 0.50001)
            {
                painter->drawEllipse(pie);
            }
            else if (getMap()->getWind()->getSpeed() < 1.00001)
            {
                painter->drawPie(pie, (windDurationFrom0To1 - 0.25) * 5800, 2900);
            }
            else
            {
                painter->drawPie(pie, (windDurationFrom0To1 - 0.125) * 5800, 1450);
            }

            delete painter;
        }
    }
}

LayerItem* InfectionZone::clone() const
{
    return new InfectionZone(*this);
}

qreal InfectionZone::getDepthInfection() const
{
    qreal windSpeed = qMin((qreal) 15, getMap()->getWind()->getSpeed());
    qint64 windSpeedTable = qFloor(windSpeed);
    qreal weight = getWeight();
    qint64 weightTable = 0;
    if (weight < 0.01)
    {
        weightTable = 0;
    }
    else if (weight < 0.05)
    {
        weightTable = 1;
    }
    else if (weight < 0.1)
    {
        weightTable = 2;
    }
    else if (weight < 0.5)
    {
        weightTable = 3;
    }
    else if (weight < 1)
    {
        weightTable = 4;
    }
    else if (weight < 3)
    {
        weightTable = 5;
    }
    else if (weight < 5)
    {
        weightTable = 6;
    }
    else if (weight < 10)
    {
        weightTable = 7;
    }
    else
    {
        weightTable = 8;
    }
    QVector<QVector<qreal> > depths;
    depths.append({0.38, 0.85, 1.25, 3.16, 4.75, 9.18, 12.53, 19.20, 29.56});
    depths.append({0.38, 0.85, 1.25, 3.16, 4.75, 9.18, 12.53, 19.20, 29.56});
    depths.append({0.26, 0.59, 0.84, 1.92, 2.84, 5.35, 7.20, 10.83, 16.44});
    depths.append({0.22, 0.48, 0.68, 1.53, 2.17, 3.99, 5.34, 7.96, 11.94});
    depths.append({0.19, 0.42, 0.59, 1.33, 1.88, 3.28, 4.36, 6.46, 9.62});
    depths.append({0.17, 0.38, 0.53, 1.19, 1.68, 2.91, 3.75, 5.53, 8.19});
    depths.append({0.15, 0.34, 0.48, 1.09, 1.53, 2.66, 3.43, 4.88, 7.20});
    depths.append({0.14, 0.32, 0.45, 1.00, 1.42, 2.46, 3.17, 4.49, 6.48});
    depths.append({0.13, 0.30, 0.42, 0.94, 1.33, 2.30, 2.97, 4.20, 5.92});
    depths.append({0.12, 0.28, 0.40, 0.88, 1.25, 2.17, 2.80, 3.96, 5.60});
    depths.append({0.12, 0.26, 0.38, 0.84, 1.19, 2.06, 2.66, 3.76, 5.31});
    depths.append({0.11, 0.25, 0.36, 0.80, 1.13, 1.96, 2.53, 3.58, 5.06});
    depths.append({0.11, 0.24, 0.34, 0.76, 1.08, 1.88, 2.42, 3.43, 4.85});
    depths.append({0.10, 0.23, 0.33, 0.74, 1.04, 1.80, 2.37, 3.29, 4.66});
    depths.append({0.10, 0.22, 0.32, 0.71, 1.00, 1.74, 2.24, 3.17, 4.49});
    depths.append({0.10, 0.22, 0.31, 0.69, 0.97, 1.68, 2.17, 3.07, 4.34});
    qreal lengthKilometers = getTime() * depths.at(windSpeedTable).at(weightTable);
    return lengthKilometers;
}

Map* InfectionZone::getMap() const
{
    return map_;
}

void InfectionZone::setMap(Map* value)
{
    map_ = value;
}

qreal InfectionZone::getTime() const
{
    return time_;
}

void InfectionZone::setTime(qreal value)
{
    time_ = value;
}

qreal InfectionZone::getWeight() const
{
    return weight_;
}

void InfectionZone::setWeight(qreal value)
{
    weight_= value;
}

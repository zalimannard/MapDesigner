#include "layeritem.h"
#include <QtMath>

LayerItem::LayerItem(const Point &keyNode, const QString &name, const QString &description, const bool &visibility) :
    DrawableObject (keyNode, name, description, visibility)
{

}

QString LayerItem::report(const Map &map) const
{
    QString reportText;
    reportText.append("Название: " + getName());
    reportText.append("\nОписание: " + getDescription());
    reportText.append("\nВидимость: " + QString(isVisible() ? "Отображён" : "Скрыт"));
    reportText.append("\nКлючевая точка: ");
    reportText.append("\n    Долгота: " + QString::number(map.imagePointToEarthPoint(
                                                              Point(getPosition().getX(), getPosition().getY())).getX()));
    reportText.append("\n    Широта: " + QString::number(map.imagePointToEarthPoint(
                                                             Point(getPosition().getX(), getPosition().getY())).getY()));
    reportText.append("\nПериметр: " + QString::number(round(perimeter(map) / 10) / 100) + " км");
    reportText.append("\nПлощадь: " + QString::number(round(square(map) / 10000) / 100) + " км^2");
    return reportText;
}

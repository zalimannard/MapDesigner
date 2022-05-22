#include "layeritem.h"

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
    reportText.append("\n    Долгота: " + QString::number(getPosition().getX()));
    reportText.append("\n    Широта: " + QString::number(getPosition().getY()));
    reportText.append("\nПериметр: " + QString::number(perimeter(map)));
    reportText.append("\nПлощадь: " + QString::number(square(map)));
    return reportText;
}

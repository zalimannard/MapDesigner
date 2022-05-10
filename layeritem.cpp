#include "layeritem.h"

LayerItem::LayerItem(const Point &keyNode, const QString &name, const QString &description, const bool &visibility) :
    DrawableObject (keyNode, name, description, visibility)
{

}

QStringList LayerItem::report(const Map &map) const
{
    QStringList reportText;
    reportText.append("Название: " + getName());
    reportText.append("Описание: " + getDescription());
    reportText.append("Видимость: " + QString(isVisible() ? "Отображён" : "Скрыт"));
    reportText.append("Ключевая точка: ");
    reportText.append("    Долгота: " + QString::number(getPosition().getX()));
    reportText.append("    Широта: " + QString::number(getPosition().getY()));
    reportText.append("Периметр: " + QString::number(perimeter(map)));
    reportText.append("Площадь: " + QString::number(square(map)));
    return reportText;
}

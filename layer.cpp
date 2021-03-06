#include <QtGlobal>
#include <QTime>

#include "layer.h"

Layer::Layer(QSqlDatabase *db, const QString &name, const QString &description) :
    DrawableObject(Point(0.0, 0.0), name, description)
{
    db_ = *db;
    query = new QSqlQuery(db_);
}

LayerItem* Layer::push(const LayerItem *item)
{
    LayerItem *copyItem = item->clone();
    items_.append(copyItem);
    query->exec("INSERT INTO " + getName() + "(name, perimeter, area) VALUES ('" +
                item->getName() + "', " +
                QString::number((qreal) (QRandomGenerator::global()->generate() % 10000) / 100) + ", " +
                QString::number((qreal) (QRandomGenerator::global()->generate() % 10000) / 100) + ")");
    return copyItem;
}

LayerItem* Layer::at(const qint64 &index)
{
    return items_.at(index);
}

void Layer::remove(const qint64 &index)
{
    items_.remove(index);
}

qint64 Layer::size()
{
    return items_.size();
}

void Layer::moveUp(const qint64 &index)
{
    LayerItem *moveItem = items_.at(index)->clone();
    items_.remove(index);
    items_.insert(qMax((qint64) 0, index - 1), moveItem);
}

void Layer::moveDown(const qint64 &index)
{
    LayerItem *moveItem = items_.at(index)->clone();
    items_.remove(index);
    items_.insert(qMin((qint64) items_.size(), index + 1), moveItem);
}

bool Layer::isHealthy() const
{
    return true;
}

bool Layer::isMaximumPoint() const
{
    return true;
}

void Layer::draw(QPixmap &pixmap) const
{
    for (LayerItem *item : items_)
    {
        if (item->isVisible())
        {
            item->draw(pixmap);
        }
    }
}

Layer* Layer::clone() const
{
    return new Layer(*this);
}

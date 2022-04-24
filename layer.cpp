#include <QtGlobal>

#include "layer.h"

Layer::Layer(const QString &name, const QString &description) : DrawableObject(name, description)
{

}

void Layer::push(const LayerItem *item)
{
    LayerItem *copyItem = item->clone();
    this->items_.append(copyItem);
}

LayerItem* Layer::at(const qint64 &index)
{
    return this->items_.at(index);
}

void Layer::remove(const qint64 &index)
{
    this->items_.remove(index);
}

void Layer::moveUp(const qint64 &index)
{
    LayerItem *moveItem = this->items_.at(index)->clone();
    this->items_.remove(index);
    this->items_.insert(qMax((qint64) 0, index - 1), moveItem);
}

void Layer::moveDown(const qint64 &index)
{
    LayerItem *moveItem = this->items_.at(index)->clone();
    this->items_.remove(index);
    this->items_.insert(qMin((qint64) this->items_.size(), index + 1), moveItem);
}

void Layer::draw(QPixmap &pixmap) const
{
    for (LayerItem *item : this->items_)
    {
        item->draw(pixmap);
    }
}

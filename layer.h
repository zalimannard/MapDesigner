#ifndef LAYER_H
#define LAYER_H

#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QRandomGenerator>
#include <QTime>

#include "layeritem.h"

class Layer : public DrawableObject
{
public:
    Layer(QSqlDatabase *db, const QString &name = "Новый слой", const QString &description = "");

    LayerItem* push(const LayerItem *item);
    LayerItem* at(const qint64 &index);
    void remove(const qint64 &index);
    qint64 size();
    void moveUp(const qint64 &index);
    void moveDown(const qint64 &index);

    bool isHealthy() const override;
    bool isMaximumPoint() const override;
    void draw(QPixmap &pixmap) const override;

    virtual Layer* clone() const;

private:
    QSqlDatabase db_;
    QSqlQuery *query;
    QVector<LayerItem *> items_;
};

#endif // LAYER_H

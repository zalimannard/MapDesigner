#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "layer.h"
#include "map.h"

class Project
{
public:
    Project(const QString &name);

    void save() const;
    void open(const QString &path);
    void draw(QPixmap &pixmap) const;

    void pushLayer(const Layer *layer);
    Layer* layerAt(const qint64 &index);
    void removeLayer(const qint64 &index);
    qint64 layerSize();
    void moveUpLayer(const qint64 &index);
    void moveDownLayer(const qint64 &index);

    bool isMapExist() const;
    Map* getMap() const;
    void setMap(const QString &path);
    Style* getStyle() const;
    void setStyle(const Style &style);

    QString getName() const;
    void setName(const QString &name);
    QString getPath() const;
    void setPath(const QString &path);
    QSqlDatabase* getDb();

private:
    QSqlDatabase db;
    QSqlQuery *query;
    QVector<Layer*> layers_;
    QString name_;
    QString path_;
    Map *map_ = nullptr;
    Style *style_ = new Style();

};

#endif // PROJECT_H

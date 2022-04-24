#ifndef PROJECT_H
#define PROJECT_H

#include <QString>

#include "layer.h"
#include "map.h"

class Project
{
public:
    Project(const QString &name);

    void save() const;
    void open(const QString &path);
    void draw(QPixmap &pixmap) const;

    void pushLayer(const Layer &Project);
    Layer layerAt(const qint64 &index);
    void removeLayer(const qint64 &index);
    void moveUpLayer(const qint64 &index);
    void moveDownLayer(const qint64 &index);

    QString getMap() const;
    void setMap(const QString &path);
    bool isMapExist() const;

    QString getName() const;
    void setName(const QString &name);
    QString getPath() const;
    void setPath(const QString &path);

private:
    QVector<Layer> layers_;
    QString name_;
    QString path_;
    Map *map_ = nullptr;

};

#endif // PROJECT_H

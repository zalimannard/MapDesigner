#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include "map.h"

class Project
{
public:
    Project(const QString &name);

    void save(const QString &path) const;
    void open(const QString &path);

    void setMap(const QString &path);
    Map getMap() const;
    bool isMapExist() const;

    QString getName() const;

    QVector<DisplayedObject> layers;

private:
    QString name_;
    Map *map_ = nullptr;

};

#endif // PROJECT_H

#include <QFile>
#include <QTextStream>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>

#include "project.h"

Project::Project(const QString &name)
{
    if (!name.isEmpty())
    {
        name_ = name;
    }
}

void Project::save() const
{
    QFile file;
    file.setFileName(path_ + "/" + name_ + ".mdp");
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream writeStream(&file);
        if (isMapExist())
        {
            writeStream << "$map" << Qt::endl;
            writeStream << map_->getPathToImage() << Qt::endl;
            writeStream.flush();
        }
    }
    file.close();
}

void Project::open(const QString &path)
{
    QFile file(path + "/" + getName() + ".mdp");

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        if (line == "$map")
        {
            QString mapPath = in.readLine();
            setMap(mapPath);
        }
    }
    file.close();

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path + "/Objects.db");

    if (db.open())
    {
        qDebug() << "open";
    }
    else
    {
        qDebug() << "close";
    }
    query = new QSqlQuery(db);
}

void Project::draw(QPixmap &pixmap) const
{
    if (isMapExist())
    {
        map_->draw(pixmap);
    }
    for(auto i = layers_.size() - 1; i >= 0; --i)
    {
        if (layers_.at(i)->isVisible())
        {
            layers_.at(i)->draw(pixmap);
        }
    }
}

void Project::pushLayer(const Layer *layer)
{
    Layer* newLayer = layer->clone();
    layers_.append(newLayer);
    query->exec(QString("CREATE TABLE ") + layer->getName() + QString("(name TEXT, perimeter REAL, area REAL);"));
}

Layer* Project::layerAt(const qint64 &index)
{
    return layers_.at(index);
}

void Project::removeLayer(const qint64 &index)
{
    query->exec(QString("DROP TABLE ") + layers_.at(index)->getName());
    layers_.remove(index);
}

qint64 Project::layerSize()
{
    return layers_.size();
}

void Project::moveUpLayer(const qint64 &index)
{
    Layer* movedLayer = layers_.at(index)->clone();
    layers_.remove(index);
    layers_.insert(qMax((qint64) 0, index - 1), movedLayer);
}

void Project::moveDownLayer(const qint64 &index)
{
    Layer* movedLayer = layers_.at(index)->clone();
    layers_.remove(index);
    layers_.insert(qMin((qint64) layers_.size(), index + 1), movedLayer);
}

bool Project::isMapExist() const
{
    return map_ != nullptr;
}

Map* Project::getMap() const
{
    return map_;
}

void Project::setMap(const QString &path)
{
    map_ = new Map(path);
}

Style* Project::getStyle() const
{
    return style_;
}

void Project::setStyle(const Style &style)
{
    style_ = new Style(style);
}

QString Project::getName() const
{
    return name_;
}

void Project::setName(const QString &name)
{
    this->name_ = name;
}

QString Project::getPath() const
{
    return path_;
}

void Project::setPath(const QString &path)
{
    this->path_ = path;
}

QSqlDatabase* Project::getDb()
{
    return &db;
}

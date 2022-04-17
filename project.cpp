#include <QFile>
#include <QTextStream>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>

#include "project.h"

Project::Project(const QString &name)
{
    if (!name.isEmpty())
    {
        name_ = name;
    }
}

void Project::save(const QString &path) const
{
    QFile file;
    file.setFileName(path + "/" + name_ + ".mdp");
    qDebug() << file.fileName();
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream writeStream(&file);
        qDebug() << "C";
        if (isMapExist())
        {
            qDebug() << "Map Exist";
            writeStream << "$map" << Qt::endl;
            writeStream << getMap().getPathToImage() << Qt::endl;
            writeStream.flush();
            qDebug() << "S";
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
            this->setMap(mapPath);
        }
    }
    file.close();
    //TODO
}

void Project::setMap(const QString &path)
{
    map_ = new Map(path);
}

Map Project::getMap() const
{
    return *map_;
}

bool Project::isMapExist() const
{
    return map_ != nullptr;
}

QString Project::getName() const
{
    return name_;
}

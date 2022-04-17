#include <QFile>
#include <QTextStream>

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
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream writeStream(&file);
        writeStream << "ABOBA" << Qt::endl;
        writeStream.flush();
    }
    file.close();
}

void Project::open(const QString &path)
{
    //TODO
}

QString Project::getName() const
{
    return name_;
}

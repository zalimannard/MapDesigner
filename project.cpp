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
    file.setFileName(path + "/" + name_ + ".mdn");
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream writeStream(&file);
        writeStream << "ABOBA" << Qt::endl;
        writeStream.flush();
    }
    file.close();
}

QString Project::getName() const
{
    return name_;
}

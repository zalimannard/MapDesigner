#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Database;
}

class Database : public QWidget
{
    Q_OBJECT

public:
    Database(QSqlDatabase db, QWidget *parent = nullptr);
    ~Database();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Database *ui;
    QSqlDatabase db_;
    QSqlQuery *query_;
    QSqlTableModel *model_;
};

#endif // DATABASE_H

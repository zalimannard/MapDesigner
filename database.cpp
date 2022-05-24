#include "database.h"
#include "ui_database.h"

Database::Database(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Database)
{
    db_ = db;
    query_ = new QSqlQuery(db_);
    model_ = new QSqlTableModel(this, db_);
    ui->setupUi(this);
    show();
}

Database::~Database()
{
    delete ui;
}

void Database::on_pushButton_clicked()
{
    query_->exec("SELECT * FROM " + ui->sqlQuery2->text());
    model_->setTable(ui->sqlQuery2->text());
    model_->select();
    ui->tableView->setModel(model_);
}

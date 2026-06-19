#ifndef ADMINPROFILE_H
#define ADMINPROFILE_H

#include "ui_adminprofile.h"

#include <QSqlError>
#include <QString>
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class adminprofile : public QWidget
{
    Q_OBJECT

public:
    explicit adminprofile(QString username, QWidget *parent = nullptr);
    ~adminprofile();

private slots:
    void UpdateUsername();
    void UpdatePassword();

private:
    Ui::adminprofile *ui;

    QString currentusername;

    void admininfo();
    bool verifypassword(Qstring password);
    void Addadmin();
};

#endif // ADMINPROFILE_H

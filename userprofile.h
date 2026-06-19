#ifndef USERPROFILE_H
#define USERPROFILE_H

#include "ui_userprofile.h"

#include <QSqlError>
#include <QString>
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class userprofile : public QWidget
{
    Q_OBJECT

public:
    explicit userprofile(QString username, QWidget *parent = nullptr);
    ~userprofile();

private slots:
    void UpdateUsername();
    void UpdatePassword();
    void CreateuserAccount();

private:
    Ui::userprofile *ui;

    QString currentusername;
    QString email;

    void userinfo();
    bool verifypassword(QString password);
    void Adduser();
};

#endif // USERPROFILE_H


#endif // USERPROFILE_H

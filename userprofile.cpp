#include "userprofile.h"
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

userprofile::userprofile(QString username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::userprofile)
    , currentusername(username)
{
    ui->setupUi(this);
    userInfo();

    connect(ui->updateUsernameBtn, &QPushButton::clicked, this, &userprofile::UpdateUsername);
    connect(ui->updatePasswordBtn, &QPushButton::clicked, this, &userprofile::UpdatePassword);
    connect(ui->createuserBtn, &QPushButton::clicked, this, &userprofile::CreateuserAccount);
}

userprofile::~userprofile()
{
    delete ui;
}

void userprofile::userInfo()
{
    QSqlQuery query;
    query.prepare("SELECT email FROM user WHERE username = :username");
    query.bindValue(":username", currentusername);

    if (query.exec() && query.next()) {
        QString email = query.value(2).toString();
        currentEmail  = email;
        ui->userNameLabel->setText(currentusername);
        ui->displayusername->setText(currentusername);
        ui->displayemail->setText(currentEmail);
    }
    else{
        ui->displayusername->setText(currentusername)
        qDebug() << "UserInfo error:" << query.lastError().text();
    }
}

void userprofile::UpdateUsername()
{
    QString newusername = ui->newUsernameLineEdit->text().trimmed();

    if (newusername.isEmpty()) {
        ::warning(this,QMessageBox "Update Username", "Username field cannot be empty.");
        return;
    }
    if (newusername == currentusername) {
        QMessageBox::information(this, "Update Username", "That is already your current username.");
        return;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE users SET username = :newname WHERE username= :oldname");
    updateQuery.bindValue(":newname", newusername);
    updateQuery.bindValue(":oldname", currentusername);

    if (updateQuery.exec()) {
        currentusername = newusername;
        // ui->displayusername->setText(currentusername); // update display
        // ui->userNameLabel->setText(currentusername);
        ui->newUsernameLineEdit->clear();
        QMessageBox::information(this, "Update Username","Username updated successfully to \"" + currentusername + "\".");
        qDebug() << "Username changed to:" << currentusername;
    } else {
        QMessageBox::critical(this, "Update Username","Failed to update username. Please try again.");
        qDebug() << "Username update error:" << updateQuery.lastError().text();
    }
}

void userprofile::UpdatePassword()
{
    QString currentpassword = ui->currentPasswordLineEdit->text();
    QString newpassword = ui->newPasswordLineEdit->text();

    if (currentpassword.isEmpty() || newpassword.isEmpty()) {
        QMessageBox::warning(this, "Update Password", "All password fields must be filled.");
        return;
    }

    if (newpassword == currentpassword) {
        QMessageBox::information(this, "Update Password", "New password must differ from current password.");
        return;
    }

    if (!verifyCurrentPassword(currentpassword)) {
        QMessageBox::critical(this, "Update Password", "Current password is incorrect.");
        return;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE users SET password = :newpassword WHERE username = :username");
    updateQuery.bindValue(":newpassword", newpassword);
    updateQuery.bindValue(":username", currentusername);

    if (updateQuery.exec()) {
        ui->currentPasswordLineEdit->clear();
        ui->newPasswordLineEdit->clear();
        QMessageBox::information(this, "Update Password", "Password updated successfully.");
        qDebug() << "Password updated for:" << currentUsername;
    } else {
        QMessageBox::critical(this, "Update Password", "Failed to update password. Please try again.");
        qDebug() << "Password update error:" << updateQuery.lastError().text();
    }
}

bool userprofile::verifyCurrentPassword(QString enteredPassword)
{
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", currentusername);

    if (query.exec() && query.next()) {
        return query.value(0).toString() == enteredPassword;
    }
    return false;

}

#include "adminprofile.h"
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlError>
#include <QSqlQuery>

adminprofile::adminprofile(QString username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::adminprofile)
    , currentusername(username)
{
    ui->setupUi(this);
    adminInfo();

    connect(ui->updateUsernameBtn, &QPushButton::clicked, this, &adminprofile::UpdateUsername);
    connect(ui->updatePasswordBtn, &QPushButton::clicked, this, &adminprofile::UpdatePassword);
    connect(ui->createAdminBtn, &QPushButton::clicked, this, &adminprofile::CreateAdminAccount);
}

adminprofile::~adminprofile()
{
    delete ui;
}

void adminprofile::adminInfo()
{
    QSqlQuery query;
    query.prepare("SELECT name FROM user WHERE username = :username");
    query.bindValue(":username", currentusername);

    if (query.exec() && query.next()) {
        ui->adminNameLabel->setText(currentusername);
    }
    else{
        qDebug() << "AdminInfo error:" << query.lastError().text();
    }
}

void adminprofile::UpdateUsername()
{
    QString newusername = ui->newUsernameLineEdit->text().trimmed();

    if (newusername.isEmpty()) {
        setFeedback("Empty block");
        return;
    }
    if (newusername == currentusername) {
        setFeedback("Same as the previous username");
        return;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE admins SET username = :newname WHERE username= :oldname");
    updateQuery.bindValue(":newname", newusername);
    updateQuery.bindValue(":oldname", currentusername);

    if (updateQuery.exec()) {
        currentusername = newusername;
        ui->displayusername->setText(currentusername); // update display
        ui->adminNameLabel->setText(currentusername);
        ui->newUsernameLineEdit->clear();
        setFeedback("Username updated successfully.");
        qDebug() << "Username changed to:" << currentUsername;
    } else {
        setFeedback("Failed to update username. Try again.");
        qDebug() << "Username update error:" << updateQuery.lastError().text();
    }
}

void adminprofile::UpdatePassword()
{
    QString currentpassword = ui->currentPasswordLineEdit->text();
    QString newpassword = ui->newPasswordLineEdit->text();

    if (currentpassword.isEmpty() || newpassword.isEmpty()) {
        setFeedback("All fields must be filled.");
        return;
    }

    if (newpassword == currentpassword) {
        setFeedback("Same as current password.");
        return;
    }

    if (!verifyCurrentPassword(currentpassword)) {
        setFeedback("Current password is incorrect.");
        return;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE admins SET password = :newpassword WHERE username = :username");
    updateQuery.bindValue(":newpassword", newpassword);
    updateQuery.bindValue(":username", currentUsername);

    if (updateQuery.exec()) {
        ui->currentPasswordLineEdit->clear();
        ui->newPasswordLineEdit->clear();
        setFeedback("Password updated successfully.");
        qDebug() << "Password updated for:" << currentUsername;
    } else {
        setFeedback("Failed to update password. Try again.");
        qDebug() << "Password update error:" << updateQuery.lastError().text();
    }
}

bool adminprofile::verifyCurrentPassword(QString enteredPassword)
{
    QSqlQuery query;
    query.prepare("SELECT password FROM admins WHERE username = :username");
    query.bindValue(":username", currentusername);

    if (query.exec() && query.next()) {
        return query.value(0).toString() == enteredPassword;
    }
    return false;

}
void adminprofile::CreateAdminAccount()
{
    QString username = ui->newAdminUsernameLineEdit->text().trimmed();
    QString password = ui->newAdminPasswordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        setFeedback("All fields are required to create an account.");
        return;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("SELECT * FROM admins WHERE username = :username AND password = :password");
    insertQuery.bindValue(":username", username);
    insertQuery.bindValue(":password", password);

    if (insertQuery.exec()) {
        ui->newAdminUsernameLineEdit->clear();
        ui->newAdminPasswordLineEdit->clear();
        setFeedback("Admin account \"" + username + "\" created successfully.");
        qDebug() << "New admin created:" << username;
    } else {
        setFeedback("Failed to create admin account. Try again.");
        qDebug() << "Create admin error:" << insertQuery.lastError().text();
    }
}

void adminprofile::setFeedback(QString message)
{
    ui->feedbackLabel->setText(message);
}

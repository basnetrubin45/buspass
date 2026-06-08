#include "signup.h"
#include "ui_signup.h"

signup::signup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::signup)
{
    ui->setupUi(this);

    if (!setupDatabase()) {
        QMessageBox::critical(this, "Error", "Could not connect to database!");
    }
}

bool signup::setupDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("buspass.db");

    if (!db.open()) {
        return false;
    }

    return true;
}

void signup::on_signup_button_clicked()
{
    QString name = ui->name->text().trimmed();
    QString password = ui->password->text().trimmed();
    QString username = ui->username->text().trimmed();
    QString email = ui->email->text().trimmed();

    if (name.isEmpty() || password.isEmpty() || username.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter all fields!");
        return;
    }

    if (checkUsername(username)==0) {

        if (checkEmail(username)==0) {
            QMessageBox::information(this, "Success", "Signup successful!");

            QSqlQuery query;
            query.exec("INSERT INTO user (username, password, name, email, isAdmin) VALUES (:username, :name, :password, :email, 0)");


        } else {
            QMessageBox::critical(this, "Failed", "Invalid email already in use.");

        }
    } else {
        QMessageBox::critical(this, "Failed", "Invalid username already taken. Try again.");

    }
}

bool signup::checkUsername(QString username)
{
    QSqlQuery query;

    query.bindValue(":username", username);        //security
    query.prepare("SELECT * FROM user WHERE username = :username");

    query.exec();

    int n=0;

    if (query.next()) {
        n=1;
    }

    return n;
}

bool signup::checkEmail(QString email)
{
    QSqlQuery query;

    query.bindValue(":email", email);        //security
    query.prepare("SELECT * FROM user WHERE email = :email");

    query.exec();

    int n=0;

    if (query.next()) {
        n=1;
    }

    return n;
}

signup::~signup()
{
    delete ui;
}

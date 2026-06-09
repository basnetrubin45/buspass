#include "login.h"
#include "signup.h"

#include "ui_login.h"

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowTitle("Login");

    if (!setupDatabase()) {
        QMessageBox::critical(this, "Error", "Could not connect to database!");
    }
}

bool login::setupDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("buspass.db");

    if (!db.open()) {
        return false;
    }


  QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS user ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "username TEXT NOT NULL UNIQUE,"
               "password TEXT NOT NULL CHECK(LENGTH(password) >= 6),"
               "name TEXT NOT NULL,"
               "email TEXT UNIQUE,"
               "isAdmin BOOLEAN NOT NULL"
               ")");

   //  query.exec("INSERT INTO user (username, password, name, email, isAdmin) VALUES ('admin', 'admin123', 'admin1', 'admin@example.com', 1)");
    return true;
}


bool login::checkCredentials(QString username, QString password)
{
    QSqlQuery query;

    query.bindValue(":username", username);     // security
    query.bindValue(":password", password);    //security
    query.prepare("SELECT * FROM user WHERE username = :username AND password = :password");

    query.exec();

    if (query.next()) {
        return true;
    }

    return false;
}

void login::on_login_button_clicked()
{
    QString username = ui->username->text().trimmed();
    QString password = ui->password->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter both username and password!");
        return;
    }

    if (checkCredentials(username, password)) {
        QMessageBox::information(this, "Success", "Login successful! Welcome, " + username + "!");
    } else {
        QMessageBox::critical(this, "Failed", "Invalid username or password. Try again.");

    }
}

void login::on_signup_button_clicked()
{
    signup *s = new signup();
    s->show();
    this->close();
}

login::~login()
{
    delete ui;
}

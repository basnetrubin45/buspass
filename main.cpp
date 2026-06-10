
#include "login.h"
#include "database.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!Database::connect()) {
        QMessageBox::critical(nullptr, "Error", "Could not connect to database!");
        return -1;
    }

    login w;
    w.show();
    return QCoreApplication::exec();
}
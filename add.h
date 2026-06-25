#ifndef ADD_H
#define ADD_H

#include <QDialog> // 1. Make sure this include is present

namespace Ui {
class add;
}

// 2. Ensure ": public QDialog" is here
class add : public QDialog
{
    Q_OBJECT

public:
    explicit add(QWidget *parent = nullptr);
    ~add();

signals:
    // COPY AND PASTE THIS: This is the custom signal to transmit your form data
    void busAdded(QString id, QString route, QString seats, QString available, QString departure, QString price);

private slots:
    // COPY AND PASTE THIS: Matches the name of your Add button (pushButton)
    void on_pushButton_clicked();

private:
    Ui::add *ui;
};

#endif // ADD_H
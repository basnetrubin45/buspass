#ifndef REVIEW_H
#define REVIEW_H


#include <QWidget>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlError>

class QLineEdit;
class QComboBox;
class QTextEdit;
class QCheckBox;
class QLabel;
class QDialogButtonBox;

class review: public QWidget
{
    Q_OBJECT

public:
    explicit review(QWidget *parent = nullptr);
    ~review();

private slots:
    void submitReview();
    void resetForm();

private:
    Ui::review *ui;

    bool setupDatabase();
    bool checkReview(QString Reviewpost);

};

#endif // REVIEW_H

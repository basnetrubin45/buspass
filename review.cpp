#include "review.h"
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QCheckBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QDebug>

review::review(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::review)
{
    ui->setupUi(this);
    ui->titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; margin-bottom: 4px;");
    connect(ui->buttonBox, &QDialogButtonBox::accepted,this,&review::submitReview);
    connect(ui->buttonBox, &QDialogButtonBox::rejected,this,&review::resetForm);
}
void review::submitReview()
{
    const QString body = ui->reviewTextEdit->toPlainText().trimmed();
    if (body.isEmpty()) {
        setFeedback("Please fill in all fields.", true);
        return;
    }

    qDebug() << " Review Submitted ";
    resetForm();
}
void review::resetForm()
{
    ui->reviewTitleLineEdit->clear();
    ui->reviewTextEdit->clear();
}
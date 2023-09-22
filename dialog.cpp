#include "dialog.h"
#include "ui_dialog.h"
#include "vrach.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setFixedSize(this->size());
    setModal(true);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setBolezn(const Bolezn &bolezn)
{
    ui->bol->setText(bolezn.bol());
    ui->med->setCurrentIndex(bolezn.id_med());
    ui->checkBox1->setChecked(bolezn.high_temp());
    ui->checkBox2->setChecked(bolezn.nausea());
    ui->checkBox3->setChecked(bolezn.stom_hurts());
    ui->proc->setText(bolezn.procedure());
}

Dialog::Dialog(const Bolezn &bolezn, QWidget *parent) : Dialog(parent)
{
    setBolezn(bolezn);
}

void Dialog::on_pushButton_clicked()
{
    auto Bolezn = getBolezn();
    emit sendBolezn(*Bolezn);
    delete Bolezn;
    this->close();
}

Bolezn *Dialog::getBolezn()
{
    auto bolezn =new Bolezn( ui->bol->text(),
                             ui->checkBox1->isChecked(),
                             ui->checkBox2->isChecked(),
                             ui->checkBox3->isChecked(),
                             ui->proc->text(),
                             ui->med->currentIndex());
    return bolezn;
}


void Dialog::on_pushButton_2_clicked()
{
    this->close();
}


#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "vrach.h"
#include "mainwindow.h"

namespace Ui {
class Dialog;
}

///Класс диалогового окна
class Dialog : public QDialog
{
    Q_OBJECT

public:
    ///Конструктор по умолчанию
    explicit Dialog(QWidget *parent = nullptr);
    ///Конструктор с параметрами
    Dialog(const Bolezn &bolezn, QWidget *parent = nullptr);
    ///Деструктор
    ~Dialog();


signals:
    ///Сигнал дл отправки данных
    void sendBolezn(Bolezn);

private slots:
    ///Слот нажатия кнопки ОК
    void on_pushButton_clicked();
    ///Слот нажатия кнопки отмена
    void on_pushButton_2_clicked();

private:
    ///UI диалогового окна
    Ui::Dialog *ui;
    ///Метод для получения данных о фильме
    Bolezn *getBolezn();
    ///Метод записи данных о фильме в интерфейс окна
    void setBolezn(const Bolezn &bolezn);
};

#endif // DIALOG_H

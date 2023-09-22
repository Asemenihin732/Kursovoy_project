#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "vrach.h"
#include "proxymodel.h"
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class proxyModel;
class QActionGroup;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ///Конструктор главного окна
    MainWindow(QWidget *parent = nullptr);
    ///Деструктор главного окна
    ~MainWindow();
    ///переменная для хранение языка
    QString language;

private:
    ///UI главного окна
    Ui::MainWindow *ui;
    ///Средство для использования контекстного меню
    QMenu *new_menu;
    ///Средство дл яиспользования БД
    database *db;
    ///Модель для сортировки данных
    proxyModel *MyProxyModel;
    ///Хранит переводчик
    QTranslator qtLanguageTranslator;
    ///Функция поиска по названию
    void filter();
    ///Функция получения медикаментов
    void getMedicaments();
    ///Функция получения количества
    void getKolvo();
private slots:
    ///Слот нажатия кнопки Добавить
    void on_actionAdd_triggered();
    ///Функция добавления данных
    void AddBolezn(Bolezn bolezn);
    ///Слот нажатия кнопки Редактировать
    void on_actionEdit_triggered();
    ///Слот нажатия кнопки Удалить
    void on_actionDelete_triggered();
    ///Функция редактирования данных
    void EditBolezn(Bolezn bolezn);
    ///Метод записи настроек
    void writeSettings();
    ///Метод для чтения натсроек
    void readSettings();
    ///Слот нажатия кнопки Смена Языка
    void on_actionChange_language_triggered();
    ///Слот нажатия кнопки Выход
    void on_actionExit_triggered();
    ///Слот нажатия кнопки об Авторе
    void on_actionAbout_author_triggered();
    ///Отработка нажатия по таблице
    void on_tableView_doubleClicked(const QModelIndex &index);
    ///Отработка нажатия по таблице
    void on_tableView_clicked(const QModelIndex &index);

protected:
    ///Метод вызова контекстного меню
    void contextMenuEvent(QContextMenuEvent *event) override;
    ///Метод смены языка
    void changeEvent(QEvent *e) override;
};
#endif // MAINWINDOW_H

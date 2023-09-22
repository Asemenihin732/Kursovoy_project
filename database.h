#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include "vrach.h"

///Класс для работы с БД
class database
{
    ///Хранение модели БД
    QSqlTableModel *_model;

public:

    ///Конструктор класса
    database();

    ///Деструктор класса
    virtual ~database();

    /// Метод подключения к базе данных
    bool connect(QObject *parent = nullptr);

    /// Метод закрытия базы данных
    void close();

    /// \brief addBolezn Метод добавления данных в БД
    /// \param Bolezn данные отправления
    /// \return Возвращает результат добавления
    bool addBolezn(const Bolezn &bolezn);

    /// \brief editBolezn Метод редактирования данных в БД
    /// \param id Номер записи в БД
    /// \param Bolezn данные отправления
    /// \return Возвращает результат редактирования
    bool editBolezn(const int id, const Bolezn &bolezn);

    /// \brief deleteBolezn метод удаления данных в БД
    /// \param id Номер записи в БД
    /// \return Возвращает результат удаления
    bool deleteBolezn(const int id);

    /// Получение базы данных
    QSqlDatabase getDatabase();

    /// Возвращает модель базы данных
    QSqlTableModel *getModel();

    /// Возвращает строку с результатом запроса медикаментов
    QString getMedicaments(const int id);

    ///Возвращает строку с результатом запроса количества медикаметов
    QString getKolvo(const int id);
};

#endif // DATABASE_H

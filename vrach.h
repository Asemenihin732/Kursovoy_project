#ifndef MOVIES_H
#define MOVIES_H
#include <QDate>
#include <QString>

///Класс данных фильма
class Bolezn
{
    ///Название болезни
    QString _bol;
    ///Высокая температура
    bool _high_temp;
    ///Тошнота
    bool _nausea;
    ///Болит живот
    bool _stom_hurts;
    ///Процедура
    QString _procedure;
    ///id болезни
    int _id_med;

public:
    ///Конструктор класса с параметрами
    Bolezn(QString bol,
           bool high_temp,
           bool nausea,
           bool stom_hurts,
           QString procedure,
           int id_med);
    ///Getter названия болезни
    QString bol() const;
    ///Getter высокой температуры
    bool high_temp() const;
    ///Getter тошноты
    bool nausea() const;
    ///Getter болезни живота
    bool stom_hurts() const;
    ///Getter процедуры
    QString procedure() const;

    ///Setter названия болезни
    void setBol(QString newBol);
    ///Setter высокой температуры
    void setHigh_temp(bool newHigh_temp);
    ///Setter тошноты
    void setNausea(bool newNausea);
    ///Setter болезни живота
    void setStom_hurts(bool newStom_hurts);
    ///Setter поцедур
    void setProcedure(QString newProcedure);
    ///Setter id болезни
    void setId_med(int newId_med);
    ///Getter id болезни
    int id_med() const;
};

#endif // VRACH_H

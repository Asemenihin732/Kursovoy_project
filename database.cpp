#include "database.h"
#include <QSqlResult>
#include <QSqlError>

database::database()
{

}

database::~database()
{
    close();
}

bool database::connect(QObject *parent)
{
    auto db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setConnectOptions("requiressl=0;connect_timeout=2");
    db.setPort(5432);
    db.setDatabaseName("Spravochnik");
    db.setUserName("postgres");
    db.setPassword("root");
    if (!db.open()) {
        return false;
    }
    _model = new QSqlTableModel(parent);
    _model->setTable("thetab");
    _model->select();
    return true;
}

void database::close()
{
    delete _model;
    {getDatabase().close();}
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
}

bool database::addBolezn(const class Bolezn &bolezn)
{
    QSqlQuery query;
    query.prepare("INSERT into thetab ( bolezn, high_temp, nausea, stomach_hurts, procedure, id_med) "
                  "VALUES (:bolezn, :high_temp, :nausea, :stomach_hurts, :procedure, :id_med)");
    query.bindValue(":bolezn", bolezn.bol());
    query.bindValue(":high_temp", bolezn.high_temp());
    query.bindValue(":nausea", bolezn.nausea());
    query.bindValue(":stomach_hurts",bolezn.stom_hurts());
    query.bindValue(":procedure", bolezn.procedure());
    query.bindValue(":id_med", bolezn.id_med());

    return  query.exec();
}

bool database::editBolezn(const int id, const class Bolezn &bolezn)
{
    QSqlQuery query;
    query.prepare("UPDATE thetab SET "
                  "bolezn = :bolezn, high_temp = :high_temp, nausea = :nausea, stomach_hurts = :stomach_hurts, procedure = :procedure, id_med=:id_med "
                  "  WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":bolezn", bolezn.bol());
    query.bindValue(":high_temp", bolezn.high_temp());
    query.bindValue(":nausea", bolezn.nausea());
    query.bindValue(":stomach_hurts",bolezn.stom_hurts());
    query.bindValue(":procedure", bolezn.procedure());
    query.bindValue(":id_med", bolezn.id_med());
    return query.exec();
}

bool database::deleteBolezn(const int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM thetab WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QString database::getMedicaments(const int id)
{
    QSqlQuery query;
    QString zapros = ("SELECT med.med FROM thetab join med using (id_med) where  thetab.id = :id");
    QString Medic;
    query.prepare(zapros);
    qDebug() << zapros;
    query.bindValue(":id", id);
    query.exec();
    qDebug() << query.lastError();
    while (query.next())
    {
        Medic = query.value(0).toString();
        qDebug() << Medic;
    }
    return Medic;
}

QString database::getKolvo(const int id)
{
    QSqlQuery query;
    QString zapros = ("SELECT med.kolvo FROM thetab join med using (id_med) where  thetab.id = :id");
    QString Kolvo;
    query.prepare(zapros);
    qDebug() << zapros;
    query.bindValue(":id", id);
    query.exec();
    qDebug() << query.lastError();
    while (query.next())
    {
        Kolvo = query.value(0).toString();
        qDebug() << Kolvo;
    }
    return Kolvo;
}

QSqlDatabase database::getDatabase()
{
    return QSqlDatabase::database();
}

QSqlTableModel *database::getModel()
{
    return _model;
}

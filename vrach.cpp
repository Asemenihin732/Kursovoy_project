#include "vrach.h"

Bolezn::Bolezn(QString bol,
               bool high_temp,
               bool nausea,
               bool stom_hurts,
               QString procedure,
               int id_med):
    _bol(bol),
    _high_temp(high_temp),
    _nausea(nausea),
    _stom_hurts(stom_hurts),
    _procedure(procedure),
    _id_med(id_med)
{

}

QString Bolezn::bol() const
{
    return _bol;
}

bool Bolezn::high_temp() const
{
    return _high_temp;
}

bool Bolezn::nausea() const
{
    return _nausea;
}

bool Bolezn::stom_hurts() const
{
    return _stom_hurts;
}

QString Bolezn::procedure() const
{
    return _procedure;
}

int Bolezn::id_med() const
{
    return _id_med;
}

void Bolezn::setBol(QString newBol)
{
    _bol=newBol;
}

void Bolezn::setHigh_temp(bool newHigh_temp)
{
    _high_temp=newHigh_temp;
}

void Bolezn::setNausea(bool newNausea)
{
    _nausea=newNausea;
}

void Bolezn::setStom_hurts(bool newStom_hurts)
{
    _stom_hurts=newStom_hurts;
}

void Bolezn::setProcedure(QString newProcedure)
{
    _procedure=newProcedure;
}

void Bolezn::setId_med(int newId_med)
{
    _id_med=newId_med;
}

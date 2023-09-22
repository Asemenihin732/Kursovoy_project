#include "proxymodel.h"

proxyModel::proxyModel(QObject* parent)
 : QSortFilterProxyModel(parent)
{

}


bool proxyModel::lessThan(const QModelIndex &source_left,
                          const QModelIndex &source_right) const
{
    QVariant left  = sourceModel()->data(source_left);
    QVariant right = sourceModel()->data(source_right);

    switch (source_left.column()) {
    default:
    {
        return QString::localeAwareCompare(left.toString(), right.toString()) < 0;
    }
    }
}

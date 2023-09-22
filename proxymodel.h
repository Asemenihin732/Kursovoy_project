#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>
///Класс для сортировки
class proxyModel: public QSortFilterProxyModel
{

    Q_OBJECT
public:
    /// Конструктор по умолчанию
    explicit proxyModel(QObject* parent = nullptr);
protected:
    /**
     * @brief lessThan переопределенный метод для задания правил сортировки, сравнивая два параметра
     * @param source_left первый сравниваемый параметр
     * @param source_right первый сравниваемый параметр
     * @return Если первое значение больше второго, то возвращает true, в противном случае - false
     */
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
};

#endif // PROXYMODEL_H

#ifndef QLISTMODEL_H
#define QLISTMODEL_H

#include <QAbstractListModel>
#include <QSize>
#include <QFont>
#include <QStringList>

#include "robot.h"

class QListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit QListModel(QObject *parent = 0);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    //bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex & index) const;

    //void setData(Robot* r);

private:
    QList<Robot*> list;
signals:

public slots:

};

#endif // QLISTMODEL_H

#include "qlistmodel.h"
#include <QBrush>

QListModel::QListModel(QObject *parent) : QAbstractListModel(parent)
{
}

int QListModel::rowCount(const QModelIndex &parent) const
{
    return list.count();
}

QVariant QListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return "x: " + QString::number(list.at(index.row())->x) + " y: " + QString::number(list.at(index.row())->y);
    case Qt::SizeHintRole:
        return QSize(0, 30);
    case Qt::ToolTipRole:
        return "x: " + QString::number(list.at(index.row())->x) + " y: " + QString::number(list.at(index.row())->y);
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
    case Qt::FontRole:
        return QFont("Times New Roman", 12, QFont::Bold);
    case  Qt::BackgroundRole:
        return QBrush(Qt::green);
    default:
        return QVariant();
        break;
    }
}

//void QListModel::setData(Robot* r)
//{
//    list << r;
//}

Qt::ItemFlags QListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

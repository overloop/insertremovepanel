#include "insertremove/model.h"

namespace InsertRemove {

Model::Model(int rows, int cols, QObject* parent /*= 0*/) : QAbstractTableModel(parent), _data(rows,cols)
{

}

Model::Model(const VariantMatrix& matrix, QObject* parent /*= 0*/) : QAbstractTableModel(parent), _data(matrix)
{

}

/*virtual*/
QModelIndex Model::index(int row, int column,
                          const QModelIndex &parent /*= QModelIndex()*/) const
{
    return createIndex(row,column);
}

/*virtual*/
QModelIndex Model::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

/*virtual*/
int Model::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
    if (parent.isValid())
        return 0;
    return _data.rowCount();
}

/*virtual*/
int Model::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
    if (parent.isValid())
        return 0;
    return _data.columnCount();
}

/*virtual*/
QVariant Model::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
    if (role == Qt::DisplayRole)
    {
        //return QString("%1 %2").arg(index.column()).arg(index.row());
        return _data.at(index.row(),index.column());
    }

    return QVariant();
}

/*virtual*/
bool Model::insertRows(int row, int count, const QModelIndex &parent /*= QModelIndex()*/)
{
    beginInsertRows(parent,row,row+count-1);
    //_row+=count;
    for (int i=0;i<count;i++)
        _data.insertRow(row+i);
    endInsertRows();
    return true;
}

/*virtual*/
bool Model::insertColumns(int column, int count, const QModelIndex &parent /*= QModelIndex()*/)
{
    beginInsertColumns(parent,column,column+count-1);
    for (int i=0;i<count;i++)
        _data.insertColumn(column+i);
    endInsertColumns();
    return true;
}

/*virtual*/
QVariant Model::headerData(int section, Qt::Orientation orientation,
                            int role /*= Qt::DisplayRole*/) const
{
    if (role == Qt::DisplayRole)
        return section + 1;
    return QVariant();
}

/*virtual*/
bool Model::removeRows(int row, int count, const QModelIndex &parent /*= QModelIndex()*/)
{
    beginRemoveRows(parent,row,row+count-1);
    for (int i=0;i<count;i++)
        _data.removeRow(row);
    endRemoveRows();
}

/*virtual*/
bool Model::removeColumns(int column, int count, const QModelIndex &parent /*= QModelIndex()*/)
{
    beginRemoveColumns(parent,column,column+count-1);
    for (int i=0;i<count;i++)
        _data.removeColumn(column);
    endRemoveColumns();
    return true;
}

/*virtual*/
bool Model::setData(const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/)
{
    if (role == Qt::EditRole)
    {
        _data.set(index.row(),index.column(),value);
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

/*virtual*/
Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

} //InsertRemove namespace

#ifndef INSERTREMOVE_MODEL_H
#define INSERTREMOVE_MODEL_H


#include <QAbstractTableModel>
#include "insertremove/matrix.h"

namespace InsertRemove {

/**
  Model that allows to insert and remove rows and columns (demo)
 */
class Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    Model(const VariantMatrix& matrix, QObject* parent = 0);
    Model(int rows = 0, int cols = 0, QObject* parent = 0);

    virtual QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex &parent /*= QModelIndex()*/);
    virtual bool removeColumns(int column, int count, const QModelIndex &parent /*= QModelIndex()*/);

    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    VariantMatrix _data;
};


}
#endif //INSERTREMOVE_MODEL_H

/**
   @author Doronin Stanislav <mugisbrows@gmail.com>

   This file is part of InsertRemovePanel.

   InsertRemovePanel is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as published
   by the Free Software Foundation, either version 3 of the License, or (at
   your option) any later version.

   InsertRemovePanel is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
   Public License for more details.

   You should have received a copy of the GNU General Public License along
   with InsertRemovePanel. If not, see <http://www.gnu.org/licenses/>.

*/

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

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

#ifndef INSERTREMOVE_MATRIX_H
#define INSERTREMOVE_MATRIX_H

#include <QVector>
#include <QVariant>

namespace InsertRemove {

/**
  Just another implementation of 2d array
 */
template<class T>
class Matrix : public QVector< QVector<T> >
{
public:
    Matrix(int rows = 0,int cols = 0)
    {
        init(rows,cols);
    }

    void init(int rows, int cols)
    {
        for (int i=0;i<rows;i++)
        {
            QVector<T> d;
            d.fill(T(),cols);
            this->append(d);
        }
        _rows = rows;
        _cols = cols;
    }

    void resize(int rows, int cols)
    {
        while (_rows>rows)
            removeRow(_rows-1);
        while (_rows<rows)
            appendRow();
        while (_cols>cols)
            removeColumn(_cols-1);
        while (_cols<cols)
            appendColumn();
    }

    void insertRow(int n, const QVector<T>& data = QVector<T>())
    {
        Q_ASSERT(n>=0 && n<=_rows);
        Q_ASSERT(data.size() == 0 || data.size() == _cols);

        QVector<T> dat;
        for(int i=0;i<_cols;i++)
        {
            T t = (data.size()>i)?(data.at(i)):(T());
            dat << t;
        }
        this->insert(n,dat);
        _rows++;
    }

    void appendRow(const QVector<T>& data = QVector<T>())
    {
        insertRow(_rows,data);
    }

    void replaceRow(int n, const QVector<T>& data = QVector<T>())
    {
        Q_ASSERT(data.size() == 0 || data.size() == _cols);
        for (int i=0;i<_cols;i++)
        {
            T t = (data.size()>i)?(data.at(i)):(T());
            set(n,i,t);
        }
    }

    void insertColumn(int n, const QVector<T>& data = QVector<T>())
    {
        Q_ASSERT(n>=0 && n<=_cols);
        Q_ASSERT(data.size() == 0 || data.size() == _rows);
        for (int i=0;i<_rows;i++)
        {
            T t = (data.size()>i)?(data.at(i)):(T());
            QVector< QVector<T> >::operator [](i).insert(n,t);
        }
        _cols++;
    }

    void appendColumn(const QVector<T>& data = QVector<T>())
    {
        insertColumn(_cols,data);
    }

    void replaceColumn(int n, const QVector<T>& data = QVector<T>())
    {
        Q_ASSERT(data.size() == 0 || data.size() == _rows);
        for (int i=0;i<_rows;i++)
        {
            T t = (data.size()>i)?(data.at(i)):(T());
            set(i,n,t);
        }
    }

    void removeColumn(int n)
    {
        Q_ASSERT(n>=0 && n<_cols);
        for (int i=0;i<_rows;i++)
        {
            QVector< QVector<T> >::operator [](i).remove(n);
        }
        _cols--;
    }

    void removeRow(int n)
    {
        Q_ASSERT(n>=0 && n<_rows);
        QVector< QVector<T> >::remove(n);
        _rows--;
    }

    void set(int row, int col, const T& t)
    {
        Q_ASSERT(row>=0 && row<_rows && col>=0 && col<_cols);
        QVector< QVector<T> >::operator [](row).replace(col,t);
    }

    const T& at(int row, int col) const
    {
        return QVector< QVector<T> >::at(row).at(col);
    }

    int rowCount() const
    {
        return _rows;
    }

    int columnCount() const
    {
        return _cols;
    }

private:
    int _rows,_cols;
};

/**
  Just another implementation of 2d array of variant
 */
class VariantMatrix : public Matrix<QVariant>
{
public:
    VariantMatrix(int rows = 0,int cols = 0);
};

}
#endif //INSERTREMOVE_MATRIX_H

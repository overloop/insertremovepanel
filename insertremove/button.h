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

#ifndef INSERTREMOVE_BUTTON_H
#define INSERTREMOVE_BUTTON_H

#include "insertremove/insertremove.h"

#include <QPushButton>
class QTableView;
class QAbstractItemModel;
class QAbstractScrollArea;

namespace InsertRemove {

/**
 Button that adds or removes column or row on QAbstractItemModel that displayed on QTableView
 */
class Button : public QPushButton
{
    Q_OBJECT
public:
    Button(Qt::Orientation orientation, InsertRemove::Type type, PolicyFlags policy = NothingAllowed, QWidget* parent = 0);
    ~Button();

    static const int SIZE_PX = 20;

protected:

    /**
      QSize -> (int x, int y) or (int y, int x), QPoint -> (int x, int y) or (int y, int x), according to orientation
     */
    virtual void getSizes(QTableView* table, QAbstractItemModel* model, int* m, int* n, int* btn1, int* btn2, int* pnt1, int* pnt2, int* ofs1, int* ofs2) const;
    virtual void nearestBorder(int policy, int pos, int sizes[], int count, int* n, int* coord) const;
    virtual void nearestMiddle(int policy, int pos, int sizes[], int count, int* n, int* coord) const;

    /** Widget size minus scrolls sizes
      */
    QSize usefulWidgetSize(QAbstractScrollArea* widget) const;

    InsertRemove::Type _type;
    Qt::Orientation _orientation;
    int _modelIndex;
    QPoint _point;
    PolicyFlags _policy;

public slots:

    void placeButton();
    void setPoint(const QPoint& point);
    void setPolicy(PolicyFlags policy);

private slots:
    void on_clicked();
};

}
#endif //INSERTREMOVE_BUTTON_H

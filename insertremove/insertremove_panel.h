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

#ifndef INSERTREMOVE_PANEL_H
#define INSERTREMOVE_PANEL_H

#include <QObject>
#include <QPoint>

#include "insertremove/insertremove.h"

class QTableView;

namespace InsertRemove {

class Button;

/**
  Panel tracks mouse move events on some QTableView and puts insert and remove buttons
 */
class Panel : public QObject
{
    Q_OBJECT
public:
    Panel(InsertRemove::PolicyFlags horizontalPolicy = NothingAllowed, InsertRemove::PolicyFlags verticalPolicy = NothingAllowed, QObject* parent = 0);
    ~Panel();

    void attach(QTableView* table);
    void detach(QTableView* table);

    void setPolicy(Qt::Orientation orientation, PolicyFlags policy);

protected:
    void createButtons(InsertRemove::PolicyFlags horizontalPolicy, InsertRemove::PolicyFlags verticalPolicy);
    bool eventFilter(QObject* object, QEvent* event);

    Button* _buttons[4];
    QTableView* _table;

public slots:
    void placeButtons();

};

}
#endif //INSERTREMOVE_PANEL_H

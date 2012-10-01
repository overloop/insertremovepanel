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

#include <QMouseEvent>
#include <QTableView>
#include <QHeaderView>
#include <QDebug>

#include "insertremove/panel.h"
#include "insertremove/button.h"

namespace InsertRemove {

Panel::Panel(InsertRemove::PolicyFlags horizontalPolicy /*= 0*/, InsertRemove::PolicyFlags verticalPolicy /*= 0*/, QObject* parent /*= 0*/) :
    QObject(parent)
{
    createButtons(horizontalPolicy,verticalPolicy);
}

Panel::~Panel()
{
    for (int i=0;i<4;i++)
    {
        if (!_buttons[i]->parent())
            delete _buttons[i];
    }
}

void Panel::attach(QTableView* table)
{
    for (int i=0;i<4;i++)
        _buttons[i]->setParent(table);
    _table = table;

    table->setMouseTracking(true);
    table->viewport()->installEventFilter(this);
    connect(table->horizontalHeader(),SIGNAL(sectionResized(int,int,int)),this,SLOT(placeButtons()));
    connect(table->verticalHeader(),SIGNAL(sectionResized(int,int,int)),this,SLOT(placeButtons()));
    placeButtons();
}

void Panel::detach(QTableView* table)
{
    for (int i=0;i<4;i++)
        _buttons[i]->setParent(0);
    _table = 0;

    disconnect(table->horizontalHeader(),SIGNAL(sectionResized(int,int,int)),this,SLOT(placeButtons()));
    disconnect(table->verticalHeader(),SIGNAL(sectionResized(int,int,int)),this,SLOT(placeButtons()));
    placeButtons();
}

void Panel::setPolicy(Qt::Orientation orientation, PolicyFlags policy)
{
    Button* buttons[2];
    if (orientation == Qt::Horizontal)
    {
        buttons[0] = _buttons[0];
        buttons[1] = _buttons[1];
    }
    else
    {
        buttons[0] = _buttons[2];
        buttons[1] = _buttons[3];
    }

    buttons[0]->setPolicy(policy);
    buttons[1]->setPolicy(policy);
}

void Panel::createButtons(InsertRemove::PolicyFlags horizontalPolicy, InsertRemove::PolicyFlags verticalPolicy)
{
    Type types[] = {Insert, Remove, Insert, Remove};
    Qt::Orientation orientations[] = { Qt::Horizontal, Qt::Horizontal, Qt::Vertical, Qt::Vertical };
    PolicyFlags policies[] = {horizontalPolicy,horizontalPolicy,verticalPolicy,verticalPolicy};
    for (int i=0;i<4;i++)
    {
        Button* button = new Button(orientations[i],types[i],policies[i],0);
        _buttons[i] = button;
        connect(button,SIGNAL(clicked()),this,SLOT(placeButtons()));
    }
}

void Panel::placeButtons()
{
    for (int i=0;i<4;i++)
        _buttons[i]->placeButton();
}

bool Panel::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::MouseMove && object == _table->viewport())
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (!mouseEvent)
            return false;
        for (int i=0;i<4;i++)
            _buttons[i]->setPoint(mouseEvent->pos());
    }
    return false;
}

} //InsertRemove namespace

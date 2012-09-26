
#include "insertremove/panel.h"
#include "insertremove/insertremove.h"
#include "insertremove/button.h"

#include <QMouseEvent>

#include <QTableView>
#include <QHeaderView>

namespace InsertRemove {

Panel::Panel(InsertRemove::PolicyFlags horizontalPolicy /*= 0*/, InsertRemove::PolicyFlags verticalPolicy /*= 0*/, QObject* parent /*= 0*/) :
    QObject(parent)
{
    createButtons(parent,horizontalPolicy,verticalPolicy);
}

Panel::~Panel()
{

}

void Panel::attach(QTableView* table)
{
    for (int i=0;i<4;i++)
        _buttons[i]->setParent(table);
    table->setMouseTracking(true);
    installFilter();
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

void Panel::createButtons(QObject* parent, InsertRemove::PolicyFlags horizontalPolicy, InsertRemove::PolicyFlags verticalPolicy)
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

void Panel::installFilter()
{
    QTableView* table = dynamic_cast<QTableView*>(_buttons[0]->parent());
    if (!table) return ;
    table->viewport()->installEventFilter(this);
    connect(table->horizontalHeader(),SIGNAL(sectionResized(int,int,int)),this,SLOT(placeButtons()));
    connect(table->verticalHeader(),SIGNAL(sectionResized(int,int,int)),this,SLOT(placeButtons()));
    placeButtons();
}

void Panel::placeButtons()
{
    for (int i=0;i<4;i++)
        _buttons[i]->placeButton();
}

bool Panel::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (!mouseEvent) return false;
        for (int i=0;i<4;i++)
            _buttons[i]->setPoint(mouseEvent->pos());
    }
    return false;
}

} //InsertRemove namespace

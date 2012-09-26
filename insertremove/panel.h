#ifndef INSERTREMOVE_PANEL_H
#define INSERTREMOVE_PANEL_H

#include <QObject>
#include <QPoint>

#include "insertremove/insertremove.h"

class QTableView;

namespace InsertRemove {

class Button;

class Panel : public QObject
{
    Q_OBJECT
public:
    Panel(InsertRemove::PolicyFlags horizontalPolicy = NothingAllowed, InsertRemove::PolicyFlags verticalPolicy = NothingAllowed, QObject* parent = 0);
    ~Panel();

    void attach(QTableView* table);

    void setPolicy(Qt::Orientation orientation, PolicyFlags policy);

protected:
    void installFilter();
    void createButtons(QObject* parent, InsertRemove::PolicyFlags horizontalPolicy, InsertRemove::PolicyFlags verticalPolicy);
    bool eventFilter(QObject *, QEvent *);

    Button* _buttons[4];

public slots:
    void placeButtons();

};

}
#endif //INSERTREMOVE_PANEL_H

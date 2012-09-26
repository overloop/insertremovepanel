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
    bool eventFilter(QObject *, QEvent *);

    Button* _buttons[4];
    QTableView* _table;

public slots:
    void placeButtons();

};

}
#endif //INSERTREMOVE_PANEL_H

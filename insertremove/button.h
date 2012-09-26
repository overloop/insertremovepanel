
#ifndef INSERTREMOVE_BUTTON_H
#define INSERTREMOVE_BUTTON_H

#include "insertremove/insertremove.h"

#include <QPushButton>
class QTableView;
class QAbstractItemModel;
class QAbstractScrollArea;

namespace InsertRemove {

class Button : public QPushButton
{
    Q_OBJECT
public:
    Button(Qt::Orientation orientation, InsertRemove::Type type, PolicyFlags policy = NothingAllowed, QWidget* parent = 0);
    ~Button();

    static const int SIZE_PX = 20;

protected:

    virtual void getSizes(QTableView* table, QAbstractItemModel* model, int* m, int* n, int* btn1, int* btn2, int* pnt1, int* pnt2, int* ofs1, int* ofs2) const;
    virtual void nearestBorder(int policy, int pos, int sizes[], int count, int* n, int* coord) const;
    virtual void nearestMiddle(int policy, int pos, int sizes[], int count, int* n, int* coord) const;
    QSize usefulWidgetSize(QAbstractScrollArea* widget) const;

    InsertRemove::Type _type;
    Qt::Orientation _orientation;
    int _modelIndex;
    QPoint _point;
    PolicyFlags _policy;
    /*QTableView* _table;*/

public slots:
    void placeButton();
    void setPoint(const QPoint& point);
    void setPolicy(PolicyFlags policy);

private slots:
    void on_clicked();
};

}
#endif //INSERTREMOVE_BUTTON_H

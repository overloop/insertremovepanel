#include "insertremove/button.h"

#include <QAbstractItemModel>
#include <QTableView>
#include <QHeaderView>
//#include <QAbstractScrollArea>
#include <QScrollBar>
#include <QDebug>

#include "insertremove/insertremove.h"

namespace InsertRemove {

Button::Button(Qt::Orientation orientation, InsertRemove::Type type, PolicyFlags policy /*= 0*/, QWidget* parent /*= 0*/) :
    QPushButton(parent),
    _type(type),
    _orientation(orientation),
    _point(QPoint(0,0)),
    _policy(policy)
{
    QString plus_css =
            "*         {image: url(':/plus-icon.png'); border: 0;}"
            "*:hover   {image: url(':/plus-icon-hover.png');}"
            "*:pressed {image: url(':/plus-icon-pressed.png');} ";

    QString minus_css =
            "*         {image: url(':/minus-icon.png'); border: 0;}"
            "*:hover   {image: url(':/minus-icon-hover.png');}"
            "*:pressed {image: url(':/minus-icon-pressed.png');} ";

    if (_type == Insert)
        setStyleSheet(plus_css);
    else
        setStyleSheet(minus_css);

    setFixedSize(SIZE_PX,SIZE_PX);
    placeButton();
    connect(this,SIGNAL(clicked()),this,SLOT(on_clicked()));
}

Button::~Button()
{

}

void Button::setPolicy(PolicyFlags policy)
{
    if ( _policy != policy)
    {
        _policy = policy;
        placeButton();
    }
}

//horizontal: 1=w 2=h
//vertical: 1=h 2=w
void Button::getSizes(QTableView* table, QAbstractItemModel* model, int* m, int* n, int* btn1, int* btn2, int* pnt1, int* pnt2, int* ofs1, int* ofs2) const
{
    if (_orientation == Qt::Horizontal)
    {
        *m = model->columnCount();
        *n = model->rowCount();
        *btn1 = size().width();
        *btn2 = size().height();
        *ofs1 = table->horizontalHeader()->offset();
        *ofs2 = table->verticalHeader()->offset();
        *pnt1 = _point.x();
        *pnt2 = _point.y();
    }
    else
    {
        *m = model->rowCount();
        *n = model->columnCount();
        *btn1 = size().height();
        *btn2 = size().width();
        *ofs1 = table->verticalHeader()->offset();
        *ofs2 = table->horizontalHeader()->offset();
        *pnt1 = _point.y();
        *pnt2 = _point.x();
    }
}

void Button::nearestBorder(int policy, int pos, int sizes[], int count, int* n, int* coord) const
{
    int sum = 0;
    int i;

    int accsizes[count];
    for (i=0;i<count;i++)
    {
        sum += sizes[i];
        accsizes[i] = sum;
    }

    if ( !(policy & InsertRemove::InsertAllowed) ) //insert not allowed -> append or prepend or hide
    {
        if ( (policy & InsertRemove::PrependAllowed) && (policy & InsertRemove::AppendAllowed) ) //prepend and append allowed -> append or prepend
        {
            if (pos>sum-pos)
            {
                *n = count;
                *coord = sum;
            }
            else
            {
                *n = 0;
                *coord = 0;
            }
        }
        else if (policy & InsertRemove::AppendAllowed) //append allowed -> append
        {
            *n = count;
            *coord = sum;
        }
        else if (policy & InsertRemove::PrependAllowed) //prepend allowed -> prepend
        {
            *n = 0;
            *coord = 0;
        }
        else //nothing allowed -> hide
        {
            *n = -1;
            *coord = 0;
        }
    }
    else if (policy & InsertRemove::InsertAllowed) //insert allowed -> insert
    {
        if (pos > sum)
        {
            *n = count;
            *coord = sum;
            return ;
        }

        for (i=0;i<count;i++)
            if (accsizes[i]>=pos)
                break;

        Q_ASSERT(i<count && i>=0); //не должно быть походу

        int isize = sizes[i];
        int asize = accsizes[i];

        if (pos-(asize-isize)>(asize-pos))
        {
            *n = i+1;
            *coord = asize;
        }
        else
        {
            *n = i;
            *coord = asize - isize;
        }
    }
}

void Button::nearestMiddle(int policy, int pos, int sizes[], int count, int* n, int* coord) const
{
    int sum = 0;
    int i;
    int isize;

    if ( !(policy & InsertRemove::RemoveAllowed) || count<1 )
    {
        *n = -1;
        *coord = 0;
    }

    for (i=0;i<count;i++)
    {
        isize = sizes[i];
        sum+=isize;
        if (sum>pos)
            break;
    }

    //last one
    if (sum<pos)
    {
        *n = count-1;
        *coord = sum - isize / 2;
        return ;
    }

    //one of
    *n = i;
    *coord = sum - isize / 2;
}

void Button::placeButton()
{
    //QTableView* table = dynamic_cast<QTableView*>(parent());
    //Q_ASSERT(table!=0);

    QTableView* _table = dynamic_cast<QTableView*>(this->parent());
    if (!_table)
    {
        setVisible(false);
        return ;
    }


    if (_point.isNull())
    {
        QSize s = _table->viewport()->size();
        //qDebug() << s;
        _point = QPoint(s.width(),s.height());
    }

    QAbstractItemModel* model = _table->model();
    if (!model) return;

    int n,m,bsize1,bsize2,offset1,offset2,point1,point2;
    getSizes(_table,model,&m,&n,&bsize1,&bsize2,&point1,&point2,&offset1,&offset2);

    int coord1;
    int coord2 = 0;

    int sizes[m];
    if (_orientation == Qt::Horizontal)
    {
        for (int i=0;i<m;i++) sizes[i] = _table->columnWidth(i);
        for (int i=0;i<n;i++) coord2 += _table->rowHeight(i);
    }
    else
    {
        for (int i=0;i<m;i++) sizes[i] = _table->rowHeight(i);
        for (int i=0;i<n;i++) coord2 += _table->columnWidth(i);
    }

    if (_type == InsertRemove::Insert)
    {
        nearestBorder(_policy,point1+offset1,sizes,m,&_modelIndex,&coord1);
    }
    else // _type == InsertRemove::Remove
    {
        nearestMiddle(_policy,point1+offset1,sizes,m,&_modelIndex,&coord1);
    }

    coord1 -= bsize1 / 2;

    QSize vp = usefulWidgetSize(_table);
    QPoint sh = _table->viewport()->mapToParent(QPoint(0,0)); //насколько viewport меньше table

    if (_orientation == Qt::Horizontal)
    {
        if (coord2 - offset2 + bsize2 + sh.y() > vp.height())
            coord2 = vp.height() - bsize2 + offset2 - sh.y();
    }
    else
    {
        if (coord2 - offset2 + bsize2 + sh.x() > vp.width())
            coord2 = vp.width() - bsize2 + offset2 - sh.x();
    }

    if (_orientation == Qt::Horizontal)
    {
        QPoint p = _table->viewport()->mapToParent(QPoint(coord1 - offset1,coord2 - offset2));
        setGeometry(QRect(p,size()));
    }
    else
    {
        QPoint p = _table->viewport()->mapToParent(QPoint(coord2 - offset2,coord1 - offset1));
        setGeometry(QRect(p,size()));
    }

    if (_type == InsertRemove::Insert)
    {
        setVisible(_modelIndex>=0);
    }
    else
    {
        setVisible((_policy & InsertRemove::RemoveAllowed) && (_modelIndex>-1));
    }

}

QSize Button::usefulWidgetSize(QAbstractScrollArea* widget) const
{
    QSize s = widget->size();
    int v = 0;
    int h = 0;

    if (widget->horizontalScrollBar()->isVisible())
        h = widget->horizontalScrollBar()->height();
    if (widget->verticalScrollBar()->isVisible())
        v = widget->verticalScrollBar()->width();

    return QSize(s.width()-v,s.height()-h);
}

void Button::setPoint(const QPoint& point)
{
    if (_point != point)
    {
        _point = point;
        placeButton();
    }
}

void Button::on_clicked()
{
    QTableView* _table = dynamic_cast<QTableView*>(this->parent());
    if (!_table)
        return ;

    QAbstractItemModel* model = _table->model();
    if (!model) return;

    if (_type == InsertRemove::Insert)
    {
        if (_orientation == Qt::Horizontal)
        {
            model->insertColumn(_modelIndex);
        }
        else
        {
            model->insertRow(_modelIndex);
        }
    }
    else
    {
        //remove
        if (_orientation == Qt::Horizontal)
        {
            model->removeColumn(_modelIndex);
        }
        else
        {
            model->removeRow(_modelIndex);
        }
    }
}


} //InsertRemove namespace

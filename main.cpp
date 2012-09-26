#include <QApplication>

#include <QTableView>

#include "insertremove/insertremove.h"
#include "insertremove/matrix.h"
#include "insertremove/model.h"
#include "insertremove/panel.h"

void demoMatrix(InsertRemove::VariantMatrix& data);
void resize(QWidget* widget, int w, int h);

int main(int argc, char** argv)
{
    QApplication app(argc,argv);

    using namespace InsertRemove;

    VariantMatrix data;
    demoMatrix(data);

    Model model(data);

    QTableView view;
    view.setModel(&model);

    Panel panel(EverythingAllowed,EverythingAllowed);
    panel.setPolicy(Qt::Horizontal, (PolicyFlags) RemoveAllowed | AppendAllowed );
    panel.attach(&view);

    view.show();
    resize(&view,600,400);

    return app.exec();
}

void resize(QWidget* widget, int w, int h)
{
    QRect rect = widget->geometry();
    rect.setWidth(w);
    rect.setHeight(h);
    widget->setGeometry(rect);
}

void demoMatrix(InsertRemove::VariantMatrix& data)
{
    int cols = 4;
    int rows = 4;
    data.resize(rows,cols);
    for (int i=0;i<rows;i++)
        for (int j=0;j<cols;j++)
            data[i][j] = QString("%1 %2").arg(i).arg(j);
}

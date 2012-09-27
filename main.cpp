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
#include <QApplication>

#include <QTableView>

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

#include "reversimainwindow.h"
#include "selectdialog.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SelectDialog s;
    if (s.exec() == QDialog::Accepted)
    {
        ReversiMainWindow win(0, s.get_humanplayer(), s.get_search_depth());
        win.show();
        return app.exec();
    }
    else
    {
        return 0;
    }
}

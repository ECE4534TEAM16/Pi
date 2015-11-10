#include "widget.h"
#include <QApplication>
#include <qdebug.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    w.resize(900,900);
    qDebug() << QT_VERSION_STR;

    return a.exec();
}

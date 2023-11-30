#include "fridgelogin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fridgeLogin w;
    w.show();

    return a.exec();
}

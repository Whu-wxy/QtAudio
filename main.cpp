#include "audiodialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AudioDialog w;
    w.show();

    return a.exec();
}

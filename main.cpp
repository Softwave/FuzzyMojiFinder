#include "fuzzymojiapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fuzzymojiapp w;

    w.show();
    return a.exec();
}

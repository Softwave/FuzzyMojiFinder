#include "fuzzymojiapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fuzzymojiapp w;

    w.setWindowIcon(QIcon(":/fuzzymojifinder.png"));
    w.show();
    return a.exec();
}

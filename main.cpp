#include "fuzzymojiapp.h"

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fuzzymojiapp w;

    // Create the system tray icon
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon(QIcon(":/fuzzymojifinder.png"), &w);
    trayIcon->setToolTip("FuzzyMojiFinder: Double click to show/hide");
    trayIcon->show();

    // Setup the system tray icon menu
    QMenu* trayIconMenu = new QMenu(&w);

    // Show/hide action
    QAction* showHideAction = trayIconMenu->addAction("Show/Hide");
    QObject::connect(showHideAction, &QAction::triggered, [&w](){
        if (w.isVisible())
        {
            w.hide();
        }
        else
        {
            w.show();
        }
    });

    // About action
    QAction* aboutAction = trayIconMenu->addAction("About");
    QObject::connect(aboutAction, &QAction::triggered, [](){
        QMessageBox::about(nullptr, "About FuzzyMojiFinder", "FuzzyMojiFinder is a simple emoji finder application. You can search for emojis and copy them to the clipboard. \n(C) Jessica Leyba 2024 GPLv3.0 License.");
    });

    // Quit action
    QAction* quitAction = trayIconMenu->addAction("Quit");
    QObject::connect(quitAction, &QAction::triggered, &a, &QApplication::quit);

    // Clicking on the system tray icon will show/hide the window
    QObject::connect(trayIcon, &QSystemTrayIcon::activated, [&w, trayIcon](QSystemTrayIcon::ActivationReason reason){
        if (reason == QSystemTrayIcon::DoubleClick)
        {
            if (w.isVisible())
            {
                w.hide();
            }
            else
            {
                w.show();
            }
        }


    });

    // Set the context menu
    trayIcon->setContextMenu(trayIconMenu);

    w.setWindowIcon(QIcon(":/fuzzymojifinder.png"));
    w.show();
    return a.exec();
}

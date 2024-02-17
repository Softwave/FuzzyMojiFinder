#ifndef FUZZYMOJIAPP_H
#define FUZZYMOJIAPP_H

#include <QMainWindow>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QFontDatabase>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include <QGuiApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVBoxLayout>
#include <QList>
#include <QString>
#include <QMap>
#include <QVariantMap>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include <QStyleFactory>
#include <QClipboard>
#include <QMouseEvent>
#include <QMenu>

class EmojiListWidget : public QListWidget
{
    Q_OBJECT

public:
    EmojiListWidget(QWidget *parent = nullptr) : QListWidget(parent) {}

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::RightButton)
        {
            QPoint pos = event->pos();
            QListWidgetItem *item = itemAt(pos);
            if (item)
            {
                QMenu contextMenu;
                QAction *copyAction = contextMenu.addAction("Copy");
                QAction *selectedAction = contextMenu.exec(mapToGlobal(pos));
                if (selectedAction == copyAction)
                {
                    // Copy only the emoji, not the description
                    QString emoji = item->text().split(" ").at(0);
                    QGuiApplication::clipboard()->setText(emoji);
                }
            }
        }
        else
        {
            QListWidget::mousePressEvent(event);
        }
    }
};

class fuzzymojiapp : public QMainWindow
{
    Q_OBJECT

public:
    fuzzymojiapp(QWidget *parent = nullptr);

private slots:
    void performSearch();
    void copySelectedEmoji();

private:
    void initUI();
    void addEmojisToList();

    QLineEdit *searchBar;
    EmojiListWidget *emojiListWidget;
    QPushButton *copyButton;


    QList<QVariantMap> emojiList;
};




#endif // FUZZYMOJIAPP_H

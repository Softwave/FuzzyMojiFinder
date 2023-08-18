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
    int levenshteinDistance(const QString &s1, const QString &s2);

    QLineEdit *searchBar;
    QListWidget *emojiListWidget;
    QPushButton *copyButton;


    QList<QVariantMap> emojiList;
};

#endif // FUZZYMOJIAPP_H

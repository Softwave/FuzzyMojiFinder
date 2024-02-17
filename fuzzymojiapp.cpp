#include "fuzzymojiapp.h"


fuzzymojiapp::fuzzymojiapp(QWidget *parent)
    : QMainWindow(parent)
{



    QFile jsonFile(":/emoji.json");
    if (jsonFile.open(QIODevice::ReadOnly))
    {
        QByteArray jsonData = jsonFile.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        QJsonArray jsonArray = doc.array();

        for (const QJsonValue &value : jsonArray)
        {
            if (value.isObject())
            {
                QJsonObject jsonObject = value.toObject();
                emojiList.append(jsonObject.toVariantMap());
            }
        }
    }

    QFontDatabase::addApplicationFont("NotoColorEmoji.ttf");


    initUI();

    connect(searchBar, &QLineEdit::textChanged, this, &fuzzymojiapp::performSearch);
    connect(copyButton, &QPushButton::clicked, this, &fuzzymojiapp::copySelectedEmoji);
}

void fuzzymojiapp::initUI()
{
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search...");
    connect(searchBar, &QLineEdit::textChanged, this, &fuzzymojiapp::performSearch);

    emojiListWidget = new EmojiListWidget(this);
    emojiListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    emojiListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


    copyButton = new QPushButton("Copy Emoji to Clipboard", this);
    connect(copyButton, &QPushButton::clicked, this, &fuzzymojiapp::copySelectedEmoji);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(searchBar);
    mainLayout->addWidget(emojiListWidget);
    mainLayout->addWidget(copyButton);

    QWidget *mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    setWindowTitle("FuzzyMoji Finder");

    // Make not resizable now
    setFixedSize(300, 400);

    // Add emojis to list
    addEmojisToList();



}

void fuzzymojiapp::copySelectedEmoji()
{
    // Copy the selected emoji to the clipboard but not the description
    QList<QListWidgetItem *> selectedItems = emojiListWidget->selectedItems();
    if (selectedItems.length() > 0)
    {
        QListWidgetItem *selectedItem = selectedItems[0];
        QString emojiText = selectedItem->text();
        int emojiIndex = emojiText.indexOf(" - ");
        emojiText = emojiText.left(emojiIndex);
        QGuiApplication::clipboard()->setText(emojiText);
    }
}

void fuzzymojiapp::performSearch()
{
    // Only post emojies that have a match in their description or tags
    emojiListWidget->clear();
    QString searchTerm = searchBar->text();
    for (const QVariantMap &emoji : emojiList)
    {
        QString description = emoji["description"].toString();
        QString tags = emoji["tags"].toString();
        QString emojiChar = emoji["emoji"].toString();

        if (description.contains(searchTerm, Qt::CaseInsensitive) ||
            tags.contains(searchTerm, Qt::CaseInsensitive))
        {
            QListWidgetItem *item = new QListWidgetItem;
            QFont itemFont("Noto Color Emoji", 12);
            item->setFont(itemFont);
            item->setText(emojiChar + " - " + description);
            emojiListWidget->addItem(item);
        }
    }
}


void fuzzymojiapp::addEmojisToList()
{
    // Add the emojis frmo emojiList to emojiListWidget
    for (const QVariantMap &emojiData : emojiList)
    {
        QString emoji = emojiData["emoji"].toString();
        QString description = emojiData["description"].toString();
        QListWidgetItem *listItem = new QListWidgetItem(QString("%1 - %2").arg(emoji, description));
        QFont itemFont("Noto Color Emoji", 12);
        listItem->setFont(itemFont);
        emojiListWidget->addItem(listItem);
        emojiListWidget->update();
    }
}


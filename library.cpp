// #include <iostream>
#include "library.h"
#include <QString>
#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QJsonValueRef>

using namespace std;

Library::Library() {}

void Library::loadData()
{
    QFile file(this->filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open: " << filePath;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());

    if (!doc.isArray())
    {
        qWarning() << "Expected JSON array in: " << filePath;
        return;
    }

    QJsonArray jsonArray = doc.array();
    for (const QJsonValue &value : jsonArray)
    {
        if (value.isObject())
        {
            QJsonObject item = value.toObject();
            LibraryItem libraryItem;
            libraryItem.setID(item["id"].toString());
            libraryItem.setTitle(item["title"].toString());
            libraryItem.setAuthor(item["author"].toString());
            libraryItem.setBorrowing(item["isBorrowed"].toBool());

            if (item.contains("genre"))
            {
                Book book(item);
                booksCatalogue.append(book);
            }
            else if (item.contains("issueNumber"))
            {
                Magazine magazine(item);
                magsCatalogue.append(magazine);
            }
        }
    }
}

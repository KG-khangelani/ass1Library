#ifndef BOOK_H
#define BOOK_H

#include "libraryitem.h"
#include <QJsonValue>
#include <QJsonObject>

class Book : public LibraryItem
{
public:
    Book();
    Book(QJsonObject item);
    QString getGenre();
    void setGenre(const QString &genre);
    void displayInfo() override
    {
        LibraryItem::displayInfo();
        printf("Genre: %s\n", genre.toStdString().c_str());
    }

private:
    QString genre;
};

#endif // BOOK_H

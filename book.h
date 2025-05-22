#ifndef BOOK_H
#define BOOK_H

#include "libraryitem.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QString>

class Book : public LibraryItem
{
public:
    Book();
    Book(const QJsonObject &item);
    QString getGenre() const;
    void setGenre(const QString &genre);
    void displayInfo() const override
    {
        LibraryItem::displayInfo();
        printf("Genre: %s\n", genre.toStdString().c_str());
    }
    friend bool operator==(const Book &lhs, const Book &rhs)
    {
        return lhs.getTitle() == rhs.getTitle() &&
               lhs.getAuthor() == rhs.getAuthor() &&
               lhs.getID() == rhs.getID() &&
               lhs.getIsBorrowed() == rhs.getIsBorrowed() &&
               lhs.genre == rhs.genre;
    };

private:
    QString genre;
};

#endif // BOOK_H

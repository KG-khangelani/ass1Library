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
    void setGenre();

private:
    QString genre;
};

#endif // BOOK_H

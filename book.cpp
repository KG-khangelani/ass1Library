#include "book.h"
#include <QString>
#include <QJsonObject>

Book::Book() {}

Book::Book(const QJsonObject &item)
{
    setID(item["id"].toString());
    setAuthor(item["author"].toString());
    setBorrowing(item["isBorrowed"].toBool());
    setTitle(item["title"].toString());
    setGenre(item["genre"].toString());
}

QString Book::getGenre() const
{
    return this->genre;
}

void Book::setGenre(const QString &genre)
{
    this->genre = genre;
}

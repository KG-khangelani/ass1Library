#include "book.h"
#include <QString>
#include <QJsonObject>

Book::Book() {}

Book::Book(const QJsonObject &item)
{
    setID(item["id"].toString());
    setAuthor(item["fullname"].toString());
    setBorrowing(item["is_borrowed"].toBool());
    setTitle(item["title"].toString());
    setGenre(item["genre"].toString());
}

QString Book::getGenre() const
{
    return this->genre;
}

void Book::setGenre(const QString genre)
{
    this->genre = genre;
}

#include "book.h"

Book::Book() {}

Book::Book(QJsonObject item)
{
    setID(item["id"].toString());
    setAuthor(item["fullname"].toString());
    setBorrowing(item["is_borrowed"].toBool());
    setTitle(item["title"].toString());
    setGenre(item["genre"].toString());
}

QString Book::getGenre()
{
    return this->genre;
}

void Book::setGenre(const QString &genre)
{
    this->genre = genre;
}

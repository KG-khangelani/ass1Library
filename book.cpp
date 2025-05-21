#include "book.h"

Book::Book() {}

Book::Book(QJsonObject  item) {
    setID(item["id"].toInt());
    setAuthor(item["fullname"].toString());
    setBorrowing(item["is_borrowed"].toBool());
    setTitle(item["title"].toString());
}

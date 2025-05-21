#include "libraryitem.h"
#include <QString>
#include <QDebug>

LibraryItem::LibraryItem() {}

QString LibraryItem::getTitle() const
{
    return this->title;
}

QString LibraryItem::getAuthor() const
{
    return this->author;
}

QString LibraryItem::getID() const
{
    return this->id;
}

void LibraryItem::setID(QString value)
{
    this->id = value;
}

void LibraryItem::setTitle(QString value)
{
    this->title = value;
}

bool LibraryItem::getIsBorrowed() const
{
    return this->isBorrowed;
}

void LibraryItem::setAuthor(QString fullname)
{
    this->author = fullname;
}

void LibraryItem::setBorrowing(bool value)
{
    this->isBorrowed = value;
}

void LibraryItem::displayInfo() const
{
    printf("ID: %s\n", id.toStdString().c_str());
    printf("Title: %s\n", title.toStdString().c_str());
    printf("Author: %s\n", author.toStdString().c_str());
    printf("Is Borrowed: %s\n", isBorrowed ? "Yes" : "No");
}

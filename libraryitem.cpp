#include "libraryitem.h"
#include <QString>
#include <QDebug>

LibraryItem::LibraryItem() {}

QString LibraryItem::getTitle() {
    return this->title;
}

QString LibraryItem::getAuthor() {
    return this->author;
}

int LibraryItem::getID() {
    return this->id;
}

void LibraryItem::setID(int value) {
    this -> id = value;
}

void LibraryItem::setTitle(QString value) {
    this -> title = value;
}

bool LibraryItem::getIsBorrowed() {
    return this -> isBorrowed;
}

void LibraryItem::setAuthor(QString fullname){
    this -> author = fullname;
}

void LibraryItem::setBorrowing(bool value) {
    this -> isBorrowed = value;
}

void LibraryItem::displayInfo() {
    qDebug() << "ID:" << id
             << "Title:" << title
             << "Author:" << author
             << "Borrowed:" << isBorrowed;
}

#include "libraryitem.h"
#include <QString>


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

bool LibraryItem::getIsBorrowed() {
    return this -> isBorrowed;
}

void LibraryItem::setAuthor(QString fullname){
    this -> author = fullname;
}

void LibraryItem::setBorrowing(bool value) {
    this -> isBorrowed = value;
}

void LibraryItem::setTitle(QString value) {
    this -> title = value;
}

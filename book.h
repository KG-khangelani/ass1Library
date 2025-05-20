#ifndef BOOK_H
#define BOOK_H

#include "libraryitem.h"

class Book : public LibraryItem
{
public:
    Book();
    QString getGenre();
    void setGenre();

private:
    QString genre;
};

#endif // BOOK_H

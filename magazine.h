#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "libraryitem.h"

class Magazine : public LibraryItem
{
public:
    Magazine();
    int getIssueNo();
    void setIssueNo(int value)
};

#endif // MAGAZINE_H

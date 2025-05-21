#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "libraryitem.h"

class Magazine : public LibraryItem
{
public:
    Magazine();
    int getIssueNo();
    void setIssueNo(int value);

private:
    int issueNo;
};

#endif // MAGAZINE_H

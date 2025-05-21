#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "libraryitem.h"

class Magazine : public LibraryItem
{
public:
    Magazine();
    Magazine(QJsonObject item);
    int getIssueNo();
    void setIssueNo(int value);
    void displayInfo() override
    {
        LibraryItem::displayInfo();
        printf("Issue Number: %d\n", issueNo);
    }

private:
    int issueNo;
};

#endif // MAGAZINE_H

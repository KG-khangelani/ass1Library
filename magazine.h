#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "libraryitem.h"

class Magazine : public LibraryItem
{
public:
    Magazine();
    Magazine(const QJsonObject item);
    int getIssueNo();
    void setIssueNo(int value);
    void displayInfo() override
    {
        LibraryItem::displayInfo();
        printf("Issue Number: %d\n", issueNo);
    }
    friend bool operator==(const Magazine &lhs, const Magazine &rhs)
    {
        return lhs.getTitle() == rhs.getTitle() &&
               lhs.getAuthor() == rhs.getAuthor() &&
               lhs.getID() == rhs.getID() &&
               lhs.issueNo == rhs.issueNo;
    };

private:
    int issueNo;
};

#endif // MAGAZINE_H

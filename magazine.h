#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "libraryitem.h"
#include <QJsonValue>
#include <QJsonObject>

class Magazine : public LibraryItem
{
public:
    Magazine();
    Magazine(const QJsonObject &item);
    int getIssueNo() const;
    void setIssueNo(int value);
    void displayInfo() const override
    {
        LibraryItem::displayInfo();
        printf("Issue Number: %d\n", issueNo);
        printf("=========================\n");
    }
    friend bool operator==(const Magazine &lhs, const Magazine &rhs)
    {
        return lhs.getTitle() == rhs.getTitle() &&
               lhs.getAuthor() == rhs.getAuthor() &&
               lhs.getID() == rhs.getID() &&
               lhs.getIsBorrowed() == rhs.getIsBorrowed() &&
               lhs.issueNo == rhs.issueNo;
    };

private:
    int issueNo;
};

#endif // MAGAZINE_H

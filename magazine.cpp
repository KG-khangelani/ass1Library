#include "magazine.h"
#include <QJsonObject>
#include <QJsonValue>

Magazine::Magazine() : issueNo(0) {}

Magazine::Magazine(const QJsonObject &item)
{
    setID(item["id"].toString());
    setAuthor(item["author"].toString());
    setBorrowing(item["isBorrowed"].toBool());
    setTitle(item["title"].toString());
    // Support both 'issueNumber' (saved data) and 'issue' (initial data)
    int issueVal = item.contains("issueNumber") ? item["issueNumber"].toInt() : item["issue"].toInt();
    setIssueNo(issueVal);
}

int Magazine::getIssueNo() const
{
    return this->issueNo;
}

void Magazine::setIssueNo(int value)
{
    this->issueNo = value;
}

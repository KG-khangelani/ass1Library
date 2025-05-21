#include "magazine.h"
#include <QJsonObject>
#include <QJsonValue>

Magazine::Magazine() {}

Magazine::Magazine(QJsonObject item)
{
    setID(item["id"].toString());
    setAuthor(item["fullname"].toString());
    setBorrowing(item["is_borrowed"].toBool());
    setTitle(item["title"].toString());
    setIssueNo(item["issueNumber"].toInt());
}

int Magazine::getIssueNo()
{
    return this->issueNo;
}

void Magazine::setIssueNo(int value)
{
    this->issueNo = value;
}

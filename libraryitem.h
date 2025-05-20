#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H
#include <QString>

class LibraryItem
{
public:
    LibraryItem();
    QString getTitle();
    QString getAuthor();
    bool getIsBorrowed();

    void setAuthor(QString value);
    void setTitle(QString value);
    void setBorrowing(bool value);
private:
    int id;
    QString title;
    QString author;
    bool isBorrowed;
};

#endif // LIBRARYITEM_H

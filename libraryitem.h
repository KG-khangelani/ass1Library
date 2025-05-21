#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H
#include <QString>

class LibraryItem
{
public:
    LibraryItem();
    int getID();
    QString getTitle();
    QString getAuthor();
    bool getIsBorrowed();

    void setID(int value);
    void setAuthor(QString fullname);
    void setTitle(QString value);
    void setBorrowing(bool value);

    friend bool operator==(const LibraryItem &lhs, const LibraryItem &rhs)
    {
        return lhs.title == rhs.title &&
               lhs.author == rhs.author &&
               lhs.id == rhs.id;
    };

    virtual void displayInfo();

private:
    int id;
    QString title;
    QString author;
    bool isBorrowed;
};

#endif // LIBRARYITEM_H

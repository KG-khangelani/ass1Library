#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H
#include <QString>

class LibraryItem
{
public:
    LibraryItem();
    QString getID() const;
    QString getTitle() const;
    QString getAuthor() const;
    bool getIsBorrowed() const;

    void setID(QString value);
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
    QString id;
    QString title;
    QString author;
    bool isBorrowed;
};

#endif // LIBRARYITEM_H

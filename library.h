#ifndef LIBRARY_H
#define LIBRARY_H
#include "book.h"
#include "libraryitem.h"
#include "magazine.h"
#include <QList>
#include <QJsonObject>

class Library
{
public:
    Library();
    void searchItem();
    void addItem(int id);
    void borrowItem(int id);
    void returnItem(int id);
    void loadData(QString &path);

private:
    QList<LibraryItem> catalogue;
    QList<int> matrix;
};

#endif // LIBRARY_H

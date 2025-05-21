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

protected:
    QString filePath = "library.json";
    void loadData();

private:
    QList<LibraryItem> catalogue;
    QList<int> matrix;
};

#endif // LIBRARY_H

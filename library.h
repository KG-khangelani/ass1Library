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
    void addItem();
    void borrowItem();
    void returnItem();

protected:
    QString filePath = "library.json";
    void loadData();
    void saveData();

private:
    QList<Book> booksCatalogue;
    QList<Magazine> magsCatalogue;
};

#endif // LIBRARY_H

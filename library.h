#ifndef LIBRARY_H
#define LIBRARY_H
#include "book.h"
#include "libraryitem.h"
#include "magazine.h"
#include <QList>
#include <QJsonObject>
#include <QCoreApplication>
#include <QDir>

class Library
{
public:
    Library();
    void searchItem();
    void addItem();
    void borrowItem();
    void returnItem();
    void saveData();
    void printAllItems();

protected:
    // Store JSON alongside the executable
    QString filePath = QCoreApplication::applicationDirPath() + "/library_data.json";
    void loadData();

private:
    QList<Book> booksCatalogue;
    QList<Magazine> magsCatalogue;
};

#endif // LIBRARY_H

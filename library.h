#ifndef LIBRARY_H
#define LIBRARY_H
#include <QCoreApplication>
#include <QJsonObject>
#include <QList>
#include <QDir>
#include "book.h"
#include "libraryitem.h"
#include "magazine.h"

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
    QList<Book> getBooksCatalogue();
    QList<Magazine> getMagazinesCatalogue();
    // make the sort key optional by giving it a default value
    void sortItems(QList<Book> &items, const QString &sortBy);
    void sortItems(QList<Magazine> &items, const QString &sortBy = QString());

protected:
    // Store JSON alongside the executable
    QString filePath = QCoreApplication::applicationDirPath() + "/library_data.json";
    void loadData();

private:
    QList<Book> booksCatalogue;
    QList<Magazine> magsCatalogue;
};

#endif // LIBRARY_H

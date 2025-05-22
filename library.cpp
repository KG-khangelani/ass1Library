#include <iostream>
#include "library.h"
#include <QString>
#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QJsonValueRef>

using namespace std;

Library::Library()
{
    // Load data from JSON file
    loadData();
}

void Library::loadData()
{
    QFile file(this->filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open: " << filePath;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());

    if (!doc.isArray())
    {
        qWarning() << "Expected JSON array in: " << filePath;
        return;
    }

    QJsonArray jsonArray = doc.array();
    for (const QJsonValue &value : jsonArray)
    {
        if (value.isObject())
        {
            QJsonObject item = value.toObject();
            LibraryItem libraryItem;
            libraryItem.setID(item["id"].toString());
            libraryItem.setTitle(item["title"].toString());
            libraryItem.setAuthor(item["author"].toString());
            libraryItem.setBorrowing(item["isBorrowed"].toBool());

            if (item.contains("genre"))
            {
                Book book(item);
                booksCatalogue.append(book);
            }
            else if (item.contains("issueNumber"))
            {
                Magazine magazine(item);
                magsCatalogue.append(magazine);
            }
        }
    }
}

void Library::saveData()
{
    QFile file(this->filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        qWarning() << "Failed to open: " << filePath;
        return;
    }

    QJsonArray jsonArray;

    for (const Book &book : booksCatalogue)
    {
        QJsonObject item;
        item["id"] = book.getID();
        item["title"] = book.getTitle();
        item["author"] = book.getAuthor();
        item["isBorrowed"] = book.getIsBorrowed();
        item["genre"] = book.getGenre();
        jsonArray.append(item);
    }

    for (const Magazine &magazine : magsCatalogue)
    {
        QJsonObject item;
        item["id"] = magazine.getID();
        item["title"] = magazine.getTitle();
        item["author"] = magazine.getAuthor();
        item["isBorrowed"] = magazine.getIsBorrowed();
        item["issueNumber"] = magazine.getIssueNo();
        jsonArray.append(item);
    }

    QJsonDocument doc(jsonArray);
    file.write(doc.toJson());
    file.close();
    printf("Data saved successfully!\n");
}

void Library::searchItem()
{
    // Implement search functionality here

    cout << "Searching for a Book or Magazine?" << endl;
    cout << "b - book | m - magazine" << endl;
    string searchTypeStd;
    cin >> searchTypeStd;
    QString searchType = QString::fromStdString(searchTypeStd);

    while (searchType != "b" && searchType != "m")
    {
        printf("Invalid input. Please enter 'b' or 'm': ");
        cin >> searchTypeStd;
        searchType = QString::fromStdString(searchTypeStd).toLower();
    }

    string searchTermStd;
    printf("Search by:\n");
    printf("t - title | a - author | i - ID\n");
    cin >> searchTermStd;
    QString searchTerm = QString::fromStdString(searchTermStd);

    while (searchTerm != "t" && searchTerm != "a" && searchTerm != "i")
    {
        printf("Invalid input. Please enter 't', 'a', or 'i': ");
        cin >> searchTermStd;
        searchTerm = QString::fromStdString(searchTermStd).toLower();
    }
    QString titleSearch, authorSearch, idSearch;

    if (searchTerm == "t")
    {
        string titleStd;
        printf("Enter title: ");
        cin >> titleStd;
        titleSearch = QString::fromStdString(titleStd).toLower();
    }
    else if (searchTerm == "a")
    {
        string authorStd;
        printf("Enter author: ");
        cin >> authorStd;
        authorSearch = QString::fromStdString(authorStd).toLower();
    }
    else if (searchTerm == "i")
    {
        string idStd;
        printf("Enter ID: ");
        cin >> idStd;
        idSearch = QString::fromStdString(idStd).toLower();
    }

    if (searchType == "b")
    {
        // Search in booksCatalogue
        for (const Book &book : booksCatalogue)
        {
            if ((searchTerm == "t" && book.getTitle().toLower() == titleSearch.toLower()) ||
                (searchTerm == "a" && book.getAuthor().toLower() == authorSearch.toLower()) ||
                (searchTerm == "i" && book.getID().toLower() == idSearch.toLower()))
            {
                book.displayInfo();
                return;
            }
        }
        printf("Book not found in the catalogue.\n\n");
        return;
    }
    else if (searchType == "m")
    {
        // Search in magsCatalogue
        for (const Magazine &magazine : magsCatalogue)
        {
            if ((searchTerm == "t" && magazine.getTitle().toLower() == titleSearch.toLower()) ||
                (searchTerm == "a" && magazine.getAuthor().toLower() == authorSearch.toLower()) ||
                (searchTerm == "i" && magazine.getID().toLower() == idSearch.toLower()))
            {
                magazine.displayInfo();
                return;
            }
        }
        printf("Magazine not found in the catalogue.\n\n");
        return;
    }
}

void Library::addItem()
{
    // Implement add item functionality here. Itshould update the JSON file too on ene on runtime.
    QFile file(this->filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open: " << filePath;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isArray())
    {
        qWarning() << "Expected JSON array in: " << filePath;
        return;
    }

    QJsonArray jsonArray = doc.array();
    QJsonObject newItem;

    printf("Is it a book or magazine? (b/m): ");
    string itemTypeStd;
    cin >> itemTypeStd;
    QString itemType = QString::fromStdString(itemTypeStd);
    while (itemType != "b" && itemType != "m")
    {
        printf("Invalid input. Please enter 'b' or 'm': ");
        cin >> itemTypeStd;
        itemType = QString::fromStdString(itemTypeStd).toLower();
    }
    if (itemType == "b")
    {
        string IdStd, titleStd, authorStd, genreStd;
        printf("Enter issue number: ");
        printf("Format should be ISBN like: 48410-0 or 23453-X \n");
        cin >> IdStd;
        printf("Enter title: ");
        cin >> titleStd;
        printf("Enter author: ");
        cin >> authorStd;
        printf("Enter genre: ");
        cin >> genreStd;

        newItem["id"] = QString::fromStdString(titleStd);
        newItem["title"] = QString::fromStdString(titleStd);
        newItem["author"] = QString::fromStdString(authorStd);
        newItem["genre"] = QString::fromStdString(genreStd);
        newItem["isBorrowed"] = false;

        Book newBook = Book(newItem);
        if (booksCatalogue.contains(newBook))
        {
            printf("Item already exists in the catalogue.\n");
            return;
        }
        booksCatalogue.append(newBook);
    }
    else if (itemType == "m")
    {
        string IdStd, titleStd, authorStd, issueNoStd;
        printf("Enter issue number: ");
        printf("Format should be ISBN like: 48410-0 or 23453-X \n");
        cin >> IdStd;
        printf("Enter title: ");
        cin >> titleStd;
        printf("Enter author's full names: ");
        cin >> authorStd;
        cin >> issueNoStd;

        newItem["id"] = QString::fromStdString(IdStd);
        newItem["title"] = QString::fromStdString(titleStd);
        newItem["author"] = QString::fromStdString(authorStd);
        newItem["issueNumber"] = QString::fromStdString(issueNoStd);
        newItem["isBorrowed"] = false;

        Magazine newMag = Magazine(newItem);
        if (magsCatalogue.contains(newMag))
        {
            printf("Item already exists in the catalogue.\n");
            return;
        }
        magsCatalogue.append(newMag);
    }

    jsonArray.append(newItem);
    QJsonDocument newDoc(jsonArray);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open: " << filePath;
        return;
    }
    file.write(newDoc.toJson());
    file.close();

    printf("Item added successfully!\n");
}

void Library::borrowItem()
{
    // Implement borrow item functionality here
    printf("Would you like to borrow a book or magazine? (b/m): ");
    string itemTypeStd;
    cin >> itemTypeStd;
    QString itemType = QString::fromStdString(itemTypeStd);
    while (itemType != "b" && itemType != "m")
    {
        printf("Invalid input. Please enter 'b' or 'm': ");
        cin >> itemTypeStd;
        itemType = QString::fromStdString(itemTypeStd).toLower();
    }

    if (itemType == "b")
    {
        printf("Enter book ID: ");
        string idStd;
        cin >> idStd;
        QString idSearch = QString::fromStdString(idStd);
        for (Book &book : booksCatalogue)
        {
            if (book.getID().toLower() == idSearch)
            {
                if (book.getIsBorrowed())
                {
                    printf("Book is already borrowed.\n");
                }
                else
                {
                    book.setBorrowing(true);
                    printf("Book borrowed successfully!\n");
                }
                return;
            }
        }
        printf("Book not found in the catalogue.\n");
    }
    else if (itemType == "m")
    {
        printf("Enter magazine ID: ");
        string idStd;
        cin >> idStd;
        QString idSearch = QString::fromStdString(idStd);
        for (Magazine &magazine : magsCatalogue)
        {
            if (magazine.getID().toLower() == idSearch)
            {
                if (magazine.getIsBorrowed())
                {
                    printf("Magazine is already borrowed.\n");
                }
                else
                {
                    magazine.setBorrowing(true);
                    printf("Magazine borrowed successfully!\n");
                }
                return;
            }
        }
        printf("Magazine not found in the catalogue.\n");
    }
}

void Library::returnItem()
{
    // Implement return item functionality here
    printf("Are you returning a book or magazine? (b/m): ");
    string itemTypeStd;
    cin >> itemTypeStd;
    QString itemType = QString::fromStdString(itemTypeStd);
    while (itemType != "b" && itemType != "m")
    {
        printf("Invalid input. Please enter 'b' or 'm': ");
        cin >> itemTypeStd;
        itemType = QString::fromStdString(itemTypeStd).toLower();
    }

    if (itemType == "b")
    {
        printf("Enter book ID: ");
        string idStd;
        cin >> idStd;
        QString idSearch = QString::fromStdString(idStd);
        for (Book &book : booksCatalogue)
        {
            if (book.getID().toLower() == idSearch)
            {
                if (!book.getIsBorrowed())
                {
                    printf("Book is not borrowed.\n");
                }
                else
                {
                    book.setBorrowing(false);
                    printf("Book returned successfully!\n");
                }
                return;
            }
        }
        printf("Book not found in the catalogue.\n");
    }
    else if (itemType == "m")
    {
        printf("Enter magazine ID: ");
        string idStd;
        cin >> idStd;
        QString idSearch = QString::fromStdString(idStd);
        for (Magazine &magazine : magsCatalogue)
        {
            if (magazine.getID().toLower() == idSearch)
            {
                if (!magazine.getIsBorrowed())
                {
                    printf("Magazine is not borrowed.\n");
                }
                else
                {
                    magazine.setBorrowing(false);
                    printf("Magazine returned successfully!\n");
                }
                return;
            }
        }
        printf("Magazine not found in the catalogue.\n");
    }
}
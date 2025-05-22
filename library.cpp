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
    // Ensure persistent JSON file exists by copying from resource on first run
    QString resourcePath = ":/data/library_data.json";
    if (!QFile::exists(filePath))
    {
        QFile resFile(resourcePath);
        if (resFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QByteArray data = resFile.readAll();
            QFile extFile(filePath);
            if (extFile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                extFile.write(data);
                extFile.close();
            }
            resFile.close();
        }
    }
    // Load data into memory
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
            // Handle magazines with either 'issueNumber' (saved) or initial 'issue'
            else if (item.contains("issueNumber") || item.contains("issue"))
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

// Provide functionality to print all books and magazines in the catalog
void Library::printAllItems()
{
    printf("Books Catalogue:\n");
    if (booksCatalogue.isEmpty())
    {
        printf("No books in catalogue.\n");
    }
    else
    {
        for (const Book &book : booksCatalogue)
        {
            book.displayInfo();
        }
    }
    printf("Magazines Catalogue:\n");
    if (magsCatalogue.isEmpty())
    {
        printf("No magazines in catalogue.\n");
    }
    else
    {
        for (const Magazine &mag : magsCatalogue)
        {
            mag.displayInfo();
        }
    }
}

void Library::searchItem()
{
    printf("Searching for a Book or Magazine?");
    printf("[b] - book | [m] - magazine");
    string searchTypeStd;
    cin >> searchTypeStd;
    QString searchType = QString::fromStdString(searchTypeStd);

    while (searchType != "b" && searchType != "m")
    {
        printf("\nInvalid input. Please enter 'b' or 'm': ");
        cin >> searchTypeStd;
        searchType = QString::fromStdString(searchTypeStd).toLower();
    }

    string searchTermStd;
    printf("Search by:\n");
    printf("[t] - title | [a] - author | [i] - ID\n");
    cin >> searchTermStd;
    QString searchTerm = QString::fromStdString(searchTermStd);

    while (searchTerm != "t" && searchTerm != "a" && searchTerm != "i")
    {
        printf("\nInvalid input. Please enter 't', 'a', or 'i': ");
        cin >> searchTermStd;
        searchTerm = QString::fromStdString(searchTermStd).toLower();
    }
    QString titleSearch, authorSearch, idSearch;

    if (searchTerm == "t")
    {
        string titleStd;
        printf("Enter title: ");
        getline(cin >> std::ws, titleStd);
        titleSearch = QString::fromStdString(titleStd).toLower();
    }
    else if (searchTerm == "a")
    {
        string authorStd;
        printf("Enter author: ");
        getline(cin >> std::ws, authorStd);
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
        bool found = false;
        for (const Book &book : booksCatalogue)
        {
            if ((searchTerm == "t" && book.getTitle().toLower() == titleSearch) ||
                (searchTerm == "a" && book.getAuthor().toLower() == authorSearch) ||
                (searchTerm == "i" && book.getID().toLower() == idSearch))
            {
                book.displayInfo();
                found = true;
                break;
            }
        }
        if (!found)
            printf("\nBook not found in the catalogue.\n");
        return;
    }
    else if (searchType == "m")
    {
        bool found = false;
        for (const Magazine &magazine : magsCatalogue)
        {
            if ((searchTerm == "t" && magazine.getTitle().toLower() == titleSearch) ||
                (searchTerm == "a" && magazine.getAuthor().toLower() == authorSearch) ||
                (searchTerm == "i" && magazine.getID().toLower() == idSearch))
            {
                magazine.displayInfo();
                found = true;
                break;
            }
        }
        if (!found)
            printf("\nMagazine not found in the catalogue.\n");
        return;
    }
}

void Library::addItem()
{
    // Prompt for new item type
    cout << "Is it a book or magazine? (b/m): ";
    string typeStd;
    cin >> typeStd;
    QString type = QString::fromStdString(typeStd).toLower();
    while (type != "b" && type != "m")
    {
        cout << "Invalid input. Please enter 'b' or 'm': ";
        cin >> typeStd;
        type = QString::fromStdString(typeStd).toLower();
    }

    QJsonObject newItem;
    if (type == "b")
    {
        string id, title, author, genre;
        cout << "Enter ID (ISBN like 48410-0): ";
        cin >> id;
        cout << "Enter title: ";
        cin >> title;
        cout << "Enter author: ";
        cin >> author;
        cout << "Enter genre: ";
        cin >> genre;
        newItem["id"] = QString::fromStdString(id);
        newItem["title"] = QString::fromStdString(title);
        newItem["author"] = QString::fromStdString(author);
        newItem["genre"] = QString::fromStdString(genre);
        newItem["isBorrowed"] = false;
        Book book(newItem);
        if (booksCatalogue.contains(book))
        {
            std::cout << "\nItem already exists in the catalogue.\n";
            return;
        }
        booksCatalogue.append(book);
    }
    else
    {
        string id, title, author, issue;
        cout << "Enter ID (like 2025-04): ";
        cin >> id;
        cout << endl
             << "Enter title: ";
        cin >> title;
        cout << endl
             << "Enter author: ";
        cin >> author;
        cout << endl
             << "Enter issue number: ";
        cin >> issue;
        newItem["id"] = QString::fromStdString(id);
        newItem["title"] = QString::fromStdString(title);
        newItem["author"] = QString::fromStdString(author);
        newItem["issueNumber"] = QString::fromStdString(issue);
        newItem["isBorrowed"] = false;
        Magazine mag(newItem);
        if (magsCatalogue.contains(mag))
        {
            printf("Item already exists in the catalogue.\n");
            return;
        }
        magsCatalogue.append(mag);
    }

    // Persist updated catalog to JSON file
    saveData();
    printf("Item added successfully!\n");
}

void Library::borrowItem()
{
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
        QString idSearch = QString::fromStdString(idStd).toLower();
        for (Book &book : booksCatalogue)
        {
            if (book.getID().toLower() == idSearch)
            {
                if (book.getIsBorrowed())
                {
                    printf("\nBook is already borrowed.\n");
                }
                else
                {
                    book.setBorrowing(true);
                    printf("\nBook borrowed successfully!\n");
                    saveData();
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
        QString idSearch = QString::fromStdString(idStd).toLower();
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
                    saveData();
                }
                return;
            }
        }
        printf("Magazine not found in the catalogue.\n");
    }
}

void Library::returnItem()
{
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
        QString idSearch = QString::fromStdString(idStd).toLower();
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
                    saveData();
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
                    saveData();
                }
                return;
            }
        }
        printf("Magazine not found in the catalogue.\n");
    }
}
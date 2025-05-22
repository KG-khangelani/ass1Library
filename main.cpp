#include "library.h"
#include <iostream>
#include <QCoreApplication>
#include <string>
#include <QDebug>
#include <QString>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("Library Management System");
    QCoreApplication::setApplicationVersion("1.0");
    QCoreApplication::setOrganizationDomain("librarymanagementsystem.com");

    Library ithala_lencwadi = Library();
    printf("Welcome to the Library Management System!\n");
    string inputStd;
    QString input;

    while (input != "q")
    {
        printf("\n");
        printf("      _______\n");
        printf("     /      /,\n");
        printf("    / Home //\n");
        printf("   /______//\n");
        printf("  (______(/\n\n");
        printf("Please choose an option:\n");
        printf("[1] - Search for an item\n");
        printf("[2] - Add an item\n");
        printf("[3] - Borrow an item\n");
        printf("[4] - Return an item\n");
        printf("[5] - Print all items\n");
        printf("[q] - Exit\n");
        cin >> inputStd;
        input = QString::fromStdString(inputStd);
        while (input != "1" && input != "q" && input != "2" && input != "3" && input != "4" && input != "5")
        {
            printf("Invalid input. Please enter a number between 1 and 5: ");
            cin >> inputStd;
            input = QString::fromStdString(inputStd);
        }
        if (input == "1")
        {
            ithala_lencwadi.searchItem();
        }
        else if (input == "2")
        {
            ithala_lencwadi.addItem();
        }
        else if (input == "3")
        {
            ithala_lencwadi.borrowItem();
        }
        else if (input == "4")
        {
            ithala_lencwadi.returnItem();
        }
        else if (input == "5")
        {
            ithala_lencwadi.printAllItems();
        }
        else if (input == "q")
        {
            printf("Saving data...\n");
            ithala_lencwadi.saveData();
            printf("Exiting the program. Goodbye!\n");
            return 0;
        }
    }

#ifdef _WIN32
    // Wait for key press to keep console open
    printf("\nPress Enter to exit...");
    getchar();
#endif

    return app.exec();
}

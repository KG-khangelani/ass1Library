#include "library.h"
#include <iostream>
#include <string>
#include <QDebug>
#include <QString>

using namespace std;

int main()
{
    QString filename = "library.json";
    Library ithala_lencwadi = Library();
    ithala_lencwadi.loadData(filename);
    string input;
    cout << "Hello" << endl;
    cin >> input;
    cout << "You entered: " << input << endl;
    printf("John vula");
    // QDebug() << "Hello World";

#ifdef _WIN32
    // Wait for key press to keep console open
    printf("\nPress Enter to exit...");
    getchar();
#endif

    return 0;
}
